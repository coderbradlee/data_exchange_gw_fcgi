#include "include.hpp"
#include "config.hpp"
#include "serverResource.hpp"
#include <boost/asio/yield.hpp>
#include <boost/asio/coroutine.hpp>

#include <boost/date_time/gregorian/gregorian.hpp>   
#include <boost/any.hpp>
#include "orderbot.hpp"
#define BOOST_DATE_TIME_SOURCE   
//#include "credit_ontime.hpp"

using namespace boost::asio;
using namespace std;

int main() {
	try
	{
		//read config.ini
			
		{
			boost::timer::cpu_timer pass;
			pass.start();
			try
			{

				
				//orderbot 接口
				boost::shared_ptr<orderbot> order=boost::shared_ptr<orderbot>(new orderbot(get_config->m_orderbot_username,get_config->m_orderbot_password,get_config->m_orderbot_url));
				order->request("GET","/admin/products.json/","class_type=sales&category_name=Rings","");

				cout<<order->get_data()<<endl;
				


			}
			catch (const MySqlException& e) 
			{
				cout << e.what() << endl;
				BOOST_LOG_SEV(slg, severity_level::error)<<"query_sql(exception:)" << e.what();
				boost_log->get_initsink()->flush();
				
			}
	//
	//    // Initialize a new test database
	//    conn.runCommand("DROP DATABASE IF EXISTS test_mysql_cpp");
	//    conn.runCommand("CREATE DATABASE test_mysql_cpp");
	//    conn.runCommand("USE test_mysql_cpp");
	//    conn.runCommand("DROP TABLE IF EXISTS user");
	//    conn.runCommand(
	//        "CREATE TABLE user ("
	//            "id INT NOT NULL AUTO_INCREMENT,"
	//            "PRIMARY KEY(id),"
	//            "email VARCHAR(64) NOT NULL,"
	//            "password CHAR(64) NOT NULL,"
	//            "age INT)");
	//
	//    // ************
	//    // Easy inserts
	//    // ************
	//    int ages[] = {27, 21, 26};
	//    string emails[] = {
	//        "bskari@yelp.com",
	//        "brandon.skari@gmail.com",
	//        "brandon@skari.org"};
	//    string passwords[] = {
	//        "peace",
	//        "love",
	//        "griffin"};
	//    conn.runCommand(
	//        "INSERT INTO user (email, password, age)"
	//            " VALUES (?, ?, ?), (?, ?, ?), (?, ?, ?)",
	//        emails[0], passwords[0], ages[0],
	//        emails[1], passwords[1], ages[1],
	//        emails[2], passwords[2], ages[2]);
	//
	//    typedef tuple<int, string, string, int> userTuple;
	//    vector<userTuple> users;
	//    // *****************************************
	//    // All commands use safe prepared statements
	//    // *****************************************
	//    const string naughtyUser("brandon@skari.org'; DROP TABLE users; -- ");
	//    conn.runQuery(&users, "SELECT * FROM user WHERE email = ?", naughtyUser);
	//    assert(0 == users.size());
	//
	//    const char naughtyUser2[] = "something' OR '1' = 1' --  ";
	//    const char* charPtr = naughtyUser2;
	//    conn.runQuery(&users, "SELECT * FROM user WHERE email = ?", charPtr);
	//    assert(0 == users.size());
	//
	//    // ***************************
	//    // Automatically typed selects
	//    // ***************************
	//    conn.runQuery(&users, "SELECT * FROM user");
	//    printTupleVector(users);
	//    users.clear();
	//
	//    // ************************
	//    // Dealing with NULL values
	//    // ************************
	//    conn.runCommand(
	//        "INSERT INTO user (email, password, age) VALUES (?, ?, NULL)",
	//        emails[0],
	//        passwords[0]);
	//
	//    try {
	//        // Trying to insert NULLs into a normal tuple will throw
	//        conn.runQuery(&users, "SELECT * FROM user");
	//    } catch (const MySqlException& e) {
	//        cout << e.what() << endl;
	//    }
	//
	//    // But, we can select into tuples with unique_ptr
	//    typedef tuple<
	//        unique_ptr<int>,
	//        unique_ptr<string>,
	//        unique_ptr<string>,
	//        unique_ptr<int>
	//    > autoPtrUserTuple;
	//    vector<autoPtrUserTuple> autoPtrUsers;
	//    conn.runQuery(&autoPtrUsers, "SELECT * FROM user");
	//    printTupleVector(autoPtrUsers);

			std::cout << "now time elapsed:" << pass.format(6) << std::endl;
		}
		////HTTP-server at port 8080 using 4 threads
		//boost::shared_ptr<HttpServer> server = boost::shared_ptr<HttpServer>(new HttpServer(port, threads));
		////serverResource(server);
		//server_resource t;
		//t(server);
		//thread server_thread([&server](){
		//	//Start server
		//	server->start();
		//});
		//
		//server_thread.join();
		//boost::shared_ptr<HttpsServer> server = boost::shared_ptr<HttpsServer>(new HttpsServer(port, threads, "ssl/server.crt", "ssl/server.key", 5,300,"ssl/dh768.pem"));
		//servers_resource t(server);
		//thread server_thread([&server](){
		//	//Start server
		//	server->start();
		//});
		//this_thread::sleep_for(chrono::seconds(10));
		//
		//
		//server_thread.join();
		
		//{
		//	//curl -X POST 'https://api.sandbox.paypal.com/v1/oauth2/token'  -H "Accept: application/json"  -H "Accept - Language: en_US"  -u "AQHK3B-gB3sdb1ierWaMMap-6dKJtC-NGIRPeCa6GsZHVioiso-peMOyDgdCpThLv2rz39BTzqk6ajWy:EOiC6EF3aXo9X4whY5l51QPlQ9vzDsbcM2ihIyUqqNDUQ2NrMpvpjUZqeJ6AJ7bmzXXXyV4BOYsmq-Lo" -d "grant_type=client_credentials"
		//	//boost::timer::cpu_timer pass;
		//	//pass.start();
		//	//HttpsClient client("api.sandbox.paypal.com", false);
		//	//HttpsClient client("127.0.0.1:8888", false);
		//	HttpsClient client("127.0.0.1:8888", true, "ssl/server.crt", "ssl/server.key", "ssl/dh768.pem");
		//	//cout << __LINE__ << endl;
		//	std::stringstream ss;
		//	ss << "grant_type=client_credentials";
		//	std::map<std::string, std::string> header;
		//	header.insert(make_pair("Accept", "application/json"));
		//	header.insert(make_pair("Accept-Language", "en_US"));
		//	//header.insert(make_pair("Authorization", "Basic AQHK3B-gB3sdb1ierWaMMap-6dKJtC-NGIRPeCa6GsZHVioiso-peMOyDgdCpThLv2rz39BTzqk6ajWy:EOiC6EF3aXo9X4whY5l51QPlQ9vzDsbcM2ihIyUqqNDUQ2NrMpvpjUZqeJ6AJ7bmzXXXyV4BOYsmq-Lo"));
		//	string auth = "AQHK3B-gB3sdb1ierWaMMap-6dKJtC-NGIRPeCa6GsZHVioiso-peMOyDgdCpThLv2rz39BTzqk6ajWy:EOiC6EF3aXo9X4whY5l51QPlQ9vzDsbcM2ihIyUqqNDUQ2NrMpvpjUZqeJ6AJ7bmzXXXyV4BOYsmq-Lo";
		//	auto r1 = client.request("POST", "/v1/oauth2/token", ss, header,auth);
		//	//auto r1 = client.request("POST", "/v1/oauth2/token");
		//	cout << __LINE__<<":"<<r1->content.rdbuf() << endl;
		//	//std::cout << "now time elapsed:" << pass.format(6) << std::endl;
		//}
		//
		//{
		//	//curl -v -X GET 'https://api.sandbox.paypal.com/v1/payments/payment?sort_order=asc&sort_by=update_time' -H "Content-Type:application/json" -H "Authorization: Bearer A101.aSJ8QgWcCXOAsB6vGPrHxqNxjB7M5-P5-RoIECH3VFQrjap_Jw1plDKJ6CdqNE5M.qJHuEy4Ubs_gmzOE9PbP6cFJmla"
		//	//boost::timer::cpu_timer pass;
		//	//pass.start();
		//	HttpsClient client("api.sandbox.paypal.com", false);
		//	std::stringstream ss;
		//	std::map<std::string, std::string> header;
		//	header.insert(make_pair("Content-Type", "application/json"));
		//	header.insert(make_pair("Authorization", "Bearer A101.aSJ8QgWcCXOAsB6vGPrHxqNxjB7M5-P5-RoIECH3VFQrjap_Jw1plDKJ6CdqNE5M.qJHuEy4Ubs_gmzOE9PbP6cFJmla"));
		//	
		//	auto r1 = client.request("GET", "/v1/payments/payment?sort_order=asc&sort_by=update_time", ss, header, "");
		//	//auto r1 = client.request("POST", "/v1/oauth2/token");
		//	cout << __LINE__ << ":" << r1->content.rdbuf() << endl;
		//	//std::cout << "now time elapsed:" << pass.format(6) << std::endl;
		//}
	}
	catch (std::exception& e) {
		//cout << diagnostic_information(e) << endl;
		cout << e.what() << endl;
        }
	catch(...) 
	{
         
	}
    return 0;
}