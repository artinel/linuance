#define DB_STATE_OPEN 1
#define DB_STATE_CLOSE 0
#define DB_STATE_EXISTS 2
#define DB_STATE_NOT_EXISTS 3
#define DB_STATE_SUCCESS 4
#define DB_STATE_FAIL 5
//TODO change db name
#define DB_NAME "data.db"

//Table user
#define DB_TABLE_USER "user"
#define DB_TABLE_USER_ID "id"
#define DB_TABLE_USER_USERNAME "username"
#define DB_TABLE_USER_PASSWORD "password"
#define DB_TABLE_USER_IMAGE "image"

//Queries
#define DB_QUERY_USER_INIT "CREATE TABLE IF NOT EXISTS " DB_TABLE_USER "(" DB_TABLE_USER_ID " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, " DB_TABLE_USER_USERNAME " TEXT NOT NULL, " DB_TABLE_USER_PASSWORD " TEXT NOT NULL ," DB_TABLE_USER_IMAGE " TEXT);"

#define DB_QUERY_INIT DB_QUERY_USER_INIT

//Table user queries
//TODO add default image path here
#define DB_QUERY_USER_CHECK_EXISTS "SELECT * FROM " DB_TABLE_USER " WHERE " DB_TABLE_USER_USERNAME " = ?;"
#define DB_QUERY_USER_REGISTER "INSERT INTO " DB_TABLE_USER " VALUES(NULL, ?, ?, NULL);"
