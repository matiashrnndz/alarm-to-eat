#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal.h>

#define DEBUGMODE true
#define FREQUENCY 5

#define LEDGREEN 2
#define LEDRED 3
#define BUTTON 4
#define SPEAKER 5
#define VO 6
#define RS 7
#define E 8
#define D4 9
#define D5 10
#define D6 11
#define D7 12

DS3231  rtc(SDA, SCL);
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

void setup()
{
    Serial.begin(9600);
    rtc.begin();
    Wire.begin();
    
    lcd.begin(16, 2);
    analogWrite(VO, 0);
    
    pinMode(LEDGREEN, OUTPUT);
    pinMode(LEDRED, OUTPUT);
    pinMode(SPEAKER, OUTPUT);
    pinMode(BUTTON, INPUT);
    
    resetTimer();
};

void loop()
{ 
    printCurrentTime();
    
    if(isAlarm(0, 0, 10))
    {
        if(DEBUGMODE)
        {
            printTextToConsole(" GREEN LED : ON ");
            printTextToConsole(" RED LED : OFF ");
            printTextToConsole(" SPEAKER : ON ");
        }

        turnOnLed(LEDGREEN);
        turnOffLed(LEDRED);
        turnOnSpeaker(SPEAKER, FREQUENCY);
    };
  
    if(isAlarm(0, 0, 20))
    {
        if(DEBUGMODE)
        {
            printTextToConsole(" GREEN LED : OFF ");
            printTextToConsole(" RED LED : ON ");
            printTextToConsole(" SPEAKER : ON ");
        }
        
        turnOffLed(LEDGREEN);
        turnOnLed(LEDRED);
        turnOnSpeaker(SPEAKER, FREQUENCY);
    };
  
    if(buttonIsPressed())
    {
        if(DEBUGMODE)
        {
            printTextToConsole(" GREEN LED : OFF ");
            printTextToConsole(" RED LED : OFF ");
            printTextToConsole(" SPEAKER : ON ");
            printTextToConsole(" TIMER : RESET ");
        }

        resetTimer();
        
        turnOffLed(LEDGREEN);
        turnOffLed(LEDRED);
        turnOnSpeaker(SPEAKER, FREQUENCY);
    };
    
    delayInSeconds(1);

    turnOffSpeaker(SPEAKER);
};

bool isAlarm(int h, int m, int s)
{
    return rtc.getTime().hour == h &&
    rtc.getTime().min == m &&
    rtc.getTime().sec == s;
};

bool buttonIsPressed()
{
    return digitalRead(BUTTON) == HIGH;
};

void turnOnLed(int LED)
{
    digitalWrite(LED, HIGH);
};

void turnOffLed(int LED)
{
    digitalWrite(LED, LOW);
};

void turnOnSpeaker(int SPEAKR, int FREQ)
{
    tone(SPEAKR, FREQ);
};

void turnOffSpeaker(int SPEAKR)
{
    noTone(SPEAKR);
};

void resetTimer()
{
    lcd.clear();
    rtc.setTime(0, 0, 0);  
};

void printTextToConsole(String text)
{
    Serial.println(text); 
};

void printTextToLCD(String text)
{
    lcd.setCursor(3, 0);
    lcd.print(text);
};
void printCurrentTime()
{
    printTextToConsole(rtc.getTimeStr());

    lcd.setCursor(1, 1);
    lcd.print(rtc.getTimeStr());
};

void delayInSeconds(int seconds)
{
    delay(seconds*1000);
};
