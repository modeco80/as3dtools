//
// AS3DTools
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <CommonDefs.hpp>

namespace as3dpak::tasks {

		struct InfoTask {

			struct Arguments {
				fs::path inputPath;
				bool verbose;
			};

			int Run(Arguments&& args);
		};

}
