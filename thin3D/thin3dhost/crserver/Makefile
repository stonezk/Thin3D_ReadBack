# Copyright (c) 2001, Stanford University
# All rights reserved.
#
# See the file LICENSE.txt for information on redistributing this software.

TOP = ..

include $(TOP)/arch.mk

SHARED = 1
#PROGRAM = crserver
LIBRARY = thin3dhost
LIBRARIES = crserverlib crstate crpacker crunpacker crutil renderspu spuload errorspu iprt xpcom ssl xml2 crypt rt  jpeg 

FILES = crservice

UNPACKS = 1

CXXFLAGS += -std=c++0x -DVBOX_WITH_XPCOM \
	-I../xpcom/include/xpcom -I../xpcom/include \
	-I../xpcom/include/nsprpub 

ifeq ($(ARCH), WIN_NT)
LDFLAGS += user32.lib ws2_32.lib
else
ifeq ($(ARCH),FreeBSD)
LDFLAGS += -lpthread
else
ifeq ($(ARCH), OSF1)
LDFLAGS += -lpthread
else
ifndef IRIX_64BIT
LDFLAGS += -ldl -lpthread
else
LDFLAGS += -lpthread
endif
endif
endif
endif

ifdef WINDOWS
LDFLAGS += user32.lib gdi32.lib
else
ifdef DARWIN
LDFLAGS += -framework Carbon -framework ApplicationServices
else
LDFLAGS += -L/usr/lib64 -lXmu -lX11
endif
endif

include $(TOP)/cr.mk
