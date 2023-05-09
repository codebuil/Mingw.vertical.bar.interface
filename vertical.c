#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
//.\gcc -o verticalbar.exe verticalbar.c  -mwindows
#define TIMER_ID 1
#define TIMER_INTERVAL 10000
#define MAX_BUFFER_SIZE 1024
#define lines 60
int iiii=0;
  
   int i=0;
   int cc=0;
   int ii=0;
   char l[50];
int numOptions =0;
const char* options[] = { "X86", "8086", "80186", "80286", "80386", "80486", "ARM", "ARM7" };
HWND hRadioButton[50];
static HWND hStartEdit,hEndEdit,hButton,hButton2,thew,tthew[lines*2+1],hGroupBox;
int xx = 2; // Define a posição horizontal
int yy = 2; // Define a posição vertical
 int nn,nnn;   
  static char startStr[1024], endStr[1024];

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("Temporizador");
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("Este programa requer Windows NT!"), szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName, TEXT("vertical bar"),
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
         
         hGroupBox=CreateWindow(
                     "BUTTON", NULL,
                    WS_CHILD | WS_VISIBLE | BS_GROUPBOX ,
                    0, 0, 640, 640,
                    hwnd, NULL, hInstance, NULL
                );
       
        hButton = CreateWindow("BUTTON", "show", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            650, 10, 50, 30,  hwnd, (HMENU)30, hInstance, NULL);
        hButton2 = CreateWindow("BUTTON", "hide", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            650, 350, 50, 30,  hwnd, (HMENU)40, hInstance, NULL);
    numOptions = sizeof(options) / sizeof(options[0]);
    const int numOptions = sizeof(options) / sizeof(options[0]);
    int yPos = 20;
    
    for (i = 0; i < numOptions; i++)
    {
        iiii=i+100;
        hRadioButton[i] = CreateWindow(
            "BUTTON",
            options[i],
            WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
            20, yPos, 150, 20,
            hGroupBox,
            (HMENU)iiii,
            hInstance,
            NULL);

        yPos += 25;
    }     
SendMessage(hRadioButton[0], BM_SETCHECK, BST_CHECKED, 0);
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static TCHAR szBuffer[80];
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
    
    time_t rawtime;
    struct tm *timeinfo;
  
   
   
    char buffer[MAX_BUFFER_SIZE];
int yPos = 20;
    

    switch (message)
    {
        case WM_CREATE:
  
        SetWindowText(hwnd,"ready");//options[i] );
        
        
        break;
        case WM_COMMAND:
        ii=LOWORD(wParam);
        
        
        
        
        
        
            if(ii==30){
            yy=yy+20;
            if(yy>4)yy=4;
            SetWindowText(hwnd,"show");
           SetWindowPos(hGroupBox, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
           for(i=0;i<8;i++){
                 ShowWindow(hRadioButton[i], SW_SHOW);
           }
            }
            if (ii==40){
            yy=yy-20; 
            if(yy<-3800)yy=3800;
            SetWindowText(hwnd,"hide");
           SetWindowPos(hGroupBox, NULL, -640, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
           for(i=0;i<8;i++){
                 ShowWindow(hRadioButton[i], SW_HIDE);
           }
            }
            
            
        if (ii>=100 && ii<=108)
    {   
        ii=ii-100;
        

            SetWindowTextA(hwnd, options[ii]);
        for(i=0;i<8;i++){
            if(i!=ii)SendMessage(hRadioButton[i], BM_SETCHECK, BST_UNCHECKED, 0);

        }    
            SendMessage(hRadioButton[ii], BM_SETCHECK, BST_CHECKED, 0);
            
    }

        
    
      
    break;
   case WM_PAINT:
            
            hdc = BeginPaint(hwnd, &ps);
            
            // Define a cor de fundo da janela para azul
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
            FillRect(hdc, &ps.rcPaint, hBrush);
            DeleteObject(hBrush);
            
            // Define a cor das linhas para branco
            HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
            SelectObject(hdc, hPen);
            
            // Desenha as linhas com base nas coordenadas fornecidas
            
            
            // Libera os recursos utilizados
            DeleteObject(hPen);
            EndPaint(hwnd, &ps);
            break;
    

    case WM_DESTROY:
        KillTimer(hwnd, TIMER_ID);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
