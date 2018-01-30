# actor_plus
An include with a bunch of useful functions and callback for actors.
Functions returning 1 on success, 0 on failure or cellmin for specific failure. Please, check the wiki for more specific informations.

***Actual version:*** *public - beta v3.0.00*

## Documentation
### Constant
#### Can not be redefined
* `MULTIPLE_TARGET_FOUND`: Returned by `GetNearestActorForPlayer` or `GetNearestActorByCoord` when multiple actors are found and when `return_multiple_target` is set to `true`
* `DEFAULT_ACTOR_VALUE`: Using this one instead of any other value result taking the value from the actor
* `DEFAULT_CHECKING_TIME`: Used to detect `OnPlayerTargetActor`
* `ALL_VALUES_INCLUDED`: If `ALL_VALUES_INCLUDED` is returned by a function, it means it will appear at every stage (like interior or virtual world)
* `DEFAULT_ACTOR_REPLACEMENT`: Time before an actor is being re-placed at his old position.
* `AP_DEBUG_ENABLED`: If some debugs printed messages are needed
* `MAX_ANIMATION_LIBRARY_LENGTH`: Maximum animation library length name
* `MAX_ANIMATION_NAME_LENGTH`: Maximum animation length name (need to be modified)
* `DEFAULT_IS_DYNAMIC_PARAMETER`: Set to `true` if streamer is included otherwise, it set to `false`
* `DONT_DETECT_OPTA`: You can define it before the include to deactivated `OnPlayerTargetActor` detection (which using timer). 

#### Can be redefined
* `DEFAULT_ACTOR_DRAW_DISTANCE`: Distance that label is displayed
* `MAX_ACTOR_LABEL_LENGTH`: Max length for a text in a label
* `DEFAULT_ACTOR_COLOR`: Default actor color name

### General functions
```pawn
native RespawnActor(actorid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native SetActorName(actorid, actor_name[], bool:display, bool:contain_id = false, bool:reformat_label = false, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native GetActorName(actorid, actor_name[], length = sizeof(actor_name), bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native GetActorTextLabel(actorid, text[], length = sizeof(text), bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native ActorHasAttachedLabel(actorid, &bool:name_displayed = false, &bool:text_displayed = false, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native UpdateAttachedActor3DTextLabel(actorid, text[], color, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native SetActorChatBubble(actorid, const text[], color, Float:drawdistance, expiretime, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native DestroyActor3DTextLabel(actorid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native ToggleActorName(actorid, bool:toggle, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native SetActorSkin(actorid, skinid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native IsActorDead(actorid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native GetActorSkin(actorid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
``` 

### Functions - Streamer dependency
```pawn
native Attach3DTextLabelToActor(actorid, const text[], bool:isdynamic, color, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:drawdistance, testlos = 0, worldid = DEFAULT_ACTOR_VALUE, interiorid = DEFAULT_ACTOR_VALUE, playerid = DEFAULT_ACTOR_VALUE, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = DEFAULT_ACTOR_VALUE, priority = 0, bool:store_string = true);

// In addition to the streamer
native GetDynamicActorInterior(actorid);
native SetDynamicActorInterior(actorid, interiorid);

// Used to get the real internal actor id used by SA-MP
native GetRealActorID(actorid);
```

### Functions - Non-Streamer dependency
```pawn
native Attach3DTextLabelToActor(actorid, const text[], color, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:drawdistance, virtualworld = DEFAULT_ACTOR_VALUE, testlos = 0, bool:store_string = true);
```

### Useful functions (none include needed)
```pawn
native GetNearestActorForPlayer(playerid, Float:range = 2.0, &bool:IsDynamic = false, type = SEARCH_TYPE_ALL, bool:return_multiple_target = true);
native GetNearestActorByCoord(Float:x, Float:y, Float:z, Float:range = 2.0, &bool:IsDynamic = false, type = SEARCH_TYPE_ALL, bool:return_multiple_target = true);
native Float:GetActorDistanceFromPoint(actorid, Float:x, Float:y, Float:z, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native IsPlayerInRangeOfActor(playerid, actorid, Float:range = 2.0, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native IsPlayerAimingActor(playerid, actorid); // Returning 0 everytime if `DONT_DETECT_OPTA` is defined
native IsActorInPlayerFacingAngle(playerid, actorid, Float:max_angle = 90.0, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
```

#### Type of research:
* `SEARCH_TYPE_DYNAMIC`: Search only for dynamics actors
* `SEARCH_TYPE_STATIC`: Search only for statics actors
* `SEARCH_TYPE_ALL`: Search for dynamics **and** statics actors

## Per-players functions (PawnRakNet dependency)
```pawn
native HideActorForPlayer(forplayerid, actorid, hide_type, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native BringBackActorForPlayer(forplayerid, actorid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native SetActorHideTypeForPlayer(forplayerid, actorid, hide_type, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native RemoveAllHiddenActorForPlayer(playerid);

native ApplyActorAnimationForPlayer(forplayerid, actorid, repeated_animation, animlib[], animname[], Float:fDelta, loop, lockx, locky, freeze, time, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
native ClearActorAnimationsForPlayer(forplayerid, actorid, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);

native SetActorPosForPlayer(forplayerid, actorid, fake_position_type, Float:x, Float:y, Float:z, bool:isdynamic = DEFAULT_IS_DYNAMIC_PARAMETER);
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
forward OnPlayerMakeDamageToActor(playerid, damaged_actorid, Float:amount, weaponid, bodypart, bool:death, bool:IsDynamicActor);
forward OnActorDeath(actorid, killerid, reason, bool:IsDynamicActor);
forward OnActorSpawn(actorid, bool:IsDynamicActor);
forward OnPlayerStreamForActor(forplayerid, actorid, actor_flags, bool:IsDynamicActor);
```

### Explanations
* `OnPlayerShotActor`: Called when a player shot an actor even if the actor is invulnerable
* `OnPlayerTargetActor`: Called when a player aim an actor.
* `OnPlayerMakeDamageToActor`: Called when a player damage an actor with a **firearm**. `bool:death` is set to `true` when the actor will die after processing damage.
***Returning 0 to this call prevent applying damage to the actor.***
* `OnActorDeath`: Called when a actor die. *Set actor's HP to 0 trigger this callback too.*
* `OnActorSpawn`: Called when a player spawn (is created).
* `OnPlayerStreamForActor`: Called when a player stream **IN** and actor even if the actor is hidden for the player.
***Important***: actor_flags should be used with different flags type defined below

### **HUGE** thank you to Jelly23 for his precious help and time to help me by answering hundred and hundred of my questions about PawnRakNet and other stuffs. Thanks also to Y_Less for fixing issues about hooking callbacks.