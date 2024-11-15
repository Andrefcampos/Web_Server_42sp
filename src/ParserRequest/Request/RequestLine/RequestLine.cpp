/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestLine.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:06:16 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/15 16:02:10 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestLine.hpp"
#include "split.hpp"

using namespace std;

const string	RequestLine::keyline[3] = {METHOD, PATH, VERSION};	

void	RequestLine::setRequestLine(string requestLine){
	list<string>			tokens;
	list<string>::iterator	it;
	int						i = -1;

	tokens = split<string, char, list<string> >(requestLine, ' ');
	for (it = tokens.begin(); it != tokens.end(); it++){
		setLine(getKeyRequestLine(++i), *it);
		_requestLine[getKeyRequestLine(i)] = *it;
	}
}

void	RequestLine::setLine(string key, string value){
	_requestLine[key] = value;
}

string	RequestLine::getKeyRequestLine(int index) const {
	if(index < 0 || index > 3)
		return "Undefined";
	return _keyLine[index];
}

void	RequestLine::setLine(string key, string value){
	_requestLine[key] = value;
}

string	RequestLine::getMethod() const{
	return _requestLine[METHOD];
}

string	RequestLine::getPath() const{
	return _requestLine[PATH];
}

string	RequestLine::getVersion() const{
	return _requestLine[VERSION];
}

RequestLine::RequestLine(){}
RequestLine::~RequestLine(){}
