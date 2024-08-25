forward BlinkSystem_OnTrailerDetached(trailerid, fromvehicleid);
forward BlinkSystem_OnTrailerAttached(trailerid, tovehicleid);
forward BlinkSystem_TrailerCheck();
forward BlinkSystem_DisableBlinks(vehicleid); 

new Blink[MAX_VEHICLES][4];
new BlinkSide[MAX_VEHICLES];
new Float:BlinkR[MAX_VEHICLES];
new BlinkTrailer[MAX_VEHICLES];
new TrailerVehicle[MAX_VEHICLES];

stock IsPlayerCanDrive(playerid, vehicleid)
{
	if(IsPlayerNPC(playerid)) return 1;
	if(GetVehicleModel(vehicleid) == 537 || GetVehicleModel(vehicleid) == 538) return 0;//blokada wsiadania do pociągów

	//god of car
	if(gracz[playerid][admin_godofcar])
	{
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER || pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION || pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS || (pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_EVENT)) return 1;
	}

	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_EVENT/* && gracz[playerid][admin_duty] < 1*/) return PermissionEventVehicle(playerid, vehicleid);
	
	if(gracz[playerid][admin_duty] < 1)//pojazdy administracyjne
	{
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_ADMINVEH) return 0;
	}
	//ma kluczyki
	if(pojazd[vehicleid][v_kluczyki_puid] != 0 && pojazd[vehicleid][v_kluczyki_puid] == gracz[playerid][UID]) return 1;
	//standard
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION && (pojazd[vehicleid][v_owner] == F_POLICE || pojazd[vehicleid][v_owner] == F_BORDERGUARD) && (gracz[playerid][frakcja] == F_POLICE || gracz[playerid][frakcja] == F_BORDERGUARD) && IsPlayerOnDutyFraction(playerid)) return 1;
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && (pojazd[vehicleid][v_owner] == VO_CARSHOP || pojazd[vehicleid][v_owner] == VO_TRUCKSHOP)) return 0;
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER && gracz[playerid][UID] != pojazd[vehicleid][v_owner]) return 0;
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION && (gracz[playerid][frakcja] == 0 || gracz[playerid][frakcja] != pojazd[vehicleid][v_owner] || !IsPlayerOnDutyFraction(playerid))) return 0;
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS && (gracz[playerid][firma] == 0 || gracz[playerid][firma] != pojazd[vehicleid][v_owner] || !IsPlayerOnDutyCompany(playerid))) return 0;

	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC)//zabezpieczenie pojazdów kurierskich, żeby nikt nie kradł
	{
		for(new c = sizeof(courier_data)-1; c != -1; c--)
		{
			if(pojazd[vehicleid][v_owner] == courier_data[c][cd_cid])//pojazd jest pojazdem kurierskich
			{
				for(new p = PlayerPoolSize(); p != -1; p--)//szukamy, czy inny gracz tego pojazdu już nie zajął
				{
					if(p == playerid) continue;
					if(!gracz[p][loggedin]) continue;
					if(gracz[p][courier_job_vehicleid] == vehicleid) return 0;//pojazd do którego gracz chce wejść jest w zarezerwowany przez innego gracza
				}
			}
		}
	}
	return 1;
}

CMD:removeveh(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 1;
	//DestroyVehicle(GetPlayerVehicleID(playerid));
	RemoveVehicle(GetPlayerVehicleID(playerid));
	DoneInfo();
	return 1;
}

stock RespawnVehicle(vehicleid, bool:force = false, bool:onlyrecreate = false)
{
	if(pojazd[vehicleid][v_model] == 0) return 0;
	if(pojazd[vehicleid][v_event_used] == true) return 0;
	new vo_type = pojazd[vehicleid][v_owner_type];
	new vo_owner = pojazd[vehicleid][v_owner];
	new bool:vehicle_used = false;
	if(pojazd[vehicleid][v_idletime]+(VEHI_GLOBALRESPTIME) > serwer[time_timestamp] && force == false) vehicle_used = true;
	if(IsVehicleInUse(vehicleid) != INVALID_PLAYER_ID && force == false) vehicle_used = true;

	if(vehicle_used == false && vo_type == VEHICLE_PUBLIC && (vo_owner == C_DHL || vo_owner == C_DPD || vo_owner == C_FEDEX || vo_owner == C_INPOST || vo_owner == C_TNT))//POJAZDY KURIERSKIE
	{
		SetVehicleHealth(vehicleid, 1000.0);
		RepairVehicle(vehicleid);
		pojazd[vehicleid][v_paliwo] = GetVehicleFuelSize(pojazd[vehicleid][v_model]);
		pojazd[vehicleid][v_cargo] = 0;
		pojazd[vehicleid][v_cargo_amount] = 0;
	}
	
	if(vehicle_used == false)
	{
		if(vo_type == VEHICLE_FRACTION)
		{
			SetVehicleHealth(vehicleid, 1000.0);
			RepairVehicle(vehicleid);
		}
		
		TrafficLight(vehicleid, 0);
		ToggleVehicleNeons(vehicleid, 0);

		GetVehicleDamageStatus(vehicleid, pojazd[vehicleid][v_uvds_panels], pojazd[vehicleid][v_uvds_doors], pojazd[vehicleid][v_uvds_lights], pojazd[vehicleid][v_uvds_tires]);
		GetVehicleHealth(vehicleid, pojazd[vehicleid][v_HP]);
		if(vo_type == VEHICLE_PLAYER)//jeśli pojazd gracza, został może przeparkowany to trzeba stworzyć go na nowym miejscu
		{
			if(!VehicleCanParkHere(vehicleid, true) && onlyrecreate == false)
			{
				if(pojazd[vehicleid][v_id] != 0)
				{
					mq_format("UPDATE `pojazdy` SET `status`='0', `rlg_lastused`='0' WHERE `id`='%d';", pojazd[vehicleid][v_id]);
					mq_send("QUpdateVehicleStatus");
				}
				RemoveVehicle(vehicleid);
				return (vehicle_used) ? (0) : (1);
			}
			else
			{
				new new_vehicleid;
				if(onlyrecreate == false) new_vehicleid = CreateVehicle(pojazd[vehicleid][v_model], pojazd[vehicleid][v_X],  pojazd[vehicleid][v_Y], pojazd[vehicleid][v_Z], pojazd[vehicleid][v_R], pojazd[vehicleid][v_color][0], pojazd[vehicleid][v_color][1], VEH_SINGLERESP_TIME);
				else
				{
					new Float:vTempPos[4];
					GetVehiclePos(vehicleid, vTempPos[0], vTempPos[1], vTempPos[2]);
					GetVehicleZAngle(vehicleid, vTempPos[3]);
					new_vehicleid = CreateVehicle(pojazd[vehicleid][v_model], vTempPos[0], vTempPos[1], vTempPos[2], vTempPos[3], pojazd[vehicleid][v_color][0], pojazd[vehicleid][v_color][1], VEH_SINGLERESP_TIME);
				}

				for(new pojazd_info:pi; pi < pojazd_info; pi++)
				{
					pojazd[new_vehicleid][pi] = pojazd[vehicleid][pi];
				}
				//*******************PRZYCZEPIALNE OBIEKTY FIX*****************************************
				//przyczepianie obiektów ze starego pojazdu do nowego
				for(new i; i < MAX_VEHICLE_OBJECTS; i++)
				{
					if(pojazd[vehicleid][v_object][i] != 0) 
					{
						new Float:offsetXYZ[3];
						new Float:offsetR_XYZ[3];
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT, pojazd[vehicleid][v_object][i], E_STREAMER_ATTACH_OFFSET_X, offsetXYZ[0]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT, pojazd[vehicleid][v_object][i], E_STREAMER_ATTACH_OFFSET_Y, offsetXYZ[1]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT, pojazd[vehicleid][v_object][i], E_STREAMER_ATTACH_OFFSET_Z, offsetXYZ[2]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT, pojazd[vehicleid][v_object][i], E_STREAMER_ATTACH_R_X, offsetR_XYZ[0]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT, pojazd[vehicleid][v_object][i], E_STREAMER_ATTACH_R_Y, offsetR_XYZ[1]);
						Streamer_GetFloatData(STREAMER_TYPE_OBJECT, pojazd[vehicleid][v_object][i], E_STREAMER_ATTACH_R_Z, offsetR_XYZ[2]);
						//printf("%f %f %f %f %f %f", offsetXYZ[0], offsetXYZ[1], offsetXYZ[2], offsetR_XYZ[0], offsetR_XYZ[1], offsetR_XYZ[2]);
						//neon wyłączony fix attach_vehid
						new attach_vehid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, pojazd[vehicleid][v_object][i], E_STREAMER_ATTACHED_VEHICLE);
						if(attach_vehid != INVALID_VEHICLE_ID) AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][i], new_vehicleid, offsetXYZ[0], offsetXYZ[1], offsetXYZ[2], offsetR_XYZ[0], offsetR_XYZ[1], offsetR_XYZ[2]);
					}
				}
				//wyzerowanie danych obiektów ze starego pojazdu po to aby removevehicle ich nie usunął.
				for(new i; i < MAX_VEHICLE_OBJECTS; i++)
				{
					if(pojazd[vehicleid][v_object][i] != 0) 
					{
						pojazd[vehicleid][v_object][i] = 0;
					}
				}
				//---------------------------------------------------------------------FIX END
				//*******************PRZYCZEPIALNE 3D TEXTY FIX*****************************************
				if(IsValidDynamic3DTextLabel(pojazd[vehicleid][v_text3d]))
				{
					new Float:offsetXYZ[3];
					new Float:draw_dist;
					new test_los;
					new label_string[512];
					Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, pojazd[vehicleid][v_text3d], E_STREAMER_ATTACH_OFFSET_X, offsetXYZ[0]);
					Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, pojazd[vehicleid][v_text3d], E_STREAMER_ATTACH_OFFSET_Y, offsetXYZ[1]);
					Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, pojazd[vehicleid][v_text3d], E_STREAMER_ATTACH_OFFSET_Z, offsetXYZ[2]);
					Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, pojazd[vehicleid][v_text3d], E_STREAMER_DRAW_DISTANCE, draw_dist);
					test_los = Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL, pojazd[vehicleid][v_text3d], E_STREAMER_TEST_LOS);
					GetDynamic3DTextLabelText(pojazd[vehicleid][v_text3d], label_string);
					pojazd[new_vehicleid][v_text3d] = CreateDynamic3DTextLabel(label_string, -1, offsetXYZ[0], offsetXYZ[1], offsetXYZ[2], draw_dist, .attachedvehicle = new_vehicleid, .testlos = test_los);
				}
				//---------------------------------------------------------------------FIX END
				RemoveVehicle(vehicleid);
				vehicleid = new_vehicleid;
			}

			//printf("[DEBUG] usuwam: %d | uid: %d", vehicleid, pojazd[vehicleid][v_id]);
			//new vid;
			//CreateVehicle(pojazd[vehicleid][v_model], pojazd[vehicleid][v_X],  pojazd[vehicleid][v_Y], pojazd[vehicleid][v_Z], pojazd[vehicleid][v_R], pojazd[vehicleid][v_color][0], pojazd[vehicleid][v_color][1], VEH_SINGLERESP_TIME);
			//printf("[DEBUG] tworzę: %d | uid: %d", vid, pojazd[vid][v_id]);
		}
		//reset pozycji recznego i zaciąganie go w miejscu spawnu pojazdu
		if(!SpecialVehicle(vehicleid))
		{
			if(onlyrecreate == false)
			{
				pojazd[vehicleid][v_handbrake_posX] = pojazd[vehicleid][v_X];
				pojazd[vehicleid][v_handbrake_posY] = pojazd[vehicleid][v_Y];
				pojazd[vehicleid][v_handbrake_posZ] = pojazd[vehicleid][v_Z];
				pojazd[vehicleid][v_handbrake_posR] = pojazd[vehicleid][v_R];
				pojazd[vehicleid][v_handbrake] = 1;
			}
		}
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)
		{
			pojazd[vehicleid][v_cargo] = 0;
			pojazd[vehicleid][v_cargo_amount] = 0;
			pojazd[vehicleid][v_cargo_score] = 0;
			pojazd[vehicleid][v_cargo_distance] = 0.0;
			pojazd[vehicleid][v_cargo_target_X] = 0.0;
			pojazd[vehicleid][v_cargo_target_Y] = 0.0;
			pojazd[vehicleid][v_cargo_target_Z] = 0.0;
			ResetVehicleADRData(vehicleid);

			new new_vehicleid;
			if(onlyrecreate == false) new_vehicleid = CreateVehicle(pojazd[vehicleid][v_model], pojazd[vehicleid][v_X],  pojazd[vehicleid][v_Y], pojazd[vehicleid][v_Z], pojazd[vehicleid][v_R], pojazd[vehicleid][v_color][0], pojazd[vehicleid][v_color][1], VEH_SINGLERESP_TIME);
			else
			{
				new Float:vTempPos[4];
				GetVehiclePos(vehicleid, vTempPos[0], vTempPos[1], vTempPos[2]);
				GetVehicleZAngle(vehicleid, vTempPos[3]);
				new_vehicleid = CreateVehicle(pojazd[vehicleid][v_model], vTempPos[0], vTempPos[1], vTempPos[2], vTempPos[3], pojazd[vehicleid][v_color][0], pojazd[vehicleid][v_color][1], VEH_SINGLERESP_TIME);
			}
			
			for(new pojazd_info:pi; pi < pojazd_info; pi++)
			{
				pojazd[new_vehicleid][pi] = pojazd[vehicleid][pi];
			}
			//*******************PRZYCZEPIALNE OBIEKTY FIX*****************************************
			//przyczepianie obiektów ze starego pojazdu do nowego
			for(new i; i < MAX_VEHICLE_OBJECTS; i++)
			{
				if(pojazd[vehicleid][v_object][i] != 0) 
				{
					new Float:offsetXYZ[3];
					new Float:offsetR_XYZ[3];
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT, pojazd[vehicleid][v_object][i], E_STREAMER_ATTACH_OFFSET_X, offsetXYZ[0]);
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT, pojazd[vehicleid][v_object][i], E_STREAMER_ATTACH_OFFSET_Y, offsetXYZ[1]);
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT, pojazd[vehicleid][v_object][i], E_STREAMER_ATTACH_OFFSET_Z, offsetXYZ[2]);
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT, pojazd[vehicleid][v_object][i], E_STREAMER_ATTACH_R_X, offsetR_XYZ[0]);
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT, pojazd[vehicleid][v_object][i], E_STREAMER_ATTACH_R_Y, offsetR_XYZ[1]);
					Streamer_GetFloatData(STREAMER_TYPE_OBJECT, pojazd[vehicleid][v_object][i], E_STREAMER_ATTACH_R_Z, offsetR_XYZ[2]);
					//printf("%f %f %f %f %f %f", offsetXYZ[0], offsetXYZ[1], offsetXYZ[2], offsetR_XYZ[0], offsetR_XYZ[1], offsetR_XYZ[2]);
					//neon wyłączony fix attach_vehid
					new attach_vehid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, pojazd[vehicleid][v_object][i], E_STREAMER_ATTACHED_VEHICLE);
					if(attach_vehid != INVALID_VEHICLE_ID) AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][i], new_vehicleid, offsetXYZ[0], offsetXYZ[1], offsetXYZ[2], offsetR_XYZ[0], offsetR_XYZ[1], offsetR_XYZ[2]);
				}
			}
			//wyzerowanie danych obiektów ze starego pojazdu po to aby removevehicle ich nie usunął.
			for(new i; i < MAX_VEHICLE_OBJECTS; i++)
			{
				if(pojazd[vehicleid][v_object][i] != 0) 
				{
					pojazd[vehicleid][v_object][i] = 0;
				}
			}
			//---------------------------------------------------------------------FIX END
			//*******************PRZYCZEPIALNE 3D TEXTY FIX*****************************************
			if(IsValidDynamic3DTextLabel(pojazd[vehicleid][v_text3d]))
			{
				new Float:offsetXYZ[3];
				new Float:draw_dist;
				new test_los;
				new label_string[512];
				Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, pojazd[vehicleid][v_text3d], E_STREAMER_ATTACH_OFFSET_X, offsetXYZ[0]);
				Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, pojazd[vehicleid][v_text3d], E_STREAMER_ATTACH_OFFSET_Y, offsetXYZ[1]);
				Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, pojazd[vehicleid][v_text3d], E_STREAMER_ATTACH_OFFSET_Z, offsetXYZ[2]);
				Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, pojazd[vehicleid][v_text3d], E_STREAMER_DRAW_DISTANCE, draw_dist);
				test_los = Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL, pojazd[vehicleid][v_text3d], E_STREAMER_TEST_LOS);
				GetDynamic3DTextLabelText(pojazd[vehicleid][v_text3d], label_string);
				pojazd[new_vehicleid][v_text3d] = CreateDynamic3DTextLabel(label_string, -1, offsetXYZ[0], offsetXYZ[1], offsetXYZ[2], draw_dist, .attachedvehicle = new_vehicleid, .testlos = test_los);
			}
			//---------------------------------------------------------------------FIX END
			RemoveVehicle(vehicleid);
			vehicleid = new_vehicleid;

			//printf("[DEBUG] usuwam: %d | uid: %d", vehicleid, pojazd[vehicleid][v_id]);
			//new vid;
			//CreateVehicle(pojazd[vehicleid][v_model], pojazd[vehicleid][v_X],  pojazd[vehicleid][v_Y], pojazd[vehicleid][v_Z], pojazd[vehicleid][v_R], pojazd[vehicleid][v_color][0], pojazd[vehicleid][v_color][1], VEH_SINGLERESP_TIME);
			//printf("[DEBUG] tworzę: %d | uid: %d", vid, pojazd[vid][v_id]);
		}
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_ADMINVEH) 
		{
			RemoveVehicle(vehicleid);
		}

		//respawn...
		SetVehicleToRespawn(vehicleid);
	}
	return (vehicle_used) ? (0) : (1);
}

public OnVehicleSpawn(vehicleid)
{
	ChangeVehicleColor(vehicleid, pojazd[vehicleid][v_color][0], pojazd[vehicleid][v_color][1]);
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_DRVLICENSE)//L-ki
	{
		SetVehicleParamsEx(vehicleid, 0, 0, 0, 1, 0, 0, 0);//zamykanie
		RepairVehicle(vehicleid);
		Handbrake(vehicleid, 1);
	}
	else SetVehicleParamsEx(vehicleid, 0, 0, 0, 0, 0, 0, 0);
	TruckSmokeEffect(vehicleid, 0);
	if(strlen(pojazd[vehicleid][v_numberplate]) > 1) SetVehicleNumberPlate(vehicleid, pojazd[vehicleid][v_numberplate]);
	else SetVehicleNumberPlate(vehicleid, VEH_REG);
	if(BlinkSystem_IsTrailer(vehicleid))
	{
		new veh;
		if((veh = TrailerVehicle[vehicleid]) != 0)
		{
			if(IsCarBlinking(veh))
			{
				DestroyDynamicObject(Blink[veh][1]);
				DestroyDynamicObject(Blink[veh][3]);
				Blink[veh][1] = -1;
				Blink[veh][3] = -1;
			}
		}
	}
	else DisableCarBlinking(vehicleid);
	if(pojazd[vehicleid][v_X] == 0.0 && pojazd[vehicleid][v_Y] == 0.0 && pojazd[vehicleid][v_Z] == 0.0)
	{
		GetVehiclePos(vehicleid, pojazd[vehicleid][v_X], pojazd[vehicleid][v_Y], pojazd[vehicleid][v_Z]);
		GetVehicleZAngle(vehicleid, pojazd[vehicleid][v_R]);
	}
	pojazd[vehicleid][v_idle_X] = pojazd[vehicleid][v_X];
	pojazd[vehicleid][v_idle_Y] = pojazd[vehicleid][v_Y];
	pojazd[vehicleid][v_idle_Z] = pojazd[vehicleid][v_Z];
	pojazd[vehicleid][v_idle_R] = pojazd[vehicleid][v_R];
	if(IsVehicleTrailer(pojazd[vehicleid][v_model])) 
	{
		pojazd[vehicleid][v_HP] = 1000.0;
		RepairVehicle(vehicleid);
	}
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER || pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)
	{
		SetVehicleHealth(vehicleid, pojazd[vehicleid][v_HP]);
		UpdateVehicleDamageStatus(vehicleid, pojazd[vehicleid][v_uvds_panels], pojazd[vehicleid][v_uvds_doors], pojazd[vehicleid][v_uvds_lights], pojazd[vehicleid][v_uvds_tires]);
	}
	return 1;
}
//
stock UnoccupiedVehicleDeath(vehicleid, killerid)
{
	if(pojazd[vehicleid][v_timer_onvehdeath] == false) 
	{
		SetTimerEx("timer_ovd", 1000*7, false, "dd", vehicleid, killerid);
		pojazd[vehicleid][v_timer_onvehdeath] = true;
	}
	return pojazd[vehicleid][v_timer_onvehdeath];
}

task timer_ovd(vehicleid, killerid)
{
	pojazd[vehicleid][v_timer_onvehdeath] = false;
	if(GetVehicleModel(vehicleid) != 0) OnVehicleDeath(vehicleid, killerid);
	return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	printf("OnVehicleDeath(%d (model: %d), %s(%d))", vehicleid, GetVehicleModel(vehicleid), nick(killerid), killerid);
	if(BlinkSystem_IsTrailer(vehicleid))
	{
		new veh;
		if((veh = TrailerVehicle[vehicleid]) != 0)
		{
			if(IsCarBlinking(veh))
			{
				DestroyDynamicObject(Blink[veh][1]);
				DestroyDynamicObject(Blink[veh][3]);
				Blink[veh][1] = -1;
				Blink[veh][3] = -1;
			}
		}
	}
	else DisableCarBlinking(vehicleid);
	
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER && IsPlayerCanDrive(killerid, vehicleid))
	{
		if(pojazd[vehicleid][v_id] != 0)
		{
			mq_format("UPDATE `pojazdy` SET `status`='2', `X`='%f', `Y`='%f', `Z`='%f', `rlg_lastused`='0' WHERE `id`='%d';", XYZ_AUTOSZROT, pojazd[vehicleid][v_id]);
			mq_send("QUpdateVehicleStatus");
		}
		RemoveVehicle(vehicleid);
		LeftNotifyShow(killerid, "info", "Pojazd zostal ~r~zezlomowany~w~. Mozesz go odebrac na ~y~autoszrocie~w~ (/v lista).", LN_RED);
	}

	if(pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)
	{
		pojazd[vehicleid][v_cargo] = 0;
		pojazd[vehicleid][v_cargo_amount] = 0;
		pojazd[vehicleid][v_cargo_score] = 0;
		pojazd[vehicleid][v_cargo_distance] = 0.0;
		pojazd[vehicleid][v_cargo_target_X] = 0.0;
		pojazd[vehicleid][v_cargo_target_Y] = 0.0;
		pojazd[vehicleid][v_cargo_target_Z] = 0.0;
	}
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_ADMINVEH)
	{
		RemoveVehicle(vehicleid);
	}
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_EVENT)
	{
		OnEventVehicleDeath(vehicleid, killerid);
	}
	ResetVehicleADRData(vehicleid);
	rope_OnVehicleDeath(vehicleid);
	if(GetVehicleModel(vehicleid) != 0) SetVehicleToRespawn(vehicleid);
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	StopCombineMode(playerid);
	DisablePlayerSpeedCap(playerid);
	gracz[playerid][pasy] = false;
	if(pojazd[vehicleid][v_kluczyki_puid] != 0)
	{
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER && gracz[playerid][UID] == pojazd[vehicleid][v_owner] && !ispassenger)
		{
			RemovePlayerFromVehicle(PlayerUIDToPlayerID(pojazd[vehicleid][v_kluczyki_puid]));
			pojazd[vehicleid][v_kluczyki_puid] = 0;
			Info(playerid, ""COL_RED"Pożyczone kluczyki zostały odebrane.");
		}
	}
	if(!IsPlayerCanDrive(playerid, vehicleid) && !ispassenger && pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC) 
	{
		Error(playerid, "Nie możesz prowadzić tego pojazdu.");
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
		ApplyAnimation(playerid, "CARRY", "crry_prtial", 1, 0, 0, 0, 0, 0, 0);
		return 1;
	}
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	if(GetPlayerVehicleSeat(playerid) == 0)//jest kierowcą
	{
		StopCombineMode(playerid);
		TruckSmokeEffect(vehicleid, 0);
		if(SpecialVehicle(vehicleid))
		{
			new engine, lights, alarm, doors, bonnet, boot, objective;
			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(vehicleid, 0, lights, alarm, doors, bonnet, boot, objective);
		}
		if(GetPlayerDrunkLevel(playerid) < 2105)//usuwanie drunk level po awarii
		{
			if(gracz[playerid][when_tipsy] == 0) SetPlayerDrunkLevel(playerid, 0);
		}
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_DRVLICENSE)//gdy wysiądzie z L-ki
		{
			PrzerwijEgzaminPrawko(playerid, "Opuszczono pojazd.");
		}
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_ADMINVEH)//gdy wysiądzie z admia
		{
			RemoveVehicle(vehicleid);
			Info(playerid, "Pojazd administracyjny automatycznie usunięty!");
		}
		DisablePlayerSpeedCap(playerid);
		gracz[playerid][towtruck_trailerid] = 0;
	}
	else//pasażer
	{
	}
	gracz[playerid][pasy] = false;
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	TuneTaxiVehicle(vehicleid);
	//tuning PRIV load
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER)
	{
		for(new t; t < ZVEH_MAX_COMPONENT_TYPES; t++)
		{
			//if(t == 5) continue;//pomija nitro
			if(t == 3)
			{
				AddVehicleComponent(vehicleid, pojazd[vehicleid][v_tune_data][t]);
				AddVehicleComponent(vehicleid, pojazd[vehicleid][v_tune_data][t]);
			}
			else AddVehicleComponent(vehicleid, pojazd[vehicleid][v_tune_data][t]);
		}
		ChangeVehiclePaintjob(vehicleid, TranslateVehPaintjob(pojazd[vehicleid][v_paintjob]));
	}

	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	
	return 1;
}


public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{
	//if(pojazd[vehicleid][v_handbrake] && !IsVehicleTrailer(pojazd[vehicleid][v_model])) return 0;
	if(gracz[playerid][loading_objects]) return 0;
	new Float:unoPos[3];
	GetVehiclePos(vehicleid, unoPos[0], unoPos[1], unoPos[2]);
	if(!IsPlayerInRangeOfPoint(playerid, 20.0, unoPos[0], unoPos[1], unoPos[2])) return 0;//Tylko gracze, którzy są blisko pojazdu mogą go synchronizować
	/*if(pojazd[vehicleid][v_handbrake] && !IsVehicleTrailer(pojazd[vehicleid][v_model]))
	{
		new Float:unoR;
		pojazd[vehicleid][v_handbrake_posZ] = unoPos[2];
		//GetVehiclePos(vehicleid, unoR, unoR,  pojazd[vehicleid][v_handbrake_posZ]);//dozwolona synchronizacja wszystkim pozycji z
		GetVehicleZAngle(vehicleid, unoR);
		if(GetDistanceBetweenPoints(pojazd[vehicleid][v_handbrake_posX], pojazd[vehicleid][v_handbrake_posY], pojazd[vehicleid][v_handbrake_posZ], new_x, new_y, new_z) > 2.0 || !((pojazd[vehicleid][v_handbrake_posR]-2.0) < unoR < (pojazd[vehicleid][v_handbrake_posR]+2.0)))
		{
			//printf("[OK] %f < %f < %f", pojazd[vehicleid][v_idle_R]-2.0, pojazd[vehicleid][v_idle_R], pojazd[vehicleid][v_idle_R]+2.0);
			SetVehiclePos(vehicleid, pojazd[vehicleid][v_handbrake_posX], pojazd[vehicleid][v_handbrake_posY], pojazd[vehicleid][v_handbrake_posZ]);
			SetVehicleZAngle(vehicleid, pojazd[vehicleid][v_handbrake_posR]);
		}
	}
	else */
	if(gracz[playerid][cargo_trailerdid] != vehicleid && IsVehicleTrailer(pojazd[vehicleid][v_model]))//zabezpieczenie przesuwania naczep - może tylko właściciel
	{
		//if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_DRVLICENSE) return 1;//Do L-ek
		//if(pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS && pojazd[vehicleid][v_owner] == gracz[playerid][firma]) return 1;//Do Firm
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_MPTRAILER)//tylko naczepy freelancer
		{
			if(pojazd[vehicleid][v_idletime]+15 > serwer[time_timestamp]) return 1;//jeśli pojazd był przez kogoś synchronizowany przez ostatnie x sekund, każdy go może synchronizować
			new Float:unoR;
			pojazd[vehicleid][v_idle_Z] = unoPos[2];
			//GetVehiclePos(vehicleid, unoR, unoR, pojazd[vehicleid][v_idle_Z]);//dozwolona synchronizacja wszystkim pozycji z
			GetVehicleZAngle(vehicleid, unoR);
			//printf("[CHECK] %f < %f < %f", pojazd[vehicleid][v_idle_R]-2.0, unoR, pojazd[vehicleid][v_idle_R]+2.0);
			if(pojazd[vehicleid][v_idle_X] == 0.0 && pojazd[vehicleid][v_idle_Y] == 0.0)
			{
				GetVehiclePos(vehicleid, pojazd[vehicleid][v_idle_X], pojazd[vehicleid][v_idle_Y], pojazd[vehicleid][v_idle_Z]);//WAŻNE!! Aktualizuj to, a zapobiegniesz znikającym autkom.
				GetVehicleZAngle(vehicleid, pojazd[vehicleid][v_idle_R]);
			}
			if(GetDistanceBetweenPoints(pojazd[vehicleid][v_idle_X], pojazd[vehicleid][v_idle_Y], pojazd[vehicleid][v_idle_Z], new_x, new_y, new_z) > 2.0 || !((pojazd[vehicleid][v_idle_R]-2.0) < unoR < (pojazd[vehicleid][v_idle_R]+2.0)))
			{
				//printf("[OK] %f < %f < %f", pojazd[vehicleid][v_idle_R]-2.0, pojazd[vehicleid][v_idle_R], pojazd[vehicleid][v_idle_R]+2.0);
				SetVehiclePos(vehicleid, pojazd[vehicleid][v_idle_X], pojazd[vehicleid][v_idle_Y], pojazd[vehicleid][v_idle_Z]);
				SetVehicleZAngle(vehicleid, pojazd[vehicleid][v_idle_R]);
			}
		}
		else
		{
			GetVehiclePos(vehicleid, pojazd[vehicleid][v_idle_X], pojazd[vehicleid][v_idle_Y], pojazd[vehicleid][v_idle_Z]);//WAŻNE!! Aktualizuj to, a zapobiegniesz znikającym autkom.
			GetVehicleZAngle(vehicleid, pojazd[vehicleid][v_idle_R]);
		}
	}
	else
	{
		GetVehiclePos(vehicleid, pojazd[vehicleid][v_idle_X], pojazd[vehicleid][v_idle_Y], pojazd[vehicleid][v_idle_Z]);//WAŻNE!! Aktualizuj to, a zapobiegniesz znikającym autkom.
		GetVehicleZAngle(vehicleid, pojazd[vehicleid][v_idle_R]);
	}
	return 1;
}


forward OnTrailerAttached(playerid, trailerid);//callback wywoływany przez sam skrypt HL
public OnTrailerAttached(playerid, trailerid)
{
	//printf("OnTrailerAttached(%d, %d);", playerid, trailerid);
	if(pojazd[trailerid][v_owner_type] == VEHICLE_BUSINESS)
	{
		cargocomp_OnTrailerAttached(playerid, trailerid);
	}
	else
	{
		cargofl_OnTrailerAttached(playerid, trailerid);
	}
	//synchro świateł
	new vehicleid = GetPlayerVehicleID(playerid);
	if(trailerid != 0 && vehicleid != 0)
	{
		new engine, lights, alarm, doors, bonnet, boot, objective;
		new engine2, lights2, alarm2, doors2, bonnet2, boot2, objective2;
		GetVehicleParamsEx(trailerid, engine, lights, alarm, doors, bonnet, boot, objective);
		GetVehicleParamsEx(vehicleid, engine2, lights2, alarm2, doors2, bonnet2, boot2, objective2);
		SetVehicleParamsEx(trailerid, engine, lights2, alarm, doors, bonnet, boot, objective);
	}
	return 1;
}

forward OnTrailerDetached(playerid, trailerid);//callback wywoływany przez sam skrypt HL
public OnTrailerDetached(playerid, trailerid)
{
	//printf("OnTrailerDetached(%d, %d);", playerid, trailerid);
	if(pojazd[trailerid][v_owner_type] == VEHICLE_BUSINESS)
	{
		cargocomp_OnTrailerDetached(playerid, trailerid);
	}
	else
	{
		cargofl_OnTrailerDetached(playerid, trailerid);
	}
	//synchro świateł
	if(trailerid != 0)
	{
		new engine, lights, alarm, doors, bonnet, boot, objective;
		GetVehicleParamsEx(trailerid, engine, lights, alarm, doors, bonnet, boot, objective);
		SetVehicleParamsEx(trailerid, engine, 0, alarm, doors, bonnet, boot, objective);
	}
	return 1;
}


public OnTrailerUpdate(playerid, vehicleid)
{
	gracz[playerid][opu_timestamp] = serwer[time_timestamp];
	if(IsVehicleTrailer(pojazd[vehicleid][v_model]))//tylko naczepy 
	{
		//do L-ek
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_DRVLICENSE)
		{
			pojazd[vehicleid][v_idletime] = serwer[time_timestamp];
			return 1;
		}
		//do skryptu truck - uprawnienia do naczep
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION)//naczepa jest frakcyjna
		{
			if(pojazd[gracz[playerid][opu_vehicleid]][v_owner_type] != VEHICLE_FRACTION)//truck nie jest firmowy
			{
				if(gracz[playerid][trailer_checkperm] != vehicleid)//zapobiega zbędnemu wywoływaniu poniższych funkcji, podczas kiedy są one w trakcie wywoływania
				{
					SetTimerEx("delay_CustomDetachTrailer", 1, false, "d", gracz[playerid][opu_vehicleid]);
					Error(playerid, "Nie możesz ciągnąć naczepy frakcyjnej, pojazdem niefrakcyjnym.");
					gracz[playerid][trailer_checkperm] = vehicleid;
				}
				DetachTrailerFromVehicle(gracz[playerid][opu_vehicleid]);
				return 1;
			}
			else//truck jest frakcyjny
			{
				if(pojazd[vehicleid][v_owner] != pojazd[gracz[playerid][opu_vehicleid]][v_owner])//naczepa jest innej frakcji co truck
				{
					if(gracz[playerid][trailer_checkperm] != vehicleid)//zapobiega zbędnemu wywoływaniu poniższych funkcji, podczas kiedy są one w trakcie wywoływania
					{
						SetTimerEx("delay_CustomDetachTrailer", 1, false, "d", gracz[playerid][opu_vehicleid]);
						Error(playerid, "Ta naczepa należy do innej frakcji.");
						gracz[playerid][trailer_checkperm] = vehicleid;
					}
					DetachTrailerFromVehicle(gracz[playerid][opu_vehicleid]);
					return 1;
				}
			}
		}
		//----
		else if(pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)//naczepa jest firmowa
		{
			if(pojazd[gracz[playerid][opu_vehicleid]][v_owner_type] != VEHICLE_BUSINESS)//truck nie jest firmowy
			{
				if(gracz[playerid][trailer_checkperm] != vehicleid)//zapobiega zbędnemu wywoływaniu poniższych funkcji, podczas kiedy są one w trakcie wywoływania
				{
					SetTimerEx("delay_CustomDetachTrailer", 1, false, "d", gracz[playerid][opu_vehicleid]);
					Error(playerid, "Nie możesz ciągnąć naczepy firmowej, pojazdem niefirmowym.");
					gracz[playerid][trailer_checkperm] = vehicleid;
				}
				DetachTrailerFromVehicle(gracz[playerid][opu_vehicleid]);
				return 1;
			}
			else//truck jest firmowy
			{
				if(pojazd[vehicleid][v_owner] != pojazd[gracz[playerid][opu_vehicleid]][v_owner])//naczepa jest innej firmy co truck
				{
					if(gracz[playerid][trailer_checkperm] != vehicleid)//zapobiega zbędnemu wywoływaniu poniższych funkcji, podczas kiedy są one w trakcie wywoływania
					{
						SetTimerEx("delay_CustomDetachTrailer", 1, false, "d", gracz[playerid][opu_vehicleid]);
						Error(playerid, "Ta naczepa należy do innej firmy.");
						gracz[playerid][trailer_checkperm] = vehicleid;
					}
					DetachTrailerFromVehicle(gracz[playerid][opu_vehicleid]);
					return 1;
				}
			}
		}
		//----
		else if(gracz[playerid][cargo_trailerdid] != vehicleid || pojazd[gracz[playerid][opu_vehicleid]][v_owner_type] == VEHICLE_BUSINESS || pojazd[gracz[playerid][opu_vehicleid]][v_owner_type] == VEHICLE_FRACTION)//pozostałe naczepy - freelancer
		{
			if(gracz[playerid][trailer_checkperm] != vehicleid)//zapobiega zbędnemu wywoływaniu poniższych funkcji, podczas kiedy są one w trakcie wywoływania
			{
				SetTimerEx("delay_CustomDetachTrailer", 1, false, "d", gracz[playerid][opu_vehicleid]);
				if(pojazd[gracz[playerid][opu_vehicleid]][v_owner_type] == VEHICLE_BUSINESS || pojazd[gracz[playerid][opu_vehicleid]][v_owner_type] == VEHICLE_FRACTION) Error(playerid, "Pojazdem firmowym nie możesz wykonywać zleceń dla freelancerów."); 
				else Error(playerid, "Nie posiadasz uprawnień do tej naczepy.");
				gracz[playerid][trailer_checkperm] = vehicleid;
			}
			DetachTrailerFromVehicle(gracz[playerid][opu_vehicleid]);
			return 1;
		}
		
		if(gracz[playerid][connected_trailervid] == 0)//if pilnujący OnTrailerAttached
		{
			gracz[playerid][connected_trailervid] = vehicleid;
			CallLocalFunction("OnTrailerAttached", "dd", playerid, gracz[playerid][connected_trailervid]);
		}
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_MPTRAILER)//tylko naczepy z towarami
		{
			pojazd[vehicleid][v_trailerupdate] = serwer[time_timestamp]+(MAX_RELOGTIME+1)*60;//minutka zapasu
		}
	}
	else//wszystko inne poza naczepami
	{
		if(gracz[playerid][towtruck_trailerid] != vehicleid) gracz[playerid][towtruck_trailerid] = vehicleid;
	}
	pojazd[vehicleid][v_idletime] = serwer[time_timestamp];
	GetVehiclePos(vehicleid, pojazd[vehicleid][v_idle_X], pojazd[vehicleid][v_idle_Y], pojazd[vehicleid][v_idle_Z]);
	GetVehicleZAngle(vehicleid, pojazd[vehicleid][v_idle_R]);
	return 1;
}

task delay_CustomDetachTrailer(fromvehicle)//Wywalić, jeśli bedzie bugowało - bedzie chodziło gorzej odczepianie ale bedzie (opóźnienie, bo rzucało pojazden - bug)
{
	DetachTrailerFromVehicle(fromvehicle);
	//SetVehicleToRespawn(vehicleid);
	new Float:vx, Float:vy, Float:vz;
	GetVehiclePos(fromvehicle, vx, vy, vz);
	GetXYInFrontOfVehicle(fromvehicle, vx, vy, 2.0);
	SetVehiclePos(fromvehicle, vx, vy, vz);
	return 1;
}


public OnVehicleDamageStatusUpdate(vehicleid, playerid)
{	
	new panels, doors, lights, tires;	
	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	if(tires != 0)
	{
		if(!IsVehicleWornOut(vehicleid, 0))
		{
			if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER || pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)
			{
				pojazd[vehicleid][v_damages_lifetime_km][0] = VehicleDamages[0][vd_exp_km]+1;
				format(pojazd[vehicleid][v_damages_lifetime_strdata], 256, "");//czyszczenie zmiennej
				for(new x; x < MAX_VEHICLEDAMAGES; x++)
				{
					pojazd[vehicleid][v_damages_lifetime_km][x]++;
					if(IsVehicleBike(pojazd[vehicleid][v_model]) && (x == 1 || x == 2)) pojazd[vehicleid][v_damages_lifetime_km][x] = 0;
					format(pojazd[vehicleid][v_damages_lifetime_strdata], 256, "%s%d ", pojazd[vehicleid][v_damages_lifetime_strdata], pojazd[vehicleid][v_damages_lifetime_km][x]);
				}
				if(pojazd[vehicleid][v_id] != 0)
				{
					mq_format("UPDATE `pojazdy` SET `przebieg`='%d', `przebiegunits`='%d', `paliwo`='%f', `eksploatacja`='%s' WHERE `id`='%d';", pojazd[vehicleid][v_przebieg], floatround(pojazd[vehicleid][v_przebiegunits]), pojazd[vehicleid][v_paliwo], pojazd[vehicleid][v_damages_lifetime_strdata], pojazd[vehicleid][v_id]);
					mq_send("QUpdateVehicle");
				}
			}
		}
	}
	pojazd[vehicleid][v_karoseria_hits]++;
	if(pojazd[vehicleid][v_id] != 0)
	{
		mq_format("UPDATE `pojazdy` SET `karoseria`='%d %d %d %d', `karoseria_hits`='%d' WHERE `id`='%d';", panels, doors, lights, tires, pojazd[vehicleid][v_karoseria_hits], pojazd[vehicleid][v_id]);
		mq_send("QZapisKaroserii");
	}
	//*ewentualnie uszkodzenie karoseri - WYKRYWANIE JEDNOKIERUNKOWE
	if(pojazd[vehicleid][v_uvds_panels] == 0 && panels != 0)
	{
		//zapiszmy tą informacje do logów pojazdów firmy
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)
		{
			new pid = IsVehicleInUseByDriver(vehicleid);
			LogCompany(gracz[pid][firma], gracz[pid][UID], gracz[pid][firma_sessionid], CLOGFLAG_POJAZD, "Uszkodzenie: maska/bagaznik. Pojazd: %s(UID: %d)", GetVehicleName(pojazd[vehicleid][v_model]), pojazd[vehicleid][v_id]);
		}
	}
	if(pojazd[vehicleid][v_uvds_panels] == 0 && doors != 0)
	{
		//zapiszmy tą informacje do logów pojazdów firmy
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)
		{
			new pid = IsVehicleInUseByDriver(vehicleid);
			LogCompany(gracz[pid][firma], gracz[pid][UID], gracz[pid][firma_sessionid], CLOGFLAG_POJAZD, "Uszkodzenie: drzwi. Pojazd: %s(UID: %d)", GetVehicleName(pojazd[vehicleid][v_model]), pojazd[vehicleid][v_id]);
		}
	}
	if(pojazd[vehicleid][v_uvds_panels] == 0 && lights != 0)
	{
		//zapiszmy tą informacje do logów pojazdów firmy
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)
		{
			new pid = IsVehicleInUseByDriver(vehicleid);
			LogCompany(gracz[pid][firma], gracz[pid][UID], gracz[pid][firma_sessionid], CLOGFLAG_POJAZD, "Uszkodzenie: swiatla. Pojazd: %s(UID: %d)", GetVehicleName(pojazd[vehicleid][v_model]), pojazd[vehicleid][v_id]);
		}
	}
	//*ewentualnie uszkodzenie karoseri  - WYKRYWANIE JEDNOKIERUNKOWE - END
	pojazd[vehicleid][v_uvds_panels] = panels;
	pojazd[vehicleid][v_uvds_doors] = doors;
	pojazd[vehicleid][v_uvds_lights] = lights;
	pojazd[vehicleid][v_uvds_tires] = tires;
	//printf(mQuery);
	return 1;	
}

stock Init_Vehicles()
{
	//config
	ManualVehicleEngineAndLights();
	//DisableOnPlayerNodeIDChange();
	//usuwanie lv lot z gps
	//**************************************wczytywanie pojazdu i odswiezanie hud
	serwer[first_time_loaderveh] = true;
	carshop_counter = 0;
	mq_format("SELECT * FROM `pojazdy` WHERE `owner_type`='%d' OR `owner_type`='%d' OR `owner_type`='%d';", VEHICLE_PUBLIC, VEHICLE_BUSINESS, VEHICLE_FRACTION);
	mq_send("LoadVehFromDB");
	SetTimer("CarHudRefresh", 550, 1);
	//******************************************CENY PALIW
	for(new fs; fs < MAX_CONCERNS; fs++)//narzucanie cen początkowych
	{
		if(fs == STATION_CPN)//dla cpn'ów
		{
			fuel_station_price[fs][F_PB] = MRandRange(STATIONS_MIN_PRICE_PB, STATIONS_MAX_PRICE_PB)+4;
			fuel_station_price[fs][F_ON] = MRandRange(STATIONS_MIN_PRICE_ON, STATIONS_MAX_PRICE_ON)+4;
			fuel_station_price[fs][F_LPG] = MRandRange(STATIONS_MIN_PRICE_LPG, STATIONS_MAX_PRICE_LPG)+4;
		}
		else
		{
			fuel_station_price[fs][F_PB] = MRandRange(STATIONS_MIN_PRICE_PB, STATIONS_MAX_PRICE_PB);
			fuel_station_price[fs][F_ON] = MRandRange(STATIONS_MIN_PRICE_ON, STATIONS_MAX_PRICE_ON);
			fuel_station_price[fs][F_LPG] = MRandRange(STATIONS_MIN_PRICE_LPG, STATIONS_MAX_PRICE_LPG);
		}
	}

	Init_FuelStation();
	//*********************************************KAŻDY pojazd ma z góry nałożony 3dtexdt label
	SetTimer("FlashLights", 150, true);//migające światła syren
	SetTimer("Process_VehicleDistanceFuel", 300, true);
	return 1;
}


task LoadVehFromDB()
{
	mq_getdata();
	new i;
	new strTemp[512];
	if(rekordy)
	{
		new tid, tmodel, tcolor_0, tcolor_1, Float:tpaliwo, towner_type, towner, tprzebieg, tprzebiegunits, trlg_lastused;
		new tkaroseria_hits;
		new teksploatacja[256];
		new tkaroseria[256];
		new ttunedata[256];
		new Float:thp;
		new Float:tX, Float:tY, Float:tZ, Float:tR;
		new vehicleid;
		while(i < rekordy)
		{
			cache_get_value_name_int(i, "id", 			tid);
			if(VehicleUidToVehicleid(tid) == -1)//pojazd nie istnieje na mapie
			{
				cache_get_value_name_int(i, "model", 				tmodel);
				
				cache_get_value_name_float(i, "X", 				tX);
				cache_get_value_name_float(i, "Y", 				tY);
				cache_get_value_name_float(i, "Z", 				tZ);
				cache_get_value_name_float(i, "R", 				tR);
				
				//if(IsVehicleTrailer(tmodel) && tmodel != 584) tZ -= 2.0;//korekcja pozycji dla naczep
				
				cache_get_value_name_int(i, "color_0", 				tcolor_0);
				cache_get_value_name_int(i, "color_1", 				tcolor_1);
				cache_get_value_name_float(i, "paliwo", 				tpaliwo);
				cache_get_value_name_int(i, "owner_type", 				towner_type);
				cache_get_value_name_int(i, "owner", 				towner);
				cache_get_value_name_int(i, "przebieg", 				tprzebieg);
				cache_get_value_name_int(i, "przebiegunits", 				tprzebiegunits);
				cache_get_value_name_int(i, "rlg_lastused", 				trlg_lastused);
				cache_get_value_name_int(i, "karoseria_hits", 				tkaroseria_hits);
				cache_get_value_name_float(i, "hp", 				thp);
				//************************************************************************DANE JESZCZE NIE SĄ W GŁÓWNYCH ZMIENNYCH
				if(towner_type == VEHICLE_PLAYER && (trlg_lastused+60*5) > serwer[time_timestamp])//wczytuje pojazd po relogu w ostatniej zapamiętanej pozycji
				{
					new Float:t_cache[4];
					cache_get_value_name_float(i, "temp_x", t_cache[0]);
					cache_get_value_name_float(i, "temp_y", t_cache[1]);
					cache_get_value_name_float(i, "temp_z", t_cache[2]);
					cache_get_value_name_float(i, "temp_r", t_cache[3]);
					vehicleid = CreateVehicle(tmodel, t_cache[0], t_cache[1], t_cache[2],  t_cache[3], tcolor_0, tcolor_1, VEH_SINGLERESP_TIME);
					
					cache_get_value_name_int(i, "rlg_c_id", 					pojazd[vehicleid][v_cargo]);
					cache_get_value_name_int(i, "rlg_c_amount", 					pojazd[vehicleid][v_cargo_amount]);
					cache_get_value_name_int(i, "rlg_c_price", 					pojazd[vehicleid][v_cargo_price]);
					cache_get_value_name_int(i, "rlg_c_score", 					pojazd[vehicleid][v_cargo_score]);
					cache_get_value_name_float(i, "rlg_c_distance", 					pojazd[vehicleid][v_cargo_distance]);
					cache_get_value_name_float(i, "rlg_c_tX", 					pojazd[vehicleid][v_cargo_target_X]);
					cache_get_value_name_float(i, "rlg_c_tY", 					pojazd[vehicleid][v_cargo_target_Y]);
					cache_get_value_name_float(i, "rlg_c_tZ", 					pojazd[vehicleid][v_cargo_target_Z]);
				}
				else if(towner_type == VEHICLE_FRACTION)//pojazdy frakcyjne (dodawanie syren etc)
				{
					if(towner == F_POLICE)
					{
						if(tmodel == 560 || tmodel == 502)//sultan & hotring
						{
							vehicleid = CreateVehicle(tmodel, tX, tY, tZ, tR, tcolor_0, tcolor_1, VEH_SINGLERESP_TIME, 1);
						}
						else vehicleid = CreateVehicle(tmodel, tX, tY, tZ, tR, tcolor_0, tcolor_1, VEH_SINGLERESP_TIME);
					}
					else if(towner == F_BORDERGUARD)
					{
						if(tmodel == 579 || tmodel == 495)//huntley & sandking
						{
							vehicleid = CreateVehicle(tmodel, tX, tY, tZ, tR, tcolor_0, tcolor_1, VEH_SINGLERESP_TIME, 1);
						}
						else vehicleid = CreateVehicle(tmodel, tX, tY, tZ, tR, tcolor_0, tcolor_1, VEH_SINGLERESP_TIME);
					}
					else vehicleid = CreateVehicle(tmodel, tX, tY, tZ, tR, tcolor_0, tcolor_1, VEH_SINGLERESP_TIME);
				}
				else vehicleid = CreateVehicle(tmodel, tX, tY, tZ, tR, tcolor_0, tcolor_1, VEH_SINGLERESP_TIME);
				cache_get_value_name(i, "numberplate", pojazd[vehicleid][v_numberplate], 32);
				SetVehicleParamsEx(vehicleid, 0, 0, 0, 0, 0, 0, 0);
				SetVehicleParamsCarWindows(vehicleid, 1, 1, 1, 1);
				if(strlen(pojazd[vehicleid][v_numberplate]) > 1) SetVehicleNumberPlate(vehicleid, pojazd[vehicleid][v_numberplate]);
				else SetVehicleNumberPlate(vehicleid, VEH_REG);
				//************************************************************************DOPIERO TUTAJ JEST ŁADOWANIE DO WŁAŚCIWYCH ZMIENNYCH
				pojazd[vehicleid][v_id] = tid;
				pojazd[vehicleid][v_model] = tmodel;
	
				pojazd[vehicleid][v_X] = tX;
				pojazd[vehicleid][v_Y] = tY;
				pojazd[vehicleid][v_Z] = tZ;
				pojazd[vehicleid][v_R] = tR;
	
				pojazd[vehicleid][v_color][0] = tcolor_0;
				pojazd[vehicleid][v_color][1] = tcolor_1;
				pojazd[vehicleid][v_paliwo] = tpaliwo;
				pojazd[vehicleid][v_owner_type] = towner_type;
				pojazd[vehicleid][v_owner] = towner;
				pojazd[vehicleid][v_przebieg] = tprzebieg;
				pojazd[vehicleid][v_przebiegunits] = tprzebiegunits;
				pojazd[vehicleid][v_karoseria_hits] = tkaroseria_hits;
				cache_get_value_name_int(i, "paintjob", 				pojazd[vehicleid][v_paintjob]);
				cache_get_value_name_int(i, "neon_modelid", 				pojazd[vehicleid][v_neon_modelid]);

				if(pojazd[vehicleid][v_paliwo] >= 9999) pojazd[vehicleid][v_paliwo] = GetVehicleFuelSize(pojazd[vehicleid][v_model]);//tankowanie do pełna
				if(!SpecialVehicle(vehicleid)) Handbrake(vehicleid, 1);
				if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER || pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)
				{
					//wczytywanie eksploatacji dla pojazdów gracza
					cache_get_value_name(i, "eksploatacja", teksploatacja);
					new sscanf_format[16];
					format(sscanf_format, 16, "a<i>[%d]", MAX_VEHICLEDAMAGES);
					sscanf(teksploatacja, sscanf_format, pojazd[vehicleid][v_damages_lifetime_km]);
					//wczytywanie karoserii
					cache_get_value_name(i, "karoseria", tkaroseria);
					new panels, doors, lights, tires;
					sscanf(tkaroseria, "dddd", panels, doors, lights, tires);
					UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
					pojazd[vehicleid][v_uvds_panels] = panels;
					pojazd[vehicleid][v_uvds_doors] = doors;
					pojazd[vehicleid][v_uvds_lights] = lights;
					pojazd[vehicleid][v_uvds_tires] = tires;
					//GetVehicleDamageStatus(vehicleid, pojazd[vehicleid][v_uvds_panels], pojazd[vehicleid][v_uvds_doors], pojazd[vehicleid][v_uvds_lights], pojazd[vehicleid][v_uvds_tires]);
					//wczytywanie HP
					SetVehicleHealth(vehicleid, thp);
					pojazd[vehicleid][v_HP] = thp;
					//wczytywanie tuningu
					cache_get_value_name(i, "tunedata", ttunedata);
					format(sscanf_format, 16, "a<i>[%d]", 32);
					sscanf(ttunedata, sscanf_format, pojazd[vehicleid][v_tune_data]);
					ChangeVehiclePaintjob(vehicleid, TranslateVehPaintjob(pojazd[vehicleid][v_paintjob]));
					//neony
					if(pojazd[vehicleid][v_neon_modelid] != 0)
					{
						if(pojazd[vehicleid][v_object][8] == 0)
						{
							pojazd[vehicleid][v_object][8] = CreateDynamicObject(pojazd[vehicleid][v_neon_modelid], 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
							//AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][8], vehicleid, 0.8000, 0.0570, -0.4655, 0.0, 0.0, 0.0);//1 strona
						}
						if(pojazd[vehicleid][v_object][9] == 0)
						{
							pojazd[vehicleid][v_object][9] = CreateDynamicObject(pojazd[vehicleid][v_neon_modelid], 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
							//AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][9], vehicleid, -0.8000, 0.0570, -0.4655, 0.0, 0.0, 0.0);//druga strona
						}
					}
				}
				else if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC)
				{
					if(pojazd[vehicleid][v_owner] == VO_MPTRAILER) //naczepy free lancer
					{
						new strSrcZone[32];
						Get2DZone(tX, tY, strSrcZone, 32);
						//new nearestnode = NearestNodeFromPoint(tX, tY, tZ);
						if(OptLocationLocked(strSrcZone))
						{
							RemoveVehicle(vehicleid);
						}
						else
						{
							pojazd[vehicleid][v_text3d] = CreateDynamic3DTextLabel("odbiór naczepy - inicjacja...", -1, tX, tY, tZ+0.3, 20.0, .attachedvehicle = vehicleid);
						}
						//new newnode =  AddNode(tX, tY, tZ);
						//ConnectNodes(nearestnode, newnode);
					} 
					else
					{
						AttachCourierLogoToVehicle(vehicleid, pojazd[vehicleid][v_owner]);
						pojazd[vehicleid][v_paliwo] = GetVehicleFuelSize(pojazd[vehicleid][v_model]);//tankowanie do pełna
					}
					if(pojazd[vehicleid][v_owner] == VO_CARSHOP) 
					{
						//Handbrake(vehicleid, 1);
						for(new v; v < MAX_CARSPEC; v++)
						{
							if(pojazd_spec[v][vspec_model] == pojazd[vehicleid][v_model])
							{
								carshop_specid[carshop_counter] = v;
								carshop_price[carshop_counter] = CalcVehiclePriceEx(pojazd_spec[v][vspec_model]);
								format(strTemp, 512, "{%06x}••••••••••••••••••••••••••••••••••••••••••••••••••", VehicleColoursTableRGBA[tcolor_0] >>> 8);
								format(strTemp, 512, "%s\n{FFCE00}%d$ ", strTemp, carshop_price[carshop_counter]);
								format(strTemp, 512, "%s\n{7DFC9C}%s", strTemp, LastTextOtherCol(pojazd_spec[v][vspec_name], 0xFFFFFFFF));
								if(pojazd_spec[v][vspec_fueltype] == F_PB) format(strTemp, 512, "%s\n{428FB8}TYP PALIWA:"COL_GREEN" PB", strTemp);
								else if(pojazd_spec[v][vspec_fueltype] == F_ON) format(strTemp, 512, "%s\n{428FB8}TYP PALIWA:{6D6D6D} ON", strTemp);
								format(strTemp, 512, "%s\n{6DC5F3}POJEMNOŚĆ ZBIORNIKA:{45A081} %d "COL_WHITE"[litr]", strTemp, pojazd_spec[v][vspec_tanksize]);
								format(strTemp, 512, "%s\n{428FB8}SPALANIE:{45A081} %0.1f "COL_WHITE"[litr/100km]", strTemp, pojazd_spec[v][vspec_fuelconsumption]+0.01);
								format(strTemp, 512, "%s\n{6DC5F3}PRZYŚPIESZENIE (0-100):{45A081} %0.1f "COL_WHITE"[sekund]", strTemp, pojazd_spec[v][vspec_0100]+0.01);
								format(strTemp, 512, "%s\n{428FB8}PRĘDKOŚĆ MAXYMALNA (V-MAX):{45A081} %d "COL_WHITE"[km/h]", strTemp, pojazd_spec[v][vspec_vmax]);
								format(strTemp, 512, "%s\n{%06x}••••••••••••••••••••••••••••••••••••••••••••••••••", strTemp, VehicleColoursTableRGBA[tcolor_0] >>> 8);
								format(carshop_buylist, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"%s\t{FFCE00}%d$\t"COL_LIME"«•", carshop_buylist, pojazd_spec[v][vspec_name], carshop_price[carshop_counter]);
								break;
							}
						}
						carshop_db_id[carshop_counter] = pojazd[vehicleid][v_id];
						SetVehicleParamsEx(vehicleid, 0, 0, 0, 1, 0, 0, 0);
						carshop_3dtext_id[carshop_counter] = CreateDynamic3DTextLabel(strTemp, -1, tX, tY, tZ+0.3, 10.0);
						if(carshop_counter < 10) carshop_counter++;	
					}
					else if(pojazd[vehicleid][v_owner] == VO_TRUCKSHOP)
					{
						//Handbrake(vehicleid, 1);
						new bool:found = false;
						pojazd[vehicleid][v_color][0] = random(255);
						pojazd[vehicleid][v_color][1] = random(255);
						tcolor_0 = pojazd[vehicleid][v_color][0];
						tcolor_1 = pojazd[vehicleid][v_color][1];
						ChangeVehicleColor(vehicleid, tcolor_0, tcolor_1);
						for(new v; v < MAX_CARSPEC; v++)
						{
							if(IsVehicleTruck(pojazd[vehicleid][v_model]) && pojazd[vehicleid][v_model] == pojazd_spec[v][vspec_model])
							{
								truckshop_price[truckshop_counter] = CalcVehiclePriceEx(pojazd[vehicleid][v_model]);
								format(strTemp, 512, "{%06x}••••••••••••••••••••••••••••••••••••••••••••••••••", VehicleColoursTableRGBA[tcolor_0] >>> 8);
								format(strTemp, 512, "%s\n{FFCE00}%d$ ", strTemp, truckshop_price[truckshop_counter]);
								format(strTemp, 512, "%s\n{7DFC9C}%s", strTemp, LastTextOtherCol(pojazd_spec[v][vspec_name], 0xFFFFFFFF));
								if(pojazd_spec[v][vspec_fueltype] == F_PB) format(strTemp, 512, "%s\n{428FB8}TYP PALIWA:"COL_GREEN" PB", strTemp);
								else if(pojazd_spec[v][vspec_fueltype] == F_ON) format(strTemp, 512, "%s\n{428FB8}TYP PALIWA:{6D6D6D} ON", strTemp);
								format(strTemp, 512, "%s\n{6DC5F3}POJEMNOŚĆ ZBIORNIKA:{45A081} %d "COL_WHITE"[litr]", strTemp, pojazd_spec[v][vspec_tanksize]);
								format(strTemp, 512, "%s\n{428FB8}SPALANIE:{45A081} %0.1f "COL_WHITE"[litr/100km]", strTemp, pojazd_spec[v][vspec_fuelconsumption]+0.01);
								format(strTemp, 512, "%s\n{6DC5F3}PRZYŚPIESZENIE (0-100):{45A081} %0.1f "COL_WHITE"[sekund]", strTemp, pojazd_spec[v][vspec_0100]+0.01);
								format(strTemp, 512, "%s\n{428FB8}PRĘDKOŚĆ MAXYMALNA (V-MAX):{45A081} %d "COL_WHITE"[km/h]", strTemp, pojazd_spec[v][vspec_vmax]);
								if(VehicleCapacity(pojazd[vehicleid][v_model])) format(strTemp, 512, "%s\n{6DC5F3}ŁADOWNOŚĆ: {FF8100}%d "COL_WHITE"[kg]", strTemp,VehicleCapacity(pojazd[vehicleid][v_model]));
								format(strTemp, 512, "%s\n{%06x}••••••••••••••••••••••••••••••••••••••••••••••••••", strTemp, VehicleColoursTableRGBA[tcolor_0] >>> 8);
								found = true;
								break;
							}
						}
						if(!found)//naczepy
						{ 
							truckshop_price[truckshop_counter] = CalcVehiclePriceEx(pojazd[vehicleid][v_model]);
							format(strTemp, 512, "{%06x}••••••••••••••••••••••••••••••••••••••••••••••••••", VehicleColoursTableRGBA[tcolor_0] >>> 8);
							format(strTemp, 512, "%s\n{FFCE00}%d$ ", strTemp, truckshop_price[truckshop_counter]);
							format(strTemp, 512, "%s\n{7DFC9C}%s", strTemp, LastTextOtherCol(GetVehicleName(pojazd[vehicleid][v_model]), 0xFFFFFFFF));
							format(strTemp, 512, "%s\n{6DC5F3}ŁADOWNOŚĆ: {FF8100}%d "COL_WHITE"[kg]", strTemp,VehicleCapacity(pojazd[vehicleid][v_model]));
							format(strTemp, 512, "%s\n{%06x}••••••••••••••••••••••••••••••••••••••••••••••••••", strTemp, VehicleColoursTableRGBA[tcolor_0] >>> 8);
						}
						SetVehicleParamsEx(vehicleid, 0, 0, 0, 1, 0, 0, 0);
						CreateDynamic3DTextLabel(strTemp, -1, tX, tY, tZ+0.3, 20.0);
						truckshop_db_id[truckshop_counter] = pojazd[vehicleid][v_id];
						if(truckshop_counter < MAX_SALONTRUCKSLOTS-1) truckshop_counter++;
					}
					else if(pojazd[vehicleid][v_owner] == VO_DRVLICENSE)//L-ki
					{
						if(pojazd[vehicleid][v_model] == 589)//CLUB
						{
							pojazd[vehicleid][v_object][0] = CreateDynamicObject(19475,0,0,-1000,0,0,0);
							AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.305000,1.199999,0.000000,-15.120001,-269.999908);
							SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][0], 0, "L", 130, "Arial", 250, 1, -1, -16776961, 1);
	
							pojazd[vehicleid][v_object][1] = CreateDynamicObject(19475,0,0,-1000,0,0,0);
							AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][1], vehicleid, 0.000000,-0.404999,1.199999,0.000000,-15.120001,269.999786);
							SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][1], 0, "L", 130, "Arial", 250, 1, -1, -16776961, 1);
						}
						else if(pojazd[vehicleid][v_model] == 514)//Tanker
						{
							pojazd[vehicleid][v_object][0] = CreateDynamicObject(19475,0,0,-1000,0,0,0);
							AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.890000,4.384999,-0.904999,0.000000,0.000000,90.180000);
							SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][0], 0, "L", 130, "Arial", 190, 1, -1, -16776961, 1);
						}
						else if(pojazd[vehicleid][v_model] == 591)//Naczepa
						{
							pojazd[vehicleid][v_object][0] = CreateDynamicObject(19475,0,0,-1000,0,0,0);
							AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, -0.974999,-3.910001,-0.514999,0.000000,0.000000,-90.180000);
							SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][0], 0, "L", 130, "Arial", 250, 1, -1, -16776961, 1);
						}
					}
				}
				else if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION)
				{
					pojazd[vehicleid][v_paliwo] = GetVehicleFuelSize(pojazd[vehicleid][v_model]);//tankowanie do pełna
					AttachObjectsToFractionVeh(vehicleid, pojazd[vehicleid][v_owner]);
					if(pojazd[vehicleid][v_owner] == F_TAXI)//standardowe ustawienia taxometrów
					{
						pojazd[vehicleid][v_taxometr_price_per_km] = 50;
					}
				}
			}
			i++;
		}
	}
	if(serwer[first_time_loaderveh]) 
	{
		serwer[first_time_loaderveh] = false;
		printf("[LOAD] Zaladowano %d pojazdow.", i);
		GenererateCarSalonCarRotation();
		for(new b=0;b<MAX_VEHICLES;b++)//pętla dla wszystkich aut
		{
			Blink[b][0] = -1;
			Blink[b][1] = -1;
			Blink[b][2] = -1;
			Blink[b][3] = -1;
		}
		//kolejnosc pojazdów w truck w salonie dla kamery
		truckshop_counter = 0;
		//sortujemy według kolejnoścy kolejki kamery
		for(new q; q < sizeof(truckshop_cameraquery); q++)
		{
			for(new v = GetVehiclePoolSize(); v != -1; v--)
			{
				if(truckshop_cameraquery[q] == pojazd[v][v_model] &&  pojazd[v][v_owner_type] == VEHICLE_PUBLIC && pojazd[v][v_owner] == VO_TRUCKSHOP)
				{
					truckshop_db_id[truckshop_counter] = pojazd[v][v_id];
					truckshop_price[truckshop_counter] = CalcVehiclePriceEx(pojazd[v][v_model]);
					for(new s; s < MAX_CARSPEC; s++)//id specyfikacji
					{
						if(pojazd_spec[s][vspec_model] == pojazd[v][v_model])
						{
							truckshop_specid[truckshop_counter] = s;
						}
					}
					if(truckshop_counter < MAX_SALONTRUCKSLOTS-1) truckshop_counter++;
				}
			}
		}
		//
		Init_TransportFreelancer();
		for(new v = GetVehiclePoolSize(); v != -1; v--)
		{
			SetVehicleToRespawn(v);
		}
	}
	return 1;
}


forward CarHudRefresh();
public CarHudRefresh()
{
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(!IsPlayerConnected(p)) continue;
		if(IsPlayerNPC(p)) continue;
		if(!gracz[p][spawned]) continue;
		if(!gracz[p][loggedin]) continue;
		Process_CarHUD(p);
	}
	return 1;
}


stock IsVehicleInUse(vehicleid)
{
	for(new i = PlayerPoolSize(); i != -1; i--)
	{
		if(IsPlayerInVehicle(i, vehicleid)) return i;
	}
	return INVALID_PLAYER_ID;
}

stock IsVehicleInUseByDriver(vehicleid)
{
	for(new i = PlayerPoolSize(); i != -1; i--)
	{
		if(GetPlayerVehicleSeat(i) == 0)
		{
			if(IsPlayerInVehicle(i, vehicleid)) return i;
		}
	}
	return INVALID_PLAYER_ID;
}

stock RemoveVehicle(vehicleid, bool:cleardata = true)
{
	BlinkSystem_DisableBlinks(vehicleid);
	TrafficLight(vehicleid, 0);
	if(cleardata)
	{
		if(IsValidDynamic3DTextLabel(pojazd[vehicleid][v_text3d]))
		{
			DestroyDynamic3DTextLabel(pojazd[vehicleid][v_text3d]);
			//printf("[DEBUG] Usuwam 3DTextLabel: %d dla vehicleid: %d", pojazd[vehicleid][v_text3d], vehicleid);
		}
		for(new i; i < MAX_VEHICLE_OBJECTS; i++)
		{
			if(pojazd[vehicleid][v_object][i] != 0) 
			{
				//printf("[DEBUG] RemoveVehicle->Destroy Objects->Model=%d", GetDynamicObjectModel(pojazd[vehicleid][v_object][i]));
				DestroyDynamicObject(pojazd[vehicleid][v_object][i]);
				pojazd[vehicleid][v_object][i] = 0;
			}
		}
		for(new pojazd_info:r; r < pojazd_info; r++)
		{
			pojazd[vehicleid][r] = 0;
		}
	}
	DestroyVehicle(vehicleid);
	return 1;
}

stock Handbrake(vehicleid, status)
{
	pojazd[vehicleid][v_handbrake] = status;
	GetVehiclePos(vehicleid, pojazd[vehicleid][v_handbrake_posX], pojazd[vehicleid][v_handbrake_posY], pojazd[vehicleid][v_handbrake_posZ]);
	GetVehicleZAngle(vehicleid, pojazd[vehicleid][v_handbrake_posR]);
	if(pojazd[vehicleid][v_id] != 0)
	{
		mq_format("UPDATE `pojazdy` SET `temp_x`='%f', `temp_y`='%f', `temp_z`='%f', `temp_r`='%f', `rlg_lastused`='%d' WHERE `id`='%d';",pojazd[vehicleid][v_handbrake_posX], pojazd[vehicleid][v_handbrake_posY], pojazd[vehicleid][v_handbrake_posZ], pojazd[vehicleid][v_handbrake_posR], serwer[time_timestamp], pojazd[vehicleid][v_id]);
		mq_send("QUpdateVehicle");
	}
	return 1;
}

stock VehicleUidToVehicleid(vehicleuid)//-1 - nie istnieje
{
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		if(pojazd[v][v_id] == vehicleuid) return v;
	}
	return -1;
}

stock VehicleStatus(status)
{
	new strTemp[32];
	switch(status)
	{
		case 0: format(strTemp, 32, ""COL_ORANGE"Niestworzony");
		case 1: format(strTemp, 32, ""COL_GREEN"Stworzony");
		case 2: format(strTemp, 32, ""COL_RED"Auto Szrot");
		case 3: format(strTemp, 32, ""COL_BLUE"Parking policyjny");
	}
	return strTemp;
}

stock GetVehicleFreeID()
{
	for(new v; v < WORLD_VEHICLES; v++)
	{
		if(!pojazd[v][v_id]) return v;
	}
	return 0;
}


task Process_CarHUD(playerid)
{
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{
		CarHUD_Hide(playerid);
		Dystrybutor_Hide(playerid);
		return 0;
	}
	new vehicleid = GetPlayerVehicleID(playerid);
	new model = pojazd[vehicleid][v_model];
	if(IsPlayerCanDrive(playerid, vehicleid)) pojazd[vehicleid][v_idletime] = serwer[time_timestamp];
	if(GetVehicleTrailer(vehicleid) == 0)
	{
		if(gracz[playerid][connected_trailervid] != 0)
		{
			CallLocalFunction("OnTrailerDetached", "dd", playerid, gracz[playerid][connected_trailervid]);
			gracz[playerid][connected_trailervid] = 0;
		}
		if(gracz[playerid][trailer_checkperm] != 0) gracz[playerid][trailer_checkperm] = 0;
		if(gracz[playerid][towtruck_trailerid] != 0) 
		{
			new towedid = gracz[playerid][towtruck_trailerid];
			Handbrake(towedid, 1);
			gracz[playerid][towtruck_trailerid] = 0;
		}
	}
	if(SpecialVehicle(vehicleid)) return 1;
	if(gracz[playerid][delay_enable_engine])
	{
		Dystrybutor_Hide(playerid);
		if(gracz[playerid][carhud_blinkfueltemp])
		{
			CarHUD_SetFuel(playerid, 0);
			CarHUD_SetTemp(playerid, 0);
			gracz[playerid][carhud_blinkfueltemp] = false;
		}
		else
		{
			CarHUD_SetFuel(playerid, 100);
			CarHUD_SetTemp(playerid, 100);
			gracz[playerid][carhud_blinkfueltemp] = true;
		}
		return 1;
	}
	new fuel_type = GetVehicleFuelType(model);
	new fuel_size = GetVehicleFuelSize(model);
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	GetPlayerKeys(playerid, gracz[playerid][gpk_keys], gracz[playerid][gpk_updown], gracz[playerid][gpk_leftright]);
	if(!engine) //zgaszony
	{
		CarHUD_SpeedLight(playerid, false);
		CarHUD_FuelWarning(playerid, false);
		CarHUD_TempWarning(playerid, false);
		CarHUD_DistanceLight(playerid, false);
		CarHUD_SERVICE(playerid, false);
		CarHUD_Battery(playerid, false);
		CarHUD_SetFuel(playerid, 0);
		CarHUD_SetTemp(playerid, 0);
		TruckSmokeEffect(vehicleid, 0);
		pojazd[vehicleid][v_nitrotime] = 0;
		CarHUD_Nitro(playerid, -1);
		if(pojazd[vehicleid][v_tune_data][5] != 0)//ma nitro na wyposażeniu
		{
			if(pojazd[vehicleid][v_whilenitro])
			{
				RemoveVehicleComponent(vehicleid, pojazd[vehicleid][v_tune_data][5]);
				AddVehicleComponent(vehicleid, pojazd[vehicleid][v_tune_data][5]);
				pojazd[vehicleid][v_whilenitro] = false;
			}
		}
	}
	else//odpalony
	{
		CarHUD_SpeedLight(playerid, true);
		CarHUD_DistanceLight(playerid, true);

		if(pojazd[vehicleid][v_enginetemp] > 70.0) CarHUD_SetTemp(playerid, procent(pojazd[vehicleid][v_enginetemp]-70.0, 40));
		else CarHUD_SetTemp(playerid, 0);

		if(pojazd[vehicleid][v_enginetemp] > 101) CarHUD_TempWarning(playerid, true);
		else CarHUD_TempWarning(playerid, false);

		if(pojazd[vehicleid][v_paliwo] > 0.0)
		{
			new paliwo_proc = procent(pojazd[vehicleid][v_paliwo], fuel_size);
			CarHUD_SetFuel(playerid, paliwo_proc);
			if(paliwo_proc <= 15) 
			{
				CarHUD_FuelWarning(playerid, true);
				if(gracz[playerid][fuel_warning_timestamp] < serwer[time_timestamp] || gracz[playerid][fuel_warning_timestamp] == 0)
				{
					gracz[playerid][fuel_warning_timestamp] = serwer[time_timestamp]+30;
					LeftNotifyShow(playerid, "Paliwo", "Malo paliwa! ~r~Odwiedz stacje i zatankuj pojazd!", LN_RED);
				}
			}
			else CarHUD_FuelWarning(playerid, false);
		}
		else 
		{
			CarHUD_FuelWarning(playerid, true);
			CarHUD_SetFuel(playerid, 0);
		}

		if(gracz[playerid][gpk_keys] == KEY_SPRINT)//invehicle sprint == VEHICLE_ACCELERATE
		{
			if(gracz[playerid][opu_speed] < 60) TruckSmokeEffect(vehicleid, 1);
			else TruckSmokeEffect(vehicleid, 2);
		} else TruckSmokeEffect(vehicleid, 0);

		//nitro
		if(pojazd[vehicleid][v_tune_data][5] != 0)//ma nitro na wyposażeniu
		{
			if(pojazd[vehicleid][v_whilenitro])//ma uruchomione nitro
			{
				if(pojazd[vehicleid][v_nitrotime] <= 0)
				{
					RemoveVehicleComponent(vehicleid, pojazd[vehicleid][v_tune_data][5]);
					//AddVehicleComponent(vehicleid, pojazd[vehicleid][v_tune_data][5]);
					CarHUD_Nitro(playerid, 0);
					GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~n~~r~NITRO:~y~ OVER",  1000, 3);
					pojazd[vehicleid][v_whilenitro] = false;
				}	
				else
				{
					if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER || pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)
					{
						new nitro = pojazd[vehicleid][v_tune_data][5];
						if(nitro > 1000)
						{
							switch(nitro)
							{
								case 1008: pojazd[vehicleid][v_paliwo] -= pojazd_spec[GetVehicleSpecID(pojazd[vehicleid][v_model])][vspec_fuelconsumption]/70.0;//nitro 5x
								case 1009: pojazd[vehicleid][v_paliwo] -= pojazd_spec[GetVehicleSpecID(pojazd[vehicleid][v_model])][vspec_fuelconsumption]/90.0;//nitro 2x
								case 1010: pojazd[vehicleid][v_paliwo] -= pojazd_spec[GetVehicleSpecID(pojazd[vehicleid][v_model])][vspec_fuelconsumption]/40.0;//nitro 10x
							}
						}
						if(pojazd[vehicleid][v_paliwo] < 0.0) pojazd[vehicleid][v_paliwo] = 0.0;
					}
					pojazd[vehicleid][v_nitrotime]--;
					if(pojazd[vehicleid][v_nitrotime] < 0) pojazd[vehicleid][v_nitrotime] = 0;
					CarHUD_Nitro(playerid, pojazd[vehicleid][v_nitrotime]);
				}
			}
			else
			{
				if(pojazd[vehicleid][v_nitrotime] < 15) 
				{
					if(gracz[playerid][holding_key_nitro] < serwer[time_timestamp]) pojazd[vehicleid][v_nitrotime]++;
					else GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~n~~r~NITRO:~y~ OVER",  1000, 3);
					if(pojazd[vehicleid][v_nitrotime] > 5)
					{
						if(GetVehicleComponentInSlot(vehicleid, 5) == 0)
						{
							AddVehicleComponent(vehicleid, pojazd[vehicleid][v_tune_data][5]);
						}
					}
					CarHUD_Nitro(playerid, pojazd[vehicleid][v_nitrotime]);
				}
			}
		}
		else
		{
			CarHUD_Nitro(playerid, -1);
		}
	}

	if(pojazd[vehicleid][v_trafficlights]) 
	{
		CarHUD_Light(playerid, 2);
	}
	else if(lights)
	{
		CarHUD_Light(playerid, 1);
	}
	else 
	{
		CarHUD_Light(playerid, 0);
	}

	if(pojazd[vehicleid][v_handbrake]) CarHUD_HandBrake(playerid, true);
	else CarHUD_HandBrake(playerid, false);

	if(doors) CarHUD_Closed(playerid, true);
	else CarHUD_Closed(playerid, false);

	if(gracz[playerid][pasy]) CarHUD_Seatbelts(playerid, false);
	else 
	{
		if(gracz[playerid][opu_speed] > 60)
		{
			if(gracz[playerid][td_seatbelts_blinksw])
			{
				CarHUD_Seatbelts(playerid, false);
				gracz[playerid][td_seatbelts_blinksw] = false;
			}
			else
			{
				CarHUD_Seatbelts(playerid, true);
				gracz[playerid][td_seatbelts_blinksw] = true;
				//PlayerPlaySound(playerid, 5205, 0.0, 0.0, 0.0);
			}
		}
		else CarHUD_Seatbelts(playerid, true);
	}

	CarHUD_SetDistance(playerid, pojazd[vehicleid][v_przebieg]);

	pojazd[vehicleid][v_speed] = gracz[playerid][opu_speed];

	new bool:service = false;
	for(new x; x < MAX_VEHICLEDAMAGES; x++)
	{
		if(IsVehicleWornOut(vehicleid, x))
		{
			service = true;
			break;
		}
	}
	if(service) CarHUD_SERVICE(playerid, true);
	else CarHUD_SERVICE(playerid, false);

	
	if(Blink[vehicleid][0] != -1)
	{
		if(gracz[playerid][carhud_blinkstatus][0] == 0)
		{
			gracz[playerid][carhud_blinkstatus][0] = 1;
		}
		else if(gracz[playerid][carhud_blinkstatus][0] == 1)
		{
			gracz[playerid][carhud_blinkstatus][0] = 0;
		}
	}
	else
	{
		gracz[playerid][carhud_blinkstatus][0] = 0;
	}
	if(Blink[vehicleid][2] != -1)
	{
		if(gracz[playerid][carhud_blinkstatus][1] == 0)
		{
			gracz[playerid][carhud_blinkstatus][1] = 1;
		}
		else if(gracz[playerid][carhud_blinkstatus][1] == 1)
		{
			gracz[playerid][carhud_blinkstatus][1] = 0;
		}
	}
	else
	{
		gracz[playerid][carhud_blinkstatus][1] = 0;
	}
	CarHUD_SetBlinker(playerid, gracz[playerid][carhud_blinkstatus][0], gracz[playerid][carhud_blinkstatus][1]);

	new bool:fs_found;
	if(!engine) 
	{
		for(new s; s < MAX_FUELSTATIONS; s++)
		{
			if(fuel_stations[s][fs_id] == 0) continue;
			if(IsPlayerInRangeOfPoint(playerid, 20.0, fuel_stations[s][fs_dX], fuel_stations[s][fs_dY], fuel_stations[s][fs_dZ]))
			{
				if(!gracz[playerid][dystrybutor_status])
				{
					Dystrybutor_Show(playerid);
					Dystrybutor_SetPrice(playerid, gracz[playerid][dystrybutor_price]);
					Dystrybutor_SetTanked(playerid, gracz[playerid][dystrybutor_tanked]);
					Dystrybutor_SetFuelType(playerid, fuel_type);
					Dystrybutor_SetStationName(playerid, GetFuelStationName(fuel_stations[s][fs_concern]));
					if(fuel_type == F_PB) Dystrybutor_SetDMPrice(playerid, fuel_station_price[fuel_stations[s][fs_concern]][F_PB]);
					else if(fuel_type == F_ON) Dystrybutor_SetDMPrice(playerid, fuel_station_price[fuel_stations[s][fs_concern]][F_ON]);
					else if(fuel_type == F_LPG) Dystrybutor_SetDMPrice(playerid, fuel_station_price[fuel_stations[s][fs_concern]][F_LPG]);
				}
				else
				{
					if(gracz[playerid][gpk_keys] == KEY_HANDBRAKE)
					{
						new fuel_price = 5;
						if(gracz[playerid][dystrybutor_multiplier] == 0) gracz[playerid][dystrybutor_multiplier] = 1;
						new fuel_multiplier = gracz[playerid][dystrybutor_multiplier];
						if(fuel_type == F_PB) fuel_price = fuel_station_price[fuel_stations[s][fs_concern]][F_PB];
						else if(fuel_type == F_ON)  fuel_price = fuel_station_price[fuel_stations[s][fs_concern]][F_ON];
						else if(fuel_type == F_LPG)  fuel_price = fuel_station_price[fuel_stations[s][fs_concern]][F_LPG];
	
						if(pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)//firmowe fury
						{
							new cid = gracz[playerid][firma];
							if(cid == 0) return GameTextForPlayer(playerid, "~r~NIE JESTES W FIRMIE",  1000, 4);
							if(!IsPlayerOnDutyCompany(playerid)) return GameTextForPlayer(playerid, "~r~NIE JESTES NA SLUZBIE~n~W FIRMIE",  1000, 4);
							gracz[playerid][dystrybutor_companyid] = cid;
							if(company[cid][cny_money] >= (fuel_price*fuel_multiplier) && floatround(pojazd[vehicleid][v_paliwo]) < fuel_size)
							{
								gracz[playerid][dystrybutor_tanked] += fuel_multiplier;
								pojazd[vehicleid][v_paliwo] += float(fuel_multiplier);
								if(fuel_multiplier < 10) gracz[playerid][dystrybutor_multiplier]++;
								gracz[playerid][dystrybutor_price] = (gracz[playerid][dystrybutor_tanked]*fuel_price);		
								Dystrybutor_SetPrice(playerid, gracz[playerid][dystrybutor_price]);
								Dystrybutor_SetTanked(playerid, gracz[playerid][dystrybutor_tanked]);
								GameTextForPlayer(playerid, "~g~TANKOWANIE...",  1000, 4);
								PlayerPlaySound(playerid, 1153, 0, 0, 0);
								gracz[playerid][last_sound] = 1153;
								company[cid][cny_money] -= (fuel_price*fuel_multiplier);
								gracz[playerid][dystrybutor_vehicleid] = vehicleid;
								gracz[playerid][dystrybutor_fueltype] = fuel_type;
								if(pojazd[vehicleid][v_id] != 0)
								{
									mq_format("UPDATE `pojazdy` SET `paliwo`='%f' WHERE `id`='%d';", pojazd[vehicleid][v_paliwo], pojazd[vehicleid][v_id]);
									mq_send("QUpdatePaliwo");
								}
								CompanySaveMoney(cid);
							}
							else 
							{
								if(gracz[playerid][last_sound] == 1153)
								{
									gracz[playerid][last_sound] = 1154;
									PlayerPlaySound(playerid, gracz[playerid][last_sound], 0, 0, 0);
								}
								gracz[playerid][dystrybutor_multiplier] = 1;
								if(company[cid][cny_money] < fuel_price) GameTextForPlayer(playerid, "~r~TWOJEJ FIRMY NIE STAC NA WIECEJ",  1000, 4);
								else if(floatround(pojazd[vehicleid][v_paliwo]) >= fuel_size) GameTextForPlayer(playerid, "~g~PELNY ZBIORNIK",  1000, 4);
							}
						}
						else//prywatne fury
						{
							gracz[playerid][dystrybutor_companyid] = 0;
							if(Money(playerid) >= (fuel_price*fuel_multiplier) && floatround(pojazd[vehicleid][v_paliwo]) < fuel_size)
							{
								gracz[playerid][dystrybutor_tanked] += fuel_multiplier;
								pojazd[vehicleid][v_paliwo] += float(fuel_multiplier);
								if(fuel_multiplier < 10) gracz[playerid][dystrybutor_multiplier]++;
								gracz[playerid][dystrybutor_price] = (gracz[playerid][dystrybutor_tanked]*fuel_price);		
								Dystrybutor_SetPrice(playerid, gracz[playerid][dystrybutor_price]);
								Dystrybutor_SetTanked(playerid, gracz[playerid][dystrybutor_tanked]);
								GameTextForPlayer(playerid, "~g~TANKOWANIE...",  1000, 4);
								PlayerPlaySound(playerid, 1153, 0, 0, 0);
								gracz[playerid][last_sound] = 1153;
								TakeMoney(playerid, (fuel_price*fuel_multiplier));
								if(pojazd[vehicleid][v_id] != 0)
								{
									mq_format("UPDATE `pojazdy` SET `paliwo`='%f' WHERE `id`='%d';", pojazd[vehicleid][v_paliwo], pojazd[vehicleid][v_id]);
									mq_send("QUpdatePaliwo");
								}
							}
							else 
							{
								if(gracz[playerid][last_sound] == 1153)
								{
									gracz[playerid][last_sound] = 1154;
									PlayerPlaySound(playerid, gracz[playerid][last_sound], 0, 0, 0);
								}
								gracz[playerid][dystrybutor_multiplier] = 1;
								if(Money(playerid) < fuel_price) GameTextForPlayer(playerid, "~r~NIEWYSTARCZAJACA ILOSC GOTOWKI",  1000, 4);
								else if(floatround(pojazd[vehicleid][v_paliwo]) >= fuel_size) GameTextForPlayer(playerid, "~g~PELNY ZBIORNIK",  1000, 4);
							}
						}
					} 
					else
					{
						if(gracz[playerid][last_sound] == 1153)
						{
							gracz[playerid][last_sound] = 1154;
							PlayerPlaySound(playerid, gracz[playerid][last_sound], 0, 0, 0);
						}
						gracz[playerid][dystrybutor_multiplier] = 1;
						GameTextForPlayer(playerid, "~y~Przytrzymaj~w~ klawisz ~b~SPACJI~w~ aby tankowac.",  1000, 4);
					}
				}
				fs_found = true;
				break;
			}
		}
	}
	if(!fs_found) Dystrybutor_Hide(playerid);
	return 1;
}

task Process_Vehicle()
{
	new Float:tX, Float:tY, Float:tZ, Float:tR;
	new engine, lights, alarm, doors, bonnet, boot, objective;
	new Float:velX, Float:velZ, Float:velY;
	new vamodel;
	static dtrash, dtires;
	//new Float:MetersLastPos;
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		vamodel = GetVehicleModel(v);
		if(vamodel > 0)
		{
			if(pojazd[v][v_model] == 0)//pojazd istnieje a nie jest wczytany przez skrypt - usuwanie
			{
				if(vamodel != 538 && vamodel != 570 && vamodel != 457)//żeby pociągów nie usuwało i golf
				{
					DestroyVehicle(v);
					printf("[DestroyVehicle] Usuwam pojazd UID: %d MODELID: %d VEHICLEID: %d - Nie znaleziono w RAM.", pojazd[v][v_id], vamodel, v);
				}
			}
			if(pojazd[v][v_model] == 0) continue;
			if(eventp_OnVehicleUpdate(v)) 
			{
				if(pojazd[v][v_handbrake])
				{
					if(!IsVehicleTrailer(pojazd[v][v_model]))
					{
						if(GetDistanceBetweenPoints(pojazd[v][v_handbrake_posX], pojazd[v][v_handbrake_posY], pojazd[v][v_handbrake_posZ], tX, tY, tZ) > 5.0)
						{
							SetVehiclePos(v, pojazd[v][v_handbrake_posX], pojazd[v][v_handbrake_posY], pojazd[v][v_handbrake_posZ]);
						}
						if(!((pojazd[v][v_handbrake_posR]-2.0) < tR < (pojazd[v][v_handbrake_posR]+2.0))) SetVehicleZAngle(v, pojazd[v][v_handbrake_posR]);
					}
				}
				continue;//pojazdy eventowe - wycinanie
			}
			GetVehiclePos(v, tX, tY, tZ);
			GetVehicleZAngle(v, tR);
			GetVehicleHealth(v, pojazd[v][v_HP]);
			GetVehicleVelocity(v, velX, velY, velZ);
			if(pojazd[v][v_HP] < 644.0 && !SpecialVehicle(v)) 
			{
				if(pojazd[v][v_HP] < 255.0)
				{
					SetVehiclePos(v, tX, tY, tZ);
					SetVehicleZAngle(v, tR);
					SetVehicleVelocity(v, velX, velY, velZ);
				}
				SetVehicleHealth(v, 645.0);
				if(!IsVehicleWornOut(v, 15))//jeśli chłodnica nie jest uszkodzona
				{
					pojazd[v][v_damages_lifetime_km][15] = VehicleDamages[15][vd_exp_km]+5;//uszkadzanie chłodnicy
					//zapiszmy tą informacje do logów pojazdów firmy
					if(pojazd[v][v_owner_type] == VEHICLE_BUSINESS)
					{
						new pid = IsVehicleInUseByDriver(v);
						LogCompany(gracz[pid][firma], gracz[pid][UID], gracz[pid][firma_sessionid], CLOGFLAG_POJAZD, "Uszkodzenie: chlodnica. Pojazd: %s(UID: %d)", GetVehicleName(pojazd[v][v_model]), pojazd[v][v_id]);
					}
				}
			}
			if(pojazd[v][v_owner_type] == VEHICLE_PLAYER || pojazd[v][v_owner_type] == VEHICLE_BUSINESS)
			{
				if(pojazd[v][v_karoseria_hits] < MAX_VEHICLEBODY_RESIST) 
				{
					GetVehicleDamageStatus(v, dtrash, dtrash, dtrash, dtires);
					UpdateVehicleDamageStatus(v, 0, 0, 0, dtires);
				}
			}
			/*else if(pojazd[v][v_owner_type] == VEHICLE_FRACTION)//niezniszczalne pojazdy frakcyjne
			{
				if(!SpecialVehicle(v))
				{
					if(pojazd[v][v_HP] < 999.0)
					{
						RepairVehicle(v);
						SetVehicleHealth(v, 1000.0);
					}
				}
			}*/
	
			if(IsVehicleTrailer(pojazd[v][v_model]))
			{
				if(pojazd[v][v_trailerupdate] < serwer[time_timestamp] && pojazd[v][v_trailerupdate] != 0)
				{
					pojazd[v][v_trailerupdate] = 0;
					DetachTrailerFromVehicle(v);
					SetVehicleToRespawn(v);//niech nie losuje od nowa
					ResetVehicleADRData(v);
					for(new p = PlayerPoolSize(); p != -1; p--)
					{
						if(gracz[p][cargo_trailerdid] == v)
						{
							gracz[p][cargo_trailerdid] = 0;
							ClearObjective(p);
							ClearTrailerSelect(p);
							Info(p, "Twoje zlecenie zostało anulowane - zbyt długo Twoja naczepa pozostawała bez opieki.");
							break;
						}
					}
					pojazd[v][v_trailerupdate] = 0;
					UpdateDynamic3DTextLabelText(pojazd[v][v_text3d], 0x009933FF, pojazd[v][v_text3d_strcache]);
				}
			}
			//wyłączanie gaszenia w helikopterze ratownictwa 
			if(IsHelicopterUseWater(v))
			{
				if(IsVehicleInUseByDriver(v) == INVALID_PLAYER_ID)
				{
					ToggleHelicopterWater(v, 0);
				}
			}
			//end
			if(!SpecialVehicle(v))
			{
				Process_SirenEffects(v);
				if(pojazd[v][v_handbrake])
				{
					if(!IsVehicleTrailer(pojazd[v][v_model]))
					{
						if(GetDistanceBetweenPoints(pojazd[v][v_handbrake_posX], pojazd[v][v_handbrake_posY], pojazd[v][v_handbrake_posZ], tX, tY, tZ) > 5.0)
						{
							SetVehiclePos(v, pojazd[v][v_handbrake_posX], pojazd[v][v_handbrake_posY], pojazd[v][v_handbrake_posZ]);
						}
						if(!((pojazd[v][v_handbrake_posR]-2.0) < tR < (pojazd[v][v_handbrake_posR]+2.0))) SetVehicleZAngle(v, pojazd[v][v_handbrake_posR]);
					}
				}
				else
				{
					if(IsVehicleStreamedInAnyone(v))
					{
						if(pojazd[v][v_owner_type] == VEHICLE_PLAYER || pojazd[v][v_owner_type] == VEHICLE_BUSINESS)
						{
							//mq_format("UPDATE `pojazdy` SET `hp`='%f' WHERE `id`='%d';", pojazd[v][v_HP], pojazd[v][v_id]);
							if(pojazd[v][v_id] != 0)
							{
								mq_format("UPDATE `pojazdy` SET `temp_x`='%f', `temp_y`='%f', `temp_z`='%f', `temp_r`='%f', `hp`='%f', `rlg_lastused`='%d' WHERE `id`='%d';", tX, tY, tZ, tR, pojazd[v][v_HP], serwer[time_timestamp], pojazd[v][v_id]);
								mq_send("QUpdateVehicle");
							}
						}
						else
						{
							if(pojazd[v][v_id] != 0)
							{
								mq_format("UPDATE `pojazdy` SET `temp_x`='%f', `temp_y`='%f', `temp_z`='%f', `temp_r`='%f', `rlg_lastused`='%d' WHERE `id`='%d';", tX, tY, tZ, tR, serwer[time_timestamp], pojazd[v][v_id]);
								mq_send("QUpdateVehicle");
							}
						}
					}
				}
				
				GetVehicleParamsEx(v, engine, lights, alarm, doors, bonnet, boot, objective);
	
				if(engine)
				{
	
					if(IsVehicleWornOut(v, 15) || IsVehicleWornOut(v, 16))//przegrzewanie
					{
						if(pojazd[v][v_enginetemp] < 65.0) pojazd[v][v_enginetemp] = 65.0;
						else if(pojazd[v][v_enginetemp] < 109 && pojazd[v][v_speed] == 0) pojazd[v][v_enginetemp] += 0.9;
						else if(pojazd[v][v_enginetemp] < 108 && pojazd[v][v_speed] < 100) pojazd[v][v_enginetemp] += 0.8;
						else if(pojazd[v][v_enginetemp] < 107 && pojazd[v][v_speed] > 100) pojazd[v][v_enginetemp] += 0.5;
						else if(pojazd[v][v_enginetemp] > 107 && pojazd[v][v_speed] < 100) pojazd[v][v_enginetemp] -= 0.1;
						else if(pojazd[v][v_enginetemp] > 107 && pojazd[v][v_speed] > 100) pojazd[v][v_enginetemp] -= 0.1;
					}
					else//normalna praca
					{
						if(pojazd[v][v_enginetemp] < 65.0) pojazd[v][v_enginetemp] = 65.0;
						else if(pojazd[v][v_enginetemp] < 101 && pojazd[v][v_speed] == 0) pojazd[v][v_enginetemp] += 0.8;
						else if(pojazd[v][v_enginetemp] < 95 && pojazd[v][v_speed] < 100) pojazd[v][v_enginetemp] += 0.6;
						else if(pojazd[v][v_enginetemp] < 92 && pojazd[v][v_speed] > 100) pojazd[v][v_enginetemp] += 0.3;
						else if(pojazd[v][v_enginetemp] > 92 && pojazd[v][v_speed] < 100) pojazd[v][v_enginetemp] -= 0.3;
						else if(pojazd[v][v_enginetemp] > 92 && pojazd[v][v_speed] > 100) pojazd[v][v_enginetemp] -= 0.4;
					}
					if(pojazd[v][v_paliwo] <= 0.0) SetVehicleParamsEx(v, 0, lights, alarm, doors, bonnet, boot, objective);//gaszenie pojazdu gdy brak paliwa



					if(pojazd[v][v_enginetemp] > 106)
					{
						pojazd[v][v_enginetemp] = 107;
						new bool:ravages = false;
						if(FractionDutyWorkersCount(F_ROADASSIST) > 0) ravages = true;
						else if(random(32) == 16 && random(8) == 4) ravages = true;
						if(ravages)
						{
							SetVehicleParamsEx(v, 0, lights, alarm, doors, bonnet, boot, objective);
							SetVehicleHealth(v, 645.0);
							pojazd[v][v_HP] = 645.0;
							LeftNotifyShow(IsVehicleInUseByDriver(v), "Awaria", "Silnik pojazdu ~r~zgasl~w~. Pojazd prawdopodobnie ulegl awarii. Odwiedz warsztat.", LN_RED);
							if(pojazd[v][v_id] != 0)
							{
								mq_format("UPDATE `pojazdy` SET `hp`='645.0' WHERE `id`='%d';", pojazd[v][v_id]);
								mq_send("QUpdateVehicle");
							}
						}
					}
				}
				else//zgaszony silnik
				{
					if(pojazd[v][v_enginetemp] > 65.0) pojazd[v][v_enginetemp] -= 0.1;
				}
			}
		}
	}
	/*mq_format("UPDATE `pojazdy` SET `rlg_lastused`='%d';", serwer[time_timestamp]);
	mq_send("QUpdateRlgLastUsed");*/
	return 1;
}


task Process_VehicleDistanceFuel()//naliczanie przebiegu i odejmowanie paliwa
{
	static engine, lights, alarm, doors, bonnet, boot, objective;
	new Float:tX, Float:tY, Float:tZ;
	new Float:MetersLastPos;
	new playerid;
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		if(pojazd[v][v_model] == 0) continue;
		if(pojazd[v][v_event_used] == true) continue;//pojazdy eventowe pomijaj
		playerid = IsVehicleInUseByDriver(v);
		if(playerid == INVALID_PLAYER_ID) continue;
		if(!SpecialVehicle(v))
		{
			GetVehicleParamsEx(v, engine, lights, alarm, doors, bonnet, boot, objective);
			GetVehiclePos(v, tX, tY, tZ);
			if(pojazd[v][v_LPosX] == 0.0)//ustawianie początkowych koordynatów
			{
				pojazd[v][v_LPosX] = tX;
				pojazd[v][v_LPosY] = tY;
				pojazd[v][v_LPosZ] = tZ;
			}
			MetersLastPos = GetDistanceBetweenPoints(pojazd[v][v_LPosX], pojazd[v][v_LPosY], pojazd[v][v_LPosZ], tX, tY, tZ);
			pojazd[v][v_LPosX] = tX;
			pojazd[v][v_LPosY] = tY;
			pojazd[v][v_LPosZ] = tZ;
			if(engine)
			{
				//licznik przebiegu
				if(pojazd[v][v_przebiegunits] < CONST_KM)
				{
					pojazd[v][v_przebiegunits] += MetersLastPos;
				}
				else
				{
					while(pojazd[v][v_przebiegunits] >= CONST_KM)
					{
						pojazd[v][v_przebiegunits] -= CONST_KM;
						pojazd[v][v_przebieg]++;
						//new playerid = IsVehicleInUseByDriver(v);
						if(playerid != INVALID_PLAYER_ID) gracz[playerid][przebieg]++;
						if(pojazd[v][v_owner_type] == VEHICLE_FRACTION && pojazd[v][v_owner] == F_TAXI)//pojazdy taxi
						{
							if(pojazd[v][v_taxometr_statuson])
							{
								pojazd[v][v_taxometr_distance]++;
								pojazd[v][v_taxometr_price] = pojazd[v][v_taxometr_price_per_km]*pojazd[v][v_taxometr_distance];
							}
						}
						if(pojazd[v][v_paliwo] > 0.0 && (pojazd[v][v_owner_type] == VEHICLE_PLAYER || pojazd[v][v_owner_type] == VEHICLE_BUSINESS))
						{
							if(IsVehicleWornOut(v, 5) || IsVehicleWornOut(v, 3) || IsVehicleWornOut(v, 17) || IsVehicleWornOut(v, 18))//awaria
							{
								pojazd[v][v_paliwo] -= pojazd_spec[GetVehicleSpecID(pojazd[v][v_model])][vspec_fuelconsumption]/40.0;//wieksze zużycie paliwa
							}
							else
							{
								pojazd[v][v_paliwo] -= pojazd_spec[GetVehicleSpecID(pojazd[v][v_model])][vspec_fuelconsumption]/100.0;//normalne zużycie paliwa
							}
							
							if(pojazd[v][v_paliwo] < 0.0) pojazd[v][v_paliwo] = 0.0;
						}
						//zużycie komponentów, tylko dla pojazdów gracza i firmowych
						if(pojazd[v][v_owner_type] == VEHICLE_PLAYER || pojazd[v][v_owner_type] == VEHICLE_BUSINESS)
						{
							format(pojazd[v][v_damages_lifetime_strdata], 256, "");//czyszczenie zmiennej
							for(new x; x < MAX_VEHICLEDAMAGES; x++)
							{
								pojazd[v][v_damages_lifetime_km][x]++;
								if(IsVehicleBike(pojazd[v][v_model]) && (x == 1 || x == 2)) pojazd[v][v_damages_lifetime_km][x] = 0;
								format(pojazd[v][v_damages_lifetime_strdata], 256, "%s%d ", pojazd[v][v_damages_lifetime_strdata], pojazd[v][v_damages_lifetime_km][x]);
							}
							//DEBUG uszkodzeń pojazdu:
							/*print("**********************************************");
							printf("strVehicleDamage_data: %s", pojazd[v][v_damages_lifetime_strdata]);
							for(new x; x < MAX_VEHICLEDAMAGES; x++)
							{
								printf("%s: %d/%d %s", VehicleDamages[x][vd_title], pojazd[v][v_damages_lifetime_km][x], VehicleDamages[x][vd_exp_km], (IsVehicleWornOut(v, x)) ? ("[ZUŻYTE]") : ("[SPRAWNE]"));
							}
							print("**********************************************");*/
						}
					}
					Process_VehicleDamage(-1, v, 1);
					if(pojazd[v][v_id] != 0)
					{
						mq_format("UPDATE `pojazdy` SET `przebieg`='%d', `przebiegunits`='%d', `paliwo`='%f', `eksploatacja`='%s' WHERE `id`='%d';", pojazd[v][v_przebieg], floatround(pojazd[v][v_przebiegunits]), pojazd[v][v_paliwo], pojazd[v][v_damages_lifetime_strdata], pojazd[v][v_id]);
						mq_send("QUpdateVehicle");
					}
				}
			}
		}
	}
	return 1;
}

stock SetCarBlinking(veh, side, bool:skip=false) //0 - left 1 - right 2 - emergy
{
	if(IsCarBlinking(veh) && !skip) return DisableCarBlinking(veh);
	new model=GetVehicleModel(veh),obj[4];
	new id = model-400, trailer;

	if(!skip) BlinkSide[veh] = side;

	GetVehicleZAngle(veh, BlinkR[veh]);

	if(id > -1)
	{
		if(BlinkOffset[id][bX] != 0.0)
		{
			if(side == 0)//lewy
			{
				obj[0] = CreateDynamicObject(19294, 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0); //blink yellow  front
				Blink[veh][0] = obj[0];
			}
			else//prawy
			{
				obj[2] = CreateDynamicObject(19294, 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
				Blink[veh][2] = obj[2];
			}
		}

		if((trailer = GetVehicleTrailer(veh)) != 0)
		{
			if(BlinkSystem_IsTrailer(trailer))
			{
				if(side == 0)
				{
					obj[1] = CreateDynamicObject(19294, 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0); //blink yellow back truck only trailer
					Blink[veh][1] = obj[1];
				}
				else
				{
					obj[3] = CreateDynamicObject(19294, 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
					Blink[veh][3] = obj[3];
				}
			}
		}
		else
		{
			if(BlinkOffset[id][brX] != 0.0)
			{
				if(side == 0)
				{
					obj[1] = CreateDynamicObject(19294, 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0); //blink yellow back truck only trailer
					Blink[veh][1] = obj[1];
				}
				else
				{
					obj[3] = CreateDynamicObject(19294, 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
					Blink[veh][3] = obj[3];
				}
			}
		}

		if(side == 0) //left
		{
			if(obj[0] != 0) AttachDynamicObjectToVehicle(obj[0], veh, BlinkOffset[id][bX],BlinkOffset[id][bY],BlinkOffset[id][bZ], 0.0, 0.0, 0.0);
			if(trailer != 0)
			{
				id = GetVehicleModel(trailer)-400;
				AttachDynamicObjectToVehicle(obj[1], trailer, BlinkOffset[id][brX],BlinkOffset[id][brY],BlinkOffset[id][brZ], 0.0, 0.0, 0.0);
			}
			else
			{
				if(obj[1] != 0) AttachDynamicObjectToVehicle(obj[1], veh, BlinkOffset[id][brX],BlinkOffset[id][brY],BlinkOffset[id][brZ], 0.0, 0.0, 0.0);
			}
		}
		else if(side == 1) //right
		{
			if(obj[2] != 0) AttachDynamicObjectToVehicle(obj[2], veh, -BlinkOffset[id][bX],BlinkOffset[id][bY],BlinkOffset[id][bZ], 0.0, 0.0, 0.0);
			if(trailer != 0)
			{
				id = GetVehicleModel(trailer)-400;
				AttachDynamicObjectToVehicle(obj[3], trailer, -BlinkOffset[id][brX],BlinkOffset[id][brY],BlinkOffset[id][brZ], 0.0, 0.0, 0.0);
			}
			else
			{
				if(obj[3] != 0) AttachDynamicObjectToVehicle(obj[3], veh, -BlinkOffset[id][brX],BlinkOffset[id][brY],BlinkOffset[id][brZ], 0.0, 0.0, 0.0);
			}
		}
		else if(side == 2)  //emergency
		{
			//SetCarBlinking(veh, 0, true);
			SetTimerEx("SetCarBlinkingT", 5, false, "ddd", veh, 0, 1);
			//SetCarBlinking(veh, 1, true);
			SetTimerEx("SetCarBlinkingT", 5, false, "ddd", veh, 1, 1);
		}
	}
	return 1;
}

task SetCarBlinkingT(veh, side, bool:skip)
{
	SetCarBlinking(veh, side, skip);
	return 1;
}

public BlinkSystem_DisableBlinks(vehicleid)
{
	for(new i=0; i<4;i++)
	{
		if(Blink[vehicleid][i] != -1) DestroyDynamicObject(Blink[vehicleid][i]);
		Blink[vehicleid][i] = -1;
	}
	return 1;
}

stock DisableCarBlinking(veh)
{
	if(!IsCarBlinking(veh)) return 1;
	BlinkSystem_DisableBlinks(veh);
	return 1;
}

stock IsCarBlinking(vehicleid)
{
	if((BlinkSide[vehicleid] == 0 && Blink[vehicleid][0] == -1 && Blink[vehicleid][1] == -1) || (BlinkSide[vehicleid] == 1 && Blink[vehicleid][2] == -1 && Blink[vehicleid][3] == -1)) return 0;
	else if(Blink[vehicleid][0] == -1 && Blink[vehicleid][1] == -1 && Blink[vehicleid][2] == -1 && Blink[vehicleid][3] == -1) return 0;
	return 1;
}

stock BlinkSystem_IsTrailer(vehicleid)
{
	switch(GetVehicleModel(vehicleid))
	{
		case 435, 450, 584, 591, 606: return 1;
	}
	return 0;
}

public BlinkSystem_OnTrailerDetached(trailerid, fromvehicleid)
{
	if(IsCarBlinking(fromvehicleid))
	{
		DisableCarBlinking(fromvehicleid);
		SetCarBlinking(fromvehicleid, BlinkSide[fromvehicleid]);
	}
	TrailerVehicle[trailerid] = 0;
}

public BlinkSystem_OnTrailerAttached(trailerid, tovehicleid)
{
	if(IsCarBlinking(tovehicleid))
	{
		DisableCarBlinking(tovehicleid);
		SetCarBlinking(tovehicleid, BlinkSide[tovehicleid]);
	}
	TrailerVehicle[trailerid] = tovehicleid;
}

public BlinkSystem_TrailerCheck()
{
	new trailer;
	for(new i = GetVehiclePoolSize(); i != -1; i--)
	{
		if((trailer = GetVehicleTrailer(i)) != 0)
		{
			if(BlinkTrailer[i] == 0)
			{
				BlinkTrailer[i]=trailer;
				BlinkSystem_OnTrailerAttached(trailer, i);
			}
		}
		else if(BlinkTrailer[i] != 0)
		{
			BlinkSystem_OnTrailerDetached(BlinkTrailer[i], i);
			BlinkTrailer[i] = 0;
		}
	}
}




CMD:v(playerid, params[])
{
	new opcja[32];
	if(sscanf(params,"s[32]", opcja)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /v [lista/zamek/parkuj/odczep]");
	if(compare(opcja, "lista") || compare(opcja, "list") || compare(opcja, "l"))
	{
		if(IsPlayerInAnyVehicle(playerid)) return Error(playerid, "Nie możesz używać "COL_RED"/v lista"COL_WHITE" będąc w pojeździe.");
		mq_format("SELECT * FROM `pojazdy` WHERE `owner_type`='%d' AND `owner`='%d' ORDER BY `status`='1' DESC LIMIT %d;", VEHICLE_PLAYER, gracz[playerid][UID], MAX_PRIVCARS_CONST);
		mq_send("QListPlayerVehicle", "d", playerid);
	}
	else if(compare(opcja, "zamek") || compare(opcja, "z"))
	{
		new Float:vPos[3];
		new vehicleid = -1;
		new engine, lights, alarm, doors, bonnet, boot, objective;
		new Float:v_range = 0.3;
		const Float:max_range = 10.0;
		while(v_range < max_range)
		{
			for(new v = GetVehiclePoolSize(); v != -1; v--)
			{
				if(!IsVehicleTrailer(GetVehicleModel(v)))
				{
					if(pojazd[v][v_owner_type] == VEHICLE_PUBLIC && pojazd[v][v_owner] == VO_DRVLICENSE) continue;//L-ki
					if(IsPlayerCanDrive(playerid, v))
					{
						if(pojazd[v][v_owner_type] == VEHICLE_PUBLIC && GetPlayerState(IsVehicleInUse(v)) == PLAYER_STATE_DRIVER) continue;
						GetVehiclePos(v, vPos[0], vPos[1], vPos[2]);
						if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsPlayerInVehicle(playerid, v))
						{
							vehicleid = v;
							PlayerPlaySound(playerid, 24600, 0, 0, 0);//w środku
							break;
						}
						else
						{
							
							if(IsPlayerInRangeOfPoint(playerid, v_range, vPos[0], vPos[1], vPos[2]))
							{
								if(v_range < 2.0)
								{
									vehicleid = v;
									ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);//KLUCZYKI
									PlayerPlaySound(playerid, 24600, 0, 0, 0);
									break;
								}
								else if(v_range < max_range)
								{
									vehicleid = v;
									ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 4.1, 0, 0, 0, 0, 0, 1);//PILOT
									CarPilotLockUnlockEffect(vehicleid);
									break;
								}
							}
						}
					}
				}
			}
			if(vehicleid != -1) break;
			v_range += 0.3;
		}

		if(vehicleid == -1) Error(playerid, "Nie znajdujesz się w pobliżu pojazdu, którym możesz zarządzać.");
		else
		{
			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			if(doors)
			{
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, 0, bonnet, boot, objective);
				LeftNotifyShow(playerid, "Sukces!", "Drzwi ~g~otwarte~w~.", LN_GREEN);
			}
			else
			{
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, 1, bonnet, boot, objective);
				LeftNotifyShow(playerid, "Sukces!", "Drzwi ~r~zamkniete~w~.", LN_RED);
			}
		}
	}
	else if(compare(opcja, "parkuj") || compare(opcja, "zaparkuj") || compare(opcja, "park") || compare(opcja, "p"))
	{
		new veh = GetPlayerVehicleID(playerid);
		if(GetPlayerVehicleSeat(playerid) == 0 && IsPlayerCanDrive(playerid, veh)) 
		{
			new trailerid = GetVehicleTrailer(veh);
			if(trailerid == 0)
			{
				ParkVehicle(playerid, veh);
			}
			else//ma naczepe
			{
				new cid = gracz[playerid][firma];
				if(cid != 0 && gracz[playerid][firma_permlvl] != 0)//może rządzić firmą i JEST W FIRMIE
				{
					new strList[512];
					format(strList, 512, ""COL_RED"»"COL_GREEN" Zaparkuj ciągnik:"COL_WHITE" %s\n"COL_RED"»"COL_BLUE" Zaparkuj naczepę:"COL_WHITE" %s", GetVehicleName(pojazd[veh][v_model]), GetVehicleName(pojazd[trailerid][v_model]));
					Dialog_Show(playerid, ASKTRAILERPARK, DIALOG_STYLE_LIST, ""COL_RED"•» "COL_WHITE"Co chcesz zaparkować?"COL_RED"«•", strList, "Wybierz", "Anuluj");
				}
				else ParkVehicle(playerid, veh);//gracze bez firmy nie mogą przeparkować
			}
		}
		else Error(playerid, "Musisz być w pojeździe.");
	}
	else if(compare(opcja, "odczep"))
	{
		new veh = GetPlayerVehicleID(playerid);
		if(GetPlayerVehicleSeat(playerid) == 0 && IsPlayerCanDrive(playerid, veh)) 
		{
			new trailerid = GetVehicleTrailer(veh);
			if(trailerid == 0) return Error(playerid, "Brak naczepy.");
			DetachTrailerFromVehicle(veh);
			new Float:vx, Float:vy, Float:vz;
			GetVehiclePos(veh, vx, vy, vz);
			GetXYInFrontOfVehicle(veh, vx, vy, 1.0);
			SetVehiclePos(veh, vx, vy, vz);
			GameTextForPlayer(playerid, "~g~NACZEPA ODCZEPIONA!", 2000, 3);
		}
		else Error(playerid, "Musisz być w pojeździe.");
	}
	else Error(playerid, "Błędna opcja.");
	return 1;
}

Dialog:ASKTRAILERPARK(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new veh = GetPlayerVehicleID(playerid);
	switch(listitem)
	{
		case 0:
		{
			ParkVehicle(playerid, veh);
		}
		case 1:
		{
			new trailerid = GetVehicleTrailer(veh);
			if(trailerid == 0) return Error(playerid, "Brak naczepy.");
			if(pojazd[trailerid][v_owner_type] != VEHICLE_BUSINESS) return Error(playerid, "Tylko naczepy firmowe można przeparkować.");
			SetPVarInt(playerid, "TrailerParkOK", 0);
			ParkVehicle(playerid, trailerid);
			if(GetPVarInt(playerid, "TrailerParkOK") == 1)
			{
				DetachTrailerFromVehicle(veh);
				//SetVehicleToRespawn(vehicleid);
				
				new Float:vx, Float:vy, Float:vz;
				GetVehiclePos(veh, vx, vy, vz);
				GetXYInFrontOfVehicle(veh, vx, vy, 2.0);
				SetVehiclePos(veh, vx, vy, vz);
			}
			DeletePVar(playerid, "TrailerParkOK");
		}
	}
	return 1;
}

forward QListPlayerVehicle(playerid);//v lista
public QListPlayerVehicle(playerid)
{
	mq_getdata();
	if(rekordy)
	{
		new strList[3072];
		new strTitle[256];
		new carlist_cache[MAX_PRIVCARS_CONST][4];
		new i;
		format(strList, 3072, "UID\tPojazd\tStatus");
		while(i < rekordy)
		{
			//last string\nid, nazwa, status
			/*cache_get_value_name_int(i, "id", 			gui_cache[playerid][i][0]);
			cache_get_value_name_int(i, "model", 			gui_cache[playerid][i][1]);
			cache_get_value_name_int(i, "status", 			gui_cache[playerid][i][2]);*/
			cache_get_value_name_int(i, "id", 			carlist_cache[i][0]);
			cache_get_value_name_int(i, "model", 			carlist_cache[i][1]);
			cache_get_value_name_int(i, "status", 			carlist_cache[i][2]);
			//format(strList, 3072, "%s\n{000000}%d\t%s\t%s", strList, gui_cache[playerid][i][0], GetVehicleName(gui_cache[playerid][i][1]), VehicleStatus(gui_cache[playerid][i][2]));
			i++;
		}
		i = 0;
		///sortowanie
		for(new s; s < MAX_PRIVCARS_CONST; s++) 
		{
			if(carlist_cache[s][0] == 0) continue;
			if(IsVehicleTruck(carlist_cache[s][1])) 
			{
				gui_cache[playerid][i][0] = carlist_cache[s][0];
				gui_cache[playerid][i][1] = carlist_cache[s][1];
				gui_cache[playerid][i][2] = carlist_cache[s][2];
				format(strList, 3072, "%s\n{000000}%d\t[TRUCK] %s\t%s", strList, gui_cache[playerid][i][0], GetVehicleName(gui_cache[playerid][i][1]), VehicleStatus(gui_cache[playerid][i][2]));
				i++;
			}
		}
		for(new s; s < MAX_PRIVCARS_CONST; s++) 
		{
			if(carlist_cache[s][0] == 0) continue;
			if(!IsVehicleTruck(carlist_cache[s][1])) 
			{
				gui_cache[playerid][i][0] = carlist_cache[s][0];
				gui_cache[playerid][i][1] = carlist_cache[s][1];
				gui_cache[playerid][i][2] = carlist_cache[s][2];
				format(strList, 3072, "%s\n{000000}%d\t%s\t%s", strList, gui_cache[playerid][i][0], GetVehicleName(gui_cache[playerid][i][1]), VehicleStatus(gui_cache[playerid][i][2]));
				i++;
			}
		}
		format(strTitle, 256, ""COL_RED"•» "COL_WHITE"Lista Twoich pojazdów "COL_BLUE"["COL_GREEN"%d"COL_WHITE"/"COL_RED"%d"COL_BLUE"] (%d) "COL_RED"«•", rekordy, MaxVehiclesPlayer(playerid), PlayerCreatedCarsCount(playerid));
		Dialog_Show(playerid, PCARLIST, DIALOG_STYLE_TABLIST_HEADERS, strTitle, strList, "Wybierz", "Anuluj");
	}
	else Error(playerid, "Nie posiadasz żadnego pojazdu.");
	return 1;
}

Dialog:PCARLIST(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new strTitle[128], strList[512];
	gracz[playerid][gui_listitem] = listitem;
	format(strList, 512, ""COL_LIME"•»\t"COL_GREEN"Stwórz"COL_WHITE"/"COL_RED"Usuń\t"COL_LIME"«•");
	format(strList, 512, "%s\n"COL_LIME"•»\t"COL_GREEN"Otwórz"COL_WHITE"/"COL_RED"Zamknij "COL_WHITE"pojazd\t"COL_LIME"«•", strList);
	format(strList, 512, "%s\n"COL_LIME"•»\t"COL_EASY"Namierz\t"COL_LIME"«•", strList);
	format(strList, 512, "%s\n"COL_LIME"•»\t"COL_EASY"Sprzedaj\t"COL_LIME"«•", strList);
	if(gui_cache[playerid][listitem][2] == 3) format(strList, 512, "%s\n"COL_LIME"•»\t"COL_BLUE"Odbierz na parkingu policyjnym\t"COL_LIME"«•", strList);
	else if(gui_cache[playerid][listitem][2] != 2) format(strList, 512, "%s\n"COL_LIME"•»\t"COL_RED"Złomuj\t"COL_LIME"«•", strList);
	else format(strList, 512, "%s\n"COL_LIME"•»\t"COL_RED"Odbierz na Auto Szrocie\t"COL_LIME"«•", strList);
	format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Zarządzanie pojazdem "COL_ORANGE"%s(%d) "COL_RED"«•", GetVehicleName(gui_cache[playerid][listitem][1]), gui_cache[playerid][listitem][0]);
	Dialog_Show(playerid, PCARMENU, DIALOG_STYLE_TABLIST, strTitle, strList, "Wybierz", "Anuluj");
	return 1;
}

Dialog:PCARMENU(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new selected = gracz[playerid][gui_listitem];
	new vehicleid = VehicleUidToVehicleid(gui_cache[playerid][selected][0]);
	SetPVarInt(playerid, "cache_pcm_vehicledbid", gui_cache[playerid][selected][0]);
	switch(listitem)
	{
		case 0:
		{
			if(gui_cache[playerid][selected][2] == 2) return Error(playerid, "Ten pojazd jest zezłomowany. Możesz go odebrać na Auto Szrocie.");
			if(gui_cache[playerid][selected][2] == 3) return Error(playerid, "Ten pojazd został odholowany. Możesz go odebrać na parkingu policyjny.");
			if(vehicleid != -1)
			{
				mq_format("UPDATE `pojazdy` SET `status`='0', `rlg_lastused`='0' WHERE `id`='%d';", gui_cache[playerid][selected][0]);
				mq_send("QUpdateVehicleStatus");
				RemoveVehicle(vehicleid);
				LeftNotifyShow(playerid, "Sukces!", "Pojazd ~r~usuniety~w~.", LN_RED);
			}
			else if(PlayerCreatedCarsCount(playerid) < MAX_PRIVCARSCREATED)
			{
				mq_format("UPDATE `pojazdy` SET `status`='1' WHERE `id`='%d';", gui_cache[playerid][selected][0]);
				mq_send("QUpdateVehicleStatus");
				mq_format("SELECT * FROM `pojazdy` WHERE `id`='%d';", gui_cache[playerid][selected][0]);
				mq_send("LoadVehFromDB");
				LeftNotifyShow(playerid, "Sukces!", "Pojazd ~g~stworzony~w~.", LN_GREEN);
			}
			else Error(playerid, "Nie możesz mieć więcej pojazdów stworzonych w tym samym czasie.");
		}
		case 1:
		{
			if(vehicleid != -1)
			{
				new Float:vPos[3];
				GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
				if(IsPlayerInRangeOfPoint(playerid, 50.0, vPos[0], vPos[1], vPos[2]))
				{
					new engine, lights, alarm, doors, bonnet, boot, objective;
					GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
					if(doors)
					{
						SetVehicleParamsEx(vehicleid, engine, lights, alarm, 0, bonnet, boot, objective);
						LeftNotifyShow(playerid, "Sukces!", "Drzwi ~g~otwarte~w~.", LN_GREEN);
					}
					else
					{
						SetVehicleParamsEx(vehicleid, engine, lights, alarm, 1, bonnet, boot, objective);
						LeftNotifyShow(playerid, "Sukces!", "Drzwi ~r~zamkniete~w~.", LN_RED);
					}	
					ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 4.1, 0, 0, 0, 0, 0, 1);//PILOT
					CarPilotLockUnlockEffect(vehicleid);
				} 
				else Error(playerid, "Jesteś za daleko.");
			}
			else Error(playerid, "Ten pojazd nie jest stworzony.");
		}
		case 2:
		{
			if(vehicleid != -1)
			{
				new Float:pos[3];
				GetVehiclePos(vehicleid, pos[0], pos[1], pos[2]);
				SetPlayerCheckpoint(playerid, pos[0], pos[1], pos[2]-0.4, 5.0);
				Info(playerid, "Pojazd został zaznaczony "COL_RED"czerwonym"COL_WHITE" punktem na mapie.");
				LeftNotifyShow(playerid, "Sukces!", "Pojazd zostal zaznaczony ~r~czerwonym~w~ punktem na mapie.", LN_GREEN);
			}
			else Error(playerid, "Ten pojazd nie jest stworzony.");
		}
		case 3:
		{
			if(vehicleid != -1)
			{
				new Float:vPos[3];
				GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
				if(IsPlayerInRangeOfPoint(playerid, 8.0, vPos[0], vPos[1], vPos[2]))
				{
					new strTitle[128];
					format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Sprzedaż pojazdu "COL_ORANGE"%s(%d) "COL_RED"«•", GetVehicleName(gui_cache[playerid][selected][1]), gui_cache[playerid][selected][0]);
					Dialog_Show(playerid, CARSELLTYPE, DIALOG_STYLE_TABLIST, strTitle, ""COL_LIME"•»\t{00FF00}Sprzedaj innemu graczowi\t"COL_LIME"«•\n"COL_LIME"•»\t{FF0000}Sprzedaj na złom "COL_GREY"[30% wartości pojazdu]\t"COL_LIME"«•", "Wybierz", "Anuluj");
				} 
				else Error(playerid, "Jesteś za daleko od pojazdu.");
			}
			else Error(playerid, "Ten pojazd nie jest stworzony.");
		}
		case 4:
		{
			if(gui_cache[playerid][selected][2] == 3)//parking policyjny
			{
				gracz[playerid][parkingpol_id] = gui_cache[playerid][selected][0];
				SetPlayerCheckpoint(playerid, XYZ_PARKINGPOLICYJNY, 3.0);
				Info(playerid, "Miejsce odbioru pojazdu z parkingu policyjnego zostało oznaczone "COL_RED"czerwonym"COL_WHITE" punktem na mapie.");
				LeftNotifyShow(playerid, "Sukces!", "Punkt zaznaczono ~r~czerwonym~w~ punktem na mapie.", LN_GREEN);
			}
			else if(gui_cache[playerid][selected][2] != 2)//autoszrot
			{
				if(vehicleid != -1)
				{
					mq_format("UPDATE `pojazdy` SET `status`='2', `X`='%f', `Y`='%f', `Z`='%f', `rlg_lastused`='0' WHERE `id`='%d';", XYZ_AUTOSZROT, gui_cache[playerid][selected][0]);
					mq_send("QUpdateVehicleStatus");
					RemoveVehicle(vehicleid);
					LeftNotifyShow(playerid, "Sukces!", "Pojazd ~r~zezlomowany~w~.", LN_RED);
				}
				else
				{
					mq_format("UPDATE `pojazdy` SET `status`='2', `X`='%f', `Y`='%f', `Z`='%f', `rlg_lastused`='0' WHERE `id`='%d';", XYZ_AUTOSZROT, gui_cache[playerid][selected][0]);
					mq_send("QUpdateVehicleStatus");
					LeftNotifyShow(playerid, "Sukces!", "Pojazd ~r~zezlomowany~w~.", LN_RED);
				}
			}
			else
			{
				gracz[playerid][autoszrot_id] = gui_cache[playerid][selected][0];
				SetPlayerCheckpoint(playerid, XYZ_AUTOSZROT, 3.0);
				Info(playerid, "Miejsce odbioru pojazdu z Auto Szrotu zostało oznaczone "COL_RED"czerwonym"COL_WHITE" punktem na mapie.");
				LeftNotifyShow(playerid, "Sukces!", "Punkt zaznaczono ~r~czerwonym~w~ punktem na mapie.", LN_GREEN);
			}
		}
	}
	return 1;
}

Dialog:CARSELLTYPE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new vehicleid = VehicleUidToVehicleid(GetPVarInt(playerid, "cache_pcm_vehicledbid"));
	if(vehicleid != -1)
	{
		new Float:vPos[3];
		GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
		if(IsPlayerInRangeOfPoint(playerid, 8.0, vPos[0], vPos[1], vPos[2]))
		{
			switch(listitem)
			{
				case 0:
				{
					new strPlayerList[2048];
					format(strPlayerList, 2048, "ID\tNazwa gracza");
					new bool:find = false;
					for(new p = PlayerPoolSize(); p != -1; p--)
					{
						if(!gracz[p][loggedin]) continue;
						if(p == playerid) continue;
						if(gracz[p][admin_spec_enabled] == true) continue;
						new Float:pPos[3];
						GetPlayerPos(p, pPos[0], pPos[1], pPos[2]);
						if(IsPlayerInRangeOfPoint(playerid, 4.0, pPos[0], pPos[1], pPos[2]))
						{
							format(strPlayerList, 2048, "%s\n%d\t{%06x}%s", strPlayerList, p, GetPlayerColor(playerid) >>> 8,nick(p));
							find = true;
						}
					}
					if(find) Dialog_Show(playerid, CARSELLPLAYER, DIALOG_STYLE_TABLIST_HEADERS,  ""COL_RED"•» "COL_WHITE"Lista graczy w pobliżu "COL_RED"«•", strPlayerList, "Wybierz", "Anuluj");
					else Error(playerid, "Nie znaleziono żadnego gracza w pobliżu.");
				}
				case 1:
				{
					const Float:price_proc = 30.0;
					new Float:vehicle_price = CalcVehiclePriceEx(pojazd[vehicleid][v_model]);
					new Float:final_price = price_proc*vehicle_price/100.0;
					new strSell[1024];
					format(strSell, 1024, ""COL_WHITE"Czy jesteś pewien, że chcesz sprzedać pojazd "COL_BLUE"%s"COL_WHITE" za "COL_RED"%d%%"COL_WHITE" jego wartości rynkowej?", GetVehicleName(pojazd[vehicleid][v_model]), floatround(price_proc));
					format(strSell, 1024, "%s\nCena rynkowa tego pojazdu to: "COL_ORANGE"%d$"COL_WHITE"", strSell, floatround(vehicle_price));
					format(strSell, 1024, "%s\n"COL_RED"%d%%"COL_WHITE" ceny rynkowej tego pojazdu to: "COL_GREEN"%d$"COL_WHITE"", strSell, floatround(price_proc), floatround(final_price));
					format(strSell, 1024, "%s\n\nJeśli chcesz sprzedać pojazd "COL_BLUE"%s"COL_WHITE" za "COL_GREEN"%d$"COL_WHITE" wpisz poniżej: "COL_LIME"sprzedaje", strSell, GetVehicleName(pojazd[vehicleid][v_model]), floatround(final_price));
					Dialog_Show(playerid, CARSELLSCRAP, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_WHITE"Sprzedaż pojazdu na złom "COL_RED"«•", strSell, "Potwierdz", "Anuluj");
					SetPVarInt(playerid, "cache_cardeal_price", floatround(final_price));
				}
			}
		} 
		else Error(playerid, "Jesteś za daleko od pojazdu.");
	}
	else Error(playerid, "Ten pojazd nie jest stworzony.");

	return 1;
}

Dialog:CARSELLSCRAP(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(!compare(inputtext, "sprzedaje"))
	{
		Error(playerid, "Pojazd nie został sprzedany.");
		return 1;
	}
	new vehicleid = VehicleUidToVehicleid(GetPVarInt(playerid, "cache_pcm_vehicledbid"));
	if(vehicleid != -1)
	{
		new Float:vPos[3];
		GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
		if(IsPlayerInRangeOfPoint(playerid, 8.0, vPos[0], vPos[1], vPos[2]))
		{
			new strOffer[512];
			format(strOffer, 512, ""COL_GREEN"Sprzedałeś "COL_WHITE"pojazd "COL_ORANGE"%s"COL_WHITE" za "COL_GREEN"%d$"COL_WHITE".", GetVehicleName(pojazd[vehicleid][v_model]), GetPVarInt(playerid, "cache_cardeal_price"));
			Dialog_Show(playerid, CARSELLWAITEND, DIALOG_STYLE_MSGBOX,  ""COL_RED"•» "COL_WHITE"Pojazd sprzedany "COL_RED"«•", strOffer, "OK", "");
			mq_format("DELETE FROM `pojazdy` WHERE `id`='%d';", GetPVarInt(playerid, "cache_pcm_vehicledbid"));
			mq_send("QDeleteVehicle");
			RemoveVehicle(vehicleid);
			GiveMoney(playerid, GetPVarInt(playerid, "cache_cardeal_price"));
		} 
		else Error(playerid, "Jesteś za daleko od pojazdu.");
	}
	else Error(playerid, "Ten pojazd nie jest stworzony.");
	return 1;
}

Dialog:CARSELLPLAYER(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new vehicleid = VehicleUidToVehicleid(GetPVarInt(playerid, "cache_pcm_vehicledbid"));
	new clientid = strval(inputtext);
	SetPVarInt(playerid, "cache_carsell_clientid", clientid);
	if(vehicleid != -1)
	{
		new Float:vPos[3];
		GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
		if(IsPlayerInRangeOfPoint(playerid, 8.0, vPos[0], vPos[1], vPos[2]))
		{
			new Float:pPos[3];
			GetPlayerPos(clientid, pPos[0], pPos[1], pPos[2]);
			if(IsPlayerInRangeOfPoint(playerid, 4.0, pPos[0], pPos[1], pPos[2]))
			{
				if(PlayerAllCarsCount(clientid) >= MaxVehiclesPlayer(clientid)) return Error(playerid, "Ten gracz posiada już maxymalną ilość pojazdów.");
				if(PlayerCreatedCarsCount(clientid) >= MAX_PRIVCARSCREATED) return Error(playerid, "Ten gracz ma już maxymalną ilość pojazdów stworzonych na mapie.");
				if(gracz[clientid][PGodz] < 6) return Error(playerid, "Gracz musi mieć minimum 6 godzin całkowitego czasu ONLINE.");
				new strOffer[1024];
				format(strOffer, 1024, ""COL_LIME"Podaj cenę"COL_WHITE", za jaką chcesz sprzedać pojazd "COL_GREEN"%s"COL_WHITE" graczowi "COL_ORANGE"%s(%d)"COL_WHITE".\n", GetVehicleName(pojazd[vehicleid][v_model]), nick(clientid), clientid);
				Dialog_Show(playerid, CARSELLPRICE, DIALOG_STYLE_INPUT,  ""COL_RED"•» "COL_WHITE"Podaj cenę "COL_RED"«•", strOffer, "Oferuj", "Anuluj");
			}
			else Error(playerid, "Gracz któremu chcesz sprzedać pojazd, nie jest w pobliżu.");
		} 
		else Error(playerid, "Jesteś za daleko od pojazdu.");
	}
	else Error(playerid, "Ten pojazd nie jest stworzony.");
	return 1;
}

Dialog:CARSELLPRICE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new vehicleid = VehicleUidToVehicleid(GetPVarInt(playerid, "cache_pcm_vehicledbid"));
	new clientid = GetPVarInt(playerid, "cache_carsell_clientid");
	new price = strval(inputtext);
	if(price < 0) return Error(playerid, "Kwota nie może być mniejsza niż 0$.");
	if(price > 10000000) return Error(playerid, "Kwota nie może być większa niż 10000000$.");
	if(vehicleid != -1)
	{
		new Float:vPos[3];
		GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
		if(IsPlayerInRangeOfPoint(playerid, 8.0, vPos[0], vPos[1], vPos[2]))
		{
			new Float:pPos[3];
			GetPlayerPos(clientid, pPos[0], pPos[1], pPos[2]);
			if(IsPlayerInRangeOfPoint(playerid, 4.0, pPos[0], pPos[1], pPos[2]))
			{
				if(PlayerAllCarsCount(clientid) >= MaxVehiclesPlayer(clientid)) return Error(playerid, "Ten gracz posiada już maxymalną ilość pojazdów.");
				if(PlayerCreatedCarsCount(clientid) >= MAX_PRIVCARSCREATED) return Error(playerid, "Ten gracz ma już maxymalną ilość pojazdów stworzonych na mapie.");
				if(price > Money(clientid)) return Error(playerid, "Ten gracz nie posiada przy sobie takiej ilości gotówki.");
				new strOffer[3000];
				format(strOffer, 3000, ""COL_WHITE"Otrzymałeś ofertę zakupu pojazdu "COL_GREEN"%s"COL_WHITE" od gracza "COL_ORANGE"%s(%d)"COL_WHITE" za kwotę "COL_LIME"%d$"COL_WHITE".", GetVehicleName(pojazd[vehicleid][v_model]), nick(playerid), playerid, price);
				format(strOffer, 3000, "%s\n"COL_WHITE"Oferta dotyczy pojazdu obok którego się oboje znajdujecie.", strOffer);
				new col1 = pojazd[vehicleid][v_color][0];
				new col2 = pojazd[vehicleid][v_color][1];
				format(strOffer, 3000, "%s\n"COL_WHITE"Przebieg pojazdu "COL_GREEN"%s"COL_WHITE" to "COL_RED"%d km"COL_WHITE". Pojazd posiada następujące kolory: {%06x}[kolor1] {%06x}[kolor2]", strOffer, GetVehicleName(pojazd[vehicleid][v_model]), pojazd[vehicleid][v_przebieg], VehicleColoursTableRGBA[col1] >>> 8, VehicleColoursTableRGBA[col2] >>> 8);
				new Float:ileprzejade = 100*pojazd[vehicleid][v_paliwo]/pojazd_spec[GetVehicleSpecID(pojazd[vehicleid][v_model])][vspec_fuelconsumption]; 
				format(strOffer, 3000, "%s\n"COL_WHITE"W pojeździe jest "COL_GREEN"%0.2f litrów"COL_WHITE" paliwa. Starczy to na "COL_GREEN"%d km"COL_WHITE".", strOffer, pojazd[vehicleid][v_paliwo], floatround(ileprzejade));
				format(strOffer, 3000, "%s\n"COL_WHITE"Jeśli akcpetujesz ofertę, wpisz poniżej słowo: "COL_LIME"akceptuje", strOffer);
				Dialog_Show(clientid, CARSELLOFFER, DIALOG_STYLE_INPUT,  ""COL_RED"•» "COL_WHITE"Oferta kupna pojazdu "COL_RED"«•", strOffer, "Potwierdz", "Anuluj");
				SetPVarInt(clientid, "cache_cardeal_vehicledbid", GetPVarInt(playerid, "cache_pcm_vehicledbid"));
				SetPVarInt(clientid, "cache_cardeal_price", price);
				SetPVarInt(clientid, "cache_cardeal_vendoruid", gracz[playerid][UID]);
				format(strOffer, 3000, ""COL_WHITE"Trwa oczekiwanie, aż "COL_ORANGE"%s"COL_WHITE" zaakceptuje Twoją ofertę. Jeśli chcesz ją "COL_RED"anulować"COL_WHITE", wciśnij przycisk "COL_RED"Anuluj"COL_WHITE".", nick(clientid));
				Dialog_Show(playerid, CARSELLWAIT, DIALOG_STYLE_MSGBOX,  ""COL_RED"•» "COL_WHITE"Oczekiwanie na zaakceptowanie oferty "COL_RED"«•", strOffer, "Anuluj", "");
			}
			else Error(playerid, "Gracz któremu chcesz sprzedać pojazd, nie jest w pobliżu.");
		} 
		else Error(playerid, "Jesteś za daleko od pojazdu.");
	}
	else Error(playerid, "Ten pojazd nie jest stworzony.");
	return 1;
}

Dialog:CARSELLOFFER(playerid, response, listitem, inputtext[])
{
	new vehicledbid = GetPVarInt(playerid, "cache_cardeal_vehicledbid");
	new price = GetPVarInt(playerid, "cache_cardeal_price");
	new vendoruid = GetPVarInt(playerid, "cache_cardeal_vendoruid");
	if(vendoruid == 0) return Error(playerid, "Oferta nieaktualna.");
	new strOffer[512];
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(!IsPlayerConnected(p)) continue;
		if(!gracz[p][loggedin]) continue;
		if(gracz[p][UID] == vendoruid)
		{
			if(!response || !compare(inputtext, "akceptuje"))
			{
				format(strOffer, 512, ""COL_WHITE"Gracz "COL_ORANGE"%s"COL_RED" odrzucił "COL_WHITE"Twoją ofertę.", nick(playerid));
				Dialog_Show(p, CARSELLWAITEND, DIALOG_STYLE_MSGBOX,  ""COL_RED"•» "COL_WHITE"Oferta odrzucona "COL_RED"«•", strOffer, "OK", "");
				format(strOffer, 512, ""COL_RED"Odrzuciłeś "COL_WHITE"ofertę od "COL_ORANGE"%s"COL_WHITE".", nick(p));
				Dialog_Show(playerid, CARSELLWAITEND, DIALOG_STYLE_MSGBOX,  ""COL_RED"•» "COL_WHITE"Oferta odrzucona "COL_RED"«•", strOffer, "OK", "");
				return 1;
			}
			if(price > Money(playerid))
			{
				Error(playerid, "Nie posiadasz wystarczającej ilości gotówki.");
				Error(p, "Gracz, któremu złożyłeś ofertę, nie posiada wystarczającej ilości gotówki.");
				return 1;
			}
			TakeMoney(playerid, price);
			GiveMoney(p, price);
			mq_format("UPDATE `pojazdy` SET `owner`='%d' WHERE `owner`='%d' AND `id`='%d';", gracz[playerid][UID], vendoruid, vehicledbid);
			mq_send("QCarDeal");
			for(new v = GetVehiclePoolSize(); v != -1; v--)
			{
				if(pojazd[v][v_id] == vehicledbid)
				{
					pojazd[v][v_owner] = gracz[playerid][UID];
					break;
				}
			}
			format(strOffer, 512, ""COL_WHITE"Gracz "COL_ORANGE"%s"COL_GREEN" przyjął "COL_WHITE"Twoją ofertę. Transakcja dobiegła końca, otrzymujesz "COL_GREEN"%d$"COL_WHITE".", nick(playerid), price);
			Dialog_Show(p, CARSELLWAITEND, DIALOG_STYLE_MSGBOX,  ""COL_RED"•» "COL_WHITE"Pojazd sprzedany "COL_RED"«•", strOffer, "OK", "");
			format(strOffer, 512, ""COL_GREEN"Kupiłeś "COL_WHITE"pojazd od "COL_ORANGE"%s"COL_WHITE" za "COL_BLUE"%d$"COL_WHITE". Panel zarządzania pojazdami znajdziesz pod komendą "COL_RED"/v lista"COL_WHITE"", nick(p), price);
			Dialog_Show(playerid, CARSELLWAITEND, DIALOG_STYLE_MSGBOX,  ""COL_RED"•» "COL_WHITE"Pojazd kupiony "COL_RED"«•", strOffer, "OK", "");
			return 1;
		}
	}
	Error(playerid, "Ups! Coś się nie udało. Spróbujcie jeszcze raz...");
	return 1;
}

Dialog:CARSELLWAIT(playerid, response, listitem, inputtext[])
{
	new clientid = GetPVarInt(playerid, "cache_carsell_clientid");
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(p == clientid)
		{
			Dialog_Close(p);
			Dialog_Close(playerid);
			SetPVarInt(p, "cache_cardeal_vendoruid", 0);
			LeftNotifyShow(p, "error", "Sprzedajacy ~r~anulowal~w~ oferte.", LN_RED);
			LeftNotifyShow(playerid, "Sukces!", "Oferta zostala ~r~anulowana~w~.", LN_RED);
			return 1;
		}
	}
	return 1;
}

forward Vehicle_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
public Vehicle_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	//nitro hold detect
	if(GetPlayerVehicleSeat(playerid) == 0)
	{
		if(HOLDING(KEY_FIRE) || HOLDING(KEY_ACTION))
		{
			gracz[playerid][holding_key_nitro] = serwer[time_timestamp]+20;
		}
		else if(RELEASED(KEY_FIRE) || RELEASED(KEY_ACTION))
		{
			gracz[playerid][holding_key_nitro] = 0;
		}
	}
	if(gracz[playerid][wypadek] > 0) return 1;
	new vehicleid = GetPlayerVehicleID(playerid);
	if(vehicleid != 0)//*****************************************W POJEŹDZIE
	{
		if(gracz[playerid][truckbuy_status]) return 1;
		if(gracz[playerid][frakcja] == F_EMERGENCY && IsPlayerOnDutyFraction(playerid))
		{
			if(PRESSED(KEY_HANDBRAKE))
			{
				//on/off dla gaszenia helikopterem
				if(IsHelicopterUseWater(vehicleid))//używa już gaszenia
				{
					if(ToggleHelicopterWater(vehicleid, 0))
					{
						LeftNotifyShow(playerid, "Gaszenie", "Wylaczono gaszenie pozaru helikopterem. Aby wlaczyc wcisnij: SPACJA.", LN_RED);
						return 1;
					}
				}
				else//nie używa
				{
					if(ToggleHelicopterWater(vehicleid, 1))
					{
						LeftNotifyShow(playerid, "Gaszenie", "Wlaczono gaszenie pozaru helikopterem. Aby wylaczyc wcisnij SPACJA.", LN_GREEN);
						return 1;
					}
				}
			}
		}
		if(SpecialVehicle(vehicleid)) return 1;
		if(GetPlayerVehicleSeat(playerid) == 0 && IsPlayerCanDrive(playerid, vehicleid))//****WŁAŚCICIEL(uprawniony) KIEROWCA
		{
			if(PRESSED(KEY_LOOK_BEHIND))
			{
				if(gracz[playerid][event_saved] == true && pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_EVENT) return 1;
				new strVehMenu[1024];
				new strTitle[128];
				if(IsVehicleBike(pojazd[vehicleid][v_model]))
				{
					format(strVehMenu, 1024, ""COL_LIME"•»\t"COL_GREEN"Odpal"COL_WHITE"/"COL_RED"Zgaś"COL_WHITE" silnik "COL_GREY"[klawisz: Y]\t"COL_LIME"«•");
					format(strVehMenu, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"Włącz"COL_WHITE"/"COL_RED"Wyłącz "COL_WHITE"światła "COL_GREY"[klawisz: lewy CTRL]\t"COL_LIME"«•", strVehMenu);
					format(strVehMenu, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"Zaparkuj\t"COL_LIME"«•", strVehMenu);
					format(strVehMenu, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"Zmień napis na rejestracji\t"COL_LIME"«•", strVehMenu);
					format(strVehMenu, 1024, "%s\n"COL_LIME"•»\t"COL_BLUE"Specyfikacja pojazdu\t"COL_LIME"«•", strVehMenu);
				}
				else
				{
					format(strVehMenu, 1024, ""COL_LIME"•»\t"COL_GREEN"Odpal"COL_WHITE"/"COL_RED"Zgaś"COL_WHITE" silnik "COL_GREY"[klawisz: Y]\t"COL_LIME"«•");
					format(strVehMenu, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"Włącz"COL_WHITE"/"COL_RED"Wyłącz "COL_WHITE"światła "COL_GREY"[klawisz: lewy CTRL]\t"COL_LIME"«•", strVehMenu);
					format(strVehMenu, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"Zaciągnij"COL_WHITE"/"COL_RED"Zwolnij "COL_WHITE"ręczny"COL_GREY" [klawisz: SPACJA]\t"COL_LIME"«•", strVehMenu);
					format(strVehMenu, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"Otwórz"COL_WHITE"/"COL_RED"Zamknij "COL_WHITE"pojazd\t"COL_LIME"«•", strVehMenu);
					format(strVehMenu, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"Włącz"COL_WHITE"/"COL_RED"Wyłącz "COL_ORANGE"światła awaryjne\t"COL_LIME"«•", strVehMenu);
					format(strVehMenu, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"Otwórz"COL_WHITE"/"COL_RED"Zamknij "COL_WHITE"maskę\t"COL_LIME"«•", strVehMenu);
					format(strVehMenu, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"Otwórz"COL_WHITE"/"COL_RED"Zamknij "COL_WHITE"bagażnik\t"COL_LIME"«•", strVehMenu);
					format(strVehMenu, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"Otwórz"COL_WHITE"/"COL_RED"Zamknij "COL_WHITE"okno\t"COL_LIME"«•", strVehMenu);
					format(strVehMenu, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"Zaparkuj\t"COL_LIME"«•", strVehMenu);
					format(strVehMenu, 1024, "%s\n"COL_LIME"•»\t"COL_EASY"Zmień napis na rejestracji\t"COL_LIME"«•", strVehMenu);
					format(strVehMenu, 1024, "%s\n"COL_LIME"•»\t"COL_BLUE"Specyfikacja pojazdu\t"COL_LIME"«•", strVehMenu);
				}
				format(strTitle, 128, ""COL_RED"•» "COL_WHITE"Zarządzanie pojazdem "COL_ORANGE"%s(%d) "COL_RED"«•", GetVehicleName(pojazd[vehicleid][v_model]), pojazd[vehicleid][v_id]);
				Dialog_Show(playerid, VEHICLECP, DIALOG_STYLE_TABLIST, strTitle, strVehMenu, "Wybierz", "Anuluj");
			}
			if(PRESSED(KEY_LOOK_LEFT) && newkeys != 320)
			{
				if(!IsCarBlinking(vehicleid)) SetCarBlinking(vehicleid, 0), SetPVarInt(playerid, "blink-car", vehicleid);
				else DisableCarBlinking(vehicleid);
			}
			else if(PRESSED(KEY_LOOK_RIGHT) && newkeys != 320)
			{
				if(!IsCarBlinking(vehicleid)) SetCarBlinking(vehicleid, 1), SetPVarInt(playerid, "blink-car", vehicleid);
				else DisableCarBlinking(vehicleid);
			}
			else if(PRESSED(KEY_YES))
			{
				if(Spam(playerid, SPAM_KEYENGINE, 1, false)) return 1;
				dialog_VEHICLECP(playerid, 1, 0, "NULL");
			}
			else if(PRESSED(KEY_NO))
			{
				if(Spam(playerid, SPAM_KEYRADIONEXT, 1, false)) return 1;
				new station = gracz[playerid][radio_laststation];
				station++;
				if(station >= sizeof(radio_stations)) station = -1;

				if(station == -1 && strlen(gracz[playerid][custom_radio]) < 3) station = 0; 

				if(station != -1)
				{
					GameTextForPlayer(playerid, radio_stations[station][rs_title],  1000, 4);
					PlayAudioStreamForPlayer(playerid, radio_stations[station][rs_url]);
				}
				else
				{
					GameTextForPlayer(playerid, "NIESTANDARDOWE",  1000, 4);
					dialog_CUSTOMRADIO(playerid, true, 3, "null");
				}
				gracz[playerid][radio_laststation] = station;
				gracz[playerid][radio_displaystep] = 0;
				Process_Radio(playerid);
			}
			else if(PRESSED(KEY_HANDBRAKE))
			{
				if(gracz[playerid][td_dokumenty] > 0) return Dokument_Hide(playerid);
				if(gracz[playerid][dystrybutor_status]) return 1;
				if(gracz[playerid][event_saved] == true && pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_EVENT) return 1;
				if(Spam(playerid, SPAM_KEYHANDBRAKE, 1, false)) return 1;
				if(pojazd[vehicleid][v_handbrake])
				{
					Handbrake(vehicleid, false);
					LeftNotifyShow(playerid, "Sukces!", "Hamulec reczny zostal ~r~zwolniony~w~.", LN_RED);
				}
				else
				{
					if(gracz[playerid][opu_speed] == 0)
					{
						if(BattleBlock(playerid)) return Error(playerid, "Na terenie walki jest zakaz używania ręcznego.");
						Handbrake(vehicleid, true);
						LeftNotifyShow(playerid, "Sukces!", "Hamulec reczny zostal ~g~zaciagniety~w~.", LN_GREEN);
					}
				}
			}
			else if(PRESSED(KEY_ACTION))
			{
				//if(pojazd[vehicleid][v_trafficlights]) TrafficLight(vehicleid, 0);
				//else TrafficLight(vehicleid, 1);

				new engine, lights, alarm, doors, bonnet, boot, objective;
				GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
				if(IsVehicleBike(pojazd[vehicleid][v_model]) || !HasTrafficLight(pojazd[vehicleid][v_model]))
				{
					if(lights)
					{
						CarHUD_Light(playerid, 0);
						SetVehicleParamsEx(vehicleid, engine, 0, alarm, doors, bonnet, boot, objective);
						GameTextForPlayer(playerid, "~r~SWIATLA: WYLACZONE",  1000, 4);
					}
					else 
					{
						CarHUD_Light(playerid, 1);
						SetVehicleParamsEx(vehicleid, engine, 1, alarm, doors, bonnet, boot, objective);
						GameTextForPlayer(playerid, "~g~SWIATLA: MIJANIA",  1000, 4);
					}
				}
				else
				{
					if(pojazd[vehicleid][v_trafficlights]) 
					{
						CarHUD_Light(playerid, 0);
						TrafficLight(vehicleid, 0);
						SetVehicleParamsEx(vehicleid, engine, 0, alarm, doors, bonnet, boot, objective);
						GameTextForPlayer(playerid, "~r~SWIATLA: WYLACZONE",  1000, 4);
						ToggleVehicleNeons(vehicleid, 0);
						new trailerid = GetVehicleTrailer(vehicleid);
						if(trailerid != 0)
						{
							GetVehicleParamsEx(trailerid, engine, lights, alarm, doors, bonnet, boot, objective);
							SetVehicleParamsEx(trailerid, engine, 0, alarm, doors, bonnet, boot, objective);
						}
					}
					else if(lights)
					{
						CarHUD_Light(playerid, 2);
						SetVehicleParamsEx(vehicleid, engine, 1, alarm, doors, bonnet, boot, objective);
						TrafficLight(vehicleid, 1);
						GameTextForPlayer(playerid, "~b~SWIATLA: DROGOWE",  1000, 4);
						ToggleVehicleNeons(vehicleid, 1);
						new trailerid = GetVehicleTrailer(vehicleid);
						if(trailerid != 0)
						{
							GetVehicleParamsEx(trailerid, engine, lights, alarm, doors, bonnet, boot, objective);
							SetVehicleParamsEx(trailerid, engine, 1, alarm, doors, bonnet, boot, objective);
						}
					}
					else 
					{
						CarHUD_Light(playerid, 1);
						SetVehicleParamsEx(vehicleid, engine, 1, alarm, doors, bonnet, boot, objective);
						GameTextForPlayer(playerid, "~g~SWIATLA: MIJANIA",  1000, 4);
						ToggleVehicleNeons(vehicleid, 1);
						new trailerid = GetVehicleTrailer(vehicleid);
						if(trailerid != 0)
						{
							GetVehicleParamsEx(trailerid, engine, lights, alarm, doors, bonnet, boot, objective);
							SetVehicleParamsEx(trailerid, engine, 1, alarm, doors, bonnet, boot, objective);
						}
					}
				}
				//nitro - key action
				if(pojazd[vehicleid][v_tune_data][5] != 0)//ma nitro na wyposażeniu
				{
					if(!(GetVehicleComponentInSlot(vehicleid, 5) && pojazd[vehicleid][v_whilenitro]))//jest wyłączone
					{
						if(pojazd[vehicleid][v_nitrotime] > 5)
						{
							//GameTextForPlayer(playerid, "~g~NIxTRO: ON",  1000, 4);
							pojazd[vehicleid][v_whilenitro] = true;
							pojazd[vehicleid][v_nitro_tick] = GetTickCount()+300;
						}
						else 
						{
							RemoveVehicleComponent(vehicleid, pojazd[vehicleid][v_tune_data][5]);
							//GameTextForPlayer(playerid, "~r~NIxTRO:~y~ OVER",  1000, 4);
						}
					}
				}
				//nitro end
			}
			else if(RELEASED(KEY_ACTION))
			{
				if(pojazd[vehicleid][v_tune_data][5] != 0)//ma nitro na wyposażeniu
				{
					if(pojazd[vehicleid][v_nitro_tick] < GetTickCount())
					{
						RemoveVehicleComponent(vehicleid, pojazd[vehicleid][v_tune_data][5]);
						if(pojazd[vehicleid][v_nitrotime] > 5) AddVehicleComponent(vehicleid, pojazd[vehicleid][v_tune_data][5]);
						if(pojazd[vehicleid][v_whilenitro])//jest uruchomione
						{
							//wyłącza je
							//GameTextForPlayer(playerid, "~r~NIxTRO: OFF",  1000, 4);
							pojazd[vehicleid][v_whilenitro] = false;
						}
					}
				}
			}
			else if(PRESSED(KEY_FIRE))
			{
				if(gracz[playerid][frakcja] == F_ROADASSIST)
				{
					if(IsPlayerOnDutyFraction(playerid))
					{
						if(pojazd[vehicleid][v_model] == 525)
						{
							new Float:vX,Float:vY,Float:vZ;
							new bool:found = false;
							if(IsTrailerAttachedToVehicle(gracz[playerid][opu_vehicleid]))
							{
								new towedid = gracz[playerid][towtruck_trailerid];
								DetachTrailerFromVehicle(gracz[playerid][opu_vehicleid]);
								/*if(pojazd[towedid][v_owner_type] == VEHICLE_PLAYER)//parkowanie tylko privów
								{
									GetVehiclePos(towedid, pojazd[towedid][v_X], pojazd[towedid][v_Y], pojazd[towedid][v_Z]);
									GetVehicleZAngle(towedid, pojazd[towedid][v_R]);
									mq_format("UPDATE `pojazdy` SET `X`='%f', `Y`='%f', `Z`='%f', `R`='%f' WHERE `id`='%d';", pojazd[towedid][v_X], pojazd[towedid][v_Y], pojazd[towedid][v_Z], pojazd[towedid][v_R], pojazd[towedid][v_id]);
									mq_send("QUpdateVehiclePos");
								}*/
								Handbrake(towedid, true);
								new strInfo[128];
								format(strInfo, 128, "Przestałeś holować pojazd "COL_FMSG"%s"COL_WHITE".", GetVehicleName(pojazd[towedid][v_model]));
								Info(playerid, strInfo);
								gracz[playerid][towtruck_trailerid] = 0;
								printf("[HOLOWANIE] Gracz %s przestal holowac pojazd UID: %d.", nick(playerid), vehicleid);
								return 1;
							}
							for(new v = GetVehiclePoolSize(); v != -1; v--)
							{
								if(pojazd[v][v_owner_type] != VEHICLE_PLAYER && pojazd[v][v_owner_type] != VEHICLE_BUSINESS) continue;
								GetVehiclePos(v, vX, vY, vZ);
								if((floatabs(gracz[playerid][PosX]-vX) < 10.0) && (floatabs(gracz[playerid][PosY]-vY) < 10.0) && (floatabs(gracz[playerid][PosZ]-vZ) < 10.0) && (v != gracz[playerid][opu_vehicleid]))
								{
									if(IsVehicleInUseByDriver(v) == INVALID_PLAYER_ID)
									{
										found = true;
										Handbrake(v, false);
										AttachTrailerToVehicle(v, gracz[playerid][opu_vehicleid]);
										new strInfo[128];
										format(strInfo, 128, "Holujesz "COL_FMSG"%s"COL_WHITE". Aby przestać ponownie wciśnij "COL_ORANGE"LPM"COL_WHITE".", GetVehicleName(pojazd[v][v_model]));
										Info(playerid, strInfo);
										printf("[HOLOWANIE] Gracz %s zaczal holowac pojazd UID: %d.", nick(playerid), v);
									}
									break;
								}
							}
							if(!found) Error(playerid, "Brak pojazdu w pobliżu do holowania (pamiętaj, że w pojeździe nie może być kierowcy).");
						}
					}
				}
				//nitro - key fire
				if(pojazd[vehicleid][v_tune_data][5] != 0)//ma nitro na wyposażeniu
				{
					if(!(GetVehicleComponentInSlot(vehicleid, 5) && pojazd[vehicleid][v_whilenitro]))//jest wyłączone
					{
						if(pojazd[vehicleid][v_nitrotime] > 5)
						{
							GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~n~~g~NITRO: ON",  1000, 3);
							pojazd[vehicleid][v_whilenitro] = true;
							pojazd[vehicleid][v_nitro_tick] = GetTickCount()+300;
						}
						else 
						{
							RemoveVehicleComponent(vehicleid, pojazd[vehicleid][v_tune_data][5]);
							GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~n~~r~NITRO:~y~ LOAD",  1000, 3);
						}
					}
				}
				//nitro end

			}
			else if(RELEASED(KEY_FIRE))
			{
				if(pojazd[vehicleid][v_tune_data][5] != 0)//ma nitro na wyposażeniu
				{
					if(pojazd[vehicleid][v_nitro_tick] < GetTickCount())
					{
						RemoveVehicleComponent(vehicleid, pojazd[vehicleid][v_tune_data][5]);
						if(pojazd[vehicleid][v_nitrotime] > 5) AddVehicleComponent(vehicleid, pojazd[vehicleid][v_tune_data][5]);
						if(pojazd[vehicleid][v_whilenitro])//jest uruchomione
						{
							//wyłącza je
							GameTextForPlayer(playerid, "~n~~n~~n~~n~~n~~n~~n~~n~~n~~r~NITRO: OFF",  1000, 3);
							pojazd[vehicleid][v_whilenitro] = false;
						}
					}
				}
			}
			else if(PRESSED(KEY_CROUCH))//klawisz H
			{
				if(pojazd[vehicleid][v_model] == 525)//Towtruck
				{
					if(pojazd[vehicleid][v_roosters_withoutsiren])
					{
						pojazd[vehicleid][v_roosters_withoutsiren] = false;
						Info(playerid, "Koguty "COL_RED"wyłączone"COL_WHITE".");
					}
					else
					{
						pojazd[vehicleid][v_roosters_withoutsiren] = true;
						Info(playerid, "Koguty "COL_GREEN"włączone"COL_WHITE".");
					}
				}
			}
			//******************************************************************************************
			/*
			//automatyczne wyłączanie kierunków
			if(IsCarBlinking(vehicleid))
			{
				new Float:a, Float:b = BlinkR[vehicleid];
				GetVehicleZAngle(vehicleid, a);

				if(BlinkSide[vehicleid] == 0)
				{
					b+=BLINK_TURN_ANGLE;
					if(b > 360.0) b -=360.0;
					if(a < b-180) a = a+360;
					if(b < a-180) b = b+360;

					if(a > b) DisableCarBlinking(vehicleid);
				}
				else if(BlinkSide[vehicleid] == 1)
				{
					b-=BLINK_TURN_ANGLE;
					if(b < 0.0) b = 360.0 + b;
					if(a < b-180) a = a+360;
					if(b < a-180) b = b+360;

					if(a < b) DisableCarBlinking(vehicleid);
				}
			}
			*/
		}
	}
	else//*****************************************POZA POJAZDEM
	{
		if(gracz[playerid][truckbuy_status]) 
		{
			if(PRESSED(KEY_YES))
			{
				gracz[playerid][truckbuy_status] = 0;
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, true);
				SalonTruckSelectTDHide(playerid);
				Info(playerid, "Zakup pojazdu został anulowany.");
				return 1;
			}
			if(RELEASED(KEY_SECONDARY_ATTACK))
			{
				
				new specid = truckshop_specid[gracz[playerid][truckbuy_selected]];
				new strTemp[512];
				SetPVarInt(playerid, "truckbuy_buyselect", gracz[playerid][truckbuy_selected]);
				if(truckshop_price[gracz[playerid][truckbuy_selected]] <= Money(playerid))
				{
					for(new v = GetVehiclePoolSize(); v != -1; v--)
					{
						if(truckshop_db_id[gracz[playerid][truckbuy_selected]] == pojazd[v][v_id])
						{
							DeletePVar(playerid, "BuyCompanyTrailer");
 							if(IsVehicleTruckSalonBanned(pojazd[v][v_model]))
							{
								Error(playerid, "Ten pojazd jest niedostępny.");
								GameTextForPlayer(playerid, "~r~NIEDOSTEPNY",  1000, 4);
								return 1;
							}
							new cid = gracz[playerid][firma];
							if(IsVehicleTrailer(pojazd[v][v_model]))//zakup naczep firmowych
							{
								if(cid == 0)
								{
									Error(playerid, "Zakup naczep jest dostępny tylko dla firm.");
									GameTextForPlayer(playerid, "~r~DLA FIRM",  1000, 4);
									return 1;
								}
								else
								{
									if(gracz[playerid][firma_permlvl] == 0) return Error(playerid, "Nie posiadasz uprawnień do zakupu pojazdu firmowego.");
									SetPVarInt(playerid, "BuyCompanyTrailer", cid);
								}
							}

							if(GetPVarInt(playerid, "BuyCompanyTrailer") == 0)
							{
								if(PlayerAllCarsCount(playerid) >= MaxVehiclesPlayer(playerid)) return Error(playerid, "Posiadasz już maxymalną ilość pojazdów.");
								if(PlayerCreatedCarsCount(playerid) >= MAX_PRIVCARSCREATED) return Error(playerid, "Masz już maxymalną ilość pojazdów stworzonych na mapie.");
							}
							else
							{
								if(CompanyVehiclesCount(cid) >= MAX_CVEHICLES) return Error(playerid, "Posiadasz już maxymalną ilość pojazdów w firmie.");
							}

							format(strTemp, 512, ""COL_WHITE"Czy jesteś pewien, że chcesz zakupić pojazd "COL_GREEN"%s "COL_WHITE"za {FFCE00}%d$"COL_WHITE"?\n", GetVehicleName(pojazd[v][v_model]), truckshop_price[gracz[playerid][truckbuy_selected]]);
							format(strTemp, 512, "%s\n"COL_BLUE"Specyfikacja techniczna"COL_WHITE":", strTemp);
							if(specid > 0)
							{
								if(pojazd_spec[specid][vspec_fueltype] == F_PB) format(strTemp, 512, "%s\n{428FB8}TYP PALIWA:"COL_GREEN" PB", strTemp);
								else if(pojazd_spec[specid][vspec_fueltype] == F_ON) format(strTemp, 512, "%s\n{428FB8}TYP PALIWA:{6D6D6D} ON", strTemp);
								format(strTemp, 512, "%s\n{6DC5F3}POJEMNOŚĆ ZBIORNIKA:{45A081} %d "COL_WHITE"[litr]", strTemp, pojazd_spec[specid][vspec_tanksize]);
								format(strTemp, 512, "%s\n{428FB8}SPALANIE:{45A081} %0.1f "COL_WHITE"[litr/100km]", strTemp, pojazd_spec[specid][vspec_fuelconsumption]+0.01);
								format(strTemp, 512, "%s\n{6DC5F3}PRZYŚPIESZENIE (0-100):{45A081} %0.1f "COL_WHITE"[sekund]", strTemp, pojazd_spec[specid][vspec_0100]+0.01);
								format(strTemp, 512, "%s\n{428FB8}PRĘDKOŚĆ MAXYMALNA (V-MAX):{45A081} %d "COL_WHITE"[km/h]", strTemp, pojazd_spec[specid][vspec_vmax]);
							}
							if(VehicleCapacity(pojazd[v][v_model])) format(strTemp, 512, "%s\n{6DC5F3}ŁADOWNOŚĆ: {FF8100}%d "COL_WHITE"[kg]", strTemp,VehicleCapacity(pojazd[v][v_model]));
							Dialog_Show(playerid, TRUCKBUYCONF, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_LIME"ZATWIERDZENIE ZAKUPU"COL_RED" «•", strTemp, "Kup", "Anuluj");
							break;
						}
					}
				}
				else Error(playerid, "Niewystarczająca ilość gotówki.");
				return 1;
			}
			const time = 1000;
			new bool:next = false;
			if(gracz[playerid][gpk_leftright] == KEY_LEFT) 
			{
				gracz[playerid][truckbuy_selected]--;
				next = true;
				if(gracz[playerid][truckbuy_selected] < 0)
				{
					for(new t; t < MAX_SALONTRUCKSLOTS; t++)
					{
						if(truckshop_db_id[t] != 0) gracz[playerid][truckbuy_selected] = t;
					}
				}
			}
			else if(gracz[playerid][gpk_leftright] == KEY_RIGHT) 
			{
				gracz[playerid][truckbuy_selected]++;
				next = true;
				if(truckshop_db_id[gracz[playerid][truckbuy_selected]] == 0) gracz[playerid][truckbuy_selected] = 0;
			}
			if(next)
			{
				for(new v = GetVehiclePoolSize(); v != -1; v--)
				{
					if(truckshop_db_id[gracz[playerid][truckbuy_selected]] == pojazd[v][v_id])
					{
						new Float:camX, Float:camY;
						GetXYInFrontOfVehicle(v, camX, camY, 20.0);
						new Float:temp_cp[3];
						new Float:temp_cl[3];
						for(new c; c < 3; c++)
						{
							temp_cp[c] = gracz[playerid][truckbuy_campos][c];
							temp_cl[c] = gracz[playerid][truckbuy_camlook][c];
						}

						gracz[playerid][truckbuy_campos][0] = camX;
						gracz[playerid][truckbuy_campos][1] = camY+10;
						gracz[playerid][truckbuy_campos][2] = pojazd[v][v_Z]+8.0;
						gracz[playerid][truckbuy_camlook][0] = pojazd[v][v_X];
						gracz[playerid][truckbuy_camlook][1] = pojazd[v][v_Y];
						gracz[playerid][truckbuy_camlook][2] = pojazd[v][v_Z];

						InterpolateCameraPos(playerid, temp_cp[0],  temp_cp[1],  temp_cp[2], gracz[playerid][truckbuy_campos][0], gracz[playerid][truckbuy_campos][1], gracz[playerid][truckbuy_campos][2], time, CAMERA_CUT);
						InterpolateCameraLookAt(playerid, temp_cl[0], temp_cl[1], temp_cl[2], gracz[playerid][truckbuy_camlook][0], gracz[playerid][truckbuy_camlook][1], gracz[playerid][truckbuy_camlook][2], time, CAMERA_CUT);
						
						new specid = truckshop_specid[gracz[playerid][truckbuy_selected]];
						if(specid > 0) SalonTruckSelectTDShow(playerid, GetVehicleName(pojazd[v][v_model]), truckshop_price[gracz[playerid][truckbuy_selected]], VehicleCapacity(pojazd[v][v_model]), pojazd_spec[specid][vspec_fueltype], pojazd_spec[specid][vspec_tanksize], pojazd_spec[specid][vspec_fuelconsumption], pojazd_spec[specid][vspec_0100], pojazd_spec[specid][vspec_vmax]);
						else SalonTruckSelectTDShow(playerid, GetVehicleName(pojazd[v][v_model]), truckshop_price[gracz[playerid][truckbuy_selected]], VehicleCapacity(pojazd[v][v_model]), -1, 0, 0.0, 0.0, 0);

						break;
					}
				}
			}
		}
		else if(PRESSED(KEY_YES))
		{
 			if(IsPlayerInRangeOfPoint(playerid, 3.0, XYZ_SALON))//kupowania auta w salonie priv aut
			{
				if(PlayerAllCarsCount(playerid) >= MaxVehiclesPlayer(playerid)) return Error(playerid, "Posiadasz już maxymalną ilość pojazdów.");
				if(PlayerCreatedCarsCount(playerid) >= MAX_PRIVCARSCREATED) return Error(playerid, "Masz już maxymalną ilość pojazdów stworzonych na mapie.");
				new strTemp[1024];
				format(strTemp, 1024, ""COL_LIME"•\t"COL_GREEN" • Nazwa pojazdu •\t{FFCE00}$ Cena $\t"COL_LIME"•%s", carshop_buylist);
				Dialog_Show(playerid, CARBUY, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_LIME"Pojazdy dostępne do zakupienia w salonie"COL_RED" «•", strTemp, "Kup", "Anuluj");
			}
			else if(IsPlayerInRangeOfPoint(playerid, 3.0, XYZ_TRUCKSALON))//kupowania auta w salonie
			{
				for(new v = GetVehiclePoolSize(); v != -1; v--)
				{
					if(truckshop_db_id[0] == pojazd[v][v_id])
					{
						//TogglePlayerSpectating(playerid, 1);
						new Float:camX, Float:camY;
						GetXYInFrontOfVehicle(v, camX, camY, 20.0);
						gracz[playerid][truckbuy_campos][0] = camX;
						gracz[playerid][truckbuy_campos][1] = camY+10;
						gracz[playerid][truckbuy_campos][2] = pojazd[v][v_Z]+8.0;
						gracz[playerid][truckbuy_camlook][0] = pojazd[v][v_X];
						gracz[playerid][truckbuy_camlook][1] = pojazd[v][v_Y];
						gracz[playerid][truckbuy_camlook][2] = pojazd[v][v_Z];
						SetPlayerCameraLookAt(playerid, gracz[playerid][truckbuy_camlook][0], gracz[playerid][truckbuy_camlook][1], gracz[playerid][truckbuy_camlook][2]);
						SetPlayerCameraPos(playerid, gracz[playerid][truckbuy_campos][0], gracz[playerid][truckbuy_campos][1], gracz[playerid][truckbuy_campos][2]);
						gracz[playerid][truckbuy_status] = 1;
						gracz[playerid][truckbuy_selected] = 0;
						TogglePlayerControllable(playerid, false);
						new specid = truckshop_specid[0];
						if(specid > 0) SalonTruckSelectTDShow(playerid, GetVehicleName(pojazd[v][v_model]), truckshop_price[0], VehicleCapacity(pojazd[v][v_model]), pojazd_spec[specid][vspec_fueltype], pojazd_spec[specid][vspec_tanksize], pojazd_spec[specid][vspec_fuelconsumption], pojazd_spec[specid][vspec_0100], pojazd_spec[specid][vspec_vmax]);
						else SalonTruckSelectTDShow(playerid, GetVehicleName(pojazd[v][v_model]), truckshop_price[0], VehicleCapacity(pojazd[v][v_model]), -1, 0, 0.0, 0.0, 0);
						LeftNotifyShow(playerid, "info", "Witaj w salonie ~g~TRUCK~w~! Wybierz swoj pojazd za pomoca ~y~strzalek~w~ na klawiaturze ~y~(lub A i D)~w~, zakup zatwierdzisz klawiszem ~g~ENTER~w~. Aby anulowac zakup wcisnij ~r~klawisz Y~w~.", LN_GREY, 15);
						break;
					}
				}
			}
		} 
	}
	return 1;
}

Dialog:VEHICLECP(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(GetPlayerVehicleSeat(playerid) != 0) return 1;
	new vehicleid = GetPlayerVehicleID(playerid);
	if(!IsPlayerCanDrive(playerid, vehicleid)) return 1;
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	new strTemp[128];
	if(IsVehicleBike(pojazd[vehicleid][v_model])) 
	{
		if(listitem == 2) listitem = 8;//parkowanie
		else if(listitem == 3) listitem = 9;//zmien rejestracje
		else if(listitem == 4) listitem = 10;//specyfikacja pojazdu
	}
	switch(listitem)
	{
		case 0:
		{
			if(engine) 
			{
				SetVehicleParamsEx(vehicleid, 0, lights, alarm, doors, bonnet, boot, objective);
				format(strTemp, 128, "/do silnik pojazdu %s został zgaszony.", GetVehicleName(pojazd[vehicleid][v_model]));
				PC_EmulateCommand(playerid, strTemp);
				LeftNotifyShow(playerid, "Sukces!", "Silnik pojazdu zostal ~n~~r~zgaszony~w~.", LN_RED);
			}
			else 
			{
				if(gracz[playerid][delay_enable_engine]) return Error(playerid, "Silnik jest już w trakcie uruchamiania.");
				SetTimerEx("DelayEnableEngine", 4000, false, "dd", playerid, vehicleid);
				SetTimerEx("SpeedoTestEffect", 100, false, "dd", playerid, 0);
				gracz[playerid][delay_enable_engine] = true;
				CarHUD_SpeedLight(playerid, true);
				CarHUD_FuelWarning(playerid, true);
				CarHUD_TempWarning(playerid, true);
				CarHUD_DistanceLight(playerid, true);
				CarHUD_SERVICE(playerid, true);
				CarHUD_Battery(playerid, true);
				LeftNotifyShow(playerid, "info", "Trwa ~g~uruchamianie~w~ silnika...", LN_GREY);
			}
		}
		case 1:
		{
			if(lights)
			{ 
				SetVehicleParamsEx(vehicleid, engine, 0, alarm, doors, bonnet, boot, objective);
				LeftNotifyShow(playerid, "Sukces!", "Swiatla ~r~wylaczone~w~.", LN_RED);
				ToggleVehicleNeons(vehicleid, 0);
				new trailerid = GetVehicleTrailer(vehicleid);
				if(trailerid != 0)
				{
					GetVehicleParamsEx(trailerid, engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(trailerid, engine, 0, alarm, doors, bonnet, boot, objective);
				}
				if(pojazd[vehicleid][v_trafficlights]) TrafficLight(vehicleid, 0);
			}
			else
			{
				SetVehicleParamsEx(vehicleid, engine, 1, alarm, doors, bonnet, boot, objective);
				ToggleVehicleNeons(vehicleid, 1);
				new trailerid = GetVehicleTrailer(vehicleid);
				if(trailerid != 0)
				{
					GetVehicleParamsEx(trailerid, engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(trailerid, engine, 1, alarm, doors, bonnet, boot, objective);
				}
				LeftNotifyShow(playerid, "Sukces!", "Swiatla ~g~wlaczone~w~.", LN_GREEN);
			}
		}
		case 2:
		{
			if(pojazd[vehicleid][v_handbrake])
			{
				LeftNotifyShow(playerid, "Sukces!", "Hamulec reczny zostal ~r~zwolniony~w~.", LN_RED);
				Handbrake(vehicleid, 0);
			}
			else
			{
				if(gracz[playerid][opu_speed] == 0)
				{
					if(BattleBlock(playerid)) return Error(playerid, "Na terenie walki jest zakaz używania ręcznego.");
					LeftNotifyShow(playerid, "Sukces!", "Hamulec reczny zostal ~g~zaciagniety~w~.", LN_GREEN);
					Handbrake(vehicleid, 1);
				}
				else
				{
					LeftNotifyShow(playerid, "error!", "Nie mozna przy rozwinietej predkosci aktywowac ~y~hamulec postojowy(reczny)~w~.", LN_RED);
				}
			}
		}
		case 3:
		{
			if(doors)
			{
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, 0, bonnet, boot, objective);
				LeftNotifyShow(playerid, "Sukces!", "Drzwi ~g~otwarte~w~.", LN_GREEN);
			}
			else
			{
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, 1, bonnet, boot, objective);
				LeftNotifyShow(playerid, "Sukces!", "Drzwi ~r~zamkniete~w~.", LN_RED);
			}
			PlayerPlaySound(playerid, 24600, 0, 0, 0);
		}
		case 4:
		{
			if(!IsCarBlinking(vehicleid)) 
			{
				SetCarBlinking(vehicleid, 2);
				SetPVarInt(playerid, "blink-car", vehicleid);
				LeftNotifyShow(playerid, "Sukces!", "Swiatla awaryjne ~g~wlaczone~w~.", LN_GREEN);
			}
			else
			{
				DisableCarBlinking(vehicleid);
				LeftNotifyShow(playerid, "Sukces!", "Swiatla awaryjne ~r~wylaczone~w~.", LN_RED);
			}
		}
		case 5:
		{
			if(bonnet)
			{
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, 0, boot, objective);
				LeftNotifyShow(playerid, "Sukces!", "Maska ~r~zamknieta~w~.", LN_RED);
			}
			else
			{
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, 1, boot, objective);
				LeftNotifyShow(playerid, "Sukces!", "Maska ~g~otwarta~w~.", LN_GREEN);
			}
		}
		case 6:
		{
			if(boot)
			{
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, 0, objective);
				LeftNotifyShow(playerid, "Sukces!", "Bagaznik ~r~zamkniety~w~.", LN_RED);
			}
			else
			{
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, 1, objective);
				LeftNotifyShow(playerid, "Sukces!", "Bagaznik ~g~otwarty~w~.", LN_GREEN);
			}
		}
		case 7:
		{
			new strWindowsMenu[1024];
			format(strWindowsMenu, 1024, ""COL_LIME"•»\t"COL_GREEN"Otwórz"COL_WHITE"/"COL_RED"Zamknij"COL_WHITE" okno kierowcy \t"COL_LIME"«•");
			format(strWindowsMenu, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"Otwórz"COL_WHITE"/"COL_RED"Zamknij "COL_WHITE"okno pasażera: przód\t"COL_LIME"«•", strWindowsMenu);
			format(strWindowsMenu, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"Otwórz"COL_WHITE"/"COL_RED"Zamknij "COL_WHITE"okno pasażera: tył lewe\t"COL_LIME"«•", strWindowsMenu);
			format(strWindowsMenu, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"Otwórz"COL_WHITE"/"COL_RED"Zamknij "COL_WHITE"okno pasażera: tył prawe\t"COL_LIME"«•", strWindowsMenu);
			Dialog_Show(playerid, VEHWINDOWS, DIALOG_STYLE_TABLIST, ""COL_RED"•» "COL_WHITE"Zarządzanie oknami"COL_ORANGE"", strWindowsMenu, "Wybierz", "Anuluj");
		}
		case 8:
		{
			ParkVehicle(playerid, vehicleid);
		}
		case 9:
		{
			if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER || (pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION && gracz[playerid][frakcja_permlvl] != 0) || (pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS && gracz[playerid][firma_permlvl] != 0))
			{
				new strDNumberPlate[1024];
				format(strDNumberPlate, 1024, ""COL_WHITE"Wprowadź w polu poniżej tekst, który ma być wyświetlany na "COL_BLUE"rejestracji pojazdu"COL_WHITE".");
				format(strDNumberPlate, 1024, "%s\n\n{8B8B8B}• maxymymalnie możesz wprowadzić 32 znaki razem z kolorami.", strDNumberPlate);
				format(strDNumberPlate, 1024, "%s\n{8B8B8B}• na rejestracji widać maxymalnie 12 znaków.", strDNumberPlate);
				format(strDNumberPlate, 1024, "%s\n{8B8B8B}• pozostaw puste pole aby przywrócić domyślny tekst.", strDNumberPlate);
				Dialog_Show(playerid, VEHSETPLATE, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_WHITE"Zmiana tekstu na rejestracji"COL_ORANGE"", strDNumberPlate, "Zatwierdz", "Anuluj");
			}
			else Error(playerid, "Brak uprawnień.");
		}
		case 10:
		{
			new specid = GetVehicleSpecID(pojazd[vehicleid][v_model]);
			if(specid > 0)
			{
				new col1 = pojazd[vehicleid][v_color][0];
				new col2 = pojazd[vehicleid][v_color][1];
				new strSpec[1024];
				format(strSpec, 1024, "%s\n"COL_BLUE"Specyfikacja techniczna"COL_WHITE" pojazdu "COL_RED"%s"COL_WHITE":", strSpec, GetVehicleName(pojazd[vehicleid][v_model]));
				if(pojazd_spec[specid][vspec_fueltype] == F_PB) format(strSpec, 512, "%s\n{428FB8}TYP PALIWA:"COL_GREEN" PB", strSpec);
				else if(pojazd_spec[specid][vspec_fueltype] == F_ON) format(strSpec, 512, "%s\n{428FB8}TYP PALIWA:{6D6D6D} ON", strSpec);
				format(strSpec, 1024, "%s\n{6DC5F3}POJEMNOŚĆ ZBIORNIKA:{45A081} %d "COL_WHITE"[litr]", strSpec, pojazd_spec[specid][vspec_tanksize]);
				format(strSpec, 1024, "%s\n{428FB8}SPALANIE:{45A081} %0.1f "COL_WHITE"[litr/100km]", strSpec, pojazd_spec[specid][vspec_fuelconsumption]+0.01);
				format(strSpec, 1024, "%s\n{6DC5F3}PRZYŚPIESZENIE (0-100):{45A081} %0.1f "COL_WHITE"[sekund]", strSpec, pojazd_spec[specid][vspec_0100]+0.01);
				format(strSpec, 1024, "%s\n{428FB8}PRĘDKOŚĆ MAXYMALNA (V-MAX):{45A081} %d "COL_WHITE"[km/h]", strSpec, pojazd_spec[specid][vspec_vmax]);
				format(strSpec, 1024, "%s\n{6DC5F3}KOLORY: {%06x}[kolor1(ID: %d)] {%06x}[kolor2(ID: %d)]", strSpec, VehicleColoursTableRGBA[col1] >>> 8, col1, VehicleColoursTableRGBA[col2] >>> 8, col2);
				MessageGUIEx(playerid, ""COL_RED"•» "COL_WHITE"Specyfikacja techniczna"COL_ORANGE"",  strSpec);
			}
		}
	}
	return 1;
}

Dialog:VEHWINDOWS(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(GetPlayerVehicleSeat(playerid) != 0) return 1;
	new vehicleid = GetPlayerVehicleID(playerid);
	if(!IsPlayerCanDrive(playerid, vehicleid)) return 1;
	new driver, passenger, backleft, backright;
	GetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, backright);
	switch(listitem)
	{
		case 0:
		{
			if(driver)
			{
				SetVehicleParamsCarWindows(vehicleid, 0, passenger, backleft, backright);
				LeftNotifyShow(playerid, "Sukces!", "Szyba kierowcy ~g~otwarta~w~.", LN_GREEN);
			}
			else 
			{
				SetVehicleParamsCarWindows(vehicleid, 1, passenger, backleft, backright);
				LeftNotifyShow(playerid, "Sukces!", "Szyba kierowcy ~r~zamknieta~w~.", LN_RED);
			}
		}
		case 1:
		{
			if(passenger)
			{
				SetVehicleParamsCarWindows(vehicleid, driver, 0, backleft, backright);
				LeftNotifyShow(playerid, "Sukces!", "Szyba pasazer przod ~g~otwarta~w~.", LN_GREEN);
			}
			else 
			{
				SetVehicleParamsCarWindows(vehicleid, driver, 1, backleft, backright);
				LeftNotifyShow(playerid, "Sukces!", "Szyba pasazer przod ~r~zamknieta~w~.", LN_RED);
			}
		}
		case 2:
		{
			if(backleft)
			{
				SetVehicleParamsCarWindows(vehicleid, driver, passenger, 0, backright);
				LeftNotifyShow(playerid, "Sukces!", "Szyba pasazer tyl lewe ~g~otwarta~w~.", LN_GREEN);
			}
			else 
			{
				SetVehicleParamsCarWindows(vehicleid, driver, passenger, 1, backright);
				LeftNotifyShow(playerid, "Sukces!", "Szyba pasazer tyl lewe ~r~zamknieta~w~.", LN_RED);
			}
		}
		case 3:
		{
			if(backright)
			{
				SetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, 0);
				LeftNotifyShow(playerid, "Sukces!", "Szyba pasazer tyl prawe ~g~otwarta~w~.", LN_GREEN);
			}
			else 
			{
				SetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, 1);
				LeftNotifyShow(playerid, "Sukces!", "Szyba pasazer tyl prawe ~r~zamknieta~w~.", LN_RED);
			}
		}
	}
	return 1;
}

Dialog:VEHSETPLATE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(GetPlayerVehicleSeat(playerid) != 0) return 1;
	new vehicleid = GetPlayerVehicleID(playerid);
	if(!IsPlayerCanDrive(playerid, vehicleid)) return 1;
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER || (pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION && gracz[playerid][frakcja_permlvl] != 0) || (pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS && gracz[playerid][firma_permlvl] != 0))
	{
		format(pojazd[vehicleid][v_numberplate], 32, "%s", inputtext);
		mysql_escape_string(pojazd[vehicleid][v_numberplate], pojazd[vehicleid][v_numberplate], 32, g_SQL);
		if(pojazd[vehicleid][v_id] != 0)
		{
			mq_format("UPDATE `pojazdy` SET `numberplate`='%s' WHERE `id`='%d';", pojazd[vehicleid][v_numberplate], pojazd[vehicleid][v_id]);
			mq_send("QUpdateVehPlate");
		}
		new strInfo[100];
		if(strlen(pojazd[vehicleid][v_numberplate]) > 1) 
		{
			SetVehicleNumberPlate(vehicleid, pojazd[vehicleid][v_numberplate]);
			format(strInfo, 100, "Nowy napis na rejestracji: "COL_GREY"%s"COL_WHITE".", pojazd[vehicleid][v_numberplate]);
		}
		else 
		{
			SetVehicleNumberPlate(vehicleid, VEH_REG);
			format(strInfo, 100, "Nowy napis na rejestracji: "COL_GREY"%s"COL_WHITE".", VEH_REG);
		}
		new Float:posPark[4];
		posPark[0] = pojazd[vehicleid][v_X];
		posPark[1] = pojazd[vehicleid][v_Y];
		posPark[2] = pojazd[vehicleid][v_Z];
		posPark[3] = pojazd[vehicleid][v_R];
		GetVehiclePos(vehicleid, pojazd[vehicleid][v_X],  pojazd[vehicleid][v_Y], pojazd[vehicleid][v_Z]);
		GetVehicleZAngle(vehicleid, pojazd[vehicleid][v_R]);
		RespawnVehicle(vehicleid, true);
		pojazd[vehicleid][v_X] = posPark[0];
		pojazd[vehicleid][v_Y] = posPark[1];
		pojazd[vehicleid][v_Z] = posPark[2];
		pojazd[vehicleid][v_R] = posPark[3];
		Info(playerid, strInfo);
		//PutPlayerInVehicle(playerid, vehicleid, 0);
	} 
	else Error(playerid, "Brak uprawnień.");
	return 1;
}

forward DelayEnableEngine(playerid, vehicleid);
public DelayEnableEngine(playerid, vehicleid)
{
	gracz[playerid][delay_enable_engine] = false;
	if(!gracz[playerid][loggedin]) return 1;
	if(IsPlayerInVehicle(playerid, vehicleid))
	{
		new engine, lights, alarm, doors, bonnet, boot, objective;
		new strTemp[128];
		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		if(pojazd[vehicleid][v_paliwo] > 0.0)
		{
			new bool:awaria = false;
			if(IsVehicleWornOut(vehicleid, 6) || IsVehicleWornOut(vehicleid, 4) || IsVehicleWornOut(vehicleid, 7) || IsVehicleWornOut(vehicleid, 3) || IsVehicleWornOut(vehicleid, 5) || IsVehicleWornOut(vehicleid, 8) || IsVehicleWornOut(vehicleid, 10))
			{
				if(random(2))
				{
					awaria = true;
				}
			}
			if(awaria || IsVehicleWornOut(vehicleid, 9))
			{
				LeftNotifyShow(playerid, "Awaria", "Silnik pojazdu ~r~nie zostal uruchomiony~w~. Pojazd prawdopodobnie ulegl awarii.", LN_RED);
			}
			else
			{
				SetVehicleParamsEx(vehicleid, 1, lights, alarm, doors, bonnet, boot, objective);
				format(strTemp, 128, "/do silnik pojazdu %s został uruchomiony.", GetVehicleName(pojazd[vehicleid][v_model]));
				PC_EmulateCommand(playerid, strTemp);
				LeftNotifyShow(playerid, "Sukces!", "Silnik pojazdu zostal ~g~uruchomiony~w~.", LN_GREEN);
				RemoveVehicleComponent(vehicleid, pojazd[vehicleid][v_tune_data][5]);
				AddVehicleComponent(vehicleid, pojazd[vehicleid][v_tune_data][5]);
				pojazd[vehicleid][v_whilenitro] = false;
			}
		}
		else
		{
			SetVehicleParamsEx(vehicleid, 0, lights, alarm, doors, bonnet, boot, objective);
			LeftNotifyShow(playerid, "Paliwo", "Silnik pojazdu ~r~nie zostal uruchomiony~w~. Brak paliwa.", LN_RED);
		}
		CarHUD_FuelWarning(playerid, false);
		CarHUD_TempWarning(playerid, false);
		CarHUD_DistanceLight(playerid, true);
		CarHUD_SERVICE(playerid, false);
		CarHUD_Battery(playerid, false);
		//CarHUD_SetSpeed(playerid, 0);
	}
	return 1;
}

forward SpeedoTestEffect(playerid, step, minus);
public SpeedoTestEffect(playerid, step, minus)
{
	if(gracz[playerid][delay_enable_engine])
	{
		if(!minus)
		{
			if(step < 200) SetTimerEx("SpeedoTestEffect", 100, false, "dd", playerid, step+20);
			else if(step < 250) SetTimerEx("SpeedoTestEffect", 100, false, "dd", playerid, step+10);
			else if(step == 250) SetTimerEx("SpeedoTestEffect", 100, false, "ddd", playerid, step-10, 1);
		}
		else if(step > 0)
		{
			if(step > 200) SetTimerEx("SpeedoTestEffect", 100, false, "ddd", playerid, step-10, 1);
			else if(step <= 200) SetTimerEx("SpeedoTestEffect", 100, false, "ddd", playerid, step-20, 1);
		}
		CarHUD_SetSpeed(playerid, step);
	}
	return 1;
}

stock CarPilotLockUnlockEffect(vehicleid)
{
	if(pojazd[vehicleid][v_cplue]) return 0;
	pojazd[vehicleid][v_cplue] = true;
	SetCarBlinking(vehicleid, 2);
	new Float:vPos[3];
	GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(gracz[p][loggedin])
		{
			if(IsPlayerInRangeOfPoint(p, 20.0, vPos[0], vPos[1], vPos[2]))
			{
				PlayerPlaySound(p, 1147, vPos[0], vPos[1], vPos[2]);
			}
		}
	}
	SetTimerEx("CarPilotLockUnlockEffect_s2", 1200, false, "d", vehicleid);
	return 1;
}

forward CarPilotLockUnlockEffect_s2(vehicleid);
public CarPilotLockUnlockEffect_s2(vehicleid)
{
	pojazd[vehicleid][v_cplue] = false;
	BlinkSystem_DisableBlinks(vehicleid);
	return 1;
}

stock AttachCourierLogoToVehicle(vehicleid, courierid)
{
	if(courierid == 0) return 1;
	if(GetVehicleModel(vehicleid) != 482) return 0;
	switch(courierid)
	{
		case C_DHL:
		{
			//ChangeVehicleColor(vehicleid, 6, 6);
			pojazd[vehicleid][v_object][0] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.910000,-1.064999,0.544999,0.000000,-15.479999,0.000000);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][0], 0, "DHL", 130, "Impact", 100, 0, -10092544, 0, 1);

			pojazd[vehicleid][v_object][1] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][1], vehicleid, -0.915000,-1.094999,0.544999,-180.179885,-195.659881,0.000000);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][1], 0, "DHL", 130, "Impact", 100, 0, -10092544, 0, 1);

			pojazd[vehicleid][v_object][2] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][2], vehicleid, -0.930000,-1.094999,0.475000,-180.179885,-192.959884,0.000000);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][2], 0, "=      =", 130, "Impact", 150, 0, -10092544, 0, 1);

			pojazd[vehicleid][v_object][3] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][3], vehicleid, 0.945000,-1.064999,0.465000,-180.179885,-344.340087,0.000000);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][3], 0, "=      =", 130, "Impact", 150, 0, -10092544, 0, 1);
		}
		case C_DPD:
		{
			pojazd[vehicleid][v_object][0] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.909999,-1.520000,0.529999,0.000000,-14.760002,0.000000);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][0], 0, "DPD", 130, "Impact", 100, 0, -16777216, 0, 1);

			pojazd[vehicleid][v_object][1] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][1], vehicleid, -0.909999,-1.520000,0.544999,0.000000,-14.760002,-180.179885);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][1], 0, "DPD", 130, "Impact", 100, 0, -16777216, 0, 1);

			pojazd[vehicleid][v_object][2] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][2], vehicleid, 0.919999,-0.579999,0.524999,0.000000,-15.839993,0.000000);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][2], 0, "v", 130, "wingdings", 130, 0, -6750208, 0, 1);

			pojazd[vehicleid][v_object][3] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][3], vehicleid, -0.919999,-0.579999,0.534999,0.000000,16.380012,0.000000);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][3], 0, "v", 130, "wingdings", 130, 0, -6750208, 0, 1);
		}
		case C_FEDEX:
		{
			pojazd[vehicleid][v_object][0] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.909999,-1.310000,0.544999,0.000000,-15.479997,-0.000001);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][0], 0, "Fed", 130, "Impact", 120, 0, -13434727, 0, 1);

			pojazd[vehicleid][v_object][1] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][1], vehicleid, -0.909999,-0.870000,0.544999,0.000000,-15.840004,-179.819885);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][1], 0, "Fed", 130, "Impact", 120, 0, -13434727, 0, 1);

			pojazd[vehicleid][v_object][2] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][2], vehicleid, 0.909999,-0.750000,0.544999,0.000000,-15.479997,-0.000001);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][2], 0, "Ex", 130, "Impact", 120, 0, -39424, 0, 1);

			pojazd[vehicleid][v_object][3] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][3], vehicleid, -0.909999,-1.430000,0.544999,0.000000,-15.840004,-179.819885);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][3], 0, "Ex", 130, "Impact", 120, 0, -39424, 0, 1);
		}
		case C_INPOST:
		{
			pojazd[vehicleid][v_object][0] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.909999,-0.375000,0.534999,0.000000,-15.659995,0.000000);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][0], 0, "*", 130, "wingdings", 110, 1, -6715392, 0, 1);

			pojazd[vehicleid][v_object][1] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][1], vehicleid, -0.909999,-0.375000,0.534999,0.000000,-15.659995,-180.179885);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][1], 0, "*", 130, "wingdings", 110, 1, -6715392, 0, 1);

			pojazd[vehicleid][v_object][2] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][2], vehicleid, -0.909999,-1.445000,0.554999,0.000000,-15.659995,-180.179885);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][2], 0, "InPost", 130, "Impact", 110, 0, -16777216, 0, 1);

			pojazd[vehicleid][v_object][3] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][3], vehicleid, 0.909999,-1.445000,0.554999,0.000000,-15.659995,-0.179994);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][3], 0, "InPost", 130, "Impact", 110, 0, -16777216, 0, 1);
		}
		case C_TNT:
		{
			pojazd[vehicleid][v_object][0] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.909999,-1.094999,0.534999,0.000000,-15.659998,0.000000);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][0], 0, "OOO", 130, "Arial", 130, 0, -1, 0, 1);

			pojazd[vehicleid][v_object][1] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][1], vehicleid, -0.909999,-1.094999,0.534999,0.000000,-15.659998,179.999877);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][1], 0, "OOO", 130, "Arial", 130, 0, -1, 0, 1);

			pojazd[vehicleid][v_object][2] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][2], vehicleid, -0.909999,-1.094999,0.544999,0.000000,-15.659998,179.999877);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][2], 0, "T     N     T", 130, "Impact", 75, 1, -1, 0, 1);

			pojazd[vehicleid][v_object][3] = CreateDynamicObject(19477,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][3], vehicleid, 0.909999,-1.094999,0.544999,0.000000,-15.659998,0.179991);
			SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][3], 0, "T     N     T", 130, "Impact", 75, 1, -1, 0, 1);
		}
	}
	return 1;
}

stock GenererateCarSalonCarRotation()
{
	const count_cars = 10;
	new veh_rotation[count_cars];
	for(new x; x < count_cars; x++)
	{
		if(veh_rotation[x] == 0)
		{
			veh_rotation[x] = random(MAX_CARSPEC);
			new rr;
			while(rr < count_cars)
			{
				//printf("while(%d)", rr);
				if((veh_rotation[rr] == veh_rotation[x] || IsVehicleSalonBanned(pojazd_spec[veh_rotation[x]][vspec_model])) && rr != x)
				{
					//new tmp = veh_rotation[x];//DEBUG PART1
					veh_rotation[x] = random(MAX_CARSPEC);
					//printf("%d == %d(%d)", veh_rotation[rr] , tmp, veh_rotation[x]);//DEBUG PART 2
					rr = -1;
				}
				rr++;
			}
		}
	}
	new strTemp[512];
	carshop_buylist = "";//czyszczenie listy aut w salonie do kupienia
	for(new x; x < count_cars; x++)
	{
		new vr = veh_rotation[x];
		new col1, col2;
		col1 = random(255);
		col2 = random(255);
		//printf("vr: %d | did: %d", pojazd_spec[vr][vspec_model], carshop_db_id[x]);
		//printf("UPDATE `pojazdy` SET `model`='%d' WHERE `id`='%d';", pojazd_spec[vr][vspec_model], carshop_db_id[x]);

		mq_format("UPDATE `pojazdy` SET `model`='%d', `color_0`='%d', `color_1`='%d', `przebieg`='0' WHERE `id`='%d';", pojazd_spec[vr][vspec_model], col1, col2, carshop_db_id[x]);
		mq_send("QRotateSalonCars");
		for(new v = GetVehiclePoolSize(); v != -1; v--)
		{
			if(pojazd[v][v_id] == carshop_db_id[x])
			{
				//printf("usuwam vid: %d", v);
				RemoveVehicle(v, false);
				carshop_specid[x] = vr;
				pojazd[v][v_model] = pojazd_spec[vr][vspec_model];
				pojazd[v][v_color][0] = col1;
				pojazd[v][v_color][1] = col2;
				pojazd[v][v_przebieg] = 0;
				pojazd[v][v_przebiegunits] = 0;
				new vid = CreateVehicle(pojazd_spec[vr][vspec_model], pojazd[v][v_X],  pojazd[v][v_Y], pojazd[v][v_Z], pojazd[v][v_R], pojazd[v][v_color][0], pojazd[v][v_color][1], VEH_SINGLERESP_TIME);
				SetVehicleParamsEx(vid, 0, 0, 0, 1, 0, 0, 0);
				SetVehicleNumberPlate(vid, VEH_REG);
				//printf("TWORZE vid: %d", vid);
				carshop_price[x] = CalcVehiclePriceEx(pojazd_spec[vr][vspec_model]);
				format(strTemp, 512, "{%06x}••••••••••••••••••••••••••••••••••••••••••••••••••", VehicleColoursTableRGBA[col1] >>> 8);
				format(strTemp, 512, "%s\n{FFCE00}%d$ ", strTemp, carshop_price[x]);
				format(strTemp, 512, "%s\n{7DFC9C}%s", strTemp, LastTextOtherCol(pojazd_spec[vr][vspec_name], 0xFFFFFFFF));
				if(pojazd_spec[vr][vspec_fueltype] == F_PB) format(strTemp, 512, "%s\n{428FB8}TYP PALIWA:"COL_GREEN" PB", strTemp);
				else if(pojazd_spec[vr][vspec_fueltype] == F_ON) format(strTemp, 512, "%s\n{428FB8}TYP PALIWA:{6D6D6D} ON", strTemp);
				format(strTemp, 512, "%s\n{6DC5F3}POJEMNOŚĆ ZBIORNIKA:{45A081} %d "COL_WHITE"[litr]", strTemp, pojazd_spec[vr][vspec_tanksize]);
				format(strTemp, 512, "%s\n{428FB8}SPALANIE:{45A081} %0.1f "COL_WHITE"[litr/100km]", strTemp, pojazd_spec[vr][vspec_fuelconsumption]+0.01);
				format(strTemp, 512, "%s\n{6DC5F3}PRZYŚPIESZENIE (0-100):{45A081} %0.1f "COL_WHITE"[sekund]", strTemp, pojazd_spec[vr][vspec_0100]+0.01);
				format(strTemp, 512, "%s\n{428FB8}PRĘDKOŚĆ MAXYMALNA (V-MAX):{45A081} %d "COL_WHITE"[km/h]", strTemp, pojazd_spec[vr][vspec_vmax]);
				format(strTemp, 512, "%s\n{%06x}••••••••••••••••••••••••••••••••••••••••••••••••••", strTemp, VehicleColoursTableRGBA[col1] >>> 8);
				UpdateDynamic3DTextLabelText(carshop_3dtext_id[x], -1, strTemp);
				format(carshop_buylist, 1024, "%s\n"COL_LIME"•»\t"COL_GREEN"%s\t{FFCE00}%d$\t"COL_LIME"«•", carshop_buylist, pojazd_spec[vr][vspec_name], carshop_price[x]);
				break;
			}	
		}
	}
	return 1;
}

stock IsVehicleSalonBanned(model)
{
	for(new b; b < sizeof(carshop_bans); b++)
	{
		if(model == carshop_bans[b]) return 1;
	}
	return 0;
}

stock IsVehicleTruckSalonBanned(model)
{
	for(new b; b < sizeof(truckshop_bans); b++)
	{
		if(model == truckshop_bans[b]) return 1;
	}
	return 0;
}

stock CalcVehiclePrice(v_max, Float:v_0100, v_tanksize)
{
	new Float:wynik = 3000.0;
	wynik = wynik+float(v_max)*300.0;
	if(v_max >= 185) wynik = wynik+float(v_max)*100.0;
	wynik = wynik-(v_0100*2000.0);
	if(v_0100 >= 4.0) wynik = wynik-(v_0100*2000.0);
	if(v_0100 <= 2.8) wynik = wynik+(v_0100*2000.0);
	wynik = wynik+float(v_tanksize)*100.0;
	return floatround(wynik);
}

stock CalcVehiclePriceEx(model)
{
	if(IsVehicleTrailer(model))
	{
		new price = 100000;
		switch(model)
		{
			case 435: price = 200000;//naczepa duża
			case 450: price = 130000;//żwirówka
			case 584: price = 210000;//cysterna
			case 591: price = 140000;//naczepa mała
		}
		return price;
	}
	else if(IsVehicleSuperCar(model))
	{
		new price = 1000000;
		switch(model)
		{
			case 402: price = 1600000;//Buffalo
			case 411: price = 4900000;//Infernus
			case 415: price = 2900000;//Cheetah
			case 429: price = 820000;//Banshee
			case 434: price = 790000;//Hotknife
			case 451: price = 3500000;//Turismo
			case 475: price = 210000;//Sabre
			case 477: price = 1700000;//ZR-350
			case 506: price = 2800000;//Super GT
			case 521: price = 410000;//FCR-900
			case 522: price = 770000;//NRG-500
			case 535: price = 175000;//Slamvan
			case 541: price = 2500000;//Bullet
			case 558: price = 170000;//Uranus
			case 559: price = 2100000;//Jester
			case 560: price = 590000;//Sultan
			case 562: price = 750000;//Elegy
			case 565: price = 165000;//Flash
			case 579: price = 200500;//Huntley
			case 587: price = 200000;//Euros
			case 603: price = 900000;//Phoenix
		}
		return price;
	}
	else if(IsVehicleTruck(model) == 1)
	{
		new price = 500000;
		switch(model)
		{
			case 403: price = 230150;//Linerunner
			case 514: price = 450000;//Tanker
			case 515: price = 715550;//Roadtrain
		}
		return price;
	}
	new v_max, Float:v_0100, v_tanksize;
	for(new v; v < MAX_CARSPEC; v++)
	{
		if(pojazd_spec[v][vspec_model] == model)
		{
			v_max = pojazd_spec[v][vspec_vmax];
			v_0100 = pojazd_spec[v][vspec_0100];
			v_tanksize = pojazd_spec[v][vspec_tanksize];
			break;
		}
	}
	new final_price =  CalcVehiclePrice(v_max, v_0100, v_tanksize);
	new v_capacity = VehicleCapacity(model);
	if(v_capacity > 0) final_price +=  v_capacity*8;
	else if(IsVehicleTruck(model) == 1) final_price +=  35000*8;

	if(v_max == 0) return 5000;
	return final_price;
}

stock VehicleCanParkHere(vehicleid, bool: lastPosPark = false)
{
	new Float:vPos[3];
	if(!lastPosPark) GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
	else
	{
		vPos[0] = pojazd[vehicleid][v_X];
		vPos[1] = pojazd[vehicleid][v_Y];
		vPos[2] = pojazd[vehicleid][v_Z];
	}
	if(GetDistanceBetweenPoints(vPos[0], vPos[1], vPos[2], XYZ_AUTOSZROT) < 10.0) return 0;
	if(GetDistanceBetweenPoints(vPos[0], vPos[1], vPos[2], XYZ_PARKINGPOLICYJNY) < 15.0) return 0;
	for(new p; p < sizeof(carshop_parkplace); p++)
	{
		if(GetDistanceBetweenPoints(vPos[0], vPos[1], vPos[2], carshop_parkplace[p][0], carshop_parkplace[p][1], carshop_parkplace[p][2]) < 6.0) return 0;
	}
	for(new p; p < sizeof(truckshop_parkplace); p++)
	{
		if(GetDistanceBetweenPoints(vPos[0], vPos[1], vPos[2], truckshop_parkplace[p][0], truckshop_parkplace[p][1], truckshop_parkplace[p][2]) < 10.0) return 0;
	}
	for(new p; p < sizeof(company); p++)
	{
		if(GetDistanceBetweenPoints(vPos[0], vPos[1], vPos[2], company[p][cny_buyparkX], company[p][cny_buyparkY], company[p][cny_buyparkZ]) < 2.8) return 0;
	}
	return 1;
}

stock GetVehicleFuelType(model)
{
	for(new v; v < MAX_CARSPEC; v++)
	{
		if(pojazd_spec[v][vspec_model] == model) return pojazd_spec[v][vspec_fueltype];
	}
	return 0;
}

stock GetVehicleFuelSize(model)
{
	for(new v; v < MAX_CARSPEC; v++)
	{
		if(pojazd_spec[v][vspec_model] == model) return pojazd_spec[v][vspec_tanksize];
	}
	return 0;
}

stock GetVehicleSpecID(model)
{
	for(new v; v < MAX_CARSPEC; v++)
	{
		if(pojazd_spec[v][vspec_model] == model) return v;
	}
	return 0;
}

Dialog:CARBUY(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new specid = carshop_specid[listitem];
	new strTemp[512];
	if(carshop_price[listitem] <= Money(playerid))
	{
		gui_cache[playerid][0][0] = listitem;
		gui_cache[playerid][1][0] = carshop_price[listitem];
		format(strTemp, 512, ""COL_WHITE"Czy jesteś pewien, że chcesz zakupić pojazd "COL_GREEN"%s "COL_WHITE"za {FFCE00}%d$"COL_WHITE"?\n", pojazd_spec[specid][vspec_name], carshop_price[listitem]);
		format(strTemp, 512, "%s\n"COL_BLUE"Specyfikacja techniczna"COL_WHITE":", strTemp);
		if(pojazd_spec[specid][vspec_fueltype] == F_PB) format(strTemp, 512, "%s\n{428FB8}TYP PALIWA:"COL_GREEN" PB", strTemp);
		else if(pojazd_spec[specid][vspec_fueltype] == F_ON) format(strTemp, 512, "%s\n{428FB8}TYP PALIWA:{6D6D6D} ON", strTemp);
		format(strTemp, 512, "%s\n{6DC5F3}POJEMNOŚĆ ZBIORNIKA:{45A081} %d "COL_WHITE"[litr]", strTemp, pojazd_spec[specid][vspec_tanksize]);
		format(strTemp, 512, "%s\n{428FB8}SPALANIE:{45A081} %0.1f "COL_WHITE"[litr/100km]", strTemp, pojazd_spec[specid][vspec_fuelconsumption]+0.01);
		format(strTemp, 512, "%s\n{6DC5F3}PRZYŚPIESZENIE (0-100):{45A081} %0.1f "COL_WHITE"[sekund]", strTemp, pojazd_spec[specid][vspec_0100]+0.01);
		format(strTemp, 512, "%s\n{428FB8}PRĘDKOŚĆ MAXYMALNA (V-MAX):{45A081} %d "COL_WHITE"[km/h]", strTemp, pojazd_spec[specid][vspec_vmax]);
		Dialog_Show(playerid, CARBUYCONF, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_LIME"ZATWIERDZENIE ZAKUPU"COL_RED" «•", strTemp, "Kup", "Anuluj");
	}
	else Error(playerid, "Niewystarczająca ilość gotówki.");
	return 1;
}

Dialog:CARBUYCONF(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cdbid = gui_cache[playerid][0][0];
	new cena = gui_cache[playerid][1][0];
	if(gui_cache[playerid][1][0] <= Money(playerid))
	{
		for(new v = GetVehiclePoolSize(); v != -1; v--)
		{
			if(pojazd[v][v_id] == carshop_db_id[cdbid])
			{
				new Float:vPos[4];
				SalonGetNextParkPos(vPos[0], vPos[1], vPos[2], vPos[3]);
				mq_format("INSERT INTO `pojazdy` (`model`, `X`, `Y`, `Z`, `R`, `color_0`, `color_1`, `owner_type`, `owner`, `status`) VALUES ('%d', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d', '1');", pojazd[v][v_model], vPos[0], vPos[1], vPos[2], vPos[3], pojazd[v][v_color][0], pojazd[v][v_color][1], VEHICLE_PLAYER, gracz[playerid][UID]);
				new car = CreateVehicle(pojazd[v][v_model], vPos[0], vPos[1], vPos[2], vPos[3], pojazd[v][v_color][0], pojazd[v][v_color][1], VEH_SINGLERESP_TIME);
				for(new pojazd_info:r; r < pojazd_info; r++)
				{
					pojazd[car][r] = 0;
				}
				mq_send("QBuyCar", "d", car);
				SetVehicleParamsEx(car, 0, 0, 0, 0, 0, 0, 0);
				SetVehicleNumberPlate(car, VEH_REG);
				SetVehicleHealth(car, 1000.0);
				TakeMoney(playerid, cena);
				pojazd[car][v_model] = pojazd[v][v_model];

				pojazd[car][v_X] = vPos[0];
				pojazd[car][v_Y] = vPos[1];
				pojazd[car][v_Z] = vPos[2];
				pojazd[car][v_R] = vPos[3];

				pojazd[car][v_color][0] = pojazd[v][v_color][0];
				pojazd[car][v_color][1] = pojazd[v][v_color][1];
				pojazd[car][v_paliwo] = GetVehicleFuelSize(pojazd[car][v_model]);
				pojazd[car][v_owner_type] = VEHICLE_PLAYER;
				pojazd[car][v_owner] = gracz[playerid][UID];
				pojazd[car][v_przebieg] = 0;
				pojazd[car][v_przebiegunits] = 0;
				new strDialog[1024];
				format(strDialog, 1024, ""COL_BLUE"Gratulacje!");
				format(strDialog, 1024, "%s\nZakupiłeś nowy, prywatny pojazd marki "COL_GREEN"%s"COL_WHITE".", strDialog, GetVehicleName(pojazd[v][v_model]));
				format(strDialog, 1024, "%s\nZapłaciłeś: {FFCE00}%d$"COL_WHITE".", strDialog, cena);
				format(strDialog, 1024, "%s\nZostałeś automatycznie przeniesiony do swojego nowego pojazdu"COL_WHITE".", strDialog);
				format(strDialog, 1024, "%s\n"COL_RED"WAŻNE!!! "COL_WHITE"Zaparkuj ("COL_GREEN"/v parkuj"COL_WHITE") swój pojazd w nowym miejscu! W innym\nprzypadku nie będzie on tworzony podczas logowania"COL_WHITE".", strDialog);
				format(strDialog, 1024, "%s\nListę swoich pojazdów znajdziesz pod "COL_GREEN"/v lista"COL_WHITE".", strDialog);
				format(strDialog, 1024, "%s\nMenu pojazdu otworzysz klawiszem "COL_GREEN"2"COL_WHITE".", strDialog);
				format(strDialog, 1024, "%s\n"COL_LIME"Aby uruchomić silnik, wciśnij klawisz "COL_GREEN"Y"COL_LIME".", strDialog);
				format(strDialog, 1024, "%s\n"COL_ORANGE"SZEROKOŚCI :)", strDialog);
				ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_GREEN"Pojazd został zakupiony!"COL_RED" «•", strDialog, "OK", "");
				PutPlayerInVehicle(playerid, car, 0);
				break;
			}
		}
	} else Error(playerid, "Niewystarczająca ilość gotówki.");
	return 1;
}

Dialog:TRUCKBUYCONF(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new tdbid = GetPVarInt(playerid, "truckbuy_buyselect");
	new cena = truckshop_price[tdbid];
	if(cena <= Money(playerid))
	{
		for(new v = GetVehiclePoolSize(); v != -1; v--)
		{
			if(pojazd[v][v_id] == truckshop_db_id[tdbid])
			{
				//per player
				//off wybieralke
				gracz[playerid][truckbuy_status] = 0;
				SetCameraBehindPlayer(playerid);
				TogglePlayerControllable(playerid, true);
				SalonTruckSelectTDHide(playerid);
				//end
				if(GetPVarInt(playerid, "BuyCompanyTrailer") == 0)
				{
					new Float:vPos[4];
					SalonTruckGetNextParkPos(vPos[0], vPos[1], vPos[2], vPos[3]);
					mq_format("INSERT INTO `pojazdy` (`model`, `X`, `Y`, `Z`, `R`, `color_0`, `color_1`, `owner_type`, `owner`, `status`) VALUES ('%d', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d', '1');", pojazd[v][v_model], vPos[0], vPos[1], vPos[2], vPos[3], pojazd[v][v_color][0], pojazd[v][v_color][1], VEHICLE_PLAYER, gracz[playerid][UID]);
					new car = CreateVehicle(pojazd[v][v_model], vPos[0], vPos[1], vPos[2], vPos[3], pojazd[v][v_color][0], pojazd[v][v_color][1], VEH_SINGLERESP_TIME);
					for(new pojazd_info:r; r < pojazd_info; r++)
					{
						pojazd[car][r] = 0;
					}
					mq_send("QBuyCar", "d", car);
					SetVehicleParamsEx(car, 0, 0, 0, 0, 0, 0, 0);
					SetVehicleNumberPlate(car, VEH_REG);
					TakeMoney(playerid, cena);
					pojazd[car][v_model] = pojazd[v][v_model];
	
					pojazd[car][v_X] = vPos[0];
					pojazd[car][v_Y] = vPos[1];
					pojazd[car][v_Z] = vPos[2];
					pojazd[car][v_R] = vPos[3];
	
					pojazd[car][v_color][0] = pojazd[v][v_color][0];
					pojazd[car][v_color][1] = pojazd[v][v_color][1];
					pojazd[car][v_paliwo] = GetVehicleFuelSize(pojazd[car][v_model]);
					pojazd[car][v_owner_type] = VEHICLE_PLAYER;
					pojazd[car][v_owner] = gracz[playerid][UID];
					pojazd[car][v_przebieg] = 0;
					pojazd[car][v_przebiegunits] = 0;
					new strDialog[1024];
					format(strDialog, 1024, ""COL_BLUE"Gratulacje!");
					format(strDialog, 1024, "%s\nZakupiłeś nowy, prywatny pojazd marki "COL_GREEN"%s"COL_WHITE".", strDialog, GetVehicleName(pojazd[v][v_model]));
					format(strDialog, 1024, "%s\nZapłaciłeś: {FFCE00}%d$"COL_WHITE".", strDialog, cena);
					format(strDialog, 1024, "%s\nZostałeś automatycznie przeniesiony do swojego nowego pojazdu"COL_WHITE".", strDialog);
					format(strDialog, 1024, "%s\n"COL_RED"WAŻNE!!! "COL_WHITE"Zaparkuj ("COL_GREEN"/v parkuj"COL_WHITE") swój pojazd w nowym miejscu! W innym\nprzypadku nie będzie on tworzony podczas logowania"COL_WHITE".", strDialog);
					format(strDialog, 1024, "%s\nListę swoich pojazdów znajdziesz pod "COL_GREEN"/v lista"COL_WHITE".", strDialog);
					format(strDialog, 1024, "%s\nMenu pojazdu otworzysz klawiszem "COL_GREEN"2"COL_WHITE".", strDialog);
					format(strDialog, 1024, "%s\n"COL_LIME"Aby uruchomić silnik, wciśnij klawisz "COL_GREEN"Y"COL_LIME".", strDialog);
					format(strDialog, 1024, "%s\n"COL_ORANGE"SZEROKOŚCI :)", strDialog);
					ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_GREEN"Pojazd został zakupiony!"COL_RED" «•", strDialog, "OK", "");
					PutPlayerInVehicle(playerid, car, 0);
				}
				else//kupowanie naczep dla firm
				{
					new cid = GetPVarInt(playerid, "BuyCompanyTrailer");
					new Float:vPos[4];
					new strDialog[1024];
					vPos[0] = company[cid][cny_buyparkX];
					vPos[1] = company[cid][cny_buyparkY];
					vPos[2] = company[cid][cny_buyparkZ];
					vPos[3] = company[cid][cny_buyparkR];
					new IAVIR = IsAnyVehicleInRange(2.5, vPos[0], vPos[1], vPos[2]);
					if(IAVIR != -1)
					{
						format(strDialog, 1024, ""COL_RED"Nie możesz zakupić pojazdu, ponieważ Twoje miejsce na zakupione pojazdy jest zajęte!");
						format(strDialog, 1024, "%s\n"COL_WHITE"Na terenie Twojej firmy znajduje się specjalne miejsce parkingowe na zakupione pojazdy z salonu.", strDialog);
						format(strDialog, 1024, "%s\n"COL_WHITE"Skrypt wykrył, że obecnie to miejsce jest zajęte przez pojazd: "COL_LIME"%s"COL_WHITE".", strDialog, GetVehicleName(pojazd[IAVIR][v_model]));
						format(strDialog, 1024, "%s\n"COL_ORANGE"Przeparkuj pojazd na inne miejsce parkingowe i spróbuj ponownie zakupić pojazd w salonie.", strDialog);
						ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_RED"Wystąpił błąd!"COL_RED" «•", strDialog, "OK", "");
						return 1;
					}
					mq_format("INSERT INTO `pojazdy` (`model`, `X`, `Y`, `Z`, `R`, `color_0`, `color_1`, `owner_type`, `owner`, `status`) VALUES ('%d', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d', '1');", pojazd[v][v_model], vPos[0], vPos[1], vPos[2], vPos[3], pojazd[v][v_color][0], pojazd[v][v_color][1], VEHICLE_BUSINESS, GetPVarInt(playerid, "BuyCompanyTrailer"));
					new car = CreateVehicle(pojazd[v][v_model], vPos[0], vPos[1], vPos[2], vPos[3], pojazd[v][v_color][0], pojazd[v][v_color][1], VEH_SINGLERESP_TIME);
					for(new pojazd_info:r; r < pojazd_info; r++)
					{
						pojazd[car][r] = 0;
					}
					mq_send("QBuyCar", "d", car);
					SetVehicleParamsEx(car, 0, 0, 0, 0, 0, 0, 0);
					SetVehicleNumberPlate(car, VEH_REG);
					TakeMoney(playerid, cena);
					pojazd[car][v_model] = pojazd[v][v_model];

					pojazd[car][v_X] = vPos[0];
					pojazd[car][v_Y] = vPos[1];
					pojazd[car][v_Z] = vPos[2];
					pojazd[car][v_R] = vPos[3];
/*
					pojazd[car][v_idle_X] = pojazd[car][v_X];
					pojazd[car][v_idle_Y] = pojazd[car][v_Y];
					pojazd[car][v_idle_Z] = pojazd[car][v_Z];
					pojazd[car][v_idle_R] = pojazd[car][v_R];
*/
					pojazd[car][v_color][0] = pojazd[v][v_color][0];
					pojazd[car][v_color][1] = pojazd[v][v_color][1];
					pojazd[car][v_paliwo] = GetVehicleFuelSize(pojazd[car][v_model]);//??????niech bedzie...
					pojazd[car][v_owner_type] = VEHICLE_BUSINESS;
					pojazd[car][v_owner] = cid;
					pojazd[car][v_przebieg] = 0;
					pojazd[car][v_przebiegunits] = 0;
					format(strDialog, 1024, ""COL_BLUE"Gratulacje!");
					format(strDialog, 1024, "%s\nZakupiłeś "COL_GREEN"%s"COL_WHITE".", strDialog, GetVehicleName(pojazd[v][v_model]));
					format(strDialog, 1024, "%s\nZapłaciłeś: {FFCE00}%d$"COL_WHITE".", strDialog, cena);
					format(strDialog, 1024, "%s\n"COL_RED"UWAGA!"COL_ORANGE" Naczepa znajduje się na specjalnym miejscu parkingowym znajdującym się na terenie Twojej firmy.", strDialog);
					format(strDialog, 1024, "%s\n"COL_ORANGE"Przeparkuj ją z tego miejsca parkingowego. Aby to zrobić, użyj trucka i komendy "COL_BLUE"/v parkuj"COL_ORANGE".", strDialog);
					format(strDialog, 1024, "%s\n"COL_YELLOW"POWODZENIA :)", strDialog);
					ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_GREEN"Pojazd został zakupiony!"COL_RED" «•", strDialog, "OK", "");
				}
				break;
			}
		}
	} else Error(playerid, "Niewystarczająca ilość gotówki.");
	return 1;
}

forward QBuyCar(cid);
public QBuyCar(cid)
{
	pojazd[cid][v_id] = cache_insert_id();
	mq_format("UPDATE `pojazdy` SET `przebieg`='%d', `przebiegunits`='%d', `paliwo`='%f' WHERE `id`='%d';", pojazd[cid][v_przebieg], floatround(pojazd[cid][v_przebiegunits]), pojazd[cid][v_paliwo], pojazd[cid][v_id]);
	mq_send("QUpdateVehicle");
	return 1;
}

stock SalonGetNextParkPos(&Float:pX, &Float:pY, &Float:pZ, &Float:pR)
{
	pX = carshop_parkplace[carshop_park_queue][0];
	pY = carshop_parkplace[carshop_park_queue][1];
	pZ = carshop_parkplace[carshop_park_queue][2];
	pR = carshop_parkplace[carshop_park_queue][3];
	carshop_park_queue++;
	if(carshop_park_queue == sizeof(carshop_parkplace)) carshop_park_queue = 0; 
	return 1;
}

stock SalonTruckGetNextParkPos(&Float:pX, &Float:pY, &Float:pZ, &Float:pR)
{
	pX = truckshop_parkplace[truckshop_park_queue][0];
	pY = truckshop_parkplace[truckshop_park_queue][1];
	pZ = truckshop_parkplace[truckshop_park_queue][2];
	pR = truckshop_parkplace[truckshop_park_queue][3];
	truckshop_park_queue++;
	if(truckshop_park_queue == sizeof(truckshop_parkplace)) truckshop_park_queue = 0; 
	return 1;
}

stock ParkVehicle(playerid, vehicleid)
{
	//if(pojazd[vehicleid][v_owner_type] != VEHICLE_PLAYER) return Error(playerid, "Tylko pojazdy prywatne można zaparkować. ");
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER || pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)
	{
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)
		{
			if(gracz[playerid][firma_permlvl] == 1 || gracz[playerid][firma_permlvl] == 2)
			{
				new Float:vPos[3];
				GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
				if(PosRangeOfCompany(pojazd[vehicleid][v_owner], vPos[0], vPos[1], vPos[2]) == 0) return Error(playerid, "Pojazd firmowy możesz zaparkować tylko na terenie firmy.");
			}
			else return Error(playerid, "Nie masz uprawnień do przeparkowania pojazdu firmowego.");
		}
		if(VehicleCanParkHere(vehicleid))
		{
			GetVehiclePos(vehicleid, pojazd[vehicleid][v_X], pojazd[vehicleid][v_Y], pojazd[vehicleid][v_Z]);
			GetVehicleZAngle(vehicleid, pojazd[vehicleid][v_R]);
			
			mq_format("UPDATE `pojazdy` SET `X`='%f', `Y`='%f', `Z`='%f', `R`='%f' WHERE `id`='%d';", pojazd[vehicleid][v_X], pojazd[vehicleid][v_Y], pojazd[vehicleid][v_Z], pojazd[vehicleid][v_R], pojazd[vehicleid][v_id]);
			mq_send("QUpdateVehiclePos");
			SetPVarInt(playerid, "TrailerParkOK", 1);
			if(IsVehicleTrailer(pojazd[vehicleid][v_model])) 
			{
				RespawnVehicle(vehicleid, true);
				LeftNotifyShow(playerid, "Sukces!", "Naczepa ~g~zaparkowana~w~.", LN_GREEN);
			}
			else LeftNotifyShow(playerid, "Sukces!", "Pojazd ~g~zaparkowany~w~.", LN_GREEN);
		} 
		else LeftNotifyShow(playerid, "Zakaz parkowania", "W tym miejscu obowiazuje ~r~zakaz parkowania~w~.", LN_RED);
	}
	else Error(playerid, "Tego pojazdu nie możesz zaparkować. ");
	return 1;
}

stock PlayerAllCarsCount(playerid)
{
	mq_format("SELECT `owner` FROM `pojazdy` WHERE `owner_type`='%d' AND `owner`='%d';", VEHICLE_PLAYER, gracz[playerid][UID]);
	new Cache:privcarquery = mysql_query(g_SQL, mQuery);
	new wynik = cache_get_row_count_ex();
	cache_delete(privcarquery);
	return wynik;
}

stock PlayerCreatedCarsCount(playerid)
{
	new wynik;
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		if(pojazd[v][v_owner_type] == VEHICLE_PLAYER && pojazd[v][v_owner] == gracz[playerid][UID]) wynik++;
	}
	return wynik;
}

task Process_Radio(playerid)
{
	if(GetPlayerVehicleSeat(playerid) == 0)
	{
		new strTemp[20];
		Radio_HighlightButton(playerid, gracz[playerid][radio_displaystep]);
		switch(gracz[playerid][radio_displaystep])
		{
			case 0..3:
			{
				new station = gracz[playerid][radio_laststation];
				if(station == -1) Radio_Text(playerid, "NIESTANDARDOWE");
				else Radio_Text(playerid, radio_stations[station][rs_title]);
				gracz[playerid][radio_displaystep]++;
				Radio_HighlightButton(playerid, 1);
			}
			case 4..13:
			{
				if(gracz[playerid][radio_displaystep] == 8 || gracz[playerid][radio_displaystep] == 10 || gracz[playerid][radio_displaystep] == 12) format(strTemp, 20, "LOKALNIE: %02d:%02d", serwer[time_hour], serwer[time_minute]);
				else format(strTemp, 20, "GODZINA: %02d %02d", serwer[time_hour], serwer[time_minute]);
				Radio_Text(playerid, strTemp);
				gracz[playerid][radio_displaystep]++;
				Radio_HighlightButton(playerid, 3);
			}
			case 14..20:
			{
				new day, month, year;
				getdate(year, month, day);
				switch(gracz[playerid][radio_displaystep])
				{
					case 14..16: format(strTemp, 20, "%d %s", day, GetMonthNameA(month));
					case 17..18: format(strTemp, 20, "%s", GetWeekDay(day, month, year));
					default: format(strTemp, 20, "%02d.%02d.%dr", day, month, year);
				}
				Radio_Text(playerid, strTemp);
				gracz[playerid][radio_displaystep]++;
				Radio_HighlightButton(playerid, 4);
			}
			case 21..23:
			{
				new vehicleid = gracz[playerid][opu_vehicleid];
				new model = GetVehicleModel(vehicleid);
				new Float:ileprzejade = 100*pojazd[vehicleid][v_paliwo]/pojazd_spec[GetVehicleSpecID(model)][vspec_fuelconsumption]; 
				format(strTemp, 20, "PALIWA NA: %dKM", floatround(ileprzejade));
				Radio_Text(playerid, strTemp);
				gracz[playerid][radio_displaystep]++;
				Radio_HighlightButton(playerid, 5);
			}
			case 24..27:
			{
				GetPlayer2DZone(playerid, strTemp, 20);
				Radio_Text(playerid, strTemp);
				gracz[playerid][radio_displaystep]++;
				Radio_HighlightButton(playerid, 6);
			}
			case 28..29:
			{
				Radio_Text(playerid, "WCISNIJ KLAWISZ N");
				gracz[playerid][radio_displaystep]++;
				Radio_HighlightButton(playerid, 7);
			}
			default:
			{
				Radio_Text(playerid, "ABY ZMIENIC STACJE");
				gracz[playerid][radio_displaystep]++;
				Radio_HighlightButton(playerid, 8);
				if(gracz[playerid][radio_displaystep] >= 32) gracz[playerid][radio_displaystep] = 0;
			}
		}
	}
	return 1;
}

CMD:radio(playerid)
{
	new radioList[3072];
	format(radioList, 3072, "Lp.\tNazwa stacji");
	format(radioList, 3072, "%s\n-\t"COL_RED"••• WYŁĄCZ RADIO •••", radioList);
	if(gracz[playerid][radio_laststation] == -1) format(radioList, 3072, "%s\n»\t{00FF00}••• Niestandardowa stacja radiowa •••", radioList);
	else format(radioList, 3072, "%s\n-\t{00FF00}••• Niestandardowa stacja radiowa •••", radioList);
	for(new r; r < sizeof(radio_stations); r++)
	{
		if(gracz[playerid][radio_laststation] == r) format(radioList, 3072, "%s\n{%06x}%d\t{%06x}» %s", radioList, PlayerColors[r] >>> 8, r, PlayerColors[r] >>> 8, radio_stations[r][rs_title]);
		else format(radioList, 3072, "%s\n%d\t{%06x}%s", radioList, r, PlayerColors[r] >>> 8, radio_stations[r][rs_title]);
	}
	Dialog_Show(playerid, RADIOCAR, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_GREEN"Stacje radiowe"COL_RED" «•", radioList, "Wybierz", "Anuluj");
	return 1;
}

Dialog:RADIOCAR(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	
	switch(listitem)
	{
		case 0: 
		{
			StopAudioStreamForPlayer(playerid);
			SendClientMessage(playerid, 0xFF0000FF, "•••  Radio zostało wyłączone. •••");
			mq_format("UPDATE `Konta` SET `last_radio`='0' WHERE `id`='%d';", gracz[playerid][UID]);
			format(gracz[playerid][last_radio], 128, "0");
			mq_send("QUpdateLastRadio");
		}
		case 1:
		{
			Dialog_Show(playerid, CUSTOMRADIO, DIALOG_STYLE_TABLIST, ""COL_RED"•» "COL_GREEN"Niestandardowa stacja radiowa"COL_RED" «•", "»\t{00FF00}Odtwórz\t«\n•\t{FF0000}Konfiguruj\t•", "Wybierz", "Anuluj");
		}
		default:
		{
			StopAudioStreamForPlayer(playerid);
			gracz[playerid][radio_laststation] = listitem-2;
			SendClientMessageEx(playerid, 0xFF0000FF, "••• "COL_EASY"Wybrano stacje: {%06x}%s "COL_RED"•••", PlayerColors[gracz[playerid][radio_laststation]] >>> 8, radio_stations[gracz[playerid][radio_laststation]][rs_title]);
			PlayAudioStreamForPlayer(playerid, radio_stations[gracz[playerid][radio_laststation]][rs_url]);
			new radio_link_escape[128];
			format(radio_link_escape, 128, radio_stations[gracz[playerid][radio_laststation]][rs_url]);
			mysql_escape_string(radio_link_escape, radio_link_escape);
			mq_format("UPDATE `Konta` SET `last_radio`='%s' WHERE `id`='%d';", radio_link_escape, gracz[playerid][UID]);
			mq_send("QUpdateLastRadio");
			format(gracz[playerid][last_radio], 128, "%s", radio_link_escape);
			gracz[playerid][radio_displaystep] = 0;
			Process_Radio(playerid);
		}
	}
	return 1;
}

Dialog:CUSTOMRADIO(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0://normalne (wywoływane przez użytkownika)
		{
			if(strlen(gracz[playerid][custom_radio]) > 3)
			{
				PlayAudioStreamForPlayer(playerid, gracz[playerid][custom_radio]);
				SendClientMessageEx(playerid, 0xFF0000FF, "••• {00FF00} Niestandardowy strumień audio: {E35205}%s "COL_RED"•••",  gracz[playerid][custom_radio]);
				gracz[playerid][radio_laststation] = -1;
				gracz[playerid][radio_displaystep] = 0;
				Process_Radio(playerid);

				new radio_link_escape[128];
				format(radio_link_escape, 128, gracz[playerid][custom_radio]);
				mysql_escape_string(radio_link_escape, radio_link_escape);
				mq_format("UPDATE `Konta` SET `last_radio`='%s' WHERE `id`='%d';", radio_link_escape, gracz[playerid][UID]);
				format(gracz[playerid][last_radio], 128, "%s", radio_link_escape);
				mq_send("QUpdateLastRadio");
			} 
			else Error(playerid, "Niestandardowy strumień audio jest nieskonfigurowany.");
		}
		case 1:
		{
			new strHelp[2048];
			if(strlen(gracz[playerid][custom_radio]) > 3)
			{
				strcat(strHelp, "{FFFFFF}Aktualnie jest ustawiony następujący strumień:\n{E35205}");
				strcat(strHelp, gracz[playerid][custom_radio]);
				strcat(strHelp, "\n\n{FFFFFF}W tym miejscu możesz skonfigurować swoją {00FF00}niestandardową stację radiową{FFFFFF}.\n");
			} else strcat(strHelp, "{FFFFFF}W tym miejscu możesz skonfigurować swoją {00FF00}niestandardową stację radiową{FFFFFF}.\n");
			
			strcat(strHelp, "Cały proces polega na podaniu {FF0000}bezpośredniego adresu{FFFFFF} do strumienia audio.\n");
			strcat(strHelp, "Obsługiwane formaty to: {E35205}.mp3{FFFFFF}, {E35205}.pls {FFFFFF}i {E35205}.ogg{FFFFFF}. W niektórych przypadkach działa także podanie {FF0000}bezpośredniego adresu{FFFFFF} i portu do {2DCCD3}SHOUTcast DNAS{FFFFFF}.\n\n");
			strcat(strHelp, "{008F7C}Przykłady:\n");
			strcat(strHelp, "{FFFFFF}Strumień radia ZET (adres:port {2DCCD3}SHOUTcast DNAS{FFFFFF}): {2DCCD3}http://zet-net-01.cdn.eurozet.pl:8400\n");
			strcat(strHelp, "{FFFFFF}Strumień radia Evropa 2 (plik {E35205}.mp3{FFFFFF}): {E35205}http://icecast3.play.cz/evropa2-128.mp3\n\n");
			strcat(strHelp, "{8B8B8B}• pamiętaj, że możesz użyć CTRL+V w celu wklejenia adresu\n");
			strcat(strHelp, "{8B8B8B}• pozostaw pole puste i zatwierdź aby wyłączyć tą usługę (nie będzie brana podczas szybkiej zmiany stacji za pomocą klawisza N)\n");
			strcat(strHelp, "{8B8B8B}• adres nie może być dłuższy niż 64 znaki\n");
			strcat(strHelp, "{FFFFFF}Podaj {FF0000}bezpośredni adres{FFFFFF} do strumienia audio:\n");
			Dialog_Show(playerid, CUSTOMRADIOSTREAM, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_GREEN"Niestandardowa stacja radiowa - Konfiguracja"COL_RED" «•", strHelp, "Ustaw", "Anuluj");
		}
		case 3://dla klawisza N - bez info na czacie (wywoływane przez skrypt)
		{
			if(strlen(gracz[playerid][custom_radio]) > 3)
			{
				PlayAudioStreamForPlayer(playerid, gracz[playerid][custom_radio]);
				gracz[playerid][radio_laststation] = -1;
				gracz[playerid][radio_displaystep] = 0;
				Process_Radio(playerid);
			} else Error(playerid, "Niestandardowy strumień audio jest nieskonfigurowany.");
		}
	}
	return 1;
}

Dialog:CUSTOMRADIOSTREAM(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	mysql_escape_string(inputtext, gracz[playerid][custom_radio], 64, g_SQL);
	mq_format("UPDATE `Konta` SET `custom_radio`='%s' WHERE `id`='%d';", gracz[playerid][custom_radio], gracz[playerid][UID]);
	mq_send("QUpdateCustomRadio");
	if(strlen(inputtext) > 3)
	{
		new strQuestion[256];
		format(strQuestion, 256, "{FFFFFF}Adres do strumienia audio to:{E35205} %s", gracz[playerid][custom_radio]);
		format(strQuestion, 256, "%s\n{FFFFFF}Konfiguracja została {00FF00}zapisana{FFFFFF}.", strQuestion);
		format(strQuestion, 256, "%s\n{FF0000}Czy chcesz przetestować(odtworzyć) strumień?", strQuestion);
		Dialog_Show(playerid, CUSTOMRADIOTEST, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_GREEN"Niestandardowa stacja radiowa"COL_RED" «•", strQuestion, "Tak", "Nie");
	}
	else ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_GREEN"Niestandardowa stacja radiowa"COL_RED" «•", "{FF0000}Wyłączono usługę niestandardowej stacji radiowej.", "OK", "");
	return 1;
}

Dialog:CUSTOMRADIOTEST(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	dialog_CUSTOMRADIO(playerid, true, 0, "null");
	return 1;
}

stock TrafficLight(vehicleid, status)
{
	new model = GetVehicleModel(vehicleid);
	new id = model-400;
	if(BlinkOffset[id][bX] != 0.0)
	{
		pojazd[vehicleid][v_trafficlights] = status;
		if(!status)
		{
			if(pojazd[vehicleid][v_object][4] != 0) DestroyDynamicObject(pojazd[vehicleid][v_object][4]), pojazd[vehicleid][v_object][4] = 0;
			if(pojazd[vehicleid][v_object][5] != 0) DestroyDynamicObject(pojazd[vehicleid][v_object][5]), pojazd[vehicleid][v_object][5] = 0;
		}
		else
		{
			//515, 514, 455, 403, 406, 407
			new light_type = 19281;
			if(model == 515 || model == 514 || model == 455 || model == 403 || model == 406 || model == 407) light_type = 19295;
			if(pojazd[vehicleid][v_object][4] == 0)//19295(big), 19281(small)
			{
				pojazd[vehicleid][v_object][4] = CreateDynamicObject(light_type, 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][4], vehicleid, BlinkOffset[id][bX]+0.1,BlinkOffset[id][bY],BlinkOffset[id][bZ]+0.1, 0.0, 0.0, 0.0);//lewy
			}
			if(pojazd[vehicleid][v_object][5] == 0)
			{
				pojazd[vehicleid][v_object][5] = CreateDynamicObject(light_type, 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][5], vehicleid, -BlinkOffset[id][bX]-0.1,BlinkOffset[id][bY],BlinkOffset[id][bZ]+0.1, 0.0, 0.0, 0.0);//prawy
			}
		}
	}
	return 1;
}

stock HasTrafficLight(model)
{
	new id = model-400;
	if(BlinkOffset[id][bX] != 0.0) return 1;
	return 0;
}


stock Init_FuelStation()
{
	mq_format("SELECT * FROM `fuel_stations`;");
	mq_send("LoadFuelStations");
	return 1;
}

forward LoadFuelStations();
public LoadFuelStations()
{
	mq_getdata();
	new i;
	new strTemp[512];
	if(rekordy)
	{
		while(i < rekordy && i < MAX_FUELSTATIONS)
		{
			cache_get_value_name_int(i, "id", 			fuel_stations[i][fs_id]);
			cache_get_value_name_int(i, "concern", 			fuel_stations[i][fs_concern]);
			cache_get_value_name_float(i, "dX", 			fuel_stations[i][fs_dX]);
			cache_get_value_name_float(i, "dY", 			fuel_stations[i][fs_dY]);
			cache_get_value_name_float(i, "dZ", 			fuel_stations[i][fs_dZ]);
			cache_get_value_name_float(i, "pX", 			fuel_stations[i][fs_pX]);
			cache_get_value_name_float(i, "pY", 			fuel_stations[i][fs_pY]);
			cache_get_value_name_float(i, "pZ", 			fuel_stations[i][fs_pZ]);
			fuel_stations[i][fs_dLabel] = CreateDynamic3DTextLabel("« "COL_BLUE"DYSTRYBUTOR "COL_GREEN"»\n"COL_RED"• "COL_WHITE"Zgaś "COL_GREEN"silnik "COL_RED"(Y)"COL_WHITE" aby "COL_GREEN"rozpocząć"COL_WHITE" tankowanie. "COL_RED"•\n"COL_RED"• "COL_WHITE"Uruchom "COL_GREEN"silnik "COL_RED"(Y)"COL_WHITE" aby "COL_RED"zakończyć"COL_WHITE" tankowanie. "COL_RED"•", 0x009933FF, fuel_stations[i][fs_dX], fuel_stations[i][fs_dY], fuel_stations[i][fs_dZ], 35.0);
			format(strTemp, 512, "« "COL_RED"%s "COL_GREEN"»", GetFuelStationName(fuel_stations[i][fs_concern]));
			format(strTemp, 512, "%s\n"COL_WHITE"BENZYNA ({19BD00}PB"COL_WHITE"):"COL_LIME" %d.00"COL_RED"$", strTemp, fuel_station_price[fuel_stations[i][fs_concern]][F_PB]);
			format(strTemp, 512, "%s\n"COL_WHITE"OLEJ NAPĘDOWY ({7A7A7A}ON"COL_WHITE"):"COL_LIME" %d.00"COL_RED"$", strTemp, fuel_station_price[fuel_stations[i][fs_concern]][F_ON]);
			//format(strTemp, 512, "%s\n"COL_WHITE"GAZ ({008CF4}LPG"COL_WHITE"):"COL_LIME" %d.00"COL_RED"$", strTemp, fuel_station_price[fuel_stations[i][fs_concern]][F_LPG]);
			fuel_stations[i][fs_pLabel] = CreateDynamic3DTextLabel(strTemp, 0x009933FF, fuel_stations[i][fs_pX], fuel_stations[i][fs_pY], fuel_stations[i][fs_pZ], 100.0);
			fuel_stations[i][fs_pickup] = CreateDynamicPickup(1650, 1, fuel_stations[i][fs_dX], fuel_stations[i][fs_dY], fuel_stations[i][fs_dZ]);
			//CreateDynamicMapIcon(fuel_stations[i][fs_dX], fuel_stations[i][fs_dY], fuel_stations[i][fs_dZ], 6, 0, .streamdistance = 9999.0, .style = MAPICON_GLOBAL);
			i++;
		}
		printf("[LOAD] Zaladowano %d stacji paliw.", i);
	}
	return 1;
}

task Process_FuelStations()
{
	for(new s; s < MAX_FUELSTATIONS; s++)
	{
		if(fuel_stations[s][fs_id] == 0) continue;
		if(attack[att_stationid] == s && attack[att_status] == 3)
		{
			UpdateDynamic3DTextLabelText(fuel_stations[s][fs_dLabel], 0x00000020, "[NAPAD]");
			UpdateDynamic3DTextLabelText(fuel_stations[s][fs_pLabel], 0x00000020, "[NAPAD]");
		}
		else
		{
			new strTemp[512];
			format(strTemp, 512, "« "COL_RED"%s "COL_GREEN"»", GetFuelStationName(fuel_stations[s][fs_concern]));
			format(strTemp, 512, "%s\n"COL_WHITE"BENZYNA ({19BD00}PB"COL_WHITE"):"COL_LIME" %d.00"COL_RED"$", strTemp, fuel_station_price[fuel_stations[s][fs_concern]][F_PB]);
			format(strTemp, 512, "%s\n"COL_WHITE"OLEJ NAPĘDOWY ({7A7A7A}ON"COL_WHITE"):"COL_LIME" %d.00"COL_RED"$", strTemp, fuel_station_price[fuel_stations[s][fs_concern]][F_ON]);
			UpdateDynamic3DTextLabelText(fuel_stations[s][fs_pLabel], 0x009933FF, strTemp);
			UpdateDynamic3DTextLabelText(fuel_stations[s][fs_dLabel], 0x009933FF, "« "COL_BLUE"DYSTRYBUTOR "COL_GREEN"»\n"COL_RED"• "COL_WHITE"Zgaś "COL_GREEN"silnik "COL_RED"(Y)"COL_WHITE" aby "COL_GREEN"rozpocząć"COL_WHITE" tankowanie. "COL_RED"•\n"COL_RED"• "COL_WHITE"Uruchom "COL_GREEN"silnik "COL_RED"(Y)"COL_WHITE" aby "COL_RED"zakończyć"COL_WHITE" tankowanie. "COL_RED"•");
		}
	}
	return 1;
}

stock GetFuelStationName(concernid)
{
	new wynik[32];
	switch(concernid)
	{
		case STATION_CPN: wynik = "CPN";
		case STATION_ORLEN: wynik = "ORLEN";
		case STATION_SHELL: wynik = "SHELL";
		case STATION_BP: wynik = "BP";
		case STATION_LOTOS: wynik = "LOTOS";
		case STATION_MOYA: wynik = "Moya";
		case STATION_CIRCLEK: wynik = "Circle K";
	}
	return wynik;
}

//*****************************************************************************************************GPS SYSTEM
task Process_GPS(playerid)
{
	//new Float:pPos[3];
	if(!gracz[playerid][gps_enabled]) return 1;
	if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return rpc_GangZoneDestroyAll(playerid);
	//if(!gracz[playerid][gps_refreshtrack]) return 1;
	if(gracz[playerid][gps_Calculating] == 1) return 1;
	if(IsPlayerInRangeOfPoint(playerid, 40.0, gracz[playerid][gps_tstart_X], gracz[playerid][gps_tstart_Y], gracz[playerid][gps_tstart_Z])) return 1;
	//if(node == gracz[playerid][gps_Destination]) return 1;
	GetPlayerPos(playerid, gracz[playerid][gps_tstart_X], gracz[playerid][gps_tstart_Y], gracz[playerid][gps_tstart_Z]);
	RGPS_CalculatePath(gracz[playerid][gps_tstart_X], gracz[playerid][gps_tstart_Y], gracz[playerid][gps_tstart_Z], gracz[playerid][gps_dest_X], gracz[playerid][gps_dest_Y], gracz[playerid][gps_dest_Z], playerid, 1);
	gracz[playerid][gps_Calculating] = 1; 
	gracz[playerid][gps_refreshtrack] = false;
	return 1;
}

stock StopRouteGPS(playerid)
{
	if(!gracz[playerid][gps_enabled]) return 0;
	gracz[playerid][gps_Calculating] = 0;
	gracz[playerid][gps_enabled] = false;
	gracz[playerid][gps_autooff] = false;
	rpc_GangZoneDestroyAll(playerid);
	CarHUD_DistanceGPS(playerid, 0.0);
	return 1;
}


/*public OnPlayerClosestNodeIDChange(playerid, old_NodeID, new_NodeID)
{
	if(old_NodeID != new_NodeID && gracz[playerid][gps_enabled]) gracz[playerid][gps_refreshtrack] = true;
	return 1;
}*/


stock StartRouteGPS(playerid, Float:fX, Float:fY, Float:fZ, bool:auto_off = false)
{
	if(gracz[playerid][gps_Calculating] == 0)
	{
		GetPlayerPos(playerid, gracz[playerid][gps_tstart_X], gracz[playerid][gps_tstart_Y], gracz[playerid][gps_tstart_Z]);
		gracz[playerid][gps_Calculating] = 0;
		gracz[playerid][gps_dest_X] = fX;
		gracz[playerid][gps_dest_Y] = fY;
		gracz[playerid][gps_dest_Z] = fZ;
		gracz[playerid][gps_enabled] = true;
		gracz[playerid][gps_autooff] = auto_off;
		RGPS_CalculatePath(gracz[playerid][gps_tstart_X], gracz[playerid][gps_tstart_Y], gracz[playerid][gps_tstart_Z], gracz[playerid][gps_dest_X], gracz[playerid][gps_dest_Y], gracz[playerid][gps_dest_Z], playerid, 1);
		gracz[playerid][gps_Calculating] = 1;
		CarHUD_DistanceGPS(playerid, -1.0);
	}
	return 1;
}
/*
public GPS_WhenRouteIsCalculated(routeid,node_id_array[],amount_of_nodes,Float:distance,Float:Polygon[],Polygon_Size)
{
	test_GPS_WhenRouteIsCalculated(routeid,node_id_array,amount_of_nodes,distance,Polygon,Polygon_Size);//DEBUG
	if(amount_of_nodes > 1)
	{
		if(routeid >= 20000)//gps calc dla towarów - vany
		{
			routeid = routeid-20000;
			RFG_OnCalculatePath(routeid, distance);
		}
		else if(routeid >= 10000)//gps calc dla towarów - naczepy
		{
			routeid = routeid-10000;
			RFT_OnCalculatePath(routeid, distance);
		}
		else if(gracz[routeid][gps_enabled])//gps calc dla gracza
		{
			if(gracz[routeid][npc_taxi_calcroute] != 0)
			{
				new npcid = gracz[routeid][npc_taxi_calcroute];
				gracz[routeid][npc_taxi_calcroute] = 0;
				new message[128];
				NPC[npcid][npc_taxi_price] = floatround((distance/CONST_KM)*50.0);
				format(message, 128, "Bot HL mówi: To %0.1f km stąd. Zapłacę %d$.", (distance/CONST_KM), NPC[npcid][npc_taxi_price]);
				ProxDetector(npcid, 18.0, message, 0xFFFFFF96, 0xC8C8C896, 0x8B8B8B96, 0x5D5D5D96,  0x41414196);
				LeftNotifyShow(routeid, "Bot HL", "Przyjales zlecenie Bota HL. Dowiez go w miejsce wskazane na mapie! ~r~UWAGA! Opuszczenie pojazdu anuluje zlecenie!", LN_GREEN, 30);
			}
			DrawGPSTrack(routeid, Polygon, 8.5, Polygon_Size);
			//printf("gracz[routeid][gps_gzcount]: %d", gracz[routeid][gps_gzcount]);
			gracz[routeid][gps_Calculating] = 0;
			gracz[routeid][gps_LastDistance] = distance;
			CarHUD_DistanceGPS(routeid, distance);
			if(gracz[routeid][gps_autooff])
			{
				if((distance/CONST_KM) <= 0.3)
				{
					StopRouteGPS(routeid);
					Info(routeid, ""COL_GREEN"Dotarłeś do celu.");
					return 1;
				}
			}
		}
	}
	
	//printf("GPS CALC END");
	return 1;
}
*/

task RGPS_WhenRouteIsCalculated(routeid,node_id_array[],amount_of_nodes,Float:distance,Float:Polygon[],Polygon_Size)
{
	if(amount_of_nodes > 1)
	{
		if(routeid >= 30000)//gps calc dla towarów - firmy
		{
			routeid = routeid-30000;
			RCC_OnCalculatePath(routeid, distance);
		}
		else if(routeid >= 20000)//gps calc dla towarów - vany
		{
			routeid = routeid-20000;
			RFG_OnCalculatePath(routeid, distance);
		}
		else if(routeid >= 10000)//gps calc dla towarów - naczepy
		{
			routeid = routeid-10000;
			RFT_OnCalculatePath(routeid, distance);
		}
		else if(gracz[routeid][gps_enabled])//gps calc dla gracza
		{
			if(gracz[routeid][npc_taxi_calcroute] != 0)
			{
				new npcid = gracz[routeid][npc_taxi_calcroute];
				gracz[routeid][npc_taxi_calcroute] = 0;
				new message[128];
				NPC[npcid][npc_taxi_price] = floatround((distance/CONST_KM)*140.0);
				format(message, 128, "Bot HL mówi: To %0.1f km stąd. Zapłacę %d$.", (distance/CONST_KM), NPC[npcid][npc_taxi_price]);
				ProxDetector(npcid, 18.0, message, 0xFFFFFF96, 0xC8C8C896, 0x8B8B8B96, 0x5D5D5D96,  0x41414196);
				LeftNotifyShow(routeid, "Bot HL", "Przyjales zlecenie Bota HL. Dowiez go w miejsce wskazane na mapie! ~r~UWAGA! Opuszczenie pojazdu anuluje zlecenie!", LN_GREEN, 30);
			}
			DrawGPSTrack(routeid, Polygon, 8.5, Polygon_Size);
			//printf("gracz[routeid][gps_gzcount]: %d", gracz[routeid][gps_gzcount]);
			gracz[routeid][gps_Calculating] = 0;
			gracz[routeid][gps_LastDistance] = distance;
			CarHUD_DistanceGPS(routeid, distance);
			if(gracz[routeid][gps_autooff])
			{
				if((distance/CONST_KM) <= 0.3)
				{
					StopRouteGPS(routeid);
					Info(routeid, ""COL_GREEN"Dotarłeś do celu.");
					return 1;
				}
			}
		}
	}

	//printf("GPS CALC END");
	return 1;
}

stock DrawGPSTrack(playerid, Float: area[ ], Float: polygon_size = 5.0, all_points = sizeof area )
{
	rpc_GangZoneDestroyAll(playerid);
	CarHUD_DistanceGPS(playerid, 0.0);
	if(all_points < 4 || GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 0;

	new
		Float: start_x, Float: start_y,
		Float: end_x, Float: end_y,
		Float: draw_x, Float: draw_y,
		distance;
	for( new points = -1, j = all_points ; ++points < j ; )
	{

		start_x = area[ points ];
		start_y = area[ points + 1 ];

		end_x = area[ points + 2 ];
		end_y = area[ ++points + 2 ];

		if( points + 1 == j )
		{
			end_x = area[ 0 ];
			end_y = area[ 1 ];
		}
		new Float:trash, Float:posZ;
		GetPlayerPos(playerid, trash, trash, posZ);
		if(!IsPlayerInRangeOfPoint(playerid, 400.0, start_x, start_y, posZ))
		{
			continue;
		}
		if( start_x == end_x || start_y == end_y )
		{
			if(rpc_GangZoneCreate(playerid, 0xFF0000FF, start_x, start_y, end_x + ( start_x == end_x ? polygon_size : 0.0 ), end_y + ( start_x == end_x ? 0.0 : polygon_size )) == -2) 
			{
				//gracz[playerid][gps_refreshtrack] = true;
				printf("[ERROR] DrawGPSTrack->rpc_GangZoneCreate = NaN");
				return 1;//przerywa wszystko, jeśli zwróci -2 (coordy NaN)
			}
			continue;
		}

		distance = floatround( VectorSize( end_x - start_x, end_y - start_y, 0.0 ) / polygon_size ) ;

		draw_x = floatdiv( end_x - start_x, float( distance ) );
		draw_y = floatdiv( end_y - start_y, float( distance ) );

		while( distance-- )
		{
			start_x += draw_x;
			start_y += draw_y;
   			if(rpc_GangZoneCreate(playerid, 0xFF0000FF, start_x, start_y, start_x + polygon_size, start_y + polygon_size) == -2) 
   			{
   				//gracz[playerid][gps_refreshtrack] = true;
   				printf("[ERROR] DrawGPSTrack->rpc_GangZoneCreate = NaN");
   				return 1;//przerywa wszystko, jeśli zwróci -2 (coordy NaN)
   			}
		}
	}
	return 1;
}
//*****************************************************************************************************DYM Z KOMINA TRUCK EFFECT
stock TruckSmokeEffect(vehicleid, status)
{
	//printf("TruckSmokeEffect(%d, %d);", vehicleid, status);
	if(IsVehicleTruck(pojazd[vehicleid][v_model]) != 1) return 0;//tylko z truckami
	if(status > 0)
	{
		switch(pojazd[vehicleid][v_model])
		{
			case 403://linerunner
			{
				if(pojazd[vehicleid][v_object][6] == 0)
				{
					pojazd[vehicleid][v_object][6] = CreateDynamicObject(18703,0,0,-1000,0,0,0);
					AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][6], vehicleid, -1.125000,0.984999,0.679999,0.000000,0.000000,0.000000);
				}
				if(pojazd[vehicleid][v_object][7] == 0)
				{
					pojazd[vehicleid][v_object][7] = CreateDynamicObject(18703,0,0,-1000,0,0,0);
					AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][7], vehicleid,  1.125000,0.984999,0.679999,0.000000,0.000000,0.000000);
				}
			}
			case 514://tanker
			{
				if(pojazd[vehicleid][v_object][6] == 0)
				{
					pojazd[vehicleid][v_object][6] = CreateDynamicObject(18703,0,0,-1000,0,0,0);
					AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][6], vehicleid, 1.200000,0.674999,0.449999,0.000000,0.000000,0.000000);
				}
				if(pojazd[vehicleid][v_object][7] == 0)
				{
					pojazd[vehicleid][v_object][7] = CreateDynamicObject(18703,0,0,-1000,0,0,0);
					AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][7], vehicleid,  -1.200000,0.674999,0.449999,0.000000,0.000000,0.000000);
				}
			}
			case 515://roadtrain
			{
				if(status == 1)
				{
					if(pojazd[vehicleid][v_object][6] == 0)
					{
						pojazd[vehicleid][v_object][6] = CreateDynamicObject(18723,0,0,-1000,0,0,0);
						AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][6], vehicleid, -1.350000,-1.125000,0.619999,0.000000,0.000000,0.000000);
						if(pojazd[vehicleid][v_object][7] != 0) DestroyDynamicObject(pojazd[vehicleid][v_object][7]), pojazd[vehicleid][v_object][7] = 0;
					}
				}
				if(status == 2)
				{
					if(pojazd[vehicleid][v_object][7] == 0)
					{
						pojazd[vehicleid][v_object][7] = CreateDynamicObject(18703,0,0,-1000,0,0,0);
						AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][7], vehicleid, -1.345000,-1.125000,0.300000,0.000000,0.000000,0.000000);
						if(pojazd[vehicleid][v_object][6] != 0) DestroyDynamicObject(pojazd[vehicleid][v_object][6]), pojazd[vehicleid][v_object][6] = 0;
					}
				}
			}
		}
	}
	else
	{
		if(pojazd[vehicleid][v_object][6] != 0) DestroyDynamicObject(pojazd[vehicleid][v_object][6]), pojazd[vehicleid][v_object][6] = 0;
		if(pojazd[vehicleid][v_object][7] != 0) DestroyDynamicObject(pojazd[vehicleid][v_object][7]), pojazd[vehicleid][v_object][7] = 0;
	}
	return 1;
}

/*
stock TrafficLight(vehicleid, status)
{
	new model = GetVehicleModel(vehicleid);
	new id = model-400;
	if(BlinkOffset[id][bX] != 0.0)
	{
		pojazd[vehicleid][v_trafficlights] = status;
		if(!status)
		{
			if(pojazd[vehicleid][v_object][4] != 0) DestroyDynamicObject(pojazd[vehicleid][v_object][4]), pojazd[vehicleid][v_object][4] = 0;
			if(pojazd[vehicleid][v_object][5] != 0) DestroyDynamicObject(pojazd[vehicleid][v_object][5]), pojazd[vehicleid][v_object][5] = 0;
		}
		else
		{
			//515, 514, 455, 403, 406, 407
			new light_type = 19281;
			if(model == 515 || model == 514 || model == 455 || model == 403 || model == 406 || model == 407) light_type = 19295;
			if(pojazd[vehicleid][v_object][4] == 0)//19295(big), 19281(small)
			{
				pojazd[vehicleid][v_object][4] = CreateDynamicObject(light_type, 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][4], vehicleid, BlinkOffset[id][bX]+0.1,BlinkOffset[id][bY],BlinkOffset[id][bZ]+0.1, 0.0, 0.0, 0.0);//lewy
			}
			if(pojazd[vehicleid][v_object][5] == 0)
			{
				pojazd[vehicleid][v_object][5] = CreateDynamicObject(light_type, 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][5], vehicleid, -BlinkOffset[id][bX]-0.1,BlinkOffset[id][bY],BlinkOffset[id][bZ]+0.1, 0.0, 0.0, 0.0);//prawy
			}
		}
	}
	return 1;
}*/
//przyczepialne obiekty do pojazdów frakcyjnych

stock AttachObjectsToFractionVeh(vehicleid, fractionid)
{
	if(fractionid == F_NONE) return 1;
	switch(fractionid)
	{
		case F_POLICE:
		{
			if(pojazd[vehicleid][v_model] == 560)//sultan
			{
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(18646,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, -0.540000,0.079999,0.859999,0.000000,0.000000,0.000000);
			}
			else if(pojazd[vehicleid][v_model] == 502)//hotring
			{
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(19620,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.445000,0.794999,0.000000,0.000000,0.000000);
			}
		}
		case F_BORDERGUARD:
		{
			if(pojazd[vehicleid][v_model] == 490)//rancher
			{
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(19420,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.020000,1.085000,0.000000,0.000000,0.000000);
			}
			else if(pojazd[vehicleid][v_model] == 579)//huntley
			{
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(19420,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.300000,1.230000,0.000000,0.000000,0.000000);
			}
			else if(pojazd[vehicleid][v_model] == 495)//sandking
			{
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(19420,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.449999,0.990000,0.000000,0.000000,0.000000);

				pojazd[vehicleid][v_object][1] = CreateDynamicObject(18646,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][1], vehicleid, -0.834999,2.440001,-0.535000,0.000000,0.000000,0.000000);

				pojazd[vehicleid][v_object][2] = CreateDynamicObject(18646,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][2], vehicleid, 0.834999,2.440001,-0.535000,0.000000,0.000000,0.000000);
			}
			/*else if(pojazd[vehicleid][v_model] == 598 || pojazd[vehicleid][v_model] == 597)//LSPD || SFPD
			{
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(19476,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0] , vehicleid, 0.000000,2.330000,0.275000,0.000000,-82.619964,-270.179809);
				SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][0] , 0, "STRAŻ GRANICZNA", 110, "Impact", 80, 0, -16759808, -16768512, 1);
			}*/
		}
		case F_EMERGENCY:
		{
			if(pojazd[vehicleid][v_model] == 490)//rancher
			{
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(11702,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.035000,1.134999,0.000000,0.000000,0.000000);
			}
			else if(pojazd[vehicleid][v_model] == 563)//raindance
			{
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(19848,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, -1.205000,-0.225000,-0.674999,0.000000,0.000000,0.000000);

				pojazd[vehicleid][v_object][1] = CreateDynamicObject(19848,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][1], vehicleid, 1.205000,-0.225000,-0.674999,0.000000,0.000000,-179.999893);
			}
		}
		case F_TAXI:
		{
			if(pojazd[vehicleid][v_model] == 560)//sultan
			{
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(19308,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.245000,0.869999,0.000000,0.000000,0.000000);
				SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][0], 0, "TAXI", 130, "Impact", 170, 0, -16777216, -4754678, 1);
			}
			else if(pojazd[vehicleid][v_model] == 411)//infernus
			{
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(19308,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.160000,0.749999,0.000000,0.000000,0.000000);
				SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][0], 0, "TAXI", 130, "Impact", 170, 0, -16777216, -4754678, 1);
			}
			else if(pojazd[vehicleid][v_model] == 551)//merit
			{
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(19308,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.544999,0.954999,0.000000,0.000000,0.000000);
				SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][0], 0, "TAXI", 130, "Impact", 170, 0, -16777216, -4754678, 1);
			}
			else if(pojazd[vehicleid][v_model] == 405)//sentinel
			{
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(19308,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.394999,0.799999,0.000000,0.000000,0.000000);
				SetDynamicObjectMaterialText(pojazd[vehicleid][v_object][0], 0, "TAXI", 130, "Impact", 170, 0, -16777216, -4754678, 1);
			}
		}
	}
	return 1;
}

stock TuneTaxiVehicle(vehicleid)
{
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION && pojazd[vehicleid][v_owner] == F_TAXI)
	{
		if(GetVehicleComponentInSlot(vehicleid, CARMODTYPE_SPOILER) != 1138)
		{
			//printf("tune car uid: %d", pojazd[vehicleid][v_id]);
			AddVehicleComponent(vehicleid, 1010);//nitro - wszedzie
			pojazd[vehicleid][v_tune_data][5] = 1010;
			if(pojazd[vehicleid][v_model] != 431) AddVehicleComponent(vehicleid, 1073);//koła - wszedzie (prócz busa)
			if(pojazd[vehicleid][v_model] == 560)//sultan
			{
				AddVehicleComponent(vehicleid, 1138);//spoiler - sultan
				AddVehicleComponent(vehicleid, 1026);//progi - sultan
				AddVehicleComponent(vehicleid, 1028);//wydech - sultan
				AddVehicleComponent(vehicleid, 1170);//zderzak przód - sultan
				AddVehicleComponent(vehicleid, 1140);//zderzak tył - sultan
			}
		}
	}
	return 1;
}

task Process_SirenEffects(vehicleid)
{
	if(pojazd[vehicleid][v_roosters_withoutsiren])
	{
		if(pojazd[vehicleid][v_model] == 525)//Towtruck
		{
			if(GetDynamicObjectModel(pojazd[vehicleid][v_object][0]) != 19803  && pojazd[vehicleid][v_object][0] == 0)
			{
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(19803,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,0.000000,0.000000,0.000000,0.000000,0.000000);
			}
		}
	}
	else
	{
		if(pojazd[vehicleid][v_model] == 525)//Towtruck
		{
			if(GetDynamicObjectModel(pojazd[vehicleid][v_object][0]) == 19803)
			{
				DestroyDynamicObject(pojazd[vehicleid][v_object][0]);
				pojazd[vehicleid][v_object][0] = 0;
			}
		}
	}
	pojazd[vehicleid][v_sirenstatus] = GetVehicleParamsSirenState(vehicleid);
	if(pojazd[vehicleid][v_sirenstatus] == 1)//*******************************************************************************************syrena uruchomiona
	{
		if(pojazd[vehicleid][v_model] == 560)//sultan
		{
			if(GetDynamicObjectModel(pojazd[vehicleid][v_object][0]) != 18646  && pojazd[vehicleid][v_object][0] == 0)
			{
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(18646,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, -0.540000,0.079999,0.859999,0.000000,0.000000,0.000000);
			}
		}
		else if(pojazd[vehicleid][v_model] == 490)//rancher
		{
			if(pojazd[vehicleid][v_owner] == F_EMERGENCY)
			{
				if(GetDynamicObjectModel(pojazd[vehicleid][v_object][0]) == 11702)
				{
					DestroyDynamicObject(pojazd[vehicleid][v_object][0]);
					pojazd[vehicleid][v_object][0] = CreateDynamicObject(11701,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
					AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.035000,1.134999,0.000000,0.000000,0.000000);
				}
			}
			else
			{
				if(GetDynamicObjectModel(pojazd[vehicleid][v_object][0]) == 19420)
				{
					DestroyDynamicObject(pojazd[vehicleid][v_object][0]);
					pojazd[vehicleid][v_object][0] = CreateDynamicObject(19419,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
					AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.020000,1.085000,0.000000,0.000000,0.000000);
				}
			}
		}
		else if(pojazd[vehicleid][v_model] == 579)//huntley
		{
			if(GetDynamicObjectModel(pojazd[vehicleid][v_object][0]) == 19420)
			{
				DestroyDynamicObject(pojazd[vehicleid][v_object][0]);
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(19419,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.300000,1.230000,0.000000,0.000000,0.000000);
			}
		}
		else if(pojazd[vehicleid][v_model] == 495)//sandking
		{
			//koguty dach
			if(GetDynamicObjectModel(pojazd[vehicleid][v_object][0]) == 19420)
			{
				DestroyDynamicObject(pojazd[vehicleid][v_object][0]);
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(19419,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.449999,0.990000,0.000000,0.000000,0.000000);
			}
			//koguty zderzak
			if(GetDynamicObjectModel(pojazd[vehicleid][v_object][1]) != 18646 &&  pojazd[vehicleid][v_object][1] == 0)
			{
				pojazd[vehicleid][v_object][1] = CreateDynamicObject(18646,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][1], vehicleid, -0.834999,2.440001,-0.535000,0.000000,0.000000,0.000000);
			}
			if(GetDynamicObjectModel(pojazd[vehicleid][v_object][2]) != 18646 && pojazd[vehicleid][v_object][2] == 0)
			{
				pojazd[vehicleid][v_object][2] = CreateDynamicObject(18646,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][2], vehicleid, 0.834999,2.440001,-0.535000,0.000000,0.000000,0.000000);
			}
		}
	}
	else//*******************************************************************************************syrena wyłączona
	{
		//**********NAPRAWIANIE REFLEKTORÓW
		if(pojazd[vehicleid][v_owner_type] == VEHICLE_FRACTION)
		{
			static panels, doors, lights, tires;
			GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
			if(lights != 0) UpdateVehicleDamageStatus(vehicleid, panels, doors, 0, tires);
		}
		//**********END NAPRAWIANIE LAMP LEFLEKTORÓW
		if(pojazd[vehicleid][v_model] == 560)//sultan
		{
			if(GetDynamicObjectModel(pojazd[vehicleid][v_object][0]) == 18646)
			{
				DestroyDynamicObject(pojazd[vehicleid][v_object][0]);
				pojazd[vehicleid][v_object][0] = 0;
			}
		}
		else if(pojazd[vehicleid][v_model] == 490)//rancher
		{
			if(pojazd[vehicleid][v_owner] == F_EMERGENCY)
			{
				if(GetDynamicObjectModel(pojazd[vehicleid][v_object][0]) == 11701)
				{
					DestroyDynamicObject(pojazd[vehicleid][v_object][0]);
					pojazd[vehicleid][v_object][0] = CreateDynamicObject(11702,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
					AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.035000,1.134999,0.000000,0.000000,0.000000);
				}
			}
			else
			{
				if(GetDynamicObjectModel(pojazd[vehicleid][v_object][0]) == 19419)
				{
					DestroyDynamicObject(pojazd[vehicleid][v_object][0]);
					pojazd[vehicleid][v_object][0] = CreateDynamicObject(19420,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
					AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.020000,1.085000,0.000000,0.000000,0.000000);
				}
			}
		}
		else if(pojazd[vehicleid][v_model] == 579)//huntley
		{
			if(GetDynamicObjectModel(pojazd[vehicleid][v_object][0]) == 19419)
			{
				DestroyDynamicObject(pojazd[vehicleid][v_object][0]);
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(19420,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.300000,1.230000,0.000000,0.000000,0.000000);
			}
		}
		else if(pojazd[vehicleid][v_model] == 495)//sandking
		{
			//koguty dach
			if(GetDynamicObjectModel(pojazd[vehicleid][v_object][0]) == 19419)
			{
				DestroyDynamicObject(pojazd[vehicleid][v_object][0]);
				pojazd[vehicleid][v_object][0] = CreateDynamicObject(19420,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][0], vehicleid, 0.000000,-0.449999,0.990000,0.000000,0.000000,0.000000);
			}
			//koguty zderzak
			if(GetDynamicObjectModel(pojazd[vehicleid][v_object][1]) == 18646)
			{
				DestroyDynamicObject(pojazd[vehicleid][v_object][1]);
				pojazd[vehicleid][v_object][1] = 0;
			}
			if(GetDynamicObjectModel(pojazd[vehicleid][v_object][2]) == 18646)
			{
				DestroyDynamicObject(pojazd[vehicleid][v_object][2]);
				pojazd[vehicleid][v_object][2] = 0;
			}
		}
	}
	return 1;
}

task FlashLights() 
{
	static panels, doors, lights, tires;
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		if(pojazd[v][v_model] == 0) continue;
		if(pojazd[v][v_sirenstatus] == 1)//syreny uruchomione
		{
			GetVehicleDamageStatus(v, panels, doors, lights, tires);
			switch(pojazd[v][v_flash_step])
			{
				case 0:
				{
					UpdateVehicleDamageStatus(v, panels, doors, 1, tires);//prawy
					pojazd[v][v_flash_step]++;
				}
				case 1:
				{
					UpdateVehicleDamageStatus(v, panels, doors, 4, tires);//lewy
					pojazd[v][v_flash_step]++;
				}
				case 2:
				{
					UpdateVehicleDamageStatus(v, panels, doors, 1, tires);//prawy
					pojazd[v][v_flash_step]++;
				}
				case 3:
				{
					UpdateVehicleDamageStatus(v, panels, doors, 5, tires);//zero
					pojazd[v][v_flash_step]++;
				}
				case 4:
				{
					UpdateVehicleDamageStatus(v, panels, doors, 1, tires);//prawy
					pojazd[v][v_flash_step]++;
				}
				case 5:
				{
					UpdateVehicleDamageStatus(v, panels, doors, 4, tires);//lewy
					pojazd[v][v_flash_step]++;
				}
				case 6:
				{
					UpdateVehicleDamageStatus(v, panels, doors, 1, tires);//prawy
					pojazd[v][v_flash_step]++;
				}
				case 7:
				{
					UpdateVehicleDamageStatus(v, panels, doors, 4, tires);//lewy
					pojazd[v][v_flash_step]++;
				}
				case 8:
				{
					UpdateVehicleDamageStatus(v, panels, doors, 5, tires);//zero
					pojazd[v][v_flash_step]++;
				}
				default:
				{
					UpdateVehicleDamageStatus(v, panels, doors, 4, tires);//lewy
					pojazd[v][v_flash_step] = 0;
				}
			}
		}
	}
	return 1;
}

stock IsVehicleWornOut(vehicleid, damageid)
{
	if(damageid > MAX_VEHICLEDAMAGES) return 0;
	if(pojazd[vehicleid][v_owner_type] != VEHICLE_PLAYER && pojazd[vehicleid][v_owner_type] != VEHICLE_BUSINESS) return 0;
	if(pojazd[vehicleid][v_damages_lifetime_km][damageid] > VehicleDamages[damageid][vd_exp_km]) return 1;
	return 0;
}

task Process_VehicleDamage(playerid, vehicleid, type)
{
	switch(type)
	{
		case 0://timer co sekunde
		{
			if(playerid == -1) return 1;
			//Problemy z sterownością
			if(gracz[playerid][opu_speed] > 30)
			{
				if(!IsVehicleBike(pojazd[vehicleid][v_model]))//tylko osobówki
				{
					if(IsVehicleWornOut(vehicleid, 1) || IsVehicleWornOut(vehicleid, 2))
					{
						if(gracz[playerid][when_tipsy] == 0) SetPlayerDrunkLevel(playerid, 2100);
					}
				}
			}
			//uszkodzony przekaźnik świateł - brak świateł
			new engine, lights, alarm, doors, bonnet, boot, objective;
			GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
			if(lights > 0)
			{
				if(IsVehicleWornOut(vehicleid, 14))
				{
					SetVehicleParamsEx(vehicleid, engine, 0, alarm, doors, bonnet, boot, objective);
					TrafficLight(vehicleid, 0);
				}
			}
			//uszkodzona chłodnica
			if(IsVehicleWornOut(vehicleid, 15))
			{
				GetVehicleHealth(vehicleid, pojazd[vehicleid][v_HP]);
				if(pojazd[vehicleid][v_HP] > 647.0)
				{
					pojazd[vehicleid][v_HP] = 645.0;
					SetVehicleHealth(vehicleid, pojazd[vehicleid][v_HP]);
					mq_format("UPDATE `pojazdy` SET `hp`='%f' WHERE `id`='%d';", pojazd[vehicleid][v_HP], pojazd[vehicleid][v_id]);
					mq_send("QUpdateVehicle");
				}
			}
		}
		case 1://co 1 km (czyli np podczas jazdy)
		{
			if(IsVehicleWornOut(vehicleid, 0))//uszkodzenie opony
			{
				new panels, doors, lights, tires;
				GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
				if(tires == 0)//jeśli oponka żadna nei jest przebita
				{
					if(IsVehicleBike(pojazd[vehicleid][v_model]))//motory
					{
						if(RandomEx(0, 2)) UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, 1);
						else UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, 2);
					}
					else//osobówki itd
					{
						new rand = RandomEx(0, 3);
						if(rand == 0) UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, 1);
						else if(rand == 1) UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, 2);
						else if(rand == 2) UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, 4);
						else if(rand == 3) UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, 8);
					}
				}
			}
			if(IsVehicleWornOut(vehicleid, 3) || IsVehicleWornOut(vehicleid, 4) || IsVehicleWornOut(vehicleid, 5))//sporadycznie gaśnie
			{
				if(random(3) != 2)
				{
					new engine, lights, alarm, doors, bonnet, boot, objective;
					GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
					if(engine) 
					{
						SetVehicleParamsEx(vehicleid, 0, lights, alarm, doors, bonnet, boot, objective);
						playerid = IsVehicleInUseByDriver(vehicleid);
						LeftNotifyShow(playerid, "Awaria", "Silnik pojazdu ~r~zgasl~w~. Pojazd prawdopodobnie ulegl awarii. Odwiedz warsztat.", LN_RED);
					}
				}
			}
		}
	}
	return 1;
}

stock TranslateVehPaintjob(source)
{
	if(source <= 0) return 3;
	return source-1;
}

stock MaxVehiclesPlayer(playerid)
{
	if(isvip(playerid)) return MAX_VEHS_VIP;
	return MAX_VEHS_PLAYER;
}

stock ToggleVehicleNeons(vehicleid, status)
{
	if(pojazd[vehicleid][v_neon_modelid] != 0)
	{
		if(status)
		{
			if(pojazd[vehicleid][v_object][8] != 0) 
			{
				DestroyDynamicObject(pojazd[vehicleid][v_object][8]);
				pojazd[vehicleid][v_object][8] = 0;
			}
			if(pojazd[vehicleid][v_object][9] != 0) 
			{
				DestroyDynamicObject(pojazd[vehicleid][v_object][9]);
				pojazd[vehicleid][v_object][9] = 0;
			}
			if(pojazd[vehicleid][v_object][8] == 0)
			{
				pojazd[vehicleid][v_object][8] = CreateDynamicObject(pojazd[vehicleid][v_neon_modelid], 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][8], vehicleid, 0.8000, 0.0570, -0.4655, 0.0, 0.0, 0.0);//1 strona
			}
			if(pojazd[vehicleid][v_object][9] == 0)
			{
				pojazd[vehicleid][v_object][9] = CreateDynamicObject(pojazd[vehicleid][v_neon_modelid], 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
				AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][9], vehicleid, -0.8000, 0.0570, -0.4655, 0.0, 0.0, 0.0);//druga strona
			}
		}
		else
		{
			if(pojazd[vehicleid][v_object][8] != 0) 
			{
				DestroyDynamicObject(pojazd[vehicleid][v_object][8]);
				pojazd[vehicleid][v_object][8] = 0;
			}
			if(pojazd[vehicleid][v_object][9] != 0) 
			{
				DestroyDynamicObject(pojazd[vehicleid][v_object][9]);
				pojazd[vehicleid][v_object][9] = 0;
			}
			if(pojazd[vehicleid][v_object][8] == 0)
			{
				pojazd[vehicleid][v_object][8] = CreateDynamicObject(pojazd[vehicleid][v_neon_modelid], 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
				//NIE PRZYCZEPIAMY: AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][8], vehicleid, 0.8000, 0.0570, -0.4655, 0.0, 0.0, 0.0);//1 strona
			}
			if(pojazd[vehicleid][v_object][9] == 0)
			{
				pojazd[vehicleid][v_object][9] = CreateDynamicObject(pojazd[vehicleid][v_neon_modelid], 0.0, 0.0, -1000.0, 0.0, 0.0, 0.0);
				//NIE PRZYCZEPIAMY: AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][9], vehicleid, -0.8000, 0.0570, -0.4655, 0.0, 0.0, 0.0);//druga strona
			}
		}
		return 1;
	}
	return 0;
}
//3D texty na pojazdach firmowych i graczy
task Process_VehPlayerBusinnesLabels()
{
	if(serwer[time_timestamp] > serwer[timestamp_VPBusinnesLabels])
	{
		new strLabel[512];
		for(new v = GetVehiclePoolSize(); v != -1; v--)
		{
			if(pojazd[v][v_model] == 0) continue;
			if(pojazd[v][v_owner_type] == VEHICLE_PLAYER)
			{
				if(!IsValidDynamic3DTextLabel(pojazd[v][v_text3d])) pojazd[v][v_text3d] = CreateDynamic3DTextLabel("[gracz]", 0x00000000, pojazd[v][v_X], pojazd[v][v_Y], pojazd[v][v_Z]+0.3, 6.0, .attachedvehicle = v, .testlos = 1);
				if(pojazd[v][v_idletime]+(5) > serwer[time_timestamp]) continue;//zostaw pojazdy które były nie dawno odświeżane
				if(pojazd[v][v_cargo] != 0) continue;//nie aktualizuj labeli dla pojazdów z towarem
				for(new p = PlayerPoolSize(); p != -1; p--)
				{
					if(gracz[p][loggedin])
					{
						if(gracz[p][UID] == pojazd[v][v_owner])
						{
							format(strLabel, 512, "["COL_DRVONLINE"Pojazd: {%06x}%s(%d)"COL_WHITE"]\n"COL_GREY"[UID: %d]", GetPlayerColor(p) >>> 8, nick(p), p, pojazd[v][v_id]);
							UpdateDynamic3DTextLabelText(pojazd[v][v_text3d], -1, strLabel);
						}
					}
				}
			}
			else if(pojazd[v][v_owner_type] == VEHICLE_BUSINESS)
			{
				if(!IsValidDynamic3DTextLabel(pojazd[v][v_text3d]))
				if(IsVehicleTrailer(pojazd[v][v_model])) pojazd[v][v_text3d] = CreateDynamic3DTextLabel("[firma]", 0x00000000, pojazd[v][v_X], pojazd[v][v_Y], pojazd[v][v_Z]+0.3, 20.0, .attachedvehicle = v, .testlos = 1);
				else pojazd[v][v_text3d] = CreateDynamic3DTextLabel("[firma]", 0x00000000, pojazd[v][v_X], pojazd[v][v_Y], pojazd[v][v_Z]+0.3, 6.0, .attachedvehicle = v, .testlos = 1);
				if(pojazd[v][v_idletime]+(5) > serwer[time_timestamp]) continue;//zostaw pojazdy które były nie dawno odświeżane
				if(pojazd[v][v_cargo] != 0) continue;//nie aktualizuj labeli dla pojazdów z towarem
				new cid = pojazd[v][v_owner];
				format(strLabel, 512, "["COL_DRVONLINE"Firma: "COL_BLUE"%s"COL_WHITE"]\n"COL_GREY"[UID: %d]", company[cid][cny_name], pojazd[v][v_id]);
				UpdateDynamic3DTextLabelText(pojazd[v][v_text3d], -1, strLabel);
			}
		}
		serwer[timestamp_VPBusinnesLabels] = serwer[time_timestamp]+30;
	}
	return 1;
}

stock HideVehicleLabel(vehicleid, bool:force = false)
{
	if(pojazd[vehicleid][v_cargo] != 0 && force == false) return 0;//nie aktualizuj labeli dla pojazdów z towarem
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER || pojazd[vehicleid][v_owner_type] == VEHICLE_BUSINESS)
	{
		if(IsValidDynamic3DTextLabel(pojazd[vehicleid][v_text3d]))
		{
			return UpdateDynamic3DTextLabelText(pojazd[vehicleid][v_text3d], 0x00000000, "_");
		}
	}
	else if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_MPTRAILER)//naczepy freelancer
	{
		if(IsValidDynamic3DTextLabel(pojazd[vehicleid][v_text3d]))
		{
			return UpdateDynamic3DTextLabelText(pojazd[vehicleid][v_text3d], 0x009933FF, pojazd[vehicleid][v_text3d_strcache]);
		}
	}
	return 0;
}
//gaszenie helikopterem
stock ToggleHelicopterWater(vehicleid, status)
{
	if(pojazd[vehicleid][v_model] != 563) return 0;
	if(status)//on
	{
		if(pojazd[vehicleid][v_object][3] != 0) 
		{
			DestroyDynamicObject(pojazd[vehicleid][v_object][3]);
			pojazd[vehicleid][v_object][3] = 0;
		}
		if(pojazd[vehicleid][v_object][3] == 0)
		{
			pojazd[vehicleid][v_object][3] = CreateDynamicObject(18707,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
			AttachDynamicObjectToVehicle(pojazd[vehicleid][v_object][3], vehicleid, 0.000000,0.000000,-2.400000,0.000000,0.000000,0.000000);
		}
	}
	else//off
	{
		if(pojazd[vehicleid][v_object][3] != 0) 
		{
			DestroyDynamicObject(pojazd[vehicleid][v_object][3]);
			pojazd[vehicleid][v_object][3] = 0;
		}
	}
	//pojazd[vehicleid][v_object][3] = CreateDynamicObject(19848,0,0,-1000,0,0,0, .streamdistance = DISDRAW_CAROBJ, .drawdistance = DISDRAW_CAROBJ, .priority = 1);
	return 1;
}

stock IsHelicopterUseWater(vehicleid)
{
	if(pojazd[vehicleid][v_model] != 563) return 0;
	if(pojazd[vehicleid][v_object][3] == 0) return 0;
	return 1;
}