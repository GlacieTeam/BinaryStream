// Copyright © 2025 GlacieTeam. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <binarystream-c/ReadOnlyBinaryStream.h>

#ifdef __cplusplus
extern "C" {
#endif

BINARY_STREAM_API void* binary_stream_create();
BINARY_STREAM_API void* binary_stream_create_with_buffer(const uint8_t* data, size_t size, bool copy_data);
BINARY_STREAM_API void  binary_stream_destroy(void* stream);
BINARY_STREAM_API void  binary_stream_reset(void* stream);

BINARY_STREAM_API void binary_stream_write_bytes(void* stream, const uint8_t* data, size_t size);
BINARY_STREAM_API void binary_stream_write_bool(void* stream, bool value);
BINARY_STREAM_API void binary_stream_write_unsigned_char(void* stream, uint8_t value);
BINARY_STREAM_API void binary_stream_write_unsigned_short(void* stream, uint16_t value);
BINARY_STREAM_API void binary_stream_write_signed_short(void* stream, int16_t value);
BINARY_STREAM_API void binary_stream_write_unsigned_int24(void* stream, uint32_t value);
BINARY_STREAM_API void binary_stream_write_unsigned_int(void* stream, uint32_t value);
BINARY_STREAM_API void binary_stream_write_signed_int(void* stream, int32_t value);
BINARY_STREAM_API void binary_stream_write_unsigned_int64(void* stream, uint64_t value);
BINARY_STREAM_API void binary_stream_write_signed_int64(void* stream, int64_t value);
BINARY_STREAM_API void binary_stream_write_float(void* stream, float value);
BINARY_STREAM_API void binary_stream_write_double(void* stream, double value);
BINARY_STREAM_API void binary_stream_write_unsigned_varint(void* stream, uint32_t value);
BINARY_STREAM_API void binary_stream_write_varint(void* stream, int32_t value);
BINARY_STREAM_API void binary_stream_write_unsigned_varint64(void* stream, uint64_t value);
BINARY_STREAM_API void binary_stream_write_varint64(void* stream, int64_t value);
BINARY_STREAM_API void binary_stream_write_string(void* stream, const char* str, size_t length);
BINARY_STREAM_API void binary_stream_write_signed_big_endian_int(void* stream, int32_t value);

BINARY_STREAM_API stream_buffer binary_stream_get_buffer(void* stream);

#ifdef __cplusplus
}
#endif