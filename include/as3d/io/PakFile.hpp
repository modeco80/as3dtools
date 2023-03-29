//
// AS3DTools
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <cstdint>
#include <as3d/structs/Pak.hpp>
#include <vector>

namespace as3d::io {

	struct PakReader;
	struct PakWriter;

	struct PakFile {
		using DataType = std::vector<std::uint8_t>;

		void SetData(DataType&& data);

		const DataType& GetData() const;

		// fill it with the right data
		void FillTOCEntry();
		structs::PakTocEntry& GetTOCEntry() { return tocEntry; }


	   private:
		friend PakReader;
		friend PakWriter;

		std::vector<std::uint8_t> data;
		structs::PakTocEntry tocEntry;
	};

} // namespace europa::io
