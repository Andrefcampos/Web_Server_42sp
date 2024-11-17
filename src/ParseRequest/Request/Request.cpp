/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:25:54 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/17 14:34:33 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <vector>
#include <iostream>
#include "utils.hpp"
#include <cstring>

void	Request::setRequestLine(string &buffer){
	string	requestLine;

	if (_parsedRequestLine == true)
		return ;
	requestLine = getLineErase<string, string>(buffer, "\r\n", true);
	if (requestLine.empty())
		throw Request::RequestException("");
	this->parseRequestLine(requestLine);
	_parsedRequestLine = true;
}

void	Request::setHeader(string &buffer){
	string	headers;

	if (_parsedHeaders == true)
		return ;
	headers = getLineErase<string, string>(buffer, "\r\n\r\n", true);
	if (headers.empty())
		throw Request::RequestException("");
	this->parseHeaders(headers);
	haveBody();
	_parsedHeaders = true;
}

void	Request::setBody(string &buffer){
	if (_haveBody == false)
		return ;
	if (_haveBoundary == true){
		if (buffer.find(getEndBoundary()) == string::npos)
			throw Request::RequestException("");
		parseBody(buffer);
		return ;
	}
	if (buffer.length() < _lengthBody)
		throw Request::RequestException("");
	parseBody(buffer);
	return ;
}

void	Request::haveBody(){
	if (_header.count(CLENGTH)){
		_haveBody = true;
		_lengthBody = atoll(getHeader(CLENGTH).front().c_str());
	}
	if (_header.count(TENCODING) && getHeader(TENCODING).front() == CHUNKED){
		_haveBody = true;
		_is_chunked = true;
	}
	if (_header.count("Content-Type")){
		string	temp = getHeader("Content-Type").front();
		if (temp.find("boundary") != string::npos){
			temp.erase(0, temp.find("=")+1);
			this->setBondary(temp);
			_haveBoundary = true;
		}
	}
}

Request::Request(){
	_parsedRequestLine = false;
	_parsedHeaders = false;
	_parsedBody = false;
	_haveBody = false;
	_is_chunked = false;
}
