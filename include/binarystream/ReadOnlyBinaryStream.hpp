// Copyright © 2025 GlacieTeam.All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <array>
#include <bit>
#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>

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
    bool read(T* target, bool bigEndian = false) noexcept;

public:
    [[nodiscard]] explicit ReadOnlyBinaryStream(std::string_view buffer, bool copyBuffer = false);
    [[nodiscard]] explicit ReadOnlyBinaryStream(std::vector<uint8_t> const& buffer, bool copyBuffer = false);
    [[nodiscard]] explicit ReadOnlyBinaryStream(const char* data, size_t size, bool copyBuffer = false);
    [[nodiscard]] explicit ReadOnlyBinaryStream(const uint8_t* data, size_t size, bool copyBuffer = false);

    [[nodiscard]] size_t size() const noexcept;
    [[nodiscard]] size_t getPosition() const noexcept;

    void setPosition(size_t value) noexcept;
    void resetPosition() noexcept;
    void ignoreBytes(size_t length) noexcept;

    [[nodiscard]] std::string      getLeftBuffer() const;
    [[nodiscard]] bool             isOverflowed() const noexcept;
    [[nodiscard]] bool             hasDataLeft() const noexcept;
    [[nodiscard]] std::string_view view() const noexcept;
    [[nodiscard]] std::string      copyData() const;
    [[nodiscard]] bool             operator==(ReadOnlyBinaryStream const&) const noexcept;

    bool                    getBytes(void* target, size_t num) noexcept;
    [[nodiscard]] std::byte getByte() noexcept;
    [[nodiscard]] uint8_t   getUnsignedChar() noexcept;
    [[nodiscard]] uint16_t  getUnsignedShort() noexcept;
    [[nodiscard]] uint32_t  getUnsignedInt() noexcept;
    [[nodiscard]] uint64_t  getUnsignedInt64() noexcept;
    [[nodiscard]] bool      getBool() noexcept;
    [[nodiscard]] double    getDouble() noexcept;
    [[nodiscard]] float     getFloat() noexcept;
    [[nodiscard]] int32_t   getSignedInt() noexcept;
    [[nodiscard]] int64_t   getSignedInt64() noexcept;
    [[nodiscard]] int16_t   getSignedShort() noexcept;
    [[nodiscard]] uint32_t  getUnsignedVarInt() noexcept;
    [[nodiscard]] uint64_t  getUnsignedVarInt64() noexcept;
    [[nodiscard]] int32_t   getVarInt() noexcept;
    [[nodiscard]] int64_t   getVarInt64() noexcept;
    [[nodiscard]] float     getNormalizedFloat() noexcept;
    [[nodiscard]] int32_t   getSignedBigEndianInt() noexcept;
    [[nodiscard]] uint32_t  getUnsignedInt24() noexcept;

    void                      getString(std::string& outString);
    [[nodiscard]] std::string getString();
    void                      getRawBytes(std::string& rawBuffer, size_t length);
    [[nodiscard]] std::string getRawBytes(size_t length);
};

namespace detail {
template <typename T>
    requires std::is_trivially_copyable_v<T>
constexpr T swapEndian(T u) noexcept {
    if constexpr (sizeof(T) == 1) {
        return u;
    } else {
        auto bytes = std::bit_cast<std::array<std::byte, sizeof(T)>>(u);
        std::reverse(bytes.begin(), bytes.end());
        return std::bit_cast<T>(bytes);
    }
}
} // namespace detail

} // namespace bedrock_protocol