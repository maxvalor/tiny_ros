#ifndef PUB_MODULE_H_
#define PUB_MODULE_H_

#include <tiny_ros/tiny_ros.h>
#include <thread>
#include <iostream>
#include <sys/time.h>

class PubModule
{
  std::thread t;

public:
  PubModule()
  {
    t = std::thread([]()
    {
      tiny_ros::NodeHandle& handle = tiny_ros::NodeHandle::Instance();
      auto topic = handle.advertise<int, int>("test");

      int i = 1000000;
      while (--i)
      {
        topic->publish(i, i * -1);
      }
    });
  }

  void join()
  {
    t.join();
  }
};

#endif
