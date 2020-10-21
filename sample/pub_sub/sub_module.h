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
    t = std::thread([]()
    {
      tiny_ros::NodeHandle& handle = tiny_ros::NodeHandle::Instance();

      auto sub_callback = [](int data, int c)
      {
        std::cout << "sub_callback:" << data << std::endl;
      };

      handle.subscribe<MESSAGE_TYPE(int, int)>("test", sub_callback);
    });
  }
  void join()
  {
    t.join();
  }
};


#endif
