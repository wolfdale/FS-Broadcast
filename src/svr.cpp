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
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

//#include "fs_header.h"
#define SUCCESS 0
#define FAILURE 1
#define MAX_SIZE 1024
#define CLI_ID "101"
#define TOKEN "#"
//#define BCAST_PORT 6000
//#define LISTENER_PORT 54545

#define BCAST_PORT 54545
#define LISTENER_PORT 6000

struct node_config_object{
	char *node_id;
	char *node_ip;
	char *node_port;
	char *buffer;
	char *timer;
	char *listener_port;
};

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

void nodeBootSequence(struct node_config_object *nodeObj)
{
	FILE *config_file = NULL;
	char line[150];
	int line_size = 150;

	config_file = fopen("../config/config","r");
	
	while (fgets(line, line_size, config_file))  
	{
    		if(line[0]=='#')
		{
                        continue;
		}
                else
                {
                        std::cout<<line<<std::endl;
			char *temp1 = NULL;
			char *temp2 = NULL;
			temp1 = strtok(line,"=");
                        std::cout<<temp1<<std::endl;
			if(strcmp(temp1,"NODE_ID") == 0){
				temp2 = strtok(NULL,"=");
				nodeObj->node_id = strdup(temp2);
			}
			if(strcmp(temp1,"NODE_IP_ADDRESS") == 0){
				temp2 = strtok(NULL,"=");
				nodeObj->node_ip = strdup(temp2);
			}
			if(strcmp(temp1,"NODE_PORT_ADDRESS") == 0){
				temp2 = strtok(NULL,"=");
				nodeObj->node_port = strdup(temp2);
			}
			if(strcmp(temp1,"MAX_BUFF") == 0){
				temp2 = strtok(NULL,"=");
				nodeObj->buffer = strdup(temp2);
			}
			if(strcmp(temp1,"FS_DURATION") == 0){
				temp2 = strtok(NULL,"=");
				nodeObj->timer = strdup(temp2);
			}

			if(strcmp(temp1,"LISTNER_PORT") == 0){
				temp2 = strtok(NULL,"=");
				nodeObj->listener_port = strdup(temp2);
			}
                }

	}
}

void fs_bcast(struct node_config_object *nodeObj)
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
		
		std::cout << "....................................." << std::endl;
		std::cout << "... Now Broadcasting Node Content ..." << std::endl;
		std::cout << "....................................." << std::endl;
		/* Broadcast Every 10 Seconds (Configurable) */
		std::this_thread::sleep_for(std::chrono::milliseconds((nodeObj->timer));
		
		/* Get files in Directory and create a FS Packet*/
		DIR *dir;
		struct dirent *ent;
		char fs_data[MAX_SIZE];
		memset(fs_data, 0, MAX_SIZE);
		strcpy(fs_data, CLI_ID);
		if ((dir = opendir ("../files")) != NULL) 
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

		std::cout << "--> "<< fs_data << std::endl;		

		//Need to implment for loop over all Socket fd to send file info
		sendto(bcast_sockfd, fs_data, strlen(fs_data), 0, (struct sockaddr *)&new_addr, sizeof(struct sockaddr_in)); 
	}
}


void bcast_listener()
{
	/* Client Address */
	struct sockaddr_in recv_client_addr;
	unsigned slen = sizeof(recv_client_addr);
	
	/* listener Address */
	int sockfd;
	struct sockaddr_in listener_addr;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&listener_addr, 0, sizeof(listener_addr));
	listener_addr.sin_family = AF_INET;
	listener_addr.sin_port = LISTENER_PORT;
	listener_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int bind_status = bind(sockfd, (struct sockaddr*)&listener_addr, sizeof(listener_addr));

	while(1)
	{
		std::cout << "Listening ..." << std::endl;
		char bcast_buffer[MAX_SIZE];
		memset(bcast_buffer, 0, sizeof(bcast_buffer));
		recvfrom(sockfd, bcast_buffer, sizeof(bcast_buffer)-1, 0, (sockaddr *)&recv_client_addr, &slen);
		std::cout << "Listening.." <<std::endl;
		std::cout << "GOT FS" << bcast_buffer << std::endl;

	}
}




int main(int argc, char **argv)
{
	/* Configuration Parsing */
	struct node_config_object *nodeObj;
	nodeObj = (struct node_config_object*)malloc(sizeof(node_config_object));
	nodeBootSequence(nodeObj);	
	std::cout << "========================="<<nodeObj->node_id;	
	std::cout << "========================="<<nodeObj->node_ip;	
	std::cout << "========================="<<nodeObj->node_port;	
	std::cout << "========================="<<nodeObj->buffer;	
	std::cout << "========================="<<nodeObj->timer;	
	std::cout << "========================="<<nodeObj->listener_port;	
	/* Start Broadcaseting Thread */
	std::thread broadcaster(fs_bcast, nodeObj);
	
	/* Start BroadCast Listener */
	std::thread listener(bcast_listener);
	
	/* Make them independent */
	broadcaster.detach();
	listener.detach();
	
	while(1){}
	return SUCCESS;
}

























































