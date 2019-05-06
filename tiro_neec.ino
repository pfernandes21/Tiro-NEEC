#include <Wire.h>
#include <Time.h>

#define MIN 1
#define MAX 8
#define DURATION 30
#define SCORE 1

const int other_add = 4;

long off_time[4] = {0}, off_start[4] = {0}, start_time;

int i;

int led[4] = {0}, lux[4] = {0};

char pontos = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  randomSeed(analogRead(5));
  
  pinMode(2, OUTPUT);
  pinMode(0, INPUT);

  pinMode(3, OUTPUT);
  pinMode(1, INPUT);

  pinMode(4, OUTPUT);
  pinMode(2, INPUT);

  pinMode(5, OUTPUT);
  pinMode(3, INPUT);
  
  i+= random(1,3);
  
  for(i=0;i<4;i++)
  {
    led[i] = 0;

    //tempo de começo da espera
    off_start[i] = millis();
      
    //escolha do tempo de espera
    off_time[i] = random(MIN, MAX) * 1000;
  }
  //tempo de começo do programa
  start_time = millis();

}

void loop() {

  //se o programa chegou ao fim
  if(millis() - start_time >= DURATION * 1000)
  {
    //desliga os leds
    for(i=0;i<4;i++)
      analogWrite(i + 2, 0);
    delay(100);
    for(i=0;i<4;i++)
      analogWrite(i + 2, 255);
    delay(100);
    for(i=0;i<4;i++)
      analogWrite(i + 2, 0);
    delay(100);
    for(i=0;i<4;i++)
      analogWrite(i + 2, 255);
    delay(100);
    for(i=0;i<4;i++)
      analogWrite(i + 2, 0);
    delay(100);
    for(i=0;i<4;i++)
      analogWrite(i + 2, 255);
    delay(100);
    for(i=0;i<4;i++)
      analogWrite(i + 2, 0);
    //estado de espera pelo reinicio do programa
    while(1);
  }

  //check se o tempo de espera dos leds acabou, ligam-se
  for (i = 0; i < 4; i++)
  {
    if (led[i] == 0 && millis() - off_start[i] >= off_time[i]) {
      analogWrite(i + 2, 255);
      led[i] = 1;
    }
  }

  //leitura do sensor
  for (i = 0; i < 4; i++)
  {
    lux[i] = analogRead(i); // leitura do valor de resistencia
  }

  
  for (i = 0; i < 4; i++)
  {
    //check se o alvo foi atingido
    if (lux[i] > 950 && led[i] == 1) {
      //desligar o led
      analogWrite(i + 2, 0);
      led[i] = 0;

      //tempo de começo da espera
      off_start[i] = millis();
      
      //escolha do tempo de espera
      off_time[i] = random(MIN, MAX) * 1000;
      
      pontos += SCORE;
      Serial.println((int)pontos);
      Wire.beginTransmission(other_add);
      Wire.write(pontos);
      Wire.endTransmission();
    }
  }
}
