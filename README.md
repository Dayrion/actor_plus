# actor_plus
An include with a bunch of useful functions and callback for actors.
Functions returning 1 on success, 0 on failure or cellmin for specific failure. Please, check the wiki for more specific informations.

### *Actual version:* public - beta v2.0.0

## Documentation
### Constant
#### Can not be redefined
* `MULTIPLE_TARGET_FOUND`: Returned by `GetNearestActorForPlayer` or `GetNearestActorByCoord` when multiple actors are found and when `return_multiple_target` is set to `true`.
* `DEFAULT_ACTOR_VALUE`: Using this one instead of any other value result taking the value from the actor.
* `DEFAULT_CHECKING_TIME`: Used to detect `OnPlayerTargetActor`.
* `ALL_VALUES_INCLUDED`: If `ALL_VALUES_INCLUDED` is returned by a function, it means it will appear at every stage (like interior or virtual world).
* `DEFAULT_ACTOR_REPLACEMENT`: Time before an actor is being re-placed at his old position.
* `AP_DEBUG_ENABLED`: If some debugs printed messages are needed.
* `MAX_ANIMATION_LIBRARY_LENGTH`: Maximum animation library length name.
* `MAX_ANIMATION_NAME_LENGTH`: Maximum animation length name (need to be modified).

#### Can be redefined
* `DEFAULT_ACTOR_DRAW_DISTANCE`: Distance that label is displayed.
* `MAX_ACTOR_LABEL_LENGTH`: Max length for a text in a label.
* `DEFAULT_ACTOR_COLOR`: Default actor color name.

### Functions - Using streamer
```pawn
native RespawnActor(actorid, bool:isdynamic = true);
native SetActorName(actorid, actor_name[], bool:display, bool:contain_id = false, bool:reformat_label = false, bool:isdynamic = true);
native GetActorName(actorid, actor_name[], length = sizeof(actor_name), bool:isdynamic = true);
native GetActorTextLabel(actorid, text[], length = sizeof(text), bool:isdynamic = true);
native Attach3DTextLabelToActor(actorid, const text[], bool:isdynamic, color, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:drawdistance, testlos = 0, worldid = DEFAULT_ACTOR_VALUE, interiorid = DEFAULT_ACTOR_VALUE, playerid = DEFAULT_ACTOR_VALUE, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = DEFAULT_ACTOR_VALUE, priority = 0, bool:store_string = true);
native ActorHasAttachedLabel(actorid, &bool:name_displayed = false, &bool:text_displayed = false, bool:isdynamic = true);
native UpdateAttachedActor3DTextLabel(actorid, text[], color, bool:isdynamic = true);
native SetActorChatBubble(actorid, const text[], color, Float:drawdistance, expiretime, bool:isdynamic = true);
native DestroyActor3DTextLabel(actorid, bool:isdynamic = true);
native ToggleActorName(actorid, bool:toggle, bool:isdynamic = true);
native SetActorSkin(actorid, skinid, bool:isdynamic = true);
native IsActorDead(actorid, bool:isdynamic = true);
native GetActorSkin(actorid, bool:isdynamic = true);


// In addition to the streamer
native GetDynamicActorInterior(actorid);
native SetDynamicActorInterior(actorid, interiorid);
native GetRealActorID(actorid);
```

### Functions - Not using streamer
```pawn
native RespawnActor(actorid);
native SetActorName(actorid, actor_name[], bool:display, bool:contain_id = false, bool:reformat_label = false);
native GetActorName(actorid, actor_name[], length = sizeof(actor_name));
native GetActorTextLabel(actorid, text[], length = sizeof(text));
native Attach3DTextLabelToActor(actorid, const text[], color, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:drawdistance, virtualworld = DEFAULT_ACTOR_VALUE, testlos = 0, bool:store_string = true);
native ActorHasAttachedLabel(actorid, &bool:name_displayed = false, &bool:text_displayed = false);
native UpdateAttachedActor3DTextLabel(actorid, text[], color);
native SetActorChatBubble(actorid, const text[], color, Float:drawdistance, expiretime);
native DestroyActor3DTextLabel(actorid);
native ToggleActorName(actorid, bool:toggle);
native SetActorSkin(actorid, skinid);
native IsActorDead(actorid);
native GetActorSkin(actorid);
```

### Per-players functions
```pawn
native HideActorForPlayer(playerid, actorid, hide_type, bool:isdynamic = true);
native BringBackActorForPlayer(playerid, actorid, bool:isdynamic = true);
```
### Hide type
* `HIDE_TYPE_ONE_TIME`: The actor will be hidden one time and reappear when it be streamed.
* `HIDE_TYPE_PERMANENT`: The actor will be hidden until the script make it come back even if the player re-stream the actor.

### Other functions (independent of streamer)
```pawn
GetNearestActorForPlayer(playerid, Float:range = 2.0, &bool:IsDynamic = false, type = SEARCH_TYPE_ALL);
GetNearestActorByCoord(Float:x, Float:y, Float:z, Float:range = 2.0, &bool:IsDynamic = false, type = SEARCH_TYPE_ALL, bool:return_multiple_target = true);
```
#### Type of research:
* `SEARCH_TYPE_DYNAMIC`: Search only for dynamics actors
* `SEARCH_TYPE_STATIC`: Search only for statics actors
* `SEARCH_TYPE_ALL`: Search for dynamics **and** statics actors

## Callbacks
```pawn
forward OnPlayerShotActor(playerid, actorid, weaponid, bool:IsDynamicActor);
forward OnPlayerTargetActor(playerid, actorid, weaponid);
forward OnPlayerMakeDamageToActor(playerid, damaged_actorid, Float:amount, weaponid, bodypart, bool:IsDynamicActor, bool:death);
forward OnActorSpawn(actorid, bool:IsDynamicActor);
```
