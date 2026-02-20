#ifndef APDATA_H
#define APDATA_H

#include <cstdint>
#include <optional>
#include <set>
#include <stdexcept>
#include <nlohmann/json_fwd.hpp>

#include "../ConstEnums.h"

namespace PVZRAPData
{
    namespace Locations
    {
        enum class SurvivalClass
        {
            DAY,
            NIGHT,
            POOL,
            FOG,
            ROOF,
            DAY_HARD,
            NIGHT_HARD,
            POOL_HARD,
            FOG_HARD,
            ROOF_HARD
        };
        
        /// Get the AP location ID for clearing a level
        /// For example, LevelClear(3, 2) will get the AP location ID for Level 2-2
        /// Dr. Zomboss is 5-10
        inline int64_t LevelClear(const int location, const int level)
        {
            if (location < 1)
            {
                return -1;
            }
            else if (location > 5)
            {
                return -1;
            }
            else if (level < 1)
            {
                return -1;
            }
            else if (level > 10)
            {
                return -1;
            }
            
            return 1000 + (location - 1) * 10 + (level - 1);
        }

        inline int64_t LevelClear(const int level)
        {
            if (level < 1 || level > 50)
            {
                return -1;
            }
            return 1000 + level - 1;
        }

        inline int64_t Twiddydinkie(const int index)
        {
            if (index < 0 || index > 63)
            {
                return -1;
            }
            return 5000 + index;
        }
        
        // Flag is 1-based
        inline int64_t SurvivalFlag(SurvivalClass cls, int flag)
        {
            switch (cls)
            {
            case SurvivalClass::DAY:
                if (flag < 1 || flag > 4) return -1;
                return 2063 + flag;
            case SurvivalClass::NIGHT:
                if (flag < 1 || flag > 4) return -1;
                return 2067 + flag;
            case SurvivalClass::POOL:
                if (flag < 1 || flag > 4) return -1;
                return 2071 + flag;
            case SurvivalClass::FOG:
                if (flag < 1 || flag > 4) return -1;
                return 2075 + flag;
            case SurvivalClass::ROOF:
                if (flag < 1 || flag > 4) return -1;
                return 2079 + flag;
            case SurvivalClass::DAY_HARD:
                if (flag < 1 || flag > 9) return -1;
                return 2083 + flag;
            case SurvivalClass::NIGHT_HARD:
                if (flag < 1 || flag > 9) return -1;
                return 2092 + flag;
            case SurvivalClass::POOL_HARD:
                if (flag < 1 || flag > 9) return -1;
                return 2101 + flag;
            case SurvivalClass::FOG_HARD:
                if (flag < 1 || flag > 9) return -1;
                return 2110 + flag;
            case SurvivalClass::ROOF_HARD:
                if (flag < 1 || flag > 9) return -1;
                return 2119 + flag;
            }
            return -1;
        }
        
        inline int64_t GamemodeClear(GameMode game_mode)
        {
            if (game_mode >= GameMode::GAMEMODE_CHALLENGE_WAR_AND_PEAS && game_mode <= GameMode::GAMEMODE_CHALLENGE_FINAL_BOSS)
            {
                return 1050 + game_mode - GAMEMODE_CHALLENGE_WAR_AND_PEAS;
            }
            if (game_mode >= GameMode::GAMEMODE_SCARY_POTTER_1 && game_mode <= GAMEMODE_SCARY_POTTER_9)
            {
                return 1070 + game_mode - GAMEMODE_SCARY_POTTER_1;
            }
            if (game_mode >= GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_1 && game_mode <= GAMEMODE_PUZZLE_I_ZOMBIE_9)
            {
                return 1079 + game_mode - GAMEMODE_PUZZLE_I_ZOMBIE_1;
            }
            if (game_mode >= GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_1 && game_mode <= GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_5)
            {
                return 1088 + game_mode - GAMEMODE_SURVIVAL_NORMAL_STAGE_1;
            }
            if (game_mode >= GameMode::GAMEMODE_SURVIVAL_HARD_STAGE_1 && game_mode <= GameMode::GAMEMODE_SURVIVAL_HARD_STAGE_5)
            {
                return 1093 + game_mode - GAMEMODE_SURVIVAL_HARD_STAGE_1;
            }
            return -1;
        }
        
        constexpr int64_t FLAG_1_7_1 = 2000;
        constexpr int64_t FLAG_1_9_1 = 2001;
        constexpr int64_t FLAG_1_10_1 = 2002;
        constexpr int64_t FLAG_2_2_1 = 2003;
        constexpr int64_t FLAG_2_4_1 = 2004;
        constexpr int64_t FLAG_2_7_1 = 2005;
        constexpr int64_t FLAG_2_9_1 = 2006;
        constexpr int64_t FLAG_2_10_1 = 2007;
        constexpr int64_t FLAG_3_2_1 = 2008;
        constexpr int64_t FLAG_3_3_1 = 2009;
        constexpr int64_t FLAG_3_4_1 = 2010;
        constexpr int64_t FLAG_3_4_2 = 2011;
        constexpr int64_t FLAG_3_5_1 = 2012;
        constexpr int64_t FLAG_3_6_1 = 2013;
        constexpr int64_t FLAG_3_7_1 = 2014;
        constexpr int64_t FLAG_3_7_2 = 2015;
        constexpr int64_t FLAG_3_8_1 = 2016;
        constexpr int64_t FLAG_3_9_1 = 2017;
        constexpr int64_t FLAG_3_9_2 = 2018;
        constexpr int64_t FLAG_3_10_1 = 2019;
        constexpr int64_t FLAG_3_10_2 = 2020;
        constexpr int64_t FLAG_4_2_1 = 2021;
        constexpr int64_t FLAG_4_4_1 = 2022;
        constexpr int64_t FLAG_4_7_1 = 2023;
        constexpr int64_t FLAG_4_9_1 = 2024;
        constexpr int64_t FLAG_4_10_1 = 2025;
        constexpr int64_t FLAG_5_2_1 = 2026;
        constexpr int64_t FLAG_5_3_1 = 2027;
        constexpr int64_t FLAG_5_4_1 = 2028;
        constexpr int64_t FLAG_5_4_2 = 2029;
        constexpr int64_t FLAG_5_5_1 = 2030;
        constexpr int64_t FLAG_5_6_1 = 2031;
        constexpr int64_t FLAG_5_7_1 = 2032;
        constexpr int64_t FLAG_5_7_2 = 2033;
        constexpr int64_t FLAG_5_8_1 = 2034;
        constexpr int64_t FLAG_5_9_1 = 2035;
        constexpr int64_t FLAG_5_9_2 = 2036;
        
        constexpr int64_t FLAG_ZOMBOTANY_1 = 2037;
        constexpr int64_t FLAG_WALL_NUT_BOWLING_1 = 2038;
        constexpr int64_t FLAG_RAINING_SEEDS_1 = 2039;
        constexpr int64_t FLAG_RAINING_SEEDS_2 = 2040;
        constexpr int64_t FLAG_RAINING_SEEDS_3 = 2041;
        constexpr int64_t FLAG_INVISIGHOUL_1 = 2042;
        constexpr int64_t FLAG_BIG_TROUBLE_LITTLE_ZOMBIE_1 = 2043;
        constexpr int64_t FLAG_BIG_TROUBLE_LITTLE_ZOMBIE_2 = 2044;
        constexpr int64_t FLAG_PORTAL_COMBAT_1 = 2045;
        constexpr int64_t FLAG_COLUMN_SEE_EM_1 = 2046;
        constexpr int64_t FLAG_COLUMN_SEE_EM_2 = 2047;
        constexpr int64_t FLAG_BOBSLED_BONANZA_1 = 2048;
        constexpr int64_t FLAG_BOBSLED_BONANZA_2 = 2049;
        constexpr int64_t FLAG_BOBSLED_BONANZA_3 = 2050;
        constexpr int64_t FLAG_ZOMBIE_NIMBLE_ZOMBIE_QUICK_1 = 2051;
        constexpr int64_t FLAG_ZOMBIE_NIMBLE_ZOMBIE_QUICK_2 = 2052;
        constexpr int64_t FLAG_ZOMBIE_NIMBLE_ZOMBIE_QUICK_3 = 2053;
        constexpr int64_t FLAG_LAST_STAND_1 = 2054;
        constexpr int64_t FLAG_LAST_STAND_2 = 2055;
        constexpr int64_t FLAG_LAST_STAND_3 = 2056;
        constexpr int64_t FLAG_LAST_STAND_4 = 2057;
        constexpr int64_t FLAG_ZOMBOTANY_2_1 = 2058;
        constexpr int64_t FLAG_ZOMBOTANY_2_2 = 2059;
        constexpr int64_t FLAG_WALL_NUT_BOWLING_2_1 = 2060;
        constexpr int64_t FLAG_WALL_NUT_BOWLING_2_2 = 2061;
        constexpr int64_t FLAG_POGO_PARTY_1 = 2062;
        constexpr int64_t FLAG_POGO_PARTY_2 = 2063;
        
        inline const int64_t* LevelFlagList(const int level)
        {
            static constexpr int64_t null_set[] = {-1};
            
            if (level < 1 || level > 50)
            {
                return null_set;
            }
            if (level == 7)
            {
                static constexpr int64_t flags[] = {FLAG_1_7_1, -1};
                return flags;
            }
            if (level == 9)
            {
                static constexpr int64_t flags[] = {FLAG_1_9_1, -1};
                return flags;
            }
            if (level == 10)
            {
                static constexpr int64_t flags[] = {FLAG_1_10_1, -1};
                return flags;
            }
            if (level == 12)
            {
                static constexpr int64_t flags[] = {FLAG_2_2_1, -1};
                return flags;
            }
            if (level == 14)
            {
                static constexpr int64_t flags[] = {FLAG_2_4_1, -1};
                return flags;
            }
            if (level == 17)
            {
                static constexpr int64_t flags[] = {FLAG_2_7_1, -1};
                return flags;
            }
            if (level == 19)
            {
                static constexpr int64_t flags[] = {FLAG_2_9_1, -1};
                return flags;
            }
            if (level == 20)
            {
                static constexpr int64_t flags[] = {FLAG_2_10_1, -1};
                return flags;
            }
            if (level == 22)
            {
                static constexpr int64_t flags[] = {FLAG_3_2_1, -1};
                return flags;
            }
            if (level == 23)
            {
                static constexpr int64_t flags[] = {FLAG_3_3_1, -1};
                return flags;
            }
            if (level == 24)
            {
                static constexpr int64_t flags[] = {FLAG_3_4_1, FLAG_3_4_2, -1};
                return flags;
            }
            if (level == 25)
            {
                static constexpr int64_t flags[] = {FLAG_3_5_1, -1};
                return flags;
            }
            if (level == 26)
            {
                static constexpr int64_t flags[] = {FLAG_3_6_1, -1};
                return flags;
            }
            if (level == 27)
            {
                static constexpr int64_t flags[] = {FLAG_3_7_1, FLAG_3_7_2, -1};
                return flags;
            }
            if (level == 28)
            {
                static constexpr int64_t flags[] = {FLAG_3_8_1, -1};
                return flags;
            }
            if (level == 29)
            {
                static constexpr int64_t flags[] = {FLAG_3_9_1, FLAG_3_9_2, -1};
                return flags;
            }
            if (level == 30)
            {
                static constexpr int64_t flags[] = {FLAG_3_10_1, FLAG_3_10_2, -1};
                return flags;
            }
            if (level == 32)
            {
                static constexpr int64_t flags[] = {FLAG_4_2_1, -1};
                return flags;
            }
            if (level == 34)
            {
                static constexpr int64_t flags[] = {FLAG_4_4_1, -1};
                return flags;
            }
            if (level == 37)
            {
                static constexpr int64_t flags[] = {FLAG_4_7_1, -1};
                return flags;
            }
            if (level == 39)
            {
                static constexpr int64_t flags[] = {FLAG_4_9_1, -1};
                return flags;
            }
            if (level == 40)
            {
                static constexpr int64_t flags[] = {FLAG_4_10_1, -1};
                return flags;
            }
            if (level == 42)
            {
                static constexpr int64_t flags[] = {FLAG_5_2_1, -1};
                return flags;
            }
            if (level == 43)
            {
                static constexpr int64_t flags[] = {FLAG_5_3_1, -1};
                return flags;
            }
            if (level == 44)
            {
                static constexpr int64_t flags[] = {FLAG_5_4_1, FLAG_5_4_2, -1};
                return flags;
            }
            if (level == 45)
            {
                static constexpr int64_t flags[] = {FLAG_5_5_1, -1};
                return flags;
            }
            if (level == 46)
            {
                static constexpr int64_t flags[] = {FLAG_5_6_1, -1};
                return flags;
            }
            if (level == 47)
            {
                static constexpr int64_t flags[] = {FLAG_5_7_1, FLAG_5_7_2, -1};
                return flags;
            }
            if (level == 48)
            {
                static constexpr int64_t flags[] = {FLAG_5_8_1, -1};
                return flags;
            }
            if (level == 49)
            {
                static constexpr int64_t flags[] = {FLAG_5_9_1, FLAG_5_9_2, -1};
                return flags;
            }
            
            return null_set;
        }
    }
    
    namespace Items
    {
        inline int64_t Seed(SeedType seed)
        {
            if (seed < SEED_PEASHOOTER || seed > SEED_IMITATER)
            {
                return -1;
            }
            return 100 + seed;
        }
        
        constexpr int64_t MUSIC_VIDEO = 1;
        constexpr int64_t CAR_KEYS = 2;
        constexpr int64_t EXTRA_SEED_SLOT = 3;
        constexpr int64_t SHOVEL = 4;
        constexpr int64_t ALMANAC = 5;
        constexpr int64_t ZEN_GARDEN = 6;
        constexpr int64_t MINIGAMES = 7;
        constexpr int64_t PUZZLE_MODE = 8;
        constexpr int64_t SURVIVAL_MODE = 9;
        constexpr int64_t CLOUDY_DAY = 10;
        constexpr int64_t BONUS_LEVELS = 11;
        constexpr int64_t ROOF_CLEANERS = 12;
        constexpr int64_t POOL_CLEANERS = 13;
        constexpr int64_t LAWN_MOWERS = 14;
        constexpr int64_t TWIDDYDINKIES_RESTOCK = 15;
        constexpr int64_t WALL_NUT_FIRST_AID = 16;
        constexpr int64_t RAKE = 17;
        constexpr int64_t ADDITIONAL_STARTING_SUN = 18;
        constexpr int64_t DAY_ACCESS = 20;
        constexpr int64_t NIGHT_ACCESS = 21;
        constexpr int64_t POOL_ACCESS = 22;
        constexpr int64_t FOG_ACCESS = 23;
        constexpr int64_t ROOF_ACCESS = 24;
        
        constexpr int64_t MUSTACHE_MODE = 50;
        constexpr int64_t FUTURE_ZOMBIES_MODE = 51;
        constexpr int64_t TRICKED_OUT_MODE = 52;
        constexpr int64_t DAISIES_MODE = 53;
        constexpr int64_t PINATA_MODE = 54;
        constexpr int64_t ALTERNATE_BRAINS_SOUND = 55;
        constexpr int64_t DANCING_ZOMBIES_MODE = 56;
        
        constexpr int64_t SILVER_COIN = 60;
        constexpr int64_t GOLD_COIN = 61;
        constexpr int64_t DIAMOND = 62;
        constexpr int64_t NOTHING = 63;
        
        constexpr int64_t TRAP_MOWER_DEPLOY = 70;
        constexpr int64_t TRAP_PACKET_COOLDOWN = 71;
        constexpr int64_t TRAP_ZOMBIE_AMBUSH = 72;
        
        inline SeedType SeedItem(int64_t item)
        {
            if (item < 100 || item > 100 + SEED_IMITATER)
            {
                return SEED_NONE;
            }
            return static_cast<SeedType>(item - 100);
        }
        
        inline int Level(const int level)
        {
            if (level < 1 || level > 50)
            {
                return -1;
            }
            return 200 + level;
        }
        
        inline int Gamemode(const GameMode game_mode)
        {
            if (game_mode >= GameMode::GAMEMODE_CHALLENGE_WAR_AND_PEAS && game_mode <= GameMode::GAMEMODE_CHALLENGE_FINAL_BOSS)
            {
                return 251 + game_mode - GAMEMODE_CHALLENGE_WAR_AND_PEAS;
            }
            if (game_mode >= GameMode::GAMEMODE_SCARY_POTTER_1 && game_mode <= GAMEMODE_SCARY_POTTER_9)
            {
                return 271 + game_mode - GAMEMODE_SCARY_POTTER_1;
            }
            if (game_mode >= GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_1 && game_mode <= GAMEMODE_PUZZLE_I_ZOMBIE_9)
            {
                return 280 + game_mode - GAMEMODE_PUZZLE_I_ZOMBIE_1;
            }
            if (game_mode >= GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_1 && game_mode <= GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_5)
            {
                return 289 + game_mode - GAMEMODE_SURVIVAL_NORMAL_STAGE_1;
            }
            if (game_mode >= GameMode::GAMEMODE_SURVIVAL_HARD_STAGE_1 && game_mode <= GameMode::GAMEMODE_SURVIVAL_HARD_STAGE_5)
            {
                return 294 + game_mode - GAMEMODE_SURVIVAL_HARD_STAGE_1;
            }
            return -1;
        }
    }
    
    class SlotData
    {
    public:
        class SlotDataInner;
        
        enum class LevelRandomisation
        {
            Off = 0,
            Vanilla = 1,
            RandomisedOrder = 2,
            Open = 3,
            LevelItems = 4
        };
        
        struct SeedStats
        {
            std::optional<int> sun_price;
            std::optional<int> recharge_time;
            std::optional<int> firing_rate;
            std::optional<int> health;
        };
        
        struct ProjectileStats
        {
            std::optional<int> damage;
        };
        
        static SlotData get_slot_data(const nlohmann::json& json);
        
        bool is_valid() const;
        std::string version() const;
        
        LevelRandomisation minigame_levels() const;
        LevelRandomisation puzzle_levels() const;
        LevelRandomisation survival_levels() const;
        
        std::map<int, int> minigame_unlocks() const;
        std::map<int, int> survival_unlocks() const;
        std::map<int, int> izombie_unlocks() const;
        std::map<int, int> vasebreaker_unlocks() const;
        
        std::optional<std::set<ZombieType>> zombies_on_level(int level) const;
        std::optional<std::map<SeedType, int>> conveyor_seeds_for_level(int level) const;
        
        bool easy_upgrade_plants() const;
        bool disable_storm_flashes() const;
        bool imitater_open() const;
        
        int sun_per_upgrade() const;
        
        std::optional<SeedStats> seed_stats(SeedType seed) const;
        std::optional<ProjectileStats> projectile_stats(ProjectileType projectile) const;
        
    private:
        
        explicit SlotData(const std::shared_ptr<SlotDataInner>& inner);
        std::shared_ptr<SlotDataInner> inner;
    };
}

#endif
