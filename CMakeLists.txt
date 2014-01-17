# Copyright © 2013 Lénaïc Bagnères, hnc@singularity.fr
# Copyright © 2014 Inria, Written by Lénaïc Bagnères, lenaic.bagneres@inria.fr

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


cmake_minimum_required(VERSION 2.6)


# User's settings - C++ Flags
	
# 	set(release "TRUE")
	set(release "FALSE")

	# Release
	if (release)
		set(CMAKE_CXX_FLAGS "-O3 -DNDEBUG -march=native -fomit-frame-pointer -ffast-math")
	# Debug # valgrind --show-reachable=yes --leak-check=full -v exe
	else()
		set(CMAKE_CXX_FLAGS "-O0 -g3")
	endif()

# User's settings - General C++ Flags
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c89 -pedantic -fopenmp")

	
# PeriScop
	message(STATUS "---")
	find_package(osl REQUIRED)
	find_package(clan REQUIRED)
	find_package(candl REQUIRED)
	find_package(isl REQUIRED)
	find_package(cloog-isl REQUIRED)
	find_package(clay REQUIRED)
	find_package(piplibMP REQUIRED)


# Include directories (to use #include <> instead of #include "")

	# main
	message(STATUS "---")
	set(main_INCLUDE "./include")
	message(STATUS "Include main = ${main_INCLUDE}")
	include_directories("${main_INCLUDE}")


# Build doxygen

	message(STATUS "---")
	find_package(Doxygen)
	if(DOXYGEN_FOUND)
		message(STATUS "Doxygen found =)")
		add_custom_target(
			doc
			${DOXYGEN_EXECUTABLE}
			WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${main_INCLUDE}"
			COMMENT "Generating API documentation with Doxygen" VERBATIM
		)
	else()
		message(STATUS "Doxygen not found :(")
	endif()


# Compiler log

	message(STATUS "---")
	message(STATUS "C++ compiler = ${CMAKE_CXX_COMPILER}")
	if (release)
		message(STATUS "Mode Release")
	else()
		message(STATUS "Mode Debug")
	endif()
	message(STATUS "C++ flags    = ${CMAKE_CXX_FLAGS}")


# Executables & tests

	enable_testing()

	message(STATUS "---")

	# Executable

	file(
		GLOB_RECURSE
		sources
		source/*.c
	)
	
	message(STATUS "Add execute main")
	add_executable(main ${sources})
	target_link_libraries(main ${CLAY_LIBRARY} ${CLOOG_ISL_LIBRARY} ${ISL_LIBRARY} ${CANDL_LIBRARY} ${CLAN_LIBRARY} ${PIPLIBMP_LIBRARY} ${OSL_LIBRARY})
	
	# Test

	file(
		GLOB_RECURSE
		source_code_with_scop
		source_code_with_scop/*.c
	)
	
	foreach(source ${source_code_with_scop})
	
		string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/source_code_with_scop/" "" source_name ${source})
		
		message(STATUS "- ${source_name}")
		add_test("main__${source_name}" main "${source}")
		
	endforeach()

# Install

	install(DIRECTORY include/ DESTINATION include FILES_MATCHING PATTERN "*.h")
	# See https://github.com/periscop/openscop/blob/master/CMakeLists.txt for executable and library


# Little help

	message(STATUS "---")
	message(STATUS "You can execute:")
	message(STATUS "    make         # To compile tests")
	message(STATUS "    make test    # To execute tests")
	message(STATUS "    make install # To install library, include and CMake module")
	message(STATUS "                 # If you need root access:")
	message(STATUS "                 #     sudo make install")
	message(STATUS "                 #     su -c \"make install\"")
	message(STATUS "    make doc     # To generate the Doxygen")

	message(STATUS "---")
