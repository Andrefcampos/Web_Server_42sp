/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Body.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:32:30 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/15 13:25:45 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <string>
#include <ostream>

class Body{
	private:
		std::string	_body;
	
	public:
		void			setBody(std::string body);
		std::string		getBody() const;
};

std::ostream &operator<<(std::ostream &os, const Body &body);