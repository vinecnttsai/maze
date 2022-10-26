#include <iostream>

#include <vector>

#include <stdio.h>

#include <stdlib.h>

using namespace std;

const int startx=2,starty=2,a=51,b=101,enda=a-3,endb=b-3;

int n[a][b],v[a][b],f[a][b],nowcount=0,total=((b-3)/2)*((a-3)/2),dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};


bool r[4];

struct point
{
    int x,y,step;
};
vector<point> p;

int main()

{

    void create_maze();
    
    void find_way(int nowa,int nowb);

    void print_maze();
    
    void check_path();

    int count_visit(int pos,int pos2);
    
    void bfs(int n,int nowa,int nowb);

    void dfs(int posx,int posy);
    
    void find_way_first();

    srand(time(NULL));

    create_maze();
    
    print_maze();
    
    p.clear();

    dfs(startx,starty);
    
    n[enda][endb]=2;
    
    print_maze();
    
    n[enda][endb]=1;
    
    find_way_first();
    
    p.clear();
    
    find_way(startx, starty);
    
    print_maze();

return 0;

}

void print_maze()

{

    int i,k;

    for(i=0;i<a;i++)

    {

        for(k=0;k<b;k++)

        {

            switch(n[i][k])

            {

                case 0:

                    cout<<"█";

                    break;

                case 1:

                    cout<<" ";

                    break;

                case 2:

                    cout<<"o";

                    break;
                case 3:
                    
                    cout<<"r";
                    
                    break;
            }
        }

        cout<<endl;

    }

}

void create_maze()

{

    int i,k;

    for(i=0;i<a;i++)

        for(k=0;k<b;k++)

        {

            n[i][k]=0;

            v[i][k]=true;
            

        }

    for(i=0;i<a;i++)

    {

        n[i][0]=1;

        n[i][b-1]=1;

        v[i][0]=true;

        v[i][b-1]=true;
        

    }

    for(i=0;i<b;i++)

    {

        n[0][i]=1;

        n[a-1][i]=1;

        v[0][i]=true;

        v[a-1][i]=true;
        

    }//外層空氣牆

    

    

    for(i=2;i<a-2;i++)

    {

        for(k=2;k<b-2;k++)

        {

            n[i][k]=1;

            v[i][k]=false;

        }

    }//內層道路

    for(i=2;i<a-2;i+=2)

    {

        for(k=3;k<b-2;k+=2)

        {

            n[i][k]=0;

            v[i][k]=true;

        }

    }

    for(i=3;i<a-2;i+=2)

    {

        for(k=2;k<b-2;k++)

        {

            n[i][k]=0;

            v[i][k]=true;

        }

    }

    n[startx][starty]=2;



}

int count_visit(int pos,int pos2)

{

    int num=0,i;

    for(i=0;i<4;i++)r[i]=false;
    
    for(i=0;i<4;i++)
    {
        if(!v[pos+2*dir[i][0]][pos2+2*dir[i][1]])
        {
            num++;
            r[i]=true;
        }
    }
    return num;

}

void dfs(int posx,int posy)
{

    int c,i;
    
    if(nowcount>=total)return;
    
    c=count_visit(posx, posy);
    
    if(!v[posx][posy])nowcount++;
    if(c)p.inset(p.begin(),{posx,posy});
    v[posx][posy]=true;

    if(c==1)
    {
        
        for(int i=0;i<4;i++)
        {
            if(r[i])
            {
                n[posx+dir[i][0]][posy+dir[i][1]]=1;
                dfs(posx+dir[i][0]*2,posy+dir[i][1]*2);
            }
        }

    }
    else if(c>1)
    {
        while(true)
        {
            i=rand()%4;
            if(r[i])
            {
                n[posx+dir[i][0][posy+dir[i][1]]=1;
                dfs(posx+dir[i][0]*2,posy+dir[i][1]*2);
                break;

            }
            else i=rand()%4;

        }

    }
    else if(c==0)
    {
        posx=p.front().x;
        posy=p.front().y;
        p.erase(p.begin());
        dfs(posx,posy);
    }

}
void find_way_first()
{
    int i,k;
    for(i=0;i<a;i++)
    {
        for(k=0;k<b;k++)f[i][k]=true;
    }
}
void find_way(int nowa,int nowb)
{
    if(nowa==enda&&nowb==endb)
    {
        n[nowa][nowb]=2;
        print_maze();
        return;
    }
    
    n[nowa][nowb]=2;
    
    bool falg=false;
    for(int i=0;i<4;i++)
    {
        int newa=nowa+dir[i][0],newb=nowb+dir[i][1];
        if(n[newa][newb]==1&&f[newa][newb])
        {
            p.insert(p.begin(),{nowa,nowb});
            find_way(newa,newb);
            flag=true;
        }
    }
    if(!flag)
    {
        n[nowa][nowb]=1;
        f[nowa][nowb]=false;
        nowa=p.front().x;
        nowb=p.front().y;
        p.erase(p.begin());
        find_way(nowa, nowb);
    }
          
    
}
void bfs(int n,int nowa,int nowb)
{
    int i;
    if(nowa==n-2&&nowb==n-2)
    {
        cout<<p.front().step<<endl;
        return;
    }
    
    if(p.empty())
    {
        cout<<"No solution!"<<endl;
        return;
    }
    
    v[nowa][nowb]=true;
    for(i=0;i<4;i++)
    {
        if(!v[nowa+dir[i][0]][nowb+dir[i][1]])
        {
            p.push_back({nowa+dir[i][0],nowb+dir[i][1],p.front().step+1});
        }
    }
    p.erase(p.begin());
    bfs(n,p.front().x,p.front().y);
}
