/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestLine.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:06:16 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/15 22:04:02 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RequestLine.hpp"
#include "utils.hpp"

using namespace std;

const string	RequestLine::_keyline[3] = {METHOD, PATH, VERSION};	

void	RequestLine::setRequestLine(string requestLine){
	list<string>			tokens;
	list<string>::iterator	it;
	int						i = -1;

	tokens = split<string, char, list<string> >(requestLine, ' ');
	for (it = tokens.begin(); it != tokens.end(); it++){
		setLine(getKeyRequestLine(++i), *it);
	}
}

void	RequestLine::setLine(string key, string value){
	_requestLine[key] = value;
}

string	RequestLine::getKeyRequestLine(int index) const {
	if(index < 0 || index > 3)
		return "Undefined";
	return _keyline[index];
}

string	RequestLine::getMethod() const{
	return _requestLine.at(METHOD);
}

string	RequestLine::getPath() const{
	return _requestLine.at(PATH);
}

string	RequestLine::getVersion() const{
	return _requestLine.at(VERSION);
}

RequestLine::RequestLine(){}
RequestLine::~RequestLine(){}
