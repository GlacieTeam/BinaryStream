// Copyright © 2025 GlacieTeam. All rights reserved.
//
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
// distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void* read_only_binary_stream_create(const uint8_t* data, size_t size, bool copy_data);
void* read_only_binary_stream_create_empty();

void read_only_binary_stream_destroy(void* stream);

size_t read_only_binary_stream_size(void* stream);
size_t read_only_binary_stream_get_position(void* stream);

void read_only_binary_stream_set_position(void* stream, size_t position);
void read_only_binary_stream_reset_position(void* stream);

bool read_only_binary_stream_overflowed(void* stream);
bool read_only_binary_stream_has_data_left(void* stream);

void read_only_binary_stream_ignore_bytes(void* stream, size_t length);

size_t   read_only_binary_stream_get_bytes(void* stream, uint8_t* buffer, size_t buffer_size);
bool     read_only_binary_stream_get_bool(void* stream);
uint8_t  read_only_binary_stream_get_unsigned_char(void* stream);
uint16_t read_only_binary_stream_get_unsigned_short(void* stream);
int16_t  read_only_binary_stream_get_signed_short(void* stream);
uint32_t read_only_binary_stream_get_unsigned_int(void* stream);
int32_t  read_only_binary_stream_get_signed_int(void* stream);
uint64_t read_only_binary_stream_get_unsigned_int64(void* stream);
int64_t  read_only_binary_stream_get_signed_int64(void* stream);
float    read_only_binary_stream_get_float(void* stream);
double   read_only_binary_stream_get_double(void* stream);
uint32_t read_only_binary_stream_get_unsigned_varint(void* stream);
int32_t  read_only_binary_stream_get_varint(void* stream);
uint64_t read_only_binary_stream_get_unsigned_varint64(void* stream);
int64_t  read_only_binary_stream_get_varint64(void* stream);
int32_t  read_only_binary_stream_get_signed_big_endian_int(void* stream);

size_t read_only_binary_stream_get_string_size(void* stream);
void   read_only_binary_stream_get_string_data(void* stream, char* buffer, size_t buffer_size);

size_t read_only_binary_stream_get_raw_bytes(void* stream, uint8_t* buffer, size_t length);

#ifdef __cplusplus
}
#endif