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

namespace as3d::structs {

	// TODO: Move this
	template<u32 keyLength = 0x400>
	constexpr void XorBuffer(u8* buffer, std::size_t length, u8* key) {
		// If the key addend behaviour is required this should be a working algo impl:
		//
		// i, j = 0
		// while(j < bufferSize) {
		// 	 i = j + addend
		//	 j++
		//	 *buffer++ ^= key[i % keySize]
		// }
		//
		// alternatively, we can just not encrypt files at all (but we can't not encrypt the TOC,
		// I'm pretty sure. But that's easy, and doesn't even use an addend)

		auto i = 0;
		auto j = 0; // key counter
	
		while(i < length) {
			buffer[i] ^= key[j++ % keyLength];
			i++;
		}
	}

	struct [[gnu::packed]] PakHeader {
		float unknownFloat; // always 1.0
		u32 unknownInt;	// Always 0x99990000
		u32 tocOffset;
		u32 fileCount;

		// This key is used to encrypt the TOC.
		u8 xorKey[0x400];


		constexpr bool Validate() const {
			return unknownInt == 0x9999;
		}

		void Init() {
			unknownFloat = 1.f;
			unknownInt = 0x9999;

			// Hey. If I have no choice other than to use a XOR key, who says I can't have some fun?
			constexpr auto XorKey = "What the fuck did you just fucking say about me, you little bitch? I'll have you know I graduated top of my class in the Navy Seals, "
									"and I've been involved in numerous secret raids on Al-Quaeda, and I have over 300 confirmed kills. I am trained in gorilla warfare and"
			 						"I'm the top sniper in the entire US armed forces. You are nothing to me but just another target. I will wipe you the fuck out with precision "
			 						"the likes of which has never been seen before on this Earth, mark my fucking words. You think you can get away with saying that shit to me over"
			 						"the Internet? Think again, fucker. As we speak I am contacting my secret network of spies across the USA and your IP is being traced right now "
			 						"so you better prepare for the storm, maggot. The storm that wipes out the pathetic little thing you call your life. You're fucking dead, kid. "
			 						"I can be anywhere, anytime, and I can kill you in over seven hundred ways, and that's just with my bare hands. Not only am I extensively trained "
									"in unarmed combat, but I have access to t";

			static_assert(sizeof(XorKey) != 0x400, "oops");
			memcpy(&xorKey[0], &XorKey[0], sizeof(xorKey));
		}

		void XorWithKey(u8* buffer, std::size_t bufferLength) {
			XorBuffer(buffer, bufferLength, &xorKey[0]);
		}
	};

	struct [[gnu::packed]] PakTocEntry {
		char name[64];
		u32 offset;
		u32 length;
		u32 xorEncrypted;
	};

	AS3D_ASSERT_TYPE_SIZE(PakHeader, 0x410);
	AS3D_ASSERT_TYPE_SIZE(PakTocEntry, 0x4c);

} // namespace as3d::structs

