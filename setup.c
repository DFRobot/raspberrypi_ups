#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
int main(){
	char buf[128] = {0};

	FILE *fp1 = fopen("/etc/rc.local","r");
	FILE *fp2 = fopen("/dfups/tmp/startupconfig.txt","r+");
	if(fp1 == NULL){
		printf("open rc.local error\n");
		return -1;
	}
	if(fp2 == NULL){
		printf("open startupconfig.txt error\n");
		return -1;
	}
	while(fgets(buf,128,fp1)!=NULL){
		
		if(strncmp(buf,"/dfups/ups_wdog",16) == 0){
			fclose(fp1);
			fclose(fp2);
			return 0;
		}
	}
	fseek(fp1,0,SEEK_SET);
	while(fgets(buf,128,fp1)!=NULL){
		fputs(buf,fp2);
		if(strncmp(buf,"#!/bin/",7) == 0){
			fputs("/dfups/ups_wdog start & \n",fp2);
			fputs("/dfups/startup.sh start & \n",fp2);
		}
		memset(buf,0,sizeof(buf));
	}

	fclose(fp1);
	fclose(fp2);
	return 0;
}
