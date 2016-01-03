#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

void bubbleSort(int *a,int length);     //Performing bubble sorting method with ascending order
void selectionSort(int *a,int length);  //Performing selection sorting method with ascending order
void quickSort(int *a,int left,int length);      //Performing quick sorting method with ascending order
void heapSort(int *a,int length);       //Performing heap sorting method with ascending order
void mergeSort(int *a,int length);      //Performing merge sorting method with ascending order

int main()
{
    srand(time(NULL));
    int length = 200;
    int *ori= (int*)malloc(sizeof(int)*length);
    int *a= (int*)malloc(sizeof(int)*length);

    cout << "Prior : " << endl;
    for(int i=0; i<length; i++)
    {
        ori[i]=rand()%500+1;
        a[i]=ori[i];
        cout << ori[i] << " ";
    }
    cout << endl << endl;

    //bubbleSort
    cout << "bubbleSort:" << endl;
    bubbleSort(a,length);
    for(int i= 0 ; i <length; i++)
    {
        cout << a[i] << " ";
        a[i]=ori[i];
    }
    cout << endl << endl;

    //selectionSort
    cout << "selectionSort:" << endl;
    selectionSort(a,length);
    for(int i= 0 ; i <length; i++)
    {
        cout << a[i] << " ";
        a[i]=ori[i];
    }
    cout << endl << endl;

    //quickSort
    cout << "quickSort:" << endl;
    quickSort(a,0,length-1);
    for(int i= 0 ; i <length; i++)
    {
        cout << a[i] << " ";
        a[i]=ori[i];
    }
    cout << endl << endl;

    //heapSort
    cout << "heapSort:" << endl;
    heapSort(a,length);
    for(int i= 0 ; i <length; i++)
    {
        cout << a[i] << " ";
        a[i]=ori[i];
    }
    cout << endl << endl;

    //mergeSort
    cout << "mergeSort:" << endl;
    mergeSort(a,length);
    for(int i= 0 ; i <length; i++)
    {
        cout << a[i] << " ";
        a[i]=ori[i];
    }
    cout << endl << endl;

    return 0;
}

void bubbleSort(int *a, int length)
{
    for(int i=0; i<length-1; i++) // length筆資料需要length-1次迴圈
    {
        for(int j=0; j<length-i-1; j++) // (length-1)-i次比較
        {
            if(a[j]>a[j+1])
            {
                int tmp=a[j];
                a[j]=a[j+1];
                a[j+1]=tmp;
            }
        }
    }
}

void selectionSort(int *a,int length)
{
    int minIndex,minValue;
    for(int i=0; i<length-1; i++) // length筆資料需要length-1次迴圈
    {
        minIndex=i; // 存放未排序區間的最小值索引
        minValue= a[minIndex]; // 存放未排序區間的最小值
        for(int j=i+1; j<length; j++) //從i+1開始
        {
            if(a[j]<minValue) // 比最小值小就記錄
            {
                minIndex=j;
                minValue=a[minIndex];
            }
        }
        //把記錄下來的最小值交換
        int tmp=a[minIndex];
        a[minIndex]=a[i];
        a[i]=tmp;
    }
}

void quickSort(int *a,int left,int right)
{
    int i = left, j = right;
    int tmp; // for swaping
    int pivot = a[(left + right) / 2];

    /* partition */
    while (i <= j) // i>j stop
    {
        while (a[i] < pivot) // left partition,a[i]>=pivot,then stop
            i++;
        while (a[j] > pivot) // right partition,a[i]<=pivot,then stop
            j--;
        if (i <= j) // i>j can't swap
        {
            tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */ // now i>j -> new partition: (left,j),(i,right)
    if (left < j)
        quickSort(a, left, j);
    if (i < right)
        quickSort(a, i, right);
}

void heapSort(int *a,int length)
{
    // create max heap tree
    int toSortArray[length+1];
    toSortArray[0] = 0;
    for(int i = 1; i < length+1; i++)
    {
        toSortArray[i] = a[i-1];
        toSortArray[0]++; //holds the number of values in the array;
        int index = i;
        while(toSortArray[index/2]<toSortArray[index] && (index/2)!=0)
        {
            int temp = toSortArray[index/2];
            toSortArray[index/2] = toSortArray[index];
            toSortArray[index] = temp;
            index=index/2;
        }
    }

    // heap sort
    while(toSortArray[0]>0)
    {
        // swap first and last data
        int temp = toSortArray[1];
        toSortArray[1] = toSortArray[toSortArray[0]];
        toSortArray[toSortArray[0]] = temp;

        // then turn it to heap tree
        for(int i = 1; i < toSortArray[0]; i++)
        {
            int index = i;
            while(toSortArray[index/2]<toSortArray[index] && (index/2)!=0)
            {
                int temp1 = toSortArray[index/2];
                toSortArray[index/2] = toSortArray[index];
                toSortArray[index] = temp1;
                index=index/2;
            }
        }

        // numbers--
        toSortArray[0]--;
    }

    // output data
    for(int i=0; i<length; i++)
    {
        a[i]=toSortArray[i+1];
    }
}

void mergeSort(int *a,int length)
{
    // 陣列分兩半
    int x[length/2],y[length/2];
    for(int i=0; i<length/2; i++)
    {
        x[i]=a[i];
        y[i]=a[i+length/2];
    }

    // 分別排序
    bubbleSort(x,length/2);
    bubbleSort(y,length/2);

    // Merge
    int i=0,j=0,k=0;
    for(i=0; j<length/2&&k<length/2; i++) // x或y其中之一處理完就會離開for
    {
        if(x[j]<y[k])
        {
            a[i]=x[j];
            j++;
        }
        else
        {
            a[i]=y[k];
            k++;
        }
    }
    if(j>=length/2) // x已處理完,將y後面未處理補上
    {
        for(int l=k; l<length/2; l++)
        {
            a[i+(l-k)]=y[l];// l-j=0,1,2.....
        }
    }
    else  // y已處理完,將x後面未處理補上
    {
        for(int l=j; l<length/2; l++)
        {
            a[i+(l-j)]=x[l]; // l-k=0,1,2.....
        }
    }

}

