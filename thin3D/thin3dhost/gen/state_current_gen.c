/* Copyright (c) 2001, Stanford University
	All rights reserved.

	See the file LICENSE.txt for information on redistributing this software. */
	

#include "state/cr_currentpointers.h"
#include "state.h"

#include <stdio.h>

#ifdef WINDOWS
#pragma warning( disable : 4127 )
#endif

typedef void (*convert_func) (GLfloat *, const unsigned char *);

/* Copyright (c) 2001, Stanford University
	All rights reserved.

	See the file LICENSE.txt for information on redistributing this software. */
	

#include "state/cr_statetypes.h"

static double __read_double( const void *src )
{
    const unsigned int *ui = (const unsigned int *) src;
    double d;
    ((unsigned int *) &d)[0] = ui[0];
    ((unsigned int *) &d)[1] = ui[1];
    return d;
}

static void __convert_Ni1 (GLfloat *dst, const GLint *src) {
	*dst = (GLfloat) *src;
}

static void __convert_Ni2 (GLfloat *dst, const GLint *src) {
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_Ni3 (GLfloat *dst, const GLint *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_Ni4 (GLfloat *dst, const GLint *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_Nb1 (GLfloat *dst, const GLbyte *src) {
	*dst = (GLfloat) *src;
}

static void __convert_Nb2 (GLfloat *dst, const GLbyte *src) {
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_Nb3 (GLfloat *dst, const GLbyte *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_Nb4 (GLfloat *dst, const GLbyte *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_Nus1 (GLfloat *dst, const GLushort *src) {
	*dst = (GLfloat) *src;
}

static void __convert_Nus2 (GLfloat *dst, const GLushort *src) {
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_Nus3 (GLfloat *dst, const GLushort *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_Nus4 (GLfloat *dst, const GLushort *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_Ns1 (GLfloat *dst, const GLshort *src) {
	*dst = (GLfloat) *src;
}

static void __convert_Ns2 (GLfloat *dst, const GLshort *src) {
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_Ns3 (GLfloat *dst, const GLshort *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_Ns4 (GLfloat *dst, const GLshort *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_b1 (GLfloat *dst, const GLbyte *src) {
	*dst = (GLfloat) *src;
}

static void __convert_b2 (GLfloat *dst, const GLbyte *src) {
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_b3 (GLfloat *dst, const GLbyte *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_b4 (GLfloat *dst, const GLbyte *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_d1 (GLfloat *dst, const GLdouble *src) {
	*dst = (GLfloat) __read_double(src);
}

static void __convert_d2 (GLfloat *dst, const GLdouble *src) {
	*dst++ = (GLfloat) __read_double(src++);
	*dst = (GLfloat) __read_double(src);
}

static void __convert_d3 (GLfloat *dst, const GLdouble *src) {
	*dst++ = (GLfloat) __read_double(src++);
	*dst++ = (GLfloat) __read_double(src++);
	*dst = (GLfloat) __read_double(src);
}

static void __convert_d4 (GLfloat *dst, const GLdouble *src) {
	*dst++ = (GLfloat) __read_double(src++);
	*dst++ = (GLfloat) __read_double(src++);
	*dst++ = (GLfloat) __read_double(src++);
	*dst = (GLfloat) __read_double(src);
}

static void __convert_f1 (GLfloat *dst, const GLfloat *src) {
	*dst = (GLfloat) *src;
}

static void __convert_f2 (GLfloat *dst, const GLfloat *src) {
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_f3 (GLfloat *dst, const GLfloat *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_f4 (GLfloat *dst, const GLfloat *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_i1 (GLfloat *dst, const GLint *src) {
	*dst = (GLfloat) *src;
}

static void __convert_i2 (GLfloat *dst, const GLint *src) {
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_i3 (GLfloat *dst, const GLint *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_i4 (GLfloat *dst, const GLint *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_l1 (GLfloat *dst, const GLboolean *src) {
	*dst = (GLfloat) *src;
}

static void __convert_l2 (GLfloat *dst, const GLboolean *src) {
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_l3 (GLfloat *dst, const GLboolean *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_l4 (GLfloat *dst, const GLboolean *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_us1 (GLfloat *dst, const GLushort *src) {
	*dst = (GLfloat) *src;
}

static void __convert_us2 (GLfloat *dst, const GLushort *src) {
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_us3 (GLfloat *dst, const GLushort *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_us4 (GLfloat *dst, const GLushort *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_s1 (GLfloat *dst, const GLshort *src) {
	*dst = (GLfloat) *src;
}

static void __convert_s2 (GLfloat *dst, const GLshort *src) {
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_s3 (GLfloat *dst, const GLshort *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_s4 (GLfloat *dst, const GLshort *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_ui1 (GLfloat *dst, const GLuint *src) {
	*dst = (GLfloat) *src;
}

static void __convert_ui2 (GLfloat *dst, const GLuint *src) {
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_ui3 (GLfloat *dst, const GLuint *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_ui4 (GLfloat *dst, const GLuint *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_Nui1 (GLfloat *dst, const GLuint *src) {
	*dst = (GLfloat) *src;
}

static void __convert_Nui2 (GLfloat *dst, const GLuint *src) {
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_Nui3 (GLfloat *dst, const GLuint *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_Nui4 (GLfloat *dst, const GLuint *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_Nub1 (GLfloat *dst, const GLubyte *src) {
	*dst = (GLfloat) *src;
}

static void __convert_Nub2 (GLfloat *dst, const GLubyte *src) {
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_Nub3 (GLfloat *dst, const GLubyte *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_Nub4 (GLfloat *dst, const GLubyte *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_ub1 (GLfloat *dst, const GLubyte *src) {
	*dst = (GLfloat) *src;
}

static void __convert_ub2 (GLfloat *dst, const GLubyte *src) {
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_ub3 (GLfloat *dst, const GLubyte *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_ub4 (GLfloat *dst, const GLubyte *src) {
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst++ = (GLfloat) *src++;
	*dst = (GLfloat) *src;
}

static void __convert_rescale_Ni1 (GLfloat *dst, const GLint *src) {
	*dst = ((GLfloat) *src) / CR_MAXINT;
}

static void __convert_rescale_Ni2 (GLfloat *dst, const GLint *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXINT;
	*dst = ((GLfloat) *src) / CR_MAXINT;
}

static void __convert_rescale_Ni3 (GLfloat *dst, const GLint *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXINT;
	*dst++ = ((GLfloat) *src++) / CR_MAXINT;
	*dst = ((GLfloat) *src) / CR_MAXINT;
}

static void __convert_rescale_Ni4 (GLfloat *dst, const GLint *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXINT;
	*dst++ = ((GLfloat) *src++) / CR_MAXINT;
	*dst++ = ((GLfloat) *src++) / CR_MAXINT;
	*dst = ((GLfloat) *src) / CR_MAXINT;
}

static void __convert_rescale_Nb1 (GLfloat *dst, const GLbyte *src) {
	*dst = ((GLfloat) *src) / CR_MAXBYTE;
}

static void __convert_rescale_Nb2 (GLfloat *dst, const GLbyte *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXBYTE;
	*dst = ((GLfloat) *src) / CR_MAXBYTE;
}

static void __convert_rescale_Nb3 (GLfloat *dst, const GLbyte *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXBYTE;
	*dst++ = ((GLfloat) *src++) / CR_MAXBYTE;
	*dst = ((GLfloat) *src) / CR_MAXBYTE;
}

static void __convert_rescale_Nb4 (GLfloat *dst, const GLbyte *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXBYTE;
	*dst++ = ((GLfloat) *src++) / CR_MAXBYTE;
	*dst++ = ((GLfloat) *src++) / CR_MAXBYTE;
	*dst = ((GLfloat) *src) / CR_MAXBYTE;
}

static void __convert_rescale_Nus1 (GLfloat *dst, const GLushort *src) {
	*dst = ((GLfloat) *src) / CR_MAXUSHORT;
}

static void __convert_rescale_Nus2 (GLfloat *dst, const GLushort *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUSHORT;
	*dst = ((GLfloat) *src) / CR_MAXUSHORT;
}

static void __convert_rescale_Nus3 (GLfloat *dst, const GLushort *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUSHORT;
	*dst++ = ((GLfloat) *src++) / CR_MAXUSHORT;
	*dst = ((GLfloat) *src) / CR_MAXUSHORT;
}

static void __convert_rescale_Nus4 (GLfloat *dst, const GLushort *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUSHORT;
	*dst++ = ((GLfloat) *src++) / CR_MAXUSHORT;
	*dst++ = ((GLfloat) *src++) / CR_MAXUSHORT;
	*dst = ((GLfloat) *src) / CR_MAXUSHORT;
}

static void __convert_rescale_Ns1 (GLfloat *dst, const GLshort *src) {
	*dst = ((GLfloat) *src) / CR_MAXSHORT;
}

static void __convert_rescale_Ns2 (GLfloat *dst, const GLshort *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXSHORT;
	*dst = ((GLfloat) *src) / CR_MAXSHORT;
}

static void __convert_rescale_Ns3 (GLfloat *dst, const GLshort *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXSHORT;
	*dst++ = ((GLfloat) *src++) / CR_MAXSHORT;
	*dst = ((GLfloat) *src) / CR_MAXSHORT;
}

static void __convert_rescale_Ns4 (GLfloat *dst, const GLshort *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXSHORT;
	*dst++ = ((GLfloat) *src++) / CR_MAXSHORT;
	*dst++ = ((GLfloat) *src++) / CR_MAXSHORT;
	*dst = ((GLfloat) *src) / CR_MAXSHORT;
}

static void __convert_rescale_b1 (GLfloat *dst, const GLbyte *src) {
	*dst = ((GLfloat) *src) / CR_MAXBYTE;
}

static void __convert_rescale_b2 (GLfloat *dst, const GLbyte *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXBYTE;
	*dst = ((GLfloat) *src) / CR_MAXBYTE;
}

static void __convert_rescale_b3 (GLfloat *dst, const GLbyte *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXBYTE;
	*dst++ = ((GLfloat) *src++) / CR_MAXBYTE;
	*dst = ((GLfloat) *src) / CR_MAXBYTE;
}

static void __convert_rescale_b4 (GLfloat *dst, const GLbyte *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXBYTE;
	*dst++ = ((GLfloat) *src++) / CR_MAXBYTE;
	*dst++ = ((GLfloat) *src++) / CR_MAXBYTE;
	*dst = ((GLfloat) *src) / CR_MAXBYTE;
}

static void __convert_rescale_i1 (GLfloat *dst, const GLint *src) {
	*dst = ((GLfloat) *src) / CR_MAXINT;
}

static void __convert_rescale_i2 (GLfloat *dst, const GLint *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXINT;
	*dst = ((GLfloat) *src) / CR_MAXINT;
}

static void __convert_rescale_i3 (GLfloat *dst, const GLint *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXINT;
	*dst++ = ((GLfloat) *src++) / CR_MAXINT;
	*dst = ((GLfloat) *src) / CR_MAXINT;
}

static void __convert_rescale_i4 (GLfloat *dst, const GLint *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXINT;
	*dst++ = ((GLfloat) *src++) / CR_MAXINT;
	*dst++ = ((GLfloat) *src++) / CR_MAXINT;
	*dst = ((GLfloat) *src) / CR_MAXINT;
}

static void __convert_rescale_us1 (GLfloat *dst, const GLushort *src) {
	*dst = ((GLfloat) *src) / CR_MAXUSHORT;
}

static void __convert_rescale_us2 (GLfloat *dst, const GLushort *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUSHORT;
	*dst = ((GLfloat) *src) / CR_MAXUSHORT;
}

static void __convert_rescale_us3 (GLfloat *dst, const GLushort *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUSHORT;
	*dst++ = ((GLfloat) *src++) / CR_MAXUSHORT;
	*dst = ((GLfloat) *src) / CR_MAXUSHORT;
}

static void __convert_rescale_us4 (GLfloat *dst, const GLushort *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUSHORT;
	*dst++ = ((GLfloat) *src++) / CR_MAXUSHORT;
	*dst++ = ((GLfloat) *src++) / CR_MAXUSHORT;
	*dst = ((GLfloat) *src) / CR_MAXUSHORT;
}

static void __convert_rescale_s1 (GLfloat *dst, const GLshort *src) {
	*dst = ((GLfloat) *src) / CR_MAXSHORT;
}

static void __convert_rescale_s2 (GLfloat *dst, const GLshort *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXSHORT;
	*dst = ((GLfloat) *src) / CR_MAXSHORT;
}

static void __convert_rescale_s3 (GLfloat *dst, const GLshort *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXSHORT;
	*dst++ = ((GLfloat) *src++) / CR_MAXSHORT;
	*dst = ((GLfloat) *src) / CR_MAXSHORT;
}

static void __convert_rescale_s4 (GLfloat *dst, const GLshort *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXSHORT;
	*dst++ = ((GLfloat) *src++) / CR_MAXSHORT;
	*dst++ = ((GLfloat) *src++) / CR_MAXSHORT;
	*dst = ((GLfloat) *src) / CR_MAXSHORT;
}

static void __convert_rescale_ui1 (GLfloat *dst, const GLuint *src) {
	*dst = ((GLfloat) *src) / CR_MAXUINT;
}

static void __convert_rescale_ui2 (GLfloat *dst, const GLuint *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUINT;
	*dst = ((GLfloat) *src) / CR_MAXUINT;
}

static void __convert_rescale_ui3 (GLfloat *dst, const GLuint *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUINT;
	*dst++ = ((GLfloat) *src++) / CR_MAXUINT;
	*dst = ((GLfloat) *src) / CR_MAXUINT;
}

static void __convert_rescale_ui4 (GLfloat *dst, const GLuint *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUINT;
	*dst++ = ((GLfloat) *src++) / CR_MAXUINT;
	*dst++ = ((GLfloat) *src++) / CR_MAXUINT;
	*dst = ((GLfloat) *src) / CR_MAXUINT;
}

static void __convert_rescale_Nui1 (GLfloat *dst, const GLuint *src) {
	*dst = ((GLfloat) *src) / CR_MAXUINT;
}

static void __convert_rescale_Nui2 (GLfloat *dst, const GLuint *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUINT;
	*dst = ((GLfloat) *src) / CR_MAXUINT;
}

static void __convert_rescale_Nui3 (GLfloat *dst, const GLuint *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUINT;
	*dst++ = ((GLfloat) *src++) / CR_MAXUINT;
	*dst = ((GLfloat) *src) / CR_MAXUINT;
}

static void __convert_rescale_Nui4 (GLfloat *dst, const GLuint *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUINT;
	*dst++ = ((GLfloat) *src++) / CR_MAXUINT;
	*dst++ = ((GLfloat) *src++) / CR_MAXUINT;
	*dst = ((GLfloat) *src) / CR_MAXUINT;
}

static void __convert_rescale_Nub1 (GLfloat *dst, const GLubyte *src) {
	*dst = ((GLfloat) *src) / CR_MAXUBYTE;
}

static void __convert_rescale_Nub2 (GLfloat *dst, const GLubyte *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUBYTE;
	*dst = ((GLfloat) *src) / CR_MAXUBYTE;
}

static void __convert_rescale_Nub3 (GLfloat *dst, const GLubyte *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUBYTE;
	*dst++ = ((GLfloat) *src++) / CR_MAXUBYTE;
	*dst = ((GLfloat) *src) / CR_MAXUBYTE;
}

static void __convert_rescale_Nub4 (GLfloat *dst, const GLubyte *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUBYTE;
	*dst++ = ((GLfloat) *src++) / CR_MAXUBYTE;
	*dst++ = ((GLfloat) *src++) / CR_MAXUBYTE;
	*dst = ((GLfloat) *src) / CR_MAXUBYTE;
}

static void __convert_rescale_ub1 (GLfloat *dst, const GLubyte *src) {
	*dst = ((GLfloat) *src) / CR_MAXUBYTE;
}

static void __convert_rescale_ub2 (GLfloat *dst, const GLubyte *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUBYTE;
	*dst = ((GLfloat) *src) / CR_MAXUBYTE;
}

static void __convert_rescale_ub3 (GLfloat *dst, const GLubyte *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUBYTE;
	*dst++ = ((GLfloat) *src++) / CR_MAXUBYTE;
	*dst = ((GLfloat) *src) / CR_MAXUBYTE;
}

static void __convert_rescale_ub4 (GLfloat *dst, const GLubyte *src) {
	*dst++ = ((GLfloat) *src++) / CR_MAXUBYTE;
	*dst++ = ((GLfloat) *src++) / CR_MAXUBYTE;
	*dst++ = ((GLfloat) *src++) / CR_MAXUBYTE;
	*dst = ((GLfloat) *src) / CR_MAXUBYTE;
}



static void __convert_boolean (GLboolean *dst, const GLboolean *src) {
	*dst = *src;
}

#define VPINCH_CONVERT_INDEX(op,data,dst) \
{\
	GLfloat vdata[2] = { 0 , };\
	switch (op) { \
	case CR_INDEX1UB_OPCODE: \
		__convert_ub1 (vdata, (GLubyte *) (data)); \
		break; \
	case CR_INDEX1S_OPCODE: \
		__convert_s1 (vdata, (GLshort *) (data)); \
		break; \
	case CR_INDEX1I_OPCODE: \
		__convert_i1 (vdata, (GLint *) (data)); \
		break; \
	case CR_INDEX1F_OPCODE: \
		__convert_f1 (vdata, (GLfloat *) (data)); \
		break; \
	case CR_INDEX1D_OPCODE: \
		__convert_d1 (vdata, (GLdouble *) (data)); \
		break; \
	default: \
		crSimpleError ( "Unknown opcode in VPINCH_CONVERT_INDEX" ); \
	}\
	(dst).[0] = vdata[0];\
}

#define VPINCH_CONVERT_VERTEXATTRIB(op,data,dst) \
{\
	GLfloat vdata[5] = { 0 , 0 , 0 , 1 , };\
	switch (op) { \
	case CR_VERTEXATTRIB1S_OPCODE: \
		__convert_s1 (vdata, (GLshort *) (data)); \
		break; \
	case CR_VERTEXATTRIB2S_OPCODE: \
		__convert_s2 (vdata, (GLshort *) (data)); \
		break; \
	case CR_VERTEXATTRIB3S_OPCODE: \
		__convert_s3 (vdata, (GLshort *) (data)); \
		break; \
	case CR_VERTEXATTRIB4S_OPCODE: \
		__convert_s4 (vdata, (GLshort *) (data)); \
		break; \
	case CR_VERTEXATTRIB1F_OPCODE: \
		__convert_f1 (vdata, (GLfloat *) (data)); \
		break; \
	case CR_VERTEXATTRIB2F_OPCODE: \
		__convert_f2 (vdata, (GLfloat *) (data)); \
		break; \
	case CR_VERTEXATTRIB3F_OPCODE: \
		__convert_f3 (vdata, (GLfloat *) (data)); \
		break; \
	case CR_VERTEXATTRIB4F_OPCODE: \
		__convert_f4 (vdata, (GLfloat *) (data)); \
		break; \
	case CR_VERTEXATTRIB1D_OPCODE: \
		__convert_d1 (vdata, (GLdouble *) (data)); \
		break; \
	case CR_VERTEXATTRIB2D_OPCODE: \
		__convert_d2 (vdata, (GLdouble *) (data)); \
		break; \
	case CR_VERTEXATTRIB3D_OPCODE: \
		__convert_d3 (vdata, (GLdouble *) (data)); \
		break; \
	case CR_VERTEXATTRIB4D_OPCODE: \
		__convert_d4 (vdata, (GLdouble *) (data)); \
		break; \
	case CR_VERTEXATTRIB1B_OPCODE: \
		__convert_b1 (vdata, (GLbyte *) (data)); \
		break; \
	case CR_VERTEXATTRIB2B_OPCODE: \
		__convert_b2 (vdata, (GLbyte *) (data)); \
		break; \
	case CR_VERTEXATTRIB3B_OPCODE: \
		__convert_b3 (vdata, (GLbyte *) (data)); \
		break; \
	case CR_VERTEXATTRIB4B_OPCODE: \
		__convert_b4 (vdata, (GLbyte *) (data)); \
		break; \
	case CR_VERTEXATTRIB1I_OPCODE: \
		__convert_i1 (vdata, (GLint *) (data)); \
		break; \
	case CR_VERTEXATTRIB2I_OPCODE: \
		__convert_i2 (vdata, (GLint *) (data)); \
		break; \
	case CR_VERTEXATTRIB3I_OPCODE: \
		__convert_i3 (vdata, (GLint *) (data)); \
		break; \
	case CR_VERTEXATTRIB4I_OPCODE: \
		__convert_i4 (vdata, (GLint *) (data)); \
		break; \
	case CR_VERTEXATTRIB1UB_OPCODE: \
		__convert_ub1 (vdata, (GLubyte *) (data)); \
		break; \
	case CR_VERTEXATTRIB2UB_OPCODE: \
		__convert_ub2 (vdata, (GLubyte *) (data)); \
		break; \
	case CR_VERTEXATTRIB3UB_OPCODE: \
		__convert_ub3 (vdata, (GLubyte *) (data)); \
		break; \
	case CR_VERTEXATTRIB4UB_OPCODE: \
		__convert_ub4 (vdata, (GLubyte *) (data)); \
		break; \
	case CR_VERTEXATTRIB1UI_OPCODE: \
		__convert_ui1 (vdata, (GLuint *) (data)); \
		break; \
	case CR_VERTEXATTRIB2UI_OPCODE: \
		__convert_ui2 (vdata, (GLuint *) (data)); \
		break; \
	case CR_VERTEXATTRIB3UI_OPCODE: \
		__convert_ui3 (vdata, (GLuint *) (data)); \
		break; \
	case CR_VERTEXATTRIB4UI_OPCODE: \
		__convert_ui4 (vdata, (GLuint *) (data)); \
		break; \
	case CR_VERTEXATTRIB1US_OPCODE: \
		__convert_us1 (vdata, (GLushort *) (data)); \
		break; \
	case CR_VERTEXATTRIB2US_OPCODE: \
		__convert_us2 (vdata, (GLushort *) (data)); \
		break; \
	case CR_VERTEXATTRIB3US_OPCODE: \
		__convert_us3 (vdata, (GLushort *) (data)); \
		break; \
	case CR_VERTEXATTRIB4US_OPCODE: \
		__convert_us4 (vdata, (GLushort *) (data)); \
		break; \
	case CR_VERTEXATTRIB1UB_OPCODE: \
		__convert_rescale_ub1 (vdata, (GLubyte *) (data)); \
		break; \
	case CR_VERTEXATTRIB2UB_OPCODE: \
		__convert_rescale_ub2 (vdata, (GLubyte *) (data)); \
		break; \
	case CR_VERTEXATTRIB3UB_OPCODE: \
		__convert_rescale_ub3 (vdata, (GLubyte *) (data)); \
		break; \
	case CR_VERTEXATTRIB4UB_OPCODE: \
		__convert_rescale_ub4 (vdata, (GLubyte *) (data)); \
		break; \
	case CR_VERTEXATTRIB1US_OPCODE: \
		__convert_rescale_us1 (vdata, (GLushort *) (data)); \
		break; \
	case CR_VERTEXATTRIB2US_OPCODE: \
		__convert_rescale_us2 (vdata, (GLushort *) (data)); \
		break; \
	case CR_VERTEXATTRIB3US_OPCODE: \
		__convert_rescale_us3 (vdata, (GLushort *) (data)); \
		break; \
	case CR_VERTEXATTRIB4US_OPCODE: \
		__convert_rescale_us4 (vdata, (GLushort *) (data)); \
		break; \
	case CR_VERTEXATTRIB1UI_OPCODE: \
		__convert_rescale_ui1 (vdata, (GLuint *) (data)); \
		break; \
	case CR_VERTEXATTRIB2UI_OPCODE: \
		__convert_rescale_ui2 (vdata, (GLuint *) (data)); \
		break; \
	case CR_VERTEXATTRIB3UI_OPCODE: \
		__convert_rescale_ui3 (vdata, (GLuint *) (data)); \
		break; \
	case CR_VERTEXATTRIB4UI_OPCODE: \
		__convert_rescale_ui4 (vdata, (GLuint *) (data)); \
		break; \
	case CR_VERTEXATTRIB1B_OPCODE: \
		__convert_rescale_b1 (vdata, (GLbyte *) (data)); \
		break; \
	case CR_VERTEXATTRIB2B_OPCODE: \
		__convert_rescale_b2 (vdata, (GLbyte *) (data)); \
		break; \
	case CR_VERTEXATTRIB3B_OPCODE: \
		__convert_rescale_b3 (vdata, (GLbyte *) (data)); \
		break; \
	case CR_VERTEXATTRIB4B_OPCODE: \
		__convert_rescale_b4 (vdata, (GLbyte *) (data)); \
		break; \
	case CR_VERTEXATTRIB1S_OPCODE: \
		__convert_rescale_s1 (vdata, (GLshort *) (data)); \
		break; \
	case CR_VERTEXATTRIB2S_OPCODE: \
		__convert_rescale_s2 (vdata, (GLshort *) (data)); \
		break; \
	case CR_VERTEXATTRIB3S_OPCODE: \
		__convert_rescale_s3 (vdata, (GLshort *) (data)); \
		break; \
	case CR_VERTEXATTRIB4S_OPCODE: \
		__convert_rescale_s4 (vdata, (GLshort *) (data)); \
		break; \
	case CR_VERTEXATTRIB1I_OPCODE: \
		__convert_rescale_i1 (vdata, (GLint *) (data)); \
		break; \
	case CR_VERTEXATTRIB2I_OPCODE: \
		__convert_rescale_i2 (vdata, (GLint *) (data)); \
		break; \
	case CR_VERTEXATTRIB3I_OPCODE: \
		__convert_rescale_i3 (vdata, (GLint *) (data)); \
		break; \
	case CR_VERTEXATTRIB4I_OPCODE: \
		__convert_rescale_i4 (vdata, (GLint *) (data)); \
		break; \
	default: \
		crSimpleError ( "Unknown opcode in VPINCH_CONVERT_VERTEXATTRIB" ); \
	}\
	(dst).x = vdata[0];\
	(dst).y = vdata[1];\
	(dst).z = vdata[2];\
	(dst).w = vdata[3];\
}

#define VPINCH_CONVERT_FOGCOORD(op,data,dst) \
{\
	GLfloat vdata[2] = { 0 , };\
	switch (op) { \
	case CR_FOGCOORD1F_OPCODE: \
		__convert_f1 (vdata, (GLfloat *) (data)); \
		break; \
	case CR_FOGCOORD1D_OPCODE: \
		__convert_d1 (vdata, (GLdouble *) (data)); \
		break; \
	default: \
		crSimpleError ( "Unknown opcode in VPINCH_CONVERT_FOGCOORD" ); \
	}\
}

#define VPINCH_CONVERT_EDGEFLAG(op,data,dst) \
{\
	GLfloat vdata[2] = { 1 , };\
	switch (op) { \
	case CR_EDGEFLAG_OPCODE: \
		__convert_l1 (vdata, (GLboolean *) (data)); \
		break; \
	default: \
		crSimpleError ( "Unknown opcode in VPINCH_CONVERT_EDGEFLAG" ); \
	}\
	(dst).[0] = vdata[0];\
}

#define VPINCH_CONVERT_NORMAL(op,data,dst) \
{\
	GLfloat vdata[4] = { 0 , 0 , 0 , };\
	switch (op) { \
	case CR_NORMAL3B_OPCODE: \
		__convert_rescale_b3 (vdata, (GLbyte *) (data)); \
		break; \
	case CR_NORMAL3S_OPCODE: \
		__convert_rescale_s3 (vdata, (GLshort *) (data)); \
		break; \
	case CR_NORMAL3I_OPCODE: \
		__convert_rescale_i3 (vdata, (GLint *) (data)); \
		break; \
	case CR_NORMAL3F_OPCODE: \
		__convert_f3 (vdata, (GLfloat *) (data)); \
		break; \
	case CR_NORMAL3D_OPCODE: \
		__convert_d3 (vdata, (GLdouble *) (data)); \
		break; \
	default: \
		crSimpleError ( "Unknown opcode in VPINCH_CONVERT_NORMAL" ); \
	}\
	(dst).[0] = vdata[0];\
	(dst).[1] = vdata[1];\
	(dst).[2] = vdata[2];\
}

#define VPINCH_CONVERT_COLOR(op,data,dst) \
{\
	GLfloat vdata[5] = { 0 , 0 , 0 , 1 , };\
	switch (op) { \
	case CR_COLOR3B_OPCODE: \
		__convert_rescale_b3 (vdata, (GLbyte *) (data)); \
		break; \
	case CR_COLOR4B_OPCODE: \
		__convert_rescale_b4 (vdata, (GLbyte *) (data)); \
		break; \
	case CR_COLOR3UB_OPCODE: \
		__convert_rescale_ub3 (vdata, (GLubyte *) (data)); \
		break; \
	case CR_COLOR4UB_OPCODE: \
		__convert_rescale_ub4 (vdata, (GLubyte *) (data)); \
		break; \
	case CR_COLOR3S_OPCODE: \
		__convert_rescale_s3 (vdata, (GLshort *) (data)); \
		break; \
	case CR_COLOR4S_OPCODE: \
		__convert_rescale_s4 (vdata, (GLshort *) (data)); \
		break; \
	case CR_COLOR3US_OPCODE: \
		__convert_rescale_us3 (vdata, (GLushort *) (data)); \
		break; \
	case CR_COLOR4US_OPCODE: \
		__convert_rescale_us4 (vdata, (GLushort *) (data)); \
		break; \
	case CR_COLOR3I_OPCODE: \
		__convert_rescale_i3 (vdata, (GLint *) (data)); \
		break; \
	case CR_COLOR4I_OPCODE: \
		__convert_rescale_i4 (vdata, (GLint *) (data)); \
		break; \
	case CR_COLOR3UI_OPCODE: \
		__convert_rescale_ui3 (vdata, (GLuint *) (data)); \
		break; \
	case CR_COLOR4UI_OPCODE: \
		__convert_rescale_ui4 (vdata, (GLuint *) (data)); \
		break; \
	case CR_COLOR3F_OPCODE: \
		__convert_f3 (vdata, (GLfloat *) (data)); \
		break; \
	case CR_COLOR4F_OPCODE: \
		__convert_f4 (vdata, (GLfloat *) (data)); \
		break; \
	case CR_COLOR3D_OPCODE: \
		__convert_d3 (vdata, (GLdouble *) (data)); \
		break; \
	case CR_COLOR4D_OPCODE: \
		__convert_d4 (vdata, (GLdouble *) (data)); \
		break; \
	default: \
		crSimpleError ( "Unknown opcode in VPINCH_CONVERT_COLOR" ); \
	}\
	(dst).[0] = vdata[0];\
	(dst).[1] = vdata[1];\
	(dst).[2] = vdata[2];\
	(dst).[3] = vdata[3];\
}

#define VPINCH_CONVERT_SECONDARYCOLOR(op,data,dst) \
{\
	GLfloat vdata[4] = { 0 , 0 , 0 , };\
	switch (op) { \
	case CR_SECONDARYCOLOR3B_OPCODE: \
		__convert_rescale_b3 (vdata, (GLbyte *) (data)); \
		break; \
	case CR_SECONDARYCOLOR3UB_OPCODE: \
		__convert_rescale_ub3 (vdata, (GLubyte *) (data)); \
		break; \
	case CR_SECONDARYCOLOR3S_OPCODE: \
		__convert_rescale_s3 (vdata, (GLshort *) (data)); \
		break; \
	case CR_SECONDARYCOLOR3US_OPCODE: \
		__convert_rescale_us3 (vdata, (GLushort *) (data)); \
		break; \
	case CR_SECONDARYCOLOR3I_OPCODE: \
		__convert_rescale_i3 (vdata, (GLint *) (data)); \
		break; \
	case CR_SECONDARYCOLOR3UI_OPCODE: \
		__convert_rescale_ui3 (vdata, (GLuint *) (data)); \
		break; \
	case CR_SECONDARYCOLOR3F_OPCODE: \
		__convert_f3 (vdata, (GLfloat *) (data)); \
		break; \
	case CR_SECONDARYCOLOR3D_OPCODE: \
		__convert_d3 (vdata, (GLdouble *) (data)); \
		break; \
	default: \
		crSimpleError ( "Unknown opcode in VPINCH_CONVERT_SECONDARYCOLOR" ); \
	}\
	(dst).[0] = vdata[0];\
	(dst).[1] = vdata[1];\
	(dst).[2] = vdata[2];\
}

#define VPINCH_CONVERT_TEXCOORD(op,data,dst) \
{\
	GLfloat vdata[5] = { 0 , 0 , 0 , 1 , };\
	switch (op) { \
	case CR_TEXCOORD1S_OPCODE: \
		__convert_s1 (vdata, (GLshort *) (data)); \
		break; \
	case CR_TEXCOORD2S_OPCODE: \
		__convert_s2 (vdata, (GLshort *) (data)); \
		break; \
	case CR_TEXCOORD3S_OPCODE: \
		__convert_s3 (vdata, (GLshort *) (data)); \
		break; \
	case CR_TEXCOORD4S_OPCODE: \
		__convert_s4 (vdata, (GLshort *) (data)); \
		break; \
	case CR_TEXCOORD1I_OPCODE: \
		__convert_i1 (vdata, (GLint *) (data)); \
		break; \
	case CR_TEXCOORD2I_OPCODE: \
		__convert_i2 (vdata, (GLint *) (data)); \
		break; \
	case CR_TEXCOORD3I_OPCODE: \
		__convert_i3 (vdata, (GLint *) (data)); \
		break; \
	case CR_TEXCOORD4I_OPCODE: \
		__convert_i4 (vdata, (GLint *) (data)); \
		break; \
	case CR_TEXCOORD1F_OPCODE: \
		__convert_f1 (vdata, (GLfloat *) (data)); \
		break; \
	case CR_TEXCOORD2F_OPCODE: \
		__convert_f2 (vdata, (GLfloat *) (data)); \
		break; \
	case CR_TEXCOORD3F_OPCODE: \
		__convert_f3 (vdata, (GLfloat *) (data)); \
		break; \
	case CR_TEXCOORD4F_OPCODE: \
		__convert_f4 (vdata, (GLfloat *) (data)); \
		break; \
	case CR_TEXCOORD1D_OPCODE: \
		__convert_d1 (vdata, (GLdouble *) (data)); \
		break; \
	case CR_TEXCOORD2D_OPCODE: \
		__convert_d2 (vdata, (GLdouble *) (data)); \
		break; \
	case CR_TEXCOORD3D_OPCODE: \
		__convert_d3 (vdata, (GLdouble *) (data)); \
		break; \
	case CR_TEXCOORD4D_OPCODE: \
		__convert_d4 (vdata, (GLdouble *) (data)); \
		break; \
	default: \
		crSimpleError ( "Unknown opcode in VPINCH_CONVERT_TEXCOORD" ); \
	}\
	(dst).[0] = vdata[0];\
	(dst).[1] = vdata[1];\
	(dst).[2] = vdata[2];\
	(dst).[3] = vdata[3];\
}



void crStateCurrentRecover( void )
{
	const unsigned char *v;
	convert_func convert=NULL;
	CRContext *g = GetCurrentContext();
	CRCurrentState *c = &(g->current);
	CRStateBits *sb = GetCurrentBits();
	CRCurrentBits *cb = &(sb->current);
	static const GLfloat color_default[4]			= {0.0f, 0.0f, 0.0f, 1.0f};
	static const GLfloat secondaryColor_default[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	static const GLfloat texCoord_default[4]	= {0.0f, 0.0f, 0.0f, 1.0f};
	static const GLfloat normal_default[4]		= {0.0f, 0.0f, 0.0f, 1.0f};
	static const GLfloat index_default			= 0.0f;
	static const GLboolean edgeFlag_default		= GL_TRUE;
	static const GLfloat vertexAttrib_default[4] = {0.0f, 0.0f, 0.0f, 1.0f};
	static const GLfloat fogCoord_default = 0.0f;
	GLnormal_p		*normal		= &(c->current->c.normal);
	GLcolor_p		*color		= &(c->current->c.color);
	GLsecondarycolor_p *secondaryColor = &(c->current->c.secondaryColor);
	GLtexcoord_p	*texCoord	= &(c->current->c.texCoord);
	GLindex_p		*index		= &(c->current->c.index);
	GLedgeflag_p	*edgeFlag	= &(c->current->c.edgeFlag);
	GLvertexattrib_p *vertexAttrib = &(c->current->c.vertexAttrib);
	GLfogcoord_p *fogCoord = &(c->current->c.fogCoord);
	unsigned int i;
	CRbitvalue nbitID[CR_MAX_BITARRAY];

	/* 
	 * If the calling SPU hasn't called crStateSetCurrentPointers()
	 * we can't recover anything, so abort now. (i.e. we don't have
	 * a pincher, oh, and just emit the message once).
	 */
	if (!c->current) {
		static int donewarning = 0;
		if (!donewarning)
			crWarning("No pincher, please call crStateSetCurrentPointers() in your SPU");
		donewarning = 1;
		return; /* never get here */
	}

	c->attribsUsedMask = c->current->attribsUsedMask;
	
	/* silence warnings */
	(void) __convert_b1;
	(void) __convert_b2;
	(void) __convert_b3;
	(void) __convert_b4;
	(void) __convert_ui1;
	(void) __convert_ui2;
	(void) __convert_ui3;
	(void) __convert_ui4;
	(void) __convert_l1;
	(void) __convert_l2;
	(void) __convert_l3;
	(void) __convert_l4;
	(void) __convert_us1;
	(void) __convert_us2;
	(void) __convert_us3;
	(void) __convert_us4;
	(void) __convert_ub1;
	(void) __convert_ub2;
	(void) __convert_ub3;
	(void) __convert_ub4;
	(void) __convert_rescale_s1;
	(void) __convert_rescale_s2;
	(void) __convert_rescale_b1;
	(void) __convert_rescale_b2;
	(void) __convert_rescale_ui1;
	(void) __convert_rescale_ui2;
	(void) __convert_rescale_i1;
	(void) __convert_rescale_i2;
	(void) __convert_rescale_us1;
	(void) __convert_rescale_us2;
	(void) __convert_rescale_ub1;
	(void) __convert_rescale_ub2;
	(void) __convert_Ni1;
	(void) __convert_Ni2;
	(void) __convert_Ni3;
	(void) __convert_Ni4;
	(void) __convert_Nb1;
	(void) __convert_Nb2;
	(void) __convert_Nb3;
	(void) __convert_Nb4;
	(void) __convert_Nus1;
	(void) __convert_Nus2;
	(void) __convert_Nus3;
	(void) __convert_Nus4;
	(void) __convert_Nui1;
	(void) __convert_Nui2;
	(void) __convert_Nui3;
	(void) __convert_Nui4;
	(void) __convert_Ns1;
	(void) __convert_Ns2;
	(void) __convert_Ns3;
	(void) __convert_Ns4;
	(void) __convert_Nub1;
	(void) __convert_Nub2;
	(void) __convert_Nub3;
	(void) __convert_Nub4;

	DIRTY(nbitID, g->neg_bitid);

	/* Save pre state */
	for (i = 0; i < CR_MAX_VERTEX_ATTRIBS; i++) {
		COPY_4V(c->vertexAttribPre[i]  , c->vertexAttrib[i]);
	}
	c->edgeFlagPre = c->edgeFlag;
	c->colorIndexPre = c->colorIndex;


	/* Index */
	v=NULL;
	if (v < index->ub1)
	{
		v = index->ub1;
		convert = (convert_func) __convert_ub1;
	}
	if (v < index->s1)
	{
		v = index->s1;
		convert = (convert_func) __convert_s1;
	}
	if (v < index->i1)
	{
		v = index->i1;
		convert = (convert_func) __convert_i1;
	}
	if (v < index->f1)
	{
		v = index->f1;
		convert = (convert_func) __convert_f1;
	}
	if (v < index->d1)
	{
		v = index->d1;
		convert = (convert_func) __convert_d1;
	}

	if (v != NULL) {
		c->colorIndex =  index_default;
		convert(&(c->colorIndex), v);
		DIRTY(cb->colorIndex, nbitID);
		DIRTY(cb->dirty, nbitID);
	}
	index->ptr = v;
	/* VertexAttrib */
	v=NULL;
	for (i = 0 ; i < CR_MAX_VERTEX_ATTRIBS ; i++)
	{
		if (v < vertexAttrib->s1[i])
		{
			v = vertexAttrib->s1[i];
			convert = (convert_func) __convert_s1;
		}
		if (v < vertexAttrib->s2[i])
		{
			v = vertexAttrib->s2[i];
			convert = (convert_func) __convert_s2;
		}
		if (v < vertexAttrib->s3[i])
		{
			v = vertexAttrib->s3[i];
			convert = (convert_func) __convert_s3;
		}
		if (v < vertexAttrib->s4[i])
		{
			v = vertexAttrib->s4[i];
			convert = (convert_func) __convert_s4;
		}
		if (v < vertexAttrib->f1[i])
		{
			v = vertexAttrib->f1[i];
			convert = (convert_func) __convert_f1;
		}
		if (v < vertexAttrib->f2[i])
		{
			v = vertexAttrib->f2[i];
			convert = (convert_func) __convert_f2;
		}
		if (v < vertexAttrib->f3[i])
		{
			v = vertexAttrib->f3[i];
			convert = (convert_func) __convert_f3;
		}
		if (v < vertexAttrib->f4[i])
		{
			v = vertexAttrib->f4[i];
			convert = (convert_func) __convert_f4;
		}
		if (v < vertexAttrib->d1[i])
		{
			v = vertexAttrib->d1[i];
			convert = (convert_func) __convert_d1;
		}
		if (v < vertexAttrib->d2[i])
		{
			v = vertexAttrib->d2[i];
			convert = (convert_func) __convert_d2;
		}
		if (v < vertexAttrib->d3[i])
		{
			v = vertexAttrib->d3[i];
			convert = (convert_func) __convert_d3;
		}
		if (v < vertexAttrib->d4[i])
		{
			v = vertexAttrib->d4[i];
			convert = (convert_func) __convert_d4;
		}
		if (v < vertexAttrib->b1[i])
		{
			v = vertexAttrib->b1[i];
			convert = (convert_func) __convert_b1;
		}
		if (v < vertexAttrib->b2[i])
		{
			v = vertexAttrib->b2[i];
			convert = (convert_func) __convert_b2;
		}
		if (v < vertexAttrib->b3[i])
		{
			v = vertexAttrib->b3[i];
			convert = (convert_func) __convert_b3;
		}
		if (v < vertexAttrib->b4[i])
		{
			v = vertexAttrib->b4[i];
			convert = (convert_func) __convert_b4;
		}
		if (v < vertexAttrib->i1[i])
		{
			v = vertexAttrib->i1[i];
			convert = (convert_func) __convert_i1;
		}
		if (v < vertexAttrib->i2[i])
		{
			v = vertexAttrib->i2[i];
			convert = (convert_func) __convert_i2;
		}
		if (v < vertexAttrib->i3[i])
		{
			v = vertexAttrib->i3[i];
			convert = (convert_func) __convert_i3;
		}
		if (v < vertexAttrib->i4[i])
		{
			v = vertexAttrib->i4[i];
			convert = (convert_func) __convert_i4;
		}
		if (v < vertexAttrib->ub1[i])
		{
			v = vertexAttrib->ub1[i];
			convert = (convert_func) __convert_ub1;
		}
		if (v < vertexAttrib->ub2[i])
		{
			v = vertexAttrib->ub2[i];
			convert = (convert_func) __convert_ub2;
		}
		if (v < vertexAttrib->ub3[i])
		{
			v = vertexAttrib->ub3[i];
			convert = (convert_func) __convert_ub3;
		}
		if (v < vertexAttrib->ub4[i])
		{
			v = vertexAttrib->ub4[i];
			convert = (convert_func) __convert_ub4;
		}
		if (v < vertexAttrib->ui1[i])
		{
			v = vertexAttrib->ui1[i];
			convert = (convert_func) __convert_ui1;
		}
		if (v < vertexAttrib->ui2[i])
		{
			v = vertexAttrib->ui2[i];
			convert = (convert_func) __convert_ui2;
		}
		if (v < vertexAttrib->ui3[i])
		{
			v = vertexAttrib->ui3[i];
			convert = (convert_func) __convert_ui3;
		}
		if (v < vertexAttrib->ui4[i])
		{
			v = vertexAttrib->ui4[i];
			convert = (convert_func) __convert_ui4;
		}
		if (v < vertexAttrib->us1[i])
		{
			v = vertexAttrib->us1[i];
			convert = (convert_func) __convert_us1;
		}
		if (v < vertexAttrib->us2[i])
		{
			v = vertexAttrib->us2[i];
			convert = (convert_func) __convert_us2;
		}
		if (v < vertexAttrib->us3[i])
		{
			v = vertexAttrib->us3[i];
			convert = (convert_func) __convert_us3;
		}
		if (v < vertexAttrib->us4[i])
		{
			v = vertexAttrib->us4[i];
			convert = (convert_func) __convert_us4;
		}
		if (v < vertexAttrib->Nub1[i])
		{
			v = vertexAttrib->Nub1[i];
			convert = (convert_func) __convert_rescale_Nub1;
		}
		if (v < vertexAttrib->Nub2[i])
		{
			v = vertexAttrib->Nub2[i];
			convert = (convert_func) __convert_rescale_Nub2;
		}
		if (v < vertexAttrib->Nub3[i])
		{
			v = vertexAttrib->Nub3[i];
			convert = (convert_func) __convert_rescale_Nub3;
		}
		if (v < vertexAttrib->Nub4[i])
		{
			v = vertexAttrib->Nub4[i];
			convert = (convert_func) __convert_rescale_Nub4;
		}
		if (v < vertexAttrib->Nus1[i])
		{
			v = vertexAttrib->Nus1[i];
			convert = (convert_func) __convert_rescale_Nus1;
		}
		if (v < vertexAttrib->Nus2[i])
		{
			v = vertexAttrib->Nus2[i];
			convert = (convert_func) __convert_rescale_Nus2;
		}
		if (v < vertexAttrib->Nus3[i])
		{
			v = vertexAttrib->Nus3[i];
			convert = (convert_func) __convert_rescale_Nus3;
		}
		if (v < vertexAttrib->Nus4[i])
		{
			v = vertexAttrib->Nus4[i];
			convert = (convert_func) __convert_rescale_Nus4;
		}
		if (v < vertexAttrib->Nui1[i])
		{
			v = vertexAttrib->Nui1[i];
			convert = (convert_func) __convert_rescale_Nui1;
		}
		if (v < vertexAttrib->Nui2[i])
		{
			v = vertexAttrib->Nui2[i];
			convert = (convert_func) __convert_rescale_Nui2;
		}
		if (v < vertexAttrib->Nui3[i])
		{
			v = vertexAttrib->Nui3[i];
			convert = (convert_func) __convert_rescale_Nui3;
		}
		if (v < vertexAttrib->Nui4[i])
		{
			v = vertexAttrib->Nui4[i];
			convert = (convert_func) __convert_rescale_Nui4;
		}
		if (v < vertexAttrib->Nb1[i])
		{
			v = vertexAttrib->Nb1[i];
			convert = (convert_func) __convert_rescale_Nb1;
		}
		if (v < vertexAttrib->Nb2[i])
		{
			v = vertexAttrib->Nb2[i];
			convert = (convert_func) __convert_rescale_Nb2;
		}
		if (v < vertexAttrib->Nb3[i])
		{
			v = vertexAttrib->Nb3[i];
			convert = (convert_func) __convert_rescale_Nb3;
		}
		if (v < vertexAttrib->Nb4[i])
		{
			v = vertexAttrib->Nb4[i];
			convert = (convert_func) __convert_rescale_Nb4;
		}
		if (v < vertexAttrib->Ns1[i])
		{
			v = vertexAttrib->Ns1[i];
			convert = (convert_func) __convert_rescale_Ns1;
		}
		if (v < vertexAttrib->Ns2[i])
		{
			v = vertexAttrib->Ns2[i];
			convert = (convert_func) __convert_rescale_Ns2;
		}
		if (v < vertexAttrib->Ns3[i])
		{
			v = vertexAttrib->Ns3[i];
			convert = (convert_func) __convert_rescale_Ns3;
		}
		if (v < vertexAttrib->Ns4[i])
		{
			v = vertexAttrib->Ns4[i];
			convert = (convert_func) __convert_rescale_Ns4;
		}
		if (v < vertexAttrib->Ni1[i])
		{
			v = vertexAttrib->Ni1[i];
			convert = (convert_func) __convert_rescale_Ni1;
		}
		if (v < vertexAttrib->Ni2[i])
		{
			v = vertexAttrib->Ni2[i];
			convert = (convert_func) __convert_rescale_Ni2;
		}
		if (v < vertexAttrib->Ni3[i])
		{
			v = vertexAttrib->Ni3[i];
			convert = (convert_func) __convert_rescale_Ni3;
		}
		if (v < vertexAttrib->Ni4[i])
		{
			v = vertexAttrib->Ni4[i];
			convert = (convert_func) __convert_rescale_Ni4;
		}

		if (v != NULL) {
			COPY_4V(c->vertexAttrib[i], vertexAttrib_default);
			convert(&(c->vertexAttrib[i][0]), v);
			DIRTY(cb->vertexAttrib[i], nbitID);
			DIRTY(cb->dirty, nbitID);
		}
		vertexAttrib->ptr[i] = v;
	}
	/* FogCoord */
	v=NULL;
	if (v < fogCoord->f1)
	{
		v = fogCoord->f1;
		convert = (convert_func) __convert_f1;
	}
	if (v < fogCoord->d1)
	{
		v = fogCoord->d1;
		convert = (convert_func) __convert_d1;
	}

	if (v != NULL) {
		c->vertexAttrib[VERT_ATTRIB_FOG][0] =  fogCoord_default;
		convert(&(c->vertexAttrib[VERT_ATTRIB_FOG][0]), v);
		DIRTY(cb->vertexAttrib[VERT_ATTRIB_FOG], nbitID);
		DIRTY(cb->dirty, nbitID);
	}
	fogCoord->ptr = v;
	/* EdgeFlag */
	v=NULL;
	if (v < edgeFlag->l1)
	{
		v = edgeFlag->l1;
		convert = (convert_func) __convert_l1;
	}

	if (v != NULL) {
		c->edgeFlag =  edgeFlag_default;
		__convert_boolean (&c->edgeFlag, v);
		DIRTY(cb->edgeFlag, nbitID);
		DIRTY(cb->dirty, nbitID);
	}
	edgeFlag->ptr = v;
	/* Normal */
	v=NULL;
	if (v < normal->b3)
	{
		v = normal->b3;
		convert = (convert_func) __convert_rescale_b3;
	}
	if (v < normal->s3)
	{
		v = normal->s3;
		convert = (convert_func) __convert_rescale_s3;
	}
	if (v < normal->i3)
	{
		v = normal->i3;
		convert = (convert_func) __convert_rescale_i3;
	}
	if (v < normal->f3)
	{
		v = normal->f3;
		convert = (convert_func) __convert_f3;
	}
	if (v < normal->d3)
	{
		v = normal->d3;
		convert = (convert_func) __convert_d3;
	}

	if (v != NULL) {
		COPY_4V(c->vertexAttrib[VERT_ATTRIB_NORMAL], normal_default);
		convert(&(c->vertexAttrib[VERT_ATTRIB_NORMAL][0]), v);
		DIRTY(cb->vertexAttrib[VERT_ATTRIB_NORMAL], nbitID);
		DIRTY(cb->dirty, nbitID);
	}
	normal->ptr = v;
	/* Color */
	v=NULL;
	if (v < color->b3)
	{
		v = color->b3;
		convert = (convert_func) __convert_rescale_b3;
	}
	if (v < color->b4)
	{
		v = color->b4;
		convert = (convert_func) __convert_rescale_b4;
	}
	if (v < color->ub3)
	{
		v = color->ub3;
		convert = (convert_func) __convert_rescale_ub3;
	}
	if (v < color->ub4)
	{
		v = color->ub4;
		convert = (convert_func) __convert_rescale_ub4;
	}
	if (v < color->s3)
	{
		v = color->s3;
		convert = (convert_func) __convert_rescale_s3;
	}
	if (v < color->s4)
	{
		v = color->s4;
		convert = (convert_func) __convert_rescale_s4;
	}
	if (v < color->us3)
	{
		v = color->us3;
		convert = (convert_func) __convert_rescale_us3;
	}
	if (v < color->us4)
	{
		v = color->us4;
		convert = (convert_func) __convert_rescale_us4;
	}
	if (v < color->i3)
	{
		v = color->i3;
		convert = (convert_func) __convert_rescale_i3;
	}
	if (v < color->i4)
	{
		v = color->i4;
		convert = (convert_func) __convert_rescale_i4;
	}
	if (v < color->ui3)
	{
		v = color->ui3;
		convert = (convert_func) __convert_rescale_ui3;
	}
	if (v < color->ui4)
	{
		v = color->ui4;
		convert = (convert_func) __convert_rescale_ui4;
	}
	if (v < color->f3)
	{
		v = color->f3;
		convert = (convert_func) __convert_f3;
	}
	if (v < color->f4)
	{
		v = color->f4;
		convert = (convert_func) __convert_f4;
	}
	if (v < color->d3)
	{
		v = color->d3;
		convert = (convert_func) __convert_d3;
	}
	if (v < color->d4)
	{
		v = color->d4;
		convert = (convert_func) __convert_d4;
	}

	if (v != NULL) {
		COPY_4V(c->vertexAttrib[VERT_ATTRIB_COLOR0], color_default);
		convert(&(c->vertexAttrib[VERT_ATTRIB_COLOR0][0]), v);
		DIRTY(cb->vertexAttrib[VERT_ATTRIB_COLOR0], nbitID);
		DIRTY(cb->dirty, nbitID);
	}
	color->ptr = v;
	/* SecondaryColor */
	v=NULL;
	if (v < secondaryColor->b3)
	{
		v = secondaryColor->b3;
		convert = (convert_func) __convert_rescale_b3;
	}
	if (v < secondaryColor->ub3)
	{
		v = secondaryColor->ub3;
		convert = (convert_func) __convert_rescale_ub3;
	}
	if (v < secondaryColor->s3)
	{
		v = secondaryColor->s3;
		convert = (convert_func) __convert_rescale_s3;
	}
	if (v < secondaryColor->us3)
	{
		v = secondaryColor->us3;
		convert = (convert_func) __convert_rescale_us3;
	}
	if (v < secondaryColor->i3)
	{
		v = secondaryColor->i3;
		convert = (convert_func) __convert_rescale_i3;
	}
	if (v < secondaryColor->ui3)
	{
		v = secondaryColor->ui3;
		convert = (convert_func) __convert_rescale_ui3;
	}
	if (v < secondaryColor->f3)
	{
		v = secondaryColor->f3;
		convert = (convert_func) __convert_f3;
	}
	if (v < secondaryColor->d3)
	{
		v = secondaryColor->d3;
		convert = (convert_func) __convert_d3;
	}

	if (v != NULL) {
		COPY_4V(c->vertexAttrib[VERT_ATTRIB_COLOR1],  secondaryColor_default);
		convert(&(c->vertexAttrib[VERT_ATTRIB_COLOR1][0]), v);
		DIRTY(cb->vertexAttrib[VERT_ATTRIB_COLOR1], nbitID);
		DIRTY(cb->dirty, nbitID);
	}
	secondaryColor->ptr = v;
	/* TexCoord */
	v=NULL;
	for (i = 0 ; i < CR_MAX_TEXTURE_UNITS ; i++)
	{
		if (v < texCoord->s1[i])
		{
			v = texCoord->s1[i];
			convert = (convert_func) __convert_s1;
		}
		if (v < texCoord->s2[i])
		{
			v = texCoord->s2[i];
			convert = (convert_func) __convert_s2;
		}
		if (v < texCoord->s3[i])
		{
			v = texCoord->s3[i];
			convert = (convert_func) __convert_s3;
		}
		if (v < texCoord->s4[i])
		{
			v = texCoord->s4[i];
			convert = (convert_func) __convert_s4;
		}
		if (v < texCoord->i1[i])
		{
			v = texCoord->i1[i];
			convert = (convert_func) __convert_i1;
		}
		if (v < texCoord->i2[i])
		{
			v = texCoord->i2[i];
			convert = (convert_func) __convert_i2;
		}
		if (v < texCoord->i3[i])
		{
			v = texCoord->i3[i];
			convert = (convert_func) __convert_i3;
		}
		if (v < texCoord->i4[i])
		{
			v = texCoord->i4[i];
			convert = (convert_func) __convert_i4;
		}
		if (v < texCoord->f1[i])
		{
			v = texCoord->f1[i];
			convert = (convert_func) __convert_f1;
		}
		if (v < texCoord->f2[i])
		{
			v = texCoord->f2[i];
			convert = (convert_func) __convert_f2;
		}
		if (v < texCoord->f3[i])
		{
			v = texCoord->f3[i];
			convert = (convert_func) __convert_f3;
		}
		if (v < texCoord->f4[i])
		{
			v = texCoord->f4[i];
			convert = (convert_func) __convert_f4;
		}
		if (v < texCoord->d1[i])
		{
			v = texCoord->d1[i];
			convert = (convert_func) __convert_d1;
		}
		if (v < texCoord->d2[i])
		{
			v = texCoord->d2[i];
			convert = (convert_func) __convert_d2;
		}
		if (v < texCoord->d3[i])
		{
			v = texCoord->d3[i];
			convert = (convert_func) __convert_d3;
		}
		if (v < texCoord->d4[i])
		{
			v = texCoord->d4[i];
			convert = (convert_func) __convert_d4;
		}

		if (v != NULL) {
			COPY_4V(c->vertexAttrib[VERT_ATTRIB_TEX0 + i], texCoord_default);
			convert(&(c->vertexAttrib[VERT_ATTRIB_TEX0 + i][0]), v);
			DIRTY(cb->vertexAttrib[VERT_ATTRIB_TEX0 + i], nbitID);
			DIRTY(cb->dirty, nbitID);
		}
		texCoord->ptr[i] = v;
	}
}


void crStateCurrentRecoverNew(CRContext *g, CRCurrentStatePointers  *current)
{
    const unsigned char *v;
    convert_func convert=NULL;
    CRCurrentState *c = &(g->current);
    CRStateBits *sb = GetCurrentBits();
    CRCurrentBits *cb = &(sb->current);

    static const GLfloat vertexAttrib_default[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    GLvertexattrib_p *vertexAttrib = &(current->c.vertexAttrib);

    unsigned int i;
    CRbitvalue nbitID[CR_MAX_BITARRAY];


    /* silence warnings */
    (void) __convert_b1;
    (void) __convert_b2;
    (void) __convert_b3;
    (void) __convert_b4;
    (void) __convert_ui1;
    (void) __convert_ui2;
    (void) __convert_ui3;
    (void) __convert_ui4;
    (void) __convert_l1;
    (void) __convert_l2;
    (void) __convert_l3;
    (void) __convert_l4;
    (void) __convert_us1;
    (void) __convert_us2;
    (void) __convert_us3;
    (void) __convert_us4;
    (void) __convert_ub1;
    (void) __convert_ub2;
    (void) __convert_ub3;
    (void) __convert_ub4;
    (void) __convert_rescale_s1;
    (void) __convert_rescale_s2;
    (void) __convert_rescale_b1;
    (void) __convert_rescale_b2;
    (void) __convert_rescale_ui1;
    (void) __convert_rescale_ui2;
    (void) __convert_rescale_i1;
    (void) __convert_rescale_i2;
    (void) __convert_rescale_us1;
    (void) __convert_rescale_us2;
    (void) __convert_rescale_ub1;
    (void) __convert_rescale_ub2;
    (void) __convert_Ni1;
    (void) __convert_Ni2;
    (void) __convert_Ni3;
    (void) __convert_Ni4;
    (void) __convert_Nb1;
    (void) __convert_Nb2;
    (void) __convert_Nb3;
    (void) __convert_Nb4;
    (void) __convert_Nus1;
    (void) __convert_Nus2;
    (void) __convert_Nus3;
    (void) __convert_Nus4;
    (void) __convert_Nui1;
    (void) __convert_Nui2;
    (void) __convert_Nui3;
    (void) __convert_Nui4;
    (void) __convert_Ns1;
    (void) __convert_Ns2;
    (void) __convert_Ns3;
    (void) __convert_Ns4;
    (void) __convert_Nub1;
    (void) __convert_Nub2;
    (void) __convert_Nub3;
    (void) __convert_Nub4;



	/* VertexAttrib */
	if (current->changedVertexAttrib)
	{
		v=NULL;
		for (i = 0 ; i < CR_MAX_VERTEX_ATTRIBS ; i++)
		{
		if (!(current->changedVertexAttrib & (1 << i))) continue;
#ifdef DEBUG_misha
			if (vertexAttrib->s1[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->s1[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->s1[i])
			{
				v = vertexAttrib->s1[i];
				convert = (convert_func) __convert_s1;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->s2[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->s2[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->s2[i])
			{
				v = vertexAttrib->s2[i];
				convert = (convert_func) __convert_s2;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->s3[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->s3[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->s3[i])
			{
				v = vertexAttrib->s3[i];
				convert = (convert_func) __convert_s3;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->s4[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->s4[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->s4[i])
			{
				v = vertexAttrib->s4[i];
				convert = (convert_func) __convert_s4;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->f1[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->f1[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->f1[i])
			{
				v = vertexAttrib->f1[i];
				convert = (convert_func) __convert_f1;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->f2[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->f2[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->f2[i])
			{
				v = vertexAttrib->f2[i];
				convert = (convert_func) __convert_f2;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->f3[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->f3[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->f3[i])
			{
				v = vertexAttrib->f3[i];
				convert = (convert_func) __convert_f3;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->f4[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->f4[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->f4[i])
			{
				v = vertexAttrib->f4[i];
				convert = (convert_func) __convert_f4;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->d1[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->d1[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->d1[i])
			{
				v = vertexAttrib->d1[i];
				convert = (convert_func) __convert_d1;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->d2[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->d2[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->d2[i])
			{
				v = vertexAttrib->d2[i];
				convert = (convert_func) __convert_d2;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->d3[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->d3[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->d3[i])
			{
				v = vertexAttrib->d3[i];
				convert = (convert_func) __convert_d3;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->d4[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->d4[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->d4[i])
			{
				v = vertexAttrib->d4[i];
				convert = (convert_func) __convert_d4;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->b1[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->b1[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->b1[i])
			{
				v = vertexAttrib->b1[i];
				convert = (convert_func) __convert_b1;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->b2[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->b2[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->b2[i])
			{
				v = vertexAttrib->b2[i];
				convert = (convert_func) __convert_b2;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->b3[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->b3[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->b3[i])
			{
				v = vertexAttrib->b3[i];
				convert = (convert_func) __convert_b3;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->b4[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->b4[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->b4[i])
			{
				v = vertexAttrib->b4[i];
				convert = (convert_func) __convert_b4;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->i1[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->i1[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->i1[i])
			{
				v = vertexAttrib->i1[i];
				convert = (convert_func) __convert_i1;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->i2[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->i2[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->i2[i])
			{
				v = vertexAttrib->i2[i];
				convert = (convert_func) __convert_i2;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->i3[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->i3[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->i3[i])
			{
				v = vertexAttrib->i3[i];
				convert = (convert_func) __convert_i3;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->i4[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->i4[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->i4[i])
			{
				v = vertexAttrib->i4[i];
				convert = (convert_func) __convert_i4;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->ub1[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->ub1[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->ub1[i])
			{
				v = vertexAttrib->ub1[i];
				convert = (convert_func) __convert_ub1;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->ub2[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->ub2[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->ub2[i])
			{
				v = vertexAttrib->ub2[i];
				convert = (convert_func) __convert_ub2;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->ub3[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->ub3[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->ub3[i])
			{
				v = vertexAttrib->ub3[i];
				convert = (convert_func) __convert_ub3;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->ub4[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->ub4[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->ub4[i])
			{
				v = vertexAttrib->ub4[i];
				convert = (convert_func) __convert_ub4;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->ui1[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->ui1[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->ui1[i])
			{
				v = vertexAttrib->ui1[i];
				convert = (convert_func) __convert_ui1;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->ui2[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->ui2[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->ui2[i])
			{
				v = vertexAttrib->ui2[i];
				convert = (convert_func) __convert_ui2;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->ui3[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->ui3[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->ui3[i])
			{
				v = vertexAttrib->ui3[i];
				convert = (convert_func) __convert_ui3;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->ui4[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->ui4[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->ui4[i])
			{
				v = vertexAttrib->ui4[i];
				convert = (convert_func) __convert_ui4;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->us1[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->us1[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->us1[i])
			{
				v = vertexAttrib->us1[i];
				convert = (convert_func) __convert_us1;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->us2[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->us2[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->us2[i])
			{
				v = vertexAttrib->us2[i];
				convert = (convert_func) __convert_us2;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->us3[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->us3[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->us3[i])
			{
				v = vertexAttrib->us3[i];
				convert = (convert_func) __convert_us3;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->us4[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->us4[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->us4[i])
			{
				v = vertexAttrib->us4[i];
				convert = (convert_func) __convert_us4;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Nub1[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Nub1[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Nub1[i])
			{
				v = vertexAttrib->Nub1[i];
				convert = (convert_func) __convert_rescale_Nub1;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Nub2[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Nub2[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Nub2[i])
			{
				v = vertexAttrib->Nub2[i];
				convert = (convert_func) __convert_rescale_Nub2;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Nub3[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Nub3[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Nub3[i])
			{
				v = vertexAttrib->Nub3[i];
				convert = (convert_func) __convert_rescale_Nub3;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Nub4[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Nub4[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Nub4[i])
			{
				v = vertexAttrib->Nub4[i];
				convert = (convert_func) __convert_rescale_Nub4;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Nus1[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Nus1[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Nus1[i])
			{
				v = vertexAttrib->Nus1[i];
				convert = (convert_func) __convert_rescale_Nus1;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Nus2[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Nus2[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Nus2[i])
			{
				v = vertexAttrib->Nus2[i];
				convert = (convert_func) __convert_rescale_Nus2;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Nus3[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Nus3[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Nus3[i])
			{
				v = vertexAttrib->Nus3[i];
				convert = (convert_func) __convert_rescale_Nus3;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Nus4[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Nus4[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Nus4[i])
			{
				v = vertexAttrib->Nus4[i];
				convert = (convert_func) __convert_rescale_Nus4;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Nui1[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Nui1[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Nui1[i])
			{
				v = vertexAttrib->Nui1[i];
				convert = (convert_func) __convert_rescale_Nui1;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Nui2[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Nui2[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Nui2[i])
			{
				v = vertexAttrib->Nui2[i];
				convert = (convert_func) __convert_rescale_Nui2;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Nui3[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Nui3[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Nui3[i])
			{
				v = vertexAttrib->Nui3[i];
				convert = (convert_func) __convert_rescale_Nui3;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Nui4[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Nui4[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Nui4[i])
			{
				v = vertexAttrib->Nui4[i];
				convert = (convert_func) __convert_rescale_Nui4;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Nb1[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Nb1[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Nb1[i])
			{
				v = vertexAttrib->Nb1[i];
				convert = (convert_func) __convert_rescale_Nb1;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Nb2[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Nb2[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Nb2[i])
			{
				v = vertexAttrib->Nb2[i];
				convert = (convert_func) __convert_rescale_Nb2;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Nb3[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Nb3[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Nb3[i])
			{
				v = vertexAttrib->Nb3[i];
				convert = (convert_func) __convert_rescale_Nb3;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Nb4[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Nb4[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Nb4[i])
			{
				v = vertexAttrib->Nb4[i];
				convert = (convert_func) __convert_rescale_Nb4;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Ns1[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Ns1[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Ns1[i])
			{
				v = vertexAttrib->Ns1[i];
				convert = (convert_func) __convert_rescale_Ns1;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Ns2[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Ns2[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Ns2[i])
			{
				v = vertexAttrib->Ns2[i];
				convert = (convert_func) __convert_rescale_Ns2;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Ns3[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Ns3[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Ns3[i])
			{
				v = vertexAttrib->Ns3[i];
				convert = (convert_func) __convert_rescale_Ns3;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Ns4[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Ns4[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Ns4[i])
			{
				v = vertexAttrib->Ns4[i];
				convert = (convert_func) __convert_rescale_Ns4;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Ni1[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Ni1[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Ni1[i])
			{
				v = vertexAttrib->Ni1[i];
				convert = (convert_func) __convert_rescale_Ni1;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Ni2[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Ni2[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Ni2[i])
			{
				v = vertexAttrib->Ni2[i];
				convert = (convert_func) __convert_rescale_Ni2;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Ni3[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Ni3[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Ni3[i])
			{
				v = vertexAttrib->Ni3[i];
				convert = (convert_func) __convert_rescale_Ni3;
			}
#ifdef DEBUG_misha
			if (vertexAttrib->Ni4[i])
			{
				uint32_t *pTst = (uint32_t*)(vertexAttrib->Ni4[i]);
				--pTst;
				Assert((*pTst) == i);
			}
#endif
			if (v < vertexAttrib->Ni4[i])
			{
				v = vertexAttrib->Ni4[i];
				convert = (convert_func) __convert_rescale_Ni4;
			}

			if (v != NULL) {
				COPY_4V(c->vertexAttrib[i], vertexAttrib_default);
				convert(&(c->vertexAttrib[i][0]), v);
				DIRTY(cb->vertexAttrib[i], nbitID);
				DIRTY(cb->dirty, nbitID);
			}
			vertexAttrib->ptr[i] = v;
		}
		current->changedVertexAttrib = 0;
	}
	crStateResetCurrentPointers(current);
}
