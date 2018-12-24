/* Versão 1.0

Calcula o valor de y(t) dada pela inequação:

y(t)= -3t^2+5 t>=0
y(t)= 3t^2+5 t<0

O arquivo de entrada é um vetor de coordenadas t que pode ser gerado
com o sfspike e ajustado com sfmath

Exemplo de uso:
		sfspike n1=51 o1=-25 d1=1 | sfmath output='x1' | sffunc > func.rsf
		func.rsf < sfgraph > func.vpl
		sfpen < func.vpl

Programador: Rodolfo A. C. Neves 01/11/2018

Acesse conteúdo exclusivo e tire dúvidas no nosso site:

	http://www.dirackslounge.online

*/

#include <rsf.h> //inclui a biblioteca do Madagascar
#include <stdio.h>

int main(int argc, char* argv[])
{
   
	
	float *t; // vetor de coordenadas
	int nt; // número de amostras
	int dt; // intervalo de amostragem
	int ot; // origem das amostras
	int i1; // contador laço sobre as amostras
	bool verb; // chave liga=1/desliga=0 modo silencioso

	/* Inicializa arquivos rsf*/
	sf_file in; // Entrada vetor t
	sf_file out; // Saída vetor y(t)

	/* Permite receber variáveis pela linhas de comando */
	sf_init(argc,argv); 

	if(! sf_getbool("verb",&verb)) verb=0;
	/* Modo= 1: modo ativo;	0: modo silencioso */

	in = sf_input("in"); // Arquivo de entrada
	out = sf_output("out"); // Arquivo de saída

	if (verb) sf_warning("Modo ativo ligado!!! verb=1");
     
	if (!sf_histint(in,"n1",&nt)) sf_error("No n1= in input");
	if (!sf_histfloat(in,"d1",&dt)) sf_error("No d1= in input");
	if (!sf_histfloat(in,"o1",&ot)) ot=0.;   
             
	t=sf_floatalloc(nt); // alocar memória vetor t

	sf_floatread(t,nt,in); // ler vetor t do arquivo de entrada

		/*****[ laço sobre as amostras ]*********
		* A função y(t) é dada pela inequação:
		* 	y(t)=-3t^2+5  t>=0
		*	y(t)= 3t^2+5  t<0
		*****************************************/
		for (i1=0; i1 < nt; i1++) {
	   		if      (t[i1] >= 0.) t[i1]=-3.*t[i1]*t[i1]+5.;
	    		else if (t[i1] < 0.) t[i1]=3.*t[i1]*t[i1]+5.;
		}
	
	sf_floatwrite(t,nt,out); // Escreve y(t) no arquivo de saída
	
	exit(0);
}
