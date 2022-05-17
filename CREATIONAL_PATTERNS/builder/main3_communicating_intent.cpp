
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class HtmlBuilder;

class HtmlElement
{
public:
    std::string type;
    std::string text;
    std::vector<HtmlElement> elements;

    HtmlElement() {}
    HtmlElement(const std::string &type, const std::string &text)
        : type(type), text(text) {}

    std::string Str(int indent = 0)
    {
        std::string ret = "<" + type + ">" + text;
        for (auto &e : elements)
            ret += e.Str();
        ret += "</" + type + ">";
        return ret;
    }

    static std::unique_ptr<HtmlBuilder> Build(const std::string &rootType)
    {
        return std::make_unique<HtmlBuilder>(rootType);
    }
};

class HtmlBuilder
{
    HtmlElement root;

public:
    HtmlBuilder(const std::string &type)
    {
        root.type = type;
    }

    HtmlBuilder &AddChild(const std::string &type, const std::string &text)
    {
        root.elements.emplace_back(HtmlElement{type, text});
        return *this;
    }
    std::string Str()
    {
        return root.Str();
    }

    // !!! CLASS TYPE CONVERSION: HtmlElement - type
    // HtmlBuilder b;
    // HtmlElement e = b; // !!! No Error (e = root) !!!
    operator HtmlElement() const
    {
        return root;
    }

    HtmlElement Build()
    {
        return root;
    }
};

int main()
{
    printf("--1--:\n");
    std::vector<std::string> words = {"Hello", "dear", "world"};
    HtmlElement e = (*HtmlElement::Build("ul"))
                        .AddChild("li", "hello")
                        .AddChild("li", "world");
    std::cout << e.Str() << "\n";

    HtmlBuilder b("ul");
    HtmlElement e2 = b.AddChild("li", "hello2").AddChild("li", "world2").Build();
    std::cout << e2.Str() << "\n";
    return 0;
}