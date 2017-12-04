#include <wiringPiI2C.h>
#include <unistd.h>
#include <signal.h>
#define ID 0x18
int fd;
void fun(int signal_num){
    wiringPiI2CWriteReg8(fd,0x09,0x2);
}

void main(){
    fd = wiringPiI2CSetup(0x18);
    signal(SIGTERM,fun);
    while(1){
        wiringPiI2CWriteReg8(fd,0x0f,0x14);
        sleep(5);
    }
}
