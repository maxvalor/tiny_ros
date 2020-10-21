#ifndef SERVER_MODULE_H_
#define SERVER_MODULE_H_

#include <tiny_ros/tiny_ros.h>
#include <iostream>

class ServerModule
{
public:
  ServerModule()
  {
    tiny_ros::NodeHandle& handle = tiny_ros::NodeHandle::Instance();
    handle.advertiseService<SERVICE_TYPE(int, int*)>("add_1", [](int x, int *rlt)
    {
      *rlt = x + 1;
      return true;
    });
  }

  void join() {}
};

#endif
