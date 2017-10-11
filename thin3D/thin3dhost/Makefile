# Copyright (c) 2001, Stanford University
# All rights reserved.
#
# See the file LICENSE.txt for information on redistributing this software.

TOP = .

include $(TOP)/arch.mk

ifeq ($(USE_DMX), 1)
DMX_DIR = dmx
endif

ifeq ($(DOXYGEN), 1)
DOXYGEN_DIR = doxygen
endif

SUBDIRS = iprt xpcom util spu_loader packer state_tracker error \
	unpacker render crserverlib crserver

include ${TOP}/cr.mk

