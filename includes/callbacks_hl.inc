#define POTENTIAL_CRASH_DAMAGE 		35.0

stock Float:Crash_GetSpeed(vehicleid)
{
	// This is only for basic speed calculations. No need to get the real speed.

	new
	    Float:fX,
	    Float:fY,
	    Float:fZ
	;

	GetVehicleVelocity(vehicleid, fX, fY, fZ);

	return (floatsqroot((fX * fX) + (fY * fY) + (fZ * fZ)) * 100);
}


public OnPlayerUpdate(playerid)
{
	new vehicleid = GetPlayerVehicleID(playerid);

	GetVehicleHealth(vehicleid, health);

	if(pojazd[vehicleid][v_crash_Health] > health && floatabs(pojazd[vehicleid][v_crash_Health] - health) >= POTENTIAL_CRASH_DAMAGE && floatabs(pojazd[vehicleid][v_crash_Speed] - Callback_GetSpeed(vehicleid)) >= 5.0)
	{
		CallLocalFunction("OnPlayerCrashVehicle", "iif", playerid, vehicleid, floatsub(pojazd[vehicleid][v_crash_Health], health));
	}
	pojazd[vehicleid][v_crash_Health] = health;
	pojazd[vehicleid][v_crash_Speed] = Callback_GetSpeed(vehicleid);
	return 1;
}