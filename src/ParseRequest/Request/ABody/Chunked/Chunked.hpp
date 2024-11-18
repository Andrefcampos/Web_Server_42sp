/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunked.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:32:53 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/18 17:30:56 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <list>
#include "ABody.hpp"

using namespace std;

class Chunked : public ABody{
	private:
		size_t	_bytes;
		void	getLineAndRemove(string &buffer, size_t length, DataBody &data);

	public:
		Chunked();
		~Chunked(){};
		void	parseBody(string &buffer);
};
