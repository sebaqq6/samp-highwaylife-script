//********************************************************************************************INICJACJA UŻYCIA PRZEDMIOTU
stock UseItem(playerid, itemid)
{
	switch(itemid)
	{
		case 1..4://bandana
		{
			if(eq_select[playerid][s_used])
			{
				new str_akc[512];
				format(str_akc, 512, ""COL_WHITE"1. "COL_RED"Przestań używać");
				format(str_akc, 512, "%s\n"COL_WHITE"2. "COL_EASY"Edytuj", str_akc);
				format(str_akc, 512, "%s\n"COL_WHITE"3. "COL_GREEN"Zresetuj pozycje", str_akc);
				Dialog_Show(playerid, BANDANACONF, DIALOG_STYLE_LIST, ""COL_BLUE"»"COL_GREY" Bandana", str_akc, "Wybierz", "Anuluj");
			}
			else
			{
				if(IsPlayerAttachedObjectSlotUsed(playerid, BANDANA_SLOT))
				{
					LeftNotifyShow(playerid, "error", "Mozna miec tylko ~r~jedna~w~ bandane w uzyciu.");
				}
				else 
				{
					mq_format("UPDATE `przedmioty` SET `used`='1' WHERE `id`='%d';", eq_select[playerid][s_id]);
					mysql_query(g_SQL, mQuery, false);
					LeftNotifyShow(playerid, "Sukces!", "Bandana ~g~nalozona~w~!");
					LoadUsedAccessories(playerid);
				}
			}
		}
		case 5..30://okulary
		{
			if(eq_select[playerid][s_used])
			{
				new str_akc[512];
				format(str_akc, 512, ""COL_WHITE"1. "COL_RED"Przestań używać");
				format(str_akc, 512, "%s\n"COL_WHITE"2. "COL_EASY"Edytuj", str_akc);
				format(str_akc, 512, "%s\n"COL_WHITE"3. "COL_GREEN"Zresetuj pozycje", str_akc);
				Dialog_Show(playerid, OKULARYCONF, DIALOG_STYLE_LIST, ""COL_BLUE"»"COL_GREY" Okulary", str_akc, "Wybierz", "Anuluj");
			}
			else
			{
				if(IsPlayerAttachedObjectSlotUsed(playerid, OKULARY_SLOT))
				{
					LeftNotifyShow(playerid, "error", "Mozna miec tylko ~r~jedne~w~ okulary w uzyciu.");
				}
				else 
				{
					mq_format("UPDATE `przedmioty` SET `used`='1' WHERE `id`='%d';", eq_select[playerid][s_id]);
					mysql_query(g_SQL, mQuery, false);
					LeftNotifyShow(playerid, "Sukces!", "Okulary ~g~nalozone~w~!");
					LoadUsedAccessories(playerid);
				}
			}
		}
		case 31..43://czapki
		{
			if(eq_select[playerid][s_used])
			{
				new str_akc[512];
				format(str_akc, 512, ""COL_WHITE"1. "COL_RED"Przestań używać");
				format(str_akc, 512, "%s\n"COL_WHITE"2. "COL_EASY"Edytuj", str_akc);
				format(str_akc, 512, "%s\n"COL_WHITE"3. "COL_GREEN"Zresetuj pozycje", str_akc);
				Dialog_Show(playerid, CZAPKACONF, DIALOG_STYLE_LIST, ""COL_BLUE"»"COL_GREY" Czapka", str_akc, "Wybierz", "Anuluj");
			}
			else
			{
				if(IsPlayerAttachedObjectSlotUsed(playerid, CZAPKA_SLOT))
				{
					LeftNotifyShow(playerid, "error", "Mozna miec tylko ~r~jedna~w~ czapke w uzyciu.");
				}
				else 
				{
					mq_format("UPDATE `przedmioty` SET `used`='1' WHERE `id`='%d';", eq_select[playerid][s_id]);
					mysql_query(g_SQL, mQuery, false);
					LeftNotifyShow(playerid, "Sukces!", "Czapka ~g~nalozona~w~!");
					LoadUsedAccessories(playerid);
				}
			}
		}
		case 44://PUSTY KANISTER
		{
			if(IsPlayerInAnyVehicle(playerid)) return LeftNotifyShow(playerid, "error", "Nie mozesz w pojezdzie uzywac tego przedmiotu. ~r~Wysiadz z niego~w~.", LN_RED);
			/*if(IsRangeOfDistributor(playerid))
			{
				TogglePlayerControllable(playerid, false);
				StartCombineMode(playerid, 7);
			}
			else
			{
				LeftNotifyShow(playerid, "error", "Aby uzupelnic ~y~kanister~w~ musisz znajdowac sie przy sprawnym dystrybutorze.");
			}*/
			for(new s; s < MAX_FUELSTATIONS; s++)
			{
				if(IsPlayerInRangeOfPoint(playerid, 10.0, fuel_stations[s][fs_dX], fuel_stations[s][fs_dY], fuel_stations[s][fs_dZ]))
				{
					SetPVarInt(playerid, "useitem_ecan_pricePB", fuel_station_price[fuel_stations[s][fs_concern]][F_PB]*10);//10 litrów PB - cena
					SetPVarInt(playerid, "useitem_ecan_priceON", fuel_station_price[fuel_stations[s][fs_concern]][F_ON]*10);//10 litrów ON - cena
					new strRefuelCan[512];
					format(strRefuelCan, 512, ""COL_ORANGE"Paliwo\t"COL_GREEN"Cena (10 litrów)");
					format(strRefuelCan, 512, "%s\n{19BD00}» "COL_WHITE"Benzyna {19BD00}[PB]\t"COL_GREEN"%d$", strRefuelCan, GetPVarInt(playerid, "useitem_ecan_pricePB"));
					format(strRefuelCan, 512, "%s\n{7A7A7A}» "COL_WHITE"Olej napędowy {7A7A7A}[ON]\t"COL_GREEN"%d$", strRefuelCan, GetPVarInt(playerid, "useitem_ecan_priceON"));
					Dialog_Show(playerid, REFUELCAN, DIALOG_STYLE_TABLIST_HEADERS,  ""COL_RED"•» Jakie paliwo chcesz wlać do kanistra?", strRefuelCan, "Wybierz", "Anuluj");
					return 1;
				}
			}
			LeftNotifyShow(playerid, "error", "Aby uzupelnic ~y~kanister~w~ musisz znajdowac sie na stacji przy dystrybutorze (pickupie).");
		}
		case 45..46://PEŁNY KANISTER
		{
			if(IsPlayerInAnyVehicle(playerid)) return LeftNotifyShow(playerid, "error", "Nie mozesz w pojezdzie uzywac tego przedmiotu. ~r~Wysiadz z niego~w~.", LN_RED);
			new list_veh[1024];
			format(list_veh, 1024, "UID\tNazwa pojazdu");
			new detected_vehs;
			new Float:vPos[3];
			new engine, lights, alarm, doors, bonnet, boot, objective;
			new fueltype = (itemid == 45) ? (F_PB) : (F_ON); 
			SetPVarInt(playerid, "useitem_fueltype", fueltype);
			for(new v = GetVehiclePoolSize(); v != -1; v--)
			{
				if(pojazd[v][v_id])
				{
					if(pojazd[v][v_owner_type] == VEHICLE_PLAYER || pojazd[v][v_owner_type] == VEHICLE_BUSINESS)
					{
						if(GetVehicleFuelType(pojazd[v][v_model]) == fueltype)
						{
							if(pojazd[v][v_paliwo] < GetVehicleFuelSize(pojazd[v][v_model])-10)
							{
								if(IsPlayerCanDrive(playerid, v))
								{
									GetVehicleParamsEx(v, engine, lights, alarm, doors, bonnet, boot, objective);
									if(!engine)
									{
										GetVehiclePos(v, vPos[0], vPos[1], vPos[2]);
										if(IsPlayerInRangeOfPoint(playerid, 6.5, vPos[0], vPos[1], vPos[2]))
										{
											format(list_veh, 1024, "%s\n"COL_BLACK"%d\t"COL_EASY"%s", list_veh, v, GetVehicleName(pojazd[v][v_model]));
											detected_vehs++;
										}
									}
								}
							}
						}
					}
				}
			}
			if(detected_vehs)
			{
				Dialog_Show(playerid, REFUEL, DIALOG_STYLE_TABLIST_HEADERS, "Który pojazd chcesz zatankować?", list_veh, "Wybierz", "Anuluj");
			}
			else
			{
				LeftNotifyShow(playerid, "error", "Aby uzupelnic paliwo, musisz sie znajdowac przy swoim zgaszonym, niezatankwanym do pelna ~y~pojezdzie~w~. Upewnij sie, ze probujesz wlac wlasciwe paliwo.");
			}
		}
		case 47..62://żarcie
		{
			if(RemoveItemFromPlayer(playerid, itemid, 1))
			{
				gracz[playerid][stamina] += 30;
				if(gracz[playerid][stamina] > 100) gracz[playerid][stamina] = 100;
				new Float:tmpFloat;
				GetPlayerHealth(playerid, tmpFloat);
				SetPlayerHealth(playerid, tmpFloat+30);
				HUD_UpdateSTAMINA(playerid);
				mq_format("UPDATE `Konta` SET `stamina`='%d' WHERE `id`='%d';", gracz[playerid][stamina], gracz[playerid][UID]);
				mq_send("QUpdateStamina");
				LeftNotifyShow(playerid, "Stamina", "Stamina i HP zostalo czesciowo zregenerowane.", LN_GREEN);
			}
		}
		case 63://uszczelniacz do chłodnic
		{
			if(IsPlayerInAnyVehicle(playerid)) return LeftNotifyShow(playerid, "error", "Nie mozesz w pojezdzie uzywac tego przedmiotu. ~r~Wysiadz z niego~w~.", LN_RED);
			new list_veh[1024];
			format(list_veh, 1024, "UID\tNazwa pojazdu");
			new detected_vehs;
			new Float:vPos[3];
			new engine, lights, alarm, doors, bonnet, boot, objective;
			for(new v = GetVehiclePoolSize(); v != -1; v--)
			{
				if(pojazd[v][v_id])
				{
					if(pojazd[v][v_owner_type] == VEHICLE_PLAYER || pojazd[v][v_owner_type] == VEHICLE_BUSINESS)
					{
						if(pojazd[v][v_damages_lifetime_km][15] >= VehicleDamages[15][vd_exp_km])
						{
							if(IsPlayerCanDrive(playerid, v))
							{
								GetVehicleParamsEx(v, engine, lights, alarm, doors, bonnet, boot, objective);
								if(!engine)
								{
									GetVehiclePos(v, vPos[0], vPos[1], vPos[2]);
									if(IsPlayerInRangeOfPoint(playerid, 6.5, vPos[0], vPos[1], vPos[2]))
									{
										format(list_veh, 1024, "%s\n"COL_BLACK"%d\t"COL_EASY"%s", list_veh, v, GetVehicleName(pojazd[v][v_model]));
										detected_vehs++;
									}
								}
							}
						}
					}
				}
			}
			if(detected_vehs)
			{
				Dialog_Show(playerid, UNTEMPV, DIALOG_STYLE_TABLIST_HEADERS, "Na którym pojeździe użyć?", list_veh, "Wybierz", "Anuluj");
			}
			else
			{
				LeftNotifyShow(playerid, "error", "Aby uzyc przedmiotu, musisz sie znajdowac przy zgaszonym pojezdzie. Pojazd musi miec uszkodzona chlodnice.");
			}
		}
		case 64://kołki do opon
		{
			if(IsPlayerInAnyVehicle(playerid)) return LeftNotifyShow(playerid, "error", "Nie mozesz w pojezdzie uzywac tego przedmiotu. ~r~Wysiadz z niego~w~.", LN_RED);
			new list_veh[1024];
			format(list_veh, 1024, "UID\tNazwa pojazdu");
			new detected_vehs;
			new Float:vPos[3];
			new engine, lights, alarm, doors, bonnet, boot, objective;
			for(new v = GetVehiclePoolSize(); v != -1; v--)
			{
				if(pojazd[v][v_id])
				{
					if(pojazd[v][v_owner_type] == VEHICLE_PLAYER || pojazd[v][v_owner_type] == VEHICLE_BUSINESS)
					{
						if(pojazd[v][v_damages_lifetime_km][0] >= VehicleDamages[0][vd_exp_km])
						{
							if(IsPlayerCanDrive(playerid, v))
							{
								GetVehicleParamsEx(v, engine, lights, alarm, doors, bonnet, boot, objective);
								if(!engine)
								{
									GetVehiclePos(v, vPos[0], vPos[1], vPos[2]);
									if(IsPlayerInRangeOfPoint(playerid, 6.5, vPos[0], vPos[1], vPos[2]))
									{
										format(list_veh, 1024, "%s\n"COL_BLACK"%d\t"COL_EASY"%s", list_veh, v, GetVehicleName(pojazd[v][v_model]));
										detected_vehs++;
									}
								}
							}
						}
					}
				}
			}
			if(detected_vehs)
			{
				Dialog_Show(playerid, UNTIRESV, DIALOG_STYLE_TABLIST_HEADERS, "Na którym pojeździe użyć?", list_veh, "Wybierz", "Anuluj");
			}
			else
			{
				LeftNotifyShow(playerid, "error", "Aby uzyc przedmiotu, musisz sie znajdowac przy zgaszonym pojezdzie. Pojazd musi miec uszkodzona opone.");
			}
		}
		case 65..72://Browar
		{
			if(IsPlayerInAnyVehicle(playerid)) return Error(playerid, "Nie można tego przedmiotu używać w pojeździe.");
			if(RemoveItemFromPlayer(playerid, itemid, 1))
			{
				gracz[playerid][drunk_remove_tick] = 20;
				gracz[playerid][last_drinkuse] = itemid;
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
				LeftNotifyShow(playerid, "info", "Wcisnij ~y~LPM~w~ aby spozyc alkohol. Aby przestac wcisnij ~r~ENTER~w~.");
			}
		}
		case 73..75://Whisky
		{
			if(IsPlayerInAnyVehicle(playerid)) return Error(playerid, "Nie można tego przedmiotu używać w pojeździe.");
			if(RemoveItemFromPlayer(playerid, itemid, 1))
			{
				gracz[playerid][drunk_remove_tick] = 14;
				gracz[playerid][last_drinkuse] = itemid;
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
				LeftNotifyShow(playerid, "info", "Wcisnij ~y~LPM~w~ aby spozyc alkohol. Aby przestac wcisnij ~r~ENTER~w~.");
			}
		}
		case 76..78://wóda
		{
			if(IsPlayerInAnyVehicle(playerid)) return Error(playerid, "Nie można tego przedmiotu używać w pojeździe.");
			if(RemoveItemFromPlayer(playerid, itemid, 1))
			{
				gracz[playerid][drunk_remove_tick] = 10;
				gracz[playerid][last_drinkuse] = itemid;
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
				LeftNotifyShow(playerid, "info", "Wcisnij ~y~LPM~w~ aby spozyc alkohol. Aby przestac wcisnij ~r~ENTER~w~.");
			}
		}
		case 79://wedka
		{
			LeftNotifyShow(playerid, "info", "Wcisnij ~y~PPM~w~ w miejscu przeznaczonym do wedkowania.");
		}
		case 80://surowa ryba
		{
			new owner_campfire;
			if(InRangeOfAnyCampfire(playerid, owner_campfire))
			{
				if(RemoveItemFromPlayer(playerid, itemid, 1))
				{
					CreateItemForPlayer(playerid, 81, 1);
					LeftNotifyShow(playerid, "Sukces!", "Ryba upieczona! Mozesz ja spozyc lub sprzedac dla rybaka w Bayside.", LN_GREEN);
				}
			}
			else
			{
				LeftNotifyShow(playerid, "error", "Surowa ryba ~r~nie nadaje sie do zjedzenia~w~. Mozesz ja przygotowac na ognisku. Kitstart dostaniesz w sklepie. Mozesz ja rowniesz sprzedac dla handalrza w Bayside.", LN_RED, 30);
			}
		}
		case 81://upieczona ryba
		{
			if(RemoveItemFromPlayer(playerid, itemid, 1))
			{
				gracz[playerid][stamina] += 100;
				if(gracz[playerid][stamina] > 100) gracz[playerid][stamina] = 100;
				SetPlayerHealth(playerid, 100.0);
				HUD_UpdateSTAMINA(playerid);
				mq_format("UPDATE `Konta` SET `stamina`='%d' WHERE `id`='%d';", gracz[playerid][stamina], gracz[playerid][UID]);
				mq_send("QUpdateStamina");
				LeftNotifyShow(playerid, "Stamina", "Stamina i HP zostalo w calosci zregenerowane.", LN_GREEN);
			}
		}
		case 82://KitStart: Ognisko
		{
			if(CreateCampfire(playerid))
			{
				if(RemoveItemFromPlayer(playerid, itemid, 1))
				{
					LeftNotifyShow(playerid, "info", "Ognisko jest rozpalane. Oddal sie aby przerwac. Mozesz cos na nim przygotowac, gdy sie rozpali.", LN_GREY, 30);
				}
			}
			else Error(playerid, "Możesz mieć maksymalnie tylko jedno ognisko rozpalone.");
		}
		default:
		{
			LeftNotifyShow(playerid, "error", "Tego przedmiotu ~r~nie da sie uzyc~w~.", LN_RED);
		}
	}
	return 1;
}
//********************************************************************************************************************************************************ŁADOWANIE UŻYWANYCH PRZEDMIOTÓW
//AKCESORIA
stock LoadUsedAccessories(playerid)
{
	RemovePlayerAttachedObject(playerid, BANDANA_SLOT);
	RemovePlayerAttachedObject(playerid, OKULARY_SLOT);
	RemovePlayerAttachedObject(playerid, CZAPKA_SLOT);
	mq_format("SELECT `itemid` FROM `przedmioty` WHERE (`itemid`>='1' AND `itemid`<='43') AND `userid`='%d' AND `used`='1' LIMIT 0,3;", gracz[playerid][UID]);
	mq_send("QAkcesoria", "d", playerid);
	return 1;
}

stock RemoveUsedAccessories(playerid)
{
	if(IsPlayerAttachedObjectSlotUsed(playerid, BANDANA_SLOT)) RemovePlayerAttachedObject(playerid, BANDANA_SLOT);
	if(IsPlayerAttachedObjectSlotUsed(playerid, OKULARY_SLOT)) RemovePlayerAttachedObject(playerid, OKULARY_SLOT);
	if(IsPlayerAttachedObjectSlotUsed(playerid, CZAPKA_SLOT)) RemovePlayerAttachedObject(playerid, CZAPKA_SLOT);
	return 1;
}

forward QAkcesoria(playerid);
public QAkcesoria(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new i;
		new t_itemid;
		while(i < rekordy)
		{
			cache_get_value_name_int(i, "itemid", t_itemid);
			AkcesoriaSet(playerid, t_itemid);
			i++;
		}
	}
	return 1;
}

stock AkcesoriaSet(playerid, item_id)
{
	//typ: 1 - bandany, 2 - okulary, 3 - czapki
	new typ;
	switch(item_id)
	{
		case 1..4: typ = 1;
		case 5..30: typ = 2;
		case 31..43: typ = 3;
	}
	mq_format("SELECT * FROM `akcesoria` WHERE `type`='%d' AND `userid`='%d' LIMIT 0,1;", typ, gracz[playerid][UID]);
	mq_send("QSetAkcesoria", "ddd", playerid, ObjectItem[item_id], typ);
	return 1;
}

forward QSetAkcesoria(playerid, model, typ);
public QSetAkcesoria(playerid, model, typ)
{
	mq_getdata();
	new aslot;
	new i;
	/*ao[playerid][aslot][ao_x] = 
	ao[playerid][aslot][ao_y] =  
	ao[playerid][aslot][ao_z] =  
	ao[playerid][aslot][ao_rx] = 
	ao[playerid][aslot][ao_ry] = 
	ao[playerid][aslot][ao_rz] = 
	ao[playerid][aslot][ao_sx] = 
	ao[playerid][aslot][ao_sy] = 
	ao[playerid][aslot][ao_sz] = 
	ao[playerid][aslot][ao_typ] = */
	switch(typ)
	{
		case 1: 
		{
			aslot = BANDANA_SLOT;
			ao[playerid][aslot][ao_x] = 0.078534;
			ao[playerid][aslot][ao_y] = 0.041857;
			ao[playerid][aslot][ao_z] = -0.001727;
			ao[playerid][aslot][ao_rx] = 268.970458;
			ao[playerid][aslot][ao_ry] = 1.533374;
			ao[playerid][aslot][ao_rz] = 269.223754;
			ao[playerid][aslot][ao_sx] = 1.0;
			ao[playerid][aslot][ao_sy] = 1.0;
			ao[playerid][aslot][ao_sz] = 1.0;
		}
		case 2:
		{
			aslot = OKULARY_SLOT;
			ao[playerid][aslot][ao_x] = 0.093999;
			ao[playerid][aslot][ao_y] = 0.036000;
			ao[playerid][aslot][ao_z] = 0.003000;
			ao[playerid][aslot][ao_rx] = 0.000000;
			ao[playerid][aslot][ao_ry] = 84.600028;
			ao[playerid][aslot][ao_rz] = 91.200012;
			ao[playerid][aslot][ao_sx] = 1.0;
			ao[playerid][aslot][ao_sy] = 1.0;
			ao[playerid][aslot][ao_sz] = 1.0;
		} 
		case 3: 
		{
			aslot = CZAPKA_SLOT;
			if(model == 18953 || model == 18954)
			{
				ao[playerid][aslot][ao_x] = 0.112000;
				ao[playerid][aslot][ao_y] = 0.019999;
				ao[playerid][aslot][ao_z] = 0.000000;
				ao[playerid][aslot][ao_rx] = 0.000000;
				ao[playerid][aslot][ao_ry] = 0.000000;
				ao[playerid][aslot][ao_rz] = 0.000000;
			}
			else if(model == 18939 || model == 18940 || model == 18941 || model == 18942 || model == 18943)
			{
				ao[playerid][aslot][ao_x] = 0.157999;
				ao[playerid][aslot][ao_y] =  0.000000;
				ao[playerid][aslot][ao_z] =  0.000000;
				ao[playerid][aslot][ao_rx] = -171.599945;
				ao[playerid][aslot][ao_ry] = 0.000000;
				ao[playerid][aslot][ao_rz] = 0.000000;
			}
			else if(18951 >= model >= 18946)//kapelusze
			{
				ao[playerid][aslot][ao_x] = 0.112000;
				ao[playerid][aslot][ao_y] = 0.019999;
				ao[playerid][aslot][ao_z] = 0.000000;
				ao[playerid][aslot][ao_rx] = 0.000000;
				ao[playerid][aslot][ao_ry] = 0.000000;
				ao[playerid][aslot][ao_rz] = 0.000000;
			}
			ao[playerid][aslot][ao_sx] = 1.0;
			ao[playerid][aslot][ao_sy] = 1.0;
			ao[playerid][aslot][ao_sz] = 1.0;
		}
	}
	ao[playerid][aslot][ao_typ] = typ;
	if(rekordy)
	{
		cache_get_value_name_float(0, "ao_x", 		ao[playerid][aslot][ao_x]);
		cache_get_value_name_float(0, "ao_y", 		ao[playerid][aslot][ao_y]);
		cache_get_value_name_float(0, "ao_z", 		ao[playerid][aslot][ao_z]);
		cache_get_value_name_float(0, "ao_rx", 		ao[playerid][aslot][ao_rx]);
		cache_get_value_name_float(0, "ao_ry", 		ao[playerid][aslot][ao_ry]);
		cache_get_value_name_float(0, "ao_rz", 		ao[playerid][aslot][ao_rz]);
		cache_get_value_name_float(0, "ao_sx", 		ao[playerid][aslot][ao_sx]);
		cache_get_value_name_float(0, "ao_sy", 		ao[playerid][aslot][ao_sy]);
		cache_get_value_name_float(0, "ao_sz", 		ao[playerid][aslot][ao_sz]);
		i = aslot;
		SetPlayerAttachedObject(playerid, aslot, model, 2, ao[playerid][i][ao_x], ao[playerid][i][ao_y], ao[playerid][i][ao_z], ao[playerid][i][ao_rx], ao[playerid][i][ao_ry], ao[playerid][i][ao_rz], ao[playerid][i][ao_sx], ao[playerid][i][ao_sy], ao[playerid][i][ao_sz]);
		//EditAttachedObject(playerid, i);
	}
	else 
	{
		i = aslot;
		SetPlayerAttachedObject(playerid, aslot, model, 2, ao[playerid][i][ao_x], ao[playerid][i][ao_y], ao[playerid][i][ao_z], ao[playerid][i][ao_rx], ao[playerid][i][ao_ry], ao[playerid][i][ao_rz], ao[playerid][i][ao_sx], ao[playerid][i][ao_sy], ao[playerid][i][ao_sz]);
		mq_format("INSERT INTO `akcesoria` VALUES (NULL, '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f');", gracz[playerid][UID], typ, ao[playerid][i][ao_x], ao[playerid][i][ao_y], ao[playerid][i][ao_z], ao[playerid][i][ao_rx], ao[playerid][i][ao_ry], ao[playerid][i][ao_rz], ao[playerid][i][ao_sx], ao[playerid][i][ao_sy], ao[playerid][i][ao_sz]);
		mq_send("QInsertAkcesoria");
	}
	return 1;
}

Dialog:BANDANACONF(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			mq_format("UPDATE `przedmioty` SET `used`='0' WHERE `id`='%d';", eq_select[playerid][s_id]);
			mysql_query(g_SQL, mQuery, false);
			LeftNotifyShow(playerid, "Sukces!", "Bandana zdjeta.");
			RemovePlayerAttachedObject(playerid, BANDANA_SLOT);
		}
		case 1:
		{
			ao[playerid][BANDANA_SLOT][ao_typ] = 1;
			EditAttachedObject(playerid, BANDANA_SLOT);
		}
		case 2:
		{
			mq_format("DELETE FROM `akcesoria` WHERE `userid`='%d' AND `type`='1';", gracz[playerid][UID]);
			mq_send("QAkcesoriaReset", "d", playerid);
		}
	}
 	return 1;
}

Dialog:OKULARYCONF(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			mq_format("UPDATE `przedmioty` SET `used`='0' WHERE `id`='%d';", eq_select[playerid][s_id]);
			mysql_query(g_SQL, mQuery, false);
			LeftNotifyShow(playerid, "Sukces!", "Okulary zdjete.");
			RemovePlayerAttachedObject(playerid, OKULARY_SLOT);
		}
		case 1:
		{
			ao[playerid][OKULARY_SLOT][ao_typ] = 2;
			EditAttachedObject(playerid, OKULARY_SLOT);
		}
		case 2:
		{
			mq_format("DELETE FROM `akcesoria` WHERE `userid`='%d' AND `type`='2';", gracz[playerid][UID]);
			mq_send("QAkcesoriaReset", "d", playerid);
		}
	}
 	return 1;
}

Dialog:CZAPKACONF(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			mq_format("UPDATE `przedmioty` SET `used`='0' WHERE `id`='%d';", eq_select[playerid][s_id]);
			mysql_query(g_SQL, mQuery, false);
			LeftNotifyShow(playerid, "Sukces!", "Czapka zdjeta.");
			RemovePlayerAttachedObject(playerid, CZAPKA_SLOT);
		}
		case 1:
		{
			ao[playerid][CZAPKA_SLOT][ao_typ] = 3;
			EditAttachedObject(playerid, CZAPKA_SLOT);
			SendClientMessage(playerid, -1, "(("COL_GREY"Wskazówka: Wciśnij spację, aby móc manewrować kamerą"COL_WHITE"))");
		}
		case 2:
		{
			mq_format("DELETE FROM `akcesoria` WHERE `userid`='%d' AND `type`='3';", gracz[playerid][UID]);
			mq_send("QAkcesoriaReset", "d", playerid);
		}
	}
 	return 1;
}


forward QAkcesoriaReset(playerid);
public QAkcesoriaReset(playerid)
{
	LoadUsedAccessories(playerid);
	return 1;
}
//PUSTY KANISTER
Dialog:REFUELCAN(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItems(playerid);
	new fuelcan_price = 1000;
	new canid = 45;
	switch(listitem)
	{
		case 0://Benzyna PB
		{
			canid = 45;
			fuelcan_price = GetPVarInt(playerid, "useitem_ecan_pricePB");
		}
		case 1://Olej Napędowy ON
		{
			canid = 46;
			fuelcan_price = GetPVarInt(playerid, "useitem_ecan_priceON");
		}
	}
	if(fuelcan_price > Money(playerid)) return Error(playerid, "Niewystarczająca ilość gotówki.");
	if(RemoveItemFromPlayer(playerid, 44, 1))
	{
		CreateItemForPlayer(playerid, canid, 1);
		TakeMoney(playerid, fuelcan_price);
		new strCommand[144];
		format(strCommand, 144, "/me uzupełnia kanister.");
		PC_EmulateCommand(playerid, strCommand);
	}
	return 1;
}

//PEŁNY KANISTER
Dialog:REFUEL(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItems(playerid);
	new v = strval(inputtext);
	new Float:vPos[3];
	new fueltype = GetPVarInt(playerid, "useitem_fueltype");
	new canid = (fueltype == F_PB) ? (45) : (46);
	if(pojazd[v][v_id])
	{
		if(pojazd[v][v_owner_type] == VEHICLE_PLAYER || pojazd[v][v_owner_type] == VEHICLE_BUSINESS)
		{
			if(GetVehicleFuelType(pojazd[v][v_model]) == fueltype)
			{
				if(pojazd[v][v_paliwo] < GetVehicleFuelSize(pojazd[v][v_model])-10)
				{
					if(IsPlayerCanDrive(playerid, v))
					{
						GetVehiclePos(v, vPos[0], vPos[1], vPos[2]);
						if(IsPlayerInRangeOfPoint(playerid, 6.5, vPos[0], vPos[1], vPos[2]))
						{
							if(RemoveItemFromPlayer(playerid, canid, 1))
							{
								CreateItemForPlayer(playerid, 44, 1);
								pojazd[v][v_paliwo] += 10.0;
								if(pojazd[v][v_id] != 0)
								{
									mq_format("UPDATE `pojazdy` SET `paliwo`='%f' WHERE `id`='%d';", pojazd[v][v_paliwo], pojazd[v][v_id]);
									mq_send("QUpdatePaliwo");
								}
								new strCommand[144];
								format(strCommand, 144, "/me wlewa paliwo z kanistra do %s.", GetVehicleName(pojazd[v][v_model]));
								PC_EmulateCommand(playerid, strCommand);
								if(pojazd[v][v_owner_type] == VEHICLE_BUSINESS)
								{
									if(fueltype == F_PB) LogCompany(gracz[playerid][firma], gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_POJAZD, "Zatankowal 10L (PB) - kanister. Pojazd: %s(UID: %d)", GetVehicleName(pojazd[v][v_model]), pojazd[v][v_id]);
									else if(fueltype == F_ON) LogCompany(gracz[playerid][firma], gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_POJAZD, "Zatankowal 10L (ON) - kanister. Pojazd: %s(UID: %d)", GetVehicleName(pojazd[v][v_model]), pojazd[v][v_id]);
								}
							}
						}
					}
				}
			}
		}
	}
	return 1;
}
//USZCZELNIACZ DO CHŁODNIC
Dialog:UNTEMPV(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItems(playerid);
	new v = strval(inputtext);
	new Float:vPos[3];
	if(pojazd[v][v_id])
	{
		if(pojazd[v][v_owner_type] == VEHICLE_PLAYER || pojazd[v][v_owner_type] == VEHICLE_BUSINESS)
		{
			if(pojazd[v][v_damages_lifetime_km][15] >= VehicleDamages[15][vd_exp_km])
			{
				if(IsPlayerCanDrive(playerid, v))
				{
					GetVehiclePos(v, vPos[0], vPos[1], vPos[2]);
					if(IsPlayerInRangeOfPoint(playerid, 6.5, vPos[0], vPos[1], vPos[2]))
					{
						if(RemoveItemFromPlayer(playerid, 63, 1))
						{
							new strCommand[144];
							format(strCommand, 144, "/me wlewa uszczelniacz do %s.", GetVehicleName(pojazd[v][v_model]));
							PC_EmulateCommand(playerid, strCommand);
							pojazd[v][v_damages_lifetime_km][15] = VehicleDamages[15][vd_exp_km]-100;
							format(pojazd[v][v_damages_lifetime_strdata], 256, "");//czyszczenie zmiennej
							SetVehicleHealth(v, 1000.0);
							for(new x; x < MAX_VEHICLEDAMAGES; x++)
							{
								pojazd[v][v_damages_lifetime_km][x]++;
								if(IsVehicleBike(pojazd[v][v_model]) && (x == 1 || x == 2)) pojazd[v][v_damages_lifetime_km][x] = 0;
								format(pojazd[v][v_damages_lifetime_strdata], 256, "%s%d ", pojazd[v][v_damages_lifetime_strdata], pojazd[v][v_damages_lifetime_km][x]);
							}
							if(pojazd[v][v_id] != 0)
							{
								mq_format("UPDATE `pojazdy` SET `przebieg`='%d', `przebiegunits`='%d', `paliwo`='%f', `eksploatacja`='%s', `hp`='1000.0' WHERE `id`='%d';", pojazd[v][v_przebieg], floatround(pojazd[v][v_przebiegunits]), pojazd[v][v_paliwo], pojazd[v][v_damages_lifetime_strdata], pojazd[v][v_id]);
								mq_send("QUpdateVehicle");
							}
							Info(playerid, "Udało się na pewien czas uszczelnić chłodnice. Odwiedź jak najszybciej warsztat i napraw ją!");
							if(pojazd[v][v_owner_type] == VEHICLE_BUSINESS)
							{
								LogCompany(gracz[playerid][firma], gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_POJAZD, "Uszczelniacz do chlodnic. Pojazd: %s(UID: %d)", GetVehicleName(pojazd[v][v_model]), pojazd[v][v_id]);
							}
						}
					}
				}
			}
			else Error(playerid, "Nie możesz wlać uszczelniacza, podczas kiedy chłodnica jest sprawna.");
		}
	}
	return 1;
}


Dialog:UNTIRESV(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItems(playerid);
	new v = strval(inputtext);
	new Float:vPos[3];
	if(pojazd[v][v_id])
	{
		if(pojazd[v][v_owner_type] == VEHICLE_PLAYER || pojazd[v][v_owner_type] == VEHICLE_BUSINESS)
		{
			if(pojazd[v][v_damages_lifetime_km][0] >= VehicleDamages[0][vd_exp_km])
			{
				if(IsPlayerCanDrive(playerid, v))
				{
					GetVehiclePos(v, vPos[0], vPos[1], vPos[2]);
					if(IsPlayerInRangeOfPoint(playerid, 6.5, vPos[0], vPos[1], vPos[2]))
					{
						if(RemoveItemFromPlayer(playerid, 64, 1))
						{
							new strCommand[144];
							format(strCommand, 144, "/me kołkuje opone w %s.", GetVehicleName(pojazd[v][v_model]));
							PC_EmulateCommand(playerid, strCommand);
							pojazd[v][v_damages_lifetime_km][0] = VehicleDamages[0][vd_exp_km]-150;
							format(pojazd[v][v_damages_lifetime_strdata], 256, "");//czyszczenie zmiennej
							GetVehicleDamageStatus(v, pojazd[v][v_uvds_panels], pojazd[v][v_uvds_doors], pojazd[v][v_uvds_lights], pojazd[v][v_uvds_tires]);
							UpdateVehicleDamageStatus(v, pojazd[v][v_uvds_panels], pojazd[v][v_uvds_doors], pojazd[v][v_uvds_lights], 0);
							for(new x; x < MAX_VEHICLEDAMAGES; x++)
							{
								pojazd[v][v_damages_lifetime_km][x]++;
								if(IsVehicleBike(pojazd[v][v_model]) && (x == 1 || x == 2)) pojazd[v][v_damages_lifetime_km][x] = 0;
								format(pojazd[v][v_damages_lifetime_strdata], 256, "%s%d ", pojazd[v][v_damages_lifetime_strdata], pojazd[v][v_damages_lifetime_km][x]);
							}
							if(pojazd[v][v_id] != 0)
							{
								mq_format("UPDATE `pojazdy` SET `przebieg`='%d', `przebiegunits`='%d', `paliwo`='%f', `eksploatacja`='%s' WHERE `id`='%d';", pojazd[v][v_przebieg], floatround(pojazd[v][v_przebiegunits]), pojazd[v][v_paliwo], pojazd[v][v_damages_lifetime_strdata], pojazd[v][v_id]);
								mq_send("QUpdateVehicle");
							}
							Info(playerid, "Udało się na pewien czas zakołkować opony. Odwiedź jak najszybciej warsztat i napraw je!");
							if(pojazd[v][v_owner_type] == VEHICLE_BUSINESS)
							{
								LogCompany(gracz[playerid][firma], gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_POJAZD, "Zakołkowane opony. Pojazd: %s(UID: %d)", GetVehicleName(pojazd[v][v_model]), pojazd[v][v_id]);
							}
						}
					}
				}
			}
			else Error(playerid, "Opony nie są uszkodzone.");
		}
	}
	return 1;
}
//alkohol
stock Event_DrunkAlcohol(playerid)
{
	new special_action = GetPlayerSpecialAction(playerid);
	if(special_action == SPECIAL_ACTION_DRINK_WINE || special_action == SPECIAL_ACTION_DRINK_BEER)
	{
		if(gracz[playerid][timestamp_lastdrunk]+3 > serwer[time_timestamp]) return 1;
		if(gracz[playerid][drunk_remove_tick] > 0)
		{
			if(gracz[playerid][last_drinkuse] >= 65 && gracz[playerid][last_drinkuse] <= 72)//browar
			{
				if(gracz[playerid][when_tipsy] == 0)//zaczyna pic (pierwszy lyk)
				{
					gracz[playerid][when_tipsy] += 2100;
				}
				else
				{
					if(gracz[playerid][when_tipsy] < 4000) gracz[playerid][when_tipsy] += 250;
				}
				SetPlayerDrunkLevel(playerid, gracz[playerid][when_tipsy]);
			}
			else if(gracz[playerid][last_drinkuse] >= 73 && gracz[playerid][last_drinkuse] <= 75)//whisky
			{
				if(gracz[playerid][when_tipsy] == 0)//zaczyna pic (pierwszy lyk)
				{
					gracz[playerid][when_tipsy] += 2100;
				}
				else
				{
					if(gracz[playerid][when_tipsy] < 10000) gracz[playerid][when_tipsy] += 250;
				}
				SetPlayerDrunkLevel(playerid, gracz[playerid][when_tipsy]);
			}
			else if(gracz[playerid][last_drinkuse] >= 76 && gracz[playerid][last_drinkuse] <= 78)//wóda
			{
				if(gracz[playerid][when_tipsy] == 0)//zaczyna pic (pierwszy lyk)
				{
					gracz[playerid][when_tipsy] += 2100;
				}
				else
				{
					if(gracz[playerid][when_tipsy] < 16000) gracz[playerid][when_tipsy] += 400;
				}
				SetPlayerDrunkLevel(playerid, gracz[playerid][when_tipsy]);
			}
			gracz[playerid][drunk_remove_tick]--;
			new strGameText[24];
			format(strGameText, 24, "Pozostalo: ~r~%d", gracz[playerid][drunk_remove_tick]);
			GameTextForPlayer(playerid, strGameText, 1500, 3);
			gracz[playerid][timestamp_lastdrunk] = serwer[time_timestamp];
			if(gracz[playerid][drunk_remove_tick] <= 0)
			{
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				LeftNotifyShow(playerid, "info", "Skonczyl sie alkohol.");
			}
		}
		else 
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			LeftNotifyShow(playerid, "info", "Skonczyl sie alkohol.");
		}
	}
	return 1;
}

task Process_DrunkLevel(playerid)
{
	if(gracz[playerid][when_tipsy] > 0)
	{
		gracz[playerid][when_tipsy] -= 5;
		if(gracz[playerid][when_tipsy] < 1900) gracz[playerid][when_tipsy] = 0;
		SetPlayerDrunkLevel(playerid, gracz[playerid][when_tipsy]);
		if(gracz[playerid][when_tipsy] == 0)
		{
			LeftNotifyShow(playerid, "info", "Wytrzezwiales.");
		} 
	} 
	return 1;
}
