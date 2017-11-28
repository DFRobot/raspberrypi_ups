#ifndef __UPS_H_
#define __UPS_H_

#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>

int getId(int fd);
int getVersion(int fd);
int getEnergy(int fd);
int getAdc1(int fd);
int getAdc2(int fd);
int getVcc(int fd);
int setFunction(int fd,int flag);
int getFunction(int fd);
int getRgbR(int fd);
int setRgbR(int fd,int num);
int getRgbG(int fd);
int setRgbG(int fd,int num);
int setRgbB(int fd,int num);
int getRgbB(int fd);
int Init(int id);
int getTimer(int fd);
int setTimer(int fd,int num);
int shDown(int fd,int time);
int setElectricity(int fd,int value);
int getElectricity(int fd);
#endif

