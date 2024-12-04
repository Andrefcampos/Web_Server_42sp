/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ABody.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:11:28 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/19 09:06:04 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <list>
#include "DataBody.hpp"

using namespace std;

class ABody{
	protected:
		size_t			_lengthBody;
		list<DataBody>	_data;
		void			setDataBody(DataBody &data);

	public:
		list<DataBody>	getDataBody();
		size_t			getLengthBody();
		void			setLengthBody(size_t length);
		
		virtual ~ABody(){};		
		virtual void	parseBody(string &buffer) = 0;

};