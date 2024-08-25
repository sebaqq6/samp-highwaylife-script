#define VHL_VERSION 101
/*
new SV_EFFECT:pre_parameq;
new SV_EFFECT:distortion;
new SV_EFFECT:post_parameq;
*/
//stream globalny
new SV_SGSTREAM:vhl_streamsg_global = SV_NULL;
//streamy frakcyjne
stock Init_SampVoice()
{
	sv_init(14000, SV_FREQUENCY_VERY_HIGH, SV_VOICE_RATE_100MS, 200.0, 0.2, 0.2);
	vhl_streamsg_global = sv_sgstream_create();
	//krótkofala test:
	/*pre_parameq = sv_effect_create_parameq(0, 150, 36, -15);
	distortion = sv_effect_create_distortion(1, -20, 30, 5400, 1000, 700);
	post_parameq = sv_effect_create_parameq(2, 150, 36, -15);*/
	return 1;
}
//strumienie lokalne (normalne gadanie)
new SV_SGSTREAM:vhl_streamsg_local_voice[MAX_PLAYERS] = SV_NULL; 
new SV_SGSTREAM:vhl_streamsg_echo[MAX_PLAYERS] = SV_NULL;
//lista streamów lokalnyc h
new SV_SGSTREAM:vhl_voiceStreamsList[MAX_PLAYERS][MAX_PLAYERS];
new vhl_voiceStreamsCount[MAX_PLAYERS];
//streamy efektów
new SV_SGSTREAM:vhl_streamsg_effects[MAX_PLAYERS] = SV_NULL;

enum vkc_data
{
	vkc_code,
	vkc_desc[64]
};

new VirtualKeyCodes[][vkc_data] = 
{
	{0x02, "Prawy przycisk myszy"},
	{0x04, "Środkowy przycisk myszy"},
	{0x05, "Przycisk myszy X1"},
	{0x06, "Przycisk myszy X2"},
	{0x13, "Klawisz: PAUSE"},
	{0x14, "Klawisz: CAPS-LOCK"},
	{0x21, "Klawisz: PAGE UP"},
	{0x22, "Klawisz: PAGE DOWN"},
	{0x23, "Klawisz: END"},
	{0x24, "Klawisz: HOME"},
	{0x2D, "Klawisz: INSERT"},
	{0x2E, "Klawisz: DELETE"},
	{0x90, "Klawisz: NUMLOCK"},
	{0x91, "Klawisz: SCROLL LOCK"},
	{0x30, "Klawisz: 0"},
	{0x31, "Klawisz: 1"},
	{0x33, "Klawisz: 3"},
	{0x34, "Klawisz: 4"},
	{0x35, "Klawisz: 5"},
	{0x36, "Klawisz: 6"},
	{0x37, "Klawisz: 7"},
	{0x38, "Klawisz: 8"},
	{0x39, "Klawisz: 9"},
	{0x42, "Klawisz: B"},
	{0x49, "Klawisz: I (i)"},
	{0x4A, "Klawisz: J"},
	{0x4B, "Klawisz: K"},
	{0x4C, "Klawisz: L"},
	{0x4D, "Klawisz: M"},
	{0x4E, "Klawisz: N"},
	{0x4F, "Klawisz: O"},
	{0x50, "Klawisz: P"},
	{0x52, "Klawisz: R"},
	{0x55, "Klawisz: U"},
	{0x58, "Klawisz: X"},
	{0x59, "Klawisz: Y"},
	{0x5A, "Klawisz: Z"},
	{0x71, "Klawisz: F2"}
};

stock Init_VoicePerPlayer(playerid)
{
	//if(!gracz[playerid][AdminLevel]) return 1;//HACK
	new vhl_client_ver = sv_get_version(playerid);
	printf("[VHL] Wersja pluginu głosowego gracza: %s to: %d", nick(playerid ), vhl_client_ver);
	if(vhl_client_ver == SV_NULL || vhl_client_ver < 10) 
	{
		//SendClientMessage(playerid, 0xFF0000FF, "[VHL] "COL_GREY"Brak pluginu głosowego! Pobierz i zainstaluj plugin: "COL_BLUE"https://forum.highwaylife.pl");
		if(vhl_client_ver < 10 && vhl_client_ver != SV_NULL) 
		{
			printf("[VHL-TRY] Gracz %s probowal wykorzystac plugin z GitHub'a.", nick(playerid));
		}
	} 
	else if(vhl_client_ver != VHL_VERSION) 
	{
		SendClientMessage(playerid, 0xFF0000FF, "[VHL] "COL_GREY"Niepoprawna wersja pluginu głosowego. Pobierz poprawną wersję z naszego forum.");
	}
	else
	{
		sv_set_key(playerid, SV_NULL);
		//**********************tworzenie strumieni statycznych per player
		//voice
		vhl_streamsg_local_voice[playerid] = sv_sgstream_create();
		sv_stream_player_attach(vhl_streamsg_local_voice[playerid], playerid);
		//echo
		vhl_streamsg_echo[playerid] = sv_sgstream_create();
		sv_stream_player_attach(vhl_streamsg_echo[playerid], playerid);
		//effects
		vhl_streamsg_effects[playerid] = sv_sgstream_create();
		sv_stream_player_attach(vhl_streamsg_effects[playerid], playerid);
		//**********************end
		SendClientMessage(playerid, COLOR_LIGHTGREEN, "[VHL] "COL_GREY"Serwer wykrył, że masz zainstalowany plugin głosowy.");
		if(!sv_has_micro(playerid)) 
		{
			SendClientMessage(playerid, 0xFF0000FF, "[VHL] "COL_GREY"Nie wykryto mikrofonu. Ustaw w systemie windows domyślne urządzenie przechwytujące.");
			gracz[playerid][has_sampvoice] = true;
			gracz[playerid][vhl_has_micro] = false;
		}
		else 
		{
			gracz[playerid][vhl_has_micro] = true;
			gracz[playerid][has_sampvoice] = true;
			//sv_record_volume(playerid, 1.0);
			sv_set_key(playerid, gracz[playerid][vhl_ptt_virtkeycode]); 
			SendClientMessage(playerid, COLOR_LIGHTGREEN, "[VHL] "COL_GREY"Wykryto mikrofon. Domyślne urządzenie przechwytujące w systemie windows.");
			SendClientMessageEx(playerid, COLOR_LIGHTGREEN, "[VHL] "COL_GREY"Klawisz aktywujący mikrofon: "COL_RED"%s", GetKeyDesc(gracz[playerid][vhl_ptt_virtkeycode]));
		}
		SendClientMessage(playerid, COLOR_LIGHTGREEN, "[VHL] "COL_GREY"Zmiana ustawień: "COL_RED"/vhl");
		dialog_VHLMICVOL(playerid, true, gracz[playerid][vhl_volume_micro]-1, "nomore");
		dialog_VHLSPEAKVOL(playerid, true, gracz[playerid][vhl_volume_speak]-1, "nomore");
	}
	mq_format("UPDATE `Konta` SET `vhl_raw`='%d %d %d %d' WHERE `id`='%d';", gracz[playerid][has_sampvoice], vhl_client_ver, gracz[playerid][vhl_has_micro], serwer[time_timestamp], gracz[playerid][UID]);
	mq_send("QVHLRaw");
	return 1;
}

stock Voice_OnPlayerDisconnect(playerid)
{
	if(gracz[playerid][has_sampvoice] == true)
	{
		//voice
		if(vhl_streamsg_local_voice[playerid] != SV_NULL) 
		{
			sv_stream_delete(vhl_streamsg_local_voice[playerid]);
			vhl_streamsg_local_voice[playerid] = SV_NULL;
			printf("[VHL] Usuwam strumien statyczny[vhl_streamsg_local_voice] dla %s", nick(playerid));
		}
		//echo
		if(vhl_streamsg_echo[playerid] != SV_NULL) 
		{
			sv_stream_delete(vhl_streamsg_echo[playerid]);
			vhl_streamsg_echo[playerid] = SV_NULL;
			printf("[VHL] Usuwam strumien statyczny[vhl_streamsg_echo] dla %s", nick(playerid));
		}
		//effects
		if(vhl_streamsg_effects[playerid] != SV_NULL) 
		{
			sv_stream_delete(vhl_streamsg_effects[playerid]);
			vhl_streamsg_effects[playerid] = SV_NULL;
			printf("[VHL] Usuwam strumien statyczny[vhl_streamsg_effects] dla %s", nick(playerid));
		}

		if(sv_stream_player_has(vhl_streamsg_global, playerid))
		{
			sv_stream_player_detach(vhl_streamsg_global, playerid);
		}
		gracz[playerid][has_sampvoice] = false;
		for(new p = PlayerPoolSize(); p != -1; p--)
		{
			Process_VoiceStreamAttacher(p);//Usuwania dla innych nieaktualnego strumienia natychmiastowo, zanim spróbują wysłać pakiet
		}
		//printf("Voice_OnPlayerDisconnect(%d)", playerid);
	}
	return 1;
}


public SV_BOOL:OnPlayerVoice(
    SV_UINT:playerid,   // ID of the sender
    SV_PACKET:packet,   // Packet descriptor
    SV_UINT:volume      // Volume level [0-32768]
    ) {
	//printf("OnPlayerVoice: %d %d %d", playerid, packet, volume);
	//printf("%s | vol: %d", nick(playerid), volume);
	//SetTimerEx("delay_OnPlayerVoice", 1, false, "dd", playerid, packet);
	delay_OnPlayerVoice(playerid, packet, volume);
	return SV_TRUE;     // Delete the packet? (SV_TRUE - yes, SV_FALSE - no)
}

task delay_OnPlayerVoice(SV_UINT:playerid, SV_PACKET:packet, SV_UINT:volume)
{
	if(gracz[playerid][has_sampvoice] == false) return 1;
	//new speed_test = GetTickCount();
	if(gracz[playerid][vhl_echo])//TRYB ECHO
	{
		MicrophoneActive(playerid, 0xFFFFFFFF, "Tryb ECHO", 3);
		sv_packet_send(packet, vhl_streamsg_echo[playerid]);
		format(temp_string, 32, "%d/100", procent(volume, 32768));
		GameTextForPlayer(playerid, temp_string, 1000, 3);
		return 1;
	}
	//normalne korzystanie:
	if(gracz[playerid][vhl_muted_timestamp] > serwer[time_timestamp])//uciszony?
	{
		format(temp_string, 32, "Uciszony! (%ds)", gracz[playerid][vhl_muted_timestamp]-serwer[time_timestamp]);
		MicrophoneActive(playerid, 0xFF0000FF, temp_string, 2);	
	}
	else//może gadać...
	{
		MicrophoneActive(playerid, 0x00CCCCFF, "Lokalnie - (10m)", 1);
		for(new s = vhl_voiceStreamsCount[playerid]; s != -1; s--)
		{
			if(vhl_voiceStreamsList[playerid][s] != SV_NULL)
			{
				sv_packet_send(packet, vhl_voiceStreamsList[playerid][s]);
				//printf("[VHL] wysyłam pakiet od %s do streamtarget: %d - statyczny", nick(playerid), vhl_voiceStreamsList[playerid][s]);
			}
			//printf("s: %d", s);
		}
		sv_packet_send(packet, vhl_streamsg_global);
	}
	//sprawdzanie czy gracz sie rusza (inny strumień)
	/*new Float:vel[3];
	if(gracz[playerid][opu_vehicleid] == 0) GetPlayerVelocity(playerid, vel[0], vel[1], vel[2]);
	else GetVehicleVelocity(gracz[playerid][opu_vehicleid], vel[0], vel[1], vel[2]);
	//vel[0] = 1.0;//HACK
	if(vel[0] != 0.0 || vel[1] != 0.0 || vel[2] != 0.0)//rusza sie
	{
		//printf("rusza sie - voice");
		//if 0 to nie wykonuj nic
		for(new s = vhl_voiceStreamsCount[playerid]; s != -1; s--)
		{
			if(vhl_voiceStreamsList[playerid][s]  != SV_NULL)
			{
				sv_packet_send(packet, vhl_voiceStreamsList[playerid][s]);
				//printf("[VHL] wysyłam pakiet od %s do streamtarget: %d - statyczny", nick(playerid), vhl_voiceStreamsList[playerid][s]);
			}
			//printf("s: %d", s);
		}
	}
	else //nie rusza sie
	{
		//printf("nie rusza sie - voice");
		sv_packet_send(packet, vhl_streamdl_local_voice[playerid]);
		//printf("[VHL] wysyłam pakiet - strumien lokalny");
	}*/
	//printf("SPEED SEND: %dms", GetTickCount()-speed_test);
	return 1;
}

//microactive[playerid] 
stock MicrophoneActive(playerid, color, comm[], label_talk = 0)
{
	if(gracz[playerid][micro_td] == 0)
	{
		if(label_talk == 1) UpdateDynamic3DTextLabelText(gracz[playerid][p_label][0], 0xFF0000FF, "[MÓWI - CZAT GŁOSOWY]");
		else if(label_talk == 2)
		{
			new strLabel[64];
			format(strLabel, 64, "[UCISZONY (%ds) - VHL]", gracz[playerid][vhl_muted_timestamp]-serwer[time_timestamp]);
			UpdateDynamic3DTextLabelText(gracz[playerid][p_label][0], 0x00CCCCFF, strLabel);
		}
		else if(label_talk == 3) UpdateDynamic3DTextLabelText(gracz[playerid][p_label][0], 0xFFFFFFFF, "[TESTUJE - CZAT GŁOSOWY]");
		PlayerTextDrawColor(playerid, microactive[playerid], color);
		PlayerTextDrawSetString(playerid, microactive[playerid], comm);
		PlayerTextDrawShow(playerid, microactive[playerid]);	
		PlayerPlaySound(playerid, 1083, 0, 0, 0);
		//printf("MicrophoneActive");
	}
	gracz[playerid][micro_td] = GetTickCount()+150;
	return 1;
}
//~h~~h~~h~~h~~g~Wcisnij ~y~F2 ~g~aby mowic
task Process_MicrophoneActive()
{
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(IsPlayerNPC(p)) continue;
		if(gracz[p][has_sampvoice] == false) continue;

		if(gracz[p][micro_td] < GetTickCount() && gracz[p][micro_td] != 0)
		{
			PlayerPlaySound(p, 1084, 0, 0, 0);
			UpdateDynamic3DTextLabelText(gracz[p][p_label][0], 0xFF0000FF, " ");
			//debug end
			gracz[p][micro_td] = 0;
			//printf("Process_MicrophoneActive - off");
			PlayerTextDrawHide(p, microactive[p]);
		}
	}
	return 1;
}

task Process_VoiceStreamAttacher(playerid)
{
	if(!gracz[playerid][has_sampvoice]) return 1;
	//czyszczenie listy streamów
	vhl_voiceStreamsCount[playerid] = 0;
	for(new x; x < MAX_PLAYERS; x++)
	{
		vhl_voiceStreamsList[playerid][x] = SV_NULL;
	}
	//generowanie na nowo listy streamów graczy którzy som blisko
	new str_players_vhl[1024];
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(playerid == p) continue;
		if(!gracz[p][loggedin]) continue;
		if(!gracz[p][has_sampvoice]) continue;
		if(vhl_streamsg_local_voice[p] != SV_NULL)
		{
			if(IsPlayerInRangeOfPoint(playerid, 10.0, gracz[p][PosX], gracz[p][PosY], gracz[p][PosZ]))//gracze którzy są w pobliżu
			{
				vhl_voiceStreamsList[playerid][vhl_voiceStreamsCount[playerid]] = vhl_streamsg_local_voice[p];
				if(gracz[p][admin_spec_enabled] == false)
				{
					format(str_players_vhl, 1024, "%s%s%s~n~", str_players_vhl, (gracz[p][micro_td] != 0) ? ("~r~") : ("~w~"), nick(p));
				}
				vhl_voiceStreamsCount[playerid]++;
			}
		}
	}
	VHL_PlayerList(playerid, "Lokalny (10M)", str_players_vhl);
	return 1;
}
//Funkcje VHL
stock VHL_PlayerEffect(playerid, index)
{
	if(!gracz[playerid][has_sampvoice]) return 0;
	if(vhl_streamsg_effects[playerid] == SV_NULL) return 0; 
	sv_stream_play_sound_internal(vhl_streamsg_effects[playerid], SV_FALSE, index);
	return 1;
}

CMD:vhl(playerid, params[])
{
 	if(!gracz[playerid][has_sampvoice]) return Error(playerid, "Nie posiadasz pluginu głosowego .asi");	
 	new vhlMenu[2048];
 	format(vhlMenu, 2048, ""COL_RED"•» "COL_EASY"Testuj mikrofon/nasłuch\t"COL_BLUE"[ECHO]");
 	format(vhlMenu, 2048, "%s\n"COL_EASY""COL_RED"•» "COL_EASY"Głośność mikrofonu\t"COL_LIME"[%d%%]", vhlMenu, gracz[playerid][vhl_volume_micro]);
 	format(vhlMenu, 2048, "%s\n"COL_EASY""COL_RED"•» "COL_EASY"Głośność nasłuchu\t"COL_LIME"[%d%%]", vhlMenu, gracz[playerid][vhl_volume_speak]);
 	format(vhlMenu, 2048, "%s\n"COL_EASY""COL_RED"•» "COL_EASY"Zmień klawisz przechwytywania\t"COL_BLUE"[%s]", vhlMenu, GetKeyDesc(gracz[playerid][vhl_ptt_virtkeycode]));
 	format(vhlMenu, 2048, "%s\n"COL_EASY""COL_RED"•» "COL_EASY"Dostosuj pozycje ikony wtyczki\t"COL_RED"/mikropos", vhlMenu);
 	//format(vhlMenu, 2048, "%s\n"COL_EASY""COL_RED"•» "COL_EASY"Regulamin czatu głosowego\t"COL_GREY"[PRZECZYTAJ]", vhlMenu);
 	Dialog_Show(playerid, VHLCONFIG, DIALOG_STYLE_TABLIST, ""COL_WHITE"Voice "COL_GREEN"Highway Life"COL_WHITE" (V"COL_GREEN"HL"COL_WHITE")", vhlMenu, "Wybierz", "Anuluj");
	return 1;
}



Dialog:VHLCONFIG(playerid, response, listitem, inputtext[])
{
	if(!gracz[playerid][has_sampvoice]) return Error(playerid, "Nie posiadasz pluginu głosowego .asi");
	if(!response) return 1;
	new strTitle[128];
	switch(listitem)
	{
		case 0://test mikro - echo
		{
			if(!gracz[playerid][vhl_has_micro]) return Error(playerid, "Nie wykryto mikrofonu.");
			gracz[playerid][vhl_echo] = true;
			new strEchoInfo[512];
			format(strEchoInfo, 512, ""COL_WHITE"Wciśnij "COL_RED"%s"COL_WHITE" aby rozpocząć test.", GetKeyDesc(gracz[playerid][vhl_ptt_virtkeycode]));
			format(strEchoInfo, 512, "%s\n"COL_WHITE"Powinieneś słyszeć dźwięk przechwycony z Twojego mikrofonu.", strEchoInfo);
			format(strEchoInfo, 512, "%s\n"COL_WHITE"Jeśli nie słyszysz dźwięku z mikrofonu, upewnij się, że w systemie windows masz", strEchoInfo);
			format(strEchoInfo, 512, "%s\n"COL_WHITE"ustawione prawidłowe urządzenie nagrywania jako domyślne.", strEchoInfo);
			format(strEchoInfo, 512, "%s\n"COL_WHITE"Na ekranie widać "COL_EASY"X/100"COL_WHITE" - to siła sygnału z Twojego mikrofonu.", strEchoInfo);
			format(strEchoInfo, 512, "%s\n\n"COL_WHITE"Aktualne ustawienia(VHL):", strEchoInfo);
			format(strEchoInfo, 512, "%s\n"COL_WHITE"Głośność mikrofonu: "COL_RED"%d%%", strEchoInfo, gracz[playerid][vhl_volume_micro]);
			format(strEchoInfo, 512, "%s\n"COL_WHITE"Głośność nasłuchu: "COL_RED"%d%%", strEchoInfo, gracz[playerid][vhl_volume_speak]);
			Dialog_Show(playerid, VHLECHO, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_GREEN"Test mikrofonu - ECHO"COL_RED" «•", strEchoInfo, "Przerwij", "");
		}
		case 1://głośność mikrofonu
		{
			if(!gracz[playerid][vhl_has_micro]) return Error(playerid, "Nie wykryto mikrofonu.");
			new volMicList[3500];
			for(new vol = 1; vol < 101; vol++)
			{
				if(vol == 1) format(volMicList, 3500, ""COL_RED"•»\t"COL_WHITE"%d%%\t"COL_RED"«•", vol);
				else format(volMicList , 3500, "%s\n"COL_RED"•»\t"COL_WHITE"%d%%\t"COL_RED"«•", volMicList, vol);
			}
			format(strTitle, 128, ""COL_RED"•» "COL_GREEN"Głośność mikrofonu"COL_WHITE" - "COL_LIME"[%d%%]"COL_RED" «•", gracz[playerid][vhl_volume_micro]);
			Dialog_Show(playerid, VHLMICVOL, DIALOG_STYLE_TABLIST, strTitle, volMicList, "Wybierz", "Wróć");
		}
		case 2://głośność nasłuchu
		{
			new volSpeakList[3500];
			for(new vol = 1; vol < 101; vol++)
			{
				if(vol == 1) format(volSpeakList, 3500, ""COL_RED"•»\t"COL_WHITE"%d%%\t"COL_RED"«•", vol);
				else format(volSpeakList, 3500, "%s\n"COL_RED"•»\t"COL_WHITE"%d%%\t"COL_RED"«•", volSpeakList, vol);
			}
			format(strTitle, 128, ""COL_RED"•» "COL_GREEN"Głośność nasłuchu"COL_WHITE" - "COL_LIME"[%d%%]"COL_RED" «•", gracz[playerid][vhl_volume_speak]);
			Dialog_Show(playerid, VHLSPEAKVOL, DIALOG_STYLE_TABLIST, strTitle, volSpeakList, "Wybierz", "Wróć");
		}
		case 3://klawisz przechwytywania
		{
			new virtKeyList[3072];
			for(new vk; vk < sizeof(VirtualKeyCodes); vk++)
			{
				if(vk == 0) format(virtKeyList, 3072, ""COL_RED"•»\t"COL_WHITE"%s\t"COL_RED"«•", VirtualKeyCodes[vk][vkc_desc]);
				else format(virtKeyList, 3072, "%s\n"COL_RED"•»\t"COL_WHITE"%s\t"COL_RED"«•", virtKeyList, VirtualKeyCodes[vk][vkc_desc]);
			}
			format(strTitle, 128, ""COL_RED"•» "COL_GREEN"Klawisz przechwytywania"COL_WHITE" - "COL_LIME"[%s]"COL_RED" «•", GetKeyDesc(gracz[playerid][vhl_ptt_virtkeycode]));
			Dialog_Show(playerid, VHLSETPTT, DIALOG_STYLE_TABLIST, strTitle, virtKeyList, "Wybierz", "Wróć");
		}
		case 4:
		{
			SendClientMessage(playerid, COLOR_LIGHTGREEN, "[VHL] "COL_GREY"Komenda jest po stronie klienta, użyj: "COL_RED"/mikropos");
		}
		case 5://regulamin czatu głosowego
		{

		}
	}
	return 1;
}

Dialog:VHLECHO(playerid, response, listitem, inputtext[])
{
	gracz[playerid][vhl_echo] = false;
	Info(playerid, "Przerwano test mikrofonu.");
	PC_EmulateCommand(playerid, "/vhl");
	return 1;
}

Dialog:VHLMICVOL(playerid, response, listitem, inputtext[])
{
	if(!gracz[playerid][vhl_has_micro]) return 1;
	if(!response) return PC_EmulateCommand(playerid, "/vhl");
	new strFloat[16];
	listitem = listitem+1;//korekta
	gracz[playerid][vhl_volume_micro] = listitem;
	new Float:valFloat = 0.0;//domyślne set
	if(listitem < 10) format(strFloat, 16, "0.0%d", listitem);
	else if(listitem == 100) format(strFloat, 16, "1.0");
	else format(strFloat, 16, "0.%d", listitem);
	valFloat = floatstr(strFloat);
	//printf("DEBUG: item: %d -> float: %f", listitem, valFloat);
	sv_record_volume(playerid, valFloat);
	if(!compare(inputtext, "nomore"))
	{
		PC_EmulateCommand(playerid, "/vhl");
		mq_format("UPDATE `Konta` SET `vhl_volume_micro`='%d' WHERE `id`='%d';", gracz[playerid][vhl_volume_micro], gracz[playerid][UID]);
		mq_send("QVHLSave");
	}
	return 1;
}

Dialog:VHLSPEAKVOL(playerid, response, listitem, inputtext[])
{
	if(!gracz[playerid][has_sampvoice]) return 1;
	if(!response) return PC_EmulateCommand(playerid, "/vhl");
	new strFloat[16];
	listitem = listitem+1;//korekta
	gracz[playerid][vhl_volume_speak] = listitem;
	new Float:valFloat = 0.0;//domyślne set
	if(listitem < 10) format(strFloat, 16, "0.0%d", listitem);
	else if(listitem == 100) format(strFloat, 16, "1.0");
	else format(strFloat, 16, "0.%d", listitem);
	valFloat = floatstr(strFloat);
	//printf("DEBUG: item: %d -> float: %f", listitem, valFloat);
	sv_stream_set_parameter(vhl_streamsg_local_voice[playerid], SV_PARAMETER_VOLUME, valFloat);
	sv_stream_set_parameter(vhl_streamsg_echo[playerid], SV_PARAMETER_VOLUME, valFloat);
	if(!compare(inputtext, "nomore"))
	{
		PC_EmulateCommand(playerid, "/vhl");
		mq_format("UPDATE `Konta` SET `vhl_volume_speak`='%d' WHERE `id`='%d';", gracz[playerid][vhl_volume_speak], gracz[playerid][UID]);
		mq_send("QVHLSave");
	}
	return 1;
}


Dialog:VHLSETPTT(playerid, response, listitem, inputtext[])
{
	if(!gracz[playerid][has_sampvoice]) return 1;
	if(!response) return PC_EmulateCommand(playerid, "/vhl");
	gracz[playerid][vhl_ptt_virtkeycode] = VirtualKeyCodes[listitem][vkc_code];
	sv_set_key(playerid, gracz[playerid][vhl_ptt_virtkeycode]);
	SendClientMessageEx(playerid, COLOR_LIGHTGREEN, "[VHL] "COL_GREY"Ustawiono: "COL_RED"%s", VirtualKeyCodes[listitem][vkc_desc]);
	PC_EmulateCommand(playerid, "/vhl");
	mq_format("UPDATE `Konta` SET `vhl_ptt_virtkeycode`='%d' WHERE `id`='%d';", gracz[playerid][vhl_ptt_virtkeycode], gracz[playerid][UID]);
	mq_send("QVHLSave");
	return 1;
}

stock GetKeyDesc(virtual_key)
{
	new strDesc[64];
	format(strDesc, 64, "NULL");
	for(new vk; vk < sizeof(VirtualKeyCodes); vk++)
	{
		if(virtual_key == VirtualKeyCodes[vk][vkc_code])
		{
			format(strDesc, 64, VirtualKeyCodes[vk][vkc_desc]);
			break;
		}
	}
	return strDesc;
}

stock VHL_GetAll(playerid)
{
	if(gracz[playerid][vhl_getall])
	{
		gracz[playerid][vhl_getall] = false;
		sv_stream_player_detach(vhl_streamsg_global, playerid);
	}
	else
	{
		gracz[playerid][vhl_getall] = true;
		
		sv_stream_player_attach(vhl_streamsg_global, playerid);
	}
	return gracz[playerid][vhl_getall];
}

/*
CMD:rstart(playerid, params[])
{
	sv_record_start(playerid);
	Info(playerid, ""COL_GREEN"START");
	return 1;
}

CMD:rstop(playerid, params[])
{
	sv_record_stop(playerid);
	Info(playerid, ""COL_GREEN"STOP");
	return 1;
}
*/
