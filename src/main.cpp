#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include <Adafruit_BNO055.h>
// #include <utility/imumaths.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_PWMServoDriver.h>

#include <Robot.h>
#include <RC_ESC.h>

const unsigned char PROGMEM YETIBOTICS[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x30, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x80, 0x80, 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x84,
    0x80, 0xC0, 0xC0, 0xC0, 0x40, 0x40, 0x40, 0x60, 0x20, 0x20, 0x30, 0x00, 0x00, 0x00, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x30, 0xF0, 0x30, 0x10, 0x10, 0x10, 0x00, 0x00, 0x18, 0x18, 0x18, 0x1C,
    0xFC, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xFC, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x26, 0x20,
    0x01, 0x40, 0x40, 0x81, 0x83, 0x02, 0x06, 0x18, 0x00, 0x00, 0xD8, 0xF8, 0xC0, 0x80, 0x80, 0x80,
    0x00, 0x00, 0x06, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xC0, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x7F, 0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x64, 0x64, 0x24, 0x26, 0x36, 0x36, 0x12, 0x12, 0x13, 0x19, 0x18, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xFC,
    0xFF, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x07, 0x02, 0x00, 0x00, 0x10, 0x7F, 0x7F, 0x4C,
    0x46, 0x62, 0x22, 0x31, 0x11, 0x19, 0x08, 0x0C, 0x07, 0x03, 0x00, 0x03, 0x08, 0x31, 0x22, 0x47,
    0x8F, 0x8E, 0x9E, 0x5E, 0x4C, 0x38, 0x19, 0x07, 0x00, 0x00, 0x01, 0xFF, 0xC0, 0xC0, 0x40, 0x00,
    0x00, 0x00, 0xF8, 0x07, 0x00, 0x00, 0xF0, 0xF8, 0x8C, 0xC6, 0xC3, 0x43, 0x41, 0x21, 0x20, 0x30,
    0x10, 0x18, 0x08, 0x00, 0x08, 0x1C, 0x1E, 0x12, 0x9B, 0xD9, 0x58, 0x78, 0x38, 0x38, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

//Adafruit_BNO055 bno = Adafruit_BNO055();
Adafruit_SSD1306 display(16);
ROBOT Robot;
WiFiMulti wifiMulti;

bool enableWIFI = false;

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
RC_ESC Lift(2, &pwm, true);

int8_t temp = 0;

void SetupTasks();
void SetupOTA();
void KillAllTasks();
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
    // if (!bno.begin())
    // {
    //     /* There was a problem detecting the BNO055 ... check your connections */
    //     Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    //     while (1)
    //         ;
    // }

    // delay(1000);



    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.drawBitmap(128, 32, YETIBOTICS, 128, 32, 1);
    display.display();

    display.setTextSize(1);
    display.setTextColor(WHITE2);

    float freq = 500;
         pwm.begin();
  pwm.setPWMFreq(freq);  // This is the maximum PWM frequency
   pwm.setPWM(0, 0, 0 / 2 );
        pwm.setPWM(1, 0, 0 / 2 ); //4096
   
    float startpules = 1391.6 / ( 1000000 / freq / 4096);
    
            pwm.setPWM(2, 0, startpules ); //342

            // for(int i = 0; i < 4096; i++)
            // {
            //     pwm.setPWM(0, 0, i );

            //     display.clearDisplay();
            //      display.setCursor(0, 0);
            //         display.print(i);
            //       display.display();

            //       i+=200;

            //     delay(500);
            // }


    pinMode(25, OUTPUT);
    digitalWrite(25, LOW);
    delay(100);
    digitalWrite(25, HIGH);
    delay(100);
    digitalWrite(25, LOW);

    if (enableWIFI)
    {
        wifiMulti.addAP("RoboticHuskies", "robotsrule");
        wifiMulti.addAP("NBS", "N3metr12");
        wifiMulti.addAP("FreePublicWIFI", "");
        wifiMulti.run();

        SetupOTA();

        display.clearDisplay();
        display.setCursor(0, 0);
        display.print(WiFi.localIP());
        display.display();

        delay(1000);
    }

    digitalWrite(25, HIGH);

    /* Display the current temperature */
    // temp = bno.getTemp();
    // display.clearDisplay();
    // display.setCursor(0, 0);
    // display.print("Temp: ");
    // display.print(temp);
    // display.println(" C");
    // display.println("");
    // display.display();

    // bno.setExtCrystalUse(true);

    SetupTasks();
}

void loop(void)
{
    //imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

    delay(20);
}

void WIRELoop(void *parameter);
TaskHandle_t WIRELoop_th;
void RobotLoop(void *parameter);
TaskHandle_t RobotLoop_th;
void AutonomousLoop(void *parameter);
TaskHandle_t AutonomousLoop_th;
void DriveLoop(void *parameter);
TaskHandle_t DriveLoop_th;
void LiftLoop(void *parameter);
TaskHandle_t LiftLoop_th;
void WIFILoop(void *parameter);
TaskHandle_t WIFILoop_th;

void SetupTasks()
{
    xTaskCreatePinnedToCore(
        WIRELoop,     /* Task function. */
        "WIRELoop",   /* String with name of task. */
        10000,        /* Stack size in words. */
        NULL,         /* Parameter passed as input of the task */
        100,          /* Priority of the task. */
        &WIRELoop_th, /* Task handle. */
        1);

    xTaskCreatePinnedToCore(
        RobotLoop,     /* Task function. */
        "RobotLoop",   /* String with name of task. */
        10000,         /* Stack size in words. */
        NULL,          /* Parameter passed as input of the task */
        10,            /* Priority of the task. */
        &RobotLoop_th, /* Task handle. */
        0);

    xTaskCreatePinnedToCore(
        AutonomousLoop,     /* Task function. */
        "AutonomousLoop",   /* String with name of task. */
        10000,              /* Stack size in words. */
        NULL,               /* Parameter passed as input of the task */
        1,                  /* Priority of the task. */
        &AutonomousLoop_th, /* Task handle. */
        0);

    xTaskCreatePinnedToCore(
        DriveLoop,     /* Task function. */
        "DriveLoop",   /* String with name of task. */
        10000,         /* Stack size in words. */
        NULL,          /* Parameter passed as input of the task */
        1,             /* Priority of the task. */
        &DriveLoop_th, /* Task handle. */
        0);

    xTaskCreatePinnedToCore(
        LiftLoop,     /* Task function. */
        "LiftLoop",   /* String with name of task. */
        10000,        /* Stack size in words. */
        NULL,         /* Parameter passed as input of the task */
        1,            /* Priority of the task. */
        &LiftLoop_th, /* Task handle. */
        0);

    if (enableWIFI)
    {
        xTaskCreatePinnedToCore(
            WIFILoop,     /* Task function. */
            "WIFILoop",   /* String with name of task. */
            10000,        /* Stack size in words. */
            NULL,         /* Parameter passed as input of the task */
            1,            /* Priority of the task. */
            &WIFILoop_th, /* Task handle. */
            0);
    }
}

void KillAllTasks()
{
    vTaskDelete(WIRELoop_th);
    vTaskDelete(RobotLoop_th);
    vTaskDelete(AutonomousLoop_th);
    vTaskDelete(DriveLoop_th);
    vTaskDelete(LiftLoop_th);

    //DONT KILL WIFI LOOP
    //vTaskDelete(WIFILoop_th);
}

volatile bool mpuInterrupt = false; // indicates whether MPU interrupt pin has gone high
void dmpDataReady()
{
    mpuInterrupt = true;
}

void WIRELoop(void *parameter)
{
    Serial.print("WIRELoop: Executing on core ");
    Serial.println(xPortGetCoreID());

    // MPU control/status vars
    bool dmpReady = false;  // set true if DMP init was successful
    uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
    uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
    uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
    uint16_t fifoCount;     // count of all bytes currently in FIFO
    uint8_t fifoBuffer[64]; // FIFO storage buffer

    // orientation/motion vars
    Quaternion q;        // [w, x, y, z]         quaternion container
    VectorInt16 aa;      // [x, y, z]            accel sensor measurements
    VectorInt16 aaReal;  // [x, y, z]            gravity-free accel sensor measurements
    VectorInt16 aaWorld; // [x, y, z]            world-frame accel sensor measurements
    VectorFloat gravity; // [x, y, z]            gravity vector
    float euler[3];      // [psi, theta, phi]    Euler angle container
    float ypr[3];        // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

    mpu.initialize();
    pinMode(21, INPUT);
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(95);
    mpu.setYGyroOffset(62);
    mpu.setZGyroOffset(-3);
    mpu.setZAccelOffset(1539); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0)
    {
        // turn on the DMP, now that it's ready

        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        attachInterrupt(digitalPinToInterrupt(21), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    }
    else
    {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }

    while (true)
    {
        // wait for MPU interrupt or extra packet(s) available
        while (!mpuInterrupt && fifoCount < packetSize)
        {
           
        }

        // reset interrupt flag and get INT_STATUS byte
        mpuInterrupt = false;
        mpuIntStatus = mpu.getIntStatus();

        // get current FIFO count
        fifoCount = mpu.getFIFOCount();

        // check for overflow (this should never happen unless our code is too inefficient)
        if ((mpuIntStatus & 0x10) || fifoCount == 1024)
        {
            // reset so we can continue cleanly
            mpu.resetFIFO();
            Serial.println(F("FIFO overflow!"));

            // otherwise, check for DMP data ready interrupt (this should happen frequently)
        }
        else if (mpuIntStatus & 0x02)
        {
            // wait for correct available data length, should be a VERY short wait
            while (fifoCount < packetSize)
                fifoCount = mpu.getFIFOCount();

            // read a packet from FIFO
            mpu.getFIFOBytes(fifoBuffer, packetSize);

            // track FIFO count here in case there is > 1 packet available
            // (this lets us immediately read more without waiting for an interrupt)
            fifoCount -= packetSize;

            // display Euler angles in degrees
            mpu.dmpGetQuaternion(&q, fifoBuffer);
            mpu.dmpGetGravity(&gravity, &q);
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
            //Serial.print("ypr\t");
           // Serial.print(ypr[0] * 180 / M_PI);
           // Serial.print("\t");
            //Serial.print(ypr[1] * 180 / M_PI);
            //Serial.print("\t");
            //Serial.println(ypr[2] * 180 / M_PI);
        }

        
        Robot.State.UpdateHeading(ypr[0] * 180 / M_PI);
        // sensors_event_t event;
        // bno.getEvent(&event);

        display.clearDisplay();
        display.setTextSize(1);
        display.setCursor(0, 0);

        display.print(Robot.State.LeftEnc);
        display.print(" ");
        display.println(Robot.State.RightEnc);

        display.print(Robot.State.LiftEnc);
        display.print(" ");
        display.println(Robot.State.Heading());

        display.print("USB: ");
        display.println(Robot.State.USBState);

        display.print("Lift: ");
        display.println(Robot.State.LiftSpeed);

        display.display();

        Lift.SetMotorSpeed(Robot.State.LiftSpeed);
       

        delay(1);
    }

    vTaskDelete(NULL);
}

void RobotLoop(void *parameter)
{
    Serial.print("RobotLoop: Executing on core ");
    Serial.println(xPortGetCoreID());

    Robot.Setup();
    while (true)
    {
        Robot.Loop();
        delay(1);
    }

    vTaskDelete(NULL);
}

void AutonomousLoop(void *parameter)
{
    Serial.print("AutonomousLoop: Executing on core ");
    Serial.println(xPortGetCoreID());

    while (true)
    {
        Robot.Autonomous.Loop();
        yield();
        delay(20);
    }

    vTaskDelete(NULL);
}
void DriveLoop(void *parameter)
{
    Serial.print("DriveLoop: Executing on core ");
    Serial.println(xPortGetCoreID());

    while (true)
    {
        Robot.Drive.Loop();
        yield();
        delay(20);
    }

    vTaskDelete(NULL);
}
void LiftLoop(void *parameter)
{
    Serial.print("LiftLoop: Executing on core ");
    Serial.println(xPortGetCoreID());

    while (true)
    {
        Robot.Lift.Loop();
        yield();
        delay(20);
    }

    vTaskDelete(NULL);
}

void WIFILoop(void *parameter)
{
    Serial.print("WIFILoop: Executing on core ");
    Serial.println(xPortGetCoreID());

    while (true)
    {
        ArduinoOTA.handle();
        delay(20);
    }

    vTaskDelete(NULL);
}

int PrevPercent = 0;
void SetupOTA()
{

    // Port defaults to 3232
    // ArduinoOTA.setPort(3232);

    // Hostname defaults to esp3232-[MAC]
    ArduinoOTA.setHostname("ace2");

    // No authentication by default
    // ArduinoOTA.setPassword("admin");

    // Password can be set with it's md5 value as well
    // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
    // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

    ArduinoOTA
        .onStart([]() {

            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else // U_SPIFFS
                type = "filesystem";

            // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
            KillAllTasks();
        })
        .onEnd([]() {
            Serial.println("\nEnd");
        })
        .onProgress([](unsigned int progress, unsigned int total) {
            if (PrevPercent < (progress / (total / 100)))
            {
                PrevPercent = (progress / (total / 100));
                //disp.WritePercentLarge(PrevPercent, 0, 0);
                display.clearDisplay();
                display.setCursor(45, 0);
                display.print(PrevPercent);
                display.println("%");

                for (int i = 0; i < PrevPercent; i += 11)
                {
                    display.print("=");
                }

                display.display();
            }
        })
        .onError([](ota_error_t error) {
            Serial.printf("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR)
                Serial.println("Auth Failed");
            else if (error == OTA_BEGIN_ERROR)
                Serial.println("Begin Failed");
            else if (error == OTA_CONNECT_ERROR)
                Serial.println("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR)
                Serial.println("Receive Failed");
            else if (error == OTA_END_ERROR)
                Serial.println("End Failed");
        });

    ArduinoOTA.begin();
}