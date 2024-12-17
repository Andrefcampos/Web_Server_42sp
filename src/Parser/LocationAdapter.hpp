/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationAdapter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 23:56:26 by myokogaw          #+#    #+#             */
/*   Updated: 2024/12/15 23:56:26 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <map>
# include <string>

class Directive;
class AllowMethodsDirective;
class RedirectDirective;
class RootDirective;
class AutoIndexDirective;
class IndexDirective;
class CgiDirective;
class UploadDirDirective;

class LocationAdapter {
	protected:
		std::map<std::string, Directive *>	_directives;

	public:
		AllowMethodsDirective		*getAllowMethods(void);
		RedirectDirective			*getRedirect(void);
		RootDirective				*getRoot(void);
		AutoIndexDirective			*getAutoIndex(void);
		IndexDirective				*getIndex(void);
		CgiDirective				*getCgi(void);
		UploadDirDirective			*getUploadDir(void);
};
