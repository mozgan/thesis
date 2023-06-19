#=============================================================================#
#
#	  File: Makefile
#
#	 Usage: make		(generate hex file to flash on chip		)
#	 	make flash	(flash the hex file on chip			)
#	 	make clean	(remove object, executables, prerequisits	)
#	 	make doxy	(generate doxygen documentation			)
#
#
#
#	Author: M. Ozgan, <mozgan@mozgan.org>
#      Created: 19.08.2013 15:22
#      Company: TU Wien
#
# $Id: Makefile,v 1.0 19.08.2013 15:22 mozgan Exp $
#
#==============================================================================#

## === Shell Commands ====================================================== ##
MAKE	= `which make`
SHELL	= `which sh`
CC	= `which avr-gcc`
OBJCOPY	= `which avr-objcopy`
OBJDUMP	= `which avr-objdump`
SIZE	= `which avr-size`
NM	= `which avr-nm`
AVRDUDE	= `which avrdude`
RM	= -rm -f
RM_DIR	= -rm -rf
COPY	= `which cp`
DOX	= `which doxygen`
DOXYFILE= doxy.file

## === Makefile Messages =================================================== ##
MSG_LINE		= ===========================
MSG_ERRORS_NONE		= Errors: none
MSG_BEGIN		= --- --- --- begin --- --- ---
MSG_END			= --- --- --- end --- --- ---
MSG_GCC_VERSION		= GCC Version
MSG_SIZE_BEFORE		= Size before:
MSG_SIZE_AFTER		= Size after:
MSG_COFF		= Converting to AVR COFF:
MSG_EXTENDED_COFF	= Converting to AVR Extended COFF:
MSG_FLASH		= Creating load file for Flash:
MSG_EEPROM		= Creating load file for EEPROM:
MSG_EXTENDED_LISTING	= Creating Extended Listing:
MSG_SYMBOL_TABLE	= Creating Symbol Table:
MSG_LINKING		= Linking:
MSG_COMPILING		= Compiling:
MSG_ASSEMBLING		= Assembling:
MSG_CLEANING		= Cleaning project:
MSG_CREATING_LIBRARY	= Creating library:

## === Sources ============================================================= ##
ALL_SRC		= $(DRIVER_SRC) $(LIBRARY) $(SRC)
OBJ		= $(ALL_SRC:.c=.o) #$(DRIVER_SRC:.c=.o) $(SRC:.c=.o) $(LIBRARY:.c=.o)
LST		= $(ALL_SRC:.c=.lst) #$(DRIVER_SRC:.c=.lst) $(LIBRARY:.c=.lst) $(SRC:.c=.lst)


LIBNAME		= lib$(TARGET).a

## === ELFSIZE - HEXSIZE =================================================== ##
ELFSIZE	= $(SIZE) --mcu=$(MCU) -d -t -A $(TARGET).elf
ELFMEM	= $(SIZE) --mcu=$(MCU) -d -t -C $(TARGET).elf
HEXSIZE	= $(SIZE) --target=$(FORMAT) $(TARGET).hex

## === Targets ============================================================= ##
all: begin gccversion sizebefore build showtarget sizeafter finished end

lib: $(LIBNAME)

# === begin === #
begin	:
	@echo
	@echo $(MSG_BEGIN)

# === gccversion === #
gccversion:
	@echo $(MSG_GCC_VERSION)
	@echo $(MSG_LINE)
	@$(CC) --version

# === sizebefore === #
sizebefore: 
	@if [ -f $(TARGET).elf ]; then                  \
		echo;                                   \
		echo $(MSG_SIZE_BEFORE);                \
		echo $(MSG_LINE);                       \
		$(ELFSIZE);                             \
		$(ELFMEM);                              \
		echo;                                   \
	fi

# === sizeafter === #
sizeafter: 
	@if [ -f $(TARGET).elf ]; then                  \
		echo;                                   \
		echo $(MSG_SIZE_AFTER);                 \
		echo $(MSG_LINE);                       \
		$(ELFSIZE);                             \
		$(ELFMEM);                              \
		echo;                                   \
	fi

# === showtarget === #
showtarget:
	@echo
	@echo " --- --- --- Target  Information --- --- --- "
	@echo "      AVR Model       : $(MCU)"
	@echo "      Board           : $(BOARD)"
	@echo "      MCU Frequency   : $(F_CPU) Hz"
	@echo " --- --- --- --- --- --- --- --- --- --- --- "

# === finished === #
finished:
	@echo $(MSG_ERRORS_NONE)

# === end === #
end:
	@echo $(MSG_END)
	@echo

# === build === #
build: elf hex eep lss sym

# === build targets === #
elf	: $(TARGET).elf
hex	: $(TARGET).hex
eep	: $(TARGET).eep
lss	: $(TARGET).lss
sym	: $(TARGET).sym

#.PRECIOUS: $(OBJ)
#.SECONDARY: $(TARGET).elf

$(TARGET).elf: $(OBJ)
	@echo
	@echo $(MSG_LINKING) $@
	@echo $(MSG_LINE)
	$(CC) $(ALL_CFLAGS) $(OBJ) $(LDFLAGS) --output $@

$(TARGET).hex: $(TARGET).elf
	@echo
	@echo $(MSG_FLASH) $@
	@echo $(MSG_LINE)
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $(TARGET).elf $@

$(TARGET).eep: $(TARGET).elf
	@echo
	@echo $(MSG_EXTENDED_LISTING) $(TARGET).hex
	@echo $(MSG_LINE)
	$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load"       	\
		--change-section-lma .eeprom=0 -O $(FORMAT) $(TARGET).elf $@ 

$(TARGET).lss: $(TARGET).elf
	@echo
	@echo $(MSG_EXTENDED_LISTING) $(TARGET).lss
	@echo $(MSG_LINE)
	$(OBJDUMP) -h -S $(TARGET).elf > $(TARGET).lss

$(TARGET).sym: $(TARGET).elf
	@echo
	@echo $(MSG_SYMBOL_TABLE) $(TARGET).sym
	@echo $(MSG_LINE)
	$(NM) -n $(TARGET).elf > $(TARGET).sym

# === Object Files === #
.c.o	: $(ALL_SRC)
	@echo
	@echo $(MSG_COMPILING) $<
	@echo $(MSG_LINE)
	@if [ ! -e .dep ]; then							\
		mkdir .dep 2>/dev/null $(wildcard .dep/*);			\
	fi
	$(CC) $(ALL_CFLAGS) -c $< -o $@

# === FLASH === #
flash: $(TARGET).hex $(TARGET).eep
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)

# === clean === #
clean: begin clean_all finished end

clean_all:
	@echo
	@echo $(MSG_CLEANING)
	$(RM) $(TARGET).hex
	$(RM) $(TARGET).eep
	$(RM) $(TARGET).obj
	$(RM) $(TARGET).cof
	$(RM) $(TARGET).elf
	$(RM) $(TARGET).map
	$(RM) $(TARGET).obj
	$(RM) $(TARGET).sym
	$(RM) $(TARGET).lnk
	$(RM) $(TARGET).lss
	$(RM) $(OBJ)
	$(RM) $(LST)
	$(RM) $(SRC:.c=.s)
	$(RM) $(SRC:.c=.d)
	$(RM_DIR) .dep
	$(RM_DIR) doc

# === doxy === #
doxy:
	@if [ ! -x $(DOX) ]; then						\
		echo "you must install doxygen";				\
	else									\
		$(DOX) $(DOXYFILE);						\
	fi

# === help === #
help:
	@echo 
	@echo	"Usage: make [options]"
	@echo	"       make       generate hex file to flash on chip"
	@echo	"       flash      flash the hex file on chip"
	@echo	"       clean      remove objects, executables, and prerequisits"
	@echo	"       doxy       generate doxygen documentation"
	@echo 

# === .PHONY === #
.PHONY: all begin finish end sizebefore sizeafter gccversion build            \
	elf hex eep lss sym coff extcoff clean clean_all flash

