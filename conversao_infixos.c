#include <stdio.h>
#include <stdlib.h> /*biblioteca para manipulação das pilhas*/
#include <ctype.h> /*biblioteca para verificar se é dígito ou letra*/

typedef struct NODE{
    int dado;
    struct NODE *next;
}NODE;

typedef struct STACK{
    NODE *top;
}STACK;

void inicializar_pilha(STACK *stack){
    stack -> top = NULL;
}

void empilhar(char dado, STACK *stack){
    NODE *ptr = (NODE*) malloc(sizeof(NODE)); /*alocação dinâmica da pilha*/
    
    /*teste de alocação*/
    if(ptr == NULL){
        printf("Erro de alocação.");
    }
    else{
        ptr -> dado = dado;
        ptr -> next = stack -> top;
        stack -> top = ptr;
    }
}

char desempilhar(STACK *stack){
    /*verificar se a pilha está vazia*/
    if(stack -> top == NULL){ 
        printf("Não é possível remover o elemento, a pilha está vazia.");
        return '\0';
    }
    else{
        /*temp armazena o valor que está sendo removido*/
        NODE *temp = stack -> top; 
        char valueTop = temp -> dado;
        stack -> top = stack -> top -> next; /*o ponteiro top se torna o próxima nó*/
        free(temp); /*libera a memoria do nó*/
        return valueTop;
    }
}

char topo(STACK *stack) {
    if (stack->top != NULL) {
        return stack->top->dado;
    }
    return '\0';
}

int prioridades(char operador) {
    switch (operador) {
        case '+':
        case '-':
            return 1; // Operadores de menor prioridade
        case '*':
            return 2; // Operadores de prioridade média
        case '/':
            return 2; // Operadores de prioridade média
        case '^':
            return 3; // Operador de maior prioridade
        default:
            return 0; // Retorna 0 se não for um operador válido
    }
}

void infixa_posfixa(const char *inf){ /*função que recebe a exp infixa (inf) e devolve e, posfixa*/
    STACK stack; /*declara a pilha para armazenamento dos operadores*/
    inicializar_pilha(&stack); 
    
    printf("Expressão infixa: %s\n", inf);
    printf("Expressão pós-fixa: ");
    
    for(int i = 0; inf[i] != '\0'; i++){ /*percorrerá todos os elementos até q a pilha retorne NULL*/
        char caractere = inf[i]; /*recebe o caractere correspondente a posição i*/ 
        
        /*verificar se o caractere é número ou letra*/
        if(isalnum(caractere)){
            printf("%c", caractere); /*se for alfanumérico já é impresso*/
        }
        else if (caractere == '(') { /*verifica se é um parentese de abertura e o empilha*/
            empilhar(caractere, &stack);
        }
        else if(caractere == ')'){/*verifica se é um parentese de fechamento e o desempilha até encontrar um (*/
            while ((stack.top != NULL) && (topo(&stack) != '(')){
                printf("%c", desempilhar(&stack));
            }
            
            desempilhar(&stack); // Remove o '(' da pilha
        }
        else{ /*se for um simbolo*/
            while ((stack.top != NULL) && (prioridades(topo(&stack)) >= prioridades(caractere))) {
                printf("%c", desempilhar(&stack));
            }
            empilhar(caractere, &stack); // Empilha o operador atual
        }
    }
    
    // Desempilha todos os operadores restantes na pilha
    while (stack.top != NULL) {
        printf("%c", desempilhar(&stack));
    }
}

int main()
{
    const char *expressao = "A+B*(C^D-E)^(F+G*H)-I"; // Expressão infixa de exemplo
    infixa_posfixa(expressao);// Converte e imprime a expressão pós-fixa
    return 0;
}