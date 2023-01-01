cmake_minimum_required(VERSION 3.25.1 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(MAKE_CXX_FLAGS "-O3")

project(pasukim VERSION 0.1)

######################## START OPTIONAL LIBS #####################
option(USE_ADDER "Sample lib" ON)
if (USE_ADDER)
    add_subdirectory(src/adder)
    list(APPEND EXTRA_INCLUDE_LIBS src/adder/include)
    list(APPEND EXTRA_LINK_DIRS src/adder) 
    list(APPEND EXTRA_LINK_LIBS adder)
endif()
######################## END OPTIONAL LIBS ########################

configure_file(include/pasukim_config.h.in pasukim_config.h)
add_executable(${PROJECT_NAME} src/pasukim.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR}) # is build dir, to include .h from config_file()

######################## START GIT SUBMODULES ######################
# Download all submodules (note this is right before add_subdir for the submod glfw)

find_package(Git QUIET)
if (GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git") #check there is a .git folder
    #Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if (GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if (NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodule")
        endif()
    endif()
endif()
# Check the submodules
if (NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The glfw submodule was not downloaded or cannot find its CMakeLists.txt! GIT_SUBMODULE was turned off or failed, please update submodule and try again")
endif()

######################## END GIT SUBMODULES #########################

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
    PUBLIC external/glfw/include
    PUBLIC ${EXTRA_INCLUDE_LIBS}
    PUBLIC /usr/local/Cellar/boost/1.80.0/include
) #specify include path(s), makes includes not need full path in code files /  can use <>

target_link_directories(${PROJECT_NAME}
    PRIVATE external/glfw/src
    /usr/local/Cellar/boost/1.80.0/lib
    PRIVATE ${EXTRA_LINK_DIRS}
    ) # dir rel to build to hold linked lib, where linker should look

target_link_libraries(${PROJECT_NAME}
    glfw
    boost_program_options
    ${EXTRA_LINK_LIBS}
) # specify libs to link when linking target, can be build system name (as here) or path to a lib or name of a lib to search for

# INSTALL
install(TARGETS pasukim DESTINATION bin) # DESTINATION: If a relative path is given it is interpreted relative to the value of the CMAKE_INSTALL_PREFIX variable.
install(FILES "${PROJECT_BINARY_DIR}/pasukim_config.h" DESTINATION include)

# CPACK
include(InstallRequiredSystemLibraries)
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/license.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${pasukim_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${pasukim_VERSION_MINOR}")
include(CPack)

