#include "aimbot.hpp"

#include "player_info.hpp"

#include "../gui/config.hpp"

#include "../client.hpp"
#include "../math.hpp"
#include "../memory.hpp"
#include <cstdint>
#include <unistd.h>

namespace buttons {
constexpr std::ptrdiff_t attack = 0x184E8F0;
constexpr std::ptrdiff_t attack2 = 0x184E980;
constexpr std::ptrdiff_t back = 0x184EBC0;
constexpr std::ptrdiff_t duck = 0x184EE90;
constexpr std::ptrdiff_t forward = 0x184EB30;
constexpr std::ptrdiff_t jump = 0x184EE00;
constexpr std::ptrdiff_t left = 0x184EC50;
constexpr std::ptrdiff_t lookatweapon = 0x1A75170;
constexpr std::ptrdiff_t reload = 0x184E860;
constexpr std::ptrdiff_t right = 0x184ECE0;
constexpr std::ptrdiff_t showscores = 0x1A75050;
constexpr std::ptrdiff_t sprint = 0x184E7D0;
constexpr std::ptrdiff_t turnleft = 0x184EA10;
constexpr std::ptrdiff_t turnright = 0x184EAA0;
constexpr std::ptrdiff_t use = 0x184ED70;
constexpr std::ptrdiff_t zoom = 0x1A750E0;
} // namespace buttons

namespace C_BaseEntity {
constexpr std::ptrdiff_t m_CBodyComponent = 0x38; // CBodyComponent*
constexpr std::ptrdiff_t m_NetworkTransmitComponent =
    0x40;                                          // CNetworkTransmitComponent
constexpr std::ptrdiff_t m_nLastThinkTick = 0x320; // GameTick_t
constexpr std::ptrdiff_t m_pGameSceneNode = 0x328; // CGameSceneNode*
constexpr std::ptrdiff_t m_pRenderComponent = 0x330; // CRenderComponent*
constexpr std::ptrdiff_t m_pCollision = 0x338;       // CCollisionProperty*
constexpr std::ptrdiff_t m_iMaxHealth = 0x340;       // int32
constexpr std::ptrdiff_t m_iHealth = 0x344;          // int32
constexpr std::ptrdiff_t m_lifeState = 0x348;        // uint8
constexpr std::ptrdiff_t m_bTakesDamage = 0x349;     // bool
constexpr std::ptrdiff_t m_nTakeDamageFlags = 0x350; // TakeDamageFlags_t
constexpr std::ptrdiff_t m_nPlatformType = 0x358;    // EntityPlatformTypes_t
constexpr std::ptrdiff_t m_ubInterpolationFrame = 0x359; // uint8
constexpr std::ptrdiff_t m_hSceneObjectController =
    0x35C; // CHandle<C_BaseEntity>
constexpr std::ptrdiff_t m_nNoInterpolationTick = 0x360;           // int32
constexpr std::ptrdiff_t m_nVisibilityNoInterpolationTick = 0x364; // int32
constexpr std::ptrdiff_t m_flProxyRandomValue = 0x368;             // float32
constexpr std::ptrdiff_t m_iEFlags = 0x36C;                        // int32
constexpr std::ptrdiff_t m_nWaterType = 0x370;                     // uint8
constexpr std::ptrdiff_t m_bInterpolateEvenWithNoModel = 0x371;    // bool
constexpr std::ptrdiff_t m_bPredictionEligible = 0x372;            // bool
constexpr std::ptrdiff_t m_bApplyLayerMatchIDToModel = 0x373;      // bool
constexpr std::ptrdiff_t m_tokLayerMatchID = 0x374;      // CUtlStringToken
constexpr std::ptrdiff_t m_nSubclassID = 0x378;          // CUtlStringToken
constexpr std::ptrdiff_t m_nSimulationTick = 0x388;      // int32
constexpr std::ptrdiff_t m_iCurrentThinkContext = 0x38C; // int32
constexpr std::ptrdiff_t m_aThinkFunctions = 0x390; // CUtlVector<thinkfunc_t>
constexpr std::ptrdiff_t m_bDisabledContextThinks = 0x3A8;       // bool
constexpr std::ptrdiff_t m_flAnimTime = 0x3AC;                   // float32
constexpr std::ptrdiff_t m_flSimulationTime = 0x3B0;             // float32
constexpr std::ptrdiff_t m_nSceneObjectOverrideFlags = 0x3B4;    // uint8
constexpr std::ptrdiff_t m_bHasSuccessfullyInterpolated = 0x3B5; // bool
constexpr std::ptrdiff_t m_bHasAddedVarsToInterpolation = 0x3B6; // bool
constexpr std::ptrdiff_t m_bRenderEvenWhenNotSuccessfullyInterpolated =
    0x3B7;                                                        // bool
constexpr std::ptrdiff_t m_nInterpolationLatchDirtyFlags = 0x3B8; // int32[2]
constexpr std::ptrdiff_t m_ListEntry = 0x3C0;                     // uint16[11]
constexpr std::ptrdiff_t m_flCreateTime = 0x3D8;                  // GameTime_t
constexpr std::ptrdiff_t m_flSpeed = 0x3DC;                       // float32
constexpr std::ptrdiff_t m_EntClientFlags = 0x3E0;                // uint16
constexpr std::ptrdiff_t m_bClientSideRagdoll = 0x3E2;            // bool
constexpr std::ptrdiff_t m_iTeamNum = 0x3E3;                      // uint8
constexpr std::ptrdiff_t m_spawnflags = 0x3E4;                    // uint32
constexpr std::ptrdiff_t m_nNextThinkTick = 0x3E8;                // GameTick_t
constexpr std::ptrdiff_t m_fFlags = 0x3EC;                        // uint32
constexpr std::ptrdiff_t m_vecAbsVelocity = 0x3F0;                // Vector
constexpr std::ptrdiff_t m_vecVelocity = 0x400;        // CNetworkVelocityVector
constexpr std::ptrdiff_t m_vecBaseVelocity = 0x430;    // Vector
constexpr std::ptrdiff_t m_hEffectEntity = 0x43C;      // CHandle<C_BaseEntity>
constexpr std::ptrdiff_t m_hOwnerEntity = 0x440;       // CHandle<C_BaseEntity>
constexpr std::ptrdiff_t m_MoveCollide = 0x444;        // MoveCollide_t
constexpr std::ptrdiff_t m_MoveType = 0x445;           // MoveType_t
constexpr std::ptrdiff_t m_nActualMoveType = 0x446;    // MoveType_t
constexpr std::ptrdiff_t m_flWaterLevel = 0x448;       // float32
constexpr std::ptrdiff_t m_fEffects = 0x44C;           // uint32
constexpr std::ptrdiff_t m_hGroundEntity = 0x450;      // CHandle<C_BaseEntity>
constexpr std::ptrdiff_t m_nGroundBodyIndex = 0x454;   // int32
constexpr std::ptrdiff_t m_flFriction = 0x458;         // float32
constexpr std::ptrdiff_t m_flElasticity = 0x45C;       // float32
constexpr std::ptrdiff_t m_flGravityScale = 0x460;     // float32
constexpr std::ptrdiff_t m_flTimeScale = 0x464;        // float32
constexpr std::ptrdiff_t m_bAnimatedEveryTick = 0x468; // bool
constexpr std::ptrdiff_t m_flNavIgnoreUntilTime = 0x46C;  // GameTime_t
constexpr std::ptrdiff_t m_hThink = 0x470;                // uint16
constexpr std::ptrdiff_t m_fBBoxVisFlags = 0x480;         // uint8
constexpr std::ptrdiff_t m_bPredictable = 0x481;          // bool
constexpr std::ptrdiff_t m_bRenderWithViewModels = 0x482; // bool
constexpr std::ptrdiff_t m_nSplitUserPlayerPredictionSlot =
    0x484;                                                   // CSplitScreenSlot
constexpr std::ptrdiff_t m_nFirstPredictableCommand = 0x488; // int32
constexpr std::ptrdiff_t m_nLastPredictableCommand = 0x48C;  // int32
constexpr std::ptrdiff_t m_hOldMoveParent = 0x490; // CHandle<C_BaseEntity>
constexpr std::ptrdiff_t m_Particles = 0x498;      // CParticleProperty
constexpr std::ptrdiff_t m_vecPredictedScriptFloats =
    0x4C0; // CUtlVector<float32>
constexpr std::ptrdiff_t m_vecPredictedScriptFloatIDs =
    0x4D8;                                                 // CUtlVector<int32>
constexpr std::ptrdiff_t m_nNextScriptVarRecordID = 0x508; // int32
constexpr std::ptrdiff_t m_vecAngVelocity = 0x518;         // QAngle
constexpr std::ptrdiff_t m_DataChangeEventRef = 0x524;     // int32
constexpr std::ptrdiff_t m_dependencies = 0x528;  // CUtlVector<CEntityHandle>
constexpr std::ptrdiff_t m_nCreationTick = 0x540; // int32
constexpr std::ptrdiff_t m_bAnimTimeChanged = 0x54D;       // bool
constexpr std::ptrdiff_t m_bSimulationTimeChanged = 0x54E; // bool
constexpr std::ptrdiff_t m_sUniqueHammerID = 0x558;        // CUtlString
constexpr std::ptrdiff_t m_nBloodType = 0x560;             // BloodType
} // namespace C_BaseEntity

void aimbot(pid_t game_pid, Display *aim_display, uintptr_t client_address) {
  for (unsigned long i = 0; i < 64; ++i) {
    //    if (!config.aim.master) break;

    PlayerInfo::Player player = PlayerInfo::get_player(i);
    PlayerInfo::Player plocal = PlayerInfo::get_local_player();

    if (player.index == plocal.index)
      continue;
    if (config.esp.ignore_team == true && player.team == plocal.team)
      continue;
    if (player.health <= 0)
      continue;

    float _out[2];
    if (!world_to_screen(game_pid, player.bone_matrix[6], _out))
      ;

    if (Aimbot::index != -1 &&
            PlayerInfo::get_player(Aimbot::index).health <= 0 ||
        (config.aim.spotted == true &&
         PlayerInfo::get_player(Aimbot::index).spotted == false)) {
      Aimbot::index = -1;
      PlayerInfo::l_players[Aimbot::index].fov_distance = 999999;
    }

    if (config.aim.spotted == true && player.spotted == false)
      continue;

    Euler plocal_angles;
    Memory::read(game_pid, Client::view_angles, &plocal_angles,
                 sizeof(float[3]));
    Euler plocal_angles_final = plocal_angles;

    // TMP
    uint32_t fFlag;
    Memory::read(game_pid, PlayerInfo::ptr_local_player + C_BaseEntity::m_fFlags, &fFlag,
                 sizeof(uint32_t));
    std::cout << fFlag << " fflag" << std::endl;

    uint32_t fHealth;
    Memory::read(game_pid,PlayerInfo::ptr_local_player + C_BaseEntity::m_iHealth, &fHealth, sizeof(uint32_t));
    std::cout << fHealth << " health" << std::endl;

    std::vector tmp = Memory::read_bytes(game_pid,PlayerInfo::local_player_controller_address + C_BaseEntity::m_iHealth, 8);
    
    const uint32_t STANDING = 65665;
    const uint32_t CROUCHING = 65667;

    uint32_t csgoInput = 27742800;
    int dwForceJump = 0x184EE00;    
    uint32_t PLUS_JUMP = 65537;
    uint32_t MINUS_JUMP = 256;

    if (PlayerInfo::get_local_player().on_ground) {
      std::cout << "standing!" << std::endl;

      uintptr_t client = Memory::module_base_address(game_pid, "client.so");

      std::cout << client << " client" << std::endl;

      std::cout << plocal.health << " heal" << std::endl;
      
      Memory::write(game_pid, client + csgoInput + buttons::jump, &PLUS_JUMP, sizeof(PLUS_JUMP));

      
      usleep(1000);
      Memory::write(game_pid, client + csgoInput + buttons::jump, &MINUS_JUMP, sizeof(MINUS_JUMP));
    } else {
      std::cout << "not standing..." << std::endl;
    }

    // ENDTMP

    Vector3 delta_location = {
        float(plocal.location.x - player.bone_matrix[6].x),
        float(plocal.location.y - player.bone_matrix[6].y),
        float(plocal.location.z + plocal.height - player.bone_matrix[6].z)};

    float hyp = sqrt(delta_location.x * delta_location.x +
                     delta_location.y * delta_location.y);

    plocal_angles_final.pitch = atan(delta_location.z / hyp) * radpi;
    plocal_angles_final.yaw = atan(delta_location.y / delta_location.x) * radpi;

    float distance = distance_3d(plocal.location, player.bone_matrix[6]);

    float fov = sqrt(powf(sin((plocal_angles.pitch - plocal_angles_final.pitch +
                               plocal.aim_punch.pitch * 2) *
                              pideg) *
                              180,
                          2.0) +
                     powf(sin((plocal_angles.yaw - plocal_angles_final.yaw +
                               plocal.aim_punch.yaw * 2) *
                              pideg) *
                              180,
                          2.0));

    if (Aimbot::index == i) {

      PlayerInfo::l_players[Aimbot::index].fov_distance = fov;

      if (delta_location.x >= 0.0f) {
        plocal_angles_final.yaw += 180.0f;
      }

      if (fov > config.aim.fov &&
          !Xutil::key_down(aim_display, config.aim.key)) {
        PlayerInfo::l_players[Aimbot::index].fov_distance = 999999;
        Aimbot::index = -1;
        continue;
      }

      while (plocal_angles_final.pitch > 89)
        plocal_angles_final.pitch -= 180;

      while (plocal_angles_final.pitch < -89)
        plocal_angles_final.pitch += 180;

      if (isNaN(plocal_angles_final.pitch))
        plocal_angles_final.pitch = 0;

      if (isNaN(plocal_angles_final.yaw))
        plocal_angles_final.yaw = 0;

      if (config.aim.recoil) {
        plocal_angles_final.pitch -= (plocal.aim_punch.pitch * 2);
        plocal_angles_final.yaw -= (plocal.aim_punch.yaw * 2);
      }
    }

    if (Aimbot::index == i && Xutil::key_down(aim_display, config.aim.key)) {
      std::cout << "aim_bot" << std::endl;
      Memory::write(game_pid, Client::view_angles, &plocal_angles_final,
      sizeof(float[2]));

      char a = 0b0;
      Memory::read(game_pid, Client::force_attack, &a, sizeof(char));

      // if (config.aim.auto_shoot) {
      a = a | (1 << 0);
      //      }

      //	Memory::write(game_pid, Client::force_attack, &a, sizeof(char));

    } else {
      if (fov <= config.aim.fov &&
          fov < PlayerInfo::get_player(Aimbot::index).fov_distance) {
        Aimbot::index = i;
        PlayerInfo::l_players[Aimbot::index].fov_distance = fov;
      }
      std::cout << "aimbot hella fucked up" << std::endl;
    }
  }
}
