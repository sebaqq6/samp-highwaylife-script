stock CreateLabelNick(playerid)
{
	gracz[playerid][p_label][0] = CreateDynamic3DTextLabel("---", -1, 0.0, 0.0, 0.4, 10.0, playerid, INVALID_VEHICLE_ID, 1);//bubble text
	gracz[playerid][p_label][1] = CreateDynamic3DTextLabel("---", -1, 0.0, 0.0, 0.4, 20.0, playerid, INVALID_VEHICLE_ID, 1);//ranga
	gracz[playerid][p_label][2] = CreateDynamic3DTextLabel("---", -1, 0.0, 0.0, 0.4, NICK_RANGE, playerid, INVALID_VEHICLE_ID, 1);//nick
	gracz[playerid][p_label][3] = CreateDynamic3DTextLabel("---", -1, 0.0, 0.0, 0.4, 20.0, playerid, INVALID_VEHICLE_ID, 1);//status
	return 1;
}

stock DestroyLabelNick(playerid)
{
	DestroyDynamic3DTextLabel(gracz[playerid][p_label][0]);
	DestroyDynamic3DTextLabel(gracz[playerid][p_label][1]);
	DestroyDynamic3DTextLabel(gracz[playerid][p_label][2]);
	DestroyDynamic3DTextLabel(gracz[playerid][p_label][3]);
	return 1;
}

task Process_NickLabel(playerid)
{
	if(gracz[playerid][event_hide_labels] == true)
	{
		UpdateDynamic3DTextLabelText(gracz[playerid][p_label][0], 0x00000000, "[hide]");
		UpdateDynamic3DTextLabelText(gracz[playerid][p_label][1], 0x00000000, "[hide]");
		UpdateDynamic3DTextLabelText(gracz[playerid][p_label][2], 0x00000000, "[hide]");
		UpdateDynamic3DTextLabelText(gracz[playerid][p_label][3], 0x00000000, "[hide]");
		return 1;
	}
	if(gracz[playerid][micro_td] == 0)
	{
		if(gracz[playerid][bubble_timestamp] < serwer[time_timestamp] && gracz[playerid][bubble_timestamp] != 0)
		{
			format(gracz[playerid][bubble_text], 144, " ");
			gracz[playerid][bubble_timestamp] = 0;
		}
		//format(gracz[playerid][p_label_string], 1024, "%s\n%s\n{%06x} %s "COL_WHITE"«"COL_EASY"%d"COL_WHITE"»\n{C9C9C9}(%s{C9C9C9})", gracz[playerid][bubble_text], GetAdminTagLabel(playerid), GetPlayerColor(playerid) >>> 8, nick(playerid), playerid, gracz[playerid][statusplayer]);
		format(gracz[playerid][p_label_string], 1024, "%s", gracz[playerid][bubble_text]);
		UpdateDynamic3DTextLabelText(gracz[playerid][p_label][0], 0x20B2AACC, gracz[playerid][p_label_string]);
	}
	UpdateAdminTagLabel(playerid);//gracz[playerid][p_label][1]
	if(gracz[playerid][p_label_nick_oc_ic] < 1)
	{
		format(gracz[playerid][p_label_string], 1024, "\n\n%s "COL_WHITE"«"COL_EASY"%d"COL_WHITE"»", nick(playerid), playerid);
		gracz[playerid][p_label_nick_oc_ic]++;
	}
	else
	{
		format(gracz[playerid][p_label_string], 1024, "\n\n%s "COL_WHITE"«"COL_EASY"%d"COL_WHITE"»", GetICName(playerid), playerid);
		gracz[playerid][p_label_nick_oc_ic]++;
		if(gracz[playerid][p_label_nick_oc_ic] > 2) gracz[playerid][p_label_nick_oc_ic] = 0;
	}
	if(gracz[playerid][p_label_excol_pause] > 0) 
	{
		gracz[playerid][p_label_excol_pause]--;
	}
	else 
	{
		gracz[playerid][p_label_nickcolor] = GetPlayerColor(playerid) - (GetPlayerColor(playerid) & 0x000000FF) + 170;
	}
	UpdateDynamic3DTextLabelText(gracz[playerid][p_label][2], gracz[playerid][p_label_nickcolor], gracz[playerid][p_label_string]);
	format(gracz[playerid][p_label_string], 1024, "\n\n\n(%s)", gracz[playerid][statusplayer]);
	UpdateDynamic3DTextLabelText(gracz[playerid][p_label][3], 0xC9C9C9AA, gracz[playerid][p_label_string]);
	return 1;
}

stock TempChangeColorNick(playerid, color, seconds)
{
	gracz[playerid][p_label_nickcolor] = color;
	gracz[playerid][p_label_excol_pause] = seconds;
	Process_NickLabel(playerid);
	return 1;
}

stock UpdateAdminTagLabel(playerid)
{
	new tag[128];
	switch(gracz[playerid][admin_duty])
	{
		case 0:
		{
			if(isvip(playerid)) 
			{
				if(gracz[playerid][hlfriend]) format(tag, 128, "\n[Przyjaciel HL]");
				else format(tag, 128, "\n[VIP]");
				UpdateDynamic3DTextLabelText(gracz[playerid][p_label][1], 0xC7BF00AB, tag);
			}
			else
		 	{
		 		if(gracz[playerid][hlfriend]) 
		 		{
		 			format(tag, 128, "\n[Przyjaciel HL]");
		 			UpdateDynamic3DTextLabelText(gracz[playerid][p_label][1], 0x00EC87AB, tag);
		 		}
		 		else
		 		{
		 			tag = " ";//gracz;
		 			UpdateDynamic3DTextLabelText(gracz[playerid][p_label][1], 0x00000000, tag);
		 		}
		 	}
		}
		case 1://Support
		{
			format(tag, 128, "\n[Support Team]");
			UpdateDynamic3DTextLabelText(gracz[playerid][p_label][1], 0x00A09EAB, tag);
		}
		case 2://Game Master
		{
			format(tag, 128, "\n[Game Master]");
			UpdateDynamic3DTextLabelText(gracz[playerid][p_label][1], 0x0052DDAB, tag);
		}
		default://Admin
		{
			format(tag, 128, "\n[Administrator]");
			UpdateDynamic3DTextLabelText(gracz[playerid][p_label][1], 0xFF0000AB, tag);
		}
	}
	return tag;
}

stock HoursToRank(playerid, hours)
{
	new wynik[32];
	if(gracz[playerid][Plec] == 1)//facet
	{
		switch(hours)
		{
			case 0: format(wynik, 32, "Świeżak");
			case 1..4: format(wynik, 32, "Żółtodziób");
			case 5..9: format(wynik, 32, "Bywalec");
			case 10..19: format(wynik, 32, "Wizjoner");
			case 20..29: format(wynik, 32, "Entuzjasta");
			case 30..49: format(wynik, 32, "Obeznany");
			case 50..99: format(wynik, 32, "Weteran");
			case 100..999: format(wynik, 32, "Zacny");
			default: format(wynik, 32, "Legenda");
		}
	}
	else//kobieta
	{
		switch(hours)
		{
			case 0: format(wynik, 32, "Świeżak");
			case 1..4: format(wynik, 32, "Żółtodziób");
			case 5..9: format(wynik, 32, "Bywalczyni");
			case 10..19: format(wynik, 32, "Wizjonerka");
			case 20..29: format(wynik, 32, "Entuzjastka");
			case 30..49: format(wynik, 32, "Obeznana");
			case 50..99: format(wynik, 32, "Weteranka");
			case 100..999: format(wynik, 32, "Zacna");
			default: format(wynik, 32, "Legenda");
		}
	}
	return wynik;
}

task Process_StatusPlayer(playerid)
{
	if(IsPlayerPaused(playerid))
	{
		format(gracz[playerid][statusplayer], 512, "ESC od %02d:%02d", gracz[playerid][pause_time][0], gracz[playerid][pause_time][1]);
		return 1;
	}
	if(IsPlayerAFK(playerid))
	{
		format(gracz[playerid][statusplayer], 512, "AFK od %02d:%02d", gracz[playerid][afk_time][0], gracz[playerid][afk_time][1]);
		return 1;
	}
	if(gracz[playerid][wypadek] > 0)
	{
		format(gracz[playerid][statusplayer], 512, "wypadek {C9C9C9}(%ds)", gracz[playerid][wypadek_time]);
		return 1;
	}
	if(gracz[playerid][bw] > 0)
	{
		if(gracz[playerid][Plec] == 1) format(gracz[playerid][statusplayer], 512, "nieprzytomny {C9C9C9}(%ds)", gracz[playerid][bw_time]);//facet
		else format(gracz[playerid][statusplayer], 512, "nieprzytomna {C9C9C9}(%ds)", gracz[playerid][bw_time]);//kobieta
		return 1;
	}
	format(gracz[playerid][statusplayer], 512, "%s", HoursToRank(playerid, gracz[playerid][PGodz]));//pierwsza ranga
	//statusy pozostałe
	if(gracz[playerid][has_sampvoice]) format(gracz[playerid][statusplayer], 512, "%s, czat głosowy", gracz[playerid][statusplayer]);
	/*if(gracz[playerid][Plec] == 1)//facet
	{
		switch(gracz[playerid][sila])
		{
			case 20..39: format(gracz[playerid][statusplayer], 512, "%s, wysportowany", gracz[playerid][statusplayer]);
			case 40..59: format(gracz[playerid][statusplayer], 512, "%s, barczysty", gracz[playerid][statusplayer]);
			case 60..79: format(gracz[playerid][statusplayer], 512, "%s, umięśniony", gracz[playerid][statusplayer]);
			case 80..100: format(gracz[playerid][statusplayer], 512, "%s, muskularny", gracz[playerid][statusplayer]);
		}
	}
	else//kobieta
	{
		switch(gracz[playerid][sila])
		{
			case 20..39: format(gracz[playerid][statusplayer], 512, "%s, wysportowana", gracz[playerid][statusplayer]);
			case 40..59: format(gracz[playerid][statusplayer], 512, "%s, barczysta", gracz[playerid][statusplayer]);
			case 60..79: format(gracz[playerid][statusplayer], 512, "%s, umięśniona", gracz[playerid][statusplayer]);
			case 80..100: format(gracz[playerid][statusplayer], 512, "%s, muskularna", gracz[playerid][statusplayer]);
		}
	}*/
	if(gracz[playerid][pasy]) format(gracz[playerid][statusplayer], 512, "%s, pasy", gracz[playerid][statusplayer]);
	if(gracz[playerid][przykuty]) 
	{
		if(gracz[playerid][Plec] == 1) format(gracz[playerid][statusplayer], 512, "%s, przykuty", gracz[playerid][statusplayer]);//facet
		else format(gracz[playerid][statusplayer], 512, "%s, przykuta", gracz[playerid][statusplayer]);//kobieta
	}
	else if(gracz[playerid][kajdanki]) 
	{
		if(gracz[playerid][Plec] == 1) format(gracz[playerid][statusplayer], 512, "%s, zakuty", gracz[playerid][statusplayer]);//facet
		else format(gracz[playerid][statusplayer], 512, "%s, zakuta", gracz[playerid][statusplayer]);//kobieta
	}
	if(gracz[playerid][stamina] < 10) 
	{
		if(gracz[playerid][Plec] == 1) format(gracz[playerid][statusplayer], 512, "%s, zmęczony", gracz[playerid][statusplayer]);//facet
		else format(gracz[playerid][statusplayer], 512, "%s, zmęczona", gracz[playerid][statusplayer]);//kobieta
	}
	return 1;
}

