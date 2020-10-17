/* Versão 1.0 - Normalizar arquivo .rsf

Ler um arquivo .rsf com uma função y(t) qualquer e normalizar
(maior valor será igual a 1)

Exemplo de uso:

		<in.rsf sfnorm > out.rsf
		<out.rsf sfgraph > out.vpl
		sfpen out.vpl

Programador: Rodolfo A. C. Neves	07/11/2018

Acesse conteúdo exclusivo e tire dúvidas no nosso site:

	http://www.dirackslounge.online
*/

#include <rsf.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[])
{

	float *t;
	float o1;
	float d1;
	float maior;
	int i;
	int n1;
	bool verb;
	
	/*inicializar arquivos .rsf*/
	sf_file in;
	sf_file out;

	/*Permite receber variáveis da linhas de comando*/
	sf_init(argc,argv);

	in = sf_input("in");
	out = sf_output("out");

	if(! sf_getbool("verb",&verb)) verb=0;
	/* Modo= 1: modo ativo;	0: modo silencioso */

	if(!sf_histint(in,"n1",&n1)) sf_error("Parâmetro n1 não definido!!!");
	/*Número de amostras*/
	if(!sf_histfloat(in,"d1",&d1)) sf_error("Parâmetro d1 não definido!!!");
	/*Intervalo de amostragem*/
	if(!sf_histfloat(in,"o1",&o1)) sf_error("Parâmetro o1 não definido!!!");
	/*Origem*/

	t=sf_floatalloc(n1);

	sf_floatread(t,n1,in);

	maior=t[0];
	
	//if(verb) sf_warning("O maior antes do laço: %g",maior);

	//Maior valor
	for(i=1;i<n1;i++){

		if(fabs(t[i])>fabs(maior)) maior=fabs(t[i]);
		if(verb) sf_warning("Amostra %i = %g",i,t[i]);
	}

	if(verb) sf_warning("O maior valor do arquivo é: %g",maior);

	//Divide pelo Maior valor
	for(i=1;i<n1;i++){

		t[i]=t[i]/maior;
	}

	sf_floatwrite(t,n1,out);

	exit(0);

}
