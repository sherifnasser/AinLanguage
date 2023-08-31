<p  align="center">
<img  src="https://github.com/sherifnasser/AinLanguage/assets/67873165/758c9fe3-f9fe-405f-8369-c340cf21153d"  width="100"  height="100">
</p>

# AinLanguage

**Ain programming language!**

A new **Arabic** programming language, built from scratch with **C++**, with no external libraries.

# Quick demo

[See the video](https://youtu.be/eHRMpJHq0so)


# What's new in v0.0.5

***This version has a lot of super changes!***

#### New in the language

* Support working in multiple files

* Support visibility modifiers for members between files

* Support global variables

* Support type checking and type deduction

* Treat primitives as types with their built-in functions, which fixes treating integers as doubles
	* We're planning to remove the functions overhead when compile to native code

* Support delimited comments

* Basic support for classes
	* Defining properties and methods inside a class
	* Visibility modifiers for members inside it
	* Operator functions
	* Basic primary constructor (without parameters)

* Support checking for statements and expressions including checking for classes that have certain members, functions, or visibility when accessing them

#### New for contributors

* Add pretty printers for expressions

* Split parser to [`PackageParser`](https://github.com/sherifnasser/AinLanguage/blob/main/include/parser/PackageParser.hpp), [`FileParser`](https://github.com/sherifnasser/AinLanguage/blob/main/include/parser/FileParser.hpp), [`ClassParser`](https://github.com/sherifnasser/AinLanguage/blob/main/include/parser/ClassParser.hpp), [`FunParser`](https://github.com/sherifnasser/AinLanguage/blob/main/include/parser/FunParser.hpp), [`StmListParser`](https://github.com/sherifnasser/AinLanguage/blob/main/include/parser/StmListParser.hpp), [`VarStatementParser`](https://github.com/sherifnasser/AinLanguage/blob/main/include/parser/VarStatementParser.hpp), [`ExpressionParser`](https://github.com/sherifnasser/AinLanguage/blob/main/include/parser/ExpressionParser.hpp)

* Add parsers for common elements [`TypeParser`](https://github.com/sherifnasser/AinLanguage/blob/main/include/parser/elements/parser/TypeParser.hpp), [`FunParamParser`](https://github.com/sherifnasser/AinLanguage/blob/main/include/parser/elements/parser/FunParamParser.hpp), [`FunDeclParser`](https://github.com/sherifnasser/AinLanguage/blob/main/include/parser/elements/parser/FunDeclParser.hpp), [`VarDeclParser`](https://github.com/sherifnasser/AinLanguage/blob/main/include/parser/elements/parser/VarDeclParser.hpp)

* Add tests for some of the parsers

* Add [`PackageScope`](https://github.com/sherifnasser/AinLanguage/blob/main/include/scope/PackageScope.hpp), [`StmListScope`](https://github.com/sherifnasser/AinLanguage/blob/main/include/scope/StmListScope.hpp)

* Add a check method for every scope, statement, and expression

# TODO in v0.0.6

* Support multiple constructors in a class

* Support params in class constructors

* Support init blocks in classes

* Support unary operators

# Ain and Unicode
**Ain** currently doesn't support some Unicode characters for some languages.

Also, **Ain** prevents Unicode characters that are considered Kufr or prohibited in Islam (Crosses, pride, music, etc.).

# Editor support
[`ain.lang`](https://github.com/sherifnasser/AinLanguage/blob/main/editor-support/ain.lang) is a syntax highlighting definition file that introduces the support for Ain in editors that use GtkSourceView (e.g. GNOME text editor gedit, GNOME Builder, mousepad etc.)
#### How to install

* Create the directories for custom language files in your home directory

```console
mkdir -p ~/.local/share/gtksourceview-3.0/language-specs
mkdir -p ~/.local/share/gtksourceview-4/language-specs
```

* Copy [`ain.lang`](https://github.com/sherifnasser/AinLanguage/blob/main/editor-support/ain.lang) to `~/.local/share/gtksourceview-3.0/language-specs` and `~/.local/share/gtksourceview-4/language-specs`

* Copy [`text-x-ain.xml`](https://github.com/sherifnasser/AinLanguage/blob/main/editor-support/text-x-ain.xml) to `~/.local/share/mime/packages`

* Update mimetypes database
```console
update-mime-database ~/.local/share/mime
```

* Optional: copy [intellij-dracula.xml](https://github.com/sherifnasser/AinLanguage/blob/main/editor-support/intellij-dracula.xml) to `~/.local/share/gtksourceview-3.0/styles` and `~/.local/share/gtksourceview-4/styles` to enable intellij dark theme

# Build & run
**Ain** uses Make as a build system and uses [CMake](https://github.com/Kitware/CMake) to generate the Makefile.

If you added new include files or ***.cpp** files, you should add them to the [`CMakeLists.txt`](https://github.com/sherifnasser/AinLanguage/blob/main/CMakeLists.txt),

or you could run [`files_cmake`](https://github.com/sherifnasser/AinLanguage/blob/main/files_cmake.cpp) to automatically add them.

Make a build directory (if not exist), enter it, and then make the project
``` console
mkdir build		# Make a build directory (if not exist)
cd build		# Enter it
cmake ..
make			# make the project
```

Once you've built the project, you'll find an executable in the build/bin directory called **ain**, run it in the terminal and pass your ***.ain** files.

# Debug
Make a debug directory (if not exist), enter it, and then run these commands
``` console
mkdir debug		# Make a debug directory (if not exist)
cd debug		# Enter it
cmake -DCMAKE_BUILD_TYPE=Debug  ..
cmake --build  .
```

# Run unit tests

Ain uses [Catch2](https://github.com/catchorg/Catch2) for unit testing. All tests are included in the [test directory](https://github.com/sherifnasser/AinLanguage/blob/main/test/).

Once you've built the project the output executable **unit_tests** will be in the build/bin directory.

If you added new tests, you could run [`files_cmake`](https://github.com/sherifnasser/AinLanguage/blob/main/files_cmake.cpp) to automatically add them.