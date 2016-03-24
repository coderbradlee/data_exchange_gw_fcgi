#ifndef CREDIT_ONTIME_HPP
#define	CREDIT_ONTIME_HPP
#include "include.hpp"
#include "mysql/mysql_api.hpp"

//#define DEBUG
class credit_ontime
{
public:
	// MySql conn(get_config->m_ip.c_str(), get_config->m_username.c_str(), get_config->m_password.c_str(), get_config->m_database.c_str(), get_config->m_port);

	// boost::gregorian::date today = boost::gregorian::day_clock::local_day();
	// std::string str1(to_iso_extended_string(today));
	// std::cout << str1 << std::endl;

	
	// typedef tuple<unique_ptr<string>, unique_ptr<double> ,unique_ptr<string>> credit_tuple;
	
	// //typedef tuple<string,double> credit_tuple;
	// vector<credit_tuple> credits;
	// string query_sql = "SELECT customer_credit_flow_id,balance,customer_master_id FROM " + get_config->m_database + "." + get_config->m_table + " where expire_date='" + str1 + "' and balance>0 and dr=0 and transaction_type=0";
	// cout << query_sql << endl;
	// conn.runQuery(&credits, query_sql.c_str());

	// BOOST_LOG_SEV(slg, boost_log->get_log_level()) << query_sql;
	// boost_log->get_initsink()->flush();
	// /********************************/
	// cout.setf(ios::showpoint); cout.setf(ios::fixed); cout.precision(8);
	// /********************************/

	// for (const auto& item : credits)
	// {
	// 	cout << item << endl;
	// 	//cout << std::get<0>(item) << endl;
		
	// 	//unique_ptr<string> data=std::move((std::get<0>(item)));
		
	// 	//UPDATE ±íÃû³Æ SET ÁÐÃû³Æ = ÐÂÖµ WHERE ÁÐÃû³Æ = Ä³Öµ
	// 	string update_sql = "update " + get_config->m_database + "." + get_config->m_table + " set balance=0 where customer_credit_flow_id='" + *(std::get<0>(item))+"'";
	// 	cout << update_sql << endl;
	// 	string update_sql2;
	// 	try
	// 	{
	// 		conn.runCommand(update_sql.c_str());
	// 		//¸üÐÂÁíÒ»¸ö±í
	// 		update_sql2 = "update " + get_config->m_database + "." + get_config->m_table2 + " set credit_balance=0 where customer_master_id='" + *(std::get<2>(item))+"'";
	// 		cout << update_sql2 << endl;
	// 		conn.runCommand(update_sql2.c_str());
			
	// 		BOOST_LOG_SEV(slg, boost_log->get_log_level()) << update_sql;
	// 		BOOST_LOG_SEV(slg, boost_log->get_log_level()) << update_sql2;
	// 		boost_log->get_initsink()->flush();
	// 	}
	// 	catch (const MySqlException& e)
	// 	{
	// 		BOOST_LOG_SEV(slg, severity_level::error) << "(1)" << update_sql << "(2)" << update_sql2 << "(exception:)" << e.what();
	// 		boost_log->get_initsink()->flush();
	// 	}
		

		
	// }

	// credits.clear();


};
#endif

