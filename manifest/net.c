#include "net.h"

size_t build_pkt(void *buf, const eth_hdr_t *eth, const void *l3,
                 const void *l4, const byte_t *payld, size_t payld_size)
{
/* TODO
 * purpose: prepare a buffer to be sent as a frame, from headers and payload
 * operation: based on header types and protocols, convert to network -
 *      endianness, validate data (checksum) and copy to the correct position -
 *      into the buffer
 * outcome: frame buffer ready to be sent, returns the size of the frame
 * verification: on success, return the size of the frame
 *      else return 0
 * notes: focus on performance, as this will be called intensively
 *      use switch statements when parsing types and protocols
 */

    return 0;
}

