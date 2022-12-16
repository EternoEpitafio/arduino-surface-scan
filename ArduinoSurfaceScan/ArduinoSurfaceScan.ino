//Programa: Varredura de Superfície
//Autor: Leonardo Gabriel Cardoso de Moraes
//Curso: Engenharia da Computação
//Intituição: UFPA

//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>

//Define os pinos para o trigger e echo
#define pino_trigger 2
#define pino_echo 3

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);

//Define o pino para o botão
#define botao 13

//int distancia = 0;
//int tempo = 0;

//Variáveis de controle
String x = "x";
String y = "y";
int xi = 0;
int yi = 0;
int continua = 0;
int vel = 128;

//Marcador de início de mensagem
String valString = "<";

//Define os pinos dos motores
#define motorXf 5 //motor x "frente"
#define motorXt 4 //motor x "trás"
#define motorXa 6 //motor x "ativa/velocidade"

#define motorYf 10 //motor y "frente"
#define motorYt 8 //motor y "trás"
#define MotorYa 9 //motor y "ativa/velocidade"

void giroHorario(String motor) {
  if (motor == "x" ) {
    analogWrite(motorXa, vel);
    digitalWrite(motorXf, HIGH);
    digitalWrite(motorXt, LOW);
  } else if (motor == "y") {
    analogWrite(MotorYa, vel);
    digitalWrite(motorYf, HIGH);
    digitalWrite(motorYt, LOW);
  }
}

void giroAntiHorario(String motor) {
  if (motor == "x" ) {
    analogWrite(motorXa, vel);
    digitalWrite(motorXf, LOW);
    digitalWrite(motorXt, HIGH);
  } else if (motor == "y") {
    analogWrite(MotorYa, vel);
    digitalWrite(motorYf, LOW);
    digitalWrite(motorYt, HIGH);
  }
}

void desligaMotor(String motor) {
  if (motor == "x" ) {
    digitalWrite(motorXa, LOW);
    digitalWrite(motorXf, LOW);
    digitalWrite(motorXt, LOW);
  } else if (motor == "y") {
    digitalWrite(MotorYa, LOW);
    digitalWrite(motorYf, LOW);
    digitalWrite(motorYt, LOW);
  }
}

float cm() {
  //Le as informacoes do sensor, em cm
  float cmMsec;
  long microsec = ultrasonic.timing();
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  return cmMsec;
}

void setup()
{
  pinMode(botao, INPUT_PULLUP);
  Serial.begin(9600);

  pinMode(motorXt, OUTPUT);  // para trás
  pinMode(motorXf, OUTPUT);  // para frente
  pinMode(motorXa, OUTPUT);  // aciona o motor A

  pinMode(motorYt, OUTPUT);  // para trás
  pinMode(motorYf, OUTPUT);  // para frente
  pinMode(MotorYa, OUTPUT);  // aciona o motor B
}

void loop()
{
  //Inicia a varredura ao pressionar o botão
  //if (!digitalRead(botao)) {
  continua = 0;
  delay(5000);
  while (continua == 0) {
    for (int j = 1; j <= 10; j++) {
      giroHorario(x);
      for (int i = 1; i <= 30; i++) {
        xi = i;
        yi = j;
        //Concatena as informações e exibe no serial monitor
        valString.concat(xi);
        valString.concat(",");
        valString.concat(yi);
        valString.concat(",");
        valString.concat(cm());
        valString.concat(">"); //Marcador de fim de mensagem
        Serial.print(valString); //Imprime as coordenadas
        valString = "<";
        delay(100);
      }
      desligaMotor(x);
      delay(200);
      giroHorario(y);
      delay(100);
      desligaMotor(y);
      delay(200);
      j = j + 1;
      yi = j;
      giroAntiHorario(x);
      for (int i = 30; i >= 1; i--) {
        xi = i;
        yi = j;
        //Concatena as informações e exibe no serial monitor
        valString.concat(xi);
        valString.concat(",");
        valString.concat(yi);
        valString.concat(",");
        valString.concat(cm());
        valString.concat(">"); //Marcador de fim de mensagem
        Serial.print(valString); //Imprime as coordenadas
        delay(100);
      }
      desligaMotor(x);
      delay(200);
      giroHorario(y);
      delay(100);
      desligaMotor(y);
      delay(200);
    }
    continua = 1;
  }
  //}
}
