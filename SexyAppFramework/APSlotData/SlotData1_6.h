#pragma once

#include "SlotData1_5.h"

class SlotData1_6 : public SlotData1_5
{
public:
    explicit SlotData1_6(nlohmann::json slot_data) : SlotData1_5(std::move(slot_data)) {}
    
    std::string version() override
    {
        return "1.6";
    }
    
    std::optional<std::map<SeedType, int>> conveyor_seeds_for_level(int level) override
    {
        auto conveyor_map = slot_data["conveyor_map"];
        auto level_data = conveyor_map[std::to_string(level)];
        if (level_data.is_null())
        {
            return {};
        }
        
        auto available_plants_for_level = level_data["weights"];

        std::map<SeedType, int> result;
        for (const auto& [plant_json, weight_json] : available_plants_for_level.items())
        {
            auto seed = static_cast<SeedType>(std::stoi(plant_json));
            result.insert_or_assign(seed, weight_json.get<int>());
        }
        return result;
    }
    
    std::optional<std::vector<SeedType>> conveyor_order_for_level(int level) override
    {
        auto conveyor_map = slot_data["conveyor_map"];
        auto level_data = conveyor_map[std::to_string(level)];
        if (level_data.is_null())
        {
            return {};
        }
        
        auto available_plants_for_level = conveyor_map["default"];
        
        std::vector<SeedType> result;
        for (const auto& plant_id : available_plants_for_level)
        {
            auto seed = static_cast<SeedType>(plant_id.get<int>());
            result.push_back(seed);
        }
        return result;
    }
};