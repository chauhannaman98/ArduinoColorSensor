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
int S2 = 7; //color sensor pin S2 to Arduino pin 7
int S3 = 8; //color sensor pin S3 to Arduino pin 8
int outPin = 4;   //color sensor out to Arduino pin 4

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
}

void loop() {
  //reading red component of color
  //S2 and S3 should be set low
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);

  pulseWidth = pulseIn(outPin,LOW);

  rColorStrength = pulseWidth/400. -1;
  rColorStrength = (255 - rColorStrength);


  //reading green component of color
  //S2 and S3 should be set high
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  pulseWidth = pulseIn(outPin,LOW);

  gColorStrength = pulseWidth/400. -1;
  gColorStrength = (255 - gColorStrength);


  //reading blue component of color
  //S2 should be high and S3 to be high
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);

  pulseWidth = pulseIn(outPin,LOW);

  bColorStrength = pulseWidth/400. -1;
  bColorStrength = (255 - bColorStrength);

  //Printing the color strengths
  Serial.print(rColorStrength);
  Serial.print("  , ");
  Serial.print(gColorStrength);
  Serial.print("  , ");
  Serial.println(bColorStrength);
  Serial.println("");

  if (rColorStrength>bColorStrength && rColorStrength>gColorStrength) {
    digitalWrite(redPin, HIGH);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, LOW);
  }

  if (gColorStrength>bColorStrength && gColorStrength>rColorStrength) {
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(greenPin, HIGH);
  }

  if (bColorStrength>rColorStrength && bColorStrength>gColorStrength) {
    digitalWrite(redPin, LOW);
    digitalWrite(bluePin, HIGH);
    digitalWrite(greenPin, LOW);
  }
  
  delay(250);
  
}
