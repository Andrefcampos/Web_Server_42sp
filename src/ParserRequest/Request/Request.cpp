/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:25:54 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/15 14:32:08 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <vector>
#include "split.hpp"

void	Request::setHeader(string headers){
}

void	Request::setBody(string body){
}

void Request::setRequestHeaders(string header){
	size_t	pos;
	string	key = "", value = "";

	if (header.empty())
		return ;
	pos = header.find(_delimit);
	if (pos != string::npos){
		key = header.substr(0, pos);
		value = header.substr(pos + _delimit.size());
		value.erase(remove(value.begin(), value.end(), '\r'), value.end());
		_headers[key] = value;
	}else
		_headers[key] = value;
}

void	Request::setHeaders(string headers){
	list<string>::iterator	it;

	for(it = tokens.begin(); it != tokens.end(); it++)
		setRequestHeaders(*it);
	return _headers;
}