#include <fstream>
#include <iostream>

#include <rclcpp/rclcpp.hpp>
#include <tf2/exceptions.h>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
 
using namespace std;
 
ofstream foutC;
 
 
int main(int argc, char **argv){
    //string file_name;
    //ros::param::get("file_name",file_name);
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("save_traj_as_tum");
    
    foutC.open("./test.txt");
    tf2_ros::Buffer tf_buffer(node->get_clock());
    tf2_ros::TransformListener listener(tf_buffer);//在ROS中，TransformListener 用于接收和处理变换（transform）信息，它可以监听并处理来自TF库（Transform Library）的变换信息
    rclcpp::Rate rate(20.0);
    while(rclcpp::ok()){
        try
        {
            //等待获取从 "/odom" 到 "/base_link" 的坐标变换信息
            //获取从 "/odom" 到 "/base_link" 的坐标变换信息，并将其存储在 transform 变量中
            auto transform = tf_buffer.lookupTransform(
                "camera_init",
                "aft_mapped",
                tf2::TimePointZero);
            foutC << rclcpp::Time(transform.header.stamp).seconds() << " ";//变换时间戳 transform.stamp_ 写入到输出流 foutC 中
            float x = transform.transform.translation.x;
            float y = transform.transform.translation.y;
            float z = transform.transform.translation.z;
            float qx = transform.transform.rotation.x;
            float qy = transform.transform.rotation.y;
            float qz = transform.transform.rotation.z;
            float qw = transform.transform.rotation.w;
            RCLCPP_INFO(node->get_logger(), "%f %f %f %f %f %f %f", x, y, z, qx, qy, qz, qw);
            foutC << x <<" " << y << " " << z << " " << qx << " " << qy << " " << qz << " " << qw << std::endl;
        }
        catch(const tf2::TransformException& e)
        {
            RCLCPP_WARN(node->get_logger(), "%s", e.what());
        }
        rate.sleep();
    }
    foutC.close();
    rclcpp::shutdown();
    return 0;
}
