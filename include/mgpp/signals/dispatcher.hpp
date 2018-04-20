#ifndef __mgpp_signals_dispatcher_hpp__
#define __mgpp_signals_dispatcher_hpp__

#include <unordered_map>
#include <memory>
#include <boost/signals2.hpp>

#include <mgpp/signals/event.hpp>

namespace mgpp {
namespace signals {

// Define callback templates and pointer types
using EventCallbackTemplate = void (EventConstPtr);
using EventCallback = std::function<EventCallbackTemplate>;
template <typename T> using EventMemberCallback = void (T::*)(EventConstPtr);

// Use boost signals2 signals/slots for the event dispatcher
typedef boost::signals2::signal<EventCallbackTemplate> EventSignal;
typedef boost::signals2::connection Connection;

// subscribe functions
Connection subscribe(const int id, const EventCallback cb);

template <typename T>
Connection subscribe(const int id, const EventMemberCallback<T> mcb, T& obj)
{
   return subscribe(id, boost::bind(mcb, &obj, _1));
}

// unsubscribe functions
void unsubscribe(const int id, const Connection& conn);

// unsubscribe_all function
void unsubscribe_all(const int id = -1);

// publish function
void publish(EventConstPtr event);

int num_slots(const int id);

}  // namespace signals
}  // namespace mgpp

#endif  // __mgpp_signals_dispatcher_hpp__
