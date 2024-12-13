/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestValidations.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:38:32 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/13 13:25:54 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"
#include <cstdlib>

int		Request::validHeadersMethods(){
	string method = this->getMethod();

	if (method == GET || method == DELETE){
		if (_header.count(CLENGTH) || _header.count(TENCODING))
			return 409;
	}
	return 0;
}

#include <iostream>
int		Request::validBodySize(std::string buffer){
	long int length = strtol(_header[CLENGTH].front().c_str(), 0, 10);

	if ((long int)buffer.length() != length){
		return 400;
	}
	return 0;
}

