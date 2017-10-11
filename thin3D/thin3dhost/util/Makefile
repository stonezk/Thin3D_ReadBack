# Copyright (c) 2001, Stanford University
# All rights reserved.
#
# See the file LICENSE.txt for information on redistributing this software.

TOP = ..
GEN = $(TOP)/gen

include ${TOP}/arch.mk

#SHARED = 1
LIBRARY = crutil
LIBRARIES = iprt

FILES = bbox \
	bufpool \
	calllists \
	devnull \
	dll \
	endian \
	environment \
	error \
	filenet \
	hash \
	hull \
	list \
	matrix \
	mem \
	net \
	pixel \
	process \
	rand \
	string \
	threads \
	tcpip \
	udptcpip \
	timer \
	url \
	warp \
	vreg \
	blitter \
	compositor \
	htable \
	bmpscale \
	sortarray 

PRECOMP = $(GEN)/debug_opcodes.c $(GEN)/state/cr_statefuncs.h $(GEN)/spu_dispatch_table.h
SLOP += ${PRECOMP}

ifeq ($(IB_SUPPORT), 1)
CFLAGS += -DIB_SUPPORT -I/usr/mellanox/include
FILES += ib
LDFLAGS += -L/usr/mellanox/lib -lvapi -lmosal -lpthread -lmpga
endif
ifeq ($(SDP_SUPPORT), 1)
CFLAGS += -DSDP_SUPPORT 
endif
ifeq ($(GM_SUPPORT), 1)
ifeq ($(ARCH),Linux)
CFLAGS += -DGM_SUPPORT
FILES += gm
LDFLAGS += -lgm
endif
ifeq ($(ARCH), WIN_NT)
CFLAGS += -DGM_SUPPORT
FILES += gm
LDFLAGS += gm.lib
endif
endif

ifeq ($(ARCH), Darwin)
LDFLAGS += -framework Carbon
endif

ifeq ($(ARCH), SunOS)
LDFLAGS+= -lsocket -lnsl
endif

LIB_DEFS = util.def

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
LDFLAGS += -lpthread -fPIC -shared
endif
endif
endif
endif

ifeq ($(TEAC_SUPPORT), 1)
CFLAGS += -DTEAC_SUPPORT -DCHROMIUM -DHOST_TABLE_FILENAME="\"${PWD}/util/teac_host_map.t\""
ifeq ($(ARCH), OSF1)
CFLAGS += -I/usr/opt/rms/include
endif
LDFLAGS += -lelan3
FILES += libteac teac
endif

ifeq ($(TCSCOMM_SUPPORT), 1)
CFLAGS += -DTCSCOMM_SUPPORT -DCHROMIUM -I/usr/opt/rms/include
LDFLAGS += -lelan3
FILES += tcscomm
endif

ifeq ($(SDP_SUPPORT), 1)
FILES += sdp
endif

include ${TOP}/cr.mk

$(GEN)/debug_opcodes.c: debug_opcodes.py $(TOP)/glapi_parser/APIspec.txt
	@$(ECHO) Making the opcode debugger...
	@$(PYTHON) debug_opcodes.py > $@

APIFILES = ../glapi_parser/apiutil.py ../glapi_parser/APIspec.txt

$(GEN)/state/cr_statefuncs.h: state_funcs.py state_special state_feedback_special state_select_special $(APIFILES)
	@$(ECHO) Making cr_statefuncs.h
	@mkdir -p $(GEN)/state
	@$(PYTHON) state_funcs.py > $@

$(GEN)/spu_dispatch_table.h: dispatchheader.py $(APIFILES)
	@$(ECHO) Making the SPU dispatch header
	@$(PYTHON) dispatchheader.py > $(GEN)/spu_dispatch_table.h
