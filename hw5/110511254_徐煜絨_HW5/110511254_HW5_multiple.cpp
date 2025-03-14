#include <bits/stdc++.h>
using namespace std;

struct out{
    vector<int> r;
    vector<int> s;
    int price;
};
struct outb{
    vector<int> r;
    vector<vector<int>> s;
    vector<int> c;
    int price;
};
struct ans{
};
int td11(vector<int> v, int length, vector<int>& r, vector<int>& s){
    if(r[length] >= 0){
        return r[length];
    }
    int q = INT_MIN;
    if(length == 0){
        q = 0;
    }
    else{
        for(int i = 1; i <= length; i++){
            if(i > 10){
                int temp1 = td11(v, length - 10, r, s);
                if(q < v[10] + temp1){
                    q = v[10] + temp1;
                    s[length] = 10;
                }
            }
            else{
                int temp1 = td11(v, length - i, r, s);
                if(q <= v[i] + temp1){
                    q = v[i] + temp1;
                    s[length] = i;
                }
            }
        }
    }
    r[length] = q;
    return q;
}

// max
out td1(vector<int> v, int length){
    vector<int> r(length+1, INT_MIN);
    vector<int> s(length+1, 0);
    int p = td11(v, length, r, s);
    return {r, s, p};
}

int td22(vector<int> v, int length, vector<int>& r, vector<int>& s){
    if(r[length] >= 0){
        return r[length];
    }
    int q = INT_MAX;
    if(length == 0){
        q = 0;
    }
    else{
        for(int i = 1; i <= length; i++){
            if(i > 10){
                int temp1 = td22(v, length - 10, r, s);
                if(q >= v[10] + temp1){
                    q = v[10] + temp1;
                    s[length] = 10;
                }
            }
            else{
                int temp1 = td22(v, length - i, r, s);
                if(q >= v[i] + temp1){
                    q = v[i] + temp1;
                    s[length] = i;
                }
            }
        }
    }
    r[length] = q;
    return q;
}

out td2(vector<int> v, int length){
    vector<int> r(length+1, INT_MIN);
    vector<int> s(length+1, 0);
    int p = td22(v, length, r, s);
    return {r, s, p};
}

outb bu1(vector<int> v, int length){
    vector<int> r(length+1, 0);
    vector<vector<int>> s(length+1, {0});
    vector<int> c(length+1, 0);

    c[0] = -1;

    for(int j=1; j<=length; j++){
        int q = INT_MAX;
        for(int i=1; i<=j && i<=10; i++){
            
            if(q > v[i]+r[j-i]){
                q = v[i]+r[j-i];
                s[j].clear();
                s[j].push_back(i);
                c[j] = c[j-i] + 1;
            }
            else if(q == v[i]+r[j-i]){
                q = v[i]+r[j-i];
                int ori_c = c[j];
                int new_c = c[j-i] + 1;
                if(ori_c > new_c){
                    s[j].clear();
                    s[j].push_back(i);
                    c[j] = new_c;
                }
                else if(ori_c == new_c){
                    if(i <= (j/2)){
                        s[j].push_back(i);
                    }
                }
            }
        }
        r[j] = q;
    }
    return {r, s, c, r[length]};
}

outb bu2(vector<int> v, int length){
    vector<int> r(length+1, 0);
    vector<int> t(length+1, 0);
    vector<vector<int>> s(length+1, {0});
    vector<int> c(length+1, 0); // cut how many time

    c[0] = -1;

    for(int j=1; j<=length; j++){
        // cout << "nowj: " << j << endl;
        int q = INT_MIN;
        for(int i=1; i<=j && i<=10; i++){
            // cout << "nowi: " << i << endl;

            if(q < v[i]+r[j-i]){
                q = v[i]+r[j-i];
                s[j].clear();
                s[j].push_back(i);
                c[j] = c[j-i] + 1;
            }
            else if(q == v[i]+r[j-i]){
                q = v[i]+r[j-i];

                // judge how to cut to get the min cut times                
                int ori_c = c[j];
                int new_c = c[j-i] + 1; // new cut times
                if(ori_c > new_c){
                    s[j].clear();
                    s[j].push_back(i);
                    c[j] = new_c;
                }
                else if(ori_c == new_c){
                    if(i <= (j/2)){
                        s[j].push_back(i);
                    }
                }
            }
        }
        r[j] = q;
    }
    return {r, s, c, r[length]};
}

void merge(vector<int> &a, int p, int q, int r){
    int i, j, k;
    int n1 = q-p+1;
    int n2 = r-q;
    // int L[n1], R[n2];
    int * L = new int[n1];
    int * R = new int[n2];
    for(i=0; i<n1; i++){
        L[i] = a[p+i];
    }
    for(j=0; j<n2; j++){
        R[j] = a[q+1+j];
    }
    i = 0;
    j = 0;
    k = p;
    while(i<n1 && j<n2){
        if(L[i] <= R[j]){
            a[k] = L[i];
            i++;
        }
        else{
            a[k] = R[j];
            j++;
        }
        k++;
    }
    while(i<n1){
        a[k] = L[i];
        i++;
        k++;
    }
    while(j<n2){
        a[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(vector<int> &a, int p, int r){
    int q;
    if (p>=r) return;
    q = (p+r)/2;
    merge_sort(a, p, q);
    merge_sort(a, q+1, r);
    merge(a, p, q, r);
}

void compare(vector<vector<int>> &a){
    for(int i=0; i<a.size(); i++){
        vector<int> temp = a[i];  //拿a[i]和a[k]做比較（i>=k）
        int j = i;
        while(j<a.size()){
            if(j==i){  // j必須從i開始增加，因為不保證a.size() > 1
                j++;  // 往下一個做比較
                continue;
            }
            else{
                if(a[j] == temp){  // 重複 -> 刪掉，注意j要維持
                    a.erase(a.begin() + j);
                }
                else{
                    j++;  // 不重複，往下一個比較
                }
            }
        }
    }
}

vector<vector<vector<int>>> deal(outb outp, int ask){
    int length = outp.s.size()-1;  // 取得length
    vector<vector<vector<int>>> ans(length+1);  // 儲存每個長度的切法
    // 其中ans[a][b]代表長度為a時的第b+1種切法，會是一個vector
    vector<int> temp;
    int temp1;
    int temp2;
    int size1;
    int size2;
    ans[0] = {0, {0}};
    for(int i=1; i<=length; i++){
        ans[i].clear();  // 初始化
        for(int j=0; j<outp.s[i].size(); j++){
            temp1 = outp.s[i][j];
            temp2 = i - temp1;
            // 長度i會由長度temp1和長度temp2組成
            
            if(temp2 == 0){  // 表示在不切的時候會有最大獲利
                ans[i].clear();
                ans[i].push_back({i});
            }

            else{
                for(int k=0; k<ans[temp1].size(); k++){  // 長度為temp1時會有幾種切法
                    for(int p=0; p<ans[temp2].size(); p++){  // 長度為temp2時會有幾種切法
                        // 假設切割成A, B兩塊
                        int size3 = ans[temp1][k].size();
                        int size4 = ans[temp2][p].size();
                        // 組合A和B的分割方式
                        temp.reserve(size3 + size4);
                        temp.insert(temp.end(), ans[temp1][k].begin(), ans[temp1][k].end());
                        temp.insert(temp.end(), ans[temp2][p].begin(), ans[temp2][p].end());
                        ans[i].push_back(temp);
                        temp.clear();
                    }
                }
            }
        }
    }
    for(int i=0; i<ans[ask].size(); i++){
        merge_sort(ans[ask][i], 0, ans[ask][i].size()-1);
    }
    compare(ans[ask]);
    
    return ans;
}

int main()
{
    int length;
    cout << "Please enter the length of the rod: ";
    cin >> length;
    vector<int> price(11, 0);
    for(int i = 1; i <= 10; i++){
        cout << "price p" << i << ": ";
        cin >> price[i];
    }
    cout << endl;
    vector<vector<vector<int>>> ansMax;
    vector<vector<vector<int>>> ansMin;

    // top down
    out outt1, outt2;
    outt1 = td1(price, length);
    outt2 = td2(price, length);

    // bottom up
    outb outb1;
    outb outb2;
    outb2 = bu2(price, length);
    outb1 = bu1(price, length);

    ansMax = deal(outb2, length);
    ansMin = deal(outb1, length);

    cout << "Top Down:" << endl;
    cout << "total length: " << length << endl;
    cout << "maximum price: " << outt1.price << endl;

    cout << "All kinds of combinations that have minimum pieces and have maximum price: " << endl;
    for(int j=0; j<ansMax[length].size(); j++){
        cout << "(";
        for(int k=0; k<ansMax[length][j].size(); k++){
            if(k == ansMax[length][j].size()-1){
                cout << ansMax[length][j][k];
            }
            else{
                cout << ansMax[length][j][k] << ", ";
            }
        }
        cout << ")" << endl;
    }
    cout << "number of pieces: " << ansMax[length][0].size() << endl;

    cout << "minimum price: " << outt2.price << endl;

    cout << "All kinds of combinations that have minimum pieces and have minimum price: " << endl;
    for(int j=0; j<ansMin[length].size(); j++){
        cout << "(";
        for(int k=0; k<ansMin[length][j].size(); k++){
            if(k == ansMin[length][j].size()-1){
                cout << ansMin[length][j][k];
            }
            else{
                cout << ansMin[length][j][k] << ", ";
            }
        }
        cout << ")" << endl;
    }
    cout << "number of pieces: " << ansMin[length][0].size() << endl;

    cout << "Bottom up:" << endl;
    cout << "total length: " << length << endl;
    cout << "maximum price: " << outb2.price << endl;

    cout << "All kinds of combinations that have minimum pieces and have maximum price: " << endl;
    for(int j=0; j<ansMax[length].size(); j++){
        cout << "(";
        for(int k=0; k<ansMax[length][j].size(); k++){
            if(k == ansMax[length][j].size()-1){
                cout << ansMax[length][j][k];
            }
            else{
                cout << ansMax[length][j][k] << ", ";
            }
        }
        cout << ")" << endl;
    }
    cout << "number of pieces: " << ansMax[length][0].size() << endl;

    cout << "minimum price: " << outb1.price << endl;

    cout << "All kinds of combinations that have minimum pieces and have minimum price: " << endl;
    for(int j=0; j<ansMin[length].size(); j++){
        cout << "(";
        for(int k=0; k<ansMin[length][j].size(); k++){
            if(k == ansMin[length][j].size()-1){
                cout << ansMin[length][j][k];
            }
            else{
                cout << ansMin[length][j][k] << ", ";
            }
        }
        cout << ")" << endl;
    }
    cout << "number of pieces: " << ansMin[length][0].size() << endl;
    
    return 0;
}