#include <ros.h>
#include <dht.h>
#include <sensor_msgs/Temperature.h>
#include <sensor_msgs/RelativeHumidity.h>

ros::NodeHandle  nh;

sensor_msgs::Temperature temp_msg;
sensor_msgs::RelativeHumidity humidity_msg;

ros::Publisher pub_temp("temperature", &temp_msg);
ros::Publisher pub_humidity("humidity", &humidity_msg);



////Variables y Constantes

dht DHT;
#define DHT11_PIN 2;


void setup()
{
  nh.initNode();
  nh.advertise(pub_temp);
  nh.advertise(pub_humidity);
  long publisher_timer = 0;
  temp_msg.header.frame_id = "/base_link"; //le di el formato la mensaje
  humidity_msg.header.frame_id = "/base_link"; //le di el formato la mensaje
  Serial.begin(115200);
} 


void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  Serial.print(DHT.temperature);
  temp_msg.temperature = (DHT.temperature); 
  pub_temp.publish( &temp_msg );
  Serial.print(DHT.humidity);
  humidity_msg.relative_humidity = (DHT.humidity);
  pub_humidity.publish( &humidity_msg );
  delay(2000);
  nh.spinOnce();
}
