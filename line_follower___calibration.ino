//pin 6 = PWMB
//pin 7 = PWMA
//pin 8 = BIN2
//pin 9 = AIN1
//pin 10 = AIN2
//pin 11 = STBY
//pin 12 = BIN1


#define RIGHT_PWM   6
#define LEFT_PWM    5
#define STANDBY     11
#define AIN_1       9
#define AIN_2       10
#define BIN_1       12
#define BIN_2       8


#define LEFT_EDGE   A5
#define LEFT_POS    A4
#define CENTER_POS  A3
#define RIGHT_POS   A2
#define RIGHT_EDGE  A1

int sensor_Max = 0;
int sensor_Min = 1024;


unsigned  sensor_top ;
unsigned  sensor_bot ;
unsigned  position_2 ;


//int sensor_1 = analogRead(LEFT_EDGE);
//int sensor_2 = analogRead(LEFT_POS);
//int sensor_3 = analogRead(CENTER_POS);
//int sensor_4 = analogRead(RIGHT_POS);
//int sensor_5 = analogRead(RIGHT_EDGE);


int s1_max, s1_min, s2_max, s3_max, s4_max, s5_max, s2_min,  s3_min, s4_min, s5_min;
int POSITION;

int s3 = 0;
int s1 = 0;
int sensor_avrg = 0;
int sensor_cal = 0;
int sensor_minus = 0;


void position_new(){

int sensor_1 = analogRead(LEFT_EDGE);
int sensor_2 = analogRead(LEFT_POS);
int sensor_3 = analogRead(CENTER_POS);
int sensor_4 = analogRead(RIGHT_POS);
int sensor_5 = analogRead(RIGHT_EDGE);

s1 = sensor_1;




  
}



void calibrate(){

int sensor_1 = analogRead(LEFT_EDGE);
int sensor_2 = analogRead(LEFT_POS);
int sensor_3 = analogRead(CENTER_POS);
int sensor_4 = analogRead(RIGHT_POS);
int sensor_5 = analogRead(RIGHT_EDGE);


while(millis() <= 200){

if(sensor_1 > sensor_Max){
  s1_max = sensor_1;
}
if(sensor_1 < sensor_Min){
  s1_min = sensor_1 ;
}

if(sensor_2 > sensor_Max){
  s2_max = sensor_2;
}
if(sensor_2 < sensor_Min){
  s2_min = sensor_2 ;
}

if(sensor_3 > sensor_Max){
  s3_max = sensor_3;
}
if(sensor_3 < sensor_Min){
  s3_min = sensor_3 ;
}
if(sensor_4 > sensor_Max){
  s4_max = sensor_4;
}
if(sensor_4 < sensor_Min){
  s4_min = sensor_4 ;
}
if(sensor_5 > sensor_Max){
  s5_max = sensor_5;
}
if(sensor_5 < sensor_Min){
  s5_min = sensor_5 ;
}




   
}

  
}
void pos(){

int sensor_1 = analogRead(LEFT_EDGE);
int sensor_2 = analogRead(LEFT_POS);
int sensor_3 = analogRead(CENTER_POS);
int sensor_4 = analogRead(RIGHT_POS);
int sensor_5 = analogRead(RIGHT_EDGE);


// if(s1_max > s1_min){
// POSITION = 1;
//}
s3 = sensor_1;

  
 if (sensor_1 > sensor_cal  && sensor_2 > sensor_cal){
  POSITION = 12;
}
else if (sensor_2 > sensor_cal && sensor_3 > sensor_cal){
  POSITION = 23;
}
else if (sensor_3 > sensor_cal && sensor_4 > sensor_cal){
  POSITION = 34;
}
else if (sensor_4 > sensor_cal && sensor_5 > sensor_cal){
  POSITION = 45;
}

else if (sensor_1 > sensor_cal){
  
  POSITION = 1;
  
}
else if (sensor_2 > sensor_cal){
  POSITION = 2;
}
else if (sensor_3 > sensor_cal){
  POSITION = 3;
}
else if (sensor_4 > sensor_cal){
  POSITION = 4;
}
else if (sensor_5 > sensor_cal){
  POSITION = 5;
}


}





void motorControl(int l_speed , int r_speed) 
{  


 
 
   if(l_speed < 0) 
   {
    l_speed = l_speed * (-1)  ; 
    analogWrite(LEFT_PWM , l_speed);  
    digitalWrite(AIN_1 , 0);
    digitalWrite(AIN_2 , 1);
   }  
   else 
   { 
     analogWrite(LEFT_PWM , l_speed); 
     digitalWrite(AIN_1 , 1);
     digitalWrite(AIN_2 , 0);
   } 
   
    if(r_speed < 0) 
   {
    r_speed = r_speed * (-1)  ; 
    analogWrite(RIGHT_PWM , r_speed); 
      digitalWrite(BIN_1 , 0);
      digitalWrite(BIN_2 , 1);
   } 
   else 
   { 
      analogWrite(RIGHT_PWM , r_speed); 
      digitalWrite(BIN_1 , 1);
      digitalWrite(BIN_2 , 0);
   }
  
}
void setup() {

Serial.begin(9600);

  int s1 = analogRead(LEFT_EDGE);
pinMode(RIGHT_PWM, OUTPUT);
pinMode(LEFT_PWM, OUTPUT);
pinMode(STANDBY, OUTPUT);
pinMode(AIN_1, OUTPUT);
pinMode(AIN_2, OUTPUT);
pinMode(BIN_1, OUTPUT);
pinMode(BIN_2, OUTPUT);




}

void loop() {


int sensor_1 = analogRead(LEFT_EDGE);
int sensor_2 = analogRead(LEFT_POS);
int sensor_3 = analogRead(CENTER_POS);
int sensor_4 = analogRead(RIGHT_POS);
int sensor_5 = analogRead(RIGHT_EDGE);



sensor_top = (100*sensor_1 + 200*sensor_2 + 300*sensor_3 + 400*sensor_4 + 500*sensor_5);
sensor_bot = (sensor_1 + sensor_2 + sensor_3 + sensor_4 + sensor_5);
position_2 = (sensor_top / sensor_bot);  

sensor_avrg = ( s1_max + s2_max + s3_max + s4_max + s5_max) / 5;
sensor_minus = sensor_Min - sensor_avrg;
sensor_cal = sensor_avrg -150;


digitalWrite(STANDBY, HIGH);


//analogWrite(RIGHT_PWM, 100);
//digitalWrite(AIN_1, HIGH);
//digitalWrite(AIN_2, LOW);

  calibrate();
  pos();
  position_new();
  
if (POSITION == 1){
  motorControl(-60 , 20);

}
if (POSITION == 2){
  motorControl(40 , 0);
}
if (POSITION == 3){
  motorControl(60 , 60);
}
if (POSITION == 4){
  motorControl(0, 40);
}
if (POSITION == 5){
  motorControl(20 , 60);
} 
if (POSITION == 12){
  motorControl(60 , 20);
}
if (POSITION == 23){
  motorControl(45 , 15);
}
if (POSITION == 34){
  motorControl(15 , 45);
}
if (POSITION == 45){
  motorControl(20 , 60);
}
  
//if (POSITION == 1){
//  motorControl(-80 , 20);
//
//}
//if (POSITION == 2){
//  motorControl(60 , 0);
//}
//if (POSITION == 3){
//  motorControl(100 , 100);
//}
//if (POSITION == 4){
//  motorControl(0, 60);
//}
//if (POSITION == 5){
//  motorControl(20 , -80);
//}
//if (POSITION == 12){
//  motorControl(-50 , 20);
//}
//if (POSITION == 23){
//  motorControl(30,65);
//}
//if (POSITION == 34){
//  motorControl(65 , 30);
//}
//if (POSITION == 45){
//  motorControl(20 , -50);
//}



delay(200);


//Serial.print(position_2);
  Serial.println();
  Serial.print(POSITION);
  Serial.println();
//  Serial.print(s3_max);
//  Serial.println();
//  Serial.print(s4_max);
//  Serial.println();
//  Serial.print(s5_max);
//  Serial.println();
 




}
