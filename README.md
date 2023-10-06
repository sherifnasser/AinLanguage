<p  align="center">
<img  src="https://github.com/sherifnasser/AinLanguage/assets/67873165/758c9fe3-f9fe-405f-8369-c340cf21153d"  width="100"  height="100">
</p>

# AinLanguage

**Ain programming language!**

A new **Arabic** programming language, built from scratch with **C++**, with no external libraries.

We plan to make the language self-hosted, which means, **Ain** will be written in **Ain**.

**Warning!** The language is under development and the code base may be changed in the future. [See open issues](https://github.com/sherifnasser/AinLanguage/issues).

[Follow us on YouTube](https://www.youtube.com/@AinProgrammingLanguage)

# Bug fixes in v0.2.1
Fix #35

# What's new in v0.2

#### New in the language

* Arrays

* Get and set operators

* Bitwise operators

#### New for contributors

* Add [`SetOperatorExpression`](https://github.com/sherifnasser/AinLanguage/blob/main/include/expression/SetOperatorExpression.hpp), [`NewArrayExpression`](https://github.com/sherifnasser/AinLanguage/blob/main/include/expression/ASTVistior.hpp) and [`AugmentedAssignStatement`](https://github.com/sherifnasser/AinLanguage/blob/main/include/statement/AugmentedAssignStatement.hpp)

# Ain and Unicode
**Ain** currently doesn't support some Unicode characters for some languages.

Also, **Ain** prevents Unicode characters that are considered Kufr or prohibited in Islam (Crosses, pride, music, etc.).

# Terminal RTL support
To support autodetecting of RTL text in your terminal emulator, you could run the command

```console
printf "\e[?2501h"
```
This will make your Arabic text appear from right to left.
You could also add this command at the end of `~/.bashrc` file to enable it permanently.

# Editor support
[`ain.lang`](https://github.com/sherifnasser/AinLanguage/blob/main/editor-support/ain.lang) is a syntax highlighting definition file that introduces the support for Ain in editors that use GtkSourceView (e.g. GNOME text editor gedit, GNOME Builder, mousepad, etc.)

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

