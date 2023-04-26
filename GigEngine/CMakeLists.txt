cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(CMAKE_FOLDER_OLD ${CMAKE_FOLDER})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMakeModules")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})

set(THIRD_PARTY_DLL
	${DEPENDS_DIR}/assimp/bin/assimp-vc143-mt.dll
	${DEPENDS_DIR}/assimp/bin/assimp-vc143-mtd.dll

)


set( THIRD_PARTY_PROJECT
   Editor
   Engine
   Physics
)


include("FetchContent")
FetchContent_Declare(
	GLFW
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.3.8)
	
set(CMAKE_FOLDER "${CMAKE_FOLDER_OLD}/vendor/glfw")
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
FetchContent_MakeAvailable(GLFW)



FetchContent_Declare(
    LibMath
    GIT_REPOSITORY https://github.com/Angel-2180/LibMaths.git
	GIT_TAG master)

set(CMAKE_FOLDER "${CMAKE_FOLDER_OLD}/vendor/lm")
FetchContent_MakeAvailable(LibMath)


set(CMAKE_FOLDER ${CMAKE_FOLDER_OLD})


#Add BULLET
set(BULLET_BUILD_LIB_DIR "${DEPENDS_DIR}/BULLET/lib")
set(BULLET_ROOT "${DEPENDS_DIR}/BULLET")

find_package(Bullet REQUIRED)


set( THIRD_PARTY_INCLUDE
assimp
STB
BULLET

)

include_directories(${MAIN_PROJECT_NAME} PRIVATE ${glfw_SOURCE_DIR}/include)
include_directories(${MAIN_PROJECT_NAME} PRIVATE ${DEPENDS_DIR}/Assimp/include)
include_directories(${MAIN_PROJECT_NAME} PRIVATE ${LIBMATHS_INCLUDE_DIR})


foreach( project_i ${THIRD_PARTY_PROJECT})
add_subdirectory(${project_i})
include_directories(${MAIN_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${project_i}/${INCLUDE_FOLDER})
endforeach( project_i )

foreach( include_i ${THIRD_PARTY_INCLUDE})
include_directories(${MAIN_PROJECT_NAME} PRIVATE ${DEPENDS_DIR}/${include_i}/${INCLUDE_FOLDER})
endforeach( include_i )


add_subdirectory(MathsTest)


set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${MAIN_PROJECT_NAME}/${SOURCE_FOLDER})
file(GLOB_RECURSE SOURCE_FILES 
${PROJECT_SOURCE_DIR}/*.c
${PROJECT_SOURCE_DIR}/*.cc
${PROJECT_SOURCE_DIR}/*.cpp
${PROJECT_SOURCE_DIR}/*.cxx
${PROJECT_SOURCE_DIR}/*.c++)

set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${MAIN_PROJECT_NAME}/${INCLUDE_FOLDER})
file(GLOB_RECURSE HEADER_FILES 
${PROJECT_INCLUDE_DIR}/*.h
${PROJECT_INCLUDE_DIR}/*.hpp
${PROJECT_INCLUDE_DIR}/*.inl)

add_executable(${MAIN_PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} )

target_include_directories(${MAIN_PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE_DIR})
target_link_libraries(${MAIN_PROJECT_NAME} PRIVATE ${THIRD_PARTY_PROJECT})
target_link_libraries(${MAIN_PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${MAIN_PROJECT_NAME} PRIVATE ${LIBMATHS_LIBRARY})



set_target_properties(${MAIN_PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))
target_compile_options(${MAIN_PROJECT_NAME} PRIVATE /W4)
#Copy resources Folder
add_custom_command(TARGET ${MAIN_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
		${RESOURCES_DIR}
        $<TARGET_FILE_DIR:${MAIN_PROJECT_NAME}>/Resources)
		

#look for shader
file(GLOB_RECURSE TARGET_SHADER_FILES #any name for extentions --> choice 
	${RESOURCES_DIR}/*.vert
	${RESOURCES_DIR}/*.frag
	${RESOURCES_DIR}/*.geom
	${RESOURCES_DIR}/*.tesc
	${RESOURCES_DIR}/*.tese
	${RESOURCES_DIR}/*.comp
	${RESOURCES_DIR}/*.glsl)

#Add raw file to main with filter
source_group(Shaders FILES ${TARGET_SHADER_FILES})
target_sources(${MAIN_PROJECT_NAME} PRIVATE ${TARGET_SHADER_FILES})

# IMGUI
set(CMAKE_FOLDER_OLD ${CMAKE_FOLDER})
set(CMAKE_FOLDER "${CMAKE_FOLDER_OLD}/vendor/ImGui")

file(GLOB_RECURSE IMGUI_SOURCES ${DEPENDS_DIR}/IMGUI/*.cpp ${DEPENDS_DIR}/IMGUI/*.h)
add_library(ImGui STATIC ${IMGUI_SOURCES})
target_include_directories(ImGui PUBLIC ${DEPENDS_DIR}/IMGUI)
target_include_directories(ImGui PUBLIC ${glfw_SOURCE_DIR}/include)


# copy dll to build folder
foreach( dll_i ${THIRD_PARTY_DLL})
add_custom_command(TARGET ${MAIN_PROJECT_NAME} PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${dll_i}
		$<TARGET_FILE_DIR:${MAIN_PROJECT_NAME}>)
endforeach( dll_i )





set(CMAKE_FOLDER ${CMAKE_FOLDER_OLD})