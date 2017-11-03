#include <dfups.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#define ID      0x18
#define wDog    0x01<<4
#define led     0x01<<3
#define rgb     0x01<<2
#define shdown  0x01<<1
#define powam   0x01<<0

void getHelp(int fd){

	printf("===========================================^-^=======================================\n");
	printf("ups	[arg]\n");
	printf("	-i\n");
	printf("		get the information of UPS,for example:ID ,VERSION ,ENERGY ,RGB...\n");
	printf("\n");
	printf("	-rgb [numR]  [numG]  [numB]\n");
	printf("		need 5 arguments to set RGB,the <numR> <numG> <numB> range 0~255\n");
	printf("\n");
	printf("	-s   <min>\n");
	printf("		shutdown after <min>,and UPS turn off after,if no <min> will shutdown now\n");
	printf("\n");
	printf("	-t   [min]\n");
	printf("		after shutdown, the pi will be switched on after <min> minutes\n");
	printf("\n");
	printf("	-a   [min]  [exe]\n");
	printf("		pi will turn on in <min> minutes after shutdown,run <exe>\n");
	printf("===========================================^-^=======================================\n");

}

void shutDown(int fd,int min){
    int flag = getFunction(fd);
    flag |= shdown;
	char buf[32]={0};
	if(min == 0){
		setFunction(fd,flag);
		system("sudo shutdown now");
	}
	else if(min > 0){
		min = min*60;
		sleep(min);
		setFunction(fd,flag);
		system("sudo shutdown now");
	}

}

void timer(int fd,int min){
	setTimer(fd,min);
}

void autorun(int fd,int min,char *file){
	char buf[128] = {0};
	timer(fd,min);

	FILE *fp1 = fopen("/dfups/tmp/startupconfig.txt","r");
    FILE *fp2 = fopen("./rc.local","w");
    if(fp1 == NULL){
		return;
	}
	if(fp2 == NULL){
		return;
	}
	

	while(fgets(buf,128,fp1)!=NULL){
		fputs(buf,fp2);
		if(strncmp(buf,"/dfups/ups_wdog",14) == 0){
			memset(buf,0,sizeof(buf));
			sprintf(buf,"%s start &\n",file);
			fputs(buf,fp2);
		}
		memset(buf,0,sizeof(buf));
	}
	fclose(fp1);
	fclose(fp2);
	system("sudo chmod 777 rc.local");
	system("sudo chgrp root rc.local");
	system("sudo chown root rc.local");
	system("sudo mv rc.local /etc/");

}

void getmsg(int fd){
        int version = getVersion(fd);
        int id = getId(fd);
        printf("id     :%X\n",id);
		printf("version:%x\n",version);

        int energy = getEnergy(fd);
		if(energy < 6){
			printf("energy level:%d\n",energy);
		}
		else if(energy == 6){
			printf("energy :is charging\n");
		}
		else if(energy == 7){
			printf("energy :fully charge\n");
		}
        int adc1 = getAdc1(fd);
        int adc2 = getAdc2(fd);
    	printf("adc1   :%d\n",adc1);
		printf("adc2   :%d\n",adc2);
        
		int vcc = getVcc(fd);
        printf("vcc    :%d\n",vcc);

        int flag = getFunction(fd);
        printf("flag   :%x\n",flag);

        int rgbr = getRgbR(fd);
        int rgbg = getRgbG(fd);
        int rgbb = getRgbB(fd);
        printf("rgb_r  :%d\n",rgbr);
		printf("rgb_g  :%d\n",rgbg);
		printf("rgb_b  :%d\n",rgbb);
}

void setrgb(int fd,int rNum,int gNum,int bNum){
    int flag = getFunction(fd); //enable rgb
    flag |= rgb;
    setFunction(fd,flag);
    setRgbR(fd,rNum);     //the num in range 0~255
    setRgbG(fd,gNum);
    setRgbB(fd,bNum);
}

int main(int argc,char *argv[]){
	char buf[32]={0};
	if(argc < 2){
		printf("please input arguments, you can input:./ups -h\n");
		return -1;
	}
	int fd = Init(ID);
	
	if(strcmp(argv[1],"-s") == 0){
		int min;
		if(argc == 2){
			min = 0;
		}
		else if(argc == 3){
			min = atoi(argv[2]);
		}
		shutDown(fd,min);
	}
	else if(strcmp(argv[1],"-h") == 0){
		getHelp(fd);
	}
	else if(strcmp(argv[1],"-i") == 0){
		getmsg(fd);
	}
	else if(strcmp(argv[1],"-rgb") == 0){
		if(argc != 5){
			printf("please input arguments, you can input:./ups -h\n");
			return -1;
		}
		int rNum = atoi(argv[2]);
		int gNum = atoi(argv[3]);
		int bNum = atoi(argv[4]);
		setrgb(fd,rNum,gNum,bNum);
	}
	else if(strcmp(argv[1],"-t") == 0){
		if(argc != 3){
			printf("please input arguments, you can input:./ups -h\n");
			return -1;
		}
		int min = atoi(argv[2]);
		timer(fd,min);
	}
	else if (strcmp(argv[1],"-a") == 0){
		if(argc != 4){
			printf("please input arguments, you can input:./ups -h\n");
			return -1;
		}
		int min = atoi(argv[2]);
		autorun(fd,min,argv[3]);
	}
	else{
		printf("please input correct arguments, you can input:./ups -h\n");
		return -1;
	}
	
}
