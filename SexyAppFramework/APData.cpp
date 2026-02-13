#include "APData.h"

#include <nlohmann/json.hpp>

#include "APSlotData/SlotData1_3.h"
#include "APSlotData/SlotData1_4.h"

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

    return SlotData(nullptr);
}

bool PVZRAPData::SlotData::is_valid() const
{
    return inner != nullptr;
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
