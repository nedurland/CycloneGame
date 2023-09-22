#include &lt;FastLED.h&gt;
#include &lt;LiquidCrystal.h&gt;
CRGB leds[30]; // leds array
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
bool WON = true ;
int Moving_Target = 29; // starts at led #29
bool Playing = false; // false
bool Game_Over = true; // true
int Level = 0;
int Button = 0; // high or low
int miss_count[10]; // array of misses

void setup()
{
  FastLED.addLeds&lt;NEOPIXEL, 7&gt;(leds, 30); //LED CONNECTED TO PIN 7 AND
THERE ARE 30 OF THEM.
  FastLED.setBrightness(30); // brightness for led
  pinMode(9, INPUT); // PUSH BUTTON IS CONNECTED TO PIN 9
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  lcd.clear();
  lcd.begin(16, 2); // 16 COLUMNS, 2 ROWS.
  for (int i = 0; i &lt; 10; i++)
  {
    miss_count[i] = 0;
  }
}

//LOST LEVEL ANIMATION
void LoseAnimation()
{
  fill_solid(leds, 30, CRGB::Green); // if lost all lights flash red
  FastLED.show();
  delay(100); // how fast leds blink when lost
  fill_solid(leds, 30, CRGB::Black);
  FastLED.show();
  delay(100);
}

// WINNING LED ANIMATION FUNCTION
void WinAnimation()
{
  fill_solid(leds, 30, CRGB::Red);
  FastLED.show();
  delay(100); // how fast leds blink when lost
  fill_solid(leds, 30, CRGB::White);
  FastLED.show();
  delay(100);
}
// INTRO animation function
void intro()
{
  fill_solid(leds, 30, CRGB::Blue); // if lost all lights flash red
  FastLED.show();
  delay(400); // how fast leds blink when lost
  fill_solid(leds, 30, CRGB::Yellow);
  FastLED.show();
  delay(400);
  fill_solid(leds, 30, CRGB::Red); // if lost all lights flash red
  FastLED.show();
  delay(400); // how fast leds blink when lost
  fill_solid(leds, 30, CRGB::White);
  FastLED.show();
  delay(400);
}

//Levels
const int NONE = 0;
const int Level_1 = 1;
const int Level_2 = 2;
const int Level_3 = 3;
const int Level_4 = 4;
const int Level_5 = 5;
const int Level_6 = 6;
const int Level_7 = 7;
const int Level_8 = 8;
const int Level_9 = 9;
const int Level_10 = 10;

int SPEED(int Levels) // Returns time delay for led movement base on Level
{

  int speed = 0;
  switch (Levels)
  {
    case Level_1:
      speed = 150;
      break;
    case Level_2:
      speed = 120;
      break;
    case Level_3:
      speed = 100;
      break;
    case Level_4:
      speed = 80;
      break;
    case Level_5:
      speed = 70;
      break;
    case Level_6:
      speed = 50;
      break;
    case Level_7:
      speed = 40;
      break;
    case Level_8:
      speed = 35;
      break;
    case Level_9:
      speed = 30;
      break;
    case Level_10:
      speed = 20;
  }
  return speed;// speed amount gets returned
}

// level increases whenever you win a level.
void Increase_Level()
{
  if (Level != Level_10 &amp;&amp; WON == true)
  {
    Level++;

  }
}

// turn on function intro led
void turnon()
{
  if (Level == 0)
  {
    intro();
  }
}
// function for printing what level you are on
void printLevel(int level)
{
  lcd.setCursor(0, 0);
  lcd.print(&quot;You are on level &quot;);
  lcd.setCursor(17, 0);
  lcd.print(level);
}
// function prints how many misses
void printMisses()
{
  lcd.setCursor(0, 2);
  lcd.print(&quot;You missed &quot;);
  lcd.setCursor(13, 2);
  lcd.print(&quot; Times &quot;);
  lcd.setCursor(11, 2);
  int total = 0;
  for (int i = 0; i &lt; 10; i++)
  {
    total = total + miss_count[i]; // equation for finding misses
  }
  lcd.print(total); // prints total of misses on lcd
}

// the game
void loop()
{
  if (Playing == true)
  {
    printLevel(Level); // prints what level you are on, on lcd

    printMisses(); // prints misses on lcd.
    
    // set led to move
    for (int i = 0; i &lt; 30; i++) // loop for setting all thirty leds to one color
    {
      leds[i] = CRGB::Black; //Turns off all the leds
    }
    leds[29] = CRGB::Blue; //Sets center led color to blue
    leds[Moving_Target] = CRGB::Green; //Sets moving led color to red
    FastLED.show();
    Moving_Target++; // moves through the LED&#39;s
    if (Moving_Target == 30) // if moving target hits led #30 when it is cycling it restarts
back to 0
    {
      Moving_Target = 0; // 
    }
    delay(SPEED(Level)); // Set speed depending on level you are on
    Button = digitalRead(9); // button is on pin 9
    if (Button == HIGH) // if button is pushed
    {
      Playing = false;
      Game_Over = true;
    }
  }

  Button = digitalRead(9); // for when button is pushed
  if (Button == HIGH) // if button has been pressed
  {
    Playing = false; //moving_target has stopped on the winning led
    for (int i = 0; i &lt; 30; i++)
    {
      //inside this loop the unlit leds are turned off
      leds [i] = CRGB::Black;
    }
    leds[29] = CRGB::Blue; // center led is blue
    leds[Moving_Target] = CRGB::Green;  // led you land on is red
    FastLED.show();
    /////////////////////////////////////////////////////////////////
    if (Game_Over == true)
    {
      int landed;// defining where moving target has landed when push button is pressed
      landed = (29 - Moving_Target); //equation for finding if center led is at 0
      if (landed == 0 ) // won if landed at 0.
      {

        turnon(); // turn on intro when first playing
        WON = true;
        if (Level != Level_10 &amp;&amp; Level != 0)
        {
          for (int i = 0; i &lt; 7; i++)
          {
            WinAnimation(); // win animation loops less than 7 times
          }
        }
        else if (Level == Level_10) // level ten finished and restarts game
        {
          for (int i = 0; i &lt; 2; i++)
          {
            intro();
            
          }
          lcd.clear();
          for (int i = 0; i &lt; 10; i++)
          {
            miss_count[i] = 0;
          }
          Level = 0;
        }
        Increase_Level();
        WON = true;
      }
      else
      {
        delay(700);  // how long led you land on shows
        for (int i = 0; i &lt; 4; i++) // loop for lose animation
        {
          LoseAnimation();
        }
        ++miss_count[Level - 1];
      }
      Game_Over = true;
    }
    Moving_Target = 0;
    delay(300);
    Button = digitalRead(9);
    if (Button == LOW)
    {
      Playing = true;
    }
  }
  return 0;

}
