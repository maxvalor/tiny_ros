#ifndef TINY_ROS_H
#define TINY_ROS_H

#include <vector>
#include <unordered_map>
#include <string>
#include <mutex>

namespace tiny_ros
{
using lock_guard = std::lock_guard<std::mutex>;

template <typename... T>
class Topic
{
  std::mutex mtx;
  std::vector<std::function<void(T...)>> subscribers;
  friend class NodeHandle;

  template <typename F>
  void addSubscriber(F&& f)
  {
    lock_guard lck(mtx);
    subscribers.emplace_back(f);
  }
public:
  void publish(T... msg)
  {
    lock_guard lck(mtx);
    for (auto subscriber : subscribers)
    {
      subscriber(msg...);
    }
  }
};

template <typename... T>
class Service
{
  std::function<bool(T...)> f;
  friend class NodeHandle;
public:
  bool call(T... srv)
  {
    f(srv...);
  }
};

class NodeHandle
{
  static NodeHandle* singleton;
  std::unordered_map<std::string, void*> topics;
  std::unordered_map<std::string, void*> srvs;
  std::mutex topic_mtx;
  std::mutex srv_mtx;

private:
  template <typename... T>
  Topic<T...>* resovle(std::string& name)
  {
    Topic<T...> *topic = nullptr;
    try
    {
      auto origin_topic = topics.at(name);
      topic = (Topic<T...>*)origin_topic;
    }
    catch(...)
    {
      topic = new Topic<T...>();
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
  template <typename... T>
  Topic<T...>* advertise(std::string name)
  {
    std::lock_guard<std::mutex> lck(topic_mtx);
    auto topic = resovle<T...>(name);
    return topic;
  }

  template <typename... T, typename F>
  void subscribe(std::string name, F&& f)
  {
    std::lock_guard<std::mutex> lck(topic_mtx);
    auto topic = resovle<T...>(name);
    topic->addSubscriber(f);
  }

  template <typename... T, typename F>
  void advertiseService(std::string name, F&& f)
  {
    std::lock_guard<std::mutex> lck(srv_mtx);
    auto *srv = new Service<T...>();
    srv->f = f;
    srvs.insert(std::pair<std::string, void*>(name, (void*)srv));
  }

  template <typename... T>
  Service<T...> *serviceClient(std::string name)
  {
    std::lock_guard<std::mutex> lck(srv_mtx);
    try
    {
      auto origin_srv = srvs.at(name);
      auto srv = (Service<T...>*)origin_srv;
      return srv;
    }
    catch(...) {}

    return nullptr;
  }
};

NodeHandle* NodeHandle::singleton = nullptr;

void init() { NodeHandle::Instance(); }
}

#endif
