// 
// QChewingTest/MainWindow.cpp
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

#include "MainWindow.hpp"

MainWindow::MainWindow()
{
  this->_lblChewing = new QLabel();
  this->_lblCommit = new QLabel();
  this->_lblBuffer = new QLabel();
  this->_lblAux = new QLabel();
  this->_lblLine = new QLabel();

  chewing_Init("/usr/share/chewing", ".");
  this->_ct = chewing_new();
  chewing_set_candPerPage(this->_ct, 9);
  chewing_set_maxChiSymbolLen(this->_ct, 20);
  chewing_set_escCleanAllBuf(this->_ct, 1);

  QWidget* container = new QWidget;
  QVBoxLayout* layout = new QVBoxLayout();
  layout->addWidget(new QLabel("Chewing symbol in buffer"));
  layout->addWidget(this->_lblChewing);
  layout->addWidget(new QLabel("Preedit buffer"));
  layout->addWidget(this->_lblBuffer);
  layout->addWidget(new QLabel("Commit output"));
  layout->addWidget(this->_lblCommit);
  layout->addWidget(new QLabel("Aux buffer"));
  layout->addWidget(this->_lblAux);
  layout->addWidget(new QLabel("Final output"));
  layout->addWidget(this->_lblLine);
  container->setLayout(layout);
  this->setCentralWidget(container);
}

MainWindow::~MainWindow()
{
  chewing_delete(this->_ct);
  chewing_Terminate();
}

void MainWindow::keyPressEvent(QKeyEvent* evt)
{
  int key = evt->key();
  if(key >= 0x21 && key <= 0x5a)
    {
      if (key >= 'A' && key <= 'Z')
        key += 'a' - 'A'; // shift to upper case
      chewing_handle_Default(this->_ct, key);
    }
  else if(key == Qt::Key_Space)
    {
      chewing_handle_Space(this->_ct);
    }
  else if(key == Qt::Key_Return) 
    {
      /* key_Enter : the enter key on the keypad... */
      chewing_handle_Enter(this->_ct);
    }
  else if(key == Qt::Key_Backspace)
    {
      /*
       * When there's a text input box (QLineEdit), 
       * Qt::Key_Backspace is consumed by that input box.
       */
      chewing_handle_Backspace(this->_ct);
    }
  else if(key == Qt::Key_Escape)
    {
      chewing_handle_Esc(this->_ct);
    }
  else
    {
      QMainWindow::keyPressEvent(evt);
    }
  int zuin_size = 0;
  char* aux_buf = chewing_aux_String(this->_ct);
  char* zuin_buf = chewing_zuin_String(this->_ct, &zuin_size);
  char* buf_buf = chewing_buffer_String(this->_ct);
  char* com_buf = chewing_commit_String(this->_ct);
  //printf("A|Z|B|C\n%s|%s|%s|%s\n", aux_buf, zuin_buf, buf_buf, com_buf);
  this->_lblChewing->setText(QString::fromUtf8(zuin_buf));
  this->_lblBuffer->setText(QString::fromUtf8(buf_buf));
  QString comString = QString::fromUtf8(com_buf);
  this->_lblAux->setText(QString::fromUtf8(aux_buf));
  if(chewing_commit_Check(this->_ct))
    {
      this->_lblCommit->setText(comString);
      this->_lblLine->setText(this->_lblLine->text() + comString);
    }
  else
    {
      this->_lblCommit->setText("");
    }
  free(aux_buf);
  free(zuin_buf);
  free(buf_buf);
  free(com_buf);
}
