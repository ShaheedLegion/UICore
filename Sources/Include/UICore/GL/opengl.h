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

#include "opengl_defines.h"
#include <utility>
#include <string>
#include "../Display/Render/texture.h"

#if defined(_MSC_VER)
#define cl_tls_variable _declspec(thread)
#elif defined(__APPLE__) // To do: change check to only apply to iOS/ARM target
#define cl_tls_variable
#else
#define cl_tls_variable __thread
#endif

namespace uicore
{
	class GLFunctions;
	class GraphicContext;
	class OpenGLContextProvider;
	class GL1GraphicContext;
	class GL3GraphicContext;

	enum TextureFormat;

	/// \brief Extension procedure address typedef for OpenGL.
	typedef void (ProcAddress)();

	typedef struct
	{
		TextureFormat texture_format;
		bool valid;		//!< True when this is a valid opengl format
		GLint internal_format;
		GLenum pixel_format;
		GLenum pixel_datatype;
	} TextureFormat_GL;

	typedef struct
	{
		GLenum source;
		GLenum type;
		GLenum severity;
		GLuint id;
		std::string message;

	} MessageLog_GL;

	/// \brief OpenGL utility class.
	class OpenGL
	{
	public:
		/// \brief Get OpenGL extension specific function address.
		static ProcAddress *get_proc_address(const std::string &function_name);

		/// \brief Function table for OpenGL 2.0.
		static cl_tls_variable GLFunctions *functions;

		/// \brief Returns the opengl texture format
		static TextureFormat_GL textureformat(TextureFormat format);

		/// \brief Sets the thread's OpenGL context to the one used by the graphic context.
		static void set_active(const GraphicContextPtr &gc);

		/// \brief Sets the thread's OpenGL context to the one used by the graphic context.
		static void set_active(const OpenGLContextProvider * const gc_provider);

		/// \brief Sets the thread's OpenGL context to the first valid allocated one
		///
		/// If a valid OpenGL context is not found, then "no render context" is set.
		///
		/// \return true = Success. false = No OpenGL contexts could be found
		static bool set_active();

		/// \brief Throw an exception if an OpenGL error was detected ( Using glGetError() )
		///
		/// Remember to call glGetError() to clear any previous errors
		static void check_error();

		/// \brief Get the OpenGL message log
		///
		/// This is required for this function to operate
		/// OpenGLContextDescription gldesc;
		/// gldesc.set_debug(true);
		/// OpenGLTarget::set_description(gldesc);
		static std::vector<MessageLog_GL> get_message_log(GLuint numMsgs);

		/// \brief Returns the OpenGL texture handle
		static GLuint get_texture_handle(const TexturePtr &texture);

		static GLenum to_enum(DrawBuffer buf);
		static GLenum to_enum(CompareFunction func);
		static GLenum to_enum(StencilOp op);
		static GLenum to_enum(CullMode mode);
		static GLenum to_enum(FillMode mode);
		static GLenum to_enum(BlendFunc func);
		static GLenum to_enum(BlendEquation eq);
		static GLenum to_enum(VertexAttributeDataType value);
		static GLenum to_enum(PrimitivesType value);
		static GLenum to_enum(LogicOp op);
		static GLenum to_enum(TextureFilter filter);
		static GLenum to_enum(TextureWrapMode mode);
		static GLenum to_enum(TextureCompareMode mode);
		static GLenum to_cube_target(int index);
		static GLenum to_enum(BufferUsage usage);
		static GLenum to_enum(BufferAccess access);

	private:
		/// \brief Remove the opengl bindings from the thread's OpenGL context
		/// 
		/// This should only be called by the OpenGLContextProvider destructor
		static void remove_active(const OpenGLContextProvider * const gc_provider);

		friend class GL1GraphicContext;
		friend class GL3GraphicContext;
		friend class PBuffer_GL1_Impl;
	};
}
