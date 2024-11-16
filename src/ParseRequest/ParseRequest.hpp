/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRequest.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:00:02 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/15 20:26:35 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Request.hpp"
#include <map>
#define BUFFER_SIZE 10


struct ctrlFD{
	Request		request;
	bool		haveBody;
	int			lentgh;
	std::string	buffer;
};

class ParseRequest{
	private:
		char	buffer[BUFFER_SIZE +1];
		int		bytesRead;
		std::map<int, ctrlFD> _socket;

		void	isNewSocket(int fd);
		int		setBody(int fd);
		int		setRequestLine(int fd);
		int		setHeaders(int fd);
		int		parseRequestLineHeaders(int fd);

	public:
		int		setBufferSocketFd(int fd);
};