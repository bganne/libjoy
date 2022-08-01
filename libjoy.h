#ifndef LIBJOY_H_
#define LIBJOY_H_

#define JOY3_UP		0x0001
#define JOY3_DOWN	0x0002
#define JOY3_LEFT	0x0004
#define JOY3_RIGHT	0x0008
#define JOY3_FIRE	0x0100

#define JOY4_UP		0x0010
#define JOY4_DOWN	0x0020
#define JOY4_LEFT	0x0040
#define JOY4_RIGHT	0x0080
#define JOY4_FIRE	0x0200

unsigned short joy(void);

#endif	/* LIBJOY_H_ */
