#include <binarystream/ReadOnlyBinaryStream.hpp>

namespace bedrock_protocol {

ReadOnlyBinaryStream::ReadOnlyBinaryStream() {
    mOwnedBuffer   = std::string();
    mBufferView    = mOwnedBuffer;
    mReadPointer   = 0;
    mHasOverflowed = false;
}

ReadOnlyBinaryStream::ReadOnlyBinaryStream(std::string_view buffer, bool copyBuffer) {
    if (copyBuffer) {
        mOwnedBuffer = buffer;
        mBufferView  = mOwnedBuffer;
    } else {
        mBufferView = buffer;
    }
    mReadPointer   = 0;
    mHasOverflowed = false;
}

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

template <typename T>
bool ReadOnlyBinaryStream::read(T* target, bool bigEndian) {
    if (mHasOverflowed) { return false; }
    size_t newReadPointer = mReadPointer + sizeof(T);
    if (newReadPointer < mReadPointer || newReadPointer > mBufferView.length()) {
        mHasOverflowed = true;
        return false;
    }
    std::copy(
        mBufferView.begin() + mReadPointer,
        mBufferView.begin() + newReadPointer,
        reinterpret_cast<char*>(target)
    );
    mReadPointer = newReadPointer;
    if (bigEndian) { *target = swapEndian(*target); }
    return true;
}

size_t ReadOnlyBinaryStream::getPosition() const { return mReadPointer; }

std::string ReadOnlyBinaryStream::getLeftBuffer() { return std::string(mBufferView.substr(mReadPointer)); }

bool ReadOnlyBinaryStream::isOverflowed() { return mHasOverflowed; }

bool ReadOnlyBinaryStream::hasDataLeft() { return mReadPointer < mBufferView.size(); }

bool ReadOnlyBinaryStream::getBytes(void* target, size_t num) {
    if (mHasOverflowed) { return false; }
    if (num == 0) { return true; }

    size_t checkedNumber = num + mReadPointer;
    bool   hasOverflowed = checkedNumber < mReadPointer;

    if (checkedNumber >= mReadPointer && checkedNumber <= mBufferView.length()) {
        std::copy(
            mBufferView.begin() + mReadPointer,
            mBufferView.begin() + mReadPointer + num,
            static_cast<char*>(target)
        );
        mReadPointer += num;
        return true;
    } else {
        if (hasOverflowed || checkedNumber > mBufferView.length()) { mHasOverflowed = true; }
        return false;
    }
}

uint8_t ReadOnlyBinaryStream::getByte() {
    uint8_t value = 0;
    if (read<>(&value)) { return value; }
    return value;
}

uint8_t ReadOnlyBinaryStream::getUnsignedChar() { return getByte(); }

uint16_t ReadOnlyBinaryStream::getUnsignedShort() {
    uint16_t value = 0;
    if (read<>(&value)) { return value; }
    return value;
}

uint32_t ReadOnlyBinaryStream::getUnsignedInt() {
    uint32_t value = 0;
    if (read<>(&value)) { return value; }
    return value;
}

uint64_t ReadOnlyBinaryStream::getUnsignedInt64() {
    uint64_t value = 0;
    if (read<>(&value)) { return value; }
    return value;
}

bool ReadOnlyBinaryStream::getBool() { return getByte(); }

double ReadOnlyBinaryStream::getDouble() {
    double value = 0;
    if (read<>(&value)) { return value; }
    return value;
}

float ReadOnlyBinaryStream::getFloat() {
    float value = 0;
    if (read<>(&value)) { return value; }
    return value;
}

int32_t ReadOnlyBinaryStream::getSignedInt() {
    int32_t value = 0;
    if (read<>(&value)) { return value; }
    return value;
}

int64_t ReadOnlyBinaryStream::getSignedInt64() {
    int64_t value = 0;
    if (read<>(&value)) { return value; }
    return value;
}

int16_t ReadOnlyBinaryStream::getSignedShort() {
    int16_t value = 0;
    if (read<>(&value)) { return value; }
    return value;
}

uint32_t ReadOnlyBinaryStream::getUnsignedVarInt() {
    uint32_t value = 0;
    int      shift = 0;
    uint8_t  b;
    do {
        if (!read<uint8_t>(&b)) { return value; }
        value |= (b & 0x7F) << shift;
        shift += 7;
    } while (b & 0x80);
    return value;
}

uint64_t ReadOnlyBinaryStream::getUnsignedVarInt64() {
    uint64_t value = 0;
    int      shift = 0;
    uint8_t  b;
    do {
        if (!read<uint8_t>(&b)) { return value; }
        value |= (b & (uint64_t)0x7F) << shift;
        shift += 7;
    } while (b & 0x80);
    return value;
}

int32_t ReadOnlyBinaryStream::getVarInt() {
    uint32_t decoded_value;

    decoded_value = getUnsignedVarInt();
    if ((decoded_value & 1) != 0) return ~(decoded_value >> 1);
    else return decoded_value >> 1;
}

int64_t ReadOnlyBinaryStream::getVarInt64() {
    uint64_t decoded_value;
    decoded_value = getUnsignedVarInt64();
    if ((decoded_value & 1) != 0) return ~(decoded_value >> 1);
    else return decoded_value >> 1;
}

float ReadOnlyBinaryStream::getNormalizedFloat() { return (float)getVarInt64() / 2147483647.0f; }

int32_t ReadOnlyBinaryStream::getSignedBigEndianInt() {
    int32_t value = 0;
    if (read<>(&value, true)) { return value; }
    return value;
}

void ReadOnlyBinaryStream::getString(std::string& outString) {
    uint32_t length = getUnsignedVarInt();
    if (length > 0) {
        outString     = mBufferView.substr(mReadPointer, length);
        mReadPointer += length;
    }
}

std::string ReadOnlyBinaryStream::getString() {
    std::string outString;
    getString(outString);
    return outString;
}

} // namespace bedrock_protocol