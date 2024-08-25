//#define DEBUGHL //tryb debugowania
//#define LIMITOBJ
//MAKRO
#define InRange IsPlayerInRangeOfPoint
#define chrtoupper(%1) (((%1) > 0x60 && (%1) <= 0x7A) ? ((%1) ^ 0x20) : (%1))//powiekszanie pierwszej litery
#define DistanceCalc(%1, %2) ((%1)/(%2))
#define task%0(%1) forward%0(%1); public%0(%1)//zadanie(task) - public i forward w jednym
//STAŁE
#define CONST_KM 250.0 //ile jednostek to 1 km
//ATTACH SLOT------------------------------------
//siłka: 0,1
#define GYM_ATTACH_INDEX1 (0)
#define GYM_ATTACH_INDEX2 (1)
#define GYM_ATTACH_INDEX3 (0)
//bandana :
#define BANDANA_SLOT 2
//bilard
#define ATTACH_SLOT3 3
//okulary: 4
#define OKULARY_SLOT 4
//paralizator
#define ATTACH_SLOT5 5
//czapka
#define CZAPKA_SLOT 6
#define ATTACH_SLOT7 7//WĘDKA
//bronie: 8,9
//DIALOGI
#define INFO_DIALOG 111
//LIMITY i CONFIGI
#undef MAX_OBJECTS
#define MAX_OBJECTS 100000//maksymalna ilość obiektów
//#define JESTZIMA 1//zakomentować, jeśli mamy lato
#define VISIBLE_ITEMS 900//max obiektów na raz
#define NICK_RANGE 100.0//widoczność nicków
#define MAX_SPAMID 32
#define GUICACHE_MAXLIST 512
#define GUICACHE_MAXVAR 16
#define MAX_CARSPEC 118
#define MAX_PRIVCARS_CONST 26//stałą maxymalna ilość pojazdów obsługiwana przez skrypt per player
#define MAX_VEHS_PLAYER 16//maksymalna ilośc posiadanych pojazdów - gracz - normal
#define MAX_VEHS_VIP 24//maksymalna ilośc posiadanych pojazdów - gracz - VIP
#define MAX_PRIVCARSCREATED 4//maksymalna ilosc pojazdów do stworzenia na mapie
#define MAX_FUELSTATIONS 100//max stacji paliw na mapie
#define MAX_CONCERNS 10//MAX koncernów stacji paliw
#define MAX_NICKCACHE 1000
#define MAX_COURIERPACK 10
#define COURIER_PACK_PRICE 950//$ za paczke dla kuriera
#define COURIER_MONEYTIME "20000"//od ilu $ praca kuriera ma być nieopłacalna
#define MAX_COURIERCLIENTS 64
#define MAX_SALONTRUCKSLOTS 20
#define MAX_RELOGTIME 5//maxymalnyczas reloga w min
#define MAX_FLPERPAGEGOODS 10//ilość towarów wyświetlanych jednocześnie na /zlecenie 
#define MAX_GOODSFORVANS 50 // ilość towarów dla vanów
#define MAX_VANLOADS 62//Maxymalna ilośc miejsc załadunkowo/rozładunkowych dla vanów
#define MAX_CONES 60//maxymalna ilość pachołków
#define MAX_NEONS 6
#define MAX_VEHICLE_OBJECTS 13
#define MAX_FALLTREE 118
#define FALLTREE_DELAY 2//co ile godzin ma spadać drzewo
#define ROPE_LENGTH 50
#define ROPE_SYNCMS 225
#define MAX_OPTLOCATIONS 16//maksymalna ilość opcjonalnych lokacji
//NAPADY
#define ATTACK_BATTLE_RANGE 100.0
#define ATTACK_EXIT_TIME 240
#define ATTACK_EXIT_RANGE 2500.0
//FREELANCER CENY
#define PRICE_FOR_KM_TRANSPORT_VAN 125//ile $ za kilometr VAN dla skryptu towarów | 60
#define PRICE_FOR_KM_TRANSPORT_TRUCK 220//ile $ za kilometr TRUCK dla skryptu towarów | 110
//FIRMY CENY
#define PRICE_FOR_KM_TRANSPORT_COMP 150//ile $ za kilometr dla firm | 60
#define PRICE_FOR_WEIGHT_TRANSPORT_COMP 0.7//ile $ za 1 kg
#define PRICE_ADR_BONUS_COMP 0.2//bonus $ za 1 kg ADR
//FIRMY CONF
#define MAX_COMPANY 15
#define COMPANY_KEEPDAYS 14 
#define MAX_CWORKERS 15
#define MAX_CVEHICLES 11*2//(MAX_CWORKERS*2)
#define RANGE_COMPANY 90.0
#define MAX_CONTRACTS 500
#define MAX_OVERLOADCARGO 30//ile procent można przeładować
#define MAX_OVERLOADCARGO_VIP 35//ile procent można przeładować - VIP
//FIRMY - LOGI
#define CLOGFLAG_KURS 1
#define CLOGFLAG_BANK 2
#define CLOGFLAG_WYDATEK 3
#define CLOGFLAG_POJAZD 4
//INNE
#define MAX_DUTYSESSION 30//sesja duty w min
#define MAX_FWORKERS 16//maksymalna ilość pracowników
#define DISDRAW_CAROBJ 90.0//rysowanie napisów na pojazdach
#define MAX_CALLS 100//maksymalna ilość wszystkich wezwań
#define FIRES_FREQUENCY 10//co ile minut maja byc pozary
#define MAX_VEHICLEDAMAGES 19//ilość komponentów pojazdu które sie zużywają [ram]
#define MAX_VEHICLEBODY_RESIST 10//automatyczna naprawa karoserii
#define PRICE_PRAWKO_TB 100//$ teoria B
#define PRICE_PRAWKO_PB 300//$ praktyka B
#define PRICE_PRAWKO_TCE 300//$ teoria CE
#define PRICE_PRAWKO_PCE 500//$ praktyka CE
#define TIME_EXAM_B 5//ile minut na zdanie praktyki B
#define TIME_EXAM_CE 6//ile minut na zdanie praktyki CE
#define MAX_DOORS 100//ilość przejść
#define TIME_LOADOBJ 6000//jak długo ma trwać ładowanie obiektów
#define MAX_GATES 512//maksymalna ilość bram
#define VEH_SINGLERESP_TIME 99999//paramtr autospawnu createvehicle
#define VEHI_GLOBALRESPTIME (60*30)//nieużywanie pojazdy dłużej niż X sekund, są respawnowane 
#define PRICE_GOLDDOLAR 10000//cena $ za żeton premium
#define MAX_HOUSES 1000//ilosc domków
#define HOUSE_VWOFFSET 700//offset vw dla domków
#define DOORS_VWOFFSET 10000//offset vw dla przejść
#define LUNAPARK_VWOFFSET 5000//offset vw dla przejść
#define OFFSET_HOUSEOBJ 1000//offset idgrupa obiektów dla domków
#define OFFSET_HOUSEINTOBJ 50000//offset idgrupa obiektów dla domków interior
#define OFFSET_COMPANYOBJ 100//offset idgrupa dla firm
#define POTENTIAL_CRASH_DAMAGE 35.0//siła uderzenia aby wykonac wypadek
#define MAX_SWEARS 1200//max słów do cenzura
#define MAX_TAXITARGET 143
#define MAX_TAXIPASS 6
#define MAX_PLAYER_BUILDING 1000
//CENY PALIW
#define STATIONS_MAX_PRICE_PB 46//50
#define STATIONS_MIN_PRICE_PB 30//30
#define STATIONS_MAX_PRICE_ON 45//54
#define STATIONS_MIN_PRICE_ON 32//34
#define STATIONS_MAX_PRICE_LPG 11
#define STATIONS_MIN_PRICE_LPG 9
//MSELECTION EXTRAID
#define MSEL_MOBJECTS 1
#define MSEL_MDUTYSKIN 2
#define MSEL_CHANGESKIN 3
#define MSEL_EVP_0 4
#define MSEL_EVP_1 5
#define MSEL_EVP_2 6
#define MSEL_EVP_3 7
#define MSEL_EVP_4 8
#define MSEL_EVP_5 9
#define MSEL_ADMINSKIN 10
//TYPY KAR
#define PENALTY_KICK 0
#define PENALTY_BAN 1
#define PENALTY_MUTE 2
#define PENALTY_JAIL 3
#define SCOREADD 4
#define SCOREDEL 5
#define PENALTY_MUTE_VHL 6
//LUNAPARK
#define LPARK_FOOTBALL 1
#define LPARK_BASKETBALL 2
#define LPARK_ASG 3
//POZYCJE MIEJSC INTERAKTYWNYCH
#define XYZ_WELCOME 1098.2721,1423.3387,11.9620
#define XYZ_AUTOSZROT 8.5784,1367.7806,9.1719//miejsce autoszrotu
#define XYZ_SALON 2322.4048,1028.9376,10.9259//miejsce salonu
#define XYZR_SALONBOT 2322.4097,1030.5171,10.9259,180.3881//bot w salonie samochodowym
#define XYZ_SALONTIP 2322.2332,1017.1712,10.9159
#define XYZ_TRUCKCENTER 1562.2251,1609.3628,10.8534
#define XYZ_TRUCKSALON 2307.3962,1440.4738,10.8490//salon truck
#define XYZ_PRISONADD 2430.0984,1726.4471,-2.3138//pickup do wpuszczania wiezniów wiezieniu
#define XYZ_PRISONOUT 2335.5835,1736.2853,10.8203//wypuszczenie z więzienia
#define XYZ_SPRAY 2629.7119,1049.4347,10.9931//spray dla pomocy drogowej
#define XYZ_PRAWKO 1030.4468,1322.3700,10.9160//zdawanie prawka
#define XYZ_BINCOC 2029.7571,2045.2577,11.0337//binco buy - custom
#define XYZ_BINCO 207.4699,-100.6546,1005.2578//binco buy - oryginal
#define XYZ_SHOP -23.4363,-55.4461,1003.5469//sklep interior pickup/3dtext
#define XYZ_GYMPICKUP 2003.7941,2043.6161,11.2286//siłownia /karnet
#define XYZ_PARKINGPOLICYJNY 2073.7422,2405.4299,10.8203//parking policyjny
#define XYZ_FIXBODY 2622.1926,1081.2463,10.9335//pickup do naprawiania karo obok pd
#define XYZ_LUNAPARK 3097.2598,-1962.8269,10.6993
#define XYZ_SELLFISH -2247.6746,2361.7722,4.9831
//REJESTRACJA POJAZDÓW
#define VEH_REG "HighwayLife"
//TYPY WŁAŚCICIELI POJAZDÓW
#define VEHICLE_PUBLIC 0
#define VEHICLE_PLAYER 1
#define VEHICLE_FRACTION 2
#define VEHICLE_BUSINESS 3
//TYPY WŁAŚCICIELI BRAM
#define GATE_PUBLIC 0
#define GATE_PLAYER 1
#define GATE_FRACTION 2
#define GATE_BUSINESS 3
#define GATE_HOME 4
//ID FRAKCJI GŁÓWNYCH
#define F_NONE 0
#define F_POLICE 1
#define F_BORDERGUARD 2
#define F_EMERGENCY 3
#define F_ROADASSIST 4
#define F_TAXI 5
#define F_MAFIA 6
//ID WŁAŚCICIELA POJAZDÓW GLOBALNYCH/publicznych - IDENTYFIKACJA POJAZDÓW
//firmy kurierskie
#define C_DHL 1
#define C_DPD 2
#define C_FEDEX 3
#define C_INPOST 4
#define C_TNT 5
//pozostałe
#define VO_CARSHOP 6//SALON SAMOCHODOWY
#define VO_MPTRAILER 7//Medium player trailer, freelancer - naczepy bezfirmowe, dla zwykłych graczy
#define VO_TRUCKSHOP 8//salon truck
#define VO_DRVLICENSE 9//pojazdy L-ki, do zdawania prawka
#define VO_ADMINVEH 10//pojazd admina
#define VO_EVENT 11
//TYPY PALIW
#define F_PB 0
#define F_ON 1
#define F_LPG 2
//ID KONCERNÓW NAFTOWYCH
#define STATION_CPN 0
#define STATION_ORLEN 1
#define STATION_SHELL 2
#define STATION_BP 3
#define STATION_LOTOS 4
#define STATION_MOYA 5
#define STATION_CIRCLEK 6
//DEFINICJE LEFTNOTIFY
#define LN_RED 0
#define LN_GREEN 1
#define LN_YELLOW 2
#define LN_GREY 3
#define LN_BLUE 4
//DEFINICJE SPAMU
#define SPAM_CHAT 0
#define SPAM_CMD 1
#define SPAM_PM 2
#define SPAM_KEYHANDBRAKE 3
#define SPAM_KEYENGINE 4
#define SPAM_KEYRADIONEXT 5
#define SPAM_GYMKEY 6
#define SPAM_SETLAG 7
#define SPAM_EYESPEEDVEH 7
#define SPAM_STARTFISH 8
//AUTOMATYCZNIE WYŁĄCZENIE MIGACZA
#define BLINK_TURN_ANGLE 55.0
//kolorki
#define COL_EASY           "{FFF1AF}"
#define COL_WHITE          "{FFFFFF}"
#define COL_BLACK          "{000000}"
#define COL_BROWN          "{6E2500}"
#define COL_GREY           "{999999}"
#define COL_RED            "{F81414}"
#define COL_YELLOW         "{F3FF02}"
#define COL_ORANGE         "{FFAF00}"
#define COL_LIME           "{B7FF00}"
#define COL_CYAN           "{00FFEE}"
#define COL_BLUE           "{00C0FF}"
#define COL_GREEN          "{009933}"
#define COL_DBLUE          "{333399}"
#define COL_PURPLE 	"{ca00d6}"
//KOLORY FRAKCJI
#define COL_DRV "{929292}"
#define COL_POL "{0051FF}"
#define COL_BORG "{2E8900}"
#define COL_EMRG "{FF5555}"
#define COL_ROADA "{FC8200}"
#define COL_TAXI "{FDFF00}"
#define COL_MAFIA "{944B00}"

#define COLOR_DRV 0x929292FF
#define COLOR_POL 0x0051FFFF
#define COLOR_BORG 0x2E8900FF
#define COLOR_EMRG 0xFF5555FF
#define COLOR_ROADA 0xFC8200FF
#define COLOR_TAXI 0xFDFF00FF
#define COLOR_MAFIA 0x944B00FF
//{}
#define COLOR_FRACTIONMSG 0x009B7FFF
#define COL_FMSG "{009B7F}"
//{}
#define COLOR_COMPANYMSG 0x00BA8CFF
#define COL_CMSG "{00BA8C}"
//{}
#define COL_VIP "{C7BF00}"
#define COLOR_VIP 0xC7BF00FF
//{}
#define COL_DRVONLINE "{00BA8C}"
#define COL_LIVECHAT "{00FF00}"
#define COLOR_INFO 0x12ADDAFF
#define BEZOWY 0xFFFFADAA
#define BIALY 0xFFFFFFAA
#define BORDOWY 0x99001FAA
#define COLOR_DIS_RED 0xFF0000FF
#define BRAZOWY 0x997A00AA
#define CIEMNY_ZIELONY 0x336633AA
#define CZARNY 0x000000AA
#define CZERWONY 0xFF0000AA
#define FIOLETOWY 0x9E3DFFAA
#define COLOR_PURPLE 0x9E3DFFAA
#define NIEBIESKI 0x0000FFAA
#define POMARANCZOWY 0xFF8000AA
#define ROZOWY 0xFF66CCAA
#define SZARY 0xB0B0B0AA
#define ZIELONY 0x00CC00AA
#define ZOLTY 0xFFFF00AA
#define COLOR_WHITE 0xFFFFFFAA
#define COLOR_FIOLET 0x8000FFFF
#define COLOR_LIGHTBLUE 0x6DC5F3FF
#define COLOR_LIGHTYELLOW 0xFAEAA9FF
#define COLOR_LIGHTGREEN 0x00FF00FF
#define COLOR_LIGHTCOLOR_WHITE 0xF7A26FFF
#define COLOR_LIGHTRED 0xFF0000FF
#define COLOR_RED 0xFF2F2FFF
#define COLOR_GREEN 0x33AA33AA
#define COLOR_GREY 0xAFAFAFAA
#define COLOR_YELLOW 0xFFFF00AA
#define COLOR_YELLOW2 0xFFFF00FF
#define COLOR_COLOR_WHITE 0xFF9900AA
#define COLOR_DARKCOLOR_WHITE 0xFF9900AA
#define COLOR_BLUE 0xFF9900AA
#define COLOR_SYSTEM 0xEFEFF7AA
#define COLOR_PINK 0xFF66FFAA
#define SPAWN_DELAY 3000
#define COLOR_KOMENDA 0xC83322FF
#define COLOR_GRAD1 0xC83322FF
#define COLOR_WIADOMOSC 0x00FF00FF
#define COLOR_BLACK 0x000000FF
#define COLOR_ADMIN 0xFF0000AA
#define COLOR_GD 0x1C86EE
#define AQUAGREEN   	0x03D687FF
#define COLOR_ORANGE 0xFF8000FF
#define COLOR_BLACK 0x000000FF
//POMOCNE
#define DoneInfo() Info(playerid, "Gotowe!")
