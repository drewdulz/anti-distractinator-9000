/*
  CustomCharacter.ino
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-9-18

  Grove - Serial LCD RGB Backlight demo.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Wire.h>
#include "rgb_lcd.h"
#include <Servo.h>
#include "pitches.h"


rgb_lcd lcd;

int fakemode = 0;

Servo myservo1;
Servo myservo2;

int pos = 90;

// notes in the melody:
int ohCanada[] = {
  NOTE_D5, NOTE_F5, NOTE_F5, NOTE_B4, 0, NOTE_C5, NOTE_D5, NOTE_E4, NOTE_F5, NOTE_G5, NOTE_C5
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int ohCandaDurations[] = {
  1, 2, 2, 1, 1, 2, 2, 2, 2, 2, 1
};

int sad[] = {
  NOTE_A7, NOTE_A7, NOTE_A7, NOTE_A7
};

int sadDurations[] = {
  1, 1, 1, 1
};

int happy[] = {
  NOTE_C1, NOTE_C1, NOTE_C1
};

int happyDurations[] = {
  1, 1, 1
};

int ttc[] = {
  NOTE_E4, NOTE_D4, NOTE_B4
};

int ttcDurations[] = {
  1, 1, 1
};


// make some custom characters:
byte heart[8] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
};

byte smiley[8] = {
    0b00000,
    0b00000,
    0b01010,
    0b00000,
    0b00000,
    0b10001,
    0b01110,
    0b00000
};

byte frownie[8] = {
    0b00000,
    0b00000,
    0b01010,
    0b00000,
    0b00000,
    0b00000,
    0b01110,
    0b10001
};

byte armsDown[8] = {
    0b00100,
    0b01010,
    0b00100,
    0b00100,
    0b01110,
    0b10101,
    0b00100,
    0b01010
};

byte armsUp[8] = {
    0b00100,
    0b01010,
    0b00100,
    0b10101,
    0b01110,
    0b00100,
    0b00100,
    0b01010
};

byte solid[8] = {
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111  
};

byte upperPupil[8] = {
    0b11111,
    0b00000,
    0b00000,
    0b00000,
    0b00100,
    0b01110,
    0b11111,
    0b11111    
};

byte lowerPupil[8] = {
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000,
    0b00000,
    0b00000,
    0b11111      
};

byte upperLine[8] = {
    0b11111,
    0b00000,
    0b00000,      
    0b00000,      
    0b00000,      
    0b00000,      
    0b00000,      
    0b00000
};


byte lowerLine[8] = {
    0b00000,
    0b00000,      
    0b00000,      
    0b00000,      
    0b00000,      
    0b00000,      
    0b00000,
    0b11111
};

byte slash[8] = {
    0b10000,
    0b01000,      
    0b01000,      
    0b00100,      
    0b00100,      
    0b00010,      
    0b00010,
    0b00001
};


byte upperRightCurve[8] = {
    0b10000,
    0b01000,      
    0b00100,      
    0b00100,      
    0b00010,      
    0b00010,      
    0b00001,
    0b00001
};
byte upperLeftCurve[8] = {
    0b00001,
    0b00010,      
    0b00100,      
    0b00100,      
    0b01000,      
    0b01000,      
    0b10000,
    0b10000  
};
byte lowerLeftCurve[8] = {
    0b10000,
    0b10000,
    0b01000,      
    0b01000,      
    0b00100,      
    0b00100,      
    0b00010,      
    0b00001
};
byte lowerRightCurve[8] = {
    0b00001,
    0b00001,
    0b00010,      
    0b00010,      
    0b00100,      
    0b00100,      
    0b01000,      
    0b10000
};


byte upperRightCurve_blink[8] = {
    0b10000,
    0b11000,      
    0b11100,      
    0b11100,      
    0b11110,      
    0b11110,      
    0b11111,
    0b11111
};
byte upperLeftCurve_blink[8] = {
    0b00001,
    0b00011,      
    0b00111,      
    0b00111,      
    0b01111,      
    0b01111,      
    0b11111,
    0b11111  
};
byte lowerLeftCurve_blink[8] = {
    0b11111,
    0b11111,
    0b01111,      
    0b01111,      
    0b00111,      
    0b00111,      
    0b00011,      
    0b00001
};
byte lowerRightCurve_blink[8] = {
    0b11111,
    0b11111,
    0b11110,      
    0b11110,      
    0b11100,      
    0b11100,      
    0b11000,      
    0b10000
};

int rating = 0;
int count = 0;

void setup() 
{
    // set up the lcd's number of columns and rows:
    lcd.begin(16, 2);

    // create a new character
    lcd.createChar(0, upperLeftCurve);
    lcd.createChar(1, upperRightCurve);
    lcd.createChar(2, lowerLeftCurve);
    lcd.createChar(3, lowerRightCurve);
    lcd.createChar(4, upperLine);
    lcd.createChar(5, lowerLine);
    lcd.createChar(6, upperPupil);
    lcd.createChar(7, lowerPupil);
    
    lcd.setCursor(0, 0);
    // Print a message to the lcd.
    //lcd.print("booting up!  ");
    //lcd.write(1);

  myservo1.attach(3);
  myservo2.attach(11);
  myservo1.write(pos);
  myservo2.write(pos);
      
    Serial.begin(19200);
    Serial.println("alive!");
}

void loop() 
{
  String message = "start";
  if (Serial.available())
  {
    message = Serial.readString();
    //lcd.print(message);
    //lcd.setCursor(0,0);
    rating = ( (message[0]-'0')*10 + message[1]-'0');  // crazy horrible string to int hack
    //lcd.print(rating);
    //delay(1000);
  }

  // bin our ratings
  if (rating != 0)
  {
    if (rating <= 9) rating = 10;
    if (rating != 76 && rating > 13) rating = 13;
  }
  
  if (fakemode == 1)
  {
    // now fake it up!!
    if (rating == 76) rating = 9;
    rating += 2;
    if (rating > 13) rating = 76;
  }

  switch(rating)  // the cases left after binning are 10, 11, 12, 13, 76
  {
    case 10:  // super sad, let's make it shades of red, and blink a lot
    case 11: // sad, but not that sad
    moveMouth(5);
    while (checkNext())
    {
      lcd.setRGB(255, 0, 0);  // red
      openeye(6);
      playTTCSound();  //delay(300);
      lcd.setRGB(255, 50, 100);  // less red
      closedeye(6);
      delay(100);
    }
    break;

    case 12:  // slightly happy
    case 13:  // super happy
    moveMouth(15);
    while (checkNext())
    {
      lcd.setRGB(255, 255, 0);  // bright green/yellow
      openeye(6);
      playHappySound(); //delay(700);
      lcd.setRGB(173, 255, 57);  // dimmer version of same?
      closedeye(6);
      delay(100);      
    }
    
    break;

    case 76:  // for 1776, american AF dog, go red/white/blue
    //moveMouth(15);
    fakemode = 1;  // time our way out of this one, rather than wait for next signal
    while (checkNext())
    {
      openeye(6);
      lcd.setRGB(255, 0, 0);  // red
      delay(150);
      moveMouth(10);
      lcd.setRGB(255, 255, 255);  // white
      delay(150);
      moveMouth(15);
      lcd.setRGB(0, 0, 255);  // blue
      delay(150);
      moveMouth(12);
    }
    playOhCanada();
    fakemode = 0;
    break;

    default:  // neutral expression mode
    moveMouth(10);
    while (checkNext())
    {
      lcd.setRGB(255, 255, 255);  // bright green/yellow
      openeye(6);
      delay(700);
      lcd.setRGB(128, 128, 128);  // dimmer version of same?
      closedeye(6);
      delay(100);
    }
    break;
    
  }

  delay(10); // just in case, prevent fast looping
  
}

boolean checkNext()
{
  if (fakemode == 1)
  {
    // fake timer:
    count++;
    if (count > 5)
    {
      count = 0;
      return 0;
    }
    else return 1;
  }
  else return !Serial.available();
}

void openeye(int pos)
{
    // then RESET the open eye stuff
    lcd.createChar(0, upperLeftCurve);
    lcd.createChar(1, upperRightCurve);
    lcd.createChar(2, lowerLeftCurve);
    lcd.createChar(3, lowerRightCurve);
    lcd.createChar(4, upperLine);

  // top
  lcd.setCursor(pos+0,0);
  lcd.write((unsigned char)0);
  lcd.write(4);
  lcd.write(6);
  lcd.write(4);
  lcd.write(1);

  // bottom
  lcd.setCursor(pos+0,1);
  lcd.write(2);
  lcd.write(5);
  lcd.write(7);
  lcd.write(5);
  lcd.write(3);

}

void closedeye(int pos)
{ // must redefine the character map
    /*
    lcd.createChar(0, upperLeftCurve_blink);
    lcd.createChar(1, upperRightCurve_blink);
    lcd.createChar(2, lowerLeftCurve_blink);
    lcd.createChar(3, lowerRightCurve_blink);
    lcd.createChar(4, solid);  
    */

      // top
  lcd.setCursor(pos+0,0);
  lcd.write((unsigned char)0);
  lcd.write(" ");
  lcd.write(" ");
  lcd.write(" ");
  lcd.write(1);

  // bottom
  lcd.setCursor(pos+0,1);
  lcd.write(2);
  lcd.write(4);
  lcd.write(4);
  lcd.write(4);
  lcd.write(3);

}


void moveMouth(int rating) {
  // HORRIBLE HACK: detach and reattach here, because the 
  // tone() function elsewhere has messed with the servo timers
  // this resets them, so servos work again, and we just do
  // it every damn time, just to be sure.
   myservo1.detach();
   myservo2.detach();
   myservo1.attach(3);  
   myservo2.attach(11);

  // clamp to 5 -> 15 range
  if (rating > 15) {
    rating = 15;
  } else if (rating < 5) {
    rating = 5;
  }
  Serial.println(rating);
  // convert rating to angle between 45 and 135
  int angle1 = ((rating - 5) * 9) + 45;

  // figure out which way to move servos
  int dir = 0;
  if (angle1 > pos) {
    dir = 1;
  } else {
    dir = -1;
  }

  // move servo to position
  for (; pos != angle1; pos += dir) {
    myservo1.write(pos);
    myservo2.write(-1 * pos + 180);
    delay(15); // MAYBE REMOVE THIS
    Serial.println(pos);
  }
}

void playOhCanada() {
  for (int thisNote = 0; thisNote < 11; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / ohCandaDurations[thisNote];
    tone(6, ohCanada[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(6);
  }
}

void playHappySound() {
  for (int thisNote = 0; thisNote < 4; thisNote++) {

    int noteDuration = 1000 / happyDurations[thisNote];
    tone(6, happy[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(6);
  }
}

void playSadSound() {
  for (int thisNote = 0; thisNote < 4; thisNote++) {

    int noteDuration = 1000 / sadDurations[thisNote];
    tone(6, sad[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(6);
  }
}

void playTTCSound() {
  for (int thisNote = 0; thisNote < 3; thisNote++) {

    int noteDuration = 1000 / ttcDurations[thisNote];
    tone(6, ttc[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(6);
  }
}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
