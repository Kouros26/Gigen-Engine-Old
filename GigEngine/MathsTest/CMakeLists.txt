cmake_minimum_required(VERSION 3.20)




# ~ FetchContent ~

include("FetchContent")

set(CMAKE_FOLDER_OLD ${CMAKE_FOLDER})
set_property(GLOBAL PROPERTY USE_FOLDERS ON)




# ~ glm

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        0.9.9.8
)
set(CMAKE_FOLDER "${CMAKE_FOLDER_OLD}/vendor/glm")

FetchContent_GetProperties(glm)
if(NOT glm_POPULATED)
    FetchContent_Populate(glm)
    set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
    add_subdirectory(${glm_SOURCE_DIR} ${glm_BINARY_DIR})
endif()

FetchContent_MakeAvailable(glm)


# ~ Catch2
FetchContent_Declare(
    Catch2
	GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
	GIT_TAG         v3.0.1
	GIT_SHALLOW		ON
)

set(CATCH_INSTALL_DOCS OFF)
set(CATCH_INSTALL_EXTRAS OFF)
    
set(CMAKE_FOLDER "${CMAKE_FOLDER_OLD}/vendor/catch")
FetchContent_MakeAvailable(Catch2)


# Move depencies to vendor folder
set(CMAKE_FOLDER ${CMAKE_FOLDER_OLD})



# ~ Sources ~ 
file(GLOB_RECURSE TARGET_HEADER_FILES
${CMAKE_CURRENT_SOURCE_DIR}/Headers/*.h
${CMAKE_CURRENT_SOURCE_DIR}/Headers/*.hpp
${CMAKE_CURRENT_SOURCE_DIR}/Headers/*.inl
)

file(GLOB_RECURSE TARGET_SOURCE_FILES
${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.c
${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cc
${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cxx
${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.c++
)



# ~ Target ~
set(TARGET_FILES ${TARGET_HEADER_FILES} ${TARGET_SOURCE_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_FILES})
set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Headers)



# ~ Executable ~

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
add_executable(${TARGET_NAME})
set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_sources(${TARGET_NAME} PRIVATE ${TARGET_FILES})

target_include_directories(${TARGET_NAME} PRIVATE ${TARGET_INCLUDE_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${LIBMATHS_INCLUDE_DIR})
target_include_directories(${TARGET_NAME} PRIVATE ${glm_SOURCE_DIR})

target_link_libraries(${TARGET_NAME} PRIVATE Catch2::Catch2)
target_link_libraries(${TARGET_NAME} PRIVATE ${LIBMATHS_LIBRARY})



# ~ Compiler ~

if(MSVC)
set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration) )

target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)
target_link_options(${TARGET_NAME} PRIVATE /FORCE:UNRESOLVED)
else()
message(WARNING "This CMakeLists.txt only run on Windows")
endif()


