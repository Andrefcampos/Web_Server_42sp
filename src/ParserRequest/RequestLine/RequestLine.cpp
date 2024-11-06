/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestLine.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:25:00 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/06 11:43:00 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <RequestLine.hpp>
#include "split.hpp"

const std::string RequestLine::_keyLine[3] = {"Method", "Path", "Version"};
std::map<std::string, std::string> 
RequestLine::setRequestLine(std::string line){
	std::list<std::string>::iterator	it;
	int									i = 0;

	_tokens = split(line, ' ');
	for (it = _tokens.begin(); it != _tokens.end(); it++){
		_requestLine[_keyLine[i]] = *it;
		i++;
	}
	return _requestLine;
}