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
#include "activemq/activemq.hpp"
using namespace activemq::core;
using namespace decaf::util::concurrent;
using namespace decaf::util;
using namespace decaf::lang;
using namespace cms;
using namespace boost::asio;
using namespace std;

int main()
{
	try
	{
		{

		    activemq::library::ActiveMQCPP::initializeLibrary();
		    {
		    std::cout << "=====================================================\n";
		    std::cout << "Starting the example:" << std::endl;
		    std::cout << "-----------------------------------------------------\n";


		    // Set the URI to point to the IP Address of your broker.
		    // add any optional params to the url to enable things like
		    // tightMarshalling or tcp logging etc.  See the CMS web site for
		    // a full list of configuration options.
		    //
		    //  http://activemq.apache.org/cms/
		    //
		    // Wire Format Options:
		    // =========================
		    // Use either stomp or openwire, the default ports are different for each
		    //
		    // Examples:
		    //    tcp://127.0.0.1:61616                      default to openwire
		    //    tcp://127.0.0.1:61616?wireFormat=openwire  same as above
		    //    tcp://127.0.0.1:61613?wireFormat=stomp     use stomp instead
		    //
		    // SSL:
		    // =========================
		    // To use SSL you need to specify the location of the trusted Root CA or the
		    // certificate for the broker you want to connect to.  Using the Root CA allows
		    // you to use failover with multiple servers all using certificates signed by
		    // the trusted root.  If using client authentication you also need to specify
		    // the location of the client Certificate.
		    //
		    //     System::setProperty( "decaf.net.ssl.keyStore", "<path>/client.pem" );
		    //     System::setProperty( "decaf.net.ssl.keyStorePassword", "password" );
		    //     System::setProperty( "decaf.net.ssl.trustStore", "<path>/rootCA.pem" );
		    //
		    // The you just specify the ssl transport in the URI, for example:
		    //
		    //     ssl://localhost:61617
		    //
		    std::string brokerURI =
		        "failover:(tcp://http://172.18.100.204/:61616"
		//        "?wireFormat=openwire"
		//        "&transport.useInactivityMonitor=false"
		//        "&connection.alwaysSyncSend=true"
		//        "&connection.useAsyncSend=true"
		//        "?transport.commandTracingEnabled=true"
		//        "&transport.tcpTracingEnabled=true"
		//        "&wireFormat.tightEncodingEnabled=true"
		        ")";

		    //============================================================
		    // set to true to use topics instead of queues
		    // Note in the code above that this causes createTopic or
		    // createQueue to be used in both consumer an producer.
		    //============================================================
		    bool useTopics = true;
		    bool sessionTransacted = false;
		    int numMessages = 2000;

		    long long startTime = System::currentTimeMillis();

		    HelloWorldProducer producer(brokerURI, numMessages, useTopics);
		    HelloWorldConsumer consumer(brokerURI, numMessages, useTopics, sessionTransacted);

		    // Start the consumer thread.
		    Thread consumerThread(&consumer);
		    consumerThread.start();

		    // Wait for the consumer to indicate that its ready to go.
		    consumer.waitUntilReady();

		    // Start the producer thread.
		    Thread producerThread(&producer);
		    producerThread.start();

		    // Wait for the threads to complete.
		    producerThread.join();
		    consumerThread.join();

		    long long endTime = System::currentTimeMillis();
		    double totalTime = (double)(endTime - startTime) / 1000.0;

		    consumer.close();
		    producer.close();

		    std::cout << "Time to completion = " << totalTime << " seconds." << std::endl;
		    std::cout << "-----------------------------------------------------\n";
		    std::cout << "Finished with the example." << std::endl;
		    std::cout << "=====================================================\n";

		    }
		    activemq::library::ActiveMQCPP::shutdownLibrary();
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