
#include <iostream>
#include <any>
#include <vector>
#include <algorithm>

template <typename T>
class Observer
{
public:
    virtual void FieldChanged(
        T &source, 
        const std::string &fieldName) = 0;
};

// observable base class (T - class to observe)
template <typename T>
class Observable{
protected:
    std::vector<Observer<T>*> observers;
public:
    void Notify(T& source, const std::string &changedField) {
        for (auto &observer: observers)
            observer->FieldChanged(source, changedField);
    }
    void Subscribe(Observer<T>* addingObs) { 
        observers.push_back(addingObs); 
        }
    void Unsubscribe(Observer<T>* deletingObs){
        observers.erase(
            std::remove(observers.begin(), observers.end(), deletingObs), 
            observers.end());
    }
};

class Person: public Observable<Person>
{
    int age;
public:
    Person(int age) : age(age) {}
    int GetAge() const { return age; }
    void SetAge(const int value)
    {
        if (age == value)
            return;
        age = value;
        Notify(*this, "age");
    }
};

// single object observer
class ConsolePersonObserver: public Observer<Person>{
public:
    virtual void FieldChanged(Person &p, const std::string &fieldName) override{
        std::cout << "Person Observer: Person's " << fieldName << " changed to " << p.GetAge() << "\n";
    }
};

class Animal: public Observable<Animal>
{
    int weight;

public:
    Animal(int weight) : weight(weight) {}
    int GetWeight() const { return weight; }
    void SetWeight(const int value)
    {
        weight = value;
        Notify(*this, "weight");
    }
};

// multiple objects observer
class ConsoleAllObserver: public Observer<Person>, public Observer<Animal>{
public:
    virtual void FieldChanged(Person &p, const std::string &fieldName) override{
        std::cout << "ALL observer: Person's " << fieldName 
            << " changed to " << p.GetAge() << "\n";
    }
    virtual void FieldChanged(Animal &a, const std::string &fieldName) override{
        std::cout << "ALL observer: Animal's " << fieldName 
            << " changed to " << a.GetWeight() << "\n";
    }
};

int main(){
    Person anton(40);
    Animal simon(4);
    ConsolePersonObserver cpo;
    ConsoleAllObserver cao;
    anton.Subscribe(&cpo);
    anton.Subscribe(&cao);
    simon.Subscribe(&cao);
    std::cout << "subscribed\n";
    anton.SetAge(41);
    anton.SetAge(42);
    simon.SetWeight(5);

    anton.Unsubscribe(&cao);
    std::cout << "all unsubscribed from person\n";
    anton.SetAge(43);
    simon.SetWeight(6);
    std::cout << "double subscribe:\n";
    anton.Subscribe(&cpo);
    anton.SetAge(46);
    std::cout << "Unsubscribe Person observer:\n";
    anton.Subscribe(&cpo);
    anton.SetAge(46);


    return 0;
}