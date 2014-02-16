#ifndef MEKRANOPLAN_H
#define MEKRANOPLAN_H

//-#include <QGLFunctions>
//-#include <QGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

//============================================================================================
class MEkranoplan : protected QOpenGLFunctions
//-                 protected QGLFunctions
{
public:
    MEkranoplan();
    virtual ~MEkranoplan();

//-    void init();
//-    void drawCubeGeometry(QGLShaderProgram *program);

  void Init();
  void Draw(QOpenGLShaderProgram* pShaderProgram);

private:
//-    void initCubeGeometry();
  void InitGeometry();

    GLuint vboIds[2];
//GLuint vboIds[3];
//--
  GLsizei CountVertexIndices;
};
//============================================================================================
#endif // MEKRANOPLAN_H
