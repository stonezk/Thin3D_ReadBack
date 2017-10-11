# Copyright (c) 2001, Stanford University
# All rights reserved.
#
# See the file LICENSE.txt for information on redistributing this software.

TOP = ..
GEN = $(TOP)/gen

SPU = 1
#SHARED = 1
LIBRARY = errorspu
LIBRARIES = crutil

FILES = errorspu_init \
	$(GEN)/errorspu

PRECOMP = $(GEN)/errorspu.c
SLOP = $(PRECOMP)

LIB_DEFS += error.def
include ${TOP}/cr.mk

$(GEN)/errorspu.c: error.py
	@$(ECHO) Building the Error SPU
	@$(PYTHON) error.py > $@
