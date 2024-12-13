/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:25:54 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/13 13:19:23 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <vector>
#include <iostream>
#include "utils.hpp"
#include <cstring>
#include "algorithm"
#include "MultPart.hpp"
#include "Chunked.hpp"
#include "SimpleBody.hpp"

int	Request::setRequestLine(string &buffer){
	string	requestLine;
	int		error;

	if (_parsedRequestLine == true)
		return 0;
	requestLine = getLineErase<string, string>(buffer, "\r\n", true);
	if (requestLine.empty())
		throw Request::RequestException("");
	_parsedRequestLine = true;
	error = this->parseRequestLine(requestLine);
	if (not error)
		return 0;
	return error;
}

int	Request::setHeader(string &buffer, Client *client){
	string	headers;
	int		error = 0;

	if (_parsedHeaders == true)
		return 0;
	headers = getLineErase<string, string>(buffer, "\r\n\r\n", true);
	if (headers.empty())
		throw Request::RequestException("");
	if ((error = this->parseHeaders(headers, client)))
		return error;
	if ((error = validHeadersMethods()))
		return error;
	checkBodyFormatting();
	_parsedHeaders = true;
	return 0;
}

int		Request::setBody(string &buffer){
	int error = 0;
	
	if (not _haveBody)
		return 0;
	if (_isMultPartBody == true){
		string	endBoundary = static_cast<MultPart *>(body)->getEndBoundary();
		if (buffer.find(endBoundary) == string::npos)
			throw Request::RequestException("");
		if ((error = validBodySize(buffer)))
			return error;
		body->parseBody(buffer);
		_parsedBody = true;
		return 0;
	}
	if (_isChunkedBody == true){
		if (buffer.find("0\r\n\r\n") == string::npos)
			throw Request::RequestException("");
		body->parseBody(buffer);
		_parsedBody = true;
		return 0;
	}
	if (_isSimpleBody == true){
		if (buffer.length() < body->getLengthBody())
			throw Request::RequestException("");
		if ((error = validBodySize(buffer)))
			return error;
		body->parseBody(buffer);
		_parsedBody = true;
		return 0;
	}
	return 0;
}

void	Request::instanceBody(){
	if (not _haveBody)
		return ;
	if (_isMultPartBody && _isSimpleBody)
		initMultPart();
	if (not _isMultPartBody && _isSimpleBody)
		initSimpleBody();
	if (_isChunkedBody)
		initChunked();
}

void	Request::initSimpleBody(){
	SimpleBody *simpleBody = new SimpleBody();
	simpleBody->setLengthBody(_bodyLength);
	body = simpleBody;	
}

void	Request::initMultPart(){
	MultPart *mult = new MultPart();

	string	temp = getHeader("Content-Type").front();
	if (temp.find("boundary") != string::npos){
		temp.erase(0, temp.find("=")+1);
		mult->setBondary(temp);
		mult->setLengthBody(_bodyLength);
	}
	body = mult;
}


void	Request::initChunked(){
	Chunked *chunked = new Chunked();

	body = chunked;
}


void	Request::checkBodyFormatting(){
	isMultPartBody();
	isSimpleBody();
	isChunkedBody();
	instanceBody();
}

void	Request::isMultPartBody(){
	if (not _header.count(CTYPE))
		return ;
	list<string> values = getHeader(CTYPE);
	list<string>::iterator it;
	if (values.empty())
		return ;
	for (it = values.begin(); it != values.end(); it++){
		string val = *it;
		if (val.find(MPART) != string::npos){
			_isMultPartBody = true;
			_haveBody = true;
			break ;
		}
	}
}

void	Request::isSimpleBody(){
	if (not _header.count(CLENGTH))
		return ;
	_haveBody = true;
	_isSimpleBody = true;
	_bodyLength = atoll(getHeader(CLENGTH).front().c_str());
}

void	Request::isChunkedBody(){
	if (not _header.count(TENCODING))
		return ;
	list<string> values = getHeader(TENCODING);
	list<string>::iterator it;
	if (values.empty())
		return ;
	for (it = values.begin(); it != values.end(); it++){
		string val = *it;
		if (val.find(CHUNKED) != string::npos){
			_isChunkedBody = true;
			_haveBody = true;
			break ;
		}
	}
}

Request::~Request(){
	if (body)
		delete body;
};

Request::Request(){
	_parsedRequestLine = false;
	_parsedHeaders = false;
	_parsedBody = false;
	_isMultPartBody = false;
	_isSimpleBody = false;
	_isChunkedBody = false;
	_haveBody = false;
	_parserError = 0;
	body = NULL;
}

ABody	*Request::getBody(){
	return body;
}

void	Request::setParserError(int error){
	_parserError = error;
}

int		Request::getParserError() const{
	return _parserError;
}
