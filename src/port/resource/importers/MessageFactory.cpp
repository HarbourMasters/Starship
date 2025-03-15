#include "MessageFactory.h"
#include "../type/Message.h"
#include "spdlog/spdlog.h"
#include <vector>

namespace SF64 {

std::vector<std::string> gASCIIFullTable = {
    "\0", "\n", "{NP:2}", "{NP:3}", "{NP:4}", "{NP:5}", "{NP:6}", "{NP:7}",
    "{PRI:0}", "{PRI:1}", "{PRI:2}", "{PRI:3}", " ", "{HSP}", "{QSP}", "{NXT}",
    "{C:<}", "{C:^}", "{C:>}", "{C:v}", "{^}", "{<}", "{v}", "{>}",
    "A", "B", "C", "D", "E", "F", "G", "H",
    "I", "J", "K", "L", "M", "N", "O", "P",
    "Q", "R", "S", "T", "U", "V", "W", "X",
    "Y", "Z", "a", "b", "c", "d", "e", "f",
    "g", "h", "i", "j", "k", "l", "m", "n",
    "o", "p", "q", "r", "s", "t", "u", "v",
    "w", "x", "y", "z", "!", "?", "-", ",",
    ".", "0", "1", "2", "3", "4", "5", "6",
    "7", "8", "9", "'", "(", ")", ":", "|",
};

std::vector<std::pair<uint16_t*, int32_t>> gCustomMessageTable;

std::shared_ptr<Ship::IResource> ResourceFactoryBinaryMessageV0::ReadResource(std::shared_ptr<Ship::File> file) {
    if (!FileHasValidFormatAndReader(file)) {
        return nullptr;
    }

    auto msg = std::make_shared<Message>(file->InitData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    auto size = reader->ReadUInt32();

    for (uint32_t i = 0; i < size; i++) {
        msg->mMessage.push_back(reader->ReadUInt16());
    }

    return msg;
}

std::shared_ptr<Ship::IResource> ResourceFactoryXMLMessageV0::ReadResource(std::shared_ptr<Ship::File> file) {
    if (!FileHasValidFormatAndReader(file)) {
        return nullptr;
    }
    auto msg = std::make_shared<Message>(file->InitData);
    auto parent = std::get<std::shared_ptr<tinyxml2::XMLDocument>>(file->Reader)->FirstChildElement("Message");
    auto id = parent->IntAttribute("Id", -1);

    tinyxml2::XMLElement* element = parent->FirstChildElement("Line");

    while (element != nullptr) {
        const char* raw = element->GetText();
        if (raw == nullptr) {
            element = element->NextSiblingElement("Line");
            msg->mMessage.push_back(1);
            continue;
        }
        auto text = std::string(raw);
        std::string key;
        for (size_t i = 0; i < text.size(); i++) {
            auto c = text[i];
            if (c == '{') {
                auto end = text.find('}', i);
                if (end == std::string::npos) {
                    continue;
                }
                key = text.substr(i, end - i + 1);
                i = end;
            } else {
                key = text.substr(i, 1);
            }

            auto it = std::find(gASCIIFullTable.begin(), gASCIIFullTable.end(), key);
            if (it != gASCIIFullTable.end()) {
                msg->mMessage.push_back(it - gASCIIFullTable.begin());
            } else {
                SPDLOG_ERROR("Unknown key: {}", key);
            }
        }
        msg->mMessage.push_back(1);
        element = element->NextSiblingElement("Line");
    } // end

    msg->mMessage.push_back(0);
    gCustomMessageTable.emplace_back(msg->mMessage.data(), id);

    return msg;
}
} // namespace LUS

extern "C" int16_t Message_SearchCustomID(uint16_t* msg) {
    for (auto& pair : SF64::gCustomMessageTable) {
        if(pair.first == msg) {
            return (int16_t) pair.second;
        }
    }
    
    return -1;
}