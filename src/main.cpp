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

int main() {
	try
	{
		{
			boost::timer::cpu_timer pass;
			pass.start();
			credit_ontime test;
			test.start_update();

			std::cout << "now time elapsed:" << pass.format(6) << std::endl;
		}
		{
			boost::timer::cpu_timer pass;
			pass.start();

			//test
			
			const std::regex pattern("^/admin/products.json/[[:graph:]]+$");

		   std::string url = "/admin/products.json/?class_type=sales&category_name=Rings";

		   std::smatch result;

		   bool match = std::regex_search(url, result, pattern);

		   if(match)
		   {
				for(size_t i = 1; i < result.size(); ++i)
			    {
			        std::cout << result[i] << std::endl;
			    }
		   }
		   else
		   {
		   	 cout<<__LINE__<<endl;
		   }
			//orderbot 接口
			boost::shared_ptr<orderbot> order=boost::shared_ptr<orderbot>(new orderbot(get_config->m_orderbot_username,get_config->m_orderbot_password,get_config->m_orderbot_url));
			order->request("GET","/admin/products.json/","class_type=sales&category_name=Rings","");

			//cout<<order->get_data().length()<<":"<<order->get_data()<<endl;
				
		
			std::cout << "now time elapsed:" << pass.format(6) << std::endl;
		}
		
	}
	catch (std::exception& e) 
	{
		//cout << diagnostic_information(e) << endl;
		cout << e.what() << endl;
    }
	catch(...) 
	{
         
	}
    return 0;
}