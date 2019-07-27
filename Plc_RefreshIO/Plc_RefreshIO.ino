/******************************************************************
  Project name : PLC-Refresh IO
  Author       :
  Date Time    : 2019-07-05
  Description  : 
  CPU BOARD    : PLC-Micro
  URL          : www.plc-expert.com
******************************************************************/

#include <Thread.h>
Thread plcThread = Thread();

int counter = 0;

void setup(){
	Serial.begin(9600);	
	plcThread.onRun(PlcTreadFunction);
	plcThread.setInterval(1);
	plcThread.run();
}

void PlcTreadFunction(){
	counter++;  
}

void loop(){
  Serial.print("Counter=");
  Serial.println(counter);
  delay(1000);
}
