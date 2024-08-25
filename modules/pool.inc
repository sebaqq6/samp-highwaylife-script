#define OBJ_SLOT_POOL ATTACH_SLOT3

enum poolBall
{
	bObject,
	bExisting,
	Float:b_last_safeX,
	Float:b_last_safeY,
	Float:b_last_safeZ
}

new
	PlayingPool[MAX_PLAYERS],
	PoolCamera[MAX_PLAYERS],
	UsingChalk[MAX_PLAYERS],
	PoolScore[MAX_PLAYERS],
	Float:AimAngle[MAX_PLAYERS][2],
	AimObject,
	PoolStarted,
	PoolAimer = -1,
	PoolLastShooter = -1,
	PoolLastScore,
	PoolBall[16][poolBall],
	Text:PoolTD[4],
	Float:PoolPower,
	PoolDir,
	pool_adminid = -1,
	pool_FixBall_timestamp,
	Text3D:pool_text3d,
	pool_polygon;

stock Init_Pool()
{
	//CreateObject(2964, 3169.74023, -1971.90234, 20.81123,   0.00000, 0.00000, 0.00000);
	//CreateObject(980, 3168.19702, -1972.02917, 20.83590,   90.00000, 0.00000, 0.00000);
	CreateBalls();

	SetTimer("PoolTimer", 21*2, 1);
	new Float:pool_wall_pD[2] = {3170.7191, -1972.4209};
	new Float:pool_wall_pG[2] = {3170.7191, -1971.360};
	new Float:pool_wall_lG[2] = {3168.7731, -1971.3609};
	new Float:pool_wall_lD[2] = {3168.7731, -1972.4229};
	new Float:pool_wall_offset = 0.030;
	//                                                                        xy prawy dolny                                             prawy górny                            
	PHY_SetWallWorld(PHY_CreateWall(pool_wall_pD[0] - pool_wall_offset, pool_wall_pD[1] - pool_wall_offset, pool_wall_pG[0] + pool_wall_offset, pool_wall_pG[1] - pool_wall_offset), 3);//krótka
	//                                                                        xy prawy górny                                             lewy górny           
	PHY_SetWallWorld(PHY_CreateWall(pool_wall_pG[0] + pool_wall_offset, pool_wall_pG[1]  - pool_wall_offset, pool_wall_lG[0] + pool_wall_offset, pool_wall_lG[1] + pool_wall_offset), 3);//długa
	//                                                                        xy lewy górny                                          lewy dolny     
	PHY_SetWallWorld(PHY_CreateWall(pool_wall_lG[0] + pool_wall_offset, pool_wall_lG[1] + pool_wall_offset, pool_wall_lD[0] - pool_wall_offset, pool_wall_lD[1] + pool_wall_offset), 3);//krótka
	//                                                                        xy lewy dolny                                           prawy dolny  
	PHY_SetWallWorld(PHY_CreateWall(pool_wall_lD[0] - pool_wall_offset, pool_wall_lD[1] + pool_wall_offset, pool_wall_pD[0] - pool_wall_offset, pool_wall_pD[1] - pool_wall_offset), 3);

	new Float:pool_polygonpos[8];
	pool_polygonpos[0] = pool_wall_pD[0] - pool_wall_offset;
	pool_polygonpos[1] = pool_wall_pD[1] - pool_wall_offset;

	pool_polygonpos[2] = pool_wall_pG[0] + pool_wall_offset;
	pool_polygonpos[3] = pool_wall_pG[1] - pool_wall_offset;

	pool_polygonpos[4] = pool_wall_lG[0] + pool_wall_offset;
	pool_polygonpos[5] = pool_wall_lG[1] + pool_wall_offset;

	pool_polygonpos[6] = pool_wall_lD[0] - pool_wall_offset;
	pool_polygonpos[7] = pool_wall_lD[1] + pool_wall_offset;

	pool_polygon = CreateDynamicPolygon(pool_polygonpos);//gdyby jakimś cudem phisycs nie wykrył

	PoolTD[0] = TextDrawCreate(505.000000, 260.000000, "~n~~n~");
	TextDrawBackgroundColor(PoolTD[0], 255);
	TextDrawFont(PoolTD[0], 1);
	TextDrawLetterSize(PoolTD[0], 0.500000, 0.439999);
	TextDrawColor(PoolTD[0], -1);
	TextDrawSetOutline(PoolTD[0], 0);
	TextDrawSetProportional(PoolTD[0], 1);
	TextDrawSetShadow(PoolTD[0], 1);
	TextDrawUseBox(PoolTD[0], 1);
	TextDrawBoxColor(PoolTD[0], 255);
	TextDrawTextSize(PoolTD[0], 569.000000, -10.000000);

	PoolTD[1] = TextDrawCreate(506.000000, 261.000000, "~n~~n~");
	TextDrawBackgroundColor(PoolTD[1], 255);
	TextDrawFont(PoolTD[1], 1);
	TextDrawLetterSize(PoolTD[1], 0.500000, 0.300000);
	TextDrawColor(PoolTD[1], -1);
	TextDrawSetOutline(PoolTD[1], 0);
	TextDrawSetProportional(PoolTD[1], 1);
	TextDrawSetShadow(PoolTD[1], 1);
	TextDrawUseBox(PoolTD[1], 1);
	TextDrawBoxColor(PoolTD[1], 0x005e47FF);
	TextDrawTextSize(PoolTD[1], 568.000000, 0.000000);

	PoolTD[2] = TextDrawCreate(506.000000, 261.000000, "~n~~n~");
	TextDrawBackgroundColor(PoolTD[2], 255);
	TextDrawFont(PoolTD[2], 1);
	TextDrawLetterSize(PoolTD[2], 0.500000, 0.300000);
	TextDrawColor(PoolTD[2], -1);
	TextDrawSetOutline(PoolTD[2], 0);
	TextDrawSetProportional(PoolTD[2], 1);
	TextDrawSetShadow(PoolTD[2], 1);
	TextDrawUseBox(PoolTD[2], 1);
	TextDrawBoxColor(PoolTD[2], 0x00ce9bFF);
	TextDrawTextSize(PoolTD[2], 501.000000, 0.000000);

	PoolTD[3] = TextDrawCreate(503.000000, 240.000000, "SILA (LPM)");
	TextDrawBackgroundColor(PoolTD[3], 255);
	TextDrawFont(PoolTD[3], 2);
	TextDrawLetterSize(PoolTD[3], 0.280000, 1.699999);
	TextDrawColor(PoolTD[3], 0x00ce9bFF);
	TextDrawSetOutline(PoolTD[3], 1);
	TextDrawSetProportional(PoolTD[3], 1);

	pool_text3d = CreateDynamic3DTextLabel("Bilard - Ladowanie...", 0x00906c98, 3172.6582,-1970.1409,21.8313, 4.0);
	CreateDynamicPickup(1239, 3, 3172.6582,-1970.1409,21.8313);

	return 1;
}

CMD:bilard(playerid, params[])
{
	/*if(!PlayingPool[playerid])
	{
		PlayingPool[playerid] = 1;
		PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		GivePlayerWeapon(playerid, 7, 1);
		PoolScore[playerid] = 0;
		if(!PoolStarted)
		{
			PoolStarted = 1;
			RespawnPoolBalls(1);
		}
	}
	else
	{
		if(PoolAimer != playerid)
		{
			ResetPoolPlayer(playerid);
		}
	}*/
	//---
	if(!IsPlayerInRangeOfPoint(playerid, 7.0, 3169.74023, -1971.90234, 20.81123)) return Error(playerid, "Nie jesteś przy stole bilardowym.");
	new strDialog[1024];
	if(pool_adminid == -1 && !PoolStarted)//można założyć grę
	{
		format(strDialog, 1024, ""COL_WHITE"Wynajęcie stołu kosztuje "COL_GREEN"1000$"COL_WHITE". Jeśli go założysz, otrzymasz uprawnienia organizatora.");
		format(strDialog, 1024, "%s\n"COL_WHITE"Jako organizator, będziesz mógł dodawać lub usuwać graczy z gry.", strDialog);
		format(strDialog, 1024, "%s\n"COL_WHITE"W momencie kiedy się rozłączysz/oddalisz od stołu, uprawnienia te uzyska inna osoba uczestnicząca w grze.", strDialog);
		format(strDialog, 1024, "%s\n"COL_BLUE"Czy chcesz zarezerwować stół za "COL_GREEN"1000$"COL_BLUE"?", strDialog);
		Dialog_Show(playerid, POOLSTART, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_WHITE"Bilard - Wynajęcie stołu "COL_RED"«•", strDialog, "Tak", "Nie");
	}
	else if(pool_adminid == playerid) //jest adminem gry
	{
		format(strDialog, 1024, ""COL_GREEN"[+]Dodaj gracza");
		format(strDialog, 1024, "%s\n"COL_RED"[-]Usuń gracza", strDialog);
		Dialog_Show(playerid, POOLEDIT, DIALOG_STYLE_LIST, ""COL_RED"•» "COL_WHITE"Bilard - Zarządzanie "COL_RED"«•", strDialog, "Wybierz", "Anuluj");
	}
	else Error(playerid, "Stół jest już zarezerwowany. Poproś organizatora o dodanie Cię do gry.");
	return 1;
}

Dialog:POOLSTART(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(pool_adminid == -1 && !PoolStarted)
	{
		if(gracz[playerid][hlfriend] == 0)
		{
			if(Money(playerid) < 1000) return Error(playerid, "Niewystarczająca ilość gotówki.");
			TakeMoney(playerid, 1000);
		}
		else Info(playerid, "Jesteś przyjacielem HL. Nie została od Ciebie pobrana opłata.");
		GivePlayerWeapon(playerid, 7, 1);
		pool_adminid = playerid;
		PlayingPool[playerid] = 1;
		PoolScore[playerid] = 0;

		PoolStarted = 1;
		RespawnPoolBalls(1);
		Info(playerid, "Stół zarezerwowany i można grać! Wpisz /bilard aby zaprosić innych graczy.");
	}
	else Error(playerid, "Stół jest już zarezerwowany. Poproś organizatora o dodanie Cię do gry.");
	return 1;
}

Dialog:POOLEDIT(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0://dodaj
		{
			new strPlayerList[2048];
			format(strPlayerList, 2048, "ID\tNazwa gracza");
			new bool:find = false;
			for(new p = PlayerPoolSize(); p != -1; p--)
			{
				if(!gracz[p][loggedin]) continue;
				if(p == playerid) continue;
				if(gracz[p][admin_spec_enabled] == true) continue;
				if(PlayingPool[p]) continue;
				if(IsPlayerInRangeOfPoint(p, 7.0, 3169.74023, -1971.90234, 20.81123))
				{
					format(strPlayerList, 2048, "%s\n%d\t{%06x}%s", strPlayerList, p, GetPlayerColor(playerid) >>> 8,nick(p));
					find = true;
				}
			}
			if(find) Dialog_Show(playerid, POOLADD, DIALOG_STYLE_TABLIST_HEADERS,  ""COL_RED"•» "COL_WHITE"Lista graczy przy stole "COL_RED"«•", strPlayerList, "Wybierz", "Anuluj");
			else Error(playerid, "Nie znaleziono żadnego gracza w pobliżu stołu bilardowego.");
		}
		case 1://usun
		{
			new strPlayerList[2048];
			format(strPlayerList, 2048, "ID\tNazwa gracza");
			new bool:find = false;
			for(new p = PlayerPoolSize(); p != -1; p--)
			{
				if(!gracz[p][loggedin]) continue;
				if(p == playerid) continue;
				if(gracz[p][admin_spec_enabled] == true) continue;
				if(!PlayingPool[p]) continue;
				if(IsPlayerInRangeOfPoint(p, 7.0, 3169.74023, -1971.90234, 20.81123))
				{
					format(strPlayerList, 2048, "%s\n%d\t{%06x}%s", strPlayerList, p, GetPlayerColor(playerid) >>> 8,nick(p));
					find = true;
				}
			}
			if(find) Dialog_Show(playerid, POOLDEL, DIALOG_STYLE_TABLIST_HEADERS,  ""COL_RED"•» "COL_WHITE"Lista graczy przy stole "COL_RED"«•", strPlayerList, "Wybierz", "Anuluj");
			else Error(playerid, "Nie znaleziono żadnego gracza w pobliżu stołu bilardowego.");
		}
	}
	return 1;
}

Dialog:POOLADD(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(PoolStarted)
	{
		new targetid = strval(inputtext);
		if(IsPlayerInRangeOfPoint(targetid, 7.0, 3169.74023, -1971.90234, 20.81123))
		{
			GivePlayerWeapon(targetid, 7, 1);
			PlayingPool[targetid] = 1;
			PoolScore[targetid] = 0;
			Info(playerid, ""COL_GREEN"Dodałeś gracza do gry w bilarda.");
			Info(targetid, ""COL_GREEN"Zostałeś dodany/a do gry w bilarda!");
		}
		else Error(playerid, "Ten gracz nie jest w pobliżu stołu bilardowego.");
	}
	else Error(playerid, "Stół bilardowy nie jest zarezerwowany.");
	return 1;
}

Dialog:POOLDEL(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(PoolStarted)
	{
		new targetid = strval(inputtext);
		if(IsPlayerInRangeOfPoint(targetid, 7.0, 3169.74023, -1971.90234, 20.81123))
		{
			ResetPoolPlayer(targetid);
			Info(playerid, ""COL_RED"Usunąłeś gracza z gry w bilarda.");
			Info(targetid, ""COL_RED"Zostałeś usunięty/a z gry w bilarda!");
		}
		else Error(playerid, "Ten gracz nie jest w pobliżu stołu bilardowego.");
	}
	else Error(playerid, "Stół bilardowy nie jest zarezerwowany.");
	return 1;
}



task Process_PoolWatchDog(playerid)
{
	if(!PlayingPool[playerid]) return 1;
	if(!IsPlayerInRangeOfPoint(playerid, 7.0, 3169.74023, -1971.90234, 20.81123))//nie jest
	{
		ResetPoolPlayer(playerid);
		LeftNotifyShow(playerid, "Bilard", "Oddaliles sie od stolu bilardowego. Zostales zdyskwalifikowany.", LN_RED);
	}
	return 1;
}

task Porcess_Pool()
{
	if(pool_FixBall_timestamp < serwer[time_timestamp])
	{
		if(AreAllBallsStopped())//odbugowanie bil
		{
			for(new i; i < 16; i++)
			{
				new Float:wX, Float:wY, Float:wZ;
				new Float:wrX, Float:wrY, Float:wrZ;
				GetObjectPos(PoolBall[i][bObject], wX, wY, wZ);
				GetObjectRot(PoolBall[i][bObject], wrX, wrY, wrZ);
				DestroyObject(PoolBall[i][bObject]);
				if(IsPointInDynamicArea(pool_polygon, wX, wY, wZ))
				{
					PoolBall[i][bObject] = CreateObject(GetBallModel(i), wX, wY, wZ, wrX, wrY, wrZ);
					PoolBall[i][b_last_safeX] = wX;
					PoolBall[i][b_last_safeY] = wY;
					PoolBall[i][b_last_safeZ] = wZ;
				}
				else
				{
					if(PoolBall[i][bExisting])
					{
						PHY_DeleteObject(PoolBall[i][bObject]);
						PoolBall[i][bExisting] = 0;
						PoolBall[i][bObject] = CreateObject(GetBallModel(i), PoolBall[i][b_last_safeX], PoolBall[i][b_last_safeY], PoolBall[i][b_last_safeZ], wrX, wrY, wrZ);//wyszła bila poza stół?
						InitBall(i);
					} 
					else PoolBall[i][bObject] = CreateObject(GetBallModel(i), wX, wY, wZ, wrX, wrY, wrZ);
				}
			}
			pool_FixBall_timestamp = serwer[time_timestamp]+7;
		}
	}
	//pool_text3d
	new strPoolText[1024];
	format(strPoolText, 1024, "« Bilard »");
	format(strPoolText, 1024, "%s\nENTER - Kredowanie.", strPoolText);
	format(strPoolText, 1024, "%s\nPPM - Celowanie/Anulowanie celowania.", strPoolText);
	format(strPoolText, 1024, "%s\nA i D - Korygowanie kąta podczas celowania.", strPoolText);
	format(strPoolText, 1024, "%s\nLPM - Uderzenie w bile.", strPoolText);
	format(strPoolText, 1024, "%s\nSHIFT - Zmiana kamery podczas celowania.", strPoolText);
	format(strPoolText, 1024, "%s\n", strPoolText);
	format(strPoolText, 1024, "%s\nLista graczy:", strPoolText);
	new list_count;
	if(pool_adminid == -1)//szukanie nowego admina bilarda
	{
		for(new p = PlayerPoolSize(); p != -1; p--)
		{
			if(!gracz[p][loggedin]) continue;
			if(!PlayingPool[p]) continue;
			pool_adminid = p;
			Info(pool_adminid, "Organizator opuścił rozgrywkę. Zostałeś organizatorem. Użyj /bilard aby zarządzać.");
			break;
		}
	}
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(!gracz[p][loggedin]) continue;
		if(!PlayingPool[p]) continue;
		list_count++;
		format(strPoolText, 1024, "%s\n%d. %s%s(%d) = %d punktów", strPoolText, list_count, (p == pool_adminid) ? ("[Organizator]") : (""), nick(p), p, PoolScore[p]);
	}
	if(list_count == 0) format(strPoolText, 1024, "%s\nBrak grających! Wpisz /bilard aby wynająć stół.", strPoolText);
	format(strPoolText, 1024, "%s\n", strPoolText);
	format(strPoolText, 1024, "%s\n((Oddal się od stołu aby opuścić grę.))", strPoolText);
	UpdateDynamic3DTextLabelText(pool_text3d, 0x00906c98, strPoolText);
	return 1;
}

task ResetPoolPlayer(playerid)
{
	UsingChalk[playerid] = 0;
	PoolScore[playerid] = 0;
	if(pool_adminid == playerid) pool_adminid = -1;
	if(PoolAimer == playerid)//jeśli ten jest w trakcie celowania (poolaimer == -1 brak gracza przy celowaniu)
	{
		PoolAimer = -1;//pilnuje też destroya i nie jest już w trybie celowania
		TextDrawHideForPlayer(playerid, PoolTD[0]);
		TextDrawHideForPlayer(playerid, PoolTD[1]);
		TextDrawHideForPlayer(playerid, PoolTD[2]);
		TextDrawHideForPlayer(playerid, PoolTD[3]);
		DestroyDynamicObject(AimObject);
		SetCameraBehindPlayer(playerid);
	}
	if(PlayingPool[playerid])//jeśli jest grającym
	{
		ResetPlayerWeapons(playerid);
		LoadFractionWeapons(playerid, gracz[playerid][frakcja]);
		PlayingPool[playerid] = 0;//to już nim nie jest
		new
			count = GetPoolPlayersCount();
		if(count <= 0)//i jeżeli jest 0 graczy to reset bil i stop gry
		{
			PoolStarted = 0;
			RespawnPoolBalls();
		}
	}
	return 1;
}


task POOL_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(IsPlayerInRangeOfPoint(playerid, 7.0, 3169.74023, -1971.90234, 20.81123) && PoolAimer != playerid)//jest przy stole i nie jest w trybie celowania
	{
		if(PRESSED(KEY_FIRE))
		{
			SetPlayerArmedWeapon(playerid, 0);
			ApplyAnimation(playerid, "CARRY", "crry_prtial", 1.0, 0, 0, 0, 0, 0);
			MessageGUIEx(playerid, "Info", "Aby uderzyć bile użyj PPM (Prawy przycisk myszy).");
		}
	}
	if(PoolStarted && PlayingPool[playerid])
	{
		if (IsKeyJustUp(KEY_SECONDARY_ATTACK, newkeys, oldkeys))//smarowanie kija
		{
			if(PlayingPool[playerid] && PoolAimer != playerid && !UsingChalk[playerid])
			{
				SetTimerEx("PlayPoolSound", 1400, 0, "d", 31807);
				SetPlayerArmedWeapon(playerid, 0);
				SetPlayerAttachedObject(playerid, OBJ_SLOT_POOL, 338, 6, 0, 0.07, -0.85, 0, 0, 0);
				ApplyAnimation(playerid, "POOL", "POOL_ChalkCue",3.0,0,0,0,0,0,1);
				UsingChalk[playerid] = 1;
				SetTimerEx("RestoreWeapon", 3500, 0, "d", playerid);
			}
		}
		if (IsKeyJustUp(KEY_JUMP, newkeys, oldkeys))//zmiana kamery
		{
			if(PoolAimer == playerid)
			{
				if(PoolCamera[playerid] < 1) PoolCamera[playerid]++;
				else PoolCamera[playerid] = 0;
				new
					Float:poolrot = AimAngle[playerid][0],
					Float:UXa,
					Float:UYa,
					Float:UZa,
					Float:x,
					Float:y;
				GetObjectPos(PoolBall[0][bObject], UXa, UYa, UZa);
				switch(PoolCamera[playerid])
				{
					case 0:
					{
						GetUXUYBehindObjectInAngle(PoolBall[0][bObject], poolrot, x, y, 0.675);
						SetPlayerCameraPos(playerid, x, y, 22.600);
						SetPlayerCameraLookAt(playerid, UXa, UYa, UZa+0.170);
					}
					case 1:
					{
						SetPlayerCameraPos(playerid, 3169.74023, -1972.01, 23.3295);
						SetPlayerCameraLookAt(playerid, 3169.74023, -1971.90234, 20.81123);
					}
					case 2:
					{
						SetPlayerCameraPos(playerid, 3169.74023, -1972.01, 23.3295);
						SetPlayerCameraLookAt(playerid, 3169.74023, -1971.90234, 20.81123);
					}
				}
			}
		}
		if (IsKeyJustUp(KEY_HANDBRAKE, newkeys, oldkeys))//przystąpienie do strzału
		{
			if(AreAllBallsStopped())
			{
				if(PoolAimer != playerid)
				{
					if(!UsingChalk[playerid] && PoolAimer == -1 && PoolBall[0][bExisting])
					{
						new
							Float:poolrot,
							Float:UX,
							Float:UY,
							Float:UZ,
							Float:UXa,
							Float:UYa,
							Float:UZa,
							Float:x,
							Float:y;
						GetPlayerPos(playerid, UX, UY, UZ);
						GetObjectPos(PoolBall[0][bObject], UXa, UYa, UZa);
						if(Is2DPointInRangeOfPoint(UX, UY, UXa, UYa, 1.5) && UZ < 23.3295)
						{
							TogglePlayerControllable(playerid, 0);
							GetAngleToUXUY(UXa, UYa, UX, UY, poolrot);
							SetPlayerFacingAngle(playerid, poolrot);
							AimAngle[playerid][0] = poolrot;
							AimAngle[playerid][1] = poolrot;
							SetPlayerArmedWeapon(playerid, 0);
							GetUXUYInFrontOfPos(UXa, UYa, poolrot+180, x, y, 0.085);
							AimObject = CreateDynamicObject(3004, x, y, UZa, 7.0, 0, poolrot+180, .playerid = playerid);
							switch(PoolCamera[playerid])
							{
								case 0:
								{
									GetUXUYBehindObjectInAngle(PoolBall[0][bObject], poolrot, x, y, 0.675);
									SetPlayerCameraPos(playerid, x, y, 22.600);
									SetPlayerCameraLookAt(playerid, UXa, UYa, UZa+0.170);
								}
								case 1:
								{
									SetPlayerCameraPos(playerid, 3169.74023, -1972.01, 23.3295);
									SetPlayerCameraLookAt(playerid, 3169.74023, -1971.90234, 20.81123);
								}
								case 2:
								{
									SetPlayerCameraPos(playerid, 3169.74023, -1972.01, 23.3295);
									SetPlayerCameraLookAt(playerid, 3169.74023, -1971.90234, 20.81123);
								}
							}
							ApplyAnimation(playerid, "POOL", "POOL_Med_Start",50.0,0,0,0,1,1,1);
							PoolAimer = playerid;
							TextDrawShowForPlayer(playerid, PoolTD[0]);
							TextDrawShowForPlayer(playerid, PoolTD[1]);
							TextDrawTextSize(PoolTD[2], 501.0, 0.0);
							TextDrawShowForPlayer(playerid, PoolTD[2]);
							TextDrawShowForPlayer(playerid, PoolTD[3]);
							PoolPower = 1.0;
							PoolDir = 0;
						}
					}
				}
				else
				{
					TogglePlayerControllable(playerid, 1);
					GivePlayerWeapon(playerid, 7, 1);
					SetPlayerSkin(playerid, GetPlayerSkin(playerid));
					ApplyAnimation(playerid, "CARRY", "crry_prtial", 1.0, 0, 0, 0, 0, 0, 1);
					SetCameraBehindPlayer(playerid);
					PoolAimer = -1;
					DestroyDynamicObject(AimObject);
					TextDrawHideForPlayer(playerid, PoolTD[0]);
					TextDrawHideForPlayer(playerid, PoolTD[1]);
					TextDrawHideForPlayer(playerid, PoolTD[2]);
					TextDrawHideForPlayer(playerid, PoolTD[3]);
				}
			}
		}
		if(IsKeyJustUp(KEY_FIRE, newkeys, oldkeys))//strzał
		{
			if(PoolAimer == playerid)
			{
				new
					Float:speed;
				ApplyAnimation(playerid, "POOL", "POOL_Med_Shot",3.0,0,0,0,0,0,1);
				speed = 0.4 + (PoolPower * 2.0) / 100.0;
				PHY_SetObjectVelocity(PoolBall[0][bObject], speed * floatsin(-AimAngle[playerid][0], degrees), speed * floatcos(-AimAngle[playerid][0], degrees));
				if(PoolCamera[playerid] == 0)
				{
					switch(random(2))
					{
						case 0: SetPlayerCameraPos(playerid, 3169.74023, -1972.01, 23.3295);
						case 1: SetPlayerCameraPos(playerid, 3169.74023, -1972.01, 23.3295);
					}
					SetPlayerCameraLookAt(playerid, 3169.74023, -1971.90234, 20.81123);
				}
				PlayPoolSound(31810);
				PoolAimer = -1;
				DestroyDynamicObject(AimObject);
				GivePlayerWeapon(playerid, 7, 1);
				PoolLastShooter = playerid;
				PoolLastScore = 0;
				TextDrawHideForPlayer(playerid, PoolTD[0]);
				TextDrawHideForPlayer(playerid, PoolTD[1]);
				TextDrawHideForPlayer(playerid, PoolTD[2]);
				TextDrawHideForPlayer(playerid, PoolTD[3]);
			}
		}

	}
	return 1;
}

task pool_PHY_OnObjectUpdate(objectid)
{
	if(PoolStarted)
	{
		for(new i; i < sizeof PoolBall; i++)
		{
			if(objectid == PoolBall[i][bObject] && PHY_IsObjectMoving(PoolBall[i][bObject]))
			{
				new Float:mOPos[3];
				GetObjectPos(PoolBall[i][bObject], mOPos[0], mOPos[1], mOPos[2]);
				if(IsPointInDynamicArea(pool_polygon, mOPos[0], mOPos[1], mOPos[2]))
				{
					PoolBall[i][b_last_safeX] = mOPos[0];
					PoolBall[i][b_last_safeY] = mOPos[1];
					PoolBall[i][b_last_safeZ] = mOPos[2];
				}
				new hole = IsBallInHole(i);

				if(hole)
				{
					new
						Float:speed,
						Float:vx, Float:vy, Float:vz;
					PHY_GetObjectVelocity(PoolBall[i][bObject], vx, vy, vz);
					speed = floatsqroot(vx * vx + vy * vy) + 0.2;

					PoolBall[i][bExisting] = 0;
					PHY_DeleteObject(PoolBall[i][bObject]);

					PlayPoolSound(31803 + random(3));


					switch(hole)
					{
						case 1:
						{
							MoveObject(PoolBall[i][bObject], 3168.7944, -1972.3976, 21.7083-0.25, speed);
							PoolBall[i][b_last_safeX] = 3168.7944;
							PoolBall[i][b_last_safeY] = -1972.3976;
							PoolBall[i][b_last_safeZ] = 21.7083-0.25;
						}
						case 2: 
						{
							MoveObject(PoolBall[i][bObject], 3170.6944, -1972.3976, 21.7083-0.25, speed);
							PoolBall[i][b_last_safeX] = 3170.6944;
							PoolBall[i][b_last_safeY] = -1972.3976;
							PoolBall[i][b_last_safeZ] = 21.7083-0.25;
						}
						case 3: 
						{
							MoveObject(PoolBall[i][bObject], 3170.6944, -1971.3976, 21.7083-0.25, speed);
							PoolBall[i][b_last_safeX] = 3170.6944;
							PoolBall[i][b_last_safeY] = -1971.3976;
							PoolBall[i][b_last_safeZ] = 21.7083-0.25;
						}
						case 4: 
						{
							MoveObject(PoolBall[i][bObject], 3168.7944, -1971.3976, 21.7083-0.25, speed);
							PoolBall[i][b_last_safeX] = 3168.7944;
							PoolBall[i][b_last_safeY] = -1971.3976;
							PoolBall[i][b_last_safeZ] = 21.7083-0.25;
						}
						case 5:
						{
							MoveObject(PoolBall[i][bObject], 3169.7464, -1971.3376, 21.7083-0.25, speed);
							PoolBall[i][b_last_safeX] = 3169.7464;
							PoolBall[i][b_last_safeY] = -1971.3376;
							PoolBall[i][b_last_safeZ] = 21.7083-0.25;
						}
						case 6: 
						{
							MoveObject(PoolBall[i][bObject], 3169.7464, -1972.4476, 21.7083-0.25, speed);
							PoolBall[i][b_last_safeX] = 3169.7464;
							PoolBall[i][b_last_safeY] = -1972.4476;
							PoolBall[i][b_last_safeZ] = 21.7083-0.25;
						}
					}
					if(i)
					{
						PoolScore[PoolLastShooter] ++;
						PoolLastScore ++;
						new string[128];
						format(string, 128, ""COL_RED"[BILARD]"COL_WHITE"{%06x} %s(%d) "COL_GREEN"-> "COL_BLUE"%s "COL_EASY"= "COL_GREEN"%d punktów", GetPlayerColor(PoolLastShooter) >>> 8, nick(PoolLastShooter), PoolLastShooter, GetBallName(GetBallModel(i)), PoolScore[PoolLastShooter]);
						SendPoolPlayersMessage(string);
						if(PoolLastScore > 0) format(string, 128, "~g~~h~+%d", PoolLastScore);
						else format(string, 128, "~r~~h~%d", PoolLastScore);
						GameTextForPlayer(PoolLastShooter, string, 100000, 4);
						PlayerPlaySound(PoolLastShooter, 1250, 0.0, 0.0, 0.0);

					}
					else
					{
						PoolScore[PoolLastShooter] --;
						PoolLastScore --;
						new string[128];
						format(string, 128, ""COL_RED"[BILARD]"COL_WHITE"{%06x} %s(%d) "COL_RED"-> "COL_WHITE"%s "COL_EASY"= "COL_RED"%d punktów", GetPlayerColor(PoolLastShooter) >>> 8, nick(PoolLastShooter), PoolLastShooter, GetBallName(GetBallModel(i)), PoolScore[PoolLastShooter]);
						SendPoolPlayersMessage(string);
						if(PoolLastScore > 0) format(string, 128, "~g~~h~+~r~~h~%d", PoolLastScore);
						else format(string, 128, "~r~~h~%d", PoolLastScore);
						GameTextForPlayer(PoolLastShooter, string, 100000, 4);
						PlayerPlaySound(PoolLastShooter, 1250, 0.0, 0.0, 0.0);
					}
					if(GetPoolBallsCount() <= 1)
					{
						//PoolStarted = 0;
						PoolAimer = -1;
						new
							winscore = GetMaxPoolScore();
						RespawnPoolBalls();
						RestoreCamera(PoolLastShooter);
						PoolLastShooter = -1;
						new string[128];
						foreach (new p : Player)
						{
							if(PlayingPool[p] && PoolScore[p] == winscore)
							{
								format(string, 128, ""COL_RED"[BILARD] "COL_WHITE"Gracz "COL_GREEN"%s"COL_WHITE" wygrał/a. Wynik: "COL_RED"%d"COL_WHITE" punktów.", nick(p), winscore);
								SendPoolPlayersMessage(string);
							}
						}
						foreach (new p : Player)
						{
							ResetPoolPlayer(p);
						}
					}
					else if(AreAllBallsStopped())
					{
						SetTimerEx("RestoreCamera", 800, 0, "d", PoolLastShooter);
						PoolLastShooter = -1;
					}
				}
				return 1;
			}
		}
	}
	return 1;
}

public PHY_OnObjectCollideWithObject(object1, object2)
{
	if(PoolStarted)
	{
		for(new i; i < sizeof PoolBall; i++)
		{
			if(object1 == PoolBall[i][bObject])
			{
				PlayPoolSound(31800 + random(3));
				return 1;
			}
		}
	}
	return 1;
}

public PHY_OnObjectCollideWithWall(objectid, wallid)
{
	if(PoolStarted)
	{
		for(new i; i < sizeof PoolBall; i++)
		{
			if(objectid == PoolBall[i][bObject])
			{
				PlayPoolSound(31808);
				return 1;
			}
		}
	}
	return 1;
}



Float:GetPointDistanceToPoint(Float:x1,Float:y1,Float:x2,Float:y2)
{
	new Float:x, Float:y;
	x = x1-x2;
	y = y1-y2;
	return floatsqroot(x*x+y*y);
}


stock GetAngleToUXUY(Float:UX, Float:UY, Float:CurrUX, Float:CurrUY, &Float:angle)
{
	angle = atan2(UY-CurrUY, UX-CurrUX);
	angle = floatsub(angle, 90.0);
	if(angle < 0.0) angle = floatadd(angle, 360.0);
}


stock GetUXUYInFrontOfPos(Float:xx,Float:yy,Float:a, &Float:x2, &Float:y2, Float:distance)
{
	if(a>360)
	{
		a=a-360;
	}
	xx += (distance * floatsin(-a, degrees));
	yy += (distance * floatcos(-a, degrees));
	x2=xx;
	y2=yy;
}

stock IsPointFacingPoint(Float:dOffset, Float:UX, Float:UY, Float:pA, Float:pUX, Float:pUY)
{
	new
		Float:ang;

	if( UY > pUY ) ang = (-acos((UX - pUX) / floatsqroot((UX - pUX)*(UX - pUX) + (UY - pUY)*(UY - pUY))) - 90.0);
	else if( UY < pUY && UX < pUX ) ang = (acos((UX - pUX) / floatsqroot((UX - pUX)*(UX - pUX) + (UY - pUY)*(UY - pUY))) - 450.0);
	else if( UY < pUY ) ang = (acos((UX - pUX) / floatsqroot((UX - pUX)*(UX - pUX) + (UY - pUY)*(UY - pUY))) - 90.0);

	if(AngleInRangeOfAngle(-ang, pA, dOffset)) return true;

	return false;

}

stock Is2DPointInRangeOfPoint(Float:x, Float:y, Float:x2, Float:y2, Float:range)
{
	x2 -= x;
	y2 -= y;
	return ((x2 * x2) + (y2 * y2)) < (range * range);
}

stock IsObjectInSphere(objectid,Float:x,Float:y,Float:z,Float:radius2)
{
	new Float:x1,Float:y1,Float:z1,Float:tmpdis;
	GetObjectPos(objectid,x1,y1,z1);
	tmpdis = floatsqroot(floatpower(floatabs(floatsub(x,x1)),2)+ floatpower(floatabs(floatsub(y,y1)),2)+ floatpower(floatabs(floatsub(z,z1)),2));
	if(tmpdis < radius2) return 1;
	return 0;
}

GetBallModel(i)
{
	switch(i)
	{
		case 0: return 3003;
		case 1: return 3002;
		case 2: return 3101;
		case 3: return 2995;
		case 4: return 2996;
		case 5: return 3106;
		case 6: return 3105;
		case 7: return 3103;
		case 8: return 3001;
		case 9: return 3100;
		case 10: return 2997;
		case 11: return 3000;
		case 12: return 3102;
		case 13: return 2999;
		case 14: return 2998;
		case 15: return 3104;
	}
	return 0;
}

stock GetBallName(ballmodel)
{
	new ball_name[64];
	switch(ballmodel)
	{
		case 3003: format(ball_name, 64, "biała");
		case 3002: format(ball_name, 64, "żółta (1)");
		case 3101: format(ball_name, 64, "czerwona (3)");
		case 2995: format(ball_name, 64, "biało-żółta (9)");
		case 2996: format(ball_name, 64, "biało-granatowa (10)");
		case 3106: format(ball_name, 64, "czarna (8)");
		case 3105: format(ball_name, 64, "brązowa (7)");
		case 3103: format(ball_name, 64, "pomarańczowa (5)");
		case 3001: format(ball_name, 64, "biało-brązowa (15)");
		case 3100: format(ball_name, 64, "niebieska (2)");
		case 2997: format(ball_name, 64, "biało-czerwona (11)");
		case 3000: format(ball_name, 64, "biało-zielona (14)");
		case 3102: format(ball_name, 64, "fioletowa (4)");
		case 2999: format(ball_name, 64, "biało-pomrańczowa (13)");
		case 2998: format(ball_name, 64, "biało-fioletowa (12)");
		case 3104: format(ball_name, 64, "zielona (6)");
	}
	return ball_name;
}

stock GetPoolBallsCount()
{
	new
		count;
	for(new i; i < 16; i++)
	{
		if(PoolBall[i][bExisting] || i == 0) count++;
	}
	return count;
}


stock GetMaxPoolScore()
{
	new
		scoremax = -1;
	foreach (new i : Player)
	{
		if(PlayingPool[i])
		{
			if(PoolScore[i] > scoremax)
			{
				scoremax = PoolScore[i];
			}
		}
	}
	return scoremax;
}

stock SendPoolPlayersMessage(string[])
{
	foreach (new i : Player)
	{
		if(PlayingPool[i])
		{
			SendClientMessage(i, -1, string);
		}
	}
}

stock AreAllBallsStopped()
{
	new
		Float:x, Float:y, Float:z;
	for(new i; i < 16; i++)
	{
		if(PoolBall[i][bExisting])
		{
			PHY_GetObjectVelocity(PoolBall[i][bObject], x, y, z);
			if(x != 0.0 || y != 0.0)
				return 0;
		}
	}
	return 1;
}

stock RespawnPoolBalls(init = 0)
{
	for(new i; i < 16; i++)
	{
		/*PoolBall[i][bMoving] = 0;
		PoolBall[i][bSpeed] = 0;*/
		//StopObject(PoolBall[i][bObject]);
		DestroyObject(PoolBall[i][bObject]);
		if(PoolBall[i][bExisting])
		{
			PHY_DeleteObject(PoolBall[i][bObject]);
			PoolBall[i][bExisting] = 0;
		}
	}

	if(PoolAimer != -1)
	{
		TogglePlayerControllable(PoolAimer, 1);
		ClearAnimations(PoolAimer);
		ApplyAnimation(PoolAimer, "CARRY", "crry_prtial", 1.0, 0, 0, 0, 0, 0);
		SetCameraBehindPlayer(PoolAimer);
		PoolAimer = -1;
		DestroyDynamicObject(AimObject);
		TextDrawHideForPlayer(PoolAimer, PoolTD[0]);
		TextDrawHideForPlayer(PoolAimer, PoolTD[1]);
		TextDrawHideForPlayer(PoolAimer, PoolTD[2]);
		TextDrawHideForPlayer(PoolAimer, PoolTD[3]);
	}

	CreateBalls();
	if(init)
	{
		for(new i; i < sizeof PoolBall; i++)
			InitBall(i);
	}
}

stock CreateBalls()
{
	PoolBall[0][bObject] = CreateObject(3003, 3169.3027, -1971.8918, 21.7463, 0, 0, 0);//biała
	PoolBall[1][bObject] = CreateObject(3002, 3170.0239, -1971.8893, 21.7463, 0, 0, 0);//żółta 1
	PoolBall[2][bObject] = CreateObject(3101, 3170.0925, -1971.8484, 21.7463, 0, 0, 0);//czerwona
	PoolBall[3][bObject] = CreateObject(2995, 3170.0918, -1971.9279, 21.7463, 0, 0, 0);//żółto biała
	PoolBall[4][bObject] = CreateObject(2996, 3170.1602, -1971.8878, 21.7463, 0, 0, 0);//biało granatowy 10
	PoolBall[5][bObject] = CreateObject(3106, 3170.1610, -1971.9642, 21.7593, 0, 0, 0);//czarna
	PoolBall[6][bObject] = CreateObject(3105, 3170.1592, -1971.8062, 21.7463, 0, 0, 0);//bordowa
	PoolBall[7][bObject] = CreateObject(3103, 3170.2275, -1971.8467, 21.7463, 0, 0, 0);//pomarańczowa
	PoolBall[8][bObject] = CreateObject(3001, 3170.2289, -1971.9274, 21.7463, 0, 0, 0);//biało bordowa
	PoolBall[9][bObject] = CreateObject(3100, 3170.2284, -1972.0054, 21.7463, 0, 0, 0);//granatowa 2
	PoolBall[10][bObject] = CreateObject(2997, 3170.2280, -1971.7695, 21.7463, 0, 0, 0);//biało czerwona
	PoolBall[11][bObject] = CreateObject(3000, 3170.2971, -1971.8110, 21.7463, 0, 0, 0);//biało zielona
	PoolBall[12][bObject] = CreateObject(3102, 3170.2988, -1971.8893, 21.7463, 0, 0, 0);//fioletowa 4
	PoolBall[13][bObject] = CreateObject(2999, 3170.2966, -1971.9677, 21.7463, 0, 0, 0);//biało pomarańczowa
	PoolBall[14][bObject] = CreateObject(2998, 3170.2959, -1972.0437, 21.7463, 0, 0, 0);//fioletowa 12
	PoolBall[15][bObject] = CreateObject(3104, 3170.2976, -1971.7327, 21.7463, 0, 0, 0);//zielona
}

stock InitBall(i)
{
	PHY_InitObject(PoolBall[i][bObject], 3003, _, _, PHY_MODE_2D);
	PHY_SetObjectFriction(PoolBall[i][bObject], 0.40);
	PHY_RollObject(PoolBall[i][bObject], _, PHY_ROLLING_MODE_ADVANCED);
	PHY_SetObjectWorld(PoolBall[i][bObject], 3);
	PoolBall[i][bExisting] = 1;
}



stock GetPoolPlayersCount()
{
	new
		count;
	if(PoolStarted)
	{
		foreach (new i : Player)
		{
			if(PlayingPool[i])
			{
				count++;
			}
		}
	}
	return count;
}

forward PoolTimer();
public PoolTimer()
{
	if(!PoolStarted) return 0;
	if(PoolAimer != -1)
	{
		new
			playerid = PoolAimer,
			keys,
			ud,
			lr;
		GetPlayerKeys(playerid, keys, ud, lr);
		if(!(keys & KEY_FIRE))
		{
			if(lr)
			{
				new
					Float:UX,
					Float:UY,
					Float:UZ,
					Float:UXa,
					Float:UYa,
					Float:UZa,
					Float:x,
					Float:y,
					Float:newrot,
					Float:dist;
				GetPlayerPos(playerid, UX, UY ,UZ);
				GetObjectPos(PoolBall[0][bObject], UXa, UYa, UZa);
				newrot = AimAngle[playerid][0] + (lr > 0 ? 0.9 : -0.9);
				dist = GetPointDistanceToPoint(UX, UY, UXa, UYa);
				if(AngleInRangeOfAngle(AimAngle[playerid][1], newrot, 19.0))
				{
					AimAngle[playerid][0] = newrot;
					switch(PoolCamera[playerid])
					{
						case 0:
						{
							GetUXUYBehindObjectInAngle(PoolBall[0][bObject], newrot, x, y, 0.675);
							SetPlayerCameraPos(playerid, x, y, 22.600);
							SetPlayerCameraLookAt(playerid, UXa, UYa, UZa+0.170);
						}
						case 1:
						{
							SetPlayerCameraPos(playerid, 3169.74023, -1972.01, 23.3295);
							SetPlayerCameraLookAt(playerid, 3169.74023, -1971.90234, 20.81123);
						}
						case 2:
						{
							SetPlayerCameraPos(playerid, 3169.74023, -1972.01, 23.3295);
							SetPlayerCameraLookAt(playerid, 3169.74023, -1971.90234, 20.81123);
						}
					}
					GetUXUYInFrontOfPos(UXa, UYa, newrot+180, x, y, 0.085);
					SetDynamicObjectPos(AimObject, x, y, UZa);
					SetDynamicObjectRot(AimObject, 7.0, 0, AimAngle[playerid][0]+180);
					GetUXUYInFrontOfPos(UXa, UYa, newrot+180, UX, UY, dist);
					SetPlayerPos(playerid, UX, UY, UZ);
					SetPlayerFacingAngle(playerid, newrot);
				}
			}
		}
		else
		{
			if(PoolDir)
				PoolPower -= 2.0;
			else
				PoolPower += 2.0;
			if(PoolPower <= 0)
			{
				PoolDir = 0;
				PoolPower = 2.0;
			}
			else if(PoolPower > 100.0)
			{
				PoolDir = 1;
				PoolPower = 98.0;
			}
			TextDrawTextSize(PoolTD[2], 501.0 + ((67.0 * PoolPower)/100.0), 0.0);
			TextDrawShowForPlayer(playerid, PoolTD[2]);
		}
	}

	if(PoolLastShooter != -1 && AreAllBallsStopped())
	{
		SetTimerEx("RestoreCamera", 800, 0, "d", PoolLastShooter);
		PoolLastShooter = -1;
	}
	return 1;
}

forward RestoreCamera(playerid);
public RestoreCamera(playerid)
{
	if(!PoolBall[0][bExisting])
	{
		DestroyObject(PoolBall[0][bObject]);
		PoolBall[0][bObject] = CreateObject(GetBallModel(0) ,3169.3027, -1971.8918, 21.7463, 0, 0, 0);
		InitBall(0);
	}
	GameTextForPlayer(playerid, " ", 100000, 4);
	//ApplyAnimation(playerid, "CARRY", "crry_prtial", 1.0, 0, 0, 0, 0, 0, 1);
	if(PoolAimer == playerid) return 0;
	TogglePlayerControllable(playerid, 1);
	SetPlayerSkin(playerid, GetPlayerSkin(playerid));
	return SetCameraBehindPlayer(playerid);
}

forward RestoreWeapon(playerid);
public RestoreWeapon(playerid)
{
	RemovePlayerAttachedObject(playerid, OBJ_SLOT_POOL);
	UsingChalk[playerid] = 0;
	GivePlayerWeapon(playerid, 7, 1);
	ApplyAnimation(playerid, "CARRY", "crry_prtial", 1.0, 0, 0, 0, 0, 0, 1);
	return 1;
}

stock IsBallInHole(i)//do symulacji spadku bili w dziure
{
	if(IsObjectInSphere(PoolBall[i][bObject],3168.7944, -1972.3976, 21.7083,0.0900)) return 1;
	else if(IsObjectInSphere(PoolBall[i][bObject],3170.6944, -1972.3976, 21.7083,0.0900)) return 2;
	else if(IsObjectInSphere(PoolBall[i][bObject],3170.6944, -1971.3976, 21.7083,0.0900)) return 3;
	else if(IsObjectInSphere(PoolBall[i][bObject],3168.7944, -1971.3976, 21.7083,0.0900)) return 4;
	else if(IsObjectInSphere(PoolBall[i][bObject],3169.7464, -1971.3376, 21.7083,0.0900)) return 5;
	else if(IsObjectInSphere(PoolBall[i][bObject],3169.7464, -1972.4476, 21.7083,0.0900)) return 6;
	else return 0;
}

stock GetUXUYBehindObjectInAngle(objectid, Float:a, &Float:x2, &Float:y2, Float:distance)
{
	new Float:z;
	GetObjectPos(objectid, x2, y2, z);

	x2 += (distance * floatsin(-a+180, degrees));
	y2 += (distance * floatcos(-a+180, degrees));
}

forward PlayPoolSound(soundid);
public PlayPoolSound(soundid)
{
	foreach(new i : Player)
	{
		if(PlayingPool[i])
		{
			PlayerPlaySound(i, soundid, 0, 0, 0);
		}
	}
	return 1;
}

stock IsKeyJustDown(key, newkeys, oldkeys)
{
	if((newkeys & key) && !(oldkeys & key)) return 1;
	return 0;
}

stock IsKeyJustUp(key, newkeys, oldkeys)
{
	if(!(newkeys & key) && (oldkeys & key)) return 1;
	return 0;
}

stock PreloadAnimLib(playerid, animlib[])
{
	ApplyAnimation(playerid,animlib,"null",0.0,0,0,0,0,0);
}

stock AngleInRangeOfAngle(Float:a1, Float:a2, Float:range)
{
	a1 -= a2;
	if((a1 < range) && (a1 > -range)) return true;

	return false;
}

stock PlayerWhileAimPool(playerid)
{
	if(PoolAimer == playerid) return 1;
	return 0;
}