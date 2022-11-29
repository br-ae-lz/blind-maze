add_executable(blind-maze main.cpp grid.cpp input.cpp)

target_sources(blind-maze
	PRIVATE
		main.cpp
		grid.cpp
		input.cpp
		replay.cpp
)

target_include_directories(blind-maze PRIVATE include)

target_link_options(blind-maze PRIVATE -mwindows)

set_property(TARGET blind-maze PROPERTY CXX_STANDARD 20)