#include <bits/stdc++.h>
using namespace std;

struct out{
    vector<int> r;
    vector<int> s;
    int price;
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

out bu1(vector<int> v, int length){
    vector<int> r(length+1, 0);
    vector<int> s(length+1, 0);

    for(int j=1; j<=length; j++){
        int q = INT_MAX;
        for(int i=1; i<=j && i<=10; i++){
            if(q >= v[i]+r[j-i]){
                q = v[i]+r[j-i];
                s[j] = i;
            }
        }
        r[j] = q;
    }
    return {r, s, r[length]};
}

out bu2(vector<int> v, int length){
    vector<int> r(length+1, 0);
    vector<int> s(length+1, 0);

    for(int j=1; j<=length; j++){
        int q = INT_MIN;
        for(int i=1; i<=j && i<=10; i++){
            if(q <= v[i]+r[j-i]){
                q = v[i]+r[j-i];
                s[j] = i;
            }
        }
        r[j] = q;
    }
    return {r, s, r[length]};
}

int pri(out outp, int length){
    int templ = length;
    int count = 0;
    while(templ > 0){
        if(outp.s[templ]!=0){
            cout << outp.s[templ] << " ";
            count++;
            templ = templ - outp.s[templ];
        }
        else{
            cout << templ;
            count++;
            return count;
        }
    }
    cout << endl;
    return count;
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

    // top down
    out outt1, outt2;
    outt1 = td1(price, length);
    outt2 = td2(price, length);

    cout << "Top Down:" << endl;
    cout << "total length: " << length << endl;
    cout << "maximum price: " << outt1.price << endl;
    
    int c = pri(outt1, length);
    cout << "number of pieces: " << c << endl;
    cout << endl;
    cout << "minimum price: " << outt2.price << endl;
    c = pri(outt2, length);
    cout << "number of pieces: " << c << endl;

    cout << endl;

    // bottom up
    out outb1, outb2;
    outb2 = bu2(price, length);
    outb1 = bu1(price, length);
    cout << "Bottom Up:" << endl;
    cout << "total length: " << length << endl;
    cout << "maximum price: " << outb2.price << endl;
    c = pri(outb2, length);
    cout << "number of pieces: " << c << endl;
    cout << endl;
    cout << "minimum price: " << outb1.price << endl;
    c = pri(outb1, length);
    cout << "number of pieces: " << c << endl;

    return 0;
}