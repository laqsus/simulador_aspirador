# include <stdio.h>
# include <stdlib.h>
# include <locale.h>
# include <time.h>
# include <conio.h>
# include <unistd.h>

int escolhe_jogo()
{
    int escolha;
    do
    {
        printf("\n\tDigite qual jogo deseja: \n\n");
        printf("\t1 - Observável: O agente tem todas as informações\n\n");
        printf("\t2 - Parcialmente Observável A: O agente só tem informações da própria sala\n");
        printf("\te se ainda existe sujeira em alguma das salas\n\n");
        printf("\t3 - Parcialmente Observável B: O agente tem informações das salas adjacentes\n\n");
        printf("\tResposta: ");
        scanf("%d", &escolha);
    }while((escolha != 1) && (escolha != 2) && (escolha != 3));

    return escolha;
}




int escolhe_modo()
{
    int escolha;
    do
    {
        printf("\n\tDigite qual modo deseja: \n\n");
        printf("\t1 - Manual\n\n");
        printf("\t2 - I.A.\n\n");
        printf("\tResposta: ");
        scanf("%d", &escolha);
    }while((escolha != 1) && (escolha != 2));

    return escolha;
}

void define_tamanho_sala(int *linhas, int *colunas) {
    printf("\n\tDigite o número de linhas da sala: ");
    scanf("%d", linhas);
    printf("\n\tDigite o número de colunas da sala: ");
    scanf("%d", colunas);
}


int salas_sujas(int max_salas)
{
    int suja;
    do
    {
        printf("\n\tQuantas salas sujas deseja (1 - %d): ", max_salas);
        scanf("%d", &suja);
    }while((suja < 1) || (suja > max_salas));

    return suja;
}




void imprimir(int **matriz, int sujeira, int *robo, int *vetor, int linhas, int colunas,int jogo, int *visitadas)
{
        int sujo=0, sujo_restante = 0, linha, coluna;

        if (jogo==1){
            for(int i = 0; i < linhas; i++)
            {
            for(int j = 0; j < colunas; j++)
                {
                    if(matriz[i][j] == *robo)
                    {
                        printf("\t%c ", 'R');
                    }
                    else
                    {
                        sujo = 0;
                        for(int k = 0; k < sujeira; k++)
                        {
                            if(matriz[i][j] == vetor[k])
                            {
                                printf("\t%c ", 'X');
                                sujo++;
                            }
                        }
                        if(sujo == 0)
                        {
                            printf("\t%c", 'O');
                        }
                    }
                }
            printf("\n\n");
            }
        }
        else{
            if(jogo==2)
            {

                for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
                for(int k = 0; k < sujeira; k++)
                        {
                            if(matriz[i][j] == vetor[k])
                            {
                                sujo_restante++;
                            }
                        }
            if (matriz[i][j] == *robo) {
                // Mostra o robô na posição atual
                printf("\t%c ", 'R');
            }
            else if (visitadas[matriz[i][j]] == 1) {

                    sujo = 0;
                        for(int k = 0; k < sujeira; k++)
                        {
                            if(matriz[i][j] == vetor[k])
                            {
                                printf("\t%c ", 'X');
                                sujo++;
                            }
                        }
                        if(sujo == 0)
                        {
                            printf("\t%c", 'O');
                        }
                }
             else {
                // Se a sala ainda não foi visitada, mostre '?'
                printf("\t%c ", '?');
            }

        }
        printf("\n\n");
         }


            printf("\tExistem %d salas sujas\n\n", sujo_restante);
            }
            else //Jogo 3
            {
                for (int i = 0; i < linhas; i++)
                {
                    for (int j = 0; j < colunas; j++)
                    {
                        if ((matriz[i][j]) == *robo)
                        {
                            linha = i;
                            coluna = j;
                        }
                    }
                }
            for(int i = 0; i < linhas; i++)
            {for(int j = 0; j < colunas; j++)
            {if(matriz[i][j]==*robo){
            printf("\t%c ", 'R');}
              else if ((i == linha - 1 && j == coluna)  ||  // Cima
                     (i == linha + 1 && j == coluna)  ||  // Baixo
                     (i == linha && j == coluna - 1)  ||  // Esquerda
                     (i == linha && j == coluna + 1)  ||  // Direita
                     (i == linha - 1 && j == coluna - 1)  ||  // Cima-Esquerda
                     (i == linha - 1 && j == coluna + 1) ||  // Cima-Direita
                     (i == linha + 1 && j == coluna - 1) ||  // Baixo-Esquerda
                     (i == linha + 1 && j == coluna + 1)) {  // Baixo-Direita)

                sujo = 0;
                for (int k = 0; k < sujeira; k++) {
                    if (matriz[i][j] == vetor[k]) {
                        printf("\t%c ", 'X'); // Sala suja
                        sujo = 1;
                        break;
                    }
                }
                if (sujo == 0) {
                    printf("\t%c ", 'O'); // Sala limpa
                }
            // Marca a sala adjacente como visitada
                visitadas[matriz[i][j]] = 1;
            } else if (visitadas[matriz[i][j]] == 1) {
                // Se a sala já foi visitada, mostra seu estado
                sujo = 0;
                for (int k = 0; k < sujeira; k++) {
                    if (matriz[i][j] == vetor[k]) {
                        printf("\t%c ", 'X'); // Sala suja
                        sujo = 1;
                        break;
                    }
                }
                if (sujo == 0) {
                    printf("\t%c ", 'O'); // Sala limpa
                }
            } else {
                // Se a sala não foi visitada e não é adjacente, mostre '?'
                printf("\t%c ", '?');
            }
        }
        printf("\n\n");
    }
            }
        }
}



void fs(int **matriz, int *robo, int *vetor, int suja, int linhas, int colunas, int *visitadas) {
    char movimento;
    int linha, coluna, vazio;

    printf("\tDigite    |w|    para movimentar o apirador\n");
    printf("\t        |a|s|d|\n");

    movimento = getch(); // Captura tecla sem "Enter"

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == *robo) {
                linha = i;
                coluna = j;
            }
        }
    }

    // Movimentos de acordo com a tecla pressionada
    if (movimento == 's' && linha != (linhas - 1)){
        *robo = matriz[linha + 1][coluna];
    } else if (movimento == 'd' && coluna != (colunas - 1)) {
        *robo = matriz[linha][coluna + 1];
    } else if (movimento == 'w' && linha != 0) {
        *robo = matriz[linha - 1][coluna];
    } else if (movimento == 'a' && coluna != 0) {
        *robo = matriz[linha][coluna - 1];
    } else if(movimento == 'f'){
        for(int i = 0; i < suja; i++)
        {
            if((vetor[i]) == (*robo))
            {
                vetor[i] = -1;
            }
        }
    }

    visitadas[matriz[linha][coluna]] = 1;
}


int fim_do_jogo(int *vetor, int suja)
{
    int igual = 0;
    for(int i = 0; i < suja; i++)
    {
        if(vetor[i] == -1)
        {
            igual++;
        }
    }
    if(igual == suja)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


// Função para o jogo manual
void jogo_manual(int **matriz, int linhas, int colunas, int suja, int max_salas,int jogo, int *robo, int *visitadas)
{
    int aleatorio, igual, fim;

    int *vetor = (int *)malloc(suja * sizeof(int));

    for(int i = 0; i < suja; i++)
        {
            do
            {
                igual = 0;
                aleatorio = (rand() % (max_salas)) + 1;
                for(int j = 0; j < suja; j++)
                {
                    if(vetor[j] == aleatorio)
                    {
                        igual++;
                    }
                }
            }while(igual != 0);
            vetor[i] = aleatorio;
        }
    system("cls");
    imprimir(matriz, suja, robo, vetor, linhas, colunas,jogo, visitadas);
    do{
        fs(matriz, robo, vetor, suja, linhas, colunas, visitadas);
        system("cls");
        imprimir(matriz, suja, robo, vetor, linhas, colunas,jogo, visitadas);
        fim = fim_do_jogo(vetor, suja);
    }while(fim != 1);

    free(vetor);
}


typedef struct no
{
    int valor;
    struct no *proximo;
}No;


void inserir_na_fila(No **fila, int num)
{
    No *aux, *novo = malloc(sizeof(No));

    if(novo)
    {
        novo -> valor = num;
        novo -> proximo = NULL;

        if(*fila == NULL)
        {
            *fila = novo;
        }
        else
        {
            aux = *fila;
            while(aux -> proximo)
            {
                aux = aux -> proximo;
            }
            aux -> proximo = novo;
        }
    }
    else
    {
        printf("\tErro ao alocar memória\n");
    }
}


No *remover_da_fila(No **fila)
{
    No *remover = NULL;

    if(*fila)
    {
        remover = *fila;
        *fila = remover -> proximo;
    }
    else
    {
        printf("\tFila vazia\n");
    }

    return remover;
}


void imprimir_fila(No *fila)
{
    printf("\t-----Início da fila-----\n");
    while(fila)
    {
        printf("%d  ", fila -> valor);
        fila = fila -> proximo;
    }
    printf("\n\t-----Fim da fila-----\n");
}

// busca em Largura Jogo Observavel
void bfs(No *fila, int **matriz, int *robo, int linhas, int colunas, No *r, int max_salas, int suja, int jogo, int *visitadas)
{
    int cima, direita, baixo, esquerda, linha, coluna, soma, aleatorio, igual, linha_robo, coluna_robo, apaga, fim, limpas_adjacentes = 1;
    int *visitadas_ia = (int *)malloc(max_salas * sizeof(int));
    for (int i = 0; i < max_salas; i++) {
        visitadas_ia[i] = 0;  // 0 significa não visitada
    }

    int *vetor_sujo = (int *)malloc(suja * sizeof(int));

    for(int i = 0; i < suja; i++)
        {
            do
            {
                igual = 0;
                aleatorio = (rand() % (max_salas)) + 1;
                for(int j = 0; j < suja; j++)
                {
                    if(vetor_sujo[j] == aleatorio)
                    {
                        igual++;
                    }
                }
            }while(igual != 0);
            vetor_sujo[i] = aleatorio;
        }
    system("cls");
    imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
    sleep(3);
    system("cls");

    inserir_na_fila(&fila, *robo);
    visitadas_ia[0] = *robo;
    do{
    r = remover_da_fila(&fila);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == (r -> valor)) {
                linha = i;
                coluna = j;
            }
        }
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == (*robo)) {
                linha_robo = i;
                coluna_robo = j;
            }
        }
    }

    for(int i = 0; i < suja; i++)
        {
            if((vetor_sujo[i]) == (r -> valor))
            {
                if(linha_robo < linha)
                {
                    while(linha_robo != linha)
                    {
                        *robo = matriz[linha_robo + 1][coluna_robo];
                        linha_robo += 1;
                        for(int j = 0; j < suja; j++)
                        {
                            if(vetor_sujo[j] == (*robo))
                            {
                                apaga = j;
                                vetor_sujo[apaga] = -1;
                            }
                        }
                        imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                        sleep(2);
                        system("cls");
                    }
                }
                else if(linha_robo > linha)
                {
                    while(linha_robo != linha)
                    {
                        *robo = matriz[linha_robo - 1][coluna_robo];
                        linha_robo -= 1;
                        for(int j=  0; j < suja; j++)
                        {
                            if(vetor_sujo[j] == (*robo))
                            {
                                apaga = j;
                                vetor_sujo[apaga] = -1;
                            }
                        }
                        imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                        sleep(2);
                        system("cls");
                    }
                }
                if(coluna_robo > coluna)
                {
                    while(coluna_robo != coluna)
                    {
                        *robo = matriz[linha_robo][coluna_robo - 1];
                        coluna_robo -= 1;
                        for(int j=  0; j < suja; j++)
                        {
                            if(vetor_sujo[j] == (*robo))
                            {
                                apaga = j;
                                vetor_sujo[apaga] = -1;
                            }
                        }
                        imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                        sleep(2);
                        system("cls");
                    }
                }
                else if(coluna_robo < coluna)
                {
                    while(coluna_robo != coluna)
                    {
                        *robo = matriz[linha_robo][coluna_robo + 1];
                        coluna_robo += 1;
                        for(int j=  0; j < suja; j++)
                        {
                            if(vetor_sujo[j] == (*robo))
                            {
                                apaga = j;
                                vetor_sujo[apaga] = -1;
                            }
                        }
                        imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                        sleep(2);
                        system("cls");
                    }
                }

                vetor_sujo[i] = -1;
            }
        }


    if (linha != 0){
        soma = 0;
        cima = matriz[linha - 1][coluna];
        for (int i = 0; i < max_salas; i++)
        {
            if(visitadas_ia[i] == cima)
            {
                soma++;
            }
        }
        if(soma == 0)
        {
            inserir_na_fila(&fila, cima);
            for (int i = 0; i < max_salas; i++)
            {
                if(visitadas_ia[i] == 0)
                {
                    visitadas_ia [i] = cima;
                    break;
                }
            }
        }
    }


    if (coluna != (colunas - 1)){
        soma = 0;
        direita = matriz[linha][coluna + 1];
        for (int i = 0; i < max_salas; i++)
        {
            if(visitadas_ia[i] == direita)
            {
                soma++;
            }
        }
        if(soma == 0)
        {
            inserir_na_fila(&fila, direita);
            for (int i = 0; i < max_salas; i++)
            {
                if(visitadas_ia[i] == 0)
                {
                    visitadas_ia [i] = direita;
                    break;
                }
            }
        }
    }


    if (linha != (linhas - 1)){
        soma = 0;
        baixo = matriz[linha + 1][coluna];
        for (int i = 0; i < max_salas; i++)
        {
            if(visitadas_ia[i] == baixo)
            {
                soma++;
            }
        }
        if(soma == 0)
        {
            inserir_na_fila(&fila, baixo);
            for (int i = 0; i < max_salas; i++)
            {
                if(visitadas_ia[i] == 0)
                {
                    visitadas_ia [i] = baixo;
                    break;
                }
            }
        }
    }


    if (coluna != 0){
        soma = 0;
        esquerda = matriz[linha][coluna - 1];
        for (int i = 0; i < max_salas; i++)
        {
            if(visitadas_ia[i] == esquerda)
            {
                soma++;
            }
        }
        if(soma == 0)
        {
            inserir_na_fila(&fila, esquerda);
            for (int i = 0; i < max_salas; i++)
            {
                if(visitadas_ia[i] == 0)
                {
                    visitadas_ia [i] = esquerda;
                    break;
                }
            }
        }
    }
    fim = fim_do_jogo(vetor_sujo, suja);

    free(r);
    }while(fim != 1);
}

// Busca em Largura Jogo Parcialmente observavel
void busca_parcial_a(int **matriz, int *robo, int linhas, int colunas, int max_salas, int suja, int jogo, int *visitadas)
{
    int igual = 0, aleatorio, meio_linha, meio_coluna, linha_robo, coluna_robo, fim;

    int *vetor_sujo = (int *)malloc(suja * sizeof(int));

    for(int i = 0; i < suja; i++)
        {
            do
            {
                igual = 0;
                aleatorio = (rand() % (max_salas)) + 1;
                for(int j = 0; j < suja; j++)
                {
                    if(vetor_sujo[j] == aleatorio)
                    {
                        igual++;
                    }
                }
            }while(igual != 0);
            vetor_sujo[i] = aleatorio;
        }

    for(int i = 0; i < suja; i++)
    {
        if(*robo == vetor_sujo[i])
        {
            vetor_sujo[i] = -1;
        }
    }

    system("cls");
    imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
    sleep(3);
    system("cls");

    meio_linha = linhas / 2;
    meio_coluna = colunas / 2;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == (*robo)) {
                linha_robo = i;
                coluna_robo = j;
            }
        }
    }

    if(((linha_robo + 1) <= meio_linha) && ((coluna_robo + 1) <= meio_coluna))
    {
        while(linha_robo != 0)
        {
            linha_robo--;
            *robo = matriz[linha_robo][coluna_robo];
            for(int j=  0; j < suja; j++)
            {
                if(vetor_sujo[j] == (*robo))
                {
                    vetor_sujo[j] = -1;
                }
            }
            imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
            sleep(2);
            system("cls");
            fim = fim_do_jogo(vetor_sujo, suja);
            if(fim == 1)
            {
                return;
            }

        }
        while(coluna_robo != 0)
        {
            coluna_robo--;
            *robo = matriz[linha_robo][coluna_robo];
            for(int j=  0; j < suja; j++)
            {
                if(vetor_sujo[j] == (*robo))
                {
                    vetor_sujo[j] = -1;
                }
            }
            imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
            sleep(2);
            system("cls");
            fim = fim_do_jogo(vetor_sujo, suja);
            if(fim == 1)
            {
                return;
            }
        }

        fim = fim_do_jogo(vetor_sujo, suja);
        while(fim != 1)
        {
            if(coluna_robo == 0)
            {
                while((coluna_robo != (colunas - 1)) && (fim != 1))
                {
                    coluna_robo++;
                    *robo = matriz[linha_robo][coluna_robo];
                    for(int j=  0; j < suja; j++)
                    {
                        if(vetor_sujo[j] == (*robo))
                        {
                            vetor_sujo[j] = -1;
                        }
                    }
                    imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                    sleep(1);
                    system("cls");
                    fim = fim_do_jogo(vetor_sujo, suja);
                }
                if(fim == 1)
                {
                    break;
                }
                linha_robo++;
                *robo = matriz[linha_robo][coluna_robo];
                for(int j=  0; j < suja; j++)
                    {
                        if(vetor_sujo[j] == (*robo))
                        {
                            vetor_sujo[j] = -1;
                        }
                    }
                imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                sleep(1);
                system("cls");
                fim = fim_do_jogo(vetor_sujo, suja);
            }

            else if(coluna_robo == (colunas - 1))
            {
                while((coluna_robo != 0) && (fim != 1))
                {
                    coluna_robo--;
                    *robo = matriz[linha_robo][coluna_robo];
                    for(int j=  0; j < suja; j++)
                    {
                        if(vetor_sujo[j] == (*robo))
                        {
                            vetor_sujo[j] = -1;
                        }
                    }
                    imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                    sleep(1);
                    system("cls");
                    fim = fim_do_jogo(vetor_sujo, suja);
                }
                if(fim == 1)
                {
                    break;
                }
                linha_robo++;
                *robo = matriz[linha_robo][coluna_robo];
                for(int j=  0; j < suja; j++)
                    {
                        if(vetor_sujo[j] == (*robo))
                        {
                            vetor_sujo[j] = -1;
                        }
                    }
                imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                sleep(1);
                system("cls");
                fim = fim_do_jogo(vetor_sujo, suja);
            }
        }

    }

    else if(((linha_robo + 1) > meio_linha) && ((coluna_robo + 1) <= meio_coluna))
    {
        while(linha_robo != (linhas - 1))
        {
            linha_robo++;
            *robo = matriz[linha_robo][coluna_robo];
            for(int j=  0; j < suja; j++)
            {
                if(vetor_sujo[j] == (*robo))
                {
                    vetor_sujo[j] = -1;
                }
            }
            imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
            sleep(2);
            system("cls");
            fim = fim_do_jogo(vetor_sujo, suja);
            if(fim == 1)
            {
                return;
            }
        }
        while(coluna_robo != 0)
        {
            coluna_robo--;
            *robo = matriz[linha_robo][coluna_robo];
            for(int j=  0; j < suja; j++)
            {
                if(vetor_sujo[j] == (*robo))
                {
                    vetor_sujo[j] = -1;
                }
            }
            imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
            sleep(2);
            system("cls");
            fim = fim_do_jogo(vetor_sujo, suja);
            if(fim == 1)
            {
                return;
            }
        }

        fim = fim_do_jogo(vetor_sujo, suja);
        while(fim != 1)
        {
            if(coluna_robo == 0)
            {
                while((coluna_robo != (colunas - 1)) && (fim != 1))
                {
                    coluna_robo++;
                    *robo = matriz[linha_robo][coluna_robo];
                    for(int j=  0; j < suja; j++)
                    {
                        if(vetor_sujo[j] == (*robo))
                        {
                            vetor_sujo[j] = -1;
                        }
                    }
                    imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                    sleep(1);
                    system("cls");
                    fim = fim_do_jogo(vetor_sujo, suja);
                }
                if(fim == 1)
                {
                    break;
                }
                linha_robo--;
                *robo = matriz[linha_robo][coluna_robo];
                for(int j=  0; j < suja; j++)
                    {
                        if(vetor_sujo[j] == (*robo))
                        {
                            vetor_sujo[j] = -1;
                        }
                    }
                imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                sleep(1);
                system("cls");
                fim = fim_do_jogo(vetor_sujo, suja);
            }

            else if(coluna_robo == (colunas - 1))
            {
                while((coluna_robo != 0) && (fim != 1))
                {
                    coluna_robo--;
                    *robo = matriz[linha_robo][coluna_robo];
                    for(int j=  0; j < suja; j++)
                    {
                        if(vetor_sujo[j] == (*robo))
                        {
                            vetor_sujo[j] = -1;
                        }
                    }
                    imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                    sleep(1);
                    system("cls");
                    fim = fim_do_jogo(vetor_sujo, suja);
                }
                if(fim == 1)
                {
                    break;
                }
                linha_robo--;
                *robo = matriz[linha_robo][coluna_robo];
                for(int j=  0; j < suja; j++)
                    {
                        if(vetor_sujo[j] == (*robo))
                        {
                            vetor_sujo[j] = -1;
                        }
                    }
                imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                sleep(1);
                system("cls");
                fim = fim_do_jogo(vetor_sujo, suja);
            }
        }

    }else if(((linha_robo + 1) <= meio_linha) && ((coluna_robo + 1) > meio_coluna))
    {
        while(linha_robo != 0)
        {
            linha_robo--;
            *robo = matriz[linha_robo][coluna_robo];
            for(int j=  0; j < suja; j++)
            {
                if(vetor_sujo[j] == (*robo))
                {
                    vetor_sujo[j] = -1;
                }
            }
            imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
            sleep(2);
            system("cls");
            fim = fim_do_jogo(vetor_sujo, suja);
            if(fim == 1)
            {
                return;
            }
        }
        while(coluna_robo != (colunas - 1))
        {
            coluna_robo++;
            *robo = matriz[linha_robo][coluna_robo];
            for(int j=  0; j < suja; j++)
            {
                if(vetor_sujo[j] == (*robo))
                {
                    vetor_sujo[j] = -1;
                }
            }
            imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
            sleep(2);
            system("cls");
            fim = fim_do_jogo(vetor_sujo, suja);
            if(fim == 1)
            {
                return;
            }
        }

        fim = fim_do_jogo(vetor_sujo, suja);
        while(fim != 1)
        {
            if(coluna_robo == 0)
            {
                while((coluna_robo != (colunas - 1)) && (fim != 1))
                {
                    coluna_robo++;
                    *robo = matriz[linha_robo][coluna_robo];
                    for(int j=  0; j < suja; j++)
                    {
                        if(vetor_sujo[j] == (*robo))
                        {
                            vetor_sujo[j] = -1;
                        }
                    }
                    imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                    sleep(1);
                    system("cls");
                    fim = fim_do_jogo(vetor_sujo, suja);
                }
                if(fim == 1)
                {
                    break;
                }
                linha_robo++;
                *robo = matriz[linha_robo][coluna_robo];
                for(int j=  0; j < suja; j++)
                    {
                        if(vetor_sujo[j] == (*robo))
                        {
                            vetor_sujo[j] = -1;
                        }
                    }
                imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                sleep(1);
                system("cls");
                fim = fim_do_jogo(vetor_sujo, suja);
            }

            else if(coluna_robo == (colunas - 1))
            {
                while((coluna_robo != 0) && (fim != 1))
                {
                    coluna_robo--;
                    *robo = matriz[linha_robo][coluna_robo];
                    for(int j=  0; j < suja; j++)
                    {
                        if(vetor_sujo[j] == (*robo))
                        {
                            vetor_sujo[j] = -1;
                        }
                    }
                    imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                    sleep(1);
                    system("cls");
                    fim = fim_do_jogo(vetor_sujo, suja);
                }
                if(fim == 1)
                {
                    break;
                }
                linha_robo++;
                *robo = matriz[linha_robo][coluna_robo];
                for(int j=  0; j < suja; j++)
                    {
                        if(vetor_sujo[j] == (*robo))
                        {
                            vetor_sujo[j] = -1;
                        }
                    }
                imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                sleep(1);
                system("cls");
                fim = fim_do_jogo(vetor_sujo, suja);
            }
        }
    }else if(((linha_robo + 1) > meio_linha) && ((coluna_robo + 1) > meio_coluna))
    {
        while(linha_robo != (linhas - 1))
        {
            linha_robo++;
            *robo = matriz[linha_robo][coluna_robo];
            for(int j=  0; j < suja; j++)
            {
                if(vetor_sujo[j] == (*robo))
                {
                    vetor_sujo[j] = -1;
                }
            }
            imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
            sleep(2);
            system("cls");
            fim = fim_do_jogo(vetor_sujo, suja);
            if(fim == 1)
            {
                return;
            }
        }
        while(coluna_robo != (colunas - 1))
        {
            coluna_robo++;
            *robo = matriz[linha_robo][coluna_robo];
            for(int j=  0; j < suja; j++)
            {
                if(vetor_sujo[j] == (*robo))
                {
                    vetor_sujo[j] = -1;
                }
            }
            imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
            sleep(2);
            system("cls");
            fim = fim_do_jogo(vetor_sujo, suja);
            if(fim == 1)
            {
                return;
            }
        }

        fim = fim_do_jogo(vetor_sujo, suja);
        while(fim != 1)
        {
            if(coluna_robo == 0)
            {
                while((coluna_robo != (colunas - 1)) && (fim != 1))
                {
                    coluna_robo++;
                    *robo = matriz[linha_robo][coluna_robo];
                    for(int j=  0; j < suja; j++)
                    {
                        if(vetor_sujo[j] == (*robo))
                        {
                            vetor_sujo[j] = -1;
                        }
                    }
                    imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                    sleep(1);
                    system("cls");
                    fim = fim_do_jogo(vetor_sujo, suja);
                }
                if(fim == 1)
                {
                    break;
                }
                linha_robo--;
                *robo = matriz[linha_robo][coluna_robo];
                for(int j=  0; j < suja; j++)
                    {
                        if(vetor_sujo[j] == (*robo))
                        {
                            vetor_sujo[j] = -1;
                        }
                    }
                imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                sleep(1);
                system("cls");
                fim = fim_do_jogo(vetor_sujo, suja);
            }

            else if(coluna_robo == (colunas - 1))
            {
                while((coluna_robo != 0) && (fim != 1))
                {
                    coluna_robo--;
                    *robo = matriz[linha_robo][coluna_robo];
                    for(int j=  0; j < suja; j++)
                    {
                        if(vetor_sujo[j] == (*robo))
                        {
                            vetor_sujo[j] = -1;
                        }
                    }
                    imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                    sleep(1);
                    system("cls");
                    fim = fim_do_jogo(vetor_sujo, suja);
                }
                if(fim == 1)
                {
                    break;
                }
                linha_robo--;
                *robo = matriz[linha_robo][coluna_robo];
                for(int j=  0; j < suja; j++)
                    {
                        if(vetor_sujo[j] == (*robo))
                        {
                            vetor_sujo[j] = -1;
                        }
                    }
                imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas,jogo, visitadas);
                sleep(1);
                system("cls");
                fim = fim_do_jogo(vetor_sujo, suja);
            }
        }
    }

}

void explorar_matriz(int **matriz, int *robo, int linhas, int colunas, int max_salas, int suja) {
    int linha_robo, coluna_robo;
    int *visitadas_ia = (int *)malloc(max_salas * sizeof(int));
    int *vetor_sujo = (int *)malloc(suja * sizeof(int));

    for (int i = 0; i < max_salas; i++) {
        visitadas_ia[i] = 0;
    }

    for (int i = 0; i < suja; i++) {
        vetor_sujo[i] = (rand() % max_salas) + 1;
    }

    while (1) {
        //Localiza a posiçao atual do
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                if (matriz[i][j] == *robo) {
                    linha_robo = i;
                    coluna_robo = j;
                    break;
                }
            }
        }

        int direcoes[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        int encontrou_sujeira_proxima = 0;

        system("cls");

        for (int d = 0; d < 4; d++) {
            int nova_linha = linha_robo + direcoes[d][0];
            int nova_coluna = coluna_robo + direcoes[d][1];

            if (nova_linha >= 0 && nova_linha < linhas && nova_coluna >= 0 && nova_coluna < colunas) {
                int proxima_pos = matriz[nova_linha][nova_coluna];
                for (int i = 0; i < suja; i++) {
                    if (vetor_sujo[i] == proxima_pos) {
                        *robo = proxima_pos;
                        vetor_sujo[i] = -1;
                        encontrou_sujeira_proxima = 1;
                        break;
                    }
                }
                if (encontrou_sujeira_proxima) break;
            }
        }

        if (encontrou_sujeira_proxima) {
            imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas, 0, visitadas_ia);
            sleep(2);
            system("cls");
            continue; // Reinicia a busca para verificar sujeiras próximas novamente
        }

        // Identifica o alvo e faz o movimento gradual
        int alvo_linha = -1, alvo_coluna = -1;
        int menor_distancia = linhas * colunas;

        for (int i = 0; i < suja; i++) {
            if (vetor_sujo[i] != -1) {
                int pos_suja = vetor_sujo[i];
                int linha_suja = (pos_suja - 1) / colunas;
                int coluna_suja = (pos_suja - 1) % colunas;
                int distancia = abs(linha_robo - linha_suja) + abs(coluna_robo - coluna_suja);

                if (distancia < menor_distancia) {
                    menor_distancia = distancia;
                    alvo_linha = linha_suja;
                    alvo_coluna = coluna_suja;
                }
            }
        }

        // Movimenta uma célula em direção ao alvo
        if (alvo_linha != -1 && alvo_coluna != -1) {
            if (linha_robo < alvo_linha) {
                linha_robo++;
            } else if (linha_robo > alvo_linha) {
                linha_robo--;
            } else if (coluna_robo < alvo_coluna) {
                coluna_robo++;
            } else if (coluna_robo > alvo_coluna) {
                coluna_robo--;
            }
            *robo = matriz[linha_robo][coluna_robo];

            // Marca a sujeira como limpa se o robô chegar lá
            for (int i = 0; i < suja; i++) {
                if (vetor_sujo[i] == *robo) {
                    vetor_sujo[i] = -1;
                    break;
                }
            }

            imprimir(matriz, suja, robo, vetor_sujo, linhas, colunas, 0, visitadas_ia);
            sleep(2);
            system("cls");
        }

        int fim = fim_do_jogo(vetor_sujo, suja);
        if (fim) break;
    }

    free(visitadas_ia);
    free(vetor_sujo);
}


int main()
{
    No *r, *fila = NULL;
    int jogo, modo, suja, linhas, colunas;
    setlocale(LC_ALL, "portuguese");
    srand(time(NULL));

    jogo = escolhe_jogo();
    modo = escolhe_modo();
    define_tamanho_sala(&linhas, &colunas);

    int max_salas = linhas * colunas;
    suja = salas_sujas(max_salas);

    // Aloca dinamicamente a matriz com o tamanho escolhido
    int *matriz = (int *)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *)malloc(colunas * sizeof(int));
    }

    // Inicializa a matriz com valores incrementais
    int contador = 1;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = contador++;
        }
    }

     // Inicializa o vetor visitadas
    int *visitadas = (int *)malloc(max_salas * sizeof(int));

// Inicializa todas as salas como não visitadas
    for (int i = 0; i < max_salas; i++) {
        visitadas[i] = 0;  // 0 significa não visitada
    }

    // Define a posição inicial do robô como um valor único
    int robo = (rand() % (max_salas - 1)) + 1;


    // Executa o jogo
    if (modo == 1) {
        jogo_manual(matriz, linhas, colunas, suja, max_salas, jogo, &robo, visitadas);  // Chama a função de jogo manual
    } else if (modo == 2) {
        if(jogo == 1)
        {
            bfs(fila, matriz, &robo, linhas, colunas, r, max_salas, suja, jogo, visitadas);
        }
        else if(jogo == 2)
        {
            busca_parcial_a(matriz, &robo, linhas, colunas, max_salas, suja, jogo, visitadas);
        }else if(jogo==3){
             explorar_matriz(matriz, &robo, linhas, colunas, max_salas, suja);
        }
    }


    // Libera a memória alocada para a matriz
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
    free(visitadas);
    free(fila);
    return 0;
}