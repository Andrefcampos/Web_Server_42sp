/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Headers.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:25:37 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/06 12:20:42 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Headers.hpp"

const std::string	Headers::_delimit = ": ";
void Headers::setRequestHeaders(std::string header){
	size_t	pos;
	std::string	key = "", value = "";

	if (header.empty())
		return ;
	pos = header.find(_delimit);
	if (pos != std::string::npos){
		key = header.substr(0, pos);
		value = header.substr(pos + _delimit.size());
		_headers[key] = value;
	}else
		_headers[key] = value;
}


mapHeader Headers::setHeaders(std::list<std::string> tokens){
	std::list<std::string>::iterator it;

	for(it = tokens.begin(); it != tokens.end(); it++) 
		setRequestHeaders(*it);
	return _headers;
}