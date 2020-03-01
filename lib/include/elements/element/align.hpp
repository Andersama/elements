/*=============================================================================
   Copyright (c) 2016-2020 Joel de Guzman

   Distributed under the MIT License [ https://opensource.org/licenses/MIT ]
=============================================================================*/
#if !defined(ELEMENTS_ALIGN_APRIL_14_2016)
#define ELEMENTS_ALIGN_APRIL_14_2016

#include <elements/element/proxy.hpp>
#include <elements/support/context.hpp>
#include <memory>

namespace cycfi { namespace elements
{
   ////////////////////////////////////////////////////////////////////////////
   // Alignment elements
   ////////////////////////////////////////////////////////////////////////////
   class align_element_base : public proxy_base
   {
   public:
                     align_element_base(double align)
                      : _align(align)
                     {}

      double         align() const        { return _align; }
      void           align(double align_)  { _align = align_; }

   private:

      double         _align;
   };

   template <typename Subject>
   class halign_element : public proxy<Subject, align_element_base>
   {
   public:

      using base_type = proxy<Subject, align_element_base>;

                              halign_element(double align, Subject&& subject);

      view_limits             limits(basic_context const& ctx) const override;
      void                    prepare_subject(context& ctx) override;
   };

   template <typename Subject>
   inline halign_element<Subject>
   halign(double align, Subject&& subject)
   {
      return { align, std::forward<Subject>(subject) };
   }

   template <typename Subject>
   inline halign_element<Subject>
   align_left(Subject&& subject)
   {
      return { 0.0, std::forward<Subject>(subject) };
   }

   template <typename Subject>
   inline halign_element<Subject>
   align_center(Subject&& subject)
   {
      return { 0.5, std::forward<Subject>(subject) };
   }

   template <typename Subject>
   inline halign_element<Subject>
   align_right(Subject&& subject)
   {
      return { 1.0, std::forward<Subject>(subject) };
   }

   template <typename Subject>
   inline halign_element<Subject>::halign_element(double align, Subject&& subject)
    : base_type(std::forward<Subject>(subject), align)
   {}

   template <typename Subject>
   inline view_limits halign_element<Subject>::limits(basic_context const& ctx) const
   {
      auto e_limits = this->subject().limits(ctx);
      return { { e_limits.min.x, e_limits.min.y }, { full_extent, e_limits.max.y } };
   }

   template <typename Subject>
   inline void halign_element<Subject>::prepare_subject(context& ctx)
   {
      view_limits    e_limits          = this->subject().limits(ctx);
      double         elem_width        = e_limits.min.x;
      double         available_width   = ctx.bounds.width();

      if (available_width > elem_width)
         elem_width = std::min(available_width, e_limits.max.x);

      ctx.bounds.left += (available_width - elem_width) * this->align();
      ctx.bounds.width(elem_width);
   }

   ////////////////////////////////////////////////////////////////////////////
   template <typename Subject>
   class valign_element : public proxy<Subject, align_element_base>
   {
   public:

      using base_type = proxy<Subject, align_element_base>;

                              valign_element(double align, Subject&& subject);

      view_limits             limits(basic_context const& ctx) const override;
      void                    prepare_subject(context& ctx) override;
   };

   template <typename Subject>
   inline valign_element<Subject>
   valign(double align, Subject&& subject)
   {
      return { align, std::forward<Subject>(subject) };
   }

   template <typename Subject>
   inline valign_element<Subject>
   align_top(Subject&& subject)
   {
      return { 0.0, std::forward<Subject>(subject) };
   }

   template <typename Subject>
   inline valign_element<Subject>
   align_middle(Subject&& subject)
   {
      return { 0.5, std::forward<Subject>(subject) };
   }

   template <typename Subject>
   inline valign_element<Subject>
   align_bottom(Subject&& subject)
   {
      return { 1.0, std::forward<Subject>(subject) };
   }

   template <typename Subject>
   valign_element<Subject>::valign_element(double align, Subject&& subject)
    : base_type(std::forward<Subject>(subject), align)
   {}

   template <typename Subject>
   inline view_limits valign_element<Subject>::limits(basic_context const& ctx) const
   {
      auto e_limits = this->subject().limits(ctx);
      return { { e_limits.min.x, e_limits.min.y }, { e_limits.max.x, full_extent } };
   }

   template <typename Subject>
   inline void valign_element<Subject>::prepare_subject(context& ctx)
   {
      auto  e_limits          = this->subject().limits(ctx);
      double elem_height      = e_limits.min.y;
      double available_height = ctx.bounds.height();

      if (available_height > elem_height)
         elem_height = std::min(available_height, e_limits.max.y);

      ctx.bounds.top += (available_height - elem_height) * this->align();
      ctx.bounds.height(elem_height);
   }

   ////////////////////////////////////////////////////////////////////////////
   template <typename Subject>
   inline auto align_left_top(Subject&& subject)
   {
      return align_left(align_top(std::forward<Subject>(subject)));
   }

   template <typename Subject>
   inline auto align_center_top(Subject&& subject)
   {
      return align_center(align_top(std::forward<Subject>(subject)));
   }

   template <typename Subject>
   inline auto align_right_top(Subject&& subject)
   {
      return align_right(align_top(std::forward<Subject>(subject)));
   }

   template <typename Subject>
   inline auto align_left_middle(Subject&& subject)
   {
      return align_left(align_middle(std::forward<Subject>(subject)));
   }

   template <typename Subject>
   inline auto align_center_middle(Subject&& subject)
   {
      return align_center(align_middle(std::forward<Subject>(subject)));
   }

   template <typename Subject>
   inline auto align_right_middle(Subject&& subject)
   {
      return align_right(align_middle(std::forward<Subject>(subject)));
   }

   template <typename Subject>
   inline auto align_left_bottom(Subject&& subject)
   {
      return align_left(align_bottom(std::forward<Subject>(subject)));
   }

   template <typename Subject>
   inline auto align_center_bottom(Subject&& subject)
   {
      return align_center(align_bottom(std::forward<Subject>(subject)));
   }

   template <typename Subject>
   inline auto align_right_bottom(Subject&& subject)
   {
      return align_right(align_bottom(std::forward<Subject>(subject)));
   }
}}

#endif
