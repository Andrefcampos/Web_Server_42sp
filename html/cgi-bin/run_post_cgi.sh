#!/bin/bash

#Export EnvVars
export REQUEST_METHOD="POST"
export QUERY_STRING=""
export CONTENT_TYPE="application/x-www-form-urlencoded"
export CONTENT_LENGTH="13"  # Tamanho dos dados no corpo
export SCRIPT_NAME="/cgi-bin/file.py"
export SERVER_NAME="localhost"
export SERVER_PORT="8080"
export SERVER_PROTOCOL="HTTP/1.1"

#Post Body
POST_DATA="name=42&lang=Python"

#Script file .py
SCRIPT_PATH="./file.py"

#Execute and send data to file.py
echo -e "$POST_DATA" | $SCRIPT_PATH
