
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Journal{
    string _title;
    vector<string> _entries;
    int _cnt;
public:
    explicit Journal(const string &title): _title(title), _cnt(1){}
    void Add(const string &entry){        
        _entries.push_back(to_string(_cnt) + ":" + entry);
        _cnt++;
    }
    void Print(){
        for (auto &entry: _entries)
            cout << entry << "\n";
    }
    friend class JournalSave; 
};

class JournalSave{
public:
    explicit JournalSave(){}
    static void Save(const Journal& j, const string &fileName){
        ofstream os(fileName);
        for (auto &entry: j._entries)
            os << entry + "\n";
    }
};

int main(){
    Journal a("my_diary");
    a.Add("First Note");
    a.Add("Second note");
    Journal b("my_work");
    b.Add("First work");
    b.Add("Second work");
    a.Print();
    b.Print();
    JournalSave::Save(a, "my_diary.txt");
    JournalSave::Save(b, "my_work.txt");
    return 0;
}