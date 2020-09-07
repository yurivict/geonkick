/**
 * File name: SampleBrowser.cpp
 * Project: Geonkick (A percussion synthesizer)
 *
 * Copyright (C) 2020 Iurie Nistor <http://iuriepage.wordpress.com>
 *
 * This file is part of Geonkick.
 *
 * GeonKick is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "SampleBrowser.h"
#include "file_dialog.h"
#include "ViewState.h"
#include "geonkick_api.h"

SampleBrowser::SampleBrowser(GeonkickWidget *parent, GeonkickApi* api)
        : GeonkickWidget(parent)
        , geonkickApi{api}
        , fileBrowser{new FileDialog(this)}
{
        fileBrowser->setFilters({".wav", ".WAV", ".flac", ".FLAC", ".ogg", ".OGG"});
        fileBrowser->setHomeDirectory(geonkickApi->getSettings("GEONKICK_CONFIG/HOME_PATH"));
        auto viewState = static_cast<ViewState*>(findObject("ViewState"));
        fileBrowser->setCurrentDirectoy(viewState->samplesBrowserPath());
        RK_ACT_BIND(fileBrowser,
                    directoryChanged,
                    RK_ACT_ARGS(const std::string &path),
                    viewState,
                    setSamplesBrowserPath(path));
        setFixedSize(parent->size());
        show();
}
