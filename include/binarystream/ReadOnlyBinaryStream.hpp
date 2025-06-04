#pragma once
#include <cstdint>
#include <iostream>

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

    [[nodiscard]] size_t size() const;

    [[nodiscard]] size_t getPosition() const;

    void setPosition(size_t value);

    void ignoreBytes(size_t length);

    [[nodiscard]] std::string getLeftBuffer() const;

    [[nodiscard]] bool isOverflowed() const;
    [[nodiscard]] bool hasDataLeft() const;

    [[nodiscard]] std::string_view view() const;

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

} // namespace bedrock_protocol
