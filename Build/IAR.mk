# TCDIR - IAR Compiler tool chain root directory
ifeq ('$(COMPVER)','V8.11.3.13950')
TCDIR=C:\\DGSTC\\"Embedded Workbench 8.0"\\
TCDIRFORPARM=C:\\DGSTC\\Embedded Workbench 8.0\\
else ifeq ('$(COMPVER)','V8.20.1.14183')
TCDIR=C:\\DGSTC\\"Embedded Workbench 8.20"\\
TCDIRFORPARM=C:\\DGSTC\\Embedded Workbench 8.20\\
else ifeq ('$(COMPVER)','V7.70.2.11706')
TCDIR=C:\\DGSTC\\"Embedded Workbench 7.5"\\
TCDIRFORPARM=C:\\DGSTC\\Embedded Workbench 7.5\\
else ifeq ('$(COMPVER)','V7.50.1.10123')
TCDIR=C:\\DGSTC\\"Embedded Workbench 7.3"\\
TCDIRFORPARM=C:\\DGSTC\\Embedded Workbench 7.3\\
else
  $(error COMPVER IAR Compiler version invalid)
endif



# Prepare TCDIR for use as parameter
TCDIRPARM=$(subst \\,\,$(TCDIRFORPARM))
# Tool directories
TCBINDIR=$(TCDIR)arm\\bin\\

#Commands
CC=$(TCBINDIR)iccarm.exe
AS=$(TCBINDIR)iasmarm.exe
AR=$(TCBINDIR)iarchive.exe
LK=$(TCBINDIR)ilinkarm.exe
ELF=$(TCBINDIR)ielftool.exe

# Compiler
CFLAGS=-D CORE_M4 
CFLAGS+=-D USE_FPU 
CFLAGS+=--diag_suppress Pa050 
CFLAGS+=--debug 
CFLAGS+=--endian=little 
CFLAGS+=--cpu=Cortex-M4 
CFLAGS+=-e 
CFLAGS+=--fpu=VFPv4_sp 
CFLAGS+=--dlib_config "$(TCDIRPARM)arm\INC\c\DLib_Config_Normal.h" 
CFLAGS+=--header_context

#CFLAGS+=--predef_macros $*.predef --dependencies $*.depend

# Assembler
ASFLAGS=-s+ -w+ -r --cpu Cortex-M4 --fpu VFPv4_sp

# Archive flags
ARFLAGS=--create 

# Linker flags
ifeq ('$(COMPVER)','V8.11.3.13950')
LKFLAGS=--entry __iar_program_start --inline "C:\DGSTC\Embedded Workbench 8.0\arm\CMSIS\Lib\IAR\iar_cortexM4lf_math.a" --vfe
else ifeq ('$(COMPVER)','V8.20.1.14183')
LKFLAGS=--entry __iar_program_start --inline "C:\DGSTC\Embedded Workbench 8.20\arm\CMSIS\Lib\IAR\iar_cortexM4lf_math.a" --vfe
else ifeq ('$(COMPVER)','V7.70.2.11706')
LKFLAGS=--entry __iar_program_start --inline "C:\DGSTC\Embedded Workbench 7.5\arm\CMSIS\Lib\IAR\iar_cortexM4lf_math.a" --vfe
else ifeq ('$(COMPVER)','V7.50.1.10123')
LKFLAGS=--entry __iar_program_start --inline "C:\DGSTC\Embedded Workbench 7.3\arm\CMSIS\Lib\IAR\iar_cortexM4lf_math.a" --vfe
else
  $(error COMPVER Compiler version invalid - cannot assign LKFLAGS)
endif

LKFLAGS_MAPFILE=$(LISTDIR)$(APPNAME).map
LKFLAGS+=--map $(LKFLAGS_MAPFILE)

# Linker script
LDSCRIPT=--config $(COMPILER)_$(UPROCESSOR).icf

# LK ARCHIVES
#
LKARCHIVES=$(DGOSPFARCHIVE) $(DGOSFWARCHIVE) $(DGOSOALARCHIVE) $(DGOSARCHIVE) $(DGOSSTUBARCHIVE) 

# ELF Tool 
ELFCHECKSUMFLAGS=--checksum "__vector_table+0x1c:4,sum32:2;__vector_table-__vector_table+0x1B" --verbose
ELFHEXFLAGS=--ihex --verbose 
ELFBINFLAGS=--bin --verbose 

# output file (-o) extension of the linker
LKOFILEEXT=out