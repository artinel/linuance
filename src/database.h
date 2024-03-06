#include<sqlite3.h>
#include"database_config.h"

//define variables
sqlite3 *db;
int db_state = DB_STATE_CLOSE; //for specify the status of database (open or close)
int db_status; //for holding database return integers
char *db_sql; //for holding sql queries
char *db_err; //for holding database error messages
//define functions
int db_open();//open database
int db_close();//close database
void db_init();//init database
void db_error();//print database errors

int db_open(){
	//db_state 1 = Database is open
	//db_state 0 = Database is close
	//check if database is close
	if(!db_state){
		//sqlite3_open returns 0 when it success to open database and 1 when it fails
		db_status = sqlite3_open(DB_NAME, &db);
		if(db_status)
			fprintf(stderr, "Couldn't open database : %s\n", sqlite3_errmsg(db));
		else
			db_state = DB_STATE_OPEN;
	}
	return db_state;
}

int db_close(){
	//check if database is open
	if(db_state){
		db_status = sqlite3_close(db);
		if(db_status)
			fprintf(stderr, "Couldn't close database : %s\n", sqlite3_errmsg(db));
		else
			db_state = DB_STATE_CLOSE;
	}
	return db_state;
}

void db_error(){
	if(db_status != SQLITE_OK){
		fprintf(stderr, "SQL error : %s\n" , db_err);
	}
}

void db_init(){
	//Open database and check if it was successful (db_state = 1)
	if(db_open()){
		//add codes here
		db_status = sqlite3_exec(db, db_sql, NULL, NULL, &db_err);
		db_error();
		db_close();
	}
}
