//@yuguantoumx@icloud.com
//This driver is based on dfrobot 4 motor sheild
//encoders and motor driver sheild are not attached to same Arduino
//In this case,we use two Arduino mega 2560 to prevent exhausting the CPU

const int E1 = 3; ///<Motor1 Speed
const int E2 = 11;///<Motor2 Speed
const int E3 = 5; ///<Motor3 Speed
const int E4 = 6; ///<Motor4 Speed

const int M1 = 4; ///<Motor1 Direction
const int M2 = 12;///<Motor2 Direction
const int M3 = 8; ///<Motor3 Direction
const int M4 = 7; ///<Motor4 Direction
void M1_advance(char Speed) ///<Motor1 Advance
{
 digitalWrite(M1,LOW);
 analogWrite(E1,Speed);
}
void M2_advance(char Speed) ///<Motor2 Advance
{
 digitalWrite(M2,HIGH);
 analogWrite(E2,Speed);
}
void M3_advance(char Speed) ///<Motor3 Advance
{
 digitalWrite(M3,LOW);
 analogWrite(E3,Speed);
}
void M4_advance(char Speed) ///<Motor4 Advance
{
 digitalWrite(M4,HIGH);
 analogWrite(E4,Speed);
}

void M1_back(char Speed) ///<Motor1 Back off
{
 digitalWrite(M1,HIGH);
 analogWrite(E1,Speed);
}
void M2_back(char Speed) ///<Motor2 Back off
{
 digitalWrite(M2,LOW);
 analogWrite(E2,Speed);
}
void M3_back(char Speed) ///<Motor3 Back off
{
 digitalWrite(M3,HIGH);
 analogWrite(E3,Speed);
}
void M4_back(char Speed) ///<Motor4 Back off
{
 digitalWrite(M4,LOW);
 analogWrite(E4,Speed);
}
void motorInit() {
  for(int i=3;i<9;i++)
  pinMode(i,OUTPUT);
  for(int i=11;i<13;i++)
  pinMode(i,OUTPUT);
}

void rotate_z_positive(int pwm){
M1_advance(pwm);
M2_advance(pwm);
M3_advance(pwm);
M4_advance(pwm);
}
void rotate_z_negetive(int pwm){
  M1_back(pwm);
M2_back(pwm);
M4_back(pwm);
M3_back(pwm);
}
void translate_y_positive(int pwm){
  M1_advance(pwm);
M2_advance(pwm);
M3_back(pwm);
M4_back(pwm);
  
}
void translate_y_negetive(int pwm){
  M3_advance(pwm);
M4_advance(pwm);
M1_back(pwm);
M2_back(pwm);
}
void advance_x_positive(int pwm){
  M1_advance(pwm);
M3_advance(pwm);
M4_back(pwm);
M2_back(pwm);
}
void advance_x_negetive(int pwm){
  M2_advance(pwm);
M4_advance(pwm);
M1_back(pwm);
M3_back(pwm);
}
void motor_stop(){
  analogWrite(E1,0);
  analogWrite(E2,0);
  analogWrite(E3,0);
  analogWrite(E4,0);
}
bool equalZero(float x){
  if(x<0.1&&x>-0.1) return true;
  else return false;
}
void control4WD(float *ControlMsg){ //ControlMsg[0] vx 1 vy 2 vz
  if(ControlMsg[0]>0&&equalZero(ControlMsg[1])&&equalZero(ControlMsg[2])){advance_x_positive(ControlMsg[0]);}
  else if(ControlMsg[0]<0&&equalZero(ControlMsg[1])&&equalZero(ControlMsg[2])){advance_x_negetive(-ControlMsg[0]);}
  else if(ControlMsg[1]>0&&equalZero(ControlMsg[0])&&equalZero(ControlMsg[2])){translate_y_positive(ControlMsg[1]);}
  else if(ControlMsg[1]<0&&equalZero(ControlMsg[0])&&equalZero(ControlMsg[2])){translate_y_negetive(-ControlMsg[1]);}
  else if (ControlMsg[2]>0&&equalZero(ControlMsg[1])&&equalZero(ControlMsg[0])){rotate_z_positive(ControlMsg[2]);}
  else if (ControlMsg[2]<0&&equalZero(ControlMsg[1])&&equalZero(ControlMsg[0])){rotate_z_negetive(-ControlMsg[2]);}
  else {;}
}