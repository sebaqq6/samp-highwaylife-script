//zł, numer, żetony
new Float:sms_cennik[][3] =
{
	{0.62, 70068.0, 25.0},
	{1.23, 71068.0, 50.0},
	{2.46, 72068.0, 100.0},
	{4.92, 74068.0, 200.0},
	{7.38, 76068.0, 300.0},
	{12.30, 91058.0, 500.0},
	{20.91, 91758.0, 850.0},
	{24.60, 92058.0, 1000.0},
	{30.75, 92578.0, 1250.0}
};
//cennik usług w żetonach premium:
#define CENA_VIP 500

stock ShowPremiumMenu(playerid)
{
	new str_menu[1024];
	strcat(str_menu, ""COL_WHITE"("COL_CYAN"SMS"COL_WHITE")\t"COL_GREY"Kup "COL_ORANGE"ż"COL_GREY"etony "COL_ORANGE"p"COL_GREY"remium"COL_WHITE"\t("COL_CYAN"SMS"COL_WHITE")\n");
	strcat(str_menu, ""COL_WHITE"("COL_GREEN"$$$"COL_WHITE")\t"COL_GREY"Wymień "COL_GREEN"$$$"COL_GREY" na "COL_ORANGE"ż"COL_GREY"etony "COL_ORANGE"p"COL_GREY"remium"COL_WHITE"\t("COL_GREEN"$$$"COL_WHITE")\n");
	strcat(str_menu, ""COL_WHITE"("COL_RED"500 "COL_ORANGE"żp"COL_WHITE")\t"COL_GREY"Konto premium"COL_WHITE"\t("COL_RED"30 dni"COL_WHITE")\n");
	new str_header[100];
	format(str_header, 100, ""COL_YELLOW"»"COL_WHITE" Posiadasz "COL_RED"%d "COL_ORANGE"żetonów premium", gracz[playerid][gold]);
	Dialog_Show(playerid, PREMIUM, DIALOG_STYLE_TABLIST, str_header, str_menu, "Wybierz", "Wróć");
	return 1;
}
//Doładowanie
Dialog:PREMIUM(playerid, response, listitem, inputtext[])
{
	if(!response) return PC_EmulateCommand(playerid, "/pomoc");
	switch(listitem)
	{
		case 0:
		{
			//if(listitem == 0) return Error(playerid, "W tym momencie ta opcja jest niedostępna.");//
			new str_sms[2048];
			new str_header[100];
			format(str_header, 100, ""COL_YELLOW"»"COL_WHITE" Posiadasz "COL_RED"%d "COL_ORANGE"żetonów premium", gracz[playerid][gold]);
			format(str_sms, 2048, "Cena\tIlość");
			for(new s; s < sizeof(sms_cennik); s++)
			{
				format(str_sms, 2048, "%s\n"COL_GREY"» "COL_WHITE"%.02f "COL_GREY"zł\t"COL_GREEN"+"COL_GREY"%d "COL_ORANGE"żp", str_sms, sms_cennik[s][0], floatround(sms_cennik[s][2]));
			}
			Dialog_Show(playerid, BUYSMS, DIALOG_STYLE_TABLIST_HEADERS, str_header, str_sms, "Wybierz", "Wróć");
		}
		case 1:
		{
			Error(playerid, "Opcja tymczasowo wyłączona. Wspomóż projekt finansowo (SMS)!");
			/*if(gracz[playerid][PGodz] < 5) return Error(playerid, "Musisz mieć minimum 5 godzin całkowitego czasu ONLINE.");
			new strExchange[1024];
			format(strExchange, 1024, ""COL_WHITE"W tym miejcu możesz wymienić swoje "COL_GREEN"pieniądze zarobione w grze"COL_WHITE" na walute premium, czyli "COL_ORANGE"żetony premium"COL_WHITE".");
			format(strExchange, 1024, "%s\n\n{a90000}» "COL_GREY"Koszt żetonu premium: "COL_GREEN"%d$", strExchange, PRICE_GOLDDOLAR);
			format(strExchange, 1024, "%s\n{a90000}» "COL_GREY"Posiadane żetony premium: "COL_ORANGE"%d sztuk", strExchange, gracz[playerid][gold]);
			format(strExchange, 1024, "%s\n{a90000}» "COL_GREY"Koszt VIP'a przeliczony na $: "COL_GREEN"%d$", strExchange, PRICE_GOLDDOLAR*CENA_VIP);
			format(strExchange, 1024, "%s\n{a90000}» "COL_GREY"Ile możesz kupić żetonów za posiadaną gotówkę: "COL_ORANGE"%d sztuk", strExchange, Money(playerid)/PRICE_GOLDDOLAR);
			format(strExchange, 1024, "%s\n\n"COL_RED" Ile potrzebujesz żetonów premium?", strExchange);
			Dialog_Show(playerid, ZETONYDOLAR, DIALOG_STYLE_INPUT, ""COL_RED"•» "COL_GREEN"Wymiana $ na żetony premium"COL_RED" «•", strExchange, "Wymień", "Wróć");*/
		}
		case 2://vip
		{
			new str_vip[2048];
			new str_header[100];
			format(str_header, 100, ""COL_YELLOW"»"COL_WHITE" Posiadasz "COL_RED"%d "COL_ORANGE"żetonów premium", gracz[playerid][gold]);
			format(str_vip, 2048, "%s\n"COL_GREY"Cechy konta premium:", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Tag "COL_VIP"[VIP]"COL_GREY" nad głową postaci.", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Tag "COL_VIP"[VIP]"COL_GREY" na czacie.", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Premia za wykonane "COL_WHITE"/zlecenie"COL_GREY".", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Premia do wypłaty, jeśli pracujesz we frakcji ", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Premia do siły na siłowni.", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Skrócony czas wypadków.", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Skrócony czas BW.", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Możliwość wyłączenia burzy: "COL_VIP"/stormoff"COL_GREY".", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Zwiększona ilość slotów EQ.", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Można bardziej przeładować pojazd firmowy.", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Możliwość posiadania więcej prywatnych pojazdów.", str_vip);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Koszt: "COL_RED"%d "COL_ORANGE"żetonów premium"COL_GREY".", str_vip, CENA_VIP);
			format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"Konto premium jest ważne przez "COL_RED"30 dni"COL_GREY".", str_vip);
			//format(str_vip, 2048, "%s\n{a90000}» "COL_GREY"x", str_vip);
			format(str_vip, 2048, "%s\n", str_vip);
			format(str_vip, 2048, "%s\n"COL_GREY"Czy chcesz wymienić żetony na konto premium?", str_vip);
			Dialog_Show(playerid, BUYVIP, DIALOG_STYLE_MSGBOX, str_header, str_vip, "Tak!", "Wróć");
		}
	}
	return 1;
}

Dialog:BUYSMS(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowPremiumMenu(playerid);
	new str_smsbuy[2048];
	new str_header[100];
	format(str_header, 100, ""COL_YELLOW"»"COL_WHITE"Posiadasz "COL_RED"%d "COL_ORANGE"żetonów premium", gracz[playerid][gold]);
	format(str_smsbuy, 2048, ""COL_GREY"Zakup "COL_RED"%d"COL_GREY" sztuk "COL_ORANGE"żetonów premium"COL_GREY":", floatround(sms_cennik[listitem][2]));
	format(str_smsbuy, 2048, "%s\n{a90000}» "COL_GREY"Wyślij SMS o treści "COL_BLUE"AP.HOSTMC"COL_GREY" na numer "COL_GREEN"%d"COL_GREY".", str_smsbuy, floatround(sms_cennik[listitem][1]));
	format(str_smsbuy, 2048, "%s\n{a90000}» "COL_CYAN"Kod zwrotny wprowadź w polu poniżej.", str_smsbuy);
	format(str_smsbuy, 2048, "%s\n{a90000}» "COL_RED"Przepisuj kod bardzo uważnie i upewnij się, że kod jest zakupiony pod wybraną wartość żetonów!", str_smsbuy);
	format(str_smsbuy, 2048, "%s\n"COL_GREY"Koszt SMS: "COL_RED"%.02f "COL_GREY"zł (brutto)", str_smsbuy, sms_cennik[listitem][0]);
	format(str_smsbuy, 2048, "%s\n", str_smsbuy);
	format(str_smsbuy, 2048, "%s\nAdministracja {a90000}Highway Life"COL_GREY" nie czerpie korzyści majątkowych ze sprzedaży żetonów premium na serwerze oraz w panelu gracza {a90000}Highway Life"COL_GREY".", str_smsbuy);
	format(str_smsbuy, 2048, "%s\nWszystkie środki są przekazywane na utrzymanie forum, serwera TS3, serwera SA:MP oraz opłacenie zakładki HOSTED.", str_smsbuy);
	format(str_smsbuy, 2048, "%s\n"COL_GREY"Płatności obsługuje: {49cc8d}dotpay.pl "COL_GREY"\t\tReklamacje: {49cc8d}https://www.dotpay.pl/kontakt/uslugi-sms-premium/", str_smsbuy);
	format(str_smsbuy, 2048, "%s\n{49cc8d}Dotpay"COL_GREY" obsługuje wszystkie sieci, w tym: {f200e8}T-MOBILE"COL_GREY", {ff6700}ORANGE"COL_GREY", {297a00}PLUS"COL_GREY", {9f00c9}PLAY"COL_GREY", {ec0018}HEYAH"COL_GREY", {f9be02}CYFROWY POLSAT", str_smsbuy);
	format(str_smsbuy, 2048, "%s\n"COL_GREY"Więcej informacji oraz {59e700}inne rodzaje płatności"COL_GREY" znajdziesz w panelu gracza {a90000}Highway Life"COL_GREY".", str_smsbuy);
	Dialog_Show(playerid, BUYSMS2, DIALOG_STYLE_INPUT, str_header, str_smsbuy, "Zatwierdź", "Anuluj");
	SetPVarInt(playerid, "BuySms_Selected", listitem);
	return 1;
}

Dialog:BUYSMS2(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	format(inputtext, 10, inputtext);
	mysql_escape_string(inputtext, inputtext, 256, g_SQL);
	new selected = GetPVarInt(playerid, "BuySms_Selected");
	new request[512];
	format(request, 512, "sebaqq6.pl/api_sms.php?number=%d&code=%s&uid=%d", floatround(sms_cennik[selected][1]), inputtext, gracz[playerid][UID]);
	SetPVarString(playerid, "Sms_Code", inputtext);
	HTTP(playerid, HTTP_GET, request, "", "ValidSMSCode");
	ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, "{f0da00}Sprawdzanie...", "Trwa sprawdzanie... Proszę czekać...", "OK","");
	return 1;
}

forward ValidSMSCode(index, response_code, data[]);
public ValidSMSCode(index, response_code, data[])
{
	new buffer[128];
	
	#if defined DEBUGHL
	format(buffer, 128, "[DEBUGHL] ValidSMSCode -  response: %d data: %s", response_code, data);
	print(buffer);
	#endif
	if(response_code == 200)//success connect api
	{
		new code_data = strval(data);
		switch(code_data)
		{
			case 0:
			{
				format(buffer, sizeof(buffer), "Błędny kod.");
				Error(index, buffer);
				Dialog_Close(index);
			}
			case 1:
			{
				new str_successbuy[512];
				new selected = GetPVarInt(index, "BuySms_Selected");
				new add_zetony = floatround(sms_cennik[selected][2]);
				format(str_successbuy, 512, "{00b415}Sukces!");
				format(str_successbuy, 512, "%s\n"COL_GREY"Dziękujemy za dofinansowanie projektu {a90000}Highway Life"COL_GREY"!", str_successbuy);
				format(str_successbuy, 512, "%s\n"COL_GREY"W zamian otrzymujesz "COL_GREEN"+"COL_RED"%d"COL_GREY" sztuk "COL_ORANGE"żetonów premium"COL_GREY" :)", str_successbuy, add_zetony);
				format(str_successbuy, 512, "%s\n"COL_GREY"Pozdrawiamy, ekipa {a90000}Highway Life"COL_GREY".", str_successbuy);
				gracz[index][gold] += add_zetony;
				mq_format("UPDATE `Konta` SET `gold`=`gold`+'%d' WHERE `id`='%d';", add_zetony, gracz[index][UID]);
				mq_send("QAddGold");
				ShowPlayerDialog(index, INFO_DIALOG, DIALOG_STYLE_MSGBOX, "{00b415}SUKCES!!!", str_successbuy, "ZAMKNIJ","");
				printf("[ZETONY]Gracz UID: %d[%s] doladowal %d zetonow. Aktualny jego stan: %d", gracz[index][UID], nick(index), add_zetony, gracz[index][gold]);
				new sms_code[32];
				GetPVarString(index, "Sms_Code", sms_code, 32);
				mq_format("INSERT INTO `WebPremiumLog` (`web`, `type`, `uid`, `nr`, `code`, `price`) VALUES ('0', '1', '%d', '%d', '%s', '%f');", gracz[index][UID], floatround(sms_cennik[selected][1]), sms_code, sms_cennik[selected][0]);
				mq_send("QSMSLog");
			}
			case 4:
			{
				format(buffer, sizeof(buffer), "Podany kod ma nieprawidłową długość (prawidłowa: 8 znaków).");
				Error(index, buffer);
				Dialog_Close(index);
			}
			default:
			{
				format(buffer, sizeof(buffer), "Błąd API: %d.", code_data);
				Error(index, buffer);
				Dialog_Close(index);
			}
		}
	}
	else
	{
		format(buffer, sizeof(buffer), "Błąd połączenia API, kod błędu: %d", response_code);
		Error(index, buffer);
		Dialog_Close(index);
		format(buffer, 100, "[HTTP_DATA]: PUID: %d | %s", gracz[index][UID], data);
		print(buffer);
	}
	return 1;
}

//kupno vipa
Dialog:BUYVIP(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowPremiumMenu(playerid);
	if(gracz[playerid][gold] < CENA_VIP) return Error(playerid, "Za mało żetonów premium.");
	gracz[playerid][gold] -= CENA_VIP;
	if(isvip(playerid))
	{
		gracz[playerid][vip] = gracz[playerid][vip]+((60*60)*24)*30;
	}
	else
	{
		gracz[playerid][vip] = serwer[time_timestamp]+((60*60)*24)*30;
	}
	mq_format("UPDATE `Konta` SET `gold`=`gold`-'%d', `vip`='%d' WHERE `id`='%d';", CENA_VIP, gracz[playerid][vip], gracz[playerid][UID]);
	mq_send("QBuyVIP");
	mq_format("INSERT INTO `LogiZetonowPremium` (`uid`, `price`, `property`) VALUES ('%d', '%d', '1');", gracz[playerid][UID], CENA_VIP);
	mq_send("QZetonLog");
	new str_successbuy[512];
	format(str_successbuy, 512, "{00b415}Sukces!");
	format(str_successbuy, 512, "%s\n"COL_GREY"Dziękujemy za zakup konta premium na projekcie {a90000}Highway Life"COL_GREY"!", str_successbuy);
	format(str_successbuy, 512, "%s\n"COL_GREY"Twoje konto premium na tej postaci jest ważne przez "COL_RED"%d dni"COL_GREY" ("COL_LIME"czas wygaśnięcia jest pod "COL_GREEN"/stats"COL_GREY").", str_successbuy, (gracz[playerid][vip]-serwer[time_timestamp])/60/60/24);
	format(str_successbuy, 512, "%s\n"COL_GREY"Możesz w każdej chwili przedłużyć ważność konta premium używając tej samej opcji co do kupna.", str_successbuy);
	ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, ""COL_YELLOW"» {00b415} Przyznano konto premium!", str_successbuy, "ZAMKNIJ","");
	return 1;
}
//wymiana żetonów
Dialog:ZETONYDOLAR(playerid, response, listitem, inputtext[])
{
	if(!response) return ShowPremiumMenu(playerid);
	new gold_value = strval(inputtext);
	if(gold_value < 1) return Error(playerid, "Wartość musi być większa niż 0.");
	if(gold_value > 1000) return Error(playerid, "Jednorazowa wymiana nie może być większa niż 1000 żetonów.");
	new gold_price = gold_value*PRICE_GOLDDOLAR;

	if(Money(playerid) < gold_price) return Error(playerid, "Niewystarczająca ilość gotówki.");
	TakeMoney(playerid, gold_price);

	gracz[playerid][gold] += gold_value;
	mq_format("UPDATE `Konta` SET `gold`=`gold`+'%d' WHERE `id`='%d';", gold_value, gracz[playerid][UID]);
	mq_send("QAddGold");

	mq_format("INSERT INTO `WebPremiumLog` (`web`, `type`, `uid`, `nr`, `code`, `price`) VALUES ('0', '1', '%d', '%d', 'srvmoney', '%d');", gracz[playerid][UID], gold_value, gold_price);
	mq_send("QSMSLog");

	new str_successbuy[512];
	format(str_successbuy, 512, "{00b415}Sukces!");
	format(str_successbuy, 512, "%s\n"COL_GREY"W zamian za "COL_GREEN"%d$"COL_GREY" otrzymujesz "COL_GREEN"+"COL_RED"%d"COL_GREY" sztuk "COL_ORANGE"żetonów premium"COL_GREY" :)", str_successbuy, gold_price, gold_value);
	format(str_successbuy, 512, "%s\n"COL_GREY"Pozdrawiamy, ekipa {a90000}Highway Life"COL_GREY".", str_successbuy);
	ShowPlayerDialog(playerid, INFO_DIALOG, DIALOG_STYLE_MSGBOX, "{00b415}SUKCES!!!", str_successbuy, "ZAMKNIJ","");
	return 1;
}