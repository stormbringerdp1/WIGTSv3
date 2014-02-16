#include "MEkranoplan.h"

//#include <QVector2D>
#include <QVector3D>
  #include <QMessageBox>
#include <QList>
#include <QFile>
#include <QTextStream>

//============================================================================================
struct VertexData
{
    QVector3D position;
  QVector3D normal;
    QVector2D texCoord;
//    QVector3D texCoord;
};
//QVector3D vertex[495];
//============================================================================================
MEkranoplan::MEkranoplan()
{
}
//--------------------------------------------------------------------------------------------
MEkranoplan::~MEkranoplan()
{
  glDeleteBuffers(2, vboIds);
//  glDeleteBuffers(1, vboIds);
//  glDeleteBuffers(3, vboIds);
}
//--------------------------------------------------------------------------------------------
//-void GeometryEngine::init()
void MEkranoplan::Init()
{
//-    initializeGLFunctions();
  initializeOpenGLFunctions();

//! [0]
  // Generate 2 VBOs
  glGenBuffers(2, vboIds);
//glGenBuffers(1, vboIds);
//glGenBuffers(3, vboIds);

//! [0]

  // Initializes cube geometry and transfers it to VBOs
//-    initCubeGeometry();
  InitGeometry();
}
//--------------------------------------------------------------------------------------------
//-void GeometryEngine::initCubeGeometry()
void MEkranoplan::InitGeometry()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
/*-
    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0, -1.0,  1.0), QVector2D(0.0, 0.0)},  // v0
        {QVector3D( 1.0, -1.0,  1.0), QVector2D(0.33, 0.0)}, // v1
        {QVector3D(-1.0,  1.0,  1.0), QVector2D(0.0, 0.5)},  // v2
        {QVector3D( 1.0,  1.0,  1.0), QVector2D(0.33, 0.5)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0, -1.0,  1.0), QVector2D( 0.0, 0.5)}, // v4
        {QVector3D( 1.0, -1.0, -1.0), QVector2D(0.33, 0.5)}, // v5
        {QVector3D( 1.0,  1.0,  1.0), QVector2D(0.0, 1.0)},  // v6
        {QVector3D( 1.0,  1.0, -1.0), QVector2D(0.33, 1.0)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0, -1.0, -1.0), QVector2D(0.66, 0.5)}, // v8
        {QVector3D(-1.0, -1.0, -1.0), QVector2D(1.0, 0.5)},  // v9
        {QVector3D( 1.0,  1.0, -1.0), QVector2D(0.66, 1.0)}, // v10
        {QVector3D(-1.0,  1.0, -1.0), QVector2D(1.0, 1.0)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0, -1.0, -1.0), QVector2D(0.66, 0.0)}, // v12
        {QVector3D(-1.0, -1.0,  1.0), QVector2D(1.0, 0.0)},  // v13
        {QVector3D(-1.0,  1.0, -1.0), QVector2D(0.66, 0.5)}, // v14
        {QVector3D(-1.0,  1.0,  1.0), QVector2D(1.0, 0.5)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0, -1.0, -1.0), QVector2D(0.33, 0.0)}, // v16
        {QVector3D( 1.0, -1.0, -1.0), QVector2D(0.66, 0.0)}, // v17
        {QVector3D(-1.0, -1.0,  1.0), QVector2D(0.33, 0.5)}, // v18
        {QVector3D( 1.0, -1.0,  1.0), QVector2D(0.66, 0.5)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0,  1.0,  1.0), QVector2D(0.33, 0.5)}, // v20
        {QVector3D( 1.0,  1.0,  1.0), QVector2D(0.66, 0.5)}, // v21
        {QVector3D(-1.0,  1.0, -1.0), QVector2D(0.33, 1.0)}, // v22
        {QVector3D( 1.0,  1.0, -1.0), QVector2D(0.66, 1.0)}  // v23
    };
*/
/*
    VertexData vertices[] = {
        {QVector3D(-1.0, -1.0,  1.0), QVector3D(0.0, 0.0, 1.0)},  // v0
        {QVector3D( 1.0, -1.0,  1.0), QVector3D(0.33, 0.0, 1.0)}, // v1
        {QVector3D(-1.0,  1.0,  1.0), QVector3D(0.0, 0.5, 1.0)},  // v2
        {QVector3D( 1.0,  1.0,  1.0), QVector3D(0.33, 0.5, 1.0)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0, -1.0,  1.0), QVector3D( 0.0, 0.5, 1.0)}, // v4
        {QVector3D( 1.0, -1.0, -1.0), QVector3D(0.33, 0.5, 1.0)}, // v5
        {QVector3D( 1.0,  1.0,  1.0), QVector3D(0.0, 1.0, 1.0)},  // v6
        {QVector3D( 1.0,  1.0, -1.0), QVector3D(0.33, 1.0, 1.0)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0, -1.0, -1.0), QVector3D(0.66, 0.5, 1.0)}, // v8
        {QVector3D(-1.0, -1.0, -1.0), QVector3D(1.0, 0.5, 1.0)},  // v9
        {QVector3D( 1.0,  1.0, -1.0), QVector3D(0.66, 1.0, 1.0)}, // v10
        {QVector3D(-1.0,  1.0, -1.0), QVector3D(1.0, 1.0, 1.0)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0, -1.0, -1.0), QVector3D(0.66, 0.0, 1.0)}, // v12
        {QVector3D(-1.0, -1.0,  1.0), QVector3D(1.0, 0.0, 1.0)},  // v13
        {QVector3D(-1.0,  1.0, -1.0), QVector3D(0.66, 0.5, 1.0)}, // v14
        {QVector3D(-1.0,  1.0,  1.0), QVector3D(1.0, 0.5, 1.0)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0, -1.0, -1.0), QVector3D(0.33, 0.0, 1.0)}, // v16
        {QVector3D( 1.0, -1.0, -1.0), QVector3D(0.66, 0.0, 1.0)}, // v17
        {QVector3D(-1.0, -1.0,  1.0), QVector3D(0.33, 0.5, 1.0)}, // v18
        {QVector3D( 1.0, -1.0,  1.0), QVector3D(0.66, 0.5, 1.0)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0,  1.0,  1.0), QVector3D(0.33, 0.5, 1.0)}, // v20
        {QVector3D( 1.0,  1.0,  1.0), QVector3D(0.66, 0.5, 1.0)}, // v21
        {QVector3D(-1.0,  1.0, -1.0), QVector3D(0.33, 1.0, 1.0)}, // v22
        {QVector3D( 1.0,  1.0, -1.0), QVector3D(0.66, 1.0, 1.0)}  // v23
    };
*/
/*
QVector3D position[] = {
        QVector3D(-1.0, -1.0,  1.0),  // v0
        QVector3D( 1.0, -1.0,  1.0), // v1
        QVector3D(-1.0,  1.0,  1.0),  // v2
        QVector3D( 1.0,  1.0,  1.0), // v3

        // Vertex data for face 1
        QVector3D( 1.0, -1.0,  1.0), // v4
        QVector3D( 1.0, -1.0, -1.0), // v5
        QVector3D( 1.0,  1.0,  1.0),  // v6
        QVector3D( 1.0,  1.0, -1.0), // v7

        // Vertex data for face 2
        QVector3D( 1.0, -1.0, -1.0), // v8
        QVector3D(-1.0, -1.0, -1.0),  // v9
        QVector3D( 1.0,  1.0, -1.0), // v10
        QVector3D(-1.0,  1.0, -1.0),  // v11

        // Vertex data for face 3
        QVector3D(-1.0, -1.0, -1.0), // v12
        QVector3D(-1.0, -1.0,  1.0),  // v13
        QVector3D(-1.0,  1.0, -1.0), // v14
        QVector3D(-1.0,  1.0,  1.0),  // v15

        // Vertex data for face 4
        QVector3D(-1.0, -1.0, -1.0), // v16
        QVector3D( 1.0, -1.0, -1.0), // v17
        QVector3D(-1.0, -1.0,  1.0), // v18
        QVector3D( 1.0, -1.0,  1.0), // v19

        // Vertex data for face 5
        QVector3D(-1.0,  1.0,  1.0), // v20
        QVector3D( 1.0,  1.0,  1.0), // v21
        QVector3D(-1.0,  1.0, -1.0), // v22
        QVector3D( 1.0,  1.0, -1.0)};  // v23

QVector3D texCoord[] = {
        QVector3D(0.0, 0.0, 1.0),  // v0
        QVector3D(0.33, 0.0, 1.0), // v1
        QVector3D(0.0, 0.5, 1.0),  // v2
        QVector3D(0.33, 0.5, 1.0), // v3

        // Vertex data for face 1
        QVector3D( 0.0, 0.5, 1.0), // v4
        QVector3D(0.33, 0.5, 1.0), // v5
        QVector3D(0.0, 1.0, 1.0),  // v6
        QVector3D(0.33, 1.0, 1.0), // v7

        // Vertex data for face 2
        QVector3D(0.66, 0.5, 1.0), // v8
        QVector3D(1.0, 0.5, 1.0),  // v9
        QVector3D(0.66, 1.0, 1.0), // v10
        QVector3D(1.0, 1.0, 1.0),  // v11

        // Vertex data for face 3
        QVector3D(0.66, 0.0, 1.0), // v12
        QVector3D(1.0, 0.0, 1.0),  // v13
        QVector3D(0.66, 0.5, 1.0), // v14
        QVector3D(1.0, 0.5, 1.0),  // v15

        // Vertex data for face 4
        QVector3D(0.33, 0.0, 1.0), // v16
        QVector3D(0.66, 0.0, 1.0), // v17
        QVector3D(0.33, 0.5, 1.0), // v18
        QVector3D(0.66, 0.5, 1.0), // v19

        // Vertex data for face 5
        QVector3D(0.33, 0.5, 1.0), // v20
        QVector3D(0.66, 0.5, 1.0), // v21
        QVector3D(0.33, 1.0, 1.0), // v22
        QVector3D(0.66, 1.0, 1.0)};  // v23
*/
/*-
    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };
*/


//  QString fileNameIn("d:\\Progs\\Ekranoplan\\export\\12.obj");  //11.obj"); //9.obj"); //7.obj"); //5.obj"); //6.obj");
//++  QString fileNameIn("__3dsMax_Ekranoplan.obj");
  QString fileNameIn(":/Ekranoplan_3dsMax.obj");
//  const int countIndicesDiff = 910;  //  countIndicesDiff == listFacePositionIndicesDiff.count()
//  const int countindices = 2832;  // =944*3

//++QString fileNameOut("__Out_Ekranoplan.txt");

//  //QString fileNameIn("d:\\Progs\\Ekranoplan\\export\\cube.obj");
//  QString fileNameIn("__3dsMax_Cube.obj");
//  const int countIndicesDiff = 36;//24;  //  countIndicesDiff == listFacePositionIndicesDiff.count()
//  const int countindices = 36; // = 12*3
//  QString fileNameOut("__Out_Cube.txt");

//  const int countvertices = 495;   const int countindices = 2832;
//  const int countvertices = 495;   const int countindices = 2832; // =944*3      //5.obj
//  const int countvertices = 490;   const int countindices = 2832;               //7.obj
//  const int countvertices = 495;   const int countindices = 2832;              //9.obj


  QList<QVector3D> listPositions;
  QList<QVector3D> listTextures;
  QList<QVector3D> listNormals;
  QList<int> listFacePositionIndices;
  QList<int> listFaceTextureIndices;
  QList<int> listFaceNormalIndices;

  QFile fileIn(fileNameIn);
  if(!fileIn.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QMessageBox msgBox; msgBox.setText("Problem file \""+fileNameIn+"\"");   msgBox.exec();
    return;
  }
//fscanf(()
QMessageBox msgBox;
  QTextStream in(&fileIn);  QString line;  QChar qc; char c;  int pos1,pos2;  QString s;  QVector3D v3D;
  while(!in.atEnd()) {
    line = in.readLine();
    if(line.length() == 0)  continue;
    qc = line.at(0);
    switch(qc.toLatin1()) {
      case 'v':
        c = line.at(1).toLatin1();
        if(c == ' ' || c == 't' || c == 'n') {  // vertices || textures || normals
          pos1 = 3;
          pos2 = line.indexOf(' ', pos1);  v3D.setX(line.mid(pos1, pos2-pos1).toFloat());  pos1 = pos2+1;
          pos2 = line.indexOf(' ', pos1);  v3D.setY(line.mid(pos1, pos2-pos1).toFloat());
                                           v3D.setZ(line.mid(pos2+1).toFloat());
//          pos2 = line.indexOf(' ', pos1);  v3D.setZ(line.mid(pos1, pos2-pos1).toFloat());
//                                           v3D.setY(line.mid(pos2+1).toFloat());
          if(c == ' ')       listPositions << v3D;
          else if(c == 't')  listTextures << v3D;
          else               listNormals  << v3D;   //  c == 'n'
        }
//s.sprintf("v3D.x() = %.4f,  v3D.y() = %.4f,  v3D.z() = %.4f",v3D.x(),v3D.y(),v3D.z());
//msgBox.setText(s);   msgBox.exec();
//return;
        break;
      case 'f':
        if(line.at(1).toLatin1() == ' ') {  // indices
          pos1 = 2;
          if(listFaceTextureIndices.count() == 0 && listNormals.count() == 0) {
//:  f 5 34 85
                              pos2 = line.indexOf(' ', pos1);  listFacePositionIndices << line.mid(pos1, pos2-pos1).toInt();
            pos1 = pos2 + 1;  pos2 = line.indexOf(' ', pos1);  listFacePositionIndices << line.mid(pos1, pos2-pos1).toInt();
            pos1 = pos2 + 1;  pos2 = line.count();             listFacePositionIndices << line.mid(pos1, pos2-pos1).toInt();
          }
          if((listTextures.count() > 0 && listNormals.count() == 0) || (listTextures.count() == 0 && listNormals.count() > 0)) {
//:  f 5/6 34/67 85/2
                              pos2 = line.indexOf('/', pos1);  listFacePositionIndices << line.mid(pos1, pos2-pos1).toInt();
            pos1 = pos2 + 1;  pos2 = line.indexOf(' ', pos1);
            if(listTextures.count() > 0)  listFaceTextureIndices << line.mid(pos1, pos2-pos1).toInt();
            else                          listFaceNormalIndices  << line.mid(pos1, pos2-pos1).toInt();

            pos1 = pos2 + 1;  pos2 = line.indexOf('/', pos1);  listFacePositionIndices << line.mid(pos1, pos2-pos1).toInt();
            pos1 = pos2 + 1;  pos2 = line.indexOf(' ', pos1);
            if(listTextures.count() > 0)  listFaceTextureIndices << line.mid(pos1, pos2-pos1).toInt();
            else                          listFaceNormalIndices  << line.mid(pos1, pos2-pos1).toInt();

            pos1 = pos2 + 1;  pos2 = line.indexOf('/', pos1);  listFacePositionIndices << line.mid(pos1, pos2-pos1).toInt();
            pos1 = pos2 + 1;  pos2 = line.count();
            if(listTextures.count() > 0)  listFaceTextureIndices << line.mid(pos1, pos2-pos1).toInt();
            else                          listFaceNormalIndices  << line.mid(pos1, pos2-pos1).toInt();
          }
          else {
//:  f 5/6/4 34/67/18 85/2/16
/*
                              pos2 = line.indexOf('/', pos1);  listFacePositionIndices  << line.mid(pos1, pos2-pos1).toInt();
            pos1 = pos2 + 1;  pos2 = line.indexOf('/', pos1);  listFaceTextureIndices << line.mid(pos1, pos2-pos1).toInt();
            pos1 = pos2 + 1;  pos2 = line.indexOf(' ', pos1);  listFaceNormalIndices  << line.mid(pos1, pos2-pos1).toInt();

            pos1 = pos2 + 1;  pos2 = line.indexOf('/', pos1);  listFacePositionIndices  << line.mid(pos1, pos2-pos1).toInt();
            pos1 = pos2 + 1;  pos2 = line.indexOf('/', pos1);  listFaceTextureIndices << line.mid(pos1, pos2-pos1).toInt();
            pos1 = pos2 + 1;  pos2 = line.indexOf(' ', pos1);  listFaceNormalIndices  << line.mid(pos1, pos2-pos1).toInt();

            pos1 = pos2 + 1;  pos2 = line.indexOf('/', pos1);  listFacePositionIndices  << line.mid(pos1, pos2-pos1).toInt();
            pos1 = pos2 + 1;  pos2 = line.indexOf('/', pos1);  listFaceTextureIndices << line.mid(pos1, pos2-pos1).toInt();
            pos1 = pos2 + 1;  pos2 = line.count();             listFaceNormalIndices  << line.mid(pos1, pos2-pos1).toInt();
*/

            int  p1,p2,p3, t1,t2,t3, n1,n2,n3;
                              pos2 = line.indexOf('/', pos1);  p1 = line.mid(pos1, pos2-pos1).toInt();
            pos1 = pos2 + 1;  pos2 = line.indexOf('/', pos1);  t1 = line.mid(pos1, pos2-pos1).toInt();
            pos1 = pos2 + 1;  pos2 = line.indexOf(' ', pos1);  n1 = line.mid(pos1, pos2-pos1).toInt();

            pos1 = pos2 + 1;  pos2 = line.indexOf('/', pos1);  p2 = line.mid(pos1, pos2-pos1).toInt();
            pos1 = pos2 + 1;  pos2 = line.indexOf('/', pos1);  t2 = line.mid(pos1, pos2-pos1).toInt();
            pos1 = pos2 + 1;  pos2 = line.indexOf(' ', pos1);  n2 = line.mid(pos1, pos2-pos1).toInt();

            pos1 = pos2 + 1;  pos2 = line.indexOf('/', pos1);  p3 = line.mid(pos1, pos2-pos1).toInt();
            pos1 = pos2 + 1;  pos2 = line.indexOf('/', pos1);  t3 = line.mid(pos1, pos2-pos1).toInt();
            pos1 = pos2 + 1;  pos2 = line.count();             n3 = line.mid(pos1, pos2-pos1).toInt();

            listFacePositionIndices << p1;   listFacePositionIndices << p2;   listFacePositionIndices << p3;
            listFaceTextureIndices  << t1;   listFaceTextureIndices <<  t2;   listFaceTextureIndices  << t3;
            listFaceNormalIndices   << n1;   listFaceNormalIndices <<   n2;   listFaceNormalIndices   << n3;

//            listFacePositionIndices << p1;   listFacePositionIndices << p3;   listFacePositionIndices << p2;
//            listFaceTextureIndices  << t1;   listFaceTextureIndices <<  t3;   listFaceTextureIndices  << t2;
//            listFaceNormalIndices   << n1;   listFaceNormalIndices <<   n3;   listFaceNormalIndices   << n2;

//+            listFacePositionIndices << p2;   listFacePositionIndices << p3;   listFacePositionIndices << p1;
//+            listFaceTextureIndices  << t2;   listFaceTextureIndices <<  t3;   listFaceTextureIndices  << t1;
//+            listFaceNormalIndices   << n2;   listFaceNormalIndices <<   n3;   listFaceNormalIndices   << n1;

//            listFacePositionIndices << p2;   listFacePositionIndices << p1;   listFacePositionIndices << p3;
//            listFaceTextureIndices  << t2;   listFaceTextureIndices <<  t1;   listFaceTextureIndices  << t3;
//            listFaceNormalIndices   << n2;   listFaceNormalIndices <<   n1;   listFaceNormalIndices   << n3;

//            listFacePositionIndices << p3;   listFacePositionIndices << p1;   listFacePositionIndices << p2;
//            listFaceTextureIndices  << t3;   listFaceTextureIndices <<  t1;   listFaceTextureIndices  << t2;
//            listFaceNormalIndices   << n3;   listFaceNormalIndices <<   n1;   listFaceNormalIndices   << n2;

//            listFacePositionIndices << p3;   listFacePositionIndices << p2;   listFacePositionIndices << p1;
//            listFaceTextureIndices  << t3;   listFaceTextureIndices <<  t2;   listFaceTextureIndices  << t1;
//            listFaceNormalIndices   << n3;   listFaceNormalIndices <<   n2;   listFaceNormalIndices   << n1;

          }
        }
        break;
      default:
        ;
    }
  }
  fileIn.close();

//s.sprintf("listVertices.count()=%d,  listTextures.count()=%d,  listIndices.count()=%d",
//           listVertices.count(),     listTextures.count(),     listIndices.count());
//msgBox.setText(s);   msgBox.exec();

  float fm = 0.0;
  for(int i=0; i < listPositions.count(); i++) {  //         fm = 359.85657
    fm = qMax(fm, qAbs(listPositions.at(i).x()));
    fm = qMax(fm, qAbs(listPositions.at(i).y()));
    fm = qMax(fm, qAbs(listPositions.at(i).z()));
  }

  for(int i = 0; i < listFacePositionIndices.count(); i++) {
    listFacePositionIndices.replace(i, listFacePositionIndices.at(i)-1);
    listFaceTextureIndices.replace(i, listFaceTextureIndices.at(i)-1);
    listFaceNormalIndices.replace(i, listFaceNormalIndices.at(i)-1);
  }

//s.sprintf("fm=%.5f", fm);  msgBox.setText(s);   msgBox.exec();
/*
//  QVector3D position[495];// = new QVector3D[listVertices.count()];   //5.obj
//  QVector3D position[502];// = new QVector3D[listVertices.count()];   //6.obj
  QVector3D position[490];// = new QVector3D[listVertices.count()];   //7.obj
//  QVector3D position[495];// = new QVector3D[listVertices.count()];   //9.obj
  for(int i=0; i<listVertices.count(); i++) { position[i] = listVertices.at(i);  position[i] /= fm; }

//  QVector3D texCoord[505];// = new QVector3D[listTextures.count()];   //5.obj
//  QVector3D texCoord[517];// = new QVector3D[listTextures.count()];   //6.obj
//  QVector3D texCoord[505];// = new QVector3D[listTextures.count()];   //7.obj
//  QVector3D texCoord[505];// = new QVector3D[listTextures.count()];   //9.obj
//  for(int i=0; i<listTextures.count(); i++) { texCoord[i] = listTextures.at(i);
  QVector3D texCoord[490];// = new QVector3D[listTextures.count()];   //7.obj
  for(int i=0; i<490; i++) { //texCoord[i] = listTextures.at(i);
    texCoord[i].setX(0.5); texCoord[i].setY(0.5); //texCoord[i].setZ(1.0);
  }
*/

  QList<int> listFacePositionIndicesDiff;
  QList<int> listFaceTextureIndicesDiff;
  QList<int> listFaceNormalIndicesDiff;
  listFacePositionIndicesDiff << listFacePositionIndices.at(0);
  listFaceTextureIndicesDiff << listFaceTextureIndices.at(0);
  listFaceNormalIndicesDiff << listFaceNormalIndices.at(0);

  QList<int> listVertexIndices;
  listVertexIndices << 0;
  int j;  bool isHas;
  for(int i = 1; i < listFacePositionIndices.count(); i++) {
    isHas = false;
    for(j = 0; j < listFacePositionIndicesDiff.count(); j++) {
      if(listFacePositionIndices.at(i) == listFacePositionIndicesDiff.at(j) &&
         listFaceTextureIndices.at(i) == listFaceTextureIndicesDiff.at(j) &&
         listFaceNormalIndices.at(i) == listFaceNormalIndicesDiff.at(j)) {
        isHas = true;
        break;
      }
    }
    if(!isHas) {
      listFacePositionIndicesDiff << listFacePositionIndices.at(i);
      listFaceTextureIndicesDiff << listFaceTextureIndices.at(i);
      listFaceNormalIndicesDiff << listFaceNormalIndices.at(i);
    }
    listVertexIndices << j;
  }
  CountVertexIndices = listVertexIndices.count();
/*
//QString s1 = "listPositions\n\n";
//QString s1 = "listTextures\n\n";
//QString s1 = "listNormals\n\n";
QString s1;
QString s0;

s1.sprintf("listVertexIndices.count()=%d\n\n", listVertexIndices.count());
for(int i = 0; i < listVertexIndices.count(); i++) {
  s0.sprintf("%d  %d", i, listVertexIndices.at(i));
  s1 += s0;  s1 += '\n';
}
msgBox.setText(s1);   msgBox.exec();
return;
*/
/*
QString s1;
QString s0;
//for(int i = 0; i < listPositions.count(); i++) {
//for(int i = 0; i < listTextures.count(); i++) {
//for(int i = 0; i < listNormals.count(); i++) {
//for(int i = 0; i < listFacePositionIndices.count(); i++) {
s1.sprintf("listFacePositionIndicesDiff.count()=%d\n\n", listFacePositionIndicesDiff.count());
for(int i = 0; i < listFacePositionIndicesDiff.count(); i++) {
//  s0.sprintf("x()=%.5f;  y()=%.5f;  z()=%.5f",
//              listPositions.at(i).x(),  listPositions.at(i).y(),  listPositions.at(i).z());
//              listTextures.at(i).x(),  listTextures.at(i).y(),  listTextures.at(i).z());
//              listNormals.at(i).x(),  listNormals.at(i).y(),  listNormals.at(i).z());

//  s0.sprintf("%d/%d/%d", listFacePositionIndices.at(i), listFaceTextureIndices.at(i), listFaceNormalIndices.at(i));
  s0.sprintf("%d  %d/%d/%d", i, listFacePositionIndicesDiff.at(i), listFaceTextureIndicesDiff.at(i), listFaceNormalIndicesDiff.at(i));
  s1 += s0;  s1 += '\n';
}
msgBox.setText(s1);   msgBox.exec();
return;
*/

//QString s1;
//QString s0;

//++  VertexData vertices[countIndicesDiff]; //  countIndicesDiff == listFacePositionIndicesDiff.count()
  VertexData* vertices = new VertexData[listFacePositionIndicesDiff.count()]; //  countIndicesDiff == listFacePositionIndicesDiff.count()

  for(int i = 0; i < listFacePositionIndicesDiff.count(); i++) {
/*
    vertices[i].position = listPositions.at(i);
//    vertices[i].texCoord = listTextures.at(i);
    vertices[i].texCoord.setX(listTextures.at(i).x());  vertices[i].texCoord.setY(listTextures.at(i).y());
    vertices[i].normal = listNormals.at(i);
*/
    vertices[i].position = listPositions.at(listFacePositionIndicesDiff.at(i)); //-1)
    vertices[i].position /= fm;
    vertices[i].normal = listNormals.at(listFaceNormalIndicesDiff.at(i)); //-1);
//    vertices[i].texCoord = listTextures.at(listFaceTextureIndicesDiff.at(i));
    vertices[i].texCoord.setX(qMin(listTextures.at(listFaceTextureIndicesDiff.at(i)).x(), 1.0f));
    vertices[i].texCoord.setY(qMin(listTextures.at(listFaceTextureIndicesDiff.at(i)).y(), 1.0f));
//    vertices[i].texCoord.setX(0.5);   vertices[i].texCoord.setY(0.5);
//    vertices[i].texCoord.setX((i*1.0)/(listFaceTextureIndicesDiff.count()-1));  vertices[i].texCoord.setY((i*1.0)/(listFaceTextureIndicesDiff.count()-1)); // vertices[i].texCoord.setZ(1.0);

//s0.sprintf("%d  %.5f %.5f %.5f", i, vertices[i].position.x(),vertices[i].position.y(),vertices[i].position.z());
//s1 += s0;  s1 += '\n';
  }
//msgBox.setText(s1);   msgBox.exec();
//return;


/*
  VertexData vertices[countvertices];
  for(int i=0; i<countvertices; i++) {
    vertices[i].position = listVertices.at(i);  vertices[i].position /= (2.0*fm); // vertices[i].position.setZ(-vertices[i].position.z());
//    vertices[i].texCoord.setX(0.5);  vertices[i].texCoord.setY(0.5); // vertices[i].texCoord.setZ(1.0);
    vertices[i].texCoord.setX((i*1.0)/(countvertices-1));  vertices[i].texCoord.setY((i*1.0)/(countvertices-1)); // vertices[i].texCoord.setZ(1.0);

//vertex[i] = vertices[i].position;
  }
//return;
*/

//  GLushort indices[2832];// = new GLushort[listIndices.count()];   //5.obj
//  GLushort indices[2850];// = new GLushort[listIndices.count()];   //6.obj
//  GLushort indices[2832];// = new GLushort[listIndices.count()];   //7.obj
//  GLushort indices[2832];// = new GLushort[listIndices.count()];   //9.obj
//++  GLushort indices[countindices]; // = new GLushort[listIndices.count()];
//++  for(int i=0; i < listVertexIndices.count(); i++) { indices[i] = listVertexIndices.at(i); }
  GLushort* indices = new GLushort[CountVertexIndices];
  for(int i=0; i < CountVertexIndices; i++) { indices[i] = listVertexIndices.at(i); }
//  for(int i=0; i<countindices; i++) { indices[i] = listIndices.at(i)-1; }


//s.sprintf("indices[0]=%d, indices[1]=%d, indices[2]=%d, indices[3]=%d, indices[4]=%d, indices[5]=%d, indices[6]=%d, indices[7]=%d, indices[8]=%d",
//           indices[0],    indices[1],    indices[2],    indices[3],    indices[4],    indices[5],    indices[6],    indices[7],    indices[8]);
//s.sprintf("indices[countindices-3]=%d, indices[countindices-2]=%d, indices[countindices-1]=%d",
//           indices[countindices-3],    indices[countindices-2],    indices[countindices-1]);
//msgBox.setText(s);   msgBox.exec();
//s.sprintf("vertices[countvertices-3].position.x()=%.3f, vertices[countvertices-3].position.y()=%.3f, vertices[countvertices-3].position.z()=%.3f\n"
//          "vertices[countvertices-2].position.x()=%.3f, vertices[countvertices-2].position.y()=%.3f, vertices[countvertices-2].position.z()=%.3f\n"
//          "vertices[countvertices-1].position.x()=%.3f, vertices[countvertices-1].position.y()=%.3f, vertices[countvertices-1].position.z()=%.3f",
//           vertices[countvertices-3].position.x()*fm, vertices[countvertices-3].position.y()*fm, vertices[countvertices-3].position.z()*fm,
//           vertices[countvertices-2].position.x()*fm, vertices[countvertices-2].position.y()*fm, vertices[countvertices-2].position.z()*fm,
//           vertices[countvertices-1].position.x()*fm, vertices[countvertices-1].position.y()*fm, vertices[countvertices-1].position.z()*fm);
//msgBox.setText(s);   msgBox.exec();

//--------
/*++
QFile fileOut(fileNameOut);
if(!fileOut.open(QIODevice::WriteOnly | QIODevice::Text)) {
  QMessageBox msgBox; msgBox.setText("Problem file \""+fileNameOut+"\"");   msgBox.exec();
  return;
}
QTextStream out(&fileOut); // QString line;  QChar qc; char c;  int pos1,pos2;  QString s;  QVector3D v3D;
QString sout;

sout.sprintf("listFacePositionIndicesDiff.count()=%d\n\n", listFacePositionIndicesDiff.count());
out << sout;
for(int i = 0; i < listFacePositionIndicesDiff.count(); i++) {
  sout.sprintf("%d   %.5f %.5f %.5f   %.5f %.5f %.5f   %.5f %.5f\n",
                 i,  vertices[i].position.x(),  vertices[i].position.y(),  vertices[i].position.z(),
                     vertices[i].normal.x(),    vertices[i].normal.y(),    vertices[i].normal.z(),
                     vertices[i].texCoord.x(),  vertices[i].texCoord.y()); //,  listTextures.at(i).z());
  out << sout;
}

sout.sprintf("\n\nlistFacePositionIndicesDiff.count()=%d\n\n", listFacePositionIndicesDiff.count());
out << sout;
for(int i = 0; i < listFacePositionIndicesDiff.count(); i++) {
//  sout.sprintf("%d/%d/%d", listFacePositionIndices.at(i), listFaceTextureIndices.at(i), listFaceNormalIndices.at(i));
  sout.sprintf("%d  %d/%d/%d\n", i, listFacePositionIndicesDiff.at(i), listFaceTextureIndicesDiff.at(i), listFaceNormalIndicesDiff.at(i));
  out << sout;
}
sout.sprintf("\n\n\nCountVertexIndices=%d\n\n", CountVertexIndices);
//  sout.sprintf("\n\n\nlistVertexIndices.count()=%d\n\n", listVertexIndices.count());
out << sout;
//+  for(int i=0; i<countindices; i++) {
for(int i=0; i < CountVertexIndices; i++) {
  sout.sprintf("%d  %d\n", i, indices[i]);
  out << sout;
}
out.flush();  fileOut.close();
//return;
*/
//--------

    // Transfer vertex data to VBO 0
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
//-    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(VertexData), vertices, GL_STATIC_DRAW);
//++    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, listFacePositionIndicesDiff.count()*sizeof(VertexData), vertices, GL_STATIC_DRAW);
//glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

  delete[] vertices;


    // Transfer index data to VBO 1
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
//-    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 34 * sizeof(GLushort), indices, GL_STATIC_DRAW);
//++    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, CountVertexIndices*sizeof(GLushort), indices, GL_STATIC_DRAW);

  delete[] indices;


/*
//! [1]
    // Transfer vertex data to VBO 0
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]);
glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//! [1]
*/
//----
//s.sprintf("sizeof(vertices)=%d,  910*sizeof(VertexData)=%d,   sizeof(indices)=%d,  CountVertexIndices*sizeof(GLushort)=%d",
//           sizeof(vertices),     910*sizeof(VertexData),      sizeof(indices),     CountVertexIndices*sizeof(GLushort));
//msgBox.setText(s);   msgBox.exec();

//++  CountIndices = sizeof(indices)/sizeof(GLushort);
//  delete[] indices;

//  delete[] position;  delete[] texCoord;  delete[] indices;

}
//--------------------------------------------------------------------------------------------
//-void GeometryEngine::drawCubeGeometry(QGLShaderProgram *program)
void MEkranoplan::Draw(QOpenGLShaderProgram* pShaderProgram)
{
    // Tell OpenGL which VBOs to use
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = pShaderProgram->attributeLocation("a_position");
    pShaderProgram->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);
//glVertexPointer(3, GL_FLOAT, 0, vertex );

//--
// Offset for normal coordinate
  offset += sizeof(QVector3D);

// Tell OpenGL programmable pipeline how to locate normal position data
  int normalLocation = pShaderProgram->attributeLocation("a_normal");
  pShaderProgram->enableAttributeArray(normalLocation);
  glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);
//--

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = pShaderProgram->attributeLocation("a_texcoord");
    pShaderProgram->enableAttributeArray(texcoordLocation);
    glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);
//    glVertexAttribPointer(texcoordLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

/*

    // Tell OpenGL which VBOs to use
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);

    // Offset for position
//-    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = pShaderProgram->attributeLocation("a_position");
    pShaderProgram->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), 0);

    // Offset for texture coordinate
//-    offset += sizeof(QVector3D);

glBindBuffer(GL_ARRAY_BUFFER, vboIds[1]);
    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = pShaderProgram->attributeLocation("a_texcoord");
    pShaderProgram->enableAttributeArray(texcoordLocation);
//-    glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);
    glVertexAttribPointer(texcoordLocation, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), 0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[2]);
*/

    // Draw cube geometry using indices from VBO 1
//-    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
//    glDrawElements(GL_TRIANGLE_STRIP, CountIndices, GL_UNSIGNED_SHORT, 0);
  glDrawElements(GL_TRIANGLES, CountVertexIndices, GL_UNSIGNED_SHORT, 0);
//+  glDrawArrays(GL_TRIANGLES, 0, CountIndices);

//    glDrawElements(GL_TRIANGLE_FAN, CountElements, GL_UNSIGNED_SHORT, 0);
//    glDrawElements(GL_TRIANGLE_FAN, CountElements, GL_UNSIGNED_BYTE, 0);
//    glDrawElements(GL_TRIANGLE_STRIP, CountElements, GL_UNSIGNED_BYTE, 0);
//    glDrawElements(GL_TRIANGLE_STRIP, CountElements, GL_SHORT, 0);
//    glDrawElements(GL_TRIANGLE_STRIP, CountElements, GL_BYTE, 0);
//    glDrawElements(GL_TRIANGLE_STRIP, CountElements, GL_FLOAT, 0);

//QMessageBox msgBox; msgBox.setText("void MEkranoplan::Draw(QOpenGLShaderProgram* pShaderProgram)");   msgBox.exec();

}
//--------------------------------------------------------------------------------------------
