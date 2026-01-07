#ifndef APDATA_H
#define APDATA_H

#include <cstdint>

#include "../ConstEnums.h"

namespace PVZRAPData
{
    namespace Locations
    {
        /// Get the AP location ID for clearing a level
        /// For example, LevelClear(3, 2) will get the AP location ID for Level 2-2
        /// Dr. Zomboss is 5-10
        constexpr int64_t LevelClear(const int location, const int level)
        {
            static_assert(location >= 1, "Location must be >= 1");
            static_assert(location <= 5, "Location must be <= 5");
            static_assert(level >= 1, "Level must be >= 1");
            static_assert(level <= 10, "Level must be <= 10");
            return 1000 + (location - 1) * 10 + (level - 1);
        }
        
        constexpr int64_t Twiddydinkie(const int index)
        {
            static_assert(index >= 1 && index <= 16, "Index must be >= 1 and <= 16");
            return 5000 + index - 1;
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
        
        // TODO: Flag locations
        
        
    }
    
    namespace Items
    {
        constexpr int64_t Seed(SeedType seed)
        {
            switch (seed)
            {
            case SEED_PEASHOOTER:
                return 500;
            case SEED_SUNFLOWER:
                return 501;
            case SEED_CHERRYBOMB:
                return 502;
            case SEED_WALLNUT:
                return 503;
            case SEED_POTATOMINE:
                return 504;
            case SEED_SNOWPEA:
                return 505;
            case SEED_CHOMPER:
                return 506;
            case SEED_REPEATER:
                return 507;
            case SEED_PUFFSHROOM:
                return 508;
            case SEED_SUNSHROOM:
                return 509;
            case SEED_FUMESHROOM:
                return 510;
            case SEED_GRAVEBUSTER:
                return 511;
            case SEED_HYPNOSHROOM:
                return 512;
            case SEED_SCAREDYSHROOM:
                return 513;
            case SEED_ICESHROOM:
                return 514;
            case SEED_DOOMSHROOM:
                return 515;
            case SEED_LILYPAD:
                return 516;
            case SEED_SQUASH:
                return 517;
            case SEED_THREEPEATER:
                return 518;
            case SEED_TANGLEKELP:
                return 519;
            case SEED_JALAPENO:
                return 520;
            case SEED_SPIKEWEED:
                return 521;
            case SEED_TORCHWOOD:
                return 522;
            case SEED_TALLNUT:
                return 523;
            case SEED_SEASHROOM:
                return 524;
            case SEED_PLANTERN:
                return 525;
            case SEED_CACTUS:
                return 526;
            case SEED_BLOVER:
                return 527;
            case SEED_SPLITPEA:
                return 528;
            case SEED_STARFRUIT:
                return 529;
            case SEED_PUMPKINSHELL:
                return 530;
            case SEED_MAGNETSHROOM:
                return 531;
            case SEED_CABBAGEPULT:
                return 532;
            case SEED_FLOWERPOT:
                return 533;
            case SEED_KERNELPULT:
                return 534;
            case SEED_INSTANT_COFFEE:
                return 535;
            case SEED_GARLIC:
                return 536;
            case SEED_UMBRELLA:
                return 537;
            case SEED_MARIGOLD:
                return 538;
            case SEED_MELONPULT:
                return 539;
            case SEED_GATLINGPEA:
                return 540;
            case SEED_TWINSUNFLOWER:
                return 541;
            case SEED_GLOOMSHROOM:
                return 542;
            case SEED_CATTAIL:
                return 543;
            case SEED_WINTERMELON:
                return 544;
            case SEED_GOLD_MAGNET:
                return 545;
            case SEED_SPIKEROCK:
                return 546;
            case SEED_COBCANNON:
                return 547;
            case SEED_IMITATER:
                return 548;
            }
            static_assert(false, "Invalid seed type");
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
    }
}

#endif
