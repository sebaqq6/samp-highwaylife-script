stock ListItems(playerid)
{
	for(new eq_select_info:r; r < eq_select_info; r++)
	{
		eq_select[playerid][r] = 0;
	}
	if(gracz[playerid][bw] > 0) return MessageGUI(playerid,"Informacja","Jesteś ciężko ranny - nie możesz przeglądać/używać przedmiotów.","OK","");
	if(gracz[playerid][wypadek] > 0) return MessageGUI(playerid,"Informacja","Jesteś podczas wypadku - nie możesz przeglądać/używać przedmiotów.","OK","");
	//mq_format("SELECT * FROM `przedmioty` WHERE `userid`='%d' ORDER BY `used` DESC, `id` ASC;", gracz[playerid][UID]);
	mq_format("SELECT * FROM `przedmioty` WHERE `userid`='%d';", gracz[playerid][UID]);
	mq_send("ShowItemsDB", "d", playerid);
	return 1;
}

new list_items[4000];
forward ShowItemsDB(playerid);
public ShowItemsDB(playerid)
{
	new t_id, t_itemid, t_count, t_used;
	mq_getdata();
	if(rekordy)
	{
		new i;
		format(list_items, 4000, "UID\tNazwa przedmiotu\tIlość");
		while(i < rekordy)
		{
			cache_get_value_name_int(i, "id", 			t_id);
			cache_get_value_name_int(i, "itemid", 			t_itemid);
			cache_get_value_name_int(i, "count", 			t_count);
			cache_get_value_name_int(i, "used", 			t_used);
			if(t_count > 0) 
			{
				if(t_used)
				{
					format(list_items, 4000, "%s\n"COL_BLACK"%d\t"COL_GREEN"[%s]\t"COL_DBLUE"%d", list_items, t_id, ItemName[t_itemid], t_count);
				}
				else
				{
					format(list_items, 4000, "%s\n"COL_BLACK"%d\t"COL_EASY"%s\t"COL_DBLUE"%d", list_items, t_id, ItemName[t_itemid], t_count);
				}
			}
			i++;
		}
		new titlestr[110];
		format(titlestr, 110, ""COL_WHITE"Ekwipunek - ["COL_BLUE"Zużyte sloty: "COL_RED"%d"COL_WHITE"/"COL_GREEN"%d"COL_WHITE"]", rekordy, GetPlayerEQSize(playerid));
		Dialog_Show(playerid, EKWIPUNEK, DIALOG_STYLE_TABLIST_HEADERS, titlestr, list_items, "Wybierz", "Anuluj");
	}
	else
	{
		MessageGUI(playerid,"Informacja","Twój ekwipunek jest pusty!","OK","");
	}
	return 1;
}


Dialog:EKWIPUNEK(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		return 1;
	}
	mq_format("SELECT * FROM `przedmioty` WHERE `id`='%d' LIMIT 0,1;", strval(inputtext));
	new Cache:itemquery = mysql_query(g_SQL, mQuery);
	cache_get_value_name_int(0, "id", 	eq_select[playerid][s_id]);
	cache_get_value_name_int(0, "itemid", 	eq_select[playerid][s_itemid]);
	cache_get_value_name_int(0, "count", 	eq_select[playerid][s_count]);
	cache_get_value_name_int(0, "used", 	eq_select[playerid][s_used]);
	cache_delete(itemquery);
	if(eq_select[playerid][s_used])
	{
		if(ItemCanConfig(eq_select[playerid][s_itemid])) Dialog_Show(playerid, EQAKCJA, DIALOG_STYLE_LIST, Title_SelectItem(playerid), ""COL_WHITE"1. "COL_ORANGE"Konfiguruj", "Wybierz", "Wróć");
		else Dialog_Show(playerid, EQAKCJA, DIALOG_STYLE_LIST, Title_SelectItem(playerid), ""COL_WHITE"1. "COL_RED"Przestań używać", "Wybierz", "Wróć");
	}
	else
	{
		Dialog_Show(playerid, EQAKCJA, DIALOG_STYLE_LIST, Title_SelectItem(playerid), "1. "COL_GREEN"Użyj\n"COL_WHITE"2. "COL_RED"Wyrzuć\n"COL_WHITE"3. "COL_RED"Zniszcz", "Wybierz", "Wróć");
	}
	return 1;
}

Dialog:EQAKCJA(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItems(playerid);
	switch(listitem)
	{
		case 0:
		{
			if(BattleBlockEx(playerid, 250.0)) return Error(playerid, "Uczestniczysz w napadzie.");
			else UseItem(playerid, eq_select[playerid][s_itemid]);
		}
		case 1:
		{
			if(eq_select[playerid][s_count] == 1)
			{
				dialog_EQDROP(playerid, 1, 0, "1");
			}
			else
			{
				Dialog_Show(playerid, EQDROP, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz wyrzucić na ziemię?", "Wyrzuć", "Wróć");
			}
		}
		case 2:
		{
			Dialog_Show(playerid, EQDESTROY, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz zniszczyć?", "Zniszcz!", "Wróć");
		}
	}
	return 1;
}

Dialog:EQDROP(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItems(playerid);
	new ilosc = strval(inputtext);
	if(ilosc < 1 || ilosc > 5000)
	{
		Dialog_Show(playerid, EQDROP, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz wyrzucić na ziemię?\n"COL_RED"Błąd! Niepoprawna ilość towaru(min: 1 | max: 5000).", "Wyrzuć", "Wróć");
	}
	else if(eq_select[playerid][s_count] >= ilosc)
	{
		if(CreateItemForWorld(eq_select[playerid][s_itemid], ilosc, gracz[playerid][PosX], gracz[playerid][PosY], gracz[playerid][PosZ], GetPlayerVirtualWorld(playerid)))
		{
			RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], ilosc);
			ListItems(playerid);
		}
		else
		{
			MessageGUI(playerid,"Informacja","W chwili obecnej nie da sie wyrzucić przedmiotu na ziemię. Powód: zbyt dużo przedmiotów na mapie.","OK","");
		}
	}
	else
	{
		Dialog_Show(playerid, EQDROP, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz wyrzucić na ziemię?\n"COL_RED"Błąd! Brak takiej ilości towaru.", "Wyrzuć", "Wróć");
	}
	return 1;
}

Dialog:EQDESTROY(playerid, response, listitem, inputtext[])
{
	if(!response) return ListItems(playerid);
	new ilosc = strval(inputtext);
	if(ilosc < 1)
	{
		Dialog_Show(playerid, EQDESTROY, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz zniszczyć?\n"COL_RED"Błąd! Nie wykryto wprowadzonej ilości.", "Zniszcz!", "Wróć");
	}
	else if(eq_select[playerid][s_count] >= ilosc)
	{
		RemoveItemFromPlayerEx(playerid, eq_select[playerid][s_id], ilosc);
		ListItems(playerid);
	}
	else
	{
		Dialog_Show(playerid, EQDESTROY, DIALOG_STYLE_INPUT, Title_SelectItem(playerid), "\t\t\t\t\t\t\t\t\t\t\t\t\t\t"COL_BLACK".\n"COL_WHITE"Ile sztuk przedmiotu chcesz zniszczyć?\n"COL_RED"Błąd! Brak takiej ilości towaru.", "Zniszcz!", "Wróć");
	}
	return 1;
}



stock CreateItemForPlayer(playerid, item_id, item_count)
{
	mq_format("SELECT * FROM `przedmioty` WHERE `userid`='%d' AND `itemid`='%d' LIMIT 0,1;", gracz[playerid][UID], item_id);
	new Cache:itemquery = mysql_query(g_SQL, mQuery);
	if(cache_get_row_count_ex() && StackedItem(item_id))
	{
		new t_id;
		cache_get_value_name_int(0, "id",   t_id);
		cache_delete(itemquery);
		mq_format("UPDATE `przedmioty` SET `count`=`count`+'%d' WHERE `id`='%d';", item_count, t_id);
		mysql_query(g_SQL, mQuery, false);
	}
	else
	{			
		cache_delete(itemquery);
		mq_format("SELECT * FROM `przedmioty` WHERE `userid`='%d';", gracz[playerid][UID]);
		itemquery = mysql_query(g_SQL, mQuery);
		if(cache_get_row_count_ex() >= GetPlayerEQSize(playerid))
		{
			cache_delete(itemquery);
			MessageGUI(playerid,"Informacja","Brak miejsca w ekwipunku!","OK","");
			return 0;
		}
		cache_delete(itemquery);
		mq_format("INSERT INTO `przedmioty` VALUES (NULL, '%d', '%d', '%d', '0');", gracz[playerid][UID], item_id, item_count);
		mysql_query(g_SQL, mQuery, false);
	}
	return 1;
}


stock RemoveItemFromPlayer(playerid, item_id, item_count)//według ITEMID
{
	if(item_count < 1) return 0;
	mq_format("SELECT `id`,`count` FROM `przedmioty` WHERE `userid`='%d' AND `itemid`='%d' LIMIT 0,1;", gracz[playerid][UID], item_id);
	new Cache:itemquery = mysql_query(g_SQL, mQuery);
	if(cache_get_row_count_ex())
	{
		new t_id, t_count;
		cache_get_value_name_int(0, "id",   t_id);
		cache_get_value_name_int(0, "count",   t_count);
		if(item_count > t_count)
		{
			if(item_id == 100) MessageGUI(playerid,"Informacja",""COL_GREY"Nie posiadasz takiej ilości "COL_CYAN"żetonów"COL_GREY".","OK","");
			else MessageGUI(playerid,"Informacja","Nie posiadasz tyle ilości towaru!","OK","");
			cache_delete(itemquery);
			return 0;
		} 
		else if(item_count == t_count)
		{
			mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
			mysql_query(g_SQL, mQuery, false);
			cache_delete(itemquery);
			return 1;
		}
		else
		{
			mq_format("UPDATE `przedmioty` SET `count`=`count`-'%d' WHERE `id`='%d';", item_count, t_id);
			mysql_query(g_SQL, mQuery, false);
			cache_delete(itemquery);
			return 1;
		}
	}
	MessageGUI(playerid,"Informacja","Nie posiadasz tyle ilości towaru!","OK","");
	cache_delete(itemquery);
	return 0;
}


stock RemoveItemFromPlayerEx(playerid, t_id, item_count)//według ID
{
	if(item_count < 1) return 0;
	mq_format("SELECT `count` FROM `przedmioty` WHERE `id`='%d' LIMIT 0,1;", t_id);
	new Cache:itemquery = mysql_query(g_SQL, mQuery);
	if(cache_get_row_count_ex())
	{
		new t_count;
		cache_get_value_name_int(0, "count",   t_count);
		if(item_count > t_count)
		{
			MessageGUI(playerid,"Informacja","Nie posiadasz tyle ilości towaru!","OK","");
			cache_delete(itemquery);
			return 0;
		} 
		else if(item_count == t_count)
		{
			mq_format("DELETE FROM `przedmioty` WHERE `id`='%d';", t_id);
			mysql_query(g_SQL, mQuery, false);
			cache_delete(itemquery);
			return 1;
		}
		else
		{
			mq_format("UPDATE `przedmioty` SET `count`=`count`-'%d' WHERE `id`='%d';", item_count, t_id);
			mysql_query(g_SQL, mQuery, false);
			cache_delete(itemquery);
			return 1;
		}
	}
	MessageGUI(playerid,"Informacja","Nie posiadasz tyle ilości towaru!","OK","");
	cache_delete(itemquery);
	return 0;
}

stock Title_SelectItem(playerid)
{
	new titlestr[200];
	format(titlestr, 200, ""COL_WHITE"Ekwipunek - ["COL_RED"%s"COL_WHITE"]["COL_GREEN"Ilość: "COL_RED"%d"COL_WHITE"]", ItemName[eq_select[playerid][s_itemid]], eq_select[playerid][s_count]);
	return titlestr;
}

stock GetItemValueForPlayer(playerid, item_id)//wedługi itemid
{
	mq_format("SELECT `count` FROM `przedmioty` WHERE `userid`='%d' AND `itemid`='%d' LIMIT 0,1;", gracz[playerid][UID], item_id);
	new Cache:itemquery = mysql_query(g_SQL, mQuery);
	new ilosc;
	if(cache_get_row_count_ex())
	{
		cache_get_value_name_int(0, "count", 		ilosc);
	}
	cache_delete(itemquery);
	return ilosc;
}


stock GetPlayerEQSize(playerid)
{
	if(isvip(playerid)) return 20;
	return 10;
}