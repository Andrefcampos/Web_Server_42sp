/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationAdapter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 23:57:21 by myokogaw          #+#    #+#             */
/*   Updated: 2024/12/15 23:57:21 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LocationAdapter.hpp"
#include "Directive.hpp"

AllowMethodsDirective		*LocationAdapter::getAllowMethods(void) {
    return (dynamic_cast<AllowMethodsDirective *>(_directives["allow_methods"]));
}

RedirectDirective			*LocationAdapter::getRedirect(void) {
    return (dynamic_cast<RedirectDirective *>(_directives["redirect"]));
}

RootDirective				*LocationAdapter::getRoot(void) {
    return (dynamic_cast<RootDirective *>(_directives["root"]));
}

AutoIndexDirective			*LocationAdapter::getAutoIndex(void) {
    return (dynamic_cast<AutoIndexDirective *>(_directives["auto_index"]));
}

IndexDirective				*LocationAdapter::getIndex(void) {
    return (dynamic_cast<IndexDirective *>(_directives["index"]));
}

CgiDirective				*LocationAdapter::getCgi(void) {
    return (dynamic_cast<CgiDirective *>(_directives["cgi"]));
}

UploadDirDirective			*LocationAdapter::getUploadDir(void) {
    return (dynamic_cast<UploadDirDirective *>(_directives["upload_dir"]));
}

