#include "client_module.h"
#include "server_module.h"

int main()
{
  tiny_ros::init();
  ServerModule sm;
  ClientModule cm;
  sm.join();
  cm.join();
  return 0;
}
