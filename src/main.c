/*
 * @Author: SingleBiu
 * @Date: 2023-02-25 14:05:20
 * @LastEditors: SingleBiu
 * @LastEditTime: 2023-02-25 16:23:35
 * @Description: file content
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/mysql.h"

#define MYSQL_HOST "127.0.0.1"
#define MYSQL_USER "root"
#define MYSQL_PASSWORD "123456"
#define MYSQL_DATABASE_TEST "test"

void connect_mysql(MYSQL *conn, char *database)
{
    if (mysql_real_connect(conn,
                           MYSQL_HOST,
                           MYSQL_USER,
                           MYSQL_PASSWORD,
                           database,
                           0,
                           NULL,
                           0))
    {
        // printf("database connected\n");
    }
    else
    {
        printf("database connect failed\n");
        return;
    }
}

void exec_query_SQL(MYSQL *conn, char *sql)
{
    if (NULL == conn || NULL == sql)
    {
        return;
    }

    MYSQL_RES *res;
    MYSQL_ROW row;
    int flag = 0;

    flag = mysql_real_query(conn, sql, (unsigned long)strlen(sql));
    if (flag)
    {
        printf("exec sql failed\n");
        return;
    }
    else
    {
        // printf("exec sql success\n");
    }

    res = mysql_store_result(conn);
    
    while (row = mysql_fetch_row(res))
    {
        for (int i = 0; i < mysql_num_fields(res); i++)
        {
            printf("%s\t", row[i]);
        }
        printf("\n");
    }
    mysql_free_result(res);
}

void exec_SQL(MYSQL *conn, char *sql)
{
    if (NULL == conn || NULL == sql)
    {
        return;
    }

    int flag = 0;

    flag = mysql_real_query(conn, sql, (unsigned long)strlen(sql));
    if (flag)
    {
        printf("exec sql failed\n");
        return;
    }
    else
    {
        // printf("exec sql success\n");
    }
}

int main(int argc, char const *argv[])
{
    MYSQL *conn;

    conn = mysql_init(NULL);

    connect_mysql(conn, MYSQL_DATABASE_TEST);

    exec_SQL(conn, "truncate table user;");

    exec_SQL(conn, "insert into user (name) values ('user1');");
    exec_SQL(conn, "insert into user (name) values ('user2');");
    exec_SQL(conn, "insert into user (name) values ('user3');");

    exec_query_SQL(conn, "select * from user;");

    exec_SQL(conn, "update user set name = 'user4' where id = 2;");
    
    printf("-----after update-----\n");

    exec_query_SQL(conn, "select * from user;");
    
    exec_SQL(conn, "delete from user where id = 3");
    
    printf("-----after delete-----\n");
    
    exec_query_SQL(conn, "select * from user;");
    
    mysql_close(conn);
    mysql_library_end();
    return 0;
}
