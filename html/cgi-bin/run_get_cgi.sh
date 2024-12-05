#!/bin/bash

# Configura as variáveis de ambiente do CGI
export REQUEST_METHOD="GET"                # Método HTTP usado
export QUERY_STRING="name=42&lang=Python"  # Query string (se GET)
export CONTENT_TYPE="application/x-www-form-urlencoded"
export CONTENT_LENGTH=""                   # Não usado para GET
export SCRIPT_NAME="/cgi-bin/file.py"
export SERVER_NAME="localhost"
export SERVER_PORT="8080"
export SERVER_PROTOCOL="HTTP/1.1"

# Caminho para o script Python
SCRIPT_PATH="./file.py"

# Executa o script CGI
echo "Executando CGI Script..."
$SCRIPT_PATH
