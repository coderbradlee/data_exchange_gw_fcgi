#ifndef ORDERBOT_HPP
#define	ORDERBOT_HPP

#include  "include.hpp"
//#define DEBUG

class orderbot
{
public:
	orderbot(const std::string& user, const std::string& password,const std::string& url) :m_username(user),m_password(password),m_url(url)
	{
		curl_global_init(CURL_GLOBAL_ALL);
		m_curl = curl_easy_init();
		curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1);
		curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, this);
		string user_pass=m_username+":"+m_password;
		curl_easy_setopt(m_curl, CURLOPT_USERPWD, user_pass.c_str());
#ifdef DEBUG
		curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1);
#endif
		//curl(m_download_url, "GET", filename, true);
	}
	virtual ~orderbot()
	{
		curl_easy_cleanup(m_curl);
		curl_global_cleanup();	
	}
	void request(const std::string& method,const std::string& path,const std::string& param,const std::string& content)
	{
		curl(path,method,param,content);
	}
	string get_data()
	{
		return m_data;
	}
protected:	
	
	static size_t request_callback(char *buffer, size_t size, size_t nmemb, void* thisPtr)
	{
		if (thisPtr)
		{
			//cout << __LINE__ << endl;
			return ((orderbot*)thisPtr)->request_write_data(buffer, size, nmemb);
		}

		else
		{
			//cout << __LINE__ << endl;
			return 0;
		}

	}
	size_t request_write_data(const char *buffer, size_t size, size_t nmemb)
	{
		int result = 0;
		if (buffer != 0)
		{
			//cout << __LINE__ << endl;
			//m_data.clear();
			m_data.append(buffer, size*nmemb);
			// cout<<"m_data:"<<m_data.size()<<endl;
			// cout<<"max_size:"<<m_data.max_size() <<endl;
			// cout<<"capacity:"<<m_data.capacity()<<endl;
			result = size*nmemb;
			// boost::asio::streambuf write_buffer;
   //          std::ostream response(&write_buffer);
   //          response << stream.rdbuf();
		}
		/*cout <<__LINE__<<":"<<  buffer << endl;*/
		//cout << __LINE__ << ":" << m_data << endl;
		
		return result;
	}

	void curl(const std::string& uri, const std::string& method = "GET", const std::string& param="",const std::string& content="")
	{		
		set_url(m_url+uri+"?"+param);		
		//cout << __LINE__ << ":" << uri << endl;
		
#ifdef DEBUG
		curl_easy_setopt(m_curl, CURLOPT_HEADER, 1);
#endif
		curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, request_callback);
		curl_easy_setopt(m_curl, CURLOPT_MAXREDIRS, 50L);
		curl_easy_setopt(m_curl, CURLOPT_TCP_KEEPALIVE, 1L);
		curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, method.c_str());
		
		
		on_request();
		
	}
	void set_url(const std::string& url) const
	{
		curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());
	}
	bool on_request() 
	{
		m_data.clear();
		return 0 == curl_easy_perform(m_curl);
	}
	
protected:	
	std::string m_data;
	CURL* m_curl;
	std::string m_url;
	std::string m_username;
	std::string m_password;
};

#endif

