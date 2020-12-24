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
      auto topic = handle.advertise<int, float, float, int>("test");

      int i = 100000;
      while (--i)
      {
        topic->publish(i, i + 1.1, i * 2.1, 3);
      }
    });
  }

  void join()
  {
    t.join();
  }
};

#endif
