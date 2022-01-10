#include<iostream>
using namespace std;

int referenceString[50], pageFaults = 0, repetead, pagesnumb, frames, counter = 0, 
recentlyused[10], check1, check2,check3, x, y, loc ,z,neededinfuture[10],pageHit=0;
string algoType;
void Optimal(int f, int st[30]) {
    int* arr = new int(f);

    //assigning all values in the array with -1
    for (x = 0; x < f; ++x) {
        arr[x] = -1;
    }

    for (x = 0; x < pagesnumb; ++x) {
        check1 = check2 = 0;
        //page hit
        for (y = 0; y < f; ++y) {
            if (arr[y] == st[x]) {
                check1 = check2 = 1;
                pageHit++;
                break;
            }
        }
       //free frames but page fault
        if (check1 == 0) {
            for (y = 0; y < f; ++y) {
                if (arr[y] == -1) {
                    pageFaults++;
                    arr[y] = st[x];
                    check2 = 1;
                    break;
                }
            }
        }
        //no free frames and page fault
        if (check2 == 0) {
            check3 = 0;

            for (y = 0; y < f; ++y) {
                neededinfuture[y] = 0;

                for (z = x + 1; z < pagesnumb; ++z) {
                    if (arr[y] == st[z]) {
                        neededinfuture[y] = z;
                        break;
                    }
                }
            }

            for (y = 0; y < f; ++y) {
                if (neededinfuture[y] == 0) {
                    loc = y;
                    check3 = 1;
                    break;
                }
            }

            if (check3 == 0) {
                //bengeeb aktar rakam 3ayzeeno fel future
                int max = neededinfuture[0];
                loc = 0;

                for (y = 1; y < f; ++y) {
                    if (neededinfuture[y] > max) {
                        max = neededinfuture[y];
                        loc = y;
                    }
                }
            }
            arr[loc] = st[x];
            pageFaults++;
        }

        cout << endl;;

        for (y = 0; y < f; ++y) {
            cout << " " << arr[y];
        }
    }

    cout << endl << " Total number of page faults is " << pageFaults << endl;
    cout << "Total number of page hits is " << pageHit << endl;


}
int findLRU(int recentlyused[], int n) {
    int i, min = recentlyused[0], loc = 0;

    for (i = 1; i < n; ++i) {
        if (recentlyused[i] < min) {
            min = recentlyused[i];
            loc = i;
        }
    }
    return loc;
}
void LRU(int f, int st[30]) {
   
    int* arr = new int(f);
    for (x = 0; x < f; ++x) {
        arr[x] = -1;
    } //assign kolo b -1

    for (x = 0; x < pagesnumb; ++x) {
        check1 = check2 = 0;

        for (y = 0; y < f; ++y) {//page hit
            if (arr[y] == st[x]) {
                counter++;
                recentlyused[y] = counter;
                check1 = check2 = 1;//condition lel other cases 
                pageHit++;
                break;
            }
        }

        if (check1 == 0) {
            for (y = 0; y < f; ++y) {//page fault and free frame
                if (arr[y] == -1) {
                    counter++;
                    pageFaults++;
                    arr[y] = st[x];
                    recentlyused[y] = counter;
                    check2 = 1;
                    break;
                }
            }
        }
        
        if (check2 == 0) {//page fault with no free frame
            loc = findLRU(recentlyused, f);
            counter++;
            pageFaults++;
            arr[loc] = st[x];
            recentlyused[loc] = counter;
        }
        cout << endl;
        for (y = 0; y < f; y++)//displayy
        {
            cout << arr[y] << " ";
        }

    }
    cout << endl << "Total number of page faults is " << pageFaults<<endl;
    cout << "Total number of page hits is " << pageHit<<endl;
  

}
void fifo(int f,int st[30]) {
    int* arr = new int(f);
    //Assign kol el values to -1
    for (int x = 0; x < f; x++)
    {
        arr[x] = -1;
    }
   
    for (int x = 0; x < pagesnumb; x++)
    {
        repetead=0;
        for (int y = 0; y < f; y++)
        {
            if (st[x] == arr[y])//Page Hit
            {
                repetead++;
                pageHit++;
                pageFaults--;//no page faults added
            }
        }
        pageFaults++;
        if ((pageFaults <= f)&&(repetead==0))
        {
            arr[x] = st[x];
        }
        else if (repetead == 0)
        {
            arr[(pageFaults - 1) % f] = st[x]; 
        }
        cout << endl;
        
        for (int y = 0; y < f; y++)//displayy
        {
            cout << arr[y] << " ";
        }
       
    }
    cout << endl << "Total number of page faults is " << pageFaults <<endl;
    cout << "Total number of Page Hits is " << pageHit << endl;

}
int main()
{
    int again;
    do {

        cout << "Enter how many numbers do you want to be in your string" << endl;
        cin >> pagesnumb;
        cout << "Enter " << pagesnumb << " numbers for your string" << endl;
        for (int i = 0; i < pagesnumb; i++)
        {
            cin >> referenceString[i];
        }
        cout << "Enter number of frames" << endl;
        cin >> frames;
        cout << "What Algorithm do you want to use ? FIFO , LRU or Optimal?";
        cin >> algoType;
        if (algoType == "FIFO" || algoType == "fifo") {
            fifo(frames, referenceString);
        }
        else if (algoType == "LRU" || algoType == "lru") {
            LRU(frames, referenceString);
        }
        else if (algoType == "Optimal" || algoType == "optimal") {
            Optimal(frames, referenceString);
        }
        cout << "To check another string press 1";
        cin >> again;
        system("cls");
        pageFaults = 0;
        pageHit = 0;
    }

    while (again == 1);
}