#ifndef __ODBCSQL_H__
#define __ODBCSQL_H__
#include <sql.h>
#include <sqlext.h>
#define RESULT_LEN  2048

//Sqlで使用される型
enum	eSqlType {
	_unknown		= -1,
	_bit			= 0, 
	_tinyint		= 1,
	_smallint		= 2,
	_int			= 3,
	_bigint			= 4,
	_decimal		= 5,
	_numeric		= 6,
	_real			= 7,
	_float			= 8,
	_smallmoney		= 9,
	_money			= 10,
	_date			= 11,
	_time			= 12,
	_datetime		= 13,
	_datetime2		= 14,
	_smalldatetime	= 15,
	_datetimeoffset	= 16,
	_char			= 17,
	_varchar		= 18,
	_text			= 19,
	_nchar			= 20,
	_nvarchar		= 21,
	_ntext			= 22,
	_binary			= 23,
	_verbinary		= 24,
	_image			= 25,
	_xml			= 26,
};

class COdbcsql {
public:
	COdbcsql();
	~COdbcsql();
public:
    SQLHANDLE get_SQLHANDLE(SQLSMALLINT HandleType);
private:
    SQLHENV   henv  = SQL_NULL_HENV;   // Environment
    SQLHDBC   hdbc  = SQL_NULL_HDBC;   // Connection handle
    SQLHSTMT  hstmt = SQL_NULL_HSTMT;  // Statement handle
    SQLRETURN retcode;
    SQLCHAR strResult[RESULT_LEN];
    SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;

public:
    SQLRETURN  SQL_API CSQLAllocConnect(SQLHENV EnvironmentHandle,
                                       SQLHDBC *ConnectionHandle);
    SQLRETURN  SQL_API CSQLAllocEnv(SQLHENV *EnvironmentHandle);
#if (ODBCVER >= 0x0300)
    SQLRETURN  SQL_API CSQLAllocHandle(SQLSMALLINT HandleType,
                                      SQLHANDLE InputHandle, SQLHANDLE *OutputHandle);
#endif
    SQLRETURN  SQL_API CSQLAllocStmt(SQLHDBC ConnectionHandle,
                                    SQLHSTMT *StatementHandle);
    SQLRETURN  SQL_API CSQLBindCol(SQLHSTMT StatementHandle,
                                  SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType,
                                  SQLPOINTER TargetValue, SQLLEN BufferLength,
                                  SQLLEN *StrLen_or_Ind);

#if (ODBCVER >= 0x0300)
    SQLRETURN  SQL_API CSQLBindParam(SQLHSTMT StatementHandle,
                                    SQLUSMALLINT ParameterNumber, SQLSMALLINT ValueType,
                                    SQLSMALLINT ParameterType, SQLULEN LengthPrecision,
                                    SQLSMALLINT ParameterScale, SQLPOINTER ParameterValue,
                                    SQLLEN *StrLen_or_Ind);
#endif

    SQLRETURN  SQL_API CSQLCancel(SQLHSTMT StatementHandle);

#if (ODBCVER >= 0x0380)
	SQLRETURN  SQL_API CSQLCancelHandle(SQLSMALLINT HandleType, SQLHANDLE InputHandle);
#endif 


#if (ODBCVER >= 0x0300)
    SQLRETURN  SQL_API CSQLCloseCursor(SQLHSTMT StatementHandle);

    SQLRETURN  SQL_API CSQLColAttribute(SQLHSTMT StatementHandle,
                                        SQLUSMALLINT ColumnNumber, SQLUSMALLINT FieldIdentifier,
                                        SQLPOINTER CharacterAttribute, SQLSMALLINT BufferLength,
                                        SQLSMALLINT *StringLength, SQLLEN *NumericAttribute );

										/* spec says (SQLPOINTER) not (SQLEN*) - PAH */
										/* Ms now say SQLLEN* 
                                           http://msdn.microsoft.com/library/en-us/odbc/htm/dasdkodbcoverview_64bit.asp - NG */
										
#endif


    SQLRETURN  SQL_API CSQLColumns(SQLHSTMT StatementHandle,
                                  SQLCHAR *CatalogName, SQLSMALLINT NameLength1,
                                  SQLCHAR *SchemaName, SQLSMALLINT NameLength2,
                                  SQLCHAR *TableName, SQLSMALLINT NameLength3,
                                  SQLCHAR *ColumnName, SQLSMALLINT NameLength4);


    SQLRETURN  SQL_API CSQLConnect(SQLHDBC ConnectionHandle,
                                  SQLCHAR *ServerName, SQLSMALLINT NameLength1,
                                  SQLCHAR *UserName, SQLSMALLINT NameLength2,
                                  SQLCHAR *Authentication, SQLSMALLINT NameLength3);

#if (ODBCVER >= 0x0300)
    SQLRETURN  SQL_API CSQLCopyDesc(SQLHDESC SourceDescHandle,
                                   SQLHDESC TargetDescHandle);
#endif

    SQLRETURN  SQL_API CSQLDataSources(SQLHENV EnvironmentHandle,
                                      SQLUSMALLINT Direction, SQLCHAR *ServerName,
                                      SQLSMALLINT BufferLength1, SQLSMALLINT *NameLength1,
                                      SQLCHAR *Description, SQLSMALLINT BufferLength2,
                                      SQLSMALLINT *NameLength2);

    SQLRETURN  SQL_API CSQLDescribeCol(SQLHSTMT StatementHandle,
                                      SQLUSMALLINT ColumnNumber, SQLCHAR *ColumnName,
                                      SQLSMALLINT BufferLength, SQLSMALLINT *NameLength,
                                      SQLSMALLINT *DataType, SQLULEN *ColumnSize,
                                      SQLSMALLINT *DecimalDigits, SQLSMALLINT *Nullable);

    SQLRETURN  SQL_API CSQLDisconnect(SQLHDBC ConnectionHandle);

#if (ODBCVER >= 0x0300)
    SQLRETURN  SQL_API CSQLEndTran(SQLSMALLINT HandleType, SQLHANDLE Handle,
                                  SQLSMALLINT CompletionType);
#endif

    SQLRETURN  SQL_API CSQLError(SQLHENV EnvironmentHandle,
                                SQLHDBC ConnectionHandle, SQLHSTMT StatementHandle,
                                SQLCHAR *Sqlstate, SQLINTEGER *NativeError,
                                SQLCHAR *MessageText, SQLSMALLINT BufferLength,
                                SQLSMALLINT *TextLength);

    SQLRETURN  SQL_API CSQLExecDirect(SQLHSTMT StatementHandle,
                                     SQLCHAR *StatementText, SQLINTEGER TextLength);

    SQLRETURN  SQL_API CSQLExecute(SQLHSTMT StatementHandle);

    SQLRETURN  SQL_API CSQLFetch(SQLHSTMT StatementHandle);

#if (ODBCVER >= 0x0300)
    SQLRETURN  SQL_API CSQLFetchScroll(SQLHSTMT StatementHandle,
                                      SQLSMALLINT FetchOrientation, SQLLEN FetchOffset);
#endif

    SQLRETURN  SQL_API CSQLFreeConnect(SQLHDBC ConnectionHandle);

    SQLRETURN  SQL_API CSQLFreeEnv(SQLHENV EnvironmentHandle);

#if (ODBCVER >= 0x0300)
    SQLRETURN  SQL_API CSQLFreeHandle(SQLSMALLINT HandleType, SQLHANDLE Handle);
#endif

    SQLRETURN  SQL_API CSQLFreeStmt(SQLHSTMT StatementHandle,
                                   SQLUSMALLINT Option);

#if (ODBCVER >= 0x0300)
    SQLRETURN  SQL_API CSQLGetConnectAttr(SQLHDBC ConnectionHandle,
                                         SQLINTEGER Attribute, SQLPOINTER Value,
                                         SQLINTEGER BufferLength, SQLINTEGER *StringLength);
#endif

    SQLRETURN  SQL_API CSQLGetConnectOption(SQLHDBC ConnectionHandle,
                                           SQLUSMALLINT Option, SQLPOINTER Value);

    SQLRETURN  SQL_API CSQLGetCursorName(SQLHSTMT StatementHandle,
                                        SQLCHAR *CursorName, SQLSMALLINT BufferLength,
                                        SQLSMALLINT *NameLength);

    SQLRETURN  SQL_API CSQLGetData(SQLHSTMT StatementHandle,
                                  SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType,
                                  SQLPOINTER TargetValue, SQLLEN BufferLength,
                                  SQLLEN *StrLen_or_Ind);

#if (ODBCVER >= 0x0300)
    SQLRETURN   CSQLGetDescField(SQLHDESC DescriptorHandle,
                                SQLSMALLINT RecNumber, SQLSMALLINT FieldIdentifier,
                                SQLPOINTER Value, SQLINTEGER BufferLength,
                                SQLINTEGER *StringLength);

    SQLRETURN  SQL_API CSQLGetDescRec(SQLHDESC DescriptorHandle,
                                     SQLSMALLINT RecNumber, SQLCHAR *Name,
                                     SQLSMALLINT BufferLength, SQLSMALLINT *StringLength,
                                     SQLSMALLINT *Type, SQLSMALLINT *SubType,
                                     SQLLEN *Length, SQLSMALLINT *Precision,
                                     SQLSMALLINT *Scale, SQLSMALLINT *Nullable);

    SQLRETURN  SQL_API CSQLGetDiagField(SQLSMALLINT HandleType, SQLHANDLE Handle,
                                       SQLSMALLINT RecNumber, SQLSMALLINT DiagIdentifier,
                                       SQLPOINTER DiagInfo, SQLSMALLINT BufferLength,
                                       SQLSMALLINT *StringLength);

    SQLRETURN  SQL_API CSQLGetDiagRec(SQLSMALLINT HandleType, SQLHANDLE Handle,
                                     SQLSMALLINT RecNumber, SQLCHAR *Sqlstate,
                                     SQLINTEGER *NativeError, SQLCHAR *MessageText,
                                     SQLSMALLINT BufferLength, SQLSMALLINT *TextLength);

    SQLRETURN  SQL_API CSQLGetEnvAttr(SQLHENV EnvironmentHandle,
                                     SQLINTEGER Attribute, SQLPOINTER Value,
                                     SQLINTEGER BufferLength, SQLINTEGER *StringLength);
#endif  /* ODBCVER >= 0x0300 */

    SQLRETURN  SQL_API CSQLGetFunctions(SQLHDBC ConnectionHandle,
                                       SQLUSMALLINT FunctionId, SQLUSMALLINT *Supported);

    SQLRETURN  SQL_API CSQLGetInfo(SQLHDBC ConnectionHandle,
                                  SQLUSMALLINT InfoType, SQLPOINTER InfoValue,
                                  SQLSMALLINT BufferLength, SQLSMALLINT *StringLength);

#if (ODBCVER >= 0x0300)
    SQLRETURN  SQL_API CSQLGetStmtAttr(SQLHSTMT StatementHandle,
                                      SQLINTEGER Attribute, SQLPOINTER Value,
                                      SQLINTEGER BufferLength, SQLINTEGER *StringLength);
#endif  /* ODBCVER >= 0x0300 */

    SQLRETURN  SQL_API CSQLGetStmtOption(SQLHSTMT StatementHandle,
                                        SQLUSMALLINT Option, SQLPOINTER Value);

    SQLRETURN  SQL_API CSQLGetTypeInfo(SQLHSTMT StatementHandle,
                                      SQLSMALLINT DataType);

    SQLRETURN  SQL_API CSQLNumResultCols(SQLHSTMT StatementHandle,
                                        SQLSMALLINT *ColumnCount);

    SQLRETURN  SQL_API CSQLParamData(SQLHSTMT StatementHandle,
                                    SQLPOINTER *Value);

    SQLRETURN  SQL_API CSQLPrepare(SQLHSTMT StatementHandle,
                                  SQLCHAR *StatementText, SQLINTEGER TextLength);

    SQLRETURN  SQL_API CSQLPutData(SQLHSTMT StatementHandle,
                                  SQLPOINTER Data, SQLLEN StrLen_or_Ind);

    SQLRETURN  SQL_API CSQLRowCount(SQLHSTMT StatementHandle,
                                   SQLLEN *RowCount);

#if (ODBCVER >= 0x0300)
    SQLRETURN  SQL_API CSQLSetConnectAttr(SQLHDBC ConnectionHandle,
                                         SQLINTEGER Attribute, SQLPOINTER Value,
                                         SQLINTEGER StringLength);
#endif /* ODBCVER >= 0x0300 */

    SQLRETURN  SQL_API CSQLSetConnectOption(SQLHDBC ConnectionHandle,
                                           SQLUSMALLINT Option, SQLULEN Value);

    SQLRETURN  SQL_API CSQLSetCursorName(SQLHSTMT StatementHandle,
                                        SQLCHAR *CursorName, SQLSMALLINT NameLength);

#if (ODBCVER >= 0x0300)
    SQLRETURN  SQL_API CSQLSetDescField(SQLHDESC DescriptorHandle,
                                       SQLSMALLINT RecNumber, SQLSMALLINT FieldIdentifier,
                                       SQLPOINTER Value, SQLINTEGER BufferLength);

    SQLRETURN  SQL_API CSQLSetDescRec(SQLHDESC DescriptorHandle,
                                     SQLSMALLINT RecNumber, SQLSMALLINT Type,
                                     SQLSMALLINT SubType, SQLLEN Length,
                                     SQLSMALLINT Precision, SQLSMALLINT Scale,
                                     SQLPOINTER Data, SQLLEN *StringLength,
                                     SQLLEN *Indicator);

    SQLRETURN  SQL_API CSQLSetEnvAttr(SQLHENV EnvironmentHandle,
                                     SQLINTEGER Attribute, SQLPOINTER Value,
                                     SQLINTEGER StringLength);
#endif /* ODBCVER >= 0x0300 */

    SQLRETURN  SQL_API CSQLSetParam(SQLHSTMT StatementHandle,
                                   SQLUSMALLINT ParameterNumber, SQLSMALLINT ValueType,
                                   SQLSMALLINT ParameterType, SQLULEN LengthPrecision,
                                   SQLSMALLINT ParameterScale, SQLPOINTER ParameterValue,
                                   SQLLEN *StrLen_or_Ind);

#if (ODBCVER >= 0x0300)
    SQLRETURN  SQL_API CSQLSetStmtAttr(SQLHSTMT StatementHandle,
                                      SQLINTEGER Attribute, SQLPOINTER Value,
                                      SQLINTEGER StringLength);
#endif

    SQLRETURN  SQL_API CSQLSetStmtOption(SQLHSTMT StatementHandle,
                                        SQLUSMALLINT Option, SQLULEN Value);

    SQLRETURN  SQL_API CSQLSpecialColumns(SQLHSTMT StatementHandle,
                                         SQLUSMALLINT IdentifierType, SQLCHAR *CatalogName,
                                         SQLSMALLINT NameLength1, SQLCHAR *SchemaName,
                                         SQLSMALLINT NameLength2, SQLCHAR *TableName,
                                         SQLSMALLINT NameLength3, SQLUSMALLINT Scope,
                                         SQLUSMALLINT Nullable);

    SQLRETURN  SQL_API CSQLStatistics(SQLHSTMT StatementHandle,
                                     SQLCHAR *CatalogName, SQLSMALLINT NameLength1,
                                     SQLCHAR *SchemaName, SQLSMALLINT NameLength2,
                                     SQLCHAR *TableName, SQLSMALLINT NameLength3,
                                     SQLUSMALLINT Unique, SQLUSMALLINT Reserved);

    SQLRETURN   SQL_API CSQLTables(SQLHSTMT StatementHandle,
                                  SQLCHAR *CatalogName, SQLSMALLINT NameLength1,
                                  SQLCHAR *SchemaName, SQLSMALLINT NameLength2,
                                  SQLCHAR *TableName, SQLSMALLINT NameLength3,
                                  SQLCHAR *TableType, SQLSMALLINT NameLength4);

    SQLRETURN  SQL_API CSQLTransact(SQLHENV EnvironmentHandle,
                                   SQLHDBC ConnectionHandle, SQLUSMALLINT CompletionType);
//SQLEXT.H

    SQLRETURN SQL_API CSQLDriverConnect(
        SQLHDBC            hdbc,
        SQLHWND            hwnd,
        SQLCHAR 		  *szConnStrIn,
        SQLSMALLINT        cbConnStrIn,
        SQLCHAR           *szConnStrOut,
        SQLSMALLINT        cbConnStrOutMax,
        SQLSMALLINT 	  *pcbConnStrOut,
        SQLUSMALLINT       fDriverCompletion);

    SQLRETURN SQL_API CSQLBrowseConnect(
        SQLHDBC            hdbc,
        SQLCHAR 		  *szConnStrIn,
        SQLSMALLINT        cbConnStrIn,
        SQLCHAR 		  *szConnStrOut,
        SQLSMALLINT        cbConnStrOutMax,
        SQLSMALLINT       *pcbConnStrOut);

#if (ODBCVER >= 0x0300)
    SQLRETURN	SQL_API CSQLBulkOperations(
        SQLHSTMT			StatementHandle,
        SQLSMALLINT			Operation);
#endif  /* ODBCVER >= 0x0300 */

    SQLRETURN SQL_API CSQLColAttributes(
        SQLHSTMT           hstmt,
        SQLUSMALLINT       icol,
        SQLUSMALLINT       fDescType,
        SQLPOINTER         rgbDesc,
        SQLSMALLINT        cbDescMax,
        SQLSMALLINT 	  *pcbDesc,
        SQLLEN 		      *pfDesc);

    SQLRETURN SQL_API CSQLColumnPrivileges(
        SQLHSTMT           hstmt,
        SQLCHAR 		  *szCatalogName,
        SQLSMALLINT        cbCatalogName,
        SQLCHAR 		  *szSchemaName,
        SQLSMALLINT        cbSchemaName,
        SQLCHAR 		  *szTableName,
        SQLSMALLINT        cbTableName,
        SQLCHAR 		  *szColumnName,
        SQLSMALLINT        cbColumnName);

    SQLRETURN SQL_API CSQLDescribeParam(
        SQLHSTMT           hstmt,
        SQLUSMALLINT       ipar,
        SQLSMALLINT 	  *pfSqlType,
        SQLULEN 	      *pcbParamDef,
        SQLSMALLINT 	  *pibScale,
        SQLSMALLINT 	  *pfNullable);

    SQLRETURN SQL_API CSQLExtendedFetch(
        SQLHSTMT           hstmt,
        SQLUSMALLINT       fFetchType,
        SQLLEN             irow,
        SQLULEN 	  	   *pcrow,
        SQLUSMALLINT 	   *rgfRowStatus);

    SQLRETURN SQL_API CSQLForeignKeys(
        SQLHSTMT           hstmt,
        SQLCHAR 		  *szPkCatalogName,
        SQLSMALLINT        cbPkCatalogName,
        SQLCHAR 		  *szPkSchemaName,
        SQLSMALLINT        cbPkSchemaName,
        SQLCHAR 		  *szPkTableName,
        SQLSMALLINT        cbPkTableName,
        SQLCHAR 		  *szFkCatalogName,
        SQLSMALLINT        cbFkCatalogName,
        SQLCHAR 		  *szFkSchemaName,
        SQLSMALLINT        cbFkSchemaName,
        SQLCHAR 		  *szFkTableName,
        SQLSMALLINT        cbFkTableName);

    SQLRETURN SQL_API CSQLMoreResults(
        SQLHSTMT           hstmt);

    SQLRETURN SQL_API CSQLNativeSql(
        SQLHDBC            hdbc,
        SQLCHAR 		  *szSqlStrIn,
        SQLINTEGER         cbSqlStrIn,
        SQLCHAR 		  *szSqlStr,
        SQLINTEGER         cbSqlStrMax,
        SQLINTEGER 		  *pcbSqlStr);

    SQLRETURN SQL_API CSQLNumParams(
        SQLHSTMT           hstmt,
        SQLSMALLINT 	  *pcpar);

    SQLRETURN SQL_API CSQLParamOptions(
        SQLHSTMT           hstmt,
        SQLULEN        	   crow,
        SQLULEN 	  	   *pirow);

    SQLRETURN SQL_API CSQLPrimaryKeys(
        SQLHSTMT           hstmt,
        SQLCHAR 		  *szCatalogName,
        SQLSMALLINT        cbCatalogName,
        SQLCHAR 		  *szSchemaName,
        SQLSMALLINT        cbSchemaName,
        SQLCHAR 		  *szTableName,
        SQLSMALLINT        cbTableName);

    SQLRETURN SQL_API CSQLProcedureColumns(
        SQLHSTMT           hstmt,
        SQLCHAR 		  *szCatalogName,
        SQLSMALLINT        cbCatalogName,
        SQLCHAR 		  *szSchemaName,
        SQLSMALLINT        cbSchemaName,
        SQLCHAR 		  *szProcName,
        SQLSMALLINT        cbProcName,
        SQLCHAR 		  *szColumnName,
        SQLSMALLINT        cbColumnName);

    SQLRETURN SQL_API CSQLProcedures(
        SQLHSTMT           hstmt,
        SQLCHAR 		  *szCatalogName,
        SQLSMALLINT        cbCatalogName,
        SQLCHAR 		  *szSchemaName,
        SQLSMALLINT        cbSchemaName,
        SQLCHAR 		  *szProcName,
        SQLSMALLINT        cbProcName);

    SQLRETURN SQL_API CSQLSetPos(
        SQLHSTMT           hstmt,
        SQLSETPOSIROW      irow,
        SQLUSMALLINT       fOption,
        SQLUSMALLINT       fLock);

    SQLRETURN SQL_API CSQLTablePrivileges(
        SQLHSTMT           hstmt,
        SQLCHAR 		  *szCatalogName,
        SQLSMALLINT        cbCatalogName,
        SQLCHAR 		  *szSchemaName,
        SQLSMALLINT        cbSchemaName,
        SQLCHAR 		  *szTableName,
        SQLSMALLINT        cbTableName);

    SQLRETURN SQL_API CSQLDrivers(
        SQLHENV            henv,
        SQLUSMALLINT       fDirection,
        SQLCHAR 		  *szDriverDesc,
        SQLSMALLINT        cbDriverDescMax,
        SQLSMALLINT 	  *pcbDriverDesc,
        SQLCHAR 		  *szDriverAttributes,
        SQLSMALLINT        cbDrvrAttrMax,
        SQLSMALLINT 	  *pcbDrvrAttr);

    SQLRETURN SQL_API CSQLBindParameter(
        SQLHSTMT           hstmt,
        SQLUSMALLINT       ipar,
        SQLSMALLINT        fParamType,
        SQLSMALLINT        fCType,
        SQLSMALLINT        fSqlType,
        SQLULEN            cbColDef,
        SQLSMALLINT        ibScale,
        SQLPOINTER         rgbValue,
        SQLLEN             cbValueMax,
        SQLLEN 		      *pcbValue);


#if (ODBCVER >= 0x0300)
    SQLRETURN SQL_API CSQLAllocHandleStd(
        SQLSMALLINT		fHandleType,
        SQLHANDLE		hInput,
        SQLHANDLE	   *phOutput);
#endif
/*      Deprecated functions from prior versions of ODBC */
    SQLRETURN SQL_API CSQLSetScrollOptions(    /*      Use SQLSetStmtOptions */
        SQLHSTMT           hstmt,
        SQLUSMALLINT       fConcurrency,
        SQLLEN             crowKeyset,
        SQLUSMALLINT       crowRowset);
};

class R_index {
public:
	R_index(){

	}
	~R_index(){

	}
	std::string CONSTRAINT_NAME;
	std::string TABLE_CATALOG;
	std::string TABLE_SCHEMA;
	std::string TABLE_NAME;
	std::string COLUMN_NAME;
	SQLINTEGER ORDINAL_POSITION;
};

class R_table {
public:
	R_table(){
		Initialize();
	}
	~R_table(){

	}
	void Initialize(){
		TABLE_CATALOG = "";
		TABLE_SCHEMA = "";
		TABLE_NAME = "";
		COLUMN_NAME = "";
		ORDINAL_POSITION = 0;
		COLUMN_DEFAULT = "";
		IS_NULLABLE = "";
		DATA_TYPE = "";
		CHARACTER_MAXIMUM_LENGTH = 0;
		CHARACTER_OCTET_LENGTH = 0;
		NUMERIC_PRECISION = 0;
		NUMERIC_SCALE = 0;
		DATETIME_PRECISION = 0;
		CHARACTER_SET_NAME = "";
		COLLATION_NAME = "";
		m_type = eSqlType::_unknown;
	}
	std::string TABLE_CATALOG;
	std::string TABLE_SCHEMA;
	std::string TABLE_NAME;
	std::string COLUMN_NAME;
	SQLINTEGER ORDINAL_POSITION;
	std::string COLUMN_DEFAULT;
	std::string IS_NULLABLE;
	std::string DATA_TYPE;
	SQLINTEGER CHARACTER_MAXIMUM_LENGTH;
	SQLINTEGER CHARACTER_OCTET_LENGTH;
	SQLINTEGER NUMERIC_PRECISION;
	SQLINTEGER NUMERIC_SCALE;
	SQLINTEGER DATETIME_PRECISION;
	std::string CHARACTER_SET_NAME;
	std::string COLLATION_NAME;
	eSqlType m_type;
};
class OdbcParameter {
public:
	OdbcParameter(const std::type_info& typ,void *value) {
		m_p = value;
	}
	~OdbcParameter(){
		
	}
	std::type_info *m_type;
	void *m_p;
};
class OdbcConnection{
public:
	OdbcConnection(){
		m_psql = new COdbcsql();
		SQLRETURN retcode;
		if (m_psql)	{
			retcode = m_psql->CSQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_henv);
			retcode = m_psql->CSQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);
			retcode = m_psql->CSQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc);
			// Set login timeout to 5 seconds
			retcode = m_psql->CSQLSetConnectAttr(m_hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
		}
		m_driver = "";
	}
	~OdbcConnection(){
		if (m_psql)		
			delete m_psql;
	}
	COdbcsql * m_psql;
	std::string Get_Driver(){ return m_driver; }
	void Set_Driver(std::string driver){ m_driver = driver; }
	std::string Get_Server() { return m_server; }
	void Set_Server(std::string server){ m_server = server; }
	std::string Get_Database() { return m_database; }
	void Set_Database(std::string database){ m_database = database; }
	std::string Get_UserID() { return m_user; }
	void Set_UserID(std::string UserID){ m_user = UserID; }
	std::string Get_Password() { return m_password; }
	void Set_Password(std::string Password){ m_password = Password; }
	SQLRETURN DriverConnect(){
		SQLCHAR outstr[2048];
		SQLSMALLINT outstrlen = 2048;
		std::string connctionstring = Get_ConnectionString();
		SQLRETURN retcode = m_psql->CSQLDriverConnect(m_hdbc, NULL, (SQLCHAR*)connctionstring.c_str(), SQL_NTS, outstr, sizeof(outstr), &outstrlen, SQL_DRIVER_NOPROMPT);
		return retcode;
	}
	std::string Get_ConnectionString(){
		std::string ret = 
			"DRIVER={" + m_driver + 
			"};SERVER=" + m_server + 
			";DATABASE=" + m_database + 
			";UID=" + m_user +
			";PWD=" + m_password + ";";
		return ret;
	}
	SQLHENV Get_EnvironmentHandle(){ return m_henv; }
	SQLHDBC Get_ConnectionHandle(){ return m_hdbc; }
protected:
	SQLHENV   m_henv  = SQL_NULL_HENV;   // Environment
	SQLHDBC   m_hdbc  = SQL_NULL_HDBC;   // Connection handle
	SQLHSTMT  m_hstmt = SQL_NULL_HSTMT;  // Statement handle
	std::string m_driver;
	std::string m_server;
	std::string m_database;
	std::string m_user;
	std::string m_password;
	std::string m_ConnectionString;
};
class OdbcCommand {
public:
	OdbcCommand(OdbcConnection *pcon){
		_con = pcon;
		_sql = _con->m_psql;
		m_CommandString = "";
		m_henv = _con->Get_EnvironmentHandle();
		m_hdbc = _con->Get_ConnectionHandle();
		_sql->CSQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt);
	}
	~OdbcCommand(){
		if(m_hstmt != SQL_NULL_HSTMT){
			_sql->CSQLFreeStmt(m_hstmt,0);
			m_hstmt = SQL_NULL_HSTMT;
		}
	}
	SQLRETURN SQLBindParameter(
        SQLUSMALLINT       ipar,
        SQLSMALLINT        fParamType,
        SQLSMALLINT        fCType,
        SQLSMALLINT        fSqlType,
        SQLULEN            cbColDef,
        SQLSMALLINT        ibScale,
        SQLPOINTER         rgbValue,
        SQLLEN             cbValueMax,
        SQLLEN 		      *pcbValue){
		return _sql->CSQLBindParameter(m_hstmt,ipar, fParamType, fCType, fSqlType, cbColDef, ibScale, rgbValue, cbValueMax, pcbValue);
		}

	SQLRETURN Direct(){
		SQLRETURN ret;
		ret = _sql->CSQLExecDirect(m_hstmt,	(SQLCHAR*) m_CommandString.c_str(), SQL_NTS);
		return ret;
	}
	SQLRETURN Direct(std::string command){
		m_CommandString = command;
		return Direct();
	}
	SQLRETURN SQLPrepare(){
		SQLINTEGER length = (SQLINTEGER)m_CommandString.length();
		SQLRETURN ret =	_sql->CSQLPrepare(m_hstmt,(SQLCHAR*)m_CommandString.c_str(), length );
		return ret;
	}
	SQLRETURN SQLPrepare(std::string command){
		m_CommandString = command;
		return this->SQLPrepare();
	}
	SQLRETURN SQLExecute(){
		return _sql->CSQLExecute(m_hstmt);
	}
	SQLRETURN SQLExecute(int count, ...){
		va_list ap;
		va_start(ap, count);
		va_end(ap);
		return _sql->CSQLExecute(m_hstmt);
	}
	SQLHSTMT Get_StatementHandle () { return m_hstmt; }
	// member
	std::string m_CommandString;

protected:
	SQLHENV   m_henv  = SQL_NULL_HENV;   // Environment
	SQLHDBC   m_hdbc  = SQL_NULL_HDBC;   // Connection handle
	SQLHSTMT  m_hstmt = SQL_NULL_HSTMT;  // Statement handle
private:
	COdbcsql	*_sql;
	OdbcConnection	*_con;
};

#endif
