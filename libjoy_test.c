#include <stdio.h>
#include <ext.h>
#include <mint/osbind.h>
#include "libjoy.h"

static void joy_check1(const unsigned short exp)
{
	unsigned short old = 0xffff;
	for (;;) {
		unsigned short j = joy();
		if (old != j) {
			printf("\rGot %04x, expected %04x", j, exp);
			if (exp == j)
				break;
			old = j;
		}
	}
	printf("\r\nSuccess!\r\n");
}

int main(void)
{
	long oldssp = Super(0L);

	printf(" == checking joystick 3 ==\r\n");
	printf("Move joystick 3 UP\r\n");
	joy_check1(JOY3_UP);
	printf("Move joystick 3 DOWN\r\n");
	joy_check1(JOY3_DOWN);
	printf("Move joystick 3 LEFT\r\n");
	joy_check1(JOY3_LEFT);
	printf("Move joystick 3 RIGHT\r\n");
	joy_check1(JOY3_RIGHT);
	printf("Fire joystick 3\r\n");
	joy_check1(JOY3_FIRE);

	printf("\r\n == checking joystick 4 ==\r\n");
	printf("Move joystick 4 UP\r\n");
	joy_check1(JOY4_UP);
	printf("Move joystick 4 DOWN\r\n");
	joy_check1(JOY4_DOWN);
	printf("Move joystick 4 LEFT\r\n");
	joy_check1(JOY4_LEFT);
	printf("Move joystick 4 RIGHT\r\n");
	joy_check1(JOY4_RIGHT);
	printf("Fire joystick 4\r\n");
	joy_check1(JOY4_FIRE);

	SuperToUser(oldssp);

	printf("Done. Hit any key to exit.\r\n");
	getch();
	return 0;
}
