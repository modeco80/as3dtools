add_executable(scrdis
		main.cpp
)

target_link_libraries(scrdis PUBLIC
		as3d
		argparse::argparse
		)

target_include_directories(scrdis PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})