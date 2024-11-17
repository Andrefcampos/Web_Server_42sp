/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataBody.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:37:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/17 17:16:31 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DataBody.hpp"

void	DataBody::setNewHeaders(string &key, string &value){
	this->_headers[key].push_back(value);
}

void	DataBody::setContent(string &value){
	this->_content = value;
}

list<string>	DataBody::getHeaders(string key) const{
	if (not _headers.count(key))
		return list<string>();
	return _headers.at(key);
}

map<string, list<string> >	DataBody::getAllHeaders() const{
	return _headers;
}

string			DataBody::getContent() const{
	return _content;
}

DataBody::DataBody(){}

DataBody::~DataBody(){}
