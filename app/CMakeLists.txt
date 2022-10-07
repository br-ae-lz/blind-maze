add_executable(blind-maze main.cpp grid.cpp input.cpp)

target_sources(blind-maze
	PRIVATE
		main.cpp
		grid.cpp
		input.cpp
		replay.cpp
)