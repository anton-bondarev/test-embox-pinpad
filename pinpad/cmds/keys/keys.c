#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <lib/crypt/b64.h>

#include <util/macro.h>
#include <framework/mod/options.h>

#define FILE_PATH \
			MACRO_STRING(OPTION_GET(STRING, file_keys))


extern int b64_encode(const char *plain, size_t plain_sz,
		char *buff, size_t buff_sz, size_t *out_coded_sz);
extern int b64_decode(const char *coded, size_t coded_sz,
		char *buff, size_t buff_sz, size_t *out_plain_sz);

int main(int argc, char **argv)	{
	int pswdf;
	char buff[128]={0};
	size_t len;

	if (argc == 3) {
		pswdf = open(FILE_PATH, O_CREAT | O_WRONLY | O_APPEND);
		if (pswdf < 0) {
			return -1;
		}
		strcpy(buff, argv[1]);
		buff[strlen(buff)] = ':';
		b64_encode(argv[2], strlen(argv[2]),
				buff + strlen(buff), sizeof(buff) - strlen(buff),
				&len);
		//strcpy(buff + strlen(buff), argv[2]);
		write(pswdf, buff, strlen(buff));

	} else if (argc == 2) {
		char *line;
		char tmp[128]={0};

		pswdf = open(FILE_PATH, O_RDONLY);
		if (pswdf < 0) {
			return -1;
		}
		read(pswdf, buff, sizeof(buff));
		line = buff;
		while(*line != '\0') {
			if (*line == ':') {
				*line = '\0';
				line ++; 
				break;
			}
			line++;
		}

		printf("\nkey name: %s\n", buff);

		b64_decode(line, strlen(line), 
					tmp, sizeof(tmp), &len);
		
		printf("key:%s\n", tmp);


	} else {
		printf ("wrong args\n");
		printf ("use: 'keys <key_name>' for reading\n");
		printf ("or keys <key_name> <key_value> for writing\n");
	}


    return 0;
}
