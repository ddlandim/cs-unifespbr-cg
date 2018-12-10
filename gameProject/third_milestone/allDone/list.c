
#include "list.h"
void init_buf(circ_bbuf_t * buf)
{
	buf->count=0;
	buf->head=0;
	buf->tail=0;
}
void cir_buf_push(circ_bbuf_t * buf,music data)
{
	if(buf->count < max_buf)
	{
		buf->head=buf->head%max_buf;
		buf->buffer[buf->head].x =data.x;
        buf->buffer[buf->head].z =data.z;
		buf->head++;
		buf->count++;
	}
}
void cir_buf_pop(circ_bbuf_t * buf,music * data)
{
	if(buf->count)
	{
		buf->tail=(buf->tail)%max_buf;
		(*data) .x=(*(buf->buffer + buf->tail)).x;
		(*data) .z=(*(buf->buffer + buf->tail)).z;

		buf->tail++;
		buf->count--;
	}
}
