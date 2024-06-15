#include <windows.h>
#include <gl/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stb_easy_font.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

int width, height;

typedef struct{
    char name[20];
    float vert[8];
    BOOL isText;
} Button;

int r = 1, g = 0, b = 0;

int is3d = -1;

Button btn[] = {
    {"program", {200,10,400,10,400,40,200,40}, TRUE},
    {"", {265,205,295,205,295,235,265,235}, FALSE},
    {"+", {305,205,335,205,335,235,305,235}, FALSE},
    {"3d", {5,205,55,205,55,255,5,255}, FALSE},
    {"red", {5,485,35,485,35,515,5,515}, FALSE},
    {"green", {5,450,35,450,35,480,5,480}, FALSE},
    {"blue", {5,415,35,415,35,445,5,445}, FALSE},
    {"yelow", {5,520,35,520,35,550,5,550}, FALSE},
    {"purple", {5,555,35,555,35,585,5,585}, FALSE},
    {"info", {200,45,400,45,400,75,200,75}, TRUE},
    {"exit", {200,80,400,80,400,110,200,110}, TRUE}
};

int btnCnt = sizeof(btn) / sizeof(btn[0]);
void drawLetter3d (int x, int y, float r, float g, float b, float size){
    glPushMatrix();
    glTranslatef(300,500,0);
    glScalef(size, size, 1);
    glBegin(GL_POLYGON);
        glColor3f(r, g, b);
        glVertex2f(x-120, y-180);
        glVertex2f(x+60, y-180);
        glVertex2f(x+120, y-120);
        glVertex2f(x+120, y+120);
        glVertex2f(x+60, y+180);
        glVertex2f(x-120, y+180);
    glEnd();

    glBegin(GL_POLYGON);
        glColor3f(1, 1, 1);
        glVertex2f(x-60, y-120);
        glVertex2f(x+30, y-120);
        glVertex2f(x+60, y-90);
        glVertex2f(x+60, y+90);
        glVertex2f(x+30, y+120);
        glVertex2f(x-60, y+120);

    glEnd();

    glBegin(GL_QUADS);
        glColor3f(r+0.5, g+0.5, b+0.5);
        glVertex2d(x-180, y-210);
        glVertex2d(x-120, y-180);
        glVertex2d(x-120, y+180);
        glVertex2d(x-180, y+150);

        glVertex2d(x-180, y-210);
        glVertex2d(x, y-210);
        glVertex2d(x+60, y-180);
        glVertex2d(x-120, y-180);

        glVertex2d(x, y-120);
        glVertex2d(x+30, y-120);
        glVertex2d(x+30, y-120);
        glVertex2d(x+60, y-90);

        glVertex2d(x, y-120);
        glVertex2d(x+60, y-90);
        glVertex2d(x+60, y+90);
        glVertex2d(x, y+60);

        glVertex2d(x, y+60);
        glVertex2d(x+60, y+90);
        glVertex2d(x+30, y+120);
        glVertex2d(x-30, y+90);

        glVertex2d(x-30, y+90);
        glVertex2d(x+30, y+120);
        glVertex2d(x-60, y+120);
        glVertex2d(x-60, y+90);
    glEnd();

    glLineWidth(3);

    glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        glVertex2f(x-120, y-180);
        glVertex2f(x+60, y-180);
        glVertex2f(x+120, y-120);
        glVertex2f(x+120, y+120);
        glVertex2f(x+60, y+180);
        glVertex2f(x-120, y+180);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        glVertex2f(x-60, y-120);
        glVertex2f(x+30, y-120);
        glVertex2f(x+60, y-90);
        glVertex2f(x+60, y+90);
        glVertex2f(x+30, y+120);
        glVertex2f(x-60, y+120);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(0, 0, 0);
        glVertex2f(x+60, y-180);
        glVertex2f(x, y-210);
        glVertex2f(x-180, y-210);
        glVertex2f(x-180, y+150);
        glVertex2f(x-120, y+180);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glColor3f(0, 0, 0);
        glVertex2f(x+60, y-90);
        glVertex2f(x, y-120);
        glVertex2f(x, y+60);
        glVertex2f(x-30, y+90);
        glVertex2f(x-60, y+90);
    glEnd();

    glBegin(GL_LINES);
        glColor3f(0, 0, 0);
        glVertex2f(x-180, y-210);
        glVertex2f(x-120, y-180);

        glVertex2f(x, y+60);
        glVertex2f(x+60, y+90);

        glVertex2f(x-30, y+90);
        glVertex2f(x+30, y+120);
    glEnd();


    glLineWidth(1);
    glPopMatrix();
}

void print_string(float x, float y, char *text, float r, float g, float b)
{
  static char buffer[99999]; // ~500 chars
  int num_quads;

  num_quads = stb_easy_font_print(x, y, text, NULL, buffer, sizeof(buffer));

  glColor3f(r,g,b);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 16, buffer);
  glDrawArrays(GL_QUADS, 0, num_quads*4);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void program(){
    char str[255] = "";
    printf("Input: ");
    fgets(str, 255, stdin);
    int iCounter = 0;
    int k = 0;
    for(int i = 0; str[i] != '\0'; i++){

        if(str[i] == 'i') iCounter++;
        if('a' <= str[i] && 'z' >= str[i]){
            if(!('a' <= str[i + 1 ] && 'z' >= str[i + 1])) k++;
        }
        if (k == 3) break;
    }

    printf("Kilkist 'i': %d\n", iCounter);

    k = 0;
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == '-' || str[i] == '+' || str[i] == '*'){
            if(str[i+1] != '-' && str[i+1] != '+' && str[i+1] != '*') k++;
        }
    }

    int znakStart = 0, znakEnd = 0;
    for(int j = 0; j < k; j++){
        for(int i = znakEnd; str[i] != '\0'; i++){
            if(str[i] != '-' && str[i] != '+' && str[i] != '*') {
                if(str[i+1] == '-' || str[i+1] == '+' || str[i+1] == '*') znakStart = i + 1;
            }
            if(str[i] == '-' || str[i] == '+' || str[i] == '*'){
                if(str[i+1] != '-' && str[i+1] != '+' && str[i+1] != '*'){
                    znakEnd = i + 1;
                    break;
                }
            }
        }

        int plusCounter = 0;
        for(int i = znakStart; i < znakEnd; i++){
            if(str[i] == '+'){
                plusCounter++;
            }
        }

        if(plusCounter >=2 ){
            for(int i = znakStart; i < znakEnd; i++){
                printf("%c", str[i]);
            }
            printf("\n");
        }
    }

}

void drawLetter2d (int x, int y, float r, float g, float b, float size){
    glPushMatrix();
    glTranslatef(300,500,0);
    glScalef(size, size, 1);
    glBegin(GL_POLYGON);
                glColor3f(r, g, b);
                glVertex2f(x-120, y-180);
                glVertex2f(x+60, y-180);
                glVertex2f(x+120, y-120);
                glVertex2f(x+120, y+120);
                glVertex2f(x+60, y+180);
                glVertex2f(x-120, y+180);
    glEnd();

    glBegin(GL_POLYGON);

                glColor3f(1, 1, 1);
                glVertex2f(x-60, y-120);
                glVertex2f(x+30, y-120);
                glVertex2f(x+60, y-90);
                glVertex2f(x+60, y+90);
                glVertex2f(x+30, y+120);
                glVertex2f(x-60, y+120);

    glEnd();

    glLineWidth(3);

    glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        glVertex2f(x-120, y-180);
        glVertex2f(x+60, y-180);
        glVertex2f(x+120, y-120);
        glVertex2f(x+120, y+120);
        glVertex2f(x+60, y+180);
        glVertex2f(x-120, y+180);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        glVertex2f(x-60, y-120);
        glVertex2f(x+30, y-120);
        glVertex2f(x+60, y-90);
        glVertex2f(x+60, y+90);
        glVertex2f(x+30, y+120);
        glVertex2f(x-60, y+120);
    glEnd();

    glLineWidth(1);
    glPopMatrix();
}


void showButton(Button btn){
    glEnableClientState(GL_VERTEX_ARRAY);
        glColor3f(0.6,0.6,0.6);
        glVertexPointer(2, GL_FLOAT, 0, btn.vert);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPushMatrix();
        if(btn.isText){
            glTranslatef(btn.vert[0],btn.vert[1],0);
            glScalef(2,2,1);
            print_string(3,3,btn.name, 0,0,0);
        }
    glPopMatrix();
}

BOOL pointInButton(int x, int y, Button btn){
    return (x > btn.vert[0]) && (x < btn.vert[4]) &&(y > btn.vert[1]) && (y < btn.vert[5]);
}

float size = 1.0;

BOOL isInfoPressed = FALSE;

void showInfo(){
    glPushMatrix();
    glBegin(GL_POLYGON);
        glColor3f(0.9,0.9,0.9);
        glVertex2d(100,300);
        glVertex2d(500,300);
        glVertex2d(500,700);
        glVertex2d(100,700);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glColor3f(0,0,0);
        glVertex2d(100,300);
        glVertex2d(500,300);
        glVertex2d(500,700);
        glVertex2d(100,700);
    glEnd();
    glTranslatef(100,300,0);
    glScalef(2,2,1);
    print_string(85,10,"lab 6",0,0,0);
    print_string(70,25,"variant 20",0,0,0);
    print_string(65,125,"Vadym Minder",0,0,0);
    print_string(80,140,"KV-22",0,0,0);

    glPopMatrix();
}

void showMenu (){
    glPushMatrix();
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1,1);
        if(is3d == 1){
            drawLetter3d(0, 0, r, g, b, size);
        }else {
            drawLetter2d(0, 0, r, g, b, size);
        }


        glBegin(GL_QUADS);
                glColor3f(0.9,0.9,0.9);
                glVertex2d(0,0);
                glVertex2d(600,0);
                glVertex2d(600,200);
                glVertex2d(0,200);
        glEnd();
        for(int i = 0; i < btnCnt; i++){
            showButton(btn[i]);
        }

        glBegin(GL_LINE_STRIP);
            glColor3f(0,0,0);
            glVertex2d(7,215);
            glVertex2d(25,215);
            glVertex2d(25,245);
            glVertex2d(7,245);
        glEnd();

        glBegin(GL_LINES);
            glColor3f(0,0,0);
            glVertex2d(7,230);
            glVertex2d(25,230);
        glEnd();

        glBegin(GL_LINE_STRIP);
            glColor3f(0,0,0);
            glVertex2d(50,210);
            glVertex2d(50,245);
            glVertex2d(35,245);
            glVertex2d(35,230);
            glVertex2d(50,230);
        glEnd();

        glBegin(GL_LINES);
            glColor3f(0,0,0);
            glVertex2d(270,220);
            glVertex2d(290, 220);
            glVertex2d(310,220);
            glVertex2d(330, 220);
            glVertex2d(320, 210);
            glVertex2d(320, 230);
        glEnd();

        glBegin(GL_LINES);
            glColor3f(0,0,0);
            glVertex2d(270,220);
            glVertex2d(290, 220);
            glVertex2d(310,220);
            glVertex2d(330, 220);
            glVertex2d(320, 210);
            glVertex2d(320, 230);
        glEnd();

        glBegin(GL_QUADS);
            glColor3f(1,0,0);
            glVertex2d(8,487);
            glVertex2d(32,487);
            glVertex2d(32,512);
            glVertex2d(8,512);

            glColor3f(0,1,0);
            glVertex2d(8,453);
            glVertex2d(32,453);
            glVertex2d(32,477);
            glVertex2d(8,477);

            glColor3f(0,0,1);
            glVertex2d(8,418);
            glVertex2d(32,418);
            glVertex2d(32,442);
            glVertex2d(8,442);

            glColor3f(1,1,0);
            glVertex2d(8,523);
            glVertex2d(32,523);
            glVertex2d(32,547);
            glVertex2d(8,547);

            glColor3f(1,0,1);
            glVertex2d(8,558);
            glVertex2d(32,558);
            glVertex2d(32,582);
            glVertex2d(8,582);
        glEnd();
        if(isInfoPressed) showInfo();

    glEnd();
    glPopMatrix();
}



int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          600,
                          800,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClearColor(1, 1, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            glPushMatrix();


            glPopMatrix();

            showMenu();

            SwapBuffers(hDC);

            theta += 1.0f;
            Sleep (1);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
        break;


        case WM_DESTROY:
            return 0;

        case WM_SIZE:
            width = LOWORD(lParam);
            height = HIWORD(lParam);
            glViewport(0,0, width, height);
            glLoadIdentity();
            float k = width/ (float)height;
            glOrtho(-k,k,-1,1,-1,1);
        break;

        case WM_LBUTTONDOWN:
            if(pointInButton(LOWORD(lParam), HIWORD(lParam), btn[0])) program();
            if(pointInButton(LOWORD(lParam), HIWORD(lParam), btn[10])) exit(0);
            if(pointInButton(LOWORD(lParam), HIWORD(lParam), btn[9])) isInfoPressed = !isInfoPressed;
            if(pointInButton(LOWORD(lParam), HIWORD(lParam), btn[1])) size -= 0.1;
            if(pointInButton(LOWORD(lParam), HIWORD(lParam), btn[2])) size += 0.1;
            if(pointInButton(LOWORD(lParam), HIWORD(lParam), btn[3])) is3d *= -1;
            if(pointInButton(LOWORD(lParam), HIWORD(lParam), btn[4])){
                r = 1;
                g = 0;
                b = 0;
            }
            if(pointInButton(LOWORD(lParam), HIWORD(lParam), btn[5])){
                r = 0;
                g = 1;
                b = 0;
            }
            if(pointInButton(LOWORD(lParam), HIWORD(lParam), btn[6])){
                r = 0;
                g = 0;
                b = 1;
            }
            if(pointInButton(LOWORD(lParam), HIWORD(lParam), btn[7])){
                r = 1;
                g = 1;
                b = 0;
            }
            if(pointInButton(LOWORD(lParam), HIWORD(lParam), btn[8])){
                r = 1;
                g = 0;
                b = 1;
            }

        break;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

