/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHeadersValidations.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 12:10:27 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/13 12:37:50 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AHeaders.hpp"
#include <cstdlib>

int		AHeaders::validHeaders(Client *client){
	int error = 0;

	if ((error = validContentLength(client)))
		return error;
	if ((error = validAmbiguityHeaders()))
		return error;
	if ((error = validTransferEnconding()))
		return error;
	if ((error = validHost()))
		return error;
	return 0;
}

int		AHeaders::validContentLength(Client *client){
	if (not _header.count(CLENGTH))
		return 0;
	long long int length = strtol(_header[CLENGTH].front().c_str(), 0, 10);
	if (length < 0)
		return 400;
	if (client->getMaxSize() < length)
		return 413;
	return 0;
};

int		AHeaders::validAmbiguityHeaders(){
	if (_header.count(CLENGTH) && _header.count(TENCODING))
		return 400;
	return 0;
}

int		AHeaders::validTransferEnconding(){
	if (not _header.count(TENCODING))
		return 0;
	list<string>::iterator it = _header[TENCODING].begin();
	for(; it != _header[TENCODING].end(); it++){
		if (*it != CHUNKED)
			return 415;	
	}
	return 0;
}

int		AHeaders::validHost(){
	if (not _header.count(HOST))
		return 400;
	return 0;
}
