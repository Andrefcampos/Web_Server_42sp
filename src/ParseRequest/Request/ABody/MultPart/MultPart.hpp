/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MultPart.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:10:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/18 09:59:15 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <list>
#include "ABody.hpp"

using namespace std;

class MultPart : public ABody {
	private:
		string			_boundary;
		string			_endboundary;
		void			parseElement(string &buffer, DataBody &data);
		void			setHeaders(string &headers, DataBody &data);
		void			addNewHeaders(string &headers, DataBody &data);
		void			setContentBody(string &contentBody, DataBody &data);
		void			formatBuffer(string &buffer);

	public:
		string			getEndBoundary() const ;
		string			getBoundary() const ;
		void			parseBody(string &buffer);
		void			setBondary(string boundary);
		~MultPart(){};
		MultPart();
};