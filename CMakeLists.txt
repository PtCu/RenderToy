cmake_minimum_required(VERSION 3.0.0)
set(PROJECT_NAME "RenderToy")
project (${PROJECT_NAME} VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(glm CONFIG REQUIRED)
#target_link_libraries(main PRIVATE glm::glm)
find_package(spdlog CONFIG REQUIRED)
#target_link_libraries(main PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

#---------------------------------------
macro(SETUP_PROJECT MODE TARGET_NAME STR_TARGET_SOURCES STR_TARGET_LIBS)
	string(REPLACE " " ";" LIST_TARGET_SOURCES ${STR_TARGET_SOURCES})
	string(REPLACE " " ";" LIST_TARGET_LIBS ${STR_TARGET_LIBS})
	
	if(${STR_TARGET_SOURCES} STREQUAL " ")
		message(WARNING "Target [${TARGET_NAME}] has no source, so it won't be generated.")
	else()
		if(${MODE} STREQUAL "EXE")
			add_executable( ${TARGET_NAME} ${LIST_TARGET_SOURCES})
			set(INSTALL_DIR "bin")
		elseif(${MODE} STREQUAL "LIB")
			add_library(${TARGET_NAME} ${LIST_TARGET_SOURCES})
			set(INSTALL_DIR "lib/${FOLDER_NAME}")
		else()
			message(FATAL_ERROR "Mode [${MODE}] is not supported, so target [TARGET_NAME] is not generated!")
			set(MODE_NOTSUPPORT " ")
		endif()
		if(NOT DEFINED MODE_NOTSUPPORT)
			if( NOT ${FOLDER_NAME} STREQUAL " ")
				SET_TARGET_PROPERTIES(${TARGET_NAME} PROPERTIES FOLDER ${FOLDER_NAME})
			endif()
			if(NOT ${STR_TARGET_LIBS} STREQUAL " ")
				target_link_libraries( ${TARGET_NAME} ${LIST_TARGET_LIBS} )
			endif()
			install (TARGETS ${TARGET_NAME} DESTINATION ${INSTALL_DIR})
			message(STATUS "Setup Project ${Mode} ${FOLDER_NAME}/[${TARGET_NAME}]")
		endif()
	endif()
endmacro(SETUP_PROJECT TARGET_NAME STR_TARGET_SOURCES STR_TARGET_LIBS)
#---------------------------------------
macro(ADD_ALL_SUBDIR)
	file(GLOB _children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
	set(_dirlist "")
	foreach(_child ${_children})
		if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${_child})
			list(APPEND _dirlist ${_child})
		endif()
	endforeach()
	#SET(${result} ${dirlist})
	foreach(_subdir ${_dirlist})
		add_subdirectory(${_subdir})
	endforeach()
endmacro(ADD_ALL_SUBDIR)
#---------------------------------------
macro(GET_DIR_NAME DIRNAME)
	string(REGEX MATCH "([^/]*)$" TMP ${CMAKE_CURRENT_SOURCE_DIR})
	set(${DIRNAME} ${TMP})
endmacro(GET_DIR_NAME DIRNAME)
#---------------------------------------

#设置头文件目录
include_directories(
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/include
	${CMAKE_BINARY_DIR}/config
)


configure_file(config/ROOT_PATH.h.in config/ROOT_PATH.h)

add_subdirectory (src)
add_subdirectory (tests)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)