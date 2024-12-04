/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:06:43 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/04 16:34:32 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <cstring>
#include <sys/epoll.h>

#define	BUFFERSIZE 4096

class ParserRequest {
	protected:
		std::map<int, std::map<std::string, std::string> >	_clientes;			
		std::map<std::string, std::string>					_request;
		std::map<int, std::string>							_oneRequest;
		void	readFdClient(epoll_event &events, epoll_event &ev,int &epollfd);

	public:
		ParserRequest();
		virtual int	responseClient(int fd, std::string resp) = 0;
		std::map<std::string, std::string>	parseHttpClient(std::string protocolHtpp);
		~ParserRequest();

};