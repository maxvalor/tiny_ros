#include <tiny_ros/tiny_ros.h>
#include "pub_module.h"
#include "sub_module.h"

int main()
{
  tiny_ros::init();
  PubModule pm;
  SubModule sm;
  pm.join();
  sm.join();
  return 0;
}
