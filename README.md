# ZEN LIBRARY

## INTRODUCTION

Welcome to use zen library. First, I should declare that I'm a **Chinese**, I use English is simply for international. The name of the library comes from a famous Chinese scientist *"Qian Xue Sen"*, I use the similar pronounce of the last word of his name. He was a physicist, so this library contains ways to produce physics and maths. However this is more likely to be a **3D Game Developing Kit** with lot of base features init. Why not take a look.

## USAGE

It's very easy to use this library, you just copy *include* folder into your own project and start to use. 

**NOTICE** because zen is a very new library so it provides you a **C++20** module version. If your compiler supports C++20, than you can copy *module* folder into your project and **import** zen in your project.

## QUICK GUIDE

Check codes below to quick start!

```C++
// If you don't have a C++20 compiler, make sure you at least have a C++17 compiler.
// Quickguide.cpp

// Your folder may not same as this, but this is the vector.hpp under the include folder.
#if _HAS_CXX20
// Diffeerent platforms may have different macros.
// However this line of code could only avalible when your compiler supports  C++20.
import zen.vector;
#else
#include <zen/vector.hpp>
#endif
#include <iostream>

int main(int argc, char* argv[])
{
    // make_vec is a factory function to make vectors generically.
    // use different args to construct a vec2 or vec3 or vec4
    // this is a vec4.
    auto vec = zen::make_vec(1.0f, 2.0f, 3.0f, 4.0f);
    // use 'value_ptr()' to get a vectors original data.
    float* arr = zen::value_ptr(vec);

    std::cout << vec.modulus() << std::endl;
    // use clip_vec3 or clip_vec2 to get a smaller vec from a bigger vec.
    zen::vec3 _vec3 = vec.clip_vec3(0);
    
    // cross and dot are only avalible for vec2 and vec3
    auto vd = zen::dot(_vec3, zen::vec3{1.f, 2.f, 3.f});
    auto vc = zen::cross(_vec3, zen::vec3{1.f, 2.f, 3.f});

    std::cout << vd << std::endl;
    std::cout << vc << std::endl;

    return 0;
}


```



You can get more details by looking at the source code. because I think they are yes quite simple, their are comments so don't worry that you could'n understand.












