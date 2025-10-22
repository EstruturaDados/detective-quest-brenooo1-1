/*
 mansao_explorer.c

 Programa em C: constrói dinamicamente uma árvore binária de cômodos (alocação com malloc)
 Permite explorar a mansão interativamente (esquerda/direita) e mostra os cômodos visitados
 até alcançar um nó-folha (fim do caminho).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME 128

typedef struct Node {
    char *name;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(const char *name) {
    Node *n = (Node*)malloc(sizeof(Node));
    if (!n) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    if (name) {
        n->name = strdup(name);
        if (!n->name) {
            perror("strdup");
            exit(EXIT_FAILURE);
        }
    } else {
        n->name = NULL;
    }
    n->left = n->right = NULL;
    return n;
}

void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root->name);
    free(root);
}

void strip_newline(char *s) {
    size_t len = strlen(s);
    if (len == 0) return;
    if (s[len-1] == '\n') s[len-1] = '\0';
}

void read_line(char *buf, size_t size) {
    if (fgets(buf, (int)size, stdin) == NULL) {
        buf[0] = '\0';
        return;
    }
    strip_newline(buf);
}

Node *build_sample_tree(void) {
    Node *entrada = create_node("Entrada");
    Node *salavao = create_node("Sala de Estar");
    Node *cozinha = create_node("Cozinha");
    Node *biblioteca = create_node("Biblioteca");
    Node *jardim = create_node("Jardim");
    Node *sotao = create_node("Sotao");
    Node *quarto = create_node("Quarto Principal");

    entrada->left = salavao;
    entrada->right = cozinha;

    salavao->left = biblioteca;
    salavao->right = jardim;

    cozinha->left = sotao;
    cozinha->right = quarto;

    return entrada;
}

Node *build_manual_subtree(int depth) {
    char buf[MAX_NAME];
    for(;;) {
        printf("Digite o nome do cômodo (ou ENTER para nenhum nó nesta posição): ");
        read_line(buf, sizeof(buf));
        if (strlen(buf) == 0) return NULL;
        break;
    }

    Node *root = create_node(buf);

    printf("Criar cômodo à esquerda de '%s'? (s/n): ", root->name);
    read_line(buf, sizeof(buf));
    if (strlen(buf) > 0 && (buf[0]=='s' || buf[0]=='S')) {
        root->left = build_manual_subtree(depth+1);
    }

    printf("Criar cômodo à direita de '%s'? (s/n): ", root->name);
    read_line(buf, sizeof(buf));
    if (strlen(buf) > 0 && (buf[0]=='s' || buf[0]=='S')) {
        root->right = build_manual_subtree(depth+1);
    }

    return root;
}

void explore(Node *root) {
    if (!root) {
        printf("Arvore vazia. Nada para explorar.\n");
        return;
    }

    Node *cur = root;
    char buf[16];

    printf("\n--- Exploração da mansão iniciada ---\n");
    while (cur) {
        printf("Você está em: %s\n", cur->name ? cur->name : "(sem nome)");

        if (!cur->left && !cur->right) {
            printf("\nVocê alcançou um cômodo-folha. Fim do caminho.\n");
            break;
        }

        printf("Opções disponíveis:");
        if (cur->left) printf(" [l] Ir para a esquerda -> %s", cur->left->name);
        if (cur->right) printf(" [r] Ir para a direita -> %s", cur->right->name);
        printf(" [q] Sair\n");

        printf("Escolha (l/r/q): ");
        read_line(buf, sizeof(buf));
        if (strlen(buf) == 0) {
            printf("Entrada vazia. Tente novamente.\n");
            continue;
        }
        char c = tolower((unsigned char)buf[0]);
        if (c == 'q') {
            printf("Saindo da exploração...\n");
            break;
        } else if (c == 'l') {
            if (cur->left) cur = cur->left;
            else printf("Não existe caminho à esquerda. Tente outra opção.\n");
        } else if (c == 'r') {
            if (cur->right) cur = cur->right;
            else printf("Não existe caminho à direita. Tente outra opção.\n");
        } else {
            printf("Opção inválida. Use 'l', 'r' ou 'q'.\n");
        }
    }
    printf("--- Exploração finalizada ---\n\n");
}

int main(void) {
    char buf[8];
    Node *root = NULL;

    printf("Construtor de mansão (árvore binária de cômodos)\n");
    printf("Deseja construir a árvore manualmente? (s/n) [n = árvore de exemplo]: ");
    read_line(buf, sizeof(buf));

    if (strlen(buf) > 0 && (buf[0]=='s' || buf[0]=='S')) {
        printf("\nIniciando construção manual da árvore. Para não criar um nó, pressione ENTER quando solicitado para o nome.\n");
        root = build_manual_subtree(0);
    } else {
        root = build_sample_tree();
        printf("Árvore de exemplo criada.\n");
    }

    explore(root);

    free_tree(root);
    return 0;
}


# Explorador de Mansão em C 🏰

Este projeto é um **programa interativo em C** que constrói dinamicamente uma **árvore binária** representando os cômodos de uma mansão. O jogador pode explorar os cômodos escolhendo caminhos à **esquerda** ou **direita**, até alcançar um **nó-folha**, que representa o fim do caminho.

---

## 🧩 Funcionalidades

- Construção dinâmica da árvore de cômodos (com `malloc`).
- Modo **automático**, com uma árvore de exemplo predefinida.
- Modo **manual**, permitindo que o usuário crie os cômodos e conexões interativamente.
- Exploração interativa: escolha esquerda (`l`), direita (`r`) ou sair (`q`).
- Exibição dos cômodos visitados até o fim do caminho.
- Liberação automática de toda a memória alocada.

---

## 🧱 Estrutura da Árvore

Cada cômodo é representado por um **nó**:

```c
struct Node {
    char *name;
    struct Node *left;
    struct Node *right;
};
```

A mansão é uma **árvore binária**, onde:
- `left` representa o caminho à esquerda;
- `right` representa o caminho à direita.

---

## 🚀 Como Compilar e Executar

1. Compile o programa com o GCC:
   ```bash
   gcc -std=c11 -Wall -Wextra -o mansao mansao_explorer.c
   ```

2. Execute:
   ```bash
   ./mansao
   ```

3. Escolha se deseja construir a mansão manualmente (`s`) ou usar a árvore de exemplo (`n`).

4. Explore a mansão interativamente:
   ```
   Escolha (l/r/q):
   ```

---

## 🧭 Exemplo de Execução

```
Construtor de mansão (árvore binária de cômodos)
Deseja construir a árvore manualmente? (s/n) [n = árvore de exemplo]: n
Árvore de exemplo criada.

--- Exploração da mansão iniciada ---
Você está em: Entrada
Opções disponíveis: [l] Ir para a esquerda -> Sala de Estar [r] Ir para a direita -> Cozinha [q] Sair
Escolha (l/r/q): l

Você está em: Sala de Estar
Opções disponíveis: [l] Ir para a esquerda -> Biblioteca [r] Ir para a direita -> Jardim [q] Sair
Escolha (l/r/q): r

Você está em: Jardim
Você alcançou um cômodo-folha. Fim do caminho.
--- Exploração finalizada ---
```

---

## 🧰 Estrutura do Projeto

```
📂 mansao_explorer
├── mansao_explorer.c   # Código-fonte principal
└── README.md            # Documentação do projeto
```

---

## 🖥️ Subindo no GitHub

1. Crie um repositório no GitHub.
2. No terminal, execute:
   ```bash
   git init
   git add mansao_explorer.c README.md
   git commit -m "Adicionar explorador de mansão em C"
   git branch -M main
   git remote add origin https://github.com/<seu-usuario>/<nome-do-repositorio>.git
   git push -u origin main
   ```

---

## 📜 Licença

Este projeto é livre para uso e modificação, desde que mantidos os créditos do autor original.

---

**Autor:** Breno Anselmo 👷‍♂️  
**Linguagem:** C (C11)  
**Descrição:** Projeto didático para prática de alocação dinâmica e estruturas de dados.
