    /*
     * Sudoku.cpp
     *
     */

    #include "Sudoku.h"

#include <utility>
    #include <algorithm>
    #include <cstring>


    /** Inicia um Sudoku vazio.
     */
    Sudoku::Sudoku()
    {
        this->initialize();
    }

    /**
     * Inicia um Sudoku com um conte�do inicial.
     * Lan�a excep��o IllegalArgumentException se os valores
     * estiverem fora da gama de 1 a 9 ou se existirem n�meros repetidos
     * por linha, coluna ou bloc 3x3.
     *
     * @param nums matriz com os valores iniciais (0 significa por preencher)
     */
    Sudoku::Sudoku(int nums[9][9])
    {
        this->initialize();

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (nums[i][j] != 0)
                {
                    int n = nums[i][j];
                    numbers[i][j] = n;
                    lineHasNumber[i][n] = true;
                    columnHasNumber[j][n] = true;
                    block3x3HasNumber[i / 3][j / 3][n] = true;
                    countFilled++;
                }
            }
        }
    }

    void Sudoku::initialize()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                for (int n = 0; n < 10; n++)
                {
                    numbers[i][j] = 0;
                    lineHasNumber[i][n] = false;
                    columnHasNumber[j][n] = false;
                    block3x3HasNumber[i / 3][j / 3][n] = false;
                }
            }
        }

        this->countFilled = 0;
    }

    /**
     * Obtem o conteudo actual (so para leitura!).
     */
    int** Sudoku::getNumbers()
    {
        int** ret = new int*[9];

        for (int i = 0; i < 9; i++)
        {
            ret[i] = new int[9];

            for (int a = 0; a < 9; a++)
                ret[i][a] = numbers[i][a];
        }

        return ret;
    }

    /**
     * Verifica se o Sudoku ja esta completamente resolvido
     */
    bool Sudoku::isComplete()
    {
        return countFilled == 9 * 9;
    }




    vector<int> Sudoku::getCandidates(size_t x, size_t y){

        vector<int> candidates = {1,2,3,4,5,6,7,8,9};

        for(size_t i = 1; i <= 9;i++){

            if(columnHasNumber[y][i])
                candidates.at(i-1) = 0;

            if(lineHasNumber[x][i])
                candidates.at(i-1) = 0;

            if(block3x3HasNumber[x / 3][y / 3][i])
                candidates.at(i-1) = 0;

        }

        vector<int>::iterator it = candidates.begin();

        while(it != candidates.end()){

            if(*it == 0)
                it = candidates.erase(it);
            else
                it++;
        }

        return candidates;
    }


    vector<int> Sudoku::getBestCandidate(size_t& x, size_t& y){


        vector<int> result,current;

        for(size_t i = 0; i < 9; i++){

            for(size_t j = 0; j < 9; j++){


                if(numbers[i][j] != 0)
                    continue;

                current = this->getCandidates(i,j);

                if(current.empty())
                    continue;

                if( (current.size() < result.size()) || result.empty()){

                    x = i;
                    y = j;
                    result = current;

                    if(result.size() == 1)
                        return result;

                }

            }

        }

        return result;

    };


    void Sudoku::insertAt(size_t x, size_t y, int k){

        columnHasNumber[y][k] = true;
        lineHasNumber[x][k] = true;
        block3x3HasNumber[x / 3][y / 3][k] = true;

        numbers[x][y] = k;

    }

    void Sudoku::removeAt(size_t x, size_t y, int k){


        columnHasNumber[y][k] = false;
        lineHasNumber[x][k] = false;
        block3x3HasNumber[x / 3][y / 3][k] = false;

        numbers[x][y] = 0;

    }

    /**
     * Resolve o Sudoku.
     * Retorna indicacao de sucesso ou insucesso (sudoku imposs�«ivel).
     */
    bool Sudoku::solve()
    {

        if(isComplete())
            return true;

        size_t x = 0,y = 0;
        vector<int> bestCandidate = getBestCandidate(x,y);

        if(bestCandidate.empty())
            return false;

        countFilled++;

        for(int i = bestCandidate.size() - 1; i >= 0; i--){

            insertAt(x,y,bestCandidate.at(i));
            if(this->solve())
                return true;

            removeAt(x,y,bestCandidate.at(i));

        }

        countFilled--;

        return false;
    }



    /**
     * Imprime o Sudoku.
     */
    void Sudoku::print()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int a = 0; a < 9; a++)
                cout << this->numbers[i][a] << " ";

            cout << endl;
        }
    }
