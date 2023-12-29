//Function 1
// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
    //Base case: index == 0 or a[0].
    if (n <= 0) {
        return true;
    }
    else{
        //Return false if the somePredicate function returns false for at least one of the array elements
        if (somePredicate(a[0]) == false) {
            return false;
        }
        //Move array pointer by one
        return allTrue(a+1, n - 1);
    }
    
}

//Function 2
// Return the number of elements in the array for which the
// somePredicate function returns true.
//Number of Checked = Number of True;
//Total Number = Number of True + Number of False
//Number of True = Total Number - Number of False
//
int countTrue(const string a[], int n)
{ 
    //Base case: index <= n.
    if (n <= 0) {
        return 0;
    }
    //Return false if the somePredicate function returns false for at least one of the array elements
    if (somePredicate(a[0])) {
       //Call recursion and move array pointer by 1
       return 1+countTrue(a+1, n-1);
    }
    return countTrue(a + 1, n - 1);
}

//Function 3
// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const string a[], int n)
{
    //If there is no such element, return -1.
    if (n <= 0) {
        return -1;
    }
    if (somePredicate(a[0])) {
        return 0;
    }
    if (firstTrue(a + 1, n - 1) == -1) {
        return -1;
    }
    return firstTrue(a + 1, n - 1) + 1;
    
}

//Function 4
// Return the subscript of the first string in the array that is >= all
// strings in the array (i.e., return the smallest subscript m such
// that a[m] >= a[k] for all k from 0 to n-1).  If the function is told
// that no strings are to be considered to be in the array, return -1.
int positionOfMax(const string a[], int n)
{
    if (n <= 0) {
        return -1;
    }
    //Base Case: If function is at position index of 0 or n=1, return 0 as the largest.
    if (n == 1) {
        return 0;
    }
    //Stack Function Calls
    int largest = positionOfMax(a, n-1);
    //If the value at current largest < value at n-1 position, return n-1 to examine in next recursive call
    if (a[largest] < a[n - 1]) {
        return n-1;
    }
    //Otherwise, keep examining the same element in the next recursive call.
    else {
        return largest;
    }
    
}

//Function 5
// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "john" "sonia" "elena" "ketanji" "sonia" "elena" "samuel"
// then the function should return true if a2 is
//    "sonia" "ketanji" "samuel"
// or
//    "sonia" "elena" "elena"
// and it should return false if a2 is
//    "sonia" "samuel" "ketanji"
// or
//    "john" "ketanji" "ketanji"
bool contains(const string a1[], int n1, const string a2[], int n2)
{
    
    //Of course, if a2 is empty (i.e., n2 is 0), return true.
    //Base Case: n2 == 0. Return true.
    /*cerr << n1 << "," << n2 << endl;*/
    if (n2 <= 0) {
        return true;
    }
    //If recursion deletes all elements in the first list, but not in the second list, return false.
    if (n1 <= 0 && n2 > 0) {
        return false;
    }
    
    //If all n2 elements of a2 appear in the n1 elements array a1, in the same order (though not necessarily consecutively), then return true
    if (a1[0] == a2[0]) {
        return contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    }
    return contains(a1 + 1, n1 - 1, a2, n2);
    
    

    //Otherwise (i.e., if the array a1 does not include a2 as a not-necessarily-contiguous subsequence), return false.
    
    


}

