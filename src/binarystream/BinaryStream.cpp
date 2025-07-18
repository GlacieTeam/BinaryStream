#include <binarystream/BinaryStream.hpp>

namespace bedrock_protocol {

template <typename T>
T swapEndian(T u) {
    union {
        T             u;
        unsigned char u8[sizeof(T)];
    } source, dest;
    source.u = u;
    for (size_t k = 0; k < sizeof(T); k++) dest.u8[k] = source.u8[sizeof(T) - k - 1];
    return dest.u;
}

BinaryStream::BinaryStream() : ReadOnlyBinaryStream(std::string(), true), mBuffer(mOwnedBuffer) {}

BinaryStream::BinaryStream(std::string& buffer, bool copyBuffer)
: ReadOnlyBinaryStream(buffer, copyBuffer),
  mBuffer(buffer) {}

template <typename T>
void BinaryStream::write(T value, bool bigEndian) {
    if (bigEndian) { value = swapEndian(value); }
    mBuffer.append((const char*)(&value), sizeof(T));
    mBufferView = mBuffer;
}

void BinaryStream::reserve(size_t size) { mBuffer.reserve(size); }

size_t BinaryStream::size() const { return mBuffer.size(); }

void BinaryStream::reset() {
    mBuffer.clear();
    mReadPointer   = 0;
    mHasOverflowed = false;
    mBufferView    = mBuffer;
}

std::string& BinaryStream::data() { return mBuffer; }

const std::string& BinaryStream::data() const { return mBuffer; }

std::string BinaryStream::copyBuffer() const { return mBuffer; }

std::string BinaryStream::getAndReleaseData() {
    std::string result = std::move(mBuffer);
    reset();
    return result;
}

void BinaryStream::writeBytes(const void* origin, size_t num) {
    mBuffer.append((const char*)origin, num);
    mBufferView = mBuffer;
}

void BinaryStream::writeByte(uint8_t value) { write<>(value); }

void BinaryStream::writeUnsignedChar(uint8_t value) { writeByte(value); }

void BinaryStream::writeUnsignedShort(uint16_t value) { write<>(value); }

void BinaryStream::writeUnsignedInt(uint32_t value) { write<>(value); }

void BinaryStream::writeUnsignedInt64(uint64_t value) { write<>(value); }

void BinaryStream::writeBool(bool value) { writeByte(value); }

void BinaryStream::writeDouble(double value) { write<>(value); }

void BinaryStream::writeFloat(float value) { write<>(value); }

void BinaryStream::writeSignedInt(int32_t value) { write<>(value); }

void BinaryStream::writeSignedInt64(int64_t value) { write<>(value); }

void BinaryStream::writeSignedShort(int16_t value) { write<>(value); }

void BinaryStream::writeUnsignedVarInt(uint32_t uvalue) {
    uint8_t next_byte;
    do {
        next_byte   = uvalue & 0x7F;
        uvalue    >>= 7;
        if (uvalue) next_byte |= 0x80u;
        writeByte(next_byte);
    } while (uvalue);
};

void BinaryStream::writeUnsignedVarInt64(uint64_t uvalue) {
    uint8_t next_byte;
    do {
        next_byte   = uvalue & 0x7F;
        uvalue    >>= 7;
        if (uvalue) next_byte |= 0x80u;
        writeByte(next_byte);
    } while (uvalue);
};

void BinaryStream::writeVarInt(int32_t value) {
    if (value >= 0) writeUnsignedVarInt(2 * value);
    else writeUnsignedVarInt(~(2 * value));
}

void BinaryStream::writeVarInt64(int64_t value) {
    uint64_t uvalue;
    if (value >= 0) uvalue = 2 * value;
    else uvalue = ~(2 * value);
    writeUnsignedVarInt64(uvalue);
}

void BinaryStream::writeNormalizedFloat(float value) { writeVarInt64((int)(value * 2147483647.0)); }

void BinaryStream::writeSignedBigEndianInt(int32_t value) { write<>(value, true); }

void BinaryStream::writeString(std::string_view value) {
    writeUnsignedVarInt((uint32_t)value.size());
    mBuffer.append(value);
    mBufferView = mBuffer;
}

void BinaryStream::writeUnsignedInt24(uint32_t value) {
    auto* b = reinterpret_cast<unsigned char*>(&value);
    for (int i = 0; i < 3; i++) write<>(*(b + i));
}

void BinaryStream::writeRawBytes(std::string_view rawBuffer) {
    mBuffer.append(rawBuffer);
    mBufferView = mBuffer;
}

void BinaryStream::writeStream(ReadOnlyBinaryStream const& stream) { writeRawBytes(stream.mBufferView); }

} // namespace bedrock_protocol