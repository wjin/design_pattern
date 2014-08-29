#include <iostream>

using namespace std;

class Singleton
{
public:
    static Singleton& getInstance() // reference
    {
        static Singleton instance; // Guaranteed to be destroyed. Instantiated on first use.
        return instance;
    }

    void dump()
    {
        cout << "I am singleton pattern: " << this << endl;
    }

private:

    Singleton() {}  // Constructor? (the {} brackets) are needed here.

    // Dont forget to declare these two. You want to make sure they
    // are unaccessable otherwise you may accidently get copies of
    // your singleton appearing.
    Singleton(const Singleton &) = delete; // Don't Implement
    Singleton& operator=(const Singleton&) = delete; // Don't implement
};

int main()
{
    Singleton::getInstance().dump();
    Singleton::getInstance().dump();
    Singleton::getInstance().dump();

    return 0;
}
