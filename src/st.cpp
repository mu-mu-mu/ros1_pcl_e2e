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


int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Too few argument\n");
    return 1;
  }
  char *file_path = argv[1];

  rosbag::Bag bag(file_path, rosbag::bagmode::Read);

  argc = 1;
  argv[1] = NULL;
  ros::init(argc, argv, "st_end");

  ros::NodeHandle n;
  ros::Publisher pc_pub = n.advertise<sensor_msgs::PointCloud2>("intm", 1000);


  ros::Rate loop_rate(100);
  int cnt = 0;
  for (const rosbag::MessageInstance &m : rosbag::View(bag)) {
    auto msg = m.instantiate<sensor_msgs::PointCloud2>();

    if (msg) {
      msg->header.seq = cnt;
      cnt++;

      pcl::PointCloud<velodyne_ros::Point> pl_orig;
      pcl::fromROSMsg(*msg, pl_orig);
      sensor_msgs::PointCloud2 conv_msg;

      ros::Time now = ros::Time::now();
      pcl::toROSMsg(pl_orig, conv_msg);
      ROS_INFO("cb start %d %ld", msg->header.seq, now.toNSec()/1000);
      pc_pub.publish(conv_msg);

      ros::spinOnce();
      loop_rate.sleep();
    }
  }
  return 0;
}
