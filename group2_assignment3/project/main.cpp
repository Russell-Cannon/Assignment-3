#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono> 
#include <iomanip>

#include "Digraph.h" 
#include "ResizingArray.h"

// Functions to get input 
void getSourcesInput(int sources[], int size, int numVertices, std::ofstream& logFile);
void getDestinationInput(int &destination, int numVertices, std::ofstream& logFile);

int main(int argc, char *argv[]) {
    //Open input file
    char fileName[32];
    if (argc < 2) { //If the user forgot to provide a filename
        std::cout << "Enter filename: ";
        std::cin >> fileName;
    } else 
        strcpy(fileName, argv[1]); //Copy terminal argument to the filename

    std::ifstream fin(fileName);

    if (!fin) {
        std::cerr << "Error: Unable to find '" << fileName << "'\n";
        return 1;
    }

    //Populate digraph from input stream
    Digraph digraph(fin);

    // Creating log file
    std::ofstream logFile("log.txt");
    if (!logFile) {
        std::cerr << "Error: Unable to open log file." << std::endl;
        return 1;
    }

    // Start timing overall run
    auto overallStart = std::chrono::high_resolution_clock::now();

    // Log the current date and time using chrono and std::put_time (from iomanip)   *Stack Overflow
    auto current_time = std::chrono::system_clock::now();
    std::time_t dateTime = std::chrono::system_clock::to_time_t(current_time);
    logFile << "Date and Time of Run: " << std::put_time(std::localtime(&dateTime), "%F %T") << "\n";
    
    
    // Prompt user for three source vertices
    const int source_size = 3;
    int sources[source_size];
    int num_of_vertices = digraph.getSize();
    getSourcesInput(sources, source_size, num_of_vertices, logFile);

    // Main interactive loop
    int destination;
    int searchCount = 1;
    bool found = false;
    while (true) {
        std::cout << "Search " << searchCount << "\n";
        logFile << "Search " << searchCount << "\n";
        getDestinationInput(destination, num_of_vertices, logFile); // Get user input for destination node
        // Exit loop when user enters a negative number
        if (destination < 0) {
            logFile << "\nExiting search loop.\n";
            break;
        }
        logFile << "Searching for shortest path to destination: " << destination << "\n";

        // For each source vertex, perform the shortest path search
        for (int i = 0; i < 3; i++) {
            // Timing for shortest path search
            auto startTime = std::chrono::high_resolution_clock::now(); // Start clocking time search

            ResizingArray<int>* path = digraph.BFS(sources[i], destination);

            auto endTime = std::chrono::high_resolution_clock::now();   // End clocking time of search

            long long searchDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count(); // Duration of search in nano seconds

            // log and display the result, if found
            if (path != nullptr) {
                std::cout << "Shortest Path from vertex " << sources[i] << " to " << destination << ": ";
                logFile << "Shortest Path from vertex " << sources[i] << " to " << destination << ": ";

                // log and display path
                for (int j = 0; j < (*path).getSize(); j++) {
                    if (j != 0) {
                        std::cout << " -> ";
                        logFile << " -> ";
                    }
                    std::cout << (*path)[j];
                    logFile << (*path)[j];
                }

                // display and log time to find path in nanoseconds
                std::cout << " (Time: " << searchDuration << " ns)" << std::endl;
                logFile << " (Time: " << searchDuration << " ns)" << "\n";
            } 
            else {
                std::cout << "No path from vertex " << sources[i] << " to " << destination << " found" << std::endl;
                logFile << "No path from vertex " << sources[i] << " to " << destination << " found\n";
            }

            // deallocate path array
            if (path != nullptr) {  
                delete path;
                path = nullptr; 
            }
        }
        logFile << "\n"; // new line to separate each set of searches in log file
        searchCount++;
    }

    
    // termination message
    std::cout << "Program terminated. Refer to log.txt for run log" << std::endl;
    logFile << "Program terminated.\n";
    
    // log overall runtime
    auto overallEnd = std::chrono::high_resolution_clock::now();
    double overallDuration = std::chrono::duration_cast<std::chrono::seconds>(overallEnd - overallStart).count();
    logFile << "Overall runtime: " << overallDuration << " seconds\n";

    // close log file
    logFile.close();

    return 0;
}

void getSourcesInput(int sources[], int size, int numVertices, std::ofstream &logFile) {
    logFile << "User entering source vertices\n";
    for (int i = 0; i < size; i++) {
        bool valid = false;
        while (!valid) {
            std::cout << "Enter source vertex " << (i + 1) << ": ";
            std::cin >> sources[i];
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "Invalid input. Please enter an integer between 0 and " << numVertices - 1 << ".\n";
                logFile << "Invalid input entered\n";
                continue;
            } 
            if (sources[i] < 0 || sources[i] >= numVertices) {
                std::cout<< "Error! source vertex must be in range of: 0 to " << numVertices - 1 << ". Please try again\n";
                logFile << "Out of range input entered: " << sources[i] << "\n";
                continue; 
            }
            logFile << "User entered " << sources[i] << " for Source vertex " << (i + 1) << "\n";
            valid = true;
        }
    }
    logFile << "\n";
}

void getDestinationInput(int& destination, const int num_vertices, std::ofstream& file) {
    file << "User entering destination vertex\n";
    bool valid = false;
    while (!valid) {
        std::cout << "Please enter the destination vertex to search for: ";
        std::cin >> destination;
        
        if (std::cin.fail()) {
            std::cout<< "Error! Invalid input. Please enter an integer value\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            file << "Invalid input entered\n";
            continue;
        }

        if (destination >= num_vertices) {
            std::cout<< "Error! destination vertex must be in range of: 0 to " << num_vertices - 1 << " or a negative number to exit.\n";
            file << "Out of range input entered: " << destination << "\n";
            continue;
        }

        if (destination < 0) {
            file << "User entered " << destination << " to exit search loop\n";
            valid = true;
        }
        else {
            file << "User entered " << destination << " as the destination vertex\n";
            valid = true;
        }
    }

}