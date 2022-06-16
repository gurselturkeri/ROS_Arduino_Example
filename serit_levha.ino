#include <ros.h>
#include <std_msgs/Empty.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <Stepper.h>

ros::NodeHandle nh;
float adim;
const int TARIK = 1600; //17Derece
//const int TARIK = 16000; //34Derece

boolean INITIAL_FLAG = 1;
//const int S = 23000;
//Stepper mStepper(S, 23,25,27,29);


int frendurum=0;
int butondurum=0;
int x = 0;
const int stepsPerRevolution = 8000; //FREN %100
//const int stepsPerRevolution = 1000; // %50

Stepper myStepper(TARIK,29,27,25,23);
Stepper stepper(stepsPerRevolution,3,4,5,6);

int ileri = 12;
int bos;
int geri = 11;



std_msgs::String button_msg;

 //digitalWrite(ileri,HIGH);
  //digitalWrite(geri,HIGH);

void ilerifonk() {

  digitalWrite(ileri,LOW);
  digitalWrite(geri,HIGH);
}

void gerifonk() {
  
  digitalWrite(geri,LOW);
  digitalWrite(ileri,HIGH);
  
}

void bosfonk() {
  digitalWrite(ileri,LOW);
  digitalWrite(geri,LOW);
}




void callbackFn( const sensor_msgs::Joy& joy_msg){

  int ileri_buton = joy_msg.buttons[3];
  int geri_buton = joy_msg.buttons[0];
  int bos_buton = joy_msg.buttons[1];
  
   
  float sag = joy_msg.axes[0];
  float sol = joy_msg.axes[0];
 
  float xAxis = joy_msg.axes[4];
  
  int butondurum = joy_msg.buttons[2]; //fren

  int yuzde25gaz =  joy_msg.buttons[4];
  int yuzde50gaz =  joy_msg.buttons[5];


  if (xAxis>0){
    
    xAxis = (175-xAxis*175);
    analogWrite(9,xAxis);
  }

  
  else if(yuzde25gaz == 1){
  yuzde25gaz = 150;
    analogWrite(9,yuzde25gaz);
  }
   
  
  else if(yuzde50gaz == 1){
     yuzde50gaz = 120 ;
    analogWrite(9,yuzde50gaz);
  }

 else {
    analogWrite(9,175);
  }
 
  
  
 if(butondurum==1 && x==0){
    x=1;
   stepper.step(-stepsPerRevolution);
   butondurum=0;
      }
  
  if(butondurum==1 && x==1){
    stepper.step(stepsPerRevolution);
    x=0;
    butondurum=0;
    }
  

 if (ileri_buton == 1){
  ilerifonk();
 }
 if (geri_buton == 1){
  gerifonk();
 }
 if (bos_buton == 1){
  bosfonk();
 }

if (sag >0 && sag <= 1){
  sagadonfonk();
 } 
  if (sol <0 && sol >= -1){
  soladonfonk();
 } 
}


void serit_callback( const std_msgs::Float64& lane){

  int serit_enabled;
  serit_enabled = lane.data;
  float adim;
  float derece;
  
  adim = derece*35,77777778;
  if(serit_enabled != 0){
    nh.loginfo("geldi");
    //stepper.step(-stepsPerRevolution); //Freni birak
    ilerifonk(); //Vites ileri
    analogWrite(9,150); //5km hizda git

    if(derece > 0){
        sagadonfonk();

    }
    else if(derece < 0){
        soladonfonk();

    }
    
  }
  
  else {
    analogWrite(9,175); //Gazi kes
    //stepper.step(stepsPerRevolution); //Frene bas
    bosfonk(); //Vites bosa
    
}

}

void YoloFunc( const std_msgs::String& yolo){
    
    
    String yolodata = "";
    yolodata = yolo.data;
  if(yolodata == "girisi_olmayan_yol"){
    nh.loginfo("YOLO Aktif");
    
    analogWrite(9,175);
    //stepper.step(stepsPerRevolution);
    bosfonk();
  }
    
    
  }




ros::Subscriber<sensor_msgs::Joy> joy("joy", &callbackFn );
ros::Subscriber<std_msgs::Float64> serit_takip("serit_takip", &serit_callback );
ros::Publisher button_publisher("button_press", &button_msg);
ros::Subscriber<std_msgs::String> sub_levha("sub_levha", &YoloFunc);



void setup() {
Serial.begin(57600);
 pinMode(ileri,OUTPUT);
 pinMode(geri,OUTPUT);
 myStepper.setSpeed(250);
 stepper.setSpeed(175); //fren
 bosfonk();
 nh.advertise(button_publisher);
 nh.initNode();

 pinMode(10,INPUT);

 //while(INITIAL_FLAG) {

 // mStepper.setSpeed(60);
 // mStepper.step(-10);


// if (digitalRead(10)) {
//

//  Serial.println("BASILDI");

 // INITIAL_FLAG=0;

 // delay(1109);
  // }
  //}
  
 // mStepper.step(S);
}

long sagadonfonk() {
  
  myStepper.step(-TARIK);
}

long soladonfonk() {
  
 myStepper.step(TARIK);
 
}

void loop() {
  

  nh.subscribe(joy);
  nh.subscribe(serit_takip);
  nh.subscribe(sub_levha);
  nh.spinOnce();
}
