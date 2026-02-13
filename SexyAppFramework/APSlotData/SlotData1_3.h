#pragma once

#include <nlohmann/json.hpp>
#include "../APData.h"
#include "SlotDataInner.h"
#include "../../Lawn/Plant.h"

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
    
    bool easy_upgrade_plants() override
    {
        return slot_data["easy_upgrade_plants"].get<int>() > 0;
    }
    
    std::optional<PVZRAPData::SlotData::SeedStats> seed_stats(SeedType seed) override
    {
        // Apply easy upgrade tax
        if (easy_upgrade_plants())
        {
            int easy_upgrade_tax;
            switch (seed)
            {
            case SeedType::SEED_GATLINGPEA:
                easy_upgrade_tax = 200;
                break;
            case SeedType::SEED_TWINSUNFLOWER:
                easy_upgrade_tax = 50;
                break;
            case SeedType::SEED_GLOOMSHROOM:
                easy_upgrade_tax = 75;
                break;
            case SeedType::SEED_CATTAIL:
                easy_upgrade_tax = 25;
                break;
            case SeedType::SEED_WINTERMELON:
                easy_upgrade_tax = 300;
                break;
            case SeedType::SEED_GOLD_MAGNET:
                easy_upgrade_tax = 100;
                break;
            case SeedType::SEED_SPIKEROCK:
                easy_upgrade_tax = 100;
                break;
            case SeedType::SEED_COBCANNON:
                easy_upgrade_tax = 200;
                break;
            default:
                // No easy upgrade tax applies
                return {};
            }

            const auto plant_def = GetPlantDefinition(seed);
            
            PVZRAPData::SlotData::SeedStats stats;
            stats.sun_price = plant_def.mSeedCost + easy_upgrade_tax;
            return stats;
        }
        return {};
    }
    
    std::optional<PVZRAPData::SlotData::ProjectileStats> projectile_stats(const ProjectileType projectile) override
    {
        // Not supported in 1.3
        return {};
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
