//**************SKRYPT Highway Life BY SEBAQQ6**************************** 
#define VER "Truck HL (build:%d)"
#pragma dynamic 8388608
#pragma disablerecursion
//********************INCLUDE******************************(pamietaj, przy aktualizacji include zeby je dostosować w a_samp: "includes/a_players.inc", "includes/a_actor.inc")
#include "qqbuild.inc"
#include "includes/a_samp.inc"
#include "includes/a_zones.inc"
#include "includes/timerfix.inc"
#include "includes/physics.inc"
//#include "includes/profiler.inc"
#include "includes/streamer.inc"
#include "includes/FCNPC.inc"
#include "includes/Pawn.RakNet.inc" 
#include "includes/sscanf2.inc"
#include "includes/a_mysql.inc"
#include "includes/Pawn.CMD.inc"
#include "includes/sampvoice.inc"
//#include "includes/RouteConnector.inc"
#include "includes/mapandreas.inc"
#include "includes/merrandom.inc"
#include "includes/nex-ac.inc"
#include "includes/DialogCenter.inc"
#include "includes/easyDialog.inc"
#include "includes/mSelection.inc"
#include "includes/playerprogress.inc"
#include "includes/zvehcomp.inc"
#include "includes/bcrypt.inc"
//#include "includes/restorebuilding.inc"
//********************MODUŁY*****************************
#include "modules/define.inc"//Definicje.
#include "modules/ram.inc"//Szufladki dla danych na których pracuje skrypt
#include "modules/textdraw.inc"//Moduł odpowiadający za obiekty 
#include "modules/auth.inc"//Baza danych/Autoryzacja użytkownika
#include "modules/utils.inc"//Przydatne funkcje
#include "modules/rgps.inc"//Moduł obsługujący zdalny GPS
#include "modules/player.inc"//Moduł gracza
#include "modules/npc.inc"//Moduł botów
#include "modules/items.inc"//Przedmioty
#include "modules/inventory.inc"//Skrypt EQ
#include "modules/useitem.inc"//Skrypty przedmiotów
#include "modules/loot.inc"//Skrypt przedmiotów leżących na ziemi
#include "modules/keys.inc"//Moduł klawiszy
#include "modules/removebuiliding.inc"//Moduł usuwający obiekty GTA SA
#include "modules/objects.inc"//Moduł odpowiadający za obiekty 
#include "modules/chat.inc"//Obsługa czatu
#include "modules/vehicles.inc"//Moduł pojazdów
#include "modules/pickups.inc"//Moduł pickupów
#include "modules/transport_courier.inc"//Moduł kurierów
#include "modules/transport_freelancer.inc"//Moduł wolnych kierowców
#include "modules/rpc.inc"//Moduł do przechwytywania pakietów RPC
#include "modules/fractions.inc"//Moduł frakcji
#include "modules/commands.inc"//Moduł komend
#include "modules/doors.inc"//System przejść
#include "modules/firesystem.inc"//System pożarów
#include "modules/nick_label.inc"//System 3D textów nad głowami graczy
#include "modules/admin.inc"//Panel administratora
#include "modules/sms.inc"//Moduł osiłownibsługujący płatności sms
#include "modules/gym.inc"//Moduł 
#include "modules/combine_mode.inc"//Moduł obsługujący tryb kombinacji
#include "modules/house.inc"//Moduł obsługujący domki
#include "modules/company.inc"//Moduł obsługujący firmy
#include "modules/voice.inc"//Moduł obsługujący plugin głosowy
#include "modules/anim.inc"//Moduł obsługujący animacje
#include "modules/speedcamera.inc"//Moduł obsługujący fotoradary
#include "modules/fireworks.inc"//Moduł obsługujący fajerwerki
#include "modules/football.inc"//Moduł obsługujący piłkę nożną
#include "modules/basketball.inc"//Moduł obsługujący koszykówkę
#include "modules/pool.inc"//Moduł obsługujący stół bilardowy
#include "modules/lunapark.inc"//Moduł obsługujący lunapark
#include "modules/eventpanel.inc"//Moduł obsługujący lunapark
#include "modules/rope.inc"//Moduł obsługujący zjazd na linie
#include "modules/asg.inc"//Moduł obsługujący ASG
#include "modules/ognisko.inc"//Moduł obsługujący ogniska
#include "modules/trafficlights.inc"//Moduł obsługujący sygnalizacje świetlne
//*******************BRUDNOPIS***************************
/*
ZNAKI SPECJALNE: §°¤«©®•»†‡‰™
 pawncc
8zdjS65mgdLHTMve
//misje 
adr i wypadki
dialog rozmowny przy poborze towaru
tymczasowy owner
tryby służby policja
wyznacz miejsce zatrzymania(lizak) - system dla policji
mini misje na mapie rekordy
respawn popraw
kurs godziny (specjalne kursy)
daj klucze
- CZY CHCESZ PRZERWAĆ RESPAWN OSTATNIO UŻYWANEGO AUTA
- bug z przeparkowaniem rejsteracja per player i firmowych
- TABELKA PO LEWEJ Z RESPAWNEM AUT GRACZA
- OPŁACANIE DOMKÓW
http://sebaqq6.pl/ss.php?screen=qq_21_06_2019_22-56-33.png
szukanie duplikatów:
SELECT 
    name, 
    COUNT(*)
FROM
    zone_names
GROUP BY name
HAVING COUNT(*) > 1;
Zapamietaj! SetVehicleHealth buguje onvehicledeath (wybuch)
IP rejestracji: 88.156.143.237
Ostatnie znane IP: 195.191.163.29
UPDATE `pojazdy` SET `model`=459 WHERE `model`=573 AND `owner_type`=0 AND `owner`=8; // dune na topfun
UPDATE `pojazdy` SET `model`=428 WHERE `model`=524 AND `owner_type`=0 AND `owner`=8; //cement na securicar
przyjaciele hl
WHERE `id`=1610 OR `id`=224 OR `id`=1379 OR `id`=1071 OR `id`=1490 OR `id`=108 OR `id`=76 OR `id`=102 OR `id`=103 OR `id`=2486 OR `id`=54 OR `id`=72 OR `id`=50 OR `id`=84 OR `id`=2251 OR `id`=2147 OR `id`=2621 OR `id`=58 OR `id`=23 OR `id`=697;
<20:12:41> "ĐAKU.": L: highwaylifemanagement@gmail.com
H: hlforever1243
https://wiki.sa-mp.com/wiki/AddThousandsSeparators


camera shake
co serie wchodzi dmg, od 0.1dmg-60.0= -0.25
powyżej 60. 0.5
styl walki 16, od 60 wzwyż
*/
//*********************SKRYPT*****************************
main(){}

function1() {
    function2();
}

function2() {
    new buf[10];
    fread(File:123, buf);
}

CMD:crashthisshit(playerid, params[])
{
	if(gracz[playerid][admin_duty] < 4) return 0;
	printf("crashuje...");
	function1();
	return 1;
}

public OnGameModeInit()
{
	//Profiler_Start();
	format(serwer[wersja], 64, VER, QQBUILD);//generowanie wersji
	print("****************SKRYPT Highway Life - WCZYTYWANIE****************");
	print("SA:MP Truck GameMode - Coded by sebaqq6.pl");
	print("Copyright  2017 ©");
	print("Skrypt serwera TRUCK dla projektu Highway Life");
	printf("==> Kompilacja (build): %s <==", serwer[wersja]);
	print("****************SKRYPT Highway Life - WCZYTYWANIE****************");
	//function1();
	SetGameModeText(serwer[wersja]);
	SendRconCommand("mapname Highway Life");
	AddPlayerClass(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	LimitPlayerMarkerRadius(99999.0);
	GetServerVarAsString("password", serwer[srv_password], 32);
	printf("[SRV_VAR] password: %s", serwer[srv_password]);
	GetServerVarAsString("hostname", serwer[srv_customhostname], 128);
	printf("[SRV_VAR] custom_hostname: %s", serwer[srv_customhostname]);
	format(serwer[srv_customhostname], 128, "[0.3DL] HL - Trwa uruchamianie...");
	SendRconCommand("password loadhlgamemode");
	//LimitPlayerMarkerRadius(99999.0);
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_GLOBAL);
	DisableInteriorEnterExits();
	EnableVehicleFriendlyFire();
	EnableStuntBonusForAll(0);
	//Streamer_ToggleChunkStream(1);
	//MapAndreas_Init(MAP_ANDREAS_MODE_FULL, "scriptfiles/SAfull.hmap");
	printf("MapAndreas_Init: %d", MapAndreas_Init(MAP_ANDREAS_MODE_MINIMAL, "scriptfiles/HLmin.hmap"));
	ShowNameTags(0);
	serwer[pogoda] = 14;
	SetWeather(serwer[pogoda]);
	serwer[time_timestamp] = gettime(serwer[time_hour], serwer[time_minute], serwer[time_second]);
	ConnectDB();//Łączenie z bazą danych
	//**czyszczenie kalkulatora - end
	SetTimer("ServerUpdate", 250, true);
	Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, VISIBLE_ITEMS);
	Process_AnnounceSCM(0);
	Process_HostName(0);
	new strTDVersion[64];
	#if defined DEBUGHL
	format(strTDVersion, 64, "~r~~h~~h~~h~(DEBUG) ~w~%s", serwer[wersja]);
	#else
	format(strTDVersion, 64, "~w~%s", serwer[wersja]);
	#endif
	UpdateScriptVersionTD(strTDVersion);//aktualizacja TD
	UnlockOptLocations();
	SetTimer("InitModules", 5000, false);
	//FallTree_Debug();//DEBUG Falltree
	//załadowanie cenzury
	new strCensor[126];
	new File:censorfile;
	if((censorfile = fopen("cenzura.txt",io_read)))
	{
		while(fread(censorfile,strCensor))
		{
			for(new i = 0, j = strlen(strCensor); i < j; i++) if(strCensor[i] == '\n' || strCensor[i] == '\r') strCensor[i] = '\0';
			Swears[num_censor_words] = strCensor;
			num_censor_words++;
		}
		fclose(censorfile);
	}
	/*
	for(new v; v < MAX_CARSPEC; v++)
	{
		//{"Landstalker", 400, F_ON, 75, 7.3, 3.7, 171},
		//if(!IsVehicleSalonBanned(pojazd_spec[v][vspec_model])) printf("%s %d", str_replace(" ", "_",  pojazd_spec[v][vspec_name]), CalcVehiclePrice(pojazd_spec[v][vspec_vmax], pojazd_spec[v][vspec_0100], pojazd_spec[v][vspec_tanksize]));
		if(IsVehicleSalonBanned(pojazd_spec[v][vspec_model]))
		{
			//printf("%s", pojazd_spec[v][vspec_name]);
			print("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
			printf("NAZWA: %s", pojazd_spec[v][vspec_name]);
			printf("CENA: %d$", CalcVehiclePriceEx(pojazd_spec[v][vspec_model]));
			printf("MODEL: %d", pojazd_spec[v][vspec_model]);
			if(pojazd_spec[v][vspec_fueltype] == F_PB) printf("PALIWO: PB");
			else if(pojazd_spec[v][vspec_fueltype] == F_ON) printf("PALIWO: ON");
			printf("POJEMNOSC ZBIORNIKA: %d litrow", pojazd_spec[v][vspec_tanksize]);
			printf("SPALANIE: %0.1f l/100", pojazd_spec[v][vspec_fuelconsumption]+0.01);
			printf("PRZYSPIESZENIE: %0.1fs", pojazd_spec[v][vspec_0100]+0.01);
			printf("V-MAX: %d KM/H", pojazd_spec[v][vspec_vmax]);
		}
		//if(strlen(pojazd_spec[v][vspec_name]) > _test_dlugosc) _test_dlugosc = strlen(pojazd_spec[v][vspec_name]);
	}
	*/
	CreatePickup(980, 1, 0.0, 0.0, -10000.0, 999);//PICKUP NULL - aby zająć ID 0
	//*************************************************************************************IKONY
	CreateDynamicMapIcon(XYZ_AUTOSZROT, 11, 0, .streamdistance = 1000.0, .style = MAPICON_GLOBAL);
	CreateDynamicMapIcon(XYZ_SALON, 55, 0, .streamdistance = 1000.0, .style = MAPICON_GLOBAL);
	CreateDynamicMapIcon(XYZ_TRUCKCENTER, 5, 0, .streamdistance = 1000.0, .style = MAPICON_GLOBAL);
	CreateDynamicMapIcon(XYZ_TRUCKSALON, 51, 0, .streamdistance = 1000.0, .style = MAPICON_GLOBAL);
	CreateDynamicMapIcon(XYZ_TRUCKSALON, 51, 0, .streamdistance = 1000.0, .style = MAPICON_GLOBAL);
	//*************************************************************************************POLYGONS/ZONES
	pol_lvairport = CreateDynamicPolygon(pol_lvairport_data);
	zone_sanandreas = CreateDynamicCuboid(-2904.1499, -2800.7571, -1000.0, 3062.8916, 2892.8152, FLOAT_INFINITY);
	#pragma unused zone_sanandreas
	#pragma unused pol_lvairport
	//*************************************************************************************3D TEXT LABEL
	CreateDynamic3DTextLabel("« "COL_BLUE"ZAKUP POJAZDU "COL_GREEN"»\n"COL_RED"• "COL_WHITE"Wciśnij "COL_GREEN"klawisz "COL_RED"Y"COL_WHITE" aby zakupić pojazd. "COL_RED"•", 0x009933FF, XYZ_SALON, 10.0);
	CreateDynamic3DTextLabel("« "COL_RED"INFO "COL_GREEN"»\n"COL_RED"• "COL_WHITE" Dostępne w salonie pojazdy są co jakiś czas "COL_LIME"zamieniane na inne"COL_WHITE". "COL_RED"•", 0x009933FF, XYZ_SALONTIP, 10.0);
	CreateDynamic3DTextLabel("« "COL_BLUE"ZAKUP POJAZDU "COL_GREEN"»\n"COL_RED"• "COL_WHITE"Wciśnij "COL_GREEN"klawisz "COL_RED"Y"COL_WHITE" aby zakupić pojazd. "COL_RED"•", 0x009933FF, XYZ_TRUCKSALON, 10.0);
	CreateDynamic3DTextLabel("« "COL_RED"EGZAMIN NA PRAWO JAZDY "COL_GREEN"»\n"COL_RED"• "COL_WHITE"Wpisz "COL_GREEN"/egzamin"COL_WHITE" aby przystąpić do egzaminu na prawo jazdy. "COL_RED"•", 0x009933FF, XYZ_PRAWKO, 25.0);
	new strWelcome[2048];
	strcat(strWelcome, "« "COL_DRVONLINE"Highway Life "COL_EASY"»");
	strcat(strWelcome, "\nWitaj szanowny graczu na naszym serwerze truck "COL_DRVONLINE"Highway Life"COL_EASY"!");
	strcat(strWelcome, "\nCieszymy się, że zechciałeś/aś odwiedzić nasz serwer!");
	strcat(strWelcome, "\nMamy nadzieje, że miło spędzisz u nas czas :)");
	strcat(strWelcome, "\nJeśli jesteś nowy, koniecznie zajrzyj pod "COL_RED"/pomoc"COL_EASY" - otrzymasz tam wszelką");
	strcat(strWelcome, "\npomoc, która pomoże Ci rozpocząć u nas swoją przygodę!");
	strcat(strWelcome, "\n"COL_ORANGE"Powodzenia i szerokiej drogi!!! :)");
	CreateDynamic3DTextLabel(strWelcome, 0xFFF1AFFF, XYZ_WELCOME, 10.0);
	CreateDynamicPickup(18631, 1, XYZ_WELCOME);
	//*************************************************************************************AKTORZY
	CreateActor(187, XYZR_SALONBOT);//SALON SAMOCHODOWY
	//salon truck aktorzy:
	CreateActor(187,2312.3467,1444.0763,10.8490,220.0719); // actortruck1
	CreateActor(187,2310.0085,1442.7317,10.8490,206.9118); // actortruck2
	CreateActor(187,2307.3953,1442.2803,10.8490,184.6649); // actortruck3
	CreateActor(187,2304.6604,1442.7748,10.8590,158.0313); // actortruck4
	CreateActor(187,2302.4080,1444.1093,10.8390,140.1712); // actortruck5
	//prawko
	CreateActor(187,1028.1563,1335.4565,10.9160,182.6049); // prawkoaktor 1
	CreateActor(187,1030.1044,1335.4469,10.9160,182.6049); // prawkoaktor 2
	CreateActor(187,1032.0094,1335.4658,10.9160,182.6049); // prawkoaktor 3
	CreateActor(187,1033.9396,1337.5773,10.9160,268.7723); // prawkoaktor 4
	CreateActor(187,1033.9481,1339.5112,10.9160,268.7723); // prawkoaktor 5
	CreateActor(187,1033.9126,1341.3553,10.9160,268.7723); // prawkoaktor 6
	//*************************************************************************************GPS NODE - PRACA NA ORYGINAŁACH
	//temp:
	//miejsca zaladunkowe vanów - debug script
	/*for(new d; d < MAX_VANLOADS; d++)
	{
		CreateDynamicMapIcon(load_place_van[d][0], load_place_van[d][1], load_place_van[d][2], 53, 0, .streamdistance = 300.0, .style = MAPICON_GLOBAL);
		CreatePickup(1254, 1, load_place_van[d][0], load_place_van[d][1], load_place_van[d][2]);
		CreateDynamic3DTextLabel("ZAŁADUNEK VAN HERE", 0x00FF00FF, load_place_van[d][0], load_place_van[d][1], load_place_van[d][2], 100.0);
	}*/
	//printf("poss: qIRmquxcpV | %d", udb_hash("qIRmquxcpV"));//364774401
	//printf("poss: 123456 | %d", udb_hash("123456"));//70123830
	/*printf("POLYGON - START=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
	new Float:veh_max_capacity = 200.0;
	new Float:veh_actualcargosize = 220.0;
	new Float:wynik = (veh_max_capacity/veh_actualcargosize)*100.0;
	printf("wynik; %d", floatround(wynik));
	printf("POLYGON - END=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
	*/

	//zveh_debug();
	//838.3120,682.5930,11.9060
	//1247
	/*new strSG_Bramka[1024];
	format(strSG_Bramka, 1024, ""COL_GREEN"« "COL_BLUE" Statusy pozostałych bramek "COL_GREEN"»");
	format(strSG_Bramka, 1024, "%s\n"COL_ORANGE"Kierowcy/Funkcjonariusze "COL_WHITE"[LV-San Fierro]"COL_ORANGE": "COL_BLUE"12"COL_ORANGE"/"COL_GREEN"1 "COL_RED"« [Tu jesteś]", strSG_Bramka);
	format(strSG_Bramka, 1024, "%s\n"COL_ORANGE"Kierowcy/Funkcjonariusze "COL_WHITE"[LV-Bone County]"COL_ORANGE": "COL_BLUE"3"COL_ORANGE"/"COL_GREEN"0", strSG_Bramka);
	format(strSG_Bramka, 1024, "%s\n"COL_ORANGE"Kierowcy/Funkcjonariusze "COL_WHITE"[LV-Los Santos]"COL_ORANGE": "COL_BLUE"7"COL_ORANGE"/"COL_GREEN"0", strSG_Bramka);
	format(strSG_Bramka, 1024, "%s\n"COL_RED"(("COL_GREEN"PPM "COL_GREY"- Teleport między bramkami"COL_RED"))", strSG_Bramka);
	format(strSG_Bramka, 1024, "%s\n"COL_RED"[Skrypt NIESKOŃCZONY! - Nie testować!]", strSG_Bramka);
	CreateDynamic3DTextLabel(strSG_Bramka, -1, 838.3120,682.5930,11.9060, 6.0);
	CreateDynamicPickup(1247, 1, 838.3120,682.5930,11.9060);*/
	/*new pass_hash_final[512];
	format(pass_hash_final, 512, "%d_%s_%s", 19, BCRYPT_SALT, 123456);
	bcrypt_hash(pass_hash_final, BCRYPT_COST, "testbcrypt");*/
	//printf("%d", udb_hash("123456"));
	return 1;
}

task InitModules()
{
	//**czyszczenie kalkulatora - start
	mq_format("TRUNCATE `gps_calc`;");
	mysql_query(g_SQL, mQuery, false);
	//--- kalkulator wyczyszcony.
	Init_Objects();//wczytywanie obiektów z db
	Init_TextDraw();//textdrawy
	Init_Vehicles();//pojazdy
	Init_Artwork();//modele i textury
	Init_Pickups();//pickupy
	//Init_NickCache();//nicki graczy(wszystkich)
	Init_TransportCourier();//firmy kurierskie
	Init_RPC();//RPC (gangzone loop)
	Init_Fractions();//frakcje
	Init_Doors();//ładowanie przejść
	Init_Binco();//Binco
	Init_BusStations();//przystanki
	Init_Shop();//sklep
	Init_Gym();//siłownia
	Init_House();//domki
	Init_RGPS();//Remote GPS system
	Init_Company();//Firmy
	Init_SampVoice();//plugin głosowy
	Init_Anims();//animacje
	Init_BorderCross();//przejścia graniczne
	Init_Office();//urzad miasta
	Init_SpeedCams();//fotoradary
	Init_Fireworks();//fajerwerki
	Init_Banks();//banki
	Init_Football();//piłka nożna
	Init_BasketBall();//koszykówka
	Init_LunaPark();//lunapark
	Init_Pool();//bilard
	Init_EventPanel();//panel eventowy
	Init_ASG();
	Init_Fishing();
	Init_TrafficLights();
	//porządek w db:
	mq_format("UPDATE `Konta` SET `rlg_timestamp`='0';");
	mq_send("QDBFix0");
	mq_format("UPDATE `pojazdy` SET `rlg_lastused`='0';");
	mq_send("QDBFix1");
	ExportItemInfo();
	ExportZoneNames();
	ExportVehicleInfo();
	//-
	SetTimer("EndLoadGMAndUnlockServer", 1000, false);
	return 1;
}

task EndLoadGMAndUnlockServer()
{
	format(serwer[srv_customhostname], 128, "[0.3DL] Highway Life - Szerokosci!");
	new strCommandRcon[256];
	if(strlen(serwer[srv_password]) > 1) format(strCommandRcon, 256, "password %s", serwer[srv_password]);
	else format(strCommandRcon, 256, "password 0");
	SendRconCommand(strCommandRcon);
	return 1;
}

CMD:uptime(playerid, params[])
{
	#pragma unused params
	new dd, gg, mm, ss;
	SecToTime(serwer[uptime], dd, gg, mm, ss);
	SendClientMessageEx(playerid,  0xFF0000FF, "Highway Life UPTIME: %d dni, %d godzin, %d minut, %d sekund",   dd, gg, mm, ss);
	return 1;
}

CMD:maxvehicles(playerid, params[])
{
	#pragma unused params
	new wynik;
	for(new v; v < MAX_VEHICLES; v++)
	{
		if(GetVehicleModel(v) == 0) continue;
		wynik++;
	}
	SendClientMessageEx(playerid,  0xFF0000FF, "Highway Life VEHICLES: "COL_BLUE"%d sztuk"COL_RED" (pozostalo: %d)", wynik, MAX_VEHICLES-wynik);
	return 1;
}
/*
CMD:bramagraczatp(playerid, params[])
{
	for(new go; go < MAX_GATES; go++)
	{
		new g = GateObjects[go];
		if(ObjectInfo[g][mgOwnerType] == 1 && ObjectInfo[g][mgOwner] > 10)//gracz
		{
			SetPlayerPos(playerid, ObjectInfo[g][oX] , ObjectInfo[g][oY] , ObjectInfo[g][oZ]);
			Info(playerid, "Teleportowałeś się do bramy którą trzeba przepisać do posesji.");
			return 1;
		}
	}
	Info(playerid, "Wydaje się, że wszystkie bramy są już naprawione :)");
	return 1;
}
*/
public OnGameModeExit()
{
	print("****************SKRYPT Highway Life UNLOAD****************");
	printf("There are %d unprocessed queries.", mysql_unprocessed_queries(g_SQL));
	mysql_close(g_SQL);
	new dd, gg, mm, ss;
	SecToTime(serwer[uptime], dd, gg, mm, ss);
	printf("UPTIME: %d dni, %d godzin, %d minut, %d sekund",   dd, gg, mm, ss);
	print("****************SKRYPT Highway Life UNLOAD****************");
	// Delete all NPCs
	for (new i = 0; i < MAX_PLAYERS; i++) {
		if (IsPlayerNPC(i)) {
			FCNPC_Destroy(i);
		}
	}
	// Close all nodes
	for (new i = 0; i < FCNPC_MAX_NODES; i++) {
		if (FCNPC_IsNodeOpen(i)) {
			FCNPC_CloseNode(i);
		}
	}
	//Profiler_Stop();
	//Profiler_Dump();
	return 1;
}

forward ServerUpdate();
public ServerUpdate()
{
	Process_MicrophoneActive();
	serwer[time_timestamp] = gettime(serwer[time_hour], serwer[time_minute], serwer[time_second]);
	if(serwer[time_lasttime_timer] < serwer[time_timestamp])
	{
		//printf("[ServerUpdate] START");
		//new test_tick = GetTickCount();
		serwer[time_lasttime_timer] = serwer[time_timestamp];
		serwer[uptime]++;
		SetClockTD(serwer[time_hour], serwer[time_minute], serwer[time_second]);

		BlinkSystem_TrailerCheck();
		/*Process_PoolPlayerSize();
		Process_Vehicle();
		Process_AutoCloseGates();
		Process_Pozary();
		Process_BorderCross();
		Process_CreateActorPos();//utils
		Process_ServerRestart();
		Process_JoinLeaveTD();
		Process_ChatOnline();
		Process_PickupFixbody();
		Process_Citizens();*/

		Process_PoolPlayerSize();

		AddPublicRunQueue("Process_Vehicle");
		AddPublicRunQueue("Process_AutoCloseGates");
		AddPublicRunQueue("Process_Pozary");
		AddPublicRunQueue("Process_BorderCross");
		AddPublicRunQueue("Process_CreateActorPos");
		AddPublicRunQueue("Process_ServerRestart");
		AddPublicRunQueue("Process_JoinLeaveTD");
		AddPublicRunQueue("Process_ChatOnline");
		AddPublicRunQueue("Process_PickupFixbody");
		AddPublicRunQueue("Process_Citizens");
		AddPublicRunQueue("Process_TaxiCitizens");
		AddPublicRunQueue("Process_NapadMafia");
		AddPublicRunQueue("Process_BC");
		AddPublicRunQueue("Process_FallTree");
		AddPublicRunQueue("Process_VehPlayerBusinnesLabels");
		AddPublicRunQueue("Process_IdleADR");
		AddPublicRunQueue("Process_LunaPark");
		AddPublicRunQueue("Process_EventPanel");
		AddPublicRunQueue("Porcess_Pool");
		AddPublicRunQueue("Process_BasketBall");
		AddPublicRunQueue("Process_FuelStations");
		AddPublicRunQueue("Process_OilSR");
		//if(serwer[time_second] == 1 || serwer[time_second] == 11 || serwer[time_second] == 21 || serwer[time_second] == 31 || serwer[time_second] == 41 || serwer[time_second] == 51)
		//{
		Process_UpdateCompanySession();
		Process_CompanyContract();
		//}
		Hide_InterwencjaTD();
		world_control();
		//new time_bench = GetTickCount();
		for(new p = PlayerPoolSize(); p != -1; p--)
		{

			OneSecondUpdate(p);
			//SetTimerEx("OneSecondUpdate", MRandRange(1, 2), false, "d", p);
		}
		//printf("trwało: %d", GetTickCount()-time_bench);
		if(serwer[time_autorespawn] < serwer[time_timestamp])
		{
			serwer[time_autorespawn] = serwer[time_timestamp]+60*60*6;
			if(!serwer[respawn_inprogress])
			{	
				serwer[respawn_inprogress] = true;
				format(serwer[respawn_adminnick], 24, "SYSTEM");
				SendClientMessageToAllEx(0x00FF00FF, "[RESPAWN] "COL_LIME"Za "COL_RED"30 sekund"COL_LIME", wszystkie pojazdy nieużywane dłużej niż "COL_RED"%d min"COL_LIME" zostaną zrespawnowane.", VEHI_GLOBALRESPTIME/60);
				SetTimer("AdminRespawnAllVehicles", 1000*30, false);
			}
		}
		//printf("[ServerUpdate] END (%dms)", GetTickCount()-test_tick);
	}
	return 1;
}

stock world_control()
{
	if(serwer[world_control_timestamp] > serwer[time_timestamp]) return 1;
	serwer[world_control_timestamp] =  serwer[time_timestamp]+60*7;
	RandomWeather();
	SetWeather(serwer[pogoda]);
	return 1;
}


task Process_AnnounceSCM(annid)
{
	if(serwer[playerscount] > 0)
	{
		//SendClientMessageToAllEx(0x00BA8CFF, "[Bot HL] "COL_GREY"%s", ann_scm[annid]);
		serwer[last_annmsg] = annid;
		if(serwer[time_connectinfo] == 0)
		{
			HUD_UpdateINFO(ann_scm_td[serwer[last_annmsg]], 0);
		}
		new strLog[256];
		format(strLog, 256, "{00BA8C}[Bot HL] "COL_GREY"%s", ann_scm[annid]);
		SavePublicChatLog(strLog);
		if(annid+1 > sizeof(ann_scm)-1) annid = 0;
		else annid++;
	}
	SetTimerEx("Process_AnnounceSCM", (1000*60)*5, false, "d", annid);
	return 1;
}

stock SavePublicChatLog(chattxt[], userid = 0)
{
	new strChat[256];
	format(strChat, 256, "%s", chattxt);
	mysql_escape_string(strChat, strChat, 256);
	if(userid > 0) mq_format("INSERT INTO `LogChat` (`uid`,`text`) VALUES ('%d', '%s');", userid, strChat);
	else mq_format("INSERT INTO `LogChat` (`text`) VALUES ('%s');", strChat);
	mq_send("QSendLogChat");
	return 1;
}

task Process_ChatOnline()
{
	if(serwer[playerscount] == 0) return 1;
	if(serwer[chat_online_process]) return 1;
	serwer[chat_online_process] = true;
	mq_format("SELECT `l`.`id`,`l`.`text`,`u`.`Nick`,`u`.`AdminLevel`,`u`.`master_nick` FROM `LogChat` AS `l` INNER JOIN `Konta` AS `u` ON `l`.`uid`=`u`.`id` WHERE `web`='1' ORDER BY `id` DESC LIMIT 0,1;");
	mq_send("ChatWWW_Load");
	return 1;
}

task ChatWWW_Load()
{
	mq_getdata();
	new strMessage[144];
	new tid;
	new tadminlvl;
	new tnick[24];
	new ttext[1024];
	new mnickcolor = 0x00BA8CFF;
	if(rekordy)
	{
		cache_get_value_name_int(0, "id", tid);
		cache_get_value_name_int(0, "AdminLevel", tadminlvl);
		cache_get_value_name(0, "Nick", tnick);
		cache_get_value_name(0, "text", ttext);
		switch(tadminlvl)
		{
			case 0://Gracz - VIP (chat online only vip)
			{
				/*if(isvip(playerid)) format(strMessage, 256, "[VIP] {%06x}«%d» %s %s{FFFFFF} %s", mnickcolor >>> 8, tnick, HighlightNick(ttext));
				else format(strMessage, 256, "{%06x}%s %s{FFFFFF} %s", mnickcolor >>> 8, tnick, HighlightNick(ttext));*/
				format(strMessage, 144, "[VIP] {%06x}%s "COL_LIVECHAT"• LiveChat •»{FFFFFF} %s", mnickcolor >>> 8, tnick, (ttext));
			}
			case 1://Support
			{
				format(strMessage, 144, "[S] {%06x}%s "COL_LIVECHAT"• LiveChat •»{FFFFFF} %s", mnickcolor >>> 8, tnick, (ttext));
			}
			case 2://Game Master
			{
				format(strMessage, 144, "[GM] {%06x}%s "COL_LIVECHAT"• LiveChat •»{FFFFFF} %s", mnickcolor >>> 8, tnick, (ttext));
			}
			default://Admin
			{
				format(strMessage, 144, "[A] {%06x}%s "COL_LIVECHAT"• LiveChat •»{FFFFFF} %s", mnickcolor >>> 8, tnick, (ttext));
			}
		}
		for(new i = PlayerPoolSize(); i != -1; i--)
		{
			if(gracz[i][loggedin])
			{
				switch(tadminlvl)//dobranie kolorów
				{
					case 0:
					{
						SendClientMessage(i, COLOR_VIP, strMessage);
						/*if(isvip(playerid)) 
						{
							SendClientMessage(i, COLOR_VIP, strMessage);
						}
						else 
						{
							SendClientMessage(i, -1, strMessage);//Gracz
						}*/
					}
					case 1: 
					{
						SendClientMessage(i, 0x00A09EFF, strMessage);//Support
					}
					case 2: 
					{
						SendClientMessage(i, 0x0052DDFF, strMessage);//Game Master
					}
					default: 
					{
						SendClientMessage(i, 0xFF0000FF, strMessage);//Admin
					}
				}
			}
		}
		mq_format("UPDATE `LogChat` SET `web`='2' WHERE `id`='%d';", tid);
		mq_send("ChatSendConf");
	}
	else serwer[chat_online_process] = false;
	return 1;
}

task ChatSendConf()
{
	serwer[chat_online_process] = false;
	return 1;
}


stock UnlockOptLocations()
{
	for(new b; b < MAX_OPTLOCATIONS; b++)
	{
		if(opt_locations_ban[b][opt_ban] == false)
		{
			opt_locations_ban[b][opt_ban] = true;
			continue;
		} 
		if(MRandom(3) == 6)
		{
			opt_locations_ban[b][opt_ban] = false;
			printf("[info] Dopuszczono opcjonalna lokacje %s.", opt_locations_ban[b][opt_name]);
		}
	}
	return 1;
}

stock OptLocationLocked(lname[])
{
	for(new b; b < MAX_OPTLOCATIONS; b++)
	{
		if(compare(lname, opt_locations_ban[b][opt_name]))
		{
			if(opt_locations_ban[b][opt_ban] == true) return 1;
		}
	}
	return 0;
}


task Process_ServerRestart()
{
	//new bool:disrestart = true;
	//if(disrestart == true) return 1;
	if(serwer[cooldown_restart] > 0)
	{
		serwer[cooldown_restart]--;
		if(serwer[cooldown_restart] >= 15 && (serwer[time_second] == 30 || serwer[time_second] == 0))
		{
			SendClientMessageToAllEx(-1, ""COL_RED"-|{fb9800} Za "COL_WHITE"%d{fb9800} sekund nastąpi restart serwera. Powód: "COL_WHITE"%s{fb9800} "COL_RED"|-", serwer[cooldown_restart], serwer[reason_restart]);
		}
		else if(serwer[cooldown_restart] <= 5 && serwer[cooldown_restart])
		{
			SendClientMessageToAllEx(-1, ""COL_RED"-|{fb9800} Za "COL_WHITE"%d{fb9800} sekund nastąpi restart serwera. Powód: "COL_WHITE"%s{fb9800} "COL_RED"|-", serwer[cooldown_restart], serwer[reason_restart]);
		}
		else if(serwer[cooldown_restart] == 0)
		{
			SendClientMessageToAll(-1, ""COL_RED"-|{fb9800} Serwer zostaje zrestartowany... "COL_RED"|-");
			printf("[SERVER_RESTART]Wysylam zadanie restartu serwera...");
			HTTP(0, HTTP_GET, "s1.highwaylife.pl/angelfall/api/SecuredAwesomeApiScript1337.php?key=TBHYpgfmGmjDqWDmpG99qTF8FfwNyz&app=restart&ins=1", "", "RServerRestart");
		}
	}
	else if(serwer[time_hour] == 3 && serwer[time_minute] == 0)
	{
		printf("[SERVER_RESTART]Rozpoczynam procedure nocnego restartu serwera...");
		//zabieranie wszystkim siły
		/*mq_format("UPDATE `Konta` SET `sila`=`sila`-'0.5' WHERE `sila`>'60.0';");
		mq_send("QSilaDown");
		mq_format("UPDATE `Konta` SET `odpornosc`=`odpornosc`-'0.5' WHERE `odpornosc`>'60.0';");
		mq_send("QDefDown");

		mq_format("UPDATE `Konta` SET `sila`=`sila`-'0.25' WHERE `sila`>'1.25' AND `sila`<`60.0';");
		mq_send("QSilaDown");
		mq_format("UPDATE `Konta` SET `odpornosc`=`odpornosc`-'0.25' WHERE `odpornosc`>'1.25' AND `odpornosc`<`60.0';");
		mq_send("QDefDown");*/
		serwer[cooldown_restart] = 65;
		format(serwer[reason_restart], 32, "Nocny restart.");
		SendClientMessageToAllEx(-1, ""COL_RED"-|{fb9800} Za "COL_WHITE"%d{fb9800} sekund nastąpi restart serwera. Powód: "COL_WHITE"%s{fb9800} "COL_RED"|-", serwer[cooldown_restart], serwer[reason_restart]);
	}
	return 1;
}

task Process_HostName(nhostid)
{
	new strHostNameCmd[128];
	new time_count = 1588518000;
	if(serwer[time_timestamp] < time_count && serwer[time_timestamp] != 0)
	{
		new hn_days, hn_hours, hn_minutes, hn_secc;
		SecToTime(time_count-serwer[time_timestamp], hn_days, hn_hours, hn_minutes, hn_secc);
		if(hn_days > 0) format(strHostNameCmd, 128, "hostname [0.3DL] Highway Life - Otwarcie za: %d dni", hn_days);
		else format(strHostNameCmd, 128, "hostname [0.3DL] Highway Life - Otwarcie za: %02d:%02d %d", hn_hours, hn_minutes, hn_secc);
	}
	else
	{
		format(strHostNameCmd, 128, "hostname %s", serwer[srv_customhostname]);
	}
	SendRconCommand(strHostNameCmd);
	/*if(nhostid+1 > sizeof(ann_scm)-1) nhostid = 0;
	else nhostid++;*/
	SetTimerEx("Process_HostName", 1000, false, "d", nhostid);
	#pragma unused nhostid
	return 1;
}

stock ExportZoneNames()
{
	mysql_query(g_SQL, "TRUNCATE `zone_names`;", false);
	for(new x; x < sizeof(all_zone_names); x++)
	{
		new esc_str_name[32];
		mysql_escape_string(all_zone_names[x], esc_str_name);
		mq_format("INSERT INTO `zone_names` (`id`,`name`) VALUES ('%d','%s');", x, esc_str_name);
		mq_send("ExportZones");
	}
	return 1;
}

stock ExportVehicleInfo()
{
	mysql_query(g_SQL, "TRUNCATE `vehicles_info`;", false);
	for(new v; v < MAX_CARSPEC; v++)
	{
		new bool:white_list = false;
		for(new wl; wl < sizeof(truckshop_cameraquery); wl++)
		{
			if(truckshop_cameraquery[wl] == pojazd_spec[v][vspec_model]) white_list = true;
		}
		if(!IsVehicleSalonBanned(pojazd_spec[v][vspec_model]) || white_list == true)
		{
			mq_format("INSERT INTO `vehicles_info` (`model`,`price`,`fuel_type`,`fuel_size`,`fuel_consumption`,`zerosto`,`vmax`, `capacity`) VALUES ('%d','%d', '%d', '%d','%f','%f','%d', '%d');", pojazd_spec[v][vspec_model], CalcVehiclePriceEx(pojazd_spec[v][vspec_model]), pojazd_spec[v][vspec_fueltype], pojazd_spec[v][vspec_tanksize], pojazd_spec[v][vspec_fuelconsumption], pojazd_spec[v][vspec_0100], pojazd_spec[v][vspec_vmax], VehicleCapacity(pojazd_spec[v][vspec_model]));
			mq_send("ExportVehInfo");
		}
	}
	//naczepy
	new nmodel;
	nmodel = 435;
	mq_format("INSERT INTO `vehicles_info` (`model`, `price`, `capacity`) VALUES ('%d','%d','%d');", nmodel, CalcVehiclePriceEx(nmodel), VehicleCapacity(nmodel));
	mq_send("ExportVehInfo");
	nmodel = 450;
	mq_format("INSERT INTO `vehicles_info` (`model`, `price`, `capacity`) VALUES ('%d','%d','%d');", nmodel, CalcVehiclePriceEx(nmodel), VehicleCapacity(nmodel));
	mq_send("ExportVehInfo");
	nmodel = 584;
	mq_format("INSERT INTO `vehicles_info` (`model`, `price`, `capacity`) VALUES ('%d','%d','%d');", nmodel, CalcVehiclePriceEx(nmodel), VehicleCapacity(nmodel));
	mq_send("ExportVehInfo");
	nmodel = 591;
	mq_format("INSERT INTO `vehicles_info` (`model`, `price`, `capacity`) VALUES ('%d','%d','%d');", nmodel, CalcVehiclePriceEx(nmodel), VehicleCapacity(nmodel));
	mq_send("ExportVehInfo");
	return 1;
}

stock Init_Artwork()
{
	mq_format("SELECT * FROM `custom_models`;");
	mq_send("LoadArtworkFromDB");
	return 1;
}

task LoadArtworkFromDB()
{
	mq_getdata();
	new i;
	if(rekordy)
	{
		new t_type = -1;
		new t_virtualworld, t_base_id, t_new_id, t_dff_name[100], t_txd_name[100];
		while(i < rekordy)
		{
			cache_get_value_name_int(i, "type", t_type);
			cache_get_value_name_int(i, "virtualworld", t_virtualworld);
			cache_get_value_name_int(i, "base_id", t_base_id);
			cache_get_value_name_int(i, "new_id", t_new_id);
			cache_get_value_name(i, "dff_name", t_dff_name, 100);
			cache_get_value_name(i, "txd_name", t_txd_name, 100);
			if(t_type != -1)
			{
				if(t_type == 0)//skin
				{
					AddCharModel(t_base_id, t_new_id, t_dff_name, t_txd_name);
				}
				else if(t_type == 1)//obiekt
				{
					AddSimpleModel(t_virtualworld, t_base_id, t_new_id, t_dff_name, t_txd_name);
				}
			}
			i++;
		}
	}
	printf("[LOAD] Wczytano %d artworks.", i);
	Init_NPC();//NPC
	return 1;
}

/*public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	StartRouteGPS(playerid, Float:fX, Float:fY, Float:fZ);
	//SetObjective(playerid, "test", Float:fX, Float:fY, Float:fZ);
	return 1;
}*/

public OnPlayerEnterDynamicArea(playerid, areaid)
{
	if(IsPlayerNPC(playerid)) return 1;
	printf("[area detect] %d enter to areaid: %d", playerid, areaid);
	return 1;
}

public OnPlayerLeaveDynamicArea(playerid, areaid)
{
	if(IsPlayerNPC(playerid)) return 1;
	printf("[area detect] %d leave from areaid: %d", playerid, areaid);
	return 1;
}

stock RandomWeather()
{
	serwer[r_weather]++;
	switch(serwer[time_hour])
	{
		case 0..5: return serwer[pogoda] = 17;
		case 6..7: return serwer[pogoda] = 5;
		case 20..23: return serwer[pogoda] = 3;
	}
	if(serwer[pogoda] == 8 || serwer[pogoda] == 9) serwer[pogoda] = 6;

	if(serwer[r_weather] >= 9)
	{
		serwer[r_weather] = 0;
		serwer[n_weather]++;
		if(serwer[n_weather] == 6)
		{
			serwer[n_weather] = 0;
		}
		switch(serwer[n_weather])
		{
			case 0:
			{
				serwer[pogoda] = 14;
			}
			case 1:
			{
				serwer[pogoda] = 8;
			}
			case 3:
			{
				serwer[pogoda] = 4;
			}
			case 4:
			{
				serwer[pogoda] = 6;
			}
			case 5:
			{
				serwer[pogoda] = 9;
			}
		}
	}
	return 1;
}


task Process_PoolPlayerSize()
{
	new temp_pool;
	temp_pool = 0;
	serwer[playerscount] = 0;
	for(new p; p < MAX_PLAYERS; p++)
	{
		if(IsPlayerNPC(p)) continue;
		if(IsPlayerConnected(p)) 
		{
			temp_pool = p;
			serwer[playerscount]++;
		}
	}
	serwer[playerPoolSize] = temp_pool;
	return 1;
}

CMD:autorzy(playerid, params[])
{
	new autorzy[512];
	strcat(autorzy,""COL_GREY"Programista PAWN(& C++), właściciel projektu, prowadzący:"COL_RED" sebaqq6 \n");
	strcat(autorzy,""COL_GREY"Programista PHP, współwłaściciel projektu, admin techniczny:"COL_RED" czerwony03 \n");
	strcat(autorzy,""COL_GREY"Obiekter, współwłaściciel projektu, pomoc przy mechanice rozgrywki:"COL_RED" Requeim\n");
	strcat(autorzy,""COL_GREY"Credtis:"COL_BLUE" iDAKU, Policjant, I3lack, Desert, Sprocik, gadzber, Arilles\n");
	strcat(autorzy,""COL_GREY"Nasze oficjalne forum : "COL_LIME"https://forum.highwaylife.pl\n");
	strcat(autorzy,""COL_GREEN"\t\t\t\t\t\t\t\t\tMiłej gry! :)\n");
	MessageGUIEx(playerid, "Osoby, które zaangażowały się w projekt Highway Life", autorzy);
	return 1;
}

CMD:tdoff(playerid, params[])
{
	for(new i; i < MAX_PLAYER_TEXT_DRAWS; i++)
	{
		PlayerTextDrawHide(playerid, PlayerText:i);
		PlayerTextDrawDestroy(playerid, PlayerText:i);
	}
	for(new x; x < MAX_TEXT_DRAWS; x++)
	{
		TextDrawHideForPlayer(playerid, Text:x);
	}
	return 1;
}

/*
CMD:lostcon(playerid, params[])
{
	new BitStream:bs = BS_New();

	BS_WriteValue(
		bs,
		PR_INT8, 33
		);

	BS_Send(bs, playerid, .reliability = PR_RELIABLE_SEQUENCED);

	BS_Delete(bs);
	//KickEx(playerid, "relog");
	SetTimerEx("KickExRun", 1000, false, "d", playerid);

	DoneInfo();
	return 1;
}

public OnOutcomingPacket(playerid, packetid, BitStream:bs)
{
	printf("[OUT]playerid: %d ; packetid: %d", playerid, packetid);
	return 1;
}


public OnIncomingPacket(playerid, packetid, BitStream:bs)
{
	//if(packetid == 33)
	//{
	//	BS_Reset(bs);
	//	BS_WriteValue(
	//		bs,
	//		PR_INT8, 34
	//		);
	//
	//	BS_Send(bs, playerid);
	//	return 0;
	//}
	printf("[IN]playerid: %d ; packetid: %d", playerid, packetid);
	return 1;
}
*/
/*
CMD:deltextureall(playerid, params[])
{
	new BitStream:bs_deltexture = BS_New(); 
	for(new u; u < 1000; u++)
	{
		BS_Reset(bs_deltexture);
		new wObjectID = u;
		new MaterialType, MaterialID, iModelID, libraryNameLength, textureNameLength, color;
		new libraryName[64], textureName[64];
		MaterialType = 1;
		MaterialID = 0;
		iModelID = 0;
		libraryNameLength = 12;
		textureNameLength = 8;
		color = 0x00AABBCC;
		libraryName = "sw_furniture";
		textureName = "CJ_WOOD5";
		BS_ResetWritePointer(bs_deltexture);
		BS_WriteValue(
		bs_deltexture,
		PR_UINT16,  wObjectID,
		PR_UINT8,  MaterialType,
		PR_UINT8,  MaterialID,
		PR_UINT16, iModelID,
		PR_UINT8,  libraryNameLength,
		PR_STRING,  libraryName,
		PR_UINT8,  textureNameLength,
		PR_STRING,  textureName,
		PR_UINT32,  color);
		BS_RPC(bs_deltexture, playerid, 84, PR_LOW_PRIORITY, PR_RELIABLE_ORDERED); 
	}
	BS_Delete(bs_deltexture); 
	DoneInfo();
	return 1;
}

CMD:cptest(playerid, params[])
{
	SetPlayerCheckpoint(playerid, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], 3.0);
	DoneInfo();
	return 1;
}

CMD:printcomp(playerid, params[])
{
	for(new c; c < 14; c++)
	{
		printf("printcomp[%d]: %d", c, GetVehicleComponentInSlot(GetPlayerVehicleID(playerid), c));
	}
	return 1;
}

CMD:attachtrailer(playerid, params[])
{
	new vehicleid = strval(params);
	Handbrake(vehicleid, false);
	AttachTrailerToVehicle(vehicleid, GetPlayerVehicleID(playerid));
	DoneInfo();
	return 1;
}

CMD:dattachtrailer(playerid, params[])
{
	DetachTrailerFromVehicle(GetPlayerVehicleID(playerid));
	DoneInfo();
	return 1;
}


CMD:sampsong(playerid, params[])
{
	PlayerPlaySound(playerid, strval(params), 0, 0, 0);
	return 1;
}


CMD:editbox(playerid, params[])
{
	EditAttachedObject(playerid, strval(params));
	return 1;
}

CMD:hajs(playerid, params[])
{
	SetMoney(playerid, strval(params));
	return 1;
}

CMD:skin(playerid, params[])
{
	if(strval(params) < 0) return 1;
	SetPlayerSkin(playerid, strval(params));
	return 1;
}

CMD:makeadmin(playerid, params[])
{
	gracz[playerid][AdminLevel] = strval(params);
	DoneInfo();
	return 1;
}

CMD:audostream(playerid, params[])
{
	PlayAudioStreamForPlayer(playerid, params);
	return 1;
}

CMD:saloncars(playerid, params[])
{
	GenererateCarSalonCarRotation();
	DoneInfo();
	return 1;
}
*/

/*
public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	printf("%f, %f, %f, %f, %f, %f", Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ);
	return 1;
}


CMD:car(playerid, params[])
{
	new carid, k[2];
	if(sscanf(params,"ddd", carid, k[0], k[1])) return SendClientMessage(playerid, -1, "UŻYJ: /car [carid] [k1] [k2]");
	if(carid < 400 || carid > 611) return 1;
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, x, y, z);
	new vid;
	vid = CreateVehicle(carid, x, y, z, 0.0, k[0], k[1], -1);
	SetVehicleParamsEx(vid, 1, 1, 0, 0, 0, 0, 0);
	pojazd[vid][v_model] = carid;
	SetVehicleToRespawn(vid);

	SendClientMessage(playerid, -1, "GOTOWE!");
	for(new i=0;i<4;i++)
	{
		Blink[vid][i] = -1;
	}
	return 1;
}


CMD:view(playerid, params[])
{
	new count = strval(params);
	SendClientMessageEx(playerid, -1, "ustawiono rendering na %d obiektów", count);
	Streamer_DestroyAllVisibleItems(playerid, STREAMER_TYPE_OBJECT);
	Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, count, playerid);
	return 1;
}

CMD:view3d(playerid, params[])
{
	new count = strval(params);
	SendClientMessageEx(playerid, -1, "ustawiono rendering z %d na %d 3dtext", Streamer_GetVisibleItems(STREAMER_TYPE_3D_TEXT_LABEL, playerid), count);
	Streamer_DestroyAllVisibleItems(playerid, STREAMER_TYPE_3D_TEXT_LABEL);
	Streamer_SetVisibleItems(STREAMER_TYPE_3D_TEXT_LABEL, count, playerid);
	return 1;
}

CMD:vnagrywaj(playerid,params[])
{
	if(isnull(params)) return SendClientMessage(playerid, -1, "error1");
	if(!IsPlayerInAnyVehicle(playerid)) 
	{
		SendClientMessage(playerid,0xFF0000FF,"Recording: Get in a vehicle.");
		return 1;
	}
	StartRecordingPlayerData(playerid,PLAYER_RECORDING_TYPE_DRIVER,params);
	SendClientMessage(playerid,0xFF0000FF,"Recording: started.");
	return 1;
}

CMD:nstop(playerid,params[])
{
	StopRecordingPlayerData(playerid);
	SendClientMessage(playerid,0xFF0000FF,"Recording: stopped.");
	return 1;
}
*/
//NARZĘDZIA:
stock COtoDB(model, Float:coX, Float:coY, Float:coZ, Float:corX, Float:corY, Float:corZ)//wrzucanie create objects do db
{
	AddObject(model, -1, 1, -1, -1, coX, coY, coZ, corX, corY, corZ);
	return 1;
}
stock COtoDB2(model, Float:coX, Float:coY, Float:coZ, Float:corX, Float:corY, Float:corZ)//wrzucanie create objects do db
{
	AddObject2(model, -2, 2, -1, -1, coX, coY, coZ, corX, corY, corZ);
	return 1;
}

stock AddObject2(model, idgrupa, uid, World, InteriorEx, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	mq_format("INSERT INTO `Obiekty` (`model`, `idgrupa`, `uid`, `World`, `InteriorEx`, `x`, `y`, `z`, `rx`, `ry`, `rz`) VALUES ('%d', '%d', '%d', '%d', '%d', '%0.5f', '%0.5f', '%0.5f', '%0.5f', '%0.5f', '%0.5f');", model, idgrupa, uid, World, InteriorEx, x, y, z, rx, ry, rz);
	print(mQuery);
	return 1;
}


stock VehicleToDB(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2)
{
	//#pragma unused color1
	//#pragma unused color2
	//mq_format("INSERT INTO `pojazdy` (`model`, `X`, `Y`, `Z`, `R`, `color_0`, `color_1`, `owner`) VALUES ('%d', '%f', '%f', '%f', '%f', '%d', '%d', '7');", modelid, spawn_x, spawn_y, spawn_z, z_angle, color1, color2);//publiczne
	mq_format("INSERT INTO `pojazdy` (`model`, `X`, `Y`, `Z`, `R`, `color_0`, `color_1`, `owner_type`, `owner`) VALUES ('%d', '%f', '%f', '%f', '%f', '%d', '%d', '1', '7');", modelid, spawn_x, spawn_y, spawn_z, z_angle, color1, color2);//frakcyjne
	print(mQuery);
	//mq_send("QVehicleToDB");
	return 1;
}

stock queryAddSimpleModel(virtualworld, baseid, newid, dffname[], txdname[])
{
	mq_format("INSERT INTO `custom_models` (`type`, `virtual_world`, `base_id`, `new_id`, `dff_name`, `txd_name`) VALUES ('1', '%d', '%d', '%d', '%s', '%s');", virtualworld, baseid, newid, dffname, txdname);
	print(mQuery);
	return 1;
}

stock queryAddCharModel(baseid, newid, dffname[], txdname[])
{
	mq_format("INSERT INTO `custom_models` (`type`, `virtual_world`, `base_id`, `new_id`, `dff_name`, `txd_name`) VALUES ('0', '-1', '%d', '%d', '%s', '%s');", baseid, newid, dffname, txdname);
	print(mQuery);
	return 1;
}
/*
new __npgt = 0;
CMD:npgt(playerid, params[])
{
	new Float:px, Float:py, Float:pz;
	GetPlayerPos(playerid, px, py, pz);
	mq_format("INSERT INTO `gps_customnodes` (`x`, `y`, `z`, `connected`, `comment`) VALUES ('%f', '%f', '%f', '%d', '%s');", px, py, pz, __npgt+2, params);
	new Cache:result = mysql_query(g_SQL, mQuery);
	__npgt = cache_insert_id();
	cache_delete(result);
	DoneInfo();
	return 1;
}



CMD:nodegpsprint(playerid, params[])
{
	
	new Float:nX, Float:nY, Float:nZ, strnode[128];
	for(new n; n < MAX_RCNODES; n++)
	{
		if(NodeExists(n))
		{
			GetNodePos(n, nX, nY, nZ);
			format(strnode, 128, "[GPS NID: {FF0000}%d{00FF00}]", n);
			CreateDynamic3DTextLabel(strnode, 0x00FF00FF, nX, nY, nZ, 100.0);
			//printf("GPS NODE [%d] %f %f %f", n, nX, nY, nZ);
		} 
	}
	DoneInfo();
	return 1;
}
*/
/*
stock get_data_ets(data[])
{
	new nazwa[32];
	new url[128];
	new null[128];
	sscanf(data, "s[128]s[32]s[128]s[128]s[128]s[128]", url, nazwa, null, null, null, null);
	//format(nazwa, 20, "%s", strtok(data, idx));
	printf("{\"%s\", \"%s\"},", str_replace("_", " ", nazwa), url);
	return 1;
}

public OnIncomingRPC(playerid, rpcid, BitStream:bs)
{
	if(rpcid == 26) 
	{
		new wVehicleID;
		new bIsPassenger;
		BS_IgnoreBits(bs, 8);
		BS_ReadValue( 
		bs,
		PR_UINT16, wVehicleID, 
		PR_UINT8, bIsPassenger
		);
		printf("wVehicleID: %d | bIsPassenger: %d | %s", wVehicleID, bIsPassenger) ;
	}
	return 1;
}
//naczepa prozwizoryczna ?
new bool:trailertopacker[MAX_PLAYERS];
CMD:trailerdesyncon(playerid, params[])
{
	trailertopacker[playerid] = true;
	ReloadTrailerStream(playerid);
	return 1;
}
CMD:trailerdesyncoff(playerid, params[])
{
	trailertopacker[playerid] = false;
	ReloadTrailerStream(playerid);
	return 1;
}

stock ReloadTrailerStream(playerid)
{
	new BitStream:bs = BS_New();
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		if(IsVehicleStreamedIn(v, playerid))
		{
			BS_WriteValue(bs, PR_UINT16, v);
			BS_RPC(bs, playerid, 165, PR_LOW_PRIORITY, PR_RELIABLE_ORDERED); 
			BS_Reset(bs);
		}
	}
	BS_Delete(bs);
	Info(playerid, "reloaded");
	return 1;
}

public OnOutcomingRPC(playerid, rpcid, BitStream:bs)
{
	if(rpcid == 163) printf("WorldPlayerRemove - ID: 163");
	if(rpcid == 32) printf("WorldPlayerAdd - ID: 32");
	if(rpcid == 164) 
	{
		printf("WorldVehicleAdd ");
		new  wVehicleID,
		ModelID,
		InteriorColor1,
		InteriorColor2,
		interior, 
		DoorDamageStatus, 
		PanelDamageStatus, 
		LightDamageStatus, 
		tireDamageStatus, 
		addsiren, 
		modslot0, 
		modslot1, 
		modslot2, 
		modslot3, 
		modslot4, 
		modslot5, 
		modslot6, 
		modslot7, 
		modslot8, 
		modslot9, 
		modslot10, 
		modslot11, 
		modslot12, 
		modslot13, 
		PaintJob, 
		BodyColor1, 
		BodyColor2;
		new Float:  X,
		Float:  Y,
		Float:  Z,
		Float:  Angle,
		Float:  Health;
		BS_ReadValue(
		bs,
		PR_UINT16,  wVehicleID,
		PR_UINT32,  ModelID,
		PR_FLOAT,  X,
		PR_FLOAT,  Y,
		PR_FLOAT,  Z,
		PR_FLOAT,  Angle,
		PR_UINT8,  InteriorColor1,
		PR_UINT8,  InteriorColor2,
		PR_FLOAT,  Health, 
		PR_UINT8,  interior, 
		PR_UINT32,  DoorDamageStatus, 
		PR_UINT32,  PanelDamageStatus, 
		PR_UINT8,  LightDamageStatus, 
		PR_UINT8,  tireDamageStatus, 
		PR_UINT8,  addsiren, 
		PR_UINT8,  modslot0, 
		PR_UINT8,  modslot1, 
		PR_UINT8,  modslot2, 
		PR_UINT8,  modslot3, 
		PR_UINT8,  modslot4, 
		PR_UINT8,  modslot5, 
		PR_UINT8,  modslot6, 
		PR_UINT8,  modslot7, 
		PR_UINT8,  modslot8, 
		PR_UINT8,  modslot9, 
		PR_UINT8,  modslot10, 
		PR_UINT8,  modslot11, 
		PR_UINT8,  modslot12, 
		PR_UINT8,  modslot13, 
		PR_UINT8,  PaintJob, 
		PR_UINT32,  BodyColor1, 
		PR_UINT32,  BodyColor2
		);
		//if(pojazd[wVehicleID][v_model_sync_rpc] != 0) 
		if(IsVehicleTrailer(ModelID) && trailertopacker[playerid]) 
		{
			ModelID = 443;
			BS_Reset(bs);
			BS_WriteValue(
			bs,
			PR_UINT16,  wVehicleID,
			PR_UINT32,  ModelID,
			PR_FLOAT,  X,
			PR_FLOAT,  Y,
			PR_FLOAT,  Z,
			PR_FLOAT,  Angle,
			PR_UINT8,  InteriorColor1,
			PR_UINT8,  InteriorColor2,
			PR_FLOAT,  Health, 
			PR_UINT8,  interior, 
			PR_UINT32,  DoorDamageStatus, 
			PR_UINT32,  PanelDamageStatus, 
			PR_UINT8,  LightDamageStatus, 
			PR_UINT8,  tireDamageStatus, 
			PR_UINT8,  addsiren, 
			PR_UINT8,  modslot0, 
			PR_UINT8,  modslot1, 
			PR_UINT8,  modslot2, 
			PR_UINT8,  modslot3, 
			PR_UINT8,  modslot4, 
			PR_UINT8,  modslot5, 
			PR_UINT8,  modslot6, 
			PR_UINT8,  modslot7, 
			PR_UINT8,  modslot8, 
			PR_UINT8,  modslot9, 
			PR_UINT8,  modslot10, 
			PR_UINT8,  modslot11, 
			PR_UINT8,  modslot12, 
			PR_UINT8,  modslot13, 
			PR_UINT8,  PaintJob, 
			PR_UINT32,  BodyColor1, 
			PR_UINT32,  BodyColor2
			);
			BS_ResetReadPointer(bs);
			BS_ResetWritePointer(bs);
		}
		printf("vehadd model: %d | vid: %d", ModelID, wVehicleID);
	}
	if(rpcid == 165) printf("WorldVehicleRemove  - ID: 165");
	return 1;
}
const TRAILER_SYNC = 210;
IPacket:TRAILER_SYNC(playerid, BitStream:bs)
{
	new trailerData[PR_TrailerSync];

	BS_IgnoreBits(bs, 8);
	BS_ReadTrailerSync(bs, trailerData);

	printf(
		"TRAILER_SYNC[%d]:\ntrailerId %d \nposition %.2f %.2f %.2f \nquaternion %.2f %.2f %.2f %.2f \nvelocity %.2f %.2f %.2f \nangularVelocity %.2f %.2f %.2f",
		playerid,
		trailerData[PR_trailerId],
		trailerData[PR_position][0],
		trailerData[PR_position][1],
		trailerData[PR_position][2],
		trailerData[PR_quaternion][0],
		trailerData[PR_quaternion][1],
		trailerData[PR_quaternion][2],
		trailerData[PR_quaternion][3],
		trailerData[PR_velocity][0],
		trailerData[PR_velocity][1],
		trailerData[PR_velocity][2],
		trailerData[PR_angularVelocity][0],
		trailerData[PR_angularVelocity][1],
		trailerData[PR_angularVelocity][2]
	);
   
	new BitStream:bs2 = BS_New(); 
	new BitStream:bs3 = BS_New(); 
	BS_WriteValue( 
	bs2, 
	PR_UINT16,  trailerData[PR_trailerId],
	PR_FLOAT, trailerData[PR_position][0],
	PR_FLOAT, trailerData[PR_position][1],
	PR_FLOAT, trailerData[PR_position][2]
	);

	new Float:zAngle;
	GetVehicleZAngle(trailerData[PR_trailerId], zAngle);
	BS_WriteValue( 
	bs3, 
	PR_UINT16,  trailerData[PR_trailerId],
	PR_FLOAT, zAngle
	);
	
	for(new p = PlayerPoolSize(); p != -1; p--)
	{
		if(p == playerid) continue;
		if(!trailertopacker[p]) continue;
		if(IsVehicleStreamedIn(trailerData[PR_trailerId], playerid))
		{
			BS_RPC(bs2, p, 159, PR_LOW_PRIORITY, PR_RELIABLE_ORDERED);
			BS_RPC(bs3, p, 160, PR_LOW_PRIORITY, PR_RELIABLE_ORDERED);
		}
	}
	BS_Delete(bs2); 
	BS_Delete(bs3); 
	return 1;
}*/
