#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

#define MAX 100
#define INFINITY 1000
#define INPUT "input"
#define OUTPUT "output"


using namespace std;

struct Node
{
    int pre; //dinh ke truoc
    int attr; // 0 - chua gan nha, 1 - da gan nhan, 2 - da danh dau
    int x; //kha nang thong qua cua dinh dang xet
};

int n; // so dinh
int beginNode, endNode;
int c[MAX][MAX]; //kha nang thong qua cua dinh tuong ung voi nhau
int f[MAX][MAX]; //luong hien tai cua cac cung tuong ung
Node node[MAX]; //cac dinh
int max_f; //gia tri luong cuc dai

void Input(); //nhap du lieu
void Init(); //khoi tao luong ban dau
void FordFulkerson();
void Output(); //xuat ket qua

void ReSetLabel(); //xoa cac nhan, dat lai nhan cho dinh phat
void SetNode(Node &node, int pre, int attr, int x); //set cac thuoc tinh cho node
char p[] = "sabcdt";


int main()
{
    Input();
    cout << "Input done !" << endl;

    Init();
    cout << "Init done !" << endl;

    FordFulkerson();
    cout << "ForkFulkerson done !" << endl;

    Output();
    cout << "Output done !" << endl;


    return 0;
}

void Input()
{
    ifstream inputFile;
    inputFile.open(INPUT, ios::in);

    //nhap n tu file
    inputFile >> n;

    //nhap gia tri tu file vao ma tran
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            inputFile >> c[i][j];
        }
    }

    inputFile >> beginNode >> endNode;

    inputFile.close();
}


void Init()
{
    max_f = 0; //luong cuc dai ban dau = 0
    //khoi tao luong ban dau bang 0
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            f[i][j] = 0;
        }
    }
}

void SetNode(Node &node, int pre, int attr, int x)
{
    node.pre = pre;
    node.attr = attr;
    node.x = x;
}

void ReSetLabel()
{
    //cac dinh ban dau chua co nhan
    for(int i = 0; i < n; i++)
    {
        SetNode(node[i], -1, 0, 0);
    }
     //gan nhan cho dinh phat
    SetNode(node[beginNode], 0, 1, INFINITY);
}

void FordFulkerson()
{
    while(true)//thuc hien cho den khi ko the danh dau duoc nua - ko con dinh nao de danh dau, ket thuc chuong trinh
    {
        ReSetLabel();

        while(node[endNode].attr == 0)
        {
            //danh dau dinh v - da gan nhan co chi so nho nhat
            int k;  // index cua dinh can danh dau v trong node[]

            for(k = 0; k < n; k++)
            {
                if(node[k].attr == 1) break; //dinh co nhan co chi so nho nhat
            }

            if(k == n) return; //ko con dinh nao de danh dau, ket thuc chuong trinh

            //danh dau dinh v
            SetNode(node[k], node[k].pre, 2, node[k].x);

            //gan nhan cho cac dinh ke v chua co nhan
            for(int i = 0; i < n; i++)
            {
                if(node[i].attr == 0) // chi xet cac node chua gan nhan
                {
                    if(c[k][i] > 0 && f[k][i] < c[k][i]) // cung (v, W);
                    {
                        SetNode(node[i], k, 1, (node[k].x < c[k][i] - f[k][i]) ? node[k].x : (c[k][i] - f[k][i]));
                        if(i == endNode) break; //break neu endNode da co nhan
                    }
                    else if(c[i][k] > 0 && f[k][i] > 0) //cung (W.v)
                    {
                        SetNode(node[i], k, 1, (node[k].x <f[k][i]) ? node[k].x : f[k][i]);
                        if(i == endNode) break; //break neu endNode da co nhan
                    }
                }
            }
        }

        //Hieu chinh luong
        int delta = node[endNode].x;
        max_f += delta; //tang luong cuc dai
        int s = endNode;
        while(s != beginNode) //truy nguoc dinh
        {
            //fij < cij thi cung chieu di
            if(f[node[s].pre][s] < c[node[s].pre][s]) // tuong duong f > 0 (fij >0 khi i < j)
            {
                f[node[s].pre][s] =  f[node[s].pre][s] + delta; //luong thuan thi cong
            }
            else if(f[node[s].pre][s] < 0)//  //fij < 0 thi nguoc chieu di
            {
                f[node[s].pre][s] =  f[node[s].pre][s] - delta; //luong nguoc thi tru
            }
            s = node[s].pre; //truy nguoc dinh
        }
    }
}

void Output()
{
    ofstream outFile;
    outFile.open(OUTPUT, ios::out);

    outFile << max_f << endl;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            outFile << setw(5) << f[i][j];
        }
        outFile << endl;
    }
    outFile.close();
}
