/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:07:34 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/17 14:57:30 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <string>
# include <sstream>
# include <fstream>
# include <exception>
# include <map>
# include <vector>
# include <sys/socket.h>

# define CRLF "\r\n"
# define LF "\n"
# define SP " "

// RFC 9112 6.1
// A server that receives a request message with a transfer coding it does not understand SHOULD respond with 501 (Not Implemented).

// A server MAY reject a request that contains a message body but not a Content-Length by responding with 411 (Length Required).

// A server that does not support persistent connections MUST send the "close" connection option
// in every response message that does not have a 1xx (Informational) status code.

class Request;
class Location;
class LocationDirective;
class ErrorPageDirective;

struct FieldLine {
	std::string field_name;
	std::string field_value;
	FieldLine(const std::string &field_name, const std::string &field_value);
	const std::string getFieldLine(void) const;
};

struct MimeTypes {
	std::map<std::string, std::string> mime_types;
	MimeTypes();
	const std::string getMimeType(const std::string &extension);
};

class Response {
	// attributes
	private:
		LocationDirective			*_location;
		ErrorPageDirective			*_error_page;
		const std::string			_http_version;
		Location					*_cur_loc;
		std::string					_code;
		std::string					_reason_phrase;
		std::vector<FieldLine *>	_header_fields;
		std::string					_body;
		size_t						_msg_size;

	// private methods
	private:
		void				validationResponse(Request *request);
		void				setStatusLine(const int code);
		void				getError(void);
		const std::string	getStatusLine(void) const;
		std::string			resolveURI(const std::string &uri);
		void				getBody(const std::string &uri);

	// public methods
	public:
		Response(Request *request, LocationDirective *location, ErrorPageDirective *error_page);
		~Response();

		const std::string	getResponseMsg(void);
		size_t				getMsgSize(void) const;
};
