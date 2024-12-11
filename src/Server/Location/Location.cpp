/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 02:19:28 by myokogaw          #+#    #+#             */
/*   Updated: 2024/12/10 23:08:12 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"
#include "Directive.hpp"

using namespace std;

Location::Location() : _route("") {
    this->_directives["allow_methods"] = new AllowMethodsDirective();
    this->_directives["autoindex"] = new AutoIndexDirective();
    this->_directives["index"] = new IndexDirective();
    this->_directives["cgi"] = new CgiDirective();
}

Location::~Location() {
    for (map<string, Directive *>::iterator it = _directives.begin(); it != _directives.end(); ++it)
        delete it->second;
    _directives.clear();
}

void    Location::setDirective(Directive *directive) {
    this->_directives[directive->getName()] = directive;
}

Directive *Location::getDirective(const string &directive) {
    return (this->_directives[directive]);
}

const string &Location::getRoute(void) const {
    return (this->_route);
}

void        Location::setRoute(const string &route) {
    this->_route = route;
}

void    Location::print(void) const {
    for (map<string, Directive *>::const_iterator it = _directives.begin(); it != _directives.end(); ++it) {
        it->second->print();
    }
}