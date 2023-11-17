#include "globals.h"

QSqlDatabase db_conn = QSqlDatabase::addDatabase("QMYSQL");
QString db_tablename;
QString db_server;
QString db_databasename;
QString db_userid;
QString db_password;
int db_port;
