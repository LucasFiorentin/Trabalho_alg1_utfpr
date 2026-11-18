#include <stdio.h>

#define NUM_CANDIDATOS 6
#define MIN_VOTOS 10

int main() {

    char nomes[6][50] = {"Ana Silva", "Bruno Costa", "Carla Dias",
                         "Diego Rocha", "Elisa Martins", "Felipe Souza"};
    int votos[6] = {0};
    int historico[2][8] = {0};
    int brancos = 0, nulos = 0, total = 0;

    int opcao;
    int voto;
    char continuar;
    int i;
    int t;
    int validos;
    int totalTurno;
    float perc;
    int turno1Feito = 0;
    int turno2Feito = 0;
    int precisaSegundo = 0;
    int primeiro = -1;
    int segundo = -1;

    do {
        printf("\n===== SISTEMA ELEITORAL =====\n");
        printf("1 - Iniciar 1o turno\n");
        printf("2 - Exibir resultado do 1o turno\n");
        printf("3 - Iniciar 2o turno (quando necessario)\n");
        printf("4 - Exibir resultado final / vencedor\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        t = -1;

        switch (opcao) {

        case 1:
            if (turno1Feito == 1) {
                printf("\nO 1o turno ja foi realizado e nao pode ser repetido.\n");
            } else {
                t = 0;
            }
            break;

        case 2:
            if (turno1Feito == 0) {
                printf("\nO 1o turno ainda nao foi realizado.\n");
                break;
            }

            validos = 0;
            for (i = 0; i < NUM_CANDIDATOS; i++) {
                validos = validos + historico[0][i];
            }
            totalTurno = validos + historico[0][6] + historico[0][7];

            printf("\n===== RESULTADO DO 1o TURNO =====\n");
            printf("Total: %d | Validos: %d (%.1f%%) | Brancos: %d (%.1f%%) | Nulos: %d (%.1f%%)\n",
                   totalTurno,
                   validos, (float)validos * 100 / totalTurno,
                   historico[0][6], (float)historico[0][6] * 100 / totalTurno,
                   historico[0][7], (float)historico[0][7] * 100 / totalTurno);

            printf("Numero  Candidato          Votos   %% dos validos\n");
            for (i = 0; i < NUM_CANDIDATOS; i++) {
                perc = 0;
                if (validos > 0) {
                    perc = (float)historico[0][i] * 100 / validos;
                }
                printf("%-7d %-18s %5d   %6.1f%%\n", i + 1, nomes[i], historico[0][i], perc);
            }

            if (validos == 0) {
                printf("Nao ha votos validos: nao ha classificados. Eleicao encerrada.\n");
            } else if (precisaSegundo == 0) {
                printf("ELEITO NO 1o TURNO: %d - %s\n", primeiro + 1, nomes[primeiro]);
            } else {
                printf("SEGUNDO TURNO: candidatos %d e %d\n", primeiro + 1, segundo + 1);
            }
            break;

        case 3:
            if (turno1Feito == 0) {
                printf("\nRealize o 1o turno antes de iniciar o 2o turno.\n");
            } else if (precisaSegundo == 0) {
                printf("\nNao ha 2o turno: a eleicao ja foi decidida no 1o turno.\n");
            } else if (turno2Feito == 1) {
                printf("\nO 2o turno ja foi realizado e nao pode ser repetido.\n");
            } else {
                t = 1;
            }
            break;

        case 4:
            if (turno1Feito == 0) {
                printf("\nNenhum turno foi apurado ainda.\n");
                break;
            }

            if (precisaSegundo == 0) {
                printf("\n===== RESULTADO FINAL =====\n");
                if (historico[0][primeiro] == 0) {
                    printf("Nao houve votos validos no 1o turno: nao ha classificados.\n");
                } else {
                    printf("VENCEDOR (1o turno): %d - %s\n", primeiro + 1, nomes[primeiro]);
                }
                break;
            }

            if (turno2Feito == 0) {
                printf("\nO 2o turno ainda nao foi realizado. Use a opcao 3.\n");
                break;
            }

            validos = historico[1][primeiro] + historico[1][segundo];
            totalTurno = validos + historico[1][6] + historico[1][7];

            printf("\n===== RESULTADO DO 2o TURNO =====\n");
            printf("Total: %d | Validos: %d (%.1f%%) | Brancos: %d (%.1f%%) | Nulos: %d (%.1f%%)\n",
                   totalTurno,
                   validos, (float)validos * 100 / totalTurno,
                   historico[1][6], (float)historico[1][6] * 100 / totalTurno,
                   historico[1][7], (float)historico[1][7] * 100 / totalTurno);

            for (i = 0; i < NUM_CANDIDATOS; i++) {
                if (i == primeiro || i == segundo) {
                    perc = 0;
                    if (validos > 0) {
                        perc = (float)historico[1][i] * 100 / validos;
                    }
                    printf("%d  %-18s %5d (%.1f%%)\n", i + 1, nomes[i], historico[1][i], perc);
                }
            }

            if (historico[1][primeiro] > historico[1][segundo]) {
                printf("VENCEDOR: %s\n", nomes[primeiro]);
            } else if (historico[1][segundo] > historico[1][primeiro]) {
                printf("VENCEDOR: %s\n", nomes[segundo]);
            } else {
                printf("EMPATE\n");
            }
            break;

        case 0:
            printf("\nEncerrando o sistema...\n");
            break;

        default:
            printf("\nOpcao invalida! Escolha 0, 1, 2, 3 ou 4.\n");
        }

        if (t != -1) {
            for (i = 0; i < NUM_CANDIDATOS; i++) {
                votos[i] = 0;
            }
            brancos = 0;
            nulos = 0;
            total = 0;

            printf("\n===== VOTACAO DO %do TURNO =====\n", t + 1);
            if (t == 0) {
                printf("Candidatos: 1 a 6 | 0 = Branco | outro numero = Nulo\n");
            } else {
                printf("Finalistas: %d - %s  |  %d - %s\n",
                       primeiro + 1, nomes[primeiro], segundo + 1, nomes[segundo]);
                printf("0 = Branco | qualquer outro numero = Nulo\n");
            }

            continuar = 's';
            while (continuar == 's') {
                printf("Voto %d: ", total + 1);
                scanf("%d", &voto);
                total++;

                if ((t == 0 && voto >= 1 && voto <= 6) ||
                    (t == 1 && (voto == primeiro + 1 || voto == segundo + 1))) {
                    votos[voto - 1]++;
                } else if (voto == 0) {
                    brancos++;
                } else {
                    nulos++;
                }

                if (total >= MIN_VOTOS) {
                    do {
                        printf("Deseja continuar votando? (s/n): ");
                        scanf(" %c", &continuar);
                    } while (continuar != 's' && continuar != 'n');
                }
            }

            for (i = 0; i < NUM_CANDIDATOS; i++) {
                historico[t][i] = votos[i];
            }
            historico[t][6] = brancos;
            historico[t][7] = nulos;

            if (t == 0) {
                validos = 0;
                for (i = 0; i < NUM_CANDIDATOS; i++) {
                    validos = validos + historico[0][i];
                }

                primeiro = -1;
                segundo = -1;
                for (i = 0; i < NUM_CANDIDATOS; i++) {
                    if (primeiro == -1 || historico[0][i] > historico[0][primeiro]) {
                        segundo = primeiro;
                        primeiro = i;
                    } else if (segundo == -1 || historico[0][i] > historico[0][segundo]) {
                        segundo = i;
                    }
                }

                if (validos > 0 && historico[0][primeiro] * 2 <= validos) {
                    precisaSegundo = 1;
                } else {
                    precisaSegundo = 0;
                }

                turno1Feito = 1;
                printf("\n1o turno encerrado com %d votos. Use a opcao 2 para ver o resultado.\n", total);
            } else {
                turno2Feito = 1;
                printf("\n2o turno encerrado com %d votos. Use a opcao 4 para ver o resultado.\n", total);
            }
        }

    } while (opcao != 0);

    return 0;
}
