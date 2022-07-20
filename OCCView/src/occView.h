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

	//!覆写键盘按键按下事件
	//void keyPressEvent(QKeyEvent *event);
	//!覆写键盘按键释放事件
	//void keyReleaseEvent(QKeyEvent *event);
	//!覆写鼠标按键按下事件
	void mousePressEvent(QMouseEvent *event);
	//!覆写鼠标按键释放事件
	void mouseReleaseEvent(QMouseEvent *event);
	//!覆写鼠标移动事件
	void mouseMoveEvent(QMouseEvent *event);
	//!覆写鼠标滚轮事件
	void wheelEvent(QWheelEvent *event);
	//!三维场景转换模式
	enum CurrentAction3d
	{
		CurAction3d_Nothing,
		CurAction3d_DynamicPanning, //平移
		CurAction3d_DynamicZooming, //缩放
		CurAction3d_DynamicRotation //旋转
	};


private:
	Standard_Integer m_x_max;    //!记录鼠标平移坐标X
	Standard_Integer m_y_max;    //!记录鼠标平移坐标Y
	CurrentAction3d m_current_mode; //!三维场景转换模式
	bool m_shift_key_pressed;   //!记录Shift键是否被按下
};
 
#endif // OCCVIEW_H