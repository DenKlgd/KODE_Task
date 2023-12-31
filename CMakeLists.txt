cmake_minimum_required(VERSION 3.8)

project("KODE_Task")

set(INC_FOLDER "include")
set(SRC_FOLDER "src")

set(SOURCES 
    ./${INC_FOLDER}/Object.h
    ./${INC_FOLDER}/Database.h
    ./${INC_FOLDER}/MenuPrinter.h
    ./${INC_FOLDER}/UI.h

    ./${SRC_FOLDER}/Object.cpp
    ./${SRC_FOLDER}/Database.cpp
    ./${SRC_FOLDER}/MenuPrinter.cpp
    ./${SRC_FOLDER}/UI.cpp
    main.cpp
)

if(CMAKE_HOST_WIN32)
    if (MSVC)
        add_compile_options(/source-charset:utf-8)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_options(/source-charset:utf-8)
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(-finput-charset=utf-8)
    endif()
endif()

add_executable(ObjectListApp ${SOURCES})
