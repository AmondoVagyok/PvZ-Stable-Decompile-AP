#ifndef APDATA_H
#define APDATA_H

#include <cstdint>
#include <stdexcept>

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
            if (index < 0 || index > 15)
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
                return 2063 + flag;
            case SurvivalClass::NIGHT:
                return 2067 + flag;
            case SurvivalClass::POOL:
                return 2071 + flag;
            case SurvivalClass::FOG:
                return 2075 + flag;
            case SurvivalClass::ROOF:
                return 2079 + flag;
            case SurvivalClass::DAY_HARD:
                return 2083 + flag;
            case SurvivalClass::NIGHT_HARD:
                return 2092 + flag;
            case SurvivalClass::POOL_HARD:
                return 2101 + flag;
            case SurvivalClass::FOG_HARD:
                return 2110 + flag;
            case SurvivalClass::ROOF_HARD:
                return 2119 + flag;
            }
        }
        
        constexpr int64_t MINIGAME_ZOMBOTANY_CLEAR = 1050;
        constexpr int64_t MINIGAME_WALL_NUT_BOWLING_CLEAR = 1051;
        constexpr int64_t MINIGAME_SLOT_MACHINE_CLEAR = 1052;
        constexpr int64_t MINIGAME_RAINING_SEEDS_CLEAR = 1053;
        constexpr int64_t MINIGAME_BEGHOULED_CLEAR = 1054;
        constexpr int64_t MINIGAME_INVISIGHOUL_CLEAR = 1055;
        constexpr int64_t MINIGAME_SEEING_STARS_CLEAR = 1056;
        constexpr int64_t MINIGAME_ZOMBIQUARIUM_CLEAR = 1057;
        constexpr int64_t MINIGAME_BEGHOULED_TWIST_CLEAR = 1058;
        constexpr int64_t MINIGAME_BIG_TROUBLE_LITTLE_ZOMBIE_CLEAR = 1059;
        constexpr int64_t MINIGAME_PORTAL_COMBAT_CLEAR = 1060;
        constexpr int64_t MINIGAME_COLUMN_SEE_EM_CLEAR = 1061;
        constexpr int64_t MINIGAME_BOBSLED_BONANZA_CLEAR = 1062;
        constexpr int64_t MINIGAME_ZOMBIE_NIMBLE_ZOMBIE_QUICK_CLEAR = 1063;
        constexpr int64_t MINIGAME_WHACK_A_ZOMBIE_CLEAR = 1064;
        constexpr int64_t MINIGAME_LAST_STAND_CLEAR = 1065;
        constexpr int64_t MINIGAME_ZOMBOTANY_2_CLEAR = 1066;
        constexpr int64_t MINIGAME_WALL_NUT_BOWLING_2_CLEAR = 1067;
        constexpr int64_t MINIGAME_POGO_PARTY_CLEAR = 1068;
        constexpr int64_t MINIGAME_ZOMBOSS_REVENGE_CLEAR = 1069;
        
        constexpr int64_t PUZZLE_VASEBREAKER_CLEAR = 1070;
        constexpr int64_t PUZZLE_TO_THE_LEFT_CLEAR = 1071;
        constexpr int64_t PUZZLE_THIRD_VASE_CLEAR = 1072;
        constexpr int64_t PUZZLE_CHAIN_REACTION_CLEAR = 1073;
        constexpr int64_t PUZZLE_M_FOR_METAL_CLEAR = 1074;
        constexpr int64_t PUZZLE_SCARY_POTTER_CLEAR = 1075;
        constexpr int64_t PUZZLE_HOKEY_POKEY_CLEAR = 1076;
        constexpr int64_t PUZZLE_ANOTHER_CHAIN_REACTION_CLEAR = 1077;
        constexpr int64_t PUZZLE_ACE_OF_VASE_CLEAR = 1078;
        constexpr int64_t PUZZLE_I_ZOMBIE_CLEAR = 1079;
        constexpr int64_t PUZZLE_I_ZOMBIE_TOO_CLEAR = 1080;
        constexpr int64_t PUZZLE_DIG_IT_CLEAR = 1081;
        constexpr int64_t PUZZLE_TOTALLY_NUTS_CLEAR = 1082;
        constexpr int64_t PUZZLE_DEAD_ZEPPELIN_CLEAR = 1083;
        constexpr int64_t PUZZLE_ME_SMASH_CLEAR = 1084;
        constexpr int64_t PUZZLE_ZOMBOOGIE_CLEAR = 1085;
        constexpr int64_t PUZZLE_THREE_HIT_WONDER_CLEAR = 1086;
        constexpr int64_t PUZZLE_BRAINZ_BELONG_TO_US_CLEAR = 1087;
        
        constexpr int64_t SURVIVAL_DAY_CLEAR = 1088;
        constexpr int64_t SURVIVAL_NIGHT_CLEAR = 1089;
        constexpr int64_t SURVIVAL_POOL_CLEAR = 1090;
        constexpr int64_t SURVIVAL_FOG_CLEAR = 1091;
        constexpr int64_t SURVIVAL_ROOF_CLEAR = 1092;
        constexpr int64_t SURVIVAL_DAY_HARD_CLEAR = 1093;
        constexpr int64_t SURVIVAL_NIGHT_HARD_CLEAR = 1094;
        constexpr int64_t SURVIVAL_POOL_HARD_CLEAR = 1095;
        constexpr int64_t SURVIVAL_FOG_HARD_CLEAR = 1096;
        constexpr int64_t SURVIVAL_ROOF_HARD_CLEAR = 1097;
        
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
        
        constexpr int64_t TRAP_POWER_DEPLOY = 70;
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
    }
}

#endif
