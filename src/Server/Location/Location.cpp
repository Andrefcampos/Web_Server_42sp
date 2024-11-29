/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:19:28 by myokogaw          #+#    #+#             */
/*   Updated: 2024/11/29 02:24:01 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"
#include "Directive.hpp"

Location::Location() : _route("") {
    this->_directives["allow_methods"] = new AllowMethodsDirective();
}

Location::~Location() {
    for (std::map<std::string, Directive *>::iterator it = _directives.begin(); it != _directives.end(); ++it)
        delete it->second;
    _directives.clear();
}

