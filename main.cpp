#include <iostream>
#include <fstream>
#include <vector>
#include <nfd.hpp>

void processCsv(const std::string& filePath) {
    std::ifstream inFile(filePath, std::ios::binary);
    if (!inFile) return;

    std::vector<char> buffer;
    char ch;
    while (inFile.get(ch)) {
        if (ch != '\r') buffer.push_back(ch);
    }
    inFile.close();

    std::ofstream outFile(filePath, std::ios::binary | std::ios::trunc);
    outFile.write(buffer.data(), buffer.size());
    outFile.close();
}

int main() {
    NFD_Init();
    nfdu8char_t *outPath;
    nfdu8filteritem_t filters[1] = { { "Fichiers CSV", "csv" } };

    // Ouvre la fenêtre native
    nfdresult_t result = NFD_OpenDialog(&outPath, filters, 1, NULL);

    if (result == NFD_OKAY) {
        processCsv(outPath);
        std::cout << "Fichier traite avec succes !" << std::endl;
        NFD_FreePath(outPath);
    } else {
        std::cout << "Selection annulee." << std::endl;
    }

    NFD_Quit();
    return 0;
}