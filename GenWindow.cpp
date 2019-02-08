#include "stdafx.h"
#include "GenWindow.h"

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
	std::string drivername = "{" + m_driver.get_text() + "}";
	pcon->Set_Driver(drivername);
	pcon->Set_Server(m_server.get_text());
	delete pcon;
}