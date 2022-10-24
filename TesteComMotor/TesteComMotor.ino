//Programa: Varredura de Superfície
//Autor: Leonardo Gabriel Cardoso de Moraes
//Curso: Engenharia da Computação
//Intituição: UFPA

int SonarTrigger = 2;
int SonarEcho = 3;

int distancia = 0;
int tempo = 0;

String x = "x";
String y = "y";
int xi = 0;
int yi = 0;
int continua = 0;

#define botao 13

#define motorXf 5
#define motorXt 4
#define motorXa 6

#define motorYf 10
#define motorYt 8
#define MotorYa 9

void giroHorario(String motor) {
  if (motor == "x" ) {
    digitalWrite(motorXa, HIGH);
    digitalWrite(motorXf, HIGH);
    digitalWrite(motorXt, LOW);
  } else if (motor == "y") {
    digitalWrite(MotorYa, HIGH);
    digitalWrite(motorYf, HIGH);
    digitalWrite(motorYt, LOW);
  }
}

void giroAntiHorario(String motor) {
  if (motor == "x" ) {
    digitalWrite(motorXa, HIGH);
    digitalWrite(motorXf, LOW);
    digitalWrite(motorXt, HIGH);
  } else if (motor == "y") {
    digitalWrite(MotorYa, HIGH);
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

int cm() {
  //código sensor
  digitalWrite(SonarTrigger, LOW); // Estabiliza sensor
  delayMicroseconds(2);

  digitalWrite(SonarTrigger, HIGH); // Envia um pulso para ativar
  delayMicroseconds(10);
  digitalWrite(SonarTrigger, LOW);

  tempo = pulseIn(SonarEcho, HIGH); // Função que recebe um pulso e retorna o valor em tempo da duração deste pulsi, em microsegundos
  distancia = tempo / 58.2; // Distancia = tempo * velocidade do som / 2 (Velocidade do som é 340 m/s)
  return distancia;
}

void setup()
{
  pinMode(SonarTrigger, OUTPUT);
  pinMode(SonarEcho, INPUT);
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
  if (!digitalRead(botao)) {
    continua = 0;
    delay(2000);
    Serial.println("Sistema iniciado");
    while (continua == 0) {
      for (int j = 1; j <= 6; j++) {
        yi = j;
        for (int i = 1; i <= 4; i++) {
          xi = i;
          if (i == 4) {
            for (int i = 4; i >= 1; i--) {
              xi = i;
              giroAntiHorario(x);
              delay(1000);
              desligaMotor(x);
              delay(100);
              Serial.print("x = ");
              Serial.print(xi);
              Serial.print(" y = ");
              Serial.println(yi);
              Serial.print("Distancia medida: ");
              Serial.print(cm());
            }
          }
          else {
            giroHorario(x);
            delay(1000);
            desligaMotor(x);
            delay(100);
            Serial.print("x = ");
            Serial.print(xi);
            Serial.print(" y = ");
            Serial.println(yi);
            Serial.print("Distancia medida: ");
            Serial.print(cm());
          }
        }
        giroHorario(y);
        delay(1000);
        desligaMotor(y);
        delay(100);
        Serial.print("x = ");
        Serial.print(xi);
        Serial.print(" y = ");
        Serial.println(yi);
        Serial.print("Distancia medida: ");
        Serial.print(cm());
      }

      //if (cm() < 100) {
      //  Serial.println("Desviar do bloqueio");
      //} else {
      //  Serial.println("Pode continuar");
      //}
      //Serial.print("Distancia medida: ");
      //Serial.print(cm());
      //Serial.println("cm");
      //if (!digitalRead(botao)) {
      //  continua = 1;
      //}
    }
  }
}
