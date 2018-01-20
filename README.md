# actor_plus
An include with a bunch of useful functions and callback for actors.


# Functions
**Streamer:**
```pawn
RespawnActor(actorid, bool:isdynamic = true);
SetActorName(actorid, actor_name[MAX_PLAYER_NAME], bool:display, bool:contain_id = false, bool:reformat_label = false, bool:isdynamic = true);
GetActorName(actorid, actor_name[MAX_PLAYER_NAME], bool:isdynamic = true);
GetActorTextLabel(actorid, text[], length = sizeof(text), bool:isdynamic = true);
Attach3DTextLabelToActor(actorid, const text[], bool:isdynamic, color, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:drawdistance, testlos = 0, worldid = DEFAULT_ACTOR_VALUE, interiorid = DEFAULT_ACTOR_VALUE, playerid = DEFAULT_ACTOR_VALUE, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = DEFAULT_ACTOR_VALUE, priority = 0, bool:store_string = true);
ActorHasAttachedLabel(actorid, bool:isdynamic = true);
UpdateAttachedActor3DTextLabel(actorid, text[], color, bool:isdynamic = true);
SetActorChatBubble(actorid, text[], color, Float:drawdistance, expiretime, bool:isdyna = true);
```

**Non-streamer:**
```pawn
RespawnActor(actorid);
SetActorName(actorid, actor_name[MAX_PLAYER_NAME], bool:display, bool:contain_id = false, bool:reformat_label = false);
GetActorName(actorid, actor_name[MAX_PLAYER_NAME]);
GetActorTextLabel(actorid, text[], length = sizeof(text));
Attach3DTextLabelToActor(actorid, const text[], color, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:drawdistance, virtualworld = DEFAULT_ACTOR_VALUE, testlos = 0, bool:store_string = true);
ActorHasAttachedLabel(actorid);
UpdateAttachedActor3DTextLabel(actorid, text[], color);
SetActorChatBubble(actorid, text[], color, Float:drawdistance, expiretime);
```

***Both:***
```pawn
GetNearestActorForPlayer(playerid, Float:range = 2.0, &bool:IsDynamic = false, type = SEARCH_TYPE_ALL);
GetNearestActorByCoord(Float:x, Float:y, Float:z, Float:range = 2.0, &bool:IsDynamic = false, type = SEARCH_TYPE_ALL);
```

***Callback:***
```pawn
forward OnPlayerShotActor(playerid, actorid, weaponid, bool:IsDynamicActor);
forward OnPlayerTargetActor(playerid, actorid, weaponid);
```