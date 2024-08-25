new HavingBall[MAX_PLAYERS];
new AnimBasket[MAX_PLAYERS];
new BasketBall = -1;
new BallStatus;
new Baller;
new ShootingBall;
new BallBounce;
new LastBasketShooter = -1;

#define POSKOSZ_POZYCJA_Z 426.5665//spisywać to przez /save
#define POSKOSZ_POZYCJA_ZLOADER POSKOSZ_POZYCJA_Z-0.8//nie zmieniać
#define POSKOSZ_PILKA 3761.4827,-1781.2800, POSKOSZ_POZYCJA_ZLOADER
//pozycja kosza 1.
#define POSKOSZ_KOSZ1X 3745.6602
#define POSKOSZ_KOSZ1Y -1781.3259
//wrzuty.
#define POSKOSZ_KOSZ1XUP POSKOSZ_KOSZ1X
#define POSKOSZ_KOSZ1YUP POSKOSZ_KOSZ1Y
//pozycja kosza 2.
#define POSKOSZ_KOSZ2X 3777.1714
#define POSKOSZ_KOSZ2Y -1781.3508
//wrzuty.
#define POSKOSZ_KOSZ2XUP POSKOSZ_KOSZ2X
#define POSKOSZ_KOSZ2YUP POSKOSZ_KOSZ2Y
//up
#define POSKOSZ_PILKAUP POSKOSZ_POZYCJA_Z+2.5


new Float:basket_areaMinMax[4] = {3742.9404, -1766.0006, 3779.7996, -1793.5217};
new basketball_area;

stock Init_BasketBall()
{
	Baller = 999;
	PHY_CreateWall(3777.5428, -1780.5581, 3777.5271, -1782.2580, 0.07, 428.4722, 429.8802);//kosz 1
	PHY_CreateWall(3745.3184, -1782.0923, 3745.3003, -1780.4141, 0.07, 428.4634, 429.8802);//kosz 2
	PHY_CreateCylinder(3744.6247, -1781.2494, 0.4, 0.8, 425.5978, 428.7578);//słupek kosza
	PHY_CreateCylinder(3778.2056, -1781.4098, 0.4, 0.8, 425.5978, 428.7578);//słupek kosza
	PHY_CreateArea(basket_areaMinMax[0], basket_areaMinMax[1], basket_areaMinMax[2], basket_areaMinMax[3]);//teren koszykówki
	basketball_area = CreateDynamicCuboid(basket_areaMinMax[0], basket_areaMinMax[1], -FLOAT_INFINITY, basket_areaMinMax[2], basket_areaMinMax[3], FLOAT_INFINITY, LUNAPARK_VWOFFSET, 10);

	CreateBasketBall();
	BasketBall_InitPhysics();
	new sterowanie[1024];
	format(sterowanie, 1024, ""COL_EASY"["COL_LIME"STEROWANIE"COL_EASY"]"COL_WHITE"");
	format(sterowanie, 1024, "%s\n"COL_GREEN"C (kucanie)"COL_EASY" - Obrona/Przyjęcie/Zatrzymanie się", sterowanie);
	format(sterowanie, 1024, "%s\n"COL_GREEN"LPM"COL_EASY" - Strzał do kosza/Podanie", sterowanie);
	CreateDynamic3DTextLabel(sterowanie, -1, 3761.4531,-1770.0101,426.5565-0.7, 10.0);
	return 1;
}

stock CreateBasketBall()
{
	if(BasketBall != -1) DestroyObject(BasketBall);
	BasketBall = CreateObject(2114, POSKOSZ_PILKA, 0, 0, 96);
	return 1;
}

stock DestroyBasketBall()
{
	if(BasketBall != -1)
	{
		DestroyObject(BasketBall);
		PHY_DeleteObject(BasketBall);
		BasketBall = -1;
	}
	return 1;
}

stock BasketBall_InitPhysics()
{
	if(BasketBall != -1)
	{
		PHY_InitObject(BasketBall, 2114, 1.0, 0.152039);
		PHY_RollObject(BasketBall);
		PHY_SetObjectFriction(BasketBall, 7.0);
		PHY_SetObjectAirResistance(BasketBall, 0.2);
		PHY_SetObjectGravity(BasketBall, 10.0);
		PHY_SetObjectZBound(BasketBall, _, _, 0.8);
		return 1;
	}
	return 0;
}

stock BasketBall_DeletePhysics()
{
	if(BasketBall != -1)
	{
		PHY_DeleteObject(BasketBall);
		return 1;
	}
	return 0;
}

forward Process_BasketBall();//1 sek
public Process_BasketBall()
{
	if(!BasketBallInValidArea())
	{
		RespawnBasketBall();
	}
	return 1;
}

forward BallDown();
public BallDown()
{
	/*new Float:x, Float:y, Float:z;
	GetObjectPos(BasketBall, x, y, z);
	new Float:a;
	new Float:x2, Float:y2;
	GetPlayerPos(playerid, x2, y2, a);
	GetPlayerFacingAngle(playerid, a);
	x2 += (16 * floatsin(-a, degrees));
	y2 += (16 * floatcos(-a, degrees));
	MoveObject(BasketBall, x2, y2, oldz-0.8, 10.0+random(3));*/
	Baller = 999;
	ShootingBall = 0;
	BallBounce = 1;
	return 1;
}

forward BallDown2(playerid);
public BallDown2(playerid)
{
	//MoveObject(BasketBall, POSKOSZ_KOSZ1X,POSKOSZ_KOSZ1Y,POSKOSZ_POZYCJA_Z-0.8, 10.0+random(3));
	CreateBasketBall();
	BasketBall_InitPhysics();
	SetObjectPos(BasketBall, POSKOSZ_KOSZ1X,POSKOSZ_KOSZ1Y,POSKOSZ_PILKAUP);
	Baller = 999;
	ShootingBall = 0;
	GameTextForPlayer(playerid, "~g~!TRAFIONY!", 3000, 3);
	BallBounce = 1;
	new str[128];
	format(str, sizeof(str), "** piłka trafiła do kosza ((%s))", GetICName(playerid));
	SendNearByMessage(playerid, 0x6082B6FF, str, 20);
	return 1;
}

forward BallDown3(playerid);
public BallDown3(playerid)
{
	//MoveObject(BasketBall, POSKOSZ_KOSZ2X,POSKOSZ_KOSZ2Y,POSKOSZ_POZYCJA_Z-0.8, 10.0+random(3));
	CreateBasketBall();
	BasketBall_InitPhysics();
	SetObjectPos(BasketBall, POSKOSZ_KOSZ2X,POSKOSZ_KOSZ2Y,POSKOSZ_PILKAUP);
	Baller = 999;
	ShootingBall = 0;
	GameTextForPlayer(playerid, "~g~!TRAFIONY!", 3000, 3);
	BallBounce = 1;
	new str[128];
	format(str, sizeof(str), "** piłka trafiła do kosza ((%s))", GetICName(playerid));
	SendNearByMessage(playerid, 0x6082B6FF, str, 20);
	return 1;
} 

forward ShootMiss(playerid, Float:pow);
public ShootMiss(playerid, Float:pow)
{
	//MoveObject(BasketBall, POSKOSZ_KOSZ1XUP+random(2), POSKOSZ_KOSZ1YUP+random(2), POSKOSZ_PILKAUP+random(2), 12.5+random(4));
	new Float:x2, Float:y2;
	GetXYInFrontOfPlayer(playerid, x2, y2, 0.8);
	CreateBasketBall();
	BasketBall_InitPhysics();
	SetObjectPos(BasketBall, x2, y2, 3.5);
	ShotFrontBasketBall(playerid, pow);
	ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
	ShootingBall = 0;
	Baller = 999;
	BallBounce = 1;
	HavingBall[playerid] = 0;
	//GameTextForPlayer(playerid, "~r~!NIETRAFIONY!", 3000, 3);
	return 1;
}

forward ShootMiss2(playerid, Float:pow);
public ShootMiss2(playerid, Float:pow)
{
	//MoveObject(BasketBall, POSKOSZ_KOSZ2XUP+random(2),POSKOSZ_KOSZ2YUP+random(2),POSKOSZ_PILKAUP+random(2), 12.5+random(4));
	new Float:x2, Float:y2;
	GetXYInFrontOfPlayer(playerid, x2, y2, 0.8);
	CreateBasketBall();
	BasketBall_InitPhysics();
	SetObjectPos(BasketBall, x2, y2, 3.5);
	ShotFrontBasketBall(playerid, pow);
	ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
	ShootingBall = 0;
	Baller = 999;
	BallBounce = 1;
	HavingBall[playerid] = 0;
	//GameTextForPlayer(playerid, "~r~!NIETRAFIONY!", 3000, 3);
	return 1;
}


task delay_ClearAnim(playerid)
{
	ClearAnimations(playerid);
	return 1;
}

public OnObjectMoved(objectid)
{
	if(objectid != BasketBall) return 1;
	new i = Baller;
	if(i > MAX_PLAYERS) return 1;
	if(ShootingBall == 2)
	{
		BallDown2(i);
		return 1;
	}
	else if(ShootingBall == 3)
	{
		BallDown3(i);
		return 1;
	}
	else if(ShootingBall == 6)
	{
		ApplyAnimation(i,"BSKTBALL","BBALL_walk",4.1,1,1,1,1,1);
		HavingBall[i] = 1;
		AnimBasket[i] = 0;
	}
	if(BallBounce == 1)
	{
		new Float:x, Float:y, Float:z;
		GetObjectPos(BasketBall, x, y, z);
		MoveObject(BasketBall, x, y, z+1.2, 4);
		BallBounce = 2;
	}
	else if(BallBounce == 2)
	{
		new Float:x, Float:y, Float:z;
		GetObjectPos(BasketBall, x, y, z);
		MoveObject(BasketBall, x, y, z-1.2, 4);
		BallBounce = 3;
	}
	else if(BallBounce == 3)
	{
		new Float:x, Float:y, Float:z;
		GetObjectPos(BasketBall, x, y, z);
		MoveObject(BasketBall, x, y, z+0.8, 4);
		BallBounce = 4;
	}
	else if(BallBounce == 4)
	{
		new Float:x, Float:y, Float:z;
		GetObjectPos(BasketBall, x, y, z);
		MoveObject(BasketBall, x, y, z-0.8, 4);
		BallBounce = 5;
	}
	else if(BallBounce == 5)
	{
		new Float:x, Float:y, Float:z;
		GetObjectPos(BasketBall, x, y, z);
		MoveObject(BasketBall, x, y, z+0.5, 4);
		BallBounce = 6;
	}
	else if(BallBounce == 6)
	{
		new Float:x, Float:y, Float:z;
		GetObjectPos(BasketBall, x, y, z);
		MoveObject(BasketBall, x, y, z-0.5, 4);
		BallBounce = 7;
	}
	else if(BallBounce == 7)
	{
		new Float:x, Float:y, Float:z;
		GetObjectPos(BasketBall, x, y, z);
		MoveObject(BasketBall, x, y, z+0.2, 4);
		BallBounce = 8;
	}
	else if(BallBounce == 8)
	{
		new Float:x, Float:y, Float:z;
		GetObjectPos(BasketBall, x, y, z);
		MoveObject(BasketBall, x, y, z-0.2, 4);
		BallBounce = 0;
	}
	if(!HavingBall[i]) return 1;
	new Keys, ud, lr;
	GetPlayerKeys(i, Keys, ud, lr);
	if(AnimBasket[i])
	{
		switch(BallStatus)
		{
			case 0:
			{
				BallStatus = 1;
				new Float:x, Float:y, Float:z;
				GetPlayerPos(i, x, y, z);
				StopObject(BasketBall);
				new Float:x2, Float:y2;
				GetXYInFrontOfPlayer(i, x2, y2, 0.4);
				MoveObject(BasketBall, x2, y2, z+0.1, 5.5);
			}
			case 1:
			{
				BallStatus = 0;
				new Float:x, Float:y, Float:z;
				GetPlayerPos(i, x, y, z);
				StopObject(BasketBall);
				new Float:x2, Float:y2;
				GetXYInFrontOfPlayer(i, x2, y2, 0.4);
				MoveObject(BasketBall, x2, y2, z-0.8, 5.5);
			}
		}
		return 1;
	}
	if(Keys & KEY_SPRINT)
	{
		ApplyAnimation(i,"BSKTBALL","BBALL_run",4.1,1,1,1,1,1);
		switch(BallStatus)
		{
			case 0:
			{
				BallStatus = 1;
				new Float:x, Float:y, Float:z;
				GetPlayerPos(i, x, y, z);
				StopObject(BasketBall);
				new Float:x2, Float:y2;
				GetXYInFrontOfPlayer(i, x2, y2, 1.5);
				MoveObject(BasketBall, x2, y2, z+0.1, 8);
			}
			case 1:
			{
				BallStatus = 0;
				new Float:x, Float:y, Float:z;
				GetPlayerPos(i, x, y, z);
				StopObject(BasketBall);
				new Float:x2, Float:y2;
				GetXYInFrontOfPlayer(i, x2, y2, 1.5);
				MoveObject(BasketBall, x2, y2, z-0.8, 8);
			}
		}
		return 1;
	}
	else
	{
		ApplyAnimation(i,"BSKTBALL","BBALL_walk",4.1,1,1,1,1,1);
	}
	switch(BallStatus)
	{
		case 0:
		{
			BallStatus = 1;
			new Float:x, Float:y, Float:z;
			GetPlayerPos(i, x, y, z);
			StopObject(BasketBall);
			new Float:x2, Float:y2;
			GetXYInFrontOfPlayer(i, x2, y2, 1.2);
			MoveObject(BasketBall, x2, y2, z+0.1, 5);
		}
		case 1:
		{
			BallStatus = 0;
			new Float:x, Float:y, Float:z;
			GetPlayerPos(i, x, y, z);
			StopObject(BasketBall);
			new Float:x2, Float:y2;
			GetXYInFrontOfPlayer(i, x2, y2, 1.2);
			MoveObject(BasketBall, x2, y2, z-0.8, 5);
		}
	}
	return 1;
}

stock BasketBallInValidArea()
{
	new Float:bsPos[3];
	GetObjectPos(BasketBall, bsPos[0], bsPos[1], bsPos[2]);
	if(IsPointInDynamicArea(basketball_area, bsPos[0], bsPos[1], bsPos[2])) return 1;
	return 0;
}

stock RespawnBasketBall()
{
	for(new i = PlayerPoolSize(); i != -1; i--)
	{
		if(!gracz[i][loggedin]) continue;
		if(gracz[i][status_lunapark] != LPARK_BASKETBALL) continue;
		SendClientMessage(i, -1, "(("COL_LIME"Piłka została zrespawnowana - "COL_BLUE"środek"COL_LIME"."COL_WHITE"))");
		if(HavingBall[i] != 0)
		{
			HavingBall[i] = 0;
			ApplyAnimation(i, "CARRY", "crry_prtial", 1.0, 0, 0, 0, 0, 0);
		}
		if(AnimBasket[i] != 0)
		{
			AnimBasket[i] = 0;
		}
		if(HavingBall[i]) Baller = 999;
	}
	Baller = 999;
	BasketBall_DeletePhysics();
	CreateBasketBall();
	BasketBall_InitPhysics();
	return 1;
}

stock Basket_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(gracz[playerid][status_lunapark] != LPARK_BASKETBALL) return 1;
	if ((newkeys & KEY_CROUCH) && !(oldkeys & KEY_CROUCH) && !IsPlayerInAnyVehicle(playerid))
	{
		if(HavingBall[playerid])
		{
			ApplyAnimation(playerid,"BSKTBALL","BBALL_idleloop",4.1,1,1,1,1,1);
		}
		else
		{
			ApplyAnimation(playerid,"BSKTBALL","BBALL_def_loop",4.0,1,0,0,0,0);
		}
		AnimBasket[playerid] = 1;
	}
	if (!(newkeys & KEY_CROUCH) && (oldkeys & KEY_CROUCH) && !IsPlayerInAnyVehicle(playerid))
	{
		ClearAnimations(playerid);
		AnimBasket[playerid] = 0;
	}
	if(newkeys & KEY_FIRE && !IsPlayerInAnyVehicle(playerid))
	{
		if(!HavingBall[playerid])
		{
			new Float:x, Float:y, Float:z;
			GetObjectPos(BasketBall, x, y, z);
			if(IsPlayerInRangeOfPoint(playerid, 1.5, x, y, z))//podniesienie piłki
			{
				BasketBall_DeletePhysics();
				CreateBasketBall();
				SetObjectPos(BasketBall, x, y, z);
				HavingBall[playerid] = 1;
				ApplyAnimation(playerid,"BSKTBALL","BBALL_pickup",4.0,0,0,0,0,0);
				if(Baller != 999)
				{
					HavingBall[Baller] = 0;
					ClearAnimations(Baller);
					ApplyAnimation(Baller, "CARRY", "crry_prtial", 1.0, 0, 0, 0, 0, 0);
					ApplyAnimation(playerid,"BSKTBALL","BBALL_walk",4.1,1,1,1,1,1);
				}
				Baller = playerid;
				BallStatus = 1;
				new Float:x2, Float:y2;
				GetXYInFrontOfPlayer(playerid, x2, y2, 0.8);
				GetPlayerPos(playerid, x, y, z);
				StopObject(BasketBall);
				MoveObject(BasketBall, x2, y2, z, 2.5);
				AnimBasket[playerid] = 0;
				BallBounce = 0;
			}
		}
		else
		{
			if(IsPlayerInRangeOfPoint(playerid, 1, POSKOSZ_KOSZ1X,POSKOSZ_KOSZ1Y,POSKOSZ_POZYCJA_ZLOADER))//rzut przy koszu
			{
				MoveObject(BasketBall, POSKOSZ_KOSZ1XUP,POSKOSZ_KOSZ1YUP,POSKOSZ_PILKAUP, 7.5);
				SetPlayerPos(playerid, POSKOSZ_KOSZ1X,POSKOSZ_KOSZ1Y,POSKOSZ_POZYCJA_ZLOADER+0.8);
				ApplyAnimation(playerid,"BSKTBALL","BBALL_Dnk",4.0,1,0,0,0,0);
				HavingBall[playerid] = 0;
				SetTimerEx("delay_ClearAnim", 1100, 0, "d", playerid);
				SetTimerEx("BallDown2", 1100, 0, "d", playerid);
				return 1;
			}
			
			else if(IsPlayerInRangeOfPoint(playerid, 4, POSKOSZ_KOSZ1X,POSKOSZ_KOSZ1Y,POSKOSZ_POZYCJA_ZLOADER) && IsPlayerFacingPoint(playerid, 20, POSKOSZ_KOSZ1X,POSKOSZ_KOSZ1Y,POSKOSZ_POZYCJA_ZLOADER))
			{
				new rand = random(1);
				if(rand == 0)
				{
					MoveObject(BasketBall, POSKOSZ_KOSZ1XUP,POSKOSZ_KOSZ1YUP,POSKOSZ_PILKAUP, 7.5+random(4));
					ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
					ShootingBall = 2;
					HavingBall[playerid] = 0;
					return 1;
				}
				ShootMiss(playerid, 4.5);
				return 1;
			}
			
			else if(IsPlayerInRangeOfPoint(playerid, 7, POSKOSZ_KOSZ1X,POSKOSZ_KOSZ1Y,POSKOSZ_POZYCJA_ZLOADER) && IsPlayerFacingPoint(playerid, 20, POSKOSZ_KOSZ1X,POSKOSZ_KOSZ1Y,POSKOSZ_POZYCJA_ZLOADER))
			{
				new rand = random(2);
				if(rand == 0)
				{
					MoveObject(BasketBall, POSKOSZ_KOSZ1XUP,POSKOSZ_KOSZ1YUP,POSKOSZ_PILKAUP, 9.0+random(4));
					ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
					ShootingBall = 2;
					HavingBall[playerid] = 0;
					return 1;
				}
				ShootMiss(playerid, 5.7);
				return 1;
			}
			else if(IsPlayerInRangeOfPoint(playerid, 10, POSKOSZ_KOSZ1X,POSKOSZ_KOSZ1Y,POSKOSZ_POZYCJA_ZLOADER) && IsPlayerFacingPoint(playerid, 20, POSKOSZ_KOSZ1X,POSKOSZ_KOSZ1Y,POSKOSZ_POZYCJA_ZLOADER))
			{
				new rand = random(3);
				if(rand == 0)
				{
					MoveObject(BasketBall, POSKOSZ_KOSZ1XUP,POSKOSZ_KOSZ1YUP,POSKOSZ_PILKAUP, 11.5+random(4));
					ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
					ShootingBall = 2;
					HavingBall[playerid] = 0;
					return 1;
				}
				ShootMiss(playerid, 6.6);
				return 1;
			}
			else if(IsPlayerInRangeOfPoint(playerid, 1, POSKOSZ_KOSZ2X,POSKOSZ_KOSZ2Y,POSKOSZ_POZYCJA_ZLOADER))//rzut przy koszu 2
			{
				MoveObject(BasketBall, POSKOSZ_KOSZ2XUP,POSKOSZ_KOSZ2YUP,POSKOSZ_PILKAUP, 7.5);
				SetPlayerPos(playerid, POSKOSZ_KOSZ2X,POSKOSZ_KOSZ2Y,POSKOSZ_POZYCJA_ZLOADER+0.8);
				ApplyAnimation(playerid,"BSKTBALL","BBALL_Dnk",4.0,1,0,0,0,0);
				HavingBall[playerid] = 0;
				SetTimerEx("delay_ClearAnim", 800, 0, "d", playerid);
				SetTimerEx("BallDown3", 1100, 0, "d", playerid);
				return 1;
			}
			else if(IsPlayerInRangeOfPoint(playerid, 4, POSKOSZ_KOSZ2X,POSKOSZ_KOSZ2Y,POSKOSZ_POZYCJA_ZLOADER) && IsPlayerFacingPoint(playerid, 20, POSKOSZ_KOSZ2X,POSKOSZ_KOSZ2Y,POSKOSZ_POZYCJA_ZLOADER))
			{

				new rand = random(1);
				if(rand == 0)
				{
					MoveObject(BasketBall, POSKOSZ_KOSZ2XUP,POSKOSZ_KOSZ2YUP,POSKOSZ_PILKAUP, 7.5+random(4));
					ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
					ShootingBall = 3;
					HavingBall[playerid] = 0;
					return 1;
				}
				ShootMiss2(playerid, 4.5);
				return 1;
			}
			else if(IsPlayerInRangeOfPoint(playerid, 7, POSKOSZ_KOSZ2X,POSKOSZ_KOSZ2Y,POSKOSZ_POZYCJA_ZLOADER) && IsPlayerFacingPoint(playerid, 20, POSKOSZ_KOSZ2X,POSKOSZ_KOSZ2Y,POSKOSZ_POZYCJA_ZLOADER))
			{
				new rand = random(2);
				if(rand == 0)
				{
					MoveObject(BasketBall, POSKOSZ_KOSZ2XUP,POSKOSZ_KOSZ2YUP,POSKOSZ_PILKAUP, 9.0+random(4));
					ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
					ShootingBall = 3;
					HavingBall[playerid] = 0;
					return 1;
				}
				ShootMiss2(playerid, 5.7);
				return 1;
			}
			else if(IsPlayerInRangeOfPoint(playerid, 10, POSKOSZ_KOSZ2X,POSKOSZ_KOSZ2Y,POSKOSZ_POZYCJA_ZLOADER) && IsPlayerFacingPoint(playerid, 20, POSKOSZ_KOSZ2X,POSKOSZ_KOSZ2Y,POSKOSZ_POZYCJA_ZLOADER))
			{
				new rand = random(3);
				if(rand == 0)
				{
					MoveObject(BasketBall, POSKOSZ_KOSZ2XUP,POSKOSZ_KOSZ2YUP,POSKOSZ_PILKAUP, 11.5+random(4));
					ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
					ShootingBall = 3;
					HavingBall[playerid] = 0;
					return 1;
				}
				ShootMiss2(playerid, 6.6);
				return 1;
			}
			for(new i = PlayerPoolSize(); i != -1; i--)//podawanie
			{
				if(IsPlayerConnected(i))
				{
					if(IsPlayerFacingPlayer(playerid, i, 15))
					{
						new Float:x, Float:y, Float:z;
						GetPlayerPos(i, x, y, z);
						if(IsPlayerInRangeOfPoint(playerid, 20.0, x, y, z))
						{
							Baller = i;
							HavingBall[playerid] = 0;
							ClearAnimations(playerid);
							ApplyAnimation(playerid,"BSKTBALL","BBALL_def_loop",4.0,1,0,0,0,0);
							SetTimerEx("delay_ClearAnim", 700, 0, "d", playerid);
							MoveObject(BasketBall, x, y, z, 13+random(4));
							AnimBasket[i] = 0;
							ShootingBall = 6;
							ApplyAnimation(i,"BSKTBALL","BBALL_def_loop",4.0,1,0,0,0,0);
							return 1;
						}
					}
				}
			}
			HavingBall[playerid] = 0;
			new Float:x2, Float:y2;
			GetXYInFrontOfPlayer(playerid, x2, y2, 0.8);
			BallDown();
			CreateBasketBall();
			BasketBall_InitPhysics();
			SetObjectPos(BasketBall, x2, y2, 3.5);
			ShotFrontBasketBall(playerid, 7.0);
			ApplyAnimation(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
			ShootingBall = 0;
		}
	}
	return 1;
}


task PHY_BasketBall(objectid)
{
	if(LastBasketShooter != -1)
	{
		new Float:phX, Float:phY, Float:phZ;
		GetObjectPos(objectid, phX, phY, phZ);
		if(GetDistanceBetweenPoints(phX, phY, phZ, POSKOSZ_KOSZ1XUP,POSKOSZ_KOSZ1YUP,POSKOSZ_PILKAUP) < 0.2)
		{
			PHY_SetObjectVelocity(objectid, 0.0, 0.0, 0.0);
			SetObjectPos(objectid, POSKOSZ_KOSZ1XUP,POSKOSZ_KOSZ1YUP,POSKOSZ_PILKAUP);
			GameTextForPlayer(LastBasketShooter, "~g~!TRAFIONY!", 3000, 3);
			new str[128];
			format(str, sizeof(str), "** piłka trafiła do kosza ((%s))", GetICName(LastBasketShooter));
			SendNearByMessage(LastBasketShooter, 0x6082B6FF, str, 20);

			LastBasketShooter = -1;
		}
		else if(GetDistanceBetweenPoints(phX, phY, phZ, POSKOSZ_KOSZ2XUP,POSKOSZ_KOSZ2YUP,POSKOSZ_PILKAUP) < 0.2)
		{
			PHY_SetObjectVelocity(objectid, 0.0, 0.0, 0.0);
			SetObjectPos(objectid, POSKOSZ_KOSZ2XUP,POSKOSZ_KOSZ2YUP,POSKOSZ_PILKAUP);
			GameTextForPlayer(LastBasketShooter, "~g~!TRAFIONY!", 3000, 3);
			new str[128];
			format(str, sizeof(str), "** piłka trafiła do kosza ((%s))", GetICName(LastBasketShooter));
			SendNearByMessage(LastBasketShooter, 0x6082B6FF, str, 20);

			LastBasketShooter = -1;
		}
	}
	return 1;
}


stock ShotFrontBasketBall(playerid, Float:power)
{
	if(power > 20) power = 20;
	if(power < 0) return 1;
	new
		Float:angle,
		Float:vx, Float:vy, Float:vz;
	GetPlayerFacingAngle(playerid, angle);
	vx = power * floatsin(-angle, degrees),
	vy = power * floatcos(-angle, degrees);
	vz = power / 0.6;
	PHY_SetObjectVelocity(BasketBall, vx, vy, vz);
	LastBasketShooter = playerid;
	return 1;
}