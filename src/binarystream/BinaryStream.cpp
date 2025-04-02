#include <binarystream/BinaryStream.hpp>

namespace bedrock_protocol {

template <typename T>
T swapEndian(T u);

BinaryStream::BinaryStream() : ReadOnlyBinaryStream({}, true), mBuffer(mOwnedBuffer) {}

BinaryStream::BinaryStream(std::string& buffer, bool copyBuffer)
: ReadOnlyBinaryStream(buffer, copyBuffer),
  mBuffer(buffer) {}

template <typename T>
void BinaryStream::write(T value, bool bigEndian) {
    if (bigEndian) { value = swapEndian(value); }
    mBuffer.append((const char*)(&value), sizeof(T));
}

void BinaryStream::setPosition(size_t value) { mReadPointer = value; }

void BinaryStream::reserve(size_t size) { mBuffer.reserve(size); }

void BinaryStream::reset() {
    mBuffer.clear();
    mReadPointer   = 0;
    mHasOverflowed = false;
}

std::string BinaryStream::getAndReleaseData() {
    std::string result = std::move(mBuffer);
    reset();
    return result;
}

void BinaryStream::writeBytes(const void* origin, size_t num) { mBuffer.append((const char*)origin, num); }

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
}

void BinaryStream::writeUnsignedInt24(uint32_t value) {
    auto* b = reinterpret_cast<unsigned char*>(&value);
    for (int i = 0; i < 3; i++) write<>(*(b + i));
}

} // namespace bedrock_protocol