/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:16:45 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/03 17:25:52 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ParserRequest.hpp"
#include <sys/socket.h>
#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include <list>
#include <string>
#include <iterator>
#include "split.hpp"

std::map<std::string, std::string>	ParserRequest
::parseHttpClient(std::string htppRequest){
	std::list<std::string>				tokens;
	std::map<std::string, std::string>	parse;
	std::list<std::string>				for_map;
	std::list<std::string>::iterator	it, it2, it3;
	
	tokens = split(htppRequest, '\n');
	it = tokens.begin();
	std::string	method(*it);
	it++;
	while(it != tokens.end()){
		for_map = split(*it, ':');
		if (!for_map.empty()){
			if (++for_map.begin() != for_map.end()){
				std::cout << *for_map.begin() << " " << *++for_map.begin() << "\n";
				parse[*for_map.begin()] = *++for_map.begin();
			}
		}
		it++;
	}
	return parse;
}

void	ParserRequest::readFdClient(epoll_event &events, epoll_event &ev, int &epollfd){
	char		buffer[BUFFERSIZE +1];
	ssize_t		bufferRead;
	std::memset(buffer, 0, BUFFERSIZE+1);


	bufferRead = recv(events.data.fd, buffer, BUFFERSIZE, MSG_DONTWAIT);
	_oneRequest[events.data.fd] += buffer;
	if (bufferRead == -1)
		std::runtime_error("error: recv()");
	if (_oneRequest[events.data.fd].find("\r\n\r\n") != std::string::npos)
	{
		parseHttpClient(_oneRequest[events.data.fd]);
		responseClient(events.data.fd, _oneRequest[events.data.fd]);
		_oneRequest.erase(events.data.fd);
		if (epoll_ctl(epollfd, EPOLL_CTL_DEL, ev.data.fd, &ev) == -1)
			throw std::runtime_error("error: epoll_ctl()");
		close(ev.data.fd);
		return ;
	}
}

ParserRequest::ParserRequest(){}

ParserRequest::~ParserRequest(){}
