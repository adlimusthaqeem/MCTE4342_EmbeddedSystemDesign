//******************SPI Communication Protocol************************//
#include <SPI.h>
#include "I2Cdev.h"

//******************Gyrosensor MPU6050 Settings************************//
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

//******************Other Variables Declaration************************//
int reading;
int mapValue;
int i, j;
MPU6050 mpu;
#define OUTPUT_READABLE_YAWPITCHROLL


//******************/MPU control/status vars************************//
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

//******************Orientation/Motion vars************************//
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0, 0, 0, 0, 0, 0, 0, 0, 0x00, 0x00, '\r', '\n' };
float angle;
byte ref;
short yawAngle;
short setYawAngle;

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
bool flag;
bool finish1, finish2;
void dmpDataReady() {
  mpuInterrupt = true;
}

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void mpuSetup ()
{
  // join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  Serial.begin(115200);
  mpu.initialize();
  //    pinMode(INTERRUPT_PIN, INPUT);
  devStatus = mpu.dmpInitialize();

  mpu.setXGyroOffset(220); //220
  mpu.setYGyroOffset(76); //76
  mpu.setZGyroOffset(-85); // -85
  mpu.setZAccelOffset(1788); //1788

  if (devStatus == 0) {
    mpu.setDMPEnabled(true);
    //        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
  }
}

short mpuRead ()
{
  mpuIntStatus = mpu.getIntStatus();

  // get current FIFO count
  fifoCount = mpu.getFIFOCount();

  if (mpuIntStatus & 0x02) {
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
    mpu.getFIFOBytes(fifoBuffer, packetSize);
    fifoCount -= packetSize;

    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    yawAngle = short(ypr[0] * 180 / M_PI);
    yawAngle = yawAngle < 0 ? 360 + yawAngle : yawAngle;
  }
  return yawAngle;
}

ISR (SPI_STC_vect)
{
  SPDR = mapValue;
}  // end of interrupt service routine (ISR) SPI_STC_vect

void setup()
{
  Serial.begin(115200);
  pinMode(MISO, OUTPUT);

  // turn on SPI in slave mode
  SPCR |= _BV(SPE);

  // turn on interrupts
  SPCR |= _BV(SPIE);

  mpuSetup();
}

void loop()
{
  reading = mpuRead();
  mapValue = map(reading, 0, 360, 0, 255);
  Serial.println(mapValue);
}


