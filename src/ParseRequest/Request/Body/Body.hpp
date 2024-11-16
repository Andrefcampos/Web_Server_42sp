/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:11:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/15 18:27:17 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <list>

using namespace std;

class Body{
	protected:
		map<string, list<string> >	_body;
	
	public:
		void			addNewElement(string key, string value);
		list<string>	getHeader(string key);
};