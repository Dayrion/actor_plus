/*
	actor+

		Include started at 19/01/18.
		-Dayrion
		Public version - beta v2.0.00
*/


#if defined _actor_plus_included
	#endinput
#else
	#define _actor_plus_included
#endif

#if !defined _samp_included
	#error "<actor+> a_samp is not included."
#endif

#if defined AP_DEBUG_ENABLED
	#define APD(%0) printf("<actor+> "%0)
#else
	#define APD(%0);
#endif

// =====================================================================================

#if defined _streamer_included
	#if !defined GetDynamicActorAnimation
		#warning "<actor+> Streamer version is not up to date. actor+ won't use it"
		#define USING_STREAMER (0)
	#else
		#define USING_STREAMER (1)
		#if defined AP_DEBUG_ENABLED
			#warning "<actor+> using streamer"
		#endif
	#endif
#else
	#define USING_STREAMER (0)
#endif

// =====================================================================================

#if defined _inc_y_iterate
	#define USING_Y_ITERATE (1)
	#if defined AP_DEBUG_ENABLED
		#warning "<actor+> using y_iterate"
	#endif
#else
	#define USING_Y_ITERATE (0)
#endif

// =====================================================================================

#if defined YSI_timer
	#define USING_Y_TIMERS (1)
	#if defined AP_DEBUG_ENABLED
		#warning "<actor+> using y_timers"
	#endif
#else
	#define USING_Y_TIMERS (0)
#endif

// =====================================================================================

#if defined PAWNRAKNET_INC_
	#define USING_PAWN_RAKNET (1)
	#if defined AP_DEBUG_ENABLED
		#warning "<actor+> using y_timers"
	#endif
#else
	#define USING_PAWN_RAKNET (0)
#endif


// =====================================================================================

#define S->%1(%0) 	stock %1(%0)
#define actor_plus_version 0x20000b

// =====================================================================================

#if !defined GetDistanceBetween2Points
	#define GetDistanceBetween2Points(%0,%1,%2,%3,%4,%5) VectorSize(%0-%3, %1-%4, %2-%5)
#endif

#if !defined strcpy
	#define strcpy(%0,%1) strcat((%0[0] = EOS, %0), %1)
#endif

#if !defined isnull
	#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

// =====================================================================================

// #define DONT_DETECT_OPTA can be defined if you won't detect use any timer for OnPlayerTargetActor(playerid, actorid, weaponid);

enum _:E_TYPE_SEARCH(<<= 1)
{
	SEARCH_TYPE_DYNAMIC = 1,
	SEARCH_TYPE_STATIC,
	SEARCH_TYPE_ALL = SEARCH_TYPE_DYNAMIC | SEARCH_TYPE_STATIC
};

#define MULTIPLE_TARGET_FOUND 	(0xFFFF01)
#define DEFAULT_ACTOR_VALUE 	(0x8FFFFFFF)

#if !defined DONT_DETECT_OPTA
	#define DEFAULT_CHECKING_TIME 	(200)
#endif

#define DYNAMIC_CATEGORY				(1)
#define STATIC_CATEGORY					(0)
#define ALL_VALUES_INCLUDED				(-1)
#define DEFAULT_ACTOR_REPLACEMENT 		(300)
#define MAX_ANIMATION_LIBRARY_LENGTH	(12)
#define MAX_ANIMATION_NAME_LENGTH		(30)

#if !defined DEFAULT_ACTOR_DRAW_DISTANCE
	#define DEFAULT_ACTOR_DRAW_DISTANCE (13.0)
#endif

#if !defined MAX_ACTOR_LABEL_LENGTH
	#define MAX_ACTOR_LABEL_LENGTH (60)
#endif

#if !defined DEFAULT_ACTOR_COLOR
	#define DEFAULT_ACTOR_COLOR (0xFFFFFFFF)
#endif

// =====================================================================================

#if defined OnPlayerShotActor
	forward OnPlayerShotActor(playerid, actorid, weaponid, bool:IsDynamicActor);
#endif

#if defined OnPlayerTargetActor
	forward OnPlayerTargetActor(playerid, actorid, weaponid);
#endif

#if defined OnPlayerMakeDamageToActor
	forward OnPlayerMakeDamageToActor(playerid, damaged_actorid, Float:amount, weaponid, bodypart, bool:IsDynamicActor, bool:death);
#endif

#if defined OnActorDeath
	forward OnActorDeath(actorid, killerid, reason, bool:IsDynamicActor);
#endif

#if defined OnActorSpawn
	forward OnActorSpawn(actorid, bool:IsDynamicActor);
#endif

// =====================================================================================

enum E_ACTOR_PLUS_DATA
{
	eapID,
	eapSkin,
	eapName[MAX_PLAYER_NAME],
	Float:eapPosX,
	Float:eapPosY,
	Float:eapPosZ,
	Float:eapPosAngle,
	eapInvulnerable,
	Float:eapHealth,
	eapVW,

	#if USING_STREAMER
	eapInt,
	eapPlayerid,
	Float:eapStreamDistance,
	STREAMER_TAG_AREA eapAreaid,
	eapPriority,
	#endif

	#if !USING_Y_TIMERS
	eapTimerChatBubble,
	#else
	Timer:eapTimerChatBubble,
	#endif

	// Text3D -- Label
	Text3D:eapLabel,
	eapLabelText[MAX_ACTOR_LABEL_LENGTH],
	eapLabelColor,
	Float:eapLabelPosX,
	Float:eapLabelPosY,
	Float:eapLabelPosZ,
	Float:eapLabelDrawDistance,
	eapLabelVW,
	eapLabelInt,


	// Animation
	eapAnimLib[MAX_ANIMATION_LIBRARY_LENGTH],
	eapAnimName[MAX_ANIMATION_NAME_LENGTH],
	Float:eapDelta,
	eapLoop,
	eapLockx,
	eapLocky,
	eapFreeze,
	eapTime,
}

enum E_ACTOR_PLUS_FLAGS (<<= 1)
{
	HAS_NAME_DISPLAYED = 1,
	HAS_TEXT_DISPLAYED,
	#if !USING_Y_ITERATE
	IS_EXISTING,
	#endif
	IS_DEAD,
	IS_INVULNERABLE,
};

static
	Actors_Plus[2][MAX_ACTORS][E_ACTOR_PLUS_DATA],
	E_ACTOR_PLUS_FLAGS:Actors_Flags[MAX_ACTORS][2],
	Player_ActorTarget[MAX_PLAYERS] = {INVALID_ACTOR_ID, INVALID_ACTOR_ID, INVALID_ACTOR_ID, ...};

#if USING_Y_ITERATE
	static
		Iterator:Static_Actors<MAX_ACTORS>,
		Iterator:Internal_ActorsID[MAX_ACTORS]<2>;

	#if USING_STREAMER
		static
			Iterator:Dynamic_Actors<MAX_ACTORS>;
	#endif
#else
	static
		Internal_ActorsID[MAX_ACTORS][2] = {{INVALID_ACTOR_ID}, {INVALID_ACTOR_ID}, ...};
#endif

enum _:E_PLAYER_AP_FLAGS(<<= 1)
{
	HIDE_TYPE_ONE_TIME = 1,
	HIDE_TYPE_PERMANENT,

	ANIMATION_PLAY_ONE_TIME,
	ANIMATION_PLAY_ONE_PERMANENT,
};

static
	Player_AP[MAX_PLAYERS][2][MAX_ACTORS];

// =====================================================================================

S->GetNearestActorForPlayer(playerid, Float:range = 2.0, &bool:isdynamic = false, type = SEARCH_TYPE_ALL)
{
	if(!IsPlayerConnected(playerid))
		return INVALID_ACTOR_ID;

	new actorid = INVALID_ACTOR_ID;
	#if USING_STREAMER
		#if USING_Y_ITERATE
			if(type & SEARCH_TYPE_STATIC)
			{
				foreach(new i : Static_Actors)
				{
					if(!IsPlayerInRangeOfPoint(playerid, range, Actors_Plus[STATIC_CATEGORY][i][eapPosX], Actors_Plus[STATIC_CATEGORY][i][eapPosY], Actors_Plus[STATIC_CATEGORY][i][eapPosZ]))
						continue;
					if(actorid != INVALID_ACTOR_ID)
						return MULTIPLE_TARGET_FOUND;
					actorid = i;
				}
			}
			if(type & SEARCH_TYPE_DYNAMIC)
			{
				foreach(new i : Dynamic_Actors)
				{
					if(!IsPlayerInRangeOfPoint(playerid, range, Actors_Plus[DYNAMIC_CATEGORY][i][eapPosX], Actors_Plus[DYNAMIC_CATEGORY][i][eapPosY], Actors_Plus[DYNAMIC_CATEGORY][i][eapPosZ]))
						continue;
					if(actorid != INVALID_ACTOR_ID)
						return MULTIPLE_TARGET_FOUND;
					actorid = i;
					isdynamic = true;
				}
			}
			return actorid;
		#else
			if(type & SEARCH_TYPE_STATIC)
			{
				for(new i, j = GetActorPoolSize(); i <= j; i++)
				{
					if(!IsValidActor(i))
						continue;
					if(!IsPlayerInRangeOfPoint(playerid, range, Actors_Plus[STATIC_CATEGORY][i][eapPosX], Actors_Plus[STATIC_CATEGORY][i][eapPosY], Actors_Plus[STATIC_CATEGORY][i][eapPosZ]))
						continue;

					if(actorid != INVALID_ACTOR_ID)
						return MULTIPLE_TARGET_FOUND;
					actorid = i;
				}
			}
			if(type & SEARCH_TYPE_DYNAMIC)
			{
				for(new i; i <= MAX_ACTORS; i++)
				{
					if(!IsValidDynamicActor(i))
						continue;
					if(!IsPlayerInRangeOfPoint(playerid, range, Actors_Plus[DYNAMIC_CATEGORY][i][eapPosX], Actors_Plus[DYNAMIC_CATEGORY][i][eapPosY], Actors_Plus[DYNAMIC_CATEGORY][i][eapPosZ]))
						continue;

					if(actorid != INVALID_ACTOR_ID)
						return MULTIPLE_TARGET_FOUND;
					actorid = i;
					isdynamic = true;
				}
			}
			return actorid;
		#endif
	#else
		#if USING_Y_ITERATE
			if(type & SEARCH_TYPE_STATIC)
			{
				foreach(new i : Static_Actors)
				{
					if(!IsPlayerInRangeOfPoint(playerid, range, Actors_Plus[STATIC_CATEGORY][i][eapPosX], Actors_Plus[STATIC_CATEGORY][i][eapPosY], Actors_Plus[STATIC_CATEGORY][i][eapPosZ]))
						continue;
					if(actorid != INVALID_ACTOR_ID)
						return MULTIPLE_TARGET_FOUND;
					actorid = i;
				}
			}
			return actorid;
		#else
			if(type & SEARCH_TYPE_STATIC)
			{
				for(new i, j = GetActorPoolSize(); i <= j; i++)
				{
					if(!IsValidActor(i))
						continue;
					if(!IsPlayerInRangeOfPoint(playerid, range, Actors_Plus[STATIC_CATEGORY][i][eapPosX], Actors_Plus[STATIC_CATEGORY][i][eapPosY], Actors_Plus[STATIC_CATEGORY][i][eapPosZ]))
						continue;

					if(actorid != INVALID_ACTOR_ID)
						return MULTIPLE_TARGET_FOUND;
					actorid = i;
				}
			}
			return actorid;
		#endif
	#endif
}

S->GetNearestActorByCoord(Float:x, Float:y, Float:z, Float:range = 2.0, &bool:isdynamic = false, type = SEARCH_TYPE_ALL, bool:return_multiple_target = true)
{
	new actorid = INVALID_ACTOR_ID;
	#if USING_STREAMER
		#if USING_Y_ITERATE
			if(type & SEARCH_TYPE_STATIC)
			{
				foreach(new i : Static_Actors)
				{
					if(!(GetDistanceBetween2Points(x, y, z, Actors_Plus[STATIC_CATEGORY][i][eapPosX], Actors_Plus[STATIC_CATEGORY][i][eapPosY], Actors_Plus[STATIC_CATEGORY][i][eapPosZ]) < range))
						continue;
					if(actorid != INVALID_ACTOR_ID && return_multiple_target)
						return MULTIPLE_TARGET_FOUND;
					actorid = i;
				}
			}
			if(type & SEARCH_TYPE_DYNAMIC)
			{
				foreach(new i : Dynamic_Actors)
				{
					if(!(GetDistanceBetween2Points(x, y, z, Actors_Plus[DYNAMIC_CATEGORY][i][eapPosX], Actors_Plus[DYNAMIC_CATEGORY][i][eapPosY], Actors_Plus[DYNAMIC_CATEGORY][i][eapPosZ]) < range))
						continue;
					if(actorid != INVALID_ACTOR_ID && return_multiple_target)
						return MULTIPLE_TARGET_FOUND;
					actorid = i;
					isdynamic = true;
				}
			}
			return actorid;
		#else
			if(type & SEARCH_TYPE_STATIC)
			{
				for(new i, j = GetActorPoolSize(); i <= j; i++)
				{
					if(!IsValidActor(i))
						continue;
					if(!(GetDistanceBetween2Points(x, y, z, Actors_Plus[STATIC_CATEGORY][i][eapPosX], Actors_Plus[STATIC_CATEGORY][i][eapPosY], Actors_Plus[STATIC_CATEGORY][i][eapPosZ]) < range))
						continue;

					if(actorid != INVALID_ACTOR_ID && return_multiple_target)
						return MULTIPLE_TARGET_FOUND;
					actorid = i;
				}
			}
			if(type & SEARCH_TYPE_DYNAMIC)
			{
				for(new i; i <= MAX_ACTORS; i++)
				{
					if(!IsValidDynamicActor(i))
						continue;
					if(!(GetDistanceBetween2Points(x, y, z, Actors_Plus[DYNAMIC_CATEGORY][i][eapPosX], Actors_Plus[DYNAMIC_CATEGORY][i][eapPosY], Actors_Plus[DYNAMIC_CATEGORY][i][eapPosZ]) < range))
						continue;

					if(actorid != INVALID_ACTOR_ID && return_multiple_target)
						return MULTIPLE_TARGET_FOUND;
					actorid = i;
					isdynamic = true;
				}
			}
			return actorid;
		#endif
	#else
		#if USING_Y_ITERATE
			if(type & SEARCH_TYPE_STATIC)
			{
				foreach(new i : Static_Actors)
				{
					if(!(GetDistanceBetween2Points(x, y, z, Actors_Plus[STATIC_CATEGORY][i][eapPosX], Actors_Plus[STATIC_CATEGORY][i][eapPosY], Actors_Plus[STATIC_CATEGORY][i][eapPosZ]) < range))
						continue;
					if(actorid != INVALID_ACTOR_ID && return_multiple_target)
						return MULTIPLE_TARGET_FOUND;
					actorid = i;
				}
			}
			return actorid;
		#else
			if(type & SEARCH_TYPE_STATIC)
			{
				for(new i, j = GetActorPoolSize(); i <= j; i++)
				{
					if(!IsValidActor(i))
						continue;
					if(!(GetDistanceBetween2Points(x, y, z, Actors_Plus[STATIC_CATEGORY][i][eapPosX], Actors_Plus[STATIC_CATEGORY][i][eapPosY], Actors_Plus[STATIC_CATEGORY][i][eapPosZ]) < range))
						continue;

					if(actorid != INVALID_ACTOR_ID && return_multiple_target)
						return MULTIPLE_TARGET_FOUND;
					actorid = i;
				}
			}
			return actorid;
		#endif
	#endif
}

// =====================================================================================

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if(hittype != BULLET_HIT_TYPE_NONE || (fX == 0.0 && fY == 0.0))
		return Y_HOOKS_CONTINUE_RETURN_1;

	new bool:isdynamic,
		actorid = GetNearestActorByCoord(fX, fY, fZ, 1.0, isdynamic);

	if(actorid != INVALID_ACTOR_ID && actorid != MULTIPLE_TARGET_FOUND)
	{
		#if defined OnPlayerShotActor
			OnPlayerShotActor(playerid, actorid, weaponid, isdynamic);
		#endif
	}

	#if defined AP_OnPlayerWeaponShot
		return AP_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerWeaponShot
    #undef OnPlayerWeaponShot
#else
    #define _ALS_OnPlayerWeaponShot
#endif
#define OnPlayerWeaponShot AP_OnPlayerWeaponShot
#if defined AP_OnPlayerWeaponShot
	forward AP_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#endif


#if defined OnPlayerMakeDamageToActor || defined OnActorDeath
public OnPlayerGiveDamageActor(playerid, damaged_actorid, Float:amount, weaponid, bodypart)
{
	new 
		Float:fOriginX, Float:fOriginY, Float:fOriginZ,
		Float:fHitPosX, Float:fHitPosY, Float:fHitPosZ;

	GetPlayerLastShotVectors(playerid, fOriginX, fOriginY, fOriginZ, fHitPosX, fHitPosY, fHitPosZ);
	// APD("STATIC: damaged_actorid: %i by %i with %i", damaged_actorid, playerid, weaponid);

	if(GetNearestActorByCoord(fHitPosX, fHitPosY, fHitPosZ, .type = SEARCH_TYPE_STATIC) == damaged_actorid)
	{
		new bool:death = ((Actors_Plus[STATIC_CATEGORY][damaged_actorid][eapHealth] -= amount) <= 0.0);
		// APD("actorid: %i detect as a valid actor - Static", damaged_actorid);
		
		#if defined OnPlayerMakeDamageToActor

			if(!OnPlayerMakeDamageToActor(playerid, damaged_actorid, amount, weaponid, bodypart, false, death))
			{
				#if defined AP_OnPlayerGiveDamageActor
					return AP_OnPlayerGiveDamageActor(playerid, damaged_actorid, amount, weaponid, bodypart);
				#else
					return 1;
				#endif
			}

			Actors_Plus[STATIC_CATEGORY][damaged_actorid][eapHealth] -= amount;
			
			if(death)
			{
				Actors_Plus[STATIC_CATEGORY][damaged_actorid][eapHealth] = 0.0;
				Actors_Flags[damaged_actorid][STATIC_CATEGORY] |= IS_DEAD;
			}

			SetActorHealth(damaged_actorid, Actors_Plus[STATIC_CATEGORY][damaged_actorid][eapHealth]);
		#endif

		#if defined OnActorDeath
			if(death)
				OnActorDeath(damaged_actorid, playerid, weaponid, false);
		#endif

		#if defined AP_OnPlayerGiveDamageActor
			return AP_OnPlayerGiveDamageActor(playerid, damaged_actorid, amount, weaponid, bodypart);
		#else
			return 1;
		#endif
	}

	#if defined AP_OnPlayerGiveDamageActor
		return AP_OnPlayerGiveDamageActor(playerid, damaged_actorid, amount, weaponid, bodypart);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerGiveDamageActor
    #undef OnPlayerGiveDamageActor
#else
    #define _ALS_OnPlayerGiveDamageActor
#endif
#define OnPlayerGiveDamageActor AP_OnPlayerGiveDamageActor
#if defined AP_OnPlayerGiveDamageActor
	forward AP_OnPlayerGiveDamageActor(playerid, damaged_actorid, Float:amount, weaponid, bodypart);
#endif

#endif


#if USING_STREAMER && (defined OnPlayerMakeDamageToActor || defined OnActorDeath)
public OnPlayerGiveDamageDynamicActor(playerid, STREAMER_TAG_ACTOR actorid, Float:amount, weaponid, bodypart)
{
	new 
		Float:fOriginX, Float:fOriginY, Float:fOriginZ,
		Float:fHitPosX, Float:fHitPosY, Float:fHitPosZ;

	GetPlayerLastShotVectors(playerid, fOriginX, fOriginY, fOriginZ, fHitPosX, fHitPosY, fHitPosZ);
	// APD("DYNAMIC: actorid: %i by %i with %i", actorid, playerid, weaponid);

	if(GetNearestActorByCoord(fHitPosX, fHitPosY, fHitPosZ, .type = SEARCH_TYPE_DYNAMIC) == actorid)
	{
		new bool:death = ((Actors_Plus[DYNAMIC_CATEGORY][actorid][eapHealth] - amount) <= 0.0);

		// APD("actorid: %i detect as a valid actor - DYNAMIC: %i", actorid, isdynamic);
		#pragma unused death

		#if defined OnPlayerMakeDamageToActor

			if(!OnPlayerMakeDamageToActor(playerid, actorid, amount, weaponid, bodypart, true, death))
			{
				#if defined BOnPlayerGiveDamageDynamicActor
					return BOnPlayerGiveDamageDynamicActor(playerid, actorid, amount, weaponid, bodypart);
				#else
					return 1;
				#endif
			}

			Actors_Plus[DYNAMIC_CATEGORY][actorid][eapHealth] -= amount;
			
			if(death)
			{
				Actors_Flags[actorid][DYNAMIC_CATEGORY] |= IS_DEAD;
				Actors_Plus[DYNAMIC_CATEGORY][actorid][eapHealth] = 0.0;
			}

			SetDynamicActorHealth(actorid, Actors_Plus[DYNAMIC_CATEGORY][actorid][eapHealth]);
		#endif

		#if defined OnActorDeath
			if(death)
				OnActorDeath(actorid, playerid, weaponid, true);
		#endif

		#if defined BOnPlayerGiveDamageDynamicActor
			return BOnPlayerGiveDamageDynamicActor(playerid, actorid, amount, weaponid, bodypart);
		#else
			return 1;
		#endif
	}

	#if defined BOnPlayerGiveDamageDynamicActor
		return BOnPlayerGiveDamageDynamicActor(playerid, actorid, amount, weaponid, bodypart);
	#else
		return 1;
	#endif
}
#endif // #if USING_STREAMER && (defined OnPlayerMakeDamageToActor || defined OnActorDeath)


#if defined AOnPlayerGiveDamageDynamicActor
    #undef OnPlayerGiveDamageDynamicActor
#else
    #define AOnPlayerGiveDamageDynamicActor
#endif
#define OnPlayerGiveDamageDynamicActor BOnPlayerGiveDamageDynamicActor
#if defined BOnPlayerGiveDamageDynamicActor
	forward BOnPlayerGiveDamageDynamicActor(playerid, STREAMER_TAG_ACTOR actorid, Float:amount, weaponid, bodypart);
#endif

public OnPlayerConnect(playerid)
{
	Player_ActorTarget[playerid] = INVALID_ACTOR_ID;
	#if defined AP_OnPlayerConnect
	    return AP_OnPlayerConnect(playerid);
	#else
	    return 1;
	#endif
}

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect AP_OnPlayerConnect
#if defined AP_OnPlayerConnect
	forward AP_OnPlayerConnect(playerid);
#endif

// =====================================================================================

#if !defined DONT_DETECT_OPTA && defined OnPlayerTargetActor
	#if !USING_Y_TIMERS
		forward @AP_AimingActor();
		@AP_AimingActor()
		{
			#if USING_Y_ITERATE
				foreach(new i : Player)
				{
					new actorid = GetPlayerTargetActor(i);
					if(actorid != INVALID_ACTOR_ID && Player_ActorTarget[i] != actorid)
					{
						Player_ActorTarget[i] = actorid;
						OnPlayerTargetActor(i, actorid, GetPlayerWeapon(i));
					}
				}
			#else
				for(new i, j = GetPlayerPoolSize(); i <= j; i++)
				{
					new actorid = GetPlayerTargetActor(i);
					if(actorid != INVALID_ACTOR_ID && Player_ActorTarget[i] != actorid)
					{
						Player_ActorTarget[i] = actorid;
						OnPlayerTargetActor(i, actorid, GetPlayerWeapon(i));
					}
				}
			#endif
			return 1;
		}
		#if !defined FILTERSCRIPT
			public OnGameModeInit()
			{
				SetTimer("@AP_AimingActor", DEFAULT_CHECKING_TIME, 1);
				#if defined AP_OnGameModeInit
					return AP_OnGameModeInit();
				#else
					return 1;
				#endif
			}

			#if defined _ALS_OnGameModeInit
			    #undef OnGameModeInit
			#else
			    #define _ALS_OnGameModeInit
			#endif
			#if defined AP_OnGameModeInit
				forward AP_OnGameModeInit();
			#endif			
			#define OnGameModeInit AP_OnGameModeInit


		#else

			public OnFilterScriptInit()
			{
				SetTimer("@AP_AimingActor", DEFAULT_CHECKING_TIME, 1);
				#if defined AUniP_OnFilterScriptInit
				    return AUniP_OnFilterScriptInit();
				#else
				    return 1;
				#endif
			}

			#if defined _ALS_OnFilterScriptInit
			    #undef OnFilterScriptInit
			#else
			    #define _ALS_OnFilterScriptInit
			#endif
			#if defined AUniP_OnFilterScriptInit
				forward AUniP_OnFilterScriptInit();
			#endif
			#define OnFilterScriptInit AUniP_OnFilterScriptInit

		#endif
	#else
		ptask AP_AimingActor[DEFAULT_CHECKING_TIME](playerid)
		{
			new actorid = GetPlayerTargetActor(playerid);
			if(actorid != INVALID_ACTOR_ID && Player_ActorTarget[i] != actorid)
			{
				Player_ActorTarget[playerid] = actorid;
				OnPlayerTargetActor(playerid, actorid, GetPlayerWeapon(i));
			}
			return 1;	
		}
	#endif // if !USING_Y_TIMERS
#endif // if !defined DONT_DETECT_OPTA


// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if USING_STREAMER
S->RespawnActor(actorid, bool:isdynamic = true)
#else
S->RespawnActor(actorid)
#endif
{
	#if !USING_STREAMER
		if(!AP_IsValidActor(actorid))
			return 0;
		RecreateActor(actorid);
		return 1;
	#else
		if(!AP_IsValidActor(actorid, isdynamic))
			return 0;

		RecreateActor(actorid, isdynamic);
		return 1;
	#endif
}


// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if USING_STREAMER
S->SetActorName(actorid, actor_name[], bool:display, bool:contain_id = false, bool:reformat_label = false, bool:isdynamic = true)
#else
S->SetActorName(actorid, actor_name[], bool:display, bool:contain_id = false, bool:reformat_label = false)
#endif
{
	if(!(3 <= strlen(actor_name) <= 24))
		return cellmin;

	new formatted_name[31];
	if(contain_id)
		format(formatted_name, sizeof(formatted_name), "%s (%i)", actor_name, actorid);
	else
		strcat(formatted_name, actor_name);
	
	#if !USING_STREAMER
		if(!AP_IsValidActor(actorid))
			return 0;

		if(display)
			Actors_Flags[actorid][STATIC_CATEGORY] |= HAS_NAME_DISPLAYED;
		else
			Actors_Flags[actorid][STATIC_CATEGORY] &= ~HAS_NAME_DISPLAYED;

		if(!(Actors_Flags[actorid][STATIC_CATEGORY] & HAS_TEXT_DISPLAYED))
		{
			Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosX] = 
			Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosY] = 0.0;
			Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosZ] = 1.0;
		}

		if(!Actors_Plus[STATIC_CATEGORY][actorid][eapLabelDrawDistance])
			Actors_Plus[STATIC_CATEGORY][actorid][eapLabelDrawDistance] = DEFAULT_ACTOR_DRAW_DISTANCE;

		strcpy(Actors_Plus[STATIC_CATEGORY][actorid][eapName], formatted_name);
		if(!Actors_Plus[STATIC_CATEGORY][actorid][eapLabelColor])
			Actors_Plus[STATIC_CATEGORY][actorid][eapLabelColor] = DEFAULT_ACTOR_COLOR;
		if(reformat_label && Actors_Plus[STATIC_CATEGORY][actorid][eapLabel] != Text3D:INVALID_3DTEXT_ID)
		{
			new other_string[MAX_PLAYER_NAME + MAX_ACTOR_LABEL_LENGTH];
			format(other_string, sizeof(other_string), "%s\n{%06x}%s", formatted_name, Actors_Plus[STATIC_CATEGORY][actorid][eapLabelColor], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText]);
			// strcpy(Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText], other_string);
			if(display)
				Attach3DTextLabelToActor(actorid, other_string, DEFAULT_ACTOR_COLOR, Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosX], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosY], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosZ], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelDrawDistance], .store_string = false);
			
		}
		else if(display)
			Attach3DTextLabelToActor(actorid, formatted_name, DEFAULT_ACTOR_COLOR, Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosX], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosY], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosZ], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelDrawDistance], .store_string = false);
	
	#else
		if(!AP_IsValidActor(actorid, isdynamic))
			return 0;

		if(display)
			Actors_Flags[actorid][isdynamic] |= HAS_NAME_DISPLAYED;
		else
			Actors_Flags[actorid][isdynamic] &= ~HAS_NAME_DISPLAYED;

		if(!Actors_Plus[isdynamic][actorid][eapLabelColor])
			Actors_Plus[isdynamic][actorid][eapLabelColor] = DEFAULT_ACTOR_COLOR;
		strcpy(Actors_Plus[isdynamic][actorid][eapName], formatted_name);

		if(!Actors_Plus[isdynamic][actorid][eapLabelDrawDistance])
			Actors_Plus[isdynamic][actorid][eapLabelDrawDistance] = DEFAULT_ACTOR_DRAW_DISTANCE;

		if(!(Actors_Flags[actorid][STATIC_CATEGORY] & HAS_TEXT_DISPLAYED))
		{
			Actors_Plus[isdynamic][actorid][eapLabelPosX] = 
			Actors_Plus[isdynamic][actorid][eapLabelPosY] = 0.0;
			Actors_Plus[isdynamic][actorid][eapLabelPosZ] = 1.0;
		}

		if(reformat_label && Actors_Plus[isdynamic][actorid][eapLabel] != Text3D:INVALID_3DTEXT_ID)
		{
			new other_string[MAX_PLAYER_NAME + MAX_ACTOR_LABEL_LENGTH];
			format(other_string, sizeof(other_string), "%s\n{%06x}%s", formatted_name, Actors_Plus[isdynamic][actorid][eapLabelColor], Actors_Plus[isdynamic][actorid][eapLabelText]);
			// strcpy(Actors_Plus[isdynamic][actorid][eapLabelText], other_string);
			if(display)
				Attach3DTextLabelToActor(actorid, other_string, isdynamic, DEFAULT_ACTOR_COLOR, Actors_Plus[isdynamic][actorid][eapLabelPosX], Actors_Plus[isdynamic][actorid][eapLabelPosY], Actors_Plus[isdynamic][actorid][eapLabelPosZ], Actors_Plus[isdynamic][actorid][eapLabelDrawDistance], .store_string = false);
		}
		else if(display)
			Attach3DTextLabelToActor(actorid, formatted_name, isdynamic, DEFAULT_ACTOR_COLOR, Actors_Plus[isdynamic][actorid][eapLabelPosX], Actors_Plus[isdynamic][actorid][eapLabelPosY], Actors_Plus[isdynamic][actorid][eapLabelPosZ], Actors_Plus[isdynamic][actorid][eapLabelDrawDistance], .store_string = false);
		
	#endif
	return 1;
}


// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if USING_STREAMER
S->GetActorName(actorid, actor_name[],  length = sizeof(actor_name), bool:isdynamic = true)
#else
S->GetActorName(actorid, actor_name[], length = sizeof(actor_name))
#endif
{
	#if !USING_STREAMER
		if(!AP_IsValidActor(actorid))
			return 0;

		if(!isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapName]))
			strcat(actor_name, Actors_Plus[STATIC_CATEGORY][actorid][eapName], length);
		else 
			return cellmin;

		return 1;
	#else
		if(!AP_IsValidActor(actorid, isdynamic))
			return 0;
		if(!isnull(Actors_Plus[isdynamic][actorid][eapName]))
			strcat(actor_name, Actors_Plus[isdynamic][actorid][eapName], length);
		else 
			return cellmin;
	
		return 1;
	#endif
}


// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if USING_STREAMER
S->GetActorTextLabel(actorid, text[], length = sizeof(text), bool:isdynamic = true)
#else
S->GetActorTextLabel(actorid, text[], length = sizeof(text))
#endif
{
	#if !USING_STREAMER
		if(!AP_IsValidActor(actorid))
			return 0;

		if(!isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText]))
			strcat(text, Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText], length);
		else 
			return cellmin;
		return 1;
	#else
		if(!AP_IsValidActor(actorid, isdynamic))
			return 0;

		if(!isnull(Actors_Plus[isdynamic][actorid][eapLabelText]))
			strcat(text, Actors_Plus[isdynamic][actorid][eapLabelText], length);
		else 
			return cellmin;
		
		return 1;
	#endif
}


// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if USING_STREAMER
S->Attach3DTextLabelToActor(actorid, const text[], bool:isdynamic, color, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:drawdistance, testlos = 0, worldid = DEFAULT_ACTOR_VALUE, interiorid = DEFAULT_ACTOR_VALUE, playerid = DEFAULT_ACTOR_VALUE, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = DEFAULT_ACTOR_VALUE, priority = 0, bool:store_string = true)
#else
S->Attach3DTextLabelToActor(actorid, text[], color, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:drawdistance, virtualworld = DEFAULT_ACTOR_VALUE, testlos = 0, bool:store_string = true)
#endif
{
	#if !USING_STREAMER
		if(!AP_IsValidActor(actorid))
			return 0;
		if(Actors_Plus[STATIC_CATEGORY][actorid][eapLabel] != Text3D:INVALID_3DTEXT_ID)
			Delete3DTextLabel(Actors_Plus[STATIC_CATEGORY][actorid][eapLabel]);

		if(store_string)
		{
			strcpy(Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText], text);
			Actors_Flags[actorid][STATIC_CATEGORY] |= HAS_TEXT_DISPLAYED;
		}

		APD("(Attach3DTextLabelToActor) text: '%s' | actorid: %i | color: %x | drawdistance: %f", text, actorid, color, drawdistance);
		Actors_Plus[STATIC_CATEGORY][actorid][eapLabelColor] = color;
		Actors_Plus[STATIC_CATEGORY][actorid][eapLabelDrawDistance] = drawdistance;
		Actors_Plus[STATIC_CATEGORY][actorid][eapLabelVW] = virtualworld;
		Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosX] = OffsetX;
		Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosY] = OffsetY;
		Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosZ] = OffsetZ;
		Actors_Plus[STATIC_CATEGORY][actorid][eapLabel] = Create3DTextLabel(text, color, Actors_Plus[STATIC_CATEGORY][actorid][eapPosX] + OffsetX, Actors_Plus[STATIC_CATEGORY][actorid][eapPosY] + OffsetY, Actors_Plus[STATIC_CATEGORY][actorid][eapPosZ] + OffsetZ, drawdistance, virtualworld == DEFAULT_ACTOR_VALUE ? Actors_Plus[STATIC_CATEGORY][actorid][eapVW] : virtualworld, testlos);
	#else
		if(!AP_IsValidActor(actorid, isdynamic))
			return 0;

		if(store_string)
			Actors_Flags[actorid][isdynamic] |= HAS_TEXT_DISPLAYED;
		
		APD("(Attach3DTextLabelToActor) text: '%s' | actorid: %i | color: %x | drawdistance: %f", text, actorid, color, drawdistance);

		if(IsValidDynamic3DTextLabel(Actors_Plus[isdynamic][actorid][eapLabel]))
			DestroyDynamic3DTextLabel(Actors_Plus[isdynamic][actorid][eapLabel]);
		if(store_string)
			strcpy(Actors_Plus[isdynamic][actorid][eapLabelText], text);

		Actors_Plus[isdynamic][actorid][eapLabelColor] = color;
		Actors_Plus[isdynamic][actorid][eapLabelDrawDistance] = drawdistance;
		Actors_Plus[isdynamic][actorid][eapLabelVW] = worldid;
		Actors_Plus[isdynamic][actorid][eapLabelPosX] = OffsetX;
		Actors_Plus[isdynamic][actorid][eapLabelPosY] = OffsetY;
		Actors_Plus[isdynamic][actorid][eapLabelPosZ] = OffsetZ;
		Actors_Plus[isdynamic][actorid][eapLabel] = CreateDynamic3DTextLabel(text, color, Actors_Plus[isdynamic][actorid][eapPosX] + OffsetX, Actors_Plus[isdynamic][actorid][eapPosY] + OffsetY, Actors_Plus[isdynamic][actorid][eapPosZ] + OffsetZ, drawdistance,
			INVALID_PLAYER_ID, INVALID_VEHICLE_ID, testlos,
			worldid == DEFAULT_ACTOR_VALUE ? Actors_Plus[isdynamic][actorid][eapVW] : worldid, interiorid == DEFAULT_ACTOR_VALUE ? Actors_Plus[isdynamic][actorid][eapInt] : interiorid, playerid == DEFAULT_ACTOR_VALUE ? Actors_Plus[isdynamic][actorid][eapPlayerid] : playerid,
			streamdistance == DEFAULT_ACTOR_VALUE ? Actors_Plus[isdynamic][actorid][eapStreamDistance] : streamdistance, areaid == DEFAULT_ACTOR_VALUE ? Actors_Plus[isdynamic][actorid][eapAreaid] : areaid, priority);
		
	#endif
	return 1;
}

// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if USING_STREAMER
S->ActorHasAttachedLabel(actorid, &bool:name_displayed = false, &bool:text_displayed = false, bool:isdynamic = true)
#else
S->ActorHasAttachedLabel(actorid, &bool:name_displayed = false, &bool:text_displayed = false)
#endif
{
	#if !USING_STREAMER
		if(!AP_IsValidActor(actorid))
			return 0;

		if(Actors_Flags[actorid][STATIC_CATEGORY] & HAS_NAME_DISPLAYED)
			name_displayed = true;

		if(Actors_Flags[actorid][STATIC_CATEGORY] & HAS_TEXT_DISPLAYED)
			text_displayed = true;

		return (Actors_Plus[STATIC_CATEGORY][actorid][eapLabel] != Text3D:INVALID_3DTEXT_ID);
	#else
		if(!AP_IsValidActor(actorid, isdynamic))
			return 0;

		if(Actors_Flags[actorid][isdynamic] & HAS_NAME_DISPLAYED)
			name_displayed = true;

		if(Actors_Flags[actorid][isdynamic] & HAS_TEXT_DISPLAYED)
			text_displayed = true;

		return (Actors_Plus[isdynamic][actorid][eapLabel] != Text3D:INVALID_3DTEXT_ID);
	#endif
}

// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if USING_STREAMER
S->UpdateAttachedActor3DTextLabel(actorid, text[], color, bool:isdynamic = true)
#else
S->UpdateAttachedActor3DTextLabel(actorid, text[], color)
#endif
{
	#if !USING_STREAMER
		if(!AP_IsValidActor(actorid) || Actors_Plus[STATIC_CATEGORY][actorid][eapLabel] == Text3D:INVALID_3DTEXT_ID)
			return 0;
		strcpy(Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText], text);
		Actors_Plus[STATIC_CATEGORY][actorid][eapLabelColor] = color;
		Internal_Update3DActorTextLabel(actorid);
		return 1;

	#else
		if(!AP_IsValidActor(actorid, isdynamic))
			return 0;

		if(Actors_Plus[isdynamic][actorid][eapLabel] == Text3D:INVALID_3DTEXT_ID)
			return 0;
		strcpy(Actors_Plus[isdynamic][actorid][eapLabelText], text);
		Actors_Plus[isdynamic][actorid][eapLabelColor] = color;
		Internal_Update3DActorTextLabel(actorid);
	
		return 1;
	#endif
}

// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if USING_STREAMER
S->SetActorChatBubble(actorid, const text[], color, Float:drawdistance, expiretime, bool:isdynamic = true)
#else
S->SetActorChatBubble(actorid, text[], color, Float:drawdistance, expiretime)
#endif
{
	#if !USING_STREAMER
		if(!AP_IsValidActor(actorid))
			return 0;

		if(Actors_Plus[STATIC_CATEGORY][actorid][eapLabel] == Text3D:INVALID_3DTEXT_ID)
			Attach3DTextLabelToActor(actorid, text, color, 0.0, 0.0, 1.0, drawdistance, .store_string = false);
		else
			Update3DTextLabelText(Actors_Plus[STATIC_CATEGORY][actorid][eapLabel], color, text);
		
		#if USING_Y_TIMERS
			Actors_Plus[STATIC_CATEGORY][actorid][eapTimerChatBubble] = defer AT_DeleteBubbleChat[expiretime](actorid, false);
		#else
			Actors_Plus[STATIC_CATEGORY][actorid][eapTimerChatBubble] = SetTimerEx("@AT_DeleteBubbleChat", expiretime, false, "ii", actorid, false);
		#endif
		return 1;
	#else
		if(!AP_IsValidActor(actorid, isdynamic))
			return 0;

		if(Actors_Plus[isdynamic][actorid][eapLabel] == Text3D:INVALID_3DTEXT_ID)
			Attach3DTextLabelToActor(actorid, text, isdynamic, color, 0.0, 0.0, 1.0, drawdistance, .store_string = false);
		
		else
		{
			new formatted_string[MAX_ACTOR_LABEL_LENGTH];
			format(formatted_string, sizeof(formatted_string), "%s\n{%06x}%s", text, Actors_Plus[isdynamic][actorid][eapName], Actors_Plus[isdynamic][actorid][eapLabelColor], Actors_Plus[isdynamic][actorid][eapLabelText]);
			UpdateDynamic3DTextLabelText(Actors_Plus[isdynamic][actorid][eapLabel], color, formatted_string);
		}
		#if USING_Y_TIMERS
			Actors_Plus[isdynamic][actorid][eapTimerChatBubble] = defer AT_DeleteBubbleChat[expiretime](actorid, isdynamic);
		#else
			Actors_Plus[isdynamic][actorid][eapTimerChatBubble] = SetTimerEx("@AT_DeleteBubbleChat", expiretime, false, "ii", actorid, isdynamic);
		#endif
		
		return 1;
	#endif
}

#if USING_Y_TIMERS
	timer AT_DeleteBubbleChat[2000](actorid, bool:isdynamic)
	{
		new formatted_label[MAX_ACTOR_LABEL_LENGTH + MAX_PLAYER_NAME];
		#if !USING_STREAMER
			Delete3DTextLabel(Actors_Plus[STATIC_CATEGORY][actorid][eapLabel]);
			if(!isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapName]))
				strcat(formatted_label, Actors_Plus[STATIC_CATEGORY][actorid][eapName]);

			if(!isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText]))
			{
				if(isnull(formatted_label))
					strcat(formatted_label, Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText]);
				else
					format(formatted_label, sizeof(formatted_label), "%s\n%s", Actors_Plus[STATIC_CATEGORY][actorid][eapName], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText]);
			}

			if(!isnull(formatted_label))
				Attach3DTextLabelToActor(actorid, formatted_label, Actors_Plus[STATIC_CATEGORY][actorid][eapLabelColor], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosX], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosY], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosZ], DEFAULT_ACTOR_DRAW_DISTANCE, .store_string = false);
			else
				Actors_Plus[STATIC_CATEGORY][actorid][eapLabel] = Text3D:INVALID_3DTEXT_ID;
		#else
			if(isdynamic)
			{
				DestroyDynamic3DTextLabel(Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabel]);
				if(!isnull(Actors_Plus[DYNAMIC_CATEGORY][actorid][eapName]))
					strcat(formatted_label, Actors_Plus[DYNAMIC_CATEGORY][actorid][eapName]);

				if(!isnull(Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelText]))
				{
					if(isnull(formatted_label))
						strcat(formatted_label, Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelText]);
					else
						format(formatted_label, sizeof(formatted_label), "%s\n%s", Actors_Plus[DYNAMIC_CATEGORY][actorid][eapName], Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelText]);
				}

				if(!isnull(formatted_label))
					Attach3DTextLabelToActor(actorid, formatted_label, isdynamic, Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelColor], Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelPosX], Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelPosY], Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelPosZ], DEFAULT_ACTOR_DRAW_DISTANCE, .store_string = false);
				else
					Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabel] = Text3D:INVALID_3DTEXT_ID;
			}
			else
			{
				DestroyDynamic3DTextLabel(Actors_Plus[STATIC_CATEGORY][actorid][eapLabel]);
				if(!isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapName]))
					strcat(formatted_label, Actors_Plus[STATIC_CATEGORY][actorid][eapName]);

				if(!isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText]))
				{
					if(isnull(formatted_label))
						strcat(formatted_label, Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText]);
					else
						format(formatted_label, sizeof(formatted_label), "%s\n%s", Actors_Plus[STATIC_CATEGORY][actorid][eapName], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText]);
				}

				if(!isnull(formatted_label))
					Attach3DTextLabelToActor(actorid, formatted_label, isdynamic, Actors_Plus[STATIC_CATEGORY][actorid][eapLabelColor], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosX], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosY], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosZ], DEFAULT_ACTOR_DRAW_DISTANCE, .store_string = false);
				else
					Actors_Plus[STATIC_CATEGORY][actorid][eapLabel] = Text3D:INVALID_3DTEXT_ID;
			}
		#endif // #if USING_Y_TIMERS
		return 1;
	}
#else
	forward @AT_DeleteBubbleChat(actorid, bool:isdynamic);
	@AT_DeleteBubbleChat(actorid, bool:isdynamic)
	{
		new formatted_label[MAX_ACTOR_LABEL_LENGTH + MAX_PLAYER_NAME];
		#if !USING_STREAMER
			Delete3DTextLabel(Actors_Plus[STATIC_CATEGORY][actorid][eapLabel]);
			if(!isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapName]))
				strcat(formatted_label, Actors_Plus[STATIC_CATEGORY][actorid][eapName]);

			if(!isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText]))
			{
				if(isnull(formatted_label))
					strcat(formatted_label, Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText]);
				else
					format(formatted_label, sizeof(formatted_label), "%s\n%s", Actors_Plus[STATIC_CATEGORY][actorid][eapName], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText]);
			}

			if(!isnull(formatted_label))
				Attach3DTextLabelToActor(actorid, formatted_label, Actors_Plus[STATIC_CATEGORY][actorid][eapLabelColor], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosX], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosY], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosZ], DEFAULT_ACTOR_DRAW_DISTANCE, .store_string = false);
			else
				Actors_Plus[STATIC_CATEGORY][actorid][eapLabel] = Text3D:INVALID_3DTEXT_ID;
		#else
			if(isdynamic)
			{
				DestroyDynamic3DTextLabel(Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabel]);
				if(!isnull(Actors_Plus[DYNAMIC_CATEGORY][actorid][eapName]))
					strcat(formatted_label, Actors_Plus[DYNAMIC_CATEGORY][actorid][eapName]);

				if(!isnull(Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelText]))
				{
					if(isnull(formatted_label))
						strcat(formatted_label, Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelText]);
					else
						format(formatted_label, sizeof(formatted_label), "%s\n%s", Actors_Plus[DYNAMIC_CATEGORY][actorid][eapName], Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelText]);
				}

				if(!isnull(formatted_label))
					Attach3DTextLabelToActor(actorid, formatted_label, isdynamic, Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelColor], Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelPosX], Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelPosY], Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelPosZ], DEFAULT_ACTOR_DRAW_DISTANCE, .store_string = false);
				else
					Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabel] = Text3D:INVALID_3DTEXT_ID;
			}
			else
			{
				DestroyDynamic3DTextLabel(Actors_Plus[STATIC_CATEGORY][actorid][eapLabel]);
				if(!isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapName]))
					strcat(formatted_label, Actors_Plus[STATIC_CATEGORY][actorid][eapName]);

				if(!isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText]))
				{
					if(isnull(formatted_label))
						strcat(formatted_label, Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText]);
					else
						format(formatted_label, sizeof(formatted_label), "%s\n%s", Actors_Plus[STATIC_CATEGORY][actorid][eapName], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText]);
				}

				if(!isnull(formatted_label))
					Attach3DTextLabelToActor(actorid, formatted_label, isdynamic, Actors_Plus[STATIC_CATEGORY][actorid][eapLabelColor], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosX], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosY], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelPosZ], DEFAULT_ACTOR_DRAW_DISTANCE, .store_string = false);
				else
					Actors_Plus[STATIC_CATEGORY][actorid][eapLabel] = Text3D:INVALID_3DTEXT_ID;
			}
		#endif // #if USING_Y_TIMERS
		return 1;
	}
#endif // #if USING_Y_TIMERS

// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if USING_STREAMER
S->DestroyActor3DTextLabel(actorid, bool:isdynamic = true)
#else
S->DestroyActor3DTextLabel(actorid)
#endif
{
	#if !USING_STREAMER
		if(!AP_IsValidActor(actorid) || Actors_Plus[STATIC_CATEGORY][actorid][eapLabel] == Text3D:INVALID_3DTEXT_ID)
			return 0;

		#if USING_Y_TIMERS
			if(_:Actors_Plus[STATIC_CATEGORY][actorid][eapTimerChatBubble])
				stop Actors_Plus[STATIC_CATEGORY][actorid][eapTimerChatBubble];
			Actors_Plus[STATIC_CATEGORY][actorid][eapTimerChatBubble] = Timer:0;
		#else
			if(Actors_Plus[STATIC_CATEGORY][actorid][eapTimerChatBubble])
				KillTimer(Actors_Plus[STATIC_CATEGORY][actorid][eapTimerChatBubble]);
			Actors_Plus[STATIC_CATEGORY][actorid][eapTimerChatBubble] = 0;
		#endif
		APD("DestroyActor3DTextLabel called by %i", actorid);
		Delete3DTextLabel(Actors_Plus[STATIC_CATEGORY][actorid][eapLabel]);
		Actors_Flags[actorid][STATIC_CATEGORY] &= ~HAS_NAME_DISPLAYED;
		Actors_Flags[actorid][STATIC_CATEGORY] &= ~HAS_TEXT_DISPLAYED;
		Actors_Plus[STATIC_CATEGORY][actorid][eapLabel] = Text3D:INVALID_3DTEXT_ID;
		Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText][0] = EOS;
		if(isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapName]))
			Actors_Plus[STATIC_CATEGORY][actorid][eapLabelColor] = 0;

		return 1;

	#else
		if(!AP_IsValidActor(actorid, isdynamic))
			return 0;

		Actors_Flags[actorid][isdynamic] &= ~HAS_NAME_DISPLAYED;
		Actors_Flags[actorid][isdynamic] &= ~HAS_TEXT_DISPLAYED;

		#if USING_Y_TIMERS
			if(_:Actors_Plus[isdynamic][actorid][eapTimerChatBubble])
				stop Actors_Plus[isdynamic][actorid][eapTimerChatBubble];
			Actors_Plus[isdynamic][actorid][eapTimerChatBubble] = Timer:0;
		#else
			if(Actors_Plus[isdynamic][actorid][eapTimerChatBubble])
				KillTimer(Actors_Plus[isdynamic][actorid][eapTimerChatBubble]);
			Actors_Plus[isdynamic][actorid][eapTimerChatBubble] = 0;
		#endif
		APD("DestroyActor3DTextLabel called by %i", actorid);
		DestroyDynamic3DTextLabel(Actors_Plus[isdynamic][actorid][eapLabel]);
		Actors_Plus[isdynamic][actorid][eapLabel] = Text3D:INVALID_3DTEXT_ID;
		Actors_Plus[isdynamic][actorid][eapLabelText][0] = EOS;
		if(isnull(Actors_Plus[isdynamic][actorid][eapName]))
			Actors_Plus[isdynamic][actorid][eapLabelColor] = 0;
		
		return 1;
	#endif
}

// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if USING_STREAMER
S->ToggleActorName(actorid, bool:toggle, bool:isdynamic = true)
#else
S->ToggleActorName(actorid, bool:toggle)
#endif
{
	if(toggle)
	{
		#if !USING_STREAMER
			#if USING_Y_TIMERS
				if(_:Actors_Plus[STATIC_CATEGORY][actorid][eapTimerChatBubble] || !AP_IsValidActor(actorid))
					return -1;
			#else
				if(Actors_Plus[STATIC_CATEGORY][actorid][eapTimerChatBubble] || !AP_IsValidActor(actorid))
					return -1;
			#endif

			if(Actors_Flags[actorid][STATIC_CATEGORY] & HAS_NAME_DISPLAYED || isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapName]))
				return cellmin;
			Actors_Flags[actorid][STATIC_CATEGORY] |= HAS_NAME_DISPLAYED;
			Internal_Update3DActorTextLabel(actorid);
		#else

			if(Actors_Flags[actorid][isdynamic] & HAS_NAME_DISPLAYED)
				return cellmin;

			if(isnull(Actors_Plus[isdynamic][actorid][eapName]))
				return cellmin;

			#if USING_Y_TIMERS
				if(_:Actors_Plus[isdynamic][actorid][eapTimerChatBubble] || !AP_IsValidActor(actorid, isdynamic))
					return 0;
			#else
				if(Actors_Plus[isdynamic][actorid][eapTimerChatBubble] || !AP_IsValidActor(actorid, isdynamic))
					return 0;
			#endif
			
			Actors_Flags[actorid][isdynamic] |= HAS_NAME_DISPLAYED;
			Internal_Update3DActorTextLabel(actorid, isdynamic);
		#endif
		return 1;
	}
	else
	{
		#if !USING_STREAMER
			#if USING_Y_TIMERS
				if(_:Actors_Plus[STATIC_CATEGORY][actorid][eapTimerChatBubble] || !AP_IsValidActor(actorid))
					return 0;
			#else
				if(Actors_Plus[STATIC_CATEGORY][actorid][eapTimerChatBubble] || !AP_IsValidActor(actorid))
					return 0;
			#endif

			if(!(Actors_Flags[actorid][STATIC_CATEGORY] & HAS_NAME_DISPLAYED) || isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapName]) || Actors_Plus[STATIC_CATEGORY][actorid][eapLabel] == Text3D:INVALID_3DTEXT_ID)
				return cellmin;

			Actors_Flags[actorid][STATIC_CATEGORY] &= ~HAS_NAME_DISPLAYED;
			if(!isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText]))
				Internal_Update3DActorTextLabel(actorid);
			else
				DestroyActor3DTextLabel(actorid);
		#else

			if(!(Actors_Flags[actorid][isdynamic] & HAS_NAME_DISPLAYED))
				return cellmin;

			#if USING_Y_TIMERS
				if(_:Actors_Plus[isdynamic][actorid][eapTimerChatBubble] || !AP_IsValidActor(actorid, isdynamic))
					return 0;
			#else
				if(Actors_Plus[isdynamic][actorid][eapTimerChatBubble] || !AP_IsValidActor(actorid, isdynamic))
					return 0;
			#endif

			if(Actors_Plus[isdynamic][actorid][eapLabel] == Text3D:INVALID_3DTEXT_ID || isnull(Actors_Plus[isdynamic][actorid][eapName]))
				return cellmin;

			if(!isnull(Actors_Plus[isdynamic][actorid][eapLabelText]))
				Internal_Update3DActorTextLabel(actorid, isdynamic);
			else
				DestroyActor3DTextLabel(actorid, isdynamic);
			
			Actors_Flags[actorid][isdynamic] &= ~HAS_NAME_DISPLAYED;

		#endif
		return 1;
	}
}

// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if USING_STREAMER
S->SetActorSkin(actorid, skinid, bool:isdynamic = true)
#else
S->SetActorSkin(actorid, skinid)
#endif
{
	#if !USING_STREAMER
		if(!AP_IsValidActor(actorid) || !(0 <= skinid <= 311) || skinid == 74)
			return 0;
		Actors_Plus[STATIC_CATEGORY][actorid][eapSkin] = skinid;
		RecreateActor(actorid);
	#else
		if(!AP_IsValidActor(actorid, isdynamic) || !(0 <= skinid <= 311) || skinid == 74)
			return 0;

		Actors_Plus[isdynamic][actorid][eapSkin] = skinid;
		RecreateActor(actorid, isdynamic);
	#endif
	return 1;
}

// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if USING_STREAMER
S->IsActorDead(actorid, bool:isdynamic = true)
#else
S->IsActorDead(actorid)
#endif
{
	#if !USING_STREAMER
		if(!AP_IsValidActor(actorid))
			return 0;
		return (Actors_Flags[actorid][STATIC_CATEGORY] & IS_DEAD) == IS_DEAD;
	#else
		if(!AP_IsValidActor(actorid, isdynamic))
			return 0;
		return (Actors_Flags[actorid][isdynamic] & IS_DEAD) == IS_DEAD;
	#endif
}

// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if !defined GetActorSkin
	#if USING_STREAMER
	S->GetActorSkin(actorid, bool:isdynamic = true)
	#else
	S->GetActorSkin(actorid)
	#endif
	{
		#if !USING_STREAMER
			if(!AP_IsValidActor(actorid))
				return 0;
			return Actors_Plus[STATIC_CATEGORY][actorid][eapSkin];
		#else
			if(!AP_IsValidActor(actorid, isdynamic))
				return 0;
			return Actors_Plus[isdynamic][actorid][eapSkin];
		#endif
	}
#endif

// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if USING_STREAMER
	S->GetDynamicActorInterior(actorid)
	{
		if(!IsValidDynamicActor(actorid))
			return 0;
		return Actors_Plus[DYNAMIC_CATEGORY][actorid][eapInt];
	}

	S->SetDynamicActorInterior(actorid, interiorid)
	{
		if(!IsValidDynamicActor(actorid))
			return 0;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapInt] = interiorid;
		return RecreateActor(actorid);
	}
#endif

// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if USING_STREAMER
S->Float:GetActorDistanceFromPoint(actorid, Float:x, Float:y, Float:z, bool:isdynamic = true)
#else
S->Float:GetActorDistanceFromPoint(actorid, Float:x, Float:y, Float:z)
#endif
{
	#if !USING_STREAMER
		return (GetDistanceBetween2Points(x, y, z, Actors_Plus[STATIC_CATEGORY][actorid][eapPosX], Actors_Plus[STATIC_CATEGORY][actorid][eapPosY], Actors_Plus[STATIC_CATEGORY][actorid][eapPosZ]));
	#else
		return (GetDistanceBetween2Points(x, y, z, Actors_Plus[isdynamic][actorid][eapPosX], Actors_Plus[isdynamic][actorid][eapPosY], Actors_Plus[isdynamic][actorid][eapPosZ]));
	#endif
}

// =======================================================================================================================================================================================
// ================================================================================ Per player functions =================================================================================
// =======================================================================================================================================================================================
// =======================================================================================================================================================================================


#if USING_PAWN_RAKNET
S->HideActorForPlayer(playerid, actorid, hide_type, bool:isdynamic = true)
{
	if(!IsPlayerConnected(playerid) || !AP_IsValidActor(actorid, isdynamic))
		return 0;

	if(!(hide_type & HIDE_TYPE_ONE_TIME) && !(hide_type & HIDE_TYPE_PERMANENT))
		return cellmin;

	if(hide_type & Player_AP[playerid][isdynamic][actorid])
		return cellmin;

	Player_AP[playerid][isdynamic][actorid] |= hide_type;

	if(isdynamic)
	{
		APD("-> HideActorForPlayer: %i", GetRealActorID(actorid));
		actorid = GetRealActorID(actorid);
	}

	Internal_HideAnActorForPlayer(playerid, actorid);
	return 1;
}

S->BringBackActorForPlayer(playerid, actorid, bool:isdynamic = true)
{
	if(!IsPlayerConnected(playerid) || !AP_IsValidActor(actorid, isdynamic))
		return 0;

	if(!(Player_AP[playerid][isdynamic][actorid] & HIDE_TYPE_ONE_TIME) && !(Player_AP[playerid][isdynamic][actorid] & HIDE_TYPE_PERMANENT))
		return cellmin;

	Player_AP[playerid][isdynamic][actorid] &= ~Player_AP[playerid][isdynamic][actorid];

	if(isdynamic)
	{
		APD("-> BringBackActorForPlayer: %i", GetRealActorID(actorid));
		actorid = GetRealActorID(actorid);
	}

	new BitStream:bit_stream = BS_New(); 
	BS_WriteValue(bit_stream, 
		PR_UINT16, actorid,
		PR_UINT32, Actors_Plus[isdynamic][actorid][eapSkin],
		PR_FLOAT, Actors_Plus[isdynamic][actorid][eapPosX],
		PR_FLOAT, Actors_Plus[isdynamic][actorid][eapPosY],
		PR_FLOAT, Actors_Plus[isdynamic][actorid][eapPosZ],
		PR_FLOAT, Actors_Plus[isdynamic][actorid][eapPosAngle],
		PR_FLOAT, Actors_Plus[isdynamic][actorid][eapHealth]); 

	BS_RPC(bit_stream, playerid, 0xAB); 
	BS_Delete(bit_stream);
	return 1;
}

S->GetRealActorID(actorid)
{
	if(!IsValidDynamicActor(actorid))
		return cellmin;

	for(new i; i < sizeof(Internal_ActorsID); i++)
		if(Internal_ActorsID[i][0] == actorid && Internal_ActorsID[i][1] == DYNAMIC_CATEGORY)
			return i;
	return INVALID_ACTOR_ID;
}

public OnOutcomingRPC(playerid, rpcid, BitStream:bs)
{
	if(rpcid == 0xAB)
	{
		new actor_detected,
			actorid,
			Float:x,
			Float:y,
			Float:z,
			bool:isdynamic;
		BS_ReadUint16(bs, actorid);
		APD("[debug] OnOutcomingRPC- actorid: %i", actorid);
		GetActorPos(actorid, x, y, z);
		actor_detected = GetNearestActorByCoord(x, y, z, 1.0, isdynamic, .return_multiple_target = false);
		APD("[debug] OnOutcomingRPC- actor found: %i", actor_detected);
		if((Player_AP[playerid][isdynamic][actor_detected] & HIDE_TYPE_PERMANENT))
		{
			APD("%i detected as a permanent hidden actor for playerid: %i", actorid, playerid);
			return 0;
		}
	}
	#if defined AP_OnOutcomingRPC
		return AP_OnOutcomingRPC(playerid, rpcid, bs);
	#else
		return 1;
}

#if defined _ALS_OnOutcomingRPC
    #undef OnOutcomingRPC
#else
    #define _ALS_OnOutcomingRPC
#endif
#define OnOutcomingRPC AP_OnOutcomingRPC
#if defined AP_OnOutcomingRPC
	forward AP_OnOutcomingRPC(playerid, rpcid, BitStream:bs);
#endif

static S->Internal_HideAnActorForPlayer(playerid, actorid)
{
	new BitStream:bit_stream = BS_New(); 
	BS_WriteValue(bit_stream, 
		PR_UINT16, actorid);

	BS_RPC(bit_stream, playerid, 0xAC); 
	BS_Delete(bit_stream);
	return 1;
}

#endif


// =======================================================================================================================================================================================
// ================================================================================= Internal functions ==================================================================================
// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if USING_STREAMER
static S->RecreateActor(actorid, bool:isdynamic = true)
#else
static S->RecreateActor(actorid)
#endif
{
	#if !USING_STREAMER
		DestroyActor(actorid);
		Actors_Plus[STATIC_CATEGORY][actorid][eapID] = CreateActor(Actors_Plus[STATIC_CATEGORY][actorid][eapSkin], Actors_Plus[STATIC_CATEGORY][actorid][eapPosX], Actors_Plus[STATIC_CATEGORY][actorid][eapPosY], Actors_Plus[STATIC_CATEGORY][actorid][eapPosZ], Actors_Plus[STATIC_CATEGORY][actorid][eapPosAngle]);
		
		if(Actors_Plus[STATIC_CATEGORY][actorid][eapLabel] != Text3D:INVALID_3DTEXT_ID)
			Internal_Update3DActorTextLabel(actorid);

		SetActorHealth(actorid, Actors_Plus[STATIC_CATEGORY][actorid][eapHealth]);
		SetActorInvulnerable(actorid, ((Actors_Flags[actorid][DYNAMIC_CATEGORY] & IS_INVULNERABLE) == IS_INVULNERABLE));
		return 1;

	#else
	DestroyDynamicActor(actorid);
	Actors_Plus[isdynamic][actorid][eapID] = CreateDynamicActor(Actors_Plus[isdynamic][actorid][eapSkin], Actors_Plus[isdynamic][actorid][eapPosX], Actors_Plus[isdynamic][actorid][eapPosY], Actors_Plus[isdynamic][actorid][eapPosZ], Actors_Plus[isdynamic][actorid][eapPosAngle], Actors_Plus[isdynamic][actorid][eapInvulnerable], Actors_Plus[isdynamic][actorid][eapHealth], Actors_Plus[isdynamic][actorid][eapVW],
		Actors_Plus[isdynamic][actorid][eapInt], Actors_Plus[isdynamic][actorid][eapPlayerid], Actors_Plus[isdynamic][actorid][eapStreamDistance], Actors_Plus[isdynamic][actorid][eapAreaid], Actors_Plus[isdynamic][actorid][eapPriority]);

	if(Actors_Plus[isdynamic][actorid][eapLabel] != Text3D:INVALID_3DTEXT_ID)
		Internal_Update3DActorTextLabel(actorid);
	SetDynamicActorHealth(actorid, Actors_Plus[isdynamic][actorid][eapHealth]);
	SetDynamicActorInvulnerable(actorid, ((Actors_Flags[actorid][isdynamic] & IS_INVULNERABLE) == IS_INVULNERABLE));
	return 1;
	#endif
}

// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if USING_STREAMER
static S->AP_IsValidActor(actorid, bool:isdynamic)
#else
static S->AP_IsValidActor(actorid)
#endif
{
	#if !USING_STREAMER
		#if USING_Y_ITERATE
			if(!Iter_Contains(Static_Actors, actorid))
				return 0;
		#else
			if(!(0 <= actorid <= MAX_ACTORS) || !(Actors_Flags[actorid][DYNAMIC_CATEGORY] & IS_EXISTING))
				return 0;
		#endif
		return 1;

	#else

		#if !USING_Y_ITERATE
			if(!(0 <= actorid <= MAX_ACTORS) || !(Actors_Flags[actorid][isdynamic] & IS_EXISTING))
				return 0;
		#else
		if(!isdynamic)
		{
			if(!Iter_Contains(Static_Actors, actorid))
				return 0;
		}

		else
		{
			if(!Iter_Contains(Dynamic_Actors, actorid))
				return 0;
		}
		#endif
		return 1;
	#endif
}

// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

static stock Format3DActorTextLabel(actorid, bool:name, bool:text, bool:isdynamic = true)
{
	new formatted_label[300];
	if(name)
		strcat(formatted_label, Actors_Plus[isdynamic][actorid][eapName]);

	if(text)
	{
		if(isnull(formatted_label))
			strcat(formatted_label, Actors_Plus[isdynamic][actorid][eapLabelText]);
		else
			format(formatted_label, sizeof(formatted_label), "%s\n%s", Actors_Plus[isdynamic][actorid][eapName], Actors_Plus[isdynamic][actorid][eapLabelText]);
	}
	return formatted_label;
}

#if USING_STREAMER
static stock Internal_Update3DActorTextLabel(actorid, bool:isdynamic = true)
#else
static stock Internal_Update3DActorTextLabel(actorid)
#endif
{
	#if USING_STREAMER

		if(Actors_Plus[isdynamic][actorid][eapLabel] == Text3D:INVALID_3DTEXT_ID)
			Attach3DTextLabelToActor(actorid, Format3DActorTextLabel(actorid, !isnull(Actors_Plus[isdynamic][actorid][eapName]) && (Actors_Flags[actorid][isdynamic] & HAS_NAME_DISPLAYED), !isnull(Actors_Plus[isdynamic][actorid][eapLabelText]) && (Actors_Flags[actorid][isdynamic] & HAS_TEXT_DISPLAYED)), isdynamic, Actors_Plus[isdynamic][actorid][eapLabelColor], Actors_Plus[isdynamic][actorid][eapLabelPosX], Actors_Plus[isdynamic][actorid][eapLabelPosY], Actors_Plus[isdynamic][actorid][eapLabelPosZ], Actors_Plus[isdynamic][actorid][eapLabelDrawDistance], .store_string = false);
		else
			Update3DTextLabelText(Actors_Plus[isdynamic][actorid][eapLabel], Actors_Plus[isdynamic][actorid][eapLabelColor], Format3DActorTextLabel(actorid, !isnull(Actors_Plus[isdynamic][actorid][eapName]) && (Actors_Flags[actorid][isdynamic] & HAS_NAME_DISPLAYED), !isnull(Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelText]) && (Actors_Flags[actorid][isdynamic] & HAS_TEXT_DISPLAYED)));
	#else
		if(Actors_Plus[STATIC_CATEGORY][actorid][eapLabel] == Text3D:INVALID_3DTEXT_ID)
			Attach3DTextLabelToActor(actorid, Format3DActorTextLabel(actorid, !isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapName]) && (Actors_Flags[actorid][STATIC_CATEGORY] & HAS_NAME_DISPLAYED), !isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText]) && (Actors_Flags[actorid][STATIC_CATEGORY] & HAS_TEXT_DISPLAYED), false), Actors_Plus[STATIC_CATEGORY][actorid][eapLabelColor], Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelPosX], Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelPosY], Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelPosZ], Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabelDrawDistance], .store_string = false);
		else
			Update3DTextLabelText(Actors_Plus[STATIC_CATEGORY][actorid][eapLabel], Actors_Plus[STATIC_CATEGORY][actorid][eapLabelColor], Format3DActorTextLabel(actorid, !isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapName]) && (Actors_Flags[actorid][STATIC_CATEGORY] & HAS_NAME_DISPLAYED), !isnull(Actors_Plus[STATIC_CATEGORY][actorid][eapLabelText]) && (Actors_Flags[actorid][STATIC_CATEGORY] & HAS_TEXT_DISPLAYED), false));
	#endif
}

static S->AP_ReturnFreeEmplacement()
{
	for(new i; i < sizeof(Internal_ActorsID); i++)
		if(Internal_ActorsID[i][0] == INVALID_ACTOR_ID)
			return i;
	return INVALID_ACTOR_ID;
}

// =======================================================================================================================================================================================
// =========================================================================== Hooked native functions ===================================================================================
// =======================================================================================================================================================================================
// =======================================================================================================================================================================================

#if USING_STREAMER

	stock AP_CreateDynamicActor(modelid, Float:x, Float:y, Float:z, Float:r, invulnerable = 1, Float:health = 100.0, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_ACTOR_SD, STREAMER_TAG_AREA areaid = STREAMER_TAG_AREA -1, priority = 0)
	{
		new actorid;
		actorid = CreateDynamicActor(modelid, x, y, z, r, invulnerable, health, worldid, interiorid, playerid, streamdistance, areaid, priority);
		if(actorid == INVALID_ACTOR_ID)
			return INVALID_ACTOR_ID;

		#if USING_Y_ITERATE
			Iter_Add(Dynamic_Actors, actorid);
		#endif

		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapID] = actorid;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapSkin] = modelid;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapPosX] = x;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapPosY] = y;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapPosZ] = z;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapPosAngle] = r;

		#if !USING_Y_ITERATE
			new new_real_actorid = AP_ReturnFreeEmplacement();
			APD("[CreateDynamicActor()] new_real_actorid -> %i", new_real_actorid);
			Actors_Flags[actorid][DYNAMIC_CATEGORY] |= IS_EXISTING;
			Internal_ActorsID[new_real_actorid][0] = actorid;
			Internal_ActorsID[new_real_actorid][1] = DYNAMIC_CATEGORY;
		#else
			Iter_Add(Dynamic_Actors, actorid);
			Iter_Add(Internal_ActorsID, actorid);
		#endif

		if(invulnerable)
			Actors_Flags[actorid][DYNAMIC_CATEGORY] |= IS_INVULNERABLE;

		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapHealth] = health;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapVW] = worldid;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapInt] = interiorid;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapPlayerid] = playerid;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapStreamDistance] = streamdistance;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapAreaid] = areaid;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapPriority] = priority;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLabel] = Text3D:INVALID_3DTEXT_ID;
		#if defined OnActorSpawn
			OnActorSpawn(actorid, true);
		#endif
		APD("CreateDynamicActor: %i created (realid: %i)", actorid, GetRealActorID(actorid));
		return actorid;
	}

	#if defined _ALS_CreateDynamicActor
	    #undef CreateDynamicActor
	#else
	    #define _ALS_CreateDynamicActor
	#endif
	#define CreateDynamicActor AP_CreateDynamicActor

	stock AP_DestroyDynamicActor(STREAMER_TAG_ACTOR actorid)
	{
		APD("Dynamic actorid %i has been destroyed.", actorid);
		new reset_var[E_ACTOR_PLUS_DATA];
		#if USING_Y_ITERATE
			new real_actorid;
			foreach(new i : Internal_ActorsID)
			{
				if(Internal_ActorsID[i] == actorid)
				{
					real_actorid = i;
					break;
				}
			}
			Iter_Remove(Dynamic_Actors, actorid);
			Iter_Remove(Internal_ActorsID[real_actorid], actorid);
		#else
			new real_actorid = GetRealActorID(actorid);
			APD("[DestroyDynamicActor()] real_actorid: DYA -> %i", real_actorid);
			Internal_ActorsID[real_actorid][0] = INVALID_ACTOR_ID;
			Actors_Flags[actorid][DYNAMIC_CATEGORY] &= ~IS_EXISTING;
		#endif
		Actors_Plus[DYNAMIC_CATEGORY][actorid] = reset_var;
		Actors_Flags[actorid][DYNAMIC_CATEGORY] = E_ACTOR_PLUS_FLAGS:0;
		return DestroyDynamicActor(actorid);
	}

	#if defined _ALS_DestroyDynamicActor
	    #undef DestroyDynamicActor
	#else
	    #define _ALS_DestroyDynamicActor
	#endif
	#define DestroyDynamicActor AP_DestroyDynamicActor


	stock AP_SetDynamicActorHealth(STREAMER_TAG_ACTOR actorid, Float:health)
	{
		if(!IsValidDynamicActor(actorid))
			return 0;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapHealth] = health;
		if((Actors_Flags[actorid][DYNAMIC_CATEGORY] & IS_DEAD) && health > 0.0)
			Actors_Flags[actorid][DYNAMIC_CATEGORY] &= ~IS_DEAD;

		if(health <= 0.0)
		{
			#if defined OnActorDeath
				OnActorDeath(actorid, INVALID_ACTOR_ID, WEAPON_DROWN, true);
			#endif
			Actors_Flags[actorid][DYNAMIC_CATEGORY] |= IS_DEAD;
		}

		return SetDynamicActorHealth(actorid, health);
	}

	#if defined _ALS_SetDynamicActorHealth
	    #undef SetDynamicActorHealth
	#else
	    #define _ALS_SetDynamicActorHealth
	#endif
	#define SetDynamicActorHealth AP_SetDynamicActorHealth

	stock AP_SetDynamicActorInvulnerable(STREAMER_TAG_ACTOR actorid, invulnerable = 1)
	{
		if(!SetDynamicActorInvulnerable(actorid, invulnerable))
			return 0;
		if(invulnerable)
			Actors_Flags[actorid][DYNAMIC_CATEGORY] |= IS_INVULNERABLE;
		else
			Actors_Flags[actorid][DYNAMIC_CATEGORY] &= ~IS_INVULNERABLE;
		return 1;
	}

	#if defined ALS_SetDynamicActorInvulnerable
	    #undef SetDynamicActorInvulnerable
	#else
	    #define ALS_SetDynamicActorInvulnerable
	#endif
	#define SetDynamicActorInvulnerable AP_SetDynamicActorInvulnerable

	stock AP_ApplyDynamicActorAnimation(STREAMER_TAG_ACTOR actorid, animlib[], animname[], Float:fdelta, loop, lockx, locky, freeze, time)
	{
		if(!IsValidDynamicActor(actorid))
			return 0;
		strcpy(Actors_Plus[DYNAMIC_CATEGORY][actorid][eapAnimLib], animlib, MAX_ANIMATION_LIBRARY_LENGTH);
		strcpy(Actors_Plus[DYNAMIC_CATEGORY][actorid][eapAnimName], animlib, MAX_ANIMATION_NAME_LENGTH);
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapDelta] = fdelta;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLoop] = loop;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLockx] = lockx;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapLocky] = locky;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapFreeze] = freeze;
		Actors_Plus[DYNAMIC_CATEGORY][actorid][eapTime] = time;
		return ApplyDynamicActorAnimation(actorid, animlib, animname, fdelta, loop, lockx, locky, freeze, time);
	}

	#if defined _ALS_ApplyDynamicActorAnimation
	    #undef ApplyDynamicActorAnimation
	#else
	    #define _ALS_ApplyDynamicActorAnimation
	#endif
	#define ApplyDynamicActorAnimation AP_ApplyDynamicActorAnimation


#endif // #if USING_STREAMER

stock AP_ApplyActorAnimation(actorid, animlib[], animname[], Float:fdelta, loop, lockx, locky, freeze, time)
{
	if(!IsValidActor(actorid))
		return 0;
	strcpy(Actors_Plus[STATIC_CATEGORY][actorid][eapAnimLib], animlib, MAX_ANIMATION_LIBRARY_LENGTH);
	strcpy(Actors_Plus[STATIC_CATEGORY][actorid][eapAnimName], animlib, MAX_ANIMATION_NAME_LENGTH);
	Actors_Plus[STATIC_CATEGORY][actorid][eapDelta] = fdelta;
	Actors_Plus[STATIC_CATEGORY][actorid][eapLoop] = loop;
	Actors_Plus[STATIC_CATEGORY][actorid][eapLockx] = lockx;
	Actors_Plus[STATIC_CATEGORY][actorid][eapLocky] = locky;
	Actors_Plus[STATIC_CATEGORY][actorid][eapFreeze] = freeze;
	Actors_Plus[STATIC_CATEGORY][actorid][eapTime] = time;
	return ApplyActorAnimation(actorid, animlib, animname, fdelta, loop, lockx, locky, freeze, time);
}

#if defined _ALS_ApplyActorAnimation
    #undef ApplyActorAnimation
#else
    #define _ALS_ApplyActorAnimation
#endif
#define ApplyActorAnimation AP_ApplyDynamicActorAnimation



stock AP_CreateActor(modelid, Float:X, Float:Y, Float:Z, Float:Rotation)
{
	new actorid;
	actorid = CreateActor(modelid, X, Y, Z, Rotation);
	if(actorid == INVALID_ACTOR_ID)
		return INVALID_ACTOR_ID;

	#if USING_Y_ITERATE
		Iter_Add(Static_Actors, actorid);
	#endif

	Actors_Plus[STATIC_CATEGORY][actorid][eapID] = actorid;
	Actors_Plus[STATIC_CATEGORY][actorid][eapSkin] = modelid;
	Actors_Plus[STATIC_CATEGORY][actorid][eapPosX] = X;
	Actors_Plus[STATIC_CATEGORY][actorid][eapPosY] = Y;
	Actors_Plus[STATIC_CATEGORY][actorid][eapPosZ] = Z;
	Actors_Plus[STATIC_CATEGORY][actorid][eapHealth] = 100.0;
	Actors_Plus[STATIC_CATEGORY][actorid][eapPosAngle] = Rotation;
	Actors_Plus[STATIC_CATEGORY][actorid][eapLabel] = Text3D:INVALID_3DTEXT_ID;
	#if defined OnActorSpawn
		OnActorSpawn(actorid, false);
	#endif
	#if !USING_Y_ITERATE
		Actors_Flags[actorid][STATIC_CATEGORY] |= IS_EXISTING;
		new new_real_actorid = AP_ReturnFreeEmplacement();
		APD("[CreateActor()] Returned AP_ReturnFreeEmplacement: %i", new_real_actorid);
		Internal_ActorsID[new_real_actorid][0] = actorid;
		Internal_ActorsID[new_real_actorid][1] = STATIC_CATEGORY;
	#else
		Iter_Add(Static_Actors, actorid);
		Iter_Add(Internal_ActorsID[AP_ReturnFreeEmplacement()], actorid);
	#endif
	APD("CreateActor: %i created. (internal id: %i)", actorid, GetRealActorID(actorid));
	return actorid;
}

stock AP_DestroyActor(actorid)
{
	APD("Normal actorid %i has been destroyed.", actorid);
	#if USING_Y_ITERATE
		Iter_Remove(Static_Actors, actorid);
		Iter_Remove(Internal_ActorsID, actorid);
	#else
		APD("[AP_DestroyActor()] actorid: DYA -> %i", actorid);
		Internal_ActorsID[actorid][0] = INVALID_ACTOR_ID;
		Actors_Flags[actorid][STATIC_CATEGORY] &= ~IS_EXISTING;
	#endif
	new reset_var[E_ACTOR_PLUS_DATA];
	Actors_Plus[STATIC_CATEGORY][actorid] = reset_var;
	Actors_Flags[actorid][STATIC_CATEGORY] = E_ACTOR_PLUS_FLAGS:0;
	return DestroyActor(actorid);
}


#if defined _ALS_CreateActor
    #undef CreateActor
#else
    #define _ALS_CreateActor
#endif
#define CreateActor AP_CreateActor

#if defined _ALS_DestroyActor
    #undef DestroyActor
#else
    #define _ALS_DestroyActor
#endif
#define DestroyActor AP_DestroyActor

stock AP_SetActorHealth(actorid, Float:health)
{
	if(!IsValidActor(actorid))
		return 0;
	Actors_Plus[STATIC_CATEGORY][actorid][eapHealth] = health;
	if((Actors_Flags[actorid][STATIC_CATEGORY] & IS_DEAD) && health > 0.0)
		Actors_Flags[actorid][STATIC_CATEGORY] &= ~IS_DEAD;

	if(health <= 0.0)
	{
		#if defined OnActorDeath
			OnActorDeath(actorid, INVALID_ACTOR_ID, WEAPON_DROWN, false);
		#endif
		Actors_Flags[actorid][STATIC_CATEGORY] |= IS_DEAD;
	}

	return SetActorHealth(actorid, health);
}

#if defined _ALS_SetActorHealth
    #undef SetActorHealth
#else
    #define _ALS_SetActorHealth
#endif
#define SetActorHealth AP_SetActorHealth


stock AP_SetActorInvulnerable(actorid, invulnerable = true)
{
	if(!SetActorInvulnerable(actorid, invulnerable))
		return 0;
	if(invulnerable)
		Actors_Flags[actorid][STATIC_CATEGORY] |= IS_INVULNERABLE;
	else
		Actors_Flags[actorid][STATIC_CATEGORY] &= ~IS_INVULNERABLE;
	SetActorPos(actorid, 999.0, 999.0, 999.0);
	#if USING_Y_TIMERS
		defer AP_ReplaceActor(actorid);
	#else
		SetTimerEx("@AP_ReplaceActor", DEFAULT_ACTOR_REPLACEMENT, 0, "i", actorid);
	#endif
	return 1;
}

#if USING_Y_TIMERS
	timer AP_ReplaceActor[DEFAULT_ACTOR_REPLACEMENT](actorid)
	{
		SetActorPos(actorid, Actors_Plus[STATIC_CATEGORY][actorid][eapPosX], Actors_Plus[STATIC_CATEGORY][actorid][eapPosY], Actors_Plus[STATIC_CATEGORY][actorid][eapPosZ]);
		SetActorFacingAngle(actorid, Actors_Plus[STATIC_CATEGORY][actorid][eapPosAngle]);
		APD("%i called: AP_ReplaceActor()", actorid);
		return 1;
	}
#else
	forward @AP_ReplaceActor(actorid);
	@AP_ReplaceActor(actorid)
	{
		SetActorPos(actorid, Actors_Plus[STATIC_CATEGORY][actorid][eapPosX], Actors_Plus[STATIC_CATEGORY][actorid][eapPosY], Actors_Plus[STATIC_CATEGORY][actorid][eapPosZ]);
		SetActorFacingAngle(actorid, Actors_Plus[STATIC_CATEGORY][actorid][eapPosAngle]);
		APD("%i called: AP_ReplaceActor()", actorid);
		return 1;
	}
#endif

#if defined _ALS_SetActorInvulnerable
    #undef SetActorInvulnerable
#else
    #define _ALS_SetActorInvulnerable
#endif
#define SetActorInvulnerable AP_SetActorInvulnerable