### Configure UPS enviroment
1. External source of power for UPS and Rasberry Pi

2. Enable to I2C:
*1. Input sudo raspi-config in the terminal
*2. Select: Interfacing Options
*3. Select: I2C; enable to I2C

3. cd /home/pi

4. git clone https://github.com/DFRobot/raspberrypi_ups.git

5. cd raspberrypi_ups

6. sh setup.sh
*1. Authorize 
*2. Compliation of  so ups ups_count ups_wdog  
*3. Move ups  .so  .h
*4. Revise self-start files

7. Run ups -i, if your configuration is successful you will see the output as below.
Then UPS can supply Rasberry Pi when you startup the conputer next time.
*  id     :DF
        *  version:10
        *  energy :is charging
        *  adc1   :2117
        *  adc2   :2066
        *  vcc    :0
        *  flag   :18
        *  rgb_r  :0
        *  rgb_g  :0
        *  rgb_b  :0

## API
   * setup I2C ,return file descriptor<br>
            int Init(int id);
   * get information of UPS <br>
        int getId(int fd);          //get id	<br>
        int getVersion(int fd);     //get version number	<br>
        int getEnergy(int fd);      //get battery info <br>
        int getAdc1(int fd);        //get adc1	<br>
        int getAdc2(int fd);        //get adc2	<br>
        int getVcc(int fd);         //get vcc	<br>
        int getFunction(int fd);    //get register	of enable function<br>
        int getRgbR(int fd);        //R		<br>
        int getRgbG(int fd);        //G		<br>
        int getRgbB(int fd);        //B		<br>
        int getTimer(int fd);       //get time of timing start-up <br>

* set UPS 	<br>
            int setFunction(int fd,int flag);   //set register of enable function<br>
            int setRgbR(int fd,int num);        //R	<br>
            int setRgbG(int fd,int num);        //G	<br>
            int setRgbB(int fd,int num);        //B	<br>
            int setTimer(int fd,int num);       //set time of timing start-up <br>
            int shDown(int fd,int time);        //shutdown, time=0 or do not write time	<br>

## UPS Functions
   * ups -h    help
   * ups -i     get information
   * ups -s  shutdown: the time unit for it is the minute, default setting of shutdown now without a stated period of time 
   * ups -rgb  set rgb value: connect RGB device to UPS bord
   * ups -t timing start-up:  when shutdown UPS, you can set time to start-up, the time unit for it is the minute.
   * ups -a  set time of programs porfrom when powered on
	   * Rasberry will switch itself on in setting when UPS turns off and run the program as below, the time unit for it is the minute.
	   * ups -a 1 /home/pi/ups/example/ups_count
	   * Rasberry will switch itself on in one minute when UPS turns off and run the file: /home/pi/ups/example/ups_count	   
*The file is a count file, Rasberry will turn off when one minute pass.
   * UPS can realise amplication by external device such as speaker and etc.
