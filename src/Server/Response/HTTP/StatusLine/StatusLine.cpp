/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusLine.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:57:53 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/15 14:30:32 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StatusLine.hpp"
#include <sstream>

StatusLine::StatusLine():_version("HTTP/1.1"), _statusCode("0"), _statusMessage(""){}

void		StatusLine::setStatusCode(int statusCode){
	std::stringstream ss;
	ss << statusCode;
	_statusCode = ss.str();
}

void		StatusLine::setStatusCode(std::string statusCode){
	_statusCode = statusCode;
}

void		StatusLine::setStatusMensage(std::string statusMessage){
	_statusMessage = statusMessage;
}
	
std::string	StatusLine::getResponseStatusLine() const{
	std::ostringstream statusLine;
	statusLine << _version << " ";
	statusLine << _statusCode << " "; 
	statusLine << _statusMessage << "\r\n"; 

	return statusLine.str();
}

std::ostream &operator<<(std::ostream &os, const StatusLine &statusLine){
	os << statusLine.getResponseStatusLine();
	return os;
}
