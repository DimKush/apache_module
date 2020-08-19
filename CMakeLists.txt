cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER /usr/bin/gcc-6)
set(CMAKE_CXX_COMPILER /usr/bin/g++-6)

project(sample_module VERSION 0.0.1)

#установка компилятора (чтобы можно было между ними переключаться по потребности

include(CMakeTools/findApache.txt)
include(CMakeTools/findAPR.txt)

add_library(dimkush SHARED src/sample_module.cpp)
include_directories(dimkush PUBLIC 
                    ${APACHE_INCLUDE_DIR}
                    ${APR_INCLUDE_DIR}    
                    )

set_target_properties(dimkush
		      PROPERTIES PREFIX "mod_"
                      COMPILE_OPTIONS "-c;-g;-O0;-fPIC;-Wall;-ansi;-pedantic;" #уровень оптимизации установлен как -O0 для -g
                      )
