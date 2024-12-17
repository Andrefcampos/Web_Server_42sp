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
# include "LocationAdapter.hpp"
# include "Directive.hpp"

class Directive;

class Location : public LocationAdapter {
	private:
		std::string	_route;
	public:
		Location();
		~Location();

		const std::string	&getRoute(void) const;
		void				setRoute(const std::string &route);
		void				setDirective(Directive *directive);
		Directive			*getDirective(const std::string &directive);
		void				print(void) const;
};
