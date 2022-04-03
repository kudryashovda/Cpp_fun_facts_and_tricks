/*
// Empty class size == 1 byte for its unique address identification

class MyClass {};

int main() {

  MyClass myClass;
  // (gdb) print sizeof(myClass)
  // $2 = 1

  return 0;
}

*/
// Empty class with method size == 1 byte

/*
class MyClass {
public:
  void Foo() { int a = 5; }
};

int main() {

  MyClass myClass;
  // (gdb) print sizeof(myClass)
  // $1 = 1

  return 0;
}
*/

/*
// Equal addreses of two objects. Compilator optimizations ???

class MyClass {
public:
  void Foo() { int a = 5; }
};

int main() {

  MyClass myClass1, myClass2;
  //(gdb) p &myClass1
  //$2 = (MyClass *) 0x7fffba4cc50f
  //(gdb) p &myClass2
  //$3 = (MyClass *) 0x7fffba4cc50f

  return 0;
}
*/

/*
// Different addreses of two objects

class MyClass {
public:
  void Foo() { int a = 5; }
};

int main() {

  MyClass* myClass1 =  new MyClass;
  MyClass* myClass2 =  new MyClass;

  delete myClass2;
  delete myClass1;

  //(gdb) p &myClass1
  //$1 = (MyClass **) 0x7ffee27423d0
  //(gdb) p &myClass2
  //$2 = (MyClass **) 0x7ffee27423d8

  return 0;
}
*/

// Different addreses of two objects

class MyClass {
public:
  void Foo() { int a = 5; }
  void Bar() { int b = 7; }
};

int main() {

  MyClass myClass1, myClass2;
  myClass1.Foo();
  myClass2.Bar();
  //(gdb) p &myClass1
  //$1 = (MyClass *) 0x7ffc02cd0766
  //(gdb) p &myClass2
  //$2 = (MyClass *)0x7ffc02cd0767

  return 0;
}
