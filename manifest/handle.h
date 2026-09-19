#pragma once

#if __BYTE_ORDER__ != __ORDER_BIG_ENDIAN__ && __BYTE__ORDER__ != __ORDER_LITTLE_ENDIAN__
    #error "unkown byte order"
#endif

#ifdef DEBUG
    #define LOG(fmt, ...) printf("[DEBUG] " fmt, ##__VA_ARGS__)
#else
    #define LOG(fmt, ...)
#endif

typedef uint8_t byte_t;

int  warn(int retcode, const char *retmess, ...);
void fatal(const char *errmess, ...);
void dump(const byte_t *buf, size_t, nbytes);

