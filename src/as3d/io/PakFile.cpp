//
// AS3DTools
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <as3d/io/PakFile.hpp>

namespace as3d::io {

	const PakFile::DataType& PakFile::GetData() const {
		return data;
	}

	void PakFile::SetData(PakFile::DataType&& newData) {
		data = std::move(newData);
	}


} // namespace as3d::io