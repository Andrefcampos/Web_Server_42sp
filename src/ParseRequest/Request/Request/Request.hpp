/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:49:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/12 19:28:54 by rbutzke          ###   ########.fr       */
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

class Client;

using namespace std;

class Request : public ARequestLine, public AHeaders{
	private:
		ABody	*body;
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
		int		setHeader(string &buffer, Client *client);
		void	setBody(std::string &buffer);
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
