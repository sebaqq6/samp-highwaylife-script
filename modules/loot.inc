#define MAX_WORLD_ITEMS 2000
#define DISTANCE 4.0

enum ItemEnum
{
	bool:Drop,
	ItemID,
	Item,
	Value,
	//ObjectGameID,
	Text3D:Label,
	Float:X,
	Float:Y,
	Float:Z,
	i_vw,
	i_time_protect
};

new Przedmiot[MAX_WORLD_ITEMS][ItemEnum];

stock CreateItemForWorld(item, value, Float:itemX, Float:itemY, Float:itemZ, vw, protect_time = 10*60)
{
	if(CountItemsInWorld() >= MAX_WORLD_ITEMS-5) return 0;
	if(0 < item && item <= MAX_ITEMS - 1)
	{
		if(0 < value && value <= 999999)
		{
			for(new i = 0; i < MAX_WORLD_ITEMS; i++)
			{
				if(Przedmiot[i][Drop] == false)
				{
					new str[128];
					format(str,sizeof(str),"{8b8b8b}%s "COL_WHITE"(%d)",ItemName[item], value);
					Przedmiot[i][Drop]         = true;
					Przedmiot[i][ItemID]       = i;
					Przedmiot[i][Item]         = item;
					Przedmiot[i][Value]        = value;
					//Przedmiot[i][ObjectGameID] = CreateDynamicObject(ObjectItem[item],itemX,itemY,itemZ-ObjectItemFloat[item][0],ObjectItemFloat[item][1],ObjectItemFloat[item][2],ObjectItemFloat[item][3], vw);
					Przedmiot[i][Label]        = CreateDynamic3DTextLabel(str,-1,itemX,itemY,itemZ-ObjectItemFloat[item][0], DISTANCE, _, _, _, vw);
					Przedmiot[i][X]            = itemX;
					Przedmiot[i][Y]            = itemY;
					Przedmiot[i][Z]            = itemZ-ObjectItemFloat[item][0];
					Przedmiot[i][i_vw]  =  vw;
					Przedmiot[i][i_time_protect] = serwer[time_timestamp]+protect_time;
					break;
				}
			}
		}
	}
	return 1;
}

stock RemoveItemFromWorld(scriptItemID)
{
	if(Przedmiot[scriptItemID][Drop] == true)
	{
		//DestroyDynamicObject(Przedmiot[scriptItemID][ObjectGameID]);
		DestroyDynamic3DTextLabel(Przedmiot[scriptItemID][Label]);
		for(new ItemEnum:r; r < ItemEnum; r++)//czyszczenie zmiennych
		{
			Przedmiot[scriptItemID][r] = 0;
		}
		return 1;
	}
	return 0;
}

stock CountItemsInWorld()
{
	static wynik;
	wynik = 0;
	for(new i = 0; i < MAX_WORLD_ITEMS; i++)
	{
		if(Przedmiot[i][Drop])
		{
			wynik++;
		}
	}
	return wynik;
}

stock ClearItemsForWorld()
{
	for(new i = 0; i < MAX_WORLD_ITEMS; i++)
	{
		if(Przedmiot[i][Drop])
		{
			if(Przedmiot[i][i_time_protect] < serwer[time_timestamp])
			{
				RemoveItemFromWorld(i);
			}
		}
	}
	return 1;
}

stock PickItemForPlayer(playerid, first_time = 1)
{
	if(gracz[playerid][bw] > 0) return MessageGUI(playerid,"Informacja","Jesteś ciężko ranny - nie możesz przeglądać/używać przedmiotów.","OK","");
	if(gracz[playerid][wypadek] > 0) return MessageGUI(playerid,"Informacja","Jesteś podczas wypadku - nie możesz przeglądać/używać przedmiotów.","OK","");
	if(IsPlayerInAnyVehicle(playerid)) return MessageGUI(playerid,"Informacja","Znajdując się w pojeździe nie posiadasz możliwości podnoszenia przedmiotów!","OK","");
	new str[2000];
	new detected_items;
	format(str,sizeof(str),"UID\tNazwa\tIlość", str);
	for(new i = 0; i < MAX_WORLD_ITEMS; i++)
	{
		if(Przedmiot[i][i_vw] != GetPlayerVirtualWorld(playerid)) continue;
		if(InRange(playerid,DISTANCE,Przedmiot[i][X],Przedmiot[i][Y],Przedmiot[i][Z]))
		{
			detected_items++;
			format(str,sizeof(str),"%s\n"COL_BLACK"%d\t"COL_GREY"%s\t"COL_DBLUE"%d",str, i, ItemName[Przedmiot[i][Item]], Przedmiot[i][Value]);
		}
	}
	if(detected_items > 0)
	{
		Dialog_Show(playerid, LOOT, DIALOG_STYLE_TABLIST_HEADERS,"Lista przedmiotów znajdujących się wokół ciebie:", str,"Podnieś","Anuluj");
	}
	else if(first_time)
	{
		MessageGUI(playerid,"Informacja","Wokół Ciebie nie znajduje się żaden przedmiot.","OK","");
	}
	return 1;
}

Dialog:LOOT(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;
	new w_uid = strval(inputtext);
	if(!Przedmiot[w_uid][Drop]) return MessageGUI(playerid,"Informacja","Ktoś inny podniósł ten przedmiot.","OK","");
	if(CreateItemForPlayer(playerid,Przedmiot[w_uid][Item],Przedmiot[w_uid][Value]))
	{
		RemoveItemFromWorld(w_uid);
		ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);
		PickItemForPlayer(playerid, 0);
	}
	return 1 ;
}