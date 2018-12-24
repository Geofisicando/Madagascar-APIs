/*Faz uma cópia de um arquivo rsf que seja um mapa 2D

Programador: Rodolfo A. C. Neves 31/10/2018

Acesse conteúdo exclusivo e tire dúvidas no nosso site:

	http://www.dirackslounge.online

*/

#include <rsf.h> //incluindo a biblioteca do Madagascar
#include <stdio.h> //Biblioteca padrão do C de entrada e saída

int main(int argc, char* argv[])
{
   
	
	float m, h, m0, x0, h0, dh, dm, *amostra, dt,mt;
	float **t;
	int nh, nm, ih, im, nt;
	bool verb; 

	/* Inicializa arquivos rsf*/
	sf_file in; // Arquivo de entrada
	sf_file out; // Saída

	/* Permite receber variáveis pela linhas de comando */
	sf_init(argc,argv); 

	if(! sf_getbool("verb",&verb)) verb=0;
	/* Modo= 1: modo ativo;	0: modo silencioso */

	in = sf_input("in"); // Arquivo de entrada
	out = sf_output("mapa.rsf"); // Arquivo de saída

	if (verb) sf_warning("Verbose ligado!!!");
     
	if (!sf_histint(in,"n1",&nh)) sf_error("No n1= in input");
	if (!sf_histfloat(in,"d1",&dh)) sf_error("No d1= in input");
	if (!sf_histfloat(in,"o1",&h0)) h0=0.;

	if (!sf_histint(in,"n2",&nm)) sf_error("No n2= in input");
	if (!sf_histfloat(in,"d2",&dm)) sf_error("No d2= in input");
	if (!sf_histfloat(in,"o2",&m0)) m0=0.;

	if (!sf_histint(in,"n3",&nt)) sf_error("No n3= in input");
	if (!sf_histfloat(in,"d3",&dt)) sf_error("No d3= in input");
	if (!sf_histfloat(in,"o3",&mt)) mt=0.;
    
          
	if (!sf_getfloat("x0",&x0)) x0=m0;
	/* CMP central */

	m0 -= x0;
    
	t=sf_floatalloc2(nh,nm);
	amostra=sf_floatalloc(nt);
        
	for (im=0; im < nm; im++) {
		m = m0 + im*dm;
	
			for (ih=0; ih < nh; ih++) {
				h = h0+ih*dh;  
			
				sf_floatread(amostra,nt,in);
						
				t[im][ih]=*amostra;
			  
			}
	}
	
	sf_floatwrite(t[0],nh*nm,out); // Escreve o arquivo de saída
	
	exit(0);
}
