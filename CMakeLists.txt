# 
# QChewingTest/CMakeLists.txt
#
# Copyright (C) 2013  Inori Sakura <inorindesu@gmail.com>
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or (at
# your option) any later version.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# 

project(QChewingTest)

cmake_minimum_required(VERSION 2.4.0)

find_package(Qt4 REQUIRED)

# libchewing headers should be found in
# ${CHEWING_ROOT}/include/chewing
#
# libchewing.a or libchewing.so should be found in 
# ${CHEWING_ROOT}/lib or ${CHEWING_ROOT}/lib64
set(CHEWING_ROOT /usr)

include_directories(${QT_INCLUDES} ${CHEWING_ROOT}/include/chewing)
link_directories(${CHEWING_ROOT}/lib ${CHEWING_ROOT}/lib64)

set(SRCS
  main.cpp
  MainWindow.cpp
  )

set(MOC_H
  MainWindow.hpp)

qt4_wrap_cpp(MOC_CPP ${MOC_H})

add_executable(QChewingTest ${SRCS} ${MOC_CPP})

target_link_libraries(QChewingTest ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} chewing)