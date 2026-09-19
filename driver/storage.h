#include "../manifest/handle.h"

#define RING_BUF_SIZE   (1024 * 1024)

typedef struct {
    alignas(64) volatile uint64_t head;
    alignas(64) volatile uint64_t tail;
    alignas(64) uint64_t          buf_mask;     // RING_BUF_SIZE - 1 on init
    byte_t                        buf[RING_BUF_SIZE];
} ring_buf;

typedef struct {
    PDEVICE_OBJECT dev_obj;     // ptr to control dev created by DriverEntry
    ring_buf      *rbuf_kernel;
    ring_buf      *rbuf_user;
    PMDL           rbuf_mdl;    // memory descriptor
    KEVENT         data_event;  // polling
} raw_dev_ext;

