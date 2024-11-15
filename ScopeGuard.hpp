#ifndef SCOPE_GUARD_HPP
#define SCOPE_GUARD_HPP

#include <mutex>

/**
 * ScopeGuard is a helper class that locks a mutex when created
 * and automatically unlocks it when it goes out of scope.
 * This helps prevent forgetting to unlock a mutex in a scope.
 */
class ScopeGuard {
public:
    explicit ScopeGuard(std::mutex& mtx) : mutex_(mtx) {
        mutex_.lock();
    }

    ~ScopeGuard() {
        mutex_.unlock();
    }

    // Prevent copying and assignment
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;

private:
    std::mutex& mutex_;  // Reference to the mutex to lock/unlock
};

#endif // SCOPE_GUARD_HPP
