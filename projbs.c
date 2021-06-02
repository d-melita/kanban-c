#include "header.h"
int tempo = 0;
struct utilizador users[MAXUSERS] = {0};
struct tarefa tarefas[MAX_TASKS] = {0};
struct atividade activities[MAXACTIVITIES] = {0};
int idsordenados[MAX_TASKS] = {0};

int main()
{
    char c;
    strcpy(activities[0].atividade, TODO);
    strcpy(activities[1].atividade, INPROGRESS);
    strcpy(activities[2].atividade, DONE);
    activities[0].numero = 1;
    activities[1].numero = 2;
    activities[2].numero = 3;
    c = getchar();
    
    while (c != 'q')
    {
        switch (c)
        {
            case 't':
            {   
                new_task();
                break;
            }
            case 'l':
            {
                list_tasks();
                break;
            }
            case 'n':
            {
                time();
                break;
            }
            case 'u':
            {
                utilizador();
                break;
            }
            case 'm':
            {
                movetask();
                break;
            }
            case 'd':
            {
                tasksinactivity();
                break;
            }
            case 'a':
            {
                addactivity();
                break;
            }
            default:
                break;
        }
        c = getchar();
    }
    return RETURN_ZERO;
}

/*Funcao new_task: esta funcao e responsavel por criar tarefas atribuindo a cada
um numero correspondente ao id, sendo este dado de ordem crescente a medida que 
sao introduzidas novas tarefas, um numero que corresponde ao tempo previsto de 
duracao da tarefa e uma descricao da tarefa, sendo estes dois ultimos atribuidos
em funcao do que esta no input. Caso ja existiam 10000 tarefas, o maximo neste 
sistema, a descricao ser duplicada ou o tempo esperado de duracao ser incorreto
e impresso erro e nao e adicionada nenhuma tarefa. */
void new_task()
{
    int i, j, m, n = 0, id = 0, tc = 0; /* tc = 0 - tempo correto  */
    char c;                                 /* tc = 1 - tempo incorreto */
    char descricao[MAXTASKDESCRIPTION];
    /* e = estado | e = 0 -> nao ocorreu nenhum erro // e = 1 -> ocorreu um 
    erro */

    c = getchar();

    for (i = 1; i < MAX_TASKS + 1; ++i) 
    {
        if (tarefas[i - 1].id == 0) /*verifica qual a primeira posicao do vetor*/
        {                           /* de tarefas cujo id está igual a 0 e */
            id = i;                 /*atribui o valor de indice ao id */
            break;
        }
    }

    if (i == MAX_TASKS + 1)
    {
        printf("%s\n", TMT);
        while (c != '\n')
        {
            c = getchar();
        }
        return;
    }

    while (c == ' ' || c == '\t') /* limpar os espaços brancos entre t e */
    {                              /*  <duracao> */
        c = getchar();
    }
    while (c != ' ') /* <duracao> */
    {
        if (c >= '0' && c <= '9')
        {
            n = n*10 + (c - '0');
        }

        else
        {
            tc = 1;
        }

        c = getchar();
    }

    while (c == ' ' || c == '\t') /* limpar os espaços brancos entre 
    <duracao> e <descricao> */
    {
        c = getchar();
    }
            
    j = 0;
    while (c != '\n' && j < MAXTASKDESCRIPTION)
    {
        descricao[j] = c;
        j++;
        c = getchar();
    }
    descricao[j] = '\0';

    while(c != '\n')
    {
        c = getchar();
    }
        
    for (j = 0; j < MAX_TASKS; ++j)
        {
            if (strcmp((descricao), tarefas[j].descricao) == 0)
            {
                printf("%s\n", DD);
                return;
            }
        }

    if (n == 0 || tc == 1)
        {
            printf("%s\n", ID);
            return;
        }

    /* se correu tudo bem até aqui, é altura de atribuir os 
        valores aos vários parametros da tarefa */
    strcpy(tarefas[i-1].descricao, descricao);
    tarefas[i-1].tempo = n; /* tarefa i tem n duração */
    tarefas[i-1].id = id; /* id da tarefa */
    strcpy(tarefas[i-1].atividade, TODO);
    tarefas[i-1].instinicio = 0;

    m = binarysearch(id); /* neste ponto ordena-se as tarefas por ordem */
    if (m == id-1)        /*alfabetica de descricao a medida que sao introduzidas */
        idsordenados[m] = id; /*aqui signfica que o id foi para o fim do vetor */
    else
        ordenar(m, id); /*Aqui e necessario reorganizar o vetor */
    printf("%s %d\n",T, id);
}

/*Esta funcao vai percorrer o vetor de tarefas que contem as tarefas ordenadas 
por ordem alfabetica de descricao de modo a determinar em que indice deve ser
colocado o id da nova tarefa introduzida */
int binarysearch(int id)
{
    int meio = 0;
    int linf = 0;
    int lsup = id-1;

    while (linf <= lsup)
    {
        meio = (linf + lsup) / 2;
        
        if ((strcmp(tarefas[id-1].descricao, \
        tarefas[idsordenados[meio]-1].descricao)) < 0 && \
        (strcmp(tarefas[id-1].descricao, \
        tarefas[idsordenados[meio-1]-1].descricao) > 0))
            return meio;
        
        if((strcmp(tarefas[id-1].descricao, \
        tarefas[idsordenados[meio]-1].descricao) > 0))
        {
            linf = meio + 1;
        }
        else
        {
            lsup = meio - 1;
        }
    }
    return meio;
}

/*Esta funcao introduz o id no indice devolvido pela funcao antrerior e reorganiza
o vetor*/
void ordenar(int n, int len)
{
    int i;
    for (i = len + 1; i > n; --i)
    {
        idsordenados[i] = idsordenados[i-1];
    }
    idsordenados[i] = len;
}

/*Esta funcao tem como objetivo listar as tarefas (mostrando o id, atividade, 
tempo esperado de duracao e a descricao) do sistema caso apenas seja introduzido
 "l" por ordem alfabetica de descricao ou listar as tarefas pelos ids que 
 aparecerem no input. Caso algum dos ids nao exista, e mostrada uma mensagem
de erro a frente do id*/
void list_tasks()
{
    char c;
    int n = 0, i = 0, cont = 0, cont2 = 0, j = 0, k = 0, l = 0, estado = 0;
    int neg = 0; /*id negativo: 1 se existir um '-' antes e 0 caso contrario */
    int tasks[MAX_TASKS]; /* neste vetor e colocado os ids do input */
    int nao_existe[MAX_TASKS]; /*neste vetor sao colocados os ids do input que*/
    c = getchar();              /*nao existam no sistema */

    if (c == '\n')
    {
        for (i = 1; i < MAX_TASKS + 1; i++)
        {
            if (tarefas[i-1].id != 0)
            {
                tasks[i-1] = tarefas[i-1].id;
                cont++; /* saber quantas tasks tenho para ordenar */
            }
        }

        for (i = 0; i < cont; ++i)
        {
            printf("%d %s #%d %s\n", \
            tarefas[idsordenados[i]-1].id, \
            tarefas[idsordenados[i]-1].atividade,\
            tarefas[idsordenados[i]-1].tempo, \
            tarefas[idsordenados[i]-1].descricao);
        }
    }

    else
    {   
        while (c != '\n')
        {
            if (c == ' ' || c == '\t')
            {
                while (c == ' ' || c == '\t')
                    c = getchar(); /* limpar caracteres brancos */
            }

            else
            {
                while (c != ' ' && c != '\t' && c != '\n')
                {   
                    if (c == '-')
                    {    
                        neg = 1;
                        c = getchar();
                    }
                    
                    else
                    {
                        n = n * 10 + (c - '0');
                        c = getchar();
                    }
                }

                if (neg == 1)
                {
                    n = -n;
                    neg = 0;
                }
                tasks[i] = n; /* id */
                i++;
                cont++;
                n = 0;
            }
        }
    
        /* ja li os ids todos do input */
        for (i = 0; i < cont; i++)
        {
            if (tasks[i] == 0) /*caso algum dos ids introduzidos seja 0 */
            {
                nao_existe[l] = tasks[i];
                estado = 1;
                l++;
                cont2++;
            }

            else
            {
                j = tasks[i] - 1;
                for (k = 0; k < MAX_TASKS; ++k)
                {
                    if (tarefas[k].id == j + 1)
                    {    
                        break;
                    }
                }

                if (k ==  MAX_TASKS)
                {
                    estado = 1;
                    nao_existe[l] = j + 1;
                    l++;
                    cont2++;
                }
            }
        }

        if (estado == 0) /* ira listar as tarefas pela ordem que aparecem no input */
        {                /* nao imprindo qualquer erro pois todos os ids existem */
            for (i = 0; i < cont; ++i)
            {
                j = tasks[i] - 1;
                printf("%d %s #%d %s\n", tasks[i], tarefas[j].atividade, \
                tarefas[j].tempo, tarefas[j].descricao);
            }
        }
        else /* pelo menos um dos ids nao existe logo nesse lugar se impresso a */
        {    /*mensagem de erro */
            for (i = 0; i < cont; ++i)
            {
                j = tasks[i] - 1;
                for (l = 0; l < cont2; ++l)
                {
                    if (nao_existe[l] == j + 1)
                    {   
                        printf("%d: %s\n", nao_existe[l], NST);
                        break;
                    }
                }
                if (l == cont2)
                    printf("%d %s #%d %s\n", tasks[i], tarefas[j].atividade, \
                    tarefas[j].tempo, tarefas[j].descricao);
            } 
        }
    }
}

/* Esta funcao avanca o tempo do sistema adicionando ao tempo atual o valor 
introduzido e mostrando o tempo atual. Caso seja introduzido um tempo invalido
e mostrada uma mensagem de erro */
void time()
{
    char c;
    int n = 0;
    c = getchar();
    
    while (c == ' ' || c == '\t')
        c = getchar(); /*limpar espacos */
    
    if (c >= '0' && c <= '9')
    {
        while (c >= '0' && c <= '9')
        {
            n = n*10 + (c - '0');
            c = getchar();
        }

        if (c != ' ' && c != '\n')
            printf("%s\n", IT);
        
        else
        {
            tempo = tempo + n;
            printf("%d\n", tempo);
        }
    }
    else
        printf("%s\n", IT);
}

/*Esta funcao adiciona um utilizador ou lista todos os utilizadores por ordem de
criacao. Caso ja existam 50 utilizadores, max deste sistema, ou caso o nome de 
utilizador inserido ja exista e impresso erro*/
void utilizador()
{
    char c, user[MAXUSER];
    int i, u; 

    c = getchar();

    while (c == ' ' || c == '\t')
        c = getchar();

    if (c == '\n') /*listar utilizadores */
    {
        for (i = 0; i < MAXUSERS; ++i)
        {
            if (users[i].u != 0)
            {
                printf("%s\n", users[i].user);
            }
        }
    }

    else
    {
        i = 0;
        while ((c != '\n' && c != ' ') && (i < MAXUSER - 1))
        {   /*ler o nome de utilizador e guardar num vetor temporario */
            user[i] = c;
            c = getchar();
            i++;
        }

        user[i] = '\0';

        while(c != '\n')
            c = getchar();
        
        for (i = 0; i < MAXUSERS; ++i)
        {
            if (strcmp(user, users[i].user) == 0) /*verificacao de utilizador */
            {                                     /*mesmo nome no sistema */
                printf("%s\n", UAE);
                return;
            }
        }
        
        for (i = 1; i < MAXUSERS + 1; ++i)
        {
            if (users[i-1].u == 0)
            {
                u = i;
                break;
            }
        }

        if (i == MAXUSERS + 1) /* significa que já existem MAXUSERS no sistema*/
        {
            printf("%s\n", TMU);
            return;
        }
        users[u-1].u = u;
        strcpy(users[u-1].user, user);
    }
}

/*Esta funcao move tasks de uma atividade para a outra e imprime, caso nao ocorra
nenhum erro e caso a tarefa seja movida para DONE e nao proveniente de DONE, o 
tempo gasto e a diferenca entre esse tempo e o tempo esperado. Caso algum dos 
inputs seja incorreto e impresso um erro em funcao do que estiver incorreto */
void movetask()
{
    char c, user[MAXUSER], activity[MAXATIVIDADE], atividade[MAXATIVIDADE];
    int i, duration, slack, id = 0;    
    c = getchar();

    while (c == ' ' || c == '\t')
        c = getchar();

    while (c >= '0' && c <= '9')
    {
        id = id*10 + (c-'0');
        c = getchar();
    }

    while (c == ' ' || c == '\t')
        c = getchar();

    i = 0;
    while (c != ' ' && c != '\t')
    {
        user[i] = c;
        i++;
        c = getchar();
    }
    user[i] = '\0';

    while (c == ' ' || c == '\t')
        c = getchar();

    i = 0;
    while (c != '\n' && i < MAXATIVIDADE)
    {   
        activity[i] = c;
        i++;
        c = getchar();
    }

    activity[i] = '\0';
    strcpy(atividade, tarefas[id-1].atividade);

    while(c != '\n')
        c = getchar();

    if (id == 0)
    {
        printf("%s\n", NST);
        return;
    }

    else
    {
        for (i = 0; i < MAX_TASKS; ++i)
        {
            if (tarefas[i].id == id) /*verificar se o id existe */
                break;
        }

        if (i == MAX_TASKS)
        {   
            printf("%s\n", NST);
            return;
        }
    }

    if ((strcmp(atividade, activity) == 0)) /*Mover para a mesma tarefa */
        return;

    if ((strcmp(activity, TODO) == 0) && (strcmp(atividade, TODO) != 0))
    {/*mover de outra atividade para to do */
        printf("%s\n", TAS);
        return;
    }
    
    for (i = 0; i < MAXUSERS; ++i)
    {
        if (strcmp(users[i].user, user) == 0) /*verificar se user existe */
            break;
    }

    if (i == MAXUSERS)
    {
        printf("%s\n", NSU);
        return;
    }

    for (i = 0; i < MAXACTIVITIES; ++i)
    {   /* verificar se atividade existe */
        if (strcmp(activities[i].atividade, activity) == 0) 
            break;
    }

    if (i == MAXACTIVITIES)
    {
        printf("%s\n", NSA);
        return;
    }
    
    if (strcmp(atividade, TODO) == 0) /*vai sair de TO DO */
    {
        tarefas[id-1].instinicio = tempo;
        strcpy(tarefas[id-1].atividade, activity);

        if (strcmp(activity, DONE) == 0)
        {
            duration = tempo - tarefas[id-1].instinicio;
            slack = duration - tarefas[id-1].tempo;
            strcpy(tarefas[id-1].atividade, DONE);
            printf("%s%d %s%d\n", DURATION, duration, SLACK, slack);
        }
            
    }
    else
    {
        if (strcmp(activity, DONE) == 0)
        {
            duration = tempo - tarefas[id-1].instinicio;
            slack = duration - tarefas[id-1].tempo;
            strcpy(tarefas[id-1].atividade, DONE);
            printf("%s%d %s%d\n", DURATION, duration, SLACK, slack);
        }

        else
        {   /*apenas muda a atividade em que se encontra a task */
            strcpy(tarefas[id-1].atividade, activity);
        }
    }
}
/*Esta funcao lista todas as tarefas que se encontrem na atividade introduzida por
ordem de instante de inicio e por ordem alfabetica de descricao caso os instantes
de inicio sejam iguais. Caso a atividade introduzida nao exista e impresso erro*/
void tasksinactivity()
{
    char c, activity[MAXATIVIDADE];
    int i = 0, cont = 0, j = 0, n, cont2, nenhuma_troca = 1;
    int ids[MAX_TASKS]; /*vetor que vai guardar os ids das tarefas que se encontram
    na atividade introduzida */
    c = getchar();

    while (c == ' ' || c == '\t')
    {
        c = getchar();
    }

    while (c != '\n' && i < MAXATIVIDADE)
    {
        activity[i] = c;
        i++;
        c = getchar();
    }
    activity[i] = '\0';

    while(c != '\n')
    {
        c = getchar();
    }

    for (i = 0; i < MAXACTIVITIES; ++i)
    {   /*verificar se existe a atividade */
        if (strcmp(activities[i].atividade, activity) == 0)
            break;
    }

    if (i == MAXACTIVITIES)
    {
        printf("%s\n", NSA);
        return;
    }

    for (i = 0; i < MAX_TASKS; ++i)
    {
        if (strcmp(tarefas[i].atividade, activity) == 0)
        {
            ids[j] = tarefas[i].id; /*vetor vai conter todos os ids*/
            cont++;
            j++;       /*com a mesma atividade mas está desordenado */
        }
    }
    cont2 = cont;
    while (nenhuma_troca == 1) /*ordenar o vetor que contem os ids na atividade*/
    {
        nenhuma_troca = 0;
        for (i = 0; i < cont - 1; ++i)
        {
            if (tarefas[ids[i]-1].instinicio > \
            tarefas[ids[i+1]-1].instinicio)
            {
                n = ids[i];
                ids[i] = ids[i+1];
                ids[i+1] = n;
                nenhuma_troca = 1;
            }

            else if (tarefas[ids[i]-1].instinicio ==\
            tarefas[ids[i+1]-1].instinicio)
            {
                if (strcmp(tarefas[ids[i]-1].descricao, \
                tarefas[ids[i+1]-1].descricao) > 0)
                {
                    n = ids[i];
                    ids[i] = ids[i+1];
                    ids[i+1] = n;
                    nenhuma_troca = 1;
                }
            }
        }
        cont--;
    }

    /* vetor de ids já está ordenado */
    for (i = 0; i < cont2; ++i)
    {   
        printf("%d %d %s\n", tarefas[ids[i]-1].id, \
        tarefas[ids[i]-1].instinicio, tarefas[ids[i]-1].descricao);
    }
}

/*Esta funcao permite listar todas as atividades do sistema caso o input seja apenas
"a" ou introduzir uma atividade. Caso se pretenda adicionar uma atividade e 
ou o input seja incorreto ou ja exista uma atividade com o mesmo nome ou ja existam
10 atividades, que e o maximo do sistem, e impresso o erro respetivo.*/
void addactivity()
{
    char c, atividade[MAXATIVIDADE];
    int i = 0,cont = 0, numero, n;
    c =  getchar();

    while (c == ' ' || c == '\t')
        c = getchar();
    
    if (c == '\n')
    {
        for (i = 0; i < MAXACTIVITIES; ++i) /*listar todas as atividades por */
        { /* ordem de cricao */
            if (activities[i].numero != 0)
            {
                printf("%s\n", activities[i].atividade);
            }
        }
    }

    else
    {        
        while (c != '\n' && i < MAXATIVIDADE -1)
        {
            atividade[i] = c;
            i++;
            cont++;
            c = getchar();
        }
        atividade[i] = '\0';

        while(c != '\n')
        {
            c = getchar();
        }

        for (i = 0; i < MAXACTIVITIES; ++i)
        {
            if (strcmp(activities[i].atividade, atividade) == 0)
            { /* verificar se ja existe alguma atividade com o mesmo nome */
                printf("%s\n", DA);
                return;
            }
        }

        for (i = 0; i < cont; ++i)
            {
                if (atividade[i] >= 'a' && atividade[i] <= 'z')
                { /*verificacao se a descricao da atividade e correta */
                    printf("%s\n", INVALIDDESCRIPTION);
                    return;
                }
            }

        for (numero = 0; numero < MAXACTIVITIES; ++numero)
        {
            if (activities[numero].numero == 0)
            {
                n = numero + 1;
                break; 
            }
        }

        if (numero == MAXACTIVITIES)
        { /*verificar se ja existem o max de atividades no sitema */
            printf("%s\n", TMA);
            return;   
        }
        /* correu tudo bem, é para adicionar atividade */
        strcpy(activities[n-1].atividade, atividade);
        activities[n-1].numero = n;
    }   
}