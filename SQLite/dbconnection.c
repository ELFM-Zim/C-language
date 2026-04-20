#include <sqlite3.h>
#include <stddef.h>
#include <stdio.h>

int callback(void* data, int argc, char** argv,	char** azColName)
{

		printf("%s: ", (const char*)data);

		for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
		printf("\n");

		return 0;
}

int main(int argc, char** argv)
{
	sqlite3* DB;

	if(sqlite3_open("connection.db", &DB) != SQLITE_OK)
	{
		return 1;
	}

	char* querry = "CREATE TABLE IF NOT EXISTS PLAYER(Id INTEGER PRIMARY KEY , Name TEXT, HealthPoints  int NOT NULL, ItemLeftHand  TEXT, ItemRightHand TEXT, Armor TEXT); INSERT INTO PLAYER (Name, HealthPoints, ItemLeftHand, ItemRightHand, Armor) VALUES('elloah', 10, 'espada', 'livre', 'calcinha');";
	char* error_message;

	if(sqlite3_exec(DB, querry, callback, "Callback function", &error_message) != SQLITE_OK)
	{
			goto ending_program;
	}

	querry = "SELECT * FROM PLAYER;";

	if(sqlite3_exec(DB, querry, callback, 0, &error_message) != SQLITE_OK)
	{
			goto ending_program;
	}

	//sqlite3_free(error_message);
	sqlite3_close(DB);	

	return 0;
ending_program:
	printf("%s\n", error_message);
	sqlite3_free(error_message);	
	sqlite3_close(DB);

	return 1;
}
