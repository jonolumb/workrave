// EventLabel.cc ---
//
// Copyright (C) 2003, 2004, 2007 Rob Caelers <robc@krandor.nl>
// All rights reserved.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include "preinclude.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "debug.hh"

#include "EventLabel.hh"


void
EventLabel::on_realize()
{
  GtkWidget *widget = GTK_WIDGET(gobj());

  GdkWindowAttr attributes;
  attributes.window_type = GDK_WINDOW_CHILD;
  attributes.x = widget->allocation.x;
  attributes.y = widget->allocation.y;
  attributes.width = widget->allocation.width;
  attributes.height = widget->allocation.height;
  attributes.wclass = GDK_INPUT_ONLY;
  attributes.event_mask = gtk_widget_get_events(widget);
  attributes.event_mask |= (GDK_EXPOSURE_MASK |
                            GDK_BUTTON_MOTION_MASK |
                            GDK_BUTTON_PRESS_MASK |
                            GDK_BUTTON_RELEASE_MASK |
                            GDK_ENTER_NOTIFY_MASK |
                            GDK_LEAVE_NOTIFY_MASK);

  gint attributes_mask = GDK_WA_X | GDK_WA_Y;

  Gtk::Label::on_realize();

  event_window = gdk_window_new(gtk_widget_get_parent_window(widget),
                                &attributes, attributes_mask);

  gdk_window_set_user_data(event_window, widget);
  gdk_window_show(event_window);
}


void
EventLabel::on_unrealize()
{
  if (event_window)
    {
      gdk_window_set_user_data(event_window, NULL);
      gdk_window_destroy(event_window);
      event_window = NULL;
    }

  Gtk::Label::on_unrealize();
}


bool
EventLabel::on_map_event(GdkEventAny *event)
{
  bool ret = Gtk::Label::on_map_event(event);

  if (event_window)
    {
      gdk_window_show(event_window);
    }

  return ret;
}


bool
EventLabel::on_unmap_event(GdkEventAny *event)
{
  if (event_window)
    {
      gdk_window_hide(event_window);
    }

  return Gtk::Label::on_unmap_event(event);
}

void
EventLabel::on_size_allocate(Gtk::Allocation &allocation)
{
  Gtk::Label::on_size_allocate(allocation);

  GtkWidget *widget = GTK_WIDGET(gobj());

  if (GTK_WIDGET_REALIZED(widget))
    {
      gdk_window_move_resize(event_window,
                             allocation.get_x(),
                             allocation.get_y() ,
                             allocation.get_width(),
                             allocation.get_height());
    }
}
