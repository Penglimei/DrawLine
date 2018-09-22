


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
		//��ָ��λ�û�һ����putpixel (int x, int y, int pixelcolor);
        //����(x,y)�����꣬pixelcolor�����ص���ɫ
        putpixel(x, (int)(y + 0.5), color);
        y += m;
    }
}


void lineMidPoint(int x0, int y0, int x1, int y1, int color){
    int x = x0, y = y0;
    int a = y0 - y1, b = x1 - x0;
	//b<0ʱx������������xÿ����һ����Ҫ��1����ʱ���ǵ��Ǵ����������ϻ���ʱ���ֵ�����
    int cx = (b >= 0 ? 1 : (b = -b, -1));
	//a>0ʱy��������xÿ����һ����y���ܼ�1��ԭ�ز�������ʱ���ǵ��Ǵ����������»���ʱ���ֵ�����
    int cy = (a <= 0 ? 1 : (a = -a, -1));

    putpixel(x, y, color);

    int d, d1, d2;
    if (-a <= b)     // ֻ������0<=|k|<=1  
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


//��Ҫ�ر�ע����ǣ�
//��������У����Ͻ�Ϊԭ��(0,0)����ˮƽ���ҷ���Ϊx���������Դ�ֱ���·���Ϊy��������


void lineBresenham1(int x0, int y0, int x1, int y1, long color)
{
	int x = x0;
    int y = y0;
    int stepX = 1;
    int stepY = 1;
	int dx = x1-x0;
	int dy = y1-y0;
	int e = -dx;
	//ֻ������0<=|k|<=1
	//�������һ�
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
	//��������
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
	 outtextxy(200, 30, "�����Ҽ��˳�");
    switch (code){
    case 1://ԭ��
        outtextxy(200, 10, "easyXϵͳ�����㷨");
        break;
    case 2://DDA�㷨
        outtextxy(200, 10, "DDA�㷨");
        break;
    case 3://�е㻭���㷨
        outtextxy(200, 10, "�е㻭���㷨");
        break;
    case 4://Bresenham�㷨
        outtextxy(200, 10, "Bresenham�㷨");
        break;
    default:
        line1();
        break;
    }
    
}



void drawLine(int x0,int y0,int x1,int y1,int code){
    showWord(code);
    switch (code){
    case 1://ԭ��
        line(x0,y0,x1,y1);
        break;
    case 2://DDA�㷨
        lineDDA(x0, y0, x1, y1,WHITE);
        break;
    case 3://�е㻭���㷨
        lineMidPoint(x0, y0, x1, y1, WHITE);
        break;
    case 4://Bresenham�㷨
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
    _itoa(showX, dintX, 10);//������showXת���ַ���dintX
    _itoa(showY, dintY, 10);//������showYת���ַ���dintY
    char str1[100] = "��һ��������꣺��";//��ʱ����û�ж��峤��   Ԫ�صĸ���Ӧ��Ϊstrlen +1  ��Ϊ�ַ���ĩβ�� '\0'���� 
    char str2[100] = "�ڶ���������꣺��";
    if (flag == 1){
        // _countof(dintX)�ܹ���ȡ��������Ԫ�صĸ��� ����\0��
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


//����easyX
void easyX(int code){
    initgraph(640, 480);       //��ʼ��
    showWord(code);
    MOUSEMSG m; // ���������Ϣ
    int n=0;//��ȡ������
    int exit = false;
    int x0=0, y0=0,x1=0,y1=0;
    while (n<2 && !exit)
    {
        m = GetMouseMsg();
        switch (m.uMsg)
        {
			//WM_RBUTTONDOWN:��������Ҽ�����ʱ����Ϣ
        case WM_RBUTTONDOWN:
            outtextxy(200, 300, "�ٴε�����˳�");
            exit = true;
            break;    // ������Ҽ��˳�����
        }
        while (m.uMsg != WM_LBUTTONDOWN){
            m = GetMouseMsg();
            switch (m.uMsg)
            {
            case WM_RBUTTONDOWN:
                outtextxy(200, 300, "�ٴε�����˳�");
                exit = true;
                break;    // ������Ҽ��˳�����
            }

        }
		 
        while (m.uMsg != WM_LBUTTONUP){
            m = GetMouseMsg();

			//cleardevice()�����Ļ��ͼ�λ�����
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
            //����
            drawLine(x0, y0, x1, y1, code);
            //����
            n = 0;
        }
    }
    //_getch();                  //�ȴ��û�����
    closegraph();             //�ر�ͼ��
}

void main(){
    int n = 1;
    printf("��ѡ�����㷨���ߣ�\n");
    printf("1.easyXϵͳ���ߺ���.\n");
    printf("2.DDA�����㷨����.\n");
    printf("3.�е㻭���㷨����.\n");
    printf("4.Bresenham�����㷨����.\n");
    printf("0.�˳�.\n");
    while (n != 0){
        scanf("%d", &n);
        if (n == 0){
            exit(0);
        }
        easyX(n);
    }
}

