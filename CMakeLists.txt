cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER /usr/bin/gcc-6)
set(CMAKE_CXX_COMPILER /usr/bin/g++-6)

project(dimkush VERSION 0.0.1)

#установка компилятора (чтобы можно было между ними переключаться по потребности



include(CMakeTools/findApache.txt)
include(CMakeTools/findAPR.txt)

add_library(dimkush OBJECT src/dimkush.cpp)
include_directories(dimkush PUBLIC 
                    ${APACHE_INCLUDE_DIR}
                    ${APR_INCLUDE_DIR}    
                    )

set(OBJECTS_NAMES $<TARGET_OBJECTS:dimkush>)

set(OBJ_DIR ${CMAKE_CURRENT_BINARY_DIR}/obj_dir)

add_library(dimkush_shared SHARED ${OBJECTS_NAMES})


set_target_properties(dimkush
		      PROPERTIES 
                      COMPILE_OPTIONS "-fPIC;-DPIC;-c" #уровень оптимизации установлен как -O0 для -g
                      )


add_custom_command(TARGET dimkush_shared
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E make_directory ${OBJ_DIR}
COMMAND ${CMAKE_COMMAND} -E copy_if_different ${OBJECTS_NAMES} ${OBJ_DIR})


#bash command in build_dir/obj_dir
#sudo apxs -i -n mod_dimkush -c dimkush.cpp.o