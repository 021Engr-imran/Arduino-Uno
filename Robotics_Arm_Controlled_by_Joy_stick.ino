#include<Servo.h>

Servo Baseservo;
Servo Jarservo;
Servo Rightservo;
Servo Leftservo;
int base =0;
int jar =0;
int right =0;
int left  =0;

void setup() 
{
  Baseservo.attach(7);
  Jarservo.attach(8);
  Rightservo.attach(9);
  Leftservo.attach(10);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  
  Baseservo.write(90);
  Jarservo.write(0);
  Rightservo.write(5);
  Leftservo.write(5);
}
void loop() 
{ 
  
//for base
      baseservomotor( );

//for jar code;
      jarservomotor( );

//for Rightside
      Rightsidemotor( );

//for left side
    Leftsidemotor( );

}


//baseservomotor( )
void baseservomotor( )
{
  int BaseservoRead=analogRead(A3);

  if (BaseservoRead>=800)
{ 
 if(base<=180)
 {
  base=base+1;
  Baseservo.write(base);
  delay(10);
 }
}

else if(BaseservoRead<=300)
{
  if(base>0)
  {
  base=base-1;
  Baseservo.write(base);
  delay(10);
  }
}
  
}

//jarservomotor( )
void jarservomotor( )
{
  int JarservoRead=analogRead(A1);

if(JarservoRead>=800)
{
 if(jar<=40)
 {
  jar=jar+1;
  Jarservo.write(jar);
  delay(5);
 }
}

else if(JarservoRead<=300)
{
  if(jar>0)
  {
  jar=jar-1;
  Jarservo.write(jar);
  delay(5);
  }
}
  
}

//Rightsidemotor( )
void Rightsidemotor( )
{
  int RightservoRead=analogRead(A0);
  
if (RightservoRead<=300)
{

 if(right<=180)
 {
  right=right+1;
  Rightservo.write(right);
  delay(10); 
 }
  
}

else if (RightservoRead>=800)
{
  if(right>0)
  {
    right=right-1;
    Rightservo.write(right);
    delay(10);
  }
}
  
}

//Leftsidemotor
void Leftsidemotor( )
{
   int LeftservoRead=analogRead(A2);
  
   if (LeftservoRead<=300)
{

 if(left<=90)
 {
  left=left+1;
  Leftservo.write(left);
  delay(10); 
 }
  
}

else if (LeftservoRead>=800)
{
  if(left>0)
  {
    left=left-1;
    Leftservo.write(left);
    delay(10);
  }
  
}

  
}