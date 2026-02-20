#include "APData.h"

#include <nlohmann/json.hpp>

#include "APSlotData/SlotData1_3.h"
#include "APSlotData/SlotData1_4.h"
#include "APSlotData/SlotData1_5.h"


class SlotDataInvalid : public PVZRAPData::SlotData::SlotDataInner
{
public:
    explicit SlotDataInvalid(std::string version) : _version(version) {}
    std::string _version;
    
    bool is_valid() override
    {
        return false;
    }
    
    std::string version() override
    {
        return _version;
    }

    PVZRAPData::SlotData::LevelRandomisation minigame_levels() override
    {
        return {};
    }
    
    PVZRAPData::SlotData::LevelRandomisation puzzle_levels() override
    {
        return {};
    }
    
    PVZRAPData::SlotData::LevelRandomisation survival_levels() override
    {
        return {};
    }

    std::map<int, int> minigame_unlocks() override
    {
        return {};
    }
    
    std::map<int, int> survival_unlocks() override
    {
        return {};
    }
    
    std::map<int, int> izombie_unlocks() override
    {
        return {};
    }
    
    std::map<int, int> vasebreaker_unlocks() override
    {
        return {};
    }
    
    std::optional<std::set<ZombieType>> zombies_on_level(int level) override
    {
        return {};
    }
    
    std::optional<std::map<SeedType, int>> conveyor_seeds_for_level(int level) override
    {
        return {};
    }
    
    bool easy_upgrade_plants() override
    {
        return {};
    }
    
    bool disable_storm_flashes() override
    {
        return {};
    }
    
    bool imitater_open() override
    {
        return {};
    }
    
    std::optional<PVZRAPData::SlotData::SeedStats> seed_stats(SeedType seed) override
    {
        return {};
    }
    
    std::optional<PVZRAPData::SlotData::ProjectileStats> projectile_stats(const ProjectileType projectile) override
    {
        return {};
    }
    
    int sun_per_upgrade() override
    {
        return {};
    }
};


PVZRAPData::SlotData PVZRAPData::SlotData::get_slot_data(const nlohmann::json& slot_data)
{
    auto gen_version = slot_data["gen_version"];
    std::string gen_version_string;
    if (gen_version.is_number_float())
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << gen_version;
        gen_version_string = ss.str();
    }
    else
    {
        gen_version_string = gen_version.get<std::string>();
    }

    if (gen_version_string == "1.3")
    {
        return SlotData(std::make_shared<SlotData1_3>(slot_data));
    }
    if (gen_version_string == "1.4")
    {
        return SlotData(std::make_shared<SlotData1_4>(slot_data));
    }
    if (gen_version_string == "1.5")
    {
        return SlotData(std::make_shared<SlotData1_5>(slot_data));
    }

    return SlotData(std::make_shared<SlotDataInvalid>(gen_version_string));
}

bool PVZRAPData::SlotData::is_valid() const
{
    return inner->is_valid();
}

std::string PVZRAPData::SlotData::version() const
{
    return inner->version();
}

PVZRAPData::SlotData::LevelRandomisation PVZRAPData::SlotData::minigame_levels() const
{
    return inner->minigame_levels();
}

PVZRAPData::SlotData::LevelRandomisation PVZRAPData::SlotData::puzzle_levels() const
{
    return inner->puzzle_levels();
}

PVZRAPData::SlotData::LevelRandomisation PVZRAPData::SlotData::survival_levels() const
{
    return inner->survival_levels();
}

std::map<int, int> PVZRAPData::SlotData::minigame_unlocks() const
{
    return inner->minigame_unlocks();
}

std::map<int, int> PVZRAPData::SlotData::survival_unlocks() const
{
    return inner->survival_unlocks();
}

std::map<int, int> PVZRAPData::SlotData::izombie_unlocks() const
{
    return inner->izombie_unlocks();
}

std::map<int, int> PVZRAPData::SlotData::vasebreaker_unlocks() const
{
    return inner->vasebreaker_unlocks();
}

std::optional<std::set<ZombieType>> PVZRAPData::SlotData::zombies_on_level(int level) const
{
    return inner->zombies_on_level(level);
}

std::optional<std::map<SeedType, int>> PVZRAPData::SlotData::conveyor_seeds_for_level(int level) const
{
    return inner->conveyor_seeds_for_level(level);
}

bool PVZRAPData::SlotData::easy_upgrade_plants() const
{
    return inner->easy_upgrade_plants();
}

bool PVZRAPData::SlotData::disable_storm_flashes() const
{
    return inner->disable_storm_flashes();
}

bool PVZRAPData::SlotData::imitater_open() const
{
    return inner->imitater_open();
}

int PVZRAPData::SlotData::sun_per_upgrade() const
{
    return inner->sun_per_upgrade();
}

std::optional<PVZRAPData::SlotData::SeedStats> PVZRAPData::SlotData::seed_stats(const SeedType seed) const
{
    return inner->seed_stats(seed);
}

std::optional<PVZRAPData::SlotData::ProjectileStats> PVZRAPData::SlotData::projectile_stats(const ProjectileType projectile) const
{
    return inner->projectile_stats(projectile);
}

PVZRAPData::SlotData::SlotData(const std::shared_ptr<SlotDataInner>& inner) : inner(inner)
{
}
