#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void normalizeCsvLineEndings(const std::string& filePath) {
    // 1. Lecture du fichier original en mode binaire
    std::ifstream inFile(filePath, std::ios::binary);
    if (!inFile) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
        return;
    }

    std::vector<char> buffer;
    char ch;
    while (inFile.get(ch)) {
        // On ignore le retour chariot (\r), on ne garde que le saut de ligne (\n)
        if (ch != '\r') {
            buffer.push_back(ch);
        }
    }
    inFile.close();

    // 2. Réécriture du fichier sous le même nom
    std::ofstream outFile(filePath, std::ios::binary | std::ios::trunc);
    if (!outFile) {
        std::cerr << "Erreur : Impossible de sauvegarder le fichier." << std::endl;
        return;
    }

    outFile.write(buffer.data(), buffer.size());
    outFile.close();

    std::cout << "Succes : Le fichier a ete normalise (LF uniquement)." << std::endl;
}

int main() {
    std::string path;
    std::cout << "--- Nettoyeur de CSV (Suppression des \\r) ---" << std::endl;
    std::cout << "Entrez le chemin complet du fichier .csv : ";
    std::getline(std::cin, path);

    // Nettoyage rapide des guillemets si l'utilisateur a fait un glisser-déposer
    if (!path.empty() && (path.front() == '"' || path.front() == '\'')) {
        path = path.substr(1, path.length() - 2);
    }

    normalizeCsvLineEndings(path);

    return 0;
}
