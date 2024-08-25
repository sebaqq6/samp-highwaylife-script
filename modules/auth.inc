//**********DANE*************

#define sqluser "user"//your sql user
#define sqlpass "pass"//your sql password
#define sqldb "sebaqq6_truck"//your sql database name
#define sqlhost "localhost"//sql host

#define BCRYPT_SALT "TNL56H&NW>srLHuyJ3veqhq5dMkYVP"

#define BCRYPT_COST 10

//******MACRO**************
new MySQL:g_SQL;
new mQuery[1024];
#define mq_format( format(mQuery, 1024, 
#define mq_send( debugmysql(), mysql_tquery(g_SQL, mQuery,
#define mq_getdata() new rekordy, pola; cache_get_row_count(rekordy); cache_get_field_count(pola)

stock cache_get_row_count_ex()
{
	new rcount;
	cache_get_row_count(rcount);
	return rcount;
}

stock debugmysql()
{
	//printf("%s", mQuery);//odkomentuj, aby śledzić zapytania skryptu
}

stock ShowLogin(playerid)  
{
	new motd[1024];
	//format(motd, 1024, "\n");
	//format(motd, 1024, "%s\n", motd);
	format(temp_string, 512,  "%s"COL_WHITE"Witaj, "COL_BLUE"%s"COL_WHITE"!\n"COL_WHITE"Aby "COL_GREEN"zagrać"COL_WHITE" musisz się "COL_BLUE"zalogować"COL_WHITE".", motd, nick(playerid));
	Dialog_Show(playerid, LOGOWANIE, DIALOG_STYLE_PASSWORD, ""COL_GREEN"»"COL_WHITE" LOGOWANIE - Highway Life", temp_string, "Zaloguj", "Wyjdz");
	return 1;
}

stock ShowRegister(playerid)  
{
	new motd[1024];
	//format(motd, 1024, "\n");
	//format(motd, 1024, "%s\n", motd);
	format(temp_string, 512,  "%s"COL_WHITE"Witaj, "COL_BLUE"%s"COL_WHITE"!\n"COL_WHITE"Aby "COL_GREEN"zagrać"COL_WHITE" musisz się "COL_BLUE"zarejestrować"COL_WHITE".", motd, nick(playerid));
	format(temp_string, 512, "%s\n"COL_WHITE"Podaj hasło"COL_RED"(Hasło musi zawierać od 4 do 16 znaków.)"COL_WHITE":\n", temp_string);
	Dialog_Show(playerid, REJESTRACJA, DIALOG_STYLE_INPUT, ""COL_RED"»"COL_WHITE" Rejestracja - Highway Life", temp_string, "Dalej", "Wyjdz");
	return 1;
}


forward OnAccountLoad(playerid);
public OnAccountLoad(playerid)
{
	//***********************************************************************************************************************************
	cache_get_value_name_int(0, "id", 	gracz[playerid][UID]);
	//ładowanie pojazdów gracza
	mq_format("SELECT * FROM `pojazdy` WHERE `status`='1' AND `owner_type`='%d' AND `owner`='%d';", VEHICLE_PLAYER, gracz[playerid][UID]);
	mq_send("LoadVehFromDB");
	//koniec ładowania pojazdów gracza
	cache_get_value_name(0, "nick_ic", gracz[playerid][nick_ic],  32);
	cache_get_value_name_int(0, "HP", 	gracz[playerid][HP]);
	cache_get_value_name_int(0, "stamina", 	gracz[playerid][stamina]);
	cache_get_value_name(0, "Haslo", gracz[playerid][Haslo], 64);
	cache_get_value_name_int(0, "Plec", 	gracz[playerid][Plec]);
	cache_get_value_name_int(0, "Wiek", 	gracz[playerid][Wiek]);
	cache_get_value_name_int(0, "Skin", 	gracz[playerid][Skin]);
	cache_get_value_name_int(0, "skin_custom", 	gracz[playerid][skin_custom]);
	cache_get_value_name_int(0, "skin_custom_expire", 	gracz[playerid][skin_custom_expire]);
	if(gracz[playerid][skin_custom_expire] > serwer[time_timestamp])
	{
		gracz[playerid][Skin] = gracz[playerid][skin_custom];
	}
	cache_get_value_name_int(0, "PSek", 	gracz[playerid][PSek]);
	cache_get_value_name_int(0, "PMin", 	gracz[playerid][PMin]);
	cache_get_value_name_int(0, "PGodz", 	gracz[playerid][PGodz]);
	cache_get_value_name_float(0, "PosX", 	gracz[playerid][PosX]);
	cache_get_value_name_float(0, "PosY", 	gracz[playerid][PosY]);
	cache_get_value_name_float(0, "PosZ", 	gracz[playerid][PosZ]);
	cache_get_value_name_float(0, "PosR", 	gracz[playerid][PosR]);
	cache_get_value_name_int(0, "AdminLevel", 	gracz[playerid][AdminLevel]);
	cache_get_value_name_int(0, "WebReg", 	gracz[playerid][WebReg]);
	cache_get_value_name_int(0, "MapperLvl", 	gracz[playerid][MapperLvl]);
	cache_get_value_name_int(0, "frakcja", 	gracz[playerid][frakcja]);
	cache_get_value_name_int(0, "frakcja_permlvl", 	gracz[playerid][frakcja_permlvl]);
	cache_get_value_name(0, "frakcja_tytul", gracz[playerid][frakcja_tytul], 24);
	cache_get_value_name_int(0, "frakcja_wyplata", 	gracz[playerid][frakcja_wyplata]);
	cache_get_value_name_int(0, "frakcja_totalduty", 	gracz[playerid][frakcja_totalduty]);
	cache_get_value_name_int(0, "firma", 	gracz[playerid][firma]);
	cache_get_value_name_int(0, "firma_permlvl", 	gracz[playerid][firma_permlvl]);
	cache_get_value_name_int(0, "firma_wyplata", 	gracz[playerid][firma_wyplata]);
	cache_get_value_name_int(0, "firma_kontrakt_kg", 	gracz[playerid][firma_kontrakt_kg]);
	cache_get_value_name(0, "master_nick", gracz[playerid][master_nick], 32);
	cache_get_value_name(0, "custom_radio", gracz[playerid][custom_radio], 64);
	if(strlen(gracz[playerid][master_nick]) < 3) format(gracz[playerid][master_nick], 32, "%s", nick(playerid));
	cache_get_value_name_int(0, "gold", 	gracz[playerid][gold]);
	cache_get_value_name_int(0, "vip", 	gracz[playerid][vip]);
	cache_get_value_name_int(0, "kasa", 	gracz[playerid][kasa]);
	cache_get_value_name_int(0, "muted_timestamp", 	gracz[playerid][muted_timestamp]);
	cache_get_value_name_int(0, "vhl_muted_timestamp", 	gracz[playerid][vhl_muted_timestamp]);
	cache_get_value_name_int(0, "score", 	gracz[playerid][ps_score]);
	SetPlayerScore(playerid, gracz[playerid][ps_score]);
	cache_get_value_name_int(0, "kursy", 	gracz[playerid][kursy]);
	cache_get_value_name_int(0, "rlg_timestamp", 	gracz[playerid][rlg_timestamp]);
	cache_get_value_name_int(0, "wanted_lvl", 	gracz[playerid][scigany_lvl]);
	cache_get_value_name(0, "wanted_reason", gracz[playerid][scigany_powod], 64);
	cache_get_value_name_int(0, "prisoner", 	gracz[playerid][prisoner]);
	cache_get_value_name_int(0, "prisoner_time", 	gracz[playerid][prisoner_time]);
	cache_get_value_name_int(0, "prisoner_prisonid", 	gracz[playerid][prisoner_prisonid]);
	cache_get_value_name_int(0, "bw", 	gracz[playerid][bw]);
	cache_get_value_name_int(0, "bw_time", 	gracz[playerid][bw_time]);
	cache_get_value_name_float(0, "bw_X", 	gracz[playerid][bw_X]);
	cache_get_value_name_float(0, "bw_Y", 	gracz[playerid][bw_Y]);
	cache_get_value_name_float(0, "bw_Z", 	gracz[playerid][bw_Z]);
	cache_get_value_name_int(0, "wypadek", 	gracz[playerid][wypadek]);
	cache_get_value_name_int(0, "wypadek_time", 	gracz[playerid][wypadek_time]);
	cache_get_value_name_float(0, "wypadek_X", 	gracz[playerid][wypadek_X]);
	cache_get_value_name_float(0, "wypadek_Y", 	gracz[playerid][wypadek_Y]);
	cache_get_value_name_float(0, "wypadek_Z", 	gracz[playerid][wypadek_Z]);
	cache_get_value_name_float(0, "wypadek_R", 	gracz[playerid][wypadek_R]);
	cache_get_value_name_int(0, "wypadek_vehicleuid", 	gracz[playerid][wypadek_vehicleuid]);
	cache_get_value_name_int(0, "dokumenty", 	gracz[playerid][dokumenty]);
	cache_get_value_name_int(0, "prawko_TB", 	gracz[playerid][prawko_TB]);
	cache_get_value_name_int(0, "prawko_PB", 	gracz[playerid][prawko_PB]);
	cache_get_value_name_int(0, "prawko_TCE", 	gracz[playerid][prawko_TCE]);
	cache_get_value_name_int(0, "prawko_PCE", 	gracz[playerid][prawko_PCE]);
	cache_get_value_name_int(0, "upr_adr", 	gracz[playerid][upr_adr]); 
	cache_get_value_name_int(0, "przebieg", 	gracz[playerid][przebieg]);
	cache_get_value_name_float(0, "sila", 		gracz[playerid][sila]);
	cache_get_value_name_float(0, "odpornosc", 	gracz[playerid][odpornosc]);
	cache_get_value_name_int(0, "fight_style", 	gracz[playerid][fight_style]);
	cache_get_value_name_int(0, "fight_timestamp_end", 	gracz[playerid][fight_timestamp_end]);
	cache_get_value_name_int(0, "karnet", 	gracz[playerid][karnet]);
	cache_get_value_name(0, "last_radio", gracz[playerid][last_radio], 128);
	cache_get_value_name_int(0, "pursuit_total", 	gracz[playerid][pursuit_total]);
	cache_get_value_name_int(0, "pursuit_escapes", 	gracz[playerid][pursuit_escapes]);
	cache_get_value_name_int(0, "pursuit_catch", 	gracz[playerid][pursuit_catch]);
	cache_get_value_name_int(0, "vhl_volume_speak", 	gracz[playerid][vhl_volume_speak]);
	cache_get_value_name_int(0, "vhl_volume_micro", 	gracz[playerid][vhl_volume_micro]);
	cache_get_value_name_int(0, "vhl_ptt_virtkeycode", 	gracz[playerid][vhl_ptt_virtkeycode]);
	cache_get_value_name_int(0, "bank_number", 	gracz[playerid][bank_number] );
	cache_get_value_name_int(0, "bank_saldo", 	gracz[playerid][bank_saldo] );
	cache_get_value_name_int(0, "hlfriend", 	gracz[playerid][hlfriend] );
	//gracz[playerid][MapperLvl] = 3;
	gracz[playerid][LastOnline] = serwer[time_timestamp];
	mq_format("UPDATE `Konta` SET `LastOnline`='%d', `ip_last`='%s' WHERE `id`='%d';", gracz[playerid][LastOnline], playerip(playerid, true), gracz[playerid][UID]);
	mq_send("QLoginUpdateData");
	new tempIP[64];
	cache_get_value_name(0, "ip_register", tempIP, 64);
	if(strlen(tempIP) < 4)
	{
		mq_format("UPDATE `Konta` SET `LastOnline`='%d', `ip_register`='%s' WHERE `id`='%d';", gracz[playerid][LastOnline], playerip(playerid, true), gracz[playerid][UID]);
		mq_send("QLoginUpdateData");
	}
	mq_format("SELECT SUM(`time`) AS `duty_suma` FROM `fractions_weekly_duty_time` WHERE `fid`='%d' AND `uid`='%d' GROUP BY `uid`;", gracz[playerid][frakcja], gracz[playerid][UID]);
	mq_send("GetTotalTolalDutyTime", "d", playerid);
	//***********************************************************************************************************************************
	gracz[playerid][loggedin] = true;
	gracz[playerid][radio_laststation] = -1;
	SetPlayerVirtualWorld(playerid, 0);
	TogglePlayerControllable(playerid, false);
	HidePanorama(playerid);
	SetPlayerHealth(playerid, gracz[playerid][HP]);
	CreateLabelNick(playerid);
	if(gracz[playerid][Skin] == 0) gracz[playerid][Skin] = 299;
	SetSpawnInfo(playerid, 0, gracz[playerid][Skin], gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], gracz[playerid][PosR], 0, 0, 0, 0, 0, 0);
	SetPVarFloat(playerid, "spawn_X", gracz[playerid][PosX]);
	SetPVarFloat(playerid, "spawn_Y", gracz[playerid][PosY]);
	SetPVarFloat(playerid, "spawn_Z", gracz[playerid][PosZ]);
	SetPVarFloat(playerid, "spawn_R", gracz[playerid][PosR]);
	gracz[playerid][last_skin] = gracz[playerid][Skin];
	SetPVarInt(playerid, "PayForChangeSkin", 0);
	TogglePlayerSpectating(playerid, false);
	//SpawnPlayer(playerid);
	SendClientMessageEx(playerid, -1, "(("COL_EASY"Zalogowano na postać "COL_GREEN"%s "COL_EASY"(UID: %d | Konto: "COL_BLUE"%s"COL_EASY"). Miłej rozgrywki!"COL_WHITE"))", nick(playerid), gracz[playerid][UID], gracz[playerid][master_nick]);
	//new bool:nofade;
	StartLoginHistory(playerid);
	if(gracz[playerid][AdminLevel])
	{
		for(new ac; ac < 60; ac++)
		{
			EnableAntiCheatForPlayer(playerid, ac, false);
		}
		SendClientMessageEx(playerid, -1, "(("COL_EASY"Posiadasz "COL_GREEN"["COL_RED"%d"COL_GREEN"]"COL_EASY" poziom uprawnień. Aby wejść na służbę wpisz: "COL_BLUE"/aduty"COL_WHITE"))", gracz[playerid][AdminLevel]);	
		PC_EmulateCommand(playerid, "/aduty");
		PC_EmulateCommand(playerid, "/eyeveh");
	}
	if(gracz[playerid][sobeit_detect])
	{
		if(!gracz[playerid][AdminLevel]) 
		{
			//nofade = true;
			Ban_Time(-1, playerid, "Niedozwolone oprogramowanie.", 90);
		}
		else 
		{
			SendClientMessage(playerid, -1, ""COL_RED"[WYKRYCIE]"COL_WHITE" Administratorze, skrypt wykrył u Ciebie mod s0beit. Pamiętaj, żeby nie używać go do zabawy.");
		}
	}
	format(temp_string, 128, "~w~Witaj z powrotem~n~~b~%s", nick(playerid));
	if(!gracz[playerid][WebReg]) GameTextForPlayer(playerid, temp_string, 3000, 1);
	ShowHud(playerid);
	//if(!nofade) FadeColorForPlayer(playerid, 0, 0, 0, 255, 0, 0, 0, 0, 30, 1);
	gracz[playerid][first_spawn] = true;
	gracz[playerid][stamina_timestamp] = serwer[time_timestamp]+(60*5);
	UpdatePlayerColor(playerid);
	StartLoginHistory(playerid);
	StopAudioStreamForPlayer(playerid);
	if(strlen(gracz[playerid][last_radio]) > 3)
	{
		PlayAudioStreamForPlayer(playerid, gracz[playerid][last_radio]);
	}
	HideTDHighLifeLogon(playerid);
	//PreloadAnimations(playerid);
	Streamer_ToggleIdleUpdate(playerid, 1);
	gracz[playerid][pointer_object] = CreateDynamicObject(19606, 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0, .playerid = playerid);
	printf("[PLAYER]Gracz %s zalogowal sie. IP: %s", nick(playerid), playerip(playerid));
	SendClientMessage(playerid, -1, ""COL_GREY"[LAG]"COL_WHITE" Jeśli masz niską liczbę klatek, możesz zredukować ilość wyświetlanych obiektów: "COL_RED"/lag"COL_WHITE".");
	SendClientMessage(playerid, -1, ""COL_GREEN"[CZAT]"COL_WHITE" Aby pisać na czacie globalnym użyj "COL_ORANGE"/o Siema :)"COL_WHITE" lub "COL_ORANGE"!Siema :)"COL_WHITE".");
	//SendClientMessageToAllEx(-1, "{00ff38}••• {3ec1dd}Gracz {FFFFFF}%s{3ec1dd}(%d) {52b81e}zalogował się{3ec1dd} do gry! Witamy serdecznie! {00ff38}•••", nick(playerid), playerid);
	new strLog[256];
	format(strLog, 256, "{00ff38}••• {3ec1dd}Gracz {FFFFFF}%s{3ec1dd}(%d) {52b81e}zalogował się{3ec1dd} do gry! Witamy serdecznie! {00ff38}•••", nick(playerid), playerid);
	SavePublicChatLog(strLog);	
	//gps_AddPlayer(playerid);
	ShowJoinLeaveTD(playerid, 0, 0, 0);
	//--------------------
	Init_VoicePerPlayer(playerid);
	return 1;
}

stock logged(playerid)
{
	if(playerid >= 0)
	{
		if(IsPlayerConnected(playerid))
		{
			if(gracz[playerid][loggedin]) return 1;
		}
	}
	return 0;
}

task GetTotalTolalDutyTime(playerid)
{
	mq_getdata();
	if(rekordy) cache_get_value_name_int(0, "duty_suma", gracz[playerid][duty_suma]);
	return 1;
}

stock LoginCamera(playerid, mode = 0)
{
	if(mode)
	{
		SetPlayerCameraPos(playerid, -16.4676, 1355.1093, 77.5971);
		SetPlayerCameraLookAt(playerid, -15.4715, 1355.1793, 77.5271);
	}
	else
	{
		SetPlayerVirtualWorld(playerid, 0);
		Process_CameraLogin(playerid, camera_login[0][0], camera_login[0][1], camera_login[0][2], camera_login[0][3], camera_login[0][4], camera_login[0][5], 0, 0);
	}
	return 1;
}

task Process_CameraLogin(playerid, Float:FromX, Float:FromY, Float:FromZ, Float:ToX, Float:ToY, Float:ToZ, camid, step)
{
	if(gracz[playerid][loggedin]) return 1;//jeśli zalogowany, to proces ma być zablokowany
	if(!IsPlayerConnected(playerid)) return 1;
	const time_move_camera = 1000*12;
	switch(step)
	{
		case 0://początkowe ustawienie kamery
		{
			SetPlayerCameraPos(playerid, FromX, FromY, FromZ);
			SetPlayerCameraLookAt(playerid, ToX, ToY, ToZ);
			SetTimerEx("Process_CameraLogin", 1000, false, "dffffffdd", playerid, FromX, FromY, FromZ, ToX, ToY, ToZ, camid, 1);
		}
		case 1://wprawianie kamery w ruch
		{
			InterpolateCameraPos(playerid, FromX, FromY, FromZ, ToX, ToY, ToZ, time_move_camera);
			SetTimerEx("Process_CameraLogin", time_move_camera-2000, false, "dffffffdd", playerid, FromX, FromY, FromZ, ToX, ToY, ToZ, camid, 2);
		}
		case 2://przełączanie na następną kamerę
		{
			if(camid >= sizeof(camera_login)-1) camid = 0;
			else camid++;
			SetTimerEx("Process_CameraLogin", 100, false, "dffffffdd", playerid, camera_login[camid][0], camera_login[camid][1], camera_login[camid][2], camera_login[camid][3], camera_login[camid][4], camera_login[camid][5], camid, 0);
			//Process_CameraLogin(playerid, camera_login[camid][0], camera_login[camid][1], camera_login[camid][2], camera_login[camid][3], camera_login[camid][4], camera_login[camid][5], camid, 0);
		}
	}
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	if(IsPlayerNPC(playerid)) return 1;
	if(gracz[playerid][loggedin]) SetSpawnInfo(playerid, 0, gracz[playerid][Skin], GetPVarFloat(playerid, "spawn_X"), GetPVarFloat(playerid, "spawn_Y"), GetPVarFloat(playerid, "spawn_Z"), GetPVarFloat(playerid, "spawn_R"), 0, 0, 0, 0, 0, 0);
	else SetSpawnInfo(playerid, 0, 162, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
	return 1;
}

stock ConnectDB()
{
	g_SQL = mysql_connect(sqlhost, sqluser, sqlpass, sqldb);
	print("[CONNECT]Lacze z  localhost...");
	if(mysql_errno() != 0) printf("[CONNECT]BLAD POLACZENIA Z BAZA DANYCH! - EXIT..."), SendRconCommand("exit");
	else
	{ 
		printf("[CONNECT]Polaczono z baza danych.");
		mysql_set_charset("cp1250", g_SQL);
	}
	return 1;
}

stock AuthPlayer(playerid)
{
	mq_format("SELECT `id`,`Haslo`,`Nick`,`ObjDrawDist` FROM `Konta` WHERE `Nick`='%s' LIMIT 0,1;", nick(playerid, true));
	mq_send("OnAccountCheck", "d", playerid);
	return 1;
}

forward OnAccountCheck(playerid);
public OnAccountCheck(playerid)
{
	Process_WeatherTime(playerid);
	//KONFIG ANTYCHEAT
	for(new ac; ac < 60; ac++)//uruchamiamy wszystko
	{
		EnableAntiCheatForPlayer(playerid, ac, true);
	}
	//wyłączamy:
	EnableAntiCheatForPlayer(playerid, 24, false);//Parkour mod
	EnableAntiCheatForPlayer(playerid, 33, false);//AntiFreeze
	EnableAntiCheatForPlayer(playerid, 36, false);//Parkour mod
	EnableAntiCheatForPlayer(playerid, 38, false);//Ping
	EnableAntiCheatForPlayer(playerid, 5, false);//Teleport hack 5
	EnableAntiCheatForPlayer(playerid, 31, false);//carshoot
	//KONFIG AC - END
	ShowTDHighLifeLogon(playerid, 0);
	mq_getdata();
	LoginCamera(playerid);
	if(rekordy)
	{
		cache_get_value_name_int(0, "id", 		gracz[playerid][UID]);
		cache_get_value_name(0, "Haslo", gracz[playerid][Haslo], 64);
		cache_get_value_name(0, "Nick", gracz[playerid][Name], 24);
		cache_get_value_name_float(0, "ObjDrawDist", 		gracz[playerid][rpc_ObjDrawDist]);
		new tmpnick[24];
		format(tmpnick, 24, "init[%d]", playerid);
		SetPlayerName(playerid, tmpnick);
		SetPlayerName(playerid, gracz[playerid][Name]);
		ShowLogin(playerid);
		CheckBan(playerid);
	}
	else
	{
		CheckBan(playerid);
		ShowRegister(playerid);
	}
	return 1;
}

Dialog:LOGOWANIE(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid, "Click 'Quit'.");
	if(!strlen(inputtext)) 
	{
		ShowLogin(playerid);
		return 1;	
	}
	if(strfind(gracz[playerid][Haslo], "$2y$", true) != -1)//bcrypt? logowanie -> 
	{
		new pass_hash_final[512];
		format(pass_hash_final, 512, "%d_%s_%s", gracz[playerid][UID], inputtext, BCRYPT_SALT);
		bcrypt_check(pass_hash_final, gracz[playerid][Haslo], "OnLoginPasswordChecked", "d", playerid);
	}
	else if(udb_hash(inputtext) == strval(gracz[playerid][Haslo]))//prawidłowe hasło UDB
	{
		//zmiana na bcrypt
		new pass_hash_final[512];
		format(pass_hash_final, 512, "%d_%s_%s", gracz[playerid][UID], inputtext, BCRYPT_SALT);
		bcrypt_hash(pass_hash_final, BCRYPT_COST, "LoginPassUDBtoBCRYPT", "d", playerid);
	}
	else BadLoginPassError(playerid);
	//**************************************
	return 1;
}

task OnLoginPasswordChecked(playerid)//bcrypt
{
	new bool:match = bcrypt_is_equal();
	if(match == true)
	{
		mq_format("SELECT * FROM `Konta` WHERE `Nick`='%s' LIMIT 0,1;", nick(playerid, true));
		mq_send("OnAccountLoad", "d", playerid);
	}
	else BadLoginPassError(playerid);
	return 1;
}

task LoginPassUDBtoBCRYPT(playerid)//zmiana z UDB na BCRYPT
{
	bcrypt_get_hash(gracz[playerid][Haslo]);
	mq_format("UPDATE `Konta` SET `Haslo`='%s' WHERE `Nick`='%s';", gracz[playerid][Haslo], gracz[playerid][Name]);
	mysql_query(g_SQL, mQuery, false);
	mq_format("SELECT * FROM `Konta` WHERE `Nick`='%s' LIMIT 0,1;", nick(playerid, true));
	mq_send("OnAccountLoad", "d", playerid);
	return 1;
}

stock BadLoginPassError(playerid)
{
	new str[130];
	SetPVarInt(playerid, "BadPass", GetPVarInt(playerid, "BadPass")+1);
	if(GetPVarInt(playerid, "BadPass") == 3) return KickEx(playerid, "3/3 bad password.");
	format(str, 130, ""COL_WHITE"Aby "COL_GREEN"zagrać"COL_WHITE" musisz się "COL_BLUE"zalogować"COL_WHITE".\nBłędnych prób: "COL_RED"%d/3", GetPVarInt(playerid, "BadPass"));
	Dialog_Show(playerid, LOGOWANIE, DIALOG_STYLE_PASSWORD, ""COL_GREEN"»"COL_WHITE" LOGIN - Highway Life", str, "Zaloguj", "Wyjdz");
	return 1;
}

stock CheckBan(playerid)
{
	mq_format("SELECT `BanList`.*, FROM_UNIXTIME(`BanList`.`time`) AS `times`, FROM_UNIXTIME(`BanList`.`time_end`) AS `time_ends`, `u1`.`Nick` AS `admin_nick`, `u2`.`Nick` AS `user_nick`, (`BanList`.`time_end`-UNIX_TIMESTAMP(CURRENT_TIMESTAMP)) AS `left` FROM `BanList` LEFT OUTER JOIN `Konta` AS `u1` ON `BanList`.`aid`=`u1`.`id` LEFT OUTER JOIN `Konta` AS `u2` ON `BanList`.`uid`=`u2`.`id` WHERE `BanList`.`time_end`>UNIX_TIMESTAMP(CURRENT_TIMESTAMP) AND (`u2`.`Nick` LIKE '%s' OR (`BanList`.`ip`='%s' AND `BanList`.`ip_on`='1') OR (INET_NTOA(INET_ATON(`BanList`.`ip`) & 0xFFFF0000)=INET_NTOA(INET_ATON('%s') & 0xFFFF0000) AND `BanList`.`ip_on`='2') OR (`BanList`.`gpci`='%s' AND `BanList`.`gpci_on`='1')) ORDER BY `BanList`.`time_end` DESC LIMIT 0,1;", nick(playerid, true), playerip(playerid, true), playerip(playerid, true), serial(playerid, true));
	mq_send("OnBanChecked", "d", playerid);
	return 1;
}

forward OnBanChecked(playerid);
public OnBanChecked(playerid)
{
	mq_getdata();
	new b_id, reason[128], b_admin[20], b_user[20], b_start[32], b_end[24], left_time;
	new a_id;
	if(rekordy)
	{
		cache_get_value_name_int(0, "id", 		b_id);
		cache_get_value_name(0, "reason", reason);
		cache_get_value_name_int(0, "aid", 		a_id);
		if(a_id)
		{
			cache_get_value_name(0, "admin_nick", b_admin);
		}
		else
		{
			format(b_admin, 20, "SYSTEM");
		}
		cache_get_value_name(0, "user_nick", b_user);
		cache_get_value_name(0, "times", b_start);
		cache_get_value_name(0, "time_ends", b_end);
		cache_get_value_name_int(0, "left", 		left_time);
		ShowBanInfo(playerid, b_id, b_admin, b_user, b_start, b_end, reason, left_time);
	}
	return 1;
}

stock ShowBanInfo(playerid, banid, admin[], user[], nadane[], koniec[], powod[], dokonca)
{
	KickEx(playerid, "Aktywny ban.");
	const contstr = 1600;
	new title[128], content[contstr];
	format(title, 128, ""COL_GREEN"»"COL_WHITE" BAN INFO"COL_RED"[ID: %d]", banid);
	format(content, contstr, ""COL_GREY"Ban ID:\t\t"COL_RED"%d\n", banid);
	format(content, contstr, "%s"COL_GREY"Admin:\t\t"COL_RED"%s\n", content, admin);
	if(compare(user, "NULL"))
	{
		format(content, contstr, "%s"COL_GREY"Konto:\t"COL_YELLOW"Nie zarejestrowane\n", content);
	}
	else
	{
		format(content, contstr, "%s"COL_GREY"Konto:\t\t"COL_YELLOW"%s\n", content, user);
	}
	format(content, contstr, "%s"COL_GREY"IP:\t\t"COL_YELLOW"%s\n", content, playerip(playerid));
	format(content, contstr, "%s"COL_GREY"Powód:\t"COL_ORANGE"%s\n", content, powod);
	format(content, contstr, "%s"COL_GREY"Data nadania:\t"COL_BLUE"%s\n", content, nadane);
	format(content, contstr, "%s"COL_GREY"Wygasa:\t"COL_BLUE"%s\n", content, koniec);
	new day_s, hour_s, minute_s, sec_s;
	SecToTime(dokonca, day_s, hour_s, minute_s, sec_s);
	format(content, contstr, "%s"COL_GREY"Pozostało:\t"COL_GREEN"%dd, %dh, %dm, %ds\n", content,  day_s, hour_s, minute_s, sec_s);
	format(content, contstr, "%s"COL_GREY"Napisz apelacje na "COL_GREEN"forum.highwaylife.pl\n", content); 
	format(content, contstr, "%s"COL_GREY"Jeśli chcesz apelować "COL_YELLOW"wciśnij F8(screenshoot jest potrzebny!).\n", content);
	format(content, contstr, "%s"COL_ORANGE"Wrzucając screena możesz zamazać adres IP!\n", content);
	ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, title, content, "Zamknij", "");
	return 1;
}

stock Ban_Time(adminid, targetid, reason[], days)
{
	if(gracz[targetid][kick_antyspam] > serwer[time_timestamp]) return 0;
	new reason_escape[64];
	format(reason_escape, 64, reason);
	mysql_escape_string(reason_escape, reason_escape, 64);
	gracz[targetid][kick_antyspam] = serwer[time_timestamp]+4;
	new czas = (days*24*60*60)+gettime();
	if(adminid != -1)
	{
		mq_format("INSERT INTO `BanList` (`uid`, `aid`, `time`, `time_end`, `ip_on`, `ip`, `gpci_on`, `gpci`, `reason`) VALUES ('%d', '%d', '%d', '%d', '1', '%s', '0', '%s', '%s');", gracz[targetid][UID], gracz[adminid][UID],  gettime(), czas, playerip(targetid, true), serial(targetid, true), reason_escape);
	}
	else
	{
		mq_format("INSERT INTO `BanList` (`uid`, `aid`, `time`, `time_end`, `ip_on`, `ip`, `gpci_on`, `gpci`, `reason`) VALUES ('%d', '0', '%d', '%d', '1', '%s', '0', '%s', '%s');", gracz[targetid][UID],  gettime(), czas, playerip(targetid, true), serial(targetid, true), reason_escape);
	}
	Interwencja(adminid, targetid, days, PENALTY_BAN, reason_escape);
	mq_send("QBan");
	KickEx(targetid, reason_escape);
	return 1;
}

stock CheckS0beit(playerid)
{
	LoginCamera(playerid, 1);
	new golf = CreateVehicle(457, 0.0, 0.0, 4.0, 0.0, 1, 1, 20);
	SetPlayerVirtualWorld(playerid, playerid+1000);
	SetVehicleVirtualWorld(golf, GetPlayerVirtualWorld(playerid));
	LinkVehicleToInterior(golf, 500);
	PutPlayerInVehicle(playerid, golf, 0);
	SetTimerEx("SobeitCheck_s1", 300, false, "dd", playerid, golf);
	return 1;
}

forward SobeitCheck_s1(playerid, vehid);
public SobeitCheck_s1(playerid, vehid)
{
	LoginCamera(playerid, 1);
	RemovePlayerFromVehicle(playerid);
	SetTimerEx("SobeitCheck_s2", 300, false, "dd", playerid, vehid);
	return 1;
}

forward SobeitCheck_s2(playerid, vehid);
public SobeitCheck_s2(playerid, vehid)
{
	LoginCamera(playerid, 1);
	DestroyVehicle(vehid);
	new wdata1, wdata2;
	GetPlayerWeaponData(playerid, 1, wdata1, wdata2);
	if(wdata1)
	{
		gracz[playerid][sobeit_detect] = true;
	}
	else
	{
		gracz[playerid][sobeit_detect] = false;
	}	
	SetTimerEx("SobeitCheck_s3", 100, false, "d", playerid);
	return 1;
}

forward SobeitCheck_s3(playerid);
public SobeitCheck_s3(playerid)
{
	LoginCamera(playerid, 1);
	new wdata1, wdata2;
	GetPlayerWeaponData(playerid, 1, wdata1, wdata2);
	if(wdata1)
	{
		gracz[playerid][sobeit_detect] = true;
	}
	else
	{
		gracz[playerid][sobeit_detect] = false;
	}
	TogglePlayerSpectating(playerid, true);
	ResetPlayerWeapons(playerid);
	AuthPlayer(playerid);
	return 1;
}

public OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle)
{
	printf("[CONNECT]Problem z baza danych - blokuje serwer...");
	SendRconCommand("password blockbymysql");
	SetGameModeText("AWARIA");
	for(new k; k <= GetPlayerPoolSize(); k++)
	{
		if(IsPlayerConnected(k) && !IsPlayerNPC(k))
		{
			KickEx(k, "AWARIA");
		}
	}
	printf("|QERROR| eid: %d | err: %s | call: %s | query: %s", errorid, error, callback, query);
	return 1;
}



Dialog:REJESTRACJA(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid, "Click 'Quit'.");
	switch(strlen(inputtext))
	{
		case 4..16:
		{
			format(gracz[playerid][Haslo], 64, "%s", inputtext);
			Dialog_Show(playerid, PLEC, DIALOG_STYLE_LIST, ""COL_RED"»"COL_WHITE" Rejestracja - Płeć postaci", ""COL_RED"»"COL_WHITE" Mężczyzna\n"COL_RED"»"COL_WHITE" Kobieta", "Dalej", "Wyjdz");
		}
		default:
		{
			ShowRegister(playerid);
		}
	}
	return 1;
}

Dialog:PLEC(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid, "Click 'Quit'.");
	if(listitem == 0)
	{
		SendClientMessage(playerid, -1, "(("COL_GREY"Płeć postaci: "COL_GREEN"Mężczyzna"COL_WHITE".))");
		gracz[playerid][Plec] = 1;
		Dialog_Show(playerid, WIEK, DIALOG_STYLE_INPUT, ""COL_RED"»"COL_WHITE" Rejestracja - Wiek postaci", "Podaj wiek"COL_RED"(18-60)"COL_WHITE":", "Dalej", "Wyjdz");
	} 
	else 
	{
		SendClientMessage(playerid, -1, "(("COL_GREY"Płeć postaci: "COL_GREEN"Kobieta"COL_WHITE".))");
		gracz[playerid][Plec] = 2;
		Dialog_Show(playerid, WIEK, DIALOG_STYLE_INPUT, ""COL_RED"»"COL_WHITE" Rejestracja - Wiek postaci", "Podaj wiek"COL_RED"(18-60)"COL_WHITE":", "Dalej", "Wyjdz");
	}
	return 1;
}

Dialog:WIEK(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid, "Click 'Quit'.");
	new age = strval(inputtext);

	switch(age)
	{
		case 18..60:
		{
			gracz[playerid][Wiek] = age;
			SendClientMessageEx(playerid, -1, "(("COL_GREY"Wiek Twojej postaci: "COL_GREEN"%d"COL_WHITE".))", gracz[playerid][Wiek]);
			Dialog_Show(playerid, NAZWAPOSTACI, DIALOG_STYLE_INPUT, ""COL_RED"»"COL_WHITE" Rejestracja - Nazwa postaci", "Imie i nazwisko postaci: "COL_RED"(format: Imie_Nazwisko (5-20 znaków))"COL_WHITE":", "Dalej", "Wyjdz");
		}
		default:
		{
			Dialog_Show(playerid, WIEK, DIALOG_STYLE_INPUT, ""COL_RED"»"COL_WHITE" Rejestracja - Wiek postaci", "Podaj wiek"COL_RED"(18-60)"COL_WHITE":", "Dalej", "Wyjdz");
		}
	}
	return 1;
}

Dialog:NAZWAPOSTACI(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid, "Click 'Quit'.");
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
	if(dataok == false) Dialog_Show(playerid, NAZWAPOSTACI, DIALOG_STYLE_INPUT, ""COL_RED"»"COL_WHITE" Rejestracja - Nazwa postaci", "Imie i nazwisko postaci: "COL_RED"(format: Imie_Nazwisko (5-20 znaków))"COL_WHITE":", "Dalej", "Wyjdz");
	else Dialog_Show(playerid, REGEND, DIALOG_STYLE_MSGBOX, ""COL_RED"»"COL_WHITE" Rejestracja - Zakonczenie", ""COL_WHITE"Czy akceptujesz "COL_RED"regulamin serwera"COL_WHITE" znajdujący się na "COL_YELLOW"forum.highwaylife.pl"COL_WHITE"?", "TAK", "NIE");
	return 1;
}


Dialog:REGEND(playerid, response, listitem, inputtext[])
{
	if(!response) return KickEx(playerid, "Click 'Quit'.");
	if(gracz[playerid][Plec] == 1) gracz[playerid][Skin] = skins_male[random(sizeof(skins_male))];
	else if(gracz[playerid][Plec] == 2) gracz[playerid][Skin] = skins_female[random(sizeof(skins_female))];
	else gracz[playerid][Skin] = 299;
	mq_format("INSERT INTO `Konta` (`Nick`,`nick_ic`,`Plec`,`Wiek`,`Skin`,`Haslo`,`WebReg`, `ip_register`, `kasa`) VALUES ('%s','%s','%d','%d','%d','%s','1', '%s', '5000');", nick(playerid, true), gracz[playerid][nick_ic], gracz[playerid][Plec], gracz[playerid][Wiek], gracz[playerid][Skin], gracz[playerid][Haslo], playerip(playerid, true));
	new Cache:cache_id = mysql_query(g_SQL, mQuery, true);
	new insert_id = cache_insert_id();
	cache_delete(cache_id);
	gracz[playerid][UID] = insert_id;
	new pass_hash_final[512];
	format(pass_hash_final, 512, "%d_%s_%s", insert_id, gracz[playerid][Haslo], BCRYPT_SALT);
	bcrypt_hash(pass_hash_final, BCRYPT_COST, "OnRegisterPassHashed", "dd", playerid, insert_id);
	return 1;
}

task OnRegisterPassHashed(playerid, insert_id)
{
	bcrypt_get_hash(gracz[playerid][Haslo]);
	mq_format("UPDATE `Konta` SET `Haslo`='%s' WHERE `id`='%d';", gracz[playerid][Haslo], insert_id);
	mq_send("QueryRegisterEnd", "d", playerid);
	SendClientMessageEx(playerid, -1, "(("COL_GREY"Twoja postać została stworzona."COL_GREEN" Zaloguj się"COL_GREY"!"COL_WHITE"))");
	SetPVarInt(playerid, "ShowRegisterSkinSelect", 1);
	return 1;
}

forward QueryRegisterEnd(playerid);
public QueryRegisterEnd(playerid)
{
	ShowLogin(playerid);
	return 1;
}
