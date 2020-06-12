#include <ros/ros.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>

using namespace message_filters;

std::string name[3]={"a","b","c"};


ros::Subscriber sub[3];


//plan A to subscirber(use the msg data to distingish)
/**
void subcallback(const geometry_msgs::Vector3::ConstPtr& msg)
{
	int i;
	double j, k;
	i = (int)msg->x ;
	j = msg->y ;
	k = msg->z ;
	switch(i)
	{
		case 0:ROS_INFO("topic1 has been received, y=%f, z=%f", j, k);
			break;
		case 1:ROS_INFO("topic2 has been received, y=%f, z=%f", j, k);
			break;
		case 2:ROS_INFO("topic3 has been received, y=%f, z=%f", j, k);
			break;
	}

}*/


//plan B to subscriber(use message_filter )

void subcallback(const geometry_msgs::Vector3Stamped::ConstPtr& msg0, const geometry_msgs::Vector3Stamped::ConstPtr& msg1, const geometry_msgs::Vector3Stamped::ConstPtr& msg2)
{
	double i, j, k;
	ROS_INFO("RECEIVE!");
	i = msg0->vector.x;
	j = msg1->vector.x;
	k = msg2->vector.x;
	ROS_INFO("topic2 has been received, a=%f, b=%f, c=%f", i, j, k);
}



int main(int argc, char** argv)
{
	//specify variables
	double a, b, c;
	
	ros::init(argc, argv, "subscribe");
	ros::NodeHandle nh;
	/**for(int i=0; i<3; i++)
	{
		//sub[i] = nh.subscribe(name[i], 1, subcallback);	//Plan A to subscribe

		//sub[i] = nh.subscribe<geometry_msgs::Vector3>(name[i], 1);

		sub[i] = nh.subscribe(name[i], 1, subcallback);	//Plan C to subscribe
	}*/
	
	message_filters::Subscriber<geometry_msgs::Vector3Stamped> sub0(nh, name[0], 1);	//Plan B to subscribe
	message_filters::Subscriber<geometry_msgs::Vector3Stamped> sub1(nh, name[1], 1);	//Plan B to subscribe
	message_filters::Subscriber<geometry_msgs::Vector3Stamped> sub2(nh, name[2], 1);	//Plan B to subscribe
	TimeSynchronizer<geometry_msgs::Vector3Stamped, geometry_msgs::Vector3Stamped, geometry_msgs::Vector3Stamped> sync(sub0, sub1, sub2, 10);
	sync.registerCallback(boost::bind(&subcallback, _1, _2, _3));

	while(ros::ok)ros::spinOnce();

	return 0;


}
