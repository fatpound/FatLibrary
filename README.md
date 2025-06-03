# FatLibrary

`General Algorithms & Utilities`
--------------------------------
This is my personal header-only library written in C++23 `(ISO/IEC 14882:2024)`, ready to be used with latest versions of GCC, Clang and MSVC compilers.

`Using The Library`
-------------------
Clone this repo to your project's include folder with this Git command: `git clone --recursive https://github.com/fatpound/FatLibrary.git`\
or\
Clone this repo to your project's include folder and update the submodules recursively:\
`git submodule update --init --recursive` **or** `git submodule update --recursive
`\
This repo can be used directly as a (static) library project in Visual Studio 2022\
Since it is header-only, there is no need to add a reference to that (static) library project. Using my [property sheets](https://github.com/fatpound/FatProps) will be enough.

`About The Code`
----------------
No warnings on `GCC 14.2` and `GCC 15.1` with [these](https://github.com/fatpound/CxxMade/blob/main/CompileOptions.cmake#L17-L56) compiler options\
No warnings on `Clang 19` with [these](https://github.com/fatpound/CxxMade/blob/main/CompileOptions.cmake#L58-L101) compiler options\
No warnings on `MSVC v19.43.34808` and `MSVC 19.44.35208` with [these](https://github.com/fatpound/CxxMade/blob/main/CompileOptions.cmake#L132-L209) compiler options\
No warnings with `Microsoft C++ Native Recommended Rules` and some more [rules](https://github.com/fatpound/FatLibrary/blob/main/_misc/FatRules.ruleset)\
No warnings in `clang-tidy 19` with [these](https://github.com/fatpound/CxxMade/blob/main/.clang-tidy) checks\
No warnings in `PVS-Studio v7.35`

`Class Diagram (outdated)`
--------------------------
![FatLibrary](https://github.com/user-attachments/assets/8ad721e9-1bb9-4d4e-a1db-6aec472766eb)
