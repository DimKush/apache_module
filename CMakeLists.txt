cmake_minimum_required(VERSION 3.10)

#install compiler variables
set(CMAKE_C_COMPILER /usr/bin/gcc-6)
set(CMAKE_CXX_COMPILER /usr/bin/g++-6)

project(json_module VERSION 0.0.1)

include(CMakeTools/findApache.cmake)
include(CMakeTools/findAPR.cmake)

set(RAPID_JSON_INTERNAL_DIR, ${PROJECT_SOURCE_DIR}/include/rapidjson)

add_library(json_module_obj OBJECT src/json_sample_module.c)
include_directories(json_module PUBLIC 
                    ${APACHE_INCLUDE_DIR}
                    ${APR_INCLUDE_DIR}    
                    )

add_library(wrapper OBJECT src/wrapper.cpp)
include_directories(wrapper PUBLIC 
                    ${APACHE_INCLUDE_DIR}
                    ${APR_INCLUDE_DIR}
                    ${PROJECT_SOURCE_DIR}/include    
                    )
target_include_directories(wrapper PUBLIC ${RAPID_JSON_INTERNAL_DIR})

#for building apache module
set(OBJECTS_NAMES $<TARGET_OBJECTS:json_module_obj> $<TARGET_OBJECTS:wrapper>)
set(OBJ_DIR ${CMAKE_CURRENT_BINARY_DIR}/obj_dir)
add_library(json_module_shared SHARED ${OBJECTS_NAMES})

set_target_properties(json_module_obj wrapper
		              PROPERTIES 
                      COMPILE_OPTIONS "-fPIC;-DPIC;-c" #compile flags
                      )

add_custom_command(TARGET json_module_shared
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E make_directory ${OBJ_DIR}
COMMAND ${CMAKE_COMMAND} -E copy_if_different ${OBJECTS_NAMES} ${OBJ_DIR})

#bash command in build_dir/obj_dir
#sudo apxs -i -n mod_dimkush -c dimkush.cpp.o
#sudo apxs -Wc,-fPIC -Wc, -lstdc++ -Wl, -c *.o