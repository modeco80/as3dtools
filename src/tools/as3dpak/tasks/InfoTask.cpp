//
// AS3DTools
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <tasks/InfoTask.hpp>

#include <as3d/io/PakReader.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>

#include <Utils.hpp>

namespace as3dpak::tasks {

	int InfoTask::Run(Arguments&& args) {
		std::ifstream ifs(args.inputPath.string(), std::ifstream::binary);

		if(!ifs) {
			std::cout << "Error: Could not open file " << args.inputPath << ".\n";
			return 1;
		}

		as3d::io::PakReader reader(ifs);

		reader.ReadData();

		if(reader.Invalid()) {
			std::cout << "Error: Invalid APK file " << args.inputPath << ".\n";
			return 1;
		}

		std::cout << "Archive " << args.inputPath << ":\n";
		std::cout << "    File Count: " << reader.GetHeader().fileCount << " files\n";

		// Print a detailed file list if verbose.
		if(args.verbose) {
			for(auto& [ filename, file ] : reader.GetFiles()) {
				std::cout << "File \"" << filename << "\":\n";
				std::cout << "    Size: " << FormatUnit(file.GetTOCEntry().length) << '\n';
				std::cout << "    XOR Encrypted: " << (file.GetTOCEntry().xorEncrypted == 1 ? "Yes" : "No") << '\n';
			}
		}

		return 0;
	}

}