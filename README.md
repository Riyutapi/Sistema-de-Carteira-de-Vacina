# Sistema de Carteira de Vacina
Projeto para concluir a matéria de Algorítmos 1, realizada na UTFPR no campus Cornélio Procópio em 2022

É um projeto de sistema de carteiras de vacinação da covid-19, sendo possível adicionar até 100 pacientes com eles tendo no máximo 5 vacinas cada
(sendo possível alterar esses valores caso necessário), alguns "pacientes" já estão cadastrados para realizar testes de funcionalidades

Possui 6 opções:

[1] Cadastrar paciente: verificando se as informações fornecidas como nome, telefone, data de nascimento, marca da vacina e data de aplicação da vacina estão corretas

[2] Buscar paciente: verificando se o paciente está no banco de dados e fornece todas as informações, e questiona se deseja adicionar uma nova vacina
(caso essa adição ultrapasse o máximo de vacinas que o sistema armazena (5), o código ira deixar salvo as 5 vacinas adicionadas mais recentemente)

[3] Listar todos os pacientes: fornece alguns dados de todos os pacientes

[4] Quantidade de Doses Aplicadas de Cada Fabricante: Contando cada dose de cada paciente

[5] Quantidade de Pacientes que Tomaram Cada uma das Doses: fornecendo juntamente com a porcentagem

[0] Sair: para finalizar o programa
