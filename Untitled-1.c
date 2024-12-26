// #include <Servo.h>

// status
bool finish = true;
bool check = false;
#define B  1
#define W  0

int demngan = 0; 
int demtrai = 0;
int demphai = 0;

// motor
char ena = 6 , enb = 5; 
char in[4] = {7,8,3,4};
int left_motor_speed;
int initial_motor_speed = 100;
int right_motor_speed;


// line sensor 
char s1 = A1; char l1;
char s2 = A2; char l2;
char s3 = A3; char l3;
char s4 = A4; char l4;
char s5 = A5; char l5;

// servo
char servo_pin;

// HCSR-04
char echo;
char trig;
// PID
// error value and PID
int error;
int previous_error = 0;
int P; int Kp = 8;
int I; int Ki = 0;
int D; int Kd = 11;
int PID_value;


void MotorControl()
{
    if(error == 0)
    {
        robot_dithang();
    }
    if(error < 0)
    {
        robot_retrai();
    }
    if(error > 0)
    {
        robot_rephai();
    }
}

// calculation error by sensor detech situation
void errorCalculation()
{
    l1 = digitalRead(s1);
    l2 = digitalRead(s2);
    l3 = digitalRead(s3);
    l4 = digitalRead(s4);
    l5 = digitalRead(s5);
    // vào khu vực dò tường
    if (l1 == W && l2 == W && l3 == W && l4 == W && l5 == W)
    {
        // initial_motor_speed = 150;
      robot_dung();
    }
    // dò line
    if (l1 == W && l2 == W && l3 == W && l4 == W && l5 == B)
    {
        error = 3;
    }
    if (l1 == W && l2 == W && l3 == W && l4 == B && l5 == W)
    {
        error = 2;
    }
    if (l1 == W && l2 == W && l3 == B && l4 == B && l5 == W)
    {
        error = 1;
    }
    if (l1 ==  W && l2 == 0 && l3 == B && l4 == W && l5 == W)
    {
        error = 0;
    }
    if (l1 == W && l2 == B && l3 == B && l4 == W && l5 == W)
    {
        error = -1;
    }
    if (l1 == W && l2 == B && l3 == W && l4 == W && l5 == W)
    {
        error = -2;
    }
    if (l1 == B && l2 == W && l3 == W && l4 == W && l5 == W)
    {
        error = -3;
    }

    // dieu huong goc vuong - re phai
    //       0          0          1          1          1
    if(l1 == W && l2 == W && l3 == B && l4 == B && l5 == B
    || l1 == W && l2 == W && l3 == W && l4 == B && l5 == B)
    {
        demphai++;
        if(demphai )
        {
            rephai90();
        }

    // robot_dung();
    // analogWrite(ena, 80);
    // analogWrite(enb, 80);
    }
    // full line
    if(l1 == 1 && l2 == 1 && l3 == 1 && l4 == 1 && l5 == 1
    || l1 == 1 && l2 == 1 && l3 == 1 && l4 == 1 && l5 == 0
    || l1 == 0 && l2 == 1 && l3 == 1 && l4 == 1 && l5 == 0
    || l1 == 0 && l2 == 1 && l3 == 1 && l4 == 1 && l5 == 1)
    {
    //     if(check == true)
    //     {
    // 
    }       
    analogWrite(enb, right_motor_speed);
}

void robot_retrai()
{
    digitalWrite(in[0], LOW);
    digitalWrite(in[1], HIGH);

    digitalWrite(in[2], LOW);
    digitalWrite(in[3], HIGH);
}
void robot_rephai()
{
    digitalWrite(in[0], HIGH);
    digitalWrite(in[1], LOW);

    digitalWrite(in[2], HIGH);
    digitalWrite(in[3], LOW);
}
void robot_lui()
{
    digitalWrite(in[0], LOW);
    digitalWrite(in[1], HIGH);

    digitalWrite(in[2], HIGH);
    digitalWrite(in[3], LOW);
}
void robot_dithang()
{
    digitalWrite(in[0], HIGH);
    digitalWrite(in[1], LOW);
    digitalWrite(in[2], LOW);
    digitalWrite(in[3], HIGH);
}
void robot_dung()
{
    for (int i = 0; i < 4; i++)
    {
        digitalWrite(in[i], LOW);
    }
}

void rephai90()
{
  analogWrite(ena, 200); 
  analogWrite(enb, 200);
  
  // chinh delay
  robot_dung();
  delay(200);
  robot_dithang();
  delay(250);
  robot_dung();
  delay(200);
 
  robot_rephai();
  delay(350);
}
void retrai90()
{
  analogWrite(ena, 200); 
  analogWrite(enb, 200);
  
  // chinh delay
  robot_dung();
  delay(200);
  robot_dithang();
  delay(250);
  robot_dung();
  delay(200);
 
  robot_retrai();
  delay(350);
}


void setup()
{
// Serial
    Serial.begin(9600);
// servo
    
// motor
    pinMode(ena,OUTPUT);
    pinMode(enb,OUTPUT);
    for(int i = 0; i< 5; i++)
    {
        pinMode(in[i], OUTPUT);
    }
// hcsr04
    pinMode(echo, OUTPUT);
    pinMode(trig, INPUT);
// line sensor
    pinMode(s1, INPUT);
    pinMode(s2, INPUT);
    pinMode(s3, INPUT);
    pinMode(s4, INPUT);
    pinMode(s5, INPUT);
    
}
void loop()
{
    errorCalculation();
    pid_calculation();
    speedControl();
    MotorControl();
}
