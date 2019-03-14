#include <ros/ros.h>
#include "std_msgs/String.h"
#include <visualization_msgs/Marker.h>
#include <delphi_esr_msgs/EsrTrack.h>
 
class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //Topic you want to publish
    pub_ = n_.advertise<delphi_esr_msgs::EsrTrack>("observer", 1000);
    //n_.advertise<PUBLISHED_MESSAGE_TYPE>("/published_topic", 1);
 
    //Topic you want to subscribe
    sub_ = n_.subscribe("/parsed_tx/radartrack", 1000, &SubscribeAndPublish::Callback,this);
    //n_.subscribe("/subscribed_topic", 1, &SubscribeAndPublish::callback, this);
  }
 
  //void callback(const SUBSCRIBED_MESSAGE_TYPE& input)
  //{
  //  PUBLISHED_MESSAGE_TYPE output;
    //.... do something with the input and generate the output...
  //  pub_.publish(output);
  //}
  void Callback(const delphi_esr_msgs::EsrTrack input)
  {
    /**
     * 这是一个回调函数，当接收到 chatter 话题的时候就会被调用。
     * 消息是以 boost shared_ptr 指针的形式传输，这就意味着你可以存储它而又不需要复制数据。 
     */
    //geometry_msgs::Point p=msg.points[msg.points.size()-1];
    //ROS_INFO("Hello callback");
    //ROS_INFO("I heard:x=%f",msg.pose.position.x);
    //ROS_INFO();
    delphi_esr_msgs::EsrTrack output;
    //output = input;
    if (input.track_range < 40)
        output = input;
        output.header.frame_id = "base_link";
    pub_.publish(output);
  }

 
private:
  ros::NodeHandle n_; 
  ros::Publisher pub_;
  ros::Subscriber sub_;
 
};//End of class SubscribeAndPublish
 
int main(int argc, char **argv)
{
  //Initiate ROS
  ros::init(argc, argv, "subscribe_and_publish");
 
  //Create an object of class SubscribeAndPublish that will take care of everything
  SubscribeAndPublish SAPObject;
 
  ros::spin();
 
  return 0;
}

/**
 * 我们来总结一下:
 * - 初始化ROS系统
 * - 定义节点类
 * -- 订阅话题
 * -- 处理数据
 * -- 发布话题
 * - 进入自循环，等待消息的到达
 * - 当消息到达，调用 Callback() 函数 
 */
