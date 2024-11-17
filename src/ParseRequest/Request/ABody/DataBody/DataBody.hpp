/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DataBody.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:37:19 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/17 17:08:20 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <list>
using namespace std;

class DataBody{
	private:
		map<string, list<string> >	_headers;
		string						_content;

	protected:
		DataBody();
		~DataBody();
		void	setNewHeaders(string &key, string &value);
		void	setContent(string &value);
		list<string>				getHeaders(string key) const;
		map<string, list<string> >	getAllHeaders() const;
		string						getContent() const;
};