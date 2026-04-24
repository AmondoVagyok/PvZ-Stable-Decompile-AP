#pragma once

#include "SlotData1_6.h"

class SlotData1_7 : public SlotData1_6
{
public:
    explicit SlotData1_7(nlohmann::json slot_data) : SlotData1_6(std::move(slot_data)) {}
    
    std::string version() override
    {
        return "1.7";
    }
    
    bool ringlink_enabled() override
    {
        return slot_data["ringlink_enabled"];
    }
    
    bool progressive_sun_capacity_items() override
    {
        return slot_data["progressive_sun_capacity_items"].get<int>();
    }
    
    bool individual_tile_unlock_items() override
    {
        return slot_data["individual_tile_unlock_items"].get<int>();
    }
};