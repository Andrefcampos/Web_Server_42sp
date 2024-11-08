/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:06:43 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/07 14:27:02 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <list>
#include <cstring>
#include <sys/epoll.h>
#include "RequestLine.hpp"
#include "Headers.hpp"
#include "include.hpp"
#define	BUFFERSIZE 5

struct	bufferFD{
	std::string		buffer;
	std::string		body;
	bool			haveBody;
	unsigned long	lentgh;
};

class ParserRequest: public Headers, RequestLine{
	private:
		std::map<int, bufferFD>	_oneRequest;
		int	parseHttpClient(bufferFD buffer);

	protected:
		ParserRequest();
		~ParserRequest();
		httpRequest _httpRequest;

	public:
		virtual int	responseClient(int fd) = 0;
		int			readFdClient(epoll_event &events);

};