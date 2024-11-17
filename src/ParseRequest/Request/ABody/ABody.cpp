/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABody.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:13:34 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/17 14:34:07 by rbutzke          ###   ########.fr       */
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
		DataBody	data;
		string	line = getLineErase<string, string>(buffer, _boundary, false);
		if (line.empty()){
			parseElement(buffer, data);
			break ;
		}
		else
			parseElement(line, data);
		getLineErase<string, string>(buffer, _boundary, true);
	}
}

void	ABody::parseElement(string &boundary, DataBody &data){
	trim(boundary);
	if (boundary.empty())
		return ;
	string	headers = getLineErase<string, string>(boundary, "\r\n\r\n", true);
	setHeaders(headers, data);
	setContentBody(boundary, data);
}

void	ABody::setHeaders(string &headers, DataBody &data){
	if (headers.empty())
		return ;
	while(not headers.empty()){
		string	line = getLineErase<string, string>(headers, "\r\n", true);
		if (line.empty()){
			addNewHeaders(data, headers);
			break ;
		}
		else
			addNewHeaders(data, line);
	}
	putMapList(data.header);
}

void	ABody::setContentBody(string &contentBody, DataBody &data){
	trim(contentBody);
	if (contentBody.empty())
		return ;
	data.buffer = contentBody;
}

void	ABody::addNewHeaders(DataBody &data, string &headers){
	string	key = getLineErase<string, string>(headers, ": ", true);
	while(not headers.empty()){
		string	value  = getLineErase<string, string>(headers, "; ", true);;
		if (value.empty()){
			data.header[key].push_back(headers);
			break ;
		}
		else
			data.header[key].push_back(value);
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