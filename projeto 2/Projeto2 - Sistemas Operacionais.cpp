#include <stdio.h>
#include <stdlib.h>

int TAM; //tamanho usado para definir o tamanho dos arrays que vao conter os valores de chegada e duração. 


int Calcula_Falta_FIFO(int Nquadros, int *frequencia){
     int i = 0, j=0, fila[Nquadros], falta=0;
     int frente=0, tras=-1;
     
     for (i; i<Nquadros; i++){ 
        fila[i] = -1;
     }
     
     for (i = 0; i<TAM-1; i++){
         
        if(i==0){ //paginas vazias, adiciona o primeiro elemento na memoria e incrementa falta
           fila[frente] = frequencia[i];
           tras++;
           falta++;         
        }
        
        else{ 
            //Comparará o elemento que entrou na memoria com os que já estão lá. Se não encontrar  
            //mas tiver quadro livre, adiciona ao quadro e incrementa falta. Se não tiver, coloca no lugar de "frente".  
           for(j=0; j<Nquadros; j++){ 
              if(frequencia[i] == fila[j]){
                 break;
              }
              else if(j==Nquadros-1 && fila[j] == -1){
                 tras++;  
                 fila[tras] = frequencia[i];
                 falta++;
              }  
              else if(j==Nquadros-1){
                 //se chegou aqui é por que não encontrou o elemento na memoria e os quadros estão todos ocupados
                 fila[frente] = frequencia[i];
                 frente++;
                 falta++;
                 if(frente == Nquadros){
                    frente = 0;
                 }  
              }   
                              
           }//for j
           
        }//else        
        
     }//for i
     return falta;
}



int Calcula_Falta_OTM(int Nquadros, int *frequencia){
     
     int i = 0, j=0, k=0, fila[Nquadros], falta=0;
     int tras=-1, maior, posicao=0, distancia;
     bool flag = false;
     
     for (i; i<Nquadros; i++){ 
        fila[i] = -1;
     }
     
      for (i = 0; i<TAM-1; i++){
         
        if(i==0){ //paginas vazias, adiciona o primeiro elemento na memoria e incrementa falta
           tras++;
           fila[tras] = frequencia[i];
           falta++;         
        }
        
        else{ 
            /*Comparará o elemento que entrou na memoria com os que já estão lá. Se não encontrar  
            mas tiver quadro livre, adiciona ao quadro e incrementa falta. Se não tiver vai usar o algoritimo OTIMO.*/  
            
           for(j=0; j<Nquadros; j++){ 
                                  
              if(frequencia[i] == fila[j]){                
                 break;
              }
              else if(j==Nquadros-1 && fila[j] == -1){
                 tras++;  
                 fila[tras] = frequencia[i];
                 falta++;                
              }  
              else if(j==Nquadros-1){
                 //se chegou aqui é por que não encontrou o elemento na memoria e os quadros estão todos ocupados
                 //vai setar flag para true para poder entrar na condição abaixo
                 flag = true;
              }   
                              
           }//for j
           
           if(flag == true){                   
               //vai agora comparar os elementos que estão na memoria e encontrar o que vai demorar mais para ser usado    
               maior = -1;  
               posicao = 0;             
               for(j=0; j<Nquadros; j++){ 
                   distancia = 0;                   
                   for(k = i+1; k<TAM-1; k++){
                      if(fila[j] != frequencia[k]){
                         distancia++;  
                      }  
                      else {                         
                         break;                                       
                      }
                   } //for k
                   if(distancia > maior){
                       maior = distancia; 
                       posicao = j;                                        
                   }
               }//for j                   
               fila[posicao] = frequencia[i];
               falta++;  
               flag = false;  
           }//if
           
        }//else        
        
     }//for i
     
     return falta;
}


int Calcula_Falta_LRU(int Nquadros, int *frequencia){
     
     int i = 0, j=0, fila[Nquadros], falta=0;
     int tras=-1, contador[Nquadros], maior, posicao=0;
     bool flag = false;
          
     for (i; i<Nquadros; i++){ 
        fila[i] = -1;
        contador[i] = -1;
     }
     
      for (i = 0; i<TAM-1; i++){
         
        if(i==0){ //paginas vazias, adiciona o primeiro elemento na memoria e incrementa falta
           tras++;
           fila[tras] = frequencia[i];
           falta++;         
        }
        
        else{ 
            /*Comparará o elemento que entrou na memoria com os que já estão lá. Se não encontrar  
            mas tiver quadro livre, adiciona ao quadro e incrementa falta. Se não tiver vai usar o algoritimo LRU.*/  
            
           for(j=0; j<Nquadros; j++){ 
                                  
              if(frequencia[i] == fila[j]){ 
                 contador[j] = -1;               
                 break;
              }
              else if(j==Nquadros-1 && fila[j] == -1){
                 tras++;  
                 fila[tras] = frequencia[i];                 
                 falta++;                
              }  
              else if(j==Nquadros-1){
                 //se chegou aqui é por que não encontrou o elemento na memoria e os quadros estão todos ocupados
                 //vai setar flag para true para poder entrar na condição abaixo
                 flag = true;
              }   
                              
           }//for j
           
           if(flag == true){                   
               //vai agora comparar os contadores para ver qual o maior. O maior será substituido.    
               maior = -1;  
               posicao = 0;             
               for(j=0; j<Nquadros; j++){                   
                   if(contador[j] > maior){
                       maior = contador[j]; 
                       posicao = j;                                        
                   }
               }//for j       
                                          
               fila[posicao] = frequencia[i];
               falta++;  
               contador[posicao] = -1;
               flag = false;  
           }//if           
                      
        }//else        
        
        for (j=0; j<Nquadros; j++){//incrementar o contador.
            if(fila[j] != -1){
               contador[j]++;        
            }    
        }
                
     }//for i
     
     return falta;
}





//-------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[]){
       
      FILE *file;
      char conteudo[3];//vai receber os dados do arquivo
      int i=0, Nquadros = 0; 
           
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
             while(fgets(conteudo, 3, file) != NULL) {         //conta quantas linhas tem no arquivo          
                  TAM++;                    
             }                           
             
             int frequencia[TAM-1];
             
             fseek(file, 0, SEEK_SET);
             
             while(fgets(conteudo, 3, file) != NULL) {      //transforma os valores obtidos em inteiro                                                                      
                  if(i == 0){
                    Nquadros = atoi(conteudo);
                  }
                  else{
                    frequencia[i-1] = atoi(conteudo); 
                  }     
                  i++;                  
             } 
           
                              
            
             printf("FIFO %d\n", Calcula_Falta_FIFO(Nquadros, frequencia)); 
             printf("OTM %d\n", Calcula_Falta_OTM(Nquadros, frequencia)); 
             printf("LRU %d", Calcula_Falta_LRU(Nquadros, frequencia)); 
                     
             printf ("\n");
             fclose(file);
         }
      }
       
       system("pause");
       return 0;
}
