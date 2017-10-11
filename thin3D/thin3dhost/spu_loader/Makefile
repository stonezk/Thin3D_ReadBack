# Copyright (c) 2001, Stanford University
# All rights reserved.
#
# See the file LICENSE.txt for information on redistributing this software.

TOP = ..
GEN = $(TOP)/gen

#SHARED = 1
LIBRARY = spuload
LIBRARIES = crutil

FILES = \
	spuinit \
	spuload \
	choosevisual \
	$(GEN)/spuchange \
	$(GEN)/spucopy \
	$(GEN)/dispatch \
	$(GEN)/glloader

PRECOMP = $(GEN)/dispatch.c $(GEN)/spucopy.c $(GEN)/spuchange.c $(GEN)/glloader.c
SLOP = $(PRECOMP)

LIB_DEFS += loader.def

# Need this for crChooseVisual()
ifdef WINDOWS
#LDFLAGS += user32.lib gdi32.lib
else
ifdef DARWIN
#LDFLAGS += -framework Carbon -framework ApplicationServices
else
LDFLAGS += -lX11
endif
endif

include ${TOP}/cr.mk

#$(TOP)/include/spu_dispatch_table.h: dispatchheader.py ../glapi_parser/apiutil.py ../glapi_parser/APIspec.txt
#	@$(ECHO) Making the SPU dispatch header
#	@$(PYTHON) dispatchheader.py > $(TOP)/include/spu_dispatch_table.h

$(GEN)/dispatch.c: dispatch.py ../glapi_parser/apiutil.py ../glapi_parser/APIspec.txt
	@$(ECHO) Making the SPU dispatch builder
	@$(PYTHON) dispatch.py > $(GEN)/dispatch.c

$(GEN)/spucopy.c: spucopy.py ../glapi_parser/apiutil.py ../glapi_parser/APIspec.txt
	@$(ECHO) Making the SPU copier
	@$(PYTHON) spucopy.py > $(GEN)/spucopy.c

$(GEN)/spuchange.c: spuchange.py ../glapi_parser/apiutil.py ../glapi_parser/APIspec.txt
	@$(ECHO) Making the SPU interface changer
	@$(PYTHON) spuchange.py > $(GEN)/spuchange.c

$(GEN)/glloader.c: glloader.py ../glapi_parser/apiutil.py ../glapi_parser/APIspec.txt
	@$(ECHO) Building the OpenGL API loader
	@$(PYTHON) glloader.py > $(GEN)/glloader.c
