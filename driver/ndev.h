#include "storage.h"

NTSTATUS map_rbuf(
    raw_dev_ext *dev_ext,           // driver iface
    PIRP irp                        // request struct
);

void unmap_rbuf(
    raw_dev_ext *dev_ext            // driver iface
);

void capture_frame(
    raw_dev_ext *dev_ext,           // driver iface
    PNET_BUFFER net_buf             // frame data container
);

NDIS_STATUS inject_frame(
    p_filter_context filt_ctx,      // NIC iface
    const byte_t *frame_buf,        // outgoing frame buffer
    size_t frame_size               // buffer size
);

