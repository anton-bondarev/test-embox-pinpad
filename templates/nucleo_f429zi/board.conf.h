#include <nucleo_f429zi.conf.h>

CONFIG {
	/* uarts */
	uarts[2].status = DISABLED;
	uarts[3].status = ENABLED;
	uarts[6].status = DISABLED;

	/* spis */
	spis[1].status  = DISABLED;
	spis[2].status  = DISABLED;
}
