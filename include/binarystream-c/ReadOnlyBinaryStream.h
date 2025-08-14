// Copyright © 2025 GlacieTeam. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <stddef.h>
#include <stdint.h>

#ifdef BINARY_STREAM_EXPORT
#ifdef _WIN32
#define BINARY_STREAM_API __declspec(dllexport)
#else
#define BINARY_STREAM_API __attribute__((visibility("default"), used))
#endif
#else
#define BINARY_STREAM_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

BINARY_STREAM_API void* read_only_binary_stream_create(const uint8_t* data, size_t size, bool copy_data);
BINARY_STREAM_API void* read_only_binary_stream_create_empty();
BINARY_STREAM_API void  read_only_binary_stream_destroy(void* stream);

BINARY_STREAM_API size_t read_only_binary_stream_size(void* stream);
BINARY_STREAM_API size_t read_only_binary_stream_get_position(void* stream);
BINARY_STREAM_API void   read_only_binary_stream_set_position(void* stream, size_t position);
BINARY_STREAM_API void   read_only_binary_stream_reset_position(void* stream);
BINARY_STREAM_API bool   read_only_binary_stream_overflowed(void* stream);
BINARY_STREAM_API bool   read_only_binary_stream_has_data_left(void* stream);

BINARY_STREAM_API void read_only_binary_stream_ignore_bytes(void* stream, size_t length);

BINARY_STREAM_API size_t   read_only_binary_stream_get_bytes(void* stream, uint8_t* buffer, size_t buffer_size);
BINARY_STREAM_API bool     read_only_binary_stream_get_bool(void* stream);
BINARY_STREAM_API uint8_t  read_only_binary_stream_get_unsigned_char(void* stream);
BINARY_STREAM_API uint16_t read_only_binary_stream_get_unsigned_short(void* stream);
BINARY_STREAM_API int16_t  read_only_binary_stream_get_signed_short(void* stream);
BINARY_STREAM_API uint32_t read_only_binary_stream_get_unsigned_int24(void* stream);
BINARY_STREAM_API uint32_t read_only_binary_stream_get_unsigned_int(void* stream);
BINARY_STREAM_API int32_t  read_only_binary_stream_get_signed_int(void* stream);
BINARY_STREAM_API uint64_t read_only_binary_stream_get_unsigned_int64(void* stream);
BINARY_STREAM_API int64_t  read_only_binary_stream_get_signed_int64(void* stream);
BINARY_STREAM_API float    read_only_binary_stream_get_float(void* stream);
BINARY_STREAM_API double   read_only_binary_stream_get_double(void* stream);
BINARY_STREAM_API uint32_t read_only_binary_stream_get_unsigned_varint(void* stream);
BINARY_STREAM_API int32_t  read_only_binary_stream_get_varint(void* stream);
BINARY_STREAM_API uint64_t read_only_binary_stream_get_unsigned_varint64(void* stream);
BINARY_STREAM_API int64_t  read_only_binary_stream_get_varint64(void* stream);
BINARY_STREAM_API int32_t  read_only_binary_stream_get_signed_big_endian_int(void* stream);

BINARY_STREAM_API size_t read_only_binary_stream_get_string_size(void* stream);
BINARY_STREAM_API void   read_only_binary_stream_get_string_data(void* stream, char* buffer, size_t buffer_size);

BINARY_STREAM_API size_t read_only_binary_stream_get_raw_bytes(void* stream, uint8_t* buffer, size_t length);

#ifdef __cplusplus
}
#endif