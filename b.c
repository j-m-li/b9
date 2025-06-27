
/* BASE 9 (+/-4) in balanced ternary logic */
 
#include <stdio.h>
#include <stdlib.h>

int argc;
char **argv;
FILE *in;
FILE *out;


int int2tri(int x, char *buf)
{
	if (1) {
		/* to ascii */
		buf[0] = ' ';
		switch (x) {
		case 4:  buf[0] = '4'; break; /* 4 */
		case 3:  buf[0] = '3'; break; /* 3 */
		case 2:  buf[0] = '2'; break; /* 2 */
		case 1:  buf[0] = '1'; break; /* 1 */
		case 0:  buf[0] = '0'; break; /* 0 */
		case -1: buf[0] = 'a'; break; /* a */
		case -2: buf[0] = 'b'; break; /* b */
		case -3: buf[0] = 'c'; break; /* c */
		case -4: buf[0] = 'd'; break; /* d */
		default: printf("errorx/%d/\n", x);
		}
		return 1;
	}
	/* TRITII: 43210abcd space newline */
	/* to UTF-8 */
	buf[0] = 0xE2;
	buf[1] = 0xA0;
	buf[2] = 0x80; /* space */
	switch (x) {
	case 4:  buf[2] = 0x8E; break; /* 4 */
	case 3:  buf[2] = 0x8C; break; /* 3 */
	case 2:  buf[2] = 0x95; break; /* 2 */
	case 1:  buf[2] = 0x9C; break; /* 1 */
	case 0:  buf[2] = 0xBF; break; /* 0 */
	case -1: buf[2] = 0xA3; break; /* a */
	case -2: buf[2] = 0xAA; break; /* b */
	case -3: buf[2] = 0xA1; break; /* c */
	case -4: buf[2] = 0xB1; break; /* d */
	}
	return 3;
}

void int2txt(int x, char *buf, int *len)
{
	static int vv = 387420489; 
	int l = 0;
	int bl = *len;
	int d;
	int k;
	int v;
/*	
	vv = 81;
	v = 81 * 9;
	d = 4;
	k = 4 * 9 + 4;
	while (k > d && v > vv)	{
		d = k;
		k = d * 9 + 4;
		vv = v;
		v = v * 9;
	}

	printf(">%d\n", vv);
*/

	v = vv;
	if (x > v || x < -v) {
		return;
	}
	while (v > 1) {
		k = (v-1) / 2;
		if (x > 0 && x > k) {
			break;
		} else if (x < 0 && -x > k) {
			break;
		}
		v = v / 9;
	}
	while (v > 1 && bl >= 3) {
		k = ((v)-1) / 2;
		/*printf("x%d(k%d)", x,k);*/
		if (x > 0 && x > k) {
			d = (x) / v;
			x = x - d * v;
			if (x > k) {
				x = x - v;
				d++;
			}
			l += int2tri(d, buf + l);
		} else if (x < 0 && -x > k) {
			d = (-x) / v;
			x = x + d * v;
			if (-x > k) {
				x = x + v;
				d++;
			}
			l += int2tri(-d, buf + l);
		} else {
			l += int2tri(0, buf + l);
		}
		/*printf("x%d v%d d%d\n", x, v, d);*/
		bl = bl - 3;
		v = v / 9;
	}
	/*printf(">v%d x%d\n", v, x); */
	l += int2tri(x, buf + l);
	*len = l;
}

void printn(int x)
{
	char buf[80];
	int l = 80;
	int2txt(x, buf, &l);
	fwrite(buf, 1, l, stdout);
}

void quit(int ec)
{
	fclose(in);
	fclose(out);
	exit(ec);
}

void loop()
{
	static char buf[512];
	static int start = 0;
	static int end = 0;
	static int opcode;
	static int value;
	static int state = 0;
	int l;

	if (start == end) {
		l = fread(buf, 1, 512, in);	
		if (l < 1) {
			state = 255;
		} else {
			end = end + l;
			fwrite(buf, 1, l, out);	
		}
		return;
	}	
	printn(state);
	fwrite("\n", 1, 1, stdout);	
	switch (state) {
	case 0: 
		state++;
		break;
	case 1: 
		state++;
		break;
	case 2: 
		state++;
		break;
	case 3: 
		state++;
		break;
	case 4: 
		state++;
		break;
	case 5: 
		state++;
		break;
	default:	
		state++;
		if (state > 1000) {
			quit(0);
		}
	}
}

void setup()
{
	if (argc != 3) {
		exit(-1);
	}
	in = fopen(argv[1], "r");
	if (!in) {
		exit(-2);
	}
	out = fopen(argv[2], "w");
	if (!out) {
		exit(-3);
	}
}

int main(int argc_, char *argv_[])
{
	argc = argc_;
	argv = argv_;
	setup();
	while (1) {
		loop();
	}
	return -1;
}

