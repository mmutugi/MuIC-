cmake_minimum_required(VERSION 3.14)
project(MuICSimulation)

set(CMAKE_CXX_STANDARD 17)

# LINK BOOST
find_package(Boost 1.40 COMPONENTS system filesystem program_options REQUIRED)

message(STATUS "boost_inc: ${boost_inc}")
message(STATUS "boost_libs: ${boost_libs}")

# LINK ROOT
execute_process(
        COMMAND root-config --incdir
        OUTPUT_VARIABLE root_inc
)

execute_process(
        COMMAND root-config --libs
        OUTPUT_VARIABLE root_libs
)

execute_process(
        COMMAND root-config --cflags
        OUTPUT_VARIABLE root_cflags
)

string(STRIP ${root_inc} root_inc)
string(STRIP ${root_libs} root_libs)
string(STRIP ${root_cflags} root_cflags)

message(STATUS "root_inc: ${root_inc}")
message(STATUS "root_libs: ${root_libs}")
message(STATUS "root_cflags: ${root_cflags}")

# LINK GEANT4
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)

if (WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else ()
    find_package(Geant4 REQUIRED)
endif ()

include(${Geant4_USE_FILE})

# Copy Macros to Output Folder
file(GLOB_RECURSE MACROS RELATIVE ${PROJECT_SOURCE_DIR} macros/*.mac)

foreach (_script ${MACROS})
    configure_file(
            ${PROJECT_SOURCE_DIR}/${_script}
            ${PROJECT_BINARY_DIR}/${_script}
            COPYONLY
    )
endforeach ()


# BUILD APPLICATION
file(GLOB_RECURSE APP_SRC ${CMAKE_SOURCE_DIR}/src/muic/*.cpp)
message(STATUS "App Sources: ${APP_SRC}")

add_executable(MuICSimulation ${APP_SRC})
target_include_directories(MuICSimulation PUBLIC ${CMAKE_SOURCE_DIR}/include ${boost_inc} ${root_inc} ${Geant4_INCLUDE_DIR})
target_link_libraries(MuICSimulation PUBLIC ${boost_libs} ${root_libs} ${Geant4_LIBRARIES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -DLINUX -Wall -funsigned-char -lboost_program_options -I${root_cflags}")
