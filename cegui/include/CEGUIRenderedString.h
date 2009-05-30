/***********************************************************************
    filename:   CEGUIRenderedString.h
    created:    25/05/2009
    author:     Paul Turner
 *************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2009 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#ifndef _CEGUIRenderedString_h_
#define _CEGUIRenderedString_h_

#include "CEGUISize.h"
#include <vector>

// Start of CEGUI namespace section
namespace CEGUI
{
class RenderedStringComponent;
class GeometryBuffer;
class Vector2;
class Rect;

/*!
\brief
    Class representing a rendered string of entities.

    Here 'string' does not refer solely to a text string, rather a string of
    any renderable items.
*/
class CEGUIEXPORT RenderedString
{
public:
    //! Constructor.
    RenderedString();

    //! Destructor.
    virtual ~RenderedString();

    /*!
    \brief
        Draw the string to a GeometryBuffer.

    \param buffer
        GeometryBuffer object that is to receive the geometry resulting from the
        draw operations.

    \param position
        Vector2 describing the position where the RenderedString is to be drawn.
        Note that this is not the final onscreen position, but the position as
        offset from the top-left corner of the entity represented by the
        GeometryBuffer.

    \param clip_rect
        Pointer to a Rect object that describes a clipping rectangle that should
        be used when drawing the RenderedString.  This may be 0 if no clipping
        is required.
    */
    void draw(GeometryBuffer& buffer, const Vector2& position,
              const Rect* clip_rect) const;

    /*!
    \brief
        Return the total pixel size of the RenderedString.
        
    \return
        Size object describing the size of the rendered output of this
        RenderedString in pixels.
    */
    Size getPixelSize() const;

    //! append \a component to the list of components drawn for this string.
    void appendComponent(const RenderedStringComponent& component);

    //! clear the list of components drawn for this string.
    void clearComponents();

    //! return the number of components that make up this string.
    size_t getComponentCount() const;

    /*!
    \brief
        split the string as close to \a split_point as possible.
        
        The RenderedString \a left will receive the left portion of the split,
        while the right portion of the split will remain in this RenderedString.

    \param split_point
        float value specifying the pixel location where the split should occur.
        The actual split will occur as close to this point as possible, though
        preferring a shorter 'left' portion when the split can not be made
        exactly at the requested point.

    \param left
        RenderedString object that will receieve the left portion of the split.
        Any existing content in the RenderedString is replaced.
    */
    void split(float split_point, RenderedString& left);

    //! Copy constructor.
    RenderedString(const RenderedString& other);
    //! Assignment.
    RenderedString& operator=(const RenderedString& rhs);

protected:
    //! Collection type used to hold the string components.
    typedef std::vector<RenderedStringComponent*> ComponentList;
    //! RenderedStringComponent objects that comprise this RenderedString.
    ComponentList d_components;
    //! Make this object's component list a clone of \a list.
    void cloneComponentList(const ComponentList& list);
    //! Free components in the given ComponentList and clear the list.
    static void clearComponentList(ComponentList& list);
};

} // End of  CEGUI namespace section

#endif // end of guard _CEGUIRenderedString_h_