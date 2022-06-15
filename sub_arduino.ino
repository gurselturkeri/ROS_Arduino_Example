
#include <ros.h>
#include <std_msgs/Float64.h>
ros::NodeHandle nh;
void value1_callback( const std_msgs::Float64& val1);
void value2_callback( const std_msgs::Float64& val2);


void value1_callback( const std_msgs::Float64& val1){

  nh.loginfo("bbbbb");
}

void value2_callback( const std_msgs::Float64& val2){

  nh.loginfo("aaaa");
  
}









ros::Subscriber<std_msgs::Float64> value1("value1", &value1_callback );
ros::Subscriber<std_msgs::Float64> value2("value2", &value2_callback );


void setup() {
Serial.begin(57600);
nh.initNode();

}

void loop() {
nh.subscribe(value1);
nh.subscribe(value2);
nh.spinOnce();

}
