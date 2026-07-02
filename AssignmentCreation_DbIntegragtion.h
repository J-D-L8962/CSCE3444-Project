#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <postgresql/libpq-fe.h> //official PostgreSQL C library, ensure your configuration is correct to use this library

// Helper function to safely execute SQL commands that don't return data
int execute_sql(PGconn *conn, const char *sql) 
{
    PGresult *res = PQexec(conn, sql);
    
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "SQL Error: %s", PQerrorMessage(conn));
        PQclear(res);
        return 0;
    }
    
    PQclear(res);
    return 1;
}

//Create the database tables automatically
void setup_database(PGconn *conn) 
{
    // Create  Users Table
    const char *users_table = 
        "CREATE TABLE IF NOT EXISTS users ("
        "id SERIAL PRIMARY KEY,"
        "username TEXT UNIQUE NOT NULL,"
        "password TEXT NOT NULL);";
    execute_sql(conn, users_table);

    // Create Assignments Table (Linked to users via user_id)
    const char *assignments_table = 
        "CREATE TABLE IF NOT EXISTS assignments ("
        "id SERIAL PRIMARY KEY,"
        "user_id INTEGER NOT NULL REFERENCES users(id) ON DELETE CASCADE,"
        "title TEXT NOT NULL,"
        "due_date TEXT NOT NULL);";
    execute_sql(conn, assignments_table);
}

//Authenticate user and return their unique User ID (-1 if failed)
int authenticate_user(PGconn *conn, const char *username, const char *password) 
{
    const char *sql = "SELECT id FROM users WHERE username = $1 AND password = $2;";
    const char *paramValues[2];
    paramValues[0] = username;
    paramValues[1] = password;

    // Secure parameterized query to block SQL injection attacks
    PGresult *res = PQexecParams(conn, sql, 2, NULL, paramValues, NULL, NULL, 0);
    int user_id = -1;

    if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0) 
    {
        user_id = atoi(PQgetvalue(res, 0, 0)); // Extract ID from row 0, column 0
    }

    PQclear(res);
    return user_id;
}

//Fetch and print assignments belonging ONLY to the logged-in user
void show_assignments(PGconn *conn, int user_id)
{
    const char *sql = "SELECT title, due_date FROM assignments WHERE user_id = $1;";
    char user_id_str[16];
    sprintf(user_id_str, "%d", user_id);
    
    const char *paramValues[1];
    paramValues[0] = user_id_str;

    PGresult *res = PQexecParams(conn, sql, 1, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) == PGRES_TUPLES_OK) 
    {
        printf("\n--- YOUR ASSIGNMENTS (pgAdmin/PostgreSQL) ---\n");
        int rows = PQntuples(res);
        
        if (rows == 0) 
        {
            printf("No assignments found for your account.\n");
        } else 
        {
            for (int i = 0; i < rows; i++) 
            {
                char *title = PQgetvalue(res, i, 0);
                char *due = PQgetvalue(res, i, 1);
                printf("Task: %s | Due: %s\n", title, due);
            }
        }
        printf("--------------------------------------------\n");
    } else 
    {
        fprintf(stderr, "Failed to fetch assignments: %s", PQerrorMessage(conn));
    }

    PQclear(res);
}