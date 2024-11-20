/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:15:58 by myokogaw          #+#    #+#             */
/*   Updated: 2024/11/11 23:39:17 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <cstdarg>
struct Conf;

namespace Logger {
	const std::string	cf_file_err(const char *pathname, const std::string &err);
	const std::string	cf_syntax_err(Conf &cf, const std::string &wrongToken,
	const std::string &err, int line);
	const std::string	log_error(Conf &cf, const char *fmt, ...);
}
