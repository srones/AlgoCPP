 #include <fstream>
 #include <iostream>
 #include <string>
 #define INF 9999999

using namespace std;

void Dijkstras(int src,int n,int adjM[][16],int weight[16],int vertexSet[16],int predecessor[16]){

    // Populate arrays
    for(int i=0;i<n;i++) {
        weight[i]=INF;
        vertexSet[i]=-1;
        predecessor[i]=-1;
    }

    // Initialize loop
    weight[src] = 0;
    int currNode = src;
    int count=0;
    int smallest, smallestNode;
    bool adjacent, inVertexSet;

    // Loop to look at every node:
    while(count<16){
        cout << setw(3) << currNode;
        // Add currNode to vertexSet
        vertexSet[currNode] = 0;

        // For every other node
        for(int U=0;U<n;U++){

            // Check if U is adjacent and not in vertexSet
            adjacent = (adjM[currNode][U] != -1);
            inVertexSet = false;
            if(vertexSet[U] != -1) inVertexSet = true;

            // If so, relax U and assign predecessor[U]
            if(adjacent && !inVertexSet){
                if(weight[U] > weight[currNode] + adjM[currNode][U]){
                    weight[U] = weight[currNode] + adjM[currNode][U];
                    predecessor[U] = currNode;
                }
            }

        }

        // Get the next node by finding smallest out of all nodes not in vertexSet
        smallest = INF;
        for(int i=0;i<n;i++){
            if(vertexSet[i]==-1){
                if(weight[i]<smallest){
                    smallest = weight[i];
                    smallestNode = i;
                }
            }
        }
        currNode = smallestNode;
        count++;

        cout << " [";
        for(int i=0;i<n;i++){
            cout << setw(8) << weight[i];
        }
        cout << "]\n";
    }
}

void readFile(string filename, int tempArr[]){
    ifstream inf;
    inf.open(filename);
    if(inf.fail()) { cerr << "Error opening the input file\n"; exit(1); }
    inf.exceptions(ifstream::failbit | ifstream::badbit);

    // Read from text file into tempArr
    int count = 0;
    int x;
    while(count<500){
        try{ inf>>x; }
        catch(ifstream::failure e){ break; }
        tempArr[count]=x;
        count++;
    }
    inf.close();
}

void printConversions(){
    cout << "Conversion list:\n20 = 0, 23E = 1, 23H = 2, 24 = 3\n30 = 4, 34 = 5, 38 = 6, 39 = 7\n41 = 8, 43 = 9, 45 = 10, 49 = 11\n50 = 12, 52 = 13, 57 = 14, 59 = 15\n\n";
}

int verifyAndConvert(string str){
    if(str == "20") return 0;
    if(str == "23E") return 1;
    if(str == "23H") return 2;
    if(str == "24") return 3;

    if(str == "30") return 4;
    if(str == "34") return 5;
    if(str == "38") return 6;
    if(str == "39") return 7;

    if(str == "41") return 8;
    if(str == "43") return 9;
    if(str == "45") return 10;
    if(str == "49") return 11;

    if(str == "50") return 12;
    if(str == "52") return 13;
    if(str == "57") return 14;
    if(str == "59") return 15;

    return -1;
}

string node2build(int node){
    string buildings[] = {"20", "23E", "23H", "24", "30", "34", "38", "39", "41", "43", "45", "49", "50", "52", "57", "59"};
    return buildings[node];
}

int main(){

    // First read edges from text file into tempArr
    string filename = "campusGraph.txt";
    int tempArr[70];
    readFile(filename,tempArr);

    // Initialize number of nodes
    int const V = tempArr[0];
    cout << "\n# Nodes: " << V << endl;

    // Initialize adjacency matrix
    int adjM[16][16];
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            adjM[i][j] = -1;
        }
    }

    // Populate adjacency matrix
    int v1, v2, cost;
    for(int i=1;i<68;i+=3){
        v1 = tempArr[i];
        v2 = tempArr[i+1];
        cost = tempArr[i+2];
        adjM[v1][v2] = cost;
        adjM[v2][v1] = cost;
    }

    // // print adjM
    // cout << "Adjacency Matrix:\n\n";
    // for(int i=0;i<16;i++){
    //     cout << "[";
    //     for(int j=0;j<16;j++){
    //         cout  << setw(5) << adjM[i][j];
    //     }
    //     cout << "]\n\n";
    // }

    // Prompt user for source and destination locations
    int src,dst;
    bool inputInvalid=true;
    while(inputInvalid){
        string srcStr, dstStr;
        cout << "Enter the source building: ";
        cin >> srcStr;
        cout << "Enter the destination building: ";
        cin >> dstStr;
        src = verifyAndConvert(srcStr);
        dst = verifyAndConvert(dstStr); 
        inputInvalid=false;
        if((src==-1) || (dst==-1)){
            cout << "Invalid inputs. Please refer to accepted inputs:\n\n";
            printConversions();
        }   
    }  

    // Initialize weight[], vertexSet[] and predecessor[]
    int weight[V];
    int vertexSet[V];
    int predecessor[V];

    // Apply Dijkstras algorithm with source node to return weightArr
    cout << "Dijkstras Algorithm:\n\n";
    Dijkstras(src,V,adjM,weight,vertexSet,predecessor);

    // Return shortest path from src to dst
    cout << "\nShortest path from " << node2build(src) << " to " << node2build(dst) << ": " << weight[dst] << endl;

    int currNode=dst;
    cout << node2build(currNode);
    currNode = predecessor[currNode];
    while(currNode != -1){
        cout  << " <- " << node2build(currNode);
        currNode = predecessor[currNode];
    }
    cout << endl;

    return 0;
}
