/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:06:43 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/06 12:43:28 by rbutzke          ###   ########.fr       */
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

#define	BUFFERSIZE 4024

class ParserRequest: public Headers, RequestLine{
	private:
		std::map<int, std::string>	_oneRequest;
		void	parseHttpClient(std::string protocolHtpp);

	protected:
		ParserRequest();
		~ParserRequest();
		std::map<std::string, std::map<std::string, std::string> > _httpRequest;

	public:
		virtual int	responseClient(int fd, std::string resp) = 0;
		void	readFdClient(epoll_event &events, epoll_event &ev,int &epollfd);

};