/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AHeaders.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:05:48 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/13 12:27:08 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <map>
#include <list>
#include "Client.hpp"

// Headers Keys
#define TENCODING "Transfer-Encoding"
#define CLENGTH "Content-Length"
#define CTYPE "Content-Type"
#define HOST "Host"

// Headers value
#define MPART "multipart"
#define CHUNKED "chunked"

using namespace std;

class AHeaders{
	private:
		void	setLastHeader(string &headers);
		void	setHeaders(string &line);
		void	addNewElement(string key, string value);
		int		validContentLength(Client *client);
		int		validAmbiguityHeaders();
		int		validTransferEnconding();
		int		validHost();

	protected:
		map<string, list<string> >	_header;
		virtual int		setHeader(string &buffer, Client *client) = 0;
		virtual 		~AHeaders(){};
		int				parseHeaders(string	&headers, Client *client);
		int				validHeaders(Client *client);

	public:
		string						getHost() const;
		list<string>				getHeader(string key) const;
		map<string, list<string> >	getAllHeader() const;
	
};
