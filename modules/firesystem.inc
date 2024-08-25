#define MAX_FIRES 200
#define MAX_FIREHP 5
enum fire_data
{
	fire_id,
	fire_hp,
	Float:fire_X,
	Float:fire_Y,
	Float:fire_Z,
	fire_object,
	Text3D:fire_label
};

new fire[MAX_FIRES][fire_data];

stock CreateFire(Float:fireX, Float:fireY, Float:fireZ)
{
	for(new f; f < MAX_FIRES; f++)
	{
		if(fire[f][fire_object] == 0)//wolny slot
		{
			fire[f][fire_id] = f;
			fire[f][fire_hp] = MAX_FIREHP;
			fire[f][fire_X] = fireX;
			fire[f][fire_Y] = fireY;
			fire[f][fire_Z] = fireZ;
			fire[f][fire_object] = CreateDynamicObject(18690, fireX, fireY, fireZ-3.0, 0.0, 0.0, 0.0);
			new strTemp[255];
			for(new hp; hp < fire[f][fire_hp]; hp++)
			{
				format(strTemp, 255, "%s•", strTemp);
			}
			fire[f][fire_label] = CreateDynamic3DTextLabel(strTemp, 0xFF0000DD, fireX, fireY, fireZ, 35.0);
			return f;
		}
	}
	return -1;
}

stock DestroyAllFires()
{
	for(new f; f < MAX_FIRES; f++)
	{
		DestroyFire(f);
	}
	return 1;
}

stock CountFires()
{
	new wynik;
	for(new f; f < MAX_FIRES; f++)
	{
		if(fire[f][fire_object] != 0) wynik ++;
	}
	return wynik;
}


stock DestroyFire(fireid)
{
	if(fire[fireid][fire_object] != 0)//istnieje
	{
		DestroyDynamicObject(fire[fireid][fire_object]);
		DestroyDynamic3DTextLabel(fire[fireid][fire_label]);
		for(new fire_data:fd; fd < fire_data; fd++)//czyszczenie zmiennych
		{
			fire[fireid][fd] = 0;
		}
		return 1;
	}
	return 0;
}

CMD:pozar(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 3) return 1;
	DestroyAllFires();
	new Float:randPos[3];
	for(new ff; ff < 50; ff++)
	{
		MRandFloatRange(0, 10.0, randPos[0]);
		MRandFloatRange(0, 10.0, randPos[1]);
		randPos[0] += gracz[playerid][PosX];
		randPos[1] += gracz[playerid][PosY];
		MapAndreas_FindZ_For2DCoord(randPos[0], randPos[1], randPos[2]);
		CreateFire(randPos[0], randPos[1], randPos[2]+1.2);
	}
	Info(playerid, "Stworzyłeś pożar.");
	printf("pozar: %f, %f, %f - %s", gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], params);
	return 1;
}

stock StworzPozar(Float:pozarX, Float:pozarY)
{
	DestroyAllFires();
	new Float:randPos[3];
	for(new ff; ff < 50; ff++)
	{
		MRandFloatRange(0, 10.0, randPos[0]);
		MRandFloatRange(0, 10.0, randPos[1]);
		randPos[0] += pozarX;
		randPos[1] += pozarY;
		MapAndreas_FindZ_For2DCoord(randPos[0], randPos[1], randPos[2]);
		CreateFire(randPos[0], randPos[1], randPos[2]+1.2);
	}
	return 1;
}

task Process_ExtinguishingFire(playerid)
{
	if(gracz[playerid][frakcja] != F_EMERGENCY) return 1;
	if(IsPlayerAFK(playerid)) return 1;
	GetPlayerKeys(playerid, gracz[playerid][gpk_keys],  gracz[playerid][gpk_updown],  gracz[playerid][gpk_leftright]);
	if(IsHelicopterUseWater(gracz[playerid][opu_vehicleid]))//gaszenie helikopterem
	{
		new max_per_tick;
		new bool:find_object_fire = false;
		for(new f; f < MAX_FIRES; f++)
		{
			if(fire[f][fire_object] == 0) continue;
			if(GetDistanceBetweenPoints(fire[f][fire_X], fire[f][fire_Y], fire[f][fire_Z], gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]-15.0) < 15.0)
			{
				if(fire[f][fire_hp] > 1)
				{
					fire[f][fire_hp]--;
					new strTemp[32];
					for(new hp; hp < fire[f][fire_hp]; hp++)
					{
						format(strTemp, 32, "%s•", strTemp);
					}
					if((fire[f][fire_hp]-1) == 0) UpdateDynamic3DTextLabelText(fire[f][fire_label], 0x999999DD, strTemp);
					else UpdateDynamic3DTextLabelText(fire[f][fire_label], 0x009933DD, strTemp);
					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~g~GASZENIE...", 1000, 3);
					DisablePlayerCheckpoint(playerid);
				}
				else
				{
					DestroyFire(f);
					GameTextForPlayer(playerid, "~g~+100$", 5000, 3);
					GiveMoney(playerid, 100);
					GiveFractionMoneyOrScore(F_EMERGENCY, 0, 100);
				}
				find_object_fire = true;
				max_per_tick++;
				if(max_per_tick > 3) break;
			}
		}
		//gaszenie pojazdów
		if(find_object_fire == false)
		{
			for(new v = GetVehiclePoolSize(); v != -1; v--)
			{
				if(pojazd[v][v_model] == 0) continue;
				if(pojazd[v][v_object][12] != 0)
				{
					new Float:vPos[3];
					GetVehiclePos(v, vPos[0], vPos[1], vPos[2]);
					if(GetDistanceBetweenPoints(vPos[0], vPos[1], vPos[2], gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ]-15.0) < 15.0)
					{
						if(pojazd[v][v_fire_hp] > 1)
						{
							pojazd[v][v_fire_hp]--;
							pojazd[v][v_fire_warn] = 0;
							GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~g~GASZENIE...", 1000, 3);
						}
						else
						{
							pojazd[v][v_fire_hp] = 0;
							if(pojazd[v][v_adr_warn] > 2) pojazd[v][v_adr_warn] = 2;
							DestroyDynamicObject(pojazd[v][v_object][12]);
							pojazd[v][v_object][12] = 0;
							GameTextForPlayer(playerid, "~g~+1000$", 5000, 3);
							GiveMoney(playerid, 1000);
							GiveFractionMoneyOrScore(F_EMERGENCY, 0, 1000);
						}
					}
				}
			}
		}
		return 1;
	}
	if(gracz[playerid][gpk_keys] != KEY_FIRE) return 1;

	if(pojazd[gracz[playerid][opu_vehicleid]][v_model] == 407)//firetruck
	{
		new
		Float:fPX, Float:fPY, Float:fPZ,
		Float:fVX, Float:fVY, Float:fVZ,
		Float:ctarget_x, Float:ctarget_y;
		
		const Float:fScale = 30.0;
	
		GetPlayerCameraPos(playerid, fPX, fPY, fPZ);
		GetPlayerCameraFrontVector(playerid, fVX, fVY, fVZ);
	
		ctarget_x = fPX + floatmul(fVX, fScale);
		ctarget_y = fPY + floatmul(fVY, fScale);

		new max_per_tick;
		new bool:find_object_fire = false;
		for(new f; f < MAX_FIRES; f++)
		{
			if(fire[f][fire_object] == 0) continue;
			if(GetDistanceBetweenPoints(fire[f][fire_X], fire[f][fire_Y], fire[f][fire_Z], ctarget_x, ctarget_y, fire[f][fire_Z]) < 12.0)
			{
				if(fire[f][fire_hp] > 1)
				{
					fire[f][fire_hp]--;
					new strTemp[32];
					for(new hp; hp < fire[f][fire_hp]; hp++)
					{
						format(strTemp, 32, "%s•", strTemp);
					}
					if((fire[f][fire_hp]-1) == 0) UpdateDynamic3DTextLabelText(fire[f][fire_label], 0x999999DD, strTemp);
					else UpdateDynamic3DTextLabelText(fire[f][fire_label], 0x009933DD, strTemp);
					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~g~GASZENIE...", 1000, 3);
					DisablePlayerCheckpoint(playerid);
				}
				else
				{
					DestroyFire(f);
					GameTextForPlayer(playerid, "~g~+100$", 5000, 3);
					GiveFractionMoneyOrScore(F_EMERGENCY, 0, 100);
					GiveMoney(playerid, 100);
				}
				find_object_fire = true;
				max_per_tick++;
				if(max_per_tick > 3) break;
			}
		}
		//gaszenie pojazdów
		if(find_object_fire == false)
		{
			for(new v = GetVehiclePoolSize(); v != -1; v--)
			{
				if(pojazd[v][v_model] == 0) continue;
				if(pojazd[v][v_object][12] != 0)
				{
					new Float:vPos[3];
					GetVehiclePos(v, vPos[0], vPos[1], vPos[2]);
					if(GetDistanceBetweenPoints(vPos[0], vPos[1], vPos[2], ctarget_x, ctarget_y, vPos[2]) < 12.0)
					{
						if(pojazd[v][v_fire_hp] > 1)
						{
							pojazd[v][v_fire_hp]--;
							pojazd[v][v_fire_warn] = 0;
							GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~g~GASZENIE...", 1000, 3);
						}
						else
						{
							pojazd[v][v_fire_hp] = 0;
							if(pojazd[v][v_adr_warn] > 2) pojazd[v][v_adr_warn] = 2;
							DestroyDynamicObject(pojazd[v][v_object][12]);
							pojazd[v][v_object][12] = 0;
							GameTextForPlayer(playerid, "~g~+1000$", 5000, 3);
							GiveFractionMoneyOrScore(F_EMERGENCY, 0, 1000);
							GiveMoney(playerid, 1000);
						}
					}
				}
			}
		}
	}
	else if(GetPlayerWeapon(playerid) == WEAPON_FIREEXTINGUISHER)//gaśnica
	{
		for(new f; f < MAX_FIRES; f++)
		{
			if(fire[f][fire_object] == 0) continue;
			if(GetDistanceBetweenPoints(fire[f][fire_X], fire[f][fire_Y], fire[f][fire_Z], gracz[playerid][PosX], gracz[playerid][PosY], fire[f][fire_Z]) < 2.0)
			{
				if(fire[f][fire_hp] > 1)
				{
					fire[f][fire_hp]--;
					new strTemp[32];
					for(new hp; hp < fire[f][fire_hp]; hp++)
					{
						format(strTemp, 32, "%s•", strTemp);
					}
					if((fire[f][fire_hp]-1) == 0) UpdateDynamic3DTextLabelText(fire[f][fire_label], 0x999999DD, strTemp);
					else UpdateDynamic3DTextLabelText(fire[f][fire_label], 0x009933DD, strTemp);
					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~g~GASZENIE...", 1000, 3);
					DisablePlayerCheckpoint(playerid);
				}
				else
				{
					DestroyFire(f);
					GameTextForPlayer(playerid, "~g~+100$", 5000, 3);
					GiveFractionMoneyOrScore(F_EMERGENCY, 0, 100);
					GiveMoney(playerid, 100);
				}
				return 1;
			}
		}
	}
	return 1;
}

task Process_Pozary()
{
	if(CountFires() > 0)//pożar istnieje
	{
		pozar_timestamp = serwer[time_timestamp]+(60*FIRES_FREQUENCY);//reset timera do nastepnego pożaru
		//---------
		//dodawanie wezwania jeśli go nie ma
		new bool:find_firecall = false;
		for(new c; c < MAX_CALLS; c++)
		{
			if(calls[c][call_type] == 0) continue;
			if(calls[c][call_fraction] == F_EMERGENCY)
			{
				if(calls[c][call_type] == 2)//pożar
				{
					find_firecall = true;//znaleziono
					break;
				}
			}
		}
		if(!find_firecall) NewCall(F_EMERGENCY, -1, 2, "Pożar", potencjalne_pozary[pozar_kolejka][0], potencjalne_pozary[pozar_kolejka][1], potencjalne_pozary[pozar_kolejka][2]);//jeśli nie ma, to dodajemy
		//----------
	}
	else//pożar nie istnieje
	{
		//---------
		//usuwanie pożaru z wezwania
		for(new c; c < MAX_CALLS; c++)
		{
			if(calls[c][call_type] == 0) continue;
			if(calls[c][call_fraction] == F_EMERGENCY)
			{
				if(calls[c][call_type] == 2)//pożar
				{
					calls[c][call_status] = 0;
					calls[c][call_type] = 0;
					break;
				}
			}
		}
		//----------
		//inicjacja nowego pożaru
		if(pozar_timestamp < serwer[time_timestamp])
		{
			if(pozar_kolejka < sizeof(potencjalne_pozary)-1) pozar_kolejka++;
			else pozar_kolejka = 0;
			pozar_timestamp = serwer[time_timestamp]+(60*FIRES_FREQUENCY);
			StworzPozar(potencjalne_pozary[pozar_kolejka][0], potencjalne_pozary[pozar_kolejka][1]);
		}
	}
	return 1;
}
/*
CMD:camtest(playerid, params[])
{
	new
	Float:fPX, Float:fPY, Float:fPZ,
	Float:fVX, Float:fVY, Float:fVZ,
	Float:object_x, Float:object_y, Float:object_z;

	// Change me to change the scale you want. A larger scale increases the distance from the camera.
	// A negative scale will inverse the vectors and make them face in the opposite direction.
	const
	Float:fScale = 20.0;

	GetPlayerCameraPos(playerid, fPX, fPY, fPZ);
	GetPlayerCameraFrontVector(playerid, fVX, fVY, fVZ);

	object_x = fPX + floatmul(fVX, fScale);
	object_y = fPY + floatmul(fVY, fScale);
	object_z = fPZ + floatmul(fVZ, fScale);

	CreateObject(345, object_x, object_y, object_z, 0.0, 0.0, 0.0);

	return 1;
}*/