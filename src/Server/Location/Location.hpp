/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:15:36 by myokogaw          #+#    #+#             */
/*   Updated: 2024/11/11 22:15:36 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <map>
# include <string>
# include "Directive.hpp"

class Location {
	private:
		std::string _route;
		std::map<std::string, Directive *> _directives;
	public:
		Location();
		~Location();

		friend class AllowMethodsHandler;
		friend class RedirectHandler;
		friend class RootHandler;
		friend class AutoIndexHandler;
		friend class IndexHandler;
		friend class CgiHandler;
		friend class UploadDirHandler;
};
