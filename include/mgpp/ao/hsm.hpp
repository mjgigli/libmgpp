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

#ifndef MGPP_AO_HSM_HPP_
#define MGPP_AO_HSM_HPP_

#include <functional>

#include <mgpp/ao/event.hpp>
#include <mgpp/noncopyable.hpp>

namespace mgpp {
namespace ao {

enum HsmSignal {
  SUPER_SIG,
  ENTRY_SIG,
  EXIT_SIG,
  INIT_SIG,
  USER_SIG  // start user signals from this value
};

enum StateAction {
  ACTION_SUPER,
  ACTION_IGNORED,
  ACTION_HANDLED,
  ACTION_INITIAL_TRANSITION,
  ACTION_TRANSITION
};

// Forward declarations
class Hsm;

// using StateHandler =
// std::function<StateAction (Hsm * const me, EventConstPtr)>;
typedef StateAction (*StateHandler)(void *const me, EventConstPtr evt);

// Helper functions
template <class T>
StateHandler StateCast(T handler) {
  return reinterpret_cast<StateHandler>(handler);
}

class Hsm : private Noncopyable {
 public:
  virtual ~Hsm();

  virtual void Init();
  virtual void Dispatch(EventConstPtr evt);

  StateHandler state() const;

 protected:
  explicit Hsm(StateHandler initial);

  template <class T>
  StateAction InitialTransition(T target);

  template <class T>
  StateAction Transition(T target);

  template <class T>
  StateAction Super(T state);

  StateAction Handled();

  static StateAction Top(Hsm *const me, EventConstPtr evt);

 private:
  StateHandler state_;
  StateHandler temp_;
  EventConstPtr super_evt_;
  EventConstPtr init_evt_;
  EventConstPtr entry_evt_;
  EventConstPtr exit_evt_;

  void EnterState(StateHandler state);
  void ExitState();
  StateAction InitialTransition(StateHandler target);
  StateAction Transition(StateHandler target);
  StateAction Super(StateHandler state);
};

template <class T>
StateAction Hsm::InitialTransition(T target) {
  return this->InitialTransition(StateCast(target));
}

template <class T>
StateAction Hsm::Transition(T target) {
  return this->Transition(StateCast(target));
}

template <class T>
StateAction Hsm::Super(T state) {
  return this->Super(StateCast(state));
}

}  // namespace ao
}  // namespace mgpp

#endif  // MGPP_AO_HSM_HPP_
