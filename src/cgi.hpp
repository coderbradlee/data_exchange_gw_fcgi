#ifndef CGI_HPP
#define	CGI_HPP

#include  "include.hpp"
//#define DEBUG
#include "fcgio.h"
#include <unistd.h>
#include <sstream>
#include <unistd.h>
class fcgi_equest
{

		#define INPUT_BUFFER_SIZE 10000
		#define MAX_INPUT_MESSAGE_BODY 100000000  //100MB
    public:
        fcgi_equest( FCGX_Request *fastcgi_request )
            :fastcgi_request(fastcgi_request)
        {


        }

        void reload(){

            this->parameters.clear();

            this->parameters[ "GATEWAY_INTERFACE" ] = FCGX_GetParam( "GATEWAY_INTERFACE", this->fastcgi_request->envp );
            this->parameters[ "SERVER_SOFTWARE" ] = FCGX_GetParam( "SERVER_SOFTWARE", this->fastcgi_request->envp );
            this->parameters[ "QUERY_STRING" ] = FCGX_GetParam( "QUERY_STRING", this->fastcgi_request->envp );
            this->parameters[ "REQUEST_METHOD" ] = FCGX_GetParam( "REQUEST_METHOD", this->fastcgi_request->envp );
            this->parameters[ "CONTENT_TYPE" ] = FCGX_GetParam( "CONTENT_TYPE", this->fastcgi_request->envp );
            this->parameters[ "CONTENT_LENGTH" ] = FCGX_GetParam( "CONTENT_LENGTH", this->fastcgi_request->envp );
            this->parameters[ "SCRIPT_FILENAME" ] = FCGX_GetParam( "SCRIPT_FILENAME", this->fastcgi_request->envp );
            this->parameters[ "SCRIPT_NAME" ] = FCGX_GetParam( "SCRIPT_NAME", this->fastcgi_request->envp );
            this->parameters[ "REQUEST_URI" ] = FCGX_GetParam( "REQUEST_URI", this->fastcgi_request->envp );
            this->parameters[ "DOCUMENT_URI" ] = FCGX_GetParam( "DOCUMENT_URI", this->fastcgi_request->envp );
            this->parameters[ "DOCUMENT_ROOT" ] = FCGX_GetParam( "DOCUMENT_ROOT", this->fastcgi_request->envp );
            this->parameters[ "SERVER_PROTOCOL" ] = FCGX_GetParam( "SERVER_PROTOCOL", this->fastcgi_request->envp );
            this->parameters[ "REMOTE_ADDR" ] = FCGX_GetParam( "REMOTE_ADDR", this->fastcgi_request->envp );
            this->parameters[ "REMOTE_PORT" ] = FCGX_GetParam( "REMOTE_PORT", this->fastcgi_request->envp );
            this->parameters[ "SERVER_ADDR" ] = FCGX_GetParam( "SERVER_ADDR", this->fastcgi_request->envp );
            this->parameters[ "SERVER_PORT" ] = FCGX_GetParam( "SERVER_PORT", this->fastcgi_request->envp );
            this->parameters[ "SERVER_NAME" ] = FCGX_GetParam( "SERVER_NAME", this->fastcgi_request->envp );

            this->loadInput();

        }


        void loadInput(){

            size_t number_of_bytes_requested = INPUT_BUFFER_SIZE;
            size_t number_of_bytes_read;
            size_t total_bytes_read = 0;

            this->message_body = "";

            do{

                number_of_bytes_read = FCGX_GetStr( this->input_buffer, number_of_bytes_requested, fastcgi_request->in );
                if( number_of_bytes_read <= 0 ){
                    break;
                }
                total_bytes_read += number_of_bytes_read;

                if( total_bytes_read > MAX_INPUT_MESSAGE_BODY ){
                    this->message_body.append( "Max Body Length Reached" );
                    break;
                }

                this->message_body.append( this->input_buffer, number_of_bytes_read );

            }while( number_of_bytes_read == INPUT_BUFFER_SIZE );


        }


        string getParameterByName( string parameter_name ){

            string parameter_value;
            parameter_value = FCGX_GetParam( parameter_name.c_str(), fastcgi_request->envp );
            return parameter_value;

        }


        map< string, string > parameters;
        string message_body;

    protected:
        FCGX_Request *fastcgi_request;

        char input_buffer[ INPUT_BUFFER_SIZE ];




};
#endif

