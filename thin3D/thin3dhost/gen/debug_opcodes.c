/* Copyright (c) 2001, Stanford University
	All rights reserved.

	See the file LICENSE.txt for information on redistributing this software. */
	

#include "cr_debugopcodes.h"
#include <stdio.h>

void crDebugOpcodes( FILE *fp, unsigned char *ptr, unsigned int num_opcodes )
{
	unsigned int i;
	for (i = 0 ; i < num_opcodes ; i++)
	{
		switch(*(ptr--))
		{

		case CR_ALPHAFUNC_OPCODE:
			fprintf( fp, "CR_ALPHAFUNC_OPCODE\n" ); 
			break;
		case CR_ARRAYELEMENT_OPCODE:
			fprintf( fp, "CR_ARRAYELEMENT_OPCODE\n" ); 
			break;
		case CR_BEGIN_OPCODE:
			fprintf( fp, "CR_BEGIN_OPCODE\n" ); 
			break;
		case CR_BINDTEXTURE_OPCODE:
			fprintf( fp, "CR_BINDTEXTURE_OPCODE\n" ); 
			break;
		case CR_BITMAP_OPCODE:
			fprintf( fp, "CR_BITMAP_OPCODE\n" ); 
			break;
		case CR_BLENDFUNC_OPCODE:
			fprintf( fp, "CR_BLENDFUNC_OPCODE\n" ); 
			break;
		case CR_BOUNDSINFOCR_OPCODE:
			fprintf( fp, "CR_BOUNDSINFOCR_OPCODE\n" ); 
			break;
		case CR_CALLLIST_OPCODE:
			fprintf( fp, "CR_CALLLIST_OPCODE\n" ); 
			break;
		case CR_CALLLISTS_OPCODE:
			fprintf( fp, "CR_CALLLISTS_OPCODE\n" ); 
			break;
		case CR_CLEAR_OPCODE:
			fprintf( fp, "CR_CLEAR_OPCODE\n" ); 
			break;
		case CR_CLIPPLANE_OPCODE:
			fprintf( fp, "CR_CLIPPLANE_OPCODE\n" ); 
			break;
		case CR_COLOR3B_OPCODE:
			fprintf( fp, "CR_COLOR3B_OPCODE\n" ); 
			break;
		case CR_COLOR3D_OPCODE:
			fprintf( fp, "CR_COLOR3D_OPCODE\n" ); 
			break;
		case CR_COLOR3F_OPCODE:
			fprintf( fp, "CR_COLOR3F_OPCODE\n" ); 
			break;
		case CR_COLOR3I_OPCODE:
			fprintf( fp, "CR_COLOR3I_OPCODE\n" ); 
			break;
		case CR_COLOR3S_OPCODE:
			fprintf( fp, "CR_COLOR3S_OPCODE\n" ); 
			break;
		case CR_COLOR3UB_OPCODE:
			fprintf( fp, "CR_COLOR3UB_OPCODE\n" ); 
			break;
		case CR_COLOR3UI_OPCODE:
			fprintf( fp, "CR_COLOR3UI_OPCODE\n" ); 
			break;
		case CR_COLOR3US_OPCODE:
			fprintf( fp, "CR_COLOR3US_OPCODE\n" ); 
			break;
		case CR_COLOR4B_OPCODE:
			fprintf( fp, "CR_COLOR4B_OPCODE\n" ); 
			break;
		case CR_COLOR4D_OPCODE:
			fprintf( fp, "CR_COLOR4D_OPCODE\n" ); 
			break;
		case CR_COLOR4F_OPCODE:
			fprintf( fp, "CR_COLOR4F_OPCODE\n" ); 
			break;
		case CR_COLOR4I_OPCODE:
			fprintf( fp, "CR_COLOR4I_OPCODE\n" ); 
			break;
		case CR_COLOR4S_OPCODE:
			fprintf( fp, "CR_COLOR4S_OPCODE\n" ); 
			break;
		case CR_COLOR4UB_OPCODE:
			fprintf( fp, "CR_COLOR4UB_OPCODE\n" ); 
			break;
		case CR_COLOR4UI_OPCODE:
			fprintf( fp, "CR_COLOR4UI_OPCODE\n" ); 
			break;
		case CR_COLOR4US_OPCODE:
			fprintf( fp, "CR_COLOR4US_OPCODE\n" ); 
			break;
		case CR_COLORMASK_OPCODE:
			fprintf( fp, "CR_COLORMASK_OPCODE\n" ); 
			break;
		case CR_COLORMATERIAL_OPCODE:
			fprintf( fp, "CR_COLORMATERIAL_OPCODE\n" ); 
			break;
		case CR_COPYPIXELS_OPCODE:
			fprintf( fp, "CR_COPYPIXELS_OPCODE\n" ); 
			break;
		case CR_COPYTEXIMAGE1D_OPCODE:
			fprintf( fp, "CR_COPYTEXIMAGE1D_OPCODE\n" ); 
			break;
		case CR_COPYTEXIMAGE2D_OPCODE:
			fprintf( fp, "CR_COPYTEXIMAGE2D_OPCODE\n" ); 
			break;
		case CR_COPYTEXSUBIMAGE1D_OPCODE:
			fprintf( fp, "CR_COPYTEXSUBIMAGE1D_OPCODE\n" ); 
			break;
		case CR_COPYTEXSUBIMAGE2D_OPCODE:
			fprintf( fp, "CR_COPYTEXSUBIMAGE2D_OPCODE\n" ); 
			break;
		case CR_COPYTEXSUBIMAGE3D_OPCODE:
			fprintf( fp, "CR_COPYTEXSUBIMAGE3D_OPCODE\n" ); 
			break;
		case CR_CULLFACE_OPCODE:
			fprintf( fp, "CR_CULLFACE_OPCODE\n" ); 
			break;
		case CR_DELETETEXTURES_OPCODE:
			fprintf( fp, "CR_DELETETEXTURES_OPCODE\n" ); 
			break;
		case CR_DEPTHFUNC_OPCODE:
			fprintf( fp, "CR_DEPTHFUNC_OPCODE\n" ); 
			break;
		case CR_DEPTHMASK_OPCODE:
			fprintf( fp, "CR_DEPTHMASK_OPCODE\n" ); 
			break;
		case CR_DEPTHRANGE_OPCODE:
			fprintf( fp, "CR_DEPTHRANGE_OPCODE\n" ); 
			break;
		case CR_DISABLE_OPCODE:
			fprintf( fp, "CR_DISABLE_OPCODE\n" ); 
			break;
		case CR_DISABLECLIENTSTATE_OPCODE:
			fprintf( fp, "CR_DISABLECLIENTSTATE_OPCODE\n" ); 
			break;
		case CR_DRAWARRAYS_OPCODE:
			fprintf( fp, "CR_DRAWARRAYS_OPCODE\n" ); 
			break;
		case CR_DRAWPIXELS_OPCODE:
			fprintf( fp, "CR_DRAWPIXELS_OPCODE\n" ); 
			break;
		case CR_EDGEFLAG_OPCODE:
			fprintf( fp, "CR_EDGEFLAG_OPCODE\n" ); 
			break;
		case CR_ENABLE_OPCODE:
			fprintf( fp, "CR_ENABLE_OPCODE\n" ); 
			break;
		case CR_ENABLECLIENTSTATE_OPCODE:
			fprintf( fp, "CR_ENABLECLIENTSTATE_OPCODE\n" ); 
			break;
		case CR_END_OPCODE:
			fprintf( fp, "CR_END_OPCODE\n" ); 
			break;
		case CR_EVALCOORD1D_OPCODE:
			fprintf( fp, "CR_EVALCOORD1D_OPCODE\n" ); 
			break;
		case CR_EVALCOORD1F_OPCODE:
			fprintf( fp, "CR_EVALCOORD1F_OPCODE\n" ); 
			break;
		case CR_EVALCOORD2D_OPCODE:
			fprintf( fp, "CR_EVALCOORD2D_OPCODE\n" ); 
			break;
		case CR_EVALCOORD2F_OPCODE:
			fprintf( fp, "CR_EVALCOORD2F_OPCODE\n" ); 
			break;
		case CR_EVALMESH1_OPCODE:
			fprintf( fp, "CR_EVALMESH1_OPCODE\n" ); 
			break;
		case CR_EVALMESH2_OPCODE:
			fprintf( fp, "CR_EVALMESH2_OPCODE\n" ); 
			break;
		case CR_EVALPOINT1_OPCODE:
			fprintf( fp, "CR_EVALPOINT1_OPCODE\n" ); 
			break;
		case CR_EVALPOINT2_OPCODE:
			fprintf( fp, "CR_EVALPOINT2_OPCODE\n" ); 
			break;
		case CR_FEEDBACKBUFFER_OPCODE:
			fprintf( fp, "CR_FEEDBACKBUFFER_OPCODE\n" ); 
			break;
		case CR_FINISH_OPCODE:
			fprintf( fp, "CR_FINISH_OPCODE\n" ); 
			break;
		case CR_FLUSH_OPCODE:
			fprintf( fp, "CR_FLUSH_OPCODE\n" ); 
			break;
		case CR_FOGCOORDDEXT_OPCODE:
			fprintf( fp, "CR_FOGCOORDDEXT_OPCODE\n" ); 
			break;
		case CR_FOGCOORDFEXT_OPCODE:
			fprintf( fp, "CR_FOGCOORDFEXT_OPCODE\n" ); 
			break;
		case CR_FOGF_OPCODE:
			fprintf( fp, "CR_FOGF_OPCODE\n" ); 
			break;
		case CR_FOGFV_OPCODE:
			fprintf( fp, "CR_FOGFV_OPCODE\n" ); 
			break;
		case CR_FOGI_OPCODE:
			fprintf( fp, "CR_FOGI_OPCODE\n" ); 
			break;
		case CR_FOGIV_OPCODE:
			fprintf( fp, "CR_FOGIV_OPCODE\n" ); 
			break;
		case CR_FRONTFACE_OPCODE:
			fprintf( fp, "CR_FRONTFACE_OPCODE\n" ); 
			break;
		case CR_FRUSTUM_OPCODE:
			fprintf( fp, "CR_FRUSTUM_OPCODE\n" ); 
			break;
		case CR_INDEXMASK_OPCODE:
			fprintf( fp, "CR_INDEXMASK_OPCODE\n" ); 
			break;
		case CR_INDEXD_OPCODE:
			fprintf( fp, "CR_INDEXD_OPCODE\n" ); 
			break;
		case CR_INDEXF_OPCODE:
			fprintf( fp, "CR_INDEXF_OPCODE\n" ); 
			break;
		case CR_INDEXI_OPCODE:
			fprintf( fp, "CR_INDEXI_OPCODE\n" ); 
			break;
		case CR_INDEXS_OPCODE:
			fprintf( fp, "CR_INDEXS_OPCODE\n" ); 
			break;
		case CR_INDEXUB_OPCODE:
			fprintf( fp, "CR_INDEXUB_OPCODE\n" ); 
			break;
		case CR_INITNAMES_OPCODE:
			fprintf( fp, "CR_INITNAMES_OPCODE\n" ); 
			break;
		case CR_LIGHTMODELF_OPCODE:
			fprintf( fp, "CR_LIGHTMODELF_OPCODE\n" ); 
			break;
		case CR_LIGHTMODELFV_OPCODE:
			fprintf( fp, "CR_LIGHTMODELFV_OPCODE\n" ); 
			break;
		case CR_LIGHTMODELI_OPCODE:
			fprintf( fp, "CR_LIGHTMODELI_OPCODE\n" ); 
			break;
		case CR_LIGHTMODELIV_OPCODE:
			fprintf( fp, "CR_LIGHTMODELIV_OPCODE\n" ); 
			break;
		case CR_LIGHTF_OPCODE:
			fprintf( fp, "CR_LIGHTF_OPCODE\n" ); 
			break;
		case CR_LIGHTFV_OPCODE:
			fprintf( fp, "CR_LIGHTFV_OPCODE\n" ); 
			break;
		case CR_LIGHTI_OPCODE:
			fprintf( fp, "CR_LIGHTI_OPCODE\n" ); 
			break;
		case CR_LIGHTIV_OPCODE:
			fprintf( fp, "CR_LIGHTIV_OPCODE\n" ); 
			break;
		case CR_LINESTIPPLE_OPCODE:
			fprintf( fp, "CR_LINESTIPPLE_OPCODE\n" ); 
			break;
		case CR_LINEWIDTH_OPCODE:
			fprintf( fp, "CR_LINEWIDTH_OPCODE\n" ); 
			break;
		case CR_LOADIDENTITY_OPCODE:
			fprintf( fp, "CR_LOADIDENTITY_OPCODE\n" ); 
			break;
		case CR_LOADMATRIXD_OPCODE:
			fprintf( fp, "CR_LOADMATRIXD_OPCODE\n" ); 
			break;
		case CR_LOADMATRIXF_OPCODE:
			fprintf( fp, "CR_LOADMATRIXF_OPCODE\n" ); 
			break;
		case CR_LOADNAME_OPCODE:
			fprintf( fp, "CR_LOADNAME_OPCODE\n" ); 
			break;
		case CR_MAP1D_OPCODE:
			fprintf( fp, "CR_MAP1D_OPCODE\n" ); 
			break;
		case CR_MAP1F_OPCODE:
			fprintf( fp, "CR_MAP1F_OPCODE\n" ); 
			break;
		case CR_MAP2D_OPCODE:
			fprintf( fp, "CR_MAP2D_OPCODE\n" ); 
			break;
		case CR_MAP2F_OPCODE:
			fprintf( fp, "CR_MAP2F_OPCODE\n" ); 
			break;
		case CR_MAPGRID1D_OPCODE:
			fprintf( fp, "CR_MAPGRID1D_OPCODE\n" ); 
			break;
		case CR_MAPGRID1F_OPCODE:
			fprintf( fp, "CR_MAPGRID1F_OPCODE\n" ); 
			break;
		case CR_MAPGRID2D_OPCODE:
			fprintf( fp, "CR_MAPGRID2D_OPCODE\n" ); 
			break;
		case CR_MAPGRID2F_OPCODE:
			fprintf( fp, "CR_MAPGRID2F_OPCODE\n" ); 
			break;
		case CR_MATERIALF_OPCODE:
			fprintf( fp, "CR_MATERIALF_OPCODE\n" ); 
			break;
		case CR_MATERIALFV_OPCODE:
			fprintf( fp, "CR_MATERIALFV_OPCODE\n" ); 
			break;
		case CR_MATERIALI_OPCODE:
			fprintf( fp, "CR_MATERIALI_OPCODE\n" ); 
			break;
		case CR_MATERIALIV_OPCODE:
			fprintf( fp, "CR_MATERIALIV_OPCODE\n" ); 
			break;
		case CR_MATRIXMODE_OPCODE:
			fprintf( fp, "CR_MATRIXMODE_OPCODE\n" ); 
			break;
		case CR_MULTMATRIXD_OPCODE:
			fprintf( fp, "CR_MULTMATRIXD_OPCODE\n" ); 
			break;
		case CR_MULTMATRIXF_OPCODE:
			fprintf( fp, "CR_MULTMATRIXF_OPCODE\n" ); 
			break;
		case CR_MULTITEXCOORD1DARB_OPCODE:
			fprintf( fp, "CR_MULTITEXCOORD1DARB_OPCODE\n" ); 
			break;
		case CR_MULTITEXCOORD1FARB_OPCODE:
			fprintf( fp, "CR_MULTITEXCOORD1FARB_OPCODE\n" ); 
			break;
		case CR_MULTITEXCOORD1IARB_OPCODE:
			fprintf( fp, "CR_MULTITEXCOORD1IARB_OPCODE\n" ); 
			break;
		case CR_MULTITEXCOORD1SARB_OPCODE:
			fprintf( fp, "CR_MULTITEXCOORD1SARB_OPCODE\n" ); 
			break;
		case CR_MULTITEXCOORD2DARB_OPCODE:
			fprintf( fp, "CR_MULTITEXCOORD2DARB_OPCODE\n" ); 
			break;
		case CR_MULTITEXCOORD2FARB_OPCODE:
			fprintf( fp, "CR_MULTITEXCOORD2FARB_OPCODE\n" ); 
			break;
		case CR_MULTITEXCOORD2IARB_OPCODE:
			fprintf( fp, "CR_MULTITEXCOORD2IARB_OPCODE\n" ); 
			break;
		case CR_MULTITEXCOORD2SARB_OPCODE:
			fprintf( fp, "CR_MULTITEXCOORD2SARB_OPCODE\n" ); 
			break;
		case CR_MULTITEXCOORD3DARB_OPCODE:
			fprintf( fp, "CR_MULTITEXCOORD3DARB_OPCODE\n" ); 
			break;
		case CR_MULTITEXCOORD3FARB_OPCODE:
			fprintf( fp, "CR_MULTITEXCOORD3FARB_OPCODE\n" ); 
			break;
		case CR_MULTITEXCOORD3IARB_OPCODE:
			fprintf( fp, "CR_MULTITEXCOORD3IARB_OPCODE\n" ); 
			break;
		case CR_MULTITEXCOORD3SARB_OPCODE:
			fprintf( fp, "CR_MULTITEXCOORD3SARB_OPCODE\n" ); 
			break;
		case CR_MULTITEXCOORD4DARB_OPCODE:
			fprintf( fp, "CR_MULTITEXCOORD4DARB_OPCODE\n" ); 
			break;
		case CR_MULTITEXCOORD4FARB_OPCODE:
			fprintf( fp, "CR_MULTITEXCOORD4FARB_OPCODE\n" ); 
			break;
		case CR_MULTITEXCOORD4IARB_OPCODE:
			fprintf( fp, "CR_MULTITEXCOORD4IARB_OPCODE\n" ); 
			break;
		case CR_MULTITEXCOORD4SARB_OPCODE:
			fprintf( fp, "CR_MULTITEXCOORD4SARB_OPCODE\n" ); 
			break;
		case CR_NORMAL3B_OPCODE:
			fprintf( fp, "CR_NORMAL3B_OPCODE\n" ); 
			break;
		case CR_NORMAL3D_OPCODE:
			fprintf( fp, "CR_NORMAL3D_OPCODE\n" ); 
			break;
		case CR_NORMAL3F_OPCODE:
			fprintf( fp, "CR_NORMAL3F_OPCODE\n" ); 
			break;
		case CR_NORMAL3I_OPCODE:
			fprintf( fp, "CR_NORMAL3I_OPCODE\n" ); 
			break;
		case CR_NORMAL3S_OPCODE:
			fprintf( fp, "CR_NORMAL3S_OPCODE\n" ); 
			break;
		case CR_ORTHO_OPCODE:
			fprintf( fp, "CR_ORTHO_OPCODE\n" ); 
			break;
		case CR_PASSTHROUGH_OPCODE:
			fprintf( fp, "CR_PASSTHROUGH_OPCODE\n" ); 
			break;
		case CR_PIXELMAPFV_OPCODE:
			fprintf( fp, "CR_PIXELMAPFV_OPCODE\n" ); 
			break;
		case CR_PIXELMAPUIV_OPCODE:
			fprintf( fp, "CR_PIXELMAPUIV_OPCODE\n" ); 
			break;
		case CR_PIXELMAPUSV_OPCODE:
			fprintf( fp, "CR_PIXELMAPUSV_OPCODE\n" ); 
			break;
		case CR_PIXELSTOREF_OPCODE:
			fprintf( fp, "CR_PIXELSTOREF_OPCODE\n" ); 
			break;
		case CR_PIXELSTOREI_OPCODE:
			fprintf( fp, "CR_PIXELSTOREI_OPCODE\n" ); 
			break;
		case CR_PIXELTRANSFERF_OPCODE:
			fprintf( fp, "CR_PIXELTRANSFERF_OPCODE\n" ); 
			break;
		case CR_PIXELTRANSFERI_OPCODE:
			fprintf( fp, "CR_PIXELTRANSFERI_OPCODE\n" ); 
			break;
		case CR_PIXELZOOM_OPCODE:
			fprintf( fp, "CR_PIXELZOOM_OPCODE\n" ); 
			break;
		case CR_POINTSIZE_OPCODE:
			fprintf( fp, "CR_POINTSIZE_OPCODE\n" ); 
			break;
		case CR_POLYGONMODE_OPCODE:
			fprintf( fp, "CR_POLYGONMODE_OPCODE\n" ); 
			break;
		case CR_POLYGONOFFSET_OPCODE:
			fprintf( fp, "CR_POLYGONOFFSET_OPCODE\n" ); 
			break;
		case CR_POLYGONSTIPPLE_OPCODE:
			fprintf( fp, "CR_POLYGONSTIPPLE_OPCODE\n" ); 
			break;
		case CR_POPMATRIX_OPCODE:
			fprintf( fp, "CR_POPMATRIX_OPCODE\n" ); 
			break;
		case CR_POPNAME_OPCODE:
			fprintf( fp, "CR_POPNAME_OPCODE\n" ); 
			break;
		case CR_PRIORITIZETEXTURES_OPCODE:
			fprintf( fp, "CR_PRIORITIZETEXTURES_OPCODE\n" ); 
			break;
		case CR_PUSHMATRIX_OPCODE:
			fprintf( fp, "CR_PUSHMATRIX_OPCODE\n" ); 
			break;
		case CR_PUSHNAME_OPCODE:
			fprintf( fp, "CR_PUSHNAME_OPCODE\n" ); 
			break;
		case CR_RASTERPOS2D_OPCODE:
			fprintf( fp, "CR_RASTERPOS2D_OPCODE\n" ); 
			break;
		case CR_RASTERPOS2F_OPCODE:
			fprintf( fp, "CR_RASTERPOS2F_OPCODE\n" ); 
			break;
		case CR_RASTERPOS2I_OPCODE:
			fprintf( fp, "CR_RASTERPOS2I_OPCODE\n" ); 
			break;
		case CR_RASTERPOS2S_OPCODE:
			fprintf( fp, "CR_RASTERPOS2S_OPCODE\n" ); 
			break;
		case CR_RASTERPOS3D_OPCODE:
			fprintf( fp, "CR_RASTERPOS3D_OPCODE\n" ); 
			break;
		case CR_RASTERPOS3F_OPCODE:
			fprintf( fp, "CR_RASTERPOS3F_OPCODE\n" ); 
			break;
		case CR_RASTERPOS3I_OPCODE:
			fprintf( fp, "CR_RASTERPOS3I_OPCODE\n" ); 
			break;
		case CR_RASTERPOS3S_OPCODE:
			fprintf( fp, "CR_RASTERPOS3S_OPCODE\n" ); 
			break;
		case CR_RASTERPOS4D_OPCODE:
			fprintf( fp, "CR_RASTERPOS4D_OPCODE\n" ); 
			break;
		case CR_RASTERPOS4F_OPCODE:
			fprintf( fp, "CR_RASTERPOS4F_OPCODE\n" ); 
			break;
		case CR_RASTERPOS4I_OPCODE:
			fprintf( fp, "CR_RASTERPOS4I_OPCODE\n" ); 
			break;
		case CR_RASTERPOS4S_OPCODE:
			fprintf( fp, "CR_RASTERPOS4S_OPCODE\n" ); 
			break;
		case CR_READPIXELS_OPCODE:
			fprintf( fp, "CR_READPIXELS_OPCODE\n" ); 
			break;
		case CR_RECTD_OPCODE:
			fprintf( fp, "CR_RECTD_OPCODE\n" ); 
			break;
		case CR_RECTF_OPCODE:
			fprintf( fp, "CR_RECTF_OPCODE\n" ); 
			break;
		case CR_RECTI_OPCODE:
			fprintf( fp, "CR_RECTI_OPCODE\n" ); 
			break;
		case CR_RECTS_OPCODE:
			fprintf( fp, "CR_RECTS_OPCODE\n" ); 
			break;
		case CR_ROTATED_OPCODE:
			fprintf( fp, "CR_ROTATED_OPCODE\n" ); 
			break;
		case CR_ROTATEF_OPCODE:
			fprintf( fp, "CR_ROTATEF_OPCODE\n" ); 
			break;
		case CR_SCALED_OPCODE:
			fprintf( fp, "CR_SCALED_OPCODE\n" ); 
			break;
		case CR_SCALEF_OPCODE:
			fprintf( fp, "CR_SCALEF_OPCODE\n" ); 
			break;
		case CR_SCISSOR_OPCODE:
			fprintf( fp, "CR_SCISSOR_OPCODE\n" ); 
			break;
		case CR_SECONDARYCOLOR3BEXT_OPCODE:
			fprintf( fp, "CR_SECONDARYCOLOR3BEXT_OPCODE\n" ); 
			break;
		case CR_SECONDARYCOLOR3DEXT_OPCODE:
			fprintf( fp, "CR_SECONDARYCOLOR3DEXT_OPCODE\n" ); 
			break;
		case CR_SECONDARYCOLOR3FEXT_OPCODE:
			fprintf( fp, "CR_SECONDARYCOLOR3FEXT_OPCODE\n" ); 
			break;
		case CR_SECONDARYCOLOR3IEXT_OPCODE:
			fprintf( fp, "CR_SECONDARYCOLOR3IEXT_OPCODE\n" ); 
			break;
		case CR_SECONDARYCOLOR3SEXT_OPCODE:
			fprintf( fp, "CR_SECONDARYCOLOR3SEXT_OPCODE\n" ); 
			break;
		case CR_SECONDARYCOLOR3UBEXT_OPCODE:
			fprintf( fp, "CR_SECONDARYCOLOR3UBEXT_OPCODE\n" ); 
			break;
		case CR_SECONDARYCOLOR3UIEXT_OPCODE:
			fprintf( fp, "CR_SECONDARYCOLOR3UIEXT_OPCODE\n" ); 
			break;
		case CR_SECONDARYCOLOR3USEXT_OPCODE:
			fprintf( fp, "CR_SECONDARYCOLOR3USEXT_OPCODE\n" ); 
			break;
		case CR_SELECTBUFFER_OPCODE:
			fprintf( fp, "CR_SELECTBUFFER_OPCODE\n" ); 
			break;
		case CR_SHADEMODEL_OPCODE:
			fprintf( fp, "CR_SHADEMODEL_OPCODE\n" ); 
			break;
		case CR_STENCILFUNC_OPCODE:
			fprintf( fp, "CR_STENCILFUNC_OPCODE\n" ); 
			break;
		case CR_STENCILMASK_OPCODE:
			fprintf( fp, "CR_STENCILMASK_OPCODE\n" ); 
			break;
		case CR_STENCILOP_OPCODE:
			fprintf( fp, "CR_STENCILOP_OPCODE\n" ); 
			break;
		case CR_TEXCOORD1D_OPCODE:
			fprintf( fp, "CR_TEXCOORD1D_OPCODE\n" ); 
			break;
		case CR_TEXCOORD1F_OPCODE:
			fprintf( fp, "CR_TEXCOORD1F_OPCODE\n" ); 
			break;
		case CR_TEXCOORD1I_OPCODE:
			fprintf( fp, "CR_TEXCOORD1I_OPCODE\n" ); 
			break;
		case CR_TEXCOORD1S_OPCODE:
			fprintf( fp, "CR_TEXCOORD1S_OPCODE\n" ); 
			break;
		case CR_TEXCOORD2D_OPCODE:
			fprintf( fp, "CR_TEXCOORD2D_OPCODE\n" ); 
			break;
		case CR_TEXCOORD2F_OPCODE:
			fprintf( fp, "CR_TEXCOORD2F_OPCODE\n" ); 
			break;
		case CR_TEXCOORD2I_OPCODE:
			fprintf( fp, "CR_TEXCOORD2I_OPCODE\n" ); 
			break;
		case CR_TEXCOORD2S_OPCODE:
			fprintf( fp, "CR_TEXCOORD2S_OPCODE\n" ); 
			break;
		case CR_TEXCOORD3D_OPCODE:
			fprintf( fp, "CR_TEXCOORD3D_OPCODE\n" ); 
			break;
		case CR_TEXCOORD3F_OPCODE:
			fprintf( fp, "CR_TEXCOORD3F_OPCODE\n" ); 
			break;
		case CR_TEXCOORD3I_OPCODE:
			fprintf( fp, "CR_TEXCOORD3I_OPCODE\n" ); 
			break;
		case CR_TEXCOORD3S_OPCODE:
			fprintf( fp, "CR_TEXCOORD3S_OPCODE\n" ); 
			break;
		case CR_TEXCOORD4D_OPCODE:
			fprintf( fp, "CR_TEXCOORD4D_OPCODE\n" ); 
			break;
		case CR_TEXCOORD4F_OPCODE:
			fprintf( fp, "CR_TEXCOORD4F_OPCODE\n" ); 
			break;
		case CR_TEXCOORD4I_OPCODE:
			fprintf( fp, "CR_TEXCOORD4I_OPCODE\n" ); 
			break;
		case CR_TEXCOORD4S_OPCODE:
			fprintf( fp, "CR_TEXCOORD4S_OPCODE\n" ); 
			break;
		case CR_TEXENVFV_OPCODE:
			fprintf( fp, "CR_TEXENVFV_OPCODE\n" ); 
			break;
		case CR_TEXENVIV_OPCODE:
			fprintf( fp, "CR_TEXENVIV_OPCODE\n" ); 
			break;
		case CR_TEXGENDV_OPCODE:
			fprintf( fp, "CR_TEXGENDV_OPCODE\n" ); 
			break;
		case CR_TEXGENFV_OPCODE:
			fprintf( fp, "CR_TEXGENFV_OPCODE\n" ); 
			break;
		case CR_TEXGENIV_OPCODE:
			fprintf( fp, "CR_TEXGENIV_OPCODE\n" ); 
			break;
		case CR_TEXIMAGE1D_OPCODE:
			fprintf( fp, "CR_TEXIMAGE1D_OPCODE\n" ); 
			break;
		case CR_TEXIMAGE2D_OPCODE:
			fprintf( fp, "CR_TEXIMAGE2D_OPCODE\n" ); 
			break;
		case CR_TEXIMAGE3D_OPCODE:
			fprintf( fp, "CR_TEXIMAGE3D_OPCODE\n" ); 
			break;
		case CR_TEXIMAGE3DEXT_OPCODE:
			fprintf( fp, "CR_TEXIMAGE3DEXT_OPCODE\n" ); 
			break;
		case CR_TEXPARAMETERFV_OPCODE:
			fprintf( fp, "CR_TEXPARAMETERFV_OPCODE\n" ); 
			break;
		case CR_TEXPARAMETERIV_OPCODE:
			fprintf( fp, "CR_TEXPARAMETERIV_OPCODE\n" ); 
			break;
		case CR_TEXSUBIMAGE1D_OPCODE:
			fprintf( fp, "CR_TEXSUBIMAGE1D_OPCODE\n" ); 
			break;
		case CR_TEXSUBIMAGE2D_OPCODE:
			fprintf( fp, "CR_TEXSUBIMAGE2D_OPCODE\n" ); 
			break;
		case CR_TEXSUBIMAGE3D_OPCODE:
			fprintf( fp, "CR_TEXSUBIMAGE3D_OPCODE\n" ); 
			break;
		case CR_TRANSLATED_OPCODE:
			fprintf( fp, "CR_TRANSLATED_OPCODE\n" ); 
			break;
		case CR_TRANSLATEF_OPCODE:
			fprintf( fp, "CR_TRANSLATEF_OPCODE\n" ); 
			break;
		case CR_VERTEX2D_OPCODE:
			fprintf( fp, "CR_VERTEX2D_OPCODE\n" ); 
			break;
		case CR_VERTEX2F_OPCODE:
			fprintf( fp, "CR_VERTEX2F_OPCODE\n" ); 
			break;
		case CR_VERTEX2I_OPCODE:
			fprintf( fp, "CR_VERTEX2I_OPCODE\n" ); 
			break;
		case CR_VERTEX2S_OPCODE:
			fprintf( fp, "CR_VERTEX2S_OPCODE\n" ); 
			break;
		case CR_VERTEX3D_OPCODE:
			fprintf( fp, "CR_VERTEX3D_OPCODE\n" ); 
			break;
		case CR_VERTEX3F_OPCODE:
			fprintf( fp, "CR_VERTEX3F_OPCODE\n" ); 
			break;
		case CR_VERTEX3I_OPCODE:
			fprintf( fp, "CR_VERTEX3I_OPCODE\n" ); 
			break;
		case CR_VERTEX3S_OPCODE:
			fprintf( fp, "CR_VERTEX3S_OPCODE\n" ); 
			break;
		case CR_VERTEX4D_OPCODE:
			fprintf( fp, "CR_VERTEX4D_OPCODE\n" ); 
			break;
		case CR_VERTEX4F_OPCODE:
			fprintf( fp, "CR_VERTEX4F_OPCODE\n" ); 
			break;
		case CR_VERTEX4I_OPCODE:
			fprintf( fp, "CR_VERTEX4I_OPCODE\n" ); 
			break;
		case CR_VERTEX4S_OPCODE:
			fprintf( fp, "CR_VERTEX4S_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB1DARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB1DARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB1FARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB1FARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB1SARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB1SARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB2DARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB2DARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB2FARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB2FARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB2SARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB2SARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB3DARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB3DARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB3FARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB3FARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB3SARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB3SARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB4NBVARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB4NBVARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB4NIVARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB4NIVARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB4NSVARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB4NSVARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB4NUBARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB4NUBARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB4NUBVARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB4NUBVARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB4NUIVARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB4NUIVARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB4NUSVARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB4NUSVARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB4BVARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB4BVARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB4DARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB4DARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB4FARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB4FARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB4IVARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB4IVARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB4SARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB4SARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB4UBVARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB4UBVARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB4UIVARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB4UIVARB_OPCODE\n" ); 
			break;
		case CR_VERTEXATTRIB4USVARB_OPCODE:
			fprintf( fp, "CR_VERTEXATTRIB4USVARB_OPCODE\n" ); 
			break;
		case CR_VIEWPORT_OPCODE:
			fprintf( fp, "CR_VIEWPORT_OPCODE\n" ); 
			break;

		}
	}
}
