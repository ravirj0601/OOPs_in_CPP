#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread> // Added for thread_func in main

using namespace std;

class Logger{
    public:
        enum class Level { INFO = 0, WARN = 1, ERROR = 2 };
        static Logger& inst();
        void setLevel(Level lvl);
        Level getLevel() const { return currentLevel_; } // Inline definition
        void log(Level lvl, const string& msg);
        void flush();

    private:
        string fileName;
        ofstream out;
        mutex mtx;
        Level currentLevel_;
        Logger();
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        ~Logger();
};

// Out-of-line definitions
Logger& Logger::inst(){
    static Logger instance;
    return instance;
}

Logger::Logger() : fileName("app.log"), currentLevel_(Level::INFO){
    out.open(fileName, std::ios::app);
    if (!out.is_open()) {
        cerr << "Logger: failed to open log file: " << fileName << "\n";
    }
}

Logger::~Logger(){
    if (out.is_open()) out.close();
}

void Logger::setLevel(Level lvl) {
    std::lock_guard<std::mutex> lock(mtx);
    currentLevel_ = lvl;
}

// Helper functions (can be static or free functions)
static std::string now_timestamp() {
    using namespace std::chrono;
    auto tp = system_clock::now();
    std::time_t t = system_clock::to_time_t(tp);
    std::tm tm{};
#if defined(_WIN32)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

static const char* level_to_cstr(Logger::Level lvl) {
    switch (lvl) {
        case Logger::Level::INFO:  return "INFO";
        case Logger::Level::WARN:  return "WARN";
        case Logger::Level::ERROR: return "ERROR";
    }
    return "UNK";
}

void Logger::log(Level lvl, const string& msg) {
    if (static_cast<int>(lvl) < static_cast<int>(currentLevel_)) return;

    std::string ts = now_timestamp();

    std::ostringstream line;
    line << "[" << ts << "]"
         << " [" << level_to_cstr(lvl) << "] "
         << msg << "\n";

    {
        std::lock_guard<std::mutex> lk(mtx);
        if (out.is_open()) {
            out << line.str();
        } else {
            std::cerr << line.str();
        }
    }
}

void Logger::flush() {
    std::lock_guard<std::mutex> lk(mtx);
    out.flush();
}

void thread_func(int id) {
    for (int i = 0; i < 10; ++i) { // Reduced loop count for quicker test
        Logger::inst().log(Logger::Level::INFO, "thread " + std::to_string(id) + " message " + std::to_string(i));
    }
}

int main() {
    Logger& logger = Logger::inst();

    logger.setLevel(Logger::Level::INFO);

    logger.log(Logger::Level::INFO, "Application started.");
    logger.log(Logger::Level::WARN, "Configuration file not found, using defaults.");
    logger.log(Logger::Level::ERROR, "Failed to connect to database!");

    logger.setLevel(Logger::Level::WARN);
    logger.log(Logger::Level::INFO, "This info message should not appear.");
    logger.log(Logger::Level::WARN, "Another warning message.");

    // Test with multiple threads
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) { // 5 threads for testing
        threads.emplace_back(thread_func, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    logger.flush();
    cout << "Log messages written to app.log\n";
    return 0;
}
