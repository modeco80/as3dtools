//
// AS3DTools
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <string>
#include <ctime>

namespace as3dpak {

	/**
 	 * Format a raw amount of bytes to a human-readable unit, if possible.
 	 * \param[in] bytes Size in bytes.
	 */
	std::string FormatUnit(std::uint64_t bytes);

}
