#include <stdio.h>
#include <stdlib.h>

int TAM;//tamanho usado para definir o tamanho dos arrays que vao conter os valores de chegada e duração. 
float TretornoMedio[3], TrespostaMedio[3], TesperaMedio[3];//vai armazenar os resultados


/*para os 3 arrays acima segue o seguinte padrão:
  posição 1 (no array posição [0]) se refere aos valores de FCFS   
  posição 2 (no array posição [1]) se refere aos valores de SJF 
  posição 3 (no array posição [2]) se refere aos valores de RR   
       
*/



void Calcula_Tempo_Medio(int *Tchegada, int *Tduracao){
     
      float soma[3], Tret = 0, Tresp=0, Tesp=0;
      int i = 0, j = 0, k=0, auxiliar;       
      int contador[TAM];  //contador vai dizer qual o tempo que terminou o processo. 
      int inicio[TAM];  //vai armazenar o momento da primeira execução do processo.
      int Tparada[TAM]; //armazena o tempo em que parou o processo (sem ter terminado)
      int Tespera[TAM]; //armazena o tempo de espera de cada processo      
      int encerra_loop = 0; 
      
      
      //Primeiro Calcula os Tempos do FCFS 
      
            
      for(i = 0; i< TAM; i++){ 
           if(i == 0){
              Tresp = 0; 
              //zera as posições de soma 
              soma[0] = 0;
              soma[1] = 0;
              soma[2] = 0; 
              }
           else{           
              Tresp += Tduracao[i-1];              
              soma[1] += (Tresp - Tchegada[i]); 
                
           }   
           
           Tret += Tduracao[i];
           soma[0] += (Tret - Tchegada[i]); 
       } 
                        
       TretornoMedio[0] = soma[0]/TAM;
       TrespostaMedio[0] = soma[1]/TAM;       
       //no fcfs o tempo de espera = tempo de resposta
       TesperaMedio[0] = soma[1]/TAM;
          
          
          
          
//------------------------------------------------------------------------------------------------------------------------------------------------------------------          
          
          
       //Calcula Agora os Tempos do SJF    
          
        int Prioridade[TAM];//array para determinar a prioridade de quem vai ser executado baseado no tempo de chegada        
        i=0;
        
        //objetivo aqui é organizar os valores tanto em Tchegada como em Tduração ( supõe-se Tchegada já ordenado no arquivo)    
        while(i < (TAM-1)){
             if(Tchegada[i] == Tchegada[i+1]){      
                if(i == 0 && Tduracao[i] <= Tduracao[i+1]){
                       Prioridade[i] = Tduracao[i];
                       Prioridade[i+1] = Tduracao[i+1];      
                }  
                     
                else if (i == 0){
                       Prioridade[i] = Tduracao[i+1];
                       Prioridade[i+1] = Tduracao[i];
                }   
                 
                else if(Prioridade[i] <= Tduracao[i+1]){                  
                       Prioridade[i+1] = Tduracao[i+1];   
                }   
                 
                else{                  
                      Prioridade[i+1] = Prioridade[i];
                      Prioridade[i] = Tduracao[i+1];
                      while(j>k){
                          if(Prioridade[j-1] <= Prioridade[j]){
                             break;      
                          }
                          else{                         
                             auxiliar = Prioridade[j];
                             Prioridade[j] = Prioridade[j-1];
                             Prioridade[j-1] = auxiliar;
                             j--;                         
                          }  
                      }//while j>0                 
                } 
             }//if chegada==chegada+1
             
             else if(i == 0){
                  Prioridade[i] = Tduracao[i];
                  Prioridade[i+1] = Tduracao[i+1];     
                  k = i+1; //flag para não ocorrer permutação de valores de ordem de chegada diferente 
             
             }             
                                   
             
             else{
                  Prioridade[i+1] = Tduracao[i+1];     
                  k = i+1;   //flag para não ocorrer permutação de valores de ordem de chegada diferente               
             }          
             
             i++;                  
             j = i;      
                 
             
        }//while(i < (TAM-1))
           
           
        int mudou_k=0; //variavel para saber se mudou o processo.
        
        k = 0;
        j = 1;
        
        for(i=0; i<TAM; i++){
           contador[i] = 0; 
           inicio[i] = -1; 
           Tespera[i] = 0;  
           Tparada[i] = 0;     
        }    
            
        i = 0;
        
          
        while(encerra_loop == 0){
                 
           Prioridade[k]--;
           contador[k]++; 
           
           if(i == 0){
              inicio[k] = 0;
           }
           
           if(i<TAM-1 && j == 1){
              i++;
           }
           
           else if (j > 1){
              j--;
           }       
                  
           else if (j == 1){
              j = 0;//flag para não comparar mais a situação abaixo;
           }
                                                           
           if(j > 0){                              
              if(Tchegada[i]>Tchegada[i-1]){                                            
                if((Tchegada[i] - contador[k]) == 0){                       
                    if(Prioridade[k] > Tduracao[i]){               
                        contador[i] = contador[k];    
                        Tparada[k] = contador[k];                    
                        k = i;  
                        inicio[k] = contador[k];                                           
                    } 
                }
                else{
                    j++;
                }         
              }
           }
           
           if(Prioridade[k] == 0){
           // se o processo em execução terminou, agora precisa procurar 
           //qual o proximo processo a ser executado. 
                mudou_k = k; //flag para saber se todos os processos ja foram encerrados
                                       
                for(int l = 0; l<TAM ; l++){
                        
                   if(l == 0 && Prioridade[l] > 0){
                      contador[l] = contador[k];              
                      k = l;    
                   }
                   
                   else if(Prioridade[l] > 0 && Prioridade[k] == 0){
                      contador[l] = contador[k];              
                      k = l;                                                                    
                   } 
                   
                   else if(Prioridade[l] > 0 && (Prioridade[l] < Prioridade[k])){
                      contador[l] = contador[k];              
                      k = l;                                                   
                   } 
                }//for
                
                if(Tparada[k] > 0){//ja foi executado antes
                   Tespera[k] += (contador[k] - Tparada[k]);           
                }
                
                if(inicio[k] < 0){ // verificar se é a primeira vez a ser executado o processo
                   inicio[k] = contador[k];
                   if(inicio[k] - Tchegada[k] > 0){//verifica se o processo esperou algum tempo desde que chegou até começar a ser executado
                      Tespera[k] = inicio[k] - Tchegada[k];    
                      }      
                }                   
                
                      
                if (mudou_k == k){
                     encerra_loop = 1;  
                }  
                                 
           } //if  Prioridade[k] == 0
           
                      
        }//while
           
        //tempo de retorno = tempo que termina o processo - tempo que chegou.
        
            
       for(i = 0; i < TAM; i++){ 
           if(i == 0){
           //zera os valores de soma[]
              soma[0] = 0;
              soma[1] = 0;
              soma[2] = 0;        
                
           }
           
           soma[0] += (contador[i] - Tchegada[i]); //Tretorno
           soma[1] += (inicio[i] - Tchegada[i]); //Tresposta
           soma[2] += Tespera[i]; //Tespera      
       } 
                        
       TretornoMedio[1] = soma[0]/TAM;
       TrespostaMedio[1] = soma[1]/TAM; 
       TesperaMedio[1] = soma[2]/TAM;      
        
//---------------------------------------------------------------------------------------------------------------------------------------------------------------          
          
          
          
          
          
 //Por ultimo Calcula os Tempos do RR com quantum 2         
          
        int TduracaoAux[TAM];     
        int fila[TAM], tras=-1, frente=0; // vai armazenar a ordem dos processos 
        int quantum = 2;
                         
        for(i=0; i<TAM; i++){
           contador[i] = 0;              
           inicio[i] = -1; 
           Tespera[i] = 0;  
           Tparada[i] = 0;
           TduracaoAux[i] = Tduracao[i];
           
        }   
         
        encerra_loop = 0; 
        mudou_k=0;   
        i = 0;
        j = 1;
        
        while(encerra_loop == 0){                  
           
           if(i == 0){    //for vai colocar todos os processos com o mesmo tempo de chegada (inicial) na fila
              for(int f = 0; f < TAM; f++){   
                  tras++;
                  fila[tras] = f;
                  
                  if(f < TAM-1 && Tchegada[f+1] > Tchegada[f]) {
                     break;              
                  }          
              }              
              inicio[fila[frente]] = 0;
           }         
           
           if(TduracaoAux[fila[frente]] > quantum){
               TduracaoAux[fila[frente]] -= quantum;
               contador[fila[frente]]+= quantum;  
           }
           else{               
               contador[fila[frente]]+= TduracaoAux[fila[frente]]; 
               TduracaoAux[fila[frente]] = 0; 
           }
           
                       
                      
           if(i<TAM-1 && j == 1){
              i++;
           }
           
           else if (j > 1){
              j--;
           }       
                  
           else if (j == 1){
              j = 0;//flag para não comparar mais a situação abaixo;
           }
                                                           
           if(j > 0){                              
              if(Tchegada[i]>Tchegada[i-1]){//verifica se o tempo de chegada do processo seguinte é maior que o do atual                                            
                if((Tchegada[i] - contador[fila[frente]]) <= 0){ //verificar se o tempo atual condiz com o tempo de chegada do novo processo    
                   
                   while(1){ //adiciona ao fim da fila os novos processos.
                                              
                      tras++;
                      fila[tras] = tras;
                          
                      if(tras == TAM-1){
                         break;             
                      }
                      else if (Tchegada[tras+1] > Tchegada[tras] && (Tchegada[tras+1] - contador[fila[frente]] > 0)){                         
                         i = tras;
                         break;  
                      }                      
                                 
                   }//while 1
                   
                }                 
                else{
                   j++;
                }                    
              }//if chegada> chegada[i-1]
                   
           } //if(j > 0)
           
           
           
           if(tras > 0){ //se tiver pelo menos 2 elementos na fila                           
           
               contador[fila[frente + 1]]  = contador[fila[frente]];//atualiza o contador do proximo processo
               Tparada[fila[frente]] = contador[fila[frente]]; // atualiza o tempo de parada do processo atual
                  
               if(Tparada[fila[frente + 1]] > 0){//se o próximo processo a ser executado ja foi executado antes                      
                  Tespera[fila[frente + 1]] += (contador[fila[frente + 1]] - Tparada[fila[frente + 1]]);                          
               }
           
           }
              
           if(TduracaoAux[fila[frente]] == 0){
           // se o processo em execução terminou, agora precisa sere removido da fila
            
               if (tras == 0){//se era o ultimo processo, agora encerra o loop
                   encerra_loop = 1;  
               } 
                            
               for (int f = 0; f< tras; f++){    //re organiza os processos               
                   fila[f] = fila[f+1];
                   if(f == (tras-1)){
                      tras--;
                   }
               }     
                
                                 
           } //if TduracaoAux[fila[frente]] == 0
           
           else{    
               auxiliar = fila[frente];
               for (int f = 0; f< tras; f++){        //re organiza os processos               
                   fila[f] = fila[f+1];
                   if(f == (tras-1)){
                      fila[tras] = auxiliar;
                   }
               }           
           }
           
           if(inicio[fila[frente]] < 0){
              inicio[fila[frente]] = contador[fila[tras]];  
              Tespera[fila[frente]] += (inicio[fila[frente]] - Tchegada[fila[frente]]); 
           }                
              
                                 
        }//while
           
       
       for(i = 0; i < TAM; i++){ 
           if(i == 0){
           //zera os valores de soma[]
              soma[0] = 0;
              soma[1] = 0;
              soma[2] = 0;        
                
           }
           
           soma[0] += (contador[i] - Tchegada[i]); //Tretorno
           soma[1] += (inicio[i] - Tchegada[i]); //Tresposta
           soma[2] += Tespera[i]; //Tespera  
       } 
                        
       TretornoMedio[2] = soma[0]/TAM;
       TrespostaMedio[2] = soma[1]/TAM; 
       TesperaMedio[2] = soma[2]/TAM;  
        
}


//-------------------------------------------------------------------------------------------------------------------------


int main(int argc, char *argv[]){
       
      FILE *file;
      char conteudo[12];//vai receber os dados do arquivo
      int i=0; 
           
      // nenhum arquivo foi arrastado para o executavel então encerrará o programa
      if (argc == 1){   
          printf("arraste um arquivo .txt com as informacoes necessarias dentro deste arquivo para o executavel do projeto.\n");          
          system("pause");    
          return 0; 
      }
      else {
         if (!(file = fopen(argv[1], "r"))) //abre o arquivo para leitura após ter sido arrastado
            printf ("arquivo nao pode ser aberto\n");
         else{
              
             TAM=0;
             while(fgets(conteudo, 11, file) != NULL) {         //conta quantas linhas tem no arquivo          
                  TAM++; 
             }   
                         
             int Tchegada[TAM], Tduracao[TAM]; 
             fseek(file, 0, SEEK_SET);
             
             while(fgets(conteudo, 11, file) != NULL) {      //transforma os valores obtidos em inteiro                                                                      
                  Tchegada[i] = atoi(conteudo);   
                  for(int j=0; j<10; j++){
                      if (conteudo[j] == ' '){                          
                          Tduracao[i] = atoi(conteudo+j+1);                                                
                          break;                
                      }   
                           
                  }      
                  i++;
             } 
           
             //vai chamar o metedo abaixo para calcular os tempos e então serão printados abaixo.
             Calcula_Tempo_Medio(Tchegada, Tduracao);
            
             
             
             printf("FCFS %d,%d %d,%d %d,%d\n", (int)TretornoMedio[0], (int)((TretornoMedio[0] - (int)TretornoMedio[0])*10),
                                              (int)TrespostaMedio[0], (int)((TrespostaMedio[0] -(int)TrespostaMedio[0])*10), 
                                              (int)TesperaMedio[0], (int)((TesperaMedio[0] -(int)TesperaMedio[0])*10));
             
            
             
             
             printf("SJF %d,%d %d,%d %d,%d\n", (int)TretornoMedio[1], (int)((TretornoMedio[1] - (int)TretornoMedio[1])*10),
                                              (int)TrespostaMedio[1], (int)((TrespostaMedio[1] -(int)TrespostaMedio[1])*10), 
                                              (int)TesperaMedio[1], (int)((TesperaMedio[1] -(int)TesperaMedio[1])*10));
                                              
              
             
             printf("RR %d,%d %d,%d %d,%d", (int)TretornoMedio[2], (int)((TretornoMedio[2] - (int)TretornoMedio[2])*10),
                                              (int)TrespostaMedio[2], (int)((TrespostaMedio[2] -(int)TrespostaMedio[2])*10), 
                                              (int)TesperaMedio[2], (int)((TesperaMedio[2] -(int)TesperaMedio[2])*10)); 
             
             
             
             printf ("\n");
             fclose(file);
         }
      }
       
       system("pause");
       return 0;
}
