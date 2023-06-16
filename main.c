//CÓDIGO POR ANDREI RAMOS LOPES
//CALCULADORA DE DETERMINANTE
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// void printMatriz(int m, int n, int **matriz) {
//   for (int i = 0; i < m; i++) {
//     for (int j = 0; j < n; j++) {
//       printf("%d ", matriz[i][j]);
//     }
//     printf("\n");
//   }
// }

int countRowZeroes(int i, int n, int **matriz) {
  int flag = 0;
  for (int j = 0; j < n; j++) {
    if (matriz[i][j] == 0) {
      flag++;
    }
  }
  return flag;
}

int countColZeroes(int j, int n, int **matriz) {
  int flag = 0;
  for (int i = 0; i < n; i++) {
    if (matriz[i][j] == 0) {
      flag++;
    }
  }
  return flag;
}

int determinante(int m, int n, int **matriz) {
  if (m != n) {
    printf("A MATRIZ DEVE SER QUADRADA\n");
    return -32767;
  }
  if (matriz == NULL) {
    printf("ERRO! MATRIZ INVÁLIDA\n");
    return -32767;
  }
  int det = 0;
  if (m < 1 || n < 1) {
    printf("A MATRIZ DEVE TER UM NÚMERO VÁLIDO DE LINHAS E COLUNAS\n");
    return -32767;
  } else if (m == 1) {
    det = matriz[0][0];
    // printDeterminante(det);
    return det;
  } else if (m == 2) {
    det = matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0];
    // printDeterminante(det);
    return det;
  } else if (m == 3) {
    det = matriz[0][0] * matriz[1][1] * matriz[2][2] +
          matriz[0][1] * matriz[1][2] * matriz[2][0] +
          matriz[0][2] * matriz[1][0] * matriz[2][1] -
          matriz[0][2] * matriz[1][1] * matriz[2][0] -
          matriz[0][0] * matriz[1][2] * matriz[2][1] -
          matriz[0][1] * matriz[1][0] * matriz[2][2];
    // printDeterminante(det);
    return det;
  } else if (m > 3) {
    if (matriz[0][0] == 1) {
      int row = m - 1;
      int col = n - 1;
      int **matriz2=(int **)malloc(sizeof(int *)*row);
      for (int i = 0; i < row; i++) {
        matriz2[i]=(int *)malloc(sizeof(int)*col);
        for (int j = 0; j < col; j++) {
          matriz2[i][j] =
              matriz[i + 1][j + 1] - (matriz[0][j + 1] * matriz[i + 1][0]);
          // printf("%d ",matriz2[i][j]);
        }
        // printf("\n");
      }
      return determinante(row, col, matriz2);
    }

    else {
      int zeroes[m];
      for (int i = 0; i < m * 2; i++) {
        if (i < m) {
          zeroes[i] = countRowZeroes(i, n, matriz);
        } else {
          zeroes[i] = countColZeroes(i, n, matriz);
        }
      }
      int maior = zeroes[0];
      int indice = 0;
      //INDICE MENOR DO QUE A METADE DE M SIMBOLIZA O INDICE DE LINHA, E MAIOR OU IGUAL QUE A METADE DE N SIMBOLIZA O INDICE DE COLUNA
      for (int i = 1; i < m * 2; i++) {
        if (zeroes[i] > maior) {
          maior = zeroes[i];
          indice = i;
        }
      }
      // printf("indice %d\n",indice);

      if (indice < m) {
        int linha = 0;
        int coluna = 0;
        for (int i = 0; i < m; i++) {
          int **matriz2=(int **)malloc(sizeof(int *)*(m-1));

          for (int a = 0; a < n; a++) {
            matriz2[a]=(int *)malloc(sizeof(int)*(n-1));
            for (int b = 0; b < n; b++) {
              if (indice != a && i != b) {
                matriz2[linha][coluna] = matriz[a][b];
                if (coluna == n - 2) {
                  linha++;
                  coluna = 0;
                } else {
                  coluna++;
                }
              }
            }
          }
          linha = 0;
          coluna = 0;

          det += matriz[indice][i] * (pow(-1, indice + i + 2)) *
                 determinante(m - 1, n - 1, matriz2);
          // printf("det linha %d\n",det);
        }
        return det;
      } else {
        indice -= m;
        int linha = 0;
        int coluna = 0;
        for (int j = 0; j < m; j++) {
          int **matriz2=(int **)malloc(sizeof(int *)*(m-1));

          for (int a = 0; a < n; a++) {
            matriz2[a]=(int *)malloc(sizeof(int)*(n-1));
            for (int b = 0; b < n; b++) {
              if (j != a && indice != b) {
                matriz2[linha][coluna] = matriz[a][b];
                // printf("linha %d\ncoluna %d\na %d\nb
                // %d\n\n",linha,coluna,a,b);
                if (coluna == n - 2) {
                  linha++;
                  coluna = 0;
                } else {
                  coluna++;
                }
              }
            }
          }
          linha = 0;
          coluna = 0;

          det += matriz[j][indice] * (pow(-1, indice + j + 2)) *
                 determinante(m - 1, n - 1, matriz2);
          // printf("det coluna %d\n",det);
        }
        return det;
      }
    }
  }
  // return -32767;
}

void printDeterminante(int m, int n, int **matriz) {
  printf("\nO determinante é %d\n\n\n", determinante(m, n, matriz));
}

int main(void) {
  while(1){
  printf("---------------------CALCULADORA DE DETERMINANTE---------------------\n");
    printf("(Insira 404 para encerrar o código)\n");
    printf("INSIRA A ORDEM DA MATRIZ:\n");
    int m;
    scanf("%d",&m);
    getchar();
    if(m==404){
      printf("Obrigado e volte sempre :)\n");
      break;
    }
    char *values[m][m];
      printf("(Insira os números com espaços entre si para separá-los)\n");
    int spaceflag=0;
    for(int i=1;i<=m;i++){
      char *string=(char *)malloc(sizeof(char)*100);
      int spacecount=0;
      printf("INSIRA A %da LINHA:\n",i);
      fgets(string,100,stdin);
        int stringlen=strlen(string);
      for(int j=0;j<m;j++){
        char *cut_string=(char *)malloc(sizeof(char)*100);
        int flag=0;
          for(int k=0;k<stringlen;k++){
            if(string[k]=='\0'){
              break;
            }
            else if(string[k]==' '){
              char newstring[100];
              for(int l=0;l<stringlen-flag;l++){
              newstring[l]=string[l+flag+1];
                }
              string=newstring;
              spacecount++;
              break;
            }
            else{
              cut_string[flag]=string[k];
              flag++;
            }
          }
          values[i-1][j]=cut_string;
      }
        if(spacecount!=m-1){
          spaceflag=1;
          break;
        }
    }
    if(spaceflag==1){
          printf("ERRO: VOCÊ INSERIU A QUANTIDADE ERRADA DE ELEMENTOS NA LINHA\n\n\n");
          continue;
    }

  int **matriz=(int **)malloc(sizeof(int *)*m);
    for(int i=0;i<m;i++){
      matriz[i]=(int *)malloc(sizeof(int)*m);
    }
    for(int i=0;i<m;i++){
      for(int j=0;j<m;j++){
        matriz[i][j]=atoi(values[i][j]);
      }
    }
    
//   int matriz[5][5] = {
//   {1, 2, 3, -3, 1},
//   {0, 4, 0, 0, 0},
//   {0, 1, 0, 1, 1},
//   {0, -6, 6, 1, 3},
//   {0, 2, 0, -1, 1}
// };
//ESSA MATRIZ 5X5 TEM DETERMINANTE -48
    
  // printMatriz(3, 3, matriz);
  printDeterminante(m, m, matriz);
    for(int i=0;i<m;i++){
      free(matriz[i]);
    }
    free(matriz);
  }
  return 0;
}