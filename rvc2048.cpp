/* ___________________________________________________________
 * ____________<<<___#_R_V_C_G_E_E_K_S___>>>__________________
 * CREATED BY #RVCGEEKS @PUNE for more rvchavadekar@gmail.com
 *
 * #RVCGEEKS 2048 game
 * created on 16.10.2018
 * 
*/

#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<vector>
#include<deque>
#include<ctime>
#define MAXUNDO 10
using namespace std;

class _2048{
    void process(char),display(),chkmax(),undo();
    long int maxtile;int n,check();
    vector< vector<long int> > v;
    vector<long int> r;
public:_2048();void play();
};
const char controls[]="adwsxu";  //L,R,U,D control chars and x for exit u for undo
const int colors[]={7,3,1,2,6,4,5};
deque<_2048> undo_mem;          //undo deque    

_2048::_2048(){
    srand(time(NULL));
    cout<<"Enter the board size :- ";
    cin>>n;v.resize(n);r.resize(n);
    for(int i=0;i<n;i++)
        v[i].assign(n,0);
}
void _2048::process(char move){
    deque<long int> d(n);
    for(int i=0;i<n;i++){d.clear();
        for(int j=0;j<n;j++){
            if(v[i][j]){if(move==controls[1])d.push_front(v[i][j]);
                else if(move==controls[0])d.push_back(v[i][j]);
                if(move==controls[0]||move==controls[1])v[i][j]=0;
            }if(v[j][i]){if(move==controls[2])d.push_back(v[j][i]);
                else if(move==controls[3])d.push_front(v[j][i]);
                if(move==controls[2]||move==controls[3])v[j][i]=0;}
        } int count=move==controls[1]||move==controls[3]?n-1:0;
        while(!d.empty()){int y=0,x=d.front();d.pop_front();
            if(!d.empty())y=d.front();
            if(x==y){d.pop_front();if(move==controls[2]||move==controls[3])  
                v[count][i]=x<<1;else v[i][count]=x<<1;      // or x*2
            }else if(move==controls[2]||move==controls[3])
                v[count][i]=x;else v[i][count]=x;
            if(move==controls[1]||move==controls[3])count--;
            else count++;}
    }chkmax();
}
int _2048::check(){
    int flag=0;r.clear();
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(!v[i][j]){
                r.push_back(n*i+j);
                flag++;
            }return flag;
}
void _2048::chkmax(){
    maxtile=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(v[i][j]>maxtile)
                maxtile=v[i][j];
}
void _2048::undo(){
    if(undo_mem.size()>1){
        undo_mem.pop_front();
        *this=undo_mem.front();
    }else cout<<"CANNOT UNDO MORE!!\n"; 
}
void _2048::display(){
    cout<<"\a  _________#RVCGEEKS 2048 Game__________\n"; // a little '\a' makes it cute ;)
    long int tmp1,tmp=maxtile;
    int color,space=1;cout<<"\n\n";
    while(tmp/=10)space++;
    for(int i=0;i<n;i++){cout<<"   ";
        for(int j=0;j<n;j++){int k=space;
            tmp1=tmp=v[i][j];color=0;
            while(tmp1/=2)color++;
            cout<<"\033[1;4"<<colors[color%7]<<"m";
            if(tmp)cout<<setw(k)<<left<<tmp;
            else while(k){cout<<" ";k--;}
            cout<<" \033[0m  ";
        }cout<<"\n\n";}
}
void _2048::play(){
    char move;int tmp;again:tmp=rand()%(n*n);
    if(!v[tmp/n][tmp%n])v[tmp/n][tmp%n]=2;
    else goto again;
    for(;;){system("clear");display();
        if(move!=controls[5])undo_mem.push_front(*this);
        again2:cout<<endl<<" a:left  d:right  w:up  s:down  x:exit  u:undo  (case independent)\n Enter your move: ";
        cin>>move;if((int)move<97)move+=32;  //if capital convert to small
        if(move!=controls[0]&&move!=controls[1]&&
           move!=controls[2]&&move!=controls[3]&&
           move!=controls[4]&&move!=controls[5]){
            cout<<"\nINVALID MOVE!! only adws...\n";
        goto again2;}
        if(!check()||move==controls[4])break;
        if(move==controls[5]){
            undo();display();continue;
        }process(move);
        again1:tmp=rand()%(r.size()); 
        tmp=r[tmp];
        if(!v[tmp/n][tmp%n])
            v[tmp/n][tmp%n]=2;
        else goto again1;
        if(undo_mem.size()>MAXUNDO)       //begin popping if overflow
            undo_mem.pop_back();
    }display();
    cout<<endl<<"\t\t ***** GAME ENDED ***** "<<endl
        <<"Maximum tile formed is: "<<maxtile<<endl;
}


main(){
    _2048 game;
    game.play();
    return 0;
}