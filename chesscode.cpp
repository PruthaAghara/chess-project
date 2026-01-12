//    0  1  2  3  4  5  6  7
// 0  r  n  b  q  k  b  n  r  
// 1  x  x  x  x  x  x  x  x  
// 2  .  .  .  .  .  .  .  .  
// 3  .  .  .  .  .  .  .  .  
// 4  .  .  .  .  .  .  .  .
// 5  .  .  .  .  .  .  .  .  
// 6  P  P  p  P  P  P  P  P
// 7  R  N  B  Q  K  B  N  R
#include<iostream>
#include <unistd.h>
using namespace std;
int gameover=0;


void clearScreen() {//it will clear the screen
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


class rock;
class pawn;
class knight;
class bishop;
class queen;
class king;
class chess
{
    public:
    char board[8][8]={{'r','n','b','k','q','b','n','r'},
        {'x','x','x','x','x','x','x','x'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'P','P','P','P','P','P','P','P'},
        {'R','N','B','K','Q','B','N','R'}};
    int point_w=0,point_b=0;
    int s_r,u_r,s_c,u_c,wb;
    void board_pri()
    {
        clearScreen();
        cout<<"\n     A B C D E F G H \n\n";
        for(int i=0;i<8;i++)
        {
            cout<<i+1<<"    ";
            for(int j=0;j<8;j++)
            {
                cout<<board[i][j]<<" ";
            }
            cout<<"\t"<<i+1<<endl;
        }
        cout<<"\n     A B C D E F G H \n";
        cout<<"\nWHITE'S POINT : "<<point_w<<"\nBLACK'S POINT : "<<point_b<<endl;
    }


    bool move(int s_r,int s_c,int u_r,int u_c,int wb);


    bool our_ele_small(char ch)//White
    {
        switch (ch)
        {
            case 'x':
            case 'r':
            case 'n':
            case 'b':
            case 'k':
            case 'q':
                return true;
                break;
            default:
                return false;
                break;
        }
    }


    bool our_ele_big(char ch)//Black
    {
        switch (ch)
        {
            case 'P':
            case 'R':
            case 'N':
            case 'B':
            case 'K':
            case 'Q':
                return true;
                break;
            default:
                return false;
                break;
        }
    }


    bool valid_white(int s_r,int s_c,int u_r,int u_c)
    {
        if(our_ele_big(board[u_r][u_c]))
            {
                cout<<"YOU ARE NOT ABLE TO CAPTURE YOUR ELEMENTS.\n";
                return false;
            }
        else if(our_ele_small(board[s_r][s_c]))
            {
                cout<<"USE YOUR OWN ELEMENTS.\n";
                return false;
            }
            else
            {
                return true;
            }
    }


    bool valid_black(int s_r,int s_c,int u_r,int u_c)
    {
        if(our_ele_small(board[u_r][u_c]))
            {
                cout<<"YOU ARE NOT ABLE TO CAPTURE YOUR ELEMENTS.\n";
                return false;
            }
        else if(our_ele_big(board[s_r][s_c]))
            {
                cout<<"USE YOUR OWN ELEMENTS.\n";
                return false;
            }
            else
                return true;
    }


    bool move_ele(int s_r,int s_c,int u_r,int u_c)
    {
        if(board[u_r][u_c]!='.')
            point_cal(u_r,u_c);
        board[u_r][u_c] = board[s_r][s_c];
        board[s_r][s_c] = '.';
        return true;
    }
    bool invalid()
    {
        cout<<"INVALID MOVE.\n";
        return false;
    }


    void point_cal(int u_r,int u_c)
    {
        if(u_r==-1&&u_c==0)
        {
            point_b++;
        }
        else if(u_r==-1&&u_c==-1)
        {
            point_w++;
        }
        switch (board[u_r][u_c])
        {
        case 'P'://white
            point_w++;
            break;
        case 'R':
            point_w+=5;
            break;
        case 'N':
            point_w+=3;
            break;
        case 'B':
            point_w+=3;
            break;
        case 'Q':
            point_w+=9;
            break;
        case 'K':
            point_w+=INT64_MAX;
            break;
        case 'x'://black
            point_b++;
            break;
        case 'r':
            point_b+=5;
            break;
        case 'n':
            point_b+=3;
            break;
        case 'b':
            point_b+=3;
            break;
        case 'q':
            point_b+=9;
            break;
        case 'k':
            point_b+=INT64_MAX;
            break;
        }
    }
    int con(char x)
    {
    if(x>=97 && x<=104)
        return x-97;
    else if(x>=65 && x<=72)
        return x-65;
    else
    {
        cout<<"ENTER VALID COL.\n";
        return -1;
    }
    }
};


class pawn : public virtual chess
{
    int dir_c=u_c-s_c;
    public :
    bool Pawn(chess & ob1, int s_r, int s_c, int u_r, int u_c, int wb) //done ✅ 💯
    {
        if(wb == 1) // White
        {
            if(!ob1.valid_white(s_r, s_c, u_r, u_c))
                return ob1.invalid();
            // En Passant Left
            else if(s_r == 3 && ob1.board[s_r][s_c - 1] == 'x' && u_r - s_r == -1 && u_c - s_c == -1)
            {
                ob1.board[s_r][s_c - 1] = '.';
                ob1.board[u_r][u_c] = ob1.board[s_r][s_c];
                ob1.board[s_r][s_c] = '.';
                ob1.point_cal(-1, 0);
                cout<<"EN PASSANT\n";
                return true;
            }
            // En Passant Right
            else if(s_r == 3 && ob1.board[s_r][s_c + 1] == 'x' && u_r - s_r == -1 && u_c - s_c == 1)
            {
                ob1.board[s_r][s_c + 1] = '.';
                ob1.board[u_r][u_c] = ob1.board[s_r][s_c];
                ob1.board[s_r][s_c] = '.';
                cout<<"EN PASSANT\n";
                ob1.point_cal(-1, 0);
                return true;
            }
            // First Move with 2-step option
            else if(s_r == 6)
            {
                if(s_r - u_r == 2 && s_c == u_c && ob1.board[s_r - 1][s_c] == '.' && ob1.board[u_r][u_c] == '.')
                    return ob1.move_ele(s_r, s_c, u_r, u_c);
                else if(s_r - u_r == 1 && (s_c - u_c == 1 || u_c - s_c == 1) && ob1.our_ele_small(ob1.board[u_r][u_c]))
                    return ob1.move_ele(s_r, s_c, u_r, u_c);
                else if(s_r - u_r == 1 && s_c == u_c && ob1.board[u_r][u_c] == '.')
                    return ob1.move_ele(s_r, s_c, u_r, u_c);
                else
                    return ob1.invalid();
            }
            // Normal Move or Capture
            else if(s_r - u_r == 1 && u_r != 0)
            {
                if((s_c - u_c == 1 || u_c - s_c == 1) && ob1.our_ele_small(ob1.board[u_r][u_c]))
                    return ob1.move_ele(s_r, s_c, u_r, u_c);
                else if(s_c == u_c && ob1.board[u_r][u_c] == '.')
                    return ob1.move_ele(s_r, s_c, u_r, u_c);
                else
                    return ob1.invalid();
            }
            // Promotion
            else if(s_r - u_r == 1 && u_r == 0)
            {
                int ele;
                cout << "WHICH ONE YOU HAVE TO SELECT : \n1.QUEEN\n2.BISHOP\n3.ROOK\n4.KNIGHT    (ENTER NUMBER)\n";
                cin >> ele;
                switch (ele)
                {
                    case 1:
                        ob1.board[u_r][u_c] = 'Q';
                        break;
                    case 2:
                        ob1.board[u_r][u_c] = 'B';
                        break;
                    case 3:
                        ob1.board[u_r][u_c] = 'R';
                        break;
                    case 4:
                        ob1.board[u_r][u_c] = 'N';
                        break;
                    default:
                        cout << "SELECT VALID OPTION.\n";
                        return false;
                }
                ob1.board[s_r][s_c] = '.';
                return true;
            }
            else
                return ob1.invalid();
        }
        else // Black
        {
            if(!ob1.valid_black(s_r, s_c, u_r, u_c))
                return ob1.invalid();
            // En Passant Left
            else if(s_r == 4 && ob1.board[s_r][s_c - 1] == 'P' && u_r - s_r == 1 && u_c - s_c == -1)
            {
                ob1.board[s_r][s_c - 1] = '.';
                ob1.board[u_r][u_c] = ob1.board[s_r][s_c];
                ob1.board[s_r][s_c] = '.';
                ob1.point_cal(-1, -1);
                cout<<"EN PASSANT\n";
                return true;
            }
            // En Passant Right
            else if(s_r == 4 && ob1.board[s_r][s_c + 1] == 'P' && u_r - s_r == 1 && u_c - s_c == 1)
            {
                ob1.board[s_r][s_c + 1] = '.';
                ob1.board[u_r][u_c] = ob1.board[s_r][s_c];
                ob1.board[s_r][s_c] = '.';
                ob1.point_cal(-1, -1);
                cout<<"EN PASSANT\n";
                return true;
            }
            // First Move with 2-step option
            else if(s_r == 1)
            {
                if(s_r - u_r == -2 && s_c == u_c && ob1.board[s_r + 1][s_c] == '.' && ob1.board[u_r][u_c] == '.')
                    return ob1.move_ele(s_r, s_c, u_r, u_c);
                else if(s_r - u_r == -1 && (s_c - u_c == 1 || u_c - s_c == 1) && ob1.our_ele_big(ob1.board[u_r][u_c]))
                    return ob1.move_ele(s_r, s_c, u_r, u_c);
                else if(s_r - u_r == -1 && s_c == u_c && ob1.board[u_r][u_c] == '.')
                    return ob1.move_ele(s_r, s_c, u_r, u_c);
                else
                    return ob1.invalid();
            }
            // Normal Move or Capture
            else if(s_r - u_r == -1 && u_r != 7)
            {
                if((s_c - u_c == 1 || u_c - s_c == 1) && ob1.our_ele_big(ob1.board[u_r][u_c]))
                    return ob1.move_ele(s_r, s_c, u_r, u_c);
                else if(s_c == u_c && ob1.board[u_r][u_c] == '.')
                    return ob1.move_ele(s_r, s_c, u_r, u_c);
                else
                    return ob1.invalid();
            }
            // Promotion
            else if(u_r - s_r == 1 && u_r == 7)
            {
                int ele;
                cout << "WHICH ONE YOU HAVE TO SELECT : \n1.QUEEN\n2.BISHOP\n3.ROOK\n4.KNIGHT    (ENTER NUMBER)\n";
                cin >> ele;
                switch (ele)
                {
                    case 1:
                        ob1.board[u_r][u_c] = 'q';
                        break;
                    case 2:
                        ob1.board[u_r][u_c] = 'b';
                        break;
                    case 3:
                        ob1.board[u_r][u_c] = 'r';
                        break;
                    case 4:
                        ob1.board[u_r][u_c] = 'n';
                        break;
                    default:
                        cout << "SELECT VALID OPTION.\n";
                        return false;
                }
                ob1.board[s_r][s_c] = '.';
                return true;
            }
            else
                return ob1.invalid();
        }
    }
};


class rock : public  virtual chess
{
    public :
    bool Rock(chess & ob1,int s_r,int s_c,int u_r,int u_c,int wb)  
    {
    if(wb==1)                  //white
        {
            if(!ob1.valid_white(s_r,s_c,u_r,u_c))
                return ob1.invalid();
            else if((s_r==u_r || u_c==s_c) && isBlock_r(ob1,s_r,s_c,u_r,u_c))
                return ob1.move_ele(s_r,s_c,u_r,u_c);
            else
                return ob1.invalid();
        }
        else
        {
            if(!ob1.valid_black(s_r,s_c,u_r,u_c))
                return ob1.invalid();
            else if((s_r==u_r || u_c==s_c ) && isBlock_r(ob1,s_r,s_c,u_r,u_c))
                return ob1.move_ele(s_r,s_c,u_r,u_c);
            else
                return ob1.invalid();
        }
    }
    bool isBlock_r(chess &ob1,int s_r,int s_c,int u_r,int u_c)     //done
    {
        int dir_r=u_r-s_r;
        int dir_c=u_c-s_c;
        int count=0;
        if(dir_r==0 && dir_c>0)                   //u_r-s_r==0 u_c>s_c//COLUMN RIGHT
        {
            for(int i=1;i<dir_c;i++)
            {
                if(ob1.board[s_r][s_c+i]=='.')
                {
                    count++;
                }
            }
            if(count==dir_c-1)
            {
                //cout<<"IS BLOCK COUNT==STEP\n";
                return true;
            }
            else
            {
                    cout<<"PATH IS BLOCKED.1\n";
                return false;
            }
        }
        if(dir_r==0 && dir_c<0)                   //u_r-s_r==0 u_c>s_c//COLUMN LEFT
        {
            for(int i=1;i<((-1)*dir_c);i++)
            {
                if(ob1.board[s_r][s_c-i]=='.')
                {
                    //cout<<"anannana";
                    count++;
                }
            }
            if(count==(-1)*dir_c-1)
            {
                //cout<<"IS BLOCK COUNT==STEP\n";
                return true;
            }
            else
            {
                cout<<"PATH IS BLOCKED.2\n";
                return false;
            }
        }
        if(dir_r<0 && dir_c==0)                   //u_r-s_r==0 u_c>s_c//ROW UP
        {
            for(int i=1;i<((-1)*dir_r);i++)
            {
                if(ob1.board[s_r-i][s_c]=='.')
                {
                    count++;
                }
            }
            if(count==(-1)*dir_r-1)
            {
                //cout<<"IS BLOCK COUNT==STEP\n";
                return true;
            }
            else
            {
                    cout<<"PATH IS BLOCKED.3\n";
                return false;
            }
        }
        if(dir_r>0 && dir_c==0)                   //u_r-s_r==0 u_c>s_c//ROW DOWN
        {
            for(int i=1;i<dir_r;i++)
            {
                if(ob1.board[s_r+i][s_c]=='.')
                {
                    count++;
                }
            }
            if(count==dir_r-1)
            {
                //cout<<"IS BLOCK COUNT==STEP\n";
                return true;
            }
            else
            {
                    cout<<"PATH IS BLOCKED.4\n";
                return false;
            }
        }
        return 0;
    }
};


class knight : public virtual chess
{
public :
bool Knight(chess & ob1,int s_r,int s_c,int u_r,int u_c,int wb)    
    {
        if(wb==1)
        {
            if(!ob1.valid_white(s_r,s_c,u_r,u_c))
                return ob1.invalid();
            else if((s_r-u_r==-2 || s_r-u_r==2) && (s_c-u_c==1 || s_c-u_c==-1))
                return ob1.move_ele(s_r,s_c,u_r,u_c);
            else if((s_r-u_r==-1 || s_r-u_r==1) && (s_c-u_c==2 || s_c-u_c==-2))
                return ob1.move_ele(s_r,s_c,u_r,u_c);
            else
                return ob1.invalid();
        }
        else
        {
            if(!ob1.valid_black(s_r,s_c,u_r,u_c))
                return ob1.invalid();
            else if((s_r-u_r==-2 || s_r-u_r==2) && (s_c-u_c==1 || s_c-u_c==-1))
                return ob1.move_ele(s_r,s_c,u_r,u_c);
            else if((s_r-u_r==-1 || s_r-u_r==1) && (s_c-u_c==2 || s_c-u_c==-2))
                return ob1.move_ele(s_r,s_c,u_r,u_c);
            else
                return ob1.invalid();
        }
    }
};


class bishop : public virtual chess
{
    public :
    bool Bishop(chess & ob1,int s_r,int s_c,int u_r,int u_c,int wb)
    {
        int dir_r=u_c-s_c;
        int dir_c=u_r-s_r;
        if(wb==1)
        {
            if(!ob1.valid_white(s_r,s_c,u_r,u_c))
                return ob1.invalid();
            else if(dir_r==dir_c)   //left up & right down
            {  
                if((dir_r>0)    && isBlock_b(ob1,s_r, s_c, u_r, u_c)    )              //right down
                    return ob1.move_ele(s_r,s_c,u_r,u_c);
                else if((dir_r<0) && isBlock_b(ob1,s_r, s_c, u_r, u_c)    )           //left up
                    return ob1.move_ele(s_r,s_c,u_r,u_c);
                else
                    return ob1.invalid();
            }
            else if(dir_r==(-1)*dir_c)
            {
                if((dir_r>0) && isBlock_b(ob1,s_r, s_c, u_r, u_c)    )              //left down
                    return ob1.move_ele(s_r,s_c,u_r,u_c);
                else if((dir_r<0) && isBlock_b(ob1,s_r, s_c, u_r, u_c)    )           //right up
                    return ob1.move_ele(s_r,s_c,u_r,u_c);
                else
                    return ob1.invalid();
            }
            else
                return ob1.invalid();
        }
        else
        {
            if(!ob1.valid_black(s_r,s_c,u_r,u_c))
                return ob1.invalid();
            else if(dir_r==dir_c)   //left up & right down
            {
                if((dir_r>0) && isBlock_b(ob1,s_r, s_c, u_r, u_c)    )              //right down
                    return ob1.move_ele(s_r,s_c,u_r,u_c);
                else if((dir_r<0) && isBlock_b(ob1,s_r, s_c, u_r, u_c)    )           //left up
                    return ob1.move_ele(s_r,s_c,u_r,u_c);
                else
                    return ob1.invalid();
            }
            else if(dir_r==(-1)*dir_c)
            {
                if((dir_r>0) && isBlock_b(ob1,s_r, s_c, u_r, u_c)    )              //left down
                    return ob1.move_ele(s_r,s_c,u_r,u_c);
                else if((dir_r<0) && isBlock_b(ob1,s_r, s_c, u_r, u_c)    )           //right up
                    return ob1.move_ele(s_r,s_c,u_r,u_c);
                else
                    return ob1.invalid();
            }
            else
                return ob1.invalid();
        }
    }
    bool isBlock_b(chess &ob1,int s_r,int s_c,int u_r,int u_c)
    {
        int dir_r=u_r-s_r;
        int dir_c=u_c-s_c;
        int step=dir_c;
        int count=0;
        if(dir_r>0 && dir_c>0)                                   //right down
        {
            for(int i=1;i<step;i++)
            {
                if(ob1.board[s_r+i][s_c+i]=='.')
                {
                    count++;
                }
            }
            if(count==step-1)
            {
                //cout<<"IS BLOCK COUNT==STEP\n";
                return true;
            }
            else
            {
                    cout<<"PATH IS BLOCKED.5\n";
                return false;
            }
        }
        if(dir_r<0 && dir_c<0)                                   //left up
        {
            step=(-1)*step;
            for(int i=1;i<step;i++)
            {
                if(ob1.board[s_r-i][s_c-i]=='.')
                {
                    //cout<<"left up\n";
                    count++;
                }
            }
            if(count==step-1)
            {
                //cout<<"IS BLOCK COUNT==STEP   left up\n";
                return true;
            }
            else
            {
                    cout<<"PATH IS BLOCKED.6\n";
                return false;
            }
        }
        if(dir_r>0 && dir_c<0)                                   //left down
        {
        step*=(-1);
            for(int i=1;i<step;i++)
            {
                step=dir_r;
                if(ob1.board[s_r+i][s_c-i]=='.')
                {
                    count++;
                }
            }
            if(count==step-1)
            {
                //cout<<"IS BLOCK COUNT==STEP\n";
                return true;
            }
            else
            {
                cout<<"PATH IS BLOCKED.7\n";
                return false;
            }
        }
        if(dir_r<0 && dir_c>0)                                   //right up
        {
            for(int i=1;i<step;i++)
            {
                if(ob1.board[s_r-i][s_c+i]=='.')
                {
                    count++;
                }
            }
            if(count==step-1)
            {
                //cout<<"IS BLOCK COUNT==STEP\n";
                return true;
            }
            else
            {
                    cout<<"PATH IS BLOCKED.8\n";
                return false;
            }
        }
        return 0;
    }
};


class queen : public  virtual chess,public virtual rock,public virtual bishop
{
    public :
    bool Queen(chess & ob1,int s_r,int s_c,int u_r,int u_c,int wb)  
    {
        bool flag;
        if(s_r==u_r || u_c==s_c)
            flag=Rock(ob1,s_r,s_c,u_r,u_c,wb);
        else
            flag=Bishop(ob1,s_r,s_c,u_r,u_c,wb);
        return flag;
    }
};


class king : public virtual chess
{
    public :
    bool King(chess &ob1,int s_r,int s_c,int u_r,int u_c,int wb)
    {
        if(wb==1)
        {
            if(s_r==7 && (s_r==u_r) && (u_c-s_c==2) && ob1.board[s_r][s_c+1]=='.' && ob1.board[s_r][s_c+2]=='.' && ob1.board[s_r][s_c+3]=='.' && ob1.board[s_r][s_c+4]=='R')
            {
                ob1.board[s_r][s_c+2]='K';
                ob1.board[s_r][s_c+1]='R';
                ob1.board[s_r][s_c]='.';
                ob1.board[u_r][s_c+3]='.';
                ob1.board[u_r][s_c+4]='.';
                return true;
            }
            else if(s_r==7 && (s_r==u_r) && (u_c-s_c==-2) && ob1.board[s_r][s_c-1]=='.' && ob1.board[s_r][s_c-2]=='.' && ob1.board[s_r][s_c-3]=='R')
            {
                ob1.board[s_r][s_c-2]='K';
                ob1.board[s_r][s_c-1]='R';
                ob1.board[s_r][s_c]='.';
                ob1.board[u_r][s_c-3]='.';
                return true;
            }
            else if(!ob1.valid_white(s_r,s_c,u_r,u_c))
                return ob1.invalid();
            else if(s_r-u_r>1 || s_c-u_c>1 || u_r-s_r>1 || u_c-s_c>1)
                return ob1.invalid();
            //pawn  //left and right up not valid                      
            else if(ob1.board[u_r-1][u_c-1]=='x')//left up (regard king)
                return ob1.invalid();
                //cout<<"pawn left up\n";
            else if(ob1.board[u_r-1][u_c+1]=='x')//right up (regard king)
                return ob1.invalid();
                //cout<<"pawn right up\n";
            else if(checkmate())//(ob1,u_r,u_c))
                return ob1.invalid();
            else if(valid_king(ob1,u_r,u_c))
                return move_ele(s_r,s_c,u_r,u_c);
            else
                return ob1.invalid();
        }
        else
        {
            if(s_r==0 && (s_r==u_r) && (u_c-s_c==2) && ob1.board[s_r][s_c+1]=='.' && ob1.board[s_r][s_c+2]=='.' && ob1.board[s_r][s_c+3]=='.' && ob1.board[s_r][s_c+4]=='r')
            {
                ob1.board[s_r][s_c+2]='k';
                ob1.board[s_r][s_c+1]='r';
                ob1.board[s_r][s_c]='.';
                ob1.board[u_r][s_c+3]='.';
                ob1.board[s_r][s_c+4]='.';
                return true;
            }
            if(s_r==0 && (s_r==u_r) && (u_c-s_c==-2) && ob1.board[s_r][s_c-1]=='.' && ob1.board[s_r][s_c-2]=='.' && ob1.board[s_r][s_c-3]=='r')
            {
                ob1.board[s_r][s_c-2]='k';
                ob1.board[s_r][s_c-1]='r';
                ob1.board[s_r][s_c]='.';
                ob1.board[s_r][s_c-3]='.';
                return true;
            }
            if(!ob1.valid_black(s_r,s_c,u_r,u_c))
                return ob1.invalid();
            else if(s_r-u_r>1 || s_c-u_c>1 || u_r-s_r>1 || u_c-s_c>1)
                return ob1.invalid();
                //pawn  //left and right down not valid                    
            else if(ob1.board[u_r+1][u_c-1]=='P')
                return ob1.invalid();
            else if(ob1.board[u_r+1][u_c+1]=='P')
                return ob1.invalid();
            else if(checkmate())//(ob1,u_r,u_c))
                return ob1.invalid();
            else if(valid_king_black(ob1,u_r,u_c))
                return ob1.move_ele(s_r,s_c,u_r,u_c);
            else
                return ob1.invalid();
        }
        return 0;
    }
    
    bool valid_king(chess &ob1,int u_r,int u_c)
    {
        /*
        column left         dir_r=0      dir_c<0
        column right        dir_r=0      dir_c>0
        row up              dir_c=0      dir_r<0
        row down            dir_c=0      dir_r>0


        (dir_r<0 && dir_c>0)                                   //right up
        dir_r>0 && dir_c<0)                                   //left down
        (dir_r<0 && dir_c<0)                                 //left up
        (dir_r>0 && dir_c>0)                                //right down


        */
        //int dir_r=u_r-s_r;
        //int dir_c=u_c-s_c;
        int flag=0;
        //rock                          
        for(int i=1;i<8;i++)   //cloumn same dir_r>0     //row down
        {
            if(u_r+i>7)
                break;
            else if(ob1.board[u_r+i][u_c]=='r'||ob1.board[u_r+i][u_c]=='q')
            {
                //cout<<"rock row down is wrong\n";
                flag++;
                return false;
            }
            else if(ob1.board[u_r+i][u_c]!='.')
                break;
        }
        for(int i=-1;i>-8;i--)     //cloumn same dir_r<0     //row up    
        {
            if(u_r+i<0)
                break;
            else if(ob1.board[u_r+i][u_c]=='r'||ob1.board[u_r+i][u_c]=='q')
            {
                //cout<<"rock row up is wrong\n";
                flag++;
                return false;
            }
            else if(ob1.board[u_r+i][u_c]!='.')
                break;
        }
        for(int i=1;i<8;i++)     //row same dir_c>0     //column right
        {
            if(u_c+i>7)
                break;
            else if(ob1.board[u_r][u_c+i]=='r'||ob1.board[u_r][u_c+i]=='q')
            {
                //cout<<"rock column right is wrong\n";
                flag++;
                return false;
            }
            else if(ob1.board[u_r][u_c+i]!='.')
                break;
        }
        for(int i=-1;i>-8;i--)     //row same dir_c<0     //column left
        {
            if(u_c+i<0)
                break;
            else if(ob1.board[u_r][u_c+i]=='r'||ob1.board[u_r][u_c+i]=='q')
            {
                //cout<<"rock column left is wrong\n";
                flag++;
                return false;
            }
            else if(ob1.board[u_r][u_c+i]!='.')
                break;
        }




        //knight                        
        int c_r,c_c,c_c2;//check_row          //check_column
        c_c=u_c+1;
        c_c2=u_c-1;
        c_r=u_r+2;
        if(c_r>7 || c_r<0 || c_c>7 || c_c<0);
        else
        {
            if(ob1.board[c_r][c_c]=='n' || ob1.board[c_r][c_c2]=='n')
            {
                flag++;
                return false;
            }// cout<<"Knight is wrong\n";
        }
        c_r=u_r-2;
        if(c_r>7 || c_r<0 || c_c>7 || c_c<0);
        else
        {
            if(ob1.board[c_r][c_c]=='n' || ob1.board[c_r][c_c2]=='n')
            {
                flag++;
                return false;
            }//cout<<"Knight is wrong\n";
        }


        c_c=u_c+2;
        c_c2=u_c-2;
        c_r=u_r+1;
        if(c_r>7 || c_r<0 || c_c>7 || c_c<0);
        else
        {
            if(ob1.board[c_r][c_c]=='n' || ob1.board[c_r][c_c2]=='n')
            {
                flag++;
                return false;
            }//cout<<"Knight is wrong\n";
        }
        c_r=u_r-1;
        if(c_r>7 || c_r<0 || c_c>7 || c_c<0);
        else
        {
            if(ob1.board[c_r][c_c]=='n' || ob1.board[c_r][c_c2]=='n')
            {
                flag++;
                return false;
            }//cout<<"Knight is wrong\n";
        }




        //bishop
        for(int i=1;i<8;i++)   //dir_r>0 && dir_c>0                 right down
        {
            if(u_r+i>7 || u_c+i>7)
                break;
            else if(ob1.board[u_r+i][u_c+i]=='b'||ob1.board[u_r+i][u_c+i]=='q')
            {
                //cout<<"bishop right down is wrong\n";
                flag++;
                return false;
            }
            else if(ob1.board[u_r+i][u_c+i]!='.')
                break;
        }
        for(int i=-1;i>-8;i--)     //dir_r<0 && dir_c<0                 left up  
        {
            if(u_r+i<0 || u_c+i<0)
                break;
            else if(ob1.board[u_r+i][u_c+i]=='b'||ob1.board[u_r+i][u_c+i]=='q')
            {
                //cout<<"bishop left up is wrong\n";
                flag++;
                return false;
            }
            else if(ob1.board[u_r+i][u_c+i]!='.')
                break;
        }
        for(int i=1,j=-1;i<8 && j>-8;i++,j--)     //dir_r>0 && dir_c<0                      left down
        {
            if(u_c+j<0 || u_r+i>7)
                break;
            else if(ob1.board[u_r+i][u_c+j]=='b'||ob1.board[u_r+i][u_c+j]=='q')
            {
                //cout<<"bishop column right is wrong\n";
                flag++;
                return false;
            }
            else if(ob1.board[u_r+i][u_c+j]!='.')
                break;
        }
        for(int i=1,j=-1;i<8 && j>-8;i++,j--)    //dir_r<0 && dir_c>0                     right up
        {
            if(u_c+j<0 || u_r+i>7)
                break;
            else if(ob1.board[u_r+j][u_c+i]=='b'||ob1.board[u_r+j][u_c+i]=='q')
            {
                //cout<<"bishop column left is wrong\n";
                flag++;
                return false;
            }
            else if(ob1.board[u_r+j][u_c+i]!='.')
                break;
        }
        return 0;
    }


    bool valid_king_black(chess &ob1,int u_r,int u_c)
    {
        bool flag;
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                switch (ob1.board[i][j])
                {
                case 'x':
                ob1.board[i][j]='P';
                    break;
                case 'b':
                ob1.board[i][j]='B';
                    break;
                case 'n':
                ob1.board[i][j]='N';
                    break;
                case 'k':
                ob1.board[i][j]='K';
                    break;
                case 'r':
                ob1.board[i][j]='R';
                    break;
                case 'q':
                ob1.board[i][j]='Q';
                    break;
                case 'P':
                ob1.board[i][j]='x';
                    break;
                case 'B':
                ob1.board[i][j]='b';
                    break;
                case 'N':
                ob1.board[i][j]='n';
                    break;
                case 'K':
                ob1.board[i][j]='k';
                    break;
                case 'R':
                ob1.board[i][j]='r';
                    break;
                case 'Q':
                ob1.board[i][j]='q';
                    break;
                }
            }
        }
        flag=valid_king(ob1,u_r,u_c);
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                switch (ob1.board[i][j])
                {
                case 'x':
                ob1.board[i][j]='P';
                    break;
                case 'b':
                ob1.board[i][j]='B';
                    break;
                case 'n':
                ob1.board[i][j]='N';
                    break;
                case 'k':
                ob1.board[i][j]='K';
                    break;
                case 'r':
                ob1.board[i][j]='R';
                    break;
                case 'q':
                ob1.board[i][j]='Q';
                    break;
                case 'P':
                ob1.board[i][j]='x';
                    break;
                case 'B':
                ob1.board[i][j]='b';
                    break;
                case 'N':
                ob1.board[i][j]='n';
                    break;
                case 'K':
                ob1.board[i][j]='k';
                    break;
                case 'R':
                ob1.board[i][j]='r';
                    break;
                case 'Q':
                ob1.board[i][j]='q';
                    break;
                }
            }
        }
        return flag;
    }


    bool checkmate()
    {
        // int flag=0;
        // for(int i=0;i<3;i++)
        // {
        //     for(int j=0;j<3;j++)
        //     {
        //         if(i==1 && j==1)
        //         continue;
        //         if(!valid_king(ob1,u_r+i,u_c+i))
        //         {
        //             flag++;
        //         }
        //     }
        // }
        // if(flag==8)
        // {
        //     cout<<"Checkmate,King is not able to move anywhere.\n";
        //     gameover=1;
        //     return false;
        // }
        // else
        // {
        //     return true;
        // }
        return true;
    }


    bool check(chess &ob1,int s_r,int s_c)
    {
        int flag=0;
        //rock                                
        for(int i=1;i<8;i++)   //cloumn same dir_r>0     //row down
        {
            if(s_r+i>7)
                break;
            else if(ob1.board[s_r+i][s_c]=='r'||ob1.board[s_r+i][s_c]=='q')
            {
                cout<<"rock's check\n";
                flag++;
                return false;
            }
            else if(ob1.board[s_r+i][s_c]!='.')
                break;
        }
        for(int i=-1;i>-8;i--)     //cloumn same dir_r<0     //row up    
        {
            if(s_r+i<0)
                break;
            else if(ob1.board[s_r+i][s_c]=='r'||ob1.board[s_r+i][s_c]=='q')
            {
                cout<<"rock's check\n";
                flag++;
                return false;
            }
            else if(ob1.board[s_r+i][s_c]!='.')
                break;
        }
        for(int i=1;i<8;i++)     //row same dir_c>0     //column right
        {
            if(s_c+i>7)
                break;
            else if(ob1.board[s_r][s_c+i]=='r'||ob1.board[s_r][s_c+i]=='q')
            {
                cout<<"rock's check\n";
                flag++;
                return false;
            }
            else if(ob1.board[s_r][s_c+i]!='.')
                break;
        }
        for(int i=-1;i>-8;i--)     //row same dir_c<0     //column left
        {
            if(s_c+i<0)
                break;
            else if(ob1.board[s_r][s_c+i]=='r'||ob1.board[s_r][s_c+i]=='q')
            {
                cout<<"rock's check\n";
                flag++;
                return false;
            }
            else if(ob1.board[s_r][s_c+i]!='.')
                break;
        }




        //knight                      
        int c_r,c_c,c_c2;//check_row          //check_column
        c_c=s_c+1;
        c_c2=s_c-1;
        c_r=s_r+2;
        if(c_r>7 || c_r<0 || c_c>7 || c_c<0);
        else
        {
            if(ob1.board[c_r][c_c]=='n' || ob1.board[c_r][c_c2]=='n')
            {
                flag++;
                return false;
            }// cout<<"Knight is wrong\n";
        }
        c_r=s_r-2;
        if(c_r>7 || c_r<0 || c_c>7 || c_c<0);
        else
        {
            if(ob1.board[c_r][c_c]=='n' || ob1.board[c_r][c_c2]=='n')
            {
                flag++;
                return false;
            }//cout<<"Knight is wrong\n";
        }


        c_c=s_c+2;
        c_c2=s_c-2;
        c_r=s_r+1;
        if(c_r>7 || c_r<0 || c_c>7 || c_c<0);
        else
        {
            if(ob1.board[c_r][c_c]=='n' || ob1.board[c_r][c_c2]=='n')
            {
                flag++;
                return false;
            }//cout<<"Knight is wrong\n";
        }
        c_r=s_r-1;
        if(c_r>7 || c_r<0 || c_c>7 || c_c<0);
        else
        {
            if(ob1.board[c_r][c_c]=='n' || ob1.board[c_r][c_c2]=='n')
            {
                flag++;
                return false;
            }//cout<<"Knight is wrong\n";
        }




        //bishop
        for(int i=1;i<8;i++)   //dir_r>0 && dir_c>0                 right down
        {
            if(s_r+i>7 || s_c+i>7)
                break;
            else if(ob1.board[s_r+i][s_c+i]=='b'||ob1.board[s_r+i][s_c+i]=='q')
            {
                cout<<"bishop's check\n";
                flag++;
                return false;
            }
            else if(ob1.board[s_r+i][s_c+i]!='.')
                break;
        }
        for(int i=-1;i>-8;i--)     //dir_r<0 && dir_c<0                 left up  
        {
            if(s_r+i<0 || s_c+i<0)
                break;
            else if(ob1.board[s_r+i][s_c+i]=='b'||ob1.board[s_r+i][s_c+i]=='q')
            {
                cout<<"bishop's check\n";
                flag++;
                return false;
            }
            else if(ob1.board[s_r+i][s_c+i]!='.')
                break;
        }
        for(int i=1,j=-1;i<8 && j>-8;i++,j--)     //dir_r>0 && dir_c<0                      left down
        {
            if(s_c+j<0 || s_r+i>7)
                break;
            else if(ob1.board[s_r+i][s_c+j]=='b'||ob1.board[s_r+i][s_c+j]=='q')
            {
                cout<<"bishop's check\n";
                flag++;
                return false;
            }
            else if(ob1.board[s_r+i][s_c+j]!='.')
                break;
        }
        for(int i=1,j=-1;i<8 && j>-8;i++,j--)    //dir_r<0 && dir_c>0                     right up
        {
            if(s_c+j<0 || s_r+i>7)
                break;
            else if(ob1.board[s_r+j][s_c+i]=='b'||ob1.board[s_r+j][s_c+i]=='q')
            {
                cout<<"bishop's check\n";
                flag++;
                return false;
            }
            else if(ob1.board[s_r+j][s_c+i]!='.')
                break;
        }
    }
};


bool chess:: move(int s_r,int s_c,int u_r,int u_c,int wb)
{
    bool flag;
    switch (board[s_r][s_c])
    {
        case 'x':
        case 'P':
        {  
            pawn p_ob;
            flag=p_ob.Pawn(*this,s_r,s_c,u_r,u_c,wb);
            break;
        }
        case 'r':
        case 'R':
        {
            rock r_ob;
            flag = r_ob.Rock(*this,s_r,s_c,u_r,u_c,wb);
            break;
        }
        case 'n':
        case 'N':
        {
            knight n_ob;
            flag=n_ob.Knight(*this,s_r,s_c,u_r,u_c,wb);
            break;
        }
        case 'b':
        case 'B':
        {
            bishop b_ob;
            flag = b_ob.Bishop(*this,s_r,s_c,u_r,u_c,wb);
            break;
        }
        case 'k':
        case 'K':
        {
            king k_ob;
            flag = k_ob.King(*this,s_r,s_c,u_r,u_c,wb);
            break;
        }
        case 'q':
        case 'Q':
        {
            queen q_ob;
            flag = q_ob.Queen(*this,s_r,s_c,u_r,u_c,wb);
            break;
        }
        default:
        {
            cout<<"INVALID MOVE.\nPLEASE SELECT VALID ELEMENT.\n";
            flag =false;
            break;
        }
    }
    return flag;
};


int main()
{
    int s_r,u_r,s_c,u_c; //select_colume //update_row
    char s_c1,u_c1;
    chess c1;
    bool flag=false;      
    cout<<"WHITE'S ELEMENTS : \nx : PAWN\tPOINT : 1\nn : KNIGHT\tPOINT : 3\nb : BISHOP\tPOINT : 3\nR : ROCK\tPOINT : 5\nq : QUEEN\tPOINT : 9\nk : KING\tPOINT : PRICELESS\n\n";
    cout<<"\nBLACK'S ELEMENTS : \nP : PAWN\tPOINT : 1\nN : KNIGHT\tPOINT : 3\nB : BISHOP\tPOINT : 3\nR : ROCK\tPOINT : 5\nQ : QUEEN\tPOINT : 9\nK : KING\tPOINT : PRICELESS\n\n";
    sleep(5);
    while(gameover==0)
    {
        if(gameover==0)
        {
            c1.board_pri();
        
        while(!flag && gameover==0)
        {
            cout<<"\nWHITE'S MOVE";
            cout<<"\nENTER THE PIECE'S POSITION TO MOVE (COL) (ROW) : ";
            cin>>s_c1>>s_r;
            cout<<"WHERE DO YOU WANT TO MOVE? ";
            cin>>u_c1>>u_r;
            s_c=c1.con(s_c1);
            u_c=c1.con(u_c1);
            flag=c1.move(s_r-1,s_c,u_r-1,u_c,-1);
        }
        flag=false;
        if(gameover==0)
            c1.board_pri();
        while(!flag && gameover==0)
        {
            cout<<"\nBLACK'S MOVE";
            cout<<"\nENTER THE PIECE'S POSITION TO MOVE (COL) (ROW) : ";
            cin>>s_c1>>s_r;
            cout<<"WHERE DO YOU WANT TO MOVE? ";
            cin>>u_c1>>u_r;
            s_c=c1.con(s_c1);
            u_c=c1.con(u_c1);
            flag=c1.move(s_r-1,s_c,u_r-1,u_c,1);
        }
        flag=false;
        }
    }
    if(c1.point_w>c1.point_b)
        cout<<"White wins the game\n";
    else if(c1.point_w<c1.point_b)
        cout<<"Black wins the game\n";
    else
    {
        cout<<"It's a draw\n";
    }
        sleep(10);
    return 0;
}
