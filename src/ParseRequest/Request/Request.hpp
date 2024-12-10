/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:49:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/10 16:03:38 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <list>
#include "ARequestLine.hpp"
#include "AHeaders.hpp"
#include "ABody.hpp"
#include "Server.hpp"

#define CLENGTH "Content-Length"
#define CTYPE "Content-Type"
#define MPART "multipart"
#define TENCODING "Transfer-Encoding"
#define CHUNKED "chunked"


using namespace std;

class Request : public ARequestLine, public AHeaders{
	private:
		ABody	*body;
		Server	*_server;
		int		_parserError;
		bool	_parsedRequestLine;
		bool	_parsedHeaders;
		bool	_parsedBody;
		bool	_isMultPartBody;
		bool	_isSimpleBody;
		bool	_isChunkedBody;
		bool	_haveBody;
		size_t	_bodyLength;
		void	checkBodyFormatting();
		void	isMultPartBody();
		void	isSimpleBody();
		void	isChunkedBody();
		void	instanceBody();
		void	initMultPart();
		void	initChunked();
		void	initSimpleBody();

	public:
		Request();
		~Request();
		ABody	*getBody();
		int		setRequestLine(string &buffer);
		int		setHeader(string &buffer);
		void	setBody(std::string &buffer);
		void	setServer(Server *server);
		Server	*getServer() const;
		void	setParserError(int error);
		int		getParserError() const;

		class RequestException:public exception{
			private:
				string _msg;	
			public:
				virtual ~RequestException() throw() {}
				RequestException(string msg) : _msg(msg){}
				virtual const char *what() const throw(){
					return _msg.c_str();
				};	
		};
};
