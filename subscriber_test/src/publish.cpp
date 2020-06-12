#include <ros/ros.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <geometry_msgs/Vector3.h>

std::string name[3]={"a","b","c"};
ros::Publisher pub[3];
geometry_msgs::Vector3Stamped msg[3];



int main(int argc, char** argv)
{
	ros::init(argc, argv, "publish");
	ros::NodeHandle nh;
	for(int i=0; i<3; i++)
	{
		
		pub[i] = nh.advertise<geometry_msgs::Vector3Stamped>(name[i], 1);
		msg[i].header.stamp = ros::Time::now();
		msg[i].header.frame_id = name[i];
		msg[i].vector.x = i;
		msg[i].vector.y = i+1;
		msg[i].vector.z = i+1;
	}

	ros::Rate loop(10);	//10hz 

	while(ros::ok)
	{
		for(int i=0; i<3; i++)
		pub[i].publish(msg[i]);

		loop.sleep();

	}
	

	return 0;

}
