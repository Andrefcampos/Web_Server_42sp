/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:49:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/17 11:31:53 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <list>
#include "ARequestLine.hpp"
#include "AHeaders.hpp"
#include "ABody.hpp"

#define CLENGTH "Content-Length"
#define TENCODING "Transfer-Encoding"
#define CHUNKED "chunked"

using namespace std;

class Request:public ARequestLine, public AHeaders, public ABody{
	private:
		void	haveBody();

	public:
		Request();
		~Request(){};
		void	setRequestLine(string &buffer);
		void	setHeader(string &buffer);
		void	setBody(std::string &buffer);

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