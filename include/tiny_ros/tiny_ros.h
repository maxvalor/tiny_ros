#ifndef TINY_ROS_H
#define TINY_ROS_H

#include <vector>
#include <unordered_map>
#include <string>
#include <mutex>

namespace tiny_ros
{
using lock_guard = std::lock_guard<std::mutex>;

template <typename T>
class Topic
{
  std::mutex mtx;
  std::vector<T> subscribers;
  friend class NodeHandle;
public:
  template <typename ...PARAMS>
  void publish(PARAMS... msg)
  {
    lock_guard lck(mtx);
    for (auto subscriber : subscribers)
      subscriber(msg...);
  }
};

template <typename T>
class Service
{
  T f;
  friend class NodeHandle;
public:
  template <typename ...PARAMS>
  bool call(PARAMS... srv)
  {
    f(srv...);
  }
};

class NodeHandle
{
  std::unordered_map<std::string, void*> topics;
  std::unordered_map<std::string, void*> srvs;
  static NodeHandle* singleton;
  std::mutex topic_mtx;
  std::mutex srv_mtx;

private:
  template <typename T>
  Topic<T>* resovle(std::string& name)
  {
    Topic<T> *topic = nullptr;
    try
    {
      auto origin_topic = topics.at(name);
      topic = (Topic<T>*)origin_topic;
    }
    catch(...)
    {
      topic = new Topic<T>();
      topics.insert(std::pair<std::string, void*>(name, (void*)topic));
    }
    return topic;
  }
public:
  static NodeHandle& Instance()
  {
    if (singleton == nullptr)
    {
      singleton = new NodeHandle();
    }

    return *singleton;
  }
  template <typename T>
  Topic<T>* advertise(std::string name)
  {
    lock_guard lck(topic_mtx);
    auto topic = resovle<T>(name);
    return topic;
  }

  template <typename T>
  void subscribe(std::string name, T&& func)
  {
    lock_guard lck(topic_mtx);
    auto topic = resovle<T>(name);
    lock_guard tlck(topic->mtx);
    topic->subscribers.push_back(func);
  }

  template <typename T>
  void advertiseService(std::string name, T&& func)
  {
    lock_guard lck(srv_mtx);
    auto srv = new Service<T>();
    srv->f = func;
    srvs.insert(std::pair<std::string, void*>(name, (void*)srv));
  }

  template <typename T>
  Service<T> *serviceClient(std::string name)
  {
    lock_guard lck(srv_mtx);
    try
    {
      auto origin_srv = srvs.at(name);
      auto srv = (Service<T>*)origin_srv;
      return srv;
    }
    catch(...) {}

    return nullptr;
  }
};

NodeHandle* NodeHandle::singleton = nullptr;

#define MESSAGE_TYPE(...) std::function<void(__VA_ARGS__)>
#define SERVICE_TYPE(...) std::function<bool(__VA_ARGS__)>

void init() { NodeHandle::Instance(); }
}

#endif
