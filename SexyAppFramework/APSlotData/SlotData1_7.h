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
    
    bool is_eligible_for_individual_tile_unlock_items(int level) override
    {
        const int ineligible_levels[] = {5, 15, 35, 52, 53, 55, 57, 58, 59, 65, 68, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 99, 103};
        if (std::ranges::find(ineligible_levels, level) != std::ranges::end(ineligible_levels))
        {
            return false;
        }
        return true;
    }
};