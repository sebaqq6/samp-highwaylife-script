/*
The MIT License (MIT)
Copyright (c) 2016 Philipp J.
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.
*/

#include <a_samp>

//#pragma unused VehicleNames

native IsValidVehicle(vehicleid);

#if !defined MAX_VEHICLES
	#define MAX_VEHICLES 2000
#endif

#if !defined VEHICLEDAMAGE_UPDATEINTERVAL
	#define VEHICLEDAMAGE_UPDATEINTERVAL 50
#endif

#define VEHICLEDAMAGE_USE_TIMER

#if !defined VEHICLEDAMAGE_FLIPVEH_IFNODMG
	#define VEHICLEDAMAGE_FLIPVEH_IFNODMG 0
#endif

enum vehicle_visual_damage_data {
	vPanels,
	vDoors,
	vTires,
	vLights
}

enum vehicle_damage_data {
	Float:vHealth,
	Float:vDamage,
	vLastHitter,
	vLastWeaponid,
	vVisualStatus[vehicle_visual_damage_data],
	vVisualDamage[vehicle_visual_damage_data],
	vIsProcessingDamage
}

new vehicle_damage[MAX_VEHICLES][vehicle_damage_data];

new 
	Float:vehicledamageupdater_health,
	Float:vehicledamageupdater_damage;

forward VehicleDamageUpdater();
forward OnVehicleTakeDamage(vehicleid, driverid, &Float:amount, playerid, weaponid, &apply_health_damage);
forward OnVehicleTakeVisualDamage(vehicleid, driverid, &apply_visual_damage);

public VehicleDamageUpdater() {
	for(new vehicleid = 0, poolsize = GetVehiclePoolSize(); vehicleid <= poolsize; vehicleid++) {
		if(!IsValidVehicle(vehicleid)) continue;
		UpdateVehicleDamageInformation(vehicleid);
	}
}

stock UpdateVehicleDamageInformation(vehicleid) {
	if(!vehicle_damage[vehicleid][vIsProcessingDamage]) {
		GetVehicleHealth(vehicleid, vehicledamageupdater_health);
		vehicledamageupdater_damage = vehicle_damage[vehicleid][vHealth] - vehicledamageupdater_health;
		vehicle_damage[vehicleid][vHealth] = vehicledamageupdater_health;
		if(vehicledamageupdater_damage > 0) 
			vehicle_damage[vehicleid][vDamage] += vehicledamageupdater_damage;		
		
		if(vehicle_damage[vehicleid][vDamage] > 0) {
			vehicle_damage[vehicleid][vIsProcessingDamage] = 1;
			PrepareVehicleDamage(vehicleid, vehicle_damage[vehicleid][vHealth], vehicle_damage[vehicleid][vDamage]);
		}
	}
}

stock PrepareVehicleDamage(vehicleid, Float:vehiclehealth, Float:original_vehicledamage) {
	new 
		driverid = RetrieveVehicleDriverID(vehicleid), 
		Float:vehicledamage = original_vehicledamage,
		apply_health_damage = 1;

	if(vehicle_damage[vehicleid][vLastHitter] == INVALID_PLAYER_ID) 
		OnVehicleTakeDamage(vehicleid, driverid, vehicledamage, INVALID_PLAYER_ID, 0, apply_health_damage);
	else 
		OnVehicleTakeDamage(vehicleid, driverid, vehicledamage, vehicle_damage[vehicleid][vLastHitter], vehicle_damage[vehicleid][vLastWeaponid], apply_health_damage);

	if(!apply_health_damage) {
		vehicle_damage[vehicleid][vHealth] = vehiclehealth + original_vehicledamage;
		SetVehicleHealth(vehicleid, vehicle_damage[vehicleid][vHealth]);
		
		if(VEHICLEDAMAGE_FLIPVEH_IFNODMG && IsVehicleUpsideDown(vehicleid)) 
			FlipVehicle(vehicleid);

	} else if(original_vehicledamage != vehicledamage) {
		vehicle_damage[vehicleid][vHealth] = (vehiclehealth + original_vehicledamage) - vehicledamage;
		SetVehicleHealth(vehicleid, vehicle_damage[vehicleid][vHealth]);
	}
	
	
	vehicle_damage[vehicleid][vDamage] -= original_vehicledamage;
	vehicle_damage[vehicleid][vLastHitter] = INVALID_PLAYER_ID;
	vehicle_damage[vehicleid][vLastWeaponid] = -1;
	vehicle_damage[vehicleid][vIsProcessingDamage] = 0;
	return 1;
}

stock PrepareVehicleVisualDamage(vehicleid) {
	new 
		driverid = RetrieveVehicleDriverID(vehicleid),
		apply_visual_damage = 1;

	OnVehicleTakeVisualDamage(vehicleid, driverid, apply_visual_damage);

	if(apply_visual_damage) 
		vehicle_damage[vehicleid][vVisualStatus] = vehicle_damage[vehicleid][vVisualDamage];
	else {
		UpdateVehicleDamageStatus(vehicleid,
			vehicle_damage[vehicleid][vVisualStatus][vPanels], 
			vehicle_damage[vehicleid][vVisualStatus][vDoors], 
			vehicle_damage[vehicleid][vVisualStatus][vLights], 
			vehicle_damage[vehicleid][vVisualStatus][vTires]);
	}
}


public OnGameModeInit()
{
    for(new i = 0; i < sizeof(vehicle_damage); i++) {
		vehicle_damage[i][vLastHitter] = INVALID_PLAYER_ID;
		vehicle_damage[i][vIsProcessingDamage] = 0;
    }
	
	#if defined VEHICLEDAMAGE_USE_TIMER
		SetTimer("VehicleDamageUpdater", VEHICLEDAMAGE_UPDATEINTERVAL, true);
	#endif
	#if defined VehDMG_OnGameModeInit
		VehDMG_OnGameModeInit();
	#endif
    return 1;
}

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif

#define OnGameModeInit VehDMG_OnGameModeInit
#if defined VehDMG_OnGameModeInit
	forward VehDMG_OnGameModeInit();
#endif

public OnVehicleDamageStatusUpdate(vehicleid, playerid) {
	GetVehicleDamageStatus(vehicleid, 
		vehicle_damage[vehicleid][vVisualDamage][vPanels], 
		vehicle_damage[vehicleid][vVisualDamage][vDoors], 
		vehicle_damage[vehicleid][vVisualDamage][vLights], 
		vehicle_damage[vehicleid][vVisualDamage][vTires]);
	PrepareVehicleVisualDamage(vehicleid);
	#if defined VehDMG_OnVehDmgStatusUpdate
		VehDMG_OnVehDmgStatusUpdate(vehicleid, playerid);
	#endif
	return 1;
}

#if defined _ALS_OnVehicleDamageStatusUpd
    #undef OnVehicleDamageStatusUpdate
#else
    #define _ALS_OnVehicleDamageStatusUpdate
#endif

#define OnVehicleDamageStatusUpdate VehDMG_OnVehDmgStatusUpdate
#if defined VehDMG_OnVehDmgStatusUpdate
	forward VehDMG_OnVehDmgStatusUpdate(vehicleid, playerid);
#endif

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if(hittype == BULLET_HIT_TYPE_VEHICLE) {
		vehicle_damage[hitid][vLastHitter]   = playerid;
		vehicle_damage[hitid][vLastWeaponid] = GetPlayerWeapon(playerid);
	}
	#if defined VehDMG_OnPlayerWeaponShot
		VehDMG_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerWeaponShot
    #undef OnPlayerWeaponShot
#else
    #define _ALS_OnPlayerWeaponShot
#endif

#define OnPlayerWeaponShot VehDMG_OnPlayerWeaponShot
#if defined VehDMG_OnPlayerWeaponShot
	forward VehDMG_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#endif


public OnVehicleSpawn(vehicleid)
{
	GetVehicleDamageStatus(vehicleid, 
			vehicle_damage[vehicleid][vVisualStatus][vPanels], 
			vehicle_damage[vehicleid][vVisualStatus][vDoors], 
			vehicle_damage[vehicleid][vVisualStatus][vLights], 
			vehicle_damage[vehicleid][vVisualStatus][vTires]);

	GetVehicleHealth(vehicleid, vehicledamageupdater_health);
	vehicle_damage[vehicleid][vHealth] = vehicledamageupdater_health;

	#if defined VehDMG_OnVehicleSpawn
		OnVehicleSpawn(vehicleid);
	#endif
	return 1;
}

#if defined _ALS_OnVehicleSpawn
    #undef OnVehicleSpawn
#else
    #define _ALS_OnVehicleSpawn
#endif

#define OnVehicleSpawn VehDMG_OnVehicleSpawn
#if defined VehDMG_OnVehicleSpawn
	forward VehDMG_OnVehicleSpawn(vehicleid);
#endif


/*
	Snippets
*/

stock IsVehicleUpsideDown(vehicleid) {
    new Float:quat_w,Float:quat_x,Float:quat_y,Float:quat_z;
    GetVehicleRotationQuat(vehicleid,quat_w,quat_x,quat_y,quat_z);
    new Float:y = atan2(2*((quat_y*quat_z)+(quat_w*quat_x)),(quat_w*quat_w)-(quat_x*quat_x)-(quat_y*quat_y)+(quat_z*quat_z));
    return (y > 90 || y < -90);
}

stock FlipVehicle(vehicleid) {
	new Float:angle;
	GetVehicleZAngle(vehicleid, angle);
	SetVehicleZAngle(vehicleid, angle);
}

stock RetrieveVehicleDriverID(vehicleid) {
	for(new playerid = 0, poolsize = GetPlayerPoolSize(); playerid <= poolsize; playerid++) {
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && IsPlayerInVehicle(playerid, vehicleid)) return playerid;
	}
	return INVALID_PLAYER_ID;
}
