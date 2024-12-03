#include "Ils.h"

Solution Perturbacao(Solution s, Data &d)
{
    int tam = 2+rand()%int(((s.sequence.size()/10)-1));
    int indice = 1 +rand()%int((s.sequence.size()-tam-2));

    int stam = 2+rand()%int((((s.sequence.size()/10)-1)));
    int sindice = 1 + rand()%int((s.sequence.size()-stam-2));

    while (true)
    {
        if(sindice == indice)
            sindice = 1 + rand()%(s.sequence.size()-stam-1);
        else if (sindice < indice && (sindice+stam) > indice)
            sindice = 1 + rand()%(s.sequence.size()-stam-1);
        else if (sindice < (indice+tam) && (sindice+stam) >= (indice + tam))
            sindice = 1 + rand()%(s.sequence.size()-stam-1);
        else if (sindice > indice && (sindice+stam) <= (indice+tam))
            sindice = 1 + rand()%(s.sequence.size()-stam-1);
        else if(sindice < indice && (sindice+stam) >= (indice+tam))
            sindice = 1 + rand()%(s.sequence.size()-stam-1);
        else
            break;
    }

    int primeiro = s.sequence[indice];
    int prev_primeiro = s.sequence[indice-1];
    int end_primeiro = s.sequence[indice+tam-1];
    int next_primeiro = s.sequence[indice+tam];
    int segundo = s.sequence[sindice];
    int prev_segundo = s.sequence[sindice-1];
    int end_segundo = s.sequence[sindice+stam-1];
    int next_segundo = s.sequence[sindice+stam];

    double delta = -d.getDistance(prev_primeiro, primeiro) + d.getDistance(prev_primeiro, segundo) - d.getDistance(end_primeiro, next_primeiro) + d.getDistance(end_segundo, next_primeiro) - d.getDistance(prev_segundo, segundo) + d.getDistance(prev_segundo, primeiro) - d.getDistance(end_segundo, next_segundo) + d.getDistance(end_primeiro, next_segundo);
    if(next_primeiro == segundo)
        delta = - d.getDistance(prev_primeiro, primeiro) + d.getDistance(prev_primeiro, segundo) - d.getDistance(end_primeiro, segundo) + d.getDistance(end_segundo, primeiro) - d.getDistance(end_segundo, next_segundo) + d.getDistance(end_primeiro, next_segundo);
    else if (next_segundo == primeiro)
        delta =  - d.getDistance(prev_segundo, segundo) + d.getDistance(prev_segundo, primeiro) - d.getDistance(end_segundo, primeiro) + d.getDistance(end_primeiro, segundo) - d.getDistance(end_primeiro, next_primeiro) + d.getDistance(end_segundo, next_primeiro);
    
    //cout << prev_primeiro << " - " << segundo << " - " << end_segundo << " - " << next_primeiro << " - "<< prev_segundo << " - " << primeiro << " - " << end_primeiro << " - " << next_segundo << endl;
    
    std::vector<int> inv(tam);
    //cout << tam << endl;
    std::vector<int> sinv(stam);
    //cout << stam << endl;
   
    for(int i=0; i<tam; i++)
    {
        inv[i] = s.sequence[indice];
        s.sequence.erase(s.sequence.begin()+indice);
    }
    if(indice < sindice)
    {
        for(int i=0; i<stam; i++)
        {
            sinv[i] = s.sequence[sindice-tam];
            s.sequence.erase(s.sequence.begin()+sindice-tam);
        }
        for(int i=0; i<tam; i++)
            s.sequence.insert(s.sequence.begin()+sindice-tam+i, inv[i]);
        for(int i=0; i<stam; i++)
            s.sequence.insert(s.sequence.begin()+indice+i, sinv[i]);
    }
    else
    {
        for(int i=0; i<stam; i++)
        {
            sinv[i] = s.sequence[sindice];
            s.sequence.erase(s.sequence.begin()+sindice);
        }
        for(int i=0; i<stam; i++)
            s.sequence.insert(s.sequence.begin()+indice-stam+i, sinv[i]);
        for(int i=0; i<tam; i++)
            s.sequence.insert(s.sequence.begin()+sindice+i, inv[i]);
    }


    s.value += delta;

    //cout << delta << endl;

    return s;
}