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

      auto sub_callback = [](int data1, float data2, float data3, int data4)
      {
        std::cout << "sub_callback: ("
            << data1  << ", "
            << data2  << ", "
            << data3  << ", "
            << data4  << ")"
            << std::endl;

      };
      handle.subscribe<int, float, float, int>("test", sub_callback);

      /*
      handle.subscribe<int, float, float, int>("test", [](int data1, float data2, float data3, int data4)
      {
        std::cout << "sub_callback: ("
            << data1  << ", "
            << data2  << ", "
            << data3  << ", "
            << data4  << ")"
            << std::endl;

      });

      handle.subscribe<int, float, float, int>("test",
        std::bind(&SubModule::callback, this, std::placeholders::_1
            , std::placeholders::_2
            , std::placeholders::_3
            , std::placeholders::_4)
      );
      */
    });
  }

  void callback(int, float, float, int) {};

  void join()
  {
    t.join();
  }
};


#endif
