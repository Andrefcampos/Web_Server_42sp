/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Headers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 18:51:33 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/15 14:34:45 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers.hpp"
#include <sstream>

using namespace std;
std::string	Headers::_keys[7] = {"Server", "Date", "Content-Type",\
								"Content-Length", "Connection",\
								"Cache-Control", "Expires"};

Headers::Headers(){
	_headers["Server"] = "MyWebServe";
	_headers["Date"];
	_headers["Content-Type"];
	_headers["Content-Length"];
	_headers["Connection"];
	_headers["Cache-Control"];
	_headers["Expires"];
}

string	Headers::getBufferHeaders() const{
	std::map<std::string, std::string>::const_iterator	it, ite;
	std::ostringstream									buffer;

	it = _headers.begin();
	ite = _headers.end();
	while (it != ite){
		if (not it->second.empty())
			buffer << it->first << ": " << it->second << "\r\n";
		it++;
	}
	buffer << "\r\n";
	return buffer.str();
}

int		Headers::thereIsHeader(std::string KeyHeader){
	for (int i = 0; i < 7; i++){
		if (KeyHeader == _keys[i])
			return 1;
	}
	return 0;
}

std::ostream &operator<<(std::ostream &os, const Headers &headers){
	os << headers.getBufferHeaders();
	return os;
}