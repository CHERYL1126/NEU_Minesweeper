#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"fixpw.h"
#include "login.h"
#include"DoAChose.h"
#include"Position.h"
#include"Explain.h"
#include"AsForUs.h"
//#include"cube.h"
#include<QPushButton>
#include<QTime>
#include<QTimer>
#include<QDebug>
#include<QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mylog = new login;
    mylog->show();
    connect(mylog,SIGNAL(loginbegin()),this,SLOT(show()));
    //myfixpw = new fixpw;
    //connect(myfixpw,SIGNAL(fixpwok),this,SLOT(pwclear));
    setWindowTitle("扫雷");

    //初始化界面
    origin();

    //游戏指导

    connect(ui->actionintroduction,&QAction::triggered,[=](){//lambda表达式的[]的作用——把外面的变量传进来[=]值传递只读的方式
        Explain * a = new Explain(this);
        a->setWindowModality(Qt::WindowModal);//Qt::WindowModal 半模态：窗口级模态对话框，阻塞父窗口、父窗口的父窗口及兄弟窗口。
        a->setAttribute(Qt::WA_DeleteOnClose);//关闭窗口
        a->show();
    });

    //关于
    connect(ui->actionasfor,&QAction::triggered,[=](){
        AsForUs * b = new AsForUs(this);
        b->setWindowModality(Qt::WindowModal);
        b->setAttribute(Qt::WA_DeleteOnClose);
        b->show();
    });

    //难度选择

    connect(ui->actionchose,&QAction::triggered,[=](){
        DoAChose * c = new DoAChose(this);
        c->setWindowModality(Qt::WindowModal);
        c->setAttribute(Qt::WA_DeleteOnClose);
        c->show();

    });

    //排行榜
    connect(ui->actionpos,&QAction::triggered,[=](){
        Position * d = new Position(this);
        d->setWindowModality(Qt::WindowModal);
        d->setAttribute(Qt::WA_DeleteOnClose);
        d->show();
    });

    //点击笑脸按钮初始化

    connect(ui->emoButton,&QPushButton::clicked,[=](){
    origin();
    });

    //按下的时候出现棒表情
    connect(ui->emoButton,&QPushButton::pressed,[=](){
    ui->emoButton->setIcon(QIcon(":/p/bang.png"));
    });

    //松开的时候恢复悠闲表情
    connect(ui->emoButton,&QPushButton::released,[=](){
    ui->emoButton->setIcon(QIcon(":/p/youxian.png"));
    });


    //设置LCD显示器的参数
    //左边时间显示
    ui->lcdNumber_1->setDigitCount(3);//设置可显示的数字个数
    ui->lcdNumber_1->setStyleSheet("border: 1px solid green; color: red; background: black;");//设置样式
    //右边雷数显示
    ui->lcdNumber_2->setDigitCount(3);//设置可显示的数字个数
    ui->lcdNumber_2->setStyleSheet("border: 1px solid green; color: yellow; background: black;");//设置样式
    ui->lcdNumber_2->display(mineCount);//设置显示的具体数字

    //创建计时器对象，计时
    timer = new QTimer(this);//定义计时器
    timer->start(1000);//计时开始，单位毫秒



}

//析构函数
MainWindow::~MainWindow()
{
    delete ui;
}
//空地（0~9）
//雷区（-1）
//已打开区域（-2）
//插旗区域
//初始化

void MainWindow::origin()
{
    ui->emoButton->setIcon(QIcon(":/p/youxian.png"));//初始化表情
    originMine();//初始化雷
    second=0;//初始化时间
    isTimeRun = true;//开始计时
    mineCount = mine;//初始化雷数
    setFixedSize(40+20*height,100+20*width);//根据参数设置窗口大小


    //因为之前把每一个按钮都在堆上开辟了空间，所以在重新初始化的时候，必须清理掉这些空间
    if(map.size() != 0)
    {
        for(int i=0; i<map.size(); i++)
        {
            for(int j=0; j<map[0].size(); j++)
            {
                if(map[i][j] != nullptr) delete map[i][j];
            }
        }
    }
    map.clear();//将map里的指针清空

    //根据参数，设置好雷区的尺寸，并在每个格子里设置好按钮
    for(int i = 0; i<height; i++)
    {
        QVector<mouseaction *> t;
    for(int j=0; j<width; j++)
        {
            mouseaction * temp = new mouseaction(this);
            temp->resize(20,20);
            temp->move(20+20*i,80+20*j);
            temp->setStyleSheet("background-image: url(:/p/cao.png);");
            t.push_back(temp);
//函数将一个新的元素加到vector的最后面，位置为当前最后一个元素的下一个元素
//push_back() 在Vector最后添加一个元素（参数为要插入的值）
        }
        map.push_back(t);
    }
    myaction();
}

void MainWindow::myaction()
{
    //显示这个按钮，并建立每个按钮的连接，部分使用了mouseaction作用域的信号为重载过的
     int t=1;

    for(int i = 0; i<map.size(); i++)
    {
        qDebug()<<"建立行数i:"<<i;
        for(int j=0; j<map[0].size(); j++)
        {
            map[i][j]->show();//显示按钮
            if(t==1)
            {
                if(mineTable[i+1][j+1]==0)
                {
                    int count = 100          ;//count为搜索的次数
                    mineDfs(i,j,count)      ;//点到0会扩散的深度优先搜索函数
                    t=0;
                }
            }

            //建立按钮与左右键同时按下时的联系
            connect(map[i][j],&mouseaction::pressRandL,[=]()
            {
              qDebug()<<"BBB同时按下";
                if(mineTable[i+1][j+1] == -2)
                {
                    //如果被打开，则遍历周边8个格子
                    for(int x= i-1; x<i+2; ++x)
                    {
                        for(int y = j-1; y<j+2; ++y)
                        {
                            if(0<=x && x< height && 0<y && y<width)
                            {
                                if(mineTable[x+1][y+1] > -2 && mineTable[x+1][y+1] < 9 )
                                {
                                    map[x][y]->setIcon(QIcon(":/p/tu.png"));
                                }
                            }
                        }
                    }
                }
                judge(true);//判断游戏是否结束
            });

            //建立左右键同时抬起与按钮的联系
            connect(map[i][j],&mouseaction::ReleaseRandL,[=]()
            {
                ui->emoButton->setIcon(QIcon(":/p/youxian.png"));
                qDebug()<<"AAA同时抬起";

                int flagCount = 0;//旗子数
                int MineCount = 0;//雷数
                int quesCount = 0;//问号数

                /*
                第一次遍历记录下周边的错误旗子数、雷数、问号数
                做判定：
                1：同时存在雷数和错误旗子，游戏结束，雷曝光
                2：存在雷或者存在问号或者存在错误旗子数，不操作
                3：如果都不存在，全部打开，设置为已读-2状态
                */


                //遍历周边8个格子
                for(int x= i-1; x<i+2; ++x)
                {
                    for(int y = j-1; y<j+2; ++y)
                    {
                        if(0<=x && x< height && 0<y && y<width)
                        {
                            //第一次遍历记录下周边的错误旗子数、雷数、问号数
                            //做判定：

                            if(mineTable[x+1][y+1] == -1 )
                            {
                                ++flagCount;
                            }
                            if( mineTable[x+1][y+1] == -10)
                            {
                                ++quesCount;
                            }
                            if( mineTable[x+1][y+1] >= 99)
                            {
                                ++MineCount;
                            }
                            if(mineTable[x+1][y+1] > -2 && mineTable[x+1][y+1] < 9)
                            {
                                map[x][y]->setIcon(QIcon(""));
                            }
                        }
                    }
                }

                //做判定：
                //1：同时存在雷数和错误旗子，游戏结束，雷曝光
                //2：存在雷或者存在问号或者存在错误旗子数，不操作
                //3：如果都不存在，全部打开，设置为已读-2状态
                if(flagCount != 0 && MineCount != 0)
                {
                    judge(false);
                }
                else if(flagCount == 0 && MineCount == 0 && quesCount ==0)
                {
                    for(int x= i-1; x<i+2; ++x)
                    {
                        for(int y = j-1; y<j+2; ++y)
                        {
                            if(0<=x && x< height && 0<y && y<width)
                            {
                                if(mineTable[x+1][y+1] > -2 && mineTable[x+1][y+1] < 9)
                                {
                                    int count = 100          ;//count为搜索的次数
                                    mineDfs(x,y,count)      ;//点到0会扩散的深度优先搜索函数
                                }
                            }
                        }
                    }
                }
                judge(true);
            });

            //建立鼠标左键与按钮的联系

            //按下左键，大表情切换为嘤！
            connect(map[i][j],&mouseaction::pressleft,[=]()
            {
                ui->emoButton->setIcon(QIcon(":/p/ying.png"));
            });

            //松开左键，大表情切换回来，并且翻开格子，并且第一次按下还会触发计时
        connect(map[i][j],&mouseaction::releaseleft,[=](){

        ui->emoButton->setIcon(QIcon(":/p/youxian.png"));

        //初始化中将isTimeRun设置为true，则表情还未计时，此时计时，并将isTimeRun设置为false;
        if(isTimeRun)
        {
                    connect(timer,&QTimer::timeout,[=](){
            second++;
            qDebug()<<second;
            ui->lcdNumber_1->display(second);
            ui->lcdNumber_2->display(mineCount);
                    });
            isTimeRun = false;
                }

                //踩到雷
                if(mineTable[i+1][j+1] == -1){
            map[i][j]->setIcon(QIcon(":/p/lei.png"));
            judge(false);
                }

                //踩到空地，既没有雷也没有旗子问号
                else if(mineTable[i+1][j+1] >= 0 && mineTable[i+1][j+1] < 9){
                    int count = 100;
                    mineDfs(i,j,count);
                }

                //判断游戏结束
        judge(true);

            });

            //建立鼠标右键与按钮的联系
            //这里需要知道我们使用右键需要标记两个状态，棋子和问号，因此我们在插入棋子的时候将雷表中的值*100，问号*10
            //这样我们就可以在遍历的时候判定，如果有值小于等于-100的话，游戏失败
        connect(map[i][j],&mouseaction::pressright,[=](){

                //第一次点击右键也会计时
        if(isTimeRun)
        {
                    connect(timer,&QTimer::timeout,[=](){
            second++;
            qDebug()<<second;
            ui->lcdNumber_1->display(second);
                    });
            isTimeRun = false;
                }


                //无状态
        if(mineTable[i+1][j+1] > -2 && mineTable[i+1][j+1] < 9)
         {
            mineCount--;
                    ui->lcdNumber_2->display(mineCount);
            map[i][j]->setIcon(QIcon(":/p/qizi.png"));
                    if(mineTable[i+1][j+1] == 0) mineTable[i+1][j+1] = 99;
                    else mineTable[i+1][j+1] *= 100;
          }
        //旗子态//标记在雷区为-100，标记错误为100~800
        else if(mineTable[i+1][j+1] == -100 || mineTable[i+1][j+1] > 90)
        {
            mineCount++;
                    ui->lcdNumber_2->display(mineCount);
            map[i][j]->setIcon(QIcon(":/p/wenhao.png"));
                    if(mineTable[i+1][j+1] == 99) mineTable[i+1][j+1] = 9;
                    else mineTable[i+1][j+1] /= 10;
                }
        //问号态//标记在雷区为-10，标记错误为10~80
                else if(mineTable[i+1][j+1] == -10 || mineTable[i+1][j+1] >= 9){
                    map[i][j]->setIcon(QIcon(""));
                    if(mineTable[i+1][j+1] == 9) mineTable[i+1][j+1] = 0;
                    else mineTable[i+1][j+1] /= 10;
                }
            });


        }
    }

}

//实现0号区域的递归翻开
void MainWindow::mineDfs(int i, int j, int count)
{
    if(i<0 || j<0 || i>=height || j>=width || mineTable[i+1][j+1] == -2 || count == 0 || (mineTable[i+1][j+1] >= 99) || (mineTable[i+1][j+1] >= 9)) return;
    if(mineTable[i+1][j+1] != 0)
    {
        QString temp = QString::number(mineTable[i+1][j+1]);
        map[i][j]->setText(temp);

    remainder--;
    map[i][j]->setStyleSheet("background-image: url(:/p/tu.png);");
        mineTable[i+1][j+1] = -2;
    }
    else
    {
    count--;

        map[i][j]->setText("0");

    remainder--;
    map[i][j]->setStyleSheet("background-image: url(:/p/tu.png);");
        mineTable[i+1][j+1] = -2;
    for (int x = i - 1; x <= i + 1; x++)
    {
        for (int y = j - 1; y <= j + 1; y++)
        {
        if (!(i == x && j == y))
        {
            mineDfs(x,y,count);

                }
            }
        }

    }
}

//游戏结束判定
void MainWindow::judge(bool isWin)
{

    if(isWin)
    {
    if(this->remainder == 0)
    {
        timer->disconnect();//断开所有联系
        this->turn();//翻开雷区所有的雷
        ui->emoButton->setIcon(QIcon(":/p/haha.png"));
        QMessageBox::information(this,"提示","助力世界的爱与和平\n恭喜您完成维和任务\n点击Ok重新开始游戏！",QMessageBox::Ok);
//        QMessageBox box;
//        box.setWindowTitle("提示");
//        box.setText("游戏胜利，恭喜你成功了！\n点击Ok重新开始游戏！");
//        box.setIconPixmap(QPixmap(":/p/peace.png"));
//        box.exec();
        }
    }
    else
    {
    this->turn();//照亮雷区所有的雷
    timer->disconnect();//断开所有联系
    ui->emoButton->setIcon(QIcon(":/p/aaa.png"));
    QMessageBox::critical(this,"提示","排雷失败，勇者请重头来过！\n点击Ok重新开始游戏！",QMessageBox::Ok);
//    QMessageBox box;
//    box.setWindowTitle("提示");
//    box.setText("游戏失败，很遗憾，请在来一局吧！\n点击Ok重新开始游戏！");
//    box.setIconPixmap(QPixmap(":/p/pia.png"));
//    box.exec();
    }

}


//翻开雷区所有的雷
void MainWindow::turn()
{
    for(int i= 0; i<height; i++)
    {
    for(int j =0; j<width; j++)
    {
            map[i][j]->disconnect();

        if(mineTable[i+1][j+1] == -1)//显示雷区
        {
        map[i][j]->setIcon(QIcon(":/p/lei.png"));

            }
        else if(mineTable[i+1][j+1] > 90)//插旗错误显示
        {
        map[i][j]->setIcon(QIcon(":/p/cha.png"));
            }
        }
    }
}

//在设定雷表的时候，建议把雷表的尺寸在map的尺寸上加2，这样便于统计每个格子上周围的雷数，而不用再加很多条件判断
void MainWindow::originMine()
{
    remainder= height*width - mine;
    mineTable.clear();
    int h = height+2;
    int w = width +2;
    int m = mine;
    //初始化雷表
    for(int i = 0; i<h; i++)
    {
        QVector<int> temp;
    for(int j = 0; j<w; j++)
    {
            temp.push_back(0);
        }
        mineTable.push_back(temp);
    }
    //设置雷的位置
    qsrand(time(NULL));
    int n = qrand();
    while(m!=0)
    {
        int rand_h = 1+rand()%height;
    int rand_w = 1+rand()%width;
    if(mineTable[rand_h][rand_w] == 0)
    {
            mineTable[rand_h][rand_w] = -1;
        m--;
        }
    }
    //设定没有的格子上的数字
    for(int i = 1; i<h-1; ++i)
    {
    for(int j = 1; j<w-1; ++j)
    {
        if(mineTable[i][j] == 0)
        {
        mineTable[i][j] = numberAcount(i,j);
       //map[i][j]->setStyleSheet("color:white");
            }
        }
    }

}

//计算中心格子周围的雷数
int MainWindow::numberAcount(int i, int j)
{
    int acount = 0;
    for (int x = i - 1; x <= i + 1; ++x)
    {
    for (int y = j - 1; y <= j + 1; ++y)
    {
        if (mineTable[x][y] == -1)
        {
        acount++;
            }
        }
    }
    return acount;
}

//提供给用户自定义的函数
void MainWindow::setHeight(int h)
{
    height = h;
}

void MainWindow::setWidth(int w)
{
    width = w;
}

void MainWindow::setMineNumber(int m)
{
    mine = m;
}



