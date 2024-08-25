/*
sprzedawanie naczep?
*/
#define CLOGFLAG_KURS 1
#define CLOGFLAG_BANK 2
#define CLOGFLAG_WYDATEK 3
#define CLOGFLAG_POJAZD 4

enum cnt_data
{
	cnt_goodid,
	cnt_fromid,
	cnt_targetid,
	Float:cnt_size,
	cnt_price,
	cnt_penalty,
	cnt_score,
	cnt_time,
	Float:cnt_distance
};

new contract[MAX_CONTRACTS][cnt_data];

stock RotateCompanyContracts()
{
	new random_cargo;
	new rand_sourceid;
	for(new c; c < MAX_CONTRACTS; c++)
	{
		random_cargo = random(sizeof(goods));
		if(random_cargo == 0 || random_cargo == 1) random_cargo = 2;
		contract[c][cnt_goodid] = random_cargo;
		//wytyczanie trasy
		rand_sourceid = random(MAX_VANLOADS);
		contract[c][cnt_fromid] = rand_sourceid;//losowe źródło
		//szukanie odpowiednio daleko celu:
		new potential_destinations[MAX_VANLOADS];
		new pd_counter;
		for(new d; d < MAX_VANLOADS; d++)
		{
			if(GetDistanceBetweenPoints(load_place_van[d][0], load_place_van[d][1], load_place_van[d][2], load_place_van[rand_sourceid][0], load_place_van[rand_sourceid][1], load_place_van[rand_sourceid][2]) > 5000.0)
			{
				potential_destinations[pd_counter] = d;
				pd_counter++;
			}
		}
		pd_counter--;
		new random_pd =  random(pd_counter);
		contract[c][cnt_targetid] = potential_destinations[random_pd];
		//wytycznie trasy - end
		//-> -> -> RCC_OnCalculatePath -> -> ->
		new Float:tempFrom[3];
		tempFrom[0] = load_place_van[contract[c][cnt_fromid]][0];
		tempFrom[1] = load_place_van[contract[c][cnt_fromid]][1];
		tempFrom[2] = load_place_van[contract[c][cnt_fromid]][2];
		new Float:tempTarget[3];
		tempTarget[0] = load_place_van[contract[c][cnt_targetid]][0];
		tempTarget[1] = load_place_van[contract[c][cnt_targetid]][1];
		tempTarget[2] = load_place_van[contract[c][cnt_targetid]][2];
		RGPS_CalculatePath(tempFrom[0], tempFrom[1], tempFrom[2], tempTarget[0], tempTarget[1], tempTarget[2], c+30000, 0);
		//-> -> -> RCC_OnCalculatePath -> -> -> 
	}
	return 1;
}

stock RCC_OnCalculatePath(c, Float:distance)
{
	//testy: 40 km to ok 360 sekund (6 minut), czyli 9 sekund na km
	contract[c][cnt_distance] = distance/CONST_KM;
	new Float:calc_size = float(MRandRange(3000000, 6500000))-(contract[c][cnt_distance]*24000.0);
	new Float:time_calc = ((calc_size/30000.0)*contract[c][cnt_distance])*float(MRandRange(40, 80));//przeliczanie czasu
	contract[c][cnt_time] = floatround(time_calc);
	new Float:calc_price = ((contract[c][cnt_distance]*PRICE_FOR_KM_TRANSPORT_COMP)+(calc_size*PRICE_FOR_WEIGHT_TRANSPORT_COMP));
	if(goods[contract[c][cnt_goodid]][gds_adr]) calc_price += calc_size*PRICE_ADR_BONUS_COMP;//premia adr
	contract[c][cnt_price] = floatround(calc_price);
	const Float:penalty_proc = 85.0;
	new Float:final_penalty = penalty_proc*float(contract[c][cnt_price])/100.0;
	contract[c][cnt_penalty] = floatround(final_penalty);
	contract[c][cnt_size] = calc_size;
	new Float:calc_score = calc_size/999000.0;//ile score za ilosc towaru
	if(calc_score < 1.0) calc_score = 1.0;
	contract[c][cnt_score] = floatround(calc_score)+random(3);
	return 1;
}

stock Init_Company()
{
	RotateCompanyContracts();
	mq_format("SELECT * FROM `firmy`;");
	mq_send("LoadCompanyFromDB");
	return 1;
}

task LoadCompanyFromDB()
{
	mq_getdata();
	new i;
	if(rekordy)
	{
		new cid;
		while(i < rekordy)
		{
			cache_get_value_name_int(i, "id", 			cid);
			cache_get_value_name(i, "name", company[cid][cny_name], 64);
			cache_get_value_name_int(i, "owner", 			company[cid][cny_owneruid]);
			cache_get_value_name_int(i, "money", 			company[cid][cny_money]);
			cache_get_value_name_int(i, "score", 			company[cid][cny_score]);
			cache_get_value_name_int(i, "expire", 			company[cid][cny_expire]);
			cache_get_value_name_float(i, "duty_x", 			company[cid][cny_dutyX]);
			cache_get_value_name_float(i, "duty_y", 			company[cid][cny_dutyY]);
			cache_get_value_name_float(i, "duty_z", 			company[cid][cny_dutyZ]);
			cache_get_value_name_float(i, "buypark_x", 			company[cid][cny_buyparkX]);
			cache_get_value_name_float(i, "buypark_y", 			company[cid][cny_buyparkY]);
			cache_get_value_name_float(i, "buypark_z", 			company[cid][cny_buyparkZ]);
			cache_get_value_name_float(i, "buypark_r", 			company[cid][cny_buyparkR]);
			cache_get_value_name_int(i, "price", 			company[cid][cny_price]);
			cache_get_value_name(i, "created", company[cid][cny_created], 32);
			cache_get_value_name_int(i, "polygon_count", 			company[cid][cny_polygoncount]);
			//ładowanie kontraktu firmy
			cache_get_value_name_int(i, "cnt_goodid", 			company[cid][cny_cnt_goodid]);
			cache_get_value_name_int(i, "cnt_fromid", 			company[cid][cny_cnt_fromid]);
			cache_get_value_name_int(i, "cnt_targetid", 			company[cid][cny_cnt_targetid]);
			cache_get_value_name_float(i, "cnt_size", 			company[cid][cny_cnt_size]);
			cache_get_value_name_float(i, "cnt_size_complet", 			company[cid][cny_cnt_size_complet]);
			cache_get_value_name_int(i, "cnt_price", 			company[cid][cny_cnt_price]);
			cache_get_value_name_int(i, "cnt_penalty", 			company[cid][cny_cnt_penalty]);
			cache_get_value_name_int(i, "cnt_score", 			company[cid][cny_cnt_score]);
			cache_get_value_name_int(i, "cnt_time", 			company[cid][cny_cnt_time]);
			cache_get_value_name_int(i, "cnt_time_left", 			company[cid][cny_cnt_time_left]);
			cache_get_value_name_float(i, "cnt_distance", 			company[cid][cny_cnt_distance]);
			cache_get_value_name_int(i, "cnt_signer_uid", 			company[cid][cny_cnt_signer_uid]);
			cache_get_value_name_int(i, "cnt_signer_sid", 			company[cid][cny_cnt_signer_sid]);
			if(company[cid][cny_polygoncount] >= 6)//minimum 3 koordy (6 danych x+y)
			{
				new sscanf_format[16];
				new zpolygons_rawdata[5000];
				new Float:zpolygons[8192];
				cache_get_value_name(i, "polygon_data", zpolygons_rawdata, 5000);
				format(sscanf_format, 16, "a<f>[%d]", 8192);
				sscanf(zpolygons_rawdata, sscanf_format, zpolygons);
				company[cid][cny_polygonid] = CreateDynamicPolygon(zpolygons, company[cid][cny_dutyZ]-10.0, company[cid][cny_dutyZ]+30.0, company[cid][cny_polygoncount], 0, 0);
			}
			i++;
		}
	}
	new strTemp[1024];
	for(new cid; cid < MAX_COMPANY; cid++)
	{
		if(company[cid][cny_price] == 0) continue;
		CreateDynamic3DTextLabel("»» !!!ZAKAZ PARKOWANIA!!! «««\n"COL_WHITE"W tym miejscu spawnują się pojazdy zakupione w salonie!\n"COL_ORANGE"Jeśli znajduje się tutaj pojazd, przeparkuj go natychmiast!"COL_WHITE"\nAby przeparkować naczepe, użyj trucka i komendy "COL_RED"/v parkuj"COL_WHITE".\nAdministracja nie ponosi odpowiedzialności za niestosowanie się do wskazówek!", 0xFF0000FF, company[cid][cny_buyparkX], company[cid][cny_buyparkY], company[cid][cny_buyparkZ]-2.0, 15.0);
		if(company[cid][cny_owneruid] != 0)
		{
			if(company[cid][cny_expire] < gettime())
			{
				//resetowanie firmy
				format(company[cid][cny_name], 64, "-brak-");
				company[cid][cny_owneruid] = 0;
				company[cid][cny_money] = 0;
				company[cid][cny_score] = 0;
				company[cid][cny_expire] = 0;
				CompanySaveData(cid);//ZAPIS (zapytanko synchronizujące RAM z polami w tabeli 'firmy')
				//wygaszanie kontraktu
				ResetCompanyContractRam(cid);
				CompanySaveDataContract(cid);
				//zwalnianie wszystkich pracowników TODO
				mq_format("UPDATE `Konta` SET `firma`='0', `firma_permlvl`='0' WHERE `firma`='%d';", cid);
				mq_send("QUpdatePlayerCompany");
				//usuwanie wszystkich firmowych pojazdów TODO
				mq_format("DELETE FROM `pojazdy` WHERE `owner_type`='%d' AND `owner`='%d';", VEHICLE_BUSINESS, cid);
				mq_send("QDelVehsCompany");
				//usuwanie logów firmy
				mq_format("DELETE FROM `LogCompany` WHERE `company_id`='%d';", cid);
				mq_send("QDelCompanyLogs");
				mq_format("DELETE FROM `LogCompanySessionDuty` WHERE `company_id`='%d';", cid);
				mq_send("QDelCompanyLogsS");
				//usuwanie pojazdów stworzonych na serwie
				for(new v = GetVehiclePoolSize(); v != -1; v--)
				{
					if(pojazd[v][v_owner_type] == VEHICLE_BUSINESS)
					{
						if(pojazd[v][v_owner] == cid)
						{
							RemoveVehicle(v);
						}
					}
				}
				//Aktualizacja daty stworzenia firmy
				mq_format("UPDATE `firmy` SET `created`=0 WHERE `id`='%d';", cid);
				mq_send("QUpdateCreateCompany", "d", cid);
			}
		}
		//wczytywanie
		if(company[cid][cny_owneruid] != 0)
		{
			company[cid][cny_pickup] = CreateDynamicPickup(1314, 1, company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ]);
			format(strTemp, 1024, ""COL_GREEN"« "COL_BLUE"SŁUŻBA W FIRMIE - "COL_RED"%s (ID: %d)"COL_GREEN"»\n", company[cid][cny_name], cid);
			format(strTemp, 1024, "%s"COL_GREEN"« "COL_YELLOW"WŁAŚCICIEL: "COL_RED"%s "COL_GREEN"»\n", strTemp, GetPlayerIGName(company[cid][cny_owneruid]));
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_ORANGE"PPM"COL_GREY" lub "COL_ORANGE"/cduty start"COL_GREY" aby rozpocząć pracę. "COL_RED"•\n", strTemp);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_ORANGE"PPM"COL_GREY" lub "COL_ORANGE"/cduty stop"COL_GREY" aby zakończyć pracę. "COL_RED"•\n", strTemp);
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
	}
	return 1;
}

stock CompanySaveData(cid)
{
	mq_format("UPDATE `firmy` SET `name`='%s', `owner`='%d', `money`='%d', `score`='%d', `expire`='%d' WHERE `id`='%d';", company[cid][cny_name], company[cid][cny_owneruid], company[cid][cny_money], company[cid][cny_score], company[cid][cny_expire], cid);
	mq_send("QCompanySave");
	return 1;
}

stock CompanySaveDataContract(cid)
{
	mq_format("UPDATE `firmy` SET `cnt_goodid`='%d', `cnt_fromid`='%d', `cnt_targetid`='%d', `cnt_size`='%f', `cnt_size_complet`='%f', `cnt_price`='%d', `cnt_penalty`='%d', `cnt_score`='%d', `cnt_time`='%d', `cnt_time_left`='%d', `cnt_distance`='%f', `cnt_signer_uid`='%d', `cnt_signer_sid`='%d' WHERE `id`='%d';", company[cid][cny_cnt_goodid], company[cid][cny_cnt_fromid], company[cid][cny_cnt_targetid], company[cid][cny_cnt_size], company[cid][cny_cnt_size_complet], company[cid][cny_cnt_price], company[cid][cny_cnt_penalty], company[cid][cny_cnt_score], company[cid][cny_cnt_time], company[cid][cny_cnt_time_left], company[cid][cny_cnt_distance], company[cid][cny_cnt_signer_uid], company[cid][cny_cnt_signer_sid], cid);
	mq_send("QCompanySaveContract");
	return 1;
}

stock ResetCompanyContractRam(cid)
{
	company[cid][cny_cnt_goodid] = 0;
	company[cid][cny_cnt_fromid] = 0;
	company[cid][cny_cnt_targetid] = 0;
	company[cid][cny_cnt_size] = 0.0;
	company[cid][cny_cnt_size_complet] =  0.0;
	company[cid][cny_cnt_price] = 0;
	company[cid][cny_cnt_penalty] = 0;
	company[cid][cny_cnt_score] = 0;
	company[cid][cny_cnt_time] = 0;
	company[cid][cny_cnt_time_left] = 0;
	company[cid][cny_cnt_distance] = 0.0;
	company[cid][cny_cnt_signer_uid] = 0;
	company[cid][cny_cnt_signer_sid] = 0;
	SendCompanyMessage(cid, "Kontrakt firmy jest już nieaktualny.");
	SendCompanyMessage(cid, "Wszystkie pojazdy zostały automatycznie rozładowane.");
	for(new v = GetVehiclePoolSize(); v != -1; v--)//usuwanie towarów z pojazdów firmowych
	{
		if(pojazd[v][v_owner_type] == VEHICLE_BUSINESS && pojazd[v][v_owner] == cid)
		{
			if(pojazd[v][v_cargo] != 0)
			{
				pojazd[v][v_cargo] = 0;
				pojazd[v][v_cargo_amount] = 0;
				pojazd[v][v_cargo_score] = 0;
				pojazd[v][v_cargo_distance] = 0.0;
				pojazd[v][v_cargo_target_X] = 0.0;
				pojazd[v][v_cargo_target_Y] = 0.0;
				pojazd[v][v_cargo_target_Z] = 0.0;
			}
		}
	}
	for(new p = PlayerPoolSize(); p != -1; p--)//ukyrwanie td z towarem
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][firma] == cid)
			{
				CargoInfo_Hide(p);
				ClearObjective(p);
			}
		}
	}
	return 1;
}

stock CompanySaveMoney(cid)
{
	mq_format("UPDATE `firmy` SET `money`='%d' WHERE `id`='%d';", company[cid][cny_money], cid);
	mq_send("QCompanySaveMoney");
	return 1;
}

stock PlayerCompanyCash(playerid)
{
	if(IsPlayerOnDutyCompany(playerid))
	{
		new cid = gracz[playerid][firma];
		return company[cid][cny_money];
	} 
	return -1;
}

stock CompanyWorkersCount(companyid)
{
	mq_format("SELECT `firma` FROM `Konta` WHERE `firma`='%d';", companyid);
	new Cache:count_query = mysql_query(g_SQL, mQuery);
	new wynik = cache_get_row_count_ex();
	cache_delete(count_query);
	return wynik;
}

stock CompanyVehiclesCount(companyid)
{
	new wynik;
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		if(pojazd[v][v_owner_type] == VEHICLE_BUSINESS)
		{
			if(pojazd[v][v_owner] == companyid) wynik++;
		}
	}
	return wynik;
}

stock PosRangeOfCompany(companyid, Float:cX, Float:cY, Float:cZ)
{
	if(GetDistanceBetweenPoints(cX, cY, cZ, company[companyid][cny_dutyX], company[companyid][cny_dutyY], company[companyid][cny_dutyZ]) < RANGE_COMPANY) return 1;
	return 0;
}

stock SavePlayerCompanyData(playerid)
{
	if(!gracz[playerid][loggedin]) return 0;
	mq_format("UPDATE `Konta` SET `firma`='%d', `firma_permlvl`='%d', `firma_wyplata`='%d', `firma_kontrakt_kg`='%d' WHERE `id`='%d';", gracz[playerid][firma], gracz[playerid][firma_permlvl], gracz[playerid][firma_wyplata], gracz[playerid][firma_kontrakt_kg], gracz[playerid][UID]);
	mq_send("QUpdatePlayerCompanyData");
	return 1;
}

stock IsPlayerOnDutyCompany(playerid)
{
	if(gracz[playerid][firma] == 0) return 0;
	if(gracz[playerid][firma_onduty] == gracz[playerid][firma]) return 1;
	return 0;
}


stock SendCompanyMessage(companyid, message[])
{
	if(companyid <= 0) return 1;
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][firma] == companyid)
			{
				SendClientMessageEx(p, COLOR_COMPANYMSG, "[C] %s", message);
			}
		}
	}
	return 1;
}

stock LogCompany(l_companyid, l_userid, l_dutysessionid, l_flag, const l_data[], {Float, _}:...)
{
	if(l_companyid == 0 || l_userid == 0 || l_dutysessionid == 0 || l_flag == 0) return 0;
	static
	args,
	str[256];
	/*
	*  Custom function that uses #emit to format variables into a string.
	*  This code is very fragile; touching any code here will cause crashing!
	*/
	if ((args = numargs()) == 5)
	{
		format(str, 256, "%s", l_data);
		mq_format("INSERT INTO `LogCompany` (`company_id`, `user_id`, `duty_session_id`, `flag`, `data`) VALUES ('%d', '%d', '%d', '%d', '%s');", l_companyid, l_userid, l_dutysessionid, l_flag, str);
		mq_send("QSendCompanyLog");
		//print(mQuery);
	}
	else
	{
		while (--args >= 5)
		{
			#emit LCTRL 5
			#emit LOAD.alt args
			#emit SHL.C.alt 2
			#emit ADD.C 12
			#emit ADD
			#emit LOAD.I
			#emit PUSH.pri
		}
		#emit PUSH.S l_data
		#emit PUSH.C 256
		#emit PUSH.C str
		#emit PUSH.S 8
		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4
		mq_format("INSERT INTO `LogCompany` (`company_id`, `user_id`, `duty_session_id`, `flag`, `data`) VALUES ('%d', '%d', '%d', '%d', '%s');", l_companyid, l_userid, l_dutysessionid, l_flag, str);
		mq_send("QSendCompanyLog");
		//print(mQuery);
		#emit RETN
	}


	
	//mq_format("INSERT INTO `LogCompany` (`company_id`, `user_id`, `duty_session_id`, `flag`, `data`) VALUES ('%d', '%d', '%d', '%d', '%s');", l_companyid, l_userid, l_dutysessionid, l_flag, l_data);
	//mq_send("QSendCompanyLog");
	return 1;
}

CMD:stworzfirme(playerid, params[])
{
	if(gracz[playerid][firma] != 0) return Error(playerid, "Nie możesz założyć firmy, bo jesteś zatrudniony w innej firmie.");
	new strCreateCompany[3072];
	for(new cid; cid < MAX_COMPANY; cid++)
	{
		if(company[cid][cny_owneruid] != 0) continue;
		if(IsPlayerInRangeOfPoint(playerid, 3.0, company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ]))
		{
			format(strCreateCompany, 3072, ""COL_WHITE"Witaj w kreatorze tworzenia firmy!");
			format(strCreateCompany, 3072, "%s\nJedynie co musisz w tym momencie zrobić to wprowadzić "COL_BLUE"nazwę swojej firmy"COL_WHITE" i posiadać "COL_GREEN"wymaganą gotówkę"COL_WHITE".", strCreateCompany);
			format(strCreateCompany, 3072, "%s\nZanim jednak to zrobisz, zapoznaj się z możliwościami jak i zasadami posiadania firmy.\n", strCreateCompany);
			format(strCreateCompany, 3072, "%s\n"COL_LIME"Możliwości"COL_WHITE":", strCreateCompany); 
			format(strCreateCompany, 3072, "%s\n"COL_LIME"• {8B8B8B}Wysokie zarobki przez wykonywanie kontraktów.", strCreateCompany);
			format(strCreateCompany, 3072, "%s\n"COL_LIME"• {8B8B8B}Możliwość zatrudniania pracowników i ustalania im wypłat.", strCreateCompany);
			format(strCreateCompany, 3072, "%s\n"COL_LIME"• {8B8B8B}Możliwość posiadania pojazdów firmowych.", strCreateCompany);
			format(strCreateCompany, 3072, "%s\n"COL_LIME"• {8B8B8B}Posiadanie własnej siedziby na mapie (w miejscu, którym się obecnie znajdujesz).\n", strCreateCompany);
			format(strCreateCompany, 3072, "%s\n"COL_ORANGE"Zasady"COL_WHITE":", strCreateCompany);
			format(strCreateCompany, 3072, "%s\n"COL_ORANGE"• {8B8B8B}Niewykonanie kontraktu w określonym czasie grozi karą finansową.", strCreateCompany);
			format(strCreateCompany, 3072, "%s\n"COL_ORANGE"• {8B8B8B}Wypłaty dla pracowników są pobierane z konta firmowego.", strCreateCompany);
			format(strCreateCompany, 3072, "%s\n"COL_ORANGE"• {8B8B8B}Pracownicy mają płacone za czas spędzony na duty a nie na akord (pilnuj swoich pracowników!).", strCreateCompany);
			format(strCreateCompany, 3072, "%s\n"COL_ORANGE"• {8B8B8B}Jeśli konto firmowe jest puste, pracownicy nie będą otrzymywać wypłat.", strCreateCompany);
			format(strCreateCompany, 3072, "%s\n"COL_ORANGE"• {8B8B8B}Jeśli Twoja firma nie będzie opłacana w czas, zostanie ona usunięta przy najbliższym restarcie serwera.", strCreateCompany);
			format(strCreateCompany, 3072, "%s\n"COL_ORANGE"• {8B8B8B}Uiszczanie opłaty za firmę wykonuje się przez panel firmy ("COL_YELLOW"/firma{8B8B8B}).", strCreateCompany);
			format(strCreateCompany, 3072, "%s\n"COL_ORANGE"• {8B8B8B}Jeśli firma zostanie usunięta to wszystkie pojazdy przypisane do firmy przepadną.", strCreateCompany);
			format(strCreateCompany, 3072, "%s\n"COL_ORANGE"• {8B8B8B}Pracownicy mogą sami odejść z firmy.\n", strCreateCompany);
			format(strCreateCompany, 3072, "%s\n"COL_ORANGE"• {8B8B8B}Firmy z nazwą budzącą kontrowersje, mogą zostać usunięte przez administracje. Także zastanów się nad normalną nazwą.\n", strCreateCompany);
			format(strCreateCompany, 3072, "%s\n"COL_DRVONLINE"Podsumowanie"COL_WHITE":", strCreateCompany);
			format(strCreateCompany, 3072, "%s\nKoszt założenia/utrzymywanie firmy: "COL_GREEN"%d$"COL_WHITE"", strCreateCompany, company[cid][cny_price]);
			format(strCreateCompany, 3072, "%s\nUiszczanie opłaty co: "COL_RED"%d dni"COL_WHITE"\n", strCreateCompany, COMPANY_KEEPDAYS);
			format(strCreateCompany, 3072, "%s\n"COL_RED"Jeśli godzisz się na przedstawione warunki i chcesz założyć firmę, "COL_LIME"wprowadź jej nazwę {8B8B8B}(od 3 do 9 znaków)"COL_RED":", strCreateCompany, COMPANY_KEEPDAYS);
			Dialog_Show(playerid, CREATECOMPANY, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_BLUE"Kreator zakładania firmy"COL_RED" «•", strCreateCompany, "Anuluj", "Załóż");
			return 1;
		}
	}
	Error(playerid, "Nie jesteś przy pickupie wolnej siedziby firmowej.");
	return 1;
}


Dialog:CREATECOMPANY(playerid, response, listitem, inputtext[])
{
	if(response) return Error(playerid, "Anulowałeś założenie firmy.");
	if(strlen(inputtext) < 3) return Error(playerid, "Nazwa firmy jest za krótka.");
	if(strlen(inputtext) > 9) return Error(playerid, "Nazwa firmy jest za długa.");
	new strCreateCompany[3072];
	for(new cid; cid < MAX_COMPANY; cid++)
	{
		if(company[cid][cny_owneruid] != 0) continue;
		if(IsPlayerInRangeOfPoint(playerid, 3.0, company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ]))
		{
			if(Money(playerid) < company[cid][cny_price]) return Error(playerid, "Nie posiadasz wymaganej gotówki.");
			//Pobranie gotówki
			TakeMoney(playerid, company[cid][cny_price]);
			//Konfiguracja firmy
			format(company[cid][cny_name], 64, inputtext);
			company[cid][cny_owneruid] = gracz[playerid][UID];
			company[cid][cny_money] = 0;
			company[cid][cny_score] = 0;
			company[cid][cny_expire] = serwer[time_timestamp]+((60*60)*24)*COMPANY_KEEPDAYS;
			DestroyDynamicPickup(company[cid][cny_pickup]);
			company[cid][cny_pickup] = CreateDynamicPickup(1314, 1, company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ]);
			new strTemp[1024];
			format(strTemp, 1024, ""COL_GREEN"« "COL_BLUE"SŁUŻBA W FIRMIE - "COL_RED"%s (ID:%d)"COL_GREEN"»\n", company[cid][cny_name], cid);
			format(strTemp, 1024, "%s"COL_GREEN"« "COL_YELLOW"WŁAŚCICIEL: "COL_RED"%s "COL_GREEN"»\n", strTemp, GetPlayerIGName(company[cid][cny_owneruid]));
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_ORANGE"PPM"COL_GREY" lub "COL_ORANGE"/cduty start"COL_GREY" aby rozpocząć pracę. "COL_RED"•\n", strTemp);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_ORANGE"PPM"COL_GREY" lub "COL_ORANGE"/cduty stop"COL_GREY" aby zakończyć pracę. "COL_RED"•\n", strTemp);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_ORANGE"/cduty info"COL_GREY" aby sprawdzić status służby. "COL_RED"•\n", strTemp);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_WHITE"/firma"COL_GREY" Panel firmy "COL_RED"•\n", strTemp);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_WHITE"/kontrakt status"COL_GREY" aby sprawdzić stan kontraktu"COL_GREY". "COL_RED"•\n", strTemp);
			UpdateDynamic3DTextLabelText(company[cid][cny_text3d], -1, strTemp);
			DestroyDynamicMapIcon(company[cid][cny_icon]);
			company[cid][cny_icon] = CreateDynamicMapIcon(company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ], 12, 0, .streamdistance = 300.0, .style = MAPICON_GLOBAL);
			//Konfiguracja gracza
			gracz[playerid][firma] = cid;
			gracz[playerid][firma_permlvl] = 2;
			//Zapis danych
			CompanySaveData(cid);
			mq_format("UPDATE `Konta` SET `firma`='%d', `firma_permlvl`='2' WHERE `id`='%d';", cid, gracz[playerid][UID]);
			mq_send("QUpdatePlayerCompany");
			//Aktualizacja daty stworzenia firmy
			mq_format("UPDATE `firmy` SET `created`=CURRENT_TIMESTAMP WHERE `id`='%d';", cid);
			mq_send("QUpdateCreateCompany", "d", cid);
			//Komuniakt
			format(strCreateCompany, 3072, ""COL_GREEN"GRATULACJE!!!");
			format(strCreateCompany, 3072, "%s\n"COL_WHITE"Właśnie stałeś się prezesem firmy: "COL_BLUE"%s", strCreateCompany, company[cid][cny_name]);
			format(strCreateCompany, 3072, "%s\n"COL_WHITE"Kosztowało Cię to "COL_GREEN"%d$"COL_WHITE".", strCreateCompany, company[cid][cny_price]);
			format(strCreateCompany, 3072, "%s\n"COL_WHITE"Zakup pojazdy firmowe, zatrudnij pracowników, zacznij wykonywać kontrakty i zarabiać krocie! :)", strCreateCompany);
			format(strCreateCompany, 3072, "%s\n"COL_ORANGE"Pamiętaj aby regularnie opłacać swoją firmę (zrobisz to w panelu firmy)!", strCreateCompany);
			format(strCreateCompany, 3072, "%s\n"COL_WHITE"Panel zarządzania firmą znajdziesz pod komendą "COL_YELLOW"/firma"COL_WHITE".", strCreateCompany);
			MessageGUIEx(playerid, ""COL_RED"•» "COL_GREEN"Firma założona!"COL_RED" «•",  strCreateCompany);
			return 1;
		}
	}
	Error(playerid, "Nie jesteś przy pickupie wolnej siedziby firmowej.");
	return 1;
}

task QUpdateCreateCompany(cid)
{
	mq_format("SELECT `created` FROM `firmy` WHERE `id`='%d';", cid);
	mq_send("QGetCompanyDateToSTR", "d", cid);
	return 1;
}

task QGetCompanyDateToSTR(cid)
{
	mq_getdata();
	if(rekordy)
	{
		cache_get_value_name(0, "created", company[cid][cny_created], 32);
	}
	return 1;
}

CMD:cduty(playerid, params[])
{
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	if(TruckerWhileOrderCheck(playerid)) return Error(playerid, "Jesteś podczas zlecenia. Aby je anulować wpisz: "COL_ORANGE"/zlecenie anuluj"COL_WHITE".");
	if(IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Jesteś na służbie w frakcji, możesz tutaj użyć: /duty stop");
	if(gracz[playerid][pursuit_enabled]) return Error(playerid, "Nie możesz zmieniać statusu duty podczas pościgu.");
	if(compare(params, "start"))
	{
		if(IsPlayerOnDutyCompany(playerid)) return Error(playerid, "Już jesteś na służbie.");
		if(IsPlayerInRangeOfPoint(playerid, 2.0, company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ]))
		{
			mq_format("INSERT INTO `LogCompanySessionDuty` (`user_id`, `company_id`, `timestamp_start`, `timestamp_end`) VALUES ('%d', '%d', FROM_UNIXTIME('%d'), FROM_UNIXTIME('%d'));", gracz[playerid][UID], gracz[playerid][firma], serwer[time_timestamp], serwer[time_timestamp]);
			mq_send("OnDutyStartCompany", "d", playerid);
		} 
		else Error(playerid, "Nie jesteś w pickupie swojej firmy.");
	}
	else if(compare(params, "stop"))
	{
		if(!IsPlayerOnDutyCompany(playerid)) return Error(playerid, "Nie jesteś na służbie.");
		new fid = gracz[playerid][frakcja];
		if(IsPlayerInRangeOfPoint(playerid, 2.0, company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ]) || IsPlayerInRangeOfPoint(playerid, 2.0, fractions[fid][fr_dutyX], fractions[fid][fr_dutyY], fractions[fid][fr_dutyZ]))
		{
			new strDutyInfo[1024];
			format(strDutyInfo, 1024, ""COL_WHITE"Zszedłeś z duty firmy: %s"COL_WHITE".\n", company[cid][cny_name]);
			format(strDutyInfo, 1024, "%s"COL_WHITE"Przerwano sesje duty która trwała: "COL_GREEN"%d minut"COL_WHITE".\n", strDutyInfo, (gracz[playerid][time_duty]/60));
			new Float:kasa_procent = procent(float((gracz[playerid][time_duty]/60)), float(MAX_DUTYSESSION));
			new Float:kasa_wynik = kasa_procent*float(gracz[playerid][firma_wyplata])/100.0;
			if(floatround(kasa_wynik) > 0)
			{
				format(strDutyInfo, 1024, "%s"COL_WHITE"Otrzymujesz "COL_BLUE"%0.1f%%"COL_WHITE" wypłaty czyli "COL_LIME"%d$"COL_WHITE".\n", strDutyInfo, kasa_procent, floatround(kasa_wynik));
				if(company[cid][cny_money] > floatround(kasa_wynik)) 
				{
					company[cid][cny_money] -= floatround(kasa_wynik);
					CompanySaveMoney(cid);
					GiveMoney(playerid, floatround(kasa_wynik));
					//CUSTOM LOG
					new strCustomLog[256];
					format(strCustomLog, 256, "Wyplata dla pracownika. Koszt: %d$. Saldo: %d$", floatround(kasa_wynik), company[cid][cny_money]);
					mq_format("INSERT INTO `LogCompany` (`company_id`, `user_id`, `duty_session_id`, `flag`, `data`, `kursy_per_wyplata`) VALUES ('%d', '%d', '%d', '%d', '%s', '%d');", cid, gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_WYDATEK, strCustomLog, gracz[playerid][company_kursy_per_wyplata]);
					mq_send("QSendCompanyLog");
					//CUSTOM LOG - END
				}
				else 
				{
					format(strDutyInfo, 1024, "%s"COL_RED"UPS! Twojej firmy nie stać na wypłatę!\n", strDutyInfo);
					//CUSTOM LOG
					new strCustomLog[256];
					format(strCustomLog, 256, "[!!!] Nie dostal wyplaty - brak srodkow. Naleznosc: %d$", floatround(kasa_wynik));
					mq_format("INSERT INTO `LogCompany` (`company_id`, `user_id`, `duty_session_id`, `flag`, `data`, `kursy_per_wyplata`) VALUES ('%d', '%d', '%d', '%d', '%s', '%d');", cid, gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_WYDATEK, strCustomLog, gracz[playerid][company_kursy_per_wyplata]);
					mq_send("QSendCompanyLog");
					//CUSTOM LOG - END
				}
				ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_WHITE"Przerwanie sesji "COL_RED"«•", strDutyInfo, "Zamknij", "");
			}
			//SendClientMessageToAllEx(0x63666AFF, "••• Gracz {%06x}%s(%d) {63666A}zakończył służbę jako %s {63666A}(%d minut) •••", GetPlayerColor(playerid) >>> 8, nick(playerid), playerid, GetFractionName(cid, 1), gracz[playerid][time_duty_total]/60);
			mq_format("UPDATE `LogCompanySessionDuty` SET `timestamp_end`=FROM_UNIXTIME('%d') WHERE `id`='%d';", serwer[time_timestamp], gracz[playerid][firma_sessionid]);
			mq_send("QEndCompanyDuty");
			gracz[playerid][firma_onduty] = 0;
			gracz[playerid][firma_sessionid] = 0;
			Info(playerid, "Zszedłeś ze służby.");
			CargoInfo_Hide(playerid);
			ClearObjective(playerid);
		}
		else Error(playerid, "Nie jesteś w pickupie swojej firmy.");
	}
	else if(compare(params, "info"))
	{
		if(!IsPlayerOnDutyCompany(playerid)) return Error(playerid, "Nie jesteś na służbie.");
		//SELECT Sum(`lg`.`duty_session_time`), `lg`.`user_id`,`lg`.`company_id` FROM (SELECT Timestampdiff(second, `l`.`timestamp_start`, `l`.`timestamp_end`) AS `duty_session_time`, `l`.`user_id`,`l`.`company_id` FROM   `LogCompanySessionDuty` `l`) `lg` GROUP  BY `lg`.`user_id`;
		//SELECT Sum(`lg`.`duty_session_time`), `lg`.`user_id`,`lg`.`company_id` FROM (SELECT Timestampdiff(second, `l`.`timestamp_start`, `l`.`timestamp_end`) AS `duty_session_time`, `l`.`user_id`,`l`.`company_id` FROM   `LogCompanySessionDuty` `l` WHERE `l`.`user_id` = '%d') `lg` GROUP  BY `lg`.`user_id`;
		//SELECT Sum(`lg`.`duty_session_time`), `lg`.`user_id`,`lg`.`company_id` FROM (SELECT Timestampdiff(second, `l`.`timestamp_start`, `l`.`timestamp_end`) AS `duty_session_time`, `l`.`user_id`,`l`.`company_id` FROM   `LogCompanySessionDuty` `l` WHERE `l`.`user_id` = '%d' AND `l`.`company_id` = '%d') `lg` GROUP  BY `lg`.`user_id`;
		//SELECT Sum(`lg`.`duty_session_time`) AS `total_duty_onecompany`, `lg`.`user_id`,`lg`.`company_id` FROM (SELECT Timestampdiff(second, `l`.`timestamp_start`, `l`.`timestamp_end`) AS `duty_session_time`, `l`.`user_id`,`l`.`company_id` FROM   `LogCompanySessionDuty` `l` WHERE `l`.`user_id` = '1' AND `l`.`company_id` = '1') `lg` GROUP  BY `lg`.`user_id`;
		//mq_format("SELECT Sum(`lg`.`duty_session_time`) AS `total_duty_onecompany`, `lg`.`user_id`,`lg`.`company_id` FROM (SELECT `l`.`seconds_online`) AS `duty_session_time`, `l`.`user_id`,`l`.`company_id` FROM `LogCompanySessionDuty` `l` WHERE `l`.`user_id` = '%d' AND `l`.`company_id` = '%d') `lg` GROUP  BY `lg`.`user_id`;", gracz[playerid][UID], cid);
		new strDutyInfo[1024];
		format(strDutyInfo, 1024, ""COL_WHITE"Jesteś na służbie w firmie: "COL_RED"%s"COL_WHITE".\n", company[cid][cny_name]);
		format(strDutyInfo, 1024, "%s"COL_WHITE"Sesja duty na serwerze trwa: "COL_ORANGE"%d minut"COL_GREY" (ta wartość jest ustalana przez administracje)"COL_WHITE".\n", strDutyInfo, MAX_DUTYSESSION);
		format(strDutyInfo, 1024, "%s"COL_WHITE"Twoja stawka za sesję duty: "COL_LIME"%d$"COL_GREY" (ta wartość jest ustalana przez lidera/v-ce lidera firmy)"COL_WHITE".\n", strDutyInfo, gracz[playerid][firma_wyplata]);
		format(strDutyInfo, 1024, "%s"COL_WHITE"Twoja sesja duty zakończy się za: "COL_GREEN"%d minut"COL_GREY" (wtedy dostaniesz wypłatę (stawkę za sesje))"COL_WHITE".\n", strDutyInfo, MAX_DUTYSESSION-(gracz[playerid][time_duty]/60));
		format(strDutyInfo, 1024, "%s"COL_WHITE"Ogólnie jesteś na służbie: "COL_GREEN"%d minut"COL_GREY" (liczone od wprowadzenia komendy /cduty start)"COL_WHITE".\n", strDutyInfo, (gracz[playerid][time_duty_total]/60));
		SetPVarString(playerid, "strDutyInfoC", strDutyInfo);
		
		mq_format("SELECT Sum(`seconds_online`) AS `suma` FROM `LogCompanySessionDuty` WHERE `company_id`='%d' AND `user_id`='%d';", cid, gracz[playerid][UID]);
		mq_send("QDutyInfoGUI", "d", playerid);// ->>>
	}
	else SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /cduty [start/stop/info]");
	return 1;
}

task OnDutyStartCompany(playerid)
{
	gracz[playerid][firma_sessionid] = cache_insert_id();
	gracz[playerid][firma_onduty] = gracz[playerid][firma];
	mq_format("SELECT `motd` FROM  `firmy` WHERE `id`='%d';", gracz[playerid][firma]);
	mq_send("ShowMOTDForPlayer", "d", playerid);
	gracz[playerid][company_kursy_per_wyplata] = 0;
	Info(playerid, "Wszedłeś na służbę.");
	return 1;
}

task QDutyInfoGUI(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new strDutyInfo[1024];
		GetPVarString(playerid, "strDutyInfoC", strDutyInfo, 1024);
		DeletePVar(playerid, "strDutyInfoC");
		new total_seconds_online;
		cache_get_value_name_int(0, "suma",   total_seconds_online);
		new  total_duty_hours, total_duty_min;
		SecToTime2(total_seconds_online, total_duty_hours, total_duty_min);
		format(strDutyInfo, 1024, "%s"COL_WHITE"Całkowity czas pracy: "COL_GREEN"%d godzin, %d minut"COL_GREY" (ile ogólnie spędziłeś czasu na /cduty od chwili zatrudnienia we firmie)"COL_WHITE".\n", strDutyInfo, total_duty_hours, total_duty_min);
		ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_WHITE"Informacje dotyczące służby "COL_RED"«•", strDutyInfo, "Zamknij", "");
	}
	return 1;
}



task Process_PlayerCompanyDuty(playerid)
{
	if(IsPlayerAFK(playerid)) return 1;
	if(IsPlayerPaused(playerid)) return 1;
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) return 1;
	if(IsPlayerOnDutyCompany(playerid))
	{
		gracz[playerid][time_duty]++;
		gracz[playerid][time_duty_total]++;
		if(gracz[playerid][time_duty] > (60*MAX_DUTYSESSION))
		{
			//wypłata
			new cid = gracz[playerid][firma];
			if(company[cid][cny_money] > gracz[playerid][firma_wyplata])
			{
				company[cid][cny_money] -= gracz[playerid][firma_wyplata];
				CompanySaveMoney(cid);
				GiveMoney(playerid, gracz[playerid][firma_wyplata]);
				GiveScore(playerid, company[gracz[playerid][firma]][cny_cnt_score]);
				//CUSTOM LOG
				new strCustomLog[256];
				format(strCustomLog, 256, "Wyplata dla pracownika. Koszt: %d$. Saldo: %d$", gracz[playerid][firma_wyplata], company[cid][cny_money]);
				mq_format("INSERT INTO `LogCompany` (`company_id`, `user_id`, `duty_session_id`, `flag`, `data`, `kursy_per_wyplata`) VALUES ('%d', '%d', '%d', '%d', '%s', '%d');", cid, gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_WYDATEK, strCustomLog, gracz[playerid][company_kursy_per_wyplata]);
				mq_send("QSendCompanyLog");
				//CUSTOM LOG - END
				PlayerPlaySound(playerid, 4201, 0, 0, 0);
				new strGameText[64];
				format(strGameText, 64, "~b~OTRZYMUJESZ WYPLATE~n~~g~+%d$~n~~y~+%d score", gracz[playerid][firma_wyplata], company[gracz[playerid][firma]][cny_cnt_score]);
				GameTextForPlayer(playerid, strGameText,  5000, 0);
				SendClientMessage(playerid, COLOR_COMPANYMSG, "[C] ••••••••••••••••••••••••••••••••••••••••» "COL_RED"Wypłata "COL_FMSG"«••••••••••••••••••••••••••••••••••••••••");
				SendClientMessageEx(playerid, COLOR_COMPANYMSG, "[C] Zakończono sesję duty ("COL_LIME"%d minut"COL_FMSG"). Ogólnie na służbie jesteś "COL_BLUE"%d minut"COL_FMSG". "COL_LIME"Czas na wypłatę!", MAX_DUTYSESSION, gracz[playerid][time_duty_total]/60);
				SendClientMessageEx(playerid, COLOR_COMPANYMSG, "[C] Otrzymujesz wynagrodzenie w postaci "COL_RED"%d$"COL_FMSG" i "COL_RED"+%d score"COL_FMSG".", gracz[playerid][firma_wyplata], company[gracz[playerid][firma]][cny_cnt_score]);
				SendClientMessageEx(playerid, COLOR_COMPANYMSG, "[C] Rozpoczęto kolejną sesję duty, aby sprawdzić jej stan, użyj: "COL_WHITE"/cduty info"COL_FMSG". Miłej pracy :)");
				SendClientMessage(playerid, COLOR_COMPANYMSG, "[C] •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••");
			}
			else
			{
				GiveScore(playerid, company[gracz[playerid][firma]][cny_cnt_score]);
				//CUSTOM LOG
				new strCustomLog[256];
				format(strCustomLog, 256, "[!!!] Nie dostal wyplaty - brak srodkow. Naleznosc: %d$", gracz[playerid][firma_wyplata]);
				mq_format("INSERT INTO `LogCompany` (`company_id`, `user_id`, `duty_session_id`, `flag`, `data`, `kursy_per_wyplata`) VALUES ('%d', '%d', '%d', '%d', '%s', '%d');", cid, gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_WYDATEK, strCustomLog, gracz[playerid][company_kursy_per_wyplata]);
				mq_send("QSendCompanyLog");
				//CUSTOM LOG - END
				SendClientMessage(playerid, COLOR_COMPANYMSG, "[C] ••••••••••••••••••••••••••••••••••••••••» "COL_RED"Wypłata "COL_FMSG"«••••••••••••••••••••••••••••••••••••••••");
				SendClientMessageEx(playerid, COLOR_COMPANYMSG, "[C] Zakończono sesję duty ("COL_LIME"%d minut"COL_FMSG"). Ogólnie na służbie jesteś "COL_BLUE"%d minut"COL_FMSG". "COL_LIME"Czas na wypłatę!", MAX_DUTYSESSION, gracz[playerid][time_duty_total]/60);
				SendClientMessageEx(playerid, COLOR_COMPANYMSG, "[C] "COL_RED"UPS! Twojej firmy nie stać na wypłatę. Dostajesz "COL_RED"%d score"COL_FMSG" (aktualny kontrakt).", company[gracz[playerid][firma]][cny_cnt_score]);
				SendClientMessageEx(playerid, COLOR_COMPANYMSG, "[C] Rozpoczęto kolejną sesję duty, aby sprawdzić jej stan, użyj: "COL_WHITE"/cduty info"COL_FMSG". Miłej pracy :)");
				SendClientMessage(playerid, COLOR_COMPANYMSG, "[C] •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••");
			}
			//--
			gracz[playerid][company_kursy_per_wyplata] = 0;
			gracz[playerid][time_duty] = 0;
		}
	} 
	else 
	{
		if(IsPlayerOnDutyFraction(playerid)) return 1;//jeśli gracz siedzi na frakcji, to nie ruszaj tych zmiennych...
		gracz[playerid][time_duty] = 0;
		gracz[playerid][time_duty_total] = 0;
	}
	return 1;
}
//UPDATE logi SET time_end = NOW() WHERE id IN (12,13,16,76,98)
task Process_UpdateCompanySession()
{
	new count_ucs = 0;
	new strPlayersOnDuty[512];
	format(strPlayersOnDuty, 512, "(");
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(!gracz[p][loggedin]) continue;
		if(IsPlayerOnDutyCompany(p))
		{
			if(gracz[p][firma_sessionid] != 0)
			{
				if(IsPlayerAFK(p)) continue;
				if(IsPlayerPaused(p)) continue;
				if(GetPlayerState(p) == PLAYER_STATE_SPECTATING) continue;
				format(strPlayersOnDuty, 512, "%s%d,", strPlayersOnDuty, gracz[p][firma_sessionid]);
				count_ucs++;
			}
		}
	}
	if(count_ucs == 0) return 1;
	new lenght = strlen(strPlayersOnDuty);
	strdel(strPlayersOnDuty, lenght-1, lenght);
	format(strPlayersOnDuty, 512, "%s)", strPlayersOnDuty);
	//printf(strPlayersOnDuty);//debug
	mq_format("UPDATE `LogCompanySessionDuty` SET `timestamp_end` = NOW(), `seconds_online`=`seconds_online`+1 WHERE `id` IN %s;", strPlayersOnDuty);
	mq_send("QUpCompSession");
	//printf(mQuery);
	return 1;
}

CMD:firma(playerid, params[])
{ 
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	if(!IsPlayerOnDutyCompany(playerid)) return Error(playerid, "Musisz być na służbie w firmie.");
	new strCompanyMenu[2048];
	if(gracz[playerid][firma_permlvl] == 0) 
	{
		if(company[cid][cny_cnt_goodid] == 0) format(strCompanyMenu, 2048, ""COL_RED"•»\t"COL_RED"-BRAK KONTRAKTU-\t"COL_RED"«•");
		else format(strCompanyMenu, 2048, ""COL_RED"•»\t"COL_RED"Status kontraktu "COL_BLUE"[ukończono: "COL_LIME"%d%%"COL_BLUE"] \t"COL_RED"«•", procent(company[cid][cny_cnt_size_complet], company[cid][cny_cnt_size]));
		format(strCompanyMenu, 2048, "%s\n"COL_LIME"•»\t"COL_EASY"Lista pracowników "COL_WHITE"("COL_RED"%d"COL_WHITE"/"COL_GREEN"%d"COL_WHITE")\t"COL_LIME"«•", strCompanyMenu, CompanyWorkersCount(cid), MAX_CWORKERS);
		format(strCompanyMenu, 2048, "%s\n"COL_LIME"•»\t"COL_ORANGE"Zwolnij się\t"COL_LIME"«•", strCompanyMenu);
		new strHeader[512];
		format(strHeader, 512, ""COL_RED"•» "COL_GREEN"Panel firmy - %s"COL_RED" «•", company[cid][cny_name]);
		Dialog_Show(playerid, COMPANYMENUWRK, DIALOG_STYLE_TABLIST, strHeader, strCompanyMenu, "OK", "Anuluj");
	//work here
	//	Dialog_Show(playerid, DEFINELISTWORKERSC, DIALOG_STYLE_MSGBOX, "Co to jest skuteczność?", ""COL_ORANGE"Skuteczność"COL_WHITE" - średnia ilość kursów na wypłatę (30 min). Oceniaj wartości pracowników z podobną ilością wypłat/kursów.", "Lista", "");
		return 1;
	}
	if(company[cid][cny_cnt_goodid] == 0) format(strCompanyMenu, 2048, ""COL_RED"•»\t"COL_RED"Szukaj kontraktu\t"COL_RED"«•");
	else format(strCompanyMenu, 2048, ""COL_RED"•»\t"COL_RED"Status kontraktu "COL_BLUE"[ukończono: "COL_LIME"%d%%"COL_BLUE"] \t"COL_RED"«•", procent(company[cid][cny_cnt_size_complet], company[cid][cny_cnt_size]));
	format(strCompanyMenu, 2048, "%s\n"COL_LIME"•»\t"COL_EASY"Lista pracowników "COL_WHITE"("COL_RED"%d"COL_WHITE"/"COL_GREEN"%d"COL_WHITE")\t"COL_LIME"«•", strCompanyMenu, CompanyWorkersCount(cid), MAX_CWORKERS);
	format(strCompanyMenu, 2048, "%s\n"COL_LIME"•»\t"COL_GREEN"Zatrudnij nowego pracownika\t"COL_LIME"«•", strCompanyMenu);
	format(strCompanyMenu, 2048, "%s\n"COL_LIME"•»\t"COL_EASY"Ustaw wiadomość powitalną\t"COL_LIME"«•", strCompanyMenu); 
	format(strCompanyMenu, 2048, "%s\n"COL_LIME"•»\t"COL_EASY"Zrespawnuj nieużywane pojazdy\t"COL_LIME"«•", strCompanyMenu); 
	format(strCompanyMenu, 2048, "%s\n"COL_LIME"•»\t"COL_EASY"Lista pojazdów firmowych "COL_WHITE"("COL_RED"%d"COL_WHITE"/"COL_GREEN"%d"COL_WHITE")\t"COL_LIME"«•", strCompanyMenu, CompanyVehiclesCount(cid), MAX_CVEHICLES);
	format(strCompanyMenu, 2048, "%s\n"COL_BLUE"•»\t"COL_EASY"Przypisz prywatny pojazd do firmy\t"COL_BLUE"«•", strCompanyMenu);
	format(strCompanyMenu, 2048, "%s\n"COL_LIME"•»\t"COL_EASY"Zamknij wszystkie bramy\t"COL_LIME"«•", strCompanyMenu); 
	format(strCompanyMenu, 2048, "%s\n"COL_RED"•»\t"COL_BLUE"Kapitał "COL_GREY"[Saldo: "COL_GREEN"%d$"COL_GREY"]\t"COL_RED"«•", strCompanyMenu, company[cid][cny_money]); 
	format(strCompanyMenu, 2048, "%s\n"COL_LIME"•»\t"COL_EASY"Logi kursów\t"COL_LIME"«•", strCompanyMenu);
	format(strCompanyMenu, 2048, "%s\n"COL_LIME"•»\t"COL_EASY"Logi pojazdów\t"COL_LIME"«•", strCompanyMenu);
	format(strCompanyMenu, 2048, "%s\n"COL_LIME"•»\t"COL_RED"Sprzedaj firme\t"COL_LIME"«•", strCompanyMenu);
	format(strCompanyMenu, 2048, "%s\n"COL_LIME"•»\t"COL_EASY"Informacje o firmie\t"COL_LIME"«•", strCompanyMenu);
	new dd, hh, mm, ss;
	new comp_timestamp = company[cid][cny_expire]-serwer[time_timestamp];
	if(comp_timestamp < 0) comp_timestamp = 0;
	SecToTime(comp_timestamp, dd, hh, mm, ss);
	format(strCompanyMenu, 2048, "%s\n"COL_RED"•»\t"COL_LIME"Opłać firmę "COL_GREY"[pozostało: %d dni, %d godzin]\t"COL_RED"«•", strCompanyMenu, dd, hh);
	if(gracz[playerid][firma_permlvl] == 1) format(strCompanyMenu, 2048, "%s\n"COL_LIME"•»\t"COL_ORANGE"Zwolnij się\t"COL_LIME"«•", strCompanyMenu);//v-ce lider
	new strHeader[512];
	format(strHeader, 512, ""COL_RED"•» "COL_GREEN"Panel firmy - %s"COL_RED" «•", company[cid][cny_name]);
	Dialog_Show(playerid, COMPANYMENU, DIALOG_STYLE_TABLIST, strHeader, strCompanyMenu, "OK", "Anuluj");
	return 1;
}


Dialog:COMPANYMENUWRK(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	switch(listitem)
	{
		case 0://status kontraktu
		{
			PC_EmulateCommand(playerid, "/kontrakt s");
		}
		case 1://lista pracowników
		{
			Dialog_Show(playerid, DEFINELISTWORKERSC, DIALOG_STYLE_MSGBOX, "Co to jest skuteczność?", ""COL_ORANGE"Skuteczność"COL_WHITE" - średnia ilość kursów na wypłatę (30 min). Oceniaj wartości pracowników z podobną ilością wypłat/kursów.", "Lista", "");
		}
		case 2://zwolnij sie
		{
			new strHeader[512], strEditWorker[1024];
			new target_uid  = gracz[playerid][UID];
			SetPVarInt(playerid, "company_manageworkeruid", target_uid);
			format(strHeader, 512, ""COL_RED"•» "COL_GREEN"Czy chcesz zwolnić "COL_ORANGE"%s (%d)"COL_GREEN"?"COL_RED" «•", GetPlayerIGName(target_uid), target_uid);
			format(strEditWorker, 1024, ""COL_RED"•» "COL_GREEN"Czy chcesz zwolnić "COL_ORANGE"%s (%d)"COL_GREEN"?"COL_RED" «•", GetPlayerIGName(target_uid), target_uid);
			Dialog_Show(playerid, COMPANYDELWORKER, DIALOG_STYLE_MSGBOX, strHeader, strEditWorker, "Zwolnij", "Anuluj");
		}
	}
	return 1;
}

Dialog:COMPANYMENU(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	if(gracz[playerid][firma_permlvl] == 0) return Error(playerid, "Brak uprawnień.");
	switch(listitem)
	{
		case 0://Kontrakty
		{
			if(company[cid][cny_cnt_goodid] == 0)
			{
				//wybór z listy
				/*
				new strContractsList[3072];
				new strSrcZone[24], strDstZone[24];
				new slc[9];//shadowline color
				new bool:shadowline;
				new count_listitem;
				format(strContractsList, 3072, "{FFFFFF}Nazwa {8D8D8D}towaru {00C5B6}[waga]\t{00E16A}Źródło "COL_LIME"» [dystans] » {FF4343}Cel\t{028900}Wynagrodzenie "COL_RED"[kara]\t"COL_WHITE"Termin wykonania\n");
				for(new c; c < MAX_CONTRACTS; c++)
				{
					Get2DZone(load_place_van[ contract[c][cnt_fromid] ][0], load_place_van[ contract[c][cnt_fromid] ][1], strSrcZone, 32);
					Get2DZone(load_place_van[ contract[c][cnt_targetid] ][0], load_place_van[ contract[c][cnt_targetid] ][1], strDstZone, 32);
					new dd, hh, mm, ss;
					SecToTime(contract[c][cnt_time], dd, hh, mm, ss);
					slc = (shadowline) ? ("{8D8D8D}") : ("{FFFFFF}");
					format(strContractsList, 3072, "%s\n%s%s {00C5B6}[%0.1f ton]\t{00E16A}%s "COL_LIME"» [%0.1f km] » {FF4343}%s\t"COL_GREEN"+$%d "COL_RED"|"COL_BLUE" +%d score "COL_RED"[-$%d]\t"COL_WHITE"%d dni, %d godz, %d min", strContractsList, slc, goods[contract[c][cnt_goodid]][gds_name], (contract[c][cnt_size]/1000.0), strSrcZone, contract[c][cnt_distance], strDstZone, contract[c][cnt_price], contract[c][cnt_score], contract[c][cnt_penalty], dd, hh, mm);
					if(shadowline) shadowline = false;
					else shadowline = true;
					gui_cache[playerid][count_listitem][0] = c;//id kontraktu
					count_listitem++;
				}
				Dialog_Show(playerid, COMPANYCONTRACTLIST, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_GREEN"Dostępne kontrakty dla firm"COL_RED" «•", strContractsList, "Przyjmij", "Anuluj");
				*/
				//LOSOWANIE - reworked
				///gui_cache[playerid][0][0] = MRandom(MAX_CONTRACTS);
				gui_cache[playerid][0][0] = company[cid][cny_losk];
				dialog_COMPANYCONTRACTLIST(playerid, 1, 0, "null");
			}
			else//status kontraktu
			{
				new strContractStatus[3072];
				new strSrcZone[24], strDstZone[24];

				Get2DZone(load_place_van[ company[cid][cny_cnt_fromid] ][0], load_place_van[ company[cid][cny_cnt_fromid] ][1], strSrcZone, 32);
				Get2DZone(load_place_van[ company[cid][cny_cnt_targetid] ][0], load_place_van[ company[cid][cny_cnt_targetid] ][1], strDstZone, 32);
				new dd, hh, mm, ss;
				SecToTime(company[cid][cny_cnt_time], dd, hh, mm, ss);
				format(strContractStatus, 3072, ""COL_ORANGE"• "COL_EASY"Nazwa towaru: "COL_WHITE"%s %s", goods[company[cid][cny_cnt_goodid]][gds_name], (goods[company[cid][cny_cnt_goodid]][gds_adr] == true) ? (""COL_ORANGE"[ADR]") : (" "));
				format(strContractStatus, 3072, "%s\n"COL_ORANGE"• "COL_EASY"Trasa: {00E16A}%s "COL_LIME"» [%0.1f km] » {FF4343}%s", strContractStatus, strSrcZone, company[cid][cny_cnt_distance], strDstZone);
				format(strContractStatus, 3072, "%s\n"COL_ORANGE"• "COL_EASY"Przetransportowany ładunek: "COL_GREEN"%0.1f"COL_EASY"/"COL_RED"%0.1f {00C5B6}ton "COL_LIME"[%d%%]", strContractStatus, (company[cid][cny_cnt_size_complet]/1000.0), (company[cid][cny_cnt_size]/1000.0), procent(company[cid][cny_cnt_size_complet], company[cid][cny_cnt_size]));
				format(strContractStatus, 3072, "%s\n"COL_ORANGE"• "COL_EASY"Wynagrodzenie: "COL_GREEN"%d$", strContractStatus, company[cid][cny_cnt_price]);
				format(strContractStatus, 3072, "%s\n"COL_ORANGE"• "COL_EASY"Ogólny czas: %d dni, %d godz, %d min", strContractStatus, dd, hh, mm);
				dd = 0;
				hh = 0;
				mm = 0;
				ss = 0;
				SecToTime(company[cid][cny_cnt_time_left], dd, hh, mm, ss);
				format(strContractStatus, 3072, "%s\n"COL_RED"• "COL_ORANGE"Pozostały czas: "COL_BLUE"%d dni, %d godz, %d min, %d sekund", strContractStatus, dd, hh, mm, ss);
				format(strContractStatus, 3072, "%s\n"COL_ORANGE"• "COL_RED"*"COL_EASY"Kara finansowa (jeśli upłynie pozostały czas lub anulujesz): "COL_RED"-%d$", strContractStatus, company[cid][cny_cnt_penalty]);
				format(strContractStatus, 3072, "%s\n\n"COL_RED"*"COL_GREY" - Kara finansowa nie zostanie nałożona, jeśli saldo firmy jest na minusie.", strContractStatus);
				format(strContractStatus, 3072, "%s\n\n"COL_GREY"Prognozowana ilość kursów, przy 100%% załadunku, konkretnymi środkami transportu:"COL_GREY"\n", strContractStatus);
				for(new t; t < 600; t++)
				{
					if(IsVehicleTruckSalonBanned(t)) continue;
					if(!TrailerCanTransportGood(t, goods[company[cid][cny_cnt_goodid]][gds_trailertype]) && IsVehicleTrailer(t)) continue;
					new vehCap = VehicleCapacity(t);
					if(vehCap != 0)
					{
						new Float:wynik = (company[cid][cny_cnt_size]-company[cid][cny_cnt_size_complet])/float(vehCap);
						if(wynik < 1.0) wynik = 1.0;
						format(strContractStatus, 3072, "%s"COL_GREY"- %s ("COL_YELLOW"~%dx"COL_GREY")\n", strContractStatus, GetVehicleName(t), floatround(wynik));
					}
				}
				format(strContractStatus, 3072, "%s\n\n"COL_RED"Czy chcesz anulować kontrakt? Pamiętaj, że za to grozi kara finansowa.", strContractStatus);
				format(strContractStatus, 3072, "%s\n"COL_RED"Aby to zrobić, wpisz w polu poniżej "COL_WHITE"anuluj"COL_RED".\n", strContractStatus);
				Dialog_Show(playerid, CSTATUSCONTRACT, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_GREEN"Status kontraktu"COL_RED" «•", strContractStatus, "Wróć", "");
			}
		}
		case 1://Lista pracowników
		{
			Dialog_Show(playerid, DEFINELISTWORKERSC, DIALOG_STYLE_MSGBOX, "Co to jest skuteczność?", ""COL_ORANGE"Skuteczność"COL_WHITE" - średnia ilość kursów na wypłatę (30 min). Oceniaj wartości pracowników z podobną ilością wypłat/kursów.", "Lista", "");
		}
		case 2://Zatrudnianie pracownika
		{
			if(CompanyWorkersCount(cid) < MAX_CWORKERS)
			{
				new strPlayerList[2048];
				format(strPlayerList, 2048, "ID\tNazwa gracza");
				new Float:pPos[3];
				new bool:find = false;
				for(new p = PlayerPoolSize(); p != -1; p--)
				{
					if(!gracz[p][loggedin]) continue;
					if(p == playerid) continue;
					if(gracz[p][admin_spec_enabled] == true) continue;
					GetPlayerPos(p, pPos[0], pPos[1], pPos[2]);
					if(IsPlayerInRangeOfPoint(playerid, 4.0, pPos[0], pPos[1], pPos[2]))
					{
						format(strPlayerList, 2048, "%s\n%d\t{%06x}%s", strPlayerList, p, GetPlayerColor(playerid) >>> 8, nick(p));
						find = true;
					}
				}
				if(find) Dialog_Show(playerid, COMPANYADDP, DIALOG_STYLE_TABLIST_HEADERS,  ""COL_RED"•» "COL_WHITE"Lista graczy w pobliżu "COL_RED"«•", strPlayerList, "Wybierz", "Wróć");
				else Error(playerid, "Nie znaleziono żadnego gracza w pobliżu.");
			}
			else Error(playerid, "W Twojej firmie znajduje się już maksymalna liczba pracowników.");
		}
		case 3://ustaw wiadomość powitalną
		{
			new strSetMotd[1024];
			strcat(strSetMotd, ""COL_WHITE"W tym miejscu możesz ustalić "COL_GREEN"wiadomość powitalną"COL_WHITE" dla swojej firmy.\n");
			strcat(strSetMotd, ""COL_WHITE"Wiadomość ta będzie wyświetlana dla pracowników "COL_RED"w momencie gdy będą wchodzili na służbę"COL_WHITE".\n");
			strcat(strSetMotd, "{008F7C}Przykład:"COL_EASY" Dziś o godzinie 20:00 odbędzie się zebranie na TS3. Obecność obowiązkowa!\n\n");
			strcat(strSetMotd, "{8B8B8B}• maksymalna długość wiadomości powitalnej to 100 znaków.\n");
			strcat(strSetMotd, "{8B8B8B}• dbaj o to, żeby wiadomość była aktualna.\n");
			strcat(strSetMotd, "{8B8B8B}• "COL_RED"wszyscy pracownicy, którzy są obecnie na służbie otrzymają treść nowej wiadomości powitalnej.\n");
			strcat(strSetMotd, "{8B8B8B}• pozostaw pole puste i zatwierdź aby wyłączyć tą usługę.\n\n");
			strcat(strSetMotd, ""COL_WHITE"Podaj treść wiadomości powitalnej w polu poniżej:");
			Dialog_Show(playerid, COMPANYSETMOTD, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_WHITE"Ustaw wiadomość powitalną "COL_RED"«•", strSetMotd, "Ustaw", "Anuluj");
		}
		case 4://zrespawnuj nieużywane pojazdy
		{
			for(new v = GetVehiclePoolSize(); v != -1; v--)
			{
				if(pojazd[v][v_owner_type] == VEHICLE_BUSINESS)
				{
					if(pojazd[v][v_owner] == cid)
					{
						if(pojazd[v][v_idletime]+(60*6) > serwer[time_timestamp]) continue;
						RespawnVehicle(v, true);
					}
				}
			}
			LeftNotifyShow(playerid, "info", "Wszystkie nieuzywane dluzej niz ~y~6 minut~w~ pojazdy nalezace do Twojej firmy, zostaly ~g~zrespawnowane~w~!", LN_BLUE, 20);
			SendCompanyMessage(cid, "Wszystkie nieużywane dłużej niż 6 minut pojazdy, zostały zrespawnowane.");
		}
		case 5://Lista pojazdów firmowych
		{
			mq_format("SELECT * FROM `pojazdy` WHERE `owner_type`='%d' AND `owner`='%d' ORDER BY `status`='1' DESC LIMIT %d;", VEHICLE_BUSINESS, gracz[playerid][firma], MAX_CVEHICLES);
			mq_send("QCompanyVehicleList", "d", playerid);
		}
		case 6://Przypisz pojazd firmowy
		{
			mq_format("SELECT * FROM `pojazdy` WHERE `owner_type`='%d' AND `owner`='%d' ORDER BY `status`='1' DESC LIMIT %d;", VEHICLE_PLAYER, gracz[playerid][UID], MAX_PRIVCARS_CONST);
			mq_send("QPrivVehToCompany", "d", playerid);
		}
		case 7:
		{
			new maxclose_ms, temp_ms;
			new counter_opengates;
			new g;
			for(new go; go < MAX_GATES; go++)
			{
				if(GateObjects[go] != 0)
				{
					g = GateObjects[go];
					if(ObjectInfo[g][mgOwnerType] != VEHICLE_BUSINESS) continue;
					if(ObjectInfo[g][mgOwner] == cid)
					{
						if(ObjectInfo[g][gOpen])
						{
							temp_ms = MoveDynamicObject(ObjectInfo[g][oObject], ObjectInfo[g][oX], ObjectInfo[g][oY], ObjectInfo[g][oZ], ObjectInfo[g][gSpeed], ObjectInfo[g][oRX], ObjectInfo[g][oRY], ObjectInfo[g][oRZ]);
							ObjectInfo[g][gOpen] = false;
							counter_opengates++;
							if(temp_ms > maxclose_ms) maxclose_ms = temp_ms;//znajdowanie najwiekszej liczby
						}
					}
				}
			}
			new Float:maxclose_sec = maxclose_ms/1000;
			if(counter_opengates > 0)
			{
				new strInfo[512];
				format(strInfo, 512, "Wszystkie ~y~bramy~w~, ktore naleza do ~b~Twojej firmy~w~ otrzymaly polecenie ~r~zamkniecia sie~w~. Znaleziono ~r~%d bram(y)~w~, ktore sa otwarte. Zamkniecie ich zajmie nie wiecej niz ~r~%d sekund(y)~w~.", counter_opengates, floatround(maxclose_sec));
				LeftNotifyShow(playerid, "info", strInfo, LN_BLUE, 20);
			}
			else LeftNotifyShow(playerid, "info", "Zadna ~y~brama~w~ w bazie Twojej firmie ~g~nie jest otwarta~w~.", LN_BLUE, 15);
		}
		case 8://bank
		{
			new strBank[512];
			format(strBank, 512, ""COL_WHITE"•» "COL_EASY"Historia wpłat/wypłat do banku "COL_GREY"[Saldo: "COL_GREEN"%d$"COL_GREY"]", company[cid][cny_money]);
			format(strBank, 512, "%s\n"COL_WHITE"•» "COL_ORANGE"Wydatki", strBank, company[cid][cny_money]); 
			format(strBank, 512, "%s\n"COL_YELLOW"•» "COL_GREEN"Wpłać gotówkę", strBank);
			format(strBank, 512, "%s\n"COL_YELLOW"•» "COL_RED"Wypłać gotówkę", strBank);
			Dialog_Show(playerid, MONEYCOMPANY, DIALOG_STYLE_LIST, ""COL_RED"•» "COL_WHITE"Konto bankowe "COL_RED"«•", strBank, "Wybierz", "Wróć");
		}
		case 9://logi kursów
		{
			GetCompanyLog(playerid, cid, CLOGFLAG_KURS, "Kursy");
		}
		case 10://logi pojazdów
		{
			GetCompanyLog(playerid, cid, CLOGFLAG_POJAZD, "Pojazdy");
		}
		case 11://sprzedaj firmę
		{
			if(company[cid][cny_owneruid] == gracz[playerid][UID])
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
				SetPVarInt(playerid, "cache_cnysell_cid", cid);
				if(find) Dialog_Show(playerid, CNYSELLPLAYER, DIALOG_STYLE_TABLIST_HEADERS,  ""COL_RED"•» "COL_WHITE"Lista graczy w pobliżu "COL_RED"«•", strPlayerList, "Wybierz", "Anuluj");
				else Error(playerid, "Nie znaleziono żadnego gracza w pobliżu, któremu mógłbyś sprzedać firmę.");
			}
			else Error(playerid, "Brak uprawnień.");
		}
		case 12://informacje o firmie
		{
			new strCompanyInfo[2048];
			format(strCompanyInfo, 2048, "\\c"COL_GREEN"Informacje o firmie\n");
			format(strCompanyInfo, 2048, "%s\n"COL_YELLOW"•» "COL_GREY"Nazwa firmy: "COL_DRVONLINE"%s", strCompanyInfo, company[cid][cny_name]);
			format(strCompanyInfo, 2048, "%s\n"COL_YELLOW"•» "COL_GREY"Właściciel: "COL_DRVONLINE"%s", strCompanyInfo, GetPlayerIGName(company[cid][cny_owneruid]));
			format(strCompanyInfo, 2048, "%s\n"COL_YELLOW"•» "COL_GREY"Data założenia firmy: "COL_DRVONLINE"%s", strCompanyInfo, company[cid][cny_created]);
			new dd, hh, mm, ss;
			new comp_timestamp = company[cid][cny_expire]-serwer[time_timestamp];
			if(comp_timestamp < 0) comp_timestamp = 0;
			SecToTime(comp_timestamp, dd, hh, mm, ss);
			format(strCompanyInfo, 2048, "%s\n"COL_YELLOW"•» "COL_GREY"Firma wygaśnie za: "COL_DRVONLINE"%d dni, %d godzin, %d minut", strCompanyInfo, dd, hh, mm);
			format(strCompanyInfo, 2048, "%s\n"COL_YELLOW"•» "COL_GREY"Score firmy: "COL_DRVONLINE"%d punktów", strCompanyInfo, company[cid][cny_score]);
			//               format(strCompanyInfo, 2048, "%s\n", strCompanyInfo);
			Dialog_Show(playerid, COMPANYINFO, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_WHITE"Informacje o firmie "COL_RED"«•", strCompanyInfo, "Zamknij", "");
		}
		case 13://opłać firmę
		{
			if(gracz[playerid][firma_permlvl] != 2) return Error(playerid, "Brak uprawnień.");
			new strCompanyExpire[1024];
			new dd, hh, mm, ss;
			new comp_timestamp = company[cid][cny_expire]-serwer[time_timestamp];
			if(comp_timestamp < 0) comp_timestamp = 0;
			SecToTime(comp_timestamp, dd, hh, mm, ss);
			format(strCompanyExpire, 1024, "\\c"COL_CMSG"Przedłużenie ważności firmy");
			format(strCompanyExpire, 1024, "%s\n"COL_LIME"» "COL_GREY"Twoja firma jest opłacona na "COL_ORANGE"%d dni, %d godzin, %d minut"COL_CMSG".", strCompanyExpire, dd, hh, mm);
			format(strCompanyExpire, 1024, "%s\n"COL_LIME"» "COL_GREY"Koszt przedłużenia firmy to: "COL_RED"%d$", strCompanyExpire, company[cid][cny_price]);
			format(strCompanyExpire, 1024, "%s\n"COL_LIME"» "COL_EASY"Pieniądze zostaną pobrane z konta firmowego. Aktualne saldo: "COL_BLUE"%d$", strCompanyExpire, company[cid][cny_money]);
			format(strCompanyExpire, 1024, "%s\n"COL_LIME"» "COL_GREY"Czy chcesz przedłużyć ważność firmy o kolejne "COL_RED"%d dni"COL_GREY"?", strCompanyExpire, COMPANY_KEEPDAYS);
			Dialog_Show(playerid, ADDEXPIRECOMPANY, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_WHITE"Opłać firmę "COL_RED"«•", strCompanyExpire, "Tak", "Nie");
		}
		case 14://zwolnij sie - tylko vce-lider
		{
			if(gracz[playerid][firma_permlvl] != 1) return Error(playerid, "Brak uprawnień.");
			new strHeader[512], strEditWorker[1024];
			new target_uid  = gracz[playerid][UID];
			SetPVarInt(playerid, "company_manageworkeruid", target_uid);
			format(strHeader, 512, ""COL_RED"•» "COL_GREEN"Czy chcesz zwolnić "COL_ORANGE"%s (%d)"COL_GREEN"?"COL_RED" «•", GetPlayerIGName(target_uid), target_uid);
			format(strEditWorker, 1024, ""COL_RED"•» "COL_GREEN"Czy chcesz zwolnić "COL_ORANGE"%s (%d)"COL_GREEN"?"COL_RED" «•", GetPlayerIGName(target_uid), target_uid);
			Dialog_Show(playerid, COMPANYDELWORKER, DIALOG_STYLE_MSGBOX, strHeader, strEditWorker, "Zwolnij", "Anuluj");
		}
	}
	return 1;
}

Dialog:CNYSELLPLAYER(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new clientid = strval(inputtext);
	if(gracz[clientid][firma] != 0) return Error(playerid, "Ten gracz jest w firmie.");
	SetPVarInt(playerid, "cache_cnysell_clientid", clientid);
	new Float:pPos[3];
	GetPlayerPos(clientid, pPos[0], pPos[1], pPos[2]);
	if(IsPlayerInRangeOfPoint(playerid, 4.0, pPos[0], pPos[1], pPos[2]))
	{
		if(gracz[clientid][PGodz] < 6) return Error(playerid, "Gracz musi mieć minimum 6 godzin całkowitego czasu ONLINE.");
		new strOffer[1024];
		format(strOffer, 1024, ""COL_LIME"Podaj cenę"COL_WHITE", za jaką chcesz sprzedać firmę graczowi "COL_ORANGE"%s(%d)"COL_WHITE".\n", nick(clientid), clientid);
		Dialog_Show(playerid, CNYSELLPRICE, DIALOG_STYLE_INPUT,  ""COL_RED"•» "COL_WHITE"Podaj cenę "COL_RED"«•", strOffer, "Oferuj", "Anuluj");
	}
	else Error(playerid, "Gracz któremu chcesz sprzedać dom, nie jest w pobliżu.");
	return 1;
}

Dialog:CNYSELLPRICE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cid = GetPVarInt(playerid, "cache_cnysell_cid");
	if(cid == 0) return Error(playerid, "Ups! Coś poszło nie tak, spróbuj ponownie.");
	new clientid = GetPVarInt(playerid, "cache_cnysell_clientid");
	if(gracz[clientid][firma] != 0) return Error(playerid, "Ten gracz jest w firmie.");
	new price = strval(inputtext);
	if(price < 0) return Error(playerid, "Kwota nie może być mniejsza niż 0$.");
	if(price > 10000000) return Error(playerid, "Kwota nie może być większa niż 10000000$.");
	new Float:pPos[3];
	GetPlayerPos(clientid, pPos[0], pPos[1], pPos[2]);
	if(IsPlayerInRangeOfPoint(playerid, 4.0, pPos[0], pPos[1], pPos[2]))
	{
		if(price > Money(clientid)) return Error(playerid, "Ten gracz nie posiada przy sobie takiej ilości gotówki.");
		new strOffer[3000];
		format(strOffer, 3000, ""COL_WHITE"Otrzymałeś ofertę zakupu firmy "COL_GREEN"%s (UID: %d)"COL_WHITE" od gracza "COL_ORANGE"%s(%d)"COL_WHITE" za kwotę "COL_LIME"%d$"COL_WHITE".", company[cid][cny_name], cid, nick(playerid), playerid, price);
		format(strOffer, 3000, "%s\n"COL_WHITE"Kapitał firmy: "COL_GREEN"%d$", strOffer, company[cid][cny_money]);
		format(strOffer, 3000, "%s\n"COL_WHITE"Jeśli akcpetujesz ofertę, wpisz poniżej słowo: "COL_LIME"akceptuje", strOffer);
		Dialog_Show(clientid, CNYSELLOFFER, DIALOG_STYLE_INPUT,  ""COL_RED"•» "COL_WHITE"Oferta kupna firmy "COL_RED"«•", strOffer, "Potwierdz", "Anuluj");
		format(strOffer, 3000, ""COL_WHITE"Trwa oczekiwanie, aż "COL_ORANGE"%s"COL_WHITE" zaakceptuje Twoją ofertę. Jeśli chcesz ją "COL_RED"anulować"COL_WHITE", wciśnij przycisk "COL_RED"Anuluj"COL_WHITE".", nick(clientid));
		Dialog_Show(playerid, CNYSELLWAIT, DIALOG_STYLE_MSGBOX,  ""COL_RED"•» "COL_WHITE"Oczekiwanie na zaakceptowanie oferty "COL_RED"«•", strOffer, "Anuluj", "");
		SetPVarInt(clientid, "cache_cnydeal_price", price);
		SetPVarInt(clientid, "cache_cnydeal_cnyuid", cid);
		SetPVarInt(clientid, "cache_cnydeal_vendoruid", gracz[playerid][UID]);
	}
	else Error(playerid, "Gracz któremu chcesz sprzedać firmę, nie jest w pobliżu.");
	return 1;
}


Dialog:CNYSELLOFFER(playerid, response, listitem, inputtext[])
{
	new cid = GetPVarInt(playerid, "cache_cnydeal_cnyuid");
	new price = GetPVarInt(playerid, "cache_cnydeal_price");
	new vendoruid = GetPVarInt(playerid, "cache_cnydeal_vendoruid");
	if(gracz[playerid][firma] != 0) return Error(playerid, "Jesteś w firmie.");
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
			//zwalnianie sprzedającego
			//sekcja offline
			gracz[p][firma] = 0;
			gracz[p][firma_permlvl] = 0;
			gracz[p][firma_wyplata] = 0; 
			gracz[p][firma_onduty] = 0;
			gracz[p][firma_sessionid] = 0;
			mq_format("UPDATE `Konta` SET `firma`='0', `firma_permlvl`='0', `firma_wyplata`='0' WHERE `id`='%d';", gracz[p][UID]);
			mq_send("QUpdateCompanyData");
			GameTextForPlayer(p, "~r~ZOSTALES ZWOLNIONY~n~Z FIRMY",  5000, 0);//4
			//zatrudnianie kupującego
			gracz[playerid][firma] = cid;
			gracz[playerid][firma_permlvl] = 2;
			gracz[playerid][firma_wyplata] = 0; 
			gracz[playerid][firma_onduty] = 0;
			gracz[playerid][firma_sessionid] = 0;
			mq_format("UPDATE `Konta` SET `firma`='%d', `firma_permlvl`='2', `firma_wyplata`='0' WHERE `id`='%d';", cid, gracz[playerid][UID]);
			mq_send("QUpdateCompanyData");

			company[cid][cny_owneruid] = gracz[playerid][UID];
			CompanySaveData(cid);

			new strTemp[1024];
			format(strTemp, 1024, ""COL_GREEN"« "COL_BLUE"SŁUŻBA W FIRMIE - "COL_RED"%s (ID: %d)"COL_GREEN"»\n", company[cid][cny_name], cid);
			format(strTemp, 1024, "%s"COL_GREEN"« "COL_YELLOW"WŁAŚCICIEL: "COL_RED"%s "COL_GREEN"»\n", strTemp, GetPlayerIGName(company[cid][cny_owneruid]));
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_ORANGE"PPM"COL_GREY" lub "COL_ORANGE"/cduty start"COL_GREY" aby rozpocząć pracę. "COL_RED"•\n", strTemp);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_ORANGE"PPM"COL_GREY" lub "COL_ORANGE"/cduty stop"COL_GREY" aby zakończyć pracę. "COL_RED"•\n", strTemp);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_ORANGE"/cduty info"COL_GREY" aby sprawdzić status służby. "COL_RED"•\n", strTemp);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_WHITE"/firma"COL_GREY" - panel firmy "COL_RED"•\n", strTemp);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_WHITE"/kontrakt status"COL_GREY" aby sprawdzić stan kontraktu"COL_GREY". "COL_RED"•\n", strTemp);
			UpdateDynamic3DTextLabelText(company[cid][cny_text3d], -1, strTemp);

			format(strOffer, 512, ""COL_WHITE"Gracz "COL_ORANGE"%s"COL_GREEN" przyjął "COL_WHITE"Twoją ofertę. Transakcja dobiegła końca, otrzymujesz "COL_GREEN"%d$"COL_WHITE".", nick(playerid), price);
			Dialog_Show(p, CNYSELLWAITEND, DIALOG_STYLE_MSGBOX,  ""COL_RED"•» "COL_WHITE"Firma sprzedana "COL_RED"«•", strOffer, "OK", "");
			format(strOffer, 512, ""COL_GREEN"Kupiłeś "COL_WHITE"firmę od "COL_ORANGE"%s"COL_WHITE" za "COL_BLUE"%d$"COL_WHITE".", nick(p), price);
			Dialog_Show(playerid, CNYSELLWAITEND, DIALOG_STYLE_MSGBOX,  ""COL_RED"•» "COL_WHITE"Firma kupiona "COL_RED"«•", strOffer, "OK", "");
			return 1;
		}
	}
	Error(playerid, "Ups! Coś się nie udało. Spróbujcie jeszcze raz...");
	return 1;
}


Dialog:CNYSELLWAIT(playerid, response, listitem, inputtext[])
{
	new clientid = GetPVarInt(playerid, "cache_cnysell_clientid");
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(p == clientid)
		{
			Dialog_Close(p);
			Dialog_Close(playerid);
			SetPVarInt(p, "cache_cnydeal_vendoruid", 0);
			LeftNotifyShow(p, "error", "Sprzedajacy ~r~anulowal~w~ oferte.", LN_RED);
			LeftNotifyShow(playerid, "Sukces!", "Oferta zostala ~r~anulowana~w~.", LN_RED);
			return 1;
		}
	}
	return 1;
}

Dialog:DEFINELISTWORKERSC(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	mq_format("SELECT `k`.`id`, `k`.`Nick`,`k`.`firma_kontrakt_kg`,`k`.`LastOnline`, `k`.`firma_permlvl`,FROM_UNIXTIME(`k`.`LastOnline`) `LastOnlineString`,AVG(`temp`.`kursy_per_wyplata`) `effectiveness`FROM (SELECT * FROM `Konta` WHERE `firma` = '%d') `k`LEFT JOIN (SELECT `lc`.`user_id` `uid`, `lc`.`kursy_per_wyplata`FROM `LogCompany` `lc`WHERE `lc`.`flag` = '3' AND `lc`.`kursy_per_wyplata` <> '-1' AND `lc`.`company_id` = '%d') `temp` ON `temp`.`uid`=`k`.`id`GROUP BY `k`.`id`;", cid, cid);
	mq_send("CompanyWorkerList", "d", playerid);
	return 1;
}

task CompanyWorkerList(playerid)
{
	mq_getdata();
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	//if(gracz[playerid][firma_permlvl] == 0) return Error(playerid, "Brak uprawnień.");
	if(rekordy)
	{
		new i;
		new strHeader[512];
		format(strHeader, 512, ""COL_RED"•» "COL_GREEN"Lista pracowników - %s "COL_WHITE"("COL_RED"%d"COL_WHITE"/"COL_GREEN"%d"COL_WHITE")"COL_RED" «•", company[cid][cny_name], rekordy, MAX_CWORKERS);
		
		new strWorkerList[3500];

		new t_id;
		new t_nick[24];
		new Float:t_avg;
		new t_permlvl;
		new t_kg_per_kontrakt;
		new t_lastonline;
		format(strWorkerList, 3500, ""COL_WHITE"Nick "COL_ORANGE"<skuteczność>"COL_WHITE"\tUprawnienia\tIlość ton (aktualny/ostatni kontrakt)\tOstatnio online\n");

		new count_listitem;
		while(i < rekordy)
		{
			cache_get_value_name_int(i, "id", 			t_id);
			cache_get_value_name(i, "Nick", t_nick, 24);
			cache_get_value_name_float(i, "effectiveness", 			t_avg);
			cache_get_value_name_int(i, "firma_permlvl", 			t_permlvl);
			cache_get_value_name_int(i, "firma_kontrakt_kg", 			t_kg_per_kontrakt);
			new Float:t_tons = float(t_kg_per_kontrakt)/1000.0;
			cache_get_value_name_int(i, "LastOnline", 			t_lastonline);
			new timeago = serwer[time_timestamp]-t_lastonline;
			new ta_d, ta_h, ta_m, ta_s;
			SecToTime(timeago, ta_d, ta_h, ta_m, ta_s);
			if(PlayerIsOnline(t_id))
			{
				format(strWorkerList, 3500, "%s"COL_WHITE"%s "COL_ORANGE"<%0.2f>"COL_WHITE"\t%s\t"COL_BLUE"%0.3f\t"COL_GREEN"[Online]\n", strWorkerList, t_nick, t_avg, PermLvlToStr(t_permlvl), t_tons, ta_d, ta_h, ta_m, ta_s);
			}
			else
			{
				format(strWorkerList, 3500, "%s"COL_WHITE"%s "COL_ORANGE"<%0.2f>"COL_WHITE"\t%s\t"COL_BLUE"%0.3f\t"COL_ORANGE"%d dni, %d godz, %d min, %d sek temu\n", strWorkerList, t_nick, t_avg, PermLvlToStr(t_permlvl), t_tons, ta_d, ta_h, ta_m, ta_s);
			}
			gui_cache[playerid][count_listitem][0] = t_id;//uid gracza
			count_listitem++;
			if(i >= 25) break;//zabezpieczenie przed wykrzaczeniem sie listy
			i++;
		}
		Dialog_Show(playerid, COMPANYWORKERSLIST, DIALOG_STYLE_TABLIST_HEADERS, strHeader, strWorkerList, "Wybierz", "Anuluj");
	}
	else Error(playerid, "Lista pracowników jest pusta.");
	return 1;
}

Dialog:COMPANYWORKERSLIST(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	if(gracz[playerid][firma_permlvl] == 0) return Error(playerid, "Brak uprawnień.");
	new target_uid = gui_cache[playerid][listitem][0];
	SetPVarInt(playerid, "company_manageworkeruid", target_uid);

	new t_permlvl;
	mq_format("SELECT `firma_permlvl` FROM `Konta` WHERE `id`='%d';", target_uid);
	new Cache:result = mysql_query(g_SQL, mQuery);
	if(cache_get_row_count_ex()) cache_get_value_name_int(0, "firma_permlvl",  t_permlvl);
	else return Error(playerid, "Wystąpił nieoczekiwany błąd.");
	cache_delete(result);
	SetPVarInt(playerid, "cache_t_permlvl", t_permlvl);

	//if(t_permlvl >= gracz[playerid][firma_permlvl] && gracz[playerid][firma_permlvl] != 2) return Error(playerid, "Brak uprawnień.");//lider może wszystko, a inni nie mogą zarządzać sobą jak mają te same upr lub cel ma wyższą

	new strCompanyMenu[1024];
	format(strCompanyMenu, 1024, ""COL_LIME"•»\t"COL_GREEN"Zmień stawkę\t"COL_LIME"«•");//0
	format(strCompanyMenu, 1024, "%s\n"COL_LIME"•»\t"COL_WHITE"Logi kursów\t"COL_LIME"«•", strCompanyMenu);//1
	format(strCompanyMenu, 1024, "%s\n"COL_LIME"•»\t"COL_WHITE"Logi wydatków "COL_GREY"[tutaj historia wynagrodzen]\t"COL_LIME"«•", strCompanyMenu);//2
	format(strCompanyMenu, 1024, "%s\n"COL_LIME"•»\t"COL_WHITE"Historia wypłat/wpłat na konto firmowe\t"COL_LIME"«•", strCompanyMenu);//3
	format(strCompanyMenu, 1024, "%s\n"COL_LIME"•»\t"COL_WHITE"Logi korzystania z pojazdów\t"COL_LIME"«•", strCompanyMenu);//4
	format(strCompanyMenu, 1024, "%s\n"COL_LIME"•»\t"COL_ORANGE"Zmień uprawnienia\t"COL_LIME"«•", strCompanyMenu); //5
	format(strCompanyMenu, 1024, "%s\n"COL_LIME"•»\t"COL_RED"Zwolnij\t"COL_LIME"«•", strCompanyMenu); //6
	new strHeader[512];
	format(strHeader, 512, ""COL_RED"•» "COL_GREEN"Ustawienia pracownika - "COL_ORANGE"%s (%d)"COL_RED" «•", GetPlayerIGName(target_uid), target_uid);
	Dialog_Show(playerid,COMPANYEDITWORKER, DIALOG_STYLE_TABLIST, strHeader, strCompanyMenu, "Wybierz", "Anuluj");
	return 1;
}

Dialog:COMPANYEDITWORKER(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	new target_uid = GetPVarInt(playerid, "company_manageworkeruid");
	new strEditWorker[1024];
	new strHeader[512];
	new t_permlvl = GetPVarInt(playerid, "cache_t_permlvl");//uprawnienia wybranym pracownikiem
	DeletePVar(playerid, "cache_t_permlvl");
	switch(listitem)
	{
		case 0://zmień stawkę
		{
			if(t_permlvl >= gracz[playerid][firma_permlvl] && gracz[playerid][firma_permlvl] != 2) return Error(playerid, "Brak uprawnień.");//lider może wszystko, a inni nie mogą zarządzać sobą jak mają te same upr lub cel ma wyższą
			new t_nick[24], t_wyplata;
			mq_format("SELECT `Nick`,`firma_wyplata` FROM `Konta` WHERE `id`='%d';", target_uid);
			new Cache:result = mysql_query(g_SQL, mQuery);
			if(cache_get_row_count_ex()) 
			{
				cache_get_value_name(0, "Nick", t_nick, 24);
				cache_get_value_name_int(0, "firma_wyplata", 				t_wyplata);
			} else return Error(playerid, "Wystąpił nieoczekiwany błąd.");
			cache_delete(result);

			format(strEditWorker, 1024, ""COL_WHITE"W tym miejscu możesz zmienić "COL_GREEN"stawkę"COL_WHITE" dla konkretnego pracownika.\n");
			format(strEditWorker, 1024, "%s"COL_WHITE"Pracownik otrzyma wypłatę za każde "COL_GREY"%d"COL_WHITE" minut spędzone na służbie.\n", strEditWorker, MAX_DUTYSESSION);
			format(strEditWorker, 1024, "%s"COL_WHITE"Minimalna wartość stawk to "COL_LIME"0$"COL_WHITE" a maksymalna "COL_RED"100 000$"COL_WHITE".\n", strEditWorker);
			format(strEditWorker, 1024, "%s"COL_WHITE"Aktualnie "COL_ORANGE"%s"COL_WHITE" na służbie otrzymuje co "COL_GREY"%d"COL_WHITE" minut wypłatę wysokości "COL_GREEN"%d$"COL_WHITE".\n\n", strEditWorker, t_nick, MAX_DUTYSESSION, t_wyplata);
			format(strEditWorker, 1024, "%s{8B8B8B}• domyślnie każdy nowo zatrudniony pracownik ma zerową stawkę.\n", strEditWorker);
			format(strEditWorker, 1024, "%s{8B8B8B}• ustawienie wartości na 0$ nie zablokuje wypłat score z aktualnego kontraktu.\n", strEditWorker);
			format(strEditWorker, 1024, "%s{8B8B8B}• środki są pobierane z konta firmowego.\n", strEditWorker);
			format(strEditWorker, 1024, "%s{8B8B8B}• pilnuj swoich pracowników, przeglądaj logi kursów, dobieraj wypłaty na podstawie skuteczności.\n", strEditWorker);
			format(strEditWorker, 1024, "%s{8B8B8B}• jeżeli na koncie firmowym nie ma środków na wypłaty, pracownik dostaje tylko score z kontraktu.\n", strEditWorker);
			format(strEditWorker, 1024, "%s{8B8B8B}• wszelkie udane i nieudane wypłaty znajdziesz w logach wydatków.\n\n", strEditWorker);
			format(strEditWorker, 1024, "%s"COL_WHITE"Podaj stawkę dla pracownika "COL_ORANGE"%s"COL_WHITE":", strEditWorker, t_nick);
			format(strHeader, 512, ""COL_RED"•» "COL_GREEN"Zmiana stawki - "COL_ORANGE"%s (%d)"COL_RED" «•", t_nick, target_uid);
			Dialog_Show(playerid, COMPANYSETWPRICE, DIALOG_STYLE_INPUT, strHeader, strEditWorker, "Ustaw", "Anuluj");
		}
		case 1:
		{
			format(strHeader, 512, "Kursy - %s (%d)", GetPlayerIGName(target_uid), target_uid);
			GetCompanyLogPlayer(playerid, target_uid, cid, CLOGFLAG_KURS, strHeader);
		}
		case 2://logi finansowe
		{
			format(strHeader, 512, "Wydatki - %s (%d)", GetPlayerIGName(target_uid), target_uid);
			GetCompanyLogPlayer(playerid, target_uid, cid, CLOGFLAG_WYDATEK, strHeader);
		}
		case 3://logi bank
		{
			format(strHeader, 512, "Historia wpłat/wypłat - %s (%d)", GetPlayerIGName(target_uid), target_uid);
			GetCompanyLogPlayer(playerid, target_uid, cid, CLOGFLAG_BANK, strHeader);
		}
		case 4:
		{
			format(strHeader, 512, "Używanie pojazdów - %s (%d)", GetPlayerIGName(target_uid), target_uid);
			GetCompanyLogPlayer(playerid, target_uid, cid, CLOGFLAG_POJAZD, strHeader);
		}
		case 5://zmiana uprawnien
		{
			if(gracz[playerid][firma_permlvl] != 2) return Error(playerid, "Brak uprawnień.");
			if(gracz[playerid][UID] == target_uid) return Error(playerid, "Nie możesz wykonać tej akcji na sobie.");
			strcat(strEditWorker, ""COL_LIME"•»\t"COL_GREY"Standard\t"COL_LIME"«•\n");
			strcat(strEditWorker, ""COL_LIME"•»\t"COL_ORANGE"V-Lider\t"COL_LIME"«•\n");
			format(strHeader, 512, ""COL_RED"•» "COL_GREEN"Modyfikacja uprawnień - "COL_ORANGE"%s (%d)"COL_RED" «•", GetPlayerIGName(target_uid), target_uid);
			Dialog_Show(playerid, COMPANYSETWPERM, DIALOG_STYLE_TABLIST, strHeader, strEditWorker, "Ustaw", "Anuluj");
		}
		case 6:
		{
			if(t_permlvl >= gracz[playerid][firma_permlvl] && gracz[playerid][firma_permlvl] != 2) return Error(playerid, "Brak uprawnień.");//lider może wszystko, a inni nie mogą zarządzać sobą jak mają te same upr lub cel ma wyższą
			if(gracz[playerid][UID] == target_uid) return Error(playerid, "Nie możesz wykonać tej akcji na sobie.");
			format(strHeader, 512, ""COL_RED"•» "COL_GREEN"Czy chcesz zwolnić "COL_ORANGE"%s (%d)"COL_GREEN"?"COL_RED" «•", GetPlayerIGName(target_uid), target_uid);
			format(strEditWorker, 1024, ""COL_RED"•» "COL_GREEN"Czy chcesz zwolnić "COL_ORANGE"%s (%d)"COL_GREEN"?"COL_RED" «•", GetPlayerIGName(target_uid), target_uid);
			Dialog_Show(playerid, COMPANYDELWORKER, DIALOG_STYLE_MSGBOX, strHeader, strEditWorker, "Zwolnij", "Anuluj");
		}
	}
	return 1;
}

Dialog:COMPANYSETWPRICE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new newpay = strval(inputtext);
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	if(newpay < 0) return Error(playerid, "Za niska stawka.");
	if(newpay > 100000) return Error(playerid, "Za wysoka stawka.");
	new target_uid = GetPVarInt(playerid, "company_manageworkeruid");
	mq_format("UPDATE `Konta` SET `firma_wyplata`='%d' WHERE `id`='%d';", newpay, target_uid);
	mq_send("QUpdateWorkerPay");
	SendClientMessageEx(playerid, COLOR_COMPANYMSG, "[C] Ustawiłeś stawkę dla "COL_ORANGE"%s"COL_CMSG" na "COL_GREEN"%d$"COL_CMSG".", GetPlayerIGName(target_uid), newpay);
	//jeśli gracz jest online...
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][UID] == target_uid)
			{
				gracz[p][firma_wyplata] = newpay;
				SendClientMessageEx(p, COLOR_COMPANYMSG, "[C] "COL_RED"Lider firmy ustawił Ci stawkę na "COL_GREEN"%d$"COL_CMSG".", gracz[p][firma_wyplata]);
				break;
			}
		}
	}
	return 1;
}

Dialog:COMPANYSETWPERM(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	new target_uid = GetPVarInt(playerid, "company_manageworkeruid");
	new new_permlvl = listitem;
	mq_format("UPDATE `Konta` SET `firma_permlvl`='%d' WHERE `id`='%d';", new_permlvl, target_uid);
	mq_send("QUpdateWorkerPerm");
	new strFmessage[144];
	format(strFmessage, 144, ""COL_ORANGE"%s"COL_WHITE" zmienił/a poziom uprawnień dla "COL_EASY"%s"COL_WHITE" na "COL_LIME"%s"COL_WHITE".", nick(playerid), GetPlayerIGName(target_uid), PermLvlToStr(new_permlvl));
	SendCompanyMessage(cid, strFmessage);
	//jeśli gracz jest online...
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][UID] == target_uid)
			{
				gracz[p][firma_permlvl] = new_permlvl;
				break;
			}
		}
	}
	return 1;
}

Dialog:COMPANYDELWORKER(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	new target_uid = GetPVarInt(playerid, "company_manageworkeruid");
	new strFmessage[144];
	format(strFmessage, 144, ""COL_ORANGE"%s"COL_RED" zwolnił/a "COL_EASY"%s"COL_WHITE".", nick(playerid), GetPlayerIGName(target_uid));
	SendCompanyMessage(cid, strFmessage);
	//sekcja offline
	mq_format("UPDATE `Konta` SET `firma`='0', `firma_permlvl`='0', `firma_wyplata`='0' WHERE `id`='%d';", target_uid);
	mq_send("QUpdateCompanyData");
	//jeśli gracz jest online...
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][UID] == target_uid)
			{
				gracz[p][firma] = 0;
				gracz[p][firma_permlvl] = 0;
				gracz[p][firma_wyplata] = 0; 
				gracz[p][firma_onduty] = 0;
				gracz[p][firma_sessionid] = 0;
				CargoInfo_Hide(p);
				ClearObjective(p);
				GameTextForPlayer(p, "~r~ZOSTALES ZWOLNIONY~n~Z FIRMY",  5000, 0);//4
				break;
			}
		}
	}
	return 1;
}

Dialog:ADDEXPIRECOMPANY(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	if(gracz[playerid][firma_permlvl] != 2) return Error(playerid, "Brak uprawnień.");
	if(company[cid][cny_money] < company[cid][cny_price]) return Error(playerid, "Brak takiej kwoty na koncie firmowym.");
	company[cid][cny_money] -= company[cid][cny_price];
	company[cid][cny_expire] = company[cid][cny_expire]+((60*60)*24)*COMPANY_KEEPDAYS;
	CompanySaveData(cid);
	LogCompany(cid, gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_WYDATEK, "Przedluzenie waznosci firmy. Koszt: %d$. Saldo: %d$", company[cid][cny_price], company[cid][cny_money]);
	Info(playerid, "Ważność Twojej firmy została przedłużona!");
	return 1;
}

Dialog:COMPANYCONTRACTLIST(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	if(gracz[playerid][firma_permlvl] == 0) return Error(playerid, "Brak uprawnień.");
	new c = gui_cache[playerid][listitem][0];//id kontraktu
	SetPVarInt(playerid, "cache_companycontractid", c);

	new strContractConfirm[3072];
	new strSrcZone[24], strDstZone[24];

	Get2DZone(load_place_van[ contract[c][cnt_fromid] ][0], load_place_van[ contract[c][cnt_fromid] ][1], strSrcZone, 32);
	Get2DZone(load_place_van[ contract[c][cnt_targetid] ][0], load_place_van[ contract[c][cnt_targetid] ][1], strDstZone, 32);
	new dd, hh, mm, ss;
	SecToTime(contract[c][cnt_time], dd, hh, mm, ss);

	format(strContractConfirm, 3072, ""COL_WHITE"Czy chcesz podpisać kontrakt? Jesteś przekonany, że Twoi ludzie dadzą radę?");
	format(strContractConfirm, 3072, "%s\n"COL_RED"» "COL_ORANGE"Szczegóły kontraktu, przeczytaj uważnie:", strContractConfirm);
	format(strContractConfirm, 3072, "%s\n"COL_ORANGE"• "COL_EASY"Towar: "COL_WHITE"%s %s", strContractConfirm, goods[contract[c][cnt_goodid]][gds_name], (goods[contract[c][cnt_goodid]][gds_adr] == true) ? (""COL_ORANGE"[ADR]") : (" "));
	format(strContractConfirm, 3072, "%s\n"COL_ORANGE"• "COL_EASY"Trasa: {00E16A}%s "COL_LIME"» [%0.1f km] » {FF4343}%s", strContractConfirm, strSrcZone, contract[c][cnt_distance], strDstZone);
	format(strContractConfirm, 3072, "%s\n"COL_ORANGE"• "COL_EASY"Ilość ładunku do przetransportowania: {00C5B6}%0.1f ton", strContractConfirm, (contract[c][cnt_size]/1000.0));
	format(strContractConfirm, 3072, "%s\n"COL_ORANGE"• "COL_EASY"Wynagrodzenie za wykonanie kontraktu: "COL_GREEN"%d$ "COL_EASY"i "COL_BLUE"%d score", strContractConfirm, contract[c][cnt_price], contract[c][cnt_score]);
	format(strContractConfirm, 3072, "%s\n"COL_ORANGE"• "COL_EASY"Czas na wykonanie kontraktu: "COL_ORANGE"%d dni, %d godz, %d min", strContractConfirm, dd, hh, mm);
	format(strContractConfirm, 3072, "%s\n"COL_ORANGE"• "COL_RED"*"COL_EASY"Kara, jeśli nie uda Ci się wykonać kontraktu na czas: "COL_RED"-%d$", strContractConfirm, contract[c][cnt_penalty]);
	format(strContractConfirm, 3072, "%s\n\n"COL_RED"*"COL_GREY" - Kara finansowa nie zostanie nałożona, jeśli saldo firmy jest na minusie.", strContractConfirm);
	format(strContractConfirm, 3072, "%s\n\n"COL_GREY"Prognozowana ilość kursów, przy 100%% załadunku, konkretnymi środkami transportu:"COL_GREY"\n", strContractConfirm);
	for(new t; t < 600; t++)
	{
		if(IsVehicleTruckSalonBanned(t)) continue;
		if(!TrailerCanTransportGood(t, goods[contract[c][cnt_goodid] ][gds_trailertype]) && IsVehicleTrailer(t)) continue;
		new vehCap = VehicleCapacity(t);
		if(vehCap != 0)
		{
			new Float:wynik = (contract[c][cnt_size])/float(vehCap);
			if(wynik < 1.0) wynik = 1.0;
			format(strContractConfirm, 3072, "%s"COL_GREY"- %s ("COL_YELLOW"~%dx"COL_GREY")\n", strContractConfirm, GetVehicleName(t), floatround(wynik));
		}
	}
	format(strContractConfirm, 3072, "%s\n\n"COL_WHITE"Nie odpowiada Ci ten kontrakt? Wprowadź w polu poniżej:", strContractConfirm);
	format(strContractConfirm, 3072, "%s\n"COL_LIME"losuj"COL_WHITE" - Aby wylosować inny kontrakt. Każdy los kosztuje "COL_RED"1500$"COL_WHITE".", strContractConfirm);
	format(strContractConfirm, 3072, "%s\n"COL_RED"• "COL_EASY" Bilans konta firmowego: "COL_GREEN"%d$", strContractConfirm, company[cid][cny_money]);
	format(strContractConfirm, 3072, "%s\n\n"COL_RED"Aby przyjąć kontrakt, musisz się podpisać. Wpisz w polu poniżej swój nick.", strContractConfirm);
	Dialog_Show(playerid, COMPANYCONTRACTCONF, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_WHITE"Potwierdzenie "COL_RED"«•", strContractConfirm, "Zatwierdz", "Wróć");
	return 1;
}

Dialog:COMPANYCONTRACTCONF(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid, "/firma");
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	if(gracz[playerid][firma_permlvl] == 0) return Error(playerid, "Brak uprawnień.");
	if(compare(inputtext, nick(playerid)))
	{
		new c = GetPVarInt(playerid, "cache_companycontractid");//id kontraktu
		DeletePVar(playerid, "cache_companycontractid");
		company[cid][cny_cnt_goodid] = contract[c][cnt_goodid];
		company[cid][cny_cnt_fromid] = contract[c][cnt_fromid];
		company[cid][cny_cnt_targetid] = contract[c][cnt_targetid];
		company[cid][cny_cnt_size] = contract[c][cnt_size];
		company[cid][cny_cnt_size_complet] =  0.0;
		company[cid][cny_cnt_price] = contract[c][cnt_price];
		company[cid][cny_cnt_penalty] = contract[c][cnt_penalty];
		company[cid][cny_cnt_score] = contract[c][cnt_score];
		company[cid][cny_cnt_time] = contract[c][cnt_time];
		company[cid][cny_cnt_time_left] = contract[c][cnt_time];
		company[cid][cny_cnt_distance] = contract[c][cnt_distance];
		company[cid][cny_cnt_signer_uid] = gracz[playerid][UID];
		company[cid][cny_cnt_signer_sid] = gracz[playerid][firma_sessionid];
		CompanySaveDataContract(cid);
		//reset firma_kontrakt_kg
		mq_format("UPDATE `Konta` SET `firma_kontrakt_kg`='0' WHERE `firma`='%d';", cid);
		mq_send("QUpdateCompKG");
		//jeśli gracz jest online...
		for(new p = PlayerPoolSize(); p != -1; p--)
		{
			if(gracz[p][loggedin])
			{
				if(gracz[p][firma] == cid)
				{
					gracz[p][firma_kontrakt_kg] = 0;
				}
			}
		}
		Info(playerid, "Kontrakt przyjęty! Status kontraktu znajdziesz w panelu firmy.");
		SendCompanyMessage(cid, "Zarząd firmy podpisał kontrakt. Wejdź do pojazdu/podczep naczepę, aby rozpocząć pracę.");
	}
	else if(compare(inputtext, "losuj"))
	{
		if(company[cid][cny_money] < 1500) 
		{
			dialog_COMPANYCONTRACTLIST(playerid, 1, 0, "null");
			return Error(playerid, "Niewystarczająca ilość pieniędzy na koncie firmowym.");
		}
		company[cid][cny_money] -= 1500;
		CompanySaveMoney(cid);
		LogCompany(cid, gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_WYDATEK, "Los - szukanie kontraktu. Koszt: 1500$. Saldo: %d$", company[cid][cny_money]);
		company[cid][cny_losk] = MRandom(MAX_CONTRACTS);
		gui_cache[playerid][0][0] = company[cid][cny_losk];
		//Info(playerid, "Wylosowano inny kontrakt.");
		dialog_COMPANYCONTRACTLIST(playerid, 1, 0, "null");
	}
	else Error(playerid, "Błąd w podpisie.");
	
	return 1;
}

Dialog:CSTATUSCONTRACT(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid, "/firma");
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	if(gracz[playerid][firma_permlvl] == 0) return Error(playerid, "Brak uprawnień.");
	if(compare(inputtext, "anuluj"))
	{
		if(company[cid][cny_money] < 0)
		{
			Info(playerid, "Kontrakt został anulowany, na Twoją firmę nie nałożono kary finansowej, ponieważ saldo jest na minusie.");
		}
		else
		{
			company[cid][cny_money] -= company[cid][cny_cnt_penalty];
			CompanySaveMoney(cid);
			LogCompany(cid, gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_WYDATEK, "Kara finansowa - anulowany kontrakt. Koszt: %d$. Saldo: %d$", company[cid][cny_cnt_penalty], company[cid][cny_money]);
			Info(playerid, "Kontrakt został anulowany, na Twoją firmę została nałożona kara finansowa.");
		}
		ResetCompanyContractRam(cid);
		CompanySaveDataContract(cid);
	}
	return 1;
}


forward QCompanyVehicleList(playerid);//lista pojazdów firmowych
public QCompanyVehicleList(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new strList[3072];
		new strTitle[256];
		new carlist_cache[MAX_CVEHICLES][4];
		new i;
		format(strList, 3072, "UID\tPojazd");
		while(i < rekordy)
		{
			cache_get_value_name_int(i, "id", 			carlist_cache[i][0]);
			cache_get_value_name_int(i, "model", 			carlist_cache[i][1]);
			i++;
		}
		i = 0;
		///sortowanie
		for(new s; s < MAX_CVEHICLES; s++) 
		{
			if(carlist_cache[s][0] == 0) continue;
			if(IsVehicleTruck(carlist_cache[s][1])) 
			{
				gui_cache[playerid][i][0] = carlist_cache[s][0];
				gui_cache[playerid][i][1] = carlist_cache[s][1];
				format(strList, 3072, "%s\n{747474}%d\t[TRUCK] %s", strList, gui_cache[playerid][i][0], GetVehicleName(gui_cache[playerid][i][1]));
				i++;
			}
		}
		for(new s; s < MAX_CVEHICLES; s++) 
		{
			if(carlist_cache[s][0] == 0) continue;
			if(!IsVehicleTruck(carlist_cache[s][1])) 
			{
				gui_cache[playerid][i][0] = carlist_cache[s][0];
				gui_cache[playerid][i][1] = carlist_cache[s][1];
				format(strList, 3072, "%s\n{747474}%d\t%s\t%s", strList, gui_cache[playerid][i][0], GetVehicleName(gui_cache[playerid][i][1]));
				i++;
			}
		}
		new cid = gracz[playerid][firma];
		format(strTitle, 256, ""COL_RED"•» "COL_WHITE"Lista pojazdów firmowych "COL_BLUE"["COL_GREEN"%d"COL_WHITE"/"COL_RED"%d"COL_BLUE"] "COL_RED"«•", CompanyVehiclesCount(cid), MAX_CVEHICLES);
		Dialog_Show(playerid, COMPANYVEHS, DIALOG_STYLE_TABLIST_HEADERS, strTitle, strList, "Wybierz", "Wróć");
	}
	else Error(playerid, "Brak pojazdów w firmie.");
	return 1;
}

Dialog:COMPANYADDP(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid, "/firma");
	new targetid = strval(inputtext);
	if(gracz[targetid][firma] != 0) return Error(playerid, "Ten gracz należy do innej firmy.");
	new cid = gracz[playerid][firma];
	new Float:pPos[3];
	GetPlayerPos(targetid, pPos[0], pPos[1], pPos[2]);
	if(IsPlayerInRangeOfPoint(playerid, 4.0, pPos[0], pPos[1], pPos[2]))
	{
		new strInv[512];
		format(strInv, 512, ""COL_WHITE"Czy akceptujesz zaproszenie do firmy "COL_BLUE"%s"COL_WHITE"?", company[cid][cny_name]);
		Dialog_Show(targetid, COMPANYINVA, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_WHITE"Zaproszenie do firmy "COL_RED"«•", strInv, "Akceptuj", "Odrzuc");
		SetPVarInt(targetid, "COMPANY_INV", cid);
		Info(playerid, "Zaproszenie do firmy zostało wysłane.");
	}
	else Error(playerid, "Ten gracz nie znajduje się w pobliżu Ciebie.");
	return 1;
}

Dialog:COMPANYINVA(playerid, response, listitem, inputtext[])//TARGETID
{
	if(!response) return 1;
	if(gracz[playerid][firma] != 0) return Error(playerid, "Należysz do innej firmy.");
	gracz[playerid][firma] = GetPVarInt(playerid, "COMPANY_INV");
	gracz[playerid][firma_permlvl] = 0; 
	gracz[playerid][firma_wyplata] = 0;
	gracz[playerid][firma_kontrakt_kg] = 0;
	SavePlayerCompanyData(playerid);//zapis danych
	new strMessage[144];
	format(strMessage, 144, ""COL_WHITE"Do firmy został zatrudniony nowy pracownik: "COL_GREEN"%s"COL_WHITE"(%d).", nick(playerid), playerid);
	SendCompanyMessage(gracz[playerid][firma], strMessage);
	Info(playerid, "Zostałeś zatrudniony! Wszelkie dostępne komendy znajdziesz pod "COL_GREEN"/pomoc"COL_WHITE".");
	SendClientMessageEx(playerid, COLOR_COMPANYMSG, "[C]"COL_RED" Zapamietaj!!! "COL_WHITE"Wszelkie wiadomości poprzedzone tagiem {%06x}[C]"COL_WHITE", to wiadomości firmowe.", COLOR_COMPANYMSG >>> 8);
	SavePlayerCompanyData(playerid);
	return 1;
}

Dialog:COMPANYSETMOTD(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	new motd_escape[100];
	format(motd_escape, 100, inputtext);
	mysql_escape_string(motd_escape, motd_escape);

	mq_format("UPDATE `firmy` SET `motd`='%s' WHERE `id`='%d';", motd_escape, cid);
	mq_send("QUpdateMotd");
	if(strlen(inputtext) > 1)
	{
		new strNewMessage[144];
		format(strNewMessage, 144, ""COL_WHITE"%s", motd_escape);
		SendCompanyMessage(cid, "••••••••••••••••••••••••••••••••••••••••» "COL_RED"Zmiana wiadomości dnia - Firma"COL_CMSG"«••••••••••••••••••••••••••••••••••••••••");
		SendCompanyMessage(cid, strNewMessage);
		SendCompanyMessage(cid, "••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••");
	}
	return 1;
}


Dialog:COMPANYVEHS(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid, "/firma");
	new strTitle[128], strList[512];
	gracz[playerid][gui_listitem] = listitem;
	format(strList, 512, ""COL_LIME"•»\t"COL_EASY"Namierz\t"COL_LIME"«•");
	format(strList, 512, "%s\n"COL_LIME"•»\t"COL_EASY"Zrespawnuj\t"COL_LIME"«•", strList);
	if(IsVehicleTrailer(gui_cache[playerid][listitem][1])) format(strList, 512, "%s\n"COL_LIME"•»\t"COL_RED"Sprzedaj naczepę\t"COL_LIME"«•", strList);
	else format(strList, 512, "%s\n"COL_LIME"•»\t"COL_RED"Przypisz pojazd do swojego konta\t"COL_LIME"«•", strList);
	format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Zarządzanie pojazdem "COL_ORANGE"%s(%d) "COL_RED"«•", GetVehicleName(gui_cache[playerid][listitem][1]), gui_cache[playerid][listitem][0]);
	format(strList, 512, "%s\n"COL_LIME"•»\t"COL_EASY"Logi pojazdu\t"COL_LIME"«•", strList);
	Dialog_Show(playerid, CVEHMENU, DIALOG_STYLE_TABLIST, strTitle, strList, "Wybierz", "Wróć");
	return 1;
}

Dialog:CVEHMENU(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid, "/firma");
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	if(gracz[playerid][firma_permlvl] == 0) return Error(playerid, "Brak uprawnień.");

	new selected = gracz[playerid][gui_listitem];
	new vehicleid = VehicleUidToVehicleid(gui_cache[playerid][selected][0]);
	if(vehicleid == -1) return Error(playerid, "Wystąpił nieoczekiwany błąd. Pojazd nie istnieje na mapie.");
	switch(listitem)
	{
		case 0:
		{
			new Float:pos[3];
			GetVehiclePos(vehicleid, pos[0], pos[1], pos[2]);
			SetPlayerCheckpoint(playerid, pos[0], pos[1], pos[2]-0.4, 5.0);
			Info(playerid, "Pojazd został zaznaczony "COL_RED"czerwonym"COL_WHITE" punktem na mapie.");
			LeftNotifyShow(playerid, "Sukces!", "Pojazd zostal zaznaczony ~r~czerwonym~w~ punktem na mapie.", LN_GREEN);
		}
		case 1:
		{
			RespawnVehicle(vehicleid, true);
			LeftNotifyShow(playerid, "Sukces!", "Pojazd zostal ~g~zrespawnowany~w~.", LN_GREEN);
		}
		case 2://przypis pojazdu do konta gracza
		{
			if(IsVehicleTrailer(gui_cache[playerid][selected][1])) 
			{
				if(vehicleid != -1)
				{
					new Float:vPos[3];
					GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
					if(IsPlayerInRangeOfPoint(playerid, 8.0, vPos[0], vPos[1], vPos[2]))
					{
						new strTitle[128];
						format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Sprzedaż pojazdu "COL_ORANGE"%s(%d) "COL_RED"«•", GetVehicleName(gui_cache[playerid][selected][1]), gui_cache[playerid][selected][0]);
						Dialog_Show(playerid, COMPVEHSELLTYPE, DIALOG_STYLE_TABLIST, strTitle, ""COL_LIME"•»\t{00FF00}Sprzedaj innej firmie"COL_RED"[obecnie niedostępne] \t"COL_LIME"«•\n"COL_LIME"•»\t{FF0000}Sprzedaj na złom "COL_GREY"[90% wartości pojazdu]\t"COL_LIME"«•", "Wybierz", "Anuluj");
					} 
					else Error(playerid, "Jesteś za daleko od pojazdu.");
				}
				else Error(playerid, "Ten pojazd nie jest stworzony.");
			}
			else
			{
				if(PlayerAllCarsCount(playerid) >= MaxVehiclesPlayer(playerid)) return Error(playerid, "Posiadasz już maxymalną ilość pojazdów.");
				if(PlayerCreatedCarsCount(playerid) >= MAX_PRIVCARSCREATED) return Error(playerid, "Masz już maxymalną ilość pojazdów stworzonych na mapie.");
				if(pojazd[vehicleid][v_cargo] != 0) return Error(playerid, "Pojazd jest załadowany."); 
				pojazd[vehicleid][v_owner_type] = VEHICLE_PLAYER;
				pojazd[vehicleid][v_owner] = gracz[playerid][UID];
				if(pojazd[vehicleid][v_id] != 0)
				{ 
					mq_format("UPDATE `pojazdy` SET `owner_type`='%d', `owner`='%d' WHERE `id`='%d';", VEHICLE_PLAYER, gracz[playerid][UID], gui_cache[playerid][selected][0]);
					mq_send("QTransferCompToPriv");
				}
				new strInfo[1024];
				format(strInfo, 1024, ""COL_WHITE"Przypisałeś pojazd firmowy "COL_LIME"%s"COL_WHITE" należący do firmy "COL_RED"%s"COL_WHITE" do swojego konta.", GetVehicleName(gui_cache[playerid][selected][1]), company[cid][cny_name]);
				format(strInfo, 1024, "%s\n"COL_WHITE"Listę pojazdów przypisanych do Twojego konta znajdziesz pod "COL_BLUE"/v lista"COL_WHITE".", strInfo);
				MessageGUIEx(playerid, ""COL_RED"•» "COL_GREEN"Sukces! "COL_RED"«•",  strInfo);
			}
		}
		case 3://logi pojazdu
		{
			new titleLog[128];
			format(titleLog, 128, "%s(%d)", GetVehicleName(pojazd[vehicleid][v_model]), gui_cache[playerid][selected][0]);
			GetCompanyLog(playerid, cid, CLOGFLAG_POJAZD, titleLog, gui_cache[playerid][selected][0]);
		}
	}
	return 1;
}


forward QPrivVehToCompany(playerid);//przypisywanie prywatnych aut do firmy
public QPrivVehToCompany(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new strList[3072];
		new strTitle[256];
		new carlist_cache[MAX_PRIVCARS_CONST][4];
		new i;
		format(strList, 3072, "UID\tPojazd\tStatus");
		while(i < rekordy)
		{
			//last string\nid, nazwa, status
			/*cache_get_value_name_int(i, "id", 			gui_cache[playerid][i][0]);
			cache_get_value_name_int(i, "model", 			gui_cache[playerid][i][1]);
			cache_get_value_name_int(i, "status", 			gui_cache[playerid][i][2]);*/
			cache_get_value_name_int(i, "id", 			carlist_cache[i][0]);
			cache_get_value_name_int(i, "model", 			carlist_cache[i][1]);
			cache_get_value_name_int(i, "status", 			carlist_cache[i][2]);
			//format(strList, 3072, "%s\n{000000}%d\t%s\t%s", strList, gui_cache[playerid][i][0], GetVehicleName(gui_cache[playerid][i][1]), VehicleStatus(gui_cache[playerid][i][2]));
			i++;
		}
		i = 0;
		///sortowanie
		for(new s; s < MAX_PRIVCARS_CONST; s++) 
		{
			if(carlist_cache[s][0] == 0) continue;
			if(IsVehicleTruck(carlist_cache[s][1])) 
			{
				gui_cache[playerid][i][0] = carlist_cache[s][0];
				gui_cache[playerid][i][1] = carlist_cache[s][1];
				gui_cache[playerid][i][2] = carlist_cache[s][2];
				format(strList, 3072, "%s\n{000000}%d\t[TRUCK] %s\t%s", strList, gui_cache[playerid][i][0], GetVehicleName(gui_cache[playerid][i][1]), VehicleStatus(gui_cache[playerid][i][2]));
				i++;
			}
		}
		for(new s; s < MAX_PRIVCARS_CONST; s++) 
		{
			if(carlist_cache[s][0] == 0) continue;
			if(!IsVehicleTruck(carlist_cache[s][1])) 
			{
				gui_cache[playerid][i][0] = carlist_cache[s][0];
				gui_cache[playerid][i][1] = carlist_cache[s][1];
				gui_cache[playerid][i][2] = carlist_cache[s][2];
				format(strList, 3072, "%s\n{000000}%d\t%s\t%s", strList, gui_cache[playerid][i][0], GetVehicleName(gui_cache[playerid][i][1]), VehicleStatus(gui_cache[playerid][i][2]));
				i++;
			}
		}
		format(strTitle, 256, ""COL_RED"•» "COL_WHITE"Który pojazd chcesz przypisać? "COL_RED"«•");
		Dialog_Show(playerid, PVEHTOCOMP, DIALOG_STYLE_TABLIST_HEADERS, strTitle, strList, "Przypisz", "Anuluj");
	}
	else Error(playerid, "Nie posiadasz żadnego pojazdu.");
	return 1;
}

Dialog:PVEHTOCOMP(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	gracz[playerid][gui_listitem] = listitem;
	new selected = gracz[playerid][gui_listitem];
	new vehicleid = VehicleUidToVehicleid(gui_cache[playerid][selected][0]);
	if(vehicleid == -1) return Error(playerid, "Pojazd musi być stworzony ma mapie.");
	if(!PosRangeOfCompany(cid, pojazd[vehicleid][v_X], pojazd[vehicleid][v_Y], pojazd[vehicleid][v_Z])) return Error(playerid, "Pojazd musi być zaparkowany na terenie Twojej firmy.");
	if(CompanyVehiclesCount(cid) >= MAX_CVEHICLES) return Error(playerid, "Posiadasz już maxymalną ilość pojazdów w firmie.");
	if(pojazd[vehicleid][v_cargo] != 0) return Error(playerid, "Pojazd jest załadowany."); 
	pojazd[vehicleid][v_owner_type] = VEHICLE_BUSINESS;
	pojazd[vehicleid][v_owner] = cid;
	if(pojazd[vehicleid][v_id] != 0)
	{	
		mq_format("UPDATE `pojazdy` SET `owner_type`='%d', `owner`='%d' WHERE `id`='%d';", VEHICLE_BUSINESS, cid, gui_cache[playerid][selected][0]);
		mq_send("QTransferPrivToCompany");
	}
	new strInfo[1024];
	format(strInfo, 1024, ""COL_WHITE"Przypisałeś pojazd prywatny "COL_LIME"%s"COL_WHITE" do firmy "COL_RED"%s"COL_WHITE".", GetVehicleName(gui_cache[playerid][selected][1]), company[cid][cny_name]);
	format(strInfo, 1024, "%s\n"COL_WHITE"Od teraz wszyscy pracownicy firmy mogą prowadzić ten pojazd.", strInfo);
	format(strInfo, 1024, "%s\n"COL_WHITE""COL_WHITE"Pojazd możesz z powrotem przypisać na swoją własność korzystając z listy pojazdów firmy.", strInfo);
	format(strInfo, 1024, "%s\n"COL_WHITE""COL_WHITE"Pojazdy firmowe możesz parkować tylko na terenie firmy.", strInfo);
	MessageGUIEx(playerid, ""COL_RED"•» "COL_GREEN"Sukces! "COL_RED"«•",  strInfo);
	return 1;
}



Dialog:COMPVEHSELLTYPE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	new selected = gracz[playerid][gui_listitem];
	new vehicleid = VehicleUidToVehicleid(gui_cache[playerid][selected][0]);
	if(vehicleid == -1) return Error(playerid, "Pojazd musi być stworzony ma mapie.");
	switch(listitem)
	{
		case 0:
		{
			Info(playerid, "Opcja zostanie odblokowana w przyszłości. Jak wprowadzimy awarie dla naczep :)");
		}
		case 1:
		{
			const Float:price_proc = 90.0;
			new Float:vehicle_price = CalcVehiclePriceEx(pojazd[vehicleid][v_model]);
			new Float:final_price = price_proc*vehicle_price/100.0;
			new strSell[1024];
			format(strSell, 1024, ""COL_WHITE"Czy jesteś pewien, że chcesz sprzedać pojazd "COL_BLUE"%s"COL_WHITE" za "COL_RED"%d%%"COL_WHITE" jego wartości rynkowej?", GetVehicleName(pojazd[vehicleid][v_model]), floatround(price_proc));
			format(strSell, 1024, "%s\nCena rynkowa tego pojazdu to: "COL_ORANGE"%d$"COL_WHITE"", strSell, floatround(vehicle_price));
			format(strSell, 1024, "%s\n"COL_RED"%d%%"COL_WHITE" ceny rynkowej tego pojazdu to: "COL_GREEN"%d$"COL_WHITE"", strSell, floatround(price_proc), floatround(final_price));
			format(strSell, 1024, "%s\n\nJeśli chcesz sprzedać pojazd "COL_BLUE"%s"COL_WHITE" za "COL_GREEN"%d$"COL_WHITE" wpisz poniżej: "COL_LIME"sprzedaje", strSell, GetVehicleName(pojazd[vehicleid][v_model]), floatround(final_price));
			Dialog_Show(playerid, COMPVEHSELLSCRAP, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_WHITE"Sprzedaż pojazdu na złom "COL_RED"«•", strSell, "Potwierdz", "Anuluj");
			SetPVarInt(playerid, "cache_cardeal_price", floatround(final_price));
		}
	}
	return 1;
}


Dialog:COMPVEHSELLSCRAP(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	if(gracz[playerid][firma_permlvl] == 0) return Error(playerid, "Brak uprawnień.");
	if(!compare(inputtext, "sprzedaje"))
	{
		Error(playerid, "Pojazd nie został sprzedany.");
		return 1;
	}
	new selected = gracz[playerid][gui_listitem];
	new vehicleid = VehicleUidToVehicleid(gui_cache[playerid][selected][0]);
	if(vehicleid != -1)
	{
		new Float:vPos[3];
		GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
		if(IsPlayerInRangeOfPoint(playerid, 8.0, vPos[0], vPos[1], vPos[2]))
		{
			new strOffer[512];
			format(strOffer, 512, ""COL_GREEN"Sprzedałeś "COL_WHITE"pojazd "COL_ORANGE"%s"COL_WHITE" za "COL_GREEN"%d$"COL_WHITE".\n"COL_GREEN"INFO: "COL_WHITE"Kwota trafiła na konto firmy.", GetVehicleName(pojazd[vehicleid][v_model]), GetPVarInt(playerid, "cache_cardeal_price"));
			Dialog_Show(playerid, CARSELLWAITEND, DIALOG_STYLE_MSGBOX,  ""COL_RED"•» "COL_WHITE"Pojazd sprzedany "COL_RED"«•", strOffer, "OK", "");
			mq_format("DELETE FROM `pojazdy` WHERE `id`='%d';", gui_cache[playerid][selected][0]);
			mq_send("QDeleteVehicle");
			RemoveVehicle(vehicleid);
			company[cid][cny_money] += GetPVarInt(playerid, "cache_cardeal_price");
			CompanySaveData(cid);
		} 
		else Error(playerid, "Jesteś za daleko od pojazdu.");
	}
	else Error(playerid, "Ten pojazd nie jest stworzony.");
	return 1;
}


Dialog:MONEYCOMPANY(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid, "/firma");
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	if(gracz[playerid][firma_permlvl] == 0) return Error(playerid, "Brak uprawnień.");
	switch(listitem)
	{
		case 0://Wpłaty wypłaty
		{
			GetCompanyLog(playerid, cid, CLOGFLAG_BANK, "Wpłaty i wypłaty");
		}
		case 1://Wydatki
		{
			GetCompanyLog(playerid, cid, CLOGFLAG_WYDATEK, "Wydatki");
		}
		case 2://Wpłata gotówki
		{
			Dialog_Show(playerid, MONEYCPLUSMINUS, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_GREEN"WPŁATA GOTÓWKI "COL_RED"«•", ""COL_GREEN"Ile chcesz wpłacić "COL_GREY"(1$ - 500 000$)"COL_GREEN"?", "Wykonaj", "Wróć");
			SetPVarInt(playerid, "MONEYCPM", 1);
		}
		case 3://Wypłata gotówki
		{
			Dialog_Show(playerid, MONEYCPLUSMINUS, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_RED"WYPŁATA GOTÓWKI "COL_RED"«•", ""COL_RED"Ile chcesz wypłacić "COL_GREY"(1$ - 500 000$)"COL_RED"?", "Wykonaj", "Wróć");
			SetPVarInt(playerid, "MONEYCPM", 2);
		}
	}
	return 1;
}

stock GetCompanyLog(playerid, company_id, flag, title[], vehuid = 0, page = 0)
{
	if(vehuid == 0) mq_format("SELECT `lc`.*,`k`.`Nick` FROM `LogCompany` `lc` LEFT JOIN `Konta` `k` ON `lc`.`user_id`=`k`.`id` WHERE `lc`.`company_id`='%d' AND `lc`.`flag`='%d' ORDER BY `lc`.`id` DESC LIMIT %d,15;", company_id, flag, page);
	else mq_format("SELECT `lc`.*,`k`.`Nick` FROM `LogCompany` `lc` LEFT JOIN `Konta` `k` ON `lc`.`user_id`=`k`.`id` WHERE `lc`.`company_id`='%d' AND `lc`.`flag`='%d' AND `lc`.`data` LIKE '%%Pojazd: %%(UID: %d)%%'  ORDER BY `lc`.`id` DESC LIMIT %d,15;", company_id, flag, vehuid, page);
	mq_send("ShowCompanyLog", "d", playerid);
	//print(mQuery);
	SetPVarString(playerid, "GetCompanyLog_Title", title);
	gracz[playerid][cmp_showlog_page] = page;
	gracz[playerid][cmp_showlog_targetuid] = 0;
	gracz[playerid][cmp_showlog_flag] = flag;
	gracz[playerid][cmp_showlog_vehuid] = vehuid;
	return 1;
}

stock GetCompanyLogPlayer(playerid, targetuid, company_id, flag, title[], page = 0)
{
	mq_format("SELECT `lc`.*,`k`.`Nick` FROM `LogCompany` `lc` LEFT JOIN `Konta` `k` ON `lc`.`user_id`=`k`.`id` WHERE `lc`.`company_id`='%d' AND `lc`.`flag`='%d' AND `lc`.`user_id`='%d' ORDER BY `lc`.`id` DESC LIMIT %d,15;", company_id, flag, targetuid, page);
	mq_send("ShowCompanyLog", "d", playerid);
	SetPVarString(playerid, "GetCompanyLog_Title", title);
	gracz[playerid][cmp_showlog_page] = page;
	gracz[playerid][cmp_showlog_targetuid] = targetuid;
	gracz[playerid][cmp_showlog_flag] = flag;
	gracz[playerid][cmp_showlog_vehuid] = 0;
	return 1;
}

task ShowCompanyLog(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new t_user_nick[32], t_duty_session_id, t_data[256], t_timestamp[32];
		new strTitle[128];
		new temp_title[32];
		GetPVarString(playerid, "GetCompanyLog_Title", temp_title, 32);
		format(strTitle, 128, ""COL_RED"•» "COL_GREEN"Logi firmowe - "COL_WHITE"%s "COL_RED"«•", temp_title);
		new strCompanyLog[3072];
		format(strCompanyLog, 3072, "Data\tGracz (ID sesji)\tZdarzenie");
		
		if(gracz[playerid][cmp_showlog_page] != 0) format(strCompanyLog, 3072, "%s\n««««\t««««\t««««", strCompanyLog);
		new i;
		while(i < rekordy)
		{
			cache_get_value_name(i, "Nick", t_user_nick, 32);
			cache_get_value_name_int(i, "duty_session_id", 			t_duty_session_id);
			cache_get_value_name(i, "data", t_data, 256);
			cache_get_value_name(i, "timestamp", t_timestamp, 32);
			format(strCompanyLog, 3072, "%s\n%s\t%s (SID: %d)\t%s", strCompanyLog, t_timestamp, t_user_nick, t_duty_session_id, t_data);
			i++;
		}
		if(i >= 15) format(strCompanyLog, 3072, "%s\n»»»»\t»»»»\t»»»»", strCompanyLog);
		Dialog_Show(playerid, COMPANYLOG, DIALOG_STYLE_TABLIST_HEADERS, strTitle, strCompanyLog, "OK", "Wróć");
	}
	else Error(playerid, "Brak danych.");
	return 1;
} 

Dialog:COMPANYLOG(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		gracz[playerid][cmp_showlog_page] = 0;
		gracz[playerid][cmp_showlog_targetuid] = 0;
		gracz[playerid][cmp_showlog_flag] = 0;
		gracz[playerid][cmp_showlog_vehuid] = 0;
		PC_EmulateCommand(playerid, "/firma");
		return 1;
	}
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	new temp_title[32];
	GetPVarString(playerid, "GetCompanyLog_Title", temp_title, 32);
	if(compare(inputtext, "»»»»"))//NEXT
	{
		gracz[playerid][cmp_showlog_page] += 15;
	}
	else if(compare(inputtext, "««««"))//PREV
	{
		gracz[playerid][cmp_showlog_page] -= 15;
		if(gracz[playerid][cmp_showlog_page] < 0) gracz[playerid][cmp_showlog_page] = 0;
	}
	if(gracz[playerid][cmp_showlog_targetuid] == 0)
	{
		GetCompanyLog(playerid, cid, gracz[playerid][cmp_showlog_flag], temp_title, gracz[playerid][cmp_showlog_vehuid], gracz[playerid][cmp_showlog_page]);
	}
	else
	{
		GetCompanyLogPlayer(playerid, gracz[playerid][cmp_showlog_targetuid], cid, gracz[playerid][cmp_showlog_flag], temp_title, gracz[playerid][cmp_showlog_page]);
	}
	return 1;
}

Dialog:MONEYCPLUSMINUS(playerid, response, listitem, inputtext[])
{
	if(!response) return dialog_COMPANYMENU(playerid, 1, 8, "null");
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	if(gracz[playerid][firma_permlvl] == 0) return Error(playerid, "Brak uprawnień.");
	new value = strval(inputtext);
	if(value < 0) return Error(playerid, "Kwota nie może być mniejsza niż 0$.");
	if(value > 500000) return Error(playerid, "Kwota nie może być większa niż 500 000$.");
	switch(GetPVarInt(playerid, "MONEYCPM"))
	{
		case 1://WPŁATA
		{
			if(value > Money(playerid)) return Error(playerid, "Nie posiadasz przy sobie tyle gotówki.");
			company[cid][cny_money] += value;
			TakeMoney(playerid, value);
			SendClientMessageEx(playerid, COLOR_COMPANYMSG, "[C]"COL_GREEN" Wpłaciłeś "COL_ORANGE"%d$ "COL_WHITE"(Saldo: %d$)"COL_GREEN" na konto firmowe.", value, company[cid][cny_money]);
			CompanySaveData(cid);
			LogCompany(cid, gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_BANK, "Wplata gotowki: %d$. Saldo: %d$", value, company[cid][cny_money]);
		}
		case 2://WYPŁATA
		{
			if(value > company[cid][cny_money]) return Error(playerid, "Na koncie firmowym nie znajduje się tak duża kwota.");
			company[cid][cny_money] -= value;
			GiveMoney(playerid, value);
			SendClientMessageEx(playerid, COLOR_COMPANYMSG, "[C]"COL_RED" Wypłaciłeś "COL_ORANGE"%d$ "COL_WHITE"(Saldo: %d$)"COL_RED" z konta firmowego.", value, company[cid][cny_money]);
			CompanySaveData(cid);
			LogCompany(cid, gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_BANK, "Wyplata gotowki: %d$. Saldo: %d$", value, company[cid][cny_money]);
		}
	}
	return 1;
}

task Process_CompanyContract()
{
	for(new cid; cid < MAX_COMPANY; cid++)
	{
		new dd, hh, mm, ss;
		if(company[cid][cny_cnt_price] != 0)
		{
			if(company[cid][cny_cnt_time_left] > 0)
			{
				company[cid][cny_cnt_time_left]--;
				SecToTime(company[cid][cny_cnt_time_left], dd, hh, mm, ss);
				if(ss == 1) CompanySaveDataContract(cid);
			}
			else
			{
				SendCompanyMessage(cid, "Firma nie wyrobiła się na czas z wykonaniem kontraktu.");
				if(company[cid][cny_money] >= 0)
				{
					company[cid][cny_money] -= company[cid][cny_cnt_penalty];
					CompanySaveMoney(cid);
					LogCompany(cid, company[cid][cny_cnt_signer_uid], company[cid][cny_cnt_signer_sid], CLOGFLAG_WYDATEK, "Kara finansowa - uplynal czas wykonania kontraktu. Koszt: %d$. Saldo: %d$", company[cid][cny_cnt_penalty], company[cid][cny_money]);
				}
				ResetCompanyContractRam(cid);
				CompanySaveDataContract(cid);
			}
		}
	}
	return 1;
}

task Company_OnPlayerStateChange(playerid, newstate, oldstate)
{
	new vehicleid = GetPlayerVehicleID(playerid);
	if(pojazd[vehicleid][v_owner_type] != VEHICLE_BUSINESS) return 1;//ważne
	new cid = gracz[playerid][firma];
	new strObjective[512];
	format(strObjective, 512, ""COL_RED"• "COL_EASY"Towar: "COL_BLUE"%s "COL_RED"•\n"COL_RED"• "COL_EASY"Przetransportowano: "COL_GREEN"%0.1f"COL_EASY"/"COL_RED"%0.1f {00C5B6}ton "COL_LIME"[%d%%] "COL_RED"•\n"COL_RED"• "COL_BLUE"Aby załadować wpisz: "COL_GREEN"/kontrakt zaladuj"COL_GREY" [lub klawisz H] "COL_RED"•", goods[company[cid][cny_cnt_goodid]][gds_name], (company[cid][cny_cnt_size_complet]/1000), (company[cid][cny_cnt_size]/1000), procent(company[cid][cny_cnt_size_complet], company[cid][cny_cnt_size]));
	if(oldstate == PLAYER_STATE_ONFOOT && newstate == PLAYER_STATE_DRIVER)//z piechoty na kierowce
	{
		if(IsPlayerCanDrive(playerid, vehicleid))
		{
			LogCompany(cid, gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_POJAZD, "Użycie. Pojazd: %s(UID: %d)", GetVehicleName(pojazd[vehicleid][v_model]), pojazd[vehicleid][v_id]);
			if(IsVehicleTruck(pojazd[vehicleid][v_model]) == 1)//trucki z naczepami
			{
				new trailerid = GetVehicleTrailer(vehicleid);
				if(trailerid != 0)
				{
					CargoInfo_Hide(playerid);
					if(pojazd[trailerid][v_cargo] == 0)//nie ma towaru
					{
						if(company[cid][cny_cnt_goodid] != 0)
						{
							LeftNotifyShow(playerid, "info", "Twoja firma ma podpisany kontrakt. Jedz na miejsce zaladunku. Zostalo ono oznaczone ~r~czerwonym punktem~w~ na mapie.", LN_BLUE, 10);
							new from = company[cid][cny_cnt_fromid];
							SetObjective(playerid, strObjective,  load_place_van[from][0], load_place_van[from][1], load_place_van[from][2], true);
						}
						else
						{
							LeftNotifyShow(playerid, "info", "Twoja firma nie ma podpisanego kontraktu. Brak ladunku do przewiezienia.", LN_RED, 10);
						}
					}
					else//ma towar
					{
						new strTargetName[24];
						Get2DZone(pojazd[trailerid][v_cargo_target_X], pojazd[trailerid][v_cargo_target_Y], strTargetName, 24);
						CargoInfo_Show(playerid, goods[pojazd[trailerid][v_cargo]][gds_name], pojazd[trailerid][v_cargo_amount], 0, strTargetName, gracz[playerid][firma_wyplata], "duty");
						format(strObjective, 512, ""COL_RED"• "COL_EASY"Przetransportowano: "COL_GREEN"%0.1f"COL_EASY"/"COL_RED"%0.1f {00C5B6}ton "COL_LIME"[%d%%] "COL_RED"•\n"COL_RED"• "COL_BLUE"Aby rozladować wpisz: "COL_GREEN"/kontrakt rozladuj"COL_GREY" [lub klawisz H] "COL_RED"•", (company[cid][cny_cnt_size_complet]/1000), (company[cid][cny_cnt_size]/1000), procent(company[cid][cny_cnt_size_complet], company[cid][cny_cnt_size]));
						SetObjective(playerid, strObjective, pojazd[trailerid][v_cargo_target_X], pojazd[trailerid][v_cargo_target_Y], pojazd[trailerid][v_cargo_target_Z], true);
					}
				}
				else//bez naczpy
				{
					if(pojazd[trailerid][v_cargo] == 0)//nie ma towaru
					{
						if(company[cid][cny_cnt_goodid] != 0)
						{
							LeftNotifyShow(playerid, "info", "Twoja firma ma podpisany kontrakt. Przyczep naczepe i jedz na miejsce zaladunku. Zostanie one wyznaczone po przyczepieniu naczepy.", LN_BLUE, 10);
						}
						else
						{
							LeftNotifyShow(playerid, "info", "Twoja firma nie ma podpisanego kontraktu. Brak ladunku do przewiezienia.", LN_RED, 10);
						}
					}
					CargoInfo_Hide(playerid);
				}
			}
			else if(IsVehicleTruck(pojazd[vehicleid][v_model]) == 2)//trucki bez naczep
			{
				if(pojazd[vehicleid][v_cargo] != 0)//ma towar
				{
					new strTargetName[24];
					Get2DZone(pojazd[vehicleid][v_cargo_target_X], pojazd[vehicleid][v_cargo_target_Y], strTargetName, 24);
					CargoInfo_Show(playerid, goods[pojazd[vehicleid][v_cargo]][gds_name], pojazd[vehicleid][v_cargo_amount], 0, strTargetName, gracz[playerid][firma_wyplata], "duty");
					format(strObjective, 512, ""COL_RED"• "COL_EASY"Przetransportowano: "COL_GREEN"%0.1f"COL_EASY"/"COL_RED"%0.1f {00C5B6}ton "COL_LIME"[%d%%] "COL_RED"•\n"COL_RED"• "COL_BLUE"Aby rozladować wpisz: "COL_GREEN"/kontrakt rozladuj"COL_GREY" [lub klawisz H] "COL_RED"•", (company[cid][cny_cnt_size_complet]/1000), (company[cid][cny_cnt_size]/1000), procent(company[cid][cny_cnt_size_complet], company[cid][cny_cnt_size]));
					SetObjective(playerid, strObjective, pojazd[vehicleid][v_cargo_target_X], pojazd[vehicleid][v_cargo_target_Y], pojazd[vehicleid][v_cargo_target_Z], true);
				}
				else//nie ma towaru
				{
					if(company[cid][cny_cnt_goodid] != 0)
					{
						LeftNotifyShow(playerid, "info", "Twoja firma ma podpisany kontrakt. Jedz na miejsce zaladunku. Zostalo ono oznaczone ~r~czerwonym punktem~w~ na mapie.", LN_BLUE, 10);
					
						new from = company[cid][cny_cnt_fromid];
						SetObjective(playerid, strObjective,  load_place_van[from][0], load_place_van[from][1], load_place_van[from][2], true);
					}
					else
					{
						LeftNotifyShow(playerid, "info", "Twoja firma nie ma podpisanego kontraktu. Brak ladunku do przewiezienia.", LN_RED, 10);
					}
					CargoInfo_Hide(playerid);
				}
			}
		}
	}
	else if(oldstate == PLAYER_STATE_DRIVER && newstate == PLAYER_STATE_ONFOOT)//z kierowcy na piechote
	{
		CargoInfo_Hide(playerid);
	}
	return 1;
}

task cargocomp_OnTrailerAttached(playerid, trailerid)
{
	new cid = gracz[playerid][firma];
	CargoInfo_Hide(playerid);
	new strObjective[512];
	format(strObjective, 512, ""COL_RED"• "COL_EASY"Towar: "COL_BLUE"%s "COL_RED"•\n"COL_RED"• "COL_EASY"Przetransportowano: "COL_GREEN"%0.1f"COL_EASY"/"COL_RED"%0.1f {00C5B6}ton "COL_LIME"[%d%%] "COL_RED"•\n"COL_RED"• "COL_BLUE"Aby załadować wpisz: "COL_GREEN"/kontrakt zaladuj"COL_GREY" [lub klawisz H] "COL_RED"•", goods[company[cid][cny_cnt_goodid]][gds_name], (company[cid][cny_cnt_size_complet]/1000), (company[cid][cny_cnt_size]/1000), procent(company[cid][cny_cnt_size_complet], company[cid][cny_cnt_size]));
	if(pojazd[trailerid][v_cargo] == 0)//nie ma towaru
	{
		if(company[cid][cny_cnt_goodid] != 0)
		{
			LeftNotifyShow(playerid, "info", "Twoja firma ma podpisany kontrakt. Jedz na miejsce zaladunku. Zostalo ono oznaczone ~r~czerwonym punktem~w~ na mapie.", LN_BLUE, 10);
			new from = company[cid][cny_cnt_fromid];
			SetObjective(playerid, strObjective,  load_place_van[from][0], load_place_van[from][1], load_place_van[from][2], true);
		}
		else
		{
			LeftNotifyShow(playerid, "info", "Twoja firma nie ma podpisanego kontraktu. Brak ladunku do przewiezienia.", LN_RED, 10);
		}
	}
	else//ma towar
	{
		new strTargetName[24];
		Get2DZone(pojazd[trailerid][v_cargo_target_X], pojazd[trailerid][v_cargo_target_Y], strTargetName, 24);
		CargoInfo_Show(playerid, goods[pojazd[trailerid][v_cargo]][gds_name], pojazd[trailerid][v_cargo_amount], 0, strTargetName, gracz[playerid][firma_wyplata], "duty");
		format(strObjective, 512, ""COL_RED"• "COL_EASY"Przetransportowano: "COL_GREEN"%0.1f"COL_EASY"/"COL_RED"%0.1f {00C5B6}ton "COL_LIME"[%d%%] "COL_RED"•\n"COL_RED"• "COL_BLUE"Aby rozladować wpisz: "COL_GREEN"/kontrakt rozladuj"COL_GREY" [lub klawisz H] "COL_RED"•", (company[cid][cny_cnt_size_complet]/1000), (company[cid][cny_cnt_size]/1000), procent(company[cid][cny_cnt_size_complet], company[cid][cny_cnt_size]));
		SetObjective(playerid, strObjective, pojazd[trailerid][v_cargo_target_X], pojazd[trailerid][v_cargo_target_Y], pojazd[trailerid][v_cargo_target_Z], true);
	}
	return 1;
}

task cargocomp_OnTrailerDetached(playerid, trailerid)
{
	CargoInfo_Hide(playerid);
	ClearObjective(playerid);
	return 1;
}

CMD:kz(playerid, params[]) return PC_EmulateCommand(playerid, "/kontrakt z");
CMD:kr(playerid, params[]) return PC_EmulateCommand(playerid, "/kontrakt r");
CMD:ks(playerid, params[]) return PC_EmulateCommand(playerid, "/kontrakt s");

CMD:kontrakt(playerid, params[])
{
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	if(!IsPlayerOnDutyCompany(playerid)) return Error(playerid, "Nie jesteś na służbie.");
	if(company[cid][cny_cnt_goodid] == 0) return Error(playerid, "Twoja firma nie ma podpisanego kontraktu.");
	new vehicleid = gracz[playerid][opu_vehicleid];
	new trucktype = IsVehicleTruck(pojazd[vehicleid][v_model]);
	new cargoveh = vehicleid;
	if(trucktype == 1)  cargoveh = GetVehicleTrailer(vehicleid);
	
	if(compare(params, "zaladuj") || compare(params, "z"))
	{
		if(vehicleid == 0) return Error(playerid, "Musisz znajdować się w pojeździe.");
		if(pojazd[vehicleid][v_owner_type] != VEHICLE_BUSINESS) return Error(playerid, "Pojazd musi być pojazdem firmowym.");
		if(trucktype == 0) return Error(playerid, "Ten pojazd nie jest przystosowany do przewozu ładunków.");
		if(VehicleCapacity(pojazd[cargoveh][v_model]) == 0) return Error(playerid, "Ten pojazd nie ma miejsca na ładunek.");
		if(GetPlayerVehicleSeat(playerid) != 0) return Error(playerid, "Musisz być kierowcą.");
		if(!IsPlayerCanDrive(playerid, vehicleid)) return Error(playerid, "Musisz mieć uprawnienia do tego pojazdu.");
		if(trucktype == 1 && !TrailerCanTransportGood(pojazd[cargoveh][v_model], goods[company[cid][cny_cnt_goodid]][gds_trailertype])) return Error(playerid, "Ta naczepa nie nadaje się do transportu tego towaru.");
		if(pojazd[cargoveh][v_cargo] != 0) return Error(playerid, "Pojazd jest już załadowany.");
		if(TruckerWhileOrderCheck(playerid)) return Error(playerid, "Jesteś podczas zlecenia prywatnego.");
		if(IsPlayerInRangeOfPoint(playerid, 13.0, gracz[playerid][objective_X], gracz[playerid][objective_Y], gracz[playerid][objective_Z]))
		{
			if(goods[company[cid][cny_cnt_goodid]][gds_adr] == true && gracz[playerid][upr_adr] == 0) return Error(playerid, "Brak uprawnień ADR.");
			new strZaladuj[2048];
			new strSrcZone[24], strDstZone[24];
			Get2DZone(load_place_van[ company[cid][cny_cnt_fromid] ][0], load_place_van[ company[cid][cny_cnt_fromid] ][1], strSrcZone, 32);
			Get2DZone(load_place_van[ company[cid][cny_cnt_targetid] ][0], load_place_van[ company[cid][cny_cnt_targetid] ][1], strDstZone, 32);
			format(strZaladuj, 2048, ""COL_EASY"Zadecyduj, ile towaru chcesz załadować?");
			format(strZaladuj, 2048, "%s\n"COL_EASY"Towar: "COL_WHITE"%s %s", strZaladuj, goods[company[cid][cny_cnt_goodid]][gds_name], (goods[company[cid][cny_cnt_goodid]][gds_adr] == true) ? (""COL_ORANGE"[ADR]") : (" "));
			new Float:FloatVehCap = float(VehicleCapacity(pojazd[cargoveh][v_model]))/1000.0;
			format(strZaladuj, 2048, "%s\n"COL_EASY"Ładowność Twojego środka transportu: "COL_DRVONLINE"%d kg "COL_GREY"(%0.1f ton)", strZaladuj, VehicleCapacity(pojazd[cargoveh][v_model]), FloatVehCap);
			format(strZaladuj, 2048, "%s\n"COL_EASY"Przetransportowany ładunek: "COL_GREEN"%0.1f"COL_EASY"/"COL_RED"%0.1f {00C5B6}ton "COL_LIME"[%d%%]", strZaladuj, (company[cid][cny_cnt_size_complet]/1000.0), (company[cid][cny_cnt_size]/1000.0), procent(company[cid][cny_cnt_size_complet], company[cid][cny_cnt_size]));
			new dd, hh, mm, ss;
			SecToTime(company[cid][cny_cnt_time_left], dd, hh, mm, ss);
			format(strZaladuj, 2048, "%s\n"COL_EASY"Pozostały czas na wykonanie zlecenia: "COL_BLUE"%d dni, %d godz, %d min, %d sekund", strZaladuj, dd, hh, mm, ss);
			format(strZaladuj, 2048, "%s\n"COL_EASY"Trasa: {00E16A}%s "COL_LIME"» [%0.1f km] » {FF4343}%s", strZaladuj, strSrcZone, company[cid][cny_cnt_distance], strDstZone);
			format(strZaladuj, 2048, "%s\n\n"COL_WHITE"Możesz przeładować o "COL_RED"%d%%"COL_WHITE" całkowitej ładowności pojazdu. Ale to jest "COL_RED"nielegalne"COL_WHITE".", strZaladuj, MaxOverloadCargo(playerid));
			format(strZaladuj, 2048, "%s\n"COL_BLUE"Wprowadź w polu poniżej ile kilogramów chcesz załadować. Możesz wykorzystać równierz skróty: ", strZaladuj);
			format(strZaladuj, 2048, "%s\n"COL_LIME"full "COL_GREY"- Ładujesz legalnie 100%% ładowności pojazdu. ", strZaladuj);
			format(strZaladuj, 2048, "%s\n"COL_LIME"over - "COL_GREY"Przeładowujesz pojazd o %d%% całkowitej ładowności pojazdu (nielegalne).", strZaladuj, MaxOverloadCargo(playerid));
			format(strZaladuj, 2048, "%s\n\n"COL_ORANGE"Decyzja ("COL_LIME"ilość kg"COL_ORANGE"/"COL_LIME"full"COL_ORANGE"/"COL_LIME"over"COL_ORANGE"):", strZaladuj);
			Dialog_Show(playerid, COMPANYVEHLOAD, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_GREEN"Ładowanie towaru "COL_RED"«•", strZaladuj, "Zatwierdz", "Anuluj");
		}
		else Error(playerid, "Nie jesteś w miejscu docelowym.");
	}
	else if(compare(params, "rozladuj") || compare(params, "r"))
	{
		if(vehicleid == 0) return Error(playerid, "Musisz znajdować się w pojeździe.");
		if(pojazd[vehicleid][v_owner_type] != VEHICLE_BUSINESS) return Error(playerid, "Pojazd musi być pojazdem firmowym.");
		if(trucktype == 0) return Error(playerid, "Ten pojazd nie jest przystosowany do przewozu ładunków.");
		if(VehicleCapacity(pojazd[cargoveh][v_model]) == 0) return Error(playerid, "Ten pojazd nie ma miejsca na ładunek.");
		if(GetPlayerVehicleSeat(playerid) != 0) return Error(playerid, "Musisz być kierowcą.");
		if(!IsPlayerCanDrive(playerid, vehicleid)) return Error(playerid, "Musisz mieć uprawnienia do tego pojazdu.");
		if(trucktype == 1 && !TrailerCanTransportGood(pojazd[cargoveh][v_model], goods[company[cid][cny_cnt_goodid]][gds_trailertype])) return Error(playerid, "Ta naczepa nie nadaje się do transportu tego towaru.");
		if(pojazd[cargoveh][v_cargo] == 0) return Error(playerid, "Pojazd nie jest załadowany.");
		if(TruckerWhileOrderCheck(playerid)) return Error(playerid, "Jesteś podczas zlecenia prywatnego.");
		if(IsPlayerInRangeOfPoint(playerid, 13.0, gracz[playerid][objective_X], gracz[playerid][objective_Y], gracz[playerid][objective_Z]))
		{
			ClearObjective(playerid);
			CargoInfo_Hide(playerid);
			if(company[cid][cny_cnt_size_complet] >= company[cid][cny_cnt_size] || company[cid][cny_cnt_goodid] == 0)
			{
				Error(playerid, "Wykonywany kontrakt jest już nieaktualny. Anulowano transport.");
			}
			else
			{
				company[cid][cny_cnt_size_complet] += float(pojazd[cargoveh][v_cargo_amount]);
				new strSrcZone[32], strDstZone[32];
				Get2DZone(load_place_van[ company[cid][cny_cnt_fromid] ][0], load_place_van[ company[cid][cny_cnt_fromid] ][1], strSrcZone, 6);
				Get2DZone(load_place_van[ company[cid][cny_cnt_targetid] ][0], load_place_van[ company[cid][cny_cnt_targetid] ][1], strDstZone, 6);
				new strSrcFormat[24], strDstFormat[24];
				format(strSrcFormat, 24, "%s...", strSrcZone);
				format(strDstFormat, 24, "%s...", strDstZone);
				LogCompany(cid, gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_KURS, "%s. %s -> %s . %0.1f ton.", goods[company[cid][cny_cnt_goodid]][gds_name], strSrcFormat, strDstFormat, float(pojazd[cargoveh][v_cargo_amount])/1000.0);
				Get2DZone(load_place_van[ company[cid][cny_cnt_fromid] ][0], load_place_van[ company[cid][cny_cnt_fromid] ][1], strSrcZone, 32);
				Get2DZone(load_place_van[ company[cid][cny_cnt_targetid] ][0], load_place_van[ company[cid][cny_cnt_targetid] ][1], strDstZone, 32);
				LogKurs(playerid, pojazd[vehicleid][v_model], pojazd[cargoveh][v_cargo_distance], 0, company[cid][cny_cnt_fromid], company[cid][cny_cnt_targetid], strSrcZone, strDstZone);
				new strCargoCompletGui[2048];
				format(strCargoCompletGui, 2048, ""COL_LIME"Gratulacje!");
				format(strCargoCompletGui, 2048, "%s\n"COL_WHITE"Udało Ci się dostarczyć {00C5B6}%0.1f ton"COL_WHITE" %s z {00E16A}%s "COL_WHITE"do {FF4343}%s"COL_WHITE".", strCargoCompletGui, float(pojazd[cargoveh][v_cargo_amount])/1000.0, goods[company[cid][cny_cnt_goodid]][gds_name], strSrcZone, strDstZone);
				format(strCargoCompletGui, 2048, "%s\n"COL_WHITE"Zdarzenie zostało zarejestrowane. Dzięki temu, Twój pracodawca będzie mógł ocenić Twoją wydajność.", strCargoCompletGui);
				gracz[playerid][firma_kontrakt_kg] += pojazd[cargoveh][v_cargo_amount];
				gracz[playerid][company_kursy_per_wyplata]++;
				mq_format("UPDATE `Konta` SET `firma_kontrakt_kg`='%d' WHERE `id`='%d';", gracz[playerid][firma_kontrakt_kg], gracz[playerid][UID]);
				mq_send("QUpdateCompKG");
				if(serwer[timestamp_delivery_msg] < serwer[time_timestamp])
				{
					SendClientMessageToAllEx(0xFF0000FF, "[%s] {%06x}• %s {FF4343}• %s » [%0.1f km] » %s "COL_LIME"• %s", company[cid][cny_name], GetPlayerColor(playerid) >>> 8, nick(playerid), strSrcZone, pojazd[cargoveh][v_cargo_distance], strDstZone, goods[pojazd[cargoveh][v_cargo]][gds_name]);
					serwer[timestamp_delivery_msg] = serwer[time_timestamp]+(60*6);
				}
				new strLog[256];
				format(strLog, 256, "{FF0000}[%s] {%06x}• %s {FF4343}• %s » [%0.1f km] » %s "COL_LIME"• %s", company[cid][cny_name], GetPlayerColor(playerid) >>> 8, nick(playerid), strSrcZone, pojazd[cargoveh][v_cargo_distance], strDstZone, goods[pojazd[cargoveh][v_cargo]][gds_name]);
				SavePublicChatLog(strLog);

				format(strLog, 256, "[%s] %s; %s -> [%0.1f km] -> %s; %s", company[cid][cny_name], nick(playerid), strSrcZone, pojazd[cargoveh][v_cargo_distance], strDstZone, goods[pojazd[cargoveh][v_cargo]][gds_name]);
				HUD_UpdateINFO(strLog, 3, 0xFFA500FF);
				serwer[time_connectinfo] = serwer[time_timestamp];

				GiveKurs(playerid, 1);
				pojazd[cargoveh][v_cargo] = 0;
				pojazd[cargoveh][v_cargo_amount] = 0;
				pojazd[cargoveh][v_cargo_score] = 0;
				pojazd[cargoveh][v_cargo_distance] = 0.0;
				pojazd[cargoveh][v_cargo_target_X] = 0.0;
				pojazd[cargoveh][v_cargo_target_Y] = 0.0;
				pojazd[cargoveh][v_cargo_target_Z] = 0.0;
				ResetVehicleADRData(cargoveh);
				if(company[cid][cny_cnt_size_complet] >= company[cid][cny_cnt_size]-1.0)//kontrakt kompletny
				{
					format(strCargoCompletGui, 2048, "%s\n"COL_RED"Dostarczyłeś ostatni ładunek. Twoja firma musi podpisać nowy kontrakt.", strCargoCompletGui);
					new strInfo[144];
					format(strInfo, 144, ""COL_BLUE"%s(%d) "COL_GREEN"dostarczył ostatni ładunek.", nick(playerid), playerid);
					SendCompanyMessage(cid, strInfo);
					company[cid][cny_money] += company[cid][cny_cnt_price];
					company[cid][cny_score] += company[cid][cny_cnt_score];
					//CompanySaveMoney(cid);
					CompanySaveData(cid);
					LogCompany(cid, gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_BANK, "Ukonczyl kontrakt. Wplynelo: %d$. Saldo: %d$.", company[cid][cny_cnt_price], company[cid][cny_money]);
					ResetCompanyContractRam(cid);
					CompanySaveDataContract(cid);
				}
				else
				{
					CompanySaveDataContract(cid);
					format(strCargoCompletGui, 2048, "%s\n"COL_WHITE"Aby sprawdzić status kontraktu, użyj: "COL_BLUE"/kontrakt status"COL_WHITE".", strCargoCompletGui);
					Company_OnPlayerStateChange(playerid, PLAYER_STATE_DRIVER, PLAYER_STATE_ONFOOT);
				}
				Dialog_Show(playerid, NULLCARGOCOM, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_LIME"SUKCES! "COL_RED"«•", strCargoCompletGui, "Zamknij", "");
				Info(playerid, "Ładunek został dostarczony!");
			}
		}
	}
	else if(compare(params, "status") || compare(params, "s"))
	{
		new strContractStatus[3072];
		new strSrcZone[24], strDstZone[24];

		Get2DZone(load_place_van[ company[cid][cny_cnt_fromid] ][0], load_place_van[ company[cid][cny_cnt_fromid] ][1], strSrcZone, 32);
		Get2DZone(load_place_van[ company[cid][cny_cnt_targetid] ][0], load_place_van[ company[cid][cny_cnt_targetid] ][1], strDstZone, 32);
		new dd, hh, mm, ss;
		SecToTime(company[cid][cny_cnt_time], dd, hh, mm, ss);
		format(strContractStatus, 3072, ""COL_ORANGE"• "COL_EASY"Nazwa towaru: "COL_WHITE"%s %s", goods[company[cid][cny_cnt_goodid]][gds_name], (goods[company[cid][cny_cnt_goodid]][gds_adr] == true) ? (""COL_ORANGE"[ADR]") : (" "));
		format(strContractStatus, 3072, "%s\n"COL_ORANGE"• "COL_EASY"Trasa: {00E16A}%s "COL_LIME"» [%0.1f km] » {FF4343}%s", strContractStatus, strSrcZone, company[cid][cny_cnt_distance], strDstZone);
		format(strContractStatus, 3072, "%s\n"COL_ORANGE"• "COL_EASY"Przetransportowany ładunek: "COL_GREEN"%0.1f"COL_EASY"/"COL_RED"%0.1f {00C5B6}ton "COL_LIME"[%d%%]", strContractStatus, (company[cid][cny_cnt_size_complet]/1000.0), (company[cid][cny_cnt_size]/1000.0), procent(company[cid][cny_cnt_size_complet], company[cid][cny_cnt_size]));
		format(strContractStatus, 3072, "%s\n"COL_ORANGE"• "COL_EASY"Wynagrodzenie: "COL_GREEN"%d$", strContractStatus, company[cid][cny_cnt_price]);
		format(strContractStatus, 3072, "%s\n"COL_ORANGE"• "COL_EASY"Ogólny czas: %d dni, %d godz, %d min", strContractStatus, dd, hh, mm);
		dd = 0;
		hh = 0;
		mm = 0;
		ss = 0;
		SecToTime(company[cid][cny_cnt_time_left], dd, hh, mm, ss);
		format(strContractStatus, 3072, "%s\n"COL_RED"• "COL_ORANGE"Pozostały czas: "COL_BLUE"%d dni, %d godz, %d min, %d sekund", strContractStatus, dd, hh, mm, ss);
		format(strContractStatus, 3072, "%s\n"COL_ORANGE"• "COL_RED"*"COL_EASY"Kara finansowa (jeśli upłynie pozostały czas lub kontrakt zostanie anulowany): "COL_RED"-%d$", strContractStatus, company[cid][cny_cnt_penalty]);
		format(strContractStatus, 3072, "%s\n\n"COL_RED"*"COL_GREY" - Kara finansowa nie zostanie nałożona, jeśli saldo firmy jest na minusie.", strContractStatus);
		format(strContractStatus, 3072, "%s\n\n"COL_GREY"Prognozowana ilość kursów, przy 100%% załadunku, konkretnymi środkami transportu:"COL_GREY"\n", strContractStatus);
		for(new t; t < 600; t++)
		{
			if(IsVehicleTruckSalonBanned(t)) continue;
			if(!TrailerCanTransportGood(t, goods[company[cid][cny_cnt_goodid]][gds_trailertype]) && IsVehicleTrailer(t)) continue;
			new vehCap = VehicleCapacity(t);
			if(vehCap != 0)
			{
				new Float:wynik = (company[cid][cny_cnt_size]-company[cid][cny_cnt_size_complet])/float(vehCap);
				if(wynik < 1.0) wynik = 1.0;
				format(strContractStatus, 3072, "%s"COL_GREY"- %s ("COL_YELLOW"~%dx"COL_GREY")\n", strContractStatus, GetVehicleName(t), floatround(wynik));
			}
		}
		Dialog_Show(playerid, CSTATUSCONTRACTB, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_GREEN"Status kontraktu"COL_RED" «•", strContractStatus, "Zamknij", "");
	}
	else
	{
		SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /k [zaladuj/rozladuj/status]");
		SendClientMessage(playerid, -1, ""COL_GREY"SKRÓTY: /kz /kr /ks");
	}
	return 1;
}


Dialog:COMPANYVEHLOAD(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	if(!IsPlayerOnDutyCompany(playerid)) return Error(playerid, "Nie jesteś na służbie.");
	if(company[cid][cny_cnt_goodid] == 0) return Error(playerid, "Twoja firma nie ma podpisanego kontraktu.");
	new vehicleid = gracz[playerid][opu_vehicleid];
	new trucktype = IsVehicleTruck(pojazd[vehicleid][v_model]);
	new cargoveh = vehicleid;
	if(trucktype == 1)  cargoveh = GetVehicleTrailer(vehicleid);
	if(vehicleid == 0) return Error(playerid, "Musisz znajdować się w pojeździe.");
	if(pojazd[vehicleid][v_owner_type] != VEHICLE_BUSINESS) return Error(playerid, "Pojazd musi być pojazdem firmowym.");
	if(trucktype == 0) return Error(playerid, "Ten pojazd nie jest przystosowany do przewozu ładunków.");
	if(VehicleCapacity(pojazd[cargoveh][v_model]) == 0) return Error(playerid, "Ten pojazd nie ma miejsca na ładunek.");
	if(GetPlayerVehicleSeat(playerid) != 0) return Error(playerid, "Musisz być kierowcą.");
	if(!IsPlayerCanDrive(playerid, vehicleid)) return Error(playerid, "Musisz mieć uprawnienia do tego pojazdu.");
	if(trucktype == 1 && !TrailerCanTransportGood(pojazd[cargoveh][v_model], goods[company[cid][cny_cnt_goodid]][gds_trailertype])) return Error(playerid, "Ta naczepa nie nadaje się do transportu tego towaru.");
	if(pojazd[cargoveh][v_cargo] != 0) return Error(playerid, "Pojazd jest już załadowany.");
	if(TruckerWhileOrderCheck(playerid)) return Error(playerid, "Jesteś podczas zlecenia prywatnego.");
	if(IsPlayerInRangeOfPoint(playerid, 13.0, gracz[playerid][objective_X], gracz[playerid][objective_Y], gracz[playerid][objective_Z]))
	{
		new strObjective[512];
		format(strObjective, 512, ""COL_RED"• "COL_EASY"Przetransportowano: "COL_GREEN"%0.1f"COL_EASY"/"COL_RED"%0.1f {00C5B6}ton "COL_LIME"[%d%%] "COL_RED"•\n"COL_RED"• "COL_BLUE"Aby rozladować wpisz: "COL_GREEN"/kontrakt rozladuj"COL_GREY" [lub klawisz H] "COL_RED"•", (company[cid][cny_cnt_size_complet]/1000), (company[cid][cny_cnt_size]/1000), procent(company[cid][cny_cnt_size_complet], company[cid][cny_cnt_size]));
		new carg_input_size = 0;
		if(compare(inputtext, "full"))
		{
			Info(playerid, "Ładujesz legalnie 100%% ładowności.");
			carg_input_size = VehicleCapacity(pojazd[cargoveh][v_model]);
			new strInfo[144];
			format(strInfo, 144, ""COL_EASY"%d kg"COL_WHITE", czyli "COL_BLUE"%0.1f ton"COL_WHITE".", carg_input_size, (float(carg_input_size)/1000.0)+0.01);
			Info(playerid, strInfo);
		}
		else if(compare(inputtext, "over"))
		{
			new Float:veh_capacity = float(VehicleCapacity(pojazd[cargoveh][v_model]));
			new Float:overload_proc = float(MaxOverloadCargo(playerid));
			new Float:wynik = veh_capacity+((overload_proc/100.0)*veh_capacity);
			carg_input_size = floatround(wynik);
			new strInfo[144];
			format(strInfo, 144, "Ładujesz "COL_RED"nielegalnie"COL_WHITE" o %d procent więcej całkowitej ładowności.", MaxOverloadCargo(playerid));
			Info(playerid, strInfo);			
			format(strInfo, 144, ""COL_EASY"%d kg"COL_WHITE", czyli "COL_BLUE"%0.1f ton"COL_WHITE".", carg_input_size, (float(carg_input_size)/1000.0)+0.01);
			Info(playerid, strInfo);
		}
		else//ręcznie wpisana wartość
		{
			new size_input = strval(inputtext);
			if(size_input > 1000000 || size_input < 1) return Error(playerid, "Nieodpowiednia wartość.");
			new Float:veh_capacity = float(VehicleCapacity(pojazd[cargoveh][v_model]));
			new Float:overload_proc = float(MaxOverloadCargo(playerid));
			new Float:wynik = veh_capacity+((overload_proc/100.0)*veh_capacity);
			if(size_input > wynik) return Error(playerid, "Zbyt duża wartość.");
			carg_input_size = size_input;
			new strInfo[144];
			format(strInfo, 144, "Ładujesz "COL_EASY"%d kg"COL_WHITE", czyli "COL_BLUE"%0.1f ton"COL_WHITE".", carg_input_size, (float(carg_input_size)/1000.0)+0.01);
			Info(playerid, strInfo);
		}
		if(carg_input_size > 0)
		{
			new Float:total_actual = company[cid][cny_cnt_size]-company[cid][cny_cnt_size_complet];
			if(carg_input_size > floatround(total_actual)) carg_input_size = floatround(total_actual);
			pojazd[cargoveh][v_cargo] = company[cid][cny_cnt_goodid];
			pojazd[cargoveh][v_cargo_amount] = carg_input_size;
			pojazd[cargoveh][v_cargo_score] = company[cid][cny_cnt_score];
			pojazd[cargoveh][v_cargo_distance] = company[cid][cny_cnt_distance];
			pojazd[cargoveh][v_cargo_target_X] = load_place_van[company[cid][cny_cnt_targetid] ][0];
			pojazd[cargoveh][v_cargo_target_Y] = load_place_van[company[cid][cny_cnt_targetid] ][1];
			pojazd[cargoveh][v_cargo_target_Z] = load_place_van[company[cid][cny_cnt_targetid] ][2];
			SetObjective(playerid, strObjective, pojazd[cargoveh][v_cargo_target_X], pojazd[cargoveh][v_cargo_target_Y], pojazd[cargoveh][v_cargo_target_Z], true);
			new strTargetName[24];
			Get2DZone(pojazd[cargoveh][v_cargo_target_X], pojazd[cargoveh][v_cargo_target_Y], strTargetName, 20);
			CargoInfo_Show(playerid, goods[pojazd[cargoveh][v_cargo]][gds_name], pojazd[cargoveh][v_cargo_amount], 0, strTargetName, gracz[playerid][firma_wyplata], "duty");
			LoadingCargo(playerid, 0);
			RegisterStartLogKurs(playerid);
			LeftNotifyShow(playerid, "Misja", "Dostarcz towar do celu. Cel zostal oznaczony ~r~czerwona~w~ flaga na minimapie, trasa do niej zostala wytyczona przez ~y~nawigacje GPS~w~.", LN_BLUE, 15);
		}
	}
	else Error(playerid, "Nie jesteś w miejscu docelowym.");
	return 1;
}

stock MaxOverloadCargo(playerid)
{
	if(isvip(playerid)) return MAX_OVERLOADCARGO_VIP;
	return MAX_OVERLOADCARGO;
}

//***************************************************/firmy
CMD:firmy(playerid, params[])
{
	new strListaFirm[2048];
	format(strListaFirm, 2048, "ID\tLokalizacja\tFirma\tCena lub aktualny właściciel");
	new strZone[24];
	for(new c; c < MAX_COMPANY; c++)
	{
		if(company[c][cny_price] == 0) continue;
		Get2DZone(company[c][cny_dutyX], company[c][cny_dutyY], strZone, 24);
		if(company[c][cny_owneruid] != 0) format(strListaFirm, 2048, "%s\n"COL_BLACK"%d\t"COL_EASY"%s\t"COL_ORANGE"%s "COL_GREY"[%d score]\t"COL_DRVONLINE"%s", strListaFirm, c, strZone, company[c][cny_name], company[c][cny_score], GetPlayerIGName(company[c][cny_owneruid]));
		else format(strListaFirm, 2048, "%s\n"COL_BLACK"%d\t"COL_EASY"%s\t"COL_LIME"[WOLNA SIEDZIBA]\t"COL_GREEN"%d$", strListaFirm, c, strZone, company[c][cny_price]);
	}
	Dialog_Show(playerid, COMPANYLIST, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_GREEN"Lista firm i wolnych siedzib"COL_RED" «•", strListaFirm, "Namierz", "Anuluj");
	return 1;
}

Dialog:COMPANYLIST(playerid, response, listitem, inputtext[])
{
	if(!response) 
	{
		DisablePlayerCheckpoint(playerid);
		return 1;
	}
	new cid = strval(inputtext);
	SetPlayerCheckpoint(playerid, company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ]-0.4, 5.0);
	Info(playerid, "Siedziba firmy została zaznaczona "COL_RED"czerwonym"COL_WHITE" punktem na mapie.");
	LeftNotifyShow(playerid, "Sukces!", "Siedziba firmy zostala zaznaczona ~r~czerwonym~w~ punktem na mapie.", LN_GREEN);
	return 1;
}

stock GetCompanyName(cid)//funkcja zrobione na potrzeby głupoty pawn, error 033
{
	new cname[24];
	format(cname, 24, "%s", company[cid][cny_name]);
	return cname;
}