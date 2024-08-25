#define PICKUP_MODEL 19135
#define LABEL_DRAWDISTANCE 8

stock Init_Doors()
{
	mq_format("SELECT * FROM `doors`;");
	mq_send("LoadDoorsFromDB");
	return 1;
}

forward LoadDoorsFromDB();
public LoadDoorsFromDB()
{
	mq_getdata();
	if(rekordy)
	{
		new i;
		new fid; 
		while(i < rekordy)
		{
			fid = GetFreeDoorID();
			cache_get_value_name_int(i, "id", 			door[fid][d_id]);
			cache_get_value_name_int(i, "status", 			door[fid][d_status]);
			cache_get_value_name_float(i, "aX", 			door[fid][d_aX]);
			cache_get_value_name_float(i, "aY", 			door[fid][d_aY]);
			cache_get_value_name_float(i, "aZ", 			door[fid][d_aZ]);
			cache_get_value_name_float(i, "bX", 			door[fid][d_bX]);
			cache_get_value_name_float(i, "bY", 			door[fid][d_bY]);
			cache_get_value_name_float(i, "bZ", 			door[fid][d_bZ]);
			cache_get_value_name_int(i, "intB", 			door[fid][d_intB]);
			door[fid][d_pickupA] = CreateDynamicPickup(PICKUP_MODEL, 1, door[fid][d_aX], door[fid][d_aY], door[fid][d_aZ]);
			door[fid][d_pickupB] = CreateDynamicPickup(PICKUP_MODEL, 1, door[fid][d_bX], door[fid][d_bY], door[fid][d_bZ], .worldid = DoorsCalcVW(fid), .interiorid = door[fid][d_intB]);
			format(temp_string, 128, ""COL_EASY"[{8b8b8b}Wejście ID: %dA"COL_EASY"]\n"COL_EASY"["COL_LIME"Użycie: klawisz ENTER"COL_EASY"]", fid);
			door[fid][d_labelA] = CreateDynamic3DTextLabel(temp_string, -1, door[fid][d_aX], door[fid][d_aY], door[fid][d_aZ], LABEL_DRAWDISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
			format(temp_string, 128, ""COL_EASY"[{8b8b8b}Wejście ID: %dB"COL_EASY"]\n"COL_EASY"["COL_LIME"Użycie: klawisz ENTER"COL_EASY"]", fid);
			door[fid][d_labelB] = CreateDynamic3DTextLabel(temp_string, -1, door[fid][d_bX], door[fid][d_bY], door[fid][d_bZ], LABEL_DRAWDISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, .worldid = DoorsCalcVW(fid), .interiorid = door[fid][d_intB]);
			if(door[fid][d_intB] == 6) CreateDynamicMapIcon(door[fid][d_aX], door[fid][d_aY], door[fid][d_aZ], 38, 0, .streamdistance = 250.0, .style = MAPICON_GLOBAL);//ikona 24/7 (przy A)
			else if(door[fid][d_intB] == 15) CreateDynamicMapIcon(door[fid][d_aX], door[fid][d_aY], door[fid][d_aZ], 45, 0, .streamdistance = 250.0, .style = MAPICON_GLOBAL);//ikona binco (przy A)
			i++;
		}
		printf("[LOAD]Zaladowano %d przejsc.", i);
	}
	return 1;
}

stock GetFreeDoorID()
{
	for(new s; s < MAX_DOORS; s++)
	{
		if(!door[s][d_status]) return s;
	}
	return 0;
}

CMD:doorset(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 3) return 0;
	new doorid, point;
	if(sscanf(params,"dc", doorid, point)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /doorset [doorid(wpisz "COL_RED"-1"COL_GREEN" aby zrobić NOWE"COL_GREY" drzwi)] [punkt: A-B, aby usunąć drzwi: X]");
	/*
	-1 = nowe drzwi
	-2 = int binco
	-3 = int sklep
	*/
	if(doorid == -1 || doorid == -2 || doorid == -3)
	{
		if(CountAllDoors()+5 > MAX_DOORS) return Error(playerid, "Limit przejść został wyczerpany.");
		new Float:bPos_X, Float:bPos_Y, Float:bPos_Z;
		new bInt;
		if(doorid == -1)//nowe drzwi
		{
			bPos_X = gracz[playerid][PosX];
			bPos_Y = gracz[playerid][PosY];
			bPos_Z = gracz[playerid][PosZ];
			bInt = GetPlayerInterior(playerid);
		}
		else if(doorid == -2)//int binco
		{
			bPos_X = 207.7101;
			bPos_Y = -110.9561;
			bPos_Z = 1005.1328;
			bInt = 15;
		}
		else if(doorid == -3)//int sklep 24/7
		{
			bPos_X = -26.6820;
			bPos_Y = -57.7868;
			bPos_Z = 1003.5469;
			bInt = 6;
		}
		mq_format("INSERT INTO `doors` VALUES (NULL, '1', '%f', '%f', '%f', '%f', '%f', '%f', '%d');", gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], bPos_X, bPos_Y, bPos_Z, bInt);
		new Cache:cache_id = mysql_query(g_SQL, mQuery, true);
		new fid = GetFreeDoorID();
		door[fid][d_id] = cache_insert_id();
		cache_delete(cache_id);
		door[fid][d_status] = 1;
		door[fid][d_aX] = gracz[playerid][PosX];
		door[fid][d_aY] = gracz[playerid][PosY];
		door[fid][d_aZ] = gracz[playerid][PosZ];
		door[fid][d_bX] = bPos_X;
		door[fid][d_bY] = bPos_Y;
		door[fid][d_bZ] = bPos_Z;
		door[fid][d_intB] = bInt;
		door[fid][d_pickupA] = CreateDynamicPickup(PICKUP_MODEL, 1, door[fid][d_aX], door[fid][d_aY], door[fid][d_aZ]);
		door[fid][d_pickupB] = CreateDynamicPickup(PICKUP_MODEL, 1, door[fid][d_bX], door[fid][d_bY], door[fid][d_bZ], .worldid = DoorsCalcVW(fid), .interiorid = door[fid][d_intB]);
		format(temp_string, 128, ""COL_EASY"[{8b8b8b}Wejście ID: %dA"COL_EASY"]\n"COL_EASY"["COL_LIME"Użycie: klawisz ENTER"COL_EASY"]", fid);
		door[fid][d_labelA] = CreateDynamic3DTextLabel(temp_string, -1, door[fid][d_aX], door[fid][d_aY], door[fid][d_aZ], LABEL_DRAWDISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
		format(temp_string, 128, ""COL_EASY"[{8b8b8b}Wejście ID: %dB"COL_EASY"]\n"COL_EASY"["COL_LIME"Użycie: klawisz ENTER"COL_EASY"]", fid);
		door[fid][d_labelB] = CreateDynamic3DTextLabel(temp_string, -1, door[fid][d_bX], door[fid][d_bY], door[fid][d_bZ], LABEL_DRAWDISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, .worldid = DoorsCalcVW(fid), .interiorid = door[fid][d_intB]);
		SendClientMessageEx(playerid, -1, "[DOORS] "COL_GREEN"Stworzono nowe drzwi!"COL_WHITE" ID: %d", fid);
		return 1;
	}
	else if(doorid < 0) return Error(playerid, "Nieznane ID.");
	if(!door[doorid][d_status]) return SendClientMessageEx(playerid, -1, "[DOORS] "COL_RED"Drzwi o ID: %d nie istnieją! Aby stworzyć nowe drzwi wpisz:"COL_WHITE" /doorset -1 %c", doorid, point);
	switch(point)
	{
		case 'A', 'a':
		{
			door[doorid][d_aX] = gracz[playerid][PosX];
			door[doorid][d_aY] = gracz[playerid][PosY];
			door[doorid][d_aZ] = gracz[playerid][PosZ];
			DestroyDynamicPickup(door[doorid][d_pickupA]);
			DestroyDynamic3DTextLabel(door[doorid][d_labelA]);
			door[doorid][d_pickupA] = CreateDynamicPickup(PICKUP_MODEL, 1, door[doorid][d_aX], door[doorid][d_aY], door[doorid][d_aZ]);
			format(temp_string, 128, ""COL_EASY"[{8b8b8b}Wejście ID: %dA"COL_EASY"]\n"COL_EASY"["COL_LIME"Użycie: klawisz ENTER"COL_EASY"]", doorid);
			door[doorid][d_labelA] = CreateDynamic3DTextLabel(temp_string, -1, door[doorid][d_aX], door[doorid][d_aY], door[doorid][d_aZ], LABEL_DRAWDISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1);
			mq_format("UPDATE `doors` SET `aX`='%f', `aY`='%f', `aZ`='%f' WHERE `id`='%d';", door[doorid][d_aX], door[doorid][d_aY], door[doorid][d_aZ], door[doorid][d_id]);
			mq_send("QUpdateDoorA");
			SendClientMessageEx(playerid, -1, "[DOORS]"COL_BLUE" Punkt A ustawiony.", doorid);
		}
		case 'B', 'b':
		{
			door[doorid][d_bX] = gracz[playerid][PosX];
			door[doorid][d_bY] = gracz[playerid][PosY];
			door[doorid][d_bZ] = gracz[playerid][PosZ];
			door[doorid][d_intB] = GetPlayerInterior(playerid);
			DestroyDynamicPickup(door[doorid][d_pickupB]);
			DestroyDynamic3DTextLabel(door[doorid][d_labelB]);
			door[doorid][d_pickupB] = CreateDynamicPickup(PICKUP_MODEL, 1, door[doorid][d_bX], door[doorid][d_bY], door[doorid][d_bZ], .worldid = DoorsCalcVW(doorid), .interiorid = door[doorid][d_intB]);
			format(temp_string, 128, ""COL_EASY"[{8b8b8b}Wejście ID: %dB"COL_EASY"]\n"COL_EASY"["COL_LIME"Użycie: klawisz ENTER"COL_EASY"]", doorid);
			door[doorid][d_labelB] = CreateDynamic3DTextLabel(temp_string, -1, door[doorid][d_bX], door[doorid][d_bY], door[doorid][d_bZ], LABEL_DRAWDISTANCE, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, .worldid = DoorsCalcVW(doorid), .interiorid = door[doorid][d_intB]);
			mq_format("UPDATE `doors` SET `bX`='%f', `bY`='%f', `bZ`='%f', `intB`='%d' WHERE `id`='%d';", door[doorid][d_bX], door[doorid][d_bY], door[doorid][d_bZ], door[doorid][d_intB], door[doorid][d_id]);
			mq_send("QUpdateDoorB");
			SetPlayerVirtualWorld(playerid, DoorsCalcVW(doorid));
			SendClientMessageEx(playerid, -1, "[DOORS]"COL_YELLOW" Punkt B ustawiony.", doorid);
		}
		case 'X':
		{
			mq_format("DELETE FROM `doors` WHERE `id`='%d';", door[doorid][d_id]);
			mq_send("QDeleteDoor");
			DestroyDynamicPickup(door[doorid][d_pickupA]);
			DestroyDynamic3DTextLabel(door[doorid][d_labelA]);
			DestroyDynamicPickup(door[doorid][d_pickupB]);
			DestroyDynamic3DTextLabel(door[doorid][d_labelB]);
			SendClientMessageEx(playerid, -1, "[DOORS]"COL_RED" Drzwi o ID: %d - USUNIĘTE!", doorid);
			for(new door_info:r; r < door_info; r++)
			{
				door[doorid][r] = 0;
			}
		}
		default:
		{
			SendClientMessageEx(playerid, -1, "[DOORS] "COL_EASY"Wprowadź punkt do ustawienia: A/B. "COL_RED"Aby usunąć drzwi: X");
		}
	}
	return 1;
}

stock EnterDoor(playerid)
{
	if(gracz[playerid][kajdanki] || gracz[playerid][przykuty]) return 1;
	if(gracz[playerid][bw] > 0) return 1;
	if(gracz[playerid][loading_objects]) return 1;
	for(new s; s < MAX_DOORS; s++)
	{
		if(!door[s][d_status]) continue;
		if(InRange(playerid, 1.1, door[s][d_aX], door[s][d_aY], door[s][d_aZ]))//A
		{
			if(!BattleBlock(playerid))
			{
				//SetPlayerPos(playerid, door[s][d_bX], door[s][d_bY], door[s][d_bZ]);
				FreezeLoadObject(playerid, door[s][d_bX], door[s][d_bY], door[s][d_bZ]);
				if(door[s][d_intB] != 0)//przenoszenie do innego int o wyjątkowym vw
				{
					SetPlayerInterior(playerid, door[s][d_intB]);
					SetPlayerVirtualWorld(playerid, DoorsCalcVW(s));
				}

			}
			break;
		}
		else if(InRange(playerid, 1.1, door[s][d_bX], door[s][d_bY], door[s][d_bZ]))//B
		{
			if(DoorsCalcVW(s) == GetPlayerVirtualWorld(playerid))
			{
				//SetPlayerPos(playerid, door[s][d_aX], door[s][d_aY], door[s][d_aZ]);
				FreezeLoadObject(playerid, door[s][d_aX], door[s][d_aY], door[s][d_aZ]);
				if(GetPlayerInterior(playerid) != LUNAPARK_VWOFFSET && GetPlayerInterior(playerid) != 10)//wyjątek  dla lunapark int
				{
					SetPlayerInterior(playerid, 0);
					SetPlayerVirtualWorld(playerid, 0);
				}
				Streamer_Update(playerid);
				break;
			}
		}
	}
	return 1;
}

stock CountAllDoors()
{
	new wynik;
	for(new s; s < MAX_DOORS; s++)
	{
		if(!door[s][d_status]) continue;
		wynik++;
	}
	return wynik;
}

stock DoorsCalcVW(doorid) 
{
	new wynik = 0;
	if(door[doorid][d_intB] != 0) wynik = DOORS_VWOFFSET+doorid;
	if(door[doorid][d_intB] == 10) wynik = LUNAPARK_VWOFFSET;
	return wynik;
}

CMD:winfo(playerid, params[])
{
	SendClientMessageEx(playerid, -1, "world: %d | interior: %d", GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
	return 1;
}