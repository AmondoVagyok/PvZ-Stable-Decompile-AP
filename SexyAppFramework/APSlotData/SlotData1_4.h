#pragma once

#include "SlotData1_3.h"

class SlotData1_4 : public SlotData1_3
{
public:
    explicit SlotData1_4(nlohmann::json slot_data) : SlotData1_3(std::move(slot_data)) {}
    
    std::string version() override
    {
        return "1.4";
    }

    std::optional<PVZRAPData::SlotData::SeedStats> seed_stats(const SeedType seed) override
    {
        PVZRAPData::SlotData::SeedStats seed_stats;

        if (const auto sun_price = slot_data["sun_prices"][std::to_string(seed)]; !sun_price.is_discarded() && !sun_price.is_null())
        {
            seed_stats.sun_price = sun_price.get<int>();
        }

        if (const auto recharge_time = slot_data["recharge_times"][std::to_string(seed)]; !recharge_time.is_discarded() && !recharge_time.is_null())
        {
            seed_stats.recharge_time = recharge_time.get<int>();
        }

        if (const auto firing_rate = slot_data["firing_rates"][std::to_string(seed)]; !firing_rate.is_discarded() && !firing_rate.is_null())
        {
            seed_stats.firing_rate = firing_rate.get<int>();
        }

        if (const auto health = slot_data["plant_healths"][std::to_string(seed)]; !health.is_discarded() && !health.is_null())
        {
            seed_stats.health = health.get<int>();
        }
        
        return seed_stats;
    }
    
    std::optional<PVZRAPData::SlotData::ProjectileStats> projectile_stats(const ProjectileType projectile) override
    {
        std::string projectile_id;
        auto factor = 1;
        switch (projectile)
        {
        case ProjectileType::PROJECTILE_FIREBALL:
            factor = 2;
            // fallthrough
        case ProjectileType::PROJECTILE_PEA:
            projectile_id = "0";
            break;
        case ProjectileType::PROJECTILE_SNOWPEA:
            projectile_id = "1";
            break;
        case ProjectileType::PROJECTILE_CABBAGE:
            projectile_id = "2";
            break;
        case ProjectileType::PROJECTILE_MELON:
            projectile_id = "3";
            break;
        case ProjectileType::PROJECTILE_PUFF:
            projectile_id = "4";
            break;
        case ProjectileType::PROJECTILE_WINTERMELON:
            projectile_id = "5";
            break;
        case ProjectileType::PROJECTILE_STAR:
            projectile_id = "6";
            break;
        case ProjectileType::PROJECTILE_SPIKE:
            projectile_id = "7";
            break;
        case ProjectileType::PROJECTILE_KERNEL:
            projectile_id = "8";
            break;
        case ProjectileType::PROJECTILE_BUTTER:
            projectile_id = "9";
            break;
        default:
            return {};
        }
        
        PVZRAPData::SlotData::ProjectileStats projectile_stats;
        if (const auto projectile_damage = slot_data["projectile_damages"][projectile_id]; !projectile_damage.is_discarded() && !projectile_damage.is_null())
        {
            projectile_stats.damage = projectile_damage.get<int>() * factor;
        }
        
        return projectile_stats;
    }
};
