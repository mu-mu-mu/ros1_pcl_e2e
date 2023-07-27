#include "ros/ros.h"
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <unistd.h>
#include <csignal>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/PointCloud.h>
#include <std_msgs/Int32.h>
#include <pcl_conversions/pcl_conversions.h>

#include "util.h"

ros::Publisher int_pub;

void intmCallback(const sensor_msgs::PointCloud2::ConstPtr& msg)
{
  pcl::PointCloud<velodyne_ros::Point> _msg;
  pcl::fromROSMsg(*msg, _msg);

  int seq = msg->header.seq;
  std_msgs::Int32 s;
  s.data = seq;
  int_pub.publish(s);
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "intm");

  ros::NodeHandle n;
  int_pub = n.advertise<std_msgs::Int32>("end", 1000);

  ros::Subscriber sub = n.subscribe("intm", 1000, intmCallback);

  ros::spin();
  return 0;
}
