
#include <iostream>
#include <string>
#include <vector>
#include <memory>

enum class Color{RED, GREEN, BLUE};
enum class Size{SMALL, MEDIUM, BIG}; 

struct Product{
    std::string _name;
    Color _color;
    Size _size;
    Product(const std::string &name, const Color color, const Size size)
        : _name(name), _color(color), _size(size){}    
};

typedef std::vector<std::shared_ptr<Product>> pList;

template <typename T> 
class Specification{
    virtual bool IsSatisfied(T* item) = 0;
};

class SpecificationColor: Specification<Product>{
    Color color;
public:
    explicit SpecificationColor(const Color color): color(color){}
    bool IsSatisfied(Product* item) override {
        return item->_color == color;
    }
};

template <typename T> class BetterFilter{
public:
    static std::vector<std::shared_ptr<T>> Filter(
        std::vector<std::shared_ptr<T>> items,
        Specification<T> &spec)
    {
        std::vector<std::shared_ptr<T>> result;
        for (auto &item: items){
            if (IsSatisfied(item)){
                result.push_back(item);                    
            }
        }
        return result;
    }
    static std::vector<std::shared_ptr<T>> ByColor(
        std::vector<std::shared_ptr<T>> &items, Color color){
        std::vector<std::shared_ptr<T>> result;
        for (auto &item: items){
            if (item->_color == color){
                result.push_back(item);                    
            }
        }
        return result;
    }
    static std::vector<std::shared_ptr<T>> BySize(
        std::vector<std::shared_ptr<T>> &items, 
        Size size)
    {
        std::vector<std::shared_ptr<T>> result;
        for (auto &item: items)
            if (item->_size == size){
                result.push_back(item);
            }
        return result;
    }
    static std::vector<std::shared_ptr<T>> ByColorAndSize(
        std::vector<std::shared_ptr<T>> &items, 
        Color color, 
        Size size)
    {
        std::vector<std::shared_ptr<T>> result;
        for (auto &item: items)
            if (item->_color == color && item->_size == size){
                result.push_back(item);
            }
        return result;
    }
};

void PrintProducts(const std::vector<std::shared_ptr<Product>> &products){
    for (auto &product: products)
        std::cout << product->_name << "\n";
}

int main(){
    std::shared_ptr<Product> tree = std::make_shared<Product>("Tree", Color::GREEN, Size::BIG);
    std::shared_ptr<Product> house = std::make_shared<Product>("House", Color::BLUE, Size::BIG);
    std::shared_ptr<Product> apple = std::make_shared<Product>("Apple", Color::RED, Size::SMALL);
    std::vector<std::shared_ptr<Product>> all{
        tree, 
        house,
        apple
    };
    // std::vector<std::shared_ptr<Product>> green = 
    //     ProductFilter::ByColor(all, Color::GREEN); 
    // std::vector<std::shared_ptr<Product>> big = 
    //     ProductFilter::BySize(all, Size::BIG);
    // std::vector<std::shared_ptr<Product>> greenBig = 
    //     ProductFilter::ByColorAndSize(all, Color::GREEN, Size::BIG);    
    // std::cout << "green:\n";
    // PrintProducts(green);
    // std::cout << "big:\n";
    // PrintProducts(big);
    // std::cout << "green and big:\n";
    // PrintProducts(greenBig);

    SpecificationColor spGreen(Color::GREEN);
    pList green = BetterFilter<Product>::Filter(all, spGreen);

    return 0;
}
