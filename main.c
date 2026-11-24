#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char nome[51];
    int qtd;
    double valor;
    long long int codigo;
    int estoque_minimo;
} produto;

// Menus
void pagina1();
void pagina2();
void pagina3();

// Auxiliares de arquivo e codigo
int ler_n_itens();
void salvar_n_itens(int n_itens);
produto* carregar_estoque(int *n_itens);
void salvar_estoque(produto *lista, int n_itens);
long long int gerar_codigo();

// Funcoes Pagina 1 (Estoque)
void listar_produtos();
void adicionar_produtos();
void remover_produtos();
void editar_produto();
void produto_caro();
void produto_barato();
void buscarProdutoPorNome();
void ordenarProdutosPorPreco();
void verificarEstoqueBaixo();
void totalUnidadesEstoque();
void produtosSemEstoque();

// Funcoes Pagina 2 (Entrada e Saida)
void entradaEstoque();
void saidaEstoque();
void registrarMovimentacao(long long int codigo, char *tipo, int quantidade);

// Funcoes Pagina 3 (Historico)
void consultarHistorico();
void relatorioEntradas();
void relatorioSaidas();
void limparHistorico();

int main() {
    srand(time(NULL));
    system("cls");

    FILE *fptr = fopen("n_itens.txt", "r");
    if (fptr == NULL) {
        fptr = fopen("n_itens.txt", "w");
        if (fptr != NULL) {
            fprintf(fptr, "%d", 0);
            fclose(fptr);
        }
    } else {
        fclose(fptr);
    }

    int n = -1;

    while (n != 0) {
        printf("\n\nPAGINA INICIAL\n\n\n");
        printf("0 ---> FINALIZAR PROGRAMA\n");
        printf("1 ---> ESTOQUE\n");
        printf("2 ---> ENTRADA/SAIDA DE PRODUTOS\n");
        printf("3 ---> HISTORICO\n\n\n");
        printf("Selecione a opcao: ");
        scanf("%d%*c", &n);

        switch (n) {
            case 0:
                printf("\n\n---FINALIZANDO PROGRAMA---\n\n\n");
                break;
            case 1:
                pagina1();
                break;
            case 2:
                pagina2();
                break;
            case 3:
                pagina3();
                break;
            default:
                printf("\nOPCAO INVALIDA\n\n");
                break;
        }
    }
    return 0;
}

// ==========================================
// FUNCOES AUXILIARES DE ARQUIVO
// ==========================================

int ler_n_itens() {
    int n = 0;
    FILE *fptr = fopen("n_itens.txt", "r");
    if (fptr != NULL) {
        fscanf(fptr, "%d", &n);
        fclose(fptr);
    }
    return n;
}

void salvar_n_itens(int n_itens) {
    FILE *fptr = fopen("n_itens.txt", "w");
    if (fptr != NULL) {
        fprintf(fptr, "%d\n", n_itens);
        fclose(fptr);
    }
}


produto* carregar_estoque(int *n_itens) {
    *n_itens = ler_n_itens();
    if (*n_itens <= 0) return NULL;

    FILE *fptr = fopen("estoque.txt", "r");
    if (fptr == NULL) {
        *n_itens = 0;
        return NULL;
    }

    produto *lista = (produto *)malloc(sizeof(produto) * (*n_itens));
    if (lista == NULL) {
        fclose(fptr);
        *n_itens = 0;
        return NULL;
    }

    int lidos = 0;
    char linha[256];

    for (int i = 0; i < *n_itens; i++) {
        if (fgets(linha, sizeof(linha), fptr) == NULL)
            break;

        int campos = sscanf(linha, "%50s %d %lf %lld %d",
            lista[i].nome,
            &lista[i].qtd,
            &lista[i].valor,
            &lista[i].codigo,
            &lista[i].estoque_minimo);

        if (campos == 4) {
            lista[i].estoque_minimo = 4;
        }
        else if (campos != 5) {
            printf("ERRO AO LER PRODUTO NO ARQUIVO!\n");
            break;
        }

        lidos++;
    }

    fclose(fptr);
    *n_itens = lidos;

    if (lidos == 0) {
        free(lista);
        return NULL;
    }

    return lista;
}

void salvar_estoque(produto *lista, int n_itens) {
    FILE *fptr = fopen("estoque.txt", "w");
    if (fptr == NULL) {
        printf("Erro ao abrir estoque.txt para salvar!\n");
        return;
    }
    for (int i = 0; i < n_itens; i++) {
        fprintf(fptr, "%s %d %lf %lld %d\n",
        lista[i].nome,
        lista[i].qtd,
        lista[i].valor,
        lista[i].codigo,
        lista[i].estoque_minimo);
    }
    fclose(fptr);
}

long long int gerar_codigo() {
    long long int x = 1;
    while (x < 1000000) {
        x *= (rand() + 1); // +1 evita multiplicacao por zero caso rand() retorne 0
    }
    return x;
}

// ==========================================
// PAGINA 1: GERENCIAMENTO DE ESTOQUE
// ==========================================

void pagina1() {
    int p = -1;
    system("cls");

    while (p != 0) {
        printf("--- ESTOQUE ---\n");
        listar_produtos();
        printf("0  ---> VOLTAR\n");
        printf("1  ---> ADICIONAR PRODUTO\n");
        printf("2  ---> EDITAR PRODUTO\n");
        printf("3  ---> REMOVER PRODUTO\n");
        printf("4  ---> PRODUTO MAIS CARO\n");
        printf("5  ---> PRODUTO MAIS BARATO\n");
        printf("6  ---> BUSCAR PRODUTO POR NOME\n");
        printf("7  ---> ORDENAR PRODUTOS POR PRECO\n");
        printf("8  ---> VERIFICAR ESTOQUE BAIXO\n");
        printf("9  ---> TOTAL DE UNIDADES EM ESTOQUE\n");
        printf("10 ---> PRODUTOS SEM ESTOQUE\n\n");
        printf("Opcao: ");
        scanf("%d", &p);

        switch (p) {
            case 0:
                system("cls");
                break;
            case 1:
                system("cls");
                adicionar_produtos();
                system("cls");
                break;
            case 2:
                editar_produto();
                break;
            case 3:
                remover_produtos();
                break;
            case 4:
                system("cls");
                produto_caro();
                break;
            case 5:
                system("cls");
                produto_barato();
                break;
            case 6:
                system("cls");
                buscarProdutoPorNome();
                break;
            case 7:
                system("cls");
                ordenarProdutosPorPreco();
                break;
            case 8:
                system("cls");
                verificarEstoqueBaixo();
                break;
            case 9:
                system("cls");
                totalUnidadesEstoque();
                break;
            case 10:
                system("cls");
                produtosSemEstoque();
                break;
            default:
                system("cls");
                printf("OPCAO INVALIDA\n\n");
                break;
        }
    }
}

void listar_produtos() {
    int n_itens = 0;
    produto *lista = carregar_estoque(&n_itens);
    produto produto_ref;

    printf("\nLISTA (%d itens):\n", n_itens);
    if (lista == NULL || n_itens == 0) {
        printf("Estoque vazio.\n\n");
        free(lista);
        return;
    }

    for (int j = 0; j < n_itens; j++) {
        for (int z = j; z > 0; z--) {
            if (strcmp(lista[z].nome, lista[z - 1].nome) < 0) {
                produto_ref = lista[z];
                lista[z] = lista[z - 1];
                lista[z - 1] = produto_ref;
            }
        }
    }

    for (int z = 0; z < n_itens; z++) {
       printf("%s | Qtd: %d | Min: %d | R$ %.2lf | Cod: %lld\n",
        lista[z].nome,
        lista[z].qtd,
        lista[z].estoque_minimo,
        lista[z].valor,
        lista[z].codigo);
    }
    printf("\n");
    free(lista);
}

void adicionar_produtos() {
    int i, z, n_itens = ler_n_itens();
    produto *lista = (produto *)malloc(sizeof(produto));
    FILE *fptr = fopen("estoque.txt", "a");

    if (fptr == NULL || lista == NULL) {
        printf("Erro ao abrir arquivo ou alocar memoria.\n");
        free(lista);
        if (fptr != NULL) fclose(fptr);
        return;
    }

    printf("\nDIGITE 0 NO NOME QUANDO ACABAR\n");
    for (i = 0; ; i++) {
        if (i > 0) {

            produto *temp = (produto *)realloc(lista, (i + 1) * sizeof(produto));

            if (temp == NULL) {
                printf("\nERRO AO REALOCAR MEMORIA\n");
                free(lista);
                fclose(fptr);
                return;
            }

            lista = temp;
        }
        printf("\nNOME DO PRODUTO (sem espacos/max. 50 caracteres): ");
        scanf("%50s", lista[i].nome);
        if (strcmp(lista[i].nome, "0") == 0)
            break;
        
        do {
        printf("QUANTIDADE: ");

        if (scanf("%d", &lista[i].qtd) != 1) {
            printf("ERRO: DIGITE UM NUMERO INTEIRO!\n");
            free(lista);
            fclose(fptr);
            return;
        }

        if (lista[i].qtd < 0) {
            printf("ERRO: QUANTIDADE NAO PODE SER NEGATIVA!\n");
        }

    } while (lista[i].qtd < 0);


    do {
        printf("VALOR DO PRODUTO: ");

        if (scanf("%lf", &lista[i].valor) != 1) {
            printf("ERRO: DIGITE UM NUMERO VALIDO!\n");
            free(lista);
            fclose(fptr);
            return;
        }

        if (!(lista[i].valor >= 0)) {
            printf("ERRO: VALOR INVALIDO!\n");
        }

    } while (!(lista[i].valor >= 0));

    do {
        printf("ESTOQUE MINIMO: ");

        if (scanf("%d", &lista[i].estoque_minimo) != 1) {
            printf("ERRO: DIGITE UM NUMERO INTEIRO!\n");
            free(lista);
            fclose(fptr);
            return;
        }

        if (lista[i].estoque_minimo < 0) {
            printf("ERRO: ESTOQUE MINIMO NAO PODE SER NEGATIVO!\n");
        }

    } while (lista[i].estoque_minimo < 0);
        }

    n_itens += i;
    for (z = 0; z < i; z++) {
        lista[z].codigo = gerar_codigo();
        fprintf(fptr, "%s %d %lf %lld %d\n",lista[z].nome, lista[z].qtd,lista[z].valor, lista[z].codigo,lista[z].estoque_minimo);
        
    }
    fclose(fptr);
    salvar_n_itens(n_itens);
    free(lista);
}

void remover_produtos() {
    int n_itens = 0, verdade = 0;
    produto *temp = carregar_estoque(&n_itens);

    if (temp == NULL || n_itens == 0) {
        system("cls");
        printf("\nESTOQUE VAZIO\n\n");
        free(temp);
        return;
    }

    long long int codigo;
    printf("CODIGO DO PRODUTO: ");
    scanf("%lld", &codigo);

    int novo_total = 0;
    for (int i = 0; i < n_itens; i++) {
        if (temp[i].codigo == codigo) {
            verdade = 1;
        } else {
            temp[novo_total] = temp[i];
            novo_total++;
        }
    }

    system("cls");
    if (verdade == 0) {
        printf("\nITEM NAO ENCONTRADO\n\n");
    } else {
        salvar_estoque(temp, novo_total);
        salvar_n_itens(novo_total);
        printf("\nITEM REMOVIDO\n\n");
    }
    free(temp);
}

void editar_produto() {
    double novo_valor;
    int i, n_itens, vdd = 0, save = -1;
    FILE *fptr = fopen("n_itens.txt", "r");

    if (fptr == NULL) {
        printf("\nERRO AO ABRIR n_itens.txt\n");
        return;
    }

    if (fscanf(fptr, "%d", &n_itens) != 1 || n_itens <= 0) {
        printf("\nQUANTIDADE DE PRODUTOS INVALIDA\n");
        fclose(fptr);
        return;
    }

    fclose(fptr);
    produto ex[n_itens];
    long long int codigo;
    printf("CODIGO DO PRODUTO: ");
    scanf("%lld", &codigo);
    fptr = fopen("estoque.txt", "r");

    if (fptr == NULL) {
        printf("\nERRO AO ABRIR estoque.txt\n");
        return;
    }
    
    char linha[256];
    int lidos = 0;

    for(i = 0; i < n_itens; i++){
        if(fgets(linha, sizeof(linha), fptr) == NULL)
            break;

        int campos = sscanf(linha, "%50s %d %lf %lld %d",
            ex[i].nome,
            &ex[i].qtd,
            &ex[i].valor,
            &ex[i].codigo,
            &ex[i].estoque_minimo);

        if(campos == 4){
            ex[i].estoque_minimo = 4;
        }
        else if(campos != 5){
            break;
        }

        lidos++;

        if(ex[i].codigo == codigo){
            save = i;
        }
    }

    fclose(fptr);

    if(lidos != n_itens){
        printf("\nERRO AO CARREGAR TODOS OS PRODUTOS!\n");
        return;
    }

    if (save == -1) {
        printf("\nITEM NAO ENCONTRADO\n");
        return;
    }

    printf("\nNOME: %s\nVALOR: R$ %.2lf\nQUANTIDADE: %d", ex[save].nome, ex[save].valor, ex[save].qtd);
    printf("\n\nNOVO VALOR: ");
    scanf("%lf", &novo_valor);
    for(i = 0; i < n_itens; i++){
        if(ex[i].codigo == codigo){
            vdd = 1;
            ex[i].valor = novo_valor;
        }
    }
    if(vdd == 0){
        printf("\nITEM NAO ENCONTRADO\n");
        return;
    }
    fptr = fopen("estoque.txt", "w");

    if (fptr == NULL) {
        printf("\nERRO AO ABRIR estoque.txt PARA ESCRITA\n");
        return;
    }

    for(i = 0; i < n_itens; i++){
        fprintf(fptr, "%s %d %lf %lld %d\n",
        ex[i].nome,
        ex[i].qtd,
        ex[i].valor,
        ex[i].codigo,
        ex[i].estoque_minimo);
    }
    fclose(fptr);    

    printf("\nVALOR ATUALIZADO\n\n");

}

void produto_caro() {
    int n_itens = 0;
    produto *lista = carregar_estoque(&n_itens);
    if (lista == NULL || n_itens == 0) {
        printf("Estoque vazio.\n\n");
        free(lista);
        return;
    }

    int idx = 0;
    for (int i = 1; i < n_itens; i++) {
        if (lista[i].valor > lista[idx].valor) {
            idx = i;
        }
    }
    printf("O PRODUTO MAIS CARO E: %s (R$ %.2lf)\n\n", lista[idx].nome, lista[idx].valor);
    free(lista);
}

void produto_barato() {
    int n_itens = 0;
    produto *lista = carregar_estoque(&n_itens);
    if (lista == NULL || n_itens == 0) {
        printf("Estoque vazio.\n\n");
        free(lista);
        return;
    }

    int idx = 0;
    for (int i = 1; i < n_itens; i++) {
        if (lista[i].valor < lista[idx].valor) {
            idx = i;
        }
    }
    printf("O PRODUTO MAIS BARATO E: %s (R$ %.2lf)\n\n", lista[idx].nome, lista[idx].valor);
    free(lista);
}

void buscarProdutoPorNome() {
    int n_itens = 0, encontrou = 0;
    produto *produtos = carregar_estoque(&n_itens);
    if (produtos == NULL || n_itens == 0) {
        printf("Estoque vazio!\n\n");
        free(produtos);
        return;
    }

    char nome[51];
    printf("Digite o nome exato do produto: ");
    scanf("%50s", nome);
    printf("\n");

    for (int i = 0; i < n_itens; i++) {
        if (strcmp(produtos[i].nome, nome) == 0) {
            printf("Codigo: %lld\n", produtos[i].codigo);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Quantidade: %d\n", produtos[i].qtd);
            printf("Estoque minimo: %d\n", produtos[i].estoque_minimo);
            printf("Preco: R$ %.2lf\n", produtos[i].valor);
            printf("-------------------------\n");
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Produto nao encontrado!\n");
    }
    printf("\n");
    free(produtos);
}

void ordenarProdutosPorPreco() {
    int n_itens = 0;
    produto *produtos = carregar_estoque(&n_itens);
    if (produtos == NULL || n_itens == 0) {
        printf("Estoque vazio!\n\n");
        free(produtos);
        return;
    }

    produto guarda;
    for (int i = 0; i < n_itens - 1; i++) {
        for (int j = 0; j < n_itens - i - 1; j++) {
            if (produtos[j].valor > produtos[j + 1].valor) {
                guarda = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = guarda;
            }
        }
    }

    printf("--- PRODUTOS ORDENADOS POR PRECO (CRESCENTE) ---\n");
    for (int i = 0; i < n_itens; i++) {
        printf("R$ %.2lf | %s | Qtd: %d | Cod: %lld\n", produtos[i].valor, produtos[i].nome, produtos[i].qtd, produtos[i].codigo);
    }
    printf("\n");
    free(produtos);
}

void verificarEstoqueBaixo() {
    int n_itens = 0, encontrou = 0;
    produto *produtos = carregar_estoque(&n_itens);
    if (produtos == NULL || n_itens == 0) {
        printf("Estoque vazio!\n\n");
        free(produtos);
        return;
    }

    printf("--- PRODUTOS COM ESTOQUE BAIXO ---\n");
    for (int i = 0; i < n_itens; i++) {
        if (produtos[i].qtd <= produtos[i].estoque_minimo) {
            printf("Codigo: %lld\n", produtos[i].codigo);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Quantidade: %d\n", produtos[i].qtd);
            printf("Estoque minimo: %d\n", produtos[i].estoque_minimo);
            printf("-------------------------\n");
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum produto com estoque baixo!\n");
    }
    printf("\n");
    free(produtos);
}

void totalUnidadesEstoque() {
    int n_itens = 0, total = 0;
    produto *produtos = carregar_estoque(&n_itens);
    if (produtos != NULL) {
        for (int i = 0; i < n_itens; i++) {
            total += produtos[i].qtd;
        }
        free(produtos);
    }
    printf("Total de unidades em estoque: %d\n\n", total);
}

void produtosSemEstoque() {
    int n_itens = 0, encontrou = 0;
    produto *produtos = carregar_estoque(&n_itens);
    if (produtos == NULL || n_itens == 0) {
        printf("Estoque vazio!\n\n");
        free(produtos);
        return;
    }

    printf("--- PRODUTOS SEM ESTOQUE ---\n");
    for (int i = 0; i < n_itens; i++) {
        if (produtos[i].qtd == 0) {
            printf("Codigo: %lld\n", produtos[i].codigo);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Preco: R$ %.2lf\n", produtos[i].valor);
            printf("-------------------------\n");
            encontrou = 1;
        }
    }
    if (encontrou == 0) {
        printf("Nenhum produto sem estoque!\n");
    }
    printf("\n");
    free(produtos);
}

// ==========================================
// PAGINA 2: ENTRADA E SAIDA DE PRODUTOS
// ==========================================

void pagina2() {
    int p = -1;
    system("cls");

    while (p != 0) {
        printf("--- ENTRADA / SAIDA DE PRODUTOS ---\n\n");
        printf("0 ---> VOLTAR\n");
        printf("1 ---> REGISTRAR ENTRADA DE ESTOQUE\n");
        printf("2 ---> REGISTRAR SAIDA DE ESTOQUE\n\n");
        printf("Opcao: ");
        scanf("%d", &p);

        switch (p) {
            case 0:
                system("cls");
                break;
            case 1:
                system("cls");
                entradaEstoque();
                break;
            case 2:
                system("cls");
                saidaEstoque();
                break;
            default:
                system("cls");
                printf("OPCAO INVALIDA\n\n");
                break;
        }
    }
}

void entradaEstoque() {
    int n_itens = 0, quantidade, encontrou = 0;
    long long int codigo;
    produto *produtos = carregar_estoque(&n_itens);

    if (produtos == NULL || n_itens == 0) {
        printf("Estoque vazio! Cadastre produtos primeiro.\n\n");
        free(produtos);
        return;
    }

    printf("Digite o codigo do produto: ");
    scanf("%lld", &codigo);

    for (int i = 0; i < n_itens; i++) {
        if (produtos[i].codigo == codigo) {
            encontrou = 1;
            printf("Produto selecionado: %s (Qtd atual: %d)\n", produtos[i].nome, produtos[i].qtd);
            printf("Digite a quantidade de entrada: ");
            scanf("%d", &quantidade);

            if (quantidade > 0) {
                produtos[i].qtd += quantidade;
                salvar_estoque(produtos, n_itens);
                registrarMovimentacao(codigo, "ENTRADA", quantidade);

                printf("\nEstoque atualizado com sucesso!\n");
                printf("Nova quantidade: %d\n\n", produtos[i].qtd);
            } else {
                printf("\nQuantidade invalida!\n\n");
            }
            break;
        }
    }
    if (encontrou == 0) {
        printf("\nProduto nao encontrado!\n\n");
    }
    free(produtos);
}

void saidaEstoque() {
    int n_itens = 0, quantidade, encontrou = 0;
    long long int codigo;
    produto *produtos = carregar_estoque(&n_itens);

    if (produtos == NULL || n_itens == 0) {
        printf("Estoque vazio!\n\n");
        free(produtos);
        return;
    }

    printf("Digite o codigo do produto: ");
    scanf("%lld", &codigo);

    for (int i = 0; i < n_itens; i++) {
        if (produtos[i].codigo == codigo) {
            encontrou = 1;
            printf("Produto selecionado: %s (Qtd atual: %d)\n", produtos[i].nome, produtos[i].qtd);
            printf("Digite a quantidade de saida: ");
            scanf("%d", &quantidade);

            if (quantidade <= 0) {
                printf("\nQuantidade invalida!\n\n");
            } else if (produtos[i].qtd >= quantidade) {
                produtos[i].qtd -= quantidade;
                salvar_estoque(produtos, n_itens);
                registrarMovimentacao(codigo, "SAIDA", quantidade);

                printf("\nSaida realizada com sucesso!\n");
                printf("Nova quantidade: %d\n\n", produtos[i].qtd);
            } else {
                printf("\nEstoque insuficiente!\n\n");
            }
            break;
        }
    }
    if (encontrou == 0) {
        printf("\nProduto nao encontrado!\n\n");
    }
    free(produtos);
}

void registrarMovimentacao(long long int codigo, char *tipo, int quantidade) {
    FILE *arquivo = fopen("movimentacoes.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de movimentacoes!\n");
        return;
    }
    fprintf(arquivo, "%lld %s %d\n", codigo, tipo, quantidade);
    fclose(arquivo);
}

// ==========================================
// PAGINA 3: HISTORICO DE MOVIMENTACOES
// ==========================================

void pagina3() {
    int p = -1;
    system("cls");

    while (p != 0) {
        printf("--- HISTORICO DE MOVIMENTACOES ---\n\n");
        printf("0 ---> VOLTAR\n");
        printf("1 ---> CONSULTAR HISTORICO COMPLETO\n");
        printf("2 ---> RELATORIO DE ENTRADAS\n");
        printf("3 ---> RELATORIO DE SAIDAS\n");
        printf("4 ---> LIMPAR HISTORICO\n\n");
        printf("Opcao: ");
        scanf("%d", &p);

        switch (p) {
            case 0:
                system("cls");
                break;
            case 1:
                system("cls");
                consultarHistorico();
                break;
            case 2:
                system("cls");
                relatorioEntradas();
                break;
            case 3:
                system("cls");
                relatorioSaidas();
                break;
            case 4:
                system("cls");
                limparHistorico();
                break;
            default:
                system("cls");
                printf("OPCAO INVALIDA\n\n");
                break;
        }
    }
}

void consultarHistorico() {
    FILE *arquivo = fopen("movimentacoes.txt", "r");
    long long int codigo;
    int quantidade, encontrou = 0;
    char tipo[20];

    if (arquivo == NULL) {
        printf("Nenhum historico encontrado!\n\n");
        return;
    }

    printf("--- HISTORICO COMPLETO ---\n");
    while (fscanf(arquivo, "%lld %19s %d", &codigo, tipo, &quantidade) == 3) {
        printf("Codigo: %lld | Tipo: %s | Quantidade: %d\n", codigo, tipo, quantidade);
        printf("--------------------------------------------------\n");
        encontrou = 1;
    }

    if (encontrou == 0) {
        printf("Nenhuma movimentacao registrada!\n");
    }
    printf("\n");
    fclose(arquivo);
}

void relatorioEntradas() {
    FILE *arquivo = fopen("movimentacoes.txt", "r");
    long long int codigo;
    int quantidade, encontrou = 0;
    char tipo[20];

    if (arquivo == NULL) {
        printf("Nenhum historico encontrado!\n\n");
        return;
    }

    printf("--- RELATORIO DE ENTRADAS ---\n");
    while (fscanf(arquivo, "%lld %19s %d", &codigo, tipo, &quantidade) == 3) {
        if (strcmp(tipo, "ENTRADA") == 0) {
            printf("Codigo: %lld | Quantidade: %d\n", codigo, quantidade);
            printf("---------------------------------\n");
            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        printf("Nenhuma entrada registrada!\n");
    }
    printf("\n");
    fclose(arquivo);
}

void relatorioSaidas() {
    FILE *arquivo = fopen("movimentacoes.txt", "r");
    long long int codigo;
    int quantidade, encontrou = 0;
    char tipo[20];

    if (arquivo == NULL) {
        printf("Nenhum historico encontrado!\n\n");
        return;
    }

    printf("--- RELATORIO DE SAIDAS ---\n");
    while (fscanf(arquivo, "%lld %19s %d", &codigo, tipo, &quantidade) == 3) {
        if (strcmp(tipo, "SAIDA") == 0) {
            printf("Codigo: %lld | Quantidade: %d\n", codigo, quantidade);
            printf("---------------------------------\n");
            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        printf("Nenhuma saida registrada!\n");
    }
    printf("\n");
    fclose(arquivo);
}

void limparHistorico() {
    char resposta;
    printf("Deseja realmente limpar o historico? (S/N): ");
    scanf(" %c", &resposta);

    if (resposta == 'S' || resposta == 's') {
        FILE *arquivo = fopen("movimentacoes.txt", "w");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo!\n\n");
            return;
        }
        fclose(arquivo);
        printf("Historico apagado com sucesso!\n\n");
    } else {
        printf("Operacao cancelada!\n\n");
    }
}
