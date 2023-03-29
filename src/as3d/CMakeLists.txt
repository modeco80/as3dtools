add_library(as3d
		# Implementation details
		io/StreamUtils.cpp

		# Pak IO
		io/PakFile.cpp
		io/PakReader.cpp
		io/PakWriter.cpp
		)

target_include_directories(as3d PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_compile_features(as3d PUBLIC cxx_std_20)
