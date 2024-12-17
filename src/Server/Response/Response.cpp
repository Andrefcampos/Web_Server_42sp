/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myokogaw <myokogaw@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:09:58 by rbutzke           #+#    #+#             */
/*   Updated: 2024/12/17 14:59:04 by myokogaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdexcept>
#include <string>
#include "Response.hpp"
#include "Request.hpp"
#include "Directive.hpp"
#include "Location.hpp"

using namespace std;

static MimeTypes mime_types;

MimeTypes::MimeTypes() {
    this->mime_types["html"] = "text/html";
    this->mime_types["css"] = "text/css";
    this->mime_types["js"] = "text/javascript";
    this->mime_types["jpeg"] = "image/jpeg";
    this->mime_types["png"] = "image/png";
    this->mime_types["json"] = "application/json";
}

const string MimeTypes::getMimeType(const string &filename) {
	string extension = filename.substr(filename.rfind('.') + 1, filename.length());
	string content_type_value = this->mime_types[extension];

	if (filename.compare("/") == 0)
		return ("text/html; charset=utf-8");
	if (content_type_value.empty() == true)
		return ("application/octet-stream; charset=utf-8");
	return (content_type_value + "; charset=utf-8"); 
}

FieldLine::FieldLine(const string &field_name, const string &field_value) : field_name(field_name), field_value(field_value) {}

const string FieldLine::getFieldLine(void) const {
	return ((this->field_name + ":" + SP + this->field_value));
}

Response::Response(Request *request, LocationDirective *location, ErrorPageDirective *error_page) :
_location(location), _error_page(error_page), _http_version("HTTP/1.1") {
	try {
		validationResponse(request);
		getBody(request->getPath());	
		_header_fields.push_back(new FieldLine("Connection", "close"));
		_header_fields.push_back(new FieldLine("Server", "MeuServidor/1.0 (Linux)"));
	} catch (const exception &e) {
		getError();
	}
}

Response::~Response() {
	for (vector<FieldLine *>::iterator it = _header_fields.begin(); it != _header_fields.end(); ++it)
		delete *it;
	_header_fields.clear();
}

void	Response::validationResponse(Request *request) {
	this->_cur_loc = _location->resolveLocation(request->getPath());
	AllowMethodsDirective *allow_methods = this->_cur_loc->getAllowMethods();

	if (allow_methods->isAllowed(request->getMethod()) == false)
		setStatusLine(405);
}

void	Response::setStatusLine(const int code) {
	switch (code) {
		case 100:
			_code = "100";
			_reason_phrase = "Continue";
			break ;
		case 101:
			_code = "101";
			_reason_phrase = "Switching Protocols";
			break ;
		case 200:
			_code = "200";
			_reason_phrase = "Ok";
			break ;
		case 201:
			_code = "201";
			_reason_phrase = "Created";
			break ;
		case 202:
			_code = "202";
			_reason_phrase = "Accepted";
			break ;
		case 203:
			_code = "203";
			_reason_phrase = "Non-Authoritative Information";
			break ;
		case 204:
			_code = "204";
			_reason_phrase = "No Content";
			break ;
		case 205:
			_code = "205";
			_reason_phrase = "Reset Content";
			break ;
		case 300:
			_code = "300";
			_reason_phrase = "Multiple Choices";
			break ;
		case 301:
			_code = "301";
			_reason_phrase = "Moved Permanently";
			break ;
		case 302:
			_code = "302";
			_reason_phrase = "Found";
			break ;
		case 303:
			_code = "303";
			_reason_phrase = "See Other";
			break ;
		case 305:
			_code = "305";
			_reason_phrase = "Use Proxy";
			break ;
		case 307:
			_code = "307";
			_reason_phrase = "Temporary Redirect";
			break ;
		case 400:
			_code = "400";
			_reason_phrase = "Bad Request";
			throw (exception());
		case 403:
			_code = "403";
			_reason_phrase = "Forbidden";
			throw (exception());
		case 404:
			_code = "404";
			_reason_phrase = "Not Found";
			throw (exception());
		case 405:
			_code = "405";
			_reason_phrase = "Method Not Allowed";
			throw (exception());
		case 406:
			_code = "406";
			_reason_phrase = "Not Acceptable";
			throw (exception());
		case 408:
			_code = "408";
			_reason_phrase = "Request Timeout";
			throw (exception());
		case 409:
			_code = "409";
			_reason_phrase = "Conflict";
			throw (exception());
		case 410:
			_code = "410";
			_reason_phrase = "Gone";
			throw (exception());
		case 411:
			_code = "411";
			_reason_phrase = "Length Required";
			throw (exception());
		case 413:
			_code = "413";
			_reason_phrase = "Payload To Large";
			throw (exception());
		case 414:
			_code = "414";
			_reason_phrase = "URI Too Long";
			throw (exception());
		case 415:
			_code = "415";
			_reason_phrase = "Unsupported Media Type";
			throw (exception());
		case 417:
			_code = "417";
			_reason_phrase = "Expectation Failed";
			throw (exception());
		case 500:
			_code = "500";
			_reason_phrase = "Internal Server Error";
			throw (exception());
		case 501:
			_code = "501";
			_reason_phrase = "Not Implemented";
			throw (exception());
		case 502:
			_code = "502";
			_reason_phrase = "Bad Gateway";
			throw (exception());
		case 503:
			_code = "503";
			_reason_phrase = "Service Unavailable";
			throw (exception());
		case 504:
			_code = "504";
			_reason_phrase = "Gateway Timeout";
			throw (exception());
		case 505:
			_code = "505";
			_reason_phrase = "HTTP Version Not Supported";
			throw (exception());
	}
}

const string Response::getStatusLine(void) const {
	return (this->_http_version + SP + this->_code + SP + this->_reason_phrase);
}

string	Response::resolveURI(const string &uri) {
	Location *location = _location->resolveLocation(uri);
	RootDirective *root;
	IndexDirective *index;

	if (location == NULL)
		setStatusLine(404);
	index = location->getIndex();
	root = location->getRoot();
	if (*uri.rbegin() == '/') {
		if (index != NULL)
			return (index->getIndex());
		setStatusLine(404);
	}
	if (root != NULL)
		return (root->getRoot() + uri);
	return (uri);
} 

void	Response::getBody(const string &uri) {
	string			resolved_uri(resolveURI(uri));
	string			ext;
	ifstream		file;
	stringstream	content_length;

	file.open(resolved_uri.c_str());
	if (file.is_open() == false)
		setStatusLine(404);
	getline(file, _body, '\0');
	content_length << _body.length();
	_header_fields.push_back(new FieldLine("Content-Type", mime_types.getMimeType(resolved_uri)));
	_header_fields.push_back(new FieldLine("Content-Length", content_length.str()));
}

size_t	Response::getMsgSize(void) const {
	return (this->_msg_size);
}

const string Response::getResponseMsg(void) {
	string response_msg(getStatusLine() + CRLF);

	for (vector<FieldLine *>::const_iterator it = _header_fields.begin(); it != _header_fields.end(); ++it)
		response_msg += ((*it)->getFieldLine() + CRLF);
	response_msg += CRLF;
	response_msg += _body;
	this->_msg_size = response_msg.length();
	return (response_msg);
}

void	Response::getError(void) {
	string error_page_uri = _error_page->getErrorPageURI(_code);
	ifstream file(error_page_uri.c_str());
	stringstream content_length;

	_header_fields.push_back(new FieldLine("Connection", "close"));
	_header_fields.push_back(new FieldLine("Server", "MeuServidor/1.0 (Linux)"));
	if (file.is_open() == false)
		return ;
	getline(file, _body, '\0');
	content_length << _body.length();
	_header_fields.push_back(new FieldLine("Content-Type", mime_types.getMimeType(error_page_uri)));
	_header_fields.push_back(new FieldLine("Content-Length", content_length.str()));
}