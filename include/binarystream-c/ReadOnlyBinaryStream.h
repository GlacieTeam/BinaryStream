#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void* read_only_binary_stream_create();

void read_only_binary_stream_destroy(void* stream);

#ifdef __cplusplus
}
#endif