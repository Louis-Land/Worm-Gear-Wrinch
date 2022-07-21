// SimpleRxAckPayload- the slave or the receiver

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_NeoPixel.h>

#define CE_PIN   D6
#define CSN_PIN D7
#define NUMPIXELS 1

const byte thisSlaveAddress[6] = "RxA04";

RF24 radio(CE_PIN, CSN_PIN);

int downPin = D5;
int upPin = D4;
int enabledPin = 6;  

char dataReceived[20]; // this must match dataToSend in the TX
int ackData[2] = {109, -4000}; // the two values to be sent to the master
bool newData = false;
int idleTime = 0;
bool commandForMe = false;
int PIN = 12;
int Power = 11;
bool idled = true;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//==============

void setup() {

    Serial.begin(115200);

    Serial.println("SimpleRxAckPayload Starting");
    radio.begin();
    radio.setDataRate( RF24_2MBPS );
    radio.openReadingPipe(1, thisSlaveAddress);

    int powerLeveLBeginning = radio.getPALevel();
    Serial.println("Starting PA Level");
    Serial.println(powerLeveLBeginning);

    radio.enableAckPayload();
    radio.setPALevel( RF24_PA_MIN );
    int powerLevel = radio.getPALevel();
    Serial.println("After Setting PA Level");
    Serial.println(powerLevel);

    pixels.begin();
    pixels.setBrightness(10);
    pinMode(Power,OUTPUT);
    digitalWrite(Power, HIGH);

    if(powerLeveLBeginning != powerLevel) {
        Serial.println("radio was detected");
        pixels.clear();
        idleColor();
        pixels.show();
        delay(2000);
    } else {
        Serial.println("radio is not detected");
        pixels.clear();
        pixels.setPixelColor(0, pixels.Color(230, 0, 0));
        pixels.show();
        for(;;){}
    }

    radio.startListening();

    radio.writeAckPayload(1, &ackData, sizeof(ackData)); // pre-load data

    pinMode(upPin, OUTPUT);
    pinMode(downPin, OUTPUT);

    digitalWrite(upPin, LOW);
    digitalWrite(downPin, LOW); 
}

//==========

void loop() {
  
    getData();
    showData();
    updateLED();
}

//============

void getData() {
    if ( radio.available() ) {
        radio.read( &dataReceived, sizeof(dataReceived) );
        updateReplyData();
        newData = true;
    }
}

//================

void showData() {

    if(idleTime > 10000 -1) {
        idled = true;
        digitalWrite(enabledPin, LOW);
        digitalWrite(downPin, LOW);
        digitalWrite(upPin, LOW);
    }

    if (newData == true) {
        idleTime = 0;
        idled = false;
        char upCommandText[20] = "Command UP";
        char downCommandText[20] = "Command DOWN";
        char nothingCommand[20] = "Command NOTHING";

        bool nothingComparsion = strcmp(dataReceived, nothingCommand) == 0;

        bool emptyComparsion = strcmp(dataReceived, "") == 0;

        if(!emptyComparsion) {
            if(strcmp(dataReceived, upCommandText) == 0 && !nothingComparsion) {
                Serial.println("GOING UP");
                digitalWrite(downPin, HIGH);
                digitalWrite(upPin, LOW);
            } else if(strcmp(dataReceived, downCommandText) == 0 && !nothingComparsion) {
                Serial.println("GOING DOWN");
                digitalWrite(upPin, HIGH);
                digitalWrite(downPin, LOW);
            } else if(nothingComparsion) {
                Serial.println("NOTHING");
                digitalWrite(downPin, LOW);
                digitalWrite(upPin, LOW);
                digitalWrite(enabledPin, HIGH);
            }
        } 
        newData = false;
    } else {
        idleTime++;
    }

}

//================

void updateReplyData() {
    ackData[0] -= 1;
    ackData[1] -= 1;
    if (ackData[0] < 100) {
        ackData[0] = 109;
    }
    if (ackData[1] < -4009) {
        ackData[1] = -4000;
    }
    radio.writeAckPayload(1, &ackData, sizeof(ackData)); // load the payload for the next time
}

//====================================================
void updateLED() {
  if(idled) {
    idleColor();
  } else {
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(0, 153, 0));
    pixels.show();
  }
}

//=========================================================
void idleColor() {
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(0, 30, 179));
  pixels.show();
}
