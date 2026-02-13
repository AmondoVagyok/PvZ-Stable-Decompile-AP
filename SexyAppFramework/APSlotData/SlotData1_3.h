#pragma once

#include <nlohmann/json.hpp>
#include "../APData.h"
#include "SlotDataInner.h"

class SlotData1_3 : public PVZRAPData::SlotData::SlotDataInner
{
public:
    explicit SlotData1_3(nlohmann::json slot_data) : slot_data(std::move(slot_data)) {}
    nlohmann::json slot_data;
    
    std::string version() override
    {
        return "1.3";
    }

    PVZRAPData::SlotData::LevelRandomisation minigame_levels() override
    {
        return parse_level_randomisation(slot_data["minigame_levels"].get<int>());
    }
    
    PVZRAPData::SlotData::LevelRandomisation puzzle_levels() override
    {
        return parse_level_randomisation(slot_data["puzzle_levels"].get<int>());
    }
    
    PVZRAPData::SlotData::LevelRandomisation survival_levels() override
    {
        return parse_level_randomisation(slot_data["survival_levels"].get<int>());
    }

    std::map<int, int> minigame_unlocks() override
    {
        return parse_unlocks(slot_data["minigame_unlocks"]);
    }
    
    std::map<int, int> survival_unlocks() override
    {
        return parse_unlocks(slot_data["survival_unlocks"]);
    }
    
    std::map<int, int> izombie_unlocks() override
    {
        return parse_unlocks(slot_data["izombie_unlocks"]);
    }
    
    std::map<int, int> vasebreaker_unlocks() override
    {
       return parse_unlocks(slot_data["vasebreaker_unlocks"]);
    }

private:
    static PVZRAPData::SlotData::LevelRandomisation parse_level_randomisation(int level_randomisation)
    {
        switch (level_randomisation)
        {
        case 0:
            return PVZRAPData::SlotData::LevelRandomisation::Off;
        case 1:
            return PVZRAPData::SlotData::LevelRandomisation::Vanilla;
        case 2:
            return PVZRAPData::SlotData::LevelRandomisation::RandomisedOrder;
        case 3:
            return PVZRAPData::SlotData::LevelRandomisation::Open;
        case 4:
            return PVZRAPData::SlotData::LevelRandomisation::LevelItems;
        default:
            // ???
            return PVZRAPData::SlotData::LevelRandomisation::Off;
        }
    }
    
    static std::map<int, int> parse_unlocks(nlohmann::json unlocks)
    {
        std::map<int, int> result;
        for (auto unlock = unlocks.begin(); unlock != unlocks.end(); ++unlock)
        {
            result[std::stoi(unlock.key())] = unlock.value().get<int>();
        }
        
        return result;
    }
};
