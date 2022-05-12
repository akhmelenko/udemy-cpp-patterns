
#include <iostream>
#include <string>
#include <vector>
#include <memory>

enum class Color
{
    RED,
    GREEN,
    BLUE
};
enum class Size
{
    SMALL,
    MEDIUM,
    BIG
};

struct Product
{
    std::string name;
    Color color;
    Size size;
    Product(const std::string &name, const Color color, const Size size)
        : name(name), color(color), size(size) {}
};

typedef std::vector<std::shared_ptr<Product>> pList;

template <typename T>
class Specification
{
public:
    virtual bool IsSatisfied(std::shared_ptr<T> item) = 0;
};

class SpecificationColor : public Specification<Product>
{
    Color color;

public:
    explicit SpecificationColor(const Color color) : color(color) {}
    virtual bool IsSatisfied(std::shared_ptr<Product> item) override
    {
        return item->color == color;
    }
};

class SpecificationSize : public Specification<Product>
{
    Size size;

public:
    explicit SpecificationSize(const Size size) : size(size) {}
    virtual bool IsSatisfied(std::shared_ptr<Product> item) override
    {
        return item->size == size;
    }
};

class SpecificationSizeAndColor : public Specification<Product>
{
    Size size;
    Color color;

public:
    explicit SpecificationSizeAndColor(const Size size, const Color color) : size(size), color(color) {}
    virtual bool IsSatisfied(std::shared_ptr<Product> item) override
    {
        return item->size == size && item->color == color;
    }
};

template <typename T>
class BetterFilter
{
public:
    static std::vector<std::shared_ptr<T>> Filter(
        std::vector<std::shared_ptr<T>> &items,
        std::shared_ptr<Specification<T>> spec)
    {
        std::vector<std::shared_ptr<T>> result;
        for (auto &item : items)
            if (spec->IsSatisfied(item))
                result.push_back(item);
        return result;
    }
};

void PrintProducts(const pList &products)
{
    for (auto &product : products)
        std::cout << product->name << "\n";
}

int main()
{
    std::shared_ptr<Product> tree = std::make_shared<Product>("Tree", Color::GREEN, Size::BIG);
    std::shared_ptr<Product> house = std::make_shared<Product>("House", Color::BLUE, Size::BIG);
    std::shared_ptr<Product> apple = std::make_shared<Product>("Apple", Color::RED, Size::SMALL);
    std::vector<std::shared_ptr<Product>> all{tree, house, apple};

    std::shared_ptr<Specification<Product>> spGreen = std::make_shared<SpecificationColor>(Color::GREEN);
    std::shared_ptr<Specification<Product>> spBig = std::make_shared<SpecificationSize>(Size::BIG);
    std::shared_ptr<Specification<Product>> spBigGreen = std::make_shared<SpecificationSizeAndColor>(Size::BIG, Color::GREEN);
    pList green = BetterFilter<Product>::Filter(all, spGreen);
    pList big = BetterFilter<Product>::Filter(all, spBig);
    pList bigGreen = BetterFilter<Product>::Filter(all, spBigGreen);
    std::cout << "green:\n";
    PrintProducts(green);
    std::cout << "big:\n";
    PrintProducts(big);
    std::cout << "big and green:\n";
    PrintProducts(bigGreen);

    return 0;
}
