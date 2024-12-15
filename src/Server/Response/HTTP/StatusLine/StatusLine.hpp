/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusLine.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:32:30 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/15 14:30:10 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <map>
#include <string>
#include <ostream>

class StatusLine{
	private:
		std::string	_version;
		std::string	_statusCode;
		std::string	_statusMessage;

	public:
		StatusLine();
		void		setStatusCode(int statusCode);
		void		setStatusCode(std::string statusCode);
		void		setStatusMensage(std::string statusMessage);	
		std::string	getResponseStatusLine() const;		
};

std::ostream &operator<<(std::ostream &os, const StatusLine &statusLine);