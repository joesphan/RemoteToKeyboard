
#include <IRremote.h>

#include "HID-Project.h"

int IR_RECEIVE_PIN = 5;

unsigned int holdbtn;     //{0,1,2,3};    {leftarrow, rightarrow, uparrow, downarrow}

IRrecv IrReceiver(IR_RECEIVE_PIN);

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(115200);   // Status message will be sent to PC at 9600 baud
    delay(2000); // To be able to connect Serial monitor after reset and before first printout

    IrReceiver.enableIRIn();  // Start the receiver
    IrReceiver.blink13(true); // Enable feedback LED
    pinMode(9, OUTPUT);
    Consumer.begin();
    BootKeyboard.begin();
}


decode_results results;
int pinstate = 0;
int holdcount = 0;
void loop() {
  if (IrReceiver.decode(&results)) {  // Grab an IR code
    if (results.value == 0x80BF3BC4) {
      //power
      BootKeyboard.write(KEY_INSERT);
      holdcount = 0;
      holdbtn = 4;
    }
    else if (results.value == 0x80BF39C6) {
      //mute
      Consumer.write(MEDIA_PLAY_PAUSE);
      holdcount = 0;
      holdbtn = 4;
    }
    else if (results.value == 0x80BF738C) {
      //enter
      BootKeyboard.write(KEY_RETURN);
      holdcount = 0;
      holdbtn = 4;
    }
    else if (results.value == 0x80BF9966) {
      //left
      BootKeyboard.write(HID_KEYBOARD_LEFTARROW);
      holdcount = 0;
      holdbtn = 0;
    }
    else if (results.value == 0x80BF837C) {
      //right
      BootKeyboard.write(HID_KEYBOARD_RIGHTARROW);
      holdcount = 0;
      holdbtn = 1;
    }
    else if (results.value == 0x80BF53AC) {
      //up
      BootKeyboard.write(HID_KEYBOARD_UPARROW);
      holdcount = 0;
      holdbtn = 2;
    }
    else if (results.value == 0x80BF4BB4) {
      //down
      BootKeyboard.write(HID_KEYBOARD_DOWNARROW);
      holdcount = 0;
      holdbtn = 3;
    }
    else if (results.value == 0x80BF19E6) {
      //home
      BootKeyboard.write(HID_KEYBOARD_LEFT_GUI);
      holdcount = 0;
      holdbtn = 4;
    }
    else if (results.value == 0x80BFA35C) {
      //back
      BootKeyboard.write(KEY_ESC);
      holdcount = 0;
      holdbtn = 4;
    }
    else if (results.value == 0x80BFA956) {
      //menu
      BootKeyboard.write(KEY_APPLICATION);
      holdcount = 0;
      holdbtn = 4;
    }
    else if (results.value == 0x80BFA15E) {
      //volup
      Consumer.write(MEDIA_NEXT);
      holdcount = 0;
      holdbtn = 4;
    }
    else if (results.value == 0x80BF619E) {
      //voldown
      Consumer.write(MEDIA_PREVIOUS);
      holdcount = 0;
      holdbtn = 4;
    }
    else if (results.value == 0xFFFFFFFF) {
      //hoooold
      if (holdcount > 3) {
        //held for long enough, write
        switch (holdbtn) {
          case 0:
          BootKeyboard.write(HID_KEYBOARD_LEFTARROW);
          break;
          case 1:
          BootKeyboard.write(HID_KEYBOARD_RIGHTARROW);
          break;
          case 2:
          BootKeyboard.write(HID_KEYBOARD_UPARROW);
          break;
          case 3:
          BootKeyboard.write(HID_KEYBOARD_DOWNARROW);
          break;
          case 4:
          //some other key
          break;
        }
      }
      else {
        holdcount++;
      }
      
    }
    else {
      //oop
    }
    Serial.println(results.value, HEX);
    IrReceiver.resume();              // Prepare for the next value
  }
}
