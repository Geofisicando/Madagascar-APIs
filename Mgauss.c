/* Versão 1.0 - Gera uma função gaussiana para plot

sfgauss cria um arquivo .rsf que é uma função gaussiana definida
pela equação:

	g(x)=cte*exp(-0.5*y(x)*y(x))

Onde:
	cte=(1/(sigma*sqrt(2*PI)))

	PI=3.14159265358979323846

	y(x)=(x-tao)/sigma

Exemplo de uso:

	sfgauss n1=50 d1=0.5 o1=0 sigma=1 tao=3 > out.rsf
	< out.rsf sfgraph > out.vpl
	sfpen out.vpl

Programador: Rodolfo A. C. Neves 07/11/2018

Acesse conteúdo exclusivo e tire dúvidas no nosso site:
	http://www.dirackslounge.online

*/

#include <rsf.h> //inclui a biblioteca do Madagascar
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[])
{
   
	
	float *t; // vetor de coordenadas
	int nt; // número de amostras
	float dt; // intervalo de amostragem
	float ot; // origem das amostras
	float sigma; // desvio padrão da gaussiana
	float tao; // centro da gaussiana
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

	/***********[ Obter parâmetros da linha de comando ]***********/

	if (verb) sf_warning("Modo ativo ligado!!! verb=1");
     
	if (!sf_getint("n1",&nt)) sf_error("Parâmetro n1 não definido!");
	/* número de amostras */
	if (!sf_getfloat("d1",&dt)) sf_error("Parâmetro d1 não definido!");
	/* intervalo de amostragem */
	if (!sf_getfloat("o1",&ot)) sf_error("Parâmetro o1 não definido!");  
	/* origem */ 
	if (!sf_getfloat("sigma",&sigma)) sigma=1.;  
	/* Desvio padrão da distribuição gaussiana */
	if (!sf_getfloat("tao",&tao)) tao=1.;
	/* Centro da gaussiana */ 
             
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

		/*******************[ laço sobre as amostras ]*************************
		* -t[i1] é a função gaussiana
		*
		* -O número PI é definido na linguagem c na biblioteca math.h como M_PI
		*
		* -Eu armazeno o valor de cte (Definida no cabeçalho deste arquivo)
		* na própria variável sigma, para evitar ter que criar mais variáveis
		**********************************************************************/	
		sigma=1./(sigma*sqrt(2.*M_PI));

		for (i1=0; i1 < nt; i1++) {
			
			t[i1]=ot+dt*i1; //inicializa a amostra t[i1]
			t[i1]=(t[i1]-tao)/sigma; // calcula y(x)
			t[i1]=sigma*exp(-0.5*t[i1]*t[i1]); // calcula g(x)

		}
	
	sf_floatwrite(t,nt,out); // Escreve g(x) no arquivo de saída
	
	exit(0);
}
