// 
// QChewingTest/MainWindow.hpp
//
// Copyright (C) 2013  Inori Sakura <inorindesu@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or (at
// your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// 

#include <QtGui>
#include "chewing.h"

class MainWindow: public QMainWindow
{
  Q_OBJECT
private:
  ChewingContext* _ct;
  QLabel* _lblChewing;
  QLabel* _lblBuffer;
  QLabel* _lblCommit;
  QLabel* _lblAux;
  QLineEdit* _txtLine;
protected:
  void keyPressEvent(QKeyEvent* evt);

public:
  MainWindow();
  ~MainWindow();
};
