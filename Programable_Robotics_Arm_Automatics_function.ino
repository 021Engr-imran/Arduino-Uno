#include<Servo.h>

Servo Baseservo;
Servo Jarservo;
Servo Rightservo;
Servo Leftservo;
int base =0;
int jar =5;
int right =0;
int left  =0;
int count =0,count2;
int var3;
 int baseservoleftsidemove;
  int  baseservorigthsidemove;
  int openjar;
  int closejar;
   int rightsideservofarwardsidepick ;
    int rightsideservobackwardpick;
    int leftsideservoupmovepick;
    int leftsideservodownmovepick;
    int  rightsideservofarwadsidedrop;
    int  rightsideservobackwarddrop;
    int leftsideservoupmovedrop;
    int leftsideservodownmovedrop;

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
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP); 
  Baseservo.write(0);
  Jarservo.write(5);
  Rightservo.write(5);
  Leftservo.write(5);
  Serial.begin(9600);
}
void loop() 
{ 
  int var = digitalRead(2);
  if(var==0)
  {
    count=count+1;
    delay(1000);
  }
  Serial.println(count);
//   Serial.println(baseservoleftsidemove);
 //   Serial.println(baseservorigthsidemove);
 // Serial.println("press button recode");
if (count<3)
{
  //for base

  int BaseservoRead=analogRead(A3);

  if (BaseservoRead>=800)
{ 
 if(base<=180)
 {if (count==1)
 {
   baseservoleftsidemove=base+1;
 }
 // Serial.println(baseservoleftsidemove);
  base=base+1;
  Baseservo.write(base);
  delay(10);
 }
}

else if(BaseservoRead<=300)
{
  if(base>0)
  {   if (count==1)
 {
      baseservorigthsidemove=base-1;
 }
  //  Serial.println(baseservorigthsidemove);
  base=base-1;
  Baseservo.write(base);
  delay(10);
  }
}

//for jar code;
  
  int JarservoRead=analogRead(A1);

if(JarservoRead>=800)
{
 if(jar<=40)
 {
  if (count==1)
 {
   openjar=jar+1;
 }
  jar=jar+1;
  Jarservo.write(jar);
  delay(5);
 }
}

else if(JarservoRead<=300)
{
  if(jar>5)
  {  if (count==1)
 {
     closejar=jar-1;
 }
  jar=jar-1;
  Jarservo.write(jar);
  delay(5);
  }
}    

//for Rightside
      int RightservoRead=analogRead(A0);
  
if (RightservoRead<=300)
{

 if(right<=180)
 {if (count==1)
 {
  rightsideservofarwardsidepick = right+1;
 }
 else if(count==2)
 {
  rightsideservofarwadsidedrop=right+1;
 }
  right=right+1;
  Rightservo.write(right);
  delay(10); 
 }
  
}

else if (RightservoRead>=800)
{
  if(right>0)
  { if (count==1)
 { 
    rightsideservobackwardpick=right-1;
 }
 else if(count==2)
 {
  rightsideservobackwarddrop=right-1;
 }
    right=right-1;
    Rightservo.write(right);
    delay(10);
  }
}

//for left side
    int LeftservoRead=analogRead(A2);
  
   if (LeftservoRead<=300)
{

 if(left<=90)
 { if (count==1)
 {  
  leftsideservoupmovepick=left+1;
 }
 else if (count==2)
 {
  leftsideservoupmovedrop=left+1;
 }
  left=left+1;
  Leftservo.write(left);
  delay(10); 
 }
  
}

else if (LeftservoRead>=800)
{
  if(left>0)
  { if (count==1)
 { 
    leftsideservodownmovepick=left-1;
 }
 else if (count==2)
 {
  leftsideservodownmovedrop=left+1;
 }
 

 
    left=left-1;
    Leftservo.write(left);
    delay(10);
  }
  
}
    
}

//for left side to pick things;
int var2=digitalRead(3);

if (var2==0)
{
  count2=count2+1;
  delay(1000);
}
Serial.println(count2);
if(count2==1)
{   count2=count2+1;
   Baseservo.write(180);
   base=180;
}

if(count>=4 && count2>0)
{ 
  
//for base
         baseseroback1( );
         delay(15);

 //for jar code;
      jarservomotoropen( );
         delay(15);
                 
//for Rightside
      Rightsidemotor1( );
      delay(15);

//for left side
            Leftsidemotor1( );
              delay(15);
              
//for jar servo close
           jarservomotoclose( );
             delay(15);
//for right sideback;
     Rightsidemotorback1( );
         delay(15);
//for left sideback;        
         leftsidemotorback1( );
           delay(15);

//for rigth side back ;
     baseservomotor1( );
    
        delay(15);
//for Rightside
      Rightsidemotor2( );
         delay(15);

//for left side    
     Leftsidemotor2( ); 
      delay(15);
          
//for jar code;
      jarservomotoropen( );  
          delay(15);
       jarservomotoclose( );
      delay(15);
//for rigth side back ;
        Rightsidemotorback2( );
        delay(15);

//for left side
      leftsidemotorback2( );
      delay(15);

}




//for right side move
else if(count>=4 )
{ 
  
//for base
      baseservomotor1( );
         delay(15);

 //for jar code;
      jarservomotoropen( );
         delay(15);
                 
//for Rightside
      Rightsidemotor1( );
      delay(15);

//for left side
            Leftsidemotor1( );
              delay(15);
              
//for jar servo close
           jarservomotoclose( );
             delay(15);
//for right sideback;
     Rightsidemotorback1( );
         delay(15);
//for left sideback;        
         leftsidemotorback1( );
           delay(15);

//for rigth side back ;
     baseseroback1( );
        delay(15);
//for Rightside
      Rightsidemotor2( );
         delay(15);

//for left side    
     Leftsidemotor2( ); 
      delay(15);
          
//for jar code;
      jarservomotoropen( );  
          delay(15);
       jarservomotoclose( );
      delay(15);
//for rigth side back ;
        Rightsidemotorback2( );
        delay(15);

//for left side
      leftsidemotorback2( );
      delay(15);

}





}




//edit code 

//baseservomotor( )
void baseservomotor1( )
{
 for(int base = baseservorigthsidemove;base<=baseservoleftsidemove; base=base+1)
 {
  Baseservo.write(base);
   delay(10);
 
}
}

void baseseroback1( )
{
 for(int base = baseservoleftsidemove;base>=baseservorigthsidemove; base=base-1)
{
  
  Baseservo.write(base);
   delay(10);
  }
}
  


//jarservomotor( )
void jarservomotoropen( )
{
for(int jar =5 ;jar<=40; jar=jar+1)
{
 
  Jarservo.write(jar);
  delay(15);
 
}
}
void jarservomotoclose( )
{
for(int jar =40;jar>=5; jar=jar-1)
{
  
 
  Jarservo.write(jar);
  delay(15);
  
}
  
}

//for Rightsidemotor( ) for pick.
void Rightsidemotor1( )
{
for(int right = rightsideservobackwardpick ; right <= rightsideservofarwardsidepick;  right=right+1)
 {

  Rightservo.write(right);
  delay(10); 
 }
  
}

void Rightsidemotorback1( )
{
  for (int right=rightsideservofarwardsidepick;right > rightsideservobackwardpick;right=right-1)
  {
    
    Rightservo.write(right);
    delay(10);
  }
}
 

//Leftsidemotor
void Leftsidemotor1( )
{for (int left =leftsideservodownmovepick;left <=leftsideservoupmovepick;left=left+1)
{

  Leftservo.write(left);
  delay(10); 
 }
  
}

void leftsidemotorback1( )

{
  for (int left =leftsideservoupmovepick;left>leftsideservodownmovepick;left=left-1)
{

  Leftservo.write(left);
  delay(10); 
 }
  
}

//for right drop
void Rightsidemotor2( )
{
for(int right = rightsideservobackwarddrop ; right <= rightsideservofarwadsidedrop;  right=right+1)
 {

  Rightservo.write(right);
  delay(10); 
 }
  
}

void Rightsidemotorback2( )
{
  for (int right = rightsideservofarwadsidedrop ;right > rightsideservobackwarddrop;right=right-1)
  {
    
    Rightservo.write(right);
    delay(10);
  }
}

//for leftside drop
void Leftsidemotor2( )
{for (int left =leftsideservodownmovedrop;left <=leftsideservoupmovedrop;left=left+1)
{

  Leftservo.write(left);
  delay(10); 
 }
  
}

void leftsidemotorback2( )

{
  for (int left =leftsideservoupmovedrop;left>leftsideservodownmovedrop;left=left-1)
{

  Leftservo.write(left);
  delay(10); 
 }
}