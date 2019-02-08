#ifndef __GENWINDOW_H__
#define __GENWINDOW_H__
#include "stdafx.h"

class GenWindow : public Gtk::Window {
public:
	GenWindow();
	virtual ~GenWindow();
protected:
	Gtk::Grid	m_grid;
	Gtk::Label	m_l001;
	Gtk::Label	m_l002;
	Gtk::Label	m_l003;
	Gtk::Label	m_l004;
	Gtk::Label	m_l005;
	Gtk::Label	m_l006;
	Gtk::Label	m_l007;
	Gtk::Entry	m_driver;
	Gtk::Entry	m_server;	
	Gtk::Entry	m_database;
	Gtk::Entry	m_user;
	Gtk::Entry	m_pass;
	Gtk::HBox	m_hbox;	
	Gtk::Button	m_Ok;
	Gtk::Button	m_Close;
	void on_Close_clicked();
	void on_Ok_clicked();
};
#endif
