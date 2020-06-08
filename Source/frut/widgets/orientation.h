/* ----------------------------------------------------------------------------

   FrutJUCE
   ========
   Common classes for use with the JUCE library

   Copyright (c) 2010-2020 Martin Zuther (http://www.mzuther.de/)

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   Thank you for using free software!

---------------------------------------------------------------------------- */

#ifndef FRUT_WIDGETS_ORIENTATION_H
#define FRUT_WIDGETS_ORIENTATION_H

namespace frut
{
namespace widgets
{

/// Orientation for widgets.
///
class Orientation
{
public:
   enum orientations { // public namespace!
      /// vertical widget (bottom to top)
      vertical = 0,

      /// horizontal widget (left to right)
      horizontal = 90,

      /// inverted vertical widget (top to bottom)
      verticalInverted = 180,

      /// inverted horizontal widget (right to left)
      horizontalInverted = 270
   };

   Orientation();
   explicit Orientation( Orientation::orientations newOrientation );

   int getAngle();
   void setAngle( Orientation::orientations newOrientation );
   void setAngle( int newAngle );

   void mirror();
   void turnLeft();
   void turnRight();

   AffineTransform getTransform( Point<float> pivot );

private:
   int angle;
};

}
}

#endif  // FRUT_WIDGETS_ORIENTATION_H
