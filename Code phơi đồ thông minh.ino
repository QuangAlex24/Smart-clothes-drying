#define BLYNK_TEMPLATE_ID "TMPL6LVAdGXGW"
#define BLYNK_TEMPLATE_NAME "test"
#define BLYNK_AUTH_TOKEN "qCoVJ1nNw-1EBc1lidTC3zE04tjP9YgQ"

#include <ESP32Servo.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define EVENT_OPEN "roof_open"
#define EVENT_CLOSE "roof_close"

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int rainAnalogPin  = 34;
const int lightAnalogPin = 35;

const int relayRoofPin = 25;
// Bỏ motorRoofIn1, motorRoofIn2 vì dùng servo
const int ledDarkPin = 13;
const int buzzerPin  = 12;

const int servoPin = 5; // chân tín hiệu servo

Servo myServo;

int rainAnalog  = 0;
int lightAnalog = 0;
bool isRoofOpen = false;

char ssid[] = "Nlgo";
char pass[] = "September23";

// Hàm điều khiển mở mái (servo quay 180°)
void openRoof() {
  digitalWrite(buzzerPin, HIGH); delay(200); digitalWrite(buzzerPin, LOW);
  digitalWrite(relayRoofPin, HIGH);
  

  myServo.attach(servoPin); // Bật servo
  myServo.write(180);       // Quay hết về 180° để mở mái
  delay(2000);              // Đợi ~2.0 giây cho servo kéo hết mái
  myServo.detach();         // Ngắt servo
  digitalWrite(relayRoofPin, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Thong bao:");
  lcd.setCursor(0, 1);
  lcd.print("ROOF OPEN");

  isRoofOpen = true;
  Serial.println("Roof opened in ~2.0s");
  Blynk.logEvent(EVENT_OPEN, "Mở mái (servo)");
}

void closeRoof() {
  digitalWrite(buzzerPin, HIGH); delay(200); digitalWrite(buzzerPin, LOW);
  digitalWrite(relayRoofPin, HIGH);

  myServo.attach(servoPin); // Bật servo
  myServo.write(0);         // Quay hết về 0° để đóng mái
  delay(2000);              // Đợi ~2.0 giây cho servo kéo hết mái
  myServo.detach();         // Ngắt servo
  digitalWrite(relayRoofPin, LOW);

  isRoofOpen = false;
    lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Thong bao:");
  lcd.setCursor(0, 1);
  lcd.print("ROOF CLOSE");

  Serial.println("Roof closed in ~2.0s");
  Blynk.logEvent(EVENT_CLOSE, "Đóng mái (servo)");
}

// Blynk nút điều khiển mái
BLYNK_WRITE(V0) {
  int control = param.asInt();
  if (control == 1 && !isRoofOpen) {
    openRoof();
  } else if (control == 0 && isRoofOpen) {
    closeRoof();
  }
  Blynk.virtualWrite(V0, control);
}

void setup() {
  Serial.begin(115200);

  pinMode(relayRoofPin, OUTPUT);
  pinMode(ledDarkPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(relayRoofPin, LOW);
  digitalWrite(ledDarkPin, LOW);
  digitalWrite(buzzerPin, LOW);

  myServo.attach(servoPin);
  myServo.write(0); // bắt đầu ở trạng thái đóng mái

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Connecting WiFi");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  lcd.clear();
}

void loop() {
  Blynk.run();

  rainAnalog  = analogRead(rainAnalogPin);
  lightAnalog = analogRead(lightAnalogPin);

  Blynk.virtualWrite(V1, rainAnalog);
  Blynk.virtualWrite(V2, lightAnalog);
  Blynk.virtualWrite(V3, isRoofOpen ? 1 : 0);

  Serial.print("🌧️ Rain: ");  
  Serial.println(rainAnalog);
  Serial.print("🔆 Light: "); 
  Serial.println(lightAnalog);

  digitalWrite(ledDarkPin, lightAnalog >= 3000 ? HIGH : LOW);
// Tự động điều khiển mái bằng servo
  if (rainAnalog <= 1500 && lightAnalog < 3000 && !isRoofOpen) {
    openRoof();
    Blynk.virtualWrite(V0, 1);
  } else if (lightAnalog >= 3000 && !isRoofOpen) {
    openRoof();
    Blynk.virtualWrite(V0, 1);
  } else if (lightAnalog < 3000 && rainAnalog > 1000 && isRoofOpen) {
    closeRoof();
    Blynk.virtualWrite(V0, 0);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TT: ");
  lcd.print(lightAnalog >= 3000 ? "Toi" : "Sang");
  lcd.print("|");
  lcd.print(rainAnalog <= 1000 ? "Mua" : "Kho");

  lcd.setCursor(0, 1);
  lcd.print("Mai: ");
  lcd.print(isRoofOpen ? "Mo" : "Dong");

  delay(200);
}
