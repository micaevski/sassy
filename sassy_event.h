#pragma once

#include "sassy_event_properties.h"

#include <vector>
#include <functional>
#include <variant>
#include <queue>

namespace sassy
{
template <typename T>
using Callback = std::function<void(const T &)>;

template <typename T>
std::vector<Callback<T>> &event_callbacks()
{
  static std::vector<Callback<T>> s_listeners;
  return s_listeners;
}

template <typename T>
struct Event
{
  static void add_listener(Callback<T> callback)
  {
    event_callbacks<T>().push_back(callback);
  }
  static void notify(const T &payload)
  {
    for (auto &callback : event_callbacks<T>())
      callback(payload);
  }
};

template <typename T>
void dispatch(const T &event)
{
  Event<T>::notify(event);
}

template <typename... Events>
void dispatch(const std::variant<Events...> &event)
{
  std::visit([](auto &&arg) { dispatch(arg); }, event);
}

template <typename... Events>
using Queue = std::queue<std::variant<Events...>>;
} // namespace sassy

////////////////////////////////////////////////////////////////////////////////////////

