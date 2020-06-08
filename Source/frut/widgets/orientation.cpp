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

namespace frut
{
namespace widgets
{

/// Default constructor.
///
Orientation::Orientation()
{
   setAngle( Orientation::orientations::vertical );
};


Orientation::Orientation( Orientation::orientations newOrientation )
{
   setAngle( newOrientation );
};


void Orientation::setAngle( Orientation::orientations newOrientation )
{
   setAngle( static_cast<int>( newOrientation ) );
};


void Orientation::setAngle( int newAngle )
{
   angle = newAngle % 360;
};


int Orientation::getAngle()
{
   return angle;
};


void Orientation::mirror()
{
   setAngle( angle + 180 );
};


void Orientation::turnLeft()
{
   setAngle( angle + 90 );
};


void Orientation::turnRight()
{
   setAngle( angle - 90 );
};


AffineTransform Orientation::getTransform( Rectangle<int> bounds )
{
   if ( angle == 0 ) {
      return AffineTransform();
   }

   auto pivot = bounds.getCentre().toFloat();

   return AffineTransform::rotation(
             degreesToRadians( static_cast<float>( angle ) ),
             pivot.getX(),
             pivot.getY() );
}

}
}
