
PRG = demo
OBJ = demo.o

MCU_TARGET = atmega168a

OPTIMIZE = -O2
DEFS =
LIBS =
	
CC = avr-gcc

override CFLAGS = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)
override LDFLAGS = -Wl,-Map,$(PRG).map

OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump

all: $(PRG).elf lst text

$(PRG).elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

# dependency:
demo.o: demo.c iocompat.h
clean:
	rm -rf *.o $(PRG).elf *.eps *.png *.pdf *.bak 
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)
lst:  $(PRG).lst
%.lst: %.elf
    $(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images
text: hex bin srec
hex:  $(PRG).hex
bin:  $(PRG).bin
srec: $(PRG).srec

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@
%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@
%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@


