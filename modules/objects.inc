new renderarea_RT, renderarea_POL, renderarea_SALONTRUCK;
new renderarea_LVAIRPORT;


stock Init_Objects()
{
	//GangZoneCreate(Float:minx, Float:miny, Float:maxx, Float:maxy)
	//(Float:minx, Float:miny, 0.0, Float:maxx, Float:maxy, 100.0)
	renderarea_RT = CreateDynamicCuboid(1563.5238, 1709.5649, 0.0, 1641.9778,1782.6323, 100.0);
	renderarea_POL = CreateDynamicCuboid(2119.5525,1610.2976, -100.0, 2677.1799,1975.3254, 100.0);
	renderarea_SALONTRUCK = CreateDynamicCuboid(2251.8667,1378.0985, -100.0, 2364.4675,1529.0566, 100.0);
	renderarea_LVAIRPORT = CreateDynamicPolygon(pol_lvairport_render_data);
	pol_cdesert = CreateDynamicPolygon(pol_cdesert_data);
	weatherarea_OilProvince = CreateDynamicPolygon(pol_OilProvinceWeather);
	weatherarea_PencilFactory = CreateDynamicPolygon(pol_PencilFactory);
	pol_deerfield = CreateDynamicPolygon(pol_deerfield_data);
	zone_sanandreas = CreateDynamicPolygon(pol_ZoneSanAndreas);
	LoadObjectsFromDB();
	return 1;
}
//Funkcja odpowiedzialna za tworzenie obiektów
//
stock Object(mmm, Float:koX, Float:koY, Float:koZ, Float:korX, Float:korY, Float:korZ, oworldid = 0, ointeriorid = 0)
{
	new Float:render_value = 300.0;
	new priority = 0;
	new renderareaid = -1;
	
	/*if(GetDistanceBetweenPoints(koX, koY, koZ, 3764.1506,-1781.9348,426.5565) < 130.0)//łuskanie obiektów - koszyk
	{
		printf("CreateObject(%d, %f, %f, %f, %f, %f, %f);", mmm, Float:koX, Float:koY, Float:koZ, Float:korX, Float:korY, Float:korZ);
	}*/
	//CreateDynamicObject(omodelid, oX, oY, oZ, orX, orY, orZ, -1, -1, -1, 300, 300, -1, 0);
	//dostosowywanie renderingu obiektów
/*	if(!IsPointInDynamicArea(zone_sanandreas, koX, koY, koZ))//wszystko poza san andreas
	{
		render_value = 750.0;
		priority = 0;
	}*/
	//baza RT i POLICJI - szczególy interior
	if(IsPointInDynamicArea(renderarea_POL, koX, koY, koZ))//baza policji
	{
		render_value = 300.0;
		priority = 1;
		renderareaid = renderarea_POL;
	}
	if(GetDistanceBetweenPoints(koX, koY, koZ, 2947.7786,2061.6135,26.2189) < 300.0)// zjazd na pustynna mape obok centrum handlowego w lv 
	{
		render_value = 600.0;
		priority = 1;
	}
	if(mmm == 6863 || mmm == 4028 || mmm == 4141 || mmm == 8555)//budynki
	{
		render_value = 600.0;
		priority = 1;
	}
	else if(mmm == 19538 || mmm == 19552 || mmm == 19543 || mmm == 19541 || mmm == 19545 || mmm == 19536)//grunty
	{
		render_value = 600.0;
		priority = 2;
		renderareaid = -1;
	}
	else if(mmm == 16773)//ogrodzenia
	{
		render_value = 600.0;
		priority = 1;
	}
	else if(mmm == 691 || mmm == 617 || mmm ==709)//drzewa
	{
		render_value = 600.0;
		priority = 1;
	}
	else if(mmm == 19481 ||  mmm == 19479)//napisy
	{
		render_value = 600.0;
		priority = 1;
		renderareaid = -1;
	}
	else if(mmm == 19447 || mmm == 19370)//logo szpitalne
	{
		if(GetDistanceBetweenPoints(koX, koY, koZ, 1587.0638,1781.6251,46.0340) < 50.0)
		{
			render_value = 600.0;
			priority = 1;
		}
	}
	else if(mmm == 1361 || mmm == 1723 || mmm == 2164 || mmm == 1360 || mmm == 2010 || mmm == 19899 || mmm == 2310 || mmm == 2637 || mmm == 2200 || mmm == 2044 || mmm == 19142 || mmm == 14782 || mmm == 948 || mmm == 2610)//meble
	{
		render_value = 50.0;
		priority = 0;
	}
	else if(mmm == 2161 || mmm == 2167 || mmm == 1714 || mmm == 2198 || mmm == 1715 || mmm == 2523 || mmm == 2611)//meble
	{
		render_value = 50.0;
		priority = 0;
	}
	else if(mmm == 19890 || mmm == 9623 || mmm == 18766 || mmm == 7313 || mmm == 19868 || mmm == 1290 || mmm == 996)//przejazd graniczny sg lv-tierra rabrada
	{
		render_value = 400.0;
		priority = 1;
	}
	else if(mmm == 19435 || mmm == 19791 || mmm == 19790 || mmm == 18980 || mmm == 19377 || mmm == 18981 || mmm == 19362 || mmm == 18762 || mmm == 3660  || mmm == 19454 || mmm == 3851 || mmm == 19391 || mmm == 19447  || mmm == 19370)//sciany baz frakfcji
	{
		if(GetDistanceBetweenPoints(koX, koY, koZ, 1004.2470,2467.5310,17.2407) < 100.0)//baza SG
		{
			render_value = 600.0;
			priority = 2;
		}
		if(GetDistanceBetweenPoints(koX, koY, koZ, 1624.7040,1763.1438,10.8184) < 50.0)//RT hangar fix
		{
			render_value = 300.0;
			priority = 1;
		}
		renderareaid = -1;
	}
	else if(mmm == 1491 || mmm == 1523)//drzwi
	{
		render_value = 150.0;
		priority = 1;
	}
	else if(mmm == 5422)//bramy garażowe
	{
		render_value = 400.0;
		priority = 1;
	}
	else if(mmm == 997)//barierki
	{
		render_value = 400.0;
		priority = 1;
	}
	else if(mmm == 19913)//ogrodzenie LV
	{
		render_value = 600.0;
		priority = 0;
	}
	else if(mmm == 9694 || mmm == 9837 || mmm == 9696 || mmm == 9693 || mmm == 9689 || mmm == 9685 || mmm == 9690 || mmm == 9838)//most golden gate
	{
		render_value = 2000.0;
		priority = 2;
	} 
	else if(mmm == 16133 || mmm == 11694 || mmm == 11695 || mmm == 18228 || mmm == 19841 || mmm == 19842)//duze obiekty wyspy
	{
		render_value = 600.0;
		priority = 2;
	}
	//
	if(mmm == 7621 || mmm == 3707 || mmm == 3755 || mmm == 3689 || mmm == 5170 || mmm == 19913  || mmm == 3630)//doki lot LV
	{
		if(GetDistanceBetweenPoints(koX, koY, koZ, 1623.9319,1622.4674,14.0759) < 270.0)
		{
			render_value = 400.0;
			priority = 1;
		}
	}
	else if(mmm == 8884 || mmm == 3571 || mmm == 19480 || mmm == 7836 || mmm == 3620 || mmm == 8885)
	{
		if(IsPointInDynamicArea(renderarea_LVAIRPORT, koX, koY, koZ))
		{
			render_value = 400.0;
			priority = 1;
		}
	}

	//else if(IsPointInDynamicArea(pol_lvairport, koX, koY, koZ)) renderareaid = renderarea_LVAIRPORT;
	//AREA RENDER
	new bool:interior_details = false;
	if(mmm == 966 || mmm == 929 || mmm == 1348 || mmm == 2063 || mmm == 18608 || mmm == 1721 || mmm == 2256 || mmm == 948 || mmm == 1811 || mmm == 19860 || mmm == 9131 || mmm == 1671 || mmm == 19808 || mmm == 2266) interior_details = true;
	if(mmm == 2263 || mmm == 2173 || mmm == 2270 || mmm == 2637 || mmm == 2264 || mmm == 2267 || mmm == 19610 || mmm == 2230 || mmm == 2528 || mmm == 2515 || mmm == 11729 || mmm == 11745 || mmm == 1726) interior_details = true;
	if(mmm == 1432 || mmm == 2631 || mmm == 2163 || mmm == 2007 || mmm == 2161 || mmm == 1714 || mmm == 1823 || mmm == 968 || mmm == 2010 || mmm == 1897 || mmm == 2855 || mmm == 2253 || mmm == 2611 || mmm == 1808) interior_details = true;
	if(mmm == 1216 || mmm == 19175 || mmm == 19999 || mmm == 2165 || mmm == 2606 || mmm == 2067 || mmm == 2608 || mmm == 2202 || mmm == 2011 || mmm == 2001 || mmm == 956 || mmm == 955 || mmm == 1209 || mmm == 1494) interior_details = true;
	if(mmm == 1722 || mmm == 2066 || mmm == 2612 || mmm == 14532 || mmm == 19893 || mmm == 2854 || mmm == 19835 || mmm == 2200 || mmm == 2164 || mmm == 11749 || mmm == 18636 || mmm == 2166 || mmm == 2356) interior_details = true;
	if(mmm == 19142 || mmm == 19919 || mmm == 1746 || mmm == 2035 || mmm == 2036 || mmm == 2358 || mmm == 2140 || mmm == 19996 || mmm == 1800 || mmm == 2310 || mmm == 2309  || mmm == 2184 || mmm == 1727 || mmm == 2162) interior_details = true;
	//if(mmm == )
	if(interior_details == true)
	{
		render_value = 60.0;
		priority = 0;
		if(IsPointInDynamicArea(renderarea_RT, koX, koY, koZ)) renderareaid = renderarea_RT;
		if(IsPointInDynamicArea(renderarea_POL, koX, koY, koZ))
		{
			render_value = 60.0;
			priority = 1;
		}
	}

	if(IsPointInDynamicArea(pol_cdesert, koX, koY, koZ))//customowa pustynia
	{
		if(mmm == 19545 || mmm == 19551 || mmm == 16258 || mmm == 16253 || mmm == 8395)//customowa pustynia poza sa, obiekty pustynne
		{
			render_value = 900.0;
			priority = 0;
			renderareaid = pol_cdesert;
		}
	}

	if(IsPointInDynamicArea(renderarea_SALONTRUCK, koX, koY, koZ))//salon truck
	{
		if(mmm == 19791)//platformy dla trucków
		{
			render_value = 500.0;
			priority = 1;
		}
	}
	if(IsPointInDynamicArea(pol_deerfield, koX, koY, koZ))//deerfield
	{
		render_value = 700.0;
		priority = 1;
	}
	//********************************************************************************
	if(GetDistanceBetweenPoints(koX, koY, koZ, 2619.8684,1686.2407,1718.7402) < 700.0)//interiory domków zawsze na -1
	{
		oworldid = -1;
		ointeriorid = -1;
	}
	new Float:drawdistance;
	if(render_value > 300.0) drawdistance = render_value-100.0;
	else drawdistance = render_value;
	//CallRemoteFunction("CA_CreateObj", "dffffffd", mmm, koX, koY, koZ, korX, korY, korZ, oworldid);//sync_col_ma.pwn
	return CreateDynamicObject(mmm, koX, koY, koZ, korX, korY, korZ, oworldid, ointeriorid, -1, render_value, drawdistance, renderareaid, priority);
	//return CreateDynamicObject(mmm, koX, koY, koZ, korX, korY, korZ, oworldid, ointeriorid, -1, render_value, render_value, renderareaid, priority);
}
//*********************************************************************************************************SYSTEM DYNAMICZNYCH OBIEKTÓW
//CALLBACK ODPOWIEDZIALNY ZA EDYCJE
public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new uid = PlayerEditObject[playerid];
	gracz[playerid][MapperLvl] = GetMapperPremGroup(playerid);
	//Aktualizowanie zmiennych
	if(response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL)
	{
		// Przypisywanie pozycji obiektu
		if(PlayerEditObject[playerid])
		{
			if(gracz[playerid][MapperLvl] == 1)
			{
				new objtype;
				new bool:isgood = false;
				if(ObjectInfo[uid][oGrupa] >= OFFSET_HOUSEOBJ) objtype = 1;
				else if(ObjectInfo[uid][oGrupa] >= OFFSET_HOUSEINTOBJ) objtype = 2;
				else if(ObjectInfo[uid][oGrupa] >= OFFSET_COMPANYOBJ) objtype = 3;
				if(objtype != 0)
				{
					if(objtype == 1)//domki
					{
						for(new h; h < MAX_HOUSES; h++)
						{
							if(house[h][h_id] == 0) continue;
							if(house[h][h_polygonid] == 0) continue;
							if(house[h][h_owneruid] == gracz[playerid][UID])
							{
								if(IsPointInDynamicArea(house[h][h_polygonid], x, y, z))
								{
									isgood = true;
									break;
								}
							}
						}
					}
					else if(objtype == 2)//domki interior
					{
						Info(playerid, "WIP");
					}
					else if(objtype == 3)//firmy
					{
						for(new cid; cid < MAX_COMPANY; cid++)
						{
							if(company[cid][cny_polygonid] == 0) continue;
							if(company[cid][cny_owneruid] == gracz[playerid][UID])
							{
								if(IsPointInDynamicArea(company[cid][cny_polygonid], x, y, z))
								{
									isgood = true;
									break;
								}
							}
						}
					}
				}
				else return Error(playerid, "Brak uprawnień do edycji tego obiektu.");
				if(isgood == false)
				{
					DeleteObject(uid);
					Error(playerid, "Obiekt znajduje się poza wyznaczonym terenem domu/firmy.");
					PlayerEditObject[playerid] = 0;
				}
				else
				{
					// Przenieś obiekt na pozycję
					SetDynamicObjectPos(objectid, x, y, z);
					SetDynamicObjectRot(objectid, rx, ry, rz);
					// Aktualizowanie zmiennych
					ObjectInfo[uid][oX] = x;
					ObjectInfo[uid][oY] = y;
					ObjectInfo[uid][oZ] = z;
					ObjectInfo[uid][oRX] = rx;
					ObjectInfo[uid][oRY] = ry;
					ObjectInfo[uid][oRZ] = rz;
					// Zapisywanie obiektu
					SaveObject(uid);
					// Zakończ edycję obiektu
					PlayerEditObject[playerid] = 0;
					// Wyślij informację dla gracza
					LeftNotifyShow(playerid, "Sukces!", "Obiekt zostal ~g~zapisany~w~.", LN_GREEN);
				}
			}
			else if(gracz[playerid][MapperLvl] == 2 && ObjectInfo[uid][oOwner] == GetPlayerUID(playerid))
			{
				// Przenieś obiekt na pozycję
				SetDynamicObjectPos(objectid, x, y, z);
				SetDynamicObjectRot(objectid, rx, ry, rz);
				// Aktualizowanie zmiennych
				ObjectInfo[uid][oX] = x;
				ObjectInfo[uid][oY] = y;
				ObjectInfo[uid][oZ] = z;
				ObjectInfo[uid][oRX] = rx;
				ObjectInfo[uid][oRY] = ry;
				ObjectInfo[uid][oRZ] = rz;
				// Zapisywanie obiektu
				SaveObject(uid);
				// Zakończ edycję obiektu
				PlayerEditObject[playerid] = 0;
				// Wyślij informację dla gracza
				LeftNotifyShow(playerid, "Sukces!", "Obiekt zostal ~g~zapisany~w~.", LN_GREEN);
			}
			else if(gracz[playerid][MapperLvl] == 3)
			{
				// Przenieś obiekt na pozycję
				SetDynamicObjectPos(objectid, x, y, z);
				SetDynamicObjectRot(objectid, rx, ry, rz);
				// Aktualizowanie zmiennych
				ObjectInfo[uid][oX] = x;
				ObjectInfo[uid][oY] = y;
				ObjectInfo[uid][oZ] = z;
				ObjectInfo[uid][oRX] = rx;
				ObjectInfo[uid][oRY] = ry;
				ObjectInfo[uid][oRZ] = rz;
				// Zapisywanie obiektu
				SaveObject(uid);
				// Zakończ edycję obiektu
				PlayerEditObject[playerid] = 0;
				// Wyślij informację dla gracza
				LeftNotifyShow(playerid, "Sukces!", "Obiekt zostal ~g~zapisany~w~.", LN_GREEN);
			}
			else
			{
				DeleteObject(uid);
				Error(playerid, "Brak uprawnień.");
				PlayerEditObject[playerid] = 0;
			}
		}
	}
	return 1;
}
public OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)
{
	new searchid = GetObjectIndex(objectid);
	gracz[playerid][MapperLvl] = GetMapperPremGroup(playerid);
	if(!searchid) return Error(playerid, "Tego obiektu nie da się edytować.");
	/*if(gracz[playerid][MapperLvl] == 1 && IsPlayerInBaseArea(playerid) && IsPointInBaseArea(playerid, x, y, z) && ObjectInfo[searchid][oGrupa] == gracz[playerid][OrgID])
	{
		PlayerEditObject[playerid] = searchid;
		EditDynamicObject(playerid, objectid);
		SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Autor obiektu: "COL_BLUE"%s"COL_EASY"(UID: %d) | Grupa UID: %d"COL_RED"))", GetPlayerIGName(ObjectInfo[searchid][oOwner]), ObjectInfo[searchid][oOwner], ObjectInfo[searchid][oGrupa]);
	}
	else */
	if(gracz[playerid][MapperLvl] == 1)
	{
		new objtype;
		new bool:isgood = false;
		if(ObjectInfo[searchid][oGrupa] >= OFFSET_HOUSEOBJ) objtype = 1;
		else if(ObjectInfo[searchid][oGrupa] >= OFFSET_HOUSEINTOBJ) objtype = 2;
		else if(ObjectInfo[searchid][oGrupa] >= OFFSET_COMPANYOBJ) objtype = 3;
		if(objtype != 0)
		{
			if(objtype == 1)//domki
			{
				for(new h; h < MAX_HOUSES; h++)
				{
					if(house[h][h_id] == 0) continue;
					if(house[h][h_polygonid] == 0) continue;
					if(house[h][h_owneruid] == gracz[playerid][UID])
					{
						if(IsPointInDynamicArea(house[h][h_polygonid], x, y, z))
						{
							isgood = true;
							break;
						}
					}
				}
			}
			else if(objtype == 2)//domki interior
			{
				Info(playerid, "WIP");
			}
			else if(objtype == 3)//firmy
			{
				for(new cid; cid < MAX_COMPANY; cid++)
				{
					if(company[cid][cny_polygonid] == 0) continue;
					if(company[cid][cny_owneruid] == gracz[playerid][UID])
					{
						if(IsPointInDynamicArea(company[cid][cny_polygonid], x, y, z))
						{
							isgood = true;
							break;
						}
					}
				}
			}
		}
		else return Error(playerid, "Brak uprawnień do edycji tego obiektu.");
		if(isgood == false)
		{
			PlayerEditObject[playerid] = 0;
			Error(playerid, "Brak uprawnień.");
		}
		else
		{
			PlayerEditObject[playerid] = searchid;
			EditDynamicObject(playerid, objectid);
			SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Autor obiektu: "COL_BLUE"%s"COL_EASY"(UID: %d) | UID obiektu: %d"COL_RED"))", GetPlayerIGName(ObjectInfo[searchid][oOwner]), ObjectInfo[searchid][oOwner], searchid);
		}
	}
	else if(gracz[playerid][MapperLvl] == 2 && ObjectInfo[searchid][oOwner] == GetPlayerUID(playerid))
	{
		PlayerEditObject[playerid] = searchid;
		EditDynamicObject(playerid, objectid);
		SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Autor obiektu: "COL_BLUE"%s"COL_EASY"(UID: %d) | UID obiektu: %d"COL_RED"))", GetPlayerIGName(ObjectInfo[searchid][oOwner]), ObjectInfo[searchid][oOwner], searchid);
	}
	else if(gracz[playerid][MapperLvl] == 3)
	{
		PlayerEditObject[playerid] = searchid;
		EditDynamicObject(playerid, objectid);
		SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Autor obiektu: "COL_BLUE"%s"COL_EASY"(UID: %d) | UID obiektu: %d"COL_RED"))", GetPlayerIGName(ObjectInfo[searchid][oOwner]), ObjectInfo[searchid][oOwner], searchid);
	}
	else
	{
		PlayerEditObject[playerid] = 0;
		Error(playerid, "Brak uprawnień.");
	}
	return 1;
}
//ładowanie obiektów z bazy
stock LoadObjectsFromDB()
{
	#if defined LIMITOBJ
	mysql_tquery(g_SQL, "SELECT * FROM `Obiekty` LIMIT 0,2000;", "LoadObjectDataReceived","");
	#else
	mysql_tquery(g_SQL, "SELECT * FROM `Obiekty`;", "LoadObjectDataReceived","");
	#endif
	return 1;
}
forward LoadObjectDataReceived();
public LoadObjectDataReceived()
{
	if(cache_get_row_count_ex() >= MAX_OBJECTS) printf("[ERROR][OBJECTS] Limit obiektow w gamemode jest zbyt maly.");
	new rows, fields;
	cache_get_row_count(rows), cache_get_field_count(fields);
	new i;
	//new File:handle = fopen("obiekty.txt", io_write);
	//new backup_str[512];
	if(rows)
	{
		while(i<cache_get_row_count_ex())
		{
			new id;
			cache_get_value_name_int(i, "id", id);
			ObjectInfo[id][oUID] = id;
			cache_get_value_name_int(i, "model", 			ObjectInfo[id][oModel]);
			cache_get_value_name_int(i, "idgrupa", 			ObjectInfo[id][oGrupa]);
			cache_get_value_name_int(i, "uid", 			ObjectInfo[id][oOwner]);
			cache_get_value_name_int(i, "World", 			ObjectInfo[id][oVW]);
			cache_get_value_name_int(i, "InteriorEx", 			ObjectInfo[id][oInt]);
			cache_get_value_name_float(i, "x", 			ObjectInfo[id][oX]);
			cache_get_value_name_float(i, "y", 			ObjectInfo[id][oY]);
			cache_get_value_name_float(i, "z", 			ObjectInfo[id][oZ]);
			cache_get_value_name_float(i, "rx", 			ObjectInfo[id][oRX]);
			cache_get_value_name_float(i, "ry", 			ObjectInfo[id][oRY]);
			cache_get_value_name_float(i, "rz", 			ObjectInfo[id][oRZ]);
			cache_get_value_name_float(i, "gx", 			ObjectInfo[id][goX]);
			cache_get_value_name_float(i, "gy", 			ObjectInfo[id][goY]);
			cache_get_value_name_float(i, "gz", 			ObjectInfo[id][goZ]);
			cache_get_value_name_float(i, "grx", 			ObjectInfo[id][goRX]);
			cache_get_value_name_float(i, "gry", 			ObjectInfo[id][goRY]);
			cache_get_value_name_float(i, "grz", 			ObjectInfo[id][goRZ]);
			cache_get_value_name_int(i, "mgate", 			ObjectInfo[id][oMgate]);
			cache_get_value_name_int(i, "mgOwnerType", 			ObjectInfo[id][mgOwnerType]);
			cache_get_value_name_int(i, "mgOwner", 			ObjectInfo[id][mgOwner]);
			cache_get_value_name_float(i, "gspeed", 			ObjectInfo[id][gSpeed]);
			cache_get_value_name_float(i, "grange", 			ObjectInfo[id][gRange]);
			cache_get_value_name_int(i, "mmat", 			ObjectInfo[id][oMMAT]);
			
			ObjectInfo[id][oObject] = Object(ObjectInfo[id][oModel], ObjectInfo[id][oX], ObjectInfo[id][oY], ObjectInfo[id][oZ], ObjectInfo[id][oRX], ObjectInfo[id][oRY], ObjectInfo[id][oRZ], ObjectInfo[id][oVW], ObjectInfo[id][oInt]);
			/*format(backup_str, 512, "%d|%d|%d|%d|%d|%d|%f|%f|%f|%f|%f|%f|%d\r\n", ObjectInfo[id][oUID], ObjectInfo[id][oModel], ObjectInfo[id][oGrupa], ObjectInfo[id][oOwner], ObjectInfo[id][oVW], ObjectInfo[id][oInt], ObjectInfo[id][oX], ObjectInfo[id][oY], ObjectInfo[id][oZ], ObjectInfo[id][oRX], ObjectInfo[id][oRY], ObjectInfo[id][oRZ], ObjectInfo[id][oMMAT]);
			fwrite(handle, backup_str);*/
			i++;
		}
	}
	//fclose(handle);
	Process_ObjectGateScan();
	printf("[LOAD] Wczytano %d obiektów z bazy danych.", i);
	#if !defined LIMITOBJ
	LoadMaterialText();
	#endif
	return 1;
}
//Ładowanie przerabiania obiektów na napisy...
stock LoadMaterialText()
{
	mysql_tquery(g_SQL, "SELECT * FROM `Obiekty_text`","LoadMaterialTextDataReceived","");
	return 1;
}
forward LoadMaterialTextDataReceived();
public LoadMaterialTextDataReceived()
{
	new rows, fields;
	cache_get_row_count(rows), cache_get_field_count(fields);
	new i;
	if(rows)
	{
		while(i<cache_get_row_count_ex())
		{
			new object, index, matsize, fontsize, bold, fontcolor, backcolor, align, fontface[32], text[64];
			cache_get_value_name_int(i, "object", 			object);
			cache_get_value_name_int(i, "index", 			index);
			cache_get_value_name_int(i, "matsize", 			matsize);
			cache_get_value_name_int(i, "fontsize", 			fontsize);
			cache_get_value_name_int(i, "bold", 			bold);
			cache_get_value_name_int(i, "color_font", 			fontcolor);
			cache_get_value_name_int(i, "color_back", 			backcolor);
			cache_get_value_name_int(i, "align", 			align);
			cache_get_value_name(i, "fontface", fontface);
			cache_get_value_name(i, "text", text);
			//printf("UPDATE `Obiekty_text` SET `text`='%s' WHERE `id`='%d';", text, cache_get_value_name_int(i, "id", g_SQL));
			if(ObjectInfo[object][oUID] && ObjectInfo[object][oMMAT] == 1)
			{
				new color_font = ShiftRGBAToABGR(fontcolor);
				new color_back = ShiftRGBAToABGR(backcolor);
				SetDynamicObjectMaterialText(ObjectInfo[object][oObject], index, text, matsize, fontface, fontsize, bold, color_font, color_back, align);
			}
			i++;
		}
	}
	printf("[LOAD] Wczytano %d [text]tekstur z bazy danych.", i);
	LoadTexture();
	return 1;
}
//Ładowanie tekstur z bazy danych
stock LoadTexture()
{
	mysql_tquery(g_SQL, "SELECT * FROM `Obiekty_textury`","LoadTextureDataReceived","");
	return 1;
}
forward LoadTextureDataReceived();
public LoadTextureDataReceived()
{
	new rows, fields;
	cache_get_row_count(rows), cache_get_field_count(fields);
	new i;
	if(rows)
	{
		while(i<cache_get_row_count_ex())
		{
			new object, index, materialcolor, modelid, txdname[32], texturename[32];
			cache_get_value_name_int(i, "object", 			object);
			cache_get_value_name_int(i, "index", 			index);
			cache_get_value_name_int(i, "materialcolor", 			materialcolor);
			cache_get_value_name_int(i, "modelid", 			modelid);
			cache_get_value_name(i, "txdname", txdname);
			cache_get_value_name(i, "texturename", texturename);
			if(ObjectInfo[object][oUID] && ObjectInfo[object][oMMAT] == 1)
			{
				SetDynamicObjectMaterial(ObjectInfo[object][oObject], index, modelid, txdname, texturename, ShiftRGBAToABGR(materialcolor));
			}
			i++;
		}
	}
	printf("[LOAD] Wczytano %d [material]tekstur z bazy danych.", i);
	printf("[OBJECTS]Wszystkich obiektow na serwerze jest: %d sztuk!", CountDynamicObjects());
	MarkBorderCrossing3DText();
	return 1;
}
stock EscapeMMAT(name[])
{
	for(new i = 0; name[i] != 0; i++)
	{
		if(name[i] == '|') name[i] = '\n';
	}
}
stock AddObject(model, idgrupa, uid, World, InteriorEx, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new Cache:result;
	mq_format("SELECT id FROM (SELECT 1 AS id) q1 WHERE NOT EXISTS (SELECT 1 FROM  Obiekty WHERE  id = 1) UNION ALL SELECT * FROM (SELECT  id + 1 FROM Obiekty t WHERE  NOT EXISTS (SELECT  1 FROM Obiekty ti WHERE ti.id = t.id +1) ORDER BY id LIMIT 1) q2 ORDER BY id LIMIT 1;");
	result = mysql_query(g_SQL, mQuery);
	new id;
	cache_get_value_name_int(0, "id", id);
	cache_delete(result);
	mq_format("INSERT INTO `Obiekty` (`id`, `model`, `idgrupa`, `uid`, `World`, `InteriorEx`, `x`, `y`, `z`, `rx`, `ry`, `rz`) VALUES ('%d', '%d', '%d', '%d', '%d', '%d', '%0.5f', '%0.5f', '%0.5f', '%0.5f', '%0.5f', '%0.5f');", id, model, idgrupa, uid, World, InteriorEx, x, y, z, rx, ry, rz);
	mysql_query(g_SQL, mQuery, false);
	ObjectInfo[id][oUID] = id;
	ObjectInfo[id][oModel] = model;
	ObjectInfo[id][oX] = x;
	ObjectInfo[id][oY] = y;
	ObjectInfo[id][oZ] = z;
	ObjectInfo[id][oRX] = rx;
	ObjectInfo[id][oRY] = ry;
	ObjectInfo[id][oRZ] = rz;
	ObjectInfo[id][oInt] = InteriorEx;
	ObjectInfo[id][oVW] = World;
	ObjectInfo[id][oGrupa] = idgrupa;
	ObjectInfo[id][oOwner] = uid;
	//ObjectInfo[id][oObject] = CreateDynamicObject(ObjectInfo[id][oModel], ObjectInfo[id][oX], ObjectInfo[id][oY], ObjectInfo[id][oZ], ObjectInfo[id][oRX], ObjectInfo[id][oRY], ObjectInfo[id][oRZ], ObjectInfo[id][oVW], ObjectInfo[id][oInt], -1, 600.0,600.0);
	ObjectInfo[id][oObject] = Object(ObjectInfo[id][oModel], ObjectInfo[id][oX], ObjectInfo[id][oY], ObjectInfo[id][oZ], ObjectInfo[id][oRX], ObjectInfo[id][oRY], ObjectInfo[id][oRZ], ObjectInfo[id][oVW], ObjectInfo[id][oInt]);
	return id;
}
stock SaveObject(id)
{
	mq_format("UPDATE `Obiekty` SET `model` = '%d', `x` = '%f', `y` = '%f', `z` = '%f', `rx` = '%f', `ry` = '%f', `rz` = '%f', `InteriorEx` = '%d', `World` = '%d', `idgrupa` = '%d', `uid` = '%d', `mmat` = '%d' WHERE `id` = '%d'",
	ObjectInfo[id][oModel],
	ObjectInfo[id][oX],
	ObjectInfo[id][oY],
	ObjectInfo[id][oZ],
	ObjectInfo[id][oRX],
	ObjectInfo[id][oRY],
	ObjectInfo[id][oRZ],
	ObjectInfo[id][oInt],
	ObjectInfo[id][oVW],
	ObjectInfo[id][oGrupa],
	ObjectInfo[id][oOwner],
	ObjectInfo[id][oMMAT],
	id);
	mq_send("QSaveObject");
	return 1;
}
stock DeleteObject(id)
{
	mq_format("DELETE FROM `Obiekty` WHERE `id` = '%d'", id);
	mq_send("QDeleteObject");
	mq_format("DELETE FROM `Obiekty_text` WHERE `object` = '%d'", id);
	mq_send("QDeleteObject");
	mq_format("DELETE FROM `Obiekty_textury` WHERE `object` = '%d'", id);
	mq_send("QDeleteObject");
	DestroyDynamicObject(ObjectInfo[id][oObject]);
	for(new oinfo:r; r < oinfo; r++)
	{
		ObjectInfo[id][r] = 0;
	}
	return 1;
}
stock GetObjectID(uid)
{
	new list = 0;
	//ForeachEx(i, MAX_OBJECTS)
	for(new i; i < MAX_OBJECTS; i++)
	{
		if(ObjectInfo[i][oUID] == uid)
		{
			list = i;
			break;
		}
	}
	return list;
}
stock IsOwnerObject(playerid, objectid)
{
	new wynik;
	ForeachEx(i, MAX_OBJECTS)
	{
		if(ObjectInfo[i][oObject]) == objectid)
		{
			//wynik = 1;//debug value
			if(gracz[playerid][UID] == ObjectInfo[i][oOwner]) wynik = 1;
			//if(PlayerGang[playerid] == ObjectInfo[i][oGrupa]) wynik = 2;
			break;
		}
	}
	return wynik;
}
stock GetObjectIndex( objectid )
{
	new uid = 0;
	//ForeachEx(i, MAX_OBJECTS)
	for(new i; i < MAX_OBJECTS; i++)
	{
		if(ObjectInfo[i][oObject] == objectid)
		{
			uid = i;
			break;
		}
	}
	return uid;
}
stock CountObjectsFromDB()
{
	new Cache:result = mysql_query(g_SQL, "SELECT * FROM `Obiekty`");
	new count=cache_num_rows();
	cache_delete(result);
	return count;
}
stock CountObjectsCreatedByPlayer(playerid)
{
	new wynik,query[256];
	format(query,256,"SELECT `uid` FROM `Obiekty` WHERE `uid`='%d';",GetPlayerUID(playerid));
	new Cache:result = mysql_query(g_SQL,query);
	wynik=cache_num_rows();
	cache_delete(result);
	return wynik;
}
stock GetObjectCreatedPerG(type, idg)
{
	new wynik,query[256];
	if(type == 1)//domki
	{
		format(query,256,"SELECT `idgrupa` FROM `Obiekty` WHERE `idgrupa`='%d';", OFFSET_HOUSEOBJ+idg);
		new Cache:result = mysql_query(g_SQL,query);
		wynik=cache_num_rows();
		cache_delete(result);
	}
	else if(type == 2)
	{
		//wip
	}
	else if(type == 3)//firmy
	{
		format(query,256,"SELECT `idgrupa` FROM `Obiekty` WHERE `idgrupa`='%d';", OFFSET_COMPANYOBJ+idg);
		new Cache:result = mysql_query(g_SQL,query);
		wynik=cache_num_rows();
		cache_delete(result);
	}
	return wynik;
}

stock GetMapperPremGroup(playerid)
{
	new wynik;
	if(GetPVarInt(playerid, "cache_mapperlvl") != 0) gracz[playerid][MapperLvl] = GetPVarInt(playerid, "cache_mapperlvl");//wczytaj cache jeśli istnieje
	if(gracz[playerid][MapperLvl] >= 2) SetPVarInt(playerid, "cache_mapperlvl", gracz[playerid][MapperLvl]);
	wynik = gracz[playerid][MapperLvl];
	new bool:in_my_field = false;

	//domek?
	for(new h; h < MAX_HOUSES; h++)
	{
		if(house[h][h_id] == 0) continue;
		if(house[h][h_polygonid] == 0) continue;
		if(house[h][h_owneruid] == gracz[playerid][UID])
		{
			if(IsPlayerInDynamicArea(playerid, house[h][h_polygonid]))
			{
				in_my_field = true;
				break;
			}
		}
	}
	//firma?
	for(new cid; cid < MAX_COMPANY; cid++)
	{
		if(company[cid][cny_polygonid] == 0) continue;
		if(company[cid][cny_owneruid] == gracz[playerid][UID])
		{
			if(IsPlayerInDynamicArea(playerid, company[cid][cny_polygonid]))
			{
				in_my_field = true;
				break;
			}
		}
	}
	if(in_my_field)
	{
		gracz[playerid][MapperLvl] = 1;
		wynik = 1;
	}
	else if(gracz[playerid][MapperLvl] == 1)
	{
		gracz[playerid][MapperLvl] = 0;
		wynik = 0;
	}
	return wynik;
}

stock GetMapperAreaType(playerid, &cidhid)
{
	//domek?
	for(new h; h < MAX_HOUSES; h++)
	{
		if(house[h][h_id] == 0) continue;
		if(house[h][h_polygonid] == 0) continue;
		if(house[h][h_owneruid] == gracz[playerid][UID])
		{
			if(IsPlayerInDynamicArea(playerid, house[h][h_polygonid])) 
			{
				cidhid = house[h][h_id];
				return 1;
			}
		}
	}
	//domek interior?
	//WIP = return 2
	//firma?
	for(new cid; cid < MAX_COMPANY; cid++)
	{
		if(company[cid][cny_polygonid] == 0) continue;
		if(company[cid][cny_owneruid] == gracz[playerid][UID])
		{
			if(IsPlayerInDynamicArea(playerid, company[cid][cny_polygonid]))
			{
				cidhid = cid;
				return 3;
			}
		}
	}
	return 0;
}

CMD:gmpg(playerid, params[])
{
	new strInfo[64];
	format(strInfo, 64, "MapperLvl: %d", GetMapperPremGroup(playerid));
	Info(playerid, strInfo);
	return 1;
}
//********************************************************************************************************************************KOMENDY DYNAMICZNEGO SYSTEMU OBIEKTÓW
new mmc_objects[] =
{
	973, 1226, 1237, 791, 1294, 19121, 691, 996, 997, 1232, 19865, 3463, 3660, 1290, 19991, 19971, 19992, 19955, 19957, 19967, 19980, 19984, 19970, 11699, 19986, 19979, 19962, 19968, 19975, 19981, 19948, 19949, 19950, 19951, 19959, 19952, 19989, 19974, 3379, 1234, 19953, 11700, 19954, 19977, 19976, 19982, 19956, 19973, 19972, 19983, 19985, 19987, 19966, 19988, 19965, 19990, 19964, 19963, 19961, 19960, 19958, 19978, 16023, 3463, 1290, 1226, 1294, 1231, 1350, 1351, 1315, 3855, 12883, 1232, 19121, 19127, 19126, 19125, 19123, 3666, 19124, 1215, 1368, 1280, 19815, 1256, 7313, 8406, 11435, 8328, 7606, 2736, 1444, 16002, 8330, 19327, 19329, 7415, 5811, 8618, 8327, 8326, 8322, 7912, 1260, 1259, 17323, 17539, 7246, 10837, 3754, 16436, 4515, 4514, 981, 4526, 16438, 1237, 3660, 869, 738, 1597, 1427, 1425, 1422, 3091, 997, 994, 996, 1423, 1424, 1228, 3578, 19425, 968, 976, 19912, 971, 2933, 19870, 2990, 988, 975, 2909, 989, 3567, 3569
};

CMD:mmc(playerid, params[])
{
	if(gracz[playerid][MapperLvl] < 2) return Error(playerid, "Brak uprawnień.");
	ShowModelSelectionMenuEx(playerid, mmc_objects, sizeof(mmc_objects), "Podreczne obiekty", MSEL_MOBJECTS, _, _, 180.0);
	return 1;
}

CMD:mc(playerid, params[])
{
	gracz[playerid][MapperLvl] = GetMapperPremGroup(playerid);
	if(!gracz[playerid][MapperLvl]) return Error(playerid, "Brak uprawnień.");
	if(PlayerEditObject[playerid]) return Error(playerid, "W tej chwili edytujesz inny obiekt.");
	if(CountObjectsFromDB() >= MAX_OBJECTS) return Error(playerid, "Limit obiektów na serwerze przekroczony!");
	new model;
	if(sscanf(params, "d", model)) return SendClientMessage(playerid, -1, "UŻYJ: /mc [idobiektu]");
	if(model < 616 && model != 338) return Error(playerid, "Błędny model.");
	//if(!BaseObjectIsAllowed(model) && gracz[playerid][MapperLvl] == 1) return Error(playerid, "Dostępne obiekty grup znajdziesz pod "COL_BLUE"/gmc");
	new vw = GetPlayerVirtualWorld(playerid);
	new interior = GetPlayerInterior(playerid);
	new Float:Pos[3]; // Definiowanie pozycji
	// Przypisywanie pozycji
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	if(gracz[playerid][MapperLvl] >= 2)
	{
		//if(CountObjectsCreatedByPlayer(playerid) >= 500) return SendClientMessage(playerid, -1, "Przekroczona ilość stworzonych obiektów(300) dla Ciebie!");
		// Tworzenie obiektu
		new uid = AddObject(model, 0 - gracz[playerid][MapperLvl], gracz[playerid][UID], vw, interior, Pos[0]+4.0, Pos[1] + 4.0, Pos[2], 0.0, 0.0, 0.0);
		// Definiowanie zmiennych
		PlayerEditObject[playerid] = uid;
		EditDynamicObject(playerid, ObjectInfo[uid][oObject]);///
		// Informacja o komendach dla gracza
		SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Stworzono obiekt: %d | To twój: %d obiekt | UID: %d"COL_RED"))", model, CountObjectsCreatedByPlayer(playerid), PlayerEditObject[playerid]);
		SendClientMessage(playerid, -1, "(("COL_GREY"Wskazówka: Wciśnij spację, aby móc manewrować kamerą"COL_WHITE"))");
		// Aktualizowanie pozycji
		Streamer_Update(playerid);
	}
	else if(gracz[playerid][MapperLvl] == 1)
	{
		new cidhid;
		new areatype = GetMapperAreaType(playerid, cidhid);//cidhid: 1/2 - domek/+int, 2 - firma, 0 null
		if(areatype == 1)//domek;
		{
			if(GetObjectCreatedPerG(areatype, cidhid) >= 10) return Error(playerid, "Limit obiektów przekroczony.");
			// Tworzenie obiektu
			new uid = AddObject(model, (OFFSET_HOUSEOBJ+cidhid), GetPlayerUID(playerid), vw, interior, Pos[0]+4.0, Pos[1] + 4.0, Pos[2], 0.0, 0.0, 0.0);
			// Definiowanie zmiennych
			PlayerEditObject[playerid] = uid;
			EditDynamicObject(playerid, ObjectInfo[uid][oObject]);
			// Informacja o komendach dla gracza
			SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Stworzono obiekt: %d | "COL_RED"%d"COL_GREY"/"COL_GREEN"10"COL_EASY" obiekt | UID: %d"COL_RED"))", model, GetObjectCreatedPerG(areatype, cidhid), PlayerEditObject[playerid]);
			SendClientMessage(playerid, -1, "(("COL_GREY"Wskazówka: Wciśnij spację, aby móc manewrować kamerą"COL_WHITE"))");
			// Aktualizowanie pozycji
			Streamer_Update(playerid);
		}
		else if(areatype == 2)//domek interior
		{
			Info(playerid, "WIP");
		}
		else if(areatype == 3)//firma
		{
			if(GetObjectCreatedPerG(areatype, cidhid) >= 10) return Error(playerid, "Limit obiektów przekroczony.");
			// Tworzenie obiektu
			new uid = AddObject(model, (OFFSET_COMPANYOBJ+cidhid), GetPlayerUID(playerid), vw, interior, Pos[0]+4.0, Pos[1] + 4.0, Pos[2], 0.0, 0.0, 0.0);
			// Definiowanie zmiennych
			PlayerEditObject[playerid] = uid;
			EditDynamicObject(playerid, ObjectInfo[uid][oObject]);
			// Informacja o komendach dla gracza
			SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Stworzono obiekt: %d | "COL_RED"%d"COL_GREY"/"COL_GREEN"10"COL_EASY" obiekt | UID: %d"COL_RED"))", model, GetObjectCreatedPerG(areatype, cidhid), PlayerEditObject[playerid]);
			SendClientMessage(playerid, -1, "(("COL_GREY"Wskazówka: Wciśnij spację, aby móc manewrować kamerą"COL_WHITE"))");
			// Aktualizowanie pozycji
			Streamer_Update(playerid);
		}
		else return Error(playerid, "Wystąpił nieoczekiwany błąd. Zgłoś go!");
	}
	/*else if(gracz[playerid][MapperLvl] == 1 && IsPlayerInBaseArea(playerid))
	{
		if(GetObjectCreatedPerGroup(playerid) >= 100) return Error(playerid, "Limit obiektów przekroczony (100 max).");
		// Tworzenie obiektu
		new uid = AddObject(model, gracz[playerid][OrgID], GetPlayerUID(playerid), vw, interior, Pos[0], Pos[1] + 2.0, Pos[2], 0.0, 0.0, 0.0);
		// Definiowanie zmiennych
		PlayerEditObject[playerid] = uid;
		EditDynamicObject(playerid, ObjectInfo[uid][oObject]);
		// Informacja o komendach dla gracza
		SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Stworzono obiekt: %d | "COL_RED"%d"COL_GREY"/"COL_GREEN"500"COL_EASY" obiekt | UID: %d"COL_RED"))", model, GetObjectCreatedPerGroup(playerid), PlayerEditObject[playerid]);
		SendClientMessage(playerid, -1, "(("COL_GREY"Wskazówka: Wciśnij spację, aby móc manewrować kamerą"COL_WHITE"))");
		// Aktualizowanie pozycji
		Streamer_Update(playerid);
	}*/
	return 1;
}
CMD:msel(playerid, params[])
{
	gracz[playerid][MapperLvl] = GetMapperPremGroup(playerid);
	if(!gracz[playerid][MapperLvl]) return Error(playerid, "Brak uprawnień.");
	if(PlayerEditObject[playerid]) return Error(playerid, "W tej chwili edytujesz inny obiekt.");
	SelectObject(playerid);
	return 1;
}
CMD:mdel(playerid, params[])
{
	if(!PlayerEditObject[playerid]) return Error(playerid, "Musisz być w trakcie edycji obiektu.");
	// Pobieranie ID obiektu
	// Usuwanie obiektu
	DeleteObject(PlayerEditObject[playerid]);
	// Informowanie gracza
	LeftNotifyShow(playerid, "Sukces!", "Obiekt ~r~usuniety~w~.", LN_RED);
	// Zerowanie zmiennych
	CancelEdit(playerid);
	Process_ObjectGateScan();
	PlayerEditObject[playerid] = 0;
	return 1;
}

CMD:mgate(playerid, params[])
{
	if(!PlayerEditObject[playerid]) return Error(playerid, "Musisz być w trakcie edycji obiektu.");
	new objectid = PlayerEditObject[playerid];
	SetPVarInt(playerid, "mgate_objectid", objectid);
	dialog_GATECREATOR(playerid, 1, 999, "null");
	CancelEdit(playerid);
	PlayerEditObject[playerid] = 0;
	return 1;
}

Dialog:GATECREATOR(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(gracz[playerid][MapperLvl] == 0) return Error(playerid, "Brak uprawnień.");
	new objectid = GetPVarInt(playerid, "mgate_objectid");
	new Float:oPos[6];
	switch(listitem)
	{
		case 0://Obiekt jest bramą
		{
			if(ObjectInfo[objectid][oMgate] > 0) ObjectInfo[objectid][oMgate] = 0;
			else ObjectInfo[objectid][oMgate] = 1;

			mq_format("UPDATE `Obiekty` SET `mgate`='%d' WHERE `id`='%d';", ObjectInfo[objectid][oMgate], objectid);
			mq_send("QMgate");
			Process_ObjectGateScan();
			//dialog_GATECREATOR(playerid, 1, 999, "null");
			SetTimerEx("dialog_GATECREATOR", 5, false, "ddd", playerid, 1, 999);
		}
		case 1://Odczytaj pozycję bramy OTWARTA
		{
			GetDynamicObjectPos(ObjectInfo[objectid][oObject], oPos[0], oPos[1], oPos[2]);
			GetDynamicObjectRot(ObjectInfo[objectid][oObject], oPos[3], oPos[4], oPos[5]);
			ObjectInfo[objectid][goX] = oPos[0]; 
			ObjectInfo[objectid][goY] = oPos[1];
			ObjectInfo[objectid][goZ] = oPos[2];

			ObjectInfo[objectid][goRX] = oPos[3];
			ObjectInfo[objectid][goRY] = oPos[4];
			ObjectInfo[objectid][goRZ] = oPos[5];

			mq_format("UPDATE `Obiekty` SET `gx`='%f', `gy`='%f', `gz`='%f', `grx`='%f', `gry`='%f', `grz`='%f' WHERE `id`='%d';", oPos[0], oPos[1], oPos[2], oPos[3], oPos[4], oPos[5], objectid);
			mq_send("QMgate");
			Process_ObjectGateScan();
			LeftNotifyShow(playerid, "Sukces!", "Uaktualniono pozycje bramy ~g~otwartej~w~. Kazda inna pozycja obiektu jest uznawana za pozycje zamknieta. Oznacza to, ze ~y~powinienes teraz przeniesc obiekt w pozycje bramy zamknietej i zapisac~w~.", LN_GREEN, 20);
		}
		case 2://Prędkość (m na sekundę)
		{
			new speed_list[2048];
			/*for(new s = 0; s < 10; s++)
			{
				format(speed_list, 1024, "%s"COL_RED"%0.1f "COL_WHITE"m na sekundę\n", speed_list, float(s));
			}*/
			new Float:selectspeed = 0.21;
			while(selectspeed < 11.0)
			{
				format(speed_list, 2048, "%s"COL_RED"%0.1f "COL_WHITE"m na sekundę\n", speed_list, selectspeed);
				selectspeed += 0.21;
			}
			Dialog_Show(playerid, GCSPEED, DIALOG_STYLE_LIST, ""COL_RED"•» "COL_WHITE" Prędkość bramy "COL_RED"«•", speed_list, "Wybierz", "Wstecz");
		}
		case 3://Zasięg (m)
		{
			new range_list[3048];
			for(new s = 1; s < 101; s++)
			{
				format(range_list, 3048, "%s"COL_RED"%0.1f "COL_WHITE"m\n", range_list, float(s));
			}
			Dialog_Show(playerid, GCRANGE, DIALOG_STYLE_LIST, ""COL_RED"•» "COL_WHITE" Zasięg wykrywania "COL_RED"«•", range_list, "Wybierz", "Wstecz");
		}
		case 4://Metoda sterowania
		{
			if(ObjectInfo[objectid][oMgate] == 2) ObjectInfo[objectid][oMgate] = 1;
			else ObjectInfo[objectid][oMgate] = 2;

			mq_format("UPDATE `Obiekty` SET `mgate`='%d' WHERE `id`='%d';", ObjectInfo[objectid][oMgate], objectid);
			mq_send("QMgate");
			Process_ObjectGateScan();
			//dialog_GATECREATOR(playerid, 1, 999, "null");
			SetTimerEx("dialog_GATECREATOR", 5, false, "ddd", playerid, 1, 999);
		}
		case 5:
		{
			if(gracz[playerid][MapperLvl] >= 2)
			{
				Dialog_Show(playerid, GCPERMG, DIALOG_STYLE_LIST, ""COL_RED"•» "COL_WHITE"Uprawnienia do korzystania z bramy "COL_RED"«•", ""COL_GREEN"Publiczne\n"COL_GREY"Gracz\n"COL_LIME"Frakcja\n"COL_BLUE"Firma\n"COL_ORANGE"Prywatny dom", "Wybierz", "Wstecz");
				SetPVarInt(playerid, "mgate_permtype", 0);
			}
			else
			{
				new objtype;
				if(ObjectInfo[objectid][oGrupa] >= OFFSET_HOUSEOBJ) objtype = 1;
				else if(ObjectInfo[objectid][oGrupa] >= OFFSET_HOUSEINTOBJ) objtype = 2;
				else if(ObjectInfo[objectid][oGrupa] >= OFFSET_COMPANYOBJ) objtype = 3;
				
				if(objtype == 1)
				{
					Dialog_Show(playerid, GCPERMG, DIALOG_STYLE_LIST, ""COL_RED"•» "COL_WHITE"Uprawnienia do korzystania z bramy "COL_RED"«•", ""COL_GREEN"Publiczne\n"COL_ORANGE"Prywatny dom", "Wybierz", "Wstecz");
					SetPVarInt(playerid, "mgate_permtype", 1);
				}
				else if(objtype == 2)
				{
					Dialog_Show(playerid, GCPERMG, DIALOG_STYLE_LIST, ""COL_RED"•» "COL_WHITE"Uprawnienia do korzystania z bramy "COL_RED"«•", ""COL_GREEN"Publiczne\n"COL_ORANGE"Prywatny dom", "Wybierz", "Wstecz");
					SetPVarInt(playerid, "mgate_permtype", 2);
				}
				else if(objtype == 3)
				{
					Dialog_Show(playerid, GCPERMG, DIALOG_STYLE_LIST, ""COL_RED"•» "COL_WHITE"Uprawnienia do korzystania z bramy "COL_RED"«•", ""COL_GREEN"Publiczne\n"COL_BLUE"Firma", "Wybierz", "Wstecz");
					SetPVarInt(playerid, "mgate_permtype", 3);
				}
				else Error(playerid, "Niezidentyfikowany obiekt.");
			}
		}
		default:
		{
			new strCreator[1024];
			format(strCreator, 1024, ""COL_WHITE"Akcja\t"COL_WHITE"Status");
			if(ObjectInfo[objectid][oMgate] > 0) 
			{
				format(strCreator, 1024, "%s\n"COL_LIME"•» "COL_WHITE"Obiekt jest bramą\t{00FF00}TAK", strCreator);
				format(strCreator, 1024, "%s\n"COL_LIME"•» "COL_WHITE"Ustaw aktualną pozycje jako brama otwarta\t"COL_GREEN"[ustaw]", strCreator);
				format(strCreator, 1024, "%s\n"COL_LIME"•» "COL_WHITE"Prędkość (m na sekundę)\t"COL_RED"%0.1f", strCreator, ObjectInfo[objectid][gSpeed]);
				format(strCreator, 1024, "%s\n"COL_LIME"•» "COL_WHITE"Zasięg (m)\t"COL_RED"%0.1f", strCreator, ObjectInfo[objectid][gRange]);
				format(strCreator, 1024, "%s\n"COL_LIME"•» "COL_WHITE"Metoda sterowania\t%s", strCreator, (ObjectInfo[objectid][oMgate] == 2) ? (""COL_BLUE"AUTOMAT") : (""COL_ORANGE"PRZYCISK"));
				
				switch(ObjectInfo[objectid][mgOwnerType])
				{
					case 1: format(strCreator, 1024, "%s\n"COL_LIME"•» "COL_WHITE"Uprawnienia\t"COL_GREY"Gracz: "COL_WHITE"%s", strCreator, GetPlayerIGName(ObjectInfo[objectid][mgOwner]));
					case 2: format(strCreator, 1024, "%s\n"COL_LIME"•» "COL_WHITE"Uprawnienia\t"COL_LIME"Frakcja: "COL_WHITE"%s", strCreator, GetFractionName(ObjectInfo[objectid][mgOwner]));
					case 3: format(strCreator, 1024, "%s\n"COL_LIME"•» "COL_WHITE"Uprawnienia\t"COL_BLUE"Firma: "COL_WHITE"%s", strCreator, company[ObjectInfo[objectid][mgOwner]][cny_name]);
					case 4: format(strCreator, 1024, "%s\n"COL_LIME"•» "COL_WHITE"Uprawnienia\t"COL_ORANGE"Dom ID: "COL_WHITE"%d", strCreator, ObjectInfo[objectid][mgOwner]);
					default: format(strCreator, 1024, "%s\n"COL_LIME"•» "COL_WHITE"Uprawnienia\t"COL_GREEN"Publiczne", strCreator);
				}
			}
			else
			{
				format(strCreator, 1024, "%s\n"COL_WHITE"Obiekt jest bramą\t{FF0000}NIE", strCreator);
			}
			Dialog_Show(playerid, GATECREATOR, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_WHITE" Kreator bram "COL_RED"«•", strCreator, "Wybierz", "Wyjdz");
		}
	}
	return 1;
}

Dialog:GCSPEED(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new objectid = GetPVarInt(playerid, "mgate_objectid");
		new Float:selectspeed = 0.21;
		new itemvar;
		while(selectspeed < 11.0)
		{
			if(itemvar == listitem) break;
			itemvar++;
			selectspeed += 0.21;
		}
		ObjectInfo[objectid][gSpeed] = selectspeed;
		mq_format("UPDATE `Obiekty` SET `gspeed`='%f' WHERE `id`='%d';", ObjectInfo[objectid][gSpeed], objectid);
		mq_send("QMgate");
		SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Ustawiono prędkość na: "COL_BLUE"%0.1f"COL_RED"))", ObjectInfo[objectid][gSpeed]);
	}
	dialog_GATECREATOR(playerid, 1, 999, "null");
	return 1;
}

Dialog:GCRANGE(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new objectid = GetPVarInt(playerid, "mgate_objectid");
		ObjectInfo[objectid][gRange] = float(listitem)+1.01;
		mq_format("UPDATE `Obiekty` SET `grange`='%f' WHERE `id`='%d';", ObjectInfo[objectid][gRange], objectid);
		mq_send("QMgate");
		SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Ustawiono zasięg wykrywania na: "COL_BLUE"%0.1f"COL_RED"))", ObjectInfo[objectid][gRange]);
	}
	dialog_GATECREATOR(playerid, 1, 999, "null");
	return 1;
}

Dialog:GCPERMG(playerid, response, listitem, inputtext[])
{
	if(!response) return dialog_GATECREATOR(playerid, 1, 999, "null");
	new objectid = GetPVarInt(playerid, "mgate_objectid");
	new permtype = GetPVarInt(playerid, "mgate_permtype");
	//per player editor
	if(permtype == 1 && listitem == 1)//domek
	{
		new cidhid = ObjectInfo[objectid][oGrupa]-OFFSET_HOUSEOBJ;
		new index;
		for(new h; h < MAX_HOUSES; h++)
		{
			if(house[h][h_id] == cidhid)
			{
				index = h;
				break;
			}
		}
		gui_cache[playerid][0][0] = index;
		dialog_GCPERMH(playerid, 1, 0, "null");
		return 1;
	}
	if(permtype == 2 && listitem == 1)//domek interior
	{
		new cidhid = ObjectInfo[objectid][oGrupa]-OFFSET_HOUSEINTOBJ;
		new index;
		for(new h; h < MAX_HOUSES; h++)
		{
			if(house[h][h_id] == cidhid)
			{
				index = h;
				break;
			}
		}
		gui_cache[playerid][0][0] = index;
		dialog_GCPERMH(playerid, 1, 0, "null");
		return 1;
	}
	if(permtype == 3 && listitem == 1)//firma
	{
		new cidhid = ObjectInfo[objectid][oGrupa]-OFFSET_COMPANYOBJ;
		ObjectInfo[objectid][mgOwner] = cidhid;
		ObjectInfo[objectid][mgOwnerType] = 3;
		SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Bramą może sterować tylko firma: "COL_BLUE"%s"COL_RED"))", company[cidhid][cny_name]);
		mq_format("UPDATE `Obiekty` SET `mgOwnerType`='%d', `mgOwner`='%d' WHERE `id`='%d';", ObjectInfo[objectid][mgOwnerType], ObjectInfo[objectid][mgOwner], objectid);
		mq_send("QMgate");
		dialog_GATECREATOR(playerid, 1, 999, "null");
		return 1;
	}
	//end
	switch(listitem)
	{
		case 0:
		{
			ObjectInfo[objectid][mgOwnerType] = 0;
			mq_format("UPDATE `Obiekty` SET `mgOwnerType`='%d' WHERE `id`='%d';", ObjectInfo[objectid][mgOwnerType], objectid);
			mq_send("QMgate");
			SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Bramą może sterować: "COL_BLUE"KAŻDY"COL_RED"))");
			dialog_GATECREATOR(playerid, 1, 999, "null");
		}
		case 1:
		{
			new strPlayerList[2048];
			format(strPlayerList, 2048, "ID\tNazwa gracza");
			new Float:pPos[3];
			new bool:find = false;
			for(new p = PlayerPoolSize(); p != -1; p--)
			{
				//if(p == playerid) continue;
				GetPlayerPos(p, pPos[0], pPos[1], pPos[2]);
				if(IsPlayerInRangeOfPoint(playerid, 15.0, pPos[0], pPos[1], pPos[2]))
				{
					format(strPlayerList, 2048, "%s\n%d\t{%06x}%s", strPlayerList, p, GetPlayerColor(playerid) >>> 8,nick(p));
					find = true;
				}
			}
			if(find) Dialog_Show(playerid, GCPERMP, DIALOG_STYLE_TABLIST_HEADERS,  ""COL_RED"•» "COL_WHITE"Lista graczy w pobliżu "COL_RED"«•", strPlayerList, "Wybierz", "Anuluj");
			else Error(playerid, "Nie znaleziono żadnego gracza w pobliżu.");
		}
		case 2:
		{
			Dialog_Show(playerid, GCPERMF, DIALOG_STYLE_LIST, "Lista frakcji", "{303EFF}Policja\n{048100}Straż Graniczna\n{FF0000}Służby Ratunkowe\n{FF9A00}Pomoc Drogowa\n{E7DE00}Taxi\n"COL_MAFIA"Mafia Paliwowa", "Wybierz", "Wstecz");
		}
		case 3:
		{
			new company_id;
			for(new cid; cid < MAX_COMPANY; cid++)
			{
				if(PosRangeOfCompany(cid, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]))
				{
					company_id = cid;
					break;
				}
			}
			if(company_id == 0) return Error(playerid, "Nie jesteś na terenie firmy.");
			ObjectInfo[objectid][mgOwner] = company_id;
			ObjectInfo[objectid][mgOwnerType] = 3;
			SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Bramą może sterować tylko firma: "COL_BLUE"%s"COL_RED"))", company[company_id][cny_name]);
			mq_format("UPDATE `Obiekty` SET `mgOwnerType`='%d', `mgOwner`='%d' WHERE `id`='%d';", ObjectInfo[objectid][mgOwnerType], ObjectInfo[objectid][mgOwner], objectid);
			mq_send("QMgate");
			dialog_GATECREATOR(playerid, 1, 999, "null");
		}
		case 4://prywatny domek
		{
			new house_list[2048];
			format(house_list, 2048, "ID Domu\tAktualny właściciel");
			new bool:find = false;
			new listcount;
			for(new h; h < MAX_HOUSES; h++)
			{
				if(house[h][h_id] == 0) continue;
				if(IsPlayerInRangeOfPoint(playerid, 100.0, house[h][h_extX], house[h][h_extY], house[h][h_extZ]))
				{
					format(house_list, 2048, "%s\n%d\t%s", house_list, house[h][h_id], GetPlayerIGName(house[h][h_owneruid]));
					gui_cache[playerid][listcount][0] = h;
					listcount++;
					find = true;
				}
			}
			if(find) Dialog_Show(playerid, GCPERMH, DIALOG_STYLE_TABLIST_HEADERS,  ""COL_RED"•» "COL_WHITE"Lista domów w pobliżu "COL_RED"«•", house_list, "Wybierz", "Anuluj");
			else Error(playerid, "Nie znaleziono żadnego domu w pobliżu.");
		}
	}
	
	return 1;
}


Dialog:GCPERMP(playerid, response, listitem, inputtext[])
{
	if(!response) return dialog_GATECREATOR(playerid, 1, 999, "null");
	new objectid = GetPVarInt(playerid, "mgate_objectid");
	new ownerid = strval(inputtext);
	ObjectInfo[objectid][mgOwner] = gracz[ownerid][UID];
	ObjectInfo[objectid][mgOwnerType] = 1;
	SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Bramą może sterować tylko gracz: "COL_BLUE"%s"COL_RED"))", GetPlayerIGName(ObjectInfo[objectid][mgOwner]));
	mq_format("UPDATE `Obiekty` SET `mgOwnerType`='%d', `mgOwner`='%d' WHERE `id`='%d';", ObjectInfo[objectid][mgOwnerType], ObjectInfo[objectid][mgOwner], objectid);
	mq_send("QMgate");
	dialog_GATECREATOR(playerid, 1, 999, "null");
	return 1;
}

Dialog:GCPERMF(playerid, response, listitem, inputtext[])
{
	if(!response) return dialog_GATECREATOR(playerid, 1, 999, "null");
	new objectid = GetPVarInt(playerid, "mgate_objectid");
	ObjectInfo[objectid][mgOwner] = listitem+1;
	ObjectInfo[objectid][mgOwnerType] = 2;
	SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Bramą może sterować tylko frakcja: "COL_BLUE"%s"COL_RED"))", GetFractionName(ObjectInfo[objectid][mgOwner]));
	mq_format("UPDATE `Obiekty` SET `mgOwnerType`='%d', `mgOwner`='%d' WHERE `id`='%d';", ObjectInfo[objectid][mgOwnerType], ObjectInfo[objectid][mgOwner], objectid);
	mq_send("QMgate");
	dialog_GATECREATOR(playerid, 1, 999, "null");
	return 1;
}

Dialog:GCPERMH(playerid, response, listitem, inputtext[])
{
	if(!response) return dialog_GATECREATOR(playerid, 1, 999, "null");
	new objectid = GetPVarInt(playerid, "mgate_objectid");
	new houseid = gui_cache[playerid][listitem][0] ;
	ObjectInfo[objectid][mgOwner] = house[houseid][h_id];
	ObjectInfo[objectid][mgOwnerType] = GATE_HOME;
	SendClientMessageEx(playerid, -1, ""COL_RED"(("COL_EASY"Bramą może sterować tylko właściciel/lokator domu(ID: %d), właściciel: "COL_BLUE"%s"COL_RED"))", house[houseid][h_id], GetPlayerIGName(house[houseid][h_owneruid]));
	mq_format("UPDATE `Obiekty` SET `mgOwnerType`='%d', `mgOwner`='%d' WHERE `id`='%d';", ObjectInfo[objectid][mgOwnerType], ObjectInfo[objectid][mgOwner], objectid);
	mq_send("QMgate");
	dialog_GATECREATOR(playerid, 1, 999, "null");
	return 1;
}

stock PlayerCanUseGate(playerid, objectid)
{
	if(ObjectInfo[objectid][oInt] != -1 && ObjectInfo[objectid][oInt] != GetPlayerInterior(playerid)) return 0;
	if(ObjectInfo[objectid][oVW] != -1 && ObjectInfo[objectid][oVW] != GetPlayerVirtualWorld(playerid)) return 0;
	if(ObjectInfo[objectid][mgOwnerType] == VEHICLE_FRACTION && (ObjectInfo[objectid][mgOwner] == F_POLICE || ObjectInfo[objectid][mgOwner] == F_BORDERGUARD) && (gracz[playerid][frakcja] == F_POLICE || gracz[playerid][frakcja] == F_BORDERGUARD)) return 1;//Policja i SG mogą używać swoich bram
	if(ObjectInfo[objectid][mgOwnerType] == GATE_PLAYER && gracz[playerid][UID] != ObjectInfo[objectid][mgOwner]) return 0;
	if(ObjectInfo[objectid][mgOwnerType] == VEHICLE_FRACTION && (gracz[playerid][frakcja] == 0 || gracz[playerid][frakcja] != ObjectInfo[objectid][mgOwner])) return 0;
	if(ObjectInfo[objectid][mgOwnerType] == VEHICLE_BUSINESS && (gracz[playerid][firma] == 0 || gracz[playerid][firma] != ObjectInfo[objectid][mgOwner])) return 0;
	if(ObjectInfo[objectid][mgOwnerType] == GATE_HOME)//domki
	{
		new bool:find = false;
		for(new h; h < MAX_HOUSES; h++)
		{
			if(house[h][h_id] == 0) continue;
			if(house[h][h_id] == ObjectInfo[objectid][mgOwner])
			{
				if(house[h][h_owneruid] == gracz[playerid][UID] || house[h][h_renteruid] == gracz[playerid][UID])
				{
					find = true;
					break;
				}
			}
		}
		if(find == false) return 0;
	}
	return 1;
}

forward Object_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
public Object_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	new timeopen;
	if(((RELEASED(KEY_CTRL_BACK) || RELEASED(KEY_HANDBRAKE)) && !IsPlayerInAnyVehicle(playerid)) || ((RELEASED(KEY_CROUCH)) && IsPlayerInAnyVehicle(playerid)))
	{
		new g;
		for(new go; go < MAX_GATES; go++)
		{
			if(GateObjects[go] != 0)
			{
				g = GateObjects[go];
				if(ObjectInfo[g][oMgate] == 1)//przycisk
				{
					if(PlayerCanUseGate(playerid, g))
					{
						if(IsPlayerInRangeOfPoint(playerid, ObjectInfo[g][gRange], ObjectInfo[g][oX] , ObjectInfo[g][oY] , ObjectInfo[g][oZ]))
						{
							if(!ObjectInfo[g][gOpen])
							{
								timeopen = MoveDynamicObject(ObjectInfo[g][oObject], ObjectInfo[g][goX], ObjectInfo[g][goY], ObjectInfo[g][goZ], ObjectInfo[g][gSpeed], ObjectInfo[g][goRX], ObjectInfo[g][goRY], ObjectInfo[g][goRZ]);
								ObjectInfo[g][gOpen] = true;
								//GameTextForPlayer(playerid, "~g~Otwieranie...",  timeopen+500, 4);
								#pragma unused timeopen
							}
							else
							{
								timeopen = MoveDynamicObject(ObjectInfo[g][oObject], ObjectInfo[g][oX], ObjectInfo[g][oY], ObjectInfo[g][oZ], ObjectInfo[g][gSpeed], ObjectInfo[g][oRX], ObjectInfo[g][oRY], ObjectInfo[g][oRZ]);
								ObjectInfo[g][gOpen] = false;
								//GameTextForPlayer(playerid, "~r~Zamykanie...",  timeopen+500, 4);
								#pragma unused timeopen
							}
							break;
						}
					}
				}
			}
		}
	}
	return 1;
}

task Process_ObjectGateScan()
{
	for(new go; go < MAX_GATES; go++)//czyszczenie tablicy 
	{
		GateObjects[go] = 0;
	}
	for(new g; g < MAX_OBJECTS; g++)
	{
		if(ObjectInfo[g][oMgate] != 0)
		{
			for(new go; go < MAX_GATES; go++)//uzupełnianie tablicy bram
			{
				if(GateObjects[go] == 0)
				{
					GateObjects[go] = g;
					break;
				}
			}
		}
	}
	return 1;
}

task Process_PlayerGateDetect(playerid)
{
	new g;
	for(new go; go < MAX_GATES; go++)
	{
		if(GateObjects[go] != 0)
		{
			g = GateObjects[go];
			if(ObjectInfo[g][oMgate] == 2)//automat
			{
				if(PlayerCanUseGate(playerid, g))
				{
					if(IsPlayerInRangeOfPoint(playerid, ObjectInfo[g][gRange], ObjectInfo[g][oX] , ObjectInfo[g][oY] , ObjectInfo[g][oZ]))
					{
						if(!ObjectInfo[g][gOpen])
						{
							MoveDynamicObject(ObjectInfo[g][oObject], ObjectInfo[g][goX], ObjectInfo[g][goY], ObjectInfo[g][goZ], ObjectInfo[g][gSpeed], ObjectInfo[g][goRX], ObjectInfo[g][goRY], ObjectInfo[g][goRZ]);
							ObjectInfo[g][gOpen] = true;
						}
						ObjectInfo[g][gCloseTimeOut] = serwer[time_timestamp]+2;
						break;
					}	
				}
			}
		}
	}
	//info
	for(new go; go < MAX_GATES; go++)
	{
		if(GateObjects[go] != 0)
		{
			g = GateObjects[go];
			if(ObjectInfo[g][oMgate] == 1)//guzik
			{
				if(PlayerCanUseGate(playerid, g))
				{
					if(IsPlayerInRangeOfPoint(playerid, ObjectInfo[g][gRange], ObjectInfo[g][oX] , ObjectInfo[g][oY] , ObjectInfo[g][oZ]))
					{
						if(IsPlayerInAnyVehicle(playerid)) ShowActionTD(playerid, "Interakcja - nacisnij klawisz ~y~H~w~.");
						else ShowActionTD(playerid, "Interakcja - nacisnij klawisz ~y~H~w~/~y~PPM~w~.");
						return 1;
					}	
				}
			}
		}
	}
	HideActionTD(playerid);
	return 1;
}

task Process_AutoCloseGates()
{
	new g;
	for(new go; go < MAX_GATES; go++)
	{
		if(GateObjects[go] != 0)
		{
			g = GateObjects[go];
			if(ObjectInfo[g][oMgate] == 2)//automat
			{
				if(ObjectInfo[g][gOpen])
				{
					if(ObjectInfo[g][gCloseTimeOut] < serwer[time_timestamp])
					{
						MoveDynamicObject(ObjectInfo[g][oObject], ObjectInfo[g][oX], ObjectInfo[g][oY], ObjectInfo[g][oZ], ObjectInfo[g][gSpeed], ObjectInfo[g][oRX], ObjectInfo[g][oRY], ObjectInfo[g][oRZ]);
						ObjectInfo[g][gOpen] = false;
					}
				}
			}
		}
	}
	return 1;
}

CMD:mcopy(playerid, params[])
{
	gracz[playerid][MapperLvl] = GetMapperPremGroup(playerid);
	if(!PlayerEditObject[playerid]) return Error(playerid, "Musisz być w trakcie edycji obiektu.");
	if(CountObjectsFromDB() >= MAX_OBJECTS) return Error(playerid, "Limit obiektów na serwerze przekroczony!");
	new objectid = PlayerEditObject[playerid];
	new vw = GetPlayerVirtualWorld(playerid); // Definiowanie świata
	new interior = GetPlayerInterior(playerid); // Definiowanie interior
	new Float:Pos[3]; // Definiowanie pozycji
	new Float:Rot[3]; // Definiowanie pozycji
	GetDynamicObjectRot(ObjectInfo[objectid][oObject], Rot[0], Rot[1], Rot[2]);
	GetDynamicObjectPos(ObjectInfo[objectid][oObject], Pos[0], Pos[1], Pos[2]);
	new uid;
	if(gracz[playerid][MapperLvl] >= 2)
	{
		uid = AddObject(ObjectInfo[objectid][oModel], 0 - gracz[playerid][MapperLvl], GetPlayerUID(playerid), vw, interior, Pos[0], Pos[1], Pos[2], Rot[0], Rot[1], Rot[2]);
	}
	else if(gracz[playerid][MapperLvl] == 1)
	{
		new cidhid;
		new areatype = GetMapperAreaType(playerid, cidhid);//cidhid: 1 - domek, 2 - firma, 0 null
		if(areatype == 1)//domek;
		{
			if(GetObjectCreatedPerG(areatype, cidhid) >= 10) return Error(playerid, "Limit obiektów przekroczony.");
			uid = AddObject(ObjectInfo[objectid][oModel], (OFFSET_HOUSEOBJ+cidhid), GetPlayerUID(playerid), vw, interior, Pos[0], Pos[1], Pos[2], Rot[0], Rot[1], Rot[2]);
		}
		else if(areatype == 2)//domek interior
		{
			Info(playerid, "WIP");
		}
		else if(areatype == 3)//firma
		{
			if(GetObjectCreatedPerG(areatype, cidhid) >= 10) return Error(playerid, "Limit obiektów przekroczony.");
			uid = AddObject(ObjectInfo[objectid][oModel], (OFFSET_COMPANYOBJ+cidhid), GetPlayerUID(playerid), vw, interior, Pos[0], Pos[1], Pos[2], Rot[0], Rot[1], Rot[2]);
		}
	}
	else return Error(playerid, "Wystąpił nieoczekiwany błąd.");
	GetDynamicObjectPos(ObjectInfo[uid][oObject], ObjectInfo[uid][oX], ObjectInfo[uid][oY], ObjectInfo[uid][oZ]);
	GetDynamicObjectRot(ObjectInfo[uid][oObject], ObjectInfo[uid][oRX], ObjectInfo[uid][oRY], ObjectInfo[uid][oRZ]);
	OnPlayerEditDynamicObject(playerid, ObjectInfo[uid][oObject], EDIT_RESPONSE_FINAL, ObjectInfo[uid][oX], ObjectInfo[uid][oY], ObjectInfo[uid][oZ], ObjectInfo[uid][oRX], ObjectInfo[uid][oRY], ObjectInfo[uid][oRZ]);
	EditDynamicObject(playerid, ObjectInfo[uid][oObject]);
	PlayerEditObject[playerid] = uid;
	LeftNotifyShow(playerid, "Sukces!", "Obiekt ~g~skopiowany~w~.", LN_GREEN);
	Streamer_Update(playerid);
	return 1;
}

CMD:mcopyex(playerid, params[])
{
	gracz[playerid][MapperLvl] = GetMapperPremGroup(playerid);
	if(!PlayerEditObject[playerid]) return Error(playerid, "Musisz być w trakcie edycji obiektu.");
	if(CountObjectsFromDB() >= MAX_OBJECTS) return Error(playerid, "Limit obiektów na serwerze przekroczony!");
	new objectid = PlayerEditObject[playerid];
	if(ObjectInfo[objectid][oMMAT] == 0) return PC_EmulateCommand(playerid, "/mcopy");
	new vw = GetPlayerVirtualWorld(playerid); // Definiowanie świata
	new interior = GetPlayerInterior(playerid); // Definiowanie interior
	new Float:Pos[3]; // Definiowanie pozycji
	new Float:Rot[3]; // Definiowanie pozycji
	GetDynamicObjectRot(ObjectInfo[objectid][oObject], Rot[0], Rot[1], Rot[2]);
	GetDynamicObjectPos(ObjectInfo[objectid][oObject], Pos[0], Pos[1], Pos[2]);
	new uid;
	if(gracz[playerid][MapperLvl] >= 2)
	{
		uid = AddObject(ObjectInfo[objectid][oModel], 0 - gracz[playerid][MapperLvl], GetPlayerUID(playerid), vw, interior, Pos[0], Pos[1], Pos[2], Rot[0], Rot[1], Rot[2]);
	}
	else if(gracz[playerid][MapperLvl] == 1)
	{
		new cidhid;
		new areatype = GetMapperAreaType(playerid, cidhid);//cidhid: 1 - domek, 2 - firma, 0 null
		if(areatype == 1)//domek;
		{
			if(GetObjectCreatedPerG(areatype, cidhid) >= 10) return Error(playerid, "Limit obiektów przekroczony.");
			uid = AddObject(ObjectInfo[objectid][oModel], (OFFSET_HOUSEOBJ+cidhid), GetPlayerUID(playerid), vw, interior, Pos[0], Pos[1], Pos[2], Rot[0], Rot[1], Rot[2]);
		}
		else if(areatype == 2)//domek interior
		{
			Info(playerid, "WIP");
		}
		else if(areatype == 3)//firma
		{
			if(GetObjectCreatedPerG(areatype, cidhid) >= 10) return Error(playerid, "Limit obiektów przekroczony.");
			uid = AddObject(ObjectInfo[objectid][oModel], (OFFSET_COMPANYOBJ+cidhid), GetPlayerUID(playerid), vw, interior, Pos[0], Pos[1], Pos[2], Rot[0], Rot[1], Rot[2]);
		}
	}
	else return Error(playerid, "Wystąpił nieoczekiwany błąd.");
	GetDynamicObjectPos(ObjectInfo[uid][oObject], ObjectInfo[uid][oX], ObjectInfo[uid][oY], ObjectInfo[uid][oZ]);
	GetDynamicObjectRot(ObjectInfo[uid][oObject], ObjectInfo[uid][oRX], ObjectInfo[uid][oRY], ObjectInfo[uid][oRZ]);
	OnPlayerEditDynamicObject(playerid, ObjectInfo[uid][oObject], EDIT_RESPONSE_FINAL, ObjectInfo[uid][oX], ObjectInfo[uid][oY], ObjectInfo[uid][oZ], ObjectInfo[uid][oRX], ObjectInfo[uid][oRY], ObjectInfo[uid][oRZ]);
	EditDynamicObject(playerid, ObjectInfo[uid][oObject]);
	PlayerEditObject[playerid] = uid;
	//kopiowanie i nakładanie mmatu
	for(new t_materialindex; t_materialindex < 16; t_materialindex++)
	{
		//printf("%d", t_materialindex);
		new str_cmd[144];
		new t_modelid, t_txdname[64], t_texturename[64], t_materialcolor;
		GetDynamicObjectMaterial(ObjectInfo[objectid][oObject], t_materialindex, t_modelid, t_txdname, t_texturename, t_materialcolor);
		//printf("GetDynamicObjectMaterial: %d %d", t_materialindex, IsDynamicObjectMaterialUsed(ObjectInfo[objectid][oObject], t_materialindex));
		if(IsDynamicObjectMaterialUsed(ObjectInfo[objectid][oObject], t_materialindex))
		{
			format(str_cmd, 144, "/mmat %d 0 0x%x %d %s %s", t_materialindex, t_materialcolor, t_modelid, t_txdname, t_texturename);
			PC_EmulateCommand(playerid, str_cmd);
			SendClientMessage(playerid, 0xFF0000FF, str_cmd);
		}
		new t_text[64], t_materialsize, t_fontface[64], t_fontsize, t_bold, t_fontcolor, t_backcolor, t_textalignment;
		GetDynamicObjectMaterialText(ObjectInfo[objectid][oObject], t_materialindex, t_text, t_materialsize, t_fontface, t_fontsize, t_bold, t_fontcolor, t_backcolor, t_textalignment);
		//printf("GetDynamicObjectMaterialText: %d %d", t_materialindex, IsDynamicObjectMaterialTextUsed(ObjectInfo[uid][oObject], t_materialindex));
		if(IsDynamicObjectMaterialTextUsed(ObjectInfo[objectid][oObject], t_materialindex))
		{
			format(str_cmd, 144, "/mmat %d 1 %d %d %d 0x%x 0x%x %d %s %s", t_materialindex, t_materialsize, t_fontsize, t_bold, t_fontcolor, t_backcolor, t_textalignment, t_fontface, t_text);
			PC_EmulateCommand(playerid, str_cmd);
			SendClientMessage(playerid, 0xFF0000FF, str_cmd);
		}
	}
	//end - kopiowanie i nakładanie mmatu
	LeftNotifyShow(playerid, "Sukces!", "Obiekt ~g~skopiowany~w~ razem z MMAT.", LN_GREEN);
	Streamer_Update(playerid);
	return 1;
}

CMD:mrx(playerid, params[])
{
	new Float: pos;
	if(!PlayerEditObject[playerid]) return Error(playerid, "Musisz być w trakcie edycji obiektu.");
	if(sscanf(params, "f", pos))
	{
		SendClientMessage(playerid, -1, "UŻYJ: /mrx [rotacja X]");
		return 1;
	}
	else
	{
		// Pobieranie ID obiektu
		new objectid = PlayerEditObject[playerid];
		// Pobieranie i ustawianie obiektu
		GetDynamicObjectRot(ObjectInfo[objectid][oObject],  ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		ObjectInfo[objectid][oRX] = ObjectInfo[objectid][oRX]+pos;
		SetDynamicObjectRot(ObjectInfo[objectid][oObject],  ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		//
		GetDynamicObjectPos(ObjectInfo[objectid][oObject], ObjectInfo[objectid][oX], ObjectInfo[objectid][oY], ObjectInfo[objectid][oZ]);
		OnPlayerEditDynamicObject(playerid, ObjectInfo[objectid][oObject], EDIT_RESPONSE_FINAL, ObjectInfo[objectid][oX], ObjectInfo[objectid][oY], ObjectInfo[objectid][oZ]\
		, ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		EditDynamicObject(playerid, ObjectInfo[objectid][oObject]);
		PlayerEditObject[playerid] = objectid;
		//
		Streamer_Update(playerid);
		// Informowanie gracza
		LeftNotifyShow(playerid, "Sukces!", "Rotacja obiektu ~g~zmieniona~w~.", LN_GREEN);
	}
	return 1;
}
CMD:mry(playerid, params[])
{
	new Float: pos;
	if(!PlayerEditObject[playerid]) return Error(playerid, "Musisz być w trakcie edycji obiektu.");
	if(sscanf(params, "f", pos))
	{
		SendClientMessage(playerid, -1, "UŻYJ: /mry [rotacja Y]");
		return 1;
	}
	else
	{
		// Pobieranie ID obiektu
		new objectid = PlayerEditObject[playerid];
		// Pobieranie i ustawianie obiektu
		GetDynamicObjectRot(ObjectInfo[objectid][oObject],  ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		ObjectInfo[objectid][oRY] = ObjectInfo[objectid][oRY]+pos;
		SetDynamicObjectRot(ObjectInfo[objectid][oObject],  ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		//
		GetDynamicObjectPos(ObjectInfo[objectid][oObject], ObjectInfo[objectid][oX], ObjectInfo[objectid][oY], ObjectInfo[objectid][oZ]);
		OnPlayerEditDynamicObject(playerid, ObjectInfo[objectid][oObject], EDIT_RESPONSE_FINAL, ObjectInfo[objectid][oX], ObjectInfo[objectid][oY], ObjectInfo[objectid][oZ]\
		, ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		EditDynamicObject(playerid, ObjectInfo[objectid][oObject]);
		PlayerEditObject[playerid] = objectid;
		//
		Streamer_Update(playerid);
		// Informowanie gracza
		LeftNotifyShow(playerid, "Sukces!", "Rotacja obiektu ~g~zmieniona~w~.", LN_GREEN);
	}
	return 1;
}
CMD:mrz(playerid, params[])
{
	new Float: pos;
	if(!PlayerEditObject[playerid]) return Error(playerid, "Musisz być w trakcie edycji obiektu.");
	if(sscanf(params, "f", pos))
	{
		SendClientMessage(playerid, -1, "UŻYJ: /mrz [rotacja Z]");
		return 1;
	}
	else
	{
		// Pobieranie ID obiektu
		new objectid = PlayerEditObject[playerid];
		// Pobieranie i ustawianie obiektu
		GetDynamicObjectRot(ObjectInfo[objectid][oObject], ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		ObjectInfo[objectid][oRZ] = ObjectInfo[objectid][oRZ]+pos;
		SetDynamicObjectRot(ObjectInfo[objectid][oObject],  ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		//
		GetDynamicObjectPos(ObjectInfo[objectid][oObject], ObjectInfo[objectid][oX], ObjectInfo[objectid][oY], ObjectInfo[objectid][oZ]);
		OnPlayerEditDynamicObject(playerid, ObjectInfo[objectid][oObject], EDIT_RESPONSE_FINAL, ObjectInfo[objectid][oX], ObjectInfo[objectid][oY], ObjectInfo[objectid][oZ]\
		, ObjectInfo[objectid][oRX], ObjectInfo[objectid][oRY], ObjectInfo[objectid][oRZ]);
		EditDynamicObject(playerid, ObjectInfo[objectid][oObject]);
		PlayerEditObject[playerid] = objectid;
		//
		Streamer_Update(playerid);
		// Informowanie gracza
		LeftNotifyShow(playerid, "Sukces!", "Rotacja obiektu ~g~zmieniona~w~.", LN_GREEN);
	}
	return 1;
}
CMD:mmat(playerid, params[])
{
	if(!PlayerEditObject[playerid]) return Error(playerid, "Musisz być w trakcie edycji obiektu.");
	new index, type, comm1[256];
	new query[1024];
	if(sscanf(params, "ddS()[256]", index, type, comm1))
	{
		SendClientMessage(playerid, -1, "UŻYJ: /mmat [index (0 - 15) [0 - tekstura / 1 - napis] [parametry]");
		return 1;
	}
	else
	{
		if(index < 0 || index > 15)
		{
			SendClientMessage(playerid, -1, "Maxymalny index to 15 a minimalny to 0 - ustaw poprawny index.");
			return 1;
		}
		if(type != 0 && type != 1)
		{
			SendClientMessage(playerid, -1, "Typ nie jest prawidłowy. 0 - tekstura / 1 - napis - Ustaw poprawny typ.");
			return 1;
		}
		if(type) // Napis
		{
			new object = PlayerEditObject[playerid];
			new matsize, fontsize, bold, fontcolor, backcolor, align, fontface[32], text[64];
			if(sscanf(comm1, "dddxxds[32]s[64]", matsize, fontsize, bold, fontcolor, backcolor, align, fontface, text))
			{
				SendClientMessage(playerid, -1, "UŻYJ: /mmat [index (0 - 15)] 1 [matsize] [fontsize] [bold] [fontcolor] [backcolor] [align] [font] [text]");
				return 1;
			}
			else
			{
				new color_font = ShiftRGBAToABGR(fontcolor);
				new color_back = ShiftRGBAToABGR(backcolor);
				EscapeMMAT(text);
				SetDynamicObjectMaterialText(ObjectInfo[object][oObject], index, text, matsize, fontface, fontsize, bold, color_font, color_back, align);
				ObjectInfo[object][oMMAT] = 1;
				SaveObject(ObjectInfo[object][oUID]);
				mysql_escape_string(fontface, fontface);
				mysql_escape_string(text, text);
				mysql_format(g_SQL,query, sizeof(query), "DELETE FROM `Obiekty_text` WHERE `index` = '%d' AND `object` = '%d'", index, ObjectInfo[object][oUID]);
				mysql_tquery(g_SQL,query,"SendQuery","");
				mysql_format(g_SQL,query, sizeof(query), "DELETE FROM `Obiekty_textury` WHERE `index` = '%d' AND `object` = '%d'", index, ObjectInfo[object][oUID]);
				mysql_tquery(g_SQL,query,"SendQuery","");
				mysql_format(g_SQL,query, sizeof(query), "INSERT INTO `Obiekty_text` VALUES (NULL, '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%s', '%s')", ObjectInfo[object][oUID], index, matsize, fontsize, bold, color_font, color_back, align, fontface, text);
				mysql_tquery(g_SQL,query,"SendQuery","");
				LeftNotifyShow(playerid, "Sukces!", "Tekstura ~g~nalozona~w~.", LN_GREEN);
			}
		}
		else // Tekstura
		{
			new object = PlayerEditObject[playerid];
			new modelid, txdname[32], texturename[32], materialcolor;
			if(sscanf(comm1, "xds[32]s[32]", materialcolor, modelid, txdname, texturename))
			{
				SendClientMessage(playerid, -1, "UŻYJ: /mmat [index (0 - 15)] 0 [materialcolor] [modelid] [txdname] [texturename]");
				return 1;
			}
			else
			{
				SetDynamicObjectMaterial(ObjectInfo[object][oObject], index, modelid, txdname, texturename, ShiftRGBAToABGR(materialcolor));
				ObjectInfo[object][oMMAT] = 1;
				SaveObject(ObjectInfo[object][oUID]);
				mysql_escape_string(txdname, txdname);
				mysql_escape_string(texturename, texturename);
				mysql_format(g_SQL,query, sizeof(query), "DELETE FROM `Obiekty_textury` WHERE `index` = '%d' AND `object` = '%d'", index, ObjectInfo[object][oUID]);
				mysql_tquery(g_SQL,query,"SendQuery","");
				mysql_format(g_SQL,query, sizeof(query), "DELETE FROM `Obiekty_text` WHERE `index` = '%d' AND `object` = '%d'", index, ObjectInfo[object][oUID]);
				mysql_tquery(g_SQL,query,"SendQuery","");
				mysql_format(g_SQL,query, sizeof(query), "INSERT INTO `Obiekty_textury` VALUES (NULL,'%d', '%d', '%d', '%d', '%s', '%s')", ObjectInfo[object][oUID], index, ShiftRGBAToABGR(materialcolor), modelid, txdname, texturename);
				mysql_tquery(g_SQL,query,"SendQuery","");
				LeftNotifyShow(playerid, "Sukces!", "Tekstura ~g~nalozona~w~.", LN_GREEN);
			}
		}
	}
	return 1;
}

public OnDynamicObjectMoved(objectid)
{
	firework_OnDynamicObjectMoved(objectid);
	return 1;
}