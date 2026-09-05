#include <iostream>
using namespace std;


class Four
{
public:
    Four()
    {
        cout << "One ";
    }
    ~Four()
    {
        cout << "Nine ";
    }
    
};

class Three
{
public:
    Three()
    {
        cout << "Two ";
    }
    ~Three()
    {
        delete four_ptr;
        cout << "Ten\n";
    }
    Four *four_ptr = new Four;
};

class Two : public Three
{
public:
    Two()
    {
        cout << "Three ";
    }
    ~Two()
    {
        cout << "Eight ";
    }
};

class Five
{
public:
    Five(Four &four)
    {
        cout << "Four ";
    }
    ~Five()
    {
        cout << "Seven ";
    }
};

class One: public Two
{
public:
    One() : five(*four_ptr)
    {
        cout << "Five " ;
    }
    ~One()
    {
        cout << "Six " ;
    }
private:
    using Three::four_ptr;
    Five five;
};

int main() {
    One one;
}
