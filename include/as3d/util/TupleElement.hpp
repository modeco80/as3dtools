//
// AS3DTools
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <cstdint>
#include <cstddef>

#include <tuple>

namespace as3d::util {

	namespace detail {

		template<std::size_t N>
		struct TupleElementImpl {
			template<typename T>
			constexpr decltype(auto) operator()(T&& t) const {
				using std::get;
				return get<N>(std::forward<T>(t));
			}
		};

		template<std::size_t N>
		inline constexpr TupleElementImpl<N> TupleElement;
	}

	using detail::TupleElement;
}
