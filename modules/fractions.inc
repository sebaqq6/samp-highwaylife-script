stock Init_Fractions()
{
	mq_format("SELECT * FROM `fractions_data`;");
	mq_send("LoadFractionsFromDB");
	//*************************************skiny frakcji
	//***policja
	fractions[F_POLICE][fr_skins_male][0] = 265;//meskie
	fractions[F_POLICE][fr_skins_male][1] = 267;//meskie
	fractions[F_POLICE][fr_skins_male][2] = 280;//meskie
	fractions[F_POLICE][fr_skins_male][3] = 281;//meskie
	fractions[F_POLICE][fr_skins_male][4] = 20025;//meskie
	fractions[F_POLICE][fr_skins_male][5] = 20026;//meskie
	fractions[F_POLICE][fr_skins_male][6] = 20027;//meskie
	fractions[F_POLICE][fr_skins_male][7] = 20028;//meskie
	fractions[F_POLICE][fr_skins_male][8] = 20029;//meskie
	fractions[F_POLICE][fr_skins_male][9] = 20030;//meskie
	fractions[F_POLICE][fr_skins_male][10] = 20031;//meskie
	fractions[F_POLICE][fr_skins_female][0] = 306;//damskie
	fractions[F_POLICE][fr_skins_female][1] = 307;//damskie
	//***straż graniczna
	fractions[F_BORDERGUARD][fr_skins_male][0] = 311;//meskie
	fractions[F_BORDERGUARD][fr_skins_male][1] = 310;//meskie
	fractions[F_BORDERGUARD][fr_skins_male][2] = 287;//meskie
	fractions[F_BORDERGUARD][fr_skins_male][3] = 282;//meskie
	fractions[F_BORDERGUARD][fr_skins_male][4] = 61;//meskie
	fractions[F_BORDERGUARD][fr_skins_male][5] = 20016;//meskie
	fractions[F_BORDERGUARD][fr_skins_male][6] = 20017;//meskie
	fractions[F_BORDERGUARD][fr_skins_female][0] = 309;//damskie
	fractions[F_BORDERGUARD][fr_skins_female][1] = 191;//damskie
	//***służby ratunkowe
	fractions[F_EMERGENCY][fr_skins_male][0]= 276;//meskie
	fractions[F_EMERGENCY][fr_skins_male][1]= 275;//meskie
	fractions[F_EMERGENCY][fr_skins_male][2]= 274;//meskie
	fractions[F_EMERGENCY][fr_skins_male][3]= 277;//meskie
	fractions[F_EMERGENCY][fr_skins_male][4]= 278;//meskie
	fractions[F_EMERGENCY][fr_skins_male][5]= 279;//meskie
	fractions[F_EMERGENCY][fr_skins_male][6]= 20032;//meskie
	fractions[F_EMERGENCY][fr_skins_male][7]= 20033;//meskie
	fractions[F_EMERGENCY][fr_skins_male][8]= 20034;//meskie
	fractions[F_EMERGENCY][fr_skins_male][9]= 20035;//meskie
	fractions[F_EMERGENCY][fr_skins_male][10]= 20036;//meskie
	fractions[F_EMERGENCY][fr_skins_male][11]= 20037;//meskie
	fractions[F_EMERGENCY][fr_skins_female][0] = 308;//damskie
	//***pomoc drogowa
	fractions[F_ROADASSIST][fr_skins_male][0] = 8;//meskie
	fractions[F_ROADASSIST][fr_skins_male][1] = 16;//meskie
	fractions[F_ROADASSIST][fr_skins_male][2] = 42;//meskie
	fractions[F_ROADASSIST][fr_skins_male][3] = 50;//meskie
	fractions[F_ROADASSIST][fr_skins_male][4] = 268;//meskie
	fractions[F_ROADASSIST][fr_skins_male][5] = 260;//meskie
	fractions[F_ROADASSIST][fr_skins_male][6] = 20023;//meskie
	fractions[F_ROADASSIST][fr_skins_male][7] = 20024;//meskie
	fractions[F_ROADASSIST][fr_skins_female][0] = 190;//damskie
	fractions[F_ROADASSIST][fr_skins_female][1] = 90;//damskie
	//***taxi
	fractions[F_TAXI][fr_skins_male][0] = 46;//meskie
	fractions[F_TAXI][fr_skins_male][1] = 185;//meskie
	fractions[F_TAXI][fr_skins_male][2] = 98;//meskie
	fractions[F_TAXI][fr_skins_male][3] = 240;//meskie
	fractions[F_TAXI][fr_skins_female][0] = 194;//damskie
	fractions[F_TAXI][fr_skins_female][1] = 233;//damskie
	//**mafia
	fractions[F_MAFIA][fr_skins_male][0] = 272;//meskie
	fractions[F_MAFIA][fr_skins_male][1] = 127;//meskie
	fractions[F_MAFIA][fr_skins_male][2] = 124;//meskie
	fractions[F_MAFIA][fr_skins_male][3] = 125;//meskie
	fractions[F_MAFIA][fr_skins_male][4] = 126;//meskie
	fractions[F_MAFIA][fr_skins_male][5] = 20018;//meskie
	fractions[F_MAFIA][fr_skins_male][6] = 20019;//meskie
	fractions[F_MAFIA][fr_skins_male][7] = 20020;//meskie
	fractions[F_MAFIA][fr_skins_male][8] = 20021;//meskie
	fractions[F_MAFIA][fr_skins_male][9] = 20022;//meskie
	fractions[F_MAFIA][fr_skins_female][0] = 152;//damskie
	fractions[F_MAFIA][fr_skins_female][1] = 85;//damskie
	fractions[F_MAFIA][fr_skins_female][2] = 55;//damskie
	//inne
	CreateDynamic3DTextLabel("« "COL_BLUE"WIĘZIENIE "COL_GREEN"»\n"COL_RED"• "COL_WHITE"Wpisz "COL_RED"/areszt [idgracza] [czas w min] [nr celi] [powód (max 64 znaki)]"COL_WHITE" aby uwięzić gracza. "COL_RED"•", 0x009933FF, XYZ_PRISONADD, 6.0);
	new strTemp[256];
	for(new c; c < sizeof(prisons); c++)
	{
		format(strTemp, 256, ""COL_BLUE"« "COL_WHITE"CELA NR: "COL_RED"%d "COL_BLUE"»", c);
		CreateDynamic3DTextLabel(strTemp, 0x009933FF, prisons[c][0], prisons[c][1], prisons[c][2], 10.0);
	}
	CreateDynamic3DTextLabel("« "COL_BLUE"LAKIERNIA "COL_GREEN"»\n"COL_RED"• "COL_FMSG"W tym miejscu otrzymasz spray, do malowania karoserii. "COL_RED"•\n"COL_RED"• "COL_FMSG"Wpisz "COL_RED"/spray"COL_FMSG" aby skonfigurować kolory spraya. "COL_RED"•\n"COL_RED"• "COL_FMSG"Podejdź do pojazdu i użyj spraya aby zacząć go malować. "COL_RED"•", 0x009933FF, XYZ_SPRAY, 10.0);
	ClearNapadRAM();
	return 1;
}

stock IsPlayerOnDutyFraction(playerid)
{
	if(gracz[playerid][frakcja] == 0) return 0;
	if(gracz[playerid][frakcja_onduty] == gracz[playerid][frakcja]) return 1;
	/*new skin = GetPlayerSkin(playerid);
	if(gracz[playerid][frakcja] == F_POLICE)
	{
		if(skin == 265 || skin == 267 || skin == 280 || skin == 281 || skin == 306 || skin == 307) return 1;
	}
	else if(gracz[playerid][frakcja] == F_BORDERGUARD)
	{
		if(skin == 311 || skin == 310 || skin == 287 || skin == 282 || skin == 309 || skin == 191 || skin == 61) return 1;
	}
	else if(gracz[playerid][frakcja] == F_EMERGENCY)
	{
		if(skin == 276 || skin == 275 || skin == 274 || skin == 277 || skin == 278 || skin == 279 || skin == 308) return 1;
	}
	else if(gracz[playerid][frakcja] == F_ROADASSIST)
	{
		if(skin == 8 || skin == 16 || skin == 42 || skin == 50 || skin == 190 || skin == 90 || skin == 268 || skin == 260) return 1;
	}
	else if(gracz[playerid][frakcja] == F_TAXI)
	{
		if(skin == 46 || skin == 185 || skin == 98 || skin == 240 || skin == 194 || skin == 233) return 1;
	}*/
	return 0;
}



task LoadFractionsFromDB()
{
	mq_getdata();
	new i;
	if(rekordy)
	{
		new t_id, t_name[24];
		new strTemp[1024];
		while(i < rekordy)
		{
			cache_get_value_name_int(i, "id", 			t_id);
			cache_get_value_name(i, "name", t_name, 24);
			cache_get_value_name_int(i, "pay_min", 			fractions[t_id][fr_paymin]);
			cache_get_value_name_int(i, "pay_max", 			fractions[t_id][fr_paymax]);
			cache_get_value_name_float(i, "duty_x", 			fractions[t_id][fr_dutyX]);
			cache_get_value_name_float(i, "duty_y", 			fractions[t_id][fr_dutyY]);
			cache_get_value_name_float(i, "duty_z", 			fractions[t_id][fr_dutyZ]);
			cache_get_value_name_int(i, "money", 			fractions[t_id][fr_money]);
			cache_get_value_name_int(i, "multiplier", 			fractions[t_id][fr_multiplier]);
			cache_get_value_name_int(i, "add_intval1", 			fractions[t_id][fr_intval1]);
			cache_get_value_name_int(i, "add_intval2", 			fractions[t_id][fr_intval2]);
			cache_get_value_name_int(i, "add_intval3", 			fractions[t_id][fr_intval3]);
			cache_get_value_name_int(i, "add_intval4", 			fractions[t_id][fr_intval4]);
			fractions[t_id][fr_pickup] = CreateDynamicPickup(1275, 1, fractions[t_id][fr_dutyX], fractions[t_id][fr_dutyY], fractions[t_id][fr_dutyZ]);
			fractions[t_id][fr_icon] = CreateDynamicMapIcon(fractions[t_id][fr_dutyX], fractions[t_id][fr_dutyY], fractions[t_id][fr_dutyZ], FractionIcon(t_id), 0, .streamdistance = 1000.0, .style = MAPICON_GLOBAL);
			format(strTemp, 1024, ""COL_GREEN"« "COL_BLUE"SŁUŻBA - %s "COL_GREEN"»\n", GetFractionName(t_id, 1));
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_ORANGE"PPM"COL_GREY" lub "COL_ORANGE"/duty start"COL_GREY" aby rozpocząć pracę. "COL_RED"•\n", strTemp);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_ORANGE"PPM"COL_GREY" lub "COL_ORANGE"/duty stop"COL_GREY" aby zakończyć pracę. "COL_RED"•\n", strTemp);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_ORANGE"/duty info"COL_GREY" aby sprawdzić status służby. "COL_RED"•\n", strTemp);
			format(strTemp, 1024, "%s"COL_RED"• "COL_GREY"Użyj "COL_ORANGE"/duty skin"COL_GREY" aby zmienić skin. "COL_RED"•\n", strTemp);
			fractions[t_id][fr_text3d] = CreateDynamic3DTextLabel(strTemp, -1, fractions[t_id][fr_dutyX], fractions[t_id][fr_dutyY], fractions[t_id][fr_dutyZ], 15.0);
			printf("[LOAD] Dane frakcji %s[%d-%d] zostaly zaladowane!", t_name, t_id, i);
			//przeliczanie kasy frakcji z score
			new t_score;
			cache_get_value_name_int(i, "score", t_score);
			new fprice = t_score*fractions[t_id][fr_multiplier];

			fractions[t_id][fr_money] +=  fprice;
			printf("[KASA FRAKCJI] Dodano %d$ do konta frakcji: %s. Saldo: %d$", fprice, t_name, fractions[t_id][fr_money]);
			mq_format("UPDATE `fractions_data` SET `score`='0', `money`='%d' WHERE `id`='%d';", fractions[t_id][fr_money], t_id);
			mq_send("QUpdateFractionMoneyScore");
			//----
			i++;
		}
	}
	return 1;
}

stock SaveFractionAddValues(fid)
{
	mq_format("UPDATE `fractions_data` SET `add_intval1`='%d', `add_intval2`='%d', `add_intval3`='%d', `add_intval4`='%d' WHERE `id`='%d';", fractions[fid][fr_intval1], fractions[fid][fr_intval2], fractions[fid][fr_intval3], fractions[fid][fr_intval4], fid);
	mq_send("QUpdateFracAddValues");
	return 1;
}

stock FractionIcon(fid)
{
	switch(fid)
	{
		case F_POLICE: return 30;
		case F_BORDERGUARD: return 62;
		case F_EMERGENCY: return 20;
		case F_ROADASSIST: return 27;
		case F_TAXI: return 44;
		case F_MAFIA: return 23;
	}
	return 0;
}

CMD:duty(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
	if(TruckerWhileOrderCheck(playerid)) return Error(playerid, "Jesteś podczas zlecenia. Aby je anulować wpisz: "COL_ORANGE"/zlecenie anuluj"COL_WHITE".");
	if(IsPlayerOnDutyCompany(playerid)) return Error(playerid, "Jesteś na służbie w firmie, możesz tutaj użyć: /cduty stop");
	if(gracz[playerid][pursuit_enabled]) return Error(playerid, "Nie możesz zmieniać statusu duty podczas pościgu.");
	if(compare(params, "start"))
	{
		if(IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Już jesteś na służbie.");
		if(IsPlayerInRangeOfPoint(playerid, 2.0, fractions[fid][fr_dutyX], fractions[fid][fr_dutyY], fractions[fid][fr_dutyZ]))
		{
			gracz[playerid][scoreduty_multiplier] = 1;
			if(gracz[playerid][frakcja] == F_POLICE)//możliwość używania cywila
			{
				Dialog_Show(playerid, DUTYSKIN, DIALOG_STYLE_LIST, ""COL_RED"•» "COL_WHITE"Czy chcesz użyć skinu frakcyjnego? "COL_RED"«•", ""COL_RED"•» "COL_GREEN"Wybierz skin frakcyjny\n"COL_RED"•» "COL_BLUE"Użyj swojego skinu", "Wybierz", "Anuluj");
			}
			else//obowiązek - skin frakcyjny
			{
				dialog_DUTYSKIN(playerid, 1, 0, "null");
			}
		} 
		else Error(playerid, "Nie jesteś w szatni swojej frakcji.");
	}
	else if(compare(params, "stop"))
	{
		if(!IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Nie jesteś na służbie.");
		new cid = gracz[playerid][firma];
		if(IsPlayerInRangeOfPoint(playerid, 2.0, company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ]) || IsPlayerInRangeOfPoint(playerid, 2.0, fractions[fid][fr_dutyX], fractions[fid][fr_dutyY], fractions[fid][fr_dutyZ]))
		{
			new strDutyMsg[256];
			format(strDutyMsg, 256,  "{63666A}••• Gracz {%06x}%s(%d) {63666A}zakończył służbę jako %s {63666A}(%d minut) •••", GetPlayerColor(playerid) >>> 8, nick(playerid), playerid, GetFractionName(fid, 1), gracz[playerid][time_duty_total]/60);
			SavePublicChatLog(strDutyMsg);
			SendClientMessageToAllEx(0x63666AFF, "••• Gracz {%06x}%s(%d) {63666A}zakończył służbę jako %s {63666A}(%d minut) •••", GetPlayerColor(playerid) >>> 8, nick(playerid), playerid, GetFractionName(fid, 1), gracz[playerid][time_duty_total]/60);
			SetPlayerSkin(playerid, gracz[playerid][Skin]);
			ResetPlayerWeapons(playerid);
			SetPlayerArmour(playerid, 0);
			UpdatePlayerColor(playerid);
			gracz[playerid][scoreduty_multiplier] = 0;
			gracz[playerid][frakcja_onduty] = 0;
			new strDutyInfo[1024];
			format(strDutyInfo, 1024, ""COL_WHITE"Zszedłeś z duty frakcji: %s"COL_WHITE".\n", GetFractionName(fid, 1));
			format(strDutyInfo, 1024, "%s"COL_WHITE"Przerwano sesje duty która trwała: "COL_GREEN"%d minut"COL_WHITE".\n", strDutyInfo, (gracz[playerid][time_duty]/60));
			new Float:kasa_procent = procent(float((gracz[playerid][time_duty]/60)), float(MAX_DUTYSESSION));
			new Float:kasa_wynik = kasa_procent*float(gracz[playerid][frakcja_wyplata])/100.0;
			if(floatround(kasa_wynik) > 0)
			{
				format(strDutyInfo, 1024, "%s"COL_WHITE"Otrzymujesz "COL_BLUE"%0.1f%%"COL_WHITE" wypłaty czyli "COL_LIME"%d$"COL_WHITE".\n", strDutyInfo, kasa_procent, floatround(kasa_wynik));
			
				if(fractions[fid][fr_money] > floatround(kasa_wynik))
				{
					fractions[fid][fr_money] -= floatround(kasa_wynik);
					mq_format("UPDATE `fractions_data` SET `money`='%d' WHERE `id`='%d';", fractions[fid][fr_money], fid);
					mq_send("QUpdateFractionMoneyScore");
					GiveMoney(playerid, floatround(kasa_wynik));
				}
				else format(strDutyInfo, 1024, "%s"COL_RED"UPS! Twojej frakcji nie stać na wypłatę!\n", strDutyInfo);
				ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_WHITE"Przerwanie sesji "COL_RED"«•", strDutyInfo, "Zamknij", "");
			}
		}
		else  Error(playerid, "Nie jesteś w szatni swojej frakcji.");
	}
	else if(compare(params, "info"))
	{
		if(!IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Nie jesteś na służbie.");
		new strDutyInfo[1024];
		format(strDutyInfo, 1024, ""COL_WHITE"Jesteś na służbie w frakcji: %s"COL_WHITE".\n", GetFractionName(fid, 1));
		format(strDutyInfo, 1024, "%s"COL_WHITE"Sesja duty na serwerze trwa: "COL_ORANGE"%d minut"COL_GREY" (ta wartość jest ustalana przez administracje)"COL_WHITE".\n", strDutyInfo, MAX_DUTYSESSION);
		format(strDutyInfo, 1024, "%s"COL_WHITE"Twoja stawka za sesję duty: "COL_LIME"%d$ (%d score"COL_RED"*"COL_LIME")"COL_GREY" (ta wartość jest ustalana przez lidera/v-ce lidera frakcji)"COL_WHITE".\n", strDutyInfo, gracz[playerid][frakcja_wyplata], gracz[playerid][scoreduty_multiplier]);
		format(strDutyInfo, 1024, "%s"COL_WHITE"Twoja sesja duty zakończy się za: "COL_GREEN"%d minut"COL_GREY" (wtedy dostaniesz wypłatę (stawkę za sesje))"COL_WHITE".\n", strDutyInfo, MAX_DUTYSESSION-(gracz[playerid][time_duty]/60));
		format(strDutyInfo, 1024, "%s"COL_WHITE"Ogólnie jesteś na służbie: "COL_GREEN"%d minut"COL_GREY" (liczone od wprowadzenia komendy /duty start)"COL_WHITE".\n", strDutyInfo, (gracz[playerid][time_duty_total]/60));
		new  total_duty_hours, total_duty_min;
		SecToTime2(gracz[playerid][frakcja_totalduty]+gracz[playerid][duty_suma], total_duty_hours, total_duty_min);
		format(strDutyInfo, 1024, "%s"COL_WHITE"Całkowity czas pracy: "COL_GREEN"%d godzin, %d minut"COL_GREY" (ile ogólnie spędziłeś czasu na /duty od chwili zatrudnienia we frakcji)"COL_WHITE".\n", strDutyInfo, total_duty_hours, total_duty_min);
		format(strDutyInfo, 1024, "%s"COL_WHITE"\n"COL_RED"* "COL_WHITE"- Stawka score na początku wynosi 1 i rośnie o 1 do maks. 5 przy każdej wypłacie. Po zejściu z duty resetuje sie.", strDutyInfo);
		ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_WHITE"Informacje dotyczące służby "COL_RED"«•", strDutyInfo, "Zamknij", "");
		UpdatePlayerColor(playerid);
	}
	else if(compare(params, "skin"))
	{
		if(!IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Nie jesteś na służbie.");
		if(IsPlayerInRangeOfPoint(playerid, 2.0, fractions[fid][fr_dutyX], fractions[fid][fr_dutyY], fractions[fid][fr_dutyZ]))
		{
			new skin_sizeof;
			for(new s; s < 8; s++)
			{
				if(gracz[playerid][Plec] == 1)//mężczyzna
				{
					if(fractions[fid][fr_skins_male][s] != 0)
					{
						skin_sizeof++;
					}
				}
				else if(gracz[playerid][Plec] == 2)//kobieta
				{
					if(fractions[fid][fr_skins_female][s] != 0)
					{
						skin_sizeof++;
					}
				}
			}
			//**aktualizacja wypłaty jeśli jest za niska badz za wysoka (np po zmianie przez administracje)
			if(gracz[playerid][frakcja_wyplata] < fractions[fid][fr_paymin]) 
			{
				gracz[playerid][frakcja_wyplata] = fractions[fid][fr_paymin];//jesli ma za mala wyplate
				mq_format("UPDATE `Konta` SET `frakcja_wyplata`='%d' WHERE `id`='%d';", gracz[playerid][frakcja_wyplata],  gracz[playerid][UID]);
				mq_send("QUpdateWorkerPay");
			}
			else if(gracz[playerid][frakcja_wyplata] > fractions[fid][fr_paymax]) 
			{
				gracz[playerid][frakcja_wyplata] = fractions[fid][fr_paymax];//jesli ma za duza wyplate
				mq_format("UPDATE `Konta` SET `frakcja_wyplata`='%d' WHERE `id`='%d';", gracz[playerid][frakcja_wyplata],  gracz[playerid][UID]);
				mq_send("QUpdateWorkerPay");
			}
			//**end
			if(gracz[playerid][Plec] == 1) ShowModelSelectionMenuEx(playerid, fractions[fid][fr_skins_male], skin_sizeof, "Wybierz skin", MSEL_MDUTYSKIN);
			else if(gracz[playerid][Plec] == 2) ShowModelSelectionMenuEx(playerid, fractions[fid][fr_skins_female], skin_sizeof, "Wybierz skin", MSEL_MDUTYSKIN);
		} 
		else Error(playerid, "Nie jesteś w szatni swojej frakcji.");
	}
	else SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /duty [start/stop/info/skin]");
	return 1;
}

Dialog:DUTYSKIN(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0://skin frakcyjny
		{
			new fid = gracz[playerid][frakcja];
			if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
			new skin_sizeof;
			for(new s; s < 12; s++)
			{
				if(gracz[playerid][Plec] == 1)//mężczyzna
				{
					if(fractions[fid][fr_skins_male][s] != 0)
					{
						skin_sizeof++;
					}
				}
				else if(gracz[playerid][Plec] == 2)//kobieta
				{
					if(fractions[fid][fr_skins_female][s] != 0)
					{
						skin_sizeof++;
					}
				}
			}
			//**aktualizacja wypłaty jeśli jest za niska badz za wysoka (np po zmianie przez administracje)
			if(gracz[playerid][frakcja_wyplata] < fractions[fid][fr_paymin]) 
			{
				gracz[playerid][frakcja_wyplata] = fractions[fid][fr_paymin];//jesli ma za mala wyplate
				mq_format("UPDATE `Konta` SET `frakcja_wyplata`='%d' WHERE `id`='%d';", gracz[playerid][frakcja_wyplata],  gracz[playerid][UID]);
				mq_send("QUpdateWorkerPay");
			}
			else if(gracz[playerid][frakcja_wyplata] > fractions[fid][fr_paymax]) 
			{
				gracz[playerid][frakcja_wyplata] = fractions[fid][fr_paymax];//jesli ma za duza wyplate
				mq_format("UPDATE `Konta` SET `frakcja_wyplata`='%d' WHERE `id`='%d';", gracz[playerid][frakcja_wyplata],  gracz[playerid][UID]);
				mq_send("QUpdateWorkerPay");
			}
			//**end
			if(gracz[playerid][Plec] == 1) ShowModelSelectionMenuEx(playerid, fractions[fid][fr_skins_male], skin_sizeof, "Wybierz skin", MSEL_MDUTYSKIN);
			else if(gracz[playerid][Plec] == 2) ShowModelSelectionMenuEx(playerid, fractions[fid][fr_skins_female], skin_sizeof, "Wybierz skin", MSEL_MDUTYSKIN);
		}
		case 1://skin gracza
		{
			new fid = gracz[playerid][frakcja];
			if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
			gracz[playerid][frakcja_onduty] = gracz[playerid][frakcja];//!!!

			if(gracz[playerid][frakcja_wyplata] < fractions[fid][fr_paymin]) 
			{
				gracz[playerid][frakcja_wyplata] = fractions[fid][fr_paymin];//jesli ma za mala wyplate
				mq_format("UPDATE `Konta` SET `frakcja_wyplata`='%d' WHERE `id`='%d';", gracz[playerid][frakcja_wyplata],  gracz[playerid][UID]);
				mq_send("QUpdateWorkerPay");
			}
			else if(gracz[playerid][frakcja_wyplata] > fractions[fid][fr_paymax]) 
			{
				gracz[playerid][frakcja_wyplata] = fractions[fid][fr_paymax];//jesli ma za duza wyplate
				mq_format("UPDATE `Konta` SET `frakcja_wyplata`='%d' WHERE `id`='%d';", gracz[playerid][frakcja_wyplata],  gracz[playerid][UID]);
				mq_send("QUpdateWorkerPay");
			}

			UpdatePlayerColor(playerid);
			//rozdanie broni
			ResetPlayerWeapons(playerid);
			LoadFractionWeapons(playerid, fid);
			//info dla wszystkich
			new strDutyMsg[256];
			format(strDutyMsg, 256, "{31F288}••• Gracz {%06x}%s(%d) {31F288}rozpoczął służbę jako %s {31F288}•••", GetPlayerColor(playerid) >>> 8, nick(playerid), playerid, GetFractionName(fid, 1));
			SavePublicChatLog(strDutyMsg);
			SendClientMessageToAllEx(0x31F288FF, "••• Gracz {%06x}%s(%d) {31F288}rozpoczął służbę jako %s {31F288}•••", GetPlayerColor(playerid) >>> 8, nick(playerid), playerid, GetFractionName(fid, 1));	
			//MOTD:
			mq_format("SELECT `motd` FROM  `fractions_data` WHERE `id`='%d';", fid);
			mq_send("ShowMOTDForPlayer", "d", playerid);
		}
	}
	return 1;
}

stock OnPlayerStartFractionDuty(playerid)
{
	new fid = gracz[playerid][frakcja];
	if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
	UpdatePlayerColor(playerid);
	//rozdanie broni
	ResetPlayerWeapons(playerid);
	LoadFractionWeapons(playerid, fid);
	//MOTD:
	mq_format("SELECT `motd` FROM  `fractions_data` WHERE `id`='%d';", fid);
	mq_send("ShowMOTDForPlayer", "d", playerid);
	return 1;
}

stock LoadFractionWeapons(playerid, fid)
{
	if(!IsPlayerOnDutyFraction(playerid)) return 1;
	//rozdanie broni
	if(fid == F_POLICE)//bronie policyjne
	{
		GivePlayerWeapon(playerid, WEAPON_NITESTICK, 1);//pałka policyjna
		GivePlayerWeapon(playerid, WEAPON_DEAGLE, 1000);//DE
		GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 1000);//shotgun
		GivePlayerWeapon(playerid, WEAPON_M4, 1000);//M4
		if(BattleBlockEx(playerid, 300.0) == 0) SetPlayerArmour(playerid, 100.0);
	}
	else if(fid == F_BORDERGUARD)//bronie sg
	{
		GivePlayerWeapon(playerid, WEAPON_NITESTICK, 1);//pałka policyjna
		/*GivePlayerWeapon(playerid, WEAPON_DEAGLE, 1000);//DE
		GivePlayerWeapon(playerid, WEAPON_MP5, 1000);//mp5
		GivePlayerWeapon(playerid, WEAPON_M4, 1000);//M4
		*/
		GivePlayerWeapon(playerid, WEAPON_DEAGLE, 1000);//DE
		GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 1000);//shotgun
		GivePlayerWeapon(playerid, WEAPON_M4, 1000);//M4
		if(BattleBlockEx(playerid, 300.0) == 0)  SetPlayerArmour(playerid, 100.0);
	}
	else if(fid == F_EMERGENCY)//ratownictwo - gasnica dla strazaków
	{
		switch(GetPlayerSkin(playerid))
		{
			case 277,278,279: 
			{
				GivePlayerWeapon(playerid, WEAPON_FIREEXTINGUISHER, 99999);
				GivePlayerWeapon(playerid, WEAPON_CHAINSAW, 99999);
			}
		}
	}
	else if(fid == F_MAFIA)
	{
		GivePlayerWeapon(playerid, WEAPON_BAT, 1);//Baseball
		/*GivePlayerWeapon(playerid, WEAPON_DEAGLE, 1000);//DE
		GivePlayerWeapon(playerid, WEAPON_TEC9, 1000);//TEC9
		GivePlayerWeapon(playerid, WEAPON_AK47, 1000);//AK47
		*/
		GivePlayerWeapon(playerid, WEAPON_DEAGLE, 1000);//DE
		GivePlayerWeapon(playerid, WEAPON_SHOTGUN, 1000);//shotgun
		GivePlayerWeapon(playerid, WEAPON_M4, 1000);//M4
		if(BattleBlockEx(playerid, 300.0) == 0) SetPlayerArmour(playerid, 100.0);
	}
	SetPlayerArmedWeapon(playerid, 0);
	return 1;
}

task ShowMOTDForPlayer(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new motd[1024];
		cache_get_value_name(0, "motd", motd);
		if(strlen(motd) > 1)
		{
			new strMotd[1024];
			format(strMotd, 1024, ""COL_FMSG"°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°");
			format(strMotd, 1024, "%s\n"COL_RED"%s", strMotd, motd);
			format(strMotd, 1024, "%s\n"COL_FMSG"°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°", strMotd);
			MessageGUIEx(playerid, ""COL_RED"•» "COL_WHITE"Wiadomość powitalna/dnia "COL_RED"«•", strMotd);
		}
	}
	return 1;
}

stock GetFractionName(fid, getcolor = 0)
{
	new fname[32];
	if(getcolor == 1)
	{
		switch(fid)
		{
			case F_POLICE: fname = ""COL_POL"Policja";
			case F_BORDERGUARD: fname = ""COL_BORG"Straż Graniczna";
			case F_EMERGENCY: fname = ""COL_EMRG"Służby Ratunkowe";
			case F_ROADASSIST: fname = ""COL_ROADA"Pomoc Drogowa";
			case F_TAXI: fname = ""COL_TAXI"Taxi";
			case F_MAFIA: fname = ""COL_MAFIA"Mafia Paliwowa";
			default: fname = ""COL_DRV"-brak-";
		}
	}
	else if(getcolor == 2)
	{
		switch(fid)
		{
			case F_POLICE: fname = COL_POL;
			case F_BORDERGUARD: fname = COL_BORG;
			case F_EMERGENCY: fname = COL_EMRG;
			case F_ROADASSIST: fname = COL_ROADA;
			case F_TAXI: fname = COL_TAXI;
			case F_MAFIA: fname = COL_MAFIA;
			default: fname = COL_DRV;
		}
	}
	else
	{
		switch(fid)
		{
			case F_POLICE: fname = "Policja";
			case F_BORDERGUARD: fname = "Straż Graniczna";
			case F_EMERGENCY: fname = "Służby Ratunkowe";
			case F_ROADASSIST: fname = "Pomoc Drogowa";
			case F_TAXI: fname = "Taxi";
			case F_MAFIA: fname = "Mafia Paliwowa";
			default: fname = "-brak-";
		}
	}
	return fname;
}

stock GetFractionNameEx(fid, getcolor = 0)
{
	new fname[32];
	if(getcolor == 1)
	{
		switch(fid)
		{
			case F_POLICE: fname = ""COL_POL"Policja";
			case F_BORDERGUARD: fname = ""COL_BORG"Straz Graniczna";
			case F_EMERGENCY: fname = ""COL_EMRG"Sluzby Ratunkowe";
			case F_ROADASSIST: fname = ""COL_ROADA"Pomoc Drogowa";
			case F_TAXI: fname = ""COL_TAXI"Taxi";
			case F_MAFIA: fname = ""COL_MAFIA"Mafia Paliwowa";
			default: fname = ""COL_DRV"-brak-";
		}
	}
	else if(getcolor == 2)
	{
		switch(fid)
		{
			case F_POLICE: fname = COL_POL;
			case F_BORDERGUARD: fname = COL_BORG;
			case F_EMERGENCY: fname = COL_EMRG;
			case F_ROADASSIST: fname = COL_ROADA;
			case F_TAXI: fname = COL_TAXI;
			case F_MAFIA: fname = COL_MAFIA;
			default: fname = COL_DRV;
		}
	}
	else
	{
		switch(fid)
		{
			case F_POLICE: fname = "Policja";
			case F_BORDERGUARD: fname = "Straz Graniczna";
			case F_EMERGENCY: fname = "Sluzby Ratunkowe";
			case F_ROADASSIST: fname = "Pomoc Drogowa";
			case F_TAXI: fname = "Taxi";
			case F_MAFIA: fname = "Mafia Paliwowa";
			default: fname = "-brak-";
		}
	}
	return fname;
}

stock PermLvlToStr(perm_lvl)
{
	new permstr[32];
	switch(perm_lvl)
	{
		case 0: permstr = "Standard";
		case 1: permstr = ""COL_ORANGE"V-Lider";
		case 2: permstr = ""COL_RED"Lider";
		default: permstr = ""COL_RED"error";
	}
	return permstr;
}


stock FractionWorkersCount(fractionid)
{
	mq_format("SELECT `frakcja` FROM `Konta` WHERE `frakcja`='%d';", fractionid);
	new Cache:count_query = mysql_query(g_SQL, mQuery);
	new wynik = cache_get_row_count_ex();
	cache_delete(count_query);
	return wynik;
}

stock FractionDutyWorkersCount(fractionid)
{
	new wynik;
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][frakcja] == fractionid && IsPlayerOnDutyFraction(p)) wynik++;
		}
	}
	return wynik;
}

stock GiveFractionMoneyOrScore(fid, score, money)
{
	fractions[fid][fr_money] += money;

	mq_format("UPDATE `fractions_data` SET `score`=`score`+'%d', `money`='%d' WHERE `id`='%d';", score, fractions[fid][fr_money], fid);
	mq_send("QUpdateFractionMoneyScore");
	return 1;
}

stock SendFractionMessage(fractionid, message[])
{
	if(fractionid <= 0) return 1;
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][frakcja] == fractionid)
			{
				SendClientMessageEx(p, COLOR_FRACTIONMSG, "[F] %s", message);
			}
		}
	}
	return 1;
}

stock SendFractionNotify(fractionid, title[], content[], type = LN_BLUE, time = 15)
{
	if(fractionid <= 0) return 1;
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][frakcja] == fractionid)
			{
				if(IsPlayerOnDutyFraction(p))
				{
					gracz[p][leftnotify_customsound] = 5205;
					LeftNotifyShow(p, title, content, type, time);
				}
			}
		}
	}
	return 1;
}


stock SavePlayerFractionData(playerid)
{
	if(!gracz[playerid][loggedin]) return 0;
	mysql_escape_string(gracz[playerid][frakcja_tytul], gracz[playerid][frakcja_tytul], 24, g_SQL);
	mq_format("UPDATE `Konta` SET `frakcja`='%d', `frakcja_permlvl`='%d', `frakcja_tytul`='%s', `frakcja_wyplata`='%d', `frakcja_totalduty`='%d' WHERE `id`='%d';", gracz[playerid][frakcja], gracz[playerid][frakcja_permlvl], gracz[playerid][frakcja_tytul], gracz[playerid][frakcja_wyplata], gracz[playerid][frakcja_totalduty], gracz[playerid][UID]);
	mq_send("QUpdateFractionData");
	return 1;
}

CMD:fonline(playerid, params[])
{
	new strFOnline[512];
	format(strFOnline, 512, "Frakcja\tNa służbie");
	format(strFOnline, 512, "%s\n%s\t"COL_RED"%d"COL_GREY" graczy", strFOnline, GetFractionName(F_POLICE, 1), FractionDutyWorkersCount(F_POLICE));
	format(strFOnline, 512, "%s\n%s\t"COL_RED"%d"COL_GREY" graczy", strFOnline, GetFractionName(F_BORDERGUARD, 1), FractionDutyWorkersCount(F_BORDERGUARD));
	format(strFOnline, 512, "%s\n%s\t"COL_RED"%d"COL_GREY" graczy", strFOnline, GetFractionName(F_EMERGENCY, 1), FractionDutyWorkersCount(F_EMERGENCY));
	format(strFOnline, 512, "%s\n%s\t"COL_RED"%d"COL_GREY" graczy", strFOnline, GetFractionName(F_ROADASSIST, 1), FractionDutyWorkersCount(F_ROADASSIST));
	format(strFOnline, 512, "%s\n%s\t"COL_RED"%d"COL_GREY" graczy", strFOnline, GetFractionName(F_TAXI, 1), FractionDutyWorkersCount(F_TAXI));
	format(strFOnline, 512, "%s\n%s\t"COL_RED"%d"COL_GREY" graczy", strFOnline, GetFractionName(F_MAFIA, 1), FractionDutyWorkersCount(F_MAFIA));
	Dialog_Show(playerid, FRONLINE, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_GREEN"Frekwencja frakcji ONLINE"COL_RED" «•", strFOnline, "Wybierz", "Anuluj");
	return 1;
}

Dialog:FRONLINE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new fraction = listitem+1;
	new strFOnline[512];
	new count;
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(!gracz[p][loggedin]) continue;
		if(gracz[p][frakcja] == fraction)
		{
			if(IsPlayerOnDutyFraction(p))
			{
				format(strFOnline, 512, "%s\n{%06x}%s(%d)", strFOnline, GetPlayerColor(p) >>> 8, nick(p), p);
				count++;
			}
		}
	}
	if(count > 0) Dialog_Show(playerid, FRONLINESH, DIALOG_STYLE_LIST, ""COL_RED"•» "COL_GREEN"Lista graczy na służbie"COL_RED" «•", strFOnline, "Zamknij", "");
	else Error(playerid, "Brak pracowników na służbie.");
	return 1;
}

CMD:fkapital(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
	if(!IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Nie jesteś na duty.");
	new strInfo[1024];
	format(strInfo, 1024, ""COL_LIME"» "COL_WHITE"Frakcja: %s", GetFractionName(fid, 1));
	format(strInfo, 1024, "%s\n"COL_LIME"» "COL_WHITE"Aktualny kapitał frakcji: "COL_GREEN"%d$", strInfo, fractions[fid][fr_money]);
	format(strInfo, 1024, "%s\n"COL_LIME"» "COL_WHITE"Aktualny przelicznik "COL_ORANGE"score => $"COL_WHITE": "COL_ORANGE"1 score = %d$", strInfo, fractions[fid][fr_multiplier]);
	format(strInfo, 1024, "%s\n\n{8B8B8B}• kapitał frakcji jest zasilany ze score frakcji, a te z kolei z aktywności pracowników.", strInfo);
	format(strInfo, 1024, "%s\n{8B8B8B}• score frakcji jest przeliczane i resetowane co 24 godziny (co restart serwera).", strInfo);
	format(strInfo, 1024, "%s\n{8B8B8B}• wypłaty dla pracowników są pobierane z kapitału frakcji.", strInfo);
	MessageGUIEx(playerid, ""COL_RED"•» "COL_WHITE"Kapitał frakcji "COL_RED"«•", strInfo);
	return 1;
}

CMD:frakcja(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
	if(gracz[playerid][frakcja_permlvl] == 0) return Error(playerid, "Brak uprawnień.");
	new strFractionMenu[1024];
	format(strFractionMenu, 1024, ""COL_LIME"•»\t"COL_EASY"Lista pracowników "COL_WHITE"("COL_RED"%d"COL_WHITE"/"COL_GREEN"%d"COL_WHITE")\t"COL_LIME"«•", FractionWorkersCount(fid), MAX_FWORKERS);
	format(strFractionMenu, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"Zatrudnij nowego pracownika\t"COL_LIME"«•", strFractionMenu);
	format(strFractionMenu, 1024, "%s\n"COL_LIME"•»\t"COL_EASY"Ustaw wiadomość powitalną\t"COL_LIME"«•", strFractionMenu); 
	format(strFractionMenu, 1024, "%s\n"COL_LIME"•»\t"COL_ORANGE"Zrespawnuj nieużywane pojazdy\t"COL_LIME"«•", strFractionMenu); 
	format(strFractionMenu, 1024, "%s\n"COL_LIME"•»\t"COL_RED"Zamknij wszystkie bramy\t"COL_LIME"«•", strFractionMenu); 
	format(strFractionMenu, 1024, "%s\n"COL_LIME"•»\t"COL_EASY"Score frakcji\t"COL_LIME"«•", strFractionMenu); 
	format(strFractionMenu, 1024, "%s\n"COL_RED"•»\t"COL_BLUE"Kapitał "COL_GREY"[Saldo: "COL_GREEN"%d$"COL_GREY"]\t"COL_RED"«•", strFractionMenu, fractions[fid][fr_money]); 
	new strHeader[512];
	format(strHeader, 512, ""COL_RED"•» "COL_GREEN"Panel frakcji - %s"COL_RED" «•", GetFractionName(fid, 1));
	Dialog_Show(playerid, FRACTIONMENU, DIALOG_STYLE_TABLIST, strHeader, strFractionMenu, "OK", "Anuluj");
	return 1;
}


Dialog:FRACTIONMENU(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new fid = gracz[playerid][frakcja];
	if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
	if(gracz[playerid][frakcja_permlvl] == 0) return Error(playerid, "Brak uprawnień.");
	switch(listitem)
	{
		case 0://Lista pracowników
		{
			mq_format("SELECT `u`.`id`,`u`.`Nick`,`u`.`frakcja_permlvl`,`u`.`frakcja_tytul`,`u`.`LastOnline`,`u`.`frakcja_totalduty` AS `duty_lastweek`,(IFNULL(SUM(`f`.`time`),0)+`u`.`frakcja_totalduty`) AS `duty_suma` FROM `Konta` AS `u` LEFT JOIN `fractions_weekly_duty_time` AS `f` ON `u`.`id`=`f`.`uid` AND `f`.`fid`=`u`.`frakcja` WHERE `u`.`frakcja`='%d' GROUP BY `u`.`id`;", fid);
			mq_send("ShowWorkersList", "d", playerid);
		}
		case 1://Zatrudnij nowego pracownika
		{
			if(FractionWorkersCount(fid) < MAX_FWORKERS)
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
				if(find) Dialog_Show(playerid, FRACTIONADDP, DIALOG_STYLE_TABLIST_HEADERS,  ""COL_RED"•» "COL_WHITE"Lista graczy w pobliżu "COL_RED"«•", strPlayerList, "Wybierz", "Anuluj");
				else Error(playerid, "Nie znaleziono żadnego gracza w pobliżu.");
			}
			else Error(playerid, "W Twojej frakcji znajduje się już maksymalna liczba pracowników.");
		}
		case 2://Ustaw wiadomość powitalną
		{
			new strSetMotd[1024];
			strcat(strSetMotd, ""COL_WHITE"W tym miejscu możesz ustalić "COL_GREEN"wiadomość powitalną"COL_WHITE" dla swojej frakcji.\n");
			strcat(strSetMotd, ""COL_WHITE"Wiadomość ta będzie wyświetlana dla pracowników "COL_RED"w momencie gdy będą wchodzili na służbę"COL_WHITE".\n");
			strcat(strSetMotd, "{008F7C}Przykład:"COL_EASY" Dziś o godzinie 20:00 odbędzie się zebranie w sali konferencyjnej. Obecność obowiązkowa!\n\n");
			strcat(strSetMotd, "{8B8B8B}• maksymalna długość wiadomości powitalnej to 100 znaków.\n");
			strcat(strSetMotd, "{8B8B8B}• dbaj o to, żeby wiadomość była aktualna.\n");
			strcat(strSetMotd, "{8B8B8B}• "COL_RED"wszyscy pracownicy, którzy są obecnie na służbie otrzymają treść nowej wiadomości powitalnej.\n");
			strcat(strSetMotd, "{8B8B8B}• pozostaw pole puste i zatwierdź aby wyłączyć tą usługę.\n\n");
			strcat(strSetMotd, ""COL_WHITE"Podaj treść wiadomości powitalnej w polu poniżej:");
			Dialog_Show(playerid, FRACTIONSETMOTD, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_WHITE"Ustaw wiadomość powitalną "COL_RED"«•", strSetMotd, "Ustaw", "Anuluj");
		}
		case 3://Zrespawnuj nieużywane pojazdy
		{
			for(new v = GetVehiclePoolSize(); v != -1; v--)
			{
				if(pojazd[v][v_owner_type] == VEHICLE_FRACTION)
				{
					if(pojazd[v][v_owner] == fid)
					{
						if(pojazd[v][v_idletime]+(60*6) > serwer[time_timestamp]) continue;
						RespawnVehicle(v, true);
					}
				}
			}
			LeftNotifyShow(playerid, "info", "Wszystkie nieuzywane dluzej niz ~y~6 minut~w~ pojazdy nalezace do Twojej frakcji, zostaly ~g~zrespawnowane~w~!", LN_BLUE, 20);
			SendFractionMessage(fid, "Wszystkie nieużywane dłużej niż 6 minut pojazdy, zostały zrespawnowane.");
		}
		case 4://Zamknij wszystkie bramy
		{
			new maxclose_ms, temp_ms;
			new counter_opengates;
			new g;
			for(new go; go < MAX_GATES; go++)
			{
				if(GateObjects[go] != 0)
				{
					g = GateObjects[go];
					if(ObjectInfo[g][mgOwnerType] != VEHICLE_FRACTION) continue;
					if(ObjectInfo[g][oModel] == 968 && ObjectInfo[g][mgOwner] == F_BORDERGUARD) continue;//nie zamyka rogatek SG
					if(ObjectInfo[g][mgOwner] == fid)
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
				format(strInfo, 512, "Wszystkie ~y~bramy~w~, ktore naleza do ~b~Twojej frakcji~w~ otrzymaly polecenie ~r~zamkniecia sie~w~. Znaleziono ~r~%d bram(y)~w~, ktore sa otwarte. Zamkniecie ich zajmie nie wiecej niz ~r~%d sekund(y)~w~.", counter_opengates, floatround(maxclose_sec));
				LeftNotifyShow(playerid, "info", strInfo, LN_BLUE, 20);
			}
			else LeftNotifyShow(playerid, "info", "Zadna ~y~brama~w~ w bazie Twojej frakcji ~g~nie jest otwarta~w~.", LN_BLUE, 15);
		}
		case 5://Score frakcji
		{
			mq_format("SELECT `id`, `score` FROM `fractions_data`;");
			mq_send("ShowFractionsScore", "d", playerid);
		}
		case 6://kapitał frakcji (historia)
		{
			new strInfo[1024];
			format(strInfo, 1024, ""COL_LIME"» "COL_WHITE"Aktualny kapitał frakcji: "COL_GREEN"%d$", fractions[fid][fr_money]);
			format(strInfo, 1024, "%s\n"COL_LIME"» "COL_WHITE"Aktualny przelicznik "COL_ORANGE"score => $"COL_WHITE": "COL_ORANGE"1 score = %d$", strInfo, fractions[fid][fr_multiplier]);
			format(strInfo, 1024, "%s\n\n{8B8B8B}• kapitał frakcji jest zasilany ze score frakcji, a te z kolei z aktywności pracowników.", strInfo);
			format(strInfo, 1024, "%s\n{8B8B8B}• score frakcji jest przeliczane i resetowane co 24 godziny (co restart serwera).", strInfo);
			format(strInfo, 1024, "%s\n{8B8B8B}• wypłaty dla pracowników są pobierane z kapitału frakcji.", strInfo);
			MessageGUIEx(playerid, ""COL_RED"•» "COL_WHITE"Kapitał frakcji "COL_RED"«•", strInfo);
		}
	}
	return 1;
}

CMD:ff(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
	if((fid != F_POLICE && fid != F_BORDERGUARD && fid != F_MAFIA) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	if(gracz[playerid][frakcja_permlvl] == 0) return Error(playerid, "Brak uprawnień.");
	if(fractions[fid][fr_disable_ff] == true)
	{
		fractions[fid][fr_disable_ff] = false;
		Info(playerid, ""COL_GREEN"Pracownicy nie mogą się atakować.");
	}
	else 
	{
		fractions[fid][fr_disable_ff] = true;
		Info(playerid, ""COL_RED"Pracownicy mogą się atakować.");
	}
	return 1;
}

task ShowFractionsScore(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new i;
		new t_id;
		new strScore[1024];
		format(strScore, 1024, ""COL_WHITE"Tutaj sprawdzisz ile Twoja frakcja posiada punktów score. Punkty score są przyznawane za każdym razem kiedy pracownik otrzymuje wypłatę.");
		format(strScore, 1024, "%s\n"COL_WHITE"Oznacza to, że czym większa aktywność pracowników, tym więcej score otrzymuje frakcja. Poniżej znajdują sie punkty score wszystkich frakcji.", strScore);
		format(strScore, 1024, "%s\n"COL_WHITE"Punkty score są przeliczane na pieniądze, które trafią na konto frakcji. Dzieje się to co 24 godziny.\n", strScore);
		while(i < rekordy)
		{
			cache_get_value_name_int(i, "id",  t_id);
			new t_score;
			cache_get_value_name_int(i, "score", t_score);
			format(strScore, 1024, "%s\n"COL_RED"» %s"COL_WHITE": %d score%s", strScore, GetFractionName(t_id, 1), t_score, (gracz[playerid][frakcja] == t_id) ? (" "COL_RED"« [Twoja frakcja]") : (" "COL_GREY"[konkurencja]"));
			i++;
		}
		MessageGUIEx(playerid, ""COL_RED"•» "COL_WHITE"Punkty score frakcji "COL_RED"«•",  strScore);
	}
	return 1;
}

Dialog:FRACTIONADDP(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new targetid = strval(inputtext);
	if(gracz[targetid][frakcja] != 0) return Error(playerid, "Ten gracz należy do innej frakcji.");
	new fid = gracz[playerid][frakcja];
	new Float:pPos[3];
	GetPlayerPos(targetid, pPos[0], pPos[1], pPos[2]);
	if(IsPlayerInRangeOfPoint(playerid, 4.0, pPos[0], pPos[1], pPos[2]))
	{
		new strInv[512];
		format(strInv, 512, ""COL_WHITE"Czy akceptujesz zaproszenie do frakcji %s"COL_WHITE"?", GetFractionName(fid, 1));
		Dialog_Show(targetid, FRACTIONINVA, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_WHITE"Zaproszenie do frakcji "COL_RED"«•", strInv, "Akceptuj", "Odrzuc");
		SetPVarInt(targetid, "FRACTION_INV", fid);
		Info(playerid, "Zaproszenie do frakcji zostało wysłane.");
	}
	else Error(playerid, "Ten gracz nie znajduje się w pobliżu Ciebie.");
	return 1;
}

Dialog:FRACTIONINVA(playerid, response, listitem, inputtext[])//TARGETID
{
	if(!response) return 1;
	if(gracz[playerid][frakcja] != 0) return Error(playerid, "Należysz do innej frakcji.");
	gracz[playerid][frakcja] = GetPVarInt(playerid, "FRACTION_INV");
	gracz[playerid][frakcja_permlvl] = 0; 
	gracz[playerid][frakcja_tytul] = 0;
	gracz[playerid][frakcja_wyplata] = fractions[gracz[playerid][frakcja]][fr_paymin];
	format(gracz[playerid][frakcja_tytul], 24, "Pracownik");
	gracz[playerid][frakcja_totalduty] = 0;
	SavePlayerFractionData(playerid);//zapis danych
	new strMessage[144];
	format(strMessage, 144, ""COL_WHITE"Do frakcji został zatrudniony nowy pracownik: "COL_GREEN"%s"COL_WHITE"(%d).", nick(playerid), playerid);
	SendFractionMessage(gracz[playerid][frakcja], strMessage);
	Info(playerid, "Zostałeś zatrudniony! Wszelkie dostępne komendy znajdziesz pod "COL_GREEN"/pomoc"COL_WHITE".");
	SendClientMessageEx(playerid, COLOR_FRACTIONMSG, "[F]"COL_RED" Zapamietaj!!! "COL_WHITE"Wszelkie wiadomości poprzedzone tagiem {%06x}[F]"COL_WHITE", to wiadomości frakcyjne.", COLOR_FRACTIONMSG >>> 8);
	UpdatePlayerColor(playerid);
	return 1;
}


Dialog:FRACTIONSETMOTD(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new fid = gracz[playerid][frakcja];
	if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
	new motd_escape[100];
	format(motd_escape, 100, inputtext);
	mysql_escape_string(motd_escape, motd_escape);
	mq_format("UPDATE `fractions_data` SET `motd`='%s' WHERE `id`='%d';", motd_escape, fid);
	mq_send("QUpdateMotd");
	if(strlen(inputtext) > 1)
	{
		new strNewMessage[144];
		format(strNewMessage, 144, ""COL_WHITE"%s", motd_escape);
		SendFractionMessage(fid, "••••••••••••••••••••••••••••••••••••••••» "COL_RED"Zmiana wiadomości dnia - Frakcja"COL_FMSG"«••••••••••••••••••••••••••••••••••••••••");
		SendFractionMessage(fid, strNewMessage);
		SendFractionMessage(fid, "••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••");
	}
	return 1;
}

task ShowWorkersList(playerid)
{
	new fid = gracz[playerid][frakcja];
	if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
	mq_getdata();
	new i;
	new strHeader[512];
	format(strHeader, 512, ""COL_RED"•» "COL_GREEN"Lista pracowników - %s "COL_WHITE"("COL_RED"%d"COL_WHITE"/"COL_GREEN"%d"COL_WHITE")"COL_RED" «•", GetFractionName(fid, 1), rekordy, MAX_FWORKERS);
	if(rekordy)
	{
		new strWorkerList[3500];
		new t_id, t_nick[24], t_permlvl, t_title[24], t_lastonline;
		format(strWorkerList, 3500, "UID\t[tytuł] Nick\tUprawnienia\tPrzepracowane "COL_GREEN"[Ostatnio online]\n");
		while(i < rekordy)
		{
			cache_get_value_name_int(i, "id", 			t_id);
			cache_get_value_name(i, "Nick", t_nick, 24);
			cache_get_value_name_int(i, "frakcja_permlvl", 			t_permlvl);
			cache_get_value_name(i, "frakcja_tytul", t_title, 24);
			cache_get_value_name_int(i, "LastOnline", 			t_lastonline);
			new total_duty_seconds, total_duty_hours, total_duty_min;
			cache_get_value_name_int(i, "duty_suma", 			total_duty_seconds);
			SecToTime2(total_duty_seconds, total_duty_hours, total_duty_min);
			if(PlayerIsOnline(t_id))
			{
				format(strWorkerList, 3500, "%s{000000}%d\t{FFFFFF}[%s] %s\t%s\t%d godz, %d min "COL_GREEN"[Online]\n", strWorkerList, t_id, t_title, t_nick, PermLvlToStr(t_permlvl), total_duty_hours, total_duty_min);
			}
			else
			{
				new timeago = serwer[time_timestamp]-t_lastonline;
				new ta_d, ta_h, ta_m, ta_s;
				SecToTime(timeago, ta_d, ta_h, ta_m, ta_s);
				format(strWorkerList, 3500, "%s{000000}%d\t{FFFFFF}[%s] %s\t%s\t%d godz, %d min "COL_ORANGE"[%d dni, %d godz, %d min, %d sek temu]\n", strWorkerList, t_id, t_title, t_nick, PermLvlToStr(t_permlvl), total_duty_hours, total_duty_min, ta_d, ta_h, ta_m, ta_s);
			}
			i++;

			if(i >= 25) break;//zabezpieczenie przed wykrzaczeniem sie listy
		} 
		Dialog_Show(playerid, FRACTIONWORKERSLIST, DIALOG_STYLE_TABLIST_HEADERS, strHeader, strWorkerList, "Wybierz", "Anuluj");
	}
	else Error(playerid, "Lista pracowników jest pusta.");
	return 1;
}

Dialog:FRACTIONWORKERSLIST(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new fid = gracz[playerid][frakcja];
	if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
	new target_uid = strval(inputtext);
	SetPVarInt(playerid, "fraction_manageworkeruid", target_uid);

	new t_permlvl;
	mq_format("SELECT `frakcja_permlvl` FROM `Konta` WHERE `id`='%d';", target_uid);
	new Cache:result = mysql_query(g_SQL, mQuery);
	if(cache_get_row_count_ex())  cache_get_value_name_int(0, "frakcja_permlvl", t_permlvl);
	else return Error(playerid, "Wystąpił nieoczekiwany błąd.");
	cache_delete(result);
	//SetPVarInt(playerid, "fraction_manageworkerpermlvl", t_permlvl);

	if(t_permlvl >= gracz[playerid][frakcja_permlvl] && gracz[playerid][frakcja_permlvl] != 2) return Error(playerid, "Brak uprawnień.");//lider może wszystko, a inni nie mogą zarządzać sobą jak mają te same upr lub cel ma wyższą
	new strFractionMenu[1024];
	format(strFractionMenu, 1024, ""COL_LIME"•»\t"COL_GREEN"Zmień stawkę\t"COL_LIME"«•");
	format(strFractionMenu, 1024, "%s\n"COL_LIME"•»\t"COL_EASY"Zmień tytuł\t"COL_LIME"«•", strFractionMenu);
	format(strFractionMenu, 1024, "%s\n"COL_LIME"•»\t"COL_ORANGE"Zmień uprawnienia\t"COL_LIME"«•", strFractionMenu); 
	format(strFractionMenu, 1024, "%s\n"COL_LIME"•»\t"COL_RED"Zwolnij\t"COL_LIME"«•", strFractionMenu); 
	new strHeader[512];
	format(strHeader, 512, ""COL_RED"•» "COL_GREEN"Ustawienia pracownika - "COL_ORANGE"%s (%d)"COL_RED" «•", GetPlayerIGName(target_uid), target_uid);
	Dialog_Show(playerid, FRACTIONEDITWORKER, DIALOG_STYLE_TABLIST, strHeader, strFractionMenu, "Wybierz", "Anuluj");
	return 1;
}

Dialog:FRACTIONEDITWORKER(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new fid = gracz[playerid][frakcja];
	if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
	new target_uid = GetPVarInt(playerid, "fraction_manageworkeruid");
	new strEditWorker[1024];
	new strHeader[512];
	switch(listitem)
	{
		case 0://Zmień stawkę
		{
			//if(gracz[playerid][UID] == target_uid) return Error(playerid, "Nie możesz wykonać tej akcji na sobie.");
			new t_nick[24], t_wyplata;
			mq_format("SELECT `Nick`,`frakcja_wyplata` FROM `Konta` WHERE `id`='%d';", target_uid);
			new Cache:result = mysql_query(g_SQL, mQuery);
			if(cache_get_row_count_ex()) 
			{
				cache_get_value_name(0, "Nick", t_nick, 24);
				cache_get_value_name_int(0, "frakcja_wyplata", 				t_wyplata);
			} else return Error(playerid, "Wystąpił nieoczekiwany błąd.");
			cache_delete(result);


			format(strEditWorker, 1024, ""COL_WHITE"W tym miejscu możesz zmienić "COL_GREEN"stawkę"COL_WHITE" dla konkretnego pracownika.\n");
			format(strEditWorker, 1024, "%s"COL_WHITE"Pracownik otrzyma wypłatę za każde "COL_GREY"%d"COL_WHITE" minut spędzone na służbie.\n", strEditWorker, MAX_DUTYSESSION);
			format(strEditWorker, 1024, "%s"COL_WHITE"Minimalna wartość stawki w frakcji %s"COL_WHITE" to "COL_LIME"%d$"COL_WHITE" a maksymalna "COL_RED"%d$"COL_WHITE".\n", strEditWorker, GetFractionName(fid, 1), fractions[fid][fr_paymin], fractions[fid][fr_paymax]);
			format(strEditWorker, 1024, "%s"COL_WHITE"Aktualnie "COL_ORANGE"%s"COL_WHITE" na służbie otrzymuje co "COL_GREY"%d"COL_WHITE" minut wypłatę wysokości "COL_GREEN"%d$"COL_WHITE".\n\n", strEditWorker, t_nick, MAX_DUTYSESSION, t_wyplata);
			format(strEditWorker, 1024, "%s{8B8B8B}• domyślnie każdy pracownik ma ustaloną minimalną stawkę dostępną w frakcji.\n", strEditWorker);
			format(strEditWorker, 1024, "%s{8B8B8B}• administracja serwera odgórnie ustala przedział stawek z jakich frakcje mogą korzystać.\n\n", strEditWorker);
			format(strEditWorker, 1024, "%s{8B8B8B}• pieniądze są pobierane z kapitału frakcji.\n\n", strEditWorker);
			format(strEditWorker, 1024, "%s"COL_WHITE"Podaj stawkę dla pracownika "COL_ORANGE"%s"COL_WHITE":", strEditWorker, t_nick);
			format(strHeader, 512, ""COL_RED"•» "COL_GREEN"Zmiana stawki - "COL_ORANGE"%s (%d)"COL_RED" «•", t_nick, target_uid);
			Dialog_Show(playerid, FRACTIONSETWPRICE, DIALOG_STYLE_INPUT, strHeader, strEditWorker, "Ustaw", "Anuluj");
		}
		case 1://Zmień tytuł
		{
			strcat(strEditWorker, ""COL_WHITE"W tym miejscu możesz zmienić "COL_GREEN"tytuł pracownika"COL_WHITE".\n");
			strcat(strEditWorker, ""COL_WHITE"Tytuł pracownika to nic innego jak swego rodzaju ranga w hierarchii frakcji.\n");
			strcat(strEditWorker, "{008F7C}Kilka przykładów:"COL_EASY" Posterunkowy, Ogniomistrz, Ordynator\n\n");
			strcat(strEditWorker, "{8B8B8B}• maksymalna długość tytułu to 24 znaki.\n");
			strcat(strEditWorker, "{8B8B8B}• tytuł pracownika jest widoczny na liście pracowników oraz czacie frakcyjnym.\n");
			strcat(strEditWorker, "{8B8B8B}• pamiętaj, że to tylko tytuł, nie ustalisz w tym miejscu uprawnień skryptowych.\n");
			strcat(strEditWorker, "{8B8B8B}• wprowadzenie tytułu, który jest krótrzy niż 3 znaki, jest równoznaczne z anulowaniem zmiany tytułu.\n\n");
			strcat(strEditWorker, ""COL_WHITE"Podaj wprowadź tytuł pracownika poniżej:");
			format(strHeader, 512, ""COL_RED"•» "COL_GREEN"Zmiana tytułu dla pracownika - "COL_ORANGE"%s (%d)"COL_RED" «•", GetPlayerIGName(target_uid), target_uid);
			Dialog_Show(playerid, FRACTIONSETWTITLE, DIALOG_STYLE_INPUT, strHeader, strEditWorker, "Ustaw", "Anuluj");
		}
		case 2://Zmień uprawnienia
		{
			if(gracz[playerid][UID] == target_uid) return Error(playerid, "Nie możesz wykonać tej akcji na sobie.");
			strcat(strEditWorker, ""COL_LIME"•»\t"COL_GREY"Standard\t"COL_LIME"«•\n");
			strcat(strEditWorker, ""COL_LIME"•»\t"COL_ORANGE"V-Lider\t"COL_LIME"«•\n");
			format(strHeader, 512, ""COL_RED"•» "COL_GREEN"Modyfikacja uprawnień - "COL_ORANGE"%s (%d)"COL_RED" «•", GetPlayerIGName(target_uid), target_uid);
			Dialog_Show(playerid, FRACTIONSETWPERM, DIALOG_STYLE_TABLIST, strHeader, strEditWorker, "Ustaw", "Anuluj");
		}
		case 3://Zwolnij
		{
			if(gracz[playerid][UID] == target_uid) return Error(playerid, "Nie możesz wykonać tej akcji na sobie.");
			format(strHeader, 512, ""COL_RED"•» "COL_GREEN"Czy chcesz zwolnić "COL_ORANGE"%s (%d)"COL_GREEN"?"COL_RED" «•", GetPlayerIGName(target_uid), target_uid);
			format(strEditWorker, 1024, ""COL_RED"•» "COL_GREEN"Czy chcesz zwolnić "COL_ORANGE"%s (%d)"COL_GREEN"?"COL_RED" «•", GetPlayerIGName(target_uid), target_uid);
			Dialog_Show(playerid, FRACTIONDELWORKER, DIALOG_STYLE_MSGBOX, strHeader, strEditWorker, "Zwolnij", "Anuluj");
		}
	}
	return 1;
}

Dialog:FRACTIONSETWPRICE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new newpay = strval(inputtext);
	new fid = gracz[playerid][frakcja];
	if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
	if(newpay < fractions[fid][fr_paymin]) return Error(playerid, "Za niska stawka.");
	if(newpay > fractions[fid][fr_paymax]) return Error(playerid, "Za wysoka stawka.");
	new target_uid = GetPVarInt(playerid, "fraction_manageworkeruid");
	mq_format("UPDATE `Konta` SET `frakcja_wyplata`='%d' WHERE `id`='%d';", newpay, target_uid);
	mq_send("QUpdateWorkerPay");
	SendClientMessageEx(playerid, COLOR_FRACTIONMSG, "[F] Ustawiłeś stawkę dla "COL_ORANGE"%s"COL_FMSG" na "COL_GREEN"%d$"COL_FMSG".", GetPlayerIGName(target_uid), newpay);
	//jeśli gracz jest online...
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][UID] == target_uid)
			{
				gracz[p][frakcja_wyplata] = newpay;
				SendClientMessageEx(p, COLOR_FRACTIONMSG, "[F] "COL_RED"Lider frakcji ustawił Ci stawkę na "COL_GREEN"%d$"COL_FMSG".", gracz[p][frakcja_wyplata]);
				break;
			}
		}
	}
	return 1;
}

Dialog:FRACTIONSETWTITLE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(strlen(inputtext) < 3) return Info(playerid, "Zmiana tytułu pracownika została anulowana, ponieważ tytuł był za krótki.");
	if(strlen(inputtext) > 23) return Error(playerid, "Zbyt duża ilość znaków");
	new fid = gracz[playerid][frakcja];
	if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
	new target_uid = GetPVarInt(playerid, "fraction_manageworkeruid");
	const max_title = 24;
	mysql_escape_string(inputtext, inputtext, max_title, g_SQL);
	mq_format("UPDATE `Konta` SET `frakcja_tytul`='%s' WHERE `id`='%d';", inputtext, target_uid);
	mq_send("QUpdateWorkerTitle");
	new strFmessage[144];
	format(strFmessage, 144, "%s "COL_ORANGE"%s"COL_WHITE" zmienił/a tytuł pracownika "COL_EASY"%s"COL_WHITE" na "COL_LIME"%s"COL_WHITE".", gracz[playerid][frakcja_tytul], nick(playerid), GetPlayerIGName(target_uid), inputtext);
	SendFractionMessage(fid, strFmessage);
	//jeśli gracz jest online...
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][UID] == target_uid)
			{
				format(gracz[p][frakcja_tytul], 24, inputtext);//zmiana tytułu dla pracownika jeśli jest online
				break;
			}
		}
	}
	return 1;
}

Dialog:FRACTIONSETWPERM(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new fid = gracz[playerid][frakcja];
	if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
	new target_uid = GetPVarInt(playerid, "fraction_manageworkeruid");
	new new_permlvl = listitem;
	mq_format("UPDATE `Konta` SET `frakcja_permlvl`='%d' WHERE `id`='%d';", new_permlvl, target_uid);
	mq_send("QUpdateWorkerPerm");
	new strFmessage[144];
	format(strFmessage, 144, "%s "COL_ORANGE"%s"COL_WHITE" zmienił/a poziom uprawnień dla "COL_EASY"%s"COL_WHITE" na "COL_LIME"%s"COL_WHITE".", gracz[playerid][frakcja_tytul], nick(playerid), GetPlayerIGName(target_uid), PermLvlToStr(new_permlvl));
	SendFractionMessage(fid, strFmessage);
	//jeśli gracz jest online...
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][UID] == target_uid)
			{
				gracz[p][frakcja_permlvl] = new_permlvl;
				break;
			}
		}
	}
	return 1;
}


Dialog:FRACTIONDELWORKER(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new fid = gracz[playerid][frakcja];
	if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
	new target_uid = GetPVarInt(playerid, "fraction_manageworkeruid");
	new strFmessage[144];
	format(strFmessage, 144, "%s "COL_ORANGE"%s"COL_RED" zwolnił/a "COL_EASY"%s"COL_WHITE".", gracz[playerid][frakcja_tytul], nick(playerid), GetPlayerIGName(target_uid));
	SendFractionMessage(fid, strFmessage);
	//sekcja offline
	mq_format("UPDATE `Konta` SET `frakcja`='0', `frakcja_permlvl`='0', `frakcja_tytul`='Bezrobotny', `frakcja_wyplata`='0' WHERE `id`='%d';", target_uid);
	mq_send("QUpdateFractionData");
	//jeśli gracz jest online...
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(gracz[p][UID] == target_uid)
			{
				gracz[p][frakcja] = 0;
				gracz[p][frakcja_permlvl] = 0;
				gracz[p][frakcja_onduty] = 0; 
				format(gracz[p][frakcja_tytul], 24, "Bezrobotny");
				GameTextForPlayer(p, "~r~ZOSTALES ZWOLNIONY",  5000, 0);//4
				SetPlayerSkin(p, gracz[p][Skin]);//usuwa z duty
				UpdatePlayerColor(p);
				ResetPlayerWeapons(p);
				SetPlayerArmour(playerid, 0);
				break;
			}
		}
	}
	return 1;
}

task Process_PlayerFractionDuty(playerid)
{
	if(IsPlayerAFK(playerid)) return 1;
	if(IsPlayerPaused(playerid)) return 1;
	//if(gracz[playerid][frakcja_wyplata] == 0) return 1;
	if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) return 1;
	if(IsPlayerOnDutyFraction(playerid))
	{
		gracz[playerid][time_duty]++;
		gracz[playerid][time_duty_total]++;
		gracz[playerid][frakcja_totalduty]++;
		if(gracz[playerid][time_duty] > (60*MAX_DUTYSESSION))
		{
			//wypłata
			new fid = gracz[playerid][frakcja];
			if(fractions[fid][fr_money] > gracz[playerid][frakcja_wyplata])
			{
				fractions[fid][fr_money] -= gracz[playerid][frakcja_wyplata];
				GiveMoney(playerid, gracz[playerid][frakcja_wyplata]);
				GiveScore(playerid, gracz[playerid][scoreduty_multiplier]);
				PlayerPlaySound(playerid, 4201, 0, 0, 0);
				new strGameText[64];
				format(strGameText, 64, "~b~OTRZYMUJESZ WYPLATE~n~~g~+%d$~n~~y~+%d score", gracz[playerid][frakcja_wyplata], gracz[playerid][scoreduty_multiplier]);
				GameTextForPlayer(playerid, strGameText,  5000, 0);
				SendClientMessage(playerid, COLOR_FRACTIONMSG, "[F] ••••••••••••••••••••••••••••••••••••••••» "COL_RED"Wypłata "COL_FMSG"«••••••••••••••••••••••••••••••••••••••••");
				SendClientMessageEx(playerid, COLOR_FRACTIONMSG, "[F] Zakończono sesję duty ("COL_LIME"%d minut"COL_FMSG"). Ogólnie na służbie jesteś "COL_BLUE"%d minut"COL_FMSG". "COL_LIME"Czas na wypłatę!", MAX_DUTYSESSION, gracz[playerid][time_duty_total]/60);
				SendClientMessageEx(playerid, COLOR_FRACTIONMSG, "[F] Otrzymujesz wynagrodzenie w postaci "COL_RED"%d$"COL_FMSG" i "COL_RED"+%d score"COL_FMSG".", gracz[playerid][frakcja_wyplata], gracz[playerid][scoreduty_multiplier]);
				SendClientMessageEx(playerid, COLOR_FRACTIONMSG, "[F] Rozpoczęto kolejną sesję duty, aby sprawdzić jej stan, użyj: "COL_WHITE"/duty info"COL_FMSG". Miłej pracy :)");
				if(isvip(playerid))
				{
					SendClientMessageEx(playerid, COLOR_FRACTIONMSG, "[F] "COL_VIP"PREMIA! Jesteś VIP'em, dostajesz bonus do wypłaty!");
					GiveMoney(playerid, 500);
					GiveScore(playerid, 1);
				}
				SendClientMessage(playerid, COLOR_FRACTIONMSG, "[F] •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••");
				//--
			}
			else
			{
				GiveScore(playerid, gracz[playerid][scoreduty_multiplier]);
				SendClientMessage(playerid, COLOR_FRACTIONMSG, "[F] ••••••••••••••••••••••••••••••••••••••••» "COL_RED"Wypłata "COL_FMSG"«••••••••••••••••••••••••••••••••••••••••");
				SendClientMessageEx(playerid, COLOR_FRACTIONMSG, "[F] Zakończono sesję duty ("COL_LIME"%d minut"COL_FMSG"). Ogólnie na służbie jesteś "COL_BLUE"%d minut"COL_FMSG". "COL_LIME"Czas na wypłatę!", MAX_DUTYSESSION, gracz[playerid][time_duty_total]/60);
				SendClientMessageEx(playerid, COLOR_FRACTIONMSG, "[F] "COL_RED"UPS! Twojej frakcji nie stać na wypłatę. Dostajesz "COL_RED"%d score"COL_FMSG".", gracz[playerid][scoreduty_multiplier]);
				SendClientMessageEx(playerid, COLOR_FRACTIONMSG, "[F] Rozpoczęto kolejną sesję duty, aby sprawdzić jej stan, użyj: "COL_WHITE"/duty info"COL_FMSG". Miłej pracy :)");
				if(isvip(playerid))
				{
					SendClientMessageEx(playerid, COLOR_FRACTIONMSG, "[F] "COL_VIP"PREMIA! Jesteś VIP'em, dostajesz bonus do wypłaty!");
					GiveMoney(playerid, 500);
					GiveScore(playerid, 1);
				}
				SendClientMessage(playerid, COLOR_FRACTIONMSG, "[F] •••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••••");
			}
			gracz[playerid][time_duty] = 0;
			mq_format("UPDATE `fractions_data` SET `score`=`score`+'%d', `money`='%d' WHERE `id`='%d';", gracz[playerid][scoreduty_multiplier], fractions[fid][fr_money], fid);
			mq_send("QUpdateFractionMoneyScore");
			if(gracz[playerid][scoreduty_multiplier] < 5) gracz[playerid][scoreduty_multiplier] += 1;
		}
	} 
	else 
	{
		if(IsPlayerOnDutyCompany(playerid)) return 1;//jeśli gracz siedzi na firmie, to nie ruszaj tych zmiennych...
		gracz[playerid][time_duty] = 0;
		gracz[playerid][time_duty_total] = 0;
	}
	return 1;
}
//SKRYPT WEZWAŃ
CMD:wezwania(playerid, params[])//wzywanie służb
{
	new fid = gracz[playerid][frakcja];
	if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
	new strMenu[1024];
	strcat(strMenu, ""COL_LIME"•»\t"COL_GREEN"Lista wezwań\t"COL_LIME"«•");
	strcat(strMenu, "\n"COL_LIME"•»\t"COL_RED"Anuluj namierzanie wezwania "COL_GREY"[usuwa marker i wyłącza GPS]\t"COL_LIME"«•");
	Dialog_Show(playerid, CALLMENU, DIALOG_STYLE_TABLIST, ""COL_RED"•» "COL_WHITE"Wezwania "COL_RED"«•", strMenu, "Wybierz", "Anuluj");
	return 1;
}

Dialog:CALLMENU(playerid, response, listitem, inputtext[])
{
	new fid = gracz[playerid][frakcja];
	if(fid == 0) return Error(playerid, "Nie jesteś w frakcji.");
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			new callList[3072];
			new bool:find = false;
			new Float:dist_caller;
			format(callList, 3072, "ID wezwania\tWzywający\tStatus\tSzczegóły wezwania");
			for(new c; c < MAX_CALLS; c++)
			{
				if(calls[c][call_type] == 0) continue;
				if(calls[c][call_fraction] == fid)
				{
					dist_caller = GetDistanceBetweenPoints(calls[c][call_X], calls[c][call_Y], calls[c][call_Z], gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ])/CONST_KM;
					format(callList, 3072, "%s\n%d\t%s(%d) "COL_GREY"[zgłosił %d min temu; %0.1f km]\t%s\t%s", callList, c, nick(PlayerUIDToPlayerID(calls[c][call_calleruid])), PlayerUIDToPlayerID(calls[c][call_calleruid]), (serwer[time_timestamp]-calls[c][call_timestamp])/60, dist_caller, StatusCall(calls[c][call_status]), calls[c][call_text]);
					find = true;
				}
			}
			if(find) Dialog_Show(playerid, CALLSLIST, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_WHITE"Lista wezwań "COL_RED"«•", callList, "Wybierz", "Zamknij");
			else Error(playerid, "Brak wezwań.");
		}
		case 1:
		{
			DisablePlayerCheckpoint(playerid);
			StopRouteGPS(playerid);
			Info(playerid, "Marker usunięty. GPS wyłączony.");
			
		}
	}
	
	return 1;
}


stock CallsCount(fractionid)
{
	new wynik;
	for(new c; c < MAX_CALLS; c++)
	{
		if(calls[c][call_type] == 0) continue;
		if(calls[c][call_fraction] == fractionid)
		{
			wynik++;
		}
	}
	return wynik;
}

Dialog:CALLSLIST(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(!IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Musisz być na służbie.");
	new callid = strval(inputtext);
	SetPVarInt(playerid, "selected_callid", callid);
	new strHeader[128];
	format(strHeader, 128, ""COL_RED"•» "COL_WHITE"Wezwanie ID: "COL_ORANGE"%d "COL_RED"«•", callid);
	new strMenu[1024];
	strcat(strMenu, ""COL_LIME"•»\t"COL_GREEN"Przyjmij wezwanie\t"COL_LIME"«•");
	strcat(strMenu, "\n"COL_LIME"•»\t"COL_RED"Usuń wezwanie\t"COL_LIME"«•");
	Dialog_Show(playerid, CALLACTION, DIALOG_STYLE_TABLIST, strHeader, strMenu, "Wybierz", "Anuluj");
	return 1;
}

Dialog:CALLACTION(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new callid = GetPVarInt(playerid, "selected_callid");
	switch(listitem)
	{
		case 0://przyjmuje wezwanie
		{
			if(calls[callid][call_status] == 2)
			{
				Info(playerid, "Przyjąłeś wezwanie które posiada status: "COL_BLUE"Przyjęte"COL_WHITE"!");
			}
			else
			{
				new strInfo[144];
				if(calls[callid][call_type] == 1)//od graczy
				{
					Info(playerid, "Wezwanie zostało przyjęte, klient został o tym również poinformowany.");
					format(strInfo, 144, "%s {%06x}%s "COL_WHITE"przyjął Twoje wezwanie. "COL_RED"Widzisz go na mapie.", gracz[playerid][frakcja_tytul], GetPlayerColor(playerid) >>> 8, nick(playerid));
					new callerid = PlayerUIDToPlayerID(calls[callid][call_calleruid]);
					Info(callerid, strInfo);
					format(strInfo, 144, "%s {%06x}%s "COL_FMSG"przyjął wezwanie gracza "COL_BLUE"%s"COL_FMSG".", gracz[playerid][frakcja_tytul], GetPlayerColor(playerid) >>> 8, nick(playerid), nick(callerid));
					SendFractionMessage(gracz[playerid][frakcja], strInfo);
				}
				else if(calls[callid][call_type] == 2)//pożary
				{
					Info(playerid, "Wezwanie zostało przyjęte.");
					format(strInfo, 144, "%s {%06x}%s "COL_FMSG"przyjął wezwanie do "COL_RED"pożaru"COL_FMSG".", gracz[playerid][frakcja_tytul], GetPlayerColor(playerid) >>> 8, nick(playerid));
					SendFractionMessage(gracz[playerid][frakcja], strInfo);
				}
				else if(calls[callid][call_type] == 3)//kłody
				{
					Info(playerid, "Wezwanie zostało przyjęte.");
					format(strInfo, 144, "%s {%06x}%s "COL_FMSG"przyjął wezwanie do "COL_RED"kłody"COL_FMSG".", gracz[playerid][frakcja_tytul], GetPlayerColor(playerid) >>> 8, nick(playerid));
					SendFractionMessage(gracz[playerid][frakcja], strInfo);
				}
			}
			Info(playerid, "Cel został zaznaczony "COL_RED"czerwonym markerem"COL_WHITE" na minimapie. Nawigacja GPS za chwilę wytyczy trasę.");
			DisablePlayerCheckpoint(playerid);
			StopRouteGPS(playerid);
			SetPlayerCheckpoint(playerid, calls[callid][call_X], calls[callid][call_Y], calls[callid][call_Z], 5.0);
			StartRouteGPS(playerid, calls[callid][call_X], calls[callid][call_Y], calls[callid][call_Z], true);
			calls[callid][call_status] = 2;
			calls[callid][call_acceptby_puid] = gracz[playerid][UID];
		}
		case 1://usuwa wezwanie
		{
			Info(playerid, "Wezwanie zostało usunięte.");
			calls[callid][call_status] = 0;
			calls[callid][call_type] = 0;
		}
	}
	return 1;
}

task Process_Caller(playerid)
{
	for(new c; c < MAX_CALLS; c++)
	{
		if(calls[c][call_type] == 0) continue;
		if(calls[c][call_calleruid] == gracz[playerid][UID])
		{
			if(!IsPlayerInRangeOfPoint(playerid, 50.0, calls[c][call_X], calls[c][call_Y], calls[c][call_Z]) || !gracz[playerid][loggedin])
			{
				calls[c][call_status] = 0;
				calls[c][call_type] = 0;
				new strInfo[144];
				format(strInfo, 144, "Wezwanie gracza "COL_BLUE"%s "COL_RED"zostało anulowane!", GetPlayerIGName(calls[c][call_calleruid]));
				SendFractionMessage(calls[c][call_fraction], strInfo);
				format(strInfo, 144, "Wezwanie gracza ~y~%s ~w~zostalo ~r~anulowane~w~!", GetPlayerIGName(calls[c][call_calleruid]));
				SendFractionNotify(calls[c][call_fraction], "Wezwanie", strInfo);
				Info(playerid, "Twoje wezwanie zostało anulowane!");
				return 1;
			}
		}
	}
	return 1;
}

stock StatusCall(statusid)
{
	new wynik[32];
	switch(statusid)
	{
		case 0: wynik = ""COL_GREEN"Nieaktualne";
		case 1: wynik = ""COL_RED"Aktualne";
		case 2: wynik = ""COL_BLUE"Przyjęte";
	}
	return wynik;
}

CMD:wezwij(playerid, params[])//wzywanie służb
{
	new strCall[1000];
	strcat(strCall,""COL_RED"•» "COL_WHITE"Wezwij "COL_POL"Policję\n");
	strcat(strCall,""COL_RED"•» "COL_WHITE"Wezwij "COL_BORG"Straż Graniczną\n");
	strcat(strCall,""COL_RED"•» "COL_WHITE"Wezwij "COL_EMRG"Służby Ratunkowe\n");
	strcat(strCall,""COL_RED"•» "COL_WHITE"Wezwij "COL_ROADA"Pomoc Drogową\n");
	strcat(strCall,""COL_RED"•» "COL_WHITE"Wezwij "COL_TAXI"TAXI\n");
	Dialog_Show(playerid, DIALOGCALL, DIALOG_STYLE_LIST, ""COL_RED"•» "COL_WHITE"Nowe wezwanie "COL_RED"«•", strCall, "Wybierz", "Anuluj");
	return 1;
}

Dialog:DIALOGCALL(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	listitem++;//podbicie zmiennej, żeby zsynchronizować z id frakcji
	for(new c; c < MAX_CALLS; c++)
	{
		if(calls[c][call_type] == 0) continue;
		if(calls[c][call_calleruid] == gracz[playerid][UID])
		{
			if(calls[c][call_fraction] == listitem) return Error(playerid, "Ta frakcja otrzymała już od Ciebie wezwanie.");
		}
	}
	SetPVarInt(playerid, "call_fractionid", listitem);
	Dialog_Show(playerid, DIALOGCALLTEXT, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_WHITE"Szczegóły wezwania "COL_RED"«•", ""COL_WHITE"Podaj szczegóły wezwania "COL_RED"(max 32 znaki)."COL_WHITE":", "Wezwij", "Anuluj");
	return 1;
}

Dialog:DIALOGCALLTEXT(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new fractionid = GetPVarInt(playerid, "call_fractionid");
	for(new c; c < MAX_CALLS; c++)
	{
		if(calls[c][call_type] == 0) continue;
		if(calls[c][call_calleruid] == gracz[playerid][UID])
		{
			if(calls[c][call_fraction] == fractionid) return Error(playerid, "Ta frakcja otrzymała już od Ciebie wezwanie.");
		}
	}
	if(strlen(inputtext) < 2) return Error(playerid, "Zbyt mało znaków.");
	if(strlen(inputtext) > 32) return Error(playerid, "Zbyt dużo znaków..");
	if(NewCall(fractionid, gracz[playerid][UID], 1, inputtext, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]))
	{
		Info(playerid, "Wezwanie zostało wysłane. O przyjęciu zlecenia przez pracownika zostaniesz poinformowany.");
		Info(playerid, ""COL_RED"Uwaga! Jeśli się oddalisz od miejsca wezwania, zostanie ono anulowane!");
	}
	else Error(playerid, "Na serwerze została przekroczona maksymalna ilość wezwań. Spróbuj później.");
	return 1;
}


stock NewCall(c_fid, c_calleruid, c_type, c_text[], Float:c_posX, Float:c_posY, Float:c_posZ)
{
	if(c_type == 0) return 0;
	for(new c; c < MAX_CALLS; c++)
	{
		if(calls[c][call_type] == 0)//typ 0 - brak zlecenia
		{
			calls[c][call_fraction] = c_fid;
			calls[c][call_type] = c_type;
			calls[c][call_calleruid] = c_calleruid;
			calls[c][call_timestamp] = serwer[time_timestamp];
			calls[c][call_status] = 1;
			calls[c][call_X] = c_posX;
			calls[c][call_Y] = c_posY;
			calls[c][call_Z] = c_posZ;
			format(calls[c][call_text], 32, c_text);
			SendFractionMessage(c_fid, "Twoja frakcja otrzymała nowe wezwanie. Lista wezwań znajduje się pod "COL_RED"/wezwania"COL_FMSG".");
			SendFractionNotify(c_fid, "Wezwanie", "Twoja frakcja otrzymala ~g~nowe wezwanie~w~. Lista wezwan znajdue sie pod ~r~/wezwania~w~. Mozesz jej uzyc nawet nie bedac na sluzbie.");
			return 1;
		}
	}
	return 0;
}
//OZNACZANIE BRAMEK SG 3D-textami
stock MarkBorderCrossing3DText()
{
	for(new g; g < MAX_OBJECTS; g++)
	{
		if(ObjectInfo[g][oMgate] == 1)//przycisk
		{
			if(ObjectInfo[g][oModel] == 968)//rogatka
			{
				if(ObjectInfo[g][mgOwnerType] == VEHICLE_FRACTION)
				{
					if(ObjectInfo[g][mgOwner] == F_BORDERGUARD)
					{
						CreateDynamic3DTextLabel("*** ROGATKA - PANEL STEROWANIA ***", 0xC2A2DAFF, ObjectInfo[g][oX] , ObjectInfo[g][oY] , ObjectInfo[g][oZ], 10.0);
					}
				}
			}
		}
	}
	return 1;
}
task Process_BorderCross()
{
	if(FractionDutyWorkersCount(F_BORDERGUARD) == 0)
	{
		new g;
		for(new go; go < MAX_GATES; go++)
		{
			if(GateObjects[go] != 0)
			{
				g = GateObjects[go];
				if(ObjectInfo[g][oMgate] == 1)//przycisk
				{
					if(ObjectInfo[g][oModel] == 968)//rogatka
					{
						if(ObjectInfo[g][mgOwnerType] == VEHICLE_FRACTION)
						{
							if(ObjectInfo[g][mgOwner] == F_BORDERGUARD)
							{
								if(!ObjectInfo[g][gOpen])
								{
									MoveDynamicObject(ObjectInfo[g][oObject], ObjectInfo[g][goX], ObjectInfo[g][goY], ObjectInfo[g][goZ], ObjectInfo[g][gSpeed], ObjectInfo[g][goRX], ObjectInfo[g][goRY], ObjectInfo[g][goRZ]);
									ObjectInfo[g][gOpen] = true;
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
//**********************************************************************************************************SKRYPTY INDYWIDUALNE DLA KAŻDEJ Z FRAKCJI
CMD:z(playerid, params[])//polecenie do zatrzymania się
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /z [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(gracz[targetid][policestop_timestamp] > serwer[time_timestamp]) return Error(playerid, "Niedawno gracz dostal polecenie zatrzymania. Jesli sie nie zatrzymuje uzyj /scigaj.");
	new strTemp[144];
	//playerid
	format(strTemp, 144, "Wysłano nakaz do zatrzymania się graczowi {%06x}%s"COL_WHITE".", GetPlayerColor(targetid) >>> 8, nick(targetid));
	Info(playerid, strTemp);
	LeftNotifyShow(playerid, "Poscig", "Jesli gracz sie nie zatrzymuje, masz ~b~60 sekund~w~ aby wszczac poscig! Uzyj komendy ~r~/scigaj (idgracza)~w~.", LN_RED, 30);
	//targetid
	GameTextForPlayer(targetid, "~r~STOP!~n~~b~Zjedz na pobocze!~n~~y~Zatrzymaj sie!", 5000, 0);
	gracz[targetid][policestop_timestamp] = serwer[time_timestamp]+60;
	LeftNotifyShow(targetid, "Uwaga!", "Jesli sie natychmiast nie zatrzymasz, sluzby rozpoczna skryptowy poscig! Wtedy wowczas nie ma mozliwosci negocjacji kary! Jesli masz slaby woz, daruj sobie! Inaczej mozesz trafic do wiezienia na godzine czasu.", LN_RED, 40);
	return 1;
}


CMD:m(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new message[128], str[256];
	if(sscanf(params,"s[128]", message)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /m [tekst]");
	format(str, 128, "%s (megafon): %s", nick(playerid), message);
	SendNearByMessage(playerid, 0xB83800AA, str, 50.0);
	return 1;
}


CMD:mandat(playerid, params[])//mandat
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid, price, reason[144];
	if(sscanf(params,"dds[144]", targetid, price, reason)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /mandat [idgracza] [kwota] [powód (max 64 znaki)]");
	if(price < 1) return Error(playerid, "Kwota jest za niska.");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	if(price > Money(targetid)) return Error(playerid, "Gracz nie posiada takiej ilości gotówki.");
	new strTemp[512];
	//playerid
	format(strTemp, 512, "Wystawiono mandat dla {%06x}%s"COL_WHITE" w wysokości "COL_GREEN"%d"COL_WHITE".", GetPlayerColor(targetid) >>> 8, nick(targetid), price);
	Info(playerid, strTemp);
	Info(playerid, "Gracz w tej chwili podejmuje decyzje czy przyjmuje mandat czy nie...");
	//targetid
	SetPVarInt(targetid, "mandat_price", price);
	SetPVarInt(targetid, "mandat_funkcjonariuszid", playerid);
	SetPVarInt(targetid, "mandat_frakcjaid", fid);
	format(gracz[targetid][cache_mandat_reason], 64, "%s", reason);
	format(strTemp, 512, ""COL_WHITE"Otrzymujesz mandat od {%06x}%s"COL_WHITE" w wysokości "COL_GREEN"%d$"COL_WHITE".\nPowód: "COL_ORANGE"%s\n"COL_RED"Przyjmujesz mandat?", GetPlayerColor(playerid) >>> 8, nick(playerid), price, gracz[targetid][cache_mandat_reason]);
	Dialog_Show(targetid, MANDATCONFIRM, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_WHITE"Mandat "COL_RED"«•", strTemp, "Tak", "Nie");
	return 1;
}

Dialog:MANDATCONFIRM(playerid, response, listitem, inputtext[])
{
	new strInfo[512];
	new funkcjonariuszid = GetPVarInt(playerid, "mandat_funkcjonariuszid");
	new mandatprice = GetPVarInt(playerid, "mandat_price");
	if(response)//przyjmuje mandat
	{
		if(gracz[funkcjonariuszid][frakcja] == F_POLICE || gracz[funkcjonariuszid][frakcja] == F_BORDERGUARD) 
		{
			format(strInfo, 512, ""COL_GREEN"Gracz %s przyjął mandat.", nick(playerid));
			MessageGUIEx(funkcjonariuszid, ""COL_RED"•» "COL_WHITE"Mandat przyjęty "COL_RED"«•",  strInfo);
			Info(funkcjonariuszid, strInfo);
			format(strInfo, 512, "Przyjety mandat (%d$), powod: %s", mandatprice, gracz[playerid][cache_mandat_reason]);
			KartotekaDodajWpis(funkcjonariuszid, playerid, strInfo);
		}
		Info(playerid, "Przyjąłeś mandat.");
		TakeMoney(playerid, mandatprice);
		//
		new fid = GetPVarInt(playerid, "mandat_frakcjaid");
		fractions[fid][fr_money] +=  mandatprice;//dodawanie kasy dla frakcji
		mq_format("UPDATE `fractions_data` SET `money`='%d' WHERE `id`='%d';", fractions[fid][fr_money], fid);
		mq_send("QUpdateFractionMoney");
	}
	else//nie przyjmuje
	{
		if(gracz[funkcjonariuszid][frakcja] == F_POLICE || gracz[funkcjonariuszid][frakcja] == F_BORDERGUARD) 
		{
			format(strInfo, 512, ""COL_RED"Gracz %s nie przyjął mandatu.", nick(playerid));
			MessageGUIEx(funkcjonariuszid, ""COL_RED"•» "COL_WHITE"Mandat odrzucony "COL_RED"«•",  strInfo);
			Info(funkcjonariuszid, strInfo);
			format(strInfo, 512, "Odrzucony mandat (%d$), powod: %s", mandatprice, gracz[playerid][cache_mandat_reason]);
			KartotekaDodajWpis(funkcjonariuszid, playerid, strInfo);
		}
		Info(playerid, "Odrzuciłeś mandat.");
	}
	DeletePVar(playerid, "mandat_price");
	DeletePVar(playerid, "mandat_funkcjonariuszid");
	DeletePVar(playerid, "mandat_frakcjaid");
	return 1;
}

CMD:alkomat(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /alkomat [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	new Float:promile;
	if(gracz[targetid][when_tipsy] == 0) promile = 0.0;
	else promile = float(gracz[targetid][when_tipsy])/5000.0;
	Info(targetid, "Funkcjonariusz sprawdza Twój stan trzeźwości...");
	Info(playerid, "Trwa sprawdzanie stanu trzeźwości...");
	new strTemp[512];
	format(strTemp, 512, "/do alkomat wskazał wynik %0.2f‰.", promile);
	PC_EmulateCommand(targetid, strTemp);
	format(strTemp, 512, ""COL_WHITE"Stan trzeźwości gracza {%06x}%s(%d)"COL_WHITE" to "COL_RED"%0.2f‰ "COL_WHITE"(promile).", GetPlayerColor(playerid) >>> 8, nick(targetid), targetid, promile);
	MessageGUIEx(playerid, ""COL_RED"•» "COL_WHITE"Wynik alkomatu "COL_RED"«•", strTemp);
	return 1;
}
//listowanie kartoteki
//SELECT `k`.*,`o`.`Nick` AS `onick`,`s`.`Nick` AS `snick` FROM `kartoteka` AS `k` LEFT JOIN `Konta` AS `o` ON `k`.`officeruid`=`o`.`id` LEFT JOIN `Konta` AS `s` ON `k`.`suspectuid`=`s`.`id` ORDER BY `k`.`date` DESC;
CMD:kartoteka(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");

	new targetid, menu[144];
	if(sscanf(params,"ds[144]", targetid, menu)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /kartoteka [idgracza] [lista/nowywpis] ");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(compare(menu, "lista"))
	{
		mq_format("SELECT `k`.*,`o`.`Nick` AS `onick`,`s`.`Nick` AS `snick` FROM `kartoteka` AS `k` LEFT JOIN `Konta` AS `o` ON `k`.`officeruid`=`o`.`id` LEFT JOIN `Konta` AS `s` ON `k`.`suspectuid`=`s`.`id` WHERE `suspectuid`='%d' ORDER BY `k`.`date` DESC LIMIT 0,20;", gracz[targetid][UID]);
		mq_send("ShowKartoteka", "d", playerid);
	}
	else if(compare(menu, "nowywpis"))
	{
		SetPVarInt(playerid, "kartotekaadd_suspectid", targetid);
		new strInfo[512];
		strcat(strInfo, ""COL_WHITE"Wprowadź treść nowego wpisu do kartoteki.\n\n");
		strcat(strInfo, "{8B8B8B}• maksymalna długość wpisu to 64 znaki.\n");
		strcat(strInfo, "{8B8B8B}• jeśli długość wpisu zostanie przekroczona, zostanie on przycięty do 64 znaków.\n\n");
		strcat(strInfo, ""COL_WHITE"Podaj treść poniżej:");
		Dialog_Show(playerid, KARTOTEKANEW, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_WHITE"Nowy wpis do kartoteki "COL_RED"«•", strInfo, "Dodaj", "Anuluj");
	}
	else SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /kartoteka [idgracza] [lista/nowywpis]");
	return 1;
}

Dialog:KARTOTEKANEW(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new targetid = GetPVarInt(playerid, "kartotekaadd_suspectid");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	KartotekaDodajWpis(playerid, targetid, inputtext);
	Info(playerid, "Wpis dodany.");
	return 1;
}

task ShowKartoteka(playerid)
{
	mq_getdata();
	new i;
	new strList[3072];
	if(rekordy)
	{
		format(strList, 3071, "Funkcjonariusz\tJaki czas temu\tTreść");
		new t_date;
		new t_officername[24], t_suspectname[24], t_raport[64];
		while(i < rekordy)
		{
			cache_get_value_name(i, "raport", t_raport, 64);
			cache_get_value_name_int(i, "date", 			t_date);
			cache_get_value_name(i, "onick", t_officername, 24);
			cache_get_value_name(i, "snick", t_suspectname, 24);
			new timeago = serwer[time_timestamp]-t_date;
			new ta_d, ta_h, ta_m, ta_s;
			SecToTime(timeago, ta_d, ta_h, ta_m, ta_s);
			format(strList, 3071, "%s\n%s\t%d dni, %d godz, %d min\t%s", strList, t_officername, ta_d, ta_h, ta_m, t_raport);
			i++;
		}
		new strHeader[128];
		format(strHeader, 128, ""COL_RED"•» "COL_WHITE"Ostatnie "COL_RED"20"COL_WHITE" wpisów z kartoteki gracza "COL_ORANGE"%s "COL_RED"«•", t_suspectname);
		Dialog_Show(playerid, KARTOTEKALIST, DIALOG_STYLE_TABLIST_HEADERS, strHeader, strList, "Zamknij", "");
	}
	else Info(playerid, "Kartoteka tego gracza jest pusta.");
	return 1;
}


stock KartotekaDodajWpis(officerid, suspectid, tresc[])
{
	if(!gracz[officerid][loggedin] || !gracz[suspectid][loggedin]) return 0;
	new tresc_escape[144];
	format(tresc_escape, 144, tresc);
	mysql_escape_string(tresc_escape, tresc_escape);
	mq_format("INSERT INTO `kartoteka` (`officeruid`, `suspectuid`, `date`, `raport`) VALUES ('%d','%d', '%d', '%s');", gracz[officerid][UID], gracz[suspectid][UID], serwer[time_timestamp], tresc_escape);
	mq_send("QAddKartotekaEntry");
	return 1;
}
/*
CMD:kajdanki(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid, menu[144];
	if(sscanf(params,"ds[144]", targetid, menu)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /kajdanki [idgracza] [zaloz/zdejmij] ");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	if(gracz[targetid][frakcja] == F_POLICE || gracz[targetid][frakcja] == F_BORDERGUARD) return Error(playerid, "Nie możesz użyć tej komendy na funkcjonariuszu.");
	new strTemp[128];
	if(compare(menu, "zaloz"))
	{
		if(gracz[targetid][kajdanki]) return Error(playerid, "Ten gracz ma już założone kajdanki."); 
		TogglePlayerControllable(targetid, false);
		gracz[targetid][kajdanki] = true;

		format(strTemp, 128, "/me zakłada kajdanki dla %s.", nick(targetid));
		PC_EmulateCommand(playerid, strTemp);
	}
	else if(compare(menu, "zdejmij"))
	{
		if(!gracz[targetid][kajdanki]) return Error(playerid, "Ten gracz nie ma założonych kajdanek."); 
		TogglePlayerControllable(targetid, true);
		gracz[targetid][kajdanki] = false;

		format(strTemp, 128, "/me zdejmuje kajdanki dla %s.", nick(targetid));
		PC_EmulateCommand(playerid, strTemp);
	}
	else SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /kajdanki [idgracza] [zaloz/zdejmij] ");
	return 1;
}
*/
CMD:parkpol(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new strVehicleList[1024];
	format(strVehicleList, 1024, "UID\tNazwa pojazdu");
	new Float:tX, Float:tY, Float:tZ;
	new vehicle_find_count;
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		if(pojazd[v][v_model] == 0) continue;
		if(pojazd[v][v_owner_type] == VEHICLE_PLAYER)
		{
			GetVehiclePos(v, tX, tY, tZ);
			if(IsPlayerInRangeOfPoint(playerid, 7.0, tX, tY, tZ))
			{
				format(strVehicleList, 1024, "%s\n"COL_BLACK"%d\t"COL_WHITE"%s", strVehicleList, pojazd[v][v_id], GetVehicleName(pojazd[v][v_model]));
				vehicle_find_count++;
			}
		}
	}
	if(vehicle_find_count > 0) Dialog_Show(playerid, SENDPP, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_LIME" Parking Policyjny - Odholowanie pojazdu "COL_RED"«•", strVehicleList, "Odholuj", "Anuluj");
	else Error(playerid, "Nie znaleziono żadnego pojazdu obok Ciebie, który możesz odholować.");
	return 1;
}

Dialog:SENDPP(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new vehicle_uid = strval(inputtext);
	new vehicleid =  VehicleUidToVehicleid(vehicle_uid);
	if(pojazd[vehicleid][v_owner_type] != VEHICLE_PLAYER) return Error(playerid, "Tego pojazdu nie można odholować.");
	new Float:tX, Float:tY, Float:tZ;
	GetVehiclePos(vehicleid, tX, tY, tZ);
	if(!IsPlayerInRangeOfPoint(playerid, 7.0, tX, tY, tZ)) return Error(playerid, "Pojazd jest za daleko.");
	if(vehicleid != -1)
	{
		if(pojazd[vehicleid][v_id] != 0)
		{
			mq_format("UPDATE `pojazdy` SET `status`='3', `X`='%f', `Y`='%f', `Z`='%f', `rlg_lastused`='0' WHERE `id`='%d';", XYZ_PARKINGPOLICYJNY, vehicle_uid);
			mq_send("QUpdateVehicleStatus");
		}
		RemoveVehicle(vehicleid);
		LeftNotifyShow(playerid, "Sukces!", "Pojazd ~r~odholowany~w~.", LN_RED);
	}
	else
	{
		if(pojazd[vehicleid][v_id] != 0)
		{
			mq_format("UPDATE `pojazdy` SET `status`='3', `X`='%f', `Y`='%f', `Z`='%f', `rlg_lastused`='0' WHERE `id`='%d';", XYZ_PARKINGPOLICYJNY, vehicle_uid);
			mq_send("QUpdateVehicleStatus");
		}
		LeftNotifyShow(playerid, "Sukces!", "Pojazd ~r~odholowany~w~.", LN_RED);
	}
	printf("[HOLOWANIE] Gracz %s odholowal pojazd UID: %d na parking policyjny.", nick(playerid), vehicle_uid);
	return 1;
}

CMD:zakuj(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /zakuj [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	if(gracz[targetid][frakcja] == F_POLICE || gracz[targetid][frakcja] == F_BORDERGUARD) return Error(playerid, "Nie możesz użyć tej komendy na funkcjonariuszu.");
	if(gracz[targetid][kajdanki]) return Error(playerid, "Ten gracz ma już założone kajdanki."); 
	if(gracz[targetid][bw] > 0) return Error(playerid, "Ten gracz ma BW.");
	if(gracz[targetid][wypadek] > 0) return Error(playerid, "Ten gracz ma wypadek.");
	if(gracz[targetid][prisoner] > 0) return Error(playerid, "Ten gracz jest w celi.");
	if(IsPlayerUseGym(targetid)) Gym_Disconnect(targetid);
	//TogglePlayerControllable(targetid, false);
	gracz[targetid][kajdanki] = true;
	new strTemp[128];
	format(strTemp, 128, "/me zakłada kajdanki dla %s.", GetICName(targetid));
	PC_EmulateCommand(playerid, strTemp);
	return 1;
}


CMD:rozkuj(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /rozkuj [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	if(gracz[targetid][frakcja] == F_POLICE || gracz[targetid][frakcja] == F_BORDERGUARD) return Error(playerid, "Nie możesz użyć tej komendy na funkcjonariuszu.");
	if(!gracz[targetid][kajdanki]) return Error(playerid, "Ten gracz nie ma założonych kajdanek."); 
	if(gracz[targetid][bw] > 0) return Error(playerid, "Ten gracz ma BW.");
	if(gracz[targetid][wypadek] > 0) return Error(playerid, "Ten gracz ma wypadek.");
	if(gracz[targetid][prisoner] > 0) return Error(playerid, "Ten gracz jest w celi.");
	if(IsPlayerUseGym(targetid)) Gym_Disconnect(targetid);
	//TogglePlayerControllable(targetid, true);
	gracz[targetid][kajdanki] = false;
	new strTemp[128];
	format(strTemp, 128, "/me zdejmuje kajdanki dla %s.", GetICName(targetid));
	PC_EmulateCommand(playerid, strTemp);
	return 1;
}

CMD:drag(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /drag [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	if(!gracz[targetid][kajdanki]) return Error(playerid, "Ten gracz nie ma założonych kajdanek."); 
	if(gracz[targetid][przykuty]) return Error(playerid, "Ten gracz jest już przykuty.");
	if(gracz[targetid][bw] > 0) return Error(playerid, "Ten gracz ma BW.");
	if(gracz[targetid][wypadek] > 0) return Error(playerid, "Ten gracz ma wypadek.");
	if(gracz[targetid][prisoner] > 0) return Error(playerid, "Ten gracz jest w celi.");
	if(IsPlayerUseGym(targetid)) Gym_Disconnect(targetid);
	new strTemp[128];
	format(strTemp, 128, "/me przykuwa do siebie %s.", GetICName(targetid));
	PC_EmulateCommand(playerid, strTemp);
	TogglePlayerControllable(targetid, false);
	gracz[targetid][przykutydo] = playerid;
	gracz[targetid][przykuty] = true;
	return 1;
}

CMD:undrag(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /undrag [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	if(!gracz[targetid][przykuty]) return Error(playerid, "Ten gracz nie jest przykuty.");
	if(gracz[targetid][bw] > 0) return Error(playerid, "Ten gracz ma BW.");
	if(gracz[targetid][wypadek] > 0) return Error(playerid, "Ten gracz ma wypadek.");
	if(gracz[targetid][prisoner] > 0) return Error(playerid, "Ten gracz jest w celi.");
	if(IsPlayerUseGym(targetid)) Gym_Disconnect(targetid);
	new strTemp[128];
	format(strTemp, 128, "/me odkuwa od siebie %s.", GetICName(targetid));
	PC_EmulateCommand(playerid, strTemp);
	TogglePlayerControllable(targetid, true);
	gracz[targetid][przykutydo] = 0;
	gracz[targetid][przykuty] = false;
	return 1;
}

task Process_Przykuty(playerid)
{
	//animacja zakucia
	if(gracz[playerid][kajdanki])
	{
		if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_CUFFED)
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CUFFED);
		}
	}
	else
	{
		if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_CUFFED)
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		}
	}
	if(!gracz[playerid][przykuty]) return 1;
	else
	{
		if(gracz[playerid][kajdanki])
		{
			new Float:bPos[2];
			for(new p = PlayerPoolSize(); p != -1; p--)
			{
				if(!gracz[p][loggedin]) continue;
				if(gracz[playerid][przykutydo] == p)
				{
					if(gracz[p][opu_vehicleid] != 0)//funkcjonariusz jest w aucie
					{
						new vid = gracz[p][opu_vehicleid];
						if(GetMaxSeats(vid) == 4)
						{
							if(!IsSeatTaken(vid, 2) && GetPlayerVehicleSeat(playerid) < 2)//próba wsadzenia gracza na tył
							{
								PutPlayerInVehicle(playerid, vid, 2);
							}
							else if(!IsSeatTaken(vid, 3) && GetPlayerVehicleSeat(playerid) < 2)//próba wsadzenia gracza na tył
							{
								PutPlayerInVehicle(playerid, vid, 3);
							}
							else if(!IsSeatTaken(vid, 1) && GetPlayerVehicleSeat(playerid) < 1)//jak nie ma z tyłu siedzen i nie wsadziło nigdzie gracza, to daje na przód
							{
								PutPlayerInVehicle(playerid, vid, 1);
							}
						}
						else if(GetMaxSeats(vid) == 2)
						{
							if(!IsSeatTaken(vid, 1) && GetPlayerVehicleSeat(playerid) < 1)//jak nie ma z tyłu siedzen i nie wsadziło nigdzie gracza, to daje na przód
							{
								PutPlayerInVehicle(playerid, vid, 1);
							}
						}
					}
					else//nie jest w aucie
					{
						GetXYInBackOfPlayer(p, bPos[0], bPos[1], 1.3);
						SetPlayerPos(playerid, bPos[0], bPos[1], gracz[p][PosZ]);
					}
					return 1;
				}
			}
		}
		else//jeśli nie ma kajdanek a jest przykuty to odkuwa go automatycznie
		{
			gracz[playerid][przykutydo] = 0;
			gracz[playerid][przykuty] = false;
		}
	}

	return 1;
}

CMD:towar(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /towar [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 6.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	new vehicleid = gracz[targetid][opu_vehicleid];
	if(vehicleid == 0) return Error(playerid, "Gracz musi znajdować się w pojeździe.");
	if(pojazd[vehicleid][v_owner_type] != VEHICLE_PLAYER && pojazd[vehicleid][v_owner_type] != VEHICLE_BUSINESS) return Error(playerid, "Gracz nie znajduje się w pojeździe prywatnym.");
	new trucktype = IsVehicleTruck(pojazd[vehicleid][v_model]);
	if(trucktype == 0) return Error(playerid, "Ten pojazd nie jest przystosowany do przewozu ładunków.");
	new cargoveh = vehicleid;
	if(trucktype == 1)  cargoveh = GetVehicleTrailer(vehicleid);
	if(pojazd[cargoveh][v_cargo] == 0)
	{
		MessageGUIEx(playerid, ""COL_RED"•» "COL_WHITE"Brak towaru "COL_RED"«•",  ""COL_RED"Brak towaru.");
		return 1;
	}
	new strSrcZone[24], strDstZone[24];
	new strInfo[1024];
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER)
	{
		if(trucktype == 1)//truck z naczepa
		{
			if(cargoveh == 0) return Error(playerid, "Brak naczepy.");
			Get2DZone(pojazd[cargoveh][v_X], pojazd[cargoveh][v_Y], strSrcZone, 24);
			Get2DZone(pojazd[pojazd[cargoveh][v_cargo_destvid]][v_X], pojazd[pojazd[cargoveh][v_cargo_destvid]][v_Y], strDstZone, 24);
		}
		else
		{
			new zid = gracz[targetid][cargo_confirmtrailer];
			Get2DZone(load_place_van[goods_for_vans[zid][gfv_loadplace_sourceid]][0], load_place_van[goods_for_vans[zid][gfv_loadplace_sourceid]][1], strSrcZone, 24);
			Get2DZone(load_place_van[goods_for_vans[zid][gfv_loadplace_targetid]][0], load_place_van[goods_for_vans[zid][gfv_loadplace_targetid]][1], strDstZone, 24);
		}
		format(strInfo, 1024, ""COL_WHITE"Kierowca: {%06x}%s", GetPlayerColor(targetid) >>> 8, nick(targetid));
		format(strInfo, 1024, "%s\n"COL_WHITE"Nazwa ładunku: {00C5B6}%s", strInfo, goods[pojazd[cargoveh][v_cargo]][gds_name]);
		format(strInfo, 1024, "%s\n"COL_WHITE"Waga ładunku: {00A599}%d [kg]", strInfo, pojazd[cargoveh][v_cargo_amount]);
		format(strInfo, 1024, "%s\n"COL_WHITE"Wartość ładunku: "COL_GREEN"%d$", strInfo, pojazd[cargoveh][v_cargo_price]);
		format(strInfo, 1024, "%s\n"COL_WHITE"Trasa: {00E16A}%s "COL_LIME"» [%0.1f km] » {FF4343}%s", strInfo, strSrcZone, pojazd[cargoveh][v_cargo_distance], strDstZone);
		MessageGUIEx(playerid, ""COL_RED"•» "COL_WHITE"Informacje o przewożonym ładunku "COL_RED"«•",  strInfo);
	}
	else if(pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)
	{
		new cid = gracz[targetid][firma];
		if(cid != 0)
		{
			format(strInfo, 1024, ""COL_WHITE"Kierowca: {%06x}%s", GetPlayerColor(targetid) >>> 8, nick(targetid));
			format(strInfo, 1024, "%s\n"COL_WHITE"Nazwa firmy: "COL_BLUE"%s (ID: %d)", strInfo, company[cid][cny_name], cid);
			format(strInfo, 1024, "%s\n"COL_WHITE"Nazwa ładunku: {00C5B6}%s", strInfo, goods[pojazd[cargoveh][v_cargo]][gds_name]);
			Get2DZone(pojazd[cargoveh][v_cargo_target_X], pojazd[cargoveh][v_cargo_target_Y], strDstZone, 24);
			format(strInfo, 1024, "%s\n"COL_WHITE"Cel: {FF4343}%s", strInfo, strDstZone);
			format(strInfo, 1024, "%s\n"COL_WHITE"Waga ładunku: {00A599}%d [kg]", strInfo, pojazd[cargoveh][v_cargo_amount]);
			format(strInfo, 1024, "%s\n"COL_WHITE"Maksymalna ładownosć pojazdu: {00A599}%d [kg]", strInfo, VehicleCapacity(pojazd[cargoveh][v_model]));
			format(strInfo, 1024, "%s\n"COL_WHITE"Procent przeładowania: {FFA599}%d%%", strInfo, procent(pojazd[cargoveh][v_cargo_amount], VehicleCapacity(pojazd[cargoveh][v_model]))-100);
			if(procent(pojazd[cargoveh][v_cargo_amount], VehicleCapacity(pojazd[cargoveh][v_model])) > 100)
			{
				SetPVarInt(playerid, "cache_penalty_targetid", targetid);
				format(strInfo, 1024, "%s\n\n"COL_RED"Czy chcesz nałożyć karę finansową na firmę "COL_BLUE"%s "COL_RED"za przeładowanie pojazdu?", strInfo, company[cid][cny_name]);
				format(strInfo, 1024, "%s\n"COL_RED"Jeśli tak, wpisz w polu poniżej kwotę ("COL_GREY"20000$ - 50000$"COL_RED"):", strInfo);
				Dialog_Show(playerid, PENALTYOVERSIZE, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_WHITE"Informacje o przewożonym ładunku "COL_RED"«•", strInfo, "Kara", "Anuluj");
			}
			else MessageGUIEx(playerid, ""COL_RED"•» "COL_WHITE"Informacje o przewożonym ładunku "COL_RED"«•",  strInfo);
		}
		else Error(playerid, "Wystąpił nieoczekiwany błąd.");
	}
	PC_EmulateCommand(playerid, "/me sprawdza towar.");
	return 1;
}

Dialog:PENALTYOVERSIZE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new targetid = GetPVarInt(playerid, "cache_penalty_targetid");
	DeletePVar(playerid, "cache_penalty_targetid");
	new cid = gracz[targetid][firma];
	if(cid != 0)
	{
		if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
		if(!IsPlayerInRangeOfPoint(playerid, 6.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
		new vehicleid = gracz[targetid][opu_vehicleid];
		if(vehicleid == 0) return Error(playerid, "Gracz musi znajdować się w pojeździe.");
		if(pojazd[vehicleid][v_owner_type] != VEHICLE_BUSINESS) return Error(playerid, "Gracz nie znajduje się w pojeździe prywatnym.");
		new trucktype = IsVehicleTruck(pojazd[vehicleid][v_model]);
		if(trucktype == 0) return Error(playerid, "Ten pojazd nie jest przystosowany do przewozu ładunków.");
		new cargoveh = vehicleid;
		if(trucktype == 1)  cargoveh = GetVehicleTrailer(vehicleid);
		if(pojazd[cargoveh][v_cargo] == 0)
		{
			MessageGUIEx(playerid, ""COL_RED"•» "COL_WHITE"Brak towaru "COL_RED"«•",  ""COL_RED"Brak towaru.");
			return 1;
		}
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)
		{
			if(procent(pojazd[cargoveh][v_cargo_amount], VehicleCapacity(pojazd[cargoveh][v_model])) > 100)
			{
				new value = strval(inputtext);
				if(value < 20000) return Error(playerid, "Nie nadano kary. Za niska kwota.");
				if(value > 50000) return Error(playerid, "Nie nadano kary. Za wysoka kwota.");
				//work here
				company[cid][cny_money] -= value;
				CompanySaveMoney(cid);
				new strTemp[512];
				format(strTemp, 512, "Przeladowanie pojazdu(%d procent). Firma: %s. %d$", procent(pojazd[cargoveh][v_cargo_amount], VehicleCapacity(pojazd[cargoveh][v_model]))-100, company[cid][cny_name], value);
				KartotekaDodajWpis(playerid, targetid, strTemp);
				LogCompany(cid, gracz[targetid][UID], gracz[targetid][firma_sessionid], CLOGFLAG_WYDATEK, "Kara za przeladowanie. Funkcjonariusz: %s. Koszt: %d$. Saldo: %d$", nick(playerid, true), value, company[cid][cny_money]);
				Info(playerid, "Kara finansowa została nadana.");
				Info(targetid, "Na Twoją firmę została nałożona kara finansowa za przeładowanie pojazdu.");
			}
		}
	}
	return 1;
}

CMD:sc(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid, sc_lvl, reason[144];
	if(sscanf(params,"dds[144]", targetid, sc_lvl, reason)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /sc [idgracza] [poziom poszukiwań(1-6)] [powód (64 znaki)]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(gracz[targetid][scigany_lvl] > 0) return Error(playerid, "Ten gracz jest już scigany.");
	if(sc_lvl < 1) return Error(playerid, "Minimalny poziom poszukiwań to 1.");
	if(sc_lvl > 6) return Error(playerid, "Maxymalny poziom poszukiwań to 6.");
	gracz[targetid][scigany_lvl] = sc_lvl;
	SetPlayerWantedLevel(targetid, sc_lvl);
	mysql_escape_string(reason, reason);
	format(gracz[targetid][scigany_powod], 64, "%s", reason);
	new strInfo[144];
	format(strInfo, 144, "Dodales gracza {%06x}%s"COL_WHITE" do listy poszukiwanych ("COL_RED"%d poziom"COL_WHITE").", GetPlayerColor(targetid) >>> 8, nick(targetid), sc_lvl);
	Info(playerid, strInfo);
	GameTextForPlayer(targetid, "~r~JESTES POSZUKIWANY!!!", 5000, 0);
	mq_format("UPDATE `Konta` SET `wanted_lvl`='%d', `wanted_reason`='%s' WHERE `id`='%d';", gracz[targetid][scigany_lvl], gracz[targetid][scigany_powod], gracz[targetid][UID]);
	mq_send("QUpdateWantedLvl");
	return 1;
}

CMD:scdel(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /scdel [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(gracz[targetid][scigany_lvl] < 1) return Error(playerid, "Ten gracz nie jest scigany.");
	gracz[targetid][scigany_lvl] = 0;
	SetPlayerWantedLevel(targetid, 0);
	new strInfo[144];
	format(strInfo, 144, "Usunales gracza {%06x}%s"COL_WHITE" z listy poszukiwanych.", GetPlayerColor(targetid) >>> 8, nick(targetid));
	Info(playerid, strInfo);
	mq_format("UPDATE `Konta` SET `wanted_lvl`='%d' WHERE `id`='%d';", gracz[targetid][scigany_lvl], gracz[targetid][UID]);
	mq_send("QUpdateWantedLvl");
	return 1;
}

CMD:sclist(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new strList[3072];
	format(strList, 3072, "Nick\tPoziom\tPowód");
	new bool:find = false;
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(!gracz[p][loggedin]) continue;
		if(gracz[p][scigany_lvl] > 0)
		{
			format(strList, 3072, "%s\n{%06x}%s (%d)\t"COL_RED"%d\t"COL_WHITE"%s", strList, GetPlayerColor(p) >>> 8, nick(p), p, gracz[p][scigany_lvl], gracz[p][scigany_powod]);
			find = true;
		}
	}
	if(find) Dialog_Show(playerid, WANTEDLIST, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_WHITE"Lista graczy poszukiwanych "COL_RED"«•",  strList, "Zamknij", "");
	else Info(playerid, "Brak graczy online posiadających status 'Scigany/Poszukiwany'.");
	return 1;
}

CMD:przejazd(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid, price;
	if(sscanf(params,"dd", targetid, price)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /przejazd [idgracza] [kwota]");
	if(price < 1) return Error(playerid, "Kwota jest za niska.");
	if(price > 5000) return Error(playerid, "Kwota jest za wysoka (5000$ maks).");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	if(price > Money(targetid)) return Error(playerid, "Gracz nie posiada takiej ilości gotówki.");
	new strTemp[512];
	//playerid
	format(strTemp, 512, "Wystawiono rachunek za przejazd dla {%06x}%s"COL_WHITE" w wysokości "COL_GREEN"%d$"COL_WHITE".", GetPlayerColor(targetid) >>> 8, nick(targetid), price);
	Info(playerid, strTemp);
	Info(playerid, "Gracz w tej chwili podejmuje decyzje czy przyjmuje rachunek czy nie...");
	//targetid
	SetPVarInt(targetid, "rachunek_price", price);
	SetPVarInt(targetid, "rachunek_funkcjonariuszid", playerid);
	format(strTemp, 512, ""COL_WHITE"Otrzymujesz rachunek za przejazd od {%06x}%s"COL_WHITE" w wysokości "COL_GREEN"%d$"COL_WHITE".\n"COL_RED"Opłacasz rachunek?", GetPlayerColor(playerid) >>> 8, nick(playerid), price);
	Dialog_Show(targetid, PRZEJAZDCONFIRM, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_WHITE"Rachunek za przejazd "COL_RED"«•", strTemp, "Tak", "Nie");
	return 1;
}

CMD:rogatkio(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new g;
	for(new go; go < MAX_GATES; go++)
	{
		if(GateObjects[go] != 0)
		{
			g = GateObjects[go];
			if(ObjectInfo[g][mgOwnerType] != VEHICLE_FRACTION) continue;
			if(ObjectInfo[g][oModel] != 968 && ObjectInfo[g][mgOwner] == F_BORDERGUARD) continue;//tylko rogatki
			if(ObjectInfo[g][mgOwner] == fid)
			{
				if(!ObjectInfo[g][gOpen])
				{
					MoveDynamicObject(ObjectInfo[g][oObject], ObjectInfo[g][goX], ObjectInfo[g][goY], ObjectInfo[g][goZ], ObjectInfo[g][gSpeed], ObjectInfo[g][goRX], ObjectInfo[g][goRY], ObjectInfo[g][goRZ]);
					ObjectInfo[g][gOpen] = true;
				}
			}
		}
	}
	new strInfo[144];
	format(strInfo, 144, "Funkcjonariusz {%06x}%s "COL_FMSG"otworzył wszystkie rogatki.", GetPlayerColor(playerid) >>> 8, nick(playerid));
	SendFractionMessage(fid, strInfo);
	LeftNotifyShow(playerid, "Rogatki", "Wszystkie rogatki zostaly ~g~otworzone~w~.");
	return 1;
}

CMD:rogatkiz(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new g;
	for(new go; go < MAX_GATES; go++)
	{
		if(GateObjects[go] != 0)
		{
			g = GateObjects[go];
			if(ObjectInfo[g][mgOwnerType] != VEHICLE_FRACTION) continue;
			if(ObjectInfo[g][oModel] != 968 && ObjectInfo[g][mgOwner] == F_BORDERGUARD) continue;//tylko rogatki
			if(ObjectInfo[g][mgOwner] == fid)
			{
				if(ObjectInfo[g][gOpen])
				{
					MoveDynamicObject(ObjectInfo[g][oObject], ObjectInfo[g][oX], ObjectInfo[g][oY], ObjectInfo[g][oZ], ObjectInfo[g][gSpeed], ObjectInfo[g][oRX], ObjectInfo[g][oRY], ObjectInfo[g][oRZ]);
					ObjectInfo[g][gOpen] = false;
				}
			}
		}
	}
	new strInfo[144];
	format(strInfo, 144, "Funkcjonariusz {%06x}%s "COL_FMSG"zamknął wszystkie rogatki.", GetPlayerColor(playerid) >>> 8, nick(playerid));
	SendFractionMessage(fid, strInfo);
	LeftNotifyShow(playerid, "Rogatki", "Wszystkie rogatki zostaly ~r~zamkniete~w~.");
	return 1;
}

Dialog:PRZEJAZDCONFIRM(playerid, response, listitem, inputtext[])
{
	new strInfo[512];
	new funkcjonariuszid = GetPVarInt(playerid, "rachunek_funkcjonariuszid");
	new rachunekprice = GetPVarInt(playerid, "rachunek_price");
	if(response)//przyjmuje
	{
		if(gracz[funkcjonariuszid][frakcja] == F_BORDERGUARD) 
		{
			format(strInfo, 512, ""COL_GREEN"Gracz %s opłacił rachunek za przejazd.\n"COL_WHITE"Pieniądze trafiły na konto frakcji.", nick(playerid));
			MessageGUIEx(funkcjonariuszid, ""COL_RED"•» "COL_WHITE"Rachunek opłacony "COL_RED"«•",  strInfo);
			Info(funkcjonariuszid, strInfo);
		}
		Info(playerid, "Rachunek za przejazd został opłacony.");
		TakeMoney(playerid, rachunekprice);
		//
		fractions[F_BORDERGUARD][fr_money] +=  rachunekprice;//dodawanie kasy dla frakcji
		mq_format("UPDATE `fractions_data` SET `money`='%d' WHERE `id`='%d';", fractions[F_BORDERGUARD][fr_money], F_BORDERGUARD);
		mq_send("QUpdateFractionMoney");
	}
	else//nie przyjmuje
	{
		if(gracz[funkcjonariuszid][frakcja] == F_BORDERGUARD) 
		{
			format(strInfo, 512, ""COL_RED"Gracz %s nie opłacił rachunku za przejazd.", nick(playerid));
			MessageGUIEx(funkcjonariuszid, ""COL_RED"•» "COL_WHITE"Rachunek odrzucony "COL_RED"«•",  strInfo);
			Info(funkcjonariuszid, strInfo);
		}
		Info(playerid, "Nie opłaciłeś rachunku za przejazd.");
	}
	return 1;
}

CMD:areszt(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid, time, cela, reason[144];
	if(sscanf(params,"ddds[144]", targetid, time, cela, reason)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /areszt [idgracza] [czas w min] [nr celi] [powód (max 64 znaki)]");
	if(time < 1) return Error(playerid, "Czas musi być dłuższy niż 1 min.");
	if(time > 60) return Error(playerid, "Czas musi być krótrzy niż 60 min.");

	if(cela < 0) return Error(playerid, "Taka cela o takim numerze nie istnieje.");
	if(cela >= sizeof(prisons)) return Error(playerid, "Taka cela o takim numerze nie istnieje.");

	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(gracz[targetid][prisoner]) return Error(playerid, "Ten gracz jest już w więzieniu.");

	if(!IsPlayerInRangeOfPoint(playerid, 5.0, XYZ_PRISONADD)) return Error(playerid, "Aby aresztować gracza musisz znajdować się przy pickupie w więzieniu.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");

	if(IsPlayerUseGym(targetid)) Gym_Disconnect(targetid);

	new strTemp[512];
	format(strTemp, 512, "Aresztowany (%d minut), powod: %s", time, reason);
	KartotekaDodajWpis(playerid, targetid, strTemp);
	//playerid
	format(strTemp, 512, "Aresztowałeś gracza {%06x}%s"COL_WHITE" na "COL_GREEN"%d"COL_WHITE" minut w celi nr %d.", GetPlayerColor(targetid) >>> 8, nick(targetid), time, cela);
	Info(playerid, strTemp);
	//targetid
	//zdejmowanie kajdanek
	TogglePlayerControllable(targetid, true);
	gracz[targetid][kajdanki] = false;

	format(strTemp, 512, ""COL_WHITE"Zostales aresztowany.\n"COL_RED"Powód: "COL_GREY"%s", reason);
	MessageGUIEx(targetid, ""COL_RED"•» "COL_WHITE"Areszt "COL_RED"«•",  strTemp);
	SetPlayerPos(targetid, prisons[cela][0], prisons[cela][1], prisons[cela][2]);
	gracz[targetid][prisoner] = 1;
	gracz[targetid][prisoner_time] = 60*time;
	gracz[targetid][prisoner_prisonid] = cela;
	mq_format("UPDATE `Konta` SET `prisoner`='%d', `prisoner_time`='%d', `prisoner_prisonid`='%d' WHERE `id`='%d';", gracz[targetid][prisoner], gracz[targetid][prisoner_time], gracz[targetid][prisoner_prisonid], gracz[targetid][UID]);
	mq_send("QUpdatePrison");
	//sciaganie skina
	SetPlayerSkin(targetid, gracz[targetid][Skin]);
	ResetPlayerWeapons(targetid);
	SetPlayerArmour(targetid, 0);
	UpdatePlayerColor(targetid);
	gracz[targetid][frakcja_onduty] = 0;
	return 1;
}

CMD:unareszt(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /unareszt [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!gracz[targetid][prisoner]) return Error(playerid, "Ten gracz nie jest w więzieniu.");
	gracz[targetid][scigany_lvl] = 0;
	SetPlayerWantedLevel(targetid, 0);
	mq_format("UPDATE `Konta` SET `wanted_lvl`='%d' WHERE `id`='%d';", gracz[targetid][scigany_lvl], gracz[targetid][UID]);
	mq_send("QUpdateWantedLvl");

	gracz[targetid][prisoner] = 0;
	gracz[targetid][prisoner_time] = 0;
	SetPlayerPos(targetid, XYZ_PRISONOUT);
	GameTextForPlayer(targetid, "~g~ZOSTALES WYPUSZCZONY!",  5000, 0);//4
	LeftNotifyShow(targetid, "Wolny!", "Zostales wypuszczony z aresztu. Staraj sie wiecej nie lamac prawa.",  LN_GREEN);
	mq_format("UPDATE `Konta` SET `prisoner`='%d', `prisoner_time`='%d', `prisoner_prisonid`='%d' WHERE `id`='%d';", gracz[targetid][prisoner], gracz[targetid][prisoner_time], gracz[targetid][prisoner_prisonid], gracz[targetid][UID]);
	mq_send("QUpdatePrison");
	new strTemp[512];
	format(strTemp, 512, "Wypuściłeś z aresztu gracza {%06x}%s"COL_WHITE".", GetPlayerColor(targetid) >>> 8, nick(targetid));
	Info(playerid, strTemp);

	return 1;
}


task Process_Prison(playerid)
{
	//odliczanie czasu
	if(gracz[playerid][prisoner] == 1)//gdy jest w więzieniu
	{
		new cela = gracz[playerid][prisoner_prisonid];
		if(!IsPlayerInRangeOfPoint(playerid, 5.0, prisons[cela][0], prisons[cela][1], prisons[cela][2]))//i nie jest w celi
		{
			SetPlayerPos(playerid, prisons[cela][0], prisons[cela][1], prisons[cela][2]);
		}
		else//jeśli jest, to odliczanie czasu
		{
			if(gracz[playerid][prisoner_time] > 0)
			{
				gracz[playerid][prisoner_time]--;
				new strTemp[128];
				format(strTemp, 128,"~n~~n~~n~~n~~n~~n~~n~~n~~n~~b~areszt:~n~~g~pozostalo %d sekund.", gracz[playerid][prisoner_time]);
				GameTextForPlayer(playerid, strTemp, 1000, 3);
			}
			else//koniec czasu? zostaje wypuszczony
			{
				gracz[playerid][scigany_lvl] = 0;
				SetPlayerWantedLevel(playerid, 0);
				mq_format("UPDATE `Konta` SET `wanted_lvl`='%d' WHERE `id`='%d';", gracz[playerid][scigany_lvl], gracz[playerid][UID]);
				mq_send("QUpdateWantedLvl");
				
				gracz[playerid][prisoner] = 0;
				SetPlayerPos(playerid, XYZ_PRISONOUT);
				GameTextForPlayer(playerid, "~g~ZOSTALES WYPUSZCZONY!",  5000, 0);//4
				LeftNotifyShow(playerid, "Wolny!", "Zostales wypuszczony z aresztu. Staraj sie wiecej nie lamac prawa.",  LN_GREEN);
			}
			mq_format("UPDATE `Konta` SET `prisoner`='%d', `prisoner_time`='%d' WHERE `id`='%d';", gracz[playerid][prisoner], gracz[playerid][prisoner_time], gracz[playerid][UID]);
			mq_send("QUpdatePrison");
		}
	}
	else//nie jest w więzieniu
	{
		new cela = gracz[playerid][prisoner_prisonid];
		if(IsPlayerInRangeOfPoint(playerid, 1.0, prisons[cela][0], prisons[cela][1], prisons[cela][2]))//i jest w celi
		{
			SetPlayerPos(playerid, XYZ_PRISONOUT);
		}
	}
	return 1;
}

CMD:suszarkaon(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new speedlimit;
	if(sscanf(params,"d", speedlimit)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /suszarkaon [limit prędkosci (km/h)]");
	if(speedlimit < 10) return Error(playerid, "Limit musi być większy niż 10 km/h.");
	if(gracz[playerid][used_fractiontool] > 0) return Error(playerid, "Prędkościomierz lub inne narzędzie frakcyjne jest już uruchomione.");
	gracz[playerid][used_fractiontool] = 1;
	gracz[playerid][f_maxspeedometer] = speedlimit;
	Process_FractionTool(playerid);
	Info(playerid, "Prędkościomierz został "COL_GREEN"uruchomiony"COL_WHITE".");
	return 1;
}

CMD:suszarkaoff(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	if(gracz[playerid][used_fractiontool] != 1) return Error(playerid, "Prędkościomierz nie jest uruchomiony.");
	gracz[playerid][used_fractiontool] = 0;
	Process_FractionTool(playerid);
	Info(playerid, "Prędkościomierz został "COL_RED"wyłączony"COL_WHITE".");
	return 1;
}

CMD:suszarkaset(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new speedlimit;
	if(sscanf(params,"d", speedlimit)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /suszarkaset [limit prędkosci (km/h)]");
	if(speedlimit < 10) return Error(playerid, "Limit musi być większy niż 10 km/h.");
	if(gracz[playerid][used_fractiontool] != 1) return Error(playerid, "Prędkościomierz nie jest uruchomiony.");
	gracz[playerid][f_maxspeedometer] = speedlimit;
	Process_FractionTool(playerid);
	Info(playerid, "Prędkościomierz został "COL_BLUE"przestawiony"COL_WHITE".");
	return 1;
}

CMD:suszarkapokaz(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /suszarkapokaz [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	if(gracz[targetid][exceeded_speed] == 0) return Error(playerid, "Na suszarce nie zostało ostatnio zarejestrowane wykroczenie gracza bądź wynik został już pokazany.");
	if(gracz[targetid][exceeded_speed_time]+(60*5) < serwer[time_timestamp]) return Error(playerid, "Wykroczenie zostało przedawnione (minęło ponad 5 minut od pomiaru).");
	new strTemp[512];
	format(strTemp, 512, "/me pokazuje wyświetlacz prędkościomierza dla %s.", nick(targetid));
	PC_EmulateCommand(playerid, strTemp);
	format(strTemp, 512, "/do z informacji na wyświetlaczu wynika, że %s przekroczył/a prędkość o %d km/h %d sekund temu.", nick(targetid), gracz[targetid][exceeded_speed], serwer[time_timestamp]-gracz[targetid][exceeded_speed_time]);
	PC_EmulateCommand(playerid, strTemp);
	format(strTemp, 512, ""COL_WHITE"Przekroczyłeś prędkość o "COL_RED"%d km/h"COL_WHITE".\nPrędkość została odczytana "COL_RED"%d sekund "COL_WHITE"temu.", gracz[targetid][exceeded_speed], serwer[time_timestamp]-gracz[targetid][exceeded_speed_time]);
	MessageGUIEx(targetid, ""COL_RED"•» "COL_WHITE"Wynik z pomiaru prędkości "COL_RED"«•",  strTemp);
	format(strTemp, 512, "Pokazałeś dla gracza {%06x}%s"COL_WHITE" o ile przekroczył ostatnio prędkość.", GetPlayerColor(targetid) >>> 8, nick(targetid));
	Info(playerid, strTemp);
	gracz[targetid][exceeded_speed] = 0;
	gracz[targetid][exceeded_speed_time] = 0;
	return 1;
}

task Process_FractionTool(playerid)
{
	if(gracz[playerid][used_fractiontool] > 0)//gdy nie jest na duty wyłączanie narzędzi frakcyjnych
	{
		if(!IsPlayerOnDutyFraction(playerid))
		{
			gracz[playerid][used_fractiontool] = 0;
		}
	}
	switch(gracz[playerid][used_fractiontool])
	{
		case 1://predkosciomierz
		{
			new pfind = false;
			new strResult[255];
			new Float:distance;
			for(new p = PlayerPoolSize(); p != -1; p--)
			{
				if(p == playerid) continue;
				if(gracz[p][opu_vehicleid] == 0) continue;
				if(GetPlayerState(p) != PLAYER_STATE_DRIVER) continue;
				if(IsPlayerInRangeOfPoint(playerid, 120.0, gracz[p][PosX], gracz[p][PosY], gracz[p][PosZ]))
				{
					distance = GetDistanceBetweenPoints(gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], gracz[p][PosX], gracz[p][PosY], gracz[p][PosZ]);
					pfind = true;
					if(gracz[p][opu_speed] > gracz[playerid][f_maxspeedometer])//przekroczył
					{
						if(gracz[p][exceeded_speed_time]+2 < serwer[time_timestamp])
						{
							if(gracz[p][exceeded_speed] < gracz[p][opu_speed]-gracz[playerid][f_maxspeedometer])
							{

								gracz[p][exceeded_speed] = gracz[p][opu_speed]-gracz[playerid][f_maxspeedometer];
								format(strResult, 255, "Gracz {%06x}%s "COL_WHITE"przekroczył prędkość o "COL_RED"%d km/h"COL_WHITE".", GetPlayerColor(playerid) >>> 8, nick(p), gracz[p][opu_speed]-gracz[playerid][f_maxspeedometer]);
								Info(playerid, strResult);
								format(strResult, 255, "Gracz: ~y~%s(%d)~n~~w~Pojazd: ~y~%s~n~~w~Predkosc: ~r~%d ~b~[km/h]~n~~w~Odleglosc: ~y~%0.1f ~b~[m]~n~~r~Limit: ~y~%d ~b~[km/h]~n~~r~PREDKOSC PRZEKROCZONA!", nick(p), p, GetVehicleName(pojazd[gracz[p][opu_vehicleid]][v_model]), gracz[p][opu_speed], distance, gracz[playerid][f_maxspeedometer]);
							}
							else
							{
								format(strResult, 255, "Gracz: ~y~%s(%d)~n~~w~Pojazd: ~y~%s~n~~w~Predkosc: ~y~%d ~b~[km/h]~n~~w~Odleglosc: ~y~%0.1f ~b~[m]~n~~w~Limit: ~y~%d ~b~[km/h]", nick(p), p, GetVehicleName(pojazd[gracz[p][opu_vehicleid]][v_model]), gracz[p][opu_speed], distance, gracz[playerid][f_maxspeedometer]);
							}
							gracz[p][exceeded_speed_time] = serwer[time_timestamp];
						}
						break;
					}
					else
					{
						format(strResult, 255, "Gracz: ~y~%s(%d)~n~~w~Pojazd: ~y~%s~n~~w~Predkosc: ~y~%d ~b~[km/h]~n~~w~Odleglosc: ~y~%0.1f ~b~[m]~n~~w~Limit: ~y~%d ~b~[km/h]", nick(p), p, GetVehicleName(pojazd[gracz[p][opu_vehicleid]][v_model]), gracz[p][opu_speed], distance, gracz[playerid][f_maxspeedometer]);
					}
				}
			}
			if(pfind) 
			{
				UpdateFractionToolTD(playerid, "Predkosciomierz", strResult);
			}
			else
			{
				format(strResult, 255, "Gracz: ~y~---~n~~w~Pojazd: ~y~---~n~~w~Predkosc: ~y~--- ~b~[km/h]~n~~w~Odleglosc: ~y~--- ~b~[m]~n~~w~Limit: ~y~%d ~b~[km/h]~n~~r~Brak danych!", gracz[playerid][f_maxspeedometer]);
				UpdateFractionToolTD(playerid, "Predkosciomierz", strResult);
			}
		}
		default: HideFractionToolTD(playerid);
	}
	return 1;
}

CMD:obd(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_ROADASSIST) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /obd [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	new target_vehicleid = GetPlayerVehicleID(targetid);
	if(target_vehicleid == 0) return Error(playerid, "Gracz musi być w pojeździe.");
	//DO REFAKTORYZACJI
	if(pojazd[target_vehicleid][v_owner_type] == VEHICLE_PLAYER)//privy
	{
		if(!IsPlayerCanDrive(targetid, target_vehicleid)) return Error(playerid, "Gracz nie ma uprawnień do tego pojazdu.");
		new engine, lights, alarm, doors, bonnet, boot, objective;
		GetVehicleParamsEx(target_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
		SetPVarInt(playerid, "cache_obd_targetid", targetid);
		new strCommand[128];
		format(strCommand, 128, "/me podłącza komputer diagnostyczny do pojazdu %s.", GetVehicleName(pojazd[target_vehicleid][v_model]));
		PC_EmulateCommand(playerid, strCommand);
		new strTitle[128];
		new str_obd_data[2048];
		format(strTitle, 128, ""COL_RED"•» "COL_WHITE"[OBD] Stan techniczny pojazdu: "COL_ORANGE"%s "COL_RED"«•", GetVehicleName(pojazd[target_vehicleid][v_model]));
		format(str_obd_data, 2048, "Komponent\tStan\tKoszt naprawy");
		new Float:damage_proc;
		new Float:fix_price;
		new bool:shadowline;
		new slc[9];//shadowline color
		for(new x; x < MAX_VEHICLEDAMAGES; x++)
		{
			damage_proc = procent(float(VehicleDamages[x][vd_exp_km]-pojazd[target_vehicleid][v_damages_lifetime_km][x]), float(VehicleDamages[x][vd_exp_km]));
			if(damage_proc < 0.0) damage_proc = 0.0;
			slc = (shadowline) ? ("{8D8D8D}") : ("{FFFFFF}");
			fix_price = (VehicleDamages[x][vd_price_proc]/100.0)*CalcVehiclePriceEx(pojazd[target_vehicleid][v_model]);
			if(IsVehicleBike(pojazd[target_vehicleid][v_model]) && (x == 1 || x == 2)) format(str_obd_data, 2048, "%s\n"COL_RED"» %s%s\t"COL_GREEN"-brak-\t"COL_LIME"---", str_obd_data, slc, VehicleDamages[x][vd_title]);
			else format(str_obd_data, 2048, "%s\n"COL_RED"» %s%s\t%s\t"COL_LIME"%d$", str_obd_data, slc, VehicleDamages[x][vd_title], (IsVehicleWornOut(target_vehicleid, x)) ? (""COL_RED"AWARIA") : (text_bar(floatround(damage_proc))), floatround(fix_price));
			if(shadowline) shadowline = false;
			else shadowline = true;
		}
		Dialog_Show(playerid, OBDDATA, DIALOG_STYLE_TABLIST_HEADERS, strTitle, str_obd_data, "Napraw", "Anuluj");
	}
	else if(pojazd[target_vehicleid][v_owner_type] == VEHICLE_BUSINESS)//firmy
	{
		if(!IsPlayerOnDutyCompany(targetid)) return Error(playerid, "Gracz nie jest na służbie w firmie.");
		if(pojazd[target_vehicleid][v_owner] != gracz[targetid][firma]) return Error(playerid, "Gracz nie jest w firmie do której należy pojazd.");
		new engine, lights, alarm, doors, bonnet, boot, objective;
		GetVehicleParamsEx(target_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
		SetPVarInt(playerid, "cache_obd_targetid", targetid);
		new strCommand[128];
		format(strCommand, 128, "/me podłącza komputer diagnostyczny do pojazdu %s.", GetVehicleName(pojazd[target_vehicleid][v_model]));
		PC_EmulateCommand(playerid, strCommand);
		new strTitle[128];
		new str_obd_data[2048];
		Info(playerid, "Diagnozujesz pojazd firmowy.");
		format(strTitle, 128, ""COL_RED"•» "COL_WHITE"[OBD] Stan techniczny pojazdu: "COL_ORANGE"%s "COL_RED"«•", GetVehicleName(pojazd[target_vehicleid][v_model]));
		format(str_obd_data, 2048, "Komponent\tStan\tKoszt naprawy");
		new Float:damage_proc;
		new Float:fix_price;
		new bool:shadowline;
		new slc[9];//shadowline color
		for(new x; x < MAX_VEHICLEDAMAGES; x++)
		{
			damage_proc = procent(float(VehicleDamages[x][vd_exp_km]-pojazd[target_vehicleid][v_damages_lifetime_km][x]), float(VehicleDamages[x][vd_exp_km]));
			if(damage_proc < 0.0) damage_proc = 0.0;
			slc = (shadowline) ? ("{8D8D8D}") : ("{FFFFFF}");
			fix_price = (VehicleDamages[x][vd_price_proc]/100.0)*CalcVehiclePriceEx(pojazd[target_vehicleid][v_model]);
			if(IsVehicleBike(pojazd[target_vehicleid][v_model]) && (x == 1 || x == 2)) format(str_obd_data, 2048, "%s\n"COL_RED"» %s%s\t"COL_GREEN"-brak-\t"COL_LIME"---", str_obd_data, slc, VehicleDamages[x][vd_title]);
			else format(str_obd_data, 2048, "%s\n"COL_RED"» %s%s\t%s\t"COL_LIME"%d$", str_obd_data, slc, VehicleDamages[x][vd_title], (IsVehicleWornOut(target_vehicleid, x)) ? (""COL_RED"AWARIA") : (text_bar(floatround(damage_proc))), floatround(fix_price));
			if(shadowline) shadowline = false;
			else shadowline = true;
		}
		Dialog_Show(playerid, OBDDATA, DIALOG_STYLE_TABLIST_HEADERS, strTitle, str_obd_data, "Napraw", "Anuluj");
	}
	else Error(playerid, "Tego pojazdu nie można diagnozować.");

	return 1;
}


Dialog:OBDDATA(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new targetid = GetPVarInt(playerid, "cache_obd_targetid");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	new target_vehicleid = GetPlayerVehicleID(targetid);
	if(target_vehicleid == 0) return Error(playerid, "Gracz musi być w pojeździe.");
	//DO REFAKTORYZACJI
	if(pojazd[target_vehicleid][v_owner_type] == VEHICLE_PLAYER)//privy
	{
		if(!IsPlayerCanDrive(targetid, target_vehicleid)) return Error(playerid, "Gracz nie ma uprawnień do tego pojazdu.");
		new engine, lights, alarm, doors, bonnet, boot, objective;
		GetVehicleParamsEx(target_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
		if(IsVehicleBike(pojazd[target_vehicleid][v_model]) && (listitem == 1 || listitem == 2)) return Error(playerid, "Pojazd nie jest wyposażony w ten komponent.");
		Info(playerid, "Zaoferowałeś naprawe pojazdu. Gracz teraz podejmuje decyzje...");
		new strTitle[128];
		new strContent[2048];
		new Float:fix_price = (VehicleDamages[listitem][vd_price_proc]/100.0)*CalcVehiclePriceEx(pojazd[target_vehicleid][v_model]);
		new Float:damage_proc = procent(float(VehicleDamages[listitem][vd_exp_km]-pojazd[target_vehicleid][v_damages_lifetime_km][listitem]), float(VehicleDamages[listitem][vd_exp_km]));
		if(damage_proc < 0.0) damage_proc = 0.0;
		format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Naprawa: "COL_ORANGE"%s "COL_RED"«•", VehicleDamages[listitem][vd_title]);
		format(strContent, 2048, ""COL_WHITE"Mechanik "COL_ROADA"%s"COL_WHITE" wystawił Ci rachunek za naprawę "COL_LIME"%s"COL_WHITE" w pojeździe "COL_BLUE"%s"COL_WHITE".", nick(playerid), VehicleDamages[listitem][vd_title], GetVehicleName(pojazd[target_vehicleid][v_model]));
		format(strContent, 2048, "%s\n"COL_RED"Jeśli odrzucisz rachunek, naprawa nie zostanie zrealizowana.", strContent);
		format(strContent, 2048, "%s\n\n"COL_RED"» "COL_WHITE"Podsumowanie:", strContent);
		format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Pojazd: "COL_BLUE"%s "COL_GREY"(UID: %d)", strContent, GetVehicleName(pojazd[target_vehicleid][v_model]), pojazd[target_vehicleid][v_id]);
		format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Komponent: "COL_LIME"%s", strContent, VehicleDamages[listitem][vd_title]);
		format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Koszt: "COL_GREEN"%d$", strContent, floatround(fix_price));
		format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Aktualny stan komponentu: %s", strContent, (damage_proc == 0.0) ? (""COL_RED"AWARIA") : (text_bar(floatround(damage_proc))));
		format(strContent, 2048, "%s\n\n"COL_GREEN"Czy zgadzasz się na naprawę i przyjmujesz rachunek?", strContent);
		Dialog_Show(targetid, OBDFIXCONFIRM, DIALOG_STYLE_MSGBOX, strTitle, strContent, "Akceptuj", "Odrzuc");
		//ładowanie cache
		SetPVarInt(targetid, "cache_odbfix_component", listitem);
		SetPVarInt(targetid, "cache_odbfix_vehicleid", target_vehicleid);
		SetPVarInt(targetid, "cache_odbfix_price", floatround(fix_price));
		SetPVarInt(targetid, "cache_odbfix_mechanicid", playerid);
	}
	else if(pojazd[target_vehicleid][v_owner_type] == VEHICLE_BUSINESS)//firmy
	{
		if(!IsPlayerOnDutyCompany(targetid)) return Error(playerid, "Gracz nie jest na służbie w firmie.");
		if(pojazd[target_vehicleid][v_owner] != gracz[targetid][firma]) return Error(playerid, "Gracz nie jest w firmie do której należy pojazd.");
		new engine, lights, alarm, doors, bonnet, boot, objective;
		GetVehicleParamsEx(target_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
		if(IsVehicleBike(pojazd[target_vehicleid][v_model]) && (listitem == 1 || listitem == 2)) return Error(playerid, "Pojazd nie jest wyposażony w ten komponent.");
		Info(playerid, "Zaoferowałeś naprawe pojazdu firmowego. Gracz teraz podejmuje decyzje...");
		new strTitle[128];
		new strContent[2048];
		new Float:fix_price = (VehicleDamages[listitem][vd_price_proc]/100.0)*CalcVehiclePriceEx(pojazd[target_vehicleid][v_model]);
		new Float:damage_proc = procent(float(VehicleDamages[listitem][vd_exp_km]-pojazd[target_vehicleid][v_damages_lifetime_km][listitem]), float(VehicleDamages[listitem][vd_exp_km]));
		if(damage_proc < 0.0) damage_proc = 0.0;
		format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Naprawa: "COL_ORANGE"%s "COL_RED"«•", VehicleDamages[listitem][vd_title]);
		format(strContent, 2048, ""COL_WHITE"Mechanik "COL_ROADA"%s"COL_WHITE" wystawił na Twoją "COL_RED"firmę"COL_WHITE" rachunek za naprawę "COL_LIME"%s"COL_WHITE" w pojeździe firmowym "COL_BLUE"%s"COL_WHITE".", nick(playerid), VehicleDamages[listitem][vd_title], GetVehicleName(pojazd[target_vehicleid][v_model]));
		format(strContent, 2048, "%s\n"COL_ORANGE"Jeśli odrzucisz rachunek, naprawa nie zostanie zrealizowana.", strContent);
		format(strContent, 2048, "%s\n"COL_RED"RACHUNEK ZOSTANIE OPŁACONY Z KONTA FIRMY", strContent);
		format(strContent, 2048, "%s\n\n"COL_RED"» "COL_WHITE"Podsumowanie:", strContent);
		format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Pojazd: "COL_BLUE"%s "COL_GREY"(UID: %d)", strContent, GetVehicleName(pojazd[target_vehicleid][v_model]), pojazd[target_vehicleid][v_id]);
		format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Komponent: "COL_LIME"%s", strContent, VehicleDamages[listitem][vd_title]);
		format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Koszt: "COL_GREEN"%d$", strContent, floatround(fix_price));
		format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Aktualny stan komponentu: %s", strContent, (damage_proc == 0.0) ? (""COL_RED"AWARIA") : (text_bar(floatround(damage_proc))));
		format(strContent, 2048, "%s\n\n"COL_GREEN"Czy zgadzasz się na naprawę i przyjmujesz rachunek?", strContent);
		Dialog_Show(targetid, OBDFIXCONFIRM, DIALOG_STYLE_MSGBOX, strTitle, strContent, "Akceptuj", "Odrzuc");
		//ładowanie cache
		SetPVarInt(targetid, "cache_odbfix_component", listitem);
		SetPVarInt(targetid, "cache_odbfix_vehicleid", target_vehicleid);
		SetPVarInt(targetid, "cache_odbfix_price", floatround(fix_price));
		SetPVarInt(targetid, "cache_odbfix_mechanicid", playerid);
	}
	else Error(playerid, "Tego pojazdu nie można diagnozować.");

	return 1;
}

Dialog:OBDFIXCONFIRM(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new vehicleid = GetPVarInt(playerid, "cache_odbfix_vehicleid");
	if(!IsPlayerInVehicle(playerid, vehicleid)) return Error(playerid, "Jesteś w niewłaściwym pojeździe.");
	new bool:firmowy = false;
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS) firmowy = true;
	new fix_price = GetPVarInt(playerid, "cache_odbfix_price");
	if(Money(playerid) < fix_price && firmowy == false) return Error(playerid, "Nie posiadasz wystarczająco dużo gotówki.");
	else if(firmowy == true && PlayerCompanyCash(playerid) < fix_price) return Error(playerid, "Twojej firmy nie stać na naprawę pojazdu.");
	new component = GetPVarInt(playerid, "cache_odbfix_component");
	pojazd[vehicleid][v_damages_lifetime_km][component] = 0;
	if(component == 15)//jeśli chłodnica
	{
		SetVehicleHealth(vehicleid, 1000.0);
		if(pojazd[vehicleid][v_id] != 0)
		{
			mq_format("UPDATE `pojazdy` SET `hp`='1000.0' WHERE `id`='%d';", pojazd[vehicleid][v_id]);
			mq_send("QUpdateVehicle");
		}
	}
	else if(component == 0)//opony
	{
		GetVehicleDamageStatus(vehicleid, pojazd[vehicleid][v_uvds_panels], pojazd[vehicleid][v_uvds_doors], pojazd[vehicleid][v_uvds_lights], pojazd[vehicleid][v_uvds_tires]);
		UpdateVehicleDamageStatus(vehicleid, pojazd[vehicleid][v_uvds_panels], pojazd[vehicleid][v_uvds_doors], pojazd[vehicleid][v_uvds_lights], 0);
	}
	format(pojazd[vehicleid][v_damages_lifetime_strdata], 256, "");//czyszczenie zmiennej
	for(new x; x < MAX_VEHICLEDAMAGES; x++)
	{
		if(IsVehicleBike(pojazd[vehicleid][v_model]) && (x == 1 || x == 2)) pojazd[vehicleid][v_damages_lifetime_km][x] = 0;
		format(pojazd[vehicleid][v_damages_lifetime_strdata], 256, "%s%d ", pojazd[vehicleid][v_damages_lifetime_strdata], pojazd[vehicleid][v_damages_lifetime_km][x]);
	}
	if(pojazd[vehicleid][v_id] != 0)
	{
		mq_format("UPDATE `pojazdy` SET `eksploatacja`='%s' WHERE `id`='%d';", pojazd[vehicleid][v_damages_lifetime_strdata], pojazd[vehicleid][v_id]);
		mq_send("QFixVehComponent");
	}
	//zapis logów firmy
	if(firmowy)
	{
		new cid = gracz[playerid][firma];
		company[cid][cny_money] -= fix_price;
		CompanySaveMoney(cid);
		LogCompany(cid, gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_WYDATEK, "%s. Koszt: %d$. Pojazd: %s(UID: %d). Saldo: %d$", VehicleDamages[component][vd_title], fix_price, GetVehicleName(pojazd[vehicleid][v_model]), pojazd[vehicleid][v_id], company[cid][cny_money]);
	} 
	else TakeMoney(playerid, fix_price);
	new strNotify[512];
	format(strNotify, 512, "Naprawiono ~y~%s~w~ w pojezdzie ~b~%s~w~.", VehicleDamages[component][vd_title], GetVehicleName(pojazd[vehicleid][v_model]));
	LeftNotifyShow(playerid, "Sukces!", strNotify, LN_GREEN);
	new mechanicid = GetPVarInt(playerid, "cache_odbfix_mechanicid");
	if(gracz[mechanicid][frakcja] == F_ROADASSIST && mechanicid != playerid)
	{
		LeftNotifyShow(mechanicid, "Sukces!", "Gracz przyjal oferte naprawy. Pojazd zostal naprawiony. Twoja frakcja otrzymala prowizje za ta naprawe.", LN_GREEN);
	}
	//--
	new Float:calc_prowizja = GetDistanceBetweenPoints(gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], fractions[F_ROADASSIST][fr_dutyX], fractions[F_ROADASSIST][fr_dutyY], fractions[F_ROADASSIST][fr_dutyZ]);
	calc_prowizja = calc_prowizja*0.8;
	GiveFractionMoneyOrScore(F_ROADASSIST, 0, floatround(calc_prowizja));
	//--
	//usuwanie cache
	DeletePVar(playerid, "cache_odbfix_component");
	DeletePVar(playerid, "cache_odbfix_vehicleid");
	DeletePVar(playerid, "cache_odbfix_price");
	DeletePVar(playerid, "cache_odbfix_mechanicid");
	return 1;
}

CMD:fnapraw(playerid, params[])
{
 	new fid = gracz[playerid][frakcja];
	if((fid != F_ROADASSIST) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /fnapraw [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	new target_vehicleid = GetPlayerVehicleID(targetid);
	if(target_vehicleid == 0) return Error(playerid, "Gracz musi być w pojeździe.");
	if(pojazd[target_vehicleid][v_owner_type] != VEHICLE_FRACTION) return Error(playerid, "To nie jest pojazd frakcyjny.");
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(target_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
	RepairVehicle(target_vehicleid);
	SetVehicleHealth(target_vehicleid, 1000.0);
	new strNotify[1024];
	format(strNotify, 1024, "Naprawiono ~y~karoserie~w~ w pojezdzie ~b~%s~w~.", GetVehicleName(pojazd[target_vehicleid][v_model]));
	LeftNotifyShow(playerid, "Sukces!", strNotify, LN_GREEN);
	LeftNotifyShow(targetid, "Sukces!", strNotify, LN_GREEN);
	return 1;
}

CMD:bodyfix(playerid, params[])
{
 	new fid = gracz[playerid][frakcja];
	if((fid != F_ROADASSIST) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /bodyfix [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	new target_vehicleid = GetPlayerVehicleID(targetid);
	if(target_vehicleid == 0) return Error(playerid, "Gracz musi być w pojeździe.");
	//DO REFAKTORYZACJI
	if(pojazd[target_vehicleid][v_owner_type] == VEHICLE_PLAYER)//privy
	{
		if(!IsPlayerCanDrive(targetid, target_vehicleid)) return Error(playerid, "Gracz nie ma uprawnień do tego pojazdu.");
		new engine, lights, alarm, doors, bonnet, boot, objective;
		GetVehicleParamsEx(target_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
		new strTitle[128];
		new strContent[2048];
		new Float:fix_price;
		fix_price = (1.0/100.0)*CalcVehiclePriceEx(pojazd[target_vehicleid][v_model]);
		format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Naprawa karoserii "COL_RED"«•", GetVehicleName(pojazd[target_vehicleid][v_model]));
		format(strContent, 2048, ""COL_WHITE"Mechanik "COL_ROADA"%s"COL_WHITE" wystawił Ci rachunek za naprawę "COL_LIME"karoserii"COL_WHITE" w pojeździe "COL_BLUE"%s"COL_WHITE".", nick(playerid), GetVehicleName(pojazd[target_vehicleid][v_model]));
		format(strContent, 2048, "%s\n"COL_RED"Jeśli odrzucisz rachunek, naprawa nie zostanie zrealizowana.", strContent);
		format(strContent, 2048, "%s\n\n"COL_RED"» "COL_WHITE"Podsumowanie:", strContent);
		format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Pojazd: "COL_BLUE"%s "COL_GREY"(UID: %d)", strContent, GetVehicleName(pojazd[target_vehicleid][v_model]), pojazd[target_vehicleid][v_id]);
		format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Komponent: "COL_LIME"Karoseria", strContent);
		format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Koszt: "COL_GREEN"%d$", strContent, floatround(fix_price));
		format(strContent, 2048, "%s\n\n"COL_GREEN"Czy zgadzasz się na naprawę i przyjmujesz rachunek?", strContent);
		Dialog_Show(targetid, KAROSERIAFIX, DIALOG_STYLE_MSGBOX, strTitle, strContent, "Akceptuj", "Odrzuc");
		Info(playerid, "Wystawiłeś dla gracza rachunek za naprawę karoserii. Jeśli przyjmie, karoseria zostanie naprawiona.");
		//ładowanie cache
		SetPVarInt(targetid, "cache_karoseriafix_vehicleid", target_vehicleid);
		SetPVarInt(targetid, "cache_karoseriafix_price", floatround(fix_price));
	}
	else if(pojazd[target_vehicleid][v_owner_type] == VEHICLE_BUSINESS)
	{
		if(!IsPlayerOnDutyCompany(targetid)) return Error(playerid, "Gracz nie jest na służbie w firmie.");
		if(pojazd[target_vehicleid][v_owner] != gracz[targetid][firma]) return Error(playerid, "Gracz nie jest w firmie do której należy pojazd.");
		new engine, lights, alarm, doors, bonnet, boot, objective;
		GetVehicleParamsEx(target_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
		new strTitle[128];
		new strContent[2048];
		new Float:fix_price;
		fix_price = (1.0/100.0)*CalcVehiclePriceEx(pojazd[target_vehicleid][v_model]);
		format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Naprawa karoserii "COL_RED"«•", GetVehicleName(pojazd[target_vehicleid][v_model]));
		format(strContent, 2048, ""COL_WHITE"Mechanik "COL_ROADA"%s"COL_WHITE" wystawił na Twoją "COL_RED"firmę"COL_WHITE" rachunek za naprawę "COL_LIME"karoserii"COL_WHITE" w pojeździe "COL_BLUE"%s"COL_WHITE".", nick(playerid), GetVehicleName(pojazd[target_vehicleid][v_model]));
		format(strContent, 2048, "%s\n"COL_ORANGE"Jeśli odrzucisz rachunek, naprawa nie zostanie zrealizowana.", strContent);
		format(strContent, 2048, "%s\n"COL_RED"RACHUNEK ZOSTANIE OPŁACONY Z KONTA FIRMY", strContent);
		format(strContent, 2048, "%s\n\n"COL_RED"» "COL_WHITE"Podsumowanie:", strContent);
		format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Pojazd: "COL_BLUE"%s "COL_GREY"(UID: %d)", strContent, GetVehicleName(pojazd[target_vehicleid][v_model]), pojazd[target_vehicleid][v_id]);
		format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Komponent: "COL_LIME"Karoseria", strContent);
		format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Koszt: "COL_GREEN"%d$", strContent, floatround(fix_price));
		format(strContent, 2048, "%s\n\n"COL_GREEN"Czy zgadzasz się na naprawę i przyjmujesz rachunek?", strContent);
		Dialog_Show(targetid, KAROSERIAFIX, DIALOG_STYLE_MSGBOX, strTitle, strContent, "Akceptuj", "Odrzuc");
		Info(playerid, "Wystawiłeś na firme do której należy gracz, rachunek za naprawę karoserii. Jeśli przyjmie, karoseria zostanie naprawiona.");
		//ładowanie cache
		SetPVarInt(targetid, "cache_karoseriafix_vehicleid", target_vehicleid);
		SetPVarInt(targetid, "cache_karoseriafix_price", floatround(fix_price));
	}
	else Error(playerid, "Tego pojazdu nie można naprawiać.");
	return 1;
}

Dialog:KAROSERIAFIX(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new vehicleid = GetPVarInt(playerid, "cache_karoseriafix_vehicleid");
	if(!IsPlayerInVehicle(playerid, vehicleid)) return Error(playerid, "Jesteś w niewłaściwym pojeździe.");
	new bool:firmowy = false;
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS) firmowy = true;
	new fix_price = GetPVarInt(playerid, "cache_karoseriafix_price");
	if(Money(playerid) < fix_price && firmowy == false) return Error(playerid, "Nie posiadasz wystarczająco dużo gotówki.");
	else if(firmowy == true && PlayerCompanyCash(playerid) < fix_price) return Error(playerid, "Twojej firmy nie stać na naprawę pojazdu.");
	new strNotify[1024];
	format(strNotify, 1024, "Naprawiono ~y~karoserie~w~ w pojezdzie ~b~%s~w~.", GetVehicleName(pojazd[vehicleid][v_model]));
	LeftNotifyShow(playerid, "Sukces!", strNotify, LN_GREEN);
	pojazd[vehicleid][v_karoseria_hits] = 0;
	//zapis logów firmy
	if(firmowy)
	{
		new cid = gracz[playerid][firma];
		company[cid][cny_money] -= fix_price;
		CompanySaveMoney(cid);
		LogCompany(cid, gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_WYDATEK, "Karoseria. Koszt: %d$. Pojazd: %s(UID: %d). Saldo: %d$", fix_price, GetVehicleName(pojazd[vehicleid][v_model]), pojazd[vehicleid][v_id], company[cid][cny_money]);
	} 
	else TakeMoney(playerid, fix_price);
	GetVehicleDamageStatus(vehicleid, pojazd[vehicleid][v_uvds_panels], pojazd[vehicleid][v_uvds_doors], pojazd[vehicleid][v_uvds_lights], pojazd[vehicleid][v_uvds_tires]);
	RepairVehicle(vehicleid);
	UpdateVehicleDamageStatus(vehicleid, 0, 0, 0, pojazd[vehicleid][v_uvds_tires]);
	//--
	new Float:calc_prowizja = GetDistanceBetweenPoints(gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], fractions[F_ROADASSIST][fr_dutyX], fractions[F_ROADASSIST][fr_dutyY], fractions[F_ROADASSIST][fr_dutyZ]);
	calc_prowizja = calc_prowizja*0.8;
	GiveFractionMoneyOrScore(F_ROADASSIST, 0, floatround(calc_prowizja));
	//--
	if(pojazd[vehicleid][v_id] != 0)
	{
		mq_format("UPDATE `pojazdy` SET `karoseria`='0 0 0 %d', `karoseria_hits`='0' WHERE `id`='%d';", pojazd[vehicleid][v_uvds_tires], pojazd[vehicleid][v_id]);
		mq_send("QZapisKaroserii");
	}
	return 1;
}


CMD:spray(playerid, params[])
{
 	new fid = gracz[playerid][frakcja];
	if((fid != F_ROADASSIST) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new strTitle[128];
	new strContent[1024];
	format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Konfiguracja spray'a "COL_RED"«•");
	format(strContent, 1024, "Akcja\tInfo");
	new tcol1, tcol2, paintjob;
	tcol1 = gracz[playerid][spray_color][0];
	tcol2 = gracz[playerid][spray_color][1];
	paintjob = gracz[playerid][spray_paintjob];
	new Float:vPos[3];
	new find_vehicleid = -1;
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		if(pojazd[v][v_owner_type] == VEHICLE_PLAYER)
		{
			GetVehiclePos(v, vPos[0], vPos[1], vPos[2]);
			if(IsPlayerInRangeOfPoint(playerid, 6.4, vPos[0], vPos[1], vPos[2]))
			{
				find_vehicleid = v;
				break;
			}
		}
	}
	format(strContent, 1024, "%s\n"COL_RED"[!] "COL_GREEN"Zmień kolor pierwszy\t"COL_WHITE"[K: {%06x}%03d"COL_WHITE"]", strContent, VehicleColoursTableRGBA[tcol1] >>> 8, tcol1);
	format(strContent, 1024, "%s\n"COL_RED"[!] "COL_GREEN"Zmień kolor drugi\t"COL_WHITE"[K: {%06x}%03d"COL_WHITE"]", strContent, VehicleColoursTableRGBA[tcol2] >>> 8, tcol2);
	if(paintjob) format(strContent, 1024, "%s\n"COL_RED"[!] "COL_GREEN"Tryb paintjob\t"COL_GREEN"[TAK: %03d"COL_GREEN"]", strContent, TranslateVehPaintjob(paintjob));
	else format(strContent, 1024, "%s\n"COL_RED"[!] "COL_GREEN"Tryb paintjob\t"COL_RED"[NIE"COL_RED"]", strContent);
	if(find_vehicleid == -1) format(strContent, 1024, "%s\n"COL_BLUE"[?] "COL_GREY"Aktualnie zasięg spray'a obejmuje:\t"COL_RED"---", strContent);
	else format(strContent, 1024, "%s\n"COL_BLUE"[?] "COL_GREY"Aktualnie zasięg spray'a obejmuje:\t"COL_GREEN"%s "COL_WHITE"[UID: "COL_RED"%d"COL_WHITE"]", strContent, GetVehicleName(pojazd[find_vehicleid][v_model]), pojazd[find_vehicleid][v_id]);
	Dialog_Show(playerid, SPRAYCONFIG, DIALOG_STYLE_TABLIST_HEADERS, strTitle, strContent, "Wybierz", "Anuluj");
	return 1;
}

Dialog:SPRAYCONFIG(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(listitem < 2)//2 pierwsze opcje
	{
		new strTitle[128];
		new strContent[3072];
		SetPVarInt(playerid, "cache_spray_colgroup", listitem);
		format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Wybór koloru %s "COL_RED"«•", (listitem == 0) ? ("pierwszy") : ("drugi"));
		for(new c; c < sizeof(VehicleColoursTableRGBA); c++)
		{
			format(strContent, 3072, "%s\n{%06x}%d", strContent, VehicleColoursTableRGBA[c] >>> 8, c);
		}
		Dialog_Show(playerid, SPRAYCOLORSET, DIALOG_STYLE_LIST, strTitle, strContent, "Wybierz", "Anuluj");
	}
	else if(listitem == 2)
	{
		new strTitle[128];
		new strContent[3072];
		format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Wybór paintjob'a "COL_RED"«•");
		format(strContent, 3072, "%s\n"COL_BLUE"•» "COL_RED"Wyłącz tryb paintjob", strContent);
		format(strContent, 3072, "%s\n"COL_LIME"» "COL_BLUE"Paintjob typ: 0", strContent);
		format(strContent, 3072, "%s\n"COL_LIME"» "COL_BLUE"Paintjob typ: 1", strContent);
		format(strContent, 3072, "%s\n"COL_LIME"» "COL_BLUE"Paintjob typ: 2", strContent);
		format(strContent, 3072, "%s\n"COL_EASY"» "COL_ORANGE"Usuń paintjob", strContent);
		Dialog_Show(playerid, SPRAYPAINTSET, DIALOG_STYLE_LIST, strTitle, strContent, "Wybierz", "Anuluj");
	}
	return 1;
}


Dialog:SPRAYCOLORSET(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new colgroup = GetPVarInt(playerid, "cache_spray_colgroup");
	new strInfo[128];
	gracz[playerid][spray_color][colgroup] = listitem;
	format(strInfo, 128, "Zmieniono kolor "COL_EASY"%s "COL_WHITE"na: {%06x}%03d", (colgroup == 0) ? ("pierwszy") : ("drugi"), VehicleColoursTableRGBA[listitem] >>> 8, gracz[playerid][spray_color][colgroup]);
	Info(playerid, strInfo);
	return 1;
}

Dialog:SPRAYPAINTSET(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	gracz[playerid][spray_paintjob] = listitem;
	if(gracz[playerid][spray_paintjob] > 0) Info(playerid, ""COL_GREEN"Spray został przestawiony na wybrany paintjob.");
	else Info(playerid, ""COL_RED"Wyłączono tryb paintjob'a dla spray'a.");
	return 1;
}

task Process_AutoSprayTake(playerid)
{
	if(gracz[playerid][frakcja] == F_ROADASSIST)
	{
		if(GetPlayerWeapon(playerid) == WEAPON_SPRAYCAN)
		{
			if(!IsPlayerInRangeOfPoint(playerid, 10.0, XYZ_SPRAY))
			{
				ResetPlayerWeapons(playerid);
				LeftNotifyShow(playerid, "info", "Opusciles lakiernie. Spray zostal Ci odebrany.", LN_GREY);
			}
		}
	}
	return 1;
}

task Process_Spray(playerid)
{
	if(gracz[playerid][frakcja] == F_ROADASSIST)
	{
		if(GetPlayerWeapon(playerid) == WEAPON_SPRAYCAN)
		{
			GetPlayerKeys(playerid, gracz[playerid][gpk_keys],  gracz[playerid][gpk_updown],  gracz[playerid][gpk_leftright]);
			if(gracz[playerid][gpk_keys] == KEY_FIRE)
			{
				//szukanie autka obok
				new Float:vPos[3];
				new find_vehicleid = -1;
				for(new v = GetVehiclePoolSize(); v != -1; v--)
				{
					if(pojazd[v][v_owner_type] == VEHICLE_PLAYER)
					{
						GetVehiclePos(v, vPos[0], vPos[1], vPos[2]);
						if(IsPlayerInRangeOfPoint(playerid, 6.4, vPos[0], vPos[1], vPos[2]))
						{
							find_vehicleid = v;
							break;
						}
					}
				}
				//-
				if(find_vehicleid == -1)
				{
					gracz[playerid][spray_progress] = 0;
					gracz[playerid][spray_block] = false;
					GameTextForPlayer(playerid, "~r~~h~~h~PRZERWANO!",  1000, 4);
				}
				else
				{
					gracz[playerid][spray_progress]++;
					if(gracz[playerid][spray_progress] < 30 && gracz[playerid][spray_block] == false)
					{
						gracz[playerid][spray_progress]++;
						GameTextForPlayer(playerid, "~b~~h~~h~LAKIEROWANIE...",  1000, 4);
					}
					else if(gracz[playerid][spray_block] == false)
					{
						GameTextForPlayer(playerid, "~g~~h~~h~GOTOWE!",  5000, 4);
						pojazd[find_vehicleid][v_paintjob] = gracz[playerid][spray_paintjob];
						if(gracz[playerid][spray_paintjob] > 0) //paintjob
						{
							pojazd[find_vehicleid][v_color][0] = gracz[playerid][spray_color][0];
							pojazd[find_vehicleid][v_color][1] = gracz[playerid][spray_color][1];
							if(pojazd[find_vehicleid][v_color][0] == 0 || pojazd[find_vehicleid][v_color][1] == 0)
							{
								pojazd[find_vehicleid][v_color][0] = 1;
								pojazd[find_vehicleid][v_color][1] = 1;
								ChangeVehicleColor(find_vehicleid, pojazd[find_vehicleid][v_color][0], pojazd[find_vehicleid][v_color][1]);
							}
							if(pojazd[find_vehicleid][v_id] != 0)
							{
								mq_format("UPDATE `pojazdy` SET `color_0`='%d', `color_1`='%d', `paintjob`='%d' WHERE `id`='%d';", pojazd[find_vehicleid][v_color][0], pojazd[find_vehicleid][v_color][1], pojazd[find_vehicleid][v_paintjob], pojazd[find_vehicleid][v_id]);
								mq_send("QUpdateVehicleColorP");
							}
							ChangeVehiclePaintjob(find_vehicleid, TranslateVehPaintjob(gracz[playerid][spray_paintjob]));
						}
						else//zwykły kolor
						{
							ChangeVehicleColor(find_vehicleid, gracz[playerid][spray_color][0], gracz[playerid][spray_color][1]);
							ChangeVehiclePaintjob(find_vehicleid, TranslateVehPaintjob(pojazd[find_vehicleid][v_paintjob]));
							pojazd[find_vehicleid][v_color][0] = gracz[playerid][spray_color][0];
							pojazd[find_vehicleid][v_color][1] = gracz[playerid][spray_color][1];
							if(pojazd[find_vehicleid][v_id] != 0)
							{
								mq_format("UPDATE `pojazdy` SET `color_0`='%d', `color_1`='%d' WHERE `id`='%d';", pojazd[find_vehicleid][v_color][0], pojazd[find_vehicleid][v_color][1], pojazd[find_vehicleid][v_id]);
								mq_send("QUpdateVehicleColor");
							}
						}
						RespawnVehicle(find_vehicleid, true, true);

						gracz[playerid][spray_block] = true;
						gracz[playerid][spray_progress] = 0;
					}
				}
			}
			else
			{
				if(gracz[playerid][spray_progress] > 0)//malował i puścił guzik
				{
					if(gracz[playerid][spray_block] == false) GameTextForPlayer(playerid, "~r~~h~~h~PRZERWANO!",  1000, 4);
					gracz[playerid][spray_block] = false;
					gracz[playerid][spray_progress] = 0;	
				}
			}
		}
	}
	return 1;
}

CMD:wybudz(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_EMERGENCY) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /wybudz [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 8.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	if(gracz[targetid][bw] == 0) return Error(playerid, "Ten gracz nie ma BW.");
	gracz[targetid][bw_time] = 0;
	new strInfo[128];
	format(strInfo, 128, "Zdjąłeś BW dla gracza {%06x}%s"COL_WHITE". Nagroda: "COL_GREEN"1000$"COL_WHITE".", GetPlayerColor(targetid) >>> 8, nick(targetid));
	Info(playerid, strInfo);
	GiveMoney(playerid, 1000);
	return 1;
}

CMD:uncrash(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_EMERGENCY) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /uncrash [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 8.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	if(gracz[targetid][wypadek] == 0) return Error(playerid, "Ten gracz nie ma wypadku.");
	gracz[targetid][wypadek_time] = 0;
	new strInfo[128];
	format(strInfo, 128, "Usunąłeś status wypadku z gracza {%06x}%s"COL_WHITE". Nagroda: "COL_GREEN"3000$"COL_WHITE".", GetPlayerColor(targetid) >>> 8, nick(targetid));
	Info(playerid, strInfo);
	GiveMoney(playerid, 3000);
	return 1;
}

CMD:ulecz(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_EMERGENCY) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /ulecz [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	SetPlayerHealth(targetid, 100.0);
	new strInfo[128];
	format(strInfo, 128, "Uleczyłeś gracza {%06x}%s"COL_WHITE".", GetPlayerColor(targetid) >>> 8, nick(targetid));
	Info(playerid, strInfo);
	format(strInfo, 128, "Zostałeś uleczony przez {%06x}%s"COL_WHITE".", GetPlayerColor(playerid) >>> 8, nick(playerid));
	Info(targetid, strInfo);
	return 1;
}



CMD:sorbent(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_EMERGENCY) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new oid = serwer[actual_oilid];
	if(oilSR_data[oid][ft_isfall])
	{
		new Float:lPos[3];
		lPos[0] = oilSR_position[oid][0];
		lPos[1] = oilSR_position[oid][1];
		lPos[2] = oilSR_position[oid][2];
		if(IsPlayerInRangeOfPoint(playerid, 2.0, lPos[0], lPos[1], lPos[2]))
		{
			OilSR_Destroy(oid);
			GiveMoney(playerid, 4000);
			GameTextForPlayer(playerid, "~g~+4000$", 5000, 3);
			GiveFractionMoneyOrScore(F_EMERGENCY, 1, 4000);
			new strCommand[128];
			format(strCommand, 128, "/me wysypuje sorbent na plamę oleju.");
			PC_EmulateCommand(playerid, strCommand);
			//---------
			for(new c; c < MAX_CALLS; c++)
			{
				if(calls[c][call_type] == 0) continue;
				if(calls[c][call_fraction] == F_EMERGENCY)
				{
					if(calls[c][call_type] == 4)//plama oleju
					{
						calls[c][call_status] = 0;
						calls[c][call_type] = 0;
						break;
					}
				}
			}
			//----------
			oilSR_createTime = gettime()+60*10;
		}
		else Error(playerid, "Nie jesteś przy plamie oleju.");
	}
	else Error(playerid, "Nie jesteś przy plamie oleju.");
	return 1;
}

CMD:adrenalina(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_EMERGENCY) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /adrenalina [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	gracz[targetid][stamina] = 100;
	mq_format("UPDATE `Konta` SET `stamina`='%d' WHERE `id`='%d';", gracz[targetid][stamina], gracz[targetid][UID]);
	mq_send("QUpdateStamina");
	HUD_UpdateSTAMINA(targetid);
	gracz[targetid][stamina_timestamp] = serwer[time_timestamp]+(60*5);
	new strInfo[128];
	format(strInfo, 128, "Zregenerowałeś zmęczenie dla gracza {%06x}%s"COL_WHITE".", GetPlayerColor(targetid) >>> 8, nick(targetid));
	Info(playerid, strInfo);
	format(strInfo, 128, "Twoje zmęczenie zostało zregenerowane przez {%06x}%s"COL_WHITE".", GetPlayerColor(playerid) >>> 8, nick(playerid));
	Info(targetid, strInfo);
	return 1;
}

task Process_Taxometr(playerid)
{
	if(gracz[playerid][opu_vehicleid] == 0) return 0;
	new vehicleid = gracz[playerid][opu_vehicleid];
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION && pojazd[vehicleid][v_owner] == F_TAXI)//pojazdy taxi
	{
		Taxometr_SetPricePerKM(playerid, pojazd[vehicleid][v_taxometr_price_per_km]);
		Taxometr_SetDistance(playerid, pojazd[vehicleid][v_taxometr_distance]);
		if(pojazd[vehicleid][v_taxometr_statuson]) Taxometr_SetPrice(playerid, pojazd[vehicleid][v_taxometr_price]);
		else Taxometr_SetPrice(playerid, -1);
	}
	return 1;
}

CMD:taxon(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_TAXI) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	if(GetPlayerVehicleSeat(playerid) != 0) return Error(playerid, "Nie jesteś kierowcą.");
	new vehicleid = gracz[playerid][opu_vehicleid];
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION && pojazd[vehicleid][v_owner] == F_TAXI)//pojazdy taxi
	{
		if(pojazd[vehicleid][v_taxometr_statuson] == true) return Error(playerid, "Taxometr jest już uruchomiony. Aby wyłączyć użyj "COL_RED"/taxoff"COL_WHITE".");
		pojazd[vehicleid][v_taxometr_statuson] = true;
		Taxometr_SetPrice(playerid, pojazd[vehicleid][v_taxometr_price]);
		LeftNotifyShow(playerid, "taxi", "Taxometr zostal ~g~uruchomiony~w~.", LN_YELLOW);
		new strCommand[128];
		format(strCommand, 128, "/me uruchamia taxometr.");
		PC_EmulateCommand(playerid, strCommand);
	}
	else Error(playerid, "Nie znajdujesz się w pojeździe TAXI.");
	return 1;
}

CMD:taxoff(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_TAXI) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	if(GetPlayerVehicleSeat(playerid) != 0) return Error(playerid, "Nie jesteś kierowcą.");
	new vehicleid = gracz[playerid][opu_vehicleid];
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION && pojazd[vehicleid][v_owner] == F_TAXI)//pojazdy taxi
	{
		if(pojazd[vehicleid][v_taxometr_statuson] == false) return Error(playerid, "Taxometr nie jest uruchomiony. Aby uruchomić użyj "COL_RED"/taxon"COL_WHITE".");
		pojazd[vehicleid][v_taxometr_statuson] = false;
		Taxometr_SetPrice(playerid, -1);
		LeftNotifyShow(playerid, "taxi", "Taxometr zostal ~r~wylaczony~w~.", LN_YELLOW);
		new strCommand[128];
		format(strCommand, 128, "/me wyłącza taxometr.");
		PC_EmulateCommand(playerid, strCommand);
	}
	else Error(playerid, "Nie znajdujesz się w pojeździe TAXI.");
	return 1;
}

CMD:treset(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_TAXI) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	if(GetPlayerVehicleSeat(playerid) != 0) return Error(playerid, "Nie jesteś kierowcą.");
	new vehicleid = gracz[playerid][opu_vehicleid];
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION && pojazd[vehicleid][v_owner] == F_TAXI)//pojazdy taxi
	{
		pojazd[vehicleid][v_taxometr_price] = 0;
		pojazd[vehicleid][v_taxometr_distance] = 0;
		Taxometr_SetPricePerKM(playerid, pojazd[vehicleid][v_taxometr_price_per_km]);
		Taxometr_SetDistance(playerid, pojazd[vehicleid][v_taxometr_distance]);
		Taxometr_SetPrice(playerid, pojazd[vehicleid][v_taxometr_price]);
		LeftNotifyShow(playerid, "taxi", "Taxometr zostal ~g~zresetowany~w~.", LN_YELLOW);
		new strCommand[128];
		format(strCommand, 128, "/me resetuje taxometr.");
		PC_EmulateCommand(playerid, strCommand);
	}
	else Error(playerid, "Nie znajdujesz się w pojeździe TAXI.");
	return 1;
}

CMD:tstawka(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_TAXI) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new bid;
	if(sscanf(params,"d", bid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /tstawka [kwota]");
	if(GetPlayerVehicleSeat(playerid) != 0) return Error(playerid, "Nie jesteś kierowcą.");
	new vehicleid = gracz[playerid][opu_vehicleid];
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION && pojazd[vehicleid][v_owner] == F_TAXI)//pojazdy taxi
	{
		if(pojazd[vehicleid][v_taxometr_price] > 0 || pojazd[vehicleid][v_taxometr_distance] > 0) return Error(playerid, "Aby ustalić nową stawkę, taxometr musi być zresetowany (/treset)."); 
		if(bid <= 0) return Error(playerid, "Stawka musi byc wieksza niz 0$.");
		if(bid > 100) return Error(playerid, "Stawka musi byc mniejsza niz 100$.");
		pojazd[vehicleid][v_taxometr_price_per_km] = bid;
		Taxometr_SetPricePerKM(playerid, pojazd[vehicleid][v_taxometr_price_per_km]);
		Taxometr_SetDistance(playerid, pojazd[vehicleid][v_taxometr_distance]);
		Taxometr_SetPrice(playerid, pojazd[vehicleid][v_taxometr_price]);
		LeftNotifyShow(playerid, "taxi", "Stawka w taxometrze zostala ~g~zaktualizowana~w~.", LN_YELLOW);
		new strCommand[128];
		format(strCommand, 128, "/me zmienia stawke w taxometrze.");
		PC_EmulateCommand(playerid, strCommand);
	}
	else Error(playerid, "Nie znajdujesz się w pojeździe TAXI.");
	return 1;
}

CMD:trachunek(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_TAXI) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /trachunek [idgracza]");
	if(GetPlayerVehicleSeat(playerid) != 0) return Error(playerid, "Nie jesteś kierowcą.");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	new vehicleid = gracz[playerid][opu_vehicleid];
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION && pojazd[vehicleid][v_owner] == F_TAXI)//pojazdy taxi
	{
		if(pojazd[vehicleid][v_taxometr_price] <= 0) return Error(playerid, "Taxometr wskazuje 0$. Nie możesz wystawić tak niskiego rachunku.");
		if(pojazd[vehicleid][v_taxometr_price] > Money(targetid)) return Error(playerid, "Gracz nie posiada takiej ilości gotówki.");
		new strTemp[512];
		//playerid
		format(strTemp, 512, "Wystawiono rachunek za przejazd dla {%06x}%s"COL_WHITE" w wysokości "COL_GREEN"%d$"COL_WHITE".", GetPlayerColor(targetid) >>> 8, nick(targetid), pojazd[vehicleid][v_taxometr_price]);
		Info(playerid, strTemp);
		Info(playerid, "Gracz w tej chwili podejmuje decyzje czy przyjmuje rachunek czy nie...");
		//targetid
		SetPVarInt(targetid, "trachunek_price", pojazd[vehicleid][v_taxometr_price]);
		SetPVarInt(targetid, "trachunek_workerid", playerid);
		format(strTemp, 512, ""COL_WHITE"Otrzymujesz rachunek za przejazd od {%06x}%s"COL_WHITE" w wysokości "COL_GREEN"%d$"COL_WHITE".\n"COL_RED"Opłacasz rachunek?", GetPlayerColor(playerid) >>> 8, nick(playerid), pojazd[vehicleid][v_taxometr_price]);
		Dialog_Show(targetid, TRACHUNEKCONFIRM, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_WHITE"Rachunek za przejazd "COL_RED"«•", strTemp, "Tak", "Nie");
	}
	else Error(playerid, "Nie znajdujesz się w pojeździe TAXI.");
	return 1;
}

Dialog:TRACHUNEKCONFIRM(playerid, response, listitem, inputtext[])
{
	new strInfo[512];
	new workerid = GetPVarInt(playerid, "trachunek_workerid");
	new rachunekprice = GetPVarInt(playerid, "trachunek_price");
	if(response)//przyjmuje
	{
		if(gracz[workerid][frakcja] == F_TAXI) 
		{
			format(strInfo, 512, ""COL_GREEN"Gracz %s opłacił rachunek za przejazd.\n"COL_LIME"Należność trafia do Twojej kieszeni!", nick(playerid));
			MessageGUIEx(workerid, ""COL_RED"•» "COL_WHITE"Rachunek opłacony "COL_RED"«•",  strInfo);
			Info(workerid, strInfo);
			GiveMoney(workerid, rachunekprice);
		}
		Info(playerid, "Rachunek za przejazd został opłacony.");
		TakeMoney(playerid, rachunekprice);
	}
	else//nie przyjmuje
	{
		if(gracz[workerid][frakcja] == F_TAXI) 
		{
			format(strInfo, 512, ""COL_RED"Gracz %s nie opłacił rachunku za przejazd.", nick(playerid));
			MessageGUIEx(workerid, ""COL_RED"•» "COL_WHITE"Rachunek odrzucony "COL_RED"«•",  strInfo);
			Info(workerid, strInfo);
		}
		Info(playerid, "Nie opłaciłeś rachunku za przejazd.");
	}
	return 1;
}
//****************************************************************************************************TRYB POŚCIGOWY DLA POLICJI/SG
CMD:scigaj(playerid, params[])
{
//	Info(playerid, "Już wkrótce...");
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /scigaj [idgracza]");
	if(gracz[playerid][chasing_targetid] == targetid && gracz[playerid][pursuit_enabled]) return Error(playerid, "Już ścigasz tego gracza.");
	if(gracz[targetid][pursuit_invisible_timestamp] > serwer[time_timestamp]) return Error(playerid, "Ten gracz niedawno miał pościg. Spróbuj za chwilę.");
	if(gracz[targetid][policestop_timestamp] < serwer[time_timestamp] && !gracz[targetid][pursuit_enabled]) return Error(playerid, "W ciagu ostatniej minuty gracz nie otrzymal polecenia do zatrzymania sie (/z).");
	if((gracz[targetid][frakcja] == F_POLICE || gracz[targetid][frakcja] == F_BORDERGUARD) && IsPlayerOnDutyFraction(targetid)) return Error(playerid, "Nie możesz ścigać innego funkcjonariusza.");
	if(!IsPlayerInRangeOfPoint(playerid, 100.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	gracz[playerid][pursuit_enabled] = true;
	gracz[targetid][pursuit_enabled] = true;
	gracz[playerid][chasing_targetid] = targetid;
	new strInfo[144];
	format(strInfo, 144, "Rozpocząłeś pościg za "COL_ORANGE"%s(%d)"COL_WHITE".", nick(targetid), targetid);
	Info(playerid, strInfo);
	return 1;
}

CMD:unscigaj(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	if(!gracz[playerid][pursuit_enabled]) return Error(playerid, "Nie jesteś podczas pościgu.");
	new strInfo[144];
	format(strInfo, 144, "Przerwałeś pościg za "COL_ORANGE"%s(%d)"COL_WHITE".", nick(gracz[playerid][chasing_targetid]), gracz[playerid][chasing_targetid]);
	Info(playerid, strInfo);
	gracz[playerid][pursuit_enabled] = false;
	gracz[playerid][chasing_targetid] = 0;
	HidePursuitTD(playerid);
	return 1;
}

task Process_Pursuit(playerid)//playerid - scigany
{
	if(gracz[playerid][pursuit_enabled])//gracz jest podczas pościgu
	{
		if(GetPursuitOfficers(playerid) < 1 && !((gracz[playerid][frakcja] == F_POLICE || gracz[playerid][frakcja] == F_BORDERGUARD) && IsPlayerOnDutyFraction(playerid)))//jeśli z jakiegoś powodu nikt go nie sciga, to przerywa akcje
		{
			gracz[playerid][pursuit_enabled] = false;
			gracz[playerid][pursuit_bar_left] = 0.0;
			gracz[playerid][pursuit_bar_right] = 0.0;
			HidePursuitTD(playerid);//ukrywanie TD
			return 1;
		}
		new Float:dist_between;
		new Float:MultiplierPursuit = 0.1;
		new bool:minOneOfficer = false;
		new strTemp[512];
		for(new p = PlayerPoolSize(); p != -1; p--)//funkcjonariusze
		{
			if(gracz[p][loggedin])//gracz zalogowany
			{
				if((gracz[p][frakcja] == F_POLICE || gracz[p][frakcja] == F_BORDERGUARD) && IsPlayerOnDutyFraction(p))//gracz jest funkcjonariuszem
				{
					if(gracz[p][pursuit_enabled])//funkcjonariusz jest podczas poscigu
					{
						if(gracz[p][chasing_targetid] == playerid)//chasing_targetid ściga playerid
						{
							ShowPursuitTD(playerid);
							ShowPursuitTD(p);
							dist_between = GetDistanceBetweenPoints(gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], gracz[p][PosX], gracz[p][PosY], gracz[p][PosZ]);
							if(dist_between < 65.0 && minOneOfficer == false)//jest wystarczająco blisko - policja wygrywa
							{
								minOneOfficer = true;
								new Float:temp_dist_between = dist_between; 
								MultiplierPursuit = 12.0;
								while(temp_dist_between > 0.0)
								{
									temp_dist_between -= 5.0;
									MultiplierPursuit -= 2.5;
								}
								if(MultiplierPursuit < 1.0) MultiplierPursuit = 1.0;

								if(gracz[playerid][pursuit_bar_left] > 0.0)//zmniejszanie paska sciganego
								{
									gracz[playerid][pursuit_bar_left] -= MultiplierPursuit;
								}
								else//zwiekszanie paska policji
								{
									if(gracz[playerid][pursuit_bar_right] > 60.0 && gracz[playerid][opu_speed] > 100) gracz[playerid][pursuit_bar_right] += 0.1;
									else gracz[playerid][pursuit_bar_right] += MultiplierPursuit;
								}
							}
							else if(minOneOfficer == false)//jest daleko - scigany wygrywa i nie ma żadnego oficera w pobliżu
							{
								MultiplierPursuit = 0.05*dist_between;
								if(MultiplierPursuit < 0.01) MultiplierPursuit = 0.01;
								if(MultiplierPursuit > 5.0) MultiplierPursuit = 5.0;
								if(gracz[playerid][pursuit_bar_right] > 0.0)//zmniejszanie paska policji
								{
									gracz[playerid][pursuit_bar_right] -= MultiplierPursuit;
								}
								else//zwiekszanie paska sciganego
								{
									gracz[playerid][pursuit_bar_left] += MultiplierPursuit;
								}
							}
							if(gracz[playerid][pursuit_bar_right] > 100.0) gracz[playerid][pursuit_bar_right] = 100.0;
							if(gracz[playerid][pursuit_bar_left] > 100.0) gracz[playerid][pursuit_bar_left] = 100.0;
							SetPorsuitWantedBarLeft(playerid, gracz[playerid][pursuit_bar_left]);
							SetPorsuitWantedBarRight(playerid, gracz[playerid][pursuit_bar_right]);
							SetPorsuitWantedBarLeft(p, gracz[playerid][pursuit_bar_left]);
							SetPorsuitWantedBarRight(p, gracz[playerid][pursuit_bar_right]);
							format(strTemp, 512, "Sciga Cie %d funkcjonariusz/y.", GetPursuitOfficers(playerid));
							SetPursuitInfo(playerid, strTemp);
							format(strTemp, 512, "Scigasz gracza:~w~ %s(%d)", nick(playerid), playerid);
							SetPursuitInfo(p, strTemp);
							if(gracz[playerid][pursuit_bar_right] > 99.0)//złapany
							{
								gracz[p][pursuit_enabled] = false;
								gracz[p][chasing_targetid] = 0;
								HidePursuitTD(p);
								GiveScore(p, 1);
								Info(p, ""COL_LIME"Udało Ci się złapać przestępcę! W nagrodę dostajesz 1 score.");
								gracz[p][pursuit_catch]++;
								gracz[p][pursuit_total]++;
								mq_format("UPDATE `Konta` SET `pursuit_total`='%d', `pursuit_catch`='%d' WHERE `id`='%d';", gracz[p][pursuit_total], gracz[p][pursuit_catch], gracz[p][UID]);
								mq_send("QSetPursuitStats");

								gracz[playerid][pursuit_total]++;
								HidePursuitTD(playerid);
								gracz[playerid][pursuit_enabled] = false;
								gracz[playerid][pursuit_bar_left] = 0.0;
								gracz[playerid][pursuit_bar_right] = 0.0;
								//kod wsadzający do celi
								gracz[playerid][wypadek_time] = 0;
								gracz[playerid][bw_time] = 0;

								TogglePlayerControllable(playerid, true);
								gracz[playerid][kajdanki] = false;
							
								format(strTemp, 512, ""COL_WHITE"Zostales aresztowany.\n"COL_RED"Powód: "COL_GREY"Przegrany pościg.");
								MessageGUIEx(playerid, ""COL_RED"•» "COL_WHITE"Areszt "COL_RED"«•",  strTemp);
								gracz[playerid][prisoner] = 1;
								gracz[playerid][prisoner_time] = 60*30;
								SetPlayerPos(playerid, prisons[gracz[playerid][prisoner_prisonid]][0], prisons[gracz[playerid][prisoner_prisonid]][1], prisons[gracz[playerid][prisoner_prisonid]][2]);
								mq_format("UPDATE `Konta` SET `prisoner`='%d', `prisoner_time`='%d', `prisoner_prisonid`='%d', `pursuit_total`='%d' WHERE `id`='%d';", gracz[playerid][prisoner], gracz[playerid][prisoner_time], gracz[playerid][prisoner_prisonid], gracz[playerid][pursuit_total], gracz[playerid][UID]);
								mq_send("QUpdatePrisonP");
								format(strTemp, 512, "Gracz "COL_RED"%s(%d)"COL_FMSG" przegrał pościg i został automatycznie wsadzony do więzienia.", nick(playerid), playerid);
								SendFractionMessage(F_POLICE, strTemp);
								SendFractionMessage(F_BORDERGUARD, strTemp);

								gracz[playerid][scigany_lvl] = 0;
								SetPlayerWantedLevel(playerid, 0);
								mq_format("UPDATE `Konta` SET `wanted_lvl`='%d', `wanted_reason`='%s' WHERE `id`='%d';", gracz[playerid][scigany_lvl], gracz[playerid][scigany_powod], gracz[playerid][UID]);
								mq_send("QUpdateWantedLvl");

								printf("[POSCIG] Gracz %s zostal zlapany!", nick(playerid));
								return 1;
							}
							else if(gracz[playerid][pursuit_bar_left] > 99.0)//uciekł
							{
								gracz[p][pursuit_enabled] = false;
								gracz[p][chasing_targetid] = 0;
								HidePursuitTD(p);
								gracz[p][pursuit_total]++;
								mq_format("UPDATE `Konta` SET `pursuit_total`='%d' WHERE `id`='%d';", gracz[p][pursuit_total], gracz[p][UID]);
								mq_send("QSetPursuitStats");

								gracz[playerid][pursuit_total]++;
								gracz[playerid][pursuit_escapes]++;
								HidePursuitTD(playerid);
								gracz[playerid][pursuit_enabled] = false;
								gracz[playerid][pursuit_bar_left] = 0.0;
								gracz[playerid][pursuit_bar_right] = 0.0;


								gracz[playerid][scigany_lvl] = 6;
								SetPlayerWantedLevel(playerid, 6);
								format(gracz[playerid][scigany_powod], 64, "Uciekl podczas poscigu.");
								GameTextForPlayer(playerid, "~r~JESTES POSZUKIWANY!!!", 5000, 0);
								mq_format("UPDATE `Konta` SET `wanted_lvl`='%d', `wanted_reason`='%s', `pursuit_total`='%d', `pursuit_escapes`='%d' WHERE `id`='%d';", gracz[playerid][scigany_lvl], gracz[playerid][scigany_powod], gracz[playerid][pursuit_total], gracz[playerid][pursuit_escapes], gracz[playerid][UID]);
								mq_send("QUpdateWantedLvlP");

								format(strTemp, 512, "Gracz "COL_RED"%s(%d)"COL_FMSG" wygrał pościg i został on dodany do listy poszukiwanych (/sclist).", nick(playerid), playerid);
								SendFractionMessage(F_POLICE, strTemp);
								SendFractionMessage(F_BORDERGUARD, strTemp);

								GiveScore(playerid, 1);

								Info(playerid, ""COL_LIME"Udało Ci się uciec! W nagrodę dostajesz 1 score.");
								gracz[playerid][pursuit_invisible_timestamp] = serwer[time_timestamp]+30;
								printf("[POSCIG] Gracz %s uciekl!", nick(playerid));
								return 1;
							}
						}
					}
				}
			}
		}
	}
	return 1;
}

stock SendSignalDisconnectPursuit(playerid)//gracz się rozłącza
{
	new bool:oneAction = false;
	if(gracz[playerid][pursuit_enabled])//gracz jest podczas pościgu
	{
		new strInfo[144];
		for(new p = PlayerPoolSize(); p != -1; p--)//funkcjonariusze/
		{
			if(gracz[p][loggedin])//gracz zalogowany
			{
				if((gracz[p][frakcja] == F_POLICE || gracz[p][frakcja] == F_BORDERGUARD) && IsPlayerOnDutyFraction(p))//gracz jest funkcjonariuszem - p
				{
					if(gracz[p][pursuit_enabled])//funkcjonariusz jest podczas poscigu
					{
						if(gracz[p][chasing_targetid] == playerid)//chasing_targetid ściga playerid
						{
							//funkcjonariusz - p
							gracz[p][pursuit_enabled] = false;//przerwanie pościgu dla funkcjonariuszy
							gracz[p][chasing_targetid] = 0;//zerowanie zmiennej
							HidePursuitTD(p);//ukrywanie TD
							format(strInfo, 144, "[POŚCIG] Gracz "COL_ORANGE"%s(%d)"COL_RED" opuścił serwer podczas pościgu. Odsiedzi swoje po powrocie.", nick(playerid), playerid);
							SendClientMessage(p, 0xFF0000FF, strInfo);
							//ścigany - playerid
							if(!oneAction)
							{
								gracz[playerid][prisoner] = 1;
								gracz[playerid][prisoner_time] = 60*60;//godzina
								mq_format("UPDATE `Konta` SET `prisoner`='%d', `prisoner_time`='%d', `prisoner_prisonid`='%d' WHERE `id`='%d';", gracz[playerid][prisoner], gracz[playerid][prisoner_time], gracz[playerid][prisoner_prisonid], gracz[playerid][UID]);
								mq_send("QUpdatePrison");
								oneAction = true;
							}
						}
					}
				}
				/*else//gracz nie jest funkcjonariuszem - anulowanie pościgu dla uciekającego - p
				{
					if(gracz[p][pursuit_enabled])//gracz jest podczas poscigu
					{
						if(gracz[playerid][chasing_targetid] == p)//chasing_targetid ściga p
						{
							if(GetPursuitOfficers(p) < 2)//sciga go więcej niż 1 funkcjonariusz
							{
								gracz[playerid][pursuit_enabled] = false;//wyłączanie dla funkcjonariusza scigania

								gracz[p][pursuit_enabled] = false;
								gracz[p][pursuit_bar_left] = 0.0;
								gracz[p][pursuit_bar_right] = 0.0;
								HidePursuitTD(p);//ukrywanie TD
							}
						}
					}
				}*/
			}
		}
	}
	return 1;
}

stock GetPursuitOfficers(playerid)
{
	new wynik;
	if(gracz[playerid][pursuit_enabled])//gracz jest podczas pościgu
	{
		for(new p = PlayerPoolSize(); p != -1; p--)//funkcjonariusze/
		{
			if(gracz[p][loggedin])//gracz zalogowany
			{
				if((gracz[p][frakcja] == F_POLICE || gracz[p][frakcja] == F_BORDERGUARD) && IsPlayerOnDutyFraction(p))//gracz jest funkcjonariuszem
				{
					if(gracz[p][pursuit_enabled])//funkcjonariusz jest podczas poscigu
					{
						if(gracz[p][chasing_targetid] == playerid)//chasing_targetid ściga playerid
						{
							wynik++;
						}
					}
				}
			}
		}
	}
	return wynik;
}
//TIUNING AUT

stock IsVehicleCompatibleType(model, type)
{
	new 
	compatible_types[ZVEH_MAX_COMPONENT_TYPES], 
	compatible_types_count; 

	GetVehicleCompatibleTypes(model, compatible_types, compatible_types_count); 

	for (new i = 0; i < compatible_types_count; i++) 
	{ 
		if(compatible_types[i] == type) return 1; 
	}  
	return 0;
}
CMD:tune(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_ROADASSIST) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /tune [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	new target_vehicleid = GetPlayerVehicleID(targetid);
	if(target_vehicleid == 0) return Error(playerid, "Gracz musi być w pojeździe.");
	if(pojazd[target_vehicleid][v_owner_type] != VEHICLE_PLAYER) return Error(playerid, "Tego pojazdu nie można tuningować.");
	if(!IsPlayerCanDrive(targetid, target_vehicleid)) return Error(playerid, "Gracz nie ma uprawnień do tego pojazdu.");
	if(IsVehicleBike(pojazd[target_vehicleid][v_model])) return Error(playerid, "Tego pojazdu nie można tuningować.");
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(target_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
	SetPVarInt(playerid, "cache_tune_targetid", targetid);
	new strTitle[128];
	format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Tuning pojazdu: "COL_ORANGE"%s "COL_RED"«•", GetVehicleName(pojazd[target_vehicleid][v_model]));
	new strTune[2048];
	format(strTune, 2048, "Typ komponentu\tDostępność");
	new typeName[64];
	new bool:shadowline;
	new slc[9];//shadowline color
	for (new i = 0; i < 12; i++) 
	{
		slc = (shadowline) ? ("{8D8D8D}") : ("{FFFFFF}");
		GetVehicleComponentTypeName(i, typeName);
		gui_cache[playerid][i][0] = IsVehicleCompatibleType(pojazd[target_vehicleid][v_model], i);
		format(strTune, 2048, "%s\n"COL_RED"» %s%s\t%s", strTune, slc, typeName, (gui_cache[playerid][i][0]) ? (""COL_GREEN"Dostępne") : (""COL_RED"Niedostępne"));
	}
	//neon
	switch(pojazd[target_vehicleid][v_model])
	{
		case 445,602,429,496,504,401,518,402,541,527,415,542,589,507,562,579,585,419,526,466,492,474,494,502,503,411,546,559,551,516,467,603,426,436,547,405,580,560,561,550,506,549,451,558,540,491,421,477,529:
		{
			gui_cache[playerid][12][0] = 1;
		}
		default:
		{
			gui_cache[playerid][12][0] = 0;
		}
	}
	format(strTune, 2048, "%s\n"COL_RED"» %sNeony\t%s", strTune, slc, (gui_cache[playerid][12][0]) ? (""COL_GREEN"Dostępne") : (""COL_RED"Niedostępne"));
	//neon end
	Dialog_Show(playerid, TUNEMENU, DIALOG_STYLE_TABLIST_HEADERS, strTitle, strTune, "Wybierz", "Anuluj");
	/*
	SetPVarInt(playerid, "cache_obd_targetid", targetid);
	new strCommand[128];
	format(strCommand, 128, "/me podłącza komputer diagnostyczny do pojazdu %s.", GetVehicleName(pojazd[target_vehicleid][v_model]));
	PC_EmulateCommand(playerid, strCommand);
	new strTitle[128];
	new str_obd_data[2048];
	format(strTitle, 128, ""COL_RED"•» "COL_WHITE"[OBD] Stan techniczny pojazdu: "COL_ORANGE"%s "COL_RED"«•", GetVehicleName(pojazd[target_vehicleid][v_model]));
	format(str_obd_data, 2048, "Komponent\tStan\tKoszt naprawy");
	new Float:damage_proc;
	new Float:fix_price;
	new bool:shadowline;
	new slc[9];//shadowline color
	for(new x; x < MAX_VEHICLEDAMAGES; x++)
	{
		damage_proc = procent(float(VehicleDamages[x][vd_exp_km]-pojazd[target_vehicleid][v_damages_lifetime_km][x]), float(VehicleDamages[x][vd_exp_km]));
		if(damage_proc < 0.0) damage_proc = 0.0;
		slc = (shadowline) ? ("{8D8D8D}") : ("{FFFFFF}");
		fix_price = (VehicleDamages[x][vd_price_proc]/100.0)*CalcVehiclePriceEx(pojazd[target_vehicleid][v_model]);
		if(IsVehicleBike(pojazd[target_vehicleid][v_model]) && (x == 1 || x == 2)) format(str_obd_data, 2048, "%s\n"COL_RED"» %s%s\t"COL_GREEN"-brak-\t"COL_LIME"---", str_obd_data, slc, VehicleDamages[x][vd_title]);
		else format(str_obd_data, 2048, "%s\n"COL_RED"» %s%s\t%s\t"COL_LIME"%d$", str_obd_data, slc, VehicleDamages[x][vd_title], (damage_proc == 0.0) ? (""COL_RED"AWARIA") : (text_bar(floatround(damage_proc))), floatround(fix_price));
		if(shadowline) shadowline = false;
		else shadowline = true;
	}
	Dialog_Show(playerid, OBDDATA, DIALOG_STYLE_TABLIST_HEADERS, strTitle, str_obd_data, "Napraw", "Anuluj");
	*/
	return 1;
}


Dialog:TUNEMENU(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(!gui_cache[playerid][listitem][0])
	{
		new strCommand[64];
		format(strCommand, 64, "/tune %d", GetPVarInt(playerid, "cache_tune_targetid"));
		PC_EmulateCommand(playerid, strCommand);
		return 1;
	}
	new targetid = GetPVarInt(playerid, "cache_tune_targetid");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	new target_vehicleid = GetPlayerVehicleID(targetid);
	if(target_vehicleid == 0) return Error(playerid, "Gracz musi być w pojeździe.");
	if(pojazd[target_vehicleid][v_owner_type] != VEHICLE_PLAYER) return Error(playerid, "Tego pojazdu nie można tuningować.");
	if(!IsPlayerCanDrive(targetid, target_vehicleid)) return Error(playerid, "Gracz nie ma uprawnień do tego pojazdu.");
	if(IsVehicleBike(pojazd[target_vehicleid][v_model])) return Error(playerid, "Tego pojazdu nie można tuningować.");
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(target_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
	new comptype = listitem;
	new compList[2048];
	format(compList, 2048, "Komponent\tCena");
	if(listitem < 12)//normalny tuning
	{
		new 
    		compatible_comp[ZVEH_MAX_COMPONENTS], 
  		compatible_comp_count;
  		GetVehicleCompatibleUpgrades(pojazd[target_vehicleid][v_model], compatible_comp, compatible_comp_count);
  		new compName[ZVEH_MAX_COMPONENT_NAME];
  		new codrugi;
  		new list = 0;
  		new tune_price = 5000;
  		new bool:shadowline;
		new slc[9];//shadowline color
		new comp_used;
		new antydouble[256];
  		for (new i = 0; i < compatible_comp_count; i++) 
		{ 
			if(GetVehicleComponentType(compatible_comp[i]) == comptype)
			{
				GetVehicleComponentName(compatible_comp[i], compName);
				tune_price = CalcTuneCost(compatible_comp[i], comptype, CalcVehiclePriceEx(pojazd[target_vehicleid][v_model]));
				comp_used = GetVehicleComponentInSlot(target_vehicleid, comptype);
				if(comptype == 3)//PROGI
				{
					if(codrugi < 2)
					{
						if(strfind(compName, "Left", true) != -1) strdel(compName, 0, 4);
						else if(strfind(compName, "Right", true) != -1) strdel(compName , 0, 5);
						if(strfind(antydouble, compName, true) != -1) continue;
						format(antydouble, 256, compName);
						slc = (shadowline) ? ("{8D8D8D}") : ("{FFFFFF}");
						if(pojazd[target_vehicleid][v_tune_data][comptype] == compatible_comp[i]) 
						{
							format(compList, 2048, "%s\n"COL_LIME"» %s%s\t"COL_LIME"Zastosowany", compList, slc, compName);
							gui_cache[playerid][list][3] = 0;
						}
						else if(comp_used == compatible_comp[i]) 
						{
							if(pojazd[target_vehicleid][v_tune_data][comptype] == comp_used) 
							{
								format(compList, 2048, "%s\n"COL_LIME"» %s%s\t"COL_LIME"Zastosowany", compList, slc, compName);
								gui_cache[playerid][list][3] = 1;
							}
							else
							{
								format(compList, 2048, "%s\n"COL_LIME"» %s%s\t"COL_BLUE"Zastosowany tymczasowo", compList, slc, compName);
								gui_cache[playerid][list][3] = 0;
							}
						}
						else 
						{
							format(compList, 2048, "%s\n"COL_LIME"» %s%s\t"COL_GREEN"%d$", compList, slc, compName, tune_price);
							gui_cache[playerid][list][3] = 0;
						}
						codrugi++;
						gui_cache[playerid][list][0] = compatible_comp[i];
						gui_cache[playerid][list][1] = comptype;
						gui_cache[playerid][list][2] = tune_price;
						list++;
					}
					else codrugi--;
				}
				else//wszystko
				{
					slc = (shadowline) ? ("{8D8D8D}") : ("{FFFFFF}");
					if(pojazd[target_vehicleid][v_tune_data][comptype] == compatible_comp[i]) 
					{
						format(compList, 2048, "%s\n"COL_LIME"» %s%s\t"COL_LIME"Zastosowany", compList, slc, compName);
						gui_cache[playerid][list][3] = 0;
					}
					else if(comp_used == compatible_comp[i]) 
					{
						if(pojazd[target_vehicleid][v_tune_data][comptype] == comp_used) 
						{
							format(compList, 2048, "%s\n"COL_LIME"» %s%s\t"COL_LIME"Zastosowany", compList, slc, compName);
							gui_cache[playerid][list][3] = 1;
						}
						else
						{
							format(compList, 2048, "%s\n"COL_LIME"» %s%s\t"COL_BLUE"Zastosowany tymczasowo", compList, slc, compName);
							gui_cache[playerid][list][3] = 0;
						}
					}
					else 
					{
						format(compList, 2048, "%s\n"COL_LIME"» %s%s\t"COL_GREEN"%d$", compList, slc, compName, tune_price);
						gui_cache[playerid][list][3] = 0;
					}
					gui_cache[playerid][list][0] = compatible_comp[i];
					gui_cache[playerid][list][1] = comptype;
					gui_cache[playerid][list][2] = tune_price;
					list++;
				}
			}
		}
		//*usuwanie komponentu
		format(compList, 2048, "%s\n"COL_LIME"» "COL_RED"Usuń komponent\t"COL_GREEN"%d$", compList, 3000);
		gui_cache[playerid][list][0] = 9999;
		gui_cache[playerid][list][1] = comptype;
		gui_cache[playerid][list][2] = 3000;
		gui_cache[playerid][list][3] = 0;
		list++;
		//*usuwanie komponentu end
		new strTitle[128];
		new typeName[64];
		GetVehicleComponentTypeName(comptype, typeName); 
		format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Tuning: "COL_LIME"%s "COL_RED"«•", typeName);
		Dialog_Show(playerid, TUNEMENUSELECT, DIALOG_STYLE_TABLIST_HEADERS, strTitle, compList, "Wybierz", "Wróć");
	}
	else if(listitem  == 12)//tuning neonów
	{
		new strNeonList[1024];
		new tune_price = 4000;
		new list = 0;
		new slc[9];//shadowline color
		new bool:shadowline;
		new used_neon = GetDynamicObjectModel(pojazd[target_vehicleid][v_object][8]);//>8-9< | 8-11 - MODEL
		format(strNeonList, 2048, "Komponent\tCena");
		for(new n; n < MAX_NEONS; n++)
		{
			slc = (shadowline) ? ("{8D8D8D}") : ("{FFFFFF}");
			tune_price = CalcTuneCost(neon_list[n][nn_model], listitem, CalcVehiclePriceEx(pojazd[target_vehicleid][v_model]));
			if(pojazd[target_vehicleid][v_neon_modelid] == neon_list[n][nn_model])
			{
				format(strNeonList, 2048, "%s\n"COL_LIME"» %sNeon: %s\t"COL_LIME"Zastosowany", strNeonList, slc, neon_list[n][nn_name]);
				gui_cache[playerid][list][3] = 0;
			}
			else if(used_neon == neon_list[n][nn_model])
			{
				if(pojazd[target_vehicleid][v_neon_modelid] == used_neon)
				{
					format(strNeonList, 2048, "%s\n"COL_LIME"» %sNeon: %s\t"COL_LIME"Zastosowany", strNeonList, slc, neon_list[n][nn_name]);
					gui_cache[playerid][list][3] = 1;
				}
				else
				{
					format(strNeonList, 2048, "%s\n"COL_LIME"» %sNeon: %s\t"COL_BLUE"Zastosowany tymczasowo", strNeonList, slc, neon_list[n][nn_name]);
					gui_cache[playerid][list][3] = 0;
				}
			}
			else
			{
				format(strNeonList, 2048, "%s\n"COL_LIME"» %sNeon: %s\t"COL_GREEN"%d$", strNeonList, slc, neon_list[n][nn_name], tune_price);
				gui_cache[playerid][list][3] = 0;
			}
			gui_cache[playerid][list][0] = n;
			gui_cache[playerid][list][2] = tune_price;
			list++;
		}
		//usuwanie neona
		gui_cache[playerid][list][0] = 9999;
		gui_cache[playerid][list][1] = listitem;
		gui_cache[playerid][list][2] = 3000;
		gui_cache[playerid][list][3] = 0;
		list++;
		//--
		format(strNeonList, 2048, "%s\n"COL_LIME"» "COL_RED"Usuń komponent\t"COL_GREEN"%d$", strNeonList, 3000);
		new strTitle[128];
		format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Tuning: "COL_LIME"Neony "COL_RED"«•");
		Dialog_Show(playerid, TUNENEON, DIALOG_STYLE_TABLIST_HEADERS, strTitle, strNeonList, "Wybierz", "Wróć");
	}
	else return Error(playerid, "Wystąpił nieoczekiwany błąd.");
	return 1;
}

Dialog:TUNENEON(playerid, response, listitem, inputtext[])
{
	if(!response || gui_cache[playerid][listitem][3] == 1)
	{
		new strCommand[64];
		format(strCommand, 64, "/tune %d", GetPVarInt(playerid, "cache_tune_targetid"));
		PC_EmulateCommand(playerid, strCommand);
		return 1;
	}
	new targetid = GetPVarInt(playerid, "cache_tune_targetid");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	new target_vehicleid = GetPlayerVehicleID(targetid);
	if(target_vehicleid == 0) return Error(playerid, "Gracz musi być w pojeździe.");
	if(pojazd[target_vehicleid][v_owner_type] != VEHICLE_PLAYER) return Error(playerid, "Tego pojazdu nie można tuningować.");
	if(!IsPlayerCanDrive(targetid, target_vehicleid)) return Error(playerid, "Gracz nie ma uprawnień do tego pojazdu.");
	if(IsVehicleBike(pojazd[target_vehicleid][v_model])) return Error(playerid, "Tego pojazdu nie można tuningować.");
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(target_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
	new tune_component = gui_cache[playerid][listitem][0];
	new tune_price = gui_cache[playerid][listitem][2];
	if(tune_component == 9999)
	{
		Dialog_Show(playerid, TUNENEONTYPE, DIALOG_STYLE_TABLIST,  ""COL_RED"•» "COL_WHITE"Co chcesz zrobić? "COL_RED"«•", ""COL_RED"» "COL_BLUE"Testuj\t"COL_GREY"[tuning tymczasowy, nie zapisuje się]\n"COL_RED"» "COL_GREEN"Zdemontuj na stałe\t"COL_GREY"[wystawiasz rachunek, zapisze się]", "Wybierz", "Anuluj");
		SetPVarInt(playerid, "cache_tune_component", 9999);
		SetPVarInt(playerid, "cache_tune_price", tune_price);
	}
	else
	{
		Dialog_Show(playerid, TUNENEONTYPE, DIALOG_STYLE_TABLIST,  ""COL_RED"•» "COL_WHITE"Co chcesz zrobić? "COL_RED"«•", ""COL_RED"» "COL_BLUE"Testuj\t"COL_GREY"[tuning tymczasowy, nie zapisuje się]\n"COL_RED"» "COL_GREEN"Zamontuj na stałe\t"COL_GREY"[wystawiasz rachunek, zapisze się]", "Wybierz", "Anuluj");
		SetPVarInt(playerid, "cache_tune_component", tune_component);
		SetPVarInt(playerid, "cache_tune_price", tune_price);
	}
	return 1;
}

Dialog:TUNENEONTYPE(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		new strCommand[64];
		format(strCommand, 64, "/tune %d", GetPVarInt(playerid, "cache_tune_targetid"));
		PC_EmulateCommand(playerid, strCommand);
		return 1;
	}
	new targetid = GetPVarInt(playerid, "cache_tune_targetid");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	new target_vehicleid = GetPlayerVehicleID(targetid);
	if(target_vehicleid == 0) return Error(playerid, "Gracz musi być w pojeździe.");
	if(pojazd[target_vehicleid][v_owner_type] != VEHICLE_PLAYER) return Error(playerid, "Tego pojazdu nie można tuningować.");
	if(!IsPlayerCanDrive(targetid, target_vehicleid)) return Error(playerid, "Gracz nie ma uprawnień do tego pojazdu.");
	if(IsVehicleBike(pojazd[target_vehicleid][v_model])) return Error(playerid, "Tego pojazdu nie można tuningować.");
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(target_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
	new tune_component = GetPVarInt(playerid, "cache_tune_component");
	new tune_price = GetPVarInt(playerid, "cache_tune_price");
	new strTitle[128];
	new strContent[2048];
	switch(listitem)
	{
		case 0://tymczasowy
		{
			if(tune_component == 9999)
			{
				new compinslot = 0;
				if(pojazd[target_vehicleid][v_object][8] != 0) compinslot = GetDynamicObjectModel(pojazd[target_vehicleid][v_object][8]);
				if(compinslot)
				{
					if(pojazd[target_vehicleid][v_object][8] != 0) 
					{
						DestroyDynamicObject(pojazd[target_vehicleid][v_object][8]);
						pojazd[target_vehicleid][v_object][8] = 0;
					}
					if(pojazd[target_vehicleid][v_object][9] != 0) 
					{
						DestroyDynamicObject(pojazd[target_vehicleid][v_object][9]);
						pojazd[target_vehicleid][v_object][9] = 0;
					}
					Info(playerid, ""COL_RED"Komponent usunięto tymczasowo.");
					Info(targetid, ""COL_RED"UWAGA! Komponent z twojego pojazdu został usunięty tymczasowo!");
					SetVehicleVelocity(target_vehicleid, 0.0, 0.0, 0.1);
				}
				else Error(playerid, "Brak komponentu do usunięcia.");
			}
			else
			{
				if(pojazd[target_vehicleid][v_neon_modelid] == neon_list[tune_component][nn_model]) 
				{
					if(pojazd[target_vehicleid][v_object][8] != 0) 
					{
						DestroyDynamicObject(pojazd[target_vehicleid][v_object][8]);
						pojazd[target_vehicleid][v_object][8] = 0;
					}
					if(pojazd[target_vehicleid][v_object][9] != 0) 
					{
						DestroyDynamicObject(pojazd[target_vehicleid][v_object][9]);
						pojazd[target_vehicleid][v_object][9] = 0;
					}
					if(pojazd[target_vehicleid][v_object][8] == 0)
					{
						pojazd[target_vehicleid][v_object][8] = CreateDynamicObject(neon_list[tune_component][nn_model], 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
						AttachDynamicObjectToVehicle(pojazd[target_vehicleid][v_object][8], target_vehicleid, 0.8000, 0.0570, -0.4655, 0.0, 0.0, 0.0);//1 strona
					}
					if(pojazd[target_vehicleid][v_object][9] == 0)
					{
						pojazd[target_vehicleid][v_object][9] = CreateDynamicObject(neon_list[tune_component][nn_model], 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
						AttachDynamicObjectToVehicle(pojazd[target_vehicleid][v_object][9], target_vehicleid, -0.8000, 0.0570, -0.4655, 0.0, 0.0, 0.0);//druga strona
					}
					
					Info(playerid, ""COL_BLUE"Przywrócono posiadany przez pojazd komponent.");
					Info(targetid, ""COL_BLUE"Przywrócono posiadany komponent!");
					SetVehicleVelocity(target_vehicleid, 0.0, 0.0, 0.1);
				}
				else
				{
					if(pojazd[target_vehicleid][v_object][8] != 0) 
					{
						DestroyDynamicObject(pojazd[target_vehicleid][v_object][8]);
						pojazd[target_vehicleid][v_object][8] = 0;
					}
					if(pojazd[target_vehicleid][v_object][9] != 0) 
					{
						DestroyDynamicObject(pojazd[target_vehicleid][v_object][9]);
						pojazd[target_vehicleid][v_object][9] = 0;
					}
					if(pojazd[target_vehicleid][v_object][8] == 0)
					{
						pojazd[target_vehicleid][v_object][8] = CreateDynamicObject(neon_list[tune_component][nn_model], 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
						AttachDynamicObjectToVehicle(pojazd[target_vehicleid][v_object][8], target_vehicleid, 0.8000, 0.0570, -0.4655, 0.0, 0.0, 0.0);//1 strona
					}
					if(pojazd[target_vehicleid][v_object][9] == 0)
					{
						pojazd[target_vehicleid][v_object][9] = CreateDynamicObject(neon_list[tune_component][nn_model], 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
						AttachDynamicObjectToVehicle(pojazd[target_vehicleid][v_object][9], target_vehicleid, -0.8000, 0.0570, -0.4655, 0.0, 0.0, 0.0);//druga strona
					}
					
					Info(playerid, ""COL_RED"Komponent zamontowano tymczasowo.");
					Info(targetid, ""COL_RED"UWAGA! Komponent na Twój pojazd został nałożony tymczasowo!");
					SetVehicleVelocity(target_vehicleid, 0.0, 0.0, 0.1);
				}
			}
		}
		case 1://na stałe - neon
		{
				if(pojazd[target_vehicleid][v_neon_modelid] == 0 && tune_component == 9999) return Error(playerid, "Pojazd nie posiada komponentu.");//usuwanie
				else if(tune_component != 9999)
				{
					if(pojazd[target_vehicleid][v_neon_modelid] == neon_list[tune_component][nn_model]) 
					{
						Error(playerid, "Gracz posiada już ten komponent. Nie możesz wystawić rachunku.");
						if(pojazd[target_vehicleid][v_object][8] != 0) 
						{
							DestroyDynamicObject(pojazd[target_vehicleid][v_object][8]);
							pojazd[target_vehicleid][v_object][8] = 0;
						}
						if(pojazd[target_vehicleid][v_object][9] != 0) 
						{
							DestroyDynamicObject(pojazd[target_vehicleid][v_object][9]);
							pojazd[target_vehicleid][v_object][9] = 0;
						}
						if(pojazd[target_vehicleid][v_object][8] == 0)
						{
							pojazd[target_vehicleid][v_object][8] = CreateDynamicObject(neon_list[tune_component][nn_model], 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
							AttachDynamicObjectToVehicle(pojazd[target_vehicleid][v_object][8], target_vehicleid, 0.8000, 0.0570, -0.4655, 0.0, 0.0, 0.0);//1 strona
						}
						if(pojazd[target_vehicleid][v_object][9] == 0)
						{
							pojazd[target_vehicleid][v_object][9] = CreateDynamicObject(neon_list[tune_component][nn_model], 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
							AttachDynamicObjectToVehicle(pojazd[target_vehicleid][v_object][9], target_vehicleid, -0.8000, 0.0570, -0.4655, 0.0, 0.0, 0.0);//druga strona
						}
						SetVehicleVelocity(target_vehicleid, 0.0, 0.0, 0.1);
						return 1;
					}
				}
				Info(playerid, "Zaoferowałeś tuning pojazdu. Gracz teraz podejmuje decyzje...");

				format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Tuning: "COL_ORANGE"Neony "COL_RED"«•");
				format(strContent, 2048, ""COL_WHITE"Mechanik "COL_ROADA"%s"COL_WHITE" wystawił Ci rachunek za tuning "COL_LIME"Neony"COL_WHITE" w pojeździe "COL_BLUE"%s"COL_WHITE".", nick(playerid), GetVehicleName(pojazd[target_vehicleid][v_model]));
				format(strContent, 2048, "%s\n"COL_RED"Jeśli odrzucisz rachunek, tuning nie zostanie zrealizowany.", strContent);
				format(strContent, 2048, "%s\n\n"COL_RED"» "COL_WHITE"Podsumowanie:", strContent);
				format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Pojazd: "COL_BLUE"%s "COL_GREY"(UID: %d)", strContent, GetVehicleName(pojazd[target_vehicleid][v_model]), pojazd[target_vehicleid][v_id]);
				new compName[32];
				if(tune_component != 9999) format(compName, 32, "%s", neon_list[tune_component][nn_name]);
				format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Komponent: %s", strContent, (tune_component == 9999) ? (""COL_RED"USUŃ KOMPONENT") : (compName));
				format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Typ tuningu: "COL_LIME"Neony", strContent);
				format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Koszt: "COL_GREEN"%d$", strContent, tune_price);
				format(strContent, 2048, "%s\n\n"COL_GREEN"Czy zgadzasz się na tuning i przyjmujesz rachunek?", strContent);
				//ładowanie cache
				SetPVarInt(targetid, "cache_tune_component", tune_component);
				SetPVarInt(targetid, "cache_tune_vehicleid", target_vehicleid);
				SetPVarInt(targetid, "cache_tune_price", tune_price);
				SetPVarInt(targetid, "cache_tune_mechanicid", playerid);
				Dialog_Show(targetid, TUNENEONCONFIRM, DIALOG_STYLE_MSGBOX, strTitle, strContent, "Akceptuj", "Odrzuc");	
		}
	}
	return 1;
}

Dialog:TUNENEONCONFIRM(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new vehicleid = GetPVarInt(playerid, "cache_tune_vehicleid");
	if(!IsPlayerInVehicle(playerid, vehicleid)) return Error(playerid, "Jesteś w niewłaściwym pojeździe.");
	new tune_price = GetPVarInt(playerid, "cache_tune_price");
	if(Money(playerid) < tune_price) return Error(playerid, "Nie posiadasz wystarczająco dużo gotówki.");
	new tune_component = GetPVarInt(playerid, "cache_tune_component");
	new mechanicid = GetPVarInt(playerid, "cache_tune_mechanicid");
	if(tune_component == 9999)
	{
		if(pojazd[vehicleid][v_object][8] != 0) 
		{
			DestroyDynamicObject(pojazd[vehicleid][v_object][8]);
			pojazd[vehicleid][v_object][8] = 0;
		}
		if(pojazd[vehicleid][v_object][9] != 0) 
		{
			DestroyDynamicObject(pojazd[vehicleid][v_object][9]);
			pojazd[vehicleid][v_object][9] = 0;
		}
		pojazd[vehicleid][v_neon_modelid] = 0;
		SetVehicleVelocity(vehicleid, 0.0, 0.0, 0.1);
	}
	else 
	{
		if(pojazd[vehicleid][v_object][8] != 0) 
		{
			DestroyDynamicObject(pojazd[vehicleid][v_object][8]);
			pojazd[vehicleid][v_object][8] = 0;
		}
		if(pojazd[vehicleid][v_object][9] != 0) 
		{
			DestroyDynamicObject(pojazd[vehicleid][v_object][9]);
			pojazd[vehicleid][v_object][9] = 0;
		}
		if(pojazd[vehicleid][v_object][8] == 0)
		{
			pojazd[vehicleid][v_object][8] = CreateDynamicObject(neon_list[tune_component][nn_model], 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][8], vehicleid, 0.8000, 0.0570, -0.4655, 0.0, 0.0, 0.0);//1 strona
		}
		if(pojazd[vehicleid][v_object][9] == 0)
		{
			pojazd[vehicleid][v_object][9] = CreateDynamicObject(neon_list[tune_component][nn_model], 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][9], vehicleid, -0.8000, 0.0570, -0.4655, 0.0, 0.0, 0.0);//druga strona
		}
		pojazd[vehicleid][v_neon_modelid] = neon_list[tune_component][nn_model];
		SetVehicleVelocity(vehicleid, 0.0, 0.0, 0.1);
	}
	if(pojazd[vehicleid][v_id] != 0)
	{
		mq_format("UPDATE `pojazdy` SET `neon_modelid`='%d' WHERE `id`='%d';", pojazd[vehicleid][v_neon_modelid] , pojazd[vehicleid][v_id]);
		mq_send("QSaveTune");
	}
	TakeMoney(playerid, tune_price);
	new strNotify[512];
	if(tune_component == 9999)
	{
		format(strNotify, 512, "Usunieto tuning ~y~Neony~w~ w pojezdzie ~b~%s~w~.", GetVehicleName(pojazd[vehicleid][v_model]));
		LeftNotifyShow(playerid, "Sukces!", strNotify, LN_GREEN);
		Info(playerid, ""COL_GREEN"Komponent został na stałe usunięty.");
	}
	else
	{
		format(strNotify, 512, "Stuningowano ~y~Neony~w~ w pojezdzie ~b~%s~w~.", GetVehicleName(pojazd[vehicleid][v_model]));
		LeftNotifyShow(playerid, "Sukces!", strNotify, LN_GREEN);
		Info(playerid, ""COL_GREEN"Komponent został zamontowany na stałe.");
		GiveFractionMoneyOrScore(F_ROADASSIST, 0, 300);
		//--
	}
	if(gracz[mechanicid][frakcja] == F_ROADASSIST)
	{
		LeftNotifyShow(mechanicid, "Sukces!", "Gracz przyjal oferte tuningu. Pojazd zostal stuningowany. Twoja frakcja otrzymala prowizje za tuning.", LN_GREEN);
	}

	DeletePVar(playerid, "cache_tune_component");
	DeletePVar(playerid, "cache_tune_vehicleid");
	DeletePVar(playerid, "cache_tune_price");
	DeletePVar(playerid, "cache_tune_mechanicid");
	return 1;
}


Dialog:TUNEMENUSELECT(playerid, response, listitem, inputtext[])
{
	if(!gui_cache[playerid][listitem][0] || !response || gui_cache[playerid][listitem][3] == 1)
	{
		new strCommand[64];
		format(strCommand, 64, "/tune %d", GetPVarInt(playerid, "cache_tune_targetid"));
		PC_EmulateCommand(playerid, strCommand);
		return 1;
	}
	new targetid = GetPVarInt(playerid, "cache_tune_targetid");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	new target_vehicleid = GetPlayerVehicleID(targetid);
	if(target_vehicleid == 0) return Error(playerid, "Gracz musi być w pojeździe.");
	if(pojazd[target_vehicleid][v_owner_type] != VEHICLE_PLAYER) return Error(playerid, "Tego pojazdu nie można tuningować.");
	if(!IsPlayerCanDrive(targetid, target_vehicleid)) return Error(playerid, "Gracz nie ma uprawnień do tego pojazdu.");
	if(IsVehicleBike(pojazd[target_vehicleid][v_model])) return Error(playerid, "Tego pojazdu nie można tuningować.");
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(target_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
	new tune_component = gui_cache[playerid][listitem][0];
	new tune_comptype = gui_cache[playerid][listitem][1];
	new tune_price = gui_cache[playerid][listitem][2];
	if(tune_component == 9999)
	{
		Dialog_Show(playerid, TUNETYPE, DIALOG_STYLE_TABLIST,  ""COL_RED"•» "COL_WHITE"Co chcesz zrobić? "COL_RED"«•", ""COL_RED"» "COL_BLUE"Testuj\t"COL_GREY"[tuning tymczasowy, nie zapisuje się]\n"COL_RED"» "COL_GREEN"Zdemontuj na stałe\t"COL_GREY"[wystawiasz rachunek, zapisze się]", "Wybierz", "Anuluj");
		SetPVarInt(playerid, "cache_tune_component", 9999);
		SetPVarInt(playerid, "cache_tune_comptype", tune_comptype);
		SetPVarInt(playerid, "cache_tune_price", tune_price);
	}
	else if(IsVehicleUpgradeCompatible(pojazd[target_vehicleid][v_model], tune_component))
	{
		Dialog_Show(playerid, TUNETYPE, DIALOG_STYLE_TABLIST,  ""COL_RED"•» "COL_WHITE"Co chcesz zrobić? "COL_RED"«•", ""COL_RED"» "COL_BLUE"Testuj\t"COL_GREY"[tuning tymczasowy, nie zapisuje się]\n"COL_RED"» "COL_GREEN"Zamontuj na stałe\t"COL_GREY"[wystawiasz rachunek, zapisze się]", "Wybierz", "Anuluj");
		SetPVarInt(playerid, "cache_tune_component", tune_component);
		SetPVarInt(playerid, "cache_tune_comptype", tune_comptype);
		SetPVarInt(playerid, "cache_tune_price", tune_price);
	} 
	else Error(playerid, "Komponent nie jest kompatybilny z tym pojazdem.");
	return 1;
}

Dialog:TUNETYPE(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		new strCommand[64];
		format(strCommand, 64, "/tune %d", GetPVarInt(playerid, "cache_tune_targetid"));
		PC_EmulateCommand(playerid, strCommand);
		return 1;
	}
	new targetid = GetPVarInt(playerid, "cache_tune_targetid");
	if(!logged(targetid)) return Error(playerid, "Gracz nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	new target_vehicleid = GetPlayerVehicleID(targetid);
	if(target_vehicleid == 0) return Error(playerid, "Gracz musi być w pojeździe.");
	if(pojazd[target_vehicleid][v_owner_type] != VEHICLE_PLAYER) return Error(playerid, "Tego pojazdu nie można tuningować.");
	if(!IsPlayerCanDrive(targetid, target_vehicleid)) return Error(playerid, "Gracz nie ma uprawnień do tego pojazdu.");
	if(IsVehicleBike(pojazd[target_vehicleid][v_model])) return Error(playerid, "Tego pojazdu nie można tuningować.");
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(target_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
	/*if(IsVehicleUpgradeCompatible(pojazd[target_vehicleid][v_model], gui_cache[playerid][listitem][0]))
	{
		if(gui_cache[playerid][listitem][1] == 3)
		{
			AddVehicleComponent(target_vehicleid, gui_cache[playerid][listitem][0]);
			AddVehicleComponent(target_vehicleid, gui_cache[playerid][listitem][0]);
		}
		else AddVehicleComponent(target_vehicleid, gui_cache[playerid][listitem][0]);
		DoneInfo();
	} 
	else Error(playerid, "Komponent nie jest kompatybilny z tym pojazdem.");
	*/
	new tune_component = GetPVarInt(playerid, "cache_tune_component");
	new tune_comptype = GetPVarInt(playerid, "cache_tune_comptype");
	new tune_price = GetPVarInt(playerid, "cache_tune_price");
	new compName[ZVEH_MAX_COMPONENT_NAME];
	GetVehicleComponentName(tune_component, compName);
	new typeName[64];
	GetVehicleComponentTypeName(tune_comptype, typeName);

	if(IsVehicleUpgradeCompatible(pojazd[target_vehicleid][v_model], tune_component) || tune_component == 9999)
	{
		new strTitle[128];
		new strContent[2048];
		switch(listitem)
		{
			case 0://tymczasowy
			{
				if(tune_component == 9999)
				{
					new compinslot = GetVehicleComponentInSlot(target_vehicleid, tune_comptype);
					if(compinslot)
					{
						Info(playerid, ""COL_RED"Komponent usunięto tymczasowo.");
						Info(targetid, ""COL_RED"UWAGA! Komponent z twojego pojazdu został usunięty tymczasowo!");
						RemoveVehicleComponent(target_vehicleid, compinslot);
					}
					else Error(playerid, "Brak komponentu do usunięcia.");
				}
				else
				{
					if(pojazd[target_vehicleid][v_tune_data][tune_comptype] == tune_component) 
					{
						AddVehicleComponent(target_vehicleid, tune_component);
						AddVehicleComponent(target_vehicleid, tune_component);
						Info(playerid, ""COL_BLUE"Przywrócono posiadany przez pojazd komponent.");
						Info(targetid, ""COL_BLUE"Przywrócono posiadany komponent!");
					}
					else
					{
						if(tune_component == 1008 || tune_component == 1009 || tune_component == 1010) return Error(playerid, "Tego komponentu nie można testować.");
						AddVehicleComponent(target_vehicleid, tune_component);
						AddVehicleComponent(target_vehicleid, tune_component);
						Info(playerid, ""COL_RED"Komponent zamontowano tymczasowo.");
						Info(targetid, ""COL_RED"UWAGA! Komponent na Twój pojazd został nałożony tymczasowo!");
					}
				}
			}
			case 1://na stałe
			{
				if(pojazd[target_vehicleid][v_tune_data][tune_comptype] == 0 && tune_component == 9999) return Error(playerid, "Pojazd nie posiada komponentu.");
				else if(pojazd[target_vehicleid][v_tune_data][tune_comptype] == tune_component) 
				{
					Error(playerid, "Gracz posiada już ten komponent. Nie możesz wystawić rachunku.");
					if(tune_comptype == 3)
					{
						AddVehicleComponent(target_vehicleid, pojazd[target_vehicleid][v_tune_data][tune_comptype]);
						AddVehicleComponent(target_vehicleid, pojazd[target_vehicleid][v_tune_data][tune_comptype]);
					}
					else AddVehicleComponent(target_vehicleid, pojazd[target_vehicleid][v_tune_data][tune_comptype]);
					return 1;
				}
				Info(playerid, "Zaoferowałeś tuning pojazdu. Gracz teraz podejmuje decyzje...");

				format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Tuning: "COL_ORANGE"%s "COL_RED"«•", typeName);
				format(strContent, 2048, ""COL_WHITE"Mechanik "COL_ROADA"%s"COL_WHITE" wystawił Ci rachunek za tuning "COL_LIME"%s"COL_WHITE" w pojeździe "COL_BLUE"%s"COL_WHITE".", nick(playerid), typeName, GetVehicleName(pojazd[target_vehicleid][v_model]));
				format(strContent, 2048, "%s\n"COL_RED"Jeśli odrzucisz rachunek, tuning nie zostanie zrealizowany.", strContent);
				format(strContent, 2048, "%s\n\n"COL_RED"» "COL_WHITE"Podsumowanie:", strContent);
				format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Pojazd: "COL_BLUE"%s "COL_GREY"(UID: %d)", strContent, GetVehicleName(pojazd[target_vehicleid][v_model]), pojazd[target_vehicleid][v_id]);
				format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Komponent: "COL_LIME"%s", strContent, (tune_component == 9999) ? (""COL_RED"USUŃ KOMPONENT") : (compName));
				format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Typ tuningu: "COL_LIME"%s", strContent, typeName);
				format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Koszt: "COL_GREEN"%d$", strContent, tune_price);
				format(strContent, 2048, "%s\n\n"COL_GREEN"Czy zgadzasz się na tuning i przyjmujesz rachunek?", strContent);
				Dialog_Show(targetid, TUNECONFIRM, DIALOG_STYLE_MSGBOX, strTitle, strContent, "Akceptuj", "Odrzuc");
				//ładowanie cache
				SetPVarInt(targetid, "cache_tune_component", tune_component);
				SetPVarInt(targetid, "cache_tune_comptype", tune_comptype);
				SetPVarInt(targetid, "cache_tune_vehicleid", target_vehicleid);
				SetPVarInt(targetid, "cache_tune_price", tune_price);
				SetPVarInt(targetid, "cache_tune_mechanicid", playerid);
			}
		}
	}
	else Error(playerid, "Komponent nie jest kompatybilny z tym pojazdem.");
	return 1;
}

Dialog:TUNECONFIRM(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new vehicleid = GetPVarInt(playerid, "cache_tune_vehicleid");
	if(!IsPlayerInVehicle(playerid, vehicleid)) return Error(playerid, "Jesteś w niewłaściwym pojeździe.");
	new tune_price = GetPVarInt(playerid, "cache_tune_price");
	if(Money(playerid) < tune_price) return Error(playerid, "Nie posiadasz wystarczająco dużo gotówki.");
	new tune_component = GetPVarInt(playerid, "cache_tune_component");
	new tune_comptype = GetPVarInt(playerid, "cache_tune_comptype");
	new mechanicid = GetPVarInt(playerid, "cache_tune_mechanicid");
	new typeName[64];
	GetVehicleComponentTypeName(GetVehicleComponentType(tune_component), typeName);

	if(IsVehicleUpgradeCompatible(pojazd[vehicleid][v_model], tune_component) || tune_component == 9999)
	{
		if(tune_component == 9999)
		{
			RemoveVehicleComponent(vehicleid, pojazd[vehicleid][v_tune_data][tune_comptype]);
			pojazd[vehicleid][v_tune_data][tune_comptype] = 0;
		}
		else if(tune_comptype == 3)
		{
			AddVehicleComponent(vehicleid, tune_component);
			AddVehicleComponent(vehicleid, tune_component);
			pojazd[vehicleid][v_tune_data][tune_comptype] = tune_component;
		}
		else 
		{
			AddVehicleComponent(vehicleid, tune_component);
			pojazd[vehicleid][v_tune_data][tune_comptype] = tune_component;
		}
		format(pojazd[vehicleid][v_tune_strdata], 256, "");//czyszczenie zmiennej
		for(new x; x < 32; x++)
		{
			format(pojazd[vehicleid][v_tune_strdata], 256, "%s%d ", pojazd[vehicleid][v_tune_strdata], pojazd[vehicleid][v_tune_data][x]);
		}
		//printf("tunedata: %s", pojazd[vehicleid][v_tune_strdata]);
		if(pojazd[vehicleid][v_id] != 0)
		{
			mq_format("UPDATE `pojazdy` SET `tunedata`='%s' WHERE `id`='%d';", pojazd[vehicleid][v_tune_strdata], pojazd[vehicleid][v_id]);
			mq_send("QSaveTune");
		}
		TakeMoney(playerid, tune_price);
		new strNotify[512];
		if(tune_component == 9999)
		{
			format(strNotify, 512, "Usunieto tuning ~y~%s~w~ w pojezdzie ~b~%s~w~.", typeName, GetVehicleName(pojazd[vehicleid][v_model]));
			LeftNotifyShow(playerid, "Sukces!", strNotify, LN_GREEN);
			Info(playerid, ""COL_GREEN"Komponent został na stałe usunięty.");
		}
		else
		{
			format(strNotify, 512, "Stuningowano ~y~%s~w~ w pojezdzie ~b~%s~w~.", typeName, GetVehicleName(pojazd[vehicleid][v_model]));
			LeftNotifyShow(playerid, "Sukces!", strNotify, LN_GREEN);
			Info(playerid, ""COL_GREEN"Komponent został zamontowany na stałe.");
			//--
			GiveFractionMoneyOrScore(F_ROADASSIST, 0, 300);
			//--
		}
		if(gracz[mechanicid][frakcja] == F_ROADASSIST)
		{
			LeftNotifyShow(mechanicid, "Sukces!", "Gracz przyjal oferte tuningu. Pojazd zostal stuningowany. Twoja frakcja otrzymala prowizje za tuning.", LN_GREEN);
		}
	} 
	else Error(playerid, "Komponent nie jest kompatybilny z tym pojazdem.");

	DeletePVar(playerid, "cache_tune_component");
	DeletePVar(playerid, "cache_tune_comptype");
	DeletePVar(playerid, "cache_tune_vehicleid");
	DeletePVar(playerid, "cache_tune_price");
	DeletePVar(playerid, "cache_tune_mechanicid");
	return 1;
}

stock CalcTuneCost(compid, type, vehiclecost)
{
	new Float:wynik;
	new Float:type_proc;
	switch(type)
	{
		case 0: type_proc = 11.0;//% Spoiler
		case 1: type_proc = 7.0;//% Maska
		case 2: type_proc = 6.0;//% Dach
		case 3: type_proc = 4.0;//% Progi
		case 4: type_proc = 9.0;//% Reflektor
		case 5: type_proc = 35.0;//% Nitro
		case 6: type_proc = 10.0;//% Wydech
		case 7: type_proc = 14.0;//% Koła
		case 8: type_proc = 0.5;//% Podbicie basu
		case 9: type_proc = 1000.0;//% Hydraulika
		case 10: type_proc = 13.0;//% Przedni zderzak
		case 11: type_proc = 12.0;//% Tylni zderzak
		case 12: type_proc = 30.3;//% Neon
		default: type_proc = 20.0;//% else
	}
	new Float:comp_calcp = ((10.0*type_proc)+(1300.0*compid))/126.0;
	new Float:wheels_multipiler = 6.3;
	switch(compid)
	{
		//nitro
		case 1008: comp_calcp = 45000.0;//nitro 5x
		case 1009: comp_calcp = 18000.0;//nitro 2x
		case 1010: comp_calcp = 90000.0;//nitro 10x
		//koła
		case 1025: comp_calcp = 1000.0*wheels_multipiler;
		case 1073: comp_calcp = 1100.0*wheels_multipiler;
		case 1074: comp_calcp = 1030.0*wheels_multipiler;
		case 1075: comp_calcp = 980.0*wheels_multipiler;
		case 1076: comp_calcp = 1560.0*wheels_multipiler;
		case 1077: comp_calcp = 1620.0*wheels_multipiler;
		case 1078: comp_calcp = 1200.0*wheels_multipiler;
		case 1079: comp_calcp = 1030.0*wheels_multipiler;
		case 1080: comp_calcp = 900.0*wheels_multipiler;
		case 1081: comp_calcp = 1230.0*wheels_multipiler;
		case 1082: comp_calcp = 820.0*wheels_multipiler;
		case 1083: comp_calcp = 1560.0*wheels_multipiler;
		case 1084: comp_calcp = 1350.0*wheels_multipiler;
		case 1085: comp_calcp = 770.0*wheels_multipiler;
		case 1096: comp_calcp = 1000.0*wheels_multipiler;
		case 1097: comp_calcp = 620.0*wheels_multipiler;
		case 1098: comp_calcp = 1140.0*wheels_multipiler;
	}
	wynik = (type_proc/100.0)*vehiclecost;
	wynik /= 35.0;
	wynik += comp_calcp;
	if(type == 12)//neony
	{
		wynik = (type_proc/100.0)*vehiclecost;
	}
	return floatround(wynik);
}
//****************************MAFIA PALIWOWA***************************************************



CMD:napad(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_MAFIA) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	if(attack[att_status] != 0) return Error(playerid, "W tym momencie trwa już napad.");
	new time_block = serwer[attack_block_timestamp]-serwer[time_timestamp];
	if(time_block > 0)
	{
		new trash;
		new hh, mm, ss;
		SecToTime(time_block, trash, hh, mm, ss);
		new strError[144];
		format(strError, 144, "Napad będzie można wykonać za %d godz, %d minut i %d sekund", hh, mm, ss);
		Error(playerid, strError);
		return 1;
	}
	new pin, type_fuel[64], litry;
	new strNapadInfo[3400];
	if(sscanf(params,"dds[64]", pin, litry, type_fuel)) 
	{
		SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /napad [pin od lidera] [ilość litrów] [paliwo: on/pb]");
		format(strNapadInfo, 3400, """Aby rozpocząć napad na stacje benzynową, użyj komendy:");
		format(strNapadInfo, 3400, "%s\n"COL_WHITE"/napad "COL_ORANGE"[PIN] "COL_GREEN"[litry] "COL_BLUE"[paliwo: "COL_LIME"on"COL_BLUE"/"COL_LIME"pb"COL_BLUE"]", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n"COL_ORANGE"[PIN] - Dostęp do kodu PIN posiada szefostwo frakcji. Kod zmienia się", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n"COL_ORANGE"po każdym napadzie. Pozwala to kontrolować napady przez szefostwo frakcji.", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n"COL_GREEN"[litry] - Ile litrów chcesz wykraść ze stacji benzynowej. Aktualny przelicznik", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n"COL_GREEN"to 1 litr = 0.15 sekundy dłużej. Na całkowity czas napadu wpływa także", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n"COL_GREEN"odległość od baz służb porządkowych (SG i Policji). Minimalna wartość to "COL_RED"100L"COL_GREEN".", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n"COL_BLUE"[paliwo: on/pb] - Jaki typ paliwa chcesz wykraść. Wyjaśnienie skrótów: ", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n"COL_LIME"on "COL_BLUE"- olej napędowy (ropa). ", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n"COL_LIME"pb "COL_BLUE"- benzyna. ", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n"COL_WHITE"Przykład: /napad "COL_ORANGE"1234 "COL_GREEN"300 "COL_LIME"on", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n"COL_EASY"Aby zainicjować napad, muszą zostać spełnione następujące warunki:", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n- Musisz znajdować się w pojeździe frakcyjnym z naczepą.", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n- Ilość osób ze służb porządkowych na duty musi być większa niż 3.", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n- Ilość osób ze służb porządkowych na duty nie może być mniejsza niż w mafii.", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n- Musisz znajdować się na terenie stacji benzynowej.", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n"COL_WHITE"Zasady:", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n1. BW jest normalnie aktywne. Po BW można dalej kontunuować atak/obronę.", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n2. Napad uznaje się za przegrany jeśli: ", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n* wszyscy z mafii na terenie bitwy będą mieli BW.", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n* nie uda się ewakuowac naczepy mafii paliwowej przed końcem czasu.", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n* mafia opusci terenie bitwy.", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n3. Napad uznaje się za wygrany jeśli: ", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n* naczepa mafii paliwowej oddali się wystarczająco daleko od miejsca napadu przed końcem czasu.", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n4. Jeśli mafia wygra napad skrypt ucina rozgrywkę(pościg) teleportując mafię do bazy frakcyjnej.", strNapadInfo);
		MessageGUIEx(playerid,  ""COL_RED"•» "COL_WHITE"Informacje dotyczące napadu "COL_RED"«•",  strNapadInfo);
		return 1;
	}
	format(strNapadInfo, 3400, "");
	if(litry < 400) return Error(playerid, "Minimalna wartość paliwa to 400L.");
	if(litry > 5000) return Error(playerid, "Maksymalna wartość paliwa to 5000L.");
	new vehid = GetPlayerVehicleID(playerid);
	if(!(pojazd[vehid][v_owner_type] == VEHICLE_FRACTION && pojazd[vehid][v_owner] == F_MAFIA)) return Error(playerid, "Nie jesteś w pojeździe frakcyjnym.");
	if(pojazd[vehid][v_model] != 515) return Error(playerid, "Nie siedzisz w pojeździe Roadtrain.");
	new trailerid = GetVehicleTrailer(vehid);
	if(trailerid == 0) return Error(playerid, "Brak cysterny.");
	if(!(pojazd[trailerid][v_owner_type] == VEHICLE_FRACTION && pojazd[trailerid][v_owner] == F_MAFIA)) return Error(playerid, "Naczepa nie należy do Twojej frakcji.");
	new int_fuel_type = -1;
	if(compare("on", type_fuel)) int_fuel_type = F_ON;
	else if(compare("pb", type_fuel)) int_fuel_type = F_PB;
	if(int_fuel_type == -1) return Error(playerid, "Niepoprawny typ paliwa.");
	if(pin == attack[att_pin])
	{
		new f_group_def = FractionDutyWorkersCount(F_BORDERGUARD)+FractionDutyWorkersCount(F_POLICE);
		new f_group_attack = FractionDutyWorkersCount(F_MAFIA);
		if(gracz[playerid][admin_duty] < 4)
		{
			if(f_group_def < 3) return Error(playerid, "Niewystarczająca ilość funkcjonariuszy SG/Policji na służbie.");
			if(f_group_def < f_group_attack) return Error(playerid, "Funkcjonariuszy jest mniej od mafii.");
		}
		new select_fs = -1;
		for(new s; s < MAX_FUELSTATIONS; s++)
		{
			if(IsPlayerInRangeOfPoint(playerid, 35.0, fuel_stations[s][fs_dX], fuel_stations[s][fs_dY], fuel_stations[s][fs_dZ]))
			{
				select_fs = s;
				break;
			}
		}
		if(select_fs == -1) return Error(playerid, "Musisz znajdować się na stacji benzynowej.");
		//rozpoczynanie napadu, wszystkie warunki spełnione
		const cancel_time = 30;
		new Float:distance_poli = GetDistanceBetweenPoints(fuel_stations[select_fs][fs_dX], fuel_stations[select_fs][fs_dY], fuel_stations[select_fs][fs_dZ], fractions[F_POLICE][fr_dutyX], fractions[F_POLICE][fr_dutyY], fractions[F_POLICE][fr_dutyZ]);
		new Float:calc_napadtime = (float(litry)*0.15)+(distance_poli/16.0)+float(ATTACK_EXIT_TIME);
		new result_napadtime = floatround(calc_napadtime);
		new t_trash, t_min, t_sec;
		SecToTime(result_napadtime, t_trash, t_trash, t_min, t_sec);
		format(strNapadInfo, 3400, ""COL_LIME"Trwa inicjacja napadu, czy chcesz anulować?");
		format(strNapadInfo, 3400, "%s\n"COL_RED"•» "COL_EASY"Podsumowanie:", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n"COL_ORANGE"» "COL_EASY"Stacja benzynowa: "COL_WHITE"%s", strNapadInfo, GetFuelStationName(fuel_stations[select_fs][fs_concern]));
		format(strNapadInfo, 3400, "%s\n"COL_ORANGE"» "COL_EASY"Aktualny stan stron: ", strNapadInfo);
		format(strNapadInfo, 3400, "%s\n"COL_RED"• "COL_ORANGE"Mafia paliwowa: "COL_WHITE"%d ludzi", strNapadInfo, f_group_attack);
		format(strNapadInfo, 3400, "%s\n"COL_RED"• "COL_BLUE"Policja i straż graniczna: "COL_WHITE"%d ludzi", strNapadInfo, f_group_def);
		format(strNapadInfo, 3400, "%s\n"COL_ORANGE"» "COL_EASY"Typ paliwa: "COL_WHITE"%s", strNapadInfo, (int_fuel_type == 1) ? ("ON (olej napędowy)") : ("PB (benzyna)"));
		format(strNapadInfo, 3400, "%s\n"COL_ORANGE"» "COL_EASY"lość paliwa: "COL_WHITE"%d litrów", strNapadInfo, litry);
		format(strNapadInfo, 3400, "%s\n"COL_ORANGE"» "COL_EASY"Całkowity czas trwania napadu: "COL_WHITE"%d minut, %d sekund.", strNapadInfo, t_min, t_sec);
		format(strNapadInfo, 3400, "%s\n"COL_RED"Napad rozpocznie się za %d sekund, aby anulować wciśnij poniższy przycisk.", strNapadInfo, cancel_time);
		format(strNapadInfo, 3400, "%s\n"COL_RED"Okno zamknie się AUTOMATYCZNIE!", strNapadInfo);
		Dialog_Show(playerid, ANULUJNAPAD, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_WHITE"Potwierdzenie "COL_RED"«•", strNapadInfo, "Anuluj", "");
		attack[att_status] = 1;
		attack[att_time] = result_napadtime;
		attack[att_fuelcount] = litry;
		attack[att_fuelid] = int_fuel_type;
		attack[att_stationid] = select_fs;
		attack[att_starttime] = cancel_time;
		attack[att_playeruid] = gracz[playerid][UID];
		attack[att_trailerid] = trailerid;
		GetPlayerName(playerid, attack[att_playernick], 24);
	}
	else Error(playerid, "Nieprawidłowy PIN. Poproś lidera/v-ce lidera aby podał PIN.");
	return 1;
}

Dialog:ANULUJNAPAD(playerid, response, listitem, inputtext[])
{
	attack[att_status] = 2;
	format(attack[att_simpletext_def], 512, "~y~%s~w~ anulowal napad na stacje ~y~%s~w~.", attack[att_playernick], GetFuelStationName(fuel_stations[attack[att_stationid]][fs_concern]));
	serwer[att_dontchangepin] = true;
	return 1;
}

stock BattleBlock(playerid)
{
	if(attack[att_status] == 0) return 0;
	new s = attack[att_stationid];
	if(IsPlayerInRangeOfPoint(playerid, ATTACK_BATTLE_RANGE, fuel_stations[s][fs_dX], fuel_stations[s][fs_dY], fuel_stations[s][fs_dZ])) return 1;
	return 0;
}

stock BattleBlockEx(playerid, Float:brange)
{
	if(attack[att_status] == 0) return 0;
	new s = attack[att_stationid];
	if(IsPlayerInRangeOfPoint(playerid, brange, fuel_stations[s][fs_dX], fuel_stations[s][fs_dY], fuel_stations[s][fs_dZ]) && IsPlayerOnDutyFraction(playerid) && ( gracz[playerid][frakcja] == F_MAFIA || gracz[playerid][frakcja] == F_POLICE)) return 1;
	return 0;
}

stock ClearNapadRAM()
{
	new lastpin = attack[att_pin];
	for(new att_data:att_x; att_x < att_data; att_x++)
	{
		attack[att_x] = 0;
	}
	if(serwer[att_dontchangepin]) attack[att_pin] = lastpin;
	else
	{
		attack[att_pin] = MRandRange(1000, 9999);
		serwer[attack_block_timestamp] = serwer[time_timestamp]+(60*60*1);//1 godzina
	}
	serwer[att_dontchangepin] = false;
	return 1;
}

task Process_NapadMafia()
{
	if(attack[att_status] == 0) return 1;
	static stationid;
	switch(attack[att_status])
	{
		case 1://trwa odliczanie do rozpoczęcia
		{
			format(attack[att_simpletext_def], 512, "~y~%s~w~ inicjuje napad. Za ~y~%d~w~ sekund rozpocznie sie napad na stacje ~y~%s~w~. Jesli ten czas uplynie ~r~sluzby porzadkowe zostana zaalarmowane~w~. Osoba inicjujaca napad moze jeszcze przerwac odliczanie.", attack[att_playernick], attack[att_starttime], GetFuelStationName(fuel_stations[attack[att_stationid]][fs_concern]));
			attack[att_temp_count_m_all] = 0;
			//-------------------------------PĘTLA MAFIA START
			for(new p = PlayerPoolSize(); p != -1; p--)
			{
				if(!gracz[p][loggedin] || !gracz[p][spawned]) continue;
				if(gracz[p][frakcja] != F_MAFIA) continue;
				if(!IsPlayerOnDutyFraction(p)) continue;
				SetSimpleTextTD(p, attack[att_simpletext_def], 2);
				attack[att_temp_count_m_all]++;
			}
			//-------------------------------PĘTLA MAFIA END
			attack[att_starttime]--;
			if(attack[att_starttime] <= 0)
			{
				attack[att_status] = 3;
			}
		}
		case 2://anulowanie napadu
		{
			//-------------------------------PĘTLA MAFIA START
			for(new p = PlayerPoolSize(); p != -1; p--)
			{
				if(!gracz[p][loggedin] || !gracz[p][spawned]) continue;
				if(!IsPlayerOnDutyFraction(p)) continue;
				if(gracz[p][frakcja] == F_MAFIA)
				{
					SetSimpleTextTD(p, attack[att_simpletext_def], 10);
				}
				else if(gracz[p][frakcja] == F_POLICE || gracz[p][frakcja] == F_BORDERGUARD)
				{
					SetSimpleTextTD(p, attack[att_simpletext_att], 10);
				}
				DisablePlayerCheckpoint(p);
			}
			//-------------------------------PĘTLA MAFIA END
			ClearNapadRAM();//attack[att_status] = 0;
		}
		case 3://trwa obrona - pompowanie paliwa
		{
			//attack[att_temp_count_m_bw]
			//attack[att_temp_count_m_all], attack[att_temp_count_m_bw]
			stationid = attack[att_stationid];//skrót
			format(attack[att_simpletext_def], 512, "Trwa pompowanie paliwa ze stacji ~y~%s~w~. Przetrwaj ~y~%d sekund~w~. Jesli wszyscy czlonkowie beda mieli ~r~BW ~w~(~r~%d~w~/~g~%d~w~) lub opuszcza teren bitwy - napad uznaje sie za ~r~przegrany~w~. Sluzby porzadkowe zostaly ~r~zaalarmowane~w~.", GetFuelStationName(fuel_stations[attack[att_stationid]][fs_concern]), attack[att_time]-ATTACK_EXIT_TIME, attack[att_temp_count_m_bw], attack[att_temp_count_m_all]);
			format(attack[att_simpletext_att], 512, "Mafia w tym momencie pompuje paliwo. Zajmie to ~y~%d sekund~w~. Jesli wszyscy czlonkowie mafii beda mieli BW na polu bitwy (~g~%d~w~/~r~%d~w~) - napad ~g~zostanie przerwany~w~. Jesli nie uda sie powstrzymac mafii na tym etapie, bedzie jeszcze szansa to zrobic na etapie ucieczki.", attack[att_time]-ATTACK_EXIT_TIME, attack[att_temp_count_m_bw], attack[att_temp_count_m_all]);
			new zoneName[64];
			Get2DZone(fuel_stations[stationid][fs_dX], fuel_stations[stationid][fs_dY], zoneName, 64);
			//-------------------------------PĘTLA MAFIA POLICJA SG START
			attack[att_temp_count_m_bw] = 0;
			attack[att_temp_count_m_all] = 0;
			for(new p = PlayerPoolSize(); p != -1; p--)
			{
				if(!gracz[p][loggedin] || !gracz[p][spawned]) continue;
				if(!IsPlayerOnDutyFraction(p)) continue;
				if(gracz[p][frakcja] == F_MAFIA)//MAFIA
				{
					//operacje na mafiozach na terenie bitwy
					if(IsPlayerInRangeOfPoint(p, ATTACK_BATTLE_RANGE, fuel_stations[stationid][fs_dX], fuel_stations[stationid][fs_dY], fuel_stations[stationid][fs_dZ]))
					{
						if(IsPlayerInAnyVehicle(p)) SetSimpleTextTD(p, "Jeszcze ~r~zbyt wczesnie na ucieczke~w~. ~y~Opusc pojazd~w~ i utrzymuj pozycje zywy!", 2);
						else SetSimpleTextTD(p, attack[att_simpletext_def], 2);
						if(!IsPlayerAFK(p)) attack[att_temp_count_m_all]++;
						if(gracz[p][bw_time] > 0) attack[att_temp_count_m_bw]++;
						DisablePlayerCheckpoint(p);
					}
					else
					{
						format(temp_string, 512, "Trwa napad na stacje ~y~%s~w~ w ~y~%s~w~. Pozostalo ~y~%d sekund~w~. Pomoz swoim kolegom utrzymac pozycje, miejsce zostalo ~y~oznaczone na mapie~w~.", GetFuelStationName(fuel_stations[attack[att_stationid]][fs_concern]), zoneName, attack[att_time]-ATTACK_EXIT_TIME);
						SetSimpleTextTD(p, temp_string, 2);
						DisablePlayerCheckpoint(p);
						SetPlayerCheckpoint(p, fuel_stations[stationid][fs_dX], fuel_stations[stationid][fs_dY], fuel_stations[stationid][fs_dZ], 1.0);
					}
					//ukrywanie gui dla inicjatora napadu
					if(attack[att_playeruid] == gracz[p][UID])
					{
						Dialog_Close(p);
						attack[att_playeruid] = 0;
						RemovePlayerFromVehicle(p);//bo siedzi pewnie w rdt
					}
				}
				else if(gracz[p][frakcja] == F_POLICE || gracz[p][frakcja] == F_BORDERGUARD)
				{
					//operacje na służbach porządkowych na terenie bitwy
					if(IsPlayerInRangeOfPoint(p, ATTACK_BATTLE_RANGE+50.0, fuel_stations[stationid][fs_dX], fuel_stations[stationid][fs_dY], fuel_stations[stationid][fs_dZ]))
					{
						SetSimpleTextTD(p, attack[att_simpletext_att], 2);
						DisablePlayerCheckpoint(p);
					}
					else
					{
						format(temp_string, 512, "Trwa napad na stacje ~y~%s~w~ w ~y~%s~w~. Pozostalo ~y~%d sekund~w~. Jedz na miejsce i powstrzymaj mafie (oznaczone na mapie):~n~- doprowadz aby mafia miala BW na terenie bitwy.~n~- nie pozwol na ucieczke przed koncem czasu.", GetFuelStationName(fuel_stations[attack[att_stationid]][fs_concern]), zoneName, attack[att_time]);
						SetSimpleTextTD(p, temp_string, 2);
						DisablePlayerCheckpoint(p);
						SetPlayerCheckpoint(p, fuel_stations[stationid][fs_dX], fuel_stations[stationid][fs_dY], fuel_stations[stationid][fs_dZ], 1.0);
					}
				}
			}
			//------------------------------PĘTLA MAFIA POLICJA SG END
			new Float:vPos[3];
			GetVehiclePos(attack[att_trailerid], vPos[0], vPos[1], vPos[2]);
			new Float:trailer_distance = GetDistanceBetweenPoints(fuel_stations[stationid][fs_dX], fuel_stations[stationid][fs_dY], fuel_stations[stationid][fs_dZ], vPos[0], vPos[1], vPos[2]);
			if(attack[att_temp_count_m_all] == 0)//mafiozi uciekli z miejsca napadu (napad przegrany)
			{
				GiveFractionMoneyOrScore(F_POLICE, 5, 0);
				GiveFractionMoneyOrScore(F_BORDERGUARD, 5, 0);
				attack[att_status] = 2;
				format(attack[att_simpletext_def], 512, "~r~PRZEGRANA!~w~ Wszyscy czlonkowie uciekli z pola bitwy. Napad ~r~nieudany~w~!");
				format(attack[att_simpletext_att], 512, "~g~WYGRANA!~w~ Mafia uciekla z pola bitwy. ~g~Napad przerwany~w~! Na konto frakcji trafia ~y~5 score~w~!");
			}
			else if(attack[att_temp_count_m_all] == attack[att_temp_count_m_bw])//wszyscy na polu bitwy mają BW? Przegrana!
			{
				GiveFractionMoneyOrScore(F_POLICE, 20, 0);
				GiveFractionMoneyOrScore(F_BORDERGUARD, 20, 0);
				GiveFractionMoneyOrScore(F_MAFIA, 5, 0);
				attack[att_status] = 2;
				format(attack[att_simpletext_def], 512, "~r~PRZEGRANA!~w~ Wszyscy na polu bitwy polegli (~y~%d osob~w~). Napad ~r~nieudany~w~!", attack[att_temp_count_m_bw]);
				format(attack[att_simpletext_att], 512, "~g~WYGRANA!~w~ Wszyscy czlonkowie mafii maja BW. ~g~Napad przerwany~w~! Na konto frakcji trafia ~y~20 score~w~!");
			}
			else if(trailer_distance > ATTACK_BATTLE_RANGE)
			{
				GiveFractionMoneyOrScore(F_POLICE, 5, 0);
				GiveFractionMoneyOrScore(F_BORDERGUARD, 5, 0);
				attack[att_status] = 2;
				format(attack[att_simpletext_def], 512, "~r~PRZEGRANA!~w~ Cysterna zostala zbyt wczesnie ewakuowana z pola bitwy. Napad ~r~nieudany~w~!");
				format(attack[att_simpletext_att], 512, "~g~WYGRANA!~w~ Mafia zbyt wczesnie ewakuowala cysterne. ~g~Napad przerwany~w~! Na konto frakcji trafia ~y~5 score~w~!");
			}
			attack[att_time]--;
			if(attack[att_time] <= ATTACK_EXIT_TIME)//4 min
			{
				attack[att_status] = 4;
			}
		}
		case 4://trwa ewakuacja/ucieczka
		{
			stationid = attack[att_stationid];//skrót
			new Float:vPos[3];
			GetVehiclePos(attack[att_trailerid], vPos[0], vPos[1], vPos[2]);
			new Float:trailer_distance = GetDistanceBetweenPoints(fuel_stations[stationid][fs_dX], fuel_stations[stationid][fs_dY], fuel_stations[stationid][fs_dZ], vPos[0], vPos[1], vPos[2]);
			new procent_ucieczki;
			if(GetDistanceBetweenPoints(fractions[F_MAFIA][fr_dutyX], fractions[F_MAFIA][fr_dutyY], fractions[F_MAFIA][fr_dutyZ], vPos[0], vPos[1], vPos[2]) < 150.0)
			{
				procent_ucieczki = 0;
			}
			else
			{
				procent_ucieczki = procent(trailer_distance, ATTACK_EXIT_RANGE);
			}
			format(attack[att_simpletext_def], 512, "Paliwo wypompowane. Mafia musi ewakuowac cysterne z miejsca napadu (jak najdalej to mozliwe). Pozostalo ~y~%d sekund~w~. Powodzenie ucieczki: ~y~%d%%~w~.", attack[att_time], procent_ucieczki);
			format(attack[att_simpletext_att], 512, "Mafia paliwowa ~r~probuje uciec~w~! Powstrzymaj ja przed koncem czasu. ~y~Nie dopusc aby cysterna oddalila sie wystarczajaco daleko od miejsca napadu~w~. Pozostalo ~y~%d sekund~w~. Powodzenie ucieczki: ~r~%d%%~w~.", attack[att_time], procent_ucieczki);
			for(new p = PlayerPoolSize(); p != -1; p--)
			{
				if(!gracz[p][loggedin] || !gracz[p][spawned]) continue;
				if(!IsPlayerOnDutyFraction(p)) continue;
				if(gracz[p][frakcja] == F_MAFIA)//MAFIA
				{
					//operacje na mafiozach na terenie bitwy
					SetSimpleTextTD(p, attack[att_simpletext_def], 2);
				}
				else if(gracz[p][frakcja] == F_POLICE || gracz[p][frakcja] == F_BORDERGUARD)
				{
					//operacje na służbach porządkowych na terenie bitwy
					SetSimpleTextTD(p, attack[att_simpletext_att], 2);
				}
			}
			attack[att_time]--;
			if(procent_ucieczki >= 100)
			{
				attack[att_status] = 2;
				format(attack[att_simpletext_att], 512, "~r~PRZEGRANA!~w~ Mafia paliwowa ~y~oddalila cysterne wystarczajaco daleko od miejsca napadu przed koncem czasu~w~. ~r~Nie udalo sie powstrzymac mafii~w~.");
				switch(attack[att_fuelid])
				{
					case F_PB:
					{
						fractions[F_MAFIA][fr_intval2] += attack[att_fuelcount];
						format(attack[att_simpletext_def], 512, "~g~WYGRANA!~w~ Cysterna zostala ewakuowana. Napad ~g~udany~w~! Zdobyto ~y~%d litrow~w~ benzyny. Aktualny stan w magazynie: ~y~%d litrow~w~.", attack[att_fuelcount], fractions[F_MAFIA][fr_intval2]);
					}
					case F_ON:
					{
						fractions[F_MAFIA][fr_intval1] += attack[att_fuelcount];
						format(attack[att_simpletext_def], 512, "~g~WYGRANA!~w~ Cysterna zostala ewakuowana. Napad ~g~udany~w~! Zdobyto ~y~%d litrow~w~ oleju napedowego. Aktualny stan w magazynie: ~y~%d litrow~w~.", attack[att_fuelcount], fractions[F_MAFIA][fr_intval1]);
					}
				}
				GiveFractionMoneyOrScore(F_POLICE, 5, 0);
				GiveFractionMoneyOrScore(F_BORDERGUARD, 5, 0);
				GiveFractionMoneyOrScore(F_MAFIA, 25, 0);
				SaveFractionAddValues(F_MAFIA);//save intvals
				//teleportacja do bazy mafii:
				for(new p = PlayerPoolSize(); p != -1; p--)
				{
					if(!gracz[p][loggedin] || !gracz[p][spawned]) continue;
					if(!IsPlayerOnDutyFraction(p)) continue;
					if(gracz[p][frakcja] == F_MAFIA)//MAFIA
					{
						if(IsPlayerInRangeOfPoint(p, ATTACK_BATTLE_RANGE, vPos[0], vPos[1], vPos[2]))
						{
							new vid = GetPlayerVehicleID(p);
							if(vid != 0) RespawnVehicle(vid, true);
							Force_FreezeLoadObject(p, fractions[F_MAFIA][fr_dutyX], fractions[F_MAFIA][fr_dutyY], fractions[F_MAFIA][fr_dutyZ]);
							LeftNotifyShow(p, "info", "Skrypt ucina rozgrywke (ucieczke), poniewaz osiagnieto wynik napadu. Zostales teleportowany do bazy.", LN_GREY, 10);
						}
					}
				}
				RespawnVehicle(attack[att_trailerid], true);//respawn naczepy
			}
			else if(attack[att_time] <= 0)
			{
				GiveFractionMoneyOrScore(F_POLICE, 20, 0);
				GiveFractionMoneyOrScore(F_BORDERGUARD, 20, 0);
				GiveFractionMoneyOrScore(F_MAFIA, 5, 0);
				attack[att_status] = 2;
				format(attack[att_simpletext_def], 512, "~r~PRZEGRANA!~w~ Nie udalo sie ewakuowac cysterny przed koncem czasu. Napad ~r~nieudany~w~!");
				format(attack[att_simpletext_att], 512, "~g~WYGRANA!~w~ Nie udalo sie mafii paliwowej oddalic cysterne od miejsca napadu wystarczajco daleko przed koncem czasu. ~g~Napad przerwany~w~! Na konto frakcji trafia ~y~20 score~w~!");
			}
		}
	}
	return 1;
}

CMD:mgetpin(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_MAFIA) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	if(gracz[playerid][frakcja_permlvl] == 0) return Error(playerid, "Brak uprawnień.");
	new strTemp[512];
	format(strTemp, 512, ""COL_WHITE"Kod PIN do napadów: "COL_RED"%d", attack[att_pin]);
	format(strTemp, 512, "%s\n"COL_GREY"Użyj: /napad %d [litry] [paliwo: on/pb]\n", strTemp, attack[att_pin]);
	format(strTemp, 512, "%s\n{8B8B8B}• każdy pracownik może wykonać napad znając kod PIN.", strTemp);
	format(strTemp, 512, "%s\n{8B8B8B}• kod PIN zmienia się automatycznie po każdym napadzie i restarcie serwera.", strTemp);
	format(strTemp, 512, "%s\n{8B8B8B}• to szefostwo frakcji odpowiada za swoich pracowników.", strTemp);
	SendClientMessageEx(playerid, -1, ""COL_GREY"UŻYJ: /napad %d [ilość litrów] [paliwo: on/pb]", attack[att_pin]);
	MessageGUIEx(playerid, ""COL_RED"•» "COL_WHITE"Kod PIN "COL_RED"«•", strTemp);
	return 1;
}

CMD:mfuelstat(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_MAFIA) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new strFuelInfo[1024];
	format(strFuelInfo, 1024, ""COL_RED"•» "COL_WHITE"Aktualny stan magazynu:");
	format(strFuelInfo, 1024, "%s\n{7A7A7A}[ON] "COL_WHITE"Olej napędowy: {7A7A7A}%d litrów "COL_GREEN"[%d$ za litr]", strFuelInfo, fractions[F_MAFIA][fr_intval1], fractions[F_MAFIA][fr_intval3]);
	format(strFuelInfo, 1024, "%s\n{19BD00}[PB] "COL_WHITE"Benzyna: {19BD00}%d litrów "COL_GREEN"[%d$ za litr]\n", strFuelInfo, fractions[F_MAFIA][fr_intval2], fractions[F_MAFIA][fr_intval4]);
	format(strFuelInfo, 1024, "%s\n{8B8B8B}• aby zatankować komuś pojazd użyj komendy "COL_WHITE"/mtank{8B8B8B}.", strFuelInfo);
	format(strFuelInfo, 1024, "%s\n{8B8B8B}• cenę za litr paliwa ustala szefostwo frakcji.", strFuelInfo);
	format(strFuelInfo, 1024, "%s\n{8B8B8B}• pieniądze ze sprzedanego paliwa trafiają na konto frakcji.", strFuelInfo);
	format(strFuelInfo, 1024, "%s\n{8B8B8B}• nie można tankować na terenie bazy frakcji i w pobliżu.", strFuelInfo);
	format(strFuelInfo, 1024, "%s\n{8B8B8B}• tankować można będąc przy cysternie mafii paliwowej (naczepa).", strFuelInfo);
	MessageGUIEx(playerid, ""COL_RED"•» "COL_WHITE"Stan paliwa "COL_RED"«•", strFuelInfo);
	return 1;
}

CMD:msetprices(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_MAFIA) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	if(gracz[playerid][frakcja_permlvl] == 0) return Error(playerid, "Brak uprawnień.");
	new strFuelPrices[512];
	format(strFuelPrices, 512, "Rodzaj paliwa\tCena");
	format(strFuelPrices, 512, "%s\n{7A7A7A}[ON] Olej napędowy\t"COL_GREEN"%d$ za litr", strFuelPrices, fractions[F_MAFIA][fr_intval3]);
	format(strFuelPrices, 512, "%s\n{19BD00}[PB] Benzyna\t"COL_GREEN"%d$ za litr", strFuelPrices, fractions[F_MAFIA][fr_intval4]);
	Dialog_Show(playerid, MFUELPRICE, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_WHITE"Zmień ceny za paliwo "COL_RED"«•", strFuelPrices, "Zmien", "Anuluj");
	return 1;
}

Dialog:MFUELPRICE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	SetPVarInt(playerid, "cache_fuelsetprice", listitem);
	new strDialog[256];
	switch(listitem)
	{
		case 0: format(strDialog, 256, ""COL_WHITE"Typ paliwa: {7A7A7A}[ON] Olej napędowy "COL_EASY"(%d$ za litr)", fractions[F_MAFIA][fr_intval3]);
		case 1: format(strDialog, 256, ""COL_WHITE"Typ paliwa: {19BD00}[PB] Benzyna "COL_EASY"(%d$ za litr)", fractions[F_MAFIA][fr_intval4]);
	}
	format(strDialog, 256, "%s\n"COL_WHITE"Dostępny przedział cenowy: "COL_GREEN"$0 - 50$.", strDialog);
	format(strDialog, 256, "%s\n\n"COL_WHITE"Wprowadź cenę poniżej:", strDialog);
	Dialog_Show(playerid, MFUELPRICESET, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_WHITE"Wprowadź cene "COL_RED"«•", strDialog, "Zatwierdz", "Anuluj");
	return 1;
}

Dialog:MFUELPRICESET(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new fueltype = GetPVarInt(playerid, "cache_fuelsetprice");
	new value = strval(inputtext);
	if(value < 0) return Error(playerid, "Wartość nie może być mniejsza niż 0$.");
	if(value > 50) return Error(playerid, "Wartość nie może być większa niż 50$.");
	new strFmsg[144];
	switch(fueltype)
	{
		case 0: 
		{
			fractions[F_MAFIA][fr_intval3] = value;
			format(strFmsg, 144, "Zmieniono stawkę: {7A7A7A}[ON] Olej napędowy "COL_EASY"%d$ za litr"COL_FMSG".", fractions[F_MAFIA][fr_intval3]);
		}
		case 1:
		{
			fractions[F_MAFIA][fr_intval4] = value;
			format(strFmsg, 144, "Zmieniono stawkę: {19BD00}[PB] Benzyna "COL_EASY"%d$ za litr"COL_FMSG".", fractions[F_MAFIA][fr_intval4]);
		}
	}
	SendFractionMessage(F_MAFIA, strFmsg);
	SaveFractionAddValues(F_MAFIA);//save intvals
	return 1;
}

CMD:mtank(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_MAFIA) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	if(IsPlayerInRangeOfPoint(playerid, 600.0, fractions[F_MAFIA][fr_dutyX], fractions[F_MAFIA][fr_dutyY], fractions[F_MAFIA][fr_dutyZ])) return Error(playerid, "Jesteś zbyt blisko bazy frakcji.");
	if(IsPlayerInAnyVehicle(playerid)) return Error(playerid, "Nie możesz być w pojeździe.");
	new find_trailer;
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		if(pojazd[v][v_model] == 0) continue;
		if(pojazd[v][v_owner_type] != VEHICLE_FRACTION) continue;
		if(pojazd[v][v_owner] != F_MAFIA) continue;
		if(pojazd[v][v_model] == 584)
		{
			new Float:vPos[3];
			GetVehiclePos(v, vPos[0], vPos[1], vPos[2]);
			if(IsPlayerInRangeOfPoint(playerid, 15.0, vPos[0], vPos[1], vPos[2]))
			{
				find_trailer = v;
				break;
			}
		}
	}
	if(find_trailer == 0) return Error(playerid, "Musisz stać przy cysternie.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /mtank [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	new target_vehicleid = GetPlayerVehicleID(targetid);
	if(target_vehicleid == 0) return Error(playerid, "Gracz musi być w pojeździe.");
	if(pojazd[target_vehicleid][v_owner_type] == VEHICLE_PLAYER || pojazd[target_vehicleid][v_owner_type] == VEHICLE_BUSINESS)
	{
		new engine, lights, alarm, doors, bonnet, boot, objective;
		GetVehicleParamsEx(target_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
		SetPVarInt(playerid, "cache_mtank_targetid", targetid);
		SetPVarInt(playerid, "cache_mtank_vehicleid", target_vehicleid);
		new fuel_type = GetVehicleFuelType(pojazd[target_vehicleid][v_model]);
		new fuel_size = GetVehicleFuelSize(pojazd[target_vehicleid][v_model]);
		new Float:fuel_actual = pojazd[target_vehicleid][v_paliwo];
		new strMtank[1024];
		format(strMtank, 1024, ""COL_RED"•» "COL_WHITE"Informacje:");
		format(strMtank, 1024, "%s\n"COL_ORANGE"» "COL_WHITE"Gracz: "COL_EASY"%s(%d)", strMtank, nick(targetid), targetid);
		format(strMtank, 1024, "%s\n"COL_ORANGE"» "COL_WHITE"Pojazd: "COL_EASY"%s(%d)", strMtank, GetVehicleName(pojazd[target_vehicleid][v_model]), pojazd[target_vehicleid][v_id]);
		format(strMtank, 1024, "%s\n"COL_ORANGE"» "COL_WHITE"Typ paliwa: "COL_EASY"%s", strMtank, (fuel_type == F_ON) ? ("Olej napędowy") : ("Benzyna"));
		format(strMtank, 1024, "%s\n"COL_ORANGE"» "COL_WHITE"Stawka za litr: "COL_GREEN"%d$", strMtank, (fuel_type == F_ON) ? (fractions[F_MAFIA][fr_intval3]) : (fractions[F_MAFIA][fr_intval4]));
		format(strMtank, 1024, "%s\n"COL_ORANGE"» "COL_WHITE"Aktualny stan zbiornika gracza: "COL_RED"%d"COL_WHITE"/"COL_GREEN"%d "COL_WHITE"litrów.", strMtank, floatround(fuel_actual), fuel_size);
		format(strMtank, 1024, "%s\n"COL_ORANGE"» "COL_WHITE"Stan magazynu: "COL_ORANGE"%d litrów", strMtank, (fuel_type == F_ON) ? (fractions[F_MAFIA][fr_intval1]) : (fractions[F_MAFIA][fr_intval2]));
		format(strMtank, 1024, "%s\n\n{8B8B8B}• maksymalna wartość to 1000L.", strMtank);
		format(strMtank, 1024, "%s\n{8B8B8B}• minimalna wartość to 10L.", strMtank);
		format(strMtank, 1024, "%s\n{8B8B8B}• wpisz "COL_WHITE"full{8B8B8B} aby zatankować do pełna.", strMtank);
		format(strMtank, 1024, "%s\n\n"COL_RED"Ile litrów paliwa chcesz oferować?", strMtank);
		Dialog_Show(playerid, MTANKSET, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_WHITE"Ile sprzedać? "COL_RED"«•", strMtank, "Oferuj", "Anuluj");
	}
	else Error(playerid, "Pojazd musi należeć gracza lub firmowy.");
	return 1;
}

Dialog:MTANKSET(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new targetid = GetPVarInt(playerid, "cache_mtank_targetid");
	new target_vehicleid = GetPVarInt(playerid, "cache_mtank_vehicleid");
	new fuel_value;
	if(compare(inputtext, "full")) fuel_value = -1;
	else fuel_value = strval(inputtext);
	if(fuel_value < 10 && fuel_value != -1) return Error(playerid, "Zbyt mała wartość.");
	if(fuel_value > 1000) return Error(playerid, "Zbyt duża wartość.");
	if(IsPlayerInVehicle(targetid, target_vehicleid))
	{
		new engine, lights, alarm, doors, bonnet, boot, objective;
		GetVehicleParamsEx(target_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
		new fuel_type = GetVehicleFuelType(pojazd[target_vehicleid][v_model]);
		new fuel_size = GetVehicleFuelSize(pojazd[target_vehicleid][v_model]);
		new Float:fuel_actual = pojazd[target_vehicleid][v_paliwo];
		if(fuel_value == -1) fuel_value = fuel_size-floatround(fuel_actual)-1;
		if(fuel_value < 0) fuel_value = 1;
		if(fuel_type == F_ON && fractions[F_MAFIA][fr_intval1] < fuel_value) return Error(playerid, "Mafia nie posiada takiej ilości oleju napędowego.");
		if(fuel_type == F_PB && fractions[F_MAFIA][fr_intval2] < fuel_value) return Error(playerid, "Mafia nie posiada takiej ilości benzyny.");
		//czy można tyle wlać paliwa do pojazdu gracza?
		if(floatround(fuel_actual)+fuel_value > fuel_size) return Error(playerid, "Zbyt dużo paliwa oferujesz. Nie zmieści się w zbiorniku.");//aktualne+to co chce dac bedzie wieksze niż całkowita objetosc paliwa
		new stawka_za_L = (fuel_type == F_ON) ? (fractions[F_MAFIA][fr_intval3]) : (fractions[F_MAFIA][fr_intval4]);
		//czy tyle paliwa jest w magazynie?
		new calc_fuel_price = fuel_value*stawka_za_L;
		if(Money(targetid) < calc_fuel_price) return Error(playerid, "Gracz ma niewystarczającą ilość gotówki.");
		new strMtank[1024];
		format(strMtank, 1024, ""COL_GREEN"Oferta została złożona. Jeśli wszystko pójdzie dobrze, potwierdzenie pojawi się na czacie.");
		format(strMtank, 1024, "%s\n\n"COL_WHITE"Szczegóły:", strMtank);
		format(strMtank, 1024, "%s\n"COL_ORANGE"» "COL_WHITE"Gracz: "COL_EASY"%s(%d)", strMtank, nick(targetid), targetid);
		format(strMtank, 1024, "%s\n"COL_ORANGE"» "COL_WHITE"Pojazd: "COL_EASY"%s(%d)", strMtank, GetVehicleName(pojazd[target_vehicleid][v_model]), pojazd[target_vehicleid][v_id]);
		format(strMtank, 1024, "%s\n"COL_ORANGE"» "COL_WHITE"Ilość paliwa zaoferowanego: "COL_EASY"%d litrów", strMtank, fuel_value);
		format(strMtank, 1024, "%s\n"COL_ORANGE"» "COL_WHITE"Typ paliwa zaoferowanego: "COL_EASY"%s", strMtank, (fuel_type == F_ON) ? ("Olej napędowy") : ("Benzyna"));
		format(strMtank, 1024, "%s\n"COL_ORANGE"» "COL_WHITE"Wartość paliwa: "COL_GREEN"%d$ "COL_EASY"(%d$ za litr)", strMtank, calc_fuel_price, stawka_za_L);
		MessageGUIEx(playerid, ""COL_RED"•» "COL_WHITE"Oferta złożona "COL_RED"«•", strMtank);
		//target
		format(strMtank, 1024, ""COL_GREEN"Otrzymałeś oferte tankowania od Mafii Paliwowej, przyjmujesz?");
		format(strMtank, 1024, "%s\n\n"COL_WHITE"Szczegóły:", strMtank);
		format(strMtank, 1024, "%s\n"COL_ORANGE"» "COL_WHITE"Pojazd: "COL_EASY"%s(%d)", strMtank, GetVehicleName(pojazd[target_vehicleid][v_model]), pojazd[target_vehicleid][v_id]);
		format(strMtank, 1024, "%s\n"COL_ORANGE"» "COL_WHITE"Ilość paliwa: "COL_EASY"%d litrów", strMtank, fuel_value);
		format(strMtank, 1024, "%s\n"COL_ORANGE"» "COL_WHITE"Typ paliwa: "COL_EASY"%s", strMtank, (fuel_type == F_ON) ? ("Olej napędowy") : ("Benzyna"));
		format(strMtank, 1024, "%s\n"COL_ORANGE"» "COL_WHITE"Cena: "COL_GREEN"%d$ "COL_EASY"(%d$ za litr)", strMtank, calc_fuel_price, stawka_za_L);
		Dialog_Show(targetid, MTANKACCEPT, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_WHITE"Oferta tankowania "COL_RED"«•", strMtank, "Akceptuj", "Odrzuc");
		SetPVarInt(targetid, "cache_mtank_acc_vehicleid", target_vehicleid);
		SetPVarInt(targetid, "cache_mtank_acc_fuelcount", fuel_value);
		SetPVarInt(targetid, "cache_mtank_acc_fueltype", fuel_type);
		SetPVarInt(targetid, "cache_mtank_acc_price", calc_fuel_price);
	}
	else Error(playerid, "Gracz nie jest w pojeździe.");
	return 1;
}

Dialog:MTANKACCEPT(playerid, response, listitem, inputtext[])//TARGET
{
	if(!response) return 1;
	if(GetPlayerVehicleID(playerid) == 0) return Error(playerid, "Nie jesteś w pojeździe.");
	new cache_vehicleid = GetPVarInt(playerid, "cache_mtank_acc_vehicleid");
	new cache_fuelcount = GetPVarInt(playerid, "cache_mtank_acc_fuelcount");
	new cache_fueltype = GetPVarInt(playerid, "cache_mtank_acc_fueltype");
	new cache_price = GetPVarInt(playerid, "cache_mtank_acc_price");
	if(IsPlayerInVehicle(playerid, cache_vehicleid))
	{
		new engine, lights, alarm, doors, bonnet, boot, objective;
		GetVehicleParamsEx(cache_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
		new Float:fuel_actual = pojazd[cache_vehicleid][v_paliwo];
		new fuel_size = GetVehicleFuelSize(pojazd[cache_vehicleid][v_model]);
		if(floatround(fuel_actual)+cache_fuelcount > fuel_size) return Error(playerid, "Zbyt duża ilość paliwa. Nie zmieści się w zbiorniku.");//aktualne+to co chce dac bedzie wieksze niż całkowita objetosc paliwa
		if(cache_fueltype == F_ON && fractions[F_MAFIA][fr_intval1] < cache_fuelcount) return Error(playerid, "Mafia nie posiada takiej ilości oleju napędowego.");
		if(cache_fueltype == F_PB && fractions[F_MAFIA][fr_intval2] < cache_fuelcount) return Error(playerid, "Mafia nie posiada takiej ilości benzyny.");
		if(cache_fueltype != F_PB && cache_fueltype != F_ON) return Error(playerid, "Wystąpił nieoczekiwany błąd.");
		if(Money(playerid) < cache_price) return Error(playerid, "Niewystarczająca ilość gotówki.");
		//transakcja:
		new strTrans[144];
		//zabieranie z magazynu
		if(cache_fueltype == F_ON)
		{
			fractions[F_MAFIA][fr_intval1] -= cache_fuelcount;
			format(strTrans, 144, "Gracz %s(%d) kupił %dL oleju napędowego za %d$. W magazynie pozostało: %d litrów.", nick(playerid), playerid, cache_fuelcount, cache_price, fractions[F_MAFIA][fr_intval1]);
		}
		else if(cache_fueltype == F_PB) 
		{
			fractions[F_MAFIA][fr_intval2] -= cache_fuelcount;
			format(strTrans, 144, "Gracz %s(%d) kupił %dL benzyny za %d$. W magazynie pozostało: %d litrów.", nick(playerid), playerid, cache_fuelcount, cache_price, fractions[F_MAFIA][fr_intval2]);
		}
		SendFractionMessage(F_MAFIA, strTrans);
		SaveFractionAddValues(F_MAFIA);//save intvals
		TakeMoney(playerid, cache_price);//zabieranie kasy
		fractions[F_MAFIA][fr_money] +=  cache_price;//dodawanie kasy dla frakcji
		pojazd[cache_vehicleid][v_paliwo] += float(cache_fuelcount);//dodawanie paliwa
		if(pojazd[cache_vehicleid][v_id] != 0)
		{
			mq_format("UPDATE `pojazdy` SET `paliwo`='%f' WHERE `id`='%d';", pojazd[cache_vehicleid][v_paliwo], pojazd[cache_vehicleid][v_id]);
			mq_send("QUpdatePaliwo");
		}
		mq_format("UPDATE `fractions_data` SET `money`='%d' WHERE `id`='%d';", fractions[F_MAFIA][fr_money], F_MAFIA);
		mq_send("QUpdateFractionMoneyScore");
		//transakcja end
		Info(playerid, "Przyjąłeś oferte. Pojazd został zatankowany!");
	}
	else Error(playerid, "Nie jesteś w pojeździe.");
	return 1;
}

//******************************************PRZEJŚCIA GRANICZNE - TP
stock Init_BorderCross()
{
	new strSG_Bramka[1024];
	for(new b; b < sizeof(border_cross); b++)
	{
		format(strSG_Bramka, 1024, ""COL_GREEN"« "COL_BLUE" Statusy pozostałych bramek "COL_GREEN"»");
		format(strSG_Bramka, 1024, "%s\n"COL_RED"(("COL_GREEN"PPM "COL_GREY"- Teleport między bramkami"COL_RED"))", strSG_Bramka);
		border_cross[b][bc_text3d] = CreateDynamic3DTextLabel(strSG_Bramka, -1, border_cross[b][bc_X], border_cross[b][bc_Y], border_cross[b][bc_Z], 6.0);
		CreateDynamicPickup(1239, 1, border_cross[b][bc_X], border_cross[b][bc_Y], border_cross[b][bc_Z]);
		border_cross[b][bc_mapicon] = CreateDynamicMapIcon(border_cross[b][bc_X], border_cross[b][bc_Y], border_cross[b][bc_Z], 0, 0x000000AA);
	}
	return 1;
}

task Process_BC()
{
	static blink_mapicon;
	for(new b; b < sizeof(border_cross); b++)
	{
		if(blink_mapicon == 0) Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, border_cross[b][bc_mapicon], E_STREAMER_COLOR,  0x00FF0050);
		else if(blink_mapicon == 1) Streamer_SetIntData(STREAMER_TYPE_MAP_ICON, border_cross[b][bc_mapicon], E_STREAMER_COLOR,  0x377E0050);
		border_cross[b][bc_count_waiting] = 0;
		border_cross[b][bc_count_officers] = 0;
		for(new p = PlayerPoolSize(); p != -1; p--)
		{
			if(!gracz[p][loggedin]) continue;
			//liczenie strażników
			if(IsPlayerInRangeOfPoint(p, 70.0, border_cross[b][bc_X], border_cross[b][bc_Y], border_cross[b][bc_Z]))
			{
				if(gracz[p][frakcja] == F_BORDERGUARD && IsPlayerOnDutyFraction(p))
				{
					border_cross[b][bc_count_officers]++;
				}
				else if(IsPlayerInAnyVehicle(p))
				{
					border_cross[b][bc_count_waiting]++;
				}
			}
		}
	}
	//odświeżanie 3dtextów
	new strSG_Bramka[1024];
	for(new b; b < sizeof(border_cross); b++)
	{
		format(strSG_Bramka, 1024, ""COL_GREEN"« "COL_BLUE" Statusy pozostałych bramek "COL_GREEN"»");
		for(new b2; b2 < sizeof(border_cross); b2++)
		{
			format(strSG_Bramka, 1024, "%s\n%s[%s]"COL_ORANGE": "COL_DRVONLINE"[Oczekujący: "COL_WHITE"%d"COL_DRVONLINE"]"COL_WHITE"/"COL_GREEN"[Funkcjonariuszy: "COL_WHITE"%d"COL_GREEN"]%s", strSG_Bramka, (border_cross[b2][bc_count_waiting] > border_cross[b2][bc_count_officers]) ? (""COL_RED"") : (""COL_WHITE""), border_cross[b2][bc_name], border_cross[b2][bc_count_waiting], border_cross[b2][bc_count_officers], (b2 == b) ? (" "COL_LIME"« [Tu jesteś]") : (" "));
		}
		format(strSG_Bramka, 1024, "%s\n"COL_RED"(("COL_GREEN"PPM "COL_GREY"- Teleport między bramkami"COL_RED"))", strSG_Bramka);
		UpdateDynamic3DTextLabelText(border_cross[b][bc_text3d], -1, strSG_Bramka);
	}
	if(blink_mapicon == 0) blink_mapicon = 1;
	else if(blink_mapicon == 1) blink_mapicon = 0;
	return 1;
}

stock IsPlayerInRangeOfPickBC(playerid)
{
	for(new b; b < sizeof(border_cross); b++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 1.5, border_cross[b][bc_X], border_cross[b][bc_Y], border_cross[b][bc_Z])) return b;
	}
	return -1;
}

stock ShowBorderCrossList(playerid)
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return 1;
	new ipiropbc = IsPlayerInRangeOfPickBC(playerid);
	if(ipiropbc == -1) return 1;
	new strBorderList[2048];
	format(strBorderList, 2048, "Nazwa granicy\tOczekujący\tFunkcjonariuszy");
	new count_listitem;
	for(new b; b < sizeof(border_cross); b++)
	{
		format(strBorderList, 2048, "%s\n%s%s%s\t"COL_DRVONLINE"%d\t"COL_GREEN"%d", strBorderList, (border_cross[b][bc_count_waiting] > border_cross[b][bc_count_officers]) ? (""COL_RED"") : (""COL_WHITE""), border_cross[b][bc_name], (b == ipiropbc) ? (" "COL_LIME" [Tu jesteś]") : (" "), border_cross[b][bc_count_waiting], border_cross[b][bc_count_officers]);
		gui_cache[playerid][count_listitem][0] = b;
		count_listitem++;
	}
	Dialog_Show(playerid, SELECTBORDERCROSS, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_WHITE"Teleport między granicami "COL_RED"«•", strBorderList, "Wybierz", "Anuluj");
	return 1;
}

Dialog:SELECTBORDERCROSS(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new b = gui_cache[playerid][listitem][0];
	FreezeLoadObject(playerid, border_cross[b][bc_X], border_cross[b][bc_Y], border_cross[b][bc_Z]);
	SendClientMessageEx(playerid, -1, ""COL_GREEN"Teleportowałeś się na przejście graniczne: "COL_BLUE"%s",  border_cross[b][bc_name]);
	return 1;
}
//**********************************************PACHOŁKI
stock CreateCone(frakcjaid, Float:cnX, Float:cnY, Float:cnZ)
{
	for(new c; c < MAX_CONES; c++)
	{
		if(cones[c][cn_object] == 0)
		{
			new strText3D[128];
			format(strText3D, 128, ""COL_ORANGE"["COL_RED"Pachołek (ID: %d)"COL_ORANGE"]\n%s", c, GetFractionName(frakcjaid, 1));
			cones[c][cn_object] = CreateDynamicObject(1238, cnX, cnY, cnZ, 0.0, 0.0, 0.0);
			cones[c][cn_text3d] = CreateDynamic3DTextLabel(strText3D, -1, cnX, cnY, cnZ, 30.0);
			cones[c][cn_X] = cnX;
			cones[c][cn_Y] = cnY;
			cones[c][cn_Z] = cnZ;
			cones[c][cn_fraction] = frakcjaid;
			return c;
		}
	}
	return -1;
}

stock DestroyCone(coneid)
{
	if(cones[coneid][cn_object] != 0)
	{
		DestroyDynamicObject(cones[coneid][cn_object]);
		DestroyDynamic3DTextLabel(cones[coneid][cn_text3d]);
		for(new cone_data:r; r < cone_data; r++)
		{
			cones[coneid][r] = 0;
		}
		return 1;
	}
	return 0;
}

CMD:pacholek(playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid)) return Error(playerid, "Tej komendy nie mozna uzywac w pojezdzie.");
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD  && fid != F_ROADASSIST && fid != F_EMERGENCY) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	new opcja[256];
	if(sscanf(params,"s[256]", opcja)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /pacholek [stworz/lista/usunwszystkie] LUB [s/l/uw]");
	if(compare(opcja, "stworz") || compare(opcja, "s"))
	{
		new Float:fPos[2];
		GetXYInFrontOfPlayer(playerid, fPos[0], fPos[1], 0.4);	
		new ccid = CreateCone(fid, fPos[0], fPos[1], gracz[playerid][PosZ]-0.7);
		if(ccid != -1) 
		{
			SendClientMessageEx(playerid, 0x61A347FF, "Stworzyłeś pachołek ID: "COL_RED"%d", ccid);
			Streamer_Update(playerid);
		}
		else Error(playerid, "Maksymalna ilość pachołków na mapie. Użyj /pacholek lista");
	}
	else if(compare(opcja, "lista") || compare(opcja, "l"))
	{
		new strConeList[2048];
		new find = 0;
		format(strConeList, 2048, "ID pacholka\tOdległość\tFrakcja");
		for(new c; c < MAX_CONES; c++)
		{
			if(cones[c][cn_object] != 0)
			{
				format(strConeList, 2048, "%s\n"COL_WHITE"%d\t"COL_LIME"%0.2f\t%s", strConeList, c, GetDistanceBetweenPoints(gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], cones[c][cn_X], cones[c][cn_Y], cones[c][cn_Z]), GetFractionName(cones[c][cn_fraction], 1));
				find++;
			}
		}
		if(find) Dialog_Show(playerid, CONESLIST, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_WHITE"Lista pachołków "COL_RED"«•", strConeList, "Usuń", "Anuluj");
		else Error(playerid, "Brak pachołków.");
	}
	else if(compare(opcja, "usunwszystkie") || compare(opcja, "uw"))
	{
		new find = 0;
		for(new c; c < MAX_CONES; c++)
		{
			if(cones[c][cn_object] != 0)
			{
				if(IsPlayerInRangeOfPoint(playerid, 10.0, cones[c][cn_X], cones[c][cn_Y], cones[c][cn_Z]))
				{
					DestroyCone(c);
					find++;
				}
			}
		}
		if(find > 0) Info(playerid, "Usunąłeś/aś wszystkie w pobliżu pachołki.");
		else Error(playerid, "Nie znaleziono pachołków w pobliżu.");
	}
	else SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /pacholek [stworz/lista/usunwszystkie] LUB [s/l/uw]");
	return 1;
}

Dialog:CONESLIST(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cid = strval(inputtext);
	SendClientMessageEx(playerid, 0xB91F1FFF, "Usunąłeś pachołek ID: %d należący do: %s", cid, GetFractionName(cones[cid][cn_fraction], 1));
	DestroyCone(cid);
	return 1;
}

//Konary służby ratunkowe
stock FallTree_Debug()
{
	for(new t; t < sizeof(fallTree_position); t++)
	{
		CreateDynamicMapIcon(fallTree_position[t][0], fallTree_position[t][1], fallTree_position[t][2], 0, 0xE066FFFF, .streamdistance = 1000.0, .style = MAPICON_GLOBAL);
	}
	return 1;
}

//19898
stock FallTree_RandomCreate()
{
	fallTree_query++;
	if(fallTree_query >= sizeof(fallTree_position)) fallTree_query = 0;
	new rTree_id = fallTree_query;
	if(fallTree_data[rTree_id][ft_isfall]) return 0;
	new Float:lPos[4];
	lPos[0] = fallTree_position[rTree_id][0];
	lPos[1] = fallTree_position[rTree_id][1];
	lPos[2] = fallTree_position[rTree_id][2];
	lPos[3] = fallTree_position[rTree_id][3];
	fallTree_data[rTree_id][ft_isfall] = true;
	fallTree_data[rTree_id][ft_hp] = 100;
	fallTree_data[rTree_id][ft_objectid] = CreateDynamicObject(846, lPos[0], lPos[1], lPos[2]+10, 0.0, 0.0, lPos[3] , 0, 0);
	MoveDynamicObject(fallTree_data[rTree_id][ft_objectid], lPos[0], lPos[1], lPos[2]-0.4, 3.0, 0.0, 0.0, lPos[3]);
	fallTree_data[rTree_id][ft_label] = CreateDynamic3DTextLabel("{9700db}***Na ziemi leży urwany konar***\n{FFFFFF}[HP: {00FF00}100%{FFFFFF}]", -1, lPos[0], lPos[1], lPos[2]-0.4, 30.0);
	//plama oleju
	//fallTree_data[rTree_id][ft_objectid] = CreateDynamicObject(19898, lPos[0], lPos[1], lPos[2]-0.85, 0.0, 0.0, lPos[3] , 0, 0);
	//fallTree_data[rTree_id][ft_label] = CreateDynamic3DTextLabel("{9700db}***Na ziemi plama oleju***\n{FFFFFF}[HP: {00FF00}100%{FFFFFF}]", -1, lPos[0], lPos[1], lPos[2]-0.4, 30.0);
	//plama oleju end
	//---------
	//----------
	return 1;
}

stock FallTree_ClearAll()
{
	for(new t; t < sizeof(fallTree_position); t++)
	{
		FallTree_Destroy(t);
	}
	return 1;
}

stock FallTree_Destroy(tree_id)
{
	if(!fallTree_data[tree_id][ft_isfall]) return 0;
	fallTree_data[tree_id][ft_isfall] = false;
	DestroyDynamicObject(fallTree_data[tree_id][ft_objectid]);
	DestroyDynamic3DTextLabel(fallTree_data[tree_id][ft_label]);
	return 1;
}

stock FallTree_Count()
{
	new wynik;
	for(new t; t < sizeof(fallTree_position); t++)
	{
		if(fallTree_data[t][ft_isfall])
		{
			wynik++;
		}
	}
	return wynik;
}

task Process_FallTree()
{
	if(fallTree_createTime < serwer[time_timestamp])
	{
		fallTree_createTime = gettime()+60*60*FALLTREE_DELAY;
		if(FallTree_Count()) FallTree_ClearAll();
		//---------
		//usuwanie kłody z wezwania
		for(new c; c < MAX_CALLS; c++)
		{
			if(calls[c][call_type] == 0) continue;
			if(calls[c][call_fraction] == F_EMERGENCY)
			{
				if(calls[c][call_type] == 3)//kłoad
				{
					calls[c][call_status] = 0;
					calls[c][call_type] = 0;
					break;
				}
			}
		}
		//----------
		FallTree_RandomCreate();
	}
	for(new t; t < sizeof(fallTree_position); t++)
	{
		if(fallTree_data[t][ft_isfall])
		{
			new Float:lPos[3];
			lPos[0] = fallTree_position[t][0];
			lPos[1] = fallTree_position[t][1];
			lPos[2] = fallTree_position[t][2];
			//dodawanie wezwania jeśli go nie ma
			new bool:find = false;
			for(new c; c < MAX_CALLS; c++)
			{
				if(calls[c][call_type] == 0) continue;
				if(calls[c][call_fraction] == F_EMERGENCY)
				{
					if(calls[c][call_type] == 3)//kłoda
					{
						find = true;//znaleziono
						break;
					}
				}
			}
			if(!find) NewCall(F_EMERGENCY, -1, 3, "Kłoda na drodze", lPos[0], lPos[1], lPos[2]);//jeśli nie ma, to dodajemy
			break;
		}
	}
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(!gracz[p][loggedin]) continue;
		if(gracz[p][frakcja] != F_EMERGENCY) continue;
		if(!IsPlayerOnDutyFraction(p)) continue;
		for(new t; t < sizeof(fallTree_position); t++)
		{
			if(fallTree_data[t][ft_isfall])
			{
				new Float:lPos[3];
				lPos[0] = fallTree_position[t][0];
				lPos[1] = fallTree_position[t][1];
				lPos[2] = fallTree_position[t][2];
				if(IsPlayerInRangeOfPoint(p, 4.0, lPos[0], lPos[1], lPos[2]))
				{
					if(GetPlayerWeapon(p) == WEAPON_CHAINSAW)
					{
						new Keys,ud,lr;
						GetPlayerKeys(p,Keys,ud,lr);
						if(Keys == KEY_FIRE)
						{
							if(fallTree_data[t][ft_hp] > 0)
							{
								fallTree_data[t][ft_hp] -= 1;
								if(fallTree_data[t][ft_hp] > 70) format(temp_string, 128, "{9700db}***Na ziemi leży urwany konar***\n{FFFFFF}[HP: {00FF00}%d%%{FFFFFF}]", fallTree_data[t][ft_hp]);
								else if(fallTree_data[t][ft_hp] > 40) format(temp_string, 128, "{9700db}***Na ziemi leży urwany konar***\n{FFFFFF}[HP: {FFFF00}%d%%{FFFFFF}]", fallTree_data[t][ft_hp]);
								else format(temp_string, 128, "{9700db}***Na ziemi leży urwany konar***\n{FFFFFF}[HP: {FF0000}%d%%{FFFFFF}]", fallTree_data[t][ft_hp]);
								UpdateDynamic3DTextLabelText(fallTree_data[t][ft_label], -1, temp_string);
							}
							else
							{
								GiveMoney(p, 4000);
								GameTextForPlayer(p, "~g~+4000$", 5000, 3);
								GiveFractionMoneyOrScore(F_EMERGENCY, 1, 4000);
								FallTree_Destroy(t);
								//---------
								//usuwanie kłody z wezwania
								for(new c; c < MAX_CALLS; c++)
								{
									if(calls[c][call_type] == 0) continue;
									if(calls[c][call_fraction] == F_EMERGENCY)
									{
										if(calls[c][call_type] == 3)//kłoda
										{
											calls[c][call_status] = 0;
											calls[c][call_type] = 0;
											break;
										}
									}
								}
								//----------
								fallTree_createTime = gettime()+60*10;
							}
						}
					}
				}
			}
		}
	}
	return 1;
}

//plamy oleju
stock OilSR_Debug()
{
	for(new t; t < sizeof(oilSR_position); t++)
	{
		CreateDynamicMapIcon(oilSR_position[t][0], oilSR_position[t][1], oilSR_position[t][2], 0, 0xE066FFFF, .streamdistance = 1000.0, .style = MAPICON_GLOBAL);
	}
	return 1;
}

stock OilSR_RandomCreate()
{
	oilSR_query++;
	if(oilSR_query >= sizeof(oilSR_position)) oilSR_query = 0;
	new oil_id = oilSR_query;
	if(oilSR_data[oil_id][ft_isfall]) return 0;
	new Float:lPos[4];
	lPos[0] = oilSR_position[oil_id][0];
	lPos[1] = oilSR_position[oil_id][1];
	lPos[2] = oilSR_position[oil_id][2];
	lPos[3] = oilSR_position[oil_id][3];
	oilSR_data[oil_id][ft_isfall] = true;
	oilSR_data[oil_id][ft_hp] = 100;
	serwer[actual_oilid] = oil_id;
	//plama oleju
	oilSR_data[oil_id][ft_objectid] = CreateDynamicObject(19898, lPos[0], lPos[1], lPos[2]-0.85, 0.0, 0.0, lPos[3] , 0, 0);
	oilSR_data[oil_id][ft_label] = CreateDynamic3DTextLabel("{9700db}***Na ziemi jest plama oleju***", -1, lPos[0], lPos[1], lPos[2]-0.4, 30.0);
	//plama oleju end
	//---------
	//----------
	return 1;
}

stock OilSR_ClearAll()
{
	for(new t; t < sizeof(oilSR_position); t++)
	{
		OilSR_Destroy(t);
	}
	return 1;
}

stock OilSR_Destroy(oil_id)
{
	if(!oilSR_data[oil_id][ft_isfall]) return 0;
	oilSR_data[oil_id][ft_isfall] = false;
	DestroyDynamicObject(oilSR_data[oil_id][ft_objectid]);
	DestroyDynamic3DTextLabel(oilSR_data[oil_id][ft_label]);
	return 1;
}

stock OilSR_Count()
{
	new wynik;
	for(new t; t < sizeof(oilSR_position); t++)
	{
		if(oilSR_data[t][ft_isfall])
		{
			wynik++;
		}
	}
	return wynik;
}

task Process_OilSR()
{
	if(oilSR_createTime < serwer[time_timestamp])
	{
		oilSR_createTime = gettime()+60*60*FALLTREE_DELAY;
		if(OilSR_Count()) OilSR_ClearAll();
		//---------
		//usuwanie kłody z wezwania
		for(new c; c < MAX_CALLS; c++)
		{
			if(calls[c][call_type] == 0) continue;
			if(calls[c][call_fraction] == F_EMERGENCY)
			{
				if(calls[c][call_type] == 4)//plama oleju
				{
					calls[c][call_status] = 0;
					calls[c][call_type] = 0;
					break;
				}
			}
		}
		//----------
		OilSR_RandomCreate();
	}
	for(new t; t < sizeof(oilSR_position); t++)
	{
		if(oilSR_data[t][ft_isfall])
		{
			new Float:lPos[3];
			lPos[0] = oilSR_position[t][0];
			lPos[1] = oilSR_position[t][1];
			lPos[2] = oilSR_position[t][2];
			//dodawanie wezwania jeśli go nie ma
			new bool:find = false;
			for(new c; c < MAX_CALLS; c++)
			{
				if(calls[c][call_type] == 0) continue;
				if(calls[c][call_fraction] == F_EMERGENCY)
				{
					if(calls[c][call_type] == 4)//plama oleju
					{
						find = true;//znaleziono
						break;
					}
				}
			}
			if(!find) NewCall(F_EMERGENCY, -1, 4, "Plama oleju na drodze", lPos[0], lPos[1], lPos[2]);//jeśli nie ma, to dodajemy
			break;
		}
	}
	/*for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(!gracz[p][loggedin]) continue;
		if(gracz[p][frakcja] != F_EMERGENCY) continue;
		if(!IsPlayerOnDutyFraction(p)) continue;
		for(new t; t < sizeof(oilSR_position); t++)
		{
			if(oilSR_data[t][ft_isfall])
			{
				new Float:lPos[3];
				lPos[0] = oilSR_position[t][0];
				lPos[1] = oilSR_position[t][1];
				lPos[2] = oilSR_position[t][2];
				if(IsPlayerInRangeOfPoint(p, 4.0, lPos[0], lPos[1], lPos[2]))
				{

				}
			}
		}
	}*/
	return 1;
}
//------------------------------------------------------------- paralizator
COMMAND:taser(playerid, params[])
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Brak uprawnień.");
	if(gracz[playerid][taser_has] == false)
	{
		gracz[playerid][taser_has] = true;
		SetPlayerAttachedObject(playerid, ATTACH_SLOT5, 18642, 6, 0.06, 0.01, 0.08, 180.0, 0.0, 0.0);
		SendClientMessage(playerid, COLOR_GREY, "((Wyciągnąłeś paralizator - pamiętaj o odgrywaniu!))");
	}
	else
	{
		gracz[playerid][taser_has] = false;
		RemovePlayerAttachedObject(playerid, ATTACH_SLOT5);
		SendClientMessage(playerid, COLOR_GREY, "((Paralizator schowany.))");
	}
	return 1;
}

task TASER_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	new fid = gracz[playerid][frakcja];
	if((fid != F_POLICE && fid != F_BORDERGUARD) || !IsPlayerOnDutyFraction(playerid)) return 1;
	if(gracz[playerid][bw] > 0) return 1;
	if(gracz[playerid][wypadek] > 0) return 1;
	if(GetPlayerWeapon(playerid) != 0)
	{
		if(gracz[playerid][taser_has] == true)
		{
			gracz[playerid][taser_has] = false;
			RemovePlayerAttachedObject(playerid, ATTACH_SLOT5);
			SendClientMessage(playerid, COLOR_GREY, "((Paralizator schowany.))");
		}
		return 1;
	}
	if(newkeys & KEY_FIRE)
	{
		if(gracz[playerid][taser_has] == true)
		{
			new TargetID = GetClosestPlayer(playerid);
			if(!IsPlayerConnected(TargetID)) return 1;
			if(gracz[TargetID][taser_tased] == true) return 1;
			if(gracz[TargetID][bw] > 0) return 1;
			if(gracz[TargetID][wypadek] > 0) return 1;
			if(gracz[TargetID][kajdanki] == true) return 1;
			if(IsPlayerOnDutyFraction(TargetID)) return 1;
			ApplyAnimation(playerid,"KNIFE","knife_3",4.1,0,1,1,0,0,1);
			if(playerid != TargetID)
			{
				if(IsPlayerInRangeOfPlayer(2.0, playerid, TargetID))
				{
					gracz[TargetID][taser_tased] = true;
					TogglePlayerControllable(TargetID, 0);
					ApplyAnimation(TargetID, "CRACK", "crckdeth2", 3.0, 1, 0, 0, 1, 0);
					SetTimerEx("RemoveTaseEffect", 7000, false, "d", TargetID);
					SendClientMessage(TargetID, COLOR_RED, "Zostałeś/aś sparaliżowany/a na 7 sekund!");
					new str[128];
					format(str, sizeof(str), "/me sparaliżował/a %s paralizatorem.", nick(TargetID));
					PC_EmulateCommand(playerid, str);
				}
			}
		}
	}
	return 1;
}

task RemoveTaseEffect(playerid)
{
	TogglePlayerControllable(playerid, 1);
	SetPlayerSkin(playerid, GetPlayerSkin(playerid));
	gracz[playerid][taser_tased] = false;
	SendClientMessage(playerid, COLOR_GREEN, "Odzyskałeś/aś sprawność...");
	return 1;
}