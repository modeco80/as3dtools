//
// AS3DTools
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#pragma once

#include <cstdint>
#include <cstring>
#include <bit>
#include <as3d/util/CommonTypes.hpp>
#include <as3d/util/FourCC.hpp>

namespace as3d::structs {

	struct ScriptChunkHeader {
		u32 fourCC{};
		u32 size{};

		template<util::FixedString MyFCC, std::endian Endian = std::endian::little>
		constexpr bool Is() const {
			return util::FourCC<MyFCC, Endian>() == this->fourCC;
		}
	};

	struct ScriptHeader {
		constexpr static auto MAGIC = util::FourCC<"RCSL">();

		u32 magic;
		u32 unk;
		u32 cashSize; //*72
		u32 builtinDefsSize; // *4
		u32 builtinFuncsSize; // *4
		u32 dataConstSize; // *8
		u32 unk2;
		u32 stringTableSize;
		u32 codeSize;       // *14
		u32 unk3;
		u32 unk4;
		u32 unk5;
		u32 unk6;
		u32 unk7;


		constexpr bool Validate() const {
			return magic == MAGIC;
		}

		constexpr void Init() {
			magic = MAGIC;
		}
	};

	enum class ScriptOpcode : u8 {
		Exit = 0,

		// Artithmetic
		Mul,
		Div,
		Add,
		Sub,
		And,
		Or,

		// Comparision
		Cnz, // compare non-zero
		Cz,  // compare zero
		Ceq, // compare equal
		Cne, // compare non-equal
		Clt, // less-than
		Cgt, // greater-than
		Cle, // less-than or equal to
		Cge, // greater-than or equal to

		
		Ret = 0x18


	};




	struct [[gnu::packed]] ScriptInstruction {
		ScriptOpcode opcode;
		u8 addrMode; // ? bitflags
		u32 unk[3];  // could be immediates
	};


	AS3D_ASSERT_TYPE_SIZE(ScriptChunkHeader, 0x8);
	AS3D_ASSERT_TYPE_SIZE(ScriptHeader, 0x38);
	AS3D_ASSERT_TYPE_SIZE(ScriptInstruction, 0xe);

}

namespace as3d::detail {

	template<>
	struct EnumToStringHelper<as3d::structs::ScriptOpcode> {
		static constexpr std::string _(as3d::structs::ScriptOpcode inst) {
			using enum as3d::structs::ScriptOpcode;
			#define E(e) case e: return #e;
			switch(inst) {
				E(Exit)
				E(Mul)
				E(Div)
				E(Add)
				E(Sub)
				E(And)
				E(Or)
				E(Cnz)
				E(Cz)
				E(Ceq)
				E(Cne)
				E(Clt)
				E(Cgt)
				E(Cle)
				E(Cge)
				E(Ret)
				default: return StringPrintf("<unknown opcode 0x%02x>", static_cast<u8>(inst));
			}
			#undef E
#ifdef __GNUC__
			__builtin_unreachable();
#endif
		}
	};

}