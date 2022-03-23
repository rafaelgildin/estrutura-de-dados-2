//
// Created by gustavo on 23/03/2022.
//

#ifndef ESTRUTURA_LEITORCSV_CPP
#define ESTRUTURA_LEITORCSV_CPP
#include <vector>
#include <fstream>


void lerCSV(const string& arquivo, vector<vector<string> >& tabela)
{
    std::ifstream t(arquivo);
    std::string csvConteudo((std::istreambuf_iterator<char>(t)),
                            std::istreambuf_iterator<char>());

    bool entreAspas(false);
    bool novaLinha(false);
    string campo;
    tabela.clear();
    vector<string> line;

    string::const_iterator aChar = csvConteudo.begin();
    while (aChar != csvConteudo.end())
    {
        switch (*aChar)
        {
            case '"':
                novaLinha = false;
                entreAspas = !entreAspas;
                break;

            case ',':
                novaLinha = false;
                if (entreAspas)
                {
                    campo += *aChar;
                }
                else
                {
                    line.push_back(campo);
                    campo.clear();
                }
                break;

            case '\n':
            case '\r':
                if (entreAspas)
                {
                    campo += *aChar;
                }
                else
                {
                    if (!novaLinha)
                    {
                        line.push_back(campo);
                        tabela.push_back(line);
                        campo.clear();
                        line.clear();
                        novaLinha = true;
                    }
                }
                break;

            default:
                novaLinha = false;
                campo.push_back(*aChar);
                break;
        }

        aChar++;
    }

    if (!campo.empty())
        line.push_back(campo);

    if (!line.empty())
        tabela.push_back(line);
}

#endif //ESTRUTURA_LEITORCSV_CPP
