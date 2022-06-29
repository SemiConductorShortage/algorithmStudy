#include <iostream>
#include <list>

int binarySearch(int list[], int target, int arrsize) {
    int min = 0;
    int max = arrsize;
    int index = (min+max)/2;
    while (min<=max){        //1,2,3,4,5      middle=3, greater than target, set max to be index, keep min the same
        if (list[index]==target){
            return index;
        }
        if (list[index]>target){
            max = index-1;
        }
        if (list[index]<target){
            min = index+1;
        }
        index = (min+max)/2;
    }
    return -1;
}

int main(){
    int list[] = {312,3132,134,245,5,3,453,53,45,123,4,534,5,6,6,7,8,55,66,345,34,5,34,2,1,23,4,4,5,6,7,8,9,12};
    //yes im using bubble sort, the O(n^2) algorithm, on binary search, the log(n) algorithm, so the time complexity of this entire thing is O(n^2+log(n))
    for (int _i:list){
        for (int i=0;i<(sizeof list/sizeof list[0])-1;i++ ){ //i wanted to use a range based for loop but that doesnt work well with i+1 since it goes out of bounds
            if (list[i]>list[i+1]){
                int temp = list[i+1];
                list[i+1] = list[i]; //move the current element forward
                list[i]=temp;
            }
        }
    }

    for(auto i : list){
        printf("%d ",i);
    }

    int target = 4;
    int indexOfTarget = binarySearch(list,target, sizeof list/sizeof list[0]);
    printf("\nindex of target: %d\n", indexOfTarget);
}
