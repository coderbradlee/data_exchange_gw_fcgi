#include "config.hpp"
#include "orderbot.hpp"
#include "credit_ontime.hpp"
#include "activemq.hpp"
#include "cgi.hpp"

int main()
{
	try
	{
		{
		 // Backup the stdio streambufs
		    streambuf * cin_streambuf  = cin.rdbuf();
		    streambuf * cout_streambuf = cout.rdbuf();
		    streambuf * cerr_streambuf = cerr.rdbuf();

		    FCGX_Request fastcgi_request;

		    FCGX_Init();
		    FCGX_InitRequest(&fastcgi_request, 0, 0);

		    int x = 0;

		    boost::shared_ptr<fcgi_equest> request = boost::shared_ptr<fcgi_equest>(new fcgi_equest( &fastcgi_request ));
		    map<string,string>::iterator parameter_iterator;

		    while( FCGX_Accept_r(&fastcgi_request) == 0 ){

		        x++;

		        request->reload();

		        cout << request->message_body << endl;
		       
		        fcgi_streambuf cin_fcgi_streambuf( fastcgi_request.in );
		        fcgi_streambuf cout_fcgi_streambuf( fastcgi_request.out );
		        fcgi_streambuf cerr_fcgi_streambuf( fastcgi_request.err );

		        cin.rdbuf( &cin_fcgi_streambuf );
		        cout.rdbuf( &cout_fcgi_streambuf );
		        cerr.rdbuf( &cerr_fcgi_streambuf );

		        cout << "Content-type: text/html\r\n"
		             << "\r\n"
		             << "<html>\n"
		             << "  <head>\n"
		             << "    <title>Hello, World!</title>\n"
		             << "  </head>\n"
		             << "  <body>\n"
		             << "    <h1>Hello, World!</h1>\n"
		             ;

		        cout << request->message_body << endl;


		        cout << sizeof( FCGX_Request ) << endl;

		        cout << x << "<br/>" << endl;

		        for( parameter_iterator = request->parameters.begin(); parameter_iterator != request->parameters.end(); parameter_iterator++ ){
		            cout << parameter_iterator->first << " => " << parameter_iterator->second << "<br/>" << endl;
		        }

		        cout << "</body></html>" << endl;

		        // Note: the fcgi_streambuf destructor will auto flush
		    }

		    // restore stdio streambufs
		    cin.rdbuf( cin_streambuf );
		    cout.rdbuf( cout_streambuf );
		    cerr.rdbuf( cerr_streambuf );

		}
		
		{
			boost::timer::cpu_timer pass;
			pass.start();
			credit_ontime test;
			//test.start_update();

			std::cout << "now time elapsed:" << pass.format(6) << std::endl;
		}
		{
			boost::timer::cpu_timer pass;
			pass.start();

			//orderbot 接口
			boost::shared_ptr<orderbot> order = boost::shared_ptr<orderbot>(new orderbot(get_config->m_orderbot_username, get_config->m_orderbot_password, get_config->m_orderbot_url));
			// order->request("GET", "/admin/products.json/", "class_type=sales&category_name=Rings", "");

			// cout<<order->get_data().length()<<":"<<order->get_data()<<endl;
			std::cout << "now time elapsed:" << pass.format(6) << std::endl;
		}
		{
			boost::timer::cpu_timer pass;
			pass.start();

			//orderbot 接口
			boost::shared_ptr<activemq> am = boost::shared_ptr<activemq>(new activemq(get_config->m_activemq_username, get_config->m_activemq_password, get_config->m_activemq_url));
			//am->request("POST", "/api/message/TEST", "type=queue", "body={message:\"test\"}");
			//cout<<am->get_data().length()<<":"<<am->get_data()<<endl;
			//am->request("GET", "/api/message/TEST", "type=queue&clientId=consumerA", "");
			//cout<<am->get_data().length()<<":"<<am->get_data()<<endl;
			this_thread::sleep_for(chrono::seconds(10));
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