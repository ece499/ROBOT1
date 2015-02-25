/* Dynamixel Wheel Mode Example
 
 This example shows how to use dynamixel as wheel mode
 All dynamixels are set as joint mode in factory,
 but if you want to make a wheel using dynamixel, 
 you have to change it to wheel mode by change CCW angle limit to 0
 
               Compatibility
 CM900                  O
 OpenCM9.04             O
 
                  Dynamixel Compatibility
               AX    MX      RX    XL-320    Pro
 CM900          O      O      O        O      X
 OpenCM9.04     O      O      O        O      X
 **** OpenCM 485 EXP board is needed to use 4 pin Dynamixel and Pro Series ****  
 
 created 16 Nov 2012
 by ROBOTIS CO,.LTD.
 */
 /* Serial device defines for dxl bus */
#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
/* Dynamixel ID defines */
#define ID_NUM1 1
#define ID_NUM2 2
/* Control table defines */
#define GOAL_SPEED 32
#define CCW_Angle_Limit 8
#define CONTROL_MODE 11
Dynamixel Dxl(DXL_BUS_SERIAL1);
//volatile float voltage=0;
//float thresh=1.65;//default
void setup() {
  // Dynamixel 2.0 Protocol -> 0: 9600, 1: 57600, 2: 115200, 3: 1Mbps 
  Dxl.begin(3);
  //AX MX RX Series   
  Dxl.writeWord(ID_NUM1, CCW_Angle_Limit, 0); 
  Dxl.writeWord(ID_NUM2, CCW_Angle_Limit, 0); 
  //disable CCW Angle Limit(L) to use wheel mode

  //XL-320
  //Dxl.writeByte(ID_NUM, CONTROL_MODE, 1);
}
char inchar;
byte index=0;
void loop() {
    if(SerialUSB.available()>0){
    char indata[20];
    while(SerialUSB.available()>0){
      if(index<19){
        inchar=SerialUSB.read();
        indata[index]=inchar;
        index++;
        indata[index]='\0';
      }
    }
    index=0;
  if(indata[0]=='s'){//1.65=3.3/2
    //forward
    //Dxl.writeWord(ID_NUM1, GOAL_SPEED, 200); 
    //Dxl.writeWord(ID_NUM2, GOAL_SPEED, 200| 0x400); //mounting
    //stop
    Dxl.writeWord(ID_NUM1, GOAL_SPEED, 0| 0x400); 
    Dxl.writeWord(ID_NUM2, GOAL_SPEED, 0); //mounting
    delay(100);
  }
  else if(indata[0]=='l') {
    //turn left
    Dxl.writeWord(ID_NUM1, GOAL_SPEED, 200);
    Dxl.writeWord(ID_NUM2, GOAL_SPEED, 200);
    delay(100); 
  }
    else if(indata[0]=='r') {
    //turn right
    Dxl.writeWord(ID_NUM1, GOAL_SPEED, 200| 0x400);
    Dxl.writeWord(ID_NUM2, GOAL_SPEED, 200| 0x400);
    delay(100); 
  }
  else if(indata[0] =='b'){
    //back
    Dxl.writeWord(ID_NUM1, GOAL_SPEED, 200| 0x400); 
    Dxl.writeWord(ID_NUM2, GOAL_SPEED, 200); //mounting
    delay(100); 
  }
  else{
    //forward
    Dxl.writeWord(ID_NUM1, GOAL_SPEED, 200); 
    Dxl.writeWord(ID_NUM2, GOAL_SPEED, 200| 0x400); //mounting
    delay(100);
    //stop
    //Dxl.writeWord(ID_NUM1, GOAL_SPEED, 0| 0x400); 
    //Dxl.writeWord(ID_NUM2, GOAL_SPEED, 0); //mounting
  }
}
}
