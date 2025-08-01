#pragma once
#include <algorithm>
#include <array>
#include <cstdint>
#include <string>
#include <type_traits>

namespace bedrock_protocol {

class BinaryStream;

class ReadOnlyBinaryStream {
    friend class BinaryStream;

protected:
    std::string      mOwnedBuffer;
    std::string_view mBufferView;
    size_t           mReadPointer;
    bool             mHasOverflowed;

private:
    template <typename T>
    bool read(T* target, bool bigEndian = false);

public:
    [[nodiscard]] explicit ReadOnlyBinaryStream(std::string_view buffer, bool copyBuffer = false);
    [[nodiscard]] explicit ReadOnlyBinaryStream(const char* data, size_t size);
    [[nodiscard]] explicit ReadOnlyBinaryStream(const unsigned char* data, size_t size);

    [[nodiscard]] size_t size() const;

    [[nodiscard]] size_t getPosition() const;

    void setPosition(size_t value);

    void resetPosition();

    void ignoreBytes(size_t length);

    [[nodiscard]] std::string getLeftBuffer() const;

    [[nodiscard]] bool isOverflowed() const;
    [[nodiscard]] bool hasDataLeft() const;

    [[nodiscard]] std::string_view view() const;

    [[nodiscard]] std::string copyData() const;

    [[nodiscard]] bool operator==(ReadOnlyBinaryStream const&) const;

    bool getBytes(void* target, size_t num);

    [[nodiscard]] uint8_t getByte();

    [[nodiscard]] uint8_t getUnsignedChar();

    [[nodiscard]] uint16_t getUnsignedShort();

    [[nodiscard]] uint32_t getUnsignedInt();

    [[nodiscard]] uint64_t getUnsignedInt64();

    [[nodiscard]] bool getBool();

    [[nodiscard]] double getDouble();

    [[nodiscard]] float getFloat();

    [[nodiscard]] int32_t getSignedInt();

    [[nodiscard]] int64_t getSignedInt64();

    [[nodiscard]] int16_t getSignedShort();

    [[nodiscard]] uint32_t getUnsignedVarInt();

    [[nodiscard]] uint64_t getUnsignedVarInt64();

    [[nodiscard]] int32_t getVarInt();

    [[nodiscard]] int64_t getVarInt64();

    [[nodiscard]] float getNormalizedFloat();

    [[nodiscard]] int32_t getSignedBigEndianInt();

    void getString(std::string& outString);

    [[nodiscard]] std::string getString();

    [[nodiscard]] uint32_t getUnsignedInt24();

    void getRawBytes(std::string& rawBuffer, size_t length);

    [[nodiscard]] std::string getRawBytes(size_t length);
};

namespace detail {
template <typename T>
    requires std::is_trivially_copyable_v<T>
T swapEndian(T u) noexcept {
    if constexpr (sizeof(T) == 1) {
        return u;
    } else {
        std::array<uint8_t, sizeof(T)> bytes;
        std::memcpy(bytes.data(), &u, sizeof(T));
        std::reverse(bytes.begin(), bytes.end());
        T result;
        std::memcpy(&result, bytes.data(), sizeof(T));
        return result;
    }
}
} // namespace detail

} // namespace bedrock_protocol
