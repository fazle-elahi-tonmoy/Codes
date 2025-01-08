#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <PID_v1.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// Define all variables

// NRF24L01+ radio setup
RF24 radio(A0, A1);  // CE, CSN
const byte address[6] = "ABCDE";
unsigned long lastSignalTime = 0;
const int signalTimeout = 250; // Radio signal timeout
int LED = 2; //Radio Signal indicator LED

// Data structure for receiving data via radio
struct packetdata {
  byte pot1;
  byte pot2;
  byte pot3;
  byte swtch1;
};
packetdata receiverdata;

// PID parameters and setup
#define PID_MIN_LIMIT -255  // Min limit for PID 
#define PID_MAX_LIMIT 255   // Max limit for PID 
#define PID_SAMPLE_TIME_IN_MILLI 10  // PID sample time in milliseconds

#define PID_PITCH_KP 58
#define PID_PITCH_KI 400
#define PID_PITCH_KD 1.1

#define PID_YAW_KP 0.7
#define PID_YAW_KI 0.4 
#define PID_YAW_KD 0.01

double setpointPitchAngle = 0;
double pitchGyroAngle = 0;
double pitchPIDOutput = 0;

double setpointYawRate = 0;
double yawGyroRate = 0;
double yawPIDOutput = 0;

PID pitchPID(&pitchGyroAngle, &pitchPIDOutput, &setpointPitchAngle, PID_PITCH_KP, PID_PITCH_KI, PID_PITCH_KD, DIRECT);
PID yawPID(&yawGyroRate, &yawPIDOutput, &setpointYawRate, PID_YAW_KP, PID_YAW_KI, PID_YAW_KD, DIRECT);

// Motor pins
uint8_t enableMotor2 = 10;
uint8_t motor2Pin1 = 6;
uint8_t motor2Pin2 = 7;

uint8_t motor1Pin1 = 4;
uint8_t motor1Pin2 = 5;
uint8_t enableMotor1 = 3;

int motorAdjustment;
#define MIN_ABSOLUTE_SPEED 15  // Min motor speed 

// MPU setup and variables
MPU6050 mpu;
bool dmpReady = false;  // set true if DMP init was successful
uint8_t devStatus;   // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

Quaternion q;           // [w, x, y, z] quaternion container
VectorFloat gravity;    // [x, y, z] gravity vector
float ypr[3];           // [yaw, pitch, roll] yaw/pitch/roll container and gravity vector
VectorInt16 gy;         // [x, y, z] gyro sensor measurements

void setup() {
    Serial.begin(9600);
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MAX);
    radio.setDataRate(RF24_250KBPS);
    radio.setChannel(124);
    radio.startListening();
    setupMotors();   
    setupMPU();
    setupPID();
    pinMode(LED, OUTPUT);
}

void setupPID() {
    pitchPID.SetOutputLimits(PID_MIN_LIMIT, PID_MAX_LIMIT);
    pitchPID.SetMode(AUTOMATIC);
    pitchPID.SetSampleTime(PID_SAMPLE_TIME_IN_MILLI);

    yawPID.SetOutputLimits(PID_MIN_LIMIT, PID_MAX_LIMIT);
    yawPID.SetMode(AUTOMATIC);
    yawPID.SetSampleTime(PID_SAMPLE_TIME_IN_MILLI);
}

void setupMotors() {
    pinMode(enableMotor1, OUTPUT);
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
  
    pinMode(enableMotor2, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);

    rotateMotor(0, 0);  // Initialize motors to stop
}

void setupMPU() {
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
  
    mpu.initialize();
    devStatus = mpu.dmpInitialize();

    // Use predefined offsets instead of auto-calibration
    mpu.setXAccelOffset(-429); 
    mpu.setYAccelOffset(-1701); 
    mpu.setZAccelOffset(1161);   
    mpu.setXGyroOffset(-5);
    mpu.setYGyroOffset(-6);
    mpu.setZGyroOffset(15);

    if (devStatus == 0) {
        mpu.setDMPEnabled(true);
        dmpReady = true;
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }
}

void loop() {
    if (!dmpReady) return;

    fifoCount = mpu.getFIFOCount();
    if (fifoCount >= packetSize) {
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        mpu.dmpGetGyro(&gy, fifoBuffer);

        pitchGyroAngle = ypr[1] * 180 / M_PI;  // Convert pitch to degrees
        yawGyroRate = gy.z;  // Gyro rate in degrees per second
        pitchPID.Compute();  // Compute pitch PID always
                
        if (radio.available()) {
            radio.read(&receiverdata, sizeof(packetdata));
            lastSignalTime = millis();
            digitalWrite(LED, HIGH);  // Signal received LED indicator

            // Adjust pitch setpoint based on pot1 value
            if (receiverdata.pot1 == 127) {
                setpointPitchAngle = 0;  // Center position
            } else {
                setpointPitchAngle = map(receiverdata.pot1, 0, 255, -2500, 2500) / 1000.0;
            }
             if (receiverdata.pot2 != 127) {
                yawPIDOutput = 0;  // Stop yaw PID control output
                motorAdjustment = map(receiverdata.pot2, 0, 255, -200, 200);  // Directly adjust motors
            } else {
                yawPID.Compute();  // Continue with yaw PID control if pot2 is centered
                motorAdjustment = 0;  // Reset manual adjustment
            }
           
        } else if (millis() - lastSignalTime > signalTimeout) {
            setpointPitchAngle = 0;
            motorAdjustment = 0;
            yawPID.Compute();
            digitalWrite(LED, LOW);  // Signal loss indicator
        }

        // Calculate motor speeds
        int motorSpeed1 = pitchPIDOutput + yawPIDOutput + motorAdjustment;
        int motorSpeed2 = pitchPIDOutput - yawPIDOutput - motorAdjustment;

        // Constrain motor speeds
        motorSpeed1 = constrain(motorSpeed1, -255, 255);
        motorSpeed2 = constrain(motorSpeed2, -255, 255);

        rotateMotor(motorSpeed1, motorSpeed2);
    }
}

void rotateMotor(int speed1, int speed2) {
    if (speed1 < 0) {
        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor1Pin2, LOW);    
    } else {
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, HIGH);      
    }

    if (speed2 < 0) {
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW);    
    } else {
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);      
    }

    // Ensure that the minimum speed is respected, even if the PID outputs a very low value
    analogWrite(enableMotor1, abs(speed1) < MIN_ABSOLUTE_SPEED ? 0 : abs(speed1));
    analogWrite(enableMotor2, abs(speed2) < MIN_ABSOLUTE_SPEED ? 0 : abs(speed2));
}
