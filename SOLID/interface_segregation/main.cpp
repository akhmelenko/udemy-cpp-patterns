
#include <iostream>
#include <string>

// we want to have multifunctional printer - scannet

template <typename T>
class MultiMachineBase
{
protected:
    T scanned;

public:
    virtual void Print(const T) = 0;
    virtual void Scan() = 0;
};

// inherit my int multi printer
class MultiMachineInt : public MultiMachineBase<int>
{
public:
    virtual void Print(const int data) override
    {
        std::cout << data << "\n";
    }
    virtual void Scan() override
    {
        std::cin >> scanned;
    }
    int GetScanned()
    {
        return scanned;
    }
};

// inherit my sting only printer
class OnlyPrinterStr : public MultiMachineBase<std::string>
{
public:
    virtual void Print(const std::string data) override
    {
        std::cout << data << "\n";
    }
    virtual void Scan()
    {
        // !!! There is a problem: we don't need this method
        // but we mast to definit it !!!
        return;
    }
};

// Better solution next: Segregate the interface
template <typename T>
class PrinterBase
{
public:
    virtual void Print(const T &) = 0;
};

template <typename T>
class ScannerBase
{
protected:
    T scanned;

public:
    virtual void Scan() = 0;
    virtual T GetScanned() = 0;
};

class MyMultitoolInt : public PrinterBase<int>, public ScannerBase<int>
{
protected:
    int scanned;

public:
    virtual void Print(const int &data) override
    {
        std::cout << data << "\n";
    }
    virtual void Scan() override
    {
        std::cin >> scanned;
    }
    virtual int GetScanned() override
    {
        return scanned;
    }
};

class MyOnlyPrinterStr : public PrinterBase<std::string>
{
public:
    virtual void Print(const std::string &data) override
    {
        std::cout << data << "\n";
    }
};

int main()
{
    std::cout << "bad solution (all interfaces in one base class):\n";
    MultiMachineInt mmi;
    mmi.Print(55);
    mmi.Scan();
    std::cout << mmi.GetScanned() << "\n";

    OnlyPrinterStr ops;
    ops.Print("Hello");

    std::cout << "\nbetter solution (all interfaces are segregated by single base classes):\n";
    MyMultitoolInt mulInt;
    mulInt.Print(77);
    mulInt.Scan();
    std::cout << mulInt.GetScanned() << "\n";

    MyOnlyPrinterStr onlyPrStr;
    onlyPrStr.Print("Hello from only printer!");
}