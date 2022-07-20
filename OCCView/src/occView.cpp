#include "occview.h"
#include <BRepPrimAPI_MakeBox.hxx>


OccView::OccView(QWidget *parent) :
    QWidget(parent)
{
    if(m_context.IsNull())//若交互式上下文为空
    {
        //此对象提供与X server的连接，在Windows和Mac OS中不起作用
        Handle(Aspect_DisplayConnection) m_display_connection=new Aspect_DisplayConnection();
       //创建OpenGl图形驱动
        if(m_graphic_driver.IsNull())
        {
            m_graphic_driver=new OpenGl_GraphicDriver(m_display_connection);
        }
        //获取QWidget的窗口系统标识符
        WId window_handle=(WId)winId();
        // 创建Windows NT 窗口
        Handle(WNT_Window) wind=new WNT_Window((Aspect_Handle)window_handle);
       //创建3D查看器
        m_viewer=new V3d_Viewer(m_graphic_driver);
        //创建视图
        m_view=m_viewer->CreateView();
        m_view->SetWindow(wind);
        //打开窗口
        if(!wind->IsMapped())
        {
            wind->Map();
        }
        //创建交互式上下文
        m_context=new AIS_InteractiveContext(m_viewer);
        //设置查看器的光照
        m_viewer->SetDefaultLights();
        //打开背景灯光
        m_viewer->SetLightOn();
        //设置视图的背景颜色为黑色
        m_view->SetBackgroundColor(Quantity_NOC_BLACK);
        m_view->MustBeResized();;
        //显示直角坐标系，可以配置在窗口显示位置、文字颜色、大小、样式
        m_view->TriedronDisplay(Aspect_TOTP_LEFT_LOWER,Quantity_NOC_GOLD,0.08,V3d_ZBUFFER);
       //设置交互式上下文的显示模式
        m_context->SetDisplayMode(AIS_Shaded,Standard_True);
        //设置模型高亮风格
        Handle(Prs3d_Drawer) t_hilight_style = m_context->HighlightStyle();
        t_hilight_style->SetMethod(Aspect_TOHM_COLOR);  // 颜色显示方式
        t_hilight_style->SetColor(Quantity_NOC_LIGHTYELLOW);    // 设置高亮颜色
        t_hilight_style->SetDisplayMode(1); // 整体高亮
        t_hilight_style->SetTransparency(0.2f); // 设置透明度
 
        // 设置选择模型的风格
        Handle(Prs3d_Drawer) t_select_style = m_context->SelectionStyle();  // 获取选择风格
        t_select_style->SetMethod(Aspect_TOHM_COLOR);  // 颜色显示方式
        t_select_style->SetColor(Quantity_NOC_LIGHTSEAGREEN);   // 设置选择后颜色
        t_select_style->SetDisplayMode(1); // 整体高亮
        t_select_style->SetTransparency(0.4f); // 设置透明度
    }
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_NoSystemBackground);
    setBackgroundRole(QPalette::NoRole);
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);//设置鼠标跟踪

    TopoDS_Shape box = BRepPrimAPI_MakeBox(10, 10, 10);
    Handle(AIS_Shape) shapess = new AIS_Shape(box);
    m_context->Display(shapess, Standard_True);
    m_view->FitAll();

}

OccView::~OccView()
{
}

 
void OccView::resizeEvent(QResizeEvent *)
{
   if(!m_view.IsNull())
   {
       m_view->MustBeResized();
   }
}


void OccView::mouseReleaseEvent(QMouseEvent *event)
{
	m_current_mode = CurAction3d_Nothing;
	m_context->MoveTo(event->pos().x(), event->pos().y(), m_view, Standard_True);
}

void OccView::wheelEvent(QWheelEvent *event)
{
	m_view->StartZoomAtPoint(event->pos().x(), event->pos().y());
	m_view->ZoomAtPoint(0, 0, event->angleDelta().y(), 0); //执行缩放
}

void OccView::mousePressEvent(QMouseEvent *event)
{
	if (m_current_mode== CurAction3d_DynamicPanning)//平移
	{
		m_view->Pan(event->pos().x() - m_x_max, m_y_max - event->pos().y());
		m_x_max = event->pos().x();
		m_y_max = event->pos().y();
	}
	else if (event->buttons() & Qt::MidButton)  //旋转
	{
		m_current_mode = CurAction3d_DynamicRotation;
		m_view->StartRotation(event->pos().x(), event->pos().y());
	}
}

void OccView::mouseMoveEvent(QMouseEvent *event)
{
	if ((event->buttons()&Qt::LeftButton) && (event->buttons()&Qt::RightButton))
	{
		// 鼠标左右键齐按：执行平移
		m_view->Pan(event->pos().x() - m_x_max, m_y_max - event->pos().y());
		m_x_max = event->x();
		m_y_max = event->y();
	}
	else if (event->buttons()&Qt::MidButton)
	{
		// 鼠标滚轮键
		if (qApp->keyboardModifiers() == Qt::ShiftModifier)    // 且按下Shift键
		{
			// 鼠标滚轮键：执行平移
			m_view->Pan(event->pos().x() - m_x_max, m_y_max - event->pos().y());
			m_x_max = event->x();
			m_y_max = event->y();
		}
		else
		{
			// 鼠标滚轮键：执行旋转
			m_view->Rotation(event->x(), event->y());
		}
	}
	else
	{
		// 将鼠标位置传递到交互环境
		m_context->MoveTo(event->pos().x(), event->pos().y(), m_view, Standard_True);
	}
}


