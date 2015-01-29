/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	net.c
 * @brief	driver for network communication
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.2
 * @date	20.08.2013 13:29:36
 * @internal
 *	$Compiler:	gcc (on Mac, GNU/Linux, 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) driver/net.c	    TU Wien 20.08.2013
 *  $Id: net.c,v 0.2 20.08.2013 13:29:36 mozgan Exp $
 */

#include <board/freq.h>
#include <device/enc28j60.h>
#include <driver/net.h>

#include <driver/leds.h>

static uint8_t macaddr[6];
static uint8_t ipaddr[4];

/**
 * @brief initialize the network
 *
 * @param mymac my mac address
 * @param myip my ip address
 */
void
net_init(uint8_t *mymac, uint8_t *myip)
{
	uint8_t i = 0;
	while (i < 4) {
		ipaddr[i] = myip[i];
		i++;
	}

	i = 0;
	while (i < 6) {
		macaddr[i] = mymac[i];
		i++;
	}
}

/**
 * @brief make the network wirh arp
 *
 * @param buf buffer
 * @param len length of buffer
 *
 * @return return 1 if success, otherwise zero
 */
uint8_t	    
eth_arp(uint8_t *buf, uint8_t len)
{
	uint8_t i = 0;

	if (len < 41)
		return 0;

	if ((buf[ETH_TYPE_H_P] != ETHTYPE_ARP_H_V) || 
	    (buf[ETH_TYPE_L_P] != ETHTYPE_ARP_L_V))
		return 0;

	while (i < 4) {
		if (buf[ARP_DEST_IP_P + i] != ipaddr[i])
			return 0;

		i++;
	}
	
	return 1;
}

/**
 * @brief make the network communication with ip address
 *
 * @param buf buffer
 * @param len length of buffer
 *
 * @return returns 1 if success, otherwise zero
 */
uint8_t 
eth_ip(uint8_t *buf, uint8_t len)
{
	uint8_t i = 0;

	if (len < 42)
		return 0;

	if ((buf[ETH_TYPE_H_P] != ETHTYPE_IP_H_V) || 
	    (buf[ETH_TYPE_L_P] != ETHTYPE_IP_L_V))
		return 0;

	while (i < 4) {
		if (buf[IP_DEST_P + i] != ipaddr[i])
			return 0;

		i++;
	}
	
	return 1;
}

/**
 * @brief make an answer if request
 *
 * @param buf buffer
 * @param len length of buffer
 */
void
arp_answer(uint8_t *buf, uint8_t len)
{
	uint8_t i = 0;

	make_eth(buf);

	buf[ARP_OPCODE_H_P] = ARP_OPCODE_REPLY_H_V;
	buf[ARP_OPCODE_L_P] = ARP_OPCODE_REPLY_L_V;

	while (i < 6) {
		buf[ARP_DEST_MAC_P + i] = buf[ARP_SRC_MAC_P + i];
		buf[ARP_SRC_MAC_P + i] = macaddr[i];
		i++;
	}

	i = 0;
	while (i < 4) {
		buf[ARP_DEST_IP_P + i] = buf[ARP_SRC_IP_P + i];
		buf[ARP_SRC_IP_P + i] = ipaddr[i];
		i++;
	}

	/* eth + arp = 42 bytes */
	enc_send_packet(42, buf);
}

/**
 * @brief make an echo answer (ping - pong) if request
 *
 * @param buf buffer
 * @param len length of buffer
 */
void
echo_reply(uint8_t *buf, uint8_t len)
{
	make_eth(buf);
	make_ip(buf);

	buf[ICMP_TYPE_P] = ICMP_REPLY_V;

	if (buf[ICMP_CHECKSUM_P] > (0xFF - 0x08))
		buf[ICMP_CHECKSUM_P + 1]++;

	buf[ICMP_CHECKSUM_P] += 0x08;

	enc_send_packet(len, buf);
}

/**
 * @brief make the UDP protocol
 *
 * @param buf buffer
 * @param data data
 * @param len length 
 * @param port port number
 */
void	    
udp_reply(uint8_t *buf, char *data, uint8_t len, uint16_t port)
{
	uint16_t ck;
	uint8_t i = 0;

	make_eth(buf);

	if (len > 220)
		len = 220;

	buf[IP_TOTLEN_H_P] = 0;
	buf[IP_TOTLEN_L_P] = IP_HEADER_LEN + UDP_HEADER_LEN + len;
	make_ip(buf);

	buf[UDP_DEST_PORT_H_P] = buf[UDP_SRC_PORT_H_P];
	buf[UDP_DEST_PORT_L_P] = buf[UDP_SRC_PORT_L_P];
	buf[UDP_SRC_PORT_H_P] = port >> 8;
	buf[UDP_SRC_PORT_L_P] = port & 0xFF;

	buf[UDP_LEN_H_P] = 0;
	buf[UDP_LEN_L_P] = UDP_HEADER_LEN + len;

	buf[UDP_CHECKSUM_H_P] = 0;
	buf[UDP_CHECKSUM_L_P] = 0;

	while (i < len) {
		buf[UDP_DATA_P + i] = data[i];
		i++;
	}

	ck = checksum(&buf[IP_SRC_P], 16 + len, 1);
	buf[UDP_CHECKSUM_H_P] = ck >> 8;
	buf[UDP_CHECKSUM_L_P] = ck & 0xFF;
	
	enc_send_packet(UDP_HEADER_LEN + IP_HEADER_LEN + ETH_HEADER_LEN + len, buf);
}

/**
 * @brief make the ethernet header
 *
 * @param buf buffer
 */
void 
make_eth(uint8_t *buf)
{
	uint8_t i = 0;

	while (i < 6) {
		buf[ETH_DEST_MAC + i] = buf[ETH_SRC_MAC + i];
		buf[ETH_SRC_MAC + i] = macaddr[i];
		i++;
	}
}

/**
 * @brief make the ip header
 *
 * @param buf
 */
void
make_ip(uint8_t *buf)
{
	uint16_t ck;
	uint8_t i = 0;

	while (i < 4) {
		buf[IP_DEST_P + i] = buf[IP_SRC_P + i];
		buf[IP_SRC_P + i] = ipaddr[i];
		i++;
	}

	/* clear checksum */
	buf[IP_CHECKSUM_P] = 0;
	buf[IP_CHECKSUM_P + 1] = 0;

	buf[IP_FLAGS_P] = 0x40;	    /* don't fragment */
	buf[IP_FLAGS_P + 1] = 0;    /* fragment offset */
	buf[IP_TTL_P] = 64;	    /* TTL */

	/* calculate the checksum */
	ck = checksum(&buf[IP_P], IP_HEADER_LEN, 0);
	buf[IP_CHECKSUM_P] = ck >> 8;
	buf[IP_CHECKSUM_P + 1] = ck & 0xFF;
}

/**
 * @brief checksum
 *
 * @param buf buffer
 * @param len length
 * @param type type
 *
 * @return sum 
 */
uint16_t	    
checksum(uint8_t *buf, uint16_t len, uint8_t type)
{
	uint32_t sum = 0;

	/* Type = UDP */
	if (type == 1) {
		sum += IP_PROTO_UDP_V;
		sum += len - 8;
	}

	/* Type = TCP */
	if (type == 2) {
		sum += IP_PROTO_TCP_V;
		sum += len - 8;
	}

	/* build the sum of 16 bit words */
	while (len > 1) {
		sum += 0xFFFF & (*buf << 8 | *(buf + 1));
		buf += 2;
		len -= 2;
	}

	if (len)
		sum += (0xFF & *buf) << 8;

	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);

	return ((uint16_t) (sum ^ 0xFFFF));
}

