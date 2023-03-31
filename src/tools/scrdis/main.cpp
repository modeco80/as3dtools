// A WIP thingy for script diassembly
// This currently dumps everything about the script
#include <iostream>
#include <fstream>

#include <as3d/structs/Scr.hpp>

// This is a nono but oh well
#include "../src/as3d/io/StreamUtils.hpp"

#include <vector>
#include <string>

struct Script {
    as3d::structs::ScriptHeader scriptHeader;

    // Imports used by the script
    std::vector<std::string> externFuncs;
    std::vector<std::string> externDefs;

    std::vector<std::string> cacheFiles;

    // constant data
    std::vector<char> stringTable;
    std::vector<as3d::u8> constPool;

    // script code
    std::vector<as3d::structs::ScriptInstruction> instructions;

    void Out() {
        std::cout << "Cache files: \n";
        for(auto& var : cacheFiles)
            std::cout << "    " << var << '\n';

        std::cout << "Extern variables:\n";
        for(auto& var : externDefs)
            std::cout << "    " << var << '\n';

        std::cout << "Extern funcs:\n";
        for(auto& var : externFuncs)
            std::cout << "    " << var << "\n";

        std::cout << "Opcode dump:\n";
        for(auto& inst : instructions)
            std::printf("%22s %02x %08x %08x %08x\n", as3d::detail::EnumToString(inst.opcode).c_str(), inst.addrMode, inst.unk[0], inst.unk[1], inst.unk[2]);

    }
};


// TODO: Refactor into a io:: object. This is already using io detail APIs, 
// so it can be relatively easily done.
Script ReadScript(std::string_view filename) {
    std::ifstream ifs(filename.data(), std::ifstream::binary);
    if(!ifs)
        throw std::runtime_error("no");

    Script s;
    s.scriptHeader = as3d::io::impl::ReadStreamType<as3d::structs::ScriptHeader>(ifs);

    if(!s.scriptHeader.Validate())
        throw std::runtime_error("Invalid script file");

    // Read all of the script chunks.
    while(!ifs.eof()) {
        auto header = as3d::io::impl::ReadStreamType<as3d::structs::ScriptChunkHeader>(ifs);

        // Trash this chunk if it's not got anything in it
        if(header.size == 0)
            continue;

        if(header.Is<"CASH">()) {        // Files that should be cached or loaded when this script file is loaded
            s.cacheFiles.reserve(s.scriptHeader.cashSize);
            for(int i = 0; i < s.scriptHeader.cashSize; ++i) {
                auto something = ifs.get();
                s.cacheFiles.push_back(as3d::io::impl::ReadPString(ifs));
            }
        } else if(header.Is<"DEFS">()) { // Imported variable names
            s.externDefs.reserve(s.scriptHeader.builtinDefsSize);
            for(int i = 0; i < s.scriptHeader.builtinDefsSize; ++i)
                s.externDefs.push_back(as3d::io::impl::ReadPString(ifs));
        } else if (header.Is<"FUNC">()) { // Imported functions
            s.externFuncs.reserve(s.scriptHeader.builtinFuncsSize);
            for(int i = 0; i < s.scriptHeader.builtinFuncsSize; ++i)
                s.externFuncs.push_back(as3d::io::impl::ReadPString(ifs));
        } else if (header.Is<"DATA">()) { // Constant pool
            s.constPool.resize(s.scriptHeader.dataConstSize * 2);
            ifs.read(reinterpret_cast<char*>(&s.constPool[0]), s.scriptHeader.dataConstSize * 2);
        } else if (header.Is<"STRG">()) { // String table
            s.stringTable.resize(s.scriptHeader.stringTableSize);
            ifs.read(&s.stringTable[0], s.scriptHeader.stringTableSize);
        } else if (header.Is<"CODE">()) { // Script instructions
            s.instructions.resize(s.scriptHeader.codeSize);
            ifs.read(reinterpret_cast<char*>(&s.instructions[0]), s.scriptHeader.codeSize * sizeof(as3d::structs::ScriptInstruction));
        }
    }

    return s;
}

int main(int argc, char** argv) {
    if(argc < 2) {
        std::printf("Usage: %s [path to .scr file]\n", argv[0]);
        std::printf("This tool is extremely WIP.\n");
        return 1;
    }
    auto script = ReadScript(argv[1]);
    script.Out();
    return 0;
}