/* ----------------------------------------------------------------------------

   Squeezer
   ========
   Flexible general-purpose audio compressor with a touch of citrus

   Copyright (c) 2013-2020 Martin Zuther (http://www.mzuther.de/)

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

#include "meter_bar_gain_reduction.h"


void MeterBarGainReduction::create(frut::widgets::Orientation orientation,
                                   bool discreteMeter,
                                   int mainSegmentHeight,
                                   const Colour &segmentColour)

{
    frut::widgets::MeterBar::create();

    setUpwardExpansion(false);

    int trueLowerThreshold = 0;
    int levelRange = 10;
    int numberOfBars = 18;

    for (int n = 0; n < numberOfBars; ++n)
    {
        bool hasHighestLevel = (n == (numberOfBars - 1)) ? true : false;

        if (discreteMeter)
        {
            // meter segment outlines overlap
            int spacingBefore = -1;
            int segmentHeight = mainSegmentHeight + 1;

            addDiscreteSegment(
                trueLowerThreshold * 0.1f,
                levelRange * 0.1f,
                0.0f,
                1.0f,
                hasHighestLevel,
                segmentHeight,
                spacingBefore,
                segmentColour,
                segmentColour.withMultipliedBrightness(0.7f));
        }
        else
        {
            // meter segment outlines must not overlap
            int spacingBefore = 0;
            int segmentHeight = mainSegmentHeight;

            addContinuousSegment(
                trueLowerThreshold * 0.1f,
                levelRange * 0.1f,
                (levelRange * 0.1f) / segmentHeight,
                hasHighestLevel,
                segmentHeight,
                spacingBefore,
                segmentColour,
                segmentColour.withMultipliedBrightness(0.7f));
        }

        trueLowerThreshold += levelRange;
    }

    // set orientation here to save some processing power
    setOrientation(orientation);
}


void MeterBarGainReduction::setUpwardExpansion(bool upwardExpansion)
{
    upwardExpansion_ = upwardExpansion;
    invertMeter(upwardExpansion_);
}
