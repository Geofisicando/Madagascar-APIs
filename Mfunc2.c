/* Versão 2.0 - Sem arquivo de entrada

Calcula o valor de y(t) dada pela inequação:

y(t)= -3t^2+5 t>=0
y(t)= 3t^2+5 t<0

Defina a janela de amostragem a partir dos parâmetros n1, o1, d1

Exemplo de uso:
		sffunc2 n1=51 o1=-25 d1=1 > func.rsf
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
	float dt; // intervalo de amostragem
	float ot; // origem das amostras
	int i1; // contador laço sobre as amostras
	bool verb; // chave liga=1/desliga=0 modo silencioso

	/* Inicializa arquivos rsf*/
	//sf_file in; // Entrada vetor t
	sf_file out; // Saída vetor y(t)

	/* Permite receber variáveis pela linhas de comando */
	sf_init(argc,argv); 

	if(! sf_getbool("verb",&verb)) verb=0;
	/* Modo= 1: modo ativo;	0: modo silencioso */

	out = sf_output("out"); // Arquivo de saída

	if (verb) sf_warning("Modo ativo ligado!!! verb=1");
     
	if (!sf_getint("n1",&nt)) sf_error("Parâmetro n1 não definido!");
	/* número de amostras */
	if (!sf_getfloat("d1",&dt)) sf_error("Parâmetro d1 não definido!");
	/* intervalo de amostragem */
	if (!sf_getfloat("o1",&ot)) sf_error("Parâmetro o1 não definido!");  
	/* origem */ 
             
	t=sf_floatalloc(nt); // alocar memória vetor t

	/**********[ Preparar o cabeçalho do arquivo de saída ]*************
	* Isso será feito com as seguintes funções:
	*
	* void sf_putint (sf_file file, const char* key, int par)
	* < Coloca um parâmetro int no cabeçalho do arquivo >
	*
	* void sf_putfloat (sf_file file, const char* key,float par)
	* < Coloca um parâmetro float no cabeçalho do arquivo >
	********************************************************************/
	sf_putint(out,"n1",nt); 
	sf_putfloat(out,"d1",dt); 
	sf_putfloat(out,"o1",ot); 

		/*****[ laço sobre as amostras ]*********
		* A função y(t) é dada pela inequação:
		* 	y(t)=-3t^2+5  t>=0
		*	y(t)= 3t^2+5  t<0
		*****************************************/
		for (i1=0; i1 < nt; i1++) {

			t[i1]=ot+dt*i1;

	   		if      (t[i1] >= 0.) t[i1]=-3.*t[i1]*t[i1]+5.;
	    		else if (t[i1] < 0.) t[i1]=3.*t[i1]*t[i1]+5.;
		}
	
	sf_floatwrite(t,nt,out); // Escreve y(t) no arquivo de saída
	
	exit(0);
}
