
#include <iostream>
#include <string>
#include <vector>

class Tag
{
protected:
    std::string type;
    std::string text;
    std::vector<Tag> children;
    std::vector<std::pair<std::string, std::string>> attributes;

    Tag(const std::string &type, const std::string &text)
        : type(type), text(text) {}
    Tag(const std::string &type, const std::vector<Tag> &children)
        : type{type}, children{children} {}

    friend std::ostream &operator<<(std::ostream &os, const Tag &obj)
    {
        os << "<" << obj.type << ">" << obj.text;
        for (auto &a : obj.attributes)
            os << a.first << ":" << a.second;
        for (auto &e : obj.children)
            os << e;
        os << "</" << obj.type << ">";
        return os;
    }
};

class Paragraph : public Tag
{
public:
    Paragraph(const std::string &text)
        : Tag("paragraph", text) {}
    Paragraph(const std::vector<Tag> &children)
        : Tag("paragraph", children) {}
};

class Image : public Tag
{
public:
    Image(const std::string &url)
        : Tag("img", "")
    {
        attributes.emplace_back("src", url);
    }
};

int main()
{
    std::cout << Paragraph({Image{"http://www.pokemon.com/pikachu.png"}}) << std::endl;
    return 0;
}