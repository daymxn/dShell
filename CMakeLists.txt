cmake_minimum_required(VERSION 3.21)
project(dShell C)

set(CMAKE_C_STANDARD 99)

add_executable(dShell src/main.c src/util.c headers/util.h headers/pch.h src/string_builder.c headers/string_builder.h src/command.c headers/command.h src/tokenzier.c headers/tokenzier.h src/parser.c headers/parser.h src/executor.c headers/executor.h src/internal.c headers/internal.h src/lifecycle.c headers/lifecycle.h)
