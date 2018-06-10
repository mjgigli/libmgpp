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

#ifndef MGPP_AO_EVENT_HPP_
#define MGPP_AO_EVENT_HPP_

#include <mgpp/signals/event.hpp>

namespace mgpp {
namespace ao {

// Reuse signals::Event class and helpers
using Event = mgpp::signals::Event;
using EventPtr = mgpp::signals::EventPtr;
using EventConstPtr = mgpp::signals::EventConstPtr;

template <typename T, typename... Args>
std::shared_ptr<T> MakeEvent(Args... args) {
    return mgpp::signals::MakeEvent<T>(args...);
}

}   // namespace ao
}   // namespace mgpp

#endif  // MGPP_AO_EVENT_HPP_