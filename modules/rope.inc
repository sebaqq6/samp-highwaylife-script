stock ResetRope(playerid)//onplayerdisconnect, onplayerdeath
{
	if(gracz[playerid][rope_while] == 1)
	{
		for(new ropedest=0;ropedest < ROPE_LENGTH;ropedest++)
		{
			if(gracz[playerid][rope_object][ropedest] != 0)
			{
				DestroyDynamicObject(gracz[playerid][rope_object][ropedest]);
				gracz[playerid][rope_object][ropedest] = 0;
			}
		}
		gracz[playerid][rope_while] = 0;
		gracz[playerid][rope_vehicleid] = 0;
		TogglePlayerControllable(playerid, 1);
	}
	return 1;
}

task rope_OnVehicleDeath(vehicleid)
{
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(!gracz[p][loggedin]) continue;
		if(gracz[p][rope_vehicleid] == vehicleid)
		{
			ResetRope(p);
		}
	}
	return 1;
}

forward RopeSync(playerid);
public RopeSync(playerid)
{
	if(gracz[playerid][rope_while] == 0) return 0;
	SetTimerEx("RopeSync",ROPE_SYNCMS,0,"d",playerid);
	ApplyAnimation(playerid,"ped","abseil",4.0,0,0,0,1,0);
	Process_RopeEnd(playerid);
	return 1;
}

task Process_RopeEnd(playerid)
{
	if(gracz[playerid][rope_while] == 1)
	{
		if(IsPlayerInRangeOfPoint(playerid, 13.7, gracz[playerid][rope_endX], gracz[playerid][rope_endY], gracz[playerid][rope_endZ]))
		{
			ClearAnimations(playerid);
			TogglePlayerControllable(playerid,0);
			SetPlayerPos(playerid, gracz[playerid][rope_endX], gracz[playerid][rope_endY], gracz[playerid][rope_endZ]+1.8);
			ResetRope(playerid);
			SetPlayerHealth(playerid, 100.0);
		}
	}
	return 1;
}

task rope_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(IsPlayerOnDutyFraction(playerid))
	{
		if((newkeys & KEY_SUBMISSION || newkeys == KEY_SUBMISSION))
		{
			if(gracz[playerid][rope_while] == 0 && GetPlayerVehicleSeat(playerid) != 0 && IsVehicleHelicopter(pojazd[gracz[playerid][opu_vehicleid]][v_model]))
			{
				GetPlayerPos(playerid,gracz[playerid][PosX],gracz[playerid][PosY],gracz[playerid][PosZ]);
				new Float:rope_Z;
				MapAndreas_FindAverageZ(gracz[playerid][PosX],gracz[playerid][PosY],rope_Z);
				new Float:rope_offset;
				rope_offset = floatsub(gracz[playerid][PosZ],rope_Z);
				if(rope_offset >= ROPE_LENGTH-1) return Error(playerid, "Jesteś za wysoko, aby móc zjechać po linie.");
				if(rope_offset <= 2) return RemovePlayerFromVehicle(playerid);
				gracz[playerid][rope_vehicleid] = GetPlayerVehicleID(playerid);
				gracz[playerid][rope_while] = 1;
				gracz[playerid][rope_endX] = gracz[playerid][PosX];
				gracz[playerid][rope_endY] = gracz[playerid][PosY];
				gracz[playerid][rope_endZ] = rope_Z;
				SetPlayerPos(playerid,gracz[playerid][PosX],gracz[playerid][PosY],floatsub(gracz[playerid][PosZ],2));
				SetPlayerVelocity(playerid,0,0,0);
				for(new rep=0;rep!=10;rep++) ApplyAnimation(playerid,"ped","abseil",4.0,0,0,0,1,0);
				for(new cre=0;cre<=rope_offset;cre++)
				{
				    gracz[playerid][rope_object][cre] = CreateDynamicObject(3004,gracz[playerid][PosX],gracz[playerid][PosY],floatadd(rope_Z,cre),87.640026855469,342.13500976563, 350.07507324219);
				}
				SetTimerEx("RopeSync",ROPE_SYNCMS,0,"d",playerid);
			}
		}
	}
	return 1;
}