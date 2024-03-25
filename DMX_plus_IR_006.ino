// - - - - -
// DmxSerial - A hardware supported interface to DMX.
//
// - - - - -

// Version 006 vom 21.03.2024
//  Reihenfolge der gebündelten Abläufe geändert:
//    -erst "night light" dann "amber" in "EINLASS"

// DMX Adresse: 505
// Serial off
// Pin für DMX input: 9
// Pin für IR-Sender: 3



#include <DMXSerial.h>
#include <IRremote.hpp>

const int SenderPin = 3; // Pin D1 beim NodeMCU ESP8266
uint16_t Address = 0x1;
uint8_t Command = 0x12;
uint8_t Repeats = 0;
// Constants for demo program

const int DMX_In =    9;  // output pin...DMX in ready

// receive at Adress with this channel:
const int DMX_Channel = 505;
int DATA = 0;

void setup() {

  //   Serial.begin(115200);
  pinMode(SenderPin, OUTPUT);
  IrSender.begin(SenderPin);
  DMXSerial.init(DMXReceiver);

  // set some default values
  DMXSerial.write(1, 80);
  // enable pwm outputs
  pinMode(DMX_In,   OUTPUT); // sets the digital pin as output
}

void loop()
{
  // Calculate how long no data bucket was received
  unsigned long lastPacket = DMXSerial.noDataSince();

  if (lastPacket < 5000)
  {
    analogWrite(DMX_In, 200);     //DMX wird empfangen --> LED on

    // read recent DMX values and set pwm levels
    DATA = DMXSerial.read(DMX_Channel);
    /*
      if (DATA == 0)
      {
      // do nothing
      }
    */
    if ( DATA > 1 && DATA < 10)
    {
      // PLUG OFF:
      // ++++++++++++++++++++++++++++++
      Address = 0x1;
      Command = 0x1;
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
    if ( DATA > 11 && DATA < 20)
    {
      // PLUG ON:
      // ++++++++++++++++++++++++++++++
      Address = 0x1;
      Command = 0x12;
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
    if ( DATA > 21 && DATA < 30)
    {
      // NIGHT LIGHT:
      // ++++++++++++++++++++++++++++++
      Address = 0x1;
      Command = 0x1E;
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
    if ( DATA > 31 && DATA < 40)
    {
      // ROT PLUG: 
      // on/red/bright
      // ++++++++++++++++++++++++++++++
      Address = 0x1;
      Command = 0x12;   // on
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x7;  // rot
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x6;   // bright
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
    if ( DATA > 41 && DATA < 50)
    {
      // ORANGE PLUG:
      // on/orange/bright
      // ++++++++++++++++++++++++++++++
      //ON
      Address = 0x1;
      Command = 0x12;  // on
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0xA;  // orange
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x6;   // bright
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
    if ( DATA > 51 && DATA < 60)
    {
      // PINK PLUG:
      // on/pink/bright
      // ++++++++++++++++++++++++++++++
      Address = 0x1;
      Command = 0x12;  // on
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0xC;   // pink
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x6;   // bright
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
    if ( DATA > 61 && DATA < 70)
    {
      // MAGENTA PLUG:
      // on/magenta/bright
      // ++++++++++++++++++++++++++++++
      Address = 0x1;
      Command = 0x12;  // on
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x0;  // magenta
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x6;   //bright
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
    if ( DATA > 91 && DATA < 100)
    {
      // LOW LIGHT:
      // ++++++++++++++++++++++++++++++
      Address = 0x1;
      Command = 0x5;
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
    if ( DATA > 101 && DATA < 110)
    {
      // GREEN PLUG:  
      // on/green/bright
      // ++++++++++++++++++++++++++++++
      Address = 0x1;
      Command = 0x12;  // on
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x8;   // green
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x6;   // bright
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
    if ( DATA > 111 && DATA < 120)
    {
      // HELLGRÜN PLUG:
      // on/hellgrün/bright
      // ++++++++++++++++++++++++++++++
      Address = 0x1;
      Command = 0x12;  // on
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x1B;  // hellgrün
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x6;   // bright
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
    if ( DATA > 121 && DATA < 130)
    {
      // AMBER PLUG:
      // on/amber/bright
      // ++++++++++++++++++++++++++++++
      Address = 0x1;
      Command = 0x12;  // on
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0xD;   // amber
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x6;   // bright
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
    if ( DATA > 131 && DATA < 140)
    {
      // GELB PLUG:
      // ++++++++++++++++++++++++++++++
      // on/gelb/bright
      Address = 0x1;
      Command = 0x12;  //on
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0xF;  //gelb
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x6;   // bright
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
    if ( DATA > 161 && DATA < 170)
    {
      // BRIGHT LIGHT PLUG:
      // ++++++++++++++++++++++++++++++
      Address = 0x1;
      Command = 0x6;
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
    if ( DATA > 171 && DATA < 180)
    {
      // DUNKELBLAU PLUG:
      // ++++++++++++++++++++++++++++++
      // on/dunkelblau/bright
      Address = 0x1;
      Command = 0x12; // on
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x9;  // dunkelblau
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x6;   // bright
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
    if ( DATA > 181 && DATA < 190)
    {
      // BLAU PLUG:
      // on/blau/bright
      // ++++++++++++++++++++++++++++++
      Address = 0x1;
      Command = 0x12;  // on
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x1F;  // blau
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x6;   // bright
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
    if ( DATA > 191 && DATA < 200)
    {
      // HELLBLAU PLUG:
      // on/hellblau/bright
      // ++++++++++++++++++++++++++++++
      Address = 0x1;
      Command = 0x12;  // on
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0xE;  // hellblau
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x6;   // bright
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
    if ( DATA > 201 && DATA < 210)
    {
      // KALTWEISSPLUG:
      // on/kaltweiss/bright
      // ++++++++++++++++++++++++++++++
      //ON
      Address = 0x1;
      Command = 0x12;  // on
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x19;  // kaltweiss
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x6;   // bright
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
    if ( DATA > 211 && DATA < 220)
    {
      //EINLASS: 
      // on/night/amber
      //++++++++++++++++++++++++++++++
      //ON
      Address = 0x1;
      Command = 0x12;  // on
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      Address = 0x1;
      Command = 0x1E;  // night
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);

      Address = 0x1;
      Command = 0xD;  // amber
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
      IrSender.sendNEC(Address, Command, Repeats);
      delay(30);
    }
  }
  else
  {
    // switch DMX_LED off, when no data was received since 5 seconds or more.
    analogWrite(DMX_In, 0);
  }
}
// End.
