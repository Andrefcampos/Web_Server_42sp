/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MultPart.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:14:54 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/17 17:28:50 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MultPart.hpp"
#include "utils.hpp"

void	MultPart::parseBody(string &buffer){
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

void	MultPart::parseElement(string &boundary){
	trim(boundary);
	if (boundary.empty())
		return ;
	string	headers = getLineErase<string, string>(boundary, "\r\n\r\n", true);
	setHeaders(headers);
	setContentBody(boundary);
}

void	MultPart::setHeaders(string &headers){
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
	putMapList(getAllHeaders());
}

void	MultPart::setContentBody(string &contentBody){
	trim(contentBody);
	if (contentBody.empty())
		return ;
	setContent(contentBody);
}

void	MultPart::addNewHeaders(string &headers){
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