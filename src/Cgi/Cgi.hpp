/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefil <andrefil@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:15:12 by andrefil          #+#    #+#             */
/*   Updated: 2024/11/23 17:18:17 by andrefil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <map>

class	Cgi {
	private:
		std::string _path;
		std::map<std::string, std::string> _extensions;
	
		Cgi(void);
		Cgi(Cgi const &obj);
		Cgi &operator=(Cgi const &obj);

	public:
		Cgi(std::string const &Path, std::map<std::string, std::string> const &Extensions);
		~Cgi(void);

		const std::string &getPath(void) const;
		const std::string &getExtensions(void) const;

		void	executeCgi(void);
};
