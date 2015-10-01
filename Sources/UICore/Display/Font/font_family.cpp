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
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Magnus Norddahl
*/

#include "UICore/precomp.h"
#include "UICore/Display/Font/font_family.h"
#include "UICore/Display/Font/font_metrics.h"
#include "UICore/Display/Font/font_description.h"
#include "UICore/Display/TargetProviders/graphic_context_provider.h"
#include "UICore/Core/IOData/path_help.h"
#include "UICore/Core/IOData/file.h"
#include "UICore/Core/System/databuffer.h"
#include "UICore/Core/Text/text.h"
#include "UICore/Core/Text/string_format.h"
#include "UICore/Core/Text/utf8_reader.h"
#include "UICore/Display/2D/canvas.h"
#include "font_family_impl.h"

namespace uicore
{
	FontFamily::FontFamily()
	{
	}

	FontFamily::FontFamily(const std::string &family_name) : impl(std::make_shared<FontFamily_Impl>(family_name))
	{
	}

	const std::string &FontFamily::get_family_name() const
	{
		throw_if_null();
		return impl->get_family_name();
	}

	void FontFamily::add(const std::string &typeface_name, float height)
	{
		throw_if_null();
		FontDescription desc;
		desc.set_height(height);
		impl->add(desc, typeface_name);
	}

	void FontFamily::add(const std::string &typeface_name, const FontDescription &desc)
	{
		throw_if_null();
		impl->add(desc, typeface_name);
	}

	void FontFamily::add(const FontDescription &desc, const std::string &ttf_filename)
	{
		throw_if_null();
		DataBuffer font_databuffer;
		if (!ttf_filename.empty())
		{
			font_databuffer = File::read_all_bytes(ttf_filename);
		}

		impl->add(desc, font_databuffer);
	}

	void FontFamily::throw_if_null() const
	{
		if (!impl)
			throw Exception("FontFamily is null");
	}
}
