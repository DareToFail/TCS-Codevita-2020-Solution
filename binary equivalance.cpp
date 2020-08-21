#include<iostream>
#include<bits/stdc++.h>
using namespace std;
#define int long long
int sum =0;

/* Function to check if x is power of 2*/
bool checkPow2(int n)  
{  
    if (n == 0)  
        return 0;  
    while (n != 1)  
    {  
        if (n%2 != 0)  
            return 0;  
        n = n/2;  
    }  
    return 1;  
}

//Calculate maximum number of bits representation
int maxbitrepre(int n){
    if(checkPow2(n))
        return ceil(log2(n)) + 1;
    return ceil(log2(n));
}

//calculating count of zeros and ones  
vector <int> counting(int n , int maxbit) 
{ 
    int count0 = 0, count1 = 0;
    vector<int> count;
    checkPow2(n+1) ? count0++ : 1;
    while (n) 
    { 
        (n % 2 == 0) ? count0++ :count1++; 
        n /= 2; 
    }
    count0 += maxbit - (count0+count1);
    count.push_back(count0);
    count.push_back(count1);
    return count; 
} 

//combination
void combinationUtil(vector<int> count0, vector<int> count1, int data0[],int data1[], int start, int end,int index, int r,vector<int> input)  
{  
    if (index == r)  
    {  
        int sum0 = data0[0];
        int sum1 = data1[0];
        for (int j = 1; j < r; j++){
            sum0 += data0[j];
            sum1 += data1[j];
        }  
        if(sum0==sum1)
            sum++;
        return;  
    }   
    for (int i = start; i <= end && end - i + 1 >= r - index; i++)  
    {  
        data0[index] = count0[i];
        data1[index] = count1[i];
        combinationUtil(count0,count1,data0, data1, i+1,end, index+1, r,input);
        while (input[i] == input[i+1])
             i++; 
		 
    }
	  
}

void combination(vector<int> count0, vector<int> count1, int n, int r,vector<int> input)  
{  
     
    int data0[r],data1[r];  
    combinationUtil(count0,count1,data0, data1, 0, n-1, 0, r,input);  
}  
  
// Function that convert Decimal to binary 
void decToBinary(int n,int maxbit) 
{ 
    // Size of an integer is assumed to be 32 bits 
    for (int i = maxbit-1; i >= 0; i--) { 
        int k = n >> i; 
        if (k & 1) 
            cout << "1"; 
        else
            cout << "0"; 
    } 
}
  
// Driver Program 
signed main() 
{ 
    int n,a;
    cin>>n;
    vector<int> input;
    for(int i=0;i<n;i++){
        cin>>a;
        input.push_back(a);
    }
    
    // Sort the vector in descending order 
    sort(input.begin(), input.end(), greater<int>());
    
    vector<int> count,count0,count1;
    for(int i=0;i<n;i++){
       count = counting(input[i],maxbitrepre(input[0]));
       count0.push_back(count[0]);
       count1.push_back(count[1]);
    }
    
    
    int r=3;
    while(r>0){
        combination(count0,count1,n, r,input);
        r--;
    }
    decToBinary(sum,maxbitrepre(input[0]));
    return 0; 
} 
