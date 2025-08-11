// Copyright © 2025 GlacieTeam. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#include "binarystream-c/ReadOnlyBinaryStream.h"
#include "binarystream/BinaryStream.hpp"

namespace {

inline bedrock_protocol::ReadOnlyBinaryStream* to_robs(void* handle) {
    return reinterpret_cast<bedrock_protocol::ReadOnlyBinaryStream*>(handle);
}

} // namespace

extern "C" {

void* read_only_binary_stream_create(const uint8_t* data, size_t size, bool copy_data) {
    try {
        if (data && size > 0) {
            return new bedrock_protocol::ReadOnlyBinaryStream(reinterpret_cast<const char*>(data), size, copy_data);
        } else {
            return read_only_binary_stream_create_empty();
        }
    } catch (...) { return nullptr; }
}

void* read_only_binary_stream_create_empty() {
    try {
        return new bedrock_protocol::ReadOnlyBinaryStream(std::string_view{});
    } catch (...) { return nullptr; }
}

void read_only_binary_stream_destroy(void* stream) {
    if (stream) { delete to_robs(stream); }
}

size_t read_only_binary_stream_size(void* stream) {
    if (!stream) return 0;
    return to_robs(stream)->size();
}

size_t read_only_binary_stream_get_position(void* stream) {
    if (!stream) return 0;
    return to_robs(stream)->getPosition();
}

void read_only_binary_stream_set_position(void* stream, size_t position) {
    if (stream) to_robs(stream)->setPosition(position);
}

void read_only_binary_stream_reset_position(void* stream) {
    if (stream) to_robs(stream)->resetPosition();
}

void read_only_binary_stream_ignore_bytes(void* stream, size_t length) {
    if (stream) to_robs(stream)->ignoreBytes(length);
}

bool read_only_binary_stream_overflowed(void* stream) {
    if (!stream) return true;
    return to_robs(stream)->isOverflowed();
}

bool read_only_binary_stream_has_data_left(void* stream) {
    if (!stream) return false;
    return to_robs(stream)->hasDataLeft();
}

size_t read_only_binary_stream_get_bytes(void* stream, uint8_t* buffer, size_t buffer_size) {
    if (!stream || !buffer || buffer_size == 0) return 0;
    return to_robs(stream)->getBytes(buffer, buffer_size) ? buffer_size : 0;
}

bool read_only_binary_stream_get_bool(void* stream) {
    if (!stream) return false;
    return to_robs(stream)->getBool();
}

uint8_t read_only_binary_stream_get_unsigned_char(void* stream) {
    if (!stream) return 0;
    return to_robs(stream)->getUnsignedChar();
}

uint16_t read_only_binary_stream_get_unsigned_short(void* stream) {
    if (!stream) return 0;
    return to_robs(stream)->getUnsignedShort();
}

int16_t read_only_binary_stream_get_signed_short(void* stream) {
    if (!stream) return 0;
    return to_robs(stream)->getSignedShort();
}

uint32_t read_only_binary_stream_get_unsigned_int(void* stream) {
    if (!stream) return 0;
    return to_robs(stream)->getUnsignedInt();
}

int32_t read_only_binary_stream_get_signed_int(void* stream) {
    {
        if (!stream) return 0;
        return to_robs(stream)->getSignedInt();
    }
}

uint64_t read_only_binary_stream_get_unsigned_int64(void* stream) {
    if (!stream) return 0;
    return to_robs(stream)->getUnsignedInt64();
}

int64_t read_only_binary_stream_get_signed_int64(void* stream) {
    if (!stream) return 0;
    return to_robs(stream)->getSignedInt64();
}

float read_only_binary_stream_get_float(void* stream) {
    if (!stream) return 0.0f;
    return to_robs(stream)->getFloat();
}

double read_only_binary_stream_get_double(void* stream) {
    if (!stream) return 0.0;
    return to_robs(stream)->getDouble();
}

uint32_t read_only_binary_stream_get_unsigned_varint(void* stream) {
    if (!stream) return 0;
    return to_robs(stream)->getUnsignedVarInt();
}

int32_t read_only_binary_stream_get_varint(void* stream) {
    if (!stream) return 0;
    return to_robs(stream)->getVarInt();
}

uint64_t read_only_binary_stream_get_unsigned_varint64(void* stream) {
    if (!stream) return 0;
    return to_robs(stream)->getUnsignedVarInt();
}

int64_t read_only_binary_stream_get_varint64(void* stream) {
    if (!stream) return 0;
    return to_robs(stream)->getVarInt();
}

int32_t read_only_binary_stream_get_signed_big_endian_int(void* stream) {
    if (!stream) return 0;
    return to_robs(stream)->getSignedBigEndianInt();
}

size_t read_only_binary_stream_get_string_size(void* stream) {
    if (stream) { return to_robs(stream)->getUnsignedVarInt(); }
    return 0;
}

void read_only_binary_stream_get_string_data(void* stream, char* buffer, size_t buffer_size) {
    if (stream && buffer) { to_robs(stream)->getBytes(buffer, buffer_size); }
}

size_t read_only_binary_stream_get_raw_bytes(void* stream, uint8_t* buffer, size_t length) {
    if (!stream || !buffer || length == 0) return 0;
    return to_robs(stream)->getBytes(buffer, length) ? length : 0;
}

} // extern "C"
