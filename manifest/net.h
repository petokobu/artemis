#pragma once

#include "handle.h"

#define MAC_SIZE        6
#define IP_SIZE         4
#define MAC_STR_SIZE    18
#define IP_STR_SIZE     16

#define SML_PKT_SIZE    526
#define STD_PKT_SIZE    4096
#define LRG_PKT_SIZE    65535

#define IPV4_PROTO      0x0800
#define ARP_PROTO       0x0806
#define IPV6_PROTO      0x86DD

#define ICMP_PROTO      1
#define IGMP_PROTO      2
#define TCP_PROTO       6
#define UDP_PROTO       17

#pragma pack(push, 1)

typedef struct {
    byte_t   dst_mac[MAC_SIZE];
    byte_t   src_mac[MAC_SIZE];
    uint16_t type;
} eth_hdr_t;

typedef struct {
    uint16_t htype;
    uint16_t ptype;
    uint8_t  hlen;
    uint8_t  plen;
    uint16_t opcode;
    byte_t   src_mac[MAC_SIZE];
    byte_t   src_ip[IP_SIZE];
    byte_t   dst_mac[MAC_SIZE];
    byte_t   dst_ip[IP_SIZE];
} arp_hdr_t

typedef struct {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint8_t  ver        : 4;
    uint8_t  ihl        : 4;
#else
    uint8_t  ihl        : 4;
    uint8_t  ver        : 4;
#endif
    uint8_t  tos;
    uint16_t len;
    uint16_t id;
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint16_t frag_off   : 13;
    uint16_t more       : 1;
    uint16_t dont       : 1;
    uint16_t res        : 1;
#else
    uint16_t res        : 1;
    uint16_t dont       : 1;
    uint16_t more       : 1;
    uint16_t frag_off   : 13;
#endif
    uint8_t  ttl;
    uint8_t  proto;
    uint16_t checksum;
    uint32_t src_ip;
    uint32_t dst_ip;
} ipv4_hdr_t;

typedef struct {
/* TODO
 * define: unified IPv6 header
 * notes: follow header structure and use other structs as a blueprint
 */
} ipv6_hdr_t;

typedef struct {
    uint16_t src_port;
    uint16_t dst_port;
    uint32_t seq_n;
    uint32_t ack_n;
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    uint8_t  off        : 4;
    uint8_t  res        : 4;
    uint8_t  cwr        : 1;
    uint8_t  ece        : 1;
    uint8_t  urg        : 1;
    uint8_t  ack        : 1;
    uint8_t  psh        : 1;
    uint8_t  rst        : 1;
    uint8_t  syn        : 1;
    uint8_t  fin        : 1;
#else
    uint8_t  res        : 4;
    uint8_t  off        : 4;
    uint8_t  fin        : 1;
    uint8_t  syn        : 1;
    uint8_t  rst        : 1;
    uint8_t  psh        : 1;
    uint8_t  ack        : 1;
    uint8_t  urg        : 1;
    uint8_t  ece        : 1;
#endif
    uint16_t window;
    uint16_t checksum;
    uint16_t urg_ptr;
} tcp_hdr_t;

typedef struct {
    uint16_t src_port;
    uint16_t dst_port;
    uint16_t len;
    uint16_t checksum;
} udp_hdr_t;

typedef struct {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint16_t id;
    uint16_t seq_n;
} icmp_hdr_t;

typedef struct
/* TODO
 * define: unified IGMP header
 * notes: follow header structure and use other structs as a blueprint
 */
{
} igmp_hdr_t;

#pragma pack(pop)

size_t build_pkt(void *buf, eth_hdr_t *eth, void *l3,
                 void *l4, const byte_t *payld, size_t payld_size);

