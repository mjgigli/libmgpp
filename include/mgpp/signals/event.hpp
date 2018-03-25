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

}  // namespace signals
}  // namespace mgpp

#endif  // __mgpp_signals_event_hpp__
