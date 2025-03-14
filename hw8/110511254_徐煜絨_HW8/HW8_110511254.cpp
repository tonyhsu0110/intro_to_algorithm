#include <bits/stdc++.h>
using namespace std;

struct m{
    int i;
    int j;
    int num;
    int cost;
};

int main()
{
    ifstream input;
    input.open("input.txt");
    ofstream output;
    output.open("110511254_output.txt");

    int n;

    queue<m> q;
    vector<vector<m>> map(19, vector<m> (19, {0, 0, 0, INT_MAX}));  // 初始化map
    vector<m> back;
    back.clear();

    int count = 1;
    
    while(input >> n){  // 把map建好
        map[1][1] = {1, 1, n, 0};

        for(int j=2; j<=17; j++){
            input >> n;
            map[1][j] = {1, j, n, INT_MAX};
        }

        for(int i=2; i<=17; i++){
            for(int j=1; j<=17; j++){
                input >> n;
                map[i][j] = {i, j, n, INT_MAX};
            }
        }

        // for(int i=1; i<=17; i++){
        //     for(int j=1; j<=17; j++){
        //         input >> n;
        //         map[i][j] = {i, j, n, INT_MAX};
        //         cout << "(" << i << ", " << j << ", " << n << ")";
        //     }
        //     cout << endl;
        // }

        if(map[1][1].num == 2){  // 起點就是陷阱的狀況
            map[1][1].cost = 1;
            q.push(map[1][1]);
        }
        else if(map[1][1].num == 1){
            map[1][1].cost = 0;
            q.push(map[1][1]);
        }
        else{
            // cout << "Pattern " << count << endl;
            // cout << "ERROR MAP (No Starting Point)" << endl;
            output << "Pattern " << count << endl;
            output << "ERROR MAP (No Starting Point)" << endl;
            break;
        }
        if((map[17][17].num != 1) && (map[17][17].num != 2)){ // 終點是牆壁的狀況
            // cout << "Pattern " << count << endl;
            // cout << "ERROR MAP (No End Point)" << endl;
            output << "Pattern " << count << endl;
            output << "ERROR MAP (No End Point)" << endl;
        }

        while(!q.empty()){ // 如果還有點沒被計算或更新，就要一直做
            int x = q.front().i;
            int y = q.front().j;
            int num = q.front().num;
            int cost = q.front().cost;
            // cout << "x=" << x << " y=" << y << " num=" << num << " cost=" << cost << endl;

            // 把周圍的點a放入q（當點a沒被造訪過，或可以得到更小的cost才會放進去q）

            if(map[x-1][y].num == 1){
                if((map[x-1][y].cost) > (cost+1)){
                    map[x-1][y].cost = cost+1;
                    q.push(map[x-1][y]);
                }
            }
            else if(map[x-1][y].num == 2){
                if((map[x-1][y].cost) > (cost+2)){
                    map[x-1][y].cost = cost+2;
                    q.push(map[x-1][y]);
                }
            }

            if(map[x+1][y].num == 1){
                if((map[x+1][y].cost) > (cost+1)){
                    map[x+1][y].cost = cost+1;
                    q.push(map[x+1][y]);
                }
            }
            else if(map[x+1][y].num == 2){
                if((map[x+1][y].cost) > (cost+2)){
                    map[x+1][y].cost = cost+2;
                    q.push(map[x+1][y]);
                }
            }

            if(map[x][y+1].num == 1){
                if((map[x][y+1].cost) > (cost+1)){
                    map[x][y+1].cost = cost+1;
                    q.push(map[x][y+1]);
                }
            }
            else if(map[x][y+1].num == 2){
                if((map[x][y+1].cost) > (cost+2)){
                    map[x][y+1].cost = cost+2;
                    q.push(map[x][y+1]);
                }
            }

            if(map[x][y-1].num == 1){
                if((map[x][y-1].cost) > (cost+1)){
                    map[x][y-1].cost = cost+1;
                    q.push(map[x][y-1]);
                }
            }
            else if(map[x][y-1].num == 2){
                if((map[x][y-1].cost) > (cost+2)){
                    map[x][y-1].cost = cost+2;
                    q.push(map[x][y-1]);
                }
            }

            q.pop();
        }

        if(map[17][17].num == 2){
            map[17][17].cost = map[17][17].cost - 1;
        }

        // cout << "pattern " << count << endl;
        // cout << "step=" << map[17][17].cost << endl;
        output << "pattern " << count << endl;
        output << "step=" << map[17][17].cost << endl;
        back.push_back(map[17][17]);
        
        int x = map[17][17].i;
        int y = map[17][17].j;
        int cost = map[17][17].cost;
        cost = cost - 1;

        // 把路線存到back裡面，從(17, 17)開始存

        while(cost>=0){
            if(map[x-1][y].cost == cost){
                back.push_back(map[x-1][y]);
                // cout << map[x-1][y].i << ", " << map[x-1][y].j << endl;
                if(map[x-1][y].num == 2){
                    back.push_back(map[x-1][y]);
                    // cout << map[x-1][y].i << ", " << map[x-1][y].j << endl;
                }
                cost = cost - map[x-1][y].num;
                x--;
            }
            else if(map[x+1][y].cost == cost){
                back.push_back(map[x+1][y]);
                // cout << map[x+1][y].i << ", " << map[x+1][y].j << endl;
                if(map[x+1][y].num == 2){
                    back.push_back(map[x+1][y]);
                    // cout << map[x+1][y].i << ", " << map[x+1][y].j << endl;
                }
                cost = cost - map[x+1][y].num;
                x++;
            }
            else if(map[x][y+1].cost == cost){
                back.push_back(map[x][y+1]);
                // cout << map[x][y+1].i << ", " << map[x][y+1].j << endl;
                if(map[x][y+1].num == 2){
                    back.push_back(map[x][y+1]);
                    // cout << map[x][y+1].i << ", " << map[x][y+1].j << endl;
                }
                cost = cost - map[x][y+1].num;
                y++;
            }
            else if(map[x][y-1].cost == cost){
                back.push_back(map[x][y-1]);
                // cout << map[x][y-1].i << ", " << map[x][y-1].j << endl;
                if(map[x][y-1].num == 2){
                    back.push_back(map[x][y-1]);
                    // cout << map[x][y-1].i << ", " << map[x][y-1].j << endl;
                }
                cost = cost - map[x][y-1].num;
                y--;
            }
            // cout << "cost left = " << cost << endl;
        }
        // cout << "size: " << back.size() << endl;

        // 印出路線，從(1, 1開始印)
        for(int p=back.size()-1; p>=0; p--){
            // cout << "(" << back[p].i << "," << back[p].j << ")" << endl;
            output << "(" << back[p].i << "," << back[p].j << ")" << endl;
        }
        // cout << endl;
        if(count <= 19){
            output << endl;
        }

        // 清空back，並開始做下一組pattern
        back.clear();
        count++;

    }



    input.close();
    output.close();
    return 0;
}