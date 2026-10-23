#include "HUSKYLENS.h"
#include "Wire.h"

HUSKYLENS huskylens;

// LED pins
#define LED1 8
#define LED2 9

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  // Set LEDs as OUTPUT
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  // LEDs OFF at start
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  // Connect to HuskyLens
  while (!huskylens.begin(Wire))
  {
    Serial.println("HUSKYLENS not connected!");
    delay(500);
  }

  Serial.println("HUSKYLENS connected!");
}

void loop()
{
  // Turn both LEDs OFF first
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  // Request data from HuskyLens
  if (!huskylens.request())
  {
    Serial.println("Request failed");
    return;
  }

  // Read detected objects
  while (huskylens.available())
  {
    HUSKYLENSResult result = huskylens.read();

    Serial.print("ID = ");
    Serial.println(result.ID);

    // ID 1 → LED 1 ON
    if (result.ID == 1)
    {
      digitalWrite(LED1, HIGH);
    }

    // ID 2 → LED 2 ON
    if (result.ID == 2)
    {
      digitalWrite(LED2, HIGH);
    }
  }

  delay(100);
}