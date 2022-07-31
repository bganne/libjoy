#include <stdio.h>
#include <ext.h>
#include <mint/osbind.h>
#include "libjoy.h"

static void joy_check1(const unsigned char joy, const unsigned char exp)
{
	unsigned char old = 0xff;
	for (;;) {
		unsigned char j;
		switch (joy) {
			case 3:
				j = joy_3();
				break;
			case 4:
				j = joy_4();
				break;
		}
		if (old != j) {
			printf("\rGot %02x, expected %02x", j, exp);
			if (exp == j)
				break;
			old = j;
		}
	}
	printf("\r\nSuccess!\r\n");
}

static void joy_check(unsigned char joy)
{
	printf("Move joystick %i UP\r\n", joy);
	joy_check1(joy, JOY_UP);
	printf("Move joystick %i DOWN\r\n", joy);
	joy_check1(joy, JOY_DOWN);
	printf("Move joystick %i LEFT\r\n", joy);
	joy_check1(joy, JOY_LEFT);
	printf("Move joystick %i RIGHT\r\n", joy);
	joy_check1(joy, JOY_RIGHT);
	printf("Fire joystick %i\r\n", joy);
	joy_check1(joy, JOY_FIRE);
}

int main(void)
{
	long oldssp = Super(0L);

	printf(" == checking joystick 3 ==\r\n");
	joy_check(3);

	printf(" == checking joystick 4 ==\r\n");
	joy_check(4);

	SuperToUser(oldssp);

	printf("Done. Hit any key to exit.\r\n");
	getch();
	return 0;
}
