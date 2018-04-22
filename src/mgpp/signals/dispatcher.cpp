/*
 * Copyright (c) 2018 Matt Gigli
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE
 * SOFTWARE.
 */

#include <mgpp/signals/dispatcher.hpp>

namespace mgpp {
namespace signals {

// singleton dispatcher class
class Dispatcher {
   public:
      Connection subscribe(const int id, const EventCallback cb);
      void unsubscribe(const int id, const Connection& conn);
      void unsubscribe_all(const int id = -1);
      void publish(EventConstPtr event);
      int num_slots(const int id);

      static Dispatcher& instance()
      {
         static Dispatcher dispatcher;
         return dispatcher;
      }

   private:
      Dispatcher();
      ~Dispatcher();
      Dispatcher(const Dispatcher&) = delete;
      Dispatcher& operator=(const Dispatcher&) = delete;

      std::unordered_map<int, EventSignal> signals_;
};

Dispatcher::Dispatcher() : signals_() {}
Dispatcher::~Dispatcher() {}

Connection Dispatcher::subscribe(const int id, const EventCallback cb)
{
   // Creates a new signal if `id` is not already in `signals_`
   return signals_[id].connect(cb);
}

void Dispatcher::unsubscribe(const int id, const Connection& conn)
{
   if (signals_.count(id) > 0) {
      conn.disconnect();

      if (signals_[id].empty()) {
         signals_.erase(id);
      }
   }
}

void Dispatcher::unsubscribe_all(const int id)
{
   if (id == -1) {
      for (auto it = signals_.begin(); it != signals_.end(); ++it) {
         it->second.disconnect_all_slots();
      }
      signals_.clear();
   } else {
      if (signals_.count(id) > 0) {
         signals_[id].disconnect_all_slots();
         signals_.erase(id);
      }
   }
}

void Dispatcher::publish(EventConstPtr event)
{
   if (signals_.count(event->id()) > 0) {
      signals_[event->id()](event);
   }
}

int Dispatcher::num_slots(const int id)
{
   if (signals_.count(id) > 0) {
      return signals_[id].num_slots();
   } else {
      return 0;
   }
}

// subscribe functions
Connection subscribe(const int id, const EventCallback cb)
{
   return Dispatcher::instance().subscribe(id, cb);
}

// unsubscribe functions
void unsubscribe(const int id, const Connection& conn)
{
   Dispatcher::instance().unsubscribe(id, conn);
}

// unsubscribe_all function
void unsubscribe_all(const int id)
{
   Dispatcher::instance().unsubscribe_all(id);
}

// publish function
void publish(EventConstPtr event)
{
   Dispatcher::instance().publish(event);
}

int num_slots(const int id)
{
   return Dispatcher::instance().num_slots(id);
}

}  // namespace signals
}  // namespace mgpp
