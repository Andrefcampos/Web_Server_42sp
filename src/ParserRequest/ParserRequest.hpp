/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParserRequest.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:06:43 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/15 12:31:42 by rbutzke          ###   ########.fr       */
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
#define DELIMITER "\r\n\r\n"
#define LIMIT_SIZE 4
#define	BUFFERSIZE 4012


struct	dataSocketFD{
	std::string		buffer;
	std::string		boundaryBegin;
	std::string		boundaryEnd;
	std::string		body;
	bool			haveBody;
	std::size_t		lentgh;
};

class ParserRequest: public Headers, RequestLine{
	private:
		std::map<int, dataSocketFD>	_dataSocket;
		int		parseHttpClient(dataSocketFD &buffer, int fd);
		void	ctrlNewRequests(int fd);
		int		setBody(int fd);
		int		requestLineHeader(int fd);
		int		haveBody(dataSocketFD &buffer, int fd);
		int		setMapRequest(std::string &buffer, int fd);
		void	parseBody(int fd, dataSocketFD &data);
		void	parse(std::string content);
		void	setBoundary(dataSocketFD &data, int fd);

	protected:
		ParserRequest();
		~ParserRequest();
		httpRequest _httpRequest;

	public:
		virtual int	responseClient(int fd) = 0;
		int			setBufferSocketFd(int fd);

};