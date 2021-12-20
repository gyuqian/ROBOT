#ifndef __SERVER_H__
#define __SERVER_H__

#include <iostream>

using namespace std;

class classServer
{
public:
	int ser_fd;
	int cli_fd;
	
public:

	classServer();
	int server_socket_init(void);
	int data_handle(void);
	void server_socket_close(void);
	int writeClient(char*);
};

#endif
