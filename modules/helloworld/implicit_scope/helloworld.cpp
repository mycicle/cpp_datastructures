// clang++ -std=c++2a -c helloworld.cpp -Xclang -emit-module-interface -o helloworld.pcm

module;
#include <stdio.h>

export module helloworld;
export void hello() { puts("Hello world!"); }



// this is for use after vendors start to support modules themselves. This errors when I compile as of 11/10/2020
// clang++ -std=c++2a -fimplicit-modules -fimplicit-module-maps -c helloworld.cpp -Xclang -emit-module-interface -o helloworld.pcm

// export module helloworld;
// import <cstdio>;
// export void hello() { puts("Hello world!"); }