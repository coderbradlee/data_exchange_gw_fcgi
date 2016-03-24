#ifndef CONFIG_HPP
#define	CONFIG_HPP

#include <curl/curl.h>
#include <string.h>
#include <cstdarg>
#include <iostream>
#include <map>
//#define DEBUG
#include "serverResource.hpp"
class config:public boost::enable_shared_from_this<config>, boost::noncopyable
{
	public:
		static boost::shared_ptr<config> get_instance(const std::string& filename)
		{
			boost::mutex::scoped_lock t(m_mu);
			if (m_ps == nullptr)
			{
				m_ps = boost::shared_ptr<config>(new config(filename));
			}
			
			return m_ps;
		}
	private:
		config(const std::string& filename)
		{			
			boost::property_tree::ini_parser::read_ini(filename, m_pt);
			m_ip = m_pt.get<std::string>("mysql.ip");
			m_port = boost::lexical_cast<unsigned short>(m_pt.get<std::string>("mysql.port"));
			m_username = m_pt.get<std::string>("mysql.username");
			m_password = m_pt.get<std::string>("mysql.password");
			m_database = m_pt.get<std::string>("mysql.database");
			m_table = m_pt.get<std::string>("mysql.table");
			m_table2 = m_pt.get<std::string>("mysql.table2");
			m_threads = boost::lexical_cast<size_t>(m_pt.get<std::string>("webserver.threads"));
			m_orderbot_username = m_pt.get<std::string>("orderbot.username");
			m_orderbot_password = m_pt.get<std::string>("orderbot.password");
			m_orderbot_url = m_pt.get<std::string>("orderbot.url");	
		}
	public:
		boost::property_tree::ptree m_pt;
		string m_ip;
		unsigned short m_port;
		string m_username;
		string m_password;
		string m_database;
		string m_table;
		string m_table2;
		size_t m_threads;
		string m_orderbot_username;
		string m_orderbot_password;
		string m_orderbot_url;	
		static boost::mutex m_mu;	
		static boost::shared_ptr<config> m_ps;
};
boost::shared_ptr<config> get_config = config::get_instance("config.ini");

#endif

