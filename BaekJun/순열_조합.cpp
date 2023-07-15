#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void printPermutation(const vector<int>& permutation)
{
    for (int num : permutation)
    {
        cout << num << " ";
    }
    cout << endl;
}

void printCombination(const vector<int>& combination)
{
    for (int num : combination)
    {
        cout << num << " ";
    }
    cout << endl;
}

// 중복이 없는 순열
void generatePermutations(vector<int>& nums, int r, vector<bool>& used, vector<int>& permutation)
{
    if (r == 0)
    {
        printPermutation(permutation);
        return;
    }

    for (int i = 0; i < nums.size(); i++)
    {
        if (!used[i])
        {
            used[i] = true;
            permutation.push_back(nums[i]);
            generatePermutations(nums, r - 1, used, permutation);
            permutation.pop_back();
            used[i] = false;
        }
        
    }
}

// 중복이 없는 조합
void generateCombinations(vector<int>& nums, int r, vector<bool>& used, vector<int>& combination, int index)
{
    if (r == 0)
    {
        printCombination(combination);
        return;
    }

    for (int i = index; i < nums.size(); i++)
    {
        if (!used[i])
        {
            used[i] = true;
            combination.push_back(nums[i]);
            generateCombinations(nums, r - 1, used, combination, i);
            combination.pop_back();
            used[i] = false;
        }

    }
}

// 중복이 있는 순열
void generatePermutations(vector<int>& nums, int r, vector<int>& permutation)
{
    if (r == 0)
    {
        printPermutation(permutation);
        return;
    }

    for (int i = 0; i < nums.size(); i++)
    {
        permutation.push_back(nums[i]);
        generatePermutations(nums, r - 1, permutation);
        permutation.pop_back();

    }
}

// 중복이 있는 조합
void generateCombinations(vector<int>& nums, int r, vector<int>& combination, int index)
{
    if (r == 0)
    {
        printCombination(combination);
        return;
    }

    for (int i = index; i < nums.size(); i++)
    {
        combination.push_back(nums[i]);
        generateCombinations(nums, r - 1, combination, i);
        combination.pop_back();
    }
}


/*
* 순열: 원소들의 순서를 고려하여 가능한 모든 경우의 수를 나열하는 것
* ex) A, B, C -> ABC, ACB, BAC, CAB, CBA
* 
* 조합: 원소들의 순서는 고려하지 않고, 주어진 원소들 중에서 일부를 선택하여 만들 수 있는 모든 부분집합
* ex) A, B, C -> A, B, C, AB, AC, BC, ABC
*/

int main()
{
    vector<int> nums = { 1, 2, 3, 4 };
    int r = 4;

    vector<int> permutation, combination;
    vector<bool> usedPer(nums.size(), false), usedComb(nums.size(), false);

    cout << "중복이 있는 순열" << endl;
    generatePermutations(nums, r, permutation);
    cout << endl << endl;
    cout << "중복이 없는 순열" << endl;
    generatePermutations(nums, r, usedPer, permutation);
    cout << endl << endl;
    cout << "중복이 있는 조합" << endl;
    generateCombinations(nums, r, combination, 0);
    cout << endl << endl;
    cout << "중복이 없는 조합" << endl;
    generateCombinations(nums, r, usedComb, combination, 0);

    return 0;
}
