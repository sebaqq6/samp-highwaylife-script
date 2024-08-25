//****************************************************************************************************************************************CZAT GŁÓWNY
public OnPlayerText(playerid, text[])
{
	if(!gracz[playerid][loggedin]) return 0;
	ResetIdleAFK(playerid);
	new pText[512];
	text[0] = chrtoupper(text[0]);
	if(text[0] == '.')//animacje
	{
		strdel(text, 0, 1);
		format(pText, 256, "/anim %s", text[0]);
		PC_EmulateCommand(playerid, pText);
		return 0;
	}
	//ADMIN
	if(text[0] == '`' && gracz[playerid][AdminLevel])//admin chat
	{
		for(new a = PlayerPoolSize(); a != -1; a--)
		{
			if(!gracz[a][loggedin]) continue;
			if(!gracz[a][AdminLevel]) continue;
			format(pText, 512, "@"COL_WHITE"(%d)"COL_RED"%s"COL_WHITE" » %s", playerid, gracz[playerid][master_nick], text[1]);
			SendClientMessage(a, 0xFF0000AA, pText);
		}
		return 0;
	}
	if(text[0] == '!')//czat ogólny
	{
		format(pText, 256, "/o %s", text[1]);
		PC_EmulateCommand(playerid, pText);
		return 0;
	}
	if(text[0] == '#' && gracz[playerid][frakcja] != 0)//czat frakcyjny
	{
		for(new sq = 0; sq < num_censor_words; sq++)
		{
			new pos;
			while((pos = strfind(text,Swears[sq],true)) != -1) for(new i = pos, j = pos + strlen(Swears[sq]); i < j; i++)
			{
				text[i] = '*';
			}
		}
		switch(gracz[playerid][frakcja_permlvl])
		{
			case 1: format(pText, 256, ""COL_ORANGE"[%s] %s(%d):{FFFFFF} %s", gracz[playerid][frakcja_tytul], nick(playerid), playerid, text[1]);
			case 2: format(pText, 256, ""COL_RED"[%s] %s(%d):{FFFFFF} %s", gracz[playerid][frakcja_tytul], nick(playerid), playerid, text[1]);
			default: format(pText, 256, "[%s] %s(%d):{FFFFFF} %s", gracz[playerid][frakcja_tytul], nick(playerid), playerid, text[1]);
		}
		
		SendFractionMessage(gracz[playerid][frakcja], pText);
		return 0;
	}

	if(text[0] == '^' && gracz[playerid][firma] != 0)//czat firmowy
	{
		for(new sq = 0; sq < num_censor_words; sq++)
		{
			new pos;
			while((pos = strfind(text,Swears[sq],true)) != -1) for(new i = pos, j = pos + strlen(Swears[sq]); i < j; i++)
			{
				text[i] = '*';
			}
		}
		switch(gracz[playerid][firma_permlvl])
		{
			case 1: format(pText, 256, ""COL_ORANGE"%s(%d):{FFFFFF} %s", nick(playerid), playerid, text[1]);
			case 2: format(pText, 256, ""COL_RED"%s(%d):{FFFFFF} %s", nick(playerid), playerid, text[1]);
			default: format(pText, 256, "%s(%d):{FFFFFF} %s", nick(playerid), playerid, text[1]);
		}
		
		SendCompanyMessage(gracz[playerid][firma], pText);
		return 0;
	}

	if(text[0] == '$' && gracz[playerid][frakcja] != 0 && gracz[playerid][frakcja] != F_MAFIA)//czat międzyfrakcyjny
	{
		for(new sq = 0; sq < num_censor_words; sq++)
		{
			new pos;
			while((pos = strfind(text,Swears[sq],true)) != -1) for(new i = pos, j = pos + strlen(Swears[sq]); i < j; i++)
			{
				text[i] = '*';
			}
		}
		format(pText, 256, "[%s"COL_FMSG"] %s(%d):{FFFFFF} %s", GetFractionName(gracz[playerid][frakcja], 1), nick(playerid), playerid, text[1]);		
		SendFractionMessage(F_POLICE, pText);
		SendFractionMessage(F_BORDERGUARD, pText);
		SendFractionMessage(F_EMERGENCY, pText);
		SendFractionMessage(F_ROADASSIST, pText);
		SendFractionMessage(F_TAXI, pText);
		return 0;
	}
	//GRACZ
	if(Spam(playerid, SPAM_CHAT, 2)) return 0;
	new posx;
	new emotid;
	while((posx = strfind(text," :)",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(":)"); i < j; i++)
		{
			text[i] = '\0'; 
		}
		emotid = 1;
	}

	while((posx = strfind(text," ;)",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(";)"); i < j; i++)
		{
			text[i] = '\0'; 
		}
		emotid = 2;
	}

	while((posx = strfind(text," ;p",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(";p"); i < j; i++)
		{
			text[i] = '\0'; 
		}
		emotid = 3;
	}

	while((posx = strfind(text," :p",true)) != -1)
	{ 
		for(new i = posx, j = posx + strlen(":p"); i < j; i++)
		{
			text[i] = '\0';
		}
		emotid = 3;
	}

	while((posx = strfind(text," :D",true)) != -1)
	{ 
		for(new i = posx, j = posx + strlen(":D"); i < j; i++)
		{
			text[i] = '\0';
		}
		emotid = 4;
	}

	while((posx = strfind(text," ;D",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(";D"); i < j; i++)
		{
			text[i] = '\0';
		}
		emotid = 5;
	}

	while((posx = strfind(text," :]",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(":]"); i < j; i++)
		{
			text[i] = '\0';
		}
		emotid = 6;
	}

	while((posx = strfind(text," ;]",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(";]"); i < j; i++)
		{
			text[i] = '\0';
		}
		emotid = 7;
	}

	while((posx = strfind(text," :(",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(":("); i < j; i++)
		{
			text[i] = '\0';
		}
		emotid = 8;
	}
	while((posx = strfind(text," ;(",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(";("); i < j; i++)
		{
			text[i] = '\0';
		}
		emotid = 8;
	}

	while((posx = strfind(text," ;/",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(";/"); i < j; i++)
		{
			text[i] = '\0'; 
		}
		emotid = 9;
	}

	while((posx = strfind(text," :/",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(":/"); i < j; i++)
		{
			text[i] = '\0';
		}
		emotid = 9;
	}
	//**********************************************************
	while((posx = strfind(text,":)",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(":)"); i < j; i++)
		{
			text[i] = '\0'; 
		}
		emotid = 1;
	}

	while((posx = strfind(text,";)",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(";)"); i < j; i++)
		{
			text[i] = '\0'; 
		}
		emotid = 2;
	}

	while((posx = strfind(text,";p",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(";p"); i < j; i++)
		{
			text[i] = '\0'; 
		}
		emotid = 3;
	}

	while((posx = strfind(text,":p",true)) != -1)
	{ 
		for(new i = posx, j = posx + strlen(":p"); i < j; i++)
		{
			text[i] = '\0';
		}
		emotid = 3;
	}

	while((posx = strfind(text,":D",true)) != -1)
	{ 
		for(new i = posx, j = posx + strlen(":D"); i < j; i++)
		{
			text[i] = '\0';
		}
		emotid = 4;
	}

	while((posx = strfind(text,";D",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(";D"); i < j; i++)
		{
			text[i] = '\0';
		}
		emotid = 5;
	}

	while((posx = strfind(text,":]",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(":]"); i < j; i++)
		{
			text[i] = '\0';
		}
		emotid = 6;
	}

	while((posx = strfind(text,";]",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(";]"); i < j; i++)
		{
			text[i] = '\0';
		}
		emotid = 7;
	}

	while((posx = strfind(text,":(",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(":("); i < j; i++)
		{
			text[i] = '\0';
		}
		emotid = 8;
	}
	while((posx = strfind(text,";(",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(";("); i < j; i++)
		{
			text[i] = '\0';
		}
		emotid = 8;
	}

	while((posx = strfind(text,";/",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(";/"); i < j; i++)
		{
			text[i] = '\0'; 
		}
		emotid = 9;
	}

	while((posx = strfind(text,":/",true)) != -1)
	{
		for(new i = posx, j = posx + strlen(":/"); i < j; i++)
		{
			text[i] = '\0';
		}
		emotid = 9;
	}
	if(emotid > 0) SetTimerEx("SendMeEmoticon", 100, false, "dd", playerid, emotid);
	if(strlen(text) > 0)
	{
		if(Interpunkcja(text))
		{
			format(pText, 512, "%s mówi: %s", GetICName(playerid), text);
		}
		else
		{
			format(pText, 512, "%s mówi: %s.", GetICName(playerid), text);
		}
		ShowBubble(playerid, text);
		ProxDetector(playerid, 18.0, pText, 0xFFFFFF96, 0xC8C8C896, 0x8B8B8B96, 0x5D5D5D96,  0x41414196);
	}
	return 0;
}


forward SendMeEmoticon(playerid, type);
public SendMeEmoticon(playerid, type)
{
	if(type == 0) return 1;
	if(type == 1)
	{
		PC_EmulateCommand(playerid, "/me uśmiecha się.");

	}
	if(type == 2)
	{
		PC_EmulateCommand(playerid, "/me uśmiecha się i puszcza oczko.");
	}
	if(type == 3)
	{
		PC_EmulateCommand(playerid, "/me pokazuje język.");
	}
	if(type == 4)
	{
		PC_EmulateCommand(playerid, "/me śmieje się.");
	}
	if(type == 5)
	{
		PC_EmulateCommand(playerid, "/me śmieje się i puszcza oczko.");
	}
	if(type == 6)
	{
		PC_EmulateCommand(playerid, "/me śmieje się specjalnie, lecz nic go tak naprawdę nie śmieszy.");
	}
	if(type == 7)
	{
		PC_EmulateCommand(playerid, "/me śmieje się specjalnie puszczając oczko, lecz nic go tak naprawdę nie śmieszy.");
	}
	if(type == 8)
	{
		PC_EmulateCommand(playerid, "/me smuci się.");
	}
	if(type == 9)
	{
		PC_EmulateCommand(playerid, "/me krzywi się.");
	}
	return 1;
}

stock ShowBubble(playerid, text[])
{
	format(gracz[playerid][bubble_text], 144, "%s", text);
	gracz[playerid][bubble_timestamp] = serwer[time_timestamp]+10;
	return 1;
}

stock GetPlayerTitle(playerid)
{
	new wynik[64];

	if(gracz[playerid][Plec] == 1) format(wynik, 64, "{63666A}• Bezrobotny •»");
	else if(gracz[playerid][Plec] == 2) format(wynik, 64, "{63666A}• Bezrobotna •»");
	if(gracz[playerid][courier_job] != 0)
	{
		for(new c = sizeof(courier_data)-1; c != -1; c--)//przyznanie tytułu kuriera na czacie
		{
			if(gracz[playerid][courier_job] == courier_data[c][cd_cid])
			{
				format(wynik, 64, "{%06x}• %s •»", courier_data[c][cd_color] >>> 8, courier_data[c][cd_name]);
				break;
			}
		}
	}
	else if(IsVehicleTruck(GetVehicleModel(gracz[playerid][opu_vehicleid])) && GetPlayerVehicleSeat(playerid) == 0 && !IsPlayerOnDutyFraction(playerid) && !IsPlayerOnDutyCompany(playerid)) 
	{
		format(wynik, 64, ""COL_DRVONLINE"• Kierowca •»");
	}
	else if(gracz[playerid][frakcja] != 0)
	{
		if(IsPlayerOnDutyFraction(playerid))
		{
			format(wynik, 64, "%s• %s •»", GetFractionName(gracz[playerid][frakcja], 2), GetFractionName(gracz[playerid][frakcja], 0));
		}
		else
		{
			if(gracz[playerid][firma] != 0)
			{
				if(IsPlayerOnDutyCompany(playerid))
				{
					format(wynik, 64, ""COL_DRVONLINE"• %s •»", company[gracz[playerid][firma]][cny_name]);
				}
				else
				{
					format(wynik, 64, "{63666A}• %s •»", GetFractionName(gracz[playerid][frakcja], 0));
				}
			}
		}
	}
	else if(gracz[playerid][firma] != 0)
	{
		if(IsPlayerOnDutyCompany(playerid))
		{
			format(wynik, 64, ""COL_DRVONLINE"• %s •»", company[gracz[playerid][firma]][cny_name]);
		}
		else
		{
			format(wynik, 64, "{63666A}• %s •»", company[gracz[playerid][firma]][cny_name]);
		}
	}
	return wynik;
}
//****************************************************************************************************************************************INNE CZATY
CMD:o(playerid, params[])
{
	//if(Spam(playerid, SPAM_CHAT, 2)) return 0;
	if(gracz[playerid][prisoner] == 1) return Error(playerid, "Będąc w areszcie nie możesz używać czatu ogólnego.");
	new message[128], str[256];
	if(serwer[block_global_ooc] == true && gracz[playerid][admin_duty] < 1) return Error(playerid, "Czat globalny jest wyłączony.");
	if(gracz[playerid][muted_timestamp] > serwer[time_timestamp])
	{
		format(str, 512,  "Jesteś uciszony. Pozostało: "COL_RED"%d"COL_WHITE" sekund.", gracz[playerid][muted_timestamp] - serwer[time_timestamp]);
		Error(playerid, str);
		return 1;
	}
	if(sscanf(params,"s[256]", message)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /o [wiadomość]");
	for(new sq = 0; sq < num_censor_words; sq++)
	{
		new pos;
		while((pos = strfind(message,Swears[sq],true)) != -1) for(new i = pos, j = pos + strlen(Swears[sq]); i < j; i++)
		{
			message[i] = '*';
		}
	}
	switch(gracz[playerid][admin_duty])
	{
		/*
		case 0://Gracz
		{
			if(isvip(playerid)) format(str, 256, "[VIP] {%06x}«%d» %s %s{FFFFFF} %s", GetPlayerColor(playerid) >>> 8, playerid, nick(playerid), GetPlayerTitle(playerid), (message));
			else 
			{
				if(gracz[playerid][has_sampvoice]) format(str, 256, "[VHL] {%06x}«%d» %s %s{FFFFFF} %s", GetPlayerColor(playerid) >>> 8, playerid, nick(playerid), GetPlayerTitle(playerid), (message));
				else format(str, 256, "{%06x}«%d» %s %s{FFFFFF} %s", GetPlayerColor(playerid) >>> 8, playerid, nick(playerid), GetPlayerTitle(playerid), (message));
			}
		}
		case 1://Support
		{
			format(str, 256, "[S] {%06x}«%d» %s %s{FFFFFF} %s", GetPlayerColor(playerid) >>> 8, playerid, nick(playerid), GetPlayerTitle(playerid), (message));
		}
		case 2://Game Master
		{
			format(str, 256, "[GM] {%06x}«%d» %s %s{FFFFFF} %s", GetPlayerColor(playerid) >>> 8, playerid, nick(playerid), GetPlayerTitle(playerid), (message));
		}
		default://Admin
		{
			format(str, 256, "[A] {%06x}«%d» %s %s{FFFFFF} %s", GetPlayerColor(playerid) >>> 8, playerid, nick(playerid), GetPlayerTitle(playerid), (message));
		}
		*/
		case 0://Gracz
		{
			if(isvip(playerid)) format(str, 256, "[VIP] {FFFFFF}«%d» %s %s{FFFFFF} %s", playerid, nick(playerid), GetPlayerTitle(playerid), (message));
			else 
			{
				if(gracz[playerid][has_sampvoice]) format(str, 256, "[VHL] {FFFFFF}«%d» %s %s{FFFFFF} %s", playerid, nick(playerid), GetPlayerTitle(playerid), (message));
				else format(str, 256, "{FFFFFF}«%d» %s %s{FFFFFF} %s", playerid, nick(playerid), GetPlayerTitle(playerid), (message));
			}
		}
		case 1://Support
		{
			format(str, 256, "[S] {FFFFFF}«%d» %s %s{FFFFFF} %s", playerid, nick(playerid), GetPlayerTitle(playerid), (message));
		}
		case 2://Game Master
		{
			format(str, 256, "[GM] {FFFFFF}«%d» %s %s{FFFFFF} %s", playerid, nick(playerid), GetPlayerTitle(playerid), (message));
		}
		default://Admin
		{
			format(str, 256, "[A] {FFFFFF}«%d» %s %s{FFFFFF} %s", playerid, nick(playerid), GetPlayerTitle(playerid), (message));
		}
	}

	if(strlen(str) > 144)
	{
		format(message, 128, "Wiadomość jest za długa. Usuń "COL_ORANGE"%d"COL_WHITE" znaków lub (jeśli użyłeś) oznaczenie @nick.", strlen(str)-144);
		Error(playerid, message);
		return 1;
	}
	new strLog[256];
	new bool:chatSaved = false;
	for(new i = PlayerPoolSize(); i != -1; i--)
	{
		if(gracz[i][loggedin])
		{
			switch(gracz[playerid][admin_duty])//dobranie kolorów
			{
				case 0:
				{
					if(isvip(playerid)) 
					{
						SendClientMessage(i, COLOR_VIP, str);
						if(!chatSaved)
						{
							chatSaved = true;
							format(strLog, 256, ""COL_VIP"%s", str);
							SavePublicChatLog(strLog, gracz[playerid][UID]);
						}
					}
					else 
					{
						if(gracz[playerid][has_sampvoice]) SendClientMessage(i, 0x00CCCCFF, str);//Voice Highway Life
						else SendClientMessage(i, -1, str);//Gracz
						if(!chatSaved)
						{
							chatSaved = true;
							format(strLog, 256, "%s", str);
							SavePublicChatLog(strLog, gracz[playerid][UID]);
						}
					}
				}
				case 1: 
				{
					SendClientMessage(i, 0x00A09EFF, str);//Support
					if(!chatSaved)
					{
						chatSaved = true;
						format(strLog, 256, "{00A09E}%s", str);
						SavePublicChatLog(strLog, gracz[playerid][UID]);
					}
				}
				case 2: 
				{
					SendClientMessage(i, 0x0052DDFF, str);//Game Master
					if(!chatSaved)
					{
						chatSaved = true;
						format(strLog, 256, "{0052DD}%s", str);
						SavePublicChatLog(strLog, gracz[playerid][UID]);
					}
				}
				default: 
				{
					SendClientMessage(i, 0xFF0000FF, str);//Admin
					if(!chatSaved)
					{
						chatSaved = true;
						format(strLog, 256, "{FF0000}%s", str);
						SavePublicChatLog(strLog, gracz[playerid][UID]);
					}
				}
			}
		}
	}
	return 1;
}

CMD:b(playerid, params[])
{
	if(Spam(playerid, SPAM_CHAT, 2)) return 0;
	new message[128], str[128];
	if(sscanf(params,"s[128]", message)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /b [wiadomość]");
	for(new sq = 0; sq < num_censor_words; sq++)
	{
		new pos;
		while((pos = strfind(message,Swears[sq],true)) != -1) for(new i = pos, j = pos + strlen(Swears[sq]); i < j; i++)
		{
			message[i] = '*';
		}
	}
	format(str, sizeof(str), "(( %s (ID: %d): %s ))", nick(playerid), playerid, message);
	SendNearByMessage(playerid, 0x999999FF, str, 5);
	return 1;
}


CMD:s(playerid, params[])
{
	if(Spam(playerid, SPAM_CHAT, 2)) return 0;
	new message[128], str[256];
	if(sscanf(params,"s[128]", message)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /s [szept]");
	message[0] = chrtoupper(message[0]);
	format(str, sizeof(str), "%s szepcze: %s", GetICName(playerid), message);
	SendNearByMessage(playerid, -1, str, 2.5);
	return 1;
}

CMD:me(playerid, params[])
{
	new message[128], str[256];
	if(sscanf(params,"s[128]", message)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /me [akcja]");
	format(str, 128, "* %s %s", GetICName(playerid), message);
	SendNearByMessage(playerid, 0xC2A2DAAA, str, 10);
	return 1;
}


CMD:do(playerid, params[])
{
	new message[128], str[256];
	if(sscanf(params,"s[128]", message)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /do [akcja]");
	format(str, 128, "* %s ((%s))", message, GetICName(playerid));
	SendNearByMessage(playerid, 0x6082B6FF, str, 10);
	return 1;
}

CMD:k(playerid, params[])
{
	if(Spam(playerid, SPAM_CHAT, 1)) return 0;
	new message[128], str[256];
	if(sscanf(params,"s[128]", message)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /k [krzyk]");
	message[0] = chrtoupper(message[0]);
	format(str, 128, "%s krzyczy: %s!", GetICName(playerid), message);
	ProxDetector(playerid, 35.0, str, 0xFFFFFF96, 0xC8C8C896, 0x8B8B8B96, 0x5D5D5D96,  0x41414196);
	return 1;
}

CMD:togpm(playerid, params[])
{
	if(gracz[playerid][blockpm] == true)
	{
		Info(playerid, ""COL_GREEN"Odblokowano prywatne wiadomości.");
		gracz[playerid][blockpm] = false;
	}
	else
	{
		Info(playerid, ""COL_RED"Zablokowano prywatne wiadomości.");
		gracz[playerid][blockpm] = true;
	}
	return 1;
}

CMD:re(playerid, params[])
{
	if(gracz[playerid][blockpm]) return Error(playerid, "Masz zablokowane PW. (/togpm)");
	if(Spam(playerid, SPAM_CHAT, 1)) return 0;
	new message[256], str[256];
	if(GetPVarInt(playerid, "RePM") == -1) return Error(playerid, "Nie możesz odpisać, gdyż nikt ostatnio do Ciebie nie napisał PM.");
	new targetid;
	targetid = GetPVarInt(playerid, "RePM");
	if(sscanf(params,"s[256]", message)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /re [wiadomość]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(gracz[targetid][blockpm] == true) return Error(playerid, "Ten gracz ma zablokowane PW.");
	if(strlen(message) < 1) return Error(playerid, "Wiadomość jest za krótka.");
	for(new sq = 0; sq < num_censor_words; sq++)
	{
		new pos;
		while((pos = strfind(message,Swears[sq],true)) != -1) for(new i = pos, j = pos + strlen(Swears[sq]); i < j; i++)
		{
			message[i] = '*';
		}
	}
	format(str, sizeof(str), ""COL_RED">>"COL_LIME" %s[%d]:"COL_RED" %s", gracz[targetid][master_nick], targetid, message);
	SendMSGLamane(playerid, 0xFF0000FF, str);
	format(str, sizeof(str), ""COL_GREEN"<<"COL_LIME" %s[%d]:"COL_RED" %s", gracz[playerid][master_nick], playerid, message);
	SendMSGLamane(targetid, 0xFF0000FF, str);
	SetPVarInt(targetid, "RePM", playerid);
	gracz[targetid][leftnotify_customsound] = 5202;
	format(str, sizeof(str), "Otrzymales prywatna wiadomosc od gracza ~g~%s (ID: %d)~w~. Uzyj ~y~/re~w~ aby odpisac.", gracz[playerid][master_nick], playerid);
	LeftNotifyShow(targetid, "Wiadomosc", str, LN_BLUE, 15);

	mysql_escape_string(message, message, 256, g_SQL);
	mq_format("INSERT INTO `LogPrivateMessages` (`id`, `sender`, `recipient`, `text`, `time`) VALUES (NULL, '%d', '%d', '%s', CURRENT_TIMESTAMP);", gracz[playerid][UID], gracz[targetid][UID], message);
	mq_send("QPMLog");
	return 1;
}
CMD:w(playerid, params[])
{
	if(gracz[playerid][blockpm]) return Error(playerid, "Masz zablokowane PW. (/togpm)");
	if(Spam(playerid, SPAM_CHAT, 1)) return 0;
	new targetid, message[256], str[256];
	if(sscanf(params,"ds[256]", targetid, message)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /w [idgracza] [wiadomość]");
	if(targetid == playerid) return Error(playerid, "Nie możesz wysłać wiadomości do samego siebie.");
	if(gracz[targetid][blockpm] == true) return Error(playerid, "Ten gracz ma zablokowane PW.");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	for(new sq = 0; sq < num_censor_words; sq++)
	{
		new pos;
		while((pos = strfind(message,Swears[sq],true)) != -1) for(new i = pos, j = pos + strlen(Swears[sq]); i < j; i++)
		{
			message[i] = '*';
		}
	}
	format(str, sizeof(str), ""COL_RED">>"COL_LIME" %s[%d]:"COL_RED" %s", gracz[targetid][master_nick], targetid, message);
	SendMSGLamane(playerid, 0xFF0000FF, str);
	format(str, sizeof(str), ""COL_GREEN"<<"COL_LIME" %s[%d]:"COL_RED" %s", gracz[playerid][master_nick], playerid, message);
	SendMSGLamane(targetid, 0xFF0000FF, str);
	SetPVarInt(targetid, "RePM", playerid);
	gracz[targetid][leftnotify_customsound] = 5202;
	format(str, sizeof(str), "Otrzymales prywatna wiadomosc od gracza ~g~%s (ID: %d)~w~. Uzyj ~y~/re~w~ aby odpisac.", gracz[playerid][master_nick], playerid);
	LeftNotifyShow(targetid, "Wiadomosc", str, LN_BLUE, 15);

	mysql_escape_string(message, message, 256, g_SQL);
	mq_format("INSERT INTO `LogPrivateMessages` (`id`, `sender`, `recipient`, `text`, `time`) VALUES (NULL, '%d', '%d', '%s', CURRENT_TIMESTAMP);", gracz[playerid][UID], gracz[targetid][UID], message);
	mq_send("QPMLog");
	return 1;
}
CMD:pm(playerid, params[])
{
	if(gracz[playerid][blockpm]) return Error(playerid, "Masz zablokowane PW. (/togpm)");
	if(Spam(playerid, SPAM_CHAT, 1)) return 0;
	new targetid, message[256], str[256];
	if(sscanf(params,"ds[256]", targetid, message)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /pm [idgracza] [wiadomość]");
	if(targetid == playerid) return Error(playerid, "Nie możesz wysłać wiadomości do samego siebie.");
	if(gracz[targetid][blockpm] == true) return Error(playerid, "Ten gracz ma zablokowane PW.");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	for(new sq = 0; sq < num_censor_words; sq++)
	{
		new pos;
		while((pos = strfind(message,Swears[sq],true)) != -1) for(new i = pos, j = pos + strlen(Swears[sq]); i < j; i++)
		{
			message[i] = '*';
		}
	}
	format(str, sizeof(str), ""COL_RED">>"COL_LIME" %s[%d]:"COL_RED" %s", gracz[targetid][master_nick], targetid, message);
	SendMSGLamane(playerid, 0xFF0000FF, str);
	format(str, sizeof(str), ""COL_GREEN"<<"COL_LIME" %s[%d]:"COL_RED" %s", gracz[playerid][master_nick], playerid, message);
	SendMSGLamane(targetid, 0xFF0000FF, str);
	SetPVarInt(targetid, "RePM", playerid);
	gracz[targetid][leftnotify_customsound] = 5202;
	format(str, sizeof(str), "Otrzymales prywatna wiadomosc od gracza ~g~%s (ID: %d)~w~. Uzyj ~y~/re~w~ aby odpisac.", gracz[playerid][master_nick], playerid);
	LeftNotifyShow(targetid, "Wiadomosc", str, LN_BLUE, 15);

	mysql_escape_string(message, message, 256, g_SQL);
	mq_format("INSERT INTO `LogPrivateMessages` (`id`, `sender`, `recipient`, `text`, `time`) VALUES (NULL, '%d', '%d', '%s', CURRENT_TIMESTAMP);", gracz[playerid][UID], gracz[targetid][UID], message);
	mq_send("QPMLog");
	return 1;
}
//************************************************************************PRZEKOLORWANIE NICKU GRACZ
enum nc_data
{
	nc_uid,
	nc_nick[24]
}
new nick_cache[MAX_NICKCACHE][nc_data];
stock Init_NickCache()
{
	mq_format("SELECT `Nick`,`id` FROM `Konta` ORDER BY  `LastOnline` DESC  LIMIT  %d;", MAX_NICKCACHE-1);
	mq_send("LoadNickCacheFromDB");
	return 1;
}

forward LoadNickCacheFromDB();
public LoadNickCacheFromDB()
{
	mq_getdata();
	new i;
	if(rekordy)
	{
		while(i < rekordy)
		{
			cache_get_value_name_int(i, "id",  nick_cache[i][nc_uid]);
			cache_get_value_name(i, "Nick", nick_cache[i][nc_nick], 24);
			i++;
		}
	}
	printf("[LOAD] Wczytano %d nick cache.", i);
	return 1;
}


/*
stock HighlightNick(text[])
{
	new wynik[128];
	new normalnick[32];
	new nickhighlight[64];
	format(wynik, 128, "%s", text);
	for(new n; n < MAX_NICKCACHE; n++)
	{
		if(nick_cache[n][nc_uid] == 0) continue;
		format(normalnick, 32, "@%s", nick_cache[n][nc_nick]);
		if(strfind(text, normalnick, true) != -1)
		{
			if(PlayerIsOnline(nick_cache[n][nc_uid])) format(nickhighlight, 64, "{00FF00}@%s{FFFFFF}", nick_cache[n][nc_nick]);
			else format(nickhighlight, 64, "{9C9C9C}@%s{FFFFFF}", nick_cache[n][nc_nick]);
			format(wynik, 128, "%s", str_replace(normalnick, nickhighlight, text, true));
			return wynik;
		}
	}
	return wynik;
}*/