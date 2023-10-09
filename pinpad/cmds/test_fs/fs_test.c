#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
	FILE *fp;
	//uint8_t ts[7];
	char path[50];
    //char dt20[20];
	char buf_item[4 + 1];
	int res = 0;

	printf("TEST file system v5\n");

	// init
	sprintf(path, "/conf/fs.tst");
	printf("Filename is %s\n", path);

	// run
	if ((fp = fopen(path, "a+b"))) {
		// log
		printf("Writing 16 times '0000' byte into %s file\n", path);

		sprintf(buf_item, "0000");
		for (int i = 0; i < 16; i++) {
			if (fwrite(buf_item, sizeof(buf_item), 1, fp) != 1) {
				printf("ERROR fwrite\n");
                res = -2;
				break;
			}

			printf("Item added (total items %d)\n", i + 1);
		}

		// OK!
		fclose(fp);

		printf("TEST Successfully finished!\n");
	}
	else {
		printf("can't create file\n");
		printf("check mod file for max num entities in dir\n");
        res = -1;
	}

    return res;
}
