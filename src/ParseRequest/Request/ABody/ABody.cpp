/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABody.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:13:34 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/17 17:38:02 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ABody.hpp"
#include <iostream>
#include "utils.hpp"

void	ABody::parseBody(string &buffer){
	formatBuffer(buffer);
	if (buffer.empty())
		return ;
	while(not buffer.empty()){
		string	line = getLineErase<string, string>(buffer, _boundary, false);
		if (line.empty()){
			parseElement(buffer);
			break ;
		}
		else
			parseElement(line);
		getLineErase<string, string>(buffer, _boundary, true);
	}
}

void	ABody::parseElement(string &boundary){
	if (boundary.empty())
		return ;
	string	headers = getLineErase<string, string>(boundary, "\r\n\r\n", true);
	setHeaders(headers);
	setContentBody(boundary);
}

void	ABody::setHeaders(string &headers){
	if (headers.empty())
		return ;
	while(not headers.empty()){
		string	line = getLineErase<string, string>(headers, "\r\n", true);
		if (line.empty()){
			addNewHeaders(headers);
			break ;
		}
		else
			addNewHeaders(line);
	}
}

void	ABody::setContentBody(string &contentBody){
	trim(contentBody);
	if (contentBody.empty())
		return ;
	setContent(contentBody);
}

void	ABody::addNewHeaders(string &headers){
	string	key = getLineErase<string, string>(headers, ": ", true);
	while(not headers.empty()){
		string	value  = getLineErase<string, string>(headers, "; ", true);;
		if (value.empty()){
			setNewHeaders(key, headers);
			break ;
		}
		else
			setNewHeaders(key, value);
	}
}

void	ABody::setBondary(string boundary){
	trim(boundary);
	_boundary = "--";
	_boundary += boundary;
	_endboundary = "\r\n";
	_endboundary += _boundary;
	_endboundary += "--";
}

string	ABody::getEndBoundary() const {
	return _endboundary;
}

string	ABody::getBoundary() const {
	return _boundary;
}

ABody::ABody(){
	_boundary = "";
	_endboundary = "";
};

void	ABody::formatBuffer(string &buffer){
	if (buffer.empty())
		return ;
	if (buffer.find(_endboundary) != string::npos)
		buffer.erase(buffer.find(_endboundary), _endboundary.length());
	if (buffer.find(_boundary) == 0)
		buffer.erase(0, _boundary.length());
}

void	ABody::setNewHeaders(string &key, string &value){
	this->_headers[key].push_back(value);
}

void	ABody::setContent(string &value){
	this->_content = value;
}

list<string> ABody::getHeaders(string key) const{
	if (not _headers.count(key))
		return list<string>();
	return _headers.at(key);
}

map<string, list<string> >	ABody::getAllHeaders() const{
	return _headers;
}

string ABody::getContent() const{
	return _content;
}