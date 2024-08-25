#define MAXASG_PICKUPS 40

enum asg_pick_data
{
	asgp_pickupid,
	asgp_weapid,
	asgp_ammo,
	Float:asgp_X,
	Float:asgp_Y,
	Float:asgp_Z,
	Text3D:asgp_text3d
};

new asg_pickups[MAXASG_PICKUPS][asg_pick_data];


new Float:asg_spawns[][4] =
{
	{1713.1421,-1863.0630,424.2012,235.6746}, //0
	{1821.2867,-1958.1642,424.2012,57.4096}, //1
	{1816.8132,-1884.9615,424.2126,275.1782}, //2
	{1809.4055,-1857.0636,424.1903,95.0098}, //3
	{1756.2263,-1880.9125,426.8304,191.4940}, //4
	{1736.8263,-1906.7412,424.1956,139.8636}, //5
	{1751.2584,-1933.0770,424.2308,320.6588}, //6
	{1777.7267,-1940.2965,424.3086,199.3975}, //7
	{1797.0227,-1927.3989,424.2306,339.1220}, //8
	{1739.0082,-1887.3030,425.1072,49.2860}, //9
	{1800.7744,-1908.5439,427.0663,358.1837}, //10
	{1787.1597,-1889.0251,425.1270,50.6840} //11
};


stock Init_ASG()
{
	//
	ASG_CreateWeapPickup(WEAPON_SHOTGSPA, 40, 1777.9388,-1975.2542,424.1903); // SHOTGUN 40
	ASG_CreateWeapPickup(WEAPON_SHOTGSPA, 40, 1717.6033,-1969.5994,424.1903); // SHOTGUN 40
	ASG_CreateWeapPickup(WEAPON_SHOTGSPA, 40, 1730.6090,-1851.5142,424.1903); // SHOTGUN 40
	ASG_CreateWeapPickup(WEAPON_SHOTGSPA, 40, 1812.8254,-1853.0159,424.1903); // SHOTGUN 40
	
	ASG_CreateWeapPickup(WEAPON_M4, 120, 1730.3781,-1932.4065,424.2066); // M4 120
	ASG_CreateWeapPickup(WEAPON_M4, 120, 1777.0488,-1939.8463,426.8320); // M4 120
	ASG_CreateWeapPickup(WEAPON_M4, 120, 1756.2791,-1882.1282,426.8304); // M4 120
	
	ASG_CreateWeapPickup(WEAPON_AK47, 120, 1753.8506,-1929.4642,424.2308); // AK47 120
	ASG_CreateWeapPickup(WEAPON_AK47, 120, 1738.8053,-1888.6835,425.1072); // AK47 120
	ASG_CreateWeapPickup(WEAPON_AK47, 120, 1826.5927,-1914.6588,424.2162); // AK47 120
	
	ASG_CreateWeapPickup(WEAPON_RIFLE, 50, 1816.1497,-1886.3512,424.2126); // COUNTRY 50
	ASG_CreateWeapPickup(WEAPON_RIFLE, 50, 1726.9164,-1936.1661,429.5568); // COUNTRY 50
	
	ASG_CreateWeapPickup(WEAPON_MP5, 160, 1764.7892,-1910.5238,431.5959); // MP5 160
	ASG_CreateWeapPickup(WEAPON_MP5, 160, 1713.9651,-1863.7777,429.1212); // MP5 160
	ASG_CreateWeapPickup(WEAPON_MP5, 160, 1821.3512,-1957.7174,429.1012); // MP5 160
	ASG_CreateWeapPickup(WEAPON_MP5, 160, 1706.8585,-1935.0055,424.1903); // MP5 160
	
	ASG_CreateWeapPickup(WEAPON_SNIPER, 30, 1764.5999,-1910.9747,439.9958); // SNIPER 30
	
	ASG_CreateWeapPickup(WEAPON_SAWEDOFF, 40, 1756.7817,-1935.1962,424.2308); // SHAWN OFF 40
	ASG_CreateWeapPickup(WEAPON_SAWEDOFF, 40, 1801.8667,-1908.6852,424.1991); // SHAWN OFF 40
	ASG_CreateWeapPickup(WEAPON_SAWEDOFF, 40, 1751.0725,-1948.9076,424.2066); // SHAWN OFF 40
	
	ASG_CreateWeapPickup(WEAPON_SHOTGSPA, 50, 1713.4031,-1890.4991,424.1903); // COMBAT 50
	ASG_CreateWeapPickup(WEAPON_SHOTGSPA, 50, 1798.1379,-1926.2679,424.2378); // COMBAT 50
	ASG_CreateWeapPickup(WEAPON_SHOTGSPA, 50, 1786.8737,-1889.2606,425.1270); // COMBAT 50
	
	ASG_CreateWeapPickup(WEAPON_TEC9, 300, 1785.8646,-1882.9852,425.1270); // TEC9 300
	ASG_CreateWeapPickup(WEAPON_TEC9, 300, 1732.2826,-1948.4380,424.1966); // TEC9 300
	ASG_CreateWeapPickup(WEAPON_TEC9, 300, 1801.5134,-1925.3315,424.2378); // TEC9 300
	ASG_CreateWeapPickup(WEAPON_TEC9, 300, 1731.2554,-1889.1525,425.1072); // TEC9 300
	
	ASG_CreateWeapPickup(WEAPON_UZI, 300, 1800.9536,-1908.5947,427.0663); // UZI 300
	ASG_CreateWeapPickup(WEAPON_UZI, 300, 1777.4879,-1940.0336,424.3086); // UZI 300
	ASG_CreateWeapPickup(WEAPON_UZI, 300, 1736.6129,-1907.5737,424.1956); // UZI 300
	ASG_CreateWeapPickup(WEAPON_UZI, 300, 1760.6632,-1885.6411,424.3069); // UZI 300
	ASG_CreateWeapPickup(WEAPON_UZI, 300, 1818.7601,-1936.6124,424.1903); // UZI 300
	return 1;
}

task ASG_OnPickup(playerid)
{
	new tick_count = GetTickCount();
	if(gracz[playerid][asg_pickup_tick]+175 > tick_count) return 1;
	gracz[playerid][asg_pickup_tick] = tick_count;
	for(new id; id < MAXASG_PICKUPS; id++)
	{
		if(asg_pickups[id][asgp_pickupid] == 0) continue;
		if(IsPlayerInRangeOfPoint(playerid, 1.0, asg_pickups[id][asgp_X], asg_pickups[id][asgp_Y], asg_pickups[id][asgp_Z]))
		{
			SetTimerEx("ASG_CreateWeapPickup", 1000*30, false, "ddfff", asg_pickups[id][asgp_weapid], asg_pickups[id][asgp_ammo], asg_pickups[id][asgp_X], asg_pickups[id][asgp_Y], asg_pickups[id][asgp_Z]);
			GivePlayerWeapon(playerid, asg_pickups[id][asgp_weapid], asg_pickups[id][asgp_ammo]);
			ASG_DestroyWeapPickup(id);
			break;
		}
	}
	return 1;
}

task ASG_OnPlayerDeath(playerid, killerid, reason)
{
	if(killerid != INVALID_PLAYER_ID) gracz[killerid][asg_score]++;
	gracz[playerid][asg_score]--;
	ASG_SendDeathMessage(killerid, playerid, reason);
	ASG_SendStopSpecSignal(playerid);
	new bool:find_spec = false;
	if(killerid != INVALID_PLAYER_ID)
	{
		if(gracz[killerid][loggedin] == true && GetPlayerState(killerid) != PLAYER_STATE_SPECTATING)
		{
			TogglePlayerSpectating(playerid, 1);
			PlayerSpectatePlayer(playerid, killerid);
			gracz[playerid][asg_specpid] = killerid;
			find_spec = true;
		}
	}
	if(find_spec == false)
	{
		TogglePlayerSpectating(playerid, 1);
		InterpolateCameraPos(playerid, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]+20, 3000);
		InterpolateCameraLookAt(playerid, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], 3000);
	}
	SetTimerEx("ASG_StopSpec", 3000, false, "d", playerid);
	return 1;
}

task ASG_StopSpec(playerid)
{
	gracz[playerid][asg_specpid] = -1;
	TogglePlayerSpectating(playerid, 0);
	return 1;
}

stock ASG_SendStopSpecSignal(playerid)
{
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(!gracz[p][loggedin]) continue;
		if(gracz[p][status_lunapark] == LPARK_ASG)
		{
			if(gracz[p][asg_specpid] == playerid)
			{
				ASG_StopSpec(p);
			}
		}
	}
	return 1;
}

task ASG_OnPlayerSpawn(playerid)
{
	gracz[playerid][asg_specpid] = -1;
	new rand_spawn = MRandom(sizeof(asg_spawns));
	if(gracz[playerid][status_lunapark] != LPARK_ASG)
	{
		FreezeLoadObject(playerid, asg_spawns[rand_spawn][0], asg_spawns[rand_spawn][1], asg_spawns[rand_spawn][2]);
		ASG_SendDeathMessage(INVALID_PLAYER_ID, playerid, 200);
		gracz[playerid][asg_score] = 0;
		SetPVarInt(playerid, "asg_spawnprotect", 8);
	}
	else
	{
		SetPlayerPos(playerid, asg_spawns[rand_spawn][0], asg_spawns[rand_spawn][1], asg_spawns[rand_spawn][2]);
		SetPVarInt(playerid, "asg_spawnprotect", 5);
	}
	gracz[playerid][status_lunapark] = LPARK_ASG;
	SetTimerEx("ASG_SpawnProtect", 1000, false, "d", playerid);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 999);

	SetPlayerHealth(playerid, 100.0);
	ResetPlayerWeapons(playerid);
	GivePlayerWeapon(playerid, WEAPON_COLT45, 500);
	SetPlayerVirtualWorld(playerid, LUNAPARK_VWOFFSET);
	SetPlayerInterior(playerid, 10);
	
	SetPlayerFacingAngle(playerid, asg_spawns[rand_spawn][3]);
	//spawn protect
	return 1;
}

task ASG_SpawnProtect(playerid)
{
	if(GetPVarInt(playerid, "asg_spawnprotect") > 0)
	{
		new str[64];
		format(str, sizeof(str), "*** %s - SPAWN OCHRONA =  %d ***", nick(playerid), GetPVarInt(playerid, "asg_spawnprotect"));
		SendNearByMessage_noplayerid(playerid, 0x6082B6FF, str, 20);
		format(str, sizeof(str), "SPAWN OCHRONA: %d", GetPVarInt(playerid, "asg_spawnprotect"));
		GameTextForPlayer(playerid, str, 1000, 3);
		SetPVarInt(playerid, "asg_spawnprotect", GetPVarInt(playerid, "asg_spawnprotect")-1);
		SetPlayerHealth(playerid, 100.0);
		SetTimerEx("ASG_SpawnProtect", 1000, false, "d", playerid);
	}
	return 1;
}

task ASG_OnPlayerExit(playerid)//gdy opuści ASG
{
	ASG_SendStopSpecSignal(playerid);
	gracz[playerid][asg_score] = 0;
	gracz[playerid][asg_specpid] = -1;
	ASG_SendDeathMessage(INVALID_PLAYER_ID, playerid, 201);
	SetPlayerHealth(playerid, 100.0);
	ResetPlayerWeapons(playerid);
	ASG_ClearDeathMessage(playerid);
	return 1;
}

task ASG_CreateWeapPickup(weapid, ammo, Float:aX, Float:aY, Float:aZ)
{
	new pick_id = -1;
	for(new id; id < MAXASG_PICKUPS; id++)
	{
		if(asg_pickups[id][asgp_pickupid] == 0)
		{
			pick_id = id;
			break;
		}
	}
	if(pick_id == -1) return 0;
	asg_pickups[pick_id][asgp_pickupid] = CreateDynamicPickup(GetWeaponModel(weapid), 1, aX, aY, aZ, .worldid = LUNAPARK_VWOFFSET, .interiorid = 10);
	asg_pickups[pick_id][asgp_weapid] = weapid;
	asg_pickups[pick_id][asgp_ammo] = ammo;
	asg_pickups[pick_id][asgp_X] = aX;
	asg_pickups[pick_id][asgp_Y] = aY;
	asg_pickups[pick_id][asgp_Z] = aZ;
	new str_text3d[256];
	format(str_text3d, 256, "Broń: %s\nAmmo: %d", WeaponName(weapid), ammo);
	asg_pickups[pick_id][asgp_text3d] = CreateDynamic3DTextLabel(str_text3d, 0xFFFFFF98, aX, aY, aZ, 5.0, .worldid = LUNAPARK_VWOFFSET, .interiorid = 10);
	return 1;
}

stock ASG_DestroyWeapPickup(pick_id)
{
	if(asg_pickups[pick_id][asgp_pickupid] == 0) return 0;
	DestroyDynamicPickup(asg_pickups[pick_id][asgp_pickupid]);
	DestroyDynamic3DTextLabel(asg_pickups[pick_id][asgp_text3d]);
	for(new asg_pick_data:r; r < asg_pick_data; r++)//czyszczenie zmiennych
	{
		asg_pickups[pick_id][r] = 0;
	}
	return 1;
}

stock ASG_SendDeathMessage(killerid, playerid, weapon)
{
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(!gracz[p][loggedin]) continue;
		if(gracz[p][status_lunapark] == LPARK_ASG)
		{
			SendDeathMessageToPlayer(p, killerid, playerid, weapon);
			if(weapon == 200) SendClientMessageEx(p, 0xFF0000FF, "[ASG] "COL_GREY"%s "COL_GREEN"wszedł na arenę ASG.", nick(playerid));
			else if(weapon == 201) SendClientMessageEx(p, 0xFF0000FF, "[ASG] "COL_GREY"%s "COL_RED"opuścił arenę ASG.", nick(playerid));
			else 
			{
				if(strlen(WeaponName(weapon)) > 1)
				{
					SendClientMessageEx(p, 0xFF0000FF, "[ASG] "COL_GREEN"%s [%d pkt] ->"COL_EASY" %s "COL_RED"-> %s [%d pkt]", nick(killerid), gracz[killerid][asg_score], WeaponName(weapon), nick(playerid), gracz[playerid][asg_score]);
				}
				else
				{
					SendClientMessageEx(p, 0xFF0000FF, "[ASG] "COL_GREY"%s "COL_RED"popełnił samobójstwo.", nick(playerid));
				}
			}
		}
	}
	return 1;
}

stock ASG_ClearDeathMessage(playerid)
{
	for(new dm; dm < 10; dm++)
	{
		SendDeathMessageToPlayer(playerid, INVALID_PLAYER_ID, 999, 255);
	}
	return 1;
}