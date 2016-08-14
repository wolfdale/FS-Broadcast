#include<iostream>
#include<vector>
#include<cstdio>
#include<string>
#include<thread>
#include<dirent.h>
#include<chrono>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<unistd.h>
#include<cstdlib>
#include<sys/wait.h>
#include<string.h>
#define SUCCESS 0
#define FAILURE 1
#define BCAST_PORT 5000
#define REQ_LISTNER_PORT 6000

void bcast_listner()
{
	int bcast_sockfd;
	int bcast_enable = 1;

	struct sockaddr_in new_addr;

	bcast_sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&new_addr, 0, sizeof(new_addr));
	setsockopt(bcast_sockfd, SOL_SOCKET, SO_BROADCAST, (void *)&bcast_enable, sizeof(bcast_enable));
	new_addr.sin_family = AF_INET;
	new_addr.sin_port = BCAST_PORT;
	new_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int bind_status = bind(bcast_sockfd, (struct sockaddr*)&new_addr, sizeof(new_addr));

	while(1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		char buf[100];
		unsigned slen = sizeof(buf);
		recvfrom(bcast_sockfd, buf, sizeof(buf)-1, 0, (sockaddr *)&new_addr, &slen);
		std::cout << buf << std::endl;

	}
}


int main(int argc, char **argv)
{
	
	std::thread broadcaster(bcast_listner);
	broadcaster.detach();
	while(1){}
	return SUCCESS;
}





































































