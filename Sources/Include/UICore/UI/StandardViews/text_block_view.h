/*
**  UICore
**  Copyright (c) 1997-2015 The UICore Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries UICore may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
*/

#pragma once

#include "../View/view.h"
#include "../../Display/Font/font.h"
#include "../../Core/Math/color.h"
#include "label_view.h"

namespace uicore
{
	class TextBlockBaseViewImpl;

	class TextBlockBaseView : public View
	{
	public:
		TextBlockBaseView();

		const std::shared_ptr<Style> &text_style(const std::string &text_class = std::string()) const;

		void set_text_alignment(TextAlignment alignment);

		void clear();
		void add_text(const std::string &text, const std::string &text_class = std::string());
		void add_child(const std::shared_ptr<View> &view, float baseline_offset = 0.0f);

		void layout_children(const CanvasPtr &canvas) override;

	protected:
		void render_content(const CanvasPtr &canvas) override;
		float calculate_preferred_width(const CanvasPtr &canvas) override;
		float calculate_preferred_height(const CanvasPtr &canvas, float width) override;
		float calculate_first_baseline_offset(const CanvasPtr &canvas, float width) override;
		float calculate_last_baseline_offset(const CanvasPtr &canvas, float width) override;
		void child_added(const std::shared_ptr<View> &view) override;
		void child_removed(const std::shared_ptr<View> &view) override;

	private:
		std::shared_ptr<TextBlockBaseViewImpl> impl;
	};
}
