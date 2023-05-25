# set the project name
get_filename_component(CURRENT_FOLDER_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
set(PROJECT_NAME ${CURRENT_FOLDER_NAME})

###############################
#                             #
# Sources                     #
#                             #
###############################

# Add source files
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FOLDER})
file(GLOB_RECURSE SOURCE_FILES
	${PROJECT_SOURCE_DIR}/*.c
	${PROJECT_SOURCE_DIR}/*.cc
	${PROJECT_SOURCE_DIR}/*.cpp
	${PROJECT_SOURCE_DIR}/*.cxx
	${PROJECT_SOURCE_DIR}/*.c++)

# Add header files
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_FOLDER})
file(GLOB_RECURSE HEADER_FILES
	${PROJECT_INCLUDE_DIR}/*.h
	${PROJECT_INCLUDE_DIR}/*.hpp
	${PROJECT_INCLUDE_DIR}/*.inl)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES} ${SOURCE_FILES})

add_compile_options(/Zi)
###############################
#                             #
# Library                  	  #
#                             #
###############################

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_FOLDER})
target_include_directories(${PROJECT_NAME} PRIVATE ${DEPENDS_DIR})


#deactivate PDB generation for bullet (too many warnings) in VIsual Studio


foreach(project_i ${THIRD_PARTY_PROJECT})
	include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE}/${project_i}/${INCLUDE_FOLDER})
endforeach( project_i )

foreach(include_i ${THIRD_PARTY_INCLUDE})
	include_directories(${PROJECT_NAME} PRIVATE ${DEPENDS_DIR}/${include_i}/${INCLUDE_FOLDER})
endforeach( include_i )

#link assimp
target_link_libraries(${PROJECT_NAME} PRIVATE ${DEPENDS_DIR}/assimp/lib/assimp-vc143-mt.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${DEPENDS_DIR}/assimp/lib/IrrXML.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${DEPENDS_DIR}/assimp/lib/zlibstatic.lib)


target_include_directories(${PROJECT_NAME} PUBLIC ${BULLET_INCLUDE_DIR})
message(STATUS "BULLET_INCLUDE_DIR: ${BULLET_INCLUDE_DIR}")
target_link_libraries(${PROJECT_NAME} PUBLIC
	debug ${BULLET_COLLISION_LIBRARY_DEBUG}
	debug ${BULLET_DYNAMICS_LIBRARY_DEBUG}
	debug ${BULLET_LINEAR_MATH_DEBUG}
	optimized ${BULLET_DYNAMICS_LIBRARY}
	optimized ${BULLET_LINEAR_MATH}
	optimized ${BULLET_COLLISION_LIBRARY}
	)