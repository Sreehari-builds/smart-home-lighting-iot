#include <SoftwareSerial.h>
#include <Keypad.h>

SoftwareSerial BT(10, 11);

const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};
byte rowPins[ROWS] = {2, 8, 4, A3};
byte colPins[COLS]  = {12, 13, A1,A2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int led1 = 9, led2 = 3, trigPin = 7, echoPin = 6;

bool masterON = false;
bool led1State = false, led2State = false;
bool ultrasonicEnabled = false;
bool motionState = false;         

int brightness1 = 128, brightness2 = 128;

int getDistance() {
  digitalWrite(trigPin, LOW);  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long d = pulseIn(echoPin, HIGH, 30000);
  return (d == 0) ? -1 : d * 0.034 / 2;
}

void setMode(int mode) {
  if (mode == 1) { brightness1 = 50;  brightness2 = 50;  }
  if (mode == 2) { brightness1 = 120; brightness2 = 120; }
  if (mode == 3) { brightness1 = 255; brightness2 = 255; }
  BT.print("MODE:"); BT.println(mode);
}


void syncBT() {
  BT.println(led1State  ? "L1_ON"  : "L1_OFF");
  BT.println(led2State  ? "L2_ON"  : "L2_OFF");
  BT.println(masterON   ? "SYS_ON" : "SYS_OFF");
  BT.print("B1_"); BT.println(map(brightness1, 0, 255, 0, 100));
  BT.print("B2_"); BT.println(map(brightness2, 0, 255, 0, 100));
}

void updateLEDs() {
  if (!masterON) {
    analogWrite(led1, 0);
    analogWrite(led2, 0);
    return;
  }

  if (ultrasonicEnabled) {
    int d = getDistance();
    bool motion = (d > 0 && d <= 40);

    analogWrite(led1, motion && led1State ? brightness1 : 0);
    analogWrite(led2, motion && led2State ? brightness2 : 0);


    if (motion != motionState) {
      motionState = motion;
      BT.println(motion ? "MOTION_ON" : "MOTION_OFF");
    }
  } else {
    analogWrite(led1, led1State ? brightness1 : 0);
    analogWrite(led2, led2State ? brightness2 : 0);
  }
}

void handleKeypad() {
  char key = keypad.getKey();
  if (!key) return;

  bool changed = true;
  switch (key) {
    case '*': masterON = true;                         break;
    case '0': masterON = false;                        break;
    case '1': led1State = !led1State;                  break;
    case '2': led2State = !led2State;                  break;
    case '4': brightness1 = max(0,   brightness1-20);  break;
    case '5': brightness1 = min(255, brightness1+20);  break;
    case '3': brightness2 = max(0,   brightness2-20);  break;
    case '6': brightness2 = min(255, brightness2+20);  break;
    case '7': setMode(1); changed = false;             break;
    case '8': setMode(2); changed = false;             break;
    case '9': setMode(3); changed = false;             break;
    case '#':
      ultrasonicEnabled = !ultrasonicEnabled;
      BT.println(ultrasonicEnabled ? "ULTRA_ON" : "ULTRA_OFF");
      changed = false;
      break;
    default: changed = false;
  }

  updateLEDs();
  if (changed) syncBT();  
}

void handleBluetooth() {
  if (!BT.available()) return;
  String cmd = BT.readStringUntil('\n');
  cmd.trim();

  bool changed = true;
  if      (cmd == "L1_ON")  led1State = true;
  else if (cmd == "L1_OFF") led1State = false;
  else if (cmd == "L2_ON")  led2State = true;
  else if (cmd == "L2_OFF") led2State = false;
  else if (cmd == "SYS_ON") masterON = true;
  else if (cmd == "SYS_OFF") masterON = false;
  else if (cmd.startsWith("B1_")) { brightness1 = map(cmd.substring(3).toInt(), 0,100,0,255); }
  else if (cmd.startsWith("B2_")) { brightness2 = map(cmd.substring(3).toInt(), 0,100,0,255); }
  else if (cmd == "M1") { setMode(1); changed = false; }
  else if (cmd == "M2") { setMode(2); changed = false; }
  else if (cmd == "M3") { setMode(3); changed = false; }
  else changed = false;

  updateLEDs();
  if (changed) syncBT();
}

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  pinMode(led1, OUTPUT); pinMode(led2, OUTPUT);
  pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT);
  BT.println("System Ready");
}

void loop() {
  handleKeypad();
  handleBluetooth();
  if (ultrasonicEnabled && masterON) updateLEDs();  
  delay(100);  
}
