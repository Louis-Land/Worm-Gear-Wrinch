// SimpleTxAckPayload - the master or the transmitter

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define CE_PIN   9
#define CSN_PIN 10
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int UP_PIN = 8;
int DOWN_PIN = 5;
int CHANNEL_UP = 7;
int CHANNEL_DOWN = 6;

byte slaveAddress[5] = "RxA00";

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

int txNum = 0;

int ackData[2] = {-1, -1}; // to hold the two values coming from the slave
bool newData = false;

bool sentUp = true;
bool doNothing = true;
bool radioConnected = false;
int currentChannel = 0;
int prevChannel = 0;
int maxChannels = 10;

bool txFailed = false;

unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 20; // send once per second

unsigned long changeChannelPrevMillis;
unsigned long changeChannelInterval = 300; // send once per second


//===============

void setup() {

    Serial.begin(115200);
    pinMode(UP_PIN, INPUT);
    pinMode(DOWN_PIN, INPUT);

    pinMode(CHANNEL_UP, INPUT);
    pinMode(CHANNEL_DOWN, INPUT);

    pinMode(13, OUTPUT);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
    }

    display.display();
    display.clearDisplay();

    radio.begin();
    radio.setDataRate( RF24_2MBPS );

    radio.enableAckPayload();

    int powerLeveLBeginning = radio.getPALevel();
    Serial.println("Starting PA Level");
    Serial.println(powerLeveLBeginning);

    radio.enableAckPayload();
    radio.setPALevel( RF24_PA_MIN);
    int powerLevel = radio.getPALevel();
    Serial.println("After Setting PA Level");
    Serial.println(powerLevel);

    if(powerLeveLBeginning != powerLevel && powerLeveLBeginning != 0 && powerLevel == 0) {
        radioConnected = true;
        Serial.println("radio was detected");
    } else {
        Serial.println("radio is not detected");
    }

    // radio.setRetries(1,1); // delay, count
    //                                    
    // 5 gives a 1500 µsec delay which is needed for a 32 byte ackPayload
    radio.openWritingPipe(slaveAddress);
}

//=============

void loop() {

    currentMillis = millis();

    changeChannel();
    masterDisplay();

    if(radioConnected) {
        if (currentMillis - prevMillis >= txIntervalMillis) {
            send();
            prevMillis = millis();
        }
        showData();
    }
}

void masterDisplay() {
    displayRadioStatus();
    displayChannel();
    displayAction();
    display.display();
}

void changeChannel() {

    if (currentMillis - changeChannelPrevMillis >= changeChannelInterval) {
        int up_input = digitalRead(CHANNEL_UP);
        int down_input = digitalRead(CHANNEL_DOWN);

        if(!(up_input == 1 && down_input == 1) && !(up_input == 0 && down_input == 0)) {

            if(up_input) {
                if(currentChannel < maxChannels) {
                    currentChannel++;
                } else {
                    currentChannel = 0;
                }
            } 

            if(down_input) {
                if(currentChannel > 0) {
                    currentChannel--;
                } else {
                    currentChannel = maxChannels;
                } 
            }
        }
        changeChannelPrevMillis = millis();
    }
}

//================

void send() {

    int up_input = digitalRead(UP_PIN);
    int down_input = digitalRead(DOWN_PIN);

    if(!(up_input == 1 && down_input == 1) && !(up_input == 0 && down_input == 0)) {
        doNothing = false;
        if(up_input == 1) {
            sentUp = true;
        }

        if(down_input == 1) {
            sentUp = false;
        } 
    } else {
        doNothing = true;
    }

    sendData();
 }

 void settingPipe() {
    String temp;
    if(currentChannel >= 10) {
        temp = "RxA"+ String(currentChannel);
    } else {
        temp = "RxA0"+ String(currentChannel);
    }
    temp.getBytes(slaveAddress, 7);
    radio.openWritingPipe(slaveAddress);
 }


//=================

void sendData() {
             
    settingPipe();
    char command [20] = "Command";
    bool rslt;

    if(doNothing == true) {
        strcat((char*)command, " NOTHING");
        rslt = radio.write(&command, sizeof(command));
        Serial.print(command );
    } else {
        if(sentUp) {
            strcat((char*)command, " UP");
            rslt = radio.write( &command , sizeof(command));
            Serial.print(command );
        } else {
            strcat((char*)command, " DOWN");
            rslt = radio.write( &command, sizeof(command));
            Serial.print(command);
        }
    }

    // Always use sizeof() as it gives the size as the number of bytes.
    // For example if dataToSend was an int sizeof() would correctly return 2
    if (rslt) {
        if ( radio.isAckPayloadAvailable() ) {
            txFailed = false;
            radio.read(&ackData, sizeof(ackData));
            newData = true;
        } else {
            txFailed = false;
            Serial.println("  Acknowledge but no data ");
        }
    } else {
        txFailed = true;
        Serial.println("  Tx failed");
    }
}

void showData() {
    if (newData == true) {
        Serial.print("  Acknowledge data ");
        Serial.print(ackData[0]);
        Serial.print(", ");
        Serial.println(ackData[1]);
        Serial.println();
        newData = false;
    }
}

//================

void updateMessage() {
    // so you can see that new data is being sent
    txNum += 1;
    if (sentUp) {
        txNum = '0';
        sentUp = false;
    } else {
        txNum = 'P';
        sentUp = true;
    }

    // dataToSend[8] = txNum;
}

void displayRadioStatus(void) {

    String text = "Disconnected";
    // Not all the characters will fit on the display. This is normal.
    // Library will draw what it can and the rest will be clipped.
    if(radioConnected) {
    text = "Connected     RX: ";
    }

    print(text, 0, 0);

    String connected = String(!txFailed);

    overridePrint(connected);
}

void displayChannel(void) {
    print("Channel ", 0, 20);
    String temp = String((char *)slaveAddress);
    overridePrint(String(currentChannel) + " " + temp + "   ");
}

void displayAction(void) {
    String informationalText = "    ";

    print("Action ", 0, 40);  
    display.setTextColor(WHITE, BLACK);
    
    if(!doNothing) {
        if(sentUp) {
            informationalText = "UP  ";
        } else {
            informationalText = "DOWN";
        }
    }

    overridePrint(informationalText);
}

// void println(String text, int x, int y) {
//     setBasicTextSettings();
//     display.println(text);
// }

void print(String text, int x, int y) {
    setBasicTextSettings(x, y);
    display.print(text);
}

void overridePrint(String text) {
    display.setTextColor(WHITE, BLACK);
    display.print(text);
}

void setBasicTextSettings(int x, int y) {
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(WHITE); // Draw white text
    display.setCursor(x, y);     // Start at top-left corner
    display.cp437(true);         // Use full 256 char 'Code Page 437' font
}
