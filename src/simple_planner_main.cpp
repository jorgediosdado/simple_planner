#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/Pose.h>
#include "leica_ts12/tsData.h"
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>

#include <vector>

leica_ts12::tsData currentPosition;

void totalStationCallback(const leica_ts12::tsData& tsmsg)
{
   currentPosition=tsmsg;
}

int main(int argc, char* argv[])
{
  double hexapodHeight=1;
  int pointsPath=10;
  nav_msgs::Path path;
  double distance[pointsPath];
  geometry_msgs::Twist outputVel;
  double kp;
  double kv;
  geometry_msgs::PoseStamped poseMsg[10];
  
  //Filling the path
  poseMsg[0].pose.position.x=0.2;
  poseMsg[0].pose.position.y=0.2;  
  poseMsg[1].pose.position.x=0.2;
  poseMsg[1].pose.position.y=0.4;  
  poseMsg[2].pose.position.x=0.2;
  poseMsg[2].pose.position.y=0.6;  
  poseMsg[3].pose.position.x=0.2;
  poseMsg[3].pose.position.y=0.8;   
  poseMsg[4].pose.position.x=0.2;
  poseMsg[4].pose.position.y=1;
  poseMsg[5].pose.position.x=0.2;
  poseMsg[5].pose.position.y=1.2;   
  poseMsg[6].pose.position.x=0.2;
  poseMsg[6].pose.position.y=1.4;  
  poseMsg[7].pose.position.x=0.2;
  poseMsg[7].pose.position.y=1.6;  
  poseMsg[8].pose.position.x=0.2;
  poseMsg[8].pose.position.y=1.8;   
  poseMsg[9].pose.position.x=0.2;
  poseMsg[9].pose.position.y=2;

  for (int i=0;i<pointsPath;i++)
  {
    poseMsg[i].pose.position.z=hexapodHeight;
  }
  for (int i=0;i<pointsPath;i++)
  {
    path.poses.push_back(poseMsg[i]);
  }  
  ros::init(argc, argv, "simple_planner");
  ros::NodeHandle n;
  ros::Subscriber subscriber = n.subscribe("ts_data", 1, totalStationCallback); 
  ros::Publisher publisher = n.advertise<geometry_msgs::Twist >("desired_velocity_planner",300);
  ros::Rate r(5);
  
  while(ros::ok())
  {
      
    
    for(int i=0; i<pointsPath ; i++)
    {
      distance[i] =sqrt(pow(path.poses[i].pose.position.x-currentPosition.point.x,2) + pow(path.poses[i].pose.position.y-currentPosition.point.y,2) + pow(path.poses[i].pose.position.z-currentPosition.point.z,2));
    }
   
    std::cout << "The smallest element is " << *std::min_element(distance,distance + pointsPath) << '\n';    
    //std::min_element(distance,distance + pointsPath);    
    //outputVel.linear.x=kp(*(std::min_element(distance,distance + pointsPath)++)-currentPosition.point.x);
    
    ros::spinOnce();
    r.sleep();
    
  }
    
}


