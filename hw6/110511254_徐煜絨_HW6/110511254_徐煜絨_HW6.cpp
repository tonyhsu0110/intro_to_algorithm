#include <bits/stdc++.h>
using namespace std;

struct ans{
    vector<vector<int>> c;
    vector<vector<int>> b;
};

void gen(vector<double> &x, int size)
{
    for(int i=1; i<=size; i++) 
    {
        double temp = rand()%100 + 1;
        cout << temp << " ";
        x.push_back(temp);
    }
    cout << endl;
}

ans LCS_Length(vector<double> x, vector<double> y){
    int m = x.size();
    int n = y.size();
    vector<vector<int>> b(m+1, vector<int> (n+1, 0));
    // up-left: 1, up: 2, left: 3
    vector<vector<int>> c(m+1, vector<int> (n+1, 0));

    for(int i=1; i<=m; i++){
        for(int j=1; j<=n; j++){
            if(x[i] == y[j]){
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = 1;
            }
            else if(c[i-1][j] >= c[i][j-1]){
                c[i][j] = c[i-1][j];
                b[i][j] = 2;
            }
            else{
                c[i][j] = c[i][j-1];
                b[i][j] = 3;
            }
        }
    }
    return {c, b};
}

void Print_LCS(int &count, vector<vector<int>> b, vector<double> x, int i, int j){
    if((i == 0) || (j == 0)){
        return;
    }
    if(b[i][j] == 1){
        Print_LCS(count, b, x, i-1, j-1);
        cout << x[i] << " ";
        count++;
    }
    else if(b[i][j] == 2){
        Print_LCS(count, b, x, i-1, j);
    }
    else{
        Print_LCS(count, b, x, i, j-1);
    }
    return;
}

vector<double> Produce(vector<double> &result, vector<vector<int>> b, vector<double> x, int i, int j){
    if((i == 0) || (j == 0)){
        return result;
    }
    if(b[i][j] == 1){
        Produce(result, b, x, i-1, j-1);
        result.push_back(x[i]);
        // cout << x[i] << " ";
    }
    else if(b[i][j] == 2){
        Produce(result, b, x, i-1, j);
    }
    else{
        Produce(result, b, x, i, j-1);
    }
    return result;
}

int main()
{
    // srand(time(0));
    vector<double> x;
    vector<double> y;
    vector<double> z;
    vector<double> xy;
    int n1, n2, n3;
    cout << "Input N1, N2, N3 (1<=length<1000)" << endl;
    cout << "N1: ";
    cin >> n1;
    cout << "N2: ";
    cin >> n2;
    cout << "N3: ";
    cin >> n3;

    x.clear();
    y.clear();
    z.clear();

    x.push_back(0);
    y.push_back(0);
    z.push_back(0);

    double temp;

    // gen(x, n1);
    // gen(y, n2);
    // gen(z, n3);

    for(int i = 1; i<=n1; i++){
        cout << "x[" << i << "] = ";
        cin >> temp;
        x.push_back(temp);
    }
    for(int i = 1; i<=n2; i++){
        cout << "y[" << i << "] = ";
        cin >> temp;
        y.push_back(temp);
    }
    for(int i = 1; i<=n3; i++){
        cout << "z[" << i << "] = ";
        cin >> temp;
        z.push_back(temp);
    }

    double time_xy1, time_xy2, time_xy3, time_xy4;
    ans ans1, ans2;
    time_xy1 = (double)clock()/CLOCKS_PER_SEC;
    ans1 = LCS_Length(x, y);
    time_xy2 = (double)clock()/CLOCKS_PER_SEC;

    // cout << "X and Y: " << time_xy2 - time_xy1 << endl;

    xy.clear();
    time_xy3 = (double)clock()/CLOCKS_PER_SEC;
    xy.push_back(0);
    Produce(xy, ans1.b, x, n1, n2);
    time_xy4 = (double)clock()/CLOCKS_PER_SEC;
    
    // cout << "Make XY: " << time_xy4 - time_xy3 << endl;

    double time_z1, time_z2, time_z3, time_z4;
    time_z1 = (double)clock()/CLOCKS_PER_SEC;
    ans2 = LCS_Length(xy, z);
    time_z2 = (double)clock()/CLOCKS_PER_SEC;

    // cout << "XY and Z: " << time_z2 - time_z1 << endl;

    int n4 = xy.size()-1;  // not to count the initial element
    int count;
    cout << "LCS: ";
    count = 0;
    time_z3 = (double)clock()/CLOCKS_PER_SEC;
    Print_LCS(count, ans2.b, xy, n4, n3);
    time_z4 = (double)clock()/CLOCKS_PER_SEC;
    cout << endl;

    // cout << "Print LCS: " << time_z4 - time_z3 << endl;

    cout << "Length of LCS: " << count << endl;
    return 0;
}