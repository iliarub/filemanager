#include<unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "func.h"

struct plug* odir(const char* dname, struct plug *plg )
{
	DIR *dp = opendir(dname);
	struct dirent *dir;
	struct stat st;
	chdir(dname);
	struct plug* tmp1=NULL;
	while((dir=readdir(dp))!=0)
	{
		printf("%s\n", dir->d_name);
		stat(dir->d_name, &st);
	}
chdir("..");
closedir(dp);
return tmp1;
}
