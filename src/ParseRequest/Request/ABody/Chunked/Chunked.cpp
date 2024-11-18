/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunked.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:36:12 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/18 19:07:21 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Chunked.hpp"
#include "utils.hpp"
#include <cstdlib>

void	Chunked::parseBody(string &buffer){

	string		sizeHexDecimal, value;
	DataBody	data;

	
 	sizeHexDecimal = getLineErase<string, string>(buffer, "\r\n", true);
	trim(sizeHexDecimal);
	_bytes = std::strtol(sizeHexDecimal.c_str(), 0, 16);

	while(_bytes > 0){
		value = getLineErase<string, string>(buffer, "\r\n", true);
		trim(value);
		data.setContentApend(value, _bytes);
	
	 	sizeHexDecimal = getLineErase<string, string>(buffer, "\r\n", true);
		trim(sizeHexDecimal);
		_bytes = std::strtol(sizeHexDecimal.c_str(), 0, 16);
	}

	cout << data.getContent() << '\n';
}

void	Chunked::getLineAndRemove(string &buffer, size_t length, DataBody &data){
	if (buffer.empty())
		return ;
	string value = buffer.substr(0, length);
	buffer.erase(0, length);
	data.setContentApend(value, length);
}

Chunked::Chunked(){
	_bytes = 0;
}

void	debug(string buffer){

	for(size_t i = 0; i < buffer.size(); i++){
		if (buffer[i] == '\r'){
			cout << "\\r" << flush; 
			i++;
		}
		if (buffer[i] == '\n'){
			cout << "\\n" << flush;
			i++;
		}
		if (buffer[i] != '\n' || buffer[i] != '\r')
			cout << buffer[i] << flush;
	}
}