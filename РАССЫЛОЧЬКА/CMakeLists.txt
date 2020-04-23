cmake_minimum_required(VERSION 3.15)
project(rassylochka_main VERSION 1.0.1)
include(ExternalProject)

set(EXTERNAL_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/external)

ExternalProject_Add(NetworkDownload
   GIT_REPOSITORY  /Users/mikchan/Documents/NetworkGithub/Network #https://github.com/wtlgo/Network.git
   CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION} -DBUILD_SHARED_LIBS=TRUE
)

include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)

find_package(nlohmann_json REQUIRED)
find_package(CURL REQUIRED)

add_executable(rassylochka main.cpp)

target_compile_features(rassylochka PUBLIC cxx_std_17)
add_dependencies(rassylochka NetworkDownload)
target_link_libraries(rassylochka PUBLIC Network nlohmann_json::nlohmann_json ${CURL_LIBRARIES})
