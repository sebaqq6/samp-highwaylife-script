CMD:acmd(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new adminacmd[3048];
	strcat(adminacmd,""COL_RED"`"COL_EASY" - Czat adminów. "COL_GREEN"(poziomy: 1,2,3)\n");
	strcat(adminacmd,""COL_RED"/aduty"COL_EASY" - Zmiana statusu służby "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/kick"COL_EASY" - Wyrzucanie gracza z serwera. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/goto"COL_EASY" - Teleportujesz się do gracza "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/get"COL_EASY" - Teleportujesz do siebie gracza "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/mute | /unmute"COL_EASY" - Uciszanie/Odciszanie gracza."COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/freeze | /unfreeze"COL_EASY" - Zamrażasz/Odmrażasz gracza. "COL_GREEN"(poziomy: 2,3) \n");
	strcat(adminacmd,""COL_RED"/unbw"COL_EASY" - Zdejmujesz BW "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/unwypadek"COL_EASY" - Usuwasz wypadek. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/ip"COL_EASY" - Sprawdzanie IP gracza. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/block"COL_EASY" - Blokada postaci. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/ban"COL_EASY" - Banujesz gracza na określony czas(dni) "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/sethp"COL_EASY" - Ustawiasz HP "COL_GREEN"(poziomy: 2,3) \n");
	strcat(adminacmd,""COL_RED"/tiger"COL_EASY" - Regenerujesz zmęczenie gracza "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/setweather"COL_EASY" - Ustawiasz pogodę "COL_GREEN"(poziomy: 3) \n");
	//strcat(adminacmd,""COL_RED"/settime"COL_EASY" - Ustawiasz godzine "COL_GREEN"(poziomy: 3) \n");
	strcat(adminacmd,""COL_RED"/spec"COL_EASY" - Obserwowanie gracza. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/respawn"COL_EASY" - Respawn nieużywanych pojazdów. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/godofcar"COL_EASY" - Tryb w którym możesz wsiadać do każdego pojazdu frakcji i wszystkich pojazdów graczy. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/unspawn"COL_EASY" - Respawn pojazdu w którym się znajdujesz. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/ann"COL_EASY" - Wiadomosc na srodku ekranu. "COL_GREEN"(poziomy: 2,3) \n");
	strcat(adminacmd,""COL_RED"/cc"COL_EASY" - Czyszczenie czatu wszystkim graczom. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/frakcjaset"COL_EASY" - Zmieniasz sobie frakcje (tymczasowo, aż do reloga). "COL_GREEN"(poziomy: 2,3) \n");
	strcat(adminacmd,""COL_RED"/makeleader"COL_EASY" - Ustawiasz nowego lidera frakcji. "COL_GREEN"(poziomy: 2,3) \n");
	strcat(adminacmd,""COL_RED"/delleader"COL_EASY" - Usuwasz lidera z danej frakcji. "COL_GREEN"(poziomy: 2,3) \n");
	strcat(adminacmd,""COL_RED"/tps"COL_EASY" - Przydatne teleporty. "COL_GREEN"(poziomy: 1,2,3) \n");
	Dialog_Show(playerid, ADMINCMDS, DIALOG_STYLE_MSGBOX, "Komendy Ekipy - strona 1", adminacmd, "Next", "Zamknij");
	return 1;
}

Dialog:ADMINCMDS(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(gracz[playerid][admin_duty] < 1) return 0;
	new adminacmd[3048];
	strcat(adminacmd,""COL_RED"/addscore | /delscore"COL_EASY" - Nagradzenie/karanie gracza (score). "COL_GREEN"(poziomy: 2,3) \n");
	strcat(adminacmd,""COL_RED"/firmapick"COL_EASY" - Zmiana pozycji pickupa firmy. "COL_GREEN"(poziomy: 3) \n");
	strcat(adminacmd,""COL_RED"/eyeveh | /eyecmd"COL_EASY" - Podgląd: niezgodność ze specyfikacją pojazdu | komend. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/doorset"COL_EASY" - Tworzenie przejść. "COL_GREEN"(poziomy: 3) \n");
	strcat(adminacmd,""COL_RED"/speedcam"COL_EASY" - Tworzenie i zarządzanie fotoradarami. "COL_GREEN"(poziomy: 2,3) \n");
	strcat(adminacmd,""COL_RED"/admincar"COL_EASY" - Tworzenie pojazdu administracyjnego. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/vhlgetall"COL_EASY" - [VHL]Podsłuchujesz wszystkich graczy. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/vhlmute | /vhlunmute"COL_EASY" - [VHL]Uciszanie/Odciszanie gracza. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/setnickic"COL_EASY" - Ustawiasz nick IC dla gracza. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/niewidka"COL_EASY" - Stajesz się niewidzilany pod /admins oraz na mapie. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/togglechat"COL_EASY" - Wyłączasz/Włączasz czat globalny. "COL_GREEN"(poziomy: 1,2,3) \n");
	strcat(adminacmd,""COL_RED"/adminskin"COL_EASY" - Skiny administracyjne. "COL_GREEN"(poziomy: 1,2,3) \n");
	ShowPlayerDialog(playerid,84520,DIALOG_STYLE_MSGBOX, "Komendy Ekipy - strona 2", adminacmd, "Czaje","");
	return 1;
}


CMD:aduty(playerid, params[])
{
	if(!gracz[playerid][AdminLevel]) return 0;
	if(gracz[playerid][admin_duty])
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING || gracz[playerid][admin_spec_enabled]) return Error(playerid, "Nie możesz w tym momencie zejść z admin duty (spec-mode?).");
		if(gracz[playerid][admin_godofcar]) return Error(playerid, "Nie możesz zejść z admin duty, ponieważ jesteś w trybie God of Car. ");
		gracz[playerid][admin_duty] = 0;
		gracz[playerid][aaInvisible] = false;
		SendClientMessage(playerid, COLOR_LIGHTGREEN, "[A] "COL_RED"Zszedłeś z admin duty!");
	}
	else
	{
		gracz[playerid][admin_duty] = gracz[playerid][AdminLevel];
		format(temp_string, 256, "[A] "COL_GREEN"Zalogowałeś"COL_WHITE" się na "COL_GREEN"["COL_RED"%d"COL_GREEN"]"COL_WHITE" poziom uprawnień. Lista dostępnych komend: "COL_RED"/acmd"COL_WHITE".", gracz[playerid][admin_duty]);
		SendClientMessage(playerid, COLOR_LIGHTGREEN, temp_string);
	}
	return 1;
}

CMD:kick(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid, reason[128];
	if(sscanf(params,"ds[128]", targetid, reason)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /kick [targetid] [powód]");
	if(!IsPlayerConnected(targetid) || IsPlayerNPC(targetid)) return Error(playerid, "Gracz nie jest połączony.");
	if(gracz[playerid][admin_duty] < gracz[targetid][admin_duty]) return Error(playerid, "Ten gracz to admin o wyższej randze!");
	Interwencja(playerid, targetid, 0, PENALTY_KICK, reason);
	KickEx(targetid, reason);
	return 1;
}

CMD:addscore(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 2) return 0;
	new targetid, score, reason[128];
	if(sscanf(params,"dds[128]", targetid, score, reason)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /addscore [targetid] [score] [powód]");
	if(playerid == targetid && gracz[playerid][admin_duty] < 4) return Error(playerid, "Nie możesz przyznać score samemu sobie.");
	if(!IsPlayerConnected(targetid) || IsPlayerNPC(targetid)) return Error(playerid, "Gracz nie jest połączony.");
	if(score < 1 || score > 1000) return Error(playerid, "Nieprawidłowa wartość score.");
	Interwencja(playerid, targetid, score, SCOREADD, reason);
	GiveScore(targetid, score);
	printf("[ADDSCORE] value: %d | admin: %s | player: %s", score, nick(playerid), nick(targetid));
	return 1;
}

CMD:delscore(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 2) return 0;
	new targetid, score, reason[128];
	if(sscanf(params,"dds[128]", targetid, score, reason)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /delscore [targetid] [score] [powód]");
	if(playerid == targetid && gracz[playerid][admin_duty] < 4) return Error(playerid, "Nie możesz zabrać score samemu sobie.");
	if(!IsPlayerConnected(targetid) || IsPlayerNPC(targetid)) return Error(playerid, "Gracz nie jest połączony.");
	if(score < 1 || score > 1000) return Error(playerid, "Nieprawidłowa wartość score.");
	Interwencja(playerid, targetid, score, SCOREDEL, reason);
	TakeScore(targetid, score);
	printf("[DELSCORE] value: %d | admin: %s | player: %s", score, nick(playerid), nick(targetid));
	return 1;
}

CMD:goto(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /goto [targetid]");
	if(!IsPlayerConnected(targetid)) return Error(playerid, "Gracz nie jest połączony.");
	SetPlayerPos(playerid, gracz[targetid][PosX]+1, gracz[targetid][PosY]+1, gracz[targetid][PosZ]);
	SetPlayerInterior(playerid, GetPlayerInterior(targetid));
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
	if(gracz[playerid][aaPosUsed] == 0)
	{
		gracz[playerid][aaPosUsed] = 1;
		gracz[playerid][aaInt] = GetPlayerInterior(playerid);
		gracz[playerid][aaVW] = GetPlayerVirtualWorld(playerid);
		GetPlayerPos(playerid, gracz[playerid][aaPosX], gracz[playerid][aaPosY], gracz[playerid][aaPosZ]);
		Info(playerid, "Twoja pozycja została zapisana, aby do niej wrócić wpisz "COL_RED"/gotoback"COL_WHITE".");
	}
	return 1;
}

CMD:gotoback(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	if(gracz[playerid][aaPosUsed] == 1)
	{
		gracz[playerid][aaPosUsed] = 0;
		SetPlayerInterior(playerid, gracz[playerid][aaInt]);
		SetPlayerVirtualWorld(playerid, gracz[playerid][aaVW]);
		SetPlayerPos(playerid, gracz[playerid][aaPosX], gracz[playerid][aaPosY], gracz[playerid][aaPosZ]);
		Info(playerid, "Twoja pozycja została wczytana i zresetowana. Komenda /goto zarejestruje na nowo Twoją pozycję.");
	}
	else Error(playerid, "Brak wcześniejszej pozycji do wczytania.");
	return 1;
}

CMD:get(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /get [targetid]");
	if(!IsPlayerConnected(targetid)) return Error(playerid, "Gracz nie jest połączony.");
	if(gracz[targetid][kajdanki]) return Error(playerid, "Ten gracz ma założone kajdanki.");
	if(gracz[targetid][przykuty]) return Error(playerid, "Ten gracz jest przykuty.");
	if(gracz[targetid][bw] > 0) return Error(playerid, "Ten gracz ma BW.");
	if(gracz[targetid][wypadek] > 0) return Error(playerid, "Ten gracz ma wypadek.");
	if(gracz[targetid][prisoner] > 0) return Error(playerid, "Ten gracz jest w celi.");
	if(IsPlayerUseGym(targetid)) Gym_Disconnect(targetid);
	SetPlayerPos(targetid, gracz[playerid][PosX]+1, gracz[playerid][PosY]+1, gracz[playerid][PosZ]);
	SetPlayerInterior(targetid, GetPlayerInterior(playerid));
	SetPlayerVirtualWorld(targetid, GetPlayerVirtualWorld(playerid));
	return 1;
}

CMD:mute(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid, minutes, reason[128];
	if(sscanf(params,"dds[128]", targetid, minutes, reason)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /mute [targetid] [minuty] [powód]");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest zalogowany.");
	if(gracz[playerid][admin_duty] < gracz[targetid][admin_duty]) return Error(playerid, "Ten gracz to admin o wyższej randze!");
	if(minutes <= 0) return Error(playerid, "Czas kary nie może być krótszy niż 1 minuta.");
	if(minutes > 120) return Error(playerid, "Czas kary nie może być dłuższy niż 120 minut.");
	gracz[targetid][muted_timestamp] = 60*minutes+gettime();
	mq_format("UPDATE `Konta` SET `muted_timestamp`='%d' WHERE `id`='%d';", gracz[targetid][muted_timestamp], gracz[targetid][UID]);
	mq_send("QMuted");
	Interwencja(playerid, targetid, minutes, PENALTY_MUTE, reason);
	return 1;
}

CMD:unmute(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /unmute [targetid]");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest zalogowany.");
	if(gracz[playerid][admin_duty] < gracz[targetid][admin_duty]) return Error(playerid, "Ten gracz to admin o wyższej randze!");
	if(gracz[targetid][muted_timestamp] < serwer[time_timestamp]) return Error(playerid, "Ten gracz nie jest uciszony.");
	gracz[targetid][muted_timestamp] = 0;
	mq_format("UPDATE `Konta` SET `muted_timestamp`='%d' WHERE `id`='%d';", gracz[targetid][muted_timestamp], gracz[targetid][UID]);
	mq_send("QMuted");
	Info(playerid, "Gracz został odciszony.");
	Info(targetid, "Zostałeś/aś odciszony.");
	return 1;
}

CMD:freeze(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 2) return 0;
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /freeze [targetid]");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest zalogowany.");
	new strInfo[144];
	format(strInfo, 144, "Zamroziłeś gracza {%06x}%s"COL_WHITE".", GetPlayerColor(targetid) >>> 8, nick(targetid));
	Info(playerid, strInfo);
	Info(targetid, "Zostałeś zamrożony przez administratora.");
	TogglePlayerControllable(targetid, 0);
	return 1;
}

CMD:unfreeze(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 2) return 0;
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /unfreeze [targetid]");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest zalogowany.");
	new strInfo[144];
	format(strInfo, 144, "Odmroziłeś gracza {%06x}%s"COL_WHITE".", GetPlayerColor(targetid) >>> 8, nick(targetid));
	Info(playerid, strInfo);
	Info(targetid, "Zostałeś odmrożony przez administratora.");
	TogglePlayerControllable(targetid, 1);
	return 1;
}

CMD:unbw(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /unbw [targetid]");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest zalogowany.");
	if(gracz[targetid][bw] == 0) return Error(playerid, "Ten gracz nie ma BW.");
	gracz[targetid][bw_time] = 0;
	new strInfo[144];
	format(strInfo, 144, "Usunąłeś BW dla gracza {%06x}%s"COL_WHITE".", GetPlayerColor(targetid) >>> 8, nick(targetid));
	Info(playerid, strInfo);
	Info(targetid, "Admin zdjął Tobie status BW.");
	return 1;
}

CMD:unwypadek(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /unwypadek [targetid]");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest zalogowany.");
	if(gracz[targetid][wypadek] == 0) return Error(playerid, "Ten gracz nie ma wypadku.");
	gracz[targetid][wypadek_time] = 0;
	new strInfo[144];
	format(strInfo, 144, "Usunąłeś wypadek dla gracza {%06x}%s"COL_WHITE".", GetPlayerColor(targetid) >>> 8, nick(targetid));
	Info(playerid, strInfo);
	Info(targetid, "Admin zdjął Tobie status wypadku.");
	return 1;
}

CMD:ip(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /ip [targetid]");
	if(!IsPlayerConnected(targetid)) return Error(playerid, "Gracz nie jest połączony.");
	SendClientMessageEx(playerid, -1, "IP gracza: "COL_BLUE"%s (%d)"COL_WHITE" to: "COL_RED"%s", nick(targetid), targetid, playerip(targetid));
	return 1;
}

CMD:block(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid, reason[128]; 
	if(sscanf(params,"ds[128]", targetid, reason)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /block [targetid] [powód]");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest zalogowany.");
	SendClientMessageEx(playerid, -1, "Zablokowałeś postać: "COL_BLUE"%s"COL_EASY" (UID: %d | Konto: %s).", nick(targetid), gracz[targetid][UID], gracz[targetid][master_nick]);
	new czas = (1025*24*60*60)+gettime();
	mq_format("INSERT INTO `BanList` (`uid`, `aid`, `time`, `time_end`, `ip_on`, `ip`, `gpci_on`, `gpci`, `reason`) VALUES ('%d', '%d', '%d', '%d', '0', '%s', '0', '%s', '%s');", gracz[targetid][UID], gracz[playerid][UID],  gettime(), czas, playerip(targetid, true), serial(targetid, true), reason);
	mq_send("QBlockChar");
	Interwencja(playerid, targetid, 0, PENALTY_BAN, reason);
	KickEx(targetid, reason);
	return 1;
}

CMD:ban(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid, reason[128], days;
	if(sscanf(params,"dds[128]", targetid, days, reason)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /ban [targetid] [dni] [powód]");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest zalogowany.");
	if(gracz[playerid][admin_duty] < gracz[targetid][admin_duty]) return Error(playerid, "Ten gracz to admin o wyższej randze!");
	if(days < 1) return Error(playerid, "Czas nie może być krótszy niż 1 dzień.");
	if(days > 1025) return Error(playerid, "Czas nie może być dłuższy niż 1025 dni.");
	Ban_Time(playerid, targetid, reason, days);
	return 1;
}

CMD:sethp(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 2) return 0;
	new targetid, hp;
	if(sscanf(params,"dd", targetid, hp)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /sethp [targetid] [hp]");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest zalogowany.");
	if(hp < 0) return Error(playerid, "HP nie może być mniejsze niż 0.");
	if(hp > 100) return Error(playerid, "HP nie może być większe niż 100.");
	SetPlayerHealth(targetid, float(hp));
	SendClientMessageEx(playerid, -1, "Ustawiłeś dla gracza: "COL_BLUE"%s (%d)"COL_WHITE" punkty HP na: "COL_DBLUE"%d", nick(targetid), targetid, hp);
	return 1;
}


CMD:tiger(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /tiger [targetid]");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest zalogowany.");
	gracz[targetid][stamina] = 100;
	HUD_UpdateSTAMINA(targetid);
	mq_format("UPDATE `Konta` SET `stamina`='%d' WHERE `id`='%d';", gracz[targetid][stamina], gracz[targetid][UID]);
	mq_send("QUpdateStamina");
	SendClientMessageEx(playerid, -1, "Zregenerowałeś stamine graczowi: "COL_BLUE"%s (%d)"COL_WHITE".", nick(targetid), targetid);
	return 1;
}

CMD:setweather(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 3) return 0;
	new pogodaid;
	if(sscanf(params,"d", pogodaid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /setweather [pogoda]");
	if(pogodaid < 0) return Error(playerid, "ID pogody nie może być mniejsze niż 0.");
	if(pogodaid > 1000) return Error(playerid, "ID pogody nie może być większe niż 1000.");
	serwer[pogoda] = pogodaid;
	SendClientMessageEx(playerid, -1, "Ustawiłeś ID pogody na: "COL_GREEN"%d", serwer[pogoda]);
	return 1;
}
/*
CMD:settime(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 3) return 0;
	new godzinaid;
	if(sscanf(params,"d", godzinaid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /settime [godzina]");
	switch(godzinaid)
	{
		case 0..23:
		{
			SendClientMessageEx(playerid, -1, "Ustawiłeś czas na: "COL_GREEN"%02d:00", serwer[godzina]);
		}
		default:
		{
			Error(playerid, "Podana godzina musi się mieścić od 0 do 23.");
		}
	}
	return 1;
}
*/
CMD:setmapper(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 3) return 0;
	new targetid, lvl;
	if(sscanf(params,"dd", targetid, lvl)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /setmapper [targetid] [poziom]");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest zalogowany.");
	if(lvl == 0 || lvl == 2 || lvl == 3)
	{
		gracz[targetid][MapperLvl] = lvl;
		SetPVarInt(targetid, "cache_mapperlvl", gracz[playerid][MapperLvl]);
		mq_format("UPDATE`Konta` SET `MapperLvl`='%d' WHERE `id`='%d';", gracz[targetid][MapperLvl], gracz[targetid][UID]);
		mq_send("QMapper");
		SendClientMessageEx(playerid, -1, "Zmieniłeś poziom mappera dla gracza: "COL_BLUE"%s (%d)"COL_WHITE" na: "COL_DBLUE"%d", nick(targetid), targetid, lvl);
	}
	else Error(playerid, "Dostępne poziomy: 2,3");
	return 1;
}
//***************************************************************SPEC MODE
CMD:spec(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /spec [targetid]");
	if(targetid == playerid) return Error(playerid, "Nie możesz specować samego siebie.");
	if(!IsPlayerConnected(targetid)) return Error(playerid, "Gracz nie jest połączony.");
	new target_state = GetPlayerState(targetid);
	if(GetPlayerState(targetid) == PLAYER_STATE_SPECTATING) return Error(playerid, "Ten gracz nie istnieje na mapie.");
	new bool:spec_success = false;
	new bool:while_spec_mode = false;
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) while_spec_mode = true;
	gracz[playerid][last_skin] = GetPlayerSkin(playerid);
	if(target_state == PLAYER_STATE_ONFOOT) 
	{
		if(!while_spec_mode) TogglePlayerSpectating(playerid, 1);
		PlayerSpectatePlayer(playerid, targetid);
		spec_success = true;
	}
	else if(GetPlayerVehicleID(targetid) != 0)
	{
		if(!while_spec_mode) TogglePlayerSpectating(playerid, 1);
		PlayerSpectateVehicle(playerid, GetPlayerVehicleID(targetid));
		spec_success = true;
	}
	else return Error(playerid, "W tym momencie tego gracza nie możesz obserwować. Spróbuj później.");
	if(spec_success) 
	{
		if(!while_spec_mode) 
		{
			SetSpawnInfo(playerid, 0, gracz[playerid][Skin], gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], gracz[playerid][PosR], 0, 0, 0, 0, 0, 0);
			gracz[playerid][admin_spec_myvw] = GetPlayerVirtualWorld(playerid);
			gracz[playerid][admin_spec_myint] = GetPlayerInterior(playerid);
		}

		SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
		SetPlayerInterior(playerid, GetPlayerInterior(targetid));

		gracz[playerid][admin_spec_targetid] = targetid;
		gracz[playerid][admin_spec_target_laststate] = target_state;

		gracz[playerid][admin_spec_enabled] = true;

		SendClientMessageEx(playerid, -1, "Specujesz gracza: "COL_BLUE"%s (%d)"COL_WHITE" (IP: "COL_RED"%s"COL_WHITE")", nick(targetid), targetid, playerip(targetid));
		
		if(!while_spec_mode)  Info(playerid, ""COL_RED"/specoff"COL_WHITE" - Aby zakończyć obserwacje.");
	}
	else Error(playerid, "Wystąpił nieoczekiwany błąd, powiadom programistę skryptu.");
	return 1;
}

CMD:specoff(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING || !gracz[playerid][admin_spec_enabled]) return Error(playerid, "Nie jesteś podczas specowania.");
	TogglePlayerSpectating(playerid, 0);
	SetPlayerVirtualWorld(playerid, gracz[playerid][admin_spec_myvw]);
	SetPlayerInterior(playerid, gracz[playerid][admin_spec_myint]);
	SetSpawnInfo(playerid, 0, gracz[playerid][Skin], GetPVarFloat(playerid, "spawn_X"), GetPVarFloat(playerid, "spawn_Y"), GetPVarFloat(playerid, "spawn_Z"), GetPVarFloat(playerid, "spawn_R"), 0, 0, 0, 0, 0, 0);
	AdminSpec_Hide(playerid);
	gracz[playerid][admin_spec_enabled] = false;
	LeftNotifyShow(playerid, "Admin Panel", "Opuszczono tryb obserwacji.", LN_RED);
	SetPlayerSkin(playerid, gracz[playerid][last_skin]);
	return 1;
}

task Process_Spectator(playerid)
{
	if(gracz[playerid][admin_duty] < 1) return 1;
	if(gracz[playerid][admin_spec_enabled])
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
		{
			new targetid = gracz[playerid][admin_spec_targetid];
			if(IsPlayerConnected(targetid))
			{
				if(GetPlayerVirtualWorld(targetid) != GetPlayerVirtualWorld(playerid)) SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
				if(GetPlayerInterior(targetid) != GetPlayerInterior(playerid)) SetPlayerInterior(playerid, GetPlayerInterior(targetid));
				new bool:camera_bug = false;
				new Float:cPos[3];
				GetPlayerCameraPos(playerid, cPos[0], cPos[1], cPos[2]);
				if(GetDistanceBetweenPoints(cPos[0], cPos[1], cPos[2], 50.0, 50.0, 50.0) < 5.0) camera_bug = true;
				if(camera_bug) GameTextForPlayer(playerid, "~g~~h~~h~CZEKAJ...~n~PROBUJE PRZYWROCIC OBRAZ :D",  1000, 4);
				if(gracz[playerid][admin_spec_target_laststate] != GetPlayerState(targetid) || camera_bug)
				{
					if(GetPlayerState(targetid) == PLAYER_STATE_ONFOOT) 
					{
						PlayerSpectatePlayer(playerid, targetid);
						gracz[playerid][admin_spec_target_laststate] = GetPlayerState(targetid);
					}
					else if(GetPlayerVehicleID(targetid) != 0)
					{
						PlayerSpectateVehicle(playerid, GetPlayerVehicleID(targetid));
						gracz[playerid][admin_spec_target_laststate] = GetPlayerState(targetid);
					}
				}
				new strSpecInfo[1024];
				format(strSpecInfo, 1024, "~n~~w~Nick: ~r~%s ~b~# ~w~Ping: ~r~%d ms ~b~# ~w~HP: ~r~%d %% ~b~# ~w~Kasa: ~g~%d$ ~b~# ~w~Score: ~r~%d ~b~# ~w~Frakcja: ~r~%s ~b~# ~w~Predkosc: ~r~%d km/h~n~~r~~h~~h~Uzyj przyciskow myszy, aby zmienic gracza.", nick(targetid), GetPlayerPing(targetid), gracz[targetid][HP], Money(targetid), GetPlayerScore(targetid), GetFractionNameEx(gracz[targetid][frakcja]), gracz[targetid][opu_speed]);
				AdminSpec_Show(playerid, strSpecInfo);
			}
			else
			{
				TogglePlayerSpectating(playerid, 0);
				SetPlayerVirtualWorld(playerid, gracz[playerid][admin_spec_myvw]);
				SetPlayerInterior(playerid, gracz[playerid][admin_spec_myint]);
				SetSpawnInfo(playerid, 0, gracz[playerid][Skin], GetPVarFloat(playerid, "spawn_X"), GetPVarFloat(playerid, "spawn_Y"), GetPVarFloat(playerid, "spawn_Z"), GetPVarFloat(playerid, "spawn_R"), 0, 0, 0, 0, 0, 0);
				AdminSpec_Hide(playerid);
				gracz[playerid][admin_spec_enabled] = false;
				LeftNotifyShow(playerid, "Admin Panel", "Opuszczono tryb obserwacji. Gracz sie rozlaczyl.", LN_RED);
			}
		}
	}
	return 1;
}

stock SendSignalDisconnectAdminSpec(playerid)
{
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][admin_spec_targetid] == playerid)
		{
			if(gracz[p][admin_spec_enabled])
			{
				if(GetPlayerState(p) == PLAYER_STATE_SPECTATING)
				{
					TogglePlayerSpectating(p, 0);
					SetPlayerVirtualWorld(p, gracz[p][admin_spec_myvw]);
					SetPlayerInterior(p, gracz[p][admin_spec_myint]);
					SetSpawnInfo(p, 0, gracz[p][Skin], GetPVarFloat(p, "spawn_X"), GetPVarFloat(p, "spawn_Y"), GetPVarFloat(p, "spawn_Z"), GetPVarFloat(p, "spawn_R"), 0, 0, 0, 0, 0, 0);
					AdminSpec_Hide(p);
					gracz[p][admin_spec_enabled] = false;
					LeftNotifyShow(p, "Admin Panel", "Opuszczono tryb obserwacji. Gracz sie rozlaczyl.", LN_RED);
				}
			}
		}
	}
	return 1;
}

stock Spec_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(gracz[playerid][admin_duty] < 1) return 1;
	if(gracz[playerid][admin_spec_enabled])
	{
		if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING)
		{
			if(PRESSED(KEY_HANDBRAKE) || PRESSED(KEY_FIRE))
			{
				if(PRESSED(KEY_FIRE))//lewy - wcześniej
				{
					new find_previous[2];
					find_previous[0] = -1;//playerid
					find_previous[1] = -1;//state
					//szukanie poprzedniego gracza ---
					for(new p = PlayerPoolSize(); p != -1; p--)
					{
						if(p == playerid) continue;
						if(!IsPlayerConnected(p)) continue;
						if(GetPlayerState(p) == PLAYER_STATE_SPECTATING) continue;
						if(p < gracz[playerid][admin_spec_targetid])
						{
							if(GetPlayerState(p) == PLAYER_STATE_ONFOOT) 
							{
								find_previous[0] = p;
								find_previous[1] = 1;
								break;
							}
							else if(GetPlayerVehicleID(p) != 0)
							{
								find_previous[0] = p;
								find_previous[1] = 2;
								break;
							}
						}
					}
					if(find_previous[0] != -1)
					{
						if(find_previous[1] == 1)
						{
							new targetid = find_previous[0];
							PlayerSpectatePlayer(playerid, targetid);
							SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
							SetPlayerInterior(playerid, GetPlayerInterior(targetid));
							gracz[playerid][admin_spec_targetid] = targetid;
							gracz[playerid][admin_spec_target_laststate] = GetPlayerState(targetid);
							SendClientMessageEx(playerid, -1, "Specujesz gracza: "COL_BLUE"%s (%d)"COL_WHITE" (IP: "COL_RED"%s"COL_WHITE")", nick(targetid), targetid, playerip(targetid));
						}
						else if(find_previous[1] == 2)
						{
							new targetid = find_previous[0];
							PlayerSpectateVehicle(playerid, GetPlayerVehicleID(targetid));
							SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
							SetPlayerInterior(playerid, GetPlayerInterior(targetid));
							gracz[playerid][admin_spec_targetid] = targetid;
							gracz[playerid][admin_spec_target_laststate] = GetPlayerState(targetid);
							SendClientMessageEx(playerid, -1, "Specujesz gracza: "COL_BLUE"%s (%d)"COL_WHITE" (IP: "COL_RED"%s"COL_WHITE")", nick(targetid), targetid, playerip(targetid));
						}
					}
				}
				else if(PRESSED(KEY_HANDBRAKE))//prawy - dalej
				{
					new find_next[2];
					find_next[0] = -1;//playerid
					find_next[1] = -1;//state
					//szukanie nastepnego gracza +++
					for(new p = PlayerPoolSize(); p != -1; p--)
					{
						if(p == playerid) continue;
						if(!IsPlayerConnected(p)) continue;
						if(GetPlayerState(p) == PLAYER_STATE_SPECTATING) continue;
						if(p > gracz[playerid][admin_spec_targetid])
						{
							if(GetPlayerState(p) == PLAYER_STATE_ONFOOT) 
							{
								find_next[0] = p;
								find_next[1] = 1;
								break;
							}
							else if(GetPlayerVehicleID(p) != 0)
							{
								find_next[0] = p;
								find_next[1] = 2;
								break;
							}
						}
					}
					if(find_next[0] != -1)
					{
						if(find_next[1] == 1)
						{
							new targetid = find_next[0];
							PlayerSpectatePlayer(playerid, targetid);
							SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
							SetPlayerInterior(playerid, GetPlayerInterior(targetid));
							gracz[playerid][admin_spec_targetid] = targetid;
							gracz[playerid][admin_spec_target_laststate] = GetPlayerState(targetid);
							SendClientMessageEx(playerid, -1, "Specujesz gracza: "COL_BLUE"%s (%d)"COL_WHITE" (IP: "COL_RED"%s"COL_WHITE")", nick(targetid), targetid, playerip(targetid));
						}
						else if(find_next[1] == 2)
						{
							new targetid = find_next[0];
							PlayerSpectateVehicle(playerid, GetPlayerVehicleID(targetid));
							SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
							SetPlayerInterior(playerid, GetPlayerInterior(targetid));
							gracz[playerid][admin_spec_targetid] = targetid;
							gracz[playerid][admin_spec_target_laststate] = GetPlayerState(targetid);
							SendClientMessageEx(playerid, -1, "Specujesz gracza: "COL_BLUE"%s (%d)"COL_WHITE" (IP: "COL_RED"%s"COL_WHITE")", nick(targetid), targetid, playerip(targetid));
						}
					}
				}
			}
		}
	}
	return 1;
}

CMD:respawn(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	if(serwer[respawn_inprogress]) return Error(playerid, "W tym momencie trwa już procedura respawnu.");
	serwer[respawn_inprogress] = true;
	format(serwer[respawn_adminnick], 24, "%s", nick(playerid));
	SendClientMessageToAllEx(0x00FF00FF, "[RESPAWN] "COL_LIME"Za "COL_RED"30 sekund"COL_LIME", wszystkie pojazdy nieużywane dłużej niż "COL_RED"%d min"COL_LIME" zostaną zrespawnowane.", VEHI_GLOBALRESPTIME/60);
	SetTimer("AdminRespawnAllVehicles", 1000*30, false);
	return 1;
}

task AdminRespawnAllVehicles()
{
	new count_respawn_vehicles;
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		if(pojazd[v][v_model] == 0) continue;
		if(RespawnVehicle(v)) count_respawn_vehicles++;
	}
	serwer[respawn_inprogress] = false;
	SendClientMessageToAllEx(0x00FF00FF, "[RESPAWN] "COL_LIME"Zrespawnowano "COL_RED"%d pojazdów"COL_LIME". Respawn wykonał "COL_RED"%s"COL_LIME".", count_respawn_vehicles, serwer[respawn_adminnick]);
	return 1;
}

CMD:godofcar(playerid, params[])
{ 
	if(gracz[playerid][admin_duty] < 1) return 0;
	if(gracz[playerid][admin_godofcar])
	{
		LeftNotifyShow(playerid, "Admin Panel", "Opusciles tryb ~r~God of Car~w~. Oznacza to, ze Twoja uprawnienia do pojazdow sa standardowe.", LN_RED, 25);
		gracz[playerid][admin_godofcar] = false;
	}
	else
	{
		LeftNotifyShow(playerid, "Admin Panel", "Aktywowales tryb ~n~~r~God of Car~w~. Od teraz mozesz prowadzic kazdy pojazd frakcyjny i wszystkie pojazdy graczy.", LN_RED, 25);
		gracz[playerid][admin_godofcar] = true;
	}
	return 1;
}

CMD:unspawn(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new vehicleid = GetPlayerVehicleID(playerid);
	if(vehicleid == 0) return Error(playerid, "Musisz znajdować się w pojeździe.");
	new strInfo[144];
	format(strInfo, 144, "Zrespawnowałeś pojazd "COL_RED"%s "COL_WHITE"("COL_GREEN"UID: %d"COL_WHITE").", GetVehicleName(pojazd[vehicleid][v_model]), pojazd[vehicleid][v_id]);
	RespawnVehicle(vehicleid, true);
	Info(playerid, strInfo);
	return 1;
}

CMD:ann(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 2) return 0;
	new time, annText[144];
	if(sscanf(params,"ds[144]", time, annText)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /ann [sekundy] [tekst]");
	if(time < 1) return Error(playerid, "Czas nie może być krótszy niż 1 sekund.");
	if(time > 15) return Error(playerid, "Czas nie może być dłuższy niż 15 sekund.");
	GameTextForAll(annText, 1000*time, 4);
	return 1;
}

CMD:cc(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	ClearChatAll();
	SendClientMessageToAllEx(0x00FF00FF, "[CZAT] "COL_RED"%s "COL_LIME"wyczyścił czat.", nick(playerid));
	return 1;
}

CMD:frakcjaset(playerid,params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	if(IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Jesteś na służbie w frakcji.");
	new frakcjaid;
	if(sscanf(params,"d", frakcjaid))
	{
		SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /frakcjaset [idfrakcji]");
		SendClientMessage(playerid, -1, ""COL_GREY"ID FRAKCJI: 0 - brak, 1 - Policja, 2 - Straż Graniczna, 3 - Ratownictwo, 4 - Pomoc Drogowa, 5 - TAXI, 6 - Mafia.");
		return 1;	
	}
	if(frakcjaid < 0 || frakcjaid > 6) return Error(playerid, "Błędne ID frakcji.");
	if(frakcjaid > 0)
	{
		gracz[playerid][frakcja] = frakcjaid;
		gracz[playerid][frakcja_permlvl] = 1;
	}
	else
	{
		gracz[playerid][frakcja] = 0;
		gracz[playerid][frakcja_permlvl] = 0;
	}
	UpdatePlayerColor(playerid);
	SendClientMessageEx(playerid, -1, "Zmieniłeś swoją frakcje na: %s", GetFractionName(gracz[playerid][frakcja], true));
	return 1;
}


CMD:makeleader(playerid,params[])
{
	if(gracz[playerid][admin_duty] < 2) return 0;
	new targetid, frakcjaid;
	if(sscanf(params,"dd", targetid, frakcjaid))
	{
		SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /makeleader [idgracza] [idfrakcji]");
		SendClientMessage(playerid, -1, ""COL_GREY"ID FRAKCJI: 1 - Policja, 2 - Straż Graniczna, 3 - Ratownictwo, 4 - Pomoc Drogowa, 5 - TAXI, 6 - Mafia.");
		return 1;	
	}
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest zalogowany.");
	if(IsPlayerOnDutyFraction(targetid)) return Error(playerid, "Ten gracz jest na służbie w innej frakcji.");
	if(frakcjaid < 1 || frakcjaid > 6) return Error(playerid, "Błędne ID frakcji.");
	//sekcja offline - usuwanie starego lidera frakcji
	mq_format("UPDATE `Konta` SET `frakcja`='0', `frakcja_permlvl`='0', `frakcja_tytul`='Bezrobotny', `frakcja_wyplata`='0', `frakcja_totalduty`='0' WHERE `frakcja`='%d' AND `frakcja_permlvl`='2';", frakcjaid);
	mysql_query(g_SQL, mQuery, false);//usuwanie starego lidera
	//jeśli aktualny lider jest online...
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][frakcja] == frakcjaid)
			{
				if(gracz[p][frakcja_permlvl] == 2)
				{
					gracz[p][frakcja] = 0;
					gracz[p][frakcja_onduty] = 0;
					gracz[p][frakcja_permlvl] = 0; 
					format(gracz[p][frakcja_tytul], 24, "Bezrobotny");
					gracz[p][frakcja_totalduty] = 0;
					GameTextForPlayer(p, "~r~ZOSTALES ZWOLNIONY",  5000, 0);
					SetPlayerSkin(p, gracz[p][Skin]);//usuwa z duty
					UpdatePlayerColor(p);
					ResetPlayerWeapons(p);
					break;
				}
			}
		}
	}
	//zatrudnianie nowego lidera
	gracz[targetid][frakcja] = frakcjaid;
	gracz[targetid][frakcja_permlvl] = 2;
	format(gracz[targetid][frakcja_tytul], 24, "Lider");
	gracz[playerid][frakcja_totalduty] = 0;
	SavePlayerFractionData(targetid);
	UpdatePlayerColor(targetid);
	SendClientMessageEx(playerid, -1, "Nadałeś graczowi "COL_ORANGE"%s"COL_WHITE" lidera frakcji: %s"COL_WHITE". "COL_RED"Stary lider został usunięty!!!", nick(targetid), GetFractionName(gracz[targetid][frakcja], true));
	SendClientMessageEx(targetid, COLOR_RED, "Otrzymałeś lidera frakcji: %s", GetFractionName(gracz[targetid][frakcja], true));
	return 1;
}

CMD:delleader(playerid,params[])
{
	if(gracz[playerid][admin_duty] < 2) return 0;
	new frakcjaid;
	if(sscanf(params,"d", frakcjaid))
	{
		SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /delleader [idfrakcji]");
		SendClientMessage(playerid, -1, ""COL_GREY"ID FRAKCJI: 1 - Policja, 2 - Straż Graniczna, 3 - Ratownictwo, 4 - Pomoc Drogowa, 5 - TAXI, 6 - Mafia.");
		return 1;	
	}
	if(frakcjaid < 1 || frakcjaid > 6) return Error(playerid, "Błędne ID frakcji.");
	//sekcja offline - usuwanie starego lidera frakcji
	mq_format("UPDATE `Konta` SET `frakcja`='0', `frakcja_permlvl`='0', `frakcja_tytul`='Bezrobotny', `frakcja_wyplata`='0' WHERE `frakcja`='%d' AND `frakcja_permlvl`='2';", frakcjaid);
	mysql_query(g_SQL, mQuery, false);//usuwanie starego lidera
	//jeśli aktualny lider jest online...
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][frakcja] == frakcjaid)
			{
				if(gracz[p][frakcja_permlvl] == 2)
				{
					gracz[p][frakcja] = 0;
					gracz[p][frakcja_onduty] = 0;
					gracz[p][frakcja_permlvl] = 0; 
					format(gracz[p][frakcja_tytul], 24, "Bezrobotny");
					GameTextForPlayer(p, "~r~ZOSTALES ZWOLNIONY",  5000, 0);
					SetPlayerSkin(p, gracz[p][Skin]);//usuwa z duty
					UpdatePlayerColor(p);
					ResetPlayerWeapons(p);
					break;
				}
			}
		}
	}
	return 1;
}

CMD:tps(playerid,params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new strTeleports[1024];
	strcat(strTeleports, ""COL_RED"1."COL_WHITE" Spawn.");
	strcat(strTeleports, "\n"COL_RED"2."COL_WHITE" Baza: Policja.");
	strcat(strTeleports, "\n"COL_RED"3."COL_WHITE" Baza: Straż Graniczna.");
	strcat(strTeleports, "\n"COL_RED"4."COL_WHITE" Baza: Ratownictwo.");
	strcat(strTeleports, "\n"COL_RED"5."COL_WHITE" Baza: Pomoc Drogowa.");
	strcat(strTeleports, "\n"COL_RED"6."COL_WHITE" Baza: TAXI.");
	strcat(strTeleports, "\n"COL_RED"7."COL_WHITE" Baza: Mafia Paliwowa.");
	strcat(strTeleports, "\n"COL_RED"8."COL_WHITE" Interiory domków.");
	strcat(strTeleports, "\n"COL_RED"9."COL_WHITE" Park rozrywki.");
	strcat(strTeleports, "\n"COL_RED"10."COL_WHITE" Piłka nożna.");
	strcat(strTeleports, "\n"COL_RED"11."COL_WHITE" Koszykówka.");
	strcat(strTeleports, "\n"COL_RED"12."COL_WHITE" Mapa ASG.");
	Dialog_Show(playerid, ADMINTP, DIALOG_STYLE_LIST, "Teleporty", strTeleports, "Wybierz", "Anuluj");
	return 1;
}

Dialog:ADMINTP(playerid, response, listitem, inputtext[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	if(!response) return 1;
	switch(listitem)
	{
		case 0://Spawn
		{
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);
			SetPlayerPos(playerid, GetPVarFloat(playerid, "spawn_X"), GetPVarFloat(playerid, "spawn_Y"), GetPVarFloat(playerid, "spawn_Z"));
		}
		case 1..6://Bazy frakcji
		{
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);
			FreezeLoadObject(playerid, fractions[listitem][fr_dutyX], fractions[listitem][fr_dutyY], fractions[listitem][fr_dutyZ]);
		}
		case 7://Interiory domków
		{
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);
			FreezeLoadObject(playerid, 2333.2173,1286.1268,1704.3627);
		}
		case 8:
		{
			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);
			FreezeLoadObject(playerid, XYZ_LUNAPARK);
		}
		case 9:
		{
			SetPlayerVirtualWorld(playerid, LUNAPARK_VWOFFSET);
			SetPlayerInterior(playerid, 10);
			FreezeLoadObject(playerid, 2706.9819,-1802.2231,422.8280);
		}
		case 10:
		{
			SetPlayerVirtualWorld(playerid, LUNAPARK_VWOFFSET);
			SetPlayerInterior(playerid, 10);
			FreezeLoadObject(playerid, 3761.4827,-1781.2800,426.5665);
		}
		case 11:
		{
			ASG_OnPlayerSpawn(playerid);
		}
	}
	SendClientMessageEx(playerid, -1, ""COL_BLUE"Teleportowałeś się do: "COL_RED"%s", inputtext);
	return 1;
}

CMD:getitem(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	new itemid, count;
	if(sscanf(params,"dd", itemid, count)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /getitem [itemid] [count]");
	CreateItemForPlayer(playerid, itemid, count);
	SendClientMessageEx(playerid, -1, "Próba dodania: "COL_GREEN"%s"COL_EASY" [ilosc: %d]", ItemName[itemid], count);
	return 1;
}

CMD:setpos(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	new Float:gotoPos[3];
	if(sscanf(params,"p<,>fff", gotoPos[0], gotoPos[1], gotoPos[2])) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /setpos x,y,z");
	SetPlayerPos(playerid,  gotoPos[0], gotoPos[1], gotoPos[2]);
	return 1;
}

CMD:restart(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	new gmx_time, gmx_reason[128];
	if(sscanf(params,"ds[128]",  gmx_time, gmx_reason)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /restart [za ile sekund] [powód]");
	format(serwer[reason_restart], 32, "%s", gmx_reason);
	serwer[cooldown_restart] = gmx_time;
	SendClientMessageToAllEx(-1, ""COL_RED"-|{fb9800} Za "COL_WHITE"%d{fb9800} sekund nastąpi restart serwera. Powód: "COL_WHITE"%s{fb9800} "COL_RED"|-", serwer[cooldown_restart], serwer[reason_restart]);
	return 1;
}

CMD:saloncars(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	GenererateCarSalonCarRotation();
	DoneInfo();
	return 1;
}

CMD:sampsong(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	PlayerPlaySound(playerid, strval(params), 0, 0, 0);
	return 1;
}

CMD:unadmin(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 3) return 0;
	new pin, targetid;
	if(sscanf(params,"dd",  pin, targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /unadmin [sekretny PIN] [targetid]");
	if(pin != 6969) return Error(playerid, "Zły pin.");
	if(gracz[targetid][AdminLevel] == 0) return Error(playerid, "Ten gracz nie jest adminem.");
	gracz[targetid][admin_duty] = 0;
	gracz[targetid][AdminLevel] = 0;
	mq_format("UPDATE `Konta` SET `AdminLevel`='0' WHERE `id`='%d';", gracz[targetid][UID]);
	mq_send("QUnAdmin");
	Info(playerid, "Gotowe.");
	return 1;
}

CMD:cheatmoney(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return Error(playerid, "xD.");
	new pin, money;
	if(sscanf(params,"dd",  pin, money)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /cheatmoney p m");
	if(pin != 4545) return Error(playerid, "xDD.");
	SetMoney(playerid, money);
	SendClientMessageEx(playerid, 0xFF0000FF, "[HAJSY] "COL_GREY"Wyciągnąłeś "COL_GREEN"%d "COL_GREY"dolców z dupy.", money);
	return 1;
}

new __npgt = 0;
CMD:npgt(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	new Float:px, Float:py, Float:pz;
	GetPlayerPos(playerid, px, py, pz);
	mq_format("INSERT INTO `gps_customnodes` (`x`, `y`, `z`, `connected`, `comment`) VALUES ('%f', '%f', '%f', '%d', '%s');", px, py, pz, __npgt+2, params);
	new Cache:result = mysql_query(g_SQL, mQuery);
	__npgt = cache_insert_id();
	cache_delete(result);
	DoneInfo();
	return 1;
}
/*
CMD:nodegpsprint(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	new Float:nX, Float:nY, Float:nZ, strnode[128];
	for(new n; n < MAX_RCNODES; n++)
	{
		if(NodeExists(n))
		{
			GetNodePos(n, nX, nY, nZ);
			format(strnode, 128, "[GPS NID: {FF0000}%d{00FF00}]", n);
			CreateDynamic3DTextLabel(strnode, 0x00FF00FF, nX, nY, nZ, 100.0);
			//printf("GPS NODE [%d] %f %f %f", n, nX, nY, nZ);
		} 
	}
	DoneInfo();
	return 1;
}
*/
CMD:delobjects(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	Streamer_DestroyAllVisibleItems(playerid, STREAMER_TYPE_OBJECT);
	DoneInfo();
	return 1;
}

CMD:leavetest(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	ShowJoinLeaveTD(playerid, 1, 1, 23);
	DoneInfo();
	return 1;
}

CMD:jointest(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	ShowJoinLeaveTD(playerid, 0, 1, 23);
	DoneInfo();
	return 1;
}

CMD:createhome(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 3) return Error(playerid, "Brak uprawnień.");
	new pin, interiorid, price;
	if(sscanf(params,"ddd",  pin, interiorid, price)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /createhome [pin] [interiorid] [cena]");
	if(pin != 333) return Error(playerid, "Zły pin.");
	if(interiorid < 0) return Error(playerid, "Najniższy interiorid: 0.");
	new strInfo[512];
	if(interiorid > sizeof(house_customint)-1)
	{
		format(strInfo, 512, "Najwyższy interiorid: %d", sizeof(house_customint)-1);
		Error(playerid, strInfo);
		return 1;
	}
	if(price < 200000) return Error(playerid, "Cena minimalna to 200000$.");
	if(price > 50000000) return Error(playerid, "Cena maksymalna to 50000000$.");
	new hid = GetFreeHouseID();
	if(hid == -1) return Error(playerid, "Przekroczony limit domków na serwerze.");
	new Float:playerPos[3];
	GetPlayerPos(playerid, playerPos[0], playerPos[1], playerPos[2]);
	house[hid][h_owneruid] = 0;
	house[hid][h_extX] = playerPos[0];
	house[hid][h_extY] = playerPos[1];
	house[hid][h_extZ] = playerPos[2];
	house[hid][h_intX] = house_customint[interiorid][0];
	house[hid][h_intY] = house_customint[interiorid][1];
	house[hid][h_intZ] = house_customint[interiorid][2];
	house[hid][h_interior] = 10;
	house[hid][h_price] = price;
	house[hid][h_expire] = 0;
	house[hid][h_open] = 1;
	mq_format("INSERT INTO `domki` (`owneruid`, `extX`, `extY`, `extZ`, `intX`, `intY`, `intZ`, `interior`, `price`, `expire`, `open`) VALUES ");
	mq_format("%s('%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d');", mQuery, house[hid][h_owneruid], house[hid][h_extX], house[hid][h_extY], house[hid][h_extZ], house[hid][h_intX], house[hid][h_intY], house[hid][h_intZ], house[hid][h_interior], house[hid][h_price], house[hid][h_expire], house[hid][h_open]);
	mq_send("QCreateHome", "d", hid);
	Info(playerid, ""COL_RED"Stworzyłeś domek!");
	return 1;
}

task QCreateHome(hid)
{
	house[hid][h_id] = cache_insert_id();
	new strHouse[1024];
	format(strHouse, 1024, ""COL_GREEN"« "COL_BLUE"POSIADŁOŚĆ"COL_GREEN"»");
	format(strHouse, 1024, "%s\n"COL_GREY"UID: "COL_DRVONLINE"%d", strHouse, house[hid][h_id]);
	format(strHouse, 1024, "%s\n"COL_GREY"Cena: "COL_GREEN"%d$", strHouse, house[hid][h_price]);
	house[hid][h_pickup] = CreateDynamicPickup(1273, 1, house[hid][h_extX], house[hid][h_extY], house[hid][h_extZ]);
	house[hid][h_icon] = CreateDynamicMapIcon(house[hid][h_extX], house[hid][h_extY], house[hid][h_extZ], 31, 0, .streamdistance = 200.0, .style = MAPICON_LOCAL);
	format(strHouse, 1024, "%s\n"COL_RED"(("COL_GREEN"PPM "COL_GREY"- Interakcja"COL_RED"))", strHouse);
	house[hid][h_text3dext] = CreateDynamic3DTextLabel(strHouse, -1, house[hid][h_extX], house[hid][h_extY], house[hid][h_extZ], 10.0);
	house[hid][h_text3dint] = CreateDynamic3DTextLabel(strHouse, -1, house[hid][h_intX], house[hid][h_intY], house[hid][h_intZ], 10.0, .worldid = HOUSE_VWOFFSET+hid);
	return 1;
}

CMD:testhomeint(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 3) return Error(playerid, "Brak uprawnień.");
	new pin, interiorid;
	if(sscanf(params,"dd",  pin, interiorid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /testhomeint [pin] [interiorid]");
	if(pin != 333) return Error(playerid, "Zły pin.");
	if(interiorid < 0) return Error(playerid, "Najniższy interiorid: 0.");
	new strInfo[512];
	if(interiorid > sizeof(house_customint)-1)
	{
		format(strInfo, 512, "Najwyższy interiorid: %d", sizeof(house_customint)-1);
		Error(playerid, strInfo);
		return 1;
	}
	SetPlayerPos(playerid, house_customint[interiorid][0], house_customint[interiorid][1], house_customint[interiorid][2]);
	format(strInfo, 512, "Teleportowałeś się do interiorid: %d", interiorid);
	Info(playerid, strInfo);
	return 1;
}

CMD:firmapick(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 3) return Error(playerid, "Brak uprawnień.");
	new cid;
	if(sscanf(params,"d",  cid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /firmapick [id firmy]");
	//musi być na terenie firmy
	if(IsPlayerInRangeOfPoint(playerid, RANGE_COMPANY, company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ]))
	{
		//zmieniamy pozycję w RAM
		GetPlayerPos(playerid, company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ]);
		//usuwamy pickup, 3dtext i ikonkę
		DestroyDynamicPickup(company[cid][cny_pickup]);
		DestroyDynamic3DTextLabel(company[cid][cny_text3d]);
		DestroyDynamicMapIcon(company[cid][cny_icon]);
		//tworzymy na nowo ikonke pickupa i 3dtext
		new strTemp[1024];
		if(company[cid][cny_owneruid] != 0)
		{
			company[cid][cny_pickup] = CreateDynamicPickup(1314, 1, company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ]);
			format(strTemp, 1024, ""COL_GREEN"« "COL_BLUE"SŁUŻBA W FIRMIE - "COL_RED"%s (ID: %d)"COL_GREEN"»\n", company[cid][cny_name], cid);
			format(strTemp, 1024, "%s"COL_GREEN"« "COL_YELLOW"WŁAŚCICIEL: "COL_RED"%s "COL_GREEN"»\n", strTemp, GetPlayerIGName(company[cid][cny_owneruid]));
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_ORANGE"/cduty start"COL_GREY" aby rozpocząć pracę. "COL_RED"•\n", strTemp);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_ORANGE"/cduty stop"COL_GREY" aby zakończyć pracę. "COL_RED"•\n", strTemp);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_ORANGE"/cduty info"COL_GREY" aby sprawdzić status służby. "COL_RED"•\n", strTemp);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_WHITE"/firma"COL_GREY" - panel firmy "COL_RED"•\n", strTemp);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_WHITE"/kontrakt status"COL_GREY" aby sprawdzić stan kontraktu"COL_GREY". "COL_RED"•\n", strTemp);
			company[cid][cny_text3d] = CreateDynamic3DTextLabel(strTemp, -1, company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ], 20.0);
			company[cid][cny_icon] = CreateDynamicMapIcon(company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ], 12, 0, .streamdistance = 300.0, .style = MAPICON_GLOBAL);
		}
		else
		{
			company[cid][cny_pickup] = CreateDynamicPickup(1276, 1, company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ]);
			format(strTemp, 1024, ""COL_RED"»»» "COL_LIME"ZAŁÓŻ FIRMĘ W TYM MIEJSCU (ID: %d) "COL_RED"«««\n", cid);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Cena założenia/utrzymania: "COL_GREEN"%d$ "COL_RED"•\n", strTemp, company[cid][cny_price]);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Opłata należysz uiszczać co: "COL_BLUE"%d dni "COL_RED"•\n", strTemp, COMPANY_KEEPDAYS);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Wpisz "COL_ORANGE"/stworzfirme"COL_GREY" aby założyć firmę na tym terenie. "COL_RED"•\n", strTemp);
			company[cid][cny_text3d] = CreateDynamic3DTextLabel(strTemp, -1, company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ], 20.0);
			company[cid][cny_icon] = CreateDynamicMapIcon(company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ], 16, 0, .streamdistance = 300.0, .style = MAPICON_GLOBAL);
		}
		mq_format("UPDATE `firmy` SET `duty_x`='%f', `duty_y`='%f', `duty_z`='%f' WHERE `id`='%d';", company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ], cid);
		mq_send("QUpdatePickCompany");
		Info(playerid, "Zrobione :)");
	}
	else Error(playerid, "Musisz być na terenie tej firmy aby móc zmienić pozycję pickupa.");
	return 1;
}

CMD:eyeveh(playerid,params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	if(gracz[playerid][admin_eyeveh] == false)
	{
		gracz[playerid][admin_eyeveh] = true;
		SendClientMessage(playerid, COLOR_RED, "/eyeveh: "COL_LIME"Śledzenie dziwnych zachowań pojazdów - ON");
	}
	else
	{
		gracz[playerid][admin_eyeveh] = false;
		SendClientMessage(playerid, COLOR_RED, "/eyeveh: "COL_RED"Śledzenie dziwnych zachowań pojazdów - OFF");
	}
	return 1;
}

stock SendEyeveh(message[])
{
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][admin_eyeveh])
			{
				SendClientMessageEx(p, COLOR_RED, "/eyeveh:"COL_WHITE" %s", message);
			}
		}
	}
	return 1;
}

CMD:eyecmd(playerid,params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	if(gracz[playerid][admin_eyecmd] == false)
	{
		gracz[playerid][admin_eyecmd] = true;
		SendClientMessage(playerid, COLOR_ORANGE, "/eyecmd: "COL_LIME"Podgląd komend - ON");
	}
	else
	{
		gracz[playerid][admin_eyecmd] = false;
		SendClientMessage(playerid, COLOR_ORANGE, "/eyecmd: "COL_RED"Podgląd komend - OFF");
	}
	return 1;
}

stock SendEyecmd(message[])
{
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][admin_eyecmd])
			{
				SendClientMessageEx(p, COLOR_ORANGE, "/eyecmd:"COL_WHITE" %s", message);
			}
		}
	}
	return 1;
}

CMD:vhlgetall(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	if(!VHL_GetAll(playerid)) SendClientMessage(playerid, COLOR_ORANGE, "/vhlgetall: "COL_RED"Nasłuchiwanie serwera - OFF.");
	else SendClientMessage(playerid, COLOR_ORANGE, "/vhlgetall: "COL_LIME"Nasłuchiwanie serwera - ON.");
	return 1;
}


CMD:vhlmute(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid, minutes, reason[128];
	if(sscanf(params,"dds[128]", targetid, minutes, reason)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /vhlmute [targetid] [minuty] [powód]");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest zalogowany.");
	if(gracz[playerid][admin_duty] < gracz[targetid][admin_duty]) return Error(playerid, "Ten gracz to admin o wyższej randze!");
	if(minutes <= 0) return Error(playerid, "Czas kary nie może być krótszy niż 1 minuta.");
	if(minutes > 120) return Error(playerid, "Czas kary nie może być dłuższy niż 120 minut.");
	gracz[targetid][vhl_muted_timestamp] = 60*minutes+gettime();
	mq_format("UPDATE `Konta` SET `vhl_muted_timestamp`='%d' WHERE `id`='%d';", gracz[targetid][vhl_muted_timestamp], gracz[targetid][UID]);
	mq_send("QMuted");
	Interwencja(playerid, targetid, minutes, PENALTY_MUTE_VHL, reason);
	return 1;
}

CMD:vhlunmute(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /vhlunmute [targetid]");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest zalogowany.");
	if(gracz[playerid][admin_duty] < gracz[targetid][admin_duty]) return Error(playerid, "Ten gracz to admin o wyższej randze!");
	if(gracz[targetid][vhl_muted_timestamp] < serwer[time_timestamp]) return Error(playerid, "Ten gracz nie jest uciszony.");
	gracz[targetid][vhl_muted_timestamp] = 0;
	mq_format("UPDATE `Konta` SET `vhl_muted_timestamp`='%d' WHERE `id`='%d';", gracz[targetid][vhl_muted_timestamp], gracz[targetid][UID]);
	mq_send("QMuted");
	Info(playerid, "[czat głosowy]Gracz został odciszony.");
	Info(targetid, "[czat głosowy]Zostałeś/aś odciszony.");
	return 1;
}

CMD:admincar(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new model;
	if(sscanf(params,"d", model)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /admincar [id modelu]");
	if(IsPlayerInAnyVehicle(playerid)) return Error(playerid, "Nie możesz używać tej komendy będąc w pojeździe.");
	new bool:found_model = false;
	for(new v; v < MAX_CARSPEC; v++)
	{
		if(pojazd_spec[v][vspec_model] == model)
		{
			found_model = true;
			break;
		}
	}
	if(model == 577 || model == 553 || model == 519) found_model = true;
	if(found_model == false) return Error(playerid, "Ten pojazd jest niedostępny.");
	new Float:angle;
	GetPlayerFacingAngle(playerid, angle);
	new vehicleid = CreateVehicle(model, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]+1, angle, 1, 1, -1, 1);
	pojazd[vehicleid][v_model] = model;
	GetVehiclePos(vehicleid, pojazd[vehicleid][v_X], pojazd[vehicleid][v_Y], pojazd[vehicleid][v_Z]);
	GetVehicleZAngle(vehicleid, pojazd[vehicleid][v_R]);
	pojazd[vehicleid][v_color][0] = 3;
	pojazd[vehicleid][v_color][1] = 3;
	pojazd[vehicleid][v_paliwo] = 9999;
	if(pojazd[vehicleid][v_paliwo] >= 9999) pojazd[vehicleid][v_paliwo] = GetVehicleFuelSize(pojazd[vehicleid][v_model]);
	if(pojazd[vehicleid][v_paliwo] == 0) pojazd[vehicleid][v_paliwo] = 9999;
	pojazd[vehicleid][v_owner_type] = VEHICLE_PUBLIC;
	pojazd[vehicleid][v_owner] = VO_ADMINVEH;
	SetVehicleParamsEx(vehicleid, 1, 1, 0, 0, 0, 0, 0);
	SetVehicleParamsCarWindows(vehicleid, 1, 1, 1, 1);
	pojazd[vehicleid][v_text3d] = CreateDynamic3DTextLabel("[admincar]", 0x00000000, pojazd[vehicleid][v_X], pojazd[vehicleid][v_Y], pojazd[vehicleid][v_Z]+0.3, 13.0, .attachedvehicle = vehicleid, .testlos = 1);
	new strRanga[64];
	switch(gracz[playerid][admin_duty])
	{
		case 1://Support
		{
			format(strRanga, 128, "\n[Support Team]");
			UpdateDynamic3DTextLabelText(pojazd[vehicleid][v_text3d], 0x00A09EFF, strRanga);
		}
		case 2://Game Master
		{
			format(strRanga, 128, "\n[Game Master]");
			UpdateDynamic3DTextLabelText(pojazd[vehicleid][v_text3d], 0x0052DDFF, strRanga);
		}
		default://Admin
		{
			format(strRanga, 128, "\n[Administrator]");
			UpdateDynamic3DTextLabelText(pojazd[vehicleid][v_text3d], 0xFF0000FF, strRanga);
		}
	}
	PutPlayerInVehicle(playerid, vehicleid, 0);
	//SetVehicleToRespawn(admcarid);
	return 1;
}

CMD:importbackupobjects(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	SendClientMessage(playerid, -1, "Rozpoczynam importowanie...");
	new File:handle = fopen("obiekty_backup.txt", io_read);
	new buf[512];
	new counter;
	new id, model, idgrupa, uid, World, InteriorEx;
	new Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz;
	new mmat;
	while(fread(handle, buf)) 
	{
		if(sscanf(buf, "p<|>ddddddffffffd", id, model, idgrupa, uid, World, InteriorEx, x, y, z, rx, ry, rz, mmat)) return printf("fatalny błąd kurwa!!!!!!");
		mq_format("INSERT INTO `samp_prp`.`Obiekty` (`id`, `model`, `idgrupa`, `uid`, `World`, `InteriorEx`, `x`, `y`, `z`, `rx`, `ry`, `rz`, `mmat`) VALUES ('%d', '%d', '%d', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d');", id, model, idgrupa, uid, World, InteriorEx, x, y, z, rx, ry, rz, mmat);
		//mq_send("QImportObjects");
		printf("%s", mQuery);
		counter++;
	}
	fclose(handle);
	SendClientMessageEx(playerid, -1, "Import zakonczony(%d rekordów)...", counter);
	return 1;
}

CMD:distanceset(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	SetPVarFloat(playerid, "distsetX", gracz[playerid][PosX]);
	SetPVarFloat(playerid, "distsetY", gracz[playerid][PosY]);
	SetPVarFloat(playerid, "distsetZ", gracz[playerid][PosZ]);
	DoneInfo();
	return 1;
}

CMD:distanceget(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	new Float:distset[3];
	distset[0] = GetPVarFloat(playerid, "distsetX");
	distset[1] = GetPVarFloat(playerid, "distsetY");
	distset[2] = GetPVarFloat(playerid, "distsetZ");
	new strResult[32];
	format(strResult, 32, "Odległość: %f", GetDistanceBetweenPoints(gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], distset[0], distset[1], distset[2]));
	Info(playerid, strResult);
	return 1;
}

CMD:napadresettime(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	Info(playerid, "napadresettime - Done!");
	serwer[attack_block_timestamp] = serwer[time_timestamp];
	return 1;
}


CMD:setnickic(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	new targetid, nickic[128];
	if(sscanf(params,"ds[128]", targetid, nickic)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /setnickic [targetid] [Imie_Nazwisko]");
	new bool:dataok = false;
	switch(strlen(nickic))
	{
		case 5..20:
		{
			if(NameValidator(targetid, nickic) == 1)
			{
				SendClientMessageEx(targetid, -1, "(("COL_GREY"Nazwa Twojej postaci: "COL_GREEN"%s"COL_WHITE".))", GetICName(targetid));
				SendClientMessageEx(playerid, -1, "(("COL_GREY"Zmieniłeś nazwe postaci dla gracza %s na: "COL_GREEN"%s"COL_WHITE".))", nick(targetid), GetICName(targetid));
				dataok = true;
			}
			else dataok = false;
		}
		default:
		{
			dataok = false;
		}
	}
	if(dataok == false) Error(playerid, "Nieprawidłowy nick IC.");
	else
	{
		mq_format("UPDATE `Konta` SET `nick_ic`='%s' WHERE `id`='%d';", gracz[targetid][nick_ic], gracz[targetid][UID]);
		mq_send("QUpdateNickIC");
	}
	return 1;
}

CMD:niewidka(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	if(gracz[playerid][aaInvisible] == false)
	{
		gracz[playerid][aaInvisible] = true;
		Info(playerid, ""COL_GREEN"Niewidzialność pod /admins i na mapie włączona.");
	}
	else
	{
		SetPlayerSkin(playerid, GetPlayerSkin(playerid));
		gracz[playerid][aaInvisible] = false;
		Info(playerid, ""COL_RED"Niewidzialność pod /admins i na mapie wyłączona.");
	}
	return 1;
}
new adminskins[] = {20001, 20002, 20003, 20004, 20005, 20006, 20007, 20008};

CMD:adminskin(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	ShowModelSelectionMenuEx(playerid, adminskins, sizeof(adminskins), "Skiny administracji", MSEL_ADMINSKIN, _, _, 0.0);
	return 1;
}

CMD:adminskin2(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	SetPlayerSkin(playerid, strval(params));
	DoneInfo();
	return 1;
}


CMD:askinset(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	gracz[playerid][Plec] = strval(params);
	DoneInfo();
	return 1;
}
/*
CMD:profilerstart(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	Info(playerid, "Profiler_Start - Done!");
	Profiler_Start();
	return 1;
}

CMD:profilerstop(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	Info(playerid, "Profiler_Stop - Done!");
	Profiler_Stop();
	return 1;
}

CMD:profilerdump(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	Info(playerid, "Profiler_Dump - Done!");
	Profiler_Dump();
	return 1;
}
*/
CMD:givems(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	new money, score;
	if(sscanf(params,"dd", money, score)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /givems [money] [score]");
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(!gracz[p][loggedin]) continue;
		GiveMoney(p, money);
		GiveScore(p, score);
	}
	SendClientMessageToAllEx(0xFF0000FF, "%s rozdał/a wszystkim %d kasy i %d score :)", nick(playerid), money, score);
	return 1;
}

CMD:hostname(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	new hname[64];
	if(sscanf(params,"s[128]", hname)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /hname [dopisek do hostname]");
	format(serwer[srv_customhostname], 128, "[0.3DL] Highway Life - %s", hname);
	Info(playerid, serwer[srv_customhostname]);
	return 1;
}

CMD:eventbank(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	new evscore, evmoney;
	if(sscanf(params,"dd", evscore, evmoney)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /eventbank [score] [kasa]");
	serwer[event_max_added_score] = evscore;
	serwer[event_max_added_money] = evmoney;
	new strInfo[128];
	format(strInfo, 128, "EVENT BANK: score: %d, kasa: %d$", serwer[event_max_added_score], serwer[event_max_added_money]);
	Info(playerid, strInfo);
	return 1;
}

CMD:togglechat(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 1) return 0;
	if(serwer[block_global_ooc])
	{
		serwer[block_global_ooc] = false;
		Info(playerid, ""COL_GREEN"Czat globalny OOC odblokowany.");
	}
	else
	{
		serwer[block_global_ooc] = true;
		Info(playerid, ""COL_RED"Czat globalny OOC zablokowany.");
	}
	return 1;
}


#define ZONESET_MAXPOINTS 8

enum zonseset_data
{
	Float:zns_X,
	Float:zns_Y,
	zns_targetid,
	zns_objectid,
	Text3D:zns_text3d
};

new zoneset[MAX_PLAYERS][ZONESET_MAXPOINTS][zonseset_data];

CMD:housezone(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 2) return 0;
	if(GetPVarInt(playerid, "cache_setzone_activemode") == 0) Dialog_Show(playerid, SETHOMEZONE, DIALOG_STYLE_LIST, "Tworzenie strefy domku", "Kreator tworzenia strefy domku\nUsuń strefę", "Wybierz", "Anuluj");
	else if(GetPVarInt(playerid, "cache_setzone_activemode") == 1) Dialog_Show(playerid, SETZONEEND, DIALOG_STYLE_LIST, "Tworzenie strefy domku", "Zatwierdź strefę\nAnuluj tworzenie", "Wybierz", "Anuluj");
	else return Error(playerid, "Użyj /companyzone");
	return 1;
}

CMD:companyzone(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 2) return 0;
	if(GetPVarInt(playerid, "cache_setzone_activemode") == 0) Dialog_Show(playerid, SETCMPZONE, DIALOG_STYLE_LIST, "Tworzenie strefy firmy", "Kreator tworzenia strefy firmy\nUsuń strefę", "Wybierz", "Anuluj");
	else if(GetPVarInt(playerid, "cache_setzone_activemode") == 2) Dialog_Show(playerid, SETZONEEND, DIALOG_STYLE_LIST, "Tworzenie strefy firmy", "Zatwierdź strefę\nAnuluj tworzenie", "Wybierz", "Anuluj");
	else return Error(playerid, "Użyj /housezone");
	return 1;
}

Dialog:SETZONEEND(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(GetPVarInt(playerid, "cache_setzone_activemode") == 0) return Error(playerid, "Nie jesteś w trakcie tworzenia strefy.");
	switch(listitem)
	{
		case 0:
		{
			new strPointsData[5000];
			new points_counter;
			for(new d; d < ZONESET_MAXPOINTS; d++)
			{
				if(zoneset[playerid][d][zns_targetid] != 0)
				{
					format(strPointsData, 5000, "%s%f %f ", strPointsData, zoneset[playerid][d][zns_X], zoneset[playerid][d][zns_Y]);
					points_counter += 2;
				}
			}
			if(points_counter < 6) return Error(playerid, "Zbyt mało punktów (minimum 3).");
			if(GetPVarInt(playerid, "cache_setzone_activemode") == 1)//domki
			{
				new houseid = zoneset[playerid][0][zns_targetid];
				if(!IsPlayerInRangeOfPoint(playerid, 50.0, house[houseid][h_extX], house[houseid][h_extY], house[houseid][h_extZ])) return Error(playerid, "Jesteś za daleko od domku.");
				if(house[houseid][h_polygonid] != 0) DestroyDynamicArea(house[houseid][h_polygonid]);
				house[houseid][h_polygoncount] = points_counter;
				new sscanf_format[16];
				new Float:zpolygons[8192];
				format(sscanf_format, 16, "a<f>[%d]", 8192);
				sscanf(strPointsData, sscanf_format, zpolygons);
				house[houseid][h_polygonid] = CreateDynamicPolygon(zpolygons, house[houseid][h_extZ]-5.0, house[houseid][h_extZ]+15.0, points_counter, 0, 0);
				mq_format("UPDATE `domki` SET `polygon_count`='%d', `polygon_data`='%s' WHERE `id`='%d';", points_counter, strPointsData, house[houseid][h_id]);
				mq_send("QUpdateHomeZone");
				CancelCreateZone(playerid);
				UpdateHouseLabel(houseid);
				Info(playerid, "Strefa domku stworzona/zaktualizowana.");
			}
			else if(GetPVarInt(playerid, "cache_setzone_activemode") == 2)//firmy
			{
				new companyid = zoneset[playerid][0][zns_targetid];
				if(!IsPlayerInRangeOfPoint(playerid, 200.0, company[companyid][cny_dutyX], company[companyid][cny_dutyY], company[companyid][cny_dutyZ])) return Error(playerid, "Jesteś za daleko od firmy.");
				if(company[companyid][cny_polygonid] != 0) DestroyDynamicArea(company[companyid][cny_polygonid]);
				company[companyid][cny_polygoncount] = 0;
				new sscanf_format[16];
				new Float:zpolygons[8192];
				format(sscanf_format, 16, "a<f>[%d]", 8192);
				sscanf(strPointsData, sscanf_format, zpolygons);
				company[companyid][cny_polygonid] = CreateDynamicPolygon(zpolygons, company[companyid][cny_dutyZ]-5.0, company[companyid][cny_dutyZ]+15.0, points_counter, 0, 0);
				mq_format("UPDATE `firmy` SET `polygon_count`='%d', `polygon_data`='%s' WHERE `id`='%d';", points_counter, strPointsData, companyid);
				mq_send("QUpdateCompanyZone");
				CancelCreateZone(playerid);
				Info(playerid, "Strefa firmy stworzona/zaktualizowana.");
			}
			else Error(playerid, "Nieoczekiwany błąd.");
		}
		case 1:
		{
			CancelCreateZone(playerid);
			Info(playerid, "Tworzenie strefy zostało anulowane.");
		}
	}
	return 1;
}

Dialog:SETHOMEZONE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			new house_list[2048];
			format(house_list, 2048, "ID Domu\tAktualny właścicie\tStrefa");
			new bool:find = false;
			new listcount;
			for(new h; h < MAX_HOUSES; h++)
			{
				if(house[h][h_id] == 0) continue;
				if(IsPlayerInRangeOfPoint(playerid, 100.0, house[h][h_extX], house[h][h_extY], house[h][h_extZ]))
				{
					format(house_list, 2048, "%s\n%d\t%s\t%s", house_list, house[h][h_id], GetPlayerIGName(house[h][h_owneruid]), (house[h][h_polygonid] == 0 ? ("NIE") : ("TAK")));
					gui_cache[playerid][listcount][0] = h;
					listcount++;
					find = true;
				}
			}
			if(find) Dialog_Show(playerid, SETHZSELECTH, DIALOG_STYLE_TABLIST_HEADERS,  ""COL_RED"•» "COL_WHITE"Tworzenie strefy "COL_RED"«•", house_list, "Wybierz", "Anuluj");
			else Error(playerid, "Nie znaleziono żadnego domu w pobliżu.");
		}
		case 1:
		{
			new house_list[2048];
			format(house_list, 2048, "ID Domu\tAktualny właścicie\tStrefa");
			new bool:find = false;
			new listcount;
			for(new h; h < MAX_HOUSES; h++)
			{
				if(house[h][h_id] == 0) continue;
				if(house[h][h_polygonid] == 0) continue;
				if(IsPlayerInRangeOfPoint(playerid, 100.0, house[h][h_extX], house[h][h_extY], house[h][h_extZ]))
				{
					format(house_list, 2048, "%s\n%d\t%s\t%s", house_list, house[h][h_id], GetPlayerIGName(house[h][h_owneruid]), (house[h][h_polygonid] == 0 ? ("NIE") : ("TAK")));
					gui_cache[playerid][listcount][0] = h;
					listcount++;
					find = true;
				}
			}
			if(find) Dialog_Show(playerid, DELETEHOMEZONE, DIALOG_STYLE_TABLIST_HEADERS,  ""COL_RED"•» "COL_WHITE"Usuwanie strefy "COL_RED"«•", house_list, "Wybierz", "Anuluj");
			else Error(playerid, "Nie znaleziono żadnego domu ze strefą w pobliżu.");
		}
	}
	return 1;
}

Dialog:SETCMPZONE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			new company_list[2048];
			format(company_list, 2048, "ID Firmy\tAktualny właścicie\tStrefa");
			new bool:find = false;
			new listcount;
			for(new c; c < MAX_COMPANY; c++)
			{
				if(company[c][cny_price] == 0) continue;
				if(IsPlayerInRangeOfPoint(playerid, 100.0, company[c][cny_dutyX], company[c][cny_dutyY], company[c][cny_dutyZ]))
				{
					format(company_list, 2048, "%s\n%d\t%s\t%s", company_list, c, GetPlayerIGName(company[c][cny_owneruid]), (company[c][cny_polygonid] == 0 ? ("NIE") : ("TAK")));
					gui_cache[playerid][listcount][0] = c;
					listcount++;
					find = true;
				}
			}
			if(find) Dialog_Show(playerid, SETCOMPZSELECT, DIALOG_STYLE_TABLIST_HEADERS,  ""COL_RED"•» "COL_WHITE"Tworzenie strefy "COL_RED"«•", company_list, "Wybierz", "Anuluj");
			else Error(playerid, "Nie znaleziono żadnej firmy w pobliżu.");
		}
		case 1:
		{
			new company_list[2048];
			format(company_list, 2048, "ID Firmy\tAktualny właścicie\tStrefa");
			new bool:find = false;
			new listcount;
			for(new c; c < MAX_COMPANY; c++)
			{
				if(company[c][cny_price] == 0) continue;
				if(company[c][cny_polygonid] == 0) continue;
				if(IsPlayerInRangeOfPoint(playerid, 200.0, company[c][cny_dutyX], company[c][cny_dutyY], company[c][cny_dutyZ]))
				{
					format(company_list, 2048, "%s\n%d\t%s\t%s", company_list, c, GetPlayerIGName(company[c][cny_owneruid]), (company[c][cny_polygonid] == 0 ? ("NIE") : ("TAK")));
					gui_cache[playerid][listcount][0] = c;
					listcount++;
					find = true;
				}
			}
			if(find) Dialog_Show(playerid, DELETECOMPZONE, DIALOG_STYLE_TABLIST_HEADERS,  ""COL_RED"•» "COL_WHITE"Usuwanie strefy "COL_RED"«•", company_list, "Wybierz", "Anuluj");
			else Error(playerid, "Nie znaleziono żadnej firmy ze strefą w pobliżu.");
		}
	}
	return 1;
}

Dialog:SETHZSELECTH(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new targetid = gui_cache[playerid][listitem][0];
	SetPVarInt(playerid, "cache_setzone_activemode", 1);
	SetPVarInt(playerid, "cache_setzone_target", targetid);
	SetPVarInt(playerid, "cache_setzone_pointid", 0);
	new strInfo[1024];
	format(strInfo, 1024, "Rozpoczęto procedurę wyznaczania terenu domku o ID: %d (%s)", house[targetid][h_id], GetPlayerIGName(house[targetid][h_owneruid]));
	format(strInfo, 1024, "%s\n"COL_WHITE"Aby zaznaczyć teren używaj "COL_BLUE"klawisza Y"COL_WHITE" na załamaniach działki. ", strInfo);
	format(strInfo, 1024, "%s\n"COL_WHITE"Punkty są automatycznie łączone w kolejności jakiej je zaznaczasz, "COL_GREEN"minimalna ilość punktów to 3 (wtedy powstaje krztałt trójkąta)"COL_WHITE".", strInfo);
	format(strInfo, 1024, "%s\n"COL_WHITE"Przykładowo, jeśli teren jest prostokontem, musisz zaznaczyć 4 punkty - każdy na rogu działki.", strInfo);
	format(strInfo, 1024, "%s\n"COL_WHITE"W innym przypadku, zaznaczaj na każdym załamaniu. Tak aby powstał wielokąt działki.", strInfo);
	format(strInfo, 1024, "%s\n"COL_WHITE"Maksymalna ilość punktów to: "COL_YELLOW"%d"COL_WHITE".", strInfo, ZONESET_MAXPOINTS);
	format(strInfo, 1024, "%s\n"COL_WHITE"Aby zakończyć/anulować tworzenie strefy, użyj: "COL_RED"/housezone", strInfo);
	MessageGUIEx(playerid, "Tworzenie strefy domku...",  strInfo);
	Info(playerid, "Klawisz Y - zaznaczenie punktu. /housezone - zakończenie/anulowanie.");
	return 1;
}

Dialog:SETCOMPZSELECT(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new targetid = gui_cache[playerid][listitem][0];
	SetPVarInt(playerid, "cache_setzone_activemode", 2);
	SetPVarInt(playerid, "cache_setzone_target", targetid);
	SetPVarInt(playerid, "cache_setzone_pointid", 0);
	new strInfo[1024];
	format(strInfo, 1024, "Rozpoczęto procedurę wyznaczania terenu firmy o ID: %d (%s)", targetid, GetPlayerIGName(company[targetid ][cny_owneruid]));
	format(strInfo, 1024, "%s\n"COL_WHITE"Aby zaznaczyć teren używaj "COL_BLUE"klawisza Y"COL_WHITE" na załamaniach działki. ", strInfo);
	format(strInfo, 1024, "%s\n"COL_WHITE"Punkty są automatycznie łączone w kolejności jakiej je zaznaczasz, "COL_GREEN"minimalna ilość punktów to 3 (wtedy powstaje krztałt trójkąta)"COL_WHITE".", strInfo);
	format(strInfo, 1024, "%s\n"COL_WHITE"Przykładowo, jeśli teren jest prostokontem, musisz zaznaczyć 4 punkty - każdy na rogu działki.", strInfo);
	format(strInfo, 1024, "%s\n"COL_WHITE"W innym przypadku, zaznaczaj na każdym załamaniu. Tak aby powstał wielokąt działki.", strInfo);
	format(strInfo, 1024, "%s\n"COL_WHITE"Maksymalna ilość punktów to: "COL_YELLOW"%d"COL_WHITE".", strInfo, ZONESET_MAXPOINTS);
	format(strInfo, 1024, "%s\n"COL_WHITE"Aby zakończyć/anulować tworzenie strefy, użyj: "COL_RED"/companyzone", strInfo);
	MessageGUIEx(playerid, "Tworzenie strefy firmy...",  strInfo);
	Info(playerid, "Klawisz Y - zaznaczenie punktu. /companyzone - zakończenie/anulowanie.");
	return 1;
}

Dialog:DELETEHOMEZONE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new targetid = gui_cache[playerid][listitem][0];
	if(house[targetid][h_polygonid] == 0) return Error(playerid, "Ten domek nie posiada strefy.");
	if(!IsPlayerInRangeOfPoint(playerid, 50.0, house[targetid][h_extX], house[targetid][h_extY], house[targetid][h_extZ])) return Error(playerid, "Jesteś za daleko od domku.");
	mq_format("UPDATE `domki` SET `polygon_count`='0', `polygon_data`='0.0' WHERE `id`='%d';", house[targetid][h_id]);
	mq_send("QUpdateHomeZone");
	if(house[targetid][h_polygonid] != 0) DestroyDynamicArea(house[targetid][h_polygonid]);
	house[targetid][h_polygonid] = 0;
	house[targetid][h_polygoncount] = 0;
	UpdateHouseLabel(targetid);
	Info(playerid, "Strefa domku usunięta.");
	return 1;
}

Dialog:DELETECOMPZONE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new targetid = gui_cache[playerid][listitem][0];
	if(company[targetid][cny_polygonid] == 0) return Error(playerid, "Ten domek nie posiada strefy.");
	if(!IsPlayerInRangeOfPoint(playerid, 200.0, company[targetid][cny_dutyX], company[targetid][cny_dutyY], company[targetid][cny_dutyZ])) return Error(playerid, "Jesteś za daleko od domku.");
	mq_format("UPDATE `firmy` SET `polygon_count`='0', `polygon_data`='0.0' WHERE `id`='%d';", targetid);
	mq_send("QUpdateCOmpanyZone");
	if(company[targetid][cny_polygonid] != 0) DestroyDynamicArea(company[targetid][cny_polygonid]);
	company[targetid][cny_polygonid] = 0;
	company[targetid][cny_polygoncount] = 0;
	Info(playerid, "Strefa firmy usunięta.");
	return 1;
}

task ZoneCreate_OnPlayerKeyStateCh(playerid, newkeys, oldkeys)
{
	if(GetPVarInt(playerid, "cache_setzone_activemode") == 0) return 1;
	if(PRESSED(KEY_YES))
	{
		new count_point = GetPVarInt(playerid, "cache_setzone_pointid");
		if(count_point < ZONESET_MAXPOINTS)
		{
			if(GetPVarInt(playerid, "cache_setzone_activemode") == 1)//domki
			{
				new targetid = GetPVarInt(playerid, "cache_setzone_target");
				if(IsPlayerInRangeOfPoint(playerid, 50.0, house[targetid][h_extX], house[targetid][h_extY], house[targetid][h_extZ]))
				{
					zoneset[playerid][count_point][zns_X] = gracz[playerid][PosX];
					zoneset[playerid][count_point][zns_Y] = gracz[playerid][PosY];
					zoneset[playerid][count_point][zns_targetid] = targetid;
					zoneset[playerid][count_point][zns_objectid] = CreateDynamicObject(1318, zoneset[playerid][count_point][zns_X], zoneset[playerid][count_point][zns_Y], gracz[playerid][PosZ], 0.0, 0.0, 0.0, -1, -1, playerid);
					new strInfo[144];
					format(strInfo, 144, "Punkt wierzchołka: %d", count_point+1);
					zoneset[playerid][count_point][zns_text3d] = CreateDynamic3DTextLabel(strInfo, 0xFF0000FF, zoneset[playerid][count_point][zns_X], zoneset[playerid][count_point][zns_Y], gracz[playerid][PosZ], 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1,  -1, playerid);
					count_point++;
					SetPVarInt(playerid, "cache_setzone_pointid", count_point);
					if(count_point < 3) format(strInfo, 144, "Stworzono punkt %d/%d. Minimalnie wymagane są 3.", count_point, ZONESET_MAXPOINTS);
					else format(strInfo, 144, "Stworzono punkt %d/%d.", count_point, ZONESET_MAXPOINTS);
					Info(playerid, strInfo);
				}
				else Error(playerid, "Za daleko od domku.");
			}
			else if(GetPVarInt(playerid, "cache_setzone_activemode") == 2)//firmy
			{
				new targetid = GetPVarInt(playerid, "cache_setzone_target");
				if(IsPlayerInRangeOfPoint(playerid, 200.0, company[targetid][cny_dutyX], company[targetid][cny_dutyY], company[targetid][cny_dutyZ]))
				{
					zoneset[playerid][count_point][zns_X] = gracz[playerid][PosX];
					zoneset[playerid][count_point][zns_Y] = gracz[playerid][PosY];
					zoneset[playerid][count_point][zns_targetid] = targetid;
					zoneset[playerid][count_point][zns_objectid] = CreateDynamicObject(1318, zoneset[playerid][count_point][zns_X], zoneset[playerid][count_point][zns_Y], gracz[playerid][PosZ], 0.0, 0.0, 0.0, -1, -1, playerid);
					new strInfo[144];
					format(strInfo, 144, "Punkt wierzchołka: %d", count_point+1);
					zoneset[playerid][count_point][zns_text3d] = CreateDynamic3DTextLabel(strInfo, 0xFF0000FF, zoneset[playerid][count_point][zns_X], zoneset[playerid][count_point][zns_Y], gracz[playerid][PosZ], 100.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1,  -1, playerid);
					count_point++;
					SetPVarInt(playerid, "cache_setzone_pointid", count_point);
					if(count_point < 3) format(strInfo, 144, "Stworzono punkt %d/%d. Minimalnie wymagane są 3.", count_point, ZONESET_MAXPOINTS);
					else format(strInfo, 144, "Stworzono punkt %d/%d.", count_point, ZONESET_MAXPOINTS);
					Info(playerid, strInfo);
				}
				else Error(playerid, "Za daleko od firmy.");
			}
		}
		else Error(playerid, "Osiągnięto maksymalną ilość punktów.");
	}
	return 1;
}


stock CancelCreateZone(playerid)
{
	if(GetPVarInt(playerid, "cache_setzone_activemode") == 0) return 1;
	for(new r1; r1 < ZONESET_MAXPOINTS; r1++)
	{
		if(IsValidDynamicObject(zoneset[playerid][r1][zns_objectid]) && IsValidDynamic3DTextLabel(zoneset[playerid][r1][zns_text3d]))
		{
			DestroyDynamicObject(zoneset[playerid][r1][zns_objectid]);
			DestroyDynamic3DTextLabel(zoneset[playerid][r1][zns_text3d]);
		}
		for(new zonseset_data:r; r < zonseset_data; r++)//czyszczenie zmiennych
		{
			zoneset[playerid][r1][r] = 0;
		}
	}
	DeletePVar(playerid, "cache_setzone_activemode");
	DeletePVar(playerid, "cache_setzone_target");
	DeletePVar(playerid, "cache_setzone_pointid");
	return 1;
}