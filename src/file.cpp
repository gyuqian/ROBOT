#include "file.h"
#include "robot.h"

#include <iostream>
#include <cstring>

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

using namespace std;

const int fileLineCount=77;
void readStrFromFile(char** strRead)
{
	int fd = 0;
    char buff[1024 * 10];
    char cmd[fileLineCount][119];
    int i = 0;
    fd = open("./file/robot.ini", O_RDONLY);

    char *locate;
    read(fd, buff, sizeof(buff));
    locate = strstr(buff, "G0000");
    memset(cmd, 0, sizeof(cmd));

    for(i = 0; i < fileLineCount; i++) {
        memcpy(&strRead[i], locate, 118);
        locate += 120;
    }
}
