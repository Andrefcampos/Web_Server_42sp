/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataBody.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 08:24:25 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/19 11:26:37 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DataBody.hpp"
#include "utils.hpp"

DataBody::DataBody(){
	_content = "";
};

void	DataBody::setNewHeaders(string &key, string &value){
	trim(value);
	this->_headers[key].push_back(value);
}

void	DataBody::setContent(string &value){
	this->_content.append(value);
}

void	DataBody::setContentApend(string value, size_t length){
	_content.append(value.c_str(), length);
}

list<string> DataBody::getHeaders(string key) const{
	if (not _headers.count(key))
		return list<string>();
	return _headers.at(key);
}

map<string, list<string> >	DataBody::getAllHeaders() const{
	return _headers;
}

string DataBody::getContent() const{
	return _content;
}

DataBody &DataBody::operator=(const DataBody & orin){
	if(this != &orin){
		this->_headers = orin.getAllHeaders();
		this->_content = orin.getContent();
	}
	return *this;
}