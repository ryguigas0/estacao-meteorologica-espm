# Estacao Metereologica - ESPM

Repositório com o código da estação metereológica

## Setup

1. Crie o arquivo `.env` contendo:
   - `ADMIN_KEY`: valor da chave de autorização de utilização de endpoints
   - `DB_NAME`: nome do banco de dados que vai ficar na pasta `.data`
   - `PORT`: porta de acesso do servidor, por padrão é 3000
2. Rode `npm i`
3. Faça uma requisição `GET` para o endereço `localhost:PORT/`

## Baixando o banco de dados

1. Fazer download do projeto no glitch
2. Extrair o arquivo `.tgz` na pasta
3. Baixar um [navegador de banco de dados sqlite](https://sqlitebrowser.org/dl/)
4. Usar o navegador de banco de dados sqlite para explorar o arquivo `estacao.db`
