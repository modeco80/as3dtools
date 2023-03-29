//
// AS3DTools
//
// (C) 2021-2023 modeco80 <lily.modeco80@protonmail.ch>
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

// Note that the TOC will have to be decrypted
// before using this pattern. This can be done
// inside ImHex, using a Data Processor.
// (This excercise is left to the reader.)

#include <std/io.pat>

#pragma endian little

struct PakHeader {
    float unkFloat;
    u32 unk; //always 0x9999
    u32 tocOff;
    u32 fileCount;
        
    // XOR key used to encrypt the archive TOC
    u8 xorKey[0x400];
};

struct PakToc {
    char name[64];
    u32 startOff;
    u32 fileLength;
    u32 encrypted;
};

struct PakFile : PakHeader {
    PakToc toc[fileCount] @ tocOff;
};

PakFile pak @ 0x0;