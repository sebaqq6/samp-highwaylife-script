/*
Fake CP include by NaS (c)2013-2014

Version: 1.0 (First Release)

This include file let's you create a different kind of Checkpoint.
It consists of 3DText Labels and can be made any size, height and color.

Re-realease, change and use as you like, but please leave this credit here.

Any bug found? Please PM me (NaS) on forum.sa-mp.com or post it in the FakeCP thread. Thank you!


Main Functions:

- CreateFakeCP(Text[], Float:X, Float:Y, Float:Z, Float:R = 1.0, Float:RowSpace = 0.5, Float:DrawDistance = 30.0, Color = 0xFF000099, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 50.0)

	Description:
	    Creates a checkpoint
	    R = Radius of the CP
	    RowSpace = Space between each outter row of the CP
	    
	Returns:
	    ID of the created checkpoint
	    -1 if no checkpoint could be created
	    
- DestroyFakeCP(fakecpid)

	Description:
	    Destroys a checkpoint
	    
	Returns:
	    1 if destroying was successful
	    -1 if the given ID was invalid
	    
- IsPlayerInFakeCP(playerid, fakecpid)

	Description:
	    Checks, if a player is in a specific checkpoint
	    
	Returns:
	    true if he is
		false if not
	
- GetPlayerFakeCP(playerid)

	Description:
	    Gets a player's checkpoint
	    
	Returns:
	    Checkpoint ID
	    -1 if the player is in no checkpoint
	    
- SetFakeCPText(fakecpid, text[])

	Description:
	    Sets a checkpoints title text
	    
	Returns:
	    true on success
		false on failure (invalid ID)

- SetFakeCPColor(fakecpid, color)

	Description:
	    Sets a checkpoints color

	Returns:
	    true on success
		false on failure (invalid ID)


Callbacks:

- OnPlayerEnterFakeCP(playerid, fakecpid)

	Description:
	    Gets called, if a player enters a checkpoint

- OnPlayerLeaveFakeCP(playerid, fakecpid)

	Description:
	    Gets called, if a player leaves a checkpoint


NOTE:

You can change the limit of checkpoints by defining "MAX_FAKECPS" before including this file like this:

#define MAX_FAKECPS 25

You can also change the text of the labels surrounding the checkpoint by defining "FCP_CP_TEXT" like this:

#define FCP_CP_TEXT "xXx"

Also note that you have to include Incognito's Streamer BEFORE you include this include.

Have fun!


native CreateFakeCP(Text[], Float:X, Float:Y, Float:Z, Float:R = 1.0, Float:RowSpace = 0.5, Float:DrawDistance = 30.0, Color = 0xFF000099, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 50.0);
native DestroyFakeCP(fakecpid);
native IsPlayerInFakeCP(playerid, fakecpid);
native GetPlayerFakeCP(playerid);
native SetFakeCPText(fakecpid, text[]);
native SetFakeCPColor(fakecpid, color);
*/

#if !defined __FAKECPS_INCLUDED__

#if !defined MAX_FAKECPS
#define MAX_FAKECPS 			20
#endif

#if !defined FCP_CP_TEXT
#define FCP_CP_TEXT 			""
#endif

// ---------------------------------------------------------------------------- Vars, Arrays, Enums etc.

enum fcp_E_FAKECPINFO
{
	bool:fcpUsed,
	Float:fcpX,
	Float:fcpY,
	Float:fcpZ,
	Float:fcpR,
	Float:fcpDrawDistance,
	Float:fcpRowSpace,
	fcpColor,
	fcpText[128],
	
	fcpAreaID,
	Text3D:fcpCPLabels[40],
	Text3D:fcpHeadLabel
};
new fcp_FakeCPs[MAX_FAKECPS][fcp_E_FAKECPINFO];

new fcp_LastFakeCP[MAX_PLAYERS];

// ---------------------------------------------------------------------------- Forwards

forward OnPlayerEnterFakeCP(playerid, fakecpid);
forward OnPlayerLeaveFakeCP(playerid, fakecpid);

// ---------------------------------------------------------------------------- Callback Hooks

public OnGameModeInit()
{
	for(new i = 0; i < MAX_FAKECPS; i ++) fcp_FakeCPs[i][fcpUsed] = false;
	
	// ----------------
	
    #if defined FCP_OnGameModeInit
            FCP_OnGameModeInit();
    #endif
    return 1;
}

#if defined _ALS_OnGameModeInit
        #undef OnGameModeInit
#else
        #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit FCP_OnGameModeInit
#if defined FCP_OnGameModeInit
        forward FCP_OnGameModeInit();
#endif

public OnFilterScriptInit()
{
	for(new i = 0; i < MAX_FAKECPS; i ++) fcp_FakeCPs[i][fcpUsed] = false;

	// ----------------

    #if defined FCP_OnFilterScriptInit
            FCP_OnFilterScriptInit();
    #endif
    return 1;
}

#if defined _ALS_OnFilterScriptInit
        #undef OnFilterScriptInit
#else
        #define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit FCP_OnFilterScriptInit
#if defined FCP_OnFilterScriptInit
        forward FCP_OnFilterScriptInit();
#endif

public OnPlayerEnterDynamicArea(playerid, areaid)
{
	new Slot = Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID); // This is the easiest way of matching an areaid with a checkpointid :)

	if(Slot < 0 || Slot >= MAX_FAKECPS) return 1;

	if(!fcp_FakeCPs[Slot][fcpUsed] || fcp_FakeCPs[Slot][fcpAreaID] != areaid) return 1;

	fcp_LastFakeCP[playerid] = Slot;

	CallRemoteFunction("OnPlayerEnterFakeCP", "dd", playerid, Slot);

	// ----------------

    #if defined FCP_OnPlayerEnterDynamicArea
            FCP_OnPlayerEnterDynamicArea(playerid, areaid);
    #endif
    return 1;
}

#if defined _ALS_OnPlayerEnterDynamicArea
        #undef OnPlayerEnterDynamicArea
#else
        #define _ALS_OnPlayerEnterDynamicArea
#endif
#define OnPlayerEnterDynamicArea FCP_OnPlayerEnterDynamicArea
#if defined FCP_OnPlayerEnterDynamicArea
        forward FCP_OnPlayerEnterDynamicArea(playerid, areaid);
#endif

public OnPlayerLeaveDynamicArea(playerid, areaid)
{
	new Slot = Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID);

	if(Slot < 0 || Slot >= MAX_FAKECPS) return 1;

	if(!fcp_FakeCPs[Slot][fcpUsed] || fcp_FakeCPs[Slot][fcpAreaID] != areaid) return 1;

	fcp_LastFakeCP[playerid] = -1;

	CallRemoteFunction("OnPlayerLeaveFakeCP", "dd", playerid, Slot);

	// ----------------

    #if defined FCP_OnPlayerLeaveDynamicArea
            FCP_OnPlayerLeaveDynamicArea(playerid, areaid);
    #endif
    return 1;
}

#if defined _ALS_OnPlayerLeaveDynamicArea
        #undef OnPlayerLeaveDynamicArea
#else
        #define _ALS_OnPlayerLeaveDynamicArea
#endif
#define OnPlayerLeaveDynamicArea FCP_OnPlayerLeaveDynamicArea
#if defined FCP_OnPlayerLeaveDynamicArea
        forward FCP_OnPlayerLeaveDynamicArea(playerid, areaid);
#endif

// ---------------------------------------------------------------------------- Main Functions

stock CreateFakeCP(Text[], Float:X, Float:Y, Float:Z, Float:R = 1.0, Float:RowSpace = 0.1, Float:DrawDistance = 30.0, Color = 0xFF000099, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 50.0)
{
	new Slot = -1;
	for(new i = 0; i < MAX_FAKECPS; i ++)
	{
	    if(fcp_FakeCPs[i][fcpUsed]) continue;
	    
	    Slot = i;
	    break;
	}
	
	if(Slot == -1) return -1; // RETURN: No free slot
	
	fcp_FakeCPs[Slot][fcpUsed] = true;
	
	if(strlen(Text) > 0) fcp_FakeCPs[Slot][fcpHeadLabel] = CreateDynamic3DTextLabel(Text, Color, X, Y, Z-1.0+(5*RowSpace), DrawDistance, INVALID_PLAYER_ID, INVALID_PLAYER_ID, 1, worldid, interiorid, playerid, streamdistance);
	else fcp_FakeCPs[Slot][fcpHeadLabel] = CreateDynamic3DTextLabel(" ", Color, X, Y, Z-1.0+(5*RowSpace), DrawDistance, INVALID_PLAYER_ID, INVALID_PLAYER_ID, 1, worldid, interiorid, playerid, streamdistance);
	
	fcp_FakeCPs[Slot][fcpAreaID] = CreateDynamicSphere(X, Y, Z, R, worldid, interiorid, playerid);
	Streamer_SetIntData(STREAMER_TYPE_AREA, fcp_FakeCPs[Slot][fcpAreaID], E_STREAMER_EXTRA_ID, Slot); // Set extraid to the checkpointit, so I can find it later again
	
	fcp_FakeCPs[Slot][fcpX] = X;
	fcp_FakeCPs[Slot][fcpY] = Y;
	fcp_FakeCPs[Slot][fcpZ] = Z;
	
	fcp_FakeCPs[Slot][fcpR] = R;
	
	fcp_FakeCPs[Slot][fcpDrawDistance] = DrawDistance;
	fcp_FakeCPs[Slot][fcpRowSpace] = RowSpace;
	fcp_FakeCPs[Slot][fcpColor] = Color;
	
	format(fcp_FakeCPs[Slot][fcpText], 128, Text);
	
	new count = 0;

	DrawDistance = R*5.0;
	if(DrawDistance < 5.0) DrawDistance = 5.0;
	
	for(new Float:i = 0.0; i < 360.0; i = i + 45.0)
	{
		new Float:pX, Float:pY;
		
		pX = X + (R * floatsin(-i, degrees));
		pY = Y + (R * floatcos(-i, degrees));
		
		for(new j = 0; j < 20; j++)
		{
			fcp_FakeCPs[Slot][fcpCPLabels][count] = CreateDynamic3DTextLabel(FCP_CP_TEXT, Color-0x00000001, pX, pY, Z-1.0+(j*RowSpace), DrawDistance, INVALID_PLAYER_ID, INVALID_PLAYER_ID, 1, worldid, interiorid, playerid, streamdistance);
			
			count ++;
		}
	}
	
	return Slot;
}

stock DestroyFakeCP(fakecpid)
{
	if(fakecpid < 0 || fakecpid >= MAX_FAKECPS) return -1; // RETURN: Invalid ID (limit exceeded)
	
	if(!fcp_FakeCPs[fakecpid][fcpUsed]) return -1; // RETURN: Invalid ID (unused)
	
    fcp_FakeCPs[fakecpid][fcpUsed] = false;
    
    DestroyDynamic3DTextLabel(fcp_FakeCPs[fakecpid][fcpHeadLabel]);
    
    DestroyDynamicArea(fcp_FakeCPs[fakecpid][fcpAreaID]);
    
    for(new i = 0; i < 40; i ++) DestroyDynamic3DTextLabel(fcp_FakeCPs[fakecpid][fcpCPLabels][i]);
    
    return 1; // RETURN: SUCCESS
}

stock IsPlayerInFakeCP(playerid, fakecpid)
{
	if(!IsPlayerConnected(playerid) || fakecpid < 0 || fakecpid >= MAX_FAKECPS) return false; // RETURN: Invalid IDs
	
	if(IsPlayerInDynamicArea(playerid, fcp_FakeCPs[fakecpid][fcpAreaID]) && fcp_FakeCPs[fakecpid][fcpUsed]) return true; // RETURN: Player is in CP
	
	return false; // RETURN: Player is in no CP
}

stock GetPlayerFakeCP(playerid)
{
	if(!IsPlayerConnected(playerid)) return -1; // RETURN: Player not connected
	
	return fcp_LastFakeCP[playerid]; // RETURN: CheckpointID
}

stock SetFakeCPText(fakecpid, text[])
{
    if(fakecpid < 0 || fakecpid >= MAX_FAKECPS) return false; // RETURN: Invalid ID (limit exceeded)
    
    if(!fcp_FakeCPs[fakecpid][fcpUsed]) return false; // RETURN: Invalid ID (unused)
    
    if(strlen(text) == 0) return false; // RETURN: Invalid Text (should not be 0 cells)
    
	UpdateDynamic3DTextLabelText(fcp_FakeCPs[fakecpid][fcpHeadLabel], fcp_FakeCPs[fakecpid][fcpColor], text);
	format(fcp_FakeCPs[fakecpid][fcpText], 128, text);
	
	return true; // RETURN: SUCCESS
}

stock SetFakeCPColor(fakecpid, color)
{
    if(fakecpid < 0 || fakecpid >= MAX_FAKECPS) return false; // RETURN: Invalid ID (limit exceeded)

    if(!fcp_FakeCPs[fakecpid][fcpUsed]) return false; // RETURN: Invalid ID (unused)

	UpdateDynamic3DTextLabelText(fcp_FakeCPs[fakecpid][fcpHeadLabel], color, fcp_FakeCPs[fakecpid][fcpText]);
	for(new i = 0; i < MAX_FAKECPS; i ++) UpdateDynamic3DTextLabelText(fcp_FakeCPs[fakecpid][fcpCPLabels][i], color, FCP_CP_TEXT);
	fcp_FakeCPs[fakecpid][fcpColor] = color;
	
	return true; // RETURN: SUCCESS
}

#endif