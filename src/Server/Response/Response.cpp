/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:09:58 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/06 17:11:45 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"
#include "Response.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <bitset>
#include <sstream>
#include <error.h>
#include <cstring>

Response::~Response(){}

Response::Response(){
	clean();
}

void	Response::setStatus(std::string value, std::string reason){
	this->_fillHttp[STATUS][VALUE] = value;
	this->_fillHttp[STATUS][REASON] = reason;
}
void	Response::setType(std::string type){
	this->_fillHttp[TYPE][HEADER_TYPE] = type;
}

void	Response::setConnection(std::string connection){
	this->_fillHttp[CONNECTION][HEADER_TYPE] = connection;
}

void	Response::setLength(std::string length){
	this->_fillHttp[LENGTH][HEADER_TYPE] = length;
}

void	Response::setBody(std::string body){
	this->_body = body;
}

std::string	Response::getHttp(){
	this->_http += this->_fillHttp[STATUS][HTTP_VERSION];
	this->_http += this->_fillHttp[STATUS][VALUE];
	this->_http += this->_fillHttp[STATUS][REASON];
	this->_http += this->_fillHttp[STATUS][END_LINE];
	this->_http += this->_fillHttp[TYPE][HEADER];
	this->_http += this->_fillHttp[TYPE][HEADER_TYPE];
	this->_http += this->_fillHttp[TYPE][ENDL];
	this->_http += this->_fillHttp[CONNECTION][HEADER];
	this->_http += this->_fillHttp[CONNECTION][HEADER_TYPE];
	this->_http += this->_fillHttp[CONNECTION][ENDL];
	this->_http += this->_fillHttp[LENGTH][HEADER];
	this->_http += this->_fillHttp[LENGTH][HEADER_TYPE];
	this->_http += this->_fillHttp[LENGTH][ENDL];
	this->_http += this->_body;
	return (this->_http);
}

void	Response::sendIndex(int fd, std::string indexHTML){
	std::ifstream		file(indexHTML.c_str());
	std::stringstream	status, lengh;
	std::string			html;

	std::getline(file, html, '\0');
	status << 200;
	this->setStatus(status.str(), " Ok");
	this->setType("text/html");
	this->setConnection("MeuServidor/1.0 (Linux) ");
	lengh << html.length();
	this->setLength(lengh.str());
	this->setBody(html);
	send(fd, this->getHttp().c_str(),this->getHttp().length(), 0);
	clean();
}

void	Response::sendImage(int fd, std::string image)
{
	std::ifstream		file(image.c_str());
	std::stringstream	bImage, status, lengh;

	status << 200;
	try{
		bImage << file.rdbuf();
	}catch(std::exception &e){
		std::cerr << e.what();
	}
	this->setStatus(status.str(), " Ok");
	this->setType("image/png");
	this->setConnection("MeuServidor/1.0 (Linux)");
	lengh << bImage.str().length();
	this->setLength(lengh.str());
	setBody(bImage.str());
	if (send(fd, this->getHttp().c_str(),this->getHttp().length(), 0) == -1)
		std::cerr << "DEU MERDA\n";
	clean();
}

void Response::clean(){
	this->_fillHttp[STATUS][HTTP_VERSION] = "HTTP/1.1 ";
	this->_fillHttp[STATUS][VALUE] = "";
	this->_fillHttp[STATUS][REASON] = "";
	this->_fillHttp[STATUS][END_LINE] = "\r\n";
	this->_fillHttp[TYPE][HEADER] = "Content-Type: ";
	this->_fillHttp[TYPE][HEADER_TYPE] = "";
	this->_fillHttp[TYPE][ENDL] = "\r\n";
	this->_fillHttp[CONNECTION][HEADER] = "Server: ";
	this->_fillHttp[CONNECTION][HEADER_TYPE] = "";
	this->_fillHttp[CONNECTION][ENDL] = "\r\n";
	this->_fillHttp[LENGTH][HEADER] = "Content-Length: ";
	this->_fillHttp[LENGTH][HEADER_TYPE] = "";
	this->_fillHttp[LENGTH][ENDL] = "\r\n\r\n";
	this->_body = "";
	this->_http = "";
}

std::string Response::getPathImage() const{
	return _pathImage;
}

std::string Response::getPathIndex() const{
	return _pathIndex;
}

void Response::setPathImage(std::string pathImage){
	_pathImage = pathImage;
}

void Response::setPathIndex(std::string pathIndex){
	_pathIndex = pathIndex;
}
