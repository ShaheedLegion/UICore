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

#include "UICore/precomp.h"
#include "gl1_vertex_array_buffer.h"
#include "UICore/Display/Render/staging_buffer.h"

namespace uicore
{
	GL1VertexArrayBuffer::GL1VertexArrayBuffer(int new_size, BufferUsage usage)
	{
		delete[] data;
		data = nullptr;
		size = 0;
		data = new char[new_size];
		size = new_size;
	}

	GL1VertexArrayBuffer::GL1VertexArrayBuffer(const void *init_data, int new_size, BufferUsage usage)
	{
		delete[] data;
		data = nullptr;
		size = 0;
		data = new char[new_size];
		size = new_size;
		memcpy(data, init_data, size);
	}

	GL1VertexArrayBuffer::~GL1VertexArrayBuffer()
	{
		delete[] data;
	}

	void GL1VertexArrayBuffer::upload_data(const GraphicContextPtr &gc, int offset, const void *new_data, int new_size)
	{
		if ((offset < 0) || (new_size < 0) || ((new_size + offset) > size))
			throw Exception("Vertex array buffer, invalid size");

		memcpy(data + offset, new_data, new_size);
	}

	void GL1VertexArrayBuffer::copy_from(const GraphicContextPtr &gc, const StagingBufferPtr &buffer, int dest_pos, int src_pos, int size)
	{
		buffer->lock(gc, access_read_only);
		memcpy(this->data + dest_pos, (char *)buffer->data() + src_pos, size);
		buffer->unlock();
	}

	void GL1VertexArrayBuffer::copy_to(const GraphicContextPtr &gc, const StagingBufferPtr &buffer, int dest_pos, int src_pos, int size)
	{
		buffer->upload_data(gc, dest_pos, this->data + src_pos, size);
	}
}
