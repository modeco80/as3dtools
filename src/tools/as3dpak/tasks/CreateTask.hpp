//
// AS3DTools
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <CommonDefs.hpp>

#include <as3d/structs/Pak.hpp>


namespace as3dpak::tasks {

		struct CreateTask {
			struct Arguments {
				fs::path inputDirectory;
				fs::path outputFile;

				bool verbose;
			};

			int Run(Arguments&& args);
		};

} // namespace eupak::tasks