
// Good explanation
// https://pabloariasal.github.io/2017/06/10/understanding-virtual-tables/

// Memory
// 0xaddress -> ~MyClass() {/* some code */}

// 0xvtable_address -> vtable of class MyClass
// | ~MyClass | 0xaddress |
/*
class MyClass {
public:
  virtual ~MyClass() {}
  // hidden field
  // pointer to vtable of class MyClass = 0xvtable_address (vpointer) <- leads
to size 8
};

int main() {

  MyClass myClass;
  //(gdb) print sizeof(myClass)
  //$1 = 8
  // without virtual size will be 1

  return 0;
}
*/

#include <iostream>

using namespace std;

class Parent {
public:
  virtual void Foo() {}
  virtual ~Parent() { cout << "Dtor of Parent was called\n";}
  // vpointer to vtable of Parent
};

// vtable of Parent
// | Foo | 0xaddrFooParent
// | ~Parent | 0xaddrDtorParent

class Derived : public Parent {
public:
  void Foo() override {}
  // vpointer to vtable of Derived

  ~Derived() override { cout << "Dtor of Derived was called\n"; };
};

// vtable of Derived
// | Foo | 0xaddrFooDerived
// |~Derived | 0xaddrDtorDerived

// Memory
// 0xaddrFooParent - Foo code of Parent
// 0xaddrDtorParent - Dtor code of Parent
// 0xaddrFooDerived - Foo code of Derived
// 0xaddrDtorDerived - Dtor code of Derived

int main() {
  Parent *ptr = new Derived; // ptr points to object with hidden field pointer
                             // to vtable of Derived
  ptr->Foo();
  // vtable of Derived
  // | Foo | 0xaddrFooDerived <- is called

  delete ptr; // Dtor of |~Derived | 0xaddrDtorDerived is called
  // Dtor of Parent is called

  return 0;
}