#include "modules/textdraw_static.inc"
#include "modules/textdraw_dynamic.inc"

stock Init_TextDrawPlayer(playerid)
{
	Init_TextDrawPlayerStatic(playerid);
	Init_TextDrawPlayerDynamic(playerid);
	return 1;
}

stock Init_TextDraw()
{
	Init_TextDrawStatic();
	Init_TextDrawDynamic();
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	confcarg_OnPlayerClickTextDraw(playerid, clickedid);
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	return 1;
}

stock ShowHud(playerid)
{
	TextDrawShowForPlayer(playerid, pgHUD0);
	TextDrawShowForPlayer(playerid, pgHUD1);
	TextDrawShowForPlayer(playerid, pgHUD2);
	TextDrawShowForPlayer(playerid, pgHUD3);
	TextDrawShowForPlayer(playerid, pgHUD6);
	TextDrawShowForPlayer(playerid, pgHUD7);
	TextDrawShowForPlayer(playerid, pgHUD8);
	TextDrawShowForPlayer(playerid, td_g_clock0);
	TextDrawShowForPlayer(playerid, td_g_clock1);
	TextDrawShowForPlayer(playerid, td_g_ver);
	HUD_UpdateNickAndID(playerid);
	HUD_UpdateKursy(playerid);
	HUD_SetFrakcja(playerid, COLOR_GREY, "Bezrobotny");
	HUD_UpdateHP(playerid);
	HUD_UpdateARMOUR(playerid);
	HUD_UpdateSTAMINA(playerid);
	HUD_UpdateKASA(playerid);
	gracz[playerid][hud_lastskin] = -1;
	gracz[playerid][hud_lastweapon] = -1;
	gracz[playerid][hud_lastammo] = -1;
	HUD_UpdateSKIN(playerid);
	HUD_UpdateWEAPON(playerid);
	return 1;
}

stock LeftNotifyShow(playerid, title[], content[], type = LN_GREY, time = 5)
{
	if(playerid == INVALID_PLAYER_ID) return 0;
	switch(type)
	{
		case LN_RED://red//error/misja
		{
			PlayerTextDrawColor(playerid, td_leftann_title[playerid], -2147483393);
			PlayerTextDrawColor(playerid, td_leftann_ball[playerid], -2147483393);
			PlayerTextDrawColor(playerid, td_leftann_icon[playerid], -1);
			PlayerTextDrawFont(playerid, td_leftann_icon[playerid], 2);
			PlayerTextDrawSetString(playerid, td_leftann_icon[playerid], "!");
			if(gracz[playerid][leftnotify_customsound] != 0)
			{
				PlayerPlaySound(playerid, gracz[playerid][leftnotify_customsound], 0.0, 0.0, 0.0);
				gracz[playerid][leftnotify_customsound] = 0;
			}
			else PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
		case LN_GREEN://green//info/sukcesy
		{
			PlayerTextDrawColor(playerid, td_leftann_title[playerid], 8388863);
			PlayerTextDrawColor(playerid, td_leftann_ball[playerid], 8388863);
			PlayerTextDrawColor(playerid, td_leftann_icon[playerid], -1);
			PlayerTextDrawFont(playerid, td_leftann_icon[playerid], 1);
			PlayerTextDrawSetString(playerid, td_leftann_icon[playerid], "i");
			if(gracz[playerid][leftnotify_customsound] != 0)
			{
				PlayerPlaySound(playerid, gracz[playerid][leftnotify_customsound], 0.0, 0.0, 0.0);
				gracz[playerid][leftnotify_customsound] = 0;
			}
			else PlayerPlaySound(playerid, 1055, 0.0, 0.0, 0.0);
		}
		case LN_YELLOW://yellow
		{
			PlayerTextDrawColor(playerid, td_leftann_title[playerid], -65281);
			PlayerTextDrawColor(playerid, td_leftann_ball[playerid], -65281);
			PlayerTextDrawColor(playerid, td_leftann_icon[playerid], -1);
			PlayerTextDrawFont(playerid, td_leftann_icon[playerid], 2);
			if(gracz[playerid][leftnotify_customsound] != 0)
			{
				PlayerPlaySound(playerid, gracz[playerid][leftnotify_customsound], 0.0, 0.0, 0.0);
				gracz[playerid][leftnotify_customsound] = 0;
			}
			else PlayerPlaySound(playerid, 1150, 0.0, 0.0, 0.0);
		}
		case LN_GREY://grey/ogólno dostepny
		{
			PlayerTextDrawColor(playerid, td_leftann_title[playerid], -2139062017);
			PlayerTextDrawColor(playerid, td_leftann_ball[playerid], -2139062017);
			PlayerTextDrawColor(playerid, td_leftann_icon[playerid], -1);
			PlayerTextDrawFont(playerid, td_leftann_icon[playerid], 2);
			PlayerTextDrawSetString(playerid, td_leftann_icon[playerid], "!");
			if(gracz[playerid][leftnotify_customsound] != 0)
			{
				PlayerPlaySound(playerid, gracz[playerid][leftnotify_customsound], 0.0, 0.0, 0.0);
				gracz[playerid][leftnotify_customsound] = 0;
			}
			else PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
		}
		case LN_BLUE:
		{
			PlayerTextDrawColor(playerid, td_leftann_title[playerid], 0x09a4d1FF);
			PlayerTextDrawColor(playerid, td_leftann_ball[playerid], 0x09a4d1FF);
			PlayerTextDrawColor(playerid, td_leftann_icon[playerid], -1);
			PlayerTextDrawFont(playerid, td_leftann_icon[playerid], 2);
			PlayerTextDrawSetString(playerid, td_leftann_icon[playerid], "!");
			if(gracz[playerid][leftnotify_customsound] != 0)
			{
				PlayerPlaySound(playerid, gracz[playerid][leftnotify_customsound], 0.0, 0.0, 0.0);
				gracz[playerid][leftnotify_customsound] = 0;
			}
			else PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
	}
	new str[512];
	format(str, 512, "%s", title);
	PlayerTextDrawSetString(playerid,  td_leftann_title[playerid], str);
	format(str, 512, "~n~%s", content);
	PlayerTextDrawSetString(playerid,  td_leftann_content[playerid], str);
	PlayerTextDrawShow(playerid, td_leftann_title[playerid]);
	PlayerTextDrawShow(playerid, td_leftann_content[playerid]);
	PlayerTextDrawShow(playerid, td_leftann_ball[playerid]);
	PlayerTextDrawShow(playerid, td_leftann_icon[playerid]);
	if(time) gracz[playerid][time_leftnotify] = serwer[time_timestamp]+time;	
	else gracz[playerid][time_leftnotify] = 0;
	return 1;
}

stock LeftNotifyHide(playerid)
{
	PlayerTextDrawHide(playerid, td_leftann_title[playerid]);
	PlayerTextDrawHide(playerid, td_leftann_content[playerid]);
	PlayerTextDrawHide(playerid, td_leftann_ball[playerid]);
	PlayerTextDrawHide(playerid, td_leftann_icon[playerid]);	
	return 1;
}

task Process_LeftNotify(playerid)
{
	if(gracz[playerid][time_leftnotify] != 0)
	{
		if(gracz[playerid][time_leftnotify] < serwer[time_timestamp])
		{
			gracz[playerid][time_leftnotify] = 0;
			LeftNotifyHide(playerid);
		}
	}
	return 1;
}

forward ShowTDHighLifeLogon(playerid, step);
public ShowTDHighLifeLogon(playerid, step)
{
	//new strHighway[24];
	//const speed = 300;
	//const soundhl = 1190;
	//printf("ShowTDHighLifeLogon: %d, %d", playerid, step);
	//if(step == 0) gracz[playerid][hl_logon_block] = false;
	if(gracz[playerid][hl_logon_block]) return 1;
	PlayerPlaySound(playerid, 1148, 0, 0, 0);
	gracz[playerid][hl_logon_block] = true;
	/*switch(step)
	{
		case 0:
		{
			format(strHighway, 24,  "H");
			PlayerTextDrawSetString(playerid, hl_logon0[playerid], strHighway);
			PlayerTextDrawShow(playerid, hl_logon0[playerid]);
			SetTimerEx("ShowTDHighLifeLogon", speed, false, "dd", playerid, step+1);
			PlayerPlaySound(playerid, soundhl, 0, 0, 0);
		}
		case 1:
		{
			format(strHighway, 24,  "Hi");
			PlayerTextDrawSetString(playerid, hl_logon0[playerid], strHighway);
			PlayerTextDrawShow(playerid, hl_logon0[playerid]);
			SetTimerEx("ShowTDHighLifeLogon", speed, false, "dd", playerid, step+1);
			PlayerPlaySound(playerid, soundhl, 0, 0, 0);
		}
		case 2:
		{
			format(strHighway, 24,  "Hig");
			PlayerTextDrawSetString(playerid, hl_logon0[playerid], strHighway);
			PlayerTextDrawShow(playerid, hl_logon0[playerid]);
			SetTimerEx("ShowTDHighLifeLogon", speed, false, "dd", playerid, step+1);
			PlayerPlaySound(playerid, soundhl, 0, 0, 0);
		}
		case 3:
		{
			format(strHighway, 24,  "High");
			PlayerTextDrawSetString(playerid, hl_logon0[playerid], strHighway);
			PlayerTextDrawShow(playerid, hl_logon0[playerid]);
			SetTimerEx("ShowTDHighLifeLogon", speed, false, "dd", playerid, step+1);
			PlayerPlaySound(playerid, soundhl, 0, 0, 0);
		}
		case 4:
		{
			format(strHighway, 24,  "Highw");
			PlayerTextDrawSetString(playerid, hl_logon0[playerid], strHighway);
			PlayerTextDrawShow(playerid, hl_logon0[playerid]);
			SetTimerEx("ShowTDHighLifeLogon", speed, false, "dd", playerid, step+1);
			PlayerPlaySound(playerid, soundhl, 0, 0, 0);
		}
		case 5:
		{
			format(strHighway, 24,  "Highwa");
			PlayerTextDrawSetString(playerid, hl_logon0[playerid], strHighway);
			PlayerTextDrawShow(playerid, hl_logon0[playerid]);
			SetTimerEx("ShowTDHighLifeLogon", speed, false, "dd", playerid, step+1);
			PlayerPlaySound(playerid, soundhl, 0, 0, 0);
		}
		case 6:
		{
			format(strHighway, 24,  "Highway");
			PlayerTextDrawSetString(playerid, hl_logon0[playerid], strHighway);
			PlayerTextDrawShow(playerid, hl_logon0[playerid]);
			SetTimerEx("ShowTDHighLifeLogon", speed+300, false, "dd", playerid, step+1);
			PlayerPlaySound(playerid, soundhl, 0, 0, 0);
		}
		case 7:
		{
			PlayerTextDrawShow(playerid, hl_logon1[playerid]);
			PlayerPlaySound(playerid, 1148, 0, 0, 0);
			gracz[playerid][hl_logon_block] = true;
		}
	}*/
	return 1;
}

stock HideTDHighLifeLogon(playerid)
{
	gracz[playerid][hl_logon_block]  = true;
	TextDrawHideForPlayer(playerid, logo_hl);
	//PlayerTextDrawHide(playerid, hl_logon0[playerid]);
	//PlayerTextDrawHide(playerid, hl_logon1[playerid]);
	return 1;
}

stock ShowPanorama(playerid)
{
	TextDrawShowForPlayer(playerid, logo_hl);
	TextDrawShowForPlayer(playerid, panorama0);
	TextDrawShowForPlayer(playerid, panorama1);
	return 1;
}

stock HidePanorama(playerid)
{
	TextDrawHideForPlayer(playerid, logo_hl);
	TextDrawHideForPlayer(playerid, panorama0);
	TextDrawHideForPlayer(playerid, panorama1);
	return 1;
}

stock UpdateScriptVersionTD(ver[])
{
	TextDrawSetString(td_g_ver, ver);
	return 1;
}

stock HUD_UpdateNickAndID(playerid)
{
	new strTemp[64];
	format(strTemp, 64, "%s~w~(%d)", nick(playerid), playerid);
	PlayerTextDrawColor(playerid, pHUD2[playerid], (gracz[playerid][last_playercolor] | 0x000000FF));
	PlayerTextDrawSetString(playerid, pHUD2[playerid], strTemp);
	PlayerTextDrawShow(playerid, pHUD2[playerid]);
	return 1;
}

stock HUD_UpdateKursy(playerid)
{
	new strTemp[16];
	format(strTemp, 16, "%d", gracz[playerid][kursy]);
	PlayerTextDrawSetString(playerid, pHUD3[playerid], strTemp);
	PlayerTextDrawShow(playerid, pHUD3[playerid]);
	return 1;
}

stock HUD_SetFrakcja(playerid, color, str_fractionname[])
{
	PlayerTextDrawSetString(playerid, pHUD4[playerid], str_fractionname);
	PlayerTextDrawColor(playerid, pHUD4[playerid], color);
	PlayerTextDrawShow(playerid, pHUD4[playerid]);
	return 1;
}

stock HUD_UpdateHP(playerid)
{
	new strProc[16];
	format(strProc, 16, "%d%%", gracz[playerid][HP]);
	PlayerTextDrawSetString(playerid, pHUD9[playerid], strProc);
	PlayerTextDrawShow(playerid, pHUD9[playerid]);
	new Float:text_size = float(gracz[playerid][HP])*-0.63899993;
	PlayerTextDrawTextSize(playerid, pHUD5[playerid], text_size, 8.711102);
	PlayerTextDrawShow(playerid, pHUD5[playerid]);
	return 1;
}

stock HUD_UpdateARMOUR(playerid)
{
	new strProc[16];
	format(strProc, 16, "%d%%", gracz[playerid][armour]);
	PlayerTextDrawSetString(playerid, pHUD10[playerid], strProc);
	PlayerTextDrawShow(playerid, pHUD10[playerid]);
	new Float:text_size = float(gracz[playerid][armour])*-0.63899993;
	PlayerTextDrawTextSize(playerid, pHUD6[playerid], text_size, 8.711102);
	PlayerTextDrawShow(playerid, pHUD6[playerid]);
	return 1;
}

stock HUD_UpdateSTAMINA(playerid)
{
	new strProc[16];
	format(strProc, 16, "%d%%", gracz[playerid][stamina]);
	PlayerTextDrawSetString(playerid, pHUD11[playerid], strProc);
	PlayerTextDrawShow(playerid, pHUD11[playerid]);
	new Float:text_size = float(gracz[playerid][stamina])*-0.63899993;
	PlayerTextDrawTextSize(playerid, pHUD7[playerid], text_size, 8.711102);
	PlayerTextDrawShow(playerid, pHUD7[playerid]);
	return 1;
}

stock HUD_UpdateKASA(playerid)
{
	new strTemp[16];
	format(strTemp, 16, "%s$", AddCommasToInt(gracz[playerid][kasa], " "));
	PlayerTextDrawSetString(playerid, pHUD0[playerid], strTemp);
	PlayerTextDrawShow(playerid, pHUD0[playerid]);
	return 1;
}


stock HUD_UpdateSKIN(playerid)
{
	new getplayskin = GetPlayerSkin(playerid);
	if(gracz[playerid][hud_lastskin] != getplayskin)
	{
		gracz[playerid][hud_lastskin] = getplayskin;
		PlayerTextDrawSetPreviewModel(playerid, pHUD8[playerid], getplayskin);
		PlayerTextDrawShow(playerid, pHUD8[playerid]);
	}
	return 1;
}

stock HUD_UpdateWEAPON(playerid)
{
	new getplayweap = GetPlayerWeapon(playerid);
	if(gracz[playerid][hud_lastweapon] != getplayweap)
	{
		gracz[playerid][hud_lastweapon] = getplayweap;
		PlayerTextDrawSetString(playerid, pHUD1[playerid], WeaponNameShortTD(getplayweap));
		PlayerTextDrawShow(playerid, pHUD1[playerid]);
	}
	new getplayammo = GetPlayerAmmo(playerid);
	if(gracz[playerid][hud_lastammo] != getplayammo)
	{
		gracz[playerid][hud_lastammo] = getplayammo;
		if(gracz[playerid][hud_lastammo] == 0)
		{
			PlayerTextDrawHide(playerid, pHUD12[playerid]);
			if(gracz[playerid][hud_lastammo_bg] == true)
			{
				TextDrawHideForPlayer(playerid, pgHUD10);
				gracz[playerid][hud_lastammo_bg] = false;
			}
		}
		else
		{
			new strAmmo[24];
			format(strAmmo, 24, "Ammo: %d", gracz[playerid][hud_lastammo]);
			PlayerTextDrawSetString(playerid, pHUD12[playerid], strAmmo);
			PlayerTextDrawShow(playerid, pHUD12[playerid]);
			if(gracz[playerid][hud_lastammo_bg] == false)
			{
				TextDrawShowForPlayer(playerid, pgHUD10);
				gracz[playerid][hud_lastammo_bg] = true;
			}
		}
	}


	return 1;
}

stock HUD_UpdateINFO(text[], icon, color = 12028415)
{
	TextDrawColor(pgHUD9, color);
	TextDrawSetString(pgHUD9, text);
	if(serwer[hud_lasticon] != icon)
	{
		switch(icon)
		{
			case 0: 
			{
				TextDrawSetString(pgHUD2, "mdl-2001:hud_logo");
				TextDrawColor(pgHUD2, -1);
			}
			case 1: 
			{
				TextDrawSetString(pgHUD2, "mdl-2001:hud_icon_join");
				TextDrawColor(pgHUD2, 0x00FF00FF);
			}
			case 2: 
			{
				TextDrawSetString(pgHUD2, "mdl-2001:hud_icon_join");
				TextDrawColor(pgHUD2, 0xFF0000FF);
			}
			case 3: 
			{
				TextDrawSetString(pgHUD2, "mdl-2001:hud_icon_delivery");
				TextDrawColor(pgHUD2, 0xFF4D00FF);
			}
		}
	}
	for(new i = PlayerPoolSize(); i != -1; i--)
	{
		if(gracz[i][loggedin])
		{
			TextDrawShowForPlayer(i, pgHUD9);
			if(serwer[hud_lasticon] != icon) TextDrawShowForPlayer(i, pgHUD2);
		}
	}
	if(serwer[hud_lasticon] != icon) serwer[hud_lasticon] = icon;
	return 1;
}

stock CarHUD_Show(playerid)
{
	if(gracz[playerid][carhud_status] > 0) return 0;
	gracz[playerid][carhud_status] = 1;
	TextDrawShowForPlayer(playerid, td_G_carhud0);
	TextDrawShowForPlayer(playerid, td_G_carhud1);
	TextDrawShowForPlayer(playerid, td_G_carhud2);
	TextDrawShowForPlayer(playerid, td_G_carhud3);
	TextDrawShowForPlayer(playerid, td_G_carhud4);
	TextDrawShowForPlayer(playerid, td_G_carhud5);
	TextDrawShowForPlayer(playerid, td_G_carhud6);
	TextDrawShowForPlayer(playerid, td_G_carhud7);
	TextDrawShowForPlayer(playerid, td_G_carhud8);
	TextDrawShowForPlayer(playerid, td_G_carhud9);
	TextDrawShowForPlayer(playerid, td_G_carhud10);
	TextDrawShowForPlayer(playerid, td_G_carhud11);
	TextDrawShowForPlayer(playerid, td_G_carhud12);
	TextDrawShowForPlayer(playerid, td_G_carhud13);
	TextDrawShowForPlayer(playerid, td_G_carhud14);
	TextDrawShowForPlayer(playerid, td_G_carhud15);
	TextDrawShowForPlayer(playerid, td_G_carhud16);
	TextDrawShowForPlayer(playerid, td_G_carhud17);
	TextDrawShowForPlayer(playerid, td_G_carhud18);
	TextDrawShowForPlayer(playerid, td_G_carhud19);
	TextDrawShowForPlayer(playerid, td_G_carhud20);
	TextDrawShowForPlayer(playerid, td_G_carhud21);
	TextDrawShowForPlayer(playerid, td_G_carhud22);
	TextDrawShowForPlayer(playerid, td_G_carhud23);
	PlayerTextDrawShow(playerid, td_P_carhud0[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud1[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud2[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud3[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud4[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud5[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud6[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud7[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud8[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud9[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud10[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud11[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud12[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud13[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud14[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud15[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud16[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud17[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud18[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud19[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud20[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud21[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud22[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud23[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud24[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud25[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud26[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud27[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud28[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud29[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud30[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud31[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud32[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud33[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud34[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud35[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud36[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud37[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud38[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud39[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud40[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud41[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud42[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud43[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud44[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud45[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud46[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud47[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud48[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud49[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud50[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud51[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud52[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud53[playerid]);
	CarHUD_SpeedLight(playerid, false);
	CarHUD_FuelWarning(playerid, false);
	CarHUD_TempWarning(playerid, false);
	CarHUD_DistanceLight(playerid, false);
	CarHUD_SERVICE(playerid, false);
	CarHUD_Battery(playerid, false);
	CarHUD_HandBrake(playerid, false);
	CarHUD_Seatbelts(playerid, false);
	//NITRO: PlayerTextDrawShow(playerid, td_P_carhud53[playerid]);
	//PlayerTextDrawShow(playerid, td_p_gpsdistance[playerid]);
	Radio_Show(playerid);
	return 1;
}

stock CarHUD_Hide(playerid)
{	
	if(gracz[playerid][carhud_status] == 0) return 0;
	gracz[playerid][carhud_status] = 0;
	TextDrawHideForPlayer(playerid, td_G_carhud0);
	TextDrawHideForPlayer(playerid, td_G_carhud1);
	TextDrawHideForPlayer(playerid, td_G_carhud2);
	TextDrawHideForPlayer(playerid, td_G_carhud3);
	TextDrawHideForPlayer(playerid, td_G_carhud4);
	TextDrawHideForPlayer(playerid, td_G_carhud5);
	TextDrawHideForPlayer(playerid, td_G_carhud6);
	TextDrawHideForPlayer(playerid, td_G_carhud7);
	TextDrawHideForPlayer(playerid, td_G_carhud8);
	TextDrawHideForPlayer(playerid, td_G_carhud9);
	TextDrawHideForPlayer(playerid, td_G_carhud10);
	TextDrawHideForPlayer(playerid, td_G_carhud11);
	TextDrawHideForPlayer(playerid, td_G_carhud12);
	TextDrawHideForPlayer(playerid, td_G_carhud13);
	TextDrawHideForPlayer(playerid, td_G_carhud14);
	TextDrawHideForPlayer(playerid, td_G_carhud15);
	TextDrawHideForPlayer(playerid, td_G_carhud16);
	TextDrawHideForPlayer(playerid, td_G_carhud17);
	TextDrawHideForPlayer(playerid, td_G_carhud18);
	TextDrawHideForPlayer(playerid, td_G_carhud19);
	TextDrawHideForPlayer(playerid, td_G_carhud20);
	TextDrawHideForPlayer(playerid, td_G_carhud21);
	TextDrawHideForPlayer(playerid, td_G_carhud22);
	TextDrawHideForPlayer(playerid, td_G_carhud23);
	TextDrawHideForPlayer(playerid, td_G_carhud24);
	PlayerTextDrawHide(playerid, td_P_carhud0[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud1[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud2[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud3[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud4[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud5[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud6[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud7[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud8[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud9[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud10[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud11[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud12[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud13[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud14[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud15[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud16[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud17[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud18[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud19[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud20[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud21[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud22[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud23[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud24[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud25[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud26[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud27[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud28[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud29[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud30[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud31[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud32[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud33[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud34[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud35[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud36[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud37[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud38[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud39[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud40[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud41[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud42[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud43[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud44[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud45[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud46[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud47[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud48[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud49[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud50[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud51[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud52[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud53[playerid]);
	PlayerTextDrawHide(playerid, td_P_carhud54[playerid]);
	PlayerTextDrawHide(playerid, td_p_gpsdistance[playerid]);
	Radio_Hide(playerid);
	return 1;
}

#define CARHUD_KMH_COLOR1 0x27D400FF//0-100
#define CARHUD_KMH_COLOR2 0xFF9A00FF//101-200
#define CARHUD_KMH_COLOR3 0xFF0000FF//201-300
stock CarHUD_SetSpeed(playerid, value)
{
	if(gracz[playerid][carhud_status] == 0) return 0;
	//td_P_carhud
	new strTemp[32];
	format(strTemp, 32, "%03d km/h", value);
	PlayerTextDrawSetString(playerid, td_P_carhud17[playerid], strTemp);
	if(value == 0)
	{
		PlayerTextDrawColor(playerid, td_P_carhud0[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud1[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud2[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud3[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud4[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud5[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud6[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud7[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud8[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud9[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud10[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud11[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud12[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud13[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud14[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud15[playerid], -1);
	}
	else if(value >= 250)
	{
		PlayerTextDrawColor(playerid, td_P_carhud0[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud1[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud2[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud3[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud4[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud5[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud6[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud7[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud8[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud9[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud10[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud11[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud12[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud13[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud14[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud15[playerid], CARHUD_KMH_COLOR3);
	}
	else if(value >= 240)
	{
		PlayerTextDrawColor(playerid, td_P_carhud0[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud1[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud2[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud3[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud4[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud5[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud6[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud7[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud8[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud9[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud10[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud11[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud12[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud13[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud14[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud15[playerid], -1);
	}
	else if(value >= 230)
	{
		PlayerTextDrawColor(playerid, td_P_carhud0[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud1[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud2[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud3[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud4[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud5[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud6[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud7[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud8[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud9[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud10[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud11[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud12[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud13[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud14[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud15[playerid], -1);
	}
	else if(value >= 220)
	{
		PlayerTextDrawColor(playerid, td_P_carhud0[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud1[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud2[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud3[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud4[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud5[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud6[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud7[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud8[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud9[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud10[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud11[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud12[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud13[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud14[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud15[playerid], -1);
	}
	else if(value >= 210)
	{
		PlayerTextDrawColor(playerid, td_P_carhud0[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud1[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud2[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud3[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud4[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud5[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud6[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud7[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud8[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud9[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud10[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud11[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud12[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud13[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud14[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud15[playerid], -1);
	}
	else if(value >= 200)
	{
		PlayerTextDrawColor(playerid, td_P_carhud0[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud1[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud2[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud3[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud4[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud5[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud6[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud7[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud8[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud9[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud10[playerid], CARHUD_KMH_COLOR3);
		PlayerTextDrawColor(playerid, td_P_carhud11[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud12[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud13[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud14[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud15[playerid], -1);
	}
	else if(value >= 180)
	{
		PlayerTextDrawColor(playerid, td_P_carhud0[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud1[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud2[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud3[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud4[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud5[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud6[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud7[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud8[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud9[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud10[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud11[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud12[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud13[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud14[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud15[playerid], -1);
	}
	else if(value >= 160)
	{
		PlayerTextDrawColor(playerid, td_P_carhud0[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud1[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud2[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud3[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud4[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud5[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud6[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud7[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud8[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud9[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud10[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud11[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud12[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud13[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud14[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud15[playerid], -1);
	}
	else if(value >= 140)
	{
		PlayerTextDrawColor(playerid, td_P_carhud0[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud1[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud2[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud3[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud4[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud5[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud6[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud7[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud8[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud9[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud10[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud11[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud12[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud13[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud14[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud15[playerid], -1);
	}
	else if(value >= 120)
	{
		PlayerTextDrawColor(playerid, td_P_carhud0[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud1[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud2[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud3[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud4[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud5[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud6[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud7[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud8[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud9[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud10[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud11[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud12[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud13[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud14[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud15[playerid], -1);
	}
	else if(value >= 100)
	{
		PlayerTextDrawColor(playerid, td_P_carhud0[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud1[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud2[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud3[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud4[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud5[playerid], CARHUD_KMH_COLOR2);
		PlayerTextDrawColor(playerid, td_P_carhud6[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud7[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud8[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud9[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud10[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud11[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud12[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud13[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud14[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud15[playerid], -1);
	}
	else if(value >= 80)
	{
		PlayerTextDrawColor(playerid, td_P_carhud0[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud1[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud2[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud3[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud4[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud5[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud6[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud7[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud8[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud9[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud10[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud11[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud12[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud13[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud14[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud15[playerid], -1);
	}
	else if(value >= 60)
	{
		PlayerTextDrawColor(playerid, td_P_carhud0[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud1[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud2[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud3[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud4[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud5[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud6[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud7[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud8[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud9[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud10[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud11[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud12[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud13[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud14[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud15[playerid], -1);
	}
	else if(value >= 40)
	{
		PlayerTextDrawColor(playerid, td_P_carhud0[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud1[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud2[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud3[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud4[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud5[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud6[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud7[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud8[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud9[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud10[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud11[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud12[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud13[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud14[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud15[playerid], -1);
	}
	else if(value >= 20)
	{
		PlayerTextDrawColor(playerid, td_P_carhud0[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud1[playerid], CARHUD_KMH_COLOR1);
		PlayerTextDrawColor(playerid, td_P_carhud2[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud3[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud4[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud5[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud6[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud7[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud8[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud9[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud10[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud11[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud12[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud13[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud14[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud15[playerid], -1);
	}
	PlayerTextDrawShow(playerid, td_P_carhud0[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud1[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud2[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud3[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud4[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud5[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud6[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud7[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud8[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud9[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud10[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud11[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud12[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud13[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud14[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud15[playerid]);
	return 1;
}

stock CarHUD_SpeedLight(playerid, bool:status, color = -1958346497)
{
	if(gracz[playerid][carhud_status] == 0) return 0;
	if(status) PlayerTextDrawColor(playerid, td_P_carhud16[playerid], color);
	else PlayerTextDrawColor(playerid, td_P_carhud16[playerid], 255);
	PlayerTextDrawShow(playerid, td_P_carhud16[playerid]);
	return 1;
}

stock CarHUD_SetBlinker(playerid, blinkerleft, blinkerright)
{
	if(gracz[playerid][carhud_status] == 0) return 0;
	if(blinkerleft) PlayerTextDrawColor(playerid, td_P_carhud19[playerid], 8388863);
	else PlayerTextDrawColor(playerid, td_P_carhud19[playerid], 808464639);
	
	if(blinkerright) PlayerTextDrawColor(playerid, td_P_carhud18[playerid], 8388863);
	else PlayerTextDrawColor(playerid, td_P_carhud18[playerid], 808464639);
	PlayerTextDrawShow(playerid, td_P_carhud19[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud18[playerid]);
	return 1;
}

stock CarHUD_Light(playerid, status)
{
	if(gracz[playerid][carhud_status] == 0) return 0;
	if(status == 1)
	{
		PlayerTextDrawSetString(playerid, td_P_carhud21[playerid], "/");
		PlayerTextDrawSetString(playerid, td_P_carhud22[playerid], "/");
		PlayerTextDrawSetString(playerid, td_P_carhud23[playerid], "/");
		PlayerTextDrawColor(playerid, td_P_carhud20[playerid], 8388863);
		PlayerTextDrawColor(playerid, td_P_carhud21[playerid], 8388863);
		PlayerTextDrawColor(playerid, td_P_carhud22[playerid], 8388863);
		PlayerTextDrawColor(playerid, td_P_carhud23[playerid], 8388863);
	}
	else if(status == 2)
	{
		PlayerTextDrawSetString(playerid, td_P_carhud21[playerid], "-");
		PlayerTextDrawSetString(playerid, td_P_carhud22[playerid], "-");
		PlayerTextDrawSetString(playerid, td_P_carhud23[playerid], "-");
		PlayerTextDrawColor(playerid, td_P_carhud20[playerid], 0x36C7FFFF);
		PlayerTextDrawColor(playerid, td_P_carhud21[playerid], 0x36C7FFFF);
		PlayerTextDrawColor(playerid, td_P_carhud22[playerid], 0x36C7FFFF);
		PlayerTextDrawColor(playerid, td_P_carhud23[playerid], 0x36C7FFFF);
	}
	else
	{
		PlayerTextDrawSetString(playerid, td_P_carhud21[playerid], "/");
		PlayerTextDrawSetString(playerid, td_P_carhud22[playerid], "/");
		PlayerTextDrawSetString(playerid, td_P_carhud23[playerid], "/");
		PlayerTextDrawColor(playerid, td_P_carhud20[playerid], 255);
		PlayerTextDrawColor(playerid, td_P_carhud21[playerid], 255);
		PlayerTextDrawColor(playerid, td_P_carhud22[playerid], 255);
		PlayerTextDrawColor(playerid, td_P_carhud23[playerid], 255);
	}
	PlayerTextDrawShow(playerid, td_P_carhud20[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud21[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud22[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud23[playerid]);
	return 1;
}

stock CarHUD_FuelWarning(playerid, bool:status)
{
	if(gracz[playerid][carhud_status] == 0) return 0;
	if(status)
	{
		PlayerTextDrawColor(playerid, td_P_carhud24[playerid], 0xFF0000FF);
		PlayerTextDrawColor(playerid, td_P_carhud25[playerid], 0xFF0000FF);
		PlayerTextDrawColor(playerid, td_P_carhud26[playerid], 0xFF0000FF);
		PlayerTextDrawColor(playerid, td_P_carhud27[playerid], 0xFF0000FF);
		PlayerTextDrawColor(playerid, td_P_carhud28[playerid], 0xFF0000FF);
		PlayerTextDrawColor(playerid, td_P_carhud29[playerid], 0xF39C12FF);
	}
	else
	{
		PlayerTextDrawColor(playerid, td_P_carhud24[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud25[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud26[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud27[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud28[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud29[playerid], -1);
	}
	PlayerTextDrawShow(playerid, td_P_carhud24[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud25[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud26[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud27[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud28[playerid]);
	return 1;
}

stock CarHUD_SetFuel(playerid, value)
{
	if(gracz[playerid][carhud_status] == 0) return 0;
	if(value > 100) value = 100;
	if(value < 0) value = 0;
	new Float:result = -0.50126239*value;
	PlayerTextDrawTextSize(playerid, td_P_carhud29[playerid], 2.844326, result);
	PlayerTextDrawShow(playerid, td_P_carhud29[playerid]);
	return 1;
}

stock CarHUD_SetTemp(playerid, value)
{
	if(gracz[playerid][carhud_status] == 0) return 0;
	if(value > 100) value = 100;
	if(value < 0) value = 0;
	new Float:result = -0.50126239*value;
	PlayerTextDrawTextSize(playerid, td_P_carhud30[playerid], 2.844326, result);
	PlayerTextDrawShow(playerid, td_P_carhud30[playerid]);
	return 1;
}

stock CarHUD_TempWarning(playerid, bool:status)
{
	if(gracz[playerid][carhud_status] == 0) return 0;
	if(status)
	{
		PlayerTextDrawColor(playerid, td_P_carhud30[playerid], 0xF39C12FF);
		PlayerTextDrawColor(playerid, td_P_carhud31[playerid], 0xFF0000FF);
		PlayerTextDrawColor(playerid, td_P_carhud32[playerid], 0xFF0000FF);
		PlayerTextDrawColor(playerid, td_P_carhud33[playerid], 0xFF0000FF);
		PlayerTextDrawColor(playerid, td_P_carhud34[playerid], 0xFF0000FF);
		PlayerTextDrawColor(playerid, td_P_carhud35[playerid], 0xFF0000FF);
	}
	else
	{
		PlayerTextDrawColor(playerid, td_P_carhud30[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud31[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud32[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud33[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud34[playerid], -1);
		PlayerTextDrawColor(playerid, td_P_carhud35[playerid], -1);
	}
	PlayerTextDrawShow(playerid, td_P_carhud31[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud32[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud33[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud34[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud35[playerid]);
	return 1;
}

stock CarHUD_DistanceLight(playerid, bool:status, color = -2139094785)
{
	if(gracz[playerid][carhud_status] == 0) return 0;
	if(status) PlayerTextDrawColor(playerid, td_P_carhud36[playerid], color);
	else PlayerTextDrawColor(playerid, td_P_carhud36[playerid], 255);
	PlayerTextDrawShow(playerid, td_P_carhud36[playerid]);
	return 1;
}

stock CarHUD_SetDistance(playerid, distance)
{
	if(gracz[playerid][carhud_status] == 0) return 0;
	if(distance > 999999999) distance = 999999999;
	if(distance < 0) distance = 0;
	new strTemp[32];
	format(strTemp, 32, "%09d km", distance);
	PlayerTextDrawSetString(playerid, td_P_carhud37[playerid], strTemp);
	return 1;
}

stock CarHUD_SERVICE(playerid, bool:status)
{
	if(gracz[playerid][carhud_status] == 0) return 0;
	if(status)
	{
		PlayerTextDrawColor(playerid, td_P_carhud38[playerid], -5963521);
		PlayerTextDrawColor(playerid, td_P_carhud39[playerid], -5963521);
		PlayerTextDrawColor(playerid, td_P_carhud40[playerid], -5963521);
		PlayerTextDrawColor(playerid, td_P_carhud41[playerid], -5963521);
		PlayerTextDrawColor(playerid, td_P_carhud42[playerid], -5963521);
	}
	else
	{
		PlayerTextDrawColor(playerid, td_P_carhud38[playerid], 255);
		PlayerTextDrawColor(playerid, td_P_carhud39[playerid], 255);
		PlayerTextDrawColor(playerid, td_P_carhud40[playerid], 255);
		PlayerTextDrawColor(playerid, td_P_carhud41[playerid], 255);
		PlayerTextDrawColor(playerid, td_P_carhud42[playerid], 255);
	}
	PlayerTextDrawShow(playerid, td_P_carhud38[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud39[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud40[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud41[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud42[playerid]);
	return 1;
}


stock CarHUD_HandBrake(playerid, bool:status)
{
	if(gracz[playerid][carhud_status] == 0) return 0;
	if(status)
	{
		PlayerTextDrawColor(playerid, td_P_carhud43[playerid], -16776961);
		PlayerTextDrawColor(playerid, td_P_carhud45[playerid], -16776961);
		PlayerTextDrawColor(playerid, td_P_carhud46[playerid], -16776961);
	}
	else
	{
		PlayerTextDrawColor(playerid, td_P_carhud43[playerid], 255);
		PlayerTextDrawColor(playerid, td_P_carhud45[playerid], 255);
		PlayerTextDrawColor(playerid, td_P_carhud46[playerid], 255);
	}
	PlayerTextDrawShow(playerid, td_P_carhud43[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud45[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud46[playerid]);
	return 1;
}

stock CarHUD_Battery(playerid, bool:status)
{
	if(gracz[playerid][carhud_status] == 0) return 0;
	if(status)
	{
		PlayerTextDrawColor(playerid, td_P_carhud47[playerid], -16776961);
		PlayerTextDrawColor(playerid, td_P_carhud48[playerid], -16776961);
		PlayerTextDrawColor(playerid, td_P_carhud49[playerid], -16776961);
		PlayerTextDrawColor(playerid, td_P_carhud50[playerid], -16776961);
		PlayerTextDrawColor(playerid, td_P_carhud51[playerid], -16776961);
		PlayerTextDrawColor(playerid, td_P_carhud52[playerid], -16776961);
		PlayerTextDrawColor(playerid, td_P_carhud53[playerid], -16776961);
	}
	else
	{
		PlayerTextDrawColor(playerid, td_P_carhud47[playerid], 255);
		PlayerTextDrawColor(playerid, td_P_carhud48[playerid], 255);
		PlayerTextDrawColor(playerid, td_P_carhud49[playerid], 255);
		PlayerTextDrawColor(playerid, td_P_carhud50[playerid], 255);
		PlayerTextDrawColor(playerid, td_P_carhud51[playerid], 255);
		PlayerTextDrawColor(playerid, td_P_carhud52[playerid], 255);
		PlayerTextDrawColor(playerid, td_P_carhud53[playerid], 255);
	}
	PlayerTextDrawShow(playerid, td_P_carhud47[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud48[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud49[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud50[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud51[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud52[playerid]);
	PlayerTextDrawShow(playerid, td_P_carhud53[playerid]);
	return 1;
}

stock CarHUD_Seatbelts(playerid, bool:status)
{
	if(gracz[playerid][carhud_status] == 0) return 0;
	TextDrawHideForPlayer(playerid, td_G_carhud22);
	TextDrawHideForPlayer(playerid, td_G_carhud23);
	if(status)
	{
		TextDrawShowForPlayer(playerid, td_G_carhud22);
		TextDrawShowForPlayer(playerid, td_G_carhud23);
	}
	return 1;
}

stock CarHUD_Closed(playerid, bool:status)
{
	if(gracz[playerid][carhud_status] == 0) return 0;
	TextDrawHideForPlayer(playerid, td_G_carhud24);
	if(status)
	{
		TextDrawShowForPlayer(playerid, td_G_carhud24);
	}
	return 1;
}


stock CarHUD_DistanceGPS(playerid, Float:raw_dist)
{
	if(gracz[playerid][carhud_status] == 0) return 0;
	PlayerTextDrawHide(playerid, td_p_gpsdistance[playerid]);
	if(raw_dist > 0.0)
	{
		new strTemp[16];
		new Float:fine_km = (raw_dist/CONST_KM);
		if(fine_km <= 0.3) 
		{
			format(strTemp, 16, "< 300 m", fine_km);
			PlayerTextDrawBackgroundColor(playerid, td_p_gpsdistance[playerid], 0x00FF00FF);

		}
		else
		{
			format(strTemp, 16, "%0.1f km", fine_km);
			PlayerTextDrawBackgroundColor(playerid, td_p_gpsdistance[playerid], -16776961);
		}
		PlayerTextDrawSetString(playerid, td_p_gpsdistance[playerid], strTemp);
		PlayerTextDrawShow(playerid, td_p_gpsdistance[playerid]);
	}
	else if(raw_dist == -1.0)
	{
		PlayerTextDrawBackgroundColor(playerid, td_p_gpsdistance[playerid], 0x0000FFFF);
		PlayerTextDrawSetString(playerid, td_p_gpsdistance[playerid], "SZUKAM TRASY...");
		PlayerTextDrawShow(playerid, td_p_gpsdistance[playerid]);
	}
	return 1;
}

stock CarHUD_Nitro(playerid, value)
{
	if(gracz[playerid][carhud_status] == 0) return 0;
	if(value == -1)
	{
		PlayerTextDrawHide(playerid, td_P_carhud54[playerid]);
		return 1;
	}
	if(value > 15) value = 15;
	if(value < 0) value = 0;
	switch(value)
	{
		case 0..5: PlayerTextDrawColor(playerid, td_P_carhud54[playerid], 0xFF0000FF);
		case 6..11: PlayerTextDrawColor(playerid, td_P_carhud54[playerid], 0xFFFF00FF);
		default:  PlayerTextDrawColor(playerid, td_P_carhud54[playerid], 12189695);
	}
	new strBar[32];
	if(value == 0)
	{
		format(strBar, 32, "N2O:");
	}
	else
	{
		format(strBar, 32, "N2O: ");
		for(new v; v < value; v++)
		{
			format(strBar, 32, "%sl", strBar);
		}
	}
	PlayerTextDrawSetString(playerid, td_P_carhud54[playerid], strBar);
	PlayerTextDrawShow(playerid, td_P_carhud54[playerid]);
	return 1;
}

stock Radio_Show(playerid)
{
	if(gracz[playerid][radio_status] == 1) return 0;
	gracz[playerid][radio_status] = 1;
	PlayerTextDrawShow(playerid, td_radiocar0[playerid]);
	PlayerTextDrawShow(playerid, td_radiocar1[playerid]);
	PlayerTextDrawShow(playerid, td_radiocar2[playerid]);
	PlayerTextDrawShow(playerid, td_radiocar3[playerid]);
	PlayerTextDrawShow(playerid, td_radiocar4[playerid]);
	PlayerTextDrawShow(playerid, td_radiocar5[playerid]);
	PlayerTextDrawShow(playerid, td_radiocar6[playerid]);
	PlayerTextDrawShow(playerid, td_radiocar7[playerid]);
	PlayerTextDrawShow(playerid, td_radiocar8[playerid]);
	PlayerTextDrawShow(playerid, td_radiocar9[playerid]);
	PlayerTextDrawShow(playerid, td_radiocar10[playerid]);
	TextDrawShowForPlayer(playerid, td_radiocar11);
	TextDrawShowForPlayer(playerid, td_radiocar12);
	TextDrawShowForPlayer(playerid, td_radiocar13);
	TextDrawShowForPlayer(playerid, td_radiocar14);
	return 1;
}


stock Radio_Hide(playerid)
{
	if(gracz[playerid][radio_status] == 0) return 0;
	gracz[playerid][radio_status] = 0;
	PlayerTextDrawHide(playerid, td_radiocar0[playerid]);
	PlayerTextDrawHide(playerid, td_radiocar1[playerid]);
	PlayerTextDrawHide(playerid, td_radiocar2[playerid]);
	PlayerTextDrawHide(playerid, td_radiocar3[playerid]);
	PlayerTextDrawHide(playerid, td_radiocar4[playerid]);
	PlayerTextDrawHide(playerid, td_radiocar5[playerid]);
	PlayerTextDrawHide(playerid, td_radiocar6[playerid]);
	PlayerTextDrawHide(playerid, td_radiocar7[playerid]);
	PlayerTextDrawHide(playerid, td_radiocar8[playerid]);
	PlayerTextDrawHide(playerid, td_radiocar9[playerid]);
	PlayerTextDrawHide(playerid, td_radiocar10[playerid]);
	TextDrawHideForPlayer(playerid, td_radiocar11);
	TextDrawHideForPlayer(playerid, td_radiocar12);
	TextDrawHideForPlayer(playerid, td_radiocar13);
	TextDrawHideForPlayer(playerid, td_radiocar14);
	return 1;
}

stock Radio_DisplayColor(playerid, color = -5963521)
{
	if(gracz[playerid][radio_status] == 0) return 0;
	PlayerTextDrawSetString(playerid, td_radiocar0[playerid] txt);
	PlayerTextDrawShow(playerid, td_radiocar0[playerid]);
	return 1;
}

stock Radio_Text(playerid, txt[])
{
	if(gracz[playerid][radio_status] == 0) return 0;
	format(txt, 20, txt);
	PlayerTextDrawSetString(playerid, td_radiocar1[playerid], txt);
	PlayerTextDrawShow(playerid, td_radiocar1[playerid]);
	return 1;
}

stock Radio_KnobColor(playerid, color = -2139062017)
{
	if(gracz[playerid][radio_status] == 0) return 0;
	PlayerTextDrawSetString(playerid, td_radiocar2[playerid] txt);
	PlayerTextDrawShow(playerid, td_radiocar2[playerid]);
	return 1;
}

stock Radio_HighlightButton(playerid, number, color = 0xFF0000FF)
{
	if(gracz[playerid][radio_status] == 0) return 0;
	switch(number)
	{
		case 1:
		{
			PlayerTextDrawColor(playerid, td_radiocar4[playerid], color);//1
			PlayerTextDrawColor(playerid, td_radiocar5[playerid], -1);//2
			PlayerTextDrawColor(playerid, td_radiocar6[playerid], -1);//3
			PlayerTextDrawColor(playerid, td_radiocar7[playerid], -1);//4
			PlayerTextDrawColor(playerid, td_radiocar8[playerid], -1);//5
			PlayerTextDrawColor(playerid, td_radiocar9[playerid], -1);//6
			PlayerTextDrawColor(playerid, td_radiocar10[playerid], -1);//0
		}
		case 2:
		{
			PlayerTextDrawColor(playerid, td_radiocar4[playerid], -1);//1
			PlayerTextDrawColor(playerid, td_radiocar5[playerid], color);//2
			PlayerTextDrawColor(playerid, td_radiocar6[playerid], -1);//3
			PlayerTextDrawColor(playerid, td_radiocar7[playerid], -1);//4
			PlayerTextDrawColor(playerid, td_radiocar8[playerid], -1);//5
			PlayerTextDrawColor(playerid, td_radiocar9[playerid], -1);//6
			PlayerTextDrawColor(playerid, td_radiocar10[playerid], -1);//0
		}
		case 3:
		{	
			PlayerTextDrawColor(playerid, td_radiocar4[playerid], -1);//1
			PlayerTextDrawColor(playerid, td_radiocar5[playerid], -1);//2
			PlayerTextDrawColor(playerid, td_radiocar6[playerid], color);//3
			PlayerTextDrawColor(playerid, td_radiocar7[playerid], -1);//4
			PlayerTextDrawColor(playerid, td_radiocar8[playerid], -1);//5
			PlayerTextDrawColor(playerid, td_radiocar9[playerid], -1);//6
			PlayerTextDrawColor(playerid, td_radiocar10[playerid], -1);//0
		}
		case 4:
		{	
			PlayerTextDrawColor(playerid, td_radiocar4[playerid], -1);//1
			PlayerTextDrawColor(playerid, td_radiocar5[playerid], -1);//2
			PlayerTextDrawColor(playerid, td_radiocar6[playerid], -1);//3
			PlayerTextDrawColor(playerid, td_radiocar7[playerid], color);//4
			PlayerTextDrawColor(playerid, td_radiocar8[playerid], -1);//5
			PlayerTextDrawColor(playerid, td_radiocar9[playerid], -1);//6
			PlayerTextDrawColor(playerid, td_radiocar10[playerid], -1);//0
		}
		case 5:
		{	
			PlayerTextDrawColor(playerid, td_radiocar4[playerid], -1);//1
			PlayerTextDrawColor(playerid, td_radiocar5[playerid], -1);//2
			PlayerTextDrawColor(playerid, td_radiocar6[playerid], -1);//3
			PlayerTextDrawColor(playerid, td_radiocar7[playerid], -1);//4
			PlayerTextDrawColor(playerid, td_radiocar8[playerid], color);//5
			PlayerTextDrawColor(playerid, td_radiocar9[playerid], -1);//6
			PlayerTextDrawColor(playerid, td_radiocar10[playerid], -1);//0
		}
		case 6:
		{	
			PlayerTextDrawColor(playerid, td_radiocar4[playerid], -1);//1
			PlayerTextDrawColor(playerid, td_radiocar5[playerid], -1);//2
			PlayerTextDrawColor(playerid, td_radiocar6[playerid], -1);//3
			PlayerTextDrawColor(playerid, td_radiocar7[playerid], -1);//4
			PlayerTextDrawColor(playerid, td_radiocar8[playerid], -1);//5
			PlayerTextDrawColor(playerid, td_radiocar9[playerid], color);//6
			PlayerTextDrawColor(playerid, td_radiocar10[playerid], -1);//0
		}
		case 7:
		{
			PlayerTextDrawColor(playerid, td_radiocar4[playerid], color);//1
			PlayerTextDrawColor(playerid, td_radiocar5[playerid], -1);//2
			PlayerTextDrawColor(playerid, td_radiocar6[playerid], -1);//3
			PlayerTextDrawColor(playerid, td_radiocar7[playerid], -1);//4
			PlayerTextDrawColor(playerid, td_radiocar8[playerid], -1);//5
			PlayerTextDrawColor(playerid, td_radiocar9[playerid], -1);//6
			PlayerTextDrawColor(playerid, td_radiocar10[playerid], color);//0
		}
		case 8:
		{
			PlayerTextDrawColor(playerid, td_radiocar4[playerid], -1);//1
			PlayerTextDrawColor(playerid, td_radiocar5[playerid], color);//2
			PlayerTextDrawColor(playerid, td_radiocar6[playerid], -1);//3
			PlayerTextDrawColor(playerid, td_radiocar7[playerid], -1);//4
			PlayerTextDrawColor(playerid, td_radiocar8[playerid], -1);//5
			PlayerTextDrawColor(playerid, td_radiocar9[playerid], -1);//6
			PlayerTextDrawColor(playerid, td_radiocar10[playerid], color);//0
		}
		case 9:
		{	
			PlayerTextDrawColor(playerid, td_radiocar4[playerid], -1);//1
			PlayerTextDrawColor(playerid, td_radiocar5[playerid], -1);//2
			PlayerTextDrawColor(playerid, td_radiocar6[playerid], color);//3
			PlayerTextDrawColor(playerid, td_radiocar7[playerid], -1);//4
			PlayerTextDrawColor(playerid, td_radiocar8[playerid], -1);//5
			PlayerTextDrawColor(playerid, td_radiocar9[playerid], -1);//6
			PlayerTextDrawColor(playerid, td_radiocar10[playerid], color);//0
		}
		case 10:
		{	
			PlayerTextDrawColor(playerid, td_radiocar4[playerid], -1);//1
			PlayerTextDrawColor(playerid, td_radiocar5[playerid], -1);//2
			PlayerTextDrawColor(playerid, td_radiocar6[playerid], -1);//3
			PlayerTextDrawColor(playerid, td_radiocar7[playerid], color);//4
			PlayerTextDrawColor(playerid, td_radiocar8[playerid], -1);//5
			PlayerTextDrawColor(playerid, td_radiocar9[playerid], -1);//6
			PlayerTextDrawColor(playerid, td_radiocar10[playerid], color);//0
		}
		case 11:
		{	
			PlayerTextDrawColor(playerid, td_radiocar4[playerid], -1);//1
			PlayerTextDrawColor(playerid, td_radiocar5[playerid], -1);//2
			PlayerTextDrawColor(playerid, td_radiocar6[playerid], -1);//3
			PlayerTextDrawColor(playerid, td_radiocar7[playerid], -1);//4
			PlayerTextDrawColor(playerid, td_radiocar8[playerid], color);//5
			PlayerTextDrawColor(playerid, td_radiocar9[playerid], -1);//6
			PlayerTextDrawColor(playerid, td_radiocar10[playerid], color);//0
		}
		case 12:
		{	
			PlayerTextDrawColor(playerid, td_radiocar4[playerid], -1);//1
			PlayerTextDrawColor(playerid, td_radiocar5[playerid], -1);//2
			PlayerTextDrawColor(playerid, td_radiocar6[playerid], -1);//3
			PlayerTextDrawColor(playerid, td_radiocar7[playerid], -1);//4
			PlayerTextDrawColor(playerid, td_radiocar8[playerid], -1);//5
			PlayerTextDrawColor(playerid, td_radiocar9[playerid], color);//6
			PlayerTextDrawColor(playerid, td_radiocar10[playerid], color);//0
		}
		default:
		{	
			PlayerTextDrawColor(playerid, td_radiocar4[playerid], -1);//1
			PlayerTextDrawColor(playerid, td_radiocar5[playerid], -1);//2
			PlayerTextDrawColor(playerid, td_radiocar6[playerid], -1);//3
			PlayerTextDrawColor(playerid, td_radiocar7[playerid], -1);//4
			PlayerTextDrawColor(playerid, td_radiocar8[playerid], -1);//5
			PlayerTextDrawColor(playerid, td_radiocar9[playerid], -1);//6
			PlayerTextDrawColor(playerid, td_radiocar10[playerid], -1);//0
		}
	}
	PlayerTextDrawShow(playerid, td_radiocar4[playerid]);//1
	PlayerTextDrawShow(playerid, td_radiocar5[playerid]);//2
	PlayerTextDrawShow(playerid, td_radiocar6[playerid]);//3
	PlayerTextDrawShow(playerid, td_radiocar7[playerid]);//4
	PlayerTextDrawShow(playerid, td_radiocar8[playerid]);//5
	PlayerTextDrawShow(playerid, td_radiocar9[playerid]);//6
	PlayerTextDrawShow(playerid, td_radiocar10[playerid]);//0
	return 1;
}

stock Dystrybutor_Show(playerid)
{
	if(gracz[playerid][dystrybutor_status]) return 0;
	gracz[playerid][dystrybutor_status] = 1;
	TextDrawShowForPlayer(playerid, td_g_dystrybutor0);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor1);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor2);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor3);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor4);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor5);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor6);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor7);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor8);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor9);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor10);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor11);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor12);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor13);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor14);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor15);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor16);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor17);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor18);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor19);
	TextDrawShowForPlayer(playerid, td_g_dystrybutor20);
	PlayerTextDrawShow(playerid, td_p_dystrybutor0[playerid]);
	PlayerTextDrawShow(playerid, td_p_dystrybutor1[playerid]);
	PlayerTextDrawShow(playerid, td_p_dystrybutor2[playerid]);
	PlayerTextDrawShow(playerid, td_p_dystrybutor3[playerid]);
	PlayerTextDrawShow(playerid, td_p_dystrybutor4[playerid]);
	PlayerTextDrawShow(playerid, td_p_dystrybutor5[playerid]);
	Dystrybutor_SetPrice(playerid, 0);
	Dystrybutor_SetTanked(playerid, 0);
	Dystrybutor_SetDMPrice(playerid, 0);
	gracz[playerid][dystrybutor_multiplier] = 1;//ustawienie standardowego mnożnika

	gracz[playerid][dystrybutor_vehicleid] = 0;
	gracz[playerid][dystrybutor_fueltype] = 0;
	gracz[playerid][dystrybutor_companyid] = 0;
	return 1;
}

stock Dystrybutor_Hide(playerid)
{
	if(!gracz[playerid][dystrybutor_status]) return 0;
	gracz[playerid][dystrybutor_status] = 0;
	TextDrawHideForPlayer(playerid, td_g_dystrybutor0);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor1);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor2);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor3);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor4);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor5);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor6);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor7);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor8);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor9);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor10);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor11);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor12);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor13);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor14);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor15);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor16);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor17);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor18);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor19);
	TextDrawHideForPlayer(playerid, td_g_dystrybutor20);
	PlayerTextDrawHide(playerid, td_p_dystrybutor0[playerid]);
	PlayerTextDrawHide(playerid, td_p_dystrybutor1[playerid]);
	PlayerTextDrawHide(playerid, td_p_dystrybutor2[playerid]);
	PlayerTextDrawHide(playerid, td_p_dystrybutor3[playerid]);
	PlayerTextDrawHide(playerid, td_p_dystrybutor4[playerid]);
	PlayerTextDrawHide(playerid, td_p_dystrybutor5[playerid]);
	if(gracz[playerid][dystrybutor_companyid] != 0)//było tankowane na firme
	{
		if(gracz[playerid][dystrybutor_tanked] != 0 && gracz[playerid][dystrybutor_price] != 0)
		{
			if(gracz[playerid][firma] == gracz[playerid][dystrybutor_companyid])
			{
				if(IsPlayerOnDutyCompany(playerid))
				{
					new fuel_name[16];
					switch(gracz[playerid][dystrybutor_fueltype])
					{
						case F_PB: format(fuel_name, 16, "PB");
						case F_ON: format(fuel_name, 16, "ON");
						case F_LPG: format(fuel_name, 16, "LPG");
					}
					new vid = gracz[playerid][dystrybutor_vehicleid];
					LogCompany(gracz[playerid][dystrybutor_companyid], gracz[playerid][UID], gracz[playerid][firma_sessionid], CLOGFLAG_WYDATEK, "Paliwo(%s) %dL. Koszt: %d$. %s(UID: %d). Saldo: %d$", fuel_name, gracz[playerid][dystrybutor_tanked], gracz[playerid][dystrybutor_price], GetVehicleName(pojazd[vid][v_model]), pojazd[vid][v_id], company[gracz[playerid][dystrybutor_companyid]][cny_money]);
				}
			}
		}
	}
	gracz[playerid][dystrybutor_tanked] = 0;
	gracz[playerid][dystrybutor_price] = 0;

	gracz[playerid][dystrybutor_vehicleid] = 0;
	gracz[playerid][dystrybutor_fueltype] = 0;
	gracz[playerid][dystrybutor_companyid] = 0;
	return 1;
}

stock Dystrybutor_SetPrice(playerid, value)
{
	if(!gracz[playerid][dystrybutor_status]) return 0;
	new strTemp[16];
	format(strTemp, 16, "%d.00", value);
	PlayerTextDrawSetString(playerid, td_p_dystrybutor0[playerid], strTemp);
	PlayerTextDrawShow(playerid, td_p_dystrybutor0[playerid]);
	return 1;
}

stock Dystrybutor_SetTanked(playerid, value)
{
	if(!gracz[playerid][dystrybutor_status]) return 0;
	new strTemp[16];
	format(strTemp, 16, "%d.00", value);
	PlayerTextDrawSetString(playerid, td_p_dystrybutor1[playerid], strTemp);
	PlayerTextDrawShow(playerid, td_p_dystrybutor0[playerid]);
	return 1;
}

stock Dystrybutor_SetDMPrice(playerid, value)
{
	if(!gracz[playerid][dystrybutor_status]) return 0;
	new strTemp[16];
	format(strTemp, 16, "%d.00", value);
	PlayerTextDrawSetString(playerid, td_p_dystrybutor2[playerid], strTemp);
	PlayerTextDrawShow(playerid, td_p_dystrybutor0[playerid]);
	return 1;
}

stock Dystrybutor_SetFuelType(playerid, type)
{
	if(!gracz[playerid][dystrybutor_status]) return 0;
	new strTemp[4];
	format(strTemp, 16, "PB");
	switch(type)
	{
		case F_PB: 
		{
			format(strTemp, 16, "PB");
			PlayerTextDrawColor(playerid, td_p_dystrybutor3[playerid], 0x19BD00FF);
		}
		case F_ON: 
		{
			format(strTemp, 16, "ON");
			PlayerTextDrawColor(playerid, td_p_dystrybutor3[playerid], 255);
		}
		case F_LPG:
		{ 
			format(strTemp, 16, "LPG");
			PlayerTextDrawColor(playerid, td_p_dystrybutor3[playerid], 0x008CF4FF);
		}
	}
	PlayerTextDrawSetString(playerid, td_p_dystrybutor4[playerid], strTemp);
	PlayerTextDrawShow(playerid, td_p_dystrybutor3[playerid]);
	PlayerTextDrawShow(playerid, td_p_dystrybutor4[playerid]);
	return 1;
}

stock Dystrybutor_SetStationName(playerid, sname[], color = -16776961)
{
	if(!gracz[playerid][dystrybutor_status]) return 0;
	PlayerTextDrawSetString(playerid, td_p_dystrybutor5[playerid], sname);
	PlayerTextDrawColor(playerid, td_p_dystrybutor5[playerid], color);
	PlayerTextDrawShow(playerid, td_p_dystrybutor5[playerid]);
	return 1;
}

stock ShowRightMessageBox(playerid, title[], content[])
{
	HideRightMessageBox(playerid);
	TextDrawShowForPlayer(playerid, td_g_rightmsgbox0);
	PlayerTextDrawSetString(playerid, td_p_rightmsgbox0[playerid], content);
	PlayerTextDrawSetString(playerid, td_p_rightmsgbox1[playerid], title);
	if(gracz[playerid][td_rightmsgboxtitlecolor]) PlayerTextDrawBackgroundColor(playerid, td_p_rightmsgbox1[playerid], -2147483393), gracz[playerid][td_rightmsgboxtitlecolor] = false;
	else PlayerTextDrawBackgroundColor(playerid, td_p_rightmsgbox1[playerid], 0x002BFFFF), gracz[playerid][td_rightmsgboxtitlecolor] = true;
	PlayerTextDrawShow(playerid, td_p_rightmsgbox0[playerid]);
	PlayerTextDrawShow(playerid, td_p_rightmsgbox1[playerid]);
	return 1;
}

stock HideRightMessageBox(playerid)
{
	TextDrawHideForPlayer(playerid, td_g_rightmsgbox0);
	PlayerTextDrawHide(playerid, td_p_rightmsgbox0[playerid]);
	PlayerTextDrawHide(playerid, td_p_rightmsgbox1[playerid]);
	return 1;
}

stock CargoInfo_Show(playerid, c_name[], c_cargosize, c_cargosizeunit, c_targetcity[], c_price, c_pricefor[])
{
	CargoInfo_Hide(playerid);
	if(pojazd[GetPlayerVehicleID(playerid)][v_model] == 525) return 1;//FIX - zapobiega wyświetlania td z towarem dla holowników (bo opiera się o attachtrailer)
	TextDrawShowForPlayer(playerid, td_g_cargoinfo0);
	TextDrawShowForPlayer(playerid, td_g_cargoinfo1);
	TextDrawShowForPlayer(playerid, td_g_cargoinfo2);
	TextDrawShowForPlayer(playerid, td_g_cargoinfo3);
	TextDrawShowForPlayer(playerid, td_g_cargoinfo4);
	TextDrawShowForPlayer(playerid, td_g_cargoinfo5);
	new cString[64];
	format(cString, 34, "Towar: ~y~%s", c_name);
	PlayerTextDrawSetString(playerid, td_p_cargoinfo0[playerid], cString);
	new formated_cargosize = c_cargosize;
	if(c_cargosize > 999) formated_cargosize = c_cargosize/1000;//przeliczanie na tony
	switch(c_cargosizeunit)
	{
		case 0: format(cString, 32, "Ilosc: ~y~%d ~w~%s", formated_cargosize, (formated_cargosize == c_cargosize) ? ("kg") : ("t"));
		case 1: format(cString, 32, "Ilosc: ~y~%d ~w~szt", c_cargosize);
	}
	PlayerTextDrawSetString(playerid, td_p_cargoinfo1[playerid], cString);
	format(cString, 24, "CEL: ~w~%s", c_targetcity);
	PlayerTextDrawSetString(playerid, td_p_cargoinfo2[playerid], cString);
	format(cString, 24, "%d$ ~y~za ~w~%s", c_price, c_pricefor);
	PlayerTextDrawSetString(playerid, td_p_cargoinfo3[playerid], cString);
	PlayerTextDrawShow(playerid, td_p_cargoinfo0[playerid]);
	PlayerTextDrawShow(playerid, td_p_cargoinfo1[playerid]);
	PlayerTextDrawShow(playerid, td_p_cargoinfo2[playerid]);
	PlayerTextDrawShow(playerid, td_p_cargoinfo3[playerid]);
	return 1;
}

stock CargoInfo_Hide(playerid)
{
	TextDrawHideForPlayer(playerid, td_g_cargoinfo0);
	TextDrawHideForPlayer(playerid, td_g_cargoinfo1);
	TextDrawHideForPlayer(playerid, td_g_cargoinfo2);
	TextDrawHideForPlayer(playerid, td_g_cargoinfo3);
	TextDrawHideForPlayer(playerid, td_g_cargoinfo4);
	TextDrawHideForPlayer(playerid, td_g_cargoinfo5);
	PlayerTextDrawHide(playerid, td_p_cargoinfo0[playerid]);
	PlayerTextDrawHide(playerid, td_p_cargoinfo1[playerid]);
	PlayerTextDrawHide(playerid, td_p_cargoinfo2[playerid]);
	PlayerTextDrawHide(playerid, td_p_cargoinfo3[playerid]);
	return 1;
}

stock SalonTruckSelectTDShow(playerid, st_name[], st_price, st_maxload, st_fueltype, st_tanksize, Float:st_fuelconsumption, Float:st_0100, st_vmax)
{
	SalonTruckSelectTDHide(playerid);
	TextDrawShowForPlayer(playerid, td_g_trucksalon0);
	TextDrawShowForPlayer(playerid, td_g_trucksalon1);
	TextDrawShowForPlayer(playerid, td_g_trucksalon2);
	TextDrawShowForPlayer(playerid, td_g_trucksalon3);
	new st_str[128];
	PlayerTextDrawSetString(playerid, td_p_trucksalon0[playerid], st_name);
	format(st_str, 128, "%d $", st_price);
	PlayerTextDrawSetString(playerid, td_p_trucksalon1[playerid], st_str);
	if(st_maxload > 0) format(st_str, 128, "Dopuszczalna ladownosc: ~r~%d ~w~[kg]", st_maxload);
	else format(st_str, 128, "Dopuszczalna ladownosc: ~r~1 ~w~[naczepa]");
	PlayerTextDrawSetString(playerid, td_p_trucksalon2[playerid], st_str);

	if(st_fueltype == -1)
	{
		PlayerTextDrawSetString(playerid, td_p_trucksalon3[playerid], "Typ paliwa: ~w~---");
		PlayerTextDrawSetString(playerid, td_p_trucksalon4[playerid], "Pojemnosc zbiornika: ~w~---");
		PlayerTextDrawSetString(playerid, td_p_trucksalon5[playerid], "Spalanie: ~w~---");
		PlayerTextDrawSetString(playerid, td_p_trucksalon6[playerid], "Przyspieszenie (0-100): ~w~---");
		PlayerTextDrawSetString(playerid, td_p_trucksalon7[playerid], "Predkosc maksymalna (V-MAX): ~w~---");
	}
	else
	{
		new str_fueltype[4];
		format(str_fueltype, 16, "PB");
		switch(st_fueltype)
		{
			case F_PB: format(str_fueltype, 16, "PB");
			case F_ON: format(str_fueltype, 16, "ON");
			case F_LPG: format(str_fueltype, 16, "LPG");
		}
		format(st_str, 128, "Typ paliwa: ~y~%s", str_fueltype);
		PlayerTextDrawSetString(playerid, td_p_trucksalon3[playerid], st_str);
		format(st_str, 128, "Pojemnosc zbiornika: ~g~%d ~w~[litr]", st_tanksize);
		PlayerTextDrawSetString(playerid, td_p_trucksalon4[playerid], st_str);
		format(st_str, 128, "Spalanie: ~g~%0.1f ~w~[litr/100]", st_fuelconsumption+0.01);
		PlayerTextDrawSetString(playerid, td_p_trucksalon5[playerid], st_str);
		format(st_str, 128, "Przyspieszenie (0-100): ~g~%0.1f ~w~[sekund]", st_0100+0.01);
		PlayerTextDrawSetString(playerid, td_p_trucksalon6[playerid], st_str);
		format(st_str, 128, "Predkosc maksymalna (V-MAX): ~g~%d ~w~[km/h]", st_vmax);
		PlayerTextDrawSetString(playerid, td_p_trucksalon7[playerid], st_str);
	}
	PlayerTextDrawShow(playerid, td_p_trucksalon0[playerid]);
	PlayerTextDrawShow(playerid, td_p_trucksalon1[playerid]);
	PlayerTextDrawShow(playerid, td_p_trucksalon2[playerid]);
	PlayerTextDrawShow(playerid, td_p_trucksalon3[playerid]);
	PlayerTextDrawShow(playerid, td_p_trucksalon4[playerid]);
	PlayerTextDrawShow(playerid, td_p_trucksalon5[playerid]);
	PlayerTextDrawShow(playerid, td_p_trucksalon6[playerid]);
	PlayerTextDrawShow(playerid, td_p_trucksalon7[playerid]);
	return 1;
}

stock SalonTruckSelectTDHide(playerid)
{
	TextDrawHideForPlayer(playerid, td_g_trucksalon0);
	TextDrawHideForPlayer(playerid, td_g_trucksalon1);
	TextDrawHideForPlayer(playerid, td_g_trucksalon2);
	TextDrawHideForPlayer(playerid, td_g_trucksalon3);
	PlayerTextDrawHide(playerid, td_p_trucksalon0[playerid]);
	PlayerTextDrawHide(playerid, td_p_trucksalon1[playerid]);
	PlayerTextDrawHide(playerid, td_p_trucksalon2[playerid]);
	PlayerTextDrawHide(playerid, td_p_trucksalon3[playerid]);
	PlayerTextDrawHide(playerid, td_p_trucksalon4[playerid]);
	PlayerTextDrawHide(playerid, td_p_trucksalon5[playerid]);
	PlayerTextDrawHide(playerid, td_p_trucksalon6[playerid]);
	PlayerTextDrawHide(playerid, td_p_trucksalon7[playerid]);
	return 1;
}

stock CargoConfirmShow(playerid, ccs_cargoname[], ccs_cargosize, bool:css_adr, ccs_money, ccs_score, ccs_trailerid, ccs_source[], ccs_target[], Float:ccs_distance)
{
	if(gracz[playerid][td_confirmcargo]) CargoConfirmHide(playerid);
	new ccs_str[512];
	if(ccs_trailerid != -1) format(ccs_str, 512, "Nazwa towaru: ~y~%s~n~~w~Ilosc: ~y~%d ~g~[kg]~n~~w~Naczepa: ~y~%s~n~~w~ADR: %s~n~~w~Skad: ~y~%s~n~~w~Do: ~y~%s~w~~n~Dystans: ~y~%0.1f ~g~[km]", ccs_cargoname, ccs_cargosize, GetVehicleName(pojazd[ccs_trailerid][v_model]), (css_adr) ? ("~r~TAK") : ("~g~NIE"), ccs_source, ccs_target, ccs_distance);
	else format(ccs_str, 512, "Nazwa towaru: ~y~%s~n~~w~Ilosc: ~y~%d ~g~[kg]~n~~w~ADR: %s~n~~w~Skad: ~y~%s~n~~w~Do: ~y~%s~w~~n~Dystans: ~y~%0.1f ~g~[km]", ccs_cargoname, ccs_cargosize, (css_adr) ? ("~r~TAK") : ("~g~NIE"), ccs_source, ccs_target, ccs_distance);
	PlayerTextDrawSetString(playerid, td_p_confirmcargo1[playerid], ccs_str);
	format(ccs_str, 512, "+%d$", ccs_money);
	PlayerTextDrawSetString(playerid, td_p_confirmcargo2[playerid], ccs_str);
	format(ccs_str, 512, "+%d score", ccs_score);
	PlayerTextDrawSetString(playerid, td_p_confirmcargo3[playerid], ccs_str);
	if(ccs_trailerid != -1)
	{
		PlayerTextDrawSetPreviewModel(playerid, td_p_confirmcargo4[playerid], pojazd[ccs_trailerid][v_model]);
		PlayerTextDrawSetPreviewVehCol(playerid,  td_p_confirmcargo4[playerid], pojazd[ccs_trailerid][v_color][0], pojazd[ccs_trailerid][v_color][1]);
		PlayerTextDrawSetPreviewRot(playerid, td_p_confirmcargo4[playerid], -30.000000, 0.000000, 50.000000, 1.100000);
	}
	else
	{
		PlayerTextDrawSetPreviewModel(playerid, td_p_confirmcargo4[playerid], 2935);
		PlayerTextDrawSetPreviewRot(playerid, td_p_confirmcargo4[playerid], -30.000000, 0.000000, 50.000000, 2.0);
	}
	TextDrawSetSelectable(td_g_confirmcargo3, true);
	TextDrawSetSelectable(td_g_confirmcargo4, true);

	TextDrawShowForPlayer(playerid, td_g_confirmcargo0);
	TextDrawShowForPlayer(playerid, td_g_confirmcargo1);
	TextDrawShowForPlayer(playerid, td_g_confirmcargo2);
	TextDrawShowForPlayer(playerid, td_g_confirmcargo3);
	TextDrawShowForPlayer(playerid, td_g_confirmcargo4);
	TextDrawShowForPlayer(playerid, td_g_confirmcargo5);
	TextDrawShowForPlayer(playerid, td_g_confirmcargo6);
	PlayerTextDrawShow(playerid, td_p_confirmcargo1[playerid]);
	PlayerTextDrawShow(playerid, td_p_confirmcargo2[playerid]);
	PlayerTextDrawShow(playerid, td_p_confirmcargo3[playerid]);
	PlayerTextDrawShow(playerid, td_p_confirmcargo4[playerid]);

	SelectTextDraw(playerid, 0x00FF00FF);

	Streamer_DestroyAllVisibleItems(playerid, STREAMER_TYPE_3D_TEXT_LABEL);
	Streamer_SetVisibleItems(STREAMER_TYPE_3D_TEXT_LABEL, 0, playerid);

	gracz[playerid][td_confirmcargo] = true;
	return 1;
}

stock CargoConfirmHide(playerid)
{
	gracz[playerid][td_confirmcargo] = false;
	CancelSelectTextDraw(playerid);
	TextDrawSetSelectable(td_g_confirmcargo3, false);
	TextDrawSetSelectable(td_g_confirmcargo4, false);
	TextDrawHideForPlayer(playerid, td_g_confirmcargo0);
	TextDrawHideForPlayer(playerid, td_g_confirmcargo1);
	TextDrawHideForPlayer(playerid, td_g_confirmcargo2);
	TextDrawHideForPlayer(playerid, td_g_confirmcargo3);
	TextDrawHideForPlayer(playerid, td_g_confirmcargo4);
	TextDrawHideForPlayer(playerid, td_g_confirmcargo5);
	TextDrawHideForPlayer(playerid, td_g_confirmcargo6);
	PlayerTextDrawHide(playerid, td_p_confirmcargo1[playerid]);
	PlayerTextDrawHide(playerid, td_p_confirmcargo2[playerid]);
	PlayerTextDrawHide(playerid, td_p_confirmcargo3[playerid]);
	PlayerTextDrawHide(playerid, td_p_confirmcargo4[playerid]);

	Streamer_DestroyAllVisibleItems(playerid, STREAMER_TYPE_3D_TEXT_LABEL);
	Streamer_SetVisibleItems(STREAMER_TYPE_3D_TEXT_LABEL, MAX_3DTEXT_GLOBAL, playerid);
	return 1;
}

stock Delivered_MainShow(playerid)
{
	if(gracz[playerid][delivered_window]) return 0;
	TextDrawShowForPlayer(playerid, td_g_delivered1);
	gracz[playerid][delivered_window] = true;
	gracz[playerid][delivered_window_step] = 0;
	gracz[playerid][delivered_canexit] = false;
	TogglePlayerControllable(playerid, 0);
	return 1;
}

stock Delivered_SecondShow(playerid)
{
	if(!gracz[playerid][delivered_window]) return 0;
	TextDrawShowForPlayer(playerid, td_g_delivered0);
	TextDrawShowForPlayer(playerid, td_g_delivered2);
	return 1;
}


stock Delivered_ThirdShow(playerid)
{
	if(!gracz[playerid][delivered_window]) return 0;
	TextDrawShowForPlayer(playerid, td_g_delivered3);
	TextDrawShowForPlayer(playerid, td_g_delivered4);
	TextDrawShowForPlayer(playerid, td_g_delivered5);
	TextDrawShowForPlayer(playerid, td_g_delivered6);
	new strTemp[128];
	format(strTemp, 128, "$%d", gracz[playerid][delivered_window_totalmoney]);
	PlayerTextDrawSetString(playerid, td_p_delivered2[playerid], strTemp);
	format(strTemp, 128, "+%d", gracz[playerid][delivered_window_totalscore]);
	PlayerTextDrawSetString(playerid, td_p_delivered3[playerid], strTemp);
	return 1;
}

stock Delivered_ExitInfoShow(playerid)
{
	if(!gracz[playerid][delivered_window]) return 0;
	gracz[playerid][delivered_canexit] = true;
	TextDrawShowForPlayer(playerid, td_g_delivered7);
	TextDrawShowForPlayer(playerid, td_g_delivered8);
	return 1;
}



stock Delivered_Money(playerid, value)
{
	if(!gracz[playerid][delivered_window]) return 0;
	new strTemp[128];
	format(strTemp, 128, "$%d", value);
	PlayerTextDrawSetString(playerid, td_p_delivered2[playerid], strTemp);
	PlayerTextDrawShow(playerid, td_p_delivered2[playerid]);
	return 1;
}


stock Delivered_Score(playerid, value)
{
	if(!gracz[playerid][delivered_window]) return 0;
	new strTemp[128];
	format(strTemp, 128, "+%d", value);
	PlayerTextDrawSetString(playerid, td_p_delivered3[playerid], strTemp);
	PlayerTextDrawShow(playerid, td_p_delivered3[playerid]);
	return 1;
}

stock Delivered_Row1(playerid, datastr[])
{
	if(!gracz[playerid][delivered_window]) return 0;
	PlayerTextDrawSetString(playerid, td_p_delivered0[playerid], datastr);
	PlayerTextDrawShow(playerid, td_p_delivered0[playerid]);
	return 1;
}

stock Delivered_Row2(playerid, datastr[])
{
	if(!gracz[playerid][delivered_window]) return 0;
	PlayerTextDrawSetString(playerid, td_p_delivered1[playerid], datastr);
	PlayerTextDrawShow(playerid, td_p_delivered1[playerid]);
	return 1;
}

stock DeliveredWindowHide(playerid)
{
	if(!gracz[playerid][delivered_canexit]) return 0;
	gracz[playerid][delivered_window] = false;
	gracz[playerid][delivered_canexit] = false;
	TextDrawHideForPlayer(playerid, td_g_delivered0);
	TextDrawHideForPlayer(playerid, td_g_delivered1);
	TextDrawHideForPlayer(playerid, td_g_delivered2);
	TextDrawHideForPlayer(playerid, td_g_delivered3);
	TextDrawHideForPlayer(playerid, td_g_delivered4);
	TextDrawHideForPlayer(playerid, td_g_delivered5);
	TextDrawHideForPlayer(playerid, td_g_delivered6);
	TextDrawHideForPlayer(playerid, td_g_delivered7);
	TextDrawHideForPlayer(playerid, td_g_delivered8);
	PlayerTextDrawHide(playerid, td_p_delivered0[playerid]);
	PlayerTextDrawHide(playerid, td_p_delivered1[playerid]);
	PlayerTextDrawHide(playerid, td_p_delivered2[playerid]);
	PlayerTextDrawHide(playerid, td_p_delivered3[playerid]);
	TogglePlayerControllable(playerid, 1);
	PlayerPlaySound(playerid, 1083, 0, 0, 0);
	return 1;
}


stock ShowAnnTD(playerid, annstr[], color = 255, colorbg = 16711935, font = 3)
{
	PlayerTextDrawSetString(playerid, anntd[playerid], annstr);
	PlayerTextDrawColor(playerid, anntd[playerid], color);
	PlayerTextDrawBackgroundColor(playerid, anntd[playerid], colorbg);
	PlayerTextDrawFont(playerid, anntd[playerid], font);
	PlayerTextDrawShow(playerid, anntd[playerid]);
	return 1;
}

task HideAnn(playerid)
{
	PlayerTextDrawHide(playerid, anntd[playerid]);
	return 1;
}

stock ShowActionTD(playerid, actiontext[])
{
	if(gracz[playerid][status_td_saction]) return 1;
	PlayerTextDrawSetString(playerid, td_p_saction0[playerid], actiontext);
	TextDrawShowForPlayer(playerid, td_g_saction0);
	TextDrawShowForPlayer(playerid, td_g_saction1);
	PlayerTextDrawShow(playerid, td_p_saction0[playerid]);
	gracz[playerid][status_td_saction] = 1;
	return 1;
}

stock HideActionTD(playerid)
{
	if(!gracz[playerid][status_td_saction]) return 1;
	TextDrawHideForPlayer(playerid, td_g_saction0);
	TextDrawHideForPlayer(playerid, td_g_saction1);
	PlayerTextDrawHide(playerid, td_p_saction0[playerid]);
	gracz[playerid][status_td_saction] = 0;
	return 1;
}

stock UpdateFractionToolTD(playerid, ftitle[], fcontent[])
{
	new strFtool[512];
	format(strFtool, 512, "~n~%s", fcontent);
	PlayerTextDrawSetString(playerid, ftool0[playerid], strFtool);
	PlayerTextDrawSetString(playerid, ftool1[playerid], ftitle);
	PlayerTextDrawShow(playerid, ftool0[playerid]);
	PlayerTextDrawShow(playerid, ftool1[playerid]);
	gracz[playerid][status_td_fractiontool] = true;
	return 1;
}

stock HideFractionToolTD(playerid)
{
	if(!gracz[playerid][status_td_fractiontool]) return 1;
	PlayerTextDrawHide(playerid, ftool0[playerid]);
	PlayerTextDrawHide(playerid, ftool1[playerid]);
	return 1;
}

stock ShowScreenFilter(playerid, bcolor)
{
	PlayerTextDrawBoxColor(playerid, td_p_fullscreen[playerid], bcolor);
	PlayerTextDrawShow(playerid, td_p_fullscreen[playerid]);
	return 1;
}

task HideScreenFilter(playerid)
{
	PlayerTextDrawHide(playerid, td_p_fullscreen[playerid]);
	return 1;
}

stock Taxometr_Show(playerid)
{
	if(gracz[playerid][taxometr_td] > 0) return 1;
	PlayerTextDrawShow(playerid, td_p_taxi0[playerid]);
	PlayerTextDrawShow(playerid, td_p_taxi1[playerid]);
	PlayerTextDrawShow(playerid, td_p_taxi2[playerid]);
	TextDrawShowForPlayer(playerid, td_g_taxi0);
	TextDrawShowForPlayer(playerid, td_g_taxi1);
	TextDrawShowForPlayer(playerid, td_g_taxi2);
	TextDrawShowForPlayer(playerid, td_g_taxi3);
	TextDrawShowForPlayer(playerid, td_g_taxi4);
	TextDrawShowForPlayer(playerid, td_g_taxi5);
	gracz[playerid][taxometr_td] = 1;
	return 1;
}

stock Taxometr_Hide(playerid)
{
	if(gracz[playerid][taxometr_td] == 0) return 0;
	PlayerTextDrawHide(playerid, td_p_taxi0[playerid]);
	PlayerTextDrawHide(playerid, td_p_taxi1[playerid]);
	PlayerTextDrawHide(playerid, td_p_taxi2[playerid]);
	TextDrawHideForPlayer(playerid, td_g_taxi0);
	TextDrawHideForPlayer(playerid, td_g_taxi1);
	TextDrawHideForPlayer(playerid, td_g_taxi2);
	TextDrawHideForPlayer(playerid, td_g_taxi3);
	TextDrawHideForPlayer(playerid, td_g_taxi4);
	TextDrawHideForPlayer(playerid, td_g_taxi5);
	gracz[playerid][taxometr_td] = 0;
	return 1;
}

stock Taxometr_SetPricePerKM(playerid, ppkm)
{
	if(gracz[playerid][taxometr_td] == 0) return 0;
	new strTemp[128];
	format(strTemp, 128, "Oplata za km: ~g~~h~~h~%d$", ppkm);
	PlayerTextDrawSetString(playerid, td_p_taxi0[playerid], strTemp);
	return 1;
}

stock Taxometr_SetDistance(playerid, distance)
{
	if(gracz[playerid][taxometr_td] == 0) return 0;
	new strTemp[128];
	format(strTemp, 128, "Przebyty dystans: ~b~~h~~h~%d km", distance);
	PlayerTextDrawSetString(playerid, td_p_taxi1[playerid], strTemp);
	return 1;
}

stock Taxometr_SetPrice(playerid, price)
{
	if(gracz[playerid][taxometr_td] == 0) return 0;
	new strTemp[128];
	if(price != -1) format(strTemp, 128, "%d$", price);
	else format(strTemp, 128, "~r~WYLACZONY");
	PlayerTextDrawSetString(playerid, td_p_taxi2[playerid], strTemp);
	return 1;
}

stock Dokument_Show(playerid, dnick[], dwiek, dplec, dskin, duid, dprawko[])
{
	if(gracz[playerid][td_dokumenty] > 0) return 1;
	TextDrawShowForPlayer(playerid, td_g_dokument0);
	TextDrawShowForPlayer(playerid, td_g_dokument1);
	TextDrawShowForPlayer(playerid, td_g_dokument2);
	TextDrawShowForPlayer(playerid, td_g_dokument3);
	TextDrawShowForPlayer(playerid, td_g_dokument4);
	TextDrawShowForPlayer(playerid, td_g_dokument5);
	TextDrawShowForPlayer(playerid, td_g_dokument6);
	TextDrawShowForPlayer(playerid, td_g_dokument7);
	new strDokument[512];
	format(strDokument, 512, "Nick: %s~n~Wiek: %d~n~Plec: %s~n~Numer dokumentu: %04d", dnick, dwiek, (dplec == 1) ? ("Mezczyzna") : ("Kobieta"), duid);
	PlayerTextDrawSetString(playerid, td_p_dokument0[playerid], strDokument);
	PlayerTextDrawShow(playerid, td_p_dokument0[playerid]);
	PlayerTextDrawSetString(playerid, td_p_dokument1[playerid], dprawko);
	PlayerTextDrawShow(playerid, td_p_dokument1[playerid]);
	PlayerTextDrawSetPreviewModel(playerid, td_p_dokument2[playerid], dskin);
	PlayerTextDrawShow(playerid, td_p_dokument2[playerid]);
	gracz[playerid][td_dokumenty] = 1;
	return 1;
}

stock Dokument_Hide(playerid)
{
	if(gracz[playerid][td_dokumenty] == 0) return 1;
	TextDrawHideForPlayer(playerid, td_g_dokument0);
	TextDrawHideForPlayer(playerid, td_g_dokument1);
	TextDrawHideForPlayer(playerid, td_g_dokument2);
	TextDrawHideForPlayer(playerid, td_g_dokument3);
	TextDrawHideForPlayer(playerid, td_g_dokument4);
	TextDrawHideForPlayer(playerid, td_g_dokument5);
	TextDrawHideForPlayer(playerid, td_g_dokument6);
	TextDrawHideForPlayer(playerid, td_g_dokument7);
	PlayerTextDrawHide(playerid, td_p_dokument0[playerid]);
	PlayerTextDrawHide(playerid, td_p_dokument1[playerid]);
	PlayerTextDrawHide(playerid, td_p_dokument2[playerid]);
	gracz[playerid][td_dokumenty] = 0;
	return 1;
}

stock AdminSpec_Show(playerid, asdata[])
{
	gracz[playerid][td_adminspec] = true;
	PlayerTextDrawSetString(playerid, td_p_adminspec0[playerid], asdata);
	PlayerTextDrawShow(playerid,  td_p_adminspec0[playerid]);
	PlayerTextDrawShow(playerid,  td_p_adminspec1[playerid]);
	return 1;
}

stock AdminSpec_Hide(playerid)
{
	if(!gracz[playerid][td_adminspec]) return 1;
	PlayerTextDrawHide(playerid, td_p_adminspec0[playerid]);
	PlayerTextDrawHide(playerid, td_p_adminspec1[playerid]);
	gracz[playerid][td_adminspec] = false;
	return 1;
}

stock CombineTD_Title(playerid, title[])
{
	PlayerTextDrawSetString(playerid, tdCombine1[playerid], title);
	return 1;
}

stock CombineTD_Left(playerid, left[])
{
	PlayerTextDrawSetString(playerid, tdCombine3[playerid], left);
	return 1;
}

stock CombineTD_Right(playerid, right[])
{

	PlayerTextDrawSetString(playerid, tdCombine4[playerid], right);
	return 1;
}

stock CombineTD_Beside(playerid, beside[])
{
	PlayerTextDrawSetString(playerid, tdCombine8[playerid], beside);
	return 1;
}

stock CombineTD_Tip(playerid, tip[])
{
	PlayerTextDrawSetString(playerid, tdCombine2[playerid], tip);
	return 1;
}

stock CombineTD_Combine(playerid, combine[])
{
	PlayerTextDrawSetString(playerid, tdCombine7[playerid], combine);
	return 1;
}

stock ShowCombineTD(playerid)
{
	PlayerTextDrawShow(playerid, tdCombine0[playerid]);
	PlayerTextDrawShow(playerid, tdCombine1[playerid]);
	PlayerTextDrawShow(playerid, tdCombine2[playerid]);
	PlayerTextDrawShow(playerid, tdCombine3[playerid]);
	PlayerTextDrawShow(playerid, tdCombine4[playerid]);
	PlayerTextDrawShow(playerid, tdCombine5[playerid]);
	PlayerTextDrawShow(playerid, tdCombine6[playerid]);
	PlayerTextDrawShow(playerid, tdCombine7[playerid]);
	PlayerTextDrawShow(playerid, tdCombine8[playerid]);
	return 1;
}

stock HideCombineTD(playerid)
{
	PlayerTextDrawHide(playerid, tdCombine0[playerid]);
	PlayerTextDrawHide(playerid, tdCombine1[playerid]);
	PlayerTextDrawHide(playerid, tdCombine2[playerid]);
	PlayerTextDrawHide(playerid, tdCombine3[playerid]);
	PlayerTextDrawHide(playerid, tdCombine4[playerid]);
	PlayerTextDrawHide(playerid, tdCombine5[playerid]);
	PlayerTextDrawHide(playerid, tdCombine6[playerid]);
	PlayerTextDrawHide(playerid, tdCombine7[playerid]);
	PlayerTextDrawHide(playerid, tdCombine8[playerid]);
	return 1;
}


stock ShowJoinLeaveTD(playerid, type, reason, time_connected)
{
	new jl_col;
	new strJL[144];
	if(type == 0)//join
	{
		jl_col = 8388863;
		format(strJL, 144, " Gracz %s (ID: %d) zalogowal sie do gry! Witamy serdeczenie!", nick(playerid), playerid);
	}
	else if(type == 1)//disconnect
	{
		jl_col = -2139062017;
		new szDisconnectReason[3][] =
		{
			"Timeout",
			"Wyszedl",
			"Kick/Ban"
		};
		format(strJL, 144, "Gracz %s (ID: %d) opuscil gre! (%d minut) (%s)", nick(playerid), playerid, time_connected, szDisconnectReason[reason]);
	}
	HUD_UpdateINFO(strJL, type+1, jl_col);
	serwer[time_connectinfo] = serwer[time_timestamp];
	return 1;
}

task Process_JoinLeaveTD()
{
	if(serwer[time_connectinfo]+15 > serwer[time_timestamp] && serwer[time_connectinfo] != 0) return 1;
	HUD_UpdateINFO(ann_scm_td[serwer[last_annmsg]], 0);
	serwer[time_connectinfo] = 0;
	return 1;
}


stock SetClockTD(hours, min, seconds)
{
	new strClock[16];
	format(strClock, 16, "%02d:%02d", hours, min);
	TextDrawSetString(td_g_clock0, strClock);
	format(strClock, 16, "%02d", seconds);
	TextDrawSetString(td_g_clock1, strClock);
	TextDrawSetString(pgHUD6, GetWeekDay());
	return 1;
}

stock ShowPursuitTD(playerid)
{
	if(gracz[playerid][td_pursuit] > 0) return 1;
	PlayerTextDrawShow(playerid, td_p_pursuit0[playerid]);
	PlayerTextDrawShow(playerid, td_p_pursuit1[playerid]);
	PlayerTextDrawShow(playerid, td_p_pursuit2[playerid]);
	PlayerTextDrawShow(playerid, td_p_pursuit3[playerid]);
	PlayerTextDrawShow(playerid, td_p_pursuit4[playerid]);
	PlayerTextDrawShow(playerid, td_p_pursuit5[playerid]);
	PlayerTextDrawShow(playerid, td_p_pursuit6[playerid]);
	PlayerTextDrawShow(playerid, td_p_pursuit7[playerid]);
	PlayerTextDrawShow(playerid, td_p_pursuit8[playerid]);
	PlayerTextDrawShow(playerid, td_p_pursuit9[playerid]);
	PlayerTextDrawShow(playerid, td_p_pursuit10[playerid]);
	gracz[playerid][td_pursuit] = 1;
	return 1;
}

stock HidePursuitTD(playerid)
{
	if(gracz[playerid][td_pursuit] == 0) return 1;
	PlayerTextDrawHide(playerid, td_p_pursuit0[playerid]);
	PlayerTextDrawHide(playerid, td_p_pursuit1[playerid]);
	PlayerTextDrawHide(playerid, td_p_pursuit2[playerid]);
	PlayerTextDrawHide(playerid, td_p_pursuit3[playerid]);
	PlayerTextDrawHide(playerid, td_p_pursuit4[playerid]);
	PlayerTextDrawHide(playerid, td_p_pursuit5[playerid]);
	PlayerTextDrawHide(playerid, td_p_pursuit6[playerid]);
	PlayerTextDrawHide(playerid, td_p_pursuit7[playerid]);
	PlayerTextDrawHide(playerid, td_p_pursuit8[playerid]);
	PlayerTextDrawHide(playerid, td_p_pursuit9[playerid]);
	PlayerTextDrawHide(playerid, td_p_pursuit10[playerid]);
	gracz[playerid][td_pursuit] = 0;
	return 1;
}

stock SetPorsuitWantedBarLeft(playerid, Float:value, color = 8388863)
{
	if(gracz[playerid][td_pursuit] == 0) return 1;
	if(value > 100.0) value = 100.0;
	if(value < 0.0) value = 0.0;
	new Float:result_td_size = -0.68977706*value;
	PlayerTextDrawTextSize(playerid, td_p_pursuit6[playerid], result_td_size, 21.404445);
	PlayerTextDrawColor(playerid,  td_p_pursuit6[playerid], color);
	PlayerTextDrawShow(playerid, td_p_pursuit6[playerid]);
	return 1;
}

stock SetPorsuitWantedBarRight(playerid, Float:value, color = -2147483393)
{
	if(gracz[playerid][td_pursuit] == 0) return 1;
	if(value > 100.0) value = 100.0;
	if(value < 0.0) value = 0.0;
	new Float:result_td_size = 0.68755691*value;
	PlayerTextDrawTextSize(playerid, td_p_pursuit7[playerid], result_td_size, 21.404445);
	PlayerTextDrawColor(playerid,  td_p_pursuit7[playerid], color);
	PlayerTextDrawShow(playerid, td_p_pursuit7[playerid]);
	return 1;
}

stock SetPursuitInfo(playerid, pinfo[])
{
	if(gracz[playerid][td_pursuit] == 0) return 1;
	PlayerTextDrawSetString(playerid, td_p_pursuit10[playerid], pinfo);
	PlayerTextDrawShow(playerid, td_p_pursuit10[playerid]);
	return 1;
}

stock SetInterwencjaTD(tekst[]) return TextDrawSetString(interwencja_td, tekst);


stock SetSimpleTextTD(playerid, text[], timeoff = 100)
{
	gracz[playerid][td_simpletext] = serwer[time_timestamp]+timeoff;
	PlayerTextDrawSetString(playerid, td_p_simpletext[playerid], text);
	PlayerTextDrawShow(playerid, td_p_simpletext[playerid]);
	return 1;
}

stock HideSimpleTextTD(playerid)
{
	if(gracz[playerid][td_simpletext] == 0) return 0;
	gracz[playerid][td_simpletext] = 0;
	PlayerTextDrawHide(playerid, td_p_simpletext[playerid]);
	return 1;
}

task Process_SimpleText(playerid)
{
	if(gracz[playerid][td_simpletext] != 0)
	{
		if(gracz[playerid][td_simpletext] < serwer[time_timestamp])
		{
			gracz[playerid][td_simpletext] = 0;
			PlayerTextDrawHide(playerid, td_p_simpletext[playerid]);
		}
	}
	return 1;
}

stock ShowTDShoot(playerid)
{
	if(gracz[playerid][td_shoot_type])
	{
		TextDrawHideForPlayer(playerid, td_g_shoot1);
		TextDrawShowForPlayer(playerid, td_g_shoot0);
		gracz[playerid][td_shoot_type] = false;
	}
	else
	{
		TextDrawHideForPlayer(playerid, td_g_shoot0);
		TextDrawShowForPlayer(playerid, td_g_shoot1);
		gracz[playerid][td_shoot_type] = true;
	}
	gracz[playerid][shoot_td_time] = serwer[time_timestamp]+1; 
	return 1;
}

task Process_TDShoot(playerid)
{
	if(gracz[playerid][shoot_td_time] != 0)
	{
		if(gracz[playerid][shoot_td_time] < serwer[time_timestamp])
		{
			TextDrawHideForPlayer(playerid, td_g_shoot0);
			TextDrawHideForPlayer(playerid, td_g_shoot1);
			gracz[playerid][shoot_td_time] = 0;
		}
	}
	return 1;
}

stock TextDrawSpeedLimit(playerid, speed)
{
	if(speed == 0 && gracz[playerid][td_speedlimit] != speed)
	{
		gracz[playerid][td_speedlimit] = speed;
		PlayerTextDrawHide(playerid, td_p_limit0[playerid]);
		TextDrawHideForPlayer(playerid, td_g_limit0);
		TextDrawHideForPlayer(playerid, td_g_limit1);
	}
	else if(gracz[playerid][td_speedlimit] != speed)
	{
		gracz[playerid][td_speedlimit] = speed;
		new strtd[8];
		format(strtd, 8, "%d", speed);
		PlayerTextDrawSetString(playerid, td_p_limit0[playerid], strtd);
		PlayerTextDrawShow(playerid, td_p_limit0[playerid]);
		TextDrawShowForPlayer(playerid, td_g_limit0);
		TextDrawShowForPlayer(playerid, td_g_limit1);
		PlayerPlaySound(playerid, 5201, 0.0, 0.0, 0.0);
	}
	return 1;
}

stock VHL_PlayerList(playerid, channel[], players_str[], hide = 0)
{
	if(hide == 1) return PlayerTextDrawHide(playerid, vhl_playerlist[playerid]);
	new string_vhl_list[1024];
	format(string_vhl_list, 1024, "[VHL]%s~n~%s", channel, players_str);
	PlayerTextDrawSetString(playerid, vhl_playerlist[playerid], string_vhl_list);
	PlayerTextDrawShow(playerid, vhl_playerlist[playerid]);
	return 1;
}