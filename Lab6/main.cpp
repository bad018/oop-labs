#include <iostream>

using namespace std;

class P
{
public:
    P()
    {
        cout<< "P";
    }
};

class O :  virtual public P
{
public:
    O()
    {
        cout<< "O";
    }
};

class C : public P
{
public:
    C()
    {
        cout<< "C";
    }
};

class R : public O
{
public:
    R(){
        cout<< "R";
    }
};

class N : public O, public C, public R
{
public:
    N(){
        cout<< "N\n"q;
    }
};

int main() {
    N obj;
}
