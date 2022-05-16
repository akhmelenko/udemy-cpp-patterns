
#include <iostream>

template <typename T>
class Observer
{
public:
    virtual void FieldChanged(T &source, const std::string &fieldName) = 0;
};

class Person
{
    int age;
    Observer<Person>* observer;    

public:
    Person(int age, Observer<Person> *observer) 
    : age(age), observer(observer) {}
    int GetAge() const { return age; }
    void SetAge(const int value)
    {
        if (age == value)
            return;
        age = value;
        observer->FieldChanged(*this, "age");
    }
};

// single object observer
class ConsolePersonObserver: public Observer<Person>{
public:
    virtual void FieldChanged(Person &p, const std::string &fieldName) override{
        std::cout << "Person's " << fieldName << " changed to " << p.GetAge() << "\n";
    }
};

int main(){
    Observer<Person>* consObs = new ConsolePersonObserver;
    // create object and add observer in constructor
    Person anton(40, consObs);
    anton.SetAge(41);
    anton.SetAge(42);
    // consObs->FieldChanged(anton, "some text");
    delete consObs;

    return 0;
}