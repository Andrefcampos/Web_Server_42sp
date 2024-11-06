/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:09:58 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/01 16:37:37 by rbutzke          ###   ########.fr       */
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

	this->_htpp += this->_fillHttp[STATUS][HTTP_VERSION];
	this->_htpp += this->_fillHttp[STATUS][VALUE];
	this->_htpp += this->_fillHttp[STATUS][REASON];
	this->_htpp += this->_fillHttp[STATUS][END_LINE];
	this->_htpp += this->_fillHttp[TYPE][HEADER];
	this->_htpp += this->_fillHttp[TYPE][HEADER_TYPE];
	this->_htpp += this->_fillHttp[TYPE][ENDL];
	this->_htpp += this->_fillHttp[CONNECTION][HEADER];
	this->_htpp += this->_fillHttp[CONNECTION][HEADER_TYPE];
	this->_htpp += this->_fillHttp[CONNECTION][ENDL];
	this->_htpp += this->_fillHttp[LENGTH][HEADER];
	this->_htpp += this->_fillHttp[LENGTH][HEADER_TYPE];
	this->_htpp += this->_fillHttp[LENGTH][ENDL];
	this->_htpp += this->_body;
	return (this->_htpp);
}

void	Response::sendResponseHTML(int fd, std::string indexHTML)
{
	std::ifstream		file(indexHTML.c_str());
	std::stringstream	status, lengh;
	std::string			html;

	std::getline(file, html, '\0');
	status << 200;
	this->setStatus(status.str(), " Ok");
	this->setType("text/html");
	this->setConnection("");
	lengh << html.length();
	this->setLength(lengh.str());
	this->setBody(html);
	send(fd, this->getHttp().c_str(),this->getHttp().length(), 0);
	clean();
}

void	Response::sendResponseImage(int fd, std::string image)
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
	this->setConnection("");
	lengh << bImage.str().length();
	this->setLength(lengh.str());
	send(fd, this->getHttp().c_str(),this->getHttp().length(), 0);
	send(fd, bImage.str().c_str(), bImage.str().length(), 0);
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
	this->_fillHttp[CONNECTION][HEADER] = "Connection: ";
	this->_fillHttp[CONNECTION][HEADER_TYPE] = "";
	this->_fillHttp[CONNECTION][ENDL] = "\r\n";
	this->_fillHttp[LENGTH][HEADER] = "Content-Length: ";
	this->_fillHttp[LENGTH][HEADER_TYPE] = "";
	this->_fillHttp[LENGTH][ENDL] = "\r\n\r\n";
	this->_body = "";
	this->_htpp = "";
}