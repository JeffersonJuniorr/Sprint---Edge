#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define o endereço I2C do LCD 20x4
#define I2C_ADDR 0x27 // Verifique o endereço do seu módulo I2C

// Define o número de colunas e linhas do LCD 20x4
#define LCD_COLS 20
#define LCD_ROWS 4

// Inicializa o LCD com o endereço I2C e número de colunas e linhas
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLS, LCD_ROWS);

// Definindo os pinos dos sensores ultrassônicos
#define TRIG_FRONT 9
#define ECHO_FRONT 10
#define TRIG_BACK 11
#define ECHO_BACK 12
#define TRIG_LEFT 13
#define ECHO_LEFT A0
#define TRIG_RIGHT A1
#define ECHO_RIGHT A2

// Definindo os pinos dos LEDs para indicar a direção
#define LED_UP 6
#define LED_DOWN 7
#define LED_LEFT 8
#define LED_RIGHT A3

// Função para criar caracteres personalizados no LCD
byte arrowUp[8] = {
  0b00100,
  0b01110,
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00000
};

byte arrowDown[8] = {
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte arrowLeft[8] = {
  0b00100,
  0b01100,
  0b11100,
  0b11111,
  0b11100,
  0b01100,
  0b00100,
  0b00000
};

byte arrowRight[8] = {
  0b00100,
  0b00110,
  0b00111,
  0b11111,
  0b00111,
  0b00110,
  0b00100,
  0b00000
};

void setup() {
  Serial.begin(9600);
  
  // Inicializa o LCD via I2C
  lcd.init();
  lcd.backlight(); // Habilita a luz de fundo do LCD

  // Cria os caracteres personalizados
  lcd.createChar(0, arrowUp);
  lcd.createChar(1, arrowDown);
  lcd.createChar(2, arrowLeft);
  lcd.createChar(3, arrowRight);

  // Inicializa os pinos dos LEDs
  pinMode(LED_UP, OUTPUT);
  pinMode(LED_DOWN, OUTPUT);
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);

  // Inicializa os pinos dos sensores ultrassônicos
  pinMode(TRIG_FRONT, OUTPUT);
  pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_BACK, OUTPUT);
  pinMode(ECHO_BACK, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);

  // Mensagem inicial no LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sistema de");
  lcd.setCursor(0, 1);
  lcd.print("Alerta de Colissao");
  delay(2000);
}

void loop() {
  // Realiza a medição da distância de cada sensor
  long distFront = readDistance(TRIG_FRONT, ECHO_FRONT);
  long distBack = readDistance(TRIG_BACK, ECHO_BACK);
  long distLeft = readDistance(TRIG_LEFT, ECHO_LEFT);
  long distRight = readDistance(TRIG_RIGHT, ECHO_RIGHT);
  
  // Limpa o LCD para atualização
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Front:");
  lcd.print(distFront);
  lcd.print("cm");
  lcd.setCursor(0, 1);
  lcd.print("Back:");
  lcd.print(distBack);
  lcd.print("cm");
  lcd.setCursor(0, 2);
  lcd.print("Left:");
  lcd.print(distLeft);
  lcd.print("cm");
  lcd.setCursor(0, 3);
  lcd.print("Right:");
  lcd.print(distRight);
  lcd.print("cm");

  // Reseta os LEDs
  digitalWrite(LED_UP, LOW);
  digitalWrite(LED_DOWN, LOW);
  digitalWrite(LED_LEFT, LOW);
  digitalWrite(LED_RIGHT, LOW);

  // Atualiza o LCD e LEDs conforme a distância de cada sensor
  updateDirection(distFront, 0, LED_UP);
  updateDirection(distBack, 1, LED_DOWN);
  updateDirection(distLeft, 2, LED_LEFT);
  updateDirection(distRight, 3, LED_RIGHT);

  delay(500); // Intervalo de atualização do sensor e do display
}

// Função para ler a distância de um sensor ultrassônico
long readDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Velocidade do som = 0.034 cm/us
  
  return distance;
}

// Função para atualizar o LCD e LEDs conforme a direção
void updateDirection(long distance, int charIndex, int ledPin) {
  int bars = map(distance, 0, 200, 4, 0); // Mapeia a distância para barras (0-4)
  
  if (bars < 0) bars = 0;
  if (bars > 4) bars = 4;
  
  // Apaga a seta se a distância for maior que 50 cm
  if (distance > 50) {
    lcd.setCursor(17, charIndex);
    lcd.print("   "); // Limpa a área da seta
  } else {
    switch (charIndex) {
      case 0: // Frente
        lcd.setCursor(18, 0);
        lcd.write(byte(0));
        break;
      case 1: // Trás
        lcd.setCursor(18, 2);
        lcd.write(byte(1));
        break;
      case 2: // Esquerda
        lcd.setCursor(17, 1);
        lcd.write(byte(2));
        break;
      case 3: // Direita
        lcd.setCursor(19, 1);
        lcd.write(byte(3));
        break;
    }
  }

  if (distance <= 50) {
    digitalWrite(ledPin, HIGH);
  }
}
