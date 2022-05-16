
#include <iostream>
#include <string>
#include <vector>

class HtmlElement{
public:
    std::string type;
    std::string text;
    std::vector<HtmlElement> elements;
    HtmlElement(){}
    HtmlElement(const std::string& type, const std::string& text)
    : type(type), text(text){}

    std::string Str(int indent = 0){
        std::string ret = "<" + type + ">" + text;
        for (auto &e: elements)
            ret += e.Str();
        ret += "</" + type + ">";
        return ret;
    }
};

class HtmlBuilder{
    HtmlElement root;
public:
    HtmlBuilder(const std::string& type, const std::string& text){ 
        root.type = type; 
        root.text = text;
    }

    void AddChild(const std::string& type, const std::string& text){
        root.elements.emplace_back(HtmlElement{type, text});
    }
    std::string Str(){
        return root.Str();
    }
};

int main(){
    printf("--1--:\n");
    std::vector<std::string> words = {"Hello", "dear", "world"};
    HtmlElement list{"ul", "Tiile"};
    for (auto &w: words)
         list.elements.emplace_back(HtmlElement("li", w));
    printf(list.Str().c_str());
  
    printf("\n--2--:\n");
    HtmlBuilder b("ul", "title text");
    b.AddChild("li", "hello");
    b.AddChild("li", "world");
    std::cout << b.Str();
    return 0;
}