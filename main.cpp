#include <iostream>
#include <memory>
#include <vector>

class Investment {
    public:
        Investment() { std::cout << "Investment created.\n"; }
        ~Investment() { std::cout << "Investment destroyed.\n"; }
};

// Create investments
Investment* createInvestment() {
    return new Investment();
}

int main() {
    // Option 1: Manual resource management (not recommended)
    {
        Investment* pInv = createInvestment();
        std::cout << "Using manual management.\n";
        delete pInv;
    }

    // Option 2: Using std::auto_ptr (deprecated in C++11)
    {
        std::auto_ptr<Investment> pInv(createInvestment());
        std::cout << "Using std::auto_ptr (deprecated).\n";
    } // Automatically calls delete when pInv goes out of scope

    // Option 3: Using std::unique_ptr (C++11+)
    {
        std::unique_ptr<Investment> pInv(createInvestment());
        std::cout << "Using std::unique_ptr for exclusive ownership.\n";
    } // Automatically calls delete when pInv goes out of scope

    // Option 4: Using std::shared_ptr (C++11+)
    {
        std::shared_ptr<Investment> pInv1(createInvestment());
        std::shared_ptr<Investment> pInv2 = pInv1; // Shared ownership
        std::cout << "Using std::shared_ptr for shared ownership.\n";
    } // Deletes resource when the last shared_ptr is destroyed

    // Option 5: std::shared_ptr with STL containers
    {
        std::vector<std::shared_ptr<Investment>> investments;
        investments.push_back(std::make_shared<Investment>());
        std::cout << "Using std::shared_ptr with STL containers.\n";
    } // Resources in the vector are cleaned up automatically

    return 0;
}
