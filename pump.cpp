#include <Arduino.h>
#include <initializer_list>

/*

Conversão de RGB 24 bits para CMYK:
The R,G,B values are divided by 255 to change the range from 0..255 to 0..1:
R' = R/255
G' = G/255
B' = B/255

The black key (K) color is calculated from the red (R'), green (G') and blue (B') colors:
K = 1-max(R', G', B')

The cyan color (C) is calculated from the red (R') and black (K) colors:
C = (1-R'-K) / (1-K)

The magenta color (M) is calculated from the green (G') and black (K) colors:
M = (1-G'-K) / (1-K)

The yellow color (Y) is calculated from the blue (B') and black (K) colors:
Y = (1-B'-K) / (1-K)

resultado é a porcentagem de cada cor
*/

String vol = "0";
float one_ml = 2.141;

void rgb2cmyk(uint8_t R, uint8_t G, uint8_t B){
  float Rfrac = (float)R/(float)255;
  float Gfrac = (float)G/(float)255;
  float Bfrac = (float)B/(float)255;

  float K = 1-max({Rfrac,Gfrac,Bfrac});

  float C = (1-Rfrac-K)/(1-K);
  float M = (1-Gfrac-K)/(1-K);
  float Y = (1-Bfrac-K)/(1-K);

  
  sleep(3);
  Serial.println("RGB");
  Serial.println(Rfrac);
  Serial.println(Gfrac);
  Serial.println(Bfrac);

  Serial.println("CMYK (%)");
  Serial.println(C);
  Serial.println(M);
  Serial.println(Y);
  Serial.println(K);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(22,OUTPUT);
  pinMode(21,OUTPUT);
  digitalWrite(21,LOW);
  digitalWrite(22,LOW);

  Serial.begin(9600);

  //Será necessário fazer casting dos valores RGB.
  rgb2cmyk(255,30,20);

  
}

void shake(){
  digitalWrite(21,HIGH);
  digitalWrite(22,LOW);
  sleep(1);
  digitalWrite(21,LOW);
  digitalWrite(22,HIGH);
  sleep(1);
  digitalWrite(22,LOW);
  

}

float toSleep(int ml){
    float secondsFor = ml/one_ml;
    return secondsFor;
}

void loop() {
  while (Serial.available()){
    vol = Serial.readString();
  }

  if (vol.toInt() != 0 ){
    //shake();
    Serial.println(vol.toInt());
    digitalWrite(21,HIGH);
    Serial.print("sleeping: ");
    Serial.println(toSleep(vol.toInt()));
    sleep(toSleep(vol.toInt()));
    digitalWrite(21,LOW);
    Serial.println(toSleep(vol.toInt()));
    
  }
  vol = "0";
}
