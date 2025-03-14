#include <bits/stdc++.h>
using namespace std;

struct ans{
    vector<vector<double>> e;
    vector<vector<int>> r;
    vector<char> s;
};

ans optimal_bst(vector<double> p, vector<double> q, int n){
    vector<vector<double>> e(n+2, vector<double> (n+2, 0));
    vector<vector<double>> w(n+2, vector<double> (n+2, 0));
    vector<vector<int>> r(n+1, vector<int> (n+1, 0));
    vector<char> s;
    s.clear();
    for(int i = 1; i <= n+1; i++){
        e[i][i-1]= q[i-1]; 
        w[i][i-1] = q[i-1];
    }
    for(int l = 1; l <= n; l++){
        for(int i = 1; i <= n-l+1; i++){
            int j = i+l-1;
            e[i][j] = INT_MAX;
            w[i][j] = w[i][j-1] + p[j] + q[j];
            for(int k = i; k <= j; k++){
                double t = e[i][k-1] + e[k+1][j] + w[i][j];
                if(t == e[i][j]){
                    char c;
                    cout << "Wanna change the root table? (y/n): ";
                    cin >> c;
                    while(1){
                        if((c == 'y') || (c == 'Y')){
                            s.push_back('y');
                            e[i][j] = t;
                            r[i][j] = k;
                            break;
                        }
                        else if((c == 'n') || (c == 'N')){
                            s.push_back('n');
                            break;
                        }
                        else{
                            cout << "Wrong input, please enter y or n: ";
                            cin >> c;
                            continue;
                        }
                    }
                }
                else if(t < e[i][j]){
                    e[i][j] = t;
                    r[i][j] = k;
                }
            }
        }
    }
    return {e, r, s};
}

void right(vector<vector<int>> root, int l, int u, int r);

void left(vector<vector<int>> root, int l, int u, int r){

    if(l>u){
        cout << "d" << u << " is the left child of k" << r << endl;
        return;
    }

    else{
        int rt = root[l][u];
        cout << "k" << rt << " is the left child of k" << r << endl;
        left(root, l, rt-1, rt);
        right(root, rt+1, u, rt);
        return;
    }

}

void right(vector<vector<int>> root, int l, int u, int r){
    
    if(l>u){
        cout << "d" << u << " is the right child of k" << r << endl;
        return;
    }

    else{
        int rt = root[l][u];
        cout << "k" << rt << " is the right child of k" << r << endl;
        left(root, l, rt-1, rt);
        right(root, rt+1, u, rt);
        return;
    }
}

void pri(vector<vector<int>> root, int n){
    int r = root[1][n];  // the root of the whole tree
    cout << "k" << r << " is the root" << endl;

    // func(ans.r, lower bound, upper bound, root of the sub tree)
    left(root, 1, r-1, r);
    right(root, r+1, n, r);
}

int main()
{
    string c;
    cout << "Enter 'm' if you want to determine the p and q yourself." << endl;
    cout << "Enter 'p' if you want to use the p and q given in the pdf file." << endl;
    cin >> c;
    double d;

    vector<double> p;
    vector<double> q;
    p.clear();
    q.clear();
    int num;
    while(1){
        if((c == "m") || (c == "M")) {
            cout << "How many k: ";
            cin >> num;
            p.push_back(0);
            for(int i = 1; i <= num; i++){
                cout << "p" << i << ": ";
                cin >> d;
                p.push_back(d);
            }
            for(int i=0; i<=num; i++){
                cout << "q" << i << ": ";
                cin >> d;
                q.push_back(d);
            }
            break;
        }
        else if((c == "p") || (c == "P")){
            num = 9;
            p = {0, 0.05, 0.04, 0.02, 0.07, 0.08, 0.09, 0.04, 0.08, 0.03};
            q = {0.08, 0.06, 0.04, 0.04, 0.03, 0.06, 0.07, 0.06, 0.04, 0.02};
            // num = 5;
            // p = {0, 0.05, 0.15, 0.15, 0.1, 0.1};
            // q = {0.05, 0.1, 0.05, 0.1, 0.05, 0.1};
            break;
        }

        else{
            cout << "Wrong input!" << endl;
            cout << "Please enter m or p: ";
            cin >> c;
            continue;
        }
    }

    ans ans;

    ans = optimal_bst(p, q, num);

    cout << "Is the root table updated when t = e[i][j]:" << endl;

    for (int i=0; i<ans.s.size(); i++){
        cout << ans.s[i] << " ";
    }
    cout << endl;
    

    cout << "Smallest search cost:" << ans.e[1][num] << endl;
    cout << "Root:" << ans.r[1][num] << endl;
    // for(int i=0; i<ans.r.size(); i++){
    //     cout << "y" << endl;
    //     for(int j=0; j<ans.r[i].size(); j++){
    //         cout << ans.r[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    cout << "Optimal Binary Search Tree:" << endl;
    pri(ans.r, num);

    return 0;
}
