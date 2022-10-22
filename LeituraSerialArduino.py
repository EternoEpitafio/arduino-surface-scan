# Código Python para receber, verificar e gravar dados em um Arquivo txt, vindos via USB de um Arduino
# Arduino precisa enviar os dados no formato "<dados>"
# Trocar a identificação da porta Serial conforme o seu PC
# Desenvolvido por Cleber Borges
# Canal FunBots

import serial
import time

beginMarker = '<'
endMarker = '>'
nomeArquivo = "testecaptura.txt"

def readArduino():
    global endMarker
    global beginMarker
    keyChars = "<>"
    message = ''

    while (arduino.inWaiting() > 0):
        message += arduino.readline(1).decode()

    if (beginMarker in message and endMarker in message): 
        for character in keyChars:
                message = message.replace(character, "")
        #print (message)
        arquivo.write(message+"\r")
        arduino.reset_input_buffer()
    

arduino = serial.Serial(
    port='COM8', #Trocar a porta aqui
    baudrate=9600,
    )

print(nomeArquivo)
while(True):
    arquivo = open(nomeArquivo, "a+")
    time.sleep(1)
    readArduino()
    arquivo.close
    
