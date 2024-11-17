/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABody.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:11:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/17 13:27:34 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <list>

using namespace std;

struct DataBody{
	map<string, list<string> > header;
	string	buffer;	
};

class ABody{
	private:
		string	_boundary;
		string	_endboundary;
		void	setContentDisposition(string &buffer, DataBody &data);
		void	setHeaders(string &headers, DataBody &data);
		void	setContentBody(string &contentBody,DataBody &data);
		void	parseElement(string &buffer, DataBody &data);
		void	addNewHeaders(DataBody &data, string &headers);
		void	formatBuffer(string &buffer);

	protected:
		bool			_haveBody;
		bool			_haveBoundary;
		bool			_is_chunked;
		bool			_parsedBody;
		size_t			_lengthBody;
		list<DataBody>	_DataBody;

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