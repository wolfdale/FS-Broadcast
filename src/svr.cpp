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
#define BCAST_PORT 5000
#define REQ_LISTNER_PORT 6000
#define MAX_SIZE 1024
#define CLI_ID "101"
#define TOKEN "#"
#define PORT 54545
std::mutex listner_mutex;

void file_bcast()
{
	//Current Client Socket
	int bcast_sockfd;
	
	bcast_sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in new_addr;
	memset(&new_addr, 0, sizeof(new_addr));
	new_addr.sin_family = AF_INET;
	new_addr.sin_port = PORT;
	new_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	while(1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		DIR *dir;
		struct dirent *ent;
		char fs_data[MAX_SIZE];
		memset(fs_data, 0, MAX_SIZE);
		strcpy(fs_data, CLI_ID);

		if ((dir = opendir ("./")) != NULL) 
		{
  			while((ent = readdir (dir)) != NULL)
 			{
				if (!strcmp(ent->d_name, ".") || !strcmp(ent->d_name, ".."))
          			{continue;}
				else
				{
					strcat(fs_data, TOKEN);
  					strcat(fs_data, ent->d_name);
          			}
			}
		}
  		closedir (dir);
		std::cout << fs_data << std::endl;		
		sendto(bcast_sockfd, fs_data, strlen(fs_data), 0, (struct sockaddr *)&new_addr, sizeof(struct sockaddr_in)); 



	}
}



int main(int argc, char **argv)
{
	
	std::thread broadcaster(file_bcast);
//	std::thread listener(bcast_listener);
	broadcaster.detach();

//	listener.detach();
	while(1){}

	return SUCCESS;
}

























































