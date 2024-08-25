///******************************CALLBACKI GRACZA*************************************************
//**********************************************************************************************************CONNECT/DISCONNECT
//new SV_SGSTREAM:streamv[MAX_PLAYERS];
public OnPlayerConnect(playerid)
{
	if(IsPlayerNPC(playerid)) return 1;
	GetPlayerIp(playerid, playerid_lastip[playerid], 64);
	SetTimerEx("DelayOnPlayerConnect", 25, false, "d", playerid);
	return 1;
}
task DelayOnPlayerConnect(playerid)
{
	if(!IsPlayerConnected(playerid)) return 1;
	ResetPoolPlayer(playerid);
	for(new player_stats:r; r < player_stats; r++)//czyszczenie zmiennych
	{
		gracz[playerid][r] = 0;
	}
	for(new ac; ac < 60; ac++)
	{
		EnableAntiCheatForPlayer(playerid, ac, false);
	}
	Streamer_DestroyAllVisibleItems(playerid, STREAMER_TYPE_3D_TEXT_LABEL);
	Streamer_SetVisibleItems(STREAMER_TYPE_3D_TEXT_LABEL, MAX_3DTEXT_GLOBAL, playerid);
	Init_TextDrawPlayer(playerid);
	fb_LoadPlayerTextDraws(playerid);
	RemoveBuilding(playerid);
	SetPVarInt(playerid, "RePM", -1);
	PlayAudioStreamForPlayer(playerid, "http://sebaqq6.pl/highwaylife/login.mp3");
	ShowPanorama(playerid);
	//--
	new clientVersion[24];
	GetPlayerVersion(playerid, clientVersion, 24);
	if(!compare("0.3.DL-R1", clientVersion)) gracz[playerid][unused03DL] = true;
	//******************************************************************************************************CZAT POWITANIE
	SendClientMessage(playerid, -1, "{006400}«{2a8279}••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••{006400}»");
	SendClientMessage(playerid, -1, "{006400}«{2a8279} Witaj na polskim serwerze truck {5fc536}Highway Life{2a8279}! {006400}»");
	SendClientMessage(playerid, -1, "{006400}«{2a8279} Portal serwera: {c62121}highwaylife.pl {006400}»");
	SendClientMessage(playerid, -1, "{006400}«{2a8279} Forum serwera: {c62121}forum.highwaylife.pl {006400}»");
	SendClientMessage(playerid, -1, "{006400}«{2a8279} TeamSpeak3 serwera: {c62121}ts.highwaylife.pl {006400}»");
	SendClientMessage(playerid, -1, "{006400}«{2a8279} Frakcje:{e78914} Policja • Straż Graniczna • Służby Ratunkowe • Pomoc Drogowa • Taxi • Mafia Paliwowa{006400}»");
	SendClientMessage(playerid, -1, "{006400}«{e78914} Zostań kim tylko chcesz{2a8279}! Kurierem, zawodowym kierowcą, właścicielem frakcji bądź {e78914}firmy{2a8279}! {006400}»");
	SendClientMessage(playerid, -1, "{006400}«{2a8279} Baw się dobrze, miłej gry życzy Ekipa {5fc536}Highway Life{2a8279}! {006400}»");
	SendClientMessage(playerid, -1, "{006400}«{2a8279}••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••{006400}»");
	return 1;
}

public OnPlayerFinishedDownloading(playerid, virtualworld)
{
	if(!gracz[playerid][loggedin]) ShowPanorama(playerid);
	return 1;
}

new baseurl[] = "http://85.255.2.44/models/";
public OnPlayerRequestDownload(playerid, type, crc)
{
	new fullurl[256+1];
	new dlfilename[64+1];
	new foundfilename=0;
	
	if(!IsPlayerConnected(playerid)) return 0;
	
	if(type == DOWNLOAD_REQUEST_TEXTURE_FILE) {
		foundfilename = FindTextureFileNameFromCRC(crc,dlfilename,64);
	}
	else if(type == DOWNLOAD_REQUEST_MODEL_FILE) {
	    foundfilename = FindModelFileNameFromCRC(crc,dlfilename,64);
	}

	if(foundfilename) {
	    format(fullurl,256,"%s/%s",baseurl,dlfilename);
	    RedirectDownload(playerid,fullurl);
	}
	return 1;
}

stock GetPlayerSkin(playerid)
{
	new t_skin_standard = ov_GetPlayerSkin(playerid);
	new t_skin_custom = GetPlayerCustomSkin(playerid);
	new wynik = t_skin_standard;
	if(t_skin_custom != 0) wynik = t_skin_custom;
	return wynik;
}

public OnPlayerDisconnect(playerid, reason)
{
	if(IsPlayerNPC(playerid)) return 1;
	Voice_OnPlayerDisconnect(playerid);
	Disconnect(playerid, reason);
	return 1;
}

stock Disconnect(playerid, reason = 1)
{
	if(!gracz[playerid][loggedin]) return 1;
	if(gracz[playerid][status_lunapark] == LPARK_ASG) ASG_OnPlayerExit(playerid);
	CancelCreateZone(playerid);
	ResetRope(playerid);
	ResetPoolPlayer(playerid);
	DestroyLabelNick(playerid);
	SendSignalDisconnectAdminSpec(playerid);
	SendSignalDisconnectPursuit(playerid);
	Gym_Disconnect(playerid);
	StopCombineMode(playerid);
	Dystrybutor_Hide(playerid);
	Streamer_ToggleIdleUpdate(playerid, 0);
	//usuwanie pojazdów gracza
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		if(pojazd[v][v_model] == 0) continue;
		if(pojazd[v][v_owner] == gracz[playerid][UID])
		{
			if(pojazd[v][v_owner_type] == VEHICLE_PLAYER)
			{
				if(!VehicleCanParkHere(v, true))
				{
					if(pojazd[v][v_id] != 0)
					{
						mq_format("UPDATE `pojazdy` SET `status`='0', `rlg_lastused`='0' WHERE `id`='%d';", pojazd[v][v_id]);
						mq_send("QUpdateVehicleStatus");
					}
				}
				RemoveVehicle(v);
			}
		}
	}
	if(gracz[playerid][opu_vehicleid] != 0)
	{
		if(pojazd[gracz[playerid][opu_vehicleid]][v_owner_type] == VEHICLE_PUBLIC && pojazd[gracz[playerid][opu_vehicleid]][v_owner] == VO_ADMINVEH)
		{
			RemoveVehicle(gracz[playerid][opu_vehicleid]);
		}
	}
	//odkuwanie graczy od siebie
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(!gracz[p][loggedin]) continue;
		if(!gracz[p][przykuty]) continue;
		if(gracz[p][przykutydo] == playerid)
		{
			gracz[p][przykutydo] = 0;
			gracz[p][przykuty] = false;
		}
	}
	//
	/*new szDisconnectReason[3][] =
	{
		"Timeout",
		"Wyszedł",
		"Kick/Ban"
	};
	SendClientMessageToAllEx(0x747474FF, "••• {908f8f}Gracz {FFFFFF}%s{908f8f}(%d) opuścił grę! (%d minut) ({5e5e5e}%s{908f8f}) {747474}•••", nick(playerid), playerid, (serwer[time_timestamp]-gracz[playerid][loginhistory_start])/60, szDisconnectReason[reason]);
	*/
	new szDisconnectReason[3][] =
	{
		"Timeout",
		"Wyszedł",
		"Kick/Ban"
	};
	new strLog[256];
	format(strLog, 256, "{747474}••• {908f8f}Gracz {FFFFFF}%s{908f8f}(%d) opuścił grę! (%d minut) ({5e5e5e}%s{908f8f}) {747474}•••", nick(playerid), playerid, (serwer[time_timestamp]-gracz[playerid][loginhistory_start])/60, szDisconnectReason[reason]);
	SavePublicChatLog(strLog);	
	ShowJoinLeaveTD(playerid, 1, reason, (serwer[time_timestamp]-gracz[playerid][loginhistory_start])/60);
	EndLoginHistory(playerid);
	Process_CourierJob(playerid, 1);
	ClearTrailerSelect(playerid);
	ClearObjective(playerid);
	gracz[playerid][spawned] = false;
	gracz[playerid][loggedin] = false;
	Process_Caller(playerid);
	if(gracz[playerid][pointer_object] != 0)
	{
		DestroyDynamicObject(gracz[playerid][pointer_object]);
		gracz[playerid][pointer_object] = 0;
	}
	//OnPlayerExitVehicle(playerid, GetPlayerVehicleID(playerid));
	if(PlayerEditObject[playerid])
	{
		DeleteObject(PlayerEditObject[playerid]);
		CancelEdit(playerid);
		PlayerEditObject[playerid] = 0;
		Streamer_Update(playerid);
	}
//	gps_RemovePlayer(playerid);
	rpc_GangZoneDestroyAll(playerid);
	//*wygaszanie ogniska
	ognisko[playerid][o_status] = 1;
	Process_Campfire(playerid);
	//*end wygaszanie
	eventp_OnPlayerDisconnect(playerid, reason);
	printf("[PLAYER]Gracz %s wylogowal sie poprawnie.", nick(playerid));
	return 1;
}
//**************************************************************************************************************************SPAWN/DEATH
public OnPlayerSpawn(playerid)
{
	if(IsPlayerNPC(playerid)) return 1;
	if(!gracz[playerid][loggedin])
	{
		CheckS0beit(playerid);
		return 1;
	}
	Process_PoolPlayerSize();
	gracz[playerid][spawned] = true;
	if(gracz[playerid][first_spawn])
	{ 
		//TogglePlayerControllable(playerid, false);
		gracz[playerid][first_spawn] = false;
		SetTimerEx("LoadRelogState", 1000, false, "d", playerid);
		Streamer_Update(playerid);
		GetPlayerPos(playerid, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);
		SetPlayerPos(playerid, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);
		PreloadAnimations(playerid);
		printf("[PLAYER]Gracz %s zespawnowal sie pierwszy raz. IP: %s", nick(playerid), playerip(playerid));
	}
	else
	{
		printf("[PLAYER]Gracz %s zespawnowal sie. IP: %s", nick(playerid), playerip(playerid));
	}
	SetSpawnInfo(playerid, 0, gracz[playerid][Skin], GetPVarFloat(playerid, "spawn_X"), GetPVarFloat(playerid, "spawn_Y"), GetPVarFloat(playerid, "spawn_Z"), GetPVarFloat(playerid, "spawn_R"), 0, 0, 0, 0, 0, 0);
	SetGoodSkillLevel(playerid);
	SetPlayerSkin(playerid, gracz[playerid][last_skin]);//naprawia buga skinami po śmierci (bug powodowany przez setspawninfo)
	LoadUsedAccessories(playerid);
	
	gracz[playerid][lastshotedby] = INVALID_PLAYER_ID;
	LoadFractionWeapons(playerid, gracz[playerid][frakcja]);
	Process_BrutallyWounded(playerid);
	if(gracz[playerid][bus_travel])
	{
		new where = GetPVarInt(playerid, "bustravel_where");
		SetPlayerPos(playerid, bus_stations[where][bs_X], bus_stations[where][bs_Y], bus_stations[where][bs_Z]);
		gracz[playerid][bus_travel] = false;
	}
	Streamer_Update(playerid);
	SetPlayerHealth(playerid, gracz[playerid][HP]);
	if(GetPVarInt(playerid, "PlayerDeathOnASG") == 1)
	{
		DeletePVar(playerid, "PlayerDeathOnASG");
		ASG_OnPlayerSpawn(playerid);
	}
	if(gracz[playerid][fight_timestamp_end] > serwer[time_timestamp] && gracz[playerid][fight_timestamp_end] != 0)
	{
		SetPlayerFightingStyle(playerid, gracz[playerid][fight_style]);
	}
	else 
	{
		gracz[playerid][fight_timestamp_end] = 0;
		gracz[playerid][fight_style] = FIGHT_STYLE_NORMAL;
		SetPlayerFightingStyle(playerid, FIGHT_STYLE_NORMAL);
		mq_format("UPDATE `Konta` SET `fight_timestamp_end`='%d', `fight_style`='%d' WHERE `id`='%d';", gracz[playerid][fight_timestamp_end], gracz[playerid][fight_style], gracz[playerid][UID]);
		mq_send("QUpdateFightTimestamp");
	}
	return 1;
}


public OnPlayerDeath(playerid, killerid, reason)
{
	gracz[playerid][last_skin] = GetPlayerSkin(playerid);
	SetSpawnInfo(playerid, 0, gracz[playerid][Skin], gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], gracz[playerid][PosR], 0, 0, 0, 0, 0, 0);
	if(gracz[playerid][status_lunapark] != LPARK_ASG)//nie jest na asg - deaktywacja BW
	{
		if(IsPlayerOnDutyFraction(playerid) && killerid != INVALID_PLAYER_ID)
		{
			if(IsPlayerOnDutyFraction(killerid) && (gracz[killerid][frakcja] == F_MAFIA || gracz[killerid][frakcja] == F_POLICE || gracz[killerid][frakcja] == F_BORDERGUARD))
			{
				SetPlayerBW(playerid, 3, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);
			}
			else if(isvip(playerid)) SetPlayerBW(playerid, 1, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);
			else SetPlayerBW(playerid, 3, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);
		}
		else if(IsPlayerOnDutyFraction(playerid) && gracz[playerid][lastshotedby] != INVALID_PLAYER_ID)
		{
			if(IsPlayerOnDutyFraction(gracz[playerid][lastshotedby]) && (gracz[gracz[playerid][lastshotedby]][frakcja] == F_MAFIA || gracz[gracz[playerid][lastshotedby]][frakcja] == F_POLICE || gracz[gracz[playerid][lastshotedby]][frakcja] == F_BORDERGUARD))
			{
				SetPlayerBW(playerid, 3, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);
			}
			else if(isvip(playerid)) SetPlayerBW(playerid, 1, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);
			else SetPlayerBW(playerid, 3, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);
		}
		else if(isvip(playerid)) SetPlayerBW(playerid, 1, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);
		else SetPlayerBW(playerid, 3, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);
	}
	else
	{
		ASG_OnPlayerDeath(playerid, killerid, reason);
		SetPVarInt(playerid, "PlayerDeathOnASG", 1);
	}
	ResetRope(playerid);
	if(PlayerEditObject[playerid])
	{
		DeleteObject(PlayerEditObject[playerid]);
		CancelEdit(playerid);
		PlayerEditObject[playerid] = 0;
		Streamer_Update(playerid);
	}
	return 1;
}
//********************************************************************************************************************ONPLAYERUPDATE
public OnPlayerUpdate(playerid)
{
	gracz[playerid][opu_timestamp] = serwer[time_timestamp];
	if(!gracz[playerid][loggedin]) return 1;
	gracz[playerid][opu_vehicleid] = GetPlayerVehicleID(playerid);

	if(gracz[playerid][truckbuy_status]) 
	{
		GetPlayerKeys(playerid, gracz[playerid][gpk_keys],  gracz[playerid][gpk_updown],  gracz[playerid][gpk_leftright]);
		Vehicle_OnPlayerKeyStateChange(playerid, 0, 0);
	}
	if(combine_mode[playerid][c_id] != 0)
	{
		GetPlayerKeys(playerid, gracz[playerid][gpk_keys],  gracz[playerid][gpk_updown],  gracz[playerid][gpk_leftright]);
		if(gracz[playerid][gpk_leftright] == 128 || gracz[playerid][gpk_leftright] == -128)
		{
			combine_OnPlayerKeyStateChange(playerid, gracz[playerid][gpk_leftright], 1);
		}
		else if(gracz[playerid][gpk_updown] == 128 || gracz[playerid][gpk_updown] == -128)
		{
			combine_OnPlayerKeyStateChange(playerid, gracz[playerid][gpk_updown], 0);
		}
	}
	//---
	if(gracz[playerid][opu_delay_inprogress] == false)
	{
		gracz[playerid][opu_delay_inprogress] = true;
		SetTimerEx("delay_OnPlayerUpdate", 1, false, "d", playerid);
	}
	if(gracz[playerid][relog_data_loaded] == false) return 0;
	return 1;
}

task delay_OnPlayerUpdate(playerid)
{
	ASG_OnPickup(playerid);
	HUD_UpdateWEAPON(playerid);
	gracz[playerid][opu_vehicleid] = GetPlayerVehicleID(playerid);
	gracz[playerid][opu_speed] = GetVehSpeed(gracz[playerid][opu_vehicleid]);
	if(gracz[playerid][loading_objects])
	{
		if(gracz[playerid][opu_speed]) 
		{
			SetVehicleVelocity(gracz[playerid][opu_vehicleid], 0.0, 0.0, 0.0);
		}
	}
	GetPlayerPos(playerid, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);
	if(!gracz[playerid][delay_enable_engine] && gracz[playerid][carhud_speedup_tick] < GetTickCount()) 
	{
		CarHUD_SetSpeed(playerid, gracz[playerid][opu_speed]);
		gracz[playerid][carhud_speedup_tick] = GetTickCount()+100;
	}
	//01100101011001010110010101100101011001010110010101100101011001010110010101100101011001010110010101100101
	if(gracz[playerid][admin_duty] < 1)
	{
		if(GetPlayerVehicleSeat(playerid) == 0)
		{
			if(gracz[playerid][opu_speed] == 0) gracz[playerid][zerosto_starttime] = GetTickCount();
			for(new v; v < MAX_CARSPEC; v++)
			{
				if(pojazd_spec[v][vspec_model] == pojazd[gracz[playerid][opu_vehicleid]][v_model])
				{
					if(pojazd[gracz[playerid][opu_vehicleid]][v_whilenitro] == false)
					{
						if(gracz[playerid][zerosto_starttime] != 0)
						{
							if(gracz[playerid][opu_speed] >= 100)
							{
								new Float:result_0100 = GetTickCount()-gracz[playerid][zerosto_starttime];
								gracz[playerid][zerosto_starttime] = 0;
								result_0100 = result_0100/1000;
								//SendClientMessageEx(playerid, PlayerColors[random(sizeof(PlayerColors))], "[0-100 WYNIK] "COL_WHITE"Pojazd "COL_GREEN"%s"COL_WHITE" rozpędził się od 0 do 100 w "COL_RED"%0.1f"COL_WHITE" sekund.", GetVehicleName(GetVehicleModel(GetPlayerVehicleID(playerid))), result_0100);
								if(result_0100 < pojazd_spec[v][vspec_0100]-0.5)
								{
									format(temp_string, 144, "[0-100km/h] %s(%d) [%s] "COL_RED"wynik: %0.1fs "COL_GREEN"specyfikacja: %0.1fs", nick(playerid), playerid, GetVehicleName(pojazd[gracz[playerid][opu_vehicleid]][v_model]), result_0100+0.01, pojazd_spec[v][vspec_0100]+0.01);
									SendEyeveh(temp_string);
								}
							}
						}
					}
					if(gracz[playerid][opu_speed] > pojazd_spec[v][vspec_vmax]+15)
					{
						if(!Spam(playerid, SPAM_EYESPEEDVEH, 3, false))
						{
							format(temp_string, 144, "[v-max] %s(%d) [%s] "COL_RED"wynik: %d km/h "COL_GREEN"specyfikacja: %d km/h", nick(playerid), playerid, GetVehicleName(pojazd[gracz[playerid][opu_vehicleid]][v_model]), gracz[playerid][opu_speed], pojazd_spec[v][vspec_vmax]);
							SendEyeveh(temp_string);
						}
					}
					break;
				}
			}
		}
	}
	//011001011001010110010101100101011001010110010101100101011001010110010101100101011001010110010101100101
	if(gracz[playerid][carhud_status] > 0)
	{
		if(pojazd[gracz[playerid][opu_vehicleid]][v_handbrake]) 
		{
			if(gracz[playerid][opu_speed]) 
			{
				if(!gracz[playerid][dystrybutor_status]) GameTextForPlayer(playerid, "~n~~n~~r~ZWOLNIJ RECZNY~n~~w~Klawisz ~y~spacji~w~ lub ~y~2",  1000, 3);
				SetVehicleVelocity(gracz[playerid][opu_vehicleid], 0.0, 0.0, 0.0);
			}
		}
		static engine, lights, alarm, doors, bonnet, boot, objective;
		GetVehicleParamsEx(gracz[playerid][opu_vehicleid], engine, lights, alarm, doors, bonnet, boot, objective);
		if(!engine)
		{
			if(!gracz[playerid][wypadek])
			{
				GetPlayerKeys(playerid, gracz[playerid][gpk_keys],  gracz[playerid][gpk_updown],  gracz[playerid][gpk_leftright]);
				if(gracz[playerid][gpk_keys] != 0 && gracz[playerid][gpk_keys] != KEY_NO && gracz[playerid][gpk_keys] != KEY_CROUCH && gracz[playerid][gpk_keys] != KEY_ACTION && gracz[playerid][gpk_keys] != KEY_YES && gracz[playerid][gpk_keys] != KEY_HANDBRAKE || gracz[playerid][gpk_leftright] != 0)
				{
					if(gracz[playerid][delay_enable_engine]) GameTextForPlayer(playerid, "~n~~n~~y~CIERPLIWOSCI~n~~g~SILNIK JUZ SIE URUCHAMIA",  1000, 3);
					else GameTextForPlayer(playerid, "~n~~n~~b~ODPALANIE/GASZENIE SILNIKA~n~~w~Klawisz ~y~Y~w~ lub ~y~2",  1000, 3);
				}
			}
		}
	}
	Process_SpeedCap(playerid);
	//WYKRYWANIE WYPADKU
	new Float:tmpVehicleHP, Float:tmpCrashSpeed;
	GetVehicleHealth(gracz[playerid][opu_vehicleid], tmpVehicleHP);
	new
	Float:fX,
	Float:fY,
	Float:fZ
	;
	GetVehicleVelocity(gracz[playerid][opu_vehicleid], fX, fY, fZ);
	tmpCrashSpeed = (floatsqroot((fX * fX) + (fY * fY) + (fZ * fZ)) * 100);
	if(pojazd[gracz[playerid][opu_vehicleid]][v_crash_Health] > tmpVehicleHP)
	{
		//CallLocalFunction("OnPlayerCrashVehicle", "iif", playerid, gracz[playerid][opu_vehicleid], floatsub(pojazd[gracz[playerid][opu_vehicleid]][v_crash_Health], tmpVehicleHP));
		if(floatabs(pojazd[gracz[playerid][opu_vehicleid]][v_crash_Health] - tmpVehicleHP) >= POTENTIAL_CRASH_DAMAGE  && floatabs(pojazd[gracz[playerid][opu_vehicleid]][v_crash_Speed] - tmpCrashSpeed) >= 5.0)
		{
			OnPlayerCrashVehicle(playerid, gracz[playerid][opu_vehicleid], floatsub(pojazd[gracz[playerid][opu_vehicleid]][v_crash_Health], tmpVehicleHP));
			Process_PlayerADR(playerid, 2);
		}
		else if(floatabs(pojazd[gracz[playerid][opu_vehicleid]][v_crash_Health] - tmpVehicleHP) >= 1.1 && floatabs(pojazd[gracz[playerid][opu_vehicleid]][v_crash_Speed] - tmpCrashSpeed) >= 1.1)
		{
			Process_PlayerADR(playerid, 1);
		}
	}
	pojazd[gracz[playerid][opu_vehicleid]][v_crash_Health] = tmpVehicleHP;
	pojazd[gracz[playerid][opu_vehicleid]][v_crash_Speed] = tmpCrashSpeed;
	//KEYS AFK WSAD
	if(!(gracz[playerid][afk_detect_timestamp]-serwer[time_timestamp] > (60*4)-1))
	{
		GetPlayerKeys(playerid, gracz[playerid][gpk_keys],  gracz[playerid][gpk_updown],  gracz[playerid][gpk_leftright]);
		if(gracz[playerid][gpk_keys] != 0 || gracz[playerid][gpk_updown] != 0 || gracz[playerid][gpk_leftright] != 0)
		{
			ResetIdleAFK(playerid);
		}
	}
	//turbo raindance
	if(gracz[playerid][frakcja] == F_EMERGENCY)
	{
		if(IsPlayerOnDutyFraction(playerid))
		{
			if(pojazd[gracz[playerid][opu_vehicleid]][v_model] == 563)
			{
				GetPlayerKeys(playerid, gracz[playerid][gpk_keys],  gracz[playerid][gpk_updown],  gracz[playerid][gpk_leftright]);
				if(gracz[playerid][gpk_keys] == KEY_FIRE)
				{
					new Float:vx, Float:vy, Float:vz;
					GetVehicleVelocity(gracz[playerid][opu_vehicleid], vx, vy, vz);
					if(floatabs(vx) < 40 && floatabs(vy) < 40)
					{
						SetVehicleVelocity(gracz[playerid][opu_vehicleid], vx * 1.05, vy * 1.05, vz);
					}
				}
			}
		}
	}
	//-----------
	if(gracz[playerid][opu_vehicleid] != 0)
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			new oid = serwer[actual_oilid];
			if(oilSR_data[oid][ft_isfall])
			{
				new Float:lPos[3];
				lPos[0] = oilSR_position[oid][0];
				lPos[1] = oilSR_position[oid][1];
				lPos[2] = oilSR_position[oid][2];
				if(IsPlayerInRangeOfPoint(playerid, 4.0, lPos[0], lPos[1], lPos[2]))
				{
					/*new Float:ofoil[2];
					MRandFloatRange(0.2, 0.5, ofoil[0]);
					MRandFloatRange(0.2, 0.5, ofoil[1]);
					new Float:vx, Float:vy, Float:vz;
					GetVehicleVelocity(gracz[playerid][opu_vehicleid], vx, vy, vz);
					SetVehicleVelocity(gracz[playerid][opu_vehicleid], vx + ofoil[0], vy + ofoil[1], vz);*/
					if(MRandom(2) == 1) SetVehicleAngularVelocity(gracz[playerid][opu_vehicleid], 0.0, 0.0, 0.06);
					else SetVehicleAngularVelocity(gracz[playerid][opu_vehicleid], 0.0, 0.0, -0.07);
					LeftNotifyShow(playerid, "Poslizg", "Wjechales w plame oleju. Twoj pojazd wpadl w poslizg.", LN_RED);
				}
			}
		}
	}
	gracz[playerid][opu_delay_inprogress] = false;
	return 1;
}
//********************************************************************************************************************DIALOG RESPONSE
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#if defined DEBUGHL
	printf("[DEBUGHL] dialogid: %d | response: %d | listitem: %d | input: '%s'", dialogid, response, listitem, inputtext);
	#endif
	return 1;
}
//********************************************************************************************************************STATE CHANGE
public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(!gracz[playerid][loggedin]) return 1;
	new vehicleid = GetPlayerVehicleID(playerid);
	if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER)//z piechoty na kierowce
	{
		if(IsPlayerCanDrive(playerid, vehicleid))
		{
			if(pojazd[vehicleid][v_owner_type] != VEHICLE_PLAYER)
			{
				if(strlen(pojazd[vehicleid][v_lastuser]) > 1)
				{
					new strMsg[144];
					format(strMsg, 144, "Ostatnio ten pojazd prowadził: "COL_RED"%s", pojazd[vehicleid][v_lastuser]);
					Info(playerid, strMsg);
				}
				format(pojazd[vehicleid][v_lastuser], 32, "%s", nick(playerid));
			}
			gracz[playerid][last_vehicleid] = vehicleid;

			gracz[playerid][gps_refreshtrack] = true;
			gracz[playerid][gps_tstart_X] = 999.0;
			gracz[playerid][gps_tstart_Y] = 999.0;
			gracz[playerid][gps_tstart_Z] = -1000.0;
			if(SpecialVehicle(vehicleid))
			{
				new engine, lights, alarm, doors, bonnet, boot, objective;
				GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(vehicleid, 1, lights, alarm, doors, bonnet, boot, objective);
				if(pojazd[vehicleid][v_model] == 563)
				{
					LeftNotifyShow(playerid, "Raindance", "1. Wcisnij SPACJE aby wlaczyc gaszenie pozaru helikopterem.~n~2. Wcisnij lewy Lewy-ALT aby uzyc TURBO.");
				}
			}
			else
			{
				Courier_Event(playerid, 1);
				CarHUD_Show(playerid);
				Process_CarHUD(playerid);
				HideVehicleLabel(vehicleid);
				if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION && pojazd[vehicleid][v_owner] == F_TAXI)//pojazdy taxi
				{
					Taxometr_Show(playerid);
					Taxometr_SetPricePerKM(playerid, pojazd[vehicleid][v_taxometr_price_per_km]);
					Taxometr_SetDistance(playerid, pojazd[vehicleid][v_taxometr_distance]);
					Taxometr_SetPrice(playerid, pojazd[vehicleid][v_taxometr_price]);
				}
				//pokazywanie TD w prawym górnym rogu z info o towarze
				if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER)
				{
					if(IsVehicleTruck(pojazd[vehicleid][v_model]) == 1)//trucki z naczepami
					{
						new trailerid = GetVehicleTrailer(vehicleid);
						if(trailerid != 0)
						{
							new strTemp[24];
							Get2DZone(pojazd[pojazd[trailerid][v_cargo_destvid]][v_X], pojazd[pojazd[trailerid][v_cargo_destvid]][v_Y], strTemp, 20);
							CargoInfo_Show(playerid, goods[pojazd[trailerid][v_cargo]][gds_name], pojazd[trailerid][v_cargo_amount], 0, strTemp, pojazd[trailerid][v_cargo_price], "kurs");
						}
						else CargoInfo_Hide(playerid);
					}
					else if(IsVehicleTruck(pojazd[vehicleid][v_model]) == 2)//trucki bez naczep
					{
						if(pojazd[vehicleid][v_cargo] != 0)//ma towar
						{
							new strTemp[24];
							Get2DZone(pojazd[vehicleid][v_cargo_target_X], pojazd[vehicleid][v_cargo_target_Y], strTemp, 20);
							if(pojazd[vehicleid][v_cargo] == 1)//KURIER
							{
								CargoInfo_Show(playerid, goods[pojazd[vehicleid][v_cargo]][gds_name], pojazd[vehicleid][v_cargo_amount], 1, strTemp, pojazd[vehicleid][v_cargo_price], "kurs");
							}
							else
							{
								CargoInfo_Show(playerid, goods[pojazd[vehicleid][v_cargo]][gds_name], pojazd[vehicleid][v_cargo_amount], 0, strTemp, pojazd[vehicleid][v_cargo_price], "kurs");
								if(!gracz[playerid][objective_status]) SetObjective(playerid, ""COL_RED"• "COL_BLUE"Aby dostarczyć zlecenie, wpisz: "COL_GREEN"/zlecenie dostarcz "COL_GREY"[/zlecenie d] "COL_RED"•", pojazd[vehicleid][v_cargo_target_X], pojazd[vehicleid][v_cargo_target_Y], pojazd[vehicleid][v_cargo_target_Z], true);
							}
						}
						else CargoInfo_Hide(playerid);
					}
				}
				else CargoInfo_Hide(playerid);

				//----ustawianie ogarnicznika jeśli coś jest popuste
				if(IsVehicleWornOut(vehicleid, 11) || IsVehicleWornOut(vehicleid, 12) || IsVehicleWornOut(vehicleid, 8) || IsVehicleWornOut(vehicleid, 5) || IsVehicleWornOut(vehicleid, 13) || IsVehicleWornOut(vehicleid, 10))
				{
					new veh_v_max;
					for(new v; v < MAX_CARSPEC; v++)
					{
						if(pojazd_spec[v][vspec_model] == pojazd[vehicleid][v_model])
						{
							veh_v_max = pojazd_spec[v][vspec_vmax];
							break;
						}
					}
					new Float:new_v_max = (80.0/100.0)*veh_v_max;
					//SetPlayerSpeedCap: 0.46 == 100 KM/H
					new Float:spsc_val = 0.0046*new_v_max;
					SetPlayerSpeedCap(playerid, spsc_val);
					//printf("spsc_val: %f | new_v_max: %f | veh_v_max: %d", spsc_val, new_v_max, veh_v_max);
				}
				else//ustawienie vmaxu
				{
					new veh_v_max;
					for(new v; v < MAX_CARSPEC; v++)
					{
						if(pojazd_spec[v][vspec_model] == pojazd[vehicleid][v_model])
						{
							veh_v_max = pojazd_spec[v][vspec_vmax];
							break;
						}
					}
					new Float:new_v_max = (140.0/100.0)*veh_v_max;
					//SetPlayerSpeedCap: 0.46 == 100 KM/H
					new Float:spsc_val = 0.0046*new_v_max;
					SetPlayerSpeedCap(playerid, spsc_val);	
				}
			}
		}
		else 
		{
			RemovePlayerFromVehicle(playerid);
			Error(playerid, "Nie możesz prowadzić tego pojazdu.");
		}
	} 
	else if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT)//z kierowcy na piechote
	{
		CarHUD_Hide(playerid);
		CargoInfo_Hide(playerid);
		Courier_Event(playerid, 2);
		Taxometr_Hide(playerid);
		gracz[playerid][pasy] = false;
		gracz[playerid][towtruck_trailerid] = 0;
	}
	else if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_PASSENGER)//z piechoty na pasażera
	{
		if(IsPlayerOnDutyFraction(playerid))
		{
			if(IsVehicleHelicopter(pojazd[vehicleid][v_model]))
			{
				LeftNotifyShow(playerid, "Lina", "Wcisnij klawisz 2 aby zjechac po linie.");
			}
		}
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION && pojazd[vehicleid][v_owner] == F_TAXI)//pojazdy taxi
		{
			Taxometr_Show(playerid);
			Taxometr_SetPricePerKM(playerid, pojazd[vehicleid][v_taxometr_price_per_km]);
			Taxometr_SetDistance(playerid, pojazd[vehicleid][v_taxometr_distance]);
			Taxometr_SetPrice(playerid, pojazd[vehicleid][v_taxometr_price]);
		}
	}
	else if(oldstate == PLAYER_STATE_PASSENGER && newstate == PLAYER_STATE_ONFOOT)//z pasażera na piechote
	{
		Taxometr_Hide(playerid);
		gracz[playerid][pasy] = false;
		gracz[playerid][towtruck_trailerid] = 0;
	}
	Company_OnPlayerStateChange(playerid, newstate, oldstate);
	return 1;
}
//********************************************************************************************************************STATE CHANGE
public OnPlayerEnterCheckpoint(playerid)
{	
	if(gracz[playerid][autoszrot_id] != 0)
	{
		if(IsPlayerInRangeOfPoint(playerid, 3.0, XYZ_AUTOSZROT))
		{
			if(2500 <= Money(playerid))
			{
				mq_format("UPDATE `pojazdy` SET `status`='1' WHERE `id`='%d';", gracz[playerid][autoszrot_id]);
				mq_send("QUpdateVehicleStatus");
				mq_format("SELECT * FROM `pojazdy` WHERE `id`='%d';", gracz[playerid][autoszrot_id]);
				mq_send("LoadVehFromDB");
				gracz[playerid][autoszrot_id]  = 0;
				Info(playerid, "Pojazd jest zaparkowany na złomowisku. "COL_GREEN"Zaparkuj swój pojazd w nowym miejscu"COL_WHITE".");
				LeftNotifyShow(playerid, "Misja", "Pojazd jest zaparkowany na zlomowisku. ~g~Zaparkuj swoj pojazd w nowym miejscu~w~. Za odebranie pojazdu ze zlomowiska, zaplaciles ~g~2500$~w~.", LN_BLUE, 20);
				TakeMoney(playerid, 2500);
			}
			else LeftNotifyShow(playerid, "error", "Aby odebrac pojazd z ~y~auto szrotu~w~ musisz posiadac przy sobie ~g~2500$~w~.", LN_RED);
		}
	}
	else if(gracz[playerid][parkingpol_id] != 0)
	{
		if(IsPlayerInRangeOfPoint(playerid, 3.0, XYZ_PARKINGPOLICYJNY))
		{
			new price_pp = 2000;
			new strParkPol[512];
			if(price_pp <= Money(playerid))
			{
				mq_format("UPDATE `pojazdy` SET `status`='1' WHERE `id`='%d';", gracz[playerid][parkingpol_id]);
				mq_send("QUpdateVehicleStatus");
				mq_format("SELECT * FROM `pojazdy` WHERE `id`='%d';", gracz[playerid][parkingpol_id]);
				mq_send("LoadVehFromDB");
				gracz[playerid][parkingpol_id]  = 0;
				Info(playerid, "Pojazd jest zaparkowany na parkingu policyjnym. "COL_GREEN"Zaparkuj swój pojazd w nowym miejscu"COL_WHITE".");
				format(strParkPol, 512, "Pojazd jest zaparkowany na parkingu policyjnym. ~g~Zaparkuj swoj pojazd w nowym miejscu~w~. Za odebranie pojazdu z parkingu policyjnego, zaplaciles ~g~%d$~w~.", price_pp);
				LeftNotifyShow(playerid, "Misja", strParkPol, LN_BLUE, 20);
				TakeMoney(playerid, price_pp);
			}
			else 
			{
				format(strParkPol, 512, "Aby odebrac pojazd z ~y~parkingu policyjnego~w~ musisz posiadac przy sobie ~g~%d$~w~.", price_pp);
				LeftNotifyShow(playerid, "error", strParkPol, LN_RED);
			}
		}
	}
	if(Courier_Event(playerid, 3) != 2) 
	{
		DisablePlayerCheckpoint(playerid);
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
	}
	DriverLicenseNextCP(playerid);
	return 1;
}
//********************************************************************************************************************MODEL SELECT
public OnPlayerModelSelectionEx(playerid, response, extraid, modelid)
{
	if(!response) 
	{
		SetPVarInt(playerid, "PayForChangeSkin", 0);
		return 1;
	}
	if(extraid == MSEL_MOBJECTS)
	{
		new str_cmd[128];
		format(str_cmd, 128, "/mc %d", modelid);
		PC_EmulateCommand(playerid, str_cmd);
	}
	else if(extraid == MSEL_MDUTYSKIN)
	{
		new fid = gracz[playerid][frakcja];
		if(fid == 0) return 1;
		if(!IsPlayerOnDutyFraction(playerid)) 
		{
			SendClientMessageToAllEx(0x31F288FF, "••• Gracz {%06x}%s(%d) {31F288}rozpoczął służbę jako %s {31F288}•••", GetPlayerColor(playerid) >>> 8, nick(playerid), playerid, GetFractionName(fid, 1));
			new strDutyMsg[256];
			format(strDutyMsg, 256, "{31F288}••• Gracz {%06x}%s(%d) {31F288}rozpoczął służbę jako %s {31F288}•••", GetPlayerColor(playerid) >>> 8, nick(playerid), playerid, GetFractionName(fid, 1));
			SavePublicChatLog(strDutyMsg);
		}
		SetPlayerSkin(playerid, modelid);
		gracz[playerid][frakcja_onduty] = gracz[playerid][frakcja];
		if(IsPlayerOnDutyFraction(playerid)) OnPlayerStartFractionDuty(playerid);
	}
	else if(extraid == MSEL_CHANGESKIN)
	{
		if(IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Będąc na służbie nie możesz zmienić skina.");
		if(Money(playerid) < GetPVarInt(playerid, "PayForChangeSkin")) return Error(playerid, "Niewystarczająca ilość gotówki.");
		TakeMoney(playerid, GetPVarInt(playerid, "PayForChangeSkin"));
		gracz[playerid][Skin] = modelid;
		SetPlayerSkin(playerid, modelid);
		mq_format("UPDATE `Konta` SET `Skin`='%d' WHERE `id`='%d';", gracz[playerid][Skin], gracz[playerid][UID]);
		mq_send("QUpdateSkin");
	}
	else if(extraid == MSEL_ADMINSKIN)
	{
		SetPlayerSkin(playerid, modelid);
	}
	else ev_OnPlayerModelSelectionEx(playerid, response, extraid, modelid);
	return 1;
}

public OnPlayerModelSelection(playerid, response, listid, modelid)
{
	ev_OnPlayerModelSelection(playerid, response, listid, modelid);
	return 1;
}
//********************************************************************************************************************ANTYCHEAT
forward OnCheatDetected(playerid, ip_address[], type, code);
public OnCheatDetected(playerid, ip_address[], type, code)
{
	if(IsPlayerNPC(playerid)) return 1;
	//new bool:var_true = true;
	//if(var_true) return 1;
	if(gracz[playerid][loginhistory_start]+3 > serwer[time_timestamp]) return 1;
	if(!gracz[playerid][loggedin])//w chwili kiedy jest sprawdzanie i logowanie
	{
		if(GetPlayerSkin(playerid) == 162) return 1;
	}
	if(type) BlockIpAddress(ip_address, 0);
	else
	{
		new strCheatName[32];
		format(strCheatName, 32, "Cheat(%d)", code);
		new identified = true;
		switch(code)
		{
			case 0..1: format(strCheatName, 32, "AirBreak(%d)", code);
			case 2..3: 
			{
				format(strCheatName, 32, "PosDesync(%d)", code);
				if(gracz[playerid][acwarn][code] < 3)
				{
					gracz[playerid][acwarn][code]++;
					identified = false;
				}
				else
				{
					identified = true;
				}
			}
			case 7..8: format(strCheatName, 32, "FlyHack(%d)", code);
			case 9..10: format(strCheatName, 32, "SpeedDesync(%d)", code);
			case 11..12:
			{
				format(strCheatName, 32, "HealHack(%d)", code);
				
				if(gracz[playerid][acwarn][code] < 3)
				{
					gracz[playerid][acwarn][code]++;
					identified = false;
				}
				else
				{
					identified = true;
				}
			}
			case 13: 
			{
				format(strCheatName, 32, "ArmourDesync");
				if(gracz[playerid][acwarn][code] < 3)
				{
					gracz[playerid][acwarn][code]++;
					identified = false;
				}
				else
				{
					identified = true;
				}
			}
			case 14:  format(strCheatName, 32, "MoneyHack");
			case 15:
			{
				format(strCheatName, 32, "WeaponDesync");
				if(IsPlayerOnDutyFraction(playerid))
				{
					if(gracz[playerid][frakcja] == F_MAFIA || gracz[playerid][frakcja] == F_POLICE)
					{
						ResetPlayerWeapons(playerid);
						LoadFractionWeapons(playerid, gracz[playerid][frakcja]);
						gracz[playerid][acwarn][code]++;
					}
					else gracz[playerid][acwarn][code] = 3;
				}
				else gracz[playerid][acwarn][code] = 3;

				if(gracz[playerid][acwarn][code] < 3)
				{
					identified = false;
				}
				else
				{
					identified = true;
				}
			}
			case 16..17:
			{
				format(strCheatName, 32, "AmmoDesync(%d)", code);
				if(gracz[playerid][acwarn][code] < 3)
				{
					gracz[playerid][acwarn][code]++;
					identified = false;
				}
				else
				{
					identified = true;
				}
			}
			//case 18:  format(strCheatName, 32, "FakeAction");
			case 19..20:  format(strCheatName, 32, "GodMode(%d)", code);
			case 21:  format(strCheatName, 32, "FakeSpec");
			case 23:  format(strCheatName, 32, "TuningHack");
			case 25:  format(strCheatName, 32, "TurnHack");
			case 26:  format(strCheatName, 32, "RapidFire");
			case 27:  format(strCheatName, 32, "FakeSpawn");
			case 28:  format(strCheatName, 32, "FakeKill");
			case 29:  format(strCheatName, 32, "AimHack");
			//case 31:  format(strCheatName, 32, "CarShoot");
			//case 32:  format(strCheatName, 32, "CarJack");
			case 34:  format(strCheatName, 32, "AFK-Ghost");
			case 35:  format(strCheatName, 32, "PadAim");
			case 38:  format(strCheatName, 32, "Ping %d/300", GetPlayerPing(playerid));
			//case 39:  format(strCheatName, 32, "FakeDialog");
			case 41:  format(strCheatName, 32, "Zły klient");
			//case 43..47:  format(strCheatName, 32, "Crasher(%d)", code);
			//case 48..50:  format(strCheatName, 32, "Flood(%d)", code);
			//case 52:  format(strCheatName, 32, "NOP Cheat");
			default: identified = false;
		}
		if((code == 9 || code == 10) && gracz[playerid][wypadek] > 0 || gracz[playerid][bw] > 0) identified = false;
		if(code == 13 && (gracz[playerid][frakcja] == F_POLICE || gracz[playerid][frakcja] == F_BORDERGUARD)) identified = false;
		//SendClientMessageEx(playerid, PlayerColors[random(sizeof(PlayerColors))], "[%d]wykryto cheat: %s", identified, strCheatName);
		if(identified)
		{
			//Ban_Time(-1, playerid, strCheatName, 90);
			Interwencja(-1, playerid, 0, PENALTY_KICK, strCheatName);
			KickEx(playerid, strCheatName);
		}
	}
	return 1;
}
//************************SYSTEMY****************************************************************************************************************************************
//***************************************************************************************TIMER GRACZA
forward OneSecondUpdate(i);
public OneSecondUpdate(i)
{
	if(!IsPlayerConnected(i)) return 1;
	if(IsPlayerNPC(i)) return 1;
	if(!gracz[i][spawned]) return 1;
	if(!gracz[i][loggedin]) return 1;
	//new test_tick = GetTickCount();
	Process_Przykuty(i);
	Process_LeftNotify(i);
	Process_Radio(i);
	Process_WeatherTime(i);
	Process_CourierJob(i, 0);
	Process_GPS(i);
	AddPlayerRunQueue("Process_PlayerGateDetect", i);//długi czas wykonywania - amx niech to wykona osobno
	AddPlayerRunQueue("Process_UpTrailerIdleTime", i);
	Process_PlayerFractionDuty(i);
	Process_SaveRelogData(i);
	Process_Prison(i);
	Process_FractionTool(i);
	Process_Caller(i);
	Process_UpdateArmourHPSleep(i);
	Process_BrutallyWounded(i);
	Process_ExtinguishingFire(i);
	Process_Wypadek(i);
	Process_AutoSprayTake(i);
	Process_Spray(i);
	Process_UpdateFractionTD(i);
	Process_Taxometr(i);
	Process_PraktykaPrawko(i);
	Process_Spectator(i);
	Process_NickLabel(i);
	Process_StatusPlayer(i);
	Process_AFK(i);
	Process_PlayedTime(i);
	Process_CombineMode(i);
	Process_Gym(i);
	Process_PlayerTeam(i);
	Process_Pursuit(i);
	Process_PlayerCompanyDuty(i);
	Process_VoiceStreamAttacher(i);
	Process_SimpleText(i);
	Process_TDShoot(i);
	Process_PlayerMarker(i);
	Process_DrunkLevel(i);
	Process_PlayerADR(i);
	Process_DJKA(i);
	AddPlayerRunQueue("Process_EventPanelPID", i);//proxy
	AddPlayerRunQueue("Process_Campfire", i);
	Process_PoolWatchDog(i);
	if(gracz[i][unused03DL]) Error(i, "Pobierz klienta SA:MP w wersji 0.3DL! - "COL_LIME"https://highwaylife.pl/pobierz");
	Process_VehicleDamage(i, gracz[i][opu_vehicleid], 0);
	UpdatePlayerColor(i);
	gracz[i][LastOnline] = serwer[time_timestamp];
	if(serwer[time_second] == 1 || serwer[time_second] == 11 || serwer[time_second] == 21 || serwer[time_second] == 31 || serwer[time_second] == 41 || serwer[time_second] == 51)//minutowy zapis statystyk
	{	
		mq_format("UPDATE `Konta` SET `LastOnline`='%d', `przebieg`='%d', `frakcja_totalduty`='%d' WHERE `id`='%d';", gracz[i][LastOnline], gracz[i][przebieg], gracz[i][frakcja_totalduty], gracz[i][UID]);
		mq_send("QOneMinPlayerQuery");
	}
	if(GetPlayerWantedLevel(i) != gracz[i][scigany_lvl]) SetPlayerWantedLevel(i, gracz[i][scigany_lvl]);
	if(IsPlayerUseGym(i))
	{
		if(gracz[i][karnet] > 0)
		{
			gracz[i][karnet]--;
			mq_format("UPDATE `Konta` SET `karnet`='%d' WHERE `id`='%d';", gracz[i][karnet], gracz[i][UID]);
			mq_send("QUpdateKarnet");
		}
	}
	HUD_UpdateSKIN(i);
	//printf("[PlayerProcess] END (%dms)", GetTickCount()-test_tick);
	return 1;
}
//***************************************************************************************KONTROLA POGODY/GODZINY
task Process_WeatherTime(playerid)
{
	if(gracz[playerid][status_lunapark] != 0)
	{
		SetPlayerWeather(playerid, 10);
		SetPlayerTime(playerid, 12, 00);
		return 1;
	}
	//czas
	if(!IsPlayerInDynamicArea(playerid, weatherarea_PencilFactory))
	{
		if(gracz[playerid][event_saved] == true && serwer[event_hour] != -1)
		{
			SetPlayerTime(playerid, serwer[event_hour], 00);
		}
		else
		{
			#if defined JESTZIMA
			switch(serwer[time_hour])
			{
				case 0..4: SetPlayerTime(playerid, 3, serwer[time_minute]);
				case 14: SetPlayerTime(playerid, 20, serwer[time_minute]);
				case 15: SetPlayerTime(playerid, 21, serwer[time_minute]);
				case 16: SetPlayerTime(playerid, 22, serwer[time_minute]);
				case 17: SetPlayerTime(playerid, 23, serwer[time_minute]);
				case 18..20: SetPlayerTime(playerid, 0, serwer[time_minute]);
				case 21..22: SetPlayerTime(playerid, 1, serwer[time_minute]);
				case 23: SetPlayerTime(playerid, 3, serwer[time_minute]);
				default: SetPlayerTime(playerid, serwer[time_hour], serwer[time_minute]);
			}
			#else
			SetPlayerTime(playerid, serwer[time_hour], serwer[time_minute]);
			#endif
		}
	}
	//pogoda
	if(IsPlayerInDynamicArea(playerid, weatherarea_OilProvince))
	{
		SetPlayerWeather(playerid, 9);
	}
	else if(IsPlayerInDynamicArea(playerid, weatherarea_PencilFactory))
	{
		SetPlayerWeather(playerid, 91);
		SetPlayerTime(playerid, 13, 00);
	}
	else 
	{
		if(gracz[playerid][event_saved] == true && serwer[event_weather_id] != -1)
		{
			SetPlayerWeather(playerid, serwer[event_weather_id]);
		}
		else
		{
			if(isvip(playerid) && gracz[playerid][stormoff])// komenda /stormoff
			{
				if(serwer[pogoda] == 8)//burza
				{
					SetPlayerWeather(playerid, 14);
				}
				else
				{
					SetPlayerWeather(playerid, serwer[pogoda]);
				}
			}
			else
			{
				SetPlayerWeather(playerid, serwer[pogoda]);
			}
		}
	}
	return 1;
}
//***************************************************************************************ZAZNACZANIE NACZEPY
stock SelectTrailer(playerid, trailerid)
{
	if(trailer_select[playerid][ts_status]) return 0;
	trailer_select[playerid][ts_status] = true;
	new Float:kX, Float:kY, Float:kZ, Float:kA;
	GetVehiclePos(trailerid, kX, kY, kZ);
	GetVehicleZAngle(trailerid, kA);
	switch(pojazd[trailerid][v_model])
	{	
		case 435: kZ -= 3.1;//naczepa duża
		case 450: kZ -= 3.3;//żwirówka
		case 584: kZ -= 3.7;//cysterna
		case 591: kZ -= 3.1;//naczepa mała
	}
	new Float:frontX, Float:frontY;
	new Float:backX, Float:backY;

	new Float:leftX, Float:leftY;
	new Float:rightX, Float:rightY;
	//zmienne while:
	new Float:_front_back = 0;
	//new Float:_left_right = 0;
	new core_counter;
	//
	GetXYInBackOfPos(kX, kY, kA, backX, backY, 5.0);
	new Float:draw_startX, Float:draw_startY;
	draw_startX = backX;
	draw_startY = backY;

	const Float:var_width = 1.5; 
	const Float:var_length = 15.0;
	new oid;
	trailer_select[playerid][ts_iconid] = CreateDynamicMapIcon(kX, kY, kZ, 0, 0xFF0000FF, .playerid = playerid, .streamdistance = 9999.0, .style = MAPICON_GLOBAL);
	while(_front_back < var_length)
	{

		GetXYInFrontOfPos(draw_startX, draw_startY, kA, frontX, frontY, 0.0+_front_back);
		GetXYInLeftOfPos(frontX, frontY, kA, leftX, leftY, var_width);
		GetXYInRightOfPos(frontX, frontY, kA, rightX, rightY, var_width);
		trailer_select[playerid][ts_objects][oid] = CreateDynamicObject(18728,  leftX, leftY, kZ, 0.0, 0.0, 0.0, .playerid = playerid);
		oid++;
		trailer_select[playerid][ts_objects][oid] = CreateDynamicObject(18728,  rightX, rightY, kZ, 0.0, 0.0, 0.0, .playerid = playerid);
		oid++;
		/*if(core_counter == 0 || !(_front_back+0.5 < var_length))
		{
			_left_right = 0.0;
			while(_left_right < var_width)
			{
				if(var_width > var_width-_left_right)
				{
					GetXYInLeftOfPos(frontX, frontY, kA, leftX, leftY, var_width-_left_right);
					GetXYInRightOfPos(frontX, frontY, kA, rightX, rightY, var_width-_left_right);
				}
				else 
				{
					GetXYInLeftOfPos(frontX, frontY, kA, leftX, leftY, 0.1);
					GetXYInRightOfPos(frontX, frontY, kA, rightX, rightY, 0.1);
				}
				CreateDynamicObject(18728,  leftX, leftY, kZ, 0.0, 0.0, 0.0);
				CreateDynamicObject(18728,  rightX, rightY, kZ, 0.0, 0.0, 0.0);
				_left_right += 0.6;
			}
		}*/
		_front_back += 3.0;
		core_counter++;
	}
	return 1;
}

stock ClearTrailerSelect(playerid)
{
	if(!trailer_select[playerid][ts_status]) return 0;
	trailer_select[playerid][ts_status] = false;
	DestroyDynamicMapIcon(trailer_select[playerid][ts_iconid]);
	for(new o; o < 10; o++)
	{
		DestroyDynamicObject(trailer_select[playerid][ts_objects][o]);
	}
	return 1;
}

//***************************************************************************************WYZNACZANIE CELU IKONA + OBIEKT +  NAPIS
	stock SetObjective(playerid, description[], Float:dX, Float:dY, Float:dZ, gps = false)
	{
		if(gracz[playerid][objective_status]) 
		{
			ClearObjective(playerid);
		}
		gracz[playerid][objective_status] = 1;

		gracz[playerid][objective_X] = dX;
		gracz[playerid][objective_Y] = dY;
		gracz[playerid][objective_Z] = dZ;

		gracz[playerid][objective_iconid] = CreateDynamicMapIcon(dX, dY, dZ, 19, 0xFF0000FF, .playerid = playerid, .streamdistance = 9999.0, .style = MAPICON_GLOBAL);
		gracz[playerid][objective_objectid][0] = CreateDynamicObject(19945,  dX, dY, dZ-3.7, 0.0, 0.0, 0.0, .playerid = playerid, .streamdistance = 500.0, .drawdistance = 500.0, .priority = 1);
		gracz[playerid][objective_objectid][1] = CreateDynamicObject(19945,  dX, dY, dZ-3.7, 0.0, 0.0, 0.0, .playerid = playerid, .streamdistance = 500.0, .drawdistance = 500.0, .priority = 1);

		new Float:h_sector = 63.6084;
		gracz[playerid][objective_objectid][2] = CreateDynamicObject(19945,  dX, dY, dZ-3.7+h_sector, 0.0, 0.0, 0.0, .playerid = playerid, .streamdistance = 500.0, .drawdistance = 500.0, .priority = 1);
		gracz[playerid][objective_objectid][3] = CreateDynamicObject(19945,  dX, dY, dZ-3.7+h_sector, 0.0, 0.0, 0.0, .playerid = playerid, .streamdistance = 500.0, .drawdistance = 500.0, .priority = 1);

		gracz[playerid][objective_objectid][4] = CreateDynamicObject(19945,  dX, dY, dZ-3.7+h_sector*2, 0.0, 0.0, 0.0, .playerid = playerid, .streamdistance = 500.0, .drawdistance = 500.0, .priority = 1);
		gracz[playerid][objective_objectid][5] = CreateDynamicObject(19945,  dX, dY, dZ-3.7+h_sector*2, 0.0, 0.0, 0.0, .playerid = playerid, .streamdistance = 500.0, .drawdistance = 500.0, .priority = 1);

		new strDesc[512];
		format(strDesc, 512, "« "COL_LIME"MIEJSCE DOCELOWE"COL_RED" »\n"COL_WHITE"%s", description);
		gracz[playerid][objective_text3d] = CreateDynamic3DTextLabel(strDesc, 0xFF0000FF, dX, dY, dZ, 200.0, .playerid = playerid);
		if(gps) StartRouteGPS(playerid, dX, dY, dZ);
		return 1;
	}
	stock ClearObjective(playerid)
	{
		if(!gracz[playerid][objective_status]) return 0;
		gracz[playerid][objective_status] = 0;
		DestroyDynamicMapIcon(gracz[playerid][objective_iconid]);
		DestroyDynamic3DTextLabel(gracz[playerid][objective_text3d]);
		StopRouteGPS(playerid);
		for(new d; d < 6; d++)
		{
			DestroyDynamicObject(gracz[playerid][objective_objectid][d]);
		}
		return 1;
	}

//***************************************************************************************RELOG SYSTEM
task Process_SaveRelogData(playerid)
{
	if(gracz[playerid][relog_data_loaded] == false) return 1;
	new vehicleid = gracz[playerid][opu_vehicleid];
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_DRVLICENSE) return 1;//kiedy jest w l-ce, nie zapisujemy danych do relogu
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) return 1;//podczas speca nie zapisuje danych
	if(gracz[playerid][bus_travel]) return 1;//podczas podróży busem blokuje zapis
	if(GetPlayerInterior(playerid) != 0 || GetPlayerVirtualWorld(playerid) != 0) return 1;//nie zapisuje w interiorach i innych vw
	if(IsPlayerUseGym(playerid)) return 1;
	new Float:posRlg[4];
	new rlg_vehicleuid = pojazd[vehicleid][v_id];
	new rlg_traileruid = pojazd[gracz[playerid][connected_trailervid]][v_id];
	new rlg_confcargo = gracz[playerid][cargo_confirmtrailer];
	new rlg_skin = GetPlayerSkin(playerid);
	if(gracz[playerid][event_saved] == true && gracz[playerid][event_last_skin_id] != 0) rlg_skin = gracz[playerid][event_last_skin_id];
	new rlg_duty = gracz[playerid][time_duty];
	new rlg_duty_total = gracz[playerid][time_duty_total];
	new rlg_session_id = gracz[playerid][firma_sessionid];
	new rlg_routelogstime = gracz[playerid][routelog_start_time];
	new rlg_scoremultiplier = gracz[playerid][scoreduty_multiplier];
	
	new rlg_onduty;
	if(rlg_session_id != 0)  rlg_onduty = gracz[playerid][firma_onduty];
	else rlg_onduty = gracz[playerid][frakcja_onduty];


	if(GetPlayerVehicleSeat(playerid) == 0)
	{
		GetVehiclePos(gracz[playerid][opu_vehicleid], posRlg[0], posRlg[1], posRlg[2]);
		GetVehicleZAngle(gracz[playerid][opu_vehicleid], posRlg[3]);
	}
	else
	{
		GetPlayerPos(playerid, posRlg[0], posRlg[1], posRlg[2]);
		GetPlayerFacingAngle(playerid, posRlg[3]);
		rlg_vehicleuid = 0;
		rlg_traileruid = 0;
	}	

	mq_format("UPDATE `Konta` SET `rlg_timestamp`='%d', `rlg_vehicleuid`='%d', `rlg_traileruid`='%d', `rlg_X`='%f', `rlg_Y`='%f', `rlg_Z`='%f', `rlg_R`='%f', `rlg_cargotrailerid`='%d', `rlg_confcargo`='%d', `rlg_skin`='%d', `rlg_duty`='%d', `rlg_duty_total`='%d', `rlg_onduty`='%d', `rlg_session_id`='%d', `rlg_routelogstime`='%d', `rlg_scoremultiplier`='%d' WHERE `id`='%d';", serwer[time_timestamp], rlg_vehicleuid, rlg_traileruid, posRlg[0], posRlg[1], posRlg[2], posRlg[3], gracz[playerid][cargo_trailerdid], rlg_confcargo, rlg_skin, rlg_duty, rlg_duty_total, rlg_onduty, rlg_session_id, rlg_routelogstime, rlg_scoremultiplier, gracz[playerid][UID]);
	mq_send("QRelogData");
	return 1;
}

task LoadRelogState(playerid)
{
	gracz[playerid][relog_data_loaded] = false;
	mq_format("SELECT * FROM `Konta` WHERE `id`='%d' LIMIT 0,1;", gracz[playerid][UID]);
	mq_send("OnRelogDataCheck", "d", playerid);
	GameTextForPlayer(playerid, "Wczytywanie stanu...", 100, 3);
	return 1;
}

forward OnRelogDataCheck(playerid);
public OnRelogDataCheck(playerid)
{
	new rlg_vehicleuid, rlg_traileruid, Float:rlg_X, Float:rlg_Y, Float:rlg_Z;
	cache_get_value_name_int(0, "rlg_vehicleuid", 	rlg_vehicleuid);
	cache_get_value_name_int(0, "rlg_traileruid", 	rlg_traileruid);
	cache_get_value_name_float(0, "rlg_X", 	rlg_X);
	cache_get_value_name_float(0, "rlg_Y", 	rlg_Y);
	cache_get_value_name_float(0, "rlg_Z", 	rlg_Z);
	if(gracz[playerid][rlg_timestamp]+60*MAX_RELOGTIME > serwer[time_timestamp])
	{
		TogglePlayerControllable(playerid, false);
		Streamer_ToggleItemUpdate(playerid, STREAMER_TYPE_OBJECT, false);
		Streamer_UpdateEx(playerid, rlg_X, rlg_Y, rlg_Z, -1, -1, STREAMER_TYPE_OBJECT);
		SetTimerEx("RelogStreamerLoaded", 2000, false, "dfff", playerid, rlg_X, rlg_Y, rlg_Z);
		GameTextForPlayer(playerid, "Wczytywanie stanu...", 2500, 3);
	}
	else//nie miał reloga
	{
		if(GetPVarInt(playerid, "ShowRegisterSkinSelect"))
		{
			SetPVarInt(playerid, "ShowRegisterSkinSelect", 0);
			SetPVarInt(playerid, "PayForChangeSkin", 0);
			ShowSelectSkinWindow(playerid);
		}
		else if(strlen(gracz[playerid][nick_ic]) < 2)
		{
			Dialog_Show(playerid, ADDICNICKNAME, DIALOG_STYLE_INPUT, ""COL_RED"»"COL_WHITE" Uzupełnij dane - Nazwa postaci", "Wprowadziliśmy opcjonalnie nick postaci IC. Uzupełni dane.\nImie i nazwisko postaci: "COL_RED"(format: Imie_Nazwisko (5-20 znaków))"COL_WHITE":", "Zatwierdz", "");
		}
		else if(gracz[playerid][bw] == 0 && gracz[playerid][wypadek] == 0)
		{
			new strSpawnList[512];
			format(strSpawnList, 512, ""COL_DRVONLINE"•»\t"COL_WHITE"Hotel "COL_DRVONLINE"Highway Life\t"COL_DRVONLINE"«•");
			format(strSpawnList, 512, "%s\n"COL_DRVONLINE"•»\t"COL_WHITE"Dom "COL_GREY"["COL_BLUE"%d"COL_GREY" pozycji"COL_GREY"]\t"COL_DRVONLINE"«•", strSpawnList, ShowHomeTeleport(playerid, true));
			format(strSpawnList, 512, "%s\n"COL_DRVONLINE"•»\t"COL_WHITE"Frakcja "COL_GREY"[%s"COL_GREY"]\t"COL_DRVONLINE"«•", strSpawnList, (gracz[playerid][frakcja] ? (GetFractionName(gracz[playerid][frakcja], 1)) : (""COL_RED"NIEDOSTĘPNE")));
			format(strSpawnList, 512, "%s\n"COL_DRVONLINE"•»\t"COL_WHITE"Firma "COL_GREY"["COL_BLUE"%s"COL_GREY"]\t"COL_DRVONLINE"«•", strSpawnList, (gracz[playerid][firma] ? (GetCompanyName(gracz[playerid][firma])) : (""COL_RED"NIEDOSTĘPNE")));
			Dialog_Show(playerid, SPAWNSELECT, DIALOG_STYLE_TABLIST, ""COL_RED"•» "COL_WHITE"Wybór spawnu "COL_RED"«•", strSpawnList, "Wybierz", "Anuluj");
		}
		gracz[playerid][relog_data_loaded] = true;
	}
	UpdatePlayerColor(playerid);
	return 1;
}

task RelogStreamerLoaded(playerid, Float: rlg_X, Float:rlg_Y, Float:rlg_Z)
{
	SetPlayerPos(playerid, rlg_X, rlg_Y, rlg_Z);
	TogglePlayerControllable(playerid, true);
	Streamer_ToggleItemUpdate(playerid, STREAMER_TYPE_OBJECT, true);
	mq_format("SELECT * FROM `Konta` WHERE `id`='%d' LIMIT 0,1;", gracz[playerid][UID]);
	mq_send("OnRelogDataCheck_2", "d", playerid);
	return 1;
}

task OnRelogDataCheck_2(playerid)
{
	new rlg_vehicleuid, rlg_traileruid, Float:rlg_X, Float:rlg_Y, Float:rlg_Z, Float:rlg_R;
	cache_get_value_name_int(0, "rlg_vehicleuid", 	rlg_vehicleuid);
	cache_get_value_name_int(0, "rlg_traileruid", 	rlg_traileruid);
	cache_get_value_name_float(0, "rlg_X", 	rlg_X);
	cache_get_value_name_float(0, "rlg_Y", 	rlg_Y);
	cache_get_value_name_float(0, "rlg_Z", 	rlg_Z);
	cache_get_value_name_float(0, "rlg_R", 	rlg_R);
	if(gracz[playerid][rlg_timestamp]+60*MAX_RELOGTIME > serwer[time_timestamp])
	{
		new rlg_skin, rlg_onduty, rlg_session_id;
		cache_get_value_name_int(0, "rlg_skin",   rlg_skin);
		cache_get_value_name_int(0, "rlg_onduty",   rlg_onduty);
		cache_get_value_name_int(0, "rlg_session_id",   rlg_session_id);
		cache_get_value_name_int(0, "rlg_routelogstime", 	gracz[playerid][routelog_start_time]);
		if(rlg_session_id == 0)
		{
			if(gracz[playerid][frakcja] != 0)//gracz ma frakcje (nie wyjebano go podczas timeouta)
			{
				if(rlg_skin != gracz[playerid][Skin])//jeśli gracz ma służbowy skin na rlg zamiast cywilnego
				{
					gracz[playerid][frakcja_onduty] = gracz[playerid][frakcja];
					SetPlayerSkin(playerid, rlg_skin);
					cache_get_value_name_int(0, "rlg_duty", gracz[playerid][time_duty]);
					cache_get_value_name_int(0, "rlg_duty_total", gracz[playerid][time_duty_total]);
					cache_get_value_name_int(0, "rlg_scoremultiplier",  gracz[playerid][scoreduty_multiplier]);
					LoadFractionWeapons(playerid, gracz[playerid][frakcja]);
					
				}
				else if(rlg_onduty == gracz[playerid][frakcja])//gracz może jest po cywilu na duty
				{
					gracz[playerid][frakcja_onduty] = gracz[playerid][frakcja];
					cache_get_value_name_int(0, "rlg_duty", gracz[playerid][time_duty] );
					cache_get_value_name_int(0, "rlg_duty_total", gracz[playerid][time_duty_total]);
					cache_get_value_name_int(0, "rlg_scoremultiplier", gracz[playerid][scoreduty_multiplier]);
					LoadFractionWeapons(playerid, gracz[playerid][frakcja]);
				}
			}
		}
		else
		{
			if(gracz[playerid][firma] == rlg_onduty)
			{
				gracz[playerid][firma_onduty] = rlg_onduty;
				gracz[playerid][firma_sessionid] = rlg_session_id;
				cache_get_value_name_int(0, "rlg_duty", gracz[playerid][time_duty]);
				cache_get_value_name_int(0, "rlg_duty_total", gracz[playerid][time_duty_total] );
			}
		}
		cache_get_value_name_int(0, "rlg_cargotrailerid", 		gracz[playerid][cargo_trailerdid]);
		cache_get_value_name_int(0, "rlg_confcargo", 		gracz[playerid][cargo_confirmtrailer]);
		if(gracz[playerid][cargo_trailerdid] != 0) 
		{
			SelectTrailer(playerid, gracz[playerid][cargo_trailerdid]);
		}
		//SetPlayerPos(playerid, rlg_X, rlg_Y, rlg_Z);
		//Force_FreezeLoadObject(playerid, rlg_X, rlg_Y, rlg_Z);
		SetPlayerFacingAngle(playerid, rlg_R);
		new engine, lights, alarm, doors, bonnet, boot, objective;
		new bool:vehicleonmap = false;
		if(rlg_vehicleuid != 0)
		{
			for(new v = GetVehiclePoolSize(); v != -1; v--)
			{
				if(pojazd[v][v_id] == rlg_vehicleuid)//znaleziono uid pojazdu w którym gracz sie znajdował znajduje
				{
					new IVIUBD = IsVehicleInUseByDriver(v);
					if(IVIUBD == INVALID_PLAYER_ID || IVIUBD == playerid)//pojazdu nie prowadzi nikt inny
					{
						PutPlayerInVehicle(playerid, v, 0);
						Handbrake(v, false);
						GetVehicleParamsEx(v, engine, lights, alarm, doors, bonnet, boot, objective);
						SetVehicleParamsEx(v, 1, 1, alarm, doors, bonnet, boot, objective);
						SetVehiclePos(v, rlg_X, rlg_Y, rlg_Z);
						SetVehicleZAngle(v, rlg_R);
						SetTimerEx("OnPlayerStateChange", 5000, false, "ddd", playerid, PLAYER_STATE_DRIVER, PLAYER_STATE_ONFOOT);//wymuszenie zdarzenia
						if(IsVehicleTruck(pojazd[v][v_model]) == 1)
						{
							if(rlg_traileruid != 0)
							{
								for(new t = GetVehiclePoolSize(); t != -1; t--)
								{	
									if(pojazd[t][v_id] == rlg_traileruid)
									{
										AttachTrailerToVehicle(t, v);
										//printf("AttachTrailerToVehicle(%d, %d);", t, v);
										SetTimerEx("RelogTrailerAttachDelay", 5000, false, "ddd", playerid, t, v);
										break;
									}
								}
							}
						} 
						else if(pojazd[v][v_cargo] != 0)
						{
							if(IsVehicleTruck(pojazd[v][v_model]) == 2)
							{
								if(pojazd[v][v_owner_type] == VEHICLE_PLAYER)
								{
									SetObjective(playerid, ""COL_RED"• "COL_BLUE"Aby dostarczyć zlecenie, wpisz: "COL_GREEN"/zlecenie dostarcz "COL_GREY"[/zlecenie d] "COL_RED"•", pojazd[v][v_cargo_target_X], pojazd[v][v_cargo_target_Y], pojazd[v][v_cargo_target_Z], true);
								}
							}
						}
					}
					else
					{
						if(pojazd[v][v_owner_type] != VEHICLE_PLAYER) LeftNotifyShow(playerid, "Relog", "Przykro nam, zanim sie rozlaczyles, prowadziles pojazd publiczny. Niestety pojazdy publiczne podczas Twojej nieobecnosci nie moga byc rezerwowane. Ktos inny go zajal, dlatego nie mozemy Ci wrocic pojazdu. Zeby Cie nie zostawic bez niczego, wrocilismy Twoja postac na glowny spawn.", LN_BLUE, 25);
						gracz[playerid][loading_objects] = false;
						SetPlayerPos(playerid, GetPVarFloat(playerid, "spawn_X"), GetPVarFloat(playerid, "spawn_Y"), GetPVarFloat(playerid, "spawn_Z"));
					}
					vehicleonmap = true;
					break;
				}
			}
			if(!vehicleonmap) 
			{
				LeftNotifyShow(playerid, "Relog", "Przykro nam, nie moglismy Cie wrocic do pojazdu, ktory prowadziles przed rozlaczeniem sie, poniewaz pojazd nie istnieje na mapie. Prawdopodobnie byl zaparkowany w niedozwolonym miejscu. Zostajesz wrocony na glowny spawn.", LN_BLUE, 25);
				gracz[playerid][loading_objects] = false;
				SetPlayerPos(playerid, GetPVarFloat(playerid, "spawn_X"), GetPVarFloat(playerid, "spawn_Y"), GetPVarFloat(playerid, "spawn_Z"));
			}
		}
		/*if(GetPVarInt(playerid, "relog_tryreload") < 3)
		{
			new strRelogDialog[1024];
			format(strRelogDialog, 1024, ""COL_WHITE"Straciłeś połączenie z serwerem niecałe 5 minut temu.");
			format(strRelogDialog, 1024, "%s\n"COL_WHITE"System RELOG wczytał Twój stan rozgrywki jeszcze zanim straciłeś połączenie z serwerem.", strRelogDialog);
			format(strRelogDialog, 1024, "%s\n"COL_WHITE"Czy wszystko się wczytało? Nie jesteś pod obiektami?", strRelogDialog);
			format(strRelogDialog, 1024, "%s\n\n"COL_WHITE"A) Jest okej? Wpisz w polu poniżej "COL_RED"ok"COL_WHITE" lub "COL_RED"A"COL_WHITE" i kontunuj rozgrywkę.", strRelogDialog);
			format(strRelogDialog, 1024, "%s\n"COL_WHITE"B) Coś jest nie tak? Nie wpisuj nic i wciśnij zatwierdź - Wczytamy ponownie stan rozgrywki.", strRelogDialog);
			format(strRelogDialog, 1024, "%s\n\n"COL_WHITE"Pozostałe próby wczytania: "COL_ORANGE"%d/3", strRelogDialog, GetPVarInt(playerid, "relog_tryreload"));
			format(strRelogDialog, 1024, "%s\n\n"COL_BLUE"Wpisz poniżej: "COL_RED"ok"COL_WHITE" lub "COL_RED"A"COL_WHITE" - aby zamknąć okno. Zostaw pole puste i zatwierdź aby ponowić wczytywanie.", strRelogDialog);
			Dialog_Show(playerid, RELOGOK, DIALOG_STYLE_INPUT, "Potwierdzenie", strRelogDialog, "Potwierdz", "");
		}*/
		gracz[playerid][relog_data_loaded] = true;
	}
	return 1;
}

Dialog:ADDICNICKNAME(playerid, response, listitem, inputtext[])
{
	new bool:dataok = false;
	switch(strlen(inputtext))
	{
		case 5..20:
		{
			if(NameValidator(playerid, inputtext) == 1)
			{
				SendClientMessageEx(playerid, -1, "(("COL_GREY"Nazwa Twojej postaci: "COL_GREEN"%s"COL_WHITE".))", GetICName(playerid));
				dataok = true;
			}
			else dataok = false;
		}
		default:
		{
			dataok = false;
		}
	}
	if(dataok == false) Dialog_Show(playerid, ADDICNICKNAME, DIALOG_STYLE_INPUT, ""COL_RED"»"COL_WHITE" Uzupełnij dane - Nazwa postaci", "Wprowadziliśmy opcjonalnie nick postaci IC. Uzupełni dane.\nImie i nazwisko postaci: "COL_RED"(format: Imie_Nazwisko (5-20 znaków))"COL_WHITE":", "Zatwierdz", "");
	else
	{
		mq_format("UPDATE `Konta` SET `nick_ic`='%s' WHERE `id`='%d';", gracz[playerid][nick_ic], gracz[playerid][UID]);
		mq_send("QUpdateNickIC");
	}
	return 1;
}

Dialog:RELOGOK(playerid, response, listitem, inputtext[])
{
	if(compare(inputtext, "ok") || compare(inputtext, "a"))
	{
		gracz[playerid][relog_data_loaded] = true;
	}
	else
	{
		SetPVarInt(playerid, "relog_tryreload", GetPVarInt(playerid, "relog_tryreload")+1);
		LoadRelogState(playerid);
	}
	return 1;
}

Dialog:SPAWNSELECT(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0://Hotel HL
		{
			GameTextForPlayer(playerid, "~g~Hotel Highway Life", 1500, 3);
		}
		case 1://Dom
		{
			if(ShowHomeTeleport(playerid) == 0) return GameTextForPlayer(playerid, "~r~NIEDOSTEPNE", 1500, 3);
		}
		case 2://Frakcja
		{
			if(gracz[playerid][frakcja] == 0) return GameTextForPlayer(playerid, "~r~NIEDOSTEPNE", 1500, 3);
			new fid = gracz[playerid][frakcja];
			FreezeLoadObject(playerid, fractions[fid][fr_dutyX], fractions[fid][fr_dutyY], fractions[fid][fr_dutyZ]);
		}
		case 3://Firma
		{
			if(gracz[playerid][firma] == 0) return GameTextForPlayer(playerid, "~r~NIEDOSTEPNE", 1500, 3);
			new cid = gracz[playerid][firma];
			FreezeLoadObject(playerid, company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ]);
		}
	}

	return 1;
}

forward RelogTrailerAttachDelay(playerid, v1, v2);
public RelogTrailerAttachDelay(playerid, v1, v2)
{
	//printf("GetVehicleTrailer(%d) != %d", GetVehicleTrailer(v2), v1);
	if(IsPlayerInVehicle(playerid, v2))
	{
		if(GetVehicleTrailer(v2) != v1)
		{
			AttachTrailerToVehicle(v1, v2);
			SetTimerEx("RelogTrailerAttachDelay", 1000, false, "ddd", playerid, v1, v2);
		}
	}
	return 1;
}
//**********************************************************************************************************************************EDYCJA AKCESORII
public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	//printf("%f, %f, %f, %f, %f, %f", Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ);
	new i = index;
	if(response)
	{
		LeftNotifyShow(playerid, "info", "Pozycja akcesorii ~g~zapisana~w~!");
		ao[playerid][index][ao_x] = fOffsetX;
		ao[playerid][index][ao_y] = fOffsetY;
		ao[playerid][index][ao_z] = fOffsetZ;
		ao[playerid][index][ao_rx] = fRotX;
		ao[playerid][index][ao_ry] = fRotY;
		ao[playerid][index][ao_rz] = fRotZ;
		ao[playerid][index][ao_sx] = fScaleX;
		ao[playerid][index][ao_sy] = fScaleY;
		ao[playerid][index][ao_sz] = fScaleZ;
		mq_format("UPDATE `akcesoria` SET `ao_x`='%f', `ao_y`='%f', `ao_z`='%f', `ao_rx`='%f', `ao_ry`='%f', `ao_rz`='%f', `ao_sx`='%f', `ao_sy`='%f', `ao_sz`='%f' WHERE `userid`='%d' AND `type`='%d';", ao[playerid][i][ao_x], ao[playerid][i][ao_y], ao[playerid][i][ao_z], ao[playerid][i][ao_rx], ao[playerid][i][ao_ry], ao[playerid][i][ao_rz], ao[playerid][i][ao_sx], ao[playerid][i][ao_sy], ao[playerid][i][ao_sz], gracz[playerid][UID], ao[playerid][i][ao_typ]);
		mq_send("QUpdateAkcesoria");
		SetPlayerAttachedObject(playerid, index, modelid, boneid, ao[playerid][i][ao_x], ao[playerid][i][ao_y], ao[playerid][i][ao_z], ao[playerid][i][ao_rx], ao[playerid][i][ao_ry], ao[playerid][i][ao_rz], ao[playerid][i][ao_sx], ao[playerid][i][ao_sy], ao[playerid][i][ao_sz]);
	}
	else
	{
		LeftNotifyShow(playerid, "info", "Ustawienie pozycji akcesorii ~r~anulowane~w~!");
		SetPlayerAttachedObject(playerid, index, modelid, boneid, ao[playerid][i][ao_x], ao[playerid][i][ao_y], ao[playerid][i][ao_z], ao[playerid][i][ao_rx], ao[playerid][i][ao_ry], ao[playerid][i][ao_rz], ao[playerid][i][ao_sx], ao[playerid][i][ao_sy], ao[playerid][i][ao_sz]);
	}
	return 1;
}
//**********************************************************************************************************************historia logowania
stock StartLoginHistory(playerid)
{
	gracz[playerid][loginhistory_start] = serwer[time_timestamp];
	gracz[playerid][loginhistory_end] = serwer[time_timestamp];
	format(gracz[playerid][loginhistory_ip], 64, "%s", playerip(playerid, true));
	format(gracz[playerid][loginhistory_serial], 64, "%s", serial(playerid, true));
	return 1;
}
stock EndLoginHistory(playerid)
{
	gracz[playerid][loginhistory_end] = serwer[time_timestamp];
	mq_format("INSERT INTO `HistoriaLogowania` (`uid`, `login`, `logout`, `ip`, `gpci`) VALUES ('%d', FROM_UNIXTIME('%d'), FROM_UNIXTIME('%d'), '%s', '%s');", gracz[playerid][UID], gracz[playerid][loginhistory_start], gracz[playerid][loginhistory_end], gracz[playerid][loginhistory_ip], gracz[playerid][loginhistory_serial]);
	mq_send("QLoginHistory");
	return 1;
}
//**********************************************************************************************************************ustawienie prawidłowego koloru nicku
stock UpdatePlayerColor(playerid)
{
	new color_set = COLOR_DRV;
	if(gracz[playerid][pursuit_invisible_timestamp] > serwer[time_timestamp])
	{
		new strTemp[128];
		format(strTemp, 128,"~b~ucieczka:~n~~g~jestes niewidzialny na mapie przez %d sekund.", gracz[playerid][pursuit_invisible_timestamp]-serwer[time_timestamp]);
		GameTextForPlayer(playerid, strTemp, 1000, 3);
		color_set = 0x92929200;
		return 1;
	}
	if(gracz[playerid][frakcja] == 0) color_set = COLOR_DRV;
	else if(gracz[playerid][frakcja] == F_POLICE) 
	{
		if(IsPlayerOnDutyFraction(playerid)) color_set = 0x0051FF00;
		else color_set = COLOR_POL;
	}
	else if(gracz[playerid][frakcja] == F_BORDERGUARD) 
	{
		if(IsPlayerOnDutyFraction(playerid)) color_set = 0x2E890000;
		else color_set = COLOR_BORG;
	}
	else if(gracz[playerid][frakcja] == F_EMERGENCY) color_set = COLOR_EMRG;
	else if(gracz[playerid][frakcja] == F_ROADASSIST) color_set = COLOR_ROADA;
	else if(gracz[playerid][frakcja] == F_TAXI) color_set = COLOR_TAXI;
	else if(gracz[playerid][frakcja] == F_MAFIA)
	{
		if(IsPlayerOnDutyFraction(playerid)) color_set = 0x944b0000;
		else color_set = COLOR_MAFIA;
	}
	new event_color = EventColor(playerid);
	if(event_color != 0) color_set = event_color;
	if(gracz[playerid][status_lunapark] == LPARK_ASG) color_set = 0xC0FF3E00;
	//aktualizacja jesli zaszla zmiana
	if(color_set != GetPlayerColor(playerid))
	{
		SetPlayerColor(playerid, color_set);
		gracz[playerid][last_playercolor] = color_set;
		HUD_UpdateNickAndID(playerid);
	}
	return 1;
}
//***************************************************************************************widoczność markerów
/*
// Make player 42 see player 1 as a red marker
SetPlayerMarkerForPlayer( 42, 1, 0xFF0000FF );
 
// Make the players marker an invisible white (chat will be white but marker will be gone).
SetPlayerMarkerForPlayer( 42, 1, 0xFFFFFF00 );
 
// Make the players marker invisible to the player while keeping chat colour the same. Will only work correctly if SetPlayerColor has been used:
SetPlayerMarkerForPlayer( 42, 1, ( GetPlayerColor( 1 ) & 0xFFFFFF00 ) );
 
// Make the players marker fully opaque (solid) to the player while keeping chat colour the same. Will only work correctly if SetPlayerColor has been used:
SetPlayerMarkerForPlayer( 42, 1, ( GetPlayerColor( 1 ) | 0x000000FF ) );
*/
task Process_PlayerMarker(playerid)//m - drugi gracz
{
	for(new m = PlayerPoolSize(); m != -1; m--)
	{
		if(gracz[m][loggedin])
		{
			if(IsPlayerInRangeOfPoint(m, 400.0, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]))
			{
				if(gracz[m][aaInvisible] == true)
				{
					SetPlayerMarkerForPlayer(playerid, m, (COLOR_DRV & 0xFFFFFF00));//szary niewidzialny
				}
				else if(gracz[m][event_saved] == false)
				{
					if(gracz[playerid][frakcja] == gracz[m][frakcja] && gracz[playerid][frakcja] && gracz[m][frakcja] && IsPlayerOnDutyFraction(m) && IsPlayerOnDutyFraction(playerid))//frakcje
					{
						SetPlayerMarkerForPlayer(playerid, m, (gracz[m][last_playercolor] | 0x000000FF));
					}
					else if(gracz[playerid][frakcja] == F_POLICE && gracz[m][frakcja] == F_BORDERGUARD && IsPlayerOnDutyFraction(m) && IsPlayerOnDutyFraction(playerid))//frakcje
					{
						SetPlayerMarkerForPlayer(playerid, m, (gracz[m][last_playercolor] | 0x000000FF));
					}
					else if(gracz[playerid][frakcja] == F_BORDERGUARD && gracz[m][frakcja] == F_POLICE && IsPlayerOnDutyFraction(m) && IsPlayerOnDutyFraction(playerid))//frakcje
					{
						SetPlayerMarkerForPlayer(playerid, m, (gracz[m][last_playercolor] | 0x000000FF));
					}
					else if((gracz[playerid][frakcja] == F_BORDERGUARD || gracz[playerid][frakcja] == F_POLICE) && IsPlayerOnDutyFraction(playerid))//na duty nie widzą graczy na minimapie
					{
						SetPlayerMarkerForPlayer(playerid, m, (gracz[m][last_playercolor] & 0xFFFFFF00));//niewidzialny
					}
					else//zmienianie na standardowe
					{
						SetPlayerMarkerForPlayer(playerid, m, gracz[m][last_playercolor]);
					}
				}
				else
				{
					SetPlayerMarkerForPlayer(playerid, m, gracz[m][last_playercolor]);
				}
			}
			else
			{
				new bool:showmarkerM = false;
				for(new c; c < MAX_CALLS; c++)
				{
					if(calls[c][call_type] == 1)//od gracza
					{
						if(calls[c][call_status] == 2)//przyjęte
						{
							if(calls[c][call_calleruid] == gracz[playerid][UID])//wezwanie pid
							{
								if(calls[c][call_acceptby_puid] == gracz[m][UID])//akceptowane przez m
								{
									showmarkerM = true;//pokaż ten marker
									break;
								}
							}
						}
					}
				}
				if(showmarkerM == false) SetPlayerMarkerForPlayer(playerid, m, (gracz[m][last_playercolor] & 0xFFFFFF00));//niewidzialny
				else SetPlayerMarkerForPlayer(playerid, m, (gracz[m][last_playercolor] | 0x000000FF));//widzialny
			}
		}
		else
		{
			SetPlayerMarkerForPlayer(playerid, m, 0x00000000);//czarny niewidzialny
		}
	}
	return 1;
}
//***************************************************************************************aktualizacja kamizelki, hp i zmeczenia
task Process_UpdateArmourHPSleep(playerid)
{
	new Float:tmpFloat;
	GetPlayerHealth(playerid, tmpFloat);
	if(tmpFloat > 100.0) SetPlayerHealth(playerid, 100.0);
	if(gracz[playerid][stamina_timestamp] < serwer[time_timestamp])
	{
		if(gracz[playerid][stamina] > 0)
		{
			gracz[playerid][stamina]--;
			mq_format("UPDATE `Konta` SET `stamina`='%d' WHERE `id`='%d';", gracz[playerid][stamina], gracz[playerid][UID]);
			mq_send("QUpdateStamina");
			HUD_UpdateSTAMINA(playerid);
			gracz[playerid][stamina_timestamp] = serwer[time_timestamp]+(60*3);
		}
		else if(tmpFloat > 10.0) 
		{
			SetPlayerHealth(playerid, tmpFloat-2.0);
			LeftNotifyShow(playerid, "info", "Twoja postac jest wyczerpana. Tracisz HP.", LN_RED);
			gracz[playerid][stamina_timestamp] = serwer[time_timestamp]+(60);
		}
	}
	if(floatround(tmpFloat) != gracz[playerid][HP])
	{
		gracz[playerid][HP] = floatround(tmpFloat);
		mq_format("UPDATE `Konta` SET `HP`='%d' WHERE `id`='%d';", gracz[playerid][HP], gracz[playerid][UID]);
		mq_send("QUpdateHP");
		HUD_UpdateHP(playerid);
	}
	GetPlayerArmour(playerid, tmpFloat);
	gracz[playerid][armour] = floatround(tmpFloat);
	HUD_UpdateARMOUR(playerid);
	return 1;
}
//***************************************************************************************skrypt BW
//aby wyłączyć bw: gracz[playerid][bw_time] = 0;
task Process_BrutallyWounded(playerid)
{
	if(gracz[playerid][bw] > 0)//ma bw
	{
		//czy jest w miejscu gdzie powinien miec bw:
		//only X Y:
		if(GetDistanceBetweenPoints(gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], gracz[playerid][bw_X], gracz[playerid][bw_Y], gracz[playerid][bw_Z]) > 4.0)
		{
			SetPlayerPos(playerid, gracz[playerid][bw_X], gracz[playerid][bw_Y], gracz[playerid][bw_Z]);
		}
		if(gracz[playerid][bw_time] > 0)//odlicza
		{
			gracz[playerid][bw_time]--;
			new strTemp[128];
			format(strTemp, 128,"~n~~n~~n~~n~~n~~n~~n~~n~~n~~b~nieprzytomny:~n~~g~pozostalo %d sekund.", gracz[playerid][bw_time]);
			GameTextForPlayer(playerid, strTemp, 1000, 3);
			SetPlayerCameraPos(playerid, gracz[playerid][bw_X]+3.0, gracz[playerid][bw_Y]+3.0, gracz[playerid][bw_Z]+5);
			SetPlayerCameraLookAt(playerid, gracz[playerid][bw_X], gracz[playerid][bw_Y], gracz[playerid][bw_Z]);
			SetPlayerHealth(playerid, 100.0);
			SetPlayerInterior(playerid, gracz[playerid][bw_interior]);
			SetPlayerVirtualWorld(playerid, gracz[playerid][bw_virtualworld]);
			if(GetPlayerAnimationIndex(playerid) != 746 && gracz[playerid][opu_vehicleid] == 0) ApplyAnimation(playerid, "KNIFE", "KILL_Knife_Ped_Die", 4.1, 0, 1, 1, 1, 0, 1);
		}
		else//koniec odliczania, staje sie przytomny
		{
			gracz[playerid][bw] = 0;
			LeftNotifyShow(playerid, "info", "Twoja ~y~postac~w~ doszla~n~do siebie.");
			ClearAnimations(playerid, 1);
			SetPlayerSkin(playerid, GetPlayerSkin(playerid));
			LoadFractionWeapons(playerid, gracz[playerid][frakcja]);
			SetCameraBehindPlayer(playerid);
			SetPlayerPos(playerid, gracz[playerid][bw_X], gracz[playerid][bw_Y], gracz[playerid][PosZ]);
		}
		mq_format("UPDATE `Konta` SET `bw`='%d', `bw_time`='%d' WHERE `id`='%d';", gracz[playerid][bw], gracz[playerid][bw_time], gracz[playerid][UID]);
		mq_send("QUpdateBW");
	}
	return 1;
}

stock SetPlayerBW(playerid, time_min, Float:bwX, Float:bwY, Float:bwZ)
{
	if(gracz[playerid][relog_data_loaded] == false) return 0;
	if(gracz[playerid][bw] > 0) return 0;
	//if(GetPlayerVirtualWorld(playerid) != 0) return 0;//tylko na vw 0 jest bw
	//if(GetPlayerInterior(playerid) != 0) return 0;//tylko na int 0 jest bw
	gracz[playerid][bw] = 1;
	gracz[playerid][bw_time] = 60*time_min;
	if(gracz[playerid][event_saved] == true || GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0) gracz[playerid][bw_time] = 16;
	gracz[playerid][bw_X] = bwX;
	gracz[playerid][bw_Y] = bwY;
	gracz[playerid][bw_Z] = bwZ;
	gracz[playerid][bw_interior] = GetPlayerInterior(playerid);
	gracz[playerid][bw_virtualworld] = GetPlayerVirtualWorld(playerid);
	if(GetPlayerVirtualWorld(playerid) != 0) return 0;//tylko na vw 0 jest bw
	if(GetPlayerInterior(playerid) != 0) return 0;//tylko na int 0 jest bw
	mq_format("UPDATE `Konta` SET `bw`='%d', `bw_time`='%d', `bw_X`='%f', `bw_Y`='%f', `bw_Z`='%f' WHERE `id`='%d';", gracz[playerid][bw], gracz[playerid][bw_time], bwX, bwY, bwZ, gracz[playerid][UID]);
	mq_send("QUpdateBW");
	Process_BrutallyWounded(playerid);
	return 1;
}
//*************************************************************************************STEROWANIE KURSOREM WSKAZUJACYM (object) GRACZA 
stock SetPointerPos(playerid, Float:ppX, Float:ppY, Float:ppZ)
{
	SetDynamicObjectPos(gracz[playerid][pointer_object], ppX, ppY, ppZ);
	return 1;
}
//*************************************************************************************SYSTEM WYPADKÓW
/*stock VehicleCrashSystem(playerid, vehicleid)
{
	new Float:acutal_hp;
	GetVehicleHealth(vehicleid, acutal_hp);
	gracz[playerid][opu_speed] = GetVehSpeed(gracz[playerid][opu_vehicleid]);
	//printf("speed: %d", gracz[playerid][opu_speed]);
	if(pojazd[vehicleid][v_crash_hp]-10.0 > acutal_hp && pojazd[vehicleid][v_crash_hp] > 400.0 && gracz[playerid][opu_speed]+10 < pojazd[vehicleid][v_last_speed])
	{
		printf("[CRASH!] Roznica predkosci: %d | Roznica HP: %f", pojazd[vehicleid][v_last_speed]-gracz[playerid][opu_speed], acutal_hp-pojazd[vehicleid][v_crash_hp]);
	}
	pojazd[vehicleid][v_crash_hp] = acutal_hp;
	return 1;
}
*/
task OnPlayerCrashVehicle(playerid, vehicleid, Float:damage)
{
	if(gracz[playerid][relog_data_loaded] == false) return 1;
	//printf("OnPlayerCrashVehicle(playerid:%d, vehicleid:%d, Float:damage:%f)", playerid, vehicleid, Float:damage);
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_DRVLICENSE) return 1;//w L-ce nie da sie mieć wypadku
	if(IsVehicleBike(pojazd[vehicleid][v_model]) || IsVehicleHelicopter(pojazd[vehicleid][v_model])) return 1;
	//if(IsPlayerOnDutyFraction(playerid)) return 1;//jeśli jest pracownikiem na duty, to brak wypadku
	switch(floatround(damage))
	{
		case 0..70:
		{
			if(gracz[playerid][pasy]) return 1;
			new Float:tmpFloat;
			GetPlayerHealth(playerid, tmpFloat);
			if(tmpFloat > 20) SetPlayerHealth(playerid, tmpFloat-4.0);
			ShowScreenFilter(playerid, 0xFF000060);
			SetTimerEx("HideCrashEffect", 400, false, "d", playerid);
			TogglePlayerControllable(playerid, false);
			if(gracz[playerid][when_tipsy] == 0) SetPlayerDrunkLevel(playerid, 2500);
		}
		case 71..90:
		{
			if(gracz[playerid][pasy]) return 1;
			new Float:tmpFloat;
			GetPlayerHealth(playerid, tmpFloat);
			if(tmpFloat > 20) SetPlayerHealth(playerid, tmpFloat-8.0);
			ShowScreenFilter(playerid, 0xFF000080);
			SetTimerEx("HideCrashEffect", 800, false, "d", playerid);
			TogglePlayerControllable(playerid, false);
			if(gracz[playerid][when_tipsy] == 0) SetPlayerDrunkLevel(playerid, 3500);
		}
		default://wypadek
		{
			if(gracz[playerid][event_saved] == true) return 0;//wypadki wyłączone dla osób zapisanych na event
			new engine, lights, alarm, doors, bonnet, boot, objective;
			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(vehicleid, 0, 0, alarm, doors, bonnet, boot, objective);
			ShowScreenFilter(playerid, 0xFF000099);
			TogglePlayerControllable(playerid, false);
			SetTimerEx("WypadekDelay", 2000, false, "dd", playerid, vehicleid);
			SetTimerEx("HideCrashEffect", 10000, false, "d", playerid);
			GameTextForPlayer(playerid, "WYPADEK!", 2500, 3);
		}
	}
	return 1;
}

task WypadekDelay(playerid, vehicleid)
{
	if(IsPlayerInVehicle(playerid, vehicleid))
	{
		if(IsPlayerOnDutyFraction(playerid))
		{
			vehicleid = GetPlayerVehicleID(playerid);
			if(vehicleid == 0) return 1;
			gracz[playerid][wypadek] = 1;
			gracz[playerid][wypadek_time] = 10;
			new Float:vPos[4];
			GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
			GetVehicleZAngle(vehicleid, vPos[3]);
			gracz[playerid][wypadek_X] = vPos[0];
			gracz[playerid][wypadek_Y] = vPos[1];
			gracz[playerid][wypadek_Z] = vPos[2];
			gracz[playerid][wypadek_R] = vPos[3];
			if(GetPlayerVehicleSeat(playerid) == 0) gracz[playerid][wypadek_vehicleuid] = pojazd[vehicleid][v_id];
			else gracz[playerid][wypadek_vehicleuid] = 0;

			if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER)//zapis wypadków tylko w pojazdach prywatnych
			{
				mq_format("UPDATE `Konta` SET `wypadek`='%d', `wypadek_time`='%d', `wypadek_X`='%f', `wypadek_Y`='%f', `wypadek_Z`='%f', `wypadek_R`='%f', `wypadek_vehicleuid`='%d' WHERE `id`='%d';", gracz[playerid][wypadek], gracz[playerid][wypadek_time], gracz[playerid][wypadek_X], gracz[playerid][wypadek_Y], gracz[playerid][wypadek_Z], gracz[playerid][wypadek_R], gracz[playerid][wypadek_vehicleuid], gracz[playerid][UID]);
				mq_send("QUpdateWypadek");
			}
		}
		else if(isvip(playerid))
		{
			if(FractionDutyWorkersCount(F_EMERGENCY) > 0) WypadekStart(playerid, 5);
			else if(gracz[playerid][pasy]) WypadekStart(playerid, 1);
			else WypadekStart(playerid, 2);
		}
		else
		{
			if(FractionDutyWorkersCount(F_EMERGENCY) > 0) WypadekStart(playerid, 10);
			else if(gracz[playerid][pasy]) WypadekStart(playerid, 2);
			else WypadekStart(playerid, 5);
		}
	}
	return 1;
}

task HideCrashEffect(playerid)
{
	if(gracz[playerid][wypadek] > 0) return 0;
	HideScreenFilter(playerid);
	TogglePlayerControllable(playerid, true);
	return 1;
}

stock WypadekStart(playerid, wtime)
{
	if(gracz[playerid][wypadek] > 0) return 0;
	if(gracz[playerid][event_saved] == true) return 0;//wypadki wyłączone dla osób zapisanych na event
	new vehicleid = GetPlayerVehicleID(playerid);
	if(vehicleid == 0) return 0;
	//kod wbijający pasażerom bw
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(!gracz[p][loggedin]) continue;
		if(gracz[p][opu_vehicleid] == vehicleid)
		{
			if(gracz[playerid][pasy] == false)
			{
				if(GetPlayerVehicleSeat(p) != 0)
				{
					RemovePlayerFromVehicle(p);
					SetPlayerBW(p, 3, gracz[playerid][PosX]+3.0, gracz[playerid][PosY]+3.0, gracz[playerid][PosZ]);
				}
			}
		}
	}
	//kod wbijający pasażerom bw - end
	if(GetPlayerVehicleSeat(playerid) == 0) gracz[playerid][wypadek_vehicleuid] = pojazd[vehicleid][v_id];
	else gracz[playerid][wypadek_vehicleuid] = 0;
	if(gracz[playerid][wypadek_vehicleuid] != 0)
	{
		gracz[playerid][wypadek] = 1;
		gracz[playerid][wypadek_time] = 60*wtime;
		new Float:vPos[4];
		GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
		GetVehicleZAngle(vehicleid, vPos[3]);
		gracz[playerid][wypadek_X] = vPos[0];
		gracz[playerid][wypadek_Y] = vPos[1];
		gracz[playerid][wypadek_Z] = vPos[2];
		gracz[playerid][wypadek_R] = vPos[3];
		
	
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER)//zapis wypadków tylko w pojazdach prywatnych
		{
			mq_format("UPDATE `Konta` SET `wypadek`='%d', `wypadek_time`='%d', `wypadek_X`='%f', `wypadek_Y`='%f', `wypadek_Z`='%f', `wypadek_R`='%f', `wypadek_vehicleuid`='%d' WHERE `id`='%d';", gracz[playerid][wypadek], gracz[playerid][wypadek_time], gracz[playerid][wypadek_X], gracz[playerid][wypadek_Y], gracz[playerid][wypadek_Z], gracz[playerid][wypadek_R], gracz[playerid][wypadek_vehicleuid], gracz[playerid][UID]);
			mq_send("QUpdateWypadek");
		}
		SetCarBlinking(vehicleid, 2);
	}
	return 1;
}

task Process_Wypadek(playerid)
{
	if(gracz[playerid][wypadek] > 0)
	{
		new vehicleid;
		if(gracz[playerid][wypadek_vehicleuid] != 0)
		{
			vehicleid = VehicleUidToVehicleid(gracz[playerid][wypadek_vehicleuid]);
		 	if(vehicleid == -1)//jeśli pojazd nie istnieje na serwerze to anuluje wypadek
		 	{
		 		gracz[playerid][wypadek_time] = 0;
		 		gracz[playerid][wypadek_vehicleuid] = 0;
		 		gracz[playerid][wypadek] = 0;
		 		HideScreenFilter(playerid);
		 		TogglePlayerControllable(playerid, true);
		 		if(gracz[playerid][when_tipsy] == 0) SetPlayerDrunkLevel(playerid, 0);
		 		mq_format("UPDATE `Konta` SET `wypadek`='%d', `wypadek_time`='%d' WHERE `id`='%d';", gracz[playerid][wypadek], gracz[playerid][wypadek_time], gracz[playerid][UID]);
		 		mq_send("QUpdateWypadek");
		 		return 1;
		 	}
		 	if(GetPlayerVehicleID(playerid) != vehicleid && vehicleid != -1) PutPlayerInVehicle(playerid, vehicleid, 0);
		 	new Float:vPos[3];
		 	GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
		 	new engine, lights, alarm, doors, bonnet, boot, objective;
		 	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		 	SetVehicleParamsEx(vehicleid, 0, 0, alarm, doors, bonnet, boot, objective);
		 	if(GetDistanceBetweenPoints(vPos[0], vPos[1], vPos[2], gracz[playerid][wypadek_X], gracz[playerid][wypadek_Y], gracz[playerid][wypadek_Z]) > 4.0)
		 	{
		 		SetVehiclePos(vehicleid, gracz[playerid][wypadek_X], gracz[playerid][wypadek_Y], gracz[playerid][wypadek_Z]);
		 		SetVehicleZAngle(vehicleid, gracz[playerid][wypadek_R]);
				Handbrake(vehicleid, 0);//zwalnianie recznego
			}
		}
		else
		{
			gracz[playerid][wypadek_time] = 0;
		 	gracz[playerid][wypadek_vehicleuid] = 0;
		 	gracz[playerid][wypadek] = 0;
		 	HideScreenFilter(playerid);
		 	TogglePlayerControllable(playerid, true);
		 	if(gracz[playerid][when_tipsy] == 0) SetPlayerDrunkLevel(playerid, 0);
		 	mq_format("UPDATE `Konta` SET `wypadek`='%d', `wypadek_time`='%d' WHERE `id`='%d';", gracz[playerid][wypadek], gracz[playerid][wypadek_time], gracz[playerid][UID]);
		 	mq_send("QUpdateWypadek");
		 	return 1;
		}
		if(gracz[playerid][wypadek_time] > 0)//podczas wypadku odliczanie
		{
			gracz[playerid][wypadek_time]--;
			new strTemp[128];
			format(strTemp, 128,"~n~~n~~n~~n~~b~wypadek:~n~~g~pozostalo %d sekund.", gracz[playerid][wypadek_time]);
			GameTextForPlayer(playerid, strTemp, 1000, 3);
			ShowScreenFilter(playerid, 0xFF000080);
			TogglePlayerControllable(playerid, false);
			if(gracz[playerid][when_tipsy] == 0) SetPlayerDrunkLevel(playerid, 2200);
		}
		else//koniec wypadku
		{
			DisableCarBlinking(GetPlayerVehicleID(playerid));
			gracz[playerid][wypadek] = 0;
			HideScreenFilter(playerid);
			TogglePlayerControllable(playerid, true);
			if(gracz[playerid][when_tipsy] == 0) SetPlayerDrunkLevel(playerid, 0);
		}
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER)//zapis wypadków tylko w pojazdach prywatnych
		{
			mq_format("UPDATE `Konta` SET `wypadek`='%d', `wypadek_time`='%d' WHERE `id`='%d';", gracz[playerid][wypadek], gracz[playerid][wypadek_time], gracz[playerid][UID]);
			mq_send("QUpdateWypadek");
		}
		//---------
		//dodawanie wezwania jeśli go nie ma
		if(gracz[playerid][wypadek_time] > 60)//tylko powyżej 60 sek
		{
			if(GetDistanceBetweenPoints(gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], gracz[playerid][wypadek_X], gracz[playerid][wypadek_Y], gracz[playerid][wypadek_Z]) < 8.0)
			{
				new bool:find_victimoid;
				for(new c; c < MAX_CALLS; c++)
				{
					if(calls[c][call_type] == 0) continue;
					if(calls[c][call_fraction] == F_EMERGENCY)
					{
						if(calls[c][call_calleruid] == gracz[playerid][UID])
						{
							find_victimoid = true;//znaleziono
							break;
						}
					}
				}
				if(!find_victimoid) 
				{
					NewCall(F_EMERGENCY, gracz[playerid][UID], 1, "Wypadek", gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);//jeśli nie ma, to dodajemy
					LeftNotifyShow(playerid, "Wypadek", "Sluzby ratunkowe zostaly powiadomione o Twoim wypadku.", LN_GREEN, 15);
				}
			}
		}
		//----------
	}
	//TODO: usuwanie wezwania
	return 1;
}
//*************************************************************************************************************SPEEDCAP
new Float:g_fSpeedCap[ MAX_PLAYERS ] = { 0.0, ... };
new g_fSpeedCapWarn[MAX_PLAYERS];
task Process_SpeedCap(playerid)
{
	new
	s_iVehicle
	;
	
	if ( g_fSpeedCap[ playerid ] != 0.0 && GetPlayerState( playerid ) == PLAYER_STATE_DRIVER )
	{
		s_iVehicle = GetPlayerVehicleID( playerid );

		if ( s_iVehicle )
		{
			new
			Float:s_fX,
			Float:s_fY,
			Float:s_fZ,
			Float:s_fVX,
			Float:s_fVY,
			Float:s_fVZ
			;
			
			GetVehiclePos( s_iVehicle, s_fX, s_fY, s_fZ );
			GetVehicleVelocity( s_iVehicle, s_fVX, s_fVY, s_fVZ );
			if ( !IsPlayerInRangeOfPoint( playerid, g_fSpeedCap[ playerid ] + 0.05, s_fX + s_fVX, s_fY + s_fVY, s_fZ + s_fVZ ) )
			{
				g_fSpeedCapWarn[playerid]++;	
				if(g_fSpeedCapWarn[playerid] > 4)
				{
					static
					Float:s_fLength
					;
					
					s_fLength = floatsqroot( ( s_fVX * s_fVX ) + ( s_fVY * s_fVY ) + ( s_fVZ * s_fVZ ) );
					
					s_fVX = ( s_fVX / s_fLength ) * g_fSpeedCap[ playerid ];
					s_fVY = ( s_fVY / s_fLength ) * g_fSpeedCap[ playerid ];
					s_fVZ = ( s_fVZ / s_fLength ) * g_fSpeedCap[ playerid ];
					
					SetVehicleVelocity( s_iVehicle, s_fVX, s_fVY, s_fVZ );
					g_fSpeedCapWarn[playerid] = 0;
				}
			}
			else if(g_fSpeedCapWarn[playerid] > 0) g_fSpeedCapWarn[playerid]--;
		}
	}
	/*else if ( g_fSpeedCap[ playerid ] != 0.0 && GetPlayerState( playerid ) == PLAYER_STATE_ONFOOT )
	{
		static
		Float:s_fX,
		Float:s_fY,
		Float:s_fZ,
		Float:s_fVX,
		Float:s_fVY,
		Float:s_fVZ,
		Float:s_temp_fVZ
		;

		GetPlayerPos(playerid, s_fX, s_fY, s_fZ );
		GetPlayerVelocity(playerid, s_fVX, s_fVY, s_fVZ );
		s_temp_fVZ = s_fVZ;
		if (!IsPlayerInRangeOfPoint( playerid, g_fSpeedCap[ playerid ] + 0.05, s_fX + s_fVX, s_fY + s_fVY, s_fZ + s_fVZ ) )
		{
			static
			Float:s_fLength
			;

			s_fLength = floatsqroot( ( s_fVX * s_fVX ) + ( s_fVY * s_fVY ) + ( s_fVZ * s_fVZ ) );

			s_fVX = ( s_fVX / s_fLength ) * g_fSpeedCap[ playerid ];
			s_fVY = ( s_fVY / s_fLength ) * g_fSpeedCap[ playerid ];
			s_fVZ = ( s_fVZ / s_fLength ) * g_fSpeedCap[ playerid ];
			SetPlayerVelocity( playerid, s_fVX, s_fVY, s_temp_fVZ);
		}
	}
	*/
	return 1;
}

stock SetPlayerSpeedCap( playerid, Float:value )//0.46 = 100 KM/h
{
	if ( 0 <= playerid < sizeof( g_fSpeedCap ) )
	{
		g_fSpeedCap[ playerid ] = value;
		g_fSpeedCapWarn[playerid] = 0;
	}
}

stock DisablePlayerSpeedCap( playerid )
{
	if ( 0 <= playerid < sizeof( g_fSpeedCap ) )
	{
		g_fSpeedCap[ playerid ] = 0.0;
		g_fSpeedCapWarn[playerid] = 0;
	}
}
//*************************************************************************************************************AKTUALIZACJA TD FRAKCJA
task Process_UpdateFractionTD(playerid)
{
	if(gracz[playerid][hud_tick_fraction] < 4)
	{
		if(gracz[playerid][firma] != 0) gracz[playerid][hud_tick_fraction]++;
		if(gracz[playerid][frakcja] == 0) gracz[playerid][hud_tick_fraction] = 4;
		if(IsPlayerOnDutyFraction(playerid))//duty
		{
			new fcolor;
			switch(gracz[playerid][frakcja])
			{
				case F_POLICE: fcolor = COLOR_POL;
				case F_BORDERGUARD: fcolor = COLOR_BORG;
				case F_EMERGENCY: fcolor = COLOR_EMRG;
				case F_ROADASSIST: fcolor = COLOR_ROADA;
				case F_TAXI: fcolor = COLOR_TAXI;
				case F_MAFIA: fcolor = COLOR_MAFIA;
				default: fcolor = COLOR_DRV;
			}
			HUD_SetFrakcja(playerid, fcolor, GetFractionNameEx(gracz[playerid][frakcja]));
		}
		else//offduty
		{
			HUD_SetFrakcja(playerid, COLOR_GREY, GetFractionNameEx(gracz[playerid][frakcja]));
		}
	}
	else
	{
		gracz[playerid][hud_tick_fraction]++;
		if(gracz[playerid][firma] != 0)
		{
			if(IsPlayerOnDutyCompany(playerid))//duty
			{
				HUD_SetFrakcja(playerid, 0x00BA8CFF, company[gracz[playerid][firma]][cny_name]);
			}
			else//offduty
			{
				HUD_SetFrakcja(playerid, COLOR_GREY, company[gracz[playerid][firma]][cny_name]);
			}
		}
		if(gracz[playerid][hud_tick_fraction] > 8) gracz[playerid][hud_tick_fraction] = 0;
	}
	return 1;
}
//*************************************************************************************************************ZMIENIARKA SKINÓW
stock ShowSelectSkinWindow(playerid)
{
	if(IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Będąc na służbie nie możesz zmienić skina.");
	if(gracz[playerid][Plec] == 1) ShowModelSelectionMenuEx(playerid, skins_male, sizeof(skins_male), "Wybierz skin", MSEL_CHANGESKIN);
	else if(gracz[playerid][Plec] == 2) ShowModelSelectionMenuEx(playerid, skins_female, sizeof(skins_female), "Wybierz skin", MSEL_CHANGESKIN);
	return 1;
}
//*************************************************************************************************************BINCO
stock Init_Binco()
{

	//custom binco
	CreateActor(56,2028.2819,2045.0819,11.0337,275.0389);//actor - custom binco
	CreateDynamic3DTextLabel("« "COL_YELLOW"BINCO "COL_GREEN"»\n"COL_RED"• "COL_WHITE"Wpisz "COL_RED"/binco"COL_WHITE" aby zmienić skin/zakupić akcesoria. "COL_RED"•", 0x009933FF, XYZ_BINCOC, 10.0);
	CreatePickup(1275, 1, XYZ_BINCOC);
	CreateDynamicMapIcon(XYZ_BINCOC, 45, 0, .streamdistance = 1000.0, .style = MAPICON_GLOBAL);
	//oryginalne binco
	CreateDynamic3DTextLabel("« "COL_YELLOW"BINCO "COL_GREEN"»\n"COL_RED"• "COL_WHITE"Wpisz "COL_RED"/binco"COL_WHITE" aby zmienić skin/zakupić akcesoria. "COL_RED"•", 0x009933FF, XYZ_BINCO, 10.0);
	CreatePickup(1275, 1, XYZ_BINCO, -1);
	return 1;
}

//*************************************************************************************************************AFK DETECT
task Process_AFK(playerid)
{
	if(!IsPlayerInRangeOfPoint(playerid, 4.0, gracz[playerid][afk_lastposX], gracz[playerid][afk_lastposY], gracz[playerid][afk_lastposZ])) 
	{
		ResetIdleAFK(playerid);
		GetPlayerPos(playerid, gracz[playerid][afk_lastposX], gracz[playerid][afk_lastposY], gracz[playerid][afk_lastposZ]);
	}
	else if(gracz[playerid][bw] > 0 || gracz[playerid][wypadek] > 0)
	{
		ResetIdleAFK(playerid);
	}
	if(gracz[playerid][afk_status] == false)//nie jest afk
	{
		if(gracz[playerid][afk_detect_timestamp] < serwer[time_timestamp] || gracz[playerid][opu_timestamp]+20 < serwer[time_timestamp])//przekroczył czas bezczynności
		{
			gracz[playerid][afk_status] = true;//zmienianie statusu na AFK
			gracz[playerid][afk_time][0] = serwer[time_hour];
			gracz[playerid][afk_time][1] = serwer[time_minute];
			SendClientMessageEx(playerid, 0xFF0000FF, "[AFK] "COL_ORANGE" Przechodzisz w status AFK.");
		}
	}
	else//jest afk
	{
		if(gracz[playerid][afk_detect_timestamp] > serwer[time_timestamp] && gracz[playerid][opu_timestamp]+20 > serwer[time_timestamp])//nie przekroczył czasu bezczynności
		{
			gracz[playerid][afk_status] = false;//usuwamy status afk
			SendClientMessageEx(playerid, 0xFF0000FF, "[AFK] "COL_LIME" Witaj z powrotem!");
		}
	}
	return 1;
}

stock ResetIdleAFK(playerid)
{
	//printf("ResetIdleAFK: %d", random(100));
	gracz[playerid][afk_detect_timestamp] = serwer[time_timestamp]+(60)*4;
	return 1;
}

stock IsPlayerAFK(playerid) return gracz[playerid][afk_status];
stock IsPlayerPaused(playerid) 
{
	#pragma unused playerid
	return 0;
}
//*************************************************************************************************************PRZEGRANE GODZINY
task Process_PlayedTime(playerid)
{
	if(IsPlayerAFK(playerid)) return 1;
	if(IsPlayerPaused(playerid)) return 1;
	new bool:secupdate = false;
	gracz[playerid][PSek]++;
	while(gracz[playerid][PSek] > 59)
	{
		gracz[playerid][PSek] -= 60;
		gracz[playerid][PMin]++;
		mq_format("UPDATE `Konta` SET `PMin`='%d', `PSek`='%d' WHERE `id`='%d';", gracz[playerid][PMin], gracz[playerid][PSek], gracz[playerid][UID]);
		mq_send("QPlayedTime");
		secupdate = true;
	}
	while(gracz[playerid][PMin] > 59)
	{
		gracz[playerid][PMin] -= 60;
		gracz[playerid][PGodz]++;
		mq_format("UPDATE `Konta` SET `PGodz`='%d', `PMin`='%d' WHERE `id`='%d';", gracz[playerid][PGodz], gracz[playerid][PMin], gracz[playerid][UID]);
		mq_send("QPlayedTime");
	}
	if(secupdate == false)
	{
		mq_format("UPDATE `Konta` SET `PSek`='%d' WHERE `id`='%d';", gracz[playerid][PSek], gracz[playerid][UID]);
		mq_send("QPlayedTime");
	}
	return 1;
}
//*************************************************************************************************************SKRYPT AUTOBUSÓW
stock Init_BusStations()
{
	new strLabel[256];
	for(new b; b < sizeof(bus_stations); b++)
	{
		format(strLabel, 256, "« "COL_BLUE"PRZYSTANEK - "COL_LIME"%s "COL_GREEN"»\n"COL_RED"• "COL_GREEN"/bus "COL_WHITE"- aby wybrac miejsce docelowe. "COL_RED"•", bus_stations[b][bs_name]);
		if(b == 0) CreateDynamic3DTextLabel(strLabel, 0x009933FF, bus_stations[b][bs_X], bus_stations[b][bs_Y], bus_stations[b][bs_Z], 100.0);//spawn - wiekszy zasieg 3dtextu
		else CreateDynamic3DTextLabel(strLabel, 0x009933FF, bus_stations[b][bs_X], bus_stations[b][bs_Y], bus_stations[b][bs_Z], 10.0);
		CreateDynamicPickup(1239, 1, bus_stations[b][bs_X], bus_stations[b][bs_Y], bus_stations[b][bs_Z], 0, 0);
		CreateDynamicMapIcon(bus_stations[b][bs_X], bus_stations[b][bs_Y], bus_stations[b][bs_Z], 8, 0, .streamdistance = 200.0, .style = MAPICON_LOCAL);
	}
	return 1;
}

stock IsPlayerInRangeOfBusStation(playerid)
{
	for(new b; b < sizeof(bus_stations); b++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 1.5, bus_stations[b][bs_X], bus_stations[b][bs_Y], bus_stations[b][bs_Z])) return b;
	}
	return -1;
}

stock CalculatePriceBusStation(from, where)
{
	if(from == -1) return 0;
	if(from == where) return 0;
	new Float:wynik;
	new Float:distance = GetDistanceBetweenPoints(bus_stations[from][bs_X], bus_stations[from][bs_Y], bus_stations[from][bs_Z], bus_stations[where][bs_X], bus_stations[where][bs_Y], bus_stations[where][bs_Z]);
	const Float:price_rate = 0.06;
	wynik = price_rate*distance;
	return floatround(wynik);
}

stock StartBusTravel(playerid, from, where)
{
	if(gracz[playerid][bus_travel]) return 0;
	if(from == where) return 0;
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) return 0;
	gracz[playerid][bus_travel] = true;
	SetPlayerCameraLookAt(playerid, bus_stations[from][bs_X], bus_stations[from][bs_Y], bus_stations[from][bs_Z]);//kamera w dół
	SetPlayerCameraPos(playerid, bus_stations[from][bs_X], bus_stations[from][bs_Y], bus_stations[from][bs_Z]+5.0);
	SetPVarInt(playerid, "bustravel_where", where);
	SetTimerEx("BusTravel_Step", 1500, false, "dddd", playerid, from, where, 0);
	gracz[playerid][last_skin] = GetPlayerSkin(playerid);
	return 1;
}

task BusTravel_Step(playerid, from, where, step)
{
	if(gracz[playerid][bus_travel] == false) return 1;
	switch(step)
	{
		case 0://kamera leci do góry
		{
			PlayerPlaySound(playerid, 1147, 0, 0, 0);
			TogglePlayerSpectating(playerid, 1);
			InterpolateCameraPos(playerid, bus_stations[from][bs_X], bus_stations[from][bs_Y], bus_stations[from][bs_Z]+5.0, bus_stations[from][bs_X], bus_stations[from][bs_Y], bus_stations[from][bs_Z]+240.0, 2000, CAMERA_CUT);
			SetTimerEx("BusTravel_Step", 2000, false, "dddd", playerid, from, where, 1);
		}
		case 1://leci w bok
		{
			const travel_time = 1000*30;
			PlayerPlaySound(playerid, 1076, 0, 0, 0);
			InterpolateCameraPos(playerid, bus_stations[from][bs_X], bus_stations[from][bs_Y], bus_stations[from][bs_Z]+240.0, bus_stations[where][bs_X], bus_stations[where][bs_Y], bus_stations[from][bs_Z]+240.0, travel_time, CAMERA_CUT);
			SetTimerEx("BusTravel_Step", travel_time-2500, false, "dddd", playerid, from, where, 2);
		}
		case 2://leci w dół
		{
			PlayerPlaySound(playerid, 1077, 0, 0, 0);
			PlayerPlaySound(playerid, 1147, 0, 0, 0);
			InterpolateCameraPos(playerid, bus_stations[where][bs_X], bus_stations[where][bs_Y], bus_stations[from][bs_Z]+240.0, bus_stations[where][bs_X], bus_stations[where][bs_Y], bus_stations[from][bs_Z]+5.0, 2000, CAMERA_CUT);
			SetTimerEx("BusTravel_Step", 2000, false, "dddd", playerid, from, where, 3);
		}
		case 3://dotarł na miejsce
		{
			TogglePlayerSpectating(playerid, 0);
			SetPlayerPos(playerid, bus_stations[where][bs_X], bus_stations[where][bs_Y], bus_stations[where][bs_Z]);
		}
	}
	return 1;
}
//*************************************************************************************************************SKLEP
stock Init_Shop()
{
	CreateDynamic3DTextLabel("« "COL_BLUE"SKLEP "COL_GREEN"»\n"COL_RED"• "COL_WHITE"Użyj "COL_RED"PPM"COL_WHITE" lub "COL_RED"/sklep"COL_WHITE" aby zakupić przedmiot. "COL_RED"•", 0x009933FF, XYZ_SHOP, 10.0);
	CreatePickup(1274, 1, XYZ_SHOP, -1);
	//biedra:
	for(new d; d < sizeof(custom_shops); d++)
	{
		CreateDynamic3DTextLabel("« "COL_BLUE"SKLEP "COL_GREEN"»\n"COL_RED"• "COL_WHITE"Użyj "COL_RED"PPM"COL_WHITE" lub "COL_RED"/sklep"COL_WHITE" aby zakupić przedmiot. "COL_RED"•", 0x009933FF, custom_shops[d][0], custom_shops[d][1], custom_shops[d][2], 10.0);
		CreatePickup(1274, 1, custom_shops[d][0], custom_shops[d][1], custom_shops[d][2], -1);
	}
	return 1;
}

stock IsPlayerInRangeOfShop(playerid)
{
	if(IsPlayerInRangeOfPoint(playerid, 2.0, XYZ_SHOP)) return 1;
	for(new d; d < sizeof(custom_shops); d++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 2.0, custom_shops[d][0], custom_shops[d][1], custom_shops[d][2])) return 1;
	}
	return 0;
}
//*************************************************************************************************************ŁADOWANIE OBIEKTÓW - FREEZE
stock Force_FreezeLoadObject(playerid, Float:posX, Float:posY, Float:posZ)
{
	if(gracz[playerid][kajdanki] || gracz[playerid][przykuty]) return 1;
	if(gracz[playerid][bw] > 0) return 1;
	gracz[playerid][loading_objects] = true;
	SetPlayerPos(playerid, posX, posY, posZ);
	TogglePlayerControllable(playerid, 0);
	SetTimerEx("FinishLoadObject", 3000, false, "dfff", playerid, posX, posY, posZ);
	//SetTimerEx("FinishLoadObject", TIME_LOADOBJ, false, "dfff", playerid, posX, posY, posZ);
	new strLO[64];
	format(strLO, 64, "~b~Ladowanie obiektow...");
	GameTextForPlayer(playerid, strLO, 3000, 3);
	return 1;
}

task FreezeLoadObject(playerid, Float:posX, Float:posY, Float:posZ)
{
	if(gracz[playerid][kajdanki] || gracz[playerid][przykuty]) return 1;
	if(gracz[playerid][bw] > 0) return 1;
	new strLO[64];
	if(gracz[playerid][loading_objects])
	{
		if(gracz[playerid][objectload_count] > 0)
		{
			//if(gracz[playerid][objectload_count] > 100) gracz[playerid][objectload_count] = 100;
			SetPlayerPos(playerid, posX, posY, posZ);
			format(strLO, 64, "~b~Ladowanie obiektow (%d)...", gracz[playerid][objectload_count]);
			GameTextForPlayer(playerid, strLO, 1000, 3);
			if(gracz[playerid][objectload_count] > 1100) gracz[playerid][objectload_count] = -1;
			else if(gracz[playerid][objectload_count] > 500) gracz[playerid][objectload_count] -= 550;
			else if(gracz[playerid][objectload_count] > 300) gracz[playerid][objectload_count] -= 152;
			else if(gracz[playerid][objectload_count] > 100) gracz[playerid][objectload_count] -= 50;
			else gracz[playerid][objectload_count] -= 33;
			if(gracz[playerid][objectload_count] < 0)
			{
				gracz[playerid][objectload_count] = 0;
				FinishLoadObject(playerid, posX, posY, posZ);
			}
			else
			{
				SetTimerEx("FreezeLoadObject", 800, false, "dfff", playerid, posX, posY, posZ);
			}
		}
		else
		{
			FinishLoadObject(playerid, posX, posY, posZ);
		}
		return 1;
	}
	if(GetDistanceBetweenPoints(gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], posX, posY, posZ) > 70.0)//przejście jest dość daleko - system wczytywania
	{
		gracz[playerid][loading_objects] = true;
		SetPlayerPos(playerid, posX, posY, posZ);
		TogglePlayerControllable(playerid, 0);
		SetTimerEx("FreezeLoadObject", 555, false, "dfff", playerid, posX, posY, posZ);
		//SetTimerEx("FinishLoadObject", TIME_LOADOBJ, false, "dfff", playerid, posX, posY, posZ);
		format(strLO, 64, "~b~Ladowanie obiektow (%d)...", gracz[playerid][objectload_count]);
		GameTextForPlayer(playerid, strLO, 500, 3);
	}
	else//blisko przejścia - przenoś natychmiast
	{
		gracz[playerid][loading_objects] = true;
		SetPlayerPos(playerid, posX, posY, posZ);
		gracz[playerid][objectload_count] = 0;
		FinishLoadObject(playerid, posX, posY, posZ);
	}
	return 1;
}

task FinishLoadObject(playerid, Float:posX, Float:posY, Float:posZ)
{
	GameTextForPlayer(playerid, "~g~Zaladowano!", 1500, 3);
	TogglePlayerControllable(playerid, 1);
	if(!gracz[playerid][loading_objects]) return 1;
	Streamer_Update(playerid);
	if(!IsPlayerInAnyVehicle(playerid)) SetPlayerPos(playerid, posX, posY, posZ);
	gracz[playerid][loading_objects] = false;
	return 1;
}
//*************************************************************************************************************Konfiguracja drużyn TEAM
task Process_PlayerTeam(playerid)
{
	new team = GetPlayerTeam(playerid);
	if(gracz[playerid][status_lunapark] == LPARK_ASG)
	{
		if(team != NO_TEAM) SetPlayerTeam(playerid, NO_TEAM);
		return 1;
	}
	if(gracz[playerid][event_saved] == true)
	{
		if(serwer[event_no_dm_status] == true)//bez DM?
		{
			if(team != 1) SetPlayerTeam(playerid, 1);
		}
		else//DM dozwolony
		{
			const ev_team_offset = 5;
			new eventid = gracz[playerid][event_teamid];
			if(eventid != -1)
			{
				if(event_teams[eventid][friendly_fire] == true)
				{
					if(team != NO_TEAM) SetPlayerTeam(playerid, NO_TEAM);//mogą się bić
				}
				else
				{
					if(eventid+ev_team_offset != team) SetPlayerTeam(playerid, eventid+ev_team_offset);//nie mogą się w teamach bić
				}
			}
			else if(eventid == -1 && team != NO_TEAM) SetPlayerTeam(playerid, NO_TEAM);//nie ma teamu, mogą się bić
		}
		return 1;
	}
	if(IsPlayerOnDutyFraction(playerid) && gracz[playerid][frakcja] == F_POLICE) 
	{
		new fid = gracz[playerid][frakcja];
		if(fractions[fid][fr_disable_ff] == true)
		{
			if(team != NO_TEAM) SetPlayerTeam(playerid, NO_TEAM);
		}
		else
		{
			if(team != 2) SetPlayerTeam(playerid, 2);
		}
	}
	else if(IsPlayerOnDutyFraction(playerid) && gracz[playerid][frakcja] == F_BORDERGUARD)
	{
		new fid = gracz[playerid][frakcja];
		if(fractions[fid][fr_disable_ff] == true)
		{
			if(team != NO_TEAM) SetPlayerTeam(playerid, NO_TEAM);
		}
		else
		{
			if(team != 2) SetPlayerTeam(playerid, 2);
		}
	}
	else if(IsPlayerOnDutyFraction(playerid) && gracz[playerid][frakcja] == F_MAFIA) 
	{
		new fid = gracz[playerid][frakcja];
		if(fractions[fid][fr_disable_ff] == true)
		{
			if(team != NO_TEAM) SetPlayerTeam(playerid, NO_TEAM);
		}
		else
		{
			if(team != 3) SetPlayerTeam(playerid, 3);
		}
	}
	else
	{
		if(gracz[playerid][ps_score] >= 20) 
		{
			if(team != NO_TEAM) SetPlayerTeam(playerid, NO_TEAM);
		}
		else if(team != 1) SetPlayerTeam(playerid, 1);
	}
	return 1;
}
//*************************************************************************************************************Logi kursów wszystkich
stock RegisterStartLogKurs(playerid)
{
	gracz[playerid][routelog_start_time] = serwer[time_timestamp];
	return 1;
}
//point_type - 0 - van loads, 1 - vehicleuid
stock LogKurs(playerid, vmodel, Float:km, point_type, pointSrc, pointDst, zoneSrc[], zoneDst[])
{
	if(gracz[playerid][routelog_start_time] == 0) return 0;
	new zoneid_src, zoneid_dst;
	for(new z; z < sizeof(all_zone_names); z++)
	{
		if(compare(zoneSrc, all_zone_names[z]))
		{
			zoneid_src = z;
			break;
		}
	}
	for(new z; z < sizeof(all_zone_names); z++)
	{
		if(compare(zoneDst, all_zone_names[z]))
		{
			zoneid_dst = z;
			break;
		}
	}
	mq_format("INSERT INTO `LogKursy` (`uid`, `vehicle`, `km`, `point_src`, `point_dst`, `point_type`, `zoneid_src`, `zoneid_dst`, `time_start`, `time_end`) VALUES ('%d', '%d', '%f', '%d', '%d', '%d', '%d', '%d', FROM_UNIXTIME('%d'), FROM_UNIXTIME('%d'));", gracz[playerid][UID], vmodel, km, pointSrc, pointDst, point_type, zoneid_src, zoneid_dst, gracz[playerid][routelog_start_time], serwer[time_timestamp]);
	mq_send("QSendLogKurs");
	gracz[playerid][routelog_start_time] = 0;
	return 1;
}
//*************************************************************************************************************DAMAGE
public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	if(issuerid != INVALID_PLAYER_ID) // If not self-inflicted
	{
		new playerid_team = GetPlayerTeam(playerid);
		new issuerid_team = GetPlayerTeam(issuerid);

		if(playerid_team != issuerid_team || playerid_team == NO_TEAM) 
		{
			if(gracz[issuerid][kajdanki] == true)
			{
				new Float:tHealth;
				new Float:tArmour;
				GetPlayerHealth(playerid, tHealth);
				GetPlayerArmour(playerid, tArmour);
				SetTimerEx("ReBackHP", 1, false, "dff", playerid, tHealth, tArmour);
				return 1;
			}
			if(weaponid == 0)
			{
				if((playerid_team == NO_TEAM && issuerid_team != 1) || issuerid_team == 2 || issuerid_team == 3)
				{
					new Float:take_dmg = gracz[issuerid][sila]-gracz[playerid][odpornosc];
					if(take_dmg < 0.1) take_dmg = 0.1;
					new Float:tHealth;
					GetPlayerHealth(playerid, tHealth);
					tHealth -= take_dmg;
					if(tHealth < 0.0) tHealth = 0.0;
					SetPlayerHealth(playerid, tHealth);
				}
				else 
				{
					new Float:tHealth;
					new Float:tArmour;
					GetPlayerHealth(playerid, tHealth);
					GetPlayerArmour(playerid, tArmour);
					SetTimerEx("ReBackHP", 1, false, "dff", playerid, tHealth, tArmour);
					return 1;
				}
			}
			gracz[playerid][lastshotedby] = issuerid;
			ShowTDShoot(issuerid);
			TempChangeColorNick(playerid, 0xFF0000EF, 2);
			SetTimerEx("Process_UpdateArmourHPSleep", 1, false, "d", playerid);
			if(!gracz[playerid][shoot_sf])
			{
				ShowScreenFilter(playerid, 0xFF000040);
				SetTimerEx("HideSF_Damage", 150, false, "d", playerid);
				gracz[playerid][shoot_sf] = true;
			}
		}
	}
	else
	{
		TempChangeColorNick(playerid, 0xFF0000EF, 2);
		SetTimerEx("Process_UpdateArmourHPSleep", 1, false, "d", playerid);
		if(!gracz[playerid][shoot_sf])
		{
			ShowScreenFilter(playerid, 0xFF000040);
			SetTimerEx("HideSF_Damage", 150, false, "d", playerid);
			gracz[playerid][shoot_sf] = true;
		}
	}
	return 1;
}

task HideSF_Damage(playerid)
{
	HideScreenFilter(playerid);
	gracz[playerid][shoot_sf] = false;
	return 1;
}

task ReBackHP(playerid, Float:value, Float:value2)
{
	SetPlayerHealth(playerid, value);
	SetPlayerArmour(playerid, value2);
	return 1;
}
//*************************************************************************************************************ADR
stock Process_PlayerADR(playerid, crash = 0)
{
	new vehicleid = gracz[playerid][opu_vehicleid];
	if(vehicleid == 0) return 1;
	new trucktype = IsVehicleTruck(pojazd[vehicleid][v_model]);
	new cargoveh = vehicleid;
	if(trucktype == 1)  cargoveh = GetVehicleTrailer(vehicleid);
	if(!IsValidDynamic3DTextLabel(pojazd[cargoveh][v_text3d])) return 1;
	const max_warns_adr = 3;
	if(vehicleid != 0)
	{
		if(cargoveh != 0)
		{
			new goodid = pojazd[cargoveh][v_cargo];
			if(goodid != 0)
			{
				if(goods[goodid][gds_adr] == true)
				{
					if(crash && pojazd[cargoveh][v_adr_warn] < max_warns_adr)
					{
						pojazd[cargoveh][v_adr_warn] += crash;
					}
					if(pojazd[cargoveh][v_adr_warn] > 0) gracz[playerid][delivered_adr_status] = 2;//uszkodzony adr
					else gracz[playerid][delivered_adr_status] = 1;//nieuszkodzony adr
					if(pojazd[cargoveh][v_adr_warn] > max_warns_adr)  pojazd[cargoveh][v_adr_warn] = max_warns_adr;
				}
				else gracz[playerid][delivered_adr_status] = 0;//brak adr
			}
			else gracz[playerid][delivered_adr_status] = 0;//brak adr
		}
	}
	return 1;
}

task Process_IdleADR()
{
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		if(pojazd[v][v_model] == 0) continue;
		if(pojazd[v][v_cargo] == 0) continue;
		if(goods[pojazd[v][v_cargo]][gds_adr] == false) continue;
		new bool:used_trailer = false;
		if(IsVehicleTrailer(pojazd[v][v_model]))//jeśli to naczepa
		{
			for(new p = PlayerPoolSize(); p != -1; p--)
			{
				if(gracz[p][loggedin])
				{
					if(gracz[p][cargo_trailerdid] == v)
					{
						used_trailer = true;
					}
				}
			}
		}
		else used_trailer = true;
		if(pojazd[v][v_owner_type] == VEHICLE_BUSINESS) used_trailer = true;
		if(used_trailer == false) continue;
		new strLabel[256];
		switch(pojazd[v][v_adr_warn])
		{
			case 0: format(strLabel, 256, ""COL_RED"[ADR]\n"COL_EASY"[Uszkodzenia: "COL_DRVONLINE"%d/3"COL_EASY"]", pojazd[v][v_adr_warn]);
			case 1: format(strLabel, 256, ""COL_RED"[ADR]\n"COL_EASY"[Uszkodzenia: "COL_YELLOW"%d/3"COL_EASY"]", pojazd[v][v_adr_warn]);
			case 2: format(strLabel, 256, ""COL_RED"[ADR]\n"COL_EASY"[Uszkodzenia: "COL_ORANGE"%d/3"COL_EASY"]", pojazd[v][v_adr_warn]);
			default:
			{
				if(pojazd[v][v_object][12] == 0)
				{
					pojazd[v][v_fire_hp] = 10;
					pojazd[v][v_object][12] = CreateDynamicObject(18691, 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
					AttachDynamicObjectToVehicle(pojazd[v][v_object][12], v, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
				}
				format(strLabel, 256, ""COL_RED"[ADR]\n"COL_EASY"[Uszkodzenia: "COL_RED"%d/3"COL_EASY"]", pojazd[v][v_adr_warn]);
			}
		}
		if(pojazd[v][v_object][12] != 0)
		{
			new fire_hp_str[64];
			if(pojazd[v][v_fire_hp] > 0)//zabezpieczenie przed infinity loop
			{
				for(new hp; hp < pojazd[v][v_fire_hp]; hp++)
				{
					format(fire_hp_str, 32, "%s•", fire_hp_str);
				}
			}
			if(pojazd[v][v_fire_hp] > 8) format(strLabel, 256, ""COL_RED"[ADR]\n"COL_EASY"[Uszkodzenia: "COL_RED"%d/3"COL_EASY"]\n"COL_ORANGE"%s", pojazd[v][v_adr_warn], fire_hp_str);
			else format(strLabel, 256, ""COL_RED"[ADR]\n"COL_EASY"[Uszkodzenia: "COL_RED"%d/3"COL_EASY"]\n"COL_GREEN"%s", pojazd[v][v_adr_warn], fire_hp_str);
			if(pojazd[v][v_fire_warn] < 15)
			{
				if(GetVehSpeed(v) < 100)
				{
					pojazd[v][v_fire_warn]++;
					format(strLabel, 256, "%s\n"COL_WHITE"["COL_RED"Wybuch za: "COL_ORANGE"%ds"COL_WHITE"]", strLabel, 15-pojazd[v][v_fire_warn]);
				}
				else
				{
					if(pojazd[v][v_fire_warn] > 0) pojazd[v][v_fire_warn]--;
					if(pojazd[v][v_fire_hp] > 1)
					{
						pojazd[v][v_fire_hp]--;
					}
					else
					{
						pojazd[v][v_fire_hp] = 0;
						if(pojazd[v][v_adr_warn] > 2) pojazd[v][v_adr_warn] = 2;
						DestroyDynamicObject(pojazd[v][v_object][12]);
						pojazd[v][v_object][12] = 0;
					}
					format(strLabel, 256, "%s\n"COL_WHITE"["COL_GREEN"Gaszenie..."COL_WHITE"]", strLabel);
				}
			}
			if(pojazd[v][v_fire_warn] >= 15)//ma być JEB
			{
				SetVehicleHealth(v, 0.0);
				new Float:vPos[3];
				GetVehiclePos(v, vPos[0], vPos[1], vPos[2]);
				CreateExplosion(vPos[0], vPos[1], vPos[2], 0, 10.0);
				if(IsVehicleTrailer(pojazd[v][v_model])) UnoccupiedVehicleDeath(v, INVALID_PLAYER_ID);
			}
		}
		else pojazd[v][v_fire_warn] = 0;
		UpdateDynamic3DTextLabelText(pojazd[v][v_text3d], -1, strLabel);
//		printf("%d: %s", v, strLabel);

	}
	return 1;
}

stock ResetVehicleADRData(vehicleid)
{
	pojazd[vehicleid][v_adr_warn] = 0;
	pojazd[vehicleid][v_fire_hp] = 0;
	pojazd[vehicleid][v_fire_warn] = 0;
	HideVehicleLabel(vehicleid, true);
	if(pojazd[vehicleid][v_object][12] != 0)
	{
		DestroyDynamicObject(pojazd[vehicleid][v_object][12]);
		pojazd[vehicleid][v_object][12]  = 0;
	}
	return 1;
}
//-----------------------------------------------------------------------------------------SYSTEM BANKÓW
#define MAX_BANKS 100
enum bnk_data
{
	bnk_id,
	Float:bnk_X,
	Float:bnk_Y,
	Float:bnk_Z,

	bnk_iconid,
	bnk_pickup,
	Text3D:bnk_3dtext
};

new banks[MAX_BANKS][bnk_data];

stock Init_Banks()
{
	mq_format("SELECT * FROM `banks`;");
	mq_send("LoadBanksFromDB");
	return 1;
}

task LoadBanksFromDB()
{
	mq_getdata();
	if(rekordy)
	{
		new i;
		new bnkid; 
		while(i < rekordy)
		{
			bnkid = GetFreeBankID();
			if(bnkid != -1)
			{
				cache_get_value_name_int(i, "id", 				banks[bnkid][bnk_id]);
				cache_get_value_name_float(i, "bX", 				banks[bnkid][bnk_X] );
				cache_get_value_name_float(i, "bY", 				banks[bnkid][bnk_Y] );
				cache_get_value_name_float(i, "bZ", 				banks[bnkid][bnk_Z] );

				banks[bnkid][bnk_iconid] = CreateDynamicMapIcon(banks[bnkid][bnk_X], banks[bnkid][bnk_Y], banks[bnkid][bnk_Z], 52, 0, .streamdistance = 200.0, .style = MAPICON_LOCAL);
				banks[bnkid][bnk_pickup] = CreateDynamicPickup(1274, 1, banks[bnkid][bnk_X], banks[bnkid][bnk_Y], banks[bnkid][bnk_Z]-0.3);
				new strBank[512];
				format(strBank, 512, ""COL_GREEN"» "COL_YELLOW"Bank (ID: %d) "COL_GREEN"«\n"COL_EASY"Użyj "COL_GREEN"PPM"COL_EASY" lub "COL_GREEN"/bank"COL_EASY" aby skorzystać.", bnkid);
				banks[bnkid][bnk_3dtext] =  CreateDynamic3DTextLabel(strBank, -1, banks[bnkid][bnk_X], banks[bnkid][bnk_Y], banks[bnkid][bnk_Z]-0.1, 3.0);
			}
			i++;
		}
	}
	return 1;
}

stock GetFreeBankID()
{
	for(new b; b < MAX_BANKS; b++)
	{
		if(!banks[b][bnk_id]) return b;
	}
	return -1;
}

stock CountAllBanks()
{
	new wynik;
	for(new b; b < MAX_BANKS; b++)
	{
		if(banks[b][bnk_id]) wynik++;
	}
	return wynik;
}

CMD:bankset(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 2) return 0;
	new bnkid;
	if(sscanf(params,"d", bnkid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /bankset [id banku do USUNIĘCIA (wpisz "COL_RED"-1"COL_GREEN" aby zrobić NOWY"COL_GREY" bank)]");
	if(bnkid < -1)  return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /bankset [id banku do USUNIĘCIA (wpisz "COL_RED"-1"COL_GREEN" aby zrobić NOWY"COL_GREY" bank)]");
	if(bnkid == -1)//tworzenie
	{
		if(CountAllBanks()+1 > MAX_BANKS) return Error(playerid, "Limit bankomatów wyczerpany. Skontaktuj się z programistą.");
		new Float:pPos[3];
		GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
		new new_bnkid = GetFreeBankID();
		banks[new_bnkid][bnk_X] = pPos[0];
		banks[new_bnkid][bnk_Y] = pPos[1];
		banks[new_bnkid][bnk_Z] = pPos[2];
		mq_format("INSERT INTO `banks` VALUES (NULL, '%f', '%f', '%f');", banks[new_bnkid][bnk_X], banks[new_bnkid][bnk_Y], banks[new_bnkid][bnk_Z]);
		new Cache:cache_id = mysql_query(g_SQL, mQuery, true);
		banks[new_bnkid][bnk_id] = cache_insert_id();
		cache_delete(cache_id);
		banks[new_bnkid][bnk_iconid] = CreateDynamicMapIcon(banks[new_bnkid][bnk_X], banks[new_bnkid][bnk_Y], banks[new_bnkid][bnk_Z], 52, 0, .streamdistance = 200.0, .style = MAPICON_LOCAL);
		banks[new_bnkid][bnk_pickup] = CreateDynamicPickup(1274, 1, banks[new_bnkid][bnk_X], banks[new_bnkid][bnk_Y], banks[new_bnkid][bnk_Z]-0.3);
		new strBank[512];
		format(strBank, 512, ""COL_GREEN"» "COL_YELLOW"Bank (ID: %d) "COL_GREEN"«\n"COL_EASY"Użyj "COL_GREEN"PPM"COL_EASY" lub "COL_GREEN"/bank"COL_EASY" aby skorzystać.", new_bnkid);
		banks[new_bnkid][bnk_3dtext] =  CreateDynamic3DTextLabel(strBank, -1, banks[new_bnkid][bnk_X], banks[new_bnkid][bnk_Y], banks[new_bnkid][bnk_Z]-0.1, 3.0);
		Info(playerid, "Bank "COL_GREEN"stworzony!");
	}
	else//usuwanie
	{
		if(banks[bnkid][bnk_id] == 0) return Error(playerid, "Bank o takim ID nie istnieje.");
		mq_format("DELETE FROM `banks` WHERE `id`='%d';", banks[bnkid][bnk_id]);
		mq_send("QDeleteBank");
		DestroyDynamicMapIcon(banks[bnkid][bnk_iconid]);
		DestroyDynamicPickup(banks[bnkid][bnk_pickup]);
		DestroyDynamic3DTextLabel(banks[bnkid][bnk_3dtext]);
		for(new bnk_data:r; r < bnk_data; r++)//czyszczenie zmiennych
		{
			banks[bnkid][r] = 0;
		}
		Info(playerid, "Bank "COL_RED"usunięty!");
	}
	return 1;
}

stock IsPlayerRangeOfBank(playerid)
{
	for(new b; b < MAX_BANKS; b++)
	{
		if(banks[b][bnk_id] == 0) continue;
		if(IsPlayerInRangeOfPoint(playerid, 1.3, banks[b][bnk_X], banks[b][bnk_Y], banks[b][bnk_Z])) return 1;
	}
	return 0;
}

CMD:bank(playerid, params[])
{
	if(IsPlayerRangeOfBank(playerid))
	{
		new strBank[1024];
		if(gracz[playerid][bank_number] == 0)//nie ma konta bankowego
		{
			format(strBank, 1024, ""COL_WHITE"Nie posiadasz konta bankowego, chcesz je założyć?");
			format(strBank, 1024, "%s\n"COL_WHITE"Koszt to "COL_GREEN"5000$"COL_WHITE". Wprowadź "COL_BLUE"swój nick"COL_WHITE" poniżej:", strBank);
			Dialog_Show(playerid, BANK, DIALOG_STYLE_INPUT, "Czy chcesz założyć konto bankowe?", strBank, "Zatwierdź", "Anuluj");
		}
		else//ma konto bankowe
		{
			format(strBank, 1024, ""COL_LIME"$\t"COL_WHITE"Saldo: "COL_LIME"%d$ "COL_WHITE"[Nr. Konta: "COL_GREEN"%d"COL_WHITE"]\t"COL_LIME"$", gracz[playerid][bank_saldo], gracz[playerid][bank_number]);
			format(strBank, 1024, "%s\n"COL_LIME"$\t"COL_BLUE"[-]"COL_EASY"Wykonaj przelew\t"COL_LIME"$", strBank);
			format(strBank, 1024, "%s\n"COL_LIME"$\t"COL_GREEN"[+]"COL_EASY"Wpłać gotówkę\t"COL_LIME"$", strBank);
			format(strBank, 1024, "%s\n"COL_LIME"$\t"COL_RED"[-]"COL_EASY"Wypłać gotówkę\t"COL_LIME"$", strBank);
			//format(strBank, 1024, "%s\n"COL_LIME"$\t"COL_BLUE"Weź kredyt\t"COL_LIME"$", strBank);
			new strTitle[128];
			format(strTitle, 128, ""COL_GREEN"» "COL_WHITE"Konto bankowe: "COL_LIME"%d", gracz[playerid][bank_number]);
			Dialog_Show(playerid, BANK, DIALOG_STYLE_TABLIST, strTitle, strBank, "Zatwierdź", "Anuluj");
		}
	}
	else Error(playerid, "Tutaj nie można użyć tej komendy.");
	return 1;
}

Dialog:BANK(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(gracz[playerid][bank_number] == 0)//nie ma konta bankowego
	{
		if(compare(inputtext, nick(playerid)))
		{
			if(gracz[playerid][PGodz] < 6) return Error(playerid, "Musisz posiadać minimum 6 przegranych godzin.");
			const koszt = 5000;
			if(Money(playerid) < koszt) return LeftNotifyShow(playerid, "error", "Niewystarczajaca ilosc gotowki.", LN_RED);
			TakeMoney(playerid, koszt);
			new first_numbers = MRandRange(100, 999);
			new strGenBankNumber[10];
			format(strGenBankNumber, 10, "%03d%06d", first_numbers, gracz[playerid][UID]);
			new final_bank_number = strval(strGenBankNumber);
			gracz[playerid][bank_number] = final_bank_number;
			gracz[playerid][bank_saldo] = 0;
			mq_format("UPDATE `Konta` SET `bank_number`= '%d', `bank_saldo`='%d' WHERE `id`='%d';", gracz[playerid][bank_number], gracz[playerid][bank_saldo], gracz[playerid][UID]);
			mq_send("QCreateBank");
			LeftNotifyShow(playerid, "Sukces!", "Konto bankowe zostalo zalozone!", LN_GREEN);
			PC_EmulateCommand(playerid, "/bank");
		}
		else LeftNotifyShow(playerid, "error", "Podpis nieprawidlowy.", LN_RED);
	}
	else//ma konto bankowe
	{
		new strInfo[512];
		switch(listitem)
		{
			case 0://historia operacji
			{
				mq_format("SELECT * FROM `LogBank` WHERE `bank_number`='%d' ORDER BY `id` DESC LIMIT 20 ;", gracz[playerid][bank_number]);
				mq_send("ShowBankLogFromDB", "d", playerid);
			}
			case 1://przelew
			{
				format(strInfo, 512, ""COL_BLUE"Wprowadź NUMER konta bankowego:");
				Dialog_Show(playerid, BANKTRANSFER, DIALOG_STYLE_INPUT, "Przelew bankowy", strInfo, "Zatwierdź", "Wróć");
			}
			case 2://wpłacanie gotówki
			{
				format(strInfo, 512, ""COL_EASY"Saldo: "COL_LIME"%d$\n\n"COL_GREEN"Ile chcesz wpłacić?", gracz[playerid][bank_saldo]);
				Dialog_Show(playerid, BANKWPLATA, DIALOG_STYLE_INPUT, "Wpłacanie gotówki", strInfo, "Zatwierdź", "Wróć");
			}
			case 3://wypłacanie gotówki
			{
				format(strInfo, 512, ""COL_EASY"Saldo: "COL_LIME"%d$\n\n"COL_RED"Ile chcesz wypłacić?", gracz[playerid][bank_saldo]);
				Dialog_Show(playerid, BANKWYPLATA, DIALOG_STYLE_INPUT, "Wypłacanie gotówki", strInfo, "Zatwierdź", "Wróć");
			}
			case 4:
			{
				Info(playerid, "Opcja tymczasowo niedostępna.");
			}
		}
	}
	return 1;
}

task ShowBankLogFromDB(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new i;
		new t_timestamp[32], t_data[256];
		new strBankLog[2048];
		format(strBankLog, 2048, "Data\tZdarzenie");
		while(i < rekordy)
		{
			cache_get_value_name(i, "data", t_data, 256);
			cache_get_value_name(i, "timestamp", t_timestamp, 32);
			format(strBankLog, 2048, "%s\n%s\t%s", strBankLog, t_data, t_timestamp);
			i++;
		}
		Dialog_Show(playerid, BANKLOG, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_GREEN"Historia operacji "COL_RED"«•", strBankLog, "Wróć", "");
	}
	else
	{
		LeftNotifyShow(playerid, "error", "Brak historii konta bankowego.", LN_RED);
		PC_EmulateCommand(playerid, "/bank");
	}
	return 1;
}

Dialog:BANKLOG(playerid, response, listitem, inputtext[])
{
	PC_EmulateCommand(playerid, "/bank");
	return 1;
}

Dialog:BANKTRANSFER(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid, "/bank");
	new nrkonta = strval(inputtext);
	if(nrkonta < 100000 || nrkonta > 9999999999)
	{
		LeftNotifyShow(playerid, "error", "Nieprawidlowy numer konta bankowego.", LN_RED);
		PC_EmulateCommand(playerid, "/bank");
		return 1;
	}
	mq_format("SELECT `id`,`Nick` FROM `Konta` WHERE `bank_number`='%d';", nrkonta);
	mq_send("FindBankNumber", "d", playerid);
	SetPVarInt(playerid, "cache_bank_trans_nr", nrkonta);
	return 1;
}

task FindBankNumber(playerid)
{
	mq_getdata();
	if(rekordy == 0)
	{
		LeftNotifyShow(playerid, "error", "Bledny numer konta bankowego.", LN_RED);
		PC_EmulateCommand(playerid, "/bank");
		return 1;
	}
	new t_id, t_nick[32];
	cache_get_value_name_int(0, "id", t_id);
	cache_get_value_name(0, "Nick", t_nick, 32);
	new nrkonta = GetPVarInt(playerid, "cache_bank_trans_nr");
	SetPVarString(playerid, "cache_bank_trans_nick", t_nick);
	if(nrkonta < 100000 || nrkonta > 9999999999)
	{
		LeftNotifyShow(playerid, "error", "Nieprawidlowy numer konta bankowego.", LN_RED);
		PC_EmulateCommand(playerid, "/bank");
		return 1;
	}
	new strTransfer[512];
	format(strTransfer, 512,""COL_LIME"Numer konta poprawny!");
	format(strTransfer, 512,"%s\n"COL_WHITE"Właściciel konta: "COL_GREEN"%s (UID: %d)", strTransfer, t_nick, t_id);
	format(strTransfer, 512,"%s\n"COL_WHITE"Numer konta: "COL_LIME"%d", strTransfer, nrkonta);
	format(strTransfer, 512,"%s\n\n"COL_EASY"Saldo Twojego konta: "COL_GREEN"%d$", strTransfer, gracz[playerid][bank_saldo]);
	format(strTransfer, 512,"%s\n\n"COL_RED"Jaką kwotę chcesz przelać?", strTransfer);
	Dialog_Show(playerid, BANKSTRAFERTWO, DIALOG_STYLE_INPUT, "Wprowadź kwotę", strTransfer, "Zatwierdź", "Wróć");
	return 1;
}

Dialog:BANKSTRAFERTWO(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid, "/bank");
	new kwota = strval(inputtext);
	if(kwota < 100 || kwota > 5000000) return LeftNotifyShow(playerid, "error", "Nieprawidlowa kwota (100$ - 5 000 000$).", LN_RED);
	if(kwota > gracz[playerid][bank_saldo]) return LeftNotifyShow(playerid, "error", "Nie masz tyle pieniedzy na koncie.", LN_RED);
	new nrkonta = GetPVarInt(playerid, "cache_bank_trans_nr");
	gracz[playerid][bank_saldo] -= kwota;
	//aktualizacja targetid
	mq_format("UPDATE `Konta` SET `bank_saldo`=`bank_saldo`+'%d' WHERE `bank_number`='%d';", kwota, nrkonta);
	mq_send("QBankTransfer");
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][bank_number] == nrkonta)
			{
				gracz[p][bank_saldo] += kwota;
				new strBankInfo[144];
				format(strBankInfo, 144, ""COL_LIME"[Przelew Przychodzący]"COL_WHITE" +%d$ - %s [%d]", kwota, nick(playerid), gracz[playerid][bank_number]);
				SendClientMessage(p, -1, strBankInfo);
				PlayerPlaySound(p, 4201, 0, 0, 0);
				break;
			}
		}
	}
	new target_nick[32];
	GetPVarString(playerid, "cache_bank_trans_nick", target_nick, 32);
	//aktualizacja playerid
	mq_format("UPDATE `Konta` SET `bank_saldo`='%d' WHERE `id`='%d';", gracz[playerid][bank_saldo], gracz[playerid][UID]);
	mq_send("QBankTransfer2");
	//aktualizacja logów playerid
	new strBnkLog[256];
	format(strBnkLog, 256, "[Przelew] Na konto: %d[%s] I Kwota: %d", nrkonta, target_nick, kwota);
	mq_format("INSERT INTO `LogBank` (`bank_number`, `data`) VALUES ('%d', '%s');", gracz[playerid][bank_number], strBnkLog);
	mq_send("QBankLog");
	//aktualizacja logów targetid
	format(strBnkLog, 256, "[Przelew] Z konta: %d[%s] I Kwota: %d", gracz[playerid][bank_number], nick(playerid, true), kwota);
	mq_format("INSERT INTO `LogBank` (`bank_number`, `data`) VALUES ('%d', '%s');", nrkonta, strBnkLog);
	mq_send("QBankLog");
	//
	LeftNotifyShow(playerid, "Sukces!", "Przelew wykonany! Historie konta bankowego mozesz znalezc pod /bank -> [wybierz saldo (1 pozycja)]", LN_GREEN, 25);
	PC_EmulateCommand(playerid, "/bank");
	return 1;
}
//WPŁATA
Dialog:BANKWPLATA(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid, "/bank");
	new value = strval(inputtext);
	if(value < 1 || value > 5000000) return LeftNotifyShow(playerid, "error", "Nieprawidlowa kwota (1$ - 5 000 000$).", LN_RED);
	if(value > Money(playerid)) return LeftNotifyShow(playerid, "error", "Nie posiadasz takiej gotowki przy sobie.", LN_RED);
	TakeMoney(playerid, value);
	gracz[playerid][bank_saldo] += value;
	//aktualizacja playerid
	mq_format("UPDATE `Konta` SET `bank_saldo`='%d' WHERE `id`='%d';", gracz[playerid][bank_saldo], gracz[playerid][UID]);
	mq_send("QBankWplata");
	//aktualizacja logów playerid
	new strBnkLog[256];
	format(strBnkLog, 256, "[Wplata] Kwota: %d$", value);
	mq_format("INSERT INTO `LogBank` (`bank_number`, `data`) VALUES ('%d', '%s');", gracz[playerid][bank_number], strBnkLog);
	mq_send("QBankLog");
	//
	LeftNotifyShow(playerid, "Sukces!", "Wplacono gotowke!", LN_GREEN);
	PC_EmulateCommand(playerid, "/bank");
	return 1;
}
//WYPŁATA
Dialog:BANKWYPLATA(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid, "/bank");
	new value = strval(inputtext);
	if(value < 1 || value > 5000000) return LeftNotifyShow(playerid, "error", "Nieprawidlowa kwota (1$ - 5 000 000$).", LN_RED);
	if(value > gracz[playerid][bank_saldo]) return LeftNotifyShow(playerid, "error", "Nie masz tyle pieniedzy na koncie.", LN_RED);
	GiveMoney(playerid, value);
	gracz[playerid][bank_saldo] -= value;
	//aktualizacja playerid
	mq_format("UPDATE `Konta` SET `bank_saldo`='%d' WHERE `id`='%d';", gracz[playerid][bank_saldo], gracz[playerid][UID]);
	mq_send("QBankWyplata");
	//aktualizacja logów playerid
	new strBnkLog[256];
	format(strBnkLog, 256, "[Wyplata] Kwota: %d$", value);
	mq_format("INSERT INTO `LogBank` (`bank_number`, `data`) VALUES ('%d', '%s');", gracz[playerid][bank_number], strBnkLog);
	mq_send("QBankLog");
	//
	LeftNotifyShow(playerid, "Sukces!", "Wyplacono gotowke!", LN_GREEN);
	PC_EmulateCommand(playerid, "/bank");
	return 1;
}
//*****************************************************************************************************************************SKRYPT WĘDKOWANIA

stock Init_Fishing()
{
	for(new f; f < sizeof(fishing_pos); f++)
	{
		CreateDynamic3DTextLabel("« "COL_BLUE"WĘDKOWANIE "COL_GREEN"»\n"COL_RED"• "COL_WHITE"Wciśnij "COL_GREEN"klawisz "COL_RED"PPM"COL_WHITE" aby rozpocząć wędkowanie. "COL_RED"•", 0x009933FF, fishing_pos[f][0], fishing_pos[f][1], fishing_pos[f][2], 15.0);
		CreateDynamicMapIcon(fishing_pos[f][0], fishing_pos[f][1], fishing_pos[f][2], 9, -1, 0, 0, -1, 450.0, MAPICON_GLOBAL);
	}
	CreateActor(34,XYZ_SELLFISH,142.8345); // handlarz rybek
	CreateDynamicMapIcon(XYZ_SELLFISH, 0, 0x0000FFFF, 0, 0, -1, 450.0, MAPICON_GLOBAL);
	CreateDynamic3DTextLabel("« "COL_BLUE"HANDLARZ RYB "COL_GREEN"»\n"COL_RED"• "COL_WHITE"Wciśnij "COL_GREEN"klawisz "COL_RED"PPM"COL_WHITE" aby sprzedać ryby. "COL_RED"•", 0x009933FF, XYZ_SELLFISH, 15.0);
	return 1;
}

stock StartFish(playerid)
{
	if(gracz[playerid][bw] > 0) return -2;
	if(GetPVarInt(playerid, "RateFish") != 0) return -1;//podczas wedkowania
	RemovePlayerAttachedObject(playerid, ATTACH_SLOT7);
	SetPlayerAttachedObject(playerid, ATTACH_SLOT7,18632,6,0.079376,0.037070,0.007706,181.482910,0.000000,0.000000,1.000000,1.000000,1.000000);
	TogglePlayerControllable(playerid, 0);
	SetCameraBehindPlayer(playerid);
	SetPVarInt(playerid, "RateFish", 10);
	ApplyAnimation(playerid,"SWORD","sword_block",50.0,0,1,0,1,1);
	//ApplyAnimation(playerid, "SAMP", "FishingIdle", 4.1, 0, 1, 1, 1, 1);
	SetTimerEx("AnimFishFixer", 1000, false, "d", playerid);
	SetTimerEx("ProcedureFish", 2000, false, "d", playerid);
	SetPlayerArmedWeapon(playerid, 0);
	GameTextForPlayer(playerid, "~b~ZARZUCANIE WEDKI...",3000,5);
	return 1;
}
forward AnimFishFixer(playerid);
public AnimFishFixer(playerid)
{
	if(IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_SLOT7)) ApplyAnimation(playerid,"SWORD","sword_block",50.0,0,1,0,1,1);
	//ApplyAnimation(playerid, "SAMP", "FishingIdle", 4.1, 0, 1, 1, 1, 1);
}
stock IsPlayerInFishingPoint(playerid)
{
	for(new f; f < sizeof(fishing_pos); f++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 3.0, fishing_pos[f][0], fishing_pos[f][1], fishing_pos[f][2])) return 1;
	}
	return 0;
}
forward ProcedureFish(playerid);
public ProcedureFish(playerid)
{
	if(!IsPlayerConnected(playerid)) return 1;
	if(GetPVarInt(playerid, "ClickFishGood") == 4)
	{
		SetPVarInt(playerid, "RateFish", 0);
		SetPVarInt(playerid, "ClickFish", 0);
		SetPVarInt(playerid, "ClickFishGood", 0);
		SetPlayerSkin(playerid, GetPlayerSkin(playerid));
		TogglePlayerControllable(playerid, 1);
		RemovePlayerAttachedObject(playerid,ATTACH_SLOT7);
		ClearAnimations(playerid, 1);
		CreateItemForPlayer(playerid, 80, 1);
		LeftNotifyShow(playerid, "Sukces!", "~g~Gratulacje!~w~ Zlowiles rybe!", LN_GREEN);
		PC_EmulateCommand(playerid, "/me złowił/a rybę.");
		return 1;
	}
	if(GetPVarInt(playerid, "RateFish") == 0)
	{
		if(IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_SLOT7))
		{
			LeftNotifyShow(playerid, "info", "Polow ryb ~r~zakonczony~w~. Ryba ~r~nie~w~ polknela haczyka.");
			SetPVarInt(playerid, "RateFish", 0);
			SetPVarInt(playerid, "ClickFish", 0);
			SetPVarInt(playerid, "ClickFishGood", 0);
			SetPlayerSkin(playerid, GetPlayerSkin(playerid));
			TogglePlayerControllable(playerid, 1);
			RemovePlayerAttachedObject(playerid,ATTACH_SLOT7);
			ClearAnimations(playerid, 1);
		}
		return 1;
	}
	new fstr[64];
	format(fstr, sizeof(fstr), "~g~LOWIENIE RYB - ~b~%d/4", GetPVarInt(playerid, "ClickFishGood"));
	SetPVarInt(playerid, "ClickFish", 0);
	if(GetPVarInt(playerid, "RateFish") < 9)
	{
		switch(random(7)+1)
		{
			case 1:
			{
				SetPVarInt(playerid, "ClickFish", 1);
				format(fstr, sizeof(fstr), "~r~WCISNIJ: ~y~LPM~w~!");
				SetPVarInt(playerid, "RateFish", GetPVarInt(playerid, "RateFish")+1);
			}
			case 2:
			{
				SetPVarInt(playerid, "ClickFish", 0);
				format(fstr, sizeof(fstr), "~g~LOWIENIE RYB - ~b~%d/4", GetPVarInt(playerid, "ClickFishGood"));
			}
			case 3:
			{
				SetPVarInt(playerid, "ClickFish", 2);
				format(fstr, sizeof(fstr), "~r~WCISNIJ: ~y~PPM~w~!");
				SetPVarInt(playerid, "RateFish", GetPVarInt(playerid, "RateFish")+1);
			}
			case 4:
			{
				SetPVarInt(playerid, "ClickFish", 0);
				format(fstr, sizeof(fstr), "~g~LOWIENIE RYB - ~b~%d/4", GetPVarInt(playerid, "ClickFishGood"));
			}
			default:
			{
				SetPVarInt(playerid, "ClickFish", 0);
				format(fstr, sizeof(fstr), "~g~LOWIENIE RYB - ~b~%d/4", GetPVarInt(playerid, "ClickFishGood"));
			}
		}
	}
	if(GetPVarInt(playerid, "RateFish") > 10)
	{
		format(fstr, sizeof(fstr), "~g~LOWIENIE RYB - ~b~%d/4", GetPVarInt(playerid, "ClickFishGood"));
		SetPVarInt(playerid, "ClickFish", 0);
	}
	GameTextForPlayer(playerid, fstr,2000,5);
	SetPVarInt(playerid, "RateFish", GetPVarInt(playerid, "RateFish")-1);
	SetTimerEx("ProcedureFish", 2000, false, "d", playerid);
	return 1;
}
stock FISHSYS_OnPlayerKeyStateChange(playerid, newkeys)
{
	if(GetPVarInt(playerid, "RateFish") == 0) return 1;
	new bool:clicked = false;
	if(newkeys == KEY_FIRE)//LPM
	{
		
		if(GetPVarInt(playerid, "ClickFish") == 1)
		{
			SetPVarInt(playerid, "ClickFish", 0);
			SetPVarInt(playerid, "ClickFishGood", GetPVarInt(playerid, "ClickFishGood")+1);
			SetPVarInt(playerid, "RateFish", GetPVarInt(playerid, "RateFish")+1);
			new fstr[64];
			format(fstr, sizeof(fstr), "~g~DOBRZE! - ~b~%d/4", GetPVarInt(playerid, "ClickFishGood"));
			GameTextForPlayer(playerid, fstr,2000,5);
		} 
		else 
		{
			SetPVarInt(playerid, "RateFish", 0);
			SetPVarInt(playerid, "ClickFish", 0);
			SetPVarInt(playerid, "ClickFishGood", 0);
			SetPlayerSkin(playerid, GetPlayerSkin(playerid));
			RemovePlayerAttachedObject(playerid,ATTACH_SLOT7);
			TogglePlayerControllable(playerid, 1);
			ClearAnimations(playerid, 1);
			LeftNotifyShow(playerid, "error", "Lowienie ryb ~r~przerwane~w~. ~r~Niepoprawny~w~ przycisk wcisnales.");
			Spam(playerid, SPAM_STARTFISH, 2, false);
		}
		clicked = true;
	}
	if(clicked == true) return 1;
	if(newkeys == 128)//PPM
	{
		if(GetPVarInt(playerid, "ClickFish") == 2)
		{
			SetPVarInt(playerid, "ClickFish", 0);
			SetPVarInt(playerid, "ClickFishGood", GetPVarInt(playerid, "ClickFishGood")+1);
			SetPVarInt(playerid, "RateFish", GetPVarInt(playerid, "RateFish")+1);
			new fstr[64];
			format(fstr, sizeof(fstr), "~g~DOBRZE! - ~b~%d/4", GetPVarInt(playerid, "ClickFishGood"));
			GameTextForPlayer(playerid, fstr,2000,5);
		} 
		else 
		{
			SetPVarInt(playerid, "RateFish", 0);
			SetPVarInt(playerid, "ClickFish", 0);
			SetPVarInt(playerid, "ClickFishGood", 0);
			SetPlayerSkin(playerid, GetPlayerSkin(playerid));
			RemovePlayerAttachedObject(playerid,ATTACH_SLOT7);
			TogglePlayerControllable(playerid, 1);
			SetPVarInt(playerid, "ClickFish", 0);
			ClearAnimations(playerid, 1);
			LeftNotifyShow(playerid, "error", "Lowienie ryb ~r~przerwane~w~. ~r~Niepoprawny~w~ przycisk wcisnales.");
			Spam(playerid, SPAM_STARTFISH, 2, false);
		}
	}
	return 1;
}

#define PRICE_FISH0 400
#define PRICE_FISH1 1250
stock SellFish(playerid)
{
	new surowa_ryba_ilosc = GetItemValueForPlayer(playerid, 80);
	new upieczona_ryba_ilosc = GetItemValueForPlayer(playerid, 81);
	if(surowa_ryba_ilosc+upieczona_ryba_ilosc == 0) return Error(playerid, "Nie posiadasz żadnych ryb.");
	new cena_ryb = (surowa_ryba_ilosc*PRICE_FISH0)+(upieczona_ryba_ilosc*PRICE_FISH1);
	new strSellFish[1024];
	format(strSellFish, 1024, ""COL_WHITE"Handlarz kupi od Ciebie wszystkie ryby z Twojego ekwipunku!");
	format(strSellFish, 1024, "%s\n"COL_WHITE"Surowa ryba: "COL_GREEN"%d$ za sztukę.", strSellFish, PRICE_FISH0);
	format(strSellFish, 1024, "%s\n"COL_WHITE"Upieczona ryba: "COL_GREEN"%d$ za sztukę.", strSellFish, PRICE_FISH1);
	format(strSellFish, 1024, "%s\n"COL_WHITE"Posiadasz "COL_EASY"%d"COL_WHITE" ryb surowych, oraz "COL_ORANGE"%d"COL_WHITE" ryb upieczonych.", strSellFish, surowa_ryba_ilosc, upieczona_ryba_ilosc);
	format(strSellFish, 1024, "%s\n"COL_WHITE"Zawartość ryb w Twoim ekwipunku została wyceniona na: "COL_LIME"%d$", strSellFish, cena_ryb);
	format(strSellFish, 1024, "%s\n"COL_RED"Czy chcesz je sprzedać?", strSellFish);
	Dialog_Show(playerid, SELLFISH, DIALOG_STYLE_MSGBOX, "Sprzedaż ryb", strSellFish, "Sprzedaj", "Anuluj");
	return 1;
}

Dialog:SELLFISH(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new surowa_ryba_ilosc = GetItemValueForPlayer(playerid, 80);
	new upieczona_ryba_ilosc = GetItemValueForPlayer(playerid, 81);
	if(surowa_ryba_ilosc+upieczona_ryba_ilosc == 0) return Error(playerid, "Nie posiadasz żadnych ryb.");
	new cena_ryb = (surowa_ryba_ilosc*PRICE_FISH0)+(upieczona_ryba_ilosc*PRICE_FISH1);
	if(surowa_ryba_ilosc > 0) RemoveItemFromPlayer(playerid, 80, surowa_ryba_ilosc);
	if(upieczona_ryba_ilosc > 0) RemoveItemFromPlayer(playerid, 81, upieczona_ryba_ilosc);
	GiveMoney(playerid, cena_ryb);
	SendClientMessageEx(playerid, 0x00FF00FF, "Otrzymujesz "COL_LIME"%d${00FF00} od handlarza.", cena_ryb);
	return 1;
}