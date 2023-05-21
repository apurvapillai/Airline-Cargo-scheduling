#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Flight {
    string source;
    string destination;
};

vector<string> findPath(const unordered_map<string, vector<Flight>>& flights, string source, string destination) {
    if (source == destination)
        return { source };

    if (flights.find(source) == flights.end())
        return {};

    for (const Flight& flight : flights.at(source)) {
        vector<string> path = findPath(flights, flight.destination, destination);
        if (!path.empty()) {
            path.insert(path.begin(), source);
            return path;
        }
    }

    return {};
}

int main() {
    int numFlights;
    cout << "Enter the number of flights: ";
    cin >> numFlights;

    unordered_map<string, vector<Flight>> flights;

    cout << "Enter the details of each flight:\n";
    for (int i = 0; i < numFlights; ++i) {
        string source, destination;
        cout << "Flight " << i + 1 << " - Source: ";
        cin >> source;
        cout << "         - Destination: ";
        cin >> destination;
        flights[source].push_back({ source, destination });
    }

    int numCargoSets;
    cout << "\nEnter the number of cargo sets: ";
    cin >> numCargoSets;

    unordered_map<string, vector<int>> cargoSets;

    cout << "Enter the details of each cargo set:\n";
    for (int i = 0; i < numCargoSets; ++i) {
        string source, destination;
        int numCargos;
        cout << "Cargo Set " << i + 1 << " - Source: ";
        cin >> source;
        cout << "            - Destination: ";
        cin >> destination;
        cout << "            - Number of cargos: ";
        cin >> numCargos;
        cargoSets[source + "-" + destination].push_back(numCargos);
    }

    cout << "\nPaths for each cargo set:\n";
    for (const auto& cargoSet : cargoSets) {
        const string& source = cargoSet.first.substr(0, cargoSet.first.find('-'));
        const string& destination = cargoSet.first.substr(cargoSet.first.find('-') + 1);
        const vector<int>& cargos = cargoSet.second;

        vector<string> path = findPath(flights, source, destination);

        if (!path.empty()) {
            cout << "Cargo Set (" << source << " to " << destination << ") - Path: ";
            for (size_t i = 0; i < path.size() - 1; ++i) {
                cout << path[i] << " -> ";
            }
            cout << path.back() << endl;

            cout << "                   - Number of cargos: " << cargos[0] << endl;
        }
    }

    return 0;
}
