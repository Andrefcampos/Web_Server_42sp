/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRequest.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:00:02 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/10 19:21:06 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Request.hpp"
#include <map>
#include "defines.hpp"
#include <ctime>

struct ctrlFD{
	Request		*request;
	bool		parsedBody;
	int			lentgh;
	std::string	buffer;
	std::time_t	 startTime;
};

class ParseRequest{
	private:
		void	isNewClient(int fd);
		void	setBuffer(int fd);
		int		setRequestLine(int fd);
		int		setHeaders(int fd);
		int		parseRequest(int fd);
		int		timeOutRequest(std::time_t timeStart);
	
	protected:
		std::map<int, ctrlFD> _socket;

	public:
		Request *setBufferSocketFd(int fd);
		void	removeFD(int fd);
};