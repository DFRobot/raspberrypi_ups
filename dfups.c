#include"dfups.h"

#define wDog	0x01<<4
#define led		0x01<<3
#define rgb		0x01<<2
#define shtdown	0x01<<1
#define powam	0x01<<0

int getId(int fd){
    int id = wiringPiI2CReadReg8(fd,0x00);
    return id;
}

int getVersion(int fd){
    int version = wiringPiI2CReadReg8(fd,0x01);
    return version;
}

int getEnergy(int fd){
    int en = wiringPiI2CReadReg8(fd,0x02);
    return en;
}

/**************ADC*****************/

int getAdc1(int fd){
    int adcL = wiringPiI2CReadReg8(fd,0x04);
    int adcH = wiringPiI2CReadReg8(fd,0x03);

    int adc1 = (adcH << 8)|adcL;
//
    
    return adc1;
}

int getAdc2(int fd){
    int adcL = wiringPiI2CReadReg8(fd,0x06);
    int adcH = wiringPiI2CReadReg8(fd,0x05);

    int adc2 = (adcH << 8)|adcL;
//
    
    return adc2;
}

/**************VCC******************/

int getVcc(int fd){
    int vccH = wiringPiI2CReadReg8(fd,0x07);
    int vccL = wiringPiI2CReadReg8(fd,0x08);

    int vcc = (vccH << 8)|vccL;
//

    return vcc;
}

/*****************Function register*****************/

int setFunction(int fd,int flag){
    wiringPiI2CWriteReg8(fd,0x09,flag);
    
    return 0;
}

int getFunction(int fd){
    int flag;
    
    flag = wiringPiI2CReadReg8(fd,0x09);
    return flag;
}

/*****************RGB******************/

int getRgbR(int fd){
    int rgbR = wiringPiI2CReadReg8(fd,0x0A);
    return rgbR;
}

int setRgbR(int fd,int num){
    if(num > 255){
        printf("Please re-enter a value less than 255\n");
        return -1;
    }
    wiringPiI2CWriteReg8(fd,0x0A,num);
    return 0;
}

int getRgbG(int fd){
    int rgbG = wiringPiI2CReadReg8(fd,0x0B);
    return rgbG;
}

int setRgbG(int fd,int num){
    if(num > 255){
        printf("Please re-enter a value less than 255\n");
        return -1;
    }
    wiringPiI2CWriteReg8(fd,0x0B,num);
    return 0;
}

int getRgbB(int fd){
    int rgbB = wiringPiI2CReadReg8(fd,0x0C);
    return rgbB;
}

int setRgbB(int fd,int num){
    if(num > 255){
        printf("Please re-enter a value less than 255\n");
        return -1;
    }
    wiringPiI2CWriteReg8(fd,0x0C,num);
    return 0;
}

int Init(int id){

    int fd = wiringPiI2CSetup(id);
    return fd;
}

int getTimer(int fd){
    int timL = wiringPiI2CReadReg8(fd,0x0E);
    int timH = wiringPiI2CReadReg8(fd,0x0D);
    
    int tim = (timH << 8) | timL;
    return tim;
}

int setTimer(int fd,int min){
    int timH = 0;
    if(min < 255){
        wiringPiI2CWriteReg8(fd,0x0E,min);
        wiringPiI2CWriteReg8(fd,0x0D,0);
    }
    else{
        timH = min - 255;
        wiringPiI2CWriteReg8(fd,0x0E,255);
        wiringPiI2CWriteReg8(fd,0x0D,timH);
    }
    return 0;
}

int getElectricity(int fd){
    int elec = wiringPiI2CReadReg8(fd,0x10);
    return elec;
}

int setElectricity(int fd,int value){
    if((value > 255)||(value < 10)){
        printf("Please re-enter a value range(10,255)\n");
        return -1;
    }
    wiringPiI2CWriteReg8(fd,0x10,value);
    return 0;
}

int shDown(int fd,int time){
    char buf[32];
//    int flag = getFunction(fd);
//    flag |= shtdown;
//    setFunction(fd,flag);
    sprintf(buf,"sleep %d && sudo shutdown now\n",time);
    system(buf);
    return 0;
}

