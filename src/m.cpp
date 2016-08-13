#include<iostream>
#include<dirent.h>


int main()
{

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir ("../files/")) != NULL) {
  	/* print all the files and directories within directory */
  	while ((ent = readdir (dir)) != NULL) {
    		printf ("%s\n", ent->d_name);
  	}
	}
  	closedir (dir);





	return 0;
}






