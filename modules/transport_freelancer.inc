stock Init_TransportFreelancer()
{
	RotateFreelancerGoods();//dla van
	RotateFreelancerTrailers();///dla trucków
	return 1;
}

#define MAX_FLPERPAGEGOODS 10//ilość towarów wyświetlanych jednocześnie na /zlecenie



CMD:zlecenie(playerid, params[])
{
	if(gracz[playerid][td_confirmcargo]) return Error(playerid, "Jesteś w trakcie zatwierdzania zlecenia.");
	if(gracz[playerid][delivered_window_process]) return Error(playerid, "Obecnie wyładowywujesz towar.");
	new vehicleid = gracz[playerid][opu_vehicleid];
	new trucktype = IsVehicleTruck(pojazd[vehicleid][v_model]);
	new cargoveh = vehicleid;
	if(trucktype == 1)  cargoveh = GetVehicleTrailer(vehicleid);
	//-------------------------------------
	new bool:whileorder = TruckerWhileOrderCheck(playerid);
	/*for(new v = GetVehiclePoolSize(); v != -1; v--)//sprawdzanie czy gracz ma zlecenie w jakimś vanie
	{
		if(pojazd[v][v_owner_type] == VEHICLE_PLAYER && pojazd[v][v_owner] == gracz[playerid][UID])
		{
			if(pojazd[v][v_cargo] != 0)
			{
				whileorder = true;
				break;
			}
		}
	}
	if(gracz[playerid][cargo_trailerdid] != 0) whileorder = true;
	if(gracz[playerid][gfv_waitforpickup] != 0) whileorder = true;*/
	//------------------------------------
	if(compare(params, "odbierz") || compare(params, "o"))
	{
		if(!whileorder) return Error(playerid, "Nie jesteś w trakcie zlecenia.");
		if(vehicleid == 0) return Error(playerid, "Musisz znajdować się w pojeździe.");
		if(pojazd[vehicleid][v_owner_type] != VEHICLE_PLAYER) return Error(playerid, "Pojazd musi być pojazdem prywatnym.");
		if(trucktype == 0) return Error(playerid, "Ten pojazd nie jest przystosowany do przewozu ładunków.");
		if(trucktype == 1) return Error(playerid, "Ten pojazd nie ma miejsca na ładunek.");
		if(GetPlayerVehicleSeat(playerid) != 0) return Error(playerid, "Musisz być kierowcą.");
		if(!IsPlayerCanDrive(playerid, vehicleid)) return Error(playerid, "Musisz mieć uprawnienia do tego pojazdu.");
		if(gracz[playerid][gfv_waitforpickup] == 0) return Error(playerid, "Brak ładunku do odebrania.");//
		if(IsPlayerInRangeOfPoint(playerid, 13.0, gracz[playerid][objective_X], gracz[playerid][objective_Y], gracz[playerid][objective_Z]))
		{
			new get_gfv = gracz[playerid][gfv_waitforpickup];
			if(VehicleCapacity(pojazd[vehicleid][v_model]) < goods_for_vans[get_gfv][gfv_amount]) return Error(playerid, "Za mała ładowność pojazdu.");
			gracz[playerid][gfv_waitforpickup] = 0;
			pojazd[cargoveh][v_cargo] = goods_for_vans[get_gfv][gfv_goodid];
			pojazd[cargoveh][v_cargo_amount] = goods_for_vans[get_gfv][gfv_amount];
			pojazd[cargoveh][v_cargo_price] = goods_for_vans[get_gfv][gfv_price];
			pojazd[cargoveh][v_cargo_score] = goods_for_vans[get_gfv][gfv_score];
			pojazd[cargoveh][v_cargo_distance] = goods_for_vans[get_gfv][gfv_distance];
			pojazd[cargoveh][v_cargo_target_X] = load_place_van[goods_for_vans[get_gfv][gfv_loadplace_targetid]][0];
			pojazd[cargoveh][v_cargo_target_Y] = load_place_van[goods_for_vans[get_gfv][gfv_loadplace_targetid]][1];
			pojazd[cargoveh][v_cargo_target_Z] = load_place_van[goods_for_vans[get_gfv][gfv_loadplace_targetid]][2];
			if(pojazd[cargoveh][v_id] != 0)
			{
				mq_format("UPDATE `pojazdy` SET `rlg_c_id`='%d', `rlg_c_amount`='%d', `rlg_c_price`='%d', `rlg_c_score`='%d', `rlg_c_distance`='%f', `rlg_c_tX`='%f', `rlg_c_tY`='%f', `rlg_c_tZ`='%f' WHERE `id`='%d';",
				pojazd[cargoveh][v_cargo],
				pojazd[cargoveh][v_cargo_amount],
				pojazd[cargoveh][v_cargo_price],
				pojazd[cargoveh][v_cargo_score],
				pojazd[cargoveh][v_cargo_distance],
				pojazd[cargoveh][v_cargo_target_X],
				pojazd[cargoveh][v_cargo_target_Y],
				pojazd[cargoveh][v_cargo_target_Z],
				pojazd[cargoveh][v_id]);
				mq_send("QUpdateRlgCargo");
			}
			new strTemp[24];
			Get2DZone(pojazd[cargoveh][v_cargo_target_X], pojazd[cargoveh][v_cargo_target_Y], strTemp, 20);
			CargoInfo_Show(playerid, goods[pojazd[cargoveh][v_cargo]][gds_name], pojazd[cargoveh][v_cargo_amount], 0, strTemp, pojazd[cargoveh][v_cargo_price], "kurs");
			SetObjective(playerid, ""COL_RED"• "COL_BLUE"Aby dostarczyć zlecenie, wpisz: "COL_GREEN"/zlecenie dostarcz "COL_GREY"[lub klawisz H] "COL_RED"•", pojazd[cargoveh][v_cargo_target_X], pojazd[cargoveh][v_cargo_target_Y], pojazd[cargoveh][v_cargo_target_Z], true);
			//Info(playerid, "Towar załadowany.");

			SetCameraBehindPlayer(playerid);
			TogglePlayerControllable(playerid, false);
			RegisterStartLogKurs(playerid);
			LoadingCargo(playerid, 0);
		}
		else Error(playerid, "Nie jesteś w miejscu docelowym.");
	}
	else if(compare(params, "dostarcz") || compare(params, "d"))//dostarczanie
	{
		if(!whileorder) return Error(playerid, "Nie jesteś w trakcie zlecenia.");
		if(vehicleid == 0) return Error(playerid, "Musisz znajdować się w pojeździe.");
		if(pojazd[vehicleid][v_owner_type] != VEHICLE_PLAYER) return Error(playerid, "Pojazd musi być pojazdem prywatnym.");
		if(trucktype == 0) return Error(playerid, "Ten pojazd nie jest przystosowany do przewozu ładunków.");
		if(GetPlayerVehicleSeat(playerid) != 0) return Error(playerid, "Musisz być kierowcą.");
		if(!IsPlayerCanDrive(playerid, vehicleid)) return Error(playerid, "Musisz mieć uprawnienia do tego pojazdu.");
		if(gracz[playerid][gfv_waitforpickup]) return Error(playerid, "Ładunek nie został odebrany.");//
		if(pojazd[cargoveh][v_cargo] == 0) return Error(playerid, "Brak ładunku."); 
		if(IsPlayerInRangeOfPoint(playerid, 13.0, gracz[playerid][objective_X], gracz[playerid][objective_Y], gracz[playerid][objective_Z]))
		{
			new strSrcZone[24], strDstZone[24];
			new rotate_trailerid = 0;
			if(trucktype == 1)//truck z naczepa
			{
				if(cargoveh == 0) return Error(playerid, "Brak naczepy.");
				DetachTrailerFromVehicle(cargoveh);
				rotate_trailerid = cargoveh;
				SetVehicleToRespawn(cargoveh);
				UpdateDynamic3DTextLabelText(pojazd[cargoveh][v_text3d], 0x009933FF, pojazd[cargoveh][v_text3d_strcache]);
				Get2DZone(pojazd[cargoveh][v_X], pojazd[cargoveh][v_Y], strSrcZone, 24);
				Get2DZone(pojazd[pojazd[cargoveh][v_cargo_destvid]][v_X], pojazd[pojazd[cargoveh][v_cargo_destvid]][v_Y], strDstZone, 24);
				LogKurs(playerid, pojazd[vehicleid][v_model], pojazd[cargoveh][v_cargo_distance], 1, pojazd[cargoveh][v_id], pojazd[pojazd[cargoveh][v_cargo_destvid]][v_id], strSrcZone, strDstZone);
				//format(goodname, 24, "%s", goods[pojazd[cargoveh][v_cargo]][gds_name]);
			}
			else
			{
				new zid = gracz[playerid][cargo_confirmtrailer];
				Get2DZone(load_place_van[goods_for_vans[zid][gfv_loadplace_sourceid]][0], load_place_van[goods_for_vans[zid][gfv_loadplace_sourceid]][1], strSrcZone, 24);
				Get2DZone(load_place_van[goods_for_vans[zid][gfv_loadplace_targetid]][0], load_place_van[goods_for_vans[zid][gfv_loadplace_targetid]][1], strDstZone, 24);
				LogKurs(playerid, pojazd[vehicleid][v_model], pojazd[cargoveh][v_cargo_distance], 0, goods_for_vans[zid][gfv_loadplace_sourceid], goods_for_vans[zid][gfv_loadplace_targetid], strSrcZone, strDstZone);
				//format(goodname, 24, "%s", goods[goods_for_vans[zid][gfv_goodid]][gds_name]);
			}
			if(serwer[timestamp_delivery_msg] < serwer[time_timestamp])
			{
				SendClientMessageToAllEx(0xFF0000FF, "[DOSTARCZENIE] {%06x}• %s {FF4343}• %s » [%0.1f km] » %s "COL_LIME"• %s", GetPlayerColor(playerid) >>> 8, nick(playerid), strSrcZone, pojazd[cargoveh][v_cargo_distance], strDstZone, goods[pojazd[cargoveh][v_cargo]][gds_name]);
				serwer[timestamp_delivery_msg] = serwer[time_timestamp]+(60*6);
			}
			new strLog[256];
			format(strLog, 256, "{FF0000}[DOSTARCZENIE] {%06x}• %s {FF4343}• %s » [%0.1f km] » %s "COL_LIME"• %s", GetPlayerColor(playerid) >>> 8, nick(playerid), strSrcZone, pojazd[cargoveh][v_cargo_distance], strDstZone, goods[pojazd[cargoveh][v_cargo]][gds_name]);
			SavePublicChatLog(strLog);	
			
			format(strLog, 256, "[DOSTARCZENIE] %s; %s -> [%0.1f km] -> %s; %s", nick(playerid), strSrcZone, pojazd[cargoveh][v_cargo_distance], strDstZone, goods[pojazd[cargoveh][v_cargo]][gds_name]);
			HUD_UpdateINFO(strLog, 3, 0xFFA500FF);
			serwer[time_connectinfo] = serwer[time_timestamp];

			ClearObjective(playerid);
			ClearTrailerSelect(playerid);//linijka niekonieczna ale może odbugować jakby coś poszło nie tak
			GiveMoney(playerid, pojazd[cargoveh][v_cargo_price]);
			GiveScore(playerid, pojazd[cargoveh][v_cargo_score]);
			GiveKurs(playerid, 1);
			gracz[playerid][delivered_cargovid] = cargoveh;
			//premia za trudne trasy
			if(compare(strSrcZone, "Pencil Factory") || compare(strSrcZone, "Oil Province") || compare(strDstZone, "Pencil Factory") || compare(strDstZone, "Oil Province"))
			{
				Process_DeliveredSummary(playerid, 0, 1);
			}
			else 
			{
				Process_DeliveredSummary(playerid, 0, 0);
			}
			mq_format("UPDATE `pojazdy` SET `rlg_c_id`='0', `rlg_c_amount`='0', `rlg_c_price`='0', `rlg_c_score`='0', `rlg_c_distance`='0.0', `rlg_c_tX`='0.0', `rlg_c_tY`='0.0', `rlg_c_tZ`='0.0' WHERE `owner_type`='%d' AND `owner`='%d';", VEHICLE_PLAYER, gracz[playerid][UID]);
			mq_send("QUpdateRlgCargo");
			//Info(playerid, "Towar dostarczony.");
			CargoInfo_Hide(playerid);
			//if(rotate_trailerid != 0) RotateFreelancerTrailer(rotate_trailerid);
		}
		else Error(playerid, "Nie jesteś w miejscu docelowym.");
	}
	else if(compare(params, "anuluj") || compare(params, "a"))//anulowanie
	{
		if(!whileorder) return Error(playerid, "Nie jesteś w trakcie zlecenia.");
		ClearTrailerSelect(playerid);//linijka niekonieczna ale może odbugować jakby coś poszło nie tak
		if(gracz[playerid][cargo_trailerdid] != 0) //porządek z naczepą
		{
			cargoveh = gracz[playerid][cargo_trailerdid];//musi only here - kiedy jest poza autem, zeby naczepe wrocilo
			DetachTrailerFromVehicle(cargoveh);
			SetVehicleToRespawn(cargoveh);//niech nie losuje od nowa
			pojazd[cargoveh][v_trailerupdate] = 0;
			UpdateDynamic3DTextLabelText(pojazd[cargoveh][v_text3d], 0x009933FF, pojazd[cargoveh][v_text3d_strcache]);
		}

		for(new v = GetVehiclePoolSize(); v != -1; v--)//usuwanie ladunków ze wszystkich pojazdów gracza
		{
			if(pojazd[v][v_owner_type] == VEHICLE_PLAYER && pojazd[v][v_owner] == gracz[playerid][UID])
			{
				pojazd[v][v_cargo] = 0;
				pojazd[v][v_cargo_amount] = 0;
			}
		}
		mq_format("UPDATE `pojazdy` SET `rlg_c_id`='0', `rlg_c_amount`='0', `rlg_c_price`='0', `rlg_c_score`='0', `rlg_c_distance`='0.0', `rlg_c_tX`='0.0', `rlg_c_tY`='0.0', `rlg_c_tZ`='0.0' WHERE `owner_type`='%d' AND `owner`='%d';", VEHICLE_PLAYER, gracz[playerid][UID]);
		mq_send("QUpdateRlgCargo");
		gracz[playerid][gfv_waitforpickup] = 0;
		gracz[playerid][cargo_trailerdid] = 0;
		gracz[playerid][routelog_start_time] = 0;
		ResetVehicleADRData(cargoveh);
		ClearObjective(playerid);
		StopRouteGPS(playerid);//ClearObjective tez to robi, ale nie zadziala, jesli nie bylo objective a byly np flary
		CargoInfo_Hide(playerid);
		Info(playerid, "Zlecenie "COL_RED"anulowano"COL_RED".");
		LeftNotifyShow(playerid, "info", "Twoje ~y~zlecenie~w~ zostalo ~r~anulowane~w~.", LN_RED);
	}
	else//przyjęcie zlecenia
	{
		if(whileorder) return Error(playerid, "Jesteś już podczas zlecenia. Aby je anulować wpisz: "COL_ORANGE"/zlecenie anuluj"COL_WHITE".");
		if(IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Jesteś na służbie.");
		if(IsPlayerOnDutyCompany(playerid)) return Error(playerid, "Jesteś na służbie.");
		if(vehicleid == 0) return Error(playerid, "Zamierzasz nosić towar na plecach?");
		if(pojazd[vehicleid][v_owner_type] != VEHICLE_PLAYER) return Error(playerid, "Pojazd musi być pojazdem prywatnym.");
		if(trucktype == 0) return Error(playerid, "Ten pojazd nie jest przystosowany do przewozu ładunków.");
		if(GetPlayerVehicleSeat(playerid) != 0) return Error(playerid, "Musisz być kierowcą.");
		if(!IsPlayerCanDrive(playerid, vehicleid)) return Error(playerid, "Musisz mieć uprawnienia do tego pojazdu.");
		new zlecenieid;
		if(!sscanf(params,"d", zlecenieid))//-- /zlecenie id_zlecenia - np: /zlecenie 123
		{
			if(trucktype == 1) //naczepa
			{
				if(pojazd[zlecenieid][v_owner_type] == VEHICLE_PUBLIC && pojazd[zlecenieid][v_owner] == VO_MPTRAILER && pojazd[cargoveh][v_trailerupdate] < serwer[time_timestamp])
				{
					gracz[playerid][td_confirmcargo] = true;
					SetTimerEx("D_CargoConfirmShowT", 500, false, "dd", playerid, zlecenieid);
				} 
				else Error(playerid, "Niepoprawne UID zlecenia.");
			}
			else//van
			{
				if(0 < zlecenieid < MAX_GOODSFORVANS)
				{
					gracz[playerid][td_confirmcargo] = true;
					SetTimerEx("D_CargoConfirmShowV", 500, false, "dd", playerid, zlecenieid);
				} 
				else Error(playerid, "Niepoprawne UID zlecenia.");
			}
		}
		else//jeśli nie podał id zlecenia, to wyświetlanie mu stosownej listy
		{
			if(trucktype == 1) ShowFreeLancerGoodsTrailer(playerid, 0);
			else ShowFreeLancerGoodsVan(playerid, 0);
		}
	}
	return 1;
}

stock ShowFreeLancerGoodsTrailer(playerid, startvid)
{
	new vehiclepoolsize = GetVehiclePoolSize();
	if(startvid <= 0) startvid = 0;
	if(startvid > vehiclepoolsize) startvid = vehiclepoolsize;
	new strGoodsList[3072];
	new strSrcZone[24], strDstZone[24];
	new count_listitem;
	gracz[playerid][flcargolist_arrownext] = false;//reset info na temat strzałek (do przewijania) na liście
	gracz[playerid][flcargolist_arrowback] = false;//reset info na temat strzałek (do przewijania) na liście
	format(strGoodsList, 3072, "{FFFFFF}UID {8D8D8D}zlecenia\t{FFFFFF}Nazwa {8D8D8D}towaru {00C5B6}[waga]\t"COL_WHITE"(Jak daleko?) {00E16A}Źródło "COL_LIME"» [dystans] » {FF4343}Cel\t{028900}Wynagrodzenie\n");
	for(new v = startvid-1; v != -1; v--)//sprawdzanie czy są jakieś poprzednie towary (czy pokazać strzałke wstecz?)
	{
		if(pojazd[v][v_owner_type] == VEHICLE_PUBLIC && pojazd[v][v_owner] == VO_MPTRAILER)
		{
			if(pojazd[v][v_trailerupdate] > serwer[time_timestamp]) continue;//blokada wyświetlania zlecen, które sa zajete
			format(strGoodsList, 3072, "%s"COL_RED"««««\t"COL_RED"««««\t"COL_RED"««««\t"COL_RED"««««\n", strGoodsList);
			gracz[playerid][flcargolist_arrowback] = true;//jest strzałka wstecz
			break;
		}
	}
	new bool:shadowline;
	new slc[9];//shadowline color
	for(new v = startvid; v < vehiclepoolsize; v++)
	{
		if(pojazd[v][v_owner_type] == VEHICLE_PUBLIC && pojazd[v][v_owner] == VO_MPTRAILER)
		{
			if(pojazd[v][v_trailerupdate] > serwer[time_timestamp]) continue;//blokada wyświetlania zlecen, które sa zajete
			Get2DZone(pojazd[v][v_X], pojazd[v][v_Y], strSrcZone, 32);
			Get2DZone(pojazd[pojazd[v][v_cargo_destvid]][v_X], pojazd[pojazd[v][v_cargo_destvid]][v_Y], strDstZone, 32);
			slc = (shadowline) ? ("{8D8D8D}") : ("{FFFFFF}");
			new Float:source_raw_distance = GetDistanceBetweenPoints(pojazd[v][v_X], pojazd[v][v_Y], pojazd[v][v_Z], gracz[playerid][PosX], gracz[playerid][PosX], gracz[playerid][PosZ]);
			new Float:source_km_dist = source_raw_distance/CONST_KM;
			format(strGoodsList, 3072, "%s%s%d\t%s%s%s {00C5B6}[%d kg]\t(%0.1fkm) {00E16A}%s "COL_LIME"» [%0.1f km] » {FF4343}%s\t"COL_GREEN"+$%d "COL_RED"|"COL_BLUE" +%d score\n", strGoodsList, slc, v,(goods[pojazd[v][v_cargo]][gds_adr]) ? (""COL_ORANGE"[ADR]") : ("") , slc, goods[pojazd[v][v_cargo]][gds_name], pojazd[v][v_cargo_amount], source_km_dist, strSrcZone, pojazd[v][v_cargo_distance], strDstZone, pojazd[v][v_cargo_price], pojazd[v][v_cargo_score]);
			if(shadowline) shadowline = false;
			else shadowline = true;
			gui_cache[playerid][count_listitem][0] = v;//id pojazdu z towarem
			count_listitem++;
			gracz[playerid][lastpage_flcargolist] = v;
		}
		if(count_listitem > MAX_FLPERPAGEGOODS) break;
	}
	for(new v = gracz[playerid][lastpage_flcargolist]+1; v < vehiclepoolsize; v++)//sprawdzanie czy są jakieś nastepne towary (czy pokazać strzałke next?)
	{
		if(pojazd[v][v_owner_type] == VEHICLE_PUBLIC && pojazd[v][v_owner] == VO_MPTRAILER)
		{
			if(pojazd[v][v_trailerupdate] > serwer[time_timestamp]) continue;//blokada wyświetlania zlecen, które sa zajete
			format(strGoodsList, 3072, "%s"COL_GREEN"»»»»\t"COL_GREEN"»»»»\t"COL_GREEN"»»»»\t"COL_GREEN"»»»»", strGoodsList);
			gracz[playerid][flcargolist_arrownext] = true;//jest strzałka next
			break;
		}
	}
	gracz[playerid][flcargolist_count_goods] = count_listitem;
	//printf("goods list char count: %d", strlen(strGoodsList));
	if(count_listitem == 0) return Error(playerid, "W tej chwili brak dostępnych zleceń. Sprawdź za chwilę.");
	Dialog_Show(playerid, TRAILERGOODS, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_GREEN"Dostępne zlecenia - Freelancer"COL_RED" «•", strGoodsList, "OK", "Anuluj");
	return 1;
}

stock ShowFreeLancerGoodsVan(playerid, startgfv)
{
	new vansgoodspoolsize = GetVansGoodsSize();
	if(startgfv <= 0) startgfv = 0;
	if(startgfv > vansgoodspoolsize) startgfv = vansgoodspoolsize;
	new strGoodsList[3072];
	new strSrcZone[24], strDstZone[24];
	new count_listitem;
	gracz[playerid][flcargolist_arrownext] = false;//reset info na temat strzałek (do przewijania) na liście
	gracz[playerid][flcargolist_arrowback] = false;//reset info na temat strzałek (do przewijania) na liście
	format(strGoodsList, 3072, "{FFFFFF}UID {8D8D8D}Zlecenia\t{FFFFFF}Nazwa {8D8D8D}towaru {00C5B6}[waga]\t"COL_WHITE"(Jak daleko?) {00E16A}Źródło "COL_LIME"» [dystans] » {FF4343}Cel\t{028900}Wynagrodzenie\n");
	for(new g = startgfv-1; g != -1; g--)//sprawdzanie czy są jakieś poprzednie towary (czy pokazać strzałke wstecz?)
	{
		if(g == 0) continue;//omija 0 
		format(strGoodsList, 3072, "%s"COL_RED"««««\t"COL_RED"««««\t"COL_RED"««««\t"COL_RED"««««\n", strGoodsList);
		gracz[playerid][flcargolist_arrowback] = true;//jest strzałka wstecz
		break;
	}
	new bool:shadowline;
	new slc[9];//shadowline color
	for(new g = startgfv; g < vansgoodspoolsize; g++)
	{
		if(g == 0) continue;//omija 0 
		Get2DZone(load_place_van[goods_for_vans[g][gfv_loadplace_sourceid]][0], load_place_van[goods_for_vans[g][gfv_loadplace_sourceid]][1], strSrcZone, 32);
		Get2DZone(load_place_van[goods_for_vans[g][gfv_loadplace_targetid]][0], load_place_van[goods_for_vans[g][gfv_loadplace_targetid]][1], strDstZone, 32);
		slc = (shadowline) ? ("{8D8D8D}") : ("{FFFFFF}");
		new Float:source_raw_distance = GetDistanceBetweenPoints(load_place_van[goods_for_vans[g][gfv_loadplace_sourceid]][0], load_place_van[goods_for_vans[g][gfv_loadplace_sourceid]][1], load_place_van[goods_for_vans[g][gfv_loadplace_sourceid]][2], gracz[playerid][PosX], gracz[playerid][PosX], gracz[playerid][PosZ]);
		new Float:source_km_dist = source_raw_distance/CONST_KM;
		format(strGoodsList, 3072, "%s%s%d\t%s%s%s {00C5B6}[%d kg]\t(%0.1fkm) {00E16A}%s"COL_LIME"» [%0.1f km] » {FF4343}%s\t"COL_GREEN"+$%d "COL_RED"|"COL_BLUE" +%d score\n", strGoodsList, slc, g, (goods[goods_for_vans[g][gfv_goodid]][gds_adr]) ? (""COL_ORANGE"[ADR]") : ("") , slc, goods[goods_for_vans[g][gfv_goodid]][gds_name], goods_for_vans[g][gfv_amount], source_km_dist, strSrcZone, goods_for_vans[g][gfv_distance], strDstZone, goods_for_vans[g][gfv_price], goods_for_vans[g][gfv_score]);
		if(shadowline) shadowline = false;
		else shadowline = true;
		gui_cache[playerid][count_listitem][0] = g;//id towaru
		count_listitem++;
		gracz[playerid][lastpage_flcargolist] = g;
		if(count_listitem > MAX_FLPERPAGEGOODS) break;
	}
	for(new g = gracz[playerid][lastpage_flcargolist]+1; g < vansgoodspoolsize; g++)//sprawdzanie czy są jakieś nastepne towary (czy pokazać strzałke next?)
	{
		if(g == 0) continue;//omija 0 
		format(strGoodsList, 3072, "%s"COL_GREEN"»»»»\t"COL_GREEN"»»»»\t"COL_GREEN"»»»»\t"COL_GREEN"»»»»", strGoodsList);
		gracz[playerid][flcargolist_arrownext] = true;//jest strzałka next
		break;
	}
	gracz[playerid][flcargolist_count_goods] = count_listitem;
	Dialog_Show(playerid, VANGOODS, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_GREEN"Dostępne zlecenia - Freelancer"COL_RED" «•", strGoodsList, "OK", "Anuluj");
	return 1;
}

stock GetVansGoodsSize()
{
	new wynik;
	for(new p; p < MAX_GOODSFORVANS; p++)
	{
		if(goods_for_vans[p][gfv_goodid] > 0)
		{
			wynik = p;
		}
	}
	return wynik;
}

Dialog:VANGOODS(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	//printf("listitem: %d", listitem);
	new action;
	//są obie strzałki
	if(gracz[playerid][flcargolist_arrownext] == true && gracz[playerid][flcargolist_arrowback] == true)
	{
		if(listitem == 0)//back
		{
			action = 1;
		}
		else if(listitem == MAX_FLPERPAGEGOODS+2)//next
		{
			action = 2;
		} 
		else action = 3;
		listitem--;
	}
	else if(gracz[playerid][flcargolist_arrownext] == false && gracz[playerid][flcargolist_arrowback] == true)//jest tylko strzałka wstecz
	{
		if(listitem == 0)//back
		{
			action = 1;
		}
		else action = 3;
		listitem--;
	}
	else if(gracz[playerid][flcargolist_arrownext] == true && gracz[playerid][flcargolist_arrowback] == false)//jest tylko strzałka next
	{
		if(listitem == MAX_FLPERPAGEGOODS+1)//next
		{
			action = 2;
		}
		else action = 3;
	}
	if(action == 1)//przewijanie wstecz
	{
		new prev_gfv; 
		new prev_gfv_startshow;
		for(new g = gracz[playerid][lastpage_flcargolist]; g != -1; g--)//szukanie MAX_FLPERPAGEGOODS wcześniejszych naczep
		{
			if(g == 0) continue;//omija 0
			prev_gfv++;
			prev_gfv_startshow = g;
			if((prev_gfv > (MAX_FLPERPAGEGOODS*2)+1) && gracz[playerid][flcargolist_arrownext] == true)  break;
			else if(prev_gfv > (MAX_FLPERPAGEGOODS+gracz[playerid][flcargolist_count_goods])) break;
		}
		ShowFreeLancerGoodsVan(playerid, prev_gfv_startshow);
	}
	else if(action == 2)//przewijanie next
	{
		ShowFreeLancerGoodsVan(playerid, gracz[playerid][lastpage_flcargolist]+1);
	}
	else if(action == 3)//wybór towaru
	{
		if(gracz[playerid][td_confirmcargo]) return Error(playerid, "Jesteś w trakcie zatwierdzania zlecenia.");
		if(gracz[playerid][cargo_trailerdid] != 0 || gracz[playerid][gfv_waitforpickup] != 0) return Error(playerid, "Jesteś już w trakcie zlecenia.");
		new zid = gui_cache[playerid][listitem][0];
		if(VehicleCapacity(pojazd[GetPlayerVehicleID(playerid)][v_model]) < goods_for_vans[zid][gfv_amount]) return Error(playerid, "Za mała ładowność pojazdu.");
		gracz[playerid][td_confirmcargo] = true;
		SetTimerEx("D_CargoConfirmShowV", 500, false, "dd", playerid, zid);//delay
	}
	
	return 1;
}

Dialog:TRAILERGOODS(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new action;
	//są obie strzałki
	if(gracz[playerid][flcargolist_arrownext] == true && gracz[playerid][flcargolist_arrowback] == true)
	{
		if(listitem == 0)//back
		{
			action = 1;
		}
		else if(listitem == MAX_FLPERPAGEGOODS+2)//next
		{
			action = 2;
		} 
		else action = 3;
		listitem--;
	}
	else if(gracz[playerid][flcargolist_arrownext] == false && gracz[playerid][flcargolist_arrowback] == true)//jest tylko strzałka wstecz
	{
		if(listitem == 0)//back
		{
			action = 1;
		}
		else action = 3;
		listitem--;
	}
	else if(gracz[playerid][flcargolist_arrownext] == true && gracz[playerid][flcargolist_arrowback] == false)//jest tylko strzałka next
	{
		if(listitem == MAX_FLPERPAGEGOODS+1)//next
		{
			action = 2;
		}
		else action = 3;
	}
	
	if(action == 1)//przewijanie wstecz
	{
		new prev_trailers; 
		new prev_trailer_startshow;
		for(new v = gracz[playerid][lastpage_flcargolist]; v != -1; v--)//szukanie MAX_FLPERPAGEGOODS wcześniejszych naczep
		{
			if(pojazd[v][v_owner_type] == VEHICLE_PUBLIC && pojazd[v][v_owner] == VO_MPTRAILER)
			{
				if(pojazd[v][v_trailerupdate] > serwer[time_timestamp]) continue;//blokada wyświetlania zlecen, które sa zajete
				prev_trailers++;
				prev_trailer_startshow = v;
				if((prev_trailers > (MAX_FLPERPAGEGOODS*2)+1) && gracz[playerid][flcargolist_arrownext] == true)  break;
				else if(prev_trailers > (MAX_FLPERPAGEGOODS+gracz[playerid][flcargolist_count_goods])) break;
			}
		}
		ShowFreeLancerGoodsTrailer(playerid, prev_trailer_startshow);
	}
	else if(action == 2)//przewijanie next
	{
		ShowFreeLancerGoodsTrailer(playerid, gracz[playerid][lastpage_flcargolist]+1);
	}
	else if(action == 3)//wybór towaru
	{
		if(gracz[playerid][td_confirmcargo]) return Error(playerid, "Jesteś w trakcie zatwierdzania zlecenia.");
		if(gracz[playerid][cargo_trailerdid] != 0 || gracz[playerid][gfv_waitforpickup] != 0) return Error(playerid, "Jesteś już w trakcie zlecenia.");
		new vid = gui_cache[playerid][listitem][0];
		gracz[playerid][td_confirmcargo] = true;
		SetTimerEx("D_CargoConfirmShowT", 500, false, "dd", playerid, vid);//delay
	}
	
	return 1;
}

forward D_CargoConfirmShowT(playerid, vid);//wyswietlanie potwierdzenia naczepa
public D_CargoConfirmShowT(playerid, vid)
{
	gracz[playerid][td_confirmcargo] = false;
	if(pojazd[vid][v_trailerupdate] > serwer[time_timestamp]) return Error(playerid, "To zlecenie jest obecnie nieaktualne.");
	if(goods[pojazd[vid][v_cargo]][gds_adr] == true && gracz[playerid][upr_adr] == 0) return Error(playerid, "Brak uprawnień ADR.");

	for(new p = PlayerPoolSize(); p != -1; p--)//sprawdzanie czy przypadkiem ktos sie szybciej nie namyslil
	{
		if(p == playerid) continue;
		if(gracz[p][loggedin])
		{
			if(gracz[p][cargo_trailerdid] == vid)//czyli już ktoś inny ja ma zarezerwowaną
			{
				return Error(playerid, "Zlecenie jest już nieaktualne.");
			}
		}
	}
	gracz[playerid][cargo_confirmtrailer] = vid;
	new strSrcZone[24], strDstZone[24];
	Get2DZone(pojazd[vid][v_X], pojazd[vid][v_Y], strSrcZone, 24);
	Get2DZone(pojazd[pojazd[vid][v_cargo_destvid]][v_X], pojazd[pojazd[vid][v_cargo_destvid]][v_Y], strDstZone, 24);
	SetPVarInt(playerid, "confcarg_type", 1);
	CargoConfirmShow(playerid, goods[pojazd[vid][v_cargo]][gds_name], pojazd[vid][v_cargo_amount], goods[pojazd[vid][v_cargo]][gds_adr], pojazd[vid][v_cargo_price], pojazd[vid][v_cargo_score], vid, strSrcZone, strDstZone, pojazd[vid][v_cargo_distance]);
	return 1;
}

forward D_CargoConfirmShowV(playerid, zid);//wyswietlanie potwierdzenia van
public D_CargoConfirmShowV(playerid, zid)
{
	gracz[playerid][td_confirmcargo] = false;
	if(goods[goods_for_vans[zid][gfv_goodid]][gds_adr] == true && gracz[playerid][upr_adr] == 0) return Error(playerid, "Brak uprawnień ADR.");
	new strSrcZone[24], strDstZone[24];
	gracz[playerid][cargo_confirmtrailer] = zid;
	Get2DZone(load_place_van[goods_for_vans[zid][gfv_loadplace_sourceid]][0], load_place_van[goods_for_vans[zid][gfv_loadplace_sourceid]][1], strSrcZone, 32);
	Get2DZone(load_place_van[goods_for_vans[zid][gfv_loadplace_targetid]][0], load_place_van[goods_for_vans[zid][gfv_loadplace_targetid]][1], strDstZone, 32);
	SetPVarInt(playerid, "confcarg_type", 2);
	CargoConfirmShow(playerid, goods[goods_for_vans[zid][gfv_goodid]][gds_name], goods_for_vans[zid][gfv_amount], goods[goods_for_vans[zid][gfv_goodid]][gds_adr], goods_for_vans[zid][gfv_price], goods_for_vans[zid][gfv_score], -1, strSrcZone, strDstZone, goods_for_vans[zid][gfv_distance]);
	return 1;
}

stock confcarg_OnPlayerClickTextDraw(playerid, Text:clickedid)//confirm cargo, potwierdzenie odbioru towaru
{
	if(gracz[playerid][td_confirmcargo]) 
	{
		if(clickedid == td_g_confirmcargo3)//accept
		{
			switch(GetPVarInt(playerid, "confcarg_type"))
			{
				case 1://naczepa
				{
					new vid = gracz[playerid][cargo_confirmtrailer];
					if(pojazd[vid][v_trailerupdate] > serwer[time_timestamp]) return Error(playerid, "To zlecenie jest obecnie nieaktualne.");
					for(new p = PlayerPoolSize(); p != -1; p--)//sprawdzanie czy przypadkiem ktos sie szybciej nie namyslil
					{
						if(p == playerid) continue;
						if(gracz[p][loggedin])
						{
							if(gracz[p][cargo_trailerdid] == vid)//czyli już ktoś inny ja ma zarezerwowaną
							{
								return Error(playerid, "To zlecenie jest obecnie nieaktualne.");
							}		
						}
					}

					//ZLECENIE ZAAKCEPTOWANE:
					gracz[playerid][cargo_trailerdid] = vid;
					StartRouteGPS(playerid, pojazd[vid][v_X], pojazd[vid][v_Y], pojazd[vid][v_Z]);
					CargoConfirmHide(playerid);
					SetVehicleToRespawn(vid);
					SelectTrailer(playerid, vid);
					UpdateDynamic3DTextLabelText(pojazd[vid][v_text3d], 0x00000000, "w trasie");
					LeftNotifyShow(playerid, "Sukces!", "Zlecenie zostalo przyjete. Musisz odebrac naczepe z towarem. Naczepa zostala oznaczona ~r~czerwonym~w~ markerem na minimapie, trasa do niej zostala wytyczona przez ~y~nawigacje GPS~w~.", LN_BLUE, 15);
				}
				case 2://VAN
				{
					//ZLECENIE ZAAKCEPTOWANE:
					new zid = gracz[playerid][cargo_confirmtrailer];
					gracz[playerid][gfv_waitforpickup] = zid;
					SetObjective(playerid, ""COL_RED"• "COL_BLUE"Aby odebrać zlecenie, wpisz: "COL_GREEN"/zlecenie odbierz "COL_GREY"[lub klawisz H] "COL_RED"•",  load_place_van[goods_for_vans[zid][gfv_loadplace_sourceid]][0], load_place_van[goods_for_vans[zid][gfv_loadplace_sourceid]][1], load_place_van[goods_for_vans[zid][gfv_loadplace_sourceid]][2], true);
					CargoConfirmHide(playerid);
					LeftNotifyShow(playerid, "Sukces!", "Zlecenie zostalo przyjete. Musisz zaladowac towar. Miejsce odbioru towaru zostalo oznaczone ~r~czerwona~w~ flaga na minimapie, trasa do niej zostala wytyczona przez ~y~nawigacje GPS~w~.", LN_BLUE, 15);
					//SendClientMessage(playerid, -1, "WIP");
				}
			}
			return 1;
		}
		if(clickedid == td_g_confirmcargo4 || clickedid == Text:INVALID_TEXT_DRAW)//decline
		{
			CargoConfirmHide(playerid);
			gracz[playerid][cargo_trailerdid] = 0;
			gracz[playerid][gfv_waitforpickup] = 0;
			gracz[playerid][cargo_confirmtrailer] = 0;
			SetPVarInt(playerid, "confcarg_type", 0);
			return 1;
		}
	}
	return 1;
}

task cargofl_OnTrailerAttached(playerid, trailerid)
{
	if(gracz[playerid][cargo_trailerdid] == trailerid) 
	{
		new v = trailerid;
		new strTemp[24];
		Get2DZone(pojazd[pojazd[v][v_cargo_destvid]][v_X], pojazd[pojazd[v][v_cargo_destvid]][v_Y], strTemp, 20);
		CargoInfo_Show(playerid, goods[pojazd[trailerid][v_cargo]][gds_name], pojazd[trailerid][v_cargo_amount], 0, strTemp, pojazd[trailerid][v_cargo_price], "kurs");
		ClearTrailerSelect(playerid);
		new Float:fX, Float:fY;
		GetXYInFrontOfPos(pojazd[pojazd[v][v_cargo_destvid]][v_X], pojazd[pojazd[v][v_cargo_destvid]][v_Y], pojazd[pojazd[v][v_cargo_destvid]][v_R], fX, fY, 10.0);
		new strDesc[512];
		format(strDesc, 512, ""COL_RED"• "COL_BLUE"Aby dostarczyć zlecenie, wpisz: "COL_GREEN"/zlecenie dostarcz "COL_GREY"[lub klawisz H] "COL_RED"•");
		SetObjective(playerid, strDesc, fX, fY, pojazd[pojazd[v][v_cargo_destvid]][v_Z], true);
		LeftNotifyShow(playerid, "Misja", "Dostarcz naczepe z towarem do celu. Cel zostal oznaczony ~r~czerwona~w~ flaga na minimapie, trasa do niej zostala wytyczona przez ~y~nawigacje GPS~w~.", LN_BLUE, 15);
		if(gracz[playerid][routelog_start_time] == 0) RegisterStartLogKurs(playerid);
	}
	return 1;
}

task cargofl_OnTrailerDetached(playerid, trailerid)
{
	if(gracz[playerid][cargo_trailerdid] == trailerid) 
	{
		CargoInfo_Hide(playerid);
		ClearTrailerSelect(playerid);
		ClearObjective(playerid);
	}
	return 1;
}


stock RotateFreelancerTrailers()
{
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		RotateFreelancerTrailer(v);
	}
	/*
	//naczepy bez towaru
	new nbt;
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		if(pojazd[v][v_owner_type] == VEHICLE_PUBLIC && pojazd[v][v_owner] == VO_MPTRAILER)
		{
			if(pojazd[v][v_cargo] == 0) nbt++;
		}
	}
	printf("%d naczep bez towaru", nbt);*/
	return 1;
}


stock RotateFreelancerTrailer(trailerid)
{
	new random_cargo;
	new trailer_model;
	new v = trailerid;
	if(pojazd[v][v_owner_type] == VEHICLE_PUBLIC && pojazd[v][v_owner] == VO_MPTRAILER)
	{
		random_cargo = random(sizeof(goods));
		if(random_cargo == 0 || random_cargo == 1) random_cargo = 2;
		switch(goods[random_cargo][gds_trailertype])
		{
			case 0: 
			{
				if(random(3) == 1) trailer_model = 591;
				else trailer_model = 435;
			}
			case 1: trailer_model = 450;
			case 2: trailer_model = 584;
		}
		pojazd[v][v_model] = trailer_model;
		pojazd[v][v_color][0] = random(255);
		pojazd[v][v_color][1] = random(255);

		new new_vehicleid = CreateVehicle(pojazd[v][v_model], pojazd[v][v_X],  pojazd[v][v_Y], pojazd[v][v_Z], pojazd[v][v_R], pojazd[v][v_color][0], pojazd[v][v_color][1], VEH_SINGLERESP_TIME);
		for(new pojazd_info:pi; pi < pojazd_info; pi++)
		{
			pojazd[new_vehicleid][pi] = pojazd[v][pi];
		}
		if(IsValidDynamic3DTextLabel(pojazd[v][v_text3d]))//pobiera 3dtext ze starego pojazdu i daje go na nowy
		{
			new Float:offsetXYZ[3];
			new Float:draw_dist;
			new test_los;
			new label_string[512];
			Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, pojazd[v][v_text3d], E_STREAMER_ATTACH_OFFSET_X, offsetXYZ[0]);
			Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, pojazd[v][v_text3d], E_STREAMER_ATTACH_OFFSET_Y, offsetXYZ[1]);
			Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, pojazd[v][v_text3d], E_STREAMER_ATTACH_OFFSET_Z, offsetXYZ[2]);
			Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, pojazd[v][v_text3d], E_STREAMER_DRAW_DISTANCE, draw_dist);
			test_los = Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL, pojazd[v][v_text3d], E_STREAMER_TEST_LOS);
			GetDynamic3DTextLabelText(pojazd[v][v_text3d], label_string);
			pojazd[new_vehicleid][v_text3d] = CreateDynamic3DTextLabel(label_string, -1, offsetXYZ[0], offsetXYZ[1], offsetXYZ[2], draw_dist, .attachedvehicle = new_vehicleid, .testlos = test_los);
		}
		RemoveVehicle(v);
		v = new_vehicleid;

		pojazd[v][v_cargo] = random_cargo;
		switch(random(4))
		{
			case 0: pojazd[v][v_cargo_amount] = VehicleCapacity(trailer_model)-1000-random(9999);
			case 1: pojazd[v][v_cargo_amount] = VehicleCapacity(trailer_model)-3000-random(9999);
			case 2: pojazd[v][v_cargo_amount] = VehicleCapacity(trailer_model)-5000-random(9999);
			default: pojazd[v][v_cargo_amount] = VehicleCapacity(trailer_model)-7000-random(9999);
		}
		if(pojazd[v][v_cargo_amount] < 1300) pojazd[v][v_cargo_amount] = 1300;
		//wytyczanie przeznaczenia towaru
		new potential_destinations[MAX_VEHICLES];
		new pd_counter;
		for(new d = GetVehiclePoolSize(); d != -1; d--)
		{
			if(pojazd[d][v_owner_type] == VEHICLE_PUBLIC && pojazd[d][v_owner] == VO_MPTRAILER)
			{
				if(GetDistanceBetweenPoints(pojazd[d][v_X], pojazd[d][v_Y], pojazd[d][v_Z], pojazd[v][v_X], pojazd[v][v_Y], pojazd[v][v_Z]) > 3500.0)
				{
					potential_destinations[pd_counter] = d;
					pd_counter++;
				}
			}
		}
		pd_counter--;
		new random_pd =  random(pd_counter);
		pojazd[v][v_cargo_destvid] = potential_destinations[random_pd];
		//-> -> -> RFT_OnCalculatePath -> -> ->
		RGPS_CalculatePath(pojazd[v][v_X], pojazd[v][v_Y], pojazd[v][v_Z], pojazd[pojazd[v][v_cargo_destvid]][v_X], pojazd[pojazd[v][v_cargo_destvid]][v_Y], pojazd[pojazd[v][v_cargo_destvid]][v_Z], v+10000, 0);
		//-> -> -> RFT_OnCalculatePath -> -> ->
	}
	return 1;
}


//OFF TYMCZASOWO:
/*
stock RotateFreelancerTrailer(trailerid)
{
	new random_cargo;
	new trailer_model;
	new v = trailerid;
	if(pojazd[v][v_owner_type] == VEHICLE_PUBLIC && pojazd[v][v_owner] == VO_MPTRAILER)
	{
		random_cargo = random(sizeof(goods));
		if(random_cargo == 0 || random_cargo == 1) random_cargo = 2;
		RemoveVehicle(v, false);
		switch(goods[random_cargo][gds_trailertype])
		{
			case 0: 
			{
				if(random(3) == 1) trailer_model = 591;
				else trailer_model = 435;
			}
			case 1: trailer_model = 450;
			case 2: trailer_model = 584;
		}
		pojazd[v][v_model] = trailer_model;
		pojazd[v][v_cargo] = random_cargo;
		switch(random(4))
		{
			case 0: pojazd[v][v_cargo_amount] = VehicleCapacity(trailer_model)-1000-random(9999);
			case 1: pojazd[v][v_cargo_amount] = VehicleCapacity(trailer_model)-3000-random(9999);
			case 2: pojazd[v][v_cargo_amount] = VehicleCapacity(trailer_model)-5000-random(9999);
			default: pojazd[v][v_cargo_amount] = VehicleCapacity(trailer_model)-7000-random(9999);
		}
		pojazd[v][v_color][0] = random(255);
		pojazd[v][v_color][1] = random(255);
		CreateVehicle(pojazd[v][v_model], pojazd[v][v_X],  pojazd[v][v_Y], pojazd[v][v_Z], pojazd[v][v_R], pojazd[v][v_color][0], pojazd[v][v_color][1], -1);
		//wytyczanie przeznaczenia towaru
		new potential_destinations[32];
		new pd_counter;
		for(new d = GetVehiclePoolSize(); d != -1; d--)//szukamy potencjalnych tras
		{
			if(pojazd[d][v_owner_type] == VEHICLE_PUBLIC && pojazd[d][v_owner] == VO_MPTRAILER)
			{
				if(GetDistanceBetweenPoints(pojazd[d][v_X], pojazd[d][v_Y], pojazd[d][v_Z], pojazd[v][v_X], pojazd[v][v_Y], pojazd[v][v_Z]) > 1500.0)
				{
					if(pd_counter < 32)
					{
						potential_destinations[pd_counter] = d;
						pd_counter++;
					}
					else break;
				}
			}
		}
		pd_counter--;
		new random_pd =  random(pd_counter);
		pojazd[v][v_cargo_destvid] = potential_destinations[random_pd];
		new nodesrc = NearestNodeFromPoint(pojazd[v][v_X], pojazd[v][v_Y], pojazd[v][v_Z]);
		new nodedst = NearestNodeFromPoint(pojazd[pojazd[v][v_cargo_destvid]][v_X], pojazd[pojazd[v][v_cargo_destvid]][v_Y], pojazd[pojazd[v][v_cargo_destvid]][v_Z]);
		CalculatePath(nodesrc, nodedst, v+10000, false, 9.5);//-> -> -> RFT_OnCalculatePath -> -> ->
	}
	
	//naczepy bez towaru
	//new nbt;
	//for(new v = GetVehiclePoolSize(); v != -1; v--)
	//{
	//	if(pojazd[v][v_owner_type] == VEHICLE_PUBLIC && pojazd[v][v_owner] == VO_MPTRAILER)
	//	{
	//		if(pojazd[v][v_cargo] == 0) nbt++;
	//	}
	//}
	//printf("%d naczep bez towaru", nbt);
	return 1;
}
*/
stock RotateFreelancerGoods()//dla vanów
{
	new random_cargo;
	new rand_sourceid;
	for(new g; g < MAX_GOODSFORVANS; g++)
	{
		//filtrowanie potencjanlych towarów stałych
		new potential_cargos[40];
		new pc_counter;
		for(new c; c <  sizeof(goods); c++)
		{
			if(c == 0 || c == 1) continue;
			if(goods[c][gds_trailertype] == 0)
			{
				if(pc_counter < 40)
				{
					potential_cargos[pc_counter] = c;
					//printf("%s", goods[c][gds_name] );
					pc_counter++;
				}
				else break;
			}
		}
		pc_counter--;
		random_cargo = random(pc_counter);
	//	if(random_cargo == 0 || random_cargo == 1) random_cargo = 2;
		goods_for_vans[g][gfv_goodid] = potential_cargos[random_cargo];
		switch(random(5))
		{
			case 0: goods_for_vans[g][gfv_amount] = 400-random(100);
			case 1: goods_for_vans[g][gfv_amount] = 500-random(100);
			case 2: goods_for_vans[g][gfv_amount] = 700-random(100);
			case 3: goods_for_vans[g][gfv_amount] = 800-random(100);
			default: goods_for_vans[g][gfv_amount] = 1000-random(100);
		}
		//wytyczanie trasy
		rand_sourceid = random(MAX_VANLOADS);
		goods_for_vans[g][gfv_loadplace_sourceid] = rand_sourceid;//losowe źródło
		//szukanie odpowiednio daleko celu:
		new potential_destinations[MAX_VANLOADS];
		new pd_counter;
		for(new d; d < MAX_VANLOADS; d++)
		{
			if(GetDistanceBetweenPoints(load_place_van[d][0], load_place_van[d][1], load_place_van[d][2], load_place_van[rand_sourceid][0], load_place_van[rand_sourceid][1], load_place_van[rand_sourceid][2]) > 900.0)
			{
				potential_destinations[pd_counter] = d;
				pd_counter++;
			}
		}
		pd_counter--;
		new random_pd =  random(pd_counter);
		goods_for_vans[g][gfv_loadplace_targetid] =  potential_destinations[random_pd];
		//-> -> -> RFG_OnCalculatePath -> -> ->
		new Float:tempFrom[3];
		tempFrom[0] = load_place_van[goods_for_vans[g][gfv_loadplace_sourceid]][0];
		tempFrom[1] = load_place_van[goods_for_vans[g][gfv_loadplace_sourceid]][1];
		tempFrom[2] = load_place_van[goods_for_vans[g][gfv_loadplace_sourceid]][2];
		new Float:tempTarget[3];
		tempTarget[0] = load_place_van[goods_for_vans[g][gfv_loadplace_targetid]][0];
		tempTarget[1] = load_place_van[goods_for_vans[g][gfv_loadplace_targetid]][1];
		tempTarget[2] = load_place_van[goods_for_vans[g][gfv_loadplace_targetid]][2];
		RGPS_CalculatePath(tempFrom[0], tempFrom[1], tempFrom[2], tempTarget[0], tempTarget[1], tempTarget[2], g+20000, 0);
		//-> -> -> RFG_OnCalculatePath -> -> ->
		//printf("van goods debug: goodid: %d  ; amount: %d, sourceid: %d ; targetid: %d ; ", goods_for_vans[g][gfv_goodid], goods_for_vans[g][gfv_amount], goods_for_vans[g][gfv_loadplace_sourceid], goods_for_vans[g][gfv_loadplace_targetid]);
	}
	return 1;
}

stock RFT_OnCalculatePath(v, Float:distance)
{
	pojazd[v][v_cargo_distance] =  distance/CONST_KM;
	new strTextCargoInfo[512];
	new strSrcZone[32], strDstZone[32];
	Get2DZone(pojazd[v][v_X], pojazd[v][v_Y], strSrcZone, 32);
	Get2DZone(pojazd[pojazd[v][v_cargo_destvid]][v_X], pojazd[pojazd[v][v_cargo_destvid]][v_Y], strDstZone, 32);
	format(strTextCargoInfo, 512, "« "COL_LIME"ZLECENIE"COL_GREEN" »\n"); 
	if(goods[pojazd[v][v_cargo]][gds_adr]) format(strTextCargoInfo, 512, "%s"COL_RED"•"COL_ORANGE" ADR "COL_RED"•\n", strTextCargoInfo); 
	format(strTextCargoInfo, 512, "%s"COL_RED"•{00C5B6} %s [%d kg]"COL_RED"•\n", strTextCargoInfo, goods[pojazd[v][v_cargo]][gds_name], pojazd[v][v_cargo_amount]); 
	//format(strTextCargoInfo, 512, "%s"COL_RED"•{00A599} %s "COL_LIME"» [%0.1f km] »{00A599} %s "COL_RED"•\n", strTextCargoInfo, strSrcZone, pojazd[v][v_cargo_distance], strDstZone); 
	format(strTextCargoInfo, 512, "%s"COL_RED"• "COL_LIME"» [%0.1f km] » "COL_RED"•\n", strTextCargoInfo, pojazd[v][v_cargo_distance]); 
	//*kalkulacja wynagrodzenia - start
	new  calc_money,  calc_score;
	calc_money = floatround(pojazd[v][v_cargo_distance])*PRICE_FOR_KM_TRANSPORT_TRUCK;//*$ za kilometr
	if(goods[pojazd[v][v_cargo]][gds_adr]) calc_money += 4500;//premia za ADR
	calc_score = pojazd[v][v_cargo_amount]/7000;//ile score za ilosc towaru
	//if(calc_money < 500) calc_money = 500;
	if(calc_score < 1) calc_score = 1;
	else if(calc_score > 1 && pojazd[v][v_cargo_distance] < 15.0) calc_score = 1;
	//*kalkulacja wynagrodzenia - end
	pojazd[v][v_cargo_price] = calc_money;
	pojazd[v][v_cargo_score] = calc_score;
	format(strTextCargoInfo, 512, "%s"COL_RED"•"COL_LIME" » [%s] » "COL_RED"•\n", strTextCargoInfo, strDstZone); 
	format(strTextCargoInfo, 512, "%s"COL_RED"•{00C5B6} +$%d "COL_RED"•\n", strTextCargoInfo, calc_money); 
	format(strTextCargoInfo, 512, "%s"COL_RED"•{00A599} +%d score"COL_RED"•\n", strTextCargoInfo, calc_score); 
	format(strTextCargoInfo, 512, "%s"COL_GREEN"» "COL_LIME"/zlecenie %d "COL_GREEN"«\n", strTextCargoInfo, v);
	UpdateDynamic3DTextLabelText(pojazd[v][v_text3d], 0x009933FF, strTextCargoInfo);
	format(pojazd[v][v_text3d_strcache], 512, strTextCargoInfo);//zrzucanie danych do cache
	return 1;
}

stock RFG_OnCalculatePath(g, Float:distance)
{
	goods_for_vans[g][gfv_distance] =  distance/CONST_KM;
	//*kalkulacja wynagrodzenia - start
	new  calc_money,  calc_score;
	calc_money = floatround(goods_for_vans[g][gfv_distance])*PRICE_FOR_KM_TRANSPORT_VAN;//*$ za kilometr
	if(goods[goods_for_vans[g][gfv_goodid]][gds_adr]) calc_money += 4500;//premia za ADR
	calc_score = goods_for_vans[g][gfv_amount]/7000;//ile score za ilosc towaru
	//premia za trudne trasy
	new strSrcZone[32], strDstZone[32];
	Get2DZone(load_place_van[goods_for_vans[g][gfv_loadplace_sourceid]][0], load_place_van[goods_for_vans[g][gfv_loadplace_sourceid]][1], strSrcZone, 24);
	Get2DZone(load_place_van[goods_for_vans[g][gfv_loadplace_targetid]][0], load_place_van[goods_for_vans[g][gfv_loadplace_targetid]][1], strDstZone, 24);
	//if(calc_money < 500) calc_money = 500;
	if(calc_score < 1) calc_score = 1;
	else if(calc_score > 1 && goods_for_vans[g][gfv_distance] < 15.0) calc_score = 1;
	//*kalkulacja wynagrodzenia - end
	goods_for_vans[g][gfv_price] = calc_money;
	goods_for_vans[g][gfv_score] = calc_score;
	return 1;
}

/*
Delivered_MainShow(playerid);
Delivered_SecondShow(playerid);
Delivered_ThirdShow(playerid);
Delivered_Row1(playerid, "] Dostarczenie ladunku");
format(strTemp, 128, "~r~+~w~%d~g~$ ~w~~r~+~w~%d~b~ score", pojazd[cargoveh][v_cargo_price], pojazd[cargoveh][v_cargo_score]);
Delivered_Row2(playerid, strTemp);
Delivered_Money(playerid, pojazd[cargoveh][v_cargo_price]);
Delivered_Score(playerid, pojazd[cargoveh][v_cargo_score]);
Delivered_ExitInfoShow(playerid);
*/
task Process_DeliveredSummary(playerid, step, hard_route)
{
	if(gracz[playerid][delivered_window_process] && step == 0) return 0;
	new cargoveh = gracz[playerid][delivered_cargovid];
	const delay = 200;	
	switch(step)
	{
		case 0://podstawa - start
		{
			PlayerPlaySound(playerid, 1190, 0, 0, 0);
			Delivered_MainShow(playerid);
			SetTimerEx("Process_DeliveredSummary", delay, false, "dd", playerid, 1);
			format(gracz[playerid][DeliveredSummary_row1], 1024, "");
			format(gracz[playerid][DeliveredSummary_row2], 1024, "");
			gracz[playerid][delivered_window_totalmoney] = pojazd[cargoveh][v_cargo_price];
			gracz[playerid][delivered_window_totalscore] = pojazd[cargoveh][v_cargo_score];

			gracz[playerid][DeliveredSummary_bonus_price] = 0;
			gracz[playerid][DeliveredSummary_bonus_sc] = 0;

			gracz[playerid][delivered_hardroute] = hard_route;

			gracz[playerid][delivered_window_process] = true;
		}
		case 1://podstawa
		{
			PlayerPlaySound(playerid, 1190, 0, 0, 0);
			Delivered_SecondShow(playerid);
			SetTimerEx("Process_DeliveredSummary", delay, false, "dd", playerid, 2);
		}
		case 2://podstawa
		{
			PlayerPlaySound(playerid, 1190, 0, 0, 0);
			Delivered_ThirdShow(playerid);
			SetTimerEx("Process_DeliveredSummary", delay, false, "dd", playerid, 3);
		}
		case 3://podstawa - row 1
		{
			PlayerPlaySound(playerid, 1190, 0, 0, 0);
			format(gracz[playerid][DeliveredSummary_row1], 1024, "] Dostarczenie ladunku");
			Delivered_Row1(playerid, gracz[playerid][DeliveredSummary_row1]);
			SetTimerEx("Process_DeliveredSummary", delay, false, "dd", playerid, 4);
		}
		case 4://podstawa - row 2
		{
			PlayerPlaySound(playerid, 1190, 0, 0, 0);
			format(gracz[playerid][DeliveredSummary_row2], 1024, "~r~+~w~%d~g~$ ~w~~r~+~w~%d~b~ score", gracz[playerid][delivered_window_totalmoney], gracz[playerid][delivered_window_totalscore]);
			Delivered_Row2(playerid, gracz[playerid][DeliveredSummary_row2]);
			SetTimerEx("Process_DeliveredSummary", delay, false, "dd", playerid, 5);
		}
		case 5://dodatkowe premia za VIP - row 1
		{
			if(isvip(playerid))
			{
				format(gracz[playerid][DeliveredSummary_row1], 1024, "%s~n~] Konto VIP", gracz[playerid][DeliveredSummary_row1]);
				Delivered_Row1(playerid, gracz[playerid][DeliveredSummary_row1]);
				SetTimerEx("Process_DeliveredSummary", delay, false, "dd", playerid, 6);
			}
			else SetTimerEx("Process_DeliveredSummary", 5, false, "dd", playerid, 6);
		}
		case 6://dodatkowe premia za VIP - row 2
		{
			if(isvip(playerid))
			{
				new premia_price = 300;
				new premia_sc = 1;
				gracz[playerid][DeliveredSummary_bonus_price] += premia_price;
				gracz[playerid][DeliveredSummary_bonus_sc] += premia_sc;
				GiveMoney(playerid, gracz[playerid][DeliveredSummary_bonus_price]);
				GiveScore(playerid, gracz[playerid][DeliveredSummary_bonus_sc]);
				format(gracz[playerid][DeliveredSummary_row2], 1024, "%s~n~~r~+~w~%d~g~$ ~w~~r~+~w~%d~b~ score", gracz[playerid][DeliveredSummary_row2], premia_price, premia_sc);
				Delivered_Row2(playerid, gracz[playerid][DeliveredSummary_row2]);
				SetTimerEx("Process_DeliveredSummary", delay, false, "dd", playerid, 7);
			}
			else SetTimerEx("Process_DeliveredSummary", 5, false, "dd", playerid, 7);
		}
		//--
		case 7://dodatkowe premia za trudne warunki - row 1
		{
			if(gracz[playerid][delivered_hardroute])
			{
				format(gracz[playerid][DeliveredSummary_row1], 1024, "%s~n~] Trudne warunki", gracz[playerid][DeliveredSummary_row1]);
				Delivered_Row1(playerid, gracz[playerid][DeliveredSummary_row1]);
				SetTimerEx("Process_DeliveredSummary", delay, false, "dd", playerid, 8);
			}
			else SetTimerEx("Process_DeliveredSummary", 5, false, "dd", playerid, 8);
		}
		case 8://dodatkowe premia za trudne warunki - row 2
		{
			if(gracz[playerid][delivered_hardroute])
			{
				new premia_price = 1500;
				new premia_sc = 1;
				gracz[playerid][DeliveredSummary_bonus_price] += premia_price;
				gracz[playerid][DeliveredSummary_bonus_sc] += premia_sc;
				GiveMoney(playerid, gracz[playerid][DeliveredSummary_bonus_price]);
				GiveScore(playerid, gracz[playerid][DeliveredSummary_bonus_sc]);
				format(gracz[playerid][DeliveredSummary_row2], 1024, "%s~n~~r~+~w~%d~g~$ ~w~~r~+~w~%d~b~ score", gracz[playerid][DeliveredSummary_row2], premia_price, premia_sc);
				Delivered_Row2(playerid, gracz[playerid][DeliveredSummary_row2]);
				SetTimerEx("Process_DeliveredSummary", delay, false, "dd", playerid, 9);
			}
			else SetTimerEx("Process_DeliveredSummary", 5, false, "dd", playerid, 9);
		}
		//--
		case 9://dodatkowa premia za jazde pod wpływem - row 1
		{
			new lastdrunk = serwer[time_timestamp]-gracz[playerid][timestamp_lastdrunk];
			SetPVarInt(playerid, "drunk_bonus", 0);
			if(lastdrunk > 60*2 && lastdrunk < 60*20 && gracz[playerid][when_tipsy] > 0)//pomiędzy 2 a 14 minutą
			{
				SetPVarInt(playerid, "drunk_bonus", 1);
				format(gracz[playerid][DeliveredSummary_row1], 1024, "%s~n~] Pod wplywem %%", gracz[playerid][DeliveredSummary_row1]);
				Delivered_Row1(playerid, gracz[playerid][DeliveredSummary_row1]);
				SetTimerEx("Process_DeliveredSummary", delay, false, "dd", playerid, 10);
			}
			else SetTimerEx("Process_DeliveredSummary", 5, false, "dd", playerid, 10);
		}
		case 10://dodatkowa premia za jazde pod wpływem - row 2
		{
			if(GetPVarInt(playerid, "drunk_bonus") == 1)
			{
				new premia_price = 2300;
				new premia_sc = 1;
				gracz[playerid][DeliveredSummary_bonus_price] += premia_price;
				gracz[playerid][DeliveredSummary_bonus_sc] += premia_sc;
				GiveMoney(playerid, gracz[playerid][DeliveredSummary_bonus_price]);
				GiveScore(playerid, gracz[playerid][DeliveredSummary_bonus_sc]);
				format(gracz[playerid][DeliveredSummary_row2], 1024, "%s~n~~r~+~w~%d~g~$ ~w~~r~+~w~%d~b~ score", gracz[playerid][DeliveredSummary_row2], premia_price, premia_sc);
				Delivered_Row2(playerid, gracz[playerid][DeliveredSummary_row2]);
				SetTimerEx("Process_DeliveredSummary", delay, false, "dd", playerid, 11);
			}
			else SetTimerEx("Process_DeliveredSummary", 5, false, "dd", playerid, 11);
			SetPVarInt(playerid, "drunk_bonus", 0);
		}
		//--
		case 11://dodatkowa premia za idealny adr - row 1
		{
			if(gracz[playerid][delivered_adr_status] == 1)
			{
				format(gracz[playerid][DeliveredSummary_row1], 1024, "%s~n~] Idealny ADR", gracz[playerid][DeliveredSummary_row1]);
				Delivered_Row1(playerid, gracz[playerid][DeliveredSummary_row1]);
				SetTimerEx("Process_DeliveredSummary", delay, false, "dd", playerid, 12);
			}
			else SetTimerEx("Process_DeliveredSummary", 5, false, "dd", playerid, 12);
		}
		case 12://dodatkowa premia za idealny adr - row 2
		{
			if(gracz[playerid][delivered_adr_status] == 1)
			{
				new premia_price = 3500;
				new premia_sc = 1;
				gracz[playerid][DeliveredSummary_bonus_price] += premia_price;
				gracz[playerid][DeliveredSummary_bonus_sc] += premia_sc;
				GiveMoney(playerid, gracz[playerid][DeliveredSummary_bonus_price]);
				GiveScore(playerid, gracz[playerid][DeliveredSummary_bonus_sc]);
				format(gracz[playerid][DeliveredSummary_row2], 1024, "%s~n~~r~+~w~%d~g~$ ~w~~r~+~w~%d~b~ score", gracz[playerid][DeliveredSummary_row2], premia_price, premia_sc);
				Delivered_Row2(playerid, gracz[playerid][DeliveredSummary_row2]);
				SetTimerEx("Process_DeliveredSummary", delay, false, "dd", playerid, 13);
			}
			else SetTimerEx("Process_DeliveredSummary", 5, false, "dd", playerid, 13);
		}
		case 13://podstawa - wyświetl cene
		{
			PlayerPlaySound(playerid, 4201, 0, 0, 0);
			Delivered_Money(playerid, gracz[playerid][delivered_window_totalmoney]+gracz[playerid][DeliveredSummary_bonus_price]);
			SetTimerEx("Process_DeliveredSummary", delay, false, "dd", playerid, 14);
		}
		case 14://podstawa - wyświetl score
		{
			Delivered_Score(playerid, gracz[playerid][delivered_window_totalscore]+gracz[playerid][DeliveredSummary_bonus_sc]);
			SetTimerEx("Process_DeliveredSummary", delay, false, "dd", playerid, 15);
		}
		case 15://podstawa - end
		{
			PlayerPlaySound(playerid, 5202, 0, 0, 0);
			pojazd[cargoveh][v_trailerupdate] = 0;
			gracz[playerid][cargo_trailerdid] = 0;
			gracz[playerid][gfv_waitforpickup] = 0;
			gracz[playerid][delivered_window_process] = false;
			for(new v = GetVehiclePoolSize(); v != -1; v--)//usuwanie ladunków ze wszystkich pojazdów gracza
			{
				if(pojazd[v][v_owner_type] == VEHICLE_PLAYER && pojazd[v][v_owner] == gracz[playerid][UID])
				{
					pojazd[v][v_cargo] = 0;
					pojazd[v][v_cargo_amount] = 0;
				}
			}
			ResetVehicleADRData(cargoveh);
			Delivered_ExitInfoShow(playerid);
		}
	}
	return 1;
}

task LoadingCargo(playerid, prog_var)
{
	if(!gracz[playerid][loggedin]) return 1;
	if(prog_var < 100)
	{
		prog_var += 10;
	}
	if(prog_var >= 100)
	{
		ShowAnnTD(playerid, "ZALADOWANO!");
		TogglePlayerControllable(playerid, true);
		SetTimerEx("HideAnn", 2000, false, "d", playerid);
		LeftNotifyShow(playerid, "Zaladowano!", "Towar zostal ~g~zaladowany~w~. Przeznaczenie towaru zostalo oznaczone ~r~czerwona~w~ flaga na minimapie, trasa do niej zostala wytyczona przez ~y~nawigacje GPS~w~.", LN_BLUE, 15);
		return 1;
	}
	TogglePlayerControllable(playerid, false);
	new strProg[32];
	format(strProg, 32, "Ladowanie... %d%%", prog_var);
	PlayerPlaySound(playerid, 1039, 0, 0, 0);
	SetVehicleVelocity(gracz[playerid][opu_vehicleid], 0.0, 0.0, -0.02);
	HideAnn(playerid);
	if(prog_var > 60) ShowAnnTD(playerid, strProg, 255, COLOR_GREEN);
	else if(prog_var > 30) ShowAnnTD(playerid, strProg, 255, COLOR_YELLOW);
	else if(prog_var > 0) ShowAnnTD(playerid, strProg, 255, COLOR_RED);
	SetTimerEx("LoadingCargo", 1000, false, "dd", playerid, prog_var);
	return 1;
}


task Process_UpTrailerIdleTime(playerid)
{
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		if(IsVehicleTrailer(pojazd[v][v_model]))
		{
			if(gracz[playerid][cargo_trailerdid] == v)
			{
				if(IsPlayerInRangeOfPoint(playerid, 100.0, pojazd[v][v_idle_X], pojazd[v][v_idle_Y], pojazd[v][v_idle_Z]))
				{
					pojazd[v][v_trailerupdate] = serwer[time_timestamp]+(MAX_RELOGTIME+1)*60;//minutka zapasu
				}
			}
		}
	}
	return 1;
}