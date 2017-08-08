#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define ID 0x18

void main(){
	int i = 0;
	char buf[5];
	int fd = open("/home/pi/upstest.txt",O_CREAT|O_WRONLY|O_TRUNC,0644);
	for(i = 0;i < 60; i++){
		sprintf(buf,"%4d",i);
		write(fd,buf,sizeof(buf));
		sleep(1);
		
	}
	system("sudo rm /home/pi/upstest.txt");
	system("ups -s");
}
