//
// AS3DTools
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <as3d/io/PakFile.hpp>
#include <as3d/structs/Pak.hpp>
#include <iosfwd>
#include <string>
#include <unordered_map>

namespace as3d::io {

	struct PakReader {
		using MapType = std::unordered_map<std::string, PakFile>;

		explicit PakReader(std::istream& is);

		void ReadData();

		void ReadFiles();

		/**
		 * Read in a specific file.
		 */
		void ReadFile(const std::string& file);

		bool Invalid() const {
			return invalid;
		}

		MapType& GetFiles();
		const MapType& GetFiles() const;

		const structs::PakHeader& GetHeader() const {
			return header;
		}


	   private:
		std::istream& stream;
		bool invalid { false };
		structs::PakHeader header;
		MapType files;
	};

} // namespace europa::io
