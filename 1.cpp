#include <bits/stdc++.h>
using namespace std;
/**
 * 面积树
 * 四叉树
 * **/
int str_to_int(string a){
    int sum = 0;
    for(int i = 0; i < a.length(); i ++){
        sum = sum * 10 + (a[i] - '0');
    }
    return sum;
}
int tot = 0;
const int MAXN = 1e6 + 5;
struct AREA_tree{
    struct NODE{
        int lx, ly, rx, ry, sum;
        int son[4];
        /*
        0 <xmid + 1, ymid + 1> <rx, ry>
        1 <lx, ymid + 1> <xmid, ry>
        2 <lx, ly> <xmid, ymid>
        3 <xmid + 1, ly> <rx, ymid>
        */
    }tree[MAXN];
    void Init_NODE(NODE x){
        memset(x.son, -1, sizeof(x.son));
    }
    void Init(){
        tot = 0;
    }
    int add(int lx, int ly, int rx, int ry){
        tree[tot].lx = lx, tree[tot].rx = rx, tree[tot].ly = ly, tree[tot].ry = ry;
        Init_NODE(tree[tot]);
        tree[tot].sum = 0;
        return tot ++;
    }
    void update(int root, int x, int y, int value){
        if(tree[root].lx <= x && tree[root].ly <= y && tree[root].rx >= x && tree[root].ry >= y){
            tree[root].sum += value;
            return ;
        }
        int xmid = (tree[root].lx + tree[root].rx) >> 1;
        int ymid = (tree[root].ly + tree[root].ry) >> 1;
        /*
        0 <xmid + 1, ymid + 1> <rx, ry>
        1 <lx, ymid + 1> <xmid, ry>
        2 <lx, ly> <xmid, ymid>
        3 <xmid + 1, ly> <rx, ymid>
        */
       int rx, ry, lx, ly;
       rx = tree[root].rx, ry = tree[root].ry, lx = tree[root].lx, ly = tree[root].ly;
        if(x <= rx && y <= ry && x >= xmid + 1 && y >= ymid + 1){
            if(tree[root].son[0] == -1){
                tree[root].son[0] = add(xmid + 1, ymid + 1, rx, ry);
            }
            update(tree[root].son[0], x, y, value);
        }
        else if(x <= xmid && y <= ry && x >= lx && y >= ymid + 1){
            if(tree[root].son[1] == -1){
                tree[root].son[1] = add(lx, ymid + 1, xmid, ry);
            }
            update(tree[root].son[1], x, y, value);
        }
        else if(x <= xmid && y <= ymid && x >= lx && y >= ly){
            if(tree[root].son[2] == -1){
                tree[root].son[2] = add(lx, ly, xmid, ymid);
            }
            update(tree[root].son[2], x, y, value);
        }
        else if(x <= rx && y <= ymid && x >= xmid + 1 && y >= ly){
            if(tree[root].son[3] == -1){
                tree[root].son[3] = add(xmid + 1, ly, rx, ymid);
            }
            update(tree[root].son[3], x, y, value);
        }
        for(int i = 0; i < 4; i ++){
            if(tree[root].son[i] != -1){
                tree[root].sum += tree[tree[root].son[i]].sum;
            }
        }
        return ;
    }
    int query(int root, int xmin, int ymin, int xmax, int ymax){
        if(tree[root].lx >= xmin && tree[root].ly >= ymin && tree[root].rx <= xmax && tree[root].ry <= ymax){
            return tree[root].sum;
        }
        int xmid = (tree[root].lx + tree[root].rx) >> 1;
        int ymid = (tree[root].ly + tree[root].ry) >> 1;
        /*
        0 <xmid + 1, ymid + 1> <rx, ry>
        1 <lx, ymid + 1> <xmid, ry>
        2 <lx, ly> <xmid, ymid>
        3 <xmid + 1, ly> <rx, ymid>
        */
        int rx, ry, lx, ly;
        rx = tree[root].rx, ry = tree[root].ry, lx = tree[root].lx, ly = tree[root].ly;
        int re = 0;
        if(xmin <= xmid && ymin <= ymid){
            if(tree[root].son[2] != -1)
            re += query(tree[root].son[2], xmin, ymin, xmax, ymax);
        }
        if(xmax > xmid && ymin <= ymid){
            if(tree[root].son[3] != -1)
            re += query(tree[root].son[3], xmin, ymin, xmax, ymax);
        }
        if(xmin <= xmid && ymax > ymid){
            if(tree[root].son[1] != -1)
            re += query(tree[root].son[1], xmin, ymin, xmax, ymax);
        }
        if(xmax > xmid && ymax > ymid){
            if(tree[root].son[0] != -1)
            re += query(tree[root].son[0], xmin, ymin, xmax, ymax);
        }
        cout << re << endl;
        return re;
    }
}area_tree;
int main(){
    ios::sync_with_stdio(false);
    string str;
    int flag = 0;///0 - I 1 - Q
    area_tree.Init();
    area_tree.add(1, 1, 20005, 20005);
    while(cin >> str){
        if(str[0] == 'E')   break;
        if(str[0] == 'I') {
            flag = 0; continue;
        }
        if(str[0] == 'Q') {
            flag = 1; continue;
        }
        if(flag == 0){
            int x = str_to_int(str);
            int y, z;
            cin >> y >> z;
            area_tree.update(0, x, y, z);
        }
        else if(flag == 1){
            int x1, y1, x2, y2;
            x1 = str_to_int(str);
            cin >> y1 >> x2 >> y2;
            cout << area_tree.query(0, x1, y1, x2, y2) << endl;
        }
    }
    return 0;
}