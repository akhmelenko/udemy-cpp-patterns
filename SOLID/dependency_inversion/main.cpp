
#include <iostream>
#include <fstream>
#include <memory>

/*
class Reporting
{
    ILogger &logger;

public:
    Reporting(const ILogger &logger) : logger{logger} {}
    void prepare_report()
    {
        logger.log_info("Preparing the report");
        ;
    }
};
*/

class Engine
{
protected:
    float volume = 5;
    int horsePower = 400;

    friend std::ostream &operator<<(std::ostream &os, const Engine &obj)
    {
        return os << "volume=" << obj.volume
                  << " horse power=" << obj.horsePower;
        // return os;
    } // thanks, ReSharper!
};

class ILogger
{
public:
    ILogger() {}
    virtual ~ILogger() {}
    virtual void Log(const std::string &s) = 0;
};

class ConsoleLogger : public ILogger
{
public:
    ConsoleLogger() {}
    ~ConsoleLogger() {}
    void virtual Log(const std::string &s) override
    {
        std::cout << "LOG: " << s << "\n";
    }
};

class FileLogger : public ILogger
{
    std::string filename;

public:
    FileLogger(const std::string &filename) : filename(filename) {}
    ~FileLogger() {}
    void virtual Log(const std::string &s) override
    {
        std::ofstream os(filename);
        os << "LOG: " << s << "\n";
        os.close();
    }
};

class Car
{
protected:
    std::shared_ptr<Engine> engine;
    std::shared_ptr<ILogger> logger;
    // Engine *engine;
    // ILogger *logger;

public:
    Car(std::shared_ptr<Engine> engine,
        std::shared_ptr<ILogger> logger)
        : engine{std::move(engine)}, logger{logger}
    // Car(Engine *engine,
    //     ILogger *logger)
    //     : engine{std::move(engine)}, logger{logger}
    {
        std::cout << "Making a car\n";
    }

    void Log(const std::string &s)
    {
        logger->Log(s);
    }

    friend std::ostream &operator<<(std::ostream &os, const Car &obj)
    {
        return os << "car with engine: " << *obj.engine;
    }
};

int main()
{
    Car car(std::make_shared<Engine>(Engine()),
            std::make_shared<ConsoleLogger>(ConsoleLogger()));
    std::cout << car << "\n";

    Car car2(std::make_shared<Engine>(Engine()),
             std::make_shared<FileLogger>(FileLogger("carlog.txt")));
    std::cout << car2 << "\n";

    car.Log("I am car!");
    car2.Log("I am car2!");

    // Just test unique_ptr
    int i = 5;
    std::unique_ptr<int> upI = std::make_unique<int>(i);
    std::cout << "upI=" << *upI << "\n";

    return 0;
}