// clang++ -std=c++2a -c helloworld.cpp -Xclang -emit-module-interface -o helloworld.pcm

module;
#include <stdio.h>

export module helloworld;
export void hello();

module :private;
void hello() { puts("Hello world!"); }