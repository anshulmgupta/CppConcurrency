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

void thread_function(promise<string> && prms){
    try{ 
        string str("Hello From Future!!!");
        throw(descriptive_exception("Exception from Future!"));
        prms.set_value(str);
    }
    catch(...){
        prms.set_exception(current_exception());
    }
}

int main(){
    promise<string> prms;
    future<string> ftr = prms.get_future();
    thread th(&thread_function, move(prms));
    cout << "Hello from main!\n";
    try{
        string str = ftr.get();
        cout << str << endl;
    }
    catch(exception &e){
        cout << e.what() << endl;
    }
    th.join();
    return 0;

}
