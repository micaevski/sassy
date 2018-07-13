
#include "sassy_event.h"
#include <iostream>
#include <string>

struct EventX : sassy::Event<EventX>
{
  std::string data;
  EventX(std::string d) : data(d) {}
};

struct EventY : sassy::Event<EventY>, sassy::properties::Indexed<EventY>
{
  std::string data;
  EventY(std::string d) : data(d) {}
};

int main()
{
  EventX::add_listener([](const EventX &event) { std::cout << event.data << "\n"; });
  EventY::add_listener([](const EventY &event) { std::cout << event.data << " - " << event.index << " from first listener.\n";  });
  EventY::add_listener([](const EventY &event) { std::cout << event.data << " - " << event.index << " from second listener.\n"; });

  EventX x{"Event X"};
  EventY y{"Event Y"};
  EventY y2{"Event Y"};

  sassy::Queue<EventX, EventY> q;
  
  q.push(x);
  q.push(y);
  q.push(y2);

  while (!q.empty())
  {
    auto event = q.front();
    q.pop();
    sassy::dispatch(event);
  }
}
