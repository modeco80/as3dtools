//
// AS3DTools
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <cstdint>

namespace as3d {
	using u8 = std::uint8_t;
	using s8 = std::int8_t;

	using u16 = std::uint16_t;
	using s16 = std::int16_t;

	using u32 = std::uint32_t;
	using s32 = std::int32_t;

	using u64 = std::uint64_t;
	using s64 = std::int64_t;

#define AS3D_ASSERT_TYPE_SIZE(T, Expected) \
	static_assert(sizeof(T) == Expected, "Error: Type " #T "has wrong size, expected " #Expected ".")

} // namespace as3d
