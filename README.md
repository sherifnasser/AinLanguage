
  

<p  align="center">

<img  src="https://github.com/sherifnasser/AinLanguage/assets/67873165/758c9fe3-f9fe-405f-8369-c340cf21153d"  width="100"  height="100">

</p>

  

# AinLanguage

**Ain programming language!**

  

A new **Arabic** programming language, that built from scratch with **C++**, with no external libraries.

  

# Quick demo

  

https://youtu.be/ukkViBr27ts

  

[Odd-Even program](https://youtu.be/kTKONLnWILQ)

  
  

# What's new in v0.0.4

  

#### New in the language

* Support lexing character literals

* Show errors when there are invalid tokens

* Support If-else statements

* Support while and do-while statements

* Support assignment operators

* Support reading a line

* Fix reading in arabic

#### New for contributors

* Use Java naming conventions

* Move lexer methods to LexerLine

* Use Catch2 for testing

* Write test for LexerLine

* Integrate tests with files_cmake.cpp

# TODO in v0.0.5

- Support basic OOP

- Add basic type checking

- Add tests for Parser

# Ain and Unicode
**Ain** currently doesn't support some Unicode characters for some languages.

Also, **Ain** prevents Unicode characters that  are considered Kufr or prohibited in Islam (Crosses, pride, music, etc.).

# Build & run

**Ain** uses Make as a build system, and uses [CMake](https://github.com/Kitware/CMake) to generate the Makefile.

If you added new include files or ***.cpp** files, you should add them to the [CMakeLists.txt](https://github.com/sherifnasser/AinLanguage/blob/main/CMakeLists.txt),

  

or you could run [files_cmake](https://github.com/sherifnasser/AinLanguage/blob/main/files_cmake.cpp) to automatically add them.

  

Once you've built the project, you'll find an executable in [build directory](https://github.com/sherifnasser/AinLanguage/blob/main/build/) called **ain**, run it in terminal and pass your ***.ain** file.

  

You could also use (Only on linux) [run.sh](https://github.com/sherifnasser/AinLanguage/blob/main/run.sh).

  

and it will run this [app.ain](https://github.com/sherifnasser/AinLanguage/blob/main/app.ain).

  

# Debug

You could use (Only on linux) [debug-build.sh](https://github.com/sherifnasser/AinLanguage/blob/main/debug-build.sh) to debug. The out executable in [debug directory](https://github.com/sherifnasser/AinLanguage/blob/main/debug/).

  

# Run unit tests

Ain uses [Catch2](https://github.com/catchorg/Catch2) for unit testing. All tests are include in the [test directory](https://github.com/sherifnasser/AinLanguage/blob/main/test/). The out executable **unit_tests** is in build directory.

If you added new tests, you could run [files_cmake](https://github.com/sherifnasser/AinLanguage/blob/main/files_cmake.cpp) to automatically add them.
