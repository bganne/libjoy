#include <mint/osbind.h>
#include "libjoy.h"

#define YM2149_RDRS					(*(volatile unsigned char *)0xff8800)
#define YM2149_WD					(*(volatile unsigned char *)0xff8802)
#define YM2149_R_MIXER_CTL			7
#define YM2149_R_PORT_A				14
#define YM2149_R_PORT_B				15
#define YM2149_R_PORT_A_STROBE		0x20
#define YM2149_R_MIXER_CTL_PORT_A	0x40
#define YM2149_R_MIXER_CTL_PORT_B	0x80
#define MFP_R_ACTIVE_EDGE			(*(volatile unsigned char *)0xfffa01)

unsigned char joy_3(void)
{
	unsigned short sr;
	unsigned char dir, fire;
	asm volatile ("move.w sr, %0\n"
			"ori #0x700, sr"
			:"=d"(sr));
	YM2149_RDRS = YM2149_R_MIXER_CTL;
	YM2149_WD = YM2149_RDRS & ~YM2149_R_MIXER_CTL_PORT_B;
	YM2149_RDRS = YM2149_R_PORT_B;
	dir = YM2149_RDRS;
	YM2149_RDRS = YM2149_R_MIXER_CTL;
	YM2149_WD = YM2149_RDRS & ~YM2149_R_MIXER_CTL_PORT_A;
	YM2149_RDRS = YM2149_R_PORT_A;
	fire = YM2149_RDRS;
	asm volatile ("move.w %0, sr"::"d"(sr));
	return (~dir) & 0x0f | (((~fire) & YM2149_R_PORT_A_STROBE) >> 1);
}

unsigned char joy_4(void)
{
	unsigned short sr;
	unsigned char dir, fire;
	asm volatile ("move.w sr, %0\n"
			"ori #0x700, sr"
			:"=d"(sr));
	YM2149_RDRS = YM2149_R_MIXER_CTL;
	YM2149_WD = YM2149_RDRS & ~YM2149_R_MIXER_CTL_PORT_B;
	YM2149_RDRS = YM2149_R_PORT_B;
	dir = YM2149_RDRS;
	fire = MFP_R_ACTIVE_EDGE;
	asm volatile ("move.w %0, sr"::"d"(sr));
	return (((~dir) & 0xf0) >> 4) | (((~fire) & 0x1) << 4);
}
