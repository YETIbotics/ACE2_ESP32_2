#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_BNO055 bno = Adafruit_BNO055();
Adafruit_SSD1306 display(16);

int8_t temp = 0;

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void)
{
  Serial.begin(9600);
  Serial.println("Orientation Sensor Raw Data Test");
  Serial.println("");

  Wire.begin(4, 15, 100000);
  //Wire.begin(21,22,100000);

  /* Initialise the sensor */
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1)
      ;
  }

  delay(1000);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  /* Display the current temperature */
  temp = bno.getTemp();
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temp);
  display.println(" C");
  display.println("");
  display.display();

  bno.setExtCrystalUse(true);
}

void loop(void)
{
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Tmp: ");
  display.print(temp);
  display.println(" C");
  display.print("X: ");
  display.print(euler.x());
  display.display();

  delay(100);
}
