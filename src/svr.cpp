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
#include<unordered_map>
#include <iostream>
#include <fstream>
#define SUCCESS 0
#define FAILURE 1
#define MAX_SIZE 1024
#define CLI_ID "101"
#define TOKEN "#"
#define BCAST_PORT 6000
#define LISTENER_PORT 54545

char Client_id[15]={0};
char b_cast_time[10]={0};

std::unordered_map<std::string,std::string> cluster_info;

void config_parser()
{
	FILE *config_file;
	char line[255];
	config_file = fopen("../config/config","r");
	while(fgets(line,sizeof(line),config_file))
	{
		if(line[0]=='\n')
			continue;	
		else
		{
			


		}

	}

	//std::fstream config_file;
	//char line[255];
	//config_file.open("../config/config",std::ios::in|std::ios::out);
/*
	while(config_file.getline(line,255))
	{

		if('\n'==line[0])
			continue;
		else
		{
			std::cout<<line<<std::endl;
			char* ip =strtok(line,"=");

			//cluster_info[ip]=port;	
			

		}



			
		}

*/

}




void fs_bcast()
{
	//Current Client Socket
	int bcast_sockfd;
	
	bcast_sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in new_addr;
	memset(&new_addr, 0, sizeof(new_addr));
	new_addr.sin_family = AF_INET;
	new_addr.sin_port = BCAST_PORT;
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


void bcast_listener()
{
	int sockfd;
	std::cout<<"Hello"<<std::endl;
	struct sockaddr_in new_addr;
	struct sockaddr_in cli_addr;
	unsigned slen = sizeof(cli_addr);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	memset(&new_addr, 0, sizeof(new_addr));
	new_addr.sin_family = AF_INET;
	new_addr.sin_port = LISTENER_PORT;
	new_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int bind_status = bind(sockfd, (struct sockaddr*)&new_addr, sizeof(new_addr));

	while(1)
	{
		char bcast_buffer[1024];
		memset(bcast_buffer, 0, sizeof(bcast_buffer));
		recvfrom(sockfd, bcast_buffer, sizeof(bcast_buffer)-1, 0, (sockaddr *)&cli_addr, &slen);
		std::cout << "Listening.." <<std::endl;
		std::cout << "GOT FS" << bcast_buffer << std::endl;
	}
}



int main(int argc, char **argv)
{
	config_parser();	
	std::thread broadcaster(fs_bcast);
	std::thread listener(bcast_listener);
	broadcaster.detach();
	listener.detach();
	while(1){}
	return SUCCESS;
}

























































