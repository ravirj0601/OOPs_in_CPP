#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class SimpleLogger{
    private:
        ofstream out_;
        string fileName_;

        SimpleLogger(){}
        ~SimpleLogger(){}

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
}

int main() {
    
    return 0;
}

