#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void criptografar(const char *chave, const char *texto) {
    int tam_chave = strlen(chave);
    int tam_texto = strlen(texto);
    char texto_cript[tam_texto + 1];

    for (int i = 0; i < tam_texto; i++) {
        int indice_chave = i % tam_chave;
        texto_cript[i] = texto[i] + chave[indice_chave];
    }
    texto_cript[tam_texto] = '\0';
    FILE *arquivo = fopen("criptografado.txt", "w");
    if (arquivo == NULL) {
        printf("\nERRO AO CRIAR ARQUIVO!!!!\n\n");
        return;
    }
    fprintf(arquivo, "%s", texto_cript);
    fclose(arquivo);
}

void descriptografar(const char *chave) {
    char texto_decript[1000];
    int pos_texto = 0;

    FILE *arquivo = fopen("criptografado.txt", "r");
    if (arquivo == NULL) {
        printf("\nERRO AO ABRIR ARQUIVO!!!!\n\n");
        return;
    }

    char caractere;
    int indice_chave = 0;
    while ((caractere = fgetc(arquivo)) != EOF) {
        texto_decript[pos_texto] = caractere - chave[indice_chave];
        indice_chave = (indice_chave + 1) % strlen(chave);
        pos_texto++;
    }
    texto_decript[pos_texto] = '\0';

    fclose(arquivo);

    printf("\nTexto descriptografado:\n");
    printf("%s\n\n", texto_decript);
}

int main() {
    int opcao;
    char texto[1000];
    char chave[100];

    printf("Criptografando em C:\n");

    while(opcao != 3){
        printf("\nMenu\n");
        printf("1 - Criptografar\n2 - Descriptografar \n3 - Fechar\n");
        printf("\nDigite a opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            printf("Digite o texto a ser criptografado:\n");
            getchar();
            fgets(texto, sizeof(texto), stdin);

            printf("Digite a palavra secreta da criptografia:\n");
            scanf("%s", &chave);

            criptografar(chave, texto);
            break;
        case 2:
            printf("Digite a palavra secreta da criptografia:\n");
            scanf("%s", chave);

            descriptografar(chave);
            break;
        case 3:
            opcao = 3;
            break;
        default:
            printf("Opcao invalida!!! Tente novamente!!!\n\n");
        }
    }

    return 0;
}
