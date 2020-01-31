#include <iostream>
#include<vector>
#include <ctime>
#include<queue>
#include<algorithm>
#include<string>
#include<fstream>
#include "GraphMatrix.h"
#include "GraphStruct.h"

using namespace std;


graph_matrix* struct_to_matr (graph_struct& graph) {
    graph_matrix* new_graph = new graph_matrix(graph.vertex_count);
    (*new_graph).is_oriented = graph.is_oriented;
    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.adjacent[i].size(); j++) {
            (*new_graph).adjacent[i][graph.adjacent[i][j].first] = graph.adjacent[i][j].second;
        }
    }
    return new_graph;
}
graph_struct* matr_to_struct (graph_matrix& graph) {
    graph_struct* new_graph = new graph_struct(graph.vertex_count);
    (*new_graph).is_oriented = graph.is_oriented;
    for (int i = 0; i < graph.vertex_count; i++) {
        for (int j = 0; j < graph.vertex_count; j++) {
            if (graph.adjacent[i][j]!=0) {
                (*new_graph).adjacent[i].push_back(make_pair(j,graph.adjacent[i][j]));
            }
        }
    }
    return new_graph;
}




void demonstration_add_to_matr (graph_matrix& graph, int verts) {
    int vert1 = rand()%verts;
    int vert2 = rand()%verts;
    while (vert1 == vert2) {vert2 = rand()%verts;}
    int weight = rand()%9+1;
    cout<<"adding new edge between "<<vert1<<" and "<<vert2<<" with weight "<<weight<<": "<<endl;
    add_to_matr(graph, vert1, vert2, weight);
    output_matrix_graph(graph);
}
void demonstration_add_to_struct (graph_struct& graph, int verts) {
    int vert1 = rand()%verts;
    int vert2 = rand()%verts;
    while (vert1 == vert2) {vert2 = rand()%verts;}
    int weight = rand()%9+1;
    cout<<"adding new edge between "<<vert1<<" and "<<vert2<<" with weight "<<weight<<": "<<endl;
    add_to_struct(graph, vert1, vert2, weight);
    output_struct_graph(graph);
}

void demonstration() {
    cout<<"1. Graph represented as matrix."<<endl;
    cout<<"Unit 0:"<<endl;
    int verts = rand()%5+5;
    int edges = rand()%10;
    cout<<"created random oriented weighed graph with "<<verts<<" vertices and "<<edges<<" egdes:"<<endl;
    graph_matrix* mgraph = create_random_matrg(verts, edges, true, true);
    output_matrix_graph(*mgraph);

    demonstration_add_to_matr(*mgraph, verts);
    demonstration_add_to_matr(*mgraph, verts);
    demonstration_add_to_matr(*mgraph, verts);
    demonstration_add_to_matr(*mgraph, verts);

    cout<<"transform matrix to structure representation: "<<endl;
    graph_struct* sgraph = matr_to_struct(*mgraph);
    output_struct_graph(*sgraph);

    cout<<"Unit 1:"<<endl;
    output_matrix_graph(*mgraph);
    cout<<"Is this graph acyclic? ";
    if (is_cyclic_matr(*mgraph)) {cout<<"no, it has cycle."<<endl;}
    else {cout<<"yes. "<<endl;}
    cout<<"Adding cycle to graph 1-2-3-1:"<<endl;
    add_to_matr(*mgraph, 1, 2, rand()%9+1);
    add_to_matr(*mgraph, 2, 3, rand()%9+1);
    add_to_matr(*mgraph, 3, 1, rand()%9+1);
    output_matrix_graph(*mgraph);
    cout<<"Is this graph acyclic? ";
    if (is_cyclic_matr(*mgraph)) {cout<<"no, it has cycle."<<endl;}
    else {cout<<"yes. "<<endl;}

    cout<<"Unit 2:"<<endl;
    output_matrix_graph(*mgraph);
    cout<<"BFS by number of vertex: ";
    bfs_matr(*mgraph, false);
    cout<<"BFS by weight: ";
    bfs_matr(*mgraph, true);

    cout<<"Unit 3:"<<endl;
    output_matrix_graph(*mgraph);
    cout<<"Floyd's algorithm."<<endl;
    cout<<"Minimal distance between all vertices in graph: "<<endl;
    vector<vector<int>> result = Floyd_matr(*mgraph);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result.size(); j++) {
            cout<<result[i][j]<<"  ";
        }
        cout<<endl;
    }
    int vert1 = rand()%((*mgraph).vertex_count);
    cout<<"Minimal distance between vertex "<<vert1<<" and all other vertices:"<<endl;
    result[0] = Floyd_matr_all_for_one(*mgraph, vert1);
    for (int i = 0; i < (*mgraph).vertex_count; i++) {
        cout<<result[0][i]<<"  ";
    }
    cout<<endl;
    int vert2 = rand()%((*mgraph).vertex_count);
    vert1 =  rand()%((*mgraph).vertex_count);
    cout<<"Minimal distance between vertex "<<vert1<<" and vertex "<<vert2<<" : "
        <<Floyd_matr_between_two(*mgraph, vert1,vert2)<<endl;

    cout<<"Unit 4: "<<endl;
    while (is_cyclic_matr(*mgraph)) {mgraph = create_random_matrg(6,6,true);}
    output_matrix_graph(*mgraph);
    cout<<"Topological sort by dfs."<<endl;
    result[0] = topological_sort_matr(*mgraph);
    if (!result[0].empty()) {
        for (int i = 0; i < (*mgraph).vertex_count; i++) {
            cout << result[0][i] << "  ";
        }
        cout << endl;
    }

    cout<<"Unit 5: "<<endl;
    mgraph = create_random_matrg(6,10,false,true);
    output_matrix_graph(*mgraph);
    graph_matrix* matr_result = bfs_matr_for_span(*mgraph);
    cout<<"Spanning tree bfs by number."<<endl;
    output_matrix_graph(*matr_result);
    cout<<"Weight of tree: "<<weight_of_matr_graph(*matr_result)<<endl;
    matr_result = bfs_matr_for_span(*mgraph, true);
    cout<<"Spanning tree bfs by weight."<<endl;
    output_matrix_graph(*matr_result);
    cout<<"Weight of tree: "<<weight_of_matr_graph(*matr_result)<<endl;

    cout<<"Unit 6: "<<endl;
    cout<<"Minimal spanning tree by Boruvka's algorithm:"<<endl;
    matr_result = boruvka_matr(*mgraph);
    output_matrix_graph(*matr_result);
    cout<<"Weight of tree: "<<weight_of_matr_graph(*matr_result)<<endl;

    cout<<"2. Graph represented as structure."<<endl;
    cout<<"Unit 0:"<<endl;
    verts = rand()%5+5;
    edges = rand()%10;
    cout<<"created random oriented weighed graph with "<<verts<<" vertices and "<<edges<<" egdes:"<<endl;
    sgraph = create_random_structg(verts, edges, true, true);
    output_struct_graph(*sgraph);

    demonstration_add_to_struct(*sgraph, verts);
    demonstration_add_to_struct(*sgraph, verts);
    demonstration_add_to_struct(*sgraph, verts);
    demonstration_add_to_struct(*sgraph, verts);

    cout<<"transform structure to matrix representation: "<<endl;
    mgraph = struct_to_matr(*sgraph);
    output_matrix_graph(*mgraph);

    cout<<"Unit 1:"<<endl;
    output_struct_graph(*sgraph);
    cout<<"Is this graph acyclic? ";
    if (is_cyclic_str(*sgraph)) {cout<<"no, it has cycle."<<endl;}
    else {cout<<"yes. "<<endl;}
    cout<<"Adding cycle to graph 1-2-3-1:"<<endl;
    add_to_struct(*sgraph, 1, 2, rand()%9+1);
    add_to_struct(*sgraph, 2, 3, rand()%9+1);
    add_to_struct(*sgraph, 3, 1, rand()%9+1);
    output_struct_graph(*sgraph);
    cout<<"Is this graph acyclic? ";
    if (is_cyclic_str(*sgraph)) {cout<<"no, it has cycle."<<endl;}
    else {cout<<"yes. "<<endl;}

    cout<<"Unit 2:"<<endl;
    output_struct_graph(*sgraph);
    cout<<"BFS by number of vertex: ";
    bfs_struct(*sgraph, false);
    cout<<"BFS by weight: ";
    bfs_struct(*sgraph, true);

    cout<<"Unit 3:"<<endl;
    output_struct_graph(*sgraph);
    cout<<"Floyd's algorithm."<<endl;
    cout<<"Minimal distance between all vertices in graph: "<<endl;
    result = Floyd_struct(*sgraph);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result.size(); j++) {
            cout<<result[i][j]<<"  ";
        }
        cout<<endl;
    }
    vert1 = rand()%((*sgraph).vertex_count);
    cout<<"Minimal distance between vertex "<<vert1<<" and all other vertices:"<<endl;
    result[0] = Floyd_struct_all_for_one(*sgraph, vert1);
    for (int i = 0; i < (*sgraph).vertex_count; i++) {
        cout<<result[0][i]<<"  ";
    }
    cout<<endl;
    vert2 = rand()%((*sgraph).vertex_count);
    vert1 =  rand()%((*sgraph).vertex_count);
    cout<<"Minimal distance between vertex "<<vert1<<" and vertex "<<vert2<<" : "
    <<Floyd_struct_between_two(*sgraph, vert1,vert2)<<endl;

    cout<<"Unit 4: "<<endl;
    while (is_cyclic_str(*sgraph)) {sgraph = create_random_structg(6,6,true);}
    output_struct_graph(*sgraph);
    cout<<"Topological sort by dfs."<<endl;
    result[0] = topological_sort_struct(*sgraph);
    if (!result[0].empty()) {
        for (int i = 0; i < (*sgraph).vertex_count; i++) {
            cout << result[0][i] << "  ";
        }
        cout << endl;
    }

    cout<<"Unit 5: "<<endl;
    sgraph = create_random_structg(6,10,false,true);
    output_struct_graph(*sgraph);
    graph_struct* struct_result = bfs_struct_for_span(*sgraph);
    cout<<"Spanning tree bfs by number."<<endl;
    output_struct_graph(*struct_result);
    cout<<"Weight of tree: "<<weight_of_struct_graph(*struct_result)<<endl;
    struct_result = bfs_struct_for_span(*sgraph, true);
    cout<<"Spanning tree bfs by weight."<<endl;
    output_struct_graph(*struct_result);
    cout<<"Weight of tree: "<<weight_of_struct_graph(*struct_result)<<endl;

    cout<<"Unit 6: "<<endl;
    cout<<"Minimal spanning tree by Boruvka's algorithm:"<<endl;
    struct_result = boruvka_struct(*sgraph);
    output_struct_graph(*struct_result);
    cout<<"Weight of tree: "<<weight_of_struct_graph(*struct_result)<<endl;

}

void interactive();
void interactive_matrix(graph_matrix**);
void interactive_struct(graph_struct**);

void interactive_matrix (graph_matrix** graph) {
    int mode = 0;

    string name;
    cout<<"Create new graph - enter 1"<<endl;
    cout<<"Add edge to the graph - enter 2"<<endl;
    cout<<"Output graph - enter 3"<<endl;
    cout<<"Create random graph - enter 4"<<endl;
    cout<<"Transform graph to struct representation - enter 5"<<endl;
    cout<<"Check if graph is acyclic - enter 6"<<endl;
    cout<<"Travel through the graph - enter 7"<<endl;
    cout<<"Find minimal distances (Floyd's algorithm) - enter 8"<<endl;
    cout<<"Topological sort (by dfs)) - enter 9"<<endl;
    cout<<"Create spanning tree (by bfs)) - enter 10"<<endl;
    cout<<"Create minimal spanning tree (Boruvka's algorithm)) - enter 11"<<endl;
    cout<<"Back to main menu - enter 0"<<endl;
    cin>>mode;

    switch(mode) {
        case 0: {
            interactive();
            return;
        }
        case 1: {
            cout<<"Enter number of vertices"<<endl;
            int amount;
            cin>>amount;
            *graph = new graph_matrix(amount);
            cout<<"Is graph oriented?"<<endl;
            string properties;
            cin>>properties;
            if (properties == "yes") {(*graph)->is_oriented = true;}
            else {(*graph)->is_oriented = false;}
            break;
        }
        case 2: {
            cout<<"Enter vertices to connect and weight of edge"<<endl;
            int vert1, vert2, weight;
            cin>>vert1>>vert2>>weight;
            add_to_matr(**graph, vert1, vert2, weight);
            break;
        }
        case 3: {
            output_matrix_graph(**graph);
            break;
        }
        case 4: {
            cout<<"Enter number of vertices and edges"<<endl;
            int vertices, edges;
            cin>>vertices>>edges;
            bool oriented = false;
            cout<<"Is graph oriented?"<<endl;
            string answer;
            cin>>answer;
            if (answer == "yes") {oriented = true;}
            cout<<"Is graph weighted?"<<endl;
            cin>>answer;
            if (answer == "yes") {*graph = create_random_matrg(vertices, edges, oriented,true);}
            else {*graph = create_random_matrg(vertices, edges, oriented);}
            break;
        }
        case 5: {
            graph_struct* graph_str = matr_to_struct(**graph);
            output_struct_graph(*graph_str);
            cout<<"Would you like to work with the struct graph now?"<<endl;
            string answer;
            cin>>answer;
            if (answer == "yes") {
                interactive_struct(&graph_str);
                return;
            }
            break;
        }
        case 6: {
            cout<<"Is graph acyclic?"<<endl;
            if (is_cyclic_matr(**graph)) {cout<<"no";}
            else {cout<<"yes";}
            break;
        }
        case 7: {
            int option;
            cout<<"For travel by number enter 1"<<endl;
            cout<<"For travel by weight enter 2"<<endl;
            cin>>option;
            if (option == 1) {bfs_matr(**graph, false);}
            if (option == 2) {bfs_matr(**graph, true);}
            break;
        }
        case 8: {
            int option;
            cout<<"For finding all the minimum distance enter 1"<<endl;
            cout<<"For finding all minimum distances for one vertex enter 2"<<endl;
            cout<<"For finding minimum distance between two vertices enter 3"<<endl;
            cin>>option;
            if (option == 1) {
                vector<vector<int>> result = Floyd_matr(**graph);
                for (int i = 0; i < result.size(); i++) {
                    for (int j = 0; j < result.size(); j++) {
                        cout<<result[i][j]<<"  ";
                    }
                    cout<<endl;
                }
            }
            if (option == 2) {
                int vert;
                cout << "Enter vertex" << endl;
                cin>>vert;
                vector<int> result = Floyd_matr_all_for_one(**graph, vert);
                for (int i = 0; i < (**graph).vertex_count; i++) {
                    cout << result[i] << "  ";
                }
                cout << endl;
            }
            if (option == 3) {
                int vert1, vert2;
                cout<<"Enter two vertices"<<endl;
                cin>>vert1>>vert2;
                cout <<Floyd_matr_between_two(**graph, vert1,vert2)<<endl;
            }
            break;
        }
        case 9: {
            vector<int> result = topological_sort_matr(**graph);
            if (!result.empty()) {
                for (int i = 0; i < (**graph).vertex_count; i++) {
                    cout << result[i] << "  ";
                }
                cout << endl;
            }
            break;
        }
        case 10: {
            int option;
            cout<<"For finding spanning tree by number enter 1"<<endl;
            cout<<"For finding spanning tree by weight enter 2"<<endl;
            cin>>option;
            if (option == 1) {
                graph_matrix* matr_result = bfs_matr_for_span(**graph);
                output_matrix_graph(*matr_result);
                cout<<"Weight of tree: "<<weight_of_matr_graph(*matr_result)<<endl;
            }
            if (option == 2) {
                graph_matrix* matr_result = bfs_matr_for_span(**graph, true);
                output_matrix_graph(*matr_result);
                cout<<"Weight of tree: "<<weight_of_matr_graph(*matr_result)<<endl;
            }
            break;
        }
        case 11: {
            graph_matrix* matr_result = boruvka_matr(**graph);
            output_matrix_graph(*matr_result);
            cout<<"Weight of tree: "<<weight_of_matr_graph(*matr_result)<<endl;
            break;
        }
        default: {
            cout<<"Wrong number!"<<endl;
            break;
        }
    }
    interactive_matrix(graph);
}
void interactive_struct (graph_struct** graph) {
    int mode = 0;

    string name;
    cout<<"Create new graph - enter 1"<<endl;
    cout<<"Add edge to the graph - enter 2"<<endl;
    cout<<"Output graph - enter 3"<<endl;
    cout<<"Create random graph - enter 4"<<endl;
    cout<<"Transform graph to matrix representation - enter 5"<<endl;
    cout<<"Check if graph is acyclic - enter 6"<<endl;
    cout<<"Travel through the graph - enter 7"<<endl;
    cout<<"Find minimal distances (Floyd's algorithm) - enter 8"<<endl;
    cout<<"Topological sort (by dfs)) - enter 9"<<endl;
    cout<<"Create spanning tree (by bfs)) - enter 10"<<endl;
    cout<<"Create minimal spanning tree (Boruvka's algorithm)) - enter 11"<<endl;
    cout<<"Back to main menu - enter 0"<<endl;
    cin>>mode;

    switch(mode) {
        case 0: {
            interactive();
            return;
        }
        case 1: {
            cout<<"Enter number of vertices"<<endl;
            int amount;
            cin>>amount;
            *graph = new graph_struct(amount);
            cout<<"Is graph oriented?"<<endl;
            string properties;
            cin>>properties;
            if (properties == "yes") {(*graph)->is_oriented = true;}
            else {(*graph)->is_oriented = false;}
            break;
        }
        case 2: {
            cout<<"Enter vertices to connect and weight of edge"<<endl;
            int vert1, vert2, weight;
            cin>>vert1>>vert2>>weight;
            add_to_struct(**graph, vert1, vert2, weight);
            break;
        }
        case 3: {
            output_struct_graph(**graph);
            break;
        }
        case 4: {
            cout<<"Enter number of vertices and edges"<<endl;
            int vertices, edges;
            cin>>vertices>>edges;
            bool oriented = false;
            cout<<"Is graph oriented?"<<endl;
            string answer;
            cin>>answer;
            if (answer == "yes") {oriented = true;}
            cout<<"Is graph weighted?"<<endl;
            cin>>answer;
            if (answer == "yes") {*graph = create_random_structg(vertices, edges, oriented,true);}
            else {*graph = create_random_structg(vertices, edges, oriented);}
            break;
        }
        case 5: {
            graph_matrix* graph_matr = struct_to_matr(**graph);
            output_matrix_graph(*graph_matr);
            cout<<"Would you like to work with the matrix graph now?"<<endl;
            string answer;
            cin>>answer;
            if (answer == "yes") {
                interactive_matrix(&graph_matr);
                return;
            }
            break;
        }
        case 6: {
            cout<<"Is graph acyclic?"<<endl;
            if (is_cyclic_str(**graph)) {cout<<"no";}
            else {cout<<"yes";}
            break;
        }
        case 7: {
            int option;
            cout<<"For travel by number enter 1"<<endl;
            cout<<"For travel by weight enter 2"<<endl;
            cin>>option;
            if (option == 1) {bfs_struct(**graph, false);}
            if (option == 2) {bfs_struct(**graph, true);}
            break;
        }
        case 8: {
            int option;
            cout<<"For finding all the minimum distance enter 1"<<endl;
            cout<<"For finding all minimum distances for one vertex enter 2"<<endl;
            cout<<"For finding minimum distance between two vertices enter 3"<<endl;
            cin>>option;
            if (option == 1) {
                vector<vector<int>> result = Floyd_struct(**graph);
                for (int i = 0; i < result.size(); i++) {
                    for (int j = 0; j < result.size(); j++) {
                        cout<<result[i][j]<<"  ";
                    }
                    cout<<endl;
                }
            }
            if (option == 2) {
                int vert;
                cout << "Enter vertex" << endl;
                cin>>vert;
                vector<int> result = Floyd_struct_all_for_one(**graph, vert);
                for (int i = 0; i < (**graph).vertex_count; i++) {
                    cout << result[i] << "  ";
                }
                cout << endl;
            }
            if (option == 3) {
                int vert1, vert2;
                cout<<"Enter two vertices"<<endl;
                cin>>vert1>>vert2;
                cout <<Floyd_struct_between_two(**graph, vert1,vert2)<<endl;
            }
            break;
        }
        case 9: {
            vector<int> result = topological_sort_struct(**graph);
            if (!result.empty()) {
                for (int i = 0; i < (**graph).vertex_count; i++) {
                    cout << result[i] << "  ";
                }
                cout << endl;
            }
            break;
        }
        case 10: {
            int option;
            cout<<"For finding spanning tree by number enter 1"<<endl;
            cout<<"For finding spanning tree by weight enter 2"<<endl;
            cin>>option;
            if (option == 1) {
                graph_struct* result = bfs_struct_for_span(**graph);
                output_struct_graph(*result);
                cout<<"Weight of tree: "<<weight_of_struct_graph(*result)<<endl;
            }
            if (option == 2) {
                graph_struct* result = bfs_struct_for_span(**graph, true);
                output_struct_graph(*result);
                cout<<"Weight of tree: "<<weight_of_struct_graph(*result)<<endl;
            }
            break;
        }
        case 11: {
            graph_struct* result = boruvka_struct(**graph);
            output_struct_graph(*result);
            cout<<"Weight of tree: "<<weight_of_struct_graph(*result)<<endl;
            break;
        }
        default: {
            cout<<"Wrong number!"<<endl;
            break;
        }
    }
    interactive_struct(graph);
}
int interactive_options() {
    int mode = 0;
    cout<<"Work with matrix representation - enter 1"<<endl;
    cout<<"Work with struct representation - enter 2"<<endl;
    cout<<"Exit - enter 0"<<endl;
    cin>>mode;
    return mode;
}
void interactive() {
    int mode = 0;
    mode = interactive_options();
    switch(mode) {
        case 0: {
            return;
        }
        case 1: {
            graph_matrix* graph = nullptr;
            interactive_matrix(&graph);
            break;
        }
        case 2: {
            graph_struct* graph = nullptr;
            interactive_struct(&graph);
            break;
        }
        default: {
            cout<<"Wrong number!"<<endl;
        }
    }
}

void benchmark() {
        int count;
        clock_t benchmark_clock;
        ofstream benchmark_results_file;
        benchmark_results_file.open("benchmark_result.txt");

        benchmark_results_file<<"Results with matrix:"<<"\r\n";
        count = 10;
        while  (count <= max_vert_count) {
            benchmark_clock = clock();
            int verts = count;
            int edges = count*count/4;

            graph_matrix* mgraph = create_random_matrg(verts, edges, true, true);
            matr_to_struct(*mgraph);
            is_cyclic_matr(*mgraph);
            Floyd_matr(*mgraph);
            int vert1 = rand()%((*mgraph).vertex_count);
            Floyd_matr_all_for_one(*mgraph, vert1);
            int vert2 = rand()%((*mgraph).vertex_count);
            vert1 =  rand()%((*mgraph).vertex_count);
            Floyd_matr_between_two(*mgraph, vert1,vert2);
            if (!is_cyclic_matr(*mgraph)) topological_sort_matr(*mgraph);
            bfs_matr_for_span(*mgraph);
            bfs_matr_for_span(*mgraph, true);
            boruvka_matr(*mgraph);


            benchmark_results_file<<count<<' '<<((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC)<<"\r\n";
            cout<<count<<' '<<((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC)<<endl;

            if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) > 10) {break;}
            count += 20;

        }

        benchmark_results_file<<"Results with struct:"<<"\r\n";
        count = 10;
    while  (count <= max_vert_count) {
        benchmark_clock = clock();
        int verts = count;
        int edges = count*count/4;

        graph_struct* graph = create_random_structg(verts, edges, true, true);
        struct_to_matr(*graph);
        is_cyclic_str(*graph);
        Floyd_struct(*graph);
        int vert1 = rand()%((*graph).vertex_count);
        Floyd_struct_all_for_one(*graph, vert1);
        int vert2 = rand()%((*graph).vertex_count);
        vert1 =  rand()%((*graph).vertex_count);
        Floyd_struct_between_two(*graph, vert1,vert2);
        if (!is_cyclic_str(*graph)) topological_sort_struct(*graph);
        bfs_struct_for_span(*graph);
        bfs_struct_for_span(*graph, true);
        boruvka_struct(*graph);

        benchmark_results_file<<count<<' '<<((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC)<<"\r\n";
        cout<<count<<' '<<((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC)<<endl;

        if (((double) (clock() - benchmark_clock) / CLOCKS_PER_SEC) > 10) {break;}
        count += 20;

    }
}

int main() {
    srand(time(0));

    int mode;
    cout << "For interactive mode enter 1" << endl;
    cout << "For demonstration mode enter 2" << endl;
    cout << "For benchmark mode enter 3" << endl;
    cin>>mode;
    if (mode == 1) {interactive();}
    if (mode == 2) {demonstration();}
    if (mode == 3) {benchmark();}


    return 0;
}