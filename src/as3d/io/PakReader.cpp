//
// AS3DTools
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include <cstring>
#include <as3d/io/PakReader.hpp>
#include <as3d/structs/Pak.hpp>

#include "StreamUtils.hpp"

namespace as3d::io {

	template<u64 N>
	constexpr auto strlen_or_buffer_len(char(&buffer)[N]) {
		const auto len = strlen(buffer);
		return len < N ? len : N;
	}

	template<u64 N>
	auto buffer_string(char(&buf)[N]) {
		return std::string(buf, strlen_or_buffer_len(buf));
	}


	PakReader::PakReader(std::istream& is)
		: stream(is) {
	}

	void PakReader::ReadData() {
		header = impl::ReadStreamType<structs::PakHeader>(stream);

		if(!header.Validate()) {
			invalid = true;
			return;
		}

		auto toc = std::vector<structs::PakTocEntry>(header.fileCount);

		// read and decrypt the TOC
		stream.seekg(header.tocOffset, std::istream::beg);
		stream.read(std::bit_cast<char*>(toc.data()), header.fileCount * sizeof(structs::PakTocEntry));
		header.XorWithKey(std::bit_cast<u8*>(toc.data()), header.fileCount * sizeof(structs::PakTocEntry));

		for(auto i = 0; i < header.fileCount; ++i) {
			files[buffer_string(toc[i].name)].GetTOCEntry() = toc[i];
		}
	}

	void PakReader::ReadFiles() {
		for(auto& [filename, file] : files)
			ReadFile(filename);
	}

	void PakReader::ReadFile(const std::string& file) {
		auto& fileObject = files[file];

		if(!fileObject.data.empty())
			return;

		auto& toc = fileObject.GetTOCEntry();
		fileObject.data.resize(toc.length);

		// do the thing!
		stream.seekg(toc.offset, std::istream::beg);
		stream.read(std::bit_cast<char*>(&fileObject.data[0]), toc.length);

		// "decrypt" encrypted files after reading
		// this is more like poor obfuscation if anything
		if(toc.xorEncrypted) 
			header.XorWithKey(std::bit_cast<u8*>(&fileObject.data[0]), toc.length);
	}

	PakReader::MapType& PakReader::GetFiles() {
		return files;
	}

	const PakReader::MapType& PakReader::GetFiles() const {
		return files;
	}

} // namespace europa::io