#include<sqlite3.h>
#include"database_config.h"

//define variables
sqlite3 *db;
sqlite3_stmt *stmt;
int db_state = DB_STATE_CLOSE; //for specify the status of database (open or close)
int db_status; //for holding database return integers
char *db_sql; //for holding sql queries
char *db_err; //for holding database error messages
//define functions
int db_open();//open database
int db_close();//close database
void db_init();//init database
void db_error();//print database errors
void db_init();//initial database
int db_user_register(const char*, const char*);//register user
int db_user_check_exists(const char*);//check if user already exists(0 = exists , 1 = does not exists)

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
		//sqlite3_close returns 0 when it success to close database and 1 when it fails
		db_status = sqlite3_close(db);
		if(db_status)
			fprintf(stderr, "Couldn't close database : %s\n", sqlite3_errmsg(db));
		else{
			db_state = DB_STATE_CLOSE;
		}
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
		db_sql = malloc(strlen(DB_QUERY_INIT) + 1);
		strcpy(db_sql, DB_QUERY_INIT);
		db_status = sqlite3_exec(db, db_sql, NULL, NULL, &db_err);
		db_error();
		db_close();
	}
}

int db_user_check_exists(const char *username){
	int exists = DB_STATE_EXISTS;
	if(db_open()){
		sqlite3_stmt *stmt;
		db_status = sqlite3_prepare_v2(db, DB_QUERY_USER_CHECK_EXISTS, -1, &stmt, 0);
		sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
		if(sqlite3_step(stmt) != SQLITE_ROW)
			//if there was not a record then it does not exists
			exists = DB_STATE_NOT_EXISTS;
		db_error();
		sqlite3_finalize(stmt);
	}
	return exists;
}

int db_user_register(const char *username, const char *password){
	if(db_open()){
		if(db_user_check_exists(username) == DB_STATE_NOT_EXISTS){
			sqlite3_stmt *res;
			db_status = sqlite3_prepare_v2(db, DB_QUERY_USER_REGISTER, -1, &stmt, 0);
			sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
			sqlite3_bind_text(stmt, 2, password, -1, SQLITE_TRANSIENT);
			sqlite3_step(stmt);
			db_error();
			sqlite3_finalize(stmt);
			db_close();
			return DB_STATE_SUCCESS;
		}else
			return DB_STATE_EXISTS;
	}
	return DB_STATE_FAIL;
}
