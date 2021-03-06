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
**    Mark Page
*/


#pragma once

#include <memory>
#include "../System/databuffer.h"

namespace uicore
{
	/// \brief MD5 hash function class.
	class MD5
	{
	public:
		/// \brief Constructs a MD5 hash generator.
		static std::shared_ptr<MD5> create();

		static const int hash_size = 16;

		/// \brief Returns the calculated hash.
		virtual std::string hash(bool uppercase = false) const = 0;

		/// \brief Get hash
		///
		/// \param out_hash = where to write to
		virtual void hash(unsigned char out_hash[hash_size]) const = 0;

		/// \brief Resets the hash generator.
		virtual void reset() = 0;

		/// \brief Enable a HMAC based calculation
		///
		/// Call this function before the initial add(). It is reset by reset()
		///
		/// \param key_data = The HMAC key
		/// \param key_size = The size of the key_data
		virtual void set_hmac(const void *key_data, int key_size) = 0;

		/// \brief Adds data to be hashed.
		virtual void add(const void *data, int size) = 0;

		/// \brief Add
		///
		/// \param data = Data Buffer
		virtual void add(const DataBufferPtr &data) = 0;

		/// \brief Finalize hash calculation.
		virtual void calculate() = 0;
	};

	typedef std::shared_ptr<MD5> MD5Ptr;
}
