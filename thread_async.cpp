#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include <algorithm>
#include <future>
#include <string>
#include <exception>
using namespace std;

class descriptive_exception : public std::exception {
public:
  descriptive_exception(std::string const &message) : msg_(message) { }
  virtual char const *what() const noexcept { return msg_.c_str(); }

private:
  std::string msg_;
};


string fun(){
    string str("Hello From Future!!!");
    throw(descriptive_exception("Exception from task!"));
    return str;
}

int main(){
    auto ftr = async(&fun);
    cout << "Hello from main!\n";
    try{
        string str = ftr.get();
        cout << str << endl;
    }
    catch(exception &e) {
        cout << e.what() << endl;
    }
    return 0;

}
