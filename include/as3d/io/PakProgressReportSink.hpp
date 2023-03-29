//
// AS3DTools
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <string>

namespace as3d::io {

	/**
	 * Interface for the writer to output detailed progress information.
	 */
	struct PakProgressReportSink {

		struct PakEvent {
			enum class Type {
				FillInHeader,    	///< Filling in header
				WritingHeader,		///< Writing header

				WritingToc			///< Writing archive TOC
			};

			Type type;
		};

		struct FileEvent {
			enum class Type {
				FileBeginWrite,   ///< File has began write to package
				FileEndWrite,     ///< File writing finished
			};

			Type type;
			std::string filename;
		};

		virtual ~PakProgressReportSink() = default;

		virtual void OnEvent(const PakEvent& event) = 0;
		virtual void OnEvent(const FileEvent& event) = 0;
	};


} // namespace europa::io
