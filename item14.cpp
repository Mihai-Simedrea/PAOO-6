#include <iostream>
#include <memory>

struct Mutex { };

void lock(Mutex* pm) {
    std::cout << "Locking mutex at address: " << pm << std::endl;
}

void unlock(Mutex* pm) {
    std::cout << "Unlocking mutex at address: " << pm << std::endl;
}

class Uncopyable {
    protected:
        Uncopyable() = default;
        ~Uncopyable() = default;

    private:
        Uncopyable(const Uncopyable&) = delete;
        Uncopyable& operator=(const Uncopyable&) = delete;
};

class Lock : private Uncopyable {
    public:
        explicit Lock(Mutex* pm) : mutexPtr(pm) {
            lock(mutexPtr);
        }

        ~Lock() {
            unlock(mutexPtr);
        }

    private:
        Mutex* mutexPtr;
};

class SharedLock {
    public:
        explicit SharedLock(Mutex* pm)
            : mutexPtr(pm, unlock) {
            lock(mutexPtr.get());
        }

    private:
        std::shared_ptr<Mutex> mutexPtr;
};

int main() {
    // using Lock with prohibited copying
    std::cout << "=== Example 1: Prohibited Copying ===" << std::endl;
    Mutex m1;
    {
        Lock lock1(&m1); // lock the mutex
        // Lock lock2(lock1); // compilation error
    } // automatically unlocks mutex

    // lock class with reference counting
    std::cout << "\n=== Example 2: Reference Counting ===" << std::endl;
    Mutex m2;
    {
        SharedLock sharedLock1(&m2); // lock the mutex
        SharedLock sharedLock2(sharedLock1); // shared ownership of the mutex
    } // automatically unlocks mutex when the last shared lock is destroyed

    return 0;
}