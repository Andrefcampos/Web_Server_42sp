/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MultPart.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:14:54 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/19 11:43:00 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MultPart.hpp"
#include "utils.hpp"
#include <fstream>

void	MultPart::parseBody(string &buffer){
	formatBuffer(buffer);
	if (buffer.empty())
		return ;
	while(not buffer.empty()){
		string	line = getLineErase<string, string>(buffer, _boundary, false);
		DataBody	data;
		if (line.empty()){
			parseElement(buffer, data);
			break ;
		}
		else
			parseElement(line, data);
		getLineErase<string, string>(buffer, _boundary, true);
	}
}

void	MultPart::parseElement(string &boundary, DataBody &data){
	trim(boundary);
	if (boundary.empty())
		return ;
	string	headers = getLineErase<string, string>(boundary, "\r\n\r\n", true);
	setHeaders(headers, data);
	setContentBody(boundary, data);
	setDataBody(data);
}

void	MultPart::setHeaders(string &headers, DataBody &data){
	if (headers.empty())
		return ;
	while(not headers.empty()){
		string	line = getLineErase<string, string>(headers, "\r\n", true);
		if (line.empty()){
			addNewHeaders(headers, data);
			break ;
		}
		else
			addNewHeaders(line, data);
	}
}

void	MultPart::setContentBody(string &contentBody, DataBody &data){
	trim(contentBody);
	if (contentBody.empty())
		return ;
	data.setContent(contentBody);
}

void	MultPart::addNewHeaders(string &headers, DataBody &data){
	string	key = getLineErase<string, string>(headers, ": ", true);
	while(not headers.empty()){
		string	value  = getLineErase<string, string>(headers, "; ", true);;
		if (value.empty()){
			data.setNewHeaders(key, headers);
			break ;
		}
		else
			data.setNewHeaders(key, value);
	}
}

void	MultPart::setBondary(string boundary){
	trim(boundary);
	_boundary = "--";
	_boundary += boundary;
	_endboundary = "\r\n";
	_endboundary += _boundary;
	_endboundary += "--";
}

string	MultPart::getEndBoundary() const {
	return _endboundary;
}

string	MultPart::getBoundary() const {
	return _boundary;
}

void	MultPart::formatBuffer(string &buffer){
	if (buffer.empty())
		return ;
	if (buffer.find(_endboundary) != string::npos)
		buffer.erase(buffer.find(_endboundary), _endboundary.length());
	if (buffer.find(_boundary) == 0)
		buffer.erase(0, _boundary.length());
}

MultPart::MultPart(){
	_boundary = "";
	_endboundary = "";
};
