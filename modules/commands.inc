//*******************************************************************************************************************************************************CMD CALLBACKS
public OnPlayerCommandReceived(playerid, cmd[], params[], flags)
{
	//printf("cmd: '/%s' | params: '%s' | all: '/%s %s'", cmd, params, cmd, params);
	if(!gracz[playerid][loggedin]) return 0;
	ResetIdleAFK(playerid);
	return 1;
}

public OnPlayerCommandPerformed(playerid, cmd[], params[], result, flags)
{
	if(result == -1)
	{
		new str[127];
		format(str, 127, "Komenda "COL_ORANGE"/%s"COL_WHITE" jest niedostępna. Dostępne komendy:"COL_GREEN" /pomoc", cmd);
		Error(playerid, str);
		return 0;
	}
	format(temp_string, 144, "%s(%d): "COL_BLUE"/%s %s", nick(playerid), playerid, cmd, params);
	SendEyecmd(temp_string);
	#if defined DEBUGHL
	printf("[DEBUGHL] cmd: '/%s' | params: '%s' | all: '/%s %s'", cmd, params, cmd, params);
	#endif
	return 1;
}
//********************************************************************************************************************************************************KOMENDY
//POMOC
CMD:pomoc(playerid, params[])
{
	new listhelp[1000];
	strcat(listhelp,""COL_WHITE"("COL_RED"FAQ"COL_WHITE")\t"COL_BLUE"Jak zacząć? Jak grać? - FAQ"COL_WHITE"\t("COL_RED"FAQ"COL_WHITE")\n");
	strcat(listhelp,""COL_WHITE"("COL_GREEN"?"COL_WHITE")\t"COL_EASY"Komendy czatu"COL_WHITE"\t("COL_GREEN"?"COL_WHITE")\n");
	strcat(listhelp,""COL_WHITE"("COL_GREEN"?"COL_WHITE")\t"COL_EASY"Podstawowe komendy gracza"COL_WHITE"\t("COL_GREEN"?"COL_WHITE")\n");
	strcat(listhelp,""COL_WHITE"("COL_GREEN"?"COL_WHITE")\t"COL_EASY"Frakcje"COL_WHITE"\t("COL_GREEN"?"COL_WHITE")\n");
	strcat(listhelp,""COL_WHITE"("COL_GREEN"?"COL_WHITE")\t"COL_EASY"Komendy edytora obiektów"COL_WHITE"\t("COL_GREEN"?"COL_WHITE")\n");
	strcat(listhelp,""COL_WHITE"("COL_GREEN"?"COL_WHITE")\t"COL_EASY"Klawiszologia"COL_WHITE"\t("COL_GREEN"?"COL_WHITE")\n");
	strcat(listhelp,""COL_WHITE"("COL_RED"$"COL_WHITE")\t"COL_YELLOW"Strefa PREMIUM"COL_WHITE"\t("COL_RED"$"COL_WHITE")\n");
	Dialog_Show(playerid, POMOC, DIALOG_STYLE_TABLIST, ""COL_WHITE"Centrum Pomocy - "COL_GREEN"HighwayLife.pl"COL_WHITE"", listhelp, "Wybierz", "Anuluj");
	return 1;
}

Dialog:POMOC(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0:
		{
			new listcmd[3000];
			new listcount;
			for(new q; q < sizeof(faq_data); q += 2)
			{
				format(listcmd, 3000, "%s"COL_RED"%d. "COL_EASY"%s\n", listcmd, listcount+1, faq_data[q]);
				gui_cache[playerid][listcount][0] = q;
				listcount++;
			}
			Dialog_Show(playerid, FAQDIALOG, DIALOG_STYLE_LIST, ""COL_RED"•» "COL_GREEN"FAQ - Najczęsciej zadawane pytania"COL_RED" «•", listcmd, "Wybierz", "Wstecz");
		}
		case 1:
		{
			new listcmd[3000];
			strcat(listcmd,""COL_GREEN"! "COL_EASY" lub "COL_GREEN"/o "COL_EASY"- Czat globalny. \n");
			strcat(listcmd,""COL_GREEN"# "COL_EASY"- Czat frakcyjny. \n");
			strcat(listcmd,""COL_GREEN"$ "COL_EASY"- Czat międzyfrakcyjny. \n");
			strcat(listcmd,""COL_GREEN"^ "COL_EASY"- Czat firmowy. \n");
			strcat(listcmd,""COL_GREEN"/b "COL_EASY"- Czat lokalny, bardzo bliskiego zasięgu. \n");
			strcat(listcmd,""COL_GREEN"/do "COL_EASY"- Opisywanie akcji otoczenia względem gracza. \n");
			strcat(listcmd,""COL_GREEN"/s "COL_EASY"- Szept. \n");
			strcat(listcmd,""COL_GREEN"/k "COL_EASY"- Krzyk. \n");
			strcat(listcmd,""COL_GREEN"/me "COL_EASY"- Opisywanie akcji gracza. \n");
			strcat(listcmd,""COL_GREEN"/pm | /w "COL_EASY"- Prywatna wiadomość. \n");
			strcat(listcmd,""COL_GREEN"/togpm "COL_EASY"- Włączasz/Wyłączasz PW. \n");
			strcat(listcmd,""COL_GREEN"/re "COL_EASY"- Odpisujesz do osoby, która ostatnio napisała do Ciebie na PW. \n");
			strcat(listcmd,""COL_GREEN"@ "COL_EASY"- Oznaczenie gracza, np. !Siema @nickgracza\n");
			ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, "Komendy czatu", listcmd,"OK","");
		}
		case 2:
		{
			new listcmd[3000];
			strcat(listcmd,""COL_GREEN"/pomoc "COL_EASY"- Pomoc. \n");
			strcat(listcmd,""COL_GREEN"/gps "COL_EASY"- Nawigacja do przydatnych miejsc. \n");
			strcat(listcmd,""COL_GREEN"/lag "COL_EASY"- Za dużo obiektów? Możesz poprawić wydajność za pomocą tej komendy. \n");
			strcat(listcmd,""COL_GREEN"/v "COL_EASY"- Zarządzanie prywatnymi pojazdami. \n");
			strcat(listcmd,""COL_GREEN"/zlecenie "COL_EASY"- Lista zleceń dla kierowców. \n");
			strcat(listcmd,""COL_GREEN"/eq "COL_EASY"- Ekwipunek. \n");
			strcat(listcmd,""COL_GREEN"/podnies "COL_EASY"- Podnosisz wybrany przedmiot. \n");
			strcat(listcmd,""COL_GREEN"/wezwij "COL_EASY"- Wezwanie wybranej służby. \n");
			strcat(listcmd,""COL_GREEN"/pay "COL_EASY"- Przekazywanie kasy. \n");
			strcat(listcmd,""COL_GREEN"/stats "COL_EASY"- Wyświetlanie statystyk. \n");
			strcat(listcmd,""COL_GREEN"/haslo "COL_EASY"- Zmiana hasła. \n");
			strcat(listcmd,""COL_GREEN"/pasy "COL_EASY"- Zapinasz/Odpinasz pasy. \n");
			strcat(listcmd,""COL_GREEN"/dokumenty "COL_EASY"- Pokazujesz dokumenty. \n");
			strcat(listcmd,""COL_GREEN"/wykop "COL_EASY"- Wyrzucasz pasażera z pojazdu. \n");
			strcat(listcmd,""COL_GREEN"/radio "COL_EASY"- Radio. \n");
			strcat(listcmd,""COL_GREEN"/fonline "COL_EASY"- Frekwencja frakcji. \n");
			strcat(listcmd,""COL_GREEN"/anim "COL_EASY"- Lista animacji. \n");
			strcat(listcmd,""COL_GREEN"/karoseria "COL_EASY"- Naprawiasz karoserię pod bazą PD. \n");
			strcat(listcmd,""COL_GREEN"/firmy "COL_EASY"- Lista firm i wolnych siedzib. \n");
			strcat(listcmd,""COL_GREEN"/kluczyki "COL_EASY"- Pożyczasz kluczyki dla innego gracza do swojego pojazdu. \n");
			strcat(listcmd,""COL_GREEN"/report "COL_EASY"- Reportujesz gracza. \n");
			strcat(listcmd,""COL_GREEN"/admins "COL_EASY"- Lista Administratorów online. \n");
			strcat(listcmd,""COL_GREEN"/autorzy "COL_EASY"- Ludzie którzy zaangażowali się w powstanie projektu Highway Life. \n");
			ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, "Podstawowe komendy gracza", listcmd,"OK","");
		}
		case 3:
		{
			new listcmd[3000];
			strcat(listcmd,""COL_WHITE"["COL_GREEN"POL"COL_WHITE"]\t"COL_POL"Policja"COL_WHITE"\t["COL_GREEN"POL"COL_WHITE"]\n");
			strcat(listcmd,""COL_WHITE"["COL_GREEN"SG"COL_WHITE"]\t"COL_BORG"Straż Graniczna"COL_WHITE"\t["COL_GREEN"SG"COL_WHITE"]\n");
			strcat(listcmd,""COL_WHITE"["COL_GREEN"RT"COL_WHITE"]\t"COL_EMRG"Służby Ratunkowe"COL_WHITE"\t["COL_GREEN"RT"COL_WHITE"]\n");
			strcat(listcmd,""COL_WHITE"["COL_GREEN"PD"COL_WHITE"]\t"COL_ROADA"Pomoc Drogowa"COL_WHITE"\t["COL_GREEN"PD"COL_WHITE"]\n");
			strcat(listcmd,""COL_WHITE"["COL_GREEN"TX"COL_WHITE"]\t"COL_TAXI"Taxi"COL_WHITE"\t["COL_GREEN"TX"COL_WHITE"]\n");
			strcat(listcmd,""COL_WHITE"["COL_GREEN"MP"COL_WHITE"]\t"COL_MAFIA"Mafia Paliwowa"COL_WHITE"\t["COL_GREEN"MP"COL_WHITE"]\n");
			Dialog_Show(playerid, FRACTIONCMDS, DIALOG_STYLE_TABLIST, "Komendy frakcji", listcmd, "Wybierz", "Anuluj");
		}
		case 4:
		{
			new listcmd[3000];
			if(gracz[playerid][MapperLvl] >= 2) 
			{
				strcat(listcmd,""COL_GREEN"/mmc "COL_EASY"- Przydatne obiekty. \n");
			}
			strcat(listcmd,""COL_GREEN"/mc "COL_EASY"- Tworzenie obiektu. \n");
			strcat(listcmd,""COL_GREEN"/msel "COL_EASY"- Wybieranie obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mdel "COL_EASY"- Usuwanie obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mcopy "COL_EASY"- Kopiowanie obiektu bez MMAT. \n");
			strcat(listcmd,""COL_GREEN"/mcopyex "COL_EASY"- Kopiowanie obiektu razem z teksturą MMAT. \n");
			strcat(listcmd,""COL_GREEN"/mmat "COL_EASY"- Ustawianie textury/textu dla obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mgate "COL_EASY"- Konfiguracja ruchomego obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mrx "COL_EASY"- Ustawienie obrotu osi X obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mry "COL_EASY"- Ustawienie obrotu osi Y obiektu. \n");
			strcat(listcmd,""COL_GREEN"/mrz "COL_EASY"- Ustawienie obrotu osi Z obiektu. \n");
			ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, "Komendy edytora obiektów", listcmd,"OK","");
		}
		case 5:
		{
			new listcmd[3000];
			strcat(listcmd,""COL_GREY"Poniższa klawiszlogia obowiązuje na domyślnych ustawieniach sterowania GTA:SA. \n");
			strcat(listcmd,""COL_GREY"Za pomocą danych klawiszy, możesz uruchomić następujące funkcjonalności: \n");
			strcat(listcmd,""COL_GREEN"Klawisz Y "COL_EASY"- Odpalanie/Gaszenie pojazdu. \n");
			strcat(listcmd,""COL_GREEN"Klawisz N "COL_EASY"- Kolejna stacja radiowa (tylko w pojazdach). \n");
			strcat(listcmd,""COL_GREEN"Klawisz 2 "COL_EASY"- Zarządzanie pojazdem. \n");
			strcat(listcmd,""COL_GREEN"Klawisz H "COL_EASY"-  Otwieranie/Zamykanie bram. \n");
			strcat(listcmd,""COL_GREEN"Klawisz spacji "COL_EASY"-  Zaciąganie/Odciąganie ręcznego. \n");
			ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, "Klawiszologia", listcmd,"OK","");
		}
		case 6:
		{
			ShowPremiumMenu(playerid);
			//Info(playerid, "Już wkrótce.");
		}
	}
	return 1;
}

Dialog:FAQDIALOG(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid, "/pomoc");
	new faq_answer[1024];
	format(faq_answer, 1024, ""COL_ORANGE"Pytanie %d: "COL_RED"%s\n\n"COL_LIME"Odpowiedź: "COL_GREEN"%s", listitem+1, faq_data[gui_cache[playerid][listitem][0]], faq_data[gui_cache[playerid][listitem][0]+1]);
	Dialog_Show(playerid, FAQANSWER, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_GREEN"FAQ - Odpowiedź na pytanie"COL_RED" «•", faq_answer, "Wstecz", "Anuluj");
	return 1;
}

Dialog:FAQANSWER(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	dialog_POMOC(playerid, 1, 0, "null");
	return 1;
}

Dialog:FRACTIONCMDS(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new listcmd[2048];
	strcat(listcmd,""COL_GREEN"/frakcja "COL_EASY"- Zarządzanie frakcją. "COL_RED"(Lider/V-ce Lider) \n");
	strcat(listcmd,""COL_GREEN"/fkapital "COL_EASY"- Sprawdzanie kapitału frakcji. \n");
	strcat(listcmd,""COL_GREEN"# "COL_EASY"- Czat frakcyjny. \n");
	strcat(listcmd,""COL_GREEN"/duty [start/stop/info] "COL_EASY"- Wchodzenie/Wychodzenie na służbę lub sprawdzanie statusu służby. \n");
	//strcat(listcmd,""COL_GREEN"/fzajety "COL_EASY"- Informujesz wszystkich na czacie, że aktualnie jesteś zajętym pracownikiem. \n");
	//strcat(listcmd,""COL_GREEN"/fwolny "COL_EASY"- Informujesz wszystkich na czacie, że aktualnie jesteś wolnym pracownikiem. \n");
	switch(listitem)
	{
		case 0://policja
		{
			strcat(listcmd,""COL_GREEN"$ "COL_EASY"- Czat międzyfrakcyjny. \n");
			strcat(listcmd,""COL_GREEN"/pacholek "COL_EASY"- Zarządzanie pachołkami. \n");
			strcat(listcmd,""COL_GREEN"/wezwania "COL_EASY"- Lista wezwań. \n");
			strcat(listcmd,""COL_GREEN"/z "COL_EASY"- Wysłanie do gracza nakazu zatrzymania się. \n");
			strcat(listcmd,""COL_GREEN"/m "COL_EASY"- Megafon. \n");
			strcat(listcmd,""COL_GREEN"/mandat "COL_EASY"- Wystawienie mandatu dla gracza. \n");
			strcat(listcmd,""COL_GREEN"/kartoteka "COL_EASY"- Przeglądanie kartoteki danego gracza. \n");
			//strcat(listcmd,""COL_GREEN"/kajdanki "COL_EASY"-  Zakładanie/Zdejmowanie kajdanek (unieruchomienie gracza). \n");
			strcat(listcmd,""COL_GREEN"/zakuj "COL_EASY"-  Zakładanie kajdanek (unieruchomienie gracza). \n");
			strcat(listcmd,""COL_GREEN"/rozkuj "COL_EASY"-  Zdejmowanie kajdanek. \n");
			strcat(listcmd,""COL_GREEN"/drag "COL_EASY"- Przykuwanie gracza do siebie. \n");
			strcat(listcmd,""COL_GREEN"/undrag "COL_EASY"- Odkuwanie gracza od siebie. \n");
			strcat(listcmd,""COL_GREEN"/sc "COL_EASY"- Nadanie statusu 'Scigany/Poszukiwany'. \n");
			strcat(listcmd,""COL_GREEN"/scdel "COL_EASY"- Usuwanie statusu  'Scigany/Poszukiwany'. \n");
			strcat(listcmd,""COL_GREEN"/sclist "COL_EASY"- Lista graczy posiadających status 'Scigany/Poszukiwany'. \n");
			strcat(listcmd,""COL_GREEN"/towar "COL_EASY"- Sprawdzanie towaru.\n");
			strcat(listcmd,""COL_GREEN"/areszt "COL_EASY"- Wsadzanie gracza do więzienia.\n");
			strcat(listcmd,""COL_GREEN"/unareszt "COL_EASY"- Wypuszczanie gracza z więzienia.\n");
			strcat(listcmd,""COL_GREEN"/suszarkaon "COL_EASY"- Uruchamianie prędkościomierza.\n");
			strcat(listcmd,""COL_GREEN"/suszarkaoff "COL_EASY"- Wyłączanie prędkościomierza.\n");
			strcat(listcmd,""COL_GREEN"/suszarkaset "COL_EASY"- Zmiana limitu prędkości prędkościomierza.\n");
			strcat(listcmd,""COL_GREEN"/suszarkapokaz "COL_EASY"- Pokazujesz zarejestrowane wykroczenie.\n");
			strcat(listcmd,""COL_GREEN"/parkpol "COL_EASY"- Odholowanie pojazdu na parking policyjny. \n");
			strcat(listcmd,""COL_GREEN"/scigaj /unscigaj "COL_EASY"- Wszczynasz/wycofujesz się z pościgu. \n");
			strcat(listcmd,""COL_GREEN"/alkomat "COL_EASY"- Sprawdzanie stanu trzeźwości. \n");
			strcat(listcmd,""COL_GREEN"/taser "COL_EASY"- Wyciągasz paralizator. \n");
			strcat(listcmd,""COL_GREEN"/ff "COL_EASY"- Włączanie/Wyłączanie FriendlyFire. \n");
		}
		case 1://straż graniczna
		{
			strcat(listcmd,""COL_GREEN"$ "COL_EASY"- Czat międzyfrakcyjny. \n");
			strcat(listcmd,""COL_GREEN"/pacholek "COL_EASY"- Zarządzanie pachołkami. \n");
			strcat(listcmd,""COL_GREEN"/wezwania "COL_EASY"- Lista wezwań. \n");
			strcat(listcmd,""COL_GREEN"/z "COL_EASY"- Wysłanie do gracza nakazu zatrzymania się. \n");
			strcat(listcmd,""COL_GREEN"/m "COL_EASY"- Megafon. \n");
			strcat(listcmd,""COL_GREEN"/mandat "COL_EASY"- Wystawienie mandatu dla gracza. \n");
			strcat(listcmd,""COL_GREEN"/kartoteka "COL_EASY"- Przeglądanie kartoteki danego gracza. \n");
			//strcat(listcmd,""COL_GREEN"/kajdanki "COL_EASY"-  Zakładanie/Zdejmowanie kajdanek (unieruchomienie gracza). \n");
			strcat(listcmd,""COL_GREEN"/zakuj "COL_EASY"-  Zakładanie kajdanek (unieruchomienie gracza). \n");
			strcat(listcmd,""COL_GREEN"/rozkuj "COL_EASY"-  Zdejmowanie kajdanek. \n");
			strcat(listcmd,""COL_GREEN"/drag "COL_EASY"- Przykuwanie gracza do siebie. \n");
			strcat(listcmd,""COL_GREEN"/undrag "COL_EASY"- Odkuwanie gracza od siebie. \n");
			strcat(listcmd,""COL_GREEN"/sc "COL_EASY"- Nadanie statusu dla gracza 'Scigany/Poszukiwany'. \n");
			strcat(listcmd,""COL_GREEN"/sclist "COL_EASY"- Lista graczy posiadających status 'Scigany/Poszukiwany'. \n");
			strcat(listcmd,""COL_GREEN"/towar "COL_EASY"- Sprawdzanie towaru.\n");
			strcat(listcmd,""COL_GREEN"/przejazd "COL_EASY"- Pobranie od gracza opłaty za przejazd przez granicę.\n");
			strcat(listcmd,""COL_GREEN"/rogatkio | /rogatkiz "COL_EASY"- Otwieranie/Zamykanie wszystkich rogatek.\n");
			strcat(listcmd,""COL_GREEN"/areszt "COL_EASY"- Wsadzanie gracza do więzienia.\n");
			strcat(listcmd,""COL_GREEN"/unareszt "COL_EASY"- Wypuszczanie gracza z więzienia.\n");
			strcat(listcmd,""COL_GREEN"/scigaj /unscigaj "COL_EASY"- Wszczynasz/wycofujesz się z pościgu. \n");
			strcat(listcmd,""COL_GREEN"/alkomat "COL_EASY"- Sprawdzanie stanu trzeźwości. \n");
			strcat(listcmd,""COL_GREEN"/taser "COL_EASY"- Wyciągasz paralizator. \n");
			strcat(listcmd,""COL_GREEN"/ff "COL_EASY"- Włączanie/Wyłączanie FriendlyFire. \n");
		}
		case 2://służby ratunkowe
		{
			strcat(listcmd,""COL_GREEN"$ "COL_EASY"- Czat międzyfrakcyjny. \n");
			strcat(listcmd,""COL_GREEN"/pacholek "COL_EASY"- Zarządzanie pachołkami. \n");
			strcat(listcmd,""COL_GREEN"/wezwania "COL_EASY"- Lista wezwań. \n");
			strcat(listcmd,""COL_GREEN"/wybudz "COL_EASY"- Zdejmujesz BW.\n");
			strcat(listcmd,""COL_GREEN"/uncrash "COL_EASY"- Usuwanie statusu wypadku z gracza.\n");
			strcat(listcmd,""COL_GREEN"/ulecz "COL_EASY"- Leczenie gracza.\n");
			strcat(listcmd,""COL_GREEN"/adrenalina "COL_EASY"- Regeneruje zmęczenie.\n");
		}
		case 3://pomoc drogowa
		{
			strcat(listcmd,""COL_GREEN"$ "COL_EASY"- Czat międzyfrakcyjny. \n");
			strcat(listcmd,""COL_GREEN"/pacholek "COL_EASY"- Zarządzanie pachołkami. \n");
			strcat(listcmd,""COL_GREEN"/wezwania "COL_EASY"- Lista wezwań. \n");
			strcat(listcmd,""COL_GREEN"/obd "COL_EASY"- On-Board Diagnostics - diagnoza/naprawa pojazdu.\n");
			strcat(listcmd,""COL_GREEN"/bodyfix "COL_EASY"- Naprawa karoserii.\n");
			strcat(listcmd,""COL_GREEN"/spray "COL_EASY"- Ustawianie koloru spray'a.\n");
			strcat(listcmd,""COL_GREEN"/tune "COL_EASY"- Tuning pojazdu.\n");
			strcat(listcmd,""COL_GREEN"/fnapraw "COL_EASY"- Naprawa pojazdów frakcyjnych.\n");
			strcat(listcmd,""COL_GREEN"Klawisz Lewy Przycisk Myszy (LPM) "COL_EASY"- Holowanie pojazdu (działa tylko w Towtruck).\n");
			strcat(listcmd,""COL_GREEN"Klawisz H "COL_EASY"- Włączasz/Wyłączasz koguty (działa tylko w Towtruck).\n");
		}
		case 4://taxi
		{
			strcat(listcmd,""COL_GREEN"$ "COL_EASY"- Czat międzyfrakcyjny. \n");
			strcat(listcmd,""COL_GREEN"/wezwania "COL_EASY"- Lista wezwań. \n");
			strcat(listcmd,""COL_GREEN"/taxon "COL_EASY"- Uruchamiasz taxometr.\n");
			strcat(listcmd,""COL_GREEN"/taxoff "COL_EASY"- Wyłączasz taxometr.\n");
			strcat(listcmd,""COL_GREEN"/treset "COL_EASY"- Resetujesz taxometr.\n");
			strcat(listcmd,""COL_GREEN"/tstawka "COL_EASY"- Zmieniasz stawkę za km.\n");
			strcat(listcmd,""COL_GREEN"/trachunek "COL_EASY"- Wystawiasz graczowi rachunek naliczony przez taxometr.\n");	
		}
		case 5://mafia
		{
			strcat(listcmd,""COL_GREEN"/napad "COL_EASY"- Inicjacja napadu (wymagany kod PIN).\n");
			strcat(listcmd,""COL_GREEN"/mgetpin "COL_EASY"- Odczyt kodu PIN do wykonania napadu "COL_RED"(Tylko Lider.)"COL_WHITE".\n");
			strcat(listcmd,""COL_GREEN"/msetprices "COL_EASY"- Zmiana stawki za litr paliwa "COL_RED"(Tylko Lider.)"COL_WHITE".\n");
			strcat(listcmd,""COL_GREEN"/mfuelstat "COL_EASY"- Ilość paliwa w magazynie.\n");
			strcat(listcmd,""COL_GREEN"/mtank "COL_EASY"- Sprzedawanie paliwa.\n");
			strcat(listcmd,""COL_GREEN"/ff "COL_EASY"- Włączanie/Wyłączanie FriendlyFire. \n");
		}
	}
	ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, "Komendy frakcji", listcmd,"OK","");
	return 1;
}
//********************************************************************************************************************************************************/stats
CMD:stats(playerid, params[])
{
	new str_header[128];
	new str_stats[2048];
	new dd, hh, mm, ss;
	format(str_header, 128, "{7e6644}» "COL_GREY"Statystyki postaci:{0d644e} %s", nick(playerid));
	format(str_stats, 2048, "Statystyka\tWartość");
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Nick\t"COL_EASY"%s", str_stats, nick(playerid));
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Nick IC\t"COL_EASY"%s", str_stats, GetICName(playerid));
	//format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Konto master\t"COL_EASY"%s", str_stats, gracz[playerid][master_nick]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"UID postaci\t"COL_EASY"%d", str_stats, gracz[playerid][UID]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Status\t"COL_EASY"%s", str_stats, gracz[playerid][statusplayer]);
	if(gracz[playerid][bank_number] != 0) format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Numer konta bankowego:\t"COL_EASY"%d", str_stats, gracz[playerid][bank_number]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Frakcja\t"COL_EASY"%s", str_stats, GetFractionName(gracz[playerid][frakcja], 1));
	if(gracz[playerid][frakcja] != 0)
	{
		new  total_duty_hours, total_duty_min;
		SecToTime2(gracz[playerid][frakcja_totalduty]+gracz[playerid][duty_suma], total_duty_hours, total_duty_min);
		format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Przepracowany czas we frakcji\t"COL_EASY"%d godzin, %d minut", str_stats, total_duty_hours, total_duty_min);
	}
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Przegrano\t%02d godzin, %02d minut, %02d sekund", str_stats, gracz[playerid][PGodz], gracz[playerid][PMin], gracz[playerid][PSek]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Kasa\t"COL_GREEN"%d$", str_stats, Money(playerid));
	if(gracz[playerid][bank_number] != 0) format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Kasa w banku\t"COL_GREEN"%d$", str_stats, gracz[playerid][bank_saldo]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Score\t"COL_EASY"%d", str_stats, GetPlayerScore(playerid));
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Kursy\t"COL_EASY"%d", str_stats, gracz[playerid][kursy]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Zrobione kilometry\t"COL_EASY"%d km", str_stats, gracz[playerid][przebieg]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Siła\t"COL_EASY"%0.3f DMG", str_stats, gracz[playerid][sila]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Odporność\t"COL_EASY"-%0.3f DMG", str_stats, gracz[playerid][odpornosc]);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Styl walki:\t"COL_EASY"%s", str_stats, GetFightStyleName(playerid));
	new fightstyle_timestamp = gracz[playerid][fight_timestamp_end]-serwer[time_timestamp];
	if(fightstyle_timestamp < 0) fightstyle_timestamp = 0;
	SecToTime(fightstyle_timestamp, dd, hh, mm, ss);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Ważność stylu walki:\t"COL_GREY"%02d dni, %02d godzin, %02d minut, %02d sekund", str_stats, dd, hh, mm, ss);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_GREY"Karnet\t"COL_EASY"%d min", str_stats, gracz[playerid][karnet]/60);
	format(str_stats, 2048, "%s\n{77fd04}» "COL_YELLOW"Żetony premium\t"COL_EASY"%d "COL_GREY"sztuk", str_stats, gracz[playerid][gold]);
	if(isvip(playerid))
	{
		new vip_timestamp = gracz[playerid][vip]-serwer[time_timestamp];
		if(vip_timestamp < 0) vip_timestamp = 0;
		SecToTime(vip_timestamp, dd, hh, mm, ss);
		format(str_stats, 2048, "%s\n{77fd04}» "COL_ORANGE"Konto premium\t"COL_GREY"%02d dni, %02d godzin, %02d minut, %02d sekund", str_stats, dd, hh, mm, ss);
	}
	if(gracz[playerid][skin_custom_expire] > serwer[time_timestamp])
	{
		new cskin_timestamp = gracz[playerid][skin_custom_expire]-serwer[time_timestamp];
		SecToTime(cskin_timestamp, dd, hh, mm, ss);
		format(str_stats, 2048, "%s\n{77fd04}» "COL_ORANGE"Ważność personalnego skina\t"COL_GREY"%02d dni, %02d godzin, %02d minut, %02d sekund", str_stats, dd, hh, mm, ss);
	}
	ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, str_header, str_stats,"Zamknij","");
	return 1;
}
//********************************************************************************************************************************************************/stats
CMD:haslo(playerid, params[])
{
	Dialog_Show(playerid, CHANGEPASS, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_GREEN"Zmiana hasła"COL_RED" «•", ""COL_WHITE"Podaj nowe hasło"COL_RED"(Hasło musi zawierać od 4 do 16 znaków)"COL_WHITE":", "Zmień", "Anuluj");
	return 1;
}
Dialog:CHANGEPASS(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	
	switch(strlen(inputtext))
	{
		case 4..16:
		{
			SendClientMessageEx(playerid, 0xFF0000FF, "[HASŁO] "COL_WHITE"Zmieniłeś swoje hasło na: "COL_PURPLE"%s", inputtext);
			new pass_hash_final[512];		
			format(pass_hash_final, 512, "%d_%s_%s", gracz[playerid][UID], inputtext, BCRYPT_SALT);
			bcrypt_hash(pass_hash_final, BCRYPT_COST, "OnChangePassHashed", "d", playerid);
		}
		default:
		{
			Dialog_Show(playerid, CHANGEPASS, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_GREEN"Zmiana hasła"COL_RED" «•", ""COL_WHITE"Podaj nowe hasło"COL_RED"(Hasło musi zawierać od 4 do 16 znaków)"COL_WHITE":", "Zmień", "Anuluj");
		}
	}
	return 1;
}

task OnChangePassHashed(playerid)
{
	bcrypt_get_hash(gracz[playerid][Haslo]);
	mq_format("UPDATE `Konta` SET `Haslo`='%s' WHERE `id`='%d';", gracz[playerid][Haslo], gracz[playerid][UID]);
	mq_send("QChangePass");
	return 1;
}
//********************************************************************************************************************************************************/eq i /podnies
CMD:eq(playerid, params[])
{
	ListItems(playerid);
	return 1;
}

CMD:podnies(playerid, params[])
{
	PickItemForPlayer(playerid);
	return 1;
}
//********************************************************************************************************************************************************/pay
CMD:pay(playerid, params[])
{
	if(gracz[playerid][PGodz] < 6) return Error(playerid, "Musisz mieć minimum 6 godzin całkowitego czasu ONLINE.");
	new targetid, price;
	if(sscanf(params,"dd", targetid, price)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /pay [idgracza] [kwota]");
	if(playerid == targetid) return Error(playerid, "Nie możesz użyć tej komendy na sobie.");
	if(!IsPlayerConnected(playerid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest zalogowany.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	if(price < 1) return Error(playerid, "Kwota jest za niska.");
	if(price > 500000) return Error(playerid, "Kwota jest za wysoka (max 500k).");
	if(price > Money(playerid)) return Error(playerid, "Nie posiadasz tyle gotówki.");
	TakeMoney(playerid, price);
	GiveMoney(targetid, price);
	new strInfo[144];
	format(strInfo, 144, ""COL_BLUE"Przekazałeś "COL_GREEN"%d$"COL_BLUE" dla gracza {%06x}%s"COL_BLUE".", price, GetPlayerColor(targetid) >>> 8, nick(targetid));
	SendClientMessage(playerid, -1, strInfo);
	format(strInfo, 144, ""COL_BLUE"Dostałeś "COL_GREEN"%d$"COL_BLUE" od gracza {%06x}%s"COL_BLUE".", price, GetPlayerColor(playerid) >>> 8, nick(playerid));
	SendClientMessage(targetid, -1, strInfo);
	mq_format("INSERT INTO `LogCash` (`od`, `do`, `sum`) VALUES ('%d', '%d', '%d');", gracz[playerid][UID], gracz[targetid][UID], price);
	mq_send("QTransferMoneyLog");
	return 1;
}
//********************************************************************************************************************************************************/pasy
CMD:pasy(playerid, params[])
{
	if(gracz[playerid][opu_vehicleid] == 0) return Error(playerid, "Nie jesteś w pojeździe.");
	if(IsVehicleBike(pojazd[gracz[playerid][opu_vehicleid]][v_model])) return Error(playerid, "Ten pojazd nie jest wyposażony w pasy bezpieczeństwa.");
	new strCommand[32];
	if(gracz[playerid][pasy])
	{
		gracz[playerid][pasy] = false;
		format(strCommand, 32, "/me odpina pasy.");
		LeftNotifyShow(playerid, "Sukces!", "Pasy zostaly ~r~odpiete~w~.", LN_RED);
	}
	else 
	{
		gracz[playerid][pasy] = true;
		format(strCommand, 32, "/me zapina pasy.");
		LeftNotifyShow(playerid, "Sukces!", "Pasy zostaly ~g~zapiete~w~.", LN_GREEN);
	}
	PC_EmulateCommand(playerid, strCommand);
	return 1;
}
//********************************************************************************************************************************************************/egzamin - zdawanie prawa jazdy
CMD:egzamin(playerid, params[])
{
	if(gracz[playerid][dokumenty] == 0)
	{
		Error(playerid, "Nie posiadasz dokumentów.");
		LeftNotifyShow(playerid, "info", "Dokumenty mozesz wyrobic w urzedzie. Urzad znajduje sie za hotelem Highway Life (SPAWN).", LN_BLUE, 15);
		return 1;
	}
	if(IsPlayerInRangeOfPoint(playerid, 2.0, XYZ_PRAWKO))
	{
		new strEgzamin[2048];
		format(strEgzamin, 2048, "Egzamin\tStatus\tCena");
		format(strEgzamin, 2048, "%s\n"COL_PURPLE"»"COL_WHITE" Egzamin "COL_BLUE"teoretyczny"COL_WHITE" kat. B"COL_WHITE"\t[%s"COL_WHITE"]\t{FFCE00}%d$", strEgzamin, (gracz[playerid][prawko_TB]) ? (""COL_GREEN"zdany") : (""COL_RED"niezdany"), PRICE_PRAWKO_TB);
		format(strEgzamin, 2048, "%s\n"COL_PURPLE"»"COL_WHITE" Egzamin "COL_ORANGE"praktyczny"COL_WHITE" kat. B"COL_WHITE"\t[%s"COL_WHITE"]\t{FFCE00}%d$", strEgzamin, (gracz[playerid][prawko_PB]) ? (""COL_GREEN"zdany") : (""COL_RED"niezdany"), PRICE_PRAWKO_PB);
		format(strEgzamin, 2048, "%s\n"COL_DRVONLINE"»"COL_WHITE" Egzamin "COL_BLUE"teoretyczny"COL_WHITE" kat. CE"COL_WHITE"\t[%s"COL_WHITE"]\t{FFCE00}%d$", strEgzamin, (gracz[playerid][prawko_TCE]) ? (""COL_GREEN"zdany") : (""COL_RED"niezdany"), PRICE_PRAWKO_TCE);
		format(strEgzamin, 2048, "%s\n"COL_DRVONLINE"»"COL_WHITE" Egzamin "COL_ORANGE"praktyczny"COL_WHITE" kat. CE"COL_WHITE"\t[%s"COL_WHITE"]\t{FFCE00}%d$", strEgzamin, (gracz[playerid][prawko_PCE]) ? (""COL_GREEN"zdany") : (""COL_RED"niezdany"), PRICE_PRAWKO_PCE);
		Dialog_Show(playerid, SELECTEGZAMIN, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_GREEN"Egzamin na prawo jazdy"COL_RED" «•", strEgzamin, "Wybierz", "Anuluj");
	}
	else Error(playerid, "Musisz znajdować się w WORD aby przystąpić do egzaminu. ");
	return 1;
}

Dialog:SELECTEGZAMIN(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	gracz[playerid][driver_license_qid] = 0;
	gracz[playerid][driver_license_points] = 0;
	switch(listitem)
	{
		case 0://teoria B
		{
			if(gracz[playerid][prawko_TB] > 0) return Error(playerid, "Ten egzamin już zdałeś/aś.");
			if(Money(playerid) < PRICE_PRAWKO_TB) return Error(playerid, "Niewystarczająca ilość gotówki.");
			TakeMoney(playerid, PRICE_PRAWKO_TB);
			gracz[playerid][driver_license_type] = 0;
			Process_TeoriaPrawko(playerid);
		}
		case 1://praktyka B
		{
			if(gracz[playerid][prawko_PB] > 0) return Error(playerid, "Ten egzamin już zdałeś/aś.");
			if(gracz[playerid][prawko_TB] == 0) return Error(playerid, "Musisz zdać najpierw egzamin teoretyczny.");
			if(Money(playerid) < PRICE_PRAWKO_PB) return Error(playerid, "Niewystarczająca ilość gotówki.");
			if(serwer[prawkoegz_delay] > serwer[time_timestamp]) return Error(playerid, "Odczekaj moment. Zbyt wiele osób chcę się dostać na praktykę.");
			//szukanie L-ki
			new learn_vehicleid = -1;
			new bool:area_inuse = false;
			for(new v = GetVehiclePoolSize(); v != -1; v--)
			{
				if(pojazd[v][v_model] == 0) continue;
				if(pojazd[v][v_owner_type] == VEHICLE_PUBLIC)
				{
					if(pojazd[v][v_owner] == VO_DRVLICENSE)
					{
						if(pojazd[v][v_model] == 589)//CLUB
						{
							learn_vehicleid = v;
						}
						if(IsVehicleInUse(v) != INVALID_PLAYER_ID)//jesli jakas L-ka jest zajeta, to plac manewrowy jest nieczynny
						{
							area_inuse = true;
							break;
						}
					}
				}
			}
			if(area_inuse)
			{
				Error(playerid, "Plac manewrowy jest zajęty. Spróbuj później.");
			}
			else
			{
				serwer[prawkoegz_delay] = serwer[time_timestamp]+2;
				RespawnAllLearnVeh();//respawn wszystkich L-ek
				gracz[playerid][driver_license_time] = (60*TIME_EXAM_B);
				gracz[playerid][driver_license_cp] = 0;
				Handbrake(learn_vehicleid, 0);
				TakeMoney(playerid, PRICE_PRAWKO_PB);
				SetVehicleToRespawn(learn_vehicleid);
				Handbrake(learn_vehicleid, 1);
				PutPlayerInVehicle(playerid, learn_vehicleid, 0);
				new cpid = gracz[playerid][driver_license_cp];
				SetPlayerCheckpoint(playerid, driver_license_cp_katB[cpid][0], driver_license_cp_katB[cpid][1], driver_license_cp_katB[cpid][2]-0.8, 2.3);
			}
		}
		case 2://teoria CE
		{
			if(gracz[playerid][prawko_TCE] > 0) return Error(playerid, "Ten egzamin już zdałeś/aś.");
			if(gracz[playerid][prawko_TB] == 0 || gracz[playerid][prawko_PB] == 0) return Error(playerid, "Musisz najpierw zdać egzaminy na prawo jazdy kat. B.");
			if(Money(playerid) < PRICE_PRAWKO_TCE) return Error(playerid, "Niewystarczająca ilość gotówki.");
			TakeMoney(playerid, PRICE_PRAWKO_TCE);
			gracz[playerid][driver_license_type] = 1;
			Process_TeoriaPrawko(playerid);
		}
		case 3://praktyka CE
		{
			if(gracz[playerid][prawko_PCE] > 0) return Error(playerid, "Ten egzamin już zdałeś/aś.");
			if(gracz[playerid][prawko_TB] == 0 || gracz[playerid][prawko_PB] == 0) return Error(playerid, "Musisz najpierw zdać egzaminy na prawo jazdy kat. B.");
			if(gracz[playerid][prawko_TCE] == 0) return Error(playerid, "Musisz zdać najpierw egzamin teoretyczny.");
			if(Money(playerid) < PRICE_PRAWKO_PCE) return Error(playerid, "Niewystarczająca ilość gotówki.");
			if(serwer[prawkoegz_delay] > serwer[time_timestamp])  return Error(playerid, "Odczekaj moment. Zbyt wiele osób chcę się dostać na praktykę.");
			//szukanie L-ki
			new learn_vehicleid = -1;
			new bool:area_inuse = false;
			for(new v = GetVehiclePoolSize(); v != -1; v--)
			{
				if(pojazd[v][v_model] == 0) continue;
				if(pojazd[v][v_owner_type] == VEHICLE_PUBLIC)
				{
					if(pojazd[v][v_owner] == VO_DRVLICENSE)
					{
						if(pojazd[v][v_model] == 514)//TANKER
						{
							learn_vehicleid = v;
						}
						if(IsVehicleInUse(v) != INVALID_PLAYER_ID)//jesli jakas L-ka jest zajeta, to plac manewrowy jest nieczynny
						{
							area_inuse = true;
							break;
						}
					}
				}
			}
			if(area_inuse)
			{
				Error(playerid, "Plac manewrowy jest zajęty. Spróbuj później.");
			}
			else
			{
				serwer[prawkoegz_delay] = serwer[time_timestamp]+2;
				RespawnAllLearnVeh();//respawn wszystkich L-ek
				gracz[playerid][driver_license_time] = (60*TIME_EXAM_CE);
				gracz[playerid][driver_license_cp] = 0;
				Handbrake(learn_vehicleid, 0);
				TakeMoney(playerid, PRICE_PRAWKO_PCE);
				SetVehicleToRespawn(learn_vehicleid);
				Handbrake(learn_vehicleid, 1);
				PutPlayerInVehicle(playerid, learn_vehicleid, 0);
				new cpid = gracz[playerid][driver_license_cp];
				SetPlayerCheckpoint(playerid, driver_license_cp_katCE[cpid][0], driver_license_cp_katCE[cpid][1], driver_license_cp_katCE[cpid][2]-0.8, 2.3);
			}
		}
	}
	return 1;
}

task Process_TeoriaPrawko(playerid)
{
	new strContent[2048];
	new strTitle[128];
	new qid = gracz[playerid][driver_license_qid];
	format(strTitle, 128, ""COL_RED"•» "COL_BLUE"Pytanie "COL_GREEN"%d"COL_BLUE"/"COL_ORANGE"15"COL_RED" «•", gracz[playerid][driver_license_qid]+1);
	if(gracz[playerid][driver_license_qid] < 10) format(strContent, 2048, ""COL_RED"%d."COL_DRVONLINE" %s", qid+1, driver_license_general[qid][qst_question]);//ogólne
	else if(gracz[playerid][driver_license_type] == 0) format(strContent, 2048, ""COL_RED"%d."COL_DRVONLINE" %s", qid+1, driver_license_katB[qid-10][qst_question]);//kat B
	else format(strContent, 2048, ""COL_RED"%d."COL_DRVONLINE" %s", qid+1, driver_license_katCE[qid-10][qst_question]);//kat CE
	Dialog_Show(playerid, EGZAMINPROCESS, DIALOG_STYLE_MSGBOX, strTitle, strContent, "Tak", "Nie");
	return 1;
}

Dialog:EGZAMINPROCESS(playerid, response, listitem, inputtext[])
{
	if(gracz[playerid][driver_license_qid] < 15)
	{
		new qid = gracz[playerid][driver_license_qid];
		new correct_answer;
		if(qid < 10) correct_answer = driver_license_general[qid][qst_answer];
		else if(gracz[playerid][driver_license_type] == 0) correct_answer = driver_license_katB[qid-10][qst_answer];
		else correct_answer = driver_license_katCE[qid-10][qst_answer];
		if(correct_answer == response) gracz[playerid][driver_license_points]++;
		gracz[playerid][driver_license_qid]++;
		if(gracz[playerid][driver_license_qid] < 15) Process_TeoriaPrawko(playerid);
		else//egzamin zakończony - wyniki here
		{
			new bool:zdany = (gracz[playerid][driver_license_points] < 12) ? (false) : (true);
			if(zdany)
			{
				if(gracz[playerid][driver_license_type] == 0)//B
				{
					gracz[playerid][prawko_TB] = 1;
					mq_format("UPDATE `Konta` SET `prawko_TB`='%d' WHERE `id`='%d';", gracz[playerid][prawko_TB], gracz[playerid][UID]);
				}
				else//CE
				{
					gracz[playerid][prawko_TCE] = 1;
					mq_format("UPDATE `Konta` SET `prawko_TCE`='%d' WHERE `id`='%d';", gracz[playerid][prawko_TCE], gracz[playerid][UID]);
				}
				mq_send("QUpdatePrawkoTeoria");
			}
			//wyniki
			new strResult[2048];
			format(strResult, 2048, ""COL_WHITE"Egzamin zakończony!");
			format(strResult, 2048, "%s\n"COL_WHITE"Możesz maxymalnie popełnić "COL_RED"3 błędy"COL_WHITE".", strResult);
			format(strResult, 2048, "%s\n"COL_WHITE"Zdobyta ilość punktów: "COL_GREEN"%d"COL_BLUE"/"COL_ORANGE"15", strResult, gracz[playerid][driver_license_points]);
			format(strResult, 2048, "%s\n"COL_WHITE"Wynik egzaminu: %s", strResult, (zdany) ? (""COL_GREEN"POZYTYWNY") : (""COL_RED"NEGATYWNY"));
			format(strResult, 2048, "%s\n"COL_WHITE"Zdany egzamin teoretyczny, pozwala na przystąpienie do egzaminu praktycznego.", strResult);
			MessageGUIEx(playerid, ""COL_RED"•» "COL_BLUE"Egzamin zakończony"COL_RED" «•",  strResult);
		}
	}
	return 1;
}

task Process_PraktykaPrawko(playerid)
{
	new vehicleid = gracz[playerid][opu_vehicleid];
	if(vehicleid == 0) return 1;
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_DRVLICENSE)
	{
		if(pojazd[vehicleid][v_model] == 589)//CLUB - zdawanie prawka na B
		{
			if(gracz[playerid][driver_license_time] > 0)//odliczanie czasu podczas zdawanie prawka
			{
				if(pojazd[vehicleid][v_HP] < 999.85) PrzerwijEgzaminPrawko(playerid, "Uszkodzono pojazd.");
				else if(gracz[playerid][opu_speed] > 60) PrzerwijEgzaminPrawko(playerid, "Przekroczono prędkość.");
				else
				{
					new strExam[1024];
					new tTrash;
					new tMin, tSec;
					gracz[playerid][driver_license_time]--;
					SecToTime(gracz[playerid][driver_license_time], tTrash, tTrash, tMin, tSec);
					new engine, lights, alarm, doors, bonnet, boot, objective;
					GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
					format(strExam, 1024, "~w~Witaj na egzaminie prawa jazdy ~y~kat. B~w~. Masz ~r~%d minut~w~ na zdanie egzaminu. Aby zdac, musisz spelnic warunki:", TIME_EXAM_B);
					format(strExam, 1024, "%s~n~%s- zapiac pasy.~n~%s- wlaczyc swiatla.~n~~w~- nie zniszczyc pojazdu.~n~%s- nie przekraczac 60km/h.~n~~w~- zaliczyc wszystkie punkty kontrolne. (~g~%d~w~/~r~%d~w~)", strExam, (gracz[playerid][pasy]) ? ("~g~~h~") : ("~w~"), (lights) ? ("~g~~h~") : ("~w~"), (gracz[playerid][opu_speed] > 40) ? ("~r~") : ("~w~"), gracz[playerid][driver_license_cp], sizeof(driver_license_cp_katB));
					format(strExam, 1024, "%s~n~~r~~h~~h~Niespelnienie tych warunkow~n~~r~~h~~h~przerywa egzamin.~n~~b~~h~~h~Powodzenia!~n~~n~Pozostaly czas: ~r~%02d~w~:~r~%02d~w~.", strExam, tMin, tSec);
					ShowRightMessageBox(playerid, "EGZAMIN", strExam);
				}
			}
			else//czas upłynął
			{
				PrzerwijEgzaminPrawko(playerid, "Czas upłynął.");
			}
		}
		else if(pojazd[vehicleid][v_model] == 514)//TANKER - Zdawanie prawka na CE
		{
			if(gracz[playerid][driver_license_time] > 0)//odliczanie czasu podczas zdawanie prawka
			{
				if(pojazd[vehicleid][v_HP] < 999.85) PrzerwijEgzaminPrawko(playerid, "Uszkodzono pojazd.");
				else if(gracz[playerid][opu_speed] > 60) PrzerwijEgzaminPrawko(playerid, "Przekroczono prędkość.");
				else if(GetVehicleTrailer(vehicleid) == 0 && gracz[playerid][driver_license_cp] > 0) PrzerwijEgzaminPrawko(playerid, "Zgubiłeś naczepe.");
				else
				{
					new strExam[1024];
					new tTrash;
					new tMin, tSec;
					gracz[playerid][driver_license_time]--;
					SecToTime(gracz[playerid][driver_license_time], tTrash, tTrash, tMin, tSec);
					new engine, lights, alarm, doors, bonnet, boot, objective;
					GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
					new trailer_status = GetVehicleTrailer(vehicleid);
					format(strExam, 1024, "~w~Witaj na egzaminie prawa jazdy ~y~kat. CE~w~. Masz ~r~%d minut~w~ na zdanie egzaminu. Aby zdac, musisz spelnic warunki:", TIME_EXAM_CE);
					format(strExam, 1024, "%s~n~%s- zapiac pasy.~n~%s- wlaczyc swiatla.~n~%s- podlaczyc naczepe.~n~~w~- nie zniszczyc pojazdu.~n~%s- nie przekraczac 60km/h.~n~~w~- zaliczyc wszystkie punkty kontrolne. (~g~%d~w~/~r~%d~w~)", strExam, (gracz[playerid][pasy]) ? ("~g~~h~") : ("~w~"), (lights) ? ("~g~~h~") : ("~w~"), (trailer_status) ? ("~g~~h~") : ("~w~"), (gracz[playerid][opu_speed] > 40) ? ("~r~") : ("~w~"), gracz[playerid][driver_license_cp], sizeof(driver_license_cp_katCE));
					format(strExam, 1024, "%s~n~~r~~h~~h~Niespelnienie tych warunkow~n~~r~~h~~h~przerywa egzamin.~n~~b~~h~~h~Powodzenia!~n~~n~Pozostaly czas: ~r~%02d~w~:~r~%02d~w~.", strExam, tMin, tSec);
					ShowRightMessageBox(playerid, "EGZAMIN", strExam);
				}
			}
			else//czas upłynął
			{
				PrzerwijEgzaminPrawko(playerid, "Czas upłynął.");
			}
		}
	}
	return 1;
}

stock PrzerwijEgzaminPrawko(playerid, reason[])
{
 	SetPlayerPos(playerid, XYZ_PRAWKO);
	HideRightMessageBox(playerid);
	new strGUI[512];
	format(strGUI, 512, ""COL_WHITE"Egzamin został przerwany.\n"COL_WHITE"Powód: "COL_RED"%s", reason);
	MessageGUIEx(playerid, ""COL_RED"•» "COL_BLUE"Egzamin zakończony"COL_RED" «•", strGUI);
	RespawnAllLearnVeh();//respawn wszystkich L-ek
	DisablePlayerCheckpoint(playerid);
	return 1;
}

stock RespawnAllLearnVeh()
{
	//respawn wszystkich L-ek
 	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		if(pojazd[v][v_model] == 0) continue;
		if(pojazd[v][v_owner_type] == VEHICLE_PUBLIC)
		{
			if(pojazd[v][v_owner] == VO_DRVLICENSE)
			{
				SetVehicleToRespawn(v);
			}
		}
	}
	return 1;
}

stock DriverLicenseNextCP(playerid)
{
	new vehicleid = gracz[playerid][opu_vehicleid];
	if(vehicleid == 0) return 1;
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PUBLIC && pojazd[vehicleid][v_owner] == VO_DRVLICENSE)
	{
		if(pojazd[vehicleid][v_model] == 589)//CLUB - zdawanie prawka na B
		{
			gracz[playerid][driver_license_cp]++;
			if(gracz[playerid][driver_license_cp] <= sizeof(driver_license_cp_katB)-1)
			{
				new engine, lights, alarm, doors, bonnet, boot, objective;
				GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
				if(!lights) PrzerwijEgzaminPrawko(playerid, "Jazda bez włączonych świateł.");
				else if(!gracz[playerid][pasy]) PrzerwijEgzaminPrawko(playerid, "Niezapięte pasy.");
				else
				{
					new cpid = gracz[playerid][driver_license_cp];
					SetPlayerCheckpoint(playerid, driver_license_cp_katB[cpid][0], driver_license_cp_katB[cpid][1], driver_license_cp_katB[cpid][2]-0.8, 2.3);
				}
			}
			else
			{
				gracz[playerid][prawko_PB] = 1;
				mq_format("UPDATE `Konta` SET `prawko_PB`='%d' WHERE `id`='%d';", gracz[playerid][prawko_PB], gracz[playerid][UID]);
				mq_send("QUpdatePrawkoPraktyka");
				DisablePlayerCheckpoint(playerid);
				SetPlayerPos(playerid, XYZ_PRAWKO);
				SetVehicleToRespawn(vehicleid);
				RespawnAllLearnVeh();
				HideRightMessageBox(playerid);
				new strResult[2048];
				format(strResult, 2048, ""COL_WHITE"Egzamin zakończony!");
				format(strResult, 2048, "%s\n"COL_WHITE"Wynik egzaminu: "COL_GREEN"POZYTYWNY", strResult);
				format(strResult, 2048, "%s\n"COL_WHITE"Gratulacje! Od tej pory możesz legalnie prowadzić pojazdy osobowe na serwerze "COL_DRVONLINE"Highway Life"COL_WHITE".", strResult);
				format(strResult, 2048, "%s\n"COL_WHITE"Aby okazac swoje dokumenty, uzyj: "COL_BLUE"/dokumenty"COL_WHITE".", strResult);
				format(strResult, 2048, "%s\n"COL_ORANGE"SZEROKOŚCI :)", strResult);
				MessageGUIEx(playerid, ""COL_RED"•» "COL_BLUE"Egzamin zakończony"COL_RED" «•",  strResult);
			}
		}
		else if(pojazd[vehicleid][v_model] == 514)//TANKER - zdawanie prawka na CE
		{
			gracz[playerid][driver_license_cp]++;
			if(gracz[playerid][driver_license_cp] <= sizeof(driver_license_cp_katCE)-1)
			{
				new engine, lights, alarm, doors, bonnet, boot, objective;
				GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
				if(!lights) PrzerwijEgzaminPrawko(playerid, "Jazda bez włączonych świateł.");
				else if(!gracz[playerid][pasy]) PrzerwijEgzaminPrawko(playerid, "Niezapięte pasy.");
				else
				{
					new cpid = gracz[playerid][driver_license_cp];
					SetPlayerCheckpoint(playerid, driver_license_cp_katCE[cpid][0], driver_license_cp_katCE[cpid][1], driver_license_cp_katCE[cpid][2]-0.8, 2.3);
				}
			}
			else
			{
				gracz[playerid][prawko_PCE] = 1;
				mq_format("UPDATE `Konta` SET `prawko_PCE`='%d' WHERE `id`='%d';", gracz[playerid][prawko_PCE], gracz[playerid][UID]);
				mq_send("QUpdatePrawkoPraktyka");
				DisablePlayerCheckpoint(playerid);
				SetPlayerPos(playerid, XYZ_PRAWKO);
				SetVehicleToRespawn(vehicleid);
				RespawnAllLearnVeh();
				HideRightMessageBox(playerid);
				new strResult[2048];
				format(strResult, 2048, ""COL_WHITE"Egzamin zakończony!");
				format(strResult, 2048, "%s\n"COL_WHITE"Wynik egzaminu: "COL_GREEN"POZYTYWNY", strResult);
				format(strResult, 2048, "%s\n"COL_WHITE"Gratulacje! Od tej pory możesz legalnie prowadzić pojazdy ciężarowe na serwerze "COL_DRVONLINE"Highway Life"COL_WHITE".", strResult);
				format(strResult, 2048, "%s\n"COL_WHITE"Aby okazac swoje dokumenty, uzyj: "COL_BLUE"/dokumenty"COL_WHITE".", strResult);
				format(strResult, 2048, "%s\n"COL_ORANGE"SZEROKOŚCI :)", strResult);
				MessageGUIEx(playerid, ""COL_RED"•» "COL_BLUE"Egzamin zakończony"COL_RED" «•",  strResult);
			}
		}
	}
	return 1;
}
//********************************************************************************************************************************************************/dokumenty
CMD:dokumenty(playerid, params[])
{
	if(gracz[playerid][dokumenty] == 0)
	{
		Error(playerid, "Nie posiadasz dokumentów.");
		LeftNotifyShow(playerid, "info", "Dokumenty mozesz wyrobic w urzedzie. Urzad znajduje sie za hotelem Highway Life (SPAWN).", LN_BLUE, 15);
		return 1;
	}
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /dokumenty [idgracza]");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	if(gracz[targetid][td_dokumenty] > 0) return Error(playerid, "Ten gracz jest już w trakcie przeglądania dokumentów.");
	new strPrawko[16];
	format(strPrawko, 16, "brak");
	if(gracz[playerid][prawko_TB] && gracz[playerid][prawko_PB] && gracz[playerid][prawko_TCE] && gracz[playerid][prawko_PCE]) format(strPrawko, 16, "B,CE");
	else if(gracz[playerid][prawko_TB] && gracz[playerid][prawko_PB]) format(strPrawko, 16, "B");
	else if(gracz[playerid][prawko_TCE] && gracz[playerid][prawko_PCE]) format(strPrawko, 16, "CE");
	if(gracz[playerid][upr_adr]) format(strPrawko, 16, "%s,ADR", strPrawko);
	if(targetid != playerid)
	{
		new strCommand[64];
		format(strCommand, 64, "/me pokazuje dokumenty dla %s.", GetICName(targetid));
		PC_EmulateCommand(playerid, strCommand);
	}
	Dokument_Show(targetid, GetICName(playerid), gracz[playerid][Wiek], gracz[playerid][Plec], gracz[playerid][Skin], gracz[playerid][UID], strPrawko);
	return 1;
}
//********************************************************************************************************************************************************/report
CMD:report(playerid, params[])
{
	if(gettime() - GetPVarInt(playerid, "ReportSpam") < 20) return Error(playerid, "Odczekaj trochę zanim wyślesz kolejny report.");
	new targetid, reason[256];
	if(sscanf(params,"ds[256]", targetid, reason)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /report [idgracza] [powód]");
	if(targetid == playerid) return Error(playerid, "Nie możesz zreportować siebie samego.");
	if(!logged(targetid)) return Error(playerid, "Ten gracz nie jest zalogowany.");
	SetPVarInt(playerid, "ReportSpam", gettime());
	for(new a = PlayerPoolSize(); a != -1; a--)
	{
		if(gracz[a][loggedin] && gracz[a][AdminLevel])
		{
			SendClientMessageEx(a, 0xFF0000FF, "|REPORT| "COL_GREEN"%s[%d]"COL_WHITE" >> "COL_RED"%s[%d]"COL_WHITE" | Powód: %s", nick(playerid), playerid, nick(targetid), targetid, reason);
		}
	}
	mysql_escape_string(reason, reason, 256, g_SQL);
	mq_format("INSERT INTO `player_report` (`uid`, `targetuid`, `reason`) VALUES ('%d', '%d', '%s');", gracz[playerid][UID], gracz[targetid][UID], reason);
	mq_send("REPORTQUERY");
	SendClientMessageEx(playerid, -1, "(("COL_GREEN"Report na gracza "COL_RED"%s"COL_GREEN" został wysłany! Dzięki!"COL_WHITE"))", nick(targetid));
	return 1;
}
//********************************************************************************************************************************************************/admins
CMD:admins(playerid, params[])
{
	new fstring[256], string[1000];
	new liczae;
	liczae = 0;
	for(new i = PlayerPoolSize(); i != -1; i--)
	{
		if(gracz[i][loggedin])
		{
			if(gracz[i][aaInvisible] == true) continue;
			if(gracz[i][admin_duty] >= 1)
			{
				if(gracz[i][admin_duty] == 1) format(fstring, sizeof(fstring),"{FFAF00}%s {B700FF}(ID:%d) {FFFFFF}- {B7FF00}Typ: {00A09E}Support{FFFFFF}\n", gracz[i][master_nick], i);
				else if(gracz[i][admin_duty] == 2) format(fstring, sizeof(fstring),"{FFAF00}%s {B700FF}(ID:%d) {FFFFFF}- {B7FF00}Typ: {0052dd}Game Master{FFFFFF}\n", gracz[i][master_nick], i);
				else if(gracz[i][admin_duty] >= 3) format(fstring, sizeof(fstring),"{FFAF00}%s {B700FF}(ID:%d) {FFFFFF}- {B7FF00}Typ: {FF0000}Administrator{FFFFFF}\n", gracz[i][master_nick], i);
				strcat(string, fstring, sizeof(string));
				liczae++;
			}
		}
	}
	if(liczae == 0)
	{
		ShowPlayerDialog(playerid,INFO_DIALOG,DIALOG_STYLE_MSGBOX,""COL_RED"»"COL_GREY" Administracja "COL_GREEN"na służbie", "{FFAF00}Brak Administracji ONLINE!","OK","");
	} 
	else
	{
		ShowPlayerDialog(playerid,INFO_DIALOG,DIALOG_STYLE_MSGBOX,""COL_RED"»"COL_GREY" Administracja "COL_GREEN"na służbie",string,"OK","");
	}
	return 1;
}
//*******************************************************************************************************************************************************/binco
CMD:binco(playerid, params[])
{
	if(!IsPlayerInRangeOfPoint(playerid, 2.0, XYZ_BINCO) && !IsPlayerInRangeOfPoint(playerid, 2.0, XYZ_BINCOC)) return Error(playerid, "Nie jesteś w binco.");
	Dialog_Show(playerid, BINCOSELECT, DIALOG_STYLE_LIST, ""COL_RED"•» "COL_BLUE"Binco"COL_RED" «•", ""COL_RED"» "COL_WHITE"Zmień skin ("COL_GREEN"100$"COL_WHITE")\n"COL_RED"» "COL_WHITE"Zakup akcesoria "COL_GREY"[Posiadane akcesoria są w Twoim "COL_ORANGE"/eq"COL_GREY"]", "Wybierz", "Anuluj");
	return 1;
}

Dialog:BINCOSELECT(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0://Zmień skin
		{
			SetPVarInt(playerid, "PayForChangeSkin", 100);
			if(Money(playerid) < GetPVarInt(playerid, "PayForChangeSkin")) return Error(playerid, "Niewystarczająca ilość gotówki ("COL_RED"100$"COL_WHITE").");
			ShowSelectSkinWindow(playerid);
		}
		case 1://Zakup akcesoria
		{
			new strShopList[3048];
			format(strShopList, 3048, "Lp.\tPrzedmiot\tKoszt");
			new list_item;
			new bool:shadowline;
			new slc[9];//shadowline color
			for(new s; s < MAX_ITEMS; s++)
			{
				if(s >= 1 && s <= 43)
				{
					gui_cache[playerid][list_item][0] = s;
					gui_cache[playerid][list_item][1] = strlen(ItemName[s])+s+300;
					slc = (shadowline) ? ("{8D8D8D}") : ("{FFFFFF}");
					format(strShopList, 3048, "%s\n"COL_RED"%d.\t%s%s\t"COL_GREEN"%d$", strShopList, list_item+1, slc, ItemName[s], gui_cache[playerid][list_item][1]);
					if(shadowline) shadowline = false;
					else shadowline = true;
					list_item++;
				}
			}
			Dialog_Show(playerid, BINCOSHOP, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_BLUE"Sklep BINCO - Akcesoria"COL_RED" «•", strShopList, "Kup", "Anuluj");
		}
	}
	return 1;
}

Dialog:BINCOSHOP(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new price = gui_cache[playerid][listitem][1];
	if(price > Money(playerid)) return Error(playerid, "Niewystarczająca ilość gotówki.");
	new itemid = gui_cache[playerid][listitem][0];
	if(CreateItemForPlayer(playerid, itemid, 1))
	{
		new strInfo[512];
		TakeMoney(playerid, price);
		format(strInfo, 512, ""COL_WHITE"Zakupiłeś/aś: "COL_BLUE"%s"COL_WHITE" za "COL_GREEN"%d$"COL_WHITE".", ItemName[itemid], price);
		format(strInfo, 512, "%s\n"COL_WHITE"Akcesoria możesz zakładać, zdejmować oraz dopasować do swojej postaci z poziomu "COL_ORANGE"ekwipunku"COL_WHITE".", strInfo);
		format(strInfo, 512, "%s\n"COL_WHITE"Użyj komendy "COL_ORANGE"/eq"COL_WHITE" aby przeglądać swój ekwipunek.", strInfo);
		MessageGUIEx(playerid, ""COL_RED"•» "COL_GREEN"Zakupiłeś przedmiot"COL_RED" «•", strInfo);
	}
	return 1;
}
//********************************************************************************************************************************************************/bus
CMD:bus(playerid, params[])
{
	if(FractionDutyWorkersCount(F_TAXI) > 0)
	{
		if(GetPlayerScore(playerid) > 30)
		{
			Error(playerid, "Masz powyżej 30 score, na serwerze jest TAXI online - poproś ich o pomoc, użyj: "COL_RED"/wezwij");
			return 1;
		}
	}
	new rangeofbus = IsPlayerInRangeOfBusStation(playerid);
	if(rangeofbus != -1)
	{
		new strStationsList[1024];
		new strPrice[64];
		format(strStationsList, 1024, "Lp.\tMiejsce docelowe\tKoszt");
		new lp = 1;
		new bool:shadowline;
		new slc[9];//shadowline color
		for(new b; b < sizeof(bus_stations); b++)
		{
			if(b == rangeofbus) format(strPrice, 64, ""COL_BLUE"[Tutaj jesteś]");
			else format(strPrice, 64, ""COL_GREEN"%d$", CalculatePriceBusStation(rangeofbus, b));
			slc = (shadowline) ? ("{8D8D8D}") : ("{FFFFFF}");
			format(strStationsList, 1024, "%s\n"COL_RED"%d.\t%s%s\t%s", strStationsList, lp, slc, bus_stations[b][bs_name], strPrice);
			if(shadowline) shadowline = false;
			else shadowline = true;
			lp++;
		}
		Dialog_Show(playerid, BUSSSELECT, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_BLUE"Wybierz miejsce docelowe"COL_RED" «•", strStationsList, "Wybierz", "Anuluj");
	}
	else Error(playerid, "Nie jesteś na przystanku autobusowym.");
	return 1;
}

Dialog:BUSSSELECT(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new rangeofbus = IsPlayerInRangeOfBusStation(playerid);
	if(rangeofbus == listitem) return Error(playerid, "Już jesteś w tym miejscu.");
	new price = CalculatePriceBusStation(rangeofbus, listitem);
	if(price > Money(playerid)) return Error(playerid, "Niewystarczająca ilość gotówki.");
	if(StartBusTravel(playerid, rangeofbus, listitem)) TakeMoney(playerid, price);
	return 1;
}
//********************************************************************************************************************************************************/sklep
CMD:sklep(playerid, params[])
{
	if(!IsPlayerInRangeOfShop(playerid)) return Error(playerid, "Nie jesteś w w sklepie.");
	new strShopList[3048];
	format(strShopList, 3048, "Lp.\tPrzedmiot\tKoszt");
	new list_item;
	new bool:shadowline;
	new slc[9];//shadowline color
	for(new s = 44; s < MAX_ITEMS; s++)
	{
		if(s == 45 || s == 46 || s == 80 || s == 81) continue;
		gui_cache[playerid][list_item][0] = s;
		gui_cache[playerid][list_item][1] = strlen(ItemName[s]);
		if(s == 44) gui_cache[playerid][list_item][1] += 1000;//droższy kanisterek
		else if(s == 63) gui_cache[playerid][list_item][1] += 2000;//uszczelniacz do chłodnic
		else if(s == 64) gui_cache[playerid][list_item][1] += 1500;//kolki do opon
		else if(s >= 65 && s <= 72) gui_cache[playerid][list_item][1] += 37;//droższy browar
		else if(s >= 73 && s <= 75) gui_cache[playerid][list_item][1] += 200;//droższe whisky
		else if(s >= 76 && s <= 78) gui_cache[playerid][list_item][1] += 100;//droższa wóda
		else if(s == 79) gui_cache[playerid][list_item][1] += 5000;//wędka
		else if(s == 82) gui_cache[playerid][list_item][1] += 4500;//wędka
		slc = (shadowline) ? ("{8D8D8D}") : ("{FFFFFF}");
		format(strShopList, 3048, "%s\n"COL_RED"%d.\t%s%s\t"COL_GREEN"%d$", strShopList, list_item+1, slc, ItemName[s], gui_cache[playerid][list_item][1]);
		if(shadowline) shadowline = false;
		else shadowline = true;
		list_item++;
	}
	Dialog_Show(playerid, SHOPBUY, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_BLUE"Sklep"COL_RED" «•", strShopList, "Kup", "Anuluj");
	return 1;
}

Dialog:SHOPBUY(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new price = gui_cache[playerid][listitem][1];
	if(price > Money(playerid)) return Error(playerid, "Niewystarczająca ilość gotówki.");
	new itemid = gui_cache[playerid][listitem][0];
	if(CreateItemForPlayer(playerid, itemid, 1))
	{
		new strInfo[512];
		TakeMoney(playerid, price);
		format(strInfo, 512, ""COL_WHITE"Zakupiłeś/aś: "COL_BLUE"%s"COL_WHITE" za "COL_GREEN"%d$"COL_WHITE".", ItemName[itemid], price);
		format(strInfo, 512, "%s\n"COL_WHITE"Przedmiot trafił do Twojego "COL_ORANGE"ekwipunku"COL_WHITE".", strInfo);
		format(strInfo, 512, "%s\n"COL_WHITE"Użyj komendy "COL_ORANGE"/eq"COL_WHITE" aby przeglądać swój ekwipunek.", strInfo);
		MessageGUIEx(playerid, ""COL_RED"•» "COL_GREEN"Zakupiłeś przedmiot"COL_RED" «•", strInfo);
	}
	return 1;
}
//********************************************************************************************************************************************************[VIP] /stormoff
CMD:stormoff(playerid, params[])
{
	if(!isvip(playerid)) return Error(playerid, "Dostępne tylko dla kont premium.");
	if(gracz[playerid][stormoff])
	{
		Info(playerid, ""COL_VIP" Przywrócono domyślne ustawienia pogody.");
		gracz[playerid][stormoff] = false;
	}
	else if(!gracz[playerid][stormoff])
	{
		Info(playerid, ""COL_VIP" Od teraz pogoda burzowa dla Ciebie nie istnieje :). Aby odwrócić działanie, wprowadź komendę ponownie.");
		gracz[playerid][stormoff] = true;
	}
	return 1;
}
//********************************************************************************************************************************************************[VIP] /stormoff
CMD:wykop(playerid, params[])
{
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /wykop [idgracza]");
	if(playerid == targetid) return Error(playerid, "Nie możesz użyć tej komendy na sobie.");
	if(!IsPlayerInAnyVehicle(playerid)) return Error(playerid, "Nie jesteś w pojeździe");
	if(GetPlayerVehicleSeat(playerid) != 0) return Error(playerid, "Komenda dostępna tylko dla kierowcy.");
	if(!gracz[playerid][loggedin]) return Error(playerid, "Ten gracz nie jest zalogowany.");
	if(GetPlayerVehicleID(playerid) == GetPlayerVehicleID(targetid) && GetPlayerVehicleID(targetid) != 0)
	{
		RemovePlayerFromVehicle(targetid);
		new strInfo[144];
		format(strInfo, 144, "Wyrzuciłeś gracza "COL_ORANGE"%s"COL_WHITE" z pojazdu.", nick(targetid));
		Info(playerid, strInfo);
		Info(targetid, "Zostałeś wyrzucony z pojazdu przez kierowcę.");
	}
	else Error(playerid, "Ten gracz nie znajduje się w Twoim pojeździe.");
	return 1;
}
//********************************************************************************************************************************************************/unlag
CMD:lag(playerid, params[])
{
	new strInfo[2048];
	strcat(strInfo, ""COL_WHITE"W następnym okienku zostanie Ci wyświetlona lista z mocami komputerów.");
	strcat(strInfo, "\n"COL_WHITE"Za jej pomocą określ jakiej mocy komputer posiadasz a my dostosujemy detale do Twojego komputera.");
	strcat(strInfo, "\n"COL_WHITE"Największe lagi po stronie klienta generują obiekty i tylko ten element rozgrywki będzie modyfikowany.");
	strcat(strInfo, "\n"COL_WHITE"Im słabszy sprzęt wybierzesz tym krótszy będzie dystans rysowania obiektów.");
	strcat(strInfo, "\n"COL_RED"Zmiany będą stosowane na nowo wyrenderowanych obiektach - czyli musisz się zacząć przemieszczać aby zauważyć zmiany.");
	strcat(strInfo, "\n"COL_WHITE"Mniejsza ilość widocznych obiektów odciąży Twój komputer i zwiększy liczbę klatek.");
	strcat(strInfo, "\n"COL_WHITE"Wybrana opcja jest zapisywana do konta gracza. Oznacza to, że po ponownym połączeniu zostanie ona wczytana.");
	strcat(strInfo, "\n"COL_WHITE"Ustawienia te możesz zmienic w każdej chwili za pomocą komendy /lag.");
	Dialog_Show(playerid, LAGINFO, DIALOG_STYLE_MSGBOX, ""COL_RED"•» "COL_GREEN"Informacja - LAG"COL_RED" «•", strInfo, "Lista", "Anuluj");
	return 1;
}
Dialog:LAGINFO(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new strInfo[2048];
	strcat(strInfo, "Moc komputera\tJakość");
	strcat(strInfo, "\n"COL_RED"» "COL_BLUE"Wysokiej klasy PC\t"COL_LIME"Najwyższa możliwa");
	strcat(strInfo, "\n"COL_RED"» "COL_BLUE"Średniej klasy PC\t"COL_LIME"Wysoka");
	strcat(strInfo, "\n"COL_RED"» "COL_BLUE"Nie najgorszy PC\t"COL_GREEN"Średnia");
	strcat(strInfo, "\n"COL_RED"» "COL_BLUE"Słaby PC\t"COL_GREEN"Niska");
	strcat(strInfo, "\n"COL_RED"» "COL_BLUE"Bardzo słaby PC\t"COL_RED"Bardzo niska");
	strcat(strInfo, "\n"COL_RED"» "COL_BLUE"Kalkulator\t"COL_RED"Krytyczna");
	strcat(strInfo, "\n"COL_RED"» "COL_BLUE"Toster\t"COL_RED"Dla zdesperowanych");
	Dialog_Show(playerid, LAGSET, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_GREEN"Ustawienia renderowania obiektów"COL_RED" «•", strInfo, "Wybierz", "Anuluj");
	return 1;
}

Dialog:LAGSET(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(Spam(playerid, SPAM_SETLAG, 15)) return 1;
	switch(listitem)
	{
		case 0://Wysokiej klasy PC
		{
			gracz[playerid][rpc_ObjDrawDist] = 0.0;
		}
		case 1://Średniej klasy PC
		{
			gracz[playerid][rpc_ObjDrawDist] = 400.0;
		}
		case 2://Nie najgorszy PC
		{
			gracz[playerid][rpc_ObjDrawDist] = 300.0;
		}
		case 3://Słaby PC
		{
			gracz[playerid][rpc_ObjDrawDist] = 200.0;
		}
		case 4://Bardzo słaby PC
		{
			gracz[playerid][rpc_ObjDrawDist] = 150.0;
		}
		case 5://Kalkulator
		{
			gracz[playerid][rpc_ObjDrawDist] = 100.0;
		}
		case 6://Toster
		{
			gracz[playerid][rpc_ObjDrawDist] = 50.0;
		}
	}
	mq_format("UPDATE `Konta` SET `ObjDrawDist`='%f' WHERE `id`='%d';", gracz[playerid][rpc_ObjDrawDist], gracz[playerid][UID]);
	mq_send("QUpdObjDrawDist");
	/*new Float:prPos[3];
	GetPlayerPos(playerid, prPos[0], prPos[1], prPos[2]);
	FreezeLoadObject(playerid, prPos[0], prPos[1], prPos[2]);
	Streamer_DestroyAllVisibleItems(playerid, STREAMER_TYPE_OBJECT);
	Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
	*/
	/*new BitStream:bs_resetveh = BS_New(); 
	for(new v = GetVehiclePoolSize(); v != -1; v--)
	{
		if(IsVehicleStreamedIn(v, playerid))
		{
			//GetVehiclePos(v, prPos[0], prPos[1], prPos[2]);
			prPos[0] = pojazd[v][v_idle_X];
			prPos[1] = pojazd[v][v_idle_Y];
			prPos[2] = pojazd[v][v_idle_Z];
			BS_Reset(bs_resetveh);
			BS_ResetWritePointer(bs_resetveh);
			BS_WriteValue(
			bs_resetveh,
			PR_UINT16,  v,
			PR_FLOAT, prPos[0],
			PR_FLOAT, prPos[1],
			PR_FLOAT, prPos[2]);
			BS_RPC(bs_resetveh, playerid, 159, PR_LOW_PRIORITY, PR_RELIABLE_ORDERED);//setvehiclepos
		}
	}
	BS_Delete(bs_resetveh); */
	Info(playerid, "Zmiany zapisano oraz zastosowano! Pamiętaj, że zawsze możesz zmienić swoje ustawienia.");
	return 1;
}
//********************************************************************************************************************************************************/karnet
CMD:karnet(playerid, params[])
{	
	if(IsPlayerInRangeOfPoint(playerid, 1.2, XYZ_GYMPICKUP))
	{
		new strGui[512];
		format(strGui, 512, "Produkt\tCena");
		format(strGui, 512, "%s\n"COL_RED"» "COL_GREY"Karnet 10 minut\t"COL_GREEN"1000$", strGui);
		format(strGui, 512, "%s\n"COL_RED"» "COL_GREY"Karnet 20 minut\t"COL_GREEN"5000$", strGui);
		format(strGui, 512, "%s\n"COL_RED"» "COL_GREY"Karnet 30 minut\t"COL_GREEN"9000$", strGui);
		format(strGui, 512, "%s\n"COL_RED"» "COL_BLUE"Zmiana sztuki walki\t"COL_GREY"[wyświetl opcje]", strGui);
		Dialog_Show(playerid, BUYKARNET, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_GREEN"Jaki karnet chcesz kupić?"COL_RED" «•", strGui, "Kup", "Anuluj");
	} 
	else Error(playerid, "Karnet możesz zakupić w centrum handlowym (dostaniesz sie tam autobusem).");
	return 1;
}

Dialog:BUYKARNET(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new karnet_time;
	new karnet_price;
	switch(listitem)
	{
		case 0:
		{
			karnet_time = 10;
			karnet_price = 1000;
		}
		case 1:
		{
			karnet_time = 20;
			karnet_price = 5000;
		}
		case 2:
		{
			karnet_time = 30;
			karnet_price = 9000;
		}
		case 3:
		{
			new strFightStyle[512];
			format(strFightStyle, 512, "Styl\tCzas trwania\tCena");
			format(strFightStyle, 512, "%s\n"COL_GREY"Knee Head\t"COL_BLUE"10 dni\t"COL_GREEN"50 000$", strFightStyle);
			format(strFightStyle, 512, "%s\n"COL_GREY"Kung Fu\t"COL_BLUE"10 dni\t"COL_GREEN"100 000$", strFightStyle);
			format(strFightStyle, 512, "%s\n"COL_GREY"Boxing\t"COL_BLUE"7 dni\t"COL_GREEN"300 000$", strFightStyle);
			format(strFightStyle, 512, "%s\n"COL_GREY"Grab Kick\t"COL_BLUE"7 dni\t"COL_GREEN"500 000$", strFightStyle);
			format(strFightStyle, 512, "%s\n"COL_GREY"Elbow\t"COL_BLUE"3 dni\t"COL_GREEN"1 000 000$", strFightStyle);
			Dialog_Show(playerid, SETFIGHTSTYLE, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_GREEN"Sztuki walki"COL_RED" «•", strFightStyle, "Kup","Anuluj");
			return 1;
		}
	}
	if(karnet_price > Money(playerid)) return Error(playerid, "Niewystarczająca ilość gotówki.");
	TakeMoney(playerid, karnet_price);
	new strInfo[512];
	if(gracz[playerid][karnet] == 0) format(strInfo, 512, ""COL_EASY"Zakupiłeś/aś karnet na "COL_RED"%d minut"COL_EASY" za "COL_GREEN"%d$"COL_EASY".", karnet_time, karnet_price);
	else format(strInfo, 512, "%s\n"COL_EASY"Przedłużyłeś/aś karnet o "COL_RED"%d minut"COL_EASY" za "COL_GREEN"%d$"COL_EASY".", strInfo, karnet_time, karnet_price);
	format(strInfo, 512, "%s\n"COL_EASY"Ważność swojego karnetu znajdziesz pod "COL_RED"/stats"COL_WHITE".", strInfo);
	MessageGUIEx(playerid, ""COL_RED"•» "COL_GREEN"Kupiłeś karnet"COL_RED" «•", strInfo);
	gracz[playerid][karnet] += 60*karnet_time;
	mq_format("UPDATE `Konta` SET `karnet`='%d' WHERE `id`='%d';", gracz[playerid][karnet], gracz[playerid][UID]);
	mq_send("QUpdateKarnet");
	return 1;
}

Dialog:SETFIGHTSTYLE(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new fight_price;
	new fight_time;
	new temp_fight_style;
	switch(listitem)
	{
		case 0:
		{
			fight_price = 50000;
			fight_time = 10;
			temp_fight_style = FIGHT_STYLE_KNEEHEAD;
		}
		case 1:
		{
			fight_price = 100000;
			fight_time = 10;
			temp_fight_style = FIGHT_STYLE_KUNGFU;
		}
		case 2:
		{
			fight_price = 300000;
			fight_time = 7;
			temp_fight_style = FIGHT_STYLE_BOXING;
		}
		case 3:
		{
			fight_price = 500000;
			fight_time = 7;
			temp_fight_style = FIGHT_STYLE_GRABKICK;
		}
		case 4:
		{
			if(gracz[playerid][sila] < 60.0) return Error(playerid, "Ten styl walki jest dostępny od 60.0 siły wzwyż.");
			fight_price = 1000000;
			fight_time = 3;
			temp_fight_style = FIGHT_STYLE_ELBOW;
		}
	}
	if(fight_price > Money(playerid)) return Error(playerid, "Niewystarczająca ilość gotówki.");
	TakeMoney(playerid, fight_price);
	new strInfo[512];
	if(gracz[playerid][fight_timestamp_end] == 0 || gracz[playerid][fight_style] != temp_fight_style) 
	{
		format(strInfo, 512, ""COL_EASY"Zakupiłeś/aś styl walki %s "COL_RED"na %d dni"COL_EASY" za "COL_GREEN"%d$"COL_EASY".", inputtext, fight_time, fight_price);
		gracz[playerid][fight_timestamp_end] = serwer[time_timestamp]+(60*60*24*fight_time);
	}
	else 
	{
		format(strInfo, 512, "%s\n"COL_EASY"Przedłużyłeś/aś styl walki %s "COL_RED"o %d dni"COL_EASY" za "COL_GREEN"%d$"COL_EASY".", strInfo, inputtext, fight_time, fight_price);
		gracz[playerid][fight_timestamp_end] = gracz[playerid][fight_timestamp_end]+(60*60*24*fight_time);
	}
	MessageGUIEx(playerid, ""COL_RED"•» "COL_GREEN"Zakupiono styl walki"COL_RED" «•", strInfo);
	gracz[playerid][fight_style] = temp_fight_style;
	SetPlayerFightingStyle(playerid, gracz[playerid][fight_style]);
	mq_format("UPDATE `Konta` SET `fight_timestamp_end`='%d', `fight_style`='%d' WHERE `id`='%d';", gracz[playerid][fight_timestamp_end], gracz[playerid][fight_style], gracz[playerid][UID]);
	mq_send("QUpdateFightTimestamp");
	return 1;
}

//***************************************************/aparat
CMD:aparat(playerid, params[])
{
	GivePlayerWeapon(playerid, WEAPON_CAMERA, 300);
	Info(playerid, "Dostałeś aparat :)");
	return 1;
}
//***************************************************/kluczyki
CMD:kluczyki(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);
	if(vehicleid == 0) return Error(playerid, "Nie jesteś w pojeździe.");
	if(pojazd[vehicleid][v_owner_type] != VEHICLE_PLAYER) return Error(playerid, "Tylko do pojazdu gracza można dać kluczyki.");
	if(pojazd[vehicleid][v_owner_type] == VEHICLE_PLAYER && gracz[playerid][UID] != pojazd[vehicleid][v_owner]) return Error(playerid, "Nie jesteś właścicielem tego pojazdu.");
	new targetid;
	if(sscanf(params,"d", targetid)) return SendClientMessage(playerid, -1, ""COL_GREY"UŻYJ: /kluczyki [idgracza]");
	if(targetid == playerid) return Error(playerid, "Nie możesz tej komendy użyć na sobie.");
	if(!logged(targetid)) return Error(playerid, "Gracz o takim ID nie jest połączony z serwerem.");
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, gracz[targetid][PosX], gracz[targetid][PosY], gracz[targetid][PosZ])) return Error(playerid, "Gracz jest za daleko.");
	pojazd[vehicleid][v_kluczyki_puid] = gracz[targetid][UID];
	SendClientMessageEx(playerid, 0xB91F1FFF, "Dałeś klucze dla gracza: {%06x}%s(%d){B91F1F}. "COL_BLUE"Wejdź do pojazdu jako kierowca aby je odebrać.", GetPlayerColor(playerid) >>> 8, nick(targetid), targetid);
	RemovePlayerFromVehicle(playerid);
	SendClientMessageEx(targetid, 0xB91F1FFF, "Dostałeś tymczasowo klucze do pojazdu: "COL_RED"%s(%d){B91F1F}.", GetVehicleName(pojazd[vehicleid][v_model]), pojazd[vehicleid][v_model]);
	return 1;
}
//***************************************************/urzad
new Float:office_pickups[][3] = 
{
	{1095.5629,1644.7130,1766.2410},
	{1091.5565,1644.5974,1766.2410},
	{1087.5526,1644.7375,1766.2410},
	{1083.8828,1644.7067,1766.2410},
	{1080.1469,1644.7773,1766.2410}
};

stock Init_Office()
{
	CreateActor(187, 1080.2861,1642.2584,1766.2250, 0.0); // urzadactor 1
	CreateActor(11, 1083.7491,1642.0276,1766.2250, 0.0); // urzadactor 2
	CreateActor(148, 1087.5846,1642.3287,1766.2250, 0.0); // urzadactor 3
	CreateActor(171, 1091.5187,1642.3043,1766.2250, 0.0); // urzadactor 4
	CreateActor(172, 1095.4731,1642.5446,1766.2250, 0.0); // urzadactor 5
	for(new o; o < sizeof(office_pickups); o++)
	{
		CreateDynamicPickup(1581, 1, office_pickups[o][0], office_pickups[o][1], office_pickups[o][2]);
		CreateDynamic3DTextLabel("« "COL_RED"URZĄD MIASTA LV "COL_GREEN"»\n"COL_RED"• "COL_WHITE"Wpisz "COL_GREEN"/urzad"COL_WHITE" aby otworzyc menu. "COL_RED"•", 0x009933FF, office_pickups[o][0], office_pickups[o][1], office_pickups[o][2], 6.0);
	}
	return 1;
}

CMD:urzad(playerid, params[])
{
	new bool:inrange = false;
	for(new o; o < sizeof(office_pickups); o++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 1.0, office_pickups[o][0], office_pickups[o][1], office_pickups[o][2]))
		{
			inrange = true;
			break;
		}
	}
	if(inrange == false) return Error(playerid, "Nie jesteś w urzędzie miasta.");
	new strUrzad[1024];
	format(strUrzad, 1024, "Opcja\tCena");
	format(strUrzad, 1024, "%s\n"COL_EASY"Wyrób "COL_BLUE"/dokumenty\t"COL_GREEN"100$", strUrzad);
	format(strUrzad, 1024, "%s\n"COL_EASY"Uprawnienia "COL_ORANGE"ADR\t"COL_GREEN"80 000$", strUrzad);
	format(strUrzad, 1024, "%s\n"COL_EASY"Zmień nazwę firmy\t"COL_GREEN"250 000$", strUrzad);
	Dialog_Show(playerid, URZAD, DIALOG_STYLE_TABLIST_HEADERS, ""COL_RED"•» "COL_GREEN"Urząd"COL_RED" «•", strUrzad, "Wybierz", "Anuluj");
	return 1;
}

Dialog:URZAD(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	switch(listitem)
	{
		case 0://dokumenty
		{
			if(gracz[playerid][dokumenty] == 1) return Error(playerid, "Posiadasz już /dokumenty.");
			if(Money(playerid) < 100) return Error(playerid, "Niewystarczająca ilość gotówki.");
			TakeMoney(playerid, 100);
			gracz[playerid][dokumenty] = 1;
			mq_format("UPDATE `Konta` SET `dokumenty`='%d' WHERE `id`='%d';", gracz[playerid][dokumenty], gracz[playerid][UID]);
			mq_send("QDokumenty");
			LeftNotifyShow(playerid, "Skuces!", "Wyrobiles dokumenty. Aby je ukazac uzyj komendy ~y~/dokumenty~w~. Koszt: ~g~100$~w~.", LN_GREEN, 15);
		}
		case 1://adr
		{
			if(gracz[playerid][dokumenty] == 0) return Error(playerid, "Nie posiadasz dokumentów.");
			if(gracz[playerid][upr_adr]) return Error(playerid, "Posiadasz już uprawnienia ADR.");
			if(Money(playerid) < 80000) return Error(playerid, "Niewystarczająca ilość gotówki.");
			new strADR[1024];
			format(strADR, 1024, ""COL_WHITE"Zanim uzyskasz uprawnienia na towary niebezpieczne (ADR). Musisz zapoznać");
			format(strADR, 1024, "%s\n"COL_WHITE"się z poniższymi zasadami. Przeczytaj uważnie:", strADR);
			format(strADR, 1024, "%s\n"COL_RED"1. "COL_WHITE"Koszt uprawnień ADR to: "COL_GREEN"80 000$", strADR);
			format(strADR, 1024, "%s\n"COL_RED"2. "COL_WHITE"Towary ADR należy przewozić zachowując szczególną ostrożność.", strADR);
			format(strADR, 1024, "%s\n"COL_RED"3. "COL_WHITE"Zakazuje się wjeżdżanie z towarami ADR w miejsca gdzie zagrozi to innym graczom.", strADR);
			format(strADR, 1024, "%s\n"COL_RED"4. "COL_WHITE"Pożar naczepy/pojazdu można ugasić na 2 sposoby:", strADR);
			format(strADR, 1024, "%s\n{8B8B8B}• Straż pożarna za pomocą Firetruck.", strADR);
			format(strADR, 1024, "%s\n{8B8B8B}• Rozpędzając pojazd do ponad 100 km/h.", strADR);
			format(strADR, 1024, "%s\n"COL_RED"5. "COL_WHITE"Status towaru ADR jest widoczny tylko na naczepie/pojeździe.", strADR);
			format(strADR, 1024, "%s\n"COL_RED"6. "COL_WHITE"HP pożaru sygnalizują kropki na pojeździe: ••••••••", strADR);
			format(strADR, 1024, "%s\n"COL_RED"7. "COL_WHITE"Podczas przewozu towaru ADR nie otrzymasz żadnych wskazówek co należy robić.", strADR);
			format(strADR, 1024, "%s\n\nCzy wszystko jasne? Warto zapamiętać te zasady aby bezpiecznie transportować towary ADR.", strADR);
			format(strADR, 1024, "%s\nPotwierdź, że rozumiesz, wpisują w polu poniżej "COL_BLUE"rozumiem"COL_WHITE": ", strADR);
			Dialog_Show(playerid, ADRCONFIRM, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_GREEN"Uprawnienia ADR"COL_RED" «•", strADR, "Zatwierdz", "Anuluj");
		}
		case 2://zmiana nazwy firmy
		{
			new cid = gracz[playerid][firma];
			if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
			if(gracz[playerid][firma_permlvl] != 2) return Error(playerid, "Tylko właściciel może zmienić nazwę firmy.");
			if(Money(playerid) < 250000) return Error(playerid, "Niewystarczająca ilość gotówki.");
			new strDialog[512];
			format(strDialog, 512, ""COL_RED"Wpisz poniżej nową nazwę firmy "COL_WHITE"%s (ID: %d)"COL_RED". Kosztuje to "COL_LIME"250 000$"COL_RED".", company[cid][cny_name], cid);
			format(strDialog, 512, "%s\n{8B8B8B}• Nazwa firmy od 3 do 9 znaków.", strDialog);
			Dialog_Show(playerid, SETNAMECOMPANY, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_GREEN" Zmiana nazwy firmy "COL_RED" «•", strDialog, "Zmien", "Anuluj");
		}
	}
	return 1;
}

Dialog:SETNAMECOMPANY(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new cid = gracz[playerid][firma];
	if(cid == 0) return Error(playerid, "Nie jesteś w firmie.");
	if(gracz[playerid][firma_permlvl] != 2) return Error(playerid, "Tylko właściciel może zmienić nazwę firmy.");
	if(Money(playerid) < 250000) return Error(playerid, "Niewystarczająca ilość gotówki.");
	if(strlen(inputtext) < 3) return Error(playerid, "Nazwa firmy jest za krótka.");
	if(strlen(inputtext) > 9) return Error(playerid, "Nazwa firmy jest za długa.");
	TakeMoney(playerid, 250000);
	format(company[cid][cny_name], 64, inputtext);
	CompanySaveData(cid);
	new strMsg[144];
	format(strMsg, 144, "Nowa nazwa firmy: "COL_WHITE"%s", company[cid][cny_name]);
	SendCompanyMessage(cid, strMsg);
	Info(playerid, "Nazwa firmy zmieniona!");
	return 1;
}

Dialog:ADRCONFIRM(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(compare(inputtext, "rozumiem"))
	{
		if(gracz[playerid][dokumenty] == 0) return Error(playerid, "Nie posiadasz dokumentów.");
		if(gracz[playerid][upr_adr]) return Error(playerid, "Posiadasz już uprawnienia ADR.");
		if(Money(playerid) < 80000) return Error(playerid, "Niewystarczająca ilość gotówki.");
		TakeMoney(playerid, 80000);
		LeftNotifyShow(playerid, "Sukces!", "Otrzymales uprawnienia ADR. Mozesz teraz transportować towary niebezpieczne. Aby udowodnic komus, ze posiadasz uprawnienia uzyj /dokumenty", LN_GREEN, 30);
		gracz[playerid][upr_adr] = 1;
		mq_format("UPDATE `Konta` SET `upr_adr`='%d' WHERE `id`='%d';", gracz[playerid][upr_adr], gracz[playerid][UID]);
		mq_send("QADRAdd");
	} else Error(playerid, "Szkoda, że nie zarozumiałeś.");
	return 1;
}

CMD:audycja(playerid, params[])
{
	HTTP(playerid, HTTP_GET, "sebaqq6.pl/api_radio.php", "", "RadioApiResponse");
	MessageGUIEx(playerid, "Info", "Trwa ładowanie...");
	return 1;
}

task RadioApiResponse(index, response_code, data[])
{
	if (response_code != 200) return Error(index, "Radio HL nie odpowiada (0).");

	new currentListeners, peakListeners, maxListeners, averageTime, streamInfo[512];
	if (sscanf(data, "p<|>iiiis[512]", currentListeners, peakListeners, maxListeners, averageTime, streamInfo)) {
		return Error(index, "Radio HL nie odpowiada (1).");
	}

	if (strcmp(streamInfo, "STREAM_OFFLINE", true, 14) == 0) {
		return Error(index, "Radio HL nie odpowiada (2).");
	}

	new serverGenre[51], serverUrl[51], serverTitle[51], songTitle[51], nextTitle[51], sampleRate[51], content[51];
	if (sscanf(streamInfo, "p<|>s[51]s[51]s[51]s[51]s[51]s[51]s[51]", serverGenre, serverUrl, serverTitle, songTitle, nextTitle, sampleRate, content)) {
		return Error(index, "Radio HL nie odpowiada (3).");
	}

	new strAudycja[1024];
	format(strAudycja, 1024, ""COL_RED"»»» Uruchom radio «««\t"COL_ORANGE"»» Highway Life ««");
	format(strAudycja, 1024, "%s\n"COL_RED"•» "COL_WHITE"DJ:\t"COL_LIME"%s", strAudycja, serverGenre);
	format(strAudycja, 1024, "%s\n"COL_RED"•» "COL_WHITE"Nazwa streamu:\t"COL_LIME"%s", strAudycja, serverTitle);
	format(strAudycja, 1024, "%s\n"COL_RED"•» "COL_WHITE"Słuchających:\t"COL_RED"%d"COL_WHITE"/"COL_GREEN"%d "COL_WHITE"("COL_ORANGE"rekord: %d"COL_WHITE")", strAudycja, currentListeners, maxListeners, peakListeners);
	format(strAudycja, 1024, "%s\n"COL_RED"•» "COL_WHITE"Aktualnie leci:\t"COL_BLUE"%s", strAudycja, songTitle);
	format(strAudycja, 1024, "%s\n"COL_RED"•» "COL_WHITE"Następna nuta:\t"COL_GREY"%s", strAudycja, nextTitle);
	Dialog_Show(index, DAUDYCJA, DIALOG_STYLE_TABLIST, ""COL_RED"•» "COL_GREEN"Audycja radia HL"COL_RED" «•", strAudycja, "Wybierz", "Anuluj");
	return 1;
}

Dialog:DAUDYCJA(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	if(listitem == 0) 
	{
		dialog_RADIOCAR(playerid, true, 2, "null");
	}
	return 1;
}

CMD:gps(playerid, params[])
{
	new strListGPS[2048];
	format(strListGPS, 2048, ""COL_ORANGE"=\t"COL_RED"Wyłącz marker/GPS\t"COL_ORANGE"=");
	format(strListGPS, 2048, "%s\n"COL_LIME"->\t"COL_GREY"Najbliższa stacja paliw.\t"COL_LIME"->", strListGPS);
	format(strListGPS, 2048, "%s\n"COL_LIME"->\t"COL_GREY"Najbliższy sklep.\t"COL_LIME"->", strListGPS);
	format(strListGPS, 2048, "%s\n"COL_LIME"->\t"COL_GREY"Najbliższe BINCO.\t"COL_LIME"->", strListGPS);
	format(strListGPS, 2048, "%s\n"COL_LIME"->\t"COL_GREY"Najbliższy przystanek autobusowy.\t"COL_LIME"->", strListGPS);
	format(strListGPS, 2048, "%s\n"COL_LIME"->\t"COL_GREY"[SPAWN] Hotel Highway Life.\t"COL_LIME"->", strListGPS);
	format(strListGPS, 2048, "%s\n"COL_LIME"->\t"COL_GREY"Komisariat policji.\t"COL_LIME"->", strListGPS);
	format(strListGPS, 2048, "%s\n"COL_LIME"->\t"COL_GREY"Placówka Straży Granicznej\t"COL_LIME"->", strListGPS);
	format(strListGPS, 2048, "%s\n"COL_LIME"->\t"COL_GREY"Służby Ratunkowe\t"COL_LIME"->", strListGPS);
	format(strListGPS, 2048, "%s\n"COL_LIME"->\t"COL_GREY"Pomoc Drogowa\t"COL_LIME"->", strListGPS);
	format(strListGPS, 2048, "%s\n"COL_LIME"->\t"COL_GREY"TAXI\t"COL_LIME"->", strListGPS);
	format(strListGPS, 2048, "%s\n"COL_LIME"->\t"COL_GREY"Mafia paliwowa\t"COL_LIME"->", strListGPS);
	format(strListGPS, 2048, "%s\n"COL_LIME"->\t"COL_GREY"Salon TRUCK - Truck Centre\t"COL_LIME"->", strListGPS);
	format(strListGPS, 2048, "%s\n"COL_LIME"->\t"COL_GREY"Salon samochodowy\t"COL_LIME"->", strListGPS);
	format(strListGPS, 2048, "%s\n"COL_LIME"->\t"COL_GREY"Park rozrywki\t"COL_LIME"->", strListGPS);
	Dialog_Show(playerid, GPS, DIALOG_STYLE_TABLIST, "Gdzie chcesz trafić?", strListGPS, "Wybierz", "Anuluj");
	return 1;
}

Dialog:GPS(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new Float:dist = 99999.0;
	new Float:tmpDist;
	new tempid = -1;
	/*
	for(new f; f < ???; f++)
	{
		tmpDist = GetDistanceBetweenPoints(gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], ???, ???, ???);
		if(tmpDist < dist)
		{
			dist = tmpDist;
			tempid = f;
		}
	}
	if(tempid != -1)
	{
		SetPlayerCheckpoint(playerid, ???, ???, ???, 5.0);
		if(gracz[playerid][gps_enabled] == false)  StartRouteGPS(playerid, ???, ???, ???, true);
		LeftNotifyShow(playerid, "Nawigacja", "Wytyczono trase do punktu. ~r~Czerwonym marker~w~ na minimapie.", LN_BLUE);
	}
	else Error(playerid, "Nie znaleziono miejsca.");
	*/
	switch(listitem)
	{
		case 0:
		{
			DisablePlayerCheckpoint(playerid);
			if(gracz[playerid][gps_enabled] == true)
			{
				if(gracz[playerid][gps_autooff] == true)
				{
					StopRouteGPS(playerid);
				}
			}
			Info(playerid, "Zdezaktywowano marker/GPS.");
		}
		case 1://stacja paliw
		{
			for(new f; f < MAX_FUELSTATIONS; f++)
			{
				if(fuel_stations[f][fs_id] == 0) continue;
				tmpDist = GetDistanceBetweenPoints(gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], fuel_stations[f][fs_dX], fuel_stations[f][fs_dY], fuel_stations[f][fs_dZ]);
				if(tmpDist < dist)
				{
					dist = tmpDist;
					tempid = f;
				}
			}
			if(tempid != -1)
			{
				SetPlayerCheckpoint(playerid, fuel_stations[tempid][fs_dX], fuel_stations[tempid][fs_dY], fuel_stations[tempid][fs_dZ], 5.0);
				if(gracz[playerid][gps_enabled] == false) StartRouteGPS(playerid, fuel_stations[tempid][fs_dX], fuel_stations[tempid][fs_dY], fuel_stations[tempid][fs_dZ], true);
				LeftNotifyShow(playerid, "Nawigacja", "Wytyczono trase do punktu. ~r~Czerwonym marker~w~ na minimapie.", LN_BLUE);
			}
			else Error(playerid, "Nie znaleziono miejsca.");
		}
		case 2://sklep
		{
			for(new f; f < MAX_DOORS; f++)
			{
				if(!door[f][d_status]) continue;
				if(door[f][d_intB] != 6) continue;
				tmpDist = GetDistanceBetweenPoints(gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], door[f][d_aX], door[f][d_aY], door[f][d_aZ]);
				if(tmpDist < dist)
				{
					dist = tmpDist;
					tempid = f;
				}
			}
			if(tempid != -1)
			{
				SetPlayerCheckpoint(playerid, door[tempid][d_aX], door[tempid][d_aY], door[tempid][d_aZ], 5.0);
				if(gracz[playerid][gps_enabled] == false)  StartRouteGPS(playerid, door[tempid][d_aX], door[tempid][d_aY], door[tempid][d_aZ], true);
				LeftNotifyShow(playerid, "Nawigacja", "Wytyczono trase do punktu. ~r~Czerwonym marker~w~ na minimapie.", LN_BLUE);
			}
			else Error(playerid, "Nie znaleziono miejsca.");
		}
		case 3://binco
		{
			for(new f; f < MAX_DOORS; f++)
			{
				if(!door[f][d_status]) continue;
				if(door[f][d_intB] != 15) continue;
				tmpDist = GetDistanceBetweenPoints(gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], door[f][d_aX], door[f][d_aY], door[f][d_aZ]);
				if(tmpDist < dist)
				{
					dist = tmpDist;
					tempid = f;
				}
			}
			if(tempid != -1)
			{
				SetPlayerCheckpoint(playerid, door[tempid][d_aX], door[tempid][d_aY], door[tempid][d_aZ], 5.0);
				if(gracz[playerid][gps_enabled] == false)  StartRouteGPS(playerid, door[tempid][d_aX], door[tempid][d_aY], door[tempid][d_aZ], true);
				LeftNotifyShow(playerid, "Nawigacja", "Wytyczono trase do punktu. ~r~Czerwonym marker~w~ na minimapie.", LN_BLUE);
			}
			else Error(playerid, "Nie znaleziono miejsca.");
		}
		case 4://przystanek autobusowy
		{
			for(new f; f < sizeof(bus_stations); f++)
			{
				tmpDist = GetDistanceBetweenPoints(gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], bus_stations[f][bs_X], bus_stations[f][bs_Y], bus_stations[f][bs_Z]);
				if(tmpDist < dist)
				{
					dist = tmpDist;
					tempid = f;
				}
			}
			if(tempid != -1)
			{
				SetPlayerCheckpoint(playerid, bus_stations[tempid][bs_X], bus_stations[tempid][bs_Y], bus_stations[tempid][bs_Z], 5.0);
				if(gracz[playerid][gps_enabled] == false)  StartRouteGPS(playerid, bus_stations[tempid][bs_X], bus_stations[tempid][bs_Y], bus_stations[tempid][bs_Z], true);
				LeftNotifyShow(playerid, "Nawigacja", "Wytyczono trase do punktu. ~r~Czerwonym marker~w~ na minimapie.", LN_BLUE);
			}
			else Error(playerid, "Nie znaleziono miejsca.");
		}
		case 5://spawn
		{
			SetPlayerCheckpoint(playerid, GetPVarFloat(playerid, "spawn_X"), GetPVarFloat(playerid, "spawn_Y"), GetPVarFloat(playerid, "spawn_Z"), 5.0);
			if(gracz[playerid][gps_enabled] == false)  StartRouteGPS(playerid, GetPVarFloat(playerid, "spawn_X"), GetPVarFloat(playerid, "spawn_Y"), GetPVarFloat(playerid, "spawn_Z"), true);
			LeftNotifyShow(playerid, "Nawigacja", "Wytyczono trase do punktu. ~r~Czerwonym marker~w~ na minimapie.", LN_BLUE);
		}
		case 6..11://bazy frakcji
		{
			listitem = listitem-5;
			SetPlayerCheckpoint(playerid, fractions[listitem][fr_dutyX], fractions[listitem][fr_dutyY], fractions[listitem][fr_dutyZ], 5.0);
			if(gracz[playerid][gps_enabled] == false)  StartRouteGPS(playerid, fractions[listitem][fr_dutyX], fractions[listitem][fr_dutyY], fractions[listitem][fr_dutyZ], true);
			LeftNotifyShow(playerid, "Nawigacja", "Wytyczono trase do punktu. ~r~Czerwonym marker~w~ na minimapie.", LN_BLUE);
		}
		case 12://salon truck
		{
			SetPlayerCheckpoint(playerid, XYZ_TRUCKSALON, 5.0);
			if(gracz[playerid][gps_enabled] == false)  StartRouteGPS(playerid, XYZ_TRUCKSALON, true);
			LeftNotifyShow(playerid, "Nawigacja", "Wytyczono trase do punktu. ~r~Czerwonym marker~w~ na minimapie.", LN_BLUE);
		}
		case 13://salon priv
		{
			SetPlayerCheckpoint(playerid, XYZ_SALON, 5.0);
			if(gracz[playerid][gps_enabled] == false)  StartRouteGPS(playerid, XYZ_SALON, true);
			LeftNotifyShow(playerid, "Nawigacja", "Wytyczono trase do punktu. ~r~Czerwonym marker~w~ na minimapie.", LN_BLUE);
		}
		case 14://park rozrywki
		{
			SetPlayerCheckpoint(playerid, XYZ_LUNAPARK, 5.0);
			if(gracz[playerid][gps_enabled] == false)  StartRouteGPS(playerid, XYZ_LUNAPARK, true);
			LeftNotifyShow(playerid, "Nawigacja", "Wytyczono trase do punktu. ~r~Czerwonym marker~w~ na minimapie.", LN_BLUE);
		}
	}
	return 1;
}