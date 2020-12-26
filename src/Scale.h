/**
 * File name: AbstractScale.h
 * Project: Geonkick (A kick synthesizer)
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

#ifndef GEONKICK_SCALE_H
#define GEONKICK_SCALE_H

#include "globals.h"
#include "GraphicsItem.h"

#include <RkPainter.h>

class Scale : public GraphicsItem
{
        struct AxisValue;
public:
        enum class ScaleType : int {
            ScaleLinear      = 0,
            ScaleLogarithmic = 1
        };

        enum class Orientation: int {
             Horizontal = 0,
             Vertical = 1,
        };

        Scale();
        virtual ~Scale() = default;
        void setName(const RkString &name);
        RkString name() const;
        void setRange(double from, int to);
        double getRangeFrom() const;
        double getRangeTo() const;
        void setValues(const std::vector<double> &values);
        void draw(RkPainter &painter) override;
        ScaleType type() const;
        void SetType(ScaleType type);
        bool isShowAxis() const;
        void setShowAxis(bool show = true);
        bool isShowAxisValue() const;
        void setShowAxisValue(bool show = true);
        Orientation orientation() const;
        void setOrientation(Orientation orientation);

 protected:
        const std::vector<AxisValue>& getAxisValues() const;
        RkPoint axisValuePosition(double value) const;
        RkString axisValueText(double value) const;
        void drawName(RkPainter &painter);
        void drawAxis(RkPainter &painter);
        void drawAxisValue(RkPainter &painter, const AxisValue &val);
        void updateAxisValuesPosition();
        void updateAxisValuesText();
        
 private:
        struct AxisValue {
                explicit AxisValue(double val = 0) : value{val} {}
                double value;
                RkPoint position;
                RkString text;
        };        
        RkString scaleName;
        ScaleType scaleType;
        Orientation scaleOrientation;
        double startRange;
        double endRange;
        RkSize scaleSize;
        RkPoint sacePosition;
        bool showAxis;
        bool showAxisValue;
        std::vector<AxisValue> axisValues;
};

#endif // GEONKICK_ABSTRACT_SCALE_H
