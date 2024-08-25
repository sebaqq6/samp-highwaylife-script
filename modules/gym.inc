//USTAWIENIA DODAWANIA SILY
#define GYM_SERIA_LAWECZKA 20
#define GYM_SERIA_HANTLE 20
#define GYM_SERIA_BIEZNIA 80
#define GYM_SERIA_ROWERYK 80
new sgym_bieznia[MAX_PLAYERS] = 0;
new sgym_roweryk[MAX_PLAYERS] = 0;
new sgym_laweczka[MAX_PLAYERS] = 0;
new sgym_hantle[MAX_PLAYERS] = 0;
stock static Float://bieznia
run_machine_pos[ ][ ] =
{
	{2015.5989,2051.9395,11.0426,1.2000}, //0
	{2018.0234,2051.9395,11.0426,1.2000}, //1
	{2020.9225,2051.9395,11.0426,1.2000} //2
};
//BIKE
stock static Float://roweryk
bike_pos[ ][ ] =
{
	{2012.9271,2053.0,11.1085,0.5565},
	{2010.9368,2053.0,11.1085,0.5565},
	{2008.7863,2053.0,11.1085,0.5565}
};
//Bench
stock static Float://lawczeka pos
bench_pos[ ][ ] =
{
	{2011.9965,2040.2,11.1185,179.7852},
	{2014.8379,2040.2,11.1185,178.2184},
	{2017.3289,2040.2,11.1185,182.2919},
	{2020.1813,2040.2,11.1185,180.0985}
};
stock static Float://pozycja sztangi duzej
barbell_pos[ ][ ] =
{
	{2011.563354, 2038.67749, 11.088541, 0.0, 90.0, 0.0},
	{2014.404541, 2038.67749, 11.088541, 0.0, 90.0, 0.0},
	{2016.904541, 2038.67749, 11.088541, 0.0, 90.0, 0.0},
	{2019.735717, 2038.67749, 11.088541, 0.0, 90.0, 0.0}
};

stock static Float://mata
dumb_pos[ ][ ] =
{
	{2011.6956,2044.5807,11.1985,0.5565},
	{2015.1077,2044.5807,11.1985,0.5565},
	{2018.3295,2044.5807,11.1985,0.5565}
};
stock static Float://prawa hantla
dumb_bell_right_pos[ ][ ] =
{
	{2012.026733, 2045.315917, 10.398535, 0.0, 90.0, 0.0},
	{2015.516479, 2045.315917, 10.398535, 0.0, 90.0, 0.0},
	{2018.73706, 2045.315917, 10.398535, 0.0, 90.0, 0.0}
};
stock static Float://lewa hantla
dumb_bell_left_pos[ ][ ] =
{
	{2011.301147, 2045.315917, 10.398535, 0.0, 90.0, 0.0},
	{2014.721679, 2045.315917, 10.398535, 0.0, 90.0, 0.0},
	{2017.892456, 2045.315917, 10.398535, 0.0, 90.0, 0.0}
};
//BOOLS
//____TREAM____
new bool:TREAM_IN_USE[sizeof run_machine_pos]=false;
new TREAM_TIME_RUN[MAX_PLAYERS];
new PLAYER_CURRECT_TREAD[MAX_PLAYERS],
bool:PLAYER_INTREAM[MAX_PLAYERS]=false;
//____BIKE___
new bool:BIKE_IN_USE[sizeof bike_pos]=false;
new BIKE_TIME_RUN[MAX_PLAYERS];
new PLAYER_CURRECT_BIKE[MAX_PLAYERS],
bool:PLAYER_INBIKE[MAX_PLAYERS]=false;
//___BENCH___
new bool:BENCH_IN_USE[sizeof bench_pos]=false;
new PLAYER_CURRECT_BENCH[MAX_PLAYERS],
bool:PLAYER_INBENCH[MAX_PLAYERS]=false;
//___DUMB_BELL___
new bool:DUMB_IN_USE[sizeof bench_pos]=false;
new PLAYER_CURRECT_DUMB[MAX_PLAYERS],
bool:PLAYER_INDUMB[MAX_PLAYERS]=false;
//Gobale
new barbell_objects[sizeof barbell_pos];
new dumbell_right_objects[sizeof dumb_bell_right_pos];
new dumbell_left_objects[sizeof dumb_bell_left_pos];
//TEXTDRAWS
//________TREAD____________________
new PLAYER_TREAM_DIS_COUNT[MAX_PLAYERS];
//________BIKE_____________________
new PLAYER_BIKE_DIS_COUNT[MAX_PLAYERS];
//_______BENCH___________________
new PLAYER_BENCH_COUNT[MAX_PLAYERS];
//________DUMB_BELL_____________
new PLAYER_DUMB_COUNT[MAX_PLAYERS];
//--------------------------------------------------------
stock Init_Gym()
{
	CreateDynamicMapIcon(1997.3120,2038.1550,11.0300, 54, 0, .streamdistance = 1000.0, .style = MAPICON_GLOBAL);
	CreateDynamic3DTextLabel("« "COL_BLUE"KARNET "COL_GREEN"»\n"COL_RED"• "COL_WHITE"Wpisz "COL_RED"/karnet"COL_WHITE" aby zakupi/sprawdzić karnet. "COL_RED"•", 0x009933FF, XYZ_GYMPICKUP, 10.0);
	CreatePickup(3071, 1, XYZ_GYMPICKUP);
	CreateActor(93,2005.2645,2044.8712,11.2345,128.1077);
	//Ruchome
	for(new o; o != sizeof (barbell_pos); o++)
	{
		barbell_objects[o] = CreateDynamicObject(2913, barbell_pos[ o ][ 0 ], barbell_pos[ o ][ 1 ], barbell_pos[ o ][ 2 ], barbell_pos[ o ][ 3 ], barbell_pos[ o ][ 4 ], barbell_pos[ o ][ 5 ], .streamdistance = 50.0, .drawdistance = 50.0, .priority = 1);
	}
	for(new o; o != sizeof (dumb_bell_right_pos); o++)
	{
		dumbell_right_objects[o] = CreateDynamicObject(3071, dumb_bell_right_pos[o][0],dumb_bell_right_pos[o][1],dumb_bell_right_pos[o][2],dumb_bell_right_pos[o][3],dumb_bell_right_pos[o][4],dumb_bell_right_pos[o][5], .streamdistance = 50.0, .drawdistance = 50.0, .priority = 1);
	}
	for(new o; o != sizeof (dumbell_left_objects); o++)
	{    
		dumbell_left_objects[o] = CreateDynamicObject(3072, dumb_bell_left_pos[o][0],dumb_bell_left_pos[o][1],dumb_bell_left_pos[o][2],dumb_bell_left_pos[o][3],dumb_bell_left_pos[o][4],dumb_bell_left_pos[o][5], .streamdistance = 50.0, .drawdistance = 50.0, .priority = 1);
	}
	//3dtexty
	for(new o; o != sizeof (bike_pos); o++)
	{
		CreateDynamic3DTextLabel(""COL_EASY"[{50a99a}Rowerek"COL_EASY"]\n"COL_EASY"["COL_LIME"Użycie: klawisz ENTER"COL_EASY"]", -1, bike_pos[o][0],bike_pos[o][1], bike_pos[o][2], 5.0);
	}
	for(new o; o != sizeof (dumb_pos); o++)
	{
		CreateDynamic3DTextLabel(""COL_EASY"[{50a99a}Hantle"COL_EASY"]\n"COL_EASY"["COL_LIME"Użycie: klawisz ENTER"COL_EASY"]", -1, dumb_pos[o][0], dumb_pos[o][1], dumb_pos[o][2], 5.0);
	}
	for(new o; o != sizeof (bench_pos); o++)
	{
		CreateDynamic3DTextLabel(""COL_EASY"[{50a99a}Ławeczka"COL_EASY"]\n"COL_EASY"["COL_LIME"Użycie: klawisz ENTER"COL_EASY"]", -1, bench_pos[o][0], bench_pos[o][1], bench_pos[o][2], 5.0);
	}
	for(new o; o != sizeof (run_machine_pos); o++)
	{
		CreateDynamic3DTextLabel(""COL_EASY"[{50a99a}Bieżnia"COL_EASY"]\n"COL_EASY"["COL_LIME"Użycie: klawisz ENTER"COL_EASY"]", -1, run_machine_pos[o][0], run_machine_pos[o][1], run_machine_pos[o][2], 5.0);
	}
	return 1;
}
stock gym_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	//schodzenie na sprzęciorów
	if((newkeys & KEY_SECONDARY_ATTACK ) && !(oldkeys & KEY_SECONDARY_ATTACK ))
	{
		if(PLAYER_INTREAM[playerid] == true)
		{
			if(Spam(playerid, SPAM_GYMKEY, 7)) return 1;
			GetOffTread(playerid);
			GameTextForPlayer(playerid,"!", 5000, 4);
			return 1;
		}
		if(PLAYER_INBIKE[playerid] == true)
		{
			if(Spam(playerid, SPAM_GYMKEY, 7)) return 1;
			GetOffBIKE(playerid);
			GameTextForPlayer(playerid,"!", 5000, 4);
			return 1;
		}
		if(PLAYER_INBENCH[playerid] == true)
		{
			if(Spam(playerid, SPAM_GYMKEY, 11)) return 1;
			GetOffBENCH(playerid);
			GameTextForPlayer(playerid,"!", 5000, 4);
			return 1;
		}
		if(PLAYER_INDUMB[playerid] == true)
		{
			if(Spam(playerid, SPAM_GYMKEY, 7)) return 1;
			PutDownDUMB(playerid);
			GameTextForPlayer(playerid,"!", 5000, 4);
			return 1;
		}
	}
	//wchodzenie na sprzęcior
	if((newkeys & KEY_SECONDARY_ATTACK ) && !( oldkeys & KEY_SECONDARY_ATTACK ))
	{
		for( new o; o != sizeof run_machine_pos; o ++ )
		{
			if(IsPlayerInRangeOfPoint(playerid, 1.0, run_machine_pos[ o ][ 0 ], run_machine_pos[ o ][ 1 ], run_machine_pos[ o ][ 2 ] ) )
			{
				if(TREAM_IN_USE[o]==false && PLAYER_INTREAM[playerid]==false)
				{
					if(gracz[playerid][odpornosc] < 65.0) return Error(playerid, "Dostępne od 65.0 odporności. Użyj roweryka.");
					if(IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Nie możesz korzystać z siłowni, kiedy jesteś na służbie!");
					if(!Karnet(playerid)) return LeftNotifyShow(playerid, "error", "~r~Brak~w~ aktywnego karnetu! Zakup nowy karnet.", LN_RED);
					if(Spam(playerid, SPAM_GYMKEY, 5)) return 1;
					PLAYER_INTREAM[playerid]=true;
					TREAM_IN_USE[o]=true;
					PLAYER_CURRECT_TREAD[playerid]=o;
					PLAYER_TREAM_DIS_COUNT[playerid]=0;
					sgym_bieznia[playerid] = 0;
					SetPlayerPos( playerid, run_machine_pos[ o ][ 0 ], run_machine_pos[ o ][ 1 ]+0.2, run_machine_pos[ o ][ 2 ] );
					SetPlayerFacingAngle( playerid, run_machine_pos[ o ][ 3 ] );
					TogglePlayerControllable( playerid, 0 );
					ApplyAnimation( playerid, "GYMNASIUM", "gym_tread_geton", 1, 0, 0, 0, 1, 0, 1 );
					SetTimerEx( "TREAM_START", 2000, false, "d", playerid);
					//SetPlayerCameraPos( playerid, run_machine_pos[ o ][ 0 ] -3, run_machine_pos[ o ][ 1 ] +3, run_machine_pos[ o ][ 2 ] + 0.5 );
					//SetPlayerCameraLookAt( playerid, run_machine_pos[ o ][ 0 ], run_machine_pos[ o ][ 1 ], run_machine_pos[ o ][ 2 ]);
				}
				else
				{
					GameTextForPlayer(playerid,"!", 5000, 4);
				}
			}
		}
		for( new b; b != sizeof bike_pos; b ++ )
		{
			if( IsPlayerInRangeOfPoint( playerid, 1.0, bike_pos[ b ][ 0 ], bike_pos[ b ][ 1 ], bike_pos[ b ][ 2 ] ) )
			{
				if(BIKE_IN_USE[b]==false && PLAYER_INBIKE[playerid]==false)
				{
					if(IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Nie możesz korzystać z siłowni, kiedy jesteś na służbie!");
					if(!Karnet(playerid)) return LeftNotifyShow(playerid, "error", "~r~Brak~w~ aktywnego karnetu! Zakup nowy karnet.", LN_RED);
					if(Spam(playerid, SPAM_GYMKEY, 7)) return 1;
					//Bool Here
					BIKE_IN_USE[b]=true;
					PLAYER_INBIKE[playerid]=true;
					PLAYER_CURRECT_BIKE[playerid]=b;
					//clearn values
					PLAYER_BIKE_DIS_COUNT[playerid]=0;
					sgym_roweryk[playerid] = 0;
					//SetPlayerPos
					SetPlayerPos( playerid, bike_pos[ b ][ 0 ], bike_pos[ b ][ 1 ], bike_pos[ b ][ 2 ] );
					SetPlayerFacingAngle( playerid, bike_pos[ b ][ 3 ] );
					TogglePlayerControllable( playerid, 0 );
					ApplyAnimation( playerid, "GYMNASIUM", "gym_bike_geton", 1, 0, 0, 0, 1, 0, 1 );
					//Set Timer
					SetTimerEx( "BIKE_START", 2000, false, "d", playerid);
					//SetPlayerCameraPos( playerid, bike_pos[ b ][ 0 ] +1, bike_pos[ b ][ 1 ] -1, bike_pos[ b ][ 2 ] + 0.5 );
				   // SetPlayerCameraLookAt( playerid, bike_pos[ b ][ 0 ], bike_pos[ b ][ 1 ], bike_pos[ b ][ 2 ]+0.5);
				}
				else
				{
					GameTextForPlayer(playerid,"!", 5000, 4);
				}
			}
		}
		for (new g; g != sizeof bench_pos; g ++)
		{
			if( IsPlayerInRangeOfPoint( playerid, 1.0, bench_pos[ g ][ 0 ], bench_pos[ g ][ 1 ], bench_pos[ g ][ 2 ] ) )
			{
				if(BENCH_IN_USE[g]==false && PLAYER_INBENCH[playerid]==false)
				{
					if(gracz[playerid][sila] < 65.0) return Error(playerid, "Dostępne od 65.0 siły. Użyj hantli.");
					if(IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Nie możesz korzystać z siłowni, kiedy jesteś na służbie!");
					if(!Karnet(playerid)) return LeftNotifyShow(playerid, "error", "~r~Brak~w~ aktywnego karnetu! Zakup nowy karnet.", LN_RED);
					if(Spam(playerid, SPAM_GYMKEY, 8)) return 1;
					BENCH_IN_USE[g]=true;
					PLAYER_INBENCH[playerid]=true;
					PLAYER_CURRECT_BENCH[playerid]=g;
					//clearn values
					PLAYER_BENCH_COUNT[playerid]=0;
					sgym_laweczka[playerid] = 0;
					//SET POS NOW
					TogglePlayerControllable( playerid, 0 );
					SetPlayerPos( playerid, bench_pos[ g ][ 0 ], bench_pos[ g ][ 1 ], bench_pos[ g ][ 2 ] );
					SetPlayerFacingAngle( playerid, bench_pos[ g ][ 3 ] );
					ApplyAnimation( playerid, "benchpress", "gym_bp_geton", 1, 0, 0, 0, 1, 0, 1 );
					SetTimerEx( "BENCH_START", 3800, 0, "dd", playerid, g);
					//SetPlayerCameraPos( playerid, bench_pos[ g ][ 0 ]-1.5, bench_pos[ g ][ 1 ]+1.5, bench_pos[ g ][ 2 ] + 0.5 );
					//SetPlayerCameraLookAt( playerid, bench_pos[ g ][ 0 ], bench_pos[ g ][ 1 ], bench_pos[ g ][ 2 ]);
				}
				else
				{
					GameTextForPlayer(playerid,"!", 5000, 4);
				}
			}
		}
		for (new d; d != sizeof dumb_pos; d ++)
		{
			if(IsPlayerInRangeOfPoint(playerid, 1.5, dumb_pos[ d ][ 0 ], dumb_pos[ d ][ 1 ], dumb_pos[ d ][ 2 ]))
			{
				if(DUMB_IN_USE[d]==false && PLAYER_INDUMB[playerid]==false)
				{
					if(IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Nie możesz korzystać z siłowni, kiedy jesteś na służbie!");
					if(!Karnet(playerid)) return LeftNotifyShow(playerid, "error", "~r~Brak~w~ aktywnego karnetu! Zakup nowy karnet.", LN_RED);
					if(Spam(playerid, SPAM_GYMKEY, 7)) return 1;
					DUMB_IN_USE[d]=true;
					PLAYER_INDUMB[playerid]=true;
					PLAYER_CURRECT_DUMB[playerid]=d;
					//clearn values
					PLAYER_DUMB_COUNT[playerid]=0;
					sgym_hantle[playerid] = 0;
					//SET POS NOW
					TogglePlayerControllable( playerid, 0 );
					SetPlayerPos(playerid, dumb_pos[ d ][ 0 ], dumb_pos[ d ][ 1 ], dumb_pos[ d ][ 2 ]);
					SetPlayerFacingAngle( playerid, dumb_pos[ d ][ 3 ] );
					ApplyAnimation( playerid, "Freeweights", "gym_free_pickup", 1, 0, 0, 0, 1, 0, 1 );
					SetTimerEx( "DUMB_START", 2000, 0, "d", playerid);
					//SetPlayerCameraPos( playerid, dumb_pos[ d ][ 0 ]+2.3, dumb_pos[ d ][ 1 ], dumb_pos[ d ][ 2 ]+0.3 );
					//SetPlayerCameraLookAt( playerid, dumb_pos[ d ][ 0 ], dumb_pos[ d ][ 1 ], dumb_pos[ d ][ 2 ]+0.5);
				}
			}
		}
	}
	return 1;
}

stock IsPlayerUseGym(playerid)
{
	if(PLAYER_INTREAM[playerid] == true) return 1;
	if(PLAYER_INBIKE[playerid] == true) return 1;
	if(PLAYER_INBENCH[playerid] == true) return 1;
	if(PLAYER_INDUMB[playerid] == true) return 1;
	return 0;
}

forward BIKE_START(playerid);
public BIKE_START(playerid)
{
	ApplyAnimation( playerid, "GYMNASIUM", "bike_start", 1, 1, 0, 0, 1, 0, 1);
	StartCombineMode(playerid, 4);
	SetTimerEx("BIKE_CHECK", 900, false, "d", playerid);
}
forward TREAM_START(playerid);
public TREAM_START(playerid)
{
	ApplyAnimation( playerid, "GYMNASIUM", "gym_tread_sprint", 1, 1, 0, 0, 1, 0, 1);
	TREAM_TIME_RUN[playerid] = serwer[time_timestamp]+8;
	StartCombineMode(playerid, 3);
	SetTimerEx("TREAM_CHECK", 500, false, "d", playerid);
}
forward BENCH_START(playerid,OBJ_INDEX);
public BENCH_START(playerid,OBJ_INDEX)
{
	SetPlayerAttachedObject(playerid, GYM_ATTACH_INDEX1, 2913, 6, 0.000000, 0.000000, -0.081999, 0.000000, 0.000000, 0.000000);
	DestroyDynamicObject(barbell_objects[OBJ_INDEX]);
	StartCombineMode(playerid, 1);
}

forward DUMB_START(playerid);
public DUMB_START(playerid)
{
	SetPlayerAttachedObject(playerid,GYM_ATTACH_INDEX2, 3072, 5);//left hand
	SetPlayerAttachedObject(playerid,GYM_ATTACH_INDEX3, 3071, 6);//right hand
	DestroyDynamicObject(dumbell_right_objects[PLAYER_CURRECT_DUMB[playerid]]);
	DestroyDynamicObject(dumbell_left_objects[PLAYER_CURRECT_DUMB[playerid]]);
	StartCombineMode(playerid, 2);
}


stock DUMB_UP(playerid)
{
	switch(random( 2 ))
	{
		case 0: ApplyAnimation( playerid, "freeweights", "gym_free_A", 1, 0, 0, 0, 1, 0, 1 );
		case 1: ApplyAnimation( playerid, "freeweights", "gym_free_B", 1, 0, 0, 0, 1, 0, 1 );
	}
}

stock DUMB_DOWN(playerid)
{
	ApplyAnimation( playerid, "freeweights", "gym_free_down", 1, 0, 0, 0, 1, 0, 1 );
	PLAYER_DUMB_COUNT[playerid]++;
	sgym_hantle[playerid]++;
	Process_Gym(playerid);
	new str[64];
	format(str, 64, "Ilosc powtorzen: ~y~%d~n~~g~Wzrost sily za: ~y~%d", PLAYER_DUMB_COUNT[playerid], GYM_SERIA_HANTLE-sgym_hantle[playerid]);
	CombineTD_Left(playerid, str);
}

stock BENCH_UP(playerid)
{
	switch(random(2))
	{
		case 0: ApplyAnimation( playerid, "benchpress", "gym_bp_up_A", 1, 0, 0, 0, 1, 0, 1 );
		case 1: ApplyAnimation( playerid, "benchpress", "gym_bp_up_B", 1, 0, 0, 0, 1, 0, 1 );
	}
}

stock BENCH_DOWN(playerid)
{
	ApplyAnimation( playerid, "benchpress", "gym_bp_down", 1, 0, 0, 0, 1, 0, 1 );
	PLAYER_BENCH_COUNT[playerid]++;
	sgym_laweczka[playerid]++;
	Process_Gym(playerid);
	new str[64];
	format(str, 64, "Ilosc powtorzen: ~y~%d~n~~g~Wzrost sily za: ~y~%d", PLAYER_BENCH_COUNT[playerid], GYM_SERIA_LAWECZKA-sgym_laweczka[playerid]);
	CombineTD_Left(playerid, str);
}

forward BIKE_CHECK(playerid);
public BIKE_CHECK(playerid)
{
	if(!PLAYER_INBIKE[playerid]) return 1;
	if(BIKE_TIME_RUN[playerid] >= serwer[time_timestamp])
	{
		ApplyAnimation( playerid, "GYMNASIUM", "gym_bike_fast", 1, 1, 0, 0, 1, 0, 1 );
		PLAYER_BIKE_DIS_COUNT[playerid]++;
		sgym_roweryk[playerid]++;
		Process_Gym(playerid);
		new str[64];
		format(str, 64, "Pokonany dystans: ~y~%dm~n~~g~Wzrost odpornosci za: ~y~%d", PLAYER_BIKE_DIS_COUNT[playerid], GYM_SERIA_ROWERYK-sgym_roweryk[playerid]);
		CombineTD_Left(playerid, str);
		format(str, 64, "00~r~:~w~%02d", BIKE_TIME_RUN[playerid]-serwer[time_timestamp]);
		CombineTD_Beside(playerid, str);
		SetTimerEx("BIKE_CHECK", 1000, false, "d", playerid);
	}
	else
	{
		ApplyAnimation( playerid, "GYMNASIUM", "gym_bike_still", 1, 1, 0, 0, 1, 0, 1);
		SetTimerEx("BIKE_CHECK", 1000, false, "d", playerid);
	}
	return 1;
}

stock BIKE_RUN(playerid)
{
	BIKE_TIME_RUN[playerid] = serwer[time_timestamp]+7;
}

forward TREAM_CHECK(playerid);
public TREAM_CHECK(playerid)
{
	if(!PLAYER_INTREAM[playerid]) return 1;
	if(TREAM_TIME_RUN[playerid] >= serwer[time_timestamp])
	{
		PLAYER_TREAM_DIS_COUNT[playerid]++;
		sgym_bieznia[playerid]++;
		Process_Gym(playerid);
		new str[64];
		format(str, 64, "Pokonany dystans: ~y~%dm~n~~g~Wzrost odpornosci za: ~y~%d", PLAYER_TREAM_DIS_COUNT[playerid], GYM_SERIA_BIEZNIA-sgym_bieznia[playerid]);
		CombineTD_Left(playerid, str);
		format(str, 64, "00~r~:~w~%02d", TREAM_TIME_RUN[playerid]-serwer[time_timestamp]);
		CombineTD_Beside(playerid, str);
		SetTimerEx("TREAM_CHECK", 700, false, "d", playerid);
	}
	else
	{
		FallOffTread(playerid);
	}
	return 1;
}

stock TREAM_RUN(playerid)
{
	TREAM_TIME_RUN[playerid] = serwer[time_timestamp]+7;
}

stock FallOffTread(playerid)
{
	StopCombineMode(playerid);
	ApplyAnimation( playerid, "GYMNASIUM", "gym_tread_falloff", 1, 0, 0, 0, 1, 0, 1 );
	SetTimerEx( "REST_PLAYER", 2000, false, "i", playerid);
}
stock GetOffTread(playerid)
{
	ApplyAnimation( playerid, "GYMNASIUM", "gym_tread_getoff", 1, 0, 0, 0, 1, 0, 1 );
	StopCombineMode(playerid);
	SetTimerEx( "REST_PLAYER", 3500, false, "i", playerid);
}
stock GetOffBENCH(playerid)
{
	ApplyAnimation(playerid, "benchpress", "gym_bp_getoff", 1, 0, 0, 0, 1, 0, 1 );
	StopCombineMode(playerid);
	SetTimerEx( "REST_PLAYER", 2500, false, "i", playerid);
}
stock PutDownDUMB(playerid)
{
	ApplyAnimation(playerid, "freeweights", "gym_free_putdown", 1, 0, 0, 0, 1, 0, 1 );
	StopCombineMode(playerid);
	SetTimerEx( "REST_PLAYER", 1000, false, "i", playerid);
}
stock GetOffBIKE(playerid)
{
	BIKE_TIME_RUN[playerid] = 0;
	ApplyAnimation( playerid, "GYMNASIUM", "gym_bike_getoff", 1, 0, 0, 0, 1, 0, 1 );
	StopCombineMode(playerid);
	SetTimerEx( "REST_PLAYER", 2000, false, "i", playerid);
}

forward REST_PLAYER(playerid);
public REST_PLAYER(playerid)
{
	if(PLAYER_INTREAM[playerid]==true)
	{
		PLAYER_INTREAM[playerid]=false;
		TREAM_IN_USE[PLAYER_CURRECT_TREAD[playerid]]=false;
		REST_PLAYER_2(playerid);
	}
	if(PLAYER_INBIKE[playerid]==true)
	{
		PLAYER_INBIKE[playerid]=false;
		BIKE_IN_USE[PLAYER_CURRECT_BIKE[playerid]]=false;
		REST_PLAYER_2(playerid);
	}
	if(PLAYER_INBENCH[playerid]==true)
	{
		PLAYER_INBENCH[playerid]=false;
		BENCH_IN_USE[PLAYER_CURRECT_BENCH[playerid]]=false;
		barbell_objects[PLAYER_CURRECT_BENCH[playerid]] = CreateDynamicObject(2913, barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 0 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 1 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 2 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 3 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 4 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 5 ], .streamdistance = 50.0, .drawdistance = 50.0, .priority = 1);
		RemovePlayerAttachedObject( playerid, GYM_ATTACH_INDEX1 );
		SetTimerEx( "REST_PLAYER_2", 5000, false, "i", playerid);
	}
	if(PLAYER_INDUMB[playerid]==true)
	{
		PLAYER_INDUMB[playerid]=false;
		DUMB_IN_USE[PLAYER_CURRECT_DUMB[playerid]]=false;
		dumbell_right_objects[PLAYER_CURRECT_DUMB[playerid]] = CreateDynamicObject(3071,dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][0],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][1],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][2],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][3],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][4],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][5], .streamdistance = 50.0, .drawdistance = 50.0, .priority = 1);
		dumbell_left_objects[PLAYER_CURRECT_DUMB[playerid]] = CreateDynamicObject(3072,dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][0],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][1],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][2],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][3],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][4],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][5], .streamdistance = 50.0, .drawdistance = 50.0, .priority = 1);
		RemovePlayerAttachedObject(playerid,GYM_ATTACH_INDEX2);
		RemovePlayerAttachedObject(playerid,GYM_ATTACH_INDEX3);
		SetTimerEx( "REST_PLAYER_2", 1500, false, "i", playerid);
	}
}

forward REST_PLAYER_2(playerid);
public REST_PLAYER_2(playerid)
{
	ClearAnimations(playerid, 1);
	SetCameraBehindPlayer(playerid);
	TogglePlayerControllable(playerid, true);
	return 1;
}

stock Gym_Disconnect(playerid)
{
	if(PLAYER_INTREAM[playerid]==true)
	{
		PLAYER_INTREAM[playerid]=false;
		TREAM_IN_USE[PLAYER_CURRECT_TREAD[playerid]]=false;
	}
	if(PLAYER_INBIKE[playerid]==true)
	{
		PLAYER_INBIKE[playerid]=false;
		BIKE_IN_USE[PLAYER_CURRECT_BIKE[playerid]]=false;
	}
	if(PLAYER_INBENCH[playerid]==true)
	{
		PLAYER_INBENCH[playerid]=false;
		BENCH_IN_USE[PLAYER_CURRECT_BENCH[playerid]]=false;
		barbell_objects[PLAYER_CURRECT_BENCH[playerid]] = CreateDynamicObject(2913, barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 0 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 1 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 2 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 3 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 4 ], barbell_pos[PLAYER_CURRECT_BENCH[playerid]][ 5 ], .streamdistance = 50.0, .drawdistance = 50.0, .priority = 1 );
		RemovePlayerAttachedObject( playerid, GYM_ATTACH_INDEX1);
	}
	if(PLAYER_INDUMB[playerid]==true)
	{
		PLAYER_INDUMB[playerid]=false;
		DUMB_IN_USE[PLAYER_CURRECT_DUMB[playerid]]=false;
		dumbell_right_objects[PLAYER_CURRECT_DUMB[playerid]] = CreateDynamicObject(3071,dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][0],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][1],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][2],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][3],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][4],dumb_bell_right_pos[PLAYER_CURRECT_DUMB[playerid]][5], .streamdistance = 50.0, .drawdistance = 50.0, .priority = 1);
		dumbell_left_objects[PLAYER_CURRECT_DUMB[playerid]] = CreateDynamicObject(3072,dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][0],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][1],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][2],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][3],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][4],dumb_bell_left_pos[PLAYER_CURRECT_DUMB[playerid]][5], .streamdistance = 50.0, .drawdistance = 50.0, .priority = 1);
		RemovePlayerAttachedObject(playerid, GYM_ATTACH_INDEX2);
		RemovePlayerAttachedObject(playerid, GYM_ATTACH_INDEX3);
	}
	ClearAnimations(playerid, 1);
	SetCameraBehindPlayer(playerid);
	TogglePlayerControllable(playerid, true);
	StopCombineMode(playerid);
	return 1;
}

task Process_Gym(playerid)
{
	if(sgym_bieznia[playerid] >= GYM_SERIA_BIEZNIA)
	{
		sgym_bieznia[playerid] = 0;
		if(isvip(playerid)) AddDefense(playerid,  0.028);
		else AddDefense(playerid,  0.025);
	}
	else if(sgym_roweryk[playerid] >= GYM_SERIA_ROWERYK)
	{
		sgym_roweryk[playerid] = 0;
		if(isvip(playerid)) AddDefense(playerid,  0.023);
		else AddDefense(playerid, 0.02);
	}
	else if(sgym_laweczka[playerid] >= GYM_SERIA_LAWECZKA)
	{
		sgym_laweczka[playerid] = 0;
		if(isvip(playerid)) AddStrenght(playerid,  0.028);
		else AddStrenght(playerid,  0.025);
	}
	else if(sgym_hantle[playerid] >= GYM_SERIA_HANTLE)
	{
		sgym_hantle[playerid] = 0;
		if(isvip(playerid)) AddStrenght(playerid,  0.023);
		else AddStrenght(playerid, 0.02);
	}
	return 1;
}


stock SetCombine_KarnetStr(playerid)
{
	new str[64];
	if(gracz[playerid][karnet] > 0)
	{
		new dd, gg, hh, mm;
		SecToTime(gracz[playerid][karnet], dd, gg, hh, mm);
		format(str, 64, "Karnet: ~g~%02d~w~:~g~%02d~w~:~g~%02d", gg, hh, mm);
	}
	else
	{
		format(str, 64, "Karnet: ~r~niewazny");
	}
	CombineTD_Right(playerid, str);
	return 1;
}


stock AddStrenght(playerid, Float:val)
{
	new str[128];
	format(str, 128, "Wzrost sily o: ~b~%0.3f", val);
	LeftNotifyShow(playerid, "Sila", str, LN_GREEN);
	gracz[playerid][sila] += val;
	mq_format("UPDATE `Konta` SET `sila`='%f' WHERE `id`='%d';", gracz[playerid][sila], gracz[playerid][UID]);
	mq_send("QUpdateSila");
	return 1;
}

stock AddDefense(playerid, Float:val)
{
	new str[128];
	format(str, 128, "Wzrost odpornosci o: ~b~%0.3f", val);
	LeftNotifyShow(playerid, "Odpornosc", str, LN_GREEN);
	gracz[playerid][odpornosc] += val;
	mq_format("UPDATE `Konta` SET `odpornosc`='%f' WHERE `id`='%d';", gracz[playerid][odpornosc], gracz[playerid][UID]);
	mq_send("QUpdateSila");
	return 1;
}

stock Karnet(playerid)
{
	if(gracz[playerid][karnet] > 0) return 1;
	return 0;
}