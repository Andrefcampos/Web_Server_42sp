/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABody.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:11:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/17 17:46:23 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <list>
#include "DataBody.hpp"

using namespace std;

class ABody{
	private:
		string	_boundary;
		string	_endboundary;

		map<string, list<string> >	_headers;
		string						_content;

		void	setContentDisposition(string &buffer);
		void	setHeaders(string &headers);
		void	setContentBody(string &contentBody);
		void	parseElement(string &buffer);
		void	addNewHeaders(string &headers);
		void	formatBuffer(string &buffer);

	protected:
		void	setNewHeaders(string &key, string &value);
		void	setContent(string &value);
		list<string>				getHeaders(string key) const;
		map<string, list<string> >	getAllHeaders() const;
		string						getContent() const;


	protected:
		bool			_haveBody;
		bool			_haveBoundary;
		bool			_is_chunked;
		bool			_parsedBody;
		size_t			_lengthBody;

		void			parseBody(string &buffer);
		void			addNewElement(string key, string value);
		void			setBondary(string boundary);
		string			getEndBoundary() const ;
		string			getBoundary() const ;
		virtual void	haveBody() = 0;
		virtual void	setBody(std::string &buffer) = 0;
		virtual 		~ABody(){};
		ABody();

	public:

};