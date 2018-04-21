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
