/************************************************************************
	filename: 	CEGUIPropertyHelper.h
	created:	6/7/2004
	author:		Paul D Turner
	
	purpose:	Interface to the PropertyHelper class
*************************************************************************/
/*************************************************************************
    Crazy Eddie's GUI System (http://crayzedsgui.sourceforge.net)
    Copyright (C)2004 Paul D Turner (crayzed@users.sourceforge.net)

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*************************************************************************/
#ifndef _CEGUIPropertyHelper_h_
#define _CEGUIPropertyHelper_h_

#include "CEGUIWindow.h"


// Start of CEGUI namespace section
namespace CEGUI
{
/*!
\brief
	Helper class used to convert various data types to and from the format expected in Propery strings
*/
class PropertyHelper
{
public:
	static	float	stringToFloat(const String& str);
	static	uint	stringToUint(const String& str);
	static	bool	stringToBool(const String& str);
	static	Size	stringToSize(const String& str);
	static	Point	stringToPoint(const String& str);
	static	Rect	stringToRect(const String& str);
	static	MetricsMode	stringToMetricsMode(const String& str);
	static const Image*	stringToImage(const String& str);

	static String	floatToString(float val);
	static String	uintToString(uint val);
	static String	boolToString(bool val);
	static String	sizeToString(const Size& val);
	static String	pointToString(const Point& val);
	static String	rectToString(const Rect& val);
	static String	metricsModeToString(MetricsMode val);
	static String	imageToString(const Image* const val);
};

} // End of  CEGUI namespace section


#endif	// end of guard _CEGUIPropertyHelper_h_
