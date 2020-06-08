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
MeterBar::MeterBar()
{
   // initialize variables
   create();
};


/// Create a new meter bar (and delete an existing one).  The meter
/// bar can be filled using addSegment() and its cousins.
///
void MeterBar::create()
{
   // this component does not have any transparent areas (increases
   // performance on redrawing)
   setOpaque( true );

   // lowest level of a 24-bit-signal in decibels
   float initialLevel = -144.0f;

   // initialise "normal" levels
   normalLevel_ = initialLevel;
   normalLevelPeak_ = initialLevel;

   // initialise "discrete" levels
   discreteLevel_ = initialLevel;
   discreteLevelPeak_ = initialLevel;

   // initialise meter dimensions
   barWidth_ = getWidth();
   barHeight_ = getHeight();

   // initialise segment width (we always use the coordinates for a
   // vertical meter, so this corresponds to the segment height in
   // horizontal meters)
   segmentWidth_ = barWidth_;

   // clear array with meter segments
   meterSegments_.clear();

   // clear array with segment spacings
   segmentSpacing_.clear();
}


/// Add a meter segment to the meter.
///
/// @param segment segment to add (will be deleted automatically)
///
/// @param segmentHeight height of the segment (in pixels)
///
/// @param spacingBefore spacing before the segment (in pixels)
///
void MeterBar::addSegment(
   widgets::MeterSegment* segment,
   int segmentHeight,
   int spacingBefore )

{
   // set levels to current levels; prevents blinking on (re)load
   segment->setLevels( normalLevel_, normalLevelPeak_,
                       discreteLevel_, discreteLevelPeak_ );

   // add spacing to meter bar's height (no spacing before first
   // meter segment!)
   if ( meterSegments_.size() > 0 ) {
      barHeight_ += spacingBefore;
   }

   // store corrected segment spacing
   segmentSpacing_.add( spacingBefore );

   // add segment to meter bar
   meterSegments_.add( segment );

   // set dimensions of meter segment; remember that we always use
   // the coordinates for a vertical meter!
   segment->setBounds( 0,
                       barHeight_,
                       segmentWidth_,
                       segmentHeight );

   // add segment height to meter bar's height
   barHeight_ += segmentHeight;

   // show meter segment
   addAndMakeVisible( segment );

   // update dimensions of meter bar
   resized();
}


/// Add a discrete meter segment to the meter.
///
/// @param lowerThreshold lower threshold level (in decibels)
///
/// @param thresholdRange difference between lower and upper level
///        threshold (in decibels)
///
/// @param retainSignalFactor if set to value other than 0.0, the segment
///        automatically fades out and all segments with lower
///        thresholds remain dark.  This factor determines how much of
///        the original brightness remains between updates (range: 0.0
///        to 1.0).
///
/// @param newSignalFactor if retainSignalFactor is set to a value other
///        than 0.0, this factor determines how much of the new signal
///        is added to the brightness (range: 0.0 to 1.0).
///
/// @param isTopmost if set to **true**, the segment has no upper
///        level threshold
///
/// @param segmentHeight height of the segment (in pixels)
///
/// @param spacingBefore spacing before the segment (in pixels)
///
/// @param segmentColour colour of the segment
///
/// @param peakMarkerColour colour of the peak marker
///
void MeterBar::addDiscreteSegment(
   float lowerThreshold,
   float thresholdRange,
   float retainSignalFactor,
   float newSignalFactor,
   bool isTopmost,
   int segmentHeight,
   int spacingBefore,
   const Colour& segmentColour,
   const Colour& peakMarkerColour )

{
   // create new discrete meter segment (will be deleted
   // automatically)
   widgets::MeterSegmentDiscrete* segment =
      new widgets::MeterSegmentDiscrete( retainSignalFactor,
                                         newSignalFactor );

   // set segment's lower threshold and display range (both in
   // decibels) and whether it is the topmost segment
   segment->setThresholdAndRange( lowerThreshold,
                                  thresholdRange,
                                  isTopmost );

   // set segment colours
   segment->setColours( segmentColour, peakMarkerColour );

   // add segment to meter
   addSegment(
      segment,
      segmentHeight,
      spacingBefore );
}


/// Add a continuous meter segment to the meter.
///
/// @param lowerThreshold lower threshold level (in decibels)
///
/// @param thresholdRange difference between lower and upper level
///        threshold (in decibels)
///
/// @param nextPixelRange level that corresponds to exactly one pixel
///        on the next segment (in decibels)
///
/// @param isTopmost if set to **true**, the segment has no upper
///        level threshold
///
/// @param segmentHeight height of the segment (in pixels)
///
/// @param spacingBefore spacing before the segment (in pixels)
///
/// @param segmentColour colour of the segment
///
/// @param peakMarkerColour colour of the peak marker
///
void MeterBar::addContinuousSegment(
   float lowerThreshold,
   float thresholdRange,
   float nextPixelRange,
   bool isTopmost,
   int segmentHeight,
   int spacingBefore,
   const Colour& segmentColour,
   const Colour& peakMarkerColour )

{
   // create new continuous meter segment (will be deleted
   // automatically)
   widgets::MeterSegmentContinuous* segment =
      new widgets::MeterSegmentContinuous();

   // set segment's lower threshold and display range (both in
   // decibels) and whether it is the topmost segment
   segment->setThresholdAndRange( lowerThreshold,
                                  thresholdRange,
                                  nextPixelRange,
                                  isTopmost );

   // set segment colours
   segment->setColours( segmentColour, peakMarkerColour );

   // add segment to meter
   addSegment(
      segment,
      segmentHeight,
      spacingBefore );

   // add (slightly) bigger margin to top-most segment
   if ( isTopmost ) {
      Rectangle<int> bounds = segment->getBounds();
      Rectangle<int> newBounds = bounds.withTop( bounds.getY() + 1 );

      // update position and size
      segment->setBounds( newBounds );
   }
}


/// Get the meter's orientation.
///
/// @return current orientation
///
widgets::Orientation MeterBar::getOrientation()
{
   return orientation_;
}


/// Set the meter's orientation.
///
/// @param orientation new meter orientation
///
void MeterBar::setOrientation(
   widgets::Orientation orientation )
{
   // update orientation
   orientation_ = orientation;

   auto bounds = getBoundsInParent();
   auto newTransform = orientation_.getTransform( bounds );

   // FIXME: use *local* positions
   setTransform( newTransform );
}


/// Get current segment width.
///
/// @return segment width for vertical meters and segment height for
///         horizontal meters.
///
int MeterBar::getSegmentWidth()
{
   return segmentWidth_;
}


/// Set segment width.  Sets segment width for vertical meters and
/// segment height for horizontal meters.
///
/// @param segmentWidth new segment width (or height, see above)
///
void MeterBar::setSegmentWidth(
   int segmentWidth )

{
   // update segment width
   segmentWidth_ = segmentWidth;

   // update meter bar's width
   barWidth_ = segmentWidth_;

   // update meter segments
   for ( int index = 0; index < meterSegments_.size(); ++index ) {
      // get current segment
      widgets::MeterSegment* segment = meterSegments_[index];

      // set dimensions of meter segment
      segment->setSize( segmentWidth_, segment->getHeight() );
   }

   // update dimensions of meter bar
   resized();
}


/// Paint meter bar.
///
/// @param g graphics context
///
void MeterBar::paint(
   Graphics& g )

{
   // fill background with black (disabled peak markers will be drawn
   // in black)
   g.fillAll( Colours::black );
}


/// This function overrides the meter bar's dimensions!
///
void MeterBar::resized()
{
   // override dimensions of meter bar
   setSize( barWidth_, barHeight_ );
}


/// Set normal (average) levels.  Use this only if you completely
/// disregard discrete (peak) levels!
///
/// @param normalLevel new normal level
///
/// @param normalLevelPeak new normal peak level
///
void MeterBar::setNormalLevels(
   float normalLevel, float normalLevelPeak )

{
   // "normal" levels have changed
   if ( ( normalLevel_ != normalLevel ) ||
        ( normalLevelPeak_ != normalLevelPeak ) ) {
      // update levels
      normalLevel_ = normalLevel;
      normalLevelPeak_ = normalLevelPeak;

      // update meter segments
      for ( int index = 0; index < meterSegments_.size(); ++index ) {
         // get current segment
         widgets::MeterSegment* segment = meterSegments_[index];

         segment->setNormalLevels(
            normalLevel_, normalLevelPeak_ );
      }
   }
}


/// Set discrete (peak) levels.  Use this only if you completely
/// disregard normal (average) levels!
///
/// @param discreteLevel new discrete level
///
/// @param discreteLevelPeak new discrete peak level
///
void MeterBar::setDiscreteLevels(
   float discreteLevel, float discreteLevelPeak )

{
   // "discrete" levels have changed
   if ( ( discreteLevel_ != discreteLevel ) ||
        ( discreteLevelPeak_ != discreteLevelPeak ) ) {
      // update levels
      discreteLevel_ = discreteLevel;
      discreteLevelPeak_ = discreteLevelPeak;

      // update meter segments
      for ( int index = 0; index < meterSegments_.size(); ++index ) {
         // get current segment
         widgets::MeterSegment* segment = meterSegments_[index];

         segment->setDiscreteLevels(
            discreteLevel_, discreteLevelPeak_ );
      }
   }
}


/// Set discrete (peak) and normal (average) levels.
///
/// @param normalLevel new normal level
///
/// @param normalLevelPeak new normal peak level
///
/// @param discreteLevel new discrete level
///
/// @param discreteLevelPeak new discrete peak level
///
void MeterBar::setLevels(
   float normalLevel, float normalLevelPeak,
   float discreteLevel, float discreteLevelPeak )

{
   // "normal" or "discrete" levels have changed
   if ( ( normalLevel_ != normalLevel ) ||
        ( normalLevelPeak_ != normalLevelPeak ) ||
        ( discreteLevel_ != discreteLevel ) ||
        ( discreteLevelPeak_ != discreteLevelPeak ) ) {
      // update "normal" levels
      normalLevel_ = normalLevel;
      normalLevelPeak_ = normalLevelPeak;

      // update "discrete" levels
      discreteLevel_ = discreteLevel;
      discreteLevelPeak_ = discreteLevelPeak;

      // update meter bars
      for ( int index = 0; index < meterSegments_.size(); ++index ) {
         // get current segment
         widgets::MeterSegment* segment = meterSegments_[index];

         segment->setLevels(
            normalLevel_, normalLevelPeak_,
            discreteLevel_, discreteLevelPeak_ );
      }
   }
}

}
}
