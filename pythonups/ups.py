import _dfups as ups
import sys
import os
import time

ID   = 0x18
wDog = 0x01<<4
led  = 0x01<<3
rgb  = 0x01<<2
shDown=0x01<<1
powAm= 0x01<<0

def shutDown(fd,min=0):
	flag = ups.getFunction(fd)
	flag |= shDown
	if min==0:
		ups.setFunction(fd,flag)
		os.system("sudo shutdown now")
	elif min > 0:
		min = min*60
		time.sleep(min)
		ups.setFunction(fd,flag)
		os.system("sudo shutdown now")


def getHelp(fd):
	print("===========================================^-^=======================================")
	print("ups     [arg]")
	print("        -i")
	print("                get the information of UPS,for example:ID ,VERSION ,ENERGY ,RGB...")
	print(" ")
	print("        -rgb <numR>  <numG>  <numB>")
	print("                need 5 arguments to set RGB,the <numR> <numG> <numB> range 0~255")
	print(" ")
	print("        -s")
	print("                shutdown pi,and UPS will turn off after")
	print(" ")
	print("        -t   <min>")
	print("                after shutdown, the pi will be switched on after <min> minutes")
	print(" ")
	print("        -a   <min>  <exe>")
	print("                pi will turn on in <min> minutes after shutdown,run <exe>")
	print("===========================================^-^=======================================")

def timer(fd,num):
	ups.setTimer(fd,num)

def autorun(fd,num,filename):
	buf = bytearray(128)
	
	os.system("sudo cp /dfups/tmp/startupconfig.txt /home/pi")
	os.system("sudo chgrp pi /home/pi/startupconfig.txt");
	os.system("sudo chown pi /home/pi/startupconfig.txt");

	fp1 = open("/home/pi/startupconfig.txt","r+")
	fp2 = open("rc.local","w+")
	
	timer(fd,num)
	while True:
		buf = fp1.readline()
		fp2.write(buf)
		fp2.flush()
		if buf[:15] == "/dfups/ups_wdog":
			print("setup success!")
			buf = filename + " start &\n"
			fp2.write(buf)
			fp2.flush()
		if not buf:
			break
	
	fp1.close()
	fp2.close()
	os.system("sudo chmod 777 rc.local")
	os.system("sudo chgrp root rc.local")
	os.system("sudo chown root rc.local")
	os.system("sudo rm /home/pi/startupconfig.txt")
	os.system("sudo mv rc.local /etc/")


def getMsg(fd):
	print("id     : %s"% hex(ups.getId(fd)))
	print("version: %s"% hex(ups.getVersion(fd)))
#	en = (int)(ups.getEnergy(fd))
#	if en < 6:
#		print("energy level:%s"% int(en))
#	elif en == 6:
#		print("energy :is charging")
#	elif en == 7:
#		print("energy :fully charge")

	print("energy : %s"% int(ups.getEnergy(fd))+"%")
	print("adc1   : %s"% hex(ups.getAdc1(fd)))
	print("adc2   : %s"% hex(ups.getAdc2(fd)))
	print("vcc    : %s"% hex(ups.getVcc(fd)))
	print("flag   : %s"% hex(ups.getFunction(fd)))
	print("R      : %s"% hex(ups.getRgbR(fd)))
	print("G      : %s"% hex(ups.getRgbG(fd)))
	print("B      : %s"% hex(ups.getRgbB(fd)))

def setrgb(fd,r,g,b):
	flag = ups.getFunction(fd)
	flag |= rgb
	ups.setFunction(fd,flag)
	ups.setRgbR(fd,r)
	ups.setRgbG(fd,g)
	ups.setRgbB(fd,b)

	

def main():
	argc = len(sys.argv)
	if argc < 2:
		print("please input arguments,you can input:ups.py -h")
		return 

	fd = ups.Init(ID)
	if sys.argv[1] == '-s':
		min = 0
		if argc == 3:
			min = int(sys.argv[2])
			if min < 0:
				print("please input a num bigger than 0")
				return -1
		shutDown(fd,min)

	elif sys.argv[1] == '-h':
		getHelp(fd)

	elif sys.argv[1] == '-i':
		getMsg(fd)

	elif sys.argv[1] == '-rgb':
		if(argc < 5):
			print("please input arguments,you can input:ups.py -h")
			return 

		rNum = int(sys.argv[2])
		gNum = int(sys.argv[3])
		bNum = int(sys.argv[4])
		setrgb(fd,rNum,gNum,bNum)

	elif sys.argv[1] == '-t':
		if argc<3:
			print("please input arguments,you can input:ups.py -h")
			return
		num = int(sys.argv[2])
		timer(fd,num)

	elif sys.argv[1] == '-a':
		if argc<4:
			print("please input arguments,you can input:ups.py -h")
			return 
		num = int(sys.argv[2])
		autorun(fd,num,sys.argv[3])
	
	else :
		print("please input arguments,you can input:ups.py -h")

	
main()


