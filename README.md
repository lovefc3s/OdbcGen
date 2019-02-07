# OdbcGen
This Project ODBC Generation for Lunux C++ End User  
MS SqlServer がLinuxに対応したので作成します。  

### 使用方法
SQL Server, MySQL/MariaDB,PostgreSQL の使用を前提に最大限の互換性を考慮して設計しました。  
ODBCドライバーは適切なフォルダへコピー済とします。

#### 1. 各種ODBCドライバーを設定します。
以下に MariaDB での設定例を記述します。
``` /etc/odbc.ini:sample
/etc/odbc.ini
[mariadb]
Description=ODBC for MariaDB
Driver=/usr/lib/libmaodbc.so
Port = 3306
Socket = /var/run/mysqld/mysqld.sock
Trace=Yes
Server=192.168.***.***
Database=mysql
ClientCharset=UTF-8

/etc/odbcinst.ini
[ODBC for MariaDB]
Description=ODBC for MariaDB
Driver=/usr/lib/libmaodbc.so
UsageCount=1
```  
#### 2. 接続先設定

