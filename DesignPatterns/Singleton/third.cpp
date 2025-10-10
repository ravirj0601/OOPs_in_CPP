#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
using namespace std;

class SimpleLogger{
    private:
        ofstream out_;
        string fileName_;
        mutex mtx;

        SimpleLogger();
        ~SimpleLogger();

        SimpleLogger(const SimpleLogger&) = delete;
        SimpleLogger& operator=(const SimpleLogger&) = delete;

    public:
        static SimpleLogger& instance();
        void log(const string& msg);
        void flush();
};

SimpleLogger& SimpleLogger::instance(){
    static SimpleLogger inst;
    return inst;
}

SimpleLogger::SimpleLogger() : fileName_("app.log"){
    out_.open(fileName_, ios::app);
    if (!out_.is_open()) {
        cerr<<"SimpleLogger: Failed to open " << fileName_ << "\n";
    }
}

void SimpleLogger::log(const string& msg){
    std::ostringstream line;
    line << msg << "\n";
    {
        lock_guard<mutex> lk(mtx);
        if (out_.is_open()) {
            out_ << line.str();
        }else {
            std::cerr << line.str();
        }
    }
}

void SimpleLogger::flush(){
    lock_guard<mutex> lk(mtx);
    if (out_.is_open()) out_.flush();
}

SimpleLogger::~SimpleLogger(){
    if (out_.is_open()) out_.close();
}

int main() {
    SimpleLogger::instance().log("Program Started: ");
    SimpleLogger::instance().log("Doing Work: ");
    SimpleLogger::instance().log("End: ");
    SimpleLogger::instance().flush();
    return 0;
}

