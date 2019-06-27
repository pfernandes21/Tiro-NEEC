#include <Wire.h>

const int segA = 12;
const int segB = 8;
const int segC = 5;
const int segD = 3;
const int segE = 2;
const int segF = 11;
const int segG = 6;
const int segPt = 4;
const int d1 = 13;
const int d2 = 10;
const int d3 = 9;
const int d4 = 7;
const int delayTime = 900;
const int own_address = 4;

int val;
char c;

void allLow() {
  digitalWrite(segA, LOW); // A
  digitalWrite(segB, LOW); // B
  digitalWrite(segC, LOW); // C
  digitalWrite(segD, LOW); // D
  digitalWrite(segE, LOW); // E
  digitalWrite(segF, LOW); // F
  digitalWrite(segG, LOW); // G
  digitalWrite(segPt, LOW); //point
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
}

void allHigh() {
  digitalWrite(segA, HIGH); // A
  digitalWrite(segB, HIGH); // B
  digitalWrite(segC, HIGH); // C
  digitalWrite(segD, HIGH); // D
  digitalWrite(segE, HIGH); // E
  digitalWrite(segF, HIGH); // F
  digitalWrite(segG, HIGH); // G
  digitalWrite(segPt, HIGH); //point
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
}

void one() {
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, LOW);

}

void two() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, LOW);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}

void three() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}

void four() {
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}

void five() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}

void six() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}

void seven() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, LOW);
}

void eight() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}

void nine() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}

void zero() {
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, LOW);
}

void selectDigit(int d)
{
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);

  switch (d)
  {
    case 1:
      digitalWrite(d1, LOW);
      break;
    case 2:
      digitalWrite(d2, LOW);
      break;
    case 3:
      digitalWrite(d3, LOW);
      break;
    default:
      digitalWrite(d4, LOW);
      break;
  }
}

void sendDigit(int x)
{
  switch (x)
  {
    case 1:
      one();
      break;
    case 2:
      two();
      break;
    case 3:
      three();
      break;
    case 4:
      four();
      break;
    case 5:
      five();
      break;
    case 6:
      six();
      break;
    case 7:
      seven();
      break;
    case 8:
      eight();
      break;
    case 9:
      nine();
      break;
    default:
      zero();
      break;
  }
}

int cents(float x)
{
  float divided = x / 100.0;
  return (int)divided;
}

int tens(float x)
{
  float divided = (x - 100.0 * cents(x)) / 10.0;
  return (int)divided;
}

int ones(float x)
{
  float divided = x - (10.0 * tens(x)) - (100.0 * cents(x));
  return (int)divided;
}

void receiveEvent(int howMany)
{
  while (Wire.available() > 0)
  {
    c = Wire.read();
    Serial.write(c);
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin(own_address);
  Wire.onReceive(receiveEvent);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(0, INPUT);

  val = 0;
  c = 0;
}

void loop() {

  val = (int)c;

  selectDigit(1);
  sendDigit(cents(val));
  delayMicroseconds(delayTime);
  digitalWrite(d1, HIGH);

  selectDigit(2);
  sendDigit(tens(val));
  delayMicroseconds(delayTime);
  digitalWrite(d2, HIGH);

  selectDigit(3);
  sendDigit(ones(val));
  delayMicroseconds(delayTime);
  digitalWrite(d3, HIGH);

}

//remover botao
