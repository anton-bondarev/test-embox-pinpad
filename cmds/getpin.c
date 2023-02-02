#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <time.h>
#include <drivers/input/input_dev.h>
#include <drivers/input/keymap.h>

#define PIN_TIMEOUT 15			// time to enter 4-digit pin before canceling, s

static void print_usage(const char *cmd) {
	printf("Usage: %s [-h] <keyboard>\n", cmd);
}

int main(int argc, char **argv)	{
	// Prepare keyboard
	int opt, fd;

	if (argc < 2) {
		print_usage(argv[0]);
		return 0;
	}
	while (-1 != (opt = getopt(argc, argv, "h"))) {
		switch (opt) {
		case 'h':
			print_usage(argv[0]);
			/* FALLTHROUGH */
		default:
			return 0;
		}
	}
	fd = open(argv[argc - 1], O_RDONLY);
	if (fd==-1) {
		printf("Failed to open %s", argv[argc - 1]);
		return -1;
	}

	// Show invitation
	puts("Enter 4-digit pin-code\nor press C to cancel");
	
	// Get pin-code
	struct input_event ev;
	unsigned char code[4];
	unsigned char key, pin[4];
	
//	clock_t t0=clock();
	
	for (int i=0; i<4;) {
		if ((read(fd, &ev, sizeof ev) > 0) && (ev.type & KBD_KEY_PRESSED)) {
			if (keymap_to_ascii(&ev, code)==1) {
				key=code[0];
				if ('0' <= key && key <= '9') {
					pin[i++]=key; 
					putchar('*');
					//printf("%ld %ld", clock()-t0, (long)CLOCKS_PER_SEC*PIN_TIMEOUT);
					fflush(stdout);
				}
				if (key == 'C') break;
			}
		}
/*		if (clock()-t0 > CLOCKS_PER_SEC*PIN_TIMEOUT) {
		key='C';
		printf("\nYou lost...");
		break;
		}
*/	}
	if (key == 'C') {
		puts("\nOperation canceled");
	} else {
		printf("\nYour pin code is ");
		for (int i=0; i<4; i++)	putchar(pin[i]); 
		putchar('\n');
	}

	close(fd);
	
	return 0;
}

