/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHeaders.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:06:54 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/13 12:11:08 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cctype>
#include "AHeaders.hpp"
#include "utils.hpp"
#include "Client.hpp"

int	AHeaders::parseHeaders(string &headers, Client *client){
	string	line;

	while (!headers.empty()){
		line = getLineErase<string, string>(headers, "\r\n", true);
		if(line.empty()){
			setLastHeader(headers);
			break ;
		}
		setHeaders(line);
	}
	return validHeaders(client);
}

void AHeaders::setLastHeader(string &headers){
	if(headers.empty())
		return ;
	string	key = getLineErase<string, string>(headers, ": ", true);
	string	value = getLineErase<string, string>(headers, ",", true);
	if (value.empty()){
		addNewElement(key, headers);
		headers.clear();
		return ;
	}
	addNewElement(key, value);
	if (!headers.empty()){
		addNewElement(key, headers);
		headers.clear();
	}
}

void AHeaders::setHeaders(string &line){
	string	key = getLineErase<string, string>(line, ": ", true);

	while(line.length() > 0){
		string	value = getLineErase<string, string>(line, ",", true);
		if (value.empty()){
			addNewElement(key, line);
			break ;
		}
		addNewElement(key, value);
	}
}

void	AHeaders::addNewElement(string key, string value){
	trim(value);
	_header[key].push_back(value);
}

list<string>	AHeaders::getHeader(string key) const {
	if (not _header.count(key) || _header.empty())
		return list<std::string>();
	return _header.at(key);
}

map<string, list<string> >	AHeaders::getAllHeader() const{
	return _header;
}

string	AHeaders::getHost() const{
	if(_header.empty())
		return "";
	return *_header.at(HOST).begin();;
}
