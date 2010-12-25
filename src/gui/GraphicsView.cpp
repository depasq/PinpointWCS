/*
 *  PinpointWCS is developed by the Chandra X-ray Center
 *  Education and Public Outreach Group
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <QDebug>
#include "GraphicsView.h"
#include "GraphicsScene.h"
#include "math.h"
//#include <QGLWidget>

GraphicsView::GraphicsView(QWidget *parent)
: QGraphicsView(parent)
{	
	// Set up view port to use OpenGL
//	setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
//	setViewportUpdateMode(FullViewportUpdate);
	
	// Set attributes from QGraphicsView
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setRenderHint(QPainter::Antialiasing);
	setDragMode(NoDrag);
	setTransformationAnchor(AnchorViewCenter);
//	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
	
	viewport()->setMouseTracking(true);
	
	// Adjust the background color
	setBackgroundBrush(QBrush(QColor(30, 30, 30)));
	
	// Set initial conditions
	rotateFactor = 0;
}

GraphicsView::~GraphicsView() {}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
	// Emit signal with size information
	QSize s = size();
	emit objectResized(s);
	
	// Call parent function
	QWidget::resizeEvent(event);
}


void GraphicsView::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Space)
		setDragMode(ScrollHandDrag);
	else if(event->modifiers() == Qt::NoModifier && event->key() == Qt::Key_R)
	{
		rotate(5);
		rotateFactor = (rotateFactor + 5) % 360;
	}
	else if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_R)
	{
		rotate(-5);
		rotateFactor = (rotateFactor - 5) % 360;
	}
	QGraphicsView::keyPressEvent(event);
//	qDebug() << transform().determinant();
}

void GraphicsView::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Space)
		setDragMode(NoDrag);
	QGraphicsView::keyReleaseEvent(event);
}


void GraphicsView::enterEvent(QEvent *event)
{
	setDragMode(QGraphicsView::NoDrag);
	setFocus();
}

void GraphicsView::leaveEvent(QEvent *event)
{
	setDragMode(QGraphicsView::NoDrag);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
	scaleView(pow((double)2, event->delta() / 240.0));
}

void GraphicsView::scaleView(qreal scaleFactor)
{
	qreal factor = matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
	if (factor < MINZOOM || factor > MAXZOOM)
		return;	
	scale(scaleFactor, scaleFactor);
}

float GraphicsView::scaling()
{
	// Get transform matrix
	QTransform t = transform();
	
	// Undo any rotations
	t.rotate(-rotateFactor);
	
	return t.m11();
}