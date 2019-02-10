#include "stdafx.h"
#include "GenWindow.h"

using namespace std;

GenWindow::GenWindow() :
	m_l001(" "),
	m_l002(" "),
	m_l003("Driver"),
	m_l004("Server"),
	m_l005("Database"),
	m_l006("User ID"),
	m_l007("PassWord"),
	m_Ok("OK"),
	m_Close("閉じる")
{
	set_title("ODBC Class Generation");
	set_default_size(400,400);
	m_grid.set_row_spacing(4);
	m_grid.set_column_spacing(4);
	m_grid.attach(m_l001,0,0,1,1);
	m_grid.attach_next_to(m_l002,m_l001, Gtk::POS_RIGHT,1,1);
	m_grid.attach_next_to(m_l003,m_l002, Gtk::POS_BOTTOM,1,1);
	m_grid.attach_next_to(m_driver,m_l003, Gtk::POS_RIGHT,2,1);
	m_grid.attach_next_to(m_l004,m_l003, Gtk::POS_BOTTOM,1,1);
	m_grid.attach_next_to(m_server,m_l004, Gtk::POS_RIGHT,2,1);
	m_grid.attach_next_to(m_l005,m_l004, Gtk::POS_BOTTOM,1,1);
	m_grid.attach_next_to(m_database,m_l005, Gtk::POS_RIGHT,2,1);
	m_grid.attach_next_to(m_l006,m_l005, Gtk::POS_BOTTOM,1,1);
	m_grid.attach_next_to(m_user,m_l006, Gtk::POS_RIGHT,2,1);
	m_grid.attach_next_to(m_l007,m_l006, Gtk::POS_BOTTOM,1,1);
	m_grid.attach_next_to(m_pass,m_l007, Gtk::POS_RIGHT,2,1);
	m_hbox.add(m_Ok);
	m_hbox.add(m_Close);
	m_grid.attach_next_to(m_hbox,m_l007, Gtk::POS_BOTTOM,3,1);
	add(m_grid);
	m_Ok.signal_clicked().connect(sigc::mem_fun(this, &GenWindow::on_Ok_clicked));
	m_Close.signal_clicked().connect(sigc::mem_fun(this, &GenWindow::on_Close_clicked));
	show_all_children();
}

GenWindow::~GenWindow() {

}

void GenWindow::on_Close_clicked(){
	this->close();
}

void GenWindow::on_Ok_clicked(){
	OdbcConnection *pcon = new OdbcConnection();
	pcon->Set_Driver(m_driver.get_text());
	pcon->Set_Server(m_server.get_text());
	pcon->Set_Database(m_database.get_text());
	pcon->Set_UserID(m_user.get_text());
	pcon->Set_Password(m_pass.get_text());
	SQLRETURN rtn = pcon->DriverConnect();
	std::string con = pcon->Get_ConnectionString();
	COdbcsql *_sql = pcon->m_psql;
	OdbcCommand	*com = new OdbcCommand(pcon);
	com->m_CommandString = "SELECT TABLE_CATALOG, TABLE_SCHEMA, TABLE_NAME, TABLE_TYPE FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_CATALOG = '" +
	pcon->Get_Database() + "';";
	SQLHSTMT  _hstmt = com->Get_StatementHandle();
	SQLRETURN retcode = com->SQLExecuteD();
	SQLCHAR TABLE_CATALOG[256], TABLE_SCHEMA[256], TABLE_NAME[256], TABLE_TYPE[256];
	retcode = _sql->CSQLBindCol(_hstmt, 1, SQL_C_CHAR, TABLE_CATALOG, 256, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 2, SQL_C_CHAR, TABLE_SCHEMA, 256, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 3, SQL_C_CHAR, TABLE_NAME, 256, 0);
	retcode = _sql->CSQLBindCol(_hstmt, 4, SQL_C_CHAR, TABLE_TYPE, 256, 0);
	vector<std::string> _tbl;
	delete com;
	delete pcon;
}