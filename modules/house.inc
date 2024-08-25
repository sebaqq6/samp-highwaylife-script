/*
postęp prac nad mappowaniem interiorów:
- zarys szkieletu skryptu
- Dodanie opcji do GUI.
- Dodanie możliwości zdecydowania czy swój czy oryginalny interior (opłata)
- Opcja do ustalania pozycji wyścia z interioru.
- Przygotować edytor map (level 1) do budowania per gracz.
- Wytypować obiekty jakie można użyć w domku.
- Przywracanie removeobj
*/

stock Init_House()
{
	mq_format("SELECT d . * , k.Nick OwnerNick, k2.Nick RenterNick FROM domki AS d LEFT JOIN Konta AS k ON k.id = d.owneruid LEFT JOIN Konta AS k2 ON k2.id = d.renteruid;");
	mq_send("LoadHousesFromDB");
	//własny interior, plansza:
	CreateDynamicObject(11083, 7.25456, 9.90522, 42.49894+2000.0,   0.00000, 0.00000, 0.00000, -1, 10);
	CreateDynamicObject(11083, 7.47269, 9.89178, 49.08620+2000.0,   180.00000, 0.00000, 180.00000, -1, 10);
	CreateDynamicObject(8357, 13.37851, 87.18410, 44.63870+2000.0,   0.00000, 90.00000, 270.47983, -1, 10);
	return 1;
}
new Float:house_myintpos[3] = {7.3301,1.8561,2040.4911};

task LoadHousesFromDB()
{
	mq_getdata();
	if(rekordy)
	{
		new i;
		new hid;
		new hOwnerNick[24];
		new hRenterNick[24];
		while(i < rekordy)
		{
			hid = GetFreeHouseID();
			cache_get_value_name_int(i, "id", 			house[hid][h_id]);
			cache_get_value_name_int(i, "owneruid", 		house[hid][h_owneruid]);
			cache_get_value_name_int(i, "renteruid", 		house[hid][h_renteruid]);
			cache_get_value_name_float(i, "extX", 			house[hid][h_extX]);
			cache_get_value_name_float(i, "extY", 			house[hid][h_extY]);
			cache_get_value_name_float(i, "extZ", 			house[hid][h_extZ]);
			cache_get_value_name_float(i, "intX", 			house[hid][h_intX]);
			cache_get_value_name_float(i, "intY", 			house[hid][h_intY]);
			cache_get_value_name_float(i, "intZ", 			house[hid][h_intZ]);
			cache_get_value_name_float(i, "ex_intX", 		house[hid][h_ex_intX]);
			cache_get_value_name_float(i, "ex_intY", 		house[hid][h_ex_intY]);
			cache_get_value_name_float(i, "ex_intZ", 		house[hid][h_ex_intZ]);
			cache_get_value_name_int(i, "interior", 			house[hid][h_interior]);
			cache_get_value_name_int(i, "price", 			house[hid][h_price]);
			cache_get_value_name_int(i, "expire", 			house[hid][h_expire]);
			cache_get_value_name_int(i, "open", 			house[hid][h_open]);
			cache_get_value_name_int(i, "customint", 		house[hid][h_customint]);
			if(house[hid][h_expire] == 0) house[hid][h_expire] = serwer[time_timestamp];
			cache_get_value_name(i, "OwnerNick", hOwnerNick, 24);
			cache_get_value_name(i, "RenterNick", hRenterNick, 24);
			if(house[hid][h_expire] <= serwer[time_timestamp] && house[hid][h_owneruid] != 0)//Wygasanie domków
			{
				house[hid][h_owneruid] = 0;
				house[hid][h_renteruid] = 0;
				house[hid][h_expire] = 0;
				house[hid][h_open] = 1;
				mq_format("UPDATE `domki` SET `owneruid`='%d', `renteruid`='%d', `open`='%d', `expire`='%d' WHERE `id`='%d';", house[hid][h_owneruid], house[hid][h_renteruid], house[hid][h_open], house[hid][h_expire], house[hid][h_id]);
				mq_send("QHouseRemove");
				printf("[HOUSE] Dom ID: %d (Wlasciciel: %s) - Wygasl!", house[hid][h_id], hOwnerNick);
			}
			if(house[hid][h_owneruid] == 0)//brak właściciela
			{
				house[hid][h_pickup] = CreateDynamicPickup(1273, 1, house[hid][h_extX], house[hid][h_extY], house[hid][h_extZ]);
				house[hid][h_icon] = CreateDynamicMapIcon(house[hid][h_extX], house[hid][h_extY], house[hid][h_extZ], 31, 0, .streamdistance = 200.0, .style = MAPICON_LOCAL);
			}
			else
			{
				if(house[hid][h_open]) house[hid][h_pickup] = CreateDynamicPickup(1272, 1, house[hid][h_extX], house[hid][h_extY], house[hid][h_extZ]);
				else house[hid][h_pickup] = CreateDynamicPickup(19522, 1, house[hid][h_extX], house[hid][h_extY], house[hid][h_extZ]);
				house[hid][h_icon] = CreateDynamicMapIcon(house[hid][h_extX], house[hid][h_extY], house[hid][h_extZ], 32, 0, .streamdistance = 200.0, .style = MAPICON_LOCAL);
			}
			house[hid][h_text3dext] = CreateDynamic3DTextLabel("---", -1, house[hid][h_extX], house[hid][h_extY], house[hid][h_extZ], 10.0);
			house[hid][h_text3dint] = CreateDynamic3DTextLabel("---", -1, house[hid][h_intX], house[hid][h_intY], house[hid][h_intZ], 10.0, .worldid = HOUSE_VWOFFSET+hid);
			//polygon
			cache_get_value_name_int(i, "polygon_count", 		house[hid][h_polygoncount]);
			if(house[hid][h_polygoncount] >= 6)//do exteriorów minmum 3 koordy (6 danych x+y)
			{
				new sscanf_format[16];
				new zpolygons_rawdata[5000];
				new Float:zpolygons[8192];
				cache_get_value_name(i, "polygon_data", zpolygons_rawdata, 5000);
				format(sscanf_format, 16, "a<f>[%d]", 8192);
				sscanf(zpolygons_rawdata, sscanf_format, zpolygons);
				house[hid][h_polygonid] = CreateDynamicPolygon(zpolygons, house[hid][h_extZ]-5.0, house[hid][h_extZ]+15.0, house[hid][h_polygoncount], 0, 0);
			}
			UpdateHouseLabel(hid, hOwnerNick, hRenterNick);
			i++;
		}
	}
	return 1;
}

stock GetFreeHouseID()
{
	for(new h; h < MAX_HOUSES; h++)
	{
		if(house[h][h_id] == 0) return h;
	}
	return -1;
}



stock House_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(gracz[playerid][loading_objects]) return 1;
	if(PRESSED(KEY_HANDBRAKE))
	{
		for(new h; h < MAX_HOUSES; h++)
		{
			if(house[h][h_id] == 0) continue;
			if((IsPlayerInRangeOfPoint(playerid, 1.2, house[h][h_extX], house[h][h_extY], house[h][h_extZ]) || (IsPlayerInRangeOfPoint(playerid, 1.2, house[h][h_intX], house[h][h_intY], house[h][h_intZ])  && GetPlayerVirtualWorld(playerid) == HOUSE_VWOFFSET+h && GetPlayerInterior(playerid) == house[h][h_interior]) || (IsPlayerInRangeOfPoint(playerid, 1.2, house[h][h_ex_intX], house[h][h_ex_intY], house[h][h_ex_intZ]) && GetPlayerVirtualWorld(playerid) == HOUSE_VWOFFSET+h && GetPlayerInterior(playerid) == house[h][h_interior])))
			{
				new strHMenu[1024];
				if(house[h][h_owneruid] == 0)//brak właściciela
				{
					format(strHMenu, 1024, ""COL_LIME"•»\t"COL_GREEN"Wejdź"COL_WHITE"/"COL_RED"Wyjdź "COL_WHITE"\t"COL_LIME"«•");//0
					format(strHMenu, 1024, "%s\n"COL_LIME"•»\t"COL_RED"Kup posiadłość za "COL_GREEN"%d$\t"COL_LIME"«•", strHMenu, house[h][h_price]);//1
				}
				else//jest właściciel
				{
					format(strHMenu, 1024, ""COL_LIME"•»\t"COL_GREEN"Wejdź"COL_WHITE"/"COL_RED"Wyjdź "COL_WHITE"\t"COL_LIME"«•");//0
					if(house[h][h_owneruid] == gracz[playerid][UID] || house[h][h_renteruid] == gracz[playerid][UID])
					{
						format(strHMenu, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"Otwórz"COL_WHITE"/"COL_RED"Zamknij "COL_WHITE"dom\t"COL_LIME"«•", strHMenu);//1
						format(strHMenu, 1024, "%s\n"COL_LIME"•»\t"COL_BLUE"Zregeneruj siły\t"COL_LIME"«•", strHMenu);//2
						format(strHMenu, 1024, "%s\n"COL_LIME"•»\t"COL_BLUE"Dodaj/Usuń lokatora\t"COL_LIME"«•", strHMenu);//3
						format(strHMenu, 1024, "%s\n"COL_LIME"•»\t"COL_RED"Sprzedaj\t"COL_LIME"«•", strHMenu);//4
						format(strHMenu, 1024, "%s\n"COL_LIME"•»\t"COL_ORANGE"Przedłuż ważność\t"COL_LIME"«•", strHMenu);//5
						if(house[h][h_customint] == 1) format(strHMenu, 1024, "%s\n"COL_LIME"•»\t"COL_RED"Dezaktywuj "COL_LIME"własny interior\t"COL_LIME"«•", strHMenu);//6
						else format(strHMenu, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"Aktywuj "COL_LIME"własny interior\t"COL_LIME"«•", strHMenu);//6
					}
				}
				SetPVarInt(playerid, "housemenu_h_id", h);
				Dialog_Show(playerid, HOUSEMENU, DIALOG_STYLE_TABLIST, ""COL_RED"•» "COL_WHITE"Dom - "COL_ORANGE"Menu "COL_RED"«•", strHMenu, "Wybierz", "Anuluj");
				break;
			}
		}
	}
	return 1;
}

Dialog:HOUSEMENU(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(gracz[playerid][loading_objects]) return 1;
	new sel_h_id = GetPVarInt(playerid, "housemenu_h_id");
	if(house[sel_h_id][h_owneruid] == 0)//brak właściciela
	{
		switch(listitem)
		{
			case 0://Wejdź do środka
			{
				if(IsPlayerInRangeOfPoint(playerid, 1.2, house[sel_h_id][h_extX], house[sel_h_id][h_extY], house[sel_h_id][h_extZ]))//wchodzenie
				{
					if(house[sel_h_id][h_customint] == 1)
					{
						FreezeLoadObject(playerid, house[sel_h_id][h_ex_intX], house[sel_h_id][h_ex_intY], house[sel_h_id][h_ex_intZ]);
						SetPlayerVirtualWorld(playerid, HOUSE_VWOFFSET+sel_h_id);
						SetPlayerInterior(playerid, 10);
					}
					else
					{
						FreezeLoadObject(playerid, house[sel_h_id][h_intX], house[sel_h_id][h_intY], house[sel_h_id][h_intZ]);
						SetPlayerVirtualWorld(playerid, HOUSE_VWOFFSET+sel_h_id);
						SetPlayerInterior(playerid, house[sel_h_id][h_interior]);
					}
				}
				else if(IsPlayerInRangeOfPoint(playerid, 1.2, house[sel_h_id][h_intX], house[sel_h_id][h_intY], house[sel_h_id][h_intZ]) || IsPlayerInRangeOfPoint(playerid, 1.2, house[sel_h_id][h_ex_intX], house[sel_h_id][h_ex_intY], house[sel_h_id][h_ex_intZ]))
				{
					if(GetPlayerVirtualWorld(playerid) == HOUSE_VWOFFSET+sel_h_id && GetPlayerInterior(playerid) == house[sel_h_id][h_interior])
					{
						FreezeLoadObject(playerid, house[sel_h_id][h_extX], house[sel_h_id][h_extY], house[sel_h_id][h_extZ]);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerInterior(playerid, 0);
						Info(playerid, "Opuściłeś/aś dom.");
					}
				}
				printf("%d", (house[sel_h_id][h_customint] == 1 && IsPlayerInRangeOfPoint(playerid, 1.2, house[sel_h_id][h_ex_intX], house[sel_h_id][h_ex_intY], house[sel_h_id][h_ex_intZ])));
			}
			case 1://Kup posiadłość
			{
				if(Money(playerid) < house[sel_h_id][h_price]) return Error(playerid, "Niewystarczająca ilość gotówki.");
				TakeMoney(playerid, house[sel_h_id][h_price]);//zabranie kasy
				//aktualizacja danych
				house[sel_h_id][h_owneruid] = gracz[playerid][UID];
				house[sel_h_id][h_open] = 0;
				house[sel_h_id][h_expire] = serwer[time_timestamp]+((60*60)*24)*30;
				mq_format("UPDATE `domki` SET `owneruid`='%d', `open`='%d', `expire`='%d' WHERE `id`='%d';", house[sel_h_id][h_owneruid], house[sel_h_id][h_open], house[sel_h_id][h_expire], house[sel_h_id][h_id]);
				mq_send("QHouseBuy");
				//aktualizacja 3dtextu
				UpdateHouseLabel(sel_h_id);
				//info o udanym zakupie
				new strHouse[144];
				format(strHouse, 144, "Gratulacje! Zakupiles dom za ~g~%d$~w~. Od teraz przy logowaniu bedziesz mogl wybrac lokalizacje spawnu!", house[sel_h_id][h_price]);
				LeftNotifyShow(playerid, "Gratualcje!", strHouse, LN_GREEN, 30);	
			}
		}
	}
	else// if(house[sel_h_id][h_owneruid] == gracz[playerid][UID] || house[sel_h_id][h_renteruid] == gracz[playerid][UID])//jest właściucielem lokatorem-===================================================================
	{
		switch(listitem)
		{
			case 0://Wejdź do środka/Wyjdź na zewnątrz
			{
				if(IsPlayerInRangeOfPoint(playerid, 1.2, house[sel_h_id][h_extX], house[sel_h_id][h_extY], house[sel_h_id][h_extZ]))//wchodzenie
				{
					if(house[sel_h_id][h_owneruid] == gracz[playerid][UID] || house[sel_h_id][h_renteruid] == gracz[playerid][UID])
					{
						if(house[sel_h_id][h_customint] == 1) 
						{
							FreezeLoadObject(playerid, house[sel_h_id][h_ex_intX], house[sel_h_id][h_ex_intY], house[sel_h_id][h_ex_intZ]);
							SetPlayerVirtualWorld(playerid, HOUSE_VWOFFSET+sel_h_id);
							SetPlayerInterior(playerid, 10);
						}
						else
						{
							FreezeLoadObject(playerid, house[sel_h_id][h_intX], house[sel_h_id][h_intY], house[sel_h_id][h_intZ]);
							SetPlayerVirtualWorld(playerid, HOUSE_VWOFFSET+sel_h_id);
							SetPlayerInterior(playerid, house[sel_h_id][h_interior]);
						}
						if(house[sel_h_id][h_open] == 0) Info(playerid, ""COL_RED"Ten dom jest zamknięty"COL_WHITE". Goście nie mogą wchodzić do środka.");
					}
					else if(house[sel_h_id][h_open] == 1)
					{
						if(house[sel_h_id][h_customint] == 1)
						{
							FreezeLoadObject(playerid, house[sel_h_id][h_ex_intX], house[sel_h_id][h_ex_intY], house[sel_h_id][h_ex_intZ]);
							SetPlayerVirtualWorld(playerid, HOUSE_VWOFFSET+sel_h_id);
							SetPlayerInterior(playerid, 10);
						}
						else
						{
							FreezeLoadObject(playerid, house[sel_h_id][h_intX], house[sel_h_id][h_intY], house[sel_h_id][h_intZ]);
							SetPlayerVirtualWorld(playerid, HOUSE_VWOFFSET+sel_h_id);
							SetPlayerInterior(playerid, house[sel_h_id][h_interior]);
						}
					}
					else Error(playerid, "Ten dom jest zamknięty");
				}
				else if(IsPlayerInRangeOfPoint(playerid, 1.2, house[sel_h_id][h_intX], house[sel_h_id][h_intY], house[sel_h_id][h_intZ]) || IsPlayerInRangeOfPoint(playerid, 1.2, house[sel_h_id][h_ex_intX], house[sel_h_id][h_ex_intY], house[sel_h_id][h_ex_intZ]))
				{
					if(GetPlayerVirtualWorld(playerid) == HOUSE_VWOFFSET+sel_h_id && GetPlayerInterior(playerid) == house[sel_h_id][h_interior])
					{
						FreezeLoadObject(playerid, house[sel_h_id][h_extX], house[sel_h_id][h_extY], house[sel_h_id][h_extZ]);
						SetPlayerVirtualWorld(playerid, 0);
						SetPlayerInterior(playerid, 0);
						Info(playerid, "Opuściłeś/aś dom.");
					}
				}
			}
			case 1://Otwórz/Zamknij
			{
				if(house[sel_h_id][h_owneruid] == gracz[playerid][UID] || house[sel_h_id][h_renteruid] == gracz[playerid][UID])
				{
					if(house[sel_h_id][h_open])//jest otwarty to zamykamy...
					{
						house[sel_h_id][h_open] = 0;
						LeftNotifyShow(playerid, "Zamek", "Dom zostal ~r~zamkniety~w~.");
					}
					else //jest zamknięty więc otwieramy
					{
						house[sel_h_id][h_open] = 1;
						LeftNotifyShow(playerid, "Zamek", "Dom zostal ~g~otwarty~w~.");
					}
					mq_format("UPDATE `domki` SET `open`='%d' WHERE `id`='%d';", house[sel_h_id][h_open], house[sel_h_id][h_id]);
					mq_send("QHouseDoor");
					//aktualizacja 3dtextu i tworzenie ikony i pickupa
					UpdateHouseLabel(sel_h_id);
				}
				else Error(playerid, "Brak uprawnień.");
			}
			case 2://Zregeneruj siły
			{
				if(house[sel_h_id][h_owneruid] == gracz[playerid][UID] || house[sel_h_id][h_renteruid] == gracz[playerid][UID])
				{
					gracz[playerid][stamina] = 100;
					HUD_UpdateSTAMINA(playerid);
					mq_format("UPDATE `Konta` SET `stamina`='%d' WHERE `id`='%d';", gracz[playerid][stamina], gracz[playerid][UID]);
					mq_send("QUpdateStamina");
					LeftNotifyShow(playerid, "Stamina", "Sily zostaly ~g~zregenerowane~w~.", LN_GREEN);
				}
				else Error(playerid, "Brak uprawnień.");
			}
			case 3://Dodaj/Usuń lokatora
			{
				if(house[sel_h_id][h_owneruid] == gracz[playerid][UID] || house[sel_h_id][h_renteruid] == gracz[playerid][UID])
				{
					new strRenter[512];
					if(house[sel_h_id][h_renteruid] != 0) format(strRenter, 512, ""COL_LIME"•»\t"COL_RED"Usuń lokatora ("COL_BLUE"%s"COL_RED")\t"COL_LIME"«•", GetPlayerIGName(house[sel_h_id][h_renteruid]));
					else format(strRenter, 512, ""COL_LIME"•»\t"COL_GREEN"Dodaj lokatora\t"COL_LIME"«•");
					Dialog_Show(playerid, HOMESETRENTER, DIALOG_STYLE_TABLIST, ""COL_RED"•» "COL_WHITE"Dom - "COL_ORANGE"Dodaj/Usuń lokatora "COL_RED"«•", strRenter, "Wybierz", "Anuluj");
				}
				else Error(playerid, "Brak uprawnień.");
			}
			case 4://Sprzedaj
			{
				if(house[sel_h_id][h_owneruid] == gracz[playerid][UID])
				{
					new strPlayerList[2048];
					format(strPlayerList, 2048, "ID\tNazwa gracza");
					new bool:find = false;
					for(new p = PlayerPoolSize(); p != -1; p--)
					{
						if(!gracz[p][loggedin]) continue;
						if(p == playerid) continue;
						if(gracz[p][admin_spec_enabled] == true) continue;
						new Float:pPos[3];
						GetPlayerPos(p, pPos[0], pPos[1], pPos[2]);
						if(IsPlayerInRangeOfPoint(playerid, 4.0, pPos[0], pPos[1], pPos[2]))
						{
							format(strPlayerList, 2048, "%s\n%d\t{%06x}%s", strPlayerList, p, GetPlayerColor(playerid) >>> 8,nick(p));
							find = true;
						}
					}
					if(find) Dialog_Show(playerid, HOMESELLPLAYER, DIALOG_STYLE_TABLIST_HEADERS,  ""COL_RED"•» "COL_WHITE"Lista graczy w pobliżu "COL_RED"«•", strPlayerList, "Wybierz", "Anuluj");
					else Error(playerid, "Nie znaleziono żadnego gracza w pobliżu, któremu mógłbyś sprzedać dom.");
				}
				else Error(playerid, "Brak uprawnień.");
			}
			case 5://Przedłuż ważność
			{
				if(house[sel_h_id][h_owneruid] == gracz[playerid][UID] || house[sel_h_id][h_renteruid] == gracz[playerid][UID])
				{
					new time_h_expire = house[sel_h_id][h_expire]-serwer[time_timestamp];
					new dd, hh, mm, ss;
					if(time_h_expire < 0) time_h_expire = 0;
					SecToTime(time_h_expire, dd, hh, mm, ss);
					new strExpire[512];
					if(dd > 25) return Error(playerid, "Twój domek jeszcze nie traci ważności.");
					format(strExpire, 512, ""COL_WHITE"Ważność Twojej posiadłości (UID: %d) wygaśnie za: "COL_EASY"%d dni, %d godzin.", sel_h_id, dd, hh);
					format(strExpire, 512, "%s\n"COL_WHITE"Czy chcesz przedłużyć ważność o kolejne 30 dni?", strExpire);
					format(strExpire, 512, "%s\nKoszt opłaty: "COL_GREEN"50 000$", strExpire);
					Dialog_Show(playerid, ADDEXPIREHOME, DIALOG_STYLE_MSGBOX,  ""COL_RED"•» "COL_WHITE"Dom - "COL_ORANGE"Przedłuż ważność "COL_RED"«•", strExpire, "Oplac", "Anuluj");
				}
			}
			case 6://aktywuj dezaktywuj własny interior
			{
				if(house[sel_h_id][h_customint] == 0)
				{
					house[sel_h_id][h_customint] = 1;
					house[sel_h_id][h_ex_intX] = house_myintpos[0];
					house[sel_h_id][h_ex_intY] = house_myintpos[1];
					house[sel_h_id][h_ex_intZ] = house_myintpos[2];
					Info(playerid, "Aktywacja");
				}
				else
				{
					house[sel_h_id][h_customint] = 0;
					Info(playerid, "Dezaktywacja");
				}
				UpdateHouseLabel(sel_h_id);
			}
		}
	}
	return 1;
}

Dialog:ADDEXPIREHOME(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new sel_h_id = GetPVarInt(playerid, "housemenu_h_id");
	if(Money(playerid) < 50000) return Error(playerid, "Niewystarczająca ilość gotówki.");
	if(house[sel_h_id][h_owneruid] == gracz[playerid][UID] || house[sel_h_id][h_renteruid] == gracz[playerid][UID])
	{
		TakeMoney(playerid, 50000);
		house[sel_h_id][h_expire] = house[sel_h_id][h_expire]+((60*60)*24)*30;
		mq_format("UPDATE `domki` SET `expire`='%d' WHERE `id`='%d';", house[sel_h_id][h_expire], house[sel_h_id][h_id]);
		mq_send("QHouseExpire");
		//aktualizacja
		UpdateHouseLabel(sel_h_id);
		Info(playerid, "Ważność przedłużona!");
	}
	else Error(playerid, "Coś poszło nie tak. Spróbuj ponownie.");
	return 1;
}

Dialog:HOMESELLPLAYER(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new clientid = strval(inputtext);
	SetPVarInt(playerid, "cache_homesell_clientid", clientid);
	new Float:pPos[3];
	GetPlayerPos(clientid, pPos[0], pPos[1], pPos[2]);
	if(IsPlayerInRangeOfPoint(playerid, 4.0, pPos[0], pPos[1], pPos[2]))
	{
		if(gracz[clientid][PGodz] < 6) return Error(playerid, "Gracz musi mieć minimum 6 godzin całkowitego czasu ONLINE.");
		new strOffer[1024];
		format(strOffer, 1024, ""COL_LIME"Podaj cenę"COL_WHITE", za jaką chcesz sprzedać dom graczowi "COL_ORANGE"%s(%d)"COL_WHITE".\n", nick(clientid), clientid);
		Dialog_Show(playerid, HOMESELLPRICE, DIALOG_STYLE_INPUT,  ""COL_RED"•» "COL_WHITE"Podaj cenę "COL_RED"«•", strOffer, "Oferuj", "Anuluj");
	}
	else Error(playerid, "Gracz któremu chcesz sprzedać dom, nie jest w pobliżu.");
	return 1;
}


Dialog:HOMESELLPRICE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new sel_h_id = GetPVarInt(playerid, "housemenu_h_id");
	new clientid = GetPVarInt(playerid, "cache_homesell_clientid");
	new price = strval(inputtext);
	if(price < 0) return Error(playerid, "Kwota nie może być mniejsza niż 0$.");
	if(price > 10000000) return Error(playerid, "Kwota nie może być większa niż 10000000$.");
	new Float:pPos[3];
	GetPlayerPos(clientid, pPos[0], pPos[1], pPos[2]);
	if(IsPlayerInRangeOfPoint(playerid, 4.0, pPos[0], pPos[1], pPos[2]))
	{
		if(price > Money(clientid)) return Error(playerid, "Ten gracz nie posiada przy sobie takiej ilości gotówki.");
		new strOffer[3000];
		format(strOffer, 3000, ""COL_WHITE"Otrzymałeś ofertę zakupu domu "COL_GREEN"(UID: %d)"COL_WHITE" od gracza "COL_ORANGE"%s(%d)"COL_WHITE" za kwotę "COL_LIME"%d$"COL_WHITE".", house[sel_h_id][h_id], nick(playerid), playerid, price);
		format(strOffer, 3000, "%s\n"COL_WHITE"Jeśli akcpetujesz ofertę, wpisz poniżej słowo: "COL_LIME"akceptuje", strOffer);
		Dialog_Show(clientid, HOMESELLOFFER, DIALOG_STYLE_INPUT,  ""COL_RED"•» "COL_WHITE"Oferta kupna domu "COL_RED"«•", strOffer, "Potwierdz", "Anuluj");
		format(strOffer, 3000, ""COL_WHITE"Trwa oczekiwanie, aż "COL_ORANGE"%s"COL_WHITE" zaakceptuje Twoją ofertę. Jeśli chcesz ją "COL_RED"anulować"COL_WHITE", wciśnij przycisk "COL_RED"Anuluj"COL_WHITE".", nick(clientid));
		Dialog_Show(playerid, HOMESELLWAIT, DIALOG_STYLE_MSGBOX,  ""COL_RED"•» "COL_WHITE"Oczekiwanie na zaakceptowanie oferty "COL_RED"«•", strOffer, "Anuluj", "");
		SetPVarInt(clientid, "cache_homedeal_price", price);
		SetPVarInt(clientid, "cache_homedeal_homeuid", house[sel_h_id][h_id]);
		SetPVarInt(clientid, "cache_homedeal_vendoruid", gracz[playerid][UID]);
	}
	else Error(playerid, "Gracz któremu chcesz sprzedać dom, nie jest w pobliżu.");
	return 1;
}


Dialog:HOMESELLOFFER(playerid, response, listitem, inputtext[])
{
	new homeuid = GetPVarInt(playerid, "cache_homedeal_homeuid");
	new price = GetPVarInt(playerid, "cache_homedeal_price");
	new vendoruid = GetPVarInt(playerid, "cache_homedeal_vendoruid");
	if(vendoruid == 0) return Error(playerid, "Oferta nieaktualna.");
	new strOffer[512];
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(!IsPlayerConnected(p)) continue;
		if(!gracz[p][loggedin]) continue;
		if(gracz[p][UID] == vendoruid)
		{
			if(!response || !compare(inputtext, "akceptuje"))
			{
				format(strOffer, 512, ""COL_WHITE"Gracz "COL_ORANGE"%s"COL_RED" odrzucił "COL_WHITE"Twoją ofertę.", nick(playerid));
				Dialog_Show(p, CARSELLWAITEND, DIALOG_STYLE_MSGBOX,  ""COL_RED"•» "COL_WHITE"Oferta odrzucona "COL_RED"«•", strOffer, "OK", "");
				format(strOffer, 512, ""COL_RED"Odrzuciłeś "COL_WHITE"ofertę od "COL_ORANGE"%s"COL_WHITE".", nick(p));
				Dialog_Show(playerid, CARSELLWAITEND, DIALOG_STYLE_MSGBOX,  ""COL_RED"•» "COL_WHITE"Oferta odrzucona "COL_RED"«•", strOffer, "OK", "");
				return 1;
			}
			if(price > Money(playerid))
			{
				Error(playerid, "Nie posiadasz wystarczającej ilości gotówki.");
				Error(p, "Gracz, któremu złożyłeś ofertę, nie posiada wystarczającej ilości gotówki.");
				return 1;
			}
			TakeMoney(playerid, price);
			GiveMoney(p, price);

			mq_format("UPDATE `domki` SET `owneruid`='%d' WHERE `owneruid`='%d' AND `id`='%d';", gracz[playerid][UID], vendoruid, homeuid);
			mq_send("QHouseDeal");
			
			for(new h; h < MAX_HOUSES; h++)
			{
				if(house[h][h_id] == homeuid)
				{
					if(house[h][h_owneruid] == vendoruid)
					{
						house[h][h_owneruid] = gracz[playerid][UID];
						UpdateHouseLabel(h);
						break;
					}
				}
			}
			

			format(strOffer, 512, ""COL_WHITE"Gracz "COL_ORANGE"%s"COL_GREEN" przyjął "COL_WHITE"Twoją ofertę. Transakcja dobiegła końca, otrzymujesz "COL_GREEN"%d$"COL_WHITE".", nick(playerid), price);
			Dialog_Show(p, HOMESELLWAITEND, DIALOG_STYLE_MSGBOX,  ""COL_RED"•» "COL_WHITE"Dom sprzedany "COL_RED"«•", strOffer, "OK", "");
			format(strOffer, 512, ""COL_GREEN"Kupiłeś "COL_WHITE"dom od "COL_ORANGE"%s"COL_WHITE" za "COL_BLUE"%d$"COL_WHITE".", nick(p), price);
			Dialog_Show(playerid, HOMESELLWAITEND, DIALOG_STYLE_MSGBOX,  ""COL_RED"•» "COL_WHITE"Dom kupiony "COL_RED"«•", strOffer, "OK", "");
			return 1;
		}
	}
	Error(playerid, "Ups! Coś się nie udało. Spróbujcie jeszcze raz...");
	return 1;
}

Dialog:HOMESELLWAIT(playerid, response, listitem, inputtext[])
{
	new clientid = GetPVarInt(playerid, "cache_homesell_clientid");
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(p == clientid)
		{
			Dialog_Close(p);
			Dialog_Close(playerid);
			SetPVarInt(p, "cache_homedeal_vendoruid", 0);
			LeftNotifyShow(p, "error", "Sprzedajacy ~r~anulowal~w~ oferte.", LN_RED);
			LeftNotifyShow(playerid, "Sukces!", "Oferta zostala ~r~anulowana~w~.", LN_RED);
			return 1;
		}
	}
	return 1;
}

Dialog:HOMESETRENTER(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new sel_h_id = GetPVarInt(playerid, "housemenu_h_id");
	if(house[sel_h_id][h_owneruid] == gracz[playerid][UID] || house[sel_h_id][h_renteruid] == gracz[playerid][UID])
	{
		if(house[sel_h_id][h_renteruid] != 0)//jest lokatr - usun
		{
			house[sel_h_id][h_renteruid] = 0;
			mq_format("UPDATE `domki` SET `renteruid`='0' WHERE `owneruid`='%d' AND `id`='%d';", gracz[playerid][UID], house[sel_h_id][h_id]);
			mq_send("QHouseSetRent");
			//aktualizacja
			UpdateHouseLabel(sel_h_id);
			Info(playerid, "Lokator usunięty.");
		}
		else//brak lokatora - dodaj
		{
			if(house[sel_h_id][h_owneruid] != gracz[playerid][UID]) return Error(playerid, "Brak uprawnień.");
			new strPlayerList[2048];
			format(strPlayerList, 2048, "ID\tNazwa gracza");
			new bool:find = false;
			for(new p = PlayerPoolSize(); p != -1; p--)
			{
				if(!gracz[p][loggedin]) continue;
				if(p == playerid) continue;
				if(gracz[p][admin_spec_enabled] == true) continue;
				new Float:pPos[3];
				GetPlayerPos(p, pPos[0], pPos[1], pPos[2]);
				if(IsPlayerInRangeOfPoint(playerid, 4.0, pPos[0], pPos[1], pPos[2]))
				{
					format(strPlayerList, 2048, "%s\n%d\t{%06x}%s", strPlayerList, p, GetPlayerColor(playerid) >>> 8,nick(p));
					find = true;
				}
			}
			if(find) Dialog_Show(playerid, HOMEADDRENTER, DIALOG_STYLE_TABLIST_HEADERS,  ""COL_RED"•» "COL_WHITE"Lista graczy w pobliżu "COL_RED"«•", strPlayerList, "Wybierz", "Anuluj");
			else Error(playerid, "Nie znaleziono żadnego gracza w pobliżu.");
		}
	}
	return 1;
}

Dialog:HOMEADDRENTER(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new sel_h_id = GetPVarInt(playerid, "housemenu_h_id");
	if(house[sel_h_id][h_owneruid] == gracz[playerid][UID])
	{
		new clientid = strval(inputtext);
		new Float:pPos[3];
		GetPlayerPos(clientid, pPos[0], pPos[1], pPos[2]);
		if(IsPlayerInRangeOfPoint(playerid, 4.0, pPos[0], pPos[1], pPos[2]))
		{
			house[sel_h_id][h_renteruid] = gracz[clientid][UID];
			mq_format("UPDATE `domki` SET `renteruid`='%d' WHERE `owneruid`='%d' AND `id`='%d';", gracz[clientid][UID], gracz[playerid][UID], house[sel_h_id][h_id]);
			mq_send("QHouseSetRent");
			SendClientMessageEx(playerid, 0x00FF00FF, "Dodałeś %s(%d) jako lokatora.", nick(clientid), clientid);
			SendClientMessageEx(clientid, 0x00FF00FF, "Gracz %s(%d) dodał Cię jako lokatora.", nick(playerid), playerid);
			//aktualizacja
			UpdateHouseLabel(sel_h_id);
		}
		else Error(playerid, "Gracz jest za daleko.");
	}
	return 1;
}

stock ShowHomeTeleport(playerid, bool:onlycountreturn = false)
{
	if(gracz[playerid][wypadek] > 0) return 1;
	if(gracz[playerid][bw] > 0) return 1;
	new strHomeList[3000];
	new count_home;
	new zone_name[32];
	new Float:dist_home_spawn;
	new Float:pPos[3];
	GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);
	format(strHomeList, 3000, "UID\tLokalizacja\tOdległość od SPAWN'u");
	for(new h; h < MAX_HOUSES; h++)
	{
		if(house[h][h_id] == 0) continue;
		if(house[h][h_owneruid] == gracz[playerid][UID] || house[h][h_renteruid] == gracz[playerid][UID])
		{
			Get2DZone(house[h][h_extX], house[h][h_extY], zone_name, 32);
			dist_home_spawn = GetDistanceBetweenPoints(house[h][h_extX], house[h][h_extY], house[h][h_extZ], pPos[0], pPos[1], pPos[2])/CONST_KM;
			format(strHomeList, 3000, "%s\n{000000}%d\t"COL_BLUE"%s\t"COL_GREY"%0.1f km w linii prostej", strHomeList, h, zone_name, dist_home_spawn);
			count_home++;
		}
	}
	if(count_home > 0 && onlycountreturn == false) Dialog_Show(playerid, HOMETP, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_WHITE"Czy chcesz się zespawnowac w domu? "COL_RED"«•", strHomeList, "Wybierz", "Anuluj");
	return count_home;
}

Dialog:HOMETP(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new home_id = strval(inputtext);
	if(home_id < 0) return 1;
	if(home_id > MAX_HOUSES) return 1;
	FreezeLoadObject(playerid, house[home_id][h_extX], house[home_id][h_extY], house[home_id][h_extZ]);
	return 1;
}

stock UpdateHouseLabel(homeid, hOwnerN[] = "", hRenterN[] = "")
{
	//aktualizacja 3dtextu
	new strHouse[1024];
	format(strHouse, 1024, ""COL_GREEN"« "COL_BLUE"POSIADŁOŚĆ"COL_GREEN"»");
	if(house[homeid][h_owneruid] == 0)//brak właściciela
	{
		format(strHouse, 1024, "%s\n"COL_GREY"UID: "COL_DRVONLINE"%d", strHouse, house[homeid][h_id]);
		format(strHouse, 1024, "%s\n"COL_GREY"Cena: "COL_GREEN"%d$", strHouse, house[homeid][h_price]);
		if(house[homeid][h_polygonid] == 0) format(strHouse, 1024, "%s\n"COL_GREY"Samodzielna edycja parceli: "COL_RED"NIE", strHouse);
		else format(strHouse, 1024, "%s\n"COL_GREY"Samodzielna edycja parceli: "COL_GREEN"TAK", strHouse);
		DestroyDynamicMapIcon(house[homeid][h_icon]);
		DestroyDynamicPickup(house[homeid][h_pickup]);
		house[homeid][h_pickup] = CreateDynamicPickup(1273, 1, house[homeid][h_extX], house[homeid][h_extY], house[homeid][h_extZ]);
		house[homeid][h_icon] = CreateDynamicMapIcon(house[homeid][h_extX], house[homeid][h_extY], house[homeid][h_extZ], 31, 0, .streamdistance = 200.0, .style = MAPICON_LOCAL);
	}
	else
	{
		format(strHouse, 1024, "%s\n"COL_GREY"UID: "COL_DRVONLINE"%d", strHouse, house[homeid][h_id]);
		
		if(strlen(hOwnerN) > 1) format(strHouse, 1024, "%s\n"COL_GREY"Właściciel: "COL_ORANGE"%s ("COL_WHITE"%d"COL_ORANGE")", strHouse, hOwnerN, house[homeid][h_owneruid]);
		else format(strHouse, 1024, "%s\n"COL_GREY"Właściciel: "COL_ORANGE"%s ("COL_WHITE"%d"COL_ORANGE")", strHouse, GetPlayerIGName(house[homeid][h_owneruid]), house[homeid][h_owneruid]);
		if(house[homeid][h_renteruid] != 0)
		{
			if(strlen(hRenterN) > 1) format(strHouse, 1024, "%s\n"COL_GREY"Lokator: "COL_ORANGE"%s ("COL_WHITE"%d"COL_ORANGE")", strHouse, hRenterN, house[homeid][h_renteruid]);
			else format(strHouse, 1024, "%s\n"COL_GREY"Lokator: "COL_ORANGE"%s ("COL_WHITE"%d"COL_ORANGE")", strHouse, GetPlayerIGName(house[homeid][h_renteruid]), house[homeid][h_renteruid]);
		}
		format(strHouse, 1024, "%s\n"COL_GREY"Status: %s", strHouse, (house[homeid][h_open]) ? (""COL_GREEN"OTWARTE") : (""COL_RED"ZAMKNIETE"));
		
		if(house[homeid][h_polygonid] == 0) format(strHouse, 1024, "%s\n"COL_GREY"Samodzielna edycja parceli: "COL_RED"NIE", strHouse);
		else format(strHouse, 1024, "%s\n"COL_GREY"Samodzielna edycja parceli: "COL_GREEN"TAK", strHouse);

		new time_h_expire = house[homeid][h_expire]-serwer[time_timestamp];
		new dd, hh, mm, ss;
		if(time_h_expire < 0) time_h_expire = 0;
		SecToTime(time_h_expire, dd, hh, mm, ss);
		format(strHouse, 1024, "%s\n\n"COL_ORANGE"Wygasa za: "COL_BLUE"%d dni, %d godzin", strHouse,  dd, hh);
		DestroyDynamicMapIcon(house[homeid][h_icon]);
		DestroyDynamicPickup(house[homeid][h_pickup]);
		if(house[homeid][h_open]) house[homeid][h_pickup] = CreateDynamicPickup(1272, 1, house[homeid][h_extX], house[homeid][h_extY], house[homeid][h_extZ]);
		else house[homeid][h_pickup] = CreateDynamicPickup(19522, 1, house[homeid][h_extX], house[homeid][h_extY], house[homeid][h_extZ]);
		house[homeid][h_icon] = CreateDynamicMapIcon(house[homeid][h_extX], house[homeid][h_extY], house[homeid][h_extZ], 32, 0, .streamdistance = 200.0, .style = MAPICON_LOCAL);
	}
	format(strHouse, 1024, "%s\n"COL_RED"(("COL_GREEN"PPM "COL_GREY"- Interakcja"COL_RED"))", strHouse);
	UpdateDynamic3DTextLabelText(house[homeid][h_text3dext], -1, strHouse);
	//UpdateDynamic3DTextLabelText(house[homeid][h_text3dint], -1, strHouse);
	DestroyDynamic3DTextLabel(house[homeid][h_text3dint]);
	if(house[homeid][h_customint] == 1) house[homeid][h_text3dint] = CreateDynamic3DTextLabel(strHouse, -1, house[homeid][h_ex_intX], house[homeid][h_ex_intY], house[homeid][h_ex_intZ], 10.0, .worldid = HOUSE_VWOFFSET+homeid);
	else house[homeid][h_text3dint] = CreateDynamic3DTextLabel(strHouse, -1, house[homeid][h_intX], house[homeid][h_intY], house[homeid][h_intZ], 10.0, .worldid = HOUSE_VWOFFSET+homeid);
	return 1;
}
