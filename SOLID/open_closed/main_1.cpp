
#include <iostream>
#include <string>
#include <vector>
#include <memory>

enum class Color{RED, GREEN, BLUE};
enum class Size{SMALL, MEDIUM, BIG};

class Product{
    std::string _name;
    Color _color;
    Size _size;
public:
    explicit Product(const std::string &name, const Color color, const Size size)
        : _name(name), _color(color), _size(size){}
    friend class ProductFilter;
    friend void PrintProducts(const std::vector<std::shared_ptr<Product>> &products);
};

template <typename T> class Specification{
    virtual bool IsSatisfied(T* item) = 0;
};

class ProductFilter{
    typedef std::vector<std::shared_ptr<Product>> Items;
public:
    static Items ByColor(Items &items, Color color){
        Items result;
        for (auto &item: items){
            if (item->_color == color){
                result.push_back(item);                    
            }
        }
        return result;
    }
    static Items BySize(Items &items, Size size){
        Items result;
        for (auto &item: items)
            if (item->_size == size){
                result.push_back(item);
            }
        return result;
    }
    static Items ByColorAndSize(Items &items, Color color, Size size){
        Items result;
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
    std::vector<std::shared_ptr<Product>> green = 
        ProductFilter::ByColor(all, Color::GREEN); 
    std::vector<std::shared_ptr<Product>> big = 
        ProductFilter::BySize(all, Size::BIG);
    std::vector<std::shared_ptr<Product>> greenBig = 
        ProductFilter::ByColorAndSize(all, Color::GREEN, Size::BIG);    
    std::cout << "green:\n";
    PrintProducts(green);
    std::cout << "big:\n";
    PrintProducts(big);
    std::cout << "green and big:\n";
    PrintProducts(greenBig);
    return 0;
}
