/*-
 * Copyright (c) 2013, mozgan.
 * All Rights Reserved with BSD License.
 * Read LICENSE file.
 */

/**
 * @file	enc28j60.h
 * @brief	registers of ENC28J60 device
 *
 * @author	M. Ozgan, <mozgan@mozgan.org>
 * @version	1.0
 * @date	19.08.2013 15:23:13
 * @internal
 *	$Compiler:	gcc (on Mac, and 4.4BSD) $
 *	$Company:	TU Wien $
 *
 *  @bug	none
 *  @todo	none
 */

/*
 *	@(#) device/enc28j60.h		TU Wien 19.08.2013
 *  $Id: enc28j60.h,v 1.0 19.08.2013 15:23:13 mozgan Exp $
 */

#ifndef __ENC28J60_H__
#define __ENC28J60_H__	1

#include <board/freq.h>
#include <include/common.h>

#include <inttypes.h>

/*
 * ENC28J60 Control Registers
 *
 * Control registers are generically grouped as ETH, MAC and MII registers. 
 * Register names starting with 'E' belong "ETH" group. Similarly, registers names starting with 'MA' belong to the "MAC" group and registers prefixed with 'MI' belong to the "MII" group.
 *
 * - Register address	    (bits 0-4)
 * - Bank number	    (bits 5-6)
 * - MAC/PHY indicator	    (bit 7)
 */

#define	    ADDR_MASK	    0x1F
#define	    BANK_MASK	    0x60
#define	    SPRD_MASK	    0x80

/*
 * EIE: Ethernet Interrupt Enable Register - Address: 0x1B
 *
 * +---------------------------------------------------------------+
 * | INTIE | PKTIE | DMAIE | LINKIE | TXIE |  r  | TXERIE | RXERIE |
 * +---------------------------------------------------------------+
 */
#define	    EIE		    0x1B

#define	    INTIE	    0x80
#define	    PKTIE	    0x40
#define	    DMAIE	    0x20
#define	    LINKIE	    0x10
#define	    TXIE	    0x08
#define	    EIE_WOLIE	    0x04
#define	    TXERIE	    0x02
#define	    RXERIE	    0x01

/*
 * EIR: Ethernet Interrupt Request (Flag) Register - Address: 0x1C
 *
 * +-------------------------------------------------------------+
 * |  -  | PKTIF | DMAIF | LINKIF | TXIF |  r  | TXERIF | RXERIF |
 * +-------------------------------------------------------------+
 */
#define	    EIR		    0x1C

#define	    PKTIF	    0x40
#define	    DMAIF	    0x20
#define	    LINKIF	    0x10
#define	    TXIF	    0x08
#define	    EIR_WOLIF	    0x04
#define	    TXERIF	    0x02
#define	    RXERIF	    0x01

/*
 * ESTAT: Ethernet Status Register - Address: 0x1D
 *
 * +--------------------------------------------------------------+
 * | INT | BUFER |  r  | LATECOL |  -  | RXBUSY | TXABRT | CLKRDY |
 * +--------------------------------------------------------------+
 */
#define	    ESTAT	    0x1D

#define	    INT		    0x80
#define	    BUFER	    0x40
#define	    ESTAT_R	    0x20
#define	    LATECOL	    0x10
#define	    RXBUSY	    0x04
#define	    TXABRT	    0x02
#define	    CLKRDY	    0x01

/*
 * ECON2: Ethernet Control Register 2 - Address: 0x1E
 *
 * +---------------------------------------------------------+
 * | AUTOINC | PKTDEC | PWRSV |  r  | VRPS |  -  |  -  |  -  |
 * +---------------------------------------------------------+
 */
#define	    ECON2	    0x1E

#define	    AUTOINC	    0x80
#define	    PKTDEC	    0x40
#define	    PWRSV	    0x20
#define	    ECON2_R	    0x10
#define	    VRPF	    0x08

/*
 * ECON1: Ethernet Control Register 1 - Address: 0x1F
 *
 * +---------------------------------------------------------------+
 * | TXRST | RXRST | DMAST | CSUMEN | TXRTS | RXEN | BSEL1 | BSEL0 | 
 * +---------------------------------------------------------------+
 */
#define	    ECON1	    0x1F

#define	    TXRST	    0x80
#define	    RXRST	    0x40
#define	    DMAST	    0x20
#define	    CSUMEN	    0x10
#define	    TXRTS	    0x08
#define	    E_RXEN	    0x04
#define	    BSEL1	    0x02
#define	    BSEL0	    0x01



/* Bank 0 Registers */
#define	    BANK0	    (0x00)

#define	    ERDPTL	    (0x00 | BANK0)
#define	    ERDPTH          (0x01 | BANK0)
#define	    EWRPTL          (0x02 | BANK0)
#define	    EWRPTH          (0x03 | BANK0)
#define	    ETXSTL          (0x04 | BANK0)
#define	    ETXSTH          (0x05 | BANK0)
#define	    ETXNDL          (0x06 | BANK0)
#define	    ETXNDH          (0x07 | BANK0)
#define	    ERXSTL          (0x08 | BANK0)
#define	    ERXSTH          (0x09 | BANK0)
#define	    ERXNDL          (0x0A | BANK0)
#define	    ERXNDH          (0x0B | BANK0)
#define	    ERXRDPTL        (0x0C | BANK0)
#define	    ERXRDPTH        (0x0D | BANK0)
#define	    ERXWRPTL        (0x0E | BANK0)
#define	    ERXWRPTH        (0x0F | BANK0)
#define	    EDMASTL         (0x10 | BANK0)
#define	    EDMASTH         (0x11 | BANK0)
#define	    EDMANDL         (0x12 | BANK0)
#define	    EDMANDH         (0x13 | BANK0)
#define	    EDMADSTL        (0x14 | BANK0)
#define	    EDMADSTH        (0x15 | BANK0)
#define	    EDMACSL         (0x16 | BANK0)
#define	    EDMACSH         (0x17 | BANK0)



/* Bank 1 Registers */
#define	    BANK1	    (0x20)

#define	    EHT0            (0x00 | BANK1)
#define	    EHT1            (0x01 | BANK1)
#define	    EHT2            (0x02 | BANK1)
#define	    EHT3            (0x03 | BANK1)
#define	    EHT4            (0x04 | BANK1)
#define	    EHT5            (0x05 | BANK1)
#define	    EHT6            (0x06 | BANK1)
#define	    EHT7            (0x07 | BANK1)
#define	    EPMM0           (0x08 | BANK1)
#define	    EPMM1           (0x09 | BANK1)
#define	    EPMM2           (0x0A | BANK1)
#define	    EPMM3           (0x0B | BANK1)
#define	    EPMM4           (0x0C | BANK1)
#define	    EPMM5           (0x0D | BANK1)
#define	    EPMM6           (0x0E | BANK1)
#define	    EPMM7           (0x0F | BANK1)
#define	    EPMCSL          (0x10 | BANK1)
#define	    EPMCSH          (0x11 | BANK1)
#define	    EPMOL           (0x14 | BANK1)
#define	    EPMOH           (0x15 | BANK1)
#define	    EWOLIE          (0x16 | BANK1)
#define	    EWOLIR          (0x17 | BANK1)
#define	    ERXFCON	    (0x18 | BANK1)
#define	    EPKTCNT         (0x19 | BANK1)



/* Bank 2 Registers */
#define	    BANK2	    (0x40)

#define	    MACON1	    (0x00 | BANK2 | 0x80)
#define	    MACON2          (0x01 | BANK2 | 0x80)
#define	    MACON3          (0x02 | BANK2 | 0x80)
#define	    MACON4          (0x03 | BANK2 | 0x80)
#define	    MABBIPG         (0x04 | BANK2 | 0x80)
#define	    MAIPGL          (0x06 | BANK2 | 0x80)
#define	    MAIPGH          (0x07 | BANK2 | 0x80)
#define	    MACLCON1	    (0x08 | BANK2 | 0x80)
#define	    MACLCON2        (0x09 | BANK2 | 0x80)
#define	    MAMXFLL         (0x0A | BANK2 | 0x80)
#define	    MAMXFLH         (0x0B | BANK2 | 0x80)
#define	    MAPHSUP         (0x0D | BANK2 | 0x80)
#define	    MICON           (0x11 | BANK2 | 0x80)
#define	    MICMD           (0x12 | BANK2 | 0x80)
#define	    MIREGADR	    (0x14 | BANK2 | 0x80)
#define	    MIWRL           (0x16 | BANK2 | 0x80)
#define	    MIWRH           (0x17 | BANK2 | 0x80)
#define	    MIRDL           (0x18 | BANK2 | 0x80)
#define	    MIRDH           (0x19 | BANK2 | 0x80)


/* Bank 3 Registers */
#define	    BANK3	    (0x60)

#define	    MAADR1          (0x00 | BANK3 | 0x80)
#define	    MAADR0          (0x01 | BANK3 | 0x80)
#define	    MAADR3          (0x02 | BANK3 | 0x80)
#define	    MAADR2          (0x03 | BANK3 | 0x80)
#define	    MAADR5          (0x04 | BANK3 | 0x80)
#define	    MAADR4          (0x05 | BANK3 | 0x80)
#define	    EBSTSD          (0x06 | BANK3)
#define	    EBSTCON         (0x07 | BANK3)
#define	    EBSTCSL         (0x08 | BANK3)
#define	    EBSTCSH         (0x09 | BANK3)
#define	    MISTAT          (0x0A | BANK3 | 0x80)
#define	    EREVID          (0x12 | BANK3)
#define	    ECOCON          (0x15 | BANK3)
#define	    EFLOCON         (0x17 | BANK3)
#define	    EPAUSL          (0x18 | BANK3)
#define	    EPAUSH          (0x19 | BANK3)


/*
 * ENC28J60 PHY Registers
 */

/*
 * PHCON1: PHY Control Register 1
 *
 * +-----------------------------------------------------------+
 * | PRST | PLOOPBK |  -  |  -  |  PPWRSV |  r  |  -  | PDPXMD | bit 8
 * +-----------------------------------------------------------+
 * |   r  |    -    |  -  |  -  |    -    |  -  |  -  |    -   | bit 0
 * +-----------------------------------------------------------+
 */
#define	    PHCON1	    0x00

#define	    PRST	    0x8000
#define	    PLOOPBK	    0x4000
#define	    PPWRSV	    0x0800
#define	    PDPXMD	    0x0100

/*
 * PHSTAT1: Physical Layer Status Register 1
 *
 * +---------------------------------------------------------+
 * |  -  |  -  |  -  | PFDPX | PHDPX |   --   |   --   |  -  | bit 8
 * +---------------------------------------------------------+
 * |  -  |  -  |  -  |   -   |   -   | LLSTAT | JBSTAT |  -  | bit 0
 * +---------------------------------------------------------+
 */
#define	    PHSTAT1	    0x01

#define	    PFDPX	    0x1000
#define	    PHDPX	    0x0800
#define	    LLSTAT	    0x0004
#define	    JBSTAT	    0x0002

/* PHHID1: PHY Identifier 1 */
#define	    PHHID1	    0x02

/* PHHID1: PHY Identifier 2 */
#define	    PHHID2	    0x03

/*
 * PHCON2: PHY Control Register 2
 *
 * +----------------------------------------------------------+
 * |  -  | FRCLNK | TXDIS |  r  |  r  | JABBER |  r  | HDLDIS | bit 8
 * +----------------------------------------------------------+
 * |  r  |    r   |   r   |  r  |  r  |    r   |  r  |    r   | bit 0
 * +----------------------------------------------------------+
 */
#define	    PHCON2	    0x10

#define	    FRCLNK	    0x4000
#define	    TXDIS	    0x2000
#define	    JABBER	    0x0400
#define	    HDLDIS	    0x0100

/*
 * PHSTAT2: Physical Layer Status Register 2
 *
 * +---------------------------------------------------------------+
 * |  -  |  -  | TXSTAT | RXSTAT | COLSTAT | LSTAT | DPXSTAT |  -  | bit 8
 * +---------------------------------------------------------------+
 * |  -  |  -  | PLRITY |   --   |   ---   |   -   |    -    |  -  |bit 0
 * +---------------------------------------------------------------+
 */
#define	    PHSTAT2	    0x11

#define	    TXSTAT	    0x2000
#define	    RXSTAT	    0x1000
#define	    COLSTAT	    0x0800
#define	    LSTAT	    0x0400
#define	    DPXSTAT	    0x0200
#define	    PLRITY	    0x0020

/*
 * PHIE: PHY Interrupt Enable Register
 *
 * +----------------------------------------------------+
 * |  r  |  r  |  r  |    r   |  r  |  r  |   r   |  r  | bit 8
 * +----------------------------------------------------+
 * |  r  |  r  |  r  | PLNKIE |  r  |  r  | PGEIE |  r  | bit 0
 * +----------------------------------------------------+
 */
#define	    PHIE	    0x12

#define	    PLNKIE	    0x0010
#define	    PGEIE	    0x0002

/*
 * PHIR: PHY Interrupt Request (Flag) Regiter
 *
 * +---------------------------------------------------+
 * |  r  |  r  |  r  |    r   |  r  |   r  |  r  |  r  | bit 8
 * +---------------------------------------------------+
 * |  r  |  r  |  r  | PLNKIF |  r  | PGIF |  r  |  r  | bit 0
 * +---------------------------------------------------+
 */
#define	    PHIR	    0x13

#define	    PLNKIF	    0x0010
#define	    PGIF	    0x0004

/*
 * PHLCON: PHY Module Led Control Register
 *
 * +-----------------------------------------------------------------------+
 * |    r   |    r   |    r   |    r   | LACFG3 | LACFG2 | LACFG1 | LACFG0 | bit 8
 * +-----------------------------------------------------------------------+
 * | LBCFG3 | LBCFG2 | LBCFG1 | LBCFG0 | LFRQ1  | LFRQ0  | STRCH  |    r   | bit 0
 * +-----------------------------------------------------------------------+
 */
#define	    PHLCON	    0x14

#define	    LACFG3	    0x0800
#define	    LACFG2	    0x0400
#define	    LACFG1	    0x0200
#define	    LACFG0	    0x0100
#define	    LBCFG3	    0x0080
#define	    LBCFG2	    0x0040
#define	    LBCFG1	    0x0020
#define	    LBCFG0	    0x0010
#define	    LFRQ1	    0x0008
#define	    LFRQ0	    0x0004
#define	    STRCH	    0x0002

/*
 * ERXFCON: Ethernet Receive Filter Control Register
 *
 * +---------------------------------------------------------+
 * | UCEN | ANDOR | CRCEN | PMEN | MPEN | HTEN | MCEN | BCEN |
 * +---------------------------------------------------------+
 */
/*#define	    ERXFCON	    (0x18 | BANK1)   */
#define	    UCEN	    0x80
#define	    ANDOR	    0x40
#define	    CRCEN	    0x20
#define	    PMEN	    0x10
#define	    MPEN	    0x08
#define	    HTEN	    0x04
#define	    MCEN	    0x02
#define	    BCEN	    0x01

/*
 * MACON1: MAC Control Register 1
 *
 * +-----------------------------------------------------------------+
 * |  -  |  -  |  -  |  LOOPBK  | TXPAUS | RXPAUS | PASSALL | MARXEN |
 * +-----------------------------------------------------------------+
 */
/*#define	    MACON1	    (0x00 | BANK2 | 0x80)    */
#define	    LOOPBK	    0x10
#define	    TXPAUS	    0x08
#define	    RXPAUS	    0x04
#define	    PASSALL	    0x02
#define	    MARXEN	    0x01

/*
 * MACON2: MAC Control Register 2
 *
 * +--------------------------------------------------------------------+
 * | MARST | RNDRST |  -  |  -  | MARXRST | RFUNRST | MATXRST | TFUNRST |
 * +--------------------------------------------------------------------+
 */
/*#define	    MACON2	    (0x01 | BANK2 | 0x80)    */
#define	    MARST	    0x80
#define	    RNDRST	    0x40
#define	    MARXRST	    0x08
#define	    RFUNRST	    0x04
#define	    MATXRST	    0x02
#define	    TFUNRST	    0x01

/*
 * MACON3: MAC Control Register 3
 *
 * +----------------------------------------------------------------------------+
 * | PADCFG2 | PADCFG1 | PADCFG0 | TXCRCEN | PHDREN | HFRMEN | FRMLNEN | FULDPX |
 * +----------------------------------------------------------------------------+
 */
/*#define	    MACON3	    (0x02 | BANK2 | 0x80)    */
#define	    PADCFG2	    0x80
#define	    PADCFG1	    0x40
#define	    PADCFG0	    0x20
#define	    TXCRCEN	    0x10
#define	    PHDREN	    0x08
#define	    HFRMEN	    0x04
#define	    FRMLNEN	    0x02
#define	    FULDPX	    0x01

/*
 * MICMD: MII Command Register
 *
 * +-----------------------------------------------------+
 * |  -  |  -  |  -  |  -  |  -  |  -  | MIISCAN | MIIRD |
 * +-----------------------------------------------------+
 */
/*#define	    MICMD	    (0x12 | 0x80 | 0x80)    */
#define	    MIISCAN	    0x02
#define	    MIIRD	    0x01

/*
 * MISTAT: MII Status Register
 *
 * +----------------------------------------------------+
 * |  -  |  -  |  -  |  -  |  r  | NVALID | SCAN | BUSY |
 * +----------------------------------------------------+
 */
/*#define	    MISTAT	    (0x0A | 0x60 | 0x80)    */
#define	    NVALID	    0x04
#define	    SCAN	    0x02
#define	    BUSY	    0x01 

/*
 * Packet Control Bytes
 *
 * +---------------------------------------------------------------+
 * |  -  |  -  |  -  |  -  | PHUGEEN | PPADEN | PCRCEN | POVERRIDE |
 * +---------------------------------------------------------------+
 */
#define	    PHUGEEN	    0x08
#define	    PPADEN	    0x04
#define	    PCRCEN	    0x02
#define	    POVERRIDE	    0x01



/* SPI Operation Codes */
#define	    READ_CTRL_REG   0x00
#define	    READ_BUF_MEM    0x3A
#define	    WRITE_CTRL_REG  0x40
#define	    WRITE_BUF_MEM   0x7A
#define	    BIT_FIELD_SET   0x80
#define	    BIT_FIELD_CLR   0xA0
#define	    SOFT_RESET	    0xFF

#define	    RX_START_INIT   0x00
#define	    RX_STOP_INIT    (0x1FFF - 0x0600 - 1)
#define	    TX_START_INIT   (0x1FFF - 0x0600)
#define	    TX_STOP_INIT    0x1FFF

#define	    MAX_FRAME_LEN   1500


extern void	    enc_start(void);
extern void	    enc_stop(void);

extern void	    enc_init(uint8_t *);
extern void	    enc_write_op(uint8_t, uint8_t, uint8_t);
extern void	    enc_write(uint8_t, uint8_t);
extern void	    enc_set_bank(uint8_t);
extern void	    enc_write_phy(uint8_t, uint16_t);
extern uint16_t	    enc_read_phy(uint8_t);
extern uint8_t	    enc_read(uint8_t);
extern uint8_t	    enc_read_op(uint8_t, uint8_t);
extern void	    enc_init_phy(void);
extern void			enc_set_mac(uint8_t *);

extern void	    enc_read_buf(uint16_t, uint8_t *);
extern void	    enc_write_buf(uint16_t, uint8_t *);
extern uint8_t	    enc_get_rev(void);
extern void	    enc_send_packet(uint16_t, uint8_t *);
extern uint16_t	    enc_recv_packet(uint16_t, uint8_t *);



#endif /* __ENC28J60_H__ */

