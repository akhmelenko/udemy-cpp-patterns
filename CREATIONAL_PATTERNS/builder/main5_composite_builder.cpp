
#include <iostream>
#include <string>
#include <vector>

class PersonBuilder;

class Person
{
    // address
    std::string street;
    std::string postCode;
    std::string city;

    // employment
    std::string company;
    std::string position;
    int annualIncome = 0;

    Person()
    {
        printf("Person Constructor\n");
    } // private!

public:
    static PersonBuilder create();

    friend std::ostream &operator<<(std::ostream &os, Person &obj)
    {
        return os << "Address:"
                  << "\nstreet: " << obj.street
                  << "\npost code: " << obj.postCode
                  << "\ncity: " << obj.city
                  << "\nEmployment:"
                  << "\ncompany: " << obj.company
                  << "\nposition: " << obj.position
                  << "\nannualIncome: " << obj.annualIncome;
    }
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;
    friend class PersonBuilder;
};

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase
{
protected:
    Person &person;                            // REFERENCE !
    explicit PersonBuilderBase(Person &person) // ptorected constructor
        : person{person}
    {
        printf("PersonBuilderBase Constructor (copy reference to Person)\n");
    }

public:
    // conversion from class PersonBuilderBase to Person
    operator Person()
    {
        return std::move(person);
    }

    // builder facets
    PersonAddressBuilder lives();
    PersonJobBuilder works();
};

class PersonBuilder : public PersonBuilderBase
{
    Person p; // OBJECT being built !
public:
    PersonBuilder() : PersonBuilderBase(p)
    {
        printf("PersonBuilder Constructor (create object Person)\n");
    }
};

class PersonAddressBuilder : public PersonBuilderBase
{
    typedef PersonAddressBuilder self;

public:
    explicit PersonAddressBuilder(Person &person) : PersonBuilderBase{person}
    {
        printf("PersonAddressBuilder Constructor\n");
    }
    self &street(const std::string &street)
    {
        person.street = street;
        return *this;
    }
    self &postcode(const std::string &postCode)
    {
        person.postCode = postCode;
        return *this;
    }
    self &city(const std::string &city)
    {
        person.city = city;
        return *this;
    }
};

class PersonJobBuilder : public PersonBuilderBase
{
    typedef PersonJobBuilder self;

public:
    explicit PersonJobBuilder(Person &person) : PersonBuilderBase{person}
    {
        printf("PersonJobBuilder Constructor\n");
    }
    self &company(const std::string &company)
    {
        person.company = company;
        return *this;
    }
    self &position(const std::string &position)
    {
        person.position = position;
        return *this;
    }
    self &income(int annualIncome)
    {
        person.annualIncome = annualIncome;
        return *this;
    }
};

PersonAddressBuilder PersonBuilderBase::lives()
{
    return PersonAddressBuilder{person};
}

PersonJobBuilder PersonBuilderBase::works()
{
    return PersonJobBuilder{person};
}

PersonBuilder Person::create()
{
    return PersonBuilder();
}

int main()
{
    Person p = Person::create() // create (PersonBuilder (with Person object) (and PersonBuilderBase))
                   .lives()     // create (PersonAddressBuilder (and PersonBuilderBase again))
                   .street("ul. Lenina")
                   .postcode("140410")
                   .city("Kolomna")
                   .works() // create (PersonJobBuilder (and PersonBuilderBase again))
                   .company("Yandex")
                   .position("Consultant")
                   .income(10e6);
    std::cout << "\n"
              << p;
    return 0;
}