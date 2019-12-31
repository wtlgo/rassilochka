cmake_minimum_required(VERSION 3.0)
project(rassylochka_main)
include(ExternalProject)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

ExternalProject_Add(NetworkDownload
   GIT_REPOSITORY https://github.com/wtlgo/Network.git
   CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
)

include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

find_package(nlohmann_json REQUIRED)

add_executable(rassylochka main.cpp)
target_compile_features(rassylochka PRIVATE cxx_std_17)
add_dependencies(rassylochka NetworkDownload)
target_link_libraries(rassylochka nlohmann_json::nlohmann_json Network)
