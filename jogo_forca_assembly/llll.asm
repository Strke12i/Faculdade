.data
nome:		.asciiz "D:/SistInf/Org/teste.txt"
buffer:		.space	4084
tamanho_buffer:	.word   4084
Palavra:	.space	100
Chutes: 	.space 26
Escreva_char: 	.asciiz "Digite uma letra minuscula?"
Letra_ja_digitada:	.asciiz "Essa letra já foi digitada! Digite outra vez"
Tentativas: 	.word 0
Numero_de_linhas: .word 0



mastro1:	.asciiz " _______    "
mastro2:	.asciiz "|/      |  "
campo_vazio:	.asciiz "|          "
cabeca1:	.asciiz "|      ( )  "
torso1:		.asciiz "|       |    "
torso2:		.asciiz "|      /|    "
torso3:		.asciiz "|      /|\\    "
perna1:		.asciiz "|      /    "
perna2:		.asciiz "|      / \\  "
base1:		.asciiz "|_____________"

voce_ganhou:	.asciiz "Voce ganhou!"
voce_perdeu:	.asciiz "Voce Perdeu!"
continuar_jogando:	.asciiz "Para continuar jogando: digite y \nPara parar: aperta qualquer outra tecla ->"

.text

.eqv        SERVICO_IMPRIME_INTEIRO     1
.eqv        SERVICO_IMPRIME_STRING      4
.eqv        SERVICO_IMPRIME_CARACTERE   11
.eqv	    SERVICO_LER_CARACTER	12
.eqv        SERVICO_OPEN_FILE    	13
.eqv        SERVICO_READ_FILE    	14
.eqv        SERVICO_CLOSE_FILE    	16
.eqv        SERVICO_TERMINA_PROGRAMA    17
.eqv        SERVICO_NUMERO_ALEATORIO    42
.eqv        SUCESSO                     0
.eqv	    CARACTER_ENDLINE		10

init:
	j main
	     

### Função Abrir Arquivo	
abrir_arquivo:
	li $v0, SERVICO_OPEN_FILE   
	la $a0, nome 
	li $a1, 0
	syscall # Vai abrir o arquivo nome e mover o file descriptor para $a0
	move $t0,$v0
	
	li $v0,SERVICO_READ_FILE  
	move $a0, $t0
	
	la $a1, buffer
	lw $a2, tamanho_buffer
	syscall # Vai ler todo o conteúdo do arquivo no buffer
	
	li $v0,SERVICO_CLOSE_FILE  
	move $a0, $t0
	syscall # Fecha o arquivo lido
	
	jr $ra
	
#void le_quantidade_de_linhas_arquivo(){
#	int i = 0;
#	int contador_endline = 0;
#	while( i < 4084){
#		if(buffer[i] == '\0') break;
#		if(buffer[i] == '\n') contador_endline++;
#	}
#	contador_endline--;
#	Numero_de_linhas = contador_endline;
#}
#
le_quantidade_de_linhas_arquivo:
	li $t0, 0 # int i = 0
	li $t1, 0 # contador_endline = 0
	li $t2, CARACTER_ENDLINE # armazena o caracter \n em $t2
	lw $t3, tamanho_buffer	# Carrega o valor do tamanho do buffer
	
incrementa_contador_endline_linhas_arquivo:
	addi $t1, $t1, 1 # incrementa o contador de endline

incrementa_i_linhas_arquivo:
	addi $t0,$t0, 1 # incrementa o contador i

while_linhas_arquivo:
	beq $t0, $t3, fim_linhas_arquivo # Caso tamanho do buffer == i : fim de execução
	lb $t4, buffer($t0) # Carrega o char na posição i do buffer
	beqz $t4, fim_linhas_arquivo # Caso seja \0 : encerra a execução
	
if_linhas_arquivo:
	beq $t4, $t2, incrementa_contador_endline_linhas_arquivo # se buffer[i] = \n : incrementa o contador de endline
	j incrementa_i_linhas_arquivo
	
fim_linhas_arquivo:
	addi $t1,$t1,-1 # diminui um valor do total de linhas
	sw $t1, Numero_de_linhas
	jr $ra
			
#retorna numero aleatorio
retorna_numero_aleatorio:
	li $a0, 0
	lw $a1, Numero_de_linhas
	li $v0, SERVICO_NUMERO_ALEATORIO 
	syscall # Carrega o serviço de gerar numero aleatorio no range $a0 a $a1-> numero de Linhas
	add $v0,$zero,$a0
	jr $ra
	
### Função que vai retornar a posiçao da palavra sorteada no arquivo	
#int retorna_posicao_do_sorteado(int numero_sorteado){
#	int i = 0;
#	int cont_n = 0;
#	while(i < tamanho_buffer){
#		if(buffer[i] == '\n') cont_n ++; 
#		i++;
#		if(cont_n == numero_sorteado) break;
#	}
#	return i;
#}
retorna_posicao_do_sorteado:
	addi  $sp, $sp, -8
	sw $a0,0($sp)
	sw $ra,4($sp) 
	lw $t0, 0($sp) # recebe a quantidade de \n que precisa encontrar
	li $t1, 0 # var i contador 
	li $t2, 0 # endline contador 
	j if_endline_posicao_do_sorteado
	
incrementa_i_posicao_do_sorteado:
	addi $t1,$t1,1 # incrementa_i
	
if_endline_posicao_do_sorteado:
	li $t4,CARACTER_ENDLINE # carrega em $t4 o valor de \n
	lb $t5,buffer($t1) # Carrega o valor em $t5 de buffer[i]
	bne $t4,$t5,if_endline_false_posicao_do_sorteado # caso buffer[i] == \n
	
if_endline_true_posicao_do_sorteado:
	addi $t2,$t2,1 # incrementa o contador de endline
	j while_condicao_posicao_do_sorteado

if_endline_false_posicao_do_sorteado:
	nop
	
if_endlineCont_Sort_posicao_do_sorteado:
	beq $t0,$t2,fim_retorna_posicao_sorteador # Caso i chega ao fim do buffer

while_condicao_posicao_do_sorteado:
	addi $t3, $zero,4084 # Verifica se o contador alcançou o final do buffer
	bne $t1,$t3,incrementa_i_posicao_do_sorteado
	
fim_retorna_posicao_sorteador:
	sw $t1,0($sp)
	lw $ra, 4($sp)
	lw   $v0, 0($sp)    # Vai retornar a posição do \n em que foi sorteado
        addi $sp, $sp, 8    
        jr   $ra            




#### Essa função vai receber um valor de posição dentro do buffer e preencher o space Palavra com os caracteres
#int preenche_palavra(int posicao_buffer){
#	int i = 0;
#	while(buffer[posicao_buffer]!='\r'){
#		Palavra[i] = buffer[posicao_buffer];
#		i++;
#		posicao_buffer ++;
#	}
#	return i;
#
preencher_palavra:
	addi $sp, $sp, -8
	sw $a0,0($sp) 
	sw $ra,4($sp)
	lw $t0, 0($sp) #posição buffer
	li $t1, 0 #variavel i

verifica_endline_string_preencher_palavra:
	li $t2, '\r'
	li $t4, '\n'
	lb $t3, buffer($t0) # Carrega o byte na posição i do buffer
	beq $t2,$t3, fim_preenche_preencher_palavra # verifica se o caracter é \n
	beq $t3,$t4, fim_preenche_preencher_palavra # verifica se o caracter é \r
	
salva_na_palavra_preencher_palavra:
	sb $t3,Palavra($t1) # Salva o byte na palavra de acordo com a sua posição
	addi $t0,$t0,1 # incrementa pos
	addi $t1,$t1,1 # incrementa i
	j verifica_endline_string_preencher_palavra
		
	
fim_preenche_preencher_palavra:
	sw $t1,0($sp)
	li $t2, '\0'
	addi $t1,$t1,1
	sb $t2,Palavra($t1) # Adiciona o \n no final da palavra
	lw $ra, 4($sp)
	lw   $v0, 0($sp)    # Retorna o tamanho da palavra 
        addi $sp, $sp, 8   
        jr   $ra
			

##### Vai ler um char válido(minusculo) e retorná-lo
#char ler_caracter(){
#	char c;
#	while(1){
#		c = scanf();
#		if(!((int)c <= 96 || (int)c >= 123))
#			break;
#	}
#	return c;
#}
#
ler_caracter:
	addi  $sp, $sp, -8
	sw $ra, 0($sp)

loop_char:
	li $v0, SERVICO_IMPRIME_CARACTERE
	li $a0, CARACTER_ENDLINE
	syscall # Faz o print do \n
pede_char:
	li $v0, SERVICO_IMPRIME_STRING
	la $a0, Escreva_char
	syscall # Imprime string pedindo para o usuario digitar
	li   $v0, SERVICO_LER_CARACTER     
  	syscall  # Carrega o char lido em v0
  	add $a0, $v0, $zero #move para a0 o char recebido
  	sw $a0, 4($sp)
  	lw $t1, 4($sp)

char_valido:
	li $t2,123 	# Caracter z
	li $t3,96	# Caracter a	
	bge $t1,$t2,loop_char # Entra em loop caso o char seja maior que z
	ble $t1,$t3,loop_char # Entra em loop caso o char seja menor que a

fim_ler_caracter:
	lw   $v0, 4($sp)  # Retorna o char lido
	lw $ra, 0($sp) 
        addi $sp, $sp, 8   
        jr   $ra
        
        
#### Vai verificar se na palavra existe o char x e retornar quantos valores desse há na palavra
#bool verifica_char_na_palavra(char letra,int tamanho_palavra)
#{
#	int i = 0;
#	while( i < tamanho_palavra){
#		if(letra == Palavra[i]) return 1;
#		i++;	
#	}
#	return 0;
#}
verifica_char_na_Palavra:
	addi  $sp, $sp, -12
	sw $a0,0($sp) 
	lw $t0, 0($sp) # tamanho palavra
	sw $a1,4($sp) 
	sw $ra,8($sp)
	lw $t1, 4($sp) # char recebido 
	li $t2 , 0 # var i
	li $t3, 0 # contador de vezes na palavra
	j percorre_palavra_verifica_char_na_Palavra

incrementa_var_i_verifica_char_na_Palavra:
	addi $t2,$t2,1 # incrementa i 
		
percorre_palavra_verifica_char_na_Palavra:	
	beq $t0,$t2,fim_verifica_char_na_Palavra #Verifica se chegou no fim da palavra
	lb $t4,Palavra($t2) # carrega o char
	beq $t1,$t4,incrementa_contador_verifica_char_na_Palavra #vai comparar o char recebido e verificar se ele é char carregado
	j incrementa_var_i_verifica_char_na_Palavra
		
incrementa_contador_verifica_char_na_Palavra:
	addi $t3,$t3,1 # incrementa o valor de retorno

fim_verifica_char_na_Palavra:
	sw $t3,0($sp) 
	lw $ra, 8($sp)
	lw $v0, 0($sp) # Retorna o booleano de encontrou o char
	addi  $sp, $sp, 12
	jr $ra


# bool verifica_se_letra_ja_foi_usada(char letra){
#	int i = 0;
#	while( i < Tentativas ){
#		if(letra == Chutes[i]) return 1;
#		i++;
#	}
#	return 0;
#}

verifica_se_letra_ja_foi_usada:
	addi $sp,$sp, -8
	sw $a0,0($sp) 
	sw $ra,4($sp)
	lw $t0, 0($sp) # Salva o char que vem como argumento da função em $t0
	li $t1, 0 # Cria um booleano para dizer se encontrou ou não o caracter no array de chutes
	lw $t2, Tentativas # Pega a quantidade de tentativas, que é o mesmo que a quantidade de vezes válida que o player jogou
	li $t3, 0	# variável i contador que serve para percorrer o array de chutes
	
	j while_letra_ja_foi_usada
	
incrementa_i_while_letra_ja_foi_usada: # Vai incrementar em 1 o contador I 
	addi $t3,$t3,1 
	j while_letra_ja_foi_usada

encontrou_char_nos_chutes: # Caso seja encontrado o char no array de chutes, muda o valor do booleano para True
	addi $t1,$t1,1
	j fim_letra_ja_foi_usada

while_letra_ja_foi_usada: 
	beq $t3, $t2, fim_letra_ja_foi_usada # Verifica a condição do while onde i < tentativas
	lb $t4, Chutes($t3) # carrega o char do array de chutes
	beq $t0, $t4, encontrou_char_nos_chutes # Compara se o char recebido na função é igual a Chutes[i]
	j incrementa_i_while_letra_ja_foi_usada
	
fim_letra_ja_foi_usada: # Retorna o booleano para a função chamadora e remonta a pilha
	sw $t1,0($sp)
	lw $v0,0($sp) 
	lw $ra,4($sp)
	addi $sp,$sp,8
	jr $ra

#verifica se todas as letras da palavra estão no chute
#bool verifica_se_ganhou(int tamanho_palavra){
#	int i = 0;
#	while(i < tamanho_palavra){
#		if(!verifica_se_letra_ja_foi_usada(Palavra[i])) return 0; 
#		i++;
#	}
#	return 1;
#	
verifica_se_ganhou:
	addi $sp,$sp,-16
	sw $a0, 0($sp)
	sw $ra, 4($sp)
	lw $t0, 0($sp) # carrega tamanho_da palavra
	li $t1, 0 # contador i
	j while_verifica_se_ganhou

incrementa_i_verifica_se_ganhou:
	addi $t1,$t1,1

while_verifica_se_ganhou:
	beq $t1,$t0, fim_verifica_se_ganhou # Verifica se chegou ao final da palavra
	lb $a0, Palavra($t1) # Carrega o char da palavra na posição i
	sw $t0, 8($sp) # Salva os valores na pilha
	sw $t1, 12($sp)
	jal verifica_se_letra_ja_foi_usada # chama a função verifica_se_letra_ja_foi_usada
	sw $v0, 0($sp)
	lw $t2, 0($sp)
	lw $t0, 8($sp)
	lw $t1, 12($sp)

compara_saida_verifica_se_ganhou:
	beqz $t2, fim_verifica_se_ganhou # Verifica se o retorna da função verifica_se_letra_ja_foi_usada
	j incrementa_i_verifica_se_ganhou
	 
fim_verifica_se_ganhou:
	sw $t2,0($sp)
	lw $v0,0($sp) # Retorna o booleano dizendo se ganhou ou não
	lw $ra, 4($sp)
	addi $sp,$sp,16
	jr $ra

Print_endline: # Faz o print do endline
	li $a0, CARACTER_ENDLINE
	li $v0, SERVICO_IMPRIME_CARACTERE
	syscall
	jr $ra

printf: # Imprime uma string passada como argumento
	li $v0, SERVICO_IMPRIME_STRING
	syscall
	li $a0, '\n'
	li $v0, SERVICO_IMPRIME_CARACTERE
	syscall
	jr $ra
		
#void printa_forca(int errors){
#	printf("  _______       \n");
#	printf(" |/      |      \n");
#	printf(" |      %c  \n", (erros>=5?'(':' '));
#	printf(" |    %c%c%c  \n", (erros>=3?'\\':' '), (erros>=4?'|':' '), (erros>=3?'/': ' '));
#	printf(" |     $c %c      \n", (erros>=2?'|':' '),erros>=1?'|':' '));
#	printf(" |          \n");
#	printf("_|___           \n");
#}
#
#



printa_forca:
	addi $sp,$sp,-8
	sw $ra, 0($sp)
	sw $a0, 4($sp)
	lw $t0, 4($sp) # vidas
	jal Print_endline
mastro: # Faz o print do mastro da forca
	la $a0, mastro1
	jal printf
	la $a0, mastro2 
	jal printf

cabeca: # Verifica se a vida é maior que 5 e faz o print da forca
	la $a0, campo_vazio 
	li $t1, 5
	bgt $t0, $t1, printa_cabeca
	la $a0, cabeca1
printa_cabeca:
	jal printf
torso: # Verifica todos os membros do torso e faz o print de acordo com a vida
	la $a0, campo_vazio 
	li $t1, 4
	bgt $t0, $t1, printa_torso
	la $a0, torso1 
	li $t1, 3
	bgt $t0, $t1, printa_torso
	la $a0, torso2
	li $t1, 2
	bgt $t0, $t1, printa_torso
	la $a0, torso3
printa_torso:
	jal printf
pernas:  # Verifica todos os membros das pernas e faz o print de acordo com a vida
	la $a0, campo_vazio 
	li $t1, 1
	bgt $t0, $t1, printa_pernas
	la $a0, perna1
	li $t1, 0
	bgt $t0, $t1, printa_pernas
	la $a0, perna2
printa_pernas:
	jal printf
base: # Faz o print da base
	la $a0, campo_vazio
	jal printf
	la $a0, base1
	jal printf
fim_print_forca:
	lw $ra,0($sp)
	addi $sp,$sp,8
	jr $ra

#void printa_palavra(int tamanho_palavra){
#	int i = 0;
#	while(i<tamanho_palavra){
#		int j = 0;
#		char caracter = '_';
#		while(j < Tentativas){
#			if(Palavra[i] == Chutes[j])
#			{
#				caracter = Palavra[i];
#				break;
#			}
#			j++;
#		}
#		printf("%c",caracter);
#		i++;
#	}
#	printf("\n");
#}
printa_palavra:
	addi $sp,$sp,-4
	sw $ra,0($sp)
	add $t0, $zero, $a0
	li $t1, 0 # Contador i = 0
	j while_percorre_palavra_printa_palavra

incrementa_i_printa_palavra:
	addi $t1, $t1, 1 # Faz o incremento de i
	j while_percorre_palavra_printa_palavra
	
incrementa_j_printa_palavra:
	addi $t3,$t3, 1 # faz o incremento de j
	j while_percorre_chutes_printa_palavra

while_percorre_palavra_printa_palavra:
	beq $t1, $t0, fim_printa_palavra # Caso i seja igual ao tamanho da palavra : fim
	li $t2, '_'
	li $t3, 0

while_percorre_chutes_printa_palavra:
	lw $t4,Tentativas
	beq $t3,$t4, printa_caracter_printa_palavra # Verifica se j é igual ao numero de tentativas
	lb $t5, Palavra($t1) 
	lb $t6, Chutes($t3)
	beq $t5,$t6,atribui_valor_em_caracter_printa_palavra # Compara se o chute é igual a palavra
	j incrementa_j_printa_palavra

atribui_valor_em_caracter_printa_palavra:
	move $t2, $t5 # Troca o valor de _ para o char

printa_caracter_printa_palavra: # Imprime o caracter mais espaço
	li $v0, SERVICO_IMPRIME_CARACTERE
	add $a0, $zero, $t2
	syscall
	li $v0, SERVICO_IMPRIME_CARACTERE
	li $a0, ' ' # CARACTER ESPAÇO
	syscall
	j incrementa_i_printa_palavra

fim_printa_palavra:	
	jal Print_endline
	lw $ra, 0($sp)
	addi $sp,$sp,4
	jr $ra


#void adiciona_letra_nos_chutes(char letra){
#	Chutes[Tentativas] = letra;
#	Tentativas++;
#}
#
adiciona_letra_nos_chutes:
	addi $sp,$sp,-4
	sw $ra, 0($sp)
	la $t0, Tentativas
	lw $t1, 0($t0)
	
	sb $a0, Chutes($t1)
	addi $t1,$t1,1
	sw $t1, 0($t0)

	lw $ra, 0($sp)
	addi $sp,$sp,4
	jr $ra


#Cuida de pegar a palavra do arquivo e retorna o tamanho da palavra
#int Sorteia_Palavra(){
#	abrir_arquivo();
#	int linha_sorteada = retorna_numero_aleatorio();
#	int posicao_no_buffer = retorna_posicao_do_sorteado(linha_sorteada);
#	return preencher_palavra(posicao_buffer);
#}
Sorteia_Palavra:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal abrir_arquivo 
	jal le_quantidade_de_linhas_arquivo
	jal retorna_numero_aleatorio
	add $a0, $zero,$v0
	jal retorna_posicao_do_sorteado
	add $a0, $zero,$v0
	jal preencher_palavra # retorna em v0 o tamanho da palavra
	lw $ra, 0($sp)
	jr $ra


#Jogo
#void Jogo(){
#	int tamanho_palavra = Sorteia_Palavra();
#	int vidas = 6;
#	while(vida != 0){
#		printa_forca(vidas);
#		printa_palavra(tamanho_palavra);
#		char letra = ler_caracter();
#		if(verifica_se_letra_ja_foi_usada) // tratar erro
#		adicionar_letra_nos chutes(letra);
#		if(!verifica_char_na_Palavra) vidas--;
#		if(verifica_se_ganhou){
#			ganhou();
#			return;
#		}
#	}
#	perdeu();
#}
#

#zerar variaveis globais
#void zerar_variaveis(){
#	int i = 0;
#	while(i != Tentativas){
#		Chutes[i] = '\0';
#	}
#	Tentativas = 0;
#}
Zerar_variaveis:
	addi $sp,$sp, -4
	sw $ra, 0($sp)
	li $t0, 0
	lw $t1, Tentativas
	j while_i_Zerar_variaveis
	
incrementa_i_Zerar_variaveis:
	addi $t0,$t0,1

while_i_Zerar_variaveis:
	beq $t0,$t1, fim_Zerar_Variaveis
	li $t2, '\0' # Carrega o valor de 0 no Chutes
	sb $t2, Chutes($t0)
	j incrementa_i_Zerar_variaveis

fim_Zerar_Variaveis:	
	li $t0, 0
	sw $t0, Tentativas # Muda o valor de tentativas para 0
	lw $ra, 0($sp)
	addi $sp,$sp, 4
	jr $ra

main: # Age como a função main
	addi $sp,$sp, -16
	sw $ra, 0($sp)
	
	jal Zerar_variaveis
	
	jal Sorteia_Palavra
	
	sw $v0, 4($sp)
	lw $t0, 4($sp) # Tamanho da Palavra
	
	li $t1, 6 #Vidas
	sw $t1, 8($sp)
	
while_Jogo:
	nop
	
printa_Jogo:
	lw $t1, 8($sp)
	beqz $t1, perdeu_Jogo # Se vidas == 0 acaba o jogo
	add $a0, $zero ,$t1 # Passa como paramentro
	jal printa_forca 
	lw $t0, 4($sp)
	add $a0, $zero ,$t0
	jal printa_palavra  #printa_forca(tamanho_palavra)
	j Caracter_Jogo

letra_ja_foi_usada_Jogo: # Vai fazer o print se a letra ja foi usada
	jal Print_endline
	la $a0, Letra_ja_digitada
	li $v0, SERVICO_IMPRIME_STRING
	syscall
	jal Print_endline
		
Caracter_Jogo:
	jal ler_caracter
	add $t2, $zero ,$v0 # $t2 recebe o char que volta de ler_caracter
	add $a0, $zero ,$t2
	sw $t2, 12($sp)
	jal verifica_se_letra_ja_foi_usada
	add $t3, $zero ,$v0
	bgtz $t3, letra_ja_foi_usada_Jogo # Vai pular se a letra ja foi usada

Vida_Jogo: # Vai cuidar da vida caso o caracter não esteja na palavra
	jal Print_endline
	lw $t2, 12($sp)
	add $a0, $zero ,$t2
	jal adiciona_letra_nos_chutes # Vai adiconar o char nos chutes
	lw $t0, 4($sp)
	add $a0, $zero ,$t0
	lw $t2, 12($sp)
	add $a1, $zero ,$t2
	jal verifica_char_na_Palavra
	add $t3, $zero ,$v0
	beqz $t3,dimunui_vida_Jogo # Caso o char não esteja na palavra diminui uma vida
	
Verifica_se_completou_Jogo:
	lw $t0, 4($sp)
	add $a0, $zero ,$t0
	jal verifica_se_ganhou # retorna 1 se ganhou 0 se não 
	add $t3, $zero ,$v0
	bgtz $t3, ganhou_Jogo # Pula para a mensagem de ganhou
	j while_Jogo

perdeu_Jogo:
	la $a0, voce_perdeu
	li $v0, SERVICO_IMPRIME_STRING
	syscall
	j fim_Jogo

ganhou_Jogo:
	la $a0, voce_ganhou
	li $v0, 4
	syscall
	j fim_Jogo
	
dimunui_vida_Jogo:
	lw $t1,8($sp)
	subi $t1,$t1,1 # Retirar um do contador da vida
	sw $t1,8($sp)
	j while_Jogo
	
fim_Jogo:
	jal Print_endline
	lw $t1,8($sp)
	add $a0, $zero ,$t1 # Passa como paramentro
	jal printa_forca 
	lw $t0, 4($sp)
	add $a0, $zero ,$t0
	jal printa_palavra  #printa_forca(tamanho_palavra)

continuar_Jogo:
	la $a0, continuar_jogando
	li $v0, SERVICO_IMPRIME_STRING
	syscall
	li   $v0, SERVICO_LER_CARACTER       
  	syscall
  	li $t0, 'y'
  	add $t1, $zero, $v0
  	beq $t1, $t0, main
  	           
encerra_jogo:
	
	addi $sp,$sp, 16
	addiu $v0, $zero, SERVICO_TERMINA_PROGRAMA # serviÃ§o 17 - tÃ©rmino do programa: exit2
        addiu $a0, $zero, SUCESSO # resultado da execuÃ§Ã£o do programa, 0: sucesso
        syscall
	
