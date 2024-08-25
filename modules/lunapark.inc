#define MAX_LUNAPARKS 10

enum lnp_data
{
	lnp_name[64],
	lnp_playerscount,
	lnp_maxplayers,
	lnp_cost,
	Float:lnp_arenarange,
	Float:lnp_aX,
	Float:lnp_aY,
	Float:lnp_aZ,
	lnp_status
};

new lunapark[MAX_LUNAPARKS][lnp_data];

#define XYZ_DJKA 3239.6345,-1986.3455,24.2275

stock Init_LunaPark()
{
	//park rozrywki
	//aktorzy recepcja
	CreateActor(264,3099.4756,-1959.1893,10.9893,91.4244); // lunaparkbot1
	CreateActor(264,3099.4785,-1962.6891,10.9893,93.9311); // lunaparkbot2
	CreateActor(264,3099.4751,-1965.9734,10.9893,93.9311); // lunaparkbot3
	//actorzy - kurwy
	new temp_actor;
	//*scena
	temp_actor = CreateActor(152,3239.6763,-1980.0184,25.0067,92.1472); // kurwa1
	ApplyActorAnimation(temp_actor, "STRIP", "STR_Loop_A", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(85,3239.7151,-1992.9408,25.0127,89.6405); // kurwa2
	ApplyActorAnimation(temp_actor, "STRIP", "STR_Loop_A", 2.0, 1, 0, 0, 0, 0);
	//osobne stanowisko
	temp_actor = CreateActor(140,3210.4087,-1971.3834,24.9384,180.8214); // kurwa3_1 - mid
	ApplyActorAnimation(temp_actor, "STRIP", "STR_Loop_A", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(257,3212.7297,-1971.8408,24.1013,178.6279); // kurwa3_2 - prawa
	ApplyActorAnimation(temp_actor, "STRIP", "STR_Loop_B", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(87,3214.1331,-1973.8562,23.2524,178.0014); // kurwa3_3 - prawa
	ApplyActorAnimation(temp_actor, "STRIP", "STR_Loop_C", 4.1, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(244,3208.0896,-1971.8599,24.1021,180.5082); // kurwa3_4 - lewa
	ApplyActorAnimation(temp_actor, "STRIP", "STR_Loop_B", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(246,3206.7231,-1974.0082,23.2457,181.7616); // kurwa3_5 - lewa
	ApplyActorAnimation(temp_actor, "STRIP", "STR_Loop_C", 4.1, 1, 0, 0, 0, 0);
	//barmani
	temp_actor = CreateActor(90,3182.3896,-1984.1202,21.4675,303.9393); // barmanka 1
	ApplyActorAnimation(temp_actor, "BAR", "Barserve_loop", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(237,3182.0396,-1989.4883,21.4675,200.2250); // barmanka 2
	ApplyActorAnimation(temp_actor, "BAR", "Barserve_loop", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(63,3177.2419,-1989.3180,21.4675,147.5845); // barmanka 3
	ApplyActorAnimation(temp_actor, "BAR", "Barserve_loop", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(178,3176.0012,-1986.0033,21.4675,79.5905); // barmanka 4
	ApplyActorAnimation(temp_actor, "BAR", "Barserve_loop", 2.0, 1, 0, 0, 0, 0);
	//ochroniarze
	temp_actor = CreateActor(163,3157.1946,-1989.5355,21.8313,71.2239); // goryl 1
	ApplyActorAnimation(temp_actor, "DEALER", "DEALER_IDLE_03", 4.1, 0, 0, 0, 1, 0);
	temp_actor = CreateActor(164,3157.3540,-1983.7620,21.8313,118.8277); // goryl 2
	ApplyActorAnimation(temp_actor, "DEALER", "DEALER_IDLE_03", 4.1, 0, 0, 0, 1, 0);
	//OPCJONALNIUE
	temp_actor = CreateActor(244,3222.8411,-1981.3943,21.5780,259.0317); // bot1-scena .strip3
	ApplyActorAnimation(temp_actor, "STRIP", "strip_F", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(178,3224.9932,-1981.8274,21.5780,82.0763); // bot2-scena .strip2
	ApplyActorAnimation(temp_actor, "STRIP", "strip_D", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(87,3223.3101,-1994.7633,21.5780,298.9052); // bot3-scena .dance8 (po zmianie .tancz8)
	ApplyActorAnimation(temp_actor, "DANCING", "dnce_m_d", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(90,3229.1423,-1987.8347,21.5780,260.0516); // bot4-scena .dance7 (po zmianie .tancz7)
	ApplyActorAnimation(temp_actor, "DANCING", "DAN_left_A", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(257,3227.8062,-1972.6108,21.5780,206.4710); // bot5-scena .strip2
	ApplyActorAnimation(temp_actor, "STRIP", "STR_Loop_A", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(63,3234.0500,-1975.6475,21.5780,137.8504); // bot6-scena .dance1 (po zmianie .tancz1)
	ApplyActorAnimation(temp_actor, "DANCING", "dnce_m_d", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(246,3219.6162,-1994.7404,21.5780,298.9054); // bot7-scena .strip4
	ApplyActorAnimation(temp_actor, "STRIP", "STR_Loop_A", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(237,3188.2666,-1976.9567,22.4325,270.0552); // dziwka-stolik .dance4 (po zmianie .tancz4)
	ApplyActorAnimation(temp_actor, "DANCING", "DAN_left_A", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(140,3230.3247,-1998.3950,21.5780,327.8091); // bot-scena .rap1
	ApplyActorAnimation(temp_actor, "RAPPING", "RAP_A_Loop", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(244,3228.7500,-1980.3818,21.5780,225.6847); // bot-scena .gogo  (po zmianie .doping2)
	ApplyActorAnimation(temp_actor, "RIOT", "RIOT_CHANT", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(246,3197.6323,-1990.9810,26.7783,94.7102); // dziwka-stol .dance5  (po zmianie .tancz5)
	ApplyActorAnimation(temp_actor, "STRIP", "STR_Loop_A", 2.0, 1, 0, 0, 0, 0);
	temp_actor = CreateActor(140,3198.5959,-1998.6238,25.9413,267.0686); // bot-podest .rap1
	ApplyActorAnimation(temp_actor, "RAPPING", "RAP_A_Loop", 2.0, 1, 0, 0, 0, 0);
	//pickupy etc
	CreateDynamicMapIcon(XYZ_LUNAPARK, 25, 0, .streamdistance = 5000.0, .style = MAPICON_GLOBAL);
	CreateDynamicPickup(1248, 1, XYZ_LUNAPARK, 0, 0);
	CreateDynamic3DTextLabel("« "COL_RED"PARK ROZRYWKI "COL_GREEN"»\n"COL_RED"• "COL_WHITE"Użyj "COL_GREEN"PPM"COL_WHITE" lub "COL_GREEN"/lunapark"COL_WHITE" aby dołączyć do zabawy! "COL_RED"•", 0x009933FF, XYZ_LUNAPARK, 25.0);
	//djka
	format(serwer[dj_url], 144, "http://s3.radioparty.pl:8005/listen.pls");
	CreateDynamicPickup(1248, 1, XYZ_DJKA, 0, 0);
	CreateDynamic3DTextLabel("« "COL_RED"DJ "COL_GREEN"»\n"COL_RED"• "COL_WHITE"Wpisz "COL_GREEN"/dj"COL_WHITE" aby zmienić link do strumienia audio. "COL_RED"•", 0x009933FF, XYZ_DJKA, 2.0);
	//rejestracja rozrywek
	RegisterLunapark(LPARK_FOOTBALL, "Piłka nożna", 25, 50, 80.0, 2706.8354,-1802.2961,422.8372);
	RegisterLunapark(LPARK_BASKETBALL, "Koszykówka", 25, 50, 90.0, 3761.4531,-1770.0101,426.5565);
	RegisterLunapark(LPARK_ASG, "Arena ASG (DM)", 15, 1000, 135.0, 1766.4508,-1911.4851,443.1161);
	return 1;
}

stock RegisterLunapark(lnid, lname[], lmaxplayers, lcost, Float:larange, Float:lX, Float:lY, Float:lZ)
{
	format(lunapark[lnid][lnp_name], 64, "%s", lname);
	lunapark[lnid][lnp_maxplayers] = lmaxplayers;
	lunapark[lnid][lnp_cost] = lcost;
	lunapark[lnid][lnp_arenarange] = larange;
	lunapark[lnid][lnp_aX] = lX;
	lunapark[lnid][lnp_aY] = lY;
	lunapark[lnid][lnp_aZ] = lZ;
	lunapark[lnid][lnp_status] = 1;
	return 1;
}

CMD:lunapark(playerid, params[])
{
	if(IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Jesteś na duty we frakcji.");
	if(gracz[playerid][status_lunapark] != 0)
	{
		if(gracz[playerid][loading_objects]) return Error(playerid, "Trwa ładowanie obiektów.");
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerInterior(playerid, 0);
		FreezeLoadObject(playerid, XYZ_LUNAPARK);
		ResetPlayerWeapons(playerid);
		if(gracz[playerid][status_lunapark] == LPARK_ASG)
		{
			ASG_OnPlayerExit(playerid);
		}
		gracz[playerid][status_lunapark] = 0;
		Info(playerid, ""COL_RED"Opuściłeś/aś arenę parku rozrywki.");
		return 1;
	}
	if(!IsPlayerInRangeOfPoint(playerid, 1.2, XYZ_LUNAPARK)) return Error(playerid, "Nie jesteś w parku rozrywki.");
	new strLunaparkList[2048];
	format(strLunaparkList, 2048, "Gra\tGraczy\tKoszt wejścia");
	new counter;
	for(new f; f < MAX_LUNAPARKS; f++)
	{
		if(lunapark[f][lnp_status] != 0)
		{
			format(strLunaparkList, 2048, "%s\n"COL_LIME"%s\t"COL_GREEN"%d"COL_WHITE"/"COL_RED"%d\t"COL_GREEN"%d$", strLunaparkList, lunapark[f][lnp_name], lunapark[f][lnp_playerscount], lunapark[f][lnp_maxplayers], lunapark[f][lnp_cost]);
			gui_cache[playerid][counter][0] = f;
			counter++;
		}
	}
	Dialog_Show(playerid, LPJOIN, DIALOG_STYLE_TABLIST_HEADERS, "Wybierz rozrywkę", strLunaparkList, "Dołącz", "Zamknij");
	return 1;
}

Dialog:LPJOIN(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(gracz[playerid][loading_objects]) return Error(playerid, "Trwa ładowanie obiektów.");
	new l_id = gui_cache[playerid][listitem][0];
	if(l_id == 0) return Error(playerid, "Niespodziewany błąd.");
	if(lunapark[l_id][lnp_playerscount] >= lunapark[l_id][lnp_maxplayers]) return Error(playerid, "Brak miejsc.");
	if(gracz[playerid][hlfriend] == 0)
	{
		if(lunapark[l_id][lnp_cost] > Money(playerid)) return Error(playerid, "Niewystarczająca ilość gotówki.");
		TakeMoney(playerid, lunapark[l_id][lnp_cost]);
	}
	else Info(playerid, "Jesteś przyjacielem HL. Nie została od Ciebie pobrana opłata.");
	gracz[playerid][status_lunapark] = l_id;
	lunapark[l_id][lnp_playerscount]++;
	new strInfo[144];
	format(strInfo, 144, "Dołączyłeś do: "COL_LIME"%s"COL_WHITE". Wpisz "COL_RED"/lunapark"COL_WHITE" aby wyjść.", lunapark[l_id][lnp_name]);
	Info(playerid, strInfo);
	if(l_id == LPARK_FOOTBALL)
	{
		Force_FreezeLoadObject(playerid, 2675.7234,-1742.0830,422.8280);
		SetPlayerVirtualWorld(playerid, LUNAPARK_VWOFFSET);
		SetPlayerInterior(playerid, 10);
	}
	else if(l_id == LPARK_BASKETBALL)
	{
		FreezeLoadObject(playerid, 3761.4531,-1770.0101,426.5565);
		SetPlayerVirtualWorld(playerid, LUNAPARK_VWOFFSET);
		SetPlayerInterior(playerid, 10);
	}
	else if(l_id == LPARK_ASG)
	{
		gracz[playerid][status_lunapark] = 0;
		ASG_OnPlayerSpawn(playerid);
	}
	else Error(playerid, "Wystąpił nieoczekiwany błąd.");
	return 1;
}

task Process_LunaPark()
{
	//pętla lunapark F
	for(new f; f < MAX_LUNAPARKS; f++)
	{
		if(lunapark[f][lnp_status] != 0)
		{
			//pętla graczy P
			lunapark[f][lnp_playerscount] = 0;
			for(new p = PlayerPoolSize(); p != -1; p--)
			{
				if(!gracz[p][loggedin]) continue;
				if(IsPlayerInRangeOfPoint(p, lunapark[f][lnp_arenarange], lunapark[f][lnp_aX], lunapark[f][lnp_aY], lunapark[f][lnp_aZ]) && GetPlayerVirtualWorld(p) == LUNAPARK_VWOFFSET)
				{
					gracz[p][status_lunapark] = f;
					lunapark[f][lnp_playerscount]++;
				}
				else
				{
					new actual_lnid = gracz[p][status_lunapark];
					if(actual_lnid != 0)
					{
						if(!IsPlayerInRangeOfPoint(p, lunapark[actual_lnid][lnp_arenarange], lunapark[actual_lnid][lnp_aX], lunapark[actual_lnid][lnp_aY], lunapark[actual_lnid][lnp_aZ]))
						{
							if(actual_lnid == LPARK_ASG)
							{
								ASG_OnPlayerExit(p);
							}
							SetPlayerVirtualWorld(p, 0);
							SetPlayerInterior(p, 0);
							FreezeLoadObject(p, XYZ_LUNAPARK);
							ResetPlayerWeapons(p);
							gracz[p][status_lunapark] = 0;
						}
					}
				}
			}
			//petla lunapark F - ciąg dalszy
		}
	}
	return 1;
}

CMD:dj(playerid, params[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 1.2, XYZ_DJKA)) return Error(playerid, "Nie jesteś przy DJ-ce.");
	new pin, url[144];
	if(sscanf(params,"ds[144]", pin, url)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /dj [PIN] [link URL]");
	if(pin != 2233) return Error(playerid, "Niepoprawny PIN.");
	format(serwer[dj_url], 144, "%s", url);
	SendClientMessage(playerid, 0xFF0000FF, serwer[dj_url]);
	SendClientMessage(playerid, 0x00FF00FF, "Wszyscy w pobliżu DJ-ki będą słyszeć strumień z tego linku ;)");
	return 1;
}

task Process_DJKA(playerid)
{
	if(IsPlayerInRangeOfPoint(playerid, 190.0, XYZ_DJKA))//jest w zasięgu djki
	{
		if(!compare(gracz[playerid][dj_listen], serwer[dj_url]))
		{
			LeftNotifyShow(playerid, "Park rozrywki", "Trwa odtwarzanie muzyki z klubu znajdujacego sie w parku rozrywki.", LN_BLUE);
			StopAudioStreamForPlayer(playerid);
			PlayAudioStreamForPlayer(playerid, serwer[dj_url], XYZ_DJKA, 225.0, 1);
			format(gracz[playerid][dj_listen], 144, "%s", serwer[dj_url]);
		}
	}
	else if(GetPlayerVirtualWorld(playerid) == LUNAPARK_VWOFFSET)
	{
		if(!compare(gracz[playerid][dj_listen], "http://stream.open.fm/101"))
		{
			LeftNotifyShow(playerid, "Park rozrywki", "Trwa odtwarzanie playlisty Trening z OpenFM.", LN_BLUE);
			StopAudioStreamForPlayer(playerid);
			PlayAudioStreamForPlayer(playerid, "http://stream.open.fm/101");
			format(gracz[playerid][dj_listen], 144, "%s", "http://stream.open.fm/101");
		}
	}
	else//nie jest
	{
		if(compare(gracz[playerid][dj_listen], serwer[dj_url]))
		{
			StopAudioStreamForPlayer(playerid);
			format(gracz[playerid][dj_listen], 144, "brak");
			if(strlen(gracz[playerid][last_radio]) > 3)
			{
				LeftNotifyShow(playerid, "Park rozrywki", "Opusciles park rozrywki. Trwa odtwarzanie radia, ktorego ostatnio sluchales.", LN_BLUE);
				PlayAudioStreamForPlayer(playerid, gracz[playerid][last_radio]);
			}
		}
	}
	//printf("%s", gracz[playerid][dj_listen]);
	return 1;
}