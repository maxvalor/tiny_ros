#ifndef SUB_MODULE_H_
#define SUB_MODULE_H_

#include <tiny_ros/tiny_ros.h>
#include <thread>
#include <iostream>

class SubModule
{
  std::thread t;
public:
  SubModule()
  {
    t = std::thread([this]()
    {
      tiny_ros::NodeHandle& handle = tiny_ros::NodeHandle::Instance();

      auto sub_callback = [](int data)
      {
        std::cout << "sub_callback:" << data << std::endl;
      };

      handle.subscribe<int>("test", sub_callback);
    });
  }

  void callback(int data) {};

  void join()
  {
    t.join();
  }
};


#endif
