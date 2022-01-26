
#include <iostream>
#include <cmath>

using namespace std;

void FillParametrForPoint(double** arr, const int rows, const int cols);
void OutPutParametr(double** arr, const int rows, const int cols);
void ChooseClaster(int amountPoint, int amountClaster, double** const arr, const int rows, const int cols, double** arrClaster);
void Algo(double** arrClasters, double** Points, double** arr, int size, int cols, int rows);
void KmeansMethod(double** arrClasters, double** Points, double** arr, double** Result, int size,int cols,int rows);
void Classification(double** arr, double** arrClaster, double** Result, int cols, int size);
void CMemory(double** arr, int size);
void CArr(double** arr, int rows, int cols);
void Form(int value);

int main()
{
    setlocale(LC_ALL, "ru");
    int rows = 3;
    int cols = 6;
    int amountClater = 0;
    int rest = 0;

    double** ParametrPoint = new double* [rows];//инициализация массивов | вывозов функций
    CArr(ParametrPoint, rows, cols);

    FillParametrForPoint(ParametrPoint, rows, cols);
    cout << "\n Выберете кол-во кластеров : ";
    cin >> amountClater;

    double** Clasters = new double* [rows];
    CArr(Clasters, rows, amountClater);

    ChooseClaster(cols, amountClater, ParametrPoint, rows, cols, Clasters);

    rest = cols - amountClater;
    double** RestPoint = new double* [rows];
    CArr(RestPoint, rows, rest);
    Algo(Clasters, RestPoint, ParametrPoint, rest, cols, rows);
    

    double** ResultClassification = new double* [2];
    CArr(ResultClassification, 2, cols);

    KmeansMethod(Clasters, RestPoint, ParametrPoint, ResultClassification, rest, cols, rows);

    CMemory(ParametrPoint, rows);//Очистка памяти
    CMemory(Clasters, rows);
    CMemory(RestPoint, rows);
    CMemory(ResultClassification, 2);
}

void FillParametrForPoint(double** arr, const int rows, const int cols)
{
    double valueParametr;

    for (int keyWhileIn = 0; keyWhileIn < cols; keyWhileIn++)
    {
        arr[0][keyWhileIn] = keyWhileIn + 1;
    }
    cout << "\n Заполните значения параметров точки \n";
    for (int keyWhileInsert = 1; keyWhileInsert < rows; keyWhileInsert++)
    {
        for (int keyWhileIn = 0; keyWhileIn < cols; keyWhileIn++)
        {
            cout << " Заполняется " << keyWhileInsert << " параметр " << keyWhileIn + 1 << " точки : ";
            cin >> valueParametr;
            arr[keyWhileInsert][keyWhileIn] = valueParametr;
        }
    }
}
void OutPutParametr(double** arr, const int rows, const int cols)
{
    Form(cols);
    for (int keyWhileInsert = 0; keyWhileInsert < rows; keyWhileInsert++)
    {
        if (keyWhileInsert == 0)
        {
            cout << endl;
            cout << "|\t";
        }else
        {
            cout << "|\t";
        }
  
        for (int keyWhileIn = 0; keyWhileIn < cols; keyWhileIn++)
        {
            cout << arr[keyWhileInsert][keyWhileIn];
            if (keyWhileIn + 1 < cols)
            {
                cout << "\t";
                cout << "|\t";
            }
            else
            {
                cout << "\t|";
            }
        }
        cout << "\n|" << "-----------------------------------------------------------------------------------------------";
        cout << endl;
    }
}
void ChooseClaster(int amountPoint, int amountClaster, double** const arr, const int rows, const int cols, double** arrClaster)
{
    OutPutParametr(arr, rows, cols);

    int valueClaster;
    for (int keyWhileClasters = 0; keyWhileClasters < amountClaster; keyWhileClasters++)
    {
        cout << "\n Выберите центроиды для " << keyWhileClasters + 1 << " кластера ";
        cin >> valueClaster;
        for (int keyWhileFillClasters = 0; keyWhileFillClasters < rows; keyWhileFillClasters++)
        {
            arrClaster[keyWhileFillClasters][keyWhileClasters] = arr[keyWhileFillClasters][valueClaster - 1];
        }
    }
    for (int key = 0; key < amountClaster; key++)
    {
        cout << "----------------";
    }
    for (int keyWhileInsert = 0; keyWhileInsert < rows; keyWhileInsert++)
    {
        if (keyWhileInsert == 0)
        {
            cout << endl;
            cout << "|\t";
        }else
        {
            cout << "|\t";
        }
        for (int keyWhileIn = 0; keyWhileIn < amountClaster; keyWhileIn++)
        {
            cout << arrClaster[keyWhileInsert][keyWhileIn];
            if (keyWhileIn + 1 < cols)
            {
                cout << "\t";
                cout << "|\t";
            }
        }
        cout << "\n|";
        for(int key =0; key <amountClaster; key ++)
        {
            cout << "----------------";
        }
        cout << endl;
    }
}
void Algo(double** arrClasters, double** Points, double** arr, int size, int cols, int rows)
{
    bool whileStatus;
    int keyFillArr = 0;
    for (int key = 0; key < cols; key++)
    {
        whileStatus = false;
        for (int keyOut = 0; keyOut < cols - size; keyOut++)
        {

            if (arr[0][key] == arrClasters[0][keyOut])
            {
                whileStatus = false;
                break;
            }
            else
                whileStatus = true;
        }
        if (whileStatus)
            {
             for (int keyWhileFill = 0; keyWhileFill < rows; keyWhileFill++)
             {
                Points[keyWhileFill][keyFillArr] = arr[keyWhileFill][key];
             }
             keyFillArr++;
        }
      
    }
}

void KmeansMethod(double** arrClasters, double** Points, double** arr, double** Result, int size, int cols,int rows)
{
    bool status = true;
    int counter = 1;
    int keyIteretion;
    while(status)
    {
        if (counter == 1)
            keyIteretion = size;
        else
            keyIteretion = cols;
        cout << "\n\nИтерация № " << counter << endl;
        for(int keyWhile = 0; keyWhile < keyIteretion; keyWhile++)
        {
            double minValue;
            int index = 1;
            double *arrResult = new double[cols - size];
            if(counter == 1)
            {
                for (int keyClastersWhile = 0; keyClastersWhile < cols - size; keyClastersWhile++)
                {

                    arrResult[keyClastersWhile] = sqrt(pow(Points[1][keyWhile] - arrClasters[1][keyClastersWhile], 2) + pow(Points[2][keyWhile] - arrClasters[2][keyClastersWhile], 2));
                }
                cout << "\n\nСравниваем расстояние от точки " << Points[0][keyWhile] << " до эталонных точек" << endl;
                for (int keyOutPut = 0; keyOutPut < cols - size; keyOutPut++)
                {
                    cout << "d(" << Points[0][keyWhile] << " e" << keyOutPut + 1 << ")" << " = " << arrResult[keyOutPut] << endl;
                }
            }else
            {
                for (int keyClastersWhile = 0; keyClastersWhile < cols - size; keyClastersWhile++)
                {

                    arrResult[keyClastersWhile] = sqrt(pow(arr[1][keyWhile] - arrClasters[1][keyClastersWhile], 2) + pow(arr[2][keyWhile] - arrClasters[2][keyClastersWhile], 2));
                }
                cout << "\n\nСравниваем расстояние от точки " << arr[0][keyWhile] << " до эталонных точек" << endl;

                for (int keyOutPut = 0; keyOutPut < cols - size; keyOutPut++)
                {
                    cout << "d(" << arr[0][keyWhile] << " e" << keyOutPut + 1 << ")" << " = " << arrResult[keyOutPut] << endl;
                }
            }

            minValue = arrResult[0];

            for(int keySearch = 0; keySearch < cols-size;keySearch++)
            {

                if(minValue >= arrResult[keySearch])
                {
                    minValue = arrResult[keySearch];
                    index = keySearch + 1;
                }
                else
                {
                    minValue = arrResult[0];
                    break;
                }
            }
            
            if(counter==1)
                cout << "Минимальным является расстояние d(" << Points[0][keyWhile] << " e" << index << ")" << endl;
            else
                cout << "Минимальным является расстояние d(" << arr[0][keyWhile] << " e" << index << ")\n" << endl;
            cout << "Пересчитываем значения для эталонной точки e" << index << endl; 
            if (counter == 1)
            {
                arrClasters[1][index - 1] = (Points[1][keyWhile] + arrClasters[1][index - 1]) / 2;
                arrClasters[2][index - 1] = (Points[2][keyWhile] + arrClasters[2][index - 1]) / 2;
            }
            else
            {
                arrClasters[1][index - 1] = (arr[1][keyWhile] + arrClasters[1][index - 1]) / 2;
                arrClasters[2][index - 1] = (arr[2][keyWhile] + arrClasters[2][index - 1]) / 2;
            }

            for (int key = 0; key < cols-size; key++)
            {
                cout << "----------------";
            }
            for (int keyWhileInsert = 0; keyWhileInsert < rows; keyWhileInsert++)
            {
                if (keyWhileInsert == 0)
                {
                    cout << endl;
                    cout << "|\t";
                }else
                {
                    cout << "|\t";
                }
                for (int keyWhileIn = 0; keyWhileIn < cols-size; keyWhileIn++)
                {
                    cout << arrClasters[keyWhileInsert][keyWhileIn];
                    if (keyWhileIn + 1 < cols)
                    {
                        cout << "\t";
                        cout << "|\t";
                    }
                    else
                    {
                        cout << "\t|";
                    }
                }
                cout << endl;
            }
            for (int key = 0; key < cols - size; key++)
            {
                cout << "----------------";
            }
            delete[] arrResult;
        }
        double** ResultClassifi = new double* [1];

        for (int keyWhile = 0; keyWhile < 1; keyWhile++)
        {
            ResultClassifi[keyWhile] = new double[cols];
        }
        
        for (int keyInput = 0; keyInput < cols; keyInput++)
        {
            ResultClassifi[0][keyInput] = Result[0][keyInput];
        }

        Classification(arr, arrClasters, Result, cols, size);

        if(counter > 1)
        {
            for (int keyCheckStatus = 0; keyCheckStatus < cols; keyCheckStatus++)
            {
                if (Result[0][keyCheckStatus] == ResultClassifi[0][keyCheckStatus])
                {
                    status = false;
                }else
                {
                    status = true;
                    break;
                }
            }
        }
        counter++;

        for (int keyWhileDelete = 0; keyWhileDelete < 1; keyWhileDelete++)
        {
            delete[] ResultClassifi[keyWhileDelete];
        }
        delete[] ResultClassifi;
    }
    cout << "\nГраницы кластеров не изменились. Завершения процесса кластеризации\n";
}
void Classification(double** arr, double** arrClaster, double** Result, int cols, int size)
{
    cout << "\nПроизводится классификация объектов" << endl;
    for(int keyClassif = 0; keyClassif < cols; keyClassif++)
    {
        double minValue = 0;
        int index = 1;
        double* arrResult = new double[cols - size];
        for (int keyClastersWhile = 0; keyClastersWhile < cols - size; keyClastersWhile++)
        {
            arrResult[keyClastersWhile] = sqrt(pow(arr[1][keyClassif] - arrClaster[1][keyClastersWhile], 2) + pow(arr[2][keyClassif] - arrClaster[2][keyClastersWhile], 2));
        }

        minValue = arrResult[0];

        for (int keySearch = 0; keySearch < cols - size; keySearch++)
        {
            if (minValue >= arrResult[keySearch])
            {
                minValue = arrResult[keySearch];
                index = keySearch + 1;
            }
            else if(minValue < arrResult[keySearch])
            {
            }
            else
            {
                minValue = arrResult[0];
                break;
            }
        }

        Result[0][keyClassif] = index;
        Result[1][keyClassif] = minValue;

        delete[] arrResult;
    }
    for (int key = 0; key < 2; key++)
    {
        cout << "----------------";
    }
    for (int key = 0; key < cols; key++)
    {
        if (key == 0)
        {
            cout << endl;
            cout << "|\t";
        }
        else
        {
            cout << "|\t";
        }
        for (int keyW = 0; keyW < 2; keyW++)
        {
            cout <<Result[keyW][key];
            if (keyW + 1 < 2)
            {
                cout << "\t";
                cout << "|    ";
            }
            else
            {
                cout << "\t|";
            }
        }
        cout << "\n|";
        for (int key = 0; key < 2; key++)
        {
            cout << "----------------";
        }
        cout << endl;
    }
}
void CMemory(double** arr, int size)
{
    for(int keyDeleteMemory = 0; keyDeleteMemory< size;keyDeleteMemory++)
    {
        delete[] arr[keyDeleteMemory];
    }
    delete arr;
}
void CArr(double** arr, int rows, int cols)
{
    for(int keyCreat =0; keyCreat < rows; keyCreat++)
    {
        arr[keyCreat] = new double[cols];
    }
}
void Form(int value)
{
    while (value != 0)
    {
        cout << "----------------";
        value--;
    }
}
