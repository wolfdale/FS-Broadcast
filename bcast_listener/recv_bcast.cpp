/*
###############################################################################
Dummy BroadCast Listener

Listen to Every Broadcast on Port 5000
For Testing Purposes

###############################################################################
*/

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
#include<mutex>

#define SUCCESS 0
#define FAILURE 1
#define BCAST_PORT 54545

std::mutex listner_mutex;

void bcast_listener()
{
	int bcast_sockfd;

	struct sockaddr_in new_addr;
	struct sockaddr_in cli_addr;
	unsigned slen = sizeof(cli_addr);

	bcast_sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&new_addr, 0, sizeof(new_addr));
	new_addr.sin_family = AF_INET;
	new_addr.sin_port = BCAST_PORT;
	new_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int bind_status = bind(bcast_sockfd, (struct sockaddr*)&new_addr, sizeof(new_addr));

	while(1)
	{
//		std::lock_guard<std::mutex> lock(listner_mutex);
//		listner_mutex.lock();
		char bcast_buffer[1024];
		memset(bcast_buffer, 0, sizeof(bcast_buffer));
		recvfrom(bcast_sockfd, bcast_buffer, sizeof(bcast_buffer)-1, 0, (sockaddr *)&cli_addr, &slen);
		std::cout << bcast_buffer << std::endl;
//		listner_mutex.unlock();
	}
}


int main(int argc, char **argv)
{
	std::cout << "BroadCast Listener" << std::endl;
	std::thread broadcaster(bcast_listener);
	broadcaster.detach();
	while(1){}
	return SUCCESS;
}







