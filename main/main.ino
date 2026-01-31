#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

int padL = D5;
int padR = D6;
int resetBtn = D7;

float history[5] = {0, 0, 0, 0, 0};
int solveCount = 0;
float personalBest = 0;
float currentAo5 = 0;

unsigned long startTime;
float finalTime;
bool isRunning = false;

byte barChar[8] = {31, 31, 31, 31, 31, 31, 31, 31};

void setup() {
  Wire.begin(D2, D1);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, barChar);
  
  pinMode(padL, INPUT);
  pinMode(padR, INPUT);
  pinMode(resetBtn, INPUT_PULLUP);

  randomSeed(analogRead(0));
  generateNewScramble();
}

void loop() {
  bool L = digitalRead(padL);
  bool R = digitalRead(padR);

  if (!isRunning && L && R) {
    lcd.clear();
    lcd.setCursor(7, 1);
    lcd.print("READY");
    
    for (int i = 0; i < 20; i++) {
      lcd.setCursor(i, 2);
      lcd.write(0); 
      delay(20);
    }

    while(digitalRead(padL) || digitalRead(padR)) { }
    
    startTime = millis();
    isRunning = true;
    lcd.clear();
  }

  if (isRunning) {
    float liveTime = (millis() - startTime) / 1000.0;
    
    lcd.setCursor(7, 1);
    lcd.print(liveTime, 2);
    lcd.print("s");

    if (digitalRead(padL) || digitalRead(padR)) {
      finalTime = (millis() - startTime) / 1000.0;
      isRunning = false;
      processSolve(finalTime);
      delay(2000);
      generateNewScramble();
    }
  }
  
  if (digitalRead(resetBtn) == LOW) {
    personalBest = 0;
    solveCount = 0;
    currentAo5 = 0;
    lcd.clear();
    lcd.print("Resetting...");
    delay(1000);
    generateNewScramble();
  }
}

void processSolve(float t) {
  if (personalBest == 0 || t < personalBest) {
    personalBest = t;
  }

  history[0] = history[1];
  history[1] = history[2];
  history[2] = history[3];
  history[3] = history[4];
  history[4] = t;
  
  solveCount++;

  if (solveCount >= 5) {
    currentAo5 = (history[0] + history[1] + history[2] + history[3] + history[4]) / 5.0;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TIME: "); lcd.print(t);
  lcd.setCursor(0, 1);
  lcd.print("PB:   "); lcd.print(personalBest);
  lcd.setCursor(0, 2);
  lcd.print("Ao5:  "); lcd.print(currentAo5);
}

void generateNewScramble() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PB:"); lcd.print(personalBest, 2);
  lcd.setCursor(11, 0);
  lcd.print("A5:"); lcd.print(currentAo5, 2);

  char moves[] = {'U', 'D', 'L', 'R', 'F', 'B'};
  lcd.setCursor(0, 1);
  for (int i = 0; i < 20; i++) {
    if (i == 7) lcd.setCursor(0, 2);
    if (i == 14) lcd.setCursor(0, 3);
    
    int r = random(0, 6);
    lcd.print(moves[r]);
    
    int s = random(0, 3);
    if (s == 1) lcd.print("'");
    if (s == 2) lcd.print("2");
    lcd.print(" ");
  }
}
