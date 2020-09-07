/**
 * File name: UiSettings.h
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

#include "UiSettings.h"

UiSettings::UiSettings()
        : mainView{UiSettings::View::Controls}
        , samplesBrowser{"", UiSettings::Oscillator::Oscillator1}
{
}

void UiSettings::fromJsonObject(const rapidjson::Value &obj)
{
        for (const auto &m: obj.GetObject()) {
                if (m.name == "MainView" && m.value.IsInt())
                        mainView = static_cast<View>(m.value.GetInt());
                if (m.name == "SamplesBrowser" && m.value.IsObject())
                        parserSamplesBrowser(m.value);
        }
}

void UiSettings::parserSamplesBrowser(const rapidjson::Value &obj)
{
        for (const auto &m: obj.GetObject()) {
                if (m.name == "currentDirectory" && m.value.IsString())
                        samplesBrowser.currentDirectory = m.value.GetString();
                if (m.name == "oscillator" && m.value.IsInt())
                        samplesBrowser.oscillator = static_cast<Oscillator>(m.value.GetInt());
        }
}

std::string UiSettings::toJson() const
{
        std::ostringstream jsonStream;
        jsonStream << "{" << std::endl;
        jsonStream << "\"MainView\": " << static_cast<int>(mainView) << ", " << std::endl;
        jsonStream << "\"SamplesBrowser\": { " << std::endl;
        jsonStream << "    \"currentDirectory\": \"" << samplesBrowser.currentDirectory << "\", " << std::endl;
        jsonStream << "    \"oscillator\": " << static_cast<int>(samplesBrowser.oscillator) << std::endl;
        jsonStream << "}" << std::endl;
        jsonStream << "}" << std::endl;
        return jsonStream.str();
}

UiSettings::View UiSettings::getMainView() const
{
        return mainView;
}

void UiSettings::setMainView(View view)
{
        mainView = view;
}

void UiSettings::setSamplesBrowserPath(const std::string &path)
{
        samplesBrowser.currentDirectory = path;
}

std::string UiSettings::samplesBrowserPath() const
{
        return samplesBrowser.currentDirectory;
}

void UiSettings::setSamplesBrowserOscillator(UiSettings::Oscillator osc)
{
        samplesBrowser.oscillator = osc;
}

UiSettings::Oscillator UiSettings::samplesBrowserOscillator() const
{
        return samplesBrowser.oscillator;
}