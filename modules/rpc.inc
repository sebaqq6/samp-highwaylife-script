new bool:rpc_gz_show[MAX_PLAYERS][MAX_GANG_ZONES];
new Float:rpc_gz_pos[MAX_PLAYERS][MAX_GANG_ZONES][4];
/*
In the example above, we modify the player's current weapon in the packet, thus making everyone see them holding a minigun (38).

BS_IgnoreBits(bs, 8); - Before reading the packet data, we ignore the first 8 bits (1 byte) because they contain the packet identifier.

BS_ReadOnFootSync(bs, onFootData); - After ignoring the first 8 bits, we can read the packet, which will have its data passed to onFootData (referencing the enumerator PR_OnFootSync).

onFootData[PR_weaponId] = 38; - We change the weapon id in the packet to anything we want. The id we set will be the one sent in the packet, and it will be the weapon other players will see.

BS_SetWriteOffset(bs, 8); - We set the write offset after the 8 bits, because we don't want to write over the packet identifier.

BS_WriteOnFootSync(bs, onFootData); - Then, we write the new on foot synchronization data in the BitStream.

return 1; - We return 1, allowing the packet to be sent with the new data we wrote in the BitStream.


#define ID_BULLET_SYNC  206

SendBullet(from, to, data[PR_BulletSync])
{
    new BitStream:bs = BS_New();

    BS_WriteValue(
        bs,
        PR_UINT8, ID_BULLET_SYNC,
        PR_UINT16, from
    );

    BS_WriteBulletSync(bs, data);

    BS_Send(bs, to, PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED);

    BS_Delete(bs);
}

//Somewhere in your code
new bulletData[PR_BulletSync];

bulletData[PR_hitType] = //Your hit type;
bulletData[PR_hitId] = //hit id

bulletData[PR_origin][0] = //origin X
bulletData[PR_origin][1] = //origin Y
bulletData[PR_origin][2] = //origin Z
    
bulletData[PR_hitPos][0] = //hit position X/
bulletData[PR_hitPos][1] = //hit position Y/
bulletData[PR_hitPos][2] = //hit position Z/
    
bulletData[PR_offsets][0] = //offset X/
bulletData[PR_offsets][1] = //offset Y/
bulletData[PR_offsets][2] = //offset Z/
    
bulletData[PR_weaponId] = //weapon id
    
SendBulletData(0, 1, bulletData); 
In the example above, the function sends a packet with bullet data to a specific player.

new BitStream:bs = BS_New(); - We create a new BitStream, where we are going to write our packet data.

PR_UINT8, ID_BULLET_SYNC, - First parameter of the BitStream. That is the packet identifier.

PR_UINT16, from - Second parameter of the BitStream. This is the responsible player, from whom the bullet data will originate.

BS_WriteBulletSync(bs, data); - "data" references the enumerator PR_BulletSync and contains the bullet data we send in the function's 3rd parameter, it's data will be written in the BitStream.

BS_Send(bs, to, PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED); - "to" is the player about to receive the packet. If "to" is -1, all players will receive the packet. PR_HIGH_PRIORITY is the packet's priority, and PR_RELIABLE_ORDERED is it's reliability.

BS_Delete(bs); - After we are done, we remove the BitStream.

*/

stock Init_RPC()
{
	//gangzone rpc init
	for(new g; g < MAX_GANG_ZONES; g++)
	{
		GangZoneCreate(1248.011, 2072.804, 1439.348, 2204.319);
	}
	//gz rpc init end
	return 1;
}

public OnIncomingPacket(playerid, packetid, BitStream:bs)
{
	//OnIncomingPacket (playerid=65535, packetid=39, BitStream:bs=-1958724)  - timeout all
	//OnIncomingPacket (playerid=65535, packetid=55, BitStream:bs=-1958724) 
	//printf("OnIncomingPacket (playerid=%d, packetid=%d, BitStream:bs=%d) ", playerid, packetid, BitStream:bs);
	if(packetid == 207)//ID_PLAYER_SYNC  
	{
		if(PlayerWhileAimPool(playerid))//niech pokazuje pool dla reszty graczy
		{
			new onFootData[PR_OnFootSync];
			BS_IgnoreBits(bs, 8);
			BS_ReadOnFootSync(bs, onFootData);
			onFootData[PR_weaponId] = 7;
			BS_SetWriteOffset(bs, 8);
			BS_WriteOnFootSync(bs, onFootData);
		}
	}
	else if(packetid == 55 || packetid == 39 || packetid == 38)
	{
		printf("OnIncomingPacket (playerid=%d, packetid=%d) ", playerid, packetid);
	}
	return 1;
}
const ID_MODIFIED_PACKET = 38;
IPacket:ID_MODIFIED_PACKET(playerid, BitStream:bs)
{
	new ip_address_pid[64];//musi zmienna z pojedynczą tablicą xD
	format(ip_address_pid, 64, "%s", playerid_lastip[playerid]);
	printf("ID_MODIFIED_PACKET: %s(%d) - BlockIpAddress!", ip_address_pid, playerid);
	BlockIpAddress(ip_address_pid, 15*1000);
	//Kick(playerid);
	return true;
}

public OnOutcomingPacket(playerid, packetid, BitStream:bs)
{
	//OnIncomingPacket (playerid=65535, packetid=39, BitStream:bs=-1958724)  - timeout all
	//OnIncomingPacket (playerid=65535, packetid=55, BitStream:bs=-1958724) 
	//printf("OnIncomingPacket (playerid=%d, packetid=%d, BitStream:bs=%d) ", playerid, packetid, BitStream:bs);
	if(packetid == 55 || packetid == 39)
	{
		printf("OnOutcomingPacket (playerid=%d, packetid=%d) ", playerid, packetid);
	}
	return 1;
}

public OnOutcomingRPC(playerid, rpcid, BitStream:bs)
{
	if(IsPlayerNPC(playerid)) return 1;
	if(playerid == -1) return 1;
	if(rpcid == 108)//AddGangZone
	{
		//gz per playerid - do nawigacji GPS
		new wGangZoneID, Float:min_x, Float:min_y, Float:max_x, Float:max_y;
		BS_ReadValue(
		bs,
		PR_UINT16,  wGangZoneID,
		PR_FLOAT,  min_x,
		PR_FLOAT,  min_y,
		PR_FLOAT,  max_x,
		PR_FLOAT,  max_y);
		//printf("AddGangZone: %d %f %f %f %f", wGangZoneID, Float:min_x, Float:min_y, Float:max_x, Float:max_y);
		if(rpc_gz_show[playerid][wGangZoneID] == true)
		{
			BS_Reset(bs);
			min_x = rpc_gz_pos[playerid][wGangZoneID][0];
			min_y = rpc_gz_pos[playerid][wGangZoneID][1];
			max_x = rpc_gz_pos[playerid][wGangZoneID][2];
			max_y = rpc_gz_pos[playerid][wGangZoneID][3];
			BS_WriteValue(
			bs,
			PR_UINT16,  wGangZoneID,
			PR_FLOAT,  min_x,
			PR_FLOAT,  min_y,
			PR_FLOAT,  max_x,
			PR_FLOAT,  max_y);
		}
		BS_ResetReadPointer(bs);
		BS_ResetWritePointer(bs);
		//printf("[EX]AddGangZone: %d %f %f %f %f", wGangZoneID, Float:min_x, Float:min_y, Float:max_x, Float:max_y);
	}
	else if(rpcid == 95)//CreatePickup
	{
		new dPickupID, dModelID, dSpawnType;
		new Float:dX, Float:dY, Float:dZ;
		BS_ReadValue(
		bs,
		PR_UINT32,  dPickupID,
		PR_UINT32,  dModelID,
		PR_UINT32,  dSpawnType,
		PR_FLOAT,  dX,
		PR_FLOAT,  dY,
		PR_FLOAT,  dZ);
		//zabezpieczenie, żeby pickup o modelu paczki pojawiał się tylko dla wybranych playerid (usuwa bug z widocznym dla wszystkich pickupem w module kurierów)
		//printf("dmodelid: %d | dpickupid: %d | courier_job_pickup: %d", dModelID, dPickupID, gracz[playerid][courier_job_pickup]);
		if(dModelID == 2912)//model paczki
		{
			if(dPickupID != gracz[playerid][courier_job_pickup]) return 0;
		}
		BS_ResetReadPointer(bs);
	}
	/*else if(rpcid == 84)//SetPlayerObjectMaterial(Text)
	{
		//MaterialType = 1 - tekstury, 2 - napisy
		//textury: UINT16 wObjectID, UINT8 MaterialType, UINT8 MaterialID, UINT16 ModelID, UINT8 libraryNameLength, char libraryName[], UINT8 textureNameLength, char textureName[], UINT32 color
		//napisy: UINT16 wObjectID, UINT8 MaterialType, UINT8 MaterialID, UINT8 MaterialSize, UINT8 fontNameLength, char fontName[], UINT8 FontSize, UINT8 Bold, UNIT32 FontColor, UNIT32 BackgroundColor, UNIT8 Align, CSTRING text[2048]
		//niewidzialna textura:  MaterialID:0 MaterialSize 100, fontNameLength 5, fontName[64] Arial, FontSize 27, Bold 1, FontColor 1048355, BackgroundColor 0
		new wObjectID, MaterialType;
		BS_ReadValue(
		bs,
		PR_UINT16,  wObjectID,
		PR_UINT8,  MaterialType);
		if(MaterialType == 1)
		{
			new MaterialID, ModelID, libraryNameLength, textureNameLength, color;
			new libraryName[64], textureName[64];
			BS_ResetReadPointer(bs);
			BS_ReadValue(
			bs,
			PR_UINT16,  wObjectID,
			PR_UINT8,  MaterialType,
			PR_UINT8,  MaterialID,
			PR_UINT16,  ModelID,
			PR_UINT8,  libraryNameLength,
			PR_STRING,  libraryName, libraryNameLength,
			PR_UINT8,  textureNameLength,
			PR_STRING,  textureName, textureNameLength,
			PR_UINT32,  color);
			color = 0x00000000;
			ModelID = 0;
			BS_ResetWritePointer(bs);
			BS_WriteValue(
			bs,
			PR_UINT16,  wObjectID,
			PR_UINT8,  MaterialType,
			PR_UINT8,  MaterialID,
			PR_UINT16,  ModelID,
			PR_UINT8,  libraryNameLength,
			PR_STRING,  libraryName,
			PR_UINT8,  textureNameLength,
			PR_STRING,  textureName,
			PR_UINT32,  color);
		}
		else if(MaterialType == 2)
		{
			new MaterialID, MaterialSize, fontNameLength, fontName[64], FontSize, Bold, FontColor, BackgroundColor;
			BS_ResetReadPointer(bs);
			BS_ReadValue(
			bs,
			PR_UINT16,  wObjectID,
			PR_UINT8,  MaterialType,
			PR_UINT8, MaterialID,
			PR_UINT8, MaterialSize,
			PR_UINT8, fontNameLength,
			PR_STRING, fontName, fontNameLength,
			PR_UINT8, FontSize,
			PR_UINT8, Bold,
			PR_UINT32, FontColor,
			PR_UINT32, BackgroundColor);
			MaterialType = 2;
			MaterialSize = 100;
			fontNameLength = 5;
			FontSize = 27;
			Bold = 1;
			FontColor = 1048355;
			BackgroundColor = 0;
			BS_ResetWritePointer(bs);
			BS_WriteValue(
			bs,
			PR_UINT16,  wObjectID,
			PR_UINT8,  MaterialType,
			PR_UINT8, MaterialID,
			PR_UINT8, MaterialSize,
			PR_UINT8, fontNameLength,
			PR_STRING, fontName,
			PR_UINT8, FontSize,
			PR_UINT8, Bold,
			PR_UINT32, FontColor,
			PR_UINT32, BackgroundColor);
		}
	}*/
	else if(rpcid == 44)//CreateObject - dziala
	{
		if(playerid != -1)
		{
			if(gracz[playerid][loading_objects]) gracz[playerid][objectload_count]++;
			else gracz[playerid][objectload_count] = 0;
			if(gracz[playerid][rpc_ObjDrawDist] > 5.0)
			{
				new wObjectID;
				new ModelID;
				new Float:x, Float:y, Float:z, Float:rotx, Float:roty, Float:rotz, Float:DrawDistance;
				new NoCameraCol;
				new attachedObject;
				new attachedVehicle;
				new Float:AttachOffsetX, Float:AttachOffsetY, Float:AttachOffsetZ, Float:AttachRotX, Float:AttachRotY, Float:AttachRotZ;
				new SyncRotation;
				BS_ReadValue(
				bs,
				PR_UINT16,  wObjectID,
				PR_UINT32,  ModelID,
				PR_FLOAT,  x,
				PR_FLOAT,  y,
				PR_FLOAT,  z,
				PR_FLOAT,  rotx,
				PR_FLOAT,  roty,
				PR_FLOAT,  rotz,
				PR_FLOAT,  DrawDistance,
				PR_UINT8,  NoCameraCol,
				PR_UINT16,  attachedObject,
				PR_UINT16,  attachedVehicle,
				PR_FLOAT,  AttachOffsetX,
				PR_FLOAT,  AttachOffsetY,
				PR_FLOAT,  AttachOffsetZ,
				PR_FLOAT,  AttachRotX,
				PR_FLOAT,  AttachRotY,
				PR_FLOAT,  AttachRotZ,
				PR_UINT8,  SyncRotation);
				if(DrawDistance > gracz[playerid][rpc_ObjDrawDist])
				{
					DrawDistance = gracz[playerid][rpc_ObjDrawDist];
					BS_Reset(bs);
					BS_WriteValue(
					bs,
					PR_UINT16,  wObjectID,
					PR_UINT32,  ModelID,
					PR_FLOAT,  x,
					PR_FLOAT,  y,
					PR_FLOAT,  z,
					PR_FLOAT,  rotx,
					PR_FLOAT,  roty,
					PR_FLOAT,  rotz,
					PR_FLOAT,  DrawDistance,
					PR_UINT8,  NoCameraCol,
					PR_UINT16,  attachedObject,
					PR_UINT16,  attachedVehicle,
					PR_FLOAT,  AttachOffsetX,
					PR_FLOAT,  AttachOffsetY,
					PR_FLOAT,  AttachOffsetZ,
					PR_FLOAT,  AttachRotX,
					PR_FLOAT,  AttachRotY,
					PR_FLOAT,  AttachRotZ,
					PR_UINT8,  SyncRotation);
					BS_ResetWritePointer(bs);
				}
				BS_ResetReadPointer(bs);
			}
		}
		//printf("wObjectID: %d, ModelID: %d dd: %f", wObjectID, ModelID, DrawDistance);
	}
	/*else if(rpcid == 105)//TextDrawSetString 
	{
		new wTextDrawID, TextLength, Text[256];
		BS_ReadValue(
		bs,
		PR_UINT16,  wTextDrawID,
		PR_UINT16,  TextLength,
		PR_STRING,  Text, TextLength);
		if(wTextDrawID < 10000)
		{
			if(!compare(rpc_tdsync[wTextDrawID][rpctds_lasttext], Text))
			{
				format(rpc_tdsync[wTextDrawID][rpctds_lasttext], 256, "%s", Text);
			}
			else return 0;
		}
		//printf("[%d]%d(%d): %s", rpcid, wTextDrawID, TextLength, Text);
		BS_ResetReadPointer(bs);
		BS_RPC(bs, playerid, rpcid, PR_LOW_PRIORITY, PR_RELIABLE_ORDERED);//obniżony priorytet
	}
	else if(rpcid == 134)//ShowTextDraw 
	{
		BS_RPC(bs, playerid, rpcid, PR_LOW_PRIORITY, PR_RELIABLE_ORDERED);//obniżony priorytet
		return 0;
	}
	else if(rpcid == 135)//HideTextDraw 
	{
		BS_RPC(bs, playerid, rpcid, PR_LOW_PRIORITY, PR_RELIABLE_ORDERED);//obniżony priorytet
		return 0;
	}*/
	/*else if(rpcid == 44)//CreateObject - render print
	{
			
		new wObjectID;
		new ModelID;
		new Float:x, Float:y, Float:z, Float:rotx, Float:roty, Float:rotz, Float:DrawDistance;
		new NoCameraCol;
		new attachedObject;
		new attachedVehicle;
		new Float:AttachOffsetX, Float:AttachOffsetY, Float:AttachOffsetZ, Float:AttachRotX, Float:AttachRotY, Float:AttachRotZ;
		new SyncRotation;
		BS_ReadValue(
		bs,
		PR_UINT16,  wObjectID,
		PR_UINT16,  ModelID,
		PR_FLOAT,  x,
		PR_FLOAT,  y,
		PR_FLOAT,  z,
		PR_FLOAT,  rotx,
		PR_FLOAT,  roty,
		PR_FLOAT,  rotz,
		PR_FLOAT,  DrawDistance,
		PR_UINT8,  NoCameraCol,
		PR_UINT16,  attachedObject,
		PR_UINT16,  attachedVehicle,
		PR_FLOAT,  AttachOffsetX,
		PR_FLOAT,  AttachOffsetY,
		PR_FLOAT,  AttachOffsetZ,
		PR_FLOAT,  AttachRotX,
		PR_FLOAT,  AttachRotY,
		PR_FLOAT,  AttachRotZ,
		PR_UINT8,  SyncRotation);
		//if(ModelID == 19480) 
		if(ModelID == 791) 
		{
			printf("ZABLOKOWANO model: %d", ModelID);
			return 0;
		}
		//printf("Wyrenderowano model: %d", ModelID);
		*/
		/*new wObjectID;
		BS_ReadValue(
		bs,
		PR_UINT16,  wObjectID);
		new BitStream:bs_deltexture = BS_New(); 

		new MaterialType, MaterialID, ModelID, libraryNameLength, textureNameLength, color;
		new libraryName[64], textureName[64];
		MaterialType = 1;
		MaterialID = 0;
		ModelID = 0;
		libraryNameLength = 4;
		textureNameLength = 4;
		color = 0x00000000;
		libraryName = "none";
		textureName = "none";
		BS_ResetWritePointer(bs);
		BS_WriteValue(
		bs_deltexture,
		PR_UINT16,  wObjectID,
		PR_UINT8,  MaterialType,
		PR_UINT8,  MaterialID,
		PR_UINT16,  ModelID,
		PR_UINT8,  libraryNameLength,
		PR_STRING,  libraryName,
		PR_UINT8,  textureNameLength,
		PR_STRING,  textureName,
		PR_UINT32,  color);
		
		BS_RPC(bs_deltexture, playerid, 84, PR_LOW_PRIORITY, PR_RELIABLE_ORDERED); 
		BS_Delete(bs_deltexture); 
		+++ rpcid 84:
		new wObjectID, MaterialType;
		BS_ReadValue(
		bs,
		PR_UINT16,  wObjectID,
		PR_UINT8,  MaterialType);
		if(MaterialType == 1)
		{
			new MaterialID, ModelID, libraryNameLength, textureNameLength, color;
			new libraryName[64], textureName[64];
			BS_ResetReadPointer(bs);
			BS_ReadValue(
			bs,
			PR_UINT16,  wObjectID,
			PR_UINT8,  MaterialType,
			PR_UINT8,  MaterialID,
			PR_UINT16,  ModelID,
			PR_UINT8,  libraryNameLength,
			PR_STRING,  libraryName, libraryNameLength,
			PR_UINT8,  textureNameLength,
			PR_STRING,  textureName, textureNameLength,
			PR_UINT32,  color);
			if(libraryNameLength != 4) return 0;
			printf("MaterialID, ModelID, libraryNameLength, textureNameLength, color: %d %d %d %d %d", MaterialID, ModelID, libraryNameLength, textureNameLength, color);
			printf("libraryName: %s textureName: %s ", libraryName, textureName);
		}
		*/
		
		/*działający kod czyszczący obiekty z tekstur
		new wObjectID;
		BS_ReadValue(
		bs,
		PR_UINT16,  wObjectID);
		new BitStream:bs_deltexture = BS_New(); 

		for(new k; k < 5; k++)
		{
			BS_Reset(bs_deltexture);
			new MaterialType, MaterialID, ModelID, libraryNameLength, textureNameLength, color;
			new libraryName[64], textureName[64];
			MaterialType = 1;
			MaterialID = k;
			ModelID = 0;
			libraryNameLength = 4;
			textureNameLength = 4;
			color = 0x00FF0000;
			libraryName = "none";
			textureName = "none";
			BS_ResetWritePointer(bs_deltexture);
			BS_WriteValue(
			bs_deltexture,
			PR_UINT16,  wObjectID,
			PR_UINT8,  MaterialType,
			PR_UINT8,  MaterialID,
			PR_UINT16,  ModelID,
			PR_UINT8,  libraryNameLength,
			PR_STRING,  libraryName,
			PR_UINT8,  textureNameLength,
			PR_STRING,  textureName,
			PR_UINT32,  color);
			BS_RPC(bs_deltexture, playerid, 84, PR_LOW_PRIORITY, PR_RELIABLE_ORDERED); 
		}
		BS_Delete(bs_deltexture); 

	}*/
	return 1;
}



stock rpc_GangZoneCreate(playerid, color, Float:min_x, Float:min_y, Float:max_x, Float:max_y)
{
	if(FloatIsNaN(min_x) || FloatIsNaN(min_y) || FloatIsNaN(max_x) || FloatIsNaN(max_y)) return -2;
	//***
	new Float:tmp;
	if(min_x == max_x) max_x += 0.5;
	if(min_y == max_y) max_y += 0.5;
	if(min_x > max_x)
	{
		tmp = max_x;
		max_x = min_x;
		min_x = tmp;
	}
	if(min_y > max_y) 
	{
		tmp = max_y;
		max_y = min_y;
		min_y = tmp;
	}
	gracz[playerid][gps_gzcount]++;
	//***
	new wGangZoneID = -1;
	for(new g; g < MAX_GANG_ZONES; g++)
	{
		if(rpc_gz_show[playerid][g] == false)
		{
			wGangZoneID = g;
			rpc_gz_show[playerid][g]= true;
			break;
		}
	}
	if(wGangZoneID != -1)
	{
		rpc_gz_pos[playerid][wGangZoneID][0] = min_x;
		rpc_gz_pos[playerid][wGangZoneID][1] = min_y;
		rpc_gz_pos[playerid][wGangZoneID][2] = max_x;
		rpc_gz_pos[playerid][wGangZoneID][3] = max_y;
		GangZoneShowForPlayer(playerid, wGangZoneID, color);
		//GangZoneFlashForPlayer(playerid, wGangZoneID, 0x00000000);
		return wGangZoneID;
	}
	return -1;
}

stock rpc_GangZoneDestroyAll(playerid)
{
	gracz[playerid][gps_gzcount] = 0;
	for(new g; g < MAX_GANG_ZONES; g++)
	{
		if(rpc_gz_show[playerid][g] == true)
		{
			rpc_gz_show[playerid][g] = false;
			GangZoneHideForPlayer(playerid, g);
		}
	}
	return 1;
}


