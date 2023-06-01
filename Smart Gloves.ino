#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please enable it
#endif

BluetoothSerial SerialBT;

const int Thumb_fingerPin = 13;
const int Fore_fingerPin = 12;
const int Middle_fingerPin = 14;

int Thumb_fingerValue = 0;
int Fore_fingerValue = 0;
int Middle_fingerValue = 0;

bool flag_A, flag_B, flag_C = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  SerialBT.begin("NIVE"); //Bluetooth device name
  delay(1000); // just my reference delay
}

void loop() {
  // read the input on analog pin 0:
  Thumb_fingerValue = analogRead(Thumb_fingerPin);
  Thumb_fingerValue = Thumb_fingerValue / 4.95;
  delay(10);
  // print out the value you read:
  Serial.print("Thumb_fingerValue: ");
  Serial.println(Thumb_fingerValue);

  Fore_fingerValue = analogRead(Fore_fingerPin);
  Fore_fingerValue = Fore_fingerValue / 4.95;
  delay(10);
  // print out the value you read:
  Serial.print("Fore_fingerValue: ");
  Serial.println(Fore_fingerValue);

  Middle_fingerValue = analogRead(Middle_fingerPin);
  Middle_fingerValue = Middle_fingerValue / 4.95;
  delay(10);
  // print out the value you read:
  Serial.print("Middle_fingerValue: ");
  Serial.println(Middle_fingerValue);

  (Thumb_fingerValue > 85) ? flag_A = 1 : flag_A = 0;

  (Fore_fingerValue > 85) ? flag_B = 1 : flag_B = 0;

  (Middle_fingerValue > 85) ? flag_C = 1 : flag_C = 0;

  if (flag_A == 0 && flag_B == 0 && flag_C == 0) {                    //000    
//    SerialBT.print(1);
    Serial.println("Safe...(000)");
    delay(3000);
  }else if (flag_A == 0 && flag_B == 0 && flag_C == 1) {              //001
    SerialBT.print(1);
    Serial.println("I Need Water...(001)");
    delay(3000);
  } else if (flag_A == 0 && flag_B == 1 && flag_C == 0) {             //010
    SerialBT.print(2);
    Serial.println("I want Food...(010)");
    delay(3000);
  } else if (flag_A == 0 && flag_B == 1 && flag_C == 1) {            //011
    SerialBT.print(3);
    Serial.println("Need to go to Restroom...(011)");
    delay(3000);
  } else if (flag_A == 1 && flag_B == 0 && flag_C == 0) {            //100
    SerialBT.print(4);
    Serial.println("I Need a bath...(100)");
    delay(3000);
  } else if (flag_A == 1 && flag_B == 0 && flag_C == 1) {            //101
    SerialBT.print(5);
    Serial.println("Pat the TV On...(101)");
    delay(3000);
  } else if (flag_A == 1 && flag_B == 1 && flag_C == 0) {            //110
    SerialBT.print(6);
    Serial.println("Take me Outside...(110)");
    delay(3000);
  } else if (flag_A == 1 && flag_B == 1 && flag_C == 1) {           //111
    SerialBT.print(7);
    Serial.println("I need to go to bed...(111)");
    delay(3000);
  } else

    delay(8000); // delay in between reads for stability
}
