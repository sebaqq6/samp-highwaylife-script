#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define RELEASED(%0) \
	(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))
#define HOLDING(%0) \
	((newkeys & (%0)) == (%0))
#define PRESSING(%0,%1) (%0 & (%1))
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(!gracz[playerid][loggedin]) return 1;
	ResetIdleAFK(playerid);
	if(RELEASED(KEY_SPRINT) && gracz[playerid][delivered_canexit]) return DeliveredWindowHide(playerid);
	if(RELEASED(KEY_SPRINT) && gracz[playerid][td_dokumenty] > 0) return Dokument_Hide(playerid);
	if(RELEASED(KEY_SECONDARY_ATTACK) && Event_StopAnim(playerid)) return 1;
	Vehicle_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	if(gracz[playerid][truckbuy_status]) return 1;//!!!!!!!!!!!!!!!!!!!!!!klawisze tylko dla vehicles.inc jesli gracz jest w wybieralce truck salon
	Object_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	Spec_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	gym_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	POOL_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	Basket_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	rope_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	ZoneCreate_OnPlayerKeyStateCh(playerid, newkeys, oldkeys);
	if(PRESSED(KEY_SECONDARY_ATTACK) && gracz[playerid][bw] == 0) EnterDoor(playerid);
	House_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	football_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	TASER_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	if(PRESSED(KEY_HANDBRAKE) && gracz[playerid][loading_objects] == false) ShowBorderCrossList(playerid); 
	if(PRESSED(KEY_FIRE)) Event_DrunkAlcohol(playerid);
	if(PRESSED(KEY_FIRE) || PRESSED(KEY_SECONDARY_ATTACK)) 
	{
		if(gracz[playerid][kajdanki] == true) MessageGUIEx(playerid, "Info", "Jesteś skuty, nie możesz atakować.\n"COL_RED"Twoja postać nie zadaje DMG.");
	}
	//sniper fix - attached object
	if(PRESSING(newkeys, KEY_HANDBRAKE))
	{
		if(GetPlayerWeapon(playerid) == 34)
		{
			RemoveUsedAccessories(playerid);
		}
	}
	else if(RELEASED(KEY_HANDBRAKE))
	{
		if(GetPlayerWeapon(playerid) == 34)
		{
			LoadUsedAccessories(playerid);
		}
	}
	//szybka akcja
	FISHSYS_OnPlayerKeyStateChange(playerid, newkeys);
	if(PRESSED(KEY_HANDBRAKE) && !IsPlayerInAnyVehicle(playerid)) KEY_FastAction(playerid);
	else if(PRESSED(KEY_CROUCH) && IsPlayerInAnyVehicle(playerid)) KEY_FastAction(playerid);
	return 1;
}

task KEY_FastAction(playerid)
{
	//wchodzenie/schodzenie szybkie na/z duty frakcji
	if(gracz[playerid][frakcja] != 0)//ma frakcje
	{
		new fid = gracz[playerid][frakcja];
		if(IsPlayerInRangeOfPoint(playerid, 2.0, fractions[fid][fr_dutyX], fractions[fid][fr_dutyY], fractions[fid][fr_dutyZ]))
		{
			if(IsPlayerOnDutyFraction(playerid))
			{
				PC_EmulateCommand(playerid, "/duty stop");
			}
			else
			{
				PC_EmulateCommand(playerid, "/duty start");
			}
			return 1;
		}
	}
	//wchodzenie/schodzenie szybkie na/z duty frakcji
	if(gracz[playerid][firma] != 0)
	{
		new cid = gracz[playerid][firma];
		if(IsPlayerInRangeOfPoint(playerid, 2.0, company[cid][cny_dutyX], company[cid][cny_dutyY], company[cid][cny_dutyZ]))
		{
			if(IsPlayerOnDutyCompany(playerid))
			{
				PC_EmulateCommand(playerid, "/cduty stop");
			}
			else
			{
				PC_EmulateCommand(playerid, "/cduty start");
			}
			return 1;
		}
	}
	//bank
	if(IsPlayerRangeOfBank(playerid))
	{
		PC_EmulateCommand(playerid, "/bank");
		return 1;
	}
	//ładowanie/rozładowanie towaru
	if(gracz[playerid][objective_status])
	{
		if(IsPlayerInRangeOfPoint(playerid, 13.0, gracz[playerid][objective_X], gracz[playerid][objective_Y], gracz[playerid][objective_Z]))
		{
			if(IsValidDynamic3DTextLabel(gracz[playerid][objective_text3d]))
			{
				new label_string[1024];
				GetDynamic3DTextLabelText(gracz[playerid][objective_text3d], label_string);
				new find_command_list[4][32] =
				{
					{"/zlecenie odbierz"},
					{"/zlecenie dostarcz"},
					{"/kontrakt zaladuj"},
					{"/kontrakt rozladuj"}
				};
				for(new search; search < 4; search++)
				{
					if(strfind(label_string, find_command_list[search], true) != -1)
					{
						PC_EmulateCommand(playerid, find_command_list[search]);
						return 1;
					}
				}
			}
		}
	}
	//sklep
	if(IsPlayerInRangeOfShop(playerid))
	{
		PC_EmulateCommand(playerid, "/sklep");
		return 1;
	}
	//lunapark
	if(IsPlayerInRangeOfPoint(playerid, 1.2, XYZ_LUNAPARK))
	{
		PC_EmulateCommand(playerid, "/lunapark");
		return 1;
	}
	//wędkowanie
	if(IsPlayerInFishingPoint(playerid))
	{
		if(Spam(playerid, SPAM_STARTFISH, 2, false)) return 1;
		if(GetItemValueForPlayer(playerid, 79) == 0) return Error(playerid, "Nie posiadasz wędki, możesz ją kupić w sklepie.");
		StartFish(playerid);
		return 1;
	}
	//sprzedaż ryb
	if(IsPlayerInRangeOfPoint(playerid, 4.0, XYZ_SELLFISH))
	{
		SellFish(playerid);
		return 1;
	}
	return 1;
}