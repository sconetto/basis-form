# Sistema de Auxílio a inclusão de novos usuários - BASIS

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/sconetto/basis-form/master/LICENSE)

- Um sistema que visa auxiliar o processo de criação de novos usuários.
	- O sistema usa de alguns atributos do usuário para gerar scripts para inclusão do usuário em sistemas necessários.
	- Os scripts gerados são para bancos de dados SQL Server 2012 R2
	- Os scripts gerados são para adição de usuários (dsadd) em domínios Windows
	

## Dependências
- gcc-4.9-base
	- E todas suas subdependências.
- make
	- E todas suas subdependências.

## Execução
```bash
make clean
make
make run
```
