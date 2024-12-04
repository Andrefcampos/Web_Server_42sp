/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Chunked.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:32:53 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/19 09:05:00 by rbutzke          ###   ########.fr       */
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
		void	removeDelimiter(string &buffer);
		string	popChunke(string &buffer, size_t length);
		size_t	popNbrBytes(string &buffer);

	public:
		Chunked();
		~Chunked(){};
		void	parseBody(string &buffer);
};
