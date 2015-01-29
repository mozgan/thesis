/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	net.h
 * @brief	header file for network communication
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.2
 * @date	20.08.2013 13:27:19
 * @internal
 *	$Compiler:	gcc (on Mac, GNU/Linux and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) driver/net.h		TU Wien 20.08.2013
 *  $Id: net.h,v 0.2 20.08.2013 13:27:19 mozgan Exp $
 */

#ifndef __NET_H__
#define __NET_H__   1

/*
 * Ethernet Frame Formats (v2)
 * ---------------------------
 *
 * +----+----+------+------+-----+
 * | DA | SA | Type | Data | FCS |
 * +----+----+------+------+-----+
 *
 * Packet format:
 * +-----------------------------------------------------+
 * | Preamble | Dest. MAC | Src. MAC | Type | Data | FCS |
 * +-----------------------------------------------------+
 *
 * Preamble			   (8 bytes)
 * DA      Destination MAC Address (6 bytes)
 * SA      Source MAC Address      (6 bytes)
 * Type    Protocol Type           (2 bytes)
 * Data    Protocol Data           (46 - 1500 bytes)
 * FCS     Frame Checksum          (4 bytes)
 *
 * Header: 
 * IP (the Internet protocol)	: 0x0800
 * ARP				: 0x0806
 *
 * source: 
 * http://tools.ietf.org/id/draft-kaplan-isis-ext-eth-02.txt 
 * http://www.infocellar.com/networks/ethernet/frame.htm
 * http://wiki.wireshark.org/Ethernet
 */

/* ETH */
#define	    ETH_HEADER_LEN	14

#define	    ETHTYPE_ARP_H_V	0x08
#define	    ETHTYPE_ARP_L_V	0x06
#define	    ETHTYPE_IP_H_V	0x08
#define	    ETHTYPE_IP_L_V	0x00

/* Ethernet type field */
#define	    ETH_TYPE_H_P	12
#define	    ETH_TYPE_L_P	13

#define	    ETH_DEST_MAC	0
#define	    ETH_SRC_MAC		6

/* ARP */
#define	    ARP_OPCODE_REPLY_H_V    0x00
#define	    ARP_OPCODE_REPLY_L_V    0x02

#define	    ARP_L_V		0x06
#define	    ARP_DEST_IP_P	0x26

#define	    ARP_OPCODE_H_P	0x14
#define	    ARP_OPCODE_L_P	0x15

#define	    ARP_SRC_MAC_P	0x16
#define	    ARP_SRC_IP_P	0x1C
#define	    ARP_DEST_MAC_P	0x20
#define	    ARP_DEST_IP_P	0x26

/*
 * Internet Header Format (v4)
 * ---------------------------
 *     0                   1                   2                   3
 *     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |Version|  IHL  |Type of Service|          Total Length         |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |         Identification        |Flags|      Fragment Offset    |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |  Time to Live |    Protocol   |         Header Checksum       |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |                       Source Address                          |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |                    Destination Address                        |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     |                    Options                    |    Padding    |
 *     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *			(Example Internet Datagram Header)
 * 
 * IHL   -  Internet Header Length
 * TTL   -  Time To Live
 *
 * source:
 * http://tools.ietf.org/html/rfc791
 * http://tools.ietf.org/html/rfc760
 */
#define	    IP_HEADER_LEN	20

#define	    IP_SRC_P		0x1A
#define	    IP_DEST_P		0x1E
#define	    IP_CHECKSUM_P	0x18
#define	    IP_TTL_P		0x16
#define	    IP_FLAGS_P		0x14
#define	    IP_P		0x0E
#define	    IP_TOTLEN_H_P	0x10
#define	    IP_TOTLEN_L_P	0x11

#define	    IP_PROTO_P		0x17

#define	    IP_PROTO_ICMP_V	1
#define	    IP_PROTO_TCP_V	6
#define	    IP_PROTO_UDP_V	17

/*
 * Internet Control Message Protocol (ICMP)
 * ----------------------------------------
 *
 * Message Formats:
 *	Version: 4
 *	IHL: Internet header length in 32-bit words.
 *	Type of Service: 0
 *	Total Length: Length of internet header and data in octets.
 *	Identification, Flags, Fragment Offset: see http://tools.ietf.org/html/rfc791
 *	Time to Live (TTL): Time to live in seconds.
 *	Protocol: ICMP = 1
 *	Header Checksum: The 16 bit one's complement of the one's complement 
 *			 sum of all 16 bit words in the header.
 *	Source Address: The address of the gateway or host that composes the 
 *			ICMP message.
 *	Destination Address: The address of the gateway or host to which the 
 *			     message should be sent.
 *
 * source: 
 * http://tools.ietf.org/html/rfc792
 */
#define	    ICMP_REPLY_V	0
#define	    ICMP_REQUEST_V	8

#define	    ICMP_TYPE_P		0x22
#define	    ICMP_CHECKSUM_P	0x24

/*
 * User Datagram Protocol (UDP)
 * ----------------------------
 * 
 * Format:
 *		  0      7 8     15 16    23 24    31
 *		 +--------+--------+--------+--------+
 *		 |     Source      |   Destination   |
 *		 |      Port       |      Port       |
 *		 +--------+--------+--------+--------+
 *		 |                 |                 |
 *		 |     Length      |    Checksum     |
 *		 +--------+--------+--------+--------+
 *		 |
 *		 |          data octets ...
 *		 +---------------- ...
 *
 * Fields:
 *		  0      7 8     15 16    23 24    31
 *		 +--------+--------+--------+--------+
 *		 |          source address           |
 *		 +--------+--------+--------+--------+
 *		 |        destination address        |
 *		 +--------+--------+--------+--------+
 *		 |  zero  |protocol|   UDP length    |
 *		 +--------+--------+--------+--------+
 * 
 *
 */
#define	    UDP_HEADER_LEN	8

#define	    UDP_SRC_PORT_H_P	0x22
#define	    UDP_SRC_PORT_L_P	0x23
#define	    UDP_DEST_PORT_H_P	0x24
#define	    UDP_DEST_PORT_L_P	0x25

#define	    UDP_LEN_H_P		0x26
#define	    UDP_LEN_L_P		0x27
#define	    UDP_CHECKSUM_H_P	0x28
#define	    UDP_CHECKSUM_L_P	0x29
#define	    UDP_DATA_P		0x2A



extern void	    net_init(uint8_t *, uint8_t *);

extern uint8_t	    eth_arp(uint8_t *, uint8_t);
extern uint8_t	    eth_ip(uint8_t *, uint8_t);

extern void	    arp_answer(uint8_t *, uint8_t);
extern void	    echo_reply(uint8_t *, uint8_t);
extern void	    udp_reply(uint8_t *, char *, uint8_t, uint16_t);

extern void	    make_eth(uint8_t *);
extern void	    make_ip(uint8_t *);

extern uint16_t	    checksum(uint8_t *, uint16_t, uint8_t);

#endif /* __NET_H__ */

