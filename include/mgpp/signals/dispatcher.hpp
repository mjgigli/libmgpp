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

#ifndef MGPP_SIGNALS_DISPATCHER_HPP_
#define MGPP_SIGNALS_DISPATCHER_HPP_

#include <memory>
#include <unordered_map>

#include <boost/signals2.hpp>
#include <mgpp/signals/event.hpp>

namespace mgpp {
namespace signals {

// Define callback templates and pointer types
using EventCallbackTemplate = void(EventConstPtr);
using EventCallback = std::function<EventCallbackTemplate>;
template <typename T>
using EventMemberCallback = void (T::*)(EventConstPtr);

// Use boost signals2 signals/slots for the event dispatcher
typedef boost::signals2::signal<EventCallbackTemplate> EventSignal;
typedef boost::signals2::connection Connection;

// Subscribe functions
Connection Subscribe(const int id, const EventCallback cb);

template <typename T>
Connection Subscribe(const int id, const EventMemberCallback<T> mcb,
                     const T &obj) {
  return Subscribe(id, boost::bind(mcb, const_cast<T *>(&obj), _1));
}

// Unsubscribe functions
void Unsubscribe(const int id, const Connection &conn);

// UnsubscribeAll function
void UnsubscribeAll(const int id = -1);

// Publish function
void Publish(EventConstPtr event);

int NumSlots(const int id);

}  // namespace signals
}  // namespace mgpp

#endif  // MGPP_SIGNALS_DISPATCHER_HPP_
