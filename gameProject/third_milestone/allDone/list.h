#define max_buf 50
#ifndef CIR_BUF_H_
#define CIR_BUF_H_
 typedef struct music_box{
    double x;
    double z;
}music ;
typedef struct
{
	music buffer[max_buf];
	int head;
	int tail;
	int count;
} circ_bbuf_t;
void init_buf(circ_bbuf_t * buf);
void cir_buf_push(circ_bbuf_t * buf,music data);
void cir_buf_pop(circ_bbuf_t * buf,music * data);


#endif /* CIR_BUF_H_ */
