#include <iostream>
#include <cstdio>
#include <sstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    FILE* inputFile = fopen("data/post1.txt", "r");  // Replace "file.txt" with the actual path to your file
    std::unordered_map<int, std::unordered_map<std::string, int>> docStemMap;

    // Step 1: Read the file and populate the document-stem map
    char line[256];
    int maxDocId = 0;
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        std::istringstream iss(line);
        std::string stem;
        int docid;
        iss >> stem >> docid;

        docStemMap[docid][stem]++;
        maxDocId = std::max(maxDocId, docid);
    }

    fclose(inputFile);

    // Step 2: Form the document
    std::ostringstream document;

    for (int docid = 0; docid <= maxDocId; docid++) {
        if (docStemMap.find(docid) != docStemMap.end()) {
            document << docid << " : ";

            for (const auto& stemCount : docStemMap[docid]) {
                const std::string& stem = stemCount.first;
                int occurrence = stemCount.second;

                document << stem  << " " << occurrence << ", ";
            }

            // Remove the trailing comma and space
            document.seekp(-2, std::ios_base::end);
            document << '\n';
        }
    }

    // Step 3: Output the document to a file
    FILE* outputFile = fopen("FormattedFile.txt", "w");

    if (outputFile != NULL) {
        fprintf(outputFile, "%s", document.str().c_str());
        fclose(outputFile);
        std::cout << "Formatted document has been written to FormattedFile.txt" << std::endl;
    } else {
        std::cerr << "Unable to open the output file." << std::endl;
    }

    return 0;
}