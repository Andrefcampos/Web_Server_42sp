/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:49:42 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/15 16:06:07 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <list>

using namespace std;

class Headers{
	protected:
		map<string, list<string>>	header;
	
	public:
		void			addNewElement(string key, string value);
		list<string>	getHeader(string key);
	
};

class Body{
	protected:
		map<string, list<string>>	body;
	
	public:
		void			addNewElement(string key, string value);
		list<string>	getHeader(string key);
};

class Request:public RequestLine, Headers, Body{
	protected:
		void	setRequestLine(string requestLine);
		void	setHeader(string headers);
		void	setBody(std::string body);
};