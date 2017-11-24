//
//  PROJECT 4
//
//  Created by 杨博超 on 15/11/3.
//  Copyright © 2015年 杨博超. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

void swap (string& s1, string& s2)  // A function that can swap two strings.
{
    string t = s1;
    s1 = s2;
    s2 = t;
}

int appendToAll(string a[], int n, string value)  // Append value to the end of each of the n elements of the array and return n.
{
    if(n < 0)  // Bad argument: a negative array size
        return -1;
    for (int k = 0; k < n; k++)
    {
        a[k] += value;  // Do what the function should do.
    }
    return n;
}

int lookup(const string a[], int n, string target)  // Return the position of a string in the array that is equal to target.
{
    if(n < 0)  // Bad argument: a negative array size
        return -1;
    for (int k = 0; k < n; k++)
    {
        if(a[k] == target)
            return k;  // Do what the function should do.
    }
    return -1;  // Return −1 if there is no such string.
}

int positionOfMax(const string a[], int n)  // Return the position of a string in the array such that that string is >= every string in the array.
{
    if(n <= 0)  // Bad argument: a negative array size  // Return −1 if the array has no elements.
        return -1;
    int pos = 0;
    for (int k = 1; k < n; k++)
    {
        if (a[k] > a[pos])
            pos = k;  // Do what the function should do.
    }
    return pos;
}

int rotateLeft(string a[], int n, int pos)  // Eliminate the item at position pos by copying all elements after it one place to the left. Put the item that was thus eliminated into the last position of the array. Return the original position of the item that was moved to the end.
{
    if(n <= 0 || pos < 0 || pos > n)  // Bad argument: a negative array size  // Bad argument: an unproper position
        return -1;
    string specialCase = a[pos];  // Save the specialcase string first
    for (int k = pos; k < n-1; k++)
    {
        a[k] = a[k+1];  // Do what the function should do.
    }
    a[n-1] = specialCase;  // Put the specialcase string to the end
    return pos;
}

int countRuns(const string a[], int n)  // Return the number of sequences of one or more consecutive identical items in a.
{
    if(n < 0)  // Bad argument: a negative array size
        return -1;
    if (n == 0)  // Specialcase when n equals to 0.
    {
        return 0;
    }
    int runs = 1;
    for (int k = 0; k < n-1; k++)
    {
        if (a[k+1] != a[k])
        {
            runs++;  // Do what the function should do.
        }
    }
    return runs;
}

int flip(string a[], int n)  // Reverse the order of the elements of the array and return n.
{
    if(n < 0)  // Bad argument: a negative array size
        return -1;
    for (int k = 0; k < n/2; k++)
    {
        swap (a[k], a[n-k-1]);  // Call the former function swap to do what the function should do.
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if(n1 < 0 || n2 < 0)  // Return the position of the first corresponding elements of a1 and a2 that are not equal. n1 is the number of interesting elements in a1, and n2 is the number of interesting elements in a2. If the arrays are equal up to the point where one or both runs out, return the smaller of n1 and n2.
        return -1;
    int n = 0;  // Let n be the smaller one of n1 and n2.
    if(n1 < n2)
        n = n1;
    else
        n = n2;
    //cout << "  " << n <<endl;
    for (int k = 0; k < n; k++)
    {
        if (a1[k] != a2[k])
            return k;  // Do what the function should do.
    }
    return n;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)  // If all n2 elements of a2 appear in a1, consecutively and in the same order, then return the position in a1 where that subsequence begins. If the subsequence appears more than once in a1, return the smallest such beginning position in the array.
{
    if(n1 < 0 || n2 < 0 || n1 < n2)  // Bad argument: negative array size(s)
        return -1;
    int p = 0;
    int q = 0;
    for (p = 0; p < n1  &&  q < n2; p++)  // Do what the function should do.
    {
        if (a1[p] == a2[q])
            q++;
    }
    if(q == n2)
        return p - n2;
    else
        return -1;  // Return −1 if a1 does not contain a2 as a contiguous subsequence.
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)  // Return the smallest position in a1 of an element that is equal to any of the elements in a2.
{
    if(n1 < 0 || n2 < 0)  // Bad argument: negative array size(s)
        return -1;
    int p = 0;
    int q = 0;
    for (p = 0; p < n1; p++)  // p grows slower
    {
        for (q = 0; q < n2; q++)  // q grows faster
        {
            if(a1[p] == a2[q])
                return p;  // Do what the function should do.
        }
    }
    return -1;  // Return −1 if no element of a1 is equal to any element of a2.
}

int split(string a[], int n, string splitter)  // Rearrange the elements of the array so that all the elements whose value is < splitter come before all the other elements, and all the elements whose value is > splitter come after all the other elements. Return the position of the first element that, after the rearrangement, is not < splitter, or n if there are no such elements.
{
    if(n < 0)  // Bad argument: a negative array size
        return -1;
    int count = 0;
    for (int k = 0; k < n - count; k++)
    {
        if(a[k] < splitter)
            continue;
        if(a[k] >= splitter)
        {
            string specialCase = a[k];  // save the specialcase string
            for (int t = k; t < n-1; t++)
            {
                a[t] = a[t+1];  // rotate the later strings to left for one position
            }
            a[n-1] = specialCase;  // add the special case string to the end
            count++;  // Do what the function should do.
        }
        k--;
    }
    return n - count;
}

int main()
{
    string a[] = {"blake", "steven", "tony"};
    string b[] = {"blake", "steven", "", "", "tony", "shawn"};
    string c[] = {"jack", "steven"};
    string d[] = {"blake", "steven", "tony", "shawn"};
    string e[] = {"blake", "steven", "", "tony", "shawn", "!"};
    string f[] = {"blake", "steven", "", "tony", "shawn", ""};
    string g[] = {"blake", "steven", "jack", "tony", "shawn", "thomas"};
    
    assert(appendToAll(d, -2, "!!!") == -1 && d[0] == "blake");
    assert(appendToAll(d, 0, "!!!") == 0 && d[0] == "blake");
    assert(appendToAll(d, 1, "!!!") == 1 && d[0] == "blake!!!" && d[2] == "tony");
    
    assert(lookup(a, -1, "blake") == -1);
    assert(lookup(a, 0, "tony") == -1);
    assert(lookup(a, 2, "tony") == -1);
    assert(lookup(a, 2, "steven") == 1);
    assert(lookup(a, 3, "jack") == -1);
    
    assert(positionOfMax(a, -2) == -1);
    assert(positionOfMax(a, 0) == -1);
    assert(positionOfMax(a, 1) == 0);
    assert(positionOfMax(a, 3) == 2);
    
    
    assert(rotateLeft(a, -1, 1) == -1);
    assert(rotateLeft(a, 2, -1) == -1);
    assert(rotateLeft(a, 2, 3) == -1);
    assert(rotateLeft(a, 0, 0) == -1);
    assert(rotateLeft(a, 2, 1) == 1 && a[1] == "steven");
    
    assert(countRuns(a, -2) == -1);
    assert(countRuns(a, 0) == 0);
    assert(countRuns(b, 1) == 1);
    assert(countRuns(b, 4) == 3);
    assert(countRuns(b, 6) == 5);
    
    assert(flip(b, -2) == -1);
    assert(flip(b, 0) == 0);
    assert(flip(b, 3) == 3 && b[0] == "" && b[4] == "tony");
    
    assert(differ(e, -1, f, 3) == -1);
    assert(differ(e, 3, f, -2) == -1);
    assert(differ(e, 0, f, 3) == 0);
    assert(differ(e, 2, f, 2) == 2);
    assert(differ(e, 3, f, 5) == 3);
    assert(differ(e, 6, f, 6) == 5);
    
    assert(subsequence(e, -1, f, 3) == -1);
    assert(subsequence(e, 1, f, -2) == -1);
    assert(subsequence(e, 3, f, 2) == 0);
    assert(subsequence(e, 3, f, 0) == 0);
    assert(subsequence(e, 0, f, 0) == 0);
    assert(subsequence(e, 3, f, 5) == -1);
    assert(subsequence(e, 6, f, 6) == -1);
    
    assert(lookupAny(c, -1, f, 3) == -1);
    assert(lookupAny(c, 1, f, -2) == -1);
    assert(lookupAny(c, 3, f, 2) == 1);
    assert(lookupAny(c, 3, f, 0) == -1);
    assert(lookupAny(c, 0, f, 2) == -1);
    
    assert(split(g, -2, "tony") == -1);
    assert(split(g, 0, "tony") == 0);
    assert(split(g, 3, "tony") == 3);
    assert(split(g, 6, "shawn") == 2);
    
    cout << "All tests succeeded" << endl;
}
