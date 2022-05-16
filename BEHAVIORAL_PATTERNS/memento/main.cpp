
#include <iostream>
#include <vector>
#include <memory>

class Account;

class Memento{
    int balance;
public:
    Memento(const int balance): balance(balance){}
    friend class Account;
};

class Account{
    int balance = 0;
    std::vector<std::shared_ptr<Memento>> changes;
    int current = 0;
public:
     Account(const int balance): balance(balance){
        changes.push_back(std::make_shared<Memento>(balance));
    }
    std::shared_ptr<Memento> Withdraw(int val){
        if (this->balance >= val){
            this->balance -= val;
        }
        current++;
        auto m = std::make_shared<Memento>(balance);
        changes.push_back(m);
        return m;
    }
    std::shared_ptr<Memento> Deposit(int val){
        balance += val;
        current++;
        auto m = std::make_shared<Memento>(balance);
        changes.push_back(m);
        return m;
    }
    auto Balance(){
        return balance;
    }
    std::shared_ptr<Memento> Undo(){
        if (current > 0){
            current--;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }
    std::shared_ptr<Memento> Redo(){
        if (current < changes.size() - 1){
            current++;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }
};

int main(){
    Account a = 100;
    std::cout << "1: balance=" << a.Balance() << "\n";
    a.Deposit(200);
    std::cout << "2: balance=" << a.Balance() << "\n";
    a.Withdraw(100);
    std::cout << "3: balance=" << a.Balance() << "\n";
    a.Undo();
    std::cout << "4: balance=" << a.Balance() << "\n";
    a.Undo();
    std::cout << "5: balance=" << a.Balance() << "\n";
    a.Undo();
    std::cout << "6: balance=" << a.Balance() << "\n";
    a.Redo();
    std::cout << "7: balance=" << a.Balance() << "\n";
    a.Redo();
    std::cout << "8: balance=" << a.Balance() << "\n";
    a.Redo();
    std::cout << "9: balance=" << a.Balance() << "\n";
    a.Redo();
    std::cout << "10: balance=" << a.Balance() << "\n";
}