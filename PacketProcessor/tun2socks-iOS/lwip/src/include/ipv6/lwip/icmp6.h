/**
 * @file
 *
 * IPv6 version of ICMP, as per RFC 4443.
 */

/*
 * Copyright (c) 2010 Inico Technologies Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Ivan Delamer <delamer@inicotech.com>
 *
 *
 * Please coordinate changes and requests with Ivan Delamer
 * <delamer@inicotech.com>
 */
#ifndef __LWIP_ICMP6_H__
#define __LWIP_ICMP6_H__

#include "lwip/opt.h"
#include "lwip/pbuf.h"
#include "lwip/ip6_addr.h"
#include "lwip/netif.h"


#ifdef __cplusplus
extern "C" {
#endif

enum icmp6_type {
  ICMP6_TYPE_DUR = 1,  /* Destination unreachable */
  ICMP6_TYPE_PTB = 2,  /* Packet too big */
  ICMP6_TYPE_TE = 3,   /* Time exceeded */
  ICMP6_TYPE_PP = 4,   /* Parameter problem */
  ICMP6_TYPE_PE1 = 100,  /* Private experimentation */
  ICMP6_TYPE_PE2 = 101,  /* Private experimentation */
  ICMP6_TYPE_RSV_ERR = 127,  /* Reserved for expansion of error messages */

  ICMP6_TYPE_EREQ = 128,  /* Echo request */
  ICMP6_TYPE_EREP = 129,  /* Echo reply */
  ICMP6_TYPE_MLQ = 130,  /* Multicast listener query */
  ICMP6_TYPE_MLR = 131,  /* Multicast listener report */
  ICMP6_TYPE_MLD = 132,  /* Multicast listener done */
  ICMP6_TYPE_RS = 133,  /* Router solicitation */
  ICMP6_TYPE_RA = 134,  /* Router advertisement */
  ICMP6_TYPE_NS = 135,  /* Neighbor solicitation */
  ICMP6_TYPE_NA = 136,  /* Neighbor advertisement */
  ICMP6_TYPE_RD = 137,  /* Redirect */
  ICMP6_TYPE_MRA = 151,  /* Multicast router advertisement */
  ICMP6_TYPE_MRS = 152,  /* Multicast router solicitation */
  ICMP6_TYPE_MRT = 153,  /* Multicast router termination */
  ICMP6_TYPE_PE3 = 200,  /* Private experimentation */
  ICMP6_TYPE_PE4 = 201,  /* Private experimentation */
  ICMP6_TYPE_RSV_INF = 255  /* Reserved for expansion of informational messages */
};

enum icmp6_dur_code {
  ICMP6_DUR_NO_ROUTE = 0,     /* No route to destination */
  ICMP6_DUR_PROHIBITED = 1,   /* Communication with destination administratively prohibited */
  ICMP6_DUR_SCOPE = 2,        /* Beyond scope of source address */
  ICMP6_DUR_ADDRESS = 3,      /* Address unreachable */
  ICMP6_DUR_PORT = 4,         /* Port unreachable */
  ICMP6_DUR_POLICY = 5,       /* Source address failed ingress/egress policy */
  ICMP6_DUR_REJECT_ROUTE = 6  /* Reject route to destination */
};

enum icmp6_te_code {
  ICMP6_TE_HL = 0,   /* Hop limit exceeded in transit */
  ICMP6_TE_FRAG = 1  /* Fragment reassembly time exceeded */
};

enum icmp6_pp_code {
  ICMP6_PP_FIELD = 0,   /* Erroneous header field encountered */
  ICMP6_PP_HEADER = 1,  /* Unrecognized next header type encountered */
  ICMP6_PP_OPTION = 2   /* Unrecognized IPv6 option encountered */
};

/** This is the standard ICMP6 header. */
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
struct icmp6_hdr2 {
  PACK_STRUCT_FIELD(u8_t type);
  PACK_STRUCT_FIELD(u8_t code);
  PACK_STRUCT_FIELD(u16_t chksum);
  PACK_STRUCT_FIELD(u32_t data);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif

/** This is the ICMP6 header adapted for echo req/resp. */
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
struct icmp6_echo_hdr {
  PACK_STRUCT_FIELD(u8_t type);
  PACK_STRUCT_FIELD(u8_t code);
  PACK_STRUCT_FIELD(u16_t chksum);
  PACK_STRUCT_FIELD(u16_t id);
  PACK_STRUCT_FIELD(u16_t seqno);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/epstruct.h"
#endif


#if LWIP_ICMP6 && LWIP_IPV6 /* don't build if not configured for use in lwipopts.h */

void icmp6_input(struct pbuf *p, struct netif *inp);
void icmp6_dest_unreach(struct pbuf *p, enum icmp6_dur_code c);
void icmp6_packet_too_big(struct pbuf *p, u32_t mtu);
void icmp6_time_exceeded(struct pbuf *p, enum icmp6_te_code c);
void icmp6_param_problem(struct pbuf *p, enum icmp6_pp_code c, u32_t pointer);

#endif /* LWIP_ICMP6 && LWIP_IPV6 */


#ifdef __cplusplus
}
#endif


#endif /* __LWIP_ICMP6_H__ */
