#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

// Vectors of all stations in metro path
const vector<string> stations = {
    // Blue Line Stops
    "Versova", "D.N. Nagar", "Azad Nagar", "Andheri", "Western Express Highway", "Chakala", "Airport Road", 
    "Marol Naka (blue)", "Saki Naka", "Asalpha", "Jagruti Nagar", "Ghatkopar", 
    // Yellow Line Stops
    "Dahisar(E) (yellow)", "Anand Nagar", "Kandarpala", "Mandapeshwar", "Eksar", "Borivali(W)", "Shimpoli", "Kandivali(W)", 
    "Dahanukarwadi", "Valnai", "Malad(W)", "Lower Malad", "Bangur Nagar", "Goregaon(W)", "Oshiwara", 
    "Lower Oshiwara", "Andheri(W)",
    // Red Line Stops
    "Dahisar(E) (red)", "Ovaripada", "Rashtriya Udyan", "Devipada", "Magathane", "Poisar", "Akurli", "Kurar", 
    "Dindoshi", "Aarey", "Goregaon(E)", "Jogeshwari(E)", "Mogra", "Gundavali",
    // Aqua Line Stops
    "Aarey JVLR", "MIDC Andheri", "Marol Naka (aqua)", "CSMI Airport T2", "Sahar Road", "CSMI Airport T1", 
    "Santacruz Metro", "Bandra Colony", "Bandra Kurla Complex"
};

// Calculating shortest path with dijkstra algorithm
void shortestPathBFS(const vector<vector<int>>& adj, int src) 
{
    int n = stations.size();
    vector<int> dist(n, INT_MAX);
    queue<int> q;
    // Initializing all distances to be zero initially
    dist[src] = 0;
    q.push(src);
    // Pushing distances into the queues
    while (!q.empty()) 
    {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) 
        {
            if (dist[v] > dist[u] + 1) 
            {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    // Displaying the shortest number of stops from current station
    cout << "\nShortest stops from " << stations[src] << ":\n";
    for (int i = 0; i < n; i++) 
        cout << stations[i] << ": " << dist[i] << " stops\n";
}

int main() 
{
    const int n = stations.size();
    vector<vector<int>> adj(n);
    unordered_map<string, int> stationIndex;
    // Create station index mapping
    for (int i = 0; i < n; i++) 
        stationIndex[stations[i]] = i;
    // Blue Line connections
    vector<int> blueLine = {0,1,2,3,4,5,6,7,8,9,10,11};
    for (int i = 0; i < blueLine.size(); i++) 
    {
        if (i > 0) adj[blueLine[i]].push_back(blueLine[i-1]);
        if (i < blueLine.size()-1) adj[blueLine[i]].push_back(blueLine[i+1]);
    }
    // Yellow Line connections
    vector<int> yellowLine = {12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};
    for (int i = 0; i < yellowLine.size(); i++) 
    {
        if (i > 0) adj[yellowLine[i]].push_back(yellowLine[i-1]);
        if (i < yellowLine.size()-1) adj[yellowLine[i]].push_back(yellowLine[i+1]);
    }
    // Connection between Andheri West and D N Nagar stop
    adj[1].push_back(stationIndex["Andheri(W)"]);
    adj[28].push_back(stationIndex["D.N. Nagar"]);  
    // Red Line connections
    vector<int> redLine = {29,30,31,32,33,34,35,36,37,38,39,40,41,42};
    for (int i = 0; i < redLine.size(); i++) 
    {
        if (i > 0) adj[redLine[i]].push_back(redLine[i-1]);
        if (i < redLine.size()-1) adj[redLine[i]].push_back(redLine[i+1]);
    }
    // Connection between Dahisar East stop on yellow and red lines
    adj[12].push_back(stationIndex["Dahisar(E) (red)"]);
    adj[29].push_back(stationIndex["Dahisar(E) (yellow)"]);
    // Connection between Gundavali and Western Express Highway
    adj[4].push_back(stationIndex["Gundavali"]);
    adj[42].push_back(stationIndex["Western Express Highway"]);
    // Aqua Line connections
    vector<int> aquaLine = {43,44,45,46,47,48,49,50,51};
    for (int i = 0; i < aquaLine.size(); i++) 
    {
        if (i > 0) adj[aquaLine[i]].push_back(aquaLine[i-1]);
        if (i < aquaLine.size()-1) adj[aquaLine[i]].push_back(aquaLine[i+1]);
    }
    // Connection between Marol Naka stop on blue and aqua lines
    adj[7].push_back(stationIndex["Marol Naka (aqua)"]);
    adj[45].push_back(stationIndex["Marol Naka (blue)"]);
    // Display station menu
    cout << "Mumbai Metro Stations:\n";
    for (int i = 0; i < n; i++) 
        cout << i << ": " << stations[i] << "\n";
    // Get user input
    cout << "\nEnter source station number: ";
    int src;
    cin >> src;
    if (src < 0 || src >= n) 
    {
        cerr << "Invalid station number!";
        return 1;
    }
    // Calculate and display paths
    shortestPathBFS(adj, src);
    return 0;
}