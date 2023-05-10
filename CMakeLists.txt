cmake_minimum_required(VERSION 3.26.3)

project(AinLanguage)


set(SRC_FILES
    src/main.cpp
    src/lexer/lexer.cpp
    src/lexer/lexerline.cpp
    src/lexer/lexertoken.cpp
    src/ain_file/ain_file.cpp
    src/helpers/string_helper.cpp
)
set(INCLUDE
    include/
    include/lexer/
    include/ain_file/
    include/helpers/
)

add_executable(main ${SRC_FILES})

target_include_directories(main PUBLIC ${INCLUDE})
