#include <binarystream/ReadOnlyBinaryStream.hpp>

namespace bedrock_protocol {

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

ReadOnlyBinaryStream::ReadOnlyBinaryStream(const char* data, size_t size)
: ReadOnlyBinaryStream(std::string(data, size), true) {}

ReadOnlyBinaryStream::ReadOnlyBinaryStream(const unsigned char* data, size_t size)
: ReadOnlyBinaryStream((const char*)data, size) {}

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
    if (bigEndian) { *target = detail::swapEndian(*target); }
    return true;
}

size_t ReadOnlyBinaryStream::getPosition() const { return mReadPointer; }

void ReadOnlyBinaryStream::setPosition(size_t value) { mReadPointer = value; }

void ReadOnlyBinaryStream::resetPosition() { setPosition(0); }

void ReadOnlyBinaryStream::ignoreBytes(size_t value) { mReadPointer += value; }

std::string ReadOnlyBinaryStream::getLeftBuffer() const { return std::string(mBufferView.substr(mReadPointer)); }

bool ReadOnlyBinaryStream::isOverflowed() const { return mHasOverflowed; }

bool ReadOnlyBinaryStream::hasDataLeft() const { return mReadPointer < mBufferView.size(); }

size_t ReadOnlyBinaryStream::size() const { return mBufferView.size(); }

std::string_view ReadOnlyBinaryStream::view() const { return mBufferView; }

std::string ReadOnlyBinaryStream::copyData() const { return std::string(mBufferView); }

bool ReadOnlyBinaryStream::operator==(ReadOnlyBinaryStream const& other) const {
    return mBufferView == other.mBufferView;
}

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

uint32_t ReadOnlyBinaryStream::getUnsignedInt24() {
    uint32_t value = 0;
    auto*    b     = reinterpret_cast<unsigned char*>(&value);
    for (int i = 0; i < 3; i++) read<>(b + i);
    return value;
}

void ReadOnlyBinaryStream::getRawBytes(std::string& rawBuffer, size_t length) {
    if (length > 0) {
        rawBuffer     = mBufferView.substr(mReadPointer, length);
        mReadPointer += length;
    }
}

std::string ReadOnlyBinaryStream::getRawBytes(size_t length) {
    std::string result;
    getRawBytes(result, length);
    return result;
}

} // namespace bedrock_protocol