// inspired by https://stackoverflow.com/questions/77005/how-to-automatically-generate-a-stacktrace-when-my-program-crashes

#include <execinfo.h>
#include <cstdio>
#include <cstdlib>

// need to add set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -rdynamic")
// to CMakeLists.txt to show foo names

void printStack() {
  void *array[10];

  // get void*'s for all entries on the stack
  int size = backtrace(array, 10);

  char **strings = backtrace_symbols(array, size);
  
  for (int i = 0; i < size; i++) {
    printf("%s\n", strings[i]);
  }
  puts("");
  free(strings);
}

void baz() {
  printf("bazzzzz\n");
  printStack();
}

void bar() { baz(); }
void foo() { bar(); }

int main() {
  foo();
}

/*
Prints:

bazzzzz
./print_stack(_Z10printStackv+0x28) [0x55b9889a5a22]
./print_stack(_Z3bazv+0x15) [0x55b9889a5ab2]
./print_stack(_Z3barv+0x9) [0x55b9889a5abe]
./print_stack(_Z3foov+0x9) [0x55b9889a5aca]
./print_stack(main+0x9) [0x55b9889a5ad6]
/lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xe7) [0x7f7097878c87]
./print_stack(_start+0x2a) [0x55b9889a591a]
*/