#ifndef GLOBALS_H
#define GLOBALS_H

#include <QSqlDatabase>
#include <QString>

extern QSqlDatabase db_conn;
extern QString db_server;
extern QString db_databasename;
extern QString db_userid;
extern QString db_password;
extern int db_port;
extern QString db_tablename;
extern QString a;

#endif // GLOBALS_H
