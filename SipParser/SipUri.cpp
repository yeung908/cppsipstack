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

#include "SipParserDefine.h"
#include "SipUri.h"

CSipUri::CSipUri(void) : m_iPort(0)
{
}

CSipUri::~CSipUri(void)
{
}

int CSipUri::Parse( const char * pszText, int iTextLen )
{
	Clear();
	if( pszText == NULL || iTextLen <= 0 ) return -1;

	int iPos, iCurPos;

	iPos = ParseProtocol( pszText, iTextLen );
	if( iPos == -1 ) return -1;
	iCurPos = iPos;

	iPos = ParseUser( pszText + iCurPos, iTextLen - iCurPos );
	if( iPos > 0 ) iCurPos += iPos;

	iPos = ParseHost( pszText + iCurPos, iTextLen - iCurPos );
	if( iPos == -1 ) return -1;
	iCurPos += iPos;

	while( iCurPos < iTextLen )
	{
		if( pszText[iCurPos] == '?' )
		{
			++iCurPos;
			break;
		}

		if( pszText[iCurPos] == ';' || pszText[iCurPos] == ' ' || pszText[iCurPos] == '\t' )
		{
			++iCurPos;
			continue;
		}

		iPos = ParseSipParameter( m_clsUriParamList, pszText + iCurPos, iTextLen - iCurPos );
		if( iPos == -1 ) return -1;
		iCurPos += iPos;
	}

	while( iCurPos < iTextLen )
	{
		if( pszText[iCurPos] == ' ' || pszText[iCurPos] == '\t' || pszText[iCurPos] == '&'  )
		{
			++iCurPos;
			continue;
		}

		iPos = ParseSipParameter( m_clsHeaderList, pszText + iCurPos, iTextLen - iCurPos );
		if( iPos == -1 ) return -1;
		iCurPos += iPos;
	}

	return iCurPos;
}

int CSipUri::ToString( char * pszText, int iTextSize )
{
	if( pszText == NULL || iTextSize <= 0 ) return -1;
	if( m_strProtocol.empty() || m_strHost.empty() ) return 0;

	int iLen = 0, iPos;

	iLen += snprintf( pszText + iLen, iTextSize - iLen, "%s:", m_strProtocol.c_str() );

	if( m_strUser.empty() == false )
	{
		iLen += snprintf( pszText + iLen, iTextSize - iLen, "%s@", m_strUser.c_str() );
	}

	iLen += snprintf( pszText + iLen, iTextSize - iLen, "%s", m_strHost.c_str() );

	if( m_iPort > 0 )
	{
		iLen += snprintf( pszText + iLen, iTextSize - iLen, ":%d", m_iPort );
	}

	iPos = MakeSipParameterString( m_clsUriParamList, pszText + iLen, iTextSize - iLen );
	if( iPos == -1 ) return -1;
	iLen += iPos;

	SIP_PARAMETER_LIST::iterator	itList;

	for( itList = m_clsHeaderList.begin(); itList != m_clsHeaderList.end(); ++itList )
	{
		if( iLen >= iTextSize ) return -1;

		if( itList == m_clsHeaderList.begin() )
		{
			pszText[iLen++] = '?';
		}
		else
		{
			pszText[iLen++] = '&';
		}

		iPos = itList->ToString( pszText + iLen, iTextSize - iLen );
		if( iPos == -1 ) return -1;
		iLen += iPos;
	}

	return iLen;
}

void CSipUri::Clear()
{
	m_strProtocol.clear();
	m_strUser.clear();
	m_strHost.clear();
	m_iPort = 0;
	m_clsUriParamList.clear();
	m_clsHeaderList.clear();
}

bool CSipUri::Empty()
{
	if( m_strProtocol.empty() || m_strHost.empty() ) return true;

	return false;
}

int CSipUri::ParseProtocol( const char * pszText, int iTextLen )
{
	for( int iPos = 0; iPos < iTextLen; ++iPos )
	{
		if( pszText[iPos] == ':' )
		{
			m_strProtocol.append( pszText, iPos );
			return iPos + 1;
		}
	}

	return -1;
}

int CSipUri::ParseUser( const char * pszText, int iTextLen )
{
	for( int iPos = 0; iPos < iTextLen; ++iPos )
	{
		if( pszText[iPos] == '@' )
		{
			m_strUser.append( pszText, iPos );
			return iPos + 1;
		}
	}

	return -1;
}

int CSipUri::ParseHost( const char * pszText, int iTextLen )
{
	int iPos, iPortPos = -1;

	for( iPos = 0; iPos < iTextLen; ++iPos )
	{
		if( pszText[iPos] == ':' )
		{
			m_strHost.append( pszText, iPos );
			iPortPos = iPos + 1;
		}
		else if( pszText[iPos] == ';' || pszText[iPos] == '?' )
		{
			break;
		}
	}

	if( iPortPos == -1 )
	{
		if( iPos > 0 )
		{
			m_strHost.append( pszText, iPos );
			return iPos;
		}
	}
	else
	{
		if( iPortPos < iPos )
		{
			std::string strTemp;

			strTemp.append( pszText + iPortPos, iPos - iPortPos );
			m_iPort = atoi( strTemp.c_str() );
		}

		return iPos;
	}

	return -1;
}
