#include <iostream>
#include <mutex>
#include <string>
#include <unordered_map>
using namespace std;

class Config{
    private:
        // Step 1: Create Private Constr
        Config(){
            cout << "Config Created...!\n";
        }
        ~Config() = default;
        // Step 2: Delete copy and move Constr
            // Delete Copy Constructor
        Config(const Config&) = delete;
            // Delete Move Constructor
        Config& operator=(const Config&) = delete;
        
        unordered_map<string, string> data_;
        mutex mtx_;
    public:
        // Step 3: Static accessor
        static Config& instance() {
            static Config inst;
            return inst;
        }

        // Example Method
        void set(const string &key, const string &value){
            lock_guard<mutex> lk(mtx_);
            data_[key] = value;
        }

        string get(const string& key){
            lock_guard<mutex> lk(mtx_);
            static const string empty = " ";
            auto it = data_.find(key);
            return it != data_.end() ? it->second : empty;
            // return data_[key];
        }

};
int main() {
    // Access the singleton instance
    Config& config1 = Config::instance();
    Config& config2 = Config::instance();

    // Verify that both references point to the same instance
    if (&config1 == &config2) {
        cout << "Both config1 and config2 refer to the same instance.\n";
    } else {
        cout << "Error: Multiple instances created.\n";
    }

    // Set some configuration values
    config1.set("database_host", "localhost");
    config1.set("database_port", "5432");
    config2.set("api_key", "your_secret_api_key"); // Can use config2 to set values

    // Get and print configuration values
    cout << "Database Host: " << config1.get("database_host") << "\n";
    cout << "Database Port: " << config2.get("database_port") << "\n"; // Can use config2 to get values
    cout << "API Key: " << config1.get("api_key") << "\n";

    // Test a non-existent key
    cout << "Non-existent Key: " << config1.get("non_existent_key") << "\n";

    return 0;
}

