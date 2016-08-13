/*
 * 
 * MOTOR 1: 
 * 1N1 -> 11
 * 1N2 -> 10
 * 1N3 -> 9
 * 1N4 -> 8
 * 
 * MOTOR 2:
 * 1N1 -> 40
 * 1N2 -> 41
 * 1N3 -> 42
 * 1N4 -> 43
 * reverse
 * 
 * ULTRASONIDOS:
 * TRIG -> 6
 * Echo -> 5
 * 
 * ZUMBADOR:
 * Sen -> 7
 * 
 * SERVO:
 * Sen -> 4 -> amarillo
 * 
 */
#include <Servo.h>

#define DIAMETRO_RUEDA 4.1
#define retardo 5
double distanciaVuelta;
int motor1[] = {8, 9, 10, 11};
int motor2[] = {40, 41, 42, 43};
int trig = 6;
int echo = 5;
int zum = 7;
Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(4);

  //circunferencia de la rueda
  distanciaVuelta = PI * DIAMETRO_RUEDA;

  //motor1
  pinMode(motor1[3], OUTPUT);
  pinMode(motor1[2], OUTPUT);
  pinMode(motor1[1], OUTPUT);
  pinMode(motor1[0], OUTPUT);
    //motor1
  pinMode(motor2[3], OUTPUT);
  pinMode(motor2[2], OUTPUT);
  pinMode(motor2[1], OUTPUT);
  pinMode(motor2[0], OUTPUT);
  //zumbador
  pinMode(zum, OUTPUT);
  //ultrasonidos
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  encender();
  
}

void loop() {
  correr();
}

// principal ///////////////////////////////////////////////////
void encender(){
  mirarFrente();
}
void correr(){
  Serial.println(getDistancia());
  if(getDistancia()<10){
    apagarMotor(motor1);
    apagarMotor(motor2);
    mirarIzquierda();
    if(getDistancia()<10){
      mirarDerecha();
      if(getDistancia()<10){
        mirarFrente();
        mediaVuelta();
      }else{
        girarDerecha();
      }
    }else{
      girarIzquierda();
    }
  }else{
    avanzar(5);
  }
  mirarFrente();
}
// control motores /////////////////////////////////////////////
void avanzarVuelta(){
  avanzar(distanciaVuelta);
}

void avanzarLibre(){
  if(getDistancia()>10){
    avanzar(1);
  }else{
    apagarMotor(motor1);
    apagarMotor(motor2);
  }
  
}

void avanzar(int x){
  int pasos = 512*x/distanciaVuelta;
  int n = 0;
  while (n<pasos){   // Girohacia la izquierda en grados 
       pasoIzquierda(motor1);
       pasoDerecha(motor2);
       n++;
  }
}

void mediaVuelta(){
  Serial.println("media vuelta");
}

void girarDerecha(){
  /*int x = 0;
  while(x<100){
    x++;
    digitalWrite(7, HIGH); 
  delayMicroseconds(1700);
  digitalWrite(7, LOW); 
  delayMicroseconds(1700);
    }
    x=0;
    while(x<100){
    x++;
    digitalWrite(7, HIGH); 
  delayMicroseconds(1700);
  digitalWrite(7, LOW); 
  delayMicroseconds(1700);
    }*/
    
}
void girarIzquierda(){
  /*int x = 0;  
  while(x<100){
    x++;
    digitalWrite(7, HIGH); 
  delayMicroseconds(1700);
  digitalWrite(7, LOW); 
  delayMicroseconds(1700);
    }*/
    
}

void apagarMotor(int motor[]) {
 digitalWrite(motor[3], LOW); 
 digitalWrite(motor[2], LOW);  
 digitalWrite(motor[1], LOW);  
 digitalWrite(motor[0], LOW);  
}

void pasoDerecha(int motor[]){
 digitalWrite(motor[3], LOW); 
 digitalWrite(motor[2], LOW);  
 digitalWrite(motor[1], HIGH);  
 digitalWrite(motor[0], HIGH);  
   delay(retardo); 
 digitalWrite(motor[3], LOW); 
 digitalWrite(motor[2], HIGH);  
 digitalWrite(motor[1], HIGH);  
 digitalWrite(motor[0], LOW);  
   delay(retardo); 
 digitalWrite(motor[3], HIGH); 
 digitalWrite(motor[2], HIGH);  
 digitalWrite(motor[1], LOW);  
 digitalWrite(motor[0], LOW);  
  delay(retardo); 
 digitalWrite(motor[3], HIGH); 
 digitalWrite(motor[2], LOW);  
 digitalWrite(motor[1], LOW);  
 digitalWrite(motor[0], HIGH);  
  delay(retardo);  
}

void pasoIzquierda(int motor[]) {
 digitalWrite(motor[3], HIGH); 
 digitalWrite(motor[2], HIGH);  
 digitalWrite(motor[1], LOW);  
 digitalWrite(motor[0], LOW);  
  delay(retardo); 
 digitalWrite(motor[3], LOW); 
 digitalWrite(motor[2], HIGH);  
 digitalWrite(motor[1], HIGH);  
 digitalWrite(motor[0], LOW);  
  delay(retardo); 
 digitalWrite(motor[3], LOW); 
 digitalWrite(motor[2], LOW);  
 digitalWrite(motor[1], HIGH);  
 digitalWrite(motor[0], HIGH);  
  delay(retardo); 
 digitalWrite(motor[3], HIGH); 
 digitalWrite(motor[2], LOW);  
 digitalWrite(motor[1], LOW);  
 digitalWrite(motor[0], HIGH);  
  delay(retardo); 
}
// control servo ///////////////////////////////////////////////
void mirarFrente() {
  servo.write(90);
  delay(2000);
}
void mirarIzquierda() {
  servo.write(180);
  delay(2000);
}
void mirarDerecha() {
  servo.write(0);
  delay(2000);
}

// ultrasonidos ///////////////////////////////////////////////

double getDistancia(){
  double distancia, duracion;
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  
  duracion = pulseIn(echo, HIGH);
  distancia = duracion/58;
  return distancia;
}

