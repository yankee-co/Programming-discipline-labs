#include <GL/freeglut.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <time.h>

float a = 1; // Параметр a
float x1, x2; // Відрізок на якому буде згенеровано графік
float scale = 1.0; // Масштаб

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(-x2+0.5, x2-1.5);// Встановлення позиції растрового тексту
    const char* name = "Eduard Zemlyanski KV-22";
    for (int i = 0; name[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, name[i]); // Виведення символу
    }
    glRasterPos2f(-x2+0.5, x2-2); // Встановлення позиції растрового тексту
    const char* equation1 = "y = arccosh(x / a);";
    for (int i = 0; equation1[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, equation1[i]);
    }
    glLineWidth(4.0);
    glBegin(GL_LINE_STRIP); // Зміна режиму малювання на GL_LINE_STRIP
    glColor3f(1.0, 0.5, 0);

    for (float x = x1; x <= x2; x += 0.01)
    {
        float y = a * acosh(x / a);
        glVertex2f(x * scale, y * scale);
    }
    glEnd();
    glLineWidth(1.0);
    // Відображення координатних вісей з підписами та маркерами
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    // Вісь X
    glVertex2f(-x2, 0.0);
    glVertex2f(x2, 0.0);
    for (float i = -x2; i <= x2; i += 1.0) {
        glVertex2f(i* scale, 0.1);
        glVertex2f(i* scale, -0.1);
        glRasterPos2f(i* scale, -0.3);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, '0' + (int)i);
    }
    // Вісь Y
    glVertex2f(0.0, -x2);
    glVertex2f(0.0, x2);
    glRasterPos2f(0.3, x2*scale);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 24);
    for (float i = -x2; i <= x2; i++) {
        glVertex2f(0.1, i*scale);
        glVertex2f(-0.1, i*scale);

        glRasterPos2f(-0.3, i*scale);
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (int)i + '0');

    }
    glEnd();

    glFlush();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-x2, x2, -x2, x2, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void mouseWheel(int wheel, int direction, int x, int y)
{
    if (direction == 1)
    {
        // Zoom in
        scale *= 1.1;
    }
    else
    {
        // Zoom out
        scale /= 1.1;
    }

    // Redraw the scene
    glutPostRedisplay();
}

void SetData(){
    std::cout << "Enter 'a': ";
    scanf("%f", &a);

    std::cout << "Enter 'x1': ";
    scanf("%f", &x1);

    std::cout << "Enter 'x2': ";
    scanf("%f", &x2);

    if (a < 0 || x2 <= x1){
        std::cout << "Wrond data given";
        Sleep(2000);
        system("cls");
        SetData();
    }
}

int main(int argc, char** argv)
{
    SetData();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("arccosh(x/a) function graph");

    glutMouseWheelFunc(mouseWheel);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);;

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutMainLoop();
    return 0;
}
