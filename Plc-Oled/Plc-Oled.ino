/******************************************************************
  Project name : Plc-Oled
  Author       :
  Date Time    : 2019-05-19
  Description  : How to use OLED LCD with Plc-Micro
  CPU BOARD    : PLC-Micro
  URL          : www.plc-expert.com
******************************************************************/
#include <PLC_Automation.h>
#include <PLC_Micro.h>
#include <U8x8lib.h>

// LCD
U8X8_SSD1306_128X32_UNIVISION_HW_I2C lcd(/* reset=*/ U8X8_PIN_NONE);
bool updateDisplayForInputs = false;
bool updateDisplayForOutputs = false;

// I/O declaration
PLC_Micro micro;          // Micro Board, initializes pin modes automatically
PLC_Automation plc;       // Automation features
IoPorts Inputs;           // Inputs 1-8
IoPorts Outputs;          // Outputs 1-8
int stepNr = 0;

void setup()
{
  //init lcd
  lcd.begin();
  lcd.setPowerSave(0);
  lcd.setFont(u8x8_font_chroma48medium8_r);

  updateDisplayForInputs = true;
  updateDisplayForOutputs = true;
}

void loop()
{
  ReadInputs();
  DisplayInputs();
  DisplayOutputs();
  DisplayStepNr();
}

void DisplayStepNr(){
  char charArray[3];
  String AddressStr = String(stepNr);
  AddressStr.toCharArray(charArray, 3);
  lcd.drawString(0, 0, "Step=");
  lcd.drawString(5, 0, charArray);
}
void DisplayInputs()
{ 
  //Inputs
  int arrayLen = 10;
  lcd.drawString(0, 2, "I=");
  char charArray[arrayLen];  
  String stateStr = StateToString(Inputs.port8) + StateToString(Inputs.port7) + StateToString(Inputs.port6) + StateToString(Inputs.port5) 
    + "-" + StateToString(Inputs.port4) + StateToString(Inputs.port3) + StateToString(Inputs.port2) + StateToString(Inputs.port1);
  stateStr.toCharArray(charArray, arrayLen);
  lcd.drawString(2, 2, charArray);
}

void DisplayOutputs()
{
  if(!updateDisplayForInputs) return;
  
  int arrayLen = 10;  
  lcd.drawString(0, 3, "O=");
  char charArray[arrayLen];  
  String stateStr = StateToString(Outputs.port8) + StateToString(Outputs.port7) + StateToString(Outputs.port6) + StateToString(Outputs.port5)
    + "-" + StateToString(Outputs.port4) + StateToString(Outputs.port3) + StateToString(Outputs.port2) + StateToString(Outputs.port1);    
  stateStr.toCharArray(charArray, arrayLen);
  lcd.drawString(2, 3, charArray);

  updateDisplayForInputs = false;
}

void ReadInputs(){
  IoPorts newInputs;
  newInputs.port1 = plc.Input(INPUT_1);
  newInputs.port2 = plc.Input(INPUT_2);
  newInputs.port3 = plc.Input(INPUT_3);
  newInputs.port4 = plc.Input(INPUT_4);
  newInputs.port5 = plc.Input(INPUT_5);
  newInputs.port6 = plc.Input(INPUT_6);
  newInputs.port7 = plc.Input(INPUT_7);
  newInputs.port8 = plc.Input(INPUT_8);

  //Update LCD only when neccesary
  updateDisplayForInputs = (Inputs.Value != newInputs.Value);
  Inputs.Value = newInputs.Value;
}

void SetupOutputs(){
    plc.Output(OUTPUT_1, Outputs.port1);
    plc.Output(OUTPUT_2, Outputs.port2);
    plc.Output(OUTPUT_3, Outputs.port3);
    plc.Output(OUTPUT_4, Outputs.port4);
    plc.Output(OUTPUT_5, Outputs.port5);
    plc.Output(OUTPUT_6, Outputs.port6);
    plc.Output(OUTPUT_7, Outputs.port7);
    plc.Output(OUTPUT_8, Outputs.port8);
}

String StateToString(bool State)
{
  return String(State);
}
