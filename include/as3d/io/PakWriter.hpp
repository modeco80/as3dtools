//
// AS3DTools
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <as3d/io/PakFile.hpp>
#include <as3d/io/PakProgressReportSink.hpp>
#include <iosfwd>
#include <string>
#include <utility>

namespace as3d::io {

	/**
	 * Writer for package files.
	 */
	struct PakWriter {
		using FlattenedType = std::pair<std::string, PakFile>;

		void Init();

		/**
		 * Write the resulting archive to the given output stream.
		 */
		void Write(std::ostream& os, std::vector<FlattenedType>&& vec, PakProgressReportSink& sink);

	};

} // namespace as3d::io
