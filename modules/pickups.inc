new pickup_spray;
new pickup_driverlicense;
new pickup_centrefreestamina;

enum pick_fbdata
{
	fb_pickup,
	Text3D:fb_label,
	bool:fb_status,
};
new pick_fixbody[pick_fbdata];

stock Init_Pickups()
{
	CreateDynamicPickup(1682, 1, 1296.70032, 1502.58423, 26.01563, 0, 0, .streamdistance = 500.0);//antena lot lv
	CreateDynamicPickup(1239, 1, XYZ_SALON, 0, 0);
	CreateDynamicPickup(1239, 1, XYZ_TRUCKSALON, 0, 0);
	CreateDynamicPickup(1247, 1, XYZ_PRISONADD, 0, 0);
	pickup_spray = CreatePickup(365, 1, XYZ_SPRAY);
	pickup_driverlicense = CreatePickup(1581, 1, XYZ_PRAWKO);
	pickup_centrefreestamina = CreatePickup(1277, 2, 2081.0640,2100.5774,14.3097);
	
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	if(gracz[playerid][status_lunapark] == LPARK_ASG) return 1;
	if(pickupid == gracz[playerid][courier_job_pickup]) Courier_Event(playerid, 4);

	if(pickupid == pickup_spray && IsPlayerOnDutyFraction(playerid) && gracz[playerid][frakcja] == F_ROADASSIST) 
	{
		ResetPlayerWeapons(playerid);
		GivePlayerWeapon(playerid, WEAPON_SPRAYCAN, 99999);
	}
	if(pickupid == pickup_driverlicense) DisablePlayerCheckpoint(playerid);
	if(pickupid == pickup_centrefreestamina)
	{
		gracz[playerid][stamina] = 100;
		SetPlayerHealth(playerid, 100.0);
		HUD_UpdateSTAMINA(playerid);
		mq_format("UPDATE `Konta` SET `stamina`='%d' WHERE `id`='%d';", gracz[playerid][stamina], gracz[playerid][UID]);
		mq_send("QUpdateStamina");
		LeftNotifyShow(playerid, "Stamina", "Stamina i HP zostalo zregenerowane.", LN_GREEN);
	}
	return 1;
}


task Process_PickupFixbody()
{
	if(pick_fixbody[fb_status] == false)
	{
		if(FractionDutyWorkersCount(F_ROADASSIST) == 0)
		{
			pick_fixbody[fb_pickup] = CreateDynamicPickup(3096, 1, XYZ_FIXBODY+1.0, 0, 0);
			pick_fixbody[fb_label] = CreateDynamic3DTextLabel("« "COL_BLUE"NAPRAWA POJAZDU "COL_GREEN"»\n"COL_RED"• "COL_WHITE"Wpisz "COL_GREEN"/karoseria"COL_WHITE" aby naprawić karoserię. "COL_RED"•\n"COL_RED"• "COL_WHITE"Wpisz "COL_GREEN"/fix"COL_WHITE" aby naprawić pojazd (Tylko stan: "COL_RED"AWARIA"COL_WHITE"). "COL_RED"•\n"COL_GREY"(Jednorazowe wprowadzenie komendy "COL_GREEN"/fix"COL_GREY" = jeden komponent)", 0x009933FF, XYZ_FIXBODY, 50.0);
			pick_fixbody[fb_status] = true;
		}
	}
	else//true pick_fixbody
	{
		if(FractionDutyWorkersCount(F_ROADASSIST) > 0)
		{
			DestroyDynamicPickup(pick_fixbody[fb_pickup]);
			DestroyDynamic3DTextLabel(pick_fixbody[fb_label]);
			pick_fixbody[fb_status] = false;
		}
	}
	return 1;
}

CMD:karoseria(playerid, params[])
{
	if(pick_fixbody[fb_status] == false) return Error(playerid, "Pomoc drogowa jest na służbie. Komenda niedostępna.");
	if(IsPlayerInRangeOfPoint(playerid, 10.0, XYZ_FIXBODY))
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(vehicleid == 0) return Error(playerid, "Musisz być w pojeździe.");
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER)
		{
			if(!IsPlayerCanDrive(playerid, vehicleid)) return Error(playerid, "Brak uprawnień.");
			new engine, lights, alarm, doors, bonnet, boot, objective;
			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
			new strTitle[128];
			new strContent[2048];
			new Float:fix_price;
			fix_price = (1.0/100.0)*CalcVehiclePriceEx(pojazd[vehicleid][v_model]);
			format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Naprawa karoserii "COL_RED"«•", GetVehicleName(pojazd[vehicleid][v_model]));
			format(strContent, 2048, ""COL_WHITE"Mechanik "COL_ROADA"%s"COL_WHITE" wystawił Ci rachunek za naprawę "COL_LIME"karoserii"COL_WHITE" w pojeździe "COL_BLUE"%s"COL_WHITE".", nick(-1), GetVehicleName(pojazd[vehicleid][v_model]));
			format(strContent, 2048, "%s\n"COL_RED"Jeśli odrzucisz rachunek, naprawa nie zostanie zrealizowana.", strContent);
			format(strContent, 2048, "%s\n\n"COL_RED"» "COL_WHITE"Podsumowanie:", strContent);
			format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Pojazd: "COL_BLUE"%s "COL_GREY"(UID: %d)", strContent, GetVehicleName(pojazd[vehicleid][v_model]), pojazd[vehicleid][v_id]);
			format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Komponent: "COL_LIME"Karoseria", strContent);
			format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Koszt: "COL_GREEN"%d$", strContent, floatround(fix_price));
			format(strContent, 2048, "%s\n\n"COL_GREEN"Czy zgadzasz się na naprawę i przyjmujesz rachunek?", strContent);
			Dialog_Show(playerid, KAROSERIAFIX, DIALOG_STYLE_MSGBOX, strTitle, strContent, "Akceptuj", "Odrzuc");
			//ładowanie cache
			SetPVarInt(playerid, "cache_karoseriafix_vehicleid", vehicleid);
			SetPVarInt(playerid, "cache_karoseriafix_price", floatround(fix_price));
		}
		else if(pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)
		{
			if(!IsPlayerOnDutyCompany(playerid)) return Error(playerid, "Gracz nie jest na służbie w firmie.");
			if(pojazd[vehicleid][v_owner] != gracz[playerid][firma]) return Error(playerid, "Gracz nie jest w firmie do której należy pojazd.");
			if(gracz[playerid][firma_permlvl] == 0) return Error(playerid, "Brak uprawnień");
			new engine, lights, alarm, doors, bonnet, boot, objective;
			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
			new strTitle[128];
			new strContent[2048];
			new Float:fix_price;
			fix_price = (1.0/100.0)*CalcVehiclePriceEx(pojazd[vehicleid][v_model]);
			format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Naprawa karoserii "COL_RED"«•", GetVehicleName(pojazd[vehicleid][v_model]));
			format(strContent, 2048, ""COL_WHITE"Mechanik "COL_ROADA"%s"COL_WHITE" wystawił na Twoją "COL_RED"firmę"COL_WHITE" rachunek za naprawę "COL_LIME"karoserii"COL_WHITE" w pojeździe "COL_BLUE"%s"COL_WHITE".", nick(-1), GetVehicleName(pojazd[vehicleid][v_model]));
			format(strContent, 2048, "%s\n"COL_ORANGE"Jeśli odrzucisz rachunek, naprawa nie zostanie zrealizowana.", strContent);
			format(strContent, 2048, "%s\n"COL_RED"RACHUNEK ZOSTANIE OPŁACONY Z KONTA FIRMY", strContent);
			format(strContent, 2048, "%s\n\n"COL_RED"» "COL_WHITE"Podsumowanie:", strContent);
			format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Pojazd: "COL_BLUE"%s "COL_GREY"(UID: %d)", strContent, GetVehicleName(pojazd[vehicleid][v_model]), pojazd[vehicleid][v_id]);
			format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Komponent: "COL_LIME"Karoseria", strContent);
			format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Koszt: "COL_GREEN"%d$", strContent, floatround(fix_price));
			format(strContent, 2048, "%s\n\n"COL_GREEN"Czy zgadzasz się na naprawę i przyjmujesz rachunek?", strContent);
			Dialog_Show(playerid, KAROSERIAFIX, DIALOG_STYLE_MSGBOX, strTitle, strContent, "Akceptuj", "Odrzuc");
			//ładowanie cache
			SetPVarInt(playerid, "cache_karoseriafix_vehicleid", vehicleid);
			SetPVarInt(playerid, "cache_karoseriafix_price", floatround(fix_price));
		}
		else if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION)
		{
			new engine, lights, alarm, doors, bonnet, boot, objective;
			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
			RepairVehicle(vehicleid);
			SetVehicleHealth(vehicleid, 1000.0);
			new strNotify[1024];
			format(strNotify, 1024, "Naprawiono ~y~karoserie~w~ w pojezdzie ~b~%s~w~.", GetVehicleName(pojazd[vehicleid][v_model]));
			LeftNotifyShow(playerid, "Sukces!", strNotify, LN_GREEN);
		}
		else Error(playerid, "Tego pojazdu nie można naprawić w ten sposób.");
	}
	else Error(playerid, "Karoserię możesz naprawić przy bazie pomocy drogowej.");
	return 1;
}

CMD:fix(playerid, params[])
{
	if(pick_fixbody[fb_status] == false) return Error(playerid, "Pomoc drogowa jest na służbie. Komenda niedostępna.");
	if(IsPlayerInRangeOfPoint(playerid, 10.0, XYZ_FIXBODY))
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if(vehicleid == 0) return Error(playerid, "Musisz być w pojeździe.");
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER)
		{
			if(!IsPlayerCanDrive(playerid, vehicleid)) return Error(playerid, "Brak uprawnień.");
			new engine, lights, alarm, doors, bonnet, boot, objective;
			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
			new strTitle[128];
			new strContent[2048];
			new Float:fix_price;
			for(new x; x < MAX_VEHICLEDAMAGES; x++)
			{
				if(IsVehicleWornOut(vehicleid, x))
				{
					fix_price = (VehicleDamages[x][vd_price_proc]/100.0)*CalcVehiclePriceEx(pojazd[vehicleid][v_model]);
					format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Naprawa: "COL_ORANGE"%s "COL_RED"«•", VehicleDamages[x][vd_title]);
					format(strContent, 2048, ""COL_WHITE"Mechanik "COL_ROADA"%s"COL_WHITE" wystawił Ci rachunek za naprawę "COL_LIME"%s"COL_WHITE" w pojeździe "COL_BLUE"%s"COL_WHITE".", nick(-1), VehicleDamages[x][vd_title], GetVehicleName(pojazd[vehicleid][v_model]));
					format(strContent, 2048, "%s\n"COL_RED"Jeśli odrzucisz rachunek, naprawa nie zostanie zrealizowana.", strContent);
					format(strContent, 2048, "%s\n\n"COL_RED"» "COL_WHITE"Podsumowanie:", strContent);
					format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Pojazd: "COL_BLUE"%s "COL_GREY"(UID: %d)", strContent, GetVehicleName(pojazd[vehicleid][v_model]), pojazd[vehicleid][v_id]);
					format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Komponent: "COL_LIME"%s", strContent, VehicleDamages[x][vd_title]);
					format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Koszt: "COL_GREEN"%d$", strContent, floatround(fix_price));
					format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Aktualny stan komponentu: "COL_RED"AWARIA", strContent);
					format(strContent, 2048, "%s\n\n"COL_GREEN"Czy zgadzasz się na naprawę i przyjmujesz rachunek?", strContent);
					Dialog_Show(playerid, OBDFIXCONFIRM, DIALOG_STYLE_MSGBOX, strTitle, strContent, "Akceptuj", "Odrzuc");
					SetPVarInt(playerid, "cache_odbfix_component", x);
					SetPVarInt(playerid, "cache_odbfix_vehicleid", vehicleid);
					SetPVarInt(playerid, "cache_odbfix_price", floatround(fix_price));
					SetPVarInt(playerid, "cache_odbfix_mechanicid", playerid);
					return 1;
				}
			}
			Error(playerid, "Nie wykryto awarii.");
		}
		else if(pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)
		{
			if(!IsPlayerOnDutyCompany(playerid)) return Error(playerid, "Gracz nie jest na służbie w firmie.");
			if(pojazd[vehicleid][v_owner] != gracz[playerid][firma]) return Error(playerid, "Gracz nie jest w firmie do której należy pojazd.");
			if(gracz[playerid][firma_permlvl] == 0) return Error(playerid, "Brak uprawnień");
			new engine, lights, alarm, doors, bonnet, boot, objective;
			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			if(engine) return Error(playerid, "Pojazd musi mieć zgaszony silnik.");
			new strTitle[128];
			new strContent[2048];
			new Float:fix_price;
			for(new x; x < MAX_VEHICLEDAMAGES; x++)
			{
				if(IsVehicleWornOut(vehicleid, x))
				{
					fix_price = (VehicleDamages[x][vd_price_proc]/100.0)*CalcVehiclePriceEx(pojazd[vehicleid][v_model]);
					format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Naprawa: "COL_ORANGE"%s "COL_RED"«•", VehicleDamages[x][vd_title]);
					format(strContent, 2048, ""COL_WHITE"Mechanik "COL_ROADA"%s"COL_WHITE" wystawił Ci rachunek za naprawę "COL_LIME"%s"COL_WHITE" w pojeździe "COL_BLUE"%s"COL_WHITE".", nick(-1), VehicleDamages[x][vd_title], GetVehicleName(pojazd[vehicleid][v_model]));
					format(strContent, 2048, "%s\n"COL_RED"Jeśli odrzucisz rachunek, naprawa nie zostanie zrealizowana.", strContent);
					format(strContent, 2048, "%s\n\n"COL_RED"» "COL_WHITE"Podsumowanie:", strContent);
					format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Pojazd: "COL_BLUE"%s "COL_GREY"(UID: %d)", strContent, GetVehicleName(pojazd[vehicleid][v_model]), pojazd[vehicleid][v_id]);
					format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Komponent: "COL_LIME"%s", strContent, VehicleDamages[x][vd_title]);
					format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Koszt: "COL_GREEN"%d$", strContent, floatround(fix_price));
					format(strContent, 2048, "%s\n"COL_ORANGE"• "COL_EASY"Aktualny stan komponentu: "COL_RED"AWARIA", strContent);
					format(strContent, 2048, "%s\n\n"COL_GREEN"Czy zgadzasz się na naprawę i przyjmujesz rachunek?", strContent);
					Dialog_Show(playerid, OBDFIXCONFIRM, DIALOG_STYLE_MSGBOX, strTitle, strContent, "Akceptuj", "Odrzuc");
					SetPVarInt(playerid, "cache_odbfix_component", x);
					SetPVarInt(playerid, "cache_odbfix_vehicleid", vehicleid);
					SetPVarInt(playerid, "cache_odbfix_price", floatround(fix_price));
					SetPVarInt(playerid, "cache_odbfix_mechanicid", playerid);
					return 1;
				}
			}
			Error(playerid, "Nie wykryto awarii.");
		}
		else Error(playerid, "Tego pojazdu nie można naprawić w ten sposób.");
	}
	else Error(playerid, "Pojazd możesz naprawić przy bazie pomocy drogowej.");
	return 1;
}


