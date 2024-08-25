//***********************STATYSTYKI GRACZA****************************
enum player_stats
{
//BAZA DANYCH
	UID,
	Name[MAX_PLAYER_NAME+1],
	nick_ic[MAX_PLAYER_NAME+1],
	HP,
	armour,
	stamina,
	Haslo[64],
	Plec,
	Wiek,
	Skin,
	skin_custom,
	skin_custom_expire,
	PSek,
	PMin,
	PGodz,
	Float:PosX,
	Float:PosY,
	Float:PosZ,
	Float:PosR,
	LastOnline,
	AdminLevel,
	WebReg,
	f_master,
	MapperLvl,
	ForumNick[20],
	master_nick[32],
	gold,
	vip,
	kursy,
	kasa,
	ps_score,
	muted_timestamp,
	frakcja,
	frakcja_permlvl,
	frakcja_tytul[24],
	frakcja_wyplata,
	frakcja_totalduty,
	frakcja_onduty,
	duty_suma,
	firma,
	firma_permlvl,
	firma_wyplata,
	firma_kontrakt_kg,
	firma_onduty,
	firma_sessionid,
	company_kursy_per_wyplata,
	custom_radio[64],
	bw,
	bw_time,
	Float:bw_X,
	Float:bw_Y,
	Float:bw_Z,
	bw_interior,
	bw_virtualworld,
	wypadek,
	wypadek_time,
	Float:wypadek_X,
	Float:wypadek_Y,
	Float:wypadek_Z,
	Float:wypadek_R,
	wypadek_vehicleuid,
	dokumenty,
	prawko_TB,
	prawko_PB,
	prawko_TCE,
	prawko_PCE,
	upr_adr,
	przebieg,
	Float:sila,
	Float:odpornosc,
	fight_style,
	fight_timestamp_end,
	karnet,
	last_radio[128],
	pursuit_total,
	pursuit_escapes,
	pursuit_catch,
	bank_number,
	bank_saldo,
	hlfriend,
	bool:unused03DL, 
	//************************************************************************************TYMCZASOWE
	//OnPlayerUpdate zmienne 
	opu_timestamp,
	opu_speed,
	opu_vehicleid,
	bool:opu_delay_inprogress,
	//GetPlayerKeys
	gpk_keys,
	gpk_updown,
	gpk_leftright,
	//***
	Text3D:p_label[4],
	p_label_string[1024],
	p_label_nickcolor,
	p_label_excol_pause,
	p_label_nick_oc_ic,
	bubble_text[144],
	bubble_timestamp,
	statusplayer[512],
	bool:pasy,
	spawned,
	bool:loggedin,
	sobeit_detect,
	bool:first_spawn,
	kick_antyspam,
	admin_duty,
	mapper_weather,
	time_leftnotify,
	bool:hl_logon_block,
	time_spam[MAX_SPAMID],
	carhud_status,
	carhud_blinkstatus[2],
	carhud_speedup_tick,
	gui_listitem,
	bool:delay_enable_engine,
	bool:carhud_blinkfueltemp,
	zerosto_starttime,
	radio_status,
	radio_laststation,
	radio_displaystep,
	dystrybutor_status,
	dystrybutor_price,
	dystrybutor_tanked,
	dystrybutor_multiplier,
	dystrybutor_companyid,
	dystrybutor_vehicleid,
	dystrybutor_fueltype,
	last_sound,
	autoszrot_id,
	last_vehicleid,
	courier_job,
	courier_job_vehicleid,
	courier_job_status,
	courier_job_pickup,
	courier_job_actor,
	courier_job_clientid,
	Text3D:courier_job_3dtext,
	player_sync_status,
	bool:td_rightmsgboxtitlecolor,
	truckbuy_status,
	truckbuy_selected,
	Float:truckbuy_campos[3],
	Float:truckbuy_camlook[3],
	bool:td_confirmcargo,
	cargo_trailerdid,
	cargo_confirmtrailer,
	//***************GPS
	bool:gps_enabled,
	gps_Calculating,
	Float:gps_LastDistance,
	Float:gps_dest_X,
	Float:gps_dest_Y,
	Float:gps_dest_Z,
	Float:gps_tstart_X,
	Float:gps_tstart_Y,
	Float:gps_tstart_Z,
	bool:gps_refreshtrack,
	gps_gzcount,
	bool:gps_autooff,
	//***************GPS-end 
	lastpage_flcargolist,
	bool:flcargolist_arrowback,
	bool:flcargolist_arrownext,
	flcargolist_count_goods,
	connected_trailervid,
	objective_status,
	objective_iconid,
	objective_objectid[6],
	Float:objective_X,
	Float:objective_Y,
	Float:objective_Z,
	Text3D:objective_text3d,
	bool:delivered_window,
	bool:delivered_window_process,
	delivered_window_step,
	delivered_window_achiv_list[1024],
	delivered_window_reward_list[1024],
	delivered_window_totalscore,
	delivered_window_totalmoney,
	delivered_cargovid,
	delivered_hardroute,
	delivered_adr_status,
	bool:delivered_canexit,
	DeliveredSummary_row1[1024],
	DeliveredSummary_row2[1024],
	DeliveredSummary_bonus_price,
	DeliveredSummary_bonus_sc,
	rlg_timestamp,
	loginhistory_start,
	loginhistory_end,
	loginhistory_ip[64],
	loginhistory_serial[64],
	gfv_waitforpickup,
	status_td_saction,
	time_duty,
	time_duty_total,
	cache_mandat_reason[64],
	bool:kajdanki,
	bool:przykuty,
	przykutydo,
	scigany_lvl,
	scigany_powod[64],
	prisoner,
	prisoner_time,
	prisoner_prisonid,
	bool:status_td_fractiontool,
	used_fractiontool,
	f_maxspeedometer,
	exceeded_speed,
	exceeded_speed_time,
	stamina_timestamp,
	pointer_object,
	bool:relog_data_loaded,
	call_crash_reload,
	spray_color[2],
	spray_paintjob,
	spray_progress,
	bool:spray_block,
	last_skin,
	trailer_checkperm,
	towtruck_trailerid,
	taxometr_td,
	driver_license_qid,
	driver_license_type,
	driver_license_points,
	driver_license_time,
	driver_license_cp,
	td_dokumenty,
	bool:admin_spec_enabled,
	admin_spec_targetid,
	admin_spec_myvw,
	admin_spec_myint,
	admin_spec_target_laststate,
	bool:td_adminspec,
	bool:admin_godofcar,
	pause_time[2],
	afk_time[2],
	bool:afk_status,
	afk_detect_timestamp,
	Float:afk_lastposX,
	Float:afk_lastposY,
	Float:afk_lastposZ,
	bool:bus_travel,
	bool:loading_objects,
	bool:stormoff,
	Float:rpc_ObjDrawDist,
	bool:td_seatbelts_blinksw,
	parkingpol_id,
	leftnotify_customsound,
	td_pursuit,
	bool:pursuit_enabled,
	Float:pursuit_bar_left,
	Float:pursuit_bar_right,
	chasing_targetid,
	pursuit_invisible_timestamp,
	policestop_timestamp,
	Float:aaPosX,
	Float:aaPosY,
	Float:aaPosZ,
	aaInt,
	aaVW,
	aaPosUsed,
	bool:aaInvisible,
	npc_taxi_calcroute,
	cmp_showlog_page,
	cmp_showlog_targetuid,
	cmp_showlog_flag,
	cmp_showlog_vehuid,
	micro_td,
	bool:has_sampvoice,
	holding_key_nitro,
	routelog_start_time,
	bool:admin_eyeveh,
	bool:admin_eyecmd,
	bool:vhl_echo,
	vhl_volume_speak,
	vhl_volume_micro,
	vhl_ptt_virtkeycode,
	bool:vhl_getall,
	vhl_muted_timestamp,
	bool:vhl_has_micro,
	whileanim,
	td_simpletext,
	scoreduty_multiplier,
	bool:td_shoot_type,
	shoot_td_time,
	bool:shoot_sf,
	last_playercolor,
	when_tipsy,
	last_drinkuse,
	drunk_remove_tick,
	timestamp_lastdrunk,
	fuel_warning_timestamp,
	photo_speed_timestamp,
	td_speedlimit,
	objectload_count,
	status_lunapark,
	dj_listen[144],
	rope_object[ROPE_LENGTH],
	rope_while,
	rope_vehicleid,
	Float:rope_endX,
	Float:rope_endY,
	Float:rope_endZ,
	asg_pickup_tick,
	asg_score,
	asg_specpid,
	bool:taser_has,
	bool:taser_tased,
	acwarn[50],
	bool:blockpm,
	lastshotedby,
	hud_lastskin,
	hud_lastweapon,
	hud_lastammo,
	bool:hud_lastammo_bg,
	hud_tick_fraction,
	//event
	bool:event_master,
	bool:event_saved, //czy gracz jest zapisany na event
	event_teamid,//int przechowujący id drużyny eventowej (-1 = brak)
	bool:ev_toggle_controllable,
	bool:event_hide_labels,
	event_last_skin_id
	//event - end
};

new gracz[MAX_PLAYERS][player_stats];

new playerid_lastip[MAX_PLAYERS][64];

new gui_cache[MAX_PLAYERS][GUICACHE_MAXLIST][GUICACHE_MAXVAR];
new PlayerEditObject[MAX_PLAYERS];

new Swears[MAX_SWEARS][126];
new num_censor_words = 0;

enum ts_data
{
	bool:ts_status,
	ts_objects[10],
	ts_iconid,
};

new trailer_select[MAX_PLAYERS][ts_data];

enum eq_select_info
{
    s_id,
    s_itemid,
    s_count,
    s_cdn,
    s_cdn_max,
    s_used
};

new eq_select[MAX_PLAYERS][eq_select_info];

enum attached_object_data
{
    Float:ao_x,
    Float:ao_y,
    Float:ao_z,
    Float:ao_rx,
    Float:ao_ry,
    Float:ao_rz,
    Float:ao_sx,
    Float:ao_sy,
    Float:ao_sz,
    ao_typ
};
 
new ao[MAX_PLAYERS][MAX_PLAYER_ATTACHED_OBJECTS][attached_object_data];

enum combine_info
{
    c_id,
    c_step,
    c_bad,
    c_key[6],
    c_qkey,
    c_key_time,
    c_mode
};

new combine_mode[MAX_PLAYERS][combine_info];
enum ognisko_info
{
o_status,
Float:o_X,
Float:o_Y,
Float:o_Z,
o_object[8],
Text3D:o_label
};

new ognisko[MAX_PLAYERS][ognisko_info];

#define EVENT_MAX_CASES 20
//*********************SERWER*************************************************************************************************
enum server_data
{
	wersja[64],
	pogoda,
	playerPoolSize,
	time_timestamp,
	time_hour,
	time_minute,
	time_second,
	uptime,
	time_lasttime_timer,
	r_weather,
	n_weather,
	world_control_timestamp,
	maxnpc,
	npc_connected,
	bool:respawn_inprogress,
	respawn_adminnick[24],
	time_autorespawn,
	cooldown_restart,
	reason_restart[32],
	prawkoegz_delay,
	time_connectinfo,
	bool:chat_online_process,
	bool:first_time_loaderveh,
	bool:bannodes_loaded,
	playerscount,
	interwencja_time,
	bool:att_dontchangepin,
	attack_block_timestamp,
	timestamp_VPBusinnesLabels,
	dj_url[144],
	srv_customhostname[128],
	srv_password[32],
	timestamp_delivery_msg,
	bool:block_global_ooc,
	last_annmsg,
	hud_lasticon,
	actual_oilid,
	//event
	bool:event_started,//hold do sprawdzania czy trwa juz jakis event
	bool:event_records_on, //Czy sa wlaczone zapisy na event
	event_max_users,//ilosc maksymalnej liczby uczestnikow
	event_time_start,//do wyliczenia trwania eventu
	event_max_added_score,//maksymalna liczba (na cały event) score do rozdania
	event_max_added_money,//maksymalna liczba (na cały event) kasy do rozdania
	bool:event_users_freeze,
	bool:event_no_dm_status,
	event_master_exit_timestamp,
	bool:event_destroy_or_respawn_veh, //destroy = true | respawn = false
	event_weather_id,
	event_hour, //if == -1 czas nie ustawiony
	event_sec_odliczanie,
	event_pickup_id,
	Float:event_pickup_pos[3],
	event_case[EVENT_MAX_CASES],//walizki
	event_case_money[EVENT_MAX_CASES],
	event_case_score[EVENT_MAX_CASES],
	STREAMER_TAG_3D_TEXT_LABEL:event_case_textid[EVENT_MAX_CASES],
	Float:event_cases_pos_x[EVENT_MAX_CASES],
	Float:event_cases_pos_y[EVENT_MAX_CASES],
	Float:event_cases_pos_z[EVENT_MAX_CASES],
	event_cases_daily_count
	//event end
};
new event_cases_podpowiedz[EVENT_MAX_CASES][124]; //przepraszam seba innej opcji nie widze
new serwer[server_data];
new temp_string[1024];

new skins_male[] = {20009, 20010, 20011, 1, 2, 3, 4, 5, 6, 7, 14, 15, 17, 19, 20, 21, 22, 23, 24, 25, 28, 29, 30, 32, 33, 34, 35, 36, 37, 43, 44, 47, 48, 57, 58, 59, 60, 66, 67, 72, 73, 86, 96, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 111, 112, 113, 114, 115, 117, 118, 119, 120, 122, 123, 125, 133, 142, 170, 176, 177, 180, 184, 188, 202, 206, 217, 221, 222, 248, 247, 249, 250, 259, 269, 270, 289, 292, 293, 296, 297};
new skins_female[] = {20012, 20013, 20014, 12, 13, 40, 55, 56, 65, 91, 93, 131, 141, 150, 151, 169, 192, 193, 195, 211, 216, 219, 224, 225, 226, 263, 298};

//EVENT PANEL
#define MAX_EVENT_TEAM_NAME 50
#define MAX_EVENT_TEAMS 4
enum teams_ev_data
{
	bool:used, //spr. czy dana druzyna jest uzywana
	team_name[MAX_EVENT_TEAM_NAME], //nazwa druzyny
	bool:friendly_fire //false - wylaczony | true - wlaczony
};
new event_teams[MAX_EVENT_TEAMS][teams_ev_data];//maksymalna liczba druzyn: MAX_EVENT_TEAMS
//**********************************************************************WEJŚCIA
enum door_info
{
    d_id,
    d_status,
    Float:d_aX,
    Float:d_aY,
    Float:d_aZ,
    Float:d_bX,
    Float:d_bY,
    Float:d_bZ,
    d_intB,
    d_pickupA,
    d_pickupB,
    Text3D:d_labelA,
    Text3D:d_labelB
};

new door[MAX_DOORS][door_info];
//*********************************************************************OBIEKTY
enum oinfo
{
	oUID,
	oModel,
	oObject,
	oMMAT,
	Float:oX,
	Float:oY,
	Float:oZ,
	Float:oRX,
	Float:oRY,
	Float:oRZ,
	Float:goX,
	Float:goY,
	Float:goZ,
	Float:goRX,
	Float:goRY,
	Float:goRZ,
	Float:gSpeed,
	Float:gRange,
	bool:gOpen,
	gCloseTimeOut,
	oMgate,
	mgOwnerType,
	mgOwner,
	oInt,
	oVW,
	oGrupa,
	oOwner
};
new ObjectInfo[MAX_OBJECTS][oinfo];
new GateObjects[MAX_GATES];
//*********************************************************************POJAZDY
enum pojazd_info
{
	v_id,
	v_model,
	Float:v_HP,
	Float:v_X,
	Float:v_Y,
	Float:v_Z,
	Float:v_R,
	v_color[2],
	Float:v_paliwo,
	v_owner_type,
	v_owner,
	v_handbrake,
	Float:v_handbrake_posX,
	Float:v_handbrake_posY,
	Float:v_handbrake_posZ,
	Float:v_handbrake_posR,
	bool:v_cplue,
	v_object[MAX_VEHICLE_OBJECTS],//0-3 - loga | 4-5 - długie światła | 6-7 - dym z komina | 8-11 neony/ex leflektory | 12 - płomienie ADR * !PAMIĘTAJ O PETLACH!
	v_przebieg,
	Float:v_przebiegunits,
	Float:v_Pmeters,
	Float:v_LPosX,
	Float:v_LPosY,
	Float:v_LPosZ,
	Float:v_enginetemp,
	Text3D:v_text3d,
	v_text3d_strcache[512],
	v_trafficlights,
	v_speed,
	v_cargo,
	v_cargo_amount,
	v_cargo_price,
	v_cargo_score,
	Float:v_cargo_target_X,
	Float:v_cargo_target_Y,
	Float:v_cargo_target_Z,
	v_cargo_destvid,
	Float:v_cargo_distance,
	v_trailerupdate,
	Float:v_idle_X,
	Float:v_idle_Y,
	Float:v_idle_Z,
	Float:v_idle_R,
	v_damages_lifetime_km[MAX_VEHICLEDAMAGES],
	v_damages_lifetime_strdata[256],
	v_karoseria_hits,
	v_numberplate[32],
	v_tune_data[32],
	v_tune_strdata[256],
	v_paintjob,
	//
	v_idletime,
	v_sirenstatus,
	v_flash_step,
	v_taxometr_price_per_km,
	v_taxometr_distance,
	v_taxometr_price,
	bool:v_taxometr_statuson,
	bool:v_specialvehicle,
	bool:v_roosters_withoutsiren,
	v_uvds_panels,
	v_uvds_doors,
	v_uvds_lights,
	v_uvds_tires,
	Float:v_crash_Health,
	Float:v_crash_Speed,
	v_nitrotime,
	bool:v_whilenitro,
	v_nitro_tick,
	v_kluczyki_puid,
	v_neon_modelid,
	v_adr_warn,
	v_fire_hp,
	v_fire_warn,
	bool:v_timer_onvehdeath,
	v_lastuser[32],
	//event
	bool:v_event_used,
	v_event_creator_uid,
	bool:v_event_godmode,
	v_event_teamid,//int przechowujący id drużyny eventowej (-1 = brak)
	v_event_virtual_world,
	v_event_interior
	//event end
};
new pojazd[MAX_VEHICLES][pojazd_info];

enum vd_data
{
	vd_title[64],
	vd_exp_km,
	Float:vd_price_proc
};

new VehicleDamages[MAX_VEHICLEDAMAGES][vd_data] =
{
	{"Opony", 3021, 0.6},//0
	{"Drazki kierownicze", 22032, 4.5},//1
	{"Wahacze", 15992, 6.0},//2
	{"Filtr paliwa", 7540, 0.5},//3
	{"Pompa paliwa", 12502, 9.0},//4
	{"Uklad wtryskowy", 11205, 15.0},//5
	{"Swiece", 6592, 0.9},//6
	{"Kable wysokiego napiecia", 5532, 2.0},//7
	{"Uszczelka pod glowica", 21303, 16.1},//8
	{"Rozrusznik", 50301, 5.0},//9
	{"Uklad dolotowy", 17310, 5.3},//10
	{"Czujnik polozenia walka rozrzadu", 25301, 3.2},//11
	{"Blok silnika", 120300, 19.4},//12
	{"Zawory", 47502, 12.2},//13
	{"Przekaznik swiatel", 3250, 0.4},//14
	{"Chlodnica", 30250, 1.5},//15
	{"Termostat", 9308, 2.1},//16
	{"Przewod paliwowy", 12635, 1.0},//17
	{"Zbiornik paliwa", 23260, 1.3}//18
};//85.2% - naprawa wszystkiego poza blokiem silnika, z blokiem silnika (19.4) - 104.6%

enum neon_data
{
	nn_name[32],
	nn_model 
};

new neon_list[MAX_NEONS][neon_data] = 
{
	{"{FF0000}Czerwony", 18647},
	{"{0000FF}Niebieski", 18648},
	{"{00FF00}Zielony", 18649},
	{"{FFFF00}Żółty", 18650},
	{"{FF00FF}Różowy", 18651},
	{"{FFFFFF}Biały", 18652}
};
//--------------------------------------------------------------------------------------------FRAKCJE
enum fr_data
{
	Float:fr_dutyX,
	Float:fr_dutyY,
	Float:fr_dutyZ,
	fr_paymin,
	fr_paymax,
	fr_pickup,
	fr_icon,
	Text3D:fr_text3d,
	fr_skins_male[12],
	fr_skins_female[12],
	bool:fr_disable_ff,
	fr_money,
	fr_multiplier,
	fr_intval1,
	fr_intval2,
	fr_intval3,
	fr_intval4
};
new fractions[7][fr_data];
// napady
enum att_data
{
	att_pin,
	att_status,
	att_time,
	att_fuelid,
	att_fuelcount,
	att_stationid,
	att_starttime,
	att_playeruid,
	att_playernick[24],
	att_trailerid,
	att_simpletext_def[512],//broniący - mafia
	att_simpletext_att[512],//atakuje - policja
	att_temp_count_m_all,
	att_temp_count_m_bw
};

new attack[att_data];
//--------------------------------------------------------------------------------------------FIRMY
enum cny_data
{
	cny_name[64],
	cny_owneruid,
	cny_money,
	cny_score,
	cny_expire,
	cny_price,
	cny_created[32],
	cny_polygoncount,
	cny_polygonid,
	Float:cny_dutyX,
	Float:cny_dutyY,
	Float:cny_dutyZ,
	Float:cny_buyparkX,
	Float:cny_buyparkY,
	Float:cny_buyparkZ,
	Float:cny_buyparkR,
	cny_pickup,
	cny_icon,
	Text3D:cny_text3d,
	cny_losk,
	//wykonywany kontrakt
	cny_cnt_goodid,
	cny_cnt_fromid,
	cny_cnt_targetid,
	Float:cny_cnt_size,
	Float:cny_cnt_size_complet,
	cny_cnt_price,
	cny_cnt_penalty,
	cny_cnt_score,
	cny_cnt_time,
	cny_cnt_time_left,
	Float:cny_cnt_distance,
	cny_cnt_signer_uid,
	cny_cnt_signer_sid
};

new company[MAX_COMPANY][cny_data];
//carshop
new carshop_db_id[10];
new Text3D:carshop_3dtext_id[10];
new carshop_price[10];
new carshop_specid[10];
new carshop_counter;
new carshop_bans[] = {403, 413, 414, 428, 440, 443, 455, 470, 456, 482, 489, 498, 499, 514, 515, 524, 573, 495, 490, 596, 597, 598, 502, 427, 525, 552, 578, 459, 563, 416, 417, 407, 420, 431, 551, 405, 409};
new Float:carshop_parkplace[][4] = 
{
	{2328.8838,987.4886,10.6131,89.8421}, // salon1
	{2328.8926,990.5840,10.6131,89.8421}, // salon2
	{2328.9011,993.6938,10.6131,89.8421}, // salon3
	{2328.9104,996.9871,10.6131,89.8421}, // salon4
	{2328.9187,1000.1155,10.6131,89.8421}, // salon5
	{2328.9270,1003.2759,10.6131,89.8421}, // salon6
	{2299.7026,987.3839,10.6131,269.8421}, // salon7
	{2299.7104,990.5381,10.6131,269.8421}, // salon8
	{2299.7188,993.7274,10.6131,269.8421}, // salon9
	{2299.7268,996.8615,10.6131,269.8421}, // salon10
	{2299.7351,999.9994,10.6131,269.8421}, // salon11
	{2299.7444,1003.2739,10.6131,269.8421}, // salon12
	{2299.7534,1006.3615,10.6131,269.8421}, // salon13
	{2299.7617,1009.4706,10.6131,269.8421}, // salon14
	{2299.7703,1012.7109,10.6131,269.8421}, // salon15
	{2299.7788,1015.9964,10.6131,269.8421}, // salon16
	{2299.7869,1019.1405,10.6131,269.8421} // salon17
};
new carshop_park_queue;
new carshop_buylist[1024];

//truck shop
new truckshop_db_id[MAX_SALONTRUCKSLOTS];
new truckshop_price[MAX_SALONTRUCKSLOTS];
new truckshop_specid[MAX_SALONTRUCKSLOTS];
new truckshop_cameraquery[] = {413, 455, 498, 456, 499, 459,  450, 584, 403, 515, 514, 435 , 591, 440, 414, 578, 428, 482};
new truckshop_bans[] = {/*naczepy:435, 450, 584, 591end, */443, 573, 524, 408};
new truckshop_counter;

new Float:truckshop_parkplace[0][4] = 
{
	{2345.5474,1518.0078,11.4368,89.8778}, //0
	{2345.5334,1511.6838,11.4369,89.8778}, //1
	{2345.5300,1505.4784,11.5029,89.8794}, //2
	{2345.5156,1498.8781,11.5043,89.8794}, //3
	{2345.5093,1495.7678,11.5049,89.8794}, //4
	{2269.6902,1495.9292,11.4259,269.8792}, //5
	{2269.7031,1502.1486,11.4261,269.8792}, //6
	{2269.7170,1508.6180,11.4262,269.8792}, //7
	{2269.7300,1514.8359,11.4263,269.8792} //8
};
new truckshop_park_queue;
//end
new fuel_station_price[MAX_CONCERNS][3];
//*********************************************************************Specyfikacja techniczna pojazdów
enum vspec_data
{
	vspec_name[24],//1
	vspec_model,//2
	vspec_fueltype,//3
	vspec_tanksize,//4
	Float:vspec_fuelconsumption,//5
	Float:vspec_0100,//6
	vspec_vmax//7
};

new pojazd_spec[MAX_CARSPEC][vspec_data] =
{
	//         1                  2      3        4    5     6      7
	{"Landstalker", 400, F_ON, 75, 12.3, 3.7, 171},
	{"Bravura", 401, F_PB, 55, 6.0, 4.4, 159},
	{"Buffalo", 402, F_PB, 80, 12.0, 2.5, 202},
	{"Linerunner", 403, F_ON, 950, 25.2, 6.6, 119},
	{"Perennial", 404, F_ON, 38, 5.7, 6.4, 144},
	{"Sentinel", 405, F_PB, 78, 8.1, 3.6, 177},
	{"Firetruck", 407, F_ON, 350, 17.1, 3.5, 160},
	{"Stretch", 409, F_PB, 70, 9.1, 4.0, 171},
	{"Manana", 410, F_PB, 48, 4.3, 5.3, 140},
	{"Infernus", 411, F_PB, 73, 16.0, 2.1, 239},
	{"Voodoo", 412, F_PB, 52, 9.0, 3.1, 182},
	{"Pony", 413, F_ON, 77, 8.5, 7.9, 119},
	{"Mule", 414, F_ON, 75, 9.0, 8.2, 114},
	{"Cheetah", 415, F_PB, 55, 10.9, 2.7, 208},
	{"Ambulance", 416, F_ON, 95, 8.4, 3.4, 166},
	{"Esperanto", 419, F_ON, 55, 5.9, 4.4, 161},
	{"Taxi", 420, F_PB, 70, 6.5, 4.6, 157},
	{"Washington", 421, F_PB, 60, 6.5, 4.1, 166},
	{"Bobcat", 422, F_ON, 45, 5.8, 5.0, 151},
	{"BF Injection", 424, F_ON, 35, 7.2, 3.3, 146},
	{"Premier", 426, F_PB, 70, 7.9, 3.4, 187},
	{"Enforcer", 427, F_ON, 87, 9.3, 4.2, 179},
	{"Securicar", 428, F_ON, 85, 8.9, 5.1, 170},
	{"Banshee", 429, F_PB, 65, 13.3, 2.4, 218},
	{"Bus", 431, F_ON, 200, 14.7, 8.3, 141},
	{"Hotknife", 434, F_ON, 40, 9.0, 3.1, 180},
	{"Previon", 436, F_PB, 55, 4.9, 4.8, 161},
	{"Stallion", 439, F_PB, 45, 9.1, 3.2, 182},
	{"Rumpo", 440, F_ON, 79, 7.8, 5.8, 147},
	{"Packer", 443, F_ON, 550, 28.0, 7.1, 137},
	{"Admiral", 445, F_ON, 60, 8.4, 3.8, 177},
	{"Turismo", 451, F_PB, 70, 14.4, 2.2, 209},
	{"Flatbed", 455, F_ON, 405, 21.9, 6.8, 170},
	{"Yankee", 456, F_ON, 100, 14.0, 10.5, 114},
	{"Solair", 458, F_PB, 55, 7.5, 4.2, 170},
	{"Topfun Van", 459, F_ON, 80, 7.2, 5.4, 147},
	{"PCJ-600", 461, F_PB, 14, 6.3, 2.5, 174},
	{"Faggio", 462, F_PB, 11, 3.3, 8.3, 121},
	{"Freeway", 463, F_PB, 19, 8.4, 3.9, 156},
	{"Glendale", 466, F_ON, 60, 5.0, 4.2, 159},
	{"Oceanic", 467, F_ON, 45, 4.7, 5.2, 152},
	{"Sanchez", 468, F_PB, 11, 7.0, 2.8, 156},
	{"Patriot", 470, F_ON, 80, 11.7, 3.4, 170},
	{"Quad", 471, F_PB, 12, 4.6, 4.0, 119},
	{"Hermes", 474, F_ON, 45, 6.0, 3.9, 161},
	{"Sabre", 475, F_ON, 62, 9.9, 3.2, 187},
	{"ZR-350", 477, F_PB, 71, 11.7, 2.8, 202},
	{"Walton", 478, F_ON, 39, 5.9, 8.0, 127},
	{"Regina", 479, F_ON, 45, 6.0, 5.1, 151},
	{"Comet", 480, F_PB, 40, 9.5, 2.6, 199},
	{"Burrito", 482, F_PB, 74, 8.4, 3.8, 169},
	{"Rancher", 489, F_ON, 95, 14.4, 4.5, 151},
	{"FBI Rancher", 490, F_ON, 82, 13.7, 3.3, 170},
	{"Virgo", 491, F_ON, 53, 7.0, 4.8, 161},
	{"Greenwood", 492, F_PB, 57, 6.9, 4.1, 152},
	{"Sandking", 495, F_PB, 80, 9.7, 2.8, 191},
	{"Blista Compact", 496, F_PB, 45, 7.0, 2.9, 176},
	{"Boxville", 498, F_ON, 75, 8.1, 9.0, 116},
	{"Benson", 499, F_ON, 80, 7.0, 6.5, 133},
	{"Mesa", 500, F_PB, 65, 10.1, 4.4, 152},
	{"Hotring Racer A", 502, F_PB, 78, 14.7, 2.3, 232},
	{"Super GT", 506, F_PB, 58, 11.7, 2.7, 194},
	{"Elegant", 507, F_PB, 85, 8.4, 4.0, 179},
	{"Tanker", 514, F_ON, 757, 37.9, 4.5, 130},
	{"Roadtrain", 515, F_ON, 1100, 45.9, 4.4, 154},
	{"Nebula", 516, F_PB, 56, 7.2, 3.9, 170},
	{"Majestic", 517, F_PB, 50, 7.2, 3.9, 170},
	{"Buccaneer", 518, F_PB, 45, 7.7, 3.6, 178},
	{"FCR-900", 521, F_PB, 17, 7.8, 2.6, 174},
	{"NRG-500", 522, F_PB, 19, 8.0, 1.7, 191},
	{"Cement Truck", 524, F_ON, 380, 24.9, 5.5, 141},
	{"Towtruck", 525, F_ON, 75, 8.9, 4.0, 173},
	{"Fortune", 526, F_PB, 55, 8.0, 4.3, 171},
	{"Cadrona", 527, F_PB, 43, 6.9, 3.8, 161},
	{"Willard", 529, F_PB, 67, 7.0, 5.1, 161},
	{"Feltzer", 533, F_ON, 45, 8.7, 3.8, 180},
	{"Remington", 534, F_PB, 57, 9.1, 3.2, 182},
	{"Slamvan", 535, F_ON, 60, 8.9, 2.5, 171},
	{"Blade", 536, F_ON, 53, 8.7, 3.2, 187},
	{"Vincent", 540, F_ON, 70, 7.2, 4.6, 161},
	{"Bullet", 541, F_PB, 65, 12.2, 2.1, 219},
	{"Clover", 542, F_ON, 55, 7.9, 3.8, 178},
	{"Sadler", 543, F_ON, 40, 6.7, 4.0, 163},
	{"Hustler", 545, F_ON, 51, 6.9, 4.2, 159},
	{"Intruder", 546, F_PB, 64, 7.0, 4.9, 161},
	{"Primo", 547, F_PB, 55, 7.1, 4.7, 154},
	{"Tampa", 549, F_ON, 70, 6.9, 3.7, 166},
	{"Sunrise", 550, F_PB, 83, 7.0, 3.8, 157},
	{"Merit", 551, F_PB, 80, 7.7, 3.2, 170},
	{"Utility Van", 552, F_ON, 68, 6.8, 5.8, 131},
	{"Yosemite", 554, F_ON, 98, 15.3, 4.2, 156},
	{"Windsor", 555, F_PB, 40, 7.6, 3.2, 171},
	{"Uranus", 558, F_PB, 72, 8.1, 3.1, 169},
	{"Jester", 559, F_PB, 70, 9.8, 2.7, 192},
	{"Sultan", 560, F_PB, 71, 8.8, 2.3, 183},
	{"Stratum", 561, F_PB, 60, 7.6, 3.9, 166},
	{"Elegy", 562, F_PB, 63, 9.1, 2.7, 192},
	{"Flash", 565, F_PB, 40, 7.9, 2.6, 178},
	{"Tahoma", 566, F_PB, 65, 7.6, 3.1, 173},
	{"Savanna", 567, F_PB, 62, 9.0, 2.9, 187},
	{"Bandito", 568, F_PB, 30, 6.6, 2.5, 158},
	{"Dune", 573, F_ON, 400, 23.2, 4.0, 119},
	{"Broadway", 575, F_PB, 40, 7.1, 4.1, 171},
	{"Tornado", 576, F_ON, 55, 7.0, 3.9, 171},
	{"DFT-30", 578, F_ON, 550, 28.0, 5.1, 141},
	{"Huntley", 579, F_PB, 78, 13.2, 4.0, 171},
	{"Stafford", 580, F_PB, 40, 7.3, 3.8, 165},
	{"BF-400", 581, F_PB, 14, 6.1, 2.7, 164},
	{"Emperor", 585, F_PB, 50, 6.8, 4.5, 165},
	{"Wayfarer", 586, F_PB, 21, 6.2, 3.7, 156},
	{"Euros", 587, F_PB, 72, 8.2, 3.4, 178},
	{"Club", 589, F_PB, 40, 7.1, 3.4, 176},
	{"Police Car (LSPD)", 596, F_PB, 70, 8.2, 3.2, 190},
	{"Police Car (SFPD)", 597, F_PB, 70, 8.2, 3.1, 190},
	{"Police Car (LVPD)", 598, F_PB, 70, 8.2, 3.1, 190},
	{"Picador", 600, F_ON, 50, 5.9, 4.3, 163},
	{"Alpha", 602, F_PB, 60, 11.0, 3.1, 183},
	{"Phoenix", 603, F_PB, 58, 9.7, 3.0, 185}
};
//*********************************************************************STACJE BENZYNOWE
enum fs_data
{
	fs_id,
	fs_concern,
	Float:fs_dX,
	Float:fs_dY,
	Float:fs_dZ,
	Float:fs_pX,
	Float:fs_pY,
	Float:fs_pZ,
	Text3D:fs_dLabel,
	Text3D:fs_pLabel,
	fs_pickup
};

new fuel_stations[MAX_FUELSTATIONS][fs_data];
//*********************************************************************DANE FIRM KURIERSKICH
enum cd_data
{
	cd_cid,
	cd_name[16],
	cd_color,
	Float:cd_pX,
	Float:cd_pY,
	Float:cd_pZ,
	Float:cd_pX2,
	Float:cd_pY2,
	Float:cd_pZ2,
};


new courier_data[][cd_data] =
{
	{C_DHL, "DHL", 0xECEE00FF, 1662.9387,759.7028,10.8203, 1662.9518,770.3951,10.8203},
	{C_DPD, "DPD", 0xFB003FFF, 1612.0586,1071.3450,10.8650, 1612.3582,1086.3083,12.0320},
	{C_FEDEX, "FedEx", 0xB000FFFF, 2828.6831,960.0466,10.8680, 2818.8799,969.2146,10.8380},
	{C_INPOST, "InPost", 0xFDFF00FF, 954.6472,2087.8423,10.9190, 958.9664,2099.3855,10.9190},
	{C_TNT, "TNT", 0xFF8D00FF, 1611.0436,2380.8589,10.8203, 1622.7797,2387.6223,10.8398}
};
//*********************************************************************PYTANIA NA PRAWKO
#define qanswer_YES 1
#define qanswer_NO 0

enum qst_data
{
	qst_question[512],
	qst_answer
};

new driver_license_general[][qst_data] =
{
	{"Jeżeli widzisz pojazd uprzywilejowany (Straż pożarna, Karetka, Policja, etc.) bez włączonych syren masz obowiązek ułatwić przejazd?", qanswer_NO},
	{"Jesteś świadkiem wypadku. Czy masz obowiązek zostać na miejscu zdarzenia?", qanswer_YES},
	{"Poruszając się pojazdem silnikowym masz obowiązek posiadania włączonych świateł mijania?", qanswer_YES},
	{"Czy trójkąt ostrzegawczy jest obowiązkowym wyposażeniem pojazdu?", qanswer_YES},
	{"Czy koło zapasowe jest obowiązkowym wyposażeniem pojazdu?", qanswer_NO},
	{"Czy bez aktualnego przeglądu pojazdu masz prawo prowadzić tym pojazdem?", qanswer_NO},
	{"Jeżeli sygnalizator świetlny świeci się na czerwono a policjant kierujący ruchem pokazuje Ci że możesz wjechać na skrzyżowanie, posłuchasz się policjanta?", qanswer_YES},
	{"Czy na rondzie porusza się ruchem zgodnym z ruchem wskazówek zegara?", qanswer_NO},
	{"Jeżeli poruszasz się drogą jednopasmową z linią podwójną ciągłą to masz prawo wyprzedzić pojazd przed Tobą?", qanswer_NO},
	{"Widzisz leżącego poszkodowanego. Czy masz obowiązek zatrzymania się, udzielenia pierwszej pomocy?", qanswer_YES}
};

new driver_license_katB[][qst_data] =
{
	{"Czy samochodem osobowym możesz przewozić więcej niż 9 osób?", qanswer_NO},
	{"Czy masz prawo kierować samochodem o dmc (dopuszczalnej masie całkowitej) przekraczającą ponad 3,5 t wraz z przyczepą lekką?", qanswer_NO},
	{"Czy wolno Ci przewozić osoby trzecie poza kabiną pojazdu jeżeli pojazd ma miejsca siedzące oraz pasy?", qanswer_YES},
	{"Czy wolno Ci wykonać postój trwający mniej niż minute w zatoce dla autobusów przy przystanku?", qanswer_NO},
	{"Czy można rozmawiać przez telefon komórkowy korzystając z zestawu głośnomówiącego?", qanswer_YES}
};

new driver_license_katCE[][qst_data] =
{
	{"Czy jeżeli masz prawo jazdy kategorii CE masz prawo kierować autobusem?", qanswer_NO},
	{"Czy ładunek może wystawać od tylnej płaszczyzny obrysu pojazdu na odległość większą niż 2,5 m?", qanswer_YES},
	{"Czy na autostradach możesz poruszać się więcej niż 80 km/h?", qanswer_NO},
	{"Czy prawo jazdy kat. CE upoważnia Cię do kierowania ciągnika siodłowego wraz z naczepą?", qanswer_YES},
	{"Czy wolno Ci przewozić towar w naczepie nie przystosowanej do tego?", qanswer_NO}
};

new Float:driver_license_cp_katB[][3] =
{
	{1048.8434,1284.7640,10.3331}, //0
	{1065.0851,1284.7754,10.3331}, //1
	{1067.5521,1228.9968,10.3353}, //2
	{1054.7977,1228.9901,10.3220}, //3
	{1047.6781,1231.9066,10.3361}, //4
	{1045.7434,1239.0979,10.3366}, //5
	{1047.5757,1231.9452,10.3360}, //6
	{1057.6046,1228.9548,10.3361}, //7
	{1067.6561,1229.1794,10.3361}, //8
	{1083.5875,1232.4685,10.3361}, //9
	{1093.6886,1232.4425,11.7703}, //10
	{1103.1505,1232.4285,10.3354}, //11
	{1113.0341,1230.0933,10.3361}, //12
	{1125.4105,1234.9314,10.3361}, //13
	{1137.2576,1230.0742,10.3361}, //14
	{1145.4498,1233.7695,10.3332}, //15
	{1122.6053,1254.6522,10.3361}, //16
	{1127.9714,1273.6630,10.3337}, //17
	{1122.9897,1291.8944,10.3492}, //18
	{1127.9606,1308.5243,10.3503}, //19
	{1124.7434,1317.5250,10.3331}, //20
	{1106.6002,1314.1653,10.3331}, //21
	{1067.9779,1285.2286,10.3331}, //22
	{1038.9214,1285.0204,10.3330} //23
};

new Float:driver_license_cp_katCE[][3] =
{
	{1082.2151,1319.4048,10.3331}, //0
	{1082.1317,1336.1534,10.3331}, //1
	{1081.9895,1309.3164,10.3331}, //2
	{1099.4733,1306.6129,10.3331}, //3
	{1128.6235,1308.7565,10.3331}, //4
	{1121.9399,1293.0664,10.3331}, //5
	{1128.5009,1273.8759,10.3331}, //6
	{1121.8805,1254.0081,10.3331}, //7
	{1130.0321,1234.2168,10.3331}, //8
	{1147.9894,1243.5947,10.3331}, //9
	{1149.8336,1309.3525,10.3331}, //10
	{1131.0477,1336.4901,10.3331}, //11
	{1149.9591,1309.2313,10.3331}, //12
	{1130.4342,1318.7035,10.3331}, //13
	{1111.1698,1282.0009,10.3331}, //14
	{1040.6959,1278.1929,10.3331} //15
};
//*********************************************************************TOWARY
enum gds_data
{
	gds_name[24],
	gds_trailertype,
	bool:gds_adr
};
/*
435, 591 - STAŁE - 0
450 - SYPKIE - 1
584 - CIEKŁE - 2
unit:
*/
new goods[][gds_data] = 
{
	{"Brak", 0, false},
	{"Paczki kurierskie", 0, false},
	{"Szambo", 2, false},
	{"Mleko", 2, false},
	{"Olej napedowy", 2, true},
	{"Benzyna bezolowiowa", 2, true},
	{"Propan-butan", 2, true},
	{"Akumulatory", 0, true},
	{"Kwas siarkowy", 2, true},
	{"Jablka", 0, false},
	{"Pomarancze", 0, false},
	{"Banany", 0, false},
	{"Pomidory", 0, false},
	{"Cebula", 0, false},
	{"Ziemniaki", 0, false},
	{"Telefony", 0, false},
	{"Telewizory", 0, false},
	{"Tablety", 0, false},
	{"Zegarki", 0, false},
	{"Komputery", 0, false},
	{"Monitory", 0, false},
	{"Gry komputerowe", 0, false},
	{"Prety zbrojeniowe", 0, false},
	{"Rury", 0, false},
	{"Przewody miedziane", 0, false},
	{"Sedesy", 0, false},
	{"Farby", 0, false},
	{"Prezerwatywy", 0, false},
	{"Drzewo", 0, false},
	{"Wegiel", 1, false},
	{"Piasek kwarcowy", 1, false},
	{"Piasek wapienny", 1, false},
	{"Popiol wulkaniczny", 1, false},
	{"Piasek morski", 1, false},
	{"Piasek rzeczny", 1, false},
	{"Osad eoliczny", 1, false},
	{"Osad fluwioglacjalny", 1, false},
	{"Koci zwir", 1, false},
	{"Zwir ogrodowy", 1, false},
	{"Zwir morski", 1, false},
	{"Pszenica", 1, false},
	{"Zyto", 1, false},
	{"Owies", 1, false},
	{"Pszenzyto", 1, false},
	{"Czekolada", 0, false},
	{"Batony", 0, false},
	{"Cukierki", 0, false},
	{"Ubrania", 0, false}
};
//*********************************************************************STACJE RADIOWE
enum rs_data
{
	rs_title[32],
	rs_url[128]
};

new radio_stations[][rs_data] = 
{
	{"=> Radio HL", "http://play.highwaylife.pl:8000/listen.pls"},
	{"Radio Party", "http://s3.radioparty.pl:8005/listen.pls"},
	{"RADIO ZET", "http://zet-net-01.cdn.eurozet.pl:8400"},
	{"RMF FM", "http://217.74.72.11:8000/rmf_fm"},
	{"Radio RMF MAXXX", "http://217.74.72.10:8000/rmf_maxxx"},
	{"Zlote Przeboje", "http://mainstream.radioagora.pl:80/tuba9-1.mp3"},
	{"Planeta FM Warszawa", "http://pla-net-01.cdn.eurozet.pl:8700/"},
	{"RMF Classic", "http://217.74.72.10:8000/rmf_classic"},
	{"Roxy FM", "http://mainstream.radioagora.pl:80/tuba8-1.mp3"},
	{"Evropa 2", "http://icecast3.play.cz/evropa2-128.mp3"},
	{"TruckSim Radio", "http://radio.trucksimradio.com:8002/stream.mp3"},
	{"Vidin", "http://89.106.110.85:8000/"},
	{"Fresh", "http://193.108.24.21:8000/fresh"},
	{"FM+", "http://193.108.24.21:8000/fmplus"},
	{"Q-Music", "http://icecast-qmusic.cdp.triple-it.nl/Qmusic_be_live_96.mp3"},
	{"Frekvence 1", "http://icecast3.play.cz/frekvence1-128.mp3"},
	{"Country Radio", "http://icecast2.play.cz:8000/country64.mp3"},
	{"DR P7 Mix", "http://live-icy.gss.dr.dk:8000/A/A21H.mp3"},
	{"VLR", "http://streaming.fynskemedier.dk/vlr"},
	{"Radio 100FM", "http://onair.100fmlive.dk/100fm_live.mp3"},
	{"80s Music HotMixRadio", "http://streaming.hotmix-radio.net/hotmixradio-80-128.mp3"},
	{"Radio METAL", "http://94.23.40.70:8010/"},
	{"Dubplate.fm - Drum & Bass", "http://sc2.dubplate.fm:5000/DnB/192"},
	{"Dubplate.fm - Dubstep", "http://sc2.dubplate.fm:5000/dubstep/192"},
	{"Dubplate.fm - Urban Electro", "http://sc2.dubplate.fm:5000/Electro/192"},
	{"NRK P1 Hordaland", "http://lyd.nrk.no/nrk_radio_p1_hordaland_mp3_h"},
	{"Hitradio OE3", "http://mp3stream7.apasf.apa.at:8000/"},
	{"Studio B", "http://radio.studiob.rs:8004/"},
	{"Mint FM", "http://audiostream.rtl.be/mint"},
	{"Nation Radio Cardiff", "http://icy-e-04.sharp-stream.com/tcnation.mp3"},
	{"FFH Rock Frankfurt", "http://mp3.ffh.de/ffhchannels/hqrock.mp3"},
	{"KTFM Geneva", "http://broadcast.infomaniak.net:80/ktfm-high.mp3"},
	{"Rock n Pop Hamburg", "http://live96.106acht.de:80"},
	{"LeineHertz Hannover", "http://leinehertz01.htp.net:8000"},
	{"Virage Lyon", "http://broadcast.infomaniak.net/virageradio-high.mp3"},
	{"FM Musik Rock", "http://rock-high.rautemusik.fm/Musik.Rock"},
	{"Direct FM Metz", "http://stream.devclic.net:8200"},
	{"Oui FM Paris", "http://broadcast.infomaniak.ch/ouifm-high.mp3"},
	{"Rock Zone Prague", "http://icecast5.play.cz/rockzone128.mp3"},
	{"Top Music Strasbourg", "http://str0.creacast.com/topmusic1"},
	{"Radio Aligator Bratislava", "http://stream.aligator.sk:8000/aligator_192.mp3"},
	{"Real Radio XS Manchester", "http://ice-the.musicradio.com:80/RealXSManchesterMP3"},
	{"Fajn Radio", "http://ice.abradio.cz/fajn128.mp3"},
	{"NRK MP3", "http://lyd.nrk.no/nrk_radio_mp3_mp3_h"},
	{"BBC Radio Music", "http://bbcmedia.ic.llnwd.net/stream/bbcmedia_6music_mf_p"},
	{"SimLiveRadio", "http://stream.laut.fm/simliveradio"}
};
//*********************************************************************DANE PRZYSTANKÓW AUTOBUSOWYCH
enum bs_data
{
	bs_name[32],
	Float:bs_X,
	Float:bs_Y,
	Float:bs_Z
};
new bus_stations[][bs_data] = 
{
	{"[SPAWN] Hotel Highway Life", 1016.2000,1411.6714,10.8203},
	{"Służby Ratunkowe", 2279.1221,2315.4885,10.8203},
	{"Placówka Straży Granicznej", 998.7415,2365.8965,10.8203},
	{"Komisariat Policji", 2319.1338,1706.3093,10.8125},
	{"Baza Taxi", 2326.8044,624.2176,10.8203},
	{"Warsztat Samochodowy", 2574.2573,1064.2799,10.8203},
	{"AutoSzrot", -64.0105,1399.1449,9.7788},
	{"Centrum handlowe", 2065.9729,2107.3125,10.8203},
	{"Truck Centre", 2331.6436,1365.5282,10.8203},
	{"Salon Samochodowy", 2324.2668,964.9921,10.8203},
	{"Baza firmy FedEx", 2735.3625,826.9949,10.8984},
	{"Baza firmy DPD/DHL", 1554.9243,921.7714,10.8203},
	{"Baza firmy InPost", 1014.8918,2151.9375,10.8203},
	{"Baza firmy TNT", 1559.1919,2345.4587,10.8203},
	{"Park rozrywki", 2869.4724,-1933.6863,11.1084}
};
//*********************************************************************DANE PRZEJŚĆ GRANICZNYCH
enum bc_data
{
	bc_name[32],
	Float:bc_X,
	Float:bc_Y,
	Float:bc_Z,
	Text3D:bc_text3d,
	bc_mapicon,
	bc_count_waiting,
	bc_count_officers
};

new border_cross[][bc_data] =
{
	{"LV-San Fierro", 838.3120,682.5930,11.9060},
	{"LV-Los Santos", 1721.6676,441.6300,30.6516},
	{"LV-Bone County", 981.1153,2541.4529,10.8600}
};
//*********************************************************************SYSTEM KIERUNKÓW

enum eBO {
	bM, Float:bX, Float:bY, Float:bZ, Float:brX, Float:brY, Float:brZ
};

new BlinkOffset[][eBO] = {
	{400, -0.9001, 2.0490, -0.0965, -0.9605, -2.2404, -0.0965},
	{401, -0.9686, 2.5393, 0.0235, -0.9970, -2.2863, 0.0235},
	{402, -0.8788, 2.5160, -0.0565, -0.9208, -2.5936, 0.0435},
	{403, -1.005000,4.429998,-0.814999, -1.1904, -0.9415, 1.8389},
	{404, -0.7236, 2.1715, -0.0365, -0.7906, -2.7052, 0.0635},
	{405, -0.9127, 2.2766, -0.0565, -0.8723, -2.6526, -0.0565},
	{406, -2.2165, 4.9242, -0.0332, -2.0785, -5.2054, 0.5468},
	{407, -0.9887, 4.0622, -0.0913, -1.0141, -3.4034, -0.0913},
	{408, -0.9659, 4.7615, -0.2513, -0.8430, -3.9722, -0.5113},
	{409, -0.7859, 3.5522, -0.0313, -0.8027, -3.8228, -0.0313},
	{410, -0.825, 2.105, 0.0635, -0.8723, -2.1926, 0.1235},
	{411, -0.9405, 2.6710, -0.1825, -0.9636, -2.4525, 0.0825},
	{412, -0.8965, 2.6478, -0.0575, -0.9592, -3.4870, -0.1575},
	{413, -0.8669, 2.5464, -0.0913, -0.8209, -2.5829, 0.0687},
	{414, -0.8069, 2.7473, 0.0087, -0.9058, -3.2050, 0.1094},
	{415, -0.8738, 2.4866, -0.2357, -0.7792, -2.3501, 0.0450},
	{416, -0.8469, 2.9073, 0.0087, -1.0352, -3.5937, 1.4522},
	{417, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{418, -0.9511, 2.3820, -0.2357, -1.0081, -2.4904, -0.1557},
	{419, -1.0742, 2.3978, -0.1757, -0.8127, -2.8620, -0.1557},
	{420, -1.0142, 2.2978, -0.0157, -0.9637, -2.6744, 0.0043},
	{421, -0.9013, 2.5343, -0.1357, -0.5921, -2.9228, -0.1957},
	{422, -0.7813, 2.1543, -0.2657, -0.8985, -2.4349, -0.1057},
	{423, -0.7817, 2.2093, -0.0313, -0.8340, -2.1794, 0.0596},
	{424, -0.7350, 1.4505, 0.1087, -0.7062, -1.4778, 0.2996},
	{425, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{426, -1.0006, 2.3164, -0.0100, -0.9627, -2.6930, -0.0100},
	{427, -0.8728, 2.5856, 0.1887, -0.9831, -3.8383, -0.3495},
	{428, -0.8728, 2.5856, -0.2103, -0.9045, -2.8871, 1.2466},
	{429, -0.7942, 2.2846, -0.2500, -0.8397, -2.3849, -0.0070},
	{430, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{431, -0.9771, 5.8479, 0.3497, -1.0300, -5.7043, -0.1041},
	{432, -1.7168, 4.0330, 0.4497, -1.5830, -4.3414, 0.7039},
	{433, -1.2619, 3.7708, -0.2163, -1.2966, -4.6534, -0.1051},
	{434, -0.599999,1.895000,-0.139999, -0.4811, -1.9838, -0.0670},
	{435, 0.0000, 0.0000, 0.0000, -1.0697, -3.9690, -1.1053}, //trailer
	{436, -0.8495, 2.2519, -0.0070, -0.8948, -2.4838, 0.1130},
	{437, -1.1156, 5.5395, -0.2163, -0.9856, -5.3099, 1.6458},
	{438, -1.1128, 2.3675, -0.2870, -1.0992, -2.4601, -0.2870},
	{439, -0.8381, 2.3101, -0.1470, -0.8221, -2.6534, -0.1070},
	{440, -0.8270, 2.5573, -0.3173, -0.8676, -2.5376, -0.0149},
	{441, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{442, -1.0354, 2.8278, -0.1870, -1.0226, -3.0877, -0.1270},
	{443, -1.0610, 5.7528, -0.9573, -1.2388, -7.1392, -0.8250},
	{444, -0.9880, 2.7188, 0.6140, -1.0722, -3.0184, 0.7248},
	{445, -0.9590, 2.3460, -0.0840, -0.9773, -2.8049, -0.0840},
	{446, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{447, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{448,  -0.1992, -0.9229, -0.1270},
	{449, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{450,  0.0000, 0.0000, 0.0000, -1.0697, -3.9690, -1.1053}, //trailer
	{451, -0.9826, 1.9642, -0.1399, -0.8894, -2.3991, -0.0199},
	{452, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{453, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{454, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{455, -1.270000,3.690000,-0.069999, -1.3866, -4.5162, -0.7399},
	{456, -0.959999,3.300001,-0.039999, -1.3045, -4.6123, 0.4601},
	{457, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{458, -0.9513, 2.4197, -0.1399, -0.9703, -2.7779, 0.0201},
	{459, -0.8214, 2.5716, -0.1274, -0.8760, -2.5775, 0.1127},
	{460, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{461, -0.119999,0.799999,0.394999, -0.089999,-1.160000,0.375000},
	{462, 0.0000, 0.0000, 0.0000, -0.100000,0.514999,0.514999},
	{463, -0.2276, 0.7185, 0.3201, -0.1952, -1.0037, 0.1601},
	{464, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{465, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{466, -0.919999,2.600000,0.099999, -1.0201, -2.7994, 0.0401},
	{467, -0.599999,2.800001,-0.119999, -0.9401, -3.0594, 0.1601},
	{468, -0.129999,0.569999,0.319999, -0.050000,-0.940000,0.300000},
	{469, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{470, -1.0259, 2.1382, 0.2001, -1.0433, -2.5463, 0.1201},
	{471, -0.119999,0.225000,0.584999, -0.109999,-0.750000,0.189999},
	{472, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{473, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{474, -0.915000,2.610001,-0.019999, -0.9833, -2.7663, -0.0599},
	{475, -0.8681, 2.4086, -0.3399, -0.8632, -2.7629, -0.2399},
	{476, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{477, -0.8081, 2.6686, -0.1999, -0.9945, -2.6987, 0.0801},
	{478, -1.0938, 2.0255, 0.1001, -1.0579, -2.5378, -0.2799},
	{479, -0.9671, 2.4844, 0.0201, -0.9578, -2.7556, 0.0601},
	{480, -0.5897, 2.2607, -0.4399, -0.9183, -2.3388, -0.1399},
	{481, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{482, -0.8841, 2.4094, -0.3399, -0.8685, -2.5676, 0.0201},
	{483, -0.7770, 2.6235, -0.0199, -0.6709, -2.7712, -0.1999},
	{484,  0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{485, -0.6104, 1.7180, 0.2201, -0.7074, -1.3681, 0.1201},
	{486, 0.0000, 0.0000, 0.0000, -0.5919, -3.2353, 0.9601},
	{487, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{488, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{489, -1.1024, 2.5796, 0.0401, -1.1261, -2.6473, 0.1601},
	{490, -1.0971, 3.1462, 0.0401, -1.1327, -3.1055, 0.1601},
	{491, -0.8495, 2.5284, -0.0799, -0.8870, -2.7776, 0.0001},
	{492, -0.7905, 2.4656, -0.0599, -0.9075, -2.8130, 0.0001},
	{493, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{494, -0.8513, 2.3630, -0.2199, -0.8275, -2.8485, 0.1401},
	{495, -1.0909, 2.3818, 0.0001, -1.1540, -2.1156, -0.0399},
	{496, -0.9219, 2.1787, 0.0401, -0.7095, -2.1087, 0.0801},
	{497, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000, 0.0000},
	{498, -0.8915, 3.0670, 0.2201, -0.9740, -3.0460, 0.3601},
	{499, -0.7725, 2.4576, -0.1999, -1.1318, -3.4186, 0.1401},
	{500, -0.9152, 1.9097, -0.0355, -0.7552, -1.9266, -0.0355},
	{501, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{502, -0.8723, 2.5986, -0.1770, -0.749999,-2.685000,-0.019999},
	{503, -0.8579, 2.3582, -0.0213, 0.0, 0.0, 0.0},
	{504, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{505, -1.1068, 2.5744, 0.0086, -1.1365, -2.6250, 0.1679},
	{506, -0.7672, 2.2106, -0.3185, -0.9113, -2.3474, -0.0273},
	{507, -1.1143, 2.6057, -0.0456, -1.1410, -2.9714, -0.0456},
	{508, -0.7012, 3.0199, -0.6678, -1.3807, -3.3356, 1.2628},
	{509, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{510, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{511, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{512, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{513, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{514, -1.2341, 4.2204, 0.0806, -0.419999,-5.059998,-0.594999},
	{515, -1.4241, 4.4811, -0.7354, -1.2973, -4.8274, -0.8974},
	{516, -0.9512, 2.7208, -0.0543, -0.9926, -2.7809, -0.0348},
	{517, -0.9401, 2.7868, -0.0726, -1.0208, -2.7461, -0.1324},
	{518, -0.9166, 2.6548, -0.0487, -1.0124, -2.8219, -0.0487}, //fake
	{519, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{520, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{521, -0.109999,0.854999,0.410000, -0.089999,-1.134999,0.410000},
	{522, -0.109999,0.834999,0.349999, -0.034999,-1.134999,0.499999},
	{523, -0.2607, 0.6038, 0.2881, -0.1973, -0.9958, 0.0638},
	{524, -0.9279, 3.6538, -0.0473, -1.3003, -3.9309, -1.0661}, //fake back
	{525, -0.8576, 2.9431, 0.1425, -1.0428, -2.9851, -0.1486}, //fake back
	{526, -0.9421, 2.3087, -0.1128, -0.9559, -2.2882, -0.0411},
	{527, -0.9351, 2.4078, -0.0242, -0.9825, -2.2344, 0.0844},
	{528, -0.8783, 2.5102, -0.1526, -0.8133, -2.5965, -0.3237}, //fake back
	{529, -1.0177, 2.5256, 0.0698, -1.0505, -2.5713, 0.2047},
	{530, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{531, -0.4216, 1.5030, -0.1191, -0.5225, -1.0517, 0.4484}, //fake
	{532, -4.0331, 3.9619, -0.9118, -1.5976, -0.3739, 0.4484}, //fake!
	{533, -0.9410, 2.3774, 0.0985, -0.9852, -2.4663, -0.0020},
	{534, -1.0159, 2.9278, -0.1698, -0.8236, -2.7548, -0.0574},
	{535, -0.8265, 2.5014, -0.2084, -0.9267, -2.6058, -0.1784},
	{536, -0.8577, 2.3943, -0.1248, -0.8736, -3.0999, -0.0900},
	{537, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{538, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{539, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{540, -0.9827, 2.5810, -0.1248, -1.0597, -2.7121, -0.0842},
	{541, -0.6055, 2.3378, -0.2108, -0.7826, -2.1992, 0.0913},
	{542, -0.9712, 2.6252, -0.0064, -0.8281, -2.9729, -0.0577},
	{543, -0.8414, 2.2904, 0.0719, -0.9831, -2.6214, -0.0116}, //fake front
	{544, -0.7346, 3.5720, 0.0200, -0.8597, -3.2242, -0.5918},
	{545, -0.4372, 1.6776, -0.0400, -0.7955, -2.0453, -0.2888},
	{546, -1.009999,2.610000,0.019999, -1.0580, -2.6948, 0.0719},
	{547, -0.9582, 2.5222, 0.0271, -0.9937, -2.5915, 0.0719},
	{548, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{549, -0.9264, 2.4914, 0.0271, -0.9070, -2.5802, 0.0271},
	{550, -1.0477, 2.5642, -0.1807, -1.0302, -2.6549, -0.1297},
	{551, -0.9334, 2.6344, -0.0448, -0.9785, -3.0524, 0.0366},
	{552, -0.8757, 3.0634, 0.3600, -0.9933, -2.9119, 0.4752},
	{553, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{554, -0.9409, 2.5345, 0.0600, -1.1112, -2.8095, 0.0651},
	{555, -0.754999,2.185000,-0.009999, -0.680000,-2.465000,-0.109999},
	{556, -0.9686, 2.5396, 0.5800, -1.1128, -2.8895, 0.7691},
	{557, -0.9886, 2.4796, 0.7000, -1.0904, -2.7699, 0.6871},
	{558, -0.9452, 2.0854, 0.0836, -0.9187, -2.4047, 0.3185},
	{559, -0.9037, 2.4333, -0.0168, -0.8819, -2.2910, 0.1482},
	{560, -0.9347, 2.5097, -0.2644, -0.9639, -2.2337, 0.1259},
	{561, -0.9157, 2.5754, -0.0857, -0.9317, -2.5444, -0.0191},
	{562, -0.9299, 2.3759, 0.0201, -0.8575, -2.2773, 0.1659},
	{563, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{564, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{565, -0.8503, 2.0545, 0.0346, -0.9249, -1.9224, 0.0816},
	{566, -0.9539, 2.7226, 0.0346, -0.9506, -2.9199, 0.0346},
	{567, -0.9942, 2.9212, -0.1543, -1.0077, -2.9164, -0.1543},
	{568, -0.2962, 2.0729, -0.0171, -0.2384, -1.2180, 0.0720},
	{569, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{570, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{571, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{572, -0.3095, 0.7291, -0.0971, -0.4318, -0.8940, -0.0510},
	{573, -0.7949, 3.0624, -0.3371, -0.8727, -3.0917, -0.4540},
	{574, -0.4348, 1.6912, -0.2171, -0.4277, -1.1358, -0.2069},
	{575, -0.9483, 2.3252, 0.1334, -0.9173, -2.7359, -0.0291},
	{576, -0.9948, 2.4505, 0.1883, -0.9983, -3.1357, -0.0291},
	{577, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{578, -1.0478, 4.3687, -0.1800, -1.1188, -5.3472, -0.5099},
	{579, -1.0598, 2.3634, 0.1013, -1.0873, -2.7596, 0.1013},
	{580, -0.7970, 2.6313, -0.2429, -1.0776, -2.8302, 0.1013},
	{581, -0.194999,0.595000,0.329999, -0.1975, -1.0375, 0.3448},
	{582, -0.8583, 2.4404, -0.0571, -0.9214, -3.3625, 0.0521},
	{583, -0.5225, 1.3799, 0.2429, -0.5486, -1.5684, 0.2462},
	{584, 0.0, 0.0, 0.0, -1.0452, -4.3338, -0.7298}, //trailer
	{585, -1.0068, 2.7905, 0.0907, -0.9760, -3.0160, 0.2088},
	{586, -0.2872, 0.5383, 0.2009, -0.1703, -1.3533, 0.2784},
	{587, -1.0236, 2.1415, -0.2834, -1.0832, -2.4851, 0.1047},
	{588, -1.0116, 3.3590, 0.1029, -1.0679, -3.9639, -0.3029},
	{589, -0.8107, 2.3905, 0.1834, -0.9605, -2.2799, 0.3761},
	{590, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{591, 0.0, 0.0, 0.0, -1.0590, -3.9902, -1.0809}, //trailer
	{592, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{593, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{594, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{595, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{596, -1.0419, 2.2929, -0.0255, -1.0332, -2.6951, 0.0005},
	{597, -1.0419, 2.2929, -0.0255, -1.0332, -2.6951, 0.0005},
	{598, -1.0423, 2.3495, 0.0600, -1.0326, -2.6930, 0.0600},
	{599, -1.0837, 2.5663, 0.0301, -1.1267, -2.6290, 0.1451},
	{600, -0.8782, 2.6525, -0.0344, -1.0586, -2.6696, 0.0596},
	{601, -0.8094, 3.0084, 0.5429, -0.9321, -3.0808, 0.9071},
	{602, -1.0297, 2.0487, -0.0543, -0.8907, -2.5334, -0.3228},
	{603, -0.9069, 2.6672, -0.1335, -0.8647, -2.5991, -0.1335},
	{604, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{605, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{606, 0.0, 0.0, 0.0, -0.5702, -1.5842, 0.7956}, //trailer
	{607, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{608, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{609, -0.8972, 3.0244, 0.2629, -0.9349, -2.9809, 0.2791},
	{610, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
	{611, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
	//END GTA CARS
};

//skrypt wezwan
enum call_data
{
	call_fraction,
	call_type,
	call_calleruid,
	call_timestamp,
	call_status,
	call_acceptby_puid,
	Float:call_X,
	Float:call_Y,
	Float:call_Z,
	call_text[32]
};
new calls[MAX_CALLS][call_data];
//kurier

new courier_clients_skins[] = {1, 2, 3, 4, 5, 6, 7, 9, 12, 13, 14, 17, 20, 21, 22, 23, 24, 25, 28, 29, 30, 31, 34, 35, 36, 43, 44, 46, 47, 48};
new Float:courier_clients[MAX_COURIERCLIENTS][4] = 
{
	{1610.7600,2102.4194,10.6719,244.6783}, //0
	{1626.9764,2097.1091,10.6719,144.4106}, //1
	{1625.5544,2072.3010,10.6719,130.9372}, //2
	{1610.3668,2063.7383,10.6719,285.7253}, //3
	{1610.5352,2036.3750,10.8203,249.0650}, //4
	{1652.7833,2005.4678,10.8203,52.6031}, //5
	{1618.1210,2004.7039,10.8203,5.6026}, //6
	{1559.6147,2001.5209,10.8203,291.6552}, //7
	{1472.4786,1964.7570,10.8203,359.6258}, //8
	{1435.4309,1965.9906,10.8203,4.0125}, //9
	{1379.5688,1974.7649,10.8203,276.2784}, //10
	{1395.2864,1996.8551,10.8203,91.1201}, //11
	{1379.6503,2029.6248,10.8203,272.2051}, //12
	{1365.2734,2045.6318,10.8203,3.3860}, //13
	{1306.1118,2036.3826,10.8203,95.5068}, //14
	{1305.4481,2001.8486,10.8203,94.2301}, //15
	{1324.8020,1945.7126,10.8203,353.6726}, //16
	{1967.3500,2636.6570,10.8203,349.2391}, //17
	{1926.2521,2635.3679,10.8203,16.1393}, //18
	{1752.6377,2721.2070,10.8203,197.8744}, //19
	{1559.4790,2828.9600,11.1289,221.0378}, //20
	{1679.2144,2758.1716,10.8203,232.0046}, //21
	{1983.1281,2749.9741,10.8203,193.4641}, //22
	{2535.9236,700.8869,10.8203,168.0604}, //23
	{2531.4980,765.5314,10.8203,4.4988}, //24
	{2628.2170,765.1439,10.8203,7.0056}, //25
	{2673.7454,765.2010,10.8203,17.6590}, //26
	{2434.8958,683.1171,10.8203,92.2096}, //27
	{2403.4031,705.2496,10.8203,22.9623}, //28
	{2337.0647,705.7963,10.8203,11.3688}, //29
	{2280.4937,695.4026,10.8203,258.2544}, //30
	{2234.3423,641.2158,10.8203,168.6403}, //31
	{2170.2732,641.1578,10.8203,181.4871}, //32
	{2113.9092,665.6382,10.8203,353.7986}, //33
	{2099.7043,680.9870,10.8203,180.8604}, //34
	{2063.5244,681.3528,10.8203,173.3403}, //35
	{2071.5671,664.2859,10.8203,26.0724}, //36
	{2038.3311,664.5057,10.8203,11.9723}, //37
	{2020.5175,680.8217,10.8203,175.5338}, //38
	{1995.3129,698.7741,10.8203,68.9995}, //39
	{1980.0388,719.7011,10.8203,287.6848}, //40
	{1979.4767,742.3331,10.8203,264.1847}, //41
	{1923.7517,765.6221,10.8203,6.9823}, //42
	{1943.0736,766.5512,10.8203,10.7424}, //43
	{1860.0283,713.8798,10.8203,257.6280}, //44
	{1859.5533,688.0621,10.8203,272.0415}, //45
	{1859.9067,665.6580,10.8203,283.3216}, //46
	{1875.3531,657.6515,10.8203,48.6328}, //47
	{1099.5254,2006.5477,10.8203,273.2949}, //48
	{1099.3177,1972.3217,10.8203,254.4946}, //49
	{1084.9460,1961.0082,10.8203,180.2339}, //50
	{1026.6270,1960.8358,10.8281,180.8606}, //51
	{1015.6096,1978.4618,10.8203,86.5464}, //52
	{998.7974,1971.8093,10.8281,267.0281}, //53
	{1000.1250,1927.4795,10.8203,263.5814}, //54
	{1015.7772,1899.9567,10.8203,111.2999}, //55
	{1015.9513,1880.7811,10.8203,98.4531}, //56
	{999.7227,1874.6069,10.8203,256.0612}, //57
	{2840.1692,2246.1174,10.8203,262.0614}, //58
	{2839.3970,2161.2681,10.8203,234.8012}, //59
	{2616.1824,1979.3615,10.8203,89.7033}, //60
	{2147.2375,1654.1179,10.8203,55.5497}, //61
	{2034.0027,1624.7058,10.8369,269.2216}, //62
	{2082.8503,1487.4287,10.8203,83.7265} //63
};


new Float:taxi_targets[MAX_TAXITARGET][3] = 
{
	{1034.5325,-1043.4225,31.2827}, //0
	{1258.7345,-1088.2163,26.3442}, //1
	{1191.4565,-1315.7170,13.1255}, //2
	{1200.0532,-1547.0125,13.1099}, //3
	{1033.5569,-1645.1079,13.1099}, //4
	{1146.0593,-1645.5734,13.5084}, //5
	{1393.1204,-1793.4047,13.1099}, //6
	{1492.7552,-1736.1648,13.1099}, //7
	{1533.5043,-1649.1355,13.1099}, //8
	{1478.8557,-1596.2981,13.1099}, //9
	{1661.9099,-1575.5852,13.1177}, //10
	{1738.8822,-1444.7793,13.0859}, //11
	{1718.7225,-1367.6145,13.1099}, //12
	{1574.9088,-1294.4211,16.9486}, //13
	{1450.7373,-1262.5469,13.1030}, //14
	{1529.1234,-1164.7596,23.6333}, //15
	{1782.5123,-1167.2003,23.3860}, //16
	{1926.0558,-1131.7546,24.6931}, //17
	{2036.5118,-1070.0909,24.3290}, //18
	{2075.7998,-1193.5907,23.4163}, //19
	{2147.2122,-1224.7830,23.5454}, //20
	{2208.5569,-1465.6804,23.5423}, //21
	{2129.3811,-1748.4006,13.1302}, //22
	{2085.6826,-1917.5428,13.1099}, //23
	{2162.2075,-1890.4490,13.0362}, //24
	{2309.8101,-1923.6508,13.1423}, //25
	{2362.4468,-1968.4437,13.0329}, //26
	{2478.8342,-2013.6000,13.0135}, //27
	{2417.6719,-1779.1523,13.1177}, //28
	{2364.5117,-1728.4628,13.1099}, //29
	{2425.4934,-1654.9886,13.1099}, //30
	{2261.1484,-1655.0493,14.8944}, //31
	{2220.2659,-2138.1926,13.0752}, //32
	{2299.0085,-2320.4531,13.1093}, //33
	{2570.6384,-2394.3823,13.1971}, //34
	{2757.1992,-2453.5239,13.2104}, //35
	{2488.7100,-2591.0442,13.1990}, //36
	{2221.1418,-2582.6641,13.1194}, //37
	{2015.9751,-2162.5327,13.1099}, //38
	{1787.7656,-2108.8274,13.1099}, //39
	{1697.8617,-2116.8315,13.1099}, //40
	{1654.5913,-2257.6951,13.0693}, //41
	{1718.7527,-2323.2329,13.1100}, //42
	{1661.1841,-2249.9446,-3.1186}, //43
	{1710.6658,-2315.3618,-3.1107}, //44
	{921.3527,-1701.7957,13.0952}, //45
	{823.4813,-1622.7804,13.1095}, //46
	{814.1714,-1736.5348,13.1099}, //47
	{697.0798,-1743.4722,13.1059}, //48
	{830.7730,-1787.9414,13.4676}, //49
	{405.3415,-1776.4231,5.0263}, //50
	{366.2228,-2041.1973,7.3990}, //51
	{351.9330,-1641.4163,32.6735}, //52
	{344.3956,-1523.8170,32.9411}, //53
	{338.3650,-1448.2573,34.0216}, //54
	{226.4119,-1440.7531,12.8671}, //55
	{461.2168,-1321.7395,14.9126}, //56
	{622.1959,-1255.5935,17.3034}, //57
	{641.3913,-1488.9486,14.3158}, //58
	{747.2596,-1409.5555,13.0963}, //59
	{801.3194,-1343.9463,13.1099}, //60
	{938.6271,-1236.5408,16.2014}, //61
	{999.9196,-1316.1973,13.1101}, //62
	{1066.4701,-1324.2458,13.0988}, //63
	{2307.3374,-1185.9240,25.0808}, //64
	{2375.0500,-1201.5806,27.1571}, //65
	{2447.0535,-1367.8057,23.5516}, //66
	{2515.6013,-1400.1439,28.0866}, //67
	{2567.1099,-1348.8492,35.8483}, //68
	{2487.1780,-1508.2832,23.5552}, //69
	{2646.7466,-1687.8518,10.5060}, //70
	{2807.4878,-1661.2589,10.4224}, //71
	{2864.9626,-1510.2654,10.5923}, //72
	{2848.7727,-1214.6753,23.1503}, //73
	{2638.8276,-1086.0392,69.1802}, //74
	{2718.8198,-1126.3488,69.1411}, //75
	{2612.4497,-1179.9690,63.4979}, //76
	{2518.4714,-1043.8673,69.1411}, //77
	{2268.2983,-1066.9896,48.0726}, //78
	{2163.2444,-1000.6824,62.5200}, //79
	{1160.0623,-893.2902,42.3004}, //80
	{869.2271,-866.7726,77.2101}, //81
	{156.8047,-1740.8276,4.6023}, //82
	{-202.4885,-306.6256,1.1568}, //83
	{91.6549,-215.4562,1.1633}, //84
	{236.7128,-145.5001,1.1568}, //85
	{159.5291,-75.8102,1.1568}, //86
	{236.8291,13.3363,2.1568}, //87
	{332.9767,81.7003,3.3331}, //88
	{293.3311,-67.9395,1.1568}, //89
	{286.7432,-169.4111,1.1566}, //90
	{683.5107,-481.1342,15.9146}, //91
	{645.7420,-574.4722,15.9146}, //92
	{787.7062,-574.5002,15.9075}, //93
	{1323.2131,229.7909,19.1333}, //94
	{1397.7355,282.0685,19.1334}, //95
	{1210.3790,307.6820,19.1333}, //96
	{2263.6387,-94.3259,26.0630}, //97
	{2397.9021,26.3685,26.0622}, //98
	{2529.9675,22.1970,26.0669}, //99
	{2249.2937,145.6178,26.0630}, //100
	{2330.2625,977.1321,10.3990}, //101
	{1924.3199,937.1890,10.3989}, //102
	{2038.4572,1013.7628,10.3989}, //103
	{2423.4878,1125.9657,10.3990}, //104
	{2574.2373,1189.3270,10.3990}, //105
	{2603.4219,1097.9047,10.3990}, //106
	{2511.7654,949.3154,10.3990}, //107
	{2618.1670,769.2615,10.3987}, //108
	{2723.1948,884.2184,10.4771}, //109
	{2651.4224,689.2905,10.3990}, //110
	{2336.2222,717.1107,10.3989}, //111
	{2065.0356,669.3643,10.3989}, //112
	{1871.4021,688.5347,10.3989}, //113
	{1718.8419,1478.9797,10.3990}, //114
	{1651.3805,1739.1188,10.3990}, //115
	{1491.3146,1932.4904,10.3990}, //116
	{1475.9349,2057.1667,10.3990}, //117
	{1563.4329,2354.4524,10.3990}, //118
	{1432.6499,2608.9075,10.3990}, //119
	{1298.0195,2547.9155,10.3894}, //120
	{1646.2534,2585.8086,10.3993}, //121
	{1463.7095,2776.0591,10.3990}, //122
	{1616.5293,2817.7000,10.3990}, //123
	{2023.4084,2438.4612,10.3989}, //124
	{2338.4121,2169.2429,10.4591}, //125
	{2217.1882,1897.1541,10.3989}, //126
	{2059.1631,2026.0555,10.3989}, //127
	{2118.5068,2181.0005,10.3990}, //128
	{2144.1213,1839.2122,10.3989}, //129
	{2076.2581,1466.3118,10.3990}, //130
	{2038.4509,1541.3678,10.3989}, //131
	{2038.4502,1342.2142,10.3990}, //132
	{2164.4133,1189.2133,10.3989}, //133
	{2793.7139,1309.2476,10.4771}, //134
	{2551.3135,1448.7227,10.3987}, //135
	{2282.2986,1369.2968,10.3990}, //136
	{1003.5170,1742.1770,10.5005}, //137
	{1011.4367,1393.7604,10.3990}, //138
	{1011.3374,2268.4507,10.4028}, //139
	{961.8881,2397.1814,10.3989}, //140
	{1779.5519,2057.2349,10.5542}, //141
	{1991.8319,2287.2537,10.3987} //142
};


new Float:load_place_van[MAX_VANLOADS][3] =
{
	{1517.7004,1608.7489,10.8534}, //CENTRUM LOGISTYCZNE LV
	{1517.7004,1608.7489,10.8534}, //CENTRUM LOGISTYCZNE LV
	{1517.7004,1608.7489,10.8534}, //CENTRUM LOGISTYCZNE LV
	{1392.8064,785.6771,11.2866}, //0
	{667.3697,1694.9059,7.5228}, //1
	{111.5922,2571.2002,18.3426}, //2
	{929.3419,863.6801,13.8463}, //3
	{584.8080,4607.7822,14.5148}, //4
	{1424.8346,1066.8901,10.7676}, //5
	{2706.1260,905.3890,10.9904}, //6
	{2823.5481,2602.6738,11.2570}, //7
	{2478.4116,1931.2307,10.7617}, //8
	{1049.9628,2087.6130,11.2570}, //9
	{1022.8768,2247.5195,11.2568}, //10
	{1064.3900,2342.8074,11.2567}, //11
	{-1728.1355,46.9815,3.9882}, //12
	{-2129.7666,-247.9613,35.7599}, //13
	{-2109.0623,-254.9280,35.7570}, //14
	{-2135.6116,-126.2752,35.7570}, //15
	{-1892.9648,-1671.5494,23.4503}, //16
	{-1818.5626,-1630.1061,23.4508}, //17
	{-2094.4739,-2245.8911,31.1169}, //18
	{-1968.9126,-2434.1707,31.0797}, //19
	{-517.6155,-537.9527,25.9727}, //20
	{-602.3802,-539.8087,25.9726}, //21
	{-1001.1240,-741.6266,32.4445}, //22
	{-1217.0383,-470.0351,14.6328}, //23
	{-1243.1287,-470.3362,14.6325}, //24
	{-1237.7555,-420.7771,14.6326}, //25
	{120.7339,-299.5957,2.0148}, //26
	{164.5427,-22.2513,2.0147}, //27
	{-116.8918,-322.7766,1.8625}, //28
	{1105.6914,-335.2610,74.4360}, //29
	{2461.1704,-2116.1025,13.9866}, //30
	{2567.5442,-2417.8623,14.0857}, //31
	{2776.5581,-2493.8899,14.1002}, //32
	{2738.7593,-2466.0266,14.1056}, //33
	{2249.2581,-2017.8804,13.9827}, //34
	{2185.2405,-2261.6904,13.8680}, //35
	{830.5028,-1207.6089,17.4131}, //36
	{979.5724,-1261.5923,16.7070}, //37
	{1110.8417,-1329.6334,13.6310}, //38
	{1239.2427,181.5942,20.3185}, //39
	{-564.7028,-1065.2612,26.1087}, //40
	{-2287.0134,2280.9055,5.4052}, //41
	{-2431.3960,2292.9531,5.4210}, //42
	{-4105.1880,431.4483,5.3315}, //43
	{2583.7422,4329.5205,71.4393}, //44
	{5984.7363,2162.8318,27.3803}, //45
	{4744.5508,906.8589,4.1560}, //46
	{-1476.1053,2655.0417,55.8359}, //47
	{-755.7404,-5778.6084,5.6326},//48
	{-1768.6942,-7216.3350,5.6126},//49
	{-4226.3594,-10545.1230,53.3042},//50
	{-3215.4375,-3430.0608,32.5674},//51
	{-4698.9512,-1354.8127,35.5427},//52
	{4406.7637,3845.7603,50.9907},//53
	{5257.5781,4662.1187,51.0187},//54
	{5395.2729,6934.4756,5.8848},//55
	{7976.7559,5572.5137,110.8554},//56
	{5609.5278,6453.9302,50.9584},//57
	{4472.7993,7572.8081,59.8115}//58
};

new Float:prisons[][] =
{
	{2445.3503,1737.1833,1.1662}, // prison1
	{2445.5894,1733.8551,1.1662}, // prison2
	{2439.5964,1728.7334,1.1662}, // prison3
	{2435.2390,1728.0210,1.1662}, // prison4
	{2435.0764,1723.6165,1.1662}, // prison5
	{2435.3752,1727.0598,-2.3138}, // prison6
	{2436.0967,1723.0331,-2.3138} // prison7
};

enum gfv_data
{
	gfv_goodid,
	gfv_loadplace_sourceid,
	gfv_loadplace_targetid,
	Float:gfv_distance,
	gfv_amount,
	gfv_score,
	gfv_price
};
new goods_for_vans[MAX_GOODSFORVANS][gfv_data];

new all_zone_names[][32] =
{
	{"Nieznane"},
	{"The Big Ear"},
	{"Aldea Malvada"},
	{"Angel Pine"},
	{"Arco del Oeste"},
	{"Avispa Country Club"},
	{"Back o Beyond"},
	{"Battery Point"},
	{"Bayside"},
	{"Bayside Marina"},
	{"Beacon Hill"},
	{"Blackfield"},
	{"Blackfield Chapel"},
	{"Blackfield Section"},
	{"Blueberry"},
	{"Blueberry Acres"},
	{"Caligula's Palace"},
	{"Calton Heights"},
	{"Chinatown"},
	{"City Hall"},
	{"Come-A-Lot"},
	{"Commerce"},
	{"Conference Center"},
	{"Cranberry Station"},
	{"Creek"},
	{"Dillimore"},
	{"Doherty"},
	{"Downtown"},
	{"Downtown Los Santos"},
	{"East Beach"},
	{"East Los Santos"},
	{"Easter Basin"},
	{"Easter Bay Airport"},
	{"Easter Bay Chemical"},
	{"Castillo del Diablo"},
	{"El Corona"},
	{"El Quebrados"},
	{"Esplanade East"},
	{"Fallen Tree"},
	{"Fallow Bridge"},
	{"Fern Ridge"},
	{"Financial"},
	{"Fisher's Lagoon"},
	{"Flint Intersection"},
	{"Flint Range"},
	{"Fort Carson"},
	{"Foster Valley"},
	{"Frederick Bridge"},
	{"Gant Bridge"},
	{"Ganton"},
	{"Garcia"},
	{"Garver Bridge"},
	{"Glen Park"},
	{"Green Palms"},
	{"Greenglass College"},
	{"Hampton Barns"},
	{"Hankypanky Point"},
	{"Harry Gold Parkway"},
	{"Hashbury"},
	{"Hilltop Farm"},
	{"Hunter Quarry"},
	{"Idlewood"},
	{"Jefferson"},
	{"Julius Thruway East"},
	{"Julius Thruway North"},
	{"Julius Thruway South"},
	{"Julius Thruway West"},
	{"Juniper Hill"},
	{"Juniper Hollow"},
	{"KACC Military Fuels"},
	{"Kincaid Bridge"},
	{"King's"},
	{"LVA Freight Depot"},
	{"Las Barrancas"},
	{"Las Brujas"},
	{"Las Colinas"},
	{"Las Payasadas"},
	{"Las Venturas Airport"},
	{"Last Dime Motel"},
	{"Leafy Hollow"},
	{"Liberty City"},
	{"Lil' Probe Inn"},
	{"Linden Side"},
	{"Linden Station"},
	{"Little Mexico"},
	{"Los Flores"},
	{"LS International"},
	{"Marina"},
	{"Market Station"},
	{"Martin Bridge"},
	{"Missionary Hill"},
	{"Montgomery"},
	{"Montgomery Section"},
	{"Mulholland"},
	{"Mulholland Section"},
	{"North Rock"},
	{"Ocean Docks"},
	{"Ocean Flats"},
	{"Octane Springs"},
	{"Old Venturas Strip"},
	{"Palisades"},
	{"Palomino Creek"},
	{"Paradiso"},
	{"Pershing Square"},
	{"Pilgrim"},
	{"Pilson Intersection"},
	{"Pirates in Men's Pants"},
	{"Playa del Seville"},
	{"Prickle Pine"},
	{"Queens"},
	{"Randolph Ind. Estate"},
	{"Redsands East"},
	{"Redsands West"},
	{"Regular Tom"},
	{"Richman"},
	{"Robada Section"},
	{"Roca Escalante"},
	{"Rockshore East"},
	{"Rockshore West"},
	{"Rodeo"},
	{"Royal Casino"},
	{"San Andreas Sound"},
	{"Santa Flora"},
	{"Santa Maria Beach"},
	{"Shady Cabin"},
	{"Shady Creeks"},
	{"Sobell Rail Yards"},
	{"Spinybed"},
	{"Starfish Casino"},
	{"Temple"},
	{"The Camel's Toe"},
	{"The Clown's Pocket"},
	{"The Emerald Isle"},
	{"The Farm"},
	{"Four Dragons Casino"},
	{"The High Roller"},
	{"The Mako Span"},
	{"The Panopticon"},
	{"The Pink Swan"},
	{"The Sherman Dam"},
	{"The Strip"},
	{"The Visage"},
	{"Unity Station"},
	{"Valle Ocultado"},
	{"Verdant Bluffs"},
	{"Verdant Meadows"},
	{"Verona Beach"},
	{"Vinewood"},
	{"Whitewood Estates"},
	{"Willowfield"},
	{"Yellow Bell Station"},
	{"Los Santos"},
	{"Las Venturas"},
	{"Bone County"},
	{"Tierra Robada"},
	{"San Fierro"},
	{"Red County"},
	{"Flint County"},
	{"Whetstone"},
	{"North Hills Village"},
	{"Icytown"},
	{"SF Island Port"},
	{"Rockvale"},
	{"Denver"},
	{"Whales Factory"},
	{"Villegreen"},
	{"Oil Province"},
	{"Pencil Factory"},
	{"Deerfield"},
	{"Norwood"},
	{"Leesville"},
	{"Reedley City"},
	{"Skyland"},
	{"Port Langlois"},
	{"ECC Factory"}
};

enum opt_locations_data
{
	opt_name[64],
	bool:opt_ban
};

new opt_locations_ban[MAX_OPTLOCATIONS][opt_locations_data] =
{
	{"North Hills Village", true},
	{"Icytown", true},
	{"SF Island Port", true},
	{"Rockvale", true},
	{"Denver", true},
	{"Whales Factory", true},
	{"Villegreen", true},
	{"Oil Province", true},
	{"Pencil Factory", true},
	{"Deerfield", true},
	{"Norwood", true},
	{"Leesville", true},
	{"Reedley City", true},
	{"Skyland", true},
	{"Port Langlois", true},
	{"ECC Factory", true}
};

new PlayerColors[] = {
0xFF8C13FF,0xC715FFFF,0x20B2AAFF,0xDC143CFF,0x6495EDFF,0xf0e68cFF,0x778899FF,0xFF1493FF,0xF4A460FF,0xEE82EEFF,
0xFFD720FF,0x8b4513FF,0x4949A0FF,0x148b8bFF,0x14ff7fFF,0x556b2fFF,0x0FD9FAFF,0x10DC29FF,0x534081FF,0x0495CDFF,
0xEF6CE8FF,0xBD34DAFF,0x247C1BFF,0x0C8E5DFF,0x635B03FF,0xCB7ED3FF,0x65ADEBFF,0x5C1ACCFF,0xF2F853FF,0x11F891FF,
0x7B39AAFF,0x53EB10FF,0x54137DFF,0x275222FF,0xF09F5BFF,0x3D0A4FFF,0x22F767FF,0xD63034FF,0x9A6980FF,0xDFB935FF,
0x3793FAFF,0x90239DFF,0xE9AB2FFF,0xAF2FF3FF,0x057F94FF,0xB98519FF,0x388EEAFF,0x028151FF,0xA55043FF,0x0DE018FF,
0x93AB1CFF,0x95BAF0FF,0x369976FF,0x18F71FFF,0x4B8987FF,0x491B9EFF,0x829DC7FF,0xBCE635FF,0xCEA6DFFF,0x20D4ADFF,
0x2D74FDFF,0x3C1C0DFF,0x12D6D4FF,0x48C000FF,0x2A51E2FF,0xE3AC12FF,0xFC42A8FF,0x2FC827FF,0x1A30BFFF,0xB740C2FF,
0x42ACF5FF,0x2FD9DEFF,0xFAFB71FF,0x05D1CDFF,0xC471BDFF,0x94436EFF,0xC1F7ECFF,0xCE79EEFF,0xBD1EF2FF,0x93B7E4FF,
0x3214AAFF,0x184D3BFF,0xAE4B99FF,0x7E49D7FF,0x4C436EFF,0xFA24CCFF,0xCE76BEFF,0xA04E0AFF,0x9F945CFF,0xDCDE3DFF,
0x10C9C5FF,0x70524DFF,0x0BE472FF,0x8A2CD7FF,0x6152C2FF,0xCF72A9FF,0xE59338FF,0xEEDC2DFF,0xD8C762FF,0x3FE65CFF
};

new VehicleColoursTableRGBA[256] = {
// The existing colours from San Andreas
0x000000FF, 0xF5F5F5FF, 0x2A77A1FF, 0x840410FF, 0x263739FF, 0x86446EFF, 0xD78E10FF, 0x4C75B7FF, 0xBDBEC6FF, 0x5E7072FF,
0x46597AFF, 0x656A79FF, 0x5D7E8DFF, 0x58595AFF, 0xD6DAD6FF, 0x9CA1A3FF, 0x335F3FFF, 0x730E1AFF, 0x7B0A2AFF, 0x9F9D94FF,
0x3B4E78FF, 0x732E3EFF, 0x691E3BFF, 0x96918CFF, 0x515459FF, 0x3F3E45FF, 0xA5A9A7FF, 0x635C5AFF, 0x3D4A68FF, 0x979592FF,
0x421F21FF, 0x5F272BFF, 0x8494ABFF, 0x767B7CFF, 0x646464FF, 0x5A5752FF, 0x252527FF, 0x2D3A35FF, 0x93A396FF, 0x6D7A88FF,
0x221918FF, 0x6F675FFF, 0x7C1C2AFF, 0x5F0A15FF, 0x193826FF, 0x5D1B20FF, 0x9D9872FF, 0x7A7560FF, 0x989586FF, 0xADB0B0FF,
0x848988FF, 0x304F45FF, 0x4D6268FF, 0x162248FF, 0x272F4BFF, 0x7D6256FF, 0x9EA4ABFF, 0x9C8D71FF, 0x6D1822FF, 0x4E6881FF,
0x9C9C98FF, 0x917347FF, 0x661C26FF, 0x949D9FFF, 0xA4A7A5FF, 0x8E8C46FF, 0x341A1EFF, 0x6A7A8CFF, 0xAAAD8EFF, 0xAB988FFF,
0x851F2EFF, 0x6F8297FF, 0x585853FF, 0x9AA790FF, 0x601A23FF, 0x20202CFF, 0xA4A096FF, 0xAA9D84FF, 0x78222BFF, 0x0E316DFF,
0x722A3FFF, 0x7B715EFF, 0x741D28FF, 0x1E2E32FF, 0x4D322FFF, 0x7C1B44FF, 0x2E5B20FF, 0x395A83FF, 0x6D2837FF, 0xA7A28FFF,
0xAFB1B1FF, 0x364155FF, 0x6D6C6EFF, 0x0F6A89FF, 0x204B6BFF, 0x2B3E57FF, 0x9B9F9DFF, 0x6C8495FF, 0x4D8495FF, 0xAE9B7FFF,
0x406C8FFF, 0x1F253BFF, 0xAB9276FF, 0x134573FF, 0x96816CFF, 0x64686AFF, 0x105082FF, 0xA19983FF, 0x385694FF, 0x525661FF,
0x7F6956FF, 0x8C929AFF, 0x596E87FF, 0x473532FF, 0x44624FFF, 0x730A27FF, 0x223457FF, 0x640D1BFF, 0xA3ADC6FF, 0x695853FF,
0x9B8B80FF, 0x620B1CFF, 0x5B5D5EFF, 0x624428FF, 0x731827FF, 0x1B376DFF, 0xEC6AAEFF, 0x000000FF,
// SA-MP extended colours (0.3x)
0x177517FF, 0x210606FF, 0x125478FF, 0x452A0DFF, 0x571E1EFF, 0x010701FF, 0x25225AFF, 0x2C89AAFF, 0x8A4DBDFF, 0x35963AFF,
0xB7B7B7FF, 0x464C8DFF, 0x84888CFF, 0x817867FF, 0x817A26FF, 0x6A506FFF, 0x583E6FFF, 0x8CB972FF, 0x824F78FF, 0x6D276AFF,
0x1E1D13FF, 0x1E1306FF, 0x1F2518FF, 0x2C4531FF, 0x1E4C99FF, 0x2E5F43FF, 0x1E9948FF, 0x1E9999FF, 0x999976FF, 0x7C8499FF,
0x992E1EFF, 0x2C1E08FF, 0x142407FF, 0x993E4DFF, 0x1E4C99FF, 0x198181FF, 0x1A292AFF, 0x16616FFF, 0x1B6687FF, 0x6C3F99FF,
0x481A0EFF, 0x7A7399FF, 0x746D99FF, 0x53387EFF, 0x222407FF, 0x3E190CFF, 0x46210EFF, 0x991E1EFF, 0x8D4C8DFF, 0x805B80FF,
0x7B3E7EFF, 0x3C1737FF, 0x733517FF, 0x781818FF, 0x83341AFF, 0x8E2F1CFF, 0x7E3E53FF, 0x7C6D7CFF, 0x020C02FF, 0x072407FF,
0x163012FF, 0x16301BFF, 0x642B4FFF, 0x368452FF, 0x999590FF, 0x818D96FF, 0x99991EFF, 0x7F994CFF, 0x839292FF, 0x788222FF,
0x2B3C99FF, 0x3A3A0BFF, 0x8A794EFF, 0x0E1F49FF, 0x15371CFF, 0x15273AFF, 0x375775FF, 0x060820FF, 0x071326FF, 0x20394BFF,
0x2C5089FF, 0x15426CFF, 0x103250FF, 0x241663FF, 0x692015FF, 0x8C8D94FF, 0x516013FF, 0x090F02FF, 0x8C573AFF, 0x52888EFF,
0x995C52FF, 0x99581EFF, 0x993A63FF, 0x998F4EFF, 0x99311EFF, 0x0D1842FF, 0x521E1EFF, 0x42420DFF, 0x4C991EFF, 0x082A1DFF,
0x96821DFF, 0x197F19FF, 0x3B141FFF, 0x745217FF, 0x893F8DFF, 0x7E1A6CFF, 0x0B370BFF, 0x27450DFF, 0x071F24FF, 0x784573FF,
0x8A653AFF, 0x732617FF, 0x319490FF, 0x56941DFF, 0x59163DFF, 0x1B8A2FFF, 0x38160BFF, 0x041804FF, 0x355D8EFF, 0x2E3F5BFF,
0x561A28FF, 0x4E0E27FF, 0x706C67FF, 0x3B3E42FF, 0x2E2D33FF, 0x7B7E7DFF, 0x4A4442FF, 0x28344EFF
};

new pozar_kolejka = -1;
new pozar_timestamp;
new Float:potencjalne_pozary[][3] = 
{
	{1333.345581, 1151.705810, 17.007658},
	{2380.593750, 2750.363037, 18.827117},
	{2173.425048, 958.225036, 21.304615},
	{2308.093994, 77.607757, 38.408256},
	{795.062194, -579.889587, 24.373626},
	{1801.646606, -1872.206054, 22.039306},
	{2464.985107, -1748.942016, 17.496665},
	{2300.543457, -6.690934, 35.713710},
	{1276.632934, 312.540679, 34.286693},
	{-93.971763, 1365.491455, 18.903539},
	{-1819.864257, 2056.230957, 26.418092},
	{-796.146423, 1606.129150, 35.793724},
	{105.492980, 1102.027221, 20.064886},
	{-360.532043, 1509.195434, 84.009063},
	{2348.585937, -1371.133422, 32.915466},
	{284.743927, -1876.754028, 8.765626},
	{-2416.073242, -2194.876953, 43.258029},
	{-1912.034545, 216.710479, 47.278453},
	{-210.804122, 1048.934814, 26.994983},
	{-196.871261, -314.245147, 11.969979},
	{2061.0862,2089.9219,13.7538}, // 
	{1432.8832,2654.2283,11.3926}, // 
	{2145.9309,2830.9675,10.8203}, //
	{2020.4613,1401.3103,10.8284}, // 
	{1340.6400,1154.1293,15.3489}, // 
	{1971.7125,2469.5134,11.1782}, // 
	{2586.8472,1086.0394,15.2874}, // 
	{2620.0757,711.8897,14.5002}, // 
	{1373.9138,745.7894,10.8500}, //
	{-113.3552,1123.5752,19.7422}, // 
	{696.4929,1973.3308,10.1195}, // 
	{-224.8855,2706.8481,62.6875}, // 
	{-1272.0785,2712.5017,50.2663}, // 
	{-2434.0515,2350.1863,4.9688}, // 
	{-1946.8052,2370.3359,54.5078}, // 
	{-1219.7212,1825.7076,46.3984}, // 
	{-862.9556,1517.9724,26.7226}, // 
	{-691.6915,928.2551,13.6293}, // 
	{598.8765,1233.4364,11.7188}, // 
	{787.0618,1680.5153,8.1822}, // 
	{4320.7817,3955.6599,60.8335}, //
	{5455.0571,6407.5859,50.9382}, // 
	{609.5995,4622.6255,18.1588}, // 
	{2613.4946,4550.2534,70.9799}, // 
	{4432.4854,6171.8540,68.5240}, // 
	{4499.0918,7433.3291,80.9610}, // 
	{5346.1763,6838.8149,8.8345}, // 
	{5246.2495,4640.5825,61.2838}, // 
	{5957.1377,1998.2258,30.2617}, // 
	{-4705.7842,-1458.1155,38.6362}, // 
	{-796.7584,-5811.3569,10.3848}, // 
	{-1773.1177,-7227.1387,15.6746}, // 
	{1920.7131,146.1747,36.6235}, // 
	{2268.2585,-76.7768,26.5781}, // 
	{2321.7583,61.2923,26.4857}, //  
	{1320.8741,281.3718,27.8034}, // 
	{743.8615,248.3541,27.2593}, // 
	{89.9454,-197.3106,1.5012}, // 
	{311.7499,-47.3085,1.5781}, // 
	{683.7734,-466.6424,22.5705}, // 
	{369.6354,-2062.8171,14.6510}, // 
	{927.1344,-2218.1694,13.2255}, // 
	{1937.4762,-2124.6670,17.6977}, //
	{2142.8962,-1822.3196,18.8687}, //
	{2783.8423,-1942.8354,17.3203}, //
	{2930.9919,-684.0094,11.0461}, //
	{2574.9138,-957.7354,81.3551}, //
	{1932.7336,-1117.7615,26.4531}, //
	{1035.8350,-1348.9253,18.5141}, //
	{1118.4974,-2035.2159,78.2109}, //
	{1133.0377,-981.9915,49.1817}, // 
	{-94.4853,-1570.1204,2.6172}, //
	{-579.4631,-1485.6819,14.3511}, //
	{-576.2715,-1065.3944,25.6620}, //
	{-1439.7675,-1542.9431,101.7578}, //
	{-1896.1355,-1640.0026,25.0391}, //
	{-2084.6985,-2450.9258,30.6250}, //
	{-2816.5288,-1525.3186,146.7734}, //
	{-649.8575,-2833.4280,54.5582}, //
	{-1116.7424,-1643.4747,76.3672}, //
	{-2541.7100,-667.6867,147.9063}, //
	{-2651.4658,-22.4748,6.1328}, //
	{-2594.8325,818.1938,49.9844}, //
	{-1720.1923,1353.1802,16.3513}, //
	{-1729.5045,-51.4497,3.5547}, //
	{-2181.6609,-223.7508,42.3126}, //
	{-1789.7146,1202.2520,25.1250} //
};

new Float:camera_login[][6] =
{
	{1244.5100,1165.9414,116.5085, 1141.9705,1351.5137,71.0417}, 
	{1469.0399,1508.3601,121.6069, 1543.6028,1579.8256,50.6891},
	{3217.9858,2021.9155,30.1773, 5868.9419,2021.8522,60.1586}, //0
	{5925.7686,1920.6985,58.0253, 6028.8057,2008.3899,58.0253}, 
	{4515.1025,1201.6455,141.4627, 4626.3604,1068.4850,72.1841},
	{1535.4270,612.9023,67.3016, 1634.7612,697.1132,34.5322},
	{1558.3301,918.3551,43.4817, 1630.0278,992.5309,30.1773},
	{2899.3467,788.9421,83.9157, 2878.0161,897.0706,40.1619},
	{2462.0530,655.8744,48.2779, 2393.2974,600.2028,23.9523},
	{2557.6973,1016.3351,44.9235, 2601.4331,1064.1272,27.8715},
	{2171.9915,1975.6935,67.6941, 2089.0669,2030.3380,33.6957},
	{1863.2831,870.7649,43.6844, 1786.3291,669.1796,37.3066}, 
	{906.1940,2374.1060,37.3066, 990.5618,2433.8103,23.7799}, 
	{860.3969,1934.6046,34.4115, 906.8116,1892.4509,21.8039}, 
	{1172.3945,959.1709,29.8629, 1262.6045,856.3644,29.8629}, 
	{2858.7080,-939.3900,97.8031, 2917.3950,-767.7763,24.2435}, 
	{-589.6865,-2861.3284,69.4003, -658.6490,-2807.6943,61.8631}, 
	{2258.7244,1809.6323,37.9126, 2363.3293,1752.9954,21.3817}
};

new Float:custom_shops[][3] = 
{
	{1375.4474,776.2133,10.8750}, //0
	{1375.3840,772.2883,10.8850}, //1
	{1375.3225,768.4142,10.8850}, //2
	{1375.3677,764.5587,10.8850}, //3
	{1375.2839,760.5523,10.8850}, //4
	{3183.9734,-1982.8903,21.4675}, //0
	{3183.1157,-1991.2333,21.4675}, //1
	{3175.7537,-1990.6407,21.4675}, //2
	{3174.0151,-1985.5851,21.4675}//3
};

new faq_data[][512] = 
{
	"Jak zacząć rozgrywkę?",
	"Wyrób dokumenty w urzędzie (Za Hotelem Highway Life (spawn)).\nZatrudnij się w jednej z firm kurierskich, aby zarobić na pierwszy prywatny pojazd. ",
	"Jak dołączyć do jednej z firm kurierskich?",
	"Udaj się do najbliższego przystanku (ikona BS na minimapie) i wybierz\njedną z baz firm kurieskich i wsiądź do dowolnego busa. ",
	"Gdzie zrobić prawo jazdy?",
	"Prawo jazdy kat. B i CE należy zrobić w WORDzie, znajdującym się na\nprzeciwko Spawnu (Przystanek: Hotel Highway Life).",
	"Gdzie kupić pierwszy prywatny pojazd?",
	"Busy i ciężarówki należy kupić w Centrum Ciężarówek (Przystanek: Truck Centre), natomiast\npojazdy osobowe w Salonie Samochodowym (Przystanek: Salon Samochodowy).",
	"W jaki sposób naprawić awarię pojazdu? ",
	"Należy wezwać Pomoc Drogową lub osobiście udać\nsię do warsztatu (Czerwony klucz na mapie).",
	"Mam wypadek. Co teraz? ",
	"Jeśli na serwerze jest dostępne Ratownictwo to na pewno już do Ciebie\njedzie z pomocą. Jednak gdy, nie ma służb ratunkowych należy odczekać pewien czas.",
	"Co oznacza ta zielona belka w HUD'zie?",
	"Jest to pasek staminy którą można uzupełnić poprzez jedzenie\nbądź picie. Osiągnięcie zera procent powoduję utratę HP do 10%.",
	"Jak mogę uzupełnić HP?",
	"Musisz udać się do sklepu i kupić coś do jedzenia lub picia albo poprosić o pomoc Pogotowie.",
	"Jak dostać się do frakcji? ",
	"Jeśli wybrana przez nas frakcja prowadzi rekrutację, należy napisać\npodanie w odpowiednim dziale na forum. ",
	"Moje podanie zostało odrzucone. Co teraz? ",
	"Możesz spróbować ponownie w następnej rekrutacji lub spróbować\nsił w innej z frakcji dostępnych na serwerze. ",
	"Czy mogę kupić rangę VIP? ",
	"Informacje na temat rangi VIP sprawdź pod komendą /pomoc -> Strefa PREMIUM",
	"Jak mogę zostać Adminem lub Mapperem?",
	"Nie prowadzimy otwartej rekrutacji do Administracji. Jeśli będziemy kogoś\nposzukiwać pojawi się odpowiednia informacja na forum. ",
	"Dostałem kicka/bana. Dlaczego? ",
	"Prawdopodobnie złamałeś regulamin serwera. Jeśli dostałeś bana permamantnego\nmożesz apelować na forum. Jeśli jest to ban czasowy musisz poczekać do jego końca.",
	"Jaki tryb rozgrywki obowiązuje na serwerze HighwayLife?",
	"Truck & LiteRP, czyli okrojona wersja RolePlay'u, wcielasz się w rolę\nkierowcy, który w przyszłości może dołączyć do jednej z frakcji. Gracz zobowiązany jest\ndo odgrywania prostych akcji RP, nie muszą być one skomplikowane, ale muszą nadawać odrobinę realistyki rozgrywki."
};

new ann_scm[][130] = 
{
	"Zapraszamy na nasze forum: "COL_RED"https://forum.highwaylife.pl"COL_GREY".",
	"Zapraszamy na nasz serwer TeamSpeak3: "COL_RED"ts.highwaylife.pl"COL_GREY".",
	"Nie wiesz od czego zacząć? Podejmij pracę w firmie kurierskiej.",
	"Po rozłączeniu się, masz 5 minut aby z powrotem wrócić na serwer. Inaczej system RELOG nie wczyta ostatniej sytuacji.",
	"Zlecenia dla kierowców są zmieniane co "COL_RED"24 godziny"COL_GREY".",
	"Rotacja aut w salonie samochodów jest zmieniana co "COL_RED"24 godziny"COL_GREY".",
	"System RELOG nie zapisuje postępów, kiedy pracujesz w pracy dorywczej (np.: w firmie kurierskiej).",
	"Ceny samochodów zostały wyliczone na podstawie ich parametrów.",
	"Pojazdy frakcyjne nie ulegają "COL_RED"awarii"COL_GREY".",
	"System RELOG nie za każdym razem jest w stanie wczytać ostatnią sytuacje.",
	"Skorzystaj z przystanków autobusowych, aby przemieszczać się do kluczowych miejsc na mapie.",
	"Zapinaj "COL_RED"/pasy"COL_GREY" a system wypadków potraktuje Cię bardziej łaskawie.",
	"Przystanki autobusowe są zaznaczone na mapie ikoną "COL_RED"BS"COL_GREY".",
	"Aby podnieść przedmiot leżący na ziemi, użyj komendy "COL_RED"/podnies"COL_GREY".",
	"Im droższy samochód, tym droższa jego eksploatacja.",
	"W centrum handlowym LV możesz zregenerować staminę "COL_RED"za darmo"COL_GREY".",
	"W Binco możesz zmienić skin i zakupić akcesoria. Sklepy Binco są oznaczone na mapie ikoną "COL_RED"T-Shirt"COL_GREY".",
	"Widzisz cheatera? Użyj "COL_RED"/report"COL_GREY" aby zgłosić ten fakt administracji.",
	"W sklepach zakupisz produkty, które zregenerują Ci staminę. Sklepy oznaczone są białą ikoną "COL_RED"S"COL_GREY".",
	"Ceny paliw na stacjach są zróżnicowane i zmieniane co "COL_RED"24 godziny"COL_GREY".",
	"Możesz sam skonfigurować swoją niestandardową stacje radiową. Użyj panelu "COL_RED"/radio"COL_GREY".",
	"Za pomocą klawisza "COL_RED"N"COL_GREY" możesz szybko przełączać stacje radiowe w aucie.",
	"Użyj "COL_RED"/eq"COL_GREY" aby zarządzać przedmiotami w swoim ekwipunku.",
	"Jesteś w potrzebie? Wezwij odpowiednie służby za pomocą komendy "COL_RED"/wezwij"COL_GREY".",
	"Mała liczba klatek? Zredukuj ilość wyświetlanych obiektów za pomocą komendy "COL_RED"/lag"COL_GREY".",
	"Praca w firmie kurierskiej jest opłacalna tylko do "COL_GREEN""COURIER_MONEYTIME"$"COL_GREY".",
	"Jeśli Twój pojazd nie został przeparkowany z miejsca niedozwolonego do parkowania, pojazd usunie się po respawnie.",
	"Czy wiesz, że "COL_RED"/wezwania"COL_GREY" działają nawet nie będąc na /duty? Możesz je tylko przeglądać.",
	"Skorzystaj z komendy "COL_RED"/karoseria"COL_GREY", jeśli nie ma pomocy drogowej na służbie a chcesz naprawić karoserię.",
	"Używanie nitro zwiększa spalanie.",
	"Pojazdy firmowe nie mogą zostać odspawnowane.",
	"Korzystaj z czatu głosowego na serwerze. Plugin do pobrania na naszym "COL_RED"forum"COL_GREY".",
	"Lista animacji: "COL_RED"/anim"COL_GREY". Nazwe animacji możesz wpisywać bezpośrednio.",
	"Aby włączyć neony, włącz światła.",
	"Chcesz pożyczyć komuś pojazd? Użyj "COL_RED"/kluczyki"COL_GREY".",
	"Dostarcz towar pod wpływem alkoholu, aby dostać bonus!",
	"Chcesz się oderwać od monotonni? Odwiedź "COL_LIME"park rozrywki"COL_GREY" oznaczony kostką do gry na minimapie!",
	"Uprawnienia ADR uzyskasz w urzędzie miasta.",
	"Zapraszamy na nasz serwer DISCORD: "COL_RED"https://discord.gg/E9eNFAV"COL_GREY".",
	"Na długość napadu wpływa: ilość paliwa do wypompowania oraz odległości zdarzenia od komisariatu.",
	"Pieniądze za /przejazd i /mandat trafiają na konto frakcji.",
	"Dodatkowe lokacje są wybiórczo aktywowane dla naczep freelancer. Ma to na celu skupienie graczy na tak sporej mapie.",
	"Im PD dalej naprawi pojazd od swojej bazy, tym wieksza kwota wpłynie na konto frakcji.",
	"Mozesz schodzic z duty frakcji w pickupie firmowym i odwrotnie :)",
	"Sprawdź nasze radio Highway Life: "COL_RED"/audycja"COL_GREY".",
	"Nie wiesz gdzie co jest? Użyj "COL_RED"/gps"COL_GREY".",
	"Chcesz powędkować? Kup wędkę i znajdź miejsce oznaczone "COL_RED"ikoną kotwicy"COL_GREY".",
	"Ryby mozesz spozyc lub sprzedac dla handlarza w Bayside."
};
new ann_scm_td[][130] = 
{
	"Zapraszamy na nasze forum: https://forum.highwaylife.pl",
	"Zapraszamy na nasz serwer TeamSpeak3: ts.highwaylife.pl",
	"Nie wiesz od czego zaczac? Podejmij prace w firmie kurierskiej",
	"Po rozlaczeniu sie, masz 5 minut aby z powrotem wrocic na serwer. Inaczej system RELOG nie wczyta ostatniej sytuacji",
	"Zlecenia dla kierowcow sa zmieniane co 24 godziny",
	"Rotacja aut w salonie samochodow jest zmieniana co 24 godziny",
	"System RELOG nie zapisuje postepow, kiedy pracujesz w pracy dorywczej (np.: w firmie kurierskiej)",
	"Ceny samochodow zostaly wyliczone na podstawie ich parametrow",
	"Pojazdy frakcyjne nie ulegaja awarii",
	"System RELOG nie za kazdym razem jest w stanie wczytac ostatnia sytuacje",
	"Skorzystaj z przystankow autobusowych, aby przemieszczac sie do kluczowych miejsc na mapie",
	"Zapinaj /pasy a system wypadkow potraktuje Cie bardziej laskawie",
	"Przystanki autobusowe sa zaznaczone na mapie ikona BS",
	"Aby podniesc przedmiot lezacy na ziemi, uzyj komendy /podnies",
	"Im drozszy samochod, tym drozsza jego eksploatacja",
	"W centrum handlowym LV mozesz zregenerowac stamine za darmo",
	"W Binco mozesz zmienic skin i zakupic akcesoria. Sklepy Binco sa oznaczone na mapie ikona T-Shirt",
	"Widzisz cheatera? Uzyj /report aby zglosic ten fakt administracji",
	"W sklepach zakupisz produkty, ktore zregeneruja Ci stamine. Sklepy oznaczone sa biala ikona S",
	"Ceny paliw na stacjach sa zroznicowane i zmieniane co 24 godziny",
	"Mozesz sam skonfigurowac swoja niestandardowa stacje radiowa. Uzyj panelu /radio",
	"Za pomoca klawisza N mozesz szybko przelaczac stacje radiowe w aucie",
	"Uzyj /eq aby zarzadzac przedmiotami w swoim ekwipunku",
	"Jestes w potrzebie? Wezwij odpowiednie sluzby za pomoca komendy /wezwij",
	"Mala liczba klatek? Zredukuj ilosc wyswietlanych obiektow za pomoca komendy /lag",
	"Praca w firmie kurierskiej jest oplacalna tylko do "COURIER_MONEYTIME"$",
	"Jesli Twoj pojazd nie zostal przeparkowany z miejsca niedozwolonego do parkowania, pojazd usunie sie po respawnie",
	"Czy wiesz, ze /wezwania dzialaja nawet nie bedac na /duty? Mozesz je tylko przegladac",
	"Skorzystaj z komendy /karoseria, jesli nie ma pomocy drogowej na sluzbie a chcesz naprawic karoserie",
	"Uzywanie nitro zwieksza spalanie",
	"Pojazdy firmowe nie moga zostac odspawnowane",
	"Korzystaj z czatu glosowego na serwerze. Plugin do pobrania na naszym forum",
	"Lista animacji: /anim. Nazwe animacji mozesz wpisywac bezposrednio",
	"Aby wlaczyc neony, wlacz swiatla",
	"Chcesz pozyczyc komus pojazd? Uzyj /kluczyki",
	"Dostarcz towar pod wplywem alkoholu, aby dostac bonus!",
	"Chcesz sie oderwac od monotonni? Odwiedz park rozrywki oznaczony kostka do gry na minimapie!",
	"Uprawnienia ADR uzyskasz w urzedzie miasta",
	"Zapraszamy na nasz serwer DISCORD: https://discord.gg/E9eNFAV",
	"Na dlugosc napadu wplywa: ilosc paliwa do wypompowania oraz odleglosci zdarzenia od komisariatu",
	"Pieniadze za /przejazd i /mandat trafiaja na konto frakcji",
	"Dodatkowe lokacje sa wybiorczo aktywowane dla naczep freelancer. Ma to na celu skupienie graczy na tak sporej mapie",
	"Im PD dalej naprawi pojazd od swojej bazy, tym wieksza kwota wplynie na konto frakcji",
	"Mozesz schodzic z duty frakcji w pickupie firmowym i odwrotnie :)",
	"Sprawdz nasze radio Highway Life: /audycja",
	"Nie wiesz gdzie co jest? Uzyj /gps",
	"Chcesz powedkowac? Kup wedke i znajdz miejsce oznaczone ikona kotwicy",
	"Ryby mozesz spozyc lub sprzedac dla handlarza w Bayside"
};

new Float:house_customint[][3] =
{
	{2304.4126,1894.8914,1704.4391}, //0
	{2321.4238,1775.7487,1704.4391}, //1
	{2305.1384,1646.1643,1704.4391}, //2
	{2320.1895,1526.8749,1705.9999}, //3
	{2305.4048,1414.3376,1704.3865}, //4
	{2458.8369,1382.7587,1704.3763}, //5
	{2578.1392,1382.5780,1704.3832}, //6
	{2686.7759,1366.2920,1704.7334}, //7
	{2802.5750,1382.4805,1704.3732}, //8
	{2941.7605,1366.4919,1705.4138} //9
};


enum house_data
{
	h_id,
	h_owneruid,
	h_renteruid,
	Float:h_extX,
	Float:h_extY,
	Float:h_extZ,
	Float:h_intX,
	Float:h_intY,
	Float:h_intZ,
	Float:h_ex_intX,
	Float:h_ex_intY,
	Float:h_ex_intZ,
	h_interior,
	h_customint,
	h_polygoncount,
	h_polygonid,
	h_price,
	h_expire,
	h_open,
	Text3D:h_text3dext,
	Text3D:h_text3dint,
	h_pickup,
	h_icon
};

new house[MAX_HOUSES][house_data];

//pachołki

enum cone_data
{
	cn_object,
	cn_fraction,
	Float:cn_X,
	Float:cn_Y,
	Float:cn_Z,
	Text3D:cn_text3d
}

new cones[MAX_CONES][cone_data];
//konary
new fallTree_query = -1;
new fallTree_createTime;

enum  falltree_info
{
	bool: ft_isfall,
	ft_hp,
	ft_objectid,
	Text3D:ft_label
};

new fallTree_data[MAX_FALLTREE][falltree_info];


new Float:fallTree_position[MAX_FALLTREE][4] =
{
	{1716.9685,1604.3519,10.0156,71.7073},//przy lv
	{1704.5104,2594.9685,10.6719,236.4922}, //0
	{1318.9279,2713.7195,10.6719,141.8412}, //1
	{1003.9630,1634.2250,10.7734,333.2896}, //2
	{2075.9514,2036.3209,10.9103,296.0260}, //3
	{1728.0592,541.3954,28.5504,231.4787}, //4
	{1658.0555,830.5906,6.7639,358.3799}, //5
	{1292.9806,903.4744,6.8125,71.0739}, //6
	{1145.7733,884.2483,10.7389,223.3554}, //7
	{1706.0718,1931.2930,10.6719,290.4561}, //8
	{1566.2740,2347.7231,10.6719,299.5663}, //9
	{1625.0737,2450.8892,6.8396,352.2068}, //10
	{2294.7029,2630.8979,6.7500,147.5982}, //11
	{2235.5405,1191.5388,10.7186,353.4602}, //12
	{1564.7203,749.8864,10.6719,329.3333}, //13
	{862.0563,2466.7332,29.7087,94.3545}, //14
	{1203.1212,1835.9458,6.7422,273.2461}, //15
	{465.2927,741.4120,4.8909,154.4916}, //16
	{193.3687,721.3332,6.1406,177.0518}, //17
	{-55.4592,554.0566,8.3244,79.2909}, //18
	{-248.5932,699.8624,23.0828,79.9175}, //19
	{155.8284,900.1661,20.8150,39.5697}, //20
	{4.1772,1149.4558,19.5938,169.8450}, //21
	{338.2518,1405.7417,6.5547,25.3970}, //22
	{526.8543,1726.1534,10.5059,98.0911}, //23
	{789.8953,1827.5935,4.9064,289.2029}, //24
	{777.3532,1457.9861,20.3478,180.4753}, //25
	{488.4716,1044.0162,28.3788,152.6608}, //26
	{664.3205,2324.0557,26.8347,51.3807}, //27
	{670.5950,2575.0249,28.8709,17.5403}, //28
	{630.0487,2657.4722,32.8611,295.7595}, //29
	{706.3322,2704.4932,55.3554,295.7595}, //30
	{262.5309,2687.4995,22.1832,153.8416}, //31
	{768.2287,4517.4985,14.0206,340.2766}, //32
	{1300.9808,4543.0234,23.1708,19.4436}, //33
	{2638.2271,4902.7378,71.0126,94.0176}, //34
	{4434.5776,4687.3647,50.9907,305.1829}, //35
	{5360.8774,5890.6714,48.6857,3.7766}, //36
	{7851.6299,5540.4263,110.7266,337.4564}, //37
	{5523.9624,6483.9590,50.9735,20.0701}, //38
	{4361.4766,6105.8291,67.2262,96.2108}, //39
	{5136.4961,5618.9995,41.0437,287.6125}, //40
	{4138.0073,3900.5496,51.0798,190.5016}, //41
	{2551.8994,3242.2715,40.5382,138.5112}, //42
	{2152.5601,2264.7920,10.6719,307.0627}, //43
	{540.6043,260.2718,15.6399,193.9483}, //44
	{1422.4718,26.7494,31.9865,24.4569}, //45
	{1697.6381,-675.0569,44.4102,252.8791}, //46
	{1680.3547,-321.6876,45.0586,90.5942}, //47
	{431.5148,-545.5094,42.1075,127.5913}, //48
	{-194.1193,-931.5444,35.4943,100.0177}, //49
	{-233.5578,-1665.3923,2.4766,57.7407}, //50
	{-340.1472,-1985.6677,25.8008,121.9746}, //51
	{-231.9846,-2861.5828,39.1977,177.5077}, //52
	{-761.1592,-2767.8364,74.5911,66.5141}, //53
	{-1985.6620,-2481.9341,31.0926,155.8149}, //54
	{-1446.8142,-2163.0117,7.7365,6.9568}, //55
	{-1023.3646,-2371.7134,58.4241,195.5619}, //56
	{-781.5192,-2458.3237,74.3283,225.9555}, //57
	{-1199.2471,-1800.2697,52.0017,94.9810}, //58
	{-1731.7529,-1475.0513,34.3857,149.1882}, //59
	{-1241.6265,-778.3466,65.1071,212.1454}, //60
	{-1028.6833,-447.2973,36.1549,28.5537}, //61
	{-875.9846,-132.2740,58.5856,28.3129}, //62
	{-251.4909,251.3115,9.4690,356.5934}, //63
	{1316.6074,-702.3929,92.5904,230.3190}, //64
	{1989.6630,41.3275,31.6433,184.8851}, //65
	{-1653.8615,-3487.3589,54.2111,280.3826}, //66
	{-1649.9453,-3946.4734,32.5674,357.4868}, //67
	{-735.0510,-5346.1680,5.6326,268.2584}, //68
	{-1600.8563,-6902.6421,5.5926,233.4056}, //69
	{-3035.4297,-851.6758,11.5599,290.1196}, //70
	{-2397.7275,-70.4003,35.1641,9.9970}, //71
	{-1066.5387,1392.9154,31.4468,101.0821}, //72
	{-1112.1984,2699.1096,45.8564,187.2519}, //73
	{1904.8879,1268.5051,10.6719,40.0836}, //
	{1873.2937,939.7082,10.6719,135.9412}, //
	{2063.1807,669.6696,10.6719,288.1992}, //
	{2457.6309,768.9429,10.6719,43.8203}, //
	{2508.6294,1017.9777,10.6719,246.5254}, //
	{2532.9202,1477.4967,10.6719,146.9079}, //
	{2721.0039,1799.9764,6.7347,329.2697}, //
	{2782.8577,2330.6116,10.7422,314.2296}, //
	{3330.5513,2021.2373,27.3803,305.4562}, //
	{6032.9692,1901.0643,27.3803,230.8822}, //
	{4665.7808,1074.6965,4.1903,296.6829}, //
	{4040.5764,3482.8684,101.6139,294.1762}, //
	{5083.3628,7112.1289,41.0437,254.9858}, //
	{191.0037,2279.5999,22.7469,41.6037}, //
	{-401.6900,2722.6992,61.9932,205.1418}, //
	{-606.4369,2450.5906,72.7573,95.4740}, //
	{-114.2799,1779.7288,20.5436,213.6019}, //
	{-445.3311,1615.2188,35.3513,12.7533}, //
	{-1010.5672,1852.9512,62.4391,23.4301}, //
	{-604.7516,1175.4193,8.6028,155.0547}, //
	{-824.9203,812.3692,18.3717,70.1406}, //
	{-1616.7808,1888.1243,16.6560,33.7936}, //
	{-1921.6068,2420.6663,51.8883,41.0003}, //
	{-2766.5735,2431.8616,90.9026,145.3412}, //
	{-2696.5413,2240.6057,55.4297,232.4488}, //
	{3638.3154,4639.5698,17.4410,293.8862}, //
	{1902.3834,-1459.4747,13.3828,229.0491}, //
	{2639.3467,-1759.6636,10.7188,214.6356}, //
	{1327.1697,-2524.4839,13.3750,55.1474}, //
	{1131.7777,-1855.6212,13.3828,59.5341}, //
	{529.7676,-1420.9901,15.9532,336.5000}, //
	{-167.6781,-185.0264,1.9728,48.8807}, //
	{-771.9181,-1007.6060,78.5413,49.5074}, //
	{-717.0071,-1626.8135,53.2245,156.3551}, //
	{-1358.4285,-1406.6099,110.6525,77.3944}, //
	{-1820.0922,-649.4791,17.2690,326.1601}, //
	{-2301.9172,322.2554,38.6120,130.3483}, //
	{-3427.8687,476.0327,4.9348,123.7682}, //
	{-2812.9216,-4.8202,7.0283,208.9723}, //
	{-2317.8345,-439.5270,79.5408,72.0443}, //
	{-2930.6763,-1776.1724,24.3651,234.9792}, //
	{-2428.8572,-2480.6914,37.2559,248.7660}, //
	{-1998.6473,-1863.7594,41.8699,281.9796} //
};

//konary
new oilSR_query = 11;
new oilSR_createTime;

enum  oilsr_info
{
	bool: ft_isfall,
	ft_hp,
	ft_objectid,
	Text3D:ft_label
};

new oilSR_data[MAX_FALLTREE][falltree_info];

#define oilSR_position fallTree_position

new Float:fishing_pos[][3] = 
{
	{-480.5437,2186.5969,41.8599}, // PRZY TAMIE
	{-1900.7578,2153.1689,2.0755}, // PLAŻA PRZED BAYSIDE
	{-2293.8149,2227.9314,4.9822}, // MOLO BAYSIDE
	{-2976.0232,506.4230,2.4297}, // SF NIEDALEKO SZPITALA
	{-1452.2786,1077.8848,7.1875}, // MOLO POD MOSTEM SF
	{900.2106,-2322.7222,1.6345}, // TRASA PRZY BIAŁYM DOMU
	{-1643.2150,-1687.2117,1.4667}, // ZŁOMOWISKO POD CHILLIAD
	{-195.4659,-1672.0192,1.4547}, // PRZY GRANICY LS/SF
	{155.0900,-1965.9323,3.7734}, // LATARNIA LS
	{380.9958,-2087.8542,7.8359}, // MOLO LS
	{2478.2175,-2708.7424,3.0000}, // DOKI LS
	{2955.8813,-1488.2352,1.6250}, // NIEDALEKO PARKU
	{2821.5549,285.2867,1.3391}, // FOLLOW THE DAM TRAIN CJ!
	{2103.2996,-103.6103,2.2789}, // PALOMINO
	{-324.5610,-468.5326,1.9922}, // BLUEBERRY
	{-489.1968,611.0876,1.7739}, // MOLO NIEDALEKO LIDLA
	{-640.3194,864.4868,2.0000}, // DOM TORENO
	{-711.0256,-5889.9976,1.4789}, // VILLEGREEN
	{-4177.8047,531.5958,4.8948}, // TRASA PRZY SZPITALU SF
	{143.4909,3020.0972,1.4743}, // TRASA PRZY STARYM LOTNISKU LV
	{5418.9497,6960.6909,5.8848} // WINDY TRASA ZIMOWA
};

//vehiclenames
new VehicleNames[][] =
{
	"Landstalker", "Bravura", "Buffalo", "Linerunner", "Perrenial", "Sentinel",
	"Dumper", "Firetruck", "Trashmaster", "Stretch", "Manana", "Infernus",
	"Voodoo", "Pony", "Mule", "Cheetah", "Ambulance", "Leviathan", "Moonbeam",
	"Esperanto", "Taxi", "Washington", "Bobcat", "Whoopee", "BF Injection",
	"Hunter", "Premier", "Enforcer", "Securicar", "Banshee", "Predator", "Bus",
	"Rhino", "Barracks", "Hotknife", "Trailer", "Previon", "Coach", "Cabbie",
	"Stallion", "Rumpo", "RC Bandit", "Romero", "Packer", "Monster", "Admiral",
	"Squalo", "Seasparrow", "Pizzaboy", "Tram", "Trailer", "Turismo", "Speeder",
	"Reefer", "Tropic", "Flatbed", "Yankee", "Caddy", "Solair", "Berkley's RC Van",
	"Skimmer", "PCJ-600", "Faggio", "Freeway", "RC Baron", "RC Raider", "Glendale",
	"Oceanic","Sanchez", "Sparrow", "Patriot", "Quad", "Coastguard", "Dinghy",
	"Hermes", "Sabre", "Rustler", "ZR-350", "Walton", "Regina", "Comet", "BMX",
	"Burrito", "Camper", "Marquis", "Baggage", "Dozer", "Maverick", "News Chopper",
	"Rancher", "FBI Rancher", "Virgo", "Greenwood", "Jetmax", "Hotring", "Sandking",
	"Blista Compact", "Police Maverick", "Boxville", "Benson", "Mesa", "RC Goblin",
	"Hotring Racer A", "Hotring Racer B", "Bloodring Banger", "Rancher", "Super GT",
	"Elegant", "Journey", "Bike", "Mountain Bike", "Beagle", "Cropduster", "Stunt",
	"Tanker", "Roadtrain", "Nebula", "Majestic", "Buccaneer", "Shamal", "Hydra",
	"FCR-900", "NRG-500", "HPV1000", "Cement Truck", "Tow Truck", "Fortune",
	"Cadrona", "FBI Truck", "Willard", "Widlak", "Tractor", "Combine", "Feltzer",
	"Remington", "Slamvan", "Blade", "Freight", "Streak", "Vortex", "Vincent",
	"Bullet", "Clover", "Sadler", "Firetruck", "Hustler", "Intruder", "Primo",
	"Cargobob", "Tampa", "Sunrise", "Merit", "Utility", "Nevada", "Yosemite",
	"Windsor", "Monster", "Monster", "Uranus", "Jester", "Sultan", "Stratium",
	"Elegy", "Raindance", "RC Tiger", "Flash", "Tahoma", "Savanna", "Bandito",
	"Freight Flat", "Streak Carriage", "Kart", "Mower", "Dune", "Sweeper",
	"Broadway", "Tornado", "AT-400", "DFT-30", "Huntley", "Stafford", "BF-400",
	"News Van", "Tug", "Trailer", "Emperor", "Wayfarer", "Euros", "Hotdog", "Club",
	"Freight Box", "Trailer", "Andromada", "Dodo", "RC Cam", "Launch", "Police Car",
	"Police Car", "Police Car", "Police Ranger", "Picador", "S.W.A.T", "Alpha",
	"Phoenix", "Glendale", "Sadler", "Luggage", "Luggage", "Stairs", "Boxville",
	"Tiller", "Utility Trailer"
};
//*************************************************************************POLYGONS/ZONES
new Float:pol_lvairport_data[] = {1701.6489,1530.2684, 1702.0790,1599.1956, 1708.8167,1619.0698,1708.9021,1703.4950, 1497.6643,1704.2557, 1497.5969,1518.2426};
new Float:pol_lvairport_render_data[] = {1456.1537,1660.3042, 1461.8743,1531.8413, 1811.7538,1304.8712, 2093.4036,1591.7946, 2121.0955,1731.4425, 1658.5729,1725.1012, 1688.7626,1665.6791};
new pol_lvairport;
new zone_sanandreas;
new Float:pol_ZoneSanAndreas[] = {3137.6699,3166.6824,-3077.3770,3196.2244,-3219.8999,-3065.8479,3260.7332,-3217.4414};
new Float:pol_cdesert_data[] = {2793.1152,1949.2572,3033.1313,1624.9917,3635.9504,1559.5812,3866.7639,979.5522,4601.5049,709.4801,6405.2515,1450.7512,6739.6167,1886.0747,6608.6553,2536.6553,6154.0859,2603.5928,2893.3977,2566.1458,2797.9004,2297.7515};
new pol_cdesert;
new weatherarea_OilProvince;
new Float:pol_OilProvinceWeather[] = {-2287.8320,-6776.5996, -2784.3120,-6685.0854, -3709.9692,-6542.1934, -3835.7266,-6889.0801, -3853.9875,-10120.2109, -4461.5786,-10133.6660, -4542.0630,-10886.0859, -3363.8157,-10725.8096, -3354.6187,-10427.3096, -3084.9741,-10154.6963, -3189.4905,-7274.7480, -2551.3928,-7243.0015, -2241.2444,-7045.9448};
new Float:pol_PencilFactory[] = {-1859.4055,-3949.2263, -1852.5857,-4282.1260, -2218.9414,-4359.2627, -2937.8064,-4341.7129, -3702.0864,-3776.6458, -3402.2815,-3204.9756, -2873.3401,-3058.5437, -2291.6602,-3017.0105, -2237.7627,-3426.6772, -1860.1918,-3939.3582};
new weatherarea_PencilFactory;
new Float:pol_deerfield_data[] = {-2881.1699,-619.7386, -3056.1917,-520.8093, -3729.7073,-421.2994, -3935.1140,-280.1003, -4552.2905,-731.6786, -4587.1494,-1031.6826, -4909.6753,-950.7227, -5108.4785,-1445.1471, -4926.3887,-1566.2483, -3957.3772,-1555.5592, -3174.6370,-1108.4590, -2901.1001,-895.0438};
new pol_deerfield;