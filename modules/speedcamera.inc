#define MAX_SPEEDCAMS 100
#define SPEEDCAM_BASEPENALTY 500
#define SPEEDCAM_ADDKMPENALTY 10

enum scm_data
{
	scm_id,
	scm_maxspeed,
	Float:scm_oX,
	Float:scm_oY,
	Float:scm_oZ,
	Float:scm_oRZ,
	Float:scm_checkX,
	Float:scm_checkY,
	Float:scm_checkZ,
	scm_objectid,
	Text3D:scm_text3d
};

new speedcams[MAX_SPEEDCAMS][scm_data];

stock Init_SpeedCams()
{
	SetTimer("Process_SpeedCams", 300, true);
	mq_format("SELECT * FROM `speedcams`;");
	mq_send("LoadSpeedCamsFromDB");
	return 1;
}

task LoadSpeedCamsFromDB()
{
	mq_getdata();
	if(rekordy)
	{
		new i;
		new scid; 
		while(i < rekordy)
		{
			scid = GetFreeSpeedCamID();
			cache_get_value_name_int(i, "id", 			speedcams[scid][scm_id]);
			cache_get_value_name_int(i, "maxspeed", 			speedcams[scid][scm_maxspeed]);
			cache_get_value_name_float(i, "oX", 			speedcams[scid][scm_oX]);
			cache_get_value_name_float(i, "oY", 			speedcams[scid][scm_oY]);
			cache_get_value_name_float(i, "oZ", 			speedcams[scid][scm_oZ]);
			cache_get_value_name_float(i, "oRZ", 			speedcams[scid][scm_oRZ]);
			cache_get_value_name_float(i, "checkX", 			speedcams[scid][scm_checkX]);
			cache_get_value_name_float(i, "checkY", 			speedcams[scid][scm_checkY]);
			cache_get_value_name_float(i, "checkZ", 			speedcams[scid][scm_checkZ]);
			speedcams[scid][scm_objectid] = CreateDynamicObject(18880, speedcams[scid][scm_oX], speedcams[scid][scm_oY], speedcams[scid][scm_oZ]-2.0, 0.0, 0.0, speedcams[scid][scm_oRZ]);
			new scmString[512];
			if(speedcams[scid][scm_maxspeed] > 0) format(scmString, 512, ""COL_EASY"»» FOTORADAR (ID: %d) ««\n"COL_WHITE"Limit: "COL_ORANGE"%d km/h", scid, speedcams[scid][scm_maxspeed]);
			else format(scmString, 512, ""COL_EASY"»» FOTORADAR (ID: %d) ««\n"COL_WHITE"Limit: "COL_GREEN"BRAK", scid, speedcams[scid][scm_maxspeed]);
			speedcams[scid][scm_text3d] = CreateDynamic3DTextLabel(scmString, -1, speedcams[scid][scm_oX], speedcams[scid][scm_oY], speedcams[scid][scm_oZ]+3.0, 65.0);
			i++;
		}
	}
	return 1;
}

stock GetFreeSpeedCamID()
{
	for(new s; s < MAX_SPEEDCAMS; s++)
	{
		if(!speedcams[s][scm_id]) return s;
	}
	return 0;
}

stock CountAllSpeedCams()
{
	new wynik;
	for(new s; s < MAX_SPEEDCAMS; s++)
	{
		if(speedcams[s][scm_id]) wynik++;
	}
	return wynik;
}

CMD:speedcam(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 2) return 0;
	new scmid;
	if(sscanf(params,"d", scmid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /speedcam [id fotoradaru (wpisz "COL_RED"-1"COL_GREEN" aby zrobić NOWY"COL_GREY" fotoradar)]");
	if(scmid < -1)  return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /speedcam [id fotoradaru (wpisz "COL_RED"-1"COL_GREEN" aby zrobić NOWY"COL_GREY" fotoradar)]"); 
	if(scmid == -1)
	{
		if(CountAllSpeedCams()+1 > MAX_SPEEDCAMS) return Error(playerid, "Limit fotoradarów wyczerpany. Skontaktuj się z programistą.");
		new new_scid = GetFreeSpeedCamID();
		speedcams[new_scid][scm_maxspeed] = 0;
		speedcams[new_scid][scm_oX] = gracz[playerid][PosX];
		speedcams[new_scid][scm_oY] = gracz[playerid][PosY];
		speedcams[new_scid][scm_oZ] = gracz[playerid][PosZ];
		speedcams[new_scid][scm_checkX] = gracz[playerid][PosX];
		speedcams[new_scid][scm_checkY] = gracz[playerid][PosY];
		speedcams[new_scid][scm_checkZ] = gracz[playerid][PosZ];
		new Float:pAngle;
		GetPlayerFacingAngle(playerid, pAngle);
		speedcams[new_scid][scm_oRZ] = pAngle+180.0;
		SetPlayerPos(playerid, gracz[playerid][PosX]+1.0, gracz[playerid][PosY], gracz[playerid][PosZ]);
		mq_format("INSERT INTO `speedcams` VALUES (NULL, '0', '%f', '%f', '%f', '%f', '%f', '%f', '%f');", speedcams[new_scid][scm_oX], speedcams[new_scid][scm_oY], speedcams[new_scid][scm_oZ], speedcams[new_scid][scm_oRZ], speedcams[new_scid][scm_checkX], speedcams[new_scid][scm_checkY], speedcams[new_scid][scm_checkZ]);
		new Cache:cache_id = mysql_query(g_SQL, mQuery, true);
		speedcams[new_scid][scm_id] = cache_insert_id();
		cache_delete(cache_id);
		speedcams[new_scid][scm_objectid] = CreateDynamicObject(18880, speedcams[new_scid][scm_oX], speedcams[new_scid][scm_oY], speedcams[new_scid][scm_oZ]-2.0, 0.0, 0.0, speedcams[new_scid][scm_oRZ]);
		new scmString[512];
		if(speedcams[new_scid][scm_maxspeed] > 0) format(scmString, 512, ""COL_EASY"»» FOTORADAR (ID: %d) ««\n"COL_WHITE"Limit: "COL_ORANGE"%d km/h", new_scid, speedcams[new_scid][scm_maxspeed]);
		else format(scmString, 512, ""COL_EASY"»» FOTORADAR (ID: %d) ««\n"COL_WHITE"Limit: "COL_GREEN"BRAK", new_scid, speedcams[new_scid][scm_maxspeed]);
		speedcams[new_scid][scm_text3d] = CreateDynamic3DTextLabel(scmString, -1, speedcams[new_scid][scm_oX], speedcams[new_scid][scm_oY], speedcams[new_scid][scm_oZ]+3.0, 65.0);
		Info(playerid, "Fotoradar stworzony! Użyj /speedcam [id fotoradaru] aby go skonfigurować.");
	}
	else//operacje na istniejącym fotoradarze
	{
		if(MAX_SPEEDCAMS-1 < scmid) return Error(playerid, "Fotoradar o takim ID nie istnieje.");
		if(speedcams[scmid][scm_id] == 0) return Error(playerid, "Fotoradar o takim ID nie istnieje.");
		if(!IsPlayerInRangeOfPoint(playerid, 70.0, speedcams[scmid][scm_oX], speedcams[scmid][scm_oY], speedcams[scmid][scm_oZ])) return Error(playerid, "Jesteś za daleko od fotoradaru.");
		new strScmMenu[512];
		format(strScmMenu, 512, "Opcja\t[info]", strScmMenu);
		format(strScmMenu, 512, "%s\n"COL_EASY"Aktualizuj pozycje fotoradaru\t"COL_GREY"[obiekt fotoradaru]", strScmMenu);
		format(strScmMenu, 512, "%s\n"COL_EASY"Ustaw punkt pomiarowy\t"COL_GREY"[miejsce na jezdni (środek)]", strScmMenu);
		format(strScmMenu, 512, "%s\n"COL_EASY"Limit prędkości\t"COL_GREY"[%d km/h (0 - wyłączony fotoradar)]", strScmMenu, speedcams[scmid][scm_maxspeed]);
		format(strScmMenu, 512, "%s\n"COL_RED"Usuń fotoradar\t"COL_GREY"[miejsce na jezdni]", strScmMenu);
		new strTitle[128];
		format(strTitle, 128, "Fotoradar ID: "COL_RED"%d", scmid);
		SetPVarInt(playerid, "cache_scmid", scmid);
		Dialog_Show(playerid, SPEEDCAMMENU, DIALOG_STYLE_TABLIST_HEADERS, strTitle, strScmMenu, "Wybierz", "Anuluj");
	}
	return 1;
}

Dialog:SPEEDCAMMENU(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new scmid = GetPVarInt(playerid, "cache_scmid");
	if(speedcams[scmid][scm_id] == 0) return Error(playerid, "Fotoradar o takim ID nie istnieje.");
	if(!IsPlayerInRangeOfPoint(playerid, 70.0, speedcams[scmid][scm_oX], speedcams[scmid][scm_oY], speedcams[scmid][scm_oZ])) return Error(playerid, "Jesteś za daleko od fotoradaru.");
	switch(listitem)
	{
		case 0://aktualizacja pozycji fotoradaru
		{
			if(!IsPlayerInRangeOfPoint(playerid, 70.0, speedcams[scmid][scm_checkX], speedcams[scmid][scm_checkY], speedcams[scmid][scm_checkZ])) return Error(playerid, "Jesteś za daleko od punktu pomiarowego.");
			if(IsValidDynamicObject(speedcams[scmid][scm_objectid]) && IsValidDynamic3DTextLabel(speedcams[scmid][scm_text3d]))
			{
				DestroyDynamicObject(speedcams[scmid][scm_objectid]);
				DestroyDynamic3DTextLabel(speedcams[scmid][scm_text3d]);
				speedcams[scmid][scm_oX] = gracz[playerid][PosX];
				speedcams[scmid][scm_oY] = gracz[playerid][PosY];
				speedcams[scmid][scm_oZ] = gracz[playerid][PosZ];
				new Float:pAngle;
				GetPlayerFacingAngle(playerid, pAngle);
				speedcams[scmid][scm_oRZ] = pAngle+180.0;
				SetPlayerPos(playerid, gracz[playerid][PosX]+1.0, gracz[playerid][PosY], gracz[playerid][PosZ]);
				speedcams[scmid][scm_objectid] = CreateDynamicObject(18880, speedcams[scmid][scm_oX], speedcams[scmid][scm_oY], speedcams[scmid][scm_oZ]-2.0, 0.0, 0.0, speedcams[scmid][scm_oRZ]);
				new scmString[512];
				if(speedcams[scmid][scm_maxspeed] > 0) format(scmString, 512, ""COL_EASY"»» FOTORADAR (ID: %d) ««\n"COL_WHITE"Limit: "COL_ORANGE"%d km/h", scmid, speedcams[scmid][scm_maxspeed]);
				else format(scmString, 512, ""COL_EASY"»» FOTORADAR (ID: %d) ««\n"COL_WHITE"Limit: "COL_GREEN"BRAK", scmid, speedcams[scmid][scm_maxspeed]);
				speedcams[scmid][scm_text3d] = CreateDynamic3DTextLabel(scmString, -1, speedcams[scmid][scm_oX], speedcams[scmid][scm_oY], speedcams[scmid][scm_oZ]+3.0, 65.0);
				mq_format("UPDATE `speedcams` SET `oX`='%f', `oY`='%f', `oZ`='%f', `oRZ`='%f' WHERE `id`='%d';", speedcams[scmid][scm_oX], speedcams[scmid][scm_oY], speedcams[scmid][scm_oZ], speedcams[scmid][scm_oRZ], speedcams[scmid][scm_id]);
				mq_send("QUpdateSCM");
				Info(playerid, "Fotoradar przestawiony.");
				//-powrót do menu
				new strCommand[64];
				format(strCommand, 64, "/speedcam %d", scmid);
				PC_EmulateCommand(playerid, strCommand);
				//-
			} 
			else Error(playerid, "Wystąpił nieoczekiwany błąd.");
		}
		case 1://ustaw punkt pomiarowy
		{
			speedcams[scmid][scm_checkX] = gracz[playerid][PosX];
			speedcams[scmid][scm_checkY] = gracz[playerid][PosY];
			speedcams[scmid][scm_checkZ] = gracz[playerid][PosZ];
			mq_format("UPDATE `speedcams` SET `checkX`='%f', `checkY`='%f', `checkZ`='%f' WHERE `id`='%d';", speedcams[scmid][scm_checkX], speedcams[scmid][scm_checkY], speedcams[scmid][scm_checkZ], speedcams[scmid][scm_id]);
			mq_send("QUpdateSCM");
			Info(playerid, "Punkt pomiarowy ustawiony.");
			//-powrót do menu
			new strCommand[64];
			format(strCommand, 64, "/speedcam %d", scmid);
			PC_EmulateCommand(playerid, strCommand);
			//-
		}
		case 2://limit predkosci
		{
			Dialog_Show(playerid, SCMSETSPEED, DIALOG_STYLE_INPUT, "Wprowadź prędkość km/h", "Podaj prędkość km/h (0-300 km/h):", "Zatwierdz", "Anuluj");
		}
		case 3://usun fotoradar
		{
			if(IsValidDynamicObject(speedcams[scmid][scm_objectid]) && IsValidDynamic3DTextLabel(speedcams[scmid][scm_text3d]))
			{
				DestroyDynamicObject(speedcams[scmid][scm_objectid]);
				DestroyDynamic3DTextLabel(speedcams[scmid][scm_text3d]);
			}
			mq_format("DELETE FROM `speedcams` WHERE `id`='%d';", speedcams[scmid][scm_id]);
			mq_send("QDeleteSCM");
			for(new scm_data:r; r < scm_data; r++)//czyszczenie zmiennych
			{
				speedcams[scmid][r] = 0;
			}
			Info(playerid, ""COL_RED"Fotoradar usunięty.");
		}
	}
	return 1;
}

Dialog:SCMSETSPEED(playerid, response, listitem, inputtext[])
{
	new scmid = GetPVarInt(playerid, "cache_scmid");
	if(!response)
	{	
		//-powrót do menu
		new strCommand[64];
		format(strCommand, 64, "/speedcam %d", scmid);
		PC_EmulateCommand(playerid, strCommand);
		//-
		return 1;
	}
	if(speedcams[scmid][scm_id] == 0) return Error(playerid, "Fotoradar o takim ID nie istnieje.");
	if(!IsPlayerInRangeOfPoint(playerid, 70.0, speedcams[scmid][scm_oX], speedcams[scmid][scm_oY], speedcams[scmid][scm_oZ])) return Error(playerid, "Jesteś za daleko od fotoradaru.");
	new value = strval(inputtext);
	if(value < 0) return Error(playerid, "Przedział: 0-300km/h");
	if(value > 300) return Error(playerid, "Przedział: 0-300km/h");
	speedcams[scmid][scm_maxspeed] = value;
	new scmString[512];
	if(speedcams[scmid][scm_maxspeed] > 0) format(scmString, 512, ""COL_EASY"»» FOTORADAR (ID: %d) ««\n"COL_WHITE"Limit: "COL_ORANGE"%d km/h", scmid, speedcams[scmid][scm_maxspeed]);
	else format(scmString, 512, ""COL_EASY"»» FOTORADAR (ID: %d) ««\n"COL_WHITE"Limit: "COL_GREEN"BRAK", scmid, speedcams[scmid][scm_maxspeed]);
	if(IsValidDynamic3DTextLabel(speedcams[scmid][scm_text3d])) UpdateDynamic3DTextLabelText(speedcams[scmid][scm_text3d], -1, scmString);
	mq_format("UPDATE `speedcams` SET `maxspeed`='%d' WHERE `id`='%d';", speedcams[scmid][scm_maxspeed], speedcams[scmid][scm_id]);
	mq_send("QUpdateSCMSpeed");
	Info(playerid, "Limit prędkości fotoradaru zmieniony.");
	//-powrót do menu
	new strCommand[64];
	format(strCommand, 64, "/speedcam %d", scmid);
	PC_EmulateCommand(playerid, strCommand);
	//-
	return 1;
}

stock GetNearestSpeedCam(playerid)
{
	new Float:dist = 200.0;
	new Float:tmpDist;
	new speedcameraid = -1;
	for(new f; f < MAX_SPEEDCAMS; f++)
	{
		if(speedcams[f][scm_id])
		{
			tmpDist = GetDistanceBetweenPoints(gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], speedcams[f][scm_checkX], speedcams[f][scm_checkY], speedcams[f][scm_checkZ]);
			if(tmpDist < dist)
			{
				dist = tmpDist;
				speedcameraid = f;
			}
		}
	}
	return speedcameraid;
}

task Process_SpeedCams()
{
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][opu_vehicleid] == 0)
			{
				TextDrawSpeedLimit(p, 0);
				continue;
			}
			if(gracz[p][photo_speed_timestamp]+5 > serwer[time_timestamp]) continue;
			if(GetPlayerVehicleSeat(p) != 0) continue;
			new f = GetNearestSpeedCam(p);
			if(f == -1) 
			{
				TextDrawSpeedLimit(p, 0);
				continue;
			}
			if(IsPlayerOnDutyFraction(p)) continue;
			if(gracz[p][admin_duty] > 0) continue;
			if(gracz[p][event_saved]) continue;
			if(gracz[p][ps_score] < 30) continue;
			if(speedcams[f][scm_maxspeed] > 0)
			{
				if(gracz[p][opu_speed] > speedcams[f][scm_maxspeed]+10)//przekracza predkość któregoś fotoradaru
				{
					if(IsPlayerInRangeOfPoint(p, 11.0, speedcams[f][scm_checkX], speedcams[f][scm_checkY], speedcams[f][scm_checkZ]))//jest w punkcie pomiarowym
					{
						gracz[p][photo_speed_timestamp] = serwer[time_timestamp];
						new overspeed = gracz[p][opu_speed]-speedcams[f][scm_maxspeed];
						new penalty_price = SPEEDCAM_BASEPENALTY+(SPEEDCAM_ADDKMPENALTY*overspeed);
						SetTimerEx("HideScreenFilter", 1500, false, "d", p);
						ShowScreenFilter(p, 0xFFFFFF80);
						new strInfo[512];
						if(Money(p) > penalty_price)
						{
							TakeMoney(p, penalty_price);
							format(strInfo, 512, "Otrzymales mandat ~y~%d$~w~ za przekroczenie predkosci. Szczegoly: ~n~- koszt: %d$.~n~- przekroczenie: %d km/h.~n~- twoja predkosc: %d km/h~n~- dopuszczalna predkosc: ~y~%d km/h~w~.~n~- platnosc: ~y~gotowka~w~", penalty_price, penalty_price, overspeed, gracz[p][opu_speed], speedcams[f][scm_maxspeed]);
						}
						else if(gracz[p][bank_number] != 0 && gracz[p][bank_saldo] > penalty_price)
						{
							//aktualizacja playerid
							gracz[p][bank_saldo] -= penalty_price;
							mq_format("UPDATE `Konta` SET `bank_saldo`='%d' WHERE `id`='%d';", gracz[p][bank_saldo], gracz[p][UID]);
							mq_send("QBankUpSaldo");
							format(strInfo, 512, "Otrzymales mandat ~y~%d$~w~ za przekroczenie predkosci. Szczegoly: ~n~- koszt: %d$.~n~- przekroczenie: %d km/h.~n~- twoja predkosc: %d km/h~n~- dopuszczalna predkosc: ~y~%d km/h~w~.~n~- platnosc: ~y~konto bankowe~w~", penalty_price, penalty_price, overspeed, gracz[p][opu_speed], speedcams[f][scm_maxspeed]);
						}
						else
						{
							format(strInfo, 512, "Niezaplacony mandat (%d$), powod: fotoradar (+%d km/h)", penalty_price, overspeed);
							KartotekaDodajWpis(p, p, strInfo);
							format(strInfo, 512, "Otrzymales wpis do kartoteki, poniewaz nie zaplaciles mandatu wystawionego przez fotoradar. Szczegoly: ~n~- koszt: %d$.~n~- przekroczenie: %d km/h.~n~- twoja predkosc: %d km/h~n~- dopuszczalna predkosc: ~y~%d km/h~w~.", penalty_price, overspeed, gracz[p][opu_speed], speedcams[f][scm_maxspeed]);
						}
						LeftNotifyShow(p, "Fotoradar", strInfo, LN_RED, 20);
					}
				}
				//wyświetlanie ostrzeżenia
				if(IsPlayerInRangeOfPoint(p, 130.0, speedcams[f][scm_checkX], speedcams[f][scm_checkY], speedcams[f][scm_checkZ])) TextDrawSpeedLimit(p, speedcams[f][scm_maxspeed]);
				else TextDrawSpeedLimit(p, 0);
			}
		}
	}
	return 1;
}