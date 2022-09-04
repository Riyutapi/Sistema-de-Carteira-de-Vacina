/*******************************************************************************

Trabalho Final - Programação em C
Grupo: 7
Integrantes: Marcia Eliana Ferreira / Ricardo Yudi Takahashi Pimentel
Turma: EC31C-C11
Data Início: 14/06/2022
Data Final: 26/06/2022

********************************************************************************

Diário:
14/06/2022: foi adicionado os include que provavelmente será utilizados no
programa e os sctruct com typedef, dos dados da carteira de vacinação.
15/06/2022: testes
16/06/2022: criação das funções de validação do nome, do telefone e da
data de nascimento
17/06/2022: início da função principal e criação da função de cadastrar paciente
18/06/2022: armazenamento dos 15 pacientes já cadastrados
19/06/2022: função de procurar o nome do paciente e fornecer seus dados
20/06/2022: ajustes
21/06/2022: funções de listar os pacientes em ordem alfabética, quantidade de
doses aplicadas de cada fabricante, ajustes e criação de funções "extras"
(validação de data da vacina e validar fabricante)
22/06/2022: ajustes e função da quantidade de pacientes que tomaram cada uma das
doses
23/06/2022: otimização

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#define TAM 100 //Tamanho (quantidade de pacientes)
#define AA 2022 //Ano Atual

//Registro com redefinição da data de nascimento
typedef struct data_nascimento {
    int dia;
    int mes;
    int ano;
} DataNasc;

//Registro com redefinição da data da aplicação da vacina
typedef struct data_aplicacao {
    int dia;
    int mes;
    int ano;
} DataApli;

//Registro com redefinição dos dados da vacina aplicada
typedef struct vacina {
    char fabricante[20];
    char lote[12];
    DataApli dataApli;
} Vacina;

//Registro com redefinição da carteira de vacinação
typedef struct carteira_vacinacao {
    char nome[80];
    char telefone[20];
    DataNasc dataNasc;
    Vacina vacina[5];
} CartVaci;

//Função para validar o nome, retorna 1 quando for válido e retorna 0 quando for inválido
int validacao_nome(char str[]) {
    int i, cont=0;
    
    //Verificar se sequência de caracteres é maior que 2 caracteres; seguido de um ESPAÇO
    for(i=0; i<strlen(str); i++) {
        if(str[i] != ' ') {
            cont++;
        } else {
            if(cont<=2){
            return 0;
            }
            cont=0;
        }
    }
    
    //Verificar se sequência de caracteres do último nome é maior que 2 caracteres
    if(cont<=2){
        return 0;
    }
    
    return 1;
}

//Função para validar o telefone, retorna 1 quando for válido e retorna 0 quando for inválido
int validacao_telefone(char str[]) {
    int i;
    
    //Verificar se o primeiro caracter digitado não é zero e se o tamanho do telefone está entre 11 e 12
    if ((str[0]!='0') || (strlen(str)<11) || (strlen(str)>12)){
        return 0;
    }
    
    //Verificar se todos os caracteres digitados são números
    for(i=0; i<strlen(str); i++) {
        if(str[i]!='0' && str[i]!='1' && str[i]!='2' && str[i]!='3' && str[i]!='4'
        && str[i]!='5' && str[i]!='6' && str[i]!='7' && str[i]!='8' && str[i]!='9') {
            return 0;
        }
    }
    
    return 1;
}

//Função para validação de data, retorna 1 quando a data valida e retorna 0 quando invalida 
int validacao_data(DataNasc dt) {
    if(dt.dia >= 1 && dt.dia <= 30) {
        if(dt.mes >= 1 && dt.mes <= 12) {
            if(dt.ano >= 1900 && dt.ano <= AA) {
                return 1;
            }
        }
    }
    return 0;
}

//Função para validação de data da vacina, retorna 1 quando a data valida e retorna 0 quando invalida 
int validar_aplicacao(DataApli dt) {
    if(dt.dia >= 1 && dt.dia <= 31) {
        if(dt.mes >= 1 && dt.mes <= 12) {
            if(dt.ano >= 2020 && dt.ano <= AA) {
                return 1;
            }
        }
    }
    return 0;
}

//Função para validar fabricante, retorna um número que determinará o nome correto
int validar_fabricante(char str[]) {
    if ((strcmp(str, "pfizer")==0) || (strcmp(str, "Pfizer")==0) || (strcmp(str, "PFIZER")==0)){
        return 1;
    } else {
        if ((strcmp(str, "janssen")==0) || (strcmp(str, "Janssen")==0) || (strcmp(str, "JANSSEN")==0)){
            return 2;
        } else {
            if ((strcmp(str, "astrazeneca")==0) || (strcmp(str, "Astrazeneca")==0) || (strcmp(str, "ASTRAZENECA")==0)){
                return 3;
            } else {
                if ((strcmp(str, "moderna")==0) || (strcmp(str, "Moderna")==0) || (strcmp(str, "MODERNA")==0)){
                    return 4;
                } else {
                    if ((strcmp(str, "sinopharm")==0) || (strcmp(str, "Sinopharm")==0) || (strcmp(str, "SINOPHARM")==0)){
                        return 5;
                    } else {
                        if ((strcmp(str, "outra")==0) || (strcmp(str, "Outra")==0) || (strcmp(str, "OUTRA")==0)
                        || (strcmp(str, "outro")==0) || (strcmp(str, "Outro")==0) || (strcmp(str, "OUTRO")==0)){
                            return 6;
                        } else {
                            return 7;
                        }
                    }
                }
            }
        }
    }
}

//Função limpar cache vacinas
CartVaci limpar_cache_vacina(CartVaci aux, int v) {
    for (v; v<5; v++){
        strcpy(aux.vacina[v].fabricante, " ");
        strcpy(aux.vacina[v].lote, " ");
        aux.vacina[v].dataApli.dia=00;
        aux.vacina[v].dataApli.mes=00;
        aux.vacina[v].dataApli.ano=0000;
    }
    return aux;
}

//Função para cadastrar vacina
CartVaci cadastrar_vacina(CartVaci aux) {
    int retornoData=0, retornoFab=0, quantVaci=0, v, armazena, vacinas=0;
    
    //Contar quantas vacinas o paciente já tem
    for (v=0; v<5; v++){
        if ((aux.vacina[v].dataApli.ano>=2020) && (aux.vacina[v].dataApli.ano<=AA)){
            vacinas=v+1;
        }
    }
    
    //Garantir que o usuário irá digitar no máximo 5 vacinas
    do{
        printf("Digite quantas vacinas foram aplicadas (se for mais que 5, digite 5 e informe as mais recentes): ");
        scanf(" %d", &quantVaci);
        getchar();
    } while (quantVaci>5 || quantVaci<0);
    
    //Caso o paciente tenha ou irá receber mais de 5 doses, irá deletar as mais antigas
    if ((quantVaci+vacinas)>5){
        do {
            for (v=1; v<5; v++){
                aux.vacina[v-1]=aux.vacina[v];
            }
            
            vacinas--;
            
        } while ((quantVaci+vacinas)>5);
    }
    
    aux=limpar_cache_vacina(aux,(quantVaci+vacinas));
    
    for (v=vacinas; v<quantVaci+vacinas; v++){
        do{
            printf("Digite o fabricante da vacina (pfizer, janssen, astrazeneca, moderna, sinopharm ou 'outra'): ");
            fgets(aux.vacina[v].fabricante, 20, stdin);
            aux.vacina[v].fabricante[strlen(aux.vacina[v].fabricante) - 1] = '\0';
            //Comando fgets adiciona no final da string "\n", então para não haver confusão substitui por \0
            
            armazena=validar_fabricante(aux.vacina[v].fabricante);
            
            switch(armazena){
                case 1:
                    strcpy(aux.vacina[v].fabricante, "pfizer");
                    break;
                
                case 2:
                    strcpy(aux.vacina[v].fabricante, "janssen");
                    break;
                    
                case 3:
                    strcpy(aux.vacina[v].fabricante, "astrazeneca");
                    break;
                
                case 4:
                    strcpy(aux.vacina[v].fabricante, "moderna");
                    break;
                    
                case 5:
                    strcpy(aux.vacina[v].fabricante, "sinopharm");
                    break;
                
                case 6:
                    strcpy(aux.vacina[v].fabricante, "outra");
                    break;
                
                default: 
                    printf("\nFabricante invalida!\n");
            }
            
        } while (armazena==7);
        
        printf("Digite o lote da vacina: ");
        fgets(aux.vacina[v].lote, 12, stdin);
        aux.vacina[v].lote[strlen(aux.vacina[v].lote) - 1] = '\0';
        //Comando fgets adiciona no final da string "\n", então para não haver confusão substitui por \0
        
        do{
            printf("Digite a data aplicada (dd/mm/aaaa): ");
            scanf("%d/%d/%d", &aux.vacina[v].dataApli.dia, &aux.vacina[v].dataApli.mes, &aux.vacina[v].dataApli.ano);
            
            retornoData=validar_aplicacao(aux.vacina[v].dataApli);
            
        } while (retornoData == 0); 
    }
    return aux;
}

//Função para cadastrar paciente 
CartVaci cadastrar_paciente() {
    CartVaci aux;
    int retornoTelef=0, retornoNome=0, retornoData=0;
    
    do{
        printf("\nDigite o nome (Por favor nao utilize letras acentuadas): ");
        fgets(aux.nome, 80, stdin);
        aux.nome[strlen(aux.nome) - 1] = '\0';
        //Comando fgets adiciona no final da string "\n", então para não haver confusão substitui por \0
        
        retornoNome=validacao_nome(aux.nome);
        
    } while (retornoNome == 0);
    
    do{
        printf("Digite o telefone (lembre-se de incluir o 0 no inicio com DDD): ");
        fgets(aux.telefone, 20, stdin);
        aux.telefone[strlen(aux.telefone) - 1] = '\0';
        //Comando fgets adiciona no final da string "\n", então para não haver confusão substitui por \0
        
        retornoTelef=validacao_telefone(aux.telefone);
        
    } while (retornoTelef == 0);
    
    do{
        printf("Digite a data de nascimento (dd/mm/aaaa): ");
        scanf("%d/%d/%d", &aux.dataNasc.dia, &aux.dataNasc.mes, &aux.dataNasc.ano);
        getchar();
        
        retornoData=validacao_data(aux.dataNasc);
        
    } while (retornoData == 0);
    
    aux=cadastrar_vacina(aux);
    
    printf("\n");
    
    return aux;
}

//Função para buscar o nome do paciente e fornecer os seus dados e adicionar nova vacina
CartVaci dados_paciente(CartVaci cartVaci[]) {
    CartVaci aux;
    int i, v, quantidade=0, armazena, retornoData=0;
    char paciente[80], adicionar;
    
    printf("\nInforme o nome do paciente (Se o paciente nao for encontrado retornara a tela inicial do sistema): ");
    fgets(paciente, 80, stdin);
    paciente[strlen(paciente) - 1] = '\0';
    //Comando fgets adiciona no final da string "\n", então para não haver confusão substitui por \0
    
    for(i=0; i<TAM; i++) {
        aux=cartVaci[i];
        
        //Verificar se o nome do paciente digitado consta no sistema e fornecer os dados dele
        if (strcmp(paciente, aux.nome)==0){
            printf("\nNome: %s", aux.nome);
            printf("\nTelefone: %s", aux.telefone);
            printf("\nData de nascimento: %02d/%02d/%4d\n", aux.dataNasc.dia, aux.dataNasc.mes,
            aux.dataNasc.ano);
            
            for (v=0; v<5; v++){
                if (aux.vacina[v].dataApli.dia!=0){
                    printf("\nFabricante da vacina: %s", aux.vacina[v].fabricante);
                    printf("\nLote da vacina: %s", aux.vacina[v].lote);
                    printf("\nData aplicada: %02d/%02d/%4d\n", aux.vacina[v].dataApli.dia,
                    aux.vacina[v].dataApli.mes, aux.vacina[v].dataApli.ano);
                }
            }
            
            //Se deseja adicionar novas vacinas ao paciente
            do{
                armazena=0;
                printf("\nDeseja adicionar novas vacinas? (s/n): ");
                scanf(" %c", &adicionar);
                if ((adicionar=='s') || (adicionar=='S')){
                    aux=cadastrar_vacina(aux);
                    
                    printf("\n");
                    return aux;
                    
                } else {
                    if ((adicionar=='n') || (adicionar=='N')){
                        printf("\n");
                        break;
                    } else {
                        printf("\nOpcao Invalida! Digite novamente");
                        armazena++;
                    }
                }
                
            } while (armazena==1);
            break;
        }
    }
    return aux;
}

//Função para listar os pacientes cadastrados em ordem alfabética, e 
//Apresentar: nome, telefone, data de nascimento e quantidade de vacinas tomadas
void listar_paciente(CartVaci cartVaci[]) {
    CartVaci aux;
    int i, j, v, cont=0;
    
	//Deixar os pacientes em ordem alfabética
	for(i=0; i<TAM; i++){
		for(j=0; j<TAM-1; j++){
			if(strcmp(cartVaci[j].nome, cartVaci[j+1].nome)>0){
				aux=cartVaci[j];
				cartVaci[j]=cartVaci[j+1];
				cartVaci[j+1]=aux;
			}
		}
	}
	
	printf("\n                        Nome                        |");
	printf("   Telefone   |Data Nascimento|Vacinas");
	
	//Fornecer alguns dados dos pacientes
    for(i=0; i<TAM; i++) {
        if (cartVaci[i].dataNasc.dia!=0){
            printf("\n %-50s", cartVaci[i].nome);
            printf(" | %-12s", cartVaci[i].telefone);
            printf(" |   %02d/%02d/%4d ", cartVaci[i].dataNasc.dia, cartVaci[i].dataNasc.mes,
            cartVaci[i].dataNasc.ano);
            
            for (v=0; v<5; v++){
                if (cartVaci[i].vacina[v].dataApli.dia!=0){
                    cont++;
                }
            }
            
            printf(" |   %d", cont);
            cont=0;
        }
    }
    
    printf("\n\n");
}

//Função que devolva a quantidade de doses aplicadas de cada fabricante.
void quantidade_fabricante(CartVaci cartVaci[]) {
    int i, v, pfizer=0, janssen=0, astra=0, mode=0, sino=0, outra=0;

    for(i=0; i<TAM; i++) {
        for (v=0; v<5; v++){
            if (strcmp(cartVaci[i].vacina[v].fabricante, "pfizer")==0){
                pfizer++;
            } else {
                if (strcmp(cartVaci[i].vacina[v].fabricante, "janssen")==0){
                    janssen++;
                } else {
                    if (strcmp(cartVaci[i].vacina[v].fabricante, "astrazeneca")==0){
                        astra++;
                    } else {
                        if (strcmp(cartVaci[i].vacina[v].fabricante, "moderna")==0){
                            mode++;
                        } else {
                            if (strcmp(cartVaci[i].vacina[v].fabricante, "sinopharm")==0){
                                sino++;
                            } else {
                                if (strcmp(cartVaci[i].vacina[v].fabricante, "outra")==0){
                                    outra++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    printf("\npfizer: %-3d | janssen: %-3d | astrazeneca: %-3d | moderna: %-3d | sinopharm: %-3d | outras: %-3d\n\n",
    pfizer, janssen, astra, mode, sino, outra);

}

//Função que devolva a quantidade de pacientes por dose
void quantidade_dose(CartVaci cartVaci[]) {
    int i, v, quantVaci;
    float primDose=0.00, segDose=0.00, tercDose=0.00, quarDose=0.00, quintDose=0.00, soma=0.00;
    
    for(i=0; i<TAM; i++) {
        quantVaci=0;
        
        for (v=0; v<5; v++){
            if (cartVaci[i].vacina[v].dataApli.dia!=0){
                quantVaci++;
            }
        }
        
        if(quantVaci == 5){
            quintDose++;
        }
        
        if(quantVaci == 4){
            quarDose++;
        }
        
        if(quantVaci == 3){
            tercDose++;
        }
        
        if(quantVaci == 2){
            segDose++;
        }
        
        if(quantVaci == 1){
            primDose++;
        }
    } 
    
    soma=(primDose+segDose+tercDose+quarDose+quintDose);
    
    printf("\n   Dose   | Quantidade | Percentual");
    printf("\n----------|------------|-----------");
    printf("\n Primeira |     %-3.0f    |  %-3.2f%%   ", primDose, (primDose/soma)*100);
    printf("\n----------|------------|-----------");
    printf("\n  Segunda |     %-3.0f    |  %-3.2f%%   ", segDose, (segDose/soma)*100);
    printf("\n----------|------------|-----------");
    printf("\n Terceira |     %-3.0f    |  %-3.2f%%   ", tercDose, (tercDose/soma)*100);
    printf("\n----------|------------|-----------");
    printf("\n   Quarta |     %-3.0f    |  %-3.2f%%   ", quarDose, (quarDose/soma)*100);
    printf("\n----------|------------|-----------");
    printf("\n   Quinta |     %-3.0f    |  %-3.2f%%   \n\n", quintDose, (quintDose/soma)*100);
}

int main(){
    CartVaci cartVaci[TAM], aux;
    int v, i, j;
    char op;
    
    /*Pacientes pré cadastrados para testar funcionalidades*/
    //Primeiro paciente
    strcpy(cartVaci[0].nome, "Jose Aparecido Junior"); 
    strcpy(cartVaci[0].telefone, "014907639662");
    cartVaci[0].dataNasc.dia=11;
    cartVaci[0].dataNasc.mes=04;
    cartVaci[0].dataNasc.ano=1969;
    /*Primeira Vacina*/
    strcpy(cartVaci[0].vacina[0].fabricante, "pfizer");
    strcpy(cartVaci[0].vacina[0].lote, "PPFF09_001");
    cartVaci[0].vacina[0].dataApli.dia=30;
    cartVaci[0].vacina[0].dataApli.mes=05;
    cartVaci[0].vacina[0].dataApli.ano=2020;
    /*Segunda Vacina*/
    strcpy(cartVaci[0].vacina[1].fabricante, "pfizer");
    strcpy(cartVaci[0].vacina[1].lote, "PPFF12_020");
    cartVaci[0].vacina[1].dataApli.dia=12;
    cartVaci[0].vacina[1].dataApli.mes=01;
    cartVaci[0].vacina[1].dataApli.ano=2021;
    /*Terceira Vacina*/
    strcpy(cartVaci[0].vacina[2].fabricante, "janssen");
    strcpy(cartVaci[0].vacina[2].lote, "JJAA05_099");
    cartVaci[0].vacina[2].dataApli.dia=22;
    cartVaci[0].vacina[2].dataApli.mes=05;
    cartVaci[0].vacina[2].dataApli.ano=2022;
    /*Resto das Vacinas*/
    cartVaci[0]=limpar_cache_vacina(cartVaci[0],3);
    
    //Segundo paciente
    strcpy(cartVaci[1].nome, "Maria de Lourdes Goncalves");
    strcpy(cartVaci[1].telefone, "07733556489");
    cartVaci[1].dataNasc.dia=06;
    cartVaci[1].dataNasc.mes=01;
    cartVaci[1].dataNasc.ano=1940;
    /*Primeira Vacina*/
    strcpy(cartVaci[1].vacina[0].fabricante, "janssen");
    strcpy(cartVaci[1].vacina[0].lote, "JJAA01_001");
    cartVaci[1].vacina[0].dataApli.dia=01;
    cartVaci[1].vacina[0].dataApli.mes=03;
    cartVaci[1].vacina[0].dataApli.ano=2020;
    /*Segunda Vacina*/
    strcpy(cartVaci[1].vacina[1].fabricante, "astrazeneca");
    strcpy(cartVaci[1].vacina[1].lote, "AAZZ02_003");
    cartVaci[1].vacina[1].dataApli.dia=24;
    cartVaci[1].vacina[1].dataApli.mes=07;
    cartVaci[1].vacina[1].dataApli.ano=2021;
    /*Terceira Vacina*/
    strcpy(cartVaci[1].vacina[2].fabricante, "astrazeneca");
    strcpy(cartVaci[1].vacina[2].lote, "AAZZ04_024");
    cartVaci[1].vacina[2].dataApli.dia=18;
    cartVaci[1].vacina[2].dataApli.mes=12;
    cartVaci[1].vacina[2].dataApli.ano=2021;
    /*Resto das Vacinas*/
    cartVaci[1]=limpar_cache_vacina(cartVaci[1],3);
    
    //Terceiro paciente
    strcpy(cartVaci[2].nome, "Joao Manoel Pereira");
    strcpy(cartVaci[2].telefone, "07204596362");
    cartVaci[2].dataNasc.dia=01;
    cartVaci[2].dataNasc.mes=01;
    cartVaci[2].dataNasc.ano=1974;
    /*Primeira Vacina*/
    strcpy(cartVaci[2].vacina[0].fabricante, "moderna");
    strcpy(cartVaci[2].vacina[0].lote, "MMOO02_032");
    cartVaci[2].vacina[0].dataApli.dia=21;
    cartVaci[2].vacina[0].dataApli.mes=9;
    cartVaci[2].vacina[0].dataApli.ano=2020;
    /*Segunda Vacina*/
    strcpy(cartVaci[2].vacina[1].fabricante, "pfizer");
    strcpy(cartVaci[2].vacina[1].lote, "PPFF06_066");
    cartVaci[2].vacina[1].dataApli.dia=14;
    cartVaci[2].vacina[1].dataApli.mes=03;
    cartVaci[2].vacina[1].dataApli.ano=2021;
    /*Terceira Vacina*/
    strcpy(cartVaci[2].vacina[2].fabricante, "sinopharm");
    strcpy(cartVaci[2].vacina[2].lote, "SSHH01_011");
    cartVaci[2].vacina[2].dataApli.dia=9;
    cartVaci[2].vacina[2].dataApli.mes=01;
    cartVaci[2].vacina[2].dataApli.ano=2022;
    /*Resto das Vacinas*/
    cartVaci[2]=limpar_cache_vacina(cartVaci[2],3);
    
    //Quarto paciente
    strcpy(cartVaci[3].nome, "Guilherme Henrique Cruz");
    strcpy(cartVaci[3].telefone, "011999218547");
    cartVaci[3].dataNasc.dia=29;
    cartVaci[3].dataNasc.mes=07;
    cartVaci[3].dataNasc.ano=2001;
    /*Primeira Vacina*/
    strcpy(cartVaci[3].vacina[0].fabricante, "pfizer");
    strcpy(cartVaci[3].vacina[0].lote, "PPFF22_001");
    cartVaci[3].vacina[0].dataApli.dia=22;
    cartVaci[3].vacina[0].dataApli.mes=12;
    cartVaci[3].vacina[0].dataApli.ano=2020;
    /*Segunda Vacina*/
    strcpy(cartVaci[3].vacina[1].fabricante, "Jansen");
    strcpy(cartVaci[3].vacina[1].lote, "JJAA14_044");
    cartVaci[3].vacina[1].dataApli.dia=29;
    cartVaci[3].vacina[1].dataApli.mes=9;
    cartVaci[3].vacina[1].dataApli.ano=2021;
    /*Resto das Vacinas*/
    cartVaci[3]=limpar_cache_vacina(cartVaci[3],2);
    
    //Quinto paciente
    strcpy(cartVaci[4].nome, "Andrezza Riglieterri");
    strcpy(cartVaci[4].telefone, "044992587456");
    cartVaci[4].dataNasc.dia=11;
    cartVaci[4].dataNasc.mes=05;
    cartVaci[4].dataNasc.ano=2006;
    /*Primeira Vacina*/
    strcpy(cartVaci[4].vacina[0].fabricante, "sinopharm");
    strcpy(cartVaci[4].vacina[0].lote, "SSHH01_007");
    cartVaci[4].vacina[0].dataApli.dia=9;
    cartVaci[4].vacina[0].dataApli.mes=9;
    cartVaci[4].vacina[0].dataApli.ano=2021;
    /*Segunda Vacina*/
    strcpy(cartVaci[4].vacina[1].fabricante, "sinopharm");
    strcpy(cartVaci[4].vacina[1].lote, "SSHH07_111");
    cartVaci[4].vacina[1].dataApli.dia=18;
    cartVaci[4].vacina[1].dataApli.mes=06;
    cartVaci[4].vacina[1].dataApli.ano=2022;
    /*Resto das Vacinas*/
    cartVaci[4]=limpar_cache_vacina(cartVaci[4],2);
    
    //Sexto paciente
    strcpy(cartVaci[5].nome, "Samuel da Rosa Silva");
    strcpy(cartVaci[5].telefone, "048992418563");
    cartVaci[5].dataNasc.dia=24;
    cartVaci[5].dataNasc.mes=02;
    cartVaci[5].dataNasc.ano=1974;
    /*Primeira Vacina*/
    strcpy(cartVaci[5].vacina[0].fabricante, "astrazeneca");
    strcpy(cartVaci[5].vacina[0].lote, "AAZZ06_331");
    cartVaci[5].vacina[0].dataApli.dia=03;
    cartVaci[5].vacina[0].dataApli.mes=07;
    cartVaci[5].vacina[0].dataApli.ano=2020;
    /*Segunda Vacina*/
    strcpy(cartVaci[5].vacina[1].fabricante, "astrazeneca");
    strcpy(cartVaci[5].vacina[1].lote, "AAZZ10_011");
    cartVaci[5].vacina[1].dataApli.dia=24;
    cartVaci[5].vacina[1].dataApli.mes=02;
    cartVaci[5].vacina[1].dataApli.ano=2021;
    /*Terceira Vacina*/
    strcpy(cartVaci[5].vacina[2].fabricante, "pfizer");
    strcpy(cartVaci[5].vacina[2].lote, "PPFF44_111");
    cartVaci[5].vacina[2].dataApli.dia=20;
    cartVaci[5].vacina[2].dataApli.mes=01;
    cartVaci[5].vacina[2].dataApli.ano=2022;
    /*Resto das Vacinas*/
    cartVaci[5]=limpar_cache_vacina(cartVaci[5],3);
    
    //Sétimo paciente
    strcpy(cartVaci[6].nome, "Adriano Mauro Magalhaes");
    strcpy(cartVaci[6].telefone, "041982745693");
    cartVaci[6].dataNasc.dia=16;
    cartVaci[6].dataNasc.mes=03;
    cartVaci[6].dataNasc.ano=1980;
    /*Primeira Vacina*/
    strcpy(cartVaci[6].vacina[0].fabricante, "pfizer");
    strcpy(cartVaci[6].vacina[0].lote, "PPFF04_010");
    cartVaci[6].vacina[0].dataApli.dia=11;
    cartVaci[6].vacina[0].dataApli.mes=01;
    cartVaci[6].vacina[0].dataApli.ano=2020;
    /*Segunda Vacina*/
    strcpy(cartVaci[6].vacina[1].fabricante, "jansen");
    strcpy(cartVaci[6].vacina[1].lote, "JJAA03_311");
    cartVaci[6].vacina[1].dataApli.dia=01;
    cartVaci[6].vacina[1].dataApli.mes=8;
    cartVaci[6].vacina[1].dataApli.ano=2020;
    /*Terceira Vacina*/
    strcpy(cartVaci[6].vacina[2].fabricante, "pfizer");
    strcpy(cartVaci[6].vacina[2].lote, "PPFF45_012");
    cartVaci[6].vacina[2].dataApli.dia=30;
    cartVaci[6].vacina[2].dataApli.mes=01;
    cartVaci[6].vacina[2].dataApli.ano=2021;
    /*Quarto Vacina*/
    strcpy(cartVaci[6].vacina[3].fabricante, "pfizer");
    strcpy(cartVaci[6].vacina[3].lote, "PPFF66_001");
    cartVaci[6].vacina[3].dataApli.dia=18;
    cartVaci[6].vacina[3].dataApli.mes=11;
    cartVaci[6].vacina[3].dataApli.ano=2021;
    /*Resto das Vacinas*/
    cartVaci[6]=limpar_cache_vacina(cartVaci[6],4);
    
    //Oitavo paciente
    strcpy(cartVaci[7].nome, "Riquelme Messi Maradona");
    strcpy(cartVaci[7].telefone, "01136614857");
    cartVaci[7].dataNasc.dia=30;
    cartVaci[7].dataNasc.mes=03;
    cartVaci[7].dataNasc.ano=2002;
    /*Primeira Vacina*/
    strcpy(cartVaci[7].vacina[0].fabricante, "moderna");
    strcpy(cartVaci[7].vacina[0].lote, "MMOO03_112");
    cartVaci[7].vacina[0].dataApli.dia=25;
    cartVaci[7].vacina[0].dataApli.mes=9;
    cartVaci[7].vacina[0].dataApli.ano=2021;
    /*Segunda Vacina*/
    strcpy(cartVaci[7].vacina[1].fabricante, "moderna");
    strcpy(cartVaci[7].vacina[1].lote, "MMOO09_114");
    cartVaci[7].vacina[1].dataApli.dia=30;
    cartVaci[7].vacina[1].dataApli.mes=04;
    cartVaci[7].vacina[1].dataApli.ano=2022;
    /*Resto das Vacinas*/
    cartVaci[7]=limpar_cache_vacina(cartVaci[7],2);
    
    //Nono paciente
    strcpy(cartVaci[8].nome, "Thays Miranda");
    strcpy(cartVaci[8].telefone, "096251474855");
    cartVaci[8].dataNasc.dia=07;
    cartVaci[8].dataNasc.mes=10;
    cartVaci[8].dataNasc.ano=1971;
    /*Primeira Vacina*/
    strcpy(cartVaci[8].vacina[0].fabricante, "astrazeneca");
    strcpy(cartVaci[8].vacina[0].lote, "AAZZ33_845");
    cartVaci[8].vacina[0].dataApli.dia=20;
    cartVaci[8].vacina[0].dataApli.mes=01;
    cartVaci[8].vacina[0].dataApli.ano=2020;
    /*Segunda Vacina*/
    strcpy(cartVaci[8].vacina[1].fabricante, "astrazeneca");
    strcpy(cartVaci[8].vacina[1].lote, "AAZZ45_455");
    cartVaci[8].vacina[1].dataApli.dia=03;
    cartVaci[8].vacina[1].dataApli.mes=8;
    cartVaci[8].vacina[1].dataApli.ano=2020;
    /*Terceira Vacina*/
    strcpy(cartVaci[8].vacina[2].fabricante, "moderna");
    strcpy(cartVaci[8].vacina[2].lote, "MMOO41_044");
    cartVaci[8].vacina[2].dataApli.dia=01;
    cartVaci[8].vacina[2].dataApli.mes=05;
    cartVaci[8].vacina[2].dataApli.ano=2021;
    /*Quarto Vacina*/
    strcpy(cartVaci[8].vacina[3].fabricante, "sinopharm");
    strcpy(cartVaci[8].vacina[3].lote, "SSHH06_078");
    cartVaci[8].vacina[3].dataApli.dia=07;
    cartVaci[8].vacina[3].dataApli.mes=06;
    cartVaci[8].vacina[3].dataApli.ano=2022;
    /*Resto das Vacinas*/
    cartVaci[8]=limpar_cache_vacina(cartVaci[8],4);
    
    //Décimo paciente
    strcpy(cartVaci[9].nome, "Jaqueline Peixoto Dias");
    strcpy(cartVaci[9].telefone, "011992654789");
    cartVaci[9].dataNasc.dia=03;
    cartVaci[9].dataNasc.mes=10;
    cartVaci[9].dataNasc.ano=1985;
    /*Primeira Vacina*/
    strcpy(cartVaci[9].vacina[0].fabricante, "janssen");
    strcpy(cartVaci[9].vacina[0].lote, "JJAA09_009");
    cartVaci[9].vacina[0].dataApli.dia=11;
    cartVaci[9].vacina[0].dataApli.mes=12;
    cartVaci[9].vacina[0].dataApli.ano=2020;
    /*Segunda Vacina*/
    strcpy(cartVaci[9].vacina[1].fabricante, "janssen");
    strcpy(cartVaci[9].vacina[1].lote, "JJAA51_051");
    cartVaci[9].vacina[1].dataApli.dia=01;
    cartVaci[9].vacina[1].dataApli.mes=9;
    cartVaci[9].vacina[1].dataApli.ano=2021;
    /*Terceira Vacina*/
    strcpy(cartVaci[9].vacina[2].fabricante, "janssen");
    strcpy(cartVaci[9].vacina[2].lote, "JJAA075_068");
    cartVaci[9].vacina[2].dataApli.dia=25;
    cartVaci[9].vacina[2].dataApli.mes=03;
    cartVaci[9].vacina[2].dataApli.ano=2022;
    /*Resto das Vacinas*/
    cartVaci[9]=limpar_cache_vacina(cartVaci[9],3);
    
    //Décimo primeiro paciente
    strcpy(cartVaci[10].nome, "Paul MacCartney");
    strcpy(cartVaci[10].telefone, "041995886632");
    cartVaci[10].dataNasc.dia=18;
    cartVaci[10].dataNasc.mes=06;
    cartVaci[10].dataNasc.ano=1942;
    /*Primeira Vacina*/
    strcpy(cartVaci[10].vacina[0].fabricante, "pfizer");
    strcpy(cartVaci[10].vacina[0].lote, "PPFF04_036");
    cartVaci[10].vacina[0].dataApli.dia=30;
    cartVaci[10].vacina[0].dataApli.mes=01;
    cartVaci[10].vacina[0].dataApli.ano=2020;
    /*Segunda Vacina*/
    strcpy(cartVaci[10].vacina[1].fabricante, "janssen");
    strcpy(cartVaci[10].vacina[1].lote, "JJAA03_058");
    cartVaci[10].vacina[1].dataApli.dia=15;
    cartVaci[10].vacina[1].dataApli.mes=07;
    cartVaci[10].vacina[1].dataApli.ano=2020;
    /*Terceira Vacina*/
    strcpy(cartVaci[10].vacina[2].fabricante, "pfizer");
    strcpy(cartVaci[10].vacina[2].lote, "PPFF10_010");
    cartVaci[10].vacina[2].dataApli.dia=17;
    cartVaci[10].vacina[2].dataApli.mes=01;
    cartVaci[10].vacina[2].dataApli.ano=2021;
    /*Quarto Vacina*/
    strcpy(cartVaci[10].vacina[3].fabricante, "pfizer");
    strcpy(cartVaci[10].vacina[3].lote, "PPFF45_045");
    cartVaci[10].vacina[3].dataApli.dia=30;
    cartVaci[10].vacina[3].dataApli.mes=10;
    cartVaci[10].vacina[3].dataApli.ano=2021;
    /*Quinta Vacina*/
    strcpy(cartVaci[10].vacina[4].fabricante, "janssen");
    strcpy(cartVaci[10].vacina[4].lote, "JJAA17_017");
    cartVaci[10].vacina[4].dataApli.dia=18;
    cartVaci[10].vacina[4].dataApli.mes=06;
    cartVaci[10].vacina[4].dataApli.ano=2022;
    
    //Décimo segundo paciente
    strcpy(cartVaci[11].nome, "Rita LEE");
    strcpy(cartVaci[11].telefone, "01136985214");
    cartVaci[11].dataNasc.dia=01;
    cartVaci[11].dataNasc.mes=10;
    cartVaci[11].dataNasc.ano=1951;
    /*Primeira Vacina*/
    strcpy(cartVaci[11].vacina[0].fabricante, "astrazeneca");
    strcpy(cartVaci[11].vacina[0].lote, "AAZZ10_100");
    cartVaci[11].vacina[0].dataApli.dia=11;
    cartVaci[11].vacina[0].dataApli.mes=01;
    cartVaci[11].vacina[0].dataApli.ano=2020;
    /*Segunda Vacina*/
    strcpy(cartVaci[11].vacina[1].fabricante, "astrazeneca");
    strcpy(cartVaci[11].vacina[1].lote, "AAZZ20_020");
    cartVaci[11].vacina[1].dataApli.dia=30;
    cartVaci[11].vacina[1].dataApli.mes=8;
    cartVaci[11].vacina[1].dataApli.ano=2020;
    /*Terceira Vacina*/
    strcpy(cartVaci[11].vacina[2].fabricante, "moderna");
    strcpy(cartVaci[11].vacina[2].lote, "MMOO15_015");
    cartVaci[11].vacina[2].dataApli.dia=04;
    cartVaci[11].vacina[2].dataApli.mes=06;
    cartVaci[11].vacina[2].dataApli.ano=2021;
    /*Quarto Vacina*/
    strcpy(cartVaci[11].vacina[3].fabricante, "sinopharm");
    strcpy(cartVaci[11].vacina[3].lote, "SSHH09_911");
    cartVaci[11].vacina[3].dataApli.dia=01;
    cartVaci[11].vacina[3].dataApli.mes=04;
    cartVaci[11].vacina[3].dataApli.ano=2022;
    /*Resto das Vacinas*/
    cartVaci[11]=limpar_cache_vacina(cartVaci[11],4);
    
    //Décimo Terceira paciente
    strcpy(cartVaci[12].nome, "Joe Ramone Ferreira");
    strcpy(cartVaci[12].telefone, "041995714452");
    cartVaci[12].dataNasc.dia=10;
    cartVaci[12].dataNasc.mes=8;
    cartVaci[12].dataNasc.ano=2012;
    /*Primeira Vacina*/
    strcpy(cartVaci[12].vacina[0].fabricante, "pfizer");
    strcpy(cartVaci[12].vacina[0].lote, "PPFF88_081");
    cartVaci[12].vacina[0].dataApli.dia=10;
    cartVaci[12].vacina[0].dataApli.mes=12;
    cartVaci[12].vacina[0].dataApli.ano=2021;
    /*Resto das Vacinas*/
    cartVaci[13]=limpar_cache_vacina(cartVaci[13],1);
    
    //Décimo quarto paciente
    strcpy(cartVaci[13].nome, "Maria Eduarda Costa");
    strcpy(cartVaci[13].telefone, "014785693214");
    cartVaci[13].dataNasc.dia=25;
    cartVaci[13].dataNasc.mes=9;
    cartVaci[13].dataNasc.ano=1996;
    /*Primeira Vacina*/
    strcpy(cartVaci[13].vacina[0].fabricante, "pfizer");
    strcpy(cartVaci[13].vacina[0].lote, "PPFF14_144");
    cartVaci[13].vacina[0].dataApli.dia=14;
    cartVaci[13].vacina[0].dataApli.mes=9;
    cartVaci[13].vacina[0].dataApli.ano=2020;
    /*Segunda Vacina*/
    strcpy(cartVaci[13].vacina[1].fabricante, "pfizer");
    strcpy(cartVaci[13].vacina[1].lote, "PPFF44_471");
    cartVaci[13].vacina[1].dataApli.dia=04;
    cartVaci[13].vacina[1].dataApli.mes=11;
    cartVaci[13].vacina[1].dataApli.ano=2021;
    /*Resto das Vacinas*/
    cartVaci[13]=limpar_cache_vacina(cartVaci[13],2);
    
    //Décimo quinto paciente
    strcpy(cartVaci[14].nome, "Joao Francisco Ferreira");
    strcpy(cartVaci[14].telefone, "041995716985");
    cartVaci[14].dataNasc.dia=16;
    cartVaci[14].dataNasc.mes=03;
    cartVaci[14].dataNasc.ano=2006;
    /*Primeira Vacina*/
    strcpy(cartVaci[14].vacina[0].fabricante, "janssen");
    strcpy(cartVaci[14].vacina[0].lote, "PPFF74_695");
    cartVaci[14].vacina[0].dataApli.dia=01;
    cartVaci[14].vacina[0].dataApli.mes=02;
    cartVaci[14].vacina[0].dataApli.ano=2021;
    /*Segunda Vacina*/
    strcpy(cartVaci[14].vacina[1].fabricante, "pfizer");
    strcpy(cartVaci[14].vacina[1].lote, "PPFF78_025");
    cartVaci[14].vacina[1].dataApli.dia=10;
    cartVaci[14].vacina[1].dataApli.mes=12;
    cartVaci[14].vacina[1].dataApli.ano=2021;
    /*Resto das Vacinas*/
    cartVaci[14]=limpar_cache_vacina(cartVaci[14],2);
    
    //limpando o cache dos outros pacientes
    for(i=15; i<TAM; i++) {
        strcpy(cartVaci[i].nome, " ");
        strcpy(cartVaci[i].telefone, " ");
        cartVaci[i].dataNasc.dia=00;
        cartVaci[i].dataNasc.mes=00;
        cartVaci[i].dataNasc.ano=0000;
        cartVaci[i]=limpar_cache_vacina(cartVaci[i],0);
    }
    
    i=15;
    
    while(1){
        printf("Sistema de dados das carteiras de vacinacao da COVID dos pacientes");
        printf("\n[ 1 ] Cadastrar Paciente");
        printf("\n[ 2 ] Buscar Paciente");
        printf("\n[ 3 ] Listar Todos os Pacientes");
        printf("\n[ 4 ] Quantidade de Doses Aplicadas de Cada Fabricante");
        printf("\n[ 5 ] Quantidade de Pacientes que Tomaram Cada uma das Doses");
        printf("\n[ 0 ] Sair");
        printf("\nOpcao: ");
        scanf(" %c", &op);
        
        switch(op){
            case '1':
                getchar();
                if(i<TAM) {
                    cartVaci[i]=cadastrar_paciente();
                    i++;
                } else {
                    printf("\nDesculpe, o sistema esta lotado\n");
                }
                break;
            
            case '2':
                getchar();
                aux=dados_paciente(cartVaci);
                
                for(j=0; j<TAM; j++) {
                    if (strcmp(aux.nome, cartVaci[j].nome)==0){
                        cartVaci[j]=aux;
                    }
                }
                break;
            
            case '3':
                listar_paciente(cartVaci);
                break;
            
            case '4':
                quantidade_fabricante(cartVaci);
                break;
            
            case '5':
                quantidade_dose(cartVaci);
                break;
            
            case '0':
                printf("\nFinalizando o programa");
                return 0;
            
            default: 
                printf("\nOpcao Invalida! Digite novamente\n");
        }
    }
    return 0;
}