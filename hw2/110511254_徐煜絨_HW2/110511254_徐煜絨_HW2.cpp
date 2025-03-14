#include <bits/stdc++.h>
using namespace std;

struct back {
    int first;
    int last;
    double value;
};

// typedef struct back back;

// check if the new subarray is bigger or the ones in the "result"
void compare(vector<back> &result, back temp) {
    int re_diff;
    int te_diff;
    if(result[result.size()-1].value < temp.value){
        // discover the new maximum subarray, clear the original result
        result.clear();
        result.push_back(temp);
    }
    else if(result[result.size()-1].value == temp.value){
        re_diff = result[result.size()-1].last - result[result.size()-1].first;
        te_diff = temp.last - temp.first;
        
        // check if the subarray covers the same number of elements
        if(re_diff == te_diff){
            if(temp.first != 0){
                result.push_back(temp);
            }
        }
        else if(re_diff > te_diff){
            result.clear();
            result.push_back(temp);
        }
    }
}

// devide and conquer (first element is on the left side and the last one is on the right side)
void dacm(vector<double> &data, vector<back> &result, int low, int mid, int high){ // value would be double!!!
    back ans;
    double maxlv = data[mid];  // value
    double sum = 0;
    int maxlp = mid;  //position
    for(int i=mid; i>=low; i--){
        sum += data[i];
        if(sum > maxlv){
            maxlv = sum;
            maxlp = i;
        }
    }
    sum = 0;
    double maxrv = data[mid+1];
    double maxrp = mid + 1;
    for(int i=mid+1; i<=high; i++){
        sum += data[i];
        if(sum > maxrv){
            maxrv = sum;
            maxrp = i;
        }
    }
    ans.first = maxlp;
    ans.last = maxrp;
    ans.value = maxlv + maxrv;
    compare(result, ans);
}

/*void cal(vector<back> &result){
    double max = result[0].value;
    vector<back> temp;
    temp = result;
    int r_size = result.size();
    result.clear();
    result.push_back(temp[0]);
    if (temp.size() > 1)
    for(int i=1; i<r_size; i++){
        if(temp[i].value > max){
            result.clear();
            result.push_back(temp[i]);
        }
        else if(temp[i].value == max){
            if(result[0].last - result[0].first > temp[i].last - temp[i].first){
                result.clear();
                result.push_back(temp[i]);
            }
            else if(result[0].last - result[0].first == temp[i].last - temp[i].first){
                result.push_back(temp[i]);
            }
        }
    }
}*/

void dac(vector<double> &data, vector<back> &result, int low, int high){
    if (low==high){
        compare(result, {low, high, data[low]});
    }
    else{
    int mid = (low+high)/2;
    // cout << "yes" << endl;
    dac(data, result, low, mid);  //dac1
    // cal(result);
    dac(data, result, mid+1, high);  //dac2
    // cal(result);
    dacm(data, result, low, mid, high);
    // cal(result);
    }
    // cout << result[0].value << endl;
}

int main(int argc, char* argv[])
{
    ifstream input;
    input.open("data.txt");
    double num, val;
    vector<double> data;  // to store every data in the txt file
    vector<back> result;
    int x=0;
    while((input >> num >> val)){
        data.push_back(val);
    }
    result.push_back({0, 0, data[0]});
    // initialize the vector. If there are any bigger subarray, 'result' will be updated
    dac(data, result, 0, data.size()-1);  // dac <=> devide and conquer
    for (int i=0; i<result.size(); i++){
        cout <<  "start from " << result[i].first+1 << " to " << result[i].last+1 << endl;
    }
    cout << "Maximum sum is " << result[0].value << endl;
    input.close();
    return 0;
}