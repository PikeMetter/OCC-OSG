#ifndef OCCVIEW_H
#define OCCVIEW_H
 //Qt
#include <QWidget>
#include <QWidget>
#include<QDebug>
#include<QVector>
#include<QpointF>
#include <QMouseEvent>
#include <QApplication>

//OCC
#include<AIS_InteractiveContext.hxx>
#include<OpenGl_GraphicDriver.hxx>
#include<V3d_View.hxx>
#include<V3d_Viewer.hxx>
#include<WNT_Window.hxx>
#include<Quantity_NameOfColor.hxx>
#include<gp_Pnt2d.hxx>
#include<TopoDS_Shape.hxx>
#include<ProjLib.hxx>
#include<ElSLib.hxx>
#include<AIS_Manipulator.hxx>
#include<TopoDS_Face.hxx>
#include<BRepBuilderAPI_MakeFace.hxx>
#include<AIS_Shape.hxx>
 

class OccView : public QWidget 
{
    Q_OBJECT
 
public:
    explicit OccView(QWidget *parent = 0);

    ~OccView();

private:
	Handle(V3d_View) m_view;
    Handle(AIS_InteractiveContext) m_context;
    Handle(V3d_Viewer) m_viewer;
    Handle(Graphic3d_GraphicDriver) m_graphic_driver;
protected:
    void resizeEvent(QResizeEvent *event);

	//!��д���̰��������¼�
	//void keyPressEvent(QKeyEvent *event);
	//!��д���̰����ͷ��¼�
	//void keyReleaseEvent(QKeyEvent *event);
	//!��д��갴�������¼�
	void mousePressEvent(QMouseEvent *event);
	//!��д��갴���ͷ��¼�
	void mouseReleaseEvent(QMouseEvent *event);
	//!��д����ƶ��¼�
	void mouseMoveEvent(QMouseEvent *event);
	//!��д�������¼�
	void wheelEvent(QWheelEvent *event);
	//!��ά����ת��ģʽ
	enum CurrentAction3d
	{
		CurAction3d_Nothing,
		CurAction3d_DynamicPanning, //ƽ��
		CurAction3d_DynamicZooming, //����
		CurAction3d_DynamicRotation //��ת
	};


private:
	Standard_Integer m_x_max;    //!��¼���ƽ������X
	Standard_Integer m_y_max;    //!��¼���ƽ������Y
	CurrentAction3d m_current_mode; //!��ά����ת��ģʽ
	bool m_shift_key_pressed;   //!��¼Shift���Ƿ񱻰���
};
 
#endif // OCCVIEW_H