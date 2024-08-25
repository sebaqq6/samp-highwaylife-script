stock Init_TransportCourier()
{
	new strTemp[128];
	for(new c = sizeof(courier_data)-1; c != -1; c--)
	{
		format(strTemp, 128, "« Załadunek paczek firmy: %s »\n"COL_GREY"((TIP: Podjedź tyłem, będzie prościej ładować.))", courier_data[c][cd_name]);
		CreateDynamic3DTextLabel(strTemp, courier_data[c][cd_color], courier_data[c][cd_pX], courier_data[c][cd_pY], courier_data[c][cd_pZ], 50.0);
	}
	return 1;
}

task Process_CourierJob(playerid, force)
{
	if(gracz[playerid][courier_job] != 0)
	{
		new cvid = gracz[playerid][courier_job_vehicleid];
		if((pojazd[cvid][v_owner_type] == VEHICLE_PUBLIC && pojazd[cvid][v_owner] == gracz[playerid][courier_job]) || force == 1)
		{
			new Float:vPos[3];
			GetVehiclePos(cvid, vPos[0], vPos[1], vPos[2]);
			if((!IsPlayerInRangeOfPoint(playerid, 50.0, vPos[0], vPos[1], vPos[2]) && GetPlayerVirtualWorld(playerid) == 0) || force == 1)
			{
				gracz[playerid][courier_job] = 0;
				if(gracz[playerid][courier_job_status] == 3)
				{
					if(gracz[playerid][courier_job_pickup] > 0)
					{
						DestroyPickup(gracz[playerid][courier_job_pickup]);
						gracz[playerid][courier_job_pickup] = 0;
					}
					DestroyDynamic3DTextLabel(gracz[playerid][courier_job_3dtext]);
				}
				RemovePlayerAttachedObject(playerid, 0);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				gracz[playerid][courier_job_status] = 0;
				gracz[playerid][courier_job_vehicleid] = 0;
				LeftNotifyShow(playerid, "Zwolnienie", "Zostales automatycznie zwolniony z pracy kuriera, gdyz oddaliles sie od swojego pojazdu firmowego na dalej niz 50m.", LN_RED, 10);
				HideRightMessageBox(playerid);
				DisablePlayerCheckpoint(playerid);
				RespawnVehicle(cvid, true);
				StopRouteGPS(playerid);
				if(gracz[playerid][courier_job_actor] != -1) DestroyActor(gracz[playerid][courier_job_actor]);
				gracz[playerid][courier_job_actor] = -1;
			}
		}
		if(gracz[playerid][courier_job_actor] != -1 && gracz[playerid][courier_job_status] == 6)
		{
			new clientid = gracz[playerid][courier_job_clientid];
			SetActorPos(gracz[playerid][courier_job_actor], courier_clients[clientid][0], courier_clients[clientid][1], courier_clients[clientid][2]);
			if(IsPlayerInRangeOfPoint(playerid, 25.0, courier_clients[clientid][0], courier_clients[clientid][1], courier_clients[clientid][2]))
			{
				ShowRightMessageBox(playerid, "Praca kuriera", "~y~Wysiadz z pojazdu~w~ i zanies paczke dla ~g~klienta~w~.");
				ApplyActorAnimation(gracz[playerid][courier_job_actor], "ON_LOOKERS", "wave_loop", 4.0, 1, 0, 0, 0, 0);
			}
			else
			{
				new strTemp[512];
				format(strTemp, 512, "Rozwiez klientom paczki. Klientow masz oznaczonych ~r~czerwonym markerem~w~ na minimapie. ~n~~n~Paczek: ~g~%d~w~/~r~%d~w~~n~~n~((jesli chcesz sie zwolnic, oddal sie od swojego pojazdu firmowego na wiecej niz 50m))" , pojazd[cvid][v_cargo_amount], MAX_COURIERPACK);
				ShowRightMessageBox(playerid, "Praca kuriera", strTemp);
				ClearActorAnimations(gracz[playerid][courier_job_actor]);
			}
		}
	}
	return 1;
}


stock Courier_Event(playerid, event_type)
{
	new vehicleid = GetPlayerVehicleID(playerid);
	new strTemp[512];
	if(event_type == 1)//wejście do pojazdu
	{
		if(gracz[playerid][courier_job] == 0)
		{
			for(new c = sizeof(courier_data)-1; c != -1; c--)//ustawienie pracy dla gracza kuriera
			{
				if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == courier_data[c][cd_cid])
				{
					if(IsPlayerOnDutyFraction(playerid)) return Error(playerid, "Jesteś na służbie.");
					if(TruckerWhileOrderCheck(playerid)) return Error(playerid, "Jesteś podczas zlecenia. Aby je anulować wpisz: "COL_ORANGE"/zlecenie anuluj"COL_WHITE".");
					StopRouteGPS(playerid);//usuwa buga z gps po relogu
					gracz[playerid][courier_job] = courier_data[c][cd_cid];
					gracz[playerid][courier_job_vehicleid] = vehicleid;
					gracz[playerid][courier_job_status] = 1;
					gracz[playerid][courier_job_actor] = -1;
					pojazd[vehicleid][v_cargo_amount] = 0;
					pojazd[vehicleid][v_cargo] = 0;
					format(strTemp, 512, "Zostales automatycznie zatrudniony w firmie kurieskiej ~y~%s~w~. Zostales tymczasowym wlascicielem pojazdu firmowego, w ktorym sie znajdujesz. Jesli chcesz sie zwolnic - oddal sie od swojego pojazdu firmowego na dalej niz 50m.", courier_data[c][cd_name]);
					LeftNotifyShow(playerid, "Zatrudnienie", strTemp, LN_BLUE, 30);
					ShowRightMessageBox(playerid, "Praca kuriera", "Jestes zatrudniony jako kurier. Aby rozpoczac prace musisz zapakowac do swojego pojazdu ~y~paczki kurierskie~w~. Mozesz to zrobic w magazynie, magazyn zostal oznaczony ~r~czerwonym markerem~w~ na minimapie. ~n~~n~((jesli chcesz sie zwolnic, oddal sie od swojego pojazdu firmowego na wiecej niz 50m))");
					SetPlayerCheckpoint(playerid, courier_data[c][cd_pX], courier_data[c][cd_pY], courier_data[c][cd_pZ], 5.0);
					break;
				}
			}
		}
		else//jest już zatrudniony
		{
			if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == gracz[playerid][courier_job] && vehicleid == gracz[playerid][courier_job_vehicleid])
			{
				if(gracz[playerid][courier_job_status] == 2)
				{
					ShowRightMessageBox(playerid, "Praca kuriera", "Jestes zatrudniony jako kurier. Aby kontynuowac prace musisz zapakowac do swojego pojazdu ~y~paczki kurierskie~w~. Mozesz to zrobic w magazynie, magazyn zostal oznaczony ~r~czerwonym markerem~w~ na minimapie. ~n~~n~((jesli chcesz sie zwolnic, oddal sie od swojego pojazdu firmowego na wiecej niz 50m))");
					gracz[playerid][courier_job_status] = 1;
					for(new c = sizeof(courier_data)-1; c != -1; c--)
					{
						if(courier_data[c][cd_cid] == gracz[playerid][courier_job]) 
						{
							SetPlayerCheckpoint(playerid, courier_data[c][cd_pX], courier_data[c][cd_pY], courier_data[c][cd_pZ], 5.0);
							break;
						}
					}
				}
				else if(gracz[playerid][courier_job_status] == 3)
				{
					ShowRightMessageBox(playerid, "Praca kuriera", "~r~Twoj pojazd firmowy nie jest zapakowany do pelna!~g~ Zapakuj~w~ pojazd pobierajac paczki z magazynu (~r~czerwony marker~w~).");
					for(new c = sizeof(courier_data)-1; c != -1; c--)
					{
						if(courier_data[c][cd_cid] == gracz[playerid][courier_job]) 
						{
							SetPlayerCheckpoint(playerid, courier_data[c][cd_pX2], courier_data[c][cd_pY2], courier_data[c][cd_pZ2], 1.5);
							break;
						}
					}
				}
				else if(gracz[playerid][courier_job_status] == 5)
				{
					gracz[playerid][courier_job_status] = 6;
					format(strTemp, 512, "Rozwiez klientom paczki. Klientow masz oznaczonych ~r~czerwonym markerem~w~ na minimapie. ~n~~n~Paczek: ~g~%d~w~/~r~%d~w~~n~~n~((jesli chcesz sie zwolnic, oddal sie od swojego pojazdu firmowego na wiecej niz 50m))" , pojazd[vehicleid][v_cargo_amount], MAX_COURIERPACK);
					ShowRightMessageBox(playerid, "Praca kuriera", strTemp);
					new clientid = gracz[playerid][courier_job_clientid];
					if(gracz[playerid][courier_job_actor] == -1)//-1 == brak aktora, brak klienta
					{
						new potential_clients[MAX_COURIERCLIENTS];
						new pc_counter;
						for(new c = MAX_COURIERCLIENTS-1; c != -1; c--)
						{
							if(!IsPlayerInRangeOfPoint(playerid, 500.0, courier_clients[c][0], courier_clients[c][1], courier_clients[c][2]))
							{
								if(pc_counter < MAX_COURIERCLIENTS)
								{
									potential_clients[pc_counter] = c;
									//printf("potential_clients[%d] = %d", pc_counter, c);
									pc_counter++;
								}
								else break;
							}
						}
						pc_counter--;//-1, żeby nie przekroczyło wielkości zmiennej
						new random_pc =  random(pc_counter);
						gracz[playerid][courier_job_clientid] = potential_clients[random_pc];
						//printf("random_pc: %d | clientid = %d", random_pc, gracz[playerid][courier_job_clientid] );
						clientid = gracz[playerid][courier_job_clientid];
						gracz[playerid][courier_job_actor] = CreateActor(courier_clients_skins[random(sizeof(courier_clients_skins))], courier_clients[clientid][0], courier_clients[clientid][1], courier_clients[clientid][2], courier_clients[clientid][3]);
						StartRouteGPS(playerid, courier_clients[clientid][0], courier_clients[clientid][1], courier_clients[clientid][2]);
					}
					SetPlayerCheckpoint(playerid, courier_clients[clientid][0], courier_clients[clientid][1], courier_clients[clientid][2], 2.0);
					pojazd[vehicleid][v_cargo_target_X] = courier_clients[clientid][0];
					pojazd[vehicleid][v_cargo_target_Y] = courier_clients[clientid][1];
					pojazd[vehicleid][v_cargo_target_Z] = courier_clients[clientid][2];
					pojazd[vehicleid][v_cargo_price] = COURIER_PACK_PRICE; 
				}
			}
		}
	}
	else if(event_type == 2)//wyjście z pojazdu
	{
		if(gracz[playerid][courier_job] != 0) 
		{
			new cvid = gracz[playerid][courier_job_vehicleid];
			if(pojazd[cvid][v_owner_type] == VEHICLE_PUBLIC && pojazd[cvid][v_owner] == gracz[playerid][courier_job] && gracz[playerid][last_vehicleid] == cvid)
			{
				new Float:vPos[3];
				GetVehiclePos(cvid, vPos[0], vPos[1], vPos[2]);
				if(gracz[playerid][courier_job_status] == 1)
				{
					ShowRightMessageBox(playerid, "Praca kuriera", "Jestes zatrudniony jako kurier. Aby kontynuowac prace, wroc do swojego pojazdu firmowego - zostal on zaznaczony ~r~czerwonym markerem~w~ na minimapie. ~n~~n~((jesli chcesz sie zwolnic, oddal sie od swojego pojazdu firmowego na wiecej niz 50m))");
					SetPlayerCheckpoint(playerid, vPos[0], vPos[1], vPos[2], 5.0);
					gracz[playerid][courier_job_status] = 2;
				}
				else if(gracz[playerid][courier_job_status] == 6)
				{
					if(gracz[playerid][courier_job_actor] != -1)
					{
						new clientid = gracz[playerid][courier_job_clientid];
						if(IsPlayerInRangeOfPoint(playerid, 25.0, courier_clients[clientid][0], courier_clients[clientid][1], courier_clients[clientid][2]))
						{
							SetPlayerAttachedObject(playerid, 0, 2912, 1, 0.321000, 0.545000, -0.372999);
							SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
							ShowRightMessageBox(playerid, "Praca kuriera", "~y~Zanies paczke~w~ dla ~b~klienta~r~(czerwony marker)~w~. ~n~~n~((jesli chcesz sie zwolnic, oddal sie od swojego pojazdu firmowego na wiecej niz 50m))");
							gracz[playerid][courier_job_status] = 7;
							return 1;
						}
					}
					gracz[playerid][courier_job_status] = 5;
					ShowRightMessageBox(playerid, "Praca kuriera", "Wroc do swojego pojazdu firmowego - zostal on zaznaczony ~r~czerwonym markerem~w~ na minimapie. Nastepnie rozwiez paczki klientom. ~n~~n~((jesli chcesz sie zwolnic, oddal sie od swojego pojazdu firmowego na wiecej niz 50m))");
					SetPlayerCheckpoint(playerid, vPos[0], vPos[1], vPos[2], 5.0);
				}
			}
		}
	}
	else if(event_type == 3)//zebranie CP
	{
		if(gracz[playerid][courier_job] != 0) 
		{
			new cvid = gracz[playerid][courier_job_vehicleid];
			if(pojazd[cvid][v_owner_type] == VEHICLE_PUBLIC && pojazd[cvid][v_owner] == gracz[playerid][courier_job])
			{
				if((!IsPlayerInVehicle(playerid, cvid) && (gracz[playerid][courier_job_status] == 2 || gracz[playerid][courier_job_status] == 5 || gracz[playerid][courier_job_status] == 7)) || gracz[playerid][courier_job_status] == 6)
				{
					if(gracz[playerid][courier_job_status] == 7)
					{
						if(pojazd[cvid][v_cargo_amount] > 0)
						{
							RemovePlayerAttachedObject(playerid, 0);
							SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
							gracz[playerid][courier_job_status] = 5;
							new Float:vPos[3];
							GetVehiclePos(cvid, vPos[0], vPos[1], vPos[2]);
							SetPlayerCheckpoint(playerid, vPos[0], vPos[1], vPos[2], 5.0);
							new cprice;
							if(Money(playerid) > strval(COURIER_MONEYTIME) || gracz[playerid][bank_saldo] > strval(COURIER_MONEYTIME)) cprice = 40;
							else cprice = COURIER_PACK_PRICE;
							GiveMoney(playerid, cprice);
							GiveKurs(playerid, 1);
							if(gracz[playerid][courier_job_actor] != -1) DestroyActor(gracz[playerid][courier_job_actor]);
							gracz[playerid][courier_job_actor] = -1;
							pojazd[cvid][v_cargo_amount]--;
							if(pojazd[cvid][v_cargo_amount] <= 0)
							{
								ShowRightMessageBox(playerid, "Praca kuriera", "Jestes zatrudniony jako kurier. Aby kontynuowac prace, wroc do swojego pojazdu firmowego - zostal on zaznaczony ~r~czerwonym markerem~w~ na minimapie. ~n~~n~((jesli chcesz sie zwolnic, oddal sie od swojego pojazdu firmowego na wiecej niz 50m))");
								gracz[playerid][courier_job_status] = 2;
								pojazd[cvid][v_cargo_amount] = 0;
								pojazd[cvid][v_cargo] = 0;
								GiveScore(playerid, 1);
								format(strTemp, 128,  "~g~DOSTARCZONO!~n~~p~+%d$~n~~b~+1 SCORE", cprice);
								GameTextForPlayer(playerid, strTemp,  3000, 4);
								StopRouteGPS(playerid);
							}
							else
							{
								format(strTemp, 128,  "~g~DOSTARCZONO!~n~~p~+%d$", cprice);
								GameTextForPlayer(playerid, strTemp,  3000, 4);
								ShowRightMessageBox(playerid, "Praca kuriera", "Wroc do swojego pojazdu firmowego - zostal on zaznaczony ~r~czerwonym markerem~w~ na minimapie. Nastepnie rozwiez paczki klientom. ~n~~n~((jesli chcesz sie zwolnic, oddal sie od swojego pojazdu firmowego na wiecej niz 50m))");
							}
						}
					}
					return 2;
				}
				else if((IsPlayerInVehicle(playerid, cvid) && gracz[playerid][courier_job_status] == 1) || gracz[playerid][courier_job_status] == 4)
				{
					if(gracz[playerid][courier_job_status] == 4)
					{
						if(pojazd[cvid][v_cargo_amount] < MAX_COURIERPACK)
						{
							pojazd[cvid][v_cargo_amount]++;
							pojazd[cvid][v_cargo] = 1;
							pojazd[cvid][v_cargo_price] = COURIER_PACK_PRICE; 
							format(strTemp, 512, "~g~PACZKA ZAPAKOWANA!~n~%d/~r~%d", pojazd[cvid][v_cargo_amount], MAX_COURIERPACK);
							GameTextForPlayer(playerid, strTemp,  3000, 4);
							RemovePlayerAttachedObject(playerid, 0);
							SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
							if(pojazd[cvid][v_cargo_amount] >= MAX_COURIERPACK)//zaladowany do pelna
							{
								gracz[playerid][courier_job_status] = 5;
								ShowRightMessageBox(playerid, "Praca kuriera", "Wroc do swojego pojazdu firmowego - zostal on zaznaczony ~r~czerwonym markerem~w~ na minimapie. Nastepnie rozwiez paczki klientom. ~n~~n~((jesli chcesz sie zwolnic, oddal sie od swojego pojazdu firmowego na wiecej niz 50m))");
								new Float:vPos[3];
								GetVehiclePos(cvid, vPos[0], vPos[1], vPos[2]);
								SetPlayerCheckpoint(playerid, vPos[0], vPos[1], vPos[2], 5.0);
								return 2;//zapobieganie zniknieciu cp
							}
						}
					}
					for(new c = sizeof(courier_data)-1; c != -1; c--)
					{
						if(courier_data[c][cd_cid] == gracz[playerid][courier_job]) 
						{
							if(IsPlayerInVehicle(playerid, cvid))
							{
								SetVehicleVelocity(vehicleid, 0.0, 0.0, 0.0);
								//RemovePlayerFromVehicle(playerid);
							}
							SetPlayerCheckpoint(playerid, courier_data[c][cd_pX2], courier_data[c][cd_pY2], courier_data[c][cd_pZ2], 1.5);
							gracz[playerid][courier_job_status] = 3;
							gracz[playerid][courier_job_pickup] = CreatePickup(2912, 1, courier_data[c][cd_pX2], courier_data[c][cd_pY2], courier_data[c][cd_pZ2]-0.5, -1);
							gracz[playerid][courier_job_3dtext] = CreateDynamic3DTextLabel("*** paczka ***", courier_data[c][cd_color], courier_data[c][cd_pX2], courier_data[c][cd_pY2], courier_data[c][cd_pZ2]-0.5, 30.0, .playerid = playerid);
							format(strTemp, 512, "~g~Odbierz paczke~w~ z magazynu - wejdz w pickup pudelka (~r~czerwony marker~w~).~n~~n~Zapakowano: ~g~%d~w~/~r~%d~w~", pojazd[cvid][v_cargo_amount], MAX_COURIERPACK);
							ShowRightMessageBox(playerid, "Praca kuriera", strTemp);
							break;
						}
					}
				}
			}
		}
	}
	else if(event_type == 4)//wejscie w pickup
	{
		if(gracz[playerid][courier_job] != 0 && !IsPlayerInAnyVehicle(playerid)) 
		{
			new cvid = gracz[playerid][courier_job_vehicleid];
			new Float:vPos[3];
			GetVehiclePos(cvid, vPos[0], vPos[1], vPos[2]);
			if(IsPlayerInRangeOfPoint(playerid, 8.0, vPos[0], vPos[1], vPos[2]))
			{
				Error(playerid, "Twój pojazd firmowy stoi za blisko miejsca odbioru paczki (pickup'a).");
			}
			else
			{
				gracz[playerid][courier_job_status] = 4;
				if(gracz[playerid][courier_job_pickup] > 0)
				{
					DestroyPickup(gracz[playerid][courier_job_pickup]);
					gracz[playerid][courier_job_pickup] = 0;
				}
				DestroyDynamic3DTextLabel(gracz[playerid][courier_job_3dtext]);
				SetPlayerAttachedObject(playerid, 0, 2912, 1, 0.321000, 0.545000, -0.372999);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
				GetXYInBackOfVehicle(cvid, vPos[0], vPos[1], 3.3);
				SetPlayerCheckpoint(playerid, vPos[0], vPos[1], vPos[2], 2.0);
				format(strTemp, 512, "~g~Zanies paczke~w~ do swojego pojazdu firmowego (~r~czerwony marker~w~).~n~~n~Zapakowano: ~g~%d~w~/~r~%d~w~", pojazd[cvid][v_cargo_amount], MAX_COURIERPACK);
				ShowRightMessageBox(playerid, "Praca kuriera", strTemp);
			}
		}
	}
	return 1;
}