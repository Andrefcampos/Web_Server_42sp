/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunked.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:36:12 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/06 14:30:21 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Chunked.hpp"
#include "utils.hpp"
#include <cstdlib>

void	Chunked::parseBody(string &buffer){
	size_t		bytes;
	DataBody	data;
	
	bytes = popNbrBytes(buffer);
	while(bytes > 0){
		data.setContentApend(popChunke(buffer, bytes), bytes);
		removeDelimiter(buffer);;
		bytes = popNbrBytes(buffer);
	}
	setDataBody(data);
}

void	Chunked::removeDelimiter(string &buffer){
	while (buffer[0] == '\n' || buffer[0] == '\r')
		buffer.erase(0, 1);
}

string	Chunked::popChunke(string &buffer, size_t length){
	string	value = buffer.substr(0, length);
	buffer.erase(0, length);
	return value;	
}

size_t	Chunked::popNbrBytes(string &buffer){
	string	nbrBytesInHex;
	size_t	nbrBytesInBuffer;

	if (buffer.empty())
		return 0;	
 	nbrBytesInHex = getLineErase<string, string>(buffer, "\r\n", true);
	trim(nbrBytesInHex);
	nbrBytesInBuffer = std::strtol(nbrBytesInHex.c_str(), 0, 16);
	return nbrBytesInBuffer;
}

Chunked::Chunked(){}
