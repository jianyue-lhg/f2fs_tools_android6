#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#define FS_COMPR_FL			0x00000004
#define FS_UNRM_FL			0x00000002
#define DEDUPE_MEM_FLAGS (FS_COMPR_FL|FS_UNRM_FL)
#define FS_IOC_GETFLAGS			_IOR('f', 1, long)
#define FS_IOC_SETFLAGS			_IOW('f', 2, long)
#define OPEN_FLAGS (O_RDONLY|O_NONBLOCK)
int main(int argc, char* argv[])
{
	int fd;
	int f,r;
	int flags = 0;
	if(0==argc)
	{
		printf("no input file.\n");
		exit(0);
	}
	if(2==argc)
	{
		flags |= FS_COMPR_FL;
		fd = open(argv[1], OPEN_FLAGS);
	}
	if(3==argc&&!strcmp(argv[1],"-d"))
	{
		flags |= DEDUPE_MEM_FLAGS;
		//printf("%x...%d\n",flags,argc);
		fd = open(argv[2], OPEN_FLAGS);
	}
	printf("doing:%s\n",argv[1]);
	r = ioctl(fd, FS_IOC_GETFLAGS, &f);
	printf("old:%x\n",f);
	f|=flags;
	r = ioctl(fd, FS_IOC_SETFLAGS, &f);
	printf("new:%x\n",f);
	close(fd);
	return 0;
}
