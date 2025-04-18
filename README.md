# FatLibrary

`General Algorithms & Utilities`
--------------------------------
This is my personal header-only library written in C++23 `(ISO/IEC 14882:2024)`, to be used with latest versions of GCC, Clang and MSVC compilers.

`Using The Library`
-------------------
Clone this repo to your project's include folder with this Git command: `git clone --recursive https://github.com/fatpound/FatLibrary.git`\
or\
Clone this repo to your project's include folder and update the submodules recursively: `git submodule update --init --recursive`\
This repo can be used directly as a (static) library project in Visual Studio 2022

`About The Code`
----------------
No warnings on `g++14` with [these](https://github.com/fatpound/CxxMade/blob/main/CompileOptions.cmake#L6-L41) compiler options\
No warnings on `clang++19` with [these](https://github.com/fatpound/CxxMade/blob/main/CompileOptions.cmake#L42-L82) compiler options\
No warnings on `MSVC v19.43.34808` with [these](https://github.com/fatpound/CxxMade/blob/main/Fat_CompileOptions.cmake#L83-L124) compiler options\
No warnings with `Microsoft C++ Native Recommended Rules` and some more [rules](https://github.com/fatpound/FatLibrary/blob/main/_misc/FatRules.ruleset)\
No warnings in `clang-tidy 19` with [these](https://github.com/fatpound/CxxMade/blob/main/.clang-tidy) checks\
No warnings in `PVS-Studio v7.35`

`Class Diagram`
---------------
![FatLibrary](https://github.com/user-attachments/assets/8ad721e9-1bb9-4d4e-a1db-6aec472766eb)
