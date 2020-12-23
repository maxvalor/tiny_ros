#ifndef CLIENT_MODULE_H_
#define CLIENT_MODULE_H_

#include <tiny_ros/tiny_ros.h>
#include <thread>
#include <iostream>

class ClientModule
{
  std::thread t;

public:
  ClientModule()
  {
    t = std::thread([]()
    {
      int i = 100;

      while (--i)
      {
        tiny_ros::NodeHandle& handle = tiny_ros::NodeHandle::Instance();
        auto srv = handle.serviceClient<int, int*>("add_1");
        if (srv != nullptr)
        {
          int rlt = 0;
          if (srv->call(i, &rlt))
          {
            std::cout << "value of rlt:" << rlt << std::endl;
          }
          else
          {
            std::cout << "return false." << std::endl;
          }
        }
        else
        {
          std::cout << "error of srv." << std::endl;
        }
      }
    });
  }

  void join()
  {
    t.join();
  }
};


#endif
