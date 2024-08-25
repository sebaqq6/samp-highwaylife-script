#define NPCROLE_FREE 0
#define NPCROLE_TRAIN 1
#define NPCROLE_CITIZEN 2
#define NPCROLE_CITIZENR 3
#define NPCROLE_TAXIPASS 4

#define MAX_CITIZENS 150

enum npc_data
{
	bool:npc_created,
	Text3D:npc_nicklabel,
	npc_role,
	npc_node_id,
	npc_node_vehnodes,
	npc_node_pednodes, 
	npc_node_navinodes,
	npc_node_point,
	npc_node_playtime,
	npc_firstrun,
	bool:npc_perfect,
	npc_freezeplayerid,
	bool:npc_wenterveh,
	bool:npc_wexitveh,
	bool:npc_useanim,
	npc_vehicle,
	Float:npc_taxi_tX,
	Float:npc_taxi_tY,
	Float:npc_taxi_tZ,
	npc_taxi_price,
	npc_halotaxi_timestamp,
	npc_taxi_deltime
};
new NPC[MAX_PLAYERS][npc_data];

new train[100];

//#define START_TRAINS 1000*60*3
#define ONE_TRAIN_STR 1000

#define MAX_NPCPNODES 80
new npc_perfectnodes_time[MAX_NPCPNODES];
new npc_perfectnodes[80][2] =
{
	{63, 1083},
	{55, 1141},
	{63, 472},
	{62, 706},
	{63, 621},
	{55, 591},
	{55, 736},
	{55, 1138},
	{62, 623},
	{62, 704},
	{63, 948},
	{62, 632},
	{63, 461},
	{62, 603},
	{55, 735},
	{62, 624},
	{63, 1309},
	{63, 433},
	{63, 584},
	{55, 778},
	{63, 543},
	{63, 540},
	{63, 612},
	{63, 428},
	{63, 1285},
	{62, 853},
	{55, 652},
	{62, 728},
	{55, 769},
	{62, 666},
	{63, 1102},
	{63, 980},
	{55, 543},
	{55, 573},
	{63, 673},
	{63, 1074},
	{55, 814},
	{62, 779},
	{55, 1245},
	{55, 785},
	{63, 783},
	{55, 1067},
	{63, 607},
	{62, 847},
	{63, 956},
	{63, 603},
	{63, 559},
	{55, 750},
	{63, 444},
	{63, 552},
	{55, 784},
	{55, 876},
	{63, 542},
	{55, 1372},
	{63, 573},
	{63, 479},
	{62, 614},
	{55, 1143},
	{63, 554},
	{62, 900},
	{63, 491},
	{62, 805},
	{55, 1063},
	{62, 804},
	{63, 557},
	{63, 512},
	{63, 652},
	{63, 987},
	{63, 1012},
	{62, 809},
	{55, 1027},
	{55, 791},
	{55, 788},
	{62, 830},
	{62, 759},
	{63, 953},
	{62, 833},
	{62, 799},
	{63, 998},
	{63, 598}
};
/*
stock Work1()
{
	new goodata[100][2];
	new gg_count;
	new find = false;
	for(new w; w < sizeof(npc_perfectnodes); w++)
	{
		find = false;
		for(new g; g < 100; g++)
		{
			if(goodata[g][0] == npc_perfectnodes[w][0] && goodata[g][1] == npc_perfectnodes[w][1])
			{
				find = true;
				break;
			}
		}
		if(find == false)
		{
			for(new g; g < 100; g++)
			{
				if(goodata[g][0] != npc_perfectnodes[w][0] && goodata[g][1] != npc_perfectnodes[w][1])
				{
					goodata[gg_count][0] = npc_perfectnodes[w][0];
					goodata[gg_count][1] = npc_perfectnodes[w][1];
					gg_count++;
					break;
				}
			}
		}
	}
	
	for(new p; p < 100; p++)
	{
		if(goodata[p][0] == 0 || goodata[p][1] == 0) continue;
		printf("{%d, %d}", goodata[p][0], goodata[p][1]);
	}
	return 1;
}*/

stock Init_NPC()
{
	//train[0] = AddStaticVehicle(538, 2864.7029, 1287.6565, 12.5796, 180.3236, 1, 1);
	for(new t; t < 20; t++)
	{
		train[t] = AddStaticVehicle(538, 2864.7029, 1287.6565, 12.5796, 180.3236, 1, 1);
	}
	for(new t = 20; t < 40; t++)
	{
		train[t] = AddStaticVehicle(538, 2864.7029, 1287.6565, 12.5796, 180.3236, 1, 1);
	}
	for(new t = 40; t < 60; t++)
	{
		train[t] = AddStaticVehicle(538, 2864.7029, 1287.6565, 12.5796, 180.3236, 1, 1);
	}
	for(new t = 60; t < 80; t++)
	{
		train[t] = AddStaticVehicle(538, 2864.7029, 1287.6565, 12.5796, 180.3236, 1, 1);
	}
	for(new t = 80; t < 100; t++)
	{
		train[t] = AddStaticVehicle(538, 2864.7029, 1287.6565, 12.5796, 180.3236, 1, 1);
	}
	//---
	//---
	FCNPC_SetUpdateRate(40);
	//MapAndreas_Init(MAP_ANDREAS_MODE_FULL, "scriptfiles/AngelFallZ.hmap");
	//if(FCNPC_InitMapAndreas(MapAndreas_GetAddress())) print("[LOAD]FCNPC zaladowal poprawnie ZMap - npc czuja grunt pod nogami.");
	//else print("[ERROR]FCNPC NIE zaladowal ZMap - npc nie wyczuwaja gruntu.");
	serwer[maxnpc] = GetServerVarAsInt("maxnpc");
	for (new i = 0; i < FCNPC_MAX_NODES; i++) {
		if (!FCNPC_IsNodeOpen(i) && !FCNPC_OpenNode(i)) {
			printf("Error: Failed to open node %d from (scriptfiles/FCNPC/nodes/NODES%d.DAT)", i, i);
			return 0;
		}
	}
	printf("[LOAD]Wpuszczam %d NPC na serwer...", serwer[maxnpc]);
	SetTimer("NPC_Add", 50, false);
	//LoadNodeBans();
	return 1;
}

forward NPC_Add();
public NPC_Add()
{         
	new name[24];
	if(serwer[npc_connected] < serwer[maxnpc])
	{
		format(name, 24, "[HL]NPC_%d", serwer[npc_connected] + 1);
		FCNPC_Create(name);
		serwer[npc_connected]++;
		SetTimer("NPC_Add", 10, false);
	}
	else
	{
		ConnectTrain(0);
	}
	return 1;
}


public FCNPC_OnCreate(npcid)
{
	NPC[npcid][npc_created] = true;
	NPC[npcid][npc_role] = NPCROLE_FREE;
	FCNPC_SetInvulnerable(npcid, true);
	FCNPC_Spawn(npcid,  courier_clients_skins[random(sizeof(courier_clients_skins))], 0.0, 0.0, -1000.0);
	FCNPC_SetVirtualWorld(npcid, 10000);
	SetPlayerColor(npcid, 0x0000FF00);
	for(new ac; ac < 60; ac++)
	{
		EnableAntiCheatForPlayer(npcid, ac, false);
	}
	return 1;
}

public FCNPC_OnFinishPlayback(npcid)
{
	new vehicleid = FCNPC_GetVehicleID(npcid);
	new vehmodel = GetVehicleModel(vehicleid);
	if(vehmodel == 537 || vehmodel == 538)
	{
		FCNPC_StartPlayingPlayback(npcid, "trainv4");
	}
	return 1;
}

stock GetFreeNpcs()
{
	new wynik;
	for(new n; n < MAX_PLAYERS; n++)
	{
		if(IsPlayerNPC(n))
		{
			if(NPC[n][npc_role] == NPCROLE_FREE) wynik++;
		}
	}
	return wynik;
}

forward ConnectTrain(var);
public ConnectTrain(var)
{
	const next_train_delay = 1000*60*1;
	for(new n; n < MAX_PLAYERS; n++)
	{
		if(IsPlayerNPC(n))
		{
			if(NPC[n][npc_role] == NPCROLE_FREE)
			{
				if(var < sizeof(train))
				{
					NPC[n][npc_role] = NPCROLE_TRAIN;
					FCNPC_PutInVehicle(n, train[var], 0);
					FCNPC_SetVirtualWorld(n, 0);
					FCNPC_StartPlayingPlayback(n, "trainv4");
					//printf("piv: %d %d %d", n, train[var], 0);
					if(var == 19) SetTimerEx("ConnectTrain", next_train_delay, false, "d", var+1);
					else if(var == 39) SetTimerEx("ConnectTrain", next_train_delay, false, "d", var+1);
					else if(var == 59) SetTimerEx("ConnectTrain", next_train_delay, false, "d", var+1);
					else if(var == 79) SetTimerEx("ConnectTrain", next_train_delay, false, "d", var+1);
					else SetTimerEx("ConnectTrain", ONE_TRAIN_STR, false, "d", var+1);
				}
				break;
			}
		}
	}
	return 1;
}
/*
SELECT id, nodeid, vehnodes, pednodes, navinodes, POINT, COUNT( id ) AS licznik
FROM fcnpc_nodeban
GROUP BY nodeid, vehnodes, pednodes, navinodes, POINT
HAVING licznik >0
ORDER BY  `fcnpc_nodeban`.`nodeid` ASC 
LIMIT 0 , 30
*/
task Process_Citizens()
{
	//printf("free npcs: %d", GetFreeNpcs());
	//if(serwer[bannodes_loaded] == false) return 1;
	new nodeid;
	new point;
	new strNick[128];
	new goodnodes[3];
	goodnodes[0] = 63;
	goodnodes[1] = 62;
	goodnodes[2] = 55;
	for(new n; n < MAX_PLAYERS; n++)
	{
		if(IsPlayerNPC(n))
		{
			if(NPC[n][npc_role] == NPCROLE_CITIZENR)
			{
				//nodeid = MRandom(FCNPC_MAX_NODES);
				//if(random(sizeof(goodnodes))) nodeid = 63;//62 - work full
				//else nodeid = 55;
				/*new rand = random(sizeof(goodnodes));
				nodeid = goodnodes[rand];
				if(!IsValidZone(nodeid)) continue;

				FCNPC_GetNodeInfo(nodeid, vehnodes, pednodes, navinodes);
				NPC[n][npc_node_playtime] = 0;
				if(pednodes != 0)
				{
					//point = random(pednodes) + pednodes + 1;
					point = MRandRange(vehnodes+1, vehnodes+pednodes-1);
					if(PedNodeIsBanned(nodeid, vehnodes, pednodes, navinodes, point) != 1)
					{
						NPC[n][npc_node_id] = nodeid;
						NPC[n][npc_node_vehnodes] = vehnodes;
						NPC[n][npc_node_pednodes] = pednodes;
						NPC[n][npc_node_navinodes] = navinodes;
						NPC[n][npc_node_point] = point;
						FCNPC_SetNodePoint(nodeid, point);
						new Float:x,
						Float:y,
						Float:z;
						FCNPC_GetNodePointPosition(nodeid, x, y, z );
						FCNPC_SetPosition(n, x, y, z+1 );
						FCNPC_SetVirtualWorld(n, 0);
						//FCNPC_SetPosition(n, taxi_clients[clientid][0], taxi_clients[clientid][1], taxi_clients[clientid][2]);
						//FCNPC_SetAngle(n, taxi_clients[clientid][3]);
						FCNPC_PlayNode(n, nodeid, FCNPC_MOVE_TYPE_WALK, .mode = FCNPC_MOVE_MODE_MAPANDREAS);
						format(strNick, 128, "NPC %d (nid: %d, point: %d)", n, nodeid, point);
						//printf("citizenadd: %d %d", nodeid, point);
						if(NPC[n][npc_firstrun]) UpdateDynamic3DTextLabelText(NPC[n][npc_nicklabel], 0x00FF00CC, strNick);
						else UpdateDynamic3DTextLabelText(NPC[n][npc_nicklabel], 0xFF0000CC, strNick);
						NPC[n][npc_role] = NPCROLE_CITIZEN;
						NPC[n][npc_firstrun] = false;
					}
				}
				*/
				new perfectnode_rand = GetPerfectNode();//random(sizeof(npc_perfectnodes));
				if(perfectnode_rand != -1)
				{
					NPC[n][npc_node_id] = npc_perfectnodes[perfectnode_rand][0];
					NPC[n][npc_node_point] = npc_perfectnodes[perfectnode_rand][1];
					if(NPC[n][npc_firstrun]) 
					{
						new minusr = MRandRange(22, 70);
						NPC[n][npc_node_playtime] = minusr;
					}
					else NPC[n][npc_node_playtime] = 0;
					nodeid = NPC[n][npc_node_id];
					point = NPC[n][npc_node_point];
					FCNPC_SetNodePoint(nodeid, point);
					new Float:x,
					Float:y,
					Float:z;
					FCNPC_SetPosition(n, x, y, z+2.0);
					FCNPC_SetVirtualWorld(n, 0);
					FCNPC_PlayNode(n, nodeid, FCNPC_MOVE_TYPE_WALK);
					SetPlayerColor(n, 0x00BA8C15);
					NPC[n][npc_role] = NPCROLE_CITIZEN;
					NPC[n][npc_firstrun] = false;
				}
			} 
			else if(NPC[n][npc_role] == NPCROLE_FREE)
			{
				if(GetCitizensCount() < 50)
				{
					NPC[n][npc_role] = NPCROLE_CITIZENR;
					NPC[n][npc_firstrun] = true;
					NPC[n][npc_perfect] = false;
					NPC[n][npc_nicklabel] = CreateDynamic3DTextLabel(strNick, 0x00FF00CC, 0.0, 0.0, 0.4, 10.0, n, INVALID_VEHICLE_ID, 1);//status
					SetPlayerColor(n, 0x00BA8C15);
				}
			}
			else if(NPC[n][npc_role] == NPCROLE_CITIZEN)
			{
				format(strNick, 128, "[Bot HL] [%ds]\n"COL_GREY"(Testy[n%dp%d])", 60-NPC[n][npc_node_playtime], NPC[n][npc_node_id], NPC[n][npc_node_point]);
				UpdateDynamic3DTextLabelText(NPC[n][npc_nicklabel], 0x00BA8CCC, strNick);
				NPC[n][npc_node_playtime]++;
				if(NPC[n][npc_node_playtime] > 60)
				{
					new perfectnode_rand = GetPerfectNode();
					if(perfectnode_rand != -1)
					{
						NPC[n][npc_node_playtime] = 0;
						FCNPC_StopPlayingNode(n);
						//new perfectnode_rand = GetPerfectNode();//random(sizeof(npc_perfectnodes));
						NPC[n][npc_node_id] = npc_perfectnodes[perfectnode_rand][0];
						NPC[n][npc_node_point] = npc_perfectnodes[perfectnode_rand][1];
						FCNPC_SetNodePoint(NPC[n][npc_node_id], NPC[n][npc_node_point]);
						new Float:x,
						Float:y,
						Float:z;
						FCNPC_GetNodePointPosition(NPC[n][npc_node_id], x, y, z);
						FCNPC_SetPosition(n, x, y, z+2.0);
						FCNPC_SetVirtualWorld(n, 0);
						FCNPC_PlayNode(n, NPC[n][npc_node_id], FCNPC_MOVE_TYPE_WALK);
					}
				}
			}
		}
	}
	return 1;
}

stock GetCitizensCount()
{
	new wynik;
	for(new n; n < MAX_PLAYERS; n++)
	{
		if(IsPlayerNPC(n))
		{
			if(NPC[n][npc_role] == NPCROLE_CITIZEN || NPC[n][npc_role] == NPCROLE_CITIZENR)
			{
				wynik++;
			}
		}
	}
	return wynik;
}

#define LAS_VENTURAS
stock IsValidZone(zoneid)
{
#if defined SAN_ANDREAS
	return zoneid > 0 && zoneid < FCNPC_MAX_NODES;
#elseif defined LOS_SANTOS
	return (zoneid >= 5 && zoneid <= 7) || (zoneid >= 12 && zoneid <= 15) || (zoneid >= 20 && zoneid <= 23);
#elseif defined SAN_FIERRO
	return zoneid == 17 || (zoneid >= 24 && zoneid <= 26) || (zoneid >= 32 && zoneid <= 24)  || (zoneid >= 40 && zoneid <= 41);
#elseif defined LAS_VENTURAS
	return (zoneid >= 38 && zoneid <= 39) || (zoneid >= 45 && zoneid <= 47) || (zoneid >= 53 && zoneid <= 55) || (zoneid >= 61 && zoneid <= 63);
#else
	return false;
#endif
}


stock GetPerfectNode()
{
	for(new n; n < sizeof(npc_perfectnodes_time); n++)
	{
		if(npc_perfectnodes_time[n] < gettime())
		{
			npc_perfectnodes_time[n] = gettime()+MRandRange(8, 20);
			return n;
		}
	}
	return -1;
}

CMD:npcsinfo(playerid, params[])
{
	new trainc, citz, free, taxi;
	for(new n; n < MAX_PLAYERS; n++)
	{
		if(IsPlayerNPC(n))
		{
			if(NPC[n][npc_role] == NPCROLE_TRAIN)
			{
				trainc++;
			}
		}
	}
	for(new n; n < MAX_PLAYERS; n++)
	{
		if(IsPlayerNPC(n))
		{
			if(NPC[n][npc_role] == NPCROLE_CITIZEN || NPC[n][npc_role] == NPCROLE_CITIZENR)
			{
				citz++;
			}
		}
	}
	for(new n; n < MAX_PLAYERS; n++)
	{
		if(IsPlayerNPC(n))
		{
			if(NPC[n][npc_role] == NPCROLE_FREE)
			{
				free++;
			}
		}
	}
	for(new n; n < MAX_PLAYERS; n++)
	{
		if(IsPlayerNPC(n))
		{
			if(NPC[n][npc_role] == NPCROLE_TAXIPASS)
			{
				taxi++;
			}
		}
	}
	SendClientMessageEx(playerid, 0xFF0000FF, " FREE: %d | TRAIN: %d | CITZ: %d | TAXIPASS:%d", free, trainc, citz, taxi);
	return 1;
}

task Process_TaxiCitizens()
{
	new count_taxiciti;
	new taxiciti[MAX_PLAYERS];
	new strNick[128];
	new calls_count = CallsCount(F_TAXI);
	for(new n; n < MAX_PLAYERS; n++)
	{
		if(IsPlayerNPC(n))
		{
			if(NPC[n][npc_role] == NPCROLE_TAXIPASS)
			{
				taxiciti[count_taxiciti] = n;
				count_taxiciti++;
				if(calls_count == 0) format(strNick, 128, "[Bot HL] [TAXI PASAŻER]\n"COL_GREY"(Aktualne przez %ds)", NPC[n][npc_taxi_deltime]);
				else format(strNick, 128, "[Bot HL] [TAXI PASAŻER]\n"COL_GREY"(Nieaktualne, TAXI ma wezwania od graczy) (%d)", NPC[n][npc_taxi_deltime]);
				
				if(NPC[n][npc_vehicle] != 0)
				{
					if(!IsPlayerInVehicle(NPC[n][npc_freezeplayerid], NPC[n][npc_vehicle]))
					{
						FCNPC_RemoveFromVehicle(n);
						StopRouteGPS(NPC[n][npc_freezeplayerid]);
						DisablePlayerCheckpoint(NPC[n][npc_freezeplayerid]);
						LeftNotifyShow(NPC[n][npc_freezeplayerid], "Bot HL", "Opusciles pojazd. Zlecenie Bota HL jest juz nieaktualne.", LN_RED);
						NPC[n][npc_vehicle] = 0;
						FCNPC_ClearAnimations(n);
						NPC[n][npc_role] = NPCROLE_CITIZENR;
					}
					format(strNick, 128, "[Bot HL] [TAXI PASAŻER]\n"COL_GREY"(pasażer, pasy)");
				}
				else
				{
					NPC[n][npc_taxi_deltime]--;
					if(NPC[n][npc_taxi_deltime] <= 0)
					{
						NPC[n][npc_role] = NPCROLE_CITIZENR;
					}
				}
				UpdateDynamic3DTextLabelText(NPC[n][npc_nicklabel], 0xf4f600CC, strNick);
			}
		}
	}
	if(count_taxiciti > MAX_TAXIPASS)//są już jakieś boty czekające na taxi
	{
		for(new t; t < count_taxiciti; t++)
		{
			if(NPC[taxiciti[t]][npc_wenterveh] == true) continue;
			if(NPC[taxiciti[t]][npc_wexitveh] == true) continue;
			if(NPC[taxiciti[t]][npc_vehicle] != 0)
			{
				new Float:nPos[3];
				new npcid = taxiciti[t];
				FCNPC_GetPosition(npcid, nPos[0], nPos[1], nPos[2]);
				if(GetDistanceBetweenPoints(nPos[0], nPos[1], nPos[2], NPC[npcid][npc_taxi_tX], NPC[npcid][npc_taxi_tY], NPC[npcid][npc_taxi_tZ]) < 4.0)
				{
					for(new p = PlayerPoolSize(); p != -1; p--)
					{
						if(!gracz[p][loggedin]) continue;
						if(gracz[p][frakcja] != F_TAXI) continue;
						if(GetPlayerVehicleSeat(p) != 0) continue;
						if(IsPlayerInVehicle(p, FCNPC_GetVehicleID(npcid)))
						{
							FCNPC_ExitVehicle(npcid);
							NPC[npcid][npc_freezeplayerid] = p;
							TogglePlayerControllable(NPC[npcid][npc_freezeplayerid], 0);
							GameTextForPlayer(p, "~b~Bot HL ~y~wysiada...",  99999, 4);
							NPC[npcid][npc_wexitveh] = true;
							break;
						}
					}
				}
				continue;
			}
			if(FCNPC_IsStreamedInForAnyone(taxiciti[t]))
			{
				if(NPC[taxiciti[t]][npc_wenterveh] == false) 
				{
					FCNPC_ApplyAnimation(taxiciti[t], "ON_LOOKERS", "wave_loop", 4.0, 1, 0, 0, 0, 0);
					NPC[taxiciti[t]][npc_useanim] = true;
				}
				if(calls_count == 0)
				{
					for(new p = PlayerPoolSize(); p != -1; p--)
					{
						if(!gracz[p][loggedin]) continue;
						if(gracz[p][frakcja] != F_TAXI) continue;
						if(!IsPlayerOnDutyFraction(p)) continue;
						if(GetPlayerVehicleSeat(p) != 0) continue;
						new Float:nPos[3];
						FCNPC_GetPosition(taxiciti[t], nPos[0], nPos[1], nPos[2]);
						if(IsPlayerInRangeOfPoint(p, 5.0, nPos[0], nPos[1], nPos[2]))//jest przy bocie
						{
							if(gracz[p][opu_speed] == 0)
							{
								new vehicleid  = GetPlayerVehicleID(p);
								if(vehicleid != 0)//jest w aucie
								{
									if(GetMaxSeats(vehicleid) == 4)
									{
										if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION && pojazd[vehicleid][v_owner] == F_TAXI)//jest w aucie taxi
										{
											if(!IsSeatTakenFCNPC(vehicleid, 3))
											{
												if(OtherNPCTaxiEnterMyVeh() == 0)
												{
													if(NPC[taxiciti[t]][npc_useanim] == true)
													{
														FCNPC_ClearAnimations(taxiciti[t]);
														NPC[taxiciti[t]][npc_useanim] = false;
													}
													TogglePlayerControllable(p, 0);
													FCNPC_EnterVehicle(taxiciti[t], vehicleid, 3);
													SetTimerEx("FCNPC_MaxEnterVehTime", 5500, false,  "ddd", taxiciti[t], vehicleid, 3);
													GameTextForPlayer(p, "~b~Bot HL ~y~wsiada...",  999999, 4);
													NPC[taxiciti[t]][npc_freezeplayerid] = p;
													NPC[taxiciti[t]][npc_wenterveh] = true;
													NPC[taxiciti[t]][npc_halotaxi_timestamp] = 333;
													//printf("freeze: %d", NPC[taxiciti[t]][npc_freezeplayerid]);
												}
											}
											break;
										}
									}
								}
							}
							else
							{
								FCNPC_SetAngle(taxiciti[t], AngleBetweenPoints(nPos[0], nPos[1], gracz[p][PosX], gracz[p][PosY]));
								NPC[taxiciti[t]][npc_taxi_deltime] = 60;
								if(NPC[taxiciti[t]][npc_halotaxi_timestamp] < serwer[time_timestamp])
								{
									new message[128];
									format(message, 128, "Bot HL krzyczy: Halo Taxi!!!");
									ProxDetector(taxiciti[t], 35.0, message, 0xFFFFFF96, 0xC8C8C896, 0x8B8B8B96, 0x5D5D5D96,  0x41414196);
									NPC[taxiciti[t]][npc_halotaxi_timestamp] = serwer[time_timestamp]+5;
								}
							}
						}
						else if(IsPlayerInRangeOfPoint(p, 35.0, nPos[0], nPos[1], nPos[2]))
						{
							new vehicleid  = GetPlayerVehicleID(p);
							if(vehicleid != 0)//jest w aucie
							{
								if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION && pojazd[vehicleid][v_owner] == F_TAXI)//jest w aucie taxi
								{
									FCNPC_SetAngle(taxiciti[t], AngleBetweenPoints(nPos[0], nPos[1], gracz[p][PosX], gracz[p][PosY]));
									NPC[taxiciti[t]][npc_taxi_deltime] = 60;
									if(NPC[taxiciti[t]][npc_halotaxi_timestamp] < serwer[time_timestamp])
									{
										new message[128];
										format(message, 128, "Bot HL krzyczy: Halo Taxi!!!");
										ProxDetector(taxiciti[t], 35.0, message, 0xFFFFFF96, 0xC8C8C896, 0x8B8B8B96, 0x5D5D5D96,  0x41414196);
										NPC[taxiciti[t]][npc_halotaxi_timestamp] = serwer[time_timestamp]+6;
									}
								}
							}
						}
						else if(IsPlayerInRangeOfPoint(p, 100.0, nPos[0], nPos[1], nPos[2]))//jest przy bocie
						{
							new vehicleid  = GetPlayerVehicleID(p);
							if(vehicleid != 0)//jest w aucie
							{
								if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION && pojazd[vehicleid][v_owner] == F_TAXI)//jest w aucie taxi
								{
									//FCNPC_GiveAngle()
									FCNPC_SetAngle(taxiciti[t], AngleBetweenPoints(nPos[0], nPos[1], gracz[p][PosX], gracz[p][PosY]));
									NPC[taxiciti[t]][npc_taxi_deltime] = 60;
								}
							}
						}
					}
				}
			}	
		}
	}
	else//nie ma botów czekających na taxi
	{
		if(random(2) == 0)
		{
			new citz_wait[MAX_PLAYERS];
			new citz_count;
			for(new n; n < MAX_PLAYERS; n++)
			{
				if(IsPlayerNPC(n))
				{
					if(NPC[n][npc_role] == NPCROLE_CITIZEN)
					{
						if(NPC[n][npc_node_playtime] > 30)
						{
							citz_wait[citz_count] = n;
							citz_count++;
						}
					}
				}
			}
			if(citz_count > MAX_TAXIPASS)
			{
				new rand_citz = random(citz_count);
				new rand_citzid = citz_wait[rand_citz];
				NPC[rand_citzid][npc_role] = NPCROLE_TAXIPASS;
				NPC[rand_citzid][npc_halotaxi_timestamp] = 0;
				SetPlayerColor(rand_citzid, 0xf4f60015);
				FCNPC_StopPlayingNode(rand_citzid);	
				NPC[rand_citzid][npc_taxi_deltime] = 60;
			}
		}
		else
		{
			new citz_wait[MAX_PLAYERS];
			new citz_count;
			for(new n; n < MAX_PLAYERS; n++)
			{
				if(IsPlayerNPC(n))
				{
					if(NPC[n][npc_role] == NPCROLE_CITIZEN)
					{
						if(NPC[n][npc_node_playtime] > 30)
						{
							citz_wait[citz_count] = n;
							citz_count++;
						}
					}
				}
			}

			if(citz_count > MAX_TAXIPASS)
			{
				new rand_citz = random(citz_count);
				new rand_citzid = citz_wait[rand_citz];
				NPC[rand_citzid][npc_role] = NPCROLE_TAXIPASS;
				SetPlayerColor(rand_citzid, 0xf4f60015);
				FCNPC_StopPlayingNode(rand_citzid);
				NPC[rand_citzid][npc_taxi_deltime] = 60;

				new potential_taxiposs[MAX_COURIERCLIENTS];
				new pt_counter;
				for(new c = MAX_COURIERCLIENTS-1; c != -1; c--)
				{
					if(!IsPlayerInRangeOfPoint(NPC[rand_citzid][npc_freezeplayerid], 500.0, courier_clients[c][0], courier_clients[c][1], courier_clients[c][2]))
					{
						if(pt_counter < MAX_COURIERCLIENTS)
						{
							potential_taxiposs[pt_counter] = c;
							pt_counter++;
						}
						else break;
					}
				}
				pt_counter--;//-1, żeby nie przekroczyło wielkości zmiennej
				new random_pt =  random(pt_counter);
				new target = potential_taxiposs[random_pt];
				FCNPC_SetPosition(rand_citzid, courier_clients[target][0], courier_clients[target][1], courier_clients[target][2]);
				NPC[rand_citzid][npc_halotaxi_timestamp] = 0;
			}

		}
	}
	return 1;
}


task FCNPC_MaxEnterVehTime(npcid, vehicleid, seatid)
{
	if(FCNPC_GetVehicleID(npcid) != vehicleid &&  FCNPC_GetVehicleSeat(npcid) != seatid) 
	{
		FCNPC_Stop(npcid);
		FCNPC_SetSpecialAction(npcid, SPECIAL_ACTION_NONE);
		FCNPC_PutInVehicle(npcid, vehicleid, seatid);
		FCNPC_OnVehicleEntryComplete(npcid, vehicleid, seatid);
	}
	else
	{
		printf("FCNPC_MaxEnterVehTime - ANULOWANE");
	}
	return 1;
}

public FCNPC_OnVehicleEntryComplete(npcid, vehicleid, seatid)
{
	if(NPC[npcid][npc_wenterveh] == true)
	{
		TogglePlayerControllable(NPC[npcid][npc_freezeplayerid], true);
		GameTextForPlayer(NPC[npcid][npc_freezeplayerid], "~b~Bot HL ~g~wsiadl...",  2000, 4);
		NPC[npcid][npc_wenterveh] = false;
		NPC[npcid][npc_vehicle] = vehicleid;
		new potential_clients[MAX_TAXITARGET];
		new pt_counter;
		for(new c = MAX_TAXITARGET-1; c != -1; c--)
		{
			if(!IsPlayerInRangeOfPoint(NPC[npcid][npc_freezeplayerid], 500.0, taxi_targets[c][0], taxi_targets[c][1], taxi_targets[c][2]))
			{
				if(pt_counter < MAX_TAXITARGET)
				{
					potential_clients[pt_counter] = c;
					//printf("potential_clients[%d] = %d", pc_counter, c);
					pt_counter++;
				}
				else break;
			}
		}
		pt_counter--;//-1, żeby nie przekroczyło wielkości zmiennej
		new random_pt =  random(pt_counter);
		new target = potential_clients[random_pt];
		NPC[npcid][npc_taxi_tX] = taxi_targets[target][0];
		NPC[npcid][npc_taxi_tY] = taxi_targets[target][1];
		NPC[npcid][npc_taxi_tZ] = taxi_targets[target][2];
		StartRouteGPS(NPC[npcid][npc_freezeplayerid], NPC[npcid][npc_taxi_tX], NPC[npcid][npc_taxi_tY], NPC[npcid][npc_taxi_tZ]);
		SetPlayerCheckpoint(NPC[npcid][npc_freezeplayerid], NPC[npcid][npc_taxi_tX], NPC[npcid][npc_taxi_tY], NPC[npcid][npc_taxi_tZ], 4.0);
		gracz[NPC[npcid][npc_freezeplayerid]][npc_taxi_calcroute] = npcid;
		new targetname[24];
		Get2DZone(NPC[npcid][npc_taxi_tX], NPC[npcid][npc_taxi_tY], targetname, 24);
		new message[128];
		format(message, 128, "Bot HL mówi: Witam! Poproszę na '%s'.", targetname);
		ProxDetector(npcid, 18.0, message, 0xFFFFFF96, 0xC8C8C896, 0x8B8B8B96, 0x5D5D5D96,  0x41414196);
		//	printf("unfreeze: %d", NPC[npcid][npc_freezeplayerid]);
	}
	else
	{
		FCNPC_RemoveFromVehicle(npcid);
		NPC[npcid][npc_vehicle] = 0;
		FCNPC_ClearAnimations(npcid);
		NPC[npcid][npc_role] = NPCROLE_CITIZENR;
	}
	return 1;
}



public FCNPC_OnVehicleExitComplete(npcid)
{
	if(NPC[npcid][npc_wexitveh] == true)
	{
		TogglePlayerControllable(NPC[npcid][npc_freezeplayerid], true);
		GameTextForPlayer(NPC[npcid][npc_freezeplayerid], "~b~Bot HL ~g~wysiadl...",  99999, 4);
		NPC[npcid][npc_wexitveh] = false;
		new Float:gotopos[2];
		GetXYInRightOfPlayer(NPC[npcid][npc_freezeplayerid], gotopos[0], gotopos[1], 4.0);
		FCNPC_GoTo(npcid, gotopos[0], gotopos[1], gracz[NPC[npcid][npc_freezeplayerid]][PosZ]);
		//FCNPC_SetPosition(npcid, gotopos[0], gotopos[1], gracz[NPC[npcid][npc_freezeplayerid]][PosZ]);
		StopRouteGPS(NPC[npcid][npc_freezeplayerid]);
		DisablePlayerCheckpoint(NPC[npcid][npc_freezeplayerid]);
		new message[128];
		format(message, 128, "Bot HL mówi: Dzięki. Miłego dnia!");
		ProxDetector(npcid, 18.0, message, 0xFFFFFF96, 0xC8C8C896, 0x8B8B8B96, 0x5D5D5D96,  0x41414196);
		GiveMoney(NPC[npcid][npc_freezeplayerid], NPC[npcid][npc_taxi_price]);
		SetTimerEx("ExitNPCPass", 1700, false, "dd", npcid, 0);
		//NPC[npcid][npc_role] = NPCROLE_CITIZENR;
	}
	return 1;
}

task ExitNPCPass(npcid, step)
{
	switch(step)
	{
		case 0:
		{
			new Float:nPos[3];
			FCNPC_GetPosition(npcid, nPos[0], nPos[1], nPos[2]);
			FCNPC_SetAngle(npcid, AngleBetweenPoints(nPos[0], nPos[1], gracz[NPC[npcid][npc_freezeplayerid]][PosX], gracz[NPC[npcid][npc_freezeplayerid]][PosY]));
			SetTimerEx("ExitNPCPass", 1000, false, "dd", npcid, 1);
			new strTemp[128];
			format(strTemp, 128,  "~g~SUKCES!~n~~p~+%d$", NPC[npcid][npc_taxi_price]);
			GameTextForPlayer(NPC[npcid][npc_freezeplayerid], strTemp,  3000, 4);
		}
		case 1:
		{
			FCNPC_ApplyAnimation(npcid, "ON_LOOKERS", "wave_loop", 4.0, 1, 0, 0, 0, 0);
			SetTimerEx("ExitNPCPass", 1000, false, "dd", npcid, 2);
		}
		case 2:
		{
			FCNPC_ApplyAnimation(npcid, "ON_LOOKERS", "wave_loop", 4.0, 1, 0, 0, 0, 0);
			SetTimerEx("ExitNPCPass", 1000, false, "dd", npcid, 3);
		}
		case 3:
		{
			FCNPC_ClearAnimations(npcid);
			NPC[npcid][npc_vehicle] = 0;
			NPC[npcid][npc_role] = NPCROLE_CITIZENR;
		}
	}
	return 1;
}




stock OtherNPCTaxiEnterMyVeh()
{
	for(new n; n < MAX_PLAYERS; n++)
	{
		if(IsPlayerNPC(n))
		{
			if(NPC[n][npc_wenterveh] == true)
			{
				if(NPC[n][npc_halotaxi_timestamp] == 333) return 1;
			}
		}
	}
	return 0;
}





























//NODE BAN
/*
#define MAX_NODEBANS 10000
enum nb_data
{
	nb_nodeid,
	nb_vehnodes,
	nb_pednodes,
	nb_navinodes,
	nb_point,
	bool:nb_used
};

new nodeped_bans[MAX_NODEBANS][nb_data];

stock BanPedNode(nodeid, vehnodes, pednodes, navinodes, point, bool:loadmode = false)
{
	if(PedNodeIsBanned(nodeid, vehnodes, pednodes, navinodes, point) && loadmode == false) return 1;
	if(serwer[uptime] < 10 && loadmode == false) return 1;
	for(new n; n < MAX_NODEBANS; n++)
	{
		if(nodeped_bans[n][nb_used] == false)
		{
			nodeped_bans[n][nb_used] = true;
			nodeped_bans[n][nb_nodeid] = nodeid;
			nodeped_bans[n][nb_vehnodes] = vehnodes;
			nodeped_bans[n][nb_pednodes] = pednodes;
			nodeped_bans[n][nb_navinodes] = navinodes;
			nodeped_bans[n][nb_point] = point;
			if(loadmode == false)
			{
				printf("[ADD_PEDNODEBAN] nodeid: %d vehnodes: %d pednodes: %d navinodes: %d point: %d", nodeid, vehnodes, pednodes, navinodes, point);
				mq_format("INSERT INTO `fcnpc_nodeban` (`nodeid` ,`vehnodes` ,`pednodes` ,`navinodes`, `point`) VALUES ('%d',  '%d',  '%d',  '%d', '%d');", nodeid, vehnodes, pednodes, navinodes, point);
				mq_send("QBanNode");
			}
			//else printf("[LOAD_PEDNODEBAN] nodeid: %d vehnodes: %d pednodes: %d navinodes: %d point: %d", nodeid, vehnodes, pednodes, navinodes, point);
			return 1;
		}
	}
	return 0;
}

stock PedNodeIsBanned(nodeid, vehnodes, pednodes, navinodes, point)
{
	//if(FCNPC_GetNodeType(nodeid) != 102) return 0;
	for(new n; n < MAX_NODEBANS; n++)
	{
		if(nodeped_bans[n][nb_used] == true)
		{
			if(nodeped_bans[n][nb_nodeid] == nodeid)
			{
				if(nodeped_bans[n][nb_point] == point)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

stock LoadNodeBans()
{
	mq_format("SELECT * FROM `fcnpc_nodeban`;");
	mq_send("QLoadNodeBans");
	return 1;
}

task QLoadNodeBans()
{
	mq_getdata();
	if(rekordy)
	{
		new i;
		while(i < rekordy)
		{
			BanPedNode(cache_get_value_name_int(i, "nodeid"), cache_get_value_name_int(i, "vehnodes"), cache_get_value_name_int(i, "pednodes"), cache_get_value_name_int(i, "navinodes"), cache_get_value_name_int(i, "point"), true);
			i++;
		}
	}
	serwer[bannodes_loaded] = true;
	return 1;
}


CMD:printperfect(playerid, params[])
{
	for(new n; n < MAX_PLAYERS; n++)
	{
		if(IsPlayerNPC(n))
		{
			if(NPC[n][npc_role] == NPCROLE_CITIZEN)
			{
				if(NPC[n][npc_perfect] == true)
				{
					printf("[PERFECTNODE] {%d, %d},", NPC[n][npc_node_id], NPC[n][npc_node_point]);
				}
			}
		}
	}
	return 1;
}
*/