// SWISH2.0 Position control for DC Motors
// For Driver Pololu item #: 2990
// For Encoder Pololu item #: 3081
// The encoders provide a resolution of 12 counts per revolution
// Gear ratio x 12 --> 298 x 12 = 3576 is one rotation
// Gear ratio x 12 --> 1000 x 12 = 12000 is one rotation (1000:1 DC)
// Phi 1 rotation = 1788, Rad Max = 6168, Hei Max = 9015
// Phi range 0 -- -1700

#include <PID_v1.h>      //For calculating PID
#include <Encoder.h>     //For reading ticks of rotary encoder

// Encoder Pins from rotary encoder
#define OUT_phiA    18      // OUT_A needs to be an intrupt pin
#define OUT_phiB    30

#define OUT_radA    19
#define OUT_radB    31

#define OUT_heiA    20
#define OUT_heiB    32


// Pins from motor controller
#define phiPWM_PIN      12  // PWM_PIN is the ENABLE pin on the board
#define phiPHASE_PIN    22  // PHASE is the direction pin
#define phiSLEEP_PIN    23  // SLEEP_PIN is on/off pin on the board

#define radPWM_PIN      11
#define radPHASE_PIN    24
#define radSLEEP_PIN    25

#define hei1PWM_PIN      10
#define hei1PHASE_PIN    26
#define hei1SLEEP_PIN    27

#define hei2PWM_PIN      9
#define hei2PHASE_PIN    28
#define hei2SLEEP_PIN    29

// Pins for Hall sensors (limit switches)
const int interruptPinHei = 3;
const int interruptPinRad = 2;

// Variables not used
bool heiHall = false;
bool radHall = false;

//Initialize limit switch halls
int radhallVal = LOW;
int heihallVal = LOW;



bool startLoop = false;  // To start the loop function when homing is done
bool WRITEBACK = true; // Not used, from an older version   
bool PARSEINT = true; //PARSEINT should be false for Unity, true for testing via Serial Monitor

bool home1 = false; //to start the homing for height
bool radHomeGo = false; // to start homing for radius

// Variables to receive data from serial
int intIn[3];


//Define an instance of encoder
Encoder phiEnc(OUT_phiA, OUT_phiB);  // OUT_A needs to be an intrupt pin
Encoder radEnc(OUT_radA, OUT_radB);
Encoder heiEnc(OUT_heiA, OUT_heiB);


//Define the PID variables
double phiSetpoint, phiInput, phiOutput;
double phivalue = 0;
boolean phi_pid_enable = false;

double radSetpoint, radInput, radOutput;
double radvalue = 0;
boolean rad_pid_enable = false;

double heiSetpoint, heiInput, heiOutput;
double heivalue = 0;
boolean hei_pid_enable = false;


//Specify the links and initial tuning parameters for PID
double phiKp = 0.25, phiKi = 0.0001, phiKd = 0.01;
PID phiPID(&phiInput, &phiOutput, &phiSetpoint, phiKp, phiKi, phiKd, DIRECT);  // if motor will only run at full speed try 'REVERSE' instead of 'DIRECT'

double radKp = 0.25, radKi = 0.0001, radKd = 0.01;
PID radPID(&radInput, &radOutput, &radSetpoint, radKp, radKi, radKd, DIRECT);

double heiKp = 0.25, heiKi = 0.0001, heiKd = 0.01;
PID heiPID(&heiInput, &heiOutput, &heiSetpoint, heiKp, heiKi, heiKd, DIRECT);



void setup() {

  Serial.begin(115200);
//  Serial2.begin(115200);
  


  // Used for no ISR method of limit switches (halls)
  pinMode (interruptPinHei, INPUT);
  pinMode (interruptPinRad, INPUT);


  //PIN Initiation
  pinMode (phiPHASE_PIN, OUTPUT);
  pinMode (phiPWM_PIN, OUTPUT);
  pinMode (phiSLEEP_PIN, OUTPUT);

  pinMode (radPHASE_PIN, OUTPUT);
  pinMode (radPWM_PIN, OUTPUT);
  pinMode (radSLEEP_PIN, OUTPUT);

  pinMode (hei1PHASE_PIN, OUTPUT);
  pinMode (hei1PWM_PIN, OUTPUT);
  pinMode (hei1SLEEP_PIN, OUTPUT);

  pinMode (hei2PHASE_PIN, OUTPUT);
  pinMode (hei2PWM_PIN, OUTPUT);
  pinMode (hei2SLEEP_PIN, OUTPUT);


  //Initialize the variables
  phiInput = phiEnc.read(); // This reads the current position of the rotary encoder
  phiSetpoint = 0;

  radInput = radEnc.read();
  radSetpoint = 0;

  heiInput = heiEnc.read();
  heiSetpoint = 0;


  //Turn the PID on
  phiPID.SetMode(AUTOMATIC);
  phiPID.SetOutputLimits(-255, 255);
  delay(1000);

  radPID.SetMode(AUTOMATIC);
  radPID.SetOutputLimits(-255, 255);
  delay(1000);

  heiPID.SetMode(AUTOMATIC);
  heiPID.SetOutputLimits(-255, 255);
  delay(1000);



  home1 = true;


}




void loop()
{


  heihallVal = digitalRead(interruptPinHei);
  radhallVal = digitalRead(interruptPinRad);

//This is where the homing happens
  if (home1) {
// first home the height
    if (heihallVal != LOW)
    {
      digitalWrite(hei1SLEEP_PIN, HIGH);
      digitalWrite(hei1PHASE_PIN, LOW);
      analogWrite(hei1PWM_PIN, 150);

      digitalWrite(hei2SLEEP_PIN, HIGH);
      digitalWrite(hei2PHASE_PIN, LOW);
      analogWrite(hei2PWM_PIN, 150);
      delay(500);
      heiEnc.write(7000);
      delay(200);
      heiEnc.write(7000);

    }

    if (heihallVal == LOW)
    {
      delay(500);
      heiEnc.write(7000);
      delay(500);
      heiEnc.write(7000);
      radHomeGo = true;
    }

// start homing for radius
    if (radHomeGo)
    {


      if (radhallVal != LOW)
      {
        delay(1000);
        digitalWrite(radSLEEP_PIN, HIGH);
        digitalWrite(radPHASE_PIN, LOW);
        analogWrite(radPWM_PIN, 200);
        delay(500);
        radEnc.write(6000);
        delay(200);
        radEnc.write(6000);
        //Serial.println("radYES");

      }
      if (radhallVal == LOW)

      {
        //Serial.println("radYES");
        home1 = false;
        startLoop = true;
        delay(500);
        radEnc.write(6000);
        delay(200);
        radEnc.write(6000);
        radSetpoint = 3084;
        rad_pid_enable = true;
        delay(50);
        heiEnc.write(7000);
        phiEnc.write(0);
      }
    }
  }
  //delay(1000);

//Homing is done now start listening to numbers from Unity
  if (startLoop)
  {
//PID calculation for theta
    phiInput = phiEnc.read();
    //Serial.print("phi: ");
    //Serial.println(phiInput);
    phiPID.Compute();

    if (phi_pid_enable) {
      phipwmOut(phiOutput);
    }
    else {
      // Put the motor to sleep mode, that is break
      digitalWrite(phiSLEEP_PIN, LOW);
      digitalWrite(phiPHASE_PIN, LOW);
    }

//PID calculation for Radius
    radInput = radEnc.read();
    //Serial.print("rad: ");
    //Serial.println(radInput);
    radPID.Compute();

    if (rad_pid_enable) {
      radpwmOut(radOutput);
    }
    else {
      // Put the motor to sleep mode, that is break
      digitalWrite(radSLEEP_PIN, LOW);
      digitalWrite(radPHASE_PIN, LOW);
    }

//PID calculation for Height
    heiInput = heiEnc.read();
    //Serial.print("hei: ");
    //Serial.println(heiInput);
    heiPID.Compute();

    if (hei_pid_enable) {
      heipwmOut(heiOutput);
      //hei2pwmOut(heiOutput);
    }
    else {
      // Put the motor to sleep mode, that is break
      digitalWrite(hei1SLEEP_PIN, LOW);
      digitalWrite(hei1PHASE_PIN, LOW);
      // digitalWrite(hei2SLEEP_PIN, LOW);
      // digitalWrite(hei2PHASE_PIN, LOW);
    }

//Serial.println("phi:\trad:\thei:");
////Serial.print("\t");
//Serial.print(phiInput);
//Serial.print("\t");
//Serial.print(radInput);
//Serial.print("\t");
//Serial.print(heiInput);
//Serial.println();

//Listen to the port from Unity
    if (Serial.available() > 0) {

//            if (PARSEINT) {
//              for (int x = 0; x < 3; x++)
//              {
//                intIn[x] = Serial.parseInt();
//              }
//            } else {
//              Serial.readBytes((char *)intIn, 6); //Read 6 bytes (3 ints)
//            }


      int len = Serial.readBytes ((char *) intIn, 6);
      
      //if (Serial.read() == '\n') {
      if (len == 6) {
        phiSetpoint = intIn[0];
        radSetpoint = intIn[1];
        heiSetpoint = intIn[2];

        phi_pid_enable = true;
        rad_pid_enable = true;
        hei_pid_enable = true;


      }


      //Report back if WRITEBACK is true, not being used
      if (WRITEBACK) {
        Serial.write((char *)intIn, 6);
      }
    }
  }
}


//send the theta motors at the heighest speed to the specified position
void phipwmOut(int phiOut) {

  if (phiOut < 0) {
    //forward
    digitalWrite(phiSLEEP_PIN, HIGH);
    digitalWrite(phiPHASE_PIN, HIGH);
    analogWrite(phiPWM_PIN, abs(phiOut));
    //Serial.println(phiOut);
  }
  else {
    //backward
    digitalWrite(phiSLEEP_PIN, HIGH);
    digitalWrite(phiPHASE_PIN, LOW);
    analogWrite(phiPWM_PIN, abs(phiOut));
    //Serial.println(phiOut);
  }
}


//send the radius motors at the heighest speed to the specified position
void radpwmOut(int radOut) {

  if (radOut < 0) {
    //forward
    digitalWrite(radSLEEP_PIN, HIGH);
    digitalWrite(radPHASE_PIN, HIGH);
    analogWrite(radPWM_PIN, abs(radOut));
  }
  else {
    //backward
    digitalWrite(radSLEEP_PIN, HIGH);
    digitalWrite(radPHASE_PIN, LOW);
    analogWrite(radPWM_PIN, abs(radOut));
  }
}


//send the height motors at the heighest speed to the specified position
void heipwmOut(int heiOut) {

  if (heiOut < 0) {
    //forward
    digitalWrite(hei1SLEEP_PIN, HIGH);
    digitalWrite(hei1PHASE_PIN, HIGH);
    analogWrite(hei1PWM_PIN, abs(heiOut));
    digitalWrite(hei2SLEEP_PIN, HIGH);
    digitalWrite(hei2PHASE_PIN, HIGH);
    analogWrite(hei2PWM_PIN, abs(heiOut));
  }
  else {
    //backward
    digitalWrite(hei1SLEEP_PIN, HIGH);
    digitalWrite(hei1PHASE_PIN, LOW);
    analogWrite(hei1PWM_PIN, abs(heiOut));
    digitalWrite(hei2SLEEP_PIN, HIGH);
    digitalWrite(hei2PHASE_PIN, LOW);
    analogWrite(hei2PWM_PIN, abs(heiOut));
  }
}
