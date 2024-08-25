//****************************************proxy overload - przeciążanie funkcji
SendClientMessage(playerid, color, message[])
{
	ov_SendClientMessage(playerid, color, message);
	/*if(gracz[playerid][loggedin])
	{
		new formtxt[255];
		format(formtxt, 255, "{%06x}%s", color >>> 8, message);
		mysql_escape_string(formtxt, formtxt);
		mq_format("INSERT INTO `chat_log` (`uid`,`chat`,`time`) VALUES ('%d','%s',CURRENT_TIMESTAMP);", gracz[playerid][UID], formtxt);
		mq_send("SendChatQuery");
	}
	*/
	return 1;
}

SetPlayerCheckpoint(playerid, Float:x, Float:y, Float:z, Float:size)
{
	if(GetPVarInt(playerid, "ov_SetPlayerCheckpoint") == 1) return 0;
	//FIX rozmiarów CP
	SetPVarInt(playerid, "ov_SetPlayerCheckpoint", 1);
	ov_SetPlayerCheckpoint(playerid, x, y, z, size);
	DisablePlayerCheckpoint(playerid);
	SetTimerEx("call_ov_SetPlayerCheckpoint", 501, false, "dffff", playerid, x, y, z, size);
	return 1;
}

forward call_ov_SetPlayerCheckpoint(playerid, Float:x, Float:y, Float:z, Float:size);
public call_ov_SetPlayerCheckpoint(playerid, Float:x, Float:y, Float:z, Float:size)
{
	if(GetPVarInt(playerid, "ov_SetPlayerCheckpoint") == 0) return 0;
	//printf("cp stworzony");
	DisablePlayerCheckpoint(playerid);
	ov_SetPlayerCheckpoint(playerid, x, y, z, size);
	SetPVarInt(playerid, "ov_SetPlayerCheckpoint", 0);
	return 1;
}

enum data_createactor
{
	dca_modelid,
	Float:dca_X,
	Float:dca_Y,
	Float:dca_Z,
	Float:dca_Rotation
};
new vars_CreateActor[MAX_ACTORS][data_createactor];

stock CreateActor(modelid, Float:X, Float:Y, Float:Z, Float:Rotation)
{
	new aid = ov_CreateActor(modelid, X, Y, Z, Rotation);
	vars_CreateActor[aid][dca_modelid] = modelid;
	vars_CreateActor[aid][dca_X] = X;
	vars_CreateActor[aid][dca_Y] = Y;
	vars_CreateActor[aid][dca_Z] = Z;
	vars_CreateActor[aid][dca_Rotation] = Rotation;
	return aid;
}

task Process_CreateActorPos()
{
	for(new a = GetActorPoolSize(); a != -1; a--)
	{
		if(IsValidActor(a))
		{
			SetActorPos(a, vars_CreateActor[a][dca_X], vars_CreateActor[a][dca_Y], vars_CreateActor[a][dca_Z]);
			SetActorFacingAngle(a, vars_CreateActor[a][dca_Rotation]);
		}
	}
	return 1;
}
//****************************************custom
stock nick(p, escape = false)
{
	new n[24];
	if(p != -1) GetPlayerName(p, n, 24);
	else format(n, 24, "SYSTEM");
	if(escape) mysql_escape_string(n, n);
	return n;
}

stock playerip(p, escape = false)
{
	new n[64];
	GetPlayerIp(p, n, 64);
	if(escape) mysql_escape_string(n, n);
	return n;
}

native gpci(playerid, serial [], len);
stock serial(p, escape = false)
{
	new n[64];
	gpci(p,  n, 64);
	if(escape) mysql_escape_string(n, n);
	return n;
}

stock HasTagHL(nickstr[24])
{
	if(strfind(nickstr, "[HL]", true) != -1) return 1;//strdel(wynik, 0, 4);
	return 0;
}

stock KickEx(playerid, reason[])
{
	printf("|KICK| %s | Reason: %s", nick(playerid), reason);
	return SetTimerEx("KickExRun", 50, false, "d", playerid);
}
forward KickExRun(playerid); 
public  KickExRun(playerid) return Kick(playerid);


stock SendClientMessageEx(playerid, color, const text[], {Float, _}:...)
{
	static
	args,
	str[144];
	/*
	*  Custom function that uses #emit to format variables into a string.
	*  This code is very fragile; touching any code here will cause crashing!
	*/
	if ((args = numargs()) == 3)
	{
		format(str, 144, "%s", text);
		SendClientMessage(playerid, color, str);
	}
	else
	{
		while (--args >= 3)
		{
			#emit LCTRL 5
			#emit LOAD.alt args
			#emit SHL.C.alt 2
			#emit ADD.C 12
			#emit ADD
			#emit LOAD.I
			#emit PUSH.pri
		}
		#emit PUSH.S text
		#emit PUSH.C 144
		#emit PUSH.C str
		#emit PUSH.S 8
		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4
		SendClientMessage(playerid, color, str);
		#emit RETN
	}
	return 1;
}


stock SendClientMessageToAllEx(color, const text[], {Float, _}:...)
{
	static
	args,
	str[144];
	/*
	*  Custom function that uses #emit to format variables into a string.
	*  This code is very fragile; touching any code here will cause crashing!
	*/
	if ((args = numargs()) == 2)
	{
		SendClientMessageToAll(color, text);
	}
	else
	{
		while (--args >= 2)
		{
			#emit LCTRL 5
			#emit LOAD.alt args
			#emit SHL.C.alt 2
			#emit ADD.C 12
			#emit ADD
			#emit LOAD.I
			#emit PUSH.pri
		}
		#emit PUSH.S text
		#emit PUSH.C 144
		#emit PUSH.C str
		#emit LOAD.S.pri 8
		#emit ADD.C 4
		#emit PUSH.pri
		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4
		SendClientMessageToAll(color, str);
		#emit RETN
	}
	return 1;
}


stock udb_hash(buf[]) 
{
	new length=strlen(buf);
	new s1 = 1;
	new s2 = 0;
	new n;
	for (n=0; n<length; n++)
	{
		s1 = (s1 + buf[n]) % 65521;
		s2 = (s2 + s1)     % 65521;
	}
	return (s2 << 16) + s1;
}


stock GetVehicleName(model)
{
	new name[32];
	format(name,32,"error");
	switch(model)
	{
		case 400: format(name,32,"Landstalker");
		case 401: format(name,32,"Bravura");
		case 402: format(name,32,"Buffalo");
		case 403: format(name,32,"Linerunner");
		case 404: format(name,32,"Perenniel");
		case 405: format(name,32,"Sentinel");
		case 406: format(name,32,"Dumper");
		case 407: format(name,32,"Firetruck");
		case 408: format(name,32,"Trashmaster");
		case 409: format(name,32,"Stretch");
		case 410: format(name,32,"Manana");
		case 411: format(name,32,"Infernus");
		case 412: format(name,32,"Voodoo");
		case 413: format(name,32,"Pony");
		case 414: format(name,32,"Mule");
		case 415: format(name,32,"Cheetah");
		case 416: format(name,32,"Ambulance");
		case 417: format(name,32,"Leviathan");
		case 418: format(name,32,"Moonbeam");
		case 419: format(name,32,"Esperanto");
		case 420: format(name,32,"Taxi");
		case 421: format(name,32,"Washington");
		case 422: format(name,32,"Bobcat");
		case 423: format(name,32,"Mr Whoopee");
		case 424: format(name,32,"BF Injection");
		case 425: format(name,32,"Hunter");
		case 426: format(name,32,"Premier");
		case 427: format(name,32,"Enforcer");
		case 428: format(name,32,"Securicar");
		case 429: format(name,32,"Banshee");
		case 430: format(name,32,"Predator");
		case 431: format(name,32,"Bus");
		case 432: format(name,32,"Rhino");
		case 433: format(name,32,"Barracks");
		case 434: format(name,32,"Hotknife");
		case 435: format(name,32,"Naczepa art.: Stale (big)");
		case 436: format(name,32,"Previon");
		case 437: format(name,32,"Coach");
		case 438: format(name,32,"Cabbie");
		case 439: format(name,32,"Stallion");
		case 440: format(name,32,"Rumpo");
		case 441: format(name,32,"RC Bandit");
		case 442: format(name,32,"Romero");
		case 443: format(name,32,"Packer");
		case 444: format(name,32,"Monster");
		case 445: format(name,32,"Admiral");
		case 446: format(name,32,"Squallo");
		case 447: format(name,32,"Seasparrow");
		case 448: format(name,32,"Pizzaboy");
		case 449: format(name,32,"Tram");
		case 450: format(name,32,"Naczepa art.: Sypkie");
		case 451: format(name,32,"Turismo");
		case 452: format(name,32,"Speeder");
		case 453: format(name,32,"Reefer");
		case 454: format(name,32,"Tropic");
		case 455: format(name,32,"Flatbed");
		case 456: format(name,32,"Yankee");
		case 457: format(name,32,"Caddy");
		case 458: format(name,32,"Solair");
		case 459: format(name,32,"Berkley's RC Van");
		case 460: format(name,32,"Skimmer");
		case 461: format(name,32,"PCJ-600");
		case 462: format(name,32,"Faggio");
		case 463: format(name,32,"Freeway");
		case 464: format(name,32,"RC Baron");
		case 465: format(name,32,"RC Raider");
		case 466: format(name,32,"Glendale");
		case 467: format(name,32,"Oceanic");
		case 468: format(name,32,"Sanchez");
		case 469: format(name,32,"Sparrow");
		case 470: format(name,32,"Patriot");
		case 471: format(name,32,"Quad");
		case 472: format(name,32,"Coastguard");
		case 473: format(name,32,"Dinghy");
		case 474: format(name,32,"Hermes");
		case 475: format(name,32,"Sabre");
		case 476: format(name,32,"Rustler");
		case 477: format(name,32,"ZR-350");
		case 478: format(name,32,"Walton");
		case 479: format(name,32,"Regina");
		case 480: format(name,32,"Comet");
		case 481: format(name,32,"BMX");
		case 482: format(name,32,"Burrito");
		case 483: format(name,32,"Camper");
		case 484: format(name,32,"Marquis");
		case 485: format(name,32,"Baggage");
		case 486: format(name,32,"Dozer");
		case 487: format(name,32,"Maverick");
		case 488: format(name,32,"SAN News Maverick");
		case 489: format(name,32,"Rancher");
		case 490: format(name,32,"FBI Rancher");
		case 491: format(name,32,"Virgo");
		case 492: format(name,32,"Greenwood");
		case 493: format(name,32,"Jetmax");
		case 494: format(name,32,"Hotring Racer");
		case 495: format(name,32,"Sandking");
		case 496: format(name,32,"Blista Compact");
		case 497: format(name,32,"Police Maverick");
		case 498: format(name,32,"Boxville");
		case 499: format(name,32,"Benson");
		case 500: format(name,32,"Mesa");
		case 501: format(name,32,"RC Goblin");
		case 502: format(name,32,"Hotring Racer");
		case 503: format(name,32,"Hotring Racer");
		case 504: format(name,32,"Bloodring Banger");
		case 505: format(name,32,"Rancher");
		case 506: format(name,32,"Super GT");
		case 507: format(name,32,"Elegant");
		case 508: format(name,32,"Journey");
		case 509: format(name,32,"Bike");
		case 510: format(name,32,"Mountain Bike");
		case 511: format(name,32,"Beagle");
		case 512: format(name,32,"Cropduster");
		case 513: format(name,32,"Stuntplane");
		case 514: format(name,32,"Tanker");
		case 515: format(name,32,"Roadtrain");
		case 516: format(name,32,"Nebula");
		case 517: format(name,32,"Majestic");
		case 518: format(name,32,"Buccaneer");
		case 519: format(name,32,"Shamal");
		case 520: format(name,32,"Hydra");
		case 521: format(name,32,"FCR-900");
		case 522: format(name,32,"NRG-500");
		case 523: format(name,32,"HPV1000");
		case 524: format(name,32,"Cement Truck");
		case 525: format(name,32,"Towtruck");
		case 526: format(name,32,"Fortune");
		case 527: format(name,32,"Cadrona");
		case 528: format(name,32,"FBI Truck");
		case 529: format(name,32,"Willard");
		case 530: format(name,32,"Forklift");
		case 531: format(name,32,"Tractor");
		case 532: format(name,32,"Combine Harvester");
		case 533: format(name,32,"Feltzer");
		case 534: format(name,32,"Remington");
		case 535: format(name,32,"Slamvan");
		case 536: format(name,32,"Blade");
		case 537: format(name,32,"Freight");
		case 538: format(name,32,"Brownstreak");
		case 539: format(name,32,"Vortex");
		case 540: format(name,32,"Vincent");
		case 541: format(name,32,"Bullet");
		case 542: format(name,32,"Clover");
		case 543: format(name,32,"Sadler");
		case 544: format(name,32,"Firetruck LA");
		case 545: format(name,32,"Hustler");
		case 546: format(name,32,"Intruder");
		case 547: format(name,32,"Primo");
		case 548: format(name,32,"Cargobob");
		case 549: format(name,32,"Tampa");
		case 550: format(name,32,"Sunrise");
		case 551: format(name,32,"Merit");
		case 552: format(name,32,"Utility Van");
		case 553: format(name,32,"Nevada");
		case 554: format(name,32,"Yosemite");
		case 555: format(name,32,"Windsor");
		case 556: format(name,32,"Monster A");
		case 557: format(name,32,"Monster B");
		case 558: format(name,32,"Uranus");
		case 559: format(name,32,"Jester");
		case 560: format(name,32,"Sultan");
		case 561: format(name,32,"Stratum");
		case 562: format(name,32,"Elegy");
		case 563: format(name,32,"Raindance");
		case 564: format(name,32,"RC Tiger");
		case 565: format(name,32,"Flash");
		case 566: format(name,32,"Tahoma");
		case 567: format(name,32,"Savanna");
		case 568: format(name,32,"Bandito");
		case 569: format(name,32,"Freight Flat Trailer");
		case 570: format(name,32,"Streak Trailer");
		case 571: format(name,32,"Kart");
		case 572: format(name,32,"Mower");
		case 573: format(name,32,"Dune");
		case 574: format(name,32,"Sweeper");
		case 575: format(name,32,"Broadway");
		case 576: format(name,32,"Tornado");
		case 577: format(name,32,"AT400");
		case 578: format(name,32,"DFT-30");
		case 579: format(name,32,"Huntley");
		case 580: format(name,32,"Stafford");
		case 581: format(name,32,"BF-400");
		case 582: format(name,32,"Newsvan");
		case 583: format(name,32,"Tug");
		case 584: format(name,32,"Naczepa art.: Plyn/Gaz");
		case 585: format(name,32,"Emperor");
		case 586: format(name,32,"Wayfarer");
		case 587: format(name,32,"Euros");
		case 588: format(name,32,"Hotdog");
		case 589: format(name,32,"Club");
		case 590: format(name,32,"Freight Box Trailer");
		case 591: format(name,32,"Naczepa art.: Stale (small)");
		case 592: format(name,32,"Andromada");
		case 593: format(name,32,"Dodo");
		case 594: format(name,32,"RC Cam");
		case 595: format(name,32,"Launch");
		case 596: format(name,32,"Police Car (LSPD)");
		case 597: format(name,32,"Police Car (SFPD)");
		case 598: format(name,32,"Police Car (LVPD)");
		case 599: format(name,32,"Police Ranger");
		case 600: format(name,32,"Picador");
		case 601: format(name,32,"S.W.A.T.");
		case 602: format(name,32,"Alpha");
		case 603: format(name,32,"Phoenix");
		case 604: format(name,32,"Glendale Shit");
		case 605: format(name,32,"Sadler Shit");
		case 606: format(name,32,"Baggage Trailer A");
		case 607: format(name,32,"Baggage Trailer B");
		case 608: format(name,32,"Tug Stairs Trailer");
		case 609: format(name,32,"Boxville");
		case 610: format(name,32,"Farm Trailer");
		case 611: format(name,32,"Utility Trailer");
	}
	return name;
}

stock GetPlayerUID(playerid) return gracz[playerid][UID];


stock GetDynamicObjectModel(oid)
{
	if(IsValidDynamicObject(oid))
	{
		return Streamer_GetIntData(STREAMER_TYPE_OBJECT, oid, E_STREAMER_MODEL_ID);
	}
	return 0;
}


stock DzienTygodnia(day)
{
	new str_dzien[16];
	switch(day)
	{
		case 0: format(str_dzien, 16, "poniedzialek");
		case 1: format(str_dzien, 16, "wtorek");
		case 2: format(str_dzien, 16, "sroda");
		case 3: format(str_dzien, 16, "czwartek");
		case 4: format(str_dzien, 16, "piatek");
		case 5: format(str_dzien, 16, "sobota");
		case 6: format(str_dzien, 16, "niedziela");
	}
	return str_dzien;
}


stock SecToTime(seconds, &days, &hours, &minutes, &secc)
{

	days = floatround((seconds / 86400), floatround_floor); // get Days
	secc = (seconds - (days * 86400));// remove days from total seconds
	hours = floatround((secc / 3600), floatround_floor); // get Hours
	secc = (secc - (hours * 3600)); // remove Hours from secs
	minutes = floatround((secc / 60), floatround_floor);// get Mins
	secc = (secc - (minutes * 60));// remove Mins from secs, whats left is seconds
/*while(seconds > 59)
{
	seconds -= 60;
	minutes++;
}
while(minutes > 59)
{
	minutes -= 60;
	hours++;
}
while(hours > 23)
{
	hours -= 24;
	days++;
}*/

//secc = seconds;
	return 1;
}

stock SecToTime2(seconds, &hours, &minutes)
{
	while(seconds > 59)
	{
		seconds -= 60;
		minutes++;
	}
	while(minutes > 59)
	{
		minutes -= 60;
		hours++;
	}
	return 1;
}

//System hałasu
/*GetPlayerSpeed(playerid):
5 = chodzenie
13 = Chodzenie na kucaka.
19 Bieg.
*/
new Float:ST[4][MAX_PLAYERS];
stock GetDzwiek(playerid)
{
	if(IsPlayerInAnyVehicle(playerid) && EngineStatus(GetPlayerVehicleID(playerid))) return 20;
	GetPlayerVelocity(playerid,ST[0][playerid],ST[1][playerid],ST[2][playerid]);
	ST[3][playerid] = floatsqroot(floatpower(floatabs(ST[0][playerid]), 2.0) + floatpower(floatabs(ST[1][playerid]), 2.0) + floatpower(floatabs(ST[2][playerid]), 2.0)) * 179.28625;
	return floatround(ST[3][playerid]);
}
new Float:STP[4][MAX_VEHICLES];
stock GetVehSpeed(vehicleid)
{
	GetVehicleVelocity(vehicleid,STP[0][vehicleid],STP[1][vehicleid],STP[2][vehicleid]);
	STP[3][vehicleid] = floatsqroot(floatpower(floatabs(STP[0][vehicleid]), 2.0) + floatpower(floatabs(STP[1][vehicleid]), 2.0) + floatpower(floatabs(STP[2][vehicleid]), 2.0)) * 195.0;//213.0;
	return floatround(STP[3][vehicleid]);
}

stock GetSpeedXY(playerid)
{
	GetPlayerVelocity(playerid,ST[0][playerid],ST[1][playerid],ST[2][playerid]);
	ST[3][playerid] = floatsqroot(floatpower(floatabs(ST[0][playerid]), 2.0) + floatpower(floatabs(ST[1][playerid]), 2.0)) * 179.28625;
	return floatround(ST[3][playerid]);
}

stock IsPlayerCrouch(playerid)
{
	if(GetPlayerAnimationIndex(playerid) == 1159) return 1;
	return 0;
}

stock MessageGUI(playerid,firstmessage[],secondmessage[],button1[],button2[])
{
	return ShowPlayerDialog(playerid,146,DIALOG_STYLE_MSGBOX,firstmessage,secondmessage,button1,button2);
}

stock MessageGUIEx(playerid, tytul[],  info[])
{
	MessageGUI(playerid, tytul, info, "Zamknij", "");
	return 1;
}

stock GetWeaponModel(weaponid)
{
	switch(weaponid)
	{
		case 1:
		return 331;
		case 2..8:
		return weaponid+331;
		case 9:
		return 341;
		case 10..15:
		return weaponid+311;
		case 16..18:
		return weaponid+326;
		case 22..29:
		return weaponid+324;
		case 30,31:
		return weaponid+325;
		case 32:
		return 372;
		case 33..45:
		return weaponid+324;
		case 46:
		return 371;
	}
	return 0;
}

stock IsWeaponSlotUsed(playerid, slotid)
{
	new weapondata[2];
	GetPlayerWeaponData(playerid, slotid, weapondata[0], weapondata[1]);
	if(weapondata[0]) return 1;
	return 0;
}

stock procent(Float:value_l, Float:value_h)
{
	new Float:wynik = ((value_l / value_h) * 100.0);
	return floatround(wynik, floatround_floor);
}

stock IsPlayerAimingEx(playerid) 
{
	new anim = GetPlayerAnimationIndex(playerid);
	if (((anim >= 1160) && (anim <= 1163)) || (anim == 1167) || (anim == 1365) || (anim == 1643) || (anim == 1453) || (anim == 220)) return 1;
	if(anim == 361 || anim == 363 || anim == 1331 || anim == 1449) return 1;
	if(GetPlayerWeapon(playerid) != 0)
	if(!IsPlayerInAnyVehicle(playerid))
	{
		new Keys,ud,lr;
		GetPlayerKeys(playerid,Keys,ud,lr);
		if(Keys == 128) return 1;
	}
	return 0;
}

stock RandomEx(min, max)
{
	return random(max - min) + min;
}

stock SetGoodSkillLevel(playerid)
{
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 1);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL_SILENCED, 1);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_DESERT_EAGLE, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SHOTGUN, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN, 1);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SPAS12_SHOTGUN, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 1);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MP5, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_AK47, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_M4, 999);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_SNIPERRIFLE, 999);
	return 1;
}

stock GetPlayerSpeed(playerid)
{
	if(IsPlayerInAnyVehicle(playerid)) return 0;
	new Float:STex[4];
	GetPlayerVelocity(playerid,STex[0],STex[1],STex[2]);
	STex[3] = floatsqroot(floatpower(floatabs(STex[0]), 2.0) + floatpower(floatabs(STex[1]), 2.0)) * 200.0;
	return floatround(STex[3]);
}
stock ShiftRGBAToABGR(color)
{
	new r, g, b, a;
	r = (color >>> 24);
	g = (color >>> 16 & 0xFF);
	b = (color >>> 8 & 0xFF);
	a = (color  & 0xFF);
	color = (a & 0xFF) | ((b & 0xFF) << 8) | ((g & 0xFF) << 16) | (r << 24);
	return color;
}

stock GetPlayerIGName(uid)
{
	new wynik[24],query[256];
	mysql_format(g_SQL,query,256,"SELECT `Nick` FROM `Konta` WHERE `id`='%d';",uid);
	new Cache:result = mysql_query(g_SQL,query);
	if(cache_get_row_count_ex()) cache_get_value_name(0, "Nick", wynik);
	else format(wynik,24,"-brak-");
	cache_delete(result);
	return wynik;
}
stock Error(playerid, string[])
{
	new strError[144];
	format(strError, 144, "(("COL_RED"Wystąpił błąd:"COL_WHITE" %s"COL_WHITE"))", string);
	ov_SendClientMessage(playerid, -1, strError);
	return 1;
}

stock Info(playerid, string[])
{
	SendClientMessageEx(playerid, -1, "(("COL_GREEN"Info:"COL_WHITE" %s"COL_WHITE"))", string);
	return 1;
}

stock GetXYInFrontOfPlayer(playerid, &Float:ifx, &Float:ify, Float:distance)
{
	new Float:a;
	GetPlayerPos(playerid, ifx, ify, a);
	GetPlayerFacingAngle(playerid, a);
	if(GetPlayerVehicleID(playerid))
	{
		GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
	}
	ifx += (distance * floatsin(-a, degrees));
	ify += (distance * floatcos(-a, degrees));
	return 1;
}


stock GetXYInBackOfPlayer(playerid, &Float:ifx, &Float:ify, Float:distance)
{
	new Float:a;
	GetPlayerPos(playerid, ifx, ify, a);
	GetPlayerFacingAngle(playerid, a);
	if(GetPlayerVehicleID(playerid))
	{
		GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
	}
	ifx -= (distance * floatsin(-a, degrees));
	ify -= (distance * floatcos(-a, degrees));
	return 1;
}

stock GetXYInLeftOfPlayer(playerid, &Float:ifx, &Float:ify, Float:distance)
{
	new Float:a;
	GetPlayerPos(playerid, ifx, ify, a);
	GetPlayerFacingAngle(playerid, a);
	if(GetPlayerVehicleID(playerid))
	{
		GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
	}
	a += 90.0;
	if(a > 360.0)
	{
		a = a-360.0;
	}
	ifx += (distance * floatsin(-a, degrees));
	ify += (distance * floatcos(-a, degrees));
	return 1;
}

stock GetXYInLeftOfPlayerEx(playerid, &Float:ifx, &Float:ify, Float:distance)
{
	new Float:a;
	GetPlayerPos(playerid, ifx, ify, a);
	GetPlayerFacingAngle(playerid, a);
	a += 90.0;
	if(a > 360.0)
	{
		a = a-360.0;
	}
	ifx += (distance * floatsin(-a, degrees));
	ify += (distance * floatcos(-a, degrees));
	return 1;
}

stock GetXYInRightOfPlayer(playerid, &Float:ifx, &Float:ify, Float:distance)
{
	new Float:a;
	GetPlayerPos(playerid, ifx, ify, a);
	GetPlayerFacingAngle(playerid, a);
	if(GetPlayerVehicleID(playerid))
	{
		GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
	}
	a += 90.0;
	if(a > 360.0)
	{
		a = a-360.0;
	}
	ifx -= (distance * floatsin(-a, degrees));
	ify -= (distance * floatcos(-a, degrees));
	return 1;
}

stock GetXYInRightOfPlayerEx(playerid, &Float:ifx, &Float:ify, Float:distance)
{
	new Float:a;
	GetPlayerPos(playerid, ifx, ify, a);
	GetPlayerFacingAngle(playerid, a);
	a += 90.0;
	if(a > 360.0)
	{
		a = a-360.0;
	}
	ifx -= (distance * floatsin(-a, degrees));
	ify -= (distance * floatcos(-a, degrees));
	return 1;
}
//*********************************************************************************************************

stock GetXYInFrontOfPos(Float:ox, Float:oy, Float:a, &Float:ifx, &Float:ify, Float:distance)
{
	ifx = ox;
	ify = oy;
	ifx += (distance * floatsin(-a, degrees));
	ify += (distance * floatcos(-a, degrees));
	return 1;
}

stock GetXYInBackOfPos(Float:ox, Float:oy, Float:a, &Float:ifx, &Float:ify, Float:distance)
{
	ifx = ox;
	ify = oy;
	ifx -= (distance * floatsin(-a, degrees));
	ify -= (distance * floatcos(-a, degrees));
	return 1;
}

stock GetXYInLeftOfPos(Float:ox, Float:oy, Float:a, &Float:ifx, &Float:ify, Float:distance)
{
	ifx = ox;
	ify = oy;
	a += 90.0;
	if(a > 360.0)
	{
		a = a-360.0;
	}
	ifx += (distance * floatsin(-a, degrees));
	ify += (distance * floatcos(-a, degrees));
	return 1;
}

stock GetXYInRightOfPos(Float:ox, Float:oy, Float:a, &Float:ifx, &Float:ify, Float:distance)
{
	ifx = ox;
	ify = oy;
	a += 90.0;
	if(a > 360.0)
	{
		a = a-360.0;
	}
	ifx -= (distance * floatsin(-a, degrees));
	ify -= (distance * floatcos(-a, degrees));
	return 1;
}

//*************************************************************************************
stock GetXYInFrontOfVehicle(vehicleid, &Float:ifx, &Float:ify, Float:distance)
{
	new Float:a;
	GetVehiclePos(vehicleid, ifx, ify, a);
	GetVehicleZAngle(vehicleid, a);
	ifx += (distance * floatsin(-a, degrees));
	ify += (distance * floatcos(-a, degrees));
	return 1;
}

stock GetXYInBackOfVehicle(vehicleid, &Float:ifx, &Float:ify, Float:distance)
{
	new Float:a;
	GetVehiclePos(vehicleid, ifx, ify, a);
	GetVehicleZAngle(vehicleid, a);
	ifx -= (distance * floatsin(-a, degrees));
	ify -= (distance * floatcos(-a, degrees));
	return 1;
}

stock compare(text1[], text2[], bool:ignorec = true)
{
	if(isnull(text1) || isnull(text2)) return 0;
	if(!strcmp(text1, text2, ignorec)) return 1;
	return 0;
}

forward Float:GetDistanceBetweenPoints(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2);
public Float:GetDistanceBetweenPoints(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2)
{
	return VectorSize(x1-x2, y1-y2, z1-z2);
}

stock PlayerPoolSize() 
{
	if(serwer[playerPoolSize] > 1000) serwer[playerPoolSize] = 0;
	if(serwer[playerPoolSize] < 0) serwer[playerPoolSize] = 0;
	return serwer[playerPoolSize];
}

stock Interpunkcja(txt[])
{
	new wynik = 0;
	for(new i; i < strlen(txt); i++)
	{
		if(txt[i] == '.')
		{
			wynik++;
		}
		if(txt[i] == '?')
		{
			wynik++;
		}
		if(txt[i] == '!')
		{
			wynik++;
		}
	}
	return wynik;
}

stock ProxDetector(playerid, Float:radius, string[], col1, col2, col3, col4, col5)
{
	new Float:x, Float:y, Float:z;
	if(IsPlayerNPC(playerid)) FCNPC_GetPosition(playerid, x, y, z);
	else GetPlayerPos(playerid, x, y, z);
	new Float:ix, Float:iy, Float:iz;
	new Float:cx, Float:cy, Float:cz;
	for(new i = PlayerPoolSize(); i != -1; i--)
	{
		if(!gracz[i][loggedin]) continue;
		if(GetPlayerInterior(playerid) == GetPlayerInterior(i) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i))
		{
			GetPlayerPos(i, ix, iy, iz);
			cx = (x - ix);
			cy = (y - iy);
			cz = (z - iz);
			if(((cx < radius/16) && (cx > -radius/16)) && ((cy < radius/16) && (cy > -radius/16)) && ((cz < radius/16) && (cz > -radius/16)))
			{
				SendMSGLamane(i,col1, string);
			}
			else if(((cx < radius/8) && (cx > -radius/8)) && ((cy < radius/8) && (cy > -radius/8)) && ((cz < radius/8) && (cz > -radius/8)))
			{
				SendMSGLamane(i,col2, string);
			}
			else if(((cx < radius/4) && (cx > -radius/4)) && ((cy < radius/4) && (cy > -radius/4)) && ((cz < radius/4) && (cz > -radius/4)))
			{
				SendMSGLamane(i,col3, string);
			}
			else if(((cx < radius/2) && (cx > -radius/2)) && ((cy < radius/2) && (cy > -radius/2)) && ((cz < radius/2) && (cz > -radius/2)))
			{
				SendMSGLamane(i,col4, string);
			}
			else if(((cx < radius) && (cx > -radius)) && ((cy < radius) && (cy > -radius)) && ((cz < radius) && (cz > -radius)))
			{
				SendMSGLamane(i,col5, string);
			}
		}
	}
	return 1;
}

#define EX_SPLITLENGTH 90
stock SendMSGLamane(playerid, color, final[])
{
	new buffer[EX_SPLITLENGTH+15];
	new len = strlen(final);
	if(len>EX_SPLITLENGTH)
	{
		new times = (len/EX_SPLITLENGTH);
		for(new i = 0; i < times+1; i++)
		{
			strdel(buffer, 0, EX_SPLITLENGTH+15);
			if(len-(i*EX_SPLITLENGTH)>EX_SPLITLENGTH)
			{
				strmid(buffer, final, EX_SPLITLENGTH*i, EX_SPLITLENGTH*(i+1));
				format(buffer, sizeof(buffer), "%s...", buffer);
			}
			else
			{
				strmid(buffer, final, EX_SPLITLENGTH*i, len);
			}
			SendClientMessage(playerid, color, buffer);
		}
	}
	else
	{
		SendClientMessage(playerid, color, final);
	}
	return 1;
}

stock SendNearByMessage(playerid, color, str[], Float:radius)
{
	for(new i = PlayerPoolSize(); i != -1; i--)
	{
		if(gracz[playerid][loggedin])
		{
			if(IsPlayerInRangeOfPoint(i, radius, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]))
			{
				if(GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i) && GetPlayerInterior(playerid) == GetPlayerInterior(i))
				{
					SendMSGLamane(i, color, str);
				}
			}
		}
	}
	return 1;
}

stock SendNearByMessage_noplayerid(playerid, color, str[], Float:radius)
{
	for(new i = PlayerPoolSize(); i != -1; i--)
	{
		if(i == playerid) continue;
		if(gracz[playerid][loggedin])
		{
			if(IsPlayerInRangeOfPoint(i, radius, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]))
			{
				if(GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i) && GetPlayerInterior(playerid) == GetPlayerInterior(i))
				{
					SendMSGLamane(i, color, str);
				}
			}
		}
	}
	return 1;
}


forward UnFreeze(playerid);
public UnFreeze(playerid)
{
	TogglePlayerControllable(playerid, true);
	return 1;
}

new s_AnimationLibraries[][] = 
{
	"AIRPORT",    "ATTRACTORS",   "BAR",                 "BASEBALL",
	"BD_FIRE",    "BEACH",            "BENCHPRESS",  "BF_INJECTION",
	"BIKED",          "BIKEH",        "BIKELEAP",        "BIKES",
	"BIKEV",          "BIKE_DBZ",     "BMX",             "BOMBER",
	"BOX",            "BSKTBALL",     "BUDDY",           "BUS",
	"CAMERA",         "CAR",          "CARRY",           "CAR_CHAT",
	"CASINO",         "CHAINSAW",     "CHOPPA",          "CLOTHES",
	"COACH",          "COLT45",       "COP_AMBIENT", "COP_DVBYZ",
	"CRACK",          "CRIB",         "DAM_JUMP",         "DANCING",
	"DEALER",         "DILDO",        "DODGE",            "DOZER",
	"DRIVEBYS",   "FAT",          "FIGHT_B",      "FIGHT_C",
	"FIGHT_D",    "FIGHT_E",      "FINALE",               "FINALE2",
	"FLAME",      "FLOWERS",      "FOOD",                 "FREEWEIGHTS",
	"GANGS",      "GHANDS",       "GHETTO_DB",    "GOGGLES",
	"GRAFFITI",   "GRAVEYARD",    "GRENADE",      "GYMNASIUM",
	"HAIRCUTS",   "HEIST9",       "INT_HOUSE",    "INT_OFFICE",
	"INT_SHOP",   "JST_BUISNESS", "KART",                 "KISSING",
	"KNIFE",      "LAPDAN1",              "LAPDAN2",      "LAPDAN3",
	"LOWRIDER",   "MD_CHASE",     "MD_END",               "MEDIC",
	"MISC",       "MTB",                  "MUSCULAR",     "NEVADA",
	"ON_LOOKERS", "OTB",                  "PARACHUTE",    "PARK",
	"PAULNMAC",   "PED",                  "PLAYER_DVBYS", "PLAYIDLES",
	"POLICE",     "POOL",                 "POOR",                 "PYTHON",
	"QUAD",       "QUAD_DBZ",     "RAPPING",      "RIFLE",
	"RIOT",       "ROB_BANK",     "ROCKET",               "RUSTLER",
	"RYDER",      "SCRATCHING",   "SHAMAL",               "SHOP",
	"SHOTGUN",    "SILENCED",     "SKATE",                "SMOKING",
	"SNIPER",     "SPRAYCAN",     "STRIP",                "SUNBATHE",
	"SWAT",       "SWEET",                "SWIM",                 "SWORD",
	"TANK",       "TATTOOS",              "TEC",                  "TRAIN",
	"TRUCK",      "UZI",                  "VAN",                  "VENDING",
	"VORTEX",     "WAYFARER",     "WEAPONS",      "WUZI",
	"WOP",        "GFUNK",                "RUNNINGMAN"
};

stock PreloadAnimations(playerid)
{
	/*for(new i = 0; i < sizeof(s_AnimationLibraries); i ++)
	{
		//ApplyAnimation(playerid, s_AnimationLibraries[i], "null", 0.0, 0, 0, 0, 0, 0);
		SetTimerEx("Task_PreloadAnim", 50+(i*50), false, "dd", playerid, i);
	}*/
	SetTimerEx("Task_PreloadAnim", 30, false, "dd", playerid, 0);
	return 1;
}

task Task_PreloadAnim(playerid, animlibid)
{
	if(!logged(playerid)) return 1;
	ApplyAnimation(playerid, s_AnimationLibraries[animlibid], "null", 0.0, 0, 0, 0, 0, 0);
	if(animlibid < sizeof(s_AnimationLibraries)-1) SetTimerEx("Task_PreloadAnim", 30, false, "dd", playerid, animlibid+1);
	return 1;
}

stock text_bar(proc)
{
	new bar[32];
	switch(proc)
	{
		case 0..9: format(bar, 32, ""COL_RED"|");
		case 10..19: format(bar, 32, ""COL_RED"||");
		case 20..29: format(bar, 32, ""COL_RED"|||");
		case 30..39: format(bar, 32, ""COL_YELLOW"||||");
		case 40..49: format(bar, 32, ""COL_YELLOW"|||||");
		case 50..59: format(bar, 32, ""COL_YELLOW"||||||");
		case 60..69: format(bar, 32, ""COL_YELLOW"|||||||");
		case 70..79: format(bar, 32, ""COL_GREEN"||||||||");
		case 80..89: format(bar, 32, ""COL_GREEN"|||||||||");
		case 90..100: format(bar, 32, ""COL_GREEN"||||||||||");
	}
	return bar;
}

new AllowedCharacters[] =
{
		"0","1","2","3","4","5","6","7","8","9",
		"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r", "s","t","u","v","w","x","y","z",
		"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"
};

stock CheckAllowedChar(string[])
{
	new l=strlen(string), ll=sizeof(AllowedCharacters);
	new n;
	for(new i=0; i<l; i++)
	{
		for(n=0; n<ll; n++)
		if(string[i] == AllowedCharacters[n])
		break;
		if(n==ll)
		return false;
	}
	return true;
}


stock isvip(playerid)
{
	if(gracz[playerid][AdminLevel] > 0) return 1;
	if(gracz[playerid][vip] > serwer[time_timestamp]) return 1;
	return 0;
}

stock Spam(playerid, spamid = 0, time = 1, infoplayer = true)
{
	if(gracz[playerid][time_spam][spamid] > serwer[time_timestamp])
	{
		if(infoplayer)
		{
			new str[100];
			format(str, 100, "(("COL_RED"Wystąpił błąd:"COL_WHITE" Odczekaj %d sekund.))", gracz[playerid][time_spam][spamid]-serwer[time_timestamp]);
			ov_SendClientMessage(playerid, -1, str);
		}
		return 1;
	}
	gracz[playerid][time_spam][spamid] = serwer[time_timestamp]+time;
	return 0;
}

stock strlenex(const string[])//nie liczy: od klamry do klamry//by sebaqq6
{
	new wynik;
	new bool:paused;
	for(new c; c < strlen(string); c++)
	{
		if(string[c] == '{') paused = true;
		if(!paused)
		{
			wynik++;
		}
		if(string[c] == '}') paused = false;
	}
	return wynik;
}

stock log(file[], txt[])
{
	new
	 File:lFile = fopen(file, io_append),
	 logData[178],
		fyear, fmonth, fday,
		fhour, fminute, fsecond;
		
 	getdate(fyear, fmonth, fday);
	gettime(fhour, fminute, fsecond);
	
	format(logData, sizeof(logData),"[%02d/%02d/%04d %02d:%02d:%02d] %s \r\n", fday, fmonth, fyear, fhour, fminute, fsecond, txt);
	fwrite(lFile, logData);

	fclose(lFile);
	return 1;
}
/*
CMD:circletest(playerid, params[])
{
	//CreateFire(gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]);
	new Float:radius = float(strval(params));
	printf("pozar: %f, %f, %f, %0.1f", gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], radius);
	new Float:fPos[2];
	fPos[0] = gracz[playerid][PosX];
	fPos[1] = gracz[playerid][PosY];
	new Float:diff = 10.0;
	for(new pz; pz < 10; pz += 5)
	{
		new Float:coord[3];
		for(new a = 0; a < 360; a++)
		{
			coord[0] = (fPos[0] + (radius * floatcos(coord[2], degrees)));
			coord[1] = (fPos[1] + (radius * floatsin(coord[2], degrees)));
			CreateFire(coord[0], coord[1], gracz[playerid][PosZ]+float(pz));
			coord[2] += diff;
			if(!(coord[2] < 360.0)) break;
		}
	}
	DoneInfo();
	return 1;
}
*/


stock logf(file[], text[], {Float, _}:...)
{
	static
	args,
	str[256];
	/*
	*  Custom function that uses #emit to format variables into a string.
	*  This code is very fragile; touching any code here will cause crashing!
	*/
	if ((args = numargs()) == 2)
	{
		log(file, text);
	}
	else
	{
		while (--args >= 2)
		{
			#emit LCTRL 5
			#emit LOAD.alt args
			#emit SHL.C.alt 2
			#emit ADD.C 12
			#emit ADD
			#emit LOAD.I
			#emit PUSH.pri
		}
		#emit PUSH.S text
		#emit PUSH.C 256
		#emit PUSH.C str
		#emit LOAD.S.pri 8
		#emit ADD.C 4
		#emit PUSH.pri
		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4
		log(file, str);
		#emit RETN
	}
	return 1;
}

stock Interwencja(adminid, targetid, time, penalty, reason[])
{
	serwer[interwencja_time] = gettime()+15;
	switch(penalty)
	{
		case PENALTY_KICK:
		{
			//SendClientMessageToAllEx(0xFF0000FF, "«KICK» "COL_ORANGE"%s "COL_RED"wyrzucił gracza "COL_GREEN"%s"COL_RED".", nick(adminid), nick(targetid));
 			//SendClientMessageToAllEx(0xFF0000FF, "«KICK» Powód: "COL_WHITE"%s", reason);
 			format(temp_string, 512, "~p~KICK ~b~~n~~g~Gracz: ~y~%s~n~~r~Nadajacy: ~y~%s~n~~p~Powod: ~y~%s", nick(targetid), nick(adminid), reason);
		}
		case PENALTY_BAN:
		{
			//SendClientMessageToAllEx(0xFF0000FF, "«BAN» "COL_ORANGE"%s "COL_RED"zbanował gracza "COL_GREEN"%s"COL_RED" na "COL_BLUE"%d dni"COL_RED".", nick(adminid), nick(targetid), time);
 			//SendClientMessageToAllEx(0xFF0000FF, "«BAN» Powód: "COL_WHITE"%s", reason);
 			format(temp_string, 512, "~p~BAN ~b~~w~(~y~%d dni~w~)~n~~g~Gracz: ~y~%s~n~~r~Nadajacy: ~y~%s~n~~p~Powod: ~y~%s", time, nick(targetid), nick(adminid), reason);
		}
		case PENALTY_MUTE:
		{
			//SendClientMessageToAllEx(0xFF0000FF, "«MUTE» "COL_ORANGE"%s "COL_RED"wyciszył gracza "COL_GREEN"%s"COL_RED" na "COL_BLUE"%d minut"COL_RED".", nick(adminid), nick(targetid), time);
 			//SendClientMessageToAllEx(0xFF0000FF, "«MUTE» Powód: "COL_WHITE"%s", reason);
 			format(temp_string, 512, "~p~MUTE ~b~~w~(~y~%d minut~w~)~n~~g~Gracz: ~y~%s~n~~r~Nadajacy: ~y~%s~n~~p~Powod: ~y~%s", time, nick(targetid), nick(adminid), reason);
		}
		case PENALTY_MUTE_VHL:
		{
			//SendClientMessageToAllEx(0xFF0000FF, "«MUTE» "COL_ORANGE"%s "COL_RED"wyciszył gracza "COL_GREEN"%s"COL_RED" na "COL_BLUE"%d minut"COL_RED".", nick(adminid), nick(targetid), time);
 			//SendClientMessageToAllEx(0xFF0000FF, "«MUTE» Powód: "COL_WHITE"%s", reason);
 			format(temp_string, 512, "~p~MUTE(czat glosowy) ~b~~w~(~y~%d minut~w~)~n~~g~Gracz: ~y~%s~n~~r~Nadajacy: ~y~%s~n~~p~Powod: ~y~%s", time, nick(targetid), nick(adminid), reason);
		}
		case PENALTY_JAIL:
		{
			//SendClientMessageToAllEx(0xFF0000FF, "«JAIL» "COL_ORANGE"%s "COL_RED"uwięził gracza "COL_GREEN"%s"COL_RED" na "COL_BLUE"%d minut"COL_RED".", nick(adminid), nick(targetid), time);
 			//SendClientMessageToAllEx(0xFF0000FF, "«JAIL» Powód: "COL_WHITE"%s", reason);
 			format(temp_string, 512, "~p~ADMIN JAIL ~b~~w~(~y~%d minut~w~)~n~~g~Gracz: ~y~%s~n~~r~Nadajacy: ~y~%s~n~~p~Powod: ~y~%s", time, nick(targetid), nick(adminid), reason);
		}
		case SCOREADD:
		{
			format(temp_string, 512, "~g~~h~~h~~h~NAGRODA ~b~~w~(~g~~h~~h~~h~+~y~%d score~w~)~n~~g~Gracz: ~y~%s~n~~r~Nadajacy: ~y~%s~n~~p~Powod: ~y~%s", time, nick(targetid), nick(adminid), reason);
		}
		case SCOREDEL:
		{
			format(temp_string, 512, "~p~KARA ~b~~w~(~r~~h~~h~~h~-~y~%d score~w~)~n~~g~Gracz: ~y~%s~n~~r~Nadajacy: ~y~%s~n~~p~Powod: ~y~%s", time, nick(targetid), nick(adminid), reason);
		}
	}
	SetInterwencjaTD(temp_string);
	TextDrawShowForAll(interwencja_td);
	return 1;
}
/*
stock InterwencjaTD(adminid, targetid, time, kara[], reason[])
{
	serwer[interwencja_time] = gettime()+15;
	format(temp_string, 512, "~p~%s~b~~w~(~y~%d~w~)~n~~g~Gracz: ~y~%s~n~~r~Nadajacy: ~y~%s~n~~p~Powod: ~y~%s", nick(targetid), nick(adminid), reason);
	SetInterwencjaTD(temp_string);
	TextDrawShowForAll(interwencja_td);
	return 1;
}*/

stock Hide_InterwencjaTD()
{
	if(serwer[interwencja_time] > gettime()) return 1;
	SetInterwencjaTD("_");
	TextDrawHideForAll(interwencja_td);
	return 1;
}

stock IsVehicleTrailer(model)
{
	switch(model)
	{
		case 435,450,584,591: return 1;
	}
	return 0;
}

stock TrailerCanTransportGood(model, good_type)
{
	switch(good_type)
	{
		case 0: 
		{
			if(model == 591 || model == 435) return 1;
		}
		case 1:
		{
			if(model == 450) return 1;
		}
		case 2:
		{
			if(model == 584) return 1;
		}
	}
	return 0;
}

stock IsVehicleBike(model)
{
	switch(model)
	{
		case 448,461,462,463,468,471,481,509,510,521,522,523,581,586: return 1;
	}
	return 0;
}

stock IsVehicleHelicopter(model)
{
	switch(model)
	{
		case 417, 425, 447, 469, 487, 488, 497, 548, 563: return 1;
	}
	return 0;
}

stock SpecialVehicle(vehicleid)
{
	new model = GetVehicleModel(vehicleid);
	for(new v; v < MAX_CARSPEC; v++)
	{
		if(pojazd_spec[v][vspec_model] == model) return 0;
	}
	return 1;
}

stock IsVehicleTruck(model)
{
	switch(model)
	{
		case 403,514,515: return 1;//trucki z naczepami
	}
	////trucki bez naczep
	if(model == 573) return 2;
	if(model == 455) return 2;
	if(model == 456) return 2;
	if(model == 578) return 2;
	if(model == 413) return 2;
	if(model == 414) return 2;
	if(model == 440) return 2;
	if(model == 443) return 2;
	if(model == 482) return 2;
	if(model == 498) return 2;
	if(model == 499) return 2;
	if(model == 524) return 2;
	if(model == 459) return 2;
	if(model == 428) return 2;
	return 0;
}

stock LastTextOtherCol(txt[], col)
{
	new wynik[144];
	format(wynik, 144, "%c{%06x}%s", txt[0], col >>> 8, txt[1]);
	return wynik;
}
/*
stock str_replace(sSearch[], sReplace[], const sSubject[], bool:ignorecase)
{
	new
		iLengthTarget = strlen(sSearch),
		iLengthReplace = strlen(sReplace),
		iLengthSource = strlen(sSubject),
		iItterations = (iLengthSource - iLengthTarget) + 1;

	new
		sTemp[256],
		sReturn[256];

	strcat(sReturn, sSubject, 256);
	new iCount = 0;

	for(new iIndex; iIndex < iItterations; ++iIndex)
	{
		strmid(sTemp, sReturn, iIndex, (iIndex + iLengthTarget), (iLengthTarget + 1));

		if(!strcmp(sTemp, sSearch, ignorecase))
		{
			strdel(sReturn, iIndex, (iIndex + iLengthTarget));
			strins(sReturn, sReplace, iIndex, iLengthReplace);

			iIndex += iLengthTarget;
			iCount++;
		}
	}

	return sReturn;
}
*/
/*
stock str_replace(search[], replace[], source[])
{
	new newdata[256];
	new newlen;
	for (new i; i < strlen(source); i++)
	{
		if (strlen(search) > 1 && i != (strlen(source) - 1))
		{
			new matched = 1;
			new start = i;
			for (new s=0; s < strlen(search) && matched == 1; s++)
			{
				if (source[i] != search[s] && s == 0)
				{
					newdata[newlen] = source[i];
					matched = 0;
				} 
				else
				{
					if (source[i] == search[s])
					{
						i++;
					} else
					{
						matched = 0;
					}
				}
			}
			if (matched == 0)
			{
				while (start <= i)
				{
					newdata[newlen] = source[start];
					newlen++;
					start++;
				}
			}
			else
			{
				for (new r; r < strlen(replace); r++)
				{
					newdata[newlen] = replace[r];
					newlen++;
				}
				i = (start + (strlen(search) - 1));
			}
		}
		else
		{
			if (strlen(search) == 1 && source[i] == search[0])
			{
				for (new r; r < strlen(replace); r++)
				{
					newdata[newlen] = replace[r];
					newlen++;
				}
			}
			else
			{
				newdata[newlen] = source[i];
				newlen++;
			}
		}
	}
	newdata[newlen] = EOS;
	return newdata;
}*/

stock SetMoney(playerid, value)
{
	gracz[playerid][kasa] = value;
	if(gracz[playerid][kasa] > 99999999) gracz[playerid][kasa] = 99999999;
	if(gracz[playerid][kasa] < 0) gracz[playerid][kasa] = 0;
	HUD_UpdateKASA(playerid);
	mq_format("UPDATE `Konta` SET `kasa`='%d' WHERE `id`='%d';", gracz[playerid][kasa], gracz[playerid][UID]);
	mq_send("QUpdateKasa");
	printf("[MONEY] SETMONEY %s(uid: %d) VALUE %d BILANS %d", nick(playerid), gracz[playerid][UID], value, gracz[playerid][kasa]);
	return 1;
}

stock GiveMoney(playerid, value)
{
	gracz[playerid][kasa] += value;
	if(gracz[playerid][kasa] > 99999999) gracz[playerid][kasa] = 99999999;
	HUD_UpdateKASA(playerid);
	mq_format("UPDATE `Konta` SET `kasa`='%d' WHERE `id`='%d';", gracz[playerid][kasa], gracz[playerid][UID]);
	mq_send("QUpdateKasa");
	printf("[MONEY] GIVE %s(uid: %d) VALUE %d BILANS %d", nick(playerid), gracz[playerid][UID], value, gracz[playerid][kasa]);
	mq_format("INSERT INTO `LogCash` (`do`, `sum`) VALUES ('%d', '%d');", gracz[playerid][UID], value);
	mq_send("QGiveMoneyLog");
	return 1;
}

stock TakeMoney(playerid, value)
{
	//if(value > gracz[playerid][kasa]) return 0;
	gracz[playerid][kasa] -= value;
	if(gracz[playerid][kasa] < 0) gracz[playerid][kasa] = 0;//pozwala na minus
	HUD_UpdateKASA(playerid);
	mq_format("UPDATE `Konta` SET `kasa`='%d' WHERE `id`='%d';", gracz[playerid][kasa], gracz[playerid][UID]);
	mq_send("QUpdateKasa");
	printf("[MONEY] TAKE %s(uid: %d) VALUE %d BILANS %d", nick(playerid), gracz[playerid][UID], value, gracz[playerid][kasa]);
	mq_format("INSERT INTO `LogCash` (`od`, `sum`) VALUES ('%d', '%d');", gracz[playerid][UID], value);
	mq_send("QTakeMoneyLog");
	return 1;
}

stock Money(playerid)
{
	return gracz[playerid][kasa];
}

stock GiveScore(playerid, value)
{
	gracz[playerid][ps_score] = gracz[playerid][ps_score]+value;
	SetPlayerScore(playerid, gracz[playerid][ps_score]);
	mq_format("UPDATE `Konta` SET `score`='%d' WHERE `id`='%d';", gracz[playerid][ps_score], gracz[playerid][UID]);
	mq_send("QUpdateScore");
	return 1;
}

stock SetScore(playerid, value)
{
	if(value < 0) value = 0;
	gracz[playerid][ps_score] = value;
	SetPlayerScore(playerid, gracz[playerid][ps_score]);
	mq_format("UPDATE `Konta` SET `score`='%d' WHERE `id`='%d';", gracz[playerid][ps_score], gracz[playerid][UID]);
	mq_send("QUpdateScore");
	return 1;
}


stock TakeScore(playerid, value)
{
	if(value < 0) value = 0;
	gracz[playerid][ps_score] = gracz[playerid][ps_score]-value;
	SetPlayerScore(playerid, gracz[playerid][ps_score]);
	mq_format("UPDATE `Konta` SET `score`='%d' WHERE `id`='%d';", gracz[playerid][ps_score], gracz[playerid][UID]);
	mq_send("QUpdateScore");
	return 1;
}

stock GiveKurs(playerid, value)
{
	gracz[playerid][kursy] += value;
	HUD_UpdateKursy(playerid);
	mq_format("UPDATE `Konta` SET `kursy`='%d' WHERE `id`='%d';", gracz[playerid][kursy], gracz[playerid][UID]);
	mq_send("QUpdateKursy");
	return 1;
}

stock GetWeekDay(day=0, month=0, year=0)
{
	if (!day) getdate(year, month, day);
	new weekday_str[32], j, e;
	if (month <= 2)
	{
		month += 12;
		--year;
	}
	j = year % 100;
	e = year / 100;
	switch ((day + (month+1)*26/10 + j + j/4 + e/4 - 2*e) % 7)
	{
		case 0: weekday_str = "Sobota";
		case 1: weekday_str = "Niedziela";
		case 2: weekday_str = "Poniedzialek";
		case 3: weekday_str = "Wtorek";
		case 4: weekday_str = "Sroda";
		case 5: weekday_str = "Czwartek";
		case 6: weekday_str = "Piatek";
	}
	return weekday_str;
}

stock GetMonthName(month)
{
	new monthname[16];
	switch(month)
	{
		case 1: monthname = "Styczen";
		case 2: monthname = "Luty";
		case 3: monthname = "Marzec";
		case 4: monthname = "Kwiecien";
		case 5: monthname = "Maj";
		case 6: monthname = "Czerwiec";
		case 7: monthname = "Lipiec";
		case 8: monthname = "Sierpien";
		case 9: monthname = "Wrzesien";
		case 10: monthname = "Pazdziernik";
		case 11: monthname = "Listopad";
		case 12: monthname = "Grudzien";
		default: monthname = "Not found";
	}
	return monthname;
}

stock GetMonthNameA(month)
{
	new monthname[16];
	switch(month)
	{
		case 1: monthname = "stycznia";
		case 2: monthname = "lutego";
		case 3: monthname = "marca";
		case 4: monthname = "kwietnia";
		case 5: monthname = "maja";
		case 6: monthname = "czerwca";
		case 7: monthname = "lipca";
		case 8: monthname = "sierpnia";
		case 9: monthname = "wrzesnia";
		case 10: monthname = "pazdziernika";
		case 11: monthname = "listopada";
		case 12: monthname = "grudnia";
		default: monthname = "Not found";
	}
	return monthname;
}

stock PlayerIsOnline(uid)
{
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][UID] == uid && gracz[p][loggedin]) return 1;
	}
	return 0;
}


stock Float:PointAngle(playerid, Float:xa, Float:ya, Float:xb, Float:yb)
{
	new Float:carangle;
	new Float:xc, Float:yc;
	new Float:angle;
	xc = floatabs(floatsub(xa,xb));
	yc = floatabs(floatsub(ya,yb));
	if (yc == 0.0 || xc == 0.0)
	{
		if(yc == 0 && xc > 0) angle = 0.0;
		else if(yc == 0 && xc < 0) angle = 180.0;
		else if(yc > 0 && xc == 0) angle = 90.0;
		else if(yc < 0 && xc == 0) angle = 270.0;
		else if(yc == 0 && xc == 0) angle = 0.0;
	}
	else
	{
		angle = atan(xc/yc);
		if(xb > xa && yb <= ya) angle += 90.0;
		else if(xb <= xa && yb < ya) angle = floatsub(90.0, angle);
		else if(xb < xa && yb >= ya) angle -= 90.0;
		else if(xb >= xa && yb > ya) angle = floatsub(270.0, angle);
	}
	GetVehicleZAngle(GetPlayerVehicleID(playerid), carangle);
	return floatadd(angle, -carangle);
}

stock Float:AngleBetweenPoints(Float:X, Float:Y, Float:PointX, Float:PointY)
{
        new Float:fAngle;
        if(X > PointX && Y > PointY)
                fAngle = floatabs(atan2(floatsub(PointX, X), floatsub(PointY, Y)));
        if(X > PointX && Y <= PointY)
                fAngle = floatadd(floatabs(atan2(floatsub(Y, PointY), floatsub(PointX, X))), 270.0);
        if(X <= PointX && Y > PointY)
                fAngle = floatadd(floatabs(atan2(floatsub(PointY, Y), floatsub(X, PointX))), 90.0);
        if(X <= PointX && Y <= PointY)
                fAngle = floatadd(floatabs(atan2(floatsub(X, PointX), floatsub(Y, PointY))), 180.0);
        return fAngle >= 360.0 ? floatsub(fAngle, 360.0) : fAngle;
}

stock VehicleCapacity(model)//pojemność pojazdu w KG
{
	switch(model)
	{
		case 413: return 500;//pony
		case 414: return 700;//mule
		case 428: return 1000;//securicar
		case 435: return 25000;//naczepa duża
		case 440: return 600;//rumpo
		case 443: return 10000;//packer
		case 450: return 34000;//żwirówka
		case 455: return 8000;//flatbed
		case 456: return 1300;//yankee
		case 459: return 600;//topfun van
		case 408: return 1000;//smieciarka
		case 482: return 600;//burrito
		case 498: return 700;//boxville
		case 499: return 550;//benson
		case 524: return 5000;//cement truck
		case 573: return 1000;//smieciarka
		case 578: return 10000;//packer
		case 584: return 33500;//cysterna
		case 591: return 15000;//naczepa mała
	}
	return 0;
}

stock IsSeatTaken(vehicleid, seatid)
{
	for(new i = PlayerPoolSize(); i != -1; i--)
	{
		if(GetPlayerVehicleID(i) == vehicleid && GetPlayerVehicleSeat(i) == seatid) return 1;
	}
	return 0;
}

stock IsSeatTakenFCNPC(vehicleid, seatid)
{
	for(new i = MAX_PLAYERS; i != -1; i--)
	{
		if(IsPlayerNPC(i))
		{
			if(FCNPC_GetVehicleID(i) == vehicleid && FCNPC_GetVehicleSeat(i) == seatid) return 1;
		}
		else
		{
			if(GetPlayerVehicleID(i) == vehicleid && GetPlayerVehicleSeat(i) == seatid) return 1;
		}
		
	}
	return 0;
}

new MaxSeats[212] = {
4,2,2,2,4,4,1,2,2,4,2,2,2,4,2,2,4,2,4,2,4,4,2,2,2,1,4,4,4,2,1,9,1,2,2,1,2,9,4,2,
4,1,2,2,2,4,1,2,1,6,1,2,1,1,1,2,2,2,4,4,2,2,2,2,2,2,4,4,2,2,4,2,1,1,2,2,1,2,2,4,
2,1,4,3,1,1,1,4,2,2,4,2,4,1,2,2,2,4,4,2,2,2,2,2,2,2,2,4,2,1,1,2,1,1,2,2,4,2,2,1,
1,2,2,2,2,2,2,2,2,4,1,1,1,2,2,2,2,0,0,1,4,2,2,2,2,2,4,4,2,2,4,4,2,1,2,2,2,2,2,2,
4,4,2,2,1,2,4,4,1,0,0,1,1,2,1,2,2,2,2,4,4,2,4,1,1,4,2,2,2,2,6,1,2,2,2,1,4,4,4,2,
2,2,2,2,4,2,1,1,1,4,1,1
};

stock GetMaxSeats(vehicleid)
{
	return MaxSeats[(GetVehicleModel(vehicleid) - 400)];
}

stock IsVehicleSuperCar(model)
{
	switch(model)
	{
		case 402: return 1;//Buffalo
		case 411: return 1;//Infernus
		case 415: return 1;//Cheetah
		case 429: return 1;//Banshee
		case 434: return 1;//Hotknife
		case 451: return 1;//Turismo
		case 475: return 1;//Sabre
		case 477: return 1;//ZR-350
		case 506: return 1;//Super GT
		case 521: return 1;//FCR-900
		case 522: return 1;//NRG-500
		case 535: return 1;//Slamvan
		case 541: return 1;//Bullet
		case 558: return 1;//Uranus
		case 559: return 1;//Jester
		case 560: return 1;//Sultan
		case 562: return 1;//Elegy
		case 565: return 1;//Flash
		case 579: return 1;//Huntley
		case 587: return 1;//Euros
		case 603: return 1;//Phoenix
	}
	return 0;
}

stock PlayerUIDToPlayerID(uid)
{
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][UID] == uid && gracz[p][loggedin]) return p;
	}
	return -1;
}

stock bool:TruckerWhileOrderCheck(playerid)
{
	//-------------------------------------
	new bool:whileorder = false;
	for(new v = GetVehiclePoolSize(); v != -1; v--)//sprawdzanie czy gracz ma zlecenie w jakimś vanie
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
	if(gracz[playerid][gfv_waitforpickup] != 0) whileorder = true;
	//------------------------------------
	return whileorder;
}

stock Float:DistanceCameraTargetToLocation(Float:CamX, Float:CamY, Float:CamZ, Float:ObjX, Float:ObjY, Float:ObjZ, Float:FrX, Float:FrY, Float:FrZ)
{
	new Float:TGTDistance;

	// get distance from camera to target
	TGTDistance = floatsqroot((CamX - ObjX) * (CamX - ObjX) + (CamY - ObjY) * (CamY - ObjY) + (CamZ - ObjZ) * (CamZ - ObjZ));

	new Float:tmpX, Float:tmpY, Float:tmpZ;

	tmpX = FrX * TGTDistance + CamX;
	tmpY = FrY * TGTDistance + CamY;
	tmpZ = FrZ * TGTDistance + CamZ;

	return floatsqroot((tmpX - ObjX) * (tmpX - ObjX) + (tmpY - ObjY) * (tmpY - ObjY) + (tmpZ - ObjZ) * (tmpZ - ObjZ));
}

stock IsPlayerAimingAt(playerid, Float:x, Float:y, Float:z, Float:radius)
{
	new Float:cx,Float:cy,Float:cz,Float:fx,Float:fy,Float:fz;
	GetPlayerCameraPos(playerid, cx, cy, cz);
	GetPlayerCameraFrontVector(playerid, fx, fy, fz);
	return (radius >= DistanceCameraTargetToLocation(cx, cy, cz, x, y, z, fx, fy, fz));
}

stock ClearChatAll()
{
	for(new c; c < 100; c++)
	{
		SendClientMessageToAll(-1, " ");
	}
	return 1;
}

stock ClearChat(playerid)
{
	for(new c; c < 100; c++)
	{
		SendClientMessage(playerid, -1, " ");
	}
	return 1;
}

stock FloatIsNaN(Float:number)
{
	return (number != number);
}

stock HL_GetZoneName(Float:hlx, Float:hly)
{
	new hlzonename[64];
	format(hlzonename, 64, "Nieznane");
	if(GetDistanceBetweenPoints(hlx, hly, 14.0982, 654.0963,4539.2549,14.0982) < 300.0) format(hlzonename, 64, "North Hills Village");
	else if(GetDistanceBetweenPoints(hlx, hly, 71.0026, 2610.7153,4421.8804,71.0026) < 300.0) format(hlzonename, 64, "Icytown");
	else if(GetDistanceBetweenPoints(hlx, hly, 4.8948, -4107.2993,448.8879,4.8948) < 300.0) format(hlzonename, 64, "SF Island Port");
	else if(GetDistanceBetweenPoints(hlx, hly, 27.3803,6012.1958,2021.7134,27.3803) < 450.0) format(hlzonename, 64, "Rockvale");
	else if(GetDistanceBetweenPoints(hlx, hly, -0.5314, 4667.7598,1009.9972,-0.5314) < 450.0) format(hlzonename, 64, "Denver");
	else if(GetDistanceBetweenPoints(hlx, hly, 5.6126,-1768.6942,-7216.3350, 5.6126) < 500.0) format(hlzonename, 64, "Whales Factory");
	else if(GetDistanceBetweenPoints(hlx, hly, 5.1967,-735.3051,-5458.1108, 5.1967) < 500.0) format(hlzonename, 64, "Villegreen");
	else if(GetDistanceBetweenPoints(hlx, hly, 53.3042, -4226.3594,-10545.1230,53.3042) < 400.0) format(hlzonename, 64, "Oil Province");
	else if(IsPointInDynamicArea(weatherarea_PencilFactory, hlx, hly, 0.0)) format(hlzonename, 64, "Pencil Factory");
	else if(IsPointInDynamicArea(pol_deerfield, hlx, hly, 0.0)) format(hlzonename, 64, "Deerfield");
	else if(GetDistanceBetweenPoints(hlx, hly, 50.9907, 4378.7944,3893.6013,50.9907) < 350.0) format(hlzonename, 64, "Norwood");
	else if(GetDistanceBetweenPoints(hlx, hly, 50.9907, 5209.7905,4688.1519,50.9907) < 350.0) format(hlzonename, 64, "Leesville");
	else if(GetDistanceBetweenPoints(hlx, hly, 50.9735, 5511.4307,6362.0923,50.9735) < 350.0) format(hlzonename, 64, "Reedley City");
	else if(GetDistanceBetweenPoints(hlx, hly, 110.5701, 7862.9873,5490.0864,110.5701) < 350.0) format(hlzonename, 64, "Skyland");
	else if(GetDistanceBetweenPoints(hlx, hly, 5.8848, 5240.8682,6881.0161,5.8848) < 350.0) format(hlzonename, 64, "Port Langlois");
	else if(GetDistanceBetweenPoints(hlx, hly, 78.0289, 4491.5933,7449.2539,78.0289) < 350.0) format(hlzonename, 64, "ECC Factory");
	return hlzonename;
}


stock AddPublicRunQueue(call[])
{
	SetTimer(call, MRandRange(6, 11), false);
	//CallLocalFunction(call, "");//debug
	return 1;
}

stock AddPlayerRunQueue(call[], playerid)
{
	SetTimerEx(call, MRandRange(6, 11), false, "d", playerid);
	return 1;
}

stock IsVehicleStreamedInAnyone(vehicleid)
{
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(!IsPlayerConnected(p)) continue;
		if(!gracz[p][loggedin]) continue;
		if(IsVehicleStreamedIn(vehicleid, p))
		{
			return 1;
		}
	}
	return 0;
}

stock IsAnyVehicleInRange(Float:vrange, Float:vx, Float:vy, Float:vz)
{
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		if(pojazd[v][v_model] == 0) continue;
		if(GetVehicleDistanceFromPoint(v, vx, vy, vz) < vrange)
		{
			return v;
		}
	}
	return -1;
}

//Panels
stock decode_panels(panels, &front_left_panel, &front_right_panel, &rear_left_panel, &rear_right_panel, &windshield, &front_bumper, &rear_bumper)
{
    front_left_panel = panels & 15;
    front_right_panel = panels >> 4 & 15;
    rear_left_panel = panels >> 8 & 15;
    rear_right_panel = panels >> 12 & 15;
    windshield = panels >> 16 & 15;
    front_bumper = panels >> 20 & 15;
    rear_bumper = panels >> 24 & 15;
}
stock encode_panels(front_left_panel, front_right_panel, rear_left_panel, rear_right_panel, windshield, front_bumper, rear_bumper)
{
    return front_left_panel | (front_right_panel << 4) | (rear_left_panel << 8) | (rear_right_panel << 12) | (windshield << 16) | (front_bumper << 20) | (rear_bumper << 24);
}
 
//Doors
stock decode_doors(doors, &bonnet, &boot, &driver_door, &passenger_door)
{
    bonnet = doors & 7;
    boot = doors >> 8 & 7;
    driver_door = doors >> 16 & 7;
    passenger_door = doors >> 24 & 7;
}
stock encode_doors(bonnet, boot, driver_door, passenger_door)
{
    return bonnet | (boot << 8) | (driver_door << 16) | (passenger_door << 24);
}
 
//Lights
stock decode_lights(lights, &front_left_light, &front_right_light, &back_lights)
{
    front_left_light = lights & 1;
    front_right_light = lights >> 2 & 1;
    back_lights = lights >> 6 & 1;
}
stock encode_lights(front_left_light, front_right_light, back_lights)
{
    return front_left_light | (front_right_light << 2) | (back_lights << 6);
}
 
//Tires
stock decode_tires(tires, &rear_right_tire, &front_right_tire, &rear_left_tire, &front_left_tire)
{
    rear_right_tire = tires & 1;
    front_right_tire = tires >> 1 & 1;
    rear_left_tire = tires >> 2 & 1;
    front_left_tire = tires >> 3 & 1;
}
stock encode_tires(rear_right_tire, front_right_tire, rear_left_tire, front_left_tire)
{
	return rear_right_tire | (front_right_tire << 1) | (rear_left_tire << 2) | (front_left_tire << 3);
}

stock GetPlayerIDFromNick(nickk[])
{
	for(new i=GetPlayerPoolSize(); i!=-1; i--)
	{
		if(IsPlayerConnected(i))
		{
			if(!strcmp(nick(i),nickk))
			{
				return i;
			}
		}
		continue;
	}
	return INVALID_PLAYER_ID;
}

stock bool:Find(const search[], const find[],bool:ignorecase=false)
{
	if(strfind(search, find, ignorecase) != -1) return true;
	return false;
}

stock isnumeric(const string[])
{
	for (new i = 0, j = strlen(string); i < j; i++)
	{
		if (string[i] > '9' || string[i] < '0') return 0;
	}
	return 1;
}

stock StrSecounds(secounds,str_int_color[]="{ffffff}",str_str_color[]="{c0c0c0}")
{
	new zwr_sec[1300];
	new Hours, Minutes, Secounds, Days;
	Secounds=secounds;
	if(Secounds>=60)
	{
		Minutes=Secounds/60;
		Secounds-=(60*Minutes);
	}
	if(Minutes>=60)
	{
		Hours=Minutes/60;
		Minutes-=(60*Hours);
	}
	if(Hours>=24)
	{
		Days=Hours/24;
		Hours-=(24*Days);
	}
	if(Days>0)
	{
		if(Days==1) format(zwr_sec,300,"%s%s%d %sdzien ",zwr_sec,str_int_color,Days,str_str_color);
		else format(zwr_sec,300,"%s%s%d %sdni ",zwr_sec,str_int_color,Days,str_str_color);
	}
	if(Hours>0)
	{
		if(Hours==1) format(zwr_sec,300,"%s%s%d %sgodzina(e) ",zwr_sec,str_int_color,Hours,str_str_color);
		if(Hours>1&&Hours<=4) format(zwr_sec,300,"%s%s%d %sgodziny ",zwr_sec,str_int_color,Hours,str_str_color);
		if(Hours>=5) format(zwr_sec,300,"%s%s%d %sgodzin ",zwr_sec,str_int_color,Hours,str_str_color);
	}
	if(Minutes>0)
	{
		if(Minutes==1) format(zwr_sec,300,"%s%s%d %sminuta(e) ",zwr_sec,str_int_color,Minutes,str_str_color);
		if(Minutes>1&&Minutes<=4) format(zwr_sec,300,"%s%s%d %sminuty ",zwr_sec,str_int_color,Minutes,str_str_color);
		if(Minutes>=5) format(zwr_sec,300,"%s%s%d %sminut ",zwr_sec,str_int_color,Minutes,str_str_color);
	}
	if(Secounds>0)
	{
		if(Secounds==1) format(zwr_sec,300,"%s%s%d %ssekunda(e)",zwr_sec,str_int_color,Secounds,str_str_color);
		if(Secounds>1&&Secounds<=4) format(zwr_sec,300,"%s%s%d %ssekundy",zwr_sec,str_int_color,Secounds,str_str_color);
		if(Secounds>=5) format(zwr_sec,300,"%s%s%d %ssekund",zwr_sec,str_int_color,Secounds,str_str_color);
	}
	if(Hours==0&&Minutes==0&&Secounds==0&&Days==0)
	{
		format(zwr_sec,300,"%s%s0 %ssekund",zwr_sec,str_int_color,str_str_color);
	}
	return zwr_sec;
}

stock bool:IsWeaponIsValid(weaponid)
{
	switch(weaponid)
	{
		case 0..18,22..46: return true;
	}
	return false;
}

stock WeaponName(weaponid)
{
	new zwrstr[50];
	switch(weaponid)
	{
		case 0: format(zwrstr,50,"Pięść");
		case 1: format(zwrstr,50,"Kastet");
		case 2: format(zwrstr,50,"Kij golfowy");
		case 3: format(zwrstr,50,"Pałka policyjna");
		case 4: format(zwrstr,50,"Nóż");
		case 5: format(zwrstr,50,"Kij Baseball'owy");
		case 6: format(zwrstr,50,"Łopata/Szpadel");
		case 7: format(zwrstr,50,"Kij Billard'owy");
		case 8: format(zwrstr,50,"Katana");
		case 9: format(zwrstr,50,"Piła mechaniczna");
		case 10: format(zwrstr,50,"Różowe Dildo");
		case 11: format(zwrstr,50,"Dildo");
		case 12: format(zwrstr,50,"Wibrator");
		case 13: format(zwrstr,50,"Srebrny wibrator");
		case 14: format(zwrstr,50,"Kwiaty");
		case 15: format(zwrstr,50,"Laska");
		case 16: format(zwrstr,50,"Granat");
		case 17: format(zwrstr,50,"Gaz łzawiący");
		case 18: format(zwrstr,50,"Koktajl Mołotowa");
		case 22: format(zwrstr,50,"Colt 45");
		case 23: format(zwrstr,50,"Colt 45 z tłumikiem");
		case 24: format(zwrstr,50,"Desert Eagle");
		case 25: format(zwrstr,50,"Shotgun");
		case 26: format(zwrstr,50,"Sawn-off Shotgun");
		case 27: format(zwrstr,50,"Combat Shotgun");
		case 28: format(zwrstr,50,"UZI");
		case 29: format(zwrstr,50,"MP5");
		case 30: format(zwrstr,50,"AK47");
		case 31: format(zwrstr,50,"M4");
		case 32: format(zwrstr,50,"TEC9");
		case 33: format(zwrstr,50,"Strzelba");
		case 34: format(zwrstr,50,"Karabin snajperski");
		case 35: format(zwrstr,50,"Wyrzutnia rakiet");
		case 36: format(zwrstr,50,"Wyrzutnia rakiet (z automatycznym namierzaniem)");
		case 37: format(zwrstr,50,"Miotacz ognia");
		case 38: format(zwrstr,50,"Minigun");
		case 39: format(zwrstr,50,"Przyczepiany materiał wybuchowy");
		case 40: format(zwrstr,50,"Detonator (Przyczepianego materiału wybuchowego)");
		case 41: format(zwrstr,50,"Spray");
		case 42: format(zwrstr,50,"Gaśnica");
		case 43: format(zwrstr,50,"Kamera");
		case 44: format(zwrstr,50,"Noktowizor");
		case 45: format(zwrstr,50,"Termowizor");
		case 46: format(zwrstr,50,"Spadochron");
	}
	return zwrstr;
}

stock WeaponNameShortTD(weaponid)
{
	new zwrstr[50];
	switch(weaponid)
	{
		case 0: format(zwrstr,50,"Piesc");
        		case 1: format(zwrstr,50,"Kastet");
        		case 2: format(zwrstr,50,"Kij");
        		case 3: format(zwrstr,50,"Baton");
        		case 4: format(zwrstr,50,"Noz");
        		case 5: format(zwrstr,50,"Baseball");
        		case 6: format(zwrstr,50,"Szpadel");
        		case 7: format(zwrstr,50,"Kij");
        		case 8: format(zwrstr,50,"Katana");
        		case 9: format(zwrstr,50,"Stihl");
        		case 10: format(zwrstr,50,"Dilo");
        		case 11: format(zwrstr,50,"Dildo");
        		case 12: format(zwrstr,50,"Wibrator");
        		case 13: format(zwrstr,50,"Wibrator");
        		case 14: format(zwrstr,50,"Kwiaty");
        		case 15: format(zwrstr,50,"Laska");
        		case 16: format(zwrstr,50,"Granat");
        		case 17: format(zwrstr,50,"Gaz");
        		case 18: format(zwrstr,50,"Molotov");
        		case 22: format(zwrstr,50,"Colt 45");
        		case 23: format(zwrstr,50,"Colt-S");
        		case 24: format(zwrstr,50,"Deagle");
        		case 25: format(zwrstr,50,"Shotgun");
        		case 26: format(zwrstr,50,"Sawn-OFF");
        		case 27: format(zwrstr,50,"Combat-S");
        		case 28: format(zwrstr,50,"UZI");
        		case 29: format(zwrstr,50,"MP5");
        		case 30: format(zwrstr,50,"AK47");
        		case 31: format(zwrstr,50,"M4");
        		case 32: format(zwrstr,50,"TEC9");
        		case 33: format(zwrstr,50,"Strzelba");
        		case 34: format(zwrstr,50,"Sniperka");
        		case 35: format(zwrstr,50,"RPG");
        		case 36: format(zwrstr,50,"AUTO-RPG");
        		case 37: format(zwrstr,50,"Miotacz");
        		case 38: format(zwrstr,50,"Minigun");
        		case 39: format(zwrstr,50,"Bomba");
        		case 40: format(zwrstr,50,"Detonator");
        		case 41: format(zwrstr,50,"Spray");
        		case 42: format(zwrstr,50,"Gasnica");
        		case 43: format(zwrstr,50,"Kamera");
        		case 44: format(zwrstr,50,"Noktowizor");
        		case 45: format(zwrstr,50,"Termowizor");
        		case 46: format(zwrstr,50,"Spadochron");
	}
	return zwrstr;
}

//MapAndreas include EX
stock Float: GetPointZPos(const Float: fX, const Float: fY, &Float: fZ = 0.0) {
        if(!((-3000.0 < fX < 3000.0) && (-3000.0 < fY < 3000.0))) {
                return 0.0;
        }
        static
                File: s_hMap
        ;
        if(!s_hMap) {
                s_hMap = fopen("SAfull.hmap", io_read);
               
                if(!s_hMap) {
                        return 0.0;
                }
        }
        new
                afZ[1]
        ;
        fseek(s_hMap, ((6000 * (-floatround(fY, floatround_tozero) + 3000) + (floatround(fX, floatround_tozero) + 3000)) << 1));
        fblockread(s_hMap, afZ);
       
        return (fZ = ((afZ[0] >>> 16) * 0.01));
}
//end
stock IsPlayerFacingPlayer(playerid, targetid, Float:dOffset)
{

	new
	Float:pX,
	Float:pY,
	Float:pZ,
	Float:pA,
	Float:X,
	Float:Y,
	Float:Z,
	Float:ang;

	if(!IsPlayerConnected(playerid) || !IsPlayerConnected(targetid)) return 0;

	GetPlayerPos(targetid, pX, pY, pZ);
	GetPlayerPos(playerid, X, Y, Z);
	GetPlayerFacingAngle(playerid, pA);

	if( Y > pY ) ang = (-acos((X - pX) / floatsqroot((X - pX)*(X - pX) + (Y - pY)*(Y - pY))) - 90.0);
	else if( Y < pY && X < pX ) ang = (acos((X - pX) / floatsqroot((X - pX)*(X - pX) + (Y - pY)*(Y - pY))) - 450.0);
	else if( Y < pY ) ang = (acos((X - pX) / floatsqroot((X - pX)*(X - pX) + (Y - pY)*(Y - pY))) - 90.0);

	if(AngleInRangeOfAngle(-ang, pA, dOffset)) return true;

	return false;

}

stock IsPlayerFacingPoint(playerid, Float:dOffset, Float:pX, Float:pY, Float:pZ)
{
	#pragma unused pZ
	new
	Float:X,
	Float:Y,
	Float:Z,
	Float:pA,
	Float:ang;

	if(!IsPlayerConnected(playerid)) return 0;

	GetPlayerPos(playerid, X, Y, Z);
	GetPlayerFacingAngle(playerid, pA);

	if( Y > pY ) ang = (-acos((X - pX) / floatsqroot((X - pX)*(X - pX) + (Y - pY)*(Y - pY))) - 90.0);
	else if( Y < pY && X < pX ) ang = (acos((X - pX) / floatsqroot((X - pX)*(X - pX) + (Y - pY)*(Y - pY))) - 450.0);
	else if( Y < pY ) ang = (acos((X - pX) / floatsqroot((X - pX)*(X - pX) + (Y - pY)*(Y - pY))) - 90.0);

	if(AngleInRangeOfAngle(-ang, pA, dOffset)) return true;

	return false;

}


stock quickSort(array[], left, right)
{
	new
	tempLeft = left,
	tempRight = right,
	pivot = array[(left + right) / 2],
	tempVar
	;
	while(tempLeft <= tempRight)
	{
		while(array[tempLeft] < pivot) tempLeft++;
		while(array[tempRight] > pivot) tempRight--;
		
		if(tempLeft <= tempRight)
		{
			tempVar = array[tempLeft], array[tempLeft] = array[tempRight], array[tempRight] = tempVar;
			tempLeft++, tempRight--;
		}
	}
	if(left < tempRight) quickSort(array, left, tempRight);
	if(tempLeft < right) quickSort(array, tempLeft, right);
}
/*
new
    array[] = { -541, 54, 689, 12, 3, 0, 3, 55, 66, -541, 5468484, -564, 1554, 1656 }
;
quickSort(array, 0, sizeof(array) - 1);
    
for(new i; i != sizeof(array); ++i)
{
    printf("%d", array[i]);
}
*/

task Float:GetDistanceBetweenPlayers(p1,p2)
{
	new Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2;
	if(!IsPlayerConnected(p1) || !IsPlayerConnected(p2))
	{
		return -1.00;
	}
	GetPlayerPos(p1,x1,y1,z1);
	GetPlayerPos(p2,x2,y2,z2);
	return floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
}

stock GetClosestPlayer(pid)
{
	new Float:dis,Float:dis2,player2;
	player2 = -1;
	dis = 99999.99;
	for(new x = PlayerPoolSize(); x != -1; x--)
	{
		if(IsPlayerConnected(x))
		{
			if(x != pid)
			{
				dis2 = GetDistanceBetweenPlayers(x,pid);
				if(dis2 < dis && dis2 != -1.00)
				{
					dis = dis2;
					player2 = x;
				}
			}
		}
	}
	return player2;
}

stock IsPlayerInRangeOfPlayer(Float:radius,playerid,targetid)
{
	if(IsPlayerConnected(playerid) && IsPlayerConnected(targetid))
	{
		new Float:posx, Float:posy, Float:posz;
		GetPlayerPos(playerid, posx, posy, posz);
		if(IsPlayerInRangeOfPoint(targetid,radius,posx,posy,posz))
		{
			return 1;
		}
	}
	return 0;
}


stock NameValidator(playerid, nickcheck[])
{
	new pname[32];
	format(pname, 32, "%s", nickcheck);
	mysql_escape_string(pname, pname, 32, g_SQL);
	if(strfind(pname,"[",true) != (-1)) return 0;
	else if(strfind(pname,"]",true) != (-1)) return 0;
	else if(strfind(pname,"$",true) != (-1)) return 0;
	else if(strfind(pname,"(",true) != (-1)) return 0;
	else if(strfind(pname,")",true) != (-1)) return 0;
	else if(strfind(pname,"=",true) != (-1)) return 0;
	else if(strfind(pname,"@",true) != (-1)) return 0;
	else if(strfind(pname,"1",true) != (-1)) return 0;
	else if(strfind(pname,"2",true) != (-1)) return 0;
	else if(strfind(pname,"3",true) != (-1)) return 0;
	else if(strfind(pname,"4",true) != (-1)) return 0;
	else if(strfind(pname,"5",true) != (-1)) return 0;
	else if(strfind(pname,"6",true) != (-1)) return 0;
	else if(strfind(pname,"7",true) != (-1)) return 0;
	else if(strfind(pname,"8",true) != (-1)) return 0;
	else if(strfind(pname,"9",true) != (-1)) return 0;
	new maxname = strlen(pname);
	new underline = 0;
	for(new i=0; i<maxname; i++)
	{
		if(pname[i] == '_') underline ++;
	}
	if(underline != 1) return 0;
	pname[0] = toupper(pname[0]);
	for(new x=1; x<maxname; x++)
	{
		if(pname[x] == '_') pname[x+1] = toupper(pname[x+1]);
		else if(pname[x] != '_' && pname[x-1] != '_') pname[x] = tolower(pname[x]);
	}
	format(gracz[playerid][nick_ic], MAX_PLAYER_NAME, "%s", pname);
	return 1;
}

stock GetICName(playerid)
{
	new ICName[MAX_PLAYER_NAME];
	if(IsPlayerConnected(playerid))
	{
		if(strlen(gracz[playerid][nick_ic]) > 2)
		{
			format(ICName, MAX_PLAYER_NAME, "%s", gracz[playerid][nick_ic]);
			for(new i = 0; i < MAX_PLAYER_NAME; i++)
			{
				if(ICName[i] == '_') ICName[i] = ' ';
			}
		}
		else
		{
			format(ICName, MAX_PLAYER_NAME, "%s", nick(playerid));
		}
	}
	else
	{
		ICName = "Brak_Postaci";
	}
	return ICName;
}

stock AddCommasToInt(number, delimiter[2] = ".")
{
	new int_string[10+3+1+1];
	/*
            The maximum value for the Integer: "-2147483647" to "2147483647"
            Consequently, transmit greater than this value as a parameter impossible (only if we make "number" parameter as string)
            Declare 10 cells for the number and 3 cells for the delimiters for the largest possible number and 1 cell
            for minus and 1 and cell for the null-character.
	*/
 
	format(int_string, sizeof(int_string), "%d", number >= 0 ? number : -number); //If the number is positive - we write it in the usual way. Otherwise, convert it to a positive number, adding a minus
 
 
	new value = strlen(int_string); // Write in "i" length of the string with the our number
 
	switch(value)
	{
		case 4..6: // If the number has passed from 4 up to 6 characters, add a delimiter
					strins(int_string, delimiter, value-3,1);
		case 7..9: // From 7 to 9 characters - two delimiters
					strins(int_string, delimiter, value-3,1), 
					strins(int_string, delimiter, value-6,1);
		case 10..12: // From 10 to 12 characters - three delimiters
					strins(int_string, delimiter, value-3,1), 
					strins(int_string, delimiter, value-6,1), 
					strins(int_string, delimiter, value-9,1);
	}	
	if(number < 0) strins(int_string, "-", 0); // If the number is negative, it return him minus
	return int_string;
}

stock GetFightStyleName(playerid)
{
	new wynik[32];
	switch(GetPlayerFightingStyle(playerid))
	{
		case FIGHT_STYLE_BOXING: wynik = "Boxing";
		case FIGHT_STYLE_KUNGFU: wynik = "Kung Fu";
		case FIGHT_STYLE_KNEEHEAD: wynik = "Knee Head";
		case FIGHT_STYLE_GRABKICK: wynik = "Grab Kick";
		case FIGHT_STYLE_ELBOW: wynik = "Elbow";
		default: wynik = "Normalny";

	}
	return wynik;
}