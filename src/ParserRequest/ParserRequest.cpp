/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:16:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/15 13:40:29 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParserRequest.hpp"
#include <sys/socket.h>
#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include <list>
#include <string>
#include <iterator>
#include "split.hpp"
#include <cstdlib>
#include "Server.hpp"
#include <sstream>

int	ParserRequest::setBufferSocketFd(int fd){
	ctrlNewRequests(fd);
	if (setBody(fd))
		return 1;
	if (requestLineHeader(fd))
		return 1;
	return 0;
}

void ParserRequest::ctrlNewRequests(int fd){
	if (not _dataSocket.count(fd)){
		_dataSocket[fd].haveBody = false;
		_dataSocket[fd].lentgh = 0;
	}
}

int	ParserRequest::setBody(int fd){
	using namespace std;
	char		buffer[BUFFERSIZE +1];
	ssize_t		bufferRead;
	memset(buffer, 0, BUFFERSIZE+1);

	if (_dataSocket[fd].haveBody){
		bufferRead = recv(fd, buffer, BUFFERSIZE, MSG_DONTWAIT);
		if (bufferRead == -1)
			return 1;
		_dataSocket[fd].buffer.append(buffer, bufferRead);
		if (_dataSocket[fd].buffer.length() >= _dataSocket[fd].lentgh){
			parseBody(fd, _dataSocket[fd]);
			cout << _dataSocket[fd].buffer << '\n';
			_httpRequest[fd]["Body"]["Body"] = _dataSocket[fd].buffer;
			_dataSocket.erase(fd);
			return 1;
		}
	}
	return 0;
}

void	ParserRequest::parseBody(int fd, dataSocketFD &data){
	using namespace std;
	size_t find = data.buffer.find(data.boundaryBegin);
	size_t findEnd = data.buffer.find(data.boundaryEnd);
	if (find != string::npos)
		data.buffer.erase(0, data.boundaryBegin.length());
	if (findEnd != string::npos)
		data.buffer.erase(findEnd, data.boundaryEnd.length());

	find = data.buffer.find(data.boundaryBegin);
	if (find != string::npos){
		string content = data.buffer.substr(0, find);
		parse(content);
		cout << content << '\n';
		data.buffer.erase(0, content.length());
		parseBody(fd, data);
	}
}

void	ParserRequest::parse(std::string content){
	std::size_t find = content.find(DELIMITER);
	if (find != std::string::npos){
		std::string temp = content.substr(0, find);
		
		mapHeader	map;
		map[temp] = content;
		
		
	}
}

int	ParserRequest::requestLineHeader(int fd){
	using namespace std;
	char		buffer[BUFFERSIZE +1];
	ssize_t		bufferRead;
	memset(buffer, 0, BUFFERSIZE+1);

	if (_dataSocket[fd].haveBody == false){
		bufferRead = recv(fd, buffer, BUFFERSIZE, MSG_DONTWAIT);
		if (bufferRead == -1)
			runtime_error("error: recv()");
		_dataSocket[fd].buffer.append(buffer, bufferRead);
		if (_dataSocket[fd].buffer.find(DELIMITER) != string::npos){
			cout << _dataSocket[fd].buffer << '\n';
			if (parseHttpClient(_dataSocket[fd], fd)){
				return 0;
			}
			_dataSocket.erase(fd);
			return (1);
		}
	}
	return 0;	
}

int	ParserRequest::parseHttpClient(dataSocketFD &data, int fd){
	if (haveBody(data, fd))
		return 1;
	setMapRequest(data.buffer, fd);
	return 0;
}

int		ParserRequest::haveBody(dataSocketFD &data, int fd){
	using namespace std;
	if (data.buffer.find("Content-Length") != string::npos){
		data.haveBody = true;
		size_t	find = data.buffer.find(DELIMITER);
		if (find == string::npos)
			return 1;
		string requestLineHeader = data.buffer.substr(0, find + LIMIT_SIZE);
		setMapRequest(requestLineHeader, fd);
		setBoundary(data, fd);
		data.buffer = data.buffer.erase(0, find + LIMIT_SIZE);
		data.lentgh = atoll(_httpRequest[fd][HEADERS]["Content-Length"].c_str());
		if (data.buffer.size() < data.lentgh)
			return 1;
	}
	return 0;
}

int	ParserRequest::setMapRequest(std::string &buffer, int fd){
	using namespace std;
	list<string>	tokens;
	tokens = split<string, char, list<string> >(buffer, '\n');
	_httpRequest[fd][REQUESTLINE] = setRequestLine(*tokens.begin());
	tokens.remove(*tokens.begin());
	_httpRequest[fd][HEADERS] = setHeaders(tokens);
	return 0;
}

void	ParserRequest::setBoundary(dataSocketFD &data, int fd){
	using namespace std;
	string	temp;
	temp = _httpRequest[fd][HEADERS]["Content-Type"];	
	size_t findBoundary = temp.find("boundary");
	if (findBoundary != string::npos){
		list<string>	tokens;
		tokens = split<string, char, list<string> >(temp, '=');
		data.boundaryBegin += "\r\n--";
		data.boundaryBegin += *(++tokens.begin());
		data.boundaryEnd += data.boundaryBegin;
		data.boundaryEnd += "--\r\n";
	}
}

ParserRequest::ParserRequest(){}

ParserRequest::~ParserRequest(){}
