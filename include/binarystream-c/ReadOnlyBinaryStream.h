// Copyright © 2025 GlacieTeam. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <binarystream-c/Macros.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct stream_buffer {
    uint8_t* data;
    size_t   size;
};
BSAPI void stream_buffer_destroy(stream_buffer* buffer);

BSAPI void* read_only_binary_stream_create(const uint8_t* data, size_t size, bool copy_data);
BSAPI void* read_only_binary_stream_create_empty();
BSAPI void  read_only_binary_stream_destroy(void* stream);

BSAPI size_t read_only_binary_stream_size(void* stream);
BSAPI size_t read_only_binary_stream_get_position(void* stream);
BSAPI void   read_only_binary_stream_set_position(void* stream, size_t position);
BSAPI void   read_only_binary_stream_reset_position(void* stream);
BSAPI bool   read_only_binary_stream_overflowed(void* stream);
BSAPI bool   read_only_binary_stream_has_data_left(void* stream);

BSAPI stream_buffer read_only_binary_stream_get_left_buffer(void* stream);

BSAPI void read_only_binary_stream_ignore_bytes(void* stream, size_t length);

BSAPI size_t   read_only_binary_stream_get_bytes(void* stream, uint8_t* buffer, size_t buffer_size);
BSAPI bool     read_only_binary_stream_get_bool(void* stream);
BSAPI uint8_t  read_only_binary_stream_get_unsigned_char(void* stream);
BSAPI uint16_t read_only_binary_stream_get_unsigned_short(void* stream);
BSAPI int16_t  read_only_binary_stream_get_signed_short(void* stream);
BSAPI uint32_t read_only_binary_stream_get_unsigned_int24(void* stream);
BSAPI uint32_t read_only_binary_stream_get_unsigned_int(void* stream);
BSAPI int32_t  read_only_binary_stream_get_signed_int(void* stream);
BSAPI uint64_t read_only_binary_stream_get_unsigned_int64(void* stream);
BSAPI int64_t  read_only_binary_stream_get_signed_int64(void* stream);
BSAPI float    read_only_binary_stream_get_float(void* stream);
BSAPI double   read_only_binary_stream_get_double(void* stream);
BSAPI uint32_t read_only_binary_stream_get_unsigned_varint(void* stream);
BSAPI int32_t  read_only_binary_stream_get_varint(void* stream);
BSAPI uint64_t read_only_binary_stream_get_unsigned_varint64(void* stream);
BSAPI int64_t  read_only_binary_stream_get_varint64(void* stream);
BSAPI int32_t  read_only_binary_stream_get_signed_big_endian_int(void* stream);

BSAPI stream_buffer read_only_binary_stream_get_string(void* stream);

BSAPI size_t read_only_binary_stream_get_raw_bytes(void* stream, uint8_t* buffer, size_t length);

#ifdef __cplusplus
}
#endif