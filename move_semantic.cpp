// Discovering move semantic

#include <vector>
#include <iostream>

using namespace std;

class MyClass {
public:
    MyClass(const MyClass &other) {
        cout << "copy ctor was called" << endl;
        closure_ = other.closure_;
    }

    MyClass(MyClass &&other) noexcept {
        cout << "move ctor was called" << endl;
        closure_.swap(other.closure_);
    }

    explicit MyClass(const vector<int> &data) : closure_(data) {
        cout << "param copy ctor was called" << endl;
    };

    explicit MyClass(vector<int> &&data) : closure_(std::move(data)) {
        cout << "param move ctor was called" << endl;
    };
private:
    vector<int> closure_;
};

vector<int> ReturnVector() {
    vector<int> vec = {1, 2, 3, 4, 5};
    return vec;
}

MyClass foo() {
    MyClass my_class({1, 2, 3, 4, 5});
    return my_class;
}

int main() {
    vector<int> vec = {1, 2, 3, 4, 5};

    MyClass my_class1(vec); // param copy ctor was called
    MyClass my_class2(std::move(vec)); // param move ctor was called
    MyClass my_class3(vector<int>{6, 7, 8, 9}); // param move ctor was called
    MyClass my_class4(std::move(vector<int>{6, 7, 8, 9})); // unnecessary move call
    MyClass my_class5({6, 7, 8, 9}); // param move ctor was called

    MyClass my_class6(ReturnVector()); // param move ctor was called
    MyClass my_class7(std::move(ReturnVector())); // unnecessary move call

    {
        MyClass test_foo(foo()); // param move ctor -> move ctor
        MyClass test_foo2(std::move(
                foo())); // param move ctor -> move ctor -> move ctor | Moving a temporary object prevents copy elision
    }
    {
        vector<int> &&test_foo = {6, 7, 8, 9}; // const
        MyClass my_class7(test_foo); // param copy ctor was called
        MyClass my_class8(const_cast<vector<int> &&>(test_foo)); // param move ctor was called
    }
}
