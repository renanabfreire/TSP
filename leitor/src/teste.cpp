#include "Ils.h"
#include <iostream>
using namespace std;


int main(int argc, char** argv) {

    //Comandos necessarios para leitura da instancia
    auto data = Data(argc, argv[1]);
    data.read();
    
    Solution s = Construcao(data.getDimension(), data.getMatrixCost());

    for(int i = 0; i < (s.sequence.size() - 1); i++)
        std::cout << s.sequence[i] << " -> ";
    std::cout << s.sequence.back() << std::endl;
    
    cout << s.value << endl;
    
    return 0;
}
