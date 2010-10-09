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

#ifndef COORDINATE_DELEGATE_H
#define COORDINATE_DELEGATE_H

#include <QItemDelegate>
#include "GraphicsScene.h"

class CoordinateDelegate : public QItemDelegate
{
	Q_OBJECT
	
public:
	CoordinateDelegate(GraphicsScene *s1, GraphicsScene *s2, QObject *parent = 0);
	QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
	
signals:
	void itemMoved(GraphicsScene *s, const QPointF &newPosition, const QPointF &oldPosition) const;
	
private:
	GraphicsScene *fitsScene;
	GraphicsScene *epoScene;
	
};

#endif
