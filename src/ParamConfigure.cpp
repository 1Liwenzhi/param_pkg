#include "ros/ros.h"
#include "param_pkg/paramConfig.h"
#include "dynamic_reconfigure/server.h"
#include "param_pkg/Dynamicparam.h"

param_pkg::Dynamicparam msg;

void CallBack(param_pkg::paramConfig &config, uint32_t level){

    msg.Gammam = config.Gamma;
    msg.lamda = config.lamda;

    msg.KD[0] = config.KD1;
    msg.KD[1] = config.KD2;
    msg.KD[2] = config.KD3;

    msg.KDTu[0] = config.KDTu1;
    msg.KDTu[1] = config.KDTu2;
    msg.KDTu[2] = config.KDTu3;

    msg.lamdaTu[0] = config.lamdaTu1;
    msg.lamdaTu[1] = config.lamdaTu2;
    msg.lamdaTu[2] = config.lamdaTu3;

    msg.GammamTu[0] = config.GammaTu1;
    msg.GammamTu[1] = config.GammaTu2;
    msg.GammamTu[2] = config.GammaTu3;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");

    ros::init(argc, argv,"DynamicParam");

    ros::NodeHandle _nh;

    ros::Rate rate(10);//发布频率

    ros::Publisher pub = _nh.advertise<param_pkg::Dynamicparam>("/data_config",100);

    dynamic_reconfigure::Server<param_pkg::paramConfig> server;
    dynamic_reconfigure::Server<param_pkg::paramConfig>::CallbackType callback = boost::bind(&CallBack,_1,_2);

    server.setCallback(callback);

    while (ros::ok())
    {
        pub.publish(msg); 

        rate.sleep();

        ros::spinOnce();
    }

    ros::spin();

    return 0;
}