#include <map>
#include <unordered_map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <climits>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <conio.h>
#include <regex>
using namespace std;

template <typename T1, typename T2>
struct greater_second {
	typedef pair<T1, T2> type;
	bool operator ()(type const& a, type const& b) const {
		return a.second > b.second;
	}
};

vector < string > findVendorsWithMaxDuplicates(vector < string > items) {

	
	map<string,string> itemlist;
	map<string, int> vendorduplicatecount;

	// get items in a map

	for (int i = 0; i < items.size(); i++){
		char *vendoritem = strtok(const_cast<char *>(items[i].c_str()), ",");
	
		string vendor = vendoritem;
		vendoritem = strtok(NULL, ",");
		string item = vendoritem;

		itemlist[vendor].append(item+",");
	}

	// get number of duplicate item each vendor sells 
	typedef std::map<std::string, std::string>::iterator it_type;

	for (it_type iterator = itemlist.begin(); iterator != itemlist.end(); iterator++) {

		string vendor = iterator->first; //get vendor
		string itemlist_str = iterator->second; // get the list of items the vendor sells
		
		//iterate through that list
		char *vendoritem = strtok(const_cast<char *>(itemlist_str.c_str()), ",");
		int itemcount = 0;
		vendorduplicatecount[vendor] = 0;

		while (vendoritem != NULL){

			string searchforitem = vendoritem;
			itemcount = 0;

			for (it_type iterator2 = itemlist.begin(); iterator2 != itemlist.end(); iterator2++) {

				string vendor2 = iterator2->first; //get vendor
				string itemlist_str2 = iterator2->second; // get the list of items the vendor sells

				if (itemlist_str2.find(searchforitem) != string::npos){ //increase item count if vendor sells it
					itemcount++;
				}
				if (itemcount > 1){
					vendorduplicatecount[vendor] += 1;
					break;
				}
			}
			vendoritem = strtok(NULL, ",");
		}

	}

	// sort count by value
	vector<pair<string, int> > mapcopy(vendorduplicatecount.begin(), vendorduplicatecount.end());
	sort(mapcopy.begin(), mapcopy.end(), greater_second<string, int>());
	
	

	// return the top ... append the vector with next vendor in the sorted list 
	vector<string> returnvector;
	vector<pair<string, int>>::iterator it;
	int max = 0;
	for (it = mapcopy.begin(); it < mapcopy.end(); it++) {
		if(it->second < max)
			break;
		returnvector.push_back(it->first);
		max = it->second;
		//cout << it->first;
	}
	return returnvector;
}

void listswap(int *list, int a, int b){
	int temp = list[a];
	list[a] = list[b];
	list[b] = temp;
}

void sortByPivot(int *list, int pivotindex, int size){
	int pivot = list[pivotindex];
	int smaller = 0, larger = size, equal = 0;


	for (int i = 0; i < size; i++){
		cout << list[i] << ",";
	}
	cout << endl;

	while (equal < larger){
		if (list[equal] < pivot){
			if (smaller!=equal)
				listswap(list, smaller++, equal++);
			else{
				smaller++;
				equal++;
			}
		}
		else if (list[equal] == pivot){
			++equal;
		}
		else{
			listswap(list, equal, --larger);
		}

		for (int i = 0; i < size; i++){
			cout << list[i] << ",";
		}
		cout << endl;
	}

	
}

void sortBool(bool *list, int size){

}


vector<int> arrayPlusOne(vector<int> input){
	int carry = 1;
	for (int i = input.size() - 1; i>=0; i--){
		input[i] += carry;
		if (input[i] == 10 && i == 0){
			input[i] = 0;
			input.insert(input.begin(), 1);
			break;
		}
		if (input[i] == 10){
			carry = 1;
			input[i] = 0;
		}
		else{
			break;
		}
	}
	return input;
}

vector<int> multiplyArrays(vector<int> A, vector<int> B){

	vector<int> result(A.size()+B.size(),0);
	
	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());

	for (int i = 0; i < A.size(); i++){
		for (int j = 0; j < B.size(); j++){
			result[i + j] += A[i] * B[j];
			result[i + j + 1] += result[i + j] / 10;
			result[i + j] %= 10;
		}
	}

	while (result.size() != 1 && result.back() == 0)
		result.pop_back();
	
	reverse(result.begin(), result.end());
	return result;
}

vector<int> mergeSortedArrays(vector<int> A, vector<int> B, int iA, int iB){

	int iM = iA + iB - 1;

	while (iA > 0 && iB > 0){
		if (A[iA - 1] >= B[iB - 1] ){
			A[iM--] = A[iA-1];
			iA--;
		}
		else if (A[iA - 1] < B[iB - 1]){
			A[iM--] = B[iB-1];
			iB--;
		}
	}

	if (iB < 0){
		while (iA>0){
			A[iM--] = A[iA - 1];
			iA--;
		}
	}
	else if (iA < 0){
		while (iB>0){
			A[iM--] = B[iB - 1];
			iB--;
		}
	}

	return A;
}

vector<int> deletekey(vector<int> A, int key){
	int count = 0;
	for (int i = 0; i < A.size()-count;i++){
		if (A[i+count] == key) 
			count++;
		
		A[i] = A[i + count];
	}
	return A;
}

int deletedup(vector<int>& A){
	int dupcount = 0;
	int current = 0;

	for (int i = 0; i < A.size(); i++){
		if (A[i] == current) {  // duplicate found
			while (A[i] == current){
				dupcount++;
				i++;
			}
		}
		A[i - dupcount] = A[i];
		current = A[i];
	}

	return dupcount;
}

bool isWinningPossible(vector<int> moves){
	int maxPosition = 0, currentMove = 0, i = 0;
	int target = moves.size() - 1;

	while (currentMove <= target && i <= maxPosition){
		currentMove = i + moves[i];
		maxPosition = (maxPosition > currentMove) ? maxPosition : currentMove;
		if (maxPosition >= target)
			return true;
		i++;
	}
	return false;
}

string IntToString(int num){

	bool isNeg = false;
	string ret;
	if (num < 0){
		num *= -1;
		isNeg = true;
	}
	do{
		ret += '0'+ num % 10;
		num /= 10;
	} while (num);

	if (isNeg) ret += "-";

	reverse(ret.begin(), ret.end());

	return ret;
}


int StringToInt(string num){

	bool isNeg = (num[0] == '-');
	int result = 0;

	for (int i = (isNeg) ? 1 : 0; i < num.size(); i++){
		int digit = num[i] - '0';
		result = (result * 10) + digit;
	}

	return (isNeg) ? -result : result;
}

int binarySearch(vector<int> numbers, int key){
	
	int start = 0, end = numbers.size()-1;
	int middle = 0;

	while (end >= start){
		middle = start + (end - start) / 2;

		if (numbers[middle] == key)
			return key;
		else if (numbers[middle] > key){
			end = middle - 1;
		}
		else{
			start = middle + 1 ;
		}
	}

	return -1;
}

int binaryIndexEqualSearch(vector<int> numbers){

	int start = 0, end = numbers.size() - 1;
	int middle = 0;

	while (end >= start){
		middle = start + (end - start) / 2;

		if (numbers[middle] == middle)
			return middle;

		if (numbers[middle] > middle){
			end = middle - 1;
		}
		else{
			start = middle + 1;
		}
	}

	return -1;
}


int binaryCyclicSearch(vector<int> numbers){

	int start = 0, end = numbers.size() - 1;
	int middle = 0;

	while (end > start){
		middle = start + (end - start) / 2;
			if (numbers[start] > numbers[middle])
				end = middle;
			else
				start = middle + 1;
	}

	return start;
}

bool isPalindrome(string s){

	map<char, int> frequencies;

	for (char c : s){
		frequencies[c]++;
	}

	int oddfrequencies = 0;

	for (auto& letter : frequencies){
		if (letter.second % 2){
			oddfrequencies++;
		}
		if (oddfrequencies > 1)
			return false;
	}
	return true;
}

// Is a given smaller string contained in a bigger string (even anagrams of it is acceptable)

bool isLetterMagazine(string letter, string magazine){

	unordered_map<char, int> frequencies;

	for (char c : letter){
		frequencies[c]++;
	}

	for (char c : magazine){
		
		unordered_map<char, int> ::iterator letter = frequencies.find(c);
		if (letter != frequencies.cend()){
			--letter->second;

			if (letter->second == 0){
				frequencies.erase(letter);
	
				if (frequencies.empty())
					break;
			}
		}
	}
	return frequencies.empty();
}

// Return the longest substring with distinct characters

string longestSubstring(string input){

	unordered_map<char, int> latest_indexes;
	int max = INT_MIN;
	int maxstart = 0, length = 0, start = 0;
	
	if (input.empty()) return "empty";

	if (input.size() == 1) return input;

	for (int i = 0; i < input.size();i++){

		unordered_map<char, int> ::iterator letter = latest_indexes.find(input[i]);
		
		if (letter != latest_indexes.cend()){	  
			start = (letter->second + 1) > start ? (letter->second + 1) : start;     // update start of current candidate substring
			length = (i - start + 1);			// update current length
			letter->second = i;				// update hash table with latest index
		}

		else{
			latest_indexes[input[i]] = i;	// insert new character with index
			length++;						// length
		}

		if (length >= max){
			max = length;					// keep track of max length
			maxstart = start;				// keep track of start of max substring
		}
	}

	return input.substr(maxstart,max);
}

vector<int> twoSum(vector<int> &numbers, int target) {

	vector<int> result;
	map<int, int> hashmap;
	hashmap.clear();
	for (int i = 0; i < numbers.size(); i++){
		hashmap[numbers[i]] = i;
	}
	for (int i = 0; i < numbers.size(); i++){
		if (hashmap.find((target - numbers[i])) != hashmap.end()){
			int index = hashmap[target - numbers[i]] + 1;
			result.push_back(min(i + 1, index));
			result.push_back(max(i + 1, index));
			return result;
		}
	}

	return vector<int>{ -1, -1 };
}

// MAXIMUM SUM of an array 

int maxSubArray(vector<int>& nums) {
	int sum = nums[0], lgsum = nums[0];
	for (int i = 1; i<nums.size(); i++)
	{
		sum = max(nums[i], sum + nums[i]);
		lgsum = max(lgsum, sum);
	}
	return lgsum;
}

// PRODUCT except self - Most efficient

vector<int> productExceptSelf(vector<int>& nums) {

	vector<int> result;
	int current = 1;
	for (int i = 0; i < nums.size(); ++i) {
		result.push_back(current);
		current *= nums[i];
	}
	int n = nums.size();
	current = 1;
	for (int i = n - 1; i >= 0; --i) {
		result[i] = current * result[i];
		current *= nums[i];
	}
	return result;
}

// Find a number in a sorted rotated array - Recursive

int search(vector<int> &nums, int left, int right, int target) {
	if (left > right) return -1;
	int mid = left + (right - left) / 2;
	if (nums[mid] == target) return mid;

	if (nums[left] <= nums[right]) {
		if (target < nums[left] || target > nums[right]) {
			return -1;
		}
		else {
			if (nums[mid] > target) {
				return search(nums, left, mid - 1, target);
			}
			else {
				return search(nums, mid + 1, right, target);
			}
		}
	}
	else {
		int s1 = search(nums, left, mid - 1, target);
		return (s1 == -1) ? search(nums, mid + 1, right, target) : s1;
	}
}

int search(vector<int>& nums, int target) {
	return search(nums, 0, nums.size() - 1, target);
}

// IS GIVEN STRING AN INTEGER

//bool isInteger(string s)
//{
//	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
//
//	char *end;
//	strtol(s.c_str(), &end, 10);  //strtol(string, endptr, base)
//
//	return (*end == 0);
//}

// using REGEX 

bool isInteger(string input)
{
	string int_regex = "^[-+]?([[:digit:]]+)$";

	regex pattern(int_regex);

	return regex_match(input, pattern);
}

// ISOMORPHIC - are two strings isomorphic

bool isIsomorphic(string s, string t) {

	if (s.empty() || t.empty()  || (s.length() != t.length()) ) return false;

	vector<char> v1(256, 0), v2(256, 0);
	for (int i = 0; i < s.size(); i++) {
		if (!v1[s[i]] && !v2[t[i]]) {
			v1[s[i]] = t[i];
			v2[t[i]] = s[i];
		}
		else if (v1[s[i]] != t[i] || v2[t[i]] != s[i])
			return false;
	}
	return true;
}

// MINIMUM WINDOW SUBSTRING

string minWindow(string s, string t) {
	if (s.empty() || s.length() < t.length() || s.length() == 0){
		return "";
	}
	unordered_map<char, int> map;
	for (char c : t){
		if (map.find(c)!=map.end()){
			map[c] = map.find(c)->second+1;
		}
		else{
			map[c] = 1;
		}
	}
	int left = 0;
	int minLeft = 0;
	int minLen = s.length() + 1;
	int count = 0;
	for (int right = 0; right < s.length(); right++){

		if (map.find(s[right]) != map.end()){
			map[s[right]] = map.find(s[right])->second - 1;
			
			if (map.find(s[right])->second >= 0){
				count++;
			}
			while (count == t.length()){
				if (right - left + 1 < minLen){
					minLeft = left;
					minLen = right - left + 1;
				}
				if (map.find(s[left]) != map.end()){
					map[s[left]] = map.find(s[left])->second + 1;
					if (map.find(s[left])->second > 0){
						count--;
					}
				}
				left++;
			}
		}
	}
	if (minLen>s.length())
	{
		return "";
	}

	return s.substr(minLeft, minLeft + minLen);
}


// Does a symmetry exist in a given set (including subsets) of 2D points

/*
typedef vector<int, int> point;
int distance(point p, int x){
	return (abs(p[0] - x));
}

bool symmetryHelper(map<int, point> map, int cx){

	int levelindex = 0;
	for (auto level : map){
		while (levelindex <= level.second.size() - levelindex){
			if (levelindex == level.second.size() - levelindex){
				if (distance(level.second[levelindex], cx) == 0)
					continue;
				else
					return false;
			}

			else if (distance(level.second[levelindex], cx) != distance(level.second[level.second.size() - levelindex], cx))
				return false;
			else
				levelindex++;
		}
	}
	return true;
}

bool isSymmetric(vector<point> points){

	map<int, point> map;
	int maxx = INT_MIN, minx = INT_MAX;

	for (auto pt : points){
		map[pt[0]] = pt;

		if (pt[0] > maxx)
			maxx = pt[0];
		if (pt[0] < minx)
			minx = pt[0];
	}

	int candidatex = minx + (maxx - minx) / 2;
	int candidatecount = 0;

	while (candidatecount<(maxx - minx)){
		if (!symmetryHelper(map, candidatex)){
			return (symmetryHelper(map, (candidatex + (maxx - candidatex) / 2)) || symmetryHelper(map, (candidatex - (candidatex - minx) / 2)));
		}
		else
			return true;
	}
}

*/

int frenemy(const char rel[5][6], int x, int y, string relString){

	int ix = 0, iy = 0;

	int currentNode = x,tCount=0;
	queue<int> nodesToVisit;
	map<int,bool> visited;
	
	// put source node in queue
	nodesToVisit.push(currentNode);
		
	while (!nodesToVisit.empty())
	{
		// get current node and deque the front
		ix = nodesToVisit.front();
		nodesToVisit.pop();
		visited[ix] = true;
			
		// make a transition from node to all possible indexes with relation = currRelation
		for (iy = 0; iy < 3; iy++){
			if (rel[ix][iy] == relString[tCount]){
				if (visited.find(iy) == visited.cend()) //only push if not already visited
					nodesToVisit.push(iy);
			}
		}

		// only make the required number of transitions
		if (tCount == relString.length() - 1)
			break;
		else
			tCount++;

		visited.clear(); //clear the visited map ..makes cyclic relations possible
	}	

		
	

	// check if the destination node is in the queue
	while (!nodesToVisit.empty())
	{
		ix = nodesToVisit.front();
		nodesToVisit.pop();
		if (ix == y)
			return 1;
	}

	return 0;
}


int main(int argc, char *argv[]){

//	//ofstream fout(getenv("OUTPUT_PATH"));
//	vector < string > res;
//	vector<int> result;
//	bool outcome;
//	string str;
//
//	int _items_size = 12;
//	//cin >> _items_size;
//	//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//	//vector<string> _items = { "Vendor1,ItemA", "Vendor1,ItemB", "Vendor1,ItemC", "Vendor1,ItemD", "Vendor2,ItemA", "Vendor2,ItemE", "Vendor3,ItemA", "Vendor3,ItemD" };
//	int list[12] = { 1, 8, 7, 5, 2, 3, 5, 1, 7, 5, 9, 3 };
//	bool boollist[8] = { false, true, true, false, true, true, false, false };
//	vector<int> input = { 378,478,550,631,103,203,220,234,279,368};
//	vector<int> input1 = { 3, 6, 16, 4, 5, 2, 7, 9 };
//	int key = 45;
//	int resultNumber = 0;
//	vector<int> moves = { 3, 3, 1, 0, 2, 0, 1 };
//	vector<int> moves2 = { 3, 3, 0, 0, 2, 0, 1 };
//	int pivotIndex = 3;
//	//int sortedlist[12];
//
////	result = arrayPlusOne(input);
//	//result = multiplyArrays(input,input1);
//
//	/*outcome = isWinningPossible(moves);
//	cout << outcome;
//	outcome = isWinningPossible(moves2);
//	cout << outcome;
//*/
//	//result = twoSum(input1, key);
//	//resultNumber = deletedup(input);
//	/*std::vector<int>::iterator it;
//	for (it = result.begin(); it<result.end(); it++) {
//		cout << *it << " ";
//	}*/
//	//sortByPivot(list, pivotIndex,_items_size);
//	//sortBool(boollist, 8);
//
//	/*string _items_item;
//	for (int _items_i = 0; _items_i<_items_size; _items_i++) {
//		getline(cin, _items_item);
//		_items.push_back(_items_item);
//	}*/
//
//	//result = mergeSortedArrays(input, input1, 6, 3);
//	cout << longestSubstring("fwrweuwqpowuepq");
//	//res = findVendorsWithMaxDuplicates(_items);
//	//sort(res.begin(), res.end());
//	/*for (int res_i = 0; res_i < result.size(); res_i++) {
//		cout << result[res_i] << endl;;
//	}*/
//	
//	//cout << IntToString(-341);
//	//cout << StringToInt("-341");



	const char matrix[5][6] = { "-EFEF",
"E-FF-", "FF-EF", "EFE-F" ,"F-FF-"};

	cout << frenemy(matrix, 0, 4, "FFEEE");

	_getch();
	return 0;
}


