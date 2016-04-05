sql£º
SELECT customer_credit_flow_id,balance,customer_master_id FROM apollo_os.t_customer_credit_flow where expire_date='2016-03-18' and balance>0 and dr=0 and transaction_type=0


update apollo_os.t_customer_credit_flow set balance=0 where customer_credit_flow_id='JAVVUWVBFV5QJIPNY79T'

update apollo_os.t_customer_master set credit_balance=0 where customer_master_id='JAVVUWUGS2OBYQ381HNP'


spawn-fcgi -p8288 ./data_exchange_gw_fcgi

fastcgi_pass 0.0.0.0:8288;
                fastcgi_index index.cgi;
                fastcgi_param SCRIPT_FILENAME fcgi$fastcgi_script_name;
                include fastcgi_params;
                fastcgi_param  GATEWAY_INTERFACE  CGI/1.1;
      fastcgi_param  SERVER_SOFTWARE    nginx;
      fastcgi_param  QUERY_STRING       $query_string;
      fastcgi_param  REQUEST_METHOD     $request_method;
      fastcgi_param  CONTENT_TYPE       $content_type;
      fastcgi_param  CONTENT_LENGTH     $content_length;
      fastcgi_param  SCRIPT_FILENAME    $document_root$fastcgi_script_name;
      fastcgi_param  SCRIPT_NAME        $fastcgi_script_name;
      fastcgi_param  REQUEST_URI        $request_uri;
      fastcgi_param  DOCUMENT_URI       $document_uri;
      fastcgi_param  DOCUMENT_ROOT      $document_root;
      fastcgi_param  SERVER_PROTOCOL    $server_protocol;
      fastcgi_param  REMOTE_ADDR        $remote_addr;
      fastcgi_param  REMOTE_PORT        $remote_port;
      fastcgi_param  SERVER_ADDR        $server_addr;
      fastcgi_param  SERVER_PORT        $server_port;
      fastcgi_param  SERVER_NAME        $server_name;
