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

#include <vector>
#include <algorithm>

#include <mgpp/ao/hsm.hpp>

namespace mgpp {
namespace ao {

Hsm::Hsm(StateHandler initial) :
    state_(StateCast(Top)),
    temp_(initial),
    super_evt_(MakeEvent<Event>(SUPER_SIG)),
    init_evt_(MakeEvent<Event>(INIT_SIG)),
    entry_evt_(MakeEvent<Event>(ENTRY_SIG)),
    exit_evt_(MakeEvent<Event>(EXIT_SIG))
{}

Hsm::~Hsm()
{}

void Hsm::Init() {
    // TODO(mgigli): Verify that Top is super state of initial state
    InitialTransition(temp_);
}

void Hsm::Dispatch(EventConstPtr evt) {
    temp_ = state_;
    while (temp_(this, evt) == ACTION_SUPER)
    {}
}

StateHandler Hsm::state() const {
    return state_;
}

StateAction Hsm::Top(Hsm * const me, EventConstPtr evt) {
    return ACTION_IGNORED;
}

void Hsm::EnterState(StateHandler state) {
    state(this, entry_evt_);
    state_ = StateCast(state);
}

void Hsm::ExitState() {
    state_(this, exit_evt_);
    state_(this, super_evt_);
    state_ = temp_;
}

StateAction Hsm::InitialTransition(StateHandler target) {
    // Record hierarchy of the target state.
    std::vector<StateHandler> target_hierarchy;
    target_hierarchy.push_back(target);
    temp_ = target;
    while (temp_(this, super_evt_) != ACTION_IGNORED &&
           temp_ != state_) {
        target_hierarchy.push_back(temp_);
    }

    // Enter each state in the hierarchy, including the target
    for (auto iter = target_hierarchy.rbegin();
         iter != target_hierarchy.rend(); ++iter) {
        EnterState(*iter);
    }

    // Perform initial transition on target
    return target(this, init_evt_);
}

bool StateInHierarchy(StateHandler state,
                      const std::vector<StateHandler>& hierarchy) {
    return (std::find(hierarchy.begin(), hierarchy.end(), state) !=
            hierarchy.end());
}

StateAction Hsm::Transition(StateHandler target) {
    // temp_ is pointing to the state that handled the event that caused
    // the transition (aka the source state). Record for later use.
    StateHandler source = temp_;

    while (source != state_) {
        // Exit states from current state up to transition source.
        ExitState();
    }

    if (target == source) {
        // Check an easy to detect transition: transition to self.
        // We can exit the source state and enter the target state..
        ExitState();
        EnterState(target);
    } else {
        // Record hierarchy of the target state.
        std::vector<StateHandler> target_hierarchy;
        target_hierarchy.push_back(target);
        temp_ = target;
        while (temp_(this, super_evt_) != ACTION_IGNORED) {
            target_hierarchy.push_back(temp_);
        }

        // Find the least common ancestor (LCA) state of the target and the
        // source states by traversing the source hierarchy until we are in a
        // state in the target hierarchy.
        while (!StateInHierarchy(state_, target_hierarchy)) {
            // Exit until we reach a state in the target hierarchy.
            // Note that the Top state is at the top of the hierarchy.
            ExitState();
        }

        if (state_ != target) {
            // Drill down into the target state, entering all the states in the
            // hierarchy along the way, skipping the current state.
            // Note that we need to traverse the target hierarchy in reverse.
            for (auto iter = std::find(target_hierarchy.rbegin(),
                                       target_hierarchy.rend(), state_) + 1;
                 iter != target_hierarchy.rend(); ++iter) {
                EnterState(*iter);
            }
        }
    }

    // Perform initial transition on target
    target(this, init_evt_);

    return ACTION_TRANSITION;
}

StateAction Hsm::Super(StateHandler state) {
    temp_ = state;
    return ACTION_SUPER;
}

StateAction Hsm::Handled() {
    return ACTION_HANDLED;
}

}   // namespace ao
}   // namespace mgpp
