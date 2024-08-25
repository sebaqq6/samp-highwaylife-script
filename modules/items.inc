//************************************************************************************************
#define MAX_ITEMS 83
#define DEFAULT_OBJECT 1575
new ItemName[MAX_ITEMS][] =
{
	{"zero"}, // 0 - Występuje błąd
	{"Bandana: zielona"},//1
	{"Bandana: niebieska"},//2
	{"Bandana: czarna"},//3
	{"Bandana: biala"},//4
	{"Okulary owalne: czerwone"},//5
	{"Okulary owalne: pomaranczowe"},//6
	{"Okulary owalne: zielone"},//7
	{"Okulary owalne: niebieskie"},//8
	{"Okulary owalne: rozowe"},//9
	{"Okulary owalne: ciemne"},//10
	{"Okulary ochronne: zolte"},//11
	{"Okulary ochronne: pomaranczowe"},//12
	{"Okulary ochronne: czerwone"},//13
	{"Okulary ochronne: niebieskie"},//14
	{"Okulary ochronne: zielone"},//15
	{"Okulary pilotki: czarne"},//16
	{"Okulary pilotki: niebieskie"},//17
	{"Okulary pilotki: fioletowe"},//18
	{"Okulary pilotki: rozowe"},//19
	{"Okulary pilotki: czerwone"},//20
	{"Okulary pilotki: pomaranczowe"},//21
	{"Okulary pilotki: zolte"},//22
	{"Okulary pilotki: zielone"},//23
	{"Okulary owalne v2: siwe"},//24
	{"Okulary owalne v2: zolte"},//25
	{"Okulary owalne v2: czerwone"},//26
	{"Okulary owalne v2: czarne"},//27
	{"Okulary policyjne: czarne"},//28
	{"Okulary policyjne: czerwone"},//29
	{"Okulary policyjne: niebieskie"},//30
	{"Kaszkietowka: zielona"},//31
	{"Kaszkietowka: szara"},//32
	{"Kaszkietowka: czarna"},//33
	{"Kaszkietowka: niebieska"},//34
	{"Kaszkietowka: elektryczna"},//35
	{"Czapka: czarna"},//36
	{"Czapka: szara"},//37
	{"Kapelusz: szary"},//38
	{"Kapelusz: czarny"},//39
	{"Kapelusz: niebieski"},//40
	{"Kapelusz: zielony"},//41
	{"Kapelusz: czerwony"},//42
	{"Kapelusz: zolty"},//43
	{"Pusty kanister (10L)"},// 44
    	{"Pelny kanister [PB] (10L)"},// 45
    	{"Pelny kanister [ON] (10L)"},// 46
    	{"Batonik proteinowy"}, //47
    	{"Konserwa rybna"},//48
    	{"Chrupki CripsyFlakes"},//49
    	{"Jogurt truskawkowy"},//50
    	{"Jogurt bananowy"},//51
    	{"Jogurt waniliowy"},//52
    	{"Solone orzeszki"},//53
    	{"Twarog niskotluszczowy"},//54
    	{"Chrupki Happy-Smiley"},//55
    	{"Woda"},//56
    	{"Mleko"},//57
    	{"Sprunk"},//58
    	{"Apo-Cola"},//59
    	{"Apo-Cola Tiger"},//60
    	{"Sok jablkowy"},//61
    	{"Sok pomaranczowy"},//62
    	{"Uszczelniacz do chlodnic"},//63
    	{"Kolki do opon"},//64
    	{"[‰]Zywiec"},//65
    	{"[‰]Tyskie"},//66
    	{"[‰]Zubr"},//67
    	{"[‰]Lech"},//68
    	{"[‰]Okocim"},//69
    	{"[‰]Warka"},//70
    	{"[‰]Perła"},//71
    	{"[‰]Tatra"},//72
    	{"[‰]Jack Daniels"},//73
    	{"[‰]Johnnie Walker"},//74
    	{"[‰]Ballantines"},//75
    	{"[‰]Zoladkowa"},//76
    	{"[‰]Krupnik"},//77
    	{"[‰]Wyborowa"},//78
    	{"Wedka"},//79
    	{"Surowa ryba"},//80
    	{"Upieczone ryba"},//81
    	{"KitStart: Ognisko"}//82
};
//piwo: 1950, whiski: 19823, wódka: 19821
new ObjectItem[MAX_ITEMS] =
{
	-1,//Błąd, 0
	18913,//Bandana: zielona, 1
	18917,//Bandana: niebieska, 2
	18912,//Bandana: czarna, 3
	18919,//Bandana: biala, 4
	19006,//Okulary owalne: czerwone, 5
	19007,//Okulary owalne: pomaranczowe, 6
	19008,//Okulary owalne: zielone, 7
	19009,//Okulary owalne: niebieskie, 8
	19010,//Okulary owalne: rozowe, 9
	19012,//Okulary owalne: ciemne, 10
	19017,//Okulary ochronne: zolte, 11
	19018,//Okulary ochronne: pomaranczowe, 12
	19019,//Okulary ochronne: czerwone, 13
	19020,//Okulary ochronne: niebieskie, 14
	19021,//Okulary ochronne: zielone, 15
	19022,//Okulary pilotki: czarne, 16
	19023,//Okulary pilotki: niebieskie, 17
	19024,//Okulary pilotki: fioletowe, 18
	19025,//Okulary pilotki: rozowe, 19
	19026,//Okulary pilotki: czerwone, 20
	19027,//Okulary pilotki: pomaranczowe, 21
	19028,//Okulary pilotki: zolte, 22
	19029,//Okulary pilotki: zielone, 23
	19030,//Okulary owalne v2: siwe, 24
	19031,//Okulary owalne v2: zolte, 25
	19032,//Okulary owalne v2: czerwone, 26
	19033,//Okulary owalne v2: czarne, 27
	19138,//Okulary policyjne: czarne, 28
	19139,//Okulary policyjne: czerwone, 29
	19140,//Okulary policyjne: niebieskie, 30
	18943,//Kaszkietowka: zielona, 31
	18942,//Kaszkietowka: szara, 32
	18941,//Kaszkietowka: czarna, 33
	18940,//Kaszkietowka: niebieska, 34
	18939,//Kaszkietowka: elektryczna, 35
	18953,//Czapka: czarna, 36
	18954,//Czapka: szara, 37
	18946,//Kapelusz: szary, 38
	18947,//Kapelusz: czarny, 39
	18948,//Kapelusz: niebieski, 40
	18949,//Kapelusz: zielony, 41
	18950,//Kapelusz: czerwony, 42
	18951,//Kapelusz: zolty, 43
	1650,//Pusty kanister (10L), 44
    	1650,//Pełny kanister [PB] (10L), 45
    	1650,//Pełny kanister [ON] (10L), 46
	11742,//Batonik proteinowy, 47
	11739,//Konserwa rybna, 48
	19561,//Chrupki CripsyFlakes, 49
	1455,//Jogurt truskawkowy, 50
	1455,//Jogurt bananowy, 51
	1455,//Jogurt waniliowy, 52
	11740,//Solone orzeszki, 53
	11740,//Twarog niskotluszczowy, 54
	19562,//Chrupki Happy-Smileym, 55
	19570,//Woda, 56
	19569,//Mleko, 57
	1546,//Sprunk, 58
	1950,//Apo-Cola, 59
	19822,//Apo-Cola Tiger, 60
	19564,//Sok jablkowy, 61
	19563,//Sok pomaranczowy, 62
	1644,//Uszczelniacz do chlodnic, 63
	DEFAULT_OBJECT,//Kolki do opon, 64
	1950,//Zywiec, 65
	1950,//Tyskie, 66
	1950,//Zubr, 67
	1950,//Lech, 68
	1950,//Okocim, 69
	1950,//Warka, 70
	1950,//Perła, 71
	1950,//Tatra, 72
	19823,//Jack Daniels, 73
	19823,//Johnnie Walker, 74
	19823,//Ballantines, 75
	19821,//Zoladkowa, 76
	19821,//Krupnik, 77
	19821,//Wyborowa, 78
	18632,//Wedka, 79
	19630,//Surowa ryba, 80
    	19630,//Upieczone ryba, 81
    	DEFAULT_OBJECT//KitStart: ognisko, 82
};

new Float:ObjectItemFloat[MAX_ITEMS][4] =
{
	{0.0, 0.0, 0.0, 0.0}, //Błąd, 0
	{1.0, 0.0, 0.0, 0.0}, //Bandana: zielona, 1
	{1.0, 0.0, 0.0, 0.0}, //Bandana: niebieska, 2
	{1.0, 0.0, 0.0, 0.0}, //Bandana: czarna, 3
	{1.0, 0.0, 0.0, 0.0}, //Bandana: biala, 4
	{1.0, 0.0, 0.0, 0.0}, //Okulary owalne: czerwone, 5
	{1.0, 0.0, 0.0, 0.0}, //Okulary owalne: pomaranczowe, 6
	{1.0, 0.0, 0.0, 0.0}, //Okulary owalne: zielone, 7
	{1.0, 0.0, 0.0, 0.0}, //Okulary owalne: niebieskie, 8
	{1.0, 0.0, 0.0, 0.0}, //Okulary owalne: rozowe, 9
	{1.0, 0.0, 0.0, 0.0}, //Okulary owalne: ciemne, 10
	{1.0, 0.0, 0.0, 0.0}, //Okulary ochronne: zolte, 11
	{1.0, 0.0, 0.0, 0.0}, //Okulary ochronne: pomaranczowe, 12
	{1.0, 0.0, 0.0, 0.0}, //Okulary ochronne: czerwone, 13
	{1.0, 0.0, 0.0, 0.0}, //Okulary ochronne: niebieskie, 14
	{1.0, 0.0, 0.0, 0.0}, //Okulary ochronne: zielone, 15
	{1.0, 0.0, 0.0, 0.0}, //Okulary pilotki: czarne, 16
	{1.0, 0.0, 0.0, 0.0}, //Okulary pilotki: niebieskie, 17
	{1.0, 0.0, 0.0, 0.0}, //Okulary pilotki: fioletowe, 18
	{1.0, 0.0, 0.0, 0.0}, //Okulary pilotki: rozowe, 19
	{1.0, 0.0, 0.0, 0.0}, //Okulary pilotki: czerwone, 20
	{1.0, 0.0, 0.0, 0.0}, //Okulary pilotki: pomaranczowe, 21
	{1.0, 0.0, 0.0, 0.0}, //Okulary pilotki: zolte, 22
	{1.0, 0.0, 0.0, 0.0}, //Okulary pilotki: zielone, 23
	{1.0, 0.0, 0.0, 0.0}, //Okulary owalne v2: siwe, 24
	{1.0, 0.0, 0.0, 0.0}, //Okulary owalne v2: zolte, 25
	{1.0, 0.0, 0.0, 0.0}, //Okulary owalne v2: czerwone, 26
	{1.0, 0.0, 0.0, 0.0}, //Okulary owalne v2: czarne, 27
	{1.0, 0.0, 0.0, 0.0}, //Okulary policyjne: czarne, 28
	{1.0, 0.0, 0.0, 0.0}, //Okulary policyjne: czerwone, 29
	{1.0, 0.0, 0.0, 0.0}, //Okulary policyjne: niebieskie, 30
	{1.0, 0.0, 0.0, 0.0}, //Kaszkietowka: zielona, 31
	{1.0, 0.0, 0.0, 0.0}, //Kaszkietowka: szara, 32
	{1.0, 0.0, 0.0, 0.0}, //Kaszkietowka: czarna, 33
	{1.0, 0.0, 0.0, 0.0}, //Kaszkietowka: niebieska, 34
	{1.0, 0.0, 0.0, 0.0}, //Kaszkietowka: elektryczna, 35
	{1.0, 0.0, 0.0, 0.0}, //Czapka: czarna, 36
	{1.0, 0.0, 0.0, 0.0}, //Czapka: szara, 37
	{1.0, 0.0, 0.0, 0.0}, //Kapelusz: szary, 38
	{1.0, 0.0, 0.0, 0.0}, //Kapelusz: czarny, 39
	{1.0, 0.0, 0.0, 0.0}, //Kapelusz: niebieski, 40
	{1.0, 0.0, 0.0, 0.0}, //Kapelusz: zielony, 41
	{1.0, 0.0, 0.0, 0.0}, //Kapelusz: czerwony, 42
	{1.0, 0.0, 0.0, 0.0}, //Kapelusz: zolty, 43
	{0.7, 0.0, 0.0, 0.0}, //Pusty kanister (10L), 44
	{0.7, 0.0, 0.0, 0.0}, //Pełny kanister [PB] (10L), 45
	{0.7, 0.0, 0.0, 0.0},//Pełny kanister [ON] (10L), 46
	{1.0, 0.0, 0.0, 0.0},//Batonik proteinowy, 47
	{1.0, 0.0, 0.0, 0.0},//Konserwa rybna, 48
	{1.0, 0.0, 0.0, 0.0},//Chrupki CripsyFlakes, 49
	{0.9, 0.0, 0.0, 0.0},//Jogurt truskawkowy, 50
	{0.9, 0.0, 0.0, 0.0},//Jogurt bananowy, 51
	{0.9, 0.0, 0.0, 0.0},//Jogurt waniliowy, 52
	{1.0, 0.0, 0.0, 0.0},//Solone orzeszki, 53
	{1.0, 0.0, 0.0, 0.0},//Twarog niskotluszczowy, 54
	{1.0, 0.0, 0.0, 0.0},//Chrupki Happy-Smileym, 55
	{1.0, 0.0, 0.0, 0.0},//Woda, 56
	{1.0, 0.0, 0.0, 0.0},//Mleko, 57
	{0.8, 0.0, 0.0, 0.0},//Sprunk, 58
	{0.8, 0.0, 0.0, 0.0},//Apo-Cola, 59
	{1.0, 0.0, 0.0, 0.0},//Apo-Cola Tiger, 60
	{1.0, 0.0, 0.0, 0.0},//Sok jablkowy, 61
	{1.0, 0.0, 0.0, 0.0},//Sok pomaranczowy, 62
	{1.0, 0.0, 0.0, 0.0},//Uszczelniacz do chłodnic, 63
	{1.0, 0.0, 0.0, 0.0},//Kolki do opon, 64
	{0.8, 0.0, 0.0, 0.0},//Zywiec, 65
	{0.8, 0.0, 0.0, 0.0},//Tyskie, 66
	{0.8, 0.0, 0.0, 0.0},//Zubr, 67
	{0.8, 0.0, 0.0, 0.0},//Lech, 68
	{0.8, 0.0, 0.0, 0.0},//Okocim, 69
	{0.8, 0.0, 0.0, 0.0},//Warka, 70
	{0.8, 0.0, 0.0, 0.0},//Perla, 71
	{0.8, 0.0, 0.0, 0.0},//Tatra, 72
	{1.0, 0.0, 0.0, 0.0},//Jack Daniels, 73
	{1.0, 0.0, 0.0, 0.0},//Johnnie Walker, 74
	{1.0, 0.0, 0.0, 0.0},//Ballantines, 75
	{1.0, 0.0, 0.0, 0.0},//Zoladkowa, 76
	{1.0, 0.0, 0.0, 0.0},//Krupnik, 77
	{1.0, 0.0, 0.0, 0.0},//Wyborowa, 78
	{1.0, 0.0, 0.0, 0.0},//Wędka, 79
	{0.9, 90.0, 0.0, 0.0},//Surowa ryba, 80
    	{0.9, 90.0, 0.0, 0.0},//Upieczone ryba, 81
    	{1.0, 0.0, 0.0, 0.0}//KitStart: Ognisko, 82
};

stock StackedItem(item_id)//0 - nie stackujacy, 1 - stackujacy
{
	switch(item_id)
	{
		case 1..43: return 0;//akcesoria
		case 44..46: return 0;//kanister
		case 63: return 0;//uszczelniacz do chłodnic
		case 64: return 0;//kołki do opon
		case 79: return 0;//wedka
	}
	return 1;
}

stock ItemCanConfig(item_id)//1 - konfigurowalny(w menu zamiast przesta jest 'konfiguruj'), 0 - niekonfigurowalny 
{
	switch(item_id)
	{
		case 1..43: return 1;//akcesoria
	}   
	return 0;
}

stock ExportItemInfo()
{
	mysql_query(g_SQL, "TRUNCATE `ItemInfo`;", false);
	for(new x; x < MAX_ITEMS; x++)
	{
		mq_format("INSERT INTO `ItemInfo` (`uid`,`name`) VALUES ('%d','%s');", x, ItemName[x]);
		mq_send("ImportItems");
	}
	return 1;
}