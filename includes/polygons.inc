//by Seregamil

/*

	Function's:
	    	CreatePolygon( Float: area[ ], Float: polygon_size = 5.0, all_points = sizeof area )
        	DestroyPolygon( polygonid )
	        PolygonFlashForAll( polygonid, color = 0xFF0000AA )
	        PolygonFlashForPlayer( playerid, polygonid, color = 0xFF0000AA )
	        PolygonStopFlashForAll( polygonid )
	        PolygonStopFlashForPlayer( playerid, polygonid )
	        PolygonShowForAll( polygonid, color = 0xFFFFFFAA )
	        PolygonShowForPlayer( playerid, polygonid, color = 0xFFFFFFAA )
	        PolygonHideForAll( playerid, polygonid )
        	PolygonHideForPlayer( playerid, polygonid )
	        CountGangZones()

	Callback's:
	    OnPlayerEnterPolygon( playerid, polygonid )
		OnPlayerLeavePolygon( playerid, polygonid )
*/

#define MAX_POLYGONS 20

#if !defined MAX_GANGZONES
    #define MAX_GANGZONES 1024
#endif

#if !defined INVALID_AREA_ID
	#define INVALID_AREA_ID -1
#endif

new gangZones[ MAX_POLYGONS * 2 ] = { INVALID_AREA_ID, ... };// firts & last

#if defined STREAMER_TYPE_AREA
	new polygons[ MAX_POLYGONS ] = { MAX_POLYGONS + 1, ... };
#endif

new totalGangZones = 0;

forward OnPlayerEnterPolygon( playerid, polygonid );
forward OnPlayerLeavePolygon( playerid, polygonid );

stock plgs_GangZoneCreate(Float:minx, Float:miny, Float:maxx, Float:maxy){
	totalGangZones++;
	return GangZoneCreate(minx, miny, maxx, maxy);
}

stock plgs_GangZoneDestroy(zone){
	totalGangZones--;
	return GangZoneDestroy(zone);
}

#if defined _ALS_GangZoneCreate
    #undef GangZoneCreate
#else
    #define _ALS_GangZoneCreate
#endif

#define GangZoneCreate plgs_GangZoneCreate

#if defined _ALS_GangZoneDestroy
    #undef GangZoneDestroy
#else
    #define _ALS_GangZoneDestroy
#endif

#define GangZoneDestroy plgs_GangZoneDestroy

stock CreatePolygon( Float: area[ ], Float: polygon_size = 5.0, all_points = sizeof area ){
	if( CountGangZones() >= MAX_GANGZONES )
	    return MAX_POLYGONS + 1;

	new i = -1;
	new g_zones = sizeof gangZones;
	while( ++i < g_zones )
	    if( gangZones[ i ] == INVALID_AREA_ID )
	        break;

	if( i == g_zones )
	    return MAX_POLYGONS + 1;

	new
		Float: start_x, Float: start_y,
		Float: end_x, Float: end_y,
		Float: draw_x, Float: draw_y,
		distance, slot = i;


	for( new points = -1, j = all_points ; ++points < j ; ){

		start_x = area[ points ];
		start_y = area[ points + 1 ];

		end_x = area[ points + 2 ];
		end_y = area[ ++points + 2 ];

		if( points + 1 == j )
		{
			end_x = area[ 0 ];
			end_y = area[ 1 ];
		}

		if( start_x == end_x || start_y == end_y ){
			gangZones[ slot ] = GangZoneCreate( start_x, start_y, end_x + ( start_x == end_x ? polygon_size : 0.0 ), end_y + ( start_x == end_x ? 0.0 : polygon_size ) );
			slot = i + 1;
		    continue;
		}

		distance = floatround( VectorSize( end_x - start_x, end_y - start_y, 0.0 ) / polygon_size ) ;

		draw_x = floatdiv( end_x - start_x, float( distance ) );
		draw_y = floatdiv( end_y - start_y, float( distance ) );

		while( distance-- ) {
			start_x += draw_x;
			start_y += draw_y;

			if( gangZones[ slot ] != INVALID_AREA_ID && slot == i )
				slot = i + 1;

   			gangZones[ slot ] = GangZoneCreate( start_x, start_y, start_x + polygon_size, start_y + polygon_size );

			if( CountGangZones() >= MAX_GANGZONES )
			    break;
		}

		if( CountGangZones() >= MAX_GANGZONES )
			break;
	}

	if( CountGangZones() >= MAX_GANGZONES ){
		DestroyPolygon( i / 2 + 1 );
		printf("ĐźĐľĐ»Đ¸ĐłĐľĐ˝ %i Đ±Ń‹Đ» Ń