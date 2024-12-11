/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPage.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:32:28 by myokogaw          #+#    #+#             */
/*   Updated: 2024/12/03 17:32:28 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ErrorPage.hpp"
#include <iostream>

using namespace std;

ErrorPage::ErrorPage() : _codes(), _uri() {}

ErrorPage::~ErrorPage() {}

void	ErrorPage::appendCode(const string &code) {
	this->_codes.push_back(code);
}

void	ErrorPage::setUri(const string &uri) {
	this->_uri = uri;
}

bool	ErrorPage::hasCode(const string &code) const {
	for (vector<string>::const_iterator it = _codes.begin(); it != _codes.end(); ++it) {
		if (*it == code)
			return (true);
	}
	return (false);
}

const string &ErrorPage::getUri(void) const {
	return (this->_uri);
}

void		ErrorPage::print(void) const {
	cout << "Error Page URI: " << _uri << endl;
	cout << "Codes covered:";
	for (vector<string>::const_iterator it = _codes.begin(); it != _codes.end(); ++it) {
		cout << "	" << *it;
	}
	return ;
}