#define MAX_TRAFFICLIGHTS 100

enum trlights_data
{
	trlights_uid,
	trlights_coop_uid,
	trlights_objectid,
	Float:trlights_oX,
	Float:trlights_oY,
	Float:trlights_oZ,
	Float:trlights_oRZ,
	Text3D:trlights_text3d,
	trlights_light,
	trlights_redtime,
	trlights_greentime,
	trlights_tick
};

new trafficlights[MAX_TRAFFICLIGHTS][trlights_data];

stock Init_TrafficLights()
{
	SetTimer("Process_TrafficLights", 1000, true);
	mq_format("SELECT * FROM `trafficlights`;");
	mq_send("LoadTrafficLightsFromDB");
	return 1;
}

task LoadTrafficLightsFromDB()
{
	mq_getdata();
	if(rekordy)
	{
		new i;
		new tlid; 
		while(i < rekordy)
		{
			tlid = GetFreeTrafficLightsID();
			if(tlid != -1)
			{
				cache_get_value_name_int(i, "id", trafficlights[tlid][trlights_uid]);
				cache_get_value_name_int(i, "coop_id", trafficlights[tlid][trlights_coop_uid]);
				cache_get_value_name_float(i, "oX", trafficlights[tlid][trlights_oX]);
				cache_get_value_name_float(i, "oY", trafficlights[tlid][trlights_oY]);
				cache_get_value_name_float(i, "oZ", trafficlights[tlid][trlights_oZ]);
				cache_get_value_name_float(i, "oRZ", trafficlights[tlid][trlights_oRZ]);
				cache_get_value_name_int(i, "redtime", trafficlights[tlid][trlights_redtime]);
				cache_get_value_name_int(i, "greentime", trafficlights[tlid][trlights_greentime]);
				trafficlights[tlid][trlights_objectid] = CreateDynamicObject(1352, trafficlights[tlid][trlights_oX], trafficlights[tlid][trlights_oY], trafficlights[tlid][trlights_oZ]-2.0, 0.0, 0.0, trafficlights[tlid][trlights_oRZ]);
				trafficlights[tlid][trlights_text3d] = CreateDynamic3DTextLabel("ładowanie...", -1, trafficlights[tlid][trlights_oX], trafficlights[tlid][trlights_oY], trafficlights[tlid][trlights_oZ]+3.0, 65.0);
				i++;
			}
			else printf("[TRAFFIC LIGHTS] Limit przekroczony!");
		}
	}
	return 1;
}

stock GetFreeTrafficLightsID()
{
	for(new t; t < MAX_TRAFFICLIGHTS; t++)
	{
		if(!trafficlights[t][trlights_uid]) return t;
	}
	return -1;
}

stock GetTrafficLightID(uid)
{
	for(new t; t < MAX_TRAFFICLIGHTS; t++)
	{
		if(!trafficlights[t][trlights_uid]) continue;
		if(trafficlights[t][trlights_uid] == uid) return t;
	}
	return -1;
}

CMD:trafficlight(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 2) return 0;
	new tlid;
	if(sscanf(params,"d", tlid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /trafficlight [id świateł (wpisz "COL_RED"-1"COL_GREEN" aby zrobić NOWE"COL_GREY" światła)]");
	if(tlid < -1) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /trafficlight [id świateł (wpisz "COL_RED"-1"COL_GREEN" aby zrobić NOWE"COL_GREY" światła)]");
	if(tlid == -1)
	{
		new new_tlid = GetFreeTrafficLightsID();
		if(new_tlid == -1) return Error(playerid, "Limit świateł drogowych przekroczony.");
		trafficlights[new_tlid][trlights_oX] = gracz[playerid][PosX];
		trafficlights[new_tlid][trlights_oY] = gracz[playerid][PosY];
		trafficlights[new_tlid][trlights_oZ] = gracz[playerid][PosZ];
		trafficlights[new_tlid][trlights_redtime] = 10;
		trafficlights[new_tlid][trlights_greentime] = 10;
		new Float:pAngle;
		GetPlayerFacingAngle(playerid, pAngle);
		trafficlights[new_tlid][trlights_oRZ] = pAngle+180.0;
		SetPlayerPos(playerid, gracz[playerid][PosX]+1.0, gracz[playerid][PosY], gracz[playerid][PosZ]);
		trafficlights[new_tlid][trlights_objectid] = CreateDynamicObject(1352, trafficlights[new_tlid][trlights_oX], trafficlights[new_tlid][trlights_oY], trafficlights[new_tlid][trlights_oZ]-2.0, 0.0, 0.0, trafficlights[new_tlid][trlights_oRZ]);
		trafficlights[new_tlid][trlights_text3d] = CreateDynamic3DTextLabel("ładowanie...", -1, trafficlights[new_tlid][trlights_oX], trafficlights[new_tlid][trlights_oY], trafficlights[new_tlid][trlights_oZ]+3.0, 65.0);
		mq_format("INSERT INTO `trafficlights` VALUES (NULL, '0', '%f', '%f', '%f', '%f', '%d', '%d');", trafficlights[new_tlid][trlights_oX], trafficlights[new_tlid][trlights_oY], trafficlights[new_tlid][trlights_oZ], trafficlights[new_tlid][trlights_oRZ], trafficlights[new_tlid][trlights_redtime], trafficlights[new_tlid][trlights_greentime]);
		new Cache:cache_id = mysql_query(g_SQL, mQuery, true);
		trafficlights[new_tlid][trlights_uid] = cache_insert_id();
		cache_delete(cache_id);
		SetTrafficLightLight(new_tlid, 4);
		Info(playerid, "Światła drogowe stworzone! Użyj /trafficlight [id świateł] aby skonfigurować.");
	}
	else
	{
		new traffic_id = GetTrafficLightID(tlid);
		if(traffic_id == -1) return Error(playerid, "Brak świateł o takim ID.");
		if(!IsPlayerInRangeOfPoint(playerid, 70.0, trafficlights[traffic_id][trlights_oX], trafficlights[traffic_id][trlights_oY], trafficlights[traffic_id][trlights_oZ])) return Error(playerid, "Jesteś za daleko od świateł o danym ID.");
		new strTrafficLightMenu[512];
		format(strTrafficLightMenu, 512, "Opcja\t[info]");
		format(strTrafficLightMenu, 512, "%s\n"COL_EASY"Aktualizuj pozycje świateł\t"COL_GREY"[obiekt świateł]", strTrafficLightMenu);
		format(strTrafficLightMenu, 512, "%s\n"COL_EASY"Parowanie świateł\t"COL_GREY"[ID pary: %d (0 - brak pary, światła nieaktywne)]", strTrafficLightMenu, trafficlights[traffic_id][trlights_coop_uid]);
		format(strTrafficLightMenu, 512, "%s\n"COL_EASY"Czas światła "COL_RED"czerwonego\t"COL_GREY"[%d sekund]", strTrafficLightMenu, trafficlights[traffic_id][trlights_redtime]);
		format(strTrafficLightMenu, 512, "%s\n"COL_EASY"Czas światła "COL_GREEN"zielonego\t"COL_GREY"[%d sekund]", strTrafficLightMenu, trafficlights[traffic_id][trlights_greentime]);
		format(strTrafficLightMenu, 512, "%s\n"COL_RED"Usuń światła\t"COL_GREY"[miejsce na jezdni]", strTrafficLightMenu);
		new strTitle[128];
		format(strTitle, 128, "Światła ID: "COL_RED"%d"COL_WHITE":%d ", trafficlights[traffic_id][trlights_uid], trafficlights[traffic_id][trlights_coop_uid]);
		SetPVarInt(playerid, "cache_trafficid", traffic_id);
		Dialog_Show(playerid, TRAFFICLIGHTMENU, DIALOG_STYLE_TABLIST_HEADERS, strTitle, strTrafficLightMenu, "Wybierz", "Anuluj");
	}
	return 1;
}

Dialog:TRAFFICLIGHTMENU(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new traffic_id = GetPVarInt(playerid, "cache_trafficid");
	if(traffic_id == -1) return Error(playerid, "Brak świateł o takim ID.");
	if(!IsPlayerInRangeOfPoint(playerid, 70.0, trafficlights[traffic_id][trlights_oX], trafficlights[traffic_id][trlights_oY], trafficlights[traffic_id][trlights_oZ])) return Error(playerid, "Jesteś za daleko od świateł o danym ID.");
	switch(listitem)
	{
		case 0://aktualizacja pozycji
		{
			if(IsValidDynamicObject(trafficlights[traffic_id][trlights_objectid]) && IsValidDynamic3DTextLabel(trafficlights[traffic_id][trlights_text3d]))
			{
				DestroyDynamicObject(trafficlights[traffic_id][trlights_objectid]);
				DestroyDynamic3DTextLabel(trafficlights[traffic_id][trlights_text3d]);
				trafficlights[traffic_id][trlights_oX] = gracz[playerid][PosX];
				trafficlights[traffic_id][trlights_oY] = gracz[playerid][PosY];
				trafficlights[traffic_id][trlights_oZ] = gracz[playerid][PosZ];
				new Float:pAngle;
				GetPlayerFacingAngle(playerid, pAngle);
				trafficlights[traffic_id][trlights_oRZ] = pAngle+180.0;
				SetPlayerPos(playerid, gracz[playerid][PosX]+1.0, gracz[playerid][PosY], gracz[playerid][PosZ]);
				trafficlights[traffic_id][trlights_objectid] = CreateDynamicObject(1352, trafficlights[traffic_id][trlights_oX], trafficlights[traffic_id][trlights_oY], trafficlights[traffic_id][trlights_oZ]-2.0, 0.0, 0.0, trafficlights[traffic_id][trlights_oRZ]);
				trafficlights[traffic_id][trlights_text3d] = CreateDynamic3DTextLabel("ładowanie...", -1, trafficlights[traffic_id][trlights_oX], trafficlights[traffic_id][trlights_oY], trafficlights[traffic_id][trlights_oZ]+3.0, 65.0);
				SetTrafficLightLight(traffic_id, 4);
				mq_format("UPDATE `trafficlights` SET `oX`='%f', `oY`='%f', `oZ`='%f', `oRZ`='%f' WHERE `id`='%d';", trafficlights[traffic_id][trlights_oX], trafficlights[traffic_id][trlights_oY], trafficlights[traffic_id][trlights_oZ], trafficlights[traffic_id][trlights_uid]);
				mq_send("QUpdateTL");
				Info(playerid, "Światła przestawione.");
				//-powrót do menu
				new strCommand[64];
				format(strCommand, 64, "/trafficlight %d", trafficlights[traffic_id][trlights_uid]);
				PC_EmulateCommand(playerid, strCommand);
				//-
			}
			else Error(playerid, "Wystąpił nieoczekiwany błąd.");
		}
		case 1://parowanie świateł
		{
			Dialog_Show(playerid, TRAFFICLPAIR, DIALOG_STYLE_INPUT, "Wprowadź ID świateł", "Parowanie pozwala na synchronizacje świateł.\nWprowadź poniżej ID świateł, z którymi chcesz zsynchronizować aktualnie wybrane światła.\nWprowadź 0 aby usunąć parę.", "Zatwierdz", "Anuluj");
		}
		case 2://czas czerwonego
		{
			if(trafficlights[traffic_id][trlights_coop_uid] == 0)
			{
				Error(playerid, "Aby ustawić czas świateł, musisz je najpierw sparować.");
				//-powrót do menu
				new strCommand[64];
				format(strCommand, 64, "/trafficlight %d", trafficlights[traffic_id][trlights_uid]);
				PC_EmulateCommand(playerid, strCommand);
				//-
				return 1;
			}
			Dialog_Show(playerid, TRAFFICLSETRED, DIALOG_STYLE_INPUT, "Wprowadź czas światła", "Wprowadź czas w sekundach, przez jaki będzie się świeciło "COL_RED"czerwone światło"COL_WHITE".\n"COL_RED"Uwaga! Czas czerwonego = czas zielonego dla sparowanego sygnalizatora.", "Zatwierdz", "Anuluj");
		}
		case 3://czas zielonego
		{
			if(trafficlights[traffic_id][trlights_coop_uid] == 0)
			{
				Error(playerid, "Aby ustawić czas świateł, musisz je najpierw sparować.");
				//-powrót do menu
				new strCommand[64];
				format(strCommand, 64, "/trafficlight %d", trafficlights[traffic_id][trlights_uid]);
				PC_EmulateCommand(playerid, strCommand);
				//-
				return 1;
			}
			Dialog_Show(playerid, TRAFFICLSETGREEN, DIALOG_STYLE_INPUT, "Wprowadź czas światła", "Wprowadź czas w sekundach, przez jaki będzie się świeciło "COL_GREEN"czerwone zielone"COL_WHITE".\n"COL_RED"Uwaga! Czas zielonego = czas czerwonego dla sparowanego sygnalizatora.", "Zatwierdz", "Anuluj");
		}
		case 4://usuwanie
		{
			if(IsValidDynamicObject(trafficlights[traffic_id][trlights_objectid]) && IsValidDynamic3DTextLabel(trafficlights[traffic_id][trlights_text3d]))
			{
				DestroyDynamicObject(trafficlights[traffic_id][trlights_objectid]);
				DestroyDynamic3DTextLabel(trafficlights[traffic_id][trlights_text3d]);
			}
			mq_format("DELETE FROM `trafficlights` WHERE `id`='%d';", trafficlights[traffic_id][trlights_uid]);
			mq_send("QDeleteTL");
			new old_coop = trafficlights[traffic_id][trlights_coop_uid];
			for(new trlights_data:r; r < trlights_data; r++)//czyszczenie zmiennych
			{
				trafficlights[traffic_id][r] = 0;
			}
			if(old_coop != 0)//usuwanie pary z drugich świateł.
			{
				for(new t; t < MAX_TRAFFICLIGHTS; t++)
				{
					if(!trafficlights[t][trlights_uid]) continue;
					if(trafficlights[t][trlights_uid] == old_coop)
					{
						trafficlights[t][trlights_coop_uid] = 0;
						trafficlights[t][trlights_redtime] = 10;
						trafficlights[t][trlights_greentime] = 10;
						mq_format("UPDATE `trafficlights` SET `coop_id`='0', `redtime`='10', `greentime`='10' WHERE `id`='%d';", trafficlights[t][trlights_uid]);
						mq_send("QUpdateTL");
						break;
					}
				}
			}
			Info(playerid, ""COL_RED"Światła usunięte.");
		}
	}
	return 1;
}

Dialog:TRAFFICLSETRED(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new traffic_id = GetPVarInt(playerid, "cache_trafficid");
	if(traffic_id == -1) return Error(playerid, "Nieoczekiwany błąd.");
	if(trafficlights[traffic_id][trlights_coop_uid] == 0)
	{
		Error(playerid, "Aby ustawić czas świateł, musisz je najpierw sparować.");
		//-powrót do menu
		new strCommand[64];
		format(strCommand, 64, "/trafficlight %d", trafficlights[traffic_id][trlights_uid]);
		PC_EmulateCommand(playerid, strCommand);
		//-
		return 1;
	}
	new input = strval(inputtext);
	if(input < 1) return Error(playerid, "Zbyt mały czas.");
	if(input > 100) return Error(playerid, "Zbyt duży czas.");
	trafficlights[traffic_id][trlights_redtime] = input;
	new pair_traffic_id = GetTrafficLightID(trafficlights[traffic_id][trlights_coop_uid]);
	trafficlights[pair_traffic_id][trlights_greentime] = trafficlights[traffic_id][trlights_redtime];
	mq_format("UPDATE `trafficlights` SET `redtime`='%d' WHERE `id`='%d';", trafficlights[traffic_id][trlights_redtime], trafficlights[traffic_id][trlights_uid]);
	mq_send("QUpdateTL");
	mq_format("UPDATE `trafficlights` SET `greentime`='%d' WHERE `id`='%d';", trafficlights[pair_traffic_id][trlights_greentime], trafficlights[pair_traffic_id][trlights_uid]);
	mq_send("QUpdateTL");
	Info(playerid, ""COL_RED"Czas czerwonego światła ustawiony!");
	return 1;
}

Dialog:TRAFFICLSETGREEN(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new traffic_id = GetPVarInt(playerid, "cache_trafficid");
	if(traffic_id == -1) return Error(playerid, "Nieoczekiwany błąd.");
	if(trafficlights[traffic_id][trlights_coop_uid] == 0)
	{
		Error(playerid, "Aby ustawić czas świateł, musisz je najpierw sparować.");
		//-powrót do menu
		new strCommand[64];
		format(strCommand, 64, "/trafficlight %d", trafficlights[traffic_id][trlights_uid]);
		PC_EmulateCommand(playerid, strCommand);
		//-
		return 1;
	}
	new input = strval(inputtext);
	if(input < 1) return Error(playerid, "Zbyt mały czas.");
	if(input > 100) return Error(playerid, "Zbyt duży czas.");
	trafficlights[traffic_id][trlights_greentime] = input;
	new pair_traffic_id = GetTrafficLightID(trafficlights[traffic_id][trlights_coop_uid]);
	trafficlights[pair_traffic_id][trlights_redtime] = trafficlights[traffic_id][trlights_greentime];
	mq_format("UPDATE `trafficlights` SET `greentime`='%d' WHERE `id`='%d';", trafficlights[traffic_id][trlights_greentime], trafficlights[traffic_id][trlights_uid]);
	mq_send("QUpdateTL");
	mq_format("UPDATE `trafficlights` SET `redtime`='%d' WHERE `id`='%d';", trafficlights[pair_traffic_id][trlights_redtime], trafficlights[pair_traffic_id][trlights_uid]);
	mq_send("QUpdateTL");
	Info(playerid, ""COL_GREEN"Czas zielonego światła ustawiony!");
	return 1;
}


Dialog:TRAFFICLPAIR(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new traffic_id = GetPVarInt(playerid, "cache_trafficid");
	if(traffic_id == -1) return Error(playerid, "Nieoczekiwany błąd.");
	new input = strval(inputtext);
	if(input == trafficlights[traffic_id][trlights_uid]) return Error(playerid, "Nie możesz sparować sygnalizatora ze sobą.");
	if(input == 0)//dezaktywacja
	{
		new old_coop = trafficlights[traffic_id][trlights_coop_uid];
		trafficlights[traffic_id][trlights_coop_uid] = 0;
		trafficlights[traffic_id][trlights_redtime] = 10;
		trafficlights[traffic_id][trlights_greentime] = 10;
		mq_format("UPDATE `trafficlights` SET `coop_id`='0', `redtime`='10', `greentime`='10' WHERE `id`='%d';", trafficlights[traffic_id][trlights_uid]);
		mq_send("QUpdateTL");
		if(old_coop != 0)//usuwanie pary z drugich świateł.
		{
			for(new t; t < MAX_TRAFFICLIGHTS; t++)
			{
				if(!trafficlights[t][trlights_uid]) continue;
				if(trafficlights[t][trlights_uid] == old_coop)
				{
					trafficlights[t][trlights_coop_uid] = 0;
					trafficlights[t][trlights_redtime] = 10;
					trafficlights[t][trlights_greentime] = 10;
					mq_format("UPDATE `trafficlights` SET `coop_id`='0', `redtime`='10', `greentime`='10' WHERE `id`='%d';", trafficlights[t][trlights_uid]);
					mq_send("QUpdateTL");
					break;
				}
			}
		}
		Info(playerid, "Para usunięta.");
		//-powrót do menu
		new strCommand[64];
		format(strCommand, 64, "/trafficlight %d", trafficlights[traffic_id][trlights_uid]);
		PC_EmulateCommand(playerid, strCommand);
		//-
		return 1;
	}
	new pair_traffic_id = GetTrafficLightID(input);
	if(pair_traffic_id == -1) return Error(playerid, "Brak świateł o takim ID.");
	//łączenie
	trafficlights[traffic_id][trlights_coop_uid] = trafficlights[pair_traffic_id][trlights_uid];
	trafficlights[pair_traffic_id][trlights_coop_uid] = trafficlights[traffic_id][trlights_uid];
	//resetowanie czasów
	trafficlights[traffic_id][trlights_redtime] = 10;
	trafficlights[pair_traffic_id][trlights_redtime] = 10;
	trafficlights[traffic_id][trlights_greentime] = 10;
	trafficlights[pair_traffic_id][trlights_greentime] = 10;
	//aktualizacja w DB
	mq_format("UPDATE `trafficlights` SET `coop_id`='%d', `redtime`='10', `greentime`='10' WHERE `id`='%d';", trafficlights[traffic_id][trlights_uid], trafficlights[pair_traffic_id][trlights_uid]);
	mq_send("QUpdateTL");
	mq_format("UPDATE `trafficlights` SET `coop_id`='%d', `redtime`='10', `greentime`='10' WHERE `id`='%d';", trafficlights[pair_traffic_id][trlights_uid], trafficlights[traffic_id][trlights_uid]);
	mq_send("QUpdateTL");
	Info(playerid, "Światła zostały zsynchronizowane. "COL_RED"Ustaw czasy świateł!");
	//-powrót do menu
	new strCommand[64];
	format(strCommand, 64, "/trafficlight %d", trafficlights[traffic_id][trlights_uid]);
	PC_EmulateCommand(playerid, strCommand);
	//-
	return 1;
}


task Process_TrafficLights()
{
	for(new t; t < MAX_TRAFFICLIGHTS; t++)
	{
		if(!trafficlights[t][trlights_uid]) continue;
		if(trafficlights[t][trlights_coop_uid] == 0)//nie ma świateł współpracujących
		{
			//miganie żółtym światłem
			if(trafficlights[t][trlights_light] == 0) SetTrafficLightLight(t, 4);
			else SetTrafficLightLight(t, 0);
		}
		else
		{
			new pair_traffic = GetTrafficLightID(trafficlights[t][trlights_coop_uid]);
			if(pair_traffic < t)//sygnalizator dominujący skryptowo
			{
				switch(trafficlights[t][trlights_light])
				{
					case 1://jest czerwone
					{
						if(trafficlights[t][trlights_tick] < trafficlights[t][trlights_redtime])
						{
							trafficlights[t][trlights_tick]++;
							new time = trafficlights[t][trlights_redtime]-trafficlights[t][trlights_tick];
							SetTrafficLightLight(t, 1, time);
							SetTrafficLightLight(pair_traffic, 3, time);
						}
						else
						{
							trafficlights[t][trlights_tick] = 0;
							SetTrafficLightLight(t, 2, 0);
							SetTrafficLightLight(pair_traffic, 4, 0);
						}
					}
					case 2://żółto/czerwone
					{
						if(trafficlights[t][trlights_tick] < 1)
						{
							trafficlights[t][trlights_tick]++;
							SetTrafficLightLight(t, 2, 0);
							SetTrafficLightLight(pair_traffic, 4, 0);
						}
						else
						{
							trafficlights[t][trlights_tick] = 0;
							SetTrafficLightLight(t, 3, trafficlights[t][trlights_greentime]);
							SetTrafficLightLight(pair_traffic, 1, trafficlights[t][trlights_greentime]);
						}
					}
					case 3://zielone
					{
						if(trafficlights[t][trlights_tick] < trafficlights[t][trlights_greentime])
						{
							trafficlights[t][trlights_tick]++;
							new time = trafficlights[t][trlights_greentime]-trafficlights[t][trlights_tick];
							SetTrafficLightLight(t, 3, time);
							SetTrafficLightLight(pair_traffic, 1, time);
						}
						else
						{
							trafficlights[t][trlights_tick] = 0;
							SetTrafficLightLight(t, 4, 0);
						}
					}
					case 4://żółte
					{
						if(trafficlights[t][trlights_tick] < 1)
						{
							trafficlights[t][trlights_tick]++;
							SetTrafficLightLight(t, 4, 0);
							SetTrafficLightLight(pair_traffic, 2, 0);
						}
						else
						{
							trafficlights[t][trlights_tick] = 0;
							SetTrafficLightLight(t, 1, trafficlights[t][trlights_redtime]);
							SetTrafficLightLight(pair_traffic, 2, 0);
						}
					}
					default:
					{
						SetTrafficLightLight(t, 4);
					}
				}
			}
		}
	}
	return 1;
}

//0 - wszystkie wyłączone, 1 - czerwone, 2 - czerwone i żółte, 3 - zielone, - 4 żółte
stock SetTrafficLightLight(tid, light, counter = 0)
{
	new trafficlights_string[512];
	switch(light)
	{
		case 1://czerwone
		{
			format(trafficlights_string, 512, "»» SYGNALIZACJA ŚWIETLNA (ID: %d:%d) ««\n{FF0000}CZERWONE (%d)\n{3a3a3a}ŻÓŁTE\n{3a3a3a}ZIELONE", trafficlights[tid][trlights_uid], trafficlights[tid][trlights_coop_uid], counter);
			UpdateDynamic3DTextLabelText(trafficlights[tid][trlights_text3d], 0xFF0000FF, trafficlights_string);
			trafficlights[tid][trlights_light] = light;
		}
		case 2://czerwono żółte
		{
			format(trafficlights_string, 512, "»» SYGNALIZACJA ŚWIETLNA (ID: %d:%d) ««\n{FF0000}CZERWONE\n{FFC100}ŻÓŁTE\n{3a3a3a}ZIELONE", trafficlights[tid][trlights_uid], trafficlights[tid][trlights_coop_uid]);
			UpdateDynamic3DTextLabelText(trafficlights[tid][trlights_text3d], 0xFF0000FF, trafficlights_string);
			trafficlights[tid][trlights_light] = light;
		}
		case 3://zielone
		{
			format(trafficlights_string, 512, "»» SYGNALIZACJA ŚWIETLNA (ID: %d:%d) ««\n{3a3a3a}CZERWONE\n{3a3a3a}ŻÓŁTE\n{00FF00}ZIELONE (%d)", trafficlights[tid][trlights_uid], trafficlights[tid][trlights_coop_uid], counter);
			UpdateDynamic3DTextLabelText(trafficlights[tid][trlights_text3d], 0x00FF00FF, trafficlights_string);
			trafficlights[tid][trlights_light] = light;
		}
		case 4://żółte
		{
			format(trafficlights_string, 512, "»» SYGNALIZACJA ŚWIETLNA (ID: %d:%d) ««\n{3a3a3a}CZERWONE\n{FFC100}ŻÓŁTE\n{3a3a3a}ZIELONE", trafficlights[tid][trlights_uid], trafficlights[tid][trlights_coop_uid], counter);
			trafficlights[tid][trlights_light] = light;
			UpdateDynamic3DTextLabelText(trafficlights[tid][trlights_text3d], 0xFFC100FF, trafficlights_string);
		}
		default://wyłącz wszystkie
		{
			format(trafficlights_string, 512, "»» SYGNALIZACJA ŚWIETLNA (ID: %d:%d) ««\n{3a3a3a}CZERWONE\n{3a3a3a}ŻÓŁTE\n{3a3a3a}ZIELONE", trafficlights[tid][trlights_uid], trafficlights[tid][trlights_coop_uid], counter);
			UpdateDynamic3DTextLabelText(trafficlights[tid][trlights_text3d], 0x3a3a3aFF, trafficlights_string);
			trafficlights[tid][trlights_light] = 0;
		}
	}
	return 1;
}
