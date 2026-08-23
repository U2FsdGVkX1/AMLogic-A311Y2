/**
 ****************************************************************************************
 *
 * @file sha256_i.h
 *
 * @brief SHA256 definitions
 *
 * Copyright (C) Amlogic 2024-2034
 *
 ****************************************************************************************
 */

#ifndef SHA256_I_H
#define SHA256_I_H
#include "aml_defs.h"

#define SHA256_BLOCK_SIZE 64

struct sha256_state {
    u64 length;
    u32 state[8], curlen;
    u8 buf[SHA256_BLOCK_SIZE];
};

/* Macros for handling unaligned memory accesses */

static inline u16
WPA_GET_BE16(const u8 *a) {
    return (a[0] << 8) | a[1];
}

static inline void
WPA_PUT_BE16(u8 *a, u16 val) {
    a[0] = val >> 8;
    a[1] = val & 0xff;
}

static inline u16
WPA_GET_LE16(const u8 *a) {
    return (a[1] << 8) | a[0];
}

static inline void
WPA_PUT_LE16(u8 *a, u16 val) {
    a[1] = val >> 8;
    a[0] = val & 0xff;
}

static inline u32
WPA_GET_BE24(const u8 *a) {
    return (a[0] << 16) | (a[1] << 8) | a[2];
}

static inline void
WPA_PUT_BE24(u8 *a, u32 val) {
    a[0] = (val >> 16) & 0xff;
    a[1] = (val >> 8) & 0xff;
    a[2] = val & 0xff;
}

static inline u32
WPA_GET_BE32(const u8 *a) {
    return ((u32)a[0] << 24) | (a[1] << 16) | (a[2] << 8) | a[3];
}

static inline void
WPA_PUT_BE32(u8 *a, u32 val) {
    a[0] = (val >> 24) & 0xff;
    a[1] = (val >> 16) & 0xff;
    a[2] = (val >> 8) & 0xff;
    a[3] = val & 0xff;
}

static inline u32
WPA_GET_LE32(const u8 *a) {
    return ((u32)a[3] << 24) | (a[2] << 16) | (a[1] << 8) | a[0];
}

static inline void
WPA_PUT_LE32(u8 *a, u32 val) {
    a[3] = (val >> 24) & 0xff;
    a[2] = (val >> 16) & 0xff;
    a[1] = (val >> 8) & 0xff;
    a[0] = val & 0xff;
}

static inline u64
WPA_GET_BE64(const u8 *a) {
    return (((u64)a[0]) << 56) | (((u64)a[1]) << 48) | (((u64)a[2]) << 40) |
           (((u64)a[3]) << 32) | (((u64)a[4]) << 24) | (((u64)a[5]) << 16) |
           (((u64)a[6]) << 8) | ((u64)a[7]);
}

static inline void
WPA_PUT_BE64(u8 *a, u64 val) {
    a[0] = val >> 56;
    a[1] = val >> 48;
    a[2] = val >> 40;
    a[3] = val >> 32;
    a[4] = val >> 24;
    a[5] = val >> 16;
    a[6] = val >> 8;
    a[7] = val & 0xff;
}

static inline u64
WPA_GET_LE64(const u8 *a) {
    return (((u64)a[7]) << 56) | (((u64)a[6]) << 48) | (((u64)a[5]) << 40) |
           (((u64)a[4]) << 32) | (((u64)a[3]) << 24) | (((u64)a[2]) << 16) |
           (((u64)a[1]) << 8) | ((u64)a[0]);
}

static inline void
WPA_PUT_LE64(u8 *a, u64 val) {
    a[7] = val >> 56;
    a[6] = val >> 48;
    a[5] = val >> 40;
    a[4] = val >> 32;
    a[3] = val >> 24;
    a[2] = val >> 16;
    a[1] = val >> 8;
    a[0] = val & 0xff;
}

void sha256_init(struct sha256_state *md);
int sha256_process(struct sha256_state *md, const unsigned char *in, unsigned long inlen);
int sha256_done(struct sha256_state *md, unsigned char *out);

//void calculate_pmkid(u8 *key, u8 *IMAC, u8 *RMAC, u8 *serviceName, u8 *pmkid);

#endif /* SHA256_I_H */
