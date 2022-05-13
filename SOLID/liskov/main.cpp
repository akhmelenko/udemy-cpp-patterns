
#include <iostream>

class Rectangle
{
protected:
    int width;
    int height;

public:
    Rectangle(const int width, const int height) : width{width}, height{height} {}

    int GetWidth() { return width; }
    virtual void SetWidth(const int width) { this->width = width; }
    int GetHeight() { return height; }
    virtual void SetHeight(const int height) { this->height = height; }

    int Area() { return width * height; }
};

class Square : public Rectangle
{
public:
    Square(const int size) : Rectangle(size, size) {}
    virtual void SetWidth(const int width) override { this->width = height = width; }
    virtual void SetHeight(const int height) override { this->height = width = height; }
};

void Process(Rectangle &r)
{
    int w = r.GetWidth();
    r.SetHeight(5);
    std::cout << "area expected=" << w * 5 << "; area got=" << r.Area() << "\n";
}

int main()
{
    Rectangle r(2, 3);
    std::cout << "r area=" << r.Area() << "\n";

    Square s(4);
    std::cout << "s area=" << s.Area() << "\n";

    Process(s);
    // solution: we can make a Factory
    // that creates both rectangles and squares:
    // struct RectangleFactory
    // {
    //     static Rectangle create_rectangle(int w, int h);
    //     static Rectangle create_square(int size);
    // };
}