/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MultPart.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:10:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/17 17:43:15 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <list>
#include "ABody.hpp"
#include "DataBody.hpp"

using namespace std;

class MultPart : public ABody {
	private:
		string			_boundary;
		string			_endboundary;
		void			formatBuffer(string &buffer);
		void			setHeaders(string &headers);
		void			parseElement(string &buffer);
		void			addNewHeaders(string &headers);
		void			setContentBody(string &contentBody);

	protected:
		bool			_isMultPart;
		size_t			_lengthBody;
		string			getEndBoundary() const ;
		string			getBoundary() const ;

	public:
		void			parseBody(string &buffer);
		void			setBondary(string boundary);
		~MultPart(){};
		MultPart();
};