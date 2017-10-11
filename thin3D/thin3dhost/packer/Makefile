# Copyright (c) 2001, Stanford University
# All rights reserved.
#
# See the file LICENSE.txt for information on redistributing this software.

TOP = ..
GEN = $(TOP)/gen

#SHARED = 1
LIBRARY = crpacker
LIBRARIES = crutil

NORMAL_FILES = $(GEN)/packer \
	pack_arrays \
	$(GEN)/pack_bbox \
	pack_beginend \
	pack_bounds \
	pack_buffer \
	pack_bufferobject \
	pack_client \
	pack_clipplane \
	pack_context \
	$(GEN)/pack_current \
	pack_error \
	pack_extensions \
	pack_feedback \
	pack_fence \
	pack_fog \
	pack_init \
	pack_lights \
	pack_lists \
	pack_swap_lists \
	pack_map \
	pack_point \
	pack_swap_map \
	pack_misc \
	pack_materials \
	pack_matrices \
	pack_pixels \
	pack_pixelmap \
	pack_swap_pixelmap \
	pack_program \
	pack_regcombiner \
	pack_stipple \
	pack_texture \
	pack_swap_texture \
	pack_framebuffer \
	pack_shaders \
	pack_visibleregion

LIB_DEFS = $(GEN)/packer.def

SWAP_FILES = pack_arrays \
	pack_bounds \
	pack_bufferobject \
	pack_client \
	pack_clipplane \
	pack_fog \
	pack_lights \
	pack_materials \
	pack_matrices \
	pack_misc \
	pack_pixels \
	pack_point \
	pack_program \
	pack_regcombiner \
	pack_stipple

NAMED_SWAP_FILES = $(addsuffix _swap, $(SWAP_FILES))
SWAP_C_FILES = $(addsuffix .c, $(NAMED_SWAP_FILES))
GEN_NAMED_SWAP_FILES = $(addprefix $(GEN)/, $(NAMED_SWAP_FILES))
GEN_SWAP_C_FILES = $(addprefix $(GEN)/, $(SWAP_C_FILES))

FILES = $(GEN_NAMED_SWAP_FILES) $(NORMAL_FILES)

PRECOMP = $(GEN)/packer.def $(GEN)/cr_packfunctions.h $(GEN)/cr_opcodes.h $(GEN)/state/cr_currentpointers.h $(GEN)/pack_bbox.c $(GEN)/pack_current.c $(GEN)/packer.c $(GEN_SWAP_C_FILES)
SLOP = $(PRECOMP)

#LIB_COPIES = packspu \
	tilesortspu \
	hiddenlinespu \
	archsplitspu \
	replicatespu

include $(TOP)/cr.mk

APIFILES = $(TOP)/glapi_parser/apiutil.py $(TOP)/glapi_parser/APIspec.txt

$(GEN)/packer.def: packer_defs.py $(APIFILES)
	@$(ECHO) Making the packer def file
	#@$(ECHO) (GEN_SWAP_C_FILES): $(GEN_SWAP_C_FILES)
	@$(PYTHON) $< > $@

$(GEN)/cr_packfunctions.h: pack_header.py packer_special $(API_FILES)
	@$(ECHO) Making the pack functions header..
	@$(PYTHON) pack_header.py > $@

$(GEN)/cr_opcodes.h: opcodes.py $(APIFILES)
	@$(ECHO) Making the opcode header...
	$(PYTHON) opcodes.py > $@

$(GEN)/state/cr_currentpointers.h: pack_currentheader.py pack_currenttypes.py
	@$(ECHO) Making cr_currentpointers.h
	@$(PYTHON) pack_currentheader.py > $@

$(GEN)/packer.c: packer.py packer_special $(APIFILES)
	@$(ECHO) Making the Packer...
	@$(PYTHON) packer.py > $@

$(GEN)/pack_bbox.c: packer_bbox.py
	@$(ECHO) Making the BBOX Packer...
	@$(PYTHON) packer_bbox.py > $@

$(GEN)/pack_current.c: pack_current.py pack_currenttypes.py
	@$(ECHO) Making the current functions...
	@$(PYTHON) pack_current.py > $@

$(GEN)/%_swap.c: %.c pack_swap.py
	@$(ECHO) Making the swapping version of $<
	@$(PYTHON) pack_swap.py $< > $@
