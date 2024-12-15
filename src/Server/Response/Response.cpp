/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:09:58 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/15 14:33:35 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include <string>
#include "utils.hpp"


using namespace std;

Response::~Response(){}

Response::Response(){}

void	Response::sendIndex(int fd, string indexHTML){
	ifstream		file(indexHTML.c_str());
	string			html;
	std::time_t		time = 0;

	_response = new HTTP();
	_response->setStatusResponse("200", "OK");
	_response->setHeaders("Server", "MyServer");
	_response->setHeaders("Date", getCurrentDateTime(time));
	_response->setHeaders("Content-Type", "text/" + indexHTML.substr(indexHTML.rfind('.') + 1, indexHTML.length() - indexHTML.rfind('.')));
	_response->setHeaders("Connection", "close");
	getline(file, html, '\0');
	_response->setBody(html);

	cout << _response->getHTTP() << "\n";
	send(fd, _response->getHTTP().c_str(),_response->getHTTP().length(), 0);

	delete _response;
}

void	Response::sendImage(int fd, string image) {
	ifstream		file(image.c_str());
	stringstream	bImage;
	std::time_t		time = 0;

	try{
		bImage << file.rdbuf();
	}catch(exception &e){
		cerr << e.what();
	}
	_response = new HTTP();
	_response->setStatusResponse("200", "OK");
	_response->setHeaders("Server", "MyServer");
	_response->setHeaders("Date", getCurrentDateTime(time));
	_response->setHeaders("Content-Type", "image/png");
	_response->setHeaders("Connection", "close");
	_response->setBody(bImage.str());
	_response->setHeaders("Content-Length", bImage.str().length());
	cout << _response->getHTTP() << "\n";
	send(fd, _response->getHTTP().c_str(),_response->getHTTP().length(), 0);
	delete _response;

}

string Response::getPathImage() const{
	return _pathImage;
}

string Response::getPathIndex() const{
	return _pathIndex;
}

void Response::setPathImage(string pathImage){
	_pathImage = pathImage;
}

void Response::setPathIndex(string pathIndex){
	_pathIndex = pathIndex;
}
