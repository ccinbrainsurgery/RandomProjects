#include <map>
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


	////loop to arrange items < pivot
	//for (int i = 0; i < size - 1; i++){
	//	if (list[i] < pivot)
	//		listswap(list, i, smaller++);

	//	if (list[i] == pivot){
	//		listswap(list, i, equal++);
	//	}
	//}

	////loop to arrange items > pivot
	//for (int i = size - 1; i > 0 && list[i] >= pivot; i--){
	//	if (list[i] > pivot)
	//		listswap(list, i, larger--);
	//}

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


int main(int argc, char *argv[]){

	//ofstream fout(getenv("OUTPUT_PATH"));
	vector < string > res;

	int _items_size = 12;
	//cin >> _items_size;
	//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//vector<string> _items = { "Vendor1,ItemA", "Vendor1,ItemB", "Vendor1,ItemC", "Vendor1,ItemD", "Vendor2,ItemA", "Vendor2,ItemE", "Vendor3,ItemA", "Vendor3,ItemD" };
	int list[12] = { 1, 8, 7, 5, 2, 3, 5, 1, 7, 5, 9, 3 };
	bool boollist[8] = { false, true, true, false, true, true, false, false };
	int pivotIndex = 3;
	//int sortedlist[12];

	sortByPivot(list, pivotIndex,_items_size);
	sortBool(boollist, 8);

	/*string _items_item;
	for (int _items_i = 0; _items_i<_items_size; _items_i++) {
		getline(cin, _items_item);
		_items.push_back(_items_item);
	}*/



	//res = findVendorsWithMaxDuplicates(_items);
	//sort(res.begin(), res.end());
	/*for (int res_i = 0; res_i < res.size(); res_i++) {
		cout << res[res_i] << endl;;
	}*/

	_getch();
	return 0;
}


