
#include <iostream>

class Person
{
    int age;

public:
    Person(int age) : age(age) {}
    int GetAge() const { return age; }
    void SetAge(const int value)
    {
        age = value;
    }
};

class PersonListener
{
public:
    PersonListener() {}
    virtual void PersonChanged(Person &p,
                               const std::string &propertyName,
                               const any newValue) = 0;
};

template <typename T>
class Observer
{
public:
    virtual void FieldChanged(T &source, const std::string &fieldName) = 0;
};