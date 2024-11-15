#ifndef SINGLETON_BASE_HPP
#define SINGLETON_BASE_HPP

#include <mutex>

/**
 * SingletonBase is an abstract base class that ensures only one instance exists.
 * It uses a POSIX mutex to protect the creation of the instance in a multi-threaded environment.
 * Derived classes should implement the `doSomething` function.
 */
class SingletonBase {
public:
    // Prevent copying and assignment
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase& operator=(const SingletonBase&) = delete;

    // Virtual destructor for abstract class
    virtual ~SingletonBase() = default;

    // Static method to access the singleton instance
    static SingletonBase* getInstance();

    // Abstract method that derived classes need to implement
    virtual void doSomething() = 0;

protected:
    SingletonBase() = default;

private:
    static SingletonBase* instance_;  // Singleton instance
    static std::mutex mutex_;         // Mutex for thread safety
};

#endif // SINGLETON_BASE_HPP
