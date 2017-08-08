### 配置UPS环境

   * 1.分别给UPS与树莓派外接电源
   * 2.使能I2C：
        * 1.终端输入sudo raspi-config
        * 2.选择Interfacing Options
        * 3.选择I2C，使能I2C
   * 3.将copy ups /home/pi/
   * 4.sh /home/pi/ups/setup.sh
        * 1.加权限
        * 2.编译so ups ups_count ups_wdog   
        * 3.ups  .so  .h文件的移动
        * 4.修改自启动文件

   * 5.运行ups -i 如果输出结果如下则配置成功。下次开机UPS可为树莓派供电。
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
        int getId(int fd);          //获取id	<br>
        int getVersion(int fd);     //获取版本号	<br>
        int getEnergy(int fd);      //获取电量状态	<br>
        int getAdc1(int fd);        //获取adc1	<br>
        int getAdc2(int fd);        //获取adc2	<br>
        int getVcc(int fd);         //获取vcc	<br>
        int getFunction(int fd);    //获取功能使能寄存器	<br>
        int getRgbR(int fd);        //R		<br>
        int getRgbG(int fd);        //G		<br>
        int getRgbB(int fd);        //B		<br>
        int getTimer(int fd);       //获取定时开机时间	<br>
            
   * set UPS 	<br>
            int setFunction(int fd,int flag);   //设置功能使能寄存器	<br>
            int setRgbR(int fd,int num);        //R	<br>
            int setRgbG(int fd,int num);        //G	<br>
            int setRgbB(int fd,int num);        //B	<br>
            int setTimer(int fd,int num);       //设置定时开机时间	<br>
            int shDown(int fd,int time);        //定时关机，立即关机，time=0或不写time	<br>

## UPS功能
   * ups -h  帮助
   * ups -i 获取信息	
   * ups -s 定时关机 :     时间以分钟为单位，如果没有写时间，则默认立即关机
   * ups -rgb 设置rgb值 : 可在ups板子上接RGB设备
   * ups -t 定时开机 :    UPS关机后，会在设定时间让树莓派开机，时间单位为分钟
   * ups -a 设置设定时间开机运行程序
	   * UPS关机后，会在设定时间让树莓派开机，时间单位为分钟，并运行程序，如：
	   * ups -a 1 /home/pi/ups/example/ups_count
	   * UPS关机后，1分钟后让树莓派开机，树莓派开机后自动运行/home/pi/ups/example/ups_count文件
	   * （此文件为计数文件，计满1分钟后，树莓派关机）
   * UPS外接扬声器等音频设备,实现功放
