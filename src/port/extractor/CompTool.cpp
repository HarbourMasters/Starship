#include "CompTool.h"
#include "utils/Decompressor.h"
#include "BinaryReader.h"
#include "BinaryWriter.h"
#include <fstream>

uint32_t CompTool::FindFileTable(std::vector<uint8_t>& rom) {
    uint8_t query_one[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x50, 0x00, 0x00, 0x00, 0x00 };
    uint8_t query_two[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x60, 0x00, 0x00, 0x00, 0x00 };

    for(size_t i = 0; i < rom.size() - sizeof(query_one); i++) {
        if(memcmp(rom.data() + i, query_one, sizeof(query_one)) == 0){
            return i;
        }

        if(memcmp(rom.data() + i, query_two, sizeof(query_two)) == 0){
            return i;
        }
    }

    throw std::runtime_error("Failed to find file table");
}

std::vector<uint8_t> CompTool::Decompress(std::vector<uint8_t> rom){
    Ship::BinaryReader basefile((char*) rom.data(), rom.size());
    basefile.SetEndianness(Ship::Endianness::Big);

    Ship::BinaryWriter decompfile;
    decompfile.SetEndianness(Ship::Endianness::Big);
    decompfile.Write((uint8_t)0x80);

    uint32_t table = CompTool::FindFileTable(rom);
    uint32_t count = 0;
    while (true){
        auto entry = table + 0x10 * count;
        basefile.Seek(entry, Ship::SeekOffsetType::Start);

        auto v_begin = basefile.ReadInt32();
        auto p_begin = basefile.ReadInt32();
        auto p_end = basefile.ReadInt32();
        auto comp_flag = basefile.ReadInt32();

        auto p_size = p_end - p_begin;
        auto v_size = (int32_t) 0;
        DataChunk* decoded = nullptr;

        if(v_begin == 0 && p_end == 0){
            break;
        }

        basefile.Seek(p_begin, Ship::SeekOffsetType::Start);

        auto bytes = new uint8_t[p_size];
        basefile.Read((char*) bytes, p_size);

        switch ((CompType) comp_flag) {
            case CompType::UNCOMPRESSED:
                v_size = p_size;
                break;
            case CompType::COMPRESSED:
                decoded = Decompressor::Decode(std::vector(bytes, bytes + p_size), 0, CompressionType::MIO0, true);
                bytes = decoded->data;
                v_size = decoded->size;
                break;
            default:
                throw std::runtime_error("Invalid compression flag. There may be a problem with your ROM.");
        }

        decompfile.Seek(v_begin, Ship::SeekOffsetType::Start);
        decompfile.Write((char*) bytes, v_size);
        auto v_end = v_begin + v_size;

        decompfile.Seek(entry + 4, Ship::SeekOffsetType::Start);
        decompfile.Write(v_begin);
        decompfile.Write(v_end);
        decompfile.Write((uint32_t) CompType::UNCOMPRESSED);
        count++;
    }

    decompfile.Seek(0x10, Ship::SeekOffsetType::Start);
    decompfile.Write(0xA7D5F194); // CRC1
    decompfile.Write(0xFE3DF761); // CRC2

    auto result = decompfile.ToVector();
    return { (uint8_t*) result.data(), (uint8_t*) result.data() + result.size() };
}