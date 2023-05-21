<p align="center">
<img src="https://github.com/sherifnasser/AinLanguage/assets/67873165/758c9fe3-f9fe-405f-8369-c340cf21153d" width="100" height="100">
 </p>

# AinLanguage
السلام عليكم ورحمة الله وبركاته
---

Welcome to ain programming language!  
A new arabic programming language, that built from scratch with c++, with no external libraries.
# Quick demo
https://youtu.be/hd-uTFrhWXE
# What's new in v0.0.3
* Declaring variables and constants
* Preform math & bool operations
* Declaring & calling functions
* Support return statement for functions
* Basic input/output to the console
# TODO in v0.0.4
- Support conditional statements
- Support loop statements
- Support assignment operators
# Build & run
Ain uses Make as a build system, and uses CMake to generate the Makefile.  
If you added new include files or *.cpp files, you should add them to the [CMakeLists.txt](https://github.com/sherifnasser/AinLanguage/blob/main/CMakeLists.txt),
or you could run [this script](https://github.com/sherifnasser/AinLanguage/blob/main/files_cmake.cpp) to automatically add them.  
Once you've built the project, you'll find an executable in build folder called ain, run it in terminal and pass your *.ain file.  
You could also use (Only on linux) [run.sh](https://github.com/sherifnasser/AinLanguage/blob/main/run.sh)
and it will run this [app.ain](https://github.com/sherifnasser/AinLanguage/blob/main/src/app.ain)
