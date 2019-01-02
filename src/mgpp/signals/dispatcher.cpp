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
  Dispatcher(const Dispatcher &) = delete;
  Dispatcher &operator=(const Dispatcher &) = delete;
  Dispatcher(Dispatcher &&) = delete;
  Dispatcher &operator=(Dispatcher &&) = delete;

  Connection Subscribe(const int id, const EventCallback cb);
  void Unsubscribe(const int id, const Connection &conn);
  void UnsubscribeAll(const int id = -1);
  void Publish(EventConstPtr event);
  int NumSlots(const int id);

  static Dispatcher &Instance() {
    static Dispatcher dispatcher;
    return dispatcher;
  }

 private:
  Dispatcher();
  ~Dispatcher();

  std::unordered_map<int, EventSignal> signals_;
};

Dispatcher::Dispatcher() = default;
Dispatcher::~Dispatcher() = default;

Connection Dispatcher::Subscribe(const int id, const EventCallback cb) {
  // Creates a new signal if `id` is not already in `signals_`
  return signals_[id].connect(cb);
}

void Dispatcher::Unsubscribe(const int id, const Connection &conn) {
  if (signals_.count(id) > 0) {
    conn.disconnect();

    if (signals_[id].empty()) {
      signals_.erase(id);
    }
  }
}

void Dispatcher::UnsubscribeAll(const int id) {
  if (id == -1) {
    for (auto &signal : signals_) {
      signal.second.disconnect_all_slots();
    }
    signals_.clear();
  } else {
    if (signals_.count(id) > 0) {
      signals_[id].disconnect_all_slots();
      signals_.erase(id);
    }
  }
}

void Dispatcher::Publish(EventConstPtr event) {
  if (signals_.count(event->id()) > 0) {
    signals_[event->id()](event);
  }
}

int Dispatcher::NumSlots(const int id) {
  if (signals_.count(id) > 0) {
    return signals_[id].num_slots();
  } else {
    return 0;
  }
}

// Subscribe functions
Connection Subscribe(const int id, const EventCallback cb) {
  return Dispatcher::Instance().Subscribe(id, cb);
}

// Unsubscribe functions
void Unsubscribe(const int id, const Connection &conn) {
  Dispatcher::Instance().Unsubscribe(id, conn);
}

// UnsubscribeAll function
void UnsubscribeAll(const int id) { Dispatcher::Instance().UnsubscribeAll(id); }

// Publish function
void Publish(EventConstPtr event) { Dispatcher::Instance().Publish(event); }

int NumSlots(const int id) { return Dispatcher::Instance().NumSlots(id); }

}  // namespace signals
}  // namespace mgpp
