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

#include "UICore/Display/Window/display_window_provider.h"
#include "UICore/Display/Render/graphic_context.h"
#include "UICore/Display/Platform/Win32/win32_window.h"
#include "UICore/Core/System/comptr.h"
#include <mutex>
#include <deque>

namespace uicore
{
	class D3DDisplayWindow : public DisplayWindowProvider
	{
	public:
		D3DDisplayWindow(const DisplayWindowDescription &description);
		~D3DDisplayWindow();

		Rect backing_geometry() const override;
		Rect backing_viewport() const override;
		float pixel_ratio() const override;

		bool has_focus() const;
		bool is_minimized() const;
		bool is_maximized() const;
		bool is_visible() const;
		bool is_fullscreen() const { return false; } // FIXME: real implementation
		std::string title() const;
		Size backing_minimum_size(bool client_area = false) const;
		Size backing_maximum_size(bool client_area = false) const;

		const GraphicContextPtr &gc() const;

		const InputDevicePtr &keyboard() const override { return window.get_keyboard(); }
		const InputDevicePtr &mouse() const override { return window.get_mouse(); }
		const std::vector<InputDevicePtr> &game_controllers() const override { return window.get_game_controllers(); }

		DisplayWindowHandle handle() const override;

		bool is_clipboard_text_available() const;
		bool is_clipboard_image_available() const;
		std::string clipboard_text() const;
		PixelBufferPtr clipboard_image() const;

		const ComPtr<ID3D11Device> &get_device() const { return device; }
		const ComPtr<ID3D11DeviceContext> &get_device_context() const { return device_context; }
		D3D_FEATURE_LEVEL get_feature_level() const { return feature_level; }
		const ComPtr<IDXGISwapChain> &get_swap_chain() const { return swap_chain; }
		const ComPtr<ID3D11Texture2D> &get_back_buffer() const { return back_buffers.front(); }
		const ComPtr<ID3D11RenderTargetView> &get_back_buffer_rtv() const { return back_buffer_rtvs.front(); }
		const ComPtr<ID3D11Debug> &get_debug() const { return debug; }
		const ComPtr<ID3D11InfoQueue> &get_info_queue() const { return info_queue; }

		Point backing_client_to_screen(const Point &client);
		Point backing_screen_to_client(const Point &screen);

		void capture_mouse(bool capture);

		void show_system_cursor();
		CursorPtr create_cursor(const CursorDescription &cursor_description);
		void set_cursor(const CursorPtr &cursor);
		void set_cursor(StandardCursor type);
		void set_cursor_handle(HCURSOR cursor);
		void hide_system_cursor();

		void set_title(const std::string &new_title);
		void set_backing_position(const Rect &pos, bool client_area);
		void set_backing_size(int width, int height, bool client_area);
		void set_backing_minimum_size(int width, int height, bool client_area);
		void set_backing_maximum_size(int width, int height, bool client_area);
		void set_enabled(bool enable);

		void minimize();
		void restore();
		void maximize();
		void toggle_fullscreen();

		void show(bool activate);
		void hide();

		void bring_to_front();

		void backing_flip(int interval);

		void update(const Rect &rect);

		void set_clipboard_text(const std::string &text);
		void set_clipboard_image(const PixelBufferPtr &buf);

		void request_repaint();

		void set_large_icon(const PixelBufferPtr &image);
		void set_small_icon(const PixelBufferPtr &image);

		void backing_enable_alpha_channel(const Rect &blur_rect);
		void backing_extend_frame_into_client_area(int left, int top, int right, int bottom);

		void validate_context();

	private:
		void create_swap_chain_buffers();
		void release_swap_chain_buffers();
		void on_window_resized();
		void log_debug_messages();

		Win32Window window;

		GraphicContextPtr _gc;

		ComPtr<ID3D11Device> device;
		ComPtr<ID3D11DeviceContext> device_context;
		D3D_FEATURE_LEVEL feature_level;
		ComPtr<IDXGISwapChain> swap_chain;
		ComPtr<ID3D11Debug> debug;
		ComPtr<ID3D11InfoQueue> info_queue;

		bool no_redirection_bitmap = false;
		int flipping_buffers = 0;
		std::deque<ComPtr<ID3D11Texture2D>> back_buffers;
		std::deque<ComPtr<ID3D11RenderTargetView>> back_buffer_rtvs;

		bool use_fake_front_buffer = false;
		ComPtr<ID3D11Texture2D> fake_front_buffer;

		int current_interval_setting = 1;

		typedef HRESULT(WINAPI *FuncD3D11CreateDeviceAndSwapChain)(
			__in_opt IDXGIAdapter* pAdapter,
			D3D_DRIVER_TYPE DriverType,
			HMODULE Software,
			UINT Flags,
			__in_ecount_opt(FeatureLevels) CONST D3D_FEATURE_LEVEL* pFeatureLevels,
			UINT FeatureLevels,
			UINT SDKVersion,
			__in_opt CONST DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
			__out_opt IDXGISwapChain** ppSwapChain,
			__out_opt ID3D11Device** ppDevice,
			__out_opt D3D_FEATURE_LEVEL* pFeatureLevel,
			__out_opt ID3D11DeviceContext** ppImmediateContext);

		static std::recursive_mutex d3d11_mutex;
		static HMODULE d3d11_dll;
		static FuncD3D11CreateDeviceAndSwapChain d3d11_createdeviceandswapchain;
	};
}
