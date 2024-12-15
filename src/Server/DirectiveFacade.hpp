/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectiveFacade.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:11:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/14 13:39:47 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <string>
#include <map>

class Directive;

class DirectiveFacade{
	protected:
		std::map<std::string, Directive *>	_directives;

	public:
		std::string		getHost() const;
		std::string		getIP() const;
		std::string		getPort() const;
		std::string		getServerName(void) const;
		long long int	getSizeMax(void) const;
};

