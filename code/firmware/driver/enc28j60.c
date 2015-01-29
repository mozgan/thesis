/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	enc28j60.c
 * @brief	ENC28J60 ethernet driver
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	1.0
 * @date	19.08.2013 18:51:18
 * @internal
 *	$Compiler:	gcc (on Mac, and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	'enc_send_packet' gives a warning with compiler option '-Woverflow'. You can devide as bytes the 16-bit registers.
 *  @todo	none
 */

/*
 *	@(#) driver/enc28j60.c	    TU Wien 19.08.2013
 *  $Id: enc28j60.c,v 1.0 19.08.2013 18:51:18 mozgan Exp $
 */

#include <board/freq.h>
#include <device/enc28j60.h>
#include <driver/spi.h>

uint8_t enc_bank;
unsigned int p_next;

/**
 * @brief start ENC28J60 pin to write or to read
 */
void
enc_start(void)
{
	ENC_CTRL_PORT &= ~(1 << ENC_CTRL_CS);
}

/**
 * @brief stop the ENC28J60 pin
 */
void
enc_stop(void)
{
	ENC_CTRL_PORT |= (1 << ENC_CTRL_CS);
}

/**
 * @brief set the mac-address to BANK3 register
 *
 * @param mymac[] my mac address
 */
void
enc_set_mac(uint8_t mymac[])
{
	enc_write(MAADR5, mymac[0]);
	enc_write(MAADR4, mymac[1]);
	enc_write(MAADR3, mymac[2]);
	enc_write(MAADR2, mymac[3]);
	enc_write(MAADR1, mymac[4]);
	enc_write(MAADR0, mymac[5]);
}

/**
 * @brief initialize the ENC28J60 
 *
 * @param mymac[] my mac address
 */
void 
enc_init(uint8_t mymac[])
{
	ENC_CTRL_DDR |= (1 << ENC_CTRL_CS);
	ENC_CTRL_PORT |= (1 << ENC_CTRL_CS);

	spi_init();

	enc_write_op(SOFT_RESET, 0, SOFT_RESET);
	_delay_ms(100);

	while (!(enc_read(ESTAT) & CLKRDY))
		;
	
	
	/* do bank 0 stuff */
	p_next = RX_START_INIT;
	enc_write(ERXSTL, RX_START_INIT & 0xFF);
	enc_write(ERXSTH, RX_START_INIT >> 8);

	enc_write(ERXRDPTL, RX_START_INIT & 0xFF);
	enc_write(ERXRDPTH, RX_START_INIT >> 8);

	enc_write(ERXNDL, RX_STOP_INIT & 0xFF);
	enc_write(ERXNDH, RX_STOP_INIT >> 8);

	enc_write(ETXSTL, TX_START_INIT & 0xFF);
	enc_write(ETXSTH, TX_START_INIT >> 8);

	enc_write(ETXNDL, TX_STOP_INIT & 0xFF);
	enc_write(ETXNDH, TX_STOP_INIT >> 8);

	/* do bank 1 stuff */
	enc_write(ERXFCON, (UCEN | CRCEN | PMEN));
	enc_write(EPMM0, 0x3F);
	enc_write(EPMM1, 0x30);
	enc_write(EPMCSL, 0xF9);
	enc_write(EPMCSH, 0xF7);

	/* do bank 2 stuff */
	enc_write(MACON1, (MARXEN | TXPAUS | RXPAUS));
	enc_write(MACON2, 0x00);

	enc_write_op(BIT_FIELD_SET, MACON3, (PADCFG0 | TXCRCEN | FRMLNEN));

	enc_write(MAIPGL, 0x12);
	enc_write(MAIPGH, 0x0C);

	enc_write(MABBIPG, 0x12);

	enc_write(MAMXFLL, MAX_FRAME_LEN & 0xFF);
	enc_write(MAMXFLH, MAX_FRAME_LEN >> 8);


	/* do bank 3 stuff */
	enc_set_mac(mymac);

	enc_write_phy(PHCON2, HDLDIS);

	enc_set_bank(ECON1);
	enc_write_op(BIT_FIELD_SET, EIE, (INTIE | PKTIE));
	enc_write_op(BIT_FIELD_SET, ECON1, E_RXEN);
}

/**
 * @brief write the operation 
 *
 * @param op operation to write on SPI
 * @param addr address to write
 * @param data data to send on SPI
 */
void
enc_write_op(uint8_t op, uint8_t addr, uint8_t data)
{
	enc_start();

	spi_write_op(op, addr);
	spi_write(data);
	
	enc_stop();
}

/**
 * @brief write on ENC28J60
 *
 * @param addr address to write
 * @param data data to send
 */
void
enc_write(uint8_t addr, uint8_t data)
{
	enc_set_bank(addr);
	enc_write_op(WRITE_CTRL_REG, addr, data);
}

/**
 * @brief set the bank on address
 *
 * @param addr address to set
 */
void
enc_set_bank(uint8_t addr)
{
	if ((addr & ADDR_MASK) != enc_bank) {
		enc_write_op(BIT_FIELD_CLR, ECON1, (BSEL1 | BSEL0));
		enc_write_op(BIT_FIELD_SET, ECON1, (addr & BANK_MASK) >> 5);
		enc_bank = (addr & BANK_MASK);
	}
}

/**
 * @brief write the data on ENC28J60 physical address
 *
 * @param addr address
 * @param data data
 */
void
enc_write_phy(uint8_t addr, uint16_t data)
{
	enc_write(MIREGADR, addr);

	enc_write(MIWRL, data);
	enc_write(MIWRH, data >> 8);

	while (enc_read(MISTAT) & BUSY)
		;
}

/**
 * @brief read from physical address of ENC28J60
 *
 * @param addr address
 *
 * @return data
 */
uint16_t
enc_read_phy(uint8_t addr)
{
	uint16_t data;

	enc_write(MIREGADR, addr);
	enc_write(MICMD, MIIRD);

	while (enc_read(MISTAT) & BUSY)
		;
	
	enc_write(MICMD, 0x00);

	data = enc_read(MIRDL);
	data |= enc_read(MIRDH);

	return data;
}

/**
 * @brief read from from address of ENC28J60
 *
 * @param addr address
 *
 * @return operation
 */
uint8_t
enc_read(uint8_t addr)
{
	enc_set_bank(addr);

	return enc_read_op(READ_CTRL_REG, addr);
}

/**
 * @brief read the operation from address of ENC28J60
 *
 * @param op operation
 * @param addr address
 *
 * @return data from SPI
 */
uint8_t
enc_read_op(uint8_t op, uint8_t addr)
{
	uint8_t data;

	enc_start();

	spi_write_op(op, addr);
	spi_write(0x00);
	data = spi_read_addr(addr);

	enc_stop();

	return data;
}

/**
 * @brief initialize the physical interface of ENC28J60
 */
void
enc_init_phy(void)
{
	enc_write_phy(PHLCON, 0x0880);
	_delay_ms(500);

	enc_write_phy(PHLCON, 0x0990);
	_delay_ms(500);

	enc_write_phy(PHLCON, 0x0880);
	_delay_ms(500);

	enc_write_phy(PHLCON, 0x0990);
	_delay_ms(500);

	enc_write_phy(PHLCON, 0x0476);
	_delay_ms(500);
}

/**
 * @brief read from the buffer 
 *
 * @param len length of data
 * @param data data to read
 */
void
enc_read_buf(uint16_t len, uint8_t *data)
{
	enc_start();

	spi_write(READ_BUF_MEM);

	while (len--)
		*data++ = spi_read();

	enc_stop();
}

/**
 * @brief write the buffer
 *
 * @param len length of data
 * @param data data
 */
void
enc_write_buf(uint16_t len, uint8_t *data)
{
	enc_start();

	spi_write(WRITE_BUF_MEM);

	while (len--)
		spi_write(*data++);
	
	enc_stop();
}

/**
 * @brief get the revision of ENC28J60
 *
 * @return revision
 */
uint8_t
enc_get_rev(void)
{
	return (enc_read(EREVID));
}

/**
 * @brief send a packet to ethernet
 *
 * @param len length of packet
 * @param packet packet to send
 */
void
enc_send_packet(uint16_t len, uint8_t *packet)
{
	enc_write(EWRPTL, TX_START_INIT);
	enc_write(EWRPTH, TX_START_INIT >> 8);

	enc_write(ETXNDL, (TX_START_INIT + len));
	enc_write(ETXNDH, (TX_START_INIT + len) >> 8);

	enc_write_op(WRITE_BUF_MEM, 0, 0x00);

	enc_write_buf(len, packet);

	enc_write_op(BIT_FIELD_SET, ECON1, TXRTS);
}

/**
 * @brief receive a packet from ethernet
 *
 * @param maxlen maximum length of packet to receive
 * @param packet packet to receive
 *
 * @return length of received packet
 */
uint16_t
enc_recv_packet(uint16_t maxlen, uint8_t *packet)
{
	unsigned int rxstat;
	unsigned int len;

	if (!enc_read(EPKTCNT))
		return 0;
	
	enc_write(ERDPTL, (p_next));
	enc_write(ERDPTH, (p_next) >> 8);

	p_next = enc_read_op(READ_BUF_MEM, 0);
	p_next |= (enc_read_op(READ_BUF_MEM, 0) << 8);

	len = enc_read_op(READ_BUF_MEM, 0);
	len |= (enc_read_op(READ_BUF_MEM, 0) << 8);

	rxstat = enc_read_op(READ_BUF_MEM, 0);
	rxstat |= (enc_read_op(READ_BUF_MEM, 0) << 8);

	len = MIN(len, maxlen);

	enc_read_buf(len, packet);

	enc_write(ERXRDPTL, (p_next));
	enc_write(ERXRDPTH, (p_next) >> 8);

	enc_write_op(BIT_FIELD_SET, ECON2, PKTDEC);

	return len;
}

