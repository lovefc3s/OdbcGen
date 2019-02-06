cmake_minimum_required(VERSION 2.8)
SET (projectid OdbcGen)
Project(${projectid} C CXX)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "-std=c++17 -Dname=__SqlServer__")
add_executable(${projectid}
	stdafx.h
	odbcsql.h
	ootabe.h
	odbcsql.cpp
	main.cpp )
set(CMAKE_MODULE_PATH /home/masamitsu/Documents/src/cotire/CMake)
include(cotire)
find_package(PkgConfig REQUIRED)
pkg_check_modules(ODBC odbc REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0 REQUIRED)
include_directories(
	${ODBC_INCLUDE_DIRS} 
	${GTKMM_INCLUDE_DIRS} 
)
link_directories(
	${ODBC_LIBRARY_DIRS}
    ${GTKMM_LIBRARY_DIRS}  )
target_link_libraries(${projectid}
	odbcinst
	odbccr
	${ODBC_LIBRARIES}
	${GTKMM_LIBRARIES} 
)	
cotire(${projectid})
