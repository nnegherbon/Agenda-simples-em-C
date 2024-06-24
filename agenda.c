#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int opc;
    char nome[40], telefone[20];
    FILE *arquivo;

    do{
        printf("adicionar contato [1]\n");
        printf("consultar contato [2]\n");
        printf("excluir contato [3]\n");
        printf("sair da agenda [4]\n");
        printf("digite o numero respectivo da sua escolha:");
        scanf("%i", &opc);

        if (opc < 1 || opc > 4)
        {
            printf("numero digitado errado! Digite novamente:\n");
            continue;
        }else {
            switch (opc)
            {
            case 1: // adiconar contato
                arquivo = fopen("contato.bin", "ab");
                if (arquivo == NULL){
                    printf("erro ao abrir o arquivo");
                    break;
                }else {
                    printf("digite o nome do seu contato:\n");
                    scanf("%39s", nome);
                    printf("digite o numero de telefone:\n");
                    scanf("%19s", telefone);
                    fprintf(arquivo, "%s %s\n", nome, telefone);
                    fclose(arquivo);
                    printf("contato criado! Dados do contato: %s - %s \n", nome, telefone);
                    break;
                }
            case 2: // consulta
                arquivo = fopen("contato.bin", "rb");
                if (arquivo == NULL)
                {
                    printf("erro ao abrir o arquivo\n");
                    break;
                }else {
                    printf("contatos armazenados:\n");
                    while(fscanf(arquivo, "%39s %19s",nome, telefone) != EOF){
                        printf("Nome: %s, Telefone: %s\n", nome, telefone);
                    }
                    fclose(arquivo);
                    break;
                }
            case 3: // excluir contato
                arquivo = fopen("contato.bin", "r+b"); 
                    if (arquivo == NULL) {
                        printf("Erro ao abrir o arquivo\n");
                        break;
                    }
                    char excluirNome[40];
                    printf("Digite o nome do contato a excluir:\n");
                    scanf("%39s", excluirNome);
                    FILE *temp = fopen("temp.bin", "wb");
                    if (temp == NULL) {
                        printf("Erro ao abrir o arquivo temporario\n");
                        fclose(arquivo);
                        break;
                    }
                    int encontrado = 0;
                    rewind(arquivo);
                    while (fscanf(arquivo, "%s %s\n", nome, telefone) == 2) {
                        if (strcmp(nome, excluirNome) == 0) {
                            encontrado = 1;
                            printf("Contato encontrado e excluido: %s - %s\n", nome, telefone);
                        } else {
                            fprintf(temp, "%s %s\n", nome, telefone);
                        }
                    }
                    fclose(arquivo); fclose(temp);
                    remove("contato.bin"); rename("temp.bin", "contato.bin");
                    break;
            case 4: // sair do programa
                printf("saindo.... ate mais!");
                remove("contato.bin");
                break;

            default:
                break;
            }
        }

    } while (opc != 4);

    return 0;
}