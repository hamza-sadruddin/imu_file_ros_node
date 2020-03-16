#include <iostream>
#include <ros/ros.h>
#include <fstream>
#include <sensor_msgs/Imu.h>
#include <sys/stat.h>

using namespace std;

typedef double Double64;


/* Accelerometer and Gyroscope data */
typedef struct EmsIcdImuRosStruct
{
	Double64	time_tag;		//system time (seconds)
	Double64	q_x;
	Double64	q_y;
	Double64	q_z;
	Double64	q_w;
	Double64	gyro_x;			//deg/sec
	Double64	gyro_y;			//deg/sec
	Double64	gyro_z;			//deg/sec
	Double64	acc_x;			//m/sec^2
	Double64	acc_y;			//m/sec^2
	Double64	acc_z;			//m/sec^2
}	EmsIcdImuRos, * EmsIcdImuRosPtr;


int main(int argc, char **argv) {

	ROS_INFO("IMU_FILE\n\n");
	
	int lines = 10083;

	EmsIcdImuRosStruct EmsIcdImuRos[lines];

	std::ifstream imu_data_file("/home/ems/catkin_ws/src/imu_file/src/imu_custom.csv");
	
	struct stat statbuf;
	if(stat("/home/ems/catkin_ws/src/imu_file/src/imu_custom.csv", &statbuf) == -1){
		}
	cout << "File Size: " << (intmax_t) statbuf.st_size << endl;
	
	char comma;
	int imu_file_counter = 0;

	if (imu_data_file.is_open())
	{
		cout << "File Opened Successfully" << endl;
		
		//~ while (!imu_data_file.eof()) {
		while (imu_file_counter < lines) {
			
			
			imu_data_file >> EmsIcdImuRos[imu_file_counter].time_tag >> comma >> EmsIcdImuRos[imu_file_counter].q_x >> comma >> EmsIcdImuRos[imu_file_counter].q_y >> comma >>
				EmsIcdImuRos[imu_file_counter].q_z >> comma >> EmsIcdImuRos[imu_file_counter].q_w >> comma >> EmsIcdImuRos[imu_file_counter].gyro_x >> comma >>
				EmsIcdImuRos[imu_file_counter].gyro_y >> comma >> EmsIcdImuRos[imu_file_counter].gyro_z >> comma >> EmsIcdImuRos[imu_file_counter].acc_x >> comma >>
				EmsIcdImuRos[imu_file_counter].acc_y >> comma >> EmsIcdImuRos[imu_file_counter].acc_z;
			
			cout << EmsIcdImuRos[imu_file_counter].time_tag <<endl;
			
			imu_file_counter++;
			
			

		}
	}
	else {
		cout << "Error File Opening" << endl;
	}

	imu_data_file.close();
	
	cout << "File read successfully\n";
	
	ros::init(argc, argv, "imu_file_node");
	ros::NodeHandle n;
	
	ros::Publisher imu_file_pub = n.advertise<sensor_msgs::Imu>("imu", 100);
	ros::Rate loop_rate(100);
	
	
	int count = 0;
	while (ros::ok() && imu_file_counter!= count)
	{

		sensor_msgs::Imu imu;

		imu.header.stamp = ros::Time(EmsIcdImuRos[count].time_tag);
		imu.header.frame_id = "imu_link";

		imu.orientation_covariance = {0};
		imu.angular_velocity_covariance = {0};
		imu.linear_acceleration_covariance = {0};

		imu.orientation.x = EmsIcdImuRos[count].q_x;
		imu.orientation.y = EmsIcdImuRos[count].q_y;
		imu.orientation.z = EmsIcdImuRos[count].q_z;
		imu.orientation.w = EmsIcdImuRos[count].q_w;

		imu.angular_velocity.x = EmsIcdImuRos[count].gyro_x;
		imu.angular_velocity.y = EmsIcdImuRos[count].gyro_y;
		imu.angular_velocity.z = EmsIcdImuRos[count].gyro_z;

		imu.linear_acceleration.x = EmsIcdImuRos[count].acc_x;
		imu.linear_acceleration.y = EmsIcdImuRos[count].acc_y;
		imu.linear_acceleration.z = EmsIcdImuRos[count].acc_z;

		imu_file_pub.publish(imu);

		ros::spinOnce();

		loop_rate.sleep();
		++count;
	}

	ROS_INFO("\nDONE\n\n");

	return 0;
}
