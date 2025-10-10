#include <iostream>
using namespace std;
enum class Weekdays{
    Monday, Tuesday, Wednesday, Thirsday, Friday, Saturday, Sunday
};


int main() {
    Weekdays day = Weekdays::Friday;
    // For Int Cast
    // cout << static_cast<int>(Weekdays::Thirsday) << "\n";
    cout << static_cast<int>(day) << "\n";
    auto dayNo = static_cast<int>(day);
    switch (dayNo) {
        case 0:
            cout << "Khooni monday!\n";
            break;
        case 1:
            cout << "Long way to go!\n";
            break;
        case 2:
            cout << "Reached halfway Please survive!\n";
            break;
        case 3:
            cout << "Almost keep breathing!\n";
            break;
        case 4:
            cout << "Yey Last day Weekend is here.. Cheers!!!\n";
            break;
        case 5:
            cout << "Where am i, Who am I!!!\n";
            break;
        default:
            cout << "Pleaes let me sleep!!!\n";
            break;
    }
    return 0;
}

