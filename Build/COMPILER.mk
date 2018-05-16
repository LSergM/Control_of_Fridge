# TCDIR - IAR Compiler tool chain root directory

COMPILERROOTDIR=$(subst \\,/,$(COMPILER_ROOT_DIR))
$(info $$COMPILERROOTDIR is [${COMPILERROOTDIR}])

ifeq ('$(COMPILER)','IAR')
include $(COMPILERROOTDIR)IAR.mk
else ifeq ('$(COMPILER)','ARMGCC')
include $(COMPILERROOTDIR)ARMGCC.mk
else
  $(error COMPILER Compiler tool chain invalid)
endif
