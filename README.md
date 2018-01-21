# actor_plus
An include with a bunch of useful functions and callback for actors.
Functions returning 1 on success, 0 on failure or cellmin for specific failure. Please, check the wiki for more specific informations.

## Documentation
### Constant
* `MULTIPLE_TARGET_FOUND`: Returned by `GetNearestActorForPlayer` or `GetNearestActorByCoord` when multiple actors are found. **It cannot be redefined**.
* `DEFAULT_ACTOR_VALUE` : Using this one instead of any other value result taking the value from the actor. **It cannot be redefined**.
* `DEFAULT_CHECKING_TIME` : Used to detect OnPlayerTargetActor. **It cannot be redefined**.

* `DEFAULT_ACTOR_DRAW_DISTANCE` : Distance that far a label can be displayed. **It can be redefined**.
* `MAX_ACTOR_LABEL_LENGTH` : Max length for a text in a label. **It can be redefined**.
* `DEFAULT_ACTOR_COLOR` : Default color for the name. **It can be redefined**.

### Functions - Using streamer
```pawn
RespawnActor(actorid, bool:isdynamic = true);
SetActorName(actorid, actor_name[], bool:display, bool:contain_id = false, bool:reformat_label = false, bool:isdynamic = true);
GetActorName(actorid, actor_name[], length = sizeof(actor_name), bool:isdynamic = true);
GetActorTextLabel(actorid, text[], length = sizeof(text), bool:isdynamic = true);
Attach3DTextLabelToActor(actorid, const text[], bool:isdynamic, color, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:drawdistance, testlos = 0, worldid = DEFAULT_ACTOR_VALUE, interiorid = DEFAULT_ACTOR_VALUE, playerid = DEFAULT_ACTOR_VALUE, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = DEFAULT_ACTOR_VALUE, priority = 0, bool:store_string = true);
ActorHasAttachedLabel(actorid, &bool:name_displayed = false, &bool:text_displayed = false, bool:isdynamic = true);
UpdateAttachedActor3DTextLabel(actorid, text[], color, bool:isdynamic = true);
SetActorChatBubble(actorid, const text[], color, Float:drawdistance, expiretime, bool:isdynamic = true);
DestroyActor3DTextLabel(actorid, bool:isdynamic = true);
ToggleActorName(actorid, bool:toggle, bool:isdynamic = true);
SetActorSkin(actorid, skinid, bool:isdynamic = true);
```

### Functions - Not using streamer
```pawn
RespawnActor(actorid);
SetActorName(actorid, actor_name[], bool:display, bool:contain_id = false, bool:reformat_label = false);
GetActorName(actorid, actor_name[], length = sizeof(actor_name));
GetActorTextLabel(actorid, text[], length = sizeof(text));
Attach3DTextLabelToActor(actorid, const text[], color, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:drawdistance, virtualworld = DEFAULT_ACTOR_VALUE, testlos = 0, bool:store_string = true);
ActorHasAttachedLabel(actorid, &bool:name_displayed = false, &bool:text_displayed = false);
UpdateAttachedActor3DTextLabel(actorid, text[], color);
SetActorChatBubble(actorid, const text[], color, Float:drawdistance, expiretime);
DestroyActor3DTextLabel(actorid);
ToggleActorName(actorid, bool:toggle);
SetActorSkin(actorid, skinid);
```

### Other functions (independent of streamer)
```pawn
GetNearestActorForPlayer(playerid, Float:range = 2.0, &bool:IsDynamic = false, type = SEARCH_TYPE_ALL);
GetNearestActorByCoord(Float:x, Float:y, Float:z, Float:range = 2.0, &bool:IsDynamic = false, type = SEARCH_TYPE_ALL);
```

## Callbacks
```pawn
forward OnPlayerShotActor(playerid, actorid, weaponid, bool:IsDynamicActor);
forward OnPlayerTargetActor(playerid, actorid, weaponid);
```
