/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	spi.c
 * @brief	driver for spi interface
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	0.1
 * @date	20.08.2013 14:52:49
 * @internal
 *	$Compiler:	gcc (on Mac, and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) driver/spi.c	    TU Wien 20.08.2013
 *  $Id: spi.c,v 0.1 20.08.2013 14:52:49 mozgan Exp $
 */

#include <driver/spi.h>

/**
 * @brief initialize SPI communication
 */
void	    
spi_init(void)
{
	SPI_PORT |= (1 << SPI_SCK);

	SPI_DDR |= (1 << SPI_SCK);
	SPI_DDR &= ~(1 << SPI_MISO);
	SPI_DDR |= (1 << SPI_MOSI);
	SPI_DDR |= (1 << SPI_SS);

	SPI_CONTROL_REG |= (1 << SPI_MASTER);
	SPI_STATUS_REG |= (1 << SPI_DOUBLE_SPEED);
	SPI_CONTROL_REG |= (1 << SPI_ENABLE);
}

/**
 * @brief write an operation to address
 *
 * @param op operation 
 * @param addr address
 */
void
spi_write_op(uint8_t op, uint8_t addr)
{
	SPI_DATA_REG = op | (addr & ADDR_MASK);

	while (!(SPI_STATUS_REG & (1 << SPI_INT_FLAG)))
		;
}

/**
 * @brief write the data to SPI
 *
 * @param data data
 */
void
spi_write(uint8_t data)
{
	SPDR = data;

	while (!(SPI_STATUS_REG & (1 << SPI_INT_FLAG)))
		;
}

/**
 * @brief read from address
 *
 * @param addr address
 *
 * @return 
 */
uint8_t
spi_read_addr(uint8_t addr)
{
	if (addr & 0x80) {
		SPDR = 0x00;

		while (!(SPSR & (1 << SPIF)))
			;
	}

	return SPDR;
}

/**
 * @brief read from SPI data register
 *
 * @return value of SPI data register
 */
uint8_t
spi_read(void)
{
	SPDR = 0x00;

	while (!(SPSR & (1 << SPIF)))
		;

	return SPDR;
}

