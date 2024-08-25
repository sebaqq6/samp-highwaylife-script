//definicje
#define MAX_EVENT_VEHICLES 100
#define EVENT_LOCAL_RANGE 20.0
#define EVENT_MASTER_PASSWORD "TrudneHaslo" //Hasło do zalogowania się jako event master
#define RGBAToRGB(%0)				(((%0) >>> 8) & 0xFFFFFF)
#define MAX_CASES_OBJECTS 3

#define KOLOR_EVENT 0x00ACC1FF
#define EVENT_MINUTES_TO_CLOSE_WITHOUT_EVENT_MASTER 600 //10 minut w sekundach. WAZNE! PODAWANY TUTAJ CZAS MUSI BYC W SEKUNDACH
#define EVENT_MAX_TIMER_TIME 20 //20 sekund
#define EVENT_MAX_DAILY_CASES 60 //maksymalna liczba dziennych niespodzianek
#define EVENT_MAX_CASES_MONEY 100000 //maksymalna liczba kasy do dodania do niespodzianki
#define EVENT_MAX_CASES_SCORE 100 //maksymalna liczba score do dodania do niespodzianki
//ręczny
#define E_HANDBRAKE_OFF 0
#define E_HANDBRAKE_ON 1
//

new g_szBuffer[10000 char];
#define form(%0) (format(g_szBuffer, sizeof g_szBuffer, %0), g_szBuffer)

//mSelection
#define EV_VEH_SEL_1 MSEL_EVP_0
#define EV_VEH_SEL_0_1 MSEL_EVP_1
#define EV_SELECT_SKIN_ALL MSEL_EVP_2
#define EV_SELECT_SKIN_LOCAL MSEL_EVP_3
#define EV_USERS_SELECT_SKIN MSEL_EVP_4

new EV_CASES_ADD_LISTID = mS_INVALID_LISTID;
new EV_CASES_ADD_IDS = mS_INVALID_LISTID;

new Text:Event_Info;



//stock
stock AddEventLog(tresc[])
{
	printf("[EVENT] %s",tresc);
	return 1;
}
stock GetEventCases()
{
	new ilosc=0;
	for(new i=0; i < EVENT_MAX_CASES; i++)
	{
		if(IsValidDynamicPickup(serwer[event_case][i])) ilosc++;
	}
	return ilosc;
}
stock CreateEventCase(playerid,modelid,i_score,i_kasa,podpowiedz[])
{
	if(GetEventCases()>=EVENT_MAX_CASES) return 0;
	if(serwer[event_cases_daily_count]>=EVENT_MAX_DAILY_CASES) return Error(playerid,form("Osiągnięto już dzienny limit niespodzianek! (%d)",EVENT_MAX_DAILY_CASES));
	new Float:CasePos[3];
	GetPlayerPos(playerid, CasePos[0], CasePos[1], CasePos[2]);
	for(new i=0; i < EVENT_MAX_CASES; i++)
	{
		if(!IsValidDynamicPickup(serwer[event_case][i]))
		{
			new str[100];
			serwer[event_case][i]=CreateDynamicPickup(modelid, 1, CasePos[0], CasePos[1], CasePos[2], GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
			serwer[event_case_money][i]=i_kasa;
			serwer[event_case_score][i]=i_score;
			if(serwer[event_case_score][i]>0&&serwer[event_case_money][i]>0) format(str,100,"{757575}Ilość score: {ffff00}%d\n{757575}Ilość kasy: {ffff00}%d",serwer[event_case_score][i],serwer[event_case_money][i]);
			if(serwer[event_case_score][i]>0&&serwer[event_case_money][i]==0) format(str,100,"{757575}Ilość score: {ffff00}%d",serwer[event_case_score][i]);
			if(serwer[event_case_score][i]==0&&serwer[event_case_money][i]>0) format(str,100,"{757575}Ilość kasy: {ffff00}%d",serwer[event_case_money][i]);
			serwer[event_case_textid][i]=CreateDynamic3DTextLabel(form("{ffffff}[{6666ff}Event{ffffff} - {ff3333}Niespodzianka{ffffff}]\n{696969}Wbiegnij w nią aby otrzymać nagrodę!\n%s\n\n{c0c0c0}UID: %d",str,i), -1, CasePos[0], CasePos[1], CasePos[2], 10.0, .testlos = 1, .worldid = GetPlayerVirtualWorld(playerid), .interiorid = GetPlayerInterior(playerid));
			serwer[event_cases_pos_x][i]=CasePos[0];
			serwer[event_cases_pos_y][i]=CasePos[1];
			serwer[event_cases_pos_z][i]=CasePos[2];
			format(event_cases_podpowiedz[i],124,"%s",podpowiedz);
			SendEventMessageToAll(form("{696969}%s [ID:%d]{c0c0c0} upuścił(a) niespodziankę! Znajdź ją pierwszy/a! Podpowiedź: {ffffff}%s",nick(playerid),playerid,podpowiedz));
			AddEventLog(form("%s [ID:%d] dodal niespodzianke (UID: %d)! ModelID: %d. Nagrody: %d kasy i %d score. Podpowiedz: %s (Koordynaty: %f,%f,%f)",nick(playerid),playerid,i,modelid,i_kasa,i_score,podpowiedz,CasePos[0],CasePos[1],CasePos[2]));
			break;
		}
	}
	serwer[event_cases_daily_count]++;
	new ranmess = random(5);
	if(ranmess==3) SendClientMessageToAll(-1, "{00BA8C}[Bot HL] {999999}Nie wiesz ile pozostało jeszcze niespodzianek? Użyj {ff0000}/niespodzianki{999999}.");
	if(serwer[event_cases_daily_count]>=EVENT_MAX_DAILY_CASES)
	{
		SendEventMessageToAll(form("{696969}%s [ID:%d]{c0c0c0} wykorzystal(a) dzienny limit niespodzianek! (%s)",nick(playerid),playerid,EVENT_MAX_DAILY_CASES));
		AddEventLog(form("%s [ID:%d] wykorzystal/a dzienny limit niespodzianek! (%d)",nick(playerid),playerid,EVENT_MAX_DAILY_CASES));
	}
	return 1;
}
stock DestroyEventCase(playerid,id,type=0)
{
	if(!IsValidDynamicPickup(serwer[event_case][id])) return 0;

	DestroyDynamicPickup(serwer[event_case][id]);
	serwer[event_case][id]=-1;
	DestroyDynamic3DTextLabel(serwer[event_case_textid][id]);
	serwer[event_case_textid][id]=STREAMER_TAG_3D_TEXT_LABEL:-1;
	if(type==0)
	{
		SendEventMessageToAll(form("{696969}%s [ID:%d]{c0c0c0} znalazł(a) niespodziankę! {c0c0c0}({ffffff}%s {c0c0c0}[%d])",nick(playerid),playerid,event_cases_podpowiedz[id],id));
		AddEventLog(form("%s [ID:%d] znalazl(a) niespodzianke (UID:%d)! Nagrody: %d kasy i %d score. Podpowiedz: %d (Koordynaty: %f, %f, %f)",nick(playerid),playerid,id,serwer[event_case_money][id],serwer[event_case_score][id],event_cases_podpowiedz[id],serwer[event_cases_pos_x][id],serwer[event_cases_pos_y][id],serwer[event_cases_pos_z][id]));
	}
	if(type==1)
	{
		SendEventMessageToAll(form("{696969}%s [ID:%d]{c0c0c0} usunął/eła niespodziankę! {c0c0c0}({ffffff}%s {c0c0c0}[%d])",nick(playerid),playerid,event_cases_podpowiedz[id],id));
		AddEventLog(form("%s [ID:%d] usunal/ela niespodzianke (UID:%d)! Nagrody: %d kasy i %d score. Podpowiedz: %d (Koordynaty: %f, %f, %f)",nick(playerid),playerid,id,serwer[event_case_money][id],serwer[event_case_score][id],event_cases_podpowiedz[id],serwer[event_cases_pos_x][id],serwer[event_cases_pos_y][id],serwer[event_cases_pos_z][id]));
	}
	serwer[event_case_money][id]=0;
	serwer[event_case_score][id]=0;
	serwer[event_cases_pos_x][id]=0.0;
	serwer[event_cases_pos_y][id]=0.0;
	serwer[event_cases_pos_z][id]=0.0;
	format(event_cases_podpowiedz[id],124,"");
	return 1;
}
stock bool:TheSame(string1[],strting2[],bool:ignorecase=false)
{
	if(!strcmp(string1,strting2,ignorecase)) return true;
	return false;
}
stock MaxPlayers()
{
	new do_odj=0;
	for(new i=GetMaxPlayers(); i != -1; i--)
	{
		if(IsPlayerNPC(i)) do_odj++;
	}
	return GetMaxPlayers()-do_odj;
}
stock CreateEventVehicle(playerid,mdlid,color1,color2)
{
	if(GetEventVehicles()>=MAX_EVENT_VEHICLES) return Error(playerid,"Osiągnięto już maksymalny limit pojazdów eventowych!");

	new Float:x,Float:y,Float:z,Float:a,Float:z2,str_text[500],veh_id;
	GetVehicleModelInfo(mdlid, VEHICLE_MODEL_INFO_SIZE, x, y, z);
	GetPlayerPos(playerid, x, y, z2);
	GetPlayerFacingAngle(playerid, a);
	veh_id=CreateVehicle(mdlid, x, y, z2+z, a, color1, color2, -1);
	pojazd[veh_id][v_id] = 0;
	pojazd[veh_id][v_model] = mdlid;
	GetVehiclePos(veh_id, pojazd[veh_id][v_X], pojazd[veh_id][v_Y], pojazd[veh_id][v_Z]);
	GetVehicleZAngle(veh_id, pojazd[veh_id][v_R]);
	pojazd[veh_id][v_color][0] = color1;
	pojazd[veh_id][v_color][1] = color2;
	pojazd[veh_id][v_paliwo] = 9999;
	if(pojazd[veh_id][v_paliwo] >= 9999) pojazd[veh_id][v_paliwo] = GetVehicleFuelSize(pojazd[veh_id][v_model]);
	if(pojazd[veh_id][v_paliwo] == 0) pojazd[veh_id][v_paliwo] = 9999;
	pojazd[veh_id][v_owner_type] = VEHICLE_PUBLIC;
	pojazd[veh_id][v_owner] = VO_EVENT;

	pojazd[veh_id][v_event_used]=true;
	pojazd[veh_id][v_event_creator_uid]=gracz[playerid][UID];
	pojazd[veh_id][v_event_godmode]=false;
	pojazd[veh_id][v_event_teamid]=-1;
	pojazd[veh_id][v_event_virtual_world]=GetPlayerVirtualWorld(playerid);
	pojazd[veh_id][v_event_interior]=GetPlayerInterior(playerid);

	format(str_text, 500, "[Pojazd {6666FF}Eventowy{ffffff}]\n{ffff00}%s\n{c0c0c0}ID: %d", VehicleNames[mdlid-400], veh_id);
	pojazd[veh_id][v_text3d] = CreateDynamic3DTextLabel(str_text, -1, 0.0, 0.0, 0.0, 10.0, .attachedvehicle = veh_id, .testlos = 1, .worldid = pojazd[veh_id][v_event_virtual_world], .interiorid = pojazd[veh_id][v_event_interior]);
	Handbrake(veh_id, E_HANDBRAKE_OFF);
	SetVehicleNumberPlate(veh_id, "{6666ff}EVENT");
	format(pojazd[veh_id][v_numberplate], 32, "{6666ff}EVENT");
	SetVehicleToRespawn(veh_id);
	LinkVehicleToInterior(veh_id, pojazd[veh_id][v_event_interior]);
	SetVehicleVirtualWorld(veh_id, pojazd[veh_id][v_event_virtual_world]);
	PutPlayerInVehicle(playerid, veh_id, 0);
	SetVehicleParamsEx(veh_id, 1, 1, 0, 0, 0, 0, 0);
	SetVehicleParamsCarWindows(veh_id, 1, 1, 1, 1);

	AddEventLog(form("%s [ID:%d] stworzyl(a) pojazd eventowy (UID:%d)! ModelID: %d. Kolory: %d i %d. (Koordynaty:%f, %f, %f, %f)",nick(playerid),playerid,veh_id,mdlid,color1,color2,pojazd[veh_id][v_X], pojazd[veh_id][v_Y], pojazd[veh_id][v_Z],pojazd[veh_id][v_R]));
	return 1;
}

stock DestroyEventVehicle(vehicleid)
{
	if(!GetVehicleModel(vehicleid)) return 0;
	if(pojazd[vehicleid][v_event_used]==false) return 0;
	RemoveVehicle(vehicleid);
	AddEventLog(form("Zniszczenie pojazdu eventowego UID: %d",vehicleid));
	return 1;
}

stock SaveEventVehiclePosToRespawn(vehicleid)
{
	new hndbrk = pojazd[vehicleid][v_handbrake];
	new kolr1 = pojazd[vehicleid][v_color][0];
	new kolr2 = pojazd[vehicleid][v_color][1];
	new bool:god = pojazd[vehicleid][v_event_godmode];
	new tmid = pojazd[vehicleid][v_event_teamid];
	new creator = pojazd[vehicleid][v_event_creator_uid];
	new Float:x,Float:y,Float:z,Float:a,str_text[500],veh_id;
	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, a);
	new mdlid = GetVehicleModel(vehicleid);
	DestroyEventVehicle(vehicleid);

	veh_id=CreateVehicle(mdlid, x, y, z, a, kolr1, kolr2, -1);
	pojazd[veh_id][v_id] = 0;
	pojazd[veh_id][v_model] = mdlid;
	GetVehiclePos(veh_id, pojazd[veh_id][v_X], pojazd[veh_id][v_Y], pojazd[veh_id][v_Z]);
	GetVehicleZAngle(veh_id, pojazd[veh_id][v_R]);
	pojazd[veh_id][v_color][0] = kolr1;
	pojazd[veh_id][v_color][1] = kolr2;
	pojazd[veh_id][v_paliwo] = 9999;
	if(pojazd[veh_id][v_paliwo] >= 9999) pojazd[veh_id][v_paliwo] = GetVehicleFuelSize(pojazd[veh_id][v_model]);
	if(pojazd[veh_id][v_paliwo] == 0) pojazd[veh_id][v_paliwo] = 9999;
	pojazd[veh_id][v_owner_type] = VEHICLE_PUBLIC;
	pojazd[veh_id][v_owner] = VO_EVENT;
	Handbrake(veh_id, hndbrk);

	pojazd[veh_id][v_event_used]=true;
	pojazd[veh_id][v_event_creator_uid]=creator;
	pojazd[veh_id][v_event_godmode]=god;
	pojazd[veh_id][v_event_teamid]=tmid;

	format(str_text, 500, "[Pojazd {6666FF}Eventowy{ffffff}]\n{ffff00}%s\n{c0c0c0}ID: %d", VehicleNames[mdlid-400],veh_id);
	pojazd[veh_id][v_text3d] = CreateDynamic3DTextLabel(str_text, -1, 0.0, 0.0, 0.0, 10.0, .attachedvehicle = veh_id, .testlos = 1);
	SetVehicleNumberPlate(veh_id, "{6666ff}EVENT");
	format(pojazd[vehicleid][v_numberplate], 32, "{6666ff}EVENT");
	SetVehicleToRespawn(veh_id);
	LinkVehicleToInterior(veh_id, pojazd[veh_id][v_event_interior]);
	SetVehicleVirtualWorld(veh_id, pojazd[veh_id][v_event_virtual_world]);
	SetVehicleParamsEx(veh_id, 1, 1, 0, 0, 0, 0, 0);
	SetVehicleParamsCarWindows(veh_id, 1, 1, 1, 1);

	AddEventLog(form("Pojazd eventowy UID: %d zostal zapisany do respawnu! (Koordynaty: %f, %f, %f, %f)",veh_id,pojazd[veh_id][v_X],pojazd[veh_id][v_Y],pojazd[veh_id][v_Z],pojazd[veh_id][v_R]));
	return 1;
}

stock GetEventVehicles()
{
	new t_ilosc=0;
	for(new i=GetVehiclePoolSize(); i!=0; i--)
	{
		if(GetVehicleModel(i)&&pojazd[i][v_event_used]==true) t_ilosc++;
		continue;
	}
	return t_ilosc;
}

stock GetEventTeamUsers(teamid)
{
	new t_ilosc=0;
	for(new i=PlayerPoolSize(); i!=-1; i--)
	{
		if(gracz[i][loggedin]==true&&gracz[i][event_teamid]==teamid) t_ilosc++;
		continue;
	}
	return t_ilosc;
}


stock bool:IsEv_PlayerControllable(playerid)
{
	if(gracz[playerid][ev_toggle_controllable]==true) return true;
	return false;
}

stock Ev_PlayerControllable(playerid, bool:toggle)
{
	if(!IsPlayerConnected(playerid)) return 0;
	gracz[playerid][ev_toggle_controllable]=toggle;
	TogglePlayerControllable(playerid, toggle);
	return 1;
}

stock bool:EvIsPlayerInRangeOfPlayer(id1,Float:range,id2)
{
	new Float:ISIROP[3];
	GetPlayerPos(id1, ISIROP[0], ISIROP[1], ISIROP[2]);
	if(IsPlayerInRangeOfPoint(id2, range, ISIROP[0], ISIROP[1], ISIROP[2])) return true;
	return false;
}

stock GetEventUsers(bool:with_masters=false)
{
	new t_ilosc=0;
	if(serwer[event_started]==true)
	{
		for(new i=PlayerPoolSize(); i != -1; i--)
		{
			if(with_masters==false) if(gracz[i][event_master]==true) continue;
			if(IsPlayerConnected(i)&&gracz[i][loggedin]==true&&gracz[i][event_saved]==true) t_ilosc++;
		}
	}
	return t_ilosc;
}

stock GetEventMasters()
{
	new t_ilosc=0;
	if(serwer[event_started]==true)
	{
		for(new i=PlayerPoolSize(); i != -1; i--)
		{
			if(IsPlayerConnected(i)&&gracz[i][loggedin]==true&&gracz[i][event_master]==true) t_ilosc++;
		}
	}
	return t_ilosc;
}

stock GetEventUsersNearPlayer(playerid, bool:with_masters=false,Float:range=EVENT_LOCAL_RANGE)
{
	new t_ilosc=0;
	for(new i=GetPlayerPoolSize(); i!=-1; i--)
	{
		if(with_masters==false && gracz[i][event_master]==true) continue;
		if(IsPlayerConnected(i)&&gracz[i][event_saved]==true&&EvIsPlayerInRangeOfPlayer(i,range,playerid)) t_ilosc++;
		continue;
	}
	return t_ilosc;
}

stock SendEventMessageToAll(tresc[])
{
	new strSM[1500];
	format(strSM,1500,"{6666ff}[Event]{ffffff} %s",tresc);
	for(new i=PlayerPoolSize(); i != -1; i--)
	{
		if(IsPlayerConnected(i)&&gracz[i][loggedin]==true) RenderMessage(i, -1, strSM);
		continue;
	}
	return 1;
}

stock RenderMessage(top, color, const text[])
{
	new temp[156], tosearch = 0, colorint, posscolor, lastcol[12];
	new mess[356], colors, tempc; format(mess, 356, "%s",text);
 
	while(strlen(mess) > 0)
	{
		if(strlen(mess) < 140)
		{
			SendClientMessage(top, color, mess);
			break;
		}
 
		strmid(temp, mess, 0, 140);
		while(strfind(temp, "{", true) != -1)
		{
			tempc = strfind(temp, "{", true);
			if(temp[tempc+7] == '}')
			{
				colors ++;
				strdel(temp, tempc, tempc+7);
			}
			else
			{
				temp[tempc] = '0';
				continue;
			}
		}
		temp = "";
 
		if(strlen(mess) <= 100+colors*8 && strlen(mess) <= 140)
		{
			SendClientMessage(top, color, mess);
			break;
		}
		tosearch = strfind(mess," ",true, 100+colors*8)+1;
		while(tosearch > 140 || tosearch <= 0)
		{
				colors --;
				tosearch = strfind(mess," ",true,100+colors*8)+1;
				}
 
		if(strfind(mess,"{",true) != -1) //color codes detection , YAY
		{
			posscolor = strfind(mess,"{",true);
 
			if(mess[posscolor+7] == '}') //detected one color
			colorint = posscolor;
 
			while(strfind(mess,"{",true,colorint+1) != -1) //repeat until none are found
			{
				posscolor = strfind(mess,"{",true,colorint+1);
				if(posscolor > tosearch) //if next color will be on the other line, use last color found to render on the next line
				{
					posscolor = colorint;
					break;
				}
				if(mess[posscolor+7] == '}') //if found, then assign the color
				{
					colorint = posscolor;
				}
				else
				{
					posscolor = colorint; //else, leave the last color.
					break;
				}
			}
 
			if(colorint == posscolor) //if the color position equals the one that was found
				strmid(lastcol,mess,colorint,colorint+8); //get the last used color string.
		}
 
		strmid(temp, mess, 0, tosearch);
		SendClientMessage(top, color, temp);
		strdel(mess, 0, tosearch);
		strins(mess, lastcol, 0); //insert last used color into the new line to be processed.
 
		temp = "";
		tosearch = 0;
		colors = 0;
	}
	return 1;
}

stock SendEventMessage(tresc[])
{
	new stringSM[1500];
	format(stringSM,1500,"{6666ff}[Event]{ffffff} %s",tresc);
	for(new i=PlayerPoolSize(); i != -1; i--)
	{
		if(IsPlayerConnected(i)&&gracz[i][event_saved]==true) RenderMessage(i, -1, stringSM);
		continue;
	}
	return 1;
}

stock bool:IsVehicleEmpty(vehicleid)
{
	for(new i=PlayerPoolSize(); i!=-1; i--)
	{
		if(IsPlayerConnected(i)&&gracz[i][loggedin]==true)
		{
			if(IsPlayerInAnyVehicle(i))
			{
				if(GetPlayerVehicleID(i)==vehicleid)
				{
					return false;
				}
			}
		}
		continue;
	}
	return true;
}

stock GetEventTeamVehicles(teamid)
{
	new t_ilosc=0;
	for(new i=GetVehiclePoolSize(); i!=0; i--)
	{
		if(GetVehicleModel(i)&&pojazd[i][v_event_teamid]==teamid&&pojazd[i][v_event_used]==true) t_ilosc++;
		continue;
	}
	return t_ilosc;
}

stock Float:ExFloatRandom(Float:min,Float:max)
{
	new Float:ran;
	MRandFloatRange(min, max, ran);
	return ran;
}

stock Init_EventPanel()
{
	Event_Info = TextDrawCreate(320.000000, 356.000000, "_");
	TextDrawFont(Event_Info, 1);
	TextDrawLetterSize(Event_Info, 0.420832, 1.399999);
	TextDrawTextSize(Event_Info, 400.000000, 192.000000);
	TextDrawSetOutline(Event_Info, 0);
	TextDrawSetShadow(Event_Info, 1);
	TextDrawAlignment(Event_Info, 2);
	TextDrawColor(Event_Info, -1);
	TextDrawBackgroundColor(Event_Info, 255);
	TextDrawBoxColor(Event_Info, 50);
	TextDrawUseBox(Event_Info, 1);
	TextDrawSetProportional(Event_Info, 1);
	TextDrawSetSelectable(Event_Info, 0);

	serwer[event_max_added_score]=50000;
	serwer[event_max_added_money]=5000000;

	EV_CASES_ADD_LISTID = LoadModelSelectionMenu("ev_cases_list.txt");
	EV_CASES_ADD_IDS = LoadModelSelectionMenu("ev_cases_list.txt");

	serwer[event_cases_daily_count]=0;

	for(new i=0; i < EVENT_MAX_CASES; i++)
	{
		serwer[event_case][i]=-1;
		serwer[event_case_money][i]=0;
		serwer[event_case_score][i]=0;
		serwer[event_case_textid][i]=STREAMER_TAG_3D_TEXT_LABEL:INVALID_3DTEXT_ID;
		serwer[event_cases_pos_x][i]=0.0;
		serwer[event_cases_pos_y][i]=0.0;
		serwer[event_cases_pos_z][i]=0.0;
		format(event_cases_podpowiedz[i],124,"");
	}

	AddEventLog(form("Inicjacja panelu eventowego (Pierwsze uruchomienie - start serwera)"));
	return 1;
}

task Ev_UnLockOOC_Info()
{
	if(serwer[block_global_ooc]==true)
	{
		serwer[block_global_ooc]=false;
	}
	return 1;
}

task Process_EventPanelPID(playerid)//sekundowy timer per playerid, zaimplementowane logged i spawned - więc nie dawaj tego.
{
	if(GetEventCases()>0)
	{
		for(new i=0; i < EVENT_MAX_CASES; i++)
		{
			if(IsValidDynamicPickup(serwer[event_case][i]))
			{
				if(IsPlayerInRangeOfPoint(playerid, 1.0, serwer[event_cases_pos_x][i], serwer[event_cases_pos_y][i], serwer[event_cases_pos_z][i])&&gracz[playerid][event_master]==false)
				{
					if(serwer[event_case_money][i]>0) GiveMoney(playerid,serwer[event_case_money][i]);
					if(serwer[event_case_score][i]>0) GiveScore(playerid,serwer[event_case_score][i]);
					if(serwer[event_case_score][i]>0&&serwer[event_case_money][i]>0) Info(playerid,form("{c0c0c0}Brawo! Znalazłeś/aś niespodziankę! Otrzymujesz {ffff00}%d{c0c0c0} score i {ffff00}%d {c0c0c0}kasy!",serwer[event_case_score][i],serwer[event_case_money][i]));
					if(serwer[event_case_score][i]>0&&serwer[event_case_money][i]==0) Info(playerid,form("{c0c0c0}Brawo! Znalazłeś/aś niespodziankę! Otrzymujesz {ffff00}%d{c0c0c0} score!",serwer[event_case_score][i]));
					if(serwer[event_case_score][i]==0&&serwer[event_case_money][i]>0) Info(playerid,form("{c0c0c0}Brawo! Znalazłeś/aś niespodziankę! Otrzymujesz {ffff00}%d {c0c0c0}kasy!",serwer[event_case_money][i]));
					DestroyEventCase(playerid,i);
					break;
				}
			}
		}
	}
	if(serwer[event_started]==true)
	{
		if(serwer[event_records_on]==true)
		{
			new str[200];
			format(str,200,"~p~EVENT~n~~w~Ilosc Uczestnikow:~n~%d/%d (%d)~n~Aby dolaczyc wpisz ~y~/event",GetEventUsers(),serwer[event_max_users],GetEventMasters());
			TextDrawSetString(Event_Info, str);
			TextDrawShowForPlayer(playerid, Event_Info);
		}

		if(gracz[playerid][event_master]==true && gracz[playerid][event_saved]==false) gracz[playerid][event_saved]=true;
	}
	return 1;
}

task Process_EventPanel()//sekundowy timer
{
	if(serwer[event_started]==false) return 1;

	if(serwer[event_sec_odliczanie]!=0)
	{
		serwer[event_sec_odliczanie]--;
		for(new i=PlayerPoolSize(); i != -1; i--)
		{
			if(!IsPlayerConnected(i)) continue;
			if(gracz[i][loggedin]==false)  continue;
			if(gracz[i][event_saved]==false) continue;
			if(serwer[event_sec_odliczanie]>0) GameTextForPlayer(i, form("~b~Odliczanie:~n~~n~~w~%d",serwer[event_sec_odliczanie]), 1000, 3);
			else GameTextForPlayer(i, "~g~GO!", 1000, 3);
		}
	}

	if(serwer[event_master_exit_timestamp]==0&&!GetEventMasters())
	{
		serwer[event_master_exit_timestamp]=gettime();
		SendEventMessageToAll(form("Ostatni(a) z event masterów wyszedł(a) z serwera! Za %d minut event zostanie zakończony.",EVENT_MINUTES_TO_CLOSE_WITHOUT_EVENT_MASTER/60));
		AddEventLog(form("Wyjscie ostatniego event mastera - Inicjacja samo zakonczenia (%d minut)",EVENT_MINUTES_TO_CLOSE_WITHOUT_EVENT_MASTER/60));
	}
	if(serwer[event_master_exit_timestamp]>0)
	{
		if(GetEventMasters()>0)
		{
			serwer[event_master_exit_timestamp]=0;
			SendEventMessageToAll("Event master wrócił(a) na serwer! Event będzie kontynuowany.");
			AddEventLog(form("Powrot event mastera! Wylaczenie samo zakonczenia!"));
			return 1;
		}
		if((gettime()-serwer[event_master_exit_timestamp])>=EVENT_MINUTES_TO_CLOSE_WITHOUT_EVENT_MASTER)
		{
			new str_end[300];
			format(str_end, 300, "{c0c0c0}Czas trwania: %s", StrSecounds(gettime()-serwer[event_time_start]));
			
			serwer[event_started]=false;
			serwer[event_weather_id]=-1;
			serwer[event_hour]=-1;
			SendEventMessageToAll(form("{696969}BOT HL{ff3333} zakończył(a){6666ff} Event{ffffff}! %s {c0c0c0}(Powód: Brak obecności event mastera przez %d min.)",str_end,(EVENT_MINUTES_TO_CLOSE_WITHOUT_EVENT_MASTER/60)));
			for(new i = PlayerPoolSize(); i != -1; i--)
			{
				if(gracz[i][loggedin]==true)
				{
					TextDrawHideForPlayer(i, Event_Info);
					if(gracz[i][event_saved]==true)
					{
						gracz[i][event_saved]=false;
						if(!IsEv_PlayerControllable(i)) Ev_PlayerControllable(i, true);
						if(gracz[i][event_teamid] != -1) gracz[i][event_teamid]=-1;
						if(gracz[i][event_hide_labels] == true) gracz[i][event_hide_labels]=false;
						//Czyszczenie PVarow
						if(gracz[i][event_master] == true)
						{
							DeletePVar(i,"EvPan_VEH_SEL_ModelID");
							DeletePVar(i,"EvP_ClickedID");
							DeletePVar(i,"Ev_NewTeamID");
							DeletePVar(i,"EvPan_VEH_SEL_Color1");
							DeletePVar(i,"EvPan_VEH_EDIT_Color1");
							DeletePVar(i,"EvPan_VEH_LIST_id");
							DeletePVar(i,"EV_GIVE_WEAPONS_ALL_id");
							DeletePVar(i,"EV_GIVE_WEAPONS_LOCAL_id");
						}
						//
						ResetPlayerWeapons(i);
						SetPlayerArmour(i, 0.0);
						SetPlayerHealth(i, 100.0);
						LoadFractionWeapons(i, gracz[i][frakcja]);

						SetPlayerPos(i, 1098.4006+ExFloatRandom(-2,2),1434.0753+ExFloatRandom(-2,2),12.3712+ExFloatRandom(0,1)); //daj kordy spawnu
						SetPlayerFacingAngle(i, 3.7128+ExFloatRandom(-180,180));
						SetPlayerInterior(i, 0);
						SetPlayerVirtualWorld(i, 0);

						if(gracz[i][event_last_skin_id]!=0) SetPlayerSkin(i, gracz[i][event_last_skin_id]);
						gracz[i][event_last_skin_id]=0;
					}
				}
				continue;
			}
			for(new i=GetVehiclePoolSize(); i!=0; i--)
			{
				if(pojazd[i][v_event_used]==true)
				{
					DestroyEventVehicle(i);
				}
				continue;
			}
			for(new i=0; i < MAX_EVENT_TEAMS; i++)
			{
				event_teams[i][used]=false;
				for(new ii=PlayerPoolSize(); ii!=-1; ii--)
				{
					gracz[ii][event_teamid]=-1;
				}
				format(event_teams[i][team_name],MAX_EVENT_TEAM_NAME,"");
			}
			serwer[event_time_start]=0;
			serwer[event_max_users]=0;
			serwer[event_records_on]=false;
			serwer[event_master_exit_timestamp]=0;
			AddEventLog(form("Zakonczenie eventu przez bota - brak event mastera!"));
		}
	}
	return 1;
}

task OnEventVehicleSpawn(vehicleid)
{
	if(pojazd[vehicleid][v_event_used]==true)
	{
		LinkVehicleToInterior(vehicleid, pojazd[vehicleid][v_event_interior]);
		SetVehicleVirtualWorld(vehicleid, pojazd[vehicleid][v_event_virtual_world]);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, pojazd[vehicleid][v_text3d], E_STREAMER_WORLD_ID, pojazd[vehicleid][v_event_virtual_world]);
		Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, pojazd[vehicleid][v_text3d], E_STREAMER_INTERIOR_ID, pojazd[vehicleid][v_event_interior]);
	}
	return pojazd[vehicleid][v_event_used];
}

task eventp_OnVehicleUpdate(vehicleid)//pętla sekundowa dla pojazdów
{
	if(pojazd[vehicleid][v_event_used]==true)
	{
		if(pojazd[vehicleid][v_event_godmode]==true)
		{
			GetVehicleHealth(vehicleid,pojazd[vehicleid][v_HP]);
			if(pojazd[vehicleid][v_HP] < 980.0)
			{
				RepairVehicle(vehicleid);
			}
			new Float:tX, Float:tY, Float:tZ, Float:tR;
			new Float:velX, Float:velZ, Float:velY;
			GetVehiclePos(vehicleid, tX, tY, tZ);
			GetVehicleZAngle(vehicleid, tR);
			GetVehicleVelocity(vehicleid, velX, velY, velZ);
			if(pojazd[vehicleid][v_HP] < 255.0)//flip pojazdu
			{
				SetVehiclePos(vehicleid, tX, tY, tZ);
				SetVehicleZAngle(vehicleid, tR);
				SetVehicleVelocity(vehicleid, velX, velY, velZ);
			}
		}
		new str_text[500];
		new mdlid = GetVehicleModel(vehicleid);
		if(pojazd[vehicleid][v_event_teamid]!=-1)
		{
			format(str_text, 500, "[Pojazd {6666FF}Eventowy{ffffff}]\n{ffff00}%s\n{00ff00}Drużyna:\n{ffff00}%s\n{c0c0c0}ID: %d", VehicleNames[mdlid-400],event_teams[pojazd[vehicleid][v_event_teamid]][team_name],vehicleid);
			UpdateDynamic3DTextLabelText(pojazd[vehicleid][v_text3d], -1, str_text);
		}
		else
		{
			format(str_text, 500, "[Pojazd {6666FF}Eventowy{ffffff}]\n{ffff00}%s\n{c0c0c0}ID: %d", VehicleNames[mdlid-400],vehicleid);
			UpdateDynamic3DTextLabelText(pojazd[vehicleid][v_text3d], -1, str_text);
		}
	}
	return pojazd[vehicleid][v_event_used];//ważne
}

stock PermissionEventVehicle(playerid, vehicleid)//spięte
{
	if(pojazd[vehicleid][v_event_used]==true)
	{
		if(GetVehicleModel(vehicleid))
		{
			if(gracz[playerid][event_saved]==false)
			{
				if(gracz[playerid][event_master]==true)
				{
					return 1;
				}
				return 0;
			}
			if(pojazd[vehicleid][v_event_teamid]!=-1)//Gdy pojazd nie jest w drużynie i żeby gracz majacy przypisaną drużynę mógł do niego wsiąść
			{
				if(pojazd[vehicleid][v_event_teamid]!=gracz[playerid][event_teamid])
				{
					if(gracz[playerid][event_master]==true)
					{
						return 1;
					}
					return 0;
				}
			}
		}
	}
	return 1;
}

task OnEventVehicleDeath(vehicleid, killerid)//OnVehicleDeath tylko dla pojazdów eventowych
{
	if(serwer[event_destroy_or_respawn_veh] == true)
	{
		DestroyEventVehicle(vehicleid);
	}
	else
	{
		Handbrake(vehicleid,E_HANDBRAKE_OFF);
		SetVehicleToRespawn(vehicleid);
	}
	return 1;
}

task eventp_OnPlayerDisconnect(playerid, reason)
{
	return 1;
}

task EventColor(playerid)
{
	new ev_col = 0;//SetPlayerColor
	if(serwer[event_started]==true)
	{
		if(gracz[playerid][event_master]==true)
		{
			ev_col = 0xff0000FF;
			return ev_col;
		}

		if(gracz[playerid][event_saved]==true)
		{
			if(gracz[playerid][event_hide_labels]==true)
			{
				//ukrywanie labeli i markerów
				ev_col = KOLOR_EVENT - (KOLOR_EVENT & 0x000000FF);
				return ev_col;
			}
			ev_col = KOLOR_EVENT;
		}
		else return ev_col;
	}
	else return ev_col;
	return ev_col;
}

task ev_OnPlayerModelSelectionEx(playerid, response, extraid, modelid) //mSelection
{
	if(response)
	{
		switch(extraid)
		{
			case EV_VEH_SEL_1:
			{
				SetPVarInt(playerid, "EvPan_VEH_SEL_ModelID", modelid);
				new str[4096];
				format(str,4096,"Wybierz pierwszy kolor:\n");
				for(new i=0; i < 256; i++)
				{
					format(str,4096,"%s{%06x}%d III\n",str,RGBAToRGB(VehicleColoursTableRGBA[i]),i);
				}
				Dialog_Show(playerid, EV_VEH_COL_1, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Panel pojazdów", str, "Dalej", "Wróć");
				return 1;
			}
			case EV_VEH_SEL_0_1:
			{
				SetPVarInt(playerid, "EvPan_VEH_SEL_ModelID", modelid);
				new str[4096];
				format(str,4096,"Wybierz pierwszy kolor:\n");
				for(new i=0; i < 256; i++)
				{
					format(str,4096,"%s{%06x}%d III\n",str,RGBAToRGB(VehicleColoursTableRGBA[i]),i);
				}
				Dialog_Show(playerid, EV_VEH_COL_1, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Panel pojazdów", str, "Dalej", "Wróć");
				return 1;
			}
			case EV_SELECT_SKIN_ALL:
			{
				new find=0;
				for(new i=PlayerPoolSize(); i!=-1; i--)
				{
					if(!IsPlayerConnected(i)||gracz[i][event_saved]==false) continue;

					if(gracz[i][event_last_skin_id]==0) gracz[i][event_last_skin_id]=GetPlayerSkin(i);
					SetPlayerSkin(i, modelid);
					Info(i,form("{696969}%s [ID:%d] {c0c0c0}zmienił ci skin.",nick(playerid),playerid));
					AddEventLog(form("%s [ID:%d] zmienia skin dla %s [ID:%d] na ID: %d",nick(playerid),playerid,nick(i),i,modelid));
					find++;
				}
				Info(playerid,form("{c0c0c0}Pomyślnie zmieniono skin dla {696969}%d{c0c0c0} uczestników!",find));
				AddEventLog(form("%s [ID:%d] zmienil(a) skin dla %d uczestnikow",nick(playerid),playerid,find));
			}
			case EV_SELECT_SKIN_LOCAL:
			{
				new find=0;
				for(new i=PlayerPoolSize(); i!=-1; i--)
				{
					if(!IsPlayerConnected(i)||gracz[i][event_saved]==false||!EvIsPlayerInRangeOfPlayer(i,EVENT_LOCAL_RANGE,playerid)) continue;

					if(gracz[i][event_last_skin_id]==0) gracz[i][event_last_skin_id]=GetPlayerSkin(i);
					SetPlayerSkin(i, modelid);
					Info(i,form("{696969}%s [ID:%d] {c0c0c0}zmienił ci skin.",nick(playerid),playerid));
					AddEventLog(form("%s [ID:%d] zmienia skin dla %s [ID:%d] na ID: %d [LOCAL]",nick(playerid),playerid,nick(i),i,modelid));
					find++;
				}
				Info(playerid,form("{c0c0c0}Pomyślnie zmieniono skin dla {696969}%d{c0c0c0} uczestników!",find));
				AddEventLog(form("%s [ID:%d] zmienil skin dla %d uczestnikow [LOCAL]",nick(playerid),playerid,find));
			}
			case EV_USERS_SELECT_SKIN:
			{
				new e_id = GetPVarInt(playerid, "EvP_ClickedID");
				if(gracz[e_id][event_last_skin_id]==0) gracz[e_id][event_last_skin_id]=GetPlayerSkin(e_id);
				SetPlayerSkin(e_id,modelid);
				Info(e_id,form("{696969}%s [ID:%d] {c0c0c0}zmienił ci skin.",nick(playerid),playerid));
				Info(playerid,"{c0c0c0}Zmieniono skina dla gracza.");
				AddEventLog(form("%s [ID:%d] zmienil skin dla %s [ID:%d] na ID: %d [SOLO]",nick(playerid),playerid,nick(e_id),e_id,modelid));
			}
		}
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
task ev_OnPlayerModelSelection(playerid, response, listid, modelid)
{
	if(response)
	{
		if(listid == EV_CASES_ADD_LISTID)
		{
			new podp[122];
			GetPVarString(playerid, "Ev_Cases_Podpowiedz", podp, 122);
			if(!CreateEventCase(playerid,modelid,GetPVarInt(playerid, "Ev_Cases_Score"),GetPVarInt(playerid, "Ev_Cases_Money"),podp)) return Error(playerid,form("Osiągnięto już limit niespodzianek! (%d)",EVENT_MAX_CASES));
			DeletePVar(playerid, "Ev_Cases_Score");
			DeletePVar(playerid, "Ev_Cases_Money");
			DeletePVar(playerid, "Ev_Cases_Podpowiedz");
		}
		if(listid == EV_CASES_ADD_IDS)
		{
			SetPVarInt(playerid, "Ev_Cases_ID", modelid);
			Dialog_Show(playerid, EV_CASES_ADD_M, DIALOG_STYLE_INPUT, "{6666ff}Event{ffffff}Panel - Niespodzianki", "{c0c0c0}Jeśli chcesz aby gracz nie otrzymał kasy wpisz {ffffff}0{c0c0c0}\n\n{ffffff}Wpisz ilosc kasy jaką mogą znaleźć:", "Dalej", "Wróć");
		}
	}
	return 1;
}

Dialog:EV_CASES_ADD_M(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		DeletePVar(playerid, "Ev_Cases_ID");
		PC_EmulateCommand(playerid,"/ev");
		return 1;
	}
	if(!strlen(inputtext)) return Dialog_Show(playerid, EV_CASES_ADD_M, DIALOG_STYLE_INPUT, "{6666ff}Event{ffffff}Panel - Niespodzianki", "{ff3333}Nic nie wpisano!\n\n{c0c0c0}Jeśli chcesz aby gracz nie otrzymał kasy wpisz {ffffff}0{c0c0c0}\n\n{ffffff}Wpisz ilosc kasy jaką mogą znaleźć:", "Dalej", "Wróć");
	if(!isnumeric(inputtext)) return Dialog_Show(playerid, EV_CASES_ADD_M, DIALOG_STYLE_INPUT, "{6666ff}Event{ffffff}Panel - Niespodzianki", "{ff3333}Wpisano zły format!\n\n{c0c0c0}Jeśli chcesz aby gracz nie otrzymał kasy wpisz {ffffff}0{c0c0c0}\n\n{ffffff}Wpisz ilosc kasy jaką mogą znaleźć:", "Dalej", "Wróć");
	if(strval(inputtext)<0) return Dialog_Show(playerid, EV_CASES_ADD_M, DIALOG_STYLE_INPUT, "{6666ff}Event{ffffff}Panel - Niespodzianki", "{ff3333}Wpisano zbyt małą wartość!\n\n{c0c0c0}Jeśli chcesz aby gracz nie otrzymał kasy wpisz {ffffff}0{c0c0c0}\n\n{ffffff}Wpisz ilosc kasy jaką mogą znaleźć:", "Dalej", "Wróć");
	if(strval(inputtext)>EVENT_MAX_CASES_MONEY) return Dialog_Show(playerid, EV_CASES_ADD_M, DIALOG_STYLE_INPUT, "{6666ff}Event{ffffff}Panel - Niespodzianki", "{ff3333}Wpisano zbyt dużą wartość!\n\n{c0c0c0}Jeśli chcesz aby gracz nie otrzymał kasy wpisz {ffffff}0{c0c0c0}\n\n{ffffff}Wpisz ilosc kasy jaką mogą znaleźć:", "Dalej", "Wróć");
	SetPVarInt(playerid, "Ev_Cases_Money", strval(inputtext));
	Dialog_Show(playerid, EV_CASES_ADD_S, DIALOG_STYLE_INPUT, "{6666ff}Event{ffffff}Panel - Niespodzianki", "{c0c0c0}Jeśli chcesz aby gracz nie otrzymał score wpisz {ffffff}0{c0c0c0}\n\n{ffffff}Wpisz ilosc score jaką mogą znaleźć:", "Dalej", "Wróć");
	return 1;
}
Dialog:EV_CASES_ADD_S(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		DeletePVar(playerid, "Ev_Cases_ID");
		DeletePVar(playerid, "Ev_Cases_Money");
		PC_EmulateCommand(playerid,"/ev");
		return 1;
	}
	if(!strlen(inputtext)) return Dialog_Show(playerid, EV_CASES_ADD_S, DIALOG_STYLE_INPUT, "{6666ff}Event{ffffff}Panel - Niespodzianki", "{ff3333}Nic nie wpisano!\n\n{c0c0c0}Jeśli chcesz aby gracz nie otrzymał score wpisz {ffffff}0{c0c0c0}\n\n{ffffff}Wpisz ilosc score jaką mogą znaleźć:", "Dalej", "Wróć");
	if(!isnumeric(inputtext)) return Dialog_Show(playerid, EV_CASES_ADD_S, DIALOG_STYLE_INPUT, "{6666ff}Event{ffffff}Panel - Niespodzianki", "{ff3333}Wpisano zły format!\n\n{c0c0c0}Jeśli chcesz aby gracz nie otrzymał score wpisz {ffffff}0{c0c0c0}\n\n{ffffff}Wpisz ilosc score jaką mogą znaleźć:", "Dalej", "Wróć");
	if(strval(inputtext)<0) return Dialog_Show(playerid, EV_CASES_ADD_S, DIALOG_STYLE_INPUT, "{6666ff}Event{ffffff}Panel - Niespodzianki", "{ff3333}Wpisano zbyt małą wartość!\n\n{c0c0c0}Jeśli chcesz aby gracz nie otrzymał score wpisz {ffffff}0{c0c0c0}\n\n{ffffff}Wpisz ilosc score jaką mogą znaleźć:", "Dalej", "Wróć");
	if(strval(inputtext)>EVENT_MAX_CASES_SCORE) return Dialog_Show(playerid, EV_CASES_ADD_S, DIALOG_STYLE_INPUT, "{6666ff}Event{ffffff}Panel - Niespodzianki", "{ff3333}Wpisano zbyt dużą wartość!\n\n{c0c0c0}Jeśli chcesz aby gracz nie otrzymał score wpisz {ffffff}0{c0c0c0}\n\n{ffffff}Wpisz ilosc score jaką mogą znaleźć:", "Dalej", "Wróć");
	if(GetPVarInt(playerid, "Ev_Cases_Money")==0&&strval(inputtext)==0) return Dialog_Show(playerid, EV_CASES_ADD_M, DIALOG_STYLE_INPUT, "{6666ff}Event{ffffff}Panel - Niespodzianki", "{ff3333}Wpisałeś/aś 0 score i 0 kasy!\n{c0c0c0}Gracz musi coś otrzymać!\n\n{c0c0c0}Jeśli chcesz aby gracz nie otrzymał kasy wpisz {ffffff}0{c0c0c0}\n\n{ffffff}Wpisz ilosc kasy jaką mogą znaleźć:", "Dalej", "Wróć");
	SetPVarInt(playerid, "Ev_Cases_Score",strval(inputtext));
	Dialog_Show(playerid, EV_CASES_ADD_P, DIALOG_STYLE_INPUT, "{6666ff}Event{ffffff}Panel - Niespodzianki", "{ffffff}Wpisz poniżej podpowiedź dla graczy:", "Dalej", "Wróć");
	return 1;
}
Dialog:EV_CASES_ADD_P(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		DeletePVar(playerid, "Ev_Cases_ID");
		DeletePVar(playerid, "Ev_Cases_Money");
		DeletePVar(playerid, "Ev_Cases_Score");
		PC_EmulateCommand(playerid,"/ev");
		return 1;
	}
	if(!strlen(inputtext)) return Dialog_Show(playerid, EV_CASES_ADD_P, DIALOG_STYLE_INPUT, "{6666ff}Event{ffffff}Panel - Niespodzianki", "{ff3333}Nic nie wpisano!\n\n{ffffff}Wpisz poniżej podpowiedź dla graczy:", "Dalej", "Wróć");
	if(!CreateEventCase(playerid,GetPVarInt(playerid, "Ev_Cases_ID"),GetPVarInt(playerid, "Ev_Cases_Score"),GetPVarInt(playerid, "Ev_Cases_Money"),inputtext)) return Error(playerid,form("Osiągnięto już limit walizek! (%d)",EVENT_MAX_CASES));
	DeletePVar(playerid, "Ev_Cases_ID");
	DeletePVar(playerid, "Ev_Cases_Money");
	DeletePVar(playerid, "Ev_Cases_Score");
	return 1;
}
Dialog:EV_USERS_TEAM(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new e_id = GetPVarInt(playerid, "EvP_ClickedID");
		new id = strval(inputtext)-1;
		if(id==-1)
		{
			Info(playerid,form("{c0c0c0}Usunięto {696969}%s [ID:%d] {c0c0c0}z drużyny {ffffff}%s",nick(e_id),e_id,event_teams[gracz[e_id][event_teamid]][team_name]));
			Info(e_id,form("{696969}%s [ID:%d] usunął/eła Ciebie {c0c0c0}z drużyny {ffffff}%s",nick(playerid),playerid,event_teams[gracz[e_id][event_teamid]][team_name]));
			AddEventLog(form("%s [ID:%d] usunal/ela %s [ID:%d] z druzyny %s",nick(playerid),playerid,nick(e_id),e_id,event_teams[gracz[e_id][event_teamid]][team_name]));
		}
		if(id>=0)
		{
			Info(playerid,form("{c0c0c0}Dodano {696969}%s [ID:%d] {c0c0c0}do drużyny {ffffff}%s",nick(e_id),e_id,event_teams[id][team_name]));
			Info(e_id,form("{696969}%s [ID:%d] dodał(a) Ciebie {c0c0c0}do drużyny {ffffff}%s",nick(playerid),playerid,event_teams[id][team_name]));
			AddEventLog(form("%s [ID:%d] dodal(a) %s [ID:%d] do druzyny %s",nick(playerid),playerid,nick(e_id),e_id,event_teams[id][team_name]));
		}
		gracz[e_id][event_teamid]=id;
		DeletePVar(playerid, "EvP_ClickedID");
	}
	else
	{
		PC_EmulateCommand(playerid, "/ev");
		DeletePVar(playerid, "EvP_ClickedID");
	}
	return 1;
}
Dialog:EV_USERS_PAN(playerid, response, listitem, inputtext[])
{
	new str[1500];
	if(response)
	{
		new e_id = GetPVarInt(playerid, "EvP_ClickedID");
		switch(listitem)
		{
			case 0://Wyrzuć z eventu
			{
				PC_EmulateCommand(playerid,form("/ev_udel %d",e_id));
				DeletePVar(playerid, "EvP_ClickedID");
			}
			case 1://Zmień drużynę
			{
				new bool:find=false;
				format(str,1500,"{ffffff}ID\tNazwa\tIlość członków\n");
				if(gracz[e_id][event_teamid]!=-1) format(str,1500,"%s0\t{ff0000}Usuń z aktualnej drużyny:\t%s\n",str,event_teams[gracz[e_id][event_teamid]][team_name]);
				for(new i=0; i < MAX_EVENT_TEAMS; i++)
				{
					if(event_teams[i][used]==true)
					{
						find=true;
						format(str,1500,"%s{ffffff}%d\t%s\t%d\n",str,i+1,event_teams[i][team_name],GetEventTeamUsers(i));
					}
				}
				if(find==false)
				{
					Error(playerid,"Brak jakichkolwiek drużyn!");
					DeletePVar(playerid, "EvP_ClickedID");
				}
				else
				{
					Dialog_Show(playerid, EV_USERS_TEAM, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Lista uczestników", str, "Zmień", "Wróć");
				}
			}
			case 2: //Dodaj/Usuń score
			{
				format(str,1500,"{c0c0c0}Zawartość banku score: {ffffff}%d\n\n{ffffff}Wpisz poniżej wartość jaką chcesz dać/usunąć uczestnikowi:",serwer[event_max_added_score]);
				Dialog_Show(playerid, EV_USERS_SCORE, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Lista uczestników - Dodaj/Usuń score", str, "Wykonaj", "Wróć");
			}
			case 3: //Dodaj/Usuń kase
			{
				format(str,1500,"{c0c0c0}Zawartość banku kasy: {ffffff}%d\n\n{ffffff}Wpisz poniżej wartość jaką chcesz dać/usunąć uczestnikowi:",serwer[event_max_added_money]);
				Dialog_Show(playerid, EV_USERS_MONEY, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Lista uczestników - Dodaj/Usuń kase", str, "Wykonaj", "Wróć");
			}
			case 4: //(Un)Freeze
			{
				if(!IsEv_PlayerControllable(e_id))
				{
					Ev_PlayerControllable(e_id, true);
					Info(playerid,form("{c0c0c0}Odmrożono {696969}%s [ID:%d]",nick(e_id),e_id));
					Info(e_id,form("{c0c0c0}Zostałeś/aś odmrożony/a przez {696969}%s [ID:%d]",nick(playerid),playerid));
					AddEventLog(form("%s [ID:%d] odmraza %s [ID:%d]",nick(playerid),playerid,nick(e_id),e_id));
					return 1;
				}
				else
				{
					Ev_PlayerControllable(e_id, false);
					Info(playerid,form("{c0c0c0}Zamrożono {696969}%s [ID:%d]",nick(e_id),e_id));
					Info(e_id,form("{c0c0c0}Zostałeś/aś zamrożony/a przez {696969}%s [ID:%d]",nick(playerid),playerid));
					AddEventLog(form("%s [ID:%d] zamraza %s [ID:%d]",nick(playerid),playerid,nick(e_id),e_id));
				}
			}
			case 5: //Teleportuj uczestnika do siebie
			{
				new Float:tp_Pos[3];
				GetPlayerPos(playerid, tp_Pos[0], tp_Pos[1], tp_Pos[2]);
				new bool:freeze=false;
				if(!IsEv_PlayerControllable(e_id)) freeze=true;
				if(freeze==true) Ev_PlayerControllable(playerid, true);
				SetPlayerPos(e_id, tp_Pos[0]+ExFloatRandom(-2.0,2.0), tp_Pos[1]+ExFloatRandom(-2.0,2.0), tp_Pos[2]+ExFloatRandom(0.0,2.0));
				SetPlayerInterior(e_id, GetPlayerInterior(playerid));
				SetPlayerVirtualWorld(e_id, GetPlayerVirtualWorld(playerid));
				if(freeze==true) Ev_PlayerControllable(playerid, false);
				Info(playerid,form("{c0c0c0}Przeteleportowano {696969}%s [ID:%d]{c0c0c0} do siebie!",nick(e_id),e_id));
				Info(e_id,form("{c0c0c0}Zostałeś/aś przeteleportowany/a przez {696969}%s [ID:%d]",nick(playerid),playerid));
				AddEventLog(form("%s [ID:%d] teleportuje %s [ID:%d] do siebie",nick(playerid),playerid,nick(e_id),e_id));
			}
			case 6: //Daj broń
			{
				strcat(str, "ID\tNazwa\n");
				for(new i=1; i<=46; i++)
				{
					if(!IsWeaponIsValid(i)) continue;
					format(str, 3000, "%s{ffffff}%d\t%s\n", str,i,WeaponName(i));
				}
				Dialog_Show(playerid, EV_USERS_GIVE_WEAPONS, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Daj broń", str, "Dalej", "Wróć");
			}
			case 7: //Wyczyść bronie
			{
				ResetPlayerWeapons(e_id);
				LoadFractionWeapons(e_id, gracz[e_id][frakcja]);
				Info(e_id,form("{696969}%s [ID:%d]{c0c0c0} wyczyścił(a) Ci bronie.",nick(playerid),playerid));
				Info(playerid,"{c0c0c0}Bronie gracza zostały wyczyszczone.");
				AddEventLog(form("%s [ID:%d] czysci bronie %s [ID:%d]",nick(playerid),playerid,nick(e_id),e_id));
			}
			case 8: //Ulecz uczestnika
			{
				SetPlayerHealth(e_id, 100.0);
				Info(e_id,form("{696969}%s [ID:%d]{c0c0c0} uleczył(a) Ciebie.",nick(playerid),playerid));
				Info(playerid,form("{c0c0c0}Uleczono {696969}%s [ID:%d]",nick(e_id),e_id));
				AddEventLog(form("%s [ID:%d] ulecza %s [ID:%d]",nick(playerid),playerid,nick(e_id),e_id));
			}
			case 9: //Daj/Odnów kamizelkę uczestnika
			{
				SetPlayerArmour(e_id, 100.0);
				Info(e_id,form("{696969}%s [ID:%d]{c0c0c0} dał(a) Tobie kamizelkę.",nick(playerid),playerid));
				Info(playerid,form("{c0c0c0}Dałeś/aś kamizelkę dla {696969}%s [ID:%d]",nick(e_id),e_id));
				AddEventLog(form("%s [ID:%d] daje/odnawia kamizelke dla %s [ID:%d]",nick(playerid),playerid,nick(e_id),e_id));
			}
			case 10: //Wyczyść armor uczestnika
			{
				SetPlayerArmour(e_id, 0.0);
				Info(e_id,form("{696969}%s [ID:%d]{c0c0c0} zabrał(a) Tobie kamizelkę.",nick(playerid),playerid));
				Info(playerid,form("{c0c0c0}Zabrałeś/aś kamizelkę dla {696969}%s [ID:%d]",nick(e_id),e_id));
				AddEventLog(form("%s [ID:%d] zabiera kamizelke dla %s [ID:%d]",nick(playerid),playerid,nick(e_id),e_id));
			}
			case 11: //Zmień skina uczestnika
			{
				new finded=0;
				for(new i=1; i <= 311; i++)
				{
					str[finded++]=i;
				}
				ShowModelSelectionMenuEx(playerid, str, finded, "Wybierz skin:", EV_USERS_SELECT_SKIN);
			}
			case 12: //Ustaw (nie)widzialność uczestnika
			{
				if(gracz[e_id][event_hide_labels]==true)
				{
					gracz[e_id][event_hide_labels]=false;
					Info(e_id,"{c0c0c0}Od teraz jesteś widoczny/a na mapie.");
					Info(playerid,"{c0c0c0}Gracz od teraz jest widoczny na mapie!");
					return 1;
				}
				else
				{
					gracz[e_id][event_hide_labels]=false;
					Info(e_id,"{c0c0c0}Od teraz jesteś niewidoczny/a na mapie.");
					Info(playerid,"{c0c0c0}Gracz od teraz jest niewidoczny na mapie!");
				}
			}
			case 13://Zmień interior dla uczestnika
			{
				format(str,3000,"{c0c0c0}Twój aktualny Interior: {ffffff}%d\n{c0c0c0}Poprawne ID Interiorów: {ffffff}0 - 256\n\n{ffffff}Wpisz poniżej ID Interioru na jaki chcesz zmienić:",GetPlayerInterior(playerid));
				Dialog_Show(playerid, EV_USERS_INTERIOR, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień interior dla uczestnika", str, "Zmień", "Wróć");
			}
			case 14://Zmień virtualworld dla uczestnika
			{
				format(str,3000,"{c0c0c0}Twój aktualny VW: {ffffff}%d\n{c0c0c0}Poprawne ID VW: {ffffff}0 - 2147483647\n\n{ffffff}Wpisz poniżej ID VirtualWorldu na jaki chcesz zmienić:",GetPlayerVirtualWorld(playerid));
				Dialog_Show(playerid, EV_USERS_VIRTUAL_WORLD, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień VirtualWorld dla uczestnika", str, "Zmień", "Wróć");
			}
		}
	}
	else
	{
		PC_EmulateCommand(playerid, "/ev");
	}
	return 1;
}
Dialog:EV_USERS_INTERIOR(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid,"/ev");
	new str[1500];
	if(!strlen(inputtext))
	{
		format(str,1500,"{ff3333}Nic nie wpisano!\n\n{c0c0c0}Poprawne ID Interiorów: {ffffff}0 - 256\n\n{ffffff}Wpisz poniżej ID Interioru na jaki chcesz zmienić:",GetPlayerInterior(playerid));
		Dialog_Show(playerid, EV_USERS_INTERIOR, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień interior dla uczestnika", str, "Zmień", "Wróć");
		return 1;
	}
	if(!isnumeric(inputtext))
	{
		format(str,1500,"{ff3333}Wpisano zły format!\n\n{c0c0c0}Poprawne ID Interiorów: {ffffff}0 - 256\n\n{ffffff}Wpisz poniżej ID Interioru na jaki chcesz zmienić:",GetPlayerInterior(playerid));
		Dialog_Show(playerid, EV_USERS_INTERIOR, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień interior dla uczestnika", str, "Zmień", "Wróć");
		return 1;
	}
	new inter_id = strval(inputtext);
	if(inter_id<0)
	{
		format(str,1500,"{ff3333}Wpisano zbyt mały Interior\n\n{c0c0c0}Poprawne ID Interiorów: {ffffff}0 - 256\n\n{ffffff}Wpisz poniżej ID Interioru na jaki chcesz zmienić:",GetPlayerInterior(playerid));
		Dialog_Show(playerid, EV_USERS_INTERIOR, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień interior dla uczestnika", str, "Zmień", "Wróć");
		return 1;
	}
	if(inter_id>256)
	{
		format(str,1500,"{ff3333}Wpisano zbyt duży Interior\n\n{c0c0c0}Poprawne ID Interiorów: {ffffff}0 - 256\n\n{ffffff}Wpisz poniżej ID Interioru na jaki chcesz zmienić:",GetPlayerInterior(playerid));
		Dialog_Show(playerid, EV_USERS_INTERIOR, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień interior dla uczestnika", str, "Zmień", "Wróć");
		return 1;
	}
	new e_id = GetPVarInt(playerid, "EvP_ClickedID");
	SetPlayerInterior(e_id, inter_id);
	Info(e_id,form("{696969}%s [ID:%d]{c0c0c0} zmienił(a) Tobie Interior na {ffff00}%d",nick(playerid),playerid,inter_id));
	Info(playerid,form("{c0c0c0}Pomyślnie zmieniono Interior dla {696969}%s [ID:%d] {c0c0c0}na ID {ffff00}%d",nick(e_id),e_id,inter_id));
	AddEventLog(form("%s [ID:%d] zmienil(a) interior dla %s [ID:%d] na ID: %d",nick(playerid),playerid,nick(e_id),e_id,inter_id));
	DeletePVar(playerid, "EvP_ClickedID");
	return 1;
}
Dialog:EV_USERS_VIRTUAL_WORLD(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid,"/ev");
	new str[1500];
	if(!strlen(inputtext))
	{
		format(str,1500,"{ff3333}Nic nie wpisano!\n\n{c0c0c0}Twój aktualny VW: {ffffff}%d\n{c0c0c0}Poprawne ID VW: {ffffff}0 - 2147483647\n\n{ffffff}Wpisz poniżej ID VirtualWorldu na jaki chcesz zmienić:",GetPlayerVirtualWorld(playerid));
		Dialog_Show(playerid, EV_USERS_VIRTUAL_WORLD, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień virtualworld dla uczestnika", str, "Zmień", "Wróć");
		return 1;
	}
	if(!isnumeric(inputtext))
	{
		format(str,1500,"{ff3333}Wpisano zły format!\n\n{c0c0c0}Twój aktualny VW: {ffffff}%d\n{c0c0c0}Poprawne ID VW: {ffffff}0 - 2147483647\n\n{ffffff}Wpisz poniżej ID VirtualWorldu na jaki chcesz zmienić:",GetPlayerVirtualWorld(playerid));
		Dialog_Show(playerid, EV_USERS_VIRTUAL_WORLD, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień virtualworld dla uczestnika", str, "Zmień", "Wróć");
		return 1;
	}
	new vw_id = strval(inputtext);
	if(vw_id<0)
	{
		format(str,1500,"{ff3333}Wpisano zbyt mały VirtualWorld\n\n{c0c0c0}Twój aktualny VW: {ffffff}%d\n{c0c0c0}Poprawne ID VW: {ffffff}0 - 2147483647\n\n{ffffff}Wpisz poniżej ID VirtualWorldu na jaki chcesz zmienić:",GetPlayerVirtualWorld(playerid));
		Dialog_Show(playerid, EV_USERS_VIRTUAL_WORLD, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień virtualworld dla uczestnika", str, "Zmień", "Wróć");
		return 1;
	}
	if(vw_id>2147483647)
	{
		format(str,1500,"{ff3333}Wpisano zbyt duży VirtualWorld\n\n{c0c0c0}Twój aktualny VW: {ffffff}%d\n{c0c0c0}Poprawne ID VW: {ffffff}0 - 2147483647\n\n{ffffff}Wpisz poniżej ID VirtualWorldu na jaki chcesz zmienić:",GetPlayerVirtualWorld(playerid));
		Dialog_Show(playerid, EV_USERS_VIRTUAL_WORLD, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień virtualworld dla uczestnika", str, "Zmień", "Wróć");
		return 1;
	}
	new e_id = GetPVarInt(playerid, "EvP_ClickedID");
	SetPlayerVirtualWorld(e_id, vw_id);
	Info(e_id,form("{696969}%s [ID:%d]{c0c0c0} zmienił(a) Tobie VirtualWorld na {ffff00}%d",nick(playerid),playerid,vw_id));
	Info(playerid,form("{c0c0c0}Pomyślnie zmieniono VirtualWorld dla {696969}%s [ID:%d] {c0c0c0}na ID {ffff00}%d",nick(e_id),e_id,vw_id));
	AddEventLog(form("%s [ID:%d] zmienil(a) virtualworld dla %s [ID:%d] na ID: %d",nick(playerid),playerid,nick(e_id),e_id,vw_id));
	DeletePVar(playerid, "EvP_ClickedID");
	return 1;
}
Dialog:EV_USERSGIVEWEAPONSAMMO(playerid, response, listitem, inputtext[])
{
	new e_id = GetPVarInt(playerid, "EvP_ClickedID");
	if(response)
	{
		if(isnull(inputtext)||!strlen(inputtext)) return Dialog_Show(playerid, EV_USERSGIVEWEAPONSAMMO, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Daj broń", "{ff0000}Nic nie wpisano!\n\n{c0c0c0}Aby dać nieskończoną ilość wpisz: {ffffff}9999\n\n{ffffff}Wpisz jaką ilość amunicji mają otrzymać?:", "Daj", "Wróć");
		if(!isnumeric(inputtext)) return Dialog_Show(playerid, EV_USERSGIVEWEAPONSAMMO, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Daj broń", "{ff0000}Wpisano zły format!\n\n{c0c0c0}Aby dać nieskończoną ilość wpisz: {ffffff}9999\n\n{ffffff}Wpisz jaką ilość amunicji mają otrzymać?:", "Daj", "Wróć");
		if(strval(inputtext)<=0) return Dialog_Show(playerid, EV_USERSGIVEWEAPONSAMMO, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Daj broń", "{ff0000}Wpisano złą wartość!\n\n{c0c0c0}Aby dać nieskończoną ilość wpisz: {ffffff}9999\n\n{ffffff}Wpisz jaką ilość amunicji mają otrzymać?:", "Daj", "Wróć");

		GivePlayerWeapon(e_id, GetPVarInt(playerid, "EV_USERS_GIVE_WEAPONS_id"), strval(inputtext));
		AddEventLog(form("%s [ID:%d] dal(a) bron dla %s [ID:%d] (ID:%d ammo:%d)",nick(playerid),playerid,nick(e_id),e_id,GetPVarInt(playerid, "EV_USERS_GIVE_WEAPONS_id"),strval(inputtext)));
		DeletePVar(playerid, "EV_USERS_GIVE_WEAPONS_id");
	}
	else
	{
		DeletePVar(playerid, "EV_USERS_GIVE_WEAPONS_id");
		PC_EmulateCommand(playerid, "/ev");
	}
	DeletePVar(playerid, "EvP_ClickedID");
	return 1;
}
Dialog:EV_USERS_GIVE_WEAPONS(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid,"/ev");

	SetPVarInt(playerid, "EV_USERS_GIVE_WEAPONS_id", strval(inputtext));
	Dialog_Show(playerid, EV_USERSGIVEWEAPONSAMMO, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Daj broń", "{c0c0c0}Aby dać nieskończoną ilość wpisz: {ffffff}9999\n\n{ffffff}Wpisz jaką ilość amunicji mają otrzymać?:", "Daj", "Wróć");
	return 1;
}
Dialog:EV_USERS_MONEY(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid,"/ev");
	new str[1500];
	new e_id = GetPVarInt(playerid, "EvP_ClickedID");
	if(!strlen(inputtext))
	{
		format(str,1500,"{ff3333}Nic nie wpisano!\n\n{c0c0c0}Zawartość banku kasy: {ffffff}%d\n\n{ffffff}Wpisz poniżej wartość jaką chcesz dać/usunąć uczestnikowi:",serwer[event_max_added_money]);
		Dialog_Show(playerid, EV_USERS_MONEY, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Lista uczestników - Dodaj/Usuń kase", str, "Wykonaj", "Wróć");
		return 1;
	}
	if(strval(inputtext)>=0)
	{
		if(!isnumeric(inputtext))
		{
			format(str,1500,"{ff3333}Wpisano zły format!\n\n{c0c0c0}Zawartość banku kasy: {ffffff}%d\n\n{ffffff}Wpisz poniżej wartość jaką chcesz dać/usunąć uczestnikowi:",serwer[event_max_added_money]);
			Dialog_Show(playerid, EV_USERS_MONEY, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Lista uczestników - Dodaj/Usuń kase", str, "Wykonaj", "Wróć");
			return 1;
		}
	}
	PC_EmulateCommand(playerid,form("/ev_umoney %d %d",e_id,strval(inputtext)));
	DeletePVar(playerid, "EvP_ClickedID");
	return 1;
}
Dialog:EV_USERS_SCORE(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid,"/ev");
	new str[1500];
	new e_id = GetPVarInt(playerid, "EvP_ClickedID");
	if(!strlen(inputtext))
	{
		format(str,1500,"{ff3333}Nic nie wpisano!\n\n{c0c0c0}Zawartość banku score: {ffffff}%d\n\n{ffffff}Wpisz poniżej wartość jaką chcesz dać/usunąć uczestnikowi:",serwer[event_max_added_score]);
		Dialog_Show(playerid, EV_USERS_SCORE, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Lista uczestników - Dodaj/Usuń score", str, "Wykonaj", "Wróć");
		return 1;
	}
	if(strval(inputtext)>=0)
	{
		if(!isnumeric(inputtext))
		{
			format(str,1500,"{ff3333}Wpisano zły format!\n\n{c0c0c0}Zawartość banku score: {ffffff}%d\n\n{ffffff}Wpisz poniżej wartość jaką chcesz dać/usunąć uczestnikowi:",serwer[event_max_added_score]);
			Dialog_Show(playerid, EV_USERS_SCORE, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Lista uczestników - Dodaj/Usuń score", str, "Wykonaj", "Wróć");
			return 1;
		}
	}
	PC_EmulateCommand(playerid,form("/ev_uscore %d %d",e_id,strval(inputtext)));
	DeletePVar(playerid, "EvP_ClickedID");
	return 1;
}
Dialog:EV_USERS(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new id = GetPlayerIDFromNick(inputtext);
		Info(playerid,form("{c0c0c0}Wybrano {696969}%s [ID:%d]",inputtext,id));
		PC_EmulateCommand(playerid,form("/ev_usercp %d",id));
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_START_MAX(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new str[1500];
		if(isnull(inputtext)||!strlen(inputtext))
		{
			format(str,1500,"{ff3333}Nic nie wpisano!\n\n{c0c0c0}Maksymalna liczba uczestników (slotów serwera): %d\n\n{ffffff}Wpisz ile ma wynosić maksymalna liczba uczestników:",MaxPlayers());
			Dialog_Show(playerid, EV_START_MAX, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Ilość uczestników", str, "{00ff00}START", "Wyjdź");
		}
		else
		{
			if(strval(inputtext)>0&&strval(inputtext)<=MaxPlayers())
			{
				serwer[event_max_users]=strval(inputtext);
				serwer[event_started]=true;
				serwer[event_time_start]=gettime();
				serwer[event_records_on]=false;
				serwer[event_master_exit_timestamp]=0;
				serwer[event_weather_id]=-1;
				serwer[event_hour]=-1;
				SendEventMessageToAll(form("{696969}%s [ID:%d]{00ff00} rozpoczął/eła{6666ff} Event{ffffff}! (Maksymalna liczba graczy: %d)",nick(playerid),playerid,serwer[event_max_users]));
				for(new i=0; i < MAX_EVENT_TEAMS; i++)
				{
					event_teams[i][used]=false;
					for(new ii=PlayerPoolSize(); ii!=-1; ii--)
					{
						gracz[ii][event_teamid]=-1;
					}
					format(event_teams[i][team_name],MAX_EVENT_TEAM_NAME,"");
				}
				serwer[event_pickup_id]=-1;
				serwer[event_pickup_pos][0]=0.0;
				serwer[event_pickup_pos][1]=0.0;
				serwer[event_pickup_pos][2]=0.0;
			}
			else
			{
				format(str,1500,"{ff3333}Wpisano złą ilość!\n\n{c0c0c0}Maksymalna liczba uczestników (slotów serwera): %d\n\n{ffffff}Wpisz ile ma wynosić maksymalna liczba uczestników:",MaxPlayers());
				Dialog_Show(playerid, EV_START_MAX, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Ilość uczestników", str, "{00ff00}START", "Wyjdź");
			}
		}
	}
	return 1;
}
Dialog:EV_NEW_TEAM(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(isnull(inputtext)||!strlen(inputtext)) return Dialog_Show(playerid, EV_NEW_TEAM, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Panel Drużyn", "{ff3333}Nic nie wpisano!\n\n{ffffff}Właśnie tworzysz nową dryżunę!\n\nPoniżej wpisz jej nazwę:", "Stwórz", "Wróć");
		else
		{
			new e_id = GetPVarInt(playerid, "Ev_NewTeamID");
			event_teams[e_id][used]=true;
			format(event_teams[e_id][team_name],MAX_EVENT_TEAM_NAME,"%s",inputtext);
			Info(playerid,form("{c0c0c0}Pomyślnie stworzono drużynę {ffffff}%s{c0c0c0}!",event_teams[e_id][team_name]));
			SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}stworzył(a) drużynę o nazwie{ffffff} %s{c0c0c0}!",nick(playerid),playerid,event_teams[e_id][team_name]));
			AddEventLog(form("%s [ID:%d] dodal druzyne %s",nick(playerid),playerid,event_teams[e_id][team_name]));
			DeletePVar(playerid, "Ev_NewTeamID");
		}
	}
	else
	{
		DeletePVar(playerid, "Ev_NewTeamID");
		PC_EmulateCommand(playerid, "/ev");
	}
	return 1;
}
Dialog:EV_NEW_NAME_TEAM(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(isnull(inputtext)||!strlen(inputtext)) return Dialog_Show(playerid, EV_NEW_NAME_TEAM, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Panel Drużyn", "{ff3333}Nie nie wpisano!\n\n{ffffff}Poniżej wpisz nową nazwę dryżyny:", "Zmień", "Wróć");
		else
		{
			new e_id = GetPVarInt(playerid, "Ev_NewTeamID");
			new str_old[50];
			format(str_old,50,"%s",event_teams[e_id][team_name]);
			format(event_teams[e_id][team_name],MAX_EVENT_TEAM_NAME,"%s",inputtext);
			SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}zmienił(a) nazwę drużyny z{ffffff} %s{c0c0c0} na {ffffff}%s{c0c0c0}!",nick(playerid),playerid,str_old,event_teams[e_id][team_name]));
			AddEventLog(form("%s [ID:%d] zmienil(a) nazwe druzyny z %s na %s",nick(playerid),playerid,str_old,event_teams[e_id][team_name]));
			DeletePVar(playerid, "Ev_NewTeamID");
		}
	}
	else
	{
		DeletePVar(playerid, "Ev_NewTeamID");
		PC_EmulateCommand(playerid, "/ev");
	}
	return 1;
}
Dialog:EV_EDIT_TEAM(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new e_id = GetPVarInt(playerid, "Ev_NewTeamID");
		switch(listitem)
		{
			case 0://nazwa
			{
				Dialog_Show(playerid, EV_NEW_NAME_TEAM, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Panel Drużyn", "{ffffff}Poniżej wpisz nową nazwę dryżyny:", "Zmień", "Wróć");
			}
			case 1://usun
			{
				event_teams[e_id][used]=false;
				Info(playerid,form("{c0c0c0}Pomyślnie usunięto drużynę {ffffff}%s{c0c0c0}!",event_teams[e_id][team_name]));
				SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}usunął/eła drużynę o nazwie{ffffff} %s{c0c0c0}!",nick(playerid),playerid,event_teams[e_id][team_name]));
				AddEventLog(form("%s [ID:%d] usunal/ela druzyne %s",nick(playerid),playerid,event_teams[e_id][team_name]));
				format(event_teams[e_id][team_name],MAX_EVENT_TEAM_NAME,"");
				for(new i=PlayerPoolSize(); i!=-1; i--)
				{
					if(gracz[i][event_teamid]==e_id) gracz[i][event_teamid]=-1;
					continue;
				}
				DeletePVar(playerid, "Ev_NewTeamID");
			}
			case 2://friendly fire
			{
				if(event_teams[e_id][friendly_fire]==false)
				{
					event_teams[e_id][friendly_fire]=true;
					Info(playerid,form("{00ff00}Włączono{c0c0c0} friendly fire w drużynie{ffffff} %s",event_teams[e_id][team_name]));
					AddEventLog(form("%s [ID:%d] wlaczyl(a) friendly fire w druzynie %s",nick(playerid),playerid,event_teams[e_id][team_name]));
					return 1;
				}
				else
				{
					event_teams[e_id][friendly_fire]=false;
					Info(playerid,form("{ff3333}Wyłączono{c0c0c0} friendly fire w drużynie{ffffff} %s",event_teams[e_id][team_name]));
					AddEventLog(form("%s [ID:%d] wylaczyl(a) friendly fire w druzynie %s",nick(playerid),playerid,event_teams[e_id][team_name]));
				}
				DeletePVar(playerid, "Ev_NewTeamID");
			}
			case 3://Dodaj do tej drużyny uczestników w pobliżu
			{
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(GetEventUsersNearPlayer(playerid,true)<=0) return Error(playerid,"Brak uczestników w pobliżu!");
				new ilosc=0;
				for(new i=PlayerPoolSize(); i!=-1; i--)
				{
					if(IsPlayerConnected(i)&&gracz[i][event_saved]==true&&EvIsPlayerInRangeOfPlayer(i,EVENT_LOCAL_RANGE,playerid)&&gracz[i][event_teamid]==-1)
					{
						if(playerid==i) continue;
						gracz[i][event_teamid]=e_id;
						Info(i,form("{696969}%s [ID:%d]{c0c0c0} dodał(a) Ciebie do drużyny {ffff00}%s",nick(playerid),playerid,event_teams[e_id][team_name]));
						AddEventLog(form("%s [ID:%d] dodal(a) %s [ID:%d] do druzyny %s [LOCAL]",nick(playerid),playerid,nick(i),i,event_teams[e_id][team_name]));
						ilosc++;
					}
					continue;
				}
				if(ilosc!=0)
				{
					Info(playerid,form("{c0c0c0}Pomyślnie dodano {ffffff}%d{c0c0c0} uczestników do drużyny {ffff00}%s",ilosc,event_teams[e_id][team_name]));
					AddEventLog(form("%s [ID:%d] dodal(a) %d uczestnikow do druzyny %s [LOCAL]",nick(playerid),playerid,ilosc,event_teams[e_id][team_name]));
					return 1;
				}
				PC_EmulateCommand(playerid,"/ev");
				Error(playerid,"Brak uczestników w pobliżu do dodania do drużyny!");				
			}
		}
	}
	else
	{
		DeletePVar(playerid, "Ev_NewTeamID");
		PC_EmulateCommand(playerid, "/ev");
	}
	return 1;
}
Dialog:EV_TEAMS(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		SetPVarInt(playerid, "Ev_NewTeamID", strval(inputtext)-1);
		if(event_teams[strval(inputtext)-1][used]==false)
		{
			Dialog_Show(playerid, EV_NEW_TEAM, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Panel Drużyn", "{ffffff}Właśnie tworzysz nową dryżunę!\n\nPoniżej wpisz jej nazwę:", "Stwórz", "Wróć");
		}
		else
		{
			new str[200];
			strcat(str, "Zmień nazwę\n");
			strcat(str, "Usuń dryżynę\n");
			strcat(str, form("Friendly Fire - %s\n", (event_teams[strval(inputtext)-1][friendly_fire]==false) ? ("{ff3333}OFF") : ("{00ff00}ON")));
			strcat(str, "Dodaj do tej drużyny uczestników w pobliżu");
			Dialog_Show(playerid, EV_EDIT_TEAM, DIALOG_STYLE_LIST, "{6666FF}Event{ffffff}Panel - Panel Drużyn", str, "Wybierz", "Wróć");
		}
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_VEH_COL_2(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		CreateEventVehicle(playerid,GetPVarInt(playerid, "EvPan_VEH_SEL_ModelID"),GetPVarInt(playerid, "EvPan_VEH_SEL_Color1"),listitem);
		DeletePVar(playerid, "EvPan_VEH_SEL_ModelID");
		DeletePVar(playerid, "EvPan_VEH_SEL_Color1");
	}
	else
	{
		DeletePVar(playerid, "EvPan_VEH_SEL_ModelID");
		DeletePVar(playerid, "EvPan_VEH_SEL_Color1");
		PC_EmulateCommand(playerid, "/ev");
	}
	return 1;
}
Dialog:EV_VEH_COL_1(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		SetPVarInt(playerid, "EvPan_VEH_SEL_Color1", listitem);
		new str[4096];
		format(str,4096,"Wybierz drugi kolor:\n");
		for(new i=0; i < 256; i++)
		{
			format(str,4096,"%s{%06x}%d III\n",str,RGBAToRGB(VehicleColoursTableRGBA[i]),i);
		}
		Dialog_Show(playerid, EV_VEH_COL_2, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Panel pojazdów", str, "Dalej", "Wróć");
	}
	else
	{
		DeletePVar(playerid, "EvPan_VEH_SEL_ModelID");
		PC_EmulateCommand(playerid, "/ev");
	}
	return 1;
}
Dialog:EV_VEH_SEL_0(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(isnull(inputtext)||!strlen(inputtext)) return Dialog_Show(playerid, EV_VEH_SEL_0, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Panel pojazdów", "{ff3333}Nic nie wpisano!\n\n{ffffff}Wpisz poniżej nazwę pojazdu do zrespienia:", "Spawnuj", "Wróć");
		else
		{
			new finded=0,findmdlid=0,str_more[212],str_rep[100];
			for(new i=0; i < sizeof(VehicleNames); i++)
			{
				if(Find(VehicleNames[i], inputtext,true))
				{
					findmdlid=i+400;
					str_more[finded++]=i+400;
				}
				if(i==sizeof(VehicleNames)-1)
				{
					if(finded==0) return Dialog_Show(playerid, EV_VEH_SEL_0, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Panel pojazdów", "{ff3333}Nie znaleziono takiego pojazdu!\n\n{ffffff}Wpisz poniżej nazwę pojazdu do zrespienia:", "Spawnuj", "Wróć");
					else
					{
						if(finded==1)
						{
							SetPVarInt(playerid, "EvPan_VEH_SEL_ModelID", findmdlid);
							new str[4096];
							format(str,4096,"Wybierz pierwszy kolor:\n");
							for(new c=0; c < 256; c++)
							{
								format(str,4096,"%s{%06x}%d III\n",str,RGBAToRGB(VehicleColoursTableRGBA[c]),c);
							}
							Dialog_Show(playerid, EV_VEH_COL_1, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Panel pojazdów", str, "Dalej", "Wróć");
							return 1;
						}
						if(finded>1)
						{
							format(str_rep,100,"~w~Liczba pojazdow z ~y~%s~w~ w nazwie",inputtext);
							ShowModelSelectionMenuEx(playerid, str_more, finded, str_rep, EV_VEH_SEL_0_1,.Zrot=90.0);
							return 1;
						}
					}
				}
				continue;
			}
		}
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_VEH_SEL_2(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(isnull(inputtext)||!strlen(inputtext)) return Dialog_Show(playerid, EV_VEH_SEL_2, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Panel pojazdów", "{ff3333}Nic nie wpisano!\n\n{ffffff}Wpisz poniżej ModelID:", "Spawnuj", "Wróć");
		else
		{
			if(!isnumeric(inputtext)) return Dialog_Show(playerid, EV_VEH_SEL_2, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Panel pojazdów", "{ff3333}Wpisano zły format!\n\n{ffffff}Wpisz poniżej ModelID:", "Spawnuj", "Wróć");
			else
			{
				if(strval(inputtext)>=400&&strval(inputtext)<=611)
				{
					SetPVarInt(playerid, "EvPan_VEH_SEL_ModelID", strval(inputtext));
					new str[4096];
					format(str,4096,"Wybierz pierwszy kolor:\n");
					for(new i=0; i < 256; i++)
					{
						format(str,4096,"%s{%06x}%d III\n",str,RGBAToRGB(VehicleColoursTableRGBA[i]),i);
					}
					Dialog_Show(playerid, EV_VEH_COL_1, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Panel pojazdów", str, "Dalej", "Wróć");
				}
				else return Dialog_Show(playerid, EV_VEH_SEL_2, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Panel pojazdów", "{ff3333}Wpisano złe ModelID!\n\n{ffffff}Wpisz poniżej ModelID:", "Spawnuj", "Wróć");
			}
		}
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_VEH_SEL(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new str[212];
		switch(listitem)
		{
			case 0://nazwa
			{
				Dialog_Show(playerid, EV_VEH_SEL_0, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Panel pojazdów", "{ffffff}Wpisz poniżej nazwę pojazdu do zrespienia:", "Spawnuj", "Wróć");
			}
			case 1://lista
			{
				for(new i=0; i < sizeof(VehicleNames); i++)
				{
					str[i]=i+400;
					continue;
				}
				ShowModelSelectionMenuEx(playerid, str, sizeof(str), "~w~Wybierz pojazd:", EV_VEH_SEL_1,.Zrot=90.0);
			}
			case 2://mdlid
			{
				Dialog_Show(playerid, EV_VEH_SEL_2, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Panel pojazdów", "{ffffff}Wpisz poniżej ModelID:", "Spawnuj", "Wróć");
			}
		}
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_VEH_DEL_SEL_3(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(isnull(inputtext)||!strlen(inputtext))
		{
			return Dialog_Show(playerid, EV_VEH_DEL_SEL_3, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Panel usuwania pojazdów", "{ff0000}Nic nie wpisano!\n\n{ffffff}Wpisz vehicleid pojazdu:", "Usuń", "Wróć");
		}
		else
		{
			new i = strval(inputtext);
			if(i>0)
			{
				if(!GetVehicleModel(i)) return Dialog_Show(playerid, EV_VEH_DEL_SEL_3, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Panel usuwania pojazdów", "{ff0000}Nie znaleziono pojazdu z takim vehicleid!\n\n{ffffff}Wpisz vehicleid pojazdu:", "Usuń", "Wróć");
				else
				{
					if(pojazd[i][v_event_used]==true)
					{
						DestroyEventVehicle(i);
						AddEventLog(form("%s [ID:%d] usunal/ela pojazd eventowy ID: %d",nick(playerid),playerid,i));
						return SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}usunął/eła pojazd eventowy {ff3333}ID:{ffff00}%d{c0c0c0}!",nick(playerid),playerid,i));
					}
					else return Error(playerid,form("{c0c0c0}Pojazd od vehicleid: {ffffff}%d {c0c0c0}nie jest pojazdem eventowym!",strval(inputtext)));
				}
			}
			else return Dialog_Show(playerid, EV_VEH_DEL_SEL_3, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Panel usuwania pojazdów", "{ff0000}Wpisano złą liczbę!\n\n{ffffff}Wpisz vehicleid pojazdu:", "Usuń", "Wróć");
		}
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_VEH_DEL_SEL(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		switch(listitem)
		{
			case 0://Wszystkie nieużywane
			{
				new ilosc=0;
				for(new i=GetVehiclePoolSize(); i!=0; i--)
				{
					if(pojazd[i][v_event_used]==true)
					{
						if(GetVehicleModel(i)&&IsVehicleEmpty(i))
						{
							DestroyEventVehicle(i);
							ilosc++;
						}
					}
					continue;
				}
				if(ilosc>0)
				{
					AddEventLog(form("%s [ID:%d] usunal/ela %s nieuzywanych pojazdow eventowych",nick(playerid),playerid,ilosc));
					SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}usunął/eła {ffff00}%d{c0c0c0} nieużywanych pojazdów eventowych!",nick(playerid),playerid,ilosc));
				}
				else return Error(playerid,"Nie znaleziono nieużywanych pojazdów!");
			}
			case 1://Wszystkie pojazdy
			{
				new ilosc=0;
				for(new i=GetVehiclePoolSize(); i!=0; i--)
				{
					if(pojazd[i][v_event_used]==true)
					{
						if(GetVehicleModel(i))
						{
							DestroyEventVehicle(i);
							ilosc++;
						}
					}
					continue;
				}
				if(ilosc>0)
				{
					AddEventLog(form("%s [ID:%d] usunal/ela %d pojazdow eventowych!",nick(playerid),playerid,ilosc));
					SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}usunął/eła {ffff00}%d{c0c0c0} pojazdów eventowych!",nick(playerid),playerid,ilosc));
				}
				else return Error(playerid,"Nie znaleziono pojazdów!");
			}
			case 2://Wszystkie stworzone przez Ciebie
			{
				new ilosc=0;
				for(new i=GetVehiclePoolSize(); i!=0; i--)
				{
					if(pojazd[i][v_event_used]==true)
					{
						if(GetVehicleModel(i)&&pojazd[i][v_event_creator_uid]==playerid)
						{
							DestroyEventVehicle(i);
							ilosc++;
						}
					}
					continue;
				}
				if(ilosc>0)
				{
					AddEventLog(form("%s [ID:%d] usunal/ela %d swoich pojazdow eventowych",nick(playerid),playerid,ilosc));
					SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}usunął/eła {ffff00}%d{c0c0c0} swoich pojazdów eventowych!",nick(playerid),playerid,ilosc));
				}
				else return Error(playerid,"Nie znaleziono pojazdów!");
			}
			case 3://Przez vehicleid (/dl)
			{
				Dialog_Show(playerid, EV_VEH_DEL_SEL_3, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Panel usuwania pojazdów", "{ffffff}Wpisz vehicleid pojazdu:", "Usuń", "Wróć");
			}
		}
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_VEH_EDIT_COL_0_2(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(!GetVehicleModel(GetPVarInt(playerid, "EvPan_VEH_LIST_id")))
		{
			Error(playerid,form("Ktoś już usunął pojazd o {ff0000}ID:{ffff00} %d",GetPVarInt(playerid, "EvPan_VEH_LIST_id")));
			DeletePVar(playerid, "EvPan_VEH_LIST_id");
			return 1;
		}
		new i = GetPVarInt(playerid, "EvPan_VEH_LIST_id");
		ChangeVehicleColor(i, GetPVarInt(playerid, "EvPan_VEH_EDIT_Color1"), strval(inputtext));
		pojazd[i][v_color][0]=GetPVarInt(playerid, "EvPan_VEH_EDIT_Color1");
		pojazd[i][v_color][1]=strval(inputtext);
		AddEventLog(form("%s [ID:%d] zmienil kolor1:%d i kolor2:%d w pojedzie ID: %d",nick(playerid),playerid,GetPVarInt(playerid, "EvPan_VEH_EDIT_Color1"),strval(inputtext),i));
		Info(playerid,form("{c0c0c0}Pomyślnie zmieniono {%06x}kolor1 {c0c0c0} i {%06x}kolor2",RGBAToRGB(VehicleColoursTableRGBA[GetPVarInt(playerid, "EvPan_VEH_EDIT_Color1")]),RGBAToRGB(VehicleColoursTableRGBA[strval(inputtext)])));
		DeletePVar(playerid, "EvPan_VEH_EDIT_Color1");
		DeletePVar(playerid, "EvPan_VEH_LIST_id");
	}
	else
	{
		PC_EmulateCommand(playerid, "/ev");
		DeletePVar(playerid, "EvPan_VEH_EDIT_Color1");
		DeletePVar(playerid, "EvPan_VEH_LIST_id");
	}
	return 1;
}
Dialog:EV_VEH_EDIT_COL_0_1(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(!GetVehicleModel(GetPVarInt(playerid, "EvPan_VEH_LIST_id")))
		{
			Error(playerid,form("Ktoś już usunął pojazd o {ff0000}ID:{ffff00} %d",GetPVarInt(playerid, "EvPan_VEH_LIST_id")));
			DeletePVar(playerid, "EvPan_VEH_LIST_id");
			return 1;
		}
		SetPVarInt(playerid, "EvPan_VEH_EDIT_Color1", listitem);
		new str[4096];
		format(str,4096,"Wybierz drugi kolor:\n");
		for(new i=0; i < 256; i++)
		{
			format(str,4096,"%s{%06x}%d III\n",str,RGBAToRGB(VehicleColoursTableRGBA[i]),i);
		}
		Dialog_Show(playerid, EV_VEH_EDIT_COL_0_2, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Zmień kolor pojazdu", str, "Dalej", "Wróć");
	}
	else
	{
		PC_EmulateCommand(playerid, "/ev");
		DeletePVar(playerid, "EvPan_VEH_LIST_id");
	}
	return 1;
}
Dialog:EV_VEH_EDIT_COL_1(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(!GetVehicleModel(GetPVarInt(playerid, "EvPan_VEH_LIST_id")))
		{
			Error(playerid,form("Ktoś już usunął pojazd o {ff0000}ID:{ffff00} %d",GetPVarInt(playerid, "EvPan_VEH_LIST_id")));
			DeletePVar(playerid, "EvPan_VEH_LIST_id");
			return 1;
		}
		new i = GetPVarInt(playerid, "EvPan_VEH_LIST_id");
		ChangeVehicleColor(i, strval(inputtext), pojazd[i][v_color][1]);
		AddEventLog(form("%s [ID:%d] zmienil(a) kolor1:%d w pojezdzie ID:%d",nick(playerid),playerid,strval(inputtext),i));
		pojazd[i][v_color][0]=strval(inputtext);
		Info(playerid,form("{c0c0c0}Pomyślnie zmieniono {%06x}kolor1",RGBAToRGB(VehicleColoursTableRGBA[strval(inputtext)])));
		DeletePVar(playerid, "EvPan_VEH_LIST_id");
	}
	else
	{
		PC_EmulateCommand(playerid, "/ev");
		DeletePVar(playerid, "EvPan_VEH_LIST_id");
	}
	return 1;
}
Dialog:EV_VEH_EDIT_COL_2(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(!GetVehicleModel(GetPVarInt(playerid, "EvPan_VEH_LIST_id")))
		{
			Error(playerid,form("Ktoś już usunął pojazd o {ff0000}ID:{ffff00} %d",GetPVarInt(playerid, "EvPan_VEH_LIST_id")));
			DeletePVar(playerid, "EvPan_VEH_LIST_id");
			return 1;
		}
		new i = GetPVarInt(playerid, "EvPan_VEH_LIST_id");
		ChangeVehicleColor(i, pojazd[i][v_color][0],strval(inputtext));
		AddEventLog(form("%s [ID:%d] zmienil(a) kolor2:%d w pojezdzie ID:%d",nick(playerid),playerid,strval(inputtext),i));
		pojazd[i][v_color][1]=strval(inputtext);
		Info(playerid,form("{c0c0c0}Pomyślnie zmieniono {%06x}kolor2",RGBAToRGB(VehicleColoursTableRGBA[strval(inputtext)])));
		DeletePVar(playerid, "EvPan_VEH_LIST_id");
	}
	else
	{
		PC_EmulateCommand(playerid, "/ev");
		DeletePVar(playerid, "EvPan_VEH_LIST_id");
	}
	return 1;
}
Dialog:EV_VEH_EDIT_COL_SEL(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(!GetVehicleModel(GetPVarInt(playerid, "EvPan_VEH_LIST_id")))
		{
			Error(playerid,form("Ktoś już usunął pojazd o {ff0000}ID:{ffff00} %d",GetPVarInt(playerid, "EvPan_VEH_LIST_id")));
			DeletePVar(playerid, "EvPan_VEH_LIST_id");
			return 1;
		}
		switch(listitem)
		{
			case 0://obydwa kolory
			{
				new str[4096];
				format(str,4096,"Wybierz pierwszy kolor:\n");
				for(new i=0; i < 256; i++)
				{
					format(str,4096,"%s{%06x}%d III\n",str,RGBAToRGB(VehicleColoursTableRGBA[i]),i);
				}
				Dialog_Show(playerid, EV_VEH_EDIT_COL_0_1, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Zmień kolor pojazdu", str, "Dalej", "Wróć");
			}
			case 1://pierwszy
			{
				new str[4096];
				format(str,4096,"Wybierz kolor:\n");
				for(new i=0; i < 256; i++)
				{
					format(str,4096,"%s{%06x}%d III\n",str,RGBAToRGB(VehicleColoursTableRGBA[i]),i);
				}
				Dialog_Show(playerid, EV_VEH_EDIT_COL_1, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Zmień kolor pojazdu", str, "Dalej", "Wróć");
			}
			case 2://drugi
			{
				new str[4096];
				format(str,4096,"Wybierz kolor:\n");
				for(new i=0; i < 256; i++)
				{
					format(str,4096,"%s{%06x}%d III\n",str,RGBAToRGB(VehicleColoursTableRGBA[i]),i);
				}
				Dialog_Show(playerid, EV_VEH_EDIT_COL_2, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Zmień kolor pojazdu", str, "Dalej", "Wróć");
			}
		}
	}
	else
	{
		PC_EmulateCommand(playerid, "/ev");
		DeletePVar(playerid, "EvPan_VEH_LIST_id");
	}
	return 1;
}
Dialog:EV_VEH_EDIT_HP(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(!GetVehicleModel(GetPVarInt(playerid, "EvPan_VEH_LIST_id")))
		{
			Error(playerid,form("Ktoś już usunął pojazd o {ff0000}ID:{ffff00} %d",GetPVarInt(playerid, "EvPan_VEH_LIST_id")));
			DeletePVar(playerid, "EvPan_VEH_LIST_id");
			return 1;
		}
		new i = GetPVarInt(playerid, "EvPan_VEH_LIST_id");
		if(isnull(inputtext)||!strlen(inputtext))
		{
			return Dialog_Show(playerid, EV_VEH_EDIT_HP, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień HP pojazdu", "{ff3333}Nic nie wpisano!\n\n\n{c0c0c0}GodMode: {ffffff}Wpisz GOD\n\n{ffff00}Regułka:\n{ffffff}Poniżej 250 - Pali się (zaraz wybuchnie)\n390-250 - Czarny dym\n550-390 - Siwy dym\n650-550 - Biały dym\nPowyżej 650 - Brak dymu\n\n{ffffff}Wpisz wartość 0-1000 (regułka wyżej) aby ustawić HP:", "Zmień", "Wróć");
		}
		else
		{
			if(!isnumeric(inputtext))
			{
				if(Find(inputtext,"GOD",true))
				{
					if(GetVehicleModel(i))
					{
						pojazd[i][v_event_godmode]=true;
					}
					else
					{
						Error(playerid,form("Ktoś już usunął pojazd o {ff0000}ID:{ffff00} %d",GetPVarInt(playerid, "EvPan_VEH_LIST_id")));
						DeletePVar(playerid, "EvPan_VEH_LIST_id");
						return 1;
					}
					SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}ustawił(a) dla pojazdu eventowego {ff0000}ID: {ffff00}%d{c0c0c0} godmode!",nick(playerid),playerid,i));
					AddEventLog(form("%s [ID:%d] ustawil(a) dla pojazdu (ID:%d) godmode",nick(playerid),playerid,i));
				}
				else
				{
					return Dialog_Show(playerid, EV_VEH_EDIT_HP, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień HP pojazdu", "{ff3333}Wpisano złą wartość! (Nie używaj wartości float)\n\n\n{c0c0c0}GodMode: {ffffff}Wpisz GOD\n\n{ffff00}Regułka:\n{ffffff}Poniżej 250 - Pali się (zaraz wybuchnie)\n390-250 - Czarny dym\n550-390 - Siwy dym\n650-550 - Biały dym\nPowyżej 650 - Brak dymu\n\n{ffffff}Wpisz wartość 0-1000 (regułka wyżej) aby ustawić HP:", "Zmień", "Wróć");
				}
			}
			else
			{
				if(strval(inputtext)>=0&&strval(inputtext)<=1000)
				{
					if(GetVehicleModel(i))
					{
						pojazd[i][v_event_godmode]=false;
						SetVehicleHealth(i, strval(inputtext));
						AddEventLog(form("%s [ID:%d] ustawil(a) HP:%d dla pojazdu ID:%d",nick(playerid),playerid,strval(inputtext),i));
					}
					else
					{
						Error(playerid,form("Ktoś już usunął pojazd o {ff0000}ID:{ffff00} %d",GetPVarInt(playerid, "EvPan_VEH_LIST_id")));
						DeletePVar(playerid, "EvPan_VEH_LIST_id");
						return 1;
					}
					SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}ustawił(a) dla pojazdu eventowego {ff0000}ID:{ffff00} %d{c0c0c0} hp na {ffff00}%d{c0c0c0}!",nick(playerid),playerid,i,strval(inputtext)));
				}
				else
				{
					return Dialog_Show(playerid, EV_VEH_EDIT_HP, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień HP pojazdu", "{ff3333}Wpisano złą wartość! (Nie używaj wartości float)\n\n\n{c0c0c0}GodMode: {ffffff}Wpisz GOD\n\n{ffff00}Regułka:\n{ffffff}Poniżej 250 - Pali się (zaraz wybuchnie)\n390-250 - Czarny dym\n550-390 - Siwy dym\n650-550 - Biały dym\nPowyżej 650 - Brak dymu\n\n{ffffff}Wpisz wartość 0-1000 (regułka wyżej) aby ustawić HP:", "Zmień", "Wróć");
				}
			}
		}
	}
	else
	{
		PC_EmulateCommand(playerid, "/ev");
		DeletePVar(playerid, "EvPan_VEH_LIST_id");
	}
	return 1;
}
Dialog:EV_VEH_TEAM_LIST(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new i = GetPVarInt(playerid, "EvPan_VEH_LIST_id");
		new id = strval(inputtext)-1;
		if(event_teams[id][used]==false)
		{
			Error(playerid,form("Drużyna ID:{ffffff} %d{ff3333} nie jest poprawna!",id));
			PC_EmulateCommand(playerid, "/ev");
			DeletePVar(playerid, "EvPan_VEH_LIST_id");			
		}
		else
		{
			if(pojazd[i][v_event_teamid]!=-1)
			{
				Info(playerid,form("{00ff00}Pomyślnie {c0c0c0}przepisano pojazd {ff0000}ID:{ffff00} %d {c0c0c0}z dryżyny {ffffff} %s {c0c0c0}do drużyny {ffffff}%s",i,event_teams[pojazd[i][v_event_teamid]][team_name],event_teams[id][team_name]));
				AddEventLog(form("%s [ID:%d] przepisal(a) pojazd ID:%d z druzyny %s do druzyny %s",nick(playerid),playerid,i,event_teams[pojazd[i][v_event_teamid]][team_name],event_teams[id][team_name]));
			}
			else
			{
				Info(playerid,form("{00ff00}Pomyślnie{c0c0c0} dopisano pojazd {ff0000}ID:{ffff00} %d {c0c0c0}do drużyny {ffffff}%s",i,event_teams[id][team_name]));
				AddEventLog(form("%s [ID:%d] dopisal(a) pojazd ID:%d do druzyny %s",nick(playerid),playerid,i,event_teams[id][team_name]));
			}
			pojazd[i][v_event_teamid]=id;
			PC_EmulateCommand(playerid, "/ev");
			DeletePVar(playerid, "EvPan_VEH_LIST_id");
		}
	}
	else
	{
		PC_EmulateCommand(playerid, "/ev");
		DeletePVar(playerid, "EvPan_VEH_LIST_id");
	}
	return 1;
}
Dialog:EV_VEH_TEAM_SEL(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new i = GetPVarInt(playerid, "EvPan_VEH_LIST_id");
		switch(listitem)
		{
			case 0://dodaj
			{
				new str[3000];
				format(str, 3000, "{ffffff}ID\tNazwa\tLiczba pojazdów\n");
				for(new ii=0; ii < MAX_EVENT_TEAMS; ii++)
				{
					if(event_teams[ii][used]==false)
					{
						format(str, 3000, "%s{ffffff}%d\tWolny Slot\t---\n", str,ii+1);
					}
					else
					{
						format(str, 3000, "%s{ffffff}%d\t%s\t%d\n", str,ii+1,event_teams[ii][team_name],GetEventTeamVehicles(ii));
					}
				}
				Dialog_Show(playerid, EV_VEH_TEAM_LIST, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Panel pojazdu w drużynie", str, "Dodaj", "Wróć");
			}
			case 1://usun
			{
				if(pojazd[i][v_event_teamid]==-1)
				{
					Error(playerid,form("Pojazd ID: {ffffff}%d{ff3333} nie należy do żadnej dryżyny!",i));
					DeletePVar(playerid, "EvPan_VEH_LIST_id");
					return 1;
				}
				else
				{
					Info(playerid,form("{c0c0c0}Usunięto pojazd {ff0000}ID:{ffff00} %d{c0c0c0} z drużyny {ffff00}%s{c0c0c0}!",i,event_teams[pojazd[i][v_event_teamid]][team_name]));
					AddEventLog(form("%s [ID:%d] usunal/ela pojazd ID:%d z druzyny %s",nick(playerid),playerid,i,event_teams[pojazd[i][v_event_teamid]][team_name]));
					pojazd[i][v_event_teamid]=-1;
				}
			}
		}
	}
	else
	{
		PC_EmulateCommand(playerid, "/ev");
		DeletePVar(playerid, "EvPan_VEH_LIST_id");
	}
	return 1;
}
Dialog:EV_VEH_LIST_GO(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new i = GetPVarInt(playerid, "EvPan_VEH_LIST_id");
		new str[3000];
		switch(listitem)
		{
			case 0://Respawnuj pojazd
			{
				Handbrake(i, 0);
				SetVehicleToRespawn(i);
				DeletePVar(playerid, "EvPan_VEH_LIST_id");
			}
			case 1://Ustaw spawn w aktualnej pozycji
			{
				SaveEventVehiclePosToRespawn(i);
				DeletePVar(playerid, "EvPan_VEH_LIST_id");
			}
			case 2://Drużyny - Dodawanie/Usuwanie pojazdu z drużyny\n
			{
				strcat(str, "Dodaj do drużyny\n");
				strcat(str, "Usuń z drużyny");
				Dialog_Show(playerid, EV_VEH_TEAM_SEL, DIALOG_STYLE_LIST, "{6666FF}Event{ffffff}Panel - Panel pojazdu w drużynie", str, "Dalej", "Wróć");
			}
			case 3://Zaciągnij/Spuść ręczny w pojeździe
			{
				if(pojazd[i][v_handbrake]!=0)
				{
					Handbrake(i, E_HANDBRAKE_OFF);
					Info(playerid,"{c0c0c0}Ręczny spuszczony!");
					AddEventLog(form("%s [ID:%d] spuscil(a) reczny w pojezdzie ID:%d",nick(playerid),playerid,i));
					return 1;
				}
				else
				{
					Handbrake(i, E_HANDBRAKE_ON);
					Info(playerid,"{c0c0c0}Ręczny zaciągnięty!");
					AddEventLog(form("%s [ID:%d] zaciagnal/ela reczny w pojezdzie ID:%d",nick(playerid),playerid,i));
				}
				DeletePVar(playerid, "EvPan_VEH_LIST_id");
			}
			case 4://Zablokuj/Odblokuj możliwość wsiadania do pojazdu
			{
				new engine, lights, alarm, doors, bonnet, boot, objective;
				GetVehicleParamsEx(i, engine, lights, alarm, doors, bonnet, boot, objective);
				if(doors==1)
				{
					SetVehicleParamsEx(i, engine, lights, alarm, 0, bonnet, boot, objective);
					Info(playerid,"{c0c0c0}Odblokowano możliwość wsiadania!");
					AddEventLog(form("%s [ID:%d] oblokowal(a) mozliwosc wsiadania do pojazdu ID:%d",nick(playerid),playerid,i));
					return 1;
				}
				else
				{
					SetVehicleParamsEx(i, engine, lights, alarm, 1, bonnet, boot, objective);
					Info(playerid,"{c0c0c0}Zablokowano możliwość wsiadania!");
					AddEventLog(form("%s [ID:%d] zablokowal(a) mozliwosc wsiadania do pojazdu ID:%d",nick(playerid),playerid,i));
				}
				DeletePVar(playerid, "EvPan_VEH_LIST_id");
			}
			case 5://Zmień kolor pojazdu
			{
				strcat(str,"Obydwa kolory\n");
				strcat(str, "Pierwszy kolor\n");
				strcat(str, "Drugi kolor");
				Dialog_Show(playerid, EV_VEH_EDIT_COL_SEL, DIALOG_STYLE_LIST, "{6666FF}Event{ffffff}Panel - Zmień kolor pojazdu", str, "Dalej", "Wróć");
			}
			case 6://Zmień HP pojazdu
			{
				Dialog_Show(playerid, EV_VEH_EDIT_HP, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień HP pojazdu", "{c0c0c0}GodMode: {ffffff}Wpisz GOD\n\n{ffff00}Regułka:\n{ffffff}Poniżej 250 - Pali się (zaraz wybuchnie)\n390-250 - Czarny dym\n550-390 - Siwy dym\n650-550 - Biały dym\nPowyżej 650 - Brak dymu\n\n{ffffff}Wpisz wartość 0-1000 (regułka wyżej) aby ustawić HP:", "Zmień", "Wróć");
			}
			case 7://Usuń pojazd
			{
				new mdlid = GetVehicleModel(i);
				DestroyEventVehicle(i);
				Info(playerid,form("{c0c0c0}Usunięto pojazd eventowy {ff3333}ID:{ffff00} %d {c0c0c0}({ffff00}%s{c0c0c0})",i,VehicleNames[mdlid-400]));
				AddEventLog(form("%s [ID:%d] usunal/ela pojazd eventowy ID:%d",nick(playerid),playerid,i));
				DeletePVar(playerid, "EvPan_VEH_LIST_id");
			}
		}
	}
	else
	{
		PC_EmulateCommand(playerid, "/ev");
		DeletePVar(playerid, "EvPan_VEH_LIST_id");
	}
	return 1;
}
Dialog:EV_VEH_LIST(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new str[1500];
		SetPVarInt(playerid, "EvPan_VEH_LIST_id", strval(inputtext));//Pobiera UID pojazdu z pierwszej "kolumny" dialogu: >UID<\t...
		strcat(str, "Respawnuj pojazd\n");
		strcat(str, "Ustaw spawn w aktualnej pozycji\n");
		strcat(str, "Drużyny - Dodawanie/Usuwanie pojazdu z drużyny\n");
		strcat(str, "Zaciągnij/Spuść ręczny w pojeździe\n");
		strcat(str, "Zablokuj/Odblokuj możliwość wsiadania do pojazdu\n");
		strcat(str, "Zmień kolor pojazdu\n");
		strcat(str, "Zmień HP pojazdu\n");
		strcat(str, "Usuń pojazd\n");
		Dialog_Show(playerid, EV_VEH_LIST_GO, DIALOG_STYLE_LIST, "{6666FF}Event{ffffff}Panel - Lista pojazdów", str, "Wybierz", "Wróć");
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_VEH_TUN(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new ilosc=0;
		for(new i=GetVehiclePoolSize();i!=0;i--)
		{
			if(pojazd[i][v_event_used]==true)
			{
				if(GetVehicleModel(i))
				{
					AddVehicleComponent(i, strval(inputtext));
					AddEventLog(form("%s [ID:%d] dodal komponent (tuning) ID: %d do pojazdu ID:%d",nick(playerid),playerid,strval(inputtext),i));
					ilosc++;
				}
			}
			continue;
		}
		if(ilosc==0) return Error(playerid,"Brak pojazdów eventowych!");
		else
		{
			AddEventLog(form("%s [ID:%d] stungingowal(a) %d pojazdow eventowych",nick(playerid),playerid,ilosc));
			Info(playerid,form("{c0c0c0}Stuningowano {ffff00}%d{c0c0c0} pojazdów eventowych!",ilosc));
		}
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_VEH_HP(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(isnull(inputtext)||!strlen(inputtext))
		{
			return Dialog_Show(playerid, EV_VEH_HP, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień HP dla wszystkich pojazdów", "{ff3333}Nic nie wpisano!\n\n\n{c0c0c0}GodMode: {ffffff}Wpisz GOD\n\n{ffff00}Regułka:\n{ffffff}Poniżej 250 - Pali się (zaraz wybuchnie)\n390-250 - Czarny dym\n550-390 - Siwy dym\n650-550 - Biały dym\nPowyżej 650 - Brak dymu\n\n{ffffff}Wpisz wartość 0-1000 (regułka wyżej) aby ustawić HP:", "Zmień", "Wróć");
		}
		else
		{
			if(!isnumeric(inputtext))
			{
				if(Find(inputtext,"GOD",true))
				{
					new ilosc=0;
					for(new i=GetVehiclePoolSize();i!=0;i--)
					{
						if(pojazd[i][v_event_used]==true)
						{
							if(GetVehicleModel(i))
							{
								pojazd[i][v_event_godmode]=true;
								SetVehicleHealth(i, 1000.0);
								AddEventLog(form("%s [ID:%d] ustawil(a) godmode w pojezdzie ID:%d",nick(playerid),playerid,i));
								ilosc++;
							}
						}
						continue;
					}
					if(ilosc==0) return Error(playerid,"Brak pojazdów eventowych!");
					else
					{
						AddEventLog(form("%s [ID:%d] ustawil(a) godmode dla %d pojazdow eventowych",nick(playerid),playerid,ilosc));
						Info(playerid,form("{c0c0c0}Ustawiono dla {ffff00}%d{c0c0c0} pojazdów eventowych godmode!",ilosc));
					}
				}
				else
				{
					return Dialog_Show(playerid, EV_VEH_HP, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień HP dla wszystkich pojazdów", "{ff3333}Wpisano złą wartość! (Nie używaj wartości float)\n\n\n{c0c0c0}GodMode: {ffffff}Wpisz GOD\n\n{ffff00}Regułka:\n{ffffff}Poniżej 250 - Pali się (zaraz wybuchnie)\n390-250 - Czarny dym\n550-390 - Siwy dym\n650-550 - Biały dym\nPowyżej 650 - Brak dymu\n\n{ffffff}Wpisz wartość 0-1000 (regułka wyżej) aby ustawić HP:", "Zmień", "Wróć");
				}
			}
			else
			{
				if(strval(inputtext)>=0&&strval(inputtext)<=1000)
				{
					new ilosc=0;
					for(new i=GetVehiclePoolSize(); i!=0; i--)
					{
						if(pojazd[i][v_event_used]==true)
						{
							if(GetVehicleModel(i))
							{
								pojazd[i][v_event_godmode]=false;
								SetVehicleHealth(i, strval(inputtext));
								AddEventLog(form("%s [ID:%d] ustawil(a) HP:%d dla pojazdu ID:%d",nick(playerid),playerid,strval(inputtext),i));
								ilosc++;
							}
						}
						continue;
					}
					if(ilosc==0) return Error(playerid,"Brak pojazdów eventowych!");
					else
					{
						AddEventLog(form("%s [ID:%d] ustawil(a) HP:%d dla %d pojazdow eventowych",nick(playerid),playerid,strval(inputtext),ilosc));
						Info(playerid,form("{c0c0c0}Ustawiono dla {ffff00}%d{c0c0c0} pojazdów eventowych hp na {ffff00}%d{c0c0c0}!",ilosc,strval(inputtext)));
					}
				}
				else
				{
					return Dialog_Show(playerid, EV_VEH_HP, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień HP dla wszystkich pojazdów", "{ff3333}Wpisano złą wartość! (Nie używaj wartości float)\n\n\n{c0c0c0}GodMode: {ffffff}Wpisz GOD\n\n{ffff00}Regułka:\n{ffffff}Poniżej 250 - Pali się (zaraz wybuchnie)\n390-250 - Czarny dym\n550-390 - Siwy dym\n650-550 - Biały dym\nPowyżej 650 - Brak dymu\n\n{ffffff}Wpisz wartość 0-1000 (regułka wyżej) aby ustawić HP:", "Zmień", "Wróć");
				}
			}
		}
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_VEH(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new str[3500];
		switch(listitem)
		{
			case 0://Zespawnuj pojazd
			{
				strcat(str,"Po nazwie\n");
				strcat(str,"Z listy\n");
				strcat(str,"Po ModelID");
				Dialog_Show(playerid, EV_VEH_SEL, DIALOG_STYLE_LIST, "{6666FF}Event{ffffff}Panel - Panel pojazdów", str, "Wybierz", "Wróć");
			}
			case 1://Usuwanie pojazdów
			{
				strcat(str,"Wszystkie nieużywane\n");
				strcat(str,"Wszystkie pojazdy\n");
				strcat(str,"Wszystkie stworzone przez Ciebie\n");
				strcat(str,"Przez vehicleid (/dl)");
				Dialog_Show(playerid, EV_VEH_DEL_SEL, DIALOG_STYLE_LIST, "{6666FF}Event{ffffff}Panel - Panel usuwania pojazdów", str, "Wybierz", "Wróć");
			}
			case 2://Zapisz pozycję wszystkich zrespionych pojazdów
			{
				new ilosc=0;
				for(new i=GetVehiclePoolSize(); i!=0; i--)
				{
					if(pojazd[i][v_event_used]==true)
					{
						if(GetVehicleModel(i))
						{
							SaveEventVehiclePosToRespawn(i);
							ilosc++;
						}
					}
					continue;
				}
				if(ilosc==0) return Error(playerid,"Brak pojazdów eventowych!");
				else
				{
					AddEventLog(form("%s [ID:%d] zapisal(a) pozycje dla %d pojazdow eventowych",nick(playerid),playerid,ilosc));
					Info(playerid,form("{c0c0c0}Zapisano pozycję dla {ffff00}%d{c0c0c0} pojazdów eventowych!",ilosc));
				}
			}
			case 3://Respawnuj pojazdy
			{
				new ilosc=0;
				for(new i=GetVehiclePoolSize(); i!=0; i--)
				{
					if(pojazd[i][v_event_used]==true)
					{
						if(GetVehicleModel(i))
						{
							Handbrake(i, E_HANDBRAKE_OFF);
							SetVehicleToRespawn(i);
							AddEventLog(form("%s [ID:%d] zrespawnowal(a) pojazd ID:%d",nick(playerid),playerid,i));
							ilosc++;
						}
					}
					continue;
				}
				if(ilosc==0) return Error(playerid,"Brak pojazdów eventowych!");
				else
				{
					AddEventLog(form("%s [ID:%d] zrespawnowal(a) %d pojazdow eventowych",nick(playerid),playerid,ilosc));
					SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}zrespawnował(a) {ffff00}%d{c0c0c0} pojazdów eventowych!",nick(playerid),playerid,ilosc));
				}
			}
			case 4://Zaciągnij ręczny w pojazdach
			{
				new ilosc=0;
				for(new i=GetVehiclePoolSize(); i!=0; i--)
				{
					if(pojazd[i][v_event_used]==true)
					{
						if(GetVehicleModel(i))
						{
							Handbrake(i, E_HANDBRAKE_ON);
							AddEventLog(form("%s [ID:%d] zaciagnal/ela reczny w pojezdzie ID:%d",nick(playerid),playerid,i));
							ilosc++;
						}
					}
					continue;
				}
				if(ilosc==0) return Error(playerid,"Brak pojazdów eventowych!");
				else
				{
					AddEventLog(form("%s [ID:%d] zaciagnal/ela reczny w %d pojazdach eventowych",nick(playerid),playerid,ilosc));
					SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}zaciągnął/eła ręczny w {ffff00}%d{c0c0c0} pojazdach eventowych!",nick(playerid),playerid,ilosc));
				}
			}
			case 5://Spuść ręczny w pojazdach
			{
				new ilosc=0;
				for(new i=GetVehiclePoolSize(); i!=0; i--)
				{
					if(pojazd[i][v_event_used]==true)
					{
						if(GetVehicleModel(i))
						{
							Handbrake(i, E_HANDBRAKE_OFF);
							AddEventLog(form("%s [ID:%d] spuscil(a) reczny w pojezdzie ID:%d",nick(playerid),playerid,i));
							ilosc++;
						}
					}
					continue;
				}
				if(ilosc==0) return Error(playerid,"Brak pojazdów eventowych!");
				else
				{
					AddEventLog(form("%s [ID:%d] spuscil(a) reczny w %d pojazdach eventowych",nick(playerid),playerid,ilosc));
					SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}spuścił(a) ręczny w {ffff00}%d{c0c0c0} pojazdach eventowych!",nick(playerid),playerid,ilosc));
				}
			}
			case 6://Lista pojazdów
			{
				new ilosc=0;
				format(str,3500,"{ffffff}ID\t{ffffff}Nazwa\t{ffffff}Kolory (1,2) | VirtualWorld - Interior\t{ffffff}Drużyna\n");
				for(new i=GetVehiclePoolSize(); i!=0; i--)
				{
					if(pojazd[i][v_event_used]==true)
					{
						if(GetVehicleModel(i))
						{
							new str_used[50];
							if(pojazd[i][v_event_teamid]!=-1) format(str_used,50,"%s (%d)",event_teams[pojazd[i][v_event_teamid]][team_name],pojazd[i][v_event_teamid]+1);
							else format(str_used,50,"---");
							format(str,3500,"%s{ffffff}%d\t{ffff00}%s\t{ffffff}%d,%d | %d - %d\t%s\n",str,i,VehicleNames[GetVehicleModel(i)-400],pojazd[i][v_color][0],pojazd[i][v_color][1],pojazd[i][v_event_virtual_world],pojazd[i][v_event_interior],str_used);
							ilosc++;
						}
					}
					continue;
				}
				if(ilosc==0) return Error(playerid,"Brak pojazdów eventowych!");
				else Dialog_Show(playerid, EV_VEH_LIST, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Lista pojazdów", str, "Wybierz", "Wróć");
			}
			case 7://Tuninguj pojazdy (tylko kola i nitro)
			{
				strcat(str,"CompID\tNazwa\n");
				strcat(str, "1008\tNitro (2x)\n");
				strcat(str, "1009\tNitro (5x)\n");
				strcat(str, "1010\tNitro (10x)\n");
				strcat(str, "1025\tKoła (Offroad)\n");
				strcat(str, "1073\tKoła (Shadow)\n");
				strcat(str, "1074\tKoła (Mega)\n");
				strcat(str, "1075\tKoła (Rimshine)\n");
				strcat(str, "1076\tKoła (Wires)\n");
				strcat(str, "1077\tKoła (Classic)\n");
				strcat(str, "1078\tKoła (Twist)\n");
				strcat(str, "1079\tKoła (Cutter)\n");
				strcat(str, "1080\tKoła (Switch)\n");
				strcat(str, "1081\tKoła (Grove)\n");
				strcat(str, "1082\tKoła (Import)\n");
				strcat(str, "1083\tKoła (Dollar)\n");
				strcat(str, "1084\tKoła (Trance)\n");
				strcat(str, "1085\tKoła (Atomic)\n");
				strcat(str, "1096\tKoła (Ahab)\n");
				strcat(str, "1097\tKoła (Virtual)\n");
				strcat(str, "1098\tKoła (Access)");
				Dialog_Show(playerid, EV_VEH_TUN, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Tuninguj pojazdy (tylko kola i nitro)", str, "Dodaj","Wróć");
			}
			case 8://Zmień HP dla wszystkich pojazdów
			{
				Dialog_Show(playerid, EV_VEH_HP, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień HP dla wszystkich pojazdów", "{c0c0c0}GodMode: {ffffff}Wpisz GOD\n\n{ffff00}Regułka:\n{ffffff}Poniżej 250 - Pali się (zaraz wybuchnie)\n390-250 - Czarny dym\n550-390 - Siwy dym\n650-550 - Biały dym\nPowyżej 650 - Brak dymu\n\n{ffffff}Wpisz wartość 0-1000 (regułka wyżej) aby ustawić HP:", "Zmień", "Wróć");
			}
			case 9://Napraw wszystkie pojazdy (Karoseria i HP)
			{
				new ilosc=0;
				for(new i=GetVehiclePoolSize(); i!=0; i--)
				{
					if(pojazd[i][v_event_used]==true)
					{
						if(GetVehicleModel(i))
						{
							RepairVehicle(i);
							if(pojazd[i][v_event_godmode]==true) SetVehicleHealth(i, 1000.0);
							AddEventLog(form("%s [ID:%d] naprawil(a) pojazd ID:%d",nick(playerid),playerid,i));
							ilosc++;
						}
					}
					continue;
				}
				if(ilosc==0) return Error(playerid,"Brak pojazdów eventowych!");
				else
				{
					AddEventLog(form("%s [ID:%d] naprawil(a) %d pojazdow eventowych",nick(playerid),playerid,ilosc));
					SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}naprawił(a) {ffff00}%d{c0c0c0} pojazdów eventowych!",nick(playerid),playerid,ilosc));
				}
			}
			case 10://Co zrobić z zniszczonym pojazdem?
			{
				strcat(str,form("%sRespawnuj pojazd (do pozycji spawnu)%s\n",(serwer[event_destroy_or_respawn_veh]==false) ? ("{00ff00}››{ffffff} ") : (""),(serwer[event_destroy_or_respawn_veh]==false) ? (" {00ff00}‹‹{ffffff}") : ("")));
				strcat(str,form("%sZnisz pojazd%s\n",(serwer[event_destroy_or_respawn_veh]==true) ? ("{00ff00}››{ffffff} ") : (""),(serwer[event_destroy_or_respawn_veh]==true) ? (" {00ff00}‹‹{ffffff}") : ("")));
				Dialog_Show(playerid, EV_VEH_RESP_OR_DESTROY, DIALOG_STYLE_LIST, "{6666FF}Event{ffffff}Panel - Co zrobić z zniszczonym pojazdem?", str, "Wybierz", "Wróć");
			}
		}
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_VEH_RESP_OR_DESTROY(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid, "/ev");
	if(listitem == 0)
	{
		if(serwer[event_destroy_or_respawn_veh] == true)
		{
			serwer[event_destroy_or_respawn_veh] = false;
			Info(playerid,"{c0c0c0}Pomyślnie zmieniono opcję na respawnowanie się w pozycji spawnu!");
			return 1;
		}
		else
		{
			PC_EmulateCommand(playerid, "/ev");
			return Error(playerid,"Opcja respawnowania pojazdu po zniszczeniu jest już ustawiona!");
		}
	}
	if(listitem == 1)
	{
		if(serwer[event_destroy_or_respawn_veh] == false)
		{
			serwer[event_destroy_or_respawn_veh] = true;
			Info(playerid,"{c0c0c0}Pomyślnie zmieniono opcję na usuwanie pojazdu z serwera!");
			return 1;
		}
		else
		{
			PC_EmulateCommand(playerid, "/ev");
			return Error(playerid,"Opcja usunięcia pojazdu po zniszczeniu jest już ustawiona!");
		}
	}
	return 1;
}
Dialog:EV_GIVE_SCORE_ALL(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new str[3000];
		new max_kwota = serwer[event_max_added_score]/GetEventUsers(true);
		if(isnull(inputtext)||!strlen(inputtext))
		{
			format(str,3000,"{ff3333}Nic nie wpisano!\n\n{c0c0c0}Liczba uczestników: {ffffff}%d\n{c0c0c0}Maksymalny budżet do rozdania (score):{ffffff} %d\n{c0c0c0}(Systemowe) Wyliczenie liczby do rozdania:{ffffff} %d\n\n{ffffff}Wpisz poniżej ilość do rozdania:",GetEventUsers(true),serwer[event_max_added_score],max_kwota);
			return Dialog_Show(playerid, EV_GIVE_SCORE_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - {ffffff}Rozdaj {0099FF}wszystkim{ffffff} uczestnikom score", str, "Rozdaj", "Wróć");
		}
		else
		{
			new kwota = strval(inputtext);
			if(kwota<=0)
			{
				format(str,3000,"{ff3333}Wpisano złą ilość!\n\n{c0c0c0}Liczba uczestników: {ffffff}%d\n{c0c0c0}Maksymalny budżet do rozdania (score):{ffffff} %d\n{c0c0c0}(Systemowe) Wyliczenie liczby do rozdania:{ffffff} %d\n\n{ffffff}Wpisz poniżej ilość do rozdania:",GetEventUsers(true),serwer[event_max_added_score],max_kwota);
				return Dialog_Show(playerid, EV_GIVE_SCORE_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - {ffffff}Rozdaj {0099FF}wszystkim{ffffff} uczestnikom score", str, "Rozdaj", "Wróć");
			}
			if(kwota>max_kwota)
			{
				format(str,3000,"{ff3333}Wpisano zbyt dużą ilość!\n{ffffff}Maksymalna wyliczona kwota: %d\n\n{c0c0c0}Liczba uczestników: {ffffff}%d\n{c0c0c0}Maksymalny budżet do rozdania (score):{ffffff} %d\n{c0c0c0}(Systemowe) Wyliczenie liczby do rozdania:{ffffff} %d\n\n{ffffff}Wpisz poniżej ilość do rozdania:",max_kwota,GetEventUsers(true),serwer[event_max_added_score],max_kwota);
				return Dialog_Show(playerid, EV_GIVE_SCORE_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - {ffffff}Rozdaj {0099FF}wszystkim{ffffff} uczestnikom score", str, "Rozdaj", "Wróć");
			}
			new ilosc=0;
			for(new i=PlayerPoolSize(); i!=-1; i--)
			{
				if(IsPlayerConnected(i)&&gracz[i][event_saved]==true)
				{
					GiveScore(i, kwota);
					Info(i,form("{c0c0c0}Otrzymałeś/aś {ffff00}%d{c0c0c0} score od {696969}%s [ID:%d]",kwota,nick(playerid),playerid));
					AddEventLog(form("%s [ID:%d] dal(a) dla %s [ID:%d] %d score",nick(playerid),playerid,nick(i),i,kwota));
					ilosc++;
				}
				continue;
			}
			new lacznie = kwota*ilosc;
			serwer[event_max_added_score]-=lacznie;
			Info(playerid,form("{00ff00}Pomyślnie{c0c0c0} rozdano łącznie {ffffff}%d{c0c0c0} score. (dla %d uczestników po %d na głowę)",lacznie,ilosc,kwota));
			AddEventLog(form("%s [ID:%d] rozdal(a) dla %d uczestnikow %d score (saldo score eventowego:%d)",nick(playerid),playerid,ilosc,lacznie,serwer[event_max_added_score]));
		}
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_GIVE_SCORE_LOCAL(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new str[3000];
		new max_kwota = serwer[event_max_added_score]/GetEventUsers(true);
		if(isnull(inputtext)||!strlen(inputtext))
		{
			format(str,3000,"{ff3333}Nic nie wpisano!\n\n{c0c0c0}Liczba uczestników: {ffffff}%d\n{c0c0c0}Maksymalny budżet do rozdania (score):{ffffff} %d\n{c0c0c0}(Systemowe) Wyliczenie liczby do rozdania:{ffffff} %d\n\n{ffffff}Wpisz poniżej ilość do rozdania:",GetEventUsers(true),serwer[event_max_added_score],max_kwota);
			return Dialog_Show(playerid, EV_GIVE_SCORE_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - {ffffff}Rozdaj uczestnikom {3333CC}w pobliżu{ffffff} score", str, "Rozdaj", "Wróć");
		}
		else
		{
			new kwota = strval(inputtext);
			if(kwota<=0)
			{
				format(str,3000,"{ff3333}Wpisano złą ilość!\n\n{c0c0c0}Liczba uczestników: {ffffff}%d\n{c0c0c0}Maksymalny budżet do rozdania (score):{ffffff} %d\n{c0c0c0}(Systemowe) Wyliczenie liczby do rozdania:{ffffff} %d\n\n{ffffff}Wpisz poniżej ilość do rozdania:",GetEventUsers(true),serwer[event_max_added_score],max_kwota);
				return Dialog_Show(playerid, EV_GIVE_SCORE_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - {ffffff}Rozdaj uczestnikom {3333CC}w pobliżu{ffffff} score", str, "Rozdaj", "Wróć");
			}
			if(kwota>max_kwota)
			{
				format(str,3000,"{ff3333}Wpisano zbyt dużą ilość!\n{ffffff}Maksymalna wyliczona kwota: %d\n\n{c0c0c0}Liczba uczestników: {ffffff}%d\n{c0c0c0}Maksymalny budżet do rozdania (score):{ffffff} %d\n{c0c0c0}(Systemowe) Wyliczenie liczby do rozdania:{ffffff} %d\n\n{ffffff}Wpisz poniżej ilość do rozdania:",max_kwota,GetEventUsers(true),serwer[event_max_added_score],max_kwota);
				return Dialog_Show(playerid, EV_GIVE_SCORE_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - {ffffff}Rozdaj uczestnikom {3333CC}w pobliżu{ffffff} score", str, "Rozdaj", "Wróć");
			}
			new ilosc=0;
			for(new i=PlayerPoolSize(); i!=-1; i--)
			{
				if(IsPlayerConnected(i)&&gracz[i][event_saved]==true&&EvIsPlayerInRangeOfPlayer(i,EVENT_LOCAL_RANGE,playerid))
				{
					GiveScore(i, kwota);
					Info(i,form("{c0c0c0}Otrzymałeś/aś {ffff00}%d{c0c0c0} score od {696969}%s [ID:%d]",kwota,nick(playerid),playerid));
					AddEventLog(form("%s [ID:%d] dal(a) dla %s [ID:%d] %d score [LOCAL]",nick(playerid),playerid,nick(i),i,kwota));
					ilosc++;
				}
				continue;
			}
			new lacznie = kwota*ilosc;
			serwer[event_max_added_score]-=lacznie;
			Info(playerid,form("{00ff00}Pomyślnie{c0c0c0} rozdano łącznie {ffffff}%d{c0c0c0} score. (dla %d uczestników po %d na głowę)",lacznie,ilosc,kwota));
			AddEventLog(form("%s [ID:%d] rozdal(a) dla %d uczestnikow %d score (saldo score eventowego:%d) [LOCAL]",nick(playerid),playerid,ilosc,lacznie,serwer[event_max_added_score]));
		}
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_GIVE_MONEY_ALL(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new str[3000];
		new max_kwota = serwer[event_max_added_money]/GetEventUsers(true);
		if(isnull(inputtext)||!strlen(inputtext))
		{
			format(str,3000,"{ff3333}Nic nie wpisano!\n\n{c0c0c0}Liczba uczestników: {ffffff}%d\n{c0c0c0}Maksymalny budżet do rozdania (kasa):{ffffff} %d\n{c0c0c0}(Systemowe) Wyliczenie liczby do rozdania:{ffffff} %d\n\n{ffffff}Wpisz poniżej ilość do rozdania:",GetEventUsers(true),serwer[event_max_added_money],max_kwota);
			return Dialog_Show(playerid, EV_GIVE_MONEY_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - {ffffff}Rozdaj {0099FF}wszystkim{ffffff} uczestnikom kase", str, "Rozdaj", "Wróć");
		}
		else
		{
			new kwota = strval(inputtext);
			if(kwota<=0)
			{
				format(str,3000,"{ff3333}Wpisano złą ilość!\n\n{c0c0c0}Liczba uczestników: {ffffff}%d\n{c0c0c0}Maksymalny budżet do rozdania (kasa):{ffffff} %d\n{c0c0c0}(Systemowe) Wyliczenie liczby do rozdania:{ffffff} %d\n\n{ffffff}Wpisz poniżej ilość do rozdania:",GetEventUsers(true),serwer[event_max_added_money],max_kwota);
				return Dialog_Show(playerid, EV_GIVE_MONEY_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - {ffffff}Rozdaj {0099FF}wszystkim{ffffff} uczestnikom kase", str, "Rozdaj", "Wróć");
			}
			if(kwota>max_kwota)
			{
				format(str,3000,"{ff3333}Wpisano zbyt dużą ilość!\n{ffffff}Maksymalna wyliczona kwota: %d\n\n{c0c0c0}Liczba uczestników: {ffffff}%d\n{c0c0c0}Maksymalny budżet do rozdania (kasa):{ffffff} %d\n{c0c0c0}(Systemowe) Wyliczenie liczby do rozdania:{ffffff} %d\n\n{ffffff}Wpisz poniżej ilość do rozdania:",max_kwota,GetEventUsers(true),serwer[event_max_added_money],max_kwota);
				return Dialog_Show(playerid, EV_GIVE_MONEY_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - {ffffff}Rozdaj {0099FF}wszystkim{ffffff} uczestnikom kase", str, "Rozdaj", "Wróć");
			}
			new ilosc=0;
			for(new i=PlayerPoolSize(); i!=-1; i--)
			{
				if(IsPlayerConnected(i)&&gracz[i][event_saved]==true)
				{
					GiveMoney(i,kwota);
					Info(i,form("{c0c0c0}Otrzymałeś/aś {ffff00}%d{c0c0c0} kasy od {696969}%s [ID:%d]",kwota,nick(playerid),playerid));
					AddEventLog(form("%s [ID:%d] dal(a) dla %s [ID:%d] %d kasy",nick(playerid),playerid,nick(i),i,kwota));
					ilosc++;
				}
				continue;
			}
			new lacznie = kwota*ilosc;
			serwer[event_max_added_money]-=lacznie;
			Info(playerid,form("{00ff00}Pomyślnie{c0c0c0} rozdano łącznie {ffffff}$%d{c0c0c0}. (dla %d uczestników po %d na głowę)",lacznie,ilosc,kwota));
			AddEventLog(form("%s [ID:%d] rozdal(a) dla %d uczestnikow %d kasy (saldo kasy eventowego:%d)",nick(playerid),playerid,ilosc,lacznie,serwer[event_max_added_money]));
		}
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_GIVE_MONEY_LOCAL(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new str[3000];
		new max_kwota = serwer[event_max_added_money]/GetEventUsers(true);
		if(isnull(inputtext)||!strlen(inputtext))
		{
			format(str,3000,"{ff3333}Nic nie wpisano!\n\n{c0c0c0}Liczba uczestników: {ffffff}%d\n{c0c0c0}Maksymalny budżet do rozdania (kasa):{ffffff} %d\n{c0c0c0}(Systemowe) Wyliczenie liczby do rozdania:{ffffff} %d\n\n{ffffff}Wpisz poniżej ilość do rozdania:",GetEventUsers(true),serwer[event_max_added_money],(serwer[event_max_added_money]/GetEventUsers()));
			return Dialog_Show(playerid, EV_GIVE_MONEY_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - {ffffff}Rozdaj uczestnikom {3333CC}w pobliżu{ffffff} kase", str, "Rozdaj", "Wróć");
		}
		else
		{
			new kwota = strval(inputtext);
			if(kwota<=0)
			{
				format(str,3000,"{ff3333}Wpisano złą ilość!\n\n{c0c0c0}Liczba uczestników: {ffffff}%d\n{c0c0c0}Maksymalny budżet do rozdania (kasa):{ffffff} %d\n{c0c0c0}(Systemowe) Wyliczenie liczby do rozdania:{ffffff} %d\n\n{ffffff}Wpisz poniżej ilość do rozdania:",GetEventUsers(true),serwer[event_max_added_money],max_kwota);
				return Dialog_Show(playerid, EV_GIVE_MONEY_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - {ffffff}Rozdaj uczestnikom {3333CC}w pobliżu{ffffff} kase", str, "Rozdaj", "Wróć");
			}
			if(kwota>max_kwota)
			{
				format(str,3000,"{ff3333}Wpisano zbyt dużą ilość!\n{ffffff}Maksymalna wyliczona kwota: %d\n\n{c0c0c0}Liczba uczestników: {ffffff}%d\n{c0c0c0}Maksymalny budżet do rozdania (kasa):{ffffff} %d\n{c0c0c0}(Systemowe) Wyliczenie liczby do rozdania:{ffffff} %d\n\n{ffffff}Wpisz poniżej ilość do rozdania:",max_kwota,GetEventUsers(true),serwer[event_max_added_money],max_kwota);
				return Dialog_Show(playerid, EV_GIVE_MONEY_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - {ffffff}Rozdaj uczestnikom {3333CC}w pobliżu{ffffff} kase", str, "Rozdaj", "Wróć");
			}
			new ilosc=0;
			for(new i=PlayerPoolSize(); i!=-1; i--)
			{
				if(IsPlayerConnected(i)&&gracz[i][event_saved]==true&&EvIsPlayerInRangeOfPlayer(i,EVENT_LOCAL_RANGE,playerid))
				{
					GiveMoney(i,kwota);
					Info(i,form("{c0c0c0}Otrzymałeś/aś {ffff00}%d{c0c0c0} kasy od {696969}%s [ID:%d]",kwota,nick(playerid),playerid));
					AddEventLog(form("%s [ID:%d] dal(a) dla %s [ID:%d] %d kasy [LOCAL]",nick(playerid),playerid,nick(i),i,kwota));
					ilosc++;
				}
				continue;
			}
			new lacznie = kwota*ilosc;
			serwer[event_max_added_money]-=lacznie;
			Info(playerid,form("{00ff00}Pomyślnie{c0c0c0} rozdano łącznie {ffffff}$%d{c0c0c0}. (dla %d uczestników po %d na głowę)",lacznie,ilosc,kwota));
			AddEventLog(form("%s [ID:%d] rozdal(a) dla %d uczestnikow %d kasy (saldo kasy eventowego:%d) [LOCAL]",nick(playerid),playerid,ilosc,lacznie,serwer[event_max_added_money]));
		}
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_GIVE_WEAPONS_ALL_AMMO(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(isnull(inputtext)||!strlen(inputtext)) return Dialog_Show(playerid, EV_GIVE_WEAPONS_ALL_AMMO, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Rozdaj bronie uczestnikom", "{ff0000}Nic nie wpisano!\n\n{c0c0c0}Aby dać nieskończoną ilość wpisz: {ffffff}9999\n\n{ffffff}Wpisz jaką ilość amunicji mają otrzymać?:", "Daj", "Wróć");
		if(!isnumeric(inputtext)) return Dialog_Show(playerid, EV_GIVE_WEAPONS_ALL_AMMO, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Rozdaj bronie uczestnikom", "{ff0000}Wpisano zły format!\n\n{c0c0c0}Aby dać nieskończoną ilość wpisz: {ffffff}9999\n\n{ffffff}Wpisz jaką ilość amunicji mają otrzymać?:", "Daj", "Wróć");
		if(strval(inputtext)<=0) return Dialog_Show(playerid, EV_GIVE_WEAPONS_ALL_AMMO, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Rozdaj bronie uczestnikom", "{ff0000}Wpisano złą wartość!\n\n{c0c0c0}Aby dać nieskończoną ilość wpisz: {ffffff}9999\n\n{ffffff}Wpisz jaką ilość amunicji mają otrzymać?:", "Daj", "Wróć");

		for(new i=PlayerPoolSize(); i!=-1; i--)
		{
			if(!IsPlayerConnected(i)) continue;
			if(gracz[i][event_saved]==false) continue;
			GivePlayerWeapon(i, GetPVarInt(playerid, "EV_GIVE_WEAPONS_ALL_id"), strval(inputtext));
			AddEventLog(form("%s [ID:%d] dal(a) bron dla %s [ID:%d] (ID:%d ammo:%d)",nick(playerid),playerid,nick(i),i,GetPVarInt(playerid, "EV_GIVE_WEAPONS_ALL_id"),strval(inputtext)));
			Info(i,form("{696969}%s [ID:%d]{c0c0c0} dał(a) Ci broń {ffffff}%s{c0c0c0}!",nick(playerid),playerid,WeaponName(GetPVarInt(playerid, "EV_GIVE_WEAPONS_ALL_id"))));
		}
		DeletePVar(playerid, "EV_GIVE_WEAPONS_ALL_id");
	}
	else
	{
		DeletePVar(playerid, "EV_GIVE_WEAPONS_ALL_id");
		PC_EmulateCommand(playerid, "/ev");
	}
	return 1;
}
Dialog:EV_GIVEWEAPONSLOCALAMMO(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(isnull(inputtext)||!strlen(inputtext)) return Dialog_Show(playerid, EV_GIVEWEAPONSLOCALAMMO, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Rozdaj bronie uczestnikom", "{ff0000}Nic nie wpisano!\n\n{c0c0c0}Aby dać nieskończoną ilość wpisz: {ffffff}9999\n\n{ffffff}Wpisz jaką ilość amunicji mają otrzymać?:", "Daj", "Wróć");
		if(!isnumeric(inputtext)) return Dialog_Show(playerid, EV_GIVEWEAPONSLOCALAMMO, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Rozdaj bronie uczestnikom", "{ff0000}Wpisano zły format!\n\n{c0c0c0}Aby dać nieskończoną ilość wpisz: {ffffff}9999\n\n{ffffff}Wpisz jaką ilość amunicji mają otrzymać?:", "Daj", "Wróć");
		if(strval(inputtext)<=0) return Dialog_Show(playerid, EV_GIVEWEAPONSLOCALAMMO, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Rozdaj bronie uczestnikom", "{ff0000}Wpisano złą wartość!\n\n{c0c0c0}Aby dać nieskończoną ilość wpisz: {ffffff}9999\n\n{ffffff}Wpisz jaką ilość amunicji mają otrzymać?:", "Daj", "Wróć");

		for(new i=PlayerPoolSize(); i!=-1; i--)
		{
			if(!IsPlayerConnected(i)) continue;
			if(gracz[i][event_saved]==false) continue;
			if(!EvIsPlayerInRangeOfPlayer(i,EVENT_LOCAL_RANGE,playerid)) continue;
			GivePlayerWeapon(i, GetPVarInt(playerid, "EV_GIVE_WEAPONS_LOCAL_id"), strval(inputtext));
			AddEventLog(form("%s [ID:%d] dal(a) bron dla %s [ID:%d] (ID:%d ammo:%d) [LOCAL]",nick(playerid),playerid,nick(i),i,GetPVarInt(playerid, "EV_GIVE_WEAPONS_LOCAL_id"),strval(inputtext)));
			Info(i,form("{696969}%s [ID:%d]{c0c0c0} dał(a) Ci broń {ffffff}%s{c0c0c0}!",nick(playerid),playerid,WeaponName(GetPVarInt(playerid, "EV_GIVE_WEAPONS_LOCAL_id"))));
		}
		DeletePVar(playerid, "EV_GIVE_WEAPONS_LOCAL_id");
	}
	else
	{
		DeletePVar(playerid, "EV_GIVE_WEAPONS_LOCAL_id");
		PC_EmulateCommand(playerid, "/ev");
	}
	return 1;
}
Dialog:EV_GIVE_WEAPONS_ALL(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		SetPVarInt(playerid, "EV_GIVE_WEAPONS_ALL_id", strval(inputtext));
		Dialog_Show(playerid, EV_GIVE_WEAPONS_ALL_AMMO, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Rozdaj bronie uczestnikom", "{c0c0c0}Aby dać nieskończoną ilość wpisz: {ffffff}9999\n\n{ffffff}Wpisz jaką ilość amunicji mają otrzymać?:", "Daj", "Wróć");
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_GIVE_WEAPONS_LOCAL(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		SetPVarInt(playerid, "EV_GIVE_WEAPONS_LOCAL_id", strval(inputtext));
		Dialog_Show(playerid, EV_GIVEWEAPONSLOCALAMMO, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Rozdaj bronie uczestnikom", "{c0c0c0}Aby dać nieskończoną ilość wpisz: {ffffff}9999\n\n{ffffff}Wpisz jaką ilość amunicji mają otrzymać?:", "Daj", "Wróć");
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_ADD_USER(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		if(GetEventUsers()>=serwer[event_max_users]) return Error(playerid,form("W trakcie dopisywania gracz osiągnięto już maksymalną liczbę uczestników. (%d/%d)",GetEventUsers(),serwer[event_max_users]));
		new id = strval(inputtext);
		PC_EmulateCommand(playerid,form("/ev_uadd %d",id));
	}
	else PC_EmulateCommand(playerid, "/ev");
	return 1;
}
Dialog:EV_STOP_LOCALATE(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid,"/ev");
	new str_end[300];
	format(str_end, 300, "{c0c0c0}Czas trwania: %s", StrSecounds(gettime()-serwer[event_time_start]));
	if(gracz[playerid][event_master]==true)
	{
		serwer[event_started]=false;
		serwer[event_weather_id]=-1;
		serwer[event_hour]=-1;
		if(IsValidDynamicPickup(serwer[event_pickup_id]))
		{
			DestroyDynamicPickup(serwer[event_pickup_id]);
			serwer[event_pickup_id]=-1;
			serwer[event_pickup_pos][0]=0.0;
			serwer[event_pickup_pos][1]=0.0;
			serwer[event_pickup_pos][2]=0.0;
		}
		SendEventMessageToAll(form("{696969}%s [ID:%d]{ff3333} zakończył(a){6666ff} Event{ffffff}! %s",nick(playerid),playerid,str_end));
		for(new i = PlayerPoolSize(); i != -1; i--)
		{
			if(gracz[i][loggedin]==true)
			{
				TextDrawHideForPlayer(i, Event_Info);
				if(gracz[i][event_saved]==true)
				{
					gracz[i][event_saved]=false;
					if(!IsEv_PlayerControllable(i)) Ev_PlayerControllable(i, true);
					if(gracz[i][event_teamid] != -1) gracz[i][event_teamid]=-1;
					if(gracz[i][event_hide_labels] == true) gracz[i][event_hide_labels]=false;
					//Czyszczenie PVarow
					if(gracz[i][event_master] == true)
					{
						DeletePVar(i,"EvPan_VEH_SEL_ModelID");
						DeletePVar(i,"EvP_ClickedID");
						DeletePVar(i,"Ev_NewTeamID");
						DeletePVar(i,"EvPan_VEH_SEL_Color1");
						DeletePVar(i,"EvPan_VEH_EDIT_Color1");
						DeletePVar(i,"EvPan_VEH_LIST_id");
						DeletePVar(i,"EV_GIVE_WEAPONS_ALL_id");
						DeletePVar(i,"EV_GIVE_WEAPONS_LOCAL_id");
					}
					//
					ResetPlayerWeapons(i);
					SetPlayerArmour(i, 0.0);
					SetPlayerHealth(i, 100.0);
					LoadFractionWeapons(i, gracz[i][frakcja]);

					if(listitem==1)
					{
						SetPlayerPos(i, 1098.4006+ExFloatRandom(-2,2),1434.0753+ExFloatRandom(-2,2),12.3712+ExFloatRandom(0,1)); //daj kordy spawnu
						SetPlayerFacingAngle(i, 3.7128+ExFloatRandom(-180,180));
					}
					SetPlayerInterior(i, 0);
					SetPlayerVirtualWorld(i, 0);

					if(gracz[i][event_last_skin_id]!=0) SetPlayerSkin(i, gracz[i][event_last_skin_id]);
					gracz[i][event_last_skin_id]=0;
				}
			}
			continue;
		}
		for(new i=GetVehiclePoolSize(); i!=0; i--)
		{
			if(pojazd[i][v_event_used]==true)
			{
				DestroyEventVehicle(i);
			}
			continue;
		}
		for(new i=0; i < MAX_EVENT_TEAMS; i++)
		{
			event_teams[i][used]=false;
			for(new ii=PlayerPoolSize(); ii!=-1; ii--)
			{
				gracz[ii][event_teamid]=-1;
			}
			format(event_teams[i][team_name],MAX_EVENT_TEAM_NAME,"");
		}
		serwer[event_time_start]=0;
		serwer[event_max_users]=0;
		serwer[event_records_on]=false;
		serwer[event_master_exit_timestamp]=0;
		AddEventLog(form("%s [ID:%d] zakonczyl(a) event!",nick(playerid),playerid));
	}
	return 1;
}
Dialog:EV(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new str[3000];
		switch(listitem)
		{
			case 0://>> Rozpocznij event! << / >> Zakończ event! <<
			{
				if(serwer[event_started]==false)
				{
					format(str,3000,"{c0c0c0}Maksymalna liczba uczestników (slotów serwera): %d\n\n{ffffff}Wpisz ile ma wynosić maksymalna liczba uczestników:",MaxPlayers());
					Dialog_Show(playerid, EV_START_MAX, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Ilość uczestników", str, "{00ff00}START", "Wyjdź");
					return 1;
				}
				else Dialog_Show(playerid, EV_STOP_LOCALATE, DIALOG_STYLE_LIST, "{6666FF}Event{ffffff}Panel - Zakończenie eventu", "Zostaw graczy w aktualnej pozycji\nTeleportuj wszytstkich na spawn", "Zakończ", "Wróć");
			}
			case 1://Lista uczestników
			{
				new str_team[100];

				format(str,3000,"{ffffff}Nick\tID\tRola\tDrużyna\n");
				for(new ev_id = 0; ev_id <= PlayerPoolSize(); ev_id++)
				{
					if(gracz[ev_id][loggedin]==true&&IsPlayerConnected(ev_id))
					{
						new bool:find=false;
						for(new i=0; i < MAX_EVENT_TEAMS; i++)
						{
							if(event_teams[i][used]==true&&gracz[ev_id][event_teamid]==i)
							{
								find=true;
								format(str_team, 100, "{ffffff}%s", event_teams[i][team_name]);
							}
						}
						if(find==false)
						{
							format(str_team, 100, "{ffffff}---");
						}
						if(gracz[ev_id][event_master]==true)
						{
							format(str,3000,"%s{ffffff}%s\t%d\t{ff3333}Założyciel\t%s\n",str,nick(ev_id),ev_id,str_team);
						}
						else if(gracz[ev_id][event_saved]==true)
						{
							format(str,3000,"%s{ffffff}%s\t%d\t{c0c0c0}Uczestnik\t%s\n",str,nick(ev_id),ev_id,str_team);
						}
					}
				}
				Dialog_Show(playerid, EV_USERS, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Lista uczestników", str, "Wybierz", "Wróć");
			}
			case 2://Zapisy
			{
				if(serwer[event_records_on]==false)
				{
					serwer[event_records_on]=true;
					SendEventMessageToAll(form("{696969}%s [ID:%d] {00ff00}właczył(a){ffffff} zapisy na event!",nick(playerid),playerid));
					AddEventLog(form("%s [ID:%d] wlaczyl(a) zapisy!",nick(playerid),playerid));
					return 1;
				}
				else
				{
					serwer[event_records_on]=false;
					TextDrawHideForAll(Event_Info);
					SendEventMessageToAll(form("{696969}%s [ID:%d] {ff3333}wyłaczył(a){ffffff} zapisy na event!",nick(playerid),playerid));
					AddEventLog(form("%s [ID:%d] wylaczyl(a) zapisy!",nick(playerid),playerid));
				}
			}
			case 3://Panel pojazdów
			{
				strcat(str, "Stwórz pojazd {c0c0c0}[/ev_vadd]\n");
				strcat(str, "Usuwanie pojazdów {c0c0c0}[/ev_vdel (vehicleid)]\n");
				strcat(str, "Zapisz pozycję wszystkich zrespionych pojazdów\n");
				strcat(str, "Respawnuj pojazdy\n");
				strcat(str, "Zaciągnij ręczny w pojazdach\n");
				strcat(str, "Spuść ręczny w pojazdach\n");
				strcat(str, "Lista pojazdów\n");
				strcat(str, "Tuninguj pojazdy (tylko kola i nitro)\n");
				strcat(str, "Zmień HP dla wszystkich pojazdów\n");
				strcat(str, "Napraw wszystkie pojazdy (Karoseria i HP)\n");
				strcat(str, "Co zrobić z zniszczonym pojazdem?\n");
				Dialog_Show(playerid, EV_VEH, DIALOG_STYLE_LIST, "{6666FF}Event{ffffff}Panel - Panel pojazdów", str, "Wybierz", "Wróć");
			}
			case 4://Panel {ff3333}No-DM{ffffff}
			{
				if(serwer[event_no_dm_status]==false)
				{
					SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}włączył(a) {ff3333}No-DM{c0c0c0} na evencie!",nick(playerid),playerid));
					AddEventLog(form("%s [ID:%d] wlaczyl(a) No-DM!",nick(playerid),playerid));
					serwer[event_no_dm_status]=true;
					return 1;
				}
				else
				{
					SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}wyłączył(a) {ff3333}No-DM{c0c0c0} na evencie!",nick(playerid),playerid));
					AddEventLog(form("%s [ID:%d] wylaczyl(a) No-DM!",nick(playerid),playerid));
					serwer[event_no_dm_status]=false;
				}
			}
			case 5://Rozdaj WSZYSTKIM uczestnikom score
			{
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można rozdawać nagród gdy zapisy na event są włączone!");
				format(str,3000,"{c0c0c0}Liczba uczestników: {ffffff}%d (+%d masterów)\n{c0c0c0}Maksymalny budżet do rozdania (score):{ffffff} %d\n{c0c0c0}(Systemowe) Wyliczenie liczby do rozdania:{ffffff} %d\n\n{ffffff}Wpisz poniżej ilość do rozdania:",GetEventUsers(),GetEventMasters(),serwer[event_max_added_score],(serwer[event_max_added_score]/GetEventUsers(true)));
				Dialog_Show(playerid, EV_GIVE_SCORE_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - {ffffff}Rozdaj {0099FF}wszystkim{ffffff} uczestnikom score", str, "Rozdaj", "Wróć");
			}
			case 6://Rozdaj uczestnikom W POBLIŻU score
			{
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(GetEventUsersNearPlayer(playerid,true)<=0) return Error(playerid,"Brak uczestników w pobliżu!");
				format(str,3000,"{c0c0c0}Liczba uczestników: {ffffff}%d (+%d masterów)\n{c0c0c0}Maksymalny budżet do rozdania (score):{ffffff} %d\n{c0c0c0}(Systemowe) Wyliczenie liczby do rozdania:{ffffff} %d\n\n{ffffff}Wpisz poniżej ilość do rozdania:",GetEventUsers(),GetEventMasters(),serwer[event_max_added_score],(serwer[event_max_added_score]/GetEventUsers(true)));
				Dialog_Show(playerid, EV_GIVE_SCORE_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - {ffffff}Rozdaj uczestnikom {3333CC}w pobliżu{ffffff} score", str, "Rozdaj", "Wróć");
			}
			case 7://Rozdaj WSZYSTKIM uczestnikom kase
			{
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsers()<=0) return Error(playerid,"Brak uczestników!");
				format(str,3000,"{c0c0c0}Liczba uczestników: {ffffff}%d (+%d masterów)\n{c0c0c0}Maksymalny budżet do rozdania (kasa):{ffffff} %d\n{c0c0c0}(Systemowe) Wyliczenie liczby do rozdania:{ffffff} %d\n\n{ffffff}Wpisz poniżej ilość do rozdania:",GetEventUsers(),GetEventMasters(),serwer[event_max_added_money],(serwer[event_max_added_money]/GetEventUsers(true)));
				Dialog_Show(playerid, EV_GIVE_MONEY_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - {ffffff}Rozdaj {0099FF}wszystkim{ffffff} uczestnikom kase", str, "Rozdaj", "Wróć");
			}
			case 8://Rozdaj uczestnikom W POBLIŻU kase
			{
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(GetEventUsersNearPlayer(playerid,true)<=0) return Error(playerid,"Brak uczestników w pobliżu!");
				format(str,3000,"{c0c0c0}Liczba uczestników: {ffffff}%d (+%d masterów)\n{c0c0c0}Maksymalny budżet do rozdania (kasa):{ffffff} %d\n{c0c0c0}(Systemowe) Wyliczenie liczby do rozdania:{ffffff} %d\n\n{ffffff}Wpisz poniżej ilość do rozdania:",GetEventUsers(),GetEventMasters(),serwer[event_max_added_money],(serwer[event_max_added_money]/GetEventUsers(true)));
				Dialog_Show(playerid, EV_GIVE_MONEY_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - {ffffff}Rozdaj uczestnikom {3333CC}w pobliżu{ffffff} kase", str, "Rozdaj", "Wróć");
			}
			case 9://Zamroź WSZYSTKICH uczetników
			{
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				new ilosc=0;
				for(new i = PlayerPoolSize(); i != -1; i--)
				{
					if(gracz[i][event_saved]==false) continue;
					if(gracz[i][event_master]==true) continue;
					if(!IsEv_PlayerControllable(i)) continue;
					if(i==playerid) continue;
					Ev_PlayerControllable(i,false);
					AddEventLog(form("%s [ID:%d] zamrozil(a) %s [ID:%d]",nick(playerid),playerid,nick(i),i));
					ilosc++;
				}
				if(ilosc>0)
				{
					AddEventLog(form("%s [ID:%d] zamrozil(a) %d uczestnikow",nick(playerid),playerid,ilosc));
					SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}zamroził(a) {ffff00}%d{c0c0c0} uczestników!",nick(playerid),playerid,ilosc));
				}
				else Error(playerid,"Brak uczestników do zamrożenia!");
			}
			case 10://Zamroź uczetników W POBLIŻU
			{
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(GetEventUsersNearPlayer(playerid)<=0) return Error(playerid,"Brak uczestników w pobliżu!");
				new ilosc=0;
				for(new i = PlayerPoolSize(); i != -1; i--)
				{
					if(gracz[i][event_saved]==false) continue;
					if(gracz[i][event_master]==true) continue;
					if(!IsEv_PlayerControllable(i)) continue;
					if(!EvIsPlayerInRangeOfPlayer(playerid,EVENT_LOCAL_RANGE,i)) continue;
					if(i==playerid) continue;
					Ev_PlayerControllable(i,false);
					AddEventLog(form("%s [ID:%d] zamrozil(a) %s [ID:%d] [LOCAL]",nick(playerid),playerid,nick(i),i));
					ilosc++;
				}
				if(ilosc>0)
				{
					AddEventLog(form("%s [ID:%d] zamrozil(a) %d uczestnikow [LOCAL]",nick(playerid),playerid,ilosc));
					SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}zamroził(a) {ffff00}%d{c0c0c0} uczestników!",nick(playerid),playerid,ilosc));
				}
				else Error(playerid,"Brak uczestników do zamrożenia!");
			}
			case 11://Odmroź WSZYSTKICH uczetników
			{
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				new ilosc=0;
				for(new i = PlayerPoolSize(); i != -1; i--)
				{
					if(gracz[i][event_saved]==false) continue;
					if(IsEv_PlayerControllable(i)) continue;
					if(i==playerid) continue;
					Ev_PlayerControllable(i,true);
					AddEventLog(form("%s [ID:%d] odmrozil(a) %s [ID:%d]",nick(playerid),playerid,nick(i),i));
					ilosc++;
				}
				if(ilosc>0)
				{
					AddEventLog(form("%s [ID:%d] odmrozil(a) %d uczestnikow",nick(playerid),playerid,ilosc));
					SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}odmroził(a) {ffff00}%d{c0c0c0} uczestników!",nick(playerid),playerid,ilosc));
				}
				else Error(playerid,"Brak uczetników do odmrożenia!");
			}
			case 12://Odmroź uczetników W POBLIŻU
			{
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(GetEventUsersNearPlayer(playerid,true)<=0) return Error(playerid,"Brak uczestników w pobliżu!");
				new ilosc=0;
				for(new i = PlayerPoolSize(); i != -1; i--)
				{
					if(gracz[i][event_saved]==false) continue;
					if(IsEv_PlayerControllable(i)) continue;
					if(!EvIsPlayerInRangeOfPlayer(playerid,EVENT_LOCAL_RANGE,i)) continue;
					if(i==playerid) continue;
					Ev_PlayerControllable(i,true);
					AddEventLog(form("%s [ID:%d] odmrozil(a) %s [ID:%d] [LOCAL]",nick(playerid),playerid,nick(i),i));
					ilosc++;
				}
				if(ilosc>0)
				{
					AddEventLog(form("%s [ID:%d] odmrozil(a) %d uczestnikow [LOCAL]",nick(playerid),playerid,ilosc));
					SendEventMessage(form("{696969}%s [ID:%d] {c0c0c0}odmroził(a) {ffff00}%d{c0c0c0} uczestników!",nick(playerid),playerid,ilosc));
				}
				else Error(playerid,"Brak uczetników do odmrożenia!");
			}
			case 13://Teleportuj wszystkich uczetników do Siebie
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				new ilosc=0;
				new Float:tp_Pos[3];
				GetPlayerPos(playerid, tp_Pos[0], tp_Pos[1], tp_Pos[2]);
				for(new i=PlayerPoolSize(); i!=-1; i--)
				{
					if(IsPlayerConnected(i)&&gracz[i][loggedin]==true&&gracz[i][event_saved]==true)
					{
						if(playerid==i) continue;
						new bool:freeze=false;
						if(!IsEv_PlayerControllable(i)) freeze=true;
						if(freeze==true) Ev_PlayerControllable(i, true);
						SetPlayerPos(i, tp_Pos[0]+ExFloatRandom(-2.0,2.0), tp_Pos[1]+ExFloatRandom(-2.0,2.0), tp_Pos[2]+ExFloatRandom(0.0,2.0));
						SetPlayerInterior(i, GetPlayerInterior(playerid));
						SetPlayerVirtualWorld(i, GetPlayerVirtualWorld(playerid));
						if(freeze==true) Ev_PlayerControllable(playerid, false);
						AddEventLog(form("%s [ID:%d] teleportowal(a) do siebie %s [ID:%d]",nick(playerid),playerid,nick(i),i));
						ilosc++;
					}
					continue;
				}
				if(ilosc<=0) return Error(playerid,"Brak uczestników!");
				AddEventLog(form("%s [ID:%d] przeteleportowal(a) %d uczestnikow do siebie",nick(playerid),playerid,ilosc));
				Info(playerid,form("{c0c0c0}Przeteleportowano {ffffff}%d{c0c0c0} uczestników!",ilosc));
			}
			case 14://Rozdaj bronie WSZYSTKIM uczestnikom
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				strcat(str, "ID\tNazwa\n");
				for(new i=1; i<=46; i++)
				{
					if(!IsWeaponIsValid(i)) continue;
					format(str, 3000, "%s{ffffff}%d\t%s\n", str,i,WeaponName(i));
				}
				Dialog_Show(playerid, EV_GIVE_WEAPONS_ALL, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Rozdaj bronie uczestnikom", str, "Dalej", "Wróć");
			}
			case 15://Rozdaj bronie uczestnikom W POBLIŻU
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsersNearPlayer(playerid,true)<=0) return Error(playerid,"Brak uczestników w pobliżu!");
				strcat(str, "ID\tNazwa\n");
				for(new i=1; i<=46; i++)
				{
					if(!IsWeaponIsValid(i)) continue;
					format(str, 3000, "%s{ffffff}%d\t%s\n", str,i,WeaponName(i));
				}
				Dialog_Show(playerid, EV_GIVE_WEAPONS_LOCAL, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Rozdaj bronie uczestnikom", str, "Dalej", "Wróć");
			}
			case 16://Wyczyść bronie WSZYSTKIM uczestnikom
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				for(new i=PlayerPoolSize(); i!=-1; i--)
				{
					if(!IsPlayerConnected(i)) continue;
					if(gracz[i][event_saved]==false) continue;
					ResetPlayerWeapons(i);
					LoadFractionWeapons(i, gracz[i][frakcja]);
					Info(i,form("{696969}%s [ID:%d]{c0c0c0} wyczyścił(a) Ci bornie!",nick(playerid),playerid));
					AddEventLog(form("%s [ID:%d] wyczycsil(a) bronie dla %s [ID:%d]",nick(playerid),playerid,nick(i),i));
				}
			}
			case 17://Wyczyść bronie uczestnikom W POBLIŻU
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsersNearPlayer(playerid)<=0) return Error(playerid,"Brak uczestników w pobliżu!");
				for(new i=PlayerPoolSize();i!=-1;i--)
				{
					if(!EvIsPlayerInRangeOfPlayer(playerid,EVENT_LOCAL_RANGE,i)) continue;
					if(!IsPlayerConnected(i)) continue;
					if(gracz[i][event_saved]==false) continue;
					ResetPlayerWeapons(i);
					LoadFractionWeapons(i, gracz[i][frakcja]);
					Info(i,form("{696969}%s [ID:%d]{c0c0c0} wyczyścił(a) Ci bornie!",nick(playerid),playerid));
					AddEventLog(form("%s [ID:%d] wyczyscil(a) bronie dla %s [ID:%d] [LOCAL]",nick(playerid),playerid,nick(i),i));
				}
			}
			case 18://Ulecz wszystkich WSZYSTKIM uczestników
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				new ilosc=0;
				for(new i=PlayerPoolSize(); i!=-1; i--)
				{
					if(!IsPlayerConnected(i)) continue;
					if(gracz[i][event_saved]==false) continue;
					SetPlayerHealth(i, 100.0);
					if(playerid!=i) Info(i,form("{696969}%s [ID:%d]{c0c0c0} zregenerował(a) Ci HP!",nick(playerid),playerid));
					AddEventLog(form("%s [ID:%d] zregenerowal(a) HP dla %s [ID:%d]",nick(playerid),playerid,nick(i),i));
					ilosc++;
				}
				if(ilosc>0)
				{
					AddEventLog(form("%s [ID:%d] zregenerowal(a) HP dla %d uczestnikow",nick(playerid),playerid,ilosc));
					Info(playerid,form("Pomyślnie zregenerowano HP dla {ffff00}%d{ffffff} uczestników!",ilosc));
				}
				else Error(playerid,"Brak uczestników do zregenerowania HP!");
			}
			case 19://Ulecz wszystkich uczestników W POBLIŻU
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsersNearPlayer(playerid,true)<=0) return Error(playerid,"Brak uczestników w pobliżu!");
				new ilosc=0;
				for(new i=PlayerPoolSize();i!=-1;i--)
				{
					if(IsPlayerConnected(i)&&gracz[i][event_saved]==true&&EvIsPlayerInRangeOfPlayer(playerid,EVENT_LOCAL_RANGE,i))
					{
						SetPlayerHealth(i, 100.0);
						if(playerid!=i) Info(i,form("{696969}%s [ID:%d]{c0c0c0} zregenerował(a) Ci HP!",nick(playerid),playerid));
						AddEventLog(form("%s [ID:%d] zregenerowal(a) HP dla %s [ID:%d] [LOCAL]",nick(playerid),playerid,nick(i),i));
						ilosc++;
					}
				}
				if(ilosc>0)
				{
					AddEventLog(form("%s [ID:%d] zregenerowal(a) HP dla %d uczestnikow [LOCAL]",nick(playerid),playerid,ilosc));
					Info(playerid,form("Pomyślnie zregenerowano HP dla {ffff00}%d{ffffff} uczestników w pobliżu!",ilosc));
				}
				else Error(playerid,"Brak uczestników w pobliżu do zregenerowania HP!");
			}
			case 20://Daj/Odnów kamizelkę WSZYSTKIM uczestnikom
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				for(new i=PlayerPoolSize(); i!=-1; i--)
				{
					if(!IsPlayerConnected(i)) continue;
					if(gracz[i][event_saved]==false) continue;
					SetPlayerArmour(i, 100.0);
					Info(i,form("{696969}%s [ID:%d]{c0c0c0} nadał(a)/odnowił(a) Ci kamizelkę!",nick(playerid),playerid));
					AddEventLog(form("%s [ID:%d] dal(a)/odnowil(a) kamizelke dla %s [ID:%d]",nick(playerid),playerid,nick(i),i));
				}
			}
			case 21://Daj/Odnów kamizelkę uczestnikom W POBLIŻU
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsersNearPlayer(playerid,true)<=0) return Error(playerid,"Brak uczestników w pobliżu!");
				for(new i=PlayerPoolSize();i!=-1;i--)
				{
					if(IsPlayerConnected(i)&&gracz[i][event_saved]==true&&EvIsPlayerInRangeOfPlayer(playerid,EVENT_LOCAL_RANGE,i))
					{
						SetPlayerArmour(i, 100.0);
						Info(i,form("{696969}%s [ID:%d]{c0c0c0} nadał(a)/odnowił(a) Ci kamizelkę!",nick(playerid),playerid));
						AddEventLog(form("%s [ID:%d] dal(a)/odnowil(a) kamizelke dla %s [ID:%d] [LOCAL]",nick(playerid),playerid,nick(i),i));
					}
				}
			}
			case 22://Wyczyść kamizelkę WSZYSTKIM uczestnikom
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				for(new i=PlayerPoolSize(); i!=-1; i--)
				{
					if(!IsPlayerConnected(i)) continue;
					if(gracz[i][event_saved]==false) continue;
					SetPlayerArmour(i, 0.0);
					Info(i,form("{696969}%s [ID:%d]{c0c0c0} usunął(a) Ci kamizelkę!",nick(playerid),playerid));
					AddEventLog(form("%s [ID:%d] usunal/ela kamizelke dla %s [ID:%d]",nick(playerid),playerid,nick(i),i));
				}
			}
			case 23://Wyczyść kamizelkę uczestnikom W POBLIŻU
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsersNearPlayer(playerid,true)<=0) return Error(playerid,"Brak uczestników w pobliżu!");
				for(new i=PlayerPoolSize();i!=-1;i--)
				{
					if(IsPlayerConnected(i)&&gracz[i][event_saved]==true&&EvIsPlayerInRangeOfPlayer(playerid,EVENT_LOCAL_RANGE,i))
					{
						SetPlayerArmour(i, 0.0);
						Info(i,form("{696969}%s [ID:%d]{c0c0c0} usunął(a) Ci kamizelkę!",nick(playerid),playerid));
						AddEventLog(form("%s [ID:%d] usunal/ela kamizelke dla %s [ID:%d] [LOCAL]",nick(playerid),playerid,nick(i),i));
					}
				}
			}
			case 24://Ustaw skin WSZYSTKIM uczestnikom
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				new finded=0;
				for(new i=1; i <= 311; i++)
				{
					str[finded++]=i;
				}
				ShowModelSelectionMenuEx(playerid, str, finded, "Wybierz skin:", EV_SELECT_SKIN_ALL);
			}
			case 25://Ustaw skin uczestnikom W POBLIŻU
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsersNearPlayer(playerid,true)<=0) return Error(playerid,"Brak uczestników w pobliżu!");
				new finded=0;
				for(new i=1; i <= 311; i++)
				{
					str[finded++]=i;
				}
				ShowModelSelectionMenuEx(playerid, str, finded, "Wybierz skin:", EV_SELECT_SKIN_LOCAL);
			}
			case 26://Ustaw niewidzialne nicki (oraz na mapie znaczniki) uczestnikom W POBLIŻU
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsersNearPlayer(playerid)<=0) return Error(playerid,"Brak uczestników w pobliżu!");
				new ilosc=0;
				for(new i=PlayerPoolSize();i!=-1;i--)
				{
					if(IsPlayerConnected(i)&&gracz[i][event_saved]==true&&EvIsPlayerInRangeOfPlayer(playerid,EVENT_LOCAL_RANGE,i))
					{
						gracz[i][event_hide_labels]=true;
						ilosc++;
						AddEventLog(form("%s [ID:%d] ukrywa %s [ID:%d] na mapie",nick(playerid),playerid,nick(i),i));
					}
				}
				Info(playerid,"{c0c0c0}Pomyślnie ukryto uczestników w pobliżu!");
				AddEventLog(form("%s [ID:%d] ukryl %d uczestnikow na mapie",nick(playerid),playerid,ilosc));
			}
			case 27://Ustaw widzialne nicki (oraz na mapie znaczniki) uczestnikom W POBLIŻU
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsersNearPlayer(playerid,true)<=0) return Error(playerid,"Brak uczestników w pobliżu!");
				new ilosc=0;
				for(new i=PlayerPoolSize();i!=-1;i--)
				{
					if(IsPlayerConnected(i)&&gracz[i][event_saved]==true&&EvIsPlayerInRangeOfPlayer(playerid,EVENT_LOCAL_RANGE,i))
					{
						gracz[i][event_hide_labels]=false;
						ilosc++;
						AddEventLog(form("%s [ID:%d] odkrywa %s [ID:%d] na mapie",nick(playerid),playerid,nick(i),i));
					}
				}
				Info(playerid,"{c0c0c0}Pomyślnie odkryto uczestników w pobliżu!");
				AddEventLog(form("%s [ID:%d] ukrywa %d uczestnikow na mapie",nick(playerid),playerid,ilosc));
			}
			case 28://Ustaw niewidzialne nicki (oraz na mapie znaczniki) WSZYSTKIM uczestnikom
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				new ilosc=0;
				for(new i=PlayerPoolSize();i!=-1;i--)
				{
					if(IsPlayerConnected(i)&&gracz[i][event_saved]==true)
					{
						gracz[i][event_hide_labels]=true;
						ilosc++;
						AddEventLog(form("%s [ID:%d] ukrywa %s [ID:%d] na mapie",nick(playerid),playerid,nick(i),i));
					}
				}
				Info(playerid,"{c0c0c0}Pomyślnie ukryto uczestników!");
				AddEventLog(form("%s [ID:%d] ukrywa %d uczestnikow na mapie",nick(playerid),playerid,ilosc));
			}
			case 29://Ustaw widzialne nicki (oraz na mapie znaczniki) WSZYSTKIM uczestnikom
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				new ilosc=0;
				for(new i=PlayerPoolSize();i!=-1;i--)
				{
					if(IsPlayerConnected(i)&&gracz[i][event_saved]==true)
					{
						gracz[i][event_hide_labels]=false;
						ilosc++;
						AddEventLog(form("%s [ID:%d] odkrywa %s [ID:%d] na mapie",nick(playerid),playerid,nick(i),i));
					}
				}
				Info(playerid,"{c0c0c0}Pomyślnie odkryto uczestników!");
				AddEventLog(form("%s [ID:%d] odkrywa %d uczestnikow na mapie",nick(playerid),playerid,ilosc));
			}
			case 30://Dopisz do eventu gracza
			{
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsers()>=serwer[event_max_users]) return Error(playerid,form("Osiągnięto już maksymalną liczbę uczestników! (%d/%d)",GetEventUsers(),serwer[event_max_users]));
				strcat(str, "ID\tNick\n");
				new finded=0;
				for(new i=0; i <= PlayerPoolSize(); i++)
				{
					if(!IsPlayerConnected(i)) continue;
					if(gracz[i][loggedin]==false) continue;
					if(gracz[i][event_saved]==true) continue;
					if(gracz[i][event_master]==true) continue;
					format(str,3000,"%s%d\t%s\n",str,i,nick(i));
					finded++;
				}
				if(finded>0)
				{
					Dialog_Show(playerid, EV_ADD_USER, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Dopisz do eventu gracza", str, "Dodaj", "Wróć");
				}
				else return Error(playerid,"Brak graczy do wygenerowania listy!");
			}
			case 31://Zmień VirtualWorld dla WSZYSTKICH uczestników
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				format(str,3000,"{c0c0c0}Twój aktualny VW: {ffffff}%d\n{c0c0c0}Poprawne ID VW: {ffffff}0 - 2147483647\n\n{ffffff}Wpisz poniżej ID VirtualWorldu na jaki chcesz zmienić:",GetPlayerVirtualWorld(playerid));
				Dialog_Show(playerid, EV_VIRTUAL_WORLD_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień VirtualWorld WSZYSTKICH dla uczestników", str, "Zmień", "Wróć");
			}
			case 32://Zmień VirtualWorld dla uczestników W POBLIŻU
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsersNearPlayer(playerid,true)<=0) return Error(playerid,"Brak uczestników w pobliżu!");
				format(str,3000,"{c0c0c0}Twój aktualny VW: {ffffff}%d\n{c0c0c0}Poprawne ID VW: {ffffff}0 - 2147483647\n\n{ffffff}Wpisz poniżej ID VirtualWorldu na jaki chcesz zmienić:",GetPlayerVirtualWorld(playerid));
				Dialog_Show(playerid, EV_VIRTUAL_WORLD_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień VirtualWorld dla uczestników W POBLIŻU", str, "Zmień", "Wróć");
			}
			case 33://Zmień Interior dla WSZYSTKICH uczestników
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				format(str,3000,"{c0c0c0}Twój aktualny Interior: {ffffff}%d\n{c0c0c0}Poprawne ID Interiorów: {ffffff}0 - 256\n\n{ffffff}Wpisz poniżej ID Interioru na jaki chcesz zmienić:",GetPlayerInterior(playerid));
				Dialog_Show(playerid, EV_INTERIOR_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień Interior dla WSZYSTKICH uczestników", str, "Zmień", "Wróć");
			}
			case 34://Zmień Interior dla uczestników W POBLIŻU
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsersNearPlayer(playerid,true)<=0) return Error(playerid,"Brak uczestników w pobliżu!");
				format(str,3000,"{c0c0c0}Twój aktualny Interior: {ffffff}%d\n{c0c0c0}Poprawne ID Interiorów: {ffffff}0 - 256\n\n{ffffff}Wpisz poniżej ID Interioru na jaki chcesz zmienić:",GetPlayerInterior(playerid));
				Dialog_Show(playerid, EV_INTERIOR_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień Interior dla uczestników W POBLIŻU", str, "Zmień", "Wróć");
			}
			case 35://Zregeneruj staminę wszystkim uczestnikom
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				new ilosc=0;
				for(new i=PlayerPoolSize(); i != -1; i--)
				{
					if(!IsPlayerConnected(i)) continue;
					if(gracz[i][loggedin]==false) continue;
					if(gracz[i][event_saved]==false) continue;
					gracz[i][stamina] = 100;
    				HUD_UpdateSTAMINA(i);
    				Info(i,form("{696969}%s [ID:%d]{c0c0c0} zregenerował(a) Ci staminę!",nick(playerid),playerid));
    				AddEventLog(form("%s [ID:%d] zregenerowal stamine dla %s [ID:%d]",nick(playerid),playerid,nick(i),i));
    				ilosc++;
				}
				AddEventLog(form("%s [ID:%d] zregenerowal stamine dla %d uczestnikow",nick(playerid),playerid,ilosc));
			}
			case 36://Zregeneruj staminę uczestnikom w poblizu
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				if(GetEventUsersNearPlayer(playerid,true)<=0) return Error(playerid,"Brak uczestników w pobliżu!");
				new ilosc=0;
				for(new i=PlayerPoolSize(); i != -1; i--)
				{
					if(!IsPlayerConnected(i)) continue;
					if(gracz[i][loggedin]==false) continue;
					if(gracz[i][event_saved]==false) continue;
					if(!EvIsPlayerInRangeOfPlayer(i,EVENT_LOCAL_RANGE,playerid)) continue;
					gracz[i][stamina] = 100;
    				HUD_UpdateSTAMINA(i);
    				Info(i,form("{696969}%s [ID:%d]{c0c0c0} zregenerował(a) Ci staminę!",nick(playerid),playerid));
    				ilosc++;
    				AddEventLog(form("%s [ID:%d] zregenerowal stamine dla %s [ID:%d]",nick(playerid),playerid,nick(i),i));
				}
				AddEventLog(form("%s [ID:%d] zregenerowal stamine dla %d uczestnikow",nick(playerid),playerid,ilosc));
			}
			case 37://Zmień godzinę na evencie
			{
				if(GetEventUsers(true)<=0) return Error(playerid,"Brak uczestników!");
				if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
				format(str,3000,"Wybierz godzinę:\n");
				for(new i=0; i != 24; i++)
				{
					format(str,3000,"%s%02d\n",str,i);
				}
				Dialog_Show(playerid, EV_HOUR, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Zmień godzinę na evencie", str, "Zmień", "Wróć");
			}
			case 38://Zmien pogode
			{
				strcat(str,"{ffffff}Poprawne ID pogody:\n");
				for(new i=0; i != 21; i++)
				{
					format(str,3000,"%s%d\n",str,i);
				}
				Dialog_Show(playerid, EV_WEATHER, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Zmień pogodę", str, "Zmień", "Wróć");
			}
			case 39://Panel drużyn
			{
				format(str, 3000, "{ffffff}ID\tNazwa\tLiczba uczestników\n");
				for(new i=0; i < MAX_EVENT_TEAMS; i++)
				{
					if(event_teams[i][used]==false)
					{
						format(str, 3000, "%s{ffffff}%d\tWolny Slot\t---\n", str,i+1);
					}
					else
					{
						format(str, 3000, "%s{ffffff}%d\t%s\t%d\n", str,i+1,event_teams[i][team_name],GetEventTeamUsers(i));
					}
					continue;
				}
				Dialog_Show(playerid, EV_TEAMS, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Panel drużyn", str, "Edytuj", "Wróć");
			}
			case 40://Odliczanie
			{
				if(serwer[event_sec_odliczanie]==0) Dialog_Show(playerid, EV_ODLICZANIE, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Odliczanie", "{ffffff}Wpisz poniżej czas do odliczenia (w sekundach):", "Odlicz", "Wróć");
				else serwer[event_sec_odliczanie]=0;
			}
			case 41://ogloszenie
			{
				Dialog_Show(playerid, EV_OGLOSZENIE, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Ogłoszenie", "{ffffff}Wpisz treść ogłoszenia:", "Ogłoś", "Wróć");
			}
			case 42://Pickup
			{
				if(!IsValidDynamicPickup(serwer[event_pickup_id])) PC_EmulateCommand(playerid,"/ev_pick d");
				else PC_EmulateCommand(playerid,"/ev_pick u");
			}
			case 43://Niespodzianki
			{
				strcat(str, form("{c0c0c0}Niespodzianki: {ffff00}%d{c0c0c0}/{ff3333}%d\n",GetEventCases(),EVENT_MAX_CASES));
				strcat(str, "Dodaj niespodziankę\n");
				strcat(str, "Usuń niespodziankę");
				Dialog_Show(playerid, EV_CASES, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel - Niespodzianki", str, "Wybierz", "Wróć");
			}
		}
	}
	return 1;
}
Dialog:EV_CASES(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid,"/ev");
	switch(listitem)
	{
		case 0://dodaj
		{
			if(GetEventCases()>=EVENT_MAX_CASES) return Error(playerid,form("Osiągnięto już limit niespodzianek! (%d)",EVENT_MAX_CASES));
			if(serwer[event_cases_daily_count]>=EVENT_MAX_DAILY_CASES) return Error(playerid,form("Osiągnięto już dzienny limit niespodzianek! (%d)",EVENT_MAX_DAILY_CASES));
			ShowModelSelectionMenu(playerid, EV_CASES_ADD_IDS, "Wybierz ModelID:");
		}
		case 1://usun
		{
			Dialog_Show(playerid, EV_CASES_DEL, DIALOG_STYLE_INPUT, "{6666ff}Event{ffffff}Panel - Niespodzianki", "{ffffff}Wpisz poniżej ID niespodzianki:", "Usuń", "Wróć");
		}
	}
	return 1;
}
Dialog:EV_CASES_DEL(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid,"/ev");
	if(!strlen(inputtext)) return Dialog_Show(playerid, EV_CASES_DEL, DIALOG_STYLE_INPUT, "{6666ff}Event{ffffff}Panel - Niespodzianki", "{ff3333}Nic nie wpisano!\n\n{ffffff}Wpisz poniżej ID niespodzianki:", "Usuń", "Wróć");
	if(!isnumeric(inputtext)) return Dialog_Show(playerid, EV_CASES_DEL, DIALOG_STYLE_INPUT, "{6666ff}Event{ffffff}Panel - Niespodzianki", "{ff3333}Wpisano zły format!\n\n{ffffff}Wpisz poniżej ID niespodzianki:", "Usuń", "Wróć");
	if(!IsValidDynamicPickup(serwer[event_case][strval(inputtext)])) return Dialog_Show(playerid, EV_CASES_DEL, DIALOG_STYLE_INPUT, "{6666ff}Event{ffffff}Panel - Niespodzianki", "{ff3333}Nie znaleziono takiej niespodzianki!\n\n{ffffff}Wpisz poniżej ID niespodzianki:", "Usuń", "Wróć");
	PC_EmulateCommand(playerid,form("/ev_niesp u %d",strval(inputtext)));
	return 1;
}
Dialog:EV_OGLOSZENIE(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid,"/ev");
	if(!strlen(inputtext)) return Dialog_Show(playerid, EV_OGLOSZENIE, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Ogłoszenie", "{ff3333}Nic nie wpisano!\n\n{ffffff}Wpisz treść ogłoszenia:", "Ogłoś", "Wróć");
	PC_EmulateCommand(playerid,form("/ev_anno %s",inputtext));
	return 1;
}
Dialog:EV_ODLICZANIE(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid,"/ev");
	if(!strlen(inputtext)) return Dialog_Show(playerid, EV_ODLICZANIE, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Odliczanie", "{ff3333}Nic nie wpisano!\n\n{ffffff}Wpisz poniżej czas do odliczenia (w sekundach):", "Odlicz", "Wróć");
	if(!isnumeric(inputtext)) return Dialog_Show(playerid, EV_ODLICZANIE, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Odliczanie", "{ff3333}Wpisano zły format!\n\n{ffffff}Wpisz poniżej czas do odliczenia (w sekundach):", "Odlicz", "Wróć");
	if(strval(inputtext)>EVENT_MAX_TIMER_TIME) return Dialog_Show(playerid, EV_ODLICZANIE, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Odliczanie", "{ff3333}Wpisano zbyt dużą liczbę!\n\n{c0c0c0}Maksymalna liczba: {ffffff}20\n\n{ffffff}Wpisz poniżej czas do odliczenia (w sekundach):", "Odlicz", "Wróć");
	PC_EmulateCommand(playerid,form("/ev_timer %d",strval(inputtext)));
	return 1;
}
Dialog:EV_HOUR(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid,"/ev");
	serwer[event_hour]=listitem;
	Info(playerid,form("{c0c0c0}Pomyślnie zmieniono godzinę dla uczestników eventu na godzinę {ffff00}%02d:00{c0c0c0}.",listitem));
	AddEventLog(form("%s [ID:%d] zmienil godzine na %02d:00",nick(playerid),playerid,listitem));
	return 1;
}
Dialog:EV_INTERIOR_LOCAL(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid,"/ev");
	new str[1500];
	if(!strlen(inputtext))
	{
		format(str,1500,"{ff3333}Nic nie wpisano!\n\n{c0c0c0}Twój aktualny Interior: {ffffff}%d\n{c0c0c0}Poprawne ID Interiorów: {ffffff}0 - 256\n\n{ffffff}Wpisz poniżej ID Interioru na jaki chcesz zmienić:",GetPlayerInterior(playerid));
		Dialog_Show(playerid, EV_INTERIOR_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień Interior dla uczestników W POBLIŻU", str, "Zmień", "Wróć");
		return 1;
	}
	if(!isnumeric(inputtext))
	{
		format(str,1500,"{ff3333}Wpisano zły format!\n\n{c0c0c0}Twój aktualny Interior: {ffffff}%d\n{c0c0c0}Poprawne ID Interiorów: {ffffff}0 - 256\n\n{ffffff}Wpisz poniżej ID Interioru na jaki chcesz zmienić:",GetPlayerInterior(playerid));
		Dialog_Show(playerid, EV_INTERIOR_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień Interior dla uczestników W POBLIŻU", str, "Zmień", "Wróć");
		return 1;
	}
	new inter_id = strval(inputtext);
	if(inter_id<0)
	{
		format(str,1500,"{ff3333}Wpisano zbyt mały Interior\n\n{c0c0c0}Twój aktualny Interior: {ffffff}%d\n{c0c0c0}Poprawne ID Interiorów: {ffffff}0 - 256\n\n{ffffff}Wpisz poniżej ID Interioru na jaki chcesz zmienić:",GetPlayerInterior(playerid));
		Dialog_Show(playerid, EV_INTERIOR_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień Interior dla uczestników W POBLIŻU", str, "Zmień", "Wróć");
		return 1;
	}
	if(inter_id>256)
	{
		format(str,1500,"{ff3333}Wpisano zbyt duży Interior\n\n{c0c0c0}Twój aktualny Interior: {ffffff}%d\n{c0c0c0}Poprawne ID Interiorów: {ffffff}0 - 256\n\n{ffffff}Wpisz poniżej ID Interioru na jaki chcesz zmienić:",GetPlayerInterior(playerid));
		Dialog_Show(playerid, EV_INTERIOR_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień Interior dla uczestników W POBLIŻU", str, "Zmień", "Wróć");
		return 1;
	}
	new ilosc=0;
	for(new i=PlayerPoolSize(); i!=-1; i--)
	{
		if(!IsPlayerConnected(i)) continue;
		if(gracz[i][event_saved]==false) continue;
		if(!EvIsPlayerInRangeOfPlayer(playerid,EVENT_LOCAL_RANGE,i)) continue;
		SetPlayerInterior(i, inter_id);
		Info(i,form("{696969}%s [ID:%d]{c0c0c0} zmienił(a) Tobie Interior na {ffff00}%d",nick(playerid),playerid,inter_id));
		AddEventLog(form("%s [ID:%d] zmienil interior dla %s [ID:%d] na ID: %d [LOCAL]",nick(playerid),playerid,nick(i),i, inter_id));
		ilosc++;
	}
	if(ilosc>0)
	{
		Info(playerid,form("{c0c0c0}Pomyślnie zmieniono Interior dla {ffff00}%d {c0c0c0}uczestników na ID {ffff00}%d",ilosc,inter_id));
		AddEventLog(form("%s [ID:%d] zmienil interior dla %d uczestnikow na ID: %d [LOCAL]",nick(playerid),playerid,ilosc,inter_id));
	}
	else return Error(playerid,"Brak uczestników do zmiany Interioru!");
	return 1;
}
Dialog:EV_INTERIOR_ALL(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid,"/ev");
	new str[1500];
	if(!strlen(inputtext))
	{
		format(str,1500,"{ff3333}Nic nie wpisano!\n\n{c0c0c0}Twój aktualny Interior: {ffffff}%d\n{c0c0c0}Poprawne ID Interiorów: {ffffff}0 - 256\n\n{ffffff}Wpisz poniżej ID Interioru na jaki chcesz zmienić:",GetPlayerInterior(playerid));
		Dialog_Show(playerid, EV_INTERIOR_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień Interior dla WSZYSTKICH uczestników", str, "Zmień", "Wróć");
		return 1;
	}
	if(!isnumeric(inputtext))
	{
		format(str,1500,"{ff3333}Wpisano zły format!\n\n{c0c0c0}Twój aktualny Interior: {ffffff}%d\n{c0c0c0}Poprawne ID Interiorów: {ffffff}0 - 256\n\n{ffffff}Wpisz poniżej ID Interioru na jaki chcesz zmienić:",GetPlayerInterior(playerid));
		Dialog_Show(playerid, EV_INTERIOR_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień Interior dla WSZYSTKICH uczestników", str, "Zmień", "Wróć");
		return 1;
	}
	new inter_id = strval(inputtext);
	if(inter_id<0)
	{
		format(str,1500,"{ff3333}Wpisano zbyt mały Interior\n\n{c0c0c0}Twój aktualny Interior: {ffffff}%d\n{c0c0c0}Poprawne ID Interiorów: {ffffff}0 - 256\n\n{ffffff}Wpisz poniżej ID Interioru na jaki chcesz zmienić:",GetPlayerInterior(playerid));
		Dialog_Show(playerid, EV_INTERIOR_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień Interior dla WSZYSTKICH uczestników", str, "Zmień", "Wróć");
		return 1;
	}
	if(inter_id>256)
	{
		format(str,1500,"{ff3333}Wpisano zbyt duży Interior\n\n{c0c0c0}Twój aktualny Interior: {ffffff}%d\n{c0c0c0}Poprawne ID Interiorów: {ffffff}0 - 256\n\n{ffffff}Wpisz poniżej ID Interioru na jaki chcesz zmienić:",GetPlayerInterior(playerid));
		Dialog_Show(playerid, EV_INTERIOR_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień Interior dla WSZYSTKICH uczestników", str, "Zmień", "Wróć");
		return 1;
	}
	new ilosc=0;
	for(new i=PlayerPoolSize(); i!=-1; i--)
	{
		if(!IsPlayerConnected(i)) continue;
		if(gracz[i][event_saved]==false) continue;
		SetPlayerInterior(i, inter_id);
		Info(i,form("{696969}%s [ID:%d]{c0c0c0} zmienił(a) Tobie Interior na {ffff00}%d",nick(playerid),playerid,inter_id));
		AddEventLog(form("%s [ID:%d] zmienil interior dla %s [ID:%d] na ID: %d",nick(playerid),playerid,nick(i),i,inter_id));
		ilosc++;
	}
	if(ilosc>0)
	{
		Info(playerid,form("{c0c0c0}Pomyślnie zmieniono Interior dla {ffff00}%d {c0c0c0}uczestników na ID {ffff00}%d",ilosc,inter_id));
		AddEventLog(form("%s [ID:%d] zmienil interior dla %d uczestnikow na ID: %d",nick(playerid),playerid,ilosc,inter_id));
	}
	else return Error(playerid,"Brak uczestników do zmiany Interioru!");
	return 1;
}
Dialog:EV_VIRTUAL_WORLD_ALL(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid,"/ev");
	new str[1500];
	if(!strlen(inputtext))
	{
		format(str,1500,"{ff3333}Nic nie wpisano!\n\n{c0c0c0}Twój aktualny VW: {ffffff}%d\n{c0c0c0}Poprawne ID VW: {ffffff}0 - 2147483647\n\n{ffffff}Wpisz poniżej ID VirtualWorldu na jaki chcesz zmienić:",GetPlayerVirtualWorld(playerid));
		Dialog_Show(playerid, EV_VIRTUAL_WORLD_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień VirtualWorld dla WSZYSTKICH uczestników", str, "Zmień", "Wróć");
		return 1;
	}
	if(!isnumeric(inputtext))
	{
		format(str,1500,"{ff3333}Wpisano zły format!\n\n{c0c0c0}Twój aktualny VW: {ffffff}%d\n{c0c0c0}Poprawne ID VW: {ffffff}0 - 2147483647\n\n{ffffff}Wpisz poniżej ID VirtualWorldu na jaki chcesz zmienić:",GetPlayerVirtualWorld(playerid));
		Dialog_Show(playerid, EV_VIRTUAL_WORLD_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień VirtualWorld dla WSZYSTKICH uczestników", str, "Zmień", "Wróć");
		return 1;
	}
	new vw_id = strval(inputtext);
	if(vw_id<0)
	{
		format(str,1500,"{ff3333}Wpisano zbyt mały VirtualWorld\n\n{c0c0c0}Twój aktualny VW: {ffffff}%d\n{c0c0c0}Poprawne ID VW: {ffffff}0 - 2147483647\n\n{ffffff}Wpisz poniżej ID VirtualWorldu na jaki chcesz zmienić:",GetPlayerVirtualWorld(playerid));
		Dialog_Show(playerid, EV_VIRTUAL_WORLD_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień VirtualWorld dla WSZYSTKICH uczestników", str, "Zmień", "Wróć");
		return 1;
	}
	if(vw_id>2147483647)
	{
		format(str,1500,"{ff3333}Wpisano zbyt duży VirtualWorld\n\n{c0c0c0}Twój aktualny VW: {ffffff}%d\n{c0c0c0}Poprawne ID VW: {ffffff}0 - 2147483647\n\n{ffffff}Wpisz poniżej ID VirtualWorldu na jaki chcesz zmienić:",GetPlayerVirtualWorld(playerid));
		Dialog_Show(playerid, EV_VIRTUAL_WORLD_ALL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień VirtualWorld dla WSZYSTKICH uczestników", str, "Zmień", "Wróć");
		return 1;
	}
	new ilosc=0;
	for(new i=PlayerPoolSize(); i!=-1; i--)
	{
		if(!IsPlayerConnected(i)) continue;
		if(gracz[i][event_saved]==false) continue;
		SetPlayerVirtualWorld(i, vw_id);
		Info(i,form("{696969}%s [ID:%d]{c0c0c0} zmienił(a) Tobie VirtualWorld na {ffff00}%d",nick(playerid),playerid,vw_id));
		AddEventLog(form("%s [ID:%d] zmienil virtualworld dla %s [ID:%d] na ID: %d",nick(playerid),playerid,nick(i),i, vw_id));
		ilosc++;
	}
	if(ilosc>0)
	{
		Info(playerid,form("{c0c0c0}Pomyślnie zmieniono VirtualWorld dla {ffff00}%d {c0c0c0}uczestników na ID {ffff00}%d",ilosc,vw_id));
		AddEventLog(form("%s [ID:%d] zmienil virtualworld dla %d na ID: %d",nick(playerid),playerid,ilosc, vw_id));
	}
	else return Error(playerid,"Brak uczestników do zmiany VirtualWorldu!");
	return 1;
}
Dialog:EV_VIRTUAL_WORLD_LOCAL(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid,"/ev");
	new str[1500];
	if(!strlen(inputtext))
	{
		format(str,1500,"{ff3333}Nic nie wpisano!\n\n{c0c0c0}Twój aktualny VW: {ffffff}%d\n{c0c0c0}Poprawne ID VW: {ffffff}0 - 2147483647\n\n{ffffff}Wpisz poniżej ID VirtualWorldu na jaki chcesz zmienić:",GetPlayerVirtualWorld(playerid));
		Dialog_Show(playerid, EV_VIRTUAL_WORLD_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień VirtualWorld dla uczestników W POBLIŻU", str, "Zmień", "Wróć");
		return 1;
	}
	if(!isnumeric(inputtext))
	{
		format(str,1500,"{ff3333}Wpisano zły format!\n\n{c0c0c0}Twój aktualny VW: {ffffff}%d\n{c0c0c0}Poprawne ID VW: {ffffff}0 - 2147483647\n\n{ffffff}Wpisz poniżej ID VirtualWorldu na jaki chcesz zmienić:",GetPlayerVirtualWorld(playerid));
		Dialog_Show(playerid, EV_VIRTUAL_WORLD_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień VirtualWorld dla uczestników W POBLIŻU", str, "Zmień", "Wróć");
		return 1;
	}
	new vw_id = strval(inputtext);
	if(vw_id<0)
	{
		format(str,1500,"{ff3333}Wpisano zbyt mały VirtualWorld\n\n{c0c0c0}Twój aktualny VW: {ffffff}%d\n{c0c0c0}Poprawne ID VW: {ffffff}0 - 2147483647\n\n{ffffff}Wpisz poniżej ID VirtualWorldu na jaki chcesz zmienić:",GetPlayerVirtualWorld(playerid));
		Dialog_Show(playerid, EV_VIRTUAL_WORLD_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień VirtualWorld dla uczestników W POBLIŻU", str, "Zmień", "Wróć");
		return 1;
	}
	if(vw_id>2147483647)
	{
		format(str,1500,"{ff3333}Wpisano zbyt duży VirtualWorld\n\n{c0c0c0}Twój aktualny VW: {ffffff}%d\n{c0c0c0}Poprawne ID VW: {ffffff}0 - 2147483647\n\n{ffffff}Wpisz poniżej ID VirtualWorldu na jaki chcesz zmienić:",GetPlayerVirtualWorld(playerid));
		Dialog_Show(playerid, EV_VIRTUAL_WORLD_LOCAL, DIALOG_STYLE_INPUT, "{6666FF}Event{ffffff}Panel - Zmień VirtualWorld dla uczestników W POBLIŻU", str, "Zmień", "Wróć");
		return 1;
	}
	new ilosc=0;
	for(new i=PlayerPoolSize(); i!=-1; i--)
	{
		if(!IsPlayerConnected(i)) continue;
		if(gracz[i][event_saved]==false) continue;
		if(!EvIsPlayerInRangeOfPlayer(playerid,EVENT_LOCAL_RANGE,i)) continue;
		SetPlayerVirtualWorld(i, vw_id);
		Info(i,form("{696969}%s [ID:%d]{c0c0c0} zmienił(a) Tobie VirtualWorld na {ffff00}%d",nick(playerid),playerid,vw_id));
		AddEventLog(form("%s [ID:%d] zmienil virtualworld dla %s [ID:%d] na ID: %d [LOCAL]",nick(playerid),playerid,nick(i),i, vw_id));
		ilosc++;
	}
	if(ilosc>0)
	{
		Info(playerid,form("{c0c0c0}Pomyślnie zmieniono VirtualWorld dla {ffff00}%d {c0c0c0}uczestników na ID {ffff00}%d",ilosc,vw_id));
		AddEventLog(form("%s [ID:%d] zmienil virtualworld dla %d na ID: %d [LOCAL]",nick(playerid),playerid,ilosc, vw_id));
	}
	else return Error(playerid,"Brak uczestników do zmiany VirtualWorldu!");
	return 1;
}
Dialog:EV_WEATHER(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid,"/ev");
	serwer[event_weather_id]=listitem;
	SendEventMessage(form("{696969}%s [ID:%d]{c0c0c0} ustawił(a) pogodę na {ff0000}ID:{ffff00} %d",nick(playerid),playerid,listitem));
	AddEventLog(form("%s [ID:%d] zmienil pogode na ID: %d",nick(playerid),playerid,listitem));
	return 1;
}
//
//Komendy - Admin
CMD:ev_master(playerid,params[])
{
	if(gracz[playerid][event_master]==false)
	{
		if(gracz[playerid][admin_duty] < 1) return 0;
		new pass[144];
		if(sscanf(params,"s[144]",pass)) return SendClientMessage(playerid, -1, ""COL_GREY"Użyj: /master [hasło]");
		if(!TheSame(pass,EVENT_MASTER_PASSWORD)) return Error(playerid,"Niepoprawne hasło!");
		gracz[playerid][event_master]=true;
		Info(playerid,"Pomyślnie zalogowano się jako EventMaster!");
		AddEventLog(form("%s [ID:%d] zalogowal(a) sie na Event Mastera!",nick(playerid),playerid));
		return 1;
	}
	else
	{
		gracz[playerid][event_master]=false;
		gracz[playerid][event_saved]=false;
		Info(playerid,"Wylogowano się z EventMaster'a!");
		AddEventLog(form("%s [ID:%d] wylogowal(a) sie z Event Mastera!",nick(playerid),playerid));
	}
	return 1;
}
CMD:ev_cmd(playerid)
{
	if(gracz[playerid][event_master]==false) return Error(playerid,"Brak uprawnień!");
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");

	new str[2000];
	strcat(str,"{ffff00}/ev_cmd {ffffff}> Spis komend eventowych\n");
	strcat(str,"{ffff00}/ev {ffffff}> Panel Eventowy\n");
	strcat(str,"{ffff00}/ev_uadd {ffffff}> Dodawanie uczestników\n");
	strcat(str,"{ffff00}/ev_udel {ffffff}> Usuwanie uczestników\n");
	strcat(str,"{ffff00}/ev_vadd {ffffff}> Dodawanie pojazdów\n");
	strcat(str,"{ffff00}/ev_vdel {ffffff}> Usuwanie pojazdów\n");
	strcat(str,"{ffff00}/ev_anno {ffffff}> Ogłoszenie\n");
	strcat(str,"{ffff00}/ev_timer {ffffff}> Odliczanie\n");
	strcat(str,"{ffff00}/ev_picktpall {ffffff}> Teleportacja wszystkich zapisanych graczy do pickupu\n");
	strcat(str,"{ffff00}/ev_info {ffffff}> Informacja na czacie OOC z wyłączeniem OOC na 10 sekund\n");
	strcat(str,"{ffff00}/ev_usercp {ffffff}> Panel uczestnika\n");
	strcat(str,"{ffff00}/ev_umoney {ffffff}> Dawanie/Usuwanie kasy dla uczestnika\n");
	strcat(str,"{ffff00}/ev_uscore {ffffff}> Dawanie/Usuwanie score dla uczestnika\n");
	strcat(str,"{ffff00}/ev_bank {ffffff}> Sprawdzanie salda eventu\n");
	Dialog_Show(playerid, EV_CMD, DIALOG_STYLE_MSGBOX, "{6666FF}Event{ffffff}Panel - Komendy", str, "Wyjdź", #);
	return 1;
}
CMD:ev_bank(playerid)
{
	if(gracz[playerid][event_master]==false) return Error(playerid,"Brak uprawnień!");
	if(serwer[event_started]==false) return Error(playerid,"Aktualnie nie trwa żaden event!");
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");
	new str[1000];
	format(str, 1000, "{ffffff}Saldo {6666ff}Eventowe{ffffff}:\n\n{c0c0c0}Kasa: {ffff00}%d\n{c0c0c0}Score: {ffff00}%d", serwer[event_max_added_money],serwer[event_max_added_score]);
	Dialog_Show(playerid, EV_BANK, DIALOG_STYLE_MSGBOX, "{6666ff}Event{ffffff}Panel - Saldo", str, "Zamknij",#);
	AddEventLog(form("%s [ID:%d] sprawdza saldo eventowe",nick(playerid),playerid));
	return 1;
}
CMD:ev_umoney(playerid,params[])
{
	if(gracz[playerid][event_master]==false) return Error(playerid,"Brak uprawnień!");
	if(serwer[event_started]==false) return Error(playerid,"Aktualnie nie trwa żaden event!");
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");
	if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");

	new e_id,e_money;
	if(sscanf(params,"ii",e_id,e_money)) return SendClientMessage(playerid, -1, ""COL_GREY"Użyj: /ev_umoney [ID] [Wartość]");

	if(!IsPlayerConnected(e_id)) return Error(playerid,"Gracz o takim ID nie jest połączony z serwerem!");
	if(gracz[e_id][event_saved]==false) return Error(playerid,"Ten gracz nie jest zapisany na event!");
	if(e_money==0) return Error(playerid,"Nie wpisujemy w wartości zera...");
	if(e_money<0 && ((Money(e_id)+e_money)<Money(e_id))) return Error(playerid,"Podano zbyt mała liczbę (ten gracz nie posiada aż tyle kasy)!");
	if(e_money>serwer[event_max_added_money]) return Error(playerid,"Wpisano zbyt dużą liczbę (eventowy bank nie posiada aż takiej ilości)!");
	if(e_money<0)
	{
		Info(e_id,form("{696969}%s [ID:%d] {c0c0c0}usunął/eła Tobie {ffff00}%d {c0c0c0}kasy.",nick(playerid),playerid,e_money));
		Info(playerid,form("{c0c0c0}Usunąłeś/ęłaś dla {696969}%s [ID:%d] {ffff00}%d {c0c0c0}kasy.",nick(e_id),e_id,e_money));
		TakeMoney(e_id,e_money);
	}
	if(e_money>0)
	{
		Info(e_id,form("{696969}%s [ID:%d]{c0c0c0} dodał(a) Tobie {ffff00}%d{c0c0c0} kasy.",nick(playerid),playerid,e_money));
		Info(playerid,form("{c0c0c0}Dodałeś/aś dla {696969}%s [ID:%d] {ffff00}%d {c0c0c0}kasy.",nick(e_id),e_id,e_money));
		GiveMoney(e_id,e_money);
	}
	serwer[event_max_added_money]-=e_money;
	AddEventLog(form("%s [ID:%d] daje/zabiera dla %s [ID:%d] %d kasy (saldo kasy eventu: %d $)",nick(playerid),playerid,nick(e_id),e_id,serwer[event_max_added_money]));
	return 1;
}
CMD:ev_uscore(playerid,params[])
{
	if(gracz[playerid][event_master]==false) return Error(playerid,"Brak uprawnień!");
	if(serwer[event_started]==false) return Error(playerid,"Aktualnie nie trwa żaden event!");
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");
	if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");

	new e_id,e_score;
	if(sscanf(params,"ii",e_id,e_score)) return SendClientMessage(playerid, -1, ""COL_GREY"Użyj: /ev_uscore [ID] [Wartość]");

	if(!IsPlayerConnected(e_id)) return Error(playerid,"Gracz o takim ID nie jest połączony z serwerem!");
	if(gracz[e_id][event_saved]==false) return Error(playerid,"Ten gracz nie jest zapisany na event!");
	if(e_score==0) return Error(playerid,"Nie wpisujemy w wartości zera...");
	if(e_score<0 && ((GetPlayerScore(e_id)+e_score)<GetPlayerScore(e_id))) return Error(playerid,"Podano zbyt mała liczbę (ten gracz nie posiada aż tyle score)!");
	if(e_score>serwer[event_max_added_score]) return Error(playerid,"Wpisano zbyt dużą liczbę (eventowy bank nie posiada aż takiej ilości)!");
	if(e_score<0)
	{
		Info(e_id,form("{696969}%s [ID:%d] {c0c0c0}usunął/eła Tobie {ffff00}%d {c0c0c0}score.",nick(playerid),playerid,e_score));
		Info(playerid,form("{c0c0c0}Usunąłeś/ęłaś dla {696969}%s [ID:%d] {ffff00}%d {c0c0c0}score.",nick(e_id),e_id,e_score));
		TakeMoney(e_id,e_score);
	}
	if(e_score>0)
	{
		Info(e_id,form("{696969}%s [ID:%d]{c0c0c0} dodał(a) Tobie {ffff00}%d{c0c0c0} score.",nick(playerid),playerid,e_score));
		Info(playerid,form("{c0c0c0}Dodałeś/aś dla {696969}%s [ID:%d] {ffff00}%d {c0c0c0}score.",nick(e_id),e_id,e_score));
		GiveMoney(e_id,e_score);
	}
	serwer[event_max_added_score]-=e_score;
	AddEventLog(form("%s [ID:%d] daje/zabiera dla %s [ID:%d] %d score (saldo score eventu: %d $)",nick(playerid),playerid,nick(e_id),e_id,serwer[event_max_added_score]));
	return 1;
}
CMD:ev_usercp(playerid,params[])
{
	if(gracz[playerid][event_master]==false) return Error(playerid,"Brak uprawnień!");
	if(serwer[event_started]==false) return Error(playerid,"Aktualnie nie trwa żaden event!");
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");

	new e_id,str[1500];
	if(sscanf(params,"i",e_id)) return SendClientMessage(playerid, -1, ""COL_GREY"Użyj: /ev_usercp [ID]");
	if(gracz[e_id][event_saved]==false) return Error(playerid,"Ten gracz nie jest zapisany na event!");
	SetPVarInt(playerid, "EvP_ClickedID", e_id);
	strcat(str,"{ff3333}Wyrzuć z eventu {c0c0c0}[/ev_udel]\n");
	strcat(str,"Zmień drużynę\n");
	strcat(str,"Dodaj/Usuń score [/ev_uscore]\n");
	strcat(str,"Dodaj/Usuń kase [/ev_umoney]\n");
	strcat(str,"(Un)Freeze\n");
	strcat(str,"Teleportuj uczestnika do siebie\n");
	strcat(str,"Daj broń\n");
	strcat(str,"Wyczyść bronie\n");
	strcat(str,"Ulecz uczestnika\n");
	strcat(str,"Daj/Odnów kamizelkę uczestnika\n");
	strcat(str,"Wyczyść armor uczestnika\n");
	strcat(str,"Zmień skina uczestnika\n");
	strcat(str,"Ustaw (nie)widzialność uczestnika\n");
	strcat(str,"Zmień interior dla uczestnika\n");
	strcat(str,"Zmień virtualworld dla uczestnika\n");
	Dialog_Show(playerid, EV_USERS_PAN, DIALOG_STYLE_LIST, "{6666FF}Event{ffffff}Panel - Lista uczestników", str, "Wybierz","Wróc");
	return 1;
}
CMD:ev_info(playerid,params[])
{
	if(gracz[playerid][event_master]==false) return Error(playerid,"Brak uprawnień!");
	if(serwer[event_started]==false) return Error(playerid,"Aktualnie nie trwa żaden event!");
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");

	new ev_i[124];
	if(sscanf(params,"s[124]",ev_i)) return SendClientMessage(playerid, -1, ""COL_GREY"Użyj: /ev_info [Treść]");
	if(serwer[block_global_ooc]==false)
	{
		serwer[block_global_ooc]=true;
		SetTimer("Ev_UnLockOOC_Info", 10000, false);
	}
	SendClientMessageToAll(-1, "\n");
	SendClientMessageToAll(-1, "\n");
	SendEventMessage("{ff0000}                                        [WAŻNE]");
	SendEventMessage(form("{757575}%s [ID:%d]{ffffff} {6666ff}»{c0c0c0}»{ffffff} %s",nick(playerid),playerid,ev_i));
	SendEventMessage("{ff0000}                                        [WAŻNE]");
	SendClientMessageToAll(-1, "\n");
	SendClientMessageToAll(-1, "\n");
	AddEventLog(form("%s [ID:%d] wysyla wiadomosc informacyjna o tresci: %s",nick(playerid),playerid,ev_i));
	return 1;
}
CMD:ev_picktpall(playerid)
{
	if(gracz[playerid][event_master]==false) return Error(playerid,"Brak uprawnień!");
	if(serwer[event_started]==false) return Error(playerid,"Aktualnie nie trwa żaden event!");
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");
	if(!IsValidDynamicPickup(serwer[event_pickup_id])) return Error(playerid,"Nie ma do czego teleportować graczy (brak pickupu)!");
	if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
	
	new ilosc=0;
	for(new i=PlayerPoolSize(); i != -1; i--)
	{
		if(!IsPlayerConnected(i)) continue;
		if(gracz[i][prisoner] == 1) continue;
		if(gracz[i][wypadek] > 0 || gracz[i][bw] > 0) continue;
		if(i==playerid) continue;

		new pick_vw,pick_interior;
		pick_vw = Streamer_GetIntData(STREAMER_TYPE_PICKUP, serwer[event_pickup_id], E_STREAMER_WORLD_ID);
		pick_interior = Streamer_GetIntData(STREAMER_TYPE_PICKUP, serwer[event_pickup_id], E_STREAMER_INTERIOR_ID);
		new bool:freeze=false;
		if(!IsEv_PlayerControllable(i)) freeze=true;
		if(freeze==true) Ev_PlayerControllable(i, true);
		SetPlayerPos(i, serwer[event_pickup_pos][0]+ExFloatRandom(-2.0,2.0), serwer[event_pickup_pos][1]+ExFloatRandom(-2.0,2.0), serwer[event_pickup_pos][2]+ExFloatRandom(0.0,2.0));
		SetPlayerVirtualWorld(i, pick_vw);
		SetPlayerInterior(i, pick_interior);
		if(freeze==true) Ev_PlayerControllable(playerid, false);
		Info(i,form("{696969}%s [ID:%d] {c0c0c0}teleportował(a) na event!",nick(playerid),playerid));
		AddEventLog(form("%s [ID:%d] teleportuje %s [ID:%d] do pickupu (Koordynaty:%f, %f, %f)",nick(playerid),playerid,nick(i),i,serwer[event_pickup_pos][0],serwer[event_pickup_pos][1],serwer[event_pickup_pos][2]));
		ilosc++;
	}
	if(ilosc>0)
	{
		Info(playerid,form("Przeteleportowano {ffff00}%d{ffffff} uczestników do pikcupu!",ilosc));
		AddEventLog(form("%s [ID:%d] przeteleportowal %d uczestnikow do pickupu (Koordynaty:%f, %f, %f)",nick(playerid),playerid,ilosc,serwer[event_pickup_pos][0],serwer[event_pickup_pos][1],serwer[event_pickup_pos][2]));
	}
	else Error(playerid,"Brak uczestników do przeteleportowania!");
	return 1;
}
CMD:ev_timer(playerid,params[])
{
	if(gracz[playerid][event_master]==false) return Error(playerid,"Brak uprawnień!");
	if(serwer[event_started]==false) return Error(playerid,"Aktualnie nie trwa żaden event!");
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");

	new time;
	if(sscanf(params, "i", time)) return SendClientMessage(playerid, -1, ""COL_GREY"Użyj: /ev_timer [sekundy]");
	if(time<0) return Error(playerid,"Wpisano zbyt małą liczbę!");
	if(time>EVENT_MAX_TIMER_TIME) return Error(playerid,form("Wpisano zbyt dużą liczbę! (Max.: %d)",EVENT_MAX_TIMER_TIME));
	SendEventMessage(form("{696969}%s [ID:%d]{c0c0c0} rozpoczął/eła odliczanie!",nick(playerid),playerid));
	serwer[event_sec_odliczanie]=time;
	AddEventLog(form("%s [ID:%d] uruchamia odliczanie (czas: %d sekund)",nick(playerid),playerid,time));
	return 1;
}
CMD:ev_anno(playerid,params[])
{
	if(gracz[playerid][event_master]==false) return Error(playerid,"Brak uprawnień!");
	if(serwer[event_started]==false) return Error(playerid,"Aktualnie nie trwa żaden event!");
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");

	new anno[128];
	if(sscanf(params,"s[128]",anno)) return SendClientMessage(playerid, -1, ""COL_GREY"Użyj: /ev_anno [treść]");
	for(new i=PlayerPoolSize(); i != -1; i--)
	{
		if(!IsPlayerConnected(i)) continue;
		if(gracz[i][loggedin]==false) continue;
		if(gracz[i][event_saved]==false) continue;
		GameTextForPlayer(i, form("~w~=~b~~h~~h~EVENT~w~=~n~~w~%s~n~~y~%s",nick(playerid),anno), 10000, 3);
	}
	AddEventLog(form("%s [ID:%d] dal ogloszenie (tresc: %s)",nick(playerid),playerid,anno));
	return 1;
}
CMD:ev_vdel(playerid,params[])
{
	if(gracz[playerid][event_master]==false) return Error(playerid,"Brak uprawnień!");
	if(serwer[event_started]==false) return Error(playerid,"Aktualnie nie trwa żaden event!");
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");
	
	new id;
	if(sscanf(params,"i",id)) return SendClientMessage(playerid, -1, ""COL_GREY"Użyj: /ev_vdel [ID]");
	if(!GetVehicleModel(id)) return Error(playerid,"Pojazd z podanym ID nie istnieje!");
	if(pojazd[id][v_event_used]==false) return Error(playerid,"Pojazd z podanym ID nie jest pojazdem eventowym!");
	DestroyEventVehicle(id);
	AddEventLog(form("%s [ID:%d] usunal/ela pojazd ID: %d",nick(playerid),playerid,id));
	return 1;
}
CMD:ev_vadd(playerid,params[])
{
	if(gracz[playerid][event_master]==false) return Error(playerid,"Brak uprawnień!");
	if(serwer[event_started]==false) return Error(playerid,"Aktualnie nie trwa żaden event!");
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");
	
	new id,str[70],color1,color2;
	if(!sscanf(params,"iii",id,color1,color2))
	{
		if(id<400||id>611) return Error(playerid,"Podane ModelID jest nie poprawne!");
		if(color1<0||color1>255) return Error(playerid,"Podane ID koloru1 jest niepoprawne!");
		if(color2<0||color2>255) return Error(playerid,"Podane ID koloru2 jest niepoprawne!");
		return CreateEventVehicle(playerid,id,color1,color2);
	}
	if(!sscanf(params,"s[70]ii",str,color1,color2))
	{
		if(color1<0||color1>255) return Error(playerid,"Podane ID koloru1 jest niepoprawne!");
		if(color2<0||color2>255) return Error(playerid,"Podane ID koloru2 jest niepoprawne!");
		if(strlen(str)<3) return Error(playerid,"Wpisano zbyt krótką nazwę!");
		for(new i=0; i<sizeof(VehicleNames);i++)
		{
			if(Find(VehicleNames[i],str,true))
			{
				return CreateEventVehicle(playerid,i+400,color1,color2);
			}
		}
		Error(playerid,"Nie znaleziono podanego pojazdu!");
		return 1;
	}
	SendClientMessage(playerid, -1, ""COL_GREY"Użyj: /ev_vadd [ModelID/Nazwa] [Kolor1] [Kolor2]");
	return 1;
}
CMD:ev_uadd(playerid,params[])
{
	if(gracz[playerid][event_master]==false) return Error(playerid,"Brak uprawnień!");
	if(serwer[event_started]==false) return Error(playerid,"Aktualnie nie trwa żaden event!");
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");
	if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
	if(GetEventUsers()>=serwer[event_max_users]) return Error(playerid,form("Osiągnięto już maksymalną liczbę uczestników! (%d/%d)",GetEventUsers(),serwer[event_max_users]));
	
	new id;
	if(sscanf(params,"i",id)) return SendClientMessage(playerid, -1, ""COL_GREY"Użyj: /ev_uadd [ID gracza]");
	if(!IsPlayerConnected(id)) return Error(playerid,form("ID {ffffff}%d{ff3333} jest niepoprawne!"));
	if(gracz[id][loggedin]==false) return Error(playerid,"Gracz nie jest jeszcze zalogowany!");
	if(gracz[id][event_master]==true) return Error(playerid,"Nie można dodawać event masterów!");
	if(gracz[id][event_saved]==true) return Error(playerid,"Nie można dodawać zapisanych już uczestników!");
	gracz[id][event_saved]=true;
	Ev_PlayerControllable(id, true);
	SendEventMessageToAll(form("{696969}%s [ID:%d]{c0c0c0} dopisał(a) {696969}%s [ID:%d]{c0c0c0} do eventu!",nick(playerid),playerid,nick(id),id));
	AddEventLog(form("%s [ID:%d] dopisuje %s [ID:%d] do eventu",nick(playerid),playerid,nick(id),id));
	return 1;
}
CMD:ev_udel(playerid,params[])
{
	if(gracz[playerid][event_master]==false) return Error(playerid,"Brak uprawnień!");
	if(serwer[event_started]==false) return Error(playerid,"Aktualnie nie trwa żaden event!");
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");
	if(serwer[event_records_on]==true) return Error(playerid,"Nie można tego użyc gdy zapisy na event są włączone!");
	
	new id;
	if(sscanf(params,"i",id)) return SendClientMessage(playerid, -1, ""COL_GREY"Użyj: /ev_udel [ID gracza]");
	if(!IsPlayerConnected(id)) return Error(playerid,form("ID {ffffff}%d{ff3333} jest niepoprawne!"));
	if(gracz[id][loggedin]==false) return Error(playerid,"Gracz nie jest jeszcze zalogowany!");
	if(gracz[id][event_saved]==false) return Error(playerid,"Nie można usuwać nie zapisanych uczestników!");
	if(gracz[id][event_master]==true) return Error(playerid,"Nie można usuwać event masterów!");
	Info(id,"{c0c0c0}Zostałeś/aś wypisany/a z eventu!");
	TextDrawHideForPlayer(id, Event_Info);
	gracz[id][event_saved]=false;
	if(!IsEv_PlayerControllable(id)) Ev_PlayerControllable(id, true);
	if(gracz[id][event_teamid] != -1) gracz[id][event_teamid]=-1;
	if(gracz[id][event_hide_labels] == true) gracz[id][event_hide_labels]=false;
	//Czyszczenie PVarow
	if(gracz[id][event_master] == true)
	{
		DeletePVar(id,"EvPan_VEH_SEL_ModelID");
		DeletePVar(id,"EvP_ClickedID");
		DeletePVar(id,"Ev_NewTeamID");
		DeletePVar(id,"EvPan_VEH_SEL_Color1");
		DeletePVar(id,"EvPan_VEH_EDIT_Color1");
		DeletePVar(id,"EvPan_VEH_LIST_id");
		DeletePVar(id,"EV_GIVE_WEAPONS_ALL_id");
		DeletePVar(id,"EV_GIVE_WEAPONS_LOCAL_id");
	}
	//
	ResetPlayerWeapons(id);
	SetPlayerArmour(id, 0.0);
	SetPlayerHealth(id, 100.0);
	LoadFractionWeapons(id, gracz[id][frakcja]);
	if(gracz[id][event_last_skin_id]!=0) SetPlayerSkin(id, gracz[id][event_last_skin_id]);
	gracz[id][event_last_skin_id]=0;

	SetPlayerPos(id, 1098.4006+ExFloatRandom(-2,2),1434.0753+ExFloatRandom(-2,2),12.3712+ExFloatRandom(0,1)); //daj kordy spawnu
	SetPlayerFacingAngle(id, 3.7128+ExFloatRandom(-180,180));
	SetPlayerInterior(id, 0);
	SetPlayerVirtualWorld(id, 0);

	SendEventMessageToAll(form("{696969}%s [ID:%d]{c0c0c0} wypisał(a) {696969}%s [ID:%d]{c0c0c0} z eventu!",nick(playerid),playerid,nick(id),id));
	
	AddEventLog(form("%s [ID:%d] wypisuje %s [ID:%d] z eventu",nick(playerid),playerid,nick(id),id));
	return 1;
}
CMD:ev_pick(playerid,params[])
{
	if(gracz[playerid][event_master]==false) return Error(playerid,"Brak uprawnień!");
	if(serwer[event_started]==false) return Error(playerid,"Aktualnie nie trwa żaden event!");
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");

	new pick[10];
	if(sscanf(params,"s[10]",pick)) return SendClientMessage(playerid, -1, ""COL_GREY"Użyj: /ev_pick [dodaj (d) | usuń (u)]");

	if(TheSame(pick, "d",true)||TheSame(pick, "dodaj",true))
	{
		if(IsValidDynamicPickup(serwer[event_pickup_id])) return Error(playerid,"Pickup jest już stworzony!");
		new Float:PickPos[3];
		GetPlayerPos(playerid, PickPos[0], PickPos[1], PickPos[2]);

		serwer[event_pickup_id] = CreateDynamicPickup(1277, 1, PickPos[0], PickPos[1], PickPos[2], .worldid = GetPlayerVirtualWorld(playerid), .interiorid = GetPlayerInterior(playerid));
		serwer[event_pickup_pos][0]=PickPos[0];
		serwer[event_pickup_pos][1]=PickPos[1];
		serwer[event_pickup_pos][2]=PickPos[2];
		Info(playerid,"Stworzono pickup!");
		AddEventLog(form("%s [ID:%d] tworzy pickup do teleportowania",nick(playerid),playerid));
		return 1;
	}
	if(TheSame(pick, "u",true)||TheSame(pick, "usuń",true)||TheSame(pick, "usun",true))
	{
		if(!IsValidDynamicPickup(serwer[event_pickup_id])) return Error(playerid,"Brak pickupu!");
		DestroyDynamicPickup(serwer[event_pickup_id]);
		serwer[event_pickup_id]=-1;
		serwer[event_pickup_pos][0]=0.0;
		serwer[event_pickup_pos][1]=0.0;
		serwer[event_pickup_pos][2]=0.0;
		Info(playerid,"Usunięto pickup!");
		AddEventLog(form("%s [ID:%d] usuwa pickup do teleportowania",nick(playerid),playerid));
		return 1;
	}
	Error(playerid,"Błędna opcja!");
	return 1;
}
CMD:ev_niesp(playerid,params[])
{
	if(gracz[playerid][event_master]==false) return Error(playerid,"Brak uprawnień!");
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");
	new type[6],resp[124];
	if(sscanf(params, "s[6]", type)) return SendClientMessage(playerid, -1, ""COL_GREY"Użyj: /ev_niesp [dodaj (d) | usuń (u) | lista (l)]");
	if(TheSame(type, "lista", true)||TheSame(type, "l", true))
	{
		if(GetEventCases()==0) return Error(playerid,"Brak niespodzianek, aby wygenerować listę!");
		new str[4500],col_type=0;
		strcat(str,"UID\tNagrody (Score | kasa)\tPodpowiedź\n");
		for(new i=0; i < EVENT_MAX_CASES; i++)
		{
			if(!IsValidDynamicPickup(serwer[event_case][i])) continue;
			new strcol[100];
			format(strcol,100,"%s",((col_type==0) ? ("{ffffff}") : ("{696969}")));
			format(str,4500,"%s%s%d\t%s%d score | %d$\t%s%s\n",str,strcol,i,strcol,serwer[event_case_score][i],serwer[event_case_money][i],strcol,event_cases_podpowiedz[i]);
			if(col_type==1)
			{
				col_type=0;
				continue;
			}
			if(col_type==0) col_type=1;
		}
		Dialog_Show(playerid, EV_NIESP_LIST, DIALOG_STYLE_TABLIST_HEADERS, "{6666ff}Event{ffffff}Panel - Lista Niespodzianek", str, "Zamknij",#);
		return 1;
	}
	if(sscanf(params, "s[6]s[122]", type,resp))
	{
		if(TheSame(type, "u", true)||TheSame(type, "usuń", true)||TheSame(type, "usun", true)) SendClientMessage(playerid, -1, ""COL_GREY"Użyj: /ev_niesp [usuń (u)] [id]");
		if(TheSame(type, "d", true)||TheSame(type, "dodaj", true)) RenderMessage(playerid, -1, ""COL_GREY"Użyj: /ev_niesp [dodaj (d)] [ilość score (0 = brak)] [ilość kasy (0 = brak)] [podpowiedź]");
		return 1;
	}
	if(TheSame(type, "u", true)||TheSame(type, "usuń", true)||TheSame(type, "usun", true))
	{
		new pick_id;
		if(sscanf(resp, "i", pick_id)) return SendClientMessage(playerid, -1, ""COL_GREY"Użyj: /ev_niesp [usuń (u)] [id]");
		if(!DestroyEventCase(playerid,pick_id,1)) return Error(playerid,form("Nie znaleziono niespodzianki o ID: %d",pick_id));
		return 1;
	}
	if(TheSame(type, "d", true)||TheSame(type, "dodaj", true))
	{
		if(GetEventCases()>=EVENT_MAX_CASES) return Error(playerid,form("Osiągnięto już limit niespodzianek! (%d)",EVENT_MAX_CASES));
		if(serwer[event_cases_daily_count]>=EVENT_MAX_DAILY_CASES) return Error(playerid,form("Osiągnięto już dzienny limit niespodzianek! (%d)",EVENT_MAX_DAILY_CASES));
		new kaska,scorczyk,podpowiedz[50];
		if(sscanf(resp,"iis[50]",scorczyk,kaska,podpowiedz)) return RenderMessage(playerid, -1, ""COL_GREY"Użyj: /ev_niesp [dodaj (d)] [ilość score (0 = brak)] [ilość kasy (0 = brak)] [podpowiedź]");
		if(kaska<0||scorczyk<0) return Error(playerid,"Nie można podawać minusowej wartości!");
		if(kaska==0&&scorczyk==0) return Error(playerid,"Nie można dać 0 score i 0 kasy!");
		if(kaska>EVENT_MAX_CASES_MONEY) return Error(playerid,"Kasy nie może być więcej niż 100000!");
		if(scorczyk>EVENT_MAX_CASES_SCORE) return Error(playerid,"Score nie może być więcej niż 100!");
		ShowModelSelectionMenu(playerid, EV_CASES_ADD_LISTID, "Wybierz ModelID:");
		SetPVarInt(playerid, "Ev_Cases_Score",scorczyk);
		SetPVarInt(playerid, "Ev_Cases_Money",kaska);
		SetPVarString(playerid, "Ev_Cases_Podpowiedz",podpowiedz);
		return 1;
	}
	Error(playerid, "Błędna opcja!");
	return 1;
}
CMD:ev(playerid)
{
	if(gracz[playerid][event_master]==false) return Error(playerid,"Brak uprawnień!");
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");
	new str[4096];
	strcat(str, "{c0c0c0}ID\t{c0c0c0}Opcja\n");
	if(serwer[event_started]==false) strcat(str, "[1]\t{00ff00}•» Rozpocznij{ffffff} event! {00ff00}«•{ffffff}\n");
	else
	{
		strcat(str, "[1]\t{ff3333}•» Zakończ{ffffff} event! {ff3333}«•{ffffff}\n");
		strcat(str, "[2]\t{8D8D8D}Lista uczestników [/ev_usercp]\n");
		strcat(str, "[3]\t{00ff00}Włącz{ffffff}/{ff3333}Wyłącz{ffffff} zapisy\n");
		strcat(str, "[4]\t{8D8D8D}Panel pojazdów\n");
		if(serwer[event_no_dm_status]==false) strcat(str, "[5]\t{00ff00}Włącz {ff3333}No-DM{ffffff}\n");
		else if(serwer[event_no_dm_status]==true) strcat(str, "[5]\t{ff3333}Wyłącz {ff3333}No-DM{ffffff}\n");
		strcat(str, "[6]\t{8D8D8D}Rozdaj {0099FF}wszystkim{8D8D8D} uczestnikom score\n");
		strcat(str, "[7]\t{ffffff}Rozdaj uczestnikom {3333CC}w pobliżu{ffffff} score\n");
		strcat(str, "[8]\t{8D8D8D}Rozdaj {0099FF}wszystkim{8D8D8D} uczestnikom kase\n");
		strcat(str, "[9]\t{ffffff}Rozdaj uczestnikom {3333CC}w pobliżu{ffffff} kase\n");
		strcat(str, "[10]\t{8D8D8D}Zamroź {0099FF}wszystkich{8D8D8D} uczetników \n");
		strcat(str, "[11]\t{ffffff}Zamroź uczetników {3333CC}w pobliżu{ffffff}\n");
		strcat(str, "[12]\t{8D8D8D}Odmroź {0099FF}wszystkich{8D8D8D} uczetników\n");
		strcat(str, "[13]\t{ffffff}Odmroź uczetników {3333CC}w pobliżu{ffffff}\n");
		strcat(str, "[14]\t{8D8D8D}Teleportuj wszystkich uczetników do siebie\n");
		strcat(str, "[15]\t{ffffff}Rozdaj bronie {0099FF}wszystkim{ffffff} uczestnikom\n");
		strcat(str, "[16]\t{8D8D8D}Rozdaj bronie uczestnikom {3333CC}w pobliżu\n");
		strcat(str, "[17]\t{ffffff}Wyczyść bronie {0099FF}wszystkim{ffffff} uczestnikom\n");
		strcat(str, "[18]\t{8D8D8D}Wyczyść bronie uczestnikom {3333CC}w pobliżu\n");
		strcat(str, "[19]\t{ffffff}Ulecz wszystkich {0099FF}wszystkim{ffffff} uczestników\n");
		strcat(str, "[20]\t{8D8D8D}Ulecz wszystkich uczestników {3333CC}w pobliżu\n");
		strcat(str, "[21]\t{ffffff}Daj/Odnów kamizelkę {0099FF}wszystkim{ffffff} uczestnikom\n");
		strcat(str, "[22]\t{8D8D8D}Daj/Odnów kamizelkę uczestnikom {3333CC}w pobliżu\n");
		strcat(str, "[23]\t{ffffff}Wyczyść kamizelkę {0099FF}wszystkim{ffffff} uczestnikom\n");
		strcat(str, "[24]\t{8D8D8D}Wyczyść kamizelkę uczestnikom {3333CC}w pobliżu\n");
		strcat(str, "[25]\t{ffffff}Ustaw skin {0099FF}wszystkim{ffffff} uczestnikom\n");
		strcat(str, "[26]\t{8D8D8D}Ustaw skin uczestnikom {3333CC}w pobliżu{ffffff}\n");
		strcat(str, "[27]\t{ffffff}Ustaw uczestników {3333CC}w pobliżu{ffffff} niewidzialnymi\n");
		strcat(str, "[28]\t{8D8D8D}Ustaw uczestników {3333CC}w pobliżu{8D8D8D} widzialnymi\n");
		strcat(str, "[29]\t{ffffff}Ustaw {0099FF}wszystkim{ffffff} uczestników niewidzialnymi\n");
		strcat(str, "[30]\t{8D8D8D}Ustaw {0099FF}wszystkim{8D8D8D} uczestników widzialnymi\n");
		strcat(str, "[31]\t{ffffff}Dopisz do eventu gracza {c0c0c0}[/ev_uadd]\n");
		strcat(str, "[32]\t{8D8D8D}Zmień VirtualWorld dla {0099FF}wszystkich{8D8D8D} uczestników\n");
		strcat(str, "[33]\t{ffffff}Zmień VirtualWorld dla uczestników {3333CC}w pobliżu{ffffff}\n");
		strcat(str, "[34]\t{8D8D8D}Zmień Interior dla {0099FF}wszystkich{8D8D8D} uczestników\n");
		strcat(str, "[35]\t{ffffff}Zmień Interior dla uczestników {3333CC}w pobliżu\n");
		strcat(str, "[36]\t{8d8d8d}Zregeneruj staminę {0099FF}wszystkim{8d8d8d} uczestnikom\n");
		strcat(str, "[37]\t{ffffff}Zregeneruj staminę uczenikom {3333CC}w pobliżu\n");
		strcat(str, "[38]\t{8D8D8D}Zmień godzinę na evencie\n");
		strcat(str, "[39]\t{ffffff}Zmień pogodę\n");
		strcat(str, "[40]\t{8D8D8D}Panel drużyn\n");
		if(serwer[event_sec_odliczanie]==0) strcat(str, "[41]\t{00ff00}Włącz {ffffff}odliczanie {c0c0c0}[/ev_timer]\n");
		if(serwer[event_sec_odliczanie]!=0) strcat(str, "[41]\t{ff3333}Wyłącz {ffffff}odliczanie {c0c0c0}[/ev_timer]\n");
		strcat(str, "[42]\t{8d8d8d}Daj ogłoszenie {c0c0c0}[/ev_anno]\n");
		if(!IsValidDynamicPickup(serwer[event_pickup_id])) strcat(str, "[43]\t{ffffff}Dodaj pickup {c0c0c0}[/ev_pick d]\n");
		else strcat(str, "[43]\t{ffffff}Usuń pickup {c0c0c0}[/ev_pick u]\n");
		strcat(str, "[44]\t{ffffff}Niespodzianki {c0c0c0}[/ev_niesp]\n");
	}
	Dialog_Show(playerid, EV, DIALOG_STYLE_TABLIST_HEADERS, "{6666FF}Event{ffffff}Panel", str, "Wybierz", "Wyjdź");
	return 1;
}
//
//Komendy - Gracz
CMD:niespodzianki(playerid)
{
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");

	if(GetEventCases()==0) return Error(playerid,"Aktualnie nie ma żadnej niespodzianki!");
	new str[3000],col_type=0;
	strcat(str,"UID\tPodpowiedź\n");
	for(new i=0; i < EVENT_MAX_CASES; i++)
	{
		if(!IsValidDynamicPickup(serwer[event_case][i])) continue;
		new strcolor[100];
		if(col_type==0) format(strcolor,100,"{ffffff}");
		if(col_type==1) format(strcolor,100,"{a28686}");
		format(str,3000,"%s%s%d\t%s%s\n",str,strcolor,i,strcolor,event_cases_podpowiedz[i]);
		if(col_type==0)
		{
			col_type=1;
			continue;
		}
		if(col_type==1) col_type=0;
	}
	Dialog_Show(playerid, EV_USERS_CASES_LIST, DIALOG_STYLE_TABLIST_HEADERS, "{ffffff}Lista dostępnych niespodzianek:", str, "Zamknij", #);
	return 1;
}
CMD:evtp(playerid)
{
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");
	if(serwer[event_started]==false) return Error(playerid,"Aktualnie nie trwa żaden event!");
	if(gracz[playerid][prisoner] == 1) return Error(playerid, "Jesteś w więzieniu.");
	if(gracz[playerid][wypadek] > 0 || gracz[playerid][bw] > 0) return Error(playerid, "Masz BW lub wypadek.");

	if(!IsValidDynamicPickup(serwer[event_pickup_id])) return Error(playerid,"Nie masz do czego się teleportować!");
	new pick_vw,pick_interior;
	pick_vw = Streamer_GetIntData(STREAMER_TYPE_PICKUP, serwer[event_pickup_id], E_STREAMER_WORLD_ID);
	pick_interior = Streamer_GetIntData(STREAMER_TYPE_PICKUP, serwer[event_pickup_id], E_STREAMER_INTERIOR_ID);
	if(IsPlayerInRangeOfPoint(playerid, 50.0, serwer[event_pickup_pos][0], serwer[event_pickup_pos][1], serwer[event_pickup_pos][2])) return Error(playerid,"Jesteś w pobliżu pickupu, nie może tego użyć.");
	SetPlayerPos(playerid, serwer[event_pickup_pos][0], serwer[event_pickup_pos][1], serwer[event_pickup_pos][2]);
	SetPlayerVirtualWorld(playerid, pick_vw);
	SetPlayerInterior(playerid, pick_interior);
	Info(playerid,"Teleportowano na event!");
	AddEventLog(form("%s [ID:%d] teleportuje sie do pickupu",nick(playerid),playerid));
	return 1;
}
CMD:event(playerid)
{
	if(gracz[playerid][loggedin]==false) return Error(playerid,"Aby tego użyć musisz być zalogowany/a!");
	if(gracz[playerid][prisoner] == 1) return Error(playerid, "Jesteś w więzieniu.");
	if(gracz[playerid][wypadek] > 0 || gracz[playerid][bw] > 0) return Error(playerid, "Masz BW lub wypadek.");
	if(serwer[event_started]==true)
	{
		if(gracz[playerid][event_master]==true) return Error(playerid,"Nie możesz tego użyć! Ponieważ posiadasz rangę założyciela!");
		if(serwer[event_records_on]==true)
		{
			if(gracz[playerid][event_saved]==false)
			{
				if(GetEventUsers()>=serwer[event_max_users]) return Error(playerid,"Już osiągnięto maksymalną liczbę uczestników!");
				gracz[playerid][event_saved]=true;
				if(!IsEv_PlayerControllable(playerid)) Ev_PlayerControllable(playerid, true);
				if(gracz[playerid][event_teamid] != -1) gracz[playerid][event_teamid]=-1;
				if(gracz[playerid][event_hide_labels] == true) gracz[playerid][event_hide_labels]=false;
				ResetPlayerWeapons(playerid);
				SetPlayerArmour(playerid, 0.0);
				SetPlayerHealth(playerid, 100.0);
				LoadFractionWeapons(playerid, gracz[playerid][frakcja]);
				gracz[playerid][event_last_skin_id]=0;
				AddEventLog(form("%s [ID:%d] zapisuje sie na event",nick(playerid),playerid));
				return SendEventMessageToAll(form("{696969}%s [ID:%d] {c0c0c0}właśnie zapisał(a) się na event!",nick(playerid),playerid));
			}
			else
			{
				gracz[playerid][event_saved]=false;
				if(!IsEv_PlayerControllable(playerid)) Ev_PlayerControllable(playerid, true);
				if(gracz[playerid][event_teamid] != -1) gracz[playerid][event_teamid]=-1;
				if(gracz[playerid][event_hide_labels] == true) gracz[playerid][event_hide_labels]=false;
				ResetPlayerWeapons(playerid);
				LoadFractionWeapons(playerid, gracz[playerid][frakcja]);
				if(gracz[playerid][event_last_skin_id]!=0) SetPlayerSkin(playerid, gracz[playerid][event_last_skin_id]);
				gracz[playerid][event_last_skin_id]=0;

				AddEventLog(form("%s [ID:%d] wypisuje sie z eventu",nick(playerid),playerid));
				SendEventMessageToAll(form("{696969}%s [ID:%d] {c0c0c0}właśnie wypisał(a) się z eventu!",nick(playerid),playerid));
			}
		}
		else
		{
			if(gracz[playerid][event_saved]==true)
			{
				gracz[playerid][event_saved]=false;
				if(!IsEv_PlayerControllable(playerid)) Ev_PlayerControllable(playerid, true);
				if(gracz[playerid][event_teamid] != -1) gracz[playerid][event_teamid]=-1;
				if(gracz[playerid][event_hide_labels] == true) gracz[playerid][event_hide_labels]=false;
				ResetPlayerWeapons(playerid);
				RemovePlayerFromVehicle(playerid);
				SetPlayerArmour(playerid, 0.0);
				SetPlayerHealth(playerid, 100.0);
				LoadFractionWeapons(playerid, gracz[playerid][frakcja]);
				if(gracz[playerid][event_last_skin_id]!=0) SetPlayerSkin(playerid, gracz[playerid][event_last_skin_id]);
				gracz[playerid][event_last_skin_id]=0;

				SetPlayerPos(playerid, 1098.4006+ExFloatRandom(-2,2),1434.0753+ExFloatRandom(-2,2),12.3712+ExFloatRandom(0,1)); //daj kordy spawnu
				SetPlayerFacingAngle(playerid, 3.7128+ExFloatRandom(-180,180));
				SetPlayerInterior(playerid, 0);
				SetPlayerVirtualWorld(playerid, 0);

				SendEventMessageToAll(form("{696969}%s [ID:%d] {c0c0c0}właśnie wypisał(a) się z eventu!",nick(playerid),playerid));
				AddEventLog(form("%s [ID:%d] wypisuje sie z eventu",nick(playerid),playerid));
			}
			else return Error(playerid,"Aktualnie zapisy są wyłączone!");
		}
	}
	else return Error(playerid,"Aktualnie nie trwa żaden event!");
	return 1;
}
//