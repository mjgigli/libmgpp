#ifndef __mgpp_signals_event_hpp__
#define __mgpp_signals_event_hpp__

namespace mgpp {
namespace signals {

class Event {
   public:
      Event(int id) : id_(id) {}
      virtual ~Event() {}

      int id() const
      {
         return id_;
      }

   private:
      const int id_;
};

using EventPtr = std::shared_ptr<Event>;
using EventConstPtr = std::shared_ptr<const Event>;

template <typename T, typename... Args>
std::shared_ptr<T> make_event(Args... args)
{
   return std::make_shared<T>(args...);
}

}  // namespace signals
}  // namespace mgpp

#endif  // __mgpp_signals_event_hpp__
