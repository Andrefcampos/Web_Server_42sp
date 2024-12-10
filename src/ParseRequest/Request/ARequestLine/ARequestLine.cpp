/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ARequestLine.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:06:16 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/10 15:46:16 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ARequestLine.hpp"
#include "utils.hpp"

using namespace std;

int	ARequestLine::parseRequestLine(string requestLine){
	list<string>			tokens;
	list<string>::iterator	it;
	int						i = -1, error = 0;

	tokens = split<string, char, list<string> >(requestLine, ' ');
	if ((error = validSize(tokens)))
		return error;
	for (it = tokens.begin(); it != tokens.end(); it++){
		setLine(getKeyRequestLine(++i), *it);
	}
	if ((error = validMethod(_requestLine[METHOD])))
		return error;
	if ((error = validVersion(_requestLine[VERSION])))
		return error;
	return 0;
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

int		ARequestLine::getRequestLineError() const{
	return _requestLineError;
}

void	ARequestLine::setRequestLineError(int error){
	_requestLineError = error;
}

int ARequestLine::validSize(list<string> tokens){
	if (tokens.size() != 3)
		return 400;
	return 0;
}

int ARequestLine::validMethod(std::string method){
	trim(method);
	for (int i = 0; i < 3; i++){
		if (method == _method[i])
			return 0;
	}
	return 405;
}

int ARequestLine::validVersion(std::string version){
	string versionInUpperCase = toUpper(version);
	if (_versionHttp != versionInUpperCase)
		return 505;
	return 0;
}

const string	ARequestLine::_keyline[3] = {METHOD, PATH, VERSION};
const string	ARequestLine::_method[3] = {GET, POST, DELETE};
const string	ARequestLine::_versionHttp = VERSION_HTTP;