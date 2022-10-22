//Programa: Varredura de Superfície
//Autor: Leonardo Gabriel Cardoso de Moraes
//Curso: Engenharia da Computação
//Intituição: UFPA

//Carrega a biblioteca do sensor ultrassonico
#include <Ultrasonic.h>

//Define os pinos para o trigger e echo
#define pino_trigger 4
#define pino_echo 5

//Define o pino para o botão
#define botao 2

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrasonic(pino_trigger, pino_echo);

//Variáveis de controle
int i;
float x,y,z;

//Marcador de início de mensagem
String valString = "<";

void setup()
{
  Serial.begin(9600);
  pinMode(botao, INPUT_PULLUP);
}

void loop()
{
  if (!digitalRead(botao)) {
    //Criar laços para incrementar x e y análogo a uma onda digital
    //Le as informacoes do sensor, em cm e pol
    float cmMsec, inMsec;
    long microsec = ultrasonic.timing();
    cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
    inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
    //Concatena as informações e exibe no serial monitor
    i++;
    valString.concat(cmMsec);
    valString.concat(",");
    valString.concat(inMsec);
    valString.concat(",");
    valString.concat(i);
    valString.concat(">"); //Marcador de fim de mensagem

    Serial.print(valString);

    valString = "<";
    delay(1000);
  }
}
