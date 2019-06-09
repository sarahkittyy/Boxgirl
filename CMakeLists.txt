cmake_minimum_required(VERSION 3.13)
project(Boxjump)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory("lib/Box2D-cmake")
add_subdirectory("lib/ECSX")

find_package(SFML 2.5 REQUIRED COMPONENTS graphics window audio network system)

file(GLOB_RECURSE sources "src/*.cpp")

add_executable(boxjump ${sources})
target_compile_options(boxjump PUBLIC -Wall)
target_link_libraries(boxjump sfml-graphics sfml-window sfml-audio sfml-network sfml-system tobanteGaming::Box2D ecsx stdc++fs)
target_include_directories(boxjump PUBLIC
				"include"
				"lib/nlohmann"
				"lib/Box2D"
				"lib/ECSX/include"
)
