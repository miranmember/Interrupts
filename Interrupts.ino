// 1- Miran Member
// 2- Interrups
// 3- Description - Attatch two interrupts for two buttons. when you press button 1 it stop the timer on the lcd screen and shows a messege stating it was interrupted. when you press button two it resets.
// 4- Include any assumptions you may have made, what do you expect from the hardware, pinouts, particular Arduino versions, etc... : NONE
// 5- References - https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
#include <LiquidCrystal.h>


int Timer = 0; // there is no way to reset the timer millis(), so instead using delay and counter to keep track of it.
bool ButtonToContinueState = false; // this will turn true when the interrupt is called by the button
String mess1 = "Interrupted, Press button 2 to continue."; // the message that is to be displayed and since it cant fit in the screen i wrote it saperatly so it can be scrolled.
int start, stop = 0; // used for lcd scrolling
int scroll = 16;
LiquidCrystal lcd(12, 11, 9, 8, 7, 6);
void setup() {
  lcd.begin(16,2);
  attachInterrupt(digitalPinToInterrupt(2),ButtonToContinue,CHANGE);
  attachInterrupt(digitalPinToInterrupt(3),ButtonToReset,CHANGE);
}



void loop() {
  if (!ButtonToContinueState) { // the statement will only execute when the first button interrpts it and changes the variable to true
    lcd.print("Waiting for");
    lcd.setCursor(0,1);
    lcd.print(Timer);
    lcd.print(" Seconds");
    delay(1000);
    lcd.clear();
    Timer++;
  } else { 
    lcd.setCursor(0,0);
    lcd.print(mess1.substring(start,stop));
    delay(300);
    lcd.clear();
    if(start == 0 && scroll > 0){
      scroll--;
      stop++;
    } else if (start == stop){
      start = stop = 0;
      scroll = 16;
    } else if (stop == mess1.length() && scroll == 0) {
      start++; 
    } else {
      start++;
      stop++;
    }
  }
}

void ButtonToContinue() { // only changing the variable so in the loop the code that I want to execute for button two will work instead
  ButtonToContinueState = true;
}

void ButtonToReset() { // resetting the timer and changing the variable so the origal if statement is executed
  ButtonToContinueState = false;
  Timer = 0;
}
