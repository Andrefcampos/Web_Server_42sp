/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefil <andrefil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:15:12 by andrefil          #+#    #+#             */
/*   Updated: 2024/11/26 09:36:05 by andrefil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <map>

class	Cgi {
	private:
		std::string _scriptpath;
		std::map<std::string, std::string> _envp;
		std::string _request;
	
		Cgi(void);
		Cgi(Cgi const &obj);
		Cgi &operator=(Cgi const &obj);

	public:
		Cgi(std::string const &ScriptPath, std::map<std::string, std::string> const &Envp, std::string const &Body);
		~Cgi(void);

		const std::string &getPath(void) const;
		const std::string &getExtensions(void) const;

		std::string	executeCgi(void);
};
