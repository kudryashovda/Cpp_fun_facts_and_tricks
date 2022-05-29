#include <iostream>

using namespace std;

void externalFoo(const string &cmd) {
    cout << "call external foo with: " << cmd << endl;
}

bool matchPatternOne(const string &token) {
    return token == "One";
}

bool matchPatternTwo(const string &token) {
    return token == "Two";
}

bool matchPatternExit(const string &token) {
    return token == "Exit";
}

void stringReceived(const string &received) {
    // each branch has a lot of operations 
    if (matchPatternOne(received)) {
        // next stage like
        // auto key = matchPatternOne.get(0);
        // auto value = matchPatternOne.get(1);
        externalFoo(received);
    } else if (matchPatternExit(received)) {
        externalFoo(received);
        return;
    } else if (matchPatternTwo(received)) {
        externalFoo(received);
    }

    cout << "post matching functions" << endl;
}

// int main() {
//     stringReceivedNew("Unmatched");
//     stringReceivedNew("One");
//     stringReceivedNew("Two");
//     stringReceivedNew("Exit");

//     return 0;
// }

// New way
struct Helper
{
    inline static bool matched = false;
    static bool call(const string &recv, bool(*ftor)(const string&)) {
        matched = ftor(recv);
        return matched;
    }
    ~Helper() { matched = false; }
};

#define PROCESS(received, ftor) if (!Helper::matched && Helper::call(received, ftor))

void stringReceivedNew(const string &received)
{
    Helper helper;

    PROCESS(received, matchPatternOne) {
        externalFoo(received);
    };
    
    PROCESS(received, matchPatternTwo) {
        externalFoo(received);
    };
        
    PROCESS(received, matchPatternExit) {
        externalFoo(received);
        return;
    };

    cout << "post matching operations" << endl;
}

int main() {
    stringReceivedNew("Unmatched");
    stringReceivedNew("One");
    stringReceivedNew("Two");
    stringReceivedNew("Exit");

    return 0;
}
