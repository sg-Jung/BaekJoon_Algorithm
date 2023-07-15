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

// �ߺ��� ���� ����
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

// �ߺ��� ���� ����
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

// �ߺ��� �ִ� ����
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

// �ߺ��� �ִ� ����
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
* ����: ���ҵ��� ������ ����Ͽ� ������ ��� ����� ���� �����ϴ� ��
* ex) A, B, C -> ABC, ACB, BAC, CAB, CBA
* 
* ����: ���ҵ��� ������ ������� �ʰ�, �־��� ���ҵ� �߿��� �Ϻθ� �����Ͽ� ���� �� �ִ� ��� �κ�����
* ex) A, B, C -> A, B, C, AB, AC, BC, ABC
*/

int main()
{
    vector<int> nums = { 1, 2, 3, 4 };
    int r = 4;

    vector<int> permutation, combination;
    vector<bool> usedPer(nums.size(), false), usedComb(nums.size(), false);

    cout << "�ߺ��� �ִ� ����" << endl;
    generatePermutations(nums, r, permutation);
    cout << endl << endl;
    cout << "�ߺ��� ���� ����" << endl;
    generatePermutations(nums, r, usedPer, permutation);
    cout << endl << endl;
    cout << "�ߺ��� �ִ� ����" << endl;
    generateCombinations(nums, r, combination, 0);
    cout << endl << endl;
    cout << "�ߺ��� ���� ����" << endl;
    generateCombinations(nums, r, usedComb, combination, 0);

    return 0;
}
