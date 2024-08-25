stock Init_RGPS()
{
	SetTimer("Process_GPS_Receive", 600, true);
	return 1;
}

//GŁÓWNY SERWER
stock RGPS_CalculatePath(Float:fromX, Float:fromY, Float:fromZ, Float:targetX, Float:targetY, Float:targetZ, routeID, polygon = 0)
{
	/*new nodeFrom = -1;
	new nodeTarget = -1;
	nodeFrom = NearestNodeFromPoint(fromX, fromY, fromZ);
	if(nodeFrom == -1) return 0;
	nodeTarget = NearestNodeFromPoint(targetX, targetY, targetZ, .IgnoreNodeID = nodeFrom);
	if(nodeTarget == -1) return 0;
	new bool:polygon_create = false;
	if(polygon > 0) polygon_create = true;
	CalculatePath(nodeFrom, nodeTarget, routeID, polygon_create, 9.5);*/
	//
	mq_format("INSERT INTO `gps_calc` (`fX`, `fY`, `fZ`, `tX`, `tY`, `tZ`, `routeid`, `createpolygon`) VALUES ('%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d');", fromX, fromY, fromZ, targetX, targetY, targetZ, routeID, polygon);
	mq_send("QRGPS_Send");
	return 1;
}
new rgps_receive = false;
task Process_GPS_Receive()
{
	if(rgps_receive) return 1;
	rgps_receive = true;
	mq_format("SELECT * FROM `gps_calc` WHERE `status`='4';");
	mq_send("GPSReceiveDataFromDB");
	return 1;
}

task GPSReceiveDataFromDB()
{
	mq_getdata();
	new i;
	if(rekordy)
	{
		new id;
		new rrouteid;
		new rnodecount;
		new Float:rdistance;
		new rpolygoncount;
		new rpolygons_rawdata[60000];
		//
		new sscanf_format[16];
		new Float:rpolygons[8192];
		new null_arr[2048];
		while(i < rekordy)
		{
			cache_get_value_name_int(i, "id", 			id);
			cache_get_value_name_int(i, "routeid", 			rrouteid);
			cache_get_value_name_int(i, "nodecount", 			rnodecount);
			cache_get_value_name_float(i, "distance", 			rdistance);
			cache_get_value_name_int(i, "polygoncount", 			rpolygoncount);

			cache_get_value_name(i, "polygonarr", rpolygons_rawdata, 60000);
			format(sscanf_format, 16, "a<f>[%d]", 8192);
			sscanf(rpolygons_rawdata, sscanf_format, rpolygons);

			RGPS_WhenRouteIsCalculated(rrouteid, null_arr, rnodecount, rdistance, rpolygons, rpolygoncount);

			mq_format("DELETE FROM `gps_calc` WHERE `id`='%d';", id);
			mq_send("QDeleteCalcEnd");
			i++;
		}
	}
	rgps_receive = false;
	return 1;
}



//SERWER LICZĄCY
/*
new bool:gps_work = false;
task Process_GPSWORK()
{
	if(gps_work) return 1;
	gps_work  = true;
	mq_format("SELECT * FROM `gps_calc` WHERE `status`='0';");
	mq_send("GPSCalculator");
	return 1;
}

task GPSCalculator()
{
	mq_getdata();
	new i;
	if(rekordy)
	{
		new id;
		new Float:source[3];
		new Float:target[3];
		new createpolygon;
		new bool:isgood = false;
		while(i < rekordy)
		{
			isgood = false;
cache_get_value_name_int(i, "id", 			id);
cache_get_value_name_float(i, "fX", 			source[0]);
cache_get_value_name_float(i, "fY", 			source[1]);
cache_get_value_name_float(i, "fZ", 			source[2]);
cache_get_value_name_float(i, "tX", 			target[0]);
cache_get_value_name_float(i, "tY", 			target[1]);
cache_get_value_name_float(i, "tZ", 			target[2]);
cache_get_value_name_int(i, "createpolygon", 			createpolygon);
			new nodeFrom = -1;
			new nodeTarget = -1;

			nodeTarget = NearestNodeFromPoint(target[0], target[1], target[2]);

			if(nodeTarget != -1)
			{
				nodeFrom = NearestNodeFromPoint(source[0], source[1], source[2], .IgnoreNodeID = nodeTarget);
				if(nodeFrom != -1)
				{
					new bool:polygon_create = false;
					if(createpolygon > 0) polygon_create = true;
					CalculatePath(nodeFrom, nodeTarget, 50000+id, polygon_create, 9.5);
					isgood = true;
				}
			}

			if(isgood == true)
			{
				mq_format("UPDATE `gps_calc` SET `status`='2' WHERE `id`='%d';", id);
				mysql_query(g_SQL, mQuery, false);
			}
			else
			{
				mq_format("UPDATE `gps_calc` SET `status`='3' WHERE `id`='%d';", id);
				mysql_query(g_SQL, mQuery, false);
			}

			i++;
		}
	}
	gps_work = false;
	return 1;
}

task test_GPS_WhenRouteIsCalculated(routeid,node_id_array[],amount_of_nodes,Float:distance,Float:Polygon[],Polygon_Size)
{
	routeid = routeid-50000;//true routeid
	for(new pol; pol < Polygon_Size; pol += 36)
	{
		mq_format("UPDATE `gps_calc` SET `polygonarr`=CONCAT(polygonarr, '%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f ') WHERE `id`='%d';", Polygon[pol], Polygon[pol+1], Polygon[pol+2], Polygon[pol+3], Polygon[pol+4], Polygon[pol+5], Polygon[pol+6], Polygon[pol+7], Polygon[pol+8], Polygon[pol+9], Polygon[pol+10], Polygon[pol+11], Polygon[pol+12], Polygon[pol+13], Polygon[pol+14], Polygon[pol+15], Polygon[pol+16], Polygon[pol+17], Polygon[pol+18], Polygon[pol+19], Polygon[pol+20], Polygon[pol+21], Polygon[pol+22], Polygon[pol+23], Polygon[pol+24], Polygon[pol+25], Polygon[pol+26], Polygon[pol+27], Polygon[pol+28], Polygon[pol+29], Polygon[pol+30], Polygon[pol+31], Polygon[pol+32], Polygon[pol+33], Polygon[pol+34], Polygon[pol+35], routeid);
		mq_send("QAddGPSPol");
		//printf("%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", Polygon[pol], Polygon[pol+1], Polygon[pol+2], Polygon[pol+3], Polygon[pol+4], Polygon[pol+5], Polygon[pol+6], Polygon[pol+7], Polygon[pol+8], Polygon[pol+9], Polygon[pol+10], Polygon[pol+11], Polygon[pol+12], Polygon[pol+13], Polygon[pol+14], Polygon[pol+15], Polygon[pol+16], Polygon[pol+17], Polygon[pol+18], Polygon[pol+19], Polygon[pol+20], Polygon[pol+21], Polygon[pol+22], Polygon[pol+23], Polygon[pol+24], Polygon[pol+25], Polygon[pol+26], Polygon[pol+27], Polygon[pol+28], Polygon[pol+29], Polygon[pol+30], Polygon[pol+31], Polygon[pol+32], Polygon[pol+33], Polygon[pol+34], Polygon[pol+35]);
	}
	mq_format("UPDATE `gps_calc` SET `status`='4', `nodecount`='%d', `distance`='%f', `polygoncount`='%d' WHERE `id`='%d';", amount_of_nodes, distance, Polygon_Size, routeid);
	mq_send("QCompleteGPSCalc");
	//new routeQuery[2000];
	//ormat(routeQuery, 2000, "UPDATE `gps_calc` SET `status`='4', `polygonarr`='%s' WHERE `id`='%d';", polygondata, routeid);
	//mysql_tquery(g_SQL, routeQuery, "QEndGPSCalc");
	return 1;
}*/