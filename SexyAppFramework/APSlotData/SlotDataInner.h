#pragma once
#include <set>

class PVZRAPData::SlotData::SlotDataInner
{
public:
    virtual ~SlotDataInner() = default;
    
    virtual bool is_valid() = 0;
    virtual std::string version() = 0;
    
    virtual LevelRandomisation minigame_levels() = 0;
    virtual LevelRandomisation puzzle_levels() = 0;
    virtual LevelRandomisation survival_levels() = 0;
    
    virtual std::map<int, int> minigame_unlocks() = 0;
    virtual std::map<int, int> survival_unlocks() = 0;
    virtual std::map<int, int> izombie_unlocks() = 0;
    virtual std::map<int, int> vasebreaker_unlocks() = 0;
    
    virtual bool easy_upgrade_plants() = 0;
    virtual bool disable_storm_flashes() = 0;
    virtual bool imitater_open() = 0;
    
    virtual int sun_per_upgrade() = 0;
    
    virtual std::optional<SeedStats> seed_stats(SeedType seed) = 0;
    virtual std::optional<ProjectileStats> projectile_stats(ProjectileType projectile) = 0;
};
