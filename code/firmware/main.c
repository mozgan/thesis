/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	main.c
 * @brief	main program
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.5
 * @date	19.08.2013 15:20:15
 * @internal
 *	$Compiler:	gcc (on Mac, and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	51. signal has not readed!
 *  @todo	none
 */

/*
 *	@(#) main.c		TU Wien 19.08.2013
 *  $Id: main.c,v 0.5 19.08.2013 15:20:15 mozgan Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <avr/io.h>
#include <util/delay.h>

#include <include/common.h>
#include <board/freq.h>
#include <lib/buffer.h>

#include <driver/leds.h>
#include <device/enc28j60.h>
#include <driver/net.h>
#include <driver/icp.h>

#define	    BUF_SIZE	150

static uint8_t buf[BUF_SIZE];

uint8_t mymac[6] = {0xab,0xbc,0x6f,0x55,0x1c,0xc2};
uint8_t myip[4] = {192, 168, 0, 3};
uint16_t myport = 1200;

volatile uint16_t plen;

volatile uint16_t new, old;
volatile uint16_t diff;
volatile float freq;

volatile int snd = 0;

/**
* @brief return-function from input capture interrupt routine
*
* @param icr input capture timer state
*/
void
trigger(uint16_t icr)
{
	old = new;
	new = icr;

	if (new > old) {
		buffer_write((new - old));

		if (snd < LEN)
			snd++;
	}

	/* debug */
#ifdef DEBUG
	led_toggle(0);
#endif
}

/**
* @brief main function (program start)
*
* @return returns zero if SUCCESS, otherwise non-zero
*/
int
main(void)
{
	buffer_init();	    /* initialize the buffer ring */
	leds_init();	    /* leds for debuging */

	/* initialize the ENC28J60 device with the physical mac address */
	enc_init(mymac);    	
	_delay_ms(100);
	enc_init_phy();

	/* initialize the ip address for the given mac address */
	net_init(mymac, myip);

	/* initialize the input capture pin and the timer/counter1 for capturing */
	icp_init(trigger);

	/* enable the interrupt routine */
	sei();

	while (TRUE) {
		/* read a packet from ENC28J60 device */
		plen = enc_recv_packet(BUF_SIZE, buf);

		if (plen == 0)
			continue;
		
		if (eth_arp(buf, plen)) {
			arp_answer(buf, plen);
			continue;
		}

		if (eth_ip(buf, plen) == 0)
			continue;

		/* if there is a ping, then send a pong */
		if ((buf[IP_PROTO_P] == IP_PROTO_ICMP_V) &&
		     buf[ICMP_TYPE_P] == ICMP_REQUEST_V) {
			echo_reply(buf, plen);
			continue;
		}

		/*
		 * if received a UDP protocol, as we waiting it,
		 * then send the frequency from ring buffer
		 */
		if (buf[IP_PROTO_P] == IP_PROTO_UDP_V) {
			if (snd == LEN) {
				char str[12];
				static float diff;

				diff = buffer_medium();
				freq = (float)F_CPU / diff;
				freq /= 256;

				dtostrf((float)freq, 12, 3, str);

				udp_reply(buf, str, strlen(str), myport);
			}
		}
	}

	return 0;
}

