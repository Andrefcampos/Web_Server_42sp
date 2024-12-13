/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DirectiveAdapter.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutzke <rbutzke@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:11:23 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/13 16:57:24 by rbutzke          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <string>
#include <map>

class Directive;

class DirectiveAdapter{
	protected:
		std::map<std::string, Directive *>	_directives;

	public:
		std::string		getHost() const;
		std::string		getIP() const;
		std::string		getPort() const;
		std::string		getServerName(void) const;
		long long int	getSizeMax(void) const;
};

