# actor_plus
An include with a bunch of useful functions and callback for actors.
Functions returning 1 on success, 2 for specific success, 0 on failure or cellmin for specific failure. Please, check the wiki for more specific informations.

***Actual version:*** *v5.0.3*

## Documentation
### Constant
#### Can not be redefined
* `MULTIPLE_TARGET_FOUND`: Returned by `GetNearestActorForPlayer` or `GetNearestActorByCoord` when multiple actors are found and when `return_multiple_target` is set to `true`
* `DEFAULT_ACTOR_VALUE`: Using this one instead of any other value result taking the value from the actor
* `DEFAULT_CHECKING_TIME`: Used to detect `OnPlayerTargetActor`
* `DEFAULT_ACTOR_REPLACEMENT`: Time before an actor is being re-placed at his old position.
* `AP_DEBUG_ENABLED`: If some debugs printed messages are needed
* `MAX_ANIMATION_LIBRARY_LENGTH`: Maximum animation library length name
* `MAX_ANIMATION_NAME_LENGTH`: Maximum animation length name
* `DEFAULT_IS_DYNAMIC_PARAMETER`: Set to `true` if streamer is included otherwise, it set to `false`

#### Can be redefined
* `DEFAULT_ACTOR_DRAW_DISTANCE`: Distance that label is displayed | (type: `float` - value: `13.0`)
* `MAX_ACTOR_LABEL_LENGTH`: Max length for a text in a label | (type: `integer` - value: `60`)
* `DEFAULT_ACTOR_COLOR`: Default actor color text | (type: `hexadecimal` - value: `0xFFFFFFFF`)
* `DEFAULT_ACTOR_COLOR_NAME`: Default actor color name | (type: `hexadecimal` - value: `0x6699FFFF`)
* `DONT_DETECT_OPTA`: You can define it before the include to deactivated `OnPlayerTargetActor` detection (which using timer) | (type: `N/A`)
* `DEFAULT_TEXT_RANGE_DETECTION`: This allows you to change the distance at which the actor (for `OnPlayerTextNearActor` **only**) is detected | (type: `float` - value: `3.0`)

#### Force disabling include
You can force disabling include by using these constants:
```pawn
#define FORCE_DISABLED_Y_ITERATE
#define FORCE_DISABLED_Y_TIMERS
#define FORCE_DISABLED_PAWNRAKNET
#define FORCE_DISABLED_STREAMER
```

### General functions
```pawn
native RespawnActor(actorid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native SetActorSkin(actorid, skinid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native IsActorDead(actorid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native GetActorSkin(actorid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native ActorPlaySound(actorid, soundid, Float:x, Float:y, Float:z, Float:max_range, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);

native SetActorName(actorid, actor_name[], bool:display, color = DEFAULT_ACTOR_COLOR_NAME, bool:contain_id = false, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native RemoveActorName(actorid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native GetActorName(actorid, actor_name[], length = sizeof(actor_name), bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native ToggleActorName(actorid, bool:toggle, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native SetActorNameColor(actorid, color, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native GetActorLabelColor(actorid, bool:ToRGB = false, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER); // output -> RGBA

native GetActorTextLabel(actorid, text[], length = sizeof(text), bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native GetActorNameColor(actorid, bool:ToRGB = false, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER); // output -> RGBA
native SetActorLabelColor(actorid, color, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native ActorHasAttachedLabel(actorid, &bool:name_displayed = false, &bool:text_displayed = false, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native UpdateAttachedActor3DTextLabel(actorid, const text[], color, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native DestroyActor3DTextLabel(actorid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);

native SetActorChatBubble(actorid, text[], color, Float:drawdistance, expiretime, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
```

### Functions - Streamer dependency
```pawn
native Attach3DTextLabelToActor(actorid, const text[], bool:isdynamic, color, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:drawdistance, testlos = 0, worldid = DEFAULT_ACTOR_VALUE, interiorid = DEFAULT_ACTOR_VALUE, playerid = DEFAULT_ACTOR_VALUE, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = DEFAULT_ACTOR_VALUE, priority = 0, bool:store_string = true);

// Used to get the real internal actor id used by SA-MP
native GetInternalActorIDForPlayer(forplayerid, actorid);

// In addition to the streamer
native GetDynamicActorInterior(actorid);
native SetDynamicActorInterior(actorid, interiorid);
native DestroyAllDynamicActors(serverwide);
native CountDynamicActors(serverwide);
native UpdateDynamicActorForPlayer(playerid);
native CountStreamedActorForPlayer(playerid, serverwide);
native STREAMER_TAG_AREA:GetDynamicActorArea(actorid);
native SetDynamicActorArea(actorid, STREAMER_TAG_AREA:areaid);
native GetDynamicActorPriority(actorid);
native SetDynamicActorPriority(actorid, priority);
native GetInternalActorIdForPlayer(forplayerid, actorid);
```

### Functions - Non-Streamer dependency
```pawn
native Attach3DTextLabelToActor(actorid, text[], color, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:drawdistance, virtualworld = DEFAULT_ACTOR_VALUE, testlos = 0, bool:store_string = true);
native SetActorInvulnerable(actorid, invulnerable = true); // Force actor re-stream
native SetActorVirtualWorld(actorid, vworld); // Force actor re-stream
native SetActorFacingAngle(actorid, Float:ang); // Force actor re-stream
native CountStaticActors();
```

### Useful functions (none include needed)
```pawn
native GetNearestActorForPlayer(playerid, &bool:isdynamic = false, type = SEARCH_TYPE_ALL, bool:return_multiple_target = false);
native GetNearestActorByCoord(Float:x, Float:y, Float:z, &bool:isdynamic = false, type = SEARCH_TYPE_ALL, bool:return_multiple_target = false, Float:max_range = INVALID_RANGE_ID);
native Float:GetActorDistanceFromPoint(actorid, Float:x, Float:y, Float:z, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native IsPlayerInRangeOfActor(playerid, actorid, Float:range = 2.0, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native IsPlayerAimingActor(playerid, actorid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native IsActorInPlayerFacingAngle(playerid, actorid, Float:max_angle = 90.0, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);

native GetActorSpawnInfo(actorid, &skinid, &Float:fX, &Float:fY, &Float:fZ, &Float:fAngle, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native GetActorAnimationName(actorid, animlib[], size_animlib = sizeof(animlib), animname[], size_animname = sizeof(animname)); // Static actors only
native GetActorAnimation(actorid, animlib[], size_animlib = sizeof(animlib), animname[], size_animname = sizeof(animname), &Float:fDelta, &loop, &lockx, &locky, &freeze, &time); // Static actors only
native ToggleActorAnimationLoop(actorid, bool:toggle); // Static actors only
native bool:IsActorPlayingAnimation(actorid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);

native CountAllActors();
```

#### Type of research:
* `SEARCH_TYPE_DYNAMIC`: Search only for dynamics actors
* `SEARCH_TYPE_STATIC`: Search only for statics actors
* `SEARCH_TYPE_ALL`: Search for dynamics **and** statics actors

## Per-players functions (Pawn RakNet dependency)
```pawn
native HideActorForPlayer(forplayerid, actorid, hide_type, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native BringBackActorForPlayer(forplayerid, actorid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native SetActorHideTypeForPlayer(forplayerid, actorid, hide_type, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native RemoveAllHiddenActorForPlayer(playerid);

native ApplyActorAnimationForPlayer(forplayerid, actorid, repeated_animation, animlib[], animname[], Float:fDelta, loop, lockx, locky, freeze, time, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native ClearActorAnimationsForPlayer(forplayerid, actorid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);

native SetActorPosForPlayer(forplayerid, actorid, fake_position_type, Float:x, Float:y, Float:z, Float:angle, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native BringBackActorPosForPlayer(forplayerid, actorid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
```

### Actor Flags
#### Hide type
* `HIDE_TYPE_NONE`: Default value
* `HIDE_TYPE_ONE_TIME`: The actor will be hidden one time and reappear when it be streamed
* `HIDE_TYPE_PERMANENT`: The actor will be hidden until the script make it come back even if the player re-stream the actor

#### Repeated animation type
* `ANIMATION_PLAY_NONE`: Default value
* `ANIMATION_PLAY_ONE_TIME`: The actor will play an animation one time and stop it when it be streamed even if the animation is looped
* `ANIMATION_PLAY_PERMANENT`: The actor will permently play the same animation. Restream the actor doesn't stop the process

#### Per players positions type
* `FAKE_POSITION_NONE`: Default value
* `FAKE_POSITION_ONE_TIME`: The actor will be placed, one time, at the specified coordinates. Re-stream the actor will place him at server sided coordinates
* `FAKE_POSITION_PERMANENT`: The actor will be placed at specified coordinates. Re-stream it won't change anything the coordinates.

## Callbacks
```pawn
forward OnPlayerShotActor(playerid, actorid, weaponid, bool:IsDynamicActor);
forward OnPlayerTargetActor(playerid, actorid, weaponid);
forward OnPlayerStopTargetActor(playerid, actorid, weaponid);
forward OnPlayerMakeDamageToActor(playerid, damaged_actorid, Float:amount, weaponid, bodypart, bool:death, bool:IsDynamicActor);
forward OnActorDeath(actorid, killerid, reason, bool:IsDynamicActor);
forward OnActorSpawn(actorid, bool:IsDynamicActor);
forward OnPlayerStreamForActor(forplayerid, actorid, actor_flags, bool:IsDynamicActor); // Pawn RakNet dependency
forward OnActorVirtualWorldChange(actorid, oldvw, newvw, bool:IsDynamicActor);
forward OnPlayerTextNearActor(playerid, actorid, text[], bool:IsDynamicActor);
forward OnDynamicActorInteriorChange(actorid, oldinterior, newinteriorid);
```

### Explanations
* `OnPlayerShotActor`: Called when a player shot an actor even if the actor is invulnerable
* `OnPlayerTargetActor`: Called when a player aim an actor.
* `OnPlayerStopTargetActor`: Called when a player stop aiming an actor.
* `OnPlayerMakeDamageToActor`: Called when a player damage an actor with a **firearm**. `bool:death` is set to `true` when the actor will die after processing damage.
***Returning 0 to this call prevent applying damage to the actor.***
* `OnActorDeath`: Called when a actor die. *Set actor's HP to 0 trigger this callback too.*
* `OnActorSpawn`: Called when a player spawn (is created).
* `OnPlayerStreamForActor`: Called when a player stream **IN** an actor even if the actor is hidden for the player.
***Important: actor_flags should be used with different flags type defined below***
* `OnActorVirtualWorldChange`: Called when a virtualworld is set to an actor
* `OnPlayerTextNearActor`: Called when a player chat near an actor
* `OnDynamicActorInteriorChange`: Called when an interior is set to a dynamic actor

### **HUGE** thank you to Jelly23 for his precious help and time to help me by answering hundred and hundred of my questions about PawnRakNet and other stuffs. Thanks also to Y_Less for fixing issues about hooking callbacks.
