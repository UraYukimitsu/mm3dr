extern "C" {
#include <3ds/types.h>
}
#include <string.h>
#include "game/common_data.h"
#include "rnd/item_effect.h"
#include "rnd/razor_sword.h"
#include "rnd/savefile.h"
#include "rnd/settings.h"
#ifdef ENABLE_DEBUG
#include "common/debug.h"
#endif
//#define DECLARE_EXTSAVEDATA

namespace rnd {
  extern "C" void SaveFile_Init() {
    game::SaveData& saveData = game::GetCommonData().save;
#ifdef ENABLE_DEBUG
    saveData.equipment.sword_shield.sword = game::SwordType::GildedSword;
    saveData.player.razor_sword_hp = 0x64;
    saveData.inventory.inventory_count_register.quiver_upgrade = game::Quiver::Quiver50;
    saveData.inventory.inventory_count_register.bomb_bag_upgrade = game::BombBag::BombBag40;
    saveData.inventory.inventory_count_register.wallet_upgrade = 2;
    saveData.inventory.inventory_count_register.stick_upgrades = 2;
    saveData.inventory.inventory_count_register.nut_upgrade = 2;
    saveData.player.rupee_count = 500;
    saveData.inventory.items[0] = game::ItemId::Ocarina;
    saveData.inventory.items[1] = game::ItemId::Arrow;
    saveData.inventory.items[2] = game::ItemId::FireArrow;
    saveData.inventory.items[3] = game::ItemId::IceArrow;
    saveData.inventory.items[4] = game::ItemId::LightArrow;
    saveData.inventory.items[6] = game::ItemId::Bomb;
    saveData.inventory.items[7] = game::ItemId::Bombchu;
    saveData.inventory.items[8] = game::ItemId::DekuStick;
    saveData.inventory.items[9] = game::ItemId::DekuNuts;
    saveData.inventory.items[10] = game::ItemId::MagicBean;
    saveData.inventory.items[12] = game::ItemId::PowderKeg;
    saveData.inventory.items[13] = game::ItemId::PictographBox;
    saveData.inventory.items[14] = game::ItemId::LensOfTruth;
    saveData.inventory.items[15] = game::ItemId::Hookshot;

    saveData.inventory.masks[5] = game::ItemId::DekuMask;
    saveData.inventory.masks[11] = game::ItemId::GoronMask;
    saveData.inventory.masks[17] = game::ItemId::ZoraMask;
    saveData.inventory.masks[23] = game::ItemId::FierceDeityMask;
    saveData.inventory.masks[19] = game::ItemId::GibdoMask;
    saveData.inventory.masks[8] = game::ItemId::BunnyHood;
    saveData.inventory.masks[20] = game::ItemId::GaroMask;

    saveData.inventory.woodfall_temple_keys = 8;
    saveData.inventory.snowhead_temple_keys = 8;
    saveData.inventory.great_bay_temple_keys = 8;
    saveData.inventory.stone_tower_temple_keys = 8;
    saveData.inventory.woodfall_dungeon_items.map = 1;
    saveData.inventory.woodfall_dungeon_items.compass = 1;
    saveData.inventory.woodfall_dungeon_items.boss_key = 1;
    saveData.inventory.snowhead_dungeon_items.map = 1;
    saveData.inventory.snowhead_dungeon_items.compass = 1;
    saveData.inventory.snowhead_dungeon_items.boss_key = 1;
    saveData.inventory.great_bay_dungeon_items.map = 1;
    saveData.inventory.great_bay_dungeon_items.compass = 1;
    saveData.inventory.great_bay_dungeon_items.boss_key = 1;
    saveData.inventory.stone_tower_dungeon_items.map = 1;
    saveData.inventory.stone_tower_dungeon_items.compass = 1;
    saveData.inventory.stone_tower_dungeon_items.boss_key = 1;
    saveData.player.magic_acquired = 1;  // Game does not check if value = 0, magic items still work
    saveData.player.magic_size_type = 2;
    saveData.player.magic = 96;
    saveData.player.magic_num_upgrades = 1;
    saveData.equipment.data[3].item_btns[0] = game::ItemId::DekuNuts;
    saveData.inventory.item_counts[6] = 50;   // Arrows
    saveData.inventory.item_counts[11] = 40;  // Bombs
    saveData.inventory.item_counts[12] = 40;  // Bombchus
    saveData.inventory.item_counts[14] = 30;  // Nuts
    saveData.inventory.item_counts[13] = 20;  // Sticks
    saveData.has_great_spin_0x02 = 2;         // Set great spin.

    saveData.player.owl_statue_flags.great_bay = 1;
    saveData.player.owl_statue_flags.zora_cape = 1;
    saveData.player.owl_statue_flags.snowhead = 1;
    saveData.player.owl_statue_flags.mountain_village = 1;
    saveData.player.owl_statue_flags.clock_town = 1;
    saveData.player.owl_statue_flags.milk_road = 1;
    saveData.player.owl_statue_flags.woodfall = 1;
    saveData.player.owl_statue_flags.southern_swamp = 1;
    saveData.player.owl_statue_flags.ikana_canyon = 1;
    saveData.player.owl_statue_flags.stone_tower = 1;

    saveData.inventory.collect_register.sonata_of_awakening = 1;
    saveData.inventory.collect_register.goron_lullaby = 1;
    saveData.inventory.collect_register.new_wave_bossa_nova = 1;
    saveData.inventory.collect_register.elegy_of_emptiness = 1;
    saveData.inventory.collect_register.eponas_song = 1;
    saveData.inventory.collect_register.song_of_soaring = 1;
    saveData.inventory.collect_register.song_of_time = 1;
    // saveData.inventory.collect_register.oath_to_order = 1;
    // saveData.inventory.collect_register.song_of_healing = 1;

    gSettingsContext.skipBombersMinigame = 1;
    gSettingsContext.freeScarecrow = 1;
    saveData.activate_dungeon_skip_portal_0xF0_for_all = 0xF0;

    SaveFile_FillOverWorldMapData();

#endif
    // TODO: Decomp event flags. Most likely in the large anonymous structs in the SaveData.
    u8 isNewFile = saveData.has_completed_intro;
    if (isNewFile == 0) {
      saveData.has_tatl = true;

      // Skips cutscenes with no item checks attached
      // Also does not skip location access cutscenes like woodfall temple rise
      SaveFile_SkipMinorCutscenes();
      // Game has shorter animations for some events that were viewed at least once
      SaveFile_SetFastAnimationFlags();

      // OOT equivalent of starting with certain warp songs
      SaveFile_SetStartingOwlStatues();
      SaveFile_SetComfortOptions();

      /*Currently starting with ocarina and song of time is default in MM rando.
        These two items allows for skipping the first three day cycle.
        Currently there is no known way to get termina field to load
        in properly without ocarina in inventory.                                */
      saveData.inventory.collect_register.song_of_time = 1;  // Part of starting quest items options
      gSettingsContext.startingOcarina = 1;

      SaveFile_SetStartingInventory();

      // These events replay after song of time
      saveData.ct_guard_allows_through_if_0x20 = 0x20;
      saveData.tatl_dialogue_snowhead_entry_0x08 = 0x08;
      saveData.pirate_leader_dialogue_0x20 = 0x20;
      saveData.temp_event_flag_bundle1.ct_deku_in_flower_if_present = 1;
      saveData.skip_tingle_intro_dialogue_0x01 = 0x01;

      saveData.player_form = game::act::Player::Form::Human;
      game::GiveItem(game::ItemId::BombersNotebook);
    }
  }

  void SaveFile_SkipMinorCutscenes() {
    game::SaveData& saveData = game::GetCommonData().save;
    saveData.has_completed_intro = 0x2B;
    saveData.skip_tatl_talking_0x04 = 0x04;

    // camera panning cutscenes
    saveData.camera_panning_event_flag_bundle.termina_field = 1;
    saveData.camera_panning_event_flag_bundle.graveyard = 1;
    saveData.camera_panning_event_flag_bundle.romani_ranch = 1;
    saveData.camera_panning_event_flag_bundle.gorman_track = 1;
    saveData.camera_panning_event_flag_bundle.mountain_village = 1;
    saveData.camera_panning_event_flag_bundle.goron_city = 1;
    saveData.camera_panning_event_flag_bundle.snowhead = 1;
    saveData.camera_panning_event_flag_bundle.southern_swamp = 1;
    saveData.camera_panning_event_flag_bundle.woodfall = 1;
    saveData.camera_panning_event_flag_bundle.deku_palace = 1;
    saveData.camera_panning_event_flag_bundle.great_bay_coast = 1;
    saveData.camera_panning_event_flag_bundle.pirates_fortress_interior = 1;
    saveData.camera_panning_event_flag_bundle.zora_domain = 1;
    saveData.camera_panning_event_flag_bundle.waterfall_rapids = 1;
    saveData.camera_panning_event_flag_bundle.ikana_canyon = 1;
    saveData.camera_panning_event_flag_bundle.stone_tower = 1;
    saveData.camera_panning_event_flag_bundle.stone_tower_inverted = 1;
    saveData.camera_panning_event_flag_bundle.east_clock_town = 1;
    saveData.camera_panning_event_flag_bundle.west_clock_town = 1;
    saveData.camera_panning_event_flag_bundle.north_clock_town = 1;
    saveData.camera_panning_event_flag_bundle.woodfall_temple = 1;
    saveData.camera_panning_event_flag_bundle.snowhead_temple_entry_room = 1;
    saveData.camera_panning_event_flag_bundle.stone_tower_temple = 1;
    saveData.camera_panning_event_flag_bundle.stone_tower_temple_inverted = 1;
    saveData.cut_scene_flag_bundle.deku_palace_throne_room_camera_pan = 1;
    saveData.road_to_woodfall_camera_pan_0x08 = 0x08;
    saveData.snowhead_temple_main_room_camera_pan_0x01 = 0x01;
    saveData.pirates_fortress_exterior_camera_pan_0x04 = 0x04;
    saveData.ikana_castle_camera_pan_0x08 = 0x80;

    // Tatl constant tatling skip
    saveData.cut_scene_flag_bundle.tatl_moon_tear_dialogue = 1;
    saveData.tatl_dialogue_flags2.go_south = 1;
    saveData.tatl_dialogue_flags1.go_north = 1;
    saveData.tatl_dialogue_flags1.go_west = 1;
    saveData.tatl_dialogue_flags1.go_east = 1;
    saveData.tatl_dialogue_flags1.go_to_skullkid = 1;
    saveData.woodfall_platform_tatl_dialogue_0x02 = 0x02;
    saveData.tatl_dialogue_inside_woodfall_temple_0x80 = 0x80;
    saveData.tatl_apology_dialogue_post_Odolwa_0x80 = 0x80;
    saveData.talt_dialogue_great_bay_temple.waterwheel_room_tatl_dialogue = 1;
    saveData.talt_dialogue_great_bay_temple.whirlpool_room_tatl_dialogue = 1;

    // tutorials
    saveData.cut_scene_flag_bundle.map_tutorial_by_tingle = 1;

    // Misc cutscenes
    saveData.meeting_happy_mask_salesman_0x01 = 0x01;
    saveData.skullkid_backstory_cutscene_0x10 = 0x10;
    saveData.cut_scene_flag_bundle.owl_statue_cut_scene = 1;
    saveData.dungeon_skip_portal_cutscene_0x3C_to_skip_all = 0x3C;
    saveData.event_flag_bundle.skip_swimming_to_great_bay_temple_cutscene = 1;

    // Needs to be greater than zero to skip first time song of time cutscene
    saveData.player.song_of_time_counter = 1;
  }
  void SaveFile_SetFastAnimationFlags() {
    game::SaveData& saveData = game::GetCommonData().save;
    // Masks
    saveData.set_fast_mask_animations.has_worn_deku_mask_once = 1;
    saveData.set_fast_mask_animations.has_worn_goron_mask_once = 1;
    saveData.set_fast_mask_animations.has_worn_zora_mask_once = 1;
    saveData.set_fast_mask_animations.has_worn_deity_mask_once = 1;
    // Dungeons
    saveData.set_fast_animation_flags.woodfall_temple_opened_at_least_once = 1;
    saveData.set_fast_animation_flags.snowhead_temple_opened_at_least_once = 1;
    saveData.set_fast_animation_flags.greatbay_temple_opened_at_least_once = 1;
    // Misc
    saveData.set_fast_animation_flags.deku_flown_in_at_least_once = 1;
  }
  void SaveFile_SetStartingOwlStatues() {
    game::SaveData& saveData = game::GetCommonData().save;
    // Walkable statues, could have an option to bundle this subgroup
    if (gSettingsContext.startingOwlStatues.clock_town)
      saveData.player.owl_statue_flags.clock_town = 1;
    if (gSettingsContext.startingOwlStatues.milk_road)
      saveData.player.owl_statue_flags.milk_road = 1;
    if (gSettingsContext.startingOwlStatues.southern_swamp)
      saveData.player.owl_statue_flags.southern_swamp = 1;
    // These give early location access
    if (gSettingsContext.startingOwlStatues.great_bay)
      saveData.player.owl_statue_flags.great_bay = 1;
    if (gSettingsContext.startingOwlStatues.zora_cape)
      saveData.player.owl_statue_flags.zora_cape = 1;
    if (gSettingsContext.startingOwlStatues.snowhead)
      saveData.player.owl_statue_flags.snowhead = 1;
    if (gSettingsContext.startingOwlStatues.mountain_village)
      saveData.player.owl_statue_flags.mountain_village = 1;
    if (gSettingsContext.startingOwlStatues.woodfall)
      saveData.player.owl_statue_flags.woodfall = 1;
    if (gSettingsContext.startingOwlStatues.ikana_canyon)
      saveData.player.owl_statue_flags.ikana_canyon = 1;
    if (gSettingsContext.startingOwlStatues.stone_tower)
      saveData.player.owl_statue_flags.stone_tower = 1;
  }
  void SaveFile_SetComfortOptions() {
    game::SaveData& saveData = game::GetCommonData().save;
    if (gSettingsContext.skipBombersMinigame) {
      // Not sure if bombers code is used elsewhere in the game's code
      saveData.bomberscode[0] = 0x01;
      saveData.bomberscode[1] = 0x01;
      saveData.bomberscode[2] = 0x01;
      saveData.bomberscode[3] = 0x01;
      saveData.bomberscode[4] = 0x01;
      saveData.temp_event_flag_bundle1.bomber_open_hideout =
          1;  // Currently gets reset by Song of time
    }
    // Game uses an inventory check to determine whether you can
    // buy beans or powder kegs
    if (gSettingsContext.skipBeansTest) {
      // currently this will disable the free bean check
      // Instead bean daddy sells one bean for 10 rupees
      // saveData.inventory.items[10] = game::ItemId::MagicBean;
    }
    if (gSettingsContext.skipPowerKegTest) {
      // currently this will disable the PowerKegTest item check
      // Instead big goron sells one powder keg for 20 rupees
      // saveData.inventory.items[12] = game::ItemId::PowderKeg;
    }

    if (gSettingsContext.freeScarecrow) {
      // Currently sets song to the ingame default: LLLLLLLL
      saveData.inventory.collect_register.scarecrows_song_icon = 1;
      // both flags below get reset to 0 by song of time
      saveData.removes_scarecrow_from_shop_0x08 = 0x08;
      saveData.activate_scarecrow_song_0x01 = 0x01;
    }
  }
  void SaveFile_FillOverWorldMapData() {
    game::SaveData& saveData = game::GetCommonData().save;
    saveData.overworld_map_get_flags_0x3F_for_all = 0x3F;
    // setting individual maps is possible if necessary, the game just ||'s the map data in.
    // Currently sets data for all maps
    saveData.overworld_map_data[0] = 0x01;
    saveData.overworld_map_data[1] = 0x34;
    saveData.overworld_map_data[2] = 0xBF;
    saveData.overworld_map_data[3] = 0x72;
    saveData.overworld_map_data[4] = 0xBD;
    saveData.overworld_map_data[5] = 0xFB;
    saveData.overworld_map_data[6] = 0xBD;
    saveData.overworld_map_data[7] = 0x7B;
    saveData.overworld_map_data[8] = 0x6F;
    saveData.overworld_map_data[9] = 0xFD;
    saveData.overworld_map_data[10] = 0xFF;
    saveData.overworld_map_data[11] = 0x7F;
    saveData.overworld_map_data[12] = 0x0B;
    saveData.overworld_map_data[13] = 0xFD;
    saveData.overworld_map_data[14] = 0x07;
  }
  // Resolve the item ID for the starting bottle
  static void SaveFile_GiveStartingBottle(StartingBottleSetting startingBottle, u8 bottleSlot) {
    game::SaveData& saveData = game::GetCommonData().save;
    if (startingBottle > StartingBottleSetting::STARTINGBOTTLE_NONE) {
      saveData.inventory.bottles[bottleSlot] = (game::ItemId)startingBottle;
    }
  }

  u8 SaveFile_GetRemainsCount(void) {
    game::InventoryData& inventoryData = game::GetCommonData().save.inventory;
    u8 count = 0;

    count += inventoryData.collect_register.odolwas_remains ? 1 : 0;
    count += inventoryData.collect_register.gohts_remains ? 1 : 0;
    count += inventoryData.collect_register.gyorgs_remains ? 1 : 0;
    count += inventoryData.collect_register.twinmolds_remains ? 1 : 0;

    return count;
  }

  void SaveFile_SetStartingInventory(void) {
    game::InventoryData& inventoryData = game::GetCommonData().save.inventory;
    game::PlayerData& playerData = game::GetCommonData().save.player;
    game::EquipmentData& equipmentData = game::GetCommonData().save.equipment;
    game::SaveData& saveData = game::GetCommonData().save;
    // give maps and compasses
    if (gSettingsContext.mapsAndCompasses ==
        (u8)MapsAndCompassesSetting::MAPSANDCOMPASSES_ANY_DUNGEON) {
      inventoryData.woodfall_dungeon_items.map = 1;
      inventoryData.woodfall_dungeon_items.compass = 1;
      inventoryData.snowhead_dungeon_items.map = 1;
      inventoryData.snowhead_dungeon_items.compass = 1;
      inventoryData.great_bay_dungeon_items.map = 1;
      inventoryData.great_bay_dungeon_items.compass = 1;
      inventoryData.stone_tower_dungeon_items.map = 1;
      inventoryData.stone_tower_dungeon_items.compass = 1;
    }
    if (gSettingsContext.mapsAndCompasses ==
        (u8)MapsAndCompassesSetting::MAPSANDCOMPASSES_OVERWORLD) {
      SaveFile_FillOverWorldMapData();
    }

    // give small keys
    if (gSettingsContext.keysanity == (u8)KeysanitySetting::KEYSANITY_START_WITH) {
      inventoryData.woodfall_temple_keys = 1;
      inventoryData.snowhead_temple_keys = 3;
      inventoryData.great_bay_temple_keys = 3;
      inventoryData.stone_tower_temple_keys = 4;
      // give starting spirit keys for vanilla key locations
    }

    // give boss keys
    if (gSettingsContext.bossKeysanity == (u8)BossKeysanitySetting::BOSSKEYSANITY_START_WITH) {
      inventoryData.woodfall_dungeon_items.boss_key = 1;
      inventoryData.snowhead_dungeon_items.boss_key = 1;
      inventoryData.great_bay_dungeon_items.boss_key = 1;
      inventoryData.stone_tower_dungeon_items.boss_key = 1;
    }

    // starting Nuts and Sticks
    if (gSettingsContext.startingConsumables) {
      inventoryData.items[9] = game::ItemId::DekuNuts;
      inventoryData.items[10] = game::ItemId::DekuStick;
      inventoryData.inventory_count_register.nut_upgrade = 0;
      inventoryData.inventory_count_register.stick_upgrades = 0;
    }

    // main inventory
    if (gSettingsContext.startingStickCapacity > 0) {
      inventoryData.items[10] = game::ItemId::DekuStick;
      inventoryData.inventory_count_register.stick_upgrades = 0;
      inventoryData.item_counts[13] = (gSettingsContext.startingStickCapacity + 1) * 10;
    }

    if (gSettingsContext.startingNutCapacity > 0) {
      inventoryData.items[9] = game::ItemId::DekuNuts;
      inventoryData.inventory_count_register.nut_upgrade = 0;
      inventoryData.item_counts[14] = (gSettingsContext.startingNutCapacity + 1) * 10;
    }

    if (gSettingsContext.startingBombBag > 0) {
      inventoryData.inventory_count_register.bomb_bag_upgrade = game::BombBag::BombBag20;
      inventoryData.items[6] = game::ItemId::Bomb;
      inventoryData.item_counts[11] = (gSettingsContext.startingBombBag + 1) * 10;
    }

    if (gSettingsContext.startingBombchus > 0) {
      inventoryData.inventory_count_register.bomb_bag_upgrade = game::BombBag::BombBag20;
      inventoryData.items[7] = game::ItemId::Bombchu;
      inventoryData.item_counts[12] = 20;
    }

    if (gSettingsContext.startingHerosBow > 0) {
      inventoryData.items[1] = game::ItemId::Arrow;
      inventoryData.item_counts[6] = (gSettingsContext.startingHerosBow + 2) * 10;
    }

    if (gSettingsContext.startingFireArrows) {
      inventoryData.items[2] = game::ItemId::FireArrow;
    }

    if (gSettingsContext.startingIceArrows) {
      inventoryData.items[3] = game::ItemId::IceArrow;
    }

    if (gSettingsContext.startingLightArrows) {
      inventoryData.items[4] = game::ItemId::LightArrow;
    }

    if (gSettingsContext.startingLensOfTruth) {
      inventoryData.items[14] = game::ItemId::LensOfTruth;
    }

    if (gSettingsContext.startingMagicBean) {
      inventoryData.items[10] = game::ItemId::MagicBean;
      inventoryData.item_counts[15] = 10;
    }

    if (gSettingsContext.startingHookshot > 0) {
      inventoryData.items[15] = game::ItemId::Hookshot;
    }

    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle1, 0);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle2, 1);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle3, 2);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle4, 3);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle5, 4);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle6, 5);
    SaveFile_GiveStartingBottle((rnd::StartingBottleSetting)gSettingsContext.startingBottle7, 6);

    if (gSettingsContext.startingOcarina > 0) {
      inventoryData.items[0] = game::ItemId::Ocarina;
    }

    if (gSettingsContext.startingGildedSword == (u8)StartingSwordSetting::STARTINGSWORD_GILDED) {
      equipmentData.sword_shield.sword = game::SwordType::GildedSword;
    }
    if (gSettingsContext.startingRazorSword == (u8)StartingSwordSetting::STARTINGSWORD_RAZOR) {
      playerData.razor_sword_hp = RS_SetDurability();
      equipmentData.sword_shield.sword = game::SwordType::RazorSword;
    }

    if (gSettingsContext.startingMagicMeter == 1) {
      equipmentData.data[3].item_btns[0] = game::ItemId::DekuNuts;
      playerData.magic_size_type = 0;
      // playerData.magic_max_2 = 0;
      playerData.magic_num_upgrades = 0;
      playerData.magic_acquired = 1;
      playerData.magic = 0x30;
    } else if (gSettingsContext.startingMagicMeter == 2) {
      playerData.magic_size_type = 0;
      // playerData.magic_max_2 = 1;
      playerData.magic_num_upgrades = 1;
      playerData.magic_acquired = 1;
      playerData.magic = 0x60;
      equipmentData.data[3].item_btns[0] = game::ItemId::DekuNuts;
    }
    if (gSettingsContext.startingDoubleDefense) {
      game::CommonData& cdata = game::GetCommonData();
      ItemEffect_GiveDefense(&cdata, 0, 0);
    }

#ifdef ENABLE_DEBUG
    playerData.health_max = 16 << 4;
    playerData.health_current = 16 << 4;
#else
    if (SaveFile_IsValidSettingsHealth()) {
      playerData.health_max = gSettingsContext.startingHealth << 4;
      playerData.health_current = gSettingsContext.startingHealth << 4;
    } else {
      playerData.health_max = 3 << 4;
      playerData.health_current = 3 << 4;
    }

#endif

    /*TODO - All these need to be broken up since we're not dealing with bitfields.
    // Quest items belong in the iventory array so we'll have to adjust which items we start with.
    // Use enums like everything else.
    gSaveContext.questItems |= gSettingsContext.startingQuestItems;
    gSaveContext.questItems |= gSettingsContext.startingDungeonReward;
    gSaveContext.equipment |= gSettingsContext.startingEquipment;
    gSaveContext.upgrades |= gSettingsContext.startingUpgrades;
*/
    // max rupees
    if (gSettingsContext.startingMaxRupees) {
      u8 wallet = inventoryData.inventory_count_register.wallet_upgrade;
      if (wallet == 0) {
        playerData.rupee_count = 99;
      } else if (wallet == 1) {
        playerData.rupee_count = 200;
      } else if (wallet == 2) {
        playerData.rupee_count = 500;
      } else {
        playerData.rupee_count = 999;
      }
    }

    // TODO: Starting stray fairies - need to update flags for which ones are acquired or not.
    if (gSettingsContext.startingSpinSettting == (u8)StartingSpinSetting::STARTINGSPIN_GREAT) {
      saveData.has_great_spin_0x02 = 2;
    }
  }

  void SaveFile_ResetItemSlotsIfMatchesID(u8 itemSlot) {
    game::SaveData& saveData = game::GetCommonData().save;
    // Remove the slot from child/adult grids
    for (u32 i = 0; i < 0x18; ++i) {
      if (saveData.inventory.items[i] == (game::ItemId)itemSlot) {
        saveData.inventory.items[i] = game::ItemId::None;
      }
    }
  }

  bool SaveFile_IsValidSettingsHealth() {
    if (gSettingsContext.startingHealth <= 0) {
      return false;
    }
    return true;
  }

}  // namespace rnd
