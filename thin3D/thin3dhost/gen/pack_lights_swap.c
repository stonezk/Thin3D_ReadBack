/* THIS FILE IS AUTOGENERATED FROM pack_lights.c BY pack_swap.py */


/* Copyright (c) 2001, Stanford University
 * All rights reserved
 *
 * See the file LICENSE.txt for information on redistributing this software.
 */

#include "packer.h"
#include "cr_error.h"

static GLboolean __handleLightData( GLenum light, GLenum pname, const GLfloat *params )
{
    CR_GET_PACKER_CONTEXT(pc);
    unsigned int packet_length = sizeof( int ) + sizeof( light ) + sizeof( pname );
    unsigned int params_length = 0;
    unsigned char *data_ptr;
    switch( pname )
    {
        case GL_AMBIENT:
        case GL_DIFFUSE:
        case GL_SPECULAR:
        case GL_POSITION:
            params_length = 4*sizeof( *params );
            break;
        case GL_SPOT_DIRECTION:
            params_length = 3*sizeof( *params );
            break;
        case GL_SPOT_EXPONENT:
        case GL_SPOT_CUTOFF:
        case GL_CONSTANT_ATTENUATION:
        case GL_LINEAR_ATTENUATION:
        case GL_QUADRATIC_ATTENUATION:
            params_length = sizeof( *params );
            break;
        default:
            __PackError( __LINE__, __FILE__, GL_INVALID_ENUM,
                                     "crPackLightSWAP(bad pname)" );
            return GL_FALSE;
    }
    packet_length += params_length;
    CR_GET_BUFFERED_POINTER(pc, packet_length );
    WRITE_DATA( 0, int, SWAP32(packet_length) );
    WRITE_DATA( sizeof( int ) + 0, GLenum, SWAP32(light) );
    WRITE_DATA( sizeof( int ) + 4, GLenum, SWAP32(pname) );
    WRITE_DATA( sizeof( int ) + 8, GLuint, SWAPFLOAT(params[0]) );
    if (params_length > sizeof( *params ))
    {
        WRITE_DATA( sizeof( int ) + 12, GLuint, SWAPFLOAT(params[1]) );
        WRITE_DATA( sizeof( int ) + 16, GLuint, SWAPFLOAT(params[2]) );
    }
    if (params_length > 3*sizeof( *params ))
    {
        WRITE_DATA( sizeof( int ) + 20, GLuint, SWAPFLOAT(params[3]) );
    }
    return GL_TRUE;
}

void PACK_APIENTRY crPackLightfvSWAP (GLenum light, GLenum pname, const GLfloat *params)
{
    CR_GET_PACKER_CONTEXT(pc);
    if (__handleLightData( light, pname, params ))
        WRITE_OPCODE( pc, CR_LIGHTFV_OPCODE );
    CR_UNLOCK_PACKER_CONTEXT(pc);
}

void PACK_APIENTRY crPackLightivSWAP (GLenum light, GLenum pname, const GLint *params)
{
    /* floats and ints are the same size, so the packing should be the same */
    CR_GET_PACKER_CONTEXT(pc);
    if (__handleLightData( light, pname, (const GLfloat *) params ))
        WRITE_OPCODE( pc, CR_LIGHTIV_OPCODE );
    CR_UNLOCK_PACKER_CONTEXT(pc);
}

static GLboolean __handleLightModelData( GLenum pname, const GLfloat *params )
{
    CR_GET_PACKER_CONTEXT(pc);
    unsigned int packet_length = sizeof( int ) + sizeof( pname );
    unsigned int params_length = 0;
    unsigned char *data_ptr;
    switch( pname )
    {
        case GL_LIGHT_MODEL_AMBIENT:
            params_length = 4*sizeof( *params );
            break;
        case GL_LIGHT_MODEL_TWO_SIDE:
        case GL_LIGHT_MODEL_LOCAL_VIEWER:
            params_length = sizeof( *params );
            break;
        default:
            __PackError( __LINE__, __FILE__, GL_INVALID_ENUM,
                                     "crPackLightModelSWAP(bad pname)" );
            return GL_FALSE;
    }
    packet_length += params_length;
    CR_GET_BUFFERED_POINTER(pc, packet_length );
    WRITE_DATA( 0, int, SWAP32(packet_length) );
    WRITE_DATA( sizeof( int ) + 0, GLenum, SWAP32(pname) );
    WRITE_DATA( sizeof( int ) + 4, GLuint, SWAPFLOAT(params[0]) );
    if (params_length > sizeof( *params ))
    {
        WRITE_DATA( sizeof( int ) + 8, GLuint, SWAPFLOAT(params[1]) );
        WRITE_DATA( sizeof( int ) + 12, GLuint, SWAPFLOAT(params[2]) );
        WRITE_DATA( sizeof( int ) + 16, GLuint, SWAPFLOAT(params[3]) );
    }
    return GL_TRUE;
}

void PACK_APIENTRY crPackLightModelfvSWAP (GLenum pname, const GLfloat *params)
{
    CR_GET_PACKER_CONTEXT(pc);
    if (__handleLightModelData( pname, params ))
        WRITE_OPCODE( pc, CR_LIGHTMODELFV_OPCODE );
    CR_UNLOCK_PACKER_CONTEXT(pc);
}

void PACK_APIENTRY crPackLightModelivSWAP (GLenum pname, const GLint *params)
{
    /* floats and ints are the same size, so the packing should be the same */
    CR_GET_PACKER_CONTEXT(pc);
    if (__handleLightModelData( pname, (const GLfloat *) params ))
        WRITE_OPCODE( pc, CR_LIGHTMODELIV_OPCODE );
    CR_UNLOCK_PACKER_CONTEXT(pc);
}
