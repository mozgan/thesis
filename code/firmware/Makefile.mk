#
# $Id: Makefile.mk,v 1.0 19.08.2013 15:23 mozgan Exp $
#

TARGET	=	$(PROJECT)

## Optimisation
OPT	=	s

## DEBUG
DEBUG	=	dwarf-2
DEBUG	+=	-DDEBUG

## Compiler C Standard
CSTD	=	-std=gnu99

## AVR-GCC Flags
DEPFLAGS=	-MD -MP -MF .dep/${@F}.d

CFLAGS	=	-g$(DEBUG)
CFLAGS	+=	-O$(OPT)
CFLAGS	+=	-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS	+=	-Wall -Wstrict-prototypes
CFLAGS	+=	-Wa,-adhlns=$(<:.c=.lst)
CFLAGS	+=	$(patsubst %,-I%,$(EXTRAINCDIRS))
CFLAGS	+=	$(CSTD)
CFLAGS	+=	-DF_CPU=$(F_CPU)

ALL_CFLAGS	= -mmcu=$(MCU) -I$(PRJ_DIR) $(CFLAGS) $(DEPFLAGS)

## Libraries
MATH_LIB	=	-lm

## ld-flags
LDFLAGS	=	-Wl,-Map=$(TARGET).map,--cref
LDFLAGS	+=	$(MATH_LIB)

## ~ ~ ~ AVRDUDE ~ ~ ~ ##
AVRDUDE_FLAGS		=	-p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)
AVRDUDE_WRITE_FLASH	=	-U flash:w:$(TARGET).hex

