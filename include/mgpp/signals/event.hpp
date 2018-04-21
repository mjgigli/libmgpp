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
