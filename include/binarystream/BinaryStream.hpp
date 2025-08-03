#pragma once
#include <binarystream/ReadOnlyBinaryStream.hpp>

namespace bedrock_protocol {

class BinaryStream : public ReadOnlyBinaryStream {
protected:
    std::string& mBuffer;

private:
    template <typename T>
    void write(T value, bool bigEndian = false);

public:
    [[nodiscard]] explicit BinaryStream();
    [[nodiscard]] explicit BinaryStream(std::string& buffer, bool copyBuffer = false);

    [[nodiscard]] size_t size() const;

    void reserve(size_t size);

    void reset();

    [[nodiscard]] std::string& data();

    [[nodiscard]] const std::string& data() const;

    [[nodiscard]] std::string copyBuffer() const;

    [[nodiscard]] std::string getAndReleaseData();

    void writeBytes(const void* origin, size_t num);

    void writeByte(std::byte value);

    void writeUnsignedChar(uint8_t value);

    void writeUnsignedShort(uint16_t value);

    void writeUnsignedInt(uint32_t value);

    void writeUnsignedInt64(uint64_t value);

    void writeBool(bool value);

    void writeDouble(double value);

    void writeFloat(float value);

    void writeSignedInt(int32_t value);

    void writeSignedInt64(int64_t value);

    void writeSignedShort(int16_t value);

    void writeUnsignedVarInt(uint32_t uvalue);

    void writeUnsignedVarInt64(uint64_t uvalue);

    void writeVarInt(int32_t value);

    void writeVarInt64(int64_t value);

    void writeNormalizedFloat(float value);

    void writeSignedBigEndianInt(int32_t value);

    void writeString(std::string_view value);

    void writeUnsignedInt24(uint32_t value);

    void writeRawBytes(std::string_view rawBuffer);

    void writeStream(ReadOnlyBinaryStream const& stream);
};

} // namespace bedrock_protocol
