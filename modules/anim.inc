enum aa_data
{
	aa_id,
	aa_cmd[32],
	aa_lib[32],
	aa_name[32],
	Float:aa_speed,
	aa_opt1,
	aa_opt2,
	aa_opt3,
	aa_opt4,
	aa_opt5,
	aa_action
};

#define MAX_ANIMS 300
new anim[MAX_ANIMS][aa_data];

stock Init_Anims()
{
	mq_format("SELECT * FROM `anims` ORDER BY `anim_command` ASC;");
	mq_send("LoadAnimsFromDB");
	return 1;
}

task LoadAnimsFromDB()
{
	mq_getdata();
	if(rekordy)
	{
		new i; 
		while(i < rekordy)
		{
			cache_get_value_name_int(i, "id", 			anim[i][aa_id]);
			cache_get_value_name(i, "anim_command", anim[i][aa_cmd], 32);
			cache_get_value_name(i, "anim_lib", anim[i][aa_lib], 32);
			cache_get_value_name(i, "anim_name", anim[i][aa_name], 32);
			cache_get_value_name_float(i, "anim_speed", 			anim[i][aa_speed]);
			cache_get_value_name_int(i, "anim_opt1", 			anim[i][aa_opt1]);
			cache_get_value_name_int(i, "anim_opt2", 			anim[i][aa_opt2]);
			cache_get_value_name_int(i, "anim_opt3", 			anim[i][aa_opt3]);
			cache_get_value_name_int(i, "anim_opt4", 			anim[i][aa_opt4]);
			cache_get_value_name_int(i, "anim_opt5", 			anim[i][aa_opt5]);
			cache_get_value_name_int(i, "anim_action", 			anim[i][aa_action]);
			i++;
		}
	}
	return 1;
}


CMD:anim(playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid)) return Error(playerid, "Nie można używać animacji w pojeździe.");
	new anim_cmd[16];
	format(anim_cmd, 16, ".%s", params);
	new anim_arrid = -1;
	for(new sa; sa < MAX_ANIMS; sa++)
	{
		if(anim[sa][aa_id] == 0) continue;
		if(compare(anim_cmd, anim[sa][aa_cmd])) anim_arrid = sa;
	}
	if(anim_arrid != -1) 
	{
		gui_cache[playerid][0][0] = anim_arrid;
		dialog_ANIMLIST(playerid, true, 0, "null");
	}
	else
	{
		new strAnimList[2048];
		format(strAnimList, 2048, "Komenda");
		new count_listitem;
		for(new a; a < MAX_ANIMS; a++)
		{
			if(anim[a][aa_id] == 0) continue;
			format(strAnimList, 2048, "%s\n%s", strAnimList, anim[a][aa_cmd]);
			gui_cache[playerid][count_listitem][0] = a;
			count_listitem++;
		}
		Dialog_Show(playerid, ANIMLIST, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_GREEN"Lista animacji"COL_RED" «•", strAnimList, "Wybierz", "Anuluj");
	}
	return 1;
}

Dialog:ANIMLIST(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(gracz[playerid][bw] > 0 || gracz[playerid][wypadek] > 0) return Error(playerid, "Nie możesz w tym momencie używać animacji.");
	new a = gui_cache[playerid][listitem][0];
	if(anim[a][aa_action] == 0)
	{
		ApplyAnimation(playerid, anim[a][aa_lib], anim[a][aa_name], anim[a][aa_speed], anim[a][aa_opt1], anim[a][aa_opt2], anim[a][aa_opt3], anim[a][aa_opt4], anim[a][aa_opt5], 1);
		gracz[playerid][whileanim] = 1;
		LeftNotifyShow(playerid, "Animacje", "Uby zakonczyc animacje, wcisnij: ~r~ENTER", LN_GREY, 30);
	}
	else//ACTION:
	{
		SetPlayerSpecialAction(playerid, anim[a][aa_action]);
		gracz[playerid][whileanim] = 2;
		LeftNotifyShow(playerid, "Animacje", "Uby zakonczyc animacje, wcisnij: ~r~ENTER", LN_GREY, 30);
	}
	return 1;
}

task Event_StopAnim(playerid)
{
	if(gracz[playerid][whileanim] == 1)
	{
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 1, 0, 0, 0, 0, 0, 0);
		LeftNotifyShow(playerid, "Animacje", "Animacja zostala przerwana.", LN_GREY, 5);
		gracz[playerid][whileanim] = 0;
		return 1;
	}
	if(gracz[playerid][whileanim] == 2)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		SetPlayerSkin(playerid, GetPlayerSkin(playerid));
		LeftNotifyShow(playerid, "Animacje", "Animacja zostala przerwana.", LN_GREY, 5);
		gracz[playerid][whileanim] = 0;
		return 1;
	}
	return 0;
}