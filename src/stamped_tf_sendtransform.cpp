#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/PoseStamped.h>

void PoseCallback(const geometry_msgs::PoseStamped& msg)
{
  static tf2_ros::TransformBroadcaster br;
  geometry_msgs::TransformStamped transformStamped;
  
  transformStamped.header.stamp = msg.header.stamp;
  transformStamped.header.frame_id = msg.header.frame_id; //parent frame id 
  transformStamped.child_frame_id = "/Robot_1/base_link_stamped";

  transformStamped.transform.translation.x = msg.pose.position.x;
  transformStamped.transform.translation.y = msg.pose.position.y;
  transformStamped.transform.translation.z = msg.pose.position.z;
  transformStamped.transform.rotation.x = msg.pose.orientation.x;
  transformStamped.transform.rotation.y = msg.pose.orientation.y;
  transformStamped.transform.rotation.z = msg.pose.orientation.z;
  transformStamped.transform.rotation.w = msg.pose.orientation.w;
  //transformStamped.transform = msg->transform;

  br.sendTransform(transformStamped);
}

int main(int argc, char** argv){
  ros::init(argc, argv, "stamped_tfPose");

  ros::NodeHandle node;

  ros::Subscriber sub;

  sub = node.subscribe("/Robot_1/pose", 10, &PoseCallback);
  

  ros::spin();
  return 0;
};
