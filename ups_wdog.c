#include <wiringPiI2C.h>
#include <unistd.h>
#define ID 0x18
void main(){
	int fd = wiringPiI2CSetup(0x18);
	while(1){
		wiringPiI2CWriteReg8(fd,0x0f,0x0a);
		sleep(1);
	}

}
