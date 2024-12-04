/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleBody.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:46:24 by rbutzke           #+#    #+#             */
/*   Updated: 2024/11/18 09:49:51 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <list>
#include "ABody.hpp"

using namespace std;

class SimpleBody : public ABody{
	private:

	public:
		void	parseBody(string &buffer);
};