/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseRequest.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:00:02 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/16 18:24:21 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Request.hpp"
#include <map>
#define BUFFER_SIZE 4012

struct ctrlFD{
	Request		*request;
	bool		parsedBody;
	int			lentgh;
	std::string	buffer;
};

class ParseRequest{
	private:
		void	isNewSocket(int fd);
		void	setBuffer(int fd);
		int		setBody(int fd);
		int		findBody(int fd);
		int		setRequestLine(int fd);
		int		setHeaders(int fd);
		int		parseRequest(int fd);
	
	protected:
		std::map<int, ctrlFD> _socket;

	public:
		int		setBufferSocketFd(int fd);
};