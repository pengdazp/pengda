cmake_minimum_required(VERSION 3.25)
project(PengdaEnglishStudy)

set(CMAKE_CXX_STANDARD 14)

add_executable(PengdaEnglishStudy main.cpp  include/Http.h include/Http.cpp md5.cpp md5.h main.h )