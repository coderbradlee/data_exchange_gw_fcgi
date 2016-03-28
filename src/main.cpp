//#include "include.hpp"
#include "config.hpp"
#include "serverResource.hpp"
#include <boost/asio/yield.hpp>
#include <boost/asio/coroutine.hpp>

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/any.hpp>
#include "orderbot.hpp"
#include "credit_ontime.hpp"
#define BOOST_DATE_TIME_SOURCE
//#include "credit_ontime.hpp"

using namespace boost::asio;
using namespace std;

int main()
{
	try
	{
		{
			//test prepared statement
			//, , , get_config->m_database.c_str(), get_config->m_port
			MySql conn(get_config->m_ip.c_str(), get_config->m_username.c_str(), get_config->m_password.c_str(), nullptr);
			
			string update_sql = "update " + get_config->m_database + "." + get_config->m_table + " set balance=0 where customer_credit_flow_id='JAVVUZJEZK06NI4SL529'";
			string update_sql2 = "update " + get_config->m_database + "." + get_config->m_table2 + " set credit_balance=0 where customer_master_id='JAVVUZIKIUYDY6PAKCGP'";
			string combine=update_sql+";"+update_sql2;
			cout<<combine<<endl;
			MySqlPreparedStatement t(combine.c_str(),&conn);
			cout<<t.getParameterCount()<<endl;
			cout<<t.getFieldCount()<<endl;
		}
		{
			boost::timer::cpu_timer pass;
			pass.start();
			credit_ontime test;
			//test.start_update();

			//std::cout << "now time elapsed:" << pass.format(6) << std::endl;
		}
		{
			boost::timer::cpu_timer pass;
			pass.start();

			//orderbot 接口
			boost::shared_ptr<orderbot> order = boost::shared_ptr<orderbot>(new orderbot(get_config->m_orderbot_username, get_config->m_orderbot_password, get_config->m_orderbot_url));
			//order->request("GET", "/admin/products.json/", "class_type=sales&category_name=Rings", "");

			//cout<<order->get_data().length()<<":"<<order->get_data()<<endl;
			std::cout << "now time elapsed:" << pass.format(6) << std::endl;
		}

	}
	catch (std::exception& e)
	{
		//cout << diagnostic_information(e) << endl;
		cout << e.what() << endl;
	}
	catch (...)
	{

	}
	return 0;
}