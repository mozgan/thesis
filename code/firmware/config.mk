#
# $Id: config.mk,v 1.0 19.08.2013 15:23 mozgan Exp $
#

## ~ ~ ~ Header ~ ~ ~ ##
PROJECT		=	main
MCU		=	atmega16
F_CPU		=	16000000
BOARD		=	Frequenzmessung

## ~ ~ ~ AVRDUDE ~ ~ ~ ##
AVRDUDE_PROGRAMMER	=	jtagmkII
AVRDUDE_PORT		=	usb

## ~ ~ ~ AVR-OBJCOPY ~ ~ ~ ##
FORMAT		=	ihex

## ~ ~ ~ Directories ~ ~ ~ ##
PRJ_DIR		=	.

BOARD_DIR	=	$(PRJ_DIR)/board
DEVICE_DIR	=	$(PRJ_DIR)/device
DRIVER_DIR	=	$(PRJ_DIR)/driver
INCLUDE_DIR	=	$(PRJ_DIR)/include
LIB_DIR		=	$(PRJ_DIR)/lib

## ~ ~ ~ Drivers ~ ~ ~ ##
LEDS		=	$(DRIVER_DIR)/leds.c
TIMER0		=	$(DRIVER_DIR)/timer0.c
ICP		=	$(DRIVER_DIR)/icp.c
SPI		=	$(DRIVER_DIR)/spi.c
ETHERNET	=	$(DRIVER_DIR)/enc28j60.c
NET		=	$(DRIVER_DIR)/net.c

## ~ ~ ~ Sources ~ ~ ~ ##
SRC		=	$(PROJECT).c

ERROR		=	#$(LIB_DIR)/error.c
BUFFER		=	$(LIB_DIR)/buffer.c

DRIVER_SRC	=	$(LEDS) $(TIMER0) $(ICP) $(SPI) $(ETHERNET) $(NET)
LIBRARY		=	$(ERROR) $(BUFFER)
EXTRAINCDIRS	=	$(INCLUDE_DIR) $(DEVICE_DIR) $(BOARD_DIR) $(DRIVER_DIR) $(LIB_DIR)

