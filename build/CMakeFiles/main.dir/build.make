# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nasser/Projects/Programming/C++/AinLanguage

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nasser/Projects/Programming/C++/AinLanguage/build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/src/main.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/main.cpp.o: /home/nasser/Projects/Programming/C++/AinLanguage/src/main.cpp
CMakeFiles/main.dir/src/main.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasser/Projects/Programming/C++/AinLanguage/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/src/main.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/main.cpp.o -MF CMakeFiles/main.dir/src/main.cpp.o.d -o CMakeFiles/main.dir/src/main.cpp.o -c /home/nasser/Projects/Programming/C++/AinLanguage/src/main.cpp

CMakeFiles/main.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/main.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasser/Projects/Programming/C++/AinLanguage/src/main.cpp > CMakeFiles/main.dir/src/main.cpp.i

CMakeFiles/main.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/main.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasser/Projects/Programming/C++/AinLanguage/src/main.cpp -o CMakeFiles/main.dir/src/main.cpp.s

CMakeFiles/main.dir/src/lexer/lexer.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/lexer/lexer.cpp.o: /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/lexer.cpp
CMakeFiles/main.dir/src/lexer/lexer.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasser/Projects/Programming/C++/AinLanguage/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/src/lexer/lexer.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/lexer/lexer.cpp.o -MF CMakeFiles/main.dir/src/lexer/lexer.cpp.o.d -o CMakeFiles/main.dir/src/lexer/lexer.cpp.o -c /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/lexer.cpp

CMakeFiles/main.dir/src/lexer/lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/lexer/lexer.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/lexer.cpp > CMakeFiles/main.dir/src/lexer/lexer.cpp.i

CMakeFiles/main.dir/src/lexer/lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/lexer/lexer.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/lexer.cpp -o CMakeFiles/main.dir/src/lexer/lexer.cpp.s

CMakeFiles/main.dir/src/lexer/keywordtoken.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/lexer/keywordtoken.cpp.o: /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/keywordtoken.cpp
CMakeFiles/main.dir/src/lexer/keywordtoken.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasser/Projects/Programming/C++/AinLanguage/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/src/lexer/keywordtoken.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/lexer/keywordtoken.cpp.o -MF CMakeFiles/main.dir/src/lexer/keywordtoken.cpp.o.d -o CMakeFiles/main.dir/src/lexer/keywordtoken.cpp.o -c /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/keywordtoken.cpp

CMakeFiles/main.dir/src/lexer/keywordtoken.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/lexer/keywordtoken.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/keywordtoken.cpp > CMakeFiles/main.dir/src/lexer/keywordtoken.cpp.i

CMakeFiles/main.dir/src/lexer/keywordtoken.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/lexer/keywordtoken.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/keywordtoken.cpp -o CMakeFiles/main.dir/src/lexer/keywordtoken.cpp.s

CMakeFiles/main.dir/src/lexer/lexerline.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/lexer/lexerline.cpp.o: /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/lexerline.cpp
CMakeFiles/main.dir/src/lexer/lexerline.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasser/Projects/Programming/C++/AinLanguage/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/src/lexer/lexerline.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/lexer/lexerline.cpp.o -MF CMakeFiles/main.dir/src/lexer/lexerline.cpp.o.d -o CMakeFiles/main.dir/src/lexer/lexerline.cpp.o -c /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/lexerline.cpp

CMakeFiles/main.dir/src/lexer/lexerline.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/lexer/lexerline.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/lexerline.cpp > CMakeFiles/main.dir/src/lexer/lexerline.cpp.i

CMakeFiles/main.dir/src/lexer/lexerline.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/lexer/lexerline.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/lexerline.cpp -o CMakeFiles/main.dir/src/lexer/lexerline.cpp.s

CMakeFiles/main.dir/src/lexer/symboltoken.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/lexer/symboltoken.cpp.o: /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/symboltoken.cpp
CMakeFiles/main.dir/src/lexer/symboltoken.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasser/Projects/Programming/C++/AinLanguage/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/src/lexer/symboltoken.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/lexer/symboltoken.cpp.o -MF CMakeFiles/main.dir/src/lexer/symboltoken.cpp.o.d -o CMakeFiles/main.dir/src/lexer/symboltoken.cpp.o -c /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/symboltoken.cpp

CMakeFiles/main.dir/src/lexer/symboltoken.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/lexer/symboltoken.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/symboltoken.cpp > CMakeFiles/main.dir/src/lexer/symboltoken.cpp.i

CMakeFiles/main.dir/src/lexer/symboltoken.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/lexer/symboltoken.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/symboltoken.cpp -o CMakeFiles/main.dir/src/lexer/symboltoken.cpp.s

CMakeFiles/main.dir/src/lexer/lexertoken.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/lexer/lexertoken.cpp.o: /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/lexertoken.cpp
CMakeFiles/main.dir/src/lexer/lexertoken.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasser/Projects/Programming/C++/AinLanguage/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/main.dir/src/lexer/lexertoken.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/lexer/lexertoken.cpp.o -MF CMakeFiles/main.dir/src/lexer/lexertoken.cpp.o.d -o CMakeFiles/main.dir/src/lexer/lexertoken.cpp.o -c /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/lexertoken.cpp

CMakeFiles/main.dir/src/lexer/lexertoken.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/lexer/lexertoken.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/lexertoken.cpp > CMakeFiles/main.dir/src/lexer/lexertoken.cpp.i

CMakeFiles/main.dir/src/lexer/lexertoken.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/lexer/lexertoken.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasser/Projects/Programming/C++/AinLanguage/src/lexer/lexertoken.cpp -o CMakeFiles/main.dir/src/lexer/lexertoken.cpp.s

CMakeFiles/main.dir/src/ain_file/ain_file.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/ain_file/ain_file.cpp.o: /home/nasser/Projects/Programming/C++/AinLanguage/src/ain_file/ain_file.cpp
CMakeFiles/main.dir/src/ain_file/ain_file.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasser/Projects/Programming/C++/AinLanguage/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/main.dir/src/ain_file/ain_file.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/ain_file/ain_file.cpp.o -MF CMakeFiles/main.dir/src/ain_file/ain_file.cpp.o.d -o CMakeFiles/main.dir/src/ain_file/ain_file.cpp.o -c /home/nasser/Projects/Programming/C++/AinLanguage/src/ain_file/ain_file.cpp

CMakeFiles/main.dir/src/ain_file/ain_file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/ain_file/ain_file.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasser/Projects/Programming/C++/AinLanguage/src/ain_file/ain_file.cpp > CMakeFiles/main.dir/src/ain_file/ain_file.cpp.i

CMakeFiles/main.dir/src/ain_file/ain_file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/ain_file/ain_file.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasser/Projects/Programming/C++/AinLanguage/src/ain_file/ain_file.cpp -o CMakeFiles/main.dir/src/ain_file/ain_file.cpp.s

CMakeFiles/main.dir/src/statement/statement.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/statement/statement.cpp.o: /home/nasser/Projects/Programming/C++/AinLanguage/src/statement/statement.cpp
CMakeFiles/main.dir/src/statement/statement.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasser/Projects/Programming/C++/AinLanguage/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/main.dir/src/statement/statement.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/statement/statement.cpp.o -MF CMakeFiles/main.dir/src/statement/statement.cpp.o.d -o CMakeFiles/main.dir/src/statement/statement.cpp.o -c /home/nasser/Projects/Programming/C++/AinLanguage/src/statement/statement.cpp

CMakeFiles/main.dir/src/statement/statement.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/statement/statement.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasser/Projects/Programming/C++/AinLanguage/src/statement/statement.cpp > CMakeFiles/main.dir/src/statement/statement.cpp.i

CMakeFiles/main.dir/src/statement/statement.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/statement/statement.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasser/Projects/Programming/C++/AinLanguage/src/statement/statement.cpp -o CMakeFiles/main.dir/src/statement/statement.cpp.s

CMakeFiles/main.dir/src/helpers/string_helper.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/helpers/string_helper.cpp.o: /home/nasser/Projects/Programming/C++/AinLanguage/src/helpers/string_helper.cpp
CMakeFiles/main.dir/src/helpers/string_helper.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasser/Projects/Programming/C++/AinLanguage/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/main.dir/src/helpers/string_helper.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/helpers/string_helper.cpp.o -MF CMakeFiles/main.dir/src/helpers/string_helper.cpp.o.d -o CMakeFiles/main.dir/src/helpers/string_helper.cpp.o -c /home/nasser/Projects/Programming/C++/AinLanguage/src/helpers/string_helper.cpp

CMakeFiles/main.dir/src/helpers/string_helper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/helpers/string_helper.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasser/Projects/Programming/C++/AinLanguage/src/helpers/string_helper.cpp > CMakeFiles/main.dir/src/helpers/string_helper.cpp.i

CMakeFiles/main.dir/src/helpers/string_helper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/helpers/string_helper.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasser/Projects/Programming/C++/AinLanguage/src/helpers/string_helper.cpp -o CMakeFiles/main.dir/src/helpers/string_helper.cpp.s

CMakeFiles/main.dir/src/helpers/wchar_t_helper.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/helpers/wchar_t_helper.cpp.o: /home/nasser/Projects/Programming/C++/AinLanguage/src/helpers/wchar_t_helper.cpp
CMakeFiles/main.dir/src/helpers/wchar_t_helper.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasser/Projects/Programming/C++/AinLanguage/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/main.dir/src/helpers/wchar_t_helper.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/helpers/wchar_t_helper.cpp.o -MF CMakeFiles/main.dir/src/helpers/wchar_t_helper.cpp.o.d -o CMakeFiles/main.dir/src/helpers/wchar_t_helper.cpp.o -c /home/nasser/Projects/Programming/C++/AinLanguage/src/helpers/wchar_t_helper.cpp

CMakeFiles/main.dir/src/helpers/wchar_t_helper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/helpers/wchar_t_helper.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasser/Projects/Programming/C++/AinLanguage/src/helpers/wchar_t_helper.cpp > CMakeFiles/main.dir/src/helpers/wchar_t_helper.cpp.i

CMakeFiles/main.dir/src/helpers/wchar_t_helper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/helpers/wchar_t_helper.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasser/Projects/Programming/C++/AinLanguage/src/helpers/wchar_t_helper.cpp -o CMakeFiles/main.dir/src/helpers/wchar_t_helper.cpp.s

CMakeFiles/main.dir/src/helpers/number_helper.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/helpers/number_helper.cpp.o: /home/nasser/Projects/Programming/C++/AinLanguage/src/helpers/number_helper.cpp
CMakeFiles/main.dir/src/helpers/number_helper.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasser/Projects/Programming/C++/AinLanguage/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/main.dir/src/helpers/number_helper.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/helpers/number_helper.cpp.o -MF CMakeFiles/main.dir/src/helpers/number_helper.cpp.o.d -o CMakeFiles/main.dir/src/helpers/number_helper.cpp.o -c /home/nasser/Projects/Programming/C++/AinLanguage/src/helpers/number_helper.cpp

CMakeFiles/main.dir/src/helpers/number_helper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/helpers/number_helper.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasser/Projects/Programming/C++/AinLanguage/src/helpers/number_helper.cpp > CMakeFiles/main.dir/src/helpers/number_helper.cpp.i

CMakeFiles/main.dir/src/helpers/number_helper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/helpers/number_helper.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasser/Projects/Programming/C++/AinLanguage/src/helpers/number_helper.cpp -o CMakeFiles/main.dir/src/helpers/number_helper.cpp.s

CMakeFiles/main.dir/src/parser/scope/scope.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/parser/scope/scope.cpp.o: /home/nasser/Projects/Programming/C++/AinLanguage/src/parser/scope/scope.cpp
CMakeFiles/main.dir/src/parser/scope/scope.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasser/Projects/Programming/C++/AinLanguage/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/main.dir/src/parser/scope/scope.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/parser/scope/scope.cpp.o -MF CMakeFiles/main.dir/src/parser/scope/scope.cpp.o.d -o CMakeFiles/main.dir/src/parser/scope/scope.cpp.o -c /home/nasser/Projects/Programming/C++/AinLanguage/src/parser/scope/scope.cpp

CMakeFiles/main.dir/src/parser/scope/scope.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/parser/scope/scope.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasser/Projects/Programming/C++/AinLanguage/src/parser/scope/scope.cpp > CMakeFiles/main.dir/src/parser/scope/scope.cpp.i

CMakeFiles/main.dir/src/parser/scope/scope.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/parser/scope/scope.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasser/Projects/Programming/C++/AinLanguage/src/parser/scope/scope.cpp -o CMakeFiles/main.dir/src/parser/scope/scope.cpp.s

CMakeFiles/main.dir/src/parser/scope/globalscope.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/parser/scope/globalscope.cpp.o: /home/nasser/Projects/Programming/C++/AinLanguage/src/parser/scope/globalscope.cpp
CMakeFiles/main.dir/src/parser/scope/globalscope.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasser/Projects/Programming/C++/AinLanguage/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/main.dir/src/parser/scope/globalscope.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/parser/scope/globalscope.cpp.o -MF CMakeFiles/main.dir/src/parser/scope/globalscope.cpp.o.d -o CMakeFiles/main.dir/src/parser/scope/globalscope.cpp.o -c /home/nasser/Projects/Programming/C++/AinLanguage/src/parser/scope/globalscope.cpp

CMakeFiles/main.dir/src/parser/scope/globalscope.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/parser/scope/globalscope.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasser/Projects/Programming/C++/AinLanguage/src/parser/scope/globalscope.cpp > CMakeFiles/main.dir/src/parser/scope/globalscope.cpp.i

CMakeFiles/main.dir/src/parser/scope/globalscope.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/parser/scope/globalscope.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasser/Projects/Programming/C++/AinLanguage/src/parser/scope/globalscope.cpp -o CMakeFiles/main.dir/src/parser/scope/globalscope.cpp.s

CMakeFiles/main.dir/src/parser/expression.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/parser/expression.cpp.o: /home/nasser/Projects/Programming/C++/AinLanguage/src/parser/expression.cpp
CMakeFiles/main.dir/src/parser/expression.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasser/Projects/Programming/C++/AinLanguage/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/main.dir/src/parser/expression.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/parser/expression.cpp.o -MF CMakeFiles/main.dir/src/parser/expression.cpp.o.d -o CMakeFiles/main.dir/src/parser/expression.cpp.o -c /home/nasser/Projects/Programming/C++/AinLanguage/src/parser/expression.cpp

CMakeFiles/main.dir/src/parser/expression.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/parser/expression.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasser/Projects/Programming/C++/AinLanguage/src/parser/expression.cpp > CMakeFiles/main.dir/src/parser/expression.cpp.i

CMakeFiles/main.dir/src/parser/expression.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/parser/expression.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasser/Projects/Programming/C++/AinLanguage/src/parser/expression.cpp -o CMakeFiles/main.dir/src/parser/expression.cpp.s

CMakeFiles/main.dir/src/parser/parser.cpp.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/parser/parser.cpp.o: /home/nasser/Projects/Programming/C++/AinLanguage/src/parser/parser.cpp
CMakeFiles/main.dir/src/parser/parser.cpp.o: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nasser/Projects/Programming/C++/AinLanguage/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/main.dir/src/parser/parser.cpp.o"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/parser/parser.cpp.o -MF CMakeFiles/main.dir/src/parser/parser.cpp.o.d -o CMakeFiles/main.dir/src/parser/parser.cpp.o -c /home/nasser/Projects/Programming/C++/AinLanguage/src/parser/parser.cpp

CMakeFiles/main.dir/src/parser/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/src/parser/parser.cpp.i"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nasser/Projects/Programming/C++/AinLanguage/src/parser/parser.cpp > CMakeFiles/main.dir/src/parser/parser.cpp.i

CMakeFiles/main.dir/src/parser/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/parser/parser.cpp.s"
	/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nasser/Projects/Programming/C++/AinLanguage/src/parser/parser.cpp -o CMakeFiles/main.dir/src/parser/parser.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/src/main.cpp.o" \
"CMakeFiles/main.dir/src/lexer/lexer.cpp.o" \
"CMakeFiles/main.dir/src/lexer/keywordtoken.cpp.o" \
"CMakeFiles/main.dir/src/lexer/lexerline.cpp.o" \
"CMakeFiles/main.dir/src/lexer/symboltoken.cpp.o" \
"CMakeFiles/main.dir/src/lexer/lexertoken.cpp.o" \
"CMakeFiles/main.dir/src/ain_file/ain_file.cpp.o" \
"CMakeFiles/main.dir/src/statement/statement.cpp.o" \
"CMakeFiles/main.dir/src/helpers/string_helper.cpp.o" \
"CMakeFiles/main.dir/src/helpers/wchar_t_helper.cpp.o" \
"CMakeFiles/main.dir/src/helpers/number_helper.cpp.o" \
"CMakeFiles/main.dir/src/parser/scope/scope.cpp.o" \
"CMakeFiles/main.dir/src/parser/scope/globalscope.cpp.o" \
"CMakeFiles/main.dir/src/parser/expression.cpp.o" \
"CMakeFiles/main.dir/src/parser/parser.cpp.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/src/main.cpp.o
main: CMakeFiles/main.dir/src/lexer/lexer.cpp.o
main: CMakeFiles/main.dir/src/lexer/keywordtoken.cpp.o
main: CMakeFiles/main.dir/src/lexer/lexerline.cpp.o
main: CMakeFiles/main.dir/src/lexer/symboltoken.cpp.o
main: CMakeFiles/main.dir/src/lexer/lexertoken.cpp.o
main: CMakeFiles/main.dir/src/ain_file/ain_file.cpp.o
main: CMakeFiles/main.dir/src/statement/statement.cpp.o
main: CMakeFiles/main.dir/src/helpers/string_helper.cpp.o
main: CMakeFiles/main.dir/src/helpers/wchar_t_helper.cpp.o
main: CMakeFiles/main.dir/src/helpers/number_helper.cpp.o
main: CMakeFiles/main.dir/src/parser/scope/scope.cpp.o
main: CMakeFiles/main.dir/src/parser/scope/globalscope.cpp.o
main: CMakeFiles/main.dir/src/parser/expression.cpp.o
main: CMakeFiles/main.dir/src/parser/parser.cpp.o
main: CMakeFiles/main.dir/build.make
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nasser/Projects/Programming/C++/AinLanguage/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/nasser/Projects/Programming/C++/AinLanguage/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nasser/Projects/Programming/C++/AinLanguage /home/nasser/Projects/Programming/C++/AinLanguage /home/nasser/Projects/Programming/C++/AinLanguage/build /home/nasser/Projects/Programming/C++/AinLanguage/build /home/nasser/Projects/Programming/C++/AinLanguage/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

