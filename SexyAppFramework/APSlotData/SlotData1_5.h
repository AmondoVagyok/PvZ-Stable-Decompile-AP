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
    
    int sun_per_upgrade() override
    {
        return slot_data["sun_per_upgrade"].get<int>();
    }
    
    std::optional<std::map<SeedType, int>> conveyor_seeds_for_level(int level) override
    {
        auto conveyor_map = slot_data["conveyor_map"];
        auto available_plants_for_level = conveyor_map[std::to_string(level)];
        if (available_plants_for_level.is_null())
        {
            return {};
        }
        
        std::map<SeedType, int> result;
        for (const auto& [plant_json, weight_json] : available_plants_for_level.items())
        {
            auto seed = static_cast<SeedType>(std::stoi(plant_json));
            result.insert_or_assign(seed, weight_json.get<int>());
        }
        return result;
    }
};