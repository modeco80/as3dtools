add_executable(as3dpak
		main.cpp

		Utils.cpp

		# Tasks
		tasks/InfoTask.cpp
		tasks/CreateTask.cpp
		tasks/ExtractTask.cpp
)

target_link_libraries(as3dpak PUBLIC
		as3d
		argparse::argparse
		indicators::indicators
		)

configure_file(As3dpakConfig.hpp.in
		${CMAKE_CURRENT_BINARY_DIR}/As3dpakConfig.hpp
)

target_include_directories(as3dpak PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(as3dpak PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})