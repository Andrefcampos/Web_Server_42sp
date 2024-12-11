/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPage.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:27:22 by myokogaw          #+#    #+#             */
/*   Updated: 2024/12/03 17:27:22 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <vector>
# include <string>

class ErrorPage {
	private:
		std::vector<std::string>	_codes;
		std::string					_uri;
	public:
		ErrorPage();
		~ErrorPage();

		void				appendCode(const std::string &code);
		void				setUri(const std::string &uri);
		bool				hasCode(const std::string &code) const;
		const std::string	&getUri(void) const;
		void				print(void) const;
};
