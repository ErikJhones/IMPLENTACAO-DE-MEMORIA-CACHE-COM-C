#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 1
void formato_cache(int *pcache,int *pbloco,int *pconj,int *linha,int *cont_bloc);


void mapeamento_direto(int *x,int *y,int *linha,int *bloco,unsigned long int **for_cache,unsigned long int *num,long int *hit,long int *miss);

void mapeamento_associativo(int *subs,int *x,int *y,int *t,int *linha,int *bloco,unsigned long int **for_cache,unsigned long int *num,int *conjunto,long int *hit,long int *miss);

void enderecos(int *subs,char **argv,int *x,int *y,int *t,unsigned long int *num,int *linha,int *cont_bloc,unsigned long int **for_cache,int *conjunto,long int *hit,long int *miss);

int main(int argc,char **argv){
    long int hit=0,miss=0;
    FILE *p;
    char a[1];
    int tag,i,x,y,t,linha,cont_bloc,subs;
    unsigned long int num,b[TAM][9],**for_cache;
    int cache,bloco,conjunto;
    clock_t inicio,fim;
    double resultado;  
    inicio = clock();
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
    printf("|                           .::CABEÇALHO::.                     \n");
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
    printf("|.::NOME::.     |Erik Jhones Freitas do Nascimento                        \n");
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
    printf("|.::MATRICULA::.|20151045050112                                          \n");
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
    printf("|.::DICIPLINA::.|Arquitetura de Computadores                            \n");
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
    printf("|.::PROFESSOR::.|Otávio Alcântara                                      \n");
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
    puts("\nDigite o valor da chace em bytes.\n");
    scanf("%d",&cache);
    puts("\nDigite o valor do bloco em bytes.\n");
    scanf("%d",&bloco);
    puts("\nDigite o número de linhas do conjunto.(Para mapeamento direto digite valor zero(0) para o conjunto.)\n");
    scanf("%d",&conjunto);
    
    if(conjunto!=0){
       puts("\nDigite o tipo de politica de substituição.\n");
       puts("\nDigite 1 para LRU ou 0 para FIFO.\n");
       scanf("%d",&subs);          
    }   
          
    formato_cache(&cache,&bloco,&conjunto,&linha,&cont_bloc);  
             
    enderecos(&subs,argv,&x,&y,&t,&num,&linha,&cont_bloc,for_cache,&conjunto,&hit,&miss);
    
    
     
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
    printf("|                  .::Tabela dos valores da cache::.                     \n");
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
    if(conjunto==0){
    printf("|.::MAPEAMENTO DIRETO::.    \n");
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n"); 
    }else{
    printf("|.::MAPEAMENTO ASSOCIATIVO POR CONJUNTO::.    \n");
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n"); 
    }
    printf("|.::TAMANHO DA CACHE::.        | %d bytes.                               \n",cache);
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
    printf("|.::TAMANHO DO BLOCO::.        | %d bytes.                               \n",bloco);
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
    printf("|.::LINHAS POR CONJUNTO::.     | %d lnhas.                               \n",conjunto);
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");         
    printf("|.::TOTAL DE HITS::.           | %li hits.                                \n",hit);
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
    printf("|.::TOTAL DE MISS::.           | %li miss.                                \n",miss);
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
    if(subs==1){
    printf("|.::POLITICA DE SUBSTITUIÇÃO::.| LRU escolhida.                         \n");
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
    }else if(subs==0){
    printf("|.::POLITICA DE SUBSTITUIÇÃO::.| FIFO escolhida.                         \n");
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
    }
    tag=32-(linha+cont_bloc);
    printf("|.::ENDEREÇO DA LINHA::.       | %d bits.                                   \n",linha);
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
    printf("|.::ENDEREÇO DO BLOCO::.       | %d bits.                                 \n",cont_bloc);
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
    printf("|.::ENDEREÇO DA TAG::.         | %d bits.                                   \n",tag);
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n"); 
       
    fim = clock();
    resultado = ((double)(fim - inicio))/CLOCKS_PER_SEC;

       
    printf("|.::TEMPO EM SEGUNDOS::.       | %f segundos.                             \n",resultado);
    printf("+-----+--------+--------+-----+--------+--------+-----+--------+--------+\n");
    return 0;
}    

void formato_cache(int *pcache,int *pbloco,int *pconj,int *linha,int *cont_bloc){ 
//define o formato da cache...tamanho de linhas,blocos,tag
     int i,cont_cac,cont_con,x=*pcache,y=*pbloco,w=*pconj,set,tag;
     for(i=0;x>0;i++){
         x/=2;
         cont_cac=i+1;
         if(y>0){
            y/=2;
            *cont_bloc=i;
         }
         
         if(w>0){
            w/=2;
             cont_con=i;
         } 
     }
     *linha=cont_cac - *cont_bloc;
     set=cont_cac -(*cont_bloc + cont_con);
     tag=32-cont_cac;
  
}        
     
void mapeamento_direto(int *x,int *y,int *linha,int *bloco,unsigned long int **for_cache,unsigned long int *num,long int *hit,long int *miss){    
   //essa parte é bem simples....
    
        
     unsigned long int end_blo,end_lin,tag;
         end_blo=*y-1;
         end_lin=(*x-1);
         tag=4294967295 << (*linha + *bloco);
         end_lin=end_lin << *bloco;
         end_blo=end_blo & *num;
         end_lin=(end_lin & *num) >> *bloco;
         tag=tag & *num;
         //printf("en_linha=%lu\n",end_lin);
         if(for_cache[end_lin][0]==tag){
         
            *hit+=1;
         }else{
            *miss+=1;
            for_cache[end_lin][0]=tag;
             
         }        
   
}     

void mapeamento_associativo(int *subs,int *x,int *y,int *t,int *linha,int *bloco,unsigned long int **for_cache,unsigned long int *num,int *conjunto,long int *hit,long int *miss){ 
     int i,j,k,d,a,g;
     unsigned long int end_lin,end_blo,tag,o;
   
    
     end_blo=*y-2;  /*essa parte organiza os endereços da linha,bloco e tag...*/
     end_lin=*x-1;
     tag=4294967295 << (*linha + *bloco);
     end_lin=end_lin << *bloco;
     end_blo=end_blo & *num;
     end_lin=(end_lin & *num) >> *bloco;
     tag=tag & *num;    
     a = *hit;   /*aqui é o final da organização... onde esse a=hit é o que ajuda a seber se ouve hit..*/
       
     for(g=0;g< *t;g+= *y){  /*aqui nesse laço é a verificação de hit..*/ 
          if(for_cache[end_lin][g]==tag){  /* sempre que ha um hit ele da um break e sai do laço.*/
              *hit+=1;
              for_cache[end_lin][g+1]++;
              break;
          }
     }      
     if(a == *hit){  /* nesse if caso aja um hit a será diferente então ele sai e verifica outro endereço..*/
          *miss+=1;  /*caso de um hit...*/
           k=1;
           o=for_cache[end_lin][k];         
           if(*subs==1){                              /*nesse if verifica a politica LRU...*/
               for(k=1;k< (*t - *y);k+= *y){
                   if(o>for_cache[end_lin][k + *y]){
                        d=k + *y;
                        o=for_cache[end_lin][k + *y];
                        // printf("teste ver=%d\n",d); 
                   }else{
                        o=for_cache[end_lin][k];
                        d=k;  
                      
                   } 
                   for_cache[end_lin][d-1]=tag;
           
                   for_cache[end_lin][d]=1;     
              }
            }else{  /* nessa parte ele faz a politica ....FIFO*/
                  j=0;
                  for(i=0;i<(*t - *y);i+= *y){
                      if(for_cache[end_lin][i] == 0){
                          for_cache[end_lin][i]=tag;
                          for_cache[end_lin][i+1]++;
                          break;
                          j=1;
                      }
                   }
                   if(j==0){           
                        for(k=1;k< (*t - *y);k+= *y){
                           if(o>for_cache[end_lin][k + *y]){
                                 d=k;
                                 o=for_cache[end_lin][k];
                                 // printf("teste ver=%d\n",d); 
                            }else{
                                 o=for_cache[end_lin][k + *y];
                                 d=k + *y;  
                           }      
                         }
                         for_cache[end_lin][d-1]=tag;
           
                         for_cache[end_lin][d]=1; 
                         
                   }      
            }       
      }
}  
 
void enderecos(int *subs,char **argv,int *x,int *y,int *t,unsigned long int *num,int *linha,int *cont_bloc,unsigned long int **for_cache,int *conjunto,long int *hit,long int *miss){
    /* verifica e converte os endereços..*/
    FILE *p;
    short int j;
    char a[1];
    int d,i,o,f;
    unsigned long int b[TAM][8],h;
    
    if(*conjunto){  /*cria a memoria dinamica que sera a cache de acordo com os parametro fornecidos...nesse caso associativa*/
         if(*linha==0){
            *y=(2<<(*cont_bloc-1))+1;//na associativa eu juntei o conjunto todo em apenas um.
            *t=*y;                   //então 4 linhas por conjunto vira 1 linha com o tamanho de 4.
            *x=0;
          }else{
               *x=(2<<(*linha-1)) / *conjunto;
               *y=(2<<(*cont_bloc-1))+1;
               *t=*conjunto * (*y);
         }
     
        if(*x==0){
           *x=1;
        }
        for_cache=(unsigned long int**)calloc(*x,sizeof(unsigned long int*));//usei calloc porque já vem zerado
        for(i=0;i < *x;i++){
           *(for_cache+i)=(unsigned long int*)calloc(*t,sizeof(unsigned long int));
        }
    }else{ /* aqui é se for direta...*/
          *x=2<<(*linha-1);
          *y=(2<<(*cont_bloc-1))+1;
          *t=*y;
          for_cache=(unsigned long int**)calloc(*x,sizeof(unsigned long int*));
          for(i=0;i< *x;i++){
              *(for_cache+i)=(unsigned long int*)calloc(*t,sizeof(unsigned long int));
          }
    } 
    
    p = fopen(*(argv+1),"rb");  //abri o arquivo...
    
    if (p == NULL) { // Sempre,sempre,sempre teste se abriu mesmo...
       fprintf(stderr, "ERRO! Não deu para abrir arquivo!!\n");
       exit (1);
    }
    for(h=0;h<1011067;h++){  //laço que verifica todos os endereços dados no arquivo..esse laço é bem amador..
        for(i=0;i<9;i++){
           fscanf(p,"%c",&a[0]);
           *num=strtol(a,NULL,16); //converte hexadecimal para decimal
           b[0][i]=*num;   
           if (feof(p)){
                     
              break;
           }
        }
        *num=0;
        for(i=7,j=0;i>=0;i--,j+=4){
            *num=(b[0][i]<<j)|*num; //esse num é o endereço em sua forma decimal....
        }
        //printf("%lu\n",*num);
         if(*conjunto!=0){
                
            mapeamento_associativo(subs,x,y,t,linha,cont_bloc,for_cache,num,conjunto,hit,miss);
     
         }else{
             mapeamento_direto(x,y,linha,cont_bloc,for_cache,num,hit,miss);
                
         }
     } 
     puts("\nDigite 1 para ver a matriz da cache ou 0 para proceguir.\n");
     scanf("%d",&f);
     if(f){  
   puts("|              .::MATRIZ DA CACHE::..");   
     
          for(i=0;i< *x;i++){
              for(d=0;d< *t;d++){
                  printf("%lu\t",for_cache[i][d]);
              }
              puts("\n");
          }
     
         puts("\n");          
     }     
     for (i=0; i< *x; i++){ //desaloca a cache...
          free(*(for_cache+i));
     }     
    
     free(for_cache);   
              
     fclose(p); //fecha o arquivo...
}    
     
