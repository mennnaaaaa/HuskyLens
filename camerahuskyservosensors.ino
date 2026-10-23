#include "HUSKYLENS.h"
#include "Wire.h"
#include <Servo.h>
#include "DHT.h"

// ================= HUSKYLENS =================

HUSKYLENS huskylens;az

// ================= SERVO =================

Servo cameraServo;

#define SERVO_PIN 6

int angle = 0;
int step = 2;

// ================= DHT22 =================
  s
#define DHT_PIN 7
#define DHT_TYPE DHT22

DHT dht(DHT_PIN, DHT_TYPE);

// ================= FLAME SENSOR =================

#define FLAME_PIN 4

// ================= TARGET =================o]=
-                                                                                      `                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             pp

#define TARGET_ID 1


void setup()
{
  Serial.begin(9600);
  Wire.begin();

  // Servo
  cameraServo.attach(SERVO_PIN);
  cameraServo.write(angle);

  // DHT
  dht.begin();

  // Flame Sensor
  pinMode(FLAME_PIN, INPUT);

  // HuskyLens
  while (!huskylens.begin(Wire))
  {
    Serial.println("HUSKYLENS not connected!");
    delay(500);
  }

  Serial.println("HUSKYLENS connected!");
  Serial.println("System Ready");
}


void loop()
{
  // =================================================
  // 1. Check HuskyLens
  // =================================================

  if (!huskylens.request())
  {
    Serial.println("HUSKYLENS request failed");
    return;
  }

  while (huskylens.available())
  {
    HUSKYLENSResult result = huskylens.read();
ئء
    Serial.print("Detected ID: ");
    Serial.println(result.ID);

    // =================================================
    // 2. ID 1 FOUND
    // =================================================

    if (result.ID == TARGET_ID)
    {
      Serial.println();
      Serial.println("==========================");
      Serial.println("ID 1 DETECTED!");
      Serial.println("SERVO STOPPED");
      Serial.println("==========================");

      // Stop servo at current position
      cameraServo.write(angle);

      // =================================================
      // 3. Read Sensors
      // =================================================

      while (true)
      {
        readSensors();

        // Read sensors every 2 seconds
        delay(2000);
      }
    }
  }

  // =================================================
  // 4. No ID 1 → Continue Scanning
  // =================================================

  angle = angle + step;

  // Reach 180° → change direction
  if (angle >= 180)
  {
    angle = 180;
    step = -2;
  }

  // Reach 0° → change direction
  if (angle <= 0)
  {
    angle = 0;
    step = 2;
  }

  cameraServo.write(angle);

  delay(50);
}


// =================================================
// SENSOR READING FUNCTION
// =================================================

void readSensors()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  int flame = digitalRead(FLAME_PIN);

  Serial.println();
  Serial.println("===== SENSOR READINGS =====");

  // DHT22
  if (isnan(temperature) || isnan(humidity))
  {
    Serial.println("DHT22: Reading Failed!");
  }
  else
  {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  // Flame Sensor
  if (flame == LOW)
  {
    Serial.println("Flame: DETECTED!");
  }
  else
  {
    Serial.println("Flame: No Flame");
  }

  Serial.println("==========================");
}