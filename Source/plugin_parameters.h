/* ----------------------------------------------------------------------------

   Squeezer
   ========
   Flexible general-purpose audio compressor with a touch of lemon.

   Copyright (c) 2013-2018 Martin Zuther (http://www.mzuther.de/)

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

#pragma once

#include "FrutHeader.h"
#include "compressor.h"


class SqueezerPluginParameters :
    public frut::parameter::Juggler
{
public:
    SqueezerPluginParameters();

    String toString();

    static const File getSkinDirectory();
    String getSkinName();
    void setSkinName(const String &strSkinName);

    enum Parameters  // public namespace!
    {
        selBypass = 0,
        selDetectorRmsFilter,
        selDesign,
        selDetector,
        selGainStage,

        selThresholdSwitch,
        selThreshold,
        selRatioSwitch,
        selRatio,
        selKneeWidth,

        selAttackRateSwitch,
        selAttackRate,
        selReleaseRateSwitch,
        selReleaseRate,

        selAutoMakeupGain,
        selMakeupGainSwitch,
        selMakeupGain,
        selWetMixSwitch,
        selWetMix,

        selSidechainInput,
        selSidechainHPFCutoffSwitch,
        selSidechainHPFCutoff,
        selSidechainLPFCutoffSwitch,
        selSidechainLPFCutoff,
        selSidechainListen,

        numberOfParametersRevealed,

        selSkinName = numberOfParametersRevealed,

        numberOfParametersComplete,
    };

private:
    JUCE_LEAK_DETECTOR(SqueezerPluginParameters);
};
