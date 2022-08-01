#include <mint/osbind.h>
#include "libjoy.h"

#define YM2149_RDRS					(*(volatile unsigned char *)0xff8800)
#define YM2149_WD					(*(volatile unsigned char *)0xff8802)
#define YM2149_R_MIXER_CTL			7
#define YM2149_R_MIXER_CTL_PORT_A	0x40
#define YM2149_R_MIXER_CTL_PORT_B	0x80
#define YM2149_R_PORT_A				14
#define YM2149_R_PORT_A_STROBE		0x20
#define YM2149_R_PORT_B				15
#define MFP_R_PARALLEL				(*(volatile unsigned char *)0xfffa01)
#define MFP_R_PARALLEL_BUSY			0x01

unsigned short joy(void)
{
	unsigned short sr;
	unsigned char dir, fire3, fire4;

	/* disable interrupts */
	asm volatile ("move.w sr, %0\n"
		"ori #0x700, sr"
		:"=d"(sr));

	/* set port A & B in input mode */
	YM2149_RDRS = YM2149_R_MIXER_CTL;
	YM2149_WD = YM2149_RDRS & ~(YM2149_R_MIXER_CTL_PORT_A|YM2149_R_MIXER_CTL_PORT_B);

	/* read joystick direction from port B */
	YM2149_RDRS = YM2149_R_PORT_B;
	dir = YM2149_RDRS;

	/* read fire3 from port A */
	YM2149_RDRS = YM2149_R_PORT_A;
	fire3 = YM2149_RDRS & YM2149_R_PORT_A_STROBE;

	/* read fire4 from parallel port */
	fire4 = MFP_R_PARALLEL & MFP_R_PARALLEL_BUSY;

	/* re-enable interrupts */
	asm volatile ("move.w %0, sr"::"d"(sr));

	/* combine dir + fire */
	union {
		struct {
			unsigned char dummy:6;
			unsigned char fire4:1;
			unsigned char fire3:1;
			unsigned char dir:8;
		};
		unsigned short as_short;
	} ret;
	ret.dummy = 0;
	ret.fire3 = !!(fire3);
	ret.fire4 = !!(fire4);
	ret.dir = dir;
	/* reg values are 0 for active and 1 for inactive, we need to invert the bits pattern */
	return ret.as_short ^ 0x03ff;
}
