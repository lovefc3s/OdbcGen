#include <stdio.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>
#include <string.h>
#include "odbcsql.h"
#define RESULT_LEN  2048

#define CHECK_ERROR(e, s, h, t) ({ if (e!=SQL_SUCCESS && e != SQL_SUCCESS_WITH_INFO) {extract_error(s, h, t); goto exit;} })
COdbcsql::COdbcsql(){

}
COdbcsql::~COdbcsql(){
    
}

SQLHANDLE  COdbcsql::get_SQLHANDLE(SQLSMALLINT HandleType){
	if (HandleType == SQL_HANDLE_ENV) {return henv;}
	if (HandleType == SQL_HANDLE_DBC) {return hdbc;}
	if (HandleType == SQL_HANDLE_STMT) { return (SQLHANDLE) hstmt;}
	return 0;
}

SQLRETURN  SQL_API COdbcsql::CSQLAllocConnect(SQLHENV EnvironmentHandle, SQLHDBC *ConnectionHandle){
    return SQLAllocConnect(EnvironmentHandle, ConnectionHandle);
}
SQLRETURN  SQL_API COdbcsql::CSQLAllocEnv(SQLHENV *EnvironmentHandle){
    return SQLAllocEnv(EnvironmentHandle);
}

#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API COdbcsql::CSQLAllocHandle(SQLSMALLINT HandleType, SQLHANDLE InputHandle, SQLHANDLE *OutputHandle){
    retcode = SQLAllocHandle( HandleType, InputHandle, OutputHandle);
	if (HandleType == SQL_HANDLE_ENV) {henv = *OutputHandle;}
	if (HandleType == SQL_HANDLE_DBC) {hdbc = *OutputHandle;}
	if (HandleType == SQL_HANDLE_STMT) {hstmt = *OutputHandle;}
	return retcode;
}
#endif
SQLRETURN  SQL_API COdbcsql::CSQLAllocStmt(SQLHDBC ConnectionHandle, SQLHSTMT *StatementHandle){
    return SQLAllocStmt( ConnectionHandle, StatementHandle);
}
SQLRETURN  SQL_API COdbcsql::CSQLBindCol(SQLHSTMT StatementHandle, SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValue, SQLLEN BufferLength, SQLLEN *StrLen_or_Ind){
    return SQLBindCol( StatementHandle, ColumnNumber, TargetType, TargetValue, BufferLength, StrLen_or_Ind);
}

#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API COdbcsql::CSQLBindParam(SQLHSTMT StatementHandle, SQLUSMALLINT ParameterNumber, SQLSMALLINT ValueType, SQLSMALLINT ParameterType, SQLULEN LengthPrecision, SQLSMALLINT ParameterScale, SQLPOINTER ParameterValue, SQLLEN *StrLen_or_Ind){
    return SQLBindParam( StatementHandle, ParameterNumber, ValueType, ParameterType, LengthPrecision, ParameterScale, ParameterValue, StrLen_or_Ind);
}
#endif

SQLRETURN  SQL_API COdbcsql::CSQLCancel(SQLHSTMT StatementHandle){
    return SQLCancel( StatementHandle);
}

#if (ODBCVER >= 0x0380)
SQLRETURN  SQL_API COdbcsql::CSQLCancelHandle(SQLSMALLINT HandleType, SQLHANDLE InputHandle){
    return 0;//SQLCancelHandle( HandleType, InputHandle);
}
#endif 

#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API COdbcsql::CSQLCloseCursor(SQLHSTMT StatementHandle){
    return SQLCloseCursor( StatementHandle);
}

SQLRETURN  SQL_API COdbcsql::CSQLColAttribute(SQLHSTMT StatementHandle,
	SQLUSMALLINT ColumnNumber, SQLUSMALLINT FieldIdentifier,
	SQLPOINTER CharacterAttribute, SQLSMALLINT BufferLength,
	SQLSMALLINT *StringLength, SQLLEN *NumericAttribute ){
	return SQLColAttribute(StatementHandle, ColumnNumber, FieldIdentifier, CharacterAttribute, BufferLength, StringLength, NumericAttribute );
}

	/* spec says (SQLPOINTER) not (SQLEN*) - PAH */
	/* Ms now say SQLLEN* 
		http://msdn.microsoft.com/library/en-us/odbc/htm/dasdkodbcoverview_64bit.asp - NG */
#endif

SQLRETURN  SQL_API COdbcsql::CSQLColumns(SQLHSTMT StatementHandle,
	SQLCHAR *CatalogName, SQLSMALLINT NameLength1,
	SQLCHAR *SchemaName, SQLSMALLINT NameLength2,
	SQLCHAR *TableName, SQLSMALLINT NameLength3,
	SQLCHAR *ColumnName, SQLSMALLINT NameLength4){
		return SQLColumns( StatementHandle,	CatalogName, NameLength1, SchemaName, NameLength2, TableName, NameLength3, ColumnName, NameLength4);
}


SQLRETURN  SQL_API COdbcsql::CSQLConnect(SQLHDBC ConnectionHandle,
	SQLCHAR *ServerName, SQLSMALLINT NameLength1,
	SQLCHAR *UserName, SQLSMALLINT NameLength2,
	SQLCHAR *Authentication, SQLSMALLINT NameLength3){
		return SQLConnect(ConnectionHandle, ServerName, NameLength1, UserName, NameLength2, Authentication, NameLength3);
}

#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API COdbcsql::CSQLCopyDesc(SQLHDESC SourceDescHandle,
	SQLHDESC TargetDescHandle){
		return SQLCopyDesc( SourceDescHandle, TargetDescHandle);
}
#endif

SQLRETURN  SQL_API COdbcsql::CSQLDataSources(SQLHENV EnvironmentHandle,
	SQLUSMALLINT Direction, SQLCHAR *ServerName,
	SQLSMALLINT BufferLength1, SQLSMALLINT *NameLength1,
	SQLCHAR *Description, SQLSMALLINT BufferLength2,
	SQLSMALLINT *NameLength2){
		return SQLDataSources( EnvironmentHandle, Direction, ServerName, BufferLength1, NameLength1, Description, BufferLength2, NameLength2);
}

SQLRETURN  SQL_API COdbcsql::CSQLDescribeCol(SQLHSTMT StatementHandle,
	SQLUSMALLINT ColumnNumber, SQLCHAR *ColumnName,
	SQLSMALLINT BufferLength, SQLSMALLINT *NameLength,
	SQLSMALLINT *DataType, SQLULEN *ColumnSize,
	SQLSMALLINT *DecimalDigits, SQLSMALLINT *Nullable){
		return SQLDescribeCol( StatementHandle,	ColumnNumber, ColumnName, BufferLength, NameLength, DataType, ColumnSize, DecimalDigits, Nullable);
}
SQLRETURN  SQL_API COdbcsql::CSQLDisconnect(SQLHDBC ConnectionHandle){
	return SQLDisconnect(ConnectionHandle);
}

#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API COdbcsql::CSQLEndTran(SQLSMALLINT HandleType, SQLHANDLE Handle, SQLSMALLINT CompletionType){
	return SQLEndTran( HandleType, Handle, CompletionType);
}
#endif

SQLRETURN  SQL_API COdbcsql::CSQLError(SQLHENV EnvironmentHandle,
	SQLHDBC ConnectionHandle, SQLHSTMT StatementHandle,
	SQLCHAR *Sqlstate, SQLINTEGER *NativeError,
	SQLCHAR *MessageText, SQLSMALLINT BufferLength,
	SQLSMALLINT *TextLength) {
	return SQLError(EnvironmentHandle, ConnectionHandle, StatementHandle, Sqlstate, NativeError, MessageText, BufferLength, TextLength);
}

SQLRETURN  SQL_API COdbcsql::CSQLExecDirect(SQLHSTMT StatementHandle,
	SQLCHAR *StatementText, SQLINTEGER TextLength){
	return SQLExecDirect(StatementHandle, StatementText, TextLength);
}

SQLRETURN  SQL_API COdbcsql::CSQLExecute(SQLHSTMT StatementHandle){
	return SQLExecute(StatementHandle);
}

SQLRETURN  SQL_API COdbcsql::CSQLFetch(SQLHSTMT StatementHandle){
	return SQLFetch( StatementHandle);
}

#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API COdbcsql::CSQLFetchScroll(SQLHSTMT StatementHandle,
	SQLSMALLINT FetchOrientation, SQLLEN FetchOffset){
	return SQLFetchScroll( StatementHandle, FetchOrientation, FetchOffset);
}
#endif

SQLRETURN  SQL_API COdbcsql::CSQLFreeConnect(SQLHDBC ConnectionHandle){
	return SQLFreeConnect(ConnectionHandle);
}

SQLRETURN  SQL_API COdbcsql::CSQLFreeEnv(SQLHENV EnvironmentHandle){
	return SQLFreeEnv(EnvironmentHandle);
}

#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API COdbcsql::CSQLFreeHandle(SQLSMALLINT HandleType, SQLHANDLE Handle){
	return SQLFreeHandle(HandleType, Handle);
}
#endif

SQLRETURN  SQL_API COdbcsql::CSQLFreeStmt(SQLHSTMT StatementHandle,	SQLUSMALLINT Option){
	return SQLFreeStmt(StatementHandle,	Option);
}

#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API COdbcsql::CSQLGetConnectAttr(SQLHDBC ConnectionHandle,
	SQLINTEGER Attribute, SQLPOINTER Value,
	SQLINTEGER BufferLength, SQLINTEGER *StringLength){
	return SQLGetConnectAttr(ConnectionHandle, Attribute, Value, BufferLength, StringLength);
}
#endif

SQLRETURN  SQL_API COdbcsql::CSQLGetConnectOption(SQLHDBC ConnectionHandle,
	SQLUSMALLINT Option, SQLPOINTER Value){
	return SQLGetConnectOption(ConnectionHandle, Option, Value);
}

SQLRETURN  SQL_API COdbcsql::CSQLGetCursorName(SQLHSTMT StatementHandle,
	SQLCHAR *CursorName, SQLSMALLINT BufferLength,
	SQLSMALLINT *NameLength){
	return SQLGetCursorName(StatementHandle, CursorName, BufferLength, NameLength);
}

SQLRETURN  SQL_API COdbcsql::CSQLGetData(SQLHSTMT StatementHandle,
	SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType,
	SQLPOINTER TargetValue, SQLLEN BufferLength,
	SQLLEN *StrLen_or_Ind){
	return SQLGetData( StatementHandle,	ColumnNumber, TargetType, TargetValue, BufferLength, StrLen_or_Ind);
}

#if (ODBCVER >= 0x0300)
SQLRETURN   COdbcsql::CSQLGetDescField(SQLHDESC DescriptorHandle,
	SQLSMALLINT RecNumber, SQLSMALLINT FieldIdentifier,
	SQLPOINTER Value, SQLINTEGER BufferLength,
	SQLINTEGER *StringLength){
	return SQLGetDescField( DescriptorHandle, RecNumber, FieldIdentifier, Value, BufferLength, StringLength);	
}

SQLRETURN  SQL_API COdbcsql::CSQLGetDescRec(SQLHDESC DescriptorHandle,
	SQLSMALLINT RecNumber, SQLCHAR *Name,
	SQLSMALLINT BufferLength, SQLSMALLINT *StringLength,
	SQLSMALLINT *Type, SQLSMALLINT *SubType,
	SQLLEN *Length, SQLSMALLINT *Precision,
	SQLSMALLINT *Scale, SQLSMALLINT *Nullable){
	return SQLGetDescRec( DescriptorHandle, RecNumber, Name, BufferLength, StringLength, Type, SubType, Length, Precision, Scale, Nullable);
}

SQLRETURN  SQL_API COdbcsql::CSQLGetDiagField(SQLSMALLINT HandleType, SQLHANDLE Handle,
	SQLSMALLINT RecNumber, SQLSMALLINT DiagIdentifier,
	SQLPOINTER DiagInfo, SQLSMALLINT BufferLength,
	SQLSMALLINT *StringLength){
	return SQLGetDiagField(HandleType, Handle, RecNumber, DiagIdentifier, DiagInfo, BufferLength, StringLength);
}

SQLRETURN  SQL_API COdbcsql::CSQLGetDiagRec(SQLSMALLINT HandleType, SQLHANDLE Handle,
	SQLSMALLINT RecNumber, SQLCHAR *Sqlstate,
	SQLINTEGER *NativeError, SQLCHAR *MessageText,
	SQLSMALLINT BufferLength, SQLSMALLINT *TextLength){
	return SQLGetDiagRec(HandleType, Handle, RecNumber, Sqlstate, NativeError, MessageText, BufferLength, TextLength);
}

SQLRETURN  SQL_API COdbcsql::CSQLGetEnvAttr(SQLHENV EnvironmentHandle,
	SQLINTEGER Attribute, SQLPOINTER Value,
	SQLINTEGER BufferLength, SQLINTEGER *StringLength){
	return SQLGetEnvAttr( EnvironmentHandle, Attribute, Value, BufferLength, StringLength);
}
#endif  /* ODBCVER >= 0x0300 */

SQLRETURN  SQL_API COdbcsql::CSQLGetFunctions(SQLHDBC ConnectionHandle, SQLUSMALLINT FunctionId, SQLUSMALLINT *Supported){
	return SQLGetFunctions( ConnectionHandle, FunctionId, Supported);
}

SQLRETURN  SQL_API COdbcsql::CSQLGetInfo(SQLHDBC ConnectionHandle,
	SQLUSMALLINT InfoType, SQLPOINTER InfoValue,
	SQLSMALLINT BufferLength, SQLSMALLINT *StringLength){
	return SQLGetInfo(ConnectionHandle, InfoType, InfoValue, BufferLength, StringLength);
}

#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API COdbcsql::CSQLGetStmtAttr(SQLHSTMT StatementHandle,
	SQLINTEGER Attribute, SQLPOINTER Value,
	SQLINTEGER BufferLength, SQLINTEGER *StringLength){
	return SQLGetStmtAttr(StatementHandle, Attribute, Value, BufferLength, StringLength);
}
#endif  /* ODBCVER >= 0x0300 */

SQLRETURN  SQL_API COdbcsql::CSQLGetStmtOption(SQLHSTMT StatementHandle,
	SQLUSMALLINT Option, SQLPOINTER Value){
	return SQLGetStmtOption( StatementHandle, Option, Value);
}

SQLRETURN  SQL_API COdbcsql::CSQLGetTypeInfo(SQLHSTMT StatementHandle, SQLSMALLINT DataType){
	return SQLGetTypeInfo(StatementHandle, DataType);
}

SQLRETURN  SQL_API COdbcsql::CSQLNumResultCols(SQLHSTMT StatementHandle,
	SQLSMALLINT *ColumnCount){
	return SQLNumResultCols( StatementHandle, ColumnCount);
}

SQLRETURN  SQL_API COdbcsql::CSQLParamData(SQLHSTMT StatementHandle, SQLPOINTER *Value){
	return SQLParamData(StatementHandle, Value);
}

SQLRETURN  SQL_API COdbcsql::CSQLPrepare(SQLHSTMT StatementHandle,
	SQLCHAR *StatementText, SQLINTEGER TextLength){
	return SQLPrepare(StatementHandle, StatementText, TextLength);
}

SQLRETURN  SQL_API COdbcsql::CSQLPutData(SQLHSTMT StatementHandle, SQLPOINTER Data, SQLLEN StrLen_or_Ind){
	return SQLPutData(StatementHandle, Data, StrLen_or_Ind);
}

SQLRETURN  SQL_API COdbcsql::CSQLRowCount(SQLHSTMT StatementHandle, SQLLEN *RowCount){
	return SQLRowCount(StatementHandle, RowCount);
}

#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API COdbcsql::CSQLSetConnectAttr(SQLHDBC ConnectionHandle,
	SQLINTEGER Attribute, SQLPOINTER Value,
	SQLINTEGER StringLength){
	return SQLSetConnectAttr(ConnectionHandle, Attribute, Value, StringLength);
}
#endif /* ODBCVER >= 0x0300 */

SQLRETURN  SQL_API COdbcsql::CSQLSetConnectOption(SQLHDBC ConnectionHandle, SQLUSMALLINT Option, SQLULEN Value){
	return SQLSetConnectOption( ConnectionHandle, Option, Value);
}

SQLRETURN  SQL_API COdbcsql::CSQLSetCursorName(SQLHSTMT StatementHandle,
									SQLCHAR *CursorName, SQLSMALLINT NameLength){
	return SQLSetCursorName(StatementHandle, CursorName, NameLength);
}

#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API COdbcsql::CSQLSetDescField(SQLHDESC DescriptorHandle,
	SQLSMALLINT RecNumber, SQLSMALLINT FieldIdentifier,
	SQLPOINTER Value, SQLINTEGER BufferLength){
	return SQLSetDescField(DescriptorHandle, RecNumber, FieldIdentifier, Value, BufferLength);
}

SQLRETURN  SQL_API COdbcsql::CSQLSetDescRec(SQLHDESC DescriptorHandle,
									SQLSMALLINT RecNumber, SQLSMALLINT Type,
									SQLSMALLINT SubType, SQLLEN Length,
									SQLSMALLINT Precision, SQLSMALLINT Scale,
									SQLPOINTER Data, SQLLEN *StringLength,
									SQLLEN *Indicator){
	return SQLSetDescRec(DescriptorHandle, RecNumber, Type, SubType, Length, Precision, Scale, Data, StringLength, Indicator);
}

SQLRETURN  SQL_API COdbcsql::CSQLSetEnvAttr(SQLHENV EnvironmentHandle,
									SQLINTEGER Attribute, SQLPOINTER Value,
									SQLINTEGER StringLength){
	return SQLSetEnvAttr(EnvironmentHandle, Attribute, Value, StringLength);
}
#endif /* ODBCVER >= 0x0300 */

SQLRETURN  SQL_API COdbcsql::CSQLSetParam(SQLHSTMT StatementHandle,
								SQLUSMALLINT ParameterNumber, SQLSMALLINT ValueType,
								SQLSMALLINT ParameterType, SQLULEN LengthPrecision,
								SQLSMALLINT ParameterScale, SQLPOINTER ParameterValue,
								SQLLEN *StrLen_or_Ind){
	return SQLSetParam( StatementHandle, ParameterNumber, ValueType, ParameterType, LengthPrecision,
			ParameterScale, ParameterValue,	StrLen_or_Ind);
}

#if (ODBCVER >= 0x0300)
SQLRETURN  SQL_API COdbcsql::CSQLSetStmtAttr(SQLHSTMT StatementHandle,
									SQLINTEGER Attribute, SQLPOINTER Value,
									SQLINTEGER StringLength){
	return SQLSetStmtAttr(StatementHandle, Attribute, Value, StringLength);
}
#endif

SQLRETURN  SQL_API COdbcsql::CSQLSetStmtOption(SQLHSTMT StatementHandle,
									SQLUSMALLINT Option, SQLULEN Value){
	return SQLSetStmtOption(StatementHandle, Option, Value);
}

SQLRETURN  SQL_API COdbcsql::CSQLSpecialColumns(SQLHSTMT StatementHandle,
										SQLUSMALLINT IdentifierType, SQLCHAR *CatalogName,
										SQLSMALLINT NameLength1, SQLCHAR *SchemaName,
										SQLSMALLINT NameLength2, SQLCHAR *TableName,
										SQLSMALLINT NameLength3, SQLUSMALLINT Scope,
										SQLUSMALLINT Nullable){
	return SQLSpecialColumns(StatementHandle,
							IdentifierType, CatalogName,
							NameLength1, SchemaName,
							NameLength2, TableName,
							NameLength3, Scope,
							Nullable);
}

SQLRETURN  SQL_API COdbcsql::CSQLStatistics(SQLHSTMT StatementHandle,
									SQLCHAR *CatalogName, SQLSMALLINT NameLength1,
									SQLCHAR *SchemaName, SQLSMALLINT NameLength2,
									SQLCHAR *TableName, SQLSMALLINT NameLength3,
									SQLUSMALLINT Unique, SQLUSMALLINT Reserved){
	return SQLStatistics(StatementHandle,
						CatalogName, NameLength1,
						SchemaName, NameLength2,
						TableName, NameLength3,
						Unique, Reserved);
}

SQLRETURN   SQL_API COdbcsql::CSQLTables(SQLHSTMT StatementHandle,
								SQLCHAR *CatalogName, SQLSMALLINT NameLength1,
								SQLCHAR *SchemaName, SQLSMALLINT NameLength2,
								SQLCHAR *TableName, SQLSMALLINT NameLength3,
								SQLCHAR *TableType, SQLSMALLINT NameLength4){
	return SQLTables(StatementHandle,
					CatalogName, NameLength1,
					SchemaName, NameLength2,
					TableName, NameLength3,
					TableType, NameLength4);
}

SQLRETURN  SQL_API COdbcsql::CSQLTransact(SQLHENV EnvironmentHandle,
								SQLHDBC ConnectionHandle, SQLUSMALLINT CompletionType){
	return SQLTransact(EnvironmentHandle,
				ConnectionHandle, CompletionType);
}

SQLRETURN SQL_API COdbcsql::CSQLDriverConnect(
	SQLHDBC            hdbc,
	SQLHWND            hwnd,
	SQLCHAR 		  *szConnStrIn,
	SQLSMALLINT        cbConnStrIn,
	SQLCHAR           *szConnStrOut,
	SQLSMALLINT        cbConnStrOutMax,
	SQLSMALLINT 	  *pcbConnStrOut,
	SQLUSMALLINT       fDriverCompletion){
	return SQLDriverConnect(
		hdbc,
		hwnd,
		szConnStrIn,
		cbConnStrIn,
		szConnStrOut,
		cbConnStrOutMax,
		pcbConnStrOut,
		fDriverCompletion);
}


SQLRETURN SQL_API COdbcsql::CSQLBrowseConnect(
	SQLHDBC            hdbc,
	SQLCHAR 		  *szConnStrIn,
	SQLSMALLINT        cbConnStrIn,
	SQLCHAR 		  *szConnStrOut,
	SQLSMALLINT        cbConnStrOutMax,
	SQLSMALLINT       *pcbConnStrOut){
	return SQLBrowseConnect(
		hdbc,
		szConnStrIn,
		cbConnStrIn,
		szConnStrOut,
		cbConnStrOutMax,
		pcbConnStrOut);
}

#if (ODBCVER >= 0x0300)
SQLRETURN	SQL_API COdbcsql::CSQLBulkOperations(
	SQLHSTMT			StatementHandle,
	SQLSMALLINT			Operation){
	return SQLBulkOperations(
		StatementHandle,
		Operation);
}

#endif  /* ODBCVER >= 0x0300 */

SQLRETURN SQL_API COdbcsql::CSQLColAttributes(
	SQLHSTMT           hstmt,
	SQLUSMALLINT       icol,
	SQLUSMALLINT       fDescType,
	SQLPOINTER         rgbDesc,
	SQLSMALLINT        cbDescMax,
	SQLSMALLINT 	  *pcbDesc,
	SQLLEN 		      *pfDesc){
	return SQLColAttributes(
		hstmt,
		icol,
		fDescType,
		rgbDesc,
		cbDescMax,
		pcbDesc,
		pfDesc);
}


SQLRETURN SQL_API COdbcsql::CSQLColumnPrivileges(
	SQLHSTMT           hstmt,
	SQLCHAR 		  *szCatalogName,
	SQLSMALLINT        cbCatalogName,
	SQLCHAR 		  *szSchemaName,
	SQLSMALLINT        cbSchemaName,
	SQLCHAR 		  *szTableName,
	SQLSMALLINT        cbTableName,
	SQLCHAR 		  *szColumnName,
	SQLSMALLINT        cbColumnName){
	return SQLColumnPrivileges(
		hstmt,
		szCatalogName,
		cbCatalogName,
		szSchemaName,
		cbSchemaName,
		szTableName,
		cbTableName,
		szColumnName,
		cbColumnName);
}

SQLRETURN SQL_API COdbcsql::CSQLDescribeParam(
	SQLHSTMT           hstmt,
	SQLUSMALLINT       ipar,
	SQLSMALLINT 	  *pfSqlType,
	SQLULEN 	      *pcbParamDef,
	SQLSMALLINT 	  *pibScale,
	SQLSMALLINT 	  *pfNullable){
	return SQLDescribeParam(
		hstmt,
		ipar,
		pfSqlType,
		pcbParamDef,
		pibScale,
		pfNullable);
}


SQLRETURN SQL_API COdbcsql::CSQLExtendedFetch(
	SQLHSTMT           hstmt,
	SQLUSMALLINT       fFetchType,
	SQLLEN             irow,
	SQLULEN 	  	   *pcrow,
	SQLUSMALLINT 	   *rgfRowStatus){
	return SQLExtendedFetch(
		hstmt,
		fFetchType,
		irow,
		pcrow,
		rgfRowStatus);
}


SQLRETURN SQL_API COdbcsql::CSQLForeignKeys(
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
	SQLSMALLINT        cbFkTableName){
	return SQLForeignKeys(
		hstmt,
		szPkCatalogName,
		cbPkCatalogName,
		szPkSchemaName,
		cbPkSchemaName,
		szPkTableName,
		cbPkTableName,
		szFkCatalogName,
		cbFkCatalogName,
		szFkSchemaName,
		cbFkSchemaName,
		szFkTableName,
		cbFkTableName);
}

SQLRETURN SQL_API COdbcsql::CSQLMoreResults(
	SQLHSTMT           hstmt){
	return SQLMoreResults(hstmt);
}

SQLRETURN SQL_API COdbcsql::CSQLNativeSql(
	SQLHDBC            hdbc,
	SQLCHAR 		  *szSqlStrIn,
	SQLINTEGER         cbSqlStrIn,
	SQLCHAR 		  *szSqlStr,
	SQLINTEGER         cbSqlStrMax,
	SQLINTEGER 		  *pcbSqlStr){

	return SQLNativeSql(
		hdbc,
		szSqlStrIn,
		cbSqlStrIn,
		szSqlStr,
		cbSqlStrMax,
		pcbSqlStr);
}

SQLRETURN SQL_API COdbcsql::CSQLNumParams(
	SQLHSTMT           hstmt,
	SQLSMALLINT 	  *pcpar){
	return SQLNumParams( hstmt, pcpar);
}


SQLRETURN SQL_API COdbcsql::CSQLParamOptions(
	SQLHSTMT           hstmt,
	SQLULEN        	   crow,
	SQLULEN 	  	   *pirow){
	return SQLParamOptions(
		hstmt,
		crow,
		pirow);
}

SQLRETURN SQL_API COdbcsql::CSQLPrimaryKeys(
	SQLHSTMT           hstmt,
	SQLCHAR 		  *szCatalogName,
	SQLSMALLINT        cbCatalogName,
	SQLCHAR 		  *szSchemaName,
	SQLSMALLINT        cbSchemaName,
	SQLCHAR 		  *szTableName,
	SQLSMALLINT        cbTableName){
	return SQLPrimaryKeys(
		hstmt,
		szCatalogName,
		cbCatalogName,
		szSchemaName,
		cbSchemaName,
		szTableName,
		cbTableName);
}


SQLRETURN SQL_API COdbcsql::CSQLProcedureColumns(
	SQLHSTMT           hstmt,
	SQLCHAR 		  *szCatalogName,
	SQLSMALLINT        cbCatalogName,
	SQLCHAR 		  *szSchemaName,
	SQLSMALLINT        cbSchemaName,
	SQLCHAR 		  *szProcName,
	SQLSMALLINT        cbProcName,
	SQLCHAR 		  *szColumnName,
	SQLSMALLINT        cbColumnName){
	return SQLProcedureColumns(
		hstmt,
		szCatalogName,
		cbCatalogName,
		szSchemaName,
		cbSchemaName,
		szProcName,
		cbProcName,
		szColumnName,
		cbColumnName);
}

SQLRETURN SQL_API COdbcsql::CSQLProcedures(
	SQLHSTMT           hstmt,
	SQLCHAR 		  *szCatalogName,
	SQLSMALLINT        cbCatalogName,
	SQLCHAR 		  *szSchemaName,
	SQLSMALLINT        cbSchemaName,
	SQLCHAR 		  *szProcName,
	SQLSMALLINT        cbProcName){
	return SQLProcedures(
		hstmt,
		szCatalogName,
		cbCatalogName,
		szSchemaName,
		cbSchemaName,
		szProcName,
		cbProcName);
}

SQLRETURN SQL_API COdbcsql::CSQLSetPos(
	SQLHSTMT           hstmt,
	SQLSETPOSIROW      irow,
	SQLUSMALLINT       fOption,
	SQLUSMALLINT       fLock){
	return SQLSetPos(
		hstmt,
		irow,
		fOption,
		fLock);
}

SQLRETURN SQL_API COdbcsql::CSQLTablePrivileges(
	SQLHSTMT           hstmt,
	SQLCHAR 		  *szCatalogName,
	SQLSMALLINT        cbCatalogName,
	SQLCHAR 		  *szSchemaName,
	SQLSMALLINT        cbSchemaName,
	SQLCHAR 		  *szTableName,
	SQLSMALLINT        cbTableName){
	return SQLTablePrivileges(
		hstmt,
		szCatalogName,
		cbCatalogName,
		szSchemaName,
		cbSchemaName,
		szTableName,
		cbTableName);
}

SQLRETURN SQL_API COdbcsql::CSQLDrivers(
	SQLHENV            henv,
	SQLUSMALLINT       fDirection,
	SQLCHAR 		  *szDriverDesc,
	SQLSMALLINT        cbDriverDescMax,
	SQLSMALLINT 	  *pcbDriverDesc,
	SQLCHAR 		  *szDriverAttributes,
	SQLSMALLINT        cbDrvrAttrMax,
	SQLSMALLINT 	  *pcbDrvrAttr){
	return SQLDrivers(
		henv,
		fDirection,
		szDriverDesc,
		cbDriverDescMax,
		pcbDriverDesc,
		szDriverAttributes,
		cbDrvrAttrMax,
		pcbDrvrAttr);
}

SQLRETURN SQL_API COdbcsql::CSQLBindParameter(
	SQLHSTMT           hstmt,
	SQLUSMALLINT       ipar,
	SQLSMALLINT        fParamType,
	SQLSMALLINT        fCType,
	SQLSMALLINT        fSqlType,
	SQLULEN            cbColDef,
	SQLSMALLINT        ibScale,
	SQLPOINTER         rgbValue,
	SQLLEN             cbValueMax,
	SQLLEN 		      *pcbValue){
	return SQLBindParameter(
		hstmt,
		ipar,
		fParamType,
		fCType,
		fSqlType,
		cbColDef,
		ibScale,
		rgbValue,
		cbValueMax,
		pcbValue);
}

#if (ODBCVER >= 0x0300)
SQLRETURN SQL_API COdbcsql::CSQLAllocHandleStd(
	SQLSMALLINT		fHandleType,
	SQLHANDLE		hInput,
	SQLHANDLE	   *phOutput){
	return SQLAllocHandleStd(
		fHandleType,
		hInput,
		phOutput);
}
#endif

/*      Deprecated functions from prior versions of ODBC */
SQLRETURN SQL_API COdbcsql::CSQLSetScrollOptions(    /*      Use SQLSetStmtOptions */
	SQLHSTMT           hstmt,
	SQLUSMALLINT       fConcurrency,
	SQLLEN             crowKeyset,
	SQLUSMALLINT       crowRowset){
	return SQLSetScrollOptions(
		hstmt,
		fConcurrency,
		crowKeyset,
		crowRowset);
}
