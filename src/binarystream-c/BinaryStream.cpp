// Copyright © 2025 GlacieTeam. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "binarystream-c/BinaryStream.h"
#include "binarystream/BinaryStream.hpp"

namespace {

inline bedrock_protocol::BinaryStream* to_bs(void* handle) {
    return reinterpret_cast<bedrock_protocol::BinaryStream*>(handle);
}

} // namespace

extern "C" {

void* binary_stream_create() {
    try {
        return new bedrock_protocol::BinaryStream();
    } catch (...) { return nullptr; }
}

void* binary_stream_create_with_buffer(const uint8_t* data, size_t size, bool copy_data) {
    try {
        if (data) {
            std::string buffer(reinterpret_cast<const char*>(data), size);
            return new bedrock_protocol::BinaryStream(buffer, copy_data);
        } else {
            return binary_stream_create();
        }
    } catch (...) { return nullptr; }
}

void binary_stream_destroy(void* stream) {
    if (stream) { delete to_bs(stream); }
}

void binary_stream_write_bytes(void* stream, const uint8_t* data, size_t size) {
    if (stream && data && size > 0) { to_bs(stream)->writeBytes(data, size); }
}

void binary_stream_write_bool(void* stream, bool value) {
    if (stream) to_bs(stream)->writeBool(value);
}

void binary_stream_write_unsigned_char(void* stream, uint8_t value) {
    if (stream) to_bs(stream)->writeUnsignedChar(value);
}

void binary_stream_write_unsigned_short(void* stream, uint16_t value) {
    if (stream) to_bs(stream)->writeUnsignedShort(value);
}

void binary_stream_write_signed_short(void* stream, int16_t value) {
    if (stream) to_bs(stream)->writeSignedShort(value);
}

void binary_stream_write_unsigned_int24(void* stream, uint32_t value) {
    if (stream) to_bs(stream)->writeUnsignedInt24(value);
}

void binary_stream_write_unsigned_int(void* stream, uint32_t value) {
    if (stream) to_bs(stream)->writeUnsignedInt(value);
}

void binary_stream_write_unsigned_int64(void* stream, uint64_t value) {
    if (stream) to_bs(stream)->writeUnsignedInt64(value);
}

void binary_stream_write_signed_int(void* stream, int32_t value) {
    if (stream) to_bs(stream)->writeSignedInt(value);
}

void binary_stream_write_signed_int64(void* stream, int64_t value) {
    if (stream) to_bs(stream)->writeSignedInt64(value);
}

void binary_stream_write_float(void* stream, float value) {
    if (stream) to_bs(stream)->writeFloat(value);
}

void binary_stream_write_double(void* stream, double value) {
    if (stream) to_bs(stream)->writeDouble(value);
}

void binary_stream_write_unsigned_varint(void* stream, uint32_t value) {
    if (stream) to_bs(stream)->writeUnsignedVarInt(value);
}

void binary_stream_write_varint(void* stream, int32_t value) {
    if (stream) to_bs(stream)->writeVarInt(value);
}

void binary_stream_write_unsigned_varint64(void* stream, uint64_t value) {
    if (stream) to_bs(stream)->writeUnsignedVarInt64(value);
}

void binary_stream_write_varint64(void* stream, int64_t value) {
    if (stream) to_bs(stream)->writeVarInt64(value);
}

void binary_stream_write_string(void* stream, const char* str, size_t length) {
    if (stream && str && length > 0) { to_bs(stream)->writeString(std::string_view(str, length)); }
}

void binary_stream_write_signed_big_endian_int(void* stream, int32_t value) {
    if (stream) to_bs(stream)->writeSignedBigEndianInt(value);
}

void binary_stream_reset(void* stream) {
    if (stream) to_bs(stream)->reset();
}

stream_buffer binary_stream_get_buffer(void* stream) {
    if (stream) {
        auto  buf  = to_bs(stream)->data();
        char* data = new char[buf.size()];
        std::memcpy(data, buf.data(), buf.size());
        stream_buffer result;
        result.data = reinterpret_cast<uint8_t*>(data);
        result.size = buf.size();
        return result;
    }
    return stream_buffer();
}

} // extern "C"