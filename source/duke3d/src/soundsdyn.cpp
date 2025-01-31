//-------------------------------------------------------------------------
/*
Copyright (C) 2013 EDuke32 developers and contributors

This file is part of EDuke32.

EDuke32 is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License version 2
as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
//-------------------------------------------------------------------------

#include "compat.h"
#include "build.h"

#include "namesdyn.h"
#include "sounds.h"
#include "soundsdyn.h"
#include "global.h"

#ifdef DYNSOUNDREMAP_ENABLE
# define DVPTR(x) &x
#else
# define DVPTR(x) NULL
#endif

int16_t DynamicSoundMap[MAXSOUNDS];

struct dynitem
{
    const char *str;
    int32_t *dynvalptr;
    const int16_t staticval;
};

static struct dynitem g_dynSoundList[] =
{
    { "ALIEN_SWITCH1",       DVPTR(ALIEN_SWITCH1),      ALIEN_SWITCH1__STATIC },
    { "BIGBANG",             DVPTR(BIGBANG),            BIGBANG__STATIC },
    { "BONUS_SPEECH1",       DVPTR(BONUS_SPEECH1),      BONUS_SPEECH1__STATIC },
    { "BONUS_SPEECH2",       DVPTR(BONUS_SPEECH2),      BONUS_SPEECH2__STATIC },
    { "BONUS_SPEECH3",       DVPTR(BONUS_SPEECH3),      BONUS_SPEECH3__STATIC },
    { "BONUS_SPEECH4",       DVPTR(BONUS_SPEECH4),      BONUS_SPEECH4__STATIC },
    { "BONUSMUSIC",          DVPTR(BONUSMUSIC),         BONUSMUSIC__STATIC },
    { "BOS1_RECOG",          DVPTR(BOS1_RECOG),         BOS1_RECOG__STATIC },
    { "BOS1_WALK",           DVPTR(BOS1_WALK),          BOS1_WALK__STATIC },
    { "BOS2_RECOG",          DVPTR(BOS2_RECOG),         BOS2_RECOG__STATIC },
    { "BOS3_RECOG",          DVPTR(BOS3_RECOG),         BOS3_RECOG__STATIC },
    { "BOS4_RECOG",          DVPTR(BOS4_RECOG),         BOS4_RECOG__STATIC },
    { "BOSS4_DEADSPEECH",    DVPTR(BOSS4_DEADSPEECH),   BOSS4_DEADSPEECH__STATIC },
    { "BOSS4_FIRSTSEE",      DVPTR(BOSS4_FIRSTSEE),     BOSS4_FIRSTSEE__STATIC },
    { "BOSSTALKTODUKE",      DVPTR(BOSSTALKTODUKE),     BOSSTALKTODUKE__STATIC },
    { "CAPT_RECOG",          DVPTR(CAPT_RECOG),         CAPT_RECOG__STATIC },
    { "CAT_FIRE",            DVPTR(CAT_FIRE),           CAT_FIRE__STATIC },
    { "CHAINGUN_FIRE",       DVPTR(CHAINGUN_FIRE),      CHAINGUN_FIRE__STATIC },
    { "COMM_RECOG",          DVPTR(COMM_RECOG),         COMM_RECOG__STATIC },
    { "DRON_RECOG",          DVPTR(DRON_RECOG),         DRON_RECOG__STATIC },
    { "DUKE_CRACK",          DVPTR(DUKE_CRACK),          DUKE_CRACK__STATIC },
    { "DUKE_CRACK_FIRST",    DVPTR(DUKE_CRACK_FIRST),    DUKE_CRACK_FIRST__STATIC },
    { "DUKE_CRACK2",         DVPTR(DUKE_CRACK2),         DUKE_CRACK2__STATIC },
    { "DUKE_DRINKING",       DVPTR(DUKE_DRINKING),       DUKE_DRINKING__STATIC },
    { "DUKE_GASP",           DVPTR(DUKE_GASP),           DUKE_GASP__STATIC },
    { "DUKE_GET",            DVPTR(DUKE_GET),            DUKE_GET__STATIC },
    { "DUKE_GETWEAPON2",     DVPTR(DUKE_GETWEAPON2),     DUKE_GETWEAPON2__STATIC },
    { "DUKE_GETWEAPON6",     DVPTR(DUKE_GETWEAPON6),     DUKE_GETWEAPON6__STATIC },
    { "DUKE_GOTHEALTHATLOW", DVPTR(DUKE_GOTHEALTHATLOW), DUKE_GOTHEALTHATLOW__STATIC },
    { "DUKE_GRUNT",          DVPTR(DUKE_GRUNT),          DUKE_GRUNT__STATIC },
    { "DUKE_HARTBEAT",       DVPTR(DUKE_HARTBEAT),       DUKE_HARTBEAT__STATIC },
    { "DUKE_JETPACK_IDLE",   DVPTR(DUKE_JETPACK_IDLE),   DUKE_JETPACK_IDLE__STATIC },
    { "DUKE_JETPACK_OFF",    DVPTR(DUKE_JETPACK_OFF),    DUKE_JETPACK_OFF__STATIC },
    { "DUKE_JETPACK_ON",     DVPTR(DUKE_JETPACK_ON),     DUKE_JETPACK_ON__STATIC },
    { "DUKE_LAND",           DVPTR(DUKE_LAND),           DUKE_LAND__STATIC },
    { "DUKE_LAND_HURT",      DVPTR(DUKE_LAND_HURT),      DUKE_LAND_HURT__STATIC },
    { "DUKE_LONGTERM_PAIN",  DVPTR(DUKE_LONGTERM_PAIN),  DUKE_LONGTERM_PAIN__STATIC },
    { "DUKE_ONWATER",        DVPTR(DUKE_ONWATER),        DUKE_ONWATER__STATIC },
    { "DUKE_PISSRELIEF",     DVPTR(DUKE_PISSRELIEF),     DUKE_PISSRELIEF__STATIC },
    { "DUKE_SCREAM",         DVPTR(DUKE_SCREAM),         DUKE_SCREAM__STATIC },
    { "DUKE_SEARCH",         DVPTR(DUKE_SEARCH),         DUKE_SEARCH__STATIC },
    { "DUKE_SEARCH2",        DVPTR(DUKE_SEARCH2),        DUKE_SEARCH2__STATIC },
    { "DUKE_TAKEPILLS",      DVPTR(DUKE_TAKEPILLS),      DUKE_TAKEPILLS__STATIC },
    { "DUKE_UNDERWATER",     DVPTR(DUKE_UNDERWATER),     DUKE_UNDERWATER__STATIC },
    { "DUKE_URINATE",        DVPTR(DUKE_URINATE),        DUKE_URINATE__STATIC },
    { "DUKE_USEMEDKIT",      DVPTR(DUKE_USEMEDKIT),      DUKE_USEMEDKIT__STATIC },
    { "DUKE_WALKINDUCTS",    DVPTR(DUKE_WALKINDUCTS),    DUKE_WALKINDUCTS__STATIC },
    { "DUKETALKTOBOSS",      DVPTR(DUKETALKTOBOSS),      DUKETALKTOBOSS__STATIC },
    { "EARTHQUAKE",          DVPTR(EARTHQUAKE),         EARTHQUAKE__STATIC },
    { "EJECT_CLIP",          DVPTR(EJECT_CLIP),         EJECT_CLIP__STATIC },
    { "ELEVATOR_OFF",        DVPTR(ELEVATOR_OFF),       ELEVATOR_OFF__STATIC },
    { "ELEVATOR_ON",         DVPTR(ELEVATOR_ON),        ELEVATOR_ON__STATIC },
    { "END_OF_LEVEL_WARN",   DVPTR(END_OF_LEVEL_WARN),  END_OF_LEVEL_WARN__STATIC },
    { "ENDSEQVOL2SND1",      DVPTR(ENDSEQVOL2SND1),     ENDSEQVOL2SND1__STATIC },
    { "ENDSEQVOL2SND2",      DVPTR(ENDSEQVOL2SND2),     ENDSEQVOL2SND2__STATIC },
    { "ENDSEQVOL2SND3",      DVPTR(ENDSEQVOL2SND3),     ENDSEQVOL2SND3__STATIC },
    { "ENDSEQVOL2SND4",      DVPTR(ENDSEQVOL2SND4),     ENDSEQVOL2SND4__STATIC },
    { "ENDSEQVOL2SND5",      DVPTR(ENDSEQVOL2SND5),     ENDSEQVOL2SND5__STATIC },
    { "ENDSEQVOL2SND6",      DVPTR(ENDSEQVOL2SND6),     ENDSEQVOL2SND6__STATIC },
    { "ENDSEQVOL2SND7",      DVPTR(ENDSEQVOL2SND7),     ENDSEQVOL2SND7__STATIC },
    { "ENDSEQVOL3SND2",      DVPTR(ENDSEQVOL3SND2),     ENDSEQVOL3SND2__STATIC },
    { "ENDSEQVOL3SND3",      DVPTR(ENDSEQVOL3SND3),     ENDSEQVOL3SND3__STATIC },
    { "ENDSEQVOL3SND4",      DVPTR(ENDSEQVOL3SND4),     ENDSEQVOL3SND4__STATIC },
    { "ENDSEQVOL3SND5",      DVPTR(ENDSEQVOL3SND5),     ENDSEQVOL3SND5__STATIC },
    { "ENDSEQVOL3SND6",      DVPTR(ENDSEQVOL3SND6),     ENDSEQVOL3SND6__STATIC },
    { "ENDSEQVOL3SND7",      DVPTR(ENDSEQVOL3SND7),     ENDSEQVOL3SND7__STATIC },
    { "ENDSEQVOL3SND8",      DVPTR(ENDSEQVOL3SND8),     ENDSEQVOL3SND8__STATIC },
    { "ENDSEQVOL3SND9",      DVPTR(ENDSEQVOL3SND9),     ENDSEQVOL3SND9__STATIC },
    { "EXITMENUSOUND",       DVPTR(EXITMENUSOUND),      EXITMENUSOUND__STATIC },
    { "EXPANDERSHOOT",       DVPTR(EXPANDERSHOOT),      EXPANDERSHOOT__STATIC },
    { "FLUSH_TOILET",        DVPTR(FLUSH_TOILET),       FLUSH_TOILET__STATIC },
    { "FLY_BY",              DVPTR(FLY_BY),             FLY_BY__STATIC },
    { "GENERIC_AMBIENCE17",  DVPTR(GENERIC_AMBIENCE17), GENERIC_AMBIENCE17__STATIC },
    { "GLASS_BREAKING",      DVPTR(GLASS_BREAKING),     GLASS_BREAKING__STATIC },
    { "GLASS_HEAVYBREAK",    DVPTR(GLASS_HEAVYBREAK),   GLASS_HEAVYBREAK__STATIC },
    { "INSERT_CLIP",         DVPTR(INSERT_CLIP),        INSERT_CLIP__STATIC },
    { "INTRO4_1",            DVPTR(INTRO4_1),           INTRO4_1__STATIC },
    { "INTRO4_2",            DVPTR(INTRO4_2),           INTRO4_2__STATIC },
    { "INTRO4_3",            DVPTR(INTRO4_3),           INTRO4_3__STATIC },
    { "INTRO4_4",            DVPTR(INTRO4_4),           INTRO4_4__STATIC },
    { "INTRO4_5",            DVPTR(INTRO4_5),           INTRO4_5__STATIC },
    { "INTRO4_6",            DVPTR(INTRO4_6),           INTRO4_6__STATIC },
    { "INTRO4_B",            DVPTR(INTRO4_B),           INTRO4_B__STATIC },
    { "ITEM_SPLASH",         DVPTR(ITEM_SPLASH),        ITEM_SPLASH__STATIC },
    { "JIBBED_ACTOR5",       DVPTR(JIBBED_ACTOR5),      JIBBED_ACTOR5__STATIC },
    { "JIBBED_ACTOR6",       DVPTR(JIBBED_ACTOR6),      JIBBED_ACTOR6__STATIC },
    { "KICK_HIT",            DVPTR(KICK_HIT),           KICK_HIT__STATIC },
    { "LASERTRIP_ARMING",    DVPTR(LASERTRIP_ARMING),   LASERTRIP_ARMING__STATIC },
    { "LASERTRIP_EXPLODE",   DVPTR(LASERTRIP_EXPLODE),  LASERTRIP_EXPLODE__STATIC },
    { "LASERTRIP_ONWALL",    DVPTR(LASERTRIP_ONWALL),   LASERTRIP_ONWALL__STATIC },
    { "LIGHTNING_SLAP",      DVPTR(LIGHTNING_SLAP),     LIGHTNING_SLAP__STATIC },
    { "MONITOR_ACTIVE",      DVPTR(MONITOR_ACTIVE),     MONITOR_ACTIVE__STATIC },
    { "NITEVISION_ONOFF",    DVPTR(NITEVISION_ONOFF),   NITEVISION_ONOFF__STATIC },
    { "OCTA_RECOG",          DVPTR(OCTA_RECOG),         OCTA_RECOG__STATIC },
    { "PIG_RECOG",           DVPTR(PIG_RECOG),          PIG_RECOG__STATIC },
    { "PIPEBOMB_BOUNCE",     DVPTR(PIPEBOMB_BOUNCE),    PIPEBOMB_BOUNCE__STATIC },
    { "PIPEBOMB_EXPLODE",    DVPTR(PIPEBOMB_EXPLODE),   PIPEBOMB_EXPLODE__STATIC },
    { "PISTOL_BODYHIT",      DVPTR(PISTOL_BODYHIT),     PISTOL_BODYHIT__STATIC },
    { "PISTOL_FIRE",         DVPTR(PISTOL_FIRE),        PISTOL_FIRE__STATIC },
    { "PISTOL_RICOCHET",     DVPTR(PISTOL_RICOCHET),    PISTOL_RICOCHET__STATIC },
    { "POOLBALLHIT",         DVPTR(POOLBALLHIT),        POOLBALLHIT__STATIC },
    { "PRED_RECOG",          DVPTR(PRED_RECOG),         PRED_RECOG__STATIC },
    { "RATTY",               DVPTR(RATTY),              RATTY__STATIC },
    { "RECO_ATTACK",         DVPTR(RECO_ATTACK),        RECO_ATTACK__STATIC },
    { "RECO_PAIN",           DVPTR(RECO_PAIN),          RECO_PAIN__STATIC },
    { "RECO_RECOG",          DVPTR(RECO_RECOG),         RECO_RECOG__STATIC },
    { "RECO_ROAM",           DVPTR(RECO_ROAM),          RECO_ROAM__STATIC },
    { "RIPHEADNECK",         DVPTR(RIPHEADNECK),        RIPHEADNECK__STATIC },
    { "RPG_EXPLODE",         DVPTR(RPG_EXPLODE),        RPG_EXPLODE__STATIC },
    { "RPG_SHOOT",           DVPTR(RPG_SHOOT),          RPG_SHOOT__STATIC },
    { "SELECT_WEAPON",       DVPTR(SELECT_WEAPON),      SELECT_WEAPON__STATIC },
    { "SHORT_CIRCUIT",       DVPTR(SHORT_CIRCUIT),      SHORT_CIRCUIT__STATIC },
    { "SHOTGUN_COCK",        DVPTR(SHOTGUN_COCK),       SHOTGUN_COCK__STATIC },
    { "SHOTGUN_FIRE",        DVPTR(SHOTGUN_FIRE),       SHOTGUN_FIRE__STATIC },
    { "SHRINKER_FIRE",       DVPTR(SHRINKER_FIRE),      SHRINKER_FIRE__STATIC },
    { "SHRINKER_HIT",        DVPTR(SHRINKER_HIT),       SHRINKER_HIT__STATIC },
    { "SLIM_ATTACK",         DVPTR(SLIM_ATTACK),        SLIM_ATTACK__STATIC },
    { "SLIM_DYING",          DVPTR(SLIM_DYING),         SLIM_DYING__STATIC },
    { "SLIM_RECOG",          DVPTR(SLIM_RECOG),         SLIM_RECOG__STATIC },
    { "SLIM_ROAM",           DVPTR(SLIM_ROAM),          SLIM_ROAM__STATIC },
    { "SOMETHING_DRIPPING",  DVPTR(SOMETHING_DRIPPING), SOMETHING_DRIPPING__STATIC },
    { "SOMETHINGFROZE",      DVPTR(SOMETHINGFROZE),     SOMETHINGFROZE__STATIC },
    { "SOMETHINGHITFORCE",   DVPTR(SOMETHINGHITFORCE),  SOMETHINGHITFORCE__STATIC },
    { "SQUISHED",            DVPTR(SQUISHED),           SQUISHED__STATIC },
    { "SUBWAY",              DVPTR(SUBWAY),             SUBWAY__STATIC },
    { "SWITCH_ON",           DVPTR(SWITCH_ON),          SWITCH_ON__STATIC },
    { "TELEPORTER",          DVPTR(TELEPORTER),         TELEPORTER__STATIC },
    { "THUD",                DVPTR(THUD),               THUD__STATIC },
    { "THUNDER",             DVPTR(THUNDER),            THUNDER__STATIC },
    { "TURR_RECOG",          DVPTR(TURR_RECOG),         TURR_RECOG__STATIC },
    { "VENT_BUST",           DVPTR(VENT_BUST),          VENT_BUST__STATIC },
    { "VOL4ENDSND1",         DVPTR(VOL4ENDSND1),        VOL4ENDSND1__STATIC },
    { "VOL4ENDSND2",         DVPTR(VOL4ENDSND2),        VOL4ENDSND2__STATIC },
    { "WAR_AMBIENCE2",       DVPTR(WAR_AMBIENCE2),      WAR_AMBIENCE2__STATIC },
    { "WHIPYOURASS",         DVPTR(WHIPYOURASS),        WHIPYOURASS__STATIC },
    { "WIERDSHOT_FLY",       DVPTR(WIERDSHOT_FLY),      WIERDSHOT_FLY__STATIC },
    { "WIND_AMBIENCE",       DVPTR(WIND_AMBIENCE),      WIND_AMBIENCE__STATIC },
    { "WIND_REPEAT",         DVPTR(WIND_REPEAT),        WIND_REPEAT__STATIC },
    { "FLAMETHROWER_INTRO",  DVPTR(FLAMETHROWER_INTRO), FLAMETHROWER_INTRO__STATIC },
    { "FLAMETHROWER_LOOP",   DVPTR(FLAMETHROWER_LOOP),  FLAMETHROWER_LOOP__STATIC },
    { "FLAMETHROWER_END",    DVPTR(FLAMETHROWER_END),   FLAMETHROWER_END__STATIC },
    { "E5L7_DUKE_QUIT_YOU",  DVPTR(E5L7_DUKE_QUIT_YOU), E5L7_DUKE_QUIT_YOU__STATIC },
 };

#ifdef DYNSOUNDREMAP_ENABLE

int32_t ALIEN_SWITCH1       = ALIEN_SWITCH1__STATIC;
int32_t BIGBANG             = BIGBANG__STATIC;
int32_t BONUS_SPEECH1       = BONUS_SPEECH1__STATIC;
int32_t BONUS_SPEECH2       = BONUS_SPEECH2__STATIC;
int32_t BONUS_SPEECH3       = BONUS_SPEECH3__STATIC;
int32_t BONUS_SPEECH4       = BONUS_SPEECH4__STATIC;
int32_t BONUSMUSIC          = BONUSMUSIC__STATIC;
int32_t BOS1_RECOG          = BOS1_RECOG__STATIC;
int32_t BOS1_WALK           = BOS1_WALK__STATIC;
int32_t BOS2_RECOG          = BOS2_RECOG__STATIC;
int32_t BOS3_RECOG          = BOS3_RECOG__STATIC;
int32_t BOS4_RECOG          = BOS4_RECOG__STATIC;
int32_t BOSS4_DEADSPEECH    = BOSS4_DEADSPEECH__STATIC;
int32_t BOSS4_FIRSTSEE      = BOSS4_FIRSTSEE__STATIC;
int32_t BOSSTALKTODUKE      = BOSSTALKTODUKE__STATIC;
int32_t CAPT_RECOG          = CAPT_RECOG__STATIC;
int32_t CAT_FIRE            = CAT_FIRE__STATIC;
int32_t CHAINGUN_FIRE       = CHAINGUN_FIRE__STATIC;
int32_t COMM_RECOG          = COMM_RECOG__STATIC;
int32_t DRON_RECOG          = DRON_RECOG__STATIC;
int32_t DUKE_CRACK          = DUKE_CRACK__STATIC;
int32_t DUKE_CRACK_FIRST    = DUKE_CRACK_FIRST__STATIC;
int32_t DUKE_CRACK2         = DUKE_CRACK2__STATIC;
int32_t DUKE_DRINKING       = DUKE_DRINKING__STATIC;
int32_t DUKE_GASP           = DUKE_GASP__STATIC;
int32_t DUKE_GET            = DUKE_GET__STATIC;
int32_t DUKE_GETWEAPON2     = DUKE_GETWEAPON2__STATIC;
int32_t DUKE_GETWEAPON6     = DUKE_GETWEAPON6__STATIC;
int32_t DUKE_GOTHEALTHATLOW = DUKE_GOTHEALTHATLOW__STATIC;
int32_t DUKE_GRUNT          = DUKE_GRUNT__STATIC;
int32_t DUKE_HARTBEAT       = DUKE_HARTBEAT__STATIC;
int32_t DUKE_JETPACK_IDLE   = DUKE_JETPACK_IDLE__STATIC;
int32_t DUKE_JETPACK_OFF    = DUKE_JETPACK_OFF__STATIC;
int32_t DUKE_JETPACK_ON     = DUKE_JETPACK_ON__STATIC;
int32_t DUKE_LAND           = DUKE_LAND__STATIC;
int32_t DUKE_LAND_HURT      = DUKE_LAND_HURT__STATIC;
int32_t DUKE_LONGTERM_PAIN  = DUKE_LONGTERM_PAIN__STATIC;
int32_t DUKE_ONWATER        = DUKE_ONWATER__STATIC;
int32_t DUKE_PISSRELIEF     = DUKE_PISSRELIEF__STATIC;
int32_t DUKE_SCREAM         = DUKE_SCREAM__STATIC;
int32_t DUKE_SEARCH         = DUKE_SEARCH__STATIC;
int32_t DUKE_SEARCH2        = DUKE_SEARCH2__STATIC;
int32_t DUKE_TAKEPILLS      = DUKE_TAKEPILLS__STATIC;
int32_t DUKE_UNDERWATER     = DUKE_UNDERWATER__STATIC;
int32_t DUKE_URINATE        = DUKE_URINATE__STATIC;
int32_t DUKE_USEMEDKIT      = DUKE_USEMEDKIT__STATIC;
int32_t DUKE_WALKINDUCTS    = DUKE_WALKINDUCTS__STATIC;
int32_t DUKETALKTOBOSS      = DUKETALKTOBOSS__STATIC;
int32_t EARTHQUAKE          = EARTHQUAKE__STATIC;
int32_t EJECT_CLIP          = EJECT_CLIP__STATIC;
int32_t ELEVATOR_OFF        = ELEVATOR_OFF__STATIC;
int32_t ELEVATOR_ON         = ELEVATOR_ON__STATIC;
int32_t END_OF_LEVEL_WARN   = END_OF_LEVEL_WARN__STATIC;
int32_t ENDSEQVOL2SND1      = ENDSEQVOL2SND1__STATIC;
int32_t ENDSEQVOL2SND2      = ENDSEQVOL2SND2__STATIC;
int32_t ENDSEQVOL2SND3      = ENDSEQVOL2SND3__STATIC;
int32_t ENDSEQVOL2SND4      = ENDSEQVOL2SND4__STATIC;
int32_t ENDSEQVOL2SND5      = ENDSEQVOL2SND5__STATIC;
int32_t ENDSEQVOL2SND6      = ENDSEQVOL2SND6__STATIC;
int32_t ENDSEQVOL2SND7      = ENDSEQVOL2SND7__STATIC;
int32_t ENDSEQVOL3SND2      = ENDSEQVOL3SND2__STATIC;
int32_t ENDSEQVOL3SND3      = ENDSEQVOL3SND3__STATIC;
int32_t ENDSEQVOL3SND4      = ENDSEQVOL3SND4__STATIC;
int32_t ENDSEQVOL3SND5      = ENDSEQVOL3SND5__STATIC;
int32_t ENDSEQVOL3SND6      = ENDSEQVOL3SND6__STATIC;
int32_t ENDSEQVOL3SND7      = ENDSEQVOL3SND7__STATIC;
int32_t ENDSEQVOL3SND8      = ENDSEQVOL3SND8__STATIC;
int32_t ENDSEQVOL3SND9      = ENDSEQVOL3SND9__STATIC;
int32_t EXITMENUSOUND       = EXITMENUSOUND__STATIC;
int32_t EXPANDERSHOOT       = EXPANDERSHOOT__STATIC;
int32_t FLUSH_TOILET        = FLUSH_TOILET__STATIC;
int32_t FLY_BY              = FLY_BY__STATIC;
int32_t GENERIC_AMBIENCE17  = GENERIC_AMBIENCE17__STATIC;
int32_t GLASS_BREAKING      = GLASS_BREAKING__STATIC;
int32_t GLASS_HEAVYBREAK    = GLASS_HEAVYBREAK__STATIC;
int32_t INSERT_CLIP         = INSERT_CLIP__STATIC;
int32_t INTRO4_1            = INTRO4_1__STATIC;
int32_t INTRO4_2            = INTRO4_2__STATIC;
int32_t INTRO4_3            = INTRO4_3__STATIC;
int32_t INTRO4_4            = INTRO4_4__STATIC;
int32_t INTRO4_5            = INTRO4_5__STATIC;
int32_t INTRO4_6            = INTRO4_6__STATIC;
int32_t INTRO4_B            = INTRO4_B__STATIC;
int32_t ITEM_SPLASH         = ITEM_SPLASH__STATIC;
int32_t JIBBED_ACTOR5       = JIBBED_ACTOR5__STATIC;
int32_t JIBBED_ACTOR6       = JIBBED_ACTOR6__STATIC;
int32_t KICK_HIT            = KICK_HIT__STATIC;
int32_t LASERTRIP_ARMING    = LASERTRIP_ARMING__STATIC;
int32_t LASERTRIP_EXPLODE   = LASERTRIP_EXPLODE__STATIC;
int32_t LASERTRIP_ONWALL    = LASERTRIP_ONWALL__STATIC;
int32_t LIGHTNING_SLAP      = LIGHTNING_SLAP__STATIC;
int32_t MONITOR_ACTIVE      = MONITOR_ACTIVE__STATIC;
int32_t NITEVISION_ONOFF    = NITEVISION_ONOFF__STATIC;
int32_t OCTA_RECOG          = OCTA_RECOG__STATIC;
int32_t PIG_RECOG           = PIG_RECOG__STATIC;
int32_t PIPEBOMB_BOUNCE     = PIPEBOMB_BOUNCE__STATIC;
int32_t PIPEBOMB_EXPLODE    = PIPEBOMB_EXPLODE__STATIC;
int32_t PISTOL_BODYHIT      = PISTOL_BODYHIT__STATIC;
int32_t PISTOL_FIRE         = PISTOL_FIRE__STATIC;
int32_t PISTOL_RICOCHET     = PISTOL_RICOCHET__STATIC;
int32_t POOLBALLHIT         = POOLBALLHIT__STATIC;
int32_t PRED_RECOG          = PRED_RECOG__STATIC;
int32_t RATTY               = RATTY__STATIC;
int32_t RECO_ATTACK         = RECO_ATTACK__STATIC;
int32_t RECO_PAIN           = RECO_PAIN__STATIC;
int32_t RECO_RECOG          = RECO_RECOG__STATIC;
int32_t RECO_ROAM           = RECO_ROAM__STATIC;
int32_t RIPHEADNECK         = RIPHEADNECK__STATIC;
int32_t RPG_EXPLODE         = RPG_EXPLODE__STATIC;
int32_t RPG_SHOOT           = RPG_SHOOT__STATIC;
int32_t SELECT_WEAPON       = SELECT_WEAPON__STATIC;
int32_t SHORT_CIRCUIT       = SHORT_CIRCUIT__STATIC;
int32_t SHOTGUN_COCK        = SHOTGUN_COCK__STATIC;
int32_t SHOTGUN_FIRE        = SHOTGUN_FIRE__STATIC;
int32_t SHRINKER_FIRE       = SHRINKER_FIRE__STATIC;
int32_t SHRINKER_HIT        = SHRINKER_HIT__STATIC;
int32_t SLIM_ATTACK         = SLIM_ATTACK__STATIC;
int32_t SLIM_DYING          = SLIM_DYING__STATIC;
int32_t SLIM_RECOG          = SLIM_RECOG__STATIC;
int32_t SLIM_ROAM           = SLIM_ROAM__STATIC;
int32_t SOMETHING_DRIPPING  = SOMETHING_DRIPPING__STATIC;
int32_t SOMETHINGFROZE      = SOMETHINGFROZE__STATIC;
int32_t SOMETHINGHITFORCE   = SOMETHINGHITFORCE__STATIC;
int32_t SQUISHED            = SQUISHED__STATIC;
int32_t SUBWAY              = SUBWAY__STATIC;
int32_t SWITCH_ON           = SWITCH_ON__STATIC;
int32_t TELEPORTER          = TELEPORTER__STATIC;
int32_t THUD                = THUD__STATIC;
int32_t THUNDER             = THUNDER__STATIC;
int32_t TURR_RECOG          = TURR_RECOG__STATIC;
int32_t VENT_BUST           = VENT_BUST__STATIC;
int32_t VOL4ENDSND1         = VOL4ENDSND1__STATIC;
int32_t VOL4ENDSND2         = VOL4ENDSND2__STATIC;
int32_t WAR_AMBIENCE2       = WAR_AMBIENCE2__STATIC;
int32_t WHIPYOURASS         = WHIPYOURASS__STATIC;
int32_t WIERDSHOT_FLY       = WIERDSHOT_FLY__STATIC;
int32_t WIND_AMBIENCE       = WIND_AMBIENCE__STATIC;
int32_t WIND_REPEAT         = WIND_REPEAT__STATIC;
int32_t FLAMETHROWER_INTRO  = FLAMETHROWER_INTRO__STATIC;
int32_t FLAMETHROWER_LOOP   = FLAMETHROWER_LOOP__STATIC;
int32_t FLAMETHROWER_END    = FLAMETHROWER_END__STATIC;
int32_t E5L7_DUKE_QUIT_YOU  = E5L7_DUKE_QUIT_YOU__STATIC;

static hashtable_t h_names = {512, NULL};

void G_ProcessDynamicSoundMapping(const char *szLabel, int32_t lValue)
{
    if ((unsigned)lValue >= MAXSOUNDS || !szLabel)
        return;

    int const i = hash_find(&h_names,szLabel);

    if (i>=0)
    {
        struct dynitem *di = &g_dynSoundList[i];
#ifdef DEBUGGINGAIDS
        if (g_scriptDebug && di->staticval != lValue)
            OSD_Printf("REMAP %s (%d) --> %d\n", di->str, di->staticval, lValue);
#endif
        *di->dynvalptr = lValue;
    }
}

void initsoundhashnames(void)
{
    hash_init(&h_names);

    for (int i=0; i < ARRAY_SSIZE(g_dynSoundList); i++)
        hash_add(&h_names, g_dynSoundList[i].str, i, 0);
}

void freesoundhashnames(void)
{
    hash_free(&h_names);
}
#endif

// This is run after all CON define's have been processed to set up the
// dynamic->static sound mapping.
void G_InitDynamicSounds(void)
{
    Bmemset(DynamicSoundMap, 0, sizeof(DynamicSoundMap));

    for (auto & i : g_dynSoundList)
#ifdef DYNSOUNDREMAP_ENABLE
        DynamicSoundMap[*(i.dynvalptr)] = i.staticval;
#else
        DynamicSoundMap[i.staticval] = i.staticval;
#endif

}
