/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ARequestLineValidations.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:30:26 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/13 12:34:48 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ARequestLine.hpp"
#include "utils.hpp"

const string	ARequestLine::_versionHttp = VERSION_HTTP;

int	ARequestLine::validRequestLine(){
	int	error = 0;

	if ((error = validMethod(_requestLine[METHOD])))
		return error;
	if ((error = validVersion(_requestLine[VERSION])))
		return error;
	return error;	
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