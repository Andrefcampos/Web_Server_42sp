/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Headers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:06:54 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/15 22:35:08 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers.hpp"
#include <iostream>
#include "utils.hpp"

void	Headers::parseHeaders(string &headers){
	string	line;

	cout << headers << "\n\n\n";

	while (!headers.empty()){
		line = getLine<string, string>(headers, "\r\n");
		if(line.empty()){
			setLastHeader(headers);
			break ;
		}
		setHeaders(line);
	}
}

void Headers::setLastHeader(string &headers){
	if(headers.empty())
		return ;
	string	key = getLine<string, string>(headers, ": ");
	string	value = getLine<string, string>(headers, ",");
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

void Headers::setHeaders(string &line){
	string	key = getLine<string, string>(line, ": ");

	while(line.length() > 0){
		string	value = getLine<string, string>(line, ",");
		if (value.empty()){
			addNewElement(key, line);
			break ;
		}
		addNewElement(key, value);
	}
}

void	Headers::addNewElement(string key, string value){
	trim(value);
	_header[key].push_back(value);
}

list<string>	Headers::getHeader(string key) const {
	return _header.at(key);
}

map<string, list<string> >	Headers::getAllHeader() const{
	return _header;
}