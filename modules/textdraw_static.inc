//Player:

new PlayerText:pHUD0[MAX_PLAYERS];
new PlayerText:pHUD1[MAX_PLAYERS];
new PlayerText:pHUD2[MAX_PLAYERS];
new PlayerText:pHUD3[MAX_PLAYERS];
new PlayerText:pHUD4[MAX_PLAYERS];
new PlayerText:pHUD5[MAX_PLAYERS];
new PlayerText:pHUD6[MAX_PLAYERS];
new PlayerText:pHUD7[MAX_PLAYERS];
new PlayerText:pHUD8[MAX_PLAYERS];
new PlayerText:pHUD9[MAX_PLAYERS];
new PlayerText:pHUD10[MAX_PLAYERS];
new PlayerText:pHUD11[MAX_PLAYERS];
new PlayerText:pHUD12[MAX_PLAYERS];

//Global:

new Text:pgHUD0;
new Text:pgHUD1;
new Text:pgHUD2;
new Text:pgHUD3;
new Text:pgHUD6;
new Text:pgHUD7;
new Text:pgHUD8;
new Text:pgHUD9;
new Text:pgHUD10;


new Text:td_g_ver;

new Text:td_g_clock0;
new Text:td_g_clock1;

new Text:interwencja_td;

stock Init_TextDrawPlayerStatic(playerid)
{
	pHUD0[playerid] = CreatePlayerTextDraw(playerid, 563.733215, 82.299255, "1 000 000$");
	PlayerTextDrawLetterSize(playerid, pHUD0[playerid], 0.449999, 1.600000);
	PlayerTextDrawAlignment(playerid, pHUD0[playerid], 2);
	PlayerTextDrawColor(playerid, pHUD0[playerid], -1);
	PlayerTextDrawSetShadow(playerid, pHUD0[playerid], 0);
	PlayerTextDrawSetOutline(playerid, pHUD0[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, pHUD0[playerid], 12028415);
	PlayerTextDrawFont(playerid, pHUD0[playerid], 3);
	PlayerTextDrawSetProportional(playerid, pHUD0[playerid], 1);
	
	pHUD1[playerid] = CreatePlayerTextDraw(playerid, 507.333221, 59.733287, "Piesc");
	PlayerTextDrawLetterSize(playerid, pHUD1[playerid], 0.159633, 1.218370);
	PlayerTextDrawAlignment(playerid, pHUD1[playerid], 2);
	PlayerTextDrawColor(playerid, pHUD1[playerid], 12028415);
	PlayerTextDrawSetShadow(playerid, pHUD1[playerid], 0);
	PlayerTextDrawSetOutline(playerid, pHUD1[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, pHUD1[playerid], 51);
	PlayerTextDrawFont(playerid, pHUD1[playerid], 1);
	PlayerTextDrawSetProportional(playerid, pHUD1[playerid], 1);
	
	pHUD2[playerid] = CreatePlayerTextDraw(playerid, 421.433502, 436.260894, "sebaqq6(0)");
	PlayerTextDrawLetterSize(playerid, pHUD2[playerid], 0.130866, 1.095170);
	PlayerTextDrawAlignment(playerid, pHUD2[playerid], 2);
	PlayerTextDrawColor(playerid, pHUD2[playerid], -1);
	PlayerTextDrawSetShadow(playerid, pHUD2[playerid], 0);
	PlayerTextDrawSetOutline(playerid, pHUD2[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, pHUD2[playerid], 51);
	PlayerTextDrawFont(playerid, pHUD2[playerid], 1);
	PlayerTextDrawSetProportional(playerid, pHUD2[playerid], 1);
	
	pHUD3[playerid] = CreatePlayerTextDraw(playerid, 501.166870, 436.095001, "12345");
	PlayerTextDrawLetterSize(playerid, pHUD3[playerid], 0.362333, 1.247407);
	PlayerTextDrawAlignment(playerid, pHUD3[playerid], 2);
	PlayerTextDrawColor(playerid, pHUD3[playerid], 12028415);
	PlayerTextDrawSetShadow(playerid, pHUD3[playerid], -2);
	PlayerTextDrawSetOutline(playerid, pHUD3[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, pHUD3[playerid], 51);
	PlayerTextDrawFont(playerid, pHUD3[playerid], 1);
	PlayerTextDrawSetProportional(playerid, pHUD3[playerid], 1);
	
	pHUD4[playerid] = CreatePlayerTextDraw(playerid, 589.199584, 435.809112, "Sluzby Ratunkowe");
	PlayerTextDrawLetterSize(playerid, pHUD4[playerid], 0.282100, 1.166933);
	PlayerTextDrawAlignment(playerid, pHUD4[playerid], 2);
	PlayerTextDrawColor(playerid, pHUD4[playerid], -1);
	PlayerTextDrawSetShadow(playerid, pHUD4[playerid], -2);
	PlayerTextDrawSetOutline(playerid, pHUD4[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, pHUD4[playerid], 51);
	PlayerTextDrawFont(playerid, pHUD4[playerid], 1);
	PlayerTextDrawSetProportional(playerid, pHUD4[playerid], 1);
	
	pHUD5[playerid] = CreatePlayerTextDraw(playerid, 611.466735, 24.971853, "mdl-2001:hud_progress_bar");
	PlayerTextDrawLetterSize(playerid, pHUD5[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, pHUD5[playerid], -63.899993, 8.711102);
	PlayerTextDrawAlignment(playerid, pHUD5[playerid], 3);
	PlayerTextDrawColor(playerid, pHUD5[playerid], -16776961);
	PlayerTextDrawSetShadow(playerid, pHUD5[playerid], 0);
	PlayerTextDrawSetOutline(playerid, pHUD5[playerid], 0);
	PlayerTextDrawFont(playerid, pHUD5[playerid], 4);
	
	pHUD6[playerid] = CreatePlayerTextDraw(playerid, 611.400024, 43.394073, "mdl-2001:hud_progress_bar");
	PlayerTextDrawLetterSize(playerid, pHUD6[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, pHUD6[playerid], -63.899993, 8.711102);
	PlayerTextDrawAlignment(playerid, pHUD6[playerid], 3);
	PlayerTextDrawColor(playerid, pHUD6[playerid], 65535);
	PlayerTextDrawSetShadow(playerid, pHUD6[playerid], 0);
	PlayerTextDrawSetOutline(playerid, pHUD6[playerid], 0);
	PlayerTextDrawFont(playerid, pHUD6[playerid], 4);
	
	pHUD7[playerid] = CreatePlayerTextDraw(playerid, 611.366394, 61.567398, "mdl-2001:hud_progress_bar");
	PlayerTextDrawLetterSize(playerid, pHUD7[playerid], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, pHUD7[playerid], -63.899993, 8.711102);
	PlayerTextDrawAlignment(playerid, pHUD7[playerid], 3);
	PlayerTextDrawColor(playerid, pHUD7[playerid], 8388863);
	PlayerTextDrawSetShadow(playerid, pHUD7[playerid], 0);
	PlayerTextDrawSetOutline(playerid, pHUD7[playerid], 0);
	PlayerTextDrawFont(playerid, pHUD7[playerid], 4);

	pHUD8[playerid] = CreatePlayerTextDraw(playerid,600.000000, 21.000000, "playerskin");
	PlayerTextDrawBackgroundColor(playerid,pHUD8[playerid], -255);
	PlayerTextDrawFont(playerid,pHUD8[playerid], 5);
	PlayerTextDrawLetterSize(playerid,pHUD8[playerid], -1.400000, -2.500000);
	PlayerTextDrawColor(playerid,pHUD8[playerid], -1);
	PlayerTextDrawSetOutline(playerid,pHUD8[playerid], 0);
	PlayerTextDrawSetProportional(playerid,pHUD8[playerid], 1);
	PlayerTextDrawSetShadow(playerid,pHUD8[playerid], 1);
	PlayerTextDrawUseBox(playerid,pHUD8[playerid], 1);
	PlayerTextDrawBoxColor(playerid,pHUD8[playerid], -255);
	PlayerTextDrawTextSize(playerid,pHUD8[playerid], 45.000000, 51.000000);
	PlayerTextDrawSetPreviewModel(playerid, pHUD8[playerid], 1);
	PlayerTextDrawSetPreviewRot(playerid, pHUD8[playerid], -16.000000, 0.000000, -30.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid,pHUD8[playerid], 0);

	pHUD9[playerid] = CreatePlayerTextDraw(playerid, 578.966125, 24.847532, "100%");
	PlayerTextDrawLetterSize(playerid, pHUD9[playerid], 0.131494, 0.675791);
	PlayerTextDrawAlignment(playerid, pHUD9[playerid], 2);
	PlayerTextDrawColor(playerid, pHUD9[playerid], -1);
	PlayerTextDrawSetShadow(playerid, pHUD9[playerid], 0);
	PlayerTextDrawSetOutline(playerid, pHUD9[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, pHUD9[playerid], 51);
	PlayerTextDrawFont(playerid, pHUD9[playerid], 3);
	PlayerTextDrawSetProportional(playerid, pHUD9[playerid], 1);
	
	pHUD10[playerid] = CreatePlayerTextDraw(playerid, 578.799499, 43.435672, "100%");
	PlayerTextDrawLetterSize(playerid, pHUD10[playerid], 0.131494, 0.675791);
	PlayerTextDrawAlignment(playerid, pHUD10[playerid], 2);
	PlayerTextDrawColor(playerid, pHUD10[playerid], -1);
	PlayerTextDrawSetShadow(playerid, pHUD10[playerid], 0);
	PlayerTextDrawSetOutline(playerid, pHUD10[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, pHUD10[playerid], 51);
	PlayerTextDrawFont(playerid, pHUD10[playerid], 3);
	PlayerTextDrawSetProportional(playerid, pHUD10[playerid], 1);
	
	pHUD11[playerid] = CreatePlayerTextDraw(playerid, 578.632995, 61.650489, "100%");
	PlayerTextDrawLetterSize(playerid, pHUD11[playerid], 0.131494, 0.675791);
	PlayerTextDrawAlignment(playerid, pHUD11[playerid], 2);
	PlayerTextDrawColor(playerid, pHUD11[playerid], -1);
	PlayerTextDrawSetShadow(playerid, pHUD11[playerid], 0);
	PlayerTextDrawSetOutline(playerid, pHUD11[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, pHUD11[playerid], 51);
	PlayerTextDrawFont(playerid, pHUD11[playerid], 3);
	PlayerTextDrawSetProportional(playerid, pHUD11[playerid], 1);
	
	pHUD12[playerid] = CreatePlayerTextDraw(playerid, 506.966705, 71.522926, "Ammo: 100");
	PlayerTextDrawLetterSize(playerid, pHUD12[playerid], 0.114230, 0.724322);
	PlayerTextDrawAlignment(playerid, pHUD12[playerid], 2);
	PlayerTextDrawColor(playerid, pHUD12[playerid], 255);
	PlayerTextDrawSetShadow(playerid, pHUD12[playerid], 0);
	PlayerTextDrawSetOutline(playerid, pHUD12[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, pHUD12[playerid], 51);
	PlayerTextDrawFont(playerid, pHUD12[playerid], 1);
	PlayerTextDrawSetProportional(playerid, pHUD12[playerid], 1);

	return 1;
}

stock Init_TextDrawStatic()
{
	pgHUD0 = TextDrawCreate(-7.000015, 431.034271, "mdl-2001:hud_belka_dolna");
	TextDrawLetterSize(pgHUD0, 0.000000, 0.000000);
	TextDrawTextSize(pgHUD0, 649.799621, 20.035570);
	TextDrawAlignment(pgHUD0, 1);
	TextDrawColor(pgHUD0, -1);
	TextDrawSetShadow(pgHUD0, 0);
	TextDrawSetOutline(pgHUD0, 0);
	TextDrawFont(pgHUD0, 4);
	
	pgHUD1 = TextDrawCreate(3.766705, 424.438385, "mdl-2001:hud_background1");
	TextDrawLetterSize(pgHUD1, 0.000000, 0.000000);
	TextDrawTextSize(pgHUD1, 17.000000, 18.376287);
	TextDrawAlignment(pgHUD1, 1);
	TextDrawColor(pgHUD1, -1);
	TextDrawSetShadow(pgHUD1, 0);
	TextDrawSetOutline(pgHUD1, 0);
	TextDrawFont(pgHUD1, 4);
	
	pgHUD2 = TextDrawCreate(3.666706, 424.733154, "mdl-2001:hud_logo");
	TextDrawLetterSize(pgHUD2, 0.000000, 0.000000);
	TextDrawTextSize(pgHUD2, 17.100000, 18.376287);
	TextDrawAlignment(pgHUD2, 1);
	TextDrawColor(pgHUD2, -1);
	TextDrawSetShadow(pgHUD2, 0);
	TextDrawSetOutline(pgHUD2, 0);
	TextDrawFont(pgHUD2, 4);
	
	pgHUD3 = TextDrawCreate(479.366546, 13.896349, "mdl-2001:hud_player");
	TextDrawLetterSize(pgHUD3, 0.000000, 0.000000);
	TextDrawTextSize(pgHUD3, 163.433349, 88.521446);
	TextDrawAlignment(pgHUD3, 1);
	TextDrawColor(pgHUD3, -1);
	TextDrawSetShadow(pgHUD3, 0);
	TextDrawSetOutline(pgHUD3, 0);
	TextDrawFont(pgHUD3, 4);
	
	td_g_clock0 = TextDrawCreate(492.133483, 20.989652, "12:00");
	TextDrawLetterSize(td_g_clock0, 0.211233, 1.213392);
	TextDrawAlignment(td_g_clock0, 1);
	TextDrawColor(td_g_clock0, 12028415);
	TextDrawSetShadow(td_g_clock0, 0);
	TextDrawSetOutline(td_g_clock0, 0);
	TextDrawBackgroundColor(td_g_clock0, 51);
	TextDrawFont(td_g_clock0, 3);
	TextDrawSetProportional(td_g_clock0, 1);
	
	td_g_clock1 = TextDrawCreate(512.566650, 20.496322, "59");
	TextDrawLetterSize(td_g_clock1, 0.187233, 1.001837);
	TextDrawAlignment(td_g_clock1, 1);
	TextDrawColor(td_g_clock1, 12028415);
	TextDrawSetShadow(td_g_clock1, 0);
	TextDrawSetOutline(td_g_clock1, 0);
	TextDrawBackgroundColor(td_g_clock1, 12028415);
	TextDrawFont(td_g_clock1, 2);
	TextDrawSetProportional(td_g_clock1, 1);
	
	pgHUD6 = TextDrawCreate(507.233154, 32.604419, "Poniedzialek");
	TextDrawLetterSize(pgHUD6, 0.130333, 0.724740);
	TextDrawAlignment(pgHUD6, 2);
	TextDrawColor(pgHUD6, 255);
	TextDrawSetShadow(pgHUD6, 0);
	TextDrawSetOutline(pgHUD6, 0);
	TextDrawBackgroundColor(pgHUD6, 51);
	TextDrawFont(pgHUD6, 1);
	TextDrawSetProportional(pgHUD6, 1);
	
	pgHUD7 = TextDrawCreate(492.900177, 54.382186, "mdl-2001:hud_background0");
	TextDrawLetterSize(pgHUD7, 0.000000, 0.000000);
	TextDrawTextSize(pgHUD7, 29.600000, 5.517051);
	TextDrawAlignment(pgHUD7, 1);
	TextDrawColor(pgHUD7, -1);
	TextDrawSetShadow(pgHUD7, 0);
	TextDrawSetOutline(pgHUD7, 0);
	TextDrawFont(pgHUD7, 4);
	
	pgHUD8 = TextDrawCreate(506.966613, 53.349605, "Uzbrojenie");
	TextDrawLetterSize(pgHUD8, 0.130333, 0.724740);
	TextDrawAlignment(pgHUD8, 2);
	TextDrawColor(pgHUD8, 255);
	TextDrawSetShadow(pgHUD8, 0);
	TextDrawSetOutline(pgHUD8, 0);
	TextDrawBackgroundColor(pgHUD8, 51);
	TextDrawFont(pgHUD8, 1);
	TextDrawSetProportional(pgHUD8, 1);
	
	pgHUD9 = TextDrawCreate(197.000091, 434.933502, "Po rozlaczeniu sie, masz 5 minut aby z powrotem wrocic na serwer. Inaczej system RELOG nie wczyta ostatniej sytuacji.");
	TextDrawLetterSize(pgHUD9, 0.165233, 1.240356);
	TextDrawAlignment(pgHUD9, 2);
	TextDrawColor(pgHUD9, 12028415);
	TextDrawSetShadow(pgHUD9, 0);
	TextDrawSetOutline(pgHUD9, 0);
	TextDrawBackgroundColor(pgHUD9, 12028415);
	TextDrawFont(pgHUD9, 1);
	TextDrawSetProportional(pgHUD9, 1);
	
	pgHUD10 = TextDrawCreate(489.966644, 72.385208, "mdl-2001:hud_background0");
	TextDrawLetterSize(pgHUD10, 0.000000, 0.000000);
	TextDrawTextSize(pgHUD10, 35.600006, 5.931867);
	TextDrawAlignment(pgHUD10, 1);
	TextDrawColor(pgHUD10, -1);
	TextDrawSetShadow(pgHUD10, 0);
	TextDrawSetOutline(pgHUD10, 0);
	TextDrawFont(pgHUD10, 4);

	td_g_ver = TextDrawCreate(637.555480, 1.841735, serwer[wersja]);
	TextDrawLetterSize(td_g_ver, 0.200311, 0.874737);
	TextDrawAlignment(td_g_ver, 3);
	TextDrawColor(td_g_ver, -1);
	TextDrawSetShadow(td_g_ver, 0);
	TextDrawSetOutline(td_g_ver, -1);
	TextDrawBackgroundColor(td_g_ver, 12225791);
	TextDrawFont(td_g_ver, 1);
	TextDrawSetProportional(td_g_ver, 1);

	interwencja_td = TextDrawCreate(3.750002, 152.424972, "_");
	TextDrawLetterSize(interwencja_td, 0.191999, 0.711875);
	TextDrawTextSize(interwencja_td, 133.000000, -54.687500);
	TextDrawAlignment(interwencja_td, 1);
	TextDrawColor(interwencja_td, -1);
	TextDrawUseBox(interwencja_td, true);
	TextDrawBoxColor(interwencja_td, 128);
	TextDrawSetShadow(interwencja_td, 0);
	TextDrawSetOutline(interwencja_td, 1);
	TextDrawBackgroundColor(interwencja_td, 51);
	TextDrawFont(interwencja_td, 1);
	TextDrawSetProportional(interwencja_td, 1);
	return 1;
}