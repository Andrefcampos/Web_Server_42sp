/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ARequestLine.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:06:16 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/17 11:31:41 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ARequestLine.hpp"
#include "utils.hpp"

using namespace std;

const string	ARequestLine::_keyline[3] = {METHOD, PATH, VERSION};	

void	ARequestLine::parseRequestLine(string requestLine){
	list<string>			tokens;
	list<string>::iterator	it;
	int						i = -1;

	tokens = split<string, char, list<string> >(requestLine, ' ');
	for (it = tokens.begin(); it != tokens.end(); it++){
		setLine(getKeyRequestLine(++i), *it);
	}
}

void	ARequestLine::setLine(string key, string value){
	trim(value);
	_requestLine[key] = value;
}

string	ARequestLine::getKeyRequestLine(int index) const {
	if(index < 0 || index > 3)
		return "Undefined";
	return _keyline[index];
}

string	ARequestLine::getMethod() const{
	return _requestLine.at(METHOD);
}

string	ARequestLine::getPath() const{
	return _requestLine.at(PATH);
}

string	ARequestLine::getVersion() const{
	return _requestLine.at(VERSION);
}

