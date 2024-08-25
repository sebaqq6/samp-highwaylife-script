#define CKEY_UP 1
#define CKEY_DOWN 2
#define CKEY_LEFT 3
#define CKEY_RIGHT 4


forward  StartCombineMode(playerid, cid);
public StartCombineMode(playerid, cid)
{
	if(combine_mode[playerid][c_id]) return 0;
	combine_mode[playerid][c_id] = cid;
	combine_mode[playerid][c_step] = 0;
	combine_mode[playerid][c_mode] = 0;
	combine_mode[playerid][c_bad] = 0;
	switch(combine_mode[playerid][c_id])
	{
		case 1:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "laweczka");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			new str[64];
			format(str, 64, "Ilosc powtorzen: ~y~0~n~~g~Wzrost sily za: ~y~%d", GYM_SERIA_LAWECZKA);
			CombineTD_Left(playerid, str);
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "_");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
		}
		case 2:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "hantle");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			new str[64];
			format(str, 64, "Ilosc powtorzen: ~y~0~n~~g~Wzrost sily za: ~y~%d", GYM_SERIA_HANTLE);
			CombineTD_Left(playerid, str);
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "_");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
		}
		case 3:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "bieznia");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			new str[64];
			format(str, 64, "Pokonany dystans: ~y~0~n~~g~Wzrost sily za: ~y~%d", GYM_SERIA_BIEZNIA);
			CombineTD_Left(playerid, str);
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "_");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
		}
		case 4:
		{
			GenerateCombine(playerid);
			CombineTD_Title(playerid, "rowerek");
			CombineTD_Tip(playerid, "((Wykonaj powyzsza kombinacje za pomoca strzalek na klawiaturze.))");
			new str[64];
			format(str, 64, "Pokonany dystans: ~y~0~n~~g~Wzrost sily za: ~y~%d", GYM_SERIA_ROWERYK);
			CombineTD_Left(playerid, str);
			CombineTD_Right(playerid, "_");
			CombineTD_Beside(playerid, "_");
			CombineTD_Combine(playerid, GetCombine(playerid));
			ShowCombineTD(playerid);
			combine_mode[playerid][c_step] = 1;
		}
	}
	return 1;
}

stock StopCombineMode(playerid)
{
	combine_mode[playerid][c_id] = 0;
	HideCombineTD(playerid);
	return 1;
}

stock InCombineMode(playerid) return combine_mode[playerid][c_id];

task Process_CombineMode(playerid)
{
	if(!combine_mode[playerid][c_id]) return 0;
	switch(combine_mode[playerid][c_id])
	{
		case 1:
		{
			SetCombine_KarnetStr(playerid);
			if(combine_mode[playerid][c_step] == 1)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					if(!Karnet(playerid))
					{
						if(combine_mode[playerid][c_qkey] >= 1)
						{
							combine_mode[playerid][c_qkey] = 0;
							LeftNotifyShow(playerid, "error", "~r~Brak~w~ aktywnego karnetu! Zakup nowy karnet.", LN_RED);
						}
					}
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					BENCH_UP(playerid);
					combine_mode[playerid][c_step] = 3;
					ShowCombineTD(playerid);
				}
			}
			else if(combine_mode[playerid][c_step] == 2)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					BENCH_DOWN(playerid);
					ShowCombineTD(playerid);
					combine_mode[playerid][c_step] = 4;
				}
			}
			else if(combine_mode[playerid][c_step] == 3)
			{
				GenerateCombine(playerid, 2);
				CombineTD_Combine(playerid, GetCombine(playerid));
				ShowCombineTD(playerid);
				combine_mode[playerid][c_step] = 2;
			}
			else if(combine_mode[playerid][c_step] == 4)
			{
				GenerateCombine(playerid);
				CombineTD_Combine(playerid, GetCombine(playerid));
				ShowCombineTD(playerid);
				combine_mode[playerid][c_step] = 1;
			}
		}
		case 2:
		{
			SetCombine_KarnetStr(playerid);
			if(combine_mode[playerid][c_step] == 1)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					if(!Karnet(playerid))
					{
						if(combine_mode[playerid][c_qkey] >= 1)
						{
							combine_mode[playerid][c_qkey] = 0;
							LeftNotifyShow(playerid, "error", "~r~Brak~w~ aktywnego karnetu! Zakup nowy karnet.", LN_RED);
						}
					}
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					DUMB_UP(playerid);
					combine_mode[playerid][c_step] = 3;
					ShowCombineTD(playerid);
				}
			}
			else if(combine_mode[playerid][c_step] == 2)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					DUMB_DOWN(playerid);
					ShowCombineTD(playerid);
					combine_mode[playerid][c_step] = 4;
				}
			}
			else if(combine_mode[playerid][c_step] == 3)
			{
				GenerateCombine(playerid, 2);
				CombineTD_Combine(playerid, GetCombine(playerid));
				ShowCombineTD(playerid);
				combine_mode[playerid][c_step] = 2;
			}
			else if(combine_mode[playerid][c_step] == 4)
			{
				GenerateCombine(playerid);
				CombineTD_Combine(playerid, GetCombine(playerid));
				ShowCombineTD(playerid);
				combine_mode[playerid][c_step] = 1;
			}
		}
		case 3:
		{
			SetCombine_KarnetStr(playerid);
			if(combine_mode[playerid][c_step] == 1)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					if(!Karnet(playerid))
					{
						if(combine_mode[playerid][c_qkey] >= 1)
						{
							combine_mode[playerid][c_qkey] = 0;
							LeftNotifyShow(playerid, "error", "~r~Brak~w~ aktywnego karnetu! Zakup nowy karnet.", LN_RED);
						}
					}
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					TREAM_RUN(playerid);
					ShowCombineTD(playerid);
					combine_mode[playerid][c_step] = 2;
				}
			}
			else if(combine_mode[playerid][c_step] == 2)
			{
				GenerateCombine(playerid);
				CombineTD_Combine(playerid, GetCombine(playerid));
				ShowCombineTD(playerid);
				combine_mode[playerid][c_step] = 1;
			}
		}
		case 4:
		{
			SetCombine_KarnetStr(playerid);
			if(combine_mode[playerid][c_step] == 1)
			{
				if(combine_mode[playerid][c_qkey] < 6)//gdy wykonuje kombinacje...
				{
					if(!Karnet(playerid))
					{
						if(combine_mode[playerid][c_qkey] >= 1)
						{
							combine_mode[playerid][c_qkey] = 0;
							LeftNotifyShow(playerid, "error", "~r~Brak~w~ aktywnego karnetu! Zakup nowy karnet.", LN_RED);
						}
					}
					CombineTD_Combine(playerid, GetCombine(playerid));
					ShowCombineTD(playerid);
				}
				else//gdy kombinacja zostaje wykonana
				{
					CombineTD_Combine(playerid, GetCombine(playerid));
					BIKE_RUN(playerid);
					ShowCombineTD(playerid);
					combine_mode[playerid][c_step] = 2;
				}
			}
			else if(combine_mode[playerid][c_step] == 2)
			{
				GenerateCombine(playerid);
				CombineTD_Combine(playerid, GetCombine(playerid));
				ShowCombineTD(playerid);
				combine_mode[playerid][c_step] = 1;
			}
		}
	}
	return 1;
}

stock combine_OnPlayerKeyStateChange(playerid, key, axis)
{
	if(!combine_mode[playerid][c_id]) return 0;
	if(combine_mode[playerid][c_key_time] > GetTickCount()) return 0;
	new qkey = combine_mode[playerid][c_qkey];
	if(qkey >= 6) return 0;
	if(axis)//lewo prawo
	{
		if(combine_mode[playerid][c_mode] == 2)
		{
			if(key == KEY_LEFT)
			{
				combine_mode[playerid][c_key][qkey] = CKEY_LEFT;
				combine_mode[playerid][c_qkey]++;
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				Process_CombineMode(playerid);
			}
			else if(key == KEY_RIGHT)
			{
				combine_mode[playerid][c_key][qkey] = CKEY_RIGHT;
				combine_mode[playerid][c_qkey]++;
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				Process_CombineMode(playerid);
			}
		}
		else
		{
			if(key == KEY_LEFT && combine_mode[playerid][c_key][qkey] == CKEY_LEFT)
			{
				combine_mode[playerid][c_qkey]++;
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				Process_CombineMode(playerid);
			}
			else if(key == KEY_RIGHT && combine_mode[playerid][c_key][qkey] == CKEY_RIGHT)
			{
				combine_mode[playerid][c_qkey]++;
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				Process_CombineMode(playerid);
			}
			else 
			{
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				combine_mode[playerid][c_bad]++;
				GenerateCombine(playerid);
				CombineTD_Combine(playerid, "~r~X~r~X~r~X~r~X~r~X~r~X");
				ShowCombineTD(playerid);
			}
		}
	}
	else//góra dół
	{
		if(combine_mode[playerid][c_mode] == 2)
		{
			if(key == KEY_UP)
			{
				combine_mode[playerid][c_key][qkey] = CKEY_UP;
				combine_mode[playerid][c_qkey]++;
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				Process_CombineMode(playerid);
			}
			else if(key == KEY_DOWN)
			{
				combine_mode[playerid][c_key][qkey] = CKEY_DOWN;
				combine_mode[playerid][c_qkey]++;
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				Process_CombineMode(playerid);
			}
		}
		else
		{
			if(key == KEY_UP && combine_mode[playerid][c_key][qkey] == CKEY_UP)
			{
				combine_mode[playerid][c_qkey]++;
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				Process_CombineMode(playerid);
			}
			else if(key == KEY_DOWN && combine_mode[playerid][c_key][qkey] == CKEY_DOWN)
			{
				combine_mode[playerid][c_qkey]++;
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				Process_CombineMode(playerid);
			}
			else 
			{
				combine_mode[playerid][c_key_time] = GetTickCount()+150;
				combine_mode[playerid][c_bad]++;
				GenerateCombine(playerid);
				CombineTD_Combine(playerid, "~r~X~r~X~r~X~r~X~r~X~r~X");
				ShowCombineTD(playerid);
			}
		}
	}
	return 1;
}

stock GetCombine(playerid)
{
	new combine[64];
	if(combine_mode[playerid][c_mode] == 0)
	{
		for(new c; c < 6; c++)
		{
			if(c < combine_mode[playerid][c_qkey])
			{
				format(combine, 64, "%s~g~X", combine);
			}
			else
			{
				switch(combine_mode[playerid][c_key][c])
				{
					case CKEY_LEFT:
					{
						format(combine, 64, "%s~<~", combine);
					}
					case CKEY_RIGHT:
					{
						format(combine, 64, "%s~>~", combine);
					}
					case CKEY_UP:
					{
						format(combine, 64, "%s~u~", combine);
					}
					case CKEY_DOWN:
					{
						format(combine, 64, "%s~d~", combine);
					}
				}
			}
		}
	}
	else if(combine_mode[playerid][c_mode] == 1)
	{
		for(new c; c < 6; c++)
		{
			if(c >= combine_mode[playerid][c_qkey])
			{
				format(combine, 64, "%s~p~X", combine);
			}
			else
			{
				switch(combine_mode[playerid][c_key][c])
				{
					case CKEY_LEFT:
					{
						format(combine, 64, "%s~<~", combine);
					}
					case CKEY_RIGHT:
					{
						format(combine, 64, "%s~>~", combine);
					}
					case CKEY_UP:
					{
						format(combine, 64, "%s~u~", combine);
					}
					case CKEY_DOWN:
					{
						format(combine, 64, "%s~d~", combine);
					}
				}
			}
		}
	}
	else if(combine_mode[playerid][c_mode] == 2)
	{
		for(new c; c < 6; c++)
		{
			if(c >= combine_mode[playerid][c_qkey])
			{
				format(combine, 64, "%s~y~X", combine);
			}
			else
			{
				switch(combine_mode[playerid][c_key][c])
				{
					case CKEY_LEFT:
					{
						format(combine, 64, "%s~<~", combine);
					}
					case CKEY_RIGHT:
					{
						format(combine, 64, "%s~>~", combine);
					}
					case CKEY_UP:
					{
						format(combine, 64, "%s~u~", combine);
					}
					case CKEY_DOWN:
					{
						format(combine, 64, "%s~d~", combine);
					}
				}
			}
		}
	}
	return combine;
}

stock GenerateCombine(playerid, difficulty = 4)
{
	combine_mode[playerid][c_qkey] = 0;
	if(combine_mode[playerid][c_mode] == 1) return 0;
	for(new k; k < 6; k++)
	{
		combine_mode[playerid][c_key][k] = MRandRange(1, difficulty);
	}
	return 1;
}

stock SetCombine(playerid, k1, k2, k3, k4, k5, k6)
{
	combine_mode[playerid][c_qkey] = 0;
	combine_mode[playerid][c_key][0] = k1;
	combine_mode[playerid][c_key][1] = k2;
	combine_mode[playerid][c_key][2] = k3;
	combine_mode[playerid][c_key][3] = k4;
	combine_mode[playerid][c_key][4] = k5;
	combine_mode[playerid][c_key][5] = k6;
	return 1;
}