/*
 * https://github.com/chauhannaman98
 *
 * Source_Code.ino
 *
 * August 18, 2017 © GPL3+
 * Author : Naman Chauhan
    
********************************************************************************/

//RGB pin declarations
int redPin = 11;
int greenPin = 10;
int bluePin = 6;

//color sensor pin declarations
int S0 = 2;
int S1 = 3;
int S2 = 7;                 //color sensor pin S2 to Arduino pin 7
int S3 = 8;                 //color sensor pin S3 to Arduino pin 8
int outPin = 4;             //color sensor out to Arduino pin 4

unsigned int pulseWidth;

int rColorStrength;
int gColorStrength;
int bColorStrength;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);

  pinMode(S2,OUTPUT);
  pinMode(S3,OUTPUT);
  pinMode(outPin,INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}

void loop() {
  //reading red component of color
  //S2 and S3 should be set low
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  rColorStrength = pulseIn(outPin,LOW);

  //reading green component of color
  //S2 and S3 should be set high
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  gColorStrength = pulseIn(outPin,LOW);

  //reading blue component of color
  //S2 should be high and S3 to be high
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  bColorStrength = pulseIn(outPin,LOW);

  //color amplifying
  if (rColorStrength>gColorStrength && gColorStrength>bColorStrength) {
    rColorStrength = 1023;
    gColorStrength = gColorStrength/2;
    bColorStrength = 0;
  }

  if (rColorStrength>bColorStrength && bColorStrength>gColorStrength) {
    rColorStrength = 1023;
    bColorStrength = bColorStrength/2;
    gColorStrength = 0;
  }

  if (gColorStrength>rColorStrength && rColorStrength>bColorStrength) {
    gColorStrength = 1023;
    rColorStrength = rColorStrength/2;
    bColorStrength = 0;
  }

  if (gColorStrength>bColorStrength && bColorStrength>rColorStrength) {
    gColorStrength = 1023;
    bColorStrength = bColorStrength/2;
    rColorStrength = 0;
  }

  if (bColorStrength>rColorStrength && rColorStrength>gColorStrength) {
    bColorStrength = 1023;
    rColorStrength = rColorStrength/2;
    gColorStrength = 0;
  }

  if (bColorStrength>gColorStrength && gColorStrength>rColorStrength) {
    bColorStrength = 1023;
    gColorStrength = gColorStrength/2;
    rColorStrength = 0;
  }

  //Printing the color strengths
  Serial.print(rColorStrength);
  Serial.print("  , ");
  Serial.print(gColorStrength);
  Serial.print("  , ");
  Serial.println(bColorStrength);
  Serial.println("");

  //sending output to the LEDs
  analogWrite(redPin, rColorStrength);
  analogWrite(greenPin, gColorStrength);
  analogWrite(bluePin, bColorStrength);
  
  delay(150);
  
}
