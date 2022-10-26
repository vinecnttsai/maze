#include <iostream>

#include <vector>

#include <SFML/Graphics.hpp>

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

using namespace std;

using namespace sf;

const int starta=2,startb=2,a=81,b=81,pia=1520,pib=1520,enda=a-3,endb=b-3;

const float spacea=pia/a,spaceb=pib/b;

int n[a][b],v[a][b],f[a][b],nowcount=0,total=((b)/2)*((a)/2),posa=0,posb=0,rate=2000;

bool r[4];

RectangleShape re;
   
RenderWindow window(VideoMode(pia, pib), "My window");

vector<int> x,y,fa,fb;

int main()

{
   
    int i,k;
   
    bool isstart=false;
   
    re.setSize(Vector2f(spacea,spaceb));
   
    void create_maze();
   
    int count_visit(int pos,int pos2);

    void dfs(int posx,int posy);
   
    void print_maze();

    void find_way(int nowa,int nowb);

    void find_way_first();

    srand(time(NULL));
   
    create_maze();

    while (window.isOpen())
    {
       
        Event event;

        while (window.pollEvent(event))
        {
           
            if (event.type == Event::Closed)
                window.close();
        }
        if(!isstart)
        {
   
            dfs(starta,startb);

            n[enda][endb]=1;

            find_way_first();

            find_way(starta, startb);
           
            isstart=true;
        }
    }
   
return 0;

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

    n[starta][startb]=2;



}
void print_maze()
{
    window.clear(Color::White);
    int i,k;
        for(i=0;i<a;i++)
        {
            for(k=0;k<b;k++)
            {
                if(n[i][k]==0)
                {
                re.setFillColor(Color::Black);
                }
                else if(n[i][k]==1)
                {
                re.setFillColor(Color::White);
                }
                else
                {
                re.setFillColor(Color::Red);
                }
                re.setPosition(Vector2f(spacea*i,spaceb*k));
                window.draw(re);
            }
        }

        window.display();
}

int count_visit(int pos,int pos2)

{

    int num=0,i;


    for(i=0;i<4;i++)r[i]=false;

    if(!v[pos][pos2+2])

    {

        num++;

        r[0]=true;

    }

    if(!v[pos][pos2-2])

    {

        num++;

        r[1]=true;

    }

    if(!v[pos+2][pos2])

    {

        num++;

        r[2]=true;

    }

    if(!v[pos-2][pos2])

    {

        r[3]=true;

        num++;

    }

    return num;

}

void dfs(int posx,int posy)

{

    int c,i;

    c=count_visit(posx, posy);

    usleep(rate);
   
    print_maze();

    if(c==1)

    {

        if(nowcount>=total)return;

        x.insert(x.begin(),posx);

        y.insert(y.begin(),posy);

        if(v[posx][posy])nowcount++;

        v[posx][posy]=true;

        if(r[0])

        {

            n[posx][posy+1]=1;

            dfs(posx,posy+2);

        }

        else if(r[1])

        {

            n[posx][posy-1]=1;

            dfs(posx,posy-2);

        }

        else if(r[2])

        {

            n[posx+1][posy]=1;

            dfs(posx+2,posy);

        }

        else if(r[3])

        {

            n[posx-1][posy]=1;

            dfs(posx-2,posy);

        }

    }

    else if(c>1)

    {

        if(nowcount>=total)return;

        while(true)

        {

            i=rand()%4;

            if(r[i])

            {

                x.insert(x.begin(),posx);

                y.insert(y.begin(),posy);

                if(v[posx][posy])nowcount++;

                v[posx][posy]=true;

                if(i==0)

                {

                    n[posx][posy+1]=1;

                    dfs(posx,posy+2);

                }

                else if(i==1)

                {

                    n[posx][posy-1]=1;

                    dfs(posx,posy-2);

                }

                else if(i==2)

                {

                    n[posx+1][posy]=1;

                    dfs(posx+2,posy);

                }

                else if(i==3)

                {

                    n[posx-1][posy]=1;

                    dfs(posx-2,posy);

                }

                break;

            }

            else

            {

                i=rand()%4;

            }

        }

    }

    else if(c==0)

    {

        if(nowcount>=total)return;

        v[posx][posy]=true;

        nowcount++;

        posx=x[0];

        posy=y[0];

        x.erase(x.begin());

        y.erase(y.begin());

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
    usleep(rate*2);
    print_maze();
    if(nowa==enda&&nowb==endb)
    {
         n[enda][endb]=2;
         n[starta][startb]=2;
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
