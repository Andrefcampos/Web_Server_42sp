/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:06:43 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/06 15:55:50 by rbutzke          ###   ########.fr       */
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

#define	BUFFERSIZE 4024

class ParserRequest: public Headers, RequestLine{
	private:
		std::map<int, std::string>	_oneRequest;
		void	parseHttpClient(std::string protocolHtpp);

	protected:
		ParserRequest();
		~ParserRequest();
		httpRequest _httpRequest;

	public:
		virtual int	responseClient(int fd) = 0;
		void	readFdClient(epoll_event &events, epoll_event &ev,int &epollfd);

};