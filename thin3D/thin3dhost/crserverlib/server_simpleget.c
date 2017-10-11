/* Copyright (c) 2001, Stanford University
	All rights reserved.

	See the file LICENSE.txt for information on redistributing this software. */
	
#include "cr_spu.h"
#include "chromium.h"
#include "cr_error.h"
#include "cr_mem.h"
#include "cr_net.h"
#include "server_dispatch.h"
#include "server.h"


static struct nv_struct { GLenum pname; unsigned int num_values;
#ifdef VBOX_WITH_CRDUMPER 
const char* pszName;
#endif
} num_values_array[] = {


        	{ GL_ACCUM_ALPHA_BITS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_ACCUM_ALPHA_BITS"
#endif
        },
        

        	{ GL_ACCUM_BLUE_BITS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_ACCUM_BLUE_BITS"
#endif
        },
        

        	{ GL_ACCUM_CLEAR_VALUE, 4
#ifdef VBOX_WITH_CRDUMPER
            , "GL_ACCUM_CLEAR_VALUE"
#endif
        },
        

        	{ GL_ACCUM_GREEN_BITS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_ACCUM_GREEN_BITS"
#endif
        },
        

        	{ GL_ACCUM_RED_BITS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_ACCUM_RED_BITS"
#endif
        },
        
#ifdef CR_EXT_stencil_two_side

        	{ GL_ACTIVE_STENCIL_FACE_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_ACTIVE_STENCIL_FACE_EXT"
        #endif
        },
        
#endif /* CR_EXT_stencil_two_side */
#ifdef CR_ARB_multitexture

        	{ GL_ACTIVE_TEXTURE_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_ACTIVE_TEXTURE_ARB"
        #endif
        },
        
#endif /* CR_ARB_multitexture */
#ifdef CR_OPENGL_VERSION_1_2

        	{ GL_ALIASED_LINE_WIDTH_RANGE, 2
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_ALIASED_LINE_WIDTH_RANGE"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_1_2 */
#ifdef CR_OPENGL_VERSION_1_2

        	{ GL_ALIASED_POINT_SIZE_RANGE, 2
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_ALIASED_POINT_SIZE_RANGE"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_1_2 */

        	{ GL_ALPHA_BIAS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_ALPHA_BIAS"
#endif
        },
        

        	{ GL_ALPHA_BITS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_ALPHA_BITS"
#endif
        },
        

        	{ GL_ALPHA_SCALE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_ALPHA_SCALE"
#endif
        },
        

        	{ GL_ALPHA_TEST, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_ALPHA_TEST"
#endif
        },
        

        	{ GL_ALPHA_TEST_FUNC, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_ALPHA_TEST_FUNC"
#endif
        },
        

        	{ GL_ALPHA_TEST_REF, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_ALPHA_TEST_REF"
#endif
        },
        
#ifdef CR_ARB_vertex_buffer_object

        	{ GL_ARRAY_BUFFER_BINDING_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_ARRAY_BUFFER_BINDING_ARB"
        #endif
        },
        
#endif /* CR_ARB_vertex_buffer_object */

        	{ GL_ATTRIB_STACK_DEPTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_ATTRIB_STACK_DEPTH"
#endif
        },
        

        	{ GL_AUTO_NORMAL, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_AUTO_NORMAL"
#endif
        },
        

        	{ GL_AUX_BUFFERS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_AUX_BUFFERS"
#endif
        },
        

        	{ GL_BLEND, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_BLEND"
#endif
        },
        
#ifdef CR_EXT_blend_color

        	{ GL_BLEND_COLOR_EXT, 4
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_BLEND_COLOR_EXT"
        #endif
        },
        
#endif /* CR_EXT_blend_color */

        	{ GL_BLEND_DST, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_BLEND_DST"
#endif
        },
        
#ifdef CR_EXT_blend_func_separate

        	{ GL_BLEND_DST_ALPHA_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_BLEND_DST_ALPHA_EXT"
        #endif
        },
        
#endif /* CR_EXT_blend_func_separate */
#ifdef CR_EXT_blend_func_separate

        	{ GL_BLEND_DST_RGB_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_BLEND_DST_RGB_EXT"
        #endif
        },
        
#endif /* CR_EXT_blend_func_separate */
#ifdef CR_EXT_blend_minmax

        	{ GL_BLEND_EQUATION_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_BLEND_EQUATION_EXT"
        #endif
        },
        
#endif /* CR_EXT_blend_minmax */

        	{ GL_BLEND_SRC, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_BLEND_SRC"
#endif
        },
        
#ifdef CR_EXT_blend_func_separate

        	{ GL_BLEND_SRC_ALPHA_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_BLEND_SRC_ALPHA_EXT"
        #endif
        },
        
#endif /* CR_EXT_blend_func_separate */
#ifdef CR_EXT_blend_func_separate

        	{ GL_BLEND_SRC_RGB_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_BLEND_SRC_RGB_EXT"
        #endif
        },
        
#endif /* CR_EXT_blend_func_separate */

        	{ GL_BLUE_BIAS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_BLUE_BIAS"
#endif
        },
        

        	{ GL_BLUE_BITS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_BLUE_BITS"
#endif
        },
        

        	{ GL_BLUE_SCALE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_BLUE_SCALE"
#endif
        },
        
#ifdef CR_ARB_multitexture

        	{ GL_CLIENT_ACTIVE_TEXTURE_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_CLIENT_ACTIVE_TEXTURE_ARB"
        #endif
        },
        
#endif /* CR_ARB_multitexture */

        	{ GL_CLIENT_ATTRIB_STACK_DEPTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CLIENT_ATTRIB_STACK_DEPTH"
#endif
        },
        

        	{ GL_CLIP_PLANE0, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CLIP_PLANE0"
#endif
        },
        

        	{ GL_CLIP_PLANE1, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CLIP_PLANE1"
#endif
        },
        

        	{ GL_CLIP_PLANE2, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CLIP_PLANE2"
#endif
        },
        

        	{ GL_CLIP_PLANE3, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CLIP_PLANE3"
#endif
        },
        

        	{ GL_CLIP_PLANE4, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CLIP_PLANE4"
#endif
        },
        

        	{ GL_CLIP_PLANE5, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CLIP_PLANE5"
#endif
        },
        
#ifdef CR_EXT_clip_volume_hint

        	{ GL_CLIP_VOLUME_CLIPPING_HINT_EXT, 3
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_CLIP_VOLUME_CLIPPING_HINT_EXT"
        #endif
        },
        
#endif /* CR_EXT_clip_volume_hint */

        	{ GL_COLOR_ARRAY, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_COLOR_ARRAY"
#endif
        },
        
#ifdef CR_ARB_vertex_buffer_object

        	{ GL_COLOR_ARRAY_BUFFER_BINDING_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_COLOR_ARRAY_BUFFER_BINDING_ARB"
        #endif
        },
        
#endif /* CR_ARB_vertex_buffer_object */

        	{ GL_COLOR_ARRAY_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_COLOR_ARRAY_SIZE"
#endif
        },
        

        	{ GL_COLOR_ARRAY_STRIDE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_COLOR_ARRAY_STRIDE"
#endif
        },
        

        	{ GL_COLOR_ARRAY_TYPE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_COLOR_ARRAY_TYPE"
#endif
        },
        

        	{ GL_COLOR_CLEAR_VALUE, 4
#ifdef VBOX_WITH_CRDUMPER
            , "GL_COLOR_CLEAR_VALUE"
#endif
        },
        

        	{ GL_COLOR_LOGIC_OP, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_COLOR_LOGIC_OP"
#endif
        },
        

        	{ GL_COLOR_MATERIAL, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_COLOR_MATERIAL"
#endif
        },
        

        	{ GL_COLOR_MATERIAL_FACE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_COLOR_MATERIAL_FACE"
#endif
        },
        

        	{ GL_COLOR_MATERIAL_PARAMETER, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_COLOR_MATERIAL_PARAMETER"
#endif
        },
        

        	{ GL_COLOR_MATRIX, 16
#ifdef VBOX_WITH_CRDUMPER
            , "GL_COLOR_MATRIX"
#endif
        },
        

        	{ GL_COLOR_MATRIX_STACK_DEPTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_COLOR_MATRIX_STACK_DEPTH"
#endif
        },
        
#ifdef CR_NV_register_combiners

        	{ GL_COLOR_SUM_CLAMP_NV, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_COLOR_SUM_CLAMP_NV"
        #endif
        },
        
#endif /* CR_NV_register_combiners */
#ifdef CR_EXT_secondary_color

        	{ GL_COLOR_SUM_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_COLOR_SUM_EXT"
        #endif
        },
        
#endif /* CR_EXT_secondary_color */

        	{ GL_COLOR_TABLE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_COLOR_TABLE"
#endif
        },
        

        	{ GL_COLOR_WRITEMASK, 4
#ifdef VBOX_WITH_CRDUMPER
            , "GL_COLOR_WRITEMASK"
#endif
        },
        
#ifdef CR_NV_register_combiners

        	{ GL_CONSTANT_COLOR0_NV, 4
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_CONSTANT_COLOR0_NV"
        #endif
        },
        
#endif /* CR_NV_register_combiners */
#ifdef CR_NV_register_combiners

        	{ GL_CONSTANT_COLOR1_NV, 4
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_CONSTANT_COLOR1_NV"
        #endif
        },
        
#endif /* CR_NV_register_combiners */

        	{ GL_CONVOLUTION_1D, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CONVOLUTION_1D"
#endif
        },
        

        	{ GL_CONVOLUTION_2D, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CONVOLUTION_2D"
#endif
        },
        

        	{ GL_CULL_FACE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CULL_FACE"
#endif
        },
        

        	{ GL_CULL_FACE_MODE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CULL_FACE_MODE"
#endif
        },
        

        	{ GL_CURRENT_COLOR, 4
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CURRENT_COLOR"
#endif
        },
        
#ifdef CR_EXT_fog_coord

        	{ GL_CURRENT_FOG_COORDINATE_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_CURRENT_FOG_COORDINATE_EXT"
        #endif
        },
        
#endif /* CR_EXT_fog_coord */

        	{ GL_CURRENT_INDEX, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CURRENT_INDEX"
#endif
        },
        

        	{ GL_CURRENT_NORMAL, 3
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CURRENT_NORMAL"
#endif
        },
        
#ifdef CR_ARB_shader_objects

        	{ GL_CURRENT_PROGRAM, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_CURRENT_PROGRAM"
        #endif
        },
        
#endif /* CR_ARB_shader_objects */

        	{ GL_CURRENT_RASTER_COLOR, 4
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CURRENT_RASTER_COLOR"
#endif
        },
        

        	{ GL_CURRENT_RASTER_DISTANCE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CURRENT_RASTER_DISTANCE"
#endif
        },
        

        	{ GL_CURRENT_RASTER_INDEX, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CURRENT_RASTER_INDEX"
#endif
        },
        

        	{ GL_CURRENT_RASTER_POSITION, 4
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CURRENT_RASTER_POSITION"
#endif
        },
        

        	{ GL_CURRENT_RASTER_POSITION_VALID, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CURRENT_RASTER_POSITION_VALID"
#endif
        },
        

        	{ GL_CURRENT_RASTER_TEXTURE_COORDS, 4
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CURRENT_RASTER_TEXTURE_COORDS"
#endif
        },
        
#ifdef CR_EXT_secondary_color

        	{ GL_CURRENT_SECONDARY_COLOR_EXT, 4
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_CURRENT_SECONDARY_COLOR_EXT"
        #endif
        },
        
#endif /* CR_EXT_secondary_color */

        	{ GL_CURRENT_TEXTURE_COORDS, 4
#ifdef VBOX_WITH_CRDUMPER
            , "GL_CURRENT_TEXTURE_COORDS"
#endif
        },
        

        	{ GL_DEPTH_BIAS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_DEPTH_BIAS"
#endif
        },
        

        	{ GL_DEPTH_BITS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_DEPTH_BITS"
#endif
        },
        

        	{ GL_DEPTH_CLEAR_VALUE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_DEPTH_CLEAR_VALUE"
#endif
        },
        

        	{ GL_DEPTH_FUNC, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_DEPTH_FUNC"
#endif
        },
        

        	{ GL_DEPTH_RANGE, 2
#ifdef VBOX_WITH_CRDUMPER
            , "GL_DEPTH_RANGE"
#endif
        },
        

        	{ GL_DEPTH_SCALE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_DEPTH_SCALE"
#endif
        },
        

        	{ GL_DEPTH_TEST, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_DEPTH_TEST"
#endif
        },
        

        	{ GL_DEPTH_WRITEMASK, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_DEPTH_WRITEMASK"
#endif
        },
        

        	{ GL_DITHER, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_DITHER"
#endif
        },
        

        	{ GL_DOUBLEBUFFER, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_DOUBLEBUFFER"
#endif
        },
        

        	{ GL_DRAW_BUFFER, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_BUFFER"
#endif
        },
        
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_DRAW_BUFFER0, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_BUFFER0"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_DRAW_BUFFER1, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_BUFFER1"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_DRAW_BUFFER10, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_BUFFER10"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_DRAW_BUFFER11, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_BUFFER11"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_DRAW_BUFFER12, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_BUFFER12"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_DRAW_BUFFER13, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_BUFFER13"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_DRAW_BUFFER14, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_BUFFER14"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_DRAW_BUFFER15, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_BUFFER15"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_DRAW_BUFFER2, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_BUFFER2"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_DRAW_BUFFER3, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_BUFFER3"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_DRAW_BUFFER4, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_BUFFER4"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_DRAW_BUFFER5, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_BUFFER5"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_DRAW_BUFFER6, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_BUFFER6"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_DRAW_BUFFER7, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_BUFFER7"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_DRAW_BUFFER8, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_BUFFER8"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_DRAW_BUFFER9, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_BUFFER9"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_EXT_framebuffer_blit

        	{ GL_DRAW_FRAMEBUFFER_BINDING_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_DRAW_FRAMEBUFFER_BINDING_EXT"
        #endif
        },
        
#endif /* CR_EXT_framebuffer_blit */

        	{ GL_EDGE_FLAG, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_EDGE_FLAG"
#endif
        },
        

        	{ GL_EDGE_FLAG_ARRAY, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_EDGE_FLAG_ARRAY"
#endif
        },
        
#ifdef CR_ARB_vertex_buffer_object

        	{ GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB"
        #endif
        },
        
#endif /* CR_ARB_vertex_buffer_object */

        	{ GL_EDGE_FLAG_ARRAY_STRIDE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_EDGE_FLAG_ARRAY_STRIDE"
#endif
        },
        
#ifdef CR_ARB_vertex_buffer_object

        	{ GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB"
        #endif
        },
        
#endif /* CR_ARB_vertex_buffer_object */

        	{ GL_FEEDBACK_BUFFER_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_FEEDBACK_BUFFER_SIZE"
#endif
        },
        

        	{ GL_FEEDBACK_BUFFER_TYPE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_FEEDBACK_BUFFER_TYPE"
#endif
        },
        

        	{ GL_FOG, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_FOG"
#endif
        },
        

        	{ GL_FOG_COLOR, 4
#ifdef VBOX_WITH_CRDUMPER
            , "GL_FOG_COLOR"
#endif
        },
        
#ifdef CR_ARB_vertex_buffer_object

        	{ GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB"
        #endif
        },
        
#endif /* CR_ARB_vertex_buffer_object */
#ifdef CR_EXT_fog_coord

        	{ GL_FOG_COORDINATE_ARRAY_STRIDE_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_FOG_COORDINATE_ARRAY_STRIDE_EXT"
        #endif
        },
        
#endif /* CR_EXT_fog_coord */
#ifdef CR_EXT_fog_coord

        	{ GL_FOG_COORDINATE_ARRAY_TYPE_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_FOG_COORDINATE_ARRAY_TYPE_EXT"
        #endif
        },
        
#endif /* CR_EXT_fog_coord */

        	{ GL_FOG_DENSITY, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_FOG_DENSITY"
#endif
        },
        
#ifdef CR_NV_fog_distance

        	{ GL_FOG_DISTANCE_MODE_NV, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_FOG_DISTANCE_MODE_NV"
        #endif
        },
        
#endif /* CR_NV_fog_distance */

        	{ GL_FOG_END, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_FOG_END"
#endif
        },
        

        	{ GL_FOG_HINT, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_FOG_HINT"
#endif
        },
        

        	{ GL_FOG_INDEX, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_FOG_INDEX"
#endif
        },
        

        	{ GL_FOG_MODE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_FOG_MODE"
#endif
        },
        

        	{ GL_FOG_START, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_FOG_START"
#endif
        },
        
#ifdef CR_NV_fragment_program

        	{ GL_FRAGMENT_PROGRAM_BINDING_NV, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_FRAGMENT_PROGRAM_BINDING_NV"
        #endif
        },
        
#endif /* CR_NV_fragment_program */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_FRAGMENT_SHADER_DERIVATIVE_HINT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_FRAGMENT_SHADER_DERIVATIVE_HINT"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_EXT_framebuffer_object

        	{ GL_FRAMEBUFFER_BINDING_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_FRAMEBUFFER_BINDING_EXT"
        #endif
        },
        
#endif /* CR_EXT_framebuffer_object */

        	{ GL_FRONT_FACE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_FRONT_FACE"
#endif
        },
        
#ifdef CR_SGIS_generate_mipmap

        	{ GL_GENERATE_MIPMAP_HINT_SGIS, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_GENERATE_MIPMAP_HINT_SGIS"
        #endif
        },
        
#endif /* CR_SGIS_generate_mipmap */

        	{ GL_GREEN_BIAS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_GREEN_BIAS"
#endif
        },
        

        	{ GL_GREEN_BITS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_GREEN_BITS"
#endif
        },
        

        	{ GL_GREEN_SCALE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_GREEN_SCALE"
#endif
        },
        

        	{ GL_HISTOGRAM, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_HISTOGRAM"
#endif
        },
        

        	{ GL_INDEX_ARRAY, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_INDEX_ARRAY"
#endif
        },
        
#ifdef CR_ARB_vertex_buffer_object

        	{ GL_INDEX_ARRAY_BUFFER_BINDING_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_INDEX_ARRAY_BUFFER_BINDING_ARB"
        #endif
        },
        
#endif /* CR_ARB_vertex_buffer_object */

        	{ GL_INDEX_ARRAY_STRIDE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_INDEX_ARRAY_STRIDE"
#endif
        },
        

        	{ GL_INDEX_ARRAY_TYPE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_INDEX_ARRAY_TYPE"
#endif
        },
        

        	{ GL_INDEX_BITS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_INDEX_BITS"
#endif
        },
        

        	{ GL_INDEX_CLEAR_VALUE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_INDEX_CLEAR_VALUE"
#endif
        },
        

        	{ GL_INDEX_LOGIC_OP, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_INDEX_LOGIC_OP"
#endif
        },
        

        	{ GL_INDEX_MODE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_INDEX_MODE"
#endif
        },
        

        	{ GL_INDEX_OFFSET, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_INDEX_OFFSET"
#endif
        },
        

        	{ GL_INDEX_SHIFT, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_INDEX_SHIFT"
#endif
        },
        

        	{ GL_INDEX_WRITEMASK, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_INDEX_WRITEMASK"
#endif
        },
        

        	{ GL_LIGHT0, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LIGHT0"
#endif
        },
        

        	{ GL_LIGHT1, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LIGHT1"
#endif
        },
        

        	{ GL_LIGHT2, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LIGHT2"
#endif
        },
        

        	{ GL_LIGHT3, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LIGHT3"
#endif
        },
        

        	{ GL_LIGHT4, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LIGHT4"
#endif
        },
        

        	{ GL_LIGHT5, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LIGHT5"
#endif
        },
        

        	{ GL_LIGHT6, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LIGHT6"
#endif
        },
        

        	{ GL_LIGHT7, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LIGHT7"
#endif
        },
        

        	{ GL_LIGHTING, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LIGHTING"
#endif
        },
        

        	{ GL_LIGHT_MODEL_AMBIENT, 4
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LIGHT_MODEL_AMBIENT"
#endif
        },
        
#ifdef CR_OPENGL_VERSION_1_2

        	{ GL_LIGHT_MODEL_COLOR_CONTROL, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_LIGHT_MODEL_COLOR_CONTROL"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_1_2 */
#ifdef CR_EXT_separate_specular_color

        	{ GL_LIGHT_MODEL_COLOR_CONTROL_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_LIGHT_MODEL_COLOR_CONTROL_EXT"
        #endif
        },
        
#endif /* CR_EXT_separate_specular_color */

        	{ GL_LIGHT_MODEL_LOCAL_VIEWER, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LIGHT_MODEL_LOCAL_VIEWER"
#endif
        },
        

        	{ GL_LIGHT_MODEL_TWO_SIDE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LIGHT_MODEL_TWO_SIDE"
#endif
        },
        

        	{ GL_LINE_SMOOTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LINE_SMOOTH"
#endif
        },
        

        	{ GL_LINE_SMOOTH_HINT, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LINE_SMOOTH_HINT"
#endif
        },
        

        	{ GL_LINE_STIPPLE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LINE_STIPPLE"
#endif
        },
        

        	{ GL_LINE_STIPPLE_PATTERN, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LINE_STIPPLE_PATTERN"
#endif
        },
        

        	{ GL_LINE_STIPPLE_REPEAT, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LINE_STIPPLE_REPEAT"
#endif
        },
        

        	{ GL_LINE_WIDTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LINE_WIDTH"
#endif
        },
        

        	{ GL_LINE_WIDTH_GRANULARITY, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LINE_WIDTH_GRANULARITY"
#endif
        },
        

        	{ GL_LINE_WIDTH_RANGE, 2
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LINE_WIDTH_RANGE"
#endif
        },
        

        	{ GL_LIST_BASE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LIST_BASE"
#endif
        },
        

        	{ GL_LIST_INDEX, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LIST_INDEX"
#endif
        },
        

        	{ GL_LIST_MODE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LIST_MODE"
#endif
        },
        

        	{ GL_LOGIC_OP_MODE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_LOGIC_OP_MODE"
#endif
        },
        

        	{ GL_MAP1_COLOR_4, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP1_COLOR_4"
#endif
        },
        

        	{ GL_MAP1_GRID_DOMAIN, 2
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP1_GRID_DOMAIN"
#endif
        },
        

        	{ GL_MAP1_GRID_SEGMENTS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP1_GRID_SEGMENTS"
#endif
        },
        

        	{ GL_MAP1_INDEX, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP1_INDEX"
#endif
        },
        

        	{ GL_MAP1_NORMAL, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP1_NORMAL"
#endif
        },
        

        	{ GL_MAP1_TEXTURE_COORD_1, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP1_TEXTURE_COORD_1"
#endif
        },
        

        	{ GL_MAP1_TEXTURE_COORD_2, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP1_TEXTURE_COORD_2"
#endif
        },
        

        	{ GL_MAP1_TEXTURE_COORD_3, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP1_TEXTURE_COORD_3"
#endif
        },
        

        	{ GL_MAP1_TEXTURE_COORD_4, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP1_TEXTURE_COORD_4"
#endif
        },
        

        	{ GL_MAP1_VERTEX_3, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP1_VERTEX_3"
#endif
        },
        

        	{ GL_MAP1_VERTEX_4, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP1_VERTEX_4"
#endif
        },
        

        	{ GL_MAP2_COLOR_4, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP2_COLOR_4"
#endif
        },
        

        	{ GL_MAP2_GRID_DOMAIN, 4
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP2_GRID_DOMAIN"
#endif
        },
        

        	{ GL_MAP2_GRID_SEGMENTS, 2
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP2_GRID_SEGMENTS"
#endif
        },
        

        	{ GL_MAP2_INDEX, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP2_INDEX"
#endif
        },
        

        	{ GL_MAP2_NORMAL, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP2_NORMAL"
#endif
        },
        

        	{ GL_MAP2_TEXTURE_COORD_1, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP2_TEXTURE_COORD_1"
#endif
        },
        

        	{ GL_MAP2_TEXTURE_COORD_2, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP2_TEXTURE_COORD_2"
#endif
        },
        

        	{ GL_MAP2_TEXTURE_COORD_3, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP2_TEXTURE_COORD_3"
#endif
        },
        

        	{ GL_MAP2_TEXTURE_COORD_4, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP2_TEXTURE_COORD_4"
#endif
        },
        

        	{ GL_MAP2_VERTEX_3, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP2_VERTEX_3"
#endif
        },
        

        	{ GL_MAP2_VERTEX_4, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP2_VERTEX_4"
#endif
        },
        

        	{ GL_MAP_COLOR, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP_COLOR"
#endif
        },
        

        	{ GL_MAP_STENCIL, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAP_STENCIL"
#endif
        },
        

        	{ GL_MATRIX_MODE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MATRIX_MODE"
#endif
        },
        

        	{ GL_MAX_3D_TEXTURE_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_3D_TEXTURE_SIZE"
#endif
        },
        

        	{ GL_MAX_ATTRIB_STACK_DEPTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_ATTRIB_STACK_DEPTH"
#endif
        },
        

        	{ GL_MAX_CLIENT_ATTRIB_STACK_DEPTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_CLIENT_ATTRIB_STACK_DEPTH"
#endif
        },
        

        	{ GL_MAX_CLIP_PLANES, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_CLIP_PLANES"
#endif
        },
        
#ifdef CR_EXT_framebuffer_object

        	{ GL_MAX_COLOR_ATTACHMENTS_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_COLOR_ATTACHMENTS_EXT"
        #endif
        },
        
#endif /* CR_EXT_framebuffer_object */

        	{ GL_MAX_COLOR_MATRIX_STACK_DEPTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_COLOR_MATRIX_STACK_DEPTH"
#endif
        },
        
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */

        	{ GL_MAX_CONVOLUTION_HEIGHT, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_CONVOLUTION_HEIGHT"
#endif
        },
        

        	{ GL_MAX_CONVOLUTION_WIDTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_CONVOLUTION_WIDTH"
#endif
        },
        
#ifdef CR_ARB_texture_cube_map

        	{ GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB"
        #endif
        },
        
#endif /* CR_ARB_texture_cube_map */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_MAX_DRAW_BUFFERS, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_DRAW_BUFFERS"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_1_2

        	{ GL_MAX_ELEMENTS_INDICES, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_ELEMENTS_INDICES"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_1_2 */
#ifdef CR_OPENGL_VERSION_1_2

        	{ GL_MAX_ELEMENTS_VERTICES, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_ELEMENTS_VERTICES"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_1_2 */

        	{ GL_MAX_EVAL_ORDER, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_EVAL_ORDER"
#endif
        },
        
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_NV_register_combiners

        	{ GL_MAX_GENERAL_COMBINERS_NV, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_GENERAL_COMBINERS_NV"
        #endif
        },
        
#endif /* CR_NV_register_combiners */

        	{ GL_MAX_LIGHTS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_LIGHTS"
#endif
        },
        

        	{ GL_MAX_LIST_NESTING, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_LIST_NESTING"
#endif
        },
        

        	{ GL_MAX_MODELVIEW_STACK_DEPTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_MODELVIEW_STACK_DEPTH"
#endif
        },
        

        	{ GL_MAX_NAME_STACK_DEPTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_NAME_STACK_DEPTH"
#endif
        },
        

        	{ GL_MAX_PIXEL_MAP_TABLE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_PIXEL_MAP_TABLE"
#endif
        },
        
#ifdef CR_ARB_vertex_program

        	{ GL_MAX_PROGRAM_MATRICES_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_PROGRAM_MATRICES_ARB"
        #endif
        },
        
#endif /* CR_ARB_vertex_program */
#ifdef CR_ARB_vertex_program

        	{ GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_PROGRAM_MATRIX_STACK_DEPTH_ARB"
        #endif
        },
        
#endif /* CR_ARB_vertex_program */

        	{ GL_MAX_PROJECTION_STACK_DEPTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_PROJECTION_STACK_DEPTH"
#endif
        },
        
#ifdef CR_NV_texture_rectangle

        	{ GL_MAX_RECTANGLE_TEXTURE_SIZE_NV, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_RECTANGLE_TEXTURE_SIZE_NV"
        #endif
        },
        
#endif /* CR_NV_texture_rectangle */
#ifdef CR_EXT_framebuffer_object

        	{ GL_MAX_RENDERBUFFER_SIZE_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_RENDERBUFFER_SIZE_EXT"
        #endif
        },
        
#endif /* CR_EXT_framebuffer_object */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_MAX_TEXTURE_COORDS, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_TEXTURE_COORDS"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_ARB_vertex_program

        	{ GL_MAX_TEXTURE_COORDS_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_TEXTURE_COORDS_ARB"
        #endif
        },
        
#endif /* CR_ARB_vertex_program */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_MAX_TEXTURE_IMAGE_UNITS, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_TEXTURE_IMAGE_UNITS"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_ARB_fragment_program

        	{ GL_MAX_TEXTURE_IMAGE_UNITS_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_TEXTURE_IMAGE_UNITS_ARB"
        #endif
        },
        
#endif /* CR_ARB_fragment_program */
#ifdef CR_EXT_texture_lod_bias

        	{ GL_MAX_TEXTURE_LOD_BIAS_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_TEXTURE_LOD_BIAS_EXT"
        #endif
        },
        
#endif /* CR_EXT_texture_lod_bias */
#ifdef CR_EXT_texture_filter_anisotropic

        	{ GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT"
        #endif
        },
        
#endif /* CR_EXT_texture_filter_anisotropic */

        	{ GL_MAX_TEXTURE_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_TEXTURE_SIZE"
#endif
        },
        

        	{ GL_MAX_TEXTURE_STACK_DEPTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_TEXTURE_STACK_DEPTH"
#endif
        },
        
#ifdef CR_ARB_multitexture

        	{ GL_MAX_TEXTURE_UNITS_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_TEXTURE_UNITS_ARB"
        #endif
        },
        
#endif /* CR_ARB_multitexture */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_MAX_VARYING_FLOATS, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_VARYING_FLOATS"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_MAX_VERTEX_ATTRIBS, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_VERTEX_ATTRIBS"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_ARB_vertex_program

        	{ GL_MAX_VERTEX_ATTRIBS_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_VERTEX_ATTRIBS_ARB"
        #endif
        },
        
#endif /* CR_ARB_vertex_program */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_MAX_VERTEX_UNIFORM_COMPONENTS, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_VERTEX_UNIFORM_COMPONENTS"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */

        	{ GL_MAX_VIEWPORT_DIMS, 2
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MAX_VIEWPORT_DIMS"
#endif
        },
        

        	{ GL_MINMAX, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MINMAX"
#endif
        },
        

        	{ GL_MODELVIEW_MATRIX, 16
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MODELVIEW_MATRIX"
#endif
        },
        

        	{ GL_MODELVIEW_STACK_DEPTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_MODELVIEW_STACK_DEPTH"
#endif
        },
        
#ifdef CR_ARB_multisample

        	{ GL_MULTISAMPLE_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_MULTISAMPLE_ARB"
        #endif
        },
        
#endif /* CR_ARB_multisample */

        	{ GL_NAME_STACK_DEPTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_NAME_STACK_DEPTH"
#endif
        },
        

        	{ GL_NORMALIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_NORMALIZE"
#endif
        },
        

        	{ GL_NORMAL_ARRAY, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_NORMAL_ARRAY"
#endif
        },
        
#ifdef CR_ARB_vertex_buffer_object

        	{ GL_NORMAL_ARRAY_BUFFER_BINDING_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_NORMAL_ARRAY_BUFFER_BINDING_ARB"
        #endif
        },
        
#endif /* CR_ARB_vertex_buffer_object */

        	{ GL_NORMAL_ARRAY_STRIDE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_NORMAL_ARRAY_STRIDE"
#endif
        },
        

        	{ GL_NORMAL_ARRAY_TYPE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_NORMAL_ARRAY_TYPE"
#endif
        },
        
#ifdef CR_ARB_texture_compression

        	{ GL_NUM_COMPRESSED_TEXTURE_FORMATS, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_NUM_COMPRESSED_TEXTURE_FORMATS"
        #endif
        },
        
#endif /* CR_ARB_texture_compression */
#ifdef CR_ARB_texture_compression

        	{ GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB"
        #endif
        },
        
#endif /* CR_ARB_texture_compression */
#ifdef CR_NV_register_combiners

        	{ GL_NUM_GENERAL_COMBINERS_NV, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_NUM_GENERAL_COMBINERS_NV"
        #endif
        },
        
#endif /* CR_NV_register_combiners */

        	{ GL_PACK_ALIGNMENT, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PACK_ALIGNMENT"
#endif
        },
        
#ifdef CR_OPENGL_VERSION_1_2

        	{ GL_PACK_IMAGE_HEIGHT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_PACK_IMAGE_HEIGHT"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_1_2 */

        	{ GL_PACK_LSB_FIRST, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PACK_LSB_FIRST"
#endif
        },
        

        	{ GL_PACK_ROW_LENGTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PACK_ROW_LENGTH"
#endif
        },
        
#ifdef CR_OPENGL_VERSION_1_2

        	{ GL_PACK_SKIP_IMAGES, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_PACK_SKIP_IMAGES"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_1_2 */

        	{ GL_PACK_SKIP_PIXELS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PACK_SKIP_PIXELS"
#endif
        },
        

        	{ GL_PACK_SKIP_ROWS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PACK_SKIP_ROWS"
#endif
        },
        

        	{ GL_PACK_SWAP_BYTES, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PACK_SWAP_BYTES"
#endif
        },
        

        	{ GL_PERSPECTIVE_CORRECTION_HINT, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PERSPECTIVE_CORRECTION_HINT"
#endif
        },
        
#ifdef CR_NV_register_combiners2

        	{ GL_PER_STAGE_CONSTANTS_NV, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_PER_STAGE_CONSTANTS_NV"
        #endif
        },
        
#endif /* CR_NV_register_combiners2 */

        	{ GL_PIXEL_MAP_A_TO_A_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PIXEL_MAP_A_TO_A_SIZE"
#endif
        },
        

        	{ GL_PIXEL_MAP_B_TO_B_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PIXEL_MAP_B_TO_B_SIZE"
#endif
        },
        

        	{ GL_PIXEL_MAP_G_TO_G_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PIXEL_MAP_G_TO_G_SIZE"
#endif
        },
        

        	{ GL_PIXEL_MAP_I_TO_A_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PIXEL_MAP_I_TO_A_SIZE"
#endif
        },
        

        	{ GL_PIXEL_MAP_I_TO_B_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PIXEL_MAP_I_TO_B_SIZE"
#endif
        },
        

        	{ GL_PIXEL_MAP_I_TO_G_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PIXEL_MAP_I_TO_G_SIZE"
#endif
        },
        

        	{ GL_PIXEL_MAP_I_TO_I_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PIXEL_MAP_I_TO_I_SIZE"
#endif
        },
        

        	{ GL_PIXEL_MAP_I_TO_R_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PIXEL_MAP_I_TO_R_SIZE"
#endif
        },
        

        	{ GL_PIXEL_MAP_R_TO_R_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PIXEL_MAP_R_TO_R_SIZE"
#endif
        },
        

        	{ GL_PIXEL_MAP_S_TO_S_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PIXEL_MAP_S_TO_S_SIZE"
#endif
        },
        

        	{ GL_POINT_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POINT_SIZE"
#endif
        },
        

        	{ GL_POINT_SIZE_GRANULARITY, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POINT_SIZE_GRANULARITY"
#endif
        },
        

        	{ GL_POINT_SIZE_RANGE, 2
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POINT_SIZE_RANGE"
#endif
        },
        

        	{ GL_POINT_SMOOTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POINT_SMOOTH"
#endif
        },
        

        	{ GL_POINT_SMOOTH_HINT, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POINT_SMOOTH_HINT"
#endif
        },
        
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_POINT_SPRITE, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_POINT_SPRITE"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_ARB_point_sprite

        	{ GL_POINT_SPRITE_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_POINT_SPRITE_ARB"
        #endif
        },
        
#endif /* CR_ARB_point_sprite */

        	{ GL_POLYGON_MODE, 2
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POLYGON_MODE"
#endif
        },
        

        	{ GL_POLYGON_OFFSET_FACTOR, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POLYGON_OFFSET_FACTOR"
#endif
        },
        

        	{ GL_POLYGON_OFFSET_FILL, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POLYGON_OFFSET_FILL"
#endif
        },
        

        	{ GL_POLYGON_OFFSET_LINE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POLYGON_OFFSET_LINE"
#endif
        },
        

        	{ GL_POLYGON_OFFSET_POINT, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POLYGON_OFFSET_POINT"
#endif
        },
        

        	{ GL_POLYGON_OFFSET_UNITS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POLYGON_OFFSET_UNITS"
#endif
        },
        

        	{ GL_POLYGON_SMOOTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POLYGON_SMOOTH"
#endif
        },
        

        	{ GL_POLYGON_SMOOTH_HINT, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POLYGON_SMOOTH_HINT"
#endif
        },
        

        	{ GL_POLYGON_STIPPLE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POLYGON_STIPPLE"
#endif
        },
        

        	{ GL_POST_COLOR_MATRIX_COLOR_TABLE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POST_COLOR_MATRIX_COLOR_TABLE"
#endif
        },
        

        	{ GL_POST_CONVOLUTION_ALPHA_BIAS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POST_CONVOLUTION_ALPHA_BIAS"
#endif
        },
        

        	{ GL_POST_CONVOLUTION_ALPHA_SCALE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POST_CONVOLUTION_ALPHA_SCALE"
#endif
        },
        

        	{ GL_POST_CONVOLUTION_BLUE_BIAS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POST_CONVOLUTION_BLUE_BIAS"
#endif
        },
        

        	{ GL_POST_CONVOLUTION_BLUE_SCALE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POST_CONVOLUTION_BLUE_SCALE"
#endif
        },
        

        	{ GL_POST_CONVOLUTION_COLOR_TABLE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POST_CONVOLUTION_COLOR_TABLE"
#endif
        },
        

        	{ GL_POST_CONVOLUTION_GREEN_BIAS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POST_CONVOLUTION_GREEN_BIAS"
#endif
        },
        

        	{ GL_POST_CONVOLUTION_GREEN_SCALE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POST_CONVOLUTION_GREEN_SCALE"
#endif
        },
        

        	{ GL_POST_CONVOLUTION_RED_BIAS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POST_CONVOLUTION_RED_BIAS"
#endif
        },
        

        	{ GL_POST_CONVOLUTION_RED_SCALE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_POST_CONVOLUTION_RED_SCALE"
#endif
        },
        
#ifdef CR_NV_fragment_program

        	{ GL_PROGRAM_ERROR_POSITION_NV, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_PROGRAM_ERROR_POSITION_NV"
        #endif
        },
        
#endif /* CR_NV_fragment_program */

        	{ GL_PROJECTION_MATRIX, 16
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PROJECTION_MATRIX"
#endif
        },
        

        	{ GL_PROJECTION_STACK_DEPTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PROJECTION_STACK_DEPTH"
#endif
        },
        

        	{ GL_PROXY_COLOR_TABLE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_PROXY_COLOR_TABLE"
#endif
        },
        
#ifdef CR_IBM_rasterpos_clip

        	{ GL_RASTER_POSITION_UNCLIPPED_IBM, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_RASTER_POSITION_UNCLIPPED_IBM"
        #endif
        },
        
#endif /* CR_IBM_rasterpos_clip */

        	{ GL_READ_BUFFER, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_READ_BUFFER"
#endif
        },
        
#ifdef CR_EXT_framebuffer_blit

        	{ GL_READ_FRAMEBUFFER_BINDING_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_READ_FRAMEBUFFER_BINDING_EXT"
        #endif
        },
        
#endif /* CR_EXT_framebuffer_blit */

        	{ GL_RED_BIAS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_RED_BIAS"
#endif
        },
        

        	{ GL_RED_BITS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_RED_BITS"
#endif
        },
        

        	{ GL_RED_SCALE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_RED_SCALE"
#endif
        },
        
#ifdef CR_EXT_framebuffer_object

        	{ GL_RENDERBUFFER_BINDING_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_RENDERBUFFER_BINDING_EXT"
        #endif
        },
        
#endif /* CR_EXT_framebuffer_object */

        	{ GL_RENDER_MODE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_RENDER_MODE"
#endif
        },
        
#ifdef CR_OPENGL_VERSION_1_2

        	{ GL_RESCALE_NORMAL, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_RESCALE_NORMAL"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_1_2 */

        	{ GL_RGBA_MODE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_RGBA_MODE"
#endif
        },
        
#ifdef CR_ARB_multisample

        	{ GL_SAMPLES_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_SAMPLES_ARB"
        #endif
        },
        
#endif /* CR_ARB_multisample */
#ifdef CR_ARB_multisample

        	{ GL_SAMPLE_ALPHA_TO_COVERAGE_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_SAMPLE_ALPHA_TO_COVERAGE_ARB"
        #endif
        },
        
#endif /* CR_ARB_multisample */
#ifdef CR_ARB_multisample

        	{ GL_SAMPLE_ALPHA_TO_ONE_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_SAMPLE_ALPHA_TO_ONE_ARB"
        #endif
        },
        
#endif /* CR_ARB_multisample */
#ifdef CR_ARB_multisample

        	{ GL_SAMPLE_BUFFERS_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_SAMPLE_BUFFERS_ARB"
        #endif
        },
        
#endif /* CR_ARB_multisample */
#ifdef CR_ARB_multisample

        	{ GL_SAMPLE_COVERAGE_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_SAMPLE_COVERAGE_ARB"
        #endif
        },
        
#endif /* CR_ARB_multisample */
#ifdef CR_ARB_multisample

        	{ GL_SAMPLE_COVERAGE_INVERT_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_SAMPLE_COVERAGE_INVERT_ARB"
        #endif
        },
        
#endif /* CR_ARB_multisample */
#ifdef CR_ARB_multisample

        	{ GL_SAMPLE_COVERAGE_VALUE_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_SAMPLE_COVERAGE_VALUE_ARB"
        #endif
        },
        
#endif /* CR_ARB_multisample */

        	{ GL_SCISSOR_BOX, 4
#ifdef VBOX_WITH_CRDUMPER
            , "GL_SCISSOR_BOX"
#endif
        },
        

        	{ GL_SCISSOR_TEST, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_SCISSOR_TEST"
#endif
        },
        
#ifdef CR_ARB_vertex_buffer_object

        	{ GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB"
        #endif
        },
        
#endif /* CR_ARB_vertex_buffer_object */
#ifdef CR_EXT_secondary_color

        	{ GL_SECONDARY_COLOR_ARRAY_SIZE_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_SECONDARY_COLOR_ARRAY_SIZE_EXT"
        #endif
        },
        
#endif /* CR_EXT_secondary_color */
#ifdef CR_EXT_secondary_color

        	{ GL_SECONDARY_COLOR_ARRAY_STRIDE_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_SECONDARY_COLOR_ARRAY_STRIDE_EXT"
        #endif
        },
        
#endif /* CR_EXT_secondary_color */
#ifdef CR_EXT_secondary_color

        	{ GL_SECONDARY_COLOR_ARRAY_TYPE_EXT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_SECONDARY_COLOR_ARRAY_TYPE_EXT"
        #endif
        },
        
#endif /* CR_EXT_secondary_color */

        	{ GL_SELECTION_BUFFER_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_SELECTION_BUFFER_SIZE"
#endif
        },
        

        	{ GL_SEPARABLE_2D, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_SEPARABLE_2D"
#endif
        },
        

        	{ GL_SHADE_MODEL, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_SHADE_MODEL"
#endif
        },
        
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_STENCIL_BACK_FAIL, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_STENCIL_BACK_FAIL"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_STENCIL_BACK_FUNC, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_STENCIL_BACK_FUNC"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_STENCIL_BACK_PASS_DEPTH_FAIL, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_STENCIL_BACK_PASS_DEPTH_FAIL"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_STENCIL_BACK_PASS_DEPTH_PASS, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_STENCIL_BACK_PASS_DEPTH_PASS"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_STENCIL_BACK_REF, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_STENCIL_BACK_REF"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_STENCIL_BACK_VALUE_MASK, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_STENCIL_BACK_VALUE_MASK"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */

        	{ GL_STENCIL_BITS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_STENCIL_BITS"
#endif
        },
        

        	{ GL_STENCIL_CLEAR_VALUE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_STENCIL_CLEAR_VALUE"
#endif
        },
        

        	{ GL_STENCIL_FAIL, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_STENCIL_FAIL"
#endif
        },
        

        	{ GL_STENCIL_FUNC, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_STENCIL_FUNC"
#endif
        },
        

        	{ GL_STENCIL_PASS_DEPTH_FAIL, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_STENCIL_PASS_DEPTH_FAIL"
#endif
        },
        

        	{ GL_STENCIL_PASS_DEPTH_PASS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_STENCIL_PASS_DEPTH_PASS"
#endif
        },
        

        	{ GL_STENCIL_REF, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_STENCIL_REF"
#endif
        },
        

        	{ GL_STENCIL_TEST, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_STENCIL_TEST"
#endif
        },
        

        	{ GL_STENCIL_VALUE_MASK, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_STENCIL_VALUE_MASK"
#endif
        },
        

        	{ GL_STENCIL_WRITEMASK, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_STENCIL_WRITEMASK"
#endif
        },
        

        	{ GL_STEREO, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_STEREO"
#endif
        },
        

        	{ GL_SUBPIXEL_BITS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_SUBPIXEL_BITS"
#endif
        },
        

        	{ GL_TEXTURE_1D, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_1D"
#endif
        },
        

        	{ GL_TEXTURE_2D, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_2D"
#endif
        },
        
#ifdef CR_OPENGL_VERSION_1_2

        	{ GL_TEXTURE_3D, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_3D"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_1_2 */

        	{ GL_TEXTURE_BINDING_1D, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_BINDING_1D"
#endif
        },
        

        	{ GL_TEXTURE_BINDING_2D, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_BINDING_2D"
#endif
        },
        

        	{ GL_TEXTURE_BINDING_3D, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_BINDING_3D"
#endif
        },
        
#ifdef CR_ARB_texture_cube_map

        	{ GL_TEXTURE_BINDING_CUBE_MAP_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_BINDING_CUBE_MAP_ARB"
        #endif
        },
        
#endif /* CR_ARB_texture_cube_map */
#ifdef CR_NV_texture_rectangle

        	{ GL_TEXTURE_BINDING_RECTANGLE_NV, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_BINDING_RECTANGLE_NV"
        #endif
        },
        
#endif /* CR_NV_texture_rectangle */

        	{ GL_TEXTURE_COORD_ARRAY, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_COORD_ARRAY"
#endif
        },
        
#ifdef CR_ARB_vertex_buffer_object

        	{ GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB"
        #endif
        },
        
#endif /* CR_ARB_vertex_buffer_object */

        	{ GL_TEXTURE_COORD_ARRAY_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_COORD_ARRAY_SIZE"
#endif
        },
        

        	{ GL_TEXTURE_COORD_ARRAY_STRIDE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_COORD_ARRAY_STRIDE"
#endif
        },
        

        	{ GL_TEXTURE_COORD_ARRAY_TYPE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_COORD_ARRAY_TYPE"
#endif
        },
        
#ifdef CR_ARB_texture_cube_map

        	{ GL_TEXTURE_CUBE_MAP_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_CUBE_MAP_ARB"
        #endif
        },
        
#endif /* CR_ARB_texture_cube_map */

        	{ GL_TEXTURE_ENV_COLOR, 4
#ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_ENV_COLOR"
#endif
        },
        

        	{ GL_TEXTURE_ENV_MODE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_ENV_MODE"
#endif
        },
        

        	{ GL_TEXTURE_GEN_Q, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_GEN_Q"
#endif
        },
        

        	{ GL_TEXTURE_GEN_R, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_GEN_R"
#endif
        },
        

        	{ GL_TEXTURE_GEN_S, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_GEN_S"
#endif
        },
        

        	{ GL_TEXTURE_GEN_T, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_GEN_T"
#endif
        },
        

        	{ GL_TEXTURE_MATRIX, 16
#ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_MATRIX"
#endif
        },
        
#ifdef CR_NV_texture_rectangle

        	{ GL_TEXTURE_RECTANGLE_NV, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_RECTANGLE_NV"
        #endif
        },
        
#endif /* CR_NV_texture_rectangle */

        	{ GL_TEXTURE_STACK_DEPTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_TEXTURE_STACK_DEPTH"
#endif
        },
        
#ifdef CR_ARB_transpose_matrix

        	{ GL_TRANSPOSE_COLOR_MATRIX_ARB, 16
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_TRANSPOSE_COLOR_MATRIX_ARB"
        #endif
        },
        
#endif /* CR_ARB_transpose_matrix */
#ifdef CR_ARB_transpose_matrix

        	{ GL_TRANSPOSE_MODELVIEW_MATRIX_ARB, 16
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_TRANSPOSE_MODELVIEW_MATRIX_ARB"
        #endif
        },
        
#endif /* CR_ARB_transpose_matrix */
#ifdef CR_ARB_transpose_matrix

        	{ GL_TRANSPOSE_PROJECTION_MATRIX_ARB, 16
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_TRANSPOSE_PROJECTION_MATRIX_ARB"
        #endif
        },
        
#endif /* CR_ARB_transpose_matrix */
#ifdef CR_ARB_transpose_matrix

        	{ GL_TRANSPOSE_TEXTURE_MATRIX_ARB, 16
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_TRANSPOSE_TEXTURE_MATRIX_ARB"
        #endif
        },
        
#endif /* CR_ARB_transpose_matrix */

        	{ GL_UNPACK_ALIGNMENT, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_UNPACK_ALIGNMENT"
#endif
        },
        
#ifdef CR_OPENGL_VERSION_1_2

        	{ GL_UNPACK_IMAGE_HEIGHT, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_UNPACK_IMAGE_HEIGHT"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_1_2 */

        	{ GL_UNPACK_LSB_FIRST, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_UNPACK_LSB_FIRST"
#endif
        },
        

        	{ GL_UNPACK_ROW_LENGTH, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_UNPACK_ROW_LENGTH"
#endif
        },
        
#ifdef CR_OPENGL_VERSION_1_2

        	{ GL_UNPACK_SKIP_IMAGES, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_UNPACK_SKIP_IMAGES"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_1_2 */

        	{ GL_UNPACK_SKIP_PIXELS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_UNPACK_SKIP_PIXELS"
#endif
        },
        

        	{ GL_UNPACK_SKIP_ROWS, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_UNPACK_SKIP_ROWS"
#endif
        },
        

        	{ GL_UNPACK_SWAP_BYTES, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_UNPACK_SWAP_BYTES"
#endif
        },
        

        	{ GL_VERTEX_ARRAY, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_VERTEX_ARRAY"
#endif
        },
        
#ifdef CR_ARB_vertex_buffer_object

        	{ GL_VERTEX_ARRAY_BUFFER_BINDING_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_VERTEX_ARRAY_BUFFER_BINDING_ARB"
        #endif
        },
        
#endif /* CR_ARB_vertex_buffer_object */

        	{ GL_VERTEX_ARRAY_SIZE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_VERTEX_ARRAY_SIZE"
#endif
        },
        

        	{ GL_VERTEX_ARRAY_STRIDE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_VERTEX_ARRAY_STRIDE"
#endif
        },
        

        	{ GL_VERTEX_ARRAY_TYPE, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_VERTEX_ARRAY_TYPE"
#endif
        },
        
#ifdef CR_NV_vertex_program

        	{ GL_VERTEX_PROGRAM_BINDING_NV, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_VERTEX_PROGRAM_BINDING_NV"
        #endif
        },
        
#endif /* CR_NV_vertex_program */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_VERTEX_PROGRAM_POINT_SIZE, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_VERTEX_PROGRAM_POINT_SIZE"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */
#ifdef CR_OPENGL_VERSION_2_0

        	{ GL_VERTEX_PROGRAM_TWO_SIDE, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_VERTEX_PROGRAM_TWO_SIDE"
        #endif
        },
        
#endif /* CR_OPENGL_VERSION_2_0 */

        	{ GL_VIEWPORT, 4
#ifdef VBOX_WITH_CRDUMPER
            , "GL_VIEWPORT"
#endif
        },
        
#ifdef CR_ARB_vertex_buffer_object

        	{ GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB, 1
        #ifdef VBOX_WITH_CRDUMPER
            , "GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB"
        #endif
        },
        
#endif /* CR_ARB_vertex_buffer_object */

        	{ GL_ZOOM_X, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_ZOOM_X"
#endif
        },
        

        	{ GL_ZOOM_Y, 1
#ifdef VBOX_WITH_CRDUMPER
            , "GL_ZOOM_Y"
#endif
        },
        
	{ 0, 0 }
};
#define CR_MAX_GET_VALUES 16

static unsigned int __numValues( GLenum pname )
{
    struct nv_struct *temp;
    
    for (temp = num_values_array; temp->num_values != 0 ; temp++)
    {
        if (temp->pname == pname)
            return temp->num_values;
    }
    crDebug( "Invalid pname to __numValues: 0x%x\n", (int) pname );
    return 0;
}

void SERVER_DISPATCH_APIENTRY crServerDispatchGetIntegerv( GLenum pname, GLint * params )
{
	GLint *get_values;
	int tablesize;

    #ifdef CR_ARB_texture_compression
    if (GL_COMPRESSED_TEXTURE_FORMATS_ARB == pname)
    {
        GLint numtexfmts = 0;
        cr_server.head_spu->dispatch_table.GetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB, &numtexfmts);
        tablesize = numtexfmts * sizeof(GLint);
    }
    else
    #endif
    {
        tablesize = __numValues( pname ) * sizeof(GLint);
    }
    
	(void) params;
	get_values = (GLint *) crAlloc( tablesize );
	if (tablesize>0)
	cr_server.head_spu->dispatch_table.GetIntegerv( pname, get_values );

    if (GL_TEXTURE_BINDING_1D==pname
        || GL_TEXTURE_BINDING_2D==pname
        || GL_TEXTURE_BINDING_3D==pname
        || GL_TEXTURE_BINDING_RECTANGLE_ARB==pname
        || GL_TEXTURE_BINDING_CUBE_MAP_ARB==pname)
    {
        GLuint texid;
        CRASSERT(tablesize/sizeof(GLint)==1);
        texid = (GLuint) *get_values;
        *get_values = (GLint) crStateTextureHWIDtoID(texid);
    }
    else if (GL_CURRENT_PROGRAM==pname)
    {
        GLuint programid;
        CRASSERT(tablesize/sizeof(GLint)==1);
        programid = (GLuint) *get_values;
        *get_values = (GLint) crStateGLSLProgramHWIDtoID(programid);
    }
    else if (GL_FRAMEBUFFER_BINDING_EXT==pname
             ||GL_READ_FRAMEBUFFER_BINDING==pname)
    {
        GLuint fboid;
        CRASSERT(tablesize/sizeof(GLint)==1);
        fboid = (GLuint) *get_values;
        if (crServerIsRedirectedToFBO()
            && (fboid==cr_server.curClient->currentMural->aidFBOs[0]
            || fboid==cr_server.curClient->currentMural->aidFBOs[1]))
        {
            fboid = 0;
        }
        else
        {
        	fboid = crStateFBOHWIDtoID(fboid);
        }
        *get_values = (GLint) fboid;
    }
    else if (GL_READ_BUFFER==pname)
    {
        if (crServerIsRedirectedToFBO()
            && CR_SERVER_FBO_FOR_IDX(cr_server.curClient->currentMural, cr_server.curClient->currentMural->iCurReadBuffer)
            && !crStateGetCurrent()->framebufferobject.readFB)
        {
            *get_values = (GLint) crStateGetCurrent()->buffer.readBuffer;
            Assert(crStateGetCurrent()->buffer.readBuffer == GL_BACK || crStateGetCurrent()->buffer.readBuffer == GL_FRONT);
        }
    }
    else if (GL_DRAW_BUFFER==pname)
    {
        if (crServerIsRedirectedToFBO()
            && CR_SERVER_FBO_FOR_IDX(cr_server.curClient->currentMural, cr_server.curClient->currentMural->iCurDrawBuffer)
            && !crStateGetCurrent()->framebufferobject.drawFB)
        {
            *get_values = (GLint) crStateGetCurrent()->buffer.drawBuffer;
            Assert(crStateGetCurrent()->buffer.drawBuffer == GL_BACK || crStateGetCurrent()->buffer.drawBuffer == GL_FRONT);
        }
    }
    else if (GL_RENDERBUFFER_BINDING_EXT==pname)
    {
        GLuint rbid;
        CRASSERT(tablesize/sizeof(GLint)==1);
        rbid = (GLuint) *get_values;
        *get_values = (GLint) crStateRBOHWIDtoID(rbid);
    }
    else if (GL_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_VERTEX_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_NORMAL_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_COLOR_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_INDEX_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB==pname)
    {
        GLuint bufid;
        CRASSERT(tablesize/sizeof(GLint)==1);
        bufid = (GLuint) *get_values;
        *get_values = (GLint) crStateBufferHWIDtoID(bufid);
    }
    else if (GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS==pname)
    {
    	if (CR_MAX_TEXTURE_UNITS < (GLuint)*get_values)
    	{
    		*get_values = (GLint)CR_MAX_TEXTURE_UNITS;
    	} 
    }
    else if (GL_MAX_VERTEX_ATTRIBS_ARB==pname)
    {
        if (CR_MAX_VERTEX_ATTRIBS < (GLuint)*get_values)
        {
            *get_values = (GLint)CR_MAX_VERTEX_ATTRIBS;
        } 
    }
    
	crServerReturnValue( get_values, tablesize );
	crFree(get_values);
}

void SERVER_DISPATCH_APIENTRY crServerDispatchGetFloatv( GLenum pname, GLfloat * params )
{
	GLfloat *get_values;
	int tablesize;

    #ifdef CR_ARB_texture_compression
    if (GL_COMPRESSED_TEXTURE_FORMATS_ARB == pname)
    {
        GLint numtexfmts = 0;
        cr_server.head_spu->dispatch_table.GetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB, &numtexfmts);
        tablesize = numtexfmts * sizeof(GLfloat);
    }
    else
    #endif
    {
        tablesize = __numValues( pname ) * sizeof(GLfloat);
    }
    
	(void) params;
	get_values = (GLfloat *) crAlloc( tablesize );
	if (tablesize>0)
	cr_server.head_spu->dispatch_table.GetFloatv( pname, get_values );

    if (GL_TEXTURE_BINDING_1D==pname
        || GL_TEXTURE_BINDING_2D==pname
        || GL_TEXTURE_BINDING_3D==pname
        || GL_TEXTURE_BINDING_RECTANGLE_ARB==pname
        || GL_TEXTURE_BINDING_CUBE_MAP_ARB==pname)
    {
        GLuint texid;
        CRASSERT(tablesize/sizeof(GLfloat)==1);
        texid = (GLuint) *get_values;
        *get_values = (GLfloat) crStateTextureHWIDtoID(texid);
    }
    else if (GL_CURRENT_PROGRAM==pname)
    {
        GLuint programid;
        CRASSERT(tablesize/sizeof(GLfloat)==1);
        programid = (GLuint) *get_values;
        *get_values = (GLfloat) crStateGLSLProgramHWIDtoID(programid);
    }
    else if (GL_FRAMEBUFFER_BINDING_EXT==pname
             ||GL_READ_FRAMEBUFFER_BINDING==pname)
    {
        GLuint fboid;
        CRASSERT(tablesize/sizeof(GLfloat)==1);
        fboid = (GLuint) *get_values;
        if (crServerIsRedirectedToFBO()
            && (fboid==cr_server.curClient->currentMural->aidFBOs[0]
            || fboid==cr_server.curClient->currentMural->aidFBOs[1]))
        {
            fboid = 0;
        }
        else
        {
        	fboid = crStateFBOHWIDtoID(fboid);
        }
        *get_values = (GLfloat) fboid;
    }
    else if (GL_READ_BUFFER==pname)
    {
        if (crServerIsRedirectedToFBO()
            && CR_SERVER_FBO_FOR_IDX(cr_server.curClient->currentMural, cr_server.curClient->currentMural->iCurReadBuffer)
            && !crStateGetCurrent()->framebufferobject.readFB)
        {
            *get_values = (GLfloat) crStateGetCurrent()->buffer.readBuffer;
            Assert(crStateGetCurrent()->buffer.readBuffer == GL_BACK || crStateGetCurrent()->buffer.readBuffer == GL_FRONT);
        }
    }
    else if (GL_DRAW_BUFFER==pname)
    {
        if (crServerIsRedirectedToFBO()
            && CR_SERVER_FBO_FOR_IDX(cr_server.curClient->currentMural, cr_server.curClient->currentMural->iCurDrawBuffer)
            && !crStateGetCurrent()->framebufferobject.drawFB)
        {
            *get_values = (GLfloat) crStateGetCurrent()->buffer.drawBuffer;
            Assert(crStateGetCurrent()->buffer.drawBuffer == GL_BACK || crStateGetCurrent()->buffer.drawBuffer == GL_FRONT);
        }
    }
    else if (GL_RENDERBUFFER_BINDING_EXT==pname)
    {
        GLuint rbid;
        CRASSERT(tablesize/sizeof(GLfloat)==1);
        rbid = (GLuint) *get_values;
        *get_values = (GLfloat) crStateRBOHWIDtoID(rbid);
    }
    else if (GL_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_VERTEX_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_NORMAL_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_COLOR_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_INDEX_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB==pname)
    {
        GLuint bufid;
        CRASSERT(tablesize/sizeof(GLfloat)==1);
        bufid = (GLuint) *get_values;
        *get_values = (GLfloat) crStateBufferHWIDtoID(bufid);
    }
    else if (GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS==pname)
    {
    	if (CR_MAX_TEXTURE_UNITS < (GLuint)*get_values)
    	{
    		*get_values = (GLfloat)CR_MAX_TEXTURE_UNITS;
    	} 
    }
    else if (GL_MAX_VERTEX_ATTRIBS_ARB==pname)
    {
        if (CR_MAX_VERTEX_ATTRIBS < (GLuint)*get_values)
        {
            *get_values = (GLfloat)CR_MAX_VERTEX_ATTRIBS;
        } 
    }
    
	crServerReturnValue( get_values, tablesize );
	crFree(get_values);
}

void SERVER_DISPATCH_APIENTRY crServerDispatchGetDoublev( GLenum pname, GLdouble * params )
{
	GLdouble *get_values;
	int tablesize;

    #ifdef CR_ARB_texture_compression
    if (GL_COMPRESSED_TEXTURE_FORMATS_ARB == pname)
    {
        GLint numtexfmts = 0;
        cr_server.head_spu->dispatch_table.GetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB, &numtexfmts);
        tablesize = numtexfmts * sizeof(GLdouble);
    }
    else
    #endif
    {
        tablesize = __numValues( pname ) * sizeof(GLdouble);
    }
    
	(void) params;
	get_values = (GLdouble *) crAlloc( tablesize );
	if (tablesize>0)
	cr_server.head_spu->dispatch_table.GetDoublev( pname, get_values );

    if (GL_TEXTURE_BINDING_1D==pname
        || GL_TEXTURE_BINDING_2D==pname
        || GL_TEXTURE_BINDING_3D==pname
        || GL_TEXTURE_BINDING_RECTANGLE_ARB==pname
        || GL_TEXTURE_BINDING_CUBE_MAP_ARB==pname)
    {
        GLuint texid;
        CRASSERT(tablesize/sizeof(GLdouble)==1);
        texid = (GLuint) *get_values;
        *get_values = (GLdouble) crStateTextureHWIDtoID(texid);
    }
    else if (GL_CURRENT_PROGRAM==pname)
    {
        GLuint programid;
        CRASSERT(tablesize/sizeof(GLdouble)==1);
        programid = (GLuint) *get_values;
        *get_values = (GLdouble) crStateGLSLProgramHWIDtoID(programid);
    }
    else if (GL_FRAMEBUFFER_BINDING_EXT==pname
             ||GL_READ_FRAMEBUFFER_BINDING==pname)
    {
        GLuint fboid;
        CRASSERT(tablesize/sizeof(GLdouble)==1);
        fboid = (GLuint) *get_values;
        if (crServerIsRedirectedToFBO()
            && (fboid==cr_server.curClient->currentMural->aidFBOs[0]
            || fboid==cr_server.curClient->currentMural->aidFBOs[1]))
        {
            fboid = 0;
        }
        else
        {
        	fboid = crStateFBOHWIDtoID(fboid);
        }
        *get_values = (GLdouble) fboid;
    }
    else if (GL_READ_BUFFER==pname)
    {
        if (crServerIsRedirectedToFBO()
            && CR_SERVER_FBO_FOR_IDX(cr_server.curClient->currentMural, cr_server.curClient->currentMural->iCurReadBuffer)
            && !crStateGetCurrent()->framebufferobject.readFB)
        {
            *get_values = (GLdouble) crStateGetCurrent()->buffer.readBuffer;
            Assert(crStateGetCurrent()->buffer.readBuffer == GL_BACK || crStateGetCurrent()->buffer.readBuffer == GL_FRONT);
        }
    }
    else if (GL_DRAW_BUFFER==pname)
    {
        if (crServerIsRedirectedToFBO()
            && CR_SERVER_FBO_FOR_IDX(cr_server.curClient->currentMural, cr_server.curClient->currentMural->iCurDrawBuffer)
            && !crStateGetCurrent()->framebufferobject.drawFB)
        {
            *get_values = (GLdouble) crStateGetCurrent()->buffer.drawBuffer;
            Assert(crStateGetCurrent()->buffer.drawBuffer == GL_BACK || crStateGetCurrent()->buffer.drawBuffer == GL_FRONT);
        }
    }
    else if (GL_RENDERBUFFER_BINDING_EXT==pname)
    {
        GLuint rbid;
        CRASSERT(tablesize/sizeof(GLdouble)==1);
        rbid = (GLuint) *get_values;
        *get_values = (GLdouble) crStateRBOHWIDtoID(rbid);
    }
    else if (GL_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_VERTEX_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_NORMAL_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_COLOR_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_INDEX_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB==pname)
    {
        GLuint bufid;
        CRASSERT(tablesize/sizeof(GLdouble)==1);
        bufid = (GLuint) *get_values;
        *get_values = (GLdouble) crStateBufferHWIDtoID(bufid);
    }
    else if (GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS==pname)
    {
    	if (CR_MAX_TEXTURE_UNITS < (GLuint)*get_values)
    	{
    		*get_values = (GLdouble)CR_MAX_TEXTURE_UNITS;
    	} 
    }
    else if (GL_MAX_VERTEX_ATTRIBS_ARB==pname)
    {
        if (CR_MAX_VERTEX_ATTRIBS < (GLuint)*get_values)
        {
            *get_values = (GLdouble)CR_MAX_VERTEX_ATTRIBS;
        } 
    }
    
	crServerReturnValue( get_values, tablesize );
	crFree(get_values);
}

void SERVER_DISPATCH_APIENTRY crServerDispatchGetBooleanv( GLenum pname, GLboolean * params )
{
	GLboolean *get_values;
	int tablesize;

    #ifdef CR_ARB_texture_compression
    if (GL_COMPRESSED_TEXTURE_FORMATS_ARB == pname)
    {
        GLint numtexfmts = 0;
        cr_server.head_spu->dispatch_table.GetIntegerv(GL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB, &numtexfmts);
        tablesize = numtexfmts * sizeof(GLboolean);
    }
    else
    #endif
    {
        tablesize = __numValues( pname ) * sizeof(GLboolean);
    }
    
	(void) params;
	get_values = (GLboolean *) crAlloc( tablesize );
	if (tablesize>0)
	cr_server.head_spu->dispatch_table.GetBooleanv( pname, get_values );

    if (GL_TEXTURE_BINDING_1D==pname
        || GL_TEXTURE_BINDING_2D==pname
        || GL_TEXTURE_BINDING_3D==pname
        || GL_TEXTURE_BINDING_RECTANGLE_ARB==pname
        || GL_TEXTURE_BINDING_CUBE_MAP_ARB==pname)
    {
        GLuint texid;
        CRASSERT(tablesize/sizeof(GLboolean)==1);
        texid = (GLuint) *get_values;
        *get_values = (GLboolean) crStateTextureHWIDtoID(texid);
    }
    else if (GL_CURRENT_PROGRAM==pname)
    {
        GLuint programid;
        CRASSERT(tablesize/sizeof(GLboolean)==1);
        programid = (GLuint) *get_values;
        *get_values = (GLboolean) crStateGLSLProgramHWIDtoID(programid);
    }
    else if (GL_FRAMEBUFFER_BINDING_EXT==pname
             ||GL_READ_FRAMEBUFFER_BINDING==pname)
    {
        GLuint fboid;
        CRASSERT(tablesize/sizeof(GLboolean)==1);
        fboid = (GLuint) *get_values;
        if (crServerIsRedirectedToFBO()
            && (fboid==cr_server.curClient->currentMural->aidFBOs[0]
            || fboid==cr_server.curClient->currentMural->aidFBOs[1]))
        {
            fboid = 0;
        }
        else
        {
        	fboid = crStateFBOHWIDtoID(fboid);
        }
        *get_values = (GLboolean) fboid;
    }
    else if (GL_READ_BUFFER==pname)
    {
        if (crServerIsRedirectedToFBO()
            && CR_SERVER_FBO_FOR_IDX(cr_server.curClient->currentMural, cr_server.curClient->currentMural->iCurReadBuffer)
            && !crStateGetCurrent()->framebufferobject.readFB)
        {
            *get_values = (GLboolean) crStateGetCurrent()->buffer.readBuffer;
            Assert(crStateGetCurrent()->buffer.readBuffer == GL_BACK || crStateGetCurrent()->buffer.readBuffer == GL_FRONT);
        }
    }
    else if (GL_DRAW_BUFFER==pname)
    {
        if (crServerIsRedirectedToFBO()
            && CR_SERVER_FBO_FOR_IDX(cr_server.curClient->currentMural, cr_server.curClient->currentMural->iCurDrawBuffer)
            && !crStateGetCurrent()->framebufferobject.drawFB)
        {
            *get_values = (GLboolean) crStateGetCurrent()->buffer.drawBuffer;
            Assert(crStateGetCurrent()->buffer.drawBuffer == GL_BACK || crStateGetCurrent()->buffer.drawBuffer == GL_FRONT);
        }
    }
    else if (GL_RENDERBUFFER_BINDING_EXT==pname)
    {
        GLuint rbid;
        CRASSERT(tablesize/sizeof(GLboolean)==1);
        rbid = (GLuint) *get_values;
        *get_values = (GLboolean) crStateRBOHWIDtoID(rbid);
    }
    else if (GL_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_ELEMENT_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_VERTEX_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_NORMAL_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_COLOR_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_INDEX_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB==pname
             || GL_WEIGHT_ARRAY_BUFFER_BINDING_ARB==pname)
    {
        GLuint bufid;
        CRASSERT(tablesize/sizeof(GLboolean)==1);
        bufid = (GLuint) *get_values;
        *get_values = (GLboolean) crStateBufferHWIDtoID(bufid);
    }
    else if (GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS==pname)
    {
    	if (CR_MAX_TEXTURE_UNITS < (GLuint)*get_values)
    	{
    		*get_values = (GLboolean)CR_MAX_TEXTURE_UNITS;
    	} 
    }
    else if (GL_MAX_VERTEX_ATTRIBS_ARB==pname)
    {
        if (CR_MAX_VERTEX_ATTRIBS < (GLuint)*get_values)
        {
            *get_values = (GLboolean)CR_MAX_VERTEX_ATTRIBS;
        } 
    }
    
	crServerReturnValue( get_values, tablesize );
	crFree(get_values);
}
