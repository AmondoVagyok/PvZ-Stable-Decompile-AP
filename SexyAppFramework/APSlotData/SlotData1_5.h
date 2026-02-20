#pragma once

#include "SlotData1_4.h"

class SlotData1_5 : public SlotData1_4
{
public:
    explicit SlotData1_5(nlohmann::json slot_data) : SlotData1_4(std::move(slot_data)) {}
    
    std::string version() override
    {
        return "1.5";
    }
};