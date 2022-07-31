#ifndef LIBJOY_H_
#define LIBJOY_H_

#define JOY3_UP		(1 << 0)
#define JOY3_DOWN	(1 << 1)
#define JOY3_LEFT	(1 << 2)
#define JOY3_RIGHT	(1 << 3)

#define JOY4_UP		(1 << 4)
#define JOY4_DOWN	(1 << 5)
#define JOY4_LEFT	(1 << 6)
#define JOY4_RIGHT	(1 << 7)

#define JOY3_FIRE	(1 << 8)
#define JOY4_FIRE	(1 << 9)

unsigned short joy(void);

#endif	/* LIBJOY_H_ */
