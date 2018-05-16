# TCDIR - GNU Arm Embedded Toolchain

#TCDIR=C:\\DGSTC\\"GNU Tools ARM Embedded"\\"gcc-arm-none-eabi-7-2017-q4-major-win32"\\
TCDIR=C:\\DGSTC\\"GNU Tools ARM Embedded"\\"7 2017-q4-major"\\
$(info $$TCDIR is [${TCDIR}])

# Tool directories
TCBINDIR=$(TCDIR)bin\\
$(info $$TCBINDIR is [${TCBINDIR}])

#Commands
CC=$(TCBINDIR)arm-none-eabi-gcc.exe
AS=$(TCBINDIR)arm-none-eabi-as.exe
AR=$(TCBINDIR)arm-none-eabi-ar.exe
LK=$(TCBINDIR)arm-none-eabi-ld.exe
ELF=$(TCBINDIR)arm-none-eabi-objcopy.exe

# ARM GCC Compiler
CFLAGS=-D__USE_CMSIS  
CFLAGS+=-DCPU_LPC54608J512ET180_cm4  
CFLAGS+=-DCPU_LPC54608J512ET180 
CFLAGS+=-D__MCUXPRESSO 

CFLAGS+=-O0  
CFLAGS+=-fno-common  
CFLAGS+=-ggdb 
CFLAGS+=-Wall  
CFLAGS+=-c  
CFLAGS+="-fmessage-length=0"  
CFLAGS+=-fno-builtin  
CFLAGS+=-ffunction-sections  
CFLAGS+=-fdata-sections  
CFLAGS+="-mcpu=cortex-m4"  
CFLAGS+="-mfpu=fpv4-sp-d16" 
CFLAGS+="-mfloat-abi=hard"  
CFLAGS+=-mthumb  
CFLAGS+=-D__REDLIB__
#CFLAGS+=-specs=redlib.specs 

# To prevent compilation of assert in fsl_
CFLAGS+=-DNDEBUG 

#CFLAGS+=-DDEBUG 


# GCC Assembler
ASFLAGS=-s+ -w+ -r --cpu Cortex-M4 --fpu VFPv4_sp

# GCC Archive flags
# -q quick append
# -c create the archive
ARFLAGS=-qc

LKFLAGS=-nostdlib -print-memory-usage --gc-sections $(SDKLINKLIB)
LKFLAGS+=-Map="$(LISTDIR)$(APPNAME).map"

# Linker script
LDSCRIPT="-T$(COMPILER)_$(UPROCESSOR).ld"

# LK Archive
LKARCHIVES=$(DGOSPFARCHIVE) $(DGOSFWARCHIVE) $(DGOSOALARCHIVE) $(DGOSARCHIVE) $(DGOSSTUBARCHIVE) $(DGOSRTOS_SDKDIR)libs\\libpower_hardabi.a

# ELF tool options
#ELFCHECKSUMFLAGS=--checksum "__vector_table+0x1c:4,sum32:2;__vector_table-__vector_table+0x1B" --verbose
ELFCHECKSUMFLAGS=-O elf32-littlearm
ELFHEXFLAGS=-O ihex
ELFBINFLAGS=-O binary

# output file (-o) extension of the linker
LKOFILEEXT=elf


