#include "stdafx.h"
#include "GenWindow.h"
using namespace std;

bool chk_multiple_startup(const gchar *process_name)
{
    FILE *fp;
    char str[256];
    int  ncnt;

    ncnt=0;
    sprintf(str,"ps x | grep %s",process_name);
    if ((fp=popen(str,"r"))==NULL)
        return(true);
    while(1){
        if(fgets(str,255,fp)==NULL){
            break;
        }
        if (strstr(str,"grep")==NULL)
            ncnt++;
        if(feof(fp)){
            break;
        }
    }
    pclose(fp);
    if (ncnt>1){
        return(false);
    }
    return(true);
 }

int member(R_table &rec,std::ofstream &file){
	int ret = 1;
	switch (rec.m_type)
	{
		case eSqlType::_unknown:
			ret = -1;
			break;
		case eSqlType::_bit:
			file << "\tSQLCHAR\t" + rec.COLUMN_NAME + ";\n";
			break;	
		case eSqlType::_tinyint:
		case eSqlType::_smallint:
			file << "\tshort\t" + rec.COLUMN_NAME + ";\n";
			break;	
		case eSqlType::_int:
			file << "\tSQLINTEGER\t" + rec.COLUMN_NAME + ";\n";
			break;
		//long long
		case eSqlType::_bigint:
			file << "\tlong long\t" + rec.COLUMN_NAME + ";\n";
			break;
		case eSqlType::_decimal:
		case eSqlType::_numeric:
			file << "\tSQL_NUMERIC_STRUCT\t" + rec.COLUMN_NAME + ";\n";
			break;
		case eSqlType::_real:
		case eSqlType::_float:
			file << "\tSQLFLOAT\t" + rec.COLUMN_NAME + ";\n";
			break;
		case eSqlType::_smallmoney:
		case eSqlType::_money:
			file << "\tSQL_NUMERIC_STRUCT\t" + rec.COLUMN_NAME + ";\n";
			break;
		case eSqlType::_date:
		case eSqlType::_time:
		case eSqlType::_datetime:
		case eSqlType::_datetime2:
		case eSqlType::_smalldatetime:
		case eSqlType::_datetimeoffset:
			file << "\tTIMESTAMP_STRUCT\t" + rec.COLUMN_NAME + ";\n";
			break;	
		case eSqlType::_char:
		case eSqlType::_varchar:
		case eSqlType::_text:
		case eSqlType::_nchar:
		case eSqlType::_nvarchar:
		case eSqlType::_ntext:
			file << "\tSQLCHAR*\t" + rec.COLUMN_NAME + ";\n";
			break;
		default:
			ret = -1;
			break;
	}
	return ret;
}
int outputlength(R_table &rec,std::ofstream &file){
	int ret = 1;
	int ilength;
	switch (rec.m_type)
	{
		case eSqlType::_unknown:
			ret = -1;
			break;
		case eSqlType::_bit:
			file << "\tSQLINTEGER\t" + rec.COLUMN_NAME + "_len\t= 1;\n";
			break;	
		case eSqlType::_tinyint:
		case eSqlType::_smallint:
			file << "\tSQLINTEGER\t" + rec.COLUMN_NAME + "_len\t= 2;\n";
			break;	
		case eSqlType::_int:
			file << "\tSQLINTEGER\t" + rec.COLUMN_NAME + "_len\t= 4;\n";
			break;
		//long long
		case eSqlType::_bigint:
			file << "\tSQLINTEGER\t" + rec.COLUMN_NAME + "_len\t= 8;\n";
			break;
		case eSqlType::_decimal:
		case eSqlType::_numeric:
			file << "\tSQLINTEGER\t" + rec.COLUMN_NAME + "_len" << dtab << "= sizeof(SQL_NUMERIC_STRUCT);" << dnew;
			break;
		case eSqlType::_real:
		case eSqlType::_float:
			file << "\tSQLINTEGER\t" + rec.COLUMN_NAME + "_len\t= 8;\n";
			break;
		case eSqlType::_smallmoney:
		case eSqlType::_money:
			file << "\tSQLINTEGER\t" + rec.COLUMN_NAME + "_len" << dtab << "= sizeof(SQL_NUMERIC_STRUCT);" << dnew;
			break;
		case eSqlType::_date:
		case eSqlType::_time:
		case eSqlType::_datetime:
		case eSqlType::_datetime2:
		case eSqlType::_smalldatetime:
		case eSqlType::_datetimeoffset:
			file << "\tSQLINTEGER\t" + rec.COLUMN_NAME + "_len" << dtab << "= sizeof(TIMESTAMP_STRUCT);" << dnew;
			break;
		case eSqlType::_char:
		case eSqlType::_varchar:
		case eSqlType::_text:
		case eSqlType::_nchar:
		case eSqlType::_nvarchar:
		case eSqlType::_ntext:
		{
			ilength = rec.CHARACTER_MAXIMUM_LENGTH;
			if (ilength > 4096)	ilength = 4096;
			file << "\tSQLINTEGER\t" + rec.COLUMN_NAME + "_len"	<< dtab	<< "= " << ilength << ";" << dnew;
			break;
		}
		default:
			ret = -1;
			break;
	}
	return ret;
}
int constructor(R_table &rec,std::ofstream &file){
	int ret = 1;
	switch (rec.m_type)
	{
		case eSqlType::_unknown:
			ret = -1;
			break;
		case eSqlType::_bit:
		case eSqlType::_tinyint:
		case eSqlType::_smallint:
		case eSqlType::_int:
		case eSqlType::_bigint:
			break;
		case eSqlType::_decimal:
		case eSqlType::_numeric:
			break;
		case eSqlType::_real:
		case eSqlType::_float:
			break;
		case eSqlType::_smallmoney:
		case eSqlType::_money:
		case eSqlType::_date:
		case eSqlType::_time:
		case eSqlType::_datetime:
		case eSqlType::_datetime2:
		case eSqlType::_smalldatetime:
		case eSqlType::_datetimeoffset:
			break;
		case eSqlType::_char:
		case eSqlType::_varchar:
		case eSqlType::_text:
		case eSqlType::_nchar:
		case eSqlType::_nvarchar:
		case eSqlType::_ntext:
		{
			ostringstream len;
			if(rec.CHARACTER_MAXIMUM_LENGTH > 4096)
				len << 4096;
			else
				len << rec.CHARACTER_MAXIMUM_LENGTH;
			file << "\t\t" + rec.COLUMN_NAME + "\t= new SQLCHAR[" + len.str() + "];\n";
			break;
		}
		default:
			ret = -1;
			break;
	}
	return ret;
}
int destructor(R_table &rec,std::ofstream &file){
	int ret = 1;
	switch (rec.m_type)
	{
		case eSqlType::_unknown:
			ret = -1;
			break;
		case eSqlType::_char:
		case eSqlType::_varchar:
		case eSqlType::_text:
		case eSqlType::_nchar:
		case eSqlType::_nvarchar:
		case eSqlType::_ntext:
			file << "\t\tdelete\t" + rec.COLUMN_NAME + ";\n";
			break;
		default:
			ret = -1;
			break;
	}
	return ret;
}

int initialize(R_table &rec,std::ofstream &file){
	int ret = 1;
	switch (rec.m_type)
	{
		case eSqlType::_unknown:
			ret = -1;
			break;
		case eSqlType::_bit:
		case eSqlType::_tinyint:
		case eSqlType::_smallint:
		case eSqlType::_int:
		case eSqlType::_bigint:
			file << "\t\t" + rec.COLUMN_NAME + "\t= 0;\n";
			break;	
		case eSqlType::_decimal:
		case eSqlType::_numeric:
			break;
		case eSqlType::_real:
		case eSqlType::_float:
			file << "\t\t" + rec.COLUMN_NAME + "\t= 0.0;\n";
			break;	
		case eSqlType::_smallmoney:
		case eSqlType::_money:
			break;
		case eSqlType::_date:
		case eSqlType::_time:
		case eSqlType::_datetime:
		case eSqlType::_datetime2:
		case eSqlType::_smalldatetime:
		case eSqlType::_datetimeoffset:
			break;	
		case eSqlType::_char:
		case eSqlType::_varchar:
		case eSqlType::_text:
		case eSqlType::_nchar:
		case eSqlType::_nvarchar:
		case eSqlType::_ntext:
			file << "\t\t*" + rec.COLUMN_NAME + "\t= 0;\n";
			break;
		default:
			ret = -1;
			break;
	}
	return ret;
}

void OutputWhere( string Keyname, std::vector<string> &Columns, std::ofstream &file){
	file << dtab << "std::string m_str" << Keyname << dtab << "= " << ddquo << " WHERE " << ddquo << dbsra;
	for (int i = 0;i<Columns.size();i++){
		if (i>0)
			file << ddquo << dbsra << dnew << dtab << dtab << ddquo << " AND ";
		else
			file << dnew << dtab << dtab << ddquo;
		
		std:: string column = Columns[i];
		file << column << " = ?";
	}
	file << ddquo << ";" << dnew;
}
int main(int argc, char** argv) {
    Gtk::Main kit(argc, argv);
    // multiple startup check
    const gchar *appname = g_get_application_name();
    if (!chk_multiple_startup(appname)){
        std::cout << "this application has already been started :"
                  << appname << std::endl;
        return 1;
    }
	//CR_t_kansei *pkansei = new CR_t_kansei();
	//CT_t_kansei *ptbl	= new CT_t_kansei();
	//ptbl->m_data.push_back(*pkansei);
	std::vector<string> sTypes = 
	{
		"bit",
		"tinyint",
		"smallint",
		"int",
		"bigint",
		"decimal",
		"numeric",
		"real",
		"float",
		"smallmoney",
		"money",
		"date",
		"time",
		"datetime",
		"datetime2",
		"smalldatetime",
		"datetimeoffset",
		"char",
		"varchar",
		"text",
		"nchar",
		"nvarchar",
		"ntext",
		"binary",
		"verbinary",
		"image",
		"xml"
	};
	GenWindow window;
	Gtk::Main::run(window);
	int i = 0;
	int len = 256;
	SQLCHAR	*pchar = nullptr;
	pchar = new SQLCHAR[len];
	OdbcConnection *p = new OdbcConnection();
	/*
	p->Set_Driver("ODBC Driver 17 for SQL Server");
	p->Set_Server("localhost");
	p->Set_Database("ootabe");
	p->Set_UserID("masamitsu");
	p->Set_Password("Daiki0620");
	int ret = (int)p->DriverConnect();
	*/
	string con = p->Get_ConnectionString();
	COdbcsql *_sql = p->m_psql;
	OdbcCommand	*com = new OdbcCommand(p);

	com->m_CommandString = "SELECT TABLE_CATALOG, TABLE_SCHEMA, TABLE_NAME, TABLE_TYPE FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_CATALOG = '" +
		p->Get_Database() + "';";
	SQLHSTMT  _hstmt = com->Get_StatementHandle();
	SQLRETURN retcode = com->Direct();
	SQLCHAR TABLE_CATALOG[256], TABLE_SCHEMA[256], TABLE_NAME[256], TABLE_TYPE[256];
	retcode = _sql->CSQLBindCol(_hstmt, 1, SQL_C_CHAR, TABLE_CATALOG, 256, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 2, SQL_C_CHAR, TABLE_SCHEMA, 256, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 3, SQL_C_CHAR, TABLE_NAME, 256, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 4, SQL_C_CHAR, TABLE_TYPE, 256, 0);
	vector<std::string> _tbl;
	std::string filename = p->Get_Database() + ".h";
	std::ofstream outputfile(filename);
	outputfile << "#include <sql.h>\n";
	outputfile << "#include <sqlext.h>\n";
	outputfile << "#include \"stdafx.h\"\n\n";
	for (int i = 0;;i++) {
		retcode = _sql->CSQLFetch(_hstmt);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			sprintf((char*)pchar,"%s",(char*)TABLE_NAME);
			std::string tbl = (char*)TABLE_NAME;
			_tbl.push_back(tbl);
			//_rec = *this;
		} else if (retcode != SQL_NO_DATA) {
		} else {
			break;
		}
	}
	delete com;
	delete[] pchar;
	com = nullptr;
	pchar = nullptr;
	for (int count = 0;count < _tbl.size();count++){
		com = new OdbcCommand(p);
		std::string tbl = _tbl[count];
		com->m_CommandString = "SELECT "\
//			" TABLE_CATALOG"\
//			",TABLE_SCHEMA"\
//			",TABLE_NAME"
			" COLUMN_NAME"
			",ORDINAL_POSITION"\
			",COLUMN_DEFAULT"\
			",IS_NULLABLE"\
			",DATA_TYPE"\
			",CHARACTER_MAXIMUM_LENGTH"\
			",CHARACTER_OCTET_LENGTH"\
			",NUMERIC_PRECISION"\
			",NUMERIC_SCALE"\
			",DATETIME_PRECISION"\
			",CHARACTER_SET_NAME"\
			",COLLATION_NAME"\
			" FROM INFORMATION_SCHEMA.COLUMNS"\
			" WHERE TABLE_CATALOG = '" + p->Get_Database() + "' AND TABLE_NAME = '" + tbl + "'"\
			" ORDER BY ORDINAL_POSITION;";

		std::string classname = "CR_"+ tbl;
		outputfile << "class\t" + classname + " {\n";
		outputfile << "public:\n";
		R_table rec;
		vector <R_table> v_tbl;
		SQLCHAR _TABLE_CATALOG[256];
		SQLCHAR _TABLE_SCHEMA[256];
		SQLCHAR _TABLE_NAME[256];
		SQLCHAR _COLUMN_NAME[256];
		SQLCHAR _COLUMN_DEFAULT[4096];
		SQLCHAR _IS_NULLABLE[256];
		SQLCHAR _DATA_TYPE[256];
		SQLCHAR _CHARACTER_SET_NAME[256];
		SQLCHAR _COLLATION_NAME[256];
		_hstmt = com->Get_StatementHandle();
		retcode = com->Direct();
//		retcode = _sql->CSQLBindCol(_hstmt, 1, SQL_C_CHAR, _TABLE_CATALOG, 128, 0);
//		retcode = _sql->CSQLBindCol(_hstmt, 2, SQL_C_CHAR, _TABLE_SCHEMA, 128, 0);
//		retcode = _sql->CSQLBindCol(_hstmt, 3, SQL_C_CHAR, _TABLE_NAME, 128, 0);
		retcode = _sql->CSQLBindCol(_hstmt, 1, SQL_C_CHAR, _COLUMN_NAME, 256, 0);
		retcode = _sql->CSQLBindCol(_hstmt, 2, SQL_C_LONG, &rec.ORDINAL_POSITION, 4, 0);
//		retcode = _sql->CSQLBindCol(_hstmt, 3, SQL_C_CHAR, _COLUMN_DEFAULT, 4096, 0);
//		retcode = _sql->CSQLBindCol(_hstmt, 4, SQL_C_CHAR, _IS_NULLABLE, 4, 0);
		retcode = _sql->CSQLBindCol(_hstmt, 5, SQL_C_CHAR, _DATA_TYPE, 256, 0);
/*		retcode = _sql->CSQLBindCol(_hstmt, 6, SQL_C_LONG, &rec.CHARACTER_MAXIMUM_LENGTH, 4, 0);
		retcode = _sql->CSQLBindCol(_hstmt, 7, SQL_C_LONG, &rec.CHARACTER_OCTET_LENGTH, 4, 0);
		retcode = _sql->CSQLBindCol(_hstmt, 8, SQL_C_TINYINT, &rec.NUMERIC_PRECISION, 2, 0);
		retcode = _sql->CSQLBindCol(_hstmt, 9, SQL_CVT_SMALLINT, &rec.NUMERIC_SCALE, 4, 0);
		retcode = _sql->CSQLBindCol(_hstmt, 10, SQL_CVT_SMALLINT, &rec.DATETIME_PRECISION, 4, 0);
		retcode = _sql->CSQLBindCol(_hstmt, 11, SQL_C_CHAR, _CHARACTER_SET_NAME, 128, 0);
		retcode = _sql->CSQLBindCol(_hstmt, 12, SQL_C_CHAR, _COLLATION_NAME, 128, 0);
		*/
		for (int i = 0;;i++) {
			std::string::size_type pos;
			rec.Initialize();
			retcode = _sql->CSQLFetch(_hstmt);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				printf("Result is: %s\n", (char*)_COLUMN_NAME);
				rec.COLUMN_NAME = (char*)_COLUMN_NAME;
				rec.DATA_TYPE = (char*)_DATA_TYPE;
				for(int _n = 0;_n<sTypes.size();_n++){
					if (rec.DATA_TYPE == sTypes[_n]) {
						rec.m_type = (eSqlType)_n;
						break;
					}
				}

				switch (rec.m_type){
					case eSqlType::_bit:
					case eSqlType::_tinyint:
					case eSqlType::_smallint:
					case eSqlType::_int:
					case eSqlType::_bigint:
					case eSqlType::_decimal:
					case eSqlType::_numeric:
					case eSqlType::_real:
					case eSqlType::_float:
					case eSqlType::_smallmoney:
					case eSqlType::_money:
					{
						retcode = _sql->CSQLGetData(_hstmt, 8, SQL_C_TINYINT, &rec.NUMERIC_PRECISION, 1, 0);
						retcode = _sql->CSQLGetData(_hstmt, 9, SQL_C_SSHORT, &rec.NUMERIC_SCALE, 2, 0);
						break;	
					}
					case eSqlType::_date:
					case eSqlType::_time:
					case eSqlType::_datetime:
					case eSqlType::_datetime2:
					case eSqlType::_smalldatetime:
					case eSqlType::_datetimeoffset:
					{
						retcode = _sql->CSQLGetData(_hstmt, 10, SQL_CVT_SMALLINT, &rec.DATETIME_PRECISION, 2, 0);
						break;	
					}
					case eSqlType::_char:
					case eSqlType::_varchar:
					case eSqlType::_text:
					case eSqlType::_nchar:
					case eSqlType::_nvarchar:
					case eSqlType::_ntext: {
						retcode = _sql->CSQLGetData(_hstmt, 6, SQL_C_LONG, &rec.CHARACTER_MAXIMUM_LENGTH, 4, 0);
						retcode = _sql->CSQLGetData(_hstmt, 7, SQL_C_LONG, &rec.CHARACTER_OCTET_LENGTH, 4, 0);
						break;
					}
				}

				v_tbl.push_back(rec);
			} else if (retcode != SQL_NO_DATA) {
			} else {
				break;
			}
		}
		//printf("%s\n",(const char*)com->m_CommandString.c_str());
		delete com;
		com = nullptr;
		for(int k = 0;k<v_tbl.size();k++){
			rec = v_tbl[k];
			//メンバー変数
			member(rec,outputfile);
		}
		outputfile << "\npublic:\n";
		outputfile << "\t" + classname + "() {\n";
		for(int k = 0;k<v_tbl.size();k++){
			rec = v_tbl[k];
			constructor(rec,outputfile);
		}
		outputfile << "\t\tInitialize();\n";
		outputfile << "\t}\n";
		outputfile << "\t~" + classname + "() {\n";
		for(int k = 0;k<v_tbl.size();k++){
			rec = v_tbl[k];
			destructor(rec,outputfile);
		}
		outputfile << "\t}\n";
		outputfile << "\tvoid Initialize() {\n";
		for(int k = 0;k<v_tbl.size();k++){
			rec = v_tbl[k];
			initialize(rec,outputfile);
		}
		outputfile << "\t}\n";
		outputfile << "};\n";
		outputfile << "\n";
		classname = "CT_" + tbl;
		outputfile << "class\t" + classname + " {\n";
		outputfile << "public:\n";
		outputfile << "\tstd::vector<CR_" + tbl + ">\tm_data;\n";
		outputfile << "public:\n";
		outputfile << "\tstd::string m_strSql = \n";
		outputfile << "\t\t\"SELECT \"\\\n";
		int siz = v_tbl.size();
		for(int k = 0;k<siz;k++){
			rec = v_tbl[k];
			outputfile << "\t\t\""+ rec.COLUMN_NAME;
			if (k==(siz-1))
				outputfile << " \"\\\n\t\t\"FROM " + tbl + " \";\n";
			else
				outputfile << ", \"" << dbsra << dnew;
		}
		//"SELECT CONSTRAINT_NAME,TABLE_CATALOG,TABLE_SCHEMA,TABLE_NAME, COLUMN_NAME, ORDINAL_POSITION FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE WHERE TABLE_NAME = ? ORDER BY CONSTRAINT_NAME,ORDINAL_POSITION;
		SQLCHAR CONSTRAINT_NAME[128],TABLE_CATALOG[128],TABLE_SCHEMA[128],TABLE_NAME[128], COLUMN_NAME[128];
		std::string str_NAME;
		std::string wk_NAME = "";
		SQLINTEGER ORDINAL_POSITION;
		com = new OdbcCommand(p);
		string strwk = "SELECT CONSTRAINT_NAME,TABLE_CATALOG,TABLE_SCHEMA,"\
			" TABLE_NAME, COLUMN_NAME, ORDINAL_POSITION FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE"\
			" WHERE TABLE_NAME = '%s' ORDER BY CONSTRAINT_NAME,ORDINAL_POSITION;";
		char * pstr = new char[1024];
		sprintf(pstr,strwk.c_str(),tbl.c_str());
		com->m_CommandString = "SELECT CONSTRAINT_NAME,TABLE_CATALOG,TABLE_SCHEMA,"\
			" TABLE_NAME, COLUMN_NAME, ORDINAL_POSITION FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE"\
			" WHERE TABLE_NAME = ? ORDER BY CONSTRAINT_NAME,ORDINAL_POSITION;";
//pstr;

		SQLLEN pramlength = (SQLLEN)tbl.length();
		delete pstr;
		pstr = nullptr;
		retcode = com->SQLPrepare();
		retcode = com->SQLBindParameter( 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, pramlength, 0, (SQLPOINTER)tbl.c_str(), 0, &pramlength); 
		_hstmt = com->Get_StatementHandle();
		retcode = _sql->CSQLBindCol(_hstmt, 1, SQL_C_CHAR, CONSTRAINT_NAME, 128, 0);
		//retcode = _sql->CSQLBindCol(_hstmt, 2, SQL_C_CHAR, TABLE_CATALOG, 128, 0);
		retcode = _sql->CSQLBindCol(_hstmt, 5, SQL_C_CHAR, COLUMN_NAME, 128, 0);
		retcode = com->SQLExecute();
		R_index idx;
		std::vector <std::string> columns;
		std::vector <R_index> IndexColumns;
		for (int i = 0;;i++) {
			retcode = _sql->CSQLFetch(_hstmt);
			if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
				std::string str_NAME = (char*)CONSTRAINT_NAME;
				if (str_NAME != wk_NAME){
					if (columns.size()>0){
						OutputWhere( wk_NAME, columns, outputfile);
						columns.clear();
					}
					wk_NAME = str_NAME;
				}
				std::string column = (char*)COLUMN_NAME;
				idx.CONSTRAINT_NAME = str_NAME;
				idx.COLUMN_NAME = column;
				columns.push_back(column);
				IndexColumns.push_back(idx);
			} else if (retcode != SQL_NO_DATA) {
			} else {
				break;
			}
		}
		if (columns.size()>0){
			OutputWhere( wk_NAME, columns, outputfile);
		}

		delete com;

		com = nullptr;
		outputfile << "private:\n";
		for(int k = 0;k<v_tbl.size();k++){
			rec = v_tbl[k];
			//長さ
			outputlength(rec,outputfile);
		}
		outputfile << "public:" << dnew;
		outputfile << dtab + classname + "() {" << dnew;
		outputfile << dtab << "}" << dnew;
		outputfile << dtab << "~" + classname + "() {" << dnew;
		outputfile << dtab << "}" << dnew;
		wk_NAME = "";
		for (int l = 0;l < IndexColumns.size();l++){
			idx = IndexColumns[l];
			if (idx.CONSTRAINT_NAME != wk_NAME){
				outputfile  << dtab << "std::string Get_SELECT_" << idx.CONSTRAINT_NAME <<
					"(){"  << dnew;
				outputfile << dtab << dtab << "return"	<< dtab << "m_strSql + m_str" + idx.CONSTRAINT_NAME << ";" <<dnew;
				outputfile << dtab << "}" << dnew;
				wk_NAME = idx.CONSTRAINT_NAME;
			}
		}
		outputfile << "};" << dnew;
		outputfile << dnew;
	}

	// SQLINTEGER key = 1158;
	// OdbcParameter parm(typeid(key),&key);
/*
	SQLHENV   _henv  = SQL_NULL_HENV;   // Environment
	SQLHDBC   _hdbc  = SQL_NULL_HDBC;   // Connection handle
	SQLHSTMT  _hstmt = SQL_NULL_HSTMT;  // Statement handle
	string strsql = "SELECT t_kansei.kk_id, t_kansei.kk_ynendo, t_kansei.kk_knendo, t_kansei.kk_syurui, t_kansei.kk_jvflg, t_kansei.kk_jvritsu, t_kansei.kk_ukeoi, "\
		" t_kansei.kk_kanmin, t_kansei.kk_ken, t_kansei.kk_shi, t_kansei.kk_tiku, t_kansei.kk_kaisi, t_kansei.kk_owari, t_kansei.kk_kingaku, t_kansei.kk_zei, "\
		" t_kansei.kk_goukei, t_kansei.kk_point, t_kansei.kk_ritsu, t_kansei.kk_key, t_kouji.km_name, t_kouji.km_no "\
		"FROM t_kansei LEFT OUTER JOIN t_kouji ON t_kansei.kk_id = t_kouji.km_index "\
		"WHERE t_kansei.kk_key = %d;";
	int key = 1158;
	SQLINTEGER kk_id;
	SQLINTEGER kk_ynendo;
	SQLINTEGER kk_knendo;
	SQLINTEGER kk_syurui;
	bool kk_jvflg;
	SQLDOUBLE kk_jvritsu;
	SQLINTEGER kk_ukeoi;
	SQLINTEGER kk_kanmin;
	std::string kk_ken;
	std::string kk_shi;
	std::string kk_tiku;
	TIMESTAMP_STRUCT kk_kaisi;
	TIMESTAMP_STRUCT kk_owari;
	SQLDOUBLE kk_kingaku;
	SQLDOUBLE kk_zei;
	SQLDOUBLE kk_goukei;
	SQLINTEGER kk_point;
	SQLDOUBLE kk_ritsu;
	SQLINTEGER kk_key;
	std::string _name;
	std::string _no;
	char buf[1024],ken[128],shi[128],tiku[128];
	char name[512],no[512];
	SQLINTEGER jvflg;
	_henv = _sql->get_SQLHANDLE(SQL_HANDLE_ENV);
	_hdbc = _sql->get_SQLHANDLE(SQL_HANDLE_DBC);
	_sql->CSQLAllocHandle(SQL_HANDLE_STMT, _hdbc, &_hstmt);
	sprintf(buf,strsql.c_str(),key);
	retcode = _sql->CSQLExecDirect(_hstmt,	(SQLCHAR*) buf , SQL_NTS);
	retcode = _sql->CSQLBindCol(_hstmt, 1, SQL_C_LONG, &kk_id, 8, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 2, SQL_C_LONG, &kk_ynendo, 8, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 3, SQL_C_LONG, &kk_knendo, 8, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 4, SQL_C_LONG, &kk_syurui, 8, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 5, SQL_C_LONG, &jvflg, 8, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 6, SQL_C_DOUBLE, &kk_jvritsu, 8, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 7, SQL_C_LONG, &kk_ukeoi, 8, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 8, SQL_C_LONG, &kk_kanmin, 8, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 9, SQL_C_CHAR, &ken, 128, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 10, SQL_C_CHAR, &shi, 128, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 11, SQL_C_CHAR, &tiku, 128, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 12, SQL_C_TYPE_TIMESTAMP, &kk_kaisi, sizeof(TIMESTAMP_STRUCT), 0);
	retcode = _sql->CSQLBindCol(_hstmt, 13, SQL_C_TYPE_TIMESTAMP, &kk_owari, sizeof(TIMESTAMP_STRUCT), 0);
	retcode = _sql->CSQLBindCol(_hstmt, 14, SQL_C_DOUBLE, &kk_kingaku, 8, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 15, SQL_C_DOUBLE, &kk_zei, 8, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 16, SQL_C_DOUBLE, &kk_goukei, 8, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 17, SQL_C_LONG, &kk_point, 8, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 18, SQL_C_DOUBLE, &kk_ritsu, 8, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 19, SQL_C_LONG, &kk_key, 8, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 20, SQL_C_CHAR, &name, 512, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 21, SQL_C_CHAR, &no, 512, 0);
	for (int i = 0;;i++) {
		retcode = _sql->CSQLFetch(_hstmt);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
			kk_ken = ken;
			kk_shi = shi;
			kk_tiku = tiku;
			_name = name;
			_no = no;
			if (jvflg == 0)	kk_jvflg = false;
			else			kk_jvflg = true;
			//kk_kaisi = kaisi;
			//kk_owari = owari;
			printf("Result is: %s\n", buf);
			//_rec = *this;
		}
		else {
			if (retcode != SQL_NO_DATA) {
			}
			else {
				break;
			}
		}
	}
	_sql->CSQLFreeStmt(_hstmt,0);
*/

	//string wk = "{" + p->Get_Driver() + "}";
	outputfile.close();
	delete p;
	//delete pkansei;
	//delete ptbl;
    return 0;
}
