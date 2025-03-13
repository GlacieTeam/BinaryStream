#pragma once
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
    explicit ReadOnlyBinaryStream();
    explicit ReadOnlyBinaryStream(std::string_view buffer, bool copyBuffer = false);

    size_t getPosition() const;

    std::string getLeftBuffer();

    bool isOverflowed();
    bool hasDataLeft();

    bool getBytes(void* target, size_t num);

    uint8_t getByte();

    uint8_t getUnsignedChar();

    uint16_t getUnsignedShort();

    uint32_t getUnsignedInt();

    uint64_t getUnsignedInt64();

    bool getBool();

    double getDouble();

    float getFloat();

    int32_t getSignedInt();

    int64_t getSignedInt64();

    int16_t getSignedShort();

    uint32_t getUnsignedVarInt();

    uint64_t getUnsignedVarInt64();

    int32_t getVarInt();

    int64_t getVarInt64();

    float getNormalizedFloat();

    int32_t getSignedBigEndianInt();

    void getString(std::string& outString);

    std::string getString();
};

} // namespace bedrock_protocol
