#include<SoftwareSerial.h>
SoftwareSerial bluetooth(2,3); //rx tx do arduino
String codigo = "";
unsigned long delay1 = 0;
int loop_dois, loop_tres, x;
const int A_frente  = 2;
const int B_frente  = 6;
const int A_tras  = 3;
const int B_tras = 5; 
const int LED_A = 10;

void frente() { //função ir para frente
  Serial.println("ROBO DA UM PASSO");
  analogWrite(A_tras, 100);
  analogWrite(B_tras, 100);
  analogWrite(A_frente, 0);
  analogWrite(B_frente, 0);
  delay(500);
  analogWrite(A_frente, 0);
  analogWrite(B_tras, 0);
  analogWrite(A_tras, 0);
  analogWrite(B_frente, 0);
}

void girar_esquerda() { //função ir para esquerda
  Serial.println("ROBO VIRA PARA ESQUERDA");
  analogWrite(A_tras, 100);
  analogWrite(B_tras, 20);
  analogWrite(A_frente, 0);
  analogWrite(B_frente, 0);
  delay(500);
  analogWrite(A_frente, 0);
  analogWrite(B_tras, 0);
  analogWrite(A_tras, 0);
  analogWrite(B_frente, 0);
}

void girar_direita() { //função ir para direita
  Serial.println("ROBO VIRA PARA DIREITA");
  analogWrite(A_tras, 20);
  analogWrite(B_tras, 100);
  analogWrite(A_frente, 0);
  analogWrite(B_frente, 0);
  delay(500);
  analogWrite(A_frente, 0);
  analogWrite(B_tras, 0);
  analogWrite(A_tras, 0);
  analogWrite(B_frente, 0);
}

void ligar_led() { //função ligar led
  Serial.println("ROBO LIGA LED");
  digitalWrite(LED_A, HIGH);
}

void desligar_led() { // função desligar led
  Serial.println("ROBO DESLIGA LED");
  digitalWrite(LED_A, LOW);
}

void tempo() { //função esperar tempo
  Serial.println("ROBO ESPERA TEMPO");
  delay(4000);
}

void for_dois() {  //função repetição 2 vezes
  Serial.println("REPETE DUAS VEZES");
  loop_dois = loop_dois + 2;
  for ( int w = 0; w < 2; w++) { //repetir 2 vezes
    for (int j = loop_dois; j < codigo.indexOf('}'); j++) { //enquanto for menor que a posição do caracter { irá analisar osição de cada caracter da string
      if (codigo[j] == 'F') {
        frente(); // chama função ir para frente
      }
      else if (codigo[j] == 'E') {
        girar_esquerda(); //chamar função ir para esquerda
      }
      else if (codigo[j] == 'D') {
        girar_direita(); //chama função ir para direita
      }
      else if (codigo[j] == 'L') {
        ligar_led(); //chama função ligar led
      }
      else if (codigo[j] == 'O') {
        desligar_led(); //chama função desligar led
      }
      else if (codigo[j] == 'S') {
        tempo(); //chama função tempo
      }
    }
  }
  resto();
}

void for_tres() { //função repetição 3 vezes
  Serial.println("REPETE TRES VEZES");
  loop_tres = loop_tres + 2; 
  for ( int w = 0; w < 3; w++) { //repetir 3 vezes
    for (int j = loop_tres; j < codigo.indexOf('}'); j++) { //enquanto for menor que a posição do caracter { irá analisar letra por letra da string
      if (codigo[j] == 'F') {
        frente(); // chama função ir para frente
      }
      else if (codigo[j] == 'E') {
        girar_esquerda(); //chamar função ir para esquerda
      }
      else if (codigo[j] == 'D') {
        girar_direita(); //chama função ir para direita
      }
      else if (codigo[j] == 'L') {
        ligar_led(); //chama função ligar led
      }
      else if (codigo[j] == 'O') {
        desligar_led(); //chama função desligar led
      }
      else if (codigo[j] == 'S') {
        tempo(); //chama função tempo
      }
    }
  }
  resto();
}

void resto() {
  codigo.remove(0, ((codigo.indexOf('}') - x)) ); //remove todos os caracteres que estavam antes de { e o x é o valor da posição que chamou o laço de repeticao
} 



void principal() {
  for (int i = 0; i < codigo.length(); i++) { //analisa posição por posição até o tamanho da string
    if (codigo[i] == 'F') {
      frente(); // chama função ir para frente
    }
    else if (codigo[i] == 'E') {
      girar_esquerda(); //chamar função ir para esquerda
    }
    else if (codigo[i] == 'D') {
      girar_direita(); //chama função ir para direita
    }
    else if (codigo[i] == 'L') {
      ligar_led(); //chama função ligar led
    }
    else if (codigo[i] == 'O') {
      desligar_led(); //chama função desligar led
    }
    else if (codigo[i] == 'S') {
      tempo(); //chama função tempo
    }
    else if (codigo[i] == '3') {
      x = i; 
      loop_tres = i; //loop_tres é igual a posição atual do i, ou seja, posição que encontrou o caracter 3
      for_tres(); //chama função de repetir 3 vezes
    }
    else if (codigo[i] == '2') {
      x = i;
      loop_dois = i; //loop_dois é igual a posição atual do i, ou seja, posição que encontrou o caracter 2
      for_dois(); //chama função de repetir 2 vezes
    }
    else {
      codigo = " "; //limpa string
    }
  }
}

void setup() {
  pinMode(A_frente, OUTPUT);
  pinMode(B_frente, OUTPUT);
  pinMode(A_tras, OUTPUT);
  pinMode(B_tras, OUTPUT);
  pinMode(LED_A, OUTPUT);
  Serial.begin(9600);
  bluetooth.begin(9600); //bluetooth
}

void (*funcReset)() = 0;

void loop() {
  char caracter;
  while (bluetooth.available()) { //enquanto tiver caracter para receber na serial
    delay(3);
    caracter = bluetooth.read(); //lê
    codigo += caracter; //convertendo string
    delay1 = millis();
  }

  if (((millis() - delay1) > 10) && (codigo != "")) { // se a string do codigo não for vazia
    principal();
    delay(200);
    funcReset();
   }
  }
