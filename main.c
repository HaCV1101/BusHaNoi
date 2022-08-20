
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "lib/jrb.h"
#include "lib/dllist.h"

#define INFINITIVE_VALUE 100000
int luot = -1;
typedef struct
{
    JRB edges;
    JRB vertices;
    JRB name_vertices;
} Graph;

Graph createGraph();
int BFS(Graph graph, char *name1, char *name2, int *rank); // duyet tim cac duong ngan nhat
void Print(JRB node);
int Print_ver(Graph graph);
void Print_Edge(Graph graph);
void Print_nameVer(Graph graph);
void copy_str(char str[], char xau[]);
void cat_str(char chuoi[], char str[], char xau[]);
void menu();
int addVertex(Graph graph, int id, char *name);          //them dinh
char *getVertex_name(Graph graph, int id);               // tra ve ten dinh
int getVertex_id(Graph graph, char *name);               // tra ve id dinh
void addEdge(Graph graph, int v1, int v2, char *weight); // them canh noi v1 va v2
JRB getEdgeValue(Graph graph, int id1, int id2);
int indegree(Graph graph, int v, int *output);
int outdegree(Graph graph, int v, int *output);
void dropGraph(Graph graph);
double shortestPath(Graph graph, int s, int t, int *path, int *length);
int so_sanh(JRB node1, JRB node2);
int out_rank(int *rank, int u, int *output);
int printPath(Graph g, int end, int rank[], int *paths[]); // duyet tim cac duong ngan nhat
int doi_bus(Graph graph, int *path, int rank);             // tim duong doi bus it nhat
int min_key(JRB node1);
char *bus(JRB node);
char *getBus(JRB node, char *key); // tra ve tuyen bus co gia tri nho nhat trong tap trong so

int main()
{
    int scan;
    int i = 1, sodinh, s, t = 0, id_child, id_parent = 0, co, sodinhlancan, total, min, num, p, stop, sum;
    char str[INFINITIVE_VALUE], bus[INFINITIVE_VALUE], ten[INFINITIVE_VALUE], chieu[INFINITIVE_VALUE], diem_dau[INFINITIVE_VALUE], diem_cuoi[INFINITIVE_VALUE], key[INFINITIVE_VALUE], key1[INFINITIVE_VALUE];
    FILE *f;
    JRB node, tree, root;
    int *paths[INFINITIVE_VALUE], sort[INFINITIVE_VALUE], input[1000];
    min = INFINITIVE_VALUE;
    char *tuyenBus[1000];
    char tentuyenbus[INFINITIVE_VALUE];
    int z;
    f = fopen("data.txt", "r");

    if (f == NULL)
    {
        printf("Loi doc file!\n");
    }

    Graph g = createGraph();
    //doc du lieu tu file va xay dung graph
    // while (!feof(f) && fgets(str, INFINITIVE_VALUE, f))
    // {
    //     str[strlen(str) - 1] = '\0';
    //     if (str[0] == '#')
    //     {
    //         copy_str(str, ten);
    //         co = 0;
    //     }
    //     else if (str[0] == '@')
    //     {
    //         copy_str(str, chieu);
    //         co = 0;
    //     }
    //     else
    //     {
    //         co = 1;
    //     }
    //     if (co == 1)
    //     {
    //         cat_str(bus, ten, chieu);
    //         //printf("%s\n", bus);
    //         id_child = addVertex(g, i, strdup(str));
    //         if (id_child == 0)
    //         {
    //             addEdge(g, id_parent, i, strdup(bus));
    //             id_parent = i;
    //             i++;
    //         }
    //         else
    //         {
    //             addEdge(g, id_parent, id_child, strdup(bus));
    //             id_parent = id_child;
    //         }
    //     }
    //     else
    //     {
    //         id_parent = 0;
    //     }
    // }

    //menu
    do
    {
        menu();
        luot = -1;
        scanf("%d", &scan);
        __fpurge(stdin);
        while (scan != 1 && scan != 2 && scan != 3)
        {
            printf("Nhap sai!!!(chi duoc nhap 1 hoac 2), moi nhap lai: ");
            scanf("%d", &scan);
            __fpurge(stdin);
        }
        switch (scan)
        {
        case 1:

            while (!feof(f) && fgets(str, INFINITIVE_VALUE, f))
            {
                str[strlen(str) - 1] = '\0';
                if (str[0] == '#')
                {
                    copy_str(str, ten);
                    co = 0;
                }
                else if (str[0] == '@')
                {
                    copy_str(str, chieu);
                    co = 0;
                }
                else
                {
                    co = 1;
                }
                if (co == 1)
                {
                    cat_str(bus, ten, chieu);
                    //printf("%s\n", bus);
                    id_child = addVertex(g, i, strdup(str));
                    if (id_child == 0)
                    {
                        addEdge(g, id_parent, i, strdup(bus));
                        id_parent = i;
                        i++;
                    }
                    else
                    {
                        addEdge(g, id_parent, id_child, strdup(bus));
                        id_parent = id_child;
                    }
                }
                else
                {
                    id_parent = 0;
                }
            }
            sodinh = Print_ver(g);
            printf("Tong so diem bus : %d\n", sodinh);

            printf("Nhap diem dau: ");
            __fpurge(stdin);
            fgets(diem_dau, INFINITIVE_VALUE, stdin);
            diem_dau[strlen(diem_dau) - 1] = '\0';
            //printf("%s\n", diem_dau);
            if (jrb_find_str(g.name_vertices, diem_dau) == NULL)
            {
                printf("Khong ton tai diem bus: %s\n", diem_dau);
                break;
            }
            printf("Nhap diem cuoi: ");
            __fpurge(stdin);
            fgets(diem_cuoi, INFINITIVE_VALUE, stdin);
            diem_cuoi[strlen(diem_cuoi) - 1] = '\0';
            if (jrb_find_str(g.name_vertices, diem_cuoi) == NULL)
            {
                printf("Khong ton tai diem bus: %s\n", diem_cuoi);
                break;
            }

            // jrb_traverse(node, g.edges)
            // {
            //     tree = (JRB)jval_v(node->val);
            //     root = (JRB)jval_v(tree->val);
            //     if (jrb_find_str(root, tentuyenbus)!=NULL)
            //     {
            //         printf("%s\n", getVertex_name(g, jval_i(node->key)));
            //     }else{
            //         printf("Khong tim thay\n");
            //     }
            // }

            stop = BFS(g, diem_dau, diem_cuoi, sort);
            // printf("Rank : %d\n", sort[stop]);
            for (int i = 0; i < 100; i++)
            {
                tuyenBus[i] = (char *)malloc(sizeof(char) * INFINITIVE_VALUE);
                paths[i] = (int *)malloc(sizeof(int) * (sort[getVertex_id(g, diem_cuoi)] + 1));
                for (int j = 0; j < sort[getVertex_id(g, diem_cuoi)]; j++)
                {
                    paths[i][j] = -1;
                }
                paths[i][sort[getVertex_id(g, diem_cuoi)]] = getVertex_id(g, diem_cuoi);
            }

            sum = printPath(g, getVertex_id(g, diem_cuoi), sort, paths);
            for (int i = 0; i <= sum; i++)
            {
                num = doi_bus(g, paths[i], sort[getVertex_id(g, diem_cuoi)]);
                if (num < min)
                {
                    min = num;
                    p = i;
                }
            }
            node = getEdgeValue(g, paths[p][sort[stop] - 1], paths[p][sort[stop]]);
            jrb_traverse(tree, node)
            {
                if (jval_i(tree->val) == min_key(node))
                {
                    strcpy(key, jval_s(tree->key));
                    // printf("Tuyen bus : %s - %d\n", key, jval_i(tree->val));
                }
            }
            tuyenBus[sort[stop]] = key;
            for (int i = sort[stop] - 1; i > 0; i--)
            {
                strcpy(key1, key);
                root = getEdgeValue(g, paths[p][i - 1], paths[p][i]);
                strcpy(tuyenBus[i], getBus(root, key1));
                strcpy(key1, getBus(root, key1));
            }
            printf("\n\nDuong di ngan nhat la: \n\n");
            for (int i = 0; i <= sort[getVertex_id(g, diem_cuoi)]; i++)
            {

                printf("%s(%s) %c ", getVertex_name(g, paths[p][i]), tuyenBus[i + 1] != NULL ? tuyenBus[i + 1] : "Diem cuoi", i == sort[getVertex_id(g, diem_cuoi)] ? '\n' : '-');
            }
            printf("\nCan phai doi it nhat : %d tuyen bus.\n", min);
            for (int i = 0; i < 10; i++)
            {
                free(paths[i]);
            }
            break;
        case 2:
            rewind(f);
            printf("Nhap vao tuyen bus :");
            __fpurge(stdin);
            fgets(tentuyenbus, 10, stdin);
            tentuyenbus[strlen(tentuyenbus) - 1] = 0;
            printf("Tuyen bus : %s\n", tentuyenbus);
            while (!feof(f) && fgets(str, INFINITIVE_VALUE, f))
            {
                str[strlen(str) - 1] = '\0';
                if (str[0] == '#')
                {
                    copy_str(str, ten);
                    //printf("%s\n", ten);
                    co = 0;
                    z = 0;
                    continue;
                }
                if (strcmp(ten, tentuyenbus) == 0)
                {
                    if (str[0] == '@')
                    {
                        copy_str(str, chieu);
                        printf("%s\n", chieu);
                        co = 0;
                        z = 1;
                    }
                    else
                    {
                        co = 1;
                    }
                    if (co == 1)
                    {
                        printf("%s\n", str);
                        z = 1;
                    }
                }
                else
                    z = 1;
                if (z == 0)
                    break;
            }
            
            break;
        case 3:
            printf("\t\tCam on ban da su dung phan mem!\n");
            break;
        }
    } while (scan != 3);

    dropGraph(g);
    return 0;
}

Graph createGraph() //Khoi tao
{
    Graph g;
    g.edges = make_jrb();
    g.vertices = make_jrb();
    g.name_vertices = make_jrb();
    return g;
}
int getVertex_id(Graph graph, char *name) // lay id dinh
{
    JRB node = jrb_find_str(graph.name_vertices, name);
    if (node == NULL)
        return 0;
    else
        return jval_i(node->val);
}
int addVertex(Graph graph, int id, char *name) // them dinh moi
{
    JRB node = jrb_find_str(graph.name_vertices, name);
    if (node == NULL)
    { // only add new vertex
        JRB node1 = make_jrb();
        jrb_insert_str(graph.name_vertices, name, new_jval_i(id));
        jrb_insert_int(graph.edges, id, new_jval_v(node1));
        jrb_insert_int(graph.vertices, id, new_jval_s(name));
        return 0;
    }
    else
    {
        return getVertex_id(graph, name);
    }
}

char *getVertex_name(Graph graph, int id) // lay ten dinh
{
    JRB node = jrb_find_int(graph.vertices, id);
    if (node == NULL)
        return NULL;
    else
        return jval_s(node->val);
}

void addEdge(Graph graph, int v1, int v2, char *weight) // them canh
{
    JRB node, tree, node1, bus;
    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
    {
        return;
    }
    tree = (JRB)jval_v(node->val);
    node1 = jrb_find_int(tree, v2);
    if (node1 == NULL)
    {
        bus = make_jrb();
        jrb_insert_str(bus, weight, new_jval_i(1));
        jrb_insert_int(tree, v2, new_jval_v(bus));
    }
    else
    {
        bus = (JRB)jval_v(node1->val);
        jrb_insert_str(bus, weight, new_jval_i(1));
    }
}

JRB getEdgeValue(Graph graph, int id1, int id2) // tra ve trong so cua canh
{
    JRB node, tree, node1;

    node = jrb_find_int(graph.edges, id1);
    if (node == NULL)
    {
        printf("Khong co bus\n");
        return NULL;
    }
    tree = (JRB)jval_v(node->val);
    node1 = jrb_find_int(tree, id2);
    if (node1 == NULL)
    {
        printf("Khong co bus\n");
        return 0;
    }
    else
        return (JRB)jval_v(node1->val);
}

int indegree(Graph graph, int v, int *input) // tra ve dinh cha
{
    JRB tree, node;
    int total = 0;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        if (jrb_find_int(tree, v))
        {
            input[total] = jval_i(node->key);
            total++;
        }
    }
    return total;
}

int outdegree(Graph graph, int v, int *output) // tra ve dinh con
{
    JRB tree, node;
    int total;
    node = jrb_find_int(graph.edges, v);
    if (node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);
    total = 0;
    jrb_traverse(node, tree)
    {
        output[total] = jval_i(node->key);
        total++;
    }
    return total;
}

void dropGraph(Graph graph) // free
{
    JRB node, tree;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_traverse(node, graph.vertices)
    {
        free(jval_s(node->val));
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
    jrb_free_tree(graph.name_vertices);
}
void copy_str(char str[], char xau[])
{
    for (int i = 0; i < strlen(str); i++)
    {
        xau[i] = str[i + 1];
    }
}
void cat_str(char chuoi[], char str[], char xau[])
{
    strcpy(chuoi, str);
    strcat(chuoi, " ");
    strcat(chuoi, xau);
}
void menu()
{
    printf("\n\n\n\n\t\t\t===========MeNu===================\n");
    printf("\t\t\t+%4s1.Tim duong di.%12s +\n", " ", " ");
    printf("\t\t\t+%4s2.Tim danh sach diem dung.%s +\n", " ", " ");
    printf("\t\t\t+%4s3.Thoat chuong trinh.%6s +\n", " ", " ");
    printf("\t\t\t==================================\n");
    printf("...........Lua chon cua ban: ");
}
void Print_nameVer(Graph graph)
{
    JRB node;
    jrb_traverse(node, graph.name_vertices)
    {
        printf("ID : %d Name : %s\n", jval_i(node->val), jval_s(node->key));
    }
}
int Print_ver(Graph graph)
{
    int i = 0;
    JRB node;
    jrb_traverse(node, graph.vertices)
    {
        printf("ID : %d Name : %s\n", jval_i(node->key), jval_s(node->val));
        i++;
    }
    return i;
}
void Print(JRB node)
{
    JRB tree;
    jrb_traverse(tree, node)
    {
        printf("%s\n", jval_s(tree->key));
    }
}

int BFS(Graph graph, char *name1, char *name2, int *rank) //
{
    int visited[INFINITIVE_VALUE] = {};
    int n, output[100], u, v;
    Dllist node, queue;
    int start, stop;
    start = getVertex_id(graph, name1);
    stop = getVertex_id(graph, name2);
    queue = new_dllist();
    dll_append(queue, new_jval_i(start));
    for (int i = 0; i < INFINITIVE_VALUE; i++)
    {
        rank[i] = INFINITIVE_VALUE;
    }
    rank[start] = 0;
    while (!dll_empty(queue))
    {
        node = dll_first(queue);
        u = jval_i(node->val);
        dll_delete_node(node);
        if (!visited[u])
        {
            visited[u] = 1;
            if (rank[u] > rank[stop])
                return stop;
            n = outdegree(graph, u, output);
            for (int i = 0; i < n; i++)
            {
                v = output[i];
                if (rank[v] - 1 > rank[u])
                    rank[v] = rank[u] + 1;
                if (!visited[v])
                    dll_append(queue, new_jval_i(v));
            }
        }
    }
    return stop;
}

// int out_rank(int *rank, int u, int *output)
// {
//     int total = 0;
//     for (int i = 0; i < INFINITIVE_VALUE; i++)
//     {
//         if (rank[i] == rank[u] + 1)
//         {
//             output[total] = i;
//             total++;
//         }
//     }
//     return total;
// }

// int so_sanh(JRB node1, JRB node2)
// {
//     JRB tree1, tree2;
//     jrb_traverse(tree1, node1)
//     {
//         jrb_traverse(tree2, node2)
//         {
//             if (tree1 == tree2)
//                 return 1;
//         }
//     }
//     return 0;
// }

int printPath(Graph g, int end, int sort[], int *path[])
{
    int input[1000];
    int i;
    if (!sort[end])
    {
        path[luot + 1][sort[end]] = end;
        return ++luot;
    }
    int total = indegree(g, end, input);
    for (int j = 0; j < total; j++)
    {
        if (sort[input[j]] == sort[end] - 1)
        {
            i = printPath(g, input[j], sort, path);
            for (int k = i; k >= 0; k--)
            {
                if (path[k][sort[input[j]]] >= 0)
                    break;
                path[k][sort[input[j]]] = input[j];
            }
        }
    }
    return luot;
}
int doi_bus(Graph graph, int *path, int rank)
{
    JRB node1, node2, tree1, tree2;
    int num;
    for (int i = 2; i <= rank; i++)
    {
        node1 = getEdgeValue(graph, path[i - 2], path[i - 1]);
        //Print(node1);
        node2 = getEdgeValue(graph, path[i - 1], path[i]);
        //Print(node2);
        jrb_traverse(tree1, node1)
        {
            jrb_traverse(tree2, node2)
            {
                if (strcmp(jval_s(tree2->key), jval_s(tree1->key)) == 0)
                {
                    (tree2->val).i = (tree1->val).i;
                }
                else
                {
                    (tree2->val).i = min_key(node1) + 1;
                }
            }
        }
    }
    num = min_key(node2);
    return num;
}
int min_key(JRB node1)
{
    JRB tree;
    int m = INFINITIVE_VALUE;
    jrb_traverse(tree, node1)
    {
        if (jval_i(tree->val) < m)
            m = jval_i(tree->val);
    }
    return m;
}
char *getBus(JRB node, char *key)
{
    int min = 1000, i;
    char *name;
    JRB tree;
    jrb_traverse(tree, node)
    {
        if (strcmp(jval_s(tree->key), key) == 0)
        {
            name = key;
            return name;
        }
        i = jval_i(tree->val);
        if (i < min)
        {
            min = i;
            name = jval_s(tree->key);
        }
    }
    return name;
}
