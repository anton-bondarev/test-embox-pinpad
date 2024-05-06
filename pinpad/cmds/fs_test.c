#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <time.h>

long unsigned int _nTest;
int _res;

#define LOG_1 LOG_0
#define LOG_0(l, ...) (printf(__VA_ARGS__), printf("\n"))
#define SET_ERROR(err) printf("Error set to %s\n", #err)
#define _countErrors()
#define getMs() ((int)(clock()%100))
#define SLS_EPP_FINISH 1
#define _test_completed_successfuly "Test completed successfuly"

#define __TEST_FAILED__(ERR) { SET_ERROR(ERR); _countErrors(); return;}

/// <summary>
/// Тестирует возможности ЩС на совместимость
/// </summary>
static void testOS()
{
	// проверка возможности работы с файлами
	char * msg = "hello!\n";
	char filename[50];
	int fd;
	
	LOG_1(LOG_INFO, "*** TEST#%lu OS COMPATIBILLITY ***", ++_nTest);
	
	// подготовка имени файла (должно быть уникальное имя файла)
	sprintf(filename, "/mnt/test-%d", getMs());
	
	// открыть файл
	if ((fd = open(filename, O_RDWR | O_CREAT | O_APPEND)) == -1) __TEST_FAILED__(ILRET_OS_INCOMPATIBLE);
	
	// что-нибудь записать в файл
	if (write(fd, msg, strlen(msg)) != strlen(msg)) __TEST_FAILED__(ILRET_OS_INCOMPATIBLE);
	
	// закрыть файл
	close(fd);
	
	// все ОК
	SET_ERROR(ILRET_OK); _res = SLS_EPP_FINISH;
	LOG_0(LOG_DEBUG, _test_completed_successfuly);
	
	_countErrors();
	LOG_0(LOG_INFO, " ");
}

int main(int argc, char **argv)	{
	testOS();	
	return 0;
}

