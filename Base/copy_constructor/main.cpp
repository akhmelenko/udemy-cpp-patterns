
#include <iostream>

class Foo{
    int *ptr;
public:
    // constructor
    Foo(int value){
        ptr = new int;
        *ptr = value;
        std::cout << "Simple constructor\n";
    }
    // copy constructor
    Foo(Foo& obj){
        ptr = new int;
        *ptr = *obj.ptr;
        std::cout << "Copy constructor\n";
    }
    ~Foo(){ 
        delete ptr; 
    }

    int GetValue(){
        return *ptr;
    }
    void InternalDisplay(){
        std::cout << "Internal display val=" << *ptr << "\n";
    }
};

void ExternalDisplay(Foo f){
        std::cout << "External display val=" << f.GetValue() << "\n";
}

Foo MakeFoo(int value){
    Foo f{value};
    std::cout << "--7--:" << &f << "\n";
    return f;
}

int main(){
    std::cout << "--1--:\n";
    Foo f(10);
    std::cout << "--2--:\n";
    f.InternalDisplay();
    std::cout << "--3--:\n";
    ExternalDisplay(f);

    std::cout << "--4--:\n";
    Foo f2 = f;
    std::cout << "--5--:\n";
    Foo f3(f);
    std::cout << "--6--:\n";
    Foo retF = MakeFoo(15);
    std::cout << "--8--:" << &retF << "\n";
    retF.InternalDisplay();
    return 0;
}