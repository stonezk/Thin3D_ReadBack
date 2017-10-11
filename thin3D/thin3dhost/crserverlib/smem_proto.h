/*******************************************************************
 * smem   guset<--->host   proto (used for both guest and host)
 * 
 * add by zhangrui 2017-9-19
 *
*******************************************************************/

#ifndef __THINPUTER_OPENGL_SMEM_PROTO_H
#define	__THINPUTER_OPENGL_SMEM_PROTO_H

#ifdef __cplusplus
extern "C" {
#endif


struct smem_notify
{
	/* Host Set, Guest Clear */
	int		h2g;
	char	_d_h2g[124];

	/* Guest Set, Host Clear */
	int		g2h;
	char	_d_g2h[124];
};



struct smem_ring
{
	int		head;
	char	_d_head[124];
	
	int		tail;
	char	_d_tail[124];

	int		size;
	char	_d_size[124];
};

struct smem_display
{
	//int			buff_size;
	
	int			width;
	int			height;
};

static __inline int ring_used_size(struct smem_ring *ring)
{
	if (ring->head >= ring->tail) {
		return ring->head - ring->tail;
	} else {
		return ring->size - ring->tail + ring->head;
	}
}

static __inline int ring_remain_size(struct smem_ring *ring)
{
	return ring->size - 1 - ring_used_size(ring);
}

static __inline void ring_do_use(struct smem_ring *ring, int size)
{
	ring->head += size;

	if (ring->head >= ring->size)
		ring->head -= ring->size;
}

static __inline void ring_do_recycle(struct smem_ring *ring, int size)
{
	ring->tail += size;
	
	if (ring->tail >= ring->size)
		ring->tail -= ring->size;
}

static __inline void *smem_ring_get_data(struct smem_ring *ring)
{
	return (void *)(ring+1);
}

static __inline void *smem_display_get_data(struct smem_display *disp)
{
	return (void *)(disp+1);
}

#ifdef __cplusplus
}
#endif

#endif	/* __THINPUTER_OPENGL_SMEM_PROTO_H */

