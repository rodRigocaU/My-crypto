#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

//FUNCION DE CIFRADO DE NUESTRO ALGORITMO DE ENCRIPTACIÓN BASADO EN AES -> CON UN SOLO BLOQUE
string cypher(vector<int> blocks, vector<int> &Nkey)
{

    string key;
    int cont = 1;
    //POR CADA BLOQUE DE 16 SE APLICA UNA MULTIPLICACIÓN
    int ranK = (1 + rand() % 50);
    Nkey.push_back(ranK);

    for (int i = 0; i < blocks.size(); i++)
    {
        int ii = blocks[i];
        int num;
#ifdef debug
        cout << "EL RANDOM ORIGINAL SERA IGUAL A : " << ranK << '\n'
#endif
            //SI ES NUMERO ES DE RELLENO DE BLOQUE ENTONCES LO SALTAMOS
            if (ii < 0)
        {
            num = ranK + 2;
        }
        else
        {
            //SI NO ES DE RELLENO LO MULTIPLICADOS
            num = ii * ranK;
#ifdef debug
            cout << "ESTE ES EL NUMERO OBTENIDO " << num << '\n';
#endif
        }
        //CONVERTIMOS EL NUMERO A STRING Y LO RELLENAMOS CON CEROS, HASTA ESTE PUNTO EL NUMERO
        //YA DEBIO SER MULTIPLICADO O CIFRADO CORRECTAMENTE
        string aux = to_string(num);

        for (int i = 0; i < (aux.length() - 5); i++)
        {
            aux = "0" + aux;
        }

        //KEY -> STRING QUE DEVUELVE EL CIFRADO
        key += aux;
        //CREAMOS LLAVES POR CADA BLOQUE DIFERENTE DE 16
        if (cont == 16 && i < blocks.size())
        {
            cont = 1;
            ranK = (1 + rand() % 50);
            Nkey.push_back(ranK);
        }
        else
        {
            cont++;
        }
    }
#ifdef debug
    cout << Nkey.size() << '\n';
#endif
    return key;
}

void decypher(string keys, vector<int> ranK)
{
    int contB = 1;
    string result;
    string aux;
    //PARA DECIFRAR TOMAMOS CADA BLOQUE CON SU LLAVE CORRESPONDIENTE
    //LO CONVERTIMOS A ENTERO Y LO DIVIDIMOS POR SU CONTRARIO O INVERSO 
    //PARA PODER OBTENER EL MENSAJE ORIGINAL
    for (int i = 0; i < keys.length(); i += 5)
    {
        if (contB == 16 + 1 && i < keys.length())
        {
            contB = 1;
            ranK.pop_back();
        }

        aux = keys.substr(i, 5);

        //PROCESO DE DECIFRADO

        int num;
        stringstream some(aux);
        some >> num;

#ifdef debug
        cout << "ESTE ES EL NUMERO " << num << '\n';
        cout << "ESTE ES EL RANDOM " << ranK[ranK.size() - 1] << '\n';
#endif

        //HACEMOS LA OPERACIÓN DE DIVISIÓN PARA OBTENER LA CADENA ORIGINAL
        if (num != ranK[ranK.size() - 1] - 2)
        {
            num /= ranK[ranK.size() - 1];
            char ch = static_cast<char>(num);
            result += ch;
        }

        contB++;
    }
    cout << "EL MENSAJE DECIFRADO ES: " << result << '\n';
}

int main()
{
    vector<int> Blocks;

    //SEPARAMOS LOS MENSAJES DE ENTRADA PARA RELLENAR CON EL NUMERO COMPLEMENTO

    string wordO;
    int num_blocks = 0;
    int res = 0;
    getline(cin, wordO);
    int aux = wordO.length();

    //16 BLOQUES POR CADA CIFRADO
    while (aux > 16)
    {
        aux -= 16;
        num_blocks++;
    }

    num_blocks++;
#ifdef debug
    cout << "AUX: " << aux << '\n';
#endif

    if (aux)
    {
        res = 16 - aux;
    }

#ifdef debug
    cout << num_blocks << '\n';
#endif

    //ALMACENAMOS LA CADENA EN ENTEROS, SU VALOR ASCII CORRESPONDIENTE
    for (int i = 0; i < wordO.length(); i++)
    {
        char aux;
        aux = wordO.at(i);
        Blocks.push_back(int(aux));
    }
    if (res > 0)
    {
        for (int i = 0; i < res; i++)
        {
            Blocks.push_back(-1);
        }
    }
#ifdef debug
    for (auto i : Blocks)
    {
        cout << "NUM E " << i << '\n';
    }
#endif
    cout << '\n';
    //CYPHER
    string key;
    vector<int> ranK;
    //ETAPA DE CIFRADO DEL MENSAJE QUE DEVUELVE RANK EL CUAL ES EL ARREGLO DE LAS CLAVES INVERSAS
    key = cypher(Blocks, ranK);
    cout << "EL MENSAJE CIFRADO ES: " << key << '\n';
    //REVERTIMOS EL ARREGLO DE LLAVES
    reverse(ranK.begin(), ranK.end());
    //ETAPA DE DECIFRADO
    decypher(key, ranK);

    return 0;
}