/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#include <elements/element/misc.hpp>

namespace cycfi { namespace elements
{
   void panel::draw(context const& ctx)
   {
      draw_panel(
         ctx.canvas
       , ctx.bounds
       , get_theme().panel_color.opacity(_opacity)
       , 4.0
      );
   }

   void frame::draw(context const& ctx)
   {
      auto const&    theme_ = get_theme();
      auto&          canvas_ = ctx.canvas;
      auto const&    bounds = ctx.bounds;

      canvas_.line_width(theme_.frame_stroke_width);
      canvas_.stroke_style(colors::black.opacity(0.4));
      canvas_.stroke_round_rect(bounds.move(-1, -1), theme_.frame_corner_radius);
      canvas_.stroke_style(theme_.frame_color);
      canvas_.stroke_round_rect(bounds, theme_.frame_corner_radius);
   }

   heading::heading(std::string text, double size)
    : _text(std::move(text))
    , _font(get_theme().heading_font)
    , _size(size)
   {}

   heading::heading(std::string text, elements::font font_, double size)
    : _text(std::move(text))
    , _font(font_)
    , _size(size)
   {}

   view_limits heading::limits(basic_context const& ctx) const
   {
      auto& thm = get_theme();
      auto  size = measure_text(
         ctx.canvas, _text.c_str()
       , _font
       , thm.heading_font_size * _size // _size is a multiplier.
      );
      return { { size.x, size.y }, { size.x, size.y } };
   }

   void heading::draw(context const& ctx)
   {
      auto const&    theme_ = get_theme();
      auto&          canvas_ = ctx.canvas;
      auto           state = canvas_.new_state();

      canvas_.fill_style(theme_.heading_font_color);
      canvas_.font(
         _font
       , theme_.heading_font_size * _size // _size is a multiplier.
      );
      canvas_.text_align(canvas_.middle | canvas_.center);

      double cx = ctx.bounds.left + (ctx.bounds.width() / 2);
      double cy = ctx.bounds.top + (ctx.bounds.height() / 2);

      canvas_.fill_text(point{ cx, cy }, _text.c_str());
   }

   void title_bar::draw(context const& ctx)
   {
      draw_box_vgradient(ctx.canvas, ctx.bounds, 4.0);
   }

   label::label(std::string text, double size)
    : _text(std::move(text))
    , _font(get_theme().label_font)
    , _size(size)
   {}

   label::label(std::string text, elements::font font_, double size)
    : _text(std::move(text))
    , _font(font_)
    , _size(size)
   {}

   view_limits label::limits(basic_context const& ctx) const
   {
      auto& thm = get_theme();
      auto  size = measure_text(
         ctx.canvas, _text.c_str()
       , _font
       , thm.label_font_size * _size // _size is a multiplier.
      );
      return { { size.x, size.y }, { size.x, size.y } };
   }

   void label::draw(context const& ctx)
   {
      auto const&    theme_ = get_theme();
      auto&          canvas_ = ctx.canvas;
      auto           state = canvas_.new_state();

      canvas_.fill_style(theme_.label_font_color);
      canvas_.font(
         _font
       , theme_.label_font_size * _size // _size is a multiplier.
      );
      canvas_.text_align(canvas_.middle | canvas_.center);

      double cx = ctx.bounds.left + (ctx.bounds.width() / 2);
      double cy = ctx.bounds.top + (ctx.bounds.height() / 2);

      canvas_.fill_text(point{ cx, cy }, _text.c_str());
   }

   void vgrid_lines::draw(context const& ctx)
   {
      auto const&    theme_ = get_theme();
      auto&          canvas_ = ctx.canvas;
      auto const&    bounds = ctx.bounds;

      double pos = bounds.top;
      double incr = bounds.height() / _major_divisions;

      canvas_.stroke_style(theme_.major_grid_color);
      canvas_.line_width(theme_.major_grid_width);
      while (pos <= bounds.bottom+1)
      {
         canvas_.move_to({ bounds.left, pos });
         canvas_.line_to({ bounds.right, pos });
         canvas_.stroke();
         pos += incr;
      }

      pos = bounds.top;
      incr = bounds.height() / _minor_divisions;

      canvas_.stroke_style(theme_.minor_grid_color);
      canvas_.line_width(theme_.minor_grid_width);
      while (pos <= bounds.bottom+1)
      {
         canvas_.move_to({ bounds.left, pos });
         canvas_.line_to({ bounds.right, pos });
         canvas_.stroke();
         pos += incr;
      }
   }

   icon::icon(std::uint32_t code_, double size_)
    : _code(code_)
    , _size(size_)
   {}

   view_limits icon::limits(basic_context const& ctx) const
   {
      auto& thm = get_theme();
      double font_size = thm.icon_font_size * _size;
      point s = measure_icon(ctx.canvas, _code, font_size);
      return { { s.x, s.y }, { s.x, s.y } };
   }

   void icon::draw(context const& ctx)
   {
      auto& thm = get_theme();
      double font_size = thm.icon_font_size * _size;
      draw_icon(ctx.canvas, ctx.bounds, _code, font_size);
   }
}}

