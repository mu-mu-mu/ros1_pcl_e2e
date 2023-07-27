#include "ros/ros.h"
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <unistd.h>
#include <csignal>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/PointCloud.h>
#include <std_msgs/Int32.h>

#define NUM 0x100

//ros::Time begin[NUM];

void endCallback(const std_msgs::Int32::ConstPtr& msg)
{
  //ros::Time end = ros::Time::now();
  //ros::Duration d = end - begin[msg->data];
  ros::Time now = ros::Time::now();

  ROS_INFO("cb end %d %ld", msg->data, now.toNSec()/1000);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "end");

  ros::NodeHandle n;
  //ros::Publisher pc_pub = n.advertise<sensor_msgs::PointCloud2>("intm", 1000);

  ros::Subscriber sub = n.subscribe("end", 1000, endCallback);
  ros::spin();

  return 0;
}
