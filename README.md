# actor_plus
An include with a bunch of useful functions and callback for actors.


# Functions
**Streamer:**
```pawn
RespawnActor(actorid, bool:IsDynamic = true);
SetActorName(actorid, name[MAX_PLAYER_NAME], bool:display, bool:contain_id = false, bool:IsDynamic = true);
Attach3DTextLabelToActor(const text[], actorid, bool:IsDynamic, color, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:drawdistance, testlos = 0, worldid = DEFAULT_ACTOR_VALUE, interiorid = DEFAULT_ACTOR_VALUE, playerid = DEFAULT_ACTOR_VALUE, Float:streamdistance = STREAMER_3D_TEXT_LABEL_SD, areaid = DEFAULT_ACTOR_VALUE, priority = 0);
```

**Non-streamer:**
```pawn
RespawnActor(actorid);
SetActorName(actorid, name[MAX_PLAYER_NAME], bool:display, bool:contain_id = false);
Attach3DTextLabelToActor(const text[], actorid, color, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:drawdistance, virtualworld = DEFAULT_ACTOR_VALUE, testlos = 0);
```

**Both:**
```pawn
GetNearestActorForPlayer(playerid, Float:range = 2.0, &bool:IsDynamic = false, type = SEARCH_TYPE_ALL);
GetNearestActorByCoord(Float:x, Float:y, Float:z, Float:range = 2.0, &bool:IsDynamic = false, type = SEARCH_TYPE_ALL);
```
