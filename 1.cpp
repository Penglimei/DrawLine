


#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <graphics.h>

void line1(){
    line(100, 100, 200, 400);
    line(100, 400, 200, 100);
    line(10, 200, 300, 300);
    line(10, 300, 300, 200);
}

void lineDDA(int x0, int y0, int x1, int y1, int color){
    int x;
    float dy, dx, y, m;
    dx = x1 - x0;
    dy = y1 - y0;
    m = dy / dx;
    y = y0;
    for (x = x0; x <= x1; x++){
		//在指定位置画一像素putpixel (int x, int y, int pixelcolor);
        //其中(x,y)是坐标，pixelcolor是象素的颜色
        putpixel(x, (int)(y + 0.5), color);
        y += m;
    }
}


void lineMidPoint(int x0, int y0, int x1, int y1, int color){
    int x = x0, y = y0;
    int a = y0 - y1, b = x1 - x0;
	//b<0时x负增长，所以x每增长一步需要减1，此时考虑的是从右下往左上画线时出现的问题
    int cx = (b >= 0 ? 1 : (b = -b, -1));
	//a>0时y负增长，x每增长一步，y可能减1或原地不动，此时考虑的是从左上往右下画线时出现的问题
    int cy = (a <= 0 ? 1 : (a = -a, -1));

    putpixel(x, y, color);

    int d, d1, d2;
    if (-a <= b)     // 只考虑了0<=|k|<=1  
    {
        d = 2 * a + b;
        d1 = 2 * a;
        d2 = 2 * (a + b);
        while (x != x1)
        {
            if (d < 0)
                y += cy, d += d2;
            else
                d += d1;
            x += cx;
            putpixel(x, y, color);
        }
    }
}


//需要特别注意的是：
//输出界面中，左上角为原点(0,0)，以水平往右方向为x轴正方向，以垂直往下方向为y轴正方向。


void lineBresenham1(int x0, int y0, int x1, int y1, long color)
{
	int x = x0;
    int y = y0;
    int stepX = 1;
    int stepY = 1;
	int dx = x1-x0;
	int dy = y1-y0;
	int e = -dx;
	//只考虑了0<=|k|<=1
	//从左往右画
	for(x;x<=x1;x++)
	{
		putpixel(x, y, color);
		
		e -= 2*dy;
		//printf("%d ",e);
		if(e>0)
		{
			y -= stepY;
			e -= 2*dx;
		}
		else
		{
			y = y;
		}
	}
	//从右往左画
	for(x;x>=x1;x--)
	{
		putpixel(x, y, color);
		
		e -= 2*dy;
		//printf("%d ",e);
		if(e>0)
		{
			y -= stepY;
			e += 2*dx;
		}
		else
		{
			y = y;
		}
	}
}


void showWord(int code){
	 outtextxy(200, 30, "单击右键退出");
    switch (code){
    case 1://原画
        outtextxy(200, 10, "easyX系统画线算法");
        break;
    case 2://DDA算法
        outtextxy(200, 10, "DDA算法");
        break;
    case 3://中点画线算法
        outtextxy(200, 10, "中点画线算法");
        break;
    case 4://Bresenham算法
        outtextxy(200, 10, "Bresenham算法");
        break;
    default:
        line1();
        break;
    }
    
}



void drawLine(int x0,int y0,int x1,int y1,int code){
    showWord(code);
    switch (code){
    case 1://原画
        line(x0,y0,x1,y1);
        break;
    case 2://DDA算法
        lineDDA(x0, y0, x1, y1,WHITE);
        break;
    case 3://中点画线算法
        lineMidPoint(x0, y0, x1, y1, WHITE);
        break;
    case 4://Bresenham算法
        lineBresenham1(x0, y0, x1, y1, WHITE);
        break;
    default:
        line1();
        break;
    }
}


void showWORDXY(int x, int y, int showX, int showY,int flag){
	char dintX[5] = { 0 };
    char dintY[5] = { 0 };
    _itoa(showX, dintX, 10);//把整数showX转成字符串dintX
    _itoa(showY, dintY, 10);//把整数showY转成字符串dintY
    char str1[100] = "第一个点的坐标：（";//此时数组没有定义长度   元素的个数应该为strlen +1  因为字符串末尾有 '\0'结束 
    char str2[100] = "第二个点的坐标：（";
    if (flag == 1){
        // _countof(dintX)能够获取到数组中元素的个数 含‘\0’
        strcat(str1,dintX);
        strcat(str1,",");
        strcat(str1,dintY);
        strcat(str1,")");
        outtextxy(x, y, str1);
    }
    else if (flag == 2){
        strcat(str2,dintX);
        strcat(str2,",");
        strcat(str2,dintY);
        strcat(str2,")");
        outtextxy(x, y, str2);
    }
}


//调用easyX
void easyX(int code){
    initgraph(640, 480);       //初始化
    showWord(code);
    MOUSEMSG m; // 定义鼠标消息
    int n=0;//读取两个点
    int exit = false;
    int x0=0, y0=0,x1=0,y1=0;
    while (n<2 && !exit)
    {
        m = GetMouseMsg();
        switch (m.uMsg)
        {
			//WM_RBUTTONDOWN:接收鼠标右键按下时的信息
        case WM_RBUTTONDOWN:
            outtextxy(200, 300, "再次点击键退出");
            exit = true;
            break;    // 按鼠标右键退出程序
        }
        while (m.uMsg != WM_LBUTTONDOWN){
            m = GetMouseMsg();
            switch (m.uMsg)
            {
            case WM_RBUTTONDOWN:
                outtextxy(200, 300, "再次点击键退出");
                exit = true;
                break;    // 按鼠标右键退出程序
            }

        }
		 
        while (m.uMsg != WM_LBUTTONUP){
            m = GetMouseMsg();

			//cleardevice()清除屏幕和图形缓冲区
            cleardevice();
         showWord(code);
           if (n == 0){
                showWORDXY(200, 430, x0, y0,1);
                x0 = m.x;
                y0 = m.y;
            }
            else{
                showWORDXY(200, 430, x0, y0, 1);
                showWORDXY(200, 450, x1, y1, 2);
                x1 = m.x;
                y1 = m.y;
            }
        }
        n++;
        if (n == 2){
            //画线
            drawLine(x0, y0, x1, y1, code);
            //重置
            n = 0;
        }
    }
    //_getch();                  //等待用户操作
    closegraph();             //关闭图形
}

void main(){
    int n = 1;
    printf("请选择画线算法画线：\n");
    printf("1.easyX系统画线函数.\n");
    printf("2.DDA画线算法函数.\n");
    printf("3.中点画线算法函数.\n");
    printf("4.Bresenham画线算法函数.\n");
    printf("0.退出.\n");
    while (n != 0){
        scanf("%d", &n);
        if (n == 0){
            exit(0);
        }
        easyX(n);
    }
}

