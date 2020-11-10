/*
// from cppcon 2017 slides
$ clang++ -std=c++2a -fmodules-ts --precompile -x c++-module [...] -o hello.pcm hello.mxx
$ clang++ -std=c++2a -fmodules-ts -o hello.pcm.o -c hello.pcm
$ clang++ -std=c++2a -fmodules-ts -x c++ -o hello.o -fmodule-file=hello.pcm -c hello.cxx
$ clang++ -std=c++2a -fmodules-ts -x c++ -o driver.o -fmodule-file=hello=hello.pcm -c driver.cxx
$ clang++ -o hello hello.pcm.o driver.o hello.o

[...] = -Xclang -fmodules-embed-all-files -Xclang -fmodules-codegen -Xclang -fmodules-debuginfo


// use these
$ clang++ -std=c++2a -fmodules-ts --precompile -x c++-module -Xclang -fmodules-embed-all-files -Xclang -fmodules-codegen -Xclang -fmodules-debuginfo -o hello.pcm hello.hh
$ clang++ -std=c++2a -fmodules-ts -o hello.pcm.o -c hello.pcm
$ clang++ -std=c++2a -fmodules-ts -x c++ -o hello.o -fmodule-file=hello.pcm -c hello.cpp
$ clang++ -std=c++2a -fmodules-ts -x c++ -o driver.o -fmodule-file=hello=hello.pcm -c driver.cpp
$ clang++ -o hello hello.pcm.o driver.o hello.o
*/

import hello;

int main() {
    say_hello("Modules");
    return 0;
}