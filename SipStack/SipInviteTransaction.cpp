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

#include "SipInviteTransaction.h"
#include "SipDeleteQueue.h"
#include "MemoryDebug.h"

/**
 * @ingroup SipStack
 * @brief 持失切
 */
CSipInviteTransaction::CSipInviteTransaction() : m_pclsRequest(NULL), m_pclsResponse(NULL), m_pclsAck(NULL), m_iReSendCount(0), m_iStatusCode(0)
{
	memset( &m_sttStartTime, 0, sizeof(m_sttStartTime) );
	memset( &m_sttStopTime, 0, sizeof(m_sttStopTime) );
	memset( &m_sttRingTime, 0, sizeof(m_sttRingTime) );
}

/**
 * @ingroup SipStack
 * @brief 社瑚切
 */
CSipInviteTransaction::~CSipInviteTransaction()
{
	if( m_pclsRequest ) gclsSipDeleteQueue.Insert( m_pclsRequest );
	if( m_pclsResponse ) gclsSipDeleteQueue.Insert( m_pclsResponse );
	if( m_pclsAck ) gclsSipDeleteQueue.Insert( m_pclsAck );
}
