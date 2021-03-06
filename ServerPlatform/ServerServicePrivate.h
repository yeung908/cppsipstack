/* 
 * Copyright (C) 2012 Yee Young Han <websearch@naver.com> (http://blog.naver.com/websearch)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */

#ifndef _SERVER_SERVICE_PRIVATE_H_
#define _SERVER_SERVICE_PRIVATE_H_

/**
 * @defgroup ServerPlatform ServerPlatform
 * 서비스 개발 라이브러리
 */

#include "ServerService.h"

// InstallService.h
bool InstallService( );
bool UninstallService( );

// ServerService.h
void ServiceStart();

// ServerSignal.h
void LastMethod( int sig );

// ServerMain.cpp
extern CServerService gclsService;
extern ServerFunc gpServerFunc;

#endif
