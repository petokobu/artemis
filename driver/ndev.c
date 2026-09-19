#include "ndev.h"

NTSTATUS map_rbuf(raw_dev_ext *dev_ext, PIRP irp)
{
/* TODO
 * purpose: maps kernel-allocated ring buffer into the address space of -
 *      a user-space application
 * operation: receives a pointer to the device extension and an i/o request -
 *      from a call, then associates it with dev_ext->rbuf_mdl
 * outcome: populates dev_ext->rbuf_user with valid user space memory address
 * verification: if dev_ext->rbuf_user is not null, return STATUS_SUCCESS
 */

    return STATUS_SUCCESS;
}

void unmap_rbuf(raw_dev_ext *dev_ext)
{
/* TODO
 * purpose: safely cleans up the user space memory mapping when the -
 *      application closes the file handle
 * operation: detaches dev_ext->rbuf_user and frees dev_ext->rbuf_mdl
 * outcome: safely releases the allocated space
 * verification: check if dev_ext->rbuf_user and dev_ext->rbuf_mdl are null
 */
}

void capture_frame(raw_dev_ext *dev_ext, PNET_BUFFER net_buf)
{
/* TODO
 * purpose: copies an incoming frame to the ring buffer
 * operation: extract raw bytes from net_buf to the ring buffer and -
 *      notifies the update via dev_ext->data_event
 * outcome: exposes raw frame to user space applications
 * verification: checks if tail incrementation is aligned and that data is -
 *      readable in user space
 */
}

NDIS_STATUS inject_frame(p_filter_context filt_ctx,
                         const byte_t *frame_buf, size_t frame_size)
{
/* TODO
 * purpose: transmits a raw frame via a NIC, bypassing Windows TCP/IP stack
 * operation: copies raw frame to an allocated NDIS NBL and issues a -
 *      notification using the NIC handle inside filt_ctx
 * outcome: sends a raw frame onto the physical network wire
 * verification: check if the function returned NDIS_STATUS_SUCCESS or -
 *      NDIS_STATUS_PENDING, confirming NDIS accepted the frame
 */

    return NDIS_STATUS_SUCCESS;
}

