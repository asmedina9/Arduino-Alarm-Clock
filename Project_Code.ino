//#include <dht_nonblocking.h>
#include "IRremote.h"
#include <LiquidCrystal.h>
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );
//www.elegoo.com
//2016.12.9

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */



// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


//Declaring remote objects and functions
int receiver = 6;
IRrecv irrecv(receiver);
decode_results results;

//Remote controls-------------Need to edit for alarm clock function
void translateIR(){
  switch(results.value){
    case 0xFFA25D: lcd.println("POWER");          break;
    case 0xFFE21D: lcd.println("FUNC/STOP");      break;
    case 0xFF629D: lcd.println("VOL+");           break;
    case 0xFF22DD: lcd.println("FAST BACK");      break;
    case 0xFF02FD: lcd.println("PAUSE");          break;
    case 0xFFC23D: lcd.println("FAST FORWARD");   break;
    case 0xFFE01F: lcd.println("DOWN");           break;
    case 0xFFA857: lcd.println("VOL-");           break;
    case 0xFF906F: lcd.println("UP");             break;
    case 0xFF9867: lcd.println("EQ");             break;
    case 0xFFB04F: lcd.println("ST/REPT");        break;
    case 0xFF6897: lcd.println("0");              break;
    case 0xFF30CF: lcd.println("1");              break;
    case 0xFF18E7: lcd.println("2");              break;
    case 0xFF7A85: lcd.println("3");              break;
    case 0xFF10EF: lcd.println("4");              break;
    case 0xFF38C7: lcd.println("5");              break;
    case 0xFF5AA5: lcd.println("6");              break;
    case 0xFF42BD: lcd.println("7");              break;
    case 0xFF4AB5: lcd.println("8");              break;
    case 0xFF52AD: lcd.println("9");              break;
    case 0xFFFFFFFF: lcd.println(" REPEAT");      break;  
  
    default: 
      Serial.println(" other button : ");
      Serial.println(results.value);
  }
}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Alarm Clock");

  //Setting up remote control
  Serial.begin(9600);
  irrecv.enableIRIn();
}

static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}


//Commenting out for now until remote settings are done
/*void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  // lcd.print(millis() / 1000);

 //Print Temperature gague
 float temperature;
 float humidity;

 if(measure_environment (&temperature, &humidity) == true){
  lcd.print("T=");
  lcd.print(temperature, 1);
  lcd.print("C, H=");
  lcd.print(humidity, 1);
  lcd.print("%") ;
 }
 }*/
